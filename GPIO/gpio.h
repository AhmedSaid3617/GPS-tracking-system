#ifndef _GPIO_H_

#define _GPIO_H_
#define GPIO_PORTF_DATA_R (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R (*((volatile unsigned long *)0x4002552C))
#define PF4 (*((volatile unsigned long *)0x40025040))
#define PF3 (*((volatile unsigned long *)0x40025020))
#define PF2 (*((volatile unsigned long *)0x40025010))
#define PF1 (*((volatile unsigned long *)0x40025008))
#define PF0 (*((volatile unsigned long *)0x40025004))
#define GPIO_LOCK_KEY 0x4C4F434B // Unlocks the GPIO_CR register
#define SYSCTL_RCGCGPIO_R (*((volatile unsigned long *)0x400FE608))
#define SYSCTL_PRGPIO_R (*((volatile unsigned long *)0x400FEA08))
#define RED 0x02
#define BLUE 0x04
#define GREEN 0x08
#define PF123_mask 0x0E
#define PF04_mask 0x11
#define PF_mask 0x20
#define PF_SW1_mask 0x10
#define PF_SW2_mask 0x01
#define DIR_Offset 0x400
#define AFSEL_Offset 0x420
#define Lock_Offset 0x520
#define PUR_Offset 0x510
#define DEN_Offset 0x51C
#define CR_Offset 0x524
#define AMSEL_Offset 0x528
#define PCTL_Offset 0x52C
#define DATA_Offset 0x3FC

#define GPIOA 0x40004000
#define GPIOB 0x40005000
#define GPIOC 0x40006000
#define GPIOD 0x40007000
#define GPIOE 0x40024000
#define GPIOF 0x40025000

// Initialize port F so that built-in switched are input, and built-in LEDs are output.
void GPIOF_default_init();

// return data & mask
unsigned char read_sw1();
unsigned char read_sw2();

// if value 0 turnoff else turn on
void write_red_led(unsigned char value);
void write_blue_led(unsigned char value);
void write_green_led(unsigned char value);

// General purpose initialize for any port
// GPIOPort is the base address of the port to be initialized
// input_config is the mask for pins which the user wants to set as input.
// output_config is the mask for pins which the user wants to set as output.
void GPIO_init(unsigned long GPIOPort, char input_config, char output_config);

// Read and return the value of a pin in the specified port.
// pin_num is the number of the pin to be read.
char GPIO_read_pin(unsigned long GPIOPort, char pin_num);

// Write the value of a pin in the specified port.
// pin_num is the number of the pin to be written.
// value is the value to be written on the pin.
void GPIO_write_pin(unsigned long GPIOPort, char pin_num, char value);

#endif