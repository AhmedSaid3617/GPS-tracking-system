#include "main.h"
#include <stdio.h>

float input_array[250][2] = {56.1234, 56.2345, 56.3456, 56.4567, 56.5678, 56.6789, 56.3456, 56.1234};
float output_array[500] = {0};


int main()
{ 
    UART0_Init(9600);
    EEPROM_Init();
    for (int i = 0; i < 1000; i++)
    {
        /* code */
    }
    
    Save_float_EEPROM(input_array, 4);
    //EEPROM_Write(1,1234);
    
    //EEPROM_Write((0) + 1 , (unsigned long)(input_array[0][0]*10000.0));

    while (1)
    {
        UART_printf("===============\n", UART0);
        read_coordinates();
        //UART0_print_float(EEPROM_Read(1));
        for (int i = 0; i < 1000000; i++)
        {
        }
    }
}

