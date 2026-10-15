/**********************************************************************************************************************
 * Arti.c - baseline of the ARTI API and of the storage of the trace variables.
 *
 * One of the three files every trace tool vendor starts from (Arti.h, Os_Arti.h, Arti.c).
 * Places a vendor may adapt are marked "VENDOR".
 **********************************************************************************************************************/
#include "Arti.h"

#if (ARTI_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

/* VENDOR: the storage the trace tool watches.  Place it in the memory section the tool requires.  The writes are
 * aligned 32 bit writes, atomic on the target, so the macros of Os_Arti.h are reentrant and need no lock. */
volatile uint32 arti_os_trace;
volatile uint32 arti_sc_trace;

/* SWS_Arti_91004.  The kernel does not call it: the integrator calls it once on start-up, before the OS is started
 * (for example from the start-up code before StartOS). */
void Arti_Init(void)
{
    arti_os_trace = 0U;
    arti_sc_trace = 0U;
    /* VENDOR: initialise the resources of the trace tool here; on failure raise ARTI_E_INIT_FAILED (SWS_Arti_00009) */
}

/* SWS_Arti_91005 */
void Arti_GetVersionInfo(Std_VersionInfoType *VersionInfoPtr)
{
    if (VersionInfoPtr == ((void *)0))
    {
#if (ARTI_DEV_ERROR_DETECT == STD_ON)
        /* VENDOR: use the real instance and API IDs; SWS_Arti_00010 */
        (void)Det_ReportError(ARTI_MODULE_ID, 0U, 0x01U, ARTI_E_PARAM_POINTER);
#endif
        return;
    }
    VersionInfoPtr->vendorID = ARTI_VENDOR_ID;
    VersionInfoPtr->moduleID = ARTI_MODULE_ID;
    VersionInfoPtr->sw_major_version = ARTI_SW_MAJOR_VERSION;
    VersionInfoPtr->sw_minor_version = ARTI_SW_MINOR_VERSION;
    VersionInfoPtr->sw_patch_version = ARTI_SW_PATCH_VERSION;
}
