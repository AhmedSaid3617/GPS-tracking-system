#include "i2c.h"
#include "uart.h"

#define RCGCGPIO *((volatile unsigned long*) 0x400FE608)

#define GPIOB 0x40005000
#define GPIOAFSEL 0x420
#define GPIOODR 0x50C

void I2C_Init() {
    SYSCTL_RCGCI2C_R = SYSCTL_RCGCI2C_R0;
    SYSCTL_RCGCGPIO_R |= 0x2; // Enable clock to GPIOB

    GPIO_PORTB_ODR_R |= (1 << 3); // Ensure I2C SDA pin is configured open drain
    GPIO_PORTB_AFSEL_R |= (1 << 3) | 1 << 2;
    GPIO_PORTB_PUR_R |=  (1 << 3) | 1 << 2;
    GPIO_PORTB_DEN_R |= (1 << 3) | 1 << 2;
//    GPIO_PORTB_AMSEL_R &= ~(1 << 3 | 1 << 2);

    I2C0_MCR_R = 0x10; // Enable Master function mode
    I2C0_MTPR_R = 0x7; // Clock divider, SCL_PERIOD = 2 × (1 + TPR) × (SCL_LP + SCL_HP) × CLK_PRD
                // 2 × (1 + I2CMTPR) × (6 + 4) × 1/(SYSCLK)
}

static char current_address;

void I2C_Start(char address) {
    I2C0_MSA_R = address << 1 | 0;
    current_address = address;
}

void I2C0_Write_First_In_Sequence(int slave_address, char data) {
    I2C0_MSA_R = slave_address << 1;
    I2C0_MDR_R = data;
    I2C0_MCS_R = 3; // RUN, START
    while (I2C0_MCS_R & 1);
}

void I2C0_Write_Last_In_Sequence(int slave_address, char data) {
    I2C0_MSA_R = slave_address << 1;
    I2C0_MDR_R = data;
    I2C0_MCS_R = 5; // RUN, START
    while (I2C0_MCS_R & 1);
}

void I2C0_Write_Single(int slave_address, char data) {
    I2C0_MSA_R = slave_address << 1;
    I2C0_MDR_R = data;
    I2C0_MCS_R = 7; // RUN, START, STOP if bytes_count
    while (I2C0_MCS_R & 1);
}

void I2C0_Write_In_Sequence(char slave_address, char data) {
    I2C0_MSA_R = slave_address << 1;
    I2C0_MDR_R = data;
    I2C0_MCS_R = 1; // RUN
    while (I2C0_MCS_R & 1);
}

void I2C0_Write_Multiple(int slave_address, char* ptr, int bytes_count)
{
    if (bytes_count-- > 1) {
        I2C0_Write_First_In_Sequence(slave_address, *ptr++);
    } else {
        I2C0_Write_Single(slave_address, *ptr);
    }

    while (bytes_count-- > 1)
    {
        I2C0_Write_In_Sequence(slave_address, *ptr++);
    }

    I2C0_Write_Last_In_Sequence(slave_address, *ptr);
}

void I2C_Send(char data) {
//    I2C0_MSA_R = current_address << 1 | 0;

    while (I2C0_MCS_R & 1);

    I2C0_MDR_R = data;

    I2C0_MCS_R = 0x3; // this generates START, STOP so multibyte transaction is not utilized

    while (I2C0_MCS_R & 1);
}

void I2C_End() {
    I2C0_MCS_R = 0x4; // this generates START, STOP so multibyte transaction is not utilized
    // Left empty as a compatibility with OLED_I2C implementation on other microcontrollers
}
