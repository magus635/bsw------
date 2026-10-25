/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Wdg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : CPUWDT
*
*   brief                 : This file contains all function declarations of Wdg Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright \(c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/*
*#Violation Summary
*
*#Wdg_h_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*/

#ifndef WDG_H_
#define WDG_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Wdg_GeneralTypes.h"
#include "Wdg_Cfg.h"
#include "Wdg_PBcfg.h"
#include "Mcall.h"
#include "Wdg_Version.h"

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#if (STD_ON == WDG_DEV_ERROR_DETECT)
/* \[SWS_Wdg_00010] */
/* API service used in wrong context (e.g. driver not initialized) */
#define WDG_E_DRIVER_STATE                  (0x10U)
/* API service called with wrong/inconsistent parameter(s) */
#define WDG_E_PARAM_MODE                    (0x11U)
/* API Service called with wrong parameter. */
/* #Violation: Wdg_h_REF_1 */
#define WDG_E_PARAM_CONFIG                  (0x12U)
/* The passed timeout value is higher than the maximum timeout value */
#define WDG_E_PARAM_TIMEOUT                 (0x13U)
/* API is called with wrong pointer value. (e.g. NULL pointer) */
#define WDG_E_PARAM_POINTER                 (0x14U)
/* Invalid configuration set selection */
/* #Violation: Wdg_h_REF_1 */
#define WDG_E_INIT_FAILED                   (0x15U)
/* Non-AUTOSAR */
/* Trigger timer interrupt in WDGIF_OFF_MODE mode */
#define WDG_E_INT_OFF_MODE                  (0x25U)
/* Report DET WDG module not configured for current Core */
#define WDG_E_CORE_NOT_CONFIGURED           (0xE0U)
#endif /* (STD_ON \== WDG_DEV_ERROR_DETECT) */

/* Runtime error */
#define WDG_E_REG_CHECK_FAILED              (0xE1U)


/* API Service ID for Wdg_Init() */
#define WDG_SID_INIT                        (0x00U)
/* API Service ID for Wdg_SetMode() */
#define WDG_SID_SETMODE                     (0x01U)
/* API Service ID for Wdg_SetTriggerCondition() */
#define WDG_SID_SETTRIGGERCONDITION         (0x03U)
/* API Service ID for Wdg_GetVersionInfo() */
#define WDG_SID_GETVERSIONINFO              (0x04U)
/* Service ID for Wdg_RefreshTimer_ISRHandler() */
#define WDG_SID_REFRESHTIMER_ISRHANDLER     (0x10U)

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
/* #Violation: Wdg_h_REF_1 */
#define WDG_START_SEC_CODE_ASIL_D_GLOBAL
#include "Wdg_MemMap.h"

extern FUNC(void, WDG_PUBLIC_CODE) Wdg_Init
(
    P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr
);

extern FUNC(Std_ReturnType, WDG_PUBLIC_CODE) Wdg_SetMode
(
    WdgIf_ModeType Mode
);

extern FUNC(void, WDG_PUBLIC_CODE) Wdg_SetTriggerCondition
(
    uint16 Timeout
);

extern FUNC(void, WDG_PUBLIC_CODE) Wdg_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, WDG_APPL_DATA) VersionInfoPtr
);

extern FUNC(void, WDG_PUBLIC_CODE) Wdg_RefreshTimer_ISRHandler
(
    void
);

extern FUNC(uint16, WDG_PUBLIC_CODE) Wdg_GetCurrentTimeout
(
    void
);
/* #Violation: Wdg_h_REF_1 */
#define WDG_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Wdg_MemMap.h"

#endif /* WDG_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

