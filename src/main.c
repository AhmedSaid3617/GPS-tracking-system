#include "main.h"

float array[250];
int main()
{
    unsigned long i;
    unsigned char * volatile to_send = (unsigned char*)&i;
    char received[4];
    unsigned long * volatile to_receieve = (unsigned long *)&received;
    
    UART0_Init(9600);
    if (EEPROM_Init() != EEPROM_Init_Failed)
    {
        //EEPROM_Write(10, 71ul);
        while (1)
        {
            i = EEPROM_Read(10);
            UART_SendByte(UART0, *to_send);
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
unsigned long read_coordinates(void){
  unsigned long size=EEPROM_Read(0);
  for (int i=0 ;i<250;i++){ 
    unsigned long L=EEPROM_Read(i);
    float *F=(float *) &L;
    array[i]=*F;
    }
    return size;
}