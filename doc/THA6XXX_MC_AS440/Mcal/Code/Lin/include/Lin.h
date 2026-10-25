/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Lin.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : ASI
*
*   brief                 : This file contains all type definitions of Lin Driver
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
*#Lin_h_REF_1:MISRAC2012-Rule-20.7;
* Justification: Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*
*#Lin_h_REF_2:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*/

/**************************************************************************************************/
#ifndef LIN_H_
#define LIN_H_
/***************************************************************************************************
*                               Includes
***************************************************************************************************/
#include "Lin_Cfg.h"
#include "Lin_PBcfg.h"
#include "ComStack_Types.h"
#include "Lin_GeneralTypes.h"
#include "Lin_Version.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#if (LIN_DEV_ERROR_DETECT == STD_ON)
/* Error Values */
/* \[SWS_Lin_00048]   The following errors and exceptions shall be detectable by the 
LIN driver depending on its build version (development/production mode)  
(SRS_BSW_00323, SRS_BSW_00327, SRS_BSW_00337, SRS_BSW_00385) */
/* \[SWS_Lin_00214]   The LIN Driver module shall report the default error 
"LIN_E_UNINIT (0x00)", when the API Service is used without module initialization.  */
#define LIN_E_UNINIT                    ((uint8)0x00U)
/* \[SWS_Lin_00215]   The LIN Driver module shall report the default error 
"LIN_E_INVALID_CHANNEL (0x02)", when API Service used with an invalid or 
inactive channel parameter.  */
#define LIN_E_INVALID_CHANNEL           ((uint8)0x02U)
/* \[SWS_Lin_00216]   The LIN Driver module shall report the default error 
"LIN_E_INVALID_POINTER (0x03)", when API Service is called with invalid 
configuration pointer.  */
#define LIN_E_INVALID_POINTER           ((uint8)0x03U)
/* \[SWS_Lin_00213] The LIN Driver module shall report the default error 
"LIN_E_STATE_TRANSITION (0x04)", when Invalid state transition occurs from the 
current state.  */
#define LIN_E_STATE_TRANSITION          ((uint8)0x04U)
/* \[SWS_Lin_00249] The LIN Driver module shall report the default error 
"LIN_E_PARAM_POINTER (0x05)", when API Service is called with a NULL pointer. 
In case of this error, the API service shall return immediately without any further 
action, beside reporting this default error.  */
#define LIN_E_PARAM_POINTER             ((uint8)0x05U)
/* Non-AUTOSAR */
/* Report DET LIN module not configured for current Core */
#define LIN_E_CORE_NOT_CONFIGURED       ((uint8)0xE0U)
/* LIN channel is not allocated to current core */
#define LIN_E_CORE_CHANNEL_MISMATCH     ((uint8)0xE1U)

/* Non-AUTOSAR */
/* SID for LIN interrupt service function(receive interrupt/wakeup interrupt) */
#define LIN_SID_ISR_RECV                ((uint8)0xE0U)
/* SID for LIN interrupt service function(error interrupt) */
#define LIN_SID_ISR_ERROR               ((uint8)0xE1U)
/* SID for LIN interrupt service function(tx interrupt) */
#define LIN_SID_ISR_TX                  ((uint8)0xE2U)
#endif /* (LIN_DEV_ERROR_DETECT  \== STD_ON) */

/* Service IDs */
#define LIN_SID_INIT                    ((uint8)0x00U)
#define LIN_SID_GETVERSIONINFO          ((uint8)0x01U)
#define LIN_SID_SENDFRAME               ((uint8)0x04U)
#define LIN_SID_GOTOSLEEP               ((uint8)0x06U)
#define LIN_SID_WAKEUP                  ((uint8)0x07U)
#define LIN_SID_GETSTATUS               ((uint8)0x08U)
#define LIN_SID_GOTOSLEEPINTERNAL       ((uint8)0x09U)
#define LIN_SID_CHECKWAKEUP             ((uint8)0x0AU)
#define LIN_SID_WAKEUPINTERNAL          ((uint8)0x0BU)

/* Mask for PID to remove Parity bits */
#define LIN_PID_MASK_PARITY                ((uint8)0x3FU)
/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
/* #Violation: Lin_h_REF_2 */
#define LIN_START_SEC_CODE_ASIL_D_GLOBAL
#include "Lin_MemMap.h"

extern FUNC(void, LIN_PUBLIC_CODE) Lin_Init
(
    P2CONST(Lin_ConfigType, AUTOMATIC, LIN_APPL_CONST) ConfigPtr
);

extern FUNC(Std_ReturnType, LIN_PUBLIC_CODE) Lin_CheckWakeup
(
    uint8 Channel
);

#if (LIN_VERSION_INFO_API == STD_ON)
extern FUNC(void, LIN_PUBLIC_CODE) Lin_GetVersionInfo
(
    /* #Violation: Lin_h_REF_1 */
    P2VAR(Std_VersionInfoType, AUTOMATIC, LIN_APPL_DATA) VersionInfoPtr
);
#endif

#if (LIN_MASTER_MODE_USED == STD_ON)
extern FUNC(Std_ReturnType, LIN_PUBLIC_CODE) Lin_SendFrame
(
    uint8 Channel,
    P2CONST(Lin_PduType, AUTOMATIC, LIN_APPL_DATA) PduInfoPtr
);
#endif /* (LIN_MASTER_MODE_USED  \== STD_ON) */

#if (LIN_MASTER_MODE_USED == STD_ON)
extern FUNC(Std_ReturnType, LIN_PUBLIC_CODE) Lin_GoToSleep
(
    uint8 Channel
);
#endif /* (LIN_MASTER_MODE_USED  \== STD_ON) */

extern FUNC(Std_ReturnType, LIN_PUBLIC_CODE) Lin_GoToSleepInternal
(
    uint8 Channel
);

extern FUNC(Std_ReturnType, LIN_PUBLIC_CODE) Lin_Wakeup
(
    uint8 Channel
);

extern FUNC(Std_ReturnType, LIN_PUBLIC_CODE) Lin_WakeupInternal
(
    uint8 Channel
);

#if (LIN_MASTER_MODE_USED == STD_ON)
extern FUNC(Lin_StatusType, LIN_PUBLIC_CODE) Lin_GetStatus
(
    uint8 Channel,
    /* #Violation: Lin_h_REF_1 */
    P2P2VAR(uint8, AUTOMATIC, LIN_APPL_DATA) Lin_SduPtr
);
#endif /* (LIN_MASTER_MODE_USED  \== STD_ON) */

#if (LIN_CFG_INTERRUPT_ENABLE == STD_ON)
extern FUNC(void, LIN_PUBLIC_CODE) Lin_AsiRecv_ISRHandler
(
    Lin_HWUnitType HwUnit
);

extern FUNC(void, LIN_PUBLIC_CODE) Lin_Error_ISRHandler
(
    Lin_HWUnitType HwUnit
);

#if (LIN_SLAVE_MODE_USED == STD_ON)
extern FUNC(void, LIN_PUBLIC_CODE) Lin_AsiTx_ISRHandler
(
    Lin_HWUnitType HwUnit
);
#endif /* (LIN_SLAVE_MODE_USED  \== STD_ON) */
#endif /* (LIN_CFG_INTERRUPT_ENABLE  \== STD_ON) */

/* #Violation: Lin_h_REF_2 */
#define LIN_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Lin_MemMap.h"

#endif /* _LIN_H_ */

/*****************************************************************************************************
**                      End of File
*****************************************************************************************************/
