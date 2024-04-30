#include "i2c.h"

#define RCGCGPIO *((volatile unsigned long*) 0x400FE608)

#define GPIOB 0x40005000
#define GPIOAFSEL 0x420
#define GPIOODR 0x50C

void I2C_Init() {
    RCGCI2C->I2C0 = 1; // Enable clock to I2C0
    RCGCGPIO |= 0x2; // Enable clock to GPIOB
    *((volatile unsigned long*) (GPIOB + GPIOODR)) |= 1 << 3; // Ensure I2C SDA pin is configured open drain
    // Texas Instruments mentions that I2C0, connected to PB2, PB3 is already the default state for this GPIO

    I2CMCR->MFE = 1; // Enable Master function mode
    I2CMTPR = 7; // Clock divider, SCL_PERIOD = 2 × (1 + TPR) × (SCL_LP + SCL_HP) × CLK_PRD
                // 2 × (1 + I2CMTPR) × (6 + 4) × 1/(SYSCLK)
}

void I2C_Start(char address) {
    I2CMSA = address << 1 | 0;
}

void I2C_Send(char data) {
    I2CMDR = data;

    I2CMCS->write = 0x7; // this generates START, STOP so multibyte transaction is not utilized

    while (I2CMCS->BUSY);

    if (I2CMCS->ERROR) {
        while (1); // TODO: Error Handling
    }
}

void I2C_End() {
    // Left empty as a compatibility with OLED_I2C implementation on other microcontrollers
}
