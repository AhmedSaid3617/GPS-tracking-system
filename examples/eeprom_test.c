#include "eeprom.h"

int main() {
    EEPROM_Init();

    // Write a 32-bit number into address 12 in EEPROM

    EEPROM_Write(12, 123456789);

    if(EEPROM_Read(12) == 123456789) {
        // Correct Operation of EEPROM
    } else {
        // EEPROM not working correctly
    }
}