#include "main.h"

<<<<<<< HEAD
int main() {
    
=======
int main()
{
    int i;
    uint8_t received;
    uint8_t array[100];
    uint8_t *array_pointer = &array[0];
    UART1_Init(9600);
    while (1)
    {
        // UART_SendByte(UART1, 'S');

        // Try to receive a byte and store it in the array.
        if (UART_ReceiveByte(UART1, &received))
        {
            for (i = 0; i < 100000; i++)
            {
                /* code */
            }
            UART_SendByte(UART1, received);
        }
    }

    return 1;
>>>>>>> UART_gcc_test
}