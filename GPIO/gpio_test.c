#include "gpio.h"
#include "tm4c123gh6pm.h"
int main(){
    int x;
    GPIO_init((unsigned long)GPIO_PORTF_DATA_BITS_R, 0x11, 0xE);
    GPIO_write_pin((unsigned long)GPIO_PORTF_DATA_BITS_R, 1, 1);
    x =	(int)GPIO_read_pin((unsigned long)GPIO_PORTF_DATA_BITS_R, 1);
}