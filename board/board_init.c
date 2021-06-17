#include "sam3x8a.h"
#include "gpio.h"

void
board_init(void) {
    /* Set bit 27 of the GPIOB port as output */
    gpio_set_pin_mode(GPIOB, 27, GPIO_OUTPUT_MODE);
}
