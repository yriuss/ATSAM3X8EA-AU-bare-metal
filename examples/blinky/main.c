#include <stdint.h>
#include "virtual_timer.h"
#include "reactor.h"
#include "hal.h"


uint32_t blinky_cb() {
    if (gpio_read_pin_latch(GPIOB, 27) != 0) {
        /* Set clear register */
        gpio_clear_pin(GPIOB, 27);
    } else {
        /* Set pin */
        gpio_set_pin(GPIOB, 27);
    }

    return 0;
}

int main(void) {
    vt_add_non_rt_handler(blinky_cb, 500, 1);
    reactor_start();

    return 0;
}
