#include <stdint.h>
#include "cmsis_gcc.h"
#include "virtual_timer.h"
#include "reactor.h"
#include "gpio.h"
#include "uart.h"
#include "adc.h"
#include "pmc.h"
#include "dac.h"

/*
 * Callback to blink the led to show the app is active
 */
void blink_cb(hcos_word_t arg) {
    gpio_toggle_pin(GPIOB, 27);
}

#define ADC_BUFFER_SIZE 1024
uint16_t adc_buffer[ADC_BUFFER_SIZE];

int main(void) {
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

#if 0
    dac_config_t adc_config =
        {
         .half_transfer_cb = half_transfer_cb,
         .full_transfer_cb = full_transfer_cb,
    };
#endif

#define MAX_TICKS 1000
#define TABLE_SIZE 32
#define TABLE_CTR_OFFSET 0
#define TABLE_CTR_MASK 31

    uint16_t table[TABLE_SIZE] =
        {2043, 2441, 2824, 3178, 3487, 3741, 3930, 4046, 4086, 4046,
         3930, 3741, 3487, 3178, 2824, 2441, 2043, 1644, 1261,  907,
         598, 344, 155, 39, 0, 39, 155, 344, 598,  907, 1261, 1644};
    int ctr = MAX_TICKS;
    uint16_t table_ctr = 0;

    //int ctr = MAX_TICKS;
    uint16_t data;
    uart_start(&SD1, &uart_cfg);


    DAC->CR = DAC_CR_SWRST;
    dac_set(DAC_CH0);


    ADC->CR = ADC_CR_SWRST;
    ADC->MR = ADC_MR_FREERUN | code_adc_mr_settling(0) |
        code_adc_mr_tracking(0) | code_adc_mr_transfer(0) |
        code_adc_mr_prescaler(200) | code_adc_mr_startup(1);
    ADC->CHER = 0x2;
    /* ADC->IER = ADC_IER_DRDY; */

    PMC_DAC_CLK_ENABLE();
    PMC_ADC_CLK_ENABLE();
    ADC->CR = ADC_CR_START;

    while (1) {
        if (--ctr == 0) {
            ctr = MAX_TICKS;
        }
        if (DAC->ISR & 0x1 && ctr == MAX_TICKS) {
            DAC->CDR = table[table_ctr++ >> TABLE_CTR_OFFSET];
            table_ctr &= TABLE_CTR_MASK;
        }
        
        if (ADC->ISR & ADC_ISR_DRDY && ctr == MAX_TICKS) {
            data = ADC->LCDR & 0xFFF;
            uart_putc(&SD1, data & 0xFF);
            uart_putc(&SD1, (data >> 8) & 0xF);
        }
    }

    /* adc_start(&DACD1, &adc_cfg); */

    /* adc_start_conversion(&DACD1, adc_buffer, DAC_BUFFER_SIZE); */

    /* reactor_start(); */

    return 0;
}


#if 0
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

void DAC_Handler(void) {
    static uint16_t n = 0;
    static uint16_t buf[BUF_SZ];

    buf[n++] = DAC->LCDR & 0xFFF;
    n &= BUF_SZ_MSK;
    if (!(n & BUF_MIDPOINT_MSK)) {
        reactor_add_handlerI(send_fun,
                            (hcos_word_t) (buf + (n ^ (BUF_SZ/2))));
    }
}
#endif
