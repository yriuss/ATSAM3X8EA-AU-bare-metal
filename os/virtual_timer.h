#ifndef VIRTUAL_TIMER_H
#define VIRTUAL_TIMER_H

#include "hcos_types_impl.h"
#include "hcos_asm_impl.h"

typedef hcos_base_int_t (*timer_cb_t)(void);

void vt_init(void);
void vt_deinit(void);
hcos_base_int_t vt_add_rt_handlerI(timer_cb_t);
hcos_base_int_t vt_add_non_rt_handlerI(timer_cb_t, hcos_word_t,
                                       hcos_base_int_t);
hcos_base_int_t vt_delete_rt_handlerI(timer_cb_t);
hcos_base_int_t vt_delete_non_rt_handlerI(timer_cb_t);
hcos_base_int_t vt_update_non_rt_handlerI(timer_cb_t, hcos_word_t,
                                          hcos_base_int_t);

#define vt_add_rt_handler(cb) do {                           \
        hcos_cli();                                          \
        vt_add_rt_handlerI(cb);                              \
        hcos_sei();                                          \
    } while (0)

#define vt_add_non_rt_handler(cb, data, is_periodic) do {       \
        hcos_cli();                                             \
        vt_add_non_rt_handlerI(cb, data, is_periodic);          \
        hcos_sei();                                             \
    } while (0)

#define vt_delete_rt_handler(cb) do {                           \
        hcos_cli();                                             \
        vt_delete_rt_handlerI(cb);                              \
        hcos_sei();                                             \
    } while (0)

#define vt_delete_non_rt_handler(cb) do {                       \
        hcos_cli();                                             \
        vt_delete_non_rt_handlerI(cb);                          \
        hcos_sei();                                             \
    } while (0)

#define vt_update_non_rt_handler(cb, data, is_periodic) do {    \
        hcos_cli();                                             \
        vt_update_non_rt_handlerI(cb, data, is_periodic);       \
        hcos_sei();                                             \
    } while (0)

#endif /* VIRTUAL_TIMER_H */
