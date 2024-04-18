#include"uart.h"

#define SYSTEM_CLCK 80000000
void UART0_Init(int Baud_rate)
{
   // Enable the clock for UART0
  SYSCTL_RCGCUART_R |= 0x01;  // Set bit 0 for UART0

  // Enable clock for GPIO Port A
  SYSCTL_RCGCGPIO_R |= 0x01;  // Set bit 0 for GPIO Port A

  // Wait for the clocks to be ready
  while ((SYSCTL_PRGPIO_R & 0x01) == 0) {}  // Check bit 0 for Port A
  while ((SYSCTL_PRUART_R & (0x01)) == 0) {}  // Check bit 0 for UART0

  // Configure PA0 (RX) and PA1 (TX) as UART pins
  GPIO_PORTA_AFSEL_R |= (1 << 0) | (1 << 1);   // Set RX and TX to alternate function
  GPIO_PORTA_PCTL_R &= ~((GPIO_PORTA_PCTL_R & (0xF << 0)) | (0xF << 4));  // Clear PCTL bits for RX and TX
  GPIO_PORTA_PCTL_R |= (1 << 0) | (1 << 4);  // Set PCTL bits for RX and TX
  GPIO_PORTA_DEN_R |= (1 << 0) | (1 << 1);     // Enable digital I/O for RX and TX pins
  GPIO_PORTA_AMSEL_R &= ~(0x03);  // Clear analog mode for RX and TX pins

  // Set baud rate
  UART0_IBRD_R= (int) (SYSTEM_CLCK/(Baud_rate*16));
  UART0_IFLS_R= ((SYSTEM_CLCK/(Baud_rate*16))-(int) (SYSTEM_CLCK/(Baud_rate*16)))*64;
  UART0_LCRH_R =0x70;                                        // Set data length to 8 bits        //one stop //fifos         // and no parity
  UART0_CTL_R |= 0x01;                                                 // Enable UART0
}
void UART1_Init(int Baud_rate)
{
   // Enable the clock for UART0
  SYSCTL_RCGCUART_R |= 0x02;  // Set bit 1 for UART1

  // Enable clock for GPIO Port C
  SYSCTL_RCGCGPIO_R |= 0x04;  // Set bit 3 for GPIO Port A

  // Wait for the clocks to be ready
  while ((SYSCTL_PRGPIO_R & 0x01) == 0) {}  // Check bit 0 for Port A
  while ((SYSCTL_PRUART_R & (0x01)) == 0) {}  // Check bit 0 for UART0

  // Configure PA0 (RX) and PA1 (TX) as UART pins
  GPIO_PORTC_AFSEL_R |= (1 << 4) | (1 << 5);   // Set RX and TX to alternate function
  GPIO_PORTC_PCTL_R &= (GPIO_PORTA_PCTL_R &0xFF00FFFF);  // Clear PCTL bits for RX and TX
  GPIO_PORTC_PCTL_R |= 0x000220000;  // Set PCTL bits for RX and TX
  GPIO_PORTC_DEN_R |= (1 << 0) | (1 << 1);     // Enable digital I/O for RX and TX pins
  GPIO_PORTC_AMSEL_R &= ~(0x30);  // Clear analog mode for RX and TX pins

  // Set baud rate
  UART1_IBRD_R= (int) (SYSTEM_CLCK/(Baud_rate*16));
  UART1_IFLS_R= ((SYSTEM_CLCK/(Baud_rate*16))-(int) (SYSTEM_CLCK/(Baud_rate*16)))*64;
  UART1_LCRH_R =0x70;                                        // Set data length to 8 bits        //one stop //fifos         // and no parity
  UART1_CTL_R |= 0x01;                                                 // Enable UART0
}