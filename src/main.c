#include "main.h"
#include <string.h>
#include <stddef.h>

int main()
{

    UART0_Init(9600);
    UART1_Init(9600);
    Systick_Init();
    const char *rmc = "$GPRMC"; // To get speed and so
    const char *gga = "$GPGGA"; // To get satellite count
    char inputBuffer[500] = {};
    char output_buffer[100]={};
    char *rmc_ptr = NULL;
    char *gga_ptr = NULL;
    float coordinates[COORDINATES_SIZE][2];
    float(*coordinates_ptr)[2] = coordinates;
    while (1)
    {
        if (gps_uart_fill_buffer(inputBuffer, UART1) > 100)
        {
            gps_uart_send_buffer(inputBuffer, UART0);
        }

        //UART_SendByte(UART0, 'A');
        
       // Systic_Delay_ms(500);
        
    }
}

void SysTick_Handler(void){
    UART_SendByte(UART0, 'A');
}