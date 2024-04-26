#include "tm4c123gh6pm.h"
#include "gpio.h"

void Clock_Enable(unsigned long GPIOPort)
{
    // Enable the clock for the port
    if (GPIOPort == (unsigned long)GPIO_PORTA_DATA_BITS_R)
    {
        SYSCTL_RCGCGPIO_R |= 0x01;
        while ((SYSCTL_PRGPIO_R & 0x01) == 0)
            ;
    }
    else if (GPIOPort == (unsigned long)GPIO_PORTB_DATA_BITS_R)
    {
        SYSCTL_RCGCGPIO_R |= 0x02;
        while ((SYSCTL_PRGPIO_R & 0x02) == 0)
            ;
    }
    else if (GPIOPort == (unsigned long)GPIO_PORTC_DATA_BITS_R)
    {
        SYSCTL_RCGCGPIO_R |= 0x04;
        while ((SYSCTL_PRGPIO_R & 0x04) == 0)
            ;
    }
    else if (GPIOPort == (unsigned long)GPIO_PORTD_DATA_BITS_R)
    {
        SYSCTL_RCGCGPIO_R |= 0x08;
        while ((SYSCTL_PRGPIO_R & 0x08) == 0)
            ;
    }
    else if (GPIOPort == (unsigned long)GPIO_PORTE_DATA_BITS_R)
    {
        SYSCTL_RCGCGPIO_R |= 0x10;
        while ((SYSCTL_PRGPIO_R & 0x10) == 0)
            ;
    }
    else if (GPIOPort == (unsigned long)GPIO_PORTF_DATA_BITS_R)
    {
        SYSCTL_RCGCGPIO_R |= 0x20;
        while ((SYSCTL_PRGPIO_R & 0x20) == 0)
            ;
    }
    else
    {
        return;
    }
}

void GPIO_init(unsigned long GPIOPort, char input_config, char output_config)
{

    // variable declaration
    unsigned long *GPIO_LOCK = (unsigned long *)(GPIOPort + Lock_Offset);
    unsigned long *GPIO_CR = (unsigned long *)(GPIOPort + CR_Offset);
    unsigned long *GPIO_DIR = (unsigned long *)(GPIOPort + DIR_Offset);
    unsigned long *GPIO_DEN = (unsigned long *)(GPIOPort + DEN_Offset);
    unsigned long *GPIO_AFSEL = (unsigned long *)(GPIOPort + AFSEL_Offset);
    unsigned long *GPIO_AMSEL = (unsigned long *)(GPIOPort + AMSEL_Offset);
    unsigned long *GPIO_PCTL = (unsigned long *)(GPIOPort + PCTL_Offset);
    unsigned long *GPIO_PUR = (unsigned long *)(GPIOPort + PUR_Offset);

    // Enable the clock for the port
    Clock_Enable(GPIOPort);

    // Unlock the port and commit the changes
    *GPIO_LOCK = GPIO_LOCK_KEY;
    *GPIO_CR |= input_config | output_config;

    // Set the direction of the pins
    *GPIO_DIR |= output_config;

    // Set the digital enable of the pins
    *GPIO_DEN |= input_config | output_config;

    // Set the alternate function select, analog mode select and port control of the pins
    *GPIO_AFSEL = 0;           // clear the alternate function select of the GPIO port pins
    *GPIO_AMSEL = 0;           // clear the analog mode select of the GPIO port pins
    *GPIO_PCTL = 0;            // use the port for GPIO
    *GPIO_PUR |= input_config; // set the pull up resistor
}

char GPIO_read_pin(unsigned long GPIOPort, char pin_num)
{
    // variable declaration
    unsigned long *GPIO_DATA = (unsigned long *)(GPIOPort + DATA_Offset);

    // Read the value of the pin
    return (*(GPIO_DATA) >> pin_num) & 1;
}

void GPIO_write_pin(unsigned long GPIOPort, char pin_num, char value)
{
    // variable declaration
    unsigned long *GPIO_DATA = (unsigned long *)(GPIOPort + DATA_Offset);

    // write the value on the pin
    switch (value)
    {
    case 0:
        *GPIO_DATA &= ~(1 << pin_num);
        break;
    case 1:
        *GPIO_DATA |= (1 << pin_num);
        break;
    }
}

void GPIOF_default_init(void)
{
    
    GPIO_init(GPIOF, 0x11, 0xE);

}
unsigned char read_sw1(void)
{
    return (~GPIO_PORTF_DATA_R) & PF_SW1_mask;
}
unsigned char read_sw2(void)
{
    return (~GPIO_PORTF_DATA_R) & PF_SW2_mask;
}

// if value 0 turnoff else turn on
void write_red_led(unsigned char value)
{
    if (value == 0)
        GPIO_PORTF_DATA_R &= ~RED;
    else
        GPIO_PORTF_DATA_R |= RED;
}
void write_blue_led(unsigned char value)
{
    if (value == 0)
        GPIO_PORTF_DATA_R &= ~BLUE;
    else
        GPIO_PORTF_DATA_R |= BLUE;
}
void write_green_led(unsigned char value)
{
    if (value == 0)
        GPIO_PORTF_DATA_R &= ~GREEN;
    else
        GPIO_PORTF_DATA_R |= GREEN;
}
