#include "uart.h"

int main()
{
    int i;
    uint8_t received;
    uint8_t array[100];
    uint8_t* array_pointer = &array[0];
    UART1_Init(9600);
    while (1)
    {
        // Try to receive a byte and store it in the array.
        if(UART_ReceiveByte(UART1, array_pointer)){
            // If a byte is received, send it and increment the pointer.
            UART_SendByte(UART1, *array_pointer);
            array_pointer++;
        }

    }

    return 1;
}