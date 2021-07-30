/**
******************************************************************************
* @file    stm32f103xb.h
* @author
* @brief   CMSIS Cortex-M3 Device Peripheral Access Layer Header File.
*          This file contains all the peripheral register's definitions, bits
*          definitions and memory mapping for SAM3X devices.
*
*          This file contains:
*           - Data structures and the address mapping for all peripherals
*           - Peripheral's registers declarations and bits definition
*           - Macros to access peripheral's registers hardware
*
******************************************************************************
*/


/** @addtogroup CMSIS
 * @{
 */

#ifndef __SAM3X8A_H
#define __SAM3X8A_H
#ifdef __cplusplus
extern "C" {
#endif
#ifdef FOOL_EMACS
}
#endif

#define BIT0 (1 << 0)
#define BIT1 (1 << 1)
#define BIT2 (1 << 2)
#define BIT3 (1 << 3)
#define BIT4 (1 << 4)
#define BIT5 (1 << 5)
#define BIT6 (1 << 6)
#define BIT7 (1 << 7)
#define BIT8 (1 << 8)
#define BIT9 (1 << 9)
#define BIT10 (1 << 10)
#define BIT11 (1 << 11)
#define BIT12 (1 << 12)
#define BIT13 (1 << 13)
#define BIT14 (1 << 14)
#define BIT15 (1 << 15)
#define BIT16 (1 << 16)
#define BIT17 (1 << 17)
#define BIT18 (1 << 18)
#define BIT19 (1 << 19)
#define BIT20 (1 << 20)
#define BIT21 (1 << 21)
#define BIT22 (1 << 22)
#define BIT23 (1 << 23)
#define BIT24 (1 << 24)
#define BIT25 (1 << 25)
#define BIT26 (1 << 26)
#define BIT27 (1 << 27)
#define BIT28 (1 << 28)
#define BIT29 (1 << 29)
#define BIT30 (1 << 30)
#define BIT31 (1 << 31)


/**
 * @brief Configuration of the Cortex-M3 Processor and Core Peripherals
 */
#define __CM3_REV                  0x0200U  /*!< Core Revision r2p0                           */
#define __MPU_PRESENT              0U       /*!< Other STM32 devices does not provide an MPU  */
#define __NVIC_PRIO_BITS           4U       /*!< STM32 uses 4 Bits for the Priority Levels    */
#define __Vendor_SysTickConfig     0U       /*!< Set to 1 if different SysTick Config is used */




#define IRAM0_ADDR      (0x20000000u) /**< Internal RAM 0 base address */
#define NFC_RAM_ADDR    (0x20100000u) /**< NAND Flash Controller RAM base address */



/**
 * @brief STM32F10x Interrupt Number Definition, according to the selected device
 *        in @ref Library_configuration_section
 */

/*!< Interrupt Number Definition */
/*  */
typedef enum {
              /******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
    NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                             */
    HardFault_IRQn              = -13,    /*!< 3 Cortex-M3 Hard Fault Interrupt                     */
    MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt              */
    BusFault_IRQn               = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                      */
    UsageFault_IRQn             = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                    */
    SVCall_IRQn                 = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                       */
    DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt                 */
    PendSV_IRQn                 = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                       */
    SysTick_IRQn                = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                   */

    /******  SAM3X specific Interrupt Numbers ******/
    /******  From page 38 of the datasheet    ******/
    SUPC_IRQn                   = 0,
    RSTC_IRQn                   = 1,
    RTC_IRQn                    = 2,
    RTT_IRQn                    = 3,
    WDG_IRQn                    = 4,
    PMC_IRQn                    = 5,
    EEFC0_IRQn                  = 6,
    EEFC1_IRQn                  = 7,
    UART_IRQn                   = 8,
#if 0
    _IRQn                   = 9,
    _IRQn                   = 10,
#endif
    PIOA_IRQn                   = 11,
    PIOB_IRQn                   = 12,
    PIOC_IRQn                   = 13,
    PIOD_IRQn                   = 14,
    PIOE_IRQn                   = 15,
    PIOF_IRQn                   = 16,
    USART0_IRQn                 = 17,
    USART1_IRQn                 = 18,
    USART2_IRQn                 = 19,
    USART3_IRQn                 = 20,
#if 0
    _IRQn                   = 21,
    _IRQn                   = 22,
    _IRQn                   = 23,
    _IRQn                   = 24,
    _IRQn                   = 25,
    _IRQn                   = 26,
    _IRQn                   = 27,
    _IRQn                   = 28,
    _IRQn                   = 29,
    _IRQn                   = 30,
    _IRQn                   = 31,
    _IRQn                   = 32,
    _IRQn                   = 33,
    _IRQn                   = 34,
    _IRQn                   = 35,
    _IRQn                   = 36,
#endif
    ADC_IRQn                = 37,
    DAC_IRQn                = 38,
#if 0
    _IRQn                   = 39,
    _IRQn                   = 40,
    _IRQn                   = 41,
    _IRQn                   = 42,
    _IRQn                   = 43,
    _IRQn                   = 44,
#endif
} IRQn_Type;

    /**
     * @}
     */

#include "core_cm3.h"
#include <stdint.h>

typedef volatile uint32_t RoReg; /**< Read only 32-bit register */
typedef volatile uint32_t WoReg; /**< Write only 32-bit register */
typedef volatile uint32_t RwReg; /**< Read-Write 32-bit register */

typedef struct {
    RwReg EEFC_FMR; /**< \brief (Efc Offset: 0x00) EEFC Flash Mode Register */
    WoReg EEFC_FCR; /**< \brief (Efc Offset: 0x04) EEFC Flash Command Register */
    RoReg EEFC_FSR; /**< \brief (Efc Offset: 0x08) EEFC Flash Status Register */
    RoReg EEFC_FRR; /**< \brief (Efc Offset: 0x0C) EEFC Flash Result Register */
} Efc_TypeDef;

typedef struct {
    WoReg PMC_SCER;      /**< \brief (Pmc Offset: 0x0000) System Clock Enable Register */
    WoReg PMC_SCDR;      /**< \brief (Pmc Offset: 0x0004) System Clock Disable Register */
    RoReg PMC_SCSR;      /**< \brief (Pmc Offset: 0x0008) System Clock Status Register */
    RoReg Reserved1[1];
    WoReg PMC_PCER0;     /**< \brief (Pmc Offset: 0x0010) Peripheral Clock Enable Register 0 */
    WoReg PMC_PCDR0;     /**< \brief (Pmc Offset: 0x0014) Peripheral Clock Disable Register 0 */
    RoReg PMC_PCSR0;     /**< \brief (Pmc Offset: 0x0018) Peripheral Clock Status Register 0 */
    RwReg CKGR_UCKR;     /**< \brief (Pmc Offset: 0x001C) UTMI Clock Register */
    RwReg CKGR_MOR;      /**< \brief (Pmc Offset: 0x0020) Main Oscillator Register */
    RoReg CKGR_MCFR;     /**< \brief (Pmc Offset: 0x0024) Main Clock Frequency Register */
    RwReg CKGR_PLLAR;    /**< \brief (Pmc Offset: 0x0028) PLLA Register */
    RoReg Reserved2[1];
    RwReg PMC_MCKR;      /**< \brief (Pmc Offset: 0x0030) Master Clock Register */
    RoReg Reserved3[1];
    RwReg PMC_USB;       /**< \brief (Pmc Offset: 0x0038) USB Clock Register */
    RoReg Reserved4[1];
    RwReg PMC_PCK[3];    /**< \brief (Pmc Offset: 0x0040) Programmable Clock 0 Register */
    RoReg Reserved5[5];
    WoReg PMC_IER;       /**< \brief (Pmc Offset: 0x0060) Interrupt Enable Register */
    WoReg PMC_IDR;       /**< \brief (Pmc Offset: 0x0064) Interrupt Disable Register */
    RoReg PMC_SR;        /**< \brief (Pmc Offset: 0x0068) Status Register */
    RoReg PMC_IMR;       /**< \brief (Pmc Offset: 0x006C) Interrupt Mask Register */
    RwReg PMC_FSMR;      /**< \brief (Pmc Offset: 0x0070) Fast Startup Mode Register */
    RwReg PMC_FSPR;      /**< \brief (Pmc Offset: 0x0074) Fast Startup Polarity Register */
    WoReg PMC_FOCR;      /**< \brief (Pmc Offset: 0x0078) Fault Output Clear Register */
    RoReg Reserved6[26];
    RwReg PMC_WPMR;      /**< \brief (Pmc Offset: 0x00E4) Write Protect Mode Register */
    RoReg PMC_WPSR;      /**< \brief (Pmc Offset: 0x00E8) Write Protect Status Register */
    RoReg Reserved7[5];
    WoReg PMC_PCER1;     /**< \brief (Pmc Offset: 0x0100) Peripheral Clock Enable Register 1 */
    WoReg PMC_PCDR1;     /**< \brief (Pmc Offset: 0x0104) Peripheral Clock Disable Register 1 */
    RoReg PMC_PCSR1;     /**< \brief (Pmc Offset: 0x0108) Peripheral Clock Status Register 1 */
    RwReg PMC_PCR;       /**< \brief (Pmc Offset: 0x010C) Peripheral Control Register */
} Pmc_TypeDef;


/**
 * @brief General Purpose I/O
 */
typedef struct {
    WoReg PER;
    WoReg PDR;
    RoReg PSR;
    RoReg reserved1;
    WoReg OER;
    WoReg ODR;
    RoReg OSR;
    RoReg reserved2;
    WoReg IFER;
    WoReg IFDR;
    RoReg IFSR;
    RoReg reserved3;
    WoReg SODR;
    WoReg CODR;
    RwReg ODSR;
    RoReg PDSR;
    WoReg IER;
    WoReg IDR;
    RoReg IMR;
    RoReg ISR;
    WoReg MDER;
    WoReg MDDR;
    RoReg MDSR;
    RoReg reserved4;
    WoReg PUDR;
    WoReg PUER;
    RoReg PUSR;
    RoReg reserved5;
    RwReg ABSR;
    RoReg reserved6[3];
    WoReg SCIFSR;
    WoReg DIFSR;
    RoReg IFDGSR;
    RwReg SCDR;
    RoReg reserved7[4];
    WoReg OWER;
    WoReg OWDR;
    RoReg OWSR;
    RoReg reserved8;
    WoReg AIMER;
    WoReg AIMDR;
    RoReg AIMMR;
    RoReg reserved9;
    WoReg ESR;
    WoReg LSR;
    RoReg ELSR;
    RoReg reserved10;
    WoReg FELLSR;
    WoReg REHLSR;
    RoReg FRLHSR;
    RoReg reserved11;
    RoReg LOCKSR;
    RwReg WPMR;
    RoReg WPSR;
} GPIO_TypeDef;

typedef struct {
  WoReg WDT_CR; /**< \brief (Wdt Offset: 0x00) Control Register */
  RwReg WDT_MR; /**< \brief (Wdt Offset: 0x04) Mode Register */
  RoReg WDT_SR; /**< \brief (Wdt Offset: 0x08) Status Register */
} Wdt_TypeDef;


typedef struct {
    WoReg CR;
    RwReg MR;
    WoReg IER;
    WoReg IDR;
    RoReg IMR;
    RoReg SR;
    RoReg RHR;
    WoReg THR;
    RwReg BRGR;
} UART_TypeDef;

typedef struct {
    WoReg CR;
    RwReg MR;
    RwReg SEQR1;
    RwReg SEQR2;
    WoReg CHER;
    WoReg CHDR;
    RoReg CHSR;
    RoReg Reserved1;
    RoReg LCDR;
    WoReg IER;
    WoReg IDR;
    RoReg IMR;
    RoReg ISR;
    RoReg Reserved2;
    RoReg Reserved3;
    RoReg OVER;
    RwReg EMR;
    RwReg CWR;
    RwReg CGR;
    RwReg COR;
    RoReg CDR[16];
    RoReg Reserved4;
    RwReg ACR;
    RoReg Reserved5[11];
    RoReg Reserved6[8];
    RwReg WPMR;
    RoReg WPSR;
} ADC_TypeDef;

typedef struct {
    WoReg CR;
    RwReg MR;
    RoReg Reserved1;
    RoReg Reserved2;
    WoReg CHER;
    WoReg CHDR;
    RoReg CHSR;
    RoReg Reserved3;
    WoReg CDR;
    WoReg IER;
    WoReg IDR;
    RoReg IMR;
    RoReg ISR;
    RwReg ACR;
    RwReg WPMR;
    RoReg WPSR;
} DAC_TypeDef;

/* */
#define PMC   ((Pmc_TypeDef *)0x400E0600U) /**< \brief (PMC       ) Base Address */
#define EFC0  ((Efc_TypeDef *)0x400E0A00U) /**< \brief (EFC0      ) Base Address */
#define EFC1  ((Efc_TypeDef *)0x400E0C00U) /**< \brief (EFC1      ) Base Address */
#define WDT   ((Wdt_TypeDef *)0x400E1A50U) /**< \brief (WDT       ) Base Address */
#define GPIOA ((GPIO_TypeDef *) 0x400E0E00U)
#define GPIOB ((GPIO_TypeDef *) 0x400E1000U)
#define GPIOC ((GPIO_TypeDef *) 0x400E1200U)
#define GPIOD ((GPIO_TypeDef *) 0x400E1400U)
#define UART  ((UART_TypeDef *) 0x400E0800U)
/* TODO: Implement USART structure. For now, using the UART
   structure */
#define USART0 ((UART_TypeDef *)  0x40098000U)
#define USART1 ((UART_TypeDef *)  0x4009C000U)
#define USART2 ((UART_TypeDef *)  0x400A0000U)
#define USART3 ((UART_TypeDef *)  0x400A4000U)
#define ADC    ((ADC_TypeDef *)   0x400C0000U)
#define DAC    ((DAC_TypeDef *)   0x400C8000U)


#define EEFC_FMR_FWS_Pos 8
#define EEFC_FMR_FWS_Msk (0xfu << EEFC_FMR_FWS_Pos) /**< \brief (EEFC_FMR) Flash Wait State */
#define EEFC_FMR_FWS(value) ((EEFC_FMR_FWS_Msk & ((value) << EEFC_FMR_FWS_Pos)))

#define CKGR_MOR_MOSCXTEN (0x1u << 0) /**< \brief (CKGR_MOR) Main Crystal Oscillator Enable */
#define CKGR_MOR_MOSCXTBY (0x1u << 1) /**< \brief (CKGR_MOR) Main Crystal Oscillator Bypass */
#define CKGR_MOR_MOSCRCEN (0x1u << 3) /**< \brief (CKGR_MOR) Main On-Chip RC Oscillator Enable */
#define CKGR_MOR_MOSCRCF_Pos 4
#define CKGR_MOR_MOSCRCF_Msk (0x7u << CKGR_MOR_MOSCRCF_Pos) /**< \brief (CKGR_MOR) Main On-Chip RC Oscillator Frequency Selection */
#define CKGR_MOR_MOSCRCF_4_MHz (0x0u << CKGR_MOR_MOSCRCF_Pos) /**< \brief (CKGR_MOR) The Fast RC Oscillator Frequency is at 4 MHz (default) */
#define CKGR_MOR_MOSCRCF_8_MHz (0x1u << CKGR_MOR_MOSCRCF_Pos) /**< \brief (CKGR_MOR) The Fast RC Oscillator Frequency is at 8 MHz */
#define CKGR_MOR_MOSCRCF_12_MHz (0x2u << CKGR_MOR_MOSCRCF_Pos) /**< \brief (CKGR_MOR) The Fast RC Oscillator Frequency is at 12 MHz */
#define CKGR_MOR_MOSCXTST_Pos 8
#define CKGR_MOR_MOSCXTST_Msk (0xffu << CKGR_MOR_MOSCXTST_Pos) /**< \brief (CKGR_MOR) Main Crystal Oscillator Start-up Time */
#define CKGR_MOR_MOSCXTST(value) ((CKGR_MOR_MOSCXTST_Msk & ((value) << CKGR_MOR_MOSCXTST_Pos)))
#define CKGR_MOR_KEY_Pos 16
#define CKGR_MOR_KEY_Msk (0xffu << CKGR_MOR_KEY_Pos) /**< \brief (CKGR_MOR) Password */
#define CKGR_MOR_KEY(value) ((CKGR_MOR_KEY_Msk & ((value) << CKGR_MOR_KEY_Pos)))
#define CKGR_MOR_MOSCSEL (0x1u << 24) /**< \brief (CKGR_MOR) Main Oscillator Selection */
#define CKGR_MOR_CFDEN (0x1u << 25) /**< \brief (CKGR_MOR) Clock Failure Detector Enable */
#define CKGR_MOR_KEY_VALUE (0X37)

#define SYS_CKGR_MOR_KEY_VALUE	CKGR_MOR_KEY(0x37UL)
#define PMC_SR_MOSCSELS_Pos 16
#define PMC_SR_MOSCSELS (0x1u << PMC_SR_MOSCSELS_Pos)
#define PMC_SR_MOSCRCS_Pos 17
#define PMC_SR_MOSCRCS (0x1u << PMC_SR_MOSCRCS_Pos)
#define PMC_SR_MCKRDY_Pos 3
#define PMC_SR_MCKRDY (0x1u << PMC_SR_MCKRDY_Pos)
#define PMC_PCER0_UART   (1U << UART_IRQn)
#define PMC_PCER0_USART0 (1U << USART0_IRQn)
#define PMC_PCER0_USART1 (1U << USART1_IRQn)
#define PMC_PCER0_USART2 (1U << USART2_IRQn)
#define PMC_PCER0_USART3 (1U << USART3_IRQn)
#define PMC_PCER0_PIOA   (1U << PIOA_IRQn)
#define PMC_PCER0_PIOB   (1U << PIOB_IRQn)
#define PMC_PCER0_PIOC   (1U << PIOC_IRQn)
#define PMC_PCER0_PIOD   (1U << PIOD_IRQn)
#define PMC_PCER1_ADC    (1U << (ADC_IRQn - 32))
#define PMC_PCER1_DAC    (1U << (DAC_IRQn - 32))

#define PMC_PCDR1_ADC    (1U << (ADC_IRQn - 32))

#define CKGR_PLLAR_ONE (0x1u << 29)

#define CKGR_PLLAR_DIVA_Pos 0
#define CKGR_PLLAR_DIVA_Msk (0xffu << CKGR_PLLAR_DIVA_Pos) /**< \brief (CKGR_PLLAR) Divider */
#define CKGR_PLLAR_DIVA(value) ((CKGR_PLLAR_DIVA_Msk & ((value) << CKGR_PLLAR_DIVA_Pos)))
#define CKGR_PLLAR_PLLACOUNT_Pos 8
#define CKGR_PLLAR_PLLACOUNT_Msk (0x3fu << CKGR_PLLAR_PLLACOUNT_Pos) /**< \brief (CKGR_PLLAR) PLLA Counter */
#define CKGR_PLLAR_PLLACOUNT(value) ((CKGR_PLLAR_PLLACOUNT_Msk & ((value) << CKGR_PLLAR_PLLACOUNT_Pos)))
#define CKGR_PLLAR_MULA_Pos 16
#define CKGR_PLLAR_MULA_Msk (0x7ffu << CKGR_PLLAR_MULA_Pos) /**< \brief (CKGR_PLLAR) PLLA Multiplier */
#define CKGR_PLLAR_MULA(value) ((CKGR_PLLAR_MULA_Msk & ((value) << CKGR_PLLAR_MULA_Pos)))
#define CKGR_PLLAR_ONE (0x1u << 29) /**< \brief (CKGR_PLLAR) Must Be Set to 1 */


#define SYS_BOARD_PLLAR (CKGR_PLLAR_ONE                                 \
                         | CKGR_PLLAR_MULA(0x6UL)                       \
                         | CKGR_PLLAR_PLLACOUNT(0x3fUL)                 \
                         | CKGR_PLLAR_DIVA(0x1UL))

#define PMC_MCKR_PRES_Pos 4
#define PMC_MCKR_PRES_Msk (0x7 << PMC_MCKR_PRES_Pos)
#define PMC_MCKR_PRES_CLK_1 0
#define PMC_MCKR_PRES_CLK_2 (0x1u << PMC_MCKR_PRES_Pos)
#define PMC_MCKR_PRES_CLK_4 (0x2u << PMC_MCKR_PRES_Pos)
#define PMC_MCKR_PRES_CLK_8 (0x3u << PMC_MCKR_PRES_Pos)
#define PMC_MCKR_PRES_CLK_16 (0x4u << PMC_MCKR_PRES_Pos)
#define PMC_MCKR_PRES_CLK_32 (0x5u << PMC_MCKR_PRES_Pos)
#define PMC_MCKR_PRES_CLK_64 (0x6u << PMC_MCKR_PRES_Pos)
#define PMC_MCKR_PRES_CLK_3 (0x7u << PMC_MCKR_PRES_Pos)

#define PMC_MCKR_CSS_PLLA_CLK (0x2u << 0)
#define SYS_BOARD_MCKR      (PMC_MCKR_PRES_CLK_1 | PMC_MCKR_CSS_PLLA_CLK)
#define SYS_BOARD_OSCOUNT   (CKGR_MOR_MOSCXTST(0x8))

#define PMC_MCKR_CSS_Pos 0
#define PMC_MCKR_CSS_Msk (0x3 << PMC_MCKR_CSS_Pos)
#define PMC_MCKR_CSS_MAIN_CLK (0x1 << PMC_MCKR_CSS_Pos)
#define PMC_SR_MOSCXTS (0x1u << 0)
#define PMC_SR_LOCKA (0x1u << 1)

#define WDT_MR_WDV_Pos 0
#define WDT_MR_WDV_Msk (0xFFFUL << WDT_MR_WDV_Pos)
#define WDT_MR_WDFIEN_Pos 12
#define WDT_MR_WDFIEN     (1UL << WDT_MR_WDFIEN_Pos)
#define WDT_MR_WDFIEN_Msk WDT_MR_WDFIEN
#define WDT_MR_WDRSTEN_Pos 13
#define WDT_MR_WDRSTEN     (1UL << WDT_MR_WDRSTEN_Pos)
#define WDT_MR_WDRSTEN_Msk WDT_MR_WDRSTEN
#define WDT_MR_WDRPROC_Pos 14
#define WDT_MR_WDRPROC     (1UL << WDT_MR_WDRPROC_Pos)
#define WDT_MR_WDRPROC_Msk WDT_MR_WDRPROC
#define WDT_MR_WDDIS_Pos 15
#define WDT_MR_WDDIS     (1UL << WDT_MR_WDDIS_Pos)
#define WDT_MR_WDDIS_Msk WDT_MR_WDDIS
#define WDT_MR_WDD_Pos 16
#define WDT_MR_WDD_Msk (0xFFFUL << WDT_MR_WDD_Pos)
#define WDT_MR_WDDBGHLT_Pos 28
#define WDT_MR_WDDBGHLT     (1UL << WDT_MR_WDDBGHLT_Pos)
#define WDT_MR_WDDBGHLT_Msk WDT_MR_WDDBGHLT
#define WDT_MR_WDIDLEHLT_Pos 29
#define WDT_MR_WDIDLEHLT     (1UL << WDT_MR_WDIDLEHLT_Pos)
#define WDT_MR_WDIDLEHLT_Msk WDT_MR_WDIDLEHLT

#define UART_CR_RSTRX_Pos  2
#define UART_CR_RSTRX      (1U << UART_CR_RSTRX_Pos)
#define UART_CR_RSTTX_Pos  3
#define UART_CR_RSTTX      (1U << UART_CR_RSTTX_Pos)
#define UART_CR_RXEN_Pos   4
#define UART_CR_RXEN       (1U << UART_CR_RXEN_Pos)
#define UART_CR_RXDIS_Pos  5
#define UART_CR_RXDIS      (1U << UART_CR_RXDIS_Pos)
#define UART_CR_TXEN_Pos   6
#define UART_CR_TXEN       (1U << UART_CR_TXEN_Pos)
#define UART_CR_TXDIS_Pos  7
#define UART_CR_TXDIS      (1U << UART_CR_TXDIS_Pos)
#define UART_CR_RSTSTA_Pos 8
#define UART_CR_RSTSTA     (1U << UART_CR_RSTSTA_Pos)

#define UART_MR_PAR_Pos 9
#define UART_MR_PAR_Msk   (0X7U << UART_MR_PAR_Pos)
#define UART_MR_EVEN_PAR  (0X0U << UART_MR_PAR_Pos)
#define UART_MR_ODD_PAR   (0X1U << UART_MR_PAR_Pos)
#define UART_MR_SPACE_PAR (0X2U << UART_MR_PAR_Pos)
#define UART_MR_MARK_PAR  (0X3U << UART_MR_PAR_Pos)
#define UART_MR_NO_PAR    (0X4U << UART_MR_PAR_Pos)
#define UART_MR_CHMODE_Pos 14
#define UART_MR_CHMODE_Msk         (0x3U << UART_MR_CHMODE_Pos)
#define UART_MR_CHMODE_NORMAL      (0x0U << UART_MR_CHMODE_Pos)
#define UART_MR_CHMODE_AUTO        (0x1U << UART_MR_CHMODE_Pos)
#define UART_MR_CHMODE_LOCAL_LOOP  (0x2U << UART_MR_CHMODE_Pos)
#define UART_MR_CHMODE_REMOTE_LOOP (0x3U << UART_MR_CHMODE_Pos)
#define UART_IMR_RXRDY_Pos   0
#define UART_IMR_RXRDY       (1U << UART_IMR_RXRDY_Pos)
#define UART_IMR_TXRDY_Pos   1
#define UART_IMR_TXRDY       (1U << UART_IMR_TXRDY_Pos)
#define UART_IMR_ENDRX_Pos   3
#define UART_IMR_ENDRX       (1U << UART_IMR_ENDRX_Pos)
#define UART_IMR_ENDTX_Pos   4
#define UART_IMR_ENDTX       (1U << UART_IMR_ENDTX_Pos)
#define UART_IMR_OVRE_Pos    5
#define UART_IMR_OVRE        (1U << UART_IMR_OVRE_Pos)
#define UART_IMR_FRAME_Pos   6
#define UART_IMR_FRAME       (1U << UART_IMR_FRAME_Pos)
#define UART_IMR_PARE_Pos    7
#define UART_IMR_PARE        (1U << UART_IMR_PARE_Pos)
#define UART_IMR_TXEMPTY_Pos 9
#define UART_IMR_TXEMPTY     (1U << UART_IMR_TXEMPTY_Pos)
#define UART_IMR_TXBUFE_Pos  11
#define UART_IMR_TXBUFE      (1U << UART_IMR_TXBUFE_Pos)
#define UART_IMR_RXBUFF_Pos  12
#define UART_IMR_RXBUFF      (1U << UART_IMR_RXBUFF_Pos)
#define UART_SR_RXRDY    UART_IMR_RXRDY
#define UART_SR_TXRDY    UART_IMR_TXRDY
#define UART_SR_ENDRX    UART_IMR_ENDRX
#define UART_SR_ENDTX    UART_IMR_ENDTX
#define UART_SR_OVRE     UART_IMR_OVRE
#define UART_SR_FRAME    UART_IMR_FRAME
#define UART_SR_PARE     UART_IMR_PARE
#define UART_SR_TXEMPTY  UART_IMR_TXEMPTY
#define UART_SR_TXBUFE   UART_IMR_TXBUFE
#define UART_SR_RXBUFF   UART_IMR_RXBUFF

#define ADC_CR_SWRST_Pos  0
#define ADC_CR_SWRST      (1 << ADC_CR_SWRST_Pos)
#define ADC_CR_START_Pos  1
#define ADC_CR_START      (1 << ADC_CR_START_Pos)
#define ADC_MR_TRGEN_Pos  0
#define ADC_MR_TRGEN      (1 << ADC_MR_TRGEN_Pos)
#define ADC_MR_TRGSEL_Pos 1
#define ADC_MR_TRGSEL_Msk (0x7 << ADC_MR_TRGSEL_Pos)
#define ADC_MR_TRGSEL_TRIG0 (0x0 << ADC_MR_TRGSEL_Pos)
#define ADC_MR_TRGSEL_TRIG1 (0x1 << ADC_MR_TRGSEL_Pos)
#define ADC_MR_TRGSEL_TRIG2 (0x2 << ADC_MR_TRGSEL_Pos)
#define ADC_MR_TRGSEL_TRIG3 (0x3 << ADC_MR_TRGSEL_Pos)
#define ADC_MR_TRGSEL_TRIG4 (0x4 << ADC_MR_TRGSEL_Pos)
#define ADC_MR_TRGSEL_TRIG5 (0x5 << ADC_MR_TRGSEL_Pos)
#define ADC_MR_TRGSEL_ADCTRG ADC_MR_TRGSEL_TRIG0
#define ADC_MR_TRGSEL_TIOA0  ADC_MR_TRGSEL_TRIG1
#define ADC_MR_TRGSEL_TIOA1  ADC_MR_TRGSEL_TRIG2
#define ADC_MR_TRGSEL_TIOA2  ADC_MR_TRGSEL_TRIG3
#define ADC_MR_TRGSEL_PWM0   ADC_MR_TRGSEL_TRIG4
#define ADC_MR_TRGSEL_PWM1   ADC_MR_TRGSEL_TRIG5
#define ADC_MR_LOWRES_Pos 4
#define ADC_MR_LOWRES     (1 << ADC_MR_LOWRES_Pos)
#define ADC_MR_SLEEP_Pos  5
#define ADC_MR_SLEEP      (1 << ADC_MR_SLEEP_Pos)
#define ADC_MR_FWUP_Pos   6
#define ADC_MR_FWUP       (1 << ADC_MR_FWUP_Pos)
#define ADC_MR_FREERUN_Pos 7
#define ADC_MR_FREERUN     (1 << ADC_MR_FREERUN_Pos)
#define ADC_MR_PRESCAL_Pos 8
#define ADC_MR_PRESCAL_Msk (0xFF << ADC_MR_PRESCAL_Pos)
#define ADC_MR_STARTUP_Pos 16
#define ADC_MR_STARTUP_Msk (0xF << ADC_MR_STARTUP_Pos)
#define ADC_MR_STARTUP_SUT0 (0x0 << ADC_MR_STARTUP_Pos)
#define ADC_MR_STARTUP_SUT8 (0x1 << ADC_MR_STARTUP_Pos)
#define ADC_MR_STARTUP_SUT16 (0x2 << ADC_MR_STARTUP_Pos)
#define ADC_MR_STARTUP_SUT24 (0x3 << ADC_MR_STARTUP_Pos)
#define ADC_MR_STARTUP_SUT64 (0x4 << ADC_MR_STARTUP_Pos)
#define ADC_MR_STARTUP_SUT80 (0x5 << ADC_MR_STARTUP_Pos)
#define ADC_MR_STARTUP_SUT96 (0x6 << ADC_MR_STARTUP_Pos)
#define ADC_MR_STARTUP_SUT112 (0x7 << ADC_MR_STARTUP_Pos)
#define ADC_MR_STARTUP_SUT512 (0x8 << ADC_MR_STARTUP_Pos)
#define ADC_MR_STARTUP_SUT576 (0x9 << ADC_MR_STARTUP_Pos)
#define ADC_MR_STARTUP_SUT640 (0xA << ADC_MR_STARTUP_Pos)
#define ADC_MR_STARTUP_SUT704 (0xB << ADC_MR_STARTUP_Pos)
#define ADC_MR_STARTUP_SUT768 (0xC << ADC_MR_STARTUP_Pos)
#define ADC_MR_STARTUP_SUT832 (0xD << ADC_MR_STARTUP_Pos)
#define ADC_MR_STARTUP_SUT896 (0xE << ADC_MR_STARTUP_Pos)
#define ADC_MR_STARTUP_SUT960 (0xF << ADC_MR_STARTUP_Pos)
#define ADC_MR_SETTLING_Pos 20
#define ADC_MR_SETTLING_Msk (0x3 << ADC_MR_SETTLING_Pos)
#define ADC_MR_SETTLING_AST3 (0x0 << ADC_MR_SETTLING_Pos)
#define ADC_MR_SETTLING_AST5 (0x1 << ADC_MR_SETTLING_Pos)
#define ADC_MR_SETTLING_AST9 (0x2 << ADC_MR_SETTLING_Pos)
#define ADC_MR_SETTLING_AST17 (0x3 << ADC_MR_SETTLING_Pos)
#define ADC_MR_ANACH_Pos  23
#define ADC_MR_ANACH      (1 << ADC_MR_ANACH_Pos)
#define ADC_MR_TRACKTIM_Pos 24
#define ADC_MR_TRACKTIM_Msk (0x7 << ADC_MR_TRACKTIM_Pos)
#define ADC_MR_TRANSFER_Pos 28
#define ADC_MR_TRANSFER_Msk (0x7 << ADC_MR_TRANSFER_Pos)
#define ADC_MR_USEQ_Pos    31
#define ADC_MR_USEQ        (1 << ADC_MR_USEQ_Pos)
#define ADC_SEQR_USCH_Msk  0xF
#define ADC_LCDR_LDATA_Pos 0
#define ADC_LCDR_LDATA_Msk (0xFFF << ADC_LCDR_LDATA_Pos)
#define ADC_LCDR_CHNB_Pos  12
#define ADC_LCDR_CHNB_Msk  (0xF << ADC_LCDR_CHNB_Pos)
#define ADC_IER_DRDY_Pos   24
#define ADC_IER_DRDY       (1 << ADC_IER_DRDY_Pos)
#define ADC_IER_GOVRE_Pos  25
#define ADC_IER_GOVRE      (1 << ADC_IER_GOVRE_Pos)
#define ADC_IER_COMPE_Pos  26
#define ADC_IER_COMPE      (1 << ADC_IER_COMPE_Pos)
#define ADC_IER_ENDRX_Pos  27
#define ADC_IER_ENDRX      (1 << ADC_IER_ENDRX_Pos)
#define ADC_IER_RXBUF_Pos  28
#define ADC_IER_RXBUF      (1 << ADC_IER_RXBUF_Pos)
#define ADC_IDR_DRDY       ADC_IER_DRDY
#define ADC_IDR_GOVRE      ADC_IER_GOVRE
#define ADC_IDR_COMPE      ADC_IER_COMPE
#define ADC_IDR_ENDRX      ADC_IER_ENDRX
#define ADC_IDR_RXBUF      ADC_IER_RXBUF
#define ADC_IMR_DRDY       ADC_IER_DRDY
#define ADC_IMR_GOVRE      ADC_IER_GOVRE
#define ADC_IMR_COMPE      ADC_IER_COMPE
#define ADC_IMR_ENDRX      ADC_IER_ENDRX
#define ADC_IMR_RXBUF      ADC_IER_RXBUF
#define ADC_ISR_DRDY       ADC_IER_DRDY
#define ADC_ISR_GOVRE      ADC_IER_GOVRE
#define ADC_ISR_COMPE      ADC_IER_COMPE
#define ADC_ISR_ENDRX      ADC_IER_ENDRX
#define ADC_ISR_RXBUF      ADC_IER_RXBUF
/* TODO: the constants related to the registers EMR, CGR, WPMR and
   WPSR below still need to be defined */
#define ADC_EMR__Pos 24
#define ADC_EMR__Msk (0x7 << ADC_MR__Pos)
/* End of TODO */
#define ADC_CDR_DATA_Pos  0
#define ADC_CDR_DATA_Msk  (0xFFF << ADC_CDR_DATA_Pos)
#define ADC_ACR_TSON_Pos  4
#define ADC_ACR_TSON      (1 << ADC_ACR_TSON_Pos)
#define ADC_ACR_IBCTL_Pos 8
#define ADC_ACR_IBCTL_Msk (0x3 << ADC_ACR_IBCTL_Pos)

#define DAC_CR_SWRST_Pos  0
#define DAC_CR_SWRST      (1 << DAC_CR_SWRST_Pos)
#define DAC_MR_TRGEN_Pos  0
#define DAC_MR_TRGEN      (1 << DAC_MR_TRGEN_Pos)
#define DAC_MR_TRGSEL_Pos 1
#define DAC_MR_TRGSEL_Msk (0x7 << DAC_MR_TRGSEL_Pos)
#define DAC_MR_TRGSEL_TRIG0 (0x0 << DAC_MR_TRGSEL_Pos)
#define DAC_MR_TRGSEL_TRIG1 (0x1 << DAC_MR_TRGSEL_Pos)
#define DAC_MR_TRGSEL_TRIG2 (0x2 << DAC_MR_TRGSEL_Pos)
#define DAC_MR_TRGSEL_TRIG3 (0x3 << DAC_MR_TRGSEL_Pos)
#define DAC_MR_TRGSEL_TRIG4 (0x4 << DAC_MR_TRGSEL_Pos)
#define DAC_MR_TRGSEL_TRIG5 (0x5 << DAC_MR_TRGSEL_Pos)
#define DAC_MR_TRGSEL_EXTTRG DAC_MR_TRGSEL_TRIG0
#define DAC_MR_TRGSEL_TIOA0  DAC_MR_TRGSEL_TRIG1
#define DAC_MR_TRGSEL_TIOA1  DAC_MR_TRGSEL_TRIG2
#define DAC_MR_TRGSEL_TIOA2  DAC_MR_TRGSEL_TRIG3
#define DAC_MR_TRGSEL_PWM0   DAC_MR_TRGSEL_TRIG4
#define DAC_MR_TRGSEL_PWM1   DAC_MR_TRGSEL_TRIG5
#define DAC_MR_WORD_Pos 4
#define DAC_MR_WORD     (1 << DAC_MR_WORD_Pos)
#define DAC_MR_SLEEP_Pos  5
#define DAC_MR_SLEEP      (1 << DAC_MR_SLEEP_Pos)
#define DAC_MR_FWUP_Pos   6
#define DAC_MR_FWUP       (1 << DAC_MR_FWUP_Pos)
#define DAC_MR_REFRESH_Pos 8
#define DAC_MR_REFRESH_Msk (0xFF << DAC_MR_REFRESH_Pos)
#define DAC_MR_USER_SEL_Pos 16
#define DAC_MR_USER_SEL_Msk  (0x3 << DAC_MR_USER_SEL_Pos)
#define DAC_MR_USER_SEL_CH0 (0x0 << DAC_MR_USER_SEL_Pos)
#define DAC_MR_USER_SEL_CH1 (0x1 << DAC_MR_USER_SEL_Pos)
#define DAC_MR_TAG_Pos  20
#define DAC_MR_TAG      (0x1 << DAC_MR_TAG_Pos)
#define DAC_MR_MAXS_Pos   21
#define DAC_MR_MAXS       (1 << DAC_MR_MAXS_Pos)
#define DAC_MR_STARTUP_Pos 24
#define DAC_MR_STARTUP_Msk (0x3F << DAC_MR_STARTUP_Pos)
#define DAC_CHER_CH0_Pos    0
#define DAC_CHER_CH0        (1 << DAC_CHER_CH0_Pos)
#define DAC_CHER_CH1_Pos    1
#define DAC_CHER_CH1        (1 << DAC_CHER_CH1_Pos)
#define DAC_CHDR_CH0_Pos    0
#define DAC_CHDR_CH0        (1 << DAC_CHDR_CH0_Pos)
#define DAC_CHDR_CH1_Pos    1
#define DAC_CHDR_CH1        (1 << DAC_CHDR_CH1_Pos)
#define DAC_CHSR_CH0_Pos    0
#define DAC_CHSR_CH0        (1 << DAC_CHSR_CH0_Pos)
#define DAC_CHSR_CH1_Pos    1
#define DAC_CHSR_CH1        (1 << DAC_CHSR_CH1_Pos)
#define DAC_IER_TXRDY_Pos   0
#define DAC_IER_TXRDY       (1 << DAC_IER_TXRDY_Pos)
#define DAC_IER_EOC_Pos     1
#define DAC_IER_EOC         (1 << DAC_IER_EOC_Pos)
#define DAC_IER_ENDTX_Pos   2
#define DAC_IER_ENDTX       (1 << DAC_IER_ENDTX_Pos)
#define DAC_IER_TXBUFE_Pos  3
#define DAC_IER_TXBUFE      (1 << DAC_IER_TXBUFE_Pos)
#define DAC_IDR_TXRDY      DAC_IER_TXRDY
#define DAC_IDR_EOC        DAC_IER_EOC
#define DAC_IDR_ENDTX      DAC_IER_ENDTX
#define DAC_IDR_TXBUFE     DAC_IER_TXBUFE
#define DAC_IMR_TXRDY      DAC_IER_TXRDY
#define DAC_IMR_EOC        DAC_IER_EOC
#define DAC_IMR_ENDTX      DAC_IER_ENDTX
#define DAC_IMR_TXBUFE     DAC_IER_TXBUFE
#define DAC_ISR_TXRDY      DAC_IER_TXRDY
#define DAC_ISR_EOC        DAC_IER_EOC
#define DAC_ISR_ENDTX      DAC_IER_ENDTX
#define DAC_ISR_TXBUFE     DAC_IER_TXBUFE


#define code_adc_mr_settling(n) (((n) << ADC_MR_SETTLING_Pos) & \
                                 ADC_MR_SETTLING_Msk)
#define code_adc_mr_tracking(n) (((n) << ADC_MR_TRACKTIM_Pos) & \
                                 ADC_MR_TRACKTIM_Msk)
#define code_adc_mr_transfer(n) (((n) << ADC_MR_TRANSFER_Pos) & \
                                 ADC_MR_TRANSFER_Msk)
#define code_adc_mr_startup(n)  (((n) << ADC_MR_STARTUP_Pos) &  \
                                 ADC_MR_STARTUP_Msk)
#define code_adc_mr_prescaler(n) (((n) << ADC_MR_PRESCAL_Pos) & \
                                  ADC_MR_PRESCAL_Msk)

#define code_dacc_mr_startup(n)  (((n) << DAC_MR_STARTUP_Pos) &  \
                                  DAC_MR_STARTUP_Msk)


#if 0
    /**
     * @brief DMA Controller
     */

#define DMA_NBR_CHANNELS 7

typedef struct {
    uint32_t CCR;
    uint32_t CNDTR;
    uint32_t CPAR;
    uint32_t CMAR;
    uint32_t reserved;
} DMA_Channel_TypeDef;

typedef struct {
    uint32_t ISR;
    uint32_t IFCR;
    DMA_Channel_TypeDef channels[DMA_NBR_CHANNELS];
} DMA_TypeDef;



    /**
     * @brief External Interrupt/Event Controller
     */

typedef struct {
    uint32_t IMR;
    uint32_t EMR;
    uint32_t RTSR;
    uint32_t FTSR;
    uint32_t SWIER;
    uint32_t PR;
} EXTI_TypeDef;

    /**
     * @brief Inter Integrated Circuit Interface
     */

typedef struct {
    uint32_t CR1;
    uint32_t CR2;
    uint32_t OAR1;
    uint32_t OAR2;
    uint32_t DR;
    uint32_t SR1;
    uint32_t SR2;
    uint32_t CCR;
    uint32_t TRISE;
} I2C_TypeDef;

    /**
     * @brief TIM Timers
     */
typedef struct {
    uint32_t CR1;             /*!< TIM control register 1,                      Address offset: 0x00 */
    uint32_t CR2;             /*!< TIM control register 2,                      Address offset: 0x04 */
    uint32_t SMCR;            /*!< TIM slave Mode Control register,             Address offset: 0x08 */
    uint32_t DIER;            /*!< TIM DMA/interrupt enable register,           Address offset: 0x0C */
    uint32_t SR;              /*!< TIM status register,                         Address offset: 0x10 */
    uint32_t EGR;             /*!< TIM event generation register,               Address offset: 0x14 */
    uint32_t CCMR1;           /*!< TIM  capture/compare mode register 1,        Address offset: 0x18 */
    uint32_t CCMR2;           /*!< TIM  capture/compare mode register 2,        Address offset: 0x1C */
    uint32_t CCER;            /*!< TIM capture/compare enable register,         Address offset: 0x20 */
    uint32_t CNT;             /*!< TIM counter register,                        Address offset: 0x24 */
    uint32_t PSC;             /*!< TIM prescaler register,                      Address offset: 0x28 */
    uint32_t ARR;             /*!< TIM auto-reload register,                    Address offset: 0x2C */
    uint32_t RCR;             /*!< TIM  repetition counter register,            Address offset: 0x30 */
    uint32_t CCR1;            /*!< TIM capture/compare register 1,              Address offset: 0x34 */
    uint32_t CCR2;            /*!< TIM capture/compare register 2,              Address offset: 0x38 */
    uint32_t CCR3;            /*!< TIM capture/compare register 3,              Address offset: 0x3C */
    uint32_t CCR4;            /*!< TIM capture/compare register 4,              Address offset: 0x40 */
    uint32_t BDTR;            /*!< TIM break and dead-time register,            Address offset: 0x44 */
    uint32_t DCR;             /*!< TIM DMA control register,                    Address offset: 0x48 */
    uint32_t DMAR;            /*!< TIM DMA address for full transfer register,  Address offset: 0x4C */
    uint32_t OR;              /*!< TIM option register,                         Address offset: 0x50 */
} TIM_TypeDef;
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SAM3X8A_H */
