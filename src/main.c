#include "main.h"

GPS_Data_Point_TypeDef point;

uint8_t mode_string[10] = "IDLE";

uint8_t latitude_string[10] = " ";
uint8_t longitude_string[10] = " ";
uint8_t gps_status_string[12] = " ";
uint8_t buffer_status_string[10] = " ";
uint8_t distance_string[15] = "0.0";
uint8_t ns_string[2] = " ";
uint8_t ew_string[2] = " ";

uint8_t gps_input_buffer[GPS_MAXIMUM_BUFFER_SIZE] = " ";
float coordinates[RAM_MAX_COORDINATES][2] = {1};

uint32_t coordinates_num = 1;
float distance = 0;

uint16_t mode = IDLE;
uint8_t heartbeat = 0;
uint32_t filled = 0;

void enable_interrupts();
float calculate_distance(const float x[2], const float y[2]);
void update_display();

int main()
{
    UART0_Init(9600);
    UART1_Init(9600);

    GPIOF_default_init();

    I2C_Init();
    EEPROM_Init();
    Systick_Init();

    OLED_I2C_Init();

    coordinates_num = 0;
    distance = 0;
    filled = 0;

    strcpy(gps_status_string, "STARTING");
    update_display(); // Display STARTING message.

    Systick_Interrupt_Init(1000);
    enable_interrupts();

#ifdef DEBUG
    UART_printf("\n++End Init\n", UART0);
#endif

    // Main Program Loop
    while (1)
    {
#ifdef DEBUG
        UART_printf("\n++Main Loop\n", UART0);
#endif

        filled = gps_uart_fill_buffer(gps_input_buffer, UART1, GPS_MAXIMUM_BUFFER_SIZE);

#ifdef DEBUG
        UART_printf("\n++End Main Loop\n", UART0);
        UART0_print_float(coordinates_num);
#endif
    }
}

void UART0_IRQHandler()
{
#ifdef DEBUG
    UART_printf("\n++UART0_IRQHandler\n", UART0);
#endif

    UART0_ICR_R |= 1 << 4; // Acknowledge

    if (mode == IDLE)
    {
        uint8_t in;
        UART_ReceiveByte(UART0, &in);

        if (in == 'U' || in == 'u')
        {
            strcpy(mode_string, "READING"); // Display waiting message.
            OLED_clear_display();
            update_display();
            EEPROM_read_coordniates(); // take the size of data saved in Epprom to iterate over Epprom
        }

        // To empty FIFO, this assumes exactly 2 characters are sent! (No Line Ending)
        UART_ReceiveByte(UART0, &in);
    }

#ifdef DEBUG
    UART_printf("\n++End UART0_IRQHandler\n", UART0);
#endif
}

void SysTick_Handler()
{
#ifdef DEBUG
    UART_printf("\n++SysTick\n", UART0);
#endif

    heartbeat = !heartbeat;
    sprintf(buffer_status_string, "%d", filled);

    if (mode == IDLE)
    {
        strcpy(mode_string, "IDLE     "); // changing the value Oled String

        if (read_sw1())
        {
            OLED_clear_display();
            mode = RECORDING; // change mode to 1 if switch is on
        }

        if (Gps_Parse(gps_input_buffer, &point))
        {
            strcpy(gps_status_string, "Valid      ");
        }
        else
        {
            strcpy(gps_status_string, "Not Valid  ");
            if (filled < 100)
                strcpy(gps_status_string, "Check Wires");
        }
    }

    else if (mode == RECORDING)
    {
        strcpy(mode_string, "RECORDING");
        if (Gps_Parse(gps_input_buffer, &point))
        {
            // Update displayed coordinates.
            strcpy(gps_status_string, "Valid    ");
            float_to_string(point.latitude, latitude_string);
            float_to_string(point.longitude, longitude_string);

            // OLED_clear_display();

            if (coordinates_num < 1000) // Condition to avoid writing out of bounds.
            {
                coordinates[coordinates_num][0] = point.latitude; // Save new point.
                coordinates[coordinates_num][1] = point.longitude;
                coordinates_num++;

                if (coordinates_num > 5)
                {
                    float delta = calculate_distance(coordinates[coordinates_num - 1], coordinates[coordinates_num - 2]);

                    if (delta > DISTANCE_MIN_THRESHOLD && delta < DISTANCE_MAX_THRESHOLD) {
                        distance += delta;
                    } else {
                        coordinates_num--;
                    }

                    float_to_string(distance, distance_string);
                }
            }
        }
        else
        {
            strcpy(gps_status_string, "Not Valid ");
        }
        if (read_sw1())
        {
            strcpy(mode_string, "SAVING"); // Display waiting message.
            OLED_clear_display();
            update_display();
            if (coordinates_num < EEPROM_MAX_COORDINATES) // If the array can fit in the EEPROM
            {
                EEPROM_write_array((float(*)[2])coordinates, coordinates_num); // Save it all in the EEPROM
            }
            else
            {
                // Save the last 250 coordinates.
                EEPROM_write_array((float(*)[2])coordinates + coordinates_num - EEPROM_MAX_COORDINATES, EEPROM_MAX_COORDINATES);
            }
            mode = IDLE;
        }
    }

    update_display();

#ifdef DEBUG
    UART_printf("\n++End SysTick\n", UART0);
#endif
}

void enable_interrupts()
{
    UART0_IFLS_R = 0;
    __asm__("cpsie i");
}

void update_display()
{
    OLED_I2C_Write(0, 0, mode_string);
    OLED_I2C_Write(6 * 10, 0, gps_status_string);

    OLED_I2C_Write(0, 2, "Distance: ");
    OLED_I2C_Write(10 * 5 + 4, 2, distance_string);

    OLED_I2C_Write(0, 4, "Latitude: ");
    OLED_I2C_Write(10 * 6, 4, latitude_string);
    OLED_I2C_Write(20 * 6, 4, ns_string);

    OLED_I2C_Write(0, 5, "Longitude: ");
    OLED_I2C_Write(10 * 6, 5, longitude_string);
    OLED_I2C_Write(20 * 6, 5, ew_string);

    OLED_I2C_Write(0, 7, "Buffer: ");
    OLED_I2C_Write(8 * 6, 7, buffer_status_string);
    OLED_I2C_Write(120, 7, heartbeat ? "." : " ");
}

float calculate_distance(const float x[2], const float y[2])
{
    double sum = 0;
    sum += 2 * 6371 * 1000 * asin(sqrt(pow(sin((x[0] - y[0]) * (M_PI / 360)), 2) + cos(x[0] * (M_PI / 180)) * cos(y[0] * (M_PI / 180)) * pow(sin((y[1] - x[1]) * (M_PI / 360)), 2)));

#ifdef DEBUG
    UART_printf("\n++Change in distance\n", UART0);
    UART0_print_float(x[0]);
    UART0_print_float(x[1]);
    UART0_print_float(y[0]);
    UART0_print_float(y[1]);
    UART0_print_float(sum);
    UART_printf("\n++End Change in distance\n", UART0);
#endif

    return sum;
}
