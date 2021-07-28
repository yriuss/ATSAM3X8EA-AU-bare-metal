#include <stdint.h>
#include "cmsis_gcc.h"
#include "virtual_timer.h"
#include "reactor.h"
#include "gpio.h"
#include "uart.h"
#include "adc.h"

#define BUF_SZ_LOG 5
#define BUF_SZ (1U << BUF_SZ_LOG)
#define BUF_SZ_MSK (BUF_SZ - 1)
#define BUF_MIDPOINT_MSK (BUF_SZ/2 - 1)

#define MAX 1
void send_fun(hcos_word_t arg) {
    
    uint8_t *buf = (uint8_t *) arg;
    static int ctr = MAX;
    if(ctr++ >= MAX) {
        gpio_toggle_pin(GPIOB, 27);
        ctr = 0;
        uart_write(&SD1, buf, BUF_SZ/2);
        //uart_putc(&SD1, 'A');
	//uart_putc(&SD1, 'A');
    }
}
void ADC_Handler(void) {
    static uint16_t n = 0;
    static uint16_t buf[BUF_SZ];

    buf[n++] = ADC->LCDR & 0xFFF;
    n &= BUF_SZ_MSK;
    if (!(n & BUF_MIDPOINT_MSK)) {

        reactor_add_handler(send_fun,
                            (hcos_word_t) (buf + (n ^ (BUF_SZ/2))));
    }
}

void my_func(hcos_word_t arg){
    ADC_Handler();
}


#define testing 1
/*
 * Callback to blink the led to show the app is active
 */
void blink_cb(hcos_word_t arg) {
    gpio_toggle_pin(GPIOB, 27);
}

//#define ADC_BUFFER_SIZE 1024
//uint16_t adc_buffer[ADC_BUFFER_SIZE];

int main(void) {
    gpio_set_pin_mode(GPIOB, 27, GPIO_OUTPUT_MODE | GPIO_SYNC_WRITE);
    //gpio_set_pin_mode(GPIOA, 3, GPIO_INPUT_MODE);
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
    /*
    adc_config_t adc_config =
        {.group = {.ch = {1, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0},
                   .len = 1,
                   .seq_order = 1
                   },
         .freerun_mode = 1,
         .trigger = 0,
         .lowres_mode = 0,
         .samples = 0,
         //.group_conv_cb = 0,
         //.eoc_injected_cb = 0,
         //.watchdog_cb = 0,
         //.half_transfer_cb = half_transfer_cb,
         //.full_transfer_cb = full_transfer_cb,
    };*/
#if 0
    adc_config_t adc_config =
        {.group = {.ch = {1, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0},
                   .len = 1,
                   .seq_order = 1
                   },
         .freerun_mode = 1,
         .trigger = 0,
         .lowres_mode = 0,
         .samples = 0,
         //.group_conv_cb = 0,
         //.eoc_injected_cb = 0,
         //.watchdog_cb = 0,
         //.half_transfer_cb = half_transfer_cb,
         //.full_transfer_cb = full_transfer_cb,
    };
    
   adc_config_t adc_config;
    int i = 0;
    for(i=0;i<16;i++){
        if(i = 0)
            adc_config.group.ch[i] = 1;
        else
            adc_config.group.ch[i] = 0;

   }
    adc_config.freerun_mode=1;
    adc_config.group.len=1;
    adc_config.group.seq_order=1;
    adc_config.trigger=0;
    adc_config.lowres_mode=0;
    adc_config.prescaler=200;
    adc_config.settling=0;
    adc_config.startup=1;
    adc_config.tracking=0;
    adc_config.transfer=0;
    adc_config.different_chann=0;

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
#define MAX_TICKS 1000000
    //vt_add_non_rt_handler(blink_cb, 250, 1);
    adc_t adc;
    uint8_t len = 2;
    uint16_t* buffer;
    uart_start(&SD1, &uart_cfg);
#if !testing
    adc_start(&adc ,&adc_config);
    
    

    adc_start_conversion(&adc, &buffer, len);
    if(buffer[0] == 4095)
        gpio_toggle_pin(GPIOB, 27);
#endif

#if testing
    ADC->CR = ADC_CR_SWRST;
    ADC->MR = ADC_MR_FREERUN | code_adc_mr_settling(0) |
        code_adc_mr_tracking(0) | code_adc_mr_transfer(0) |
        code_adc_mr_prescaler(255) | code_adc_mr_startup(1);
    ADC->CHER = 0x2;


    NVIC_EnableIRQ(ADC_IRQn);
    NVIC_SetPriority(ADC_IRQn, 3);
    PMC_ADC_CLK_ENABLE();
    
    ADC->IER = ADC_IER_DRDY;
    ADC->CR = ADC_CR_START;
    int ctr = MAX_TICKS;
    uint16_t data = 0;
    
    gpio_set_pin(GPIOB,27);


    //vt_add_non_rt_handler(my_func, 20, 1);
    reactor_start();
    /*while (1) {
        if(--ctr == 0){
            ctr = MAX_TICKS;
        }
        ADC_Handler();

        if (ADC->ISR & ADC_ISR_DRDY){
            data = ADC->LCDR & 0xFFF;
            if(!(ctr & 0xF)){
                uart_putc(&SD1, data & 0xFF);
                uart_putc(&SD1, (data >> 8) & 0xF);
            }
        }
    }*/
#endif
    /* adc_start(&ADCD1, &adc_cfg); */

    /* adc_start_conversion(&ADCD1, adc_buffer, ADC_BUFFER_SIZE); */

    /* reactor_start(); */

    return 0;
}





