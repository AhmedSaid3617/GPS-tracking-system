#ifndef UART_H
    #include <stdint.h>
    #include "tm4c123gh6pm.h"

    #define UART_H

    #define UART0 0x4000C000
    #define UART1 0x4000D000
    #define UART2 0x4000E000
    #define UART3 0x4000F000
    #define UART4 0x40010000
    #define UART5 0x40011000
    #define UART6 0x40012000
    #define UART7 0x40013000

//    #define ECHO_TO_UART0

    void UART0_Init(int Baud_rate);
    void UART1_Init(int Baud_rate);
    void UART2_Init(int Baud_rate);
    void UART7_Init(int Baud_rate);

    void UART_SendByte(uint32_t base, uint8_t data);
	void UART_SendFloat(uint32_t UART_base,float data_float);
    uint16_t UART_ReceiveByte(uint32_t UART_base, uint8_t *destination);

    void UART_printf(char *buffer, uint32_t UART_base);
    void UART0_print_float(float num);

#endif