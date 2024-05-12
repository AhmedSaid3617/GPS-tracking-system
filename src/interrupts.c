#include "tm4c123gh6pm.h"
#include <stdint.h>

void UART0_interrupt_init(){
/* SYSCTL_RCGCUART_R|=0x0001;
UART0_CTL_R&=~0X0001;
UART0_IBRD_R =0x68;
UART0_FBRD_R =0xB;
UART0_LCRH_R =0x0070;
UART0_CTL_R=0x0301; */
UART0_ICR_R |= 0x10;
UART0_IM_R|=0x10;
NVIC_PRI1_R|=(1<<14); // Priority 2
NVIC_EN0_R|=(1<<6);
}