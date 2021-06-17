#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include "sam3x8a.h"


#define GPIO_INPUT_MODE  0X00
#define GPIO_OUTPUT_MODE 0X10
#define GPIO_AF1_MODE    0X20
#define GPIO_AF2_MODE    0X30
#define GPIO_MODE_Msk    0xF0

#define GPIO_PULLUP      0X01
#define GPIO_OPENDRAIN   0X02
#define GPIO_DEBOUNCE    0X04
#define GPIO_SYNC_WRITE  0X08
#define GPIO_FEATURES_Msk 0x0F


/*
 * Functions
 */
/* We don't really do anything in gpio_init(), so it is defined here
   as an empty #define.  The original prototype was static void
   gpio_init(void); */
#define gpio_init()


/*
 * Macros to operate on the port level
 */
#define gpio_read_port(port)			\
    ((uint32_t) ((port)->PDSR))

#define gpio_read_port_latches(port)		\
    ((uint32_t) ((port)->ODSR))

#define gpio_write_port(port, value)		\
    ((port)->ODSR = (value))

#define gpio_set_port(port)			\
    ((port)->SODR = 0xFFFFFFFF)

#define gpio_clear_port(port)			\
    ((port)->CODR = 0xFFFFFFFF)

#define gpio_toggle_port(port)			\
    ((port)->ODSR = ~(port)->ODSR)

#define gpio_set_port_mode(port, mode)                  \
    void gpio_set_group_mode(port, 0xFFFFFFFF, 0, mode)


/*
 * Macros to operate on a level of group of bits
 */
#define gpio_read_group(port, mask, offset)		\
    ((gpio_read_port(port) >> (offset)) & (mask))

#define gpio_read_group_latches(port, mask, offset)		\
    ((gpio_read_port_latches(port) >> (offset)) & (mask))

#define gpio_write_group(port, mask, offset, value)			\
    gpio_write_port((gpio_read_port(port) & ~((mask) << (offset))) |	\
                    (((value) & (mask)) << (offset)))

#define gpio_set_group(port, mask, offset)	\
    ((port)->SODR = ((mask) << (offset)))

#define gpio_clear_group(port, mask, offset)	\
    ((port)->CODR = ((mask) << (offset)))

#define gpio_toggle_group(port, mask, offset)                   \
    ((port)->ODSR ^= ((mask) << (offset)))

void gpio_set_group_mode(GPIO_TypeDef *port, uint32_t bitmask,
                         int offset, uint32_t mode);


/*
 * Macros to operate on the level of single bits
 */
/* TODO: Should we provide a version returning the value without
   shifting? */
#define gpio_read_pin(port, pin_nbr)		\
    ((gpio_read_port(port) >> (pin_nbr)) & 0x1)

#define gpio_read_pin_latch(port, pin_nbr)		\
    ((gpio_read_port_latches(port) >> (pin_nbr)) & 0x1)

#define gpio_write_pin(port, pin_nbr, value)               \
    ((port)->ODSR = ((port)->ODSR & ~(1 << (pin_nbr))) |   \
     ((value) << (pin_nbr)))

#define gpio_set_pin(port, pin_nbr)		\
    ((port)->SODR = (1 << (pin_nbr)))

#define gpio_clear_pin(port, pin_nbr)		\
    (port)->CODR = (1 << (pin_nbr))

#define gpio_toggle_pin(port, pin_nbr)		\
    gpio_toggle_group(port, 1, pin_nbr)

#define gpio_set_pin_mode(port, pin_nbr, mode)  \
    gpio_set_group_mode(port, 1, pin_nbr, mode)

#endif /* GPIO_H */
