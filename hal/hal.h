#ifndef HAL_H
#define HAL_H

#include "gpio.h"
#include "uart.h"
#include "adc.h"
#if 0
#include "dma.h"
#include "spi.h"
#endif

#define hal_init() do {				\
        gpio_init();				\
	uart_init();				\
        adc_init();                             \
    } while(0)

#if 0
#define hal_init() do {				\
        gpio_init();				\
	uart_init();				\
	dma_init();				\
        spi_init();                 \
    } while(0)
#endif

#endif /* HAL_H */
