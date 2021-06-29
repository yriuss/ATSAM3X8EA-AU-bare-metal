#include <stdint.h>
#include "cmsis_gcc.h"
#include "virtual_timer.h"
#include "reactor.h"
#include "gpio.h"
#include "uart.h"
#include "adc.h"


/*
 * Callback to blink the led to show the app is active
 */
void blink_cb(hcos_word_t arg) {
    gpio_toggle_pin(GPIOB, 27);
}

#define ADC_BUFFER_SIZE 1024
uint16_t adc_buffer[ADC_BUFFER_SIZE];

int main(void) {
    uart_config_t uart_cfg = {.baudrate = 500000,
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

#if 0
    adc_group_t adc_groups_config =
        {.group = {.ch = {1, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0},
                   .len = 1,
                   .seq_order = 1,
                   };
         .freerun_mode = 1,
         .trigger = 0,
         .lowres_mode = 0,
         .samples = adc_buffer,
         .group_conv_cb = 0,
         .eoc_injected_cb = 0,
         .watchdog_cb = 0,
         .half_transfer_cb = half_transfer_cb,
         .full_transfer_cb = full_transfer_cb,
    };
#endif

#include "pmc.h"
#define MAX_TICKS 500000
    vt_add_non_rt_handler(blink_cb, 250, 1);

    uart_start(&SD1, &uart_cfg);

    ADC->CR = ADC_CR_SWRST;
    ADC->MR = ADC_MR_FREERUN | code_adc_mr_settling(0) |
        code_adc_mr_tracking(3) | code_adc_mr_transfer(2) |
        code_adc_mr_prescaler(255) | code_adc_mr_startup(1);
    ADC->CHER = 0x2;
    /* ADC->IER = ADC_IER_DRDY; */


    NVIC_EnableIRQ(ADC_IRQn);
    NVIC_SetPriority(ADC_IRQn, 3);
    PMC_ADC_CLK_ENABLE();
    ADC->CR = ADC_CR_START;

    while (1) {
        while (!ADC->ISR & ADC_ISR_DRDY)
            ;
        data = ADC->LCDR & 0xFFF;
        uart_putc(&SD1, data & 0xFF);
        uart_putc(&SD1, (data >> 8) & 0xF);
    }

    /* adc_start(&ADCD1, &adc_cfg); */

    /* adc_start_conversion(&ADCD1, adc_buffer, ADC_BUFFER_SIZE); */

    /* reactor_start(); */

    return 0;
}


#define BUF_SZ_LOG 5
#define BUF_SZ (1U << BUF_SZ_LOG)
#define BUF_SZ_MSK (BUF_SZ - 1)
#define BUF_MIDPOINT_MSK (BUF_SZ/2 - 1)

#define MAX 2
void send_fun(hcos_word_t arg) {
    uint8_t *buf = (uint8_t *) arg;
    static int ctr = 0;
    if(++ctr >= MAX) {
        ctr = 0;
        uart_write(&SD1, buf, BUF_SZ);
    }
}

void ADC_Handler(void) {
    static uint16_t n = 0;
    static uint16_t buf[BUF_SZ];

    buf[n++] = ADC->LCDR & 0xFFF;
    n &= BUF_SZ_MSK;
    if (!(n & BUF_MIDPOINT_MSK)) {
        reactor_add_handlerI(send_fun,
                            (hcos_word_t) (buf + (n ^ (BUF_SZ/2))));
    }
}
