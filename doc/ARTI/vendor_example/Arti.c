/**********************************************************************************************************
 * Arti.c - EXAMPLE of the Arti API and of the storage of the trace variables.
 * To be replaced by the file of the trace tool; places a vendor has to adapt are marked "VENDOR".
 **********************************************************************************************************/
#include "Arti.h"
#include "Os_Arti.h"

/* VENDOR: the storage the trace tool observes.  Place it in the memory section the tool requires (for example
 * with the project's MemMap), and make sure the debugger or the trace hardware can reach it.
 * One 32 bit word per core: an aligned 32 bit write is atomic, so the macros are reentrant. */
volatile uint32 arti_os_trace[ARTI_OS_CORES];

/* SWS_Arti_91004.  The kernel does not call it: VENDOR / integrator, call it once before the OS starts
 * (for example from the start-up code before StartOS), on every core that is traced. */
void Arti_Init(void)
{
    uint32 core;

    for (core = 0U; core < ARTI_OS_CORES; core++)
    {
        arti_os_trace[core] = 0U;
    }
    /* VENDOR: initialise the tool's own resources here; on failure raise ARTI_E_INIT_FAILED (SWS_Arti_00009) */
}

/* SWS_Arti_91005 */
void Arti_GetVersionInfo(Std_VersionInfoType *VersionInfoPtr)
{
    if (VersionInfoPtr == ((void *)0))
    {
        /* VENDOR: raise ARTI_E_PARAM_POINTER (SWS_Arti_00010), for example through the DET */
        return;
    }
    VersionInfoPtr->vendorID = ARTI_VENDOR_ID;
    VersionInfoPtr->moduleID = ARTI_MODULE_ID;
    VersionInfoPtr->sw_major_version = ARTI_SW_MAJOR_VERSION;
    VersionInfoPtr->sw_minor_version = ARTI_SW_MINOR_VERSION;
    VersionInfoPtr->sw_patch_version = ARTI_SW_PATCH_VERSION;
}
