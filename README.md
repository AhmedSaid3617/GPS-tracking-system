# Project Description

The goal of this project is to develop an embedded system using C programming that gathers real-time positional coordinates while a microcontroller is in motion (GPS tracking system using TM4C123G LaunchPad) after power-on until a destination point is reached. The collected data will then be efficiently transferred to a personal computer (PC) and visualized on a map application.

Other functions required by the system:

1. When the destination point is reached the built-in LED of the launchpad should be turned on.
2. The system should check for UART commands from the PC and if the PC sends the command ‘U’ then the system should send the stored trajectory to the PC.

## EEPROM

1. The default for any program is that the run time data is saved in the RAM, which is a volatile memory, so as the we cut the power from the kit data is lost.
2. Sometimes there are critical data that shouldn't be lost even if the power is off, so we need a type of Non volatile memory to hold this important data.
3. EEPROM (Electrically Erasable Programmable Read-Only Memory) is crucial in Arm processors for non-volatile storage. It retains data even when power is off, making it ideal for storing configuration settings, calibration data, and user preferences. Additionally, its execute-while-write capability allows real-time updates without interrupting system operation.
4. We used the EEPROM of the TivaC kit we have by writing a driver from scratch to be able to fully control the EEPROM and save the Coordinates we parse from the GPS module in the EEPROM in order to prevent this data from loss if the power was turned off from the kit.

### Functions of the driver and their usage:

| Function                                         | Usage                                                        |
|--------------------------------------------------|--------------------------------------------------------------|
| unsigned long EEPROM_Read(int address)          | Read data of a certain address of the EEPROM                 |
| void EEPROM_Write(unsigned int address, unsigned long value) | Saves a certain value in a certain address of the EEPROM |
| EEPROM_Init_Status EEPROM_Init()                 | Initializes the EEPROM of the kit|
| EEPROM_write_array(float coordinates[][2], unsigned long number_of_saved_reading) | Saves the array of coordinates the module gets in contiguous locations starting by the number of saved Coordinates |
| unsigned long EEPROM_read_coordinates()          | Reads the saved array of coordinates saved in the EEPROM     |


## I2C
The I2C (Inter-Integrated Circuit) driver facilitates communication between the microcontroller and external devices using the I2C protocol. I2C is a serial communication protocol commonly used for connecting peripherals to microcontrollers. This driver initializes the I2C protocol, enables data transmission, and provides functions for writing and reading data to and from I2C-compatible devices.


### Functions of the driver and their usage:

| Function                                             | Description                                                                                                         | Parameters                                                                                            | Usage                                                                       |
|------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------|
| `I2C_Init()`                                        | Initializes the I2C communication protocol.                                                                         | None                                                                                                  | Call this function to initialize the I2C communication protocol.            |
| `I2C0_Write_Multiple(int slave_address, char* ptr, int bytes_count)` | Writes multiple bytes to the specified slave device.                                                                | `slave_address`: Address of the slave device.<br>`ptr`: Pointer to the data buffer to be written.<br>`bytes_count`: Number of bytes to be written.  | Call this function to write multiple bytes to the specified slave device.    |
| `I2C0_Write_In_Sequence(char slave_address, char data)` | Writes data to the specified slave device in sequence.                                                             | `slave_address`: Address of the slave device.<br>`data`: Data to be written.                          | Call this function to write data to the specified slave device in sequence.   |
| `I2C0_Write_First_In_Sequence(int slave_address, char data)` | Writes data to the specified slave device as the first byte in a sequence.                                        | `slave_address`: Address of the slave device.<br>`data`: Data to be written.                          | Call this function to write data to the specified slave device as the first byte in a sequence. |
| `I2C0_Write_Single(int slave_address, char data)`    | Writes a single byte to the specified slave device.                                                                 | `slave_address`: Address of the slave device.<br>`data`: Data to be written.                          | Call this function to write a single byte to the specified slave device.     |
| `I2C0_Write_Last_In_Sequence(int slave_address, char data)`  | Writes data to the specified slave device as the last byte in a sequence.                                         | `slave_address`: Address of the slave device.<br>`data`: Data to be written.                          | Call this function to write data to the specified slave device as the last byte in a sequence. |


## OLED
The OLED (Organic Light Emitting Diode) driver enables interfacing with OLED displays via the I2C protocol. OLED displays are lightweight, flexible, and offer high contrast and brightness, making them ideal for various applications, including embedded systems. This driver initializes the OLED display, provides functions for drawing data on the display, and offers utilities for writing to specific columns and pages of the OLED screen.

### Functions of the driver and their usage:

| Function                                             | Description                                                                                                         | Parameters                                                                                            | Usage                                                                       |
|------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------|
| `OLED_I2C_Init()`                                        | Initializes the OLED display using the I2C protocol.                                                                | None                                                                                                  | Call this function to initialize the OLED display using the I2C protocol.            |
| `OLED_I2C_Draw(const char * ptr, int length)` | Draws data on the OLED display.                                                                | `ptr`: Pointer to the data buffer to be drawn.<br>`length`: Length of the data buffer.  | Call this function to draw data on the OLED display.    |
| `OLED_I2C_Write(unsigned char col, unsigned char page, char * ptr)` | Writes data to the specified column and page of the OLED display.                                                             | `col`: Column number.<br>`page`: Page number.<br>`ptr`: Pointer to the data to be written.                          | Call this function to write data to the specified column and page of the OLED display.   |
| `OLED_clear_display()`    | Clears the OLED display.                                                                 | None.<br>                                                                                         | Call this function to clear the OLED display.     |

## UART 

The UART (Universal Asynchronous Receiver-Transmitter) driver handles serial communication between the microcontroller and external devices or peripherals. UART is a widely used communication protocol for transmitting data between devices asynchronously. This driver initializes UART modules, configures baud rates, sends and receives single bytes or strings of data, and provides utilities for printing formatted data over UART interfaces.

### Functions of the driver and their usage:

| Function                                             | Description                                                                                                         | Parameters                                                                                            | Usage                                                                       |
|------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------|----------------------------------------------------------------------------|
| `UART0_Init(int Baud_rate)`                          | Initializes UART0 with the specified baud rate.                                                                    | `Baud_rate`: Baud rate for UART communication.                                                      | Call this function to initialize UART0 with the specified baud rate.        |
| `UART1_Init(int Baud_rate)`                          | Initializes UART1 with the specified baud rate.                                                                    | `Baud_rate`: Baud rate for UART communication.                                                      | Call this function to initialize UART1 with the specified baud rate.        |
| `UART2_Init(int Baud_rate)`                          | Initializes UART2 with the specified baud rate.                                                                    | `Baud_rate`: Baud rate for UART communication.                                                      | Call this function to initialize UART2 with the specified baud rate.        |
| `UART7_Init(int Baud_rate)`                          | Initializes UART7 with the specified baud rate.                                                                    | `Baud_rate`: Baud rate for UART communication.                                                      | Call this function to initialize UART7 with the specified baud rate.        |
| `UART_SendByte(uint32_t UART_base, uint8_t data)`    | Sends a single byte of data over the specified UART interface.                                                      | `UART_base`: Base address of the UART module to use.<br>`data`: The byte of data to send.             | Call this function to send a single byte of data over the specified UART interface. |
| `UART_SendFloat(uint32_t UART_base, float data_float)` | Sends a float value over the specified UART interface.                                                               | `UART_base`: Base address of the UART module to use.<br>`data_float`: The float value to send.       | Call this function to send a float value over the specified UART interface.     |
| `UART_ReceiveByte(uint32_t UART_base, uint8_t *destination)` | Receives a single byte of data from the specified UART interface.                                                  | `UART_base`: Base address of the UART module to use.<br>`destination`: Pointer to where the received byte will be stored. | Call this function to receive a single byte of data from the specified UART interface. |
| `UART_printf(char *buffer, uint32_t UART_base)`      | (Not implemented) Sends a null-terminated string over the specified UART interface.                                  | `buffer`: Pointer to the null-terminated string to send.<br>`UART_base`: Base address of the UART module to use. | (Not implemented) Call this function to send a null-terminated string over the specified UART interface. |
| `UART0_print_float(float num)`                       | (Not implemented) Prints a float value over UART0.                                                                 | `num`: The float value to print.                                                                      | (Not implemented) Call this function to print a float value over UART0.       |

## GPIO

The GPIO (General Purpose Input/Output) driver allows the microcontroller to control digital input and output pins. GPIO pins are versatile and can be configured as either inputs or outputs, allowing the microcontroller to interact with external sensors, switches, LEDs, and other digital devices. This driver initializes GPIO ports, sets pin directions, reads and writes pin values, and provides utilities for common GPIO operations.

### Functions of the driver and their usage:


| Function                                    | Description                                                                                                                                                                      | Parameters                                                                                                | Usage                                                                         |
|---------------------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------|
| `void GPIOF_default_init(void)`             | Initializes the GPIO Port F with the built-in switches as input and built-in LEDs as output.                                                                                   | None                                                                                                      | Call this function to initialize GPIO Port F for the default configuration.     |
| `unsigned char read_sw1(void)`             | Reads the state of the SW1 switch connected to GPIO Port F and returns its value (1 for pressed, 0 for not pressed).                                                            | None                                                                                                      | Call this function to read the state of the SW1 switch.                         |
| `unsigned char read_sw2(void)`             | Reads the state of the SW2 switch connected to GPIO Port F and returns its value (1 for pressed, 0 for not pressed).                                                            | None                                                                                                      | Call this function to read the state of the SW2 switch.                         |
| `void write_red_led(unsigned char value)`  | Turns the red LED on GPIO Port F on or off based on the value provided (1 for on, 0 for off).                                                                                  | `value`: The value to turn the LED on or off (1 for on, 0 for off).                                      | Call this function to turn the red LED on GPIO Port F on or off.                 |
| `void write_blue_led(unsigned char value)` | Turns the blue LED on GPIO Port F on or off based on the value provided (1 for on, 0 for off).                                                                                 | `value`: The value to turn the LED on or off (1 for on, 0 for off).                                      | Call this function to turn the blue LED on GPIO Port F on or off.                |
| `void write_green_led(unsigned char value)`| Turns the green LED on GPIO Port F on or off based on the value provided (1 for on, 0 for off).                                                                                | `value`: The value to turn the LED on or off (1 for on, 0 for off).                                      | Call this function to turn the green LED on GPIO Port F on or off.               |
| `void GPIO_init(unsigned long GPIOPort, char input_config, char output_config)` | Initializes the specified GPIO port with the provided input and output configurations.                                                                         | `GPIOPort`: The base address of the GPIO port to be initialized.<br>`input_config`: Mask for pins to be set as input.<br>`output_config`: Mask for pins to be set as output. | Call this function to initialize the specified GPIO port with custom configurations. |
| `char GPIO_read_pin(unsigned long GPIOPort, char pin_num)` | Reads and returns the value of the specified pin in the GPIO port.                                                                                                                | `GPIOPort`: The base address of the GPIO port.<br>`pin_num`: The number of the pin to be read.            | Call this function to read the value of a specific pin in the GPIO port.         |
| `void GPIO_write_pin(unsigned long GPIOPort, char pin_num, char value)` | Writes the provided value to the specified pin in the GPIO port.                                                                                                                 | `GPIOPort`: The base address of the GPIO port.<br>`pin_num`: The number of the pin to be written.<br>`value`: The value to be written to the pin.                         | Call this function to write a value to a specific pin in the GPIO port.         |




## Systick

The Systick driver manages the SysTick timer, a system timer integrated into the microcontroller. SysTick is a countdown timer that generates periodic interrupts, enabling precise timing operations and timekeeping in embedded systems. This driver initializes the SysTick timer, creates delays in milliseconds or clock cycles, and configures interrupts at specified intervals for time-sensitive applications.

### Functions of the driver and their usage:
| Function                                    | Description                                                                                                                                                                      | Parameters                                                                                                | Usage                                                                         |
|---------------------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------|
| `void Systick_Init()`                      | Initializes the SysTick timer.                                                                                                                                                   | None                                                                                                      | Call this function to initialize the SysTick timer.                             |
| `void Systic_Delay_ms(unsigned int time_ms)`| Delays the program execution by the specified number of milliseconds using the SysTick timer.                                                                                   | `time_ms`: The number of milliseconds to delay.                                                        | Call this function to create a delay in milliseconds using the SysTick timer.   |
| `void Systick_Delay_cycles(unsigned int delay)` | Delays the program execution by the specified number of clock cycles using the SysTick timer.                                                                                 | `delay`: The number of clock cycles to delay.                                                          | Call this function to create a delay in clock cycles using the SysTick timer.    |
| `void Systick_Interrupt_Init(int delay_ms)`| Initializes the SysTick timer to send an interrupt every `delay_ms` milliseconds.                                                                                                 | `delay_ms`: The interval for the interrupt in milliseconds.                                             | Call this function to set up a SysTick interrupt with the specified interval.  |






## GPS Module
### Functions of the driver and their usage:

| Function                                             | Description                                                                                                         | Parameters                                                                                            | Returns       | Usage                                                                       |
|------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------|---------------|----------------------------------------------------------------------------|
| `GPS_Start()`                                        | Initializes the GPS module and starts data reception.                                                               | None                                                                                                  | None          | Call this function to initialize the GPS module and begin data reception. |
| `gps_uart_fill_buffer(uint8_t* buffer, uint32_t UART_base, uint16_t max_size)` | Fills the buffer with raw data received from the GPS module via UART.                         | `buffer`: Pointer to the buffer where the received data will be stored.<br>`UART_base`: Base address of the UART module used for communication with the GPS module.<br>`max_size`: Maximum size of the buffer. | Number of bytes filled into the buffer | Call this function to fill a buffer with raw data received from the GPS module. |
| `gps_uart_send_buffer(uint8_t* buffer, uint32_t UART_base)`    | (Not implemented) Sends data stored in a buffer over UART to the PC.                                                | `buffer`: Pointer to the buffer containing the data to be sent.<br>`UART_base`: Base address of the UART module used for communication with the PC. | None          | (Not implemented) Call this function to send data stored in a buffer over UART to the PC.    |
| `Gps_Parse(char *s, GPS_Data_Point_TypeDef *gps_data_final)` | Parses the GPS data string and extracts latitude and longitude information.                     | `s`: Pointer to the GPS data string.<br>`gps_data_final`: Pointer to the structure where the parsed latitude and longitude will be stored. | 1 if successful, 0 otherwise | Call this function to parse a GPS data string and extract latitude and longitude information. |


