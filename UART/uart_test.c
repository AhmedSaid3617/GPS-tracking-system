#include "uart.h"

int main()
{
    int i;
    UART0_Init(9600);
    while (1)
    {

        UART_SendByte(UART0, 'f');

        for (i = 0; i < 1000000; i++)
        {
        }
    }

    return 1;
}