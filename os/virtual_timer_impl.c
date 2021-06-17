#include "core_cm3.h"
#include "sam3x8a.h"
#include "virtual_timer.h"


void vt_init(void) {
    NVIC_ClearPendingIRQ(SysTick_IRQn);
    NVIC_EnableIRQ(SysTick_IRQn);
}

void vt_deinit(void) {
    NVIC_DisableIRQ(SysTick_IRQn);
}
