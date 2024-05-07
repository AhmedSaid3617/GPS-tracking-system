#include "main.h"
#include <stdio.h>

//float array[250];
static char output_buffer[50];
int main()
{
  //unsigned long i;
  //unsigned char *volatile to_send = (unsigned char *)&i;
  UART0_Init(9600);
  // char received[4];
  // unsigned long * volatile to_receieve = (unsigned long *)&received;
  //double f = 3.5;
  
  sprintf(output_buffer, "float: %d",33);

  

  //float coordinates[2][2] = {{100.21, 25.5}, {300.5, 30.88}};
  //Save_float_EEPROM(coordinates, 2);
  //unsigned long size = EEPROM_Read(0);
 // EEPROM_Read(int address);
  while (1)
  {

      //UART_printf("output_buffer", UART0);
      //UART_SendByte(UART0,'A');
      // void UART_SendFloat( UART0, 3.5);
     for (int i = 0; i < 100000; i++)
      {
      
      }

    
    
  }
  

}

// unsigned long read_coordinates(void)
// {
//   unsigned long size=EEPROM_Read(0);
//   for (int i=0 ;i<250;i++){ 
//     unsigned long L=EEPROM_Read(i);
//     float *F=(float *) &L;
//     array[i]=*F;
//     }
//     return size;
// }
