#include "virtual_timer_priv.h"
#include "reactor.h"
#include "systime.h"


volatile uint32_t systick_no_ticks = 0;

void
SysTick_Handler(void)
{
    int i;

    systick_no_ticks++;

    for(i=0; i<VT_RT_ARRAY_MAX; i++)
        if(vt_rt_handler_array[i])
            if((vt_rt_handler_array[i])())
                vt_rt_handler_array[i] = 0;

    for(i=0; i<VT_NON_RT_ARRAY_MAX; i++)
        if(vt_non_rt_handler_array[i]) {
            if(--vt_non_rt_data_array[i])
                continue;
            reactor_add_handlerI(vt_non_rt_handler_array[i], 0);
            if(vt_non_rt_data_array[i + VT_NON_RT_ARRAY_MAX]) {
                /* If the handler is a periodic one, reloads it with
                   the appropriate timeout value */
                vt_non_rt_data_array[i] =
                    vt_non_rt_data_array[i + VT_NON_RT_ARRAY_MAX];
            } else {
                /* Otherwise, kill it right away */
                vt_non_rt_handler_array[i] = 0;
            }
        }
}
