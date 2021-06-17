#include <stdint.h>
#include "virtual_timer.h"
#include "reactor.h"
#include "hal.h"


int main(void) {
    int i;
	
    /* vt_add_non_rt_handler(read_pin_cb, 10, 1); */
    /* reactor_start(); */

    while(1) {
        for (i=0; i<2000000; i++)
            asm("NOP");

        if (gpio_read_pin_latch(GPIOB, 27) != 0) {
            /* Set clear register */
            gpio_clear_pin(GPIOB, 27);
        } else {
            /* Set pin */
            gpio_set_pin(GPIOB, 27);
        }
    }
    return 0;
}
