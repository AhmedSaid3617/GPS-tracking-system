#include "lcd.h"
#define LCD_1602_EN (1 << 2)
#define LCD_1602_RS (1 << 0)


/*
 * 8-bit commands split up onto two nibbles and latched using a falling edge pulse on E pin
 * */
void LCD_1602_I2C_Send_Nibble(char nibble) {
    I2C0_Write_Single(LCD_1602_7_Bit_Address, nibble | LCD_1602_EN);

    // sketchy 5ms delay
    for(int i = 0; i < 50000; i++);

    I2C0_Write_Single(LCD_1602_7_Bit_Address, nibble & ~LCD_1602_EN);

    // sketchy 5ms delay
    for(int i = 0; i < 50000; i++);
}

void LCD_1602_I2C_Send_Command(char byte) {
    LCD_1602_I2C_Send_Nibble(byte & 0xF0);
    LCD_1602_I2C_Send_Nibble((byte << 4) & 0xF0 );
}

void LCD_1602_I2C_Send_Data(char byte) {
    LCD_1602_I2C_Send_Nibble(LCD_1602_RS | (byte & 0xF0));
    LCD_1602_I2C_Send_Nibble(LCD_1602_RS | ((byte << 4) &  0xF0));
}


void LCD_1602_I2C_Init() {
    LCD_1602_I2C_Send_Command(0x03);  // Initialize in 8-bit mode
    LCD_1602_I2C_Send_Command(0x03);  // Initialize in 8-bit mode
    LCD_1602_I2C_Send_Command(0x03);  // Initialize in 8-bit mode
    LCD_1602_I2C_Send_Command(0x02);  // Initialize in 4-bit mode
    LCD_1602_I2C_Send_Command(0x20);  // set to 28 to enable multiline
    LCD_1602_I2C_Send_Command(0x00);  // Display off
    LCD_1602_I2C_Send_Command(0x08);  // Display off
    LCD_1602_I2C_Send_Command(0x00);  // Clear display
    LCD_1602_I2C_Send_Command(0x01);  // Clear display
    LCD_1602_I2C_Send_Command(0x06);  // Entry mode set: Increment cursor, No display shift
    LCD_1602_I2C_Send_Command(0x0E);  // Display on, Cursor off, Blink off
}

void LCD_1602_I2C_Write(char * ptr) {
    LCD_1602_I2C_Send_Command(0x01);  // Clear display

    while (*ptr) {
        LCD_1602_I2C_Send_Data(*ptr++);
    }

    LCD_1602_I2C_Send_Command(0x10);  // Moves Cursor
    I2C0_Write_Single(LCD_1602_7_Bit_Address, 1 << 3);
}
