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

// Parses the GPS data from the buffer
int Gps_Parse(char *s,gps_data_t *gps_data_final){
    gps_data_t gps_data;
    int x=0,n=0;
    char *p = strstr(s,"$GPGGA");
    if(p!=NULL){
        x = sscanf(p,"$GPGGA,%*f,%*f,%*c,%*f,%*c,%d,%d,%*f,%f",&gps_data.fix,&gps_data.satellites,&gps_data.altitude);
    }
    p = strstr(s,"$GPRMC");
    if(p!=NULL){
        n = sscanf(p,"$GPRMC,%f,%c,%f,%c,%f,%c,%f",&gps_data.time,&gps_data.status,&gps_data.latitude,&gps_data.ns,&gps_data.longitude,&gps_data.ew,&gps_data.knots);
    }
    if(x+n<10) {
        gps_data_final = NULL;
        return 0;
    }
    else{
        *gps_data_final = gps_data;
        return 1;
    }
}