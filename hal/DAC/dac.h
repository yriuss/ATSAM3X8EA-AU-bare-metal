/*
*   This is a simple abstraction layer for DAC1 in STM32F103C8T6.
*/
#ifndef DAC_H
#define DAC_H

#include <stdint.h>
#include "sam3x8a.h"
#include "reactor.h"

#ifdef DAC_USE_DMA
#undef DAC_USE_DMA
#define DAC_USE_DMA 1
#define DAC_DMA_PRIO DMA_PRIO_VERY_HIGH
#endif /* DAC_USE_DMA */

#if 0
//TODO: add external trigger configuration
typedef uint16_t dac_sample_t;
/* The data type below is not needed for the SAM3X microcontroller,
   but is here to allow for future portability */
typedef enum {
              X
} dac_config_sr_t;

typedef struct {
    reactor_cb_t group_conv_cb;    /* End of Group conversion callback */
#if DAC_USE_DMA == 1
    reactor_cb_t half_transfer_cb;
    reactor_cb_t full_transfer_cb;
#endif
} dac_config_t;

typedef struct {
    DAC_TypeDef *dev;               /* DAC device */

    dac_sample_t *samples;   /* Storage of DAC readings. Provide a
                              * buffer with a minimum size:
                              * sizeof(dac_sample_t) (conversion
                              * group's length)
                              */
    int buflen;
    reactor_cb_t group_conv_cb;    /* End of Group conversion callback */
#if DAC_USE_DMA == 1
    reactor_cb_t half_transfer_cb;
    reactor_cb_t full_transfer_cb;

    uint32_t dma_channel;          /* DMA channel for this DAC */
#endif
} dac_t;

extern dac_t DACD1;

void dac_init(void);
void dac_config_sample_rate(dac_t *drv, int n, dac_config_sr_t sr);
int dac_start(dac_t *drv, dac_config_t *config);
int dac_start_conversion(dac_t *drv, uint16_t* buf, uint16_t n);
int dac_stop_conversion(dac_t *drv);
int dac_stop(dac_t *drv);
#endif
/* General macros */
#define _GPIO_CRL_CNF(n)        (unsigned long) (0x3UL << (2 + (n) * 4))
#define _GPIO_CRL_MODE(n)       (unsigned long) (0x3UL << ((n) * 4))

#define SET_REG_BITS_AT_MASK(REG, MASK, VAL, POS)   ( (REG) = (((REG) & ~(MASK)) | (((VAL) << (POS)) & (MASK))) )

/* Macro to Configure DAC pins */
#define dac_set_gpio(n) \
    do {    \
        if (n <= 7) {   \
            RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; \
            GPIOA->CRL &= ~(_GPIO_CRL_CNF(n)) & ~(_GPIO_CRL_MODE(n)); \
        } else if (n <= 9) {    \
            RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; \
            GPIOB->CRL &= ~(_GPIO_CRL_CNF(n-8)) & ~(_GPIO_CRL_MODE(n-8)); \
        } else if (n <= 15) {   \
            RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; \
            GPIOC->CRL &= ~(_GPIO_CRL_CNF(n-10)) & ~(_GPIO_CRL_MODE(n-10)); \
        }   \
    } while(0)

/* Conversion macros */
#define dac_enable_EOC_irq(DAC_DEV)    \
    do {    \
        __NVIC_EnableIRQ(DAC1_2_IRQn);  \
        (DAC_DEV)->CR1 |= DAC_CR1_EOCIE; \
    } while(0);

#define DAC_EVT_EOC(DAC_DEV)                    ( (DAC_DEV)->SR & DAC_SR_EOC )
#define dac_disable_irq()                       ( __NVIC_DisableIRQ(DAC1_2_IRQn) )
#define dac_write(value)                       ( DAC->CDR = value )
#define dac_set(CH) do {                                     \
                        DAC->MR = 0x200000|((CH & 0x2) << 16);  \
                        DAC->CHER = CH;                      \
                    } while(0);
#define DAC_CH1 DAC_CHER_CH1
#define DAC_CH0 DAC_CHER_CH0


#endif
