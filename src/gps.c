#include "gps.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define COORDINATES_SIZE 100
#define BUFFER_SIZE 250

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
    char buffer[BUFFER_SIZE];

    while(1) {
        GPS_UART_Fill_Buffer(buffer);

        const char *rmc = "$GPRMC"; // To get speed and so
        const char *gga = "$GPGGA"; // To get satellite count
        const char *rmc_ptr = NULL;
        const char *gga_ptr = NULL;
        float coordinates[COORDINATES_SIZE][2];
        float (*coordinates_ptr)[2] = coordinates;

        rmc_ptr = strstr(buffer, rmc);
        gga_ptr = strstr(buffer, gga);

        if (rmc_ptr != NULL) {
            float time, latitude, longitude, knots;
            char status, ns, ew;

            if (sscanf(rmc_ptr, "$GPRMC,%f,%c,%f,%c,%f,%c,%f,", &time, &status, &latitude, &ns, &longitude, &ew, &knots) == 7) {
                (*coordinates_ptr)[0] = latitude;
                (*coordinates_ptr)[1] = longitude;
            }
        }

        if (gga_ptr != NULL) {
            float time, latitude, longitude, knots, hdop, altitude;
            char status, ns, ew;
            int fix, satellites;

            if (sscanf(gga_ptr, "$GPGGA,%f,%f,%c,%f,%c,%d,%d,%f,%f,",
                       &time, &latitude, &ns, &longitude, &ew, &fix, &satellites, &hdop, &altitude) == 9) {
                (*coordinates_ptr)[0] = latitude;
                (*coordinates_ptr)[1] = longitude;
            }
        }

        coordinates_ptr++;

        /* if (coordinates_ptr - coordinates > COORDINATES_SIZE) {
            coordinates_ptr = coordinates;
            GPS_EEPROM_Save();
        } */
    }
}
