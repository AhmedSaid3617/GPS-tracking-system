#include "main.h"
#include <math.h>

#define MAX_COORDINATES 1000
#define GPS_BUFFER_SIZE 500

float coordinates[MAX_COORDINATES][2] = {};
float (*coordinates_ptr)[2] = coordinates;
float total_distance = 0;
char buffer[GPS_BUFFER_SIZE];

int main()
{
    float x[5][2] = {{45,100},{45,120},{40,130},{30,140},{30,160}};
    calculate_total_distance (x, 5);

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
void calculate_total_distance (float x[][2],int size){
    float sum = 0;
    for (int i = 0; i < size - 1; i++){
        sum += 2*6371*asin(sqrt(pow(sin((x[i+1][0]-x[i][0])*(M_PI/360)),2)+cos(x[i][0]*(M_PI/180))*cos(x[i+1][0]*(M_PI/180))*pow(sin((x[i+1][1]-x[i][1])*(M_PI/360)),2)));
    }
    printf("%.6f", sum);
}

void computer_upload_isr(){
    // EEPROM_READ_ARRAY
}

void eeprom_upload_isr(){
    // EEPROM_READ_ARRAY
}
