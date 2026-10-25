/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Lin.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : ASI
*
*   brief                 : This file contains all functions of Lin Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/


/*
*#Violation Summary
*#Lin_c_REF_1:MISRAC2012-Rule-20.10; 
* Justification: Use glue operator to construct the exclusive area function name.
*
*#Lin_c_REF_2:MISRAC2012-Rule-20.7;
* Justification: Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*
*#Lin_c_REF_3:MISRAC2012-Rule-20.1;
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Lin_c_REF_4:MISRAC2012-Rule-10.5;
* Justification: Redundant cast is necessary to maintain the software structure and reduce the complexity.
*
*#Lin_c_REF_5:MISRAC2012-Dir-4.9;
* Justification: Function like macros are used to reduce code complexity.
*
*#Lin_c_REF_6:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
*#Lin_c_REF_7:CertC-DCL00-C;
* Justification: Parameter declared refer to AUTOSAR specifications.
*
*#Lin_c_REF_8:CertC-PRE00-C;
* Justification: Function like macros are used to reduce code complexity.
*
*#Lin_c_REF_9:CWE-547-C;
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*
*#Lin_c_REF_10:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access.
*
*#Lin_c_REF_11:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Lin.h"
#include "SchM_Lin.h"
#include "Lin_Cfg.h"
#include "LinIf.h"
#include "Mcall.h"
#include "Lin_Version.h"
#include "tha6_cfg.h"
/* Included for the declaration of Det_ReportError() */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */

/* Included for the declaration of Dem_SetEventStatus() */
#if (LIN_DEM_ERROR_REPORT_STATUS == STD_ON)
#include "Dem.h"
#endif /* (LIN_DEM_ERROR_REPORT_STATUS  \== STD_ON) */

/****************************************************************************************************
**                          Version Checks                                                         **
****************************************************************************************************/
/* Check if current file and LIN header file are of the same vendor */
#if (LIN_VENDOR_ID != LIN_CFG_VENDOR_ID)
  #error "Lin.c : Mismatch in Vendor ID"
#endif /* (LIN_VENDOR_ID \!= LIN_CFG_VENDOR_ID) */

#if (LIN_MODULE_ID != LIN_CFG_MODULE_ID)
  #error "Lin.c : Mismatch in Module ID"
#endif /* (LIN_MODULE_ID \!= LIN_CFG_MODULE_ID) */

#if (LIN_AR_RELEASE_MAJOR_VERSION != LIN_CFG_AR_RELEASE_MAJOR_VERSION)
  #error "Lin.c : Mismatch in Release Major Version"
#endif /* (LIN_AR_RELEASE_MAJOR_VERSION \!= LIN_CFG_AR_RELEASE_MAJOR_VERSION) */

#if (LIN_AR_RELEASE_MINOR_VERSION != LIN_CFG_AR_RELEASE_MINOR_VERSION)
  #error "Lin.c : Mismatch in Release Minor Version"
#endif /* (LIN_AR_RELEASE_MINOR_VERSION \!= LIN_CFG_AR_RELEASE_MINOR_VERSION) */

#if (LIN_AR_RELEASE_REVISION_VERSION != LIN_CFG_AR_RELEASE_REVISION_VERSION)
  #error "Lin.c : Mismatch in Release Revision Version"
#endif /* (LIN_AR_RELEASE_REVISION_VERSION \!= LIN_CFG_AR_RELEASE_REVISION_VERSION) */

#if (LIN_SW_MAJOR_VERSION != LIN_CFG_SW_MAJOR_VERSION)
  #error "Lin.c : Mismatch in Software Major Version"
#endif /* (LIN_SW_MAJOR_VERSION \!= LIN_CFG_SW_MAJOR_VERSION) */

#if (LIN_SW_MINOR_VERSION != LIN_CFG_SW_MINOR_VERSION)
  #error "Lin.c : Mismatch in Software Minor Version"
#endif /* (LIN_SW_MINOR_VERSION \!= LIN_CFG_SW_MINOR_VERSION) */

#if (LIN_SW_PATCH_VERSION != LIN_CFG_SW_PATCH_VERSION)
  #error "Lin.c : Mismatch in Software Patch Version"
#endif /* (LIN_SW_PATCH_VERSION \!= LIN_CFG_SW_PATCH_VERSION) */
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
#define LIN_INIT                           (1U)
#define LIN_UNINIT                         (0U)
/* Max SDU length */
#define LIN_MAX_SDU_BUFFER_LENGTH              (8U)
/* Mask: Get the error status register LINESR value */
#define LIN_ERROR_STATUS_VALUE_MASK        (0xFFFFU)

/****************************************************************************************************
*                          SchM Critical Section Protection Macros                                 **
****************************************************************************************************/
/* #Violation: Lin_c_REF_1 */ 
/* #Violation: Lin_c_REF_8 */ 
#define LIN_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Lin_##Exclusive_Area() 
/* #Violation: Lin_c_REF_1 */ 
/* #Violation: Lin_c_REF_8 */ 
#define LIN_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Lin_##Exclusive_Area() 

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#if (LIN_MAX_CHANNEL_TO_CORE0 > 0U)
/* #Violation: Lin_c_REF_11*/
#define LIN_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 

/* Lin channel internal status machine */
static Lin_ChInternalStatusType Lin_ChannelStatusCore0[LIN_MAX_CHANNEL_TO_CORE0];
/* Lin channel SDU buffer, size = Lin channel number * Max length of data buffer */
static uint8 Lin_SduBufferCore0[LIN_MAX_CHANNEL_TO_CORE0 * LIN_MAX_SDU_BUFFER_LENGTH];

/* #Violation: Lin_c_REF_11*/
#define LIN_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 

/* #Violation: Lin_c_REF_11*/
#define LIN_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 

/* Lin initialization status in core0 */
/* \[SWS_Lin_00145]   Reset -> LIN_UNINIT: After reset, the Lin module shall set its 
state to LIN_UNINIT.  */
static uint8 Lin_InitStatusCore0;

/* #Violation: Lin_c_REF_11*/
#define LIN_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 

/* #Violation: Lin_c_REF_3 */
#define LIN_START_SEC_CONST_ASIL_D_CORE0_UNSPECIFIED 
/* #Violation: Lin_c_REF_3 */ 
#include "Lin_MemMap.h" 

/* Holding core0 specific LIN channel status */
static const Lin_CoreStatusType Lin_StatusSetCore0 =
{
    &Lin_ChannelStatusCore0[0],
    &Lin_InitStatusCore0,
    &Lin_SduBufferCore0[0]
};

/* #Violation: Lin_c_REF_3 */
#define LIN_STOP_SEC_CONST_ASIL_D_CORE0_UNSPECIFIED 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 

#endif /* (LIN_MAX_CHANNEL_TO_CORE0 \> 0U) */

#if (MCAL_NUMBER_OF_CORES > 1U)
#if (LIN_MAX_CHANNEL_TO_CORE1 > 0U)

/* #Violation: Lin_c_REF_11*/
#define LIN_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 

/* Lin channel internal status machine */
static Lin_ChInternalStatusType Lin_ChannelStatusCore1[LIN_MAX_CHANNEL_TO_CORE1];
/* Lin channel SDU buffer */
static uint8 Lin_SduBufferCore1[LIN_MAX_CHANNEL_TO_CORE1 * LIN_MAX_SDU_BUFFER_LENGTH];

/* #Violation: Lin_c_REF_11*/
#define LIN_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 

/* #Violation: Lin_c_REF_11*/
#define LIN_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 

/* Lin initialization status in core1 */
/* \[SWS_Lin_00145]   Reset -> LIN_UNINIT: After reset, the Lin module shall set its 
state to LIN_UNINIT.  */
static uint8 Lin_InitStatusCore1;

/* #Violation: Lin_c_REF_11*/
#define LIN_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 

/* #Violation: Lin_c_REF_11 */
#define LIN_START_SEC_CONST_ASIL_D_CORE1_UNSPECIFIED 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 


/* Holding core1 specific LIN channel status */
static const Lin_CoreStatusType Lin_StatusSetCore1 =
{
    &Lin_ChannelStatusCore1[0],
    &Lin_InitStatusCore1,
    &Lin_SduBufferCore1[0],
};

/* #Violation: Lin_c_REF_11 */
#define LIN_STOP_SEC_CONST_ASIL_D_CORE1_UNSPECIFIED 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 
#endif /* (LIN_MAX_CHANNEL_TO_CORE1 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 1U) */

#if (MCAL_NUMBER_OF_CORES > 2U)
#if (LIN_MAX_CHANNEL_TO_CORE2 > 0U)
/* #Violation: Lin_c_REF_11*/
#define LIN_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 


/* Lin channel internal status machine */
static Lin_ChInternalStatusType Lin_ChannelStatusCore2[LIN_MAX_CHANNEL_TO_CORE2];
/* Lin channel SDU buffer */
static uint8 Lin_SduBufferCore2[LIN_MAX_CHANNEL_TO_CORE2 * LIN_MAX_SDU_BUFFER_LENGTH];
/* #Violation: Lin_c_REF_11*/
#define LIN_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 

/* #Violation: Lin_c_REF_11*/
#define LIN_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 


/* Lin initialization status in core2 */
/* \[SWS_Lin_00145]   Reset -> LIN_UNINIT: After reset, the Lin module shall set its 
state to LIN_UNINIT.  */
static uint8 Lin_InitStatusCore2;
/* #Violation: Lin_c_REF_11*/
#define LIN_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 

/* #Violation: Lin_c_REF_11*/
#define LIN_START_SEC_CONST_ASIL_D_CORE2_UNSPECIFIED 
/* #Violation: Lin_c_REF_3*/
#include "Lin_MemMap.h" 


/* Holding core2 specific LIN channel status */
static const Lin_CoreStatusType Lin_StatusSetCore2 =
{
    &Lin_ChannelStatusCore2[0],
    &Lin_InitStatusCore2,
    &Lin_SduBufferCore2[0],
};
/* #Violation: Lin_c_REF_11*/
#define LIN_STOP_SEC_CONST_ASIL_D_CORE2_UNSPECIFIED 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 

#endif /* (LIN_MAX_CHANNEL_TO_CORE2 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 2U) */

#if (MCAL_NUMBER_OF_CORES > 3U)
#if (LIN_MAX_CHANNEL_TO_CORE3 > 0U)
/* #Violation: Lin_c_REF_11*/
#define LIN_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 


/* Lin channel internal status machine */
static Lin_ChInternalStatusType Lin_ChannelStatusCore3[LIN_MAX_CHANNEL_TO_CORE3];
/* Lin channel SDU buffer */
static uint8 Lin_SduBufferCore3[LIN_MAX_CHANNEL_TO_CORE3 * LIN_MAX_SDU_BUFFER_LENGTH];
/* #Violation: Lin_c_REF_11*/
#define LIN_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 

/* #Violation: Lin_c_REF_11*/
#define LIN_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 


/* Lin initialization status in core3 */
/* \[SWS_Lin_00145]   Reset -> LIN_UNINIT: After reset, the Lin module shall set its 
state to LIN_UNINIT.  */
static uint8 Lin_InitStatusCore3;
/* #Violation: Lin_c_REF_11*/
#define LIN_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 

/* #Violation: Lin_c_REF_11*/
#define LIN_START_SEC_CONST_ASIL_D_CORE3_UNSPECIFIED 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 


/* Holding core3 specific LIN channel status */
static const Lin_CoreStatusType Lin_StatusSetCore3 =
{
    &Lin_ChannelStatusCore3[0],
    &Lin_InitStatusCore3,
    &Lin_SduBufferCore3[0],
};

#define LIN_STOP_SEC_CONST_ASIL_D_CORE3_UNSPECIFIED 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 

#endif /* (LIN_MAX_CHANNEL_TO_CORE3 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 3U) */

/* #Violation: Lin_c_REF_11 */
#define LIN_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 

/* Channel status information for all core */
static CONSTP2CONST(Lin_CoreStatusType, LIN_VAR, LIN_APPL_CONST)
                                      Lin_CoreStatus[MCAL_NUMBER_OF_CORES] =
{
#if (LIN_MAX_CHANNEL_TO_CORE0 > 0U)
    &Lin_StatusSetCore0
#else
    NULL_PTR
#endif /* (LIN_MAX_CHANNEL_TO_CORE0 \> 0U) */

#if (MCAL_NUMBER_OF_CORES > 1U)
#if (LIN_MAX_CHANNEL_TO_CORE1 > 0U)
    ,&Lin_StatusSetCore1
#else
    ,NULL_PTR
#endif /* (LIN_MAX_CHANNEL_TO_CORE1 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 1U) */

#if (MCAL_NUMBER_OF_CORES > 2U)
#if (LIN_MAX_CHANNEL_TO_CORE2 > 0U)
    ,&Lin_StatusSetCore2
#else
    ,NULL_PTR
#endif /* (LIN_MAX_CHANNEL_TO_CORE2 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 2U) */

#if (MCAL_NUMBER_OF_CORES > 3U)
#if (LIN_MAX_CHANNEL_TO_CORE3 > 0U)
    ,&Lin_StatusSetCore3
#else
    ,NULL_PTR
#endif /* (LIN_MAX_CHANNEL_TO_CORE3 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 3U) */
};

/* #Violation: Lin_c_REF_11*/
#define LIN_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 

/* #Violation: Lin_c_REF_11*/
#define LIN_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 

static P2CONST(Lin_ConfigType, LIN_VAR, LIN_APPL_CONST) Lin_ConfigPtr;

/* #Violation: Lin_c_REF_11*/
#define LIN_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/
/* #Violation: Lin_c_REF_11*/
#define LIN_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 

/* Lin module register base address packaging */
/* #Violation: Lin_c_REF_2 */
static CONSTP2VAR(ASI_MODULE, AUTOMATIC, SPI_APPL_CONST) Lin_BaseAddr[LIN_MAX_HWUNIT_COUNT] =
{
#if (LIN_MAX_HWUNIT_COUNT > 0U)
#if defined(LIN_HWUNIT_CHANNEL0)
    ASI0
#else /* \!defined(LIN_HWUNIT_CHANNEL0) */
    NULL_PTR
#endif /* defined(LIN_HWUNIT_CHANNEL0) */
#endif /* (LIN_MAX_HWUNIT_COUNT \> 0U) */

#if (LIN_MAX_HWUNIT_COUNT > 1U)
#if defined(LIN_HWUNIT_CHANNEL1)
    ,ASI1
#else /* \!defined(LIN_HWUNIT_CHANNEL1) */
    ,NULL_PTR
#endif /* defined(LIN_HWUNIT_CHANNEL1) */
#endif /* (LIN_MAX_HWUNIT_COUNT \> 1U) */

#if (LIN_MAX_HWUNIT_COUNT > 2U)
#if defined(LIN_HWUNIT_CHANNEL2)
    /* #Violation: Lin_c_REF_6 */
    ,ASI2
#else /* \!defined(LIN_HWUNIT_CHANNEL2) */
    ,NULL_PTR
#endif /* defined(LIN_HWUNIT_CHANNEL2) */
#endif /* (LIN_MAX_HWUNIT_COUNT \> 2U) */

#if (LIN_MAX_HWUNIT_COUNT > 3U)
#if defined(LIN_HWUNIT_CHANNEL3)
    /* #Violation: Lin_c_REF_6 */
    ,ASI3 
#else /* \!defined(LIN_HWUNIT_CHANNEL3) */
    ,NULL_PTR
#endif /* defined(LIN_HWUNIT_CHANNEL3) */
#endif /* (LIN_MAX_HWUNIT_COUNT \> 3U) */

#if (LIN_MAX_HWUNIT_COUNT > 4U)
#if defined(LIN_HWUNIT_CHANNEL4)
    ,ASI4
#else /* \!defined(LIN_HWUNIT_CHANNEL4) */
    ,NULL_PTR
#endif /* defined(LIN_HWUNIT_CHANNEL4) */
#endif /* (LIN_MAX_HWUNIT_COUNT \> 4U) */

#if (LIN_MAX_HWUNIT_COUNT > 5U)
#if defined(LIN_HWUNIT_CHANNEL5)
    /* #Violation: Lin_c_REF_6 */
    ,ASI5 
#else /* \!defined(LIN_HWUNIT_CHANNEL5) */
    ,NULL_PTR
#endif /* defined(LIN_HWUNIT_CHANNEL5) */
#endif /* (LIN_MAX_HWUNIT_COUNT \> 5U) */

#if (LIN_MAX_HWUNIT_COUNT > 6U)
#if defined(LIN_HWUNIT_CHANNEL6)
    ,ASI6
#else /* \!defined(LIN_HWUNIT_CHANNEL6) */
    ,NULL_PTR
#endif /* defined(LIN_HWUNIT_CHANNEL6) */
#endif /* (LIN_MAX_HWUNIT_COUNT \> 6U) */

#if (LIN_MAX_HWUNIT_COUNT > 7U)
#if defined(LIN_HWUNIT_CHANNEL7)
    ,ASI7
#else /* \!defined(LIN_HWUNIT_CHANNEL7) */
    ,NULL_PTR
#endif /* defined(LIN_HWUNIT_CHANNEL7) */
#endif /* (LIN_MAX_HWUNIT_COUNT \> 7U) */

#if (LIN_MAX_HWUNIT_COUNT > 8U)
#if defined(LIN_HWUNIT_CHANNEL8)
    ,ASI8
#else /* \!defined(LIN_HWUNIT_CHANNEL8) */
    ,NULL_PTR
#endif /* defined(LIN_HWUNIT_CHANNEL8) */
#endif /* (LIN_MAX_HWUNIT_COUNT \> 8U) */

#if (LIN_MAX_HWUNIT_COUNT > 9U)
#if defined(LIN_HWUNIT_CHANNEL9)
    ,ASI9
#else /* \!defined(LIN_HWUNIT_CHANNEL9) */
    ,NULL_PTR
#endif /* defined(LIN_HWUNIT_CHANNEL9) */
#endif /* (LIN_MAX_HWUNIT_COUNT \> 9U) */

#if (LIN_MAX_HWUNIT_COUNT > 10U)
#if defined(LIN_HWUNIT_CHANNEL10)
    ,ASI10
#else /* \!defined(LIN_HWUNIT_CHANNEL10) */
    ,NULL_PTR
#endif /* defined(LIN_HWUNIT_CHANNEL10) */
#endif /* (LIN_MAX_HWUNIT_COUNT \> 10U) */

#if (LIN_MAX_HWUNIT_COUNT > 11U)
#if defined(LIN_HWUNIT_CHANNEL11)
    ,ASI11
#else /* \!defined(LIN_HWUNIT_CHANNEL11) */
    ,NULL_PTR
#endif /* defined(LIN_HWUNIT_CHANNEL11) */
#endif /* (LIN_MAX_HWUNIT_COUNT \> 11U) */

#if (LIN_MAX_HWUNIT_COUNT > 12U)
#if defined(LIN_HWUNIT_CHANNEL12)
    ,ASI12
#else /* \!defined(LIN_HWUNIT_CHANNEL12) */
    ,NULL_PTR
#endif /* defined(LIN_HWUNIT_CHANNEL12) */
#endif /* (LIN_MAX_HWUNIT_COUNT \> 12U) */

#if (LIN_MAX_HWUNIT_COUNT > 13U)
#if defined(LIN_HWUNIT_CHANNEL13)
    ,ASI13
#else /* \!defined(LIN_HWUNIT_CHANNEL13) */
    ,NULL_PTR
#endif /* defined(LIN_HWUNIT_CHANNEL13) */
#endif /* (LIN_MAX_HWUNIT_COUNT \> 13U) */

#if (LIN_MAX_HWUNIT_COUNT > 14U)
#if defined(LIN_HWUNIT_CHANNEL14)
    ,ASI14
#else /* \!defined(LIN_HWUNIT_CHANNEL14) */
    ,NULL_PTR
#endif /* defined(LIN_HWUNIT_CHANNEL14) */
#endif /* (LIN_MAX_HWUNIT_COUNT \> 14U) */

#if (LIN_MAX_HWUNIT_COUNT > 15U)
#if defined(LIN_HWUNIT_CHANNEL15)
    ,ASI15
#else /* \!defined(LIN_HWUNIT_CHANNEL15) */
    ,NULL_PTR
#endif /* defined(LIN_HWUNIT_CHANNEL15) */
#endif /* (LIN_MAX_HWUNIT_COUNT \> 15U) */

#if (LIN_MAX_HWUNIT_COUNT > 16U)
#if defined(LIN_HWUNIT_CHANNEL16)
    ,ASI16
#else /* \!defined(LIN_HWUNIT_CHANNEL16) */
    ,NULL_PTR
#endif /* defined(LIN_HWUNIT_CHANNEL16) */
#endif /* (LIN_MAX_HWUNIT_COUNT \> 16U) */

#if (LIN_MAX_HWUNIT_COUNT > 17U)
#if defined(LIN_HWUNIT_CHANNEL17)
    ,ASI17
#else /* \!defined(LIN_HWUNIT_CHANNEL17) */
    ,NULL_PTR
#endif /* defined(LIN_HWUNIT_CHANNEL17) */
#endif /* (LIN_MAX_HWUNIT_COUNT \> 17U) */

#if (LIN_MAX_HWUNIT_COUNT > 18U)
#if defined(LIN_HWUNIT_CHANNEL18)
    ,ASI18
#else /* \!defined(LIN_HWUNIT_CHANNEL18) */
    ,NULL_PTR
#endif /* defined(LIN_HWUNIT_CHANNEL18) */
#endif /* (LIN_MAX_HWUNIT_COUNT \> 18U) */

#if (LIN_MAX_HWUNIT_COUNT > 19U)
#if defined(LIN_HWUNIT_CHANNEL19)
    ,ASI19
#else /* \!defined(LIN_HWUNIT_CHANNEL19) */
    ,NULL_PTR
#endif /* defined(LIN_HWUNIT_CHANNEL19) */
#endif /* (LIN_MAX_HWUNIT_COUNT \> 19U) */

#if (LIN_MAX_HWUNIT_COUNT > 20U)
#if defined(LIN_HWUNIT_CHANNEL20)
    ,ASI20
#else /* \!defined(LIN_HWUNIT_CHANNEL20) */
    ,NULL_PTR
#endif /* defined(LIN_HWUNIT_CHANNEL20) */
#endif /* (LIN_MAX_HWUNIT_COUNT \> 20U) */

#if (LIN_MAX_HWUNIT_COUNT > 21U)
#if defined(LIN_HWUNIT_CHANNEL21)
    ,ASI21
#else /* \!defined(LIN_HWUNIT_CHANNEL21) */
    ,NULL_PTR
#endif /* defined(LIN_HWUNIT_CHANNEL21) */
#endif /* (LIN_MAX_HWUNIT_COUNT \> 21U) */

#if (LIN_MAX_HWUNIT_COUNT > 22U)
#if defined(LIN_HWUNIT_CHANNEL22)
    ,ASI22
#else /* \!defined(LIN_HWUNIT_CHANNEL22) */
    ,NULL_PTR
#endif /* defined(LIN_HWUNIT_CHANNEL22) */
#endif /* (LIN_MAX_HWUNIT_COUNT \> 22U) */

#if (LIN_MAX_HWUNIT_COUNT > 23U)
#if defined(LIN_HWUNIT_CHANNEL23)
    ,ASI23
#else /* \!defined(LIN_HWUNIT_CHANNEL23) */
    ,NULL_PTR
#endif /* \defined(LIN_HWUNIT_CHANNEL23) */
#endif /* (LIN_MAX_HWUNIT_COUNT \> 23U) */

};
/* #Violation: Lin_c_REF_11*/
#define LIN_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 
/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
/* #Violation: Lin_c_REF_11*/
#define LIN_START_SEC_CODE_ASIL_D_GLOBAL 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 

static FUNC(Std_ReturnType, LIN_PRIVATE_CODE) Lin_CheckInitDetStatus(
    Mcal_CoreType CoreId,
    uint8 ServiceId,
    CONSTP2CONST(Lin_ConfigType, AUTOMATIC, LIN_APPL_CONST) ConfigPtr
);

static FUNC(Std_ReturnType, LIN_PRIVATE_CODE) Lin_CheckRuntimeDetStatus(
    Mcal_CoreType CoreId,
    uint8 Channel,
    uint8 ServiceId
);

static FUNC(Std_ReturnType, LIN_PRIVATE_CODE) Lin_GetDetStatus
(
    Mcal_CoreType   CoreId,
    uint8           Channel,
    uint8           ServiceId,
    CONSTP2CONST(Lin_ConfigType, AUTOMATIC, LIN_APPL_CONST) ConfigPtr
);

#if ((LIN_CFG_INTERRUPT_ENABLE == STD_ON) && ((LIN_WAKEUP_SUPPORT == STD_ON)))
static FUNC(void, LIN_PRIVATE_CODE) Lin_WakeupDetect
(
    P2CONST(Lin_ChannelConfigType, AUTOMATIC, LIN_APPL_CONST) ChannelConfigPtr,
    boolean       EnableWakeupDetect
);
#endif /* ((LIN_CFG_INTERRUPT_ENABLE == STD_ON) \&& ((LIN_WAKEUP_SUPPORT == STD_ON))) */

static FUNC(void, LIN_PRIVATE_CODE) Lin_ClearLinChBuffer
(
    CONSTP2CONST(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr
);

#if (LIN_MASTER_MODE_USED == STD_ON)
static FUNC(Std_ReturnType, LIN_PRIVATE_CODE) Lin_SendFrameData
(
    CONSTP2CONST(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr,
    Lin_HWUnitType HwUnit
);

static FUNC(Std_ReturnType, LIN_PRIVATE_CODE) Lin_GoToSleepCmd
(
    /* #Violation: Lin_c_REF_2 */
    CONSTP2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr,
    Lin_HWUnitType HwUnit
);
#endif /* (LIN_MASTER_MODE_USED \== STD_ON) */

static FUNC(Std_ReturnType, LIN_PRIVATE_CODE) Lin_GoToSleepInternalCmd
(
    Lin_HWUnitType HwUnit
);

static FUNC(Std_ReturnType, LIN_PRIVATE_CODE) Lin_WakeupCmd
(
    CONSTP2CONST(Lin_ChannelConfigType, AUTOMATIC, LIN_APPL_CONST) ChannelConfigPtr
);

static FUNC(Std_ReturnType, LIN_PRIVATE_CODE) Lin_WakeupInternalCmd
(
    CONSTP2CONST(Lin_ChannelConfigType, AUTOMATIC, LIN_APPL_CONST) ChannelConfigPtr
);

#if (LIN_MASTER_MODE_USED == STD_ON)
static FUNC(void, LIN_PRIVATE_CODE) Lin_HandleHeaderComplete
(
    /* #Violation: Lin_c_REF_2 */
    CONSTP2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr
);

static FUNC(void, LIN_PRIVATE_CODE) Lin_HandleResponseActive
(
    /* #Violation: Lin_c_REF_2 */
    CONSTP2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr
);

static FUNC(void, LIN_PRIVATE_CODE) Lin_HandleErrorStatus
(
    /* #Violation: Lin_c_REF_2 */
    CONSTP2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr,
    uint32 RegValue
);

static FUNC(void, LIN_PRIVATE_CODE) Lin_ChStatusFromHwReg
(
    /* #Violation: Lin_c_REF_2 */
    CONSTP2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr,
    Lin_HWUnitType HwUnit
);

static FUNC(Lin_StatusType, LIN_PRIVATE_CODE) Lin_GetChStatus
(
    /* #Violation: Lin_c_REF_2 */
    CONSTP2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr,
    Lin_HWUnitType HwUnit
);

static FUNC(Lin_StatusType, LIN_PRIVATE_CODE) Lin_ChannelStateTransition
(
    Lin_ChStatusType ChannelStatus
);
#endif /* (LIN_MASTER_MODE_USED \== STD_ON) */

static FUNC(void, LIN_PRIVATE_CODE) Lin_IsrRecvDataHandler
(
    /* #Violation: Lin_c_REF_2 */
    CONSTP2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr,
    CONSTP2CONST(Lin_ChannelConfigType, AUTOMATIC, LIN_APPL_CONST) ChannelConfigPtr
);

#if (LIN_CFG_INTERRUPT_ENABLE == STD_ON)
static FUNC(void, LIN_PRIVATE_CODE) Lin_HandleMasterOtherErrors
(
    /* #Violation: Lin_c_REF_2 */
    CONSTP2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr,
    CONSTP2CONST(Lin_ChannelConfigType, AUTOMATIC, LIN_APPL_CONST) ChannelConfigPtr
);
#endif /* \(LIN_CFG_INTERRUPT_ENABLE \== STD_ON) */

static FUNC(void, LIN_PRIVATE_CODE) Lin_IsrMasterErrorHandler
(
    /* #Violation: Lin_c_REF_2 */
    CONSTP2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr,
    CONSTP2CONST(Lin_ChannelConfigType, AUTOMATIC, LIN_APPL_CONST) ChannelConfigPtr
);

#if ((LIN_CFG_INTERRUPT_ENABLE == STD_ON) && (LIN_SLAVE_MODE_USED == STD_ON))
static FUNC(void, LIN_PRIVATE_CODE) Lin_IsrRecvHeaderHandler
(
    /* #Violation: Lin_c_REF_2 */
    P2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr,
    CONSTP2CONST(Lin_ChannelConfigType, AUTOMATIC, LIN_APPL_CONST) ChannelConfigPtr
);

static FUNC(void, LIN_PRIVATE_CODE) Lin_HandleOtherErrors
(
    /* #Violation: Lin_c_REF_2 */
    CONSTP2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr,
    CONSTP2CONST(Lin_ChannelConfigType, AUTOMATIC, LIN_APPL_CONST) ChannelConfigPtr,
    Lin_HWUnitType HwUnit
);

static FUNC(void, LIN_PRIVATE_CODE) Lin_IsrSlaveErrorHandler
(
    /* #Violation: Lin_c_REF_2 */
    CONSTP2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr,
    CONSTP2CONST(Lin_ChannelConfigType, AUTOMATIC, LIN_APPL_CONST) ChannelConfigPtr
);

static FUNC(void, LIN_PRIVATE_CODE) Lin_IsrTxHandler
(
    /* #Violation: Lin_c_REF_2 */
    CONSTP2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr,
    CONSTP2CONST(Lin_ChannelConfigType, AUTOMATIC, LIN_APPL_CONST) ChannelConfigPtr
);

static FUNC(Lin_FramePidType, LIN_PRIVATE_CODE) Lin_CalculatePid
(
    uint8           FramePid
);
#endif /* ((LIN_CFG_INTERRUPT_ENABLE == STD_ON) && (LIN_SLAVE_MODE_USED \== STD_ON)) */

static FUNC(void, LIN_PRIVATE_CODE) Lin_IsrWakeupHandler
(
    /* #Violation: Lin_c_REF_2 */
    CONSTP2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr,
    CONSTP2CONST(Lin_ChannelConfigType, AUTOMATIC, LIN_APPL_CONST) ChannelConfigPtr
);

/* #Violation: Lin_c_REF_11*/
#define LIN_STOP_SEC_CODE_ASIL_D_GLOBAL 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
/* #Violation: Lin_c_REF_11*/
#define LIN_START_SEC_CODE_ASIL_D_GLOBAL 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 

/****************************************************************************************************
*   Function Name           : Lin_CheckInitDetStatus
*
*   Service ID              : None.
*
*   Description             : DET check and return check RetStatus, when ServiceId == LIN_SID_INIT.
*
*   Parameters in           : CoreId: Current execution core ID
*                             ServiceId: API service ID
*                             ConfigPtr: configuration parameter pointer ,If there is no 
*                                        configuration parameter, it is marked with NULL_PTR
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK: No DET error
*                             E_NOT_OK: DET error.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, LIN_PRIVATE_CODE) Lin_CheckInitDetStatus
(
    Mcal_CoreType   CoreId,
    uint8           ServiceId,
    CONSTP2CONST(Lin_ConfigType, AUTOMATIC, LIN_APPL_CONST) ConfigPtr
)
{
    Std_ReturnType                  RetStatus;
    /* Set the initial function return status value */
    RetStatus = E_NOT_OK;

    if(NULL_PTR == ConfigPtr)
    {            
#if (LIN_DEV_ERROR_DETECT == STD_ON)
    /* Invalid pointer */
    /* \[SWS_Lin_00099]   If default error detection for the Lin module is enabled: the 
    function Lin_Init shall check the parameter Config for being within the allowed range. 
    If Config is not in the allowed range, the function Lin_Init shall raise the default error 
    LIN_E_INVALID_POINTER.  */
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, ServiceId,
                              LIN_E_INVALID_POINTER);
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
    }
    else if(NULL_PTR == Lin_CoreStatus[CoreId])
    {
#if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* Not Lin driver RetStatus information storage variable in current core */
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, ServiceId,
                              LIN_E_CORE_NOT_CONFIGURED);
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
    }
    else if(NULL_PTR == ConfigPtr->CoreConfigPtr[CoreId])
    {
#if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* Not Lin driver RetStatus information storage variable in current core */
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, ServiceId,
                              LIN_E_CORE_NOT_CONFIGURED);
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
    }
    else if(LIN_INIT == *(Lin_CoreStatus[CoreId]->CoreInitStatusPtr))
    {
#if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* API service used without module initialization */
        /* \[SWS_Lin_00105]   If default error detection for the Lin module is enabled: the 
        function Lin_Init shall check the Lin driver for being in the state LIN_UNINIT. If the Lin 
        driver is not in the state LIN_UNINIT, the function Lin_Init shall raise the default error 
        LIN_E_STATE_TRANSITION.  */
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, ServiceId,
                              LIN_E_STATE_TRANSITION);
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
    }
    else
    {
        RetStatus = E_OK;
    }

#if (LIN_DEV_ERROR_DETECT == STD_OFF)
    MCAL_UNUSED_VAR(ServiceId);
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Lin_CheckRuntimeDetStatus
*
*   Service ID              : None.
*
*   Description             : DET check and return check RetStatus, when ServiceId != LIN_SID_INIT.
*
*   Parameters in           : CoreId: Current execution core ID
*                             Channel: Lin logical channel, if there is no logical channe,
*                                       it is marked with 0xFF
*                             ServiceId: API service ID
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK: No DET error
*                             E_NOT_OK: DET error.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, LIN_PRIVATE_CODE) Lin_CheckRuntimeDetStatus
(
    Mcal_CoreType   CoreId,
    uint8           Channel,
    uint8           ServiceId
)
{
    Std_ReturnType                  RetStatus;
    /* Set the initial function return status value */
    RetStatus = E_NOT_OK;
    const Lin_CoreConfigType        *CorexConfigPtr;

    /* Read the core configuration information from Lin_ConfigPtr */
    CorexConfigPtr = Lin_ConfigPtr->CoreConfigPtr[CoreId];
    if(NULL_PTR == Lin_CoreStatus[CoreId])
    {
#if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* Not Lin driver RetStatus information storage variable in current core */
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, ServiceId,
                                LIN_E_CORE_NOT_CONFIGURED);
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
    }
    else if(LIN_UNINIT == *(Lin_CoreStatus[CoreId]->CoreInitStatusPtr))
    {
#if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* API service used with an invalid or inactive channel parameter */
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, ServiceId,
                                LIN_E_UNINIT);
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
    }
    else if (NULL_PTR == CorexConfigPtr)
    {
#if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* Channel Config in current core is NULL */
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, ServiceId,
                                LIN_E_CORE_NOT_CONFIGURED);
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
    }
    else if (Channel >= LIN_TOTAL_CFG_CHANNEL_NUM)
    {
#if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* API service used with an invalid or inactive channel parameter */
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, ServiceId,
                                LIN_E_INVALID_CHANNEL);
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
    }
    else if (Lin_ConfigPtr->ChannelToCorePtr[Channel] >= 
                CorexConfigPtr->MaxCoreChannels)
    {
#if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* Channel number is greater than maximum configured of current core */
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, ServiceId,
                                LIN_E_CORE_CHANNEL_MISMATCH);
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
    }
    else if (Channel != CorexConfigPtr->
                ChannelConfigPtr[Lin_ConfigPtr->ChannelToCorePtr[Channel]].ChannelId)
    {
#if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* Logical channel is mismatch */
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, ServiceId,
                                LIN_E_CORE_CHANNEL_MISMATCH);
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
    }
    else if ((Lin_HWUnitType)LIN_MAX_HWUNIT_COUNT <= CorexConfigPtr->
                ChannelConfigPtr[Lin_ConfigPtr->ChannelToCorePtr[Channel]].HwUnitId)
    {
#if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* Logical channel is mismatch */
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, ServiceId,
                                LIN_E_CORE_CHANNEL_MISMATCH);
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
    }
    else if (NULL_PTR == 
                Lin_BaseAddr[CorexConfigPtr->
                ChannelConfigPtr[Lin_ConfigPtr->ChannelToCorePtr[Channel]].HwUnitId])
    {
#if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* Logical channel is mismatch */
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, ServiceId,
                                LIN_E_CORE_CHANNEL_MISMATCH);
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
    }
    else
    {
        RetStatus = E_OK;
    }

#if (LIN_DEV_ERROR_DETECT == STD_OFF)
    MCAL_UNUSED_VAR(ServiceId);
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */

    return RetStatus;
}


/****************************************************************************************************
*   Function Name           : Lin_GetDetStatus
*
*   Service ID              : None.
*
*   Description             : DET check and return check RetStatus.
*
*   Parameters in           : CoreId: Current execution core ID
*                             Channel: Lin logical channel, if there is no logical channe,
*                                       it is marked with 0xFF
*                             ServiceId: API service ID
*                             ConfigPtr: configuration parameter pointer ,If there is no 
*                                        configuration parameter, it is marked with NULL_PTR
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK: No DET error
*                             E_NOT_OK: DET error.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, LIN_PRIVATE_CODE) Lin_GetDetStatus
(
    Mcal_CoreType   CoreId,
    uint8           Channel,
    uint8           ServiceId,
    CONSTP2CONST(Lin_ConfigType, AUTOMATIC, LIN_APPL_CONST) ConfigPtr
)
{
    Std_ReturnType                  RetStatus;

    /* Init API DET Diagnosis */
    if(LIN_SID_INIT == ServiceId)
    {
        RetStatus = Lin_CheckInitDetStatus(CoreId, ServiceId, ConfigPtr);
    }
    else
    {
        RetStatus = Lin_CheckRuntimeDetStatus(CoreId, Channel, ServiceId);
    }

    return RetStatus;
}

#if ((LIN_CFG_INTERRUPT_ENABLE == STD_ON) && ((LIN_WAKEUP_SUPPORT == STD_ON)))
/****************************************************************************************************
*   Function Name           : Lin_WakeupDetect
*
*   Service ID              : None.
*
*   Description             : Enable/Disable wake-up detection interrupt.
*
*   Parameters in           : ChannelConfigPtr: Lin channel config pointer.
                              EnableWakeupDetect: Enable/Disable wake-up detection interrupt.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, LIN_PRIVATE_CODE) Lin_WakeupDetect
(
    P2CONST(Lin_ChannelConfigType, AUTOMATIC, LIN_APPL_CONST) ChannelConfigPtr,
    boolean       EnableWakeupDetect
)
{
    if (TRUE == ChannelConfigPtr->ChannelWakeupSupport)
    {
        if (TRUE == EnableWakeupDetect)
        {
            /* Enable wake-up detection interrupt */
            Asi_Lin_Hal_SetInterrupt(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], ASI_LIN_WAKEUP_INT, TRUE);
            /* Disable Rx detection interrupt */
            Asi_Lin_Hal_SetInterrupt(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], (ASI_LIN_DATA_RX_COMPLETED_INT | ASI_LIN_ALL_ERROR_INTS), FALSE);
        }
        else
        {
            /* Disable wake-up detection interrupt */
            Asi_Lin_Hal_SetInterrupt(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], ASI_LIN_WAKEUP_INT, FALSE);
            /* Enable Rx detection interrupt */
            Asi_Lin_Hal_SetInterrupt(Lin_BaseAddr[ChannelConfigPtr->HwUnitId],
                        (ASI_LIN_DATA_RX_COMPLETED_INT | ASI_LIN_ALL_ERROR_INTS), TRUE);
        }
    }
}

#endif  /* ((LIN_CFG_INTERRUPT_ENABLE == STD_OFF) \&& ((LIN_WAKEUP_SUPPORT == STD_ON))) */

/****************************************************************************************************
*   Function Name           : Lin_ClearLinChBuffer
*
*   Service ID              : None.
*
*   Description             : Clear LIN channel buffer.
*
*   Parameters in           : ChannelStatusPtr: Point to current LIN Channel Status.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK: No DET error
*                             E_NOT_OK: DET error.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, LIN_PRIVATE_CODE) Lin_ClearLinChBuffer
(
    CONSTP2CONST(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr
)
{
    uint8 LoopCount;

    for (LoopCount = 0U; LoopCount < ChannelStatusPtr->PduBuffer.Dl; LoopCount++)
    {
        ChannelStatusPtr->PduBuffer.SduPtr[LoopCount] = 0U;
    }
}

#if (LIN_MASTER_MODE_USED == STD_ON)
/****************************************************************************************************
*   Function Name           : Lin_SendFrameData
*
*   Service ID              : None
*
*   Description             : Sends the LIN frame.
*                               Initiates the transmission of the header part and response part
*                               of the LIN frame on Channel using information stored on PduInfoPtr
*                               pointer.
*
*   Parameters in           : ChannelStatusPtr: Point to current LIN channel status.
*                             HwUnit: ASI Hardware unit, 0-23.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK: Send succeeded.
*                             E_NOT_OK: In case of a time out situation only.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, LIN_PRIVATE_CODE) Lin_SendFrameData
(
    CONSTP2CONST(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr,
    Lin_HWUnitType HwUnit
)
{
    Std_ReturnType          RetStatus;
    Lin_FrameControlType    LinFrameControl;


    LIN_ENTER_CRITICAL_SECTION(SendFrame);
    /* \[SWS_Lin_00021]   The LIN driver shall abort the current frame transmission if a 
    new frame transmission is requested by the LIN interface (see Lin_SendFrame), also 
    if an ongoing transmission may be still in progress or unsuccessfully completed.  */
    /* \[SWS_Lin_00240]   In case of response transmission errors, the LIN 2.1 
    specification describes within the frame processor state machine how to handle such 
    errors. It is stated that a mismatch between sent and readback data shall be detected 
    not later than after the completion of the byte field containing the mismatch. 
    Furthermore, LIN 2.1 specifies that the transmission shall be aborted.  */
    /* Abort data transmission, enter initialization mode to clear the remaining request status */
    RetStatus = Asi_Hal_SoftReset(Lin_BaseAddr[HwUnit], LIN_TIMEOUT_DURATION);
    LIN_EXIT_CRITICAL_SECTION(SendFrame);

    if (E_OK == RetStatus)
    {
        /* \[SWS_Lin_00017]   The LIN driver shall be able to send a LIN header. This is 
        composed of the break field, synch byte field, and protected identifier byte field as 
        detailed in [17] (see Lin_SendFrame).  (SRS_Lin_01578) */
        /* Set the checksum method to register */
        /* #Violation: Lin_c_REF_4 */
        LinFrameControl.checksum = (Asi_Lin_ChecksumType)ChannelStatusPtr->PduBuffer.Cs; 

        /* Set the data length to register */
        LinFrameControl.dataLength = ChannelStatusPtr->PduBuffer.Dl;
        /* Set the data ID, convert the PID to ID */
        /* \[SWS_Lin_00016]   The LIN driver shall interpret the supplied identifier as PID. The 
        identifier is then transmitted as-supplied within the LIN header (see Lin_SendFrame).
          */
        LinFrameControl.frameID = ChannelStatusPtr->PduBuffer.Pid & LIN_PID_MASK_PARITY;
        LIN_ENTER_CRITICAL_SECTION(SendFrame);
        /* Clear DRBNE(Data Reception Buffer Not Empty flag) - write 1 to clear */
        Asi_Lin_Hal_ClearFlagStatus(Lin_BaseAddr[HwUnit], 
                                    ASI_LIN_DATA_RX_BUFFER_NOT_EMPTY_FLAG);
        /* Master response is required */
        /* \[SWS_Lin_00192]   The function Lin_SendFrame shall send the header part (Break 
        Field, Synch Byte Field and PID Field) and, depending on the direction of the frame 
        response, a complete LIN response part of a LIN frame on the addressed LIN 
        channel.  */
        if (LIN_FRAMERESPONSE_TX == ChannelStatusPtr->PduBuffer.Drc)
        {
            /* Set Enable Frame Header Transmission(Master send) */
            LinFrameControl.dir = ASI_LIN_DATADIR_TX;
            /* \[SWS_Lin_00018]   The LIN driver shall be able to send a LIN header and 
            response.  */
            /* Start Lin frame header transmission */
            Asi_Lin_Hal_SendHeader(Lin_BaseAddr[HwUnit], (const Asi_Lin_FrameControl *)&LinFrameControl);
            /* Start Lin data transfer */
            (void)Asi_Lin_Hal_SendData(Lin_BaseAddr[HwUnit], ChannelStatusPtr->PduBuffer.SduPtr, 
                ChannelStatusPtr->PduBuffer.Dl);
        }
        /* Slave response is required */
        else if (LIN_FRAMERESPONSE_RX == ChannelStatusPtr->PduBuffer.Drc)
        {
            /* Set to enable frame header transmission (Master receive) */
            LinFrameControl.dir = ASI_LIN_DATADIR_RX;
            /* Start Lin frame header transmission */
            Asi_Lin_Hal_SendHeader(Lin_BaseAddr[HwUnit], (const Asi_Lin_FrameControl *)&LinFrameControl);
        }
        /* Slave to slave response is required */
        else
        {
            /* Set to enable frame header transmission (Master discards received data) */
            LinFrameControl.dir = ASI_LIN_DATADIR_NODATA;
            /* Start Lin frame header transmission */
            Asi_Lin_Hal_SendHeader(Lin_BaseAddr[HwUnit], (const Asi_Lin_FrameControl *)&LinFrameControl);
        }    
        LIN_EXIT_CRITICAL_SECTION(SendFrame);
    }

    return RetStatus;
}
#endif /* (LIN_MASTER_MODE_USED \== STD_ON) */
#if (LIN_MASTER_MODE_USED == STD_ON)
/****************************************************************************************************
*   Function Name           : Lin_GoToSleepCmd
*
*   Service ID              : None
*
*   Description             : Prepares and send a go-to-sleep-command frame on Channel.
*                               This function stops any ongoing transmission and initiates
*                               the transmission of the sleep command.
*
*   Parameters in           : ChannelStatusPtr: Point to current LIN channel status.
*                             HwUnit: ASI Hardware unit, 0-23.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK: Send succeeded.
*                             E_NOT_OK: In case of a time out situation only.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, LIN_PRIVATE_CODE) Lin_GoToSleepCmd
(
    /* #Violation: Lin_c_REF_2 */
    CONSTP2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr,
    Lin_HWUnitType HwUnit
)
{
    Std_ReturnType      RetStatus;

    /* Update Lin_Channel_Info with Sleep command */
    /* \[SWS_Lin_00089]   The function Lin_GoToSleep shall send a go-to-sleep command 
    on the addressed LIN channel as defined in LIN Specification 2.1.  */
    /* Data length is 8 */
    ChannelStatusPtr->PduBuffer.Dl = 8U;
    /* Both 0x3C and 0x3D are classic checksum */
    ChannelStatusPtr->PduBuffer.Cs = LIN_CLASSIC_CS;
    /* PID is 0x3C */
    ChannelStatusPtr->PduBuffer.Pid = 0x3CU;
    /* Master response */
    ChannelStatusPtr->PduBuffer.Drc = LIN_FRAMERESPONSE_TX;
    /* Load sleep command to data buffer
     * Go to sleep command is 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF*/
    ChannelStatusPtr->PduBuffer.SduPtr[0U] = 0x00U;
    ChannelStatusPtr->PduBuffer.SduPtr[1U] = 0xFFU;
    ChannelStatusPtr->PduBuffer.SduPtr[2U] = 0xFFU;
    ChannelStatusPtr->PduBuffer.SduPtr[3U] = 0xFFU;
    ChannelStatusPtr->PduBuffer.SduPtr[4U] = 0xFFU;
    ChannelStatusPtr->PduBuffer.SduPtr[5U] = 0xFFU;
    ChannelStatusPtr->PduBuffer.SduPtr[6U] = 0xFFU;
    ChannelStatusPtr->PduBuffer.SduPtr[7U] = 0xFFU;
    /* Ready to send go to sleep command */
    /* \[SWS_Lin_00074]   The function Lin_GoToSleep shall terminate ongoing frame 
    transmission of prior transmission requests, even if the transmission is 
    unsuccessfully completed.   */
    RetStatus = Lin_SendFrameData(ChannelStatusPtr, HwUnit);

    return RetStatus;
}
#endif /* (LIN_MASTER_MODE_USED \== STD_ON) */
/****************************************************************************************************
*   Function Name           : Lin_GoToSleepInternalCmd
*
*   Service ID              : None
*
*   Description             : This function stops any ongoing transmission and put the
*                               Channel in sleep mode (then LIN hardware enters a
*                               reduced power operation mode).
*
*   Parameters in           : HwUnit: ASI Hardware unit, 0-23.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK: Target hardware go to sleep successfully.
*                             E_NOT_OK: In case of a time out situation only.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, LIN_PRIVATE_CODE) Lin_GoToSleepInternalCmd
(
    Lin_HWUnitType HwUnit
)
{
    uint32          RegValue;
    Std_ReturnType  RetStatus;

    LIN_ENTER_CRITICAL_SECTION(GoToSleepInternal);
    /* Software reset hardware unit status */
    RetStatus = Asi_Hal_SoftReset(Lin_BaseAddr[HwUnit], LIN_TIMEOUT_DURATION);
    LIN_EXIT_CRITICAL_SECTION(GoToSleepInternal);

    if (E_OK == RetStatus)
    {
        /* \[SWS_Lin_00032]   When the LIN channel enters sleep mode, it shall perform the 
        transition to low-power mode of the LIN hardware unit (if available) (see
        Lin_GoToSleep/Lin_GoToSleepInternal).  */
        /* \[SWS_Lin_00223]   The function Lin_GoToSleepInternal shall optionally set the LIN 
        hardware unit to reduced power operation mode (if supported by HW).  */
        /* Enter low power mode */
        LIN_ENTER_CRITICAL_SECTION(GoToSleepInternal);
        Asi_Hal_EnterSleepMode(Lin_BaseAddr[HwUnit]);
        /* Get Lin status (Lins register bit) */
        RegValue = Asi_Lin_Hal_GetFlagStatus(Lin_BaseAddr[HwUnit], ASI_LIN_STATE_FLAG);
        LIN_EXIT_CRITICAL_SECTION(GoToSleepInternal);
        /* Judge whether enter sleep mode */
        if (ASI_LIN_SLEEP_STATE_FLAG != RegValue)
        {
            RetStatus = E_NOT_OK;
        }
    }

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Lin_WakeupCmd
*
*   Service ID              : None
*
*   Description             : Sends a wake up signal to the LIN bus.
*
*   Parameters in           : ChannelConfigPtr : Channel configuration pointer.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK: Send succeeded.
*                             E_NOT_OK: In case of a time out situation only.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, LIN_PRIVATE_CODE) Lin_WakeupCmd
(
    CONSTP2CONST(Lin_ChannelConfigType, AUTOMATIC, LIN_APPL_CONST) ChannelConfigPtr
)
{
    uint8           WakeUpData;
    uint8           HwUnit;
    uint32          RegValue;
    Std_ReturnType  RetStatus;

    HwUnit = ChannelConfigPtr->HwUnitId;
    /* Set the initial function return status value */
    RetStatus = E_NOT_OK;

    /* Wake-up hardware unit(LIN channel) from low power mode */
    (void)Asi_Hal_ExitSleepMode(Lin_BaseAddr[HwUnit]);
    /* Get Lin status (Lins register bit) */
    RegValue = Asi_Lin_Hal_GetFlagStatus(Lin_BaseAddr[HwUnit], ASI_LIN_STATE_FLAG);

    /* Judge whether enter sleep mode */
    if (ASI_LIN_SLEEP_STATE_FLAG != RegValue)
    {
        LIN_ENTER_CRITICAL_SECTION(WakeUp);
        /* Software reset hardware unit status */
        RetStatus = Asi_Hal_SoftReset(Lin_BaseAddr[HwUnit], LIN_TIMEOUT_DURATION);
        LIN_EXIT_CRITICAL_SECTION(WakeUp);

        if (E_OK == RetStatus)
        {
            /* Set wake up data */
            /* \[SWS_Lin_00043]   Lin_Wakeup: If the LIN driver receives a wake-up request from 
            the LIN interface, the requested channel shall send a wake-up pulse to the LIN bus. */
            /* \[SWS_Lin_00209]   Lin_Wakeup: During the state transition from LIN_CH_SLEEP 
            to LIN_CH_OPERATIONAL the LIN Driver shall ensure that the rest of the cluster is 
            awake. This is achieved by issuing a wake-up request, forcing the bus to the 
            dominant state for 250 us to 5 ms.  */
            WakeUpData = 0x00U;
            /* Start wakeup data transfer */
            (void)Asi_Lin_Hal_SendData(Lin_BaseAddr[HwUnit], &WakeUpData, 1U);
            LIN_ENTER_CRITICAL_SECTION(WakeUp);
            /* Send wake-up signal */
            Asi_Lin_Hal_SendWakeupRequest(Lin_BaseAddr[HwUnit]);
            LIN_EXIT_CRITICAL_SECTION(WakeUp);
            /* Clear error status */
            Asi_Lin_Hal_ClearFlagStatus(Lin_BaseAddr[HwUnit], ASI_LIN_ALL_ERROR_FLAGS);
#if (LIN_CFG_INTERRUPT_ENABLE == STD_ON)
#if (LIN_WAKEUP_SUPPORT == STD_ON)
            LIN_ENTER_CRITICAL_SECTION(WakeUp);
            /* Disable wake-up detection interrupt */
            Lin_WakeupDetect(ChannelConfigPtr, FALSE);
            LIN_EXIT_CRITICAL_SECTION(WakeUp);
#endif /* (LIN_WAKEUP_SUPPORT  \== STD_ON) */
#endif /* (LIN_CFG_INTERRUPT_ENABLE  \== STD_ON) */
        }
    }
    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Lin_WakeupInternalCmd
*
*   Service ID              : None
*
*   Description             : Wake up the LIN channel.
*
*   Parameters in           : HwUnit: ASI Hardware unit, 0-23.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK: Exit sleep mode successfully.
*                             E_NOT_OK: In case of a time out situation only.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, LIN_PRIVATE_CODE) Lin_WakeupInternalCmd
(
    CONSTP2CONST(Lin_ChannelConfigType, AUTOMATIC, LIN_APPL_CONST) ChannelConfigPtr
)
{
    uint8          HwUnit;
    uint32         RegValue;
    Std_ReturnType RetStatus;
    
    HwUnit = ChannelConfigPtr->HwUnitId;
    /* Set the initial function return status value */
    RetStatus = E_NOT_OK;
    /* Wake-up hardware unit(LIN channel) from low power mode */
    /* \[SWS_Lin_00262]   Lin_WakeupInternal: If the LIN driver receives an internal 
    wake-up request from the LIN interface, the requested channel shall send no wake-up pulse to the LIN bus. */
    LIN_ENTER_CRITICAL_SECTION(WakeUpInternal);
    (void)Asi_Hal_ExitSleepMode(Lin_BaseAddr[HwUnit]);
    /* Get Lin status (Lins register bit) */
    RegValue = Asi_Lin_Hal_GetFlagStatus(Lin_BaseAddr[HwUnit], ASI_LIN_STATE_FLAG);
    LIN_EXIT_CRITICAL_SECTION(WakeUpInternal);

    /* Judge whether exit sleep mode */
    if (ASI_LIN_SLEEP_STATE_FLAG != RegValue)
    {
        LIN_ENTER_CRITICAL_SECTION(WakeUpInternal);
        /* Software reset hardware unit status */
        RetStatus = Asi_Hal_SoftReset(Lin_BaseAddr[HwUnit], LIN_TIMEOUT_DURATION);
        LIN_EXIT_CRITICAL_SECTION(WakeUpInternal);

        if (E_OK == RetStatus)
        {
            /* Clear error status */
            Asi_Lin_Hal_ClearFlagStatus(Lin_BaseAddr[HwUnit], ASI_LIN_ALL_ERROR_FLAGS);
#if (LIN_CFG_INTERRUPT_ENABLE == STD_ON)
#if (LIN_WAKEUP_SUPPORT == STD_ON)
            LIN_ENTER_CRITICAL_SECTION(WakeUpInternal);
            /* Disable wake-up detection interrupt */
            Lin_WakeupDetect(ChannelConfigPtr, FALSE);
            LIN_EXIT_CRITICAL_SECTION(WakeUpInternal);
#endif /* (LIN_WAKEUP_SUPPORT  \== STD_ON) */
#endif /* (LIN_CFG_INTERRUPT_ENABLE  \== STD_ON) */
        }
    }
    return RetStatus;
}

#if (LIN_MASTER_MODE_USED == STD_ON)
/****************************************************************************************************
*   Function Name           : Lin_HandleErrorStatus
*
*   Service ID              : None
*
*   Description             : Handles LIN channel error status based on current state and register value.
*                             Sets appropriate error status when unexpected hardware state is detected.
*
*   Parameters in           : ChannelStatusPtr: Point to current LIN channel status.
*                             RegValue: Hardware register status value.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Unexpected hardware state detected.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, LIN_PRIVATE_CODE) Lin_HandleErrorStatus
(
    CONSTP2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr,
    uint32 RegValue
)
{
    if (ASI_LIN_IDLE_STATE_FLAG != RegValue)
    {
        if (LIN_CH_TX_HEADER_BUSY_STATUS == ChannelStatusPtr->ChStatus)
        {
            /* Error occurred when frame header transmitting */
            ChannelStatusPtr->ChStatus = LIN_CH_TX_HEADER_ERROR_STATUS;
        }
        else if (LIN_CH_TX_BUSY_STATUS == ChannelStatusPtr->ChStatus)
        {
            /* Error occurred when frame response transmitting */
            ChannelStatusPtr->ChStatus = LIN_CH_TX_ERROR_STATUS;
        }
        else if (LIN_CH_RX_BUSY_STATUS == ChannelStatusPtr->ChStatus)
        {
            /* Error occurred when frame response receiving */
            ChannelStatusPtr->ChStatus = LIN_CH_RX_ERROR_STATUS;
        }
        else
        {
            /* Other exception error */
            ChannelStatusPtr->ChStatus = LIN_CH_OTHER_ERROR;
        }
    }
}
/****************************************************************************************************
*   Function Name           : Lin_HandleResponseActive
*
*   Service ID              : None
*
*   Description             : Handles the LIN channel status when response is active.
*                             Sets the appropriate TX or RX busy status.
*
*   Parameters in           : ChannelStatusPtr: Point to current LIN channel status.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Response must be active.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, LIN_PRIVATE_CODE) Lin_HandleResponseActive
(
    CONSTP2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr
)
{
    if (LIN_FRAMERESPONSE_TX == ChannelStatusPtr->PduBuffer.Drc)
    {
        /* Response is sending by master, change the LIN channel status to
         * 'LIN_CH_TX_BUSY_STATUS' */
        ChannelStatusPtr->ChStatus = LIN_CH_TX_BUSY_STATUS;
    }
    else
    {
        ChannelStatusPtr->ChStatus = LIN_CH_RX_BUSY_STATUS;
    }
}
/****************************************************************************************************
*   Function Name           : Lin_HandleHeaderComplete
*
*   Service ID              : None
*
*   Description             : Handles the LIN channel status when header transmission is complete.
*                             Sets the appropriate status based on the frame response direction.
*
*   Parameters in           : ChannelStatusPtr: Point to current LIN channel status.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Header transmission must be complete.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, LIN_PRIVATE_CODE) Lin_HandleHeaderComplete
(
    CONSTP2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr
)
{
    if (LIN_FRAMERESPONSE_TX == ChannelStatusPtr->PduBuffer.Drc)
    {
        /* Response is sending by master, change the LIN channel status to
         * 'LIN_CH_TX_BUSY_STATUS' */
        ChannelStatusPtr->ChStatus = LIN_CH_TX_BUSY_STATUS;
    }
    else if(LIN_FRAMERESPONSE_RX == ChannelStatusPtr->PduBuffer.Drc)
    {
        /* Response is receiving from slave, change the LIN channel
         * status to 'LIN_CH_RX_BUSY_STATUS' */
        ChannelStatusPtr->ChStatus = LIN_CH_RX_BUSY_STATUS;
    }
    else
    {
        /* LIN_FRAMERESPONSE_IGNORE == ChannelStatusPtr->PduBuffer.Drc
           transmission is complete */
        ChannelStatusPtr->ChStatus = LIN_CH_TX_OK_STATUS;
    }
}

/****************************************************************************************************
*   Function Name           : Lin_ChStatusFromHwReg
*
*   Service ID              : None
*
*   Description             : Updates the LIN channel status based on the hardware register status.
8                             This function is called by RX ISR for the ASI units
*
*   Parameters in           : ChannelStatusPtr: Point to current LIN channel status.
*                             HwUnit: ASI Hardware unit, 0-23.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, LIN_PRIVATE_CODE) Lin_ChStatusFromHwReg
(
    /* #Violation: Lin_c_REF_2 */
    CONSTP2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr,
    Lin_HWUnitType HwUnit
)
{
    uint32  RegValue;

    /* Get Lin status (Lins register bit) */
    RegValue = Asi_Lin_Hal_GetFlagStatus(Lin_BaseAddr[HwUnit], ASI_LIN_STATE_FLAG);
    /* Header is transmitting */
    /* Sync break field is transmitting */
    if ((ASI_LIN_BREAK_STATE_FLAG == RegValue) ||
        /* Break delimiter is transmitting */
        (ASI_LIN_BREAK_DELIMITER_STATE_FLAG == RegValue) ||
        /* Sync field is transmitting */
        (ASI_LIN_SYNC_FIELD_STATE_FLAG == RegValue) ||
        /* Protected identifier is transmitting */
        (ASI_LIN_ID_FIELD_STATE_FLAG == RegValue))
    {
        /* Header is sending by master, change the LIN channel status to
         * 'LIN_CH_TX_HEADER_BUSY_STATUS' */
        ChannelStatusPtr->ChStatus = LIN_CH_TX_HEADER_BUSY_STATUS;
    }
    /* header transmission is complete */
    else if (ASI_LIN_HEADER_DONE_STATE_FLAG == RegValue)
    {
        Lin_HandleHeaderComplete(ChannelStatusPtr);
    }
    /* Response is receiving/transmitting */
             /* Response is receiving(Slave response) or transmitting(Master response) */
    else if (((ASI_LIN_CHECKSUM_STATE_FLAG) == RegValue) || ((ASI_LIN_DATA_DONE_STATE_FLAG) == RegValue))
    {
        Lin_HandleResponseActive(ChannelStatusPtr);
    }
    else
    {
        /* (LIN_STATUS_REG_SLEEP == RegValue) or
         * (LIN_STATUS_REG_INITIALIZING == RegValue) or
         * (LIN_STTAUS_REG_HEADER_SNED = RegValue) or not 'IDLE' : exception error */
        Lin_HandleErrorStatus(ChannelStatusPtr, RegValue);
    }
}

/****************************************************************************************************
*   Function Name           : Lin_GetChStatus
*
*   Service ID              : None
*
*   Description             : Judge the LIN channel status.
*
*   Parameters in           : ChannelStatusPtr: Point to current LIN channel status.
*                             HwUnit: ASI Hardware unit, 0-23.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK: Send succeeded.
*                             E_NOT_OK: In case of a time out situation only.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Lin_StatusType, LIN_PRIVATE_CODE) Lin_GetChStatus
(
    /* #Violation: Lin_c_REF_2 */
    CONSTP2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr,
    Lin_HWUnitType HwUnit
)
{
    uint32          RegValue;
    Lin_StatusType  LinChStatus;

    /* Not error occurred */
    if ((LIN_CH_TX_HEADER_ERROR_STATUS != ChannelStatusPtr->ChStatus) &&
        (LIN_CH_TX_ERROR_STATUS != ChannelStatusPtr->ChStatus) &&
        (LIN_CH_RX_ERROR_STATUS != ChannelStatusPtr->ChStatus) &&
        (LIN_CH_OTHER_ERROR != ChannelStatusPtr->ChStatus) &&
        (LIN_CH_RX_NO_RESPONSE_STATUS != ChannelStatusPtr->ChStatus))
    {
        /* Judge current status through register 'LINSR' */
        Lin_ChStatusFromHwReg(ChannelStatusPtr, HwUnit);
    }

    /* \[SWS_Lin_00200]   The return states LIN_TX_OK, LIN_TX_BUSY, 
        LIN_TX_HEADER_ERROR, LIN_TX_ERROR, LIN_RX_OK, LIN_RX_BUSY, 
        LIN_RX_ERROR , LIN_RX_NO_RESPONSE and LIN_OPERATIONAL are sub-states 
        of the channel state LIN_CH_OPERATIONAL.  */
    /* Get current LIN channel status */
    switch (ChannelStatusPtr->ChStatus)
    {
        case LIN_CH_TX_HEADER_BUSY_STATUS:
        {
            /* \[SWS_Lin_00238]   The function Lin_GetStatus shall return LIN_TX_OK, when
            - A Master Response Type frame is send and LIN header as well as LIN 
            response of the frame are transmitted successfully or
            - A Slave to Slave Response Type frame is send and the LIN header of the frame 
            is transmitted successfully.  */
            if (LIN_FRAMERESPONSE_TX == ChannelStatusPtr->PduBuffer.Drc)
            {
                /* Get Lin status (LINSR register bit) */
                RegValue = Asi_Lin_Hal_GetFlagStatus(Lin_BaseAddr[HwUnit],
                    ASI_LIN_DATA_TX_COMPLETED_FLAG);
                /* Data transmission successfully */
                if (0U != (RegValue & ASI_LIN_DATA_TX_COMPLETED_FLAG))
                {
                    /* Data transmission finished */
                    ChannelStatusPtr->ChStatus = LIN_CH_TX_OK_STATUS;
                    LinChStatus = LIN_TX_OK;
                    /* Clear register status of 'DTF' */
                    Asi_Lin_Hal_ClearFlagStatus(Lin_BaseAddr[HwUnit],ASI_LIN_DATA_TX_COMPLETED_FLAG);
                }
                else
                {
                    LinChStatus = LIN_TX_BUSY;
                }
            }
            else if (LIN_FRAMERESPONSE_IGNORE == ChannelStatusPtr->PduBuffer.Drc)
            {
                /* Header frame send successfully */
                /* Get Lin status (Lins register bit) */
                RegValue = Asi_Lin_Hal_GetFlagStatus(Lin_BaseAddr[HwUnit],
                    ASI_LIN_STATE_FLAG);
                    /* Current LINS is 'IDLE' */
                if (ASI_LIN_IDLE_STATE_FLAG == RegValue)
                {
                    /* Check if error is occured */
                    RegValue = Asi_Lin_Hal_GetFlagStatus(Lin_BaseAddr[HwUnit], ASI_LIN_ALL_ERROR_FLAGS);
                    if (0U == (RegValue & LIN_ERROR_STATUS_VALUE_MASK))
                    {
                        ChannelStatusPtr->ChStatus = LIN_CH_TX_OK_STATUS;
                        LinChStatus = LIN_TX_OK;
                    }
                    else
                    {
                        /* In interrupt mode, error interrupt is triggered, 
                        state machine will be handle in interrupt handler. 
                        In polling mode, the next poll will change the state and clear the error flag*/
                        LinChStatus = LIN_TX_BUSY;
                    }
                }
                else
                {
                    LinChStatus = LIN_TX_BUSY;
                }
            }
            else
            {
                LinChStatus = LIN_TX_BUSY;
            }
            break;
        }
        case LIN_CH_TX_BUSY_STATUS:
        {
            /* Get Lin status (LINSR register bit) */
            RegValue = Asi_Lin_Hal_GetFlagStatus(Lin_BaseAddr[HwUnit],
                    ASI_LIN_DATA_TX_COMPLETED_FLAG);
            /* Data transmission successfully */
            if (0U != (RegValue & ASI_LIN_DATA_TX_COMPLETED_FLAG))
            {
                /* Data transmission finished */
                ChannelStatusPtr->ChStatus = LIN_CH_TX_OK_STATUS;
                LinChStatus = LIN_TX_OK;
                /* Clear register status of 'DTF' */
                Asi_Lin_Hal_ClearFlagStatus(Lin_BaseAddr[HwUnit],ASI_LIN_DATA_TX_COMPLETED_FLAG);
            }
            else
            {
                LinChStatus = LIN_TX_BUSY;
            }
            break;
        }
        default:
        {
            /* Internal state machine switch to standard state machine */
            LinChStatus = Lin_ChannelStateTransition(ChannelStatusPtr->ChStatus);
            break;
        }
    }
    return LinChStatus;
}
#endif /*(LIN_MASTER_MODE_USED \== STD_ON)*/
/****************************************************************************************************
*   Function Name           : Lin_IsrRecvDataHandler
*
*   Service ID              : None
*
*   Description             : Handler received data by Rx interrupt, Copy the data to internal
*                               buffer.
*
*   Parameters in           : ChannelStatusPtr: Point to current LIN channel status.
*                             HwUnit: ASI Hardware unit, 0-23
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, LIN_PRIVATE_CODE) Lin_IsrRecvDataHandler
(
    /* #Violation: Lin_c_REF_2 */
    CONSTP2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr,
    CONSTP2CONST(Lin_ChannelConfigType, AUTOMATIC, LIN_APPL_CONST) ChannelConfigPtr
)
{
    uint32          LoopCount;
    uint32          RegValue;

    /* Get the data receiving completion flag */
    RegValue = Asi_Lin_Hal_GetFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], 
                                        ASI_LIN_DATA_RX_COMPLETED_FLAG);
    /* Data receiving completed */
    if (ASI_LIN_DATA_RX_COMPLETED_FLAG == RegValue)
    {
        /* Set the Loop initial value */
        LoopCount = LIN_TIMEOUT_DURATION;
        /* Waiting data is ready to be read */
        do
        {
            /* 'LoopCount' reduce for avoid dead loop here */
            LoopCount--;
            /* Get free message buffer flag */
            RegValue = 
                Asi_Lin_Hal_GetFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], 
                                          ASI_LIN_MESSAGE_BUFFER_READY_FLAG);
        }while ((LoopCount > 0U ) && (ASI_LIN_MESSAGE_BUFFER_READY_FLAG != RegValue));

        /* Data is ready to be read by software */
        if (ASI_LIN_MESSAGE_BUFFER_READY_FLAG == RegValue)
        {
            /* Change LIN channel status to 'LIN_CH_RX_OK_STATUS' */
            ChannelStatusPtr->ChStatus = LIN_CH_RX_OK_STATUS;
            /* Copy data from 'BDRL' and 'BDRM' to internal buffer */
            (void)Asi_Lin_Hal_ReceiveData(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], 
                                          ChannelStatusPtr->PduBuffer.SduPtr, 
                                          ChannelStatusPtr->PduBuffer.Dl);
#if (LIN_SLAVE_MODE_USED == STD_ON)
            /* Determine whether the controller is in slave mode */
            if (ASI_LIN_MODE_SLAVE == ChannelConfigPtr->RegisterConfigPtr->mode)
            {
                /* \[SWS_Lin_00274] After successful reception of a LIN response, the LIN driver 
                shall directly make the received data available to the LIN interface module by calling 
                the Rx indication callback function LinIf_RxIndication with the Lin_SduPtr parameter 
                set to the reception data.  */
                LinIf_RxIndication((NetworkHandleType)ChannelConfigPtr->ChannelId, 
                                   ChannelStatusPtr->PduBuffer.SduPtr);
                /* Clear LIN channel buffer */
                Lin_ClearLinChBuffer(ChannelStatusPtr);
                /* Reset header received status */
                ChannelStatusPtr->IsHeaderRecv = FALSE;
            }
#endif /* (LIN_SLAVE_MODE_USED  \== STD_ON) */
            /* Noise Error has occurred ? */
            RegValue = Asi_Lin_Hal_GetFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], ASI_LIN_NOISE_FLAG);
            if (ASI_LIN_NOISE_FLAG == RegValue)
            {
                ChannelStatusPtr->ChStatus = LIN_CH_OTHER_ERROR;
                /* Clear error flag */
                Asi_Lin_Hal_ClearFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], ASI_LIN_NOISE_FLAG);
            }
            /* \[SWS_Lin_00157]   The Lin module shall reset the interrupt flag at the end of the 
            ISR (if not done automatically by hardware).   */
            /* Clear DRF(data receiving completed flag) and RMB(data ready flag) and 
            DRBNE(Data Reception Buffer Not Empty flag) - write 1 to clear */
            Asi_Lin_Hal_ClearFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], 
                                        ASI_LIN_DATA_RX_COMPLETED_FLAG | ASI_LIN_MESSAGE_BUFFER_READY_FLAG |
                                        ASI_LIN_DATA_RX_BUFFER_NOT_EMPTY_FLAG);

#if (LIN_DEM_ERROR_REPORT_STATUS == STD_ON)
            /* \[SWS_Lin_00218]   The LIN Driver module shall report the production or default
            error "LIN_E_TIMEOUT (value assigned by DEM)", when Timeout caused by
            hardware error.  */

            Dem_SetEventStatus(LIN_E_TIMEOUT, DEM_EVENT_STATUS_PASSED);
#endif  /* (LIN_DEM_ERROR_REPORT_STATUS  \== STD_ON) */
        }
        else
        {
            /* Buffer is not ready to be read */
            ChannelStatusPtr->ChStatus = LIN_CH_RX_ERROR_STATUS;
#if (LIN_DEM_ERROR_REPORT_STATUS == STD_ON)
            /* \[SWS_Lin_00218]   The LIN Driver module shall report the production or default
            error "LIN_E_TIMEOUT (value assigned by DEM)", when Timeout caused by
            hardware error.  */
            /* \[SWS_Lin_00097]   If a change to the LIN hardware control registers results in the 
            need to wait for a status change, this shall be protected by a configurable time out 
            mechanism (LinTimeoutDuration). If such a time out is detected the 
            LIN_E_TIMEOUT error shall be raised to the DET or DEM. This situation should only 
            arise in the event of a LIN hardware unit fault, and should be communicated to the 
            rest of the system.  */
            Dem_SetEventStatus(LIN_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
#endif  /* (LIN_DEM_ERROR_REPORT_STATUS  \== STD_ON) */
        }
    }
}

#if (LIN_CFG_INTERRUPT_ENABLE == STD_ON)
/****************************************************************************************************
*   Function Name           : Lin_HandleMasterOtherErrors
*
*   Service ID              : None
*
*   Description             : Handles other LIN master errors including SZF and exception errors.
*
*   Parameters in           : ChannelStatusPtr: Point to current LIN channel status.
*                             ChannelConfigPtr: LIN channel configuration.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Other errors detected.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, LIN_PRIVATE_CODE) Lin_HandleMasterOtherErrors
(
    CONSTP2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr,
    CONSTP2CONST(Lin_ChannelConfigType, AUTOMATIC, LIN_APPL_CONST) ChannelConfigPtr
)
{
    uint32 RegValue;
    
    /* Determines whether the frame header has been received */
    RegValue = Asi_Lin_Hal_GetFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], 
                                        ASI_LIN_DATA_RX_BUFFER_NOT_EMPTY_FLAG);
    if (ASI_LIN_DATA_RX_BUFFER_NOT_EMPTY_FLAG != RegValue)
    {
        ChannelStatusPtr->ChStatus = LIN_CH_TX_HEADER_ERROR_STATUS;
    }
    else if (LIN_FRAMERESPONSE_TX == ChannelStatusPtr->PduBuffer.Drc)
    {
        ChannelStatusPtr->ChStatus = LIN_CH_TX_ERROR_STATUS;
    }
    else if (LIN_FRAMERESPONSE_RX == ChannelStatusPtr->PduBuffer.Drc)
    {
        ChannelStatusPtr->ChStatus = LIN_CH_RX_ERROR_STATUS;
    }
    else
    {
        /* Physical bus error or hardware error */
        ChannelStatusPtr->ChStatus = LIN_CH_OTHER_ERROR;
    }
}
#endif /* \(LIN_CFG_INTERRUPT_ENABLE \== STD_ON) */
/****************************************************************************************************
*   Function Name           : Lin_IsrMasterErrorHandler
*
*   Service ID              : None
*
*   Description             : This function is called by Error ISR for the ASI units
*
*   Parameters in           : HWUnit : Hardware unit used.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, LIN_PRIVATE_CODE) Lin_IsrMasterErrorHandler
(
    /* #Violation: Lin_c_REF_2 */
    CONSTP2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr,
    CONSTP2CONST(Lin_ChannelConfigType, AUTOMATIC, LIN_APPL_CONST) ChannelConfigPtr
)
{
    Std_ReturnType      RetStatus;
    uint32              RegValue;

#if (LIN_CFG_INTERRUPT_ENABLE == STD_OFF)
    /* Set the initial function return status value */
    RetStatus = E_NOT_OK;
#endif /* (LIN_CFG_INTERRUPT_ENABLE  \== STD_OFF) */

    /**************************************************************
     * Read Error RetStatus
     *************************************************************/
    /* Get error status register(LINESR) value */
    RegValue = Asi_Lin_Hal_GetFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], ASI_LIN_ALL_ERROR_FLAGS);
    /* Get LINESR Error status register value */
    RegValue = RegValue & LIN_ERROR_STATUS_VALUE_MASK;
    /* If mutil-error occurred at same time then only record a error status to ChErrStatus */
    /* Timeout error */
    if (0U != (RegValue & ASI_LIN_OUTPUT_COMPARE_FLAG))
    {
        /* Detect whether response data is stored in the BDRL */
        RegValue = Asi_Lin_Hal_GetFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], 
                                             ASI_LIN_DATA_RX_BUFFER_NOT_EMPTY_FLAG);
        if (ASI_LIN_DATA_RX_BUFFER_NOT_EMPTY_FLAG == RegValue)
        {
            /* Set master state to LIN_CH_RX_ERROR_STATUS */
            ChannelStatusPtr->ChStatus = LIN_CH_RX_ERROR_STATUS;
        }
        else
        {
            /* Set master state to LIN_CH_RX_NO_RESPONSE_STATUS */
            ChannelStatusPtr->ChStatus = LIN_CH_RX_NO_RESPONSE_STATUS;
        }
        Asi_Lin_Hal_ClearFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], 
                                    ASI_LIN_DATA_RX_BUFFER_NOT_EMPTY_FLAG);
    }
    /* Bit error */
    else if (0U != (RegValue & ASI_LIN_BITERROR_FLAG))
    {
        /* Set master state */
        /* LIN channel frame header is sending */
        if (LIN_CH_TX_HEADER_BUSY_STATUS == ChannelStatusPtr->ChStatus)
        {
            ChannelStatusPtr->ChStatus = LIN_CH_TX_HEADER_ERROR_STATUS;
        }
        /* LIN channel frame response is sending */
        else if (LIN_CH_TX_BUSY_STATUS == ChannelStatusPtr->ChStatus)
        {
            ChannelStatusPtr->ChStatus = LIN_CH_TX_ERROR_STATUS;
        }
        else
        {
            ChannelStatusPtr->ChStatus = LIN_CH_OTHER_ERROR;
        }
    }
    /* Checksum error */
    else if (0U != (RegValue & ASI_LIN_CHECKSUM_ERROR_FLAG))
    {
        /* Set master state */
        ChannelStatusPtr->ChStatus = LIN_CH_RX_ERROR_STATUS;
    }
    /* Frame(Invalid stop bit) error */
    else if (0U != (RegValue & ASI_LIN_FRAMING_ERROR_FLAG))
    {
        /* Set master state */
        ChannelStatusPtr->ChStatus = LIN_CH_RX_ERROR_STATUS;
        /* Discard data reception */
        Asi_Lin_Hal_DataDiscardRequest(Lin_BaseAddr[ChannelConfigPtr->HwUnitId]);
        /* Clear Data Reception Buffer Not Empty flag */
        Asi_Lin_Hal_ClearFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], ASI_LIN_DATA_RX_BUFFER_NOT_EMPTY_FLAG);
    }
    /* Buffer overflow error */
    else if (0U != (RegValue & ASI_LIN_BUFFER_OVERRUN_FLAG))
    {
        /* Set master state */
        ChannelStatusPtr->ChStatus = LIN_CH_RX_ERROR_STATUS;
        /* Discard data reception */
        Asi_Lin_Hal_DataDiscardRequest(Lin_BaseAddr[ChannelConfigPtr->HwUnitId]);
        /* Clear Data Reception Buffer Not Empty flag */
        Asi_Lin_Hal_ClearFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], ASI_LIN_DATA_RX_BUFFER_NOT_EMPTY_FLAG);
    }
    else
    {
#if (LIN_CFG_INTERRUPT_ENABLE == STD_ON)
        /* Stack zero error
         * 1. SZF error;
         * 2. exception error */
        /* hardware error */
        /* Set master state */
        /* Determines whether the frame header has been received */
        Lin_HandleMasterOtherErrors(ChannelStatusPtr, ChannelConfigPtr);
#else  /* (LIN_CFG_INTERRUPT_ENABLE  \== STD_ON) */
        RetStatus = E_OK;
#endif /* (LIN_CFG_INTERRUPT_ENABLE  \== STD_ON) */
    }

#if (LIN_CFG_INTERRUPT_ENABLE == STD_OFF)
    if (E_NOT_OK == RetStatus)
#endif /* (LIN_CFG_INTERRUPT_ENABLE  \== STD_OFF) */
    {
        /* Clear error status */
        /* \[SWS_Lin_00157]   The Lin module shall reset the interrupt flag at the end of the 
        ISR (if not done automatically by hardware).   */
        Asi_Lin_Hal_ClearFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], ASI_LIN_ALL_ERROR_FLAGS);

        LIN_ENTER_CRITICAL_SECTION(ErrorHandle);
        /* SWS_Lin_00239, SWS_Lin_00240 */
        /* Abort data transmission */
        RetStatus = Asi_Hal_SoftReset(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], LIN_TIMEOUT_DURATION);
        LIN_EXIT_CRITICAL_SECTION(ErrorHandle);

        if (E_NOT_OK == RetStatus)
        {
            /* Hardware error */
            ChannelStatusPtr->ChStatus = LIN_CH_OTHER_ERROR;
        }
#if (LIN_DEM_ERROR_REPORT_STATUS == STD_ON)
        if (LIN_CH_OTHER_ERROR == ChannelStatusPtr->ChStatus)
        {
            /* \[SWS_Lin_00218]   The LIN Driver module shall report the production or default
            error "LIN_E_TIMEOUT (value assigned by DEM)", when Timeout caused by
            hardware error.  */
            Dem_SetEventStatus(LIN_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
        }
        else
        {
            /* \[SWS_Lin_00218]   The LIN Driver module shall report the production or default
            error "LIN_E_TIMEOUT (value assigned by DEM)", when Timeout caused by
            hardware error.  */
            Dem_SetEventStatus(LIN_E_TIMEOUT, DEM_EVENT_STATUS_PASSED);
        }
#endif /* (LIN_DEM_ERROR_REPORT_STATUS  \== STD_ON) */
    }
}

#if (LIN_SLAVE_MODE_USED == STD_ON)
/****************************************************************************************************
*   Function Name           : Lin_IsrTxHandler
*
*   Service ID              : None
*
*   Description             : Transmit data successfully by Tx interrupt.
*
*   Parameters in           : ChannelStatusPtr: Point to current LIN channel status.
*                             HwUnit: ASI Hardware unit, 0-23
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, LIN_PRIVATE_CODE) Lin_IsrTxHandler
(
    /* #Violation: Lin_c_REF_2 */
    CONSTP2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr,
    CONSTP2CONST(Lin_ChannelConfigType, AUTOMATIC, LIN_APPL_CONST) ChannelConfigPtr
)
{
    uint32          RegValue;

    /* Get the data sending completion flag */
    RegValue = Asi_Lin_Hal_GetFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], 
                                         ASI_LIN_DATA_TX_COMPLETED_FLAG);
    /* Data sending completed */
    if (ASI_LIN_DATA_TX_COMPLETED_FLAG == RegValue)
    {
        /* \[SWS_Lin_00275] After successful transmission of a LIN response, the 
        transmission shall be directly confirmed to the LIN Interface module by calling the Tx 
        confirmation callback function LinIf_TxConfirmation. */
        LinIf_TxConfirmation((NetworkHandleType)ChannelConfigPtr->ChannelId);
        /* \[SWS_Lin_00157]   The Lin module shall reset the interrupt flag at the end of the 
        ISR (if not done automatically by hardware).   */
        /* Clear DTF(data transmission completed flag) - write 1 to clear */
        Asi_Lin_Hal_ClearFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], 
                                        ASI_LIN_DATA_TX_COMPLETED_FLAG);
        /* Reset header received status */
        ChannelStatusPtr->IsHeaderRecv = FALSE;
#if (LIN_DEM_ERROR_REPORT_STATUS == STD_ON)
        /* \[SWS_Lin_00218]   The LIN Driver module shall report the production or default
        error "LIN_E_TIMEOUT (value assigned by DEM)", when Timeout caused by
        hardware error.  */
        Dem_SetEventStatus(LIN_E_TIMEOUT, DEM_EVENT_STATUS_PASSED);
    }
    else
    {
        /* \[SWS_Lin_00218]   The LIN Driver module shall report the production or default
        error "LIN_E_TIMEOUT (value assigned by DEM)", when Timeout caused by
        hardware error.  */
        /* \[SWS_Lin_00097]   If a change to the LIN hardware control registers results in the 
        need to wait for a status change, this shall be protected by a configurable time out 
        mechanism (LinTimeoutDuration). If such a time out is detected the 
        LIN_E_TIMEOUT error shall be raised to the DET or DEM. This situation should only 
        arise in the event of a LIN hardware unit fault, and should be communicated to the 
        rest of the system.  */
        Dem_SetEventStatus(LIN_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
#endif /* (LIN_DEM_ERROR_REPORT_STATUS  \== STD_ON) */
    }
}

/****************************************************************************************************
*   Function Name           : Lin_IsrRecvHeaderHandler
*
*   Service ID              : None
*
*   Description             : Handler received data by Rx interrupt, Copy the data to internal
*                               buffer.
*
*   Parameters in           : ChannelStatusPtr: Point to current LIN channel status.
*                             HwUnit: ASI Hardware unit, 0-23
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, LIN_PRIVATE_CODE) Lin_IsrRecvHeaderHandler
(
    /* #Violation: Lin_c_REF_2 */
    P2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr,
    CONSTP2CONST(Lin_ChannelConfigType, AUTOMATIC, LIN_APPL_CONST) ChannelConfigPtr
)
{
    Std_ReturnType          ResultVal;
    uint32                  RegValue;
    uint8                   LinFrameId;
    Lin_FrameControlType    LinFrameControl;


    /* Get the data receiving completion flag */
    RegValue = Asi_Lin_Hal_GetFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], ASI_LIN_HEADER_RX_FLAG);
    if (ASI_LIN_HEADER_RX_FLAG == RegValue)
    {
        ChannelStatusPtr->IsHeaderRecv = TRUE;
        /* Get PID */
        /* \[SWS_Lin_00271]   If the LIN hardware unit cannot detect invalid PIDs, the LIN
        driver shall not evaluate the PID value (i.e. it shall not verify parity bits in software). 
        The LIN driver shall provide the PID as-received to the LIN interface module. */
        Asi_Lin_Hal_ReceiveHeader(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], &LinFrameId);
        /* \[SWS_Lin_00280]   On LIN header reception, the LIN driver shall call the header
        indication callback function LinIf_HeaderIndication with PduPtr->Pid set to the 
        received PID value and PduPtr->SduPtr set to the (hardware or shadow) buffer of the 
        LIN driver, to which the slave response shall be written by the upper layer. */
        /* Calcilate PID */
        ChannelStatusPtr->PduBuffer.Pid = Lin_CalculatePid(LinFrameId);
        /* \[SWS_Lin_00280] */
        /* \[SWS_Lin_00284]   If the LIN response is going to be received
        (LIN_FRAMERESPONSE_RX), the LIN driver shall evaluate the Cs and Dl members 
        in parameter PduPtr (after the call of LinIf_HeaderIndication with return value E_OK) 
        to configure the LIN response reception. */
        /* \[SWS_Lin_00283] If the LIN response is going to be transmitted
        (LIN_FRAMERESPONSE_TX), the LIN driver shall evaluate the Cs, Dl and SduPtr 
        members in parameter PduPtr (after the call of LinIf_HeaderIndication with return 
        value E_OK) to setup and transmit the LIN response. */
        ResultVal = LinIf_HeaderIndication((NetworkHandleType)ChannelConfigPtr->ChannelId, 
                                           &(ChannelStatusPtr->PduBuffer));
        if (E_OK == ResultVal)
        {
            /* \[SWS_Lin_00282] After the call of LinIf_HeaderIndication when the return value is 
            E_OK, the LIN driver shall evaluate the PduPtr->Drc to determine the type of LIN 
            response. */
            if (LIN_FRAMERESPONSE_TX == ChannelStatusPtr->PduBuffer.Drc)
            {
                /* #Violation: Lin_c_REF_4 */
                LinFrameControl.checksum = (Asi_Lin_ChecksumType)ChannelStatusPtr->PduBuffer.Cs; 
                LinFrameControl.dataLength = ChannelStatusPtr->PduBuffer.Dl;
                LinFrameControl.dir = ASI_LIN_DATADIR_TX;
                LinFrameControl.frameID = LinFrameId;
                Asi_Lin_Hal_SetBufferIdentifier(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], 
                       (const Asi_Lin_FrameControl *)&LinFrameControl);
                (void)Asi_Lin_Hal_SendData(Lin_BaseAddr[ChannelConfigPtr->HwUnitId],
                                                 ChannelStatusPtr->PduBuffer.SduPtr, 
                                                 ChannelStatusPtr->PduBuffer.Dl);
            }
            else if (LIN_FRAMERESPONSE_RX == ChannelStatusPtr->PduBuffer.Drc)
            {
                /* #Violation: Lin_c_REF_4 */
                LinFrameControl.checksum = (Asi_Lin_ChecksumType)ChannelStatusPtr->PduBuffer.Cs; 
                LinFrameControl.dataLength = ChannelStatusPtr->PduBuffer.Dl;
                LinFrameControl.dir = ASI_LIN_DATADIR_RX;
                LinFrameControl.frameID = LinFrameId;
                Asi_Lin_Hal_SetBufferIdentifier(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], 
                       (const Asi_Lin_FrameControl *)&LinFrameControl);
            }
            else
            {
                /* SWS_Lin_00276 : The LIN driver shall not report any events to the LIN interface 
                module if the LIN response is ignored until the reception of a new LIN header.   */
                Asi_Lin_Hal_DataDiscardRequest(Lin_BaseAddr[ChannelConfigPtr->HwUnitId]);
                /* Clear Data Reception Buffer Not Empty flag */
                Asi_Lin_Hal_ClearFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], ASI_LIN_DATA_RX_BUFFER_NOT_EMPTY_FLAG);
                ChannelStatusPtr->IsHeaderRecv = FALSE;
            }
        }
        else
        {
            /* \[SWS_Lin_00286] If the return value of LinIf_HeaderIndication is E_NOT_OK or 
            the returned PduPtr->Drc is LIN_FRAMERESPONSE_IGNORE, the LIN driver shall 
            ignore the response.  */
            Asi_Lin_Hal_DataDiscardRequest(Lin_BaseAddr[ChannelConfigPtr->HwUnitId]);
            /* Clear Data Reception Buffer Not Empty flag */
            Asi_Lin_Hal_ClearFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], ASI_LIN_DATA_RX_BUFFER_NOT_EMPTY_FLAG);
        }
        /* Clear HRF(header receiving completed flag) - write 1 to clear */
        Asi_Lin_Hal_ClearFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], ASI_LIN_HEADER_RX_FLAG);
    }
}

/****************************************************************************************************
*   Function Name           : Lin_HandleOtherErrors
*
*   Service ID              : None
*
*   Description             : Handles other LIN errors including SZF and exception errors.
*
*   Parameters in           : ChannelStatusPtr: Point to current LIN channel status.
*                             ChannelConfigPtr: LIN channel configuration.
*                             HwUnit: Hardware unit ID.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Other errors detected.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, LIN_PRIVATE_CODE) Lin_HandleOtherErrors
(
    CONSTP2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr,
    CONSTP2CONST(Lin_ChannelConfigType, AUTOMATIC, LIN_APPL_CONST) ChannelConfigPtr,
    Lin_HWUnitType HwUnit
)
{
    uint32 RegValue;
    
    /* Determines whether the frame header has been received */
    RegValue = Asi_Lin_Hal_GetFlagStatus(Lin_BaseAddr[HwUnit], ASI_LIN_DATA_RX_BUFFER_NOT_EMPTY_FLAG);
    if (ASI_LIN_DATA_RX_BUFFER_NOT_EMPTY_FLAG != RegValue)
    {
        /* Report LIN_ERR_HEADER */
        LinIf_LinErrorIndication(ChannelConfigPtr->ChannelId, LIN_ERR_HEADER);
    }
    else if (LIN_FRAMERESPONSE_TX == ChannelStatusPtr->PduBuffer.Drc)
    {
        LinIf_LinErrorIndication(ChannelConfigPtr->ChannelId, LIN_ERR_RESP_DATABIT);
    }
    else if (LIN_FRAMERESPONSE_RX == ChannelStatusPtr->PduBuffer.Drc)
    {
        LinIf_LinErrorIndication(ChannelConfigPtr->ChannelId, LIN_ERR_RESP_CHKSUM);
    }
    else
    {
        /* Ignore frame */
        LinIf_LinErrorIndication(ChannelConfigPtr->ChannelId, LIN_ERR_HEADER);
    }
}
/****************************************************************************************************
*   Function Name           : Lin_IsrSlaveErrorHandler
*
*   Service ID              : None
*
*   Description             : This function is called by Error ISR for the ASI units
*
*   Parameters in           : ChannelStatusPtr: Point to current LIN channel status.
*                             ChannelConfigPtr: LIN channel configuration.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, LIN_PRIVATE_CODE) Lin_IsrSlaveErrorHandler
(
    /* #Violation: Lin_c_REF_2 */
    CONSTP2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr,
    CONSTP2CONST(Lin_ChannelConfigType, AUTOMATIC, LIN_APPL_CONST) ChannelConfigPtr
)
{
#if (LIN_DEM_ERROR_REPORT_STATUS == STD_ON)
    Std_ReturnType      RetStatus;
#endif /* (LIN_DEM_ERROR_REPORT_STATUS  \== STD_ON) */
    uint32              RegValue;

    /**************************************************************
     * Read Error RetStatus
     *************************************************************/
    /* Get error status register(LINESR) value */
    RegValue = Asi_Lin_Hal_GetFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], ASI_LIN_ALL_ERROR_FLAGS);
    /* Get LINESR Error status register value */
    RegValue = RegValue & LIN_ERROR_STATUS_VALUE_MASK;
    /* If mutil-error occurred at same time then only record a error status to ChErrStatus */
    /* Timeout error */
    if (0U != (RegValue & ASI_LIN_OUTPUT_COMPARE_FLAG))
    {
        /* Detect header is received or not */
        if (FALSE == ChannelStatusPtr->IsHeaderRecv)
        {
            /* Header is not received */
            LinIf_LinErrorIndication(ChannelConfigPtr->ChannelId, LIN_ERR_HEADER);
        }
        else
        {
            /* Detect whether response data is stored in the BDRL */
            RegValue = Asi_Lin_Hal_GetFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], ASI_LIN_DATA_RX_BUFFER_NOT_EMPTY_FLAG);
            if (ASI_LIN_DATA_RX_BUFFER_NOT_EMPTY_FLAG == RegValue)
            {
                LinIf_LinErrorIndication(ChannelConfigPtr->ChannelId, LIN_ERR_INC_RESP);
            }
            else
            {
                LinIf_LinErrorIndication(ChannelConfigPtr->ChannelId, LIN_ERR_NO_RESP);
            }
        }
        /* Clear Data Reception Buffer Not Empty flag */
        Asi_Lin_Hal_ClearFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], ASI_LIN_DATA_RX_BUFFER_NOT_EMPTY_FLAG);
    }
    /* Bit error */
    else if (0U != (RegValue & ASI_LIN_BITERROR_FLAG))
    {
        /* Report LIN_ERR_RESP_DATABIT */
        LinIf_LinErrorIndication(ChannelConfigPtr->ChannelId, LIN_ERR_RESP_DATABIT);
    }
    /* Checksum error */
    else if (0U != (RegValue & ASI_LIN_CHECKSUM_ERROR_FLAG))
    {
        /* Report LIN_ERR_RESP_CHKSUM */
        LinIf_LinErrorIndication(ChannelConfigPtr->ChannelId, LIN_ERR_RESP_CHKSUM);
    }
    /* Synchronous field, Break delimiter, ID parity check error */
    else if (0U != (RegValue & (ASI_LIN_SYNC_FIELD_ERROR_FLAG | 
             ASI_LIN_BREAK_DELIMITER_ERROR_FLAG | ASI_LIN_ID_PARITY_ERROR_FLAG)))
    {
        /* Report LIN_ERR_HEADER */
        LinIf_LinErrorIndication(ChannelConfigPtr->ChannelId, LIN_ERR_HEADER);
    }
    /* Frame(Invalid stop bit) error */
    else if (0U != (RegValue & ASI_LIN_FRAMING_ERROR_FLAG))
    {
        /* Discard data reception */
        Asi_Lin_Hal_DataDiscardRequest(Lin_BaseAddr[ChannelConfigPtr->HwUnitId]);
        /* Detect whether response data is stored in the BDRL */
        RegValue = Asi_Lin_Hal_GetFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], ASI_LIN_DATA_RX_BUFFER_NOT_EMPTY_FLAG);
        if (ASI_LIN_DATA_RX_BUFFER_NOT_EMPTY_FLAG == RegValue)
        {
            /* \[SWS_LinIf_00870] The LIN Interface shall translate the error code reported by 
            LinIf_LinErrorIndication to an error code of Lin_StatusType before calling 
            Mirror_ReportLinFrame(). The error code LIN_ERR_RESP_STOPBIT shall be 
            mapped LIN_TX_ERROR or LIN_RX_ERROR, depending on the direction of the 
            current frame. The error codes LIN_ERR_RESP_CHKSUM and 
            LIN_ERR_INCOMP_RESP shall be mapped to LIN_RX_ERROR. The error code 
            LIN_ERR_NO_RESP shall be mapped to LIN_RX_NO_RESPONSE. The error code 
            LIN_ERR_RESP_DATABIT shall be mapped to LIN_TX_ERROR. */
            /* Report LIN_ERR_RESP_STOPBIT */
            LinIf_LinErrorIndication(ChannelConfigPtr->ChannelId, LIN_ERR_RESP_STOPBIT);
        }
        else
        {
            /* Report LIN_ERR_HEADER */
            LinIf_LinErrorIndication(ChannelConfigPtr->ChannelId, LIN_ERR_HEADER);
        }
        /* Clear Data Reception Buffer Not Empty flag */
        Asi_Lin_Hal_ClearFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], ASI_LIN_DATA_RX_BUFFER_NOT_EMPTY_FLAG);
    }
    /* Buffer overflow error */
    else if (0U != (RegValue & ASI_LIN_BUFFER_OVERRUN_FLAG))
    {
        /* Report LIN_ERR_INC_RESP */
        /* The latest data overwrites the current received data, so the reception is incomplete */
        LinIf_LinErrorIndication(ChannelConfigPtr->ChannelId, LIN_ERR_INC_RESP);
        /* Discard data reception */
        Asi_Lin_Hal_DataDiscardRequest(Lin_BaseAddr[ChannelConfigPtr->HwUnitId]);
        /* Clear Data Reception Buffer Not Empty flag */
        Asi_Lin_Hal_ClearFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], ASI_LIN_DATA_RX_BUFFER_NOT_EMPTY_FLAG);
    }
    else
    {
        /* Stack zero error
         * 1. SZF error;
         * 2. exception error*/
        /* hardware error */
        /* Set master state */
        /* Determines whether the frame header has been received */
        Lin_HandleOtherErrors(ChannelStatusPtr, ChannelConfigPtr, ChannelConfigPtr->HwUnitId);
    }
    /* Clear error status */
    Asi_Lin_Hal_ClearFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], ASI_LIN_ALL_ERROR_FLAGS);
    LIN_ENTER_CRITICAL_SECTION(ErrorHandle);
    /* SWS_Lin_00277 The LIN driver shall detect communication errors during 
    response transmission and response reception. Once an error is detected, the 
    current frame handling shall be aborted and the error indication callback function 
    LinIf_LinErrorIndication shall be called. */
    /* Abort data transmission */
#if (LIN_DEM_ERROR_REPORT_STATUS == STD_ON)
    RetStatus = Asi_Hal_SoftReset(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], LIN_TIMEOUT_DURATION);
#else
    (void)Asi_Hal_SoftReset(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], LIN_TIMEOUT_DURATION);
#endif /* (LIN_DEM_ERROR_REPORT_STATUS  \== STD_ON) */
    LIN_EXIT_CRITICAL_SECTION(ErrorHandle);
    /* Reset header received status */
    ChannelStatusPtr->IsHeaderRecv = FALSE;
#if (LIN_DEM_ERROR_REPORT_STATUS == STD_ON)
    if (E_NOT_OK == RetStatus)
    {
        /* \[SWS_Lin_00218]   The LIN Driver module shall report the production or default
        error "LIN_E_TIMEOUT (value assigned by DEM)", when Timeout caused by
        hardware error.  */
        Dem_SetEventStatus(LIN_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
    }
    else
    {
        /* \[SWS_Lin_00218]   The LIN Driver module shall report the production or default
        error "LIN_E_TIMEOUT (value assigned by DEM)", when Timeout caused by
        hardware error.  */
        Dem_SetEventStatus(LIN_E_TIMEOUT, DEM_EVENT_STATUS_PASSED);
    }
#endif /* (LIN_DEM_ERROR_REPORT_STATUS  \== STD_ON) */
}

/****************************************************************************************************
*   Function Name           : Lin_CalculatePid
*
*   Service ID              : None
*
*   Description             : Calculate Pid from ID.
*
*   Parameters in           : uint8 FrameID
*                             
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : Lin_FramePidType .
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Lin_FramePidType, LIN_PRIVATE_CODE) Lin_CalculatePid
(
    uint8           FramePid
)
{
    uint32 U32Temp1;
    uint32 U32Temp2;

    U32Temp1 = ((uint32)FramePid) & LIN_PID_MASK_PARITY;
    U32Temp2 = FramePid;

    /* Calculate parity bit P1 = !(ID1 ^ ID3 ^ ID4 ^ ID5) */
    U32Temp1 |= ((((U32Temp2 >> 1U) ^ \
                   (U32Temp2 >> 3U) ^ \
                   (U32Temp2 >> 4U) ^ \
                   (U32Temp2 >> 5U) \
                  )& ((uint32)1U) \
                 ) ^ ((uint32)1U) \
                ) << (uint32)7U;

    /* Calculate parity bit P0 = (ID0 ^ ID1 ^ ID2 ^ ID4) */
    U32Temp1 |= (((U32Temp2) ^ \
                  (U32Temp2 >> 1U) ^ \
                  (U32Temp2 >> 2U) ^ \
                  (U32Temp2 >> 4U) \
                 ) & ((uint32)1U) \
                ) << (uint32)6U;

    return (uint8)U32Temp1;
}

#endif /* (LIN_SLAVE_MODE_USED  \== STD_ON) */

/****************************************************************************************************
*   Function Name           : Lin_IsrWakeupHandler
*
*   Service ID              : None
*
*   Description             : Handler wake-up signal.
*
*   Parameters in           : ChannelStatusPtr: Point to current LIN channel status.
*                             ChannelConfigPtr : Lin channel configuration parameters address.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, LIN_PRIVATE_CODE) Lin_IsrWakeupHandler
(
    /* #Violation: Lin_c_REF_2 */
    CONSTP2VAR(Lin_ChInternalStatusType, AUTOMATIC, LIN_APPL_CONST) ChannelStatusPtr,
    CONSTP2CONST(Lin_ChannelConfigType, AUTOMATIC, LIN_APPL_CONST) ChannelConfigPtr
)
{
    uint32          RegValue;

    /* Get the status value of the automatic wakeup flag */
    RegValue = 
        Asi_Lin_Hal_GetFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], ASI_LIN_WAKEUP_FLAG);
    if (ASI_LIN_WAKEUP_FLAG == RegValue)
    {
        /* Clear wake-up flag */
        /* \[SWS_Lin_00157]   The Lin module shall reset the interrupt flag at the end of the 
        ISR (if not done automatically by hardware).   */
        Asi_Lin_Hal_ClearFlagStatus(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], ASI_LIN_WAKEUP_FLAG);
        /* Only set when current status is sleeping */
        if ((LIN_CH_SLEEP_STATE == ChannelStatusPtr->ChStatus) || (LIN_CH_SLEEP_PENDING == ChannelStatusPtr->ChStatus))
        {
            /* Set wake-up state */
            ChannelStatusPtr->WakeupFlag = TRUE;
#if (LIN_CFG_INTERRUPT_ENABLE == STD_ON)
#if (LIN_WAKEUP_SUPPORT == STD_ON)
            /* Check whether wake-up detection is enabled */
            if (TRUE == ChannelConfigPtr->ChannelWakeupSupport)
            {
                /* \[SWS_Lin_00176]   The Lin module shall invoke the callback function 
                EcuM_CheckWakeup from within the wake-up ISR of the corresponding LIN channel 
                when a valid LIN wake-up pulse has been detected.  */
                EcuM_CheckWakeup(ChannelConfigPtr->ChannelEcuMWakeupSource);
            }
#endif /* (LIN_WAKEUP_SUPPORT  \== STD_ON) */
#endif /* (LIN_CFG_INTERRUPT_ENABLE  \== STD_ON) */
        }
    }
}

#if (LIN_MASTER_MODE_USED == STD_ON)
/****************************************************************************************************
*   Function Name           : Lin_ChannelStateTransition
*
*   Service ID              : None
*
*   Description             : Used for channel state transition.
*
*   Parameters in           : ChannelStatus: Point to current LIN channel status.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Lin_StatusType, LIN_PRIVATE_CODE) Lin_ChannelStateTransition
(
    Lin_ChStatusType ChannelStatus
)
{
    Lin_StatusType Lin_StandRetVal;

    switch(ChannelStatus)
    {
        case LIN_CH_TX_OK_STATUS:
        {
            /* Successful transmission */
            Lin_StandRetVal = LIN_TX_OK;
          break;
        }
        case LIN_CH_TX_HEADER_ERROR_STATUS:
        {
            /* Header error */
            Lin_StandRetVal = LIN_TX_HEADER_ERROR;
          break;
        }
        case LIN_CH_TX_ERROR_STATUS:
        {
            /* Transmission error */
            Lin_StandRetVal = LIN_TX_ERROR;
          break;
        }
        case LIN_CH_RX_OK_STATUS:
        {
            /* Successful receive */
            Lin_StandRetVal = LIN_RX_OK;
          break;
        }
        case LIN_CH_RX_BUSY_STATUS:
        {
            /* Receive busy */
            Lin_StandRetVal = LIN_RX_BUSY;
          break;
        }
        case LIN_CH_RX_ERROR_STATUS:
        {
            /* Receive error */
            Lin_StandRetVal = LIN_RX_ERROR;
          break;
        }
        case LIN_CH_RX_NO_RESPONSE_STATUS:
        {
            /* No response */
            Lin_StandRetVal = LIN_RX_NO_RESPONSE;
          break;
        }
        case LIN_CH_OPERATIONAL:
        {
            /* Successful transmission */
            Lin_StandRetVal = LIN_OPERATIONAL;
          break;
        }
        default:
        {
            /* LIN_CH_TX_BUSY_STATUS, LIN_CH_TX_HEADER_BUSY_STATUS, LIN_CH_SLEEP_STATE,
               LIN_CH_SLEEP_PENDING, LIN_CH_OTHER_ERROR
               case LIN_CH_SLEEP_PENDING, LIN_CH_SLEEP_STATE is used in Lin_GetStatus;
               case LIN_CH_TX_BUSY_STATUS, LIN_CH_TX_HEADER_BUSY_STATUS is used in 
               Lin_GetChStatus;
               case LIN_CH_OTHER_ERROR Transmission error */
            Lin_StandRetVal = LIN_NOT_OK;
          break;
        }
    }
    return Lin_StandRetVal;
}
#endif /* (LIN_MASTER_MODE_USED \== STD_ON) */

/* #Violation: Lin_c_REF_11*/
#define LIN_STOP_SEC_CODE_ASIL_D_GLOBAL 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/* #Violation: Lin_c_REF_11*/
#define LIN_START_SEC_CODE_ASIL_D_GLOBAL 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 

/****************************************************************************************************
*   Function Name           : Lin_Init
*
*   Service ID              : 0x00.
*
*   Description             : Initializes the LIN module.
*
*   Parameters in           : ConfigPtr: Pointer to LIN driver configuration set.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Lin_00006.
****************************************************************************************************/
/* #Violation: Lin_c_REF_10 */ 
FUNC(void, LIN_PUBLIC_CODE) Lin_Init
(
    /* #Violation: Lin_c_REF_7 */ 
    P2CONST(Lin_ConfigType, AUTOMATIC, LIN_APPL_CONST) ConfigPtr
)
{
    uint8                       ChannelLoop;
    uint8                       CoreMaxChannel;
    Mcal_CoreType               CoreId;    
    const Lin_ChannelConfigType *ChannelConfigPtr;
    Lin_ChInternalStatusType    *ChannelStatusPtr;
    Std_ReturnType              RetStatus;

    /* Get core id which is executing currently */
    /* #Violation: Lin_c_REF_5 */
    CoreId = Mcal_GetCoreId(); 
    

#if (LIN_DEV_ERROR_DETECT == STD_ON)
    RetStatus = Lin_GetDetStatus(CoreId, 0xFFU, LIN_SID_INIT, ConfigPtr);
    if(E_OK == RetStatus)
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Set the initial function return status value */
        RetStatus = E_OK;
        /* Get the total channel number of current core */
        CoreMaxChannel = ConfigPtr->CoreConfigPtr[CoreId]->MaxCoreChannels;
        /* Initialize all channels in current core */
        /* \[SWS_Lin_00084]   The function Lin_Init shall initialize the Lin module (i.e. static 
        variables, including flags and LIN HW Unit global hardware settings), as well as the 
        LIN channels.   */
        /* \[SWS_Lin_00190]   The function Lin_Init shall also invoke initializations for LIN 
        channel specific settings.  */
        for (ChannelLoop = 0U; (ChannelLoop < CoreMaxChannel)&&(E_OK == RetStatus); ChannelLoop++)
        {
            /* Get Lin channel configuration in current core */
            ChannelConfigPtr = &(ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[ChannelLoop]);
            /* Initialize the configuration registers of the current Channel */
            /* \[SWS_Lin_00150]   The function Lin_Init shall initialize the module according to the 
            configuration set pointed to by the parameter Config.  */
            /* \[SWS_Lin_00008]   The function Lin_Init shall invoke initializations for relevant 
            hardware register settings common to all channels available on the LIN hardware 
            unit.  */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
            if(LIN_MAX_HWUNIT_COUNT > ChannelConfigPtr->HwUnitId)
            {
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
                RetStatus = Asi_Lin_Hal_InitModule(Lin_BaseAddr[ChannelConfigPtr->HwUnitId], 
                    ChannelConfigPtr->RegisterConfigPtr, LIN_TIMEOUT_DURATION);
#if (LIN_DEV_ERROR_DETECT == STD_ON)
            }
            else
            {
                RetStatus = E_NOT_OK;
            }
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
            /* Initialize success */
            if (E_OK == RetStatus)
            {
                /* Get channel status pointer address */
                ChannelStatusPtr = &(Lin_CoreStatus[CoreId]->ChannelStatusPtr[ChannelLoop]);
                /* Convert the LIN Channel Status to 'OPERATIONAL' */
                /* \[SWS_Lin_00171] On entering the state LIN_INIT, the Lin module shall set each 
                channel into state LIN_CH_SLEEP, enable the wake-up detection (if enabled by 
                LinChannelWakeupSupport), and optionally set the LIN hardware unit to reduced 
                power operation mode (if supported by HW).  */
                Asi_Hal_EnterSleepMode(Lin_BaseAddr[ChannelConfigPtr->HwUnitId]);
#if (LIN_CFG_INTERRUPT_ENABLE == STD_ON)
#if (LIN_WAKEUP_SUPPORT == STD_ON)
                Lin_WakeupDetect(ChannelConfigPtr, TRUE);
#endif /* (LIN_WAKEUP_SUPPORT  \== STD_ON) */
#endif /* (LIN_CFG_INTERRUPT_ENABLE  \== STD_ON) */
                /* Set state machine to LIN_CH_SLEEP_STATE */
                ChannelStatusPtr->ChStatus = LIN_CH_SLEEP_STATE;
                /* Specify internal Sdu buffer */
                /* \[SWS_Lin_00092]   If a SDU has been successfully received, the function 
                    Lin_GetStatus shall store the SDU in a shadow buffer or memory mapped LIN 
                    Hardware receive buffer referenced by Lin_SduPtr. The buffer will only be valid and 
                    must be read until the next Lin_SendFrame function call.  */
                ChannelStatusPtr->PduBuffer.SduPtr = &(Lin_CoreStatus[CoreId]->
                    CoreSduBufferPtr[ChannelLoop * LIN_MAX_SDU_BUFFER_LENGTH]);
                /* Reset auto-wake-up flag */
                ChannelStatusPtr->WakeupFlag = FALSE;
                /* Reset header received flag */
                ChannelStatusPtr->IsHeaderRecv = FALSE;
                /* Clear LIN channel buffer */
                Lin_ClearLinChBuffer(ChannelStatusPtr);
#if (LIN_DEM_ERROR_REPORT_STATUS == STD_ON)
                /* \[SWS_Lin_00218]   The LIN Driver module shall report the production or default
                error "LIN_E_TIMEOUT (value assigned by DEM)", when Timeout caused by
                hardware error.  */
                Dem_SetEventStatus(LIN_E_TIMEOUT, DEM_EVENT_STATUS_PASSED);
#endif /* (LIN_DEM_ERROR_REPORT_STATUS  \== STD_ON) */
#if (LIN_DEM_ERROR_REPORT_STATUS == STD_ON)
            }
            else
            {
                Dem_SetEventStatus(LIN_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
#endif /* (LIN_DEM_ERROR_REPORT_STATUS  \== STD_ON) */
            }
        }
        /* All LIN channels are initialized successfully */
        if (E_OK == RetStatus)
        {
            /* Set initialization RetStatus */
            /* \[SWS_Lin_00146]   LIN_UNINIT -> LIN_INIT: The Lin module shall transition from 
            LIN_UNINIT to LIN_INIT when the function Lin_Init is called.  */
            *(Lin_CoreStatus[CoreId]->CoreInitStatusPtr) = LIN_INIT;
            if (NULL_PTR == Lin_ConfigPtr)
            {
                /* Store configuration information for use by other APIs when 'Lin_ConfigPtr'
                    * if NULL, For avoid repeat-set when multicore used */
                Lin_ConfigPtr = ConfigPtr;
            }
        }
    }
}

/****************************************************************************************************
*   Function Name           : Lin_CheckWakeup
*
*   Service ID              : 0x0A.
*
*   Description             : This function checks if a wake-up has occurred on the addressed
*                             LIN channel.
*
*   Parameters in           : Channel: LIN channel to be addressed.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK: No error has occurred during execution of the API
*                             E_NOT_OK: An error has occurred during execution of the API
*
*   Preconditions           : LIN channel is in sleep mode.
*
*   AUTOSAR_Requirement     : SWS_Lin_00160.
****************************************************************************************************/
/* #Violation: Lin_c_REF_10 */ 
FUNC(Std_ReturnType, LIN_PUBLIC_CODE) Lin_CheckWakeup
(
    uint8 Channel
)
{
    uint8                           CoreChIdx;
    Mcal_CoreType                   CoreId;    
    Std_ReturnType                  RetStatus;
#if ((LIN_CFG_INTERRUPT_ENABLE == STD_OFF) || ((LIN_WAKEUP_SUPPORT == STD_ON)))
    const Lin_ChannelConfigType     *ChannelConfigPtr;
#endif /* ((LIN_CFG_INTERRUPT_ENABLE == STD_OFF) /|| ((LIN_WAKEUP_SUPPORT == STD_ON))) */
    Lin_ChInternalStatusType        *ChannelStatusPtr;

    /* Get core id which is executing currently */
    /* #Violation: Lin_c_REF_5 */
    CoreId = Mcal_GetCoreId(); 

    /* \[SWS_Lin_00251]    If development error detection for the LIN module is enabled: if 
    the channel parameter is invalid, the function Lin_CheckWakeup shall raise the 
    development error LIN_E_INVALID_CHANNEL otherwise (if DET is disabled) return 
    E_NOT_OK.  */
    /* \[SWS_Lin_00107]   If default error detection for the LIN module is enabled: if the 
    function Lin_CheckWakeup is called before the LIN module was initialized, the 
    function Lin_CheckWakeup shall raise the default error LIN_E_UNINIT.  */
    RetStatus = Lin_GetDetStatus(CoreId, Channel, LIN_SID_CHECKWAKEUP, NULL_PTR);
    if(E_OK == RetStatus)
    {
        /* Set the initial function return status value */
        RetStatus = E_NOT_OK;
        /* Find  channel id in current core */
        CoreChIdx = Lin_ConfigPtr->ChannelToCorePtr[Channel];
        /* Get the LIN Channel Status pointer */
        ChannelStatusPtr = &(Lin_CoreStatus[CoreId]->ChannelStatusPtr[CoreChIdx]);
        /* Only can check wake-up signal when Lin channel in sleep Status */
        /* \[SWS_Lin_00220]   If wake-up detection is supported by configuration parameter 
        LinChannelWakeupSupport , then the function Lin_GoToSleep shall enable the 
        wake-up detection, even in case of an erroneous transmission of the go-to-sleep-command.  */
        if ((LIN_CH_SLEEP_STATE == ChannelStatusPtr->ChStatus) || (LIN_CH_SLEEP_PENDING == ChannelStatusPtr->ChStatus))
        {
#if ((LIN_CFG_INTERRUPT_ENABLE == STD_OFF) || ((LIN_WAKEUP_SUPPORT == STD_ON)))
            /* Get channel configuration information structure pointer */
            ChannelConfigPtr = &(Lin_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx]);
#endif /* ((LIN_CFG_INTERRUPT_ENABLE == STD_OFF) /|| ((LIN_WAKEUP_SUPPORT == STD_ON))) */
#if (LIN_CFG_INTERRUPT_ENABLE == STD_OFF)
            /* Call to wake up the middle segment service function */
            Lin_IsrWakeupHandler(ChannelStatusPtr, ChannelConfigPtr);
#endif /* (LIN_CFG_INTERRUPT_ENABLE  \== STD_OFF) */
            /* Check if the Lin channel detects a wake-up signal */
            /* \[SWS_Lin_00098]   The function Lin_CheckWakeup shall evaluate the wakeup on 
            the addressed LIN channel. When a wake-up event on the addressed LIN channel 
            (e.g. RxD pin has constant low level) is detected, the function Lin_CheckWakeup 
            shall notify the ECU State Manager module immediately via the 
            EcuM_SetWakeupEvent and the Lin Interface module via LinIf_WakeupConfirmation 
            callback function.  */
            if (TRUE == ChannelStatusPtr->WakeupFlag)
            {
                /* Clear wake-up RetStatus when wake-up signal triggered */
                ChannelStatusPtr->WakeupFlag = FALSE;
                /* Check whether the automatic wake-up function is enabled */
#if (LIN_WAKEUP_SUPPORT == STD_ON)
                if (TRUE == ChannelConfigPtr->ChannelWakeupSupport)
                {
                    /* Indicates a valid timer wake-up event to ECU State Manager */
                    EcuM_SetWakeupEvent(ChannelConfigPtr->ChannelEcuMWakeupSource);
                    /* Report the wake-up source after the successful wake-up to LinInterface */
                    /* \[SWS_LinIf_00716] the function LinIf_WakeupConfirmation shall set the wakeup
                    flag for the channel depending on the given parameter WakeupSource. The wakeup 
                    flags shall be provided for each channel.   */
                    LinIf_WakeupConfirmation(ChannelConfigPtr->ChannelEcuMWakeupSource);
                }
#endif /* (LIN_WAKEUP_SUPPORT  \== STD_ON) */
                /* Set function return status value */
                RetStatus = E_OK;
            }
        }
    }

    return RetStatus;
}

#if (LIN_VERSION_INFO_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Lin_GetVersionInfo
*
*   Service ID              : 0x01.
*
*   Description             : This service returns the version information of this module.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : VersionInfoPtr: Pointer to where to store the version information of this
*                                             module.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Lin_00161
****************************************************************************************************/
/* #Violation: Lin_c_REF_10 */ 
FUNC(void, LIN_PUBLIC_CODE) Lin_GetVersionInfo
(
    /* #Violation: Lin_c_REF_7 */ 
    /* #Violation: Lin_c_REF_2 */
    P2VAR(Std_VersionInfoType, AUTOMATIC, LIN_APPL_DATA) VersionInfoPtr
)
{
#if (LIN_DEV_ERROR_DETECT == STD_ON)
    if(NULL_PTR == VersionInfoPtr)
    {
        /* Invalid pointer */
        /* \[SWS_Lin_00248]   If default error detection for the LIN module is enabled: If the 
        parameter versioninfo is a NULL pointer, the function Lin_GetVersionInfo shall raise 
        the error LIN_E_PARAM_POINTER.  */
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_GETVERSIONINFO,
                              LIN_E_PARAM_POINTER);
    }
    else
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* \[SWS_Lin_00001]   The function Lin_GetVersionInfo shall return the version 
        information of the LIN module. The version information includes:
        Two bytes for the vendor ID
        Two byte for the module ID
        Three bytes version number The numbering shall be vendor specific; it 
        consists of:
        - The major, the minor and the patch version number of the 
        module.
        - The AUTOSAR specification version number shall not be 
        included. The AUTOSAR specification version number is 
        checked during compile time and therefore not required in this 
        API.  (SRS_BSW_00407) */
        VersionInfoPtr->vendorID = (uint16)LIN_VENDOR_ID;
        VersionInfoPtr->moduleID = (uint16)LIN_MODULE_ID;
        VersionInfoPtr->sw_major_version = (uint8)LIN_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = (uint8)LIN_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = (uint8)LIN_SW_PATCH_VERSION;
    }
}
#endif /* LIN_VERSION_INFO_API == STD_ON */

/* \[SWS_Lin_00287] The function Lin_SendFrame is only available if the Lin module 
is configured as LIN master node on at least one channel. In a pure LIN slave 
configuration, this function is not available. This depends on the configuration 
parameters LinNodeType. */
#if (LIN_MASTER_MODE_USED == STD_ON)
/****************************************************************************************************
*   Function Name           : Lin_SendFrame
*
*   Service ID              : 0x04.
*
*   Description             : Sends a LIN header and a LIN response, if necessary. The direction of
*                             the frame response (master response, slave response, slave-to-slave
*                             communication) is provided by the PduInfoPtr.
*
*   Parameters in           : Channel: LIN channel to be addressed.
*                             PduInfoPtr: Pointer to PDU containing the PID, checksum model,
*                                         response type, Dl and SDU data pointer
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK: Send command has been accepted.
*                             E_NOT_OK: Send command has not been accepted,
*                                       development or production error occurred.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Lin_00191
****************************************************************************************************/
/* #Violation: Lin_c_REF_10 */ 
FUNC(Std_ReturnType, LIN_PUBLIC_CODE) Lin_SendFrame
(
    uint8 Channel,
    /* #Violation: Lin_c_REF_7 */ 
    P2CONST(Lin_PduType, AUTOMATIC, LIN_APPL_DATA) PduInfoPtr
)
{
    uint8                       LoopCount;
    uint8                       CoreChIdx;    
    Mcal_CoreType               CoreId;
    Std_ReturnType              RetStatus;
    Lin_ChInternalStatusType    *ChannelStatusPtr;   

    /* Get core id which is executing currently */
    /* #Violation: Lin_c_REF_5 */
    CoreId = Mcal_GetCoreId(); 

    /* \[SWS_Lin_00195]   If development error detection for the LIN module is enabled: if 
        the function Lin_SendFrame is called before the LIN module was initialized, the 
        function Lin_SendFrame shall raise the development error LIN_E_UNINIT otherwise 
        (if DET is disabled) return E_NOT_OK.  */
        /* API service used with an invalid or inactive channel parameter */
    /* \[SWS_Lin_00197]   If development error detection for the LIN module is enabled: if 
        the channel parameter is invalid, the function Lin_SendFrame shall raise the 
        development error LIN_E_INVALID_CHANNEL otherwise (if DET is disabled) return
        E_NOT_OK.  */
    /* Check PduInfoPtr for not being a null pointer */
    RetStatus = Lin_GetDetStatus(CoreId, Channel, LIN_SID_SENDFRAME, NULL_PTR);
    if (E_OK == RetStatus)
    {
        /* Set the return value of the function execution status to E_NOT_OK */
        RetStatus = E_NOT_OK;
        if (NULL_PTR == PduInfoPtr)
        {
#if (LIN_DEV_ERROR_DETECT == STD_ON)
            /* \[SWS_Lin_00198]   If development error detection for the LIN module is enabled: 
            the function Lin_SendFrame shall check the parameter PduInfoPtr for not being a 
            NULL pointer. If PduInfoPtr is a NULL pointer, the function Lin_SendFrame shall 
            raise the development error LIN_E_PARAM_POINTER otherwise (if DET is disabled) 
            return E_NOT_OK.  */
            /* Invalid pointer */
            (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_SENDFRAME,
                                    LIN_E_PARAM_POINTER);
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
        }
        else if((LIN_FRAMERESPONSE_TX == PduInfoPtr->Drc) && (NULL_PTR == PduInfoPtr->SduPtr))
        {
#if (LIN_DEV_ERROR_DETECT == STD_ON)
            /* Invalid pointer */
            (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_SENDFRAME,
                                    LIN_E_PARAM_POINTER);
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
        }
        else
        {
            /* Find sub channel id in current core */
            CoreChIdx = Lin_ConfigPtr->ChannelToCorePtr[Channel];
            /* Get channel status information structure pointer */
            ChannelStatusPtr = &(Lin_CoreStatus[CoreId]->ChannelStatusPtr[CoreChIdx]);
            /* load current LIN channel configuration information address */
            if (ASI_LIN_MODE_SLAVE == 
                (&(Lin_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx]))->
                RegisterConfigPtr->mode)
            {
#if (LIN_DEV_ERROR_DETECT == STD_ON)
                /* \[SWS_Lin_00197] If development error detection for the LIN module is enabled: if 
                the channel parameter is invalid, the function Lin_SendFrame shall raise the 
                development error LIN_E_INVALID_CHANNEL otherwise (if DET is disabled) return
                E_NOT_OK. */
                (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_SENDFRAME,
                                          LIN_E_INVALID_CHANNEL);
#endif /* (LIN_DEV_ERRO?R_DETECT  \== STD_ON) */
            }
            /* Check whether the LIN channel is in LIN_CH_SLEEP_STATE state */
            /* \[SWS_Lin_00194]   The Lin module environment shall only call Lin_SendFrame
            on a channel which is in state LIN_CH_OPERATIONAL or in one of the sub-states of 
            LIN_CH_OPERATIONAL.  */
            else if ((LIN_CH_SLEEP_STATE == ChannelStatusPtr->ChStatus) ||
                (LIN_CH_SLEEP_PENDING == ChannelStatusPtr->ChStatus))
            {
                /* LIN channel is in sleep mode */
#if (LIN_DEV_ERROR_DETECT == STD_ON)
                /* \[SWS_Lin_00199]   If development error detection for the LIN module is enabled: if 
                the LIN channel state-machine is in the state LIN_CH_SLEEP, the function 
                Lin_SendFrame shall raise the development error LIN_E_STATE_TRANSITION
                otherwise (if DET is disabled) return E_NOT_OK.  */
                (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_SENDFRAME,
                                        LIN_E_STATE_TRANSITION);
#endif /* (LIN_DEV_ERRO?R_DETECT  \== STD_ON) */
            }
            else
            {
                /* Copy PDU parameters */
                /* \[SWS_Lin_00053]   The LIN driver shall directly copy the data from the upper layer 
                buffers.   ( SRS_Lin_01522, SRS_Lin_01526) */
                /* \[SWS_Lin_00025]   The LIN driver shall send response data as provided by the LIN 
                interface module (see Lin_SendFrame).  ( SRS_Lin_01522, SRS_Lin_01503) */
                ChannelStatusPtr->PduBuffer.Dl = PduInfoPtr->Dl;
                ChannelStatusPtr->PduBuffer.Cs = PduInfoPtr->Cs;
                ChannelStatusPtr->PduBuffer.Pid = PduInfoPtr->Pid;
                ChannelStatusPtr->PduBuffer.Drc = PduInfoPtr->Drc;
                /* Check whether master response is required */
                if (LIN_FRAMERESPONSE_TX == PduInfoPtr->Drc)
                {
                    /* Copy data from 'PduInfoPtr' to internal buffer */
                    for (LoopCount = 0U; LoopCount < PduInfoPtr->Dl; LoopCount++)
                    {
                        ChannelStatusPtr->PduBuffer.SduPtr[LoopCount] = PduInfoPtr->SduPtr[LoopCount];
                    }
                }
                else
                {
                    /* Clear LIN channel buffer */
                    Lin_ClearLinChBuffer(ChannelStatusPtr);
                }
                /* Set LIN Channel Status to 'LIN_CH_TX_HEADER_BUSY_STATUS' */
                ChannelStatusPtr->ChStatus = LIN_CH_TX_HEADER_BUSY_STATUS;
                /* Start send frame header and response(if need) */
                RetStatus = Lin_SendFrameData(ChannelStatusPtr, 
                    Lin_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx].HwUnitId);
#if (LIN_DEM_ERROR_REPORT_STATUS == STD_ON)
                if (E_OK == RetStatus)
                {
                    /* \[SWS_Lin_00218]   The LIN Driver module shall report the production or default
                    error "LIN_E_TIMEOUT (value assigned by DEM)", when Timeout caused by
                    hardware error.  */
                    Dem_SetEventStatus(LIN_E_TIMEOUT, DEM_EVENT_STATUS_PASSED);
                }
                else
                {
                    /* \[SWS_Lin_00218]   The LIN Driver module shall report the production or default
                    error "LIN_E_TIMEOUT (value assigned by DEM)", when Timeout caused by
                    hardware error.  */
                    Dem_SetEventStatus(LIN_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
                }
#endif
            }
        }
    }

    return RetStatus;
}
#endif /* (LIN_MASTER_MODE_USED  \== STD_ON) */

/* \[SWS_Lin_00288] The function Lin_GotoSleep is only available if the Lin module 
is configured as LIN master node on at least one channel. In a pure LIN slave 
configuration, this function is not available. This depends on the configuration 
parameters LinNodeType. */
#if (LIN_MASTER_MODE_USED == STD_ON)
/****************************************************************************************************
*   Function Name           : Lin_GoToSleep
*
*   Service ID              : 0x06.
*
*   Description             : The service instructs the driver to transmit a go-to-sleep-command on
*                             the addressed LIN channel.
*
*   Parameters in           : Channel: LIN channel to be addressed.
*
*   Parameters inout        : None.
*
*   Parameters out          :
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK: Sleep command has been accepted
*                             E_NOT_OK: Sleep command has not been accepted,
*                                       development or production error occurred
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Lin_00166
****************************************************************************************************/
/* #Violation: Lin_c_REF_10 */ 
FUNC(Std_ReturnType, LIN_PUBLIC_CODE) Lin_GoToSleep
(
    uint8 Channel
)
{

    uint8                    CoreChIdx;
    Mcal_CoreType            CoreId;    
    Std_ReturnType           RetStatus;
    Lin_ChInternalStatusType *ChannelStatusPtr;    

    /* Get core id which is executing currently */
    /* #Violation: Lin_c_REF_5 */
    CoreId = Mcal_GetCoreId(); 

#if (LIN_DEV_ERROR_DETECT == STD_ON)
    /* \[SWS_Lin_00129]   If default error detection for the LIN module is enabled: if the 
    function Lin_GoToSleep is called before the LIN module was initialized, the function 
    Lin_GoToSleep shall raise the default error LIN_E_UNINIT.  */
    /* \[SWS_Lin_00131]   If default error detection for the LIN module is enabled: the 
    function Lin_GoToSleep shall raise the default error LIN_E_INVALID_CHANNEL if 
    the channel parameter is invalid.  */
    RetStatus = Lin_GetDetStatus(CoreId, Channel, LIN_SID_GOTOSLEEP, NULL_PTR);
    if(E_OK == RetStatus)
#endif /* (LIN_DEV_ERRO?R_DETECT  \== STD_ON) */
    {
        /* Set the return value of the function execution status to E_NOT_OK */
        RetStatus = E_NOT_OK;
        /* Find sub channel id in current core */
        CoreChIdx = Lin_ConfigPtr->ChannelToCorePtr[Channel];
        /* Get channel state structure pointer */
        ChannelStatusPtr = &(Lin_CoreStatus[CoreId]->ChannelStatusPtr[CoreChIdx]);

        if (ASI_LIN_MODE_SLAVE == 
            (&(Lin_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx]))->RegisterConfigPtr->mode)
        {
#if (LIN_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_GOTOSLEEP,
                                  LIN_E_INVALID_CHANNEL);
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
        }
        /* Check whether the LIN channel is in LIN_CH_SLEEP_STATE state */
        else if (LIN_CH_SLEEP_STATE != ChannelStatusPtr->ChStatus)
        {
            /* Only send go to sleep command when LIN channel is not in LIN_CH_SLEEP_STATUS */
            /* Send go to sleep command */
            /* \[SWS_Lin_00263]   LIN_CH_OPERATIONAL -> LIN_CH_SLEEP_PENDING 
            through Lin_GoToSleep: If a go to sleep is requested by the LIN interface, the Lin 
            module shall ensure that the rest of the LIN cluster goes to sleep also. This is 
            achieved by issuing a go-to-sleep-command on the bus before entering the 
            LIN_CH_SLEEP_PENDING state.  */
            RetStatus = Lin_GoToSleepCmd(ChannelStatusPtr, 
                Lin_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx].HwUnitId);
#if (LIN_DEM_ERROR_REPORT_STATUS == STD_ON)
            if (E_OK == RetStatus)
            {
                /* \[SWS_Lin_00218]   The LIN Driver module shall report the production or default
                error "LIN_E_TIMEOUT (value assigned by DEM)", when Timeout caused by
                hardware error.  */
                Dem_SetEventStatus(LIN_E_TIMEOUT, DEM_EVENT_STATUS_PASSED);
            }
            else
            {
                /* \[SWS_Lin_00218]   The LIN Driver module shall report the production or default
                error "LIN_E_TIMEOUT (value assigned by DEM)", when Timeout caused by
                hardware error.  */
                Dem_SetEventStatus(LIN_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
            }
#endif /* (LIN_DEM_ERROR_REPORT_STATUS  \== STD_ON) */
            /* Set Channel state to LIN_CH_SLEEP_PENDING state */
            /* \[SWS_Lin_00266]  The function Lin_GoToSleep shall set the channel state to 
            LIN_CH_SLEEP_PENDING, even in case of an erroneous transmission of the go-to-sleep-command.  */
            ChannelStatusPtr->ChStatus = LIN_CH_SLEEP_PENDING;
#if (LIN_CFG_INTERRUPT_ENABLE == STD_ON)
#if (LIN_WAKEUP_SUPPORT == STD_ON)
            LIN_ENTER_CRITICAL_SECTION(GoToSleep);
            /* \[SWS_Lin_00220] If wake-up detection is supported by configuration parameter 
            LinChannelWakeupSupport , then the function Lin_GoToSleep shall enable the 
            wake-up detection, even in case of an erroneous transmission of the go-to-sleep-command.*/
            Lin_WakeupDetect(&(Lin_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx]), 
                             TRUE);
            LIN_EXIT_CRITICAL_SECTION(GoToSleep);
#endif /* (LIN_WAKEUP_SUPPORT  \== STD_ON) */
#endif /* (LIN_CFG_INTERRUPT_ENABLE  \== STD_ON) */
        }
        else
        /* #Violation: Lin_c_REF_9 */
        {
            /* Do nothing */
        }
    }

    return RetStatus;
}
#endif /* (LIN_MASTER_MODE_USED  \== STD_ON) */

/****************************************************************************************************
*   Function Name           : Lin_GoToSleepInternal
*
*   Service ID              : 0x09.
*
*   Description             : Sets the channel state to LIN_CH_SLEEP, enables the wake-up detection
*                             and optionally sets the LIN hardware unit to reduced power operation
*                             mode (if supported by HW).
*
*   Parameters in           : Channel: LIN channel to be addressed.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK: Sleep command has been accepted
*                             E_NOT_OK: Sleep command has not been accepted,
*                                       development or production error occurred
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Lin_00167
****************************************************************************************************/
/* #Violation: Lin_c_REF_10 */ 
FUNC(Std_ReturnType, LIN_PUBLIC_CODE) Lin_GoToSleepInternal
(
    uint8 Channel
)
{
    uint8                    CoreChIdx;
    Mcal_CoreType            CoreId;
    Std_ReturnType           RetStatus;
    Lin_ChInternalStatusType *ChannelStatusPtr;

    /* Get core id which is executing currently */
    /* #Violation: Lin_c_REF_5 */
    CoreId = Mcal_GetCoreId(); 

#if (LIN_DEV_ERROR_DETECT == STD_ON)
    /* \[SWS_Lin_00133]   If default error detection for the LIN module is enabled: if the 
    function Lin_GoToSleepInternal is called before the LIN module was initialized, the 
    function Lin_GoToSleepInternal shall raise the default error LIN_E_UNINIT.  */
    /* \[SWS_Lin_00135]   If default error detection for the LIN module is enabled: the 
    function Lin_GoToSleepInternal shall raise the default error 
    LIN_E_INVALID_CHANNEL if the channel parameter is invalid.  */
    RetStatus = Lin_GetDetStatus(CoreId, Channel, LIN_SID_GOTOSLEEPINTERNAL, NULL_PTR);
    if(E_OK == RetStatus)
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Set the initial function return status value */
        RetStatus = E_NOT_OK;
        /* Find sub channel id in current core */
        CoreChIdx = Lin_ConfigPtr->ChannelToCorePtr[Channel];
        /* Get channel state structure pointer */
        ChannelStatusPtr = &(Lin_CoreStatus[CoreId]->ChannelStatusPtr[CoreChIdx]);
        /* Check whether the LIN channel is in LIN_CH_OPERATIONAL state */
        if (LIN_CH_SLEEP_STATE != ChannelStatusPtr->ChStatus)
        {
#if (LIN_CFG_INTERRUPT_ENABLE == STD_ON)
#if (LIN_WAKEUP_SUPPORT == STD_ON)
            LIN_ENTER_CRITICAL_SECTION(GoToSleepInternal);
            /* \[SWS_Lin_00222] The function Lin_GoToSleepInternal shall enable the wake-up.*/
            Lin_WakeupDetect(&(Lin_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx]), TRUE);
            LIN_EXIT_CRITICAL_SECTION(GoToSleepInternal);
#endif /* (LIN_WAKEUP_SUPPORT  \== STD_ON) */
#endif /* (LIN_CFG_INTERRUPT_ENABLE  \== STD_ON) */
            /* Enter low power mode */
            /* \[SWS_Lin_00032]   When the LIN channel enters sleep mode, it shall perform the 
            transition to low-power mode of the LIN hardware unit (if available) (see
            Lin_GoToSleep/Lin_GoToSleepInternal).  ( SRS_Lin_01524) */
            RetStatus = Lin_GoToSleepInternalCmd(
                Lin_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx].HwUnitId);
            /* Enter low power mode successfully */
            if (E_OK == RetStatus)
            {
                /* Set LIN Channel Status to LIN_CH_SLEEP_STATE */
                /* \[SWS_Lin_00265]   LIN_CH_OPERATIONAL -> LIN_CH_SLEEP through 
                Lin_GoToSleepInternal: If an internal go to sleep is requested by the LIN interface, 
                the LIN driver shall directly enter the LIN_CH_SLEEP state.  */
                /* \[SWS_Lin_00095]   The function Lin_GoToSleepInternal shall set the channel state 
                to LIN_CH_SLEEP.  */
                ChannelStatusPtr->ChStatus = LIN_CH_SLEEP_STATE;
#if (LIN_DEM_ERROR_REPORT_STATUS == STD_ON)
                /* \[SWS_Lin_00218]   The LIN Driver module shall report the production or default
                error "LIN_E_TIMEOUT (value assigned by DEM)", when Timeout caused by
                hardware error.  */
                Dem_SetEventStatus(LIN_E_TIMEOUT, DEM_EVENT_STATUS_PASSED);
            }
            else
            {
                /* \[SWS_Lin_00218]   The LIN Driver module shall report the production or default
                error "LIN_E_TIMEOUT (value assigned by DEM)", when Timeout caused by
                hardware error.  */
                Dem_SetEventStatus(LIN_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
#endif
            }
        }
    }

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Lin_Wakeup
*
*   Service ID              : 0x07.
*
*   Description             : Generates a wake up pulse and sets the channel state to
*                             LIN_CH_OPERATIONAL.
*
*   Parameters in           : Channel: LIN channel to be addressed.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK: Wake-up request has been accepted
*                             E_NOT_OK: Wake-up request has not been accepted,
*                                       development or production error occurred
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Lin_00169
****************************************************************************************************/
/* #Violation: Lin_c_REF_10 */ 
FUNC(Std_ReturnType, LIN_PUBLIC_CODE) Lin_Wakeup
(
    uint8 Channel
)
{
    uint8                           CoreChIdx;
    Mcal_CoreType                   CoreId;
    Std_ReturnType                  RetStatus;
    Lin_ChInternalStatusType        *ChannelStatusPtr;

    /* Get core id which is executing currently */
    /* #Violation: Lin_c_REF_5 */
    CoreId = Mcal_GetCoreId(); 

#if (LIN_DEV_ERROR_DETECT == STD_ON)
    /* \[SWS_Lin_00137]   If default error detection for the LIN module is enabled: if the 
    function Lin_Wakeup is called before the LIN module was initialized, the function 
    Lin_Wakeup shall raise the default error LIN_E_UNINIT.  */
    /* \[SWS_Lin_00139]   If default error detection for the LIN module is enabled: the 
    function Lin_Wakeup shall raise the default error LIN_E_INVALID_CHANNEL if the 
    channel parameter is invalid or the channel is inactive.  */
    RetStatus = Lin_GetDetStatus(CoreId, Channel, LIN_SID_WAKEUP, NULL_PTR);
    if(E_OK == RetStatus)
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Find sub channel id in current core */
        CoreChIdx = Lin_ConfigPtr->ChannelToCorePtr[Channel];
        /* Get LIN Channel Status pointer */
        ChannelStatusPtr = &(Lin_CoreStatus[CoreId]->ChannelStatusPtr[CoreChIdx]);
        /* Check whether the LIN channel is in LIN_CH_SLEEP_STATE state */
        /* \[SWS_Lin_00140]   If default error detection for the LIN module is enabled: the 
        function Lin_Wakeup shall raise the default error LIN_E_STATE_TRANSITION if the 
        LIN channel state-machine is not in the state LIN_CH_SLEEP.   */
        if (LIN_CH_SLEEP_STATE != ChannelStatusPtr->ChStatus)
        {
#if (LIN_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_WAKEUP,
                                  LIN_E_STATE_TRANSITION);
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
            RetStatus = E_NOT_OK;
        }
        else
        {
            /* Clear LIN channel buffer first */
            Lin_ClearLinChBuffer(ChannelStatusPtr);
            /* Call the slave wake-up command */
            RetStatus = Lin_WakeupCmd(&(Lin_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx]));
            if (E_OK == RetStatus)
            {
                /* Set LIN Channel Status to LIN_CH_OPERATIONAL */
                /* \[SWS_Lin_00174]   LIN_CH_SLEEP -> LIN_CH_OPERATIONAL through 
                Lin_Wakeup: If a LIN channel is in the state LIN_CH_SLEEP, the function 
                Lin_Wakeup shall put the LIN channel into the state LIN_CH_OPERATIONAL.   */
                ChannelStatusPtr->ChStatus = LIN_CH_OPERATIONAL;
#if (LIN_DEM_ERROR_REPORT_STATUS == STD_ON)
                /* \[SWS_Lin_00218]   The LIN Driver module shall report the production or default
                error "LIN_E_TIMEOUT (value assigned by DEM)", when Timeout caused by
                hardware error.  */
                Dem_SetEventStatus(LIN_E_TIMEOUT, DEM_EVENT_STATUS_PASSED);
            }
            else
            {
                /* \[SWS_Lin_00218]   The LIN Driver module shall report the production or default
                error "LIN_E_TIMEOUT (value assigned by DEM)", when Timeout caused by
                hardware error.  */
                Dem_SetEventStatus(LIN_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
#endif
            }
        }
    }

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Lin_WakeupInternal
*
*   Service ID              : 0x0b.
*
*   Description             : Sets the channel state to LIN_CH_OPERATIONAL without generating a
*                             wake up pulse.
*
*   Parameters in           : Channel: LIN channel to be addressed.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK: Wake-up request has been accepted
*                             E_NOT_OK: Wake-up request has not been accepted,
*                                       development or production error occurred
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Lin_00256
****************************************************************************************************/
/* #Violation: Lin_c_REF_10 */ 
FUNC(Std_ReturnType, LIN_PUBLIC_CODE) Lin_WakeupInternal
(
    uint8 Channel
)
{
    uint8                           CoreChIdx;
    Mcal_CoreType                   CoreId;    
    Std_ReturnType                  RetStatus;
    Lin_ChInternalStatusType        *ChannelStatusPtr;
    /* Get core id which is executing currently */
    /* #Violation: Lin_c_REF_5 */
    CoreId = Mcal_GetCoreId(); 

#if (LIN_DEV_ERROR_DETECT == STD_ON)
    /* \[SWS_Lin_00258]   If default error detection for the LIN module is enabled: if the 
    function Lin_WakeupInternal is called before the LIN module was initialized, the 
    function Lin_WakeupInternal shall raise the default error LIN_E_UNINIT.  */
    /* \[SWS_Lin_00259]   If default error detection for the LIN module is enabled: the 
    function Lin_WakeupInternal shall raise the default error LIN_E_INVALID_CHANNEL
    if the channel parameter is invalid or the channel is inactive.  */
    RetStatus = Lin_GetDetStatus(CoreId, Channel, LIN_SID_WAKEUPINTERNAL, NULL_PTR);
    if(E_OK == RetStatus)
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Find sub channel id in current core */
        CoreChIdx = Lin_ConfigPtr->ChannelToCorePtr[Channel];
        /* Get LIN Channel Status pointer */
        ChannelStatusPtr = &(Lin_CoreStatus[CoreId]->ChannelStatusPtr[CoreChIdx]);
        /* Check whether the LIN channel is in LIN_CH_SLEEP_STATE state */
        /* \[SWS_Lin_00260]   If default error detection for the LIN module is enabled: the 
        function Lin_WakeupInternal shall raise the default error 
        LIN_E_STATE_TRANSITION if the LIN channel state-machine is not in the state 
        LIN_CH_SLEEP.   */
        if (LIN_CH_SLEEP_STATE != ChannelStatusPtr->ChStatus)  
        {
#if (LIN_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_WAKEUPINTERNAL,
                                  LIN_E_STATE_TRANSITION);
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
            RetStatus = E_NOT_OK;
        }
        else
        {
            /* Clear LIN channel buffer first */
            Lin_ClearLinChBuffer(ChannelStatusPtr);
            /* Set registers for initialization after wake-up */
            RetStatus = Lin_WakeupInternalCmd(
                &(Lin_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx]));
            if (E_OK == RetStatus)
            {
                /* Set LIN Channel Status to LIN_CH_OPERATIONAL */
                /* \[SWS_Lin_00261][   LIN_CH_SLEEP -> LIN_CH_OPERATIONAL through 
                Lin_WakeupInternal: If a LIN channel is in the state LIN_CH_SLEEP, the function 
                Lin_WakeupInternal shall put the LIN channel into the state 
                LIN_CH_OPERATIONAL.   */
                /* \[SWS_Lin_00257] the function Lin_WakeupInternal sets the addressed LIN
                channel to state LIN_CH_OPERATIONAL without generating a wake up pulse.  */
                ChannelStatusPtr->ChStatus = LIN_CH_OPERATIONAL;
#if (LIN_DEM_ERROR_REPORT_STATUS == STD_ON)
                /* \[SWS_Lin_00218]   The LIN Driver module shall report the production or default
                error "LIN_E_TIMEOUT (value assigned by DEM)", when Timeout caused by
                hardware error.  */
                Dem_SetEventStatus(LIN_E_TIMEOUT, DEM_EVENT_STATUS_PASSED);
            }
            else
            {
                /* \[SWS_Lin_00218]   The LIN Driver module shall report the production or default
                error "LIN_E_TIMEOUT (value assigned by DEM)", when Timeout caused by
                hardware error.  */
                Dem_SetEventStatus(LIN_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
#endif
            }
        }
    }

    return RetStatus;
}
/* \[SWS_Lin_00289] The function Lin_GetStatus is only available if the Lin module is 
configured as LIN master node on at least one channel. In a pure LIN slave 
configuration, this function is not available. This depends on the configuration 
parameters LinNodeType. */
#if (LIN_MASTER_MODE_USED == STD_ON)
/****************************************************************************************************
*   Function Name           : Lin_GetStatus
*
*   Service ID              : 0x08.
*
*   Description             : Gets the RetStatus of the LIN driver.
*
*   Parameters in           : Channel: LIN channel to be checked.
*
*   Parameters inout        : None.
*
*   Parameters out          : Lin_SduPtr: Pointer to pointer to a shadow buffer or memory mapped LIN
*                                         Hardware receive buffer where the current SDU is stored.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : Lin_StatusType: refer to the enumeration definition.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Lin_00168
****************************************************************************************************/
/* #Violation: Lin_c_REF_10 */ 
FUNC(Lin_StatusType, LIN_PUBLIC_CODE) Lin_GetStatus
(
    uint8 Channel,
    /* #Violation: Lin_c_REF_7 */ 
    /* #Violation: Lin_c_REF_2 */ 
    P2P2VAR(uint8, AUTOMATIC, LIN_APPL_DATA) Lin_SduPtr
)
{
    uint8                           CoreChIdx;
    Std_ReturnType                  RetStatus;
    Mcal_CoreType                   CoreId;   
    Lin_HWUnitType                  HwUnit;    
    Lin_StatusType                  LinStatus;
    Lin_ChInternalStatusType        *ChannelStatusPtr;
    const Lin_ChannelConfigType     *ChannelConfigPtr;

    /* Set Lin initial drive state */
    LinStatus = LIN_NOT_OK;
    /* Get core id which is executing currently */
    /* #Violation: Lin_c_REF_5 */
    CoreId = Mcal_GetCoreId(); 

    /* \[SWS_Lin_00141]   If default error detection for the LIN module is enabled: if the 
    function Lin_GetStatus is called before the LIN module was initialized, the function 
    Lin_GetStatus shall raise the default error LIN_E_UNINIT and return LIN_NOT_OK. */
    /* \[SWS_Lin_00143]   If default error detection for the LIN module is enabled: if the 
    channel parameter is invalid or the channel is inactive, the function Lin_GetStatus 
    shall raise the default error LIN_E_INVALID_CHANNEL and return LIN_NOT_OK. */
    RetStatus = Lin_GetDetStatus(CoreId, Channel, LIN_SID_GETSTATUS, NULL_PTR);
    /* Check Lin_SduPtr for not being a null pointer */
    if ((E_OK == RetStatus) && (NULL_PTR == Lin_SduPtr))
    {
#if (LIN_DEV_ERROR_DETECT == STD_ON)  
        /* \[SWS_Lin_00144]   If development error detection for the LIN module is enabled: 
        the function Lin_GetStatus shall check the parameter Lin_SduPtr for not being a 
        NULL pointer. If Lin_SduPtr is a NULL pointer, the function Lin_GetStatus shall raise 
        the development error LIN_E_PARAM_POINTER otherwise (if DET is disabled) 
        return LIN_NOT_OK.  */
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_GETSTATUS,
                                LIN_E_PARAM_POINTER);
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
        RetStatus = E_NOT_OK;
    }
    if(E_OK == RetStatus)
    {
        /* Find sub channel id in current core */
        CoreChIdx = Lin_ConfigPtr->ChannelToCorePtr[Channel];
        /* Get LIN Channel Status pointer */
        ChannelStatusPtr = &(Lin_CoreStatus[CoreId]->ChannelStatusPtr[CoreChIdx]);
        /* Get hardware unit of this LIN channel in this core */
        HwUnit = Lin_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx].HwUnitId;
        /* load current LIN channel configuration information address */
        ChannelConfigPtr = &(Lin_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx]);
        /* Whether the current channel is in slave mode */
        if (ASI_LIN_MODE_SLAVE == ChannelConfigPtr->RegisterConfigPtr->mode)
        {
#if (LIN_DEV_ERROR_DETECT == STD_ON)  
            /* \[SWS_Lin_00143]   If default error detection for the LIN module is enabled: if the 
            channel parameter is invalid or the channel is inactive, the function Lin_GetStatus 
            shall raise the default error LIN_E_INVALID_CHANNEL and return LIN_NOT_OK. */
            (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_GETSTATUS,
                                  LIN_E_INVALID_CHANNEL);
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
        }
        else
        {
            /* \[SWS_Lin_00022]   The function Lin_GetStatus shall return the status of the current 
            frame transmission request for the channel.  */
            switch (ChannelStatusPtr->ChStatus)
            {
                case LIN_CH_SLEEP_STATE:
                {
                    LinStatus = LIN_CH_SLEEP;
                    break;
                }
                case LIN_CH_SLEEP_PENDING:
                {
                    /* \[SWS_Lin_00264]   LIN_CH_SLEEP_PENDING -> LIN_CH_SLEEP: When 
                    Lin_GetStatus is called, the LIN driver shall directly enter the LIN_CH_SLEEP state, 
                    even if the go-to-sleep-command has not yet been sent.   */
                    /* \[SWS_Lin_00255]  The LIN channel shall enter the state LIN_CH_SLEEP the next 
                    time Lin_GetStatus is called, independent of the success of the transmission of the 
                    goto-sleep-command on the bus.  */
                    /* Change the current LIN Channel Status to 'SLEEP' */
                    ChannelStatusPtr->ChStatus = LIN_CH_SLEEP_STATE;
                    LinStatus = LIN_CH_SLEEP;
#if (LIN_CFG_INTERRUPT_ENABLE == STD_ON)
#if (LIN_WAKEUP_SUPPORT == STD_ON)
                    LIN_ENTER_CRITICAL_SECTION(Status);
                    /* \[SWS_Lin_00037] When a LIN channel is in LIN_CH_SLEEP state and wake-up
                    detection is supported by configuration parameter LinChannelWakeupSupport, the 
                    LIN hardware unit shall monitor the bus for a wake-up request on that channel.  */
                    /* Enable wake-up detection interrupt */
                    Lin_WakeupDetect(&(Lin_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx]), TRUE);
                    LIN_EXIT_CRITICAL_SECTION(Status);
#endif /* (LIN_WAKEUP_SUPPORT  \== STD_ON) */
#endif /* (LIN_CFG_INTERRUPT_ENABLE  \== STD_ON) */
                    break;
                }
                default:
                {
                    LIN_ENTER_CRITICAL_SECTION(Status);
                    /* Get Status according to the current LIN channel hardware to determine which 
                       stage the LIN communication is in */
                    LinStatus = Lin_GetChStatus(ChannelStatusPtr, HwUnit);
                    LIN_EXIT_CRITICAL_SECTION(Status);
#if (LIN_CFG_INTERRUPT_ENABLE == STD_OFF)
                    /* Get Error RetStatus and report potential errors based on the current stage 
                       of LIN communication if it exist.*/
                    Lin_IsrMasterErrorHandler(ChannelStatusPtr, ChannelConfigPtr);
                    /* Receive Data */
                    /* \[SWS_Lin_00211]   The complete LIN frame receive processing (including copying 
                    to destination layer) can be implemented in the Lin_GetStatus function. The received 
                    data shall be consistent until either next LIN frame has been received successfully or 
                    LIN channel state has changed.v */
                    Lin_IsrRecvDataHandler(ChannelStatusPtr, ChannelConfigPtr);
#endif /* (LIN_CFG_INTERRUPT_ENABLE  \== STD_OFF) */
                    if (LIN_CH_RX_OK_STATUS == ChannelStatusPtr->ChStatus)
                    {
                        /* Update the 'Lin_SduPtr' when received successfully */
                        /* \[SWS_Lin_00024]   The LIN driver shall make received data available to the LIN 
                        interface module. After successful reception of a whole LIN frame, the received data 
                        shall be prepared for function call of the LIN interface (see Lin_GetStatus). 
                        (SRS_Lin_01555, SRS_Lin_01503) */
                        /* \[SWS_Lin_00092]   If a SDU has been successfully received, the function 
                        Lin_GetStatus shall store the SDU in a shadow buffer or memory mapped LIN 
                        Hardware receive buffer referenced by Lin_SduPtr. The buffer will only be valid and 
                        must be read until the next Lin_SendFrame function call.  */
                        *Lin_SduPtr = ChannelStatusPtr->PduBuffer.SduPtr;
                        LinStatus = LIN_RX_OK;
                    }
                    break;
                }
            }
        }
    }
    /* \[SWS_Lin_00091]   The function Lin_GetStatus shall return the current 
    transmission, reception or operation status of the LIN driver.  */
    return LinStatus;
}

#endif /* (LIN_MASTER_MODE_USED  \== STD_ON) */
#if (LIN_CFG_INTERRUPT_ENABLE == STD_ON)
/****************************************************************************************************
*   Function Name           : Lin_AsiRecv_ISRHandler
*
*   Service ID              : 0xE0.
*
*   Description             : ASI receive interrupt service function.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, LIN_PUBLIC_CODE) Lin_AsiRecv_ISRHandler
(
    Lin_HWUnitType HwUnit
)
{
    uint8                       Channel;
    uint8                       CoreChIdx;
    Mcal_CoreType               CoreId;
    const Lin_ChannelConfigType *ChannelConfigPtr;
    Lin_ChInternalStatusType    *ChannelStatusPtr;
#if (LIN_DEV_ERROR_DETECT == STD_ON)    
    Std_ReturnType           RetStatus;

    if(NULL_PTR == Lin_ConfigPtr)
    {
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_ISR_RECV,
                              LIN_E_CORE_CHANNEL_MISMATCH);
    }
    else if(LIN_MAX_HWUNIT_COUNT <= HwUnit)
    {
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_ISR_RECV,
                              LIN_E_CORE_CHANNEL_MISMATCH);
    }
    else
    {
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
        /* Get core id which is executing currently */
        /* #Violation: Lin_c_REF_5 */
        CoreId = Mcal_GetCoreId(); 
        /* Find the LIN channel according to the HWUnit */
        Channel = Lin_ConfigPtr->HwUnitToChannelIdPtr[HwUnit];

#if (LIN_DEV_ERROR_DETECT == STD_ON)
        RetStatus = Lin_GetDetStatus(CoreId, Channel, LIN_SID_ISR_RECV, NULL_PTR);
        if(E_OK == RetStatus)
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
        {
            /* Find the sub-LIN channel in specified core */
            CoreChIdx = Lin_ConfigPtr->ChannelToCorePtr[Channel];
            /* Load current LIN Channel Status information address */
            ChannelStatusPtr = &(Lin_CoreStatus[CoreId]->ChannelStatusPtr[CoreChIdx]);
            /* load current LIN channel configuration information address */
            ChannelConfigPtr = &(Lin_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx]);

            /**************************************************************
             * Header receiving handler in slave mode
             *************************************************************/
#if ((LIN_CFG_INTERRUPT_ENABLE == STD_ON) && (LIN_SLAVE_MODE_USED == STD_ON))
            if (ASI_LIN_MODE_SLAVE == ChannelConfigPtr->RegisterConfigPtr->mode)
            {
                /* \[SWS_Lin_00272] The LIN driver shall be able to receive a LIN header at any time 
                in LIN_CH_OPERATIONAL state. The header is composed of the break field, synch 
                byte field, and protected identifier byte field */
                if ((LIN_CH_SLEEP_STATE != ChannelStatusPtr->ChStatus) &&
                   (LIN_CH_SLEEP_PENDING != ChannelStatusPtr->ChStatus))
                {
                    Lin_IsrRecvHeaderHandler(ChannelStatusPtr, ChannelConfigPtr);
                }
            }
#endif /* ((LIN_CFG_INTERRUPT_ENABLE == STD_ON) && (LIN_SLAVE_MODE_USED \== STD_ON)) */
            /**************************************************************
             * Data receiving handler
             *************************************************************/
            /* \[SWS_Lin_00060]  The complete LIN frame receive processing (including copying 
            to destination layer) can be implemented in an ISR. The received data shall be 
            consistent until either next LIN frame has been received successfully or LIN channel 
            state has changed. */
            Lin_IsrRecvDataHandler(ChannelStatusPtr, ChannelConfigPtr);

            /**************************************************************
             * Wake-up handler
             *************************************************************/
            Lin_IsrWakeupHandler(ChannelStatusPtr, ChannelConfigPtr);
        }
#if (LIN_DEV_ERROR_DETECT == STD_ON)
    }
#endif /* (LIN_DEV_ERROR_DETECT \== STD_ON) */

}

/****************************************************************************************************
*   Function Name           : Lin_Error_ISRHandler
*
*   Service ID              : 0xE1.
*
*   Description             : ASI error interrupt service function.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, LIN_PUBLIC_CODE) Lin_Error_ISRHandler
(
    Lin_HWUnitType HwUnit
)
{
    uint8                           Channel;
    Mcal_CoreType                   CoreId;
    uint8                           CoreChIdx;
    const Lin_ChannelConfigType     *ChannelConfigPtr;

 #if (LIN_DEV_ERROR_DETECT == STD_ON)    
    Std_ReturnType           RetStatus;
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */

    /* Get core id which is executing currently */
    /* #Violation: Lin_c_REF_5 */
    CoreId = Mcal_GetCoreId(); 
#if (LIN_DEV_ERROR_DETECT == STD_ON)
    if(NULL_PTR == Lin_ConfigPtr)
    {
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_ISR_ERROR,
                              LIN_E_CORE_CHANNEL_MISMATCH);
    }
    else if(LIN_MAX_HWUNIT_COUNT <= HwUnit)
    {
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_ISR_ERROR,
                              LIN_E_CORE_CHANNEL_MISMATCH);
    }
    else
    {
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
        /* Find the LIN channel according to the HWUnit */
        Channel = Lin_ConfigPtr->HwUnitToChannelIdPtr[HwUnit];
#if (LIN_DEV_ERROR_DETECT == STD_ON)
        RetStatus = Lin_GetDetStatus(CoreId, Channel, LIN_SID_ISR_ERROR, NULL_PTR);
        if(E_OK == RetStatus)
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
        {
            /* Find the sub-LIN channel in specified core */
            CoreChIdx = Lin_ConfigPtr->ChannelToCorePtr[Channel];
            ChannelConfigPtr = &(Lin_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx]);
#if (LIN_SLAVE_MODE_USED == STD_ON)
            if (ASI_LIN_MODE_MASTER == ChannelConfigPtr->RegisterConfigPtr->mode)
            {
#endif /* (LIN_SLAVE_MODE_USED  \== STD_ON) */
                Lin_IsrMasterErrorHandler(&(Lin_CoreStatus[CoreId]->
                    ChannelStatusPtr[Lin_ConfigPtr->ChannelToCorePtr[Channel]]), 
                    ChannelConfigPtr);
#if (LIN_SLAVE_MODE_USED == STD_ON)
            }
            else
            {
                Lin_IsrSlaveErrorHandler(&(Lin_CoreStatus[CoreId]->
                    ChannelStatusPtr[Lin_ConfigPtr->ChannelToCorePtr[Channel]]), 
                    ChannelConfigPtr);
            }
#endif /* (LIN_SLAVE_MODE_USED  \== STD_ON) */
        }
#if (LIN_DEV_ERROR_DETECT == STD_ON)
    }
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
}
#if (LIN_SLAVE_MODE_USED == STD_ON)
/****************************************************************************************************
*   Function Name           : Lin_AsiTx_ISRHandler
*
*   Service ID              : 0xE2.
*
*   Description             : ASI transmit interrupt service function.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, LIN_PUBLIC_CODE) Lin_AsiTx_ISRHandler
(
    Lin_HWUnitType HwUnit
)
{
    uint8          Channel;
    Mcal_CoreType  CoreId;
    uint8          CoreChIdx;


 #if (LIN_DEV_ERROR_DETECT == STD_ON)    
    Std_ReturnType           RetStatus;
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */

    /* Get core id which is executing currently */
    /* #Violation: Lin_c_REF_5 */
    CoreId = Mcal_GetCoreId(); 
#if (LIN_DEV_ERROR_DETECT == STD_ON)
    if(NULL_PTR == Lin_ConfigPtr)
    {
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_ISR_TX,
                              LIN_E_CORE_CHANNEL_MISMATCH);
    }
    else if(LIN_MAX_HWUNIT_COUNT <= HwUnit)
    {
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_ISR_TX,
                              LIN_E_CORE_CHANNEL_MISMATCH);
    }
    else
    {
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
        /* Find the LIN channel according to the HWUnit */
        Channel = Lin_ConfigPtr->HwUnitToChannelIdPtr[HwUnit];
#if (LIN_DEV_ERROR_DETECT == STD_ON)
        RetStatus = Lin_GetDetStatus(CoreId, Channel, LIN_SID_ISR_TX, NULL_PTR);
        if(E_OK == RetStatus)
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
        {
            /* Find the sub-LIN channel in specified core */
            CoreChIdx = Lin_ConfigPtr->ChannelToCorePtr[Channel];

            Lin_IsrTxHandler(&(Lin_CoreStatus[CoreId]->
                ChannelStatusPtr[Lin_ConfigPtr->ChannelToCorePtr[Channel]]), 
                &(Lin_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx]));
        }
#if (LIN_DEV_ERROR_DETECT == STD_ON)
    }
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */
}
#endif /* (LIN_SLAVE_MODE_USED  \== STD_ON) */
#endif /* (LIN_CFG_INTERRUPT_ENABLE  \== STD_ON) */

/* #Violation: Lin_c_REF_11*/
#define LIN_STOP_SEC_CODE_ASIL_D_GLOBAL 
/* #Violation: Lin_c_REF_3 */
#include "Lin_MemMap.h" 
/****************************************************************************************************
**                          End of File                                                            **
*****************************************************************************************************/
