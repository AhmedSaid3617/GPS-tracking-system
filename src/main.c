#include "main.h"

gps_data_t data_point;
char latitude_string[10] = "NaN";
char longitude_string[10] = "NaN";
char gps_status[10] = "Not valid";
char satelites_string[10] = "0";
unsigned int ticks = 0;

char gps_input_buffer[500] = {1};
int mode = 0;
char oledString[100];
char led = 0;

int main()
{

    UART0_Init(9600);
    UART1_Init(9600);
    I2C_Init();
    OLED_I2C_Init();
    // Systick_Interrupt_Init(100);

    OLED_I2C_Write(0, 0, gps_status);
    OLED_I2C_Write(0, 2, longitude_string);
    OLED_I2C_Write(0, 4, latitude_string);

    while (1)
    {
        if (gps_uart_fill_buffer(gps_input_buffer, UART1) > 200)
        {
            gps_uart_send_buffer(gps_input_buffer, UART0);
            if (Gps_Parse(gps_input_buffer, &data_point))
            {
                strncpy(gps_status, "Valid    ", 10);
                float_to_string(data_point.latitude, latitude_string);
                float_to_string(data_point.longitude, longitude_string);
                float_to_string(data_point.satellites, satelites_string);
                OLED_I2C_Write(0, 0, gps_status);
                OLED_I2C_Write(0, 2, longitude_string);
                OLED_I2C_Write(0, 4, latitude_string);
                OLED_I2C_Write(0, 6, satelites_string);
            }
        }
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
                unsigned long size = read_coordinates(); // take the size of data saved in Epprom to iterate over Epprom

            }
        }
        if (read_sw1())
            mode = 1; // change mode to 1 if switch is on
        
        led = 2;
        strcpy(oledString, "IDLE"); // changing the value Oled String
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
