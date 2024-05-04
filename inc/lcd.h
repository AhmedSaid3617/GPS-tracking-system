#ifndef C0_LCD_H
#define C0_LCD_H

#include "i2c.h"
#define LCD_1602_7_Bit_Address 0x27

//extern void delay(int);

void LCD_1602_I2C_Init();
void LCD_1602_I2C_Write(char * ptr);

#endif //C0_LCD_H
