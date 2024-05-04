#include <stdio.h>
#include "main.h"
static char buff[200];

int main() {
    double decimal = 1.3445;
    I2C_Init();
    LCD_1602_I2C_Init();

    LCD_1602_I2C_Write("Example");
}