#include "uart.h"

int main()
{

    UART0_Init(9600);

    while (1)
    {
        int i;
        UART0_SendChar('A');

        for (i = 0; i < 10000; i++)
        {
        }
    }

    return 1;
}