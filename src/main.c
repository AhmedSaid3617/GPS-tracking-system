#include "main.h"

int main() {
    UART0_Init(9600);
    UART_SendByte(UART0, 'A');
    I2C_Init();
//    OLED_I2C_Init();
//    OLED_I2C_Write(0, 0, "Hi");

    char data[3] = {0xAA, 0xAA, 0xAA};
    char *ptr = data;

    I2C0_Write_Multiple(0x3C, data, 3);

//    while(1) {
//        for(int i = 0; i < 10000; ++i);
//        I2C_Start(0x3C);
//        I2C_Send(0xAA);
//        I2C_Send(0xAA);
//        I2C_End();
//    }
}