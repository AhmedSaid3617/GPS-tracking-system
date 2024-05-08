#include "oled.h"

void OLED_I2C_Init() {
    char d1[10] = {CONTROL_BYTE, 0xAE, 0xD5, 0xF0, 0xA8, 64 - 1, 0x8D, 0x14, 0xAF, 0xA4};
    I2C0_Write_Multiple(OLED_7Bit_ADDRESS, d1, 10);

    char d2[3] = {CONTROL_BYTE, 0x20, 0x00};
    I2C0_Write_Multiple(OLED_7Bit_ADDRESS, d2, 3);

    // TODO: clear display, uses old API
    I2C0_Write_First_In_Sequence(OLED_7Bit_ADDRESS, DATA_BYTE);
    for (int i = 0; i < 1023; i++) {
        I2C0_Write_In_Sequence(OLED_7Bit_ADDRESS, 0);
    }
    I2C0_Write_Last_In_Sequence(OLED_7Bit_ADDRESS, 0);
}

// TODO: draw bitmap on display, uses old API
//void OLED_I2C_Draw(const char * ptr, int length) {
//    I2C_Start(OLED_7Bit_ADDRESS);
//    I2C_Send(CONTROL_BYTE);
//    I2C_Send(0x21);
//    I2C_Send(0);
//    I2C_Send(127);
//    I2C_Send(0x22);
//    I2C_Send(0);
//    I2C_Send(7);
//    I2C_End();
//
//    I2C_Start(OLED_7Bit_ADDRESS);
//    I2C_Send(DATA_BYTE);
//    for (int i = 0; i < length; i++) {
//        I2C_Send(*(ptr + i));
//    }
//    I2C_End();
//}

void OLED_I2C_Write(unsigned char col, unsigned char page, char * ptr) {
    char d[7] = {CONTROL_BYTE,0x21, col, 127, 0x22, page, 7};
    I2C0_Write_Multiple(OLED_7Bit_ADDRESS, d, 7);

    I2C0_Write_First_In_Sequence(OLED_7Bit_ADDRESS, DATA_BYTE);

    while (*ptr) {
        I2C0_Write_In_Sequence(OLED_7Bit_ADDRESS, font5x7[*ptr][0]);
        I2C0_Write_In_Sequence(OLED_7Bit_ADDRESS, font5x7[*ptr][1]);
        I2C0_Write_In_Sequence(OLED_7Bit_ADDRESS, font5x7[*ptr][2]);
        I2C0_Write_In_Sequence(OLED_7Bit_ADDRESS, font5x7[*ptr][3]);
        I2C0_Write_In_Sequence(OLED_7Bit_ADDRESS, font5x7[*ptr][4]);
        if (*(ptr + 1))
            I2C0_Write_In_Sequence(OLED_7Bit_ADDRESS, 0);

        ptr++;
    }

    I2C0_Write_Last_In_Sequence(OLED_7Bit_ADDRESS, 0);
}