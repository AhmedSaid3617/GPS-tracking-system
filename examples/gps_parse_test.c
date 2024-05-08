#include "main.h"
#include <string.h>
#include <stddef.h>

gps_data_t data_point;
char *gps_input_buffer = "$GPGSA,A,3,18,29,28,05,25,12,,,,,,,3.04,1.36,2.72*0F\
$GPGSV,3,1,09,05,34$GPRMC,091126.00,A,3003.94682,N,03116.72624,E,0.548,,040524,,,A*72\
$GPVTG,,T,,M,0.548,N,1.014,K,A*2E\
$GPGGA,091126.00,3003.94682,N,03116.72624,E,1,06,1.36,70.7,M,15.4,M,,*62";

int main()
{
    
    
    UART0_Init(9600);
    //UART1_Init(9600);
    Systick_Init();
    Gps_Parse(gps_input_buffer, &data_point);
    while (1)
    {
        UART0_print_float(data_point.latitude);
        UART_SendByte(UART0, data_point.ns);
        UART0_print_float(data_point.longitude);
        UART_SendByte(UART0, data_point.ew);
        UART0_print_float(data_point.satellites);
        Systic_Delay_ms(500);
    }
}