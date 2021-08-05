/*
*   This is a simple abstraction layer for ADC1 in STM32F103C8T6.
*/
#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include "sam3x8a.h"
#include "reactor.h"

#define ADC_NBR_CH_IN_GROUP  16


#ifdef ADC_USE_DMA
#undef ADC_USE_DMA
#define ADC_USE_DMA 1
#define ADC_DMA_PRIO DMA_PRIO_VERY_HIGH
#endif /* ADC_USE_DMA */

#define BUF_SZ_LOG 5
#define BUF_SZ (1U << BUF_SZ_LOG)
#define BUF_SZ_MSK (BUF_SZ - 1)
#define BUF_MIDPOINT_MSK (BUF_SZ/2 - 1)

typedef struct {
    /* Channels to be converted. To make the struct size a multiple of
       4 bytes, make the number of elements equal to 4*m + 2 >= number
       of channels */
    uint8_t ch[((ADC_NBR_CH_IN_GROUP + 3) & ~0x3)];
    uint8_t len;        /* Number of active channels in conversion
                                        group */
    uint8_t seq_order;  /* Define if the channels are sampled in the
                           order given by the above array (!= 0) or in
                           numeric order (== 0).  For example, if the
                           channels are given as 3, 1, 2, 0 and this
                           flag is 0, then the channels are sampled in
                           the order 0, 1, 2 and 3.  If the flag is
                           nonzero, the sampling order is 3, 1, 2,
                           0. */
} adc_group_t;

//TODO: add external trigger configuration
typedef uint16_t adc_buffer_t;
/* The data type below is not needed for the SAM3X microcontroller,
   but is here to allow for future portability */
typedef enum {
              X
} adc_config_sr_t;

typedef struct {
    adc_group_t group;      /* ADC Group configuration */

    /*adc_config_sr_t sr[ADC_NBR_CH_IN_GROUP]; /* Sample Rate of each
                                                channel. Not used in
                                                SAM3X */
    uint8_t align_mode;    /* Right or Left word alignment. Not used
                              in SAM3X */
    uint8_t freerun_mode;  /* Continuous (!= 0) or Single mode */
    uint8_t trigger;       /* Set ADC Trigger source (0 disables it) */
    uint8_t lowres_mode;   /* Low resolution mode on (!= 0) or off */
    uint8_t prescaler;     /* Prescaler value */
    uint8_t startup;       /* Coded number (dependent on the
                              microcontroller) of clock periods to
                              wait at startup */
    uint8_t settling;      /* Number of clock periods to wait for
                              settling */
    uint8_t tracking;      /* Number of clock periods to wait for
                              tracking */
    uint8_t transfer;      /* Number of clock periods to wait for
                              transfer */
    uint8_t different_chann; /* Different gain and offset
                               characteristics for each channel */
    uint8_t temp_on;       /* Turns on the temperature sensor */

    reactor_cb_t group_conv_cb;    /* End of Group conversion callback */
    reactor_cb_t eoc_injected_cb;  /*  */
    reactor_cb_t watchdog_cb;      /* TODO: callback for future
                                      implementation of watchdog */
#if ADC_USE_DMA == 1
    reactor_cb_t half_transfer_cb;
    reactor_cb_t full_transfer_cb;
#endif
} adc_config_t;

typedef struct {
    ADC_TypeDef *dev;               /* ADC device */

    adc_buffer_t *buf;   /* Storage of ADC readings. Provide a
                              * buffer with a minimum size:
                              * sizeof(adc_sample_t) (conversion
                              * group's length)
                              */
    uint16_t buflen;
    uint8_t eoc;
    reactor_cb_t group_conv_cb;    /* End of Group conversion callback */
    reactor_cb_t eoc_injected_cb;  /* Not applicable to SAM3X. Only
                                      here for portability */
    reactor_cb_t watchdog_cb;      /* Not applicable to SAM3X. Only
                                      here for portability */
#if ADC_USE_DMA == 1
    reactor_cb_t half_transfer_cb;
    reactor_cb_t full_transfer_cb;

    uint32_t dma_channel;          /* DMA channel for this ADC */
#endif
} adc_t;

extern adc_t ADCD1;

void adc_init(void);
int adc_start(adc_t* drv,adc_config_t* adc_config);
void adc_config_sample_rate(adc_t *drv, int n, adc_config_sr_t sr);
//int adc_start(adc_t *drv, adc_config_t *config);
int adc_start_conversion(adc_t *drv, uint16_t* buf, uint16_t n);
int adc_stop_conversion(adc_t *drv);
int adc_stop(adc_t *drv);

/* General macros */
#define _GPIO_CRL_CNF(n)        (unsigned long) (0x3UL << (2 + (n) * 4))
#define _GPIO_CRL_MODE(n)       (unsigned long) (0x3UL << ((n) * 4))

#define SET_REG_BITS_AT_MASK(REG, MASK, VAL, POS)   ( (REG) = (((REG) & ~(MASK)) | (((VAL) << (POS)) & (MASK))) )

/* Macro to Configure ADC pins */
#define adc_set_gpio(n) \
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
#define adc_enable_EOC_irq(ADC_DEV)    \
    do {    \
        __NVIC_EnableIRQ(ADC1_2_IRQn);  \
        (ADC_DEV)->CR1 |= ADC_CR1_EOCIE; \
    } while(0);

#define ADC_EVT_EOC(ADC_DEV)                    ( (ADC_DEV)->SR & ADC_SR_EOC )
#define adc_disable_irq()                       ( __NVIC_DisableIRQ(ADC1_2_IRQn) )
#define adc_read(ADC_DEV)                       ( (ADC_DEV)->LCDR & 0xFFF)
#endif
