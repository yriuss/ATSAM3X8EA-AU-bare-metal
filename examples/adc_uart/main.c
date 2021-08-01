#include <stdint.h>
#include "cmsis_gcc.h"
#include "virtual_timer.h"
#include "reactor.h"
#include "gpio.h"
#include "uart.h"
#include "adc.h"
#include "pmc.h"



#define ADC_BUFFER_SIZE 1024
uint16_t adc_buffer[ADC_BUFFER_SIZE];

void adc_conv_callback(hcos_word_t arg) {    
    uint8_t *buf = (uint8_t *) arg;
    gpio_toggle_pin(GPIOB, 27);
    //uart_write(&SD1, buf, BUF_SZ/2); 
    uart_write(&SD1, adc_buffer, ADC_BUFFER_SIZE);  
}


int main(void) {
    gpio_set_pin_mode(GPIOB, 27, GPIO_OUTPUT_MODE | GPIO_SYNC_WRITE);

    uart_config_t uart_cfg = {.baudrate = 115200,
			      .word_length = 8,
			      .stop_bits = 1,
			      .parity = 0,
			      .over_sampling = 0,
			      .hw_flow_ctl = 0,
			      .rx_threshold = UART_BUFFER_SIZE/2, /* Threshold to call the rx callback */
			      .rx_complete_cb = 0,
			      .tx_complete_cb = 0,
			      .error_cb = 0
    };

    adc_config_t adc_config =
        {.group = {.ch = {0, 1, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0},
                   .len = 1,
                   .seq_order = 0
                   },
         .align_mode=0,
         .freerun_mode = 1,
         .trigger = 0,
         .lowres_mode = 0,
         .prescaler = 255,
         .startup = 1,
         .settling = 0,
         .tracking = 0,
         .transfer = 0,
         .different_chann = 0,
         .temp_on = 0,
         .group_conv_cb = adc_conv_callback,
         .eoc_injected_cb = 0,
         .watchdog_cb = 0
    };

    adc_t adc;

    uart_start(&SD1, &uart_cfg);

    
    gpio_set_pin(GPIOB,27);
    adc_start(&adc, &adc_config);
    adc_start_conversion(&adc, adc_buffer, ADC_BUFFER_SIZE);
    
    reactor_start();

    return 0;
}