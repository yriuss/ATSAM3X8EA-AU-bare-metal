#include <core_cm3.h>
#include <sam3x8a.h>

#include <cmsis_gcc.h>

#include "reactor.h"
#include "virtual_timer.h"
#include "hal.h"

void system_init(void) {
    /* Set FWS according to SYS_BOARD_MCKR configuration */
    EFC0->EEFC_FMR = EEFC_FMR_FWS(4);
    EFC1->EEFC_FMR = EEFC_FMR_FWS(4);

    /* Disable the watchdog timer. */
    /* TODO: Make it configurable, either dinamically or statically */
    WDT->WDT_MR = WDT_MR_WDDIS;

    /* Initialize main oscillator */
    if (!(PMC->CKGR_MOR & CKGR_MOR_MOSCSEL)) {
        PMC->CKGR_MOR = SYS_CKGR_MOR_KEY_VALUE |
            SYS_BOARD_OSCOUNT |
            CKGR_MOR_MOSCRCEN |
            CKGR_MOR_MOSCRCF_12_MHz;
        while (!(PMC->PMC_SR & PMC_SR_MOSCRCS)) {
        }
    }

    PMC->PMC_MCKR = (PMC->PMC_MCKR &
                     ~(PMC_MCKR_CSS_Msk | CKGR_MOR_MOSCRCF_Msk)) |
        PMC_MCKR_CSS_MAIN_CLK;
    while (!(PMC->PMC_SR & PMC_SR_MCKRDY)) {
    }

    /* Initialize PLLA */
    PMC->CKGR_PLLAR = SYS_BOARD_PLLAR;
    while (!(PMC->PMC_SR & PMC_SR_LOCKA)) {
    }

    /* Set the prescaler before setting the PLL */
    PMC->PMC_MCKR = (PMC->PMC_MCKR & ~PMC_MCKR_PRES_Msk) |
        PMC_MCKR_PRES_CLK_1;
    while (!(PMC->PMC_SR & PMC_SR_MCKRDY)) {
    }

    /* Switch to PLLA */
    PMC->PMC_MCKR = (PMC->PMC_MCKR & ~PMC_MCKR_CSS_Msk) |
        PMC_MCKR_CSS_PLLA_CLK;
    while (!(PMC->PMC_SR & PMC_SR_MCKRDY)) {
    }

    /* Set the tick handler to aproximately 1 tick per ms */
    SysTick_Config(84000);

    /* Initiates the reactor scheduler and the virtual timers*/
    reactor_init();
    vt_init();
    hal_init();

    __enable_irq();
}
