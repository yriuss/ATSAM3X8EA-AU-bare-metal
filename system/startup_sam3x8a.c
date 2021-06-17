#include "sam3x8a.h"

typedef void (*handler_t)(void);

/* Symbols defined in the linker file */
extern uint32_t _sfixed;
extern uint32_t _efixed;
extern uint32_t _data_flash;
extern uint32_t _data_begin;
extern uint32_t _data_end;
extern uint32_t _bss_begin;
extern uint32_t _bss_end;
extern uint32_t _stack_begin;
extern uint32_t _stack_end;

int main(void);

/* A dummy init function to be used if no other is provided */
void dummy_init_fun(void) {}

/* The three expected init functions: one for the microcontroller,
   another for the board, and the last for user initialization */
void system_init(void) __attribute__ ((weak, alias("dummy_init_fun")));
void board_init(void) __attribute__ ((weak, alias("dummy_init_fun")));
void user_init(void) __attribute__ ((weak, alias("dummy_init_fun")));

/* The default handlers */
void Dummy_Handler(void);
void Reset_Handler(void);

/* Cortex-M3 core handlers */
void NMI_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void HardFault_Handler  ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void MemManage_Handler  ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void BusFault_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void UsageFault_Handler ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SVC_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void DebugMon_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PendSV_Handler     ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SysTick_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));

/* Peripherals handlers */
void SUPC_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void RSTC_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void RTC_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void RTT_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void WDT_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PMC_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void EFC0_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void EFC1_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void UART_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef _SAM3XA_SMC_INSTANCE_
void SMC_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM3XA_SMC_INSTANCE_ */
#ifdef _SAM3XA_SDRAMC_INSTANCE_
void SDRAMC_Handler     ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM3XA_SDRAMC_INSTANCE_ */
void PIOA_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PIOB_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef _SAM3XA_PIOC_INSTANCE_
void PIOC_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM3XA_PIOC_INSTANCE_ */
#ifdef _SAM3XA_PIOD_INSTANCE_
void PIOD_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM3XA_PIOD_INSTANCE_ */
#ifdef _SAM3XA_PIOE_INSTANCE_
void PIOE_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM3XA_PIOE_INSTANCE_ */
#ifdef _SAM3XA_PIOF_INSTANCE_
void PIOF_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM3XA_PIOF_INSTANCE_ */
void USART0_Handler     ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void USART1_Handler     ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void USART2_Handler     ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef _SAM3XA_USART3_INSTANCE_
void USART3_Handler     ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM3XA_USART3_INSTANCE_ */
void HSMCI_Handler      ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TWI0_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TWI1_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SPI0_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef _SAM3XA_SPI1_INSTANCE_
void SPI1_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM3XA_SPI1_INSTANCE_ */
void SSC_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC0_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC1_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC2_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC3_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC4_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC5_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef _SAM3XA_TC2_INSTANCE_
void TC6_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC7_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC8_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM3XA_TC2_INSTANCE_ */
void PWM_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void ADC_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void DACC_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void DMAC_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void UOTGHS_Handler     ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TRNG_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef _SAM3XA_EMAC_INSTANCE_
void EMAC_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAM3XA_EMAC_INSTANCE_ */
void CAN0_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void CAN1_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));

/* Exception Table */
__attribute__ ((section(".vectors")))
const handler_t exception_table[] = {
    (handler_t) (&_stack_end),
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,
    0,
    0,
    0,
    SVC_Handler,
    DebugMon_Handler,
    0,
    PendSV_Handler,
    SysTick_Handler,

    /* Configurable interrupts */
    SUPC_Handler,    /*  0  Supply Controller */
    RSTC_Handler,    /*  1  Reset Controller */
    RTC_Handler,     /*  2  Real Time Clock */
    RTT_Handler,     /*  3  Real Time Timer */
    WDT_Handler,     /*  4  Watchdog Timer */
    PMC_Handler,     /*  5  PMC */
    EFC0_Handler,    /*  6  EFC 0 */
    EFC1_Handler,    /*  7  EFC 1 */
    UART_Handler,    /*  8  UART */
#ifdef _SAM3XA_SMC_INSTANCE_
    SMC_Handler,     /*  9  SMC */
#else
    (0UL),           /*  9 Reserved */
#endif /* _SAM3XA_SMC_INSTANCE_ */
#ifdef _SAM3XA_SDRAMC_INSTANCE_
    SDRAMC_Handler,  /* 10  SDRAMC */
#else
    (0UL),           /* 10 Reserved */
#endif /* _SAM3XA_SDRAMC_INSTANCE_ */
    PIOA_Handler,    /* 11 Parallel IO Controller A */
    PIOB_Handler,    /* 12 Parallel IO Controller B */
#ifdef _SAM3XA_PIOC_INSTANCE_
    PIOC_Handler,    /* 13 Parallel IO Controller C */
#else
    (0UL),           /* 13 Reserved */
#endif /* _SAM3XA_PIOC_INSTANCE_ */
#ifdef _SAM3XA_PIOD_INSTANCE_
    PIOD_Handler,    /* 14 Parallel IO Controller D */
#else
    (0UL),           /* 14 Reserved */
#endif /* _SAM3XA_PIOD_INSTANCE_ */
#ifdef _SAM3XA_PIOE_INSTANCE_
    PIOE_Handler,    /* 15 Parallel IO Controller E */
#else
    (0UL),           /* 15 Reserved */
#endif /* _SAM3XA_PIOE_INSTANCE_ */
#ifdef _SAM3XA_PIOF_INSTANCE_
    PIOF_Handler,    /* 16 Parallel IO Controller F */
#else
    (0UL),           /* 16 Reserved */
#endif /* _SAM3XA_PIOF_INSTANCE_ */
    USART0_Handler,  /* 17 USART 0 */
    USART1_Handler,  /* 18 USART 1 */
    USART2_Handler,  /* 19 USART 2 */
#ifdef _SAM3XA_USART3_INSTANCE_
    USART3_Handler,  /* 20 USART 3 */
#else
    (0UL),           /* 20 Reserved */
#endif /* _SAM3XA_USART3_INSTANCE_ */
    HSMCI_Handler,   /* 21 MCI */
    TWI0_Handler,    /* 22 TWI 0 */
    TWI1_Handler,    /* 23 TWI 1 */
    SPI0_Handler,    /* 24 SPI 0 */
#ifdef _SAM3XA_SPI1_INSTANCE_
    SPI1_Handler,    /* 25 SPI 1 */
#else
    (0UL),           /* 25 Reserved */
#endif /* _SAM3XA_SPI1_INSTANCE_ */
    SSC_Handler,     /* 26 SSC */
    TC0_Handler,     /* 27 Timer Counter 0 */
    TC1_Handler,     /* 28 Timer Counter 1 */
    TC2_Handler,     /* 29 Timer Counter 2 */
    TC3_Handler,     /* 30 Timer Counter 3 */
    TC4_Handler,     /* 31 Timer Counter 4 */
    TC5_Handler,     /* 32 Timer Counter 5 */
#ifdef _SAM3XA_TC2_INSTANCE_
    TC6_Handler,     /* 33 Timer Counter 6 */
    TC7_Handler,     /* 34 Timer Counter 7 */
    TC8_Handler,     /* 35 Timer Counter 8 */
#else
    (0UL),           /* 33 Reserved */
    (0UL),           /* 34 Reserved */
    (0UL),           /* 35 Reserved */
#endif /* _SAM3XA_TC2_INSTANCE_ */
    PWM_Handler,     /* 36 PWM */
    ADC_Handler,     /* 37 ADC controller */
    DACC_Handler,    /* 38 DAC controller */
    DMAC_Handler,    /* 39 DMA Controller */
    UOTGHS_Handler,  /* 40 USB OTG High Speed */
    TRNG_Handler,    /* 41 True Random Number Generator */
#ifdef _SAM3XA_EMAC_INSTANCE_
    EMAC_Handler,    /* 42 Ethernet MAC */
#else
    (0UL),           /* 42 Reserved */
#endif /* _SAM3XA_EMAC_INSTANCE_ */
    CAN0_Handler,    /* 43 CAN Controller 0 */
    CAN1_Handler     /* 44 CAN Controller 1 */
};

/**
 * \brief This is the code that gets called on processor reset.
 * To initialize the device, and call the main() routine.
 */
void Reset_Handler(void) {
    uint32_t *src, *dst;

    /* Initialize the relocate segment */
    src = &_data_flash;
    dst = &_data_begin;

    if (src != dst)
        while (dst < &_data_end)
            *dst++ = *src++;

    /* Clear the zero segment */
    for (dst = &_bss_begin; dst < &_bss_end;)
        *dst++ = 0;

    /* Set the vector table base address */
    src = (uint32_t *) & _sfixed;
    SCB->VTOR = ((uint32_t) src & SCB_VTOR_TBLOFF_Msk);

    if (((uint32_t) src >= IRAM0_ADDR) && ((uint32_t) src < NFC_RAM_ADDR))
        SCB->VTOR |= (1UL) << SCB_VTOR_TBLBASE_Pos;

    system_init();
    board_init();
    user_init();

    /* Branch to main function */
    main();

    /* Infinite loop */
    while (1)
        ;
}

/**
 * \brief Default interrupt handler for unused IRQs.
 */
void Dummy_Handler(void) {
    while (1) {
    }
}
