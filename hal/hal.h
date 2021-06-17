#ifndef HAL_H
#define HAL_H

#include "gpio.h"
#if 0
#include "uart.h"
#include "dma.h"
#include "adc.h"
#include "spi.h"
#endif

#define hal_init() do {				\
        gpio_init();				\
    } while(0)

#if 0
#define hal_init() do {				\
        gpio_init();				\
	uart_init();				\
	dma_init();				\
        adc_init();                 \
        spi_init();                 \
    } while(0)
#endif

#endif /* HAL_H */
