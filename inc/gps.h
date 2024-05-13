#ifndef GPS_TRACKING_SYSTEM_GPS_H
#define GPS_TRACKING_SYSTEM_GPS_H

#define GPS_UART_Fill_Buffer(buffer)
#define GPS_EEPROM_Save(buffer)

#include "uart.h"

struct GPS_Data_Point_TypeDef
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

typedef struct GPS_Data_Point_TypeDef GPS_Data_Point_TypeDef;

void GPS_Start();

uint32_t gps_uart_fill_buffer(uint8_t* buffer, uint32_t UART_base, uint16_t max_size);

void gps_uart_send_buffer(uint8_t* buffer, uint32_t UART_base);

int Gps_Parse(char *s, GPS_Data_Point_TypeDef *gps_data_final);

#endif 
