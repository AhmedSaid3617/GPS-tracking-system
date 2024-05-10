#ifndef GPS_TRACKING_SYSTEM_MAIN_H
#define GPS_TRACKING_SYSTEM_MAIN_H
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "i2c.h"
#include "oled.h"
#include "uart.h"
#include "gps.h"
#include "Systic.h"
#include "gpio.h"
#include "eeprom.h"
#include "utils.h"
#include "tm4c123gh6pm.h"

#define RAM_MAX_COORDINATES 1000
#define EEPROM_MAX_COORDINATES 250

void oled_display_data();

#endif //GPS_TRACKING_SYSTEM_MAIN_H
