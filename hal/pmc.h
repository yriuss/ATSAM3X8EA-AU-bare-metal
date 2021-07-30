#ifndef PMC_H
#define PMC_H

#include "core_cm3.h"

#if 0
#define PMC_DMA1_CLK_ENABLE()   do {			\
    __IO uint32_t tmpreg;				\
    PMC->AHBENR |= PMC_AHBENR_DMA1EN;			\
    /* Delay after an PMC peripheral clock enabling */	\
    tmpreg = PMC->AHBENR & PMC_AHBENR_DMA1EN;	\
		      (void)tmpreg;			\
		      } while(0U)

#define PMC_SRAM_CLK_ENABLE()   do {			\
    __IO uint32_t tmpreg;				\
    PMC->AHBENR |= PMC_AHBENR_SRAMEN;			\
    /* Delay after an PMC peripheral clock enabling */	\
    tmpreg = PMC->AHBENR & PMC_AHBENR_SRAMEN;	\
		      (void)tmpreg;			\
		      } while(0U)

#define PMC_FLITF_CLK_ENABLE()   do {			\
    __IO uint32_t tmpreg;				\
    PMC->AHBENR |= PMC_AHBENR_FLITFEN;			\
    /* Delay after an PMC peripheral clock enabling */	\
    tmpreg = PMC->AHBENR & PMC_AHBENR_FLITFEN;	\
		      (void)tmpreg;			\
		      } while(0U)

#define PMC_CRC_CLK_ENABLE()   do {			\
    __IO uint32_t tmpreg;				\
    PMC->AHBENR |= PMC_AHBENR_CRCEN;			\
    /* Delay after an PMC peripheral clock enabling */	\
    tmpreg = PMC->AHBENR & PMC_AHBENR_CRCEN;	\
		      (void)tmpreg;			\
		      } while(0U)

#define PMC_AFIO_CLK_ENABLE()   do {				\
	__IO uint32_t tmpreg;					\
	PMC->APB2ENR |= PMC_APB2ENR_AFIOEN;			\
	/* Delay after an PMC peripheral clock enabling */	\
	tmpreg = PMC->APB2ENR & PMC_APB2ENR_AFIOEN;		\
	(void)tmpreg;						\
    } while(0U)

#define PMC_TIM1_CLK_ENABLE()   do {				\
	__IO uint32_t tmpreg;					\
	PMC->APB2ENR |= PMC_APB2ENR_TIM1EN;			\
	/* Delay after an PMC peripheral clock enabling */	\
	tmpreg = PMC->APB2ENR & PMC_APB2ENR_TIM1EN;		\
	(void)tmpreg;						\
    } while(0U)

#define PMC_TIM2_CLK_ENABLE()   do {				\
	__IO uint32_t tmpreg;					\
	PMC->APB1ENR |= PMC_APB1ENR_TIM2EN;			\
	/* Delay after an PMC peripheral clock enabling */	\
	tmpreg = PMC->APB1ENR & PMC_APB1ENR_TIM2EN;		\
	(void)tmpreg;						\
    } while(0U)

#define PMC_TIM3_CLK_ENABLE()   do {				\
	__IO uint32_t tmpreg;					\
	PMC->APB1ENR |= PMC_APB1ENR_TIM3EN;			\
	/* Delay after an PMC peripheral clock enabling */	\
	tmpreg = PMC->APB1ENR & PMC_APB1ENR_TIM3EN;		\
	(void)tmpreg;						\
    } while(0U)

#define PMC_SPI1_CLK_ENABLE()   do {				\
	__IO uint32_t tmpreg;					\
	PMC->APB2ENR |= PMC_APB2ENR_SPI1EN;			\
	/* Delay after an PMC peripheral clock enabling */	\
	tmpreg = PMC->APB2ENR & PMC_APB2ENR_SPI1EN;		\
	(void)tmpreg;						\
    } while(0U)
#endif

#define PMC_UART_CLK_ENABLE()    (PMC->PMC_PCER0 = PMC_PCER0_UART)
#define PMC_USART0_CLK_ENABLE()  (PMC->PMC_PCER0 = PMC_PCER0_USART0)
#define PMC_USART1_CLK_ENABLE()  (PMC->PMC_PCER0 = PMC_PCER0_USART1)
#define PMC_USART2_CLK_ENABLE()  (PMC->PMC_PCER0 = PMC_PCER0_USART2)
#define PMC_USART3_CLK_ENABLE()  (PMC->PMC_PCER0 = PMC_PCER0_USART3)
#define PMC_GPIOA_CLK_ENABLE()   (PMC->PMC_PCER0 = PMC_PCER0_PIOA)
#define PMC_GPIOB_CLK_ENABLE()   (PMC->PMC_PCER0 = PMC_PCER0_PIOB)
#define PMC_GPIOC_CLK_ENABLE()   (PMC->PMC_PCER0 = PMC_PCER0_PIOC)
#define PMC_GPIOD_CLK_ENABLE()   (PMC->PMC_PCER0 = PMC_PCER0_PIOD)
#define PMC_ADC_CLK_ENABLE()     (PMC->PMC_PCER1 = PMC_PCER1_ADC)
#define PMC_DAC_CLK_ENABLE()     (PMC->PMC_PCER1 = PMC_PCER1_DAC)

#if 0
#define PMC_WWDG_CLK_ENABLE()   do {				\
	__IO uint32_t tmpreg;					\
	PMC->APB1ENR |= PMC_APB1ENR_WWDGEN;			\
	/* Delay after an PMC peripheral clock enabling */	\
	tmpreg = PMC->APB1ENR & PMC_APB1ENR_WWDGEN;		\
	(void)tmpreg;						\
    } while(0U)

#define PMC_I2C1_CLK_ENABLE()   do {				\
	__IO uint32_t tmpreg;					\
	PMC->APB1ENR |= PMC_APB1ENR_I2C1EN;			\
	/* Delay after an PMC peripheral clock enabling */	\
	tmpreg = PMC->APB1ENR & PMC_APB1ENR_I2C1EN;		\
	(void)tmpreg;						\
    } while(0U)

#define PMC_BKP_CLK_ENABLE()   do {				\
	__IO uint32_t tmpreg;					\
	PMC->APB1ENR |= PMC_APB1ENR_BKPEN;			\
	/* Delay after an PMC peripheral clock enabling */	\
	tmpreg = PMC->APB1ENR & PMC_APB1ENR_BKPEN;		\
	(void)tmpreg;						\
    } while(0U)

#define PMC_PWR_CLK_ENABLE()   do {				\
	__IO uint32_t tmpreg;					\
	PMC->APB1ENR |= PMC_APB1ENR_PWREN;			\
	/* Delay after an PMC peripheral clock enabling */	\
	tmpreg = PMC->APB1ENR & PMC_APB1ENR_PWREN;		\
	(void)tmpreg;						\
    } while(0U)

#define PMC_TIM4_CLK_ENABLE()   do {				\
	__IO uint32_t tmpreg;					\
	PMC->APB1ENR |= PMC_APB1ENR_TIM4EN;			\
	/* Delay after an PMC peripheral clock enabling */	\
	tmpreg = PMC->APB1ENR & PMC_APB1ENR_TIM4EN;		\
	(void)tmpreg;						\
    } while(0U)

#define PMC_SPI2_CLK_ENABLE()   do {				\
	__IO uint32_t tmpreg;					\
	PMC->APB1ENR |= PMC_APB1ENR_SPI2EN;			\
	/* Delay after an PMC peripheral clock enabling */	\
	tmpreg = PMC->APB1ENR & PMC_APB1ENR_SPI2EN;		\
	(void)tmpreg;						\
    } while(0U)

#define PMC_I2C2_CLK_ENABLE()   do {				\
	__IO uint32_t tmpreg;					\
	PMC->APB1ENR |= PMC_APB1ENR_I2C2EN;			\
	/* Delay after an PMC peripheral clock enabling */	\
	tmpreg = PMC->APB1ENR & PMC_APB1ENR_I2C2EN;		\
	(void)tmpreg;						\
    } while(0U)
#endif

#if 0
#define PMC_DMA1_CLK_DISABLE()      (PMC->AHBENR = ~(PMC_AHBENR_DMA1EN))
#define PMC_SRAM_CLK_DISABLE()      (PMC->AHBENR = ~(PMC_AHBENR_SRAMEN))
#define PMC_FLITF_CLK_DISABLE()     (PMC->AHBENR = ~(PMC_AHBENR_FLITFEN))
#define PMC_CRC_CLK_DISABLE()       (PMC->AHBENR = ~(PMC_AHBENR_CRCEN))

#define PMC_TIM1_CLK_DISABLE()      (PMC->APB2ENR = ~(PMC_APB2ENR_TIM1EN))
#define PMC_TIM2_CLK_DISABLE()      (PMC->APB1ENR = ~(PMC_APB1ENR_TIM2EN))
#define PMC_TIM3_CLK_DISABLE()      (PMC->APB1ENR = ~(PMC_APB1ENR_TIM3EN))
#define PMC_SPI1_CLK_DISABLE()      (PMC->APB2ENR = ~(PMC_APB2ENR_SPI1EN))
#endif

#define PMC_UART_CLK_DISABLE()   (PMC->PMC_PCDR0 = PMC_PCER0_UART)
#define PMC_USART0_CLK_DISABLE() (PMC->PMC_PCDR0 = PMC_PCER0_USART0)
#define PMC_USART1_CLK_DISABLE() (PMC->PMC_PCDR0 = PMC_PCER0_USART1)
#define PMC_USART2_CLK_DISABLE() (PMC->PMC_PCDR0 = PMC_PCER0_USART2)
#define PMC_USART3_CLK_DISABLE() (PMC->PMC_PCDR0 = PMC_PCER0_USART3)
#define PMC_GPIOA_CLK_DISABLE()  (PMC->PMC_PCDR0 = PMC_PCER0_PIOA)
#define PMC_GPIOB_CLK_DISABLE()  (PMC->PMC_PCDR0 = PMC_PCER0_PIOB)
#define PMC_GPIOC_CLK_DISABLE()  (PMC->PMC_PCDR0 = PMC_PCER0_PIOC)
#define PMC_GPIOD_CLK_DISABLE()  (PMC->PMC_PCDR0 = PMC_PCER0_PIOD)
#define PMC_ADC_CLK_DISABLE()    (PMC->PMC_PCDR1 = PMC_PCER1_ADC)

#if 0
#define PMC_I2C1_CLK_DISABLE()      (PMC->APB1ENR &= ~(PMC_APB1ENR_I2C1EN))
#define PMC_WWDG_CLK_DISABLE()      (PMC->APB1ENR &= ~(PMC_APB1ENR_WWDGEN))
#define PMC_AFIO_CLK_DISABLE()      (PMC->APB2ENR &= ~(PMC_APB2ENR_AFIOEN))

#define PMC_TIM4_CLK_DISABLE()        (PMC->APB1ENR &= ~(PMC_APB1ENR_TIM4EN))
#define PMC_SPI2_CLK_DISABLE()        (PMC->APB1ENR &= ~(PMC_APB1ENR_SPI2EN))
#define PMC_I2C2_CLK_DISABLE()        (PMC->APB1ENR &= ~(PMC_APB1ENR_I2C2EN))
#endif

#endif /* PMC_H */
