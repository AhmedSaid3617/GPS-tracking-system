#include "gpio.h"
#include "tm4c123gh6pm.h"
int main(){
    int x;
    GPIO_init((unsigned long)GPIO_PORTF_DATA_BITS_R, 0x11, 0xE);
    GPIO_write_pin((unsigned long)GPIO_PORTF_DATA_BITS_R, 1, 1);
    x =	(int)GPIO_read_pin((unsigned long)GPIO_PORTF_DATA_BITS_R, 1);
    unsigned char button = 1;
	GPIOF_default_init();
	while(1){
	if (read_sw1() & read_sw2()){
		write_red_led(button);
	}
	else if(!read_sw1() & read_sw2()){
		write_blue_led(button);
	}
	else if (read_sw1() & !read_sw2()){
		write_green_led(button);
	}
}
}
