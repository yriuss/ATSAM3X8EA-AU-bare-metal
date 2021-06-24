#ifndef VIRTUAL_TIMER_PRIV
#define VIRTUAL_TIMER_PRIV

#include "virtual_timer.h"

#define VT_RT_ARRAY_MAX 4
#define VT_NON_RT_ARRAY_MAX 8

extern volatile rt_cb_t vt_rt_handler_array[VT_RT_ARRAY_MAX];
extern volatile non_rt_cb_t vt_non_rt_handler_array[VT_NON_RT_ARRAY_MAX];
extern volatile hcos_word_t vt_non_rt_data_array[2*VT_NON_RT_ARRAY_MAX];

#endif /* VIRTUAL_TIMER_PRIV */
