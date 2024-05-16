# GPS Tracker Project

## Introduction

This project involves developing a GPS tracking system implemented on the Tiva C evaluation kit using C. The system records GPS coordinates, stores them in EEPROM, and retrieves them later to be displayed on a map using a custom Python script. This project showcases various functionalities including GPS data parsing, distance calculation, and data visualization.

## Functional Description

### Overview

The GPS Tracker operates in two main modes: IDLE mode and RECORDING mode. Each mode leverages custom drivers and functions to interact with various peripherals and process GPS data efficiently.

### Modes of Operation

1. **IDLE Mode**
   - **Functionality**: In this mode, the system continuously parses data received from the GPS module.
   - **Display**: It indicates whether the parsed GPS data is valid or invalid on the OLED screen.
   - **Components Involved**: 
     - **GPS Data Parsing**: Utilizes custom functions to extract and verify GPS data.
     - **OLED Display**: Shows the status of the GPS data (valid/invalid).

2. **RECORDING Mode**
   - **Functionality**: This mode is activated to record GPS coordinates.
   - **Data Storage**: The coordinates are stored in the EEPROM.
   - **Distance Calculation**: The system calculates the distance covered based on the recorded coordinates.
   - **Components Involved**:
     - **GPS Data Parsing**: Continuously extracts coordinates from the GPS data.
     - **EEPROM Storage**: Saves the parsed coordinates for future retrieval.
     - **Distance Calculation**: Computes the distance traveled using the stored coordinates.

### Custom Drivers

The project includes custom drivers for efficient hardware interaction:
- **GPIO Driver**: Manages general-purpose input/output operations.
- **UART Driver**: Handles communication with the GPS module.
- **Systick Timer Driver**: Provides timing functionalities for the system.
- **EEPROM Driver**: Manages read and write operations for data storage.
- **I2C Driver**: Facilitates communication with the OLED screen and other I2C devices.
- **OLED Screen Driver**: Manages display operations for the OLED screen.

### Python Script for Data Visualization

A Python script is provided to retrieve the stored GPS coordinates from the EEPROM and display them on a map. This script offers a visual representation of the tracked path, enhancing the usability of the GPS tracker.

### How to Use

1. **Compile and Upload**: Compile the C code and upload it to the Tiva C evaluation kit.
2. **Connect GPS Module**: Ensure the GPS module is properly connected to the UART interface.
3. **Switch Modes**: Push switch 1 to switch from IDLE to RECORDING mode, push it again to stop recording, save coordinates to EEPROM and go back to IDLE mode.
4. **Retrieve Data**: Use the Python script to retrieve and visualize the recorded GPS coordinates on a map.

This README serves as an introductory guide to understanding and utilizing the GPS Tracker Project. For detailed information on implementation and usage, please refer to the provided documentation and source code comments.


## Drivers
The following is a top-level discription of drivers developed in this project and their uses.

## EEPROM

1. The default for any program is that the run time data is saved in the RAM, which is a volatile memory, so as the we cut the power from the kit data is lost.
2. Sometimes there are critical data that shouldn't be lost even if the power is off, so we need a type of Non volatile memory to hold this important data.
3. EEPROM (Electrically Erasable Programmable Read-Only Memory) is crucial in Arm processors for non-volatile storage. It retains data even when power is off, making it ideal for storing configuration settings, calibration data, and user preferences. Additionally, its execute-while-write capability allows real-time updates without interrupting system operation.
4. We used the EEPROM of the TivaC kit we have by writing a driver from scratch to be able to fully control the EEPROM and save the Coordinates we parse from the GPS module in the EEPROM in order to prevent this data from loss if the power was turned off from the kit.

### Functions of the driver and their usage:
| Function                                             | Description                                                                                                         | Parameters                                                                                            | Usage                                                                       |
|------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------|
| `EEPROM_Init()`                                     | Initializes the EEPROM module for communication.                                                                   | None                                                                                                  | Call this function to initialize the EEPROM module for communication.       |
| `EEPROM_Set_Block_And_Offset(unsigned int block, unsigned int offset)` | Prepares the EEPROM for writing or reading data at a specific block and offset.                                     | `block`: Block number for EEPROM access.<br> `offset`: Offset within the block for EEPROM access.   | Call this function to set the block and offset for EEPROM access.           |
| `EEPROM_Read(int address)`                          | Reads a 32-bit value from the specified pseudo-address in EEPROM.                                                   | `address`: Pseudo-address in EEPROM (4 bytes), min 0, max 512.                                        | Call this function to read data from the specified pseudo-address in EEPROM. |
| `EEPROM_Write(unsigned int address, unsigned long value)` | Writes a 32-bit value to the specified pseudo-address in EEPROM.                                                    | `address`: Pseudo-address in EEPROM (4 bytes), min 0, max 512.<br>`value`: 32-bit value to be written. | Call this function to write data to the specified pseudo-address in EEPROM.   |
| `EEPROM_write_array(float coordinates[][2],unsigned long number_of_saved_reading)` | Writes an array of coordinates to EEPROM.                                                                          | `coordinates`: 2D array of coordinates to be written.<br>`number_of_saved_reading`: Number of readings to be saved. | Call this function to write an array of coordinates to EEPROM.               |
| `EEPROM_read_coordniates()`                         | Reads the coordinates stored in EEPROM.                                                                             | None                                                                                                  | Call this function to read the coordinates stored in EEPROM.                |


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
| `Gps_Parse(char *s, GPS_Data_Point_TypeDef *gps_data_final)` | Parses the GPS data string and extracts latitude and longitude information.                     | `s`: Pointer to the GPS data string.<br>`gps_data_final`: Pointer to the structure where the parsed latitude and longitude will be stored. | 1 if successful, 0 otherwise | Call this function to parse a GPS data string and extract latitude and longitude information |


