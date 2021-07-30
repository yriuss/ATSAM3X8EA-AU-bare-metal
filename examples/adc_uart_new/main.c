#include <stdint.h>
#include "cmsis_gcc.h"
#include "virtual_timer.h"
#include "reactor.h"
#include "gpio.h"
#include "uart.h"
#include "adc.h"
#include "pmc.h"








#define testing 1


//#define ADC_BUFFER_SIZE 1024
//uint16_t adc_buffer[ADC_BUFFER_SIZE];

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
         .group_conv_cb = 0,
         .eoc_injected_cb = 0,
         .watchdog_cb = 0
         //.half_transfer_cb = half_transfer_cb,
         //.full_transfer_cb = full_transfer_cb,
    };
    
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


    //vt_add_non_rt_handler(blink_cb, 250, 1);
    adc_t adc;
    
    uart_start(&SD1, &uart_cfg);
#if !testing
    adc_start(&adc ,&adc_config);
    
    

    adc_start_conversion(&adc, &buffer, len);
    if(buffer[0] == 4095)
        gpio_toggle_pin(GPIOB, 27);
#endif

#if testing
    
    
    gpio_set_pin(GPIOB,27);
    adc_start(&adc, &adc_config);

    reactor_start();
#endif

    return 0;
}





