#include "uart.h"
#include "tm4c123gh6pm.h"

#define SYSTEM_CLCK 80000000

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
  SYSCTL_RCGCUART_R |= (1<<1); // Set bit 1 for UART1

  // Enable clock for GPIO Port B
  SYSCTL_RCGCGPIO_R |= (1<<1); // Set bit 2 for GPIO Port B

  // Wait for the clocks to be ready
  while ((SYSCTL_PRGPIO_R & (1 << 1)) == 0) {} // Check bit 0 for Port C
  // while ((SYSCTL_PRUART_R & (1<<1)) == 0) {} // Check bit 0 for UART1

  // Configure PB0 (RX) and PB1 (TX) as UART pins
  GPIO_PORTB_AFSEL_R |= (1 << 0) | (1 << 1);             // Set RX and TX to alternate function
  GPIO_PORTB_PCTL_R &= (GPIO_PORTA_PCTL_R & 0xFFFFFF00); // Clear PCTL bits for RX and TX
  GPIO_PORTB_PCTL_R |= 0x000000011;                      // Set PCTL bits for RX and TX
  GPIO_PORTB_DEN_R |= (1 << 0) | (1 << 1);               // Enable digital I/O for RX and TX pins
  GPIO_PORTB_AMSEL_R &= ~((1 << 0) | (1 << 1));                         // Clear analog mode for RX and TX pins

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

void UART_SendByte(uint32_t UART_base, uint8_t data)
{
  // Wait until the transmit FIFO is not full
  while ((*(volatile uint32_t *)(UART_base + 0x18) & 0x20) != 0) {}

  // Send the character
  *(volatile uint32_t *)(UART_base + 0x00) = data;
}

uint16_t UART_ReceiveByte(uint32_t UART_base, uint8_t *destination)
{
  int i;

  for (i = 0; i < 10000; i++)
  {
    if ((*(volatile uint32_t *)(UART_base + 0x18) & 0x10) == 0) // Check if FIFO is full.
    {
      *destination = (char)(*(volatile uint32_t *)(UART_base + 0x00) & 0xFF); // Store received byte.
      return (uint16_t)1;  // Return success.
    }
  }

  // Retrun fail.
  return (uint16_t)0;
}
