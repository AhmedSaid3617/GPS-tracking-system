#include "main.h"
#include <stdio.h>

float input_array[250][2] = {99.4598, 99.6712, 99.7456, 99.1234};
float output_array[500] = {0};


int main()
{ 
    UART0_Init(9600);
    EEPROM_Init();
    //Save_float_EEPROM(input_array, 2);
    //EEPROM_Write(1,1234);
    read_coordinates();
    //EEPROM_Write((0) + 1 , (unsigned long)(input_array[0][0]*10000.0));

    while (1)
    {
        
        for (int i = 0; i < 5; i++)
        {
            UART0_print_float(output_array[i]);
        }
        
        
        
        for (int i = 0; i < 100000; i++)
        {
        }
    }
}

unsigned long read_coordinates(void)
{
    unsigned long size = EEPROM_Read(0);
    for (int i = 0; i < 250; i++)
    {
        float L = EEPROM_Read(i)/10000.0;
        output_array[i] = L;
    }
    return size;
}