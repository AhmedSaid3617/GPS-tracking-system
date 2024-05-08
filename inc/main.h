#ifndef GPS_TRACKING_SYSTEM_MAIN_H
#define GPS_TRACKING_SYSTEM_MAIN_H
#include <stdint.h>
#include "i2c.h"
#include "oled.h"
#include "uart.h"
#include "gps.h"
#include "Systic.h"
#include "eeprom.h"

#define COORDINATES_SIZE 250

unsigned long read_coordinates(void);
#endif //GPS_TRACKING_SYSTEM_MAIN_H
