#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define COORDINATES_SIZE 100

void GPS_Start() {
    const char *rmc = "$GPRMC"; // To get speed and so
    const char *gga = "$GPGGA"; // To get satellite count
    const char *rmc_ptr = NULL;
    const char *gga_ptr = NULL;
    float coordinates[COORDINATES_SIZE][2];
    float (*coordinates_ptr)[2] = coordinates;

    rmc_ptr = strstr(data, rmc);
    gga_ptr = strstr(data, gga);

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

    if (coordinates_ptr - coordinates > COORDINATES_SIZE)
        coordinates_ptr = coordinates;

}
