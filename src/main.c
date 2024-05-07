#include "main.h"
#include <stdio.h>

float input_array[250][2] = {17.1234, 17.2345, 17.3456, 17.4567, 17.5678, 17.6789};
float output_array[500] = {0};


int main()
{ 
    UART0_Init(9600);
    EEPROM_Init();
    for (int i = 0; i < 1000; i++)
    {
        /* code */
    }
    
    Save_float_EEPROM(input_array, 3);
    //EEPROM_Write(1,1234);
    read_coordinates();
    //EEPROM_Write((0) + 1 , (unsigned long)(input_array[0][0]*10000.0));

    while (1)
    {
        UART_SendByte(UART0, '=');
        for (int i = 0; i < 6; i++)
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
    for (int i = 0; i < 500; i++)
    {
        float L = EEPROM_Read(i+1)/1000000.0;
        output_array[i] = L;
    }
    return size;
}