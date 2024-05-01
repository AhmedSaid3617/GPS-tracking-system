#include "main.h"

#define MAX_COORDINATES 1000
#define GPS_BUFFER_SIZE 500

float coordinates[MAX_COORDINATES][2] = {};
float (*coordinates_ptr)[2] = coordinates;
float total_distance = 0;
char buffer[GPS_BUFFER_SIZE];

int main()
{
    while (1)
    {
        // Uart_fill_buffer

        // GPS_parse_and_push

        // calculate_total_distance();

        // display oled

        // 
    }
    
    return 1;
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
