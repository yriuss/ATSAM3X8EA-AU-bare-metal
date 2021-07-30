#include <stdint.h>
#include "virtual_timer.h"
#include "reactor.h"
#include "hal.h"


uint32_t blinky_cb() {
    gpio_toggle_pin(GPIOB, 27);

    return 0;
}

int main(void) {
    vt_add_non_rt_handler(blinky_cb, 500, 1);
    reactor_start();
    
    return 0;
}
