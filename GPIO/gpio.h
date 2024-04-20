#ifndef _GPIO_H_

    #define _GPIO_H_
		#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
		#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
		#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
		#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
		#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
		#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
		#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
		#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
		#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
		#define PF4                     (*((volatile unsigned long *)0x40025040))
		#define PF3                     (*((volatile unsigned long *)0x40025020))
		#define PF2                     (*((volatile unsigned long *)0x40025010))
		#define PF1                     (*((volatile unsigned long *)0x40025008))
		#define PF0                     (*((volatile unsigned long *)0x40025004))
		#define GPIO_LOCK_KEY           0x4C4F434B  // Unlocks the GPIO_CR register
		#define SYSCTL_RCGCGPIO_R       (*((volatile unsigned long *)0x400FE608))
		#define SYSCTL_PRGPIO_R         (*((volatile unsigned long *)0x400FEA08))
		#define RED       0x02
		#define BLUE      0x04
		#define GREEN     0x08
		#define PF123_mask             0x0E
		#define PF04_mask               0x11
		#define PF_mask                0x20
		#define PF_SW1_mask            0x10
		#define PF_SW2_mask 
    
    // Like Lab 3
    // Initialize port F so that built-in switched are input, and built-in LEDs are output.
    void GPIOF_default_init();
    //return data & mask
    char read_sw1();
    char read_sw2();
    // if value 0 turnoff else turn on
    void write_red_led(char value);   
    void write_blue_led(char value);
    void write_green_led(char value);

    // General purpose initialize port E.
    // input_config is the mask for pins which the user wants to set as input.
    // output_config is the mask for pins which the user wants to set as output.
    void GPIOE_init(char input_config, char output_config);

    // Read and return the value of a pin in port E.
    // pin_num is the number of the pin to be read.
    char GPIOE_read_pin(char pin_num);

    // Write and return the value of a pin in port E.
    // pin_num is the number of the pin to be write.
    void GPIOE_write_pin(char pin_num);


#endif