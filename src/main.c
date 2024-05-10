#include "main.h"

enum State {IDLE = 1, RECORDING};

gps_data_t data_point;
char oledString[10] = "IDLE";
char latitude_string[10] = " ";
char longitude_string[10] = " ";
char gps_status_string[] = "Not valid";
//char satelites_string[10] = "0";
char distance[10] = "0.0";

char gps_input_buffer[500] ="1";
int mode = IDLE;

int main()
{
    UART0_Init(9600);
    UART1_Init(9600);
    GPIOF_default_init();
    I2C_Init();
    OLED_I2C_Init();
    Systick_Init();

    strcpy(gps_status_string, "STARTING"); 
    oled_display_data(); // Display STARTING message.

    while (gps_uart_fill_buffer(gps_input_buffer, UART1) < 100); // Wait until gps_input_buffer is filled for the first time.

    Systic_Delay_ms(300); // Insert hold time.
    Systick_Interrupt_Init(1000);

    while (1)
    {
        gps_uart_fill_buffer(gps_input_buffer, UART1);
        oled_display_data();
    }
}

void SysTick_Handler()
{
    if (mode == IDLE)
    {
        uint8_t data;
        if (UART_ReceiveByte(UART0, &data))
        { // read what in the UART and change the value in the data
            if (data == 'U')
            {
                read_coordinates(); // take the size of data saved in Epprom to iterate over Epprom
            }
        }
        if (read_sw1()){
            OLED_clear_display();
            mode = RECORDING; // change mode to 1 if switch is on
        }

        if (Gps_Parse(gps_input_buffer, &data_point)){
            strcpy(gps_status_string, "Valid    ");
        }
        else{
            strcpy(gps_status_string, "Not Valid ");
        }
        strcpy(oledString, "IDLE"); // changing the value Oled String
    }

    else if (mode == RECORDING)
    {
        if (Gps_Parse(gps_input_buffer, &data_point))
        {
            strcpy(gps_status_string, "Valid    ");
            float_to_string(data_point.latitude, latitude_string);
            float_to_string(data_point.longitude, longitude_string);
            //float_to_string(data_point.satellites, satelites_string);
            //OLED_clear_display();
            
        }
        strcpy(oledString, "RECORDING");
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
    OLED_I2C_Write(0, 0, oledString);
    OLED_I2C_Write(6*10, 0, gps_status_string);
    OLED_I2C_Write(0, 2, "Distance: 00000");
    OLED_I2C_Write(0, 4, "Latitude: ");
    OLED_I2C_Write(10*6, 4, latitude_string);
    OLED_I2C_Write(0, 6, "Longitude: ");
    OLED_I2C_Write(10*6, 6, longitude_string);
}
