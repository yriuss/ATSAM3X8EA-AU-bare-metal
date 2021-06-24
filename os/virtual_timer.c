#include "virtual_timer_priv.h"
#include "hcos_asm_impl.h"


/* Trick to garantee the hcos_word_t type has the same size as the
   hcos_ptr_t type */
extern char _CHECK_SIZE_OF_[1/!(sizeof(hcos_word_t) != sizeof(hcos_ptr_t))];

volatile rt_cb_t vt_rt_handler_array[VT_RT_ARRAY_MAX];
volatile non_rt_cb_t vt_non_rt_handler_array[VT_NON_RT_ARRAY_MAX];
volatile hcos_word_t vt_non_rt_data_array[2*VT_NON_RT_ARRAY_MAX];


void vt_init(void) __attribute ((weak));
void vt_init(void) {
    /* Some mumbo-jumbo to set timer */
}


void vt_deinit(void) __attribute ((weak));
void vt_deinit(void) {
    /* Some mumbo-jumbo to stop timer */
}


hcos_base_int_t vt_add_rt_handlerI(rt_cb_t cb) {
    hcos_base_int_t rc = 1;
    int i;

    if(!cb)
        return rc;

    for(i=0; i<VT_RT_ARRAY_MAX; i++)
        if(!vt_rt_handler_array[i]) {
            vt_rt_handler_array[i] = cb;
            rc = 0;
            break;
        }
    return rc;
}


hcos_base_int_t vt_add_non_rt_handlerI(non_rt_cb_t cb, hcos_word_t timeout, hcos_base_int_t is_periodic) {
    hcos_base_int_t rc = 1;
    int i;

    if(!(timeout && cb))
        return rc;

    for(i=0; i<VT_NON_RT_ARRAY_MAX; i++)
        if(!vt_non_rt_handler_array[i]) {
            vt_non_rt_data_array[i] = timeout;
            vt_non_rt_handler_array[i] = cb;
            if(is_periodic)
                vt_non_rt_data_array[i + VT_NON_RT_ARRAY_MAX] = timeout;
            else
                vt_non_rt_data_array[i + VT_NON_RT_ARRAY_MAX] = 0;
            rc = 0;
            break;
        }
    return rc;
}


hcos_base_int_t vt_delete_rt_handlerI(rt_cb_t cb) {
    hcos_base_int_t rc = 1;
    int i;

    if(!cb)
        return rc;

    for(i=0; i<VT_RT_ARRAY_MAX; i++)
        if(vt_rt_handler_array[i] == cb) {
            vt_rt_handler_array[i] = 0;
            rc = 0;
            break;
        }
    return rc;
}


hcos_base_int_t vt_delete_non_rt_handlerI(non_rt_cb_t cb) {
    hcos_base_int_t rc = 1;
    int i;

    if(!cb)
        return rc;

    for(i=0; i<VT_NON_RT_ARRAY_MAX; i++)
        if(vt_non_rt_handler_array[i] == cb) {
            vt_non_rt_data_array[i] = 0;
            vt_non_rt_data_array[i + VT_NON_RT_ARRAY_MAX] = 0;
            vt_non_rt_handler_array[i] = 0;
            rc = 0;
            break;
        }
    return rc;
}


hcos_base_int_t vt_update_non_rt_handlerI(non_rt_cb_t old_cb,
                                          non_rt_cb_t new_cb,
                                          hcos_word_t timeout,
                                          hcos_base_int_t is_periodic) {
    hcos_base_int_t rc = 1;
    int i;

    if(!(timeout && old_cb && new_cb))
        return rc;

    for(i=0; i<VT_NON_RT_ARRAY_MAX; i++)
        if(vt_non_rt_handler_array[i] == old_cb) {
            vt_non_rt_handler_array[i] = new_cb;
            vt_non_rt_data_array[i] = timeout;
            if(is_periodic)
                vt_non_rt_data_array[i + VT_NON_RT_ARRAY_MAX] = timeout;
            else
                vt_non_rt_data_array[i + VT_NON_RT_ARRAY_MAX] = 0;
            rc = 0;
            break;
        }
    return rc;
}
