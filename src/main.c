#include "main.h"

#define MAX_COORDINATES 1000
#define GPS_BUFFER_SIZE 500

float coordinates[MAX_COORDINATES][2] = {};
float (*coordinates_ptr)[2] = coordinates;
float total_distance = 0;

char buffer[GPS_BUFFER_SIZE];
int mode=0;
char oledString[100];
char led = 0;


int main()
{
    while (1)
    {

        // Uart_fill_buffer

        // GPS_parse_and_push

        // calculate_total_distance();

        // display oled

        //
        GPIO_write_pin(GpioF, led, 1);
    }



    return 1;
}
void SysTick_Handler(){
    if (mode==0){
        uint8_t data;
        if (UART_ReceiveByte(UART_BASE, &data)) {  // read what in the UART and change the value in the data
           if (data == 'U') {
            unsigned long size=read_coordinates();  // take the size of data saved in Epprom to iterate over Epprom

            led = 2;
            strcpy(oledString, "IDLE"); // changing the value Oled String
            }}
        if (read_sw1())
            mode=1; // change mode to 1 if switch is on


    }


}

//
void calculate_total_distance(){

}

void computer_upload_isr(){
    // EEPROM_READ_ARRAY
}

void eeprom_upload_isr(){
    // EEPROM_READ_ARRAY
}

