#include "oled.h"

void OLED_I2C_Init() {
    I2C_Start(OLED_7Bit_ADDRESS);
    I2C_Send(CONTROL_BYTE);
    I2C_Send(0xAE);
    I2C_Send(0xD5);
    I2C_Send(0xF0);
    I2C_Send(0xA8);
    I2C_Send(64 - 1);
    I2C_Send(0x8D);
    I2C_Send(0x14);
    I2C_Send(0xAF);
    I2C_Send(0xA4);
    I2C_End();

    I2C_Start(OLED_7Bit_ADDRESS);
    I2C_Send(CONTROL_BYTE);
    I2C_Send(0x20);
    I2C_Send(0x00);
    I2C_End();

    I2C_Start(OLED_7Bit_ADDRESS);
    I2C_Send(DATA_BYTE);
    for (int i = 0; i < 1024; i++) {
        I2C_Send(0);
    }
    I2C_End();
}

void OLED_I2C_Draw(const char * ptr, int length) {
    I2C_Start(OLED_7Bit_ADDRESS);
    I2C_Send(CONTROL_BYTE);
    I2C_Send(0x21);
    I2C_Send(0);
    I2C_Send(127);
    I2C_Send(0x22);
    I2C_Send(0);
    I2C_Send(7);
    I2C_End();

    I2C_Start(OLED_7Bit_ADDRESS);
    I2C_Send(DATA_BYTE);
    for (int i = 0; i < length; i++) {
        I2C_Send(*(ptr + i));
    }
    I2C_End();
}

void OLED_I2C_Write(unsigned char col, unsigned char page, char * ptr) {
    I2C_Start(OLED_7Bit_ADDRESS);
    I2C_Send(CONTROL_BYTE);
    I2C_Send(0x21);
    I2C_Send(col);
    I2C_Send(127);
    I2C_Send(0x22);
    I2C_Send(page);
    I2C_Send(7);
    I2C_End();

    I2C_Start(OLED_7Bit_ADDRESS);
    I2C_Send(DATA_BYTE);

    while (*ptr) {
        I2C_Send(font5x7[*ptr][0]);
        I2C_Send(font5x7[*ptr][1]);
        I2C_Send(font5x7[*ptr][2]);
        I2C_Send(font5x7[*ptr][3]);
        I2C_Send(font5x7[*ptr][4]);
        if (*(ptr + 1))
            I2C_Send(0);

        ptr++;
    }

    I2C_End();
}