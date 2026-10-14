/*
* Arti.c
*
*  To be used with the ARTI implementation of TRACE32:
*    ~~/demo/kernel/arti/hooks_cp/common
*/

#include "oe_oo_api_osek.h"
#include "Arti.h"

#include "../../../trace32/Arti/arti.c"

/*=============================================================================
 * Polling mode
 *===========================================================================*/
/*
 * Recover the wrap count from SYST_CVR alone. SysTick counts downwards, so a
 * new CVR value GREATER than the previous sample means the counter wrapped
 * (exactly one wrap - guaranteed by the "call at least twice per period"
 * constraint of systick32_attach()).
 */

#define SYST_RVR        (*(volatile uint32_t *)0xE000E014u)
#define SYST_CVR        (*(volatile uint32_t *)0xE000E018u)

/* Polling mode: 64-bit wrap count and last observed CVR. */
static volatile uint32_t s_poll_lo;
static volatile uint32_t s_poll_hi;
static volatile uint32_t s_poll_last_cvr;

uint64_t systick64_now_poll(void)
{
    uint32_t cvr = SYST_CVR;

    if (cvr > s_poll_last_cvr) {
        uint32_t lo = s_poll_lo + 1u;
        s_poll_lo = lo;
        if (lo == 0u) {
            s_poll_hi++;
        }
    }
    s_poll_last_cvr = cvr;

    uint32_t rvr = SYST_RVR;
    uint64_t period = (uint64_t)rvr + 1u;
    return (((uint64_t)s_poll_hi << 32) + s_poll_lo) * period + (uint64_t)(rvr - cvr);
}

void systick32_attach(void)
{
    s_poll_lo  = 0u;
    s_poll_hi  = 0u;
    s_poll_last_cvr = SYST_CVR;              /* baseline, no wrap assumed  */
}
