#ifndef REACTOR_H
#define REACTOR_H

#include "hcos_types_impl.h"
#include "hcos_asm_impl.h"

typedef void (*reactor_cb_t)(hcos_word_t);

void reactor_init(void);
void reactor_start(void);
hcos_base_int_t reactor_add_handlerI(reactor_cb_t cb, hcos_word_t data);

#define reactor_add_handler(cb, data) do {                      \
        hcos_cli();                                             \
        reactor_add_handlerI(cb, data);                         \
        hcos_sei();                                             \
    } while(0)

#endif /* REACTOR_H */
