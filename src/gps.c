#include "gps.h"

#include <string.h>
#include <stdio.h>

/*
 * Fills buffer with raw data from gps.
 * @param buffer: address for the 500 byte long buffer to fill.
 * @param UART_base: base address for the UART module to use.
 * */
uint32_t gps_uart_fill_buffer(uint8_t* buffer, uint32_t UART_base){
    
    for (int i = 0; i < 500; i++)
    {
        if (UART_ReceiveByte(UART_base, buffer+i))
            i++;
        else{
            return (uint32_t)i;
            break;
        }
    }
}

void gps_uart_send_buffer(uint8_t* buffer, uint32_t UART_base){

    for (int i = 0; i < 500; i++)
    {
        UART_SendByte(UART0, *(buffer + i));
    }
    
}

/*
 * Polls GPS for latitude, longitude, satellites used and altitude
 * */
void GPS_Start() {
}
