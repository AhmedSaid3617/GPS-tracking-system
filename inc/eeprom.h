#ifndef GPS_TRACKING_SYSTEM_EEPROM_H
#define GPS_TRACKING_SYSTEM_EEPROM_H

#include "uart.h"

#define EEPROM_BLOCK_SIZE 16

// TODO: Insert delay (6 cycles plus function call overhead)
#define DELAY_6_CYCLES()            \
    {                               \
        for (int i = 0; i < 1000; i++) \
        {                           \
        }                           \
    }

// TODO: Insert delay (4 cycles plus function call overhead)
#define DELAY_4_CYCLES()            \
    {                               \
        for (int i = 0; i < 1000; i++) \
        {                           \
        }                           \
    }
    
#define EEPROM *(volatile unsigned long *)0x400AF000

#define RCGCEEPROM ((volatile RCGCEEPROM_TypeDef *)0x400FE658)
#define EEDONE ((volatile EEDONE_TypeDef *)0x400AF018)
#define EESUPP ((volatile EESUPP_TypeDef *)0x400AF01C)
#define SREEPROM ((volatile SREEPROM_TypeDef *)0x400FE558)

#define EERDWR *((volatile unsigned long *)0x400AF010)
#define EEBLOCK ((volatile EEBLOCK_TypeDef *)0x400AF004)
#define EEOFFSET ((volatile EEOFFSET_TypeDef *)0x400AF008)

typedef enum EEPROM_Init_Status
{
    EEPROM_Init_Successfull,
    EEPROM_Init_Failed,
} EEPROM_Init_Status;

typedef union RCGCEEPROM_TypeDef
{
    unsigned int R0 : 1;
    unsigned long value;
} RCGCEEPROM_TypeDef;

typedef union EEBLOCK_TypeDef
{
    struct 
    {
        unsigned int BLOCK : 16;
    };
    
    
    unsigned long value;
} EEBLOCK_TypeDef;

typedef union EEOFFSET_TypeDef
{
    
    struct
    {
       unsigned int OFFSET : 4;
    };
    
    unsigned long value;
} EEOFFSET_TypeDef;

typedef union SREEPROM_TypeDef
{
    unsigned int R0 : 1;
    unsigned long value;
} SREEPROM_TypeDef;

typedef union EEDONE_TypeDef
{
    struct
    {
        unsigned int WORKING : 1;
        unsigned int _reserved : 1;
        unsigned int WKERASE : 1;
        unsigned int WKCOPY : 1;
        unsigned int NOPERM : 1;
        unsigned int WRBUSY : 1;
    };
    unsigned long value;
} EEDONE_TypeDef;

typedef union EESUPP_TypeDef
{
    struct
    {
        unsigned int START : 1;
        unsigned int EREQ : 1;
        unsigned int ERETRY : 1;
        unsigned int PERTRY : 1;
    };
    unsigned long value;
} EESUPP_TypeDef;

unsigned long EEPROM_Read(int address);
void EEPROM_Write(unsigned int address, unsigned long value);
EEPROM_Init_Status EEPROM_Init();
void Save_float_EEPROM(float coordinates[][2],unsigned long number_of_saved_reading);
unsigned long read_coordinates(void);
#endif // GPS_TRACKING_SYSTEM_EEPROM_H