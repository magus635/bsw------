
/***************************************************************************************
    @Copyright: (C) 1989-2023 Lauterbach GmbH, licensed for use with TRACE32(R) only
 **************************************************************************************/

/***************************************************************************************
 *  FILE DESCRIPTION
 *         File:  arti.c
 *  Description:  Standard ARTI source file.
 *                This file includes the source file according to the tracing method.
 **************************************************************************************/


/***************************************************************************************
 * Standard includes
 **************************************************************************************/

#include "arti.h"

#ifdef ARTI_AUTOSAR
#  if (ARTI_DEV_ERROR_DETECT == STD_ON)
#    include "Det.h"
#  endif
#endif


/***************************************************************************************
 * AUTOSAR Arti Module Interface
 **************************************************************************************/

#ifdef ARTI_AUTOSAR
void Arti_GetVersionInfo (Std_VersionInfoType* VersionInfoPtr)
{
#if (ARTI_DEV_ERROR_DETECT == STD_ON)
    if (!VersionInfoPtr)
        Det_ReportError (5, 0, 1, ARTI_E_PARAM_POINTER);
#endif

    VersionInfoPtr->vendorID = 0x009D;  /* Lauterbach */
    VersionInfoPtr->moduleID = 5;       /* Arti */
    VersionInfoPtr->sw_major_version = 1;
    VersionInfoPtr->sw_minor_version = 0;
    VersionInfoPtr->sw_patch_version = 0;
}
#endif


/**********************************************************************************************************************
 * Trace specific sources
 ********************************************************************************************************************/

#ifdef ARTI_T32_DATA_TRACE
#include "arti_t32_data_trace/arti_t32_data_trace.c"
#define ARTI_T32_INCLUDED
#endif

#ifdef ARTI_T32_LOGGER
#include "arti_t32_logger/arti_t32_logger.c"
#define ARTI_T32_INCLUDED
#endif

#ifdef ARTI_T32_LOGGER_SINGLECORE
#include "arti_t32_logger_singlecore/arti_t32_logger_singlecore.c"
#define ARTI_T32_INCLUDED
#endif

#ifdef ARTI_T32_FDX
#include "arti_t32_fdx/arti_t32_fdx.c"
#define ARTI_T32_INCLUDED
#endif

#ifdef ARTI_T32_FDX_SINGLECORE
#include "arti_t32_fdx_singlecore/arti_t32_fdx_singlecore.c"
#define ARTI_T32_INCLUDED
#endif

#ifdef ARTI_T32_TC2xx_LMU_HIGHTEC
#include "arti_t32_tc2xx_lmu_hightec/arti_t32_tc2xx_lmu_hightec.c"
#define ARTI_T32_INCLUDED
#endif

#ifdef ARTI_T32_TC2xx_LMU_TASKING
#include "arti_t32_tc2xx_lmu_tasking/arti_t32_tc2xx_lmu_tasking.c"
#define ARTI_T32_INCLUDED
#endif

#ifdef ARTI_T32_TC3xx_OLDA_GHS
#include "arti_t32_tc3xx_olda_ghs/arti_t32_tc3xx_olda_ghs.c"
#define ARTI_T32_INCLUDED
#endif

#ifdef ARTI_T32_TC3xx_OLDA_HIGHTEC
#include "arti_t32_tc3xx_olda_hightec/arti_t32_tc3xx_olda_hightec.c"
#define ARTI_T32_INCLUDED
#endif

#ifdef ARTI_T32_TC3xx_OLDA_TASKING
#include "arti_t32_tc3xx_olda_tasking/arti_t32_tc3xx_olda_tasking.c"
#define ARTI_T32_INCLUDED
#endif


/***************************************************************************************
 * TRACE32 helpers
 **************************************************************************************/

#ifdef ARTI_ASAM
unsigned int t32_current = 0;
#endif


/***************************************************************************************
 *  END OF FILE: arti.c
 **************************************************************************************/
