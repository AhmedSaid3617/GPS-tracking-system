#include "main.h"

int main()
{
    unsigned long i;
    unsigned char * volatile c = (unsigned char*)&i;
    
    UART0_Init(9600);
    if (EEPROM_Init() != EEPROM_Init_Failed)
    {
        while (1)
        {
            EEPROM_Write(10, (unsigned long)'B');
            i = EEPROM_Read(10);
            
            UART_SendByte(UART0, *c);

            for (int i = 0; i < 100000; i++);
        }
    }
    else
    {
        while (1)
        {
            UART_SendByte(UART0, 'F');
            for (int i = 0; i < 100000; i++)
                ;
        }
        
    }
    
}