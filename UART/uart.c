#include "uart.h"
#include "tm4c123gh6pm.h"

#define SYSTEM_CLCK 16000000

void UART0_Init(int Baud_rate)
{
  // Enable the clock for UART0
  SYSCTL_RCGCUART_R |= 0x01; // Set bit 0 for UART0

  // Enable clock for GPIO Port A
  SYSCTL_RCGCGPIO_R |= 0x01; // Set bit 0 for GPIO Port A

  // Wait for the clocks to be ready
  while ((SYSCTL_PRGPIO_R & 0x01) == 0)
  {
  } // Check bit 0 for Port A
  // while ((SYSCTL_PRUART_R & (0x01)) == 0) {}  // Check bit 0 for UART0

  // Configure PA0 (RX) and PA1 (TX) as UART pins
  GPIO_PORTA_DEN_R |= (1 << 0) | (1 << 1);                               // Enable digital I/O for RX and TX pins
  GPIO_PORTA_AFSEL_R |= (1 << 0) | (1 << 1);                             // Set RX and TX to alternate function
  GPIO_PORTA_PCTL_R &= ~((GPIO_PORTA_PCTL_R & (0xF << 0)) | (0xF << 4)); // Clear PCTL bits for RX and TX NOT NEEDED?
  GPIO_PORTA_PCTL_R |= (1 << 0) | (1 << 4);                              // Set PCTL bits for RX and TX
  GPIO_PORTA_AMSEL_R &= ~(0x03);                                         // Clear analog mode for RX and TX pins

  // Set baud rate
  UART0_IBRD_R = (int)(SYSTEM_CLCK / (Baud_rate * 16));
  UART0_IFLS_R = ((SYSTEM_CLCK / (Baud_rate * 16)) - (int)(SYSTEM_CLCK / (Baud_rate * 16))) * 64;
  UART0_LCRH_R = 0x70;  // Set data length to 8 bits        //one stop //fifos         // and no parity
  UART0_CTL_R |= 0x301; // Enable UART0
}

void UART1_Init(int Baud_rate)
{
  // Enable the clock for UART1
  SYSCTL_RCGCUART_R |= 0x02; // Set bit 1 for UART1

  // Enable clock for GPIO Port C
  SYSCTL_RCGCGPIO_R |= 0x04; // Set bit 3 for GPIO Port A

  // Wait for the clocks to be ready
  while ((SYSCTL_PRGPIO_R & (2 << 1)) == 0)
  {
  } // Check bit 0 for Port C
  // while ((SYSCTL_PRUART_R & (1<<1)) == 0) {} // Check bit 0 for UART1

  // Configure PC4 (RX) and PC5 (TX) as UART pins
  GPIO_PORTC_AFSEL_R |= (1 << 4) | (1 << 5);             // Set RX and TX to alternate function
  GPIO_PORTC_PCTL_R &= (GPIO_PORTA_PCTL_R & 0xFF00FFFF); // Clear PCTL bits for RX and TX
  GPIO_PORTC_PCTL_R |= 0x000220000;                      // Set PCTL bits for RX and TX
  GPIO_PORTC_DEN_R |= (1 << 0) | (1 << 1);               // Enable digital I/O for RX and TX pins
  GPIO_PORTC_AMSEL_R &= ~(0x30);                         // Clear analog mode for RX and TX pins

  // Set baud rate
  UART1_IBRD_R = (int)(SYSTEM_CLCK / (Baud_rate * 16));
  UART1_IFLS_R = ((SYSTEM_CLCK / (Baud_rate * 16)) - (int)(SYSTEM_CLCK / (Baud_rate * 16))) * 64;
  UART1_LCRH_R = 0x70;  // Set data length to 8 bits        //one stop //fifos         // and no parity
  UART1_CTL_R |= 0x301; // Enable UART1
}

void UART2_Init(int Baud_rate)
{
  // Enable the clock for UART1
  SYSCTL_RCGCUART_R |= (1 << 1);

  // Enable clock for GPIO Port D
  SYSCTL_RCGCGPIO_R |= (3 << 1);

  // Wait for the clocks to be ready
  while ((SYSCTL_PRGPIO_R & (3 << 1)) == 0)
  {
  }
  // while ((SYSCTL_PRUART_R & (1<<1)) == 0) {} // Check bit 0 for UART1

  // Configure PD6 (RX) and PD7 (TX) as UART pins
  GPIO_PORTD_AFSEL_R |= (1 << 6) | (1 << 7);             // Set RX and TX to alternate function
  GPIO_PORTD_PCTL_R &= (GPIO_PORTA_PCTL_R & 0xFF00FFFF); // Clear PCTL bits for RX and TX
  GPIO_PORTD_PCTL_R |= 0x000220000;                      // Set PCTL bits for RX and TX
  GPIO_PORTD_DEN_R |= (1 << 0) | (1 << 1);               // Enable digital I/O for RX and TX pins
  GPIO_PORTD_AMSEL_R &= ~(0x30);                         // Clear analog mode for RX and TX pins

  // Set baud rate
  UART2_IBRD_R = (int)(SYSTEM_CLCK / (Baud_rate * 16));
  UART2_IFLS_R = ((SYSTEM_CLCK / (Baud_rate * 16)) - (int)(SYSTEM_CLCK / (Baud_rate * 16))) * 64;
  UART2_LCRH_R = 0x70;  // Set data length to 8 bits        //one stop //fifos         // and no parity
  UART2_CTL_R |= 0x301; // Enable UART0
}

void UART_SendByte(uint32_t base, uint8_t data)
{
  // Wait until the transmit FIFO is not full
  while ((*(volatile uint32_t *)(base + 0x18) & 0x20) != 0)
  {
  }

  // Send the character
  *(volatile uint32_t *)(base + 0x00) = data;
}

uint8_t UART_ReceiveByte(uint32_t base)
{

  // Wait until the transmit FIFO is not full
  while ((*(volatile uint32_t *)(base + 0x18) & 0x10) != 0)
  {
  }

  // Receive the character
  return (char)(*(volatile uint32_t *)(base + 0x00) & 0xFF);
}

char UART0_GetChar(void)
{
  // Wait until the receive FIFO is not empty
  while ((UART0_FR_R & 0x10) != 0)
  {
  }

  // Receive the character
  return (char)(UART0_DR_R & 0xFF);
}

char UART1_GetChar(void)
{
  // Wait until the receive FIFO is not empty
  while ((UART1_FR_R & 0x10) != 0)
  {
  }

  // Receive the character
  return (char)(UART1_DR_R & 0xFF);
}
