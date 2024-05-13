#include "uart.h"

#define SYSTEM_CLCK 16000000

// UART0 with interrupt
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
  while ((SYSCTL_PRUART_R & (0x01)) == 0)
  {
  } // Check bit 0 for UART0
  while ((SYSCTL_PRGPIO_R & 0x01) == 0)
  {
  } // Check bit 0 for Port A
  while ((SYSCTL_PRUART_R & (0x01)) == 0)
  {
  } // Check bit 0 for UART0

  // Configure PA0 (RX) and PA1 (TX) as UART pins


  GPIO_PORTA_DEN_R |= (1 << 0) | (1 << 1);                               // Enable digital I/O for RX and TX pins
  GPIO_PORTA_AFSEL_R |= (1 << 0) | (1 << 1);                             // Set RX and TX to alternate function
  GPIO_PORTA_PCTL_R &= ~((GPIO_PORTA_PCTL_R & (0xF << 0)) | (0xF << 4)); // Clear PCTL bits for RX and TX
  GPIO_PORTA_PCTL_R |= (1 << 0) | (1 << 4);                              // Set PCTL bits for RX and TX
  GPIO_PORTA_AMSEL_R &= ~(0x03);                                         // Clear analog mode for RX and TX pins


  // Set baud rate
  UART0_IBRD_R = (int)(SYSTEM_CLCK / (Baud_rate * 16));
  UART0_FBRD_R = ((SYSTEM_CLCK / (Baud_rate * 16)) - (int)(SYSTEM_CLCK / (Baud_rate * 16))) * 64;
  UART0_LCRH_R = 0x70;  // Set data length to 8 bits        //one stop //fifos         // and no parity

  UART0_IM_R |= (1 << 4);
  NVIC_EN0_R |= (1 << 5);
  UART0_CTL_R |= 0x301; // Enable UART0
}

void UART1_Init(int Baud_rate)
{

  // Enable the clock for UART1
  SYSCTL_RCGCUART_R |= (1 << 1); // Set bit 1 for UART1
  SYSCTL_RCGCUART_R |= (1 << 1); // Set bit 1 for UART1

  // Enable clock for GPIO Port B
  SYSCTL_RCGCGPIO_R |= (1 << 1); // Set bit 2 for GPIO Port B
  SYSCTL_RCGCGPIO_R |= (1 << 1); // Set bit 2 for GPIO Port B

  // Wait for the clocks to be ready
  while ((SYSCTL_PRGPIO_R & (1 << 1)) == 0)
  {
  } // Check bit 1 for Port B
  while ((SYSCTL_PRUART_R & (1 << 1)) == 0)
  {
  } // Check bit 1 for UART1

  while ((SYSCTL_PRGPIO_R & (1 << 1)) == 0)
  {
  } // Check bit 1 for Port B
  while ((SYSCTL_PRUART_R & (1 << 1)) == 0)
  {
  } // Check bit 1 for UART1

  // Configure PB0 (RX) and PB1 (TX) as UART pins
  GPIO_PORTB_DEN_R |= (1 << 0) | (1 << 1);               // Enable digital I/O for RX and TX pins
  GPIO_PORTB_AFSEL_R |= (1 << 0) | (1 << 1);             // Set RX and TX to alternate function
  GPIO_PORTB_PCTL_R &= (GPIO_PORTB_PCTL_R & 0xFFFFFF00); // Clear PCTL bits for RX and TX
  GPIO_PORTB_PCTL_R |= 0x000000011;                      // Set PCTL bits for RX and TX
  GPIO_PORTB_AMSEL_R &= ~((1 << 0) | (1 << 1));          // Clear analog mode for RX and TX pins
  GPIO_PORTB_AMSEL_R &= ~((1 << 0) | (1 << 1));          // Clear analog mode for RX and TX pins

  // Set baud rate
  UART1_IBRD_R = (int)(SYSTEM_CLCK / (Baud_rate * 16));
  UART1_FBRD_R = ((SYSTEM_CLCK / (Baud_rate * 16)) - (int)(SYSTEM_CLCK / (Baud_rate * 16))) * 64;
  UART1_FBRD_R = ((SYSTEM_CLCK / (Baud_rate * 16)) - (int)(SYSTEM_CLCK / (Baud_rate * 16))) * 64;
  UART1_LCRH_R = 0x70;  // Set data length to 8 bits        //one stop //fifos         // and no parity
  UART1_CTL_R |= 0x301; // Enable UART1
}

void UART2_Init(int Baud_rate)
{
  // Enable the clock for UART1
  SYSCTL_RCGCUART_R |= (1 << 2);

  // Enable clock for GPIO Port D
  SYSCTL_RCGCGPIO_R |= (1 << 3);

  // Wait for the clocks to be ready
  while ((SYSCTL_PRGPIO_R & (1 << 3)) == 0)
  {
  }
  while ((SYSCTL_PRUART_R & (1 << 2)) == 0)
  {
  } // Check bit 2 for UART2
  while ((SYSCTL_PRGPIO_R & (1 << 3)) == 0)
  {
  }
  while ((SYSCTL_PRUART_R & (1 << 2)) == 0)
  {
  } // Check bit 2 for UART2

  // Configure PD6 (RX) and PD7 (TX) as UART pins

  GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;
  GPIO_PORTD_CR_R |= 0xFF;
  GPIO_PORTD_DEN_R |= (1 << 6) | (1 << 7);               // Enable digital I/O for RX and TX pins
  GPIO_PORTD_AFSEL_R |= (1 << 6) | (1 << 7);             // Set RX and TX to alternate function
  GPIO_PORTD_PCTL_R &= (GPIO_PORTD_PCTL_R & 0x00FFFFFF); // Clear PCTL bits for RX and TX
  GPIO_PORTD_PCTL_R |= 0xFF0000000;                      // Set PCTL bits for RX and TX
  GPIO_PORTD_AMSEL_R &= ~((1 << 7) | (1 << 7));          // Clear analog mode for RX and TX pins
  GPIO_PORTD_AMSEL_R &= ~((1 << 7) | (1 << 7));          // Clear analog mode for RX and TX pins

  // Set baud rate
  UART2_IBRD_R = (int)(SYSTEM_CLCK / (Baud_rate * 16));
  UART2_FBRD_R = ((SYSTEM_CLCK / (Baud_rate * 16)) - (int)(SYSTEM_CLCK / (Baud_rate * 16))) * 64;
  UART2_LCRH_R = 0x70;  // Set data length to 8 bits        //one stop //fifos         // and no parity
  UART2_CTL_R |= 0x301; // Enable UART0
}

void UART7_Init(int Baud_rate)
{
  // Enable the clock for UART0
  SYSCTL_RCGCUART_R |= (1 << 7); // Set bit 0 for UART0
  SYSCTL_RCGCUART_R |= (1 << 7); // Set bit 0 for UART0

  // Enable clock for GPIO Port A
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4; // Set bit 0 for GPIO Port E

  // Wait for the clocks to be ready
  while ((SYSCTL_PRGPIO_R & 0x10) == 0)
  {
  } // Check bit 0 for Port A
  // while ((SYSCTL_PRUART_R & (1<<7)) == 0) {}  // Check bit 0 for UART0
  while ((SYSCTL_PRGPIO_R & 0x10) == 0)
  {
  } // Check bit 0 for Port A
  // while ((SYSCTL_PRUART_R & (1<<7)) == 0) {}  // Check bit 0 for UART0

  // Configure PE0 (RX) and PE1 (TX) as UART pins


  GPIO_PORTE_DEN_R |= (1 << 0) | (1 << 1);                               // Enable digital I/O for RX and TX pins
  GPIO_PORTE_AFSEL_R |= (1 << 0) | (1 << 1);                             // Set RX and TX to alternate function
  GPIO_PORTE_PCTL_R &= ~((GPIO_PORTE_PCTL_R & (0xF << 0)) | (0xF << 4)); // Clear PCTL bits for RX and TX
  GPIO_PORTE_PCTL_R |= (1 << 0) | (1 << 4);                              // Set PCTL bits for RX and TX
  GPIO_PORTE_AMSEL_R &= ~(0x03);                                         // Clear analog mode for RX and TX pins


  // Set baud rate


  UART7_IBRD_R = (int)(SYSTEM_CLCK / (Baud_rate * 16));
  UART7_FBRD_R = ((SYSTEM_CLCK / (Baud_rate * 16)) - (int)(SYSTEM_CLCK / (Baud_rate * 16))) * 64;
  UART7_LCRH_R = 0x70;  // Set data length to 8 bits        //one stop //fifos         // and no parity
  UART7_CTL_R |= 0x301; // Enable UART7
}

void UART_SendByte(uint32_t UART_base, uint8_t data)
{
  // Wait until the transmit FIFO is not full
  while ((*(volatile uint32_t *)(UART_base + 0x18) & 0x20) != 0)
  {
  }
  while ((*(volatile uint32_t *)(UART_base + 0x18) & 0x20) != 0)
  {
  }

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
#ifdef ECHO_TO_UART0
      UART_SendByte(UART0, (char)(*(volatile uint32_t *)(UART_base + 0x00) & 0xFF));
#endif
      return (uint16_t)1;                                                     // Return success.
    }
  }

  // Retrun fail.
  return (uint16_t)0;
}


void UART_printf(char *buffer, uint32_t UART_base)
{
  while (*buffer != 0)
  {
    UART_SendByte(UART_base, *buffer);
    buffer++;
  }
  
}


void ftostr(float number, char* str, int precision) {
    int whole = (int)number;
    float fraction = number - whole;
    sprintf(str, "%d", whole);
    while (*str != '\0') {
        str++;
    }
    *str++ = '.';
    while (precision > 0) {
        fraction *= 10;
        int digit = (int)fraction;
        *str++ = '0' + digit;
        fraction -= digit;
        precision--;
    }
    *str++ = '\n';
    *str = '\0';
}

void UART0_print_float(float num)
{
  char output_buffer[15];

  ftostr(num, output_buffer, 9);
  
  UART_printf(output_buffer, UART0);
}