/*
* Arti.h
*
*  To be used with the ARTI implementation of TRACE32:
*    ~~/demo/kernel/arti/hooks_cp/common
*/

uint64_t systick64_now_poll(void);
void systick32_attach(void);

#include "../../../trace32/Arti/arti.h"
