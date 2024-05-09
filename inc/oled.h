#ifndef GPS_TRACKING_SYSTEM_OLED_H
#define GPS_TRACKING_SYSTEM_OLED_H

#include "i2c.h"
#include "fonts.h"

#define OLED_7Bit_ADDRESS 0x3C
#define CONTROL_BYTE 0x00
#define DATA_BYTE 0x40

void OLED_I2C_Init();
void OLED_I2C_Draw(const char * ptr, int length);
void OLED_I2C_Write(unsigned char col, unsigned char page, char * ptr);
void OLED_clear_display();

#endif //GPS_TRACKING_SYSTEM_OLED_H
