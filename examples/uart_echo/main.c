#include <stdint.h>
#include "virtual_timer.h"
#include "reactor.h"
#include "gpio.h"
#include "uart.h"
#include "cmsis_gcc.h"


/*
 * Callback to blink the led to show the app is active
 */
void blink_cb(hcos_word_t arg) {
    gpio_toggle_pin(GPIOB, 27);
}

/*
 * The rx callback.  We read the data and echo it in the tx side
 */
void echo_cb(hcos_word_t arg) {
    uint8_t n = 0;
    uart_t* drv = (uart_t *) arg;
    static uint8_t buf[UART_BUFFER_SIZE + 1];

    n = uart_read(drv, buf, UART_BUFFER_SIZE);
    uart_write(drv, buf, n);
}

void error_cb(hcos_word_t arg) {
    uart_t* drv = (uart_t *) arg;
    const uint8_t buf[] = "ERROR!";

    uart_write(drv, buf, sizeof(buf));
}

int main(void) {
    uart_config_t cfg = {.baudrate = 200000,
			 .word_length = 8,
			 .stop_bits = 1,
			 .parity = 0,
			 .over_sampling = 0,
			 .hw_flow_ctl = 0,
			 .rx_threshold = UART_BUFFER_SIZE/2, /* Threshold to call the rx callback */
			 .rx_complete_cb = echo_cb,
			 .tx_complete_cb = 0,
			 .error_cb = error_cb
    };

    vt_add_non_rt_handler(blink_cb, 750, 1);

    uart_start(&SD1, &cfg);
    reactor_start();

    return 0;
}
