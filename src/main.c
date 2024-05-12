#include "main.h"

enum State
{
    IDLE = 1,
    RECORDING
};

gps_data_t data_point;
char mode_string[10] = "IDLE";
char latitude_string[10] = " ";
char ns[2] = " ";
char longitude_string[10] = " ";
char ew[2] = " ";
char gps_status_string[10] = " ";
char distance_string[15] = "0.0";

char gps_input_buffer[500] = "1";
float coordinates[RAM_MAX_COORDINATES][2] = {1};
unsigned long coordinates_num = 1;
float distance = 1;
int mode = IDLE;

float rad(float degree) {
    return (degree * M_PI) / 180;
}

float calculate_distance (float c1[2],float c2[2]){
    float x[2] = {c1[0], c2[0]};
    float y[2] = {c1[1], c2[1]};
    float sum = 0;
    sum += 2*6371*asin(sqrt(pow(sin((x[0]-y[0])*(M_PI/360)),2)+cos(x[0]*(M_PI/180))*cos(y[0]*(M_PI/180))*pow(sin((y[1]-x[1])*(M_PI/360)),2)));


    UART_printf("\n===========xxx=========\n", UART0);

    UART0_print_float(sum);
    UART_printf("\n=====xxxxxx===============\n", UART0);


    return sum;
}

int main()
{
    UART0_Init(9600);
    UART1_Init(9600);
    GPIOF_default_init();
    I2C_Init();
    OLED_I2C_Init();
    Systick_Init();
    EEPROM_Init();

    coordinates_num = 0;
    distance = 0;

    strcpy(gps_status_string, "STARTING");
    oled_display_data(); // Display STARTING message.

    while (gps_uart_fill_buffer(gps_input_buffer, UART1) < 50)
        ; // Wait until gps_input_buffer is filled for the first time.

    Systic_Delay_ms(300); // Insert hold time.
    Systick_Interrupt_Init(1000);

    while (1)
    {
        if (gps_uart_fill_buffer(gps_input_buffer, UART1) > 100)
        {
            UART_printf("\n====================\n", UART0);
            UART_printf(gps_input_buffer, UART0);
        }


        oled_display_data();
    }
}

void SysTick_Handler()
{
    if (mode == IDLE)
    {
        strcpy(mode_string, "IDLE     "); // changing the value Oled String
        uint8_t data;
        if (UART_ReceiveByte(UART0, &data))
        { // read what in the UART and change the value in the data
            if (data == 'U')
            {
                strcpy(mode_string, "READING"); // Display waiting message.
                OLED_clear_display();
                oled_display_data();
                EEPROM_read_coordniates(); // take the size of data saved in Epprom to iterate over Epprom
            }
        }
        if (read_sw1())
        {
            OLED_clear_display();
            mode = RECORDING; // change mode to 1 if switch is on
        }

        // TODO: REMOVE THIS
        if (read_sw2())
        {
            //EEPROM_read_coordniates();
        }

        if (Gps_Parse(gps_input_buffer, &data_point))
        {
            strcpy(gps_status_string, "Valid    ");
        }
        else
        {
            strcpy(gps_status_string, "Not Valid");
        }
    }

    else if (mode == RECORDING)
    {
        strcpy(mode_string, "RECORDING");
        if (Gps_Parse(gps_input_buffer, &data_point))
        {
            // Update displayed coordinates.
            strcpy(gps_status_string, "Valid    ");
            float_to_string(data_point.latitude, latitude_string);
            float_to_string(data_point.longitude, longitude_string);

            // OLED_clear_display();

            if (coordinates_num < 1000) // Condition to avoid writing out of bounds.
            {
                coordinates[coordinates_num][0] = data_point.latitude; // Save new point.
                coordinates[coordinates_num][1] = data_point.longitude;
                coordinates_num++;
                if (coordinates_num > 1) {
                    float delta = calculate_distance(coordinates[coordinates_num], coordinates[coordinates_num - 1]);
                    UART_printf("+++++++++++++++====", UART0);
                    UART0_print_float(delta);
                    if (delta > DISTANCE_THRESHOLD)
                        distance += delta;

                    float_to_string(distance, distance_string);
                }
            }


        }
        else
        {
            strcpy(gps_status_string, "Not Valid ");
            /* strcpy(latitude_string, "          ");
            strcpy(longitude_string, "          "); */
        }
        if (read_sw1())
        {
            strcpy(mode_string, "SAVING"); // Display waiting message.
            OLED_clear_display();
            oled_display_data();
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
}

void computer_upload_isr()
{
    // EEPROM_READ_ARRAY
}

void eeprom_upload_isr()
{
    // EEPROM_READ_ARRAY
}

void oled_display_data()
{
    OLED_I2C_Write(0, 0, mode_string);
    OLED_I2C_Write(6 * 10, 0, gps_status_string);

    OLED_I2C_Write(0, 2, "Distance: ");
    OLED_I2C_Write(10*5+4, 2, distance_string);

    OLED_I2C_Write(0, 4, "Latitude: ");
    OLED_I2C_Write(10 * 6, 4, latitude_string);
    OLED_I2C_Write(20 * 6, 4, ns);

    OLED_I2C_Write(0, 6, "Longitude: ");
    OLED_I2C_Write(10 * 6, 6, longitude_string);
    OLED_I2C_Write(20 * 6, 6, ew);
}
