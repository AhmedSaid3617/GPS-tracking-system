#ifndef _UART_H_
    #include <stdint.h>

    #define _UART_H_

    #define UART0 0x4000C000
    #define UART1 0x4000D000
    #define UART2 0x4000E000
    #define UART3 0x4000F000
    #define UART4 0x40010000
    #define UART5 0x40011000
    #define UART6 0x40012000
    #define UART7 0x40013000

    void UART0_Init(int Baud_rate);
    void UART1_Init(int Baud_rate);
    void UART2_Init(int Baud_rate);

    void UART_SendByte(uint32_t base, uint8_t data);
    uint8_t UART_ReceiveByte(uint32_t base);

    char UART0_GetChar(void) ;
    char UART1_GetChar(void);

    

#endif
