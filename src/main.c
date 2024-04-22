#include "main.h"

int main()
{
    int i;
    uint8_t received;
    uint8_t array[100];
    uint8_t *array_pointer = &array[0];
    UART7_Init(9600);
    while (1)
    {
        // Try to receive a byte and store it in the array.
        UART_SendByte(UART7, 'A');
        for (i = 0; i < 100000; i++)
        {
            /* code */
        }
        
    }

    return 1;
}