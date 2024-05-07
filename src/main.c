#include "main.h"

#define MAX_COORDINATES 1000
#define GPS_BUFFER_SIZE 500

float coordinates[MAX_COORDINATES][2] = {};
float (*coordinates_ptr)[2] = coordinates;
float total_distance = 0;
char buffer[GPS_BUFFER_SIZE];
char oled_string[100];
int mode = 0;

int main()
{
    while (1)
    {
        // gps fill buffer.
        // gpio led.
        // oled display.
    }
    
    return 1;
}

// Systick handler
// if mode == 0
    //
    // if u:
        // eeprom_read
    // led = red
    // oled_string = IDLE
    // If gpio_sw1_read
        // mode = 1



void calculate_total_distance(){

}

void computer_upload_isr(){
    // EEPROM_READ_ARRAY
}

void eeprom_upload_isr(){
    // EEPROM_READ_ARRAY
}
