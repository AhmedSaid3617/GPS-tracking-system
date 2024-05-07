#include "main.h"
#include <string.h>
#include <stddef.h>

int main()
{
    gps_data_t data_point;
    char *gps_input_buffer = "$GPGSA,A,3,18,29,28,05,25,26,12,,,,,,2.33,1.12,2.04*09\
    $GPGSV,3,1,09,05,$GPRMC,091124.00,A,3003.94740,N,03116.72766,E,0.716,,040524,,,A*71\
    $GPVTG,,T,,M,0.716,N,1.325,K,A*26\
    $GPGGA,091124.00,3003.94740,N,03116.72766,E,1,06,1.36,71.0,M,15.4,M,,*6E\
    $GPGSA,A,3,18,29,28,05,25,12,,,,,,,3.04,1.36,2.72*0F\
    $GPGSV,3,1,09,05,34$GPRMC,091125.00,A,3003.94705,N,03116.72688,E,0.295,,040524,,,A*7E\
    $GPVTG,,T,,M,0.295,N,0.546,K,A*2A\
    $GPGGA,091125.00,3003.94705,N,03116.72688,E,1,06,1.36,70.8,M,15.4,M,,*66";
    UART0_Init(9600);
    UART1_Init(9600);
    Systick_Init();

    while (1)
    {
        
    }
}

void SysTick_Handler(void)
{
    UART_SendByte(UART0, 'A');
}