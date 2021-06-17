#include <stdint.h>
#include "gpio.h" 


void gpio_set_group_mode(GPIO_TypeDef *port, uint32_t mask,
                         int offset, uint32_t mode) {
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
        port->OER = mask;
        port->PER = mask;
    } else if ((io_mode == GPIO_AF1_MODE) ||
               (io_mode == GPIO_AF2_MODE)) {
        port->ABSR = io_mode == GPIO_AF1_MODE ?
            (port->ABSR & ~(mask << offset)) :
            (port->ABSR | (mask << offset));
        port->PDR = mask;
    }
}
