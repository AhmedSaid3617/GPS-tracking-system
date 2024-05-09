#ifndef GPS_TRACKING_SYSTEM_GPS_H
#define GPS_TRACKING_SYSTEM_GPS_H

#define GPS_UART_Fill_Buffer(buffer)
#define GPS_EEPROM_Save(buffer)

#include "uart.h"

struct gps_data_s
{
    float latitude;
    float longitude;
    float time;
    float knots;
    float altitude;
    int fix;
    int satellites;
    char ns;
    char ew;
    char status;
};

typedef struct gps_data_s gps_data_t;

void GPS_Start();

uint32_t gps_uart_fill_buffer(uint8_t* buffer, uint32_t UART_base);

void gps_uart_send_buffer(uint8_t* buffer, uint32_t UART_base);

int Gps_Parse(char *s,gps_data_t *gps_data_final);

#endif 
