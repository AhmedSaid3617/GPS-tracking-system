#include "eeprom.h"

/*
 * EEPROM Initialization (8.2.4.2)
 * */
EEPROM_Init_Status EEPROM_Init() {
    RCGCEEPROM->R0 = 1;

    DELAY_6_CYCLES();

    while (EEDONE->WORKING == 1);

    if (EESUPP->ERETRY || EESUPP->PERTRY) {
        return EEPROM_Init_Failed;
    }

    SREEPROM->R0 = 0;

    DELAY_6_CYCLES();

    while (EEDONE->WORKING == 1);

    

    return EEPROM_Init_Successfull;
}

/*
 * Prepare the EEPROM to write or read data at [block] and [offset]
 * */
void EEPROM_Set_Block_And_Offset(unsigned int block, unsigned int offset) {
    if (block > (1 << 16)) {
        return;
    }

    if (offset > (1 << 4)) {
        return;
    }

    EEBLOCK->BLOCK = block;
    EEOFFSET->OFFSET = offset;

    DELAY_4_CYCLES();
}

/*
 * Write data at pseudo-address [address] in EEPROM
 * */
unsigned long EEPROM_Read(int address) {
    // TODO: convert address into block and offset
    EEPROM_Set_Block_And_Offset(0, address);


    return EERDWR;
}

/*
 * Read data at pseudo-address [address] from EEPROM
 * */
void EEPROM_Write(int address, unsigned long value) {
    // TODO: convert address into block and offset
    EEPROM_Set_Block_And_Offset(0, address);


    EERDWR = value;
}