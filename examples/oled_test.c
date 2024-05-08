#include <stdio.h>
#include "main.h"
static char buff[200];

int main() {
    double decimal = 1.3445;
    I2C_Init();
    OLED_I2C_Init();
    OLED_I2C_Write(0,0,"Test");
    sprintf(buff, "Latitude: %d.%d", (int) decimal, (int)((decimal - (int) decimal) * 10000));
    OLED_I2C_Write(0,0,buff);
}