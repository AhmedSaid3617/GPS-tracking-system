#ifndef GPS_TRACKING_SYSTEM_MAIN_H
#define GPS_TRACKING_SYSTEM_MAIN_H


#define COORDINATES_SIZE 250

#include <stdint.h>
#include "uart.h"
#include "gps.h"
#include "Systic.h"
#include "eeprom.h"
unsigned long read_coordinates(void);
#endif //GPS_TRACKING_SYSTEM_MAIN_H
