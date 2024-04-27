#include "main.h"

int main() {
    //GPS_Start();
    uint8_t received;
    UART0_Init(9600);
    UART1_Init(9600);
    char buffer[500];

    while (1)
    {
        if(gps_uart_fill_buffer(buffer, UART1) > 100){
            gps_uart_send_buffer(buffer, UART0);
        }
        for (int i = 0; i < 10000000; i++);
    }
}