#ifndef GPS_TRACKING_SYSTEM_I2C_H
#define GPS_TRACKING_SYSTEM_I2C_H

#define RCGCI2C ((volatile RCGCI2C_TypeDef*) 0x400FE620)

#define I2CMCR ((volatile I2CMCR_TypeDef *) 0x40020020)
#define I2CMTPR *((volatile unsigned long*) 0x4002000C)
#define I2CMSA *((volatile unsigned long*) 0x40020000)
#define I2CMDR *((volatile unsigned long*) 0x40020008)
#define I2CMCS ((volatile I2CMCS_TypeDef*) 0x40020004)

typedef union I2CMCS_TypeDef {
    struct  {
        unsigned long const
                BUSY: 1,
                ERROR:1,
                ADRACK:1,
                DATACK:1,
                ARBLST:1,
                IDLE:1,
                BUSBSY:1,
                CLKTO:1;
    };

    unsigned long write;
} I2CMCS_TypeDef ;

typedef struct I2CMCR_TypeDef {
    unsigned long
        LPBK: 1,
        : 3,
        MFE:  1,
        SFE:  1,
        GFE:  1;
} I2CMCR_TypeDef;

typedef struct RCGCI2C_TypeDef {
    unsigned long I2C3: 1,
                  I2C2: 1,
                  I2C1: 1,
                  I2C0: 1;
} RCGCI2C_TypeDef;

void I2C_Init();
void I2C_Start(char address);
void I2C_Send(char data);
void I2C_End();

#endif //GPS_TRACKING_SYSTEM_I2C_H
