#ifndef VIRTUAL_TIMER_H
#define VIRTUAL_TIMER_H

#include "hcos_types_impl.h"
#include "hcos_asm_impl.h"

typedef hcos_base_int_t (*rt_cb_t)(void);
typedef void (*non_rt_cb_t)(hcos_word_t);

void vt_init(void);
void vt_deinit(void);
hcos_base_int_t vt_add_rt_handlerI(rt_cb_t);
hcos_base_int_t vt_add_non_rt_handlerI(non_rt_cb_t, hcos_word_t,
                                       hcos_base_int_t);
hcos_base_int_t vt_delete_rt_handlerI(rt_cb_t);
hcos_base_int_t vt_delete_non_rt_handlerI(non_rt_cb_t);
hcos_base_int_t vt_update_non_rt_handlerI(non_rt_cb_t, non_rt_cb_t,
                                          hcos_word_t, hcos_base_int_t);

static inline hcos_base_int_t
vt_add_rt_handler(rt_cb_t cb) {
    hcos_base_int_t rc;
    hcos_cli();
    rc = vt_add_rt_handlerI(cb);
    hcos_sei();
    return rc;
}

static inline hcos_base_int_t
vt_add_non_rt_handler(non_rt_cb_t cb,
                      hcos_word_t timeout,
                      hcos_base_int_t is_periodic) {
    hcos_base_int_t rc;
    hcos_cli();
    rc = vt_add_non_rt_handlerI(cb, timeout, is_periodic);
    hcos_sei();
    return rc;
}

static inline hcos_base_int_t
vt_delete_rt_handler(rt_cb_t cb) {
    hcos_base_int_t rc;
    hcos_cli();
    rc = vt_delete_rt_handlerI(cb);
    hcos_sei();
    return rc;
}

static inline hcos_base_int_t
vt_delete_non_rt_handler(non_rt_cb_t cb) {
    hcos_base_int_t rc;
    hcos_cli();
    rc = vt_delete_non_rt_handlerI(cb);
    hcos_sei();
    return rc;
}

static inline hcos_base_int_t
vt_update_non_rt_handler(non_rt_cb_t old_cb,
                         non_rt_cb_t new_cb,
                         hcos_word_t data,
                         hcos_base_int_t is_periodic) {
    hcos_base_int_t rc;
    hcos_cli();
    rc = vt_update_non_rt_handlerI(old_cb, new_cb, data, is_periodic);
    hcos_sei();
    return rc;
}

#endif /* VIRTUAL_TIMER_H */
