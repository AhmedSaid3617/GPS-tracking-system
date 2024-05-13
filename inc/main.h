#ifndef GPS_TRACKING_SYSTEM_MAIN_H
#define GPS_TRACKING_SYSTEM_MAIN_H
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "i2c.h"
#include "oled.h"
#include "uart.h"
#include "gps.h"
#include "Systic.h"
#include "gpio.h"
#include "eeprom.h"
#include "utils.h"
#include "tm4c123gh6pm.h"

#define RAM_MAX_COORDINATES 250
#define EEPROM_MAX_COORDINATES 250

#define DISTANCE_MIN_THRESHOLD 1
#define DISTANCE_MAX_THRESHOLD 50
#define GPS_MAXIMUM_BUFFER_SIZE 500

#define DEBUG

typedef enum StateTypeDef
{
    IDLE = 1,
    RECORDING
} StateTypeDef;

#endif //GPS_TRACKING_SYSTEM_MAIN_H
