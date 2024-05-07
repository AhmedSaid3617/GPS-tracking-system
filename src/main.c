#include "main.h"

int main()
{
    int i;
    uint8_t received;
    uint8_t array[100];
    uint8_t *array_pointer = &array[0];
    UART0_Init(9600);
    Systi_Init();
    while (1)
    {
        UART_SendByte(UART0, 'A');
        Systic_Delay_ms(1000);
    }

    return 1;
}