#include "uart.h"
#include "Systic.h"


int main()
{
    int i;
    uint8_t received;
    uint8_t array[100];
    uint8_t *array_pointer = &array[0];
    UART0_Init(9600);
    Systick_Interrupt_Init();

    /* while (1)
    {
    } */

    return 1;
}

void SysTick_Handler(void){
    UART_SendByte(UART0, 'A');
}