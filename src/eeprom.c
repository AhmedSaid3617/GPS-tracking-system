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
    if (block > 31)
    {
        return;
    }

    if (offset > 15)
    {
        return;
    }
    
    EEBLOCK->value = block;
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

        DELAY_4_CYCLES();

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

        DELAY_6_CYCLES();

        EERDWR = value;

        for (int i = 0; i < 10000; i++)
        {
            
        }

        /* UART0_print_float(block);
        UART0_print_float(offset);
        UART0_print_float(EERDWR);
        UART_printf("=============", UART0); */

        
    }
}

// TODO: Rename.
unsigned long EEPROM_read_coordniates(void)
{
    unsigned long size = EEPROM_Read(0);
    UART0_print_float(size);
    for (int i = 0; i < size * 2; i++)
    {
        for (int x = 0; x < 1000; x++);
        
        float L = EEPROM_Read(i+1)/1000000.0;
        UART0_print_float(L);
    } 
    return size;
} 

// TODO Rename
void EEPROM_write_array(float coordinates[][2], unsigned long number_of_saved_reading) // number_of elements is not the size of the array/
{
    char i, j;
    float f_value = 0;
    EEPROM_Write(0, number_of_saved_reading); // save the number of saved readings for the Coordinates (longtude,latitude) not the size of the 2D array/

    for (i = 0; i < number_of_saved_reading; i++)
    {
        for (j = 0; j < 2; j++)
        {
            f_value = coordinates[i][j];
            for (int x = 0; x < 10000; x++)
            {
                
            }

            EEPROM_Write(2 * i + j + 1, (unsigned int)(f_value * 1000000.0));
        }


    }
}