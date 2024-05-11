#include "gps.h"

#include <string.h>
#include <stdio.h>
/*
 * Fills buffer with raw data from gps.
 * @param buffer: address for the 500 byte long buffer to fill.
 * @param UART_base: base address for the UART module to use.
 * */
uint32_t gps_uart_fill_buffer(uint8_t* buffer, uint32_t UART_base){

    int i = 0;
    while (i < 250)
    {
        if (UART_ReceiveByte(UART_base, buffer+i)){
            if (*(buffer +i) != 0)
            {
                i++;
            }
        }

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

// Parses the GPS data from the buffer
int Gps_Parse(char *s,gps_data_t *gps_data_final){
    gps_data_t gps_data;
    int x=0;
    char *p = strstr(s,"$GPGGA");
    if(p!=NULL){
        x = sscanf(p,"$GPGGA,%*f,%f,%*c,%f,",&gps_data.latitude,&gps_data.longitude);
    }

    if(x<2) {
        gps_data_final = NULL;
        return 0;
    }
    else{
        gps_data.latitude  = (int)gps_data.latitude/100  + (gps_data.latitude  - ((float)((int)(gps_data.latitude/100))*100))/60;

        gps_data.longitude = (int)gps_data.longitude/100 + (gps_data.longitude - ((float)((int)(gps_data.longitude/100))*100))/60;

        *gps_data_final = gps_data;
        return 1;
    }
}