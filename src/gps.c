#include "gps.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define COORDINATES_SIZE 100
#define BUFFER_SIZE 250

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

        if (coordinates_ptr - coordinates > COORDINATES_SIZE) {
            coordinates_ptr = coordinates;
            GPS_EEPROM_Save();
        }
    }
}
