#ifndef _GPIO_H_

    #define _GPIO_H_
    
    // Like Lab 3
    // Initialize port F so that built-in switched are input, and built-in LEDs are output.
    void GPIOF_default_init();

    char read_sw1();
    char read_sw2();

    void write_red_led();
    void write_blue_led();
    void write_green_led();

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