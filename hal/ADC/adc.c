#include <stdint.h>
#include "sam3x8a.h"
#include "adc.h"
#include "pmc.h"
#include "reactor.h"
#include "uart.h"

#define MAX 1
#if 0
#include "dma.h"
#endif

adc_t ADCD1;


void adc_init(void) {
    ADCD1.dev = ADC;
    ADCD1.buflen = 0;
    ADCD1.group_conv_cb = 0;

#if ADC_USE_DMA == 1
    ADCD1.dma_channel = DMA_ADC1_CHANNEL;
#endif /* ADC_USE_DMA */
}


void ADC_Handler(void) {
    static uint16_t n = 0, samples = 0;
    static uint16_t buf[BUF_SZ];
    static uint16_t eoc = 0;

    buf[n++] = ADC->LCDR & 0xFFF;

    n &= BUF_SZ_MSK;
    if (!(n & BUF_MIDPOINT_MSK) && !eoc) {
        reactor_add_handler(ADCD1.group_conv_cb,
                            (hcos_word_t) (buf + (n ^ (BUF_SZ/2))));
        ADCD1.buf[samples] = ADC->LCDR & 0xFFF;
        if(!(n&BUF_SZ_MSK) && samples < ADCD1.buflen){
            samples++;
        }else{
            if(samples == ADCD1.buflen){
                ADC->IDR = ADC_IDR_DRDY;
            }
        }                
    }
    
}





int adc_start(adc_t* drv,adc_config_t* adc_config) {
    uint8_t i;
    uint32_t cher = 0;

    drv->dev = ADC;
    drv->dev->CR = ADC_CR_SWRST;
    drv->dev->MR = ADC_MR_FREERUN | code_adc_mr_settling(adc_config->settling) |
        code_adc_mr_tracking(adc_config->tracking) | code_adc_mr_transfer(adc_config->transfer) |
        code_adc_mr_prescaler(adc_config->prescaler) | code_adc_mr_startup(adc_config->startup);
    
    drv->dev->ACR = (adc_config->temp_on ? ADC_ACR_TSON : 0);

    drv->dev->SEQR1 = drv->dev->SEQR2 = 0;
    drv->dev->CHDR = 0xFF; /* Disable all channels */
    adc_config->group.len = adc_config->group.len > 16 ? 16 : adc_config->group.len;

    for(i = 0; i < ADC_NBR_CH_IN_GROUP; i++){
        if(adc_config->group.ch[i] != 0)
            cher |= (1 << i);
    }
    
    drv->dev->CHER = cher;


    ADCD1.group_conv_cb   = adc_config->group_conv_cb; // TENHO QUE PENSAR EM OUTRA FORMA
    drv->eoc_injected_cb = adc_config->eoc_injected_cb;
    drv->watchdog_cb     = adc_config->watchdog_cb;

#if ADC_USE_DMA == 1
    drv->half_transfer_cb = adc_config->half_transfer_cb;
    drv->full_transfer_cb = adc_config->full_transfer_cb;
#endif

    NVIC_EnableIRQ(ADC_IRQn);
    NVIC_SetPriority(ADC_IRQn, 3);
    PMC_ADC_CLK_ENABLE();

#if ADC_USE_DMA == 1
    dma_start(&DMAD1);
#endif /* ADC_USE_DMA */
    
    return 0;
}

int adc_start_conversion(adc_t* drv, uint16_t* buf, uint16_t n) {
#if ADC_USE_DMA == 1
    dma_bind_config_t config = {.peripheral_address = (uint32_t) &drv->dev->DR,
				.memory_address = (uint32_t) buf,
				.nbr_transfers = n,
				.mem2mem_flag = 0,
				.priority = DMA_PRIO_VERY_HIGH,
				.peripheral_size = DMA_PER_SIZE_16BITS,
				.memory_size = DMA_MEM_SIZE_16BITS,
				.peripheral_increment = DMA_NO_PER_INCREMENT_MODE,
				.memory_increment = DMA_MEM_INCREMENT_MODE,
				.direction = DMA_FROM_PER_MODE,
				.circular_mode = DMA_CIRCULAR_MODE,
				.half_transfer_cb = drv->half_transfer_cb,
				.full_transfer_cb = drv->full_transfer_cb,
				.error_cb = 0,
				.half_transfer_args = 0,
				.full_transfer_args = 0,
				.error_args = 0,
				.half_transfer_rt_cb = 0,
				.full_transfer_rt_cb = 0,
				.error_rt_cb = 0,
				.half_transfer_rt_args = (hcos_word_t) drv,
				.full_transfer_rt_args = (hcos_word_t) drv,
				.error_rt_args = 0,
    };

    dma_bind(&DMAD1, drv->dma_channel, config);
    drv->dev->CR2 |= ADC_CR2_DMA;
    dma_enable(&DMAD1, drv->dma_channel);
    drv->length = 0;
#else  /* ADC_USE_DMA == FALSE */



    drv->buf = buf;
    drv->buflen = n;
    drv->dev->IDR = 0xFFFFFFFF;

    ADCD1.buflen = n;

    drv->dev->IER = ADC_IER_DRDY;
    drv->dev->CR = ADC_CR_START;
#endif  /* ADC_USE_DMA */

    drv->dev->CR |= ADC_CR_START;

    return 0;
}

int adc_stop_conversion(adc_t *drv) {
#if ADC_USE_DMA != 1
    drv->dev->IDR = 0xFFFFFFFF;
#endif
    drv->dev->CHDR = 0xFFFF;
    drv->dev->MR &= ~(ADC_MR_FREERUN);   // Stop ADC

    /* TODO:  Check the best value to return */
    /* return drv->dev->SR & ? 1 : 0; */
    return 0;
}

int adc_stop(adc_t *drv) {
    adc_stop_conversion(drv);
    PMC_ADC_CLK_DISABLE();

    return 0;
}



#if 0
int adc_start(adc_t *drv, adc_config_t *config) {
    int i;
    int lim;
    int ch;
    uint32_t seqr = 0;
    uint32_t cher = 0;

    /* Reset the ADC to start from zero */
    drv->dev->CR = ADC_CR_SWRST;

    /* TODO: add support to trigger config */
    drv->dev->MR = (config->freerun_mode ? ADC_MR_FREERUN : 0) |
        (config->lowres_mode ? ADC_MR_LOWRES: 0) |
        (config->different_chann ? ADC_MR_ANACH : 0) |
        (config->group.seq_order ? ADC_MR_USEQ : 0) |
        code_adc_mr_settling(config->settling) |
        code_adc_mr_tracking(config->tracking) |
        code_adc_mr_transfer(config->transfer) |
        code_adc_mr_prescaler(config->prescaler) |
        code_adc_mr_startup(config->startup);

    drv->dev->ACR = (config->temp_on ? ADC_ACR_TSON : 0);

    drv->dev->SEQR1 = drv->dev->SEQR2 = 0;
    drv->dev->CHDR = 0xFF; /* Disable all channels */
    config.group.len = config.group.len > 16 ? 16 : config.group.len;
    lim = config.group.len > 8 ? 8 : config.group.len;
    for (i=seqr=ch=0; i<lim; i++) {
        seqr |= ((config.group.ch[i] & 0xF) << (i << 2));
        cher |= (1 << i);
    }
    drv->dev->SEQR1 = seqr;
    for (i=seqr=lim; i<config.group.len; i++) {
        seqr |= ((config.group.ch[i] & 0xF) << ((i - lim) << 2));
        cher |= (1 << i);
    }        
    drv->dev->SEQR2 = seqr;
    drv->dev->CHER  = cher;

    drv->group_conv_cb = config->group_conv_cb;
    drv->eoc_injected_cb = config->eoc_injected_cb;
    drv->watchdog_cb = config->watchdog_cb;
#if ADC_USE_DMA == 1
    drv->half_transfer_cb = config->half_transfer_cb;
    drv->full_transfer_cb = config->full_transfer_cb;
#endif

    drv->samples = 0;
    drv->buflen = 0;

    PMC_ADC_CLK_ENABLE();

#if ADC_USE_DMA == 1
    dma_start(&DMAD1);
#endif /* ADC_USE_DMA */

    return 0;
}

#if ADC_USE_DMA == 1
void adc_full_transfer_cb(hcos_word_t arg) {

}
#endif

int adc_start_conversion(adc_t* drv, uint16_t* buf, uint16_t n) {
#if ADC_USE_DMA == 1
    dma_bind_config_t config = {.peripheral_address = (uint32_t) &drv->dev->DR,
				.memory_address = (uint32_t) buf,
				.nbr_transfers = n,
				.mem2mem_flag = 0,
				.priority = DMA_PRIO_VERY_HIGH,
				.peripheral_size = DMA_PER_SIZE_16BITS,
				.memory_size = DMA_MEM_SIZE_16BITS,
				.peripheral_increment = DMA_NO_PER_INCREMENT_MODE,
				.memory_increment = DMA_MEM_INCREMENT_MODE,
				.direction = DMA_FROM_PER_MODE,
				.circular_mode = DMA_CIRCULAR_MODE,
				.half_transfer_cb = drv->half_transfer_cb,
				.full_transfer_cb = drv->full_transfer_cb,
				.error_cb = 0,
				.half_transfer_args = 0,
				.full_transfer_args = 0,
				.error_args = 0,
				.half_transfer_rt_cb = 0,
				.full_transfer_rt_cb = 0,
				.error_rt_cb = 0,
				.half_transfer_rt_args = (hcos_word_t) drv,
				.full_transfer_rt_args = (hcos_word_t) drv,
				.error_rt_args = 0,
    };

    dma_bind(&DMAD1, drv->dma_channel, config);
    drv->dev->CR2 |= ADC_CR2_DMA;
    dma_enable(&DMAD1, drv->dma_channel);
    drv->length = 0;
#else  /* ADC_USE_DMA == FALSE */
    drv->samples = buf;
    drv->length = n;
    drv->dev->IDR = 0xFFFFFFFF;
    drv->dev->IER = ADC_IER_DRDY;
#endif  /* ADC_USE_DMA */

    drv->dev->CR |= ADC_CR_START;

    return 0;
}

int adc_stop_conversion(adc_t *drv) {
#if ADC_USE_DMA != 1
    drv->dev->IDR = 0xFFFFFFFF;
#endif
    drv->dev->CHDR = 0xFFFF;
    drv->dev->MR &= ~(ADC_MR_FREERUN);   // Stop ADC

    /* TODO:  Check the best value to return */
    /* return drv->dev->SR & ? 1 : 0; */
    return 0;
}

int adc_stop(adc_t *drv) {
    adc_stop_conversion(drv);
    PMC_ADC_CLK_DISABLE();

    return 0;
}

void ADC_Handler(void) {
    static uint8_t conv_count = 0;

    if(ADC_EVT_EOC(ADC1)) {
        ADCD1.samples[conv_count] = adc_read(ADC1);
        conv_count += 1;

        if (conv_count >= active_drv->config->group->len) {
            /* Stop conversion if finished group's conversion
             * and no external trigger is set.
             */
            conv_count = 0;
            if (ADCD1.group_conv_cb != 0) {
                reactor_add_handler(ADCD1.group_conv_cb, (hcos_word_t) &ADCD1);
            }
        } else {
            /* Start group's next conversion if external trigger is not set */
            /* Need to see if the line below is really needed */
            /* if (active_drv->trigger == 0) active_drv->dev->CR2 |= ADC_CR2_ADON; */
        }
    }
    //TODO: Handle errors
}
#endif
