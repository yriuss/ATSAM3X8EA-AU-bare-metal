#include <stdint.h>
#include "gpio.h"
#include "pmc.h"


void gpio_set_group_mode(GPIO_TypeDef *port, uint32_t mask,
                         int offset, gpio_mode_t mode) {
    uint32_t io_mode = mode & GPIO_MODE_Msk;
    uint32_t features = mode & GPIO_FEATURES_Msk;

    mask <<= offset;

    if (features & GPIO_PULLUP)
        port->PUER = mask;
    else
        port->PUDR = mask;

    if (io_mode == GPIO_INPUT_MODE) {
        if (features & GPIO_DEBOUNCE)
            port->IFER = mask;
        else
            port->IFDR = mask;
        
        port->ODR = mask;
        port->PER = mask;
    } else if (io_mode == GPIO_OUTPUT_MODE) {
        if (features & GPIO_OPENDRAIN)
            port->MDER = mask;
        else
            port->MDDR = mask;
        if (features & GPIO_SYNC_WRITE)
            port->OWER = mask;
        else
            port->OWDR = mask;
        port->OER = mask;
        port->PER = mask;
    } else if ((io_mode == GPIO_AF1_MODE) ||
               (io_mode == GPIO_AF2_MODE)) {
        port->ABSR = io_mode == GPIO_AF1_MODE ?
            (port->ABSR & ~mask) :
            (port->ABSR | mask);
        port->PDR = mask;
    }

    if (io_mode != GPIO_OUTPUT_MODE) {
        (port == GPIOA) && PMC_GPIOA_CLK_ENABLE();
        (port == GPIOB) && PMC_GPIOB_CLK_ENABLE();
        (port == GPIOC) && PMC_GPIOC_CLK_ENABLE();
        (port == GPIOD) && PMC_GPIOD_CLK_ENABLE();
    }
}
