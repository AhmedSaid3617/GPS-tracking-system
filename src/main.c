#include "main.h"

gps_data_t data_point;
char oledString[10] = {1};
char latitude_string[10] = "NaN";
char longitude_string[10] = "NaN";
char gps_status[10] = "Not valid";
char satelites_string[10] = "0";
//unsigned int ticks = 0;

char gps_input_buffer[500] = {1};
int mode = 2;
char led = 0x10000;

int main()
{

    UART0_Init(9600);
    UART1_Init(9600);
    GPIOF_default_init();
    // write_green_led(0);
    I2C_Init();
    OLED_I2C_Init();
    //Systick_Interrupt_Init(1000);
    mode = 0;

    while (1)
    {
        gps_uart_fill_buffer(gps_input_buffer, UART1);
        UART_printf(gps_input_buffer, UART0);
        UART_printf("\n====================\n", UART0);
        OLED_I2C_Write(0, 0, oledString);
        OLED_I2C_Write(0, 2, gps_status);
        OLED_I2C_Write(0, 4, longitude_string);
        OLED_I2C_Write(0, 6, latitude_string);
        OLED_I2C_Write(0, 8, satelites_string);

        GPIO_write_pin(GPIOF, led, 1);
    }
}

void SysTick_Handler()
{
    if (mode == 0)
    {
        uint8_t data;
        if (UART_ReceiveByte(UART0, &data))
        { // read what in the UART and change the value in the data
            if (data == 'U')
            {
                read_coordinates(); // take the size of data saved in Epprom to iterate over Epprom
            }
        }
        if (read_sw1())
            mode = 1; // change mode to 1 if switch is on

        led = RED;
        strcpy(oledString, "IDLE"); // changing the value Oled String
    }

    else if (mode == 1)
    {
        if (Gps_Parse(gps_input_buffer, &data_point))
        {
            strncpy(gps_status, "Valid    ", 10);
            float_to_string(data_point.latitude, latitude_string);
            float_to_string(data_point.longitude, longitude_string);
            float_to_string(data_point.satellites, satelites_string);
            OLED_clear_display();
        }
    }
}

//
void calculate_total_distance()
{
}

void computer_upload_isr()
{
    // EEPROM_READ_ARRAY
}

void eeprom_upload_isr()
{
    // EEPROM_READ_ARRAY
}
