#include "eeprom.h"

/*
 * EEPROM Initialization (8.2.4.2)
 * */
EEPROM_Init_Status EEPROM_Init()
{
    RCGCEEPROM->R0 = 1;

    DELAY_6_CYCLES();

    while (EEDONE->WORKING == 1)
        ;

    if (EESUPP->ERETRY || EESUPP->PERTRY)
    {
        return EEPROM_Init_Failed;
    }

    SREEPROM->R0 = 0;

    DELAY_6_CYCLES();

    while (EEDONE->WORKING == 1)
        ;

    return EEPROM_Init_Successfull;
}

/*
 * Prepare the EEPROM to write or read data at [block] and [offset]
 * */
void EEPROM_Set_Block_And_Offset(unsigned int block, unsigned int offset)
{
    if (block > (1 << 16))
    {
        return;
    }

    if (offset > (1 << 4))
    {
        return;
    }

    EEBLOCK->BLOCK = block;
    EEOFFSET->OFFSET = offset;

    DELAY_4_CYCLES();
}

/*
 * Write data at pseudo-address [address] in EEPROM
 * @param   address     Pseudo-address (4 bytes) in the EEPROM, min 0, max 512.
 * @result              The 32-bit value at pseudo-address [address] in the EEPROM
 * */
unsigned long EEPROM_Read(int address)
{
    if (address < 512)
    {
        int block = address / EEPROM_BLOCK_SIZE;
        int offset = address % EEPROM_BLOCK_SIZE;

        EEPROM_Set_Block_And_Offset(block, offset);

        return EERDWR;
    }
}

/*
 * Read data at pseudo-address [address] from EEPROM
 * @param   address     Pseudo-address (4 bytes) in the EEPROM, min 0, max 512.
 * @param   value       The 32-bit value to write at the specified address in the EEPROM.
 * */
void EEPROM_Write(unsigned int address, unsigned long value)
{
    if (address < 512)
    {
        unsigned int block = address / EEPROM_BLOCK_SIZE;
        unsigned int offset = address % EEPROM_BLOCK_SIZE;

        EEPROM_Set_Block_And_Offset(block, offset);

        EERDWR = value;
    }
}

// TODO Rename
void Save_float_EEPROM(float coordinates[][2],unsigned long number_of_saved_reading)/number_of elements is not the size of the array/
{
    char i,j;
    float f_value = 0;
    EEPROM_Write(0,number_of_saved_reading);  /save the number of saved readings for the Coordinates (longtude,latitude) not the size of the 2D array/

    for(i=0;i<number_of_saved_reading;i++)
    {
       for(j=0;j<2;j++)
       {
    	    f_value = coordinates[i][j];

            EEPROM_Write(2*i + j +1 , (unsigned int)(f_value*10000.0));
            
       }
    }
}