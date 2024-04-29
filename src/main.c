#include "main.h"
#include <string.h>
#include <stddef.h>

int main()
{

    UART0_Init(9600);
    UART1_Init(9600);
    const char *rmc = "$GPRMC"; // To get speed and so
    const char *gga = "$GPGGA"; // To get satellite count
    char inputBuffer[500] = {};
    char output_buffer[100]={};
    char *rmc_ptr = NULL;
    char *gga_ptr = NULL;
    float coordinates[COORDINATES_SIZE][2];
    float(*coordinates_ptr)[2] = coordinates;
    while (1)
    {
        sprintf(output_buffer, "Coordinates Saved: %d\n", coordinates_ptr - coordinates);
        UART_printf(output_buffer, UART0);

        for (int i = 0; i < 100000; i++)
        {
            /* code */
        }
        
        if (gps_uart_fill_buffer(inputBuffer, UART1) > 100)
        {

            gga_ptr = strstr(inputBuffer, gga);
            rmc_ptr = strstr(inputBuffer, rmc);

            if (rmc_ptr != NULL)
            {
                float time, latitude, longitude, knots;
                char status, ns, ew;

                if (sscanf(rmc_ptr, "$GPRMC,%f,%c,%f,%c,%f,%c,%f,", &time, &status, &latitude, &ns, &longitude, &ew, &knots) == 7)
                {
                    (*coordinates_ptr)[0] = latitude;
                    (*coordinates_ptr)[1] = longitude;
                }
            }

            if (gga_ptr != NULL)
            {
                float time, latitude, longitude, knots, hdop, altitude;
                char status, ns, ew;
                int fix, satellites;

                if (sscanf(gga_ptr, "$GPGGA,%f,%f,%c,%f,%c,%d,%d,%f,%f,",
                           &time, &latitude, &ns, &longitude, &ew, &fix, &satellites, &hdop, &altitude) == 9)
                {
                    (*coordinates_ptr)[0] = latitude;
                    (*coordinates_ptr)[1] = longitude;
                }
            }

            coordinates_ptr += (gga_ptr != NULL) || (rmc_ptr != NULL);
        }
    }
}