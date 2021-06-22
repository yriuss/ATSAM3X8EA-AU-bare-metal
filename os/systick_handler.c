#include "virtual_timer_priv.h"
#include "virtual_timer.h"
#include "reactor.h"
#include "systime.h"


volatile uint32_t systick_no_ticks = 0;

void
SysTick_Handler(void)
{
    int i;

    systick_no_ticks++;

    for(i=0; i<VT_RT_HANDLER_ARRAY_MAX; i++)
        if(vt_rt_handler_array[i])
            if(((timer_cb_t) vt_rt_handler_array[i])())
                vt_rt_handler_array[i] = 0;

    for(i=VT_NON_RT_HANDLER_ARRAY_MAX; i<2*VT_NON_RT_HANDLER_ARRAY_MAX; i++)
        if(vt_non_rt_handler_array[i]) {
            if(--vt_non_rt_handler_array[i - VT_NON_RT_HANDLER_ARRAY_MAX])
                continue;
            reactor_add_handlerI(vt_non_rt_handler_array[i], 0);
            if(!vt_non_rt_handler_array[i + VT_NON_RT_HANDLER_ARRAY_MAX]) {
                /* If the handler is a one-shot, kill it right away */
                vt_non_rt_handler_array[i] = 0;
            } else
                /* Otherwise, reloads it with the appropriate timeout
                   value */
                vt_non_rt_handler_array[i - VT_NON_RT_HANDLER_ARRAY_MAX] =
                    vt_non_rt_handler_array[i + VT_NON_RT_HANDLER_ARRAY_MAX];
        }
}
