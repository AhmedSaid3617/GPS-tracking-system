#ifndef _UART_H_

    #define _UART_H_

    #define UART0_DR_R              (*((volatile unsigned long *)0x4000C000))
    #define UART0_RSR_R             (*((volatile unsigned long *)0x4000C004))
    #define UART0_ECR_R             (*((volatile unsigned long *)0x4000C004))
    #define UART0_FR_R              (*((volatile unsigned long *)0x4000C018))
    #define UART0_ILPR_R            (*((volatile unsigned long *)0x4000C020))
    #define UART0_IBRD_R            (*((volatile unsigned long *)0x4000C024))
    #define UART0_FBRD_R            (*((volatile unsigned long *)0x4000C028))
    #define UART0_LCRH_R            (*((volatile unsigned long *)0x4000C02C))
    #define UART0_CTL_R             (*((volatile unsigned long *)0x4000C030))
    #define UART0_IFLS_R            (*((volatile unsigned long *)0x4000C034))
    #define UART0_IM_R              (*((volatile unsigned long *)0x4000C038))
    #define UART0_RIS_R             (*((volatile unsigned long *)0x4000C03C))
    #define UART0_MIS_R             (*((volatile unsigned long *)0x4000C040))
    #define UART0_ICR_R             (*((volatile unsigned long *)0x4000C044))
    #define UART0_DMACTL_R          (*((volatile unsigned long *)0x4000C048))
    #define UART0_9BITADDR_R        (*((volatile unsigned long *)0x4000C0A4))
    #define UART0_9BITAMASK_R       (*((volatile unsigned long *)0x4000C0A8))
    #define UART0_PP_R              (*((volatile unsigned long *)0x4000CFC0))
    #define UART0_CC_R              (*((volatile unsigned long *)0x4000CFC8))


    //*****************************************************************************
    //
    // UART registers (UART1)
    //
    //*****************************************************************************
    #define UART1_DR_R              (*((volatile unsigned long *)0x4000D000))
    #define UART1_RSR_R             (*((volatile unsigned long *)0x4000D004))
    #define UART1_ECR_R             (*((volatile unsigned long *)0x4000D004))
    #define UART1_FR_R              (*((volatile unsigned long *)0x4000D018))
    #define UART1_ILPR_R            (*((volatile unsigned long *)0x4000D020))
    #define UART1_IBRD_R            (*((volatile unsigned long *)0x4000D024))
    #define UART1_FBRD_R            (*((volatile unsigned long *)0x4000D028))
    #define UART1_LCRH_R            (*((volatile unsigned long *)0x4000D02C))
    #define UART1_CTL_R             (*((volatile unsigned long *)0x4000D030))
    #define UART1_IFLS_R            (*((volatile unsigned long *)0x4000D034))
    #define UART1_IM_R              (*((volatile unsigned long *)0x4000D038))
    #define UART1_RIS_R             (*((volatile unsigned long *)0x4000D03C))
    #define UART1_MIS_R             (*((volatile unsigned long *)0x4000D040))
    #define UART1_ICR_R             (*((volatile unsigned long *)0x4000D044))
    #define UART1_DMACTL_R          (*((volatile unsigned long *)0x4000D048))
    #define UART1_9BITADDR_R        (*((volatile unsigned long *)0x4000D0A4))
    #define UART1_9BITAMASK_R       (*((volatile unsigned long *)0x4000D0A8))
    #define UART1_PP_R              (*((volatile unsigned long *)0x4000DFC0))
    #define UART1_CC_R              (*((volatile unsigned long *)0x4000DFC8))


    //*****************************************************************************
    //
    // System Control registers (SYSCTL)
    //
    //*****************************************************************************

    #define SYSCTL_RCGC0_R          (*((volatile unsigned long *)0x400FE100))
    #define SYSCTL_RCGC1_R          (*((volatile unsigned long *)0x400FE104))
    #define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
    #define SYSCTL_RCGCWD_R         (*((volatile unsigned long *)0x400FE600))
    #define SYSCTL_RCGCTIMER_R      (*((volatile unsigned long *)0x400FE604))
    #define SYSCTL_RCGCGPIO_R       (*((volatile unsigned long *)0x400FE608))
    #define SYSCTL_RCGCDMA_R        (*((volatile unsigned long *)0x400FE60C))
    #define SYSCTL_RCGCHIB_R        (*((volatile unsigned long *)0x400FE614))
    #define SYSCTL_RCGCUART_R       (*((volatile unsigned long *)0x400FE618))
    #define SYSCTL_RCGCSSI_R        (*((volatile unsigned long *)0x400FE61C))
    #define SYSCTL_RCGCI2C_R        (*((volatile unsigned long *)0x400FE620))
    #define SYSCTL_RCGCUSB_R        (*((volatile unsigned long *)0x400FE628))
    #define SYSCTL_RCGCCAN_R        (*((volatile unsigned long *)0x400FE634))
    #define SYSCTL_RCGCADC_R        (*((volatile unsigned long *)0x400FE638))
    #define SYSCTL_RCGCACMP_R       (*((volatile unsigned long *)0x400FE63C))
    #define SYSCTL_RCGCPWM_R        (*((volatile unsigned long *)0x400FE640))
    #define SYSCTL_RCGCQEI_R        (*((volatile unsigned long *)0x400FE644))
    #define SYSCTL_RCGCEEPROM_R     (*((volatile unsigned long *)0x400FE658))
    #define SYSCTL_RCGCWTIMER_R     (*((volatile unsigned long *)0x400FE65C))
    #define SYSCTL_PRGPIO_R         (*((volatile unsigned long *)0x400FEA08))
    #define SYSCTL_PRUART_R         (*((volatile unsigned long *)0x400FEA18))
    //*****************************************************************************
    //
    // GPIO registers (PORTA)
    //
    //*****************************************************************************
    #define GPIO_PORTA_DATA_BITS_R  ((volatile unsigned long *)0x40004000)
    #define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)0x400043FC))
    #define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))
    #define GPIO_PORTA_IS_R         (*((volatile unsigned long *)0x40004404))
    #define GPIO_PORTA_IBE_R        (*((volatile unsigned long *)0x40004408))
    #define GPIO_PORTA_IEV_R        (*((volatile unsigned long *)0x4000440C))
    #define GPIO_PORTA_IM_R         (*((volatile unsigned long *)0x40004410))
    #define GPIO_PORTA_RIS_R        (*((volatile unsigned long *)0x40004414))
    #define GPIO_PORTA_MIS_R        (*((volatile unsigned long *)0x40004418))
    #define GPIO_PORTA_ICR_R        (*((volatile unsigned long *)0x4000441C))
    #define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
    #define GPIO_PORTA_DR2R_R       (*((volatile unsigned long *)0x40004500))
    #define GPIO_PORTA_DR4R_R       (*((volatile unsigned long *)0x40004504))
    #define GPIO_PORTA_DR8R_R       (*((volatile unsigned long *)0x40004508))
    #define GPIO_PORTA_ODR_R        (*((volatile unsigned long *)0x4000450C))
    #define GPIO_PORTA_PUR_R        (*((volatile unsigned long *)0x40004510))
    #define GPIO_PORTA_PDR_R        (*((volatile unsigned long *)0x40004514))
    #define GPIO_PORTA_SLR_R        (*((volatile unsigned long *)0x40004518))
    #define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
    #define GPIO_PORTA_LOCK_R       (*((volatile unsigned long *)0x40004520))
    #define GPIO_PORTA_CR_R         (*((volatile unsigned long *)0x40004524))
    #define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
    #define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))
    #define GPIO_PORTA_ADCCTL_R     (*((volatile unsigned long *)0x40004530))
    #define GPIO_PORTA_DMACTL_R     (*((volatile unsigned long *)0x40004534))

    //*****************************************************************************
    //
    // GPIO registers (PORTB)
    //
    //*****************************************************************************
    #define GPIO_PORTB_DATA_BITS_R  ((volatile unsigned long *)0x40005000)
    #define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC))
    #define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
    #define GPIO_PORTB_IS_R         (*((volatile unsigned long *)0x40005404))
    #define GPIO_PORTB_IBE_R        (*((volatile unsigned long *)0x40005408))
    #define GPIO_PORTB_IEV_R        (*((volatile unsigned long *)0x4000540C))
    #define GPIO_PORTB_IM_R         (*((volatile unsigned long *)0x40005410))
    #define GPIO_PORTB_RIS_R        (*((volatile unsigned long *)0x40005414))
    #define GPIO_PORTB_MIS_R        (*((volatile unsigned long *)0x40005418))
    #define GPIO_PORTB_ICR_R        (*((volatile unsigned long *)0x4000541C))
    #define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
    #define GPIO_PORTB_DR2R_R       (*((volatile unsigned long *)0x40005500))
    #define GPIO_PORTB_DR4R_R       (*((volatile unsigned long *)0x40005504))
    #define GPIO_PORTB_DR8R_R       (*((volatile unsigned long *)0x40005508))
    #define GPIO_PORTB_ODR_R        (*((volatile unsigned long *)0x4000550C))
    #define GPIO_PORTB_PUR_R        (*((volatile unsigned long *)0x40005510))
    #define GPIO_PORTB_PDR_R        (*((volatile unsigned long *)0x40005514))
    #define GPIO_PORTB_SLR_R        (*((volatile unsigned long *)0x40005518))
    #define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
    #define GPIO_PORTB_LOCK_R       (*((volatile unsigned long *)0x40005520))
    #define GPIO_PORTB_CR_R         (*((volatile unsigned long *)0x40005524))
    #define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
    #define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))
    #define GPIO_PORTB_ADCCTL_R     (*((volatile unsigned long *)0x40005530))
    #define GPIO_PORTB_DMACTL_R     (*((volatile unsigned long *)0x40005534))

    //*****************************************************************************
    //
    // GPIO registers (PORTC)
    //
    //*****************************************************************************
    #define GPIO_PORTC_DATA_BITS_R  ((volatile unsigned long *)0x40006000)
    #define GPIO_PORTC_DATA_R       (*((volatile unsigned long *)0x400063FC))
    #define GPIO_PORTC_DIR_R        (*((volatile unsigned long *)0x40006400))
    #define GPIO_PORTC_IS_R         (*((volatile unsigned long *)0x40006404))
    #define GPIO_PORTC_IBE_R        (*((volatile unsigned long *)0x40006408))
    #define GPIO_PORTC_IEV_R        (*((volatile unsigned long *)0x4000640C))
    #define GPIO_PORTC_IM_R         (*((volatile unsigned long *)0x40006410))
    #define GPIO_PORTC_RIS_R        (*((volatile unsigned long *)0x40006414))
    #define GPIO_PORTC_MIS_R        (*((volatile unsigned long *)0x40006418))
    #define GPIO_PORTC_ICR_R        (*((volatile unsigned long *)0x4000641C))
    #define GPIO_PORTC_AFSEL_R      (*((volatile unsigned long *)0x40006420))
    #define GPIO_PORTC_DR2R_R       (*((volatile unsigned long *)0x40006500))
    #define GPIO_PORTC_DR4R_R       (*((volatile unsigned long *)0x40006504))
    #define GPIO_PORTC_DR8R_R       (*((volatile unsigned long *)0x40006508))
    #define GPIO_PORTC_ODR_R        (*((volatile unsigned long *)0x4000650C))
    #define GPIO_PORTC_PUR_R        (*((volatile unsigned long *)0x40006510))
    #define GPIO_PORTC_PDR_R        (*((volatile unsigned long *)0x40006514))
    #define GPIO_PORTC_SLR_R        (*((volatile unsigned long *)0x40006518))
    #define GPIO_PORTC_DEN_R        (*((volatile unsigned long *)0x4000651C))
    #define GPIO_PORTC_LOCK_R       (*((volatile unsigned long *)0x40006520))
    #define GPIO_PORTC_CR_R         (*((volatile unsigned long *)0x40006524))
    #define GPIO_PORTC_AMSEL_R      (*((volatile unsigned long *)0x40006528))
    #define GPIO_PORTC_PCTL_R       (*((volatile unsigned long *)0x4000652C))
    #define GPIO_PORTC_ADCCTL_R     (*((volatile unsigned long *)0x40006530))
    #define GPIO_PORTC_DMACTL_R     (*((volatile unsigned long *)0x40006534))

    void UART0_Init(int Baud_rate);
    void UART1_Init(int Baud_rate);
    void UART0_SendChar(char data);
    char UART0_GetChar(void) ;
    void UART1_SendChar(char data);
    char UART1_GetChar(void);

#endif
