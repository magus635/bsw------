/****************************************************************************************************
 *
 ****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Mcu.h
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : RCC,PWRC
 *
 *   brief                 : This file contains all function declarations of Mcu Driver
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
*#Mcu_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*#Mcu_h_REF_2:MISRAC2012-Rule-20.7; 
* Justification: Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*
*#Mcu_h_REF_3:MISRAC2012-Rule-20.1;
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the
*driver must be placed.
*/
#ifndef MCU_H_
#define MCU_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

/* Included for pre-compile options */
#include "Mcu_Cfg.h"
/* To publish the type Mcu_ConfigType */
#include "Mcu_GeneralTypes.h"
/* Included for module version information */
#include "Mcu_Version.h"
#include "Mcu_PBcfg.h"

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
/* Service IDs */
/* Service Id of Mcu_Init API */
#define MCU_INIT_SID               (0x00U)

/* Service Id of Mcu_InitRamSection API */
#define MCU_INITRAMSECTION_SID     (0x01U)

/* Service Id of Mcu_InitClock API */
#define MCU_INITCLOCK_SID          (0x02U)

/* Service Id of Mcu_DistributePllClock API */
#define MCU_DISTRIBUTEPLLCLOCK_SID (0x03U)

/* Service Id of Mcu_GetPllStatus API */
#define MCU_GETPLLSTATUS_SID       (0x04U)

/* Service Id of Mcu_GetResetReason API */
#define MCU_GETRESETREASON_SID     (0x05U)

/* Service Id of Mcu_GetResetRawValue API */
#define MCU_GETRESETRAWVAULE_SID   (0x06U)

/* Service Id of Mcu_PerformReset API */
#define MCU_PERFORMRESET_SID       (0x07U)

/* Service Id of Mcu_SetMode API */
#define MCU_SETMODE_SID            (0x08U)

/* Service Id of Mcu_GetVersionInfo API */
#define MCU_GETVERSIONINFO_SID     (0x09U)

/* Service Id of Mcu_GetRamState API */
/* #Violation: Mcu_h_REF_1*/
#define MCU_GETRAMSTATE_SID        (0x0AU)
#if (MCU_CLR_COLD_RESET_STAT_API == STD_ON)
#define MCU_CLEARCOLDRESETSTATUS_SID  (0x20U)
#endif
/* \[SWS_Mcu_00012]
 *  *Development Errors */

/* DET Code to report NULL pointer passed to Mcu_Init API */
#define MCU_E_PARAM_CONFIG         (0x0AU) /*10U*/

/* DET Code for invalid Clock Setting */
#define MCU_E_PARAM_CLOCK          (0x0BU) /*11U*/

/* DET Code for invalid Operation Mode */
#define MCU_E_PARAM_MODE           (0x0CU) /*12U*/

/* DET Code for invalid RAM Section handle */
#define MCU_E_PARAM_RAMSECTION     (0x0DU) /*13U*/

/* DET Code to report that PLL Clock is not locked */
#define MCU_E_PLL_NOT_LOCKED       (0x0EU) /*14U*/

/* DET code to report uninitialized state */
#define MCU_E_UNINIT               (0x0FU) /*15U*/

/* DET code to report NULL pointer violations */
#define MCU_E_PARAM_POINTER        (0x10U) /*16U*/

/* DET code to report Invalid configuration set selection */
#define MCU_E_INIT_FAILED          (0x11U) /*17U*/

/* extend Error */
#define MCU_E_CORE_MISMATCH        (0xF0U) /*240U*/
#define MCU_E_REG_CHECK_FAIL       (0xF5U) /*245U*/
#if defined(THA6_THA6206D) || defined(THA6_THA6206)
#define MCU_E_CHIP_MISMATCH        (0xF1U) /*241U*/
#endif /* THA6_THA6206D || THA6_THA6206 */

/* runtime error */
/* Mcu_PerformReset fail */
#define MCU_E_RESET_FAILED         (0xF1U) /*241U*/

#define MCU_RESET_RAW_UNDEFINED    (0xFFFFFFFFU)


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
/* #Violation: Mcu_h_REF_1*/
#define MCU_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Mcu_h_REF_3*/
#include "Mcu_MemMap.h"

extern FUNC(void, MCU_CODE) Mcu_Init
(
    P2CONST(Mcu_ConfigType, AUTOMATIC, MCU_CONFIG_DATA) ConfigPtr
);

extern FUNC(Std_ReturnType, MCU_CODE) Mcu_InitRamSection
(
    Mcu_RamSectionType RamSection
);
#if (MCU_INIT_CLOCK == STD_ON)
extern FUNC(Std_ReturnType, MCU_CODE) Mcu_InitClock
(
    Mcu_ClockType ClockSetting
);
#endif /* (MCU_INIT_CLOCK  \== STD_ON) */

#if (MCU_NO_PLL == STD_OFF)
extern FUNC(Std_ReturnType, MCU_CODE) Mcu_DistributePllClock
(
    void
);
#endif /* (MCU_NO_PLL  \== STD_OFF) */

extern FUNC(Mcu_PllStatusType, MCU_CODE) Mcu_GetPllStatus
(
    void
);

extern FUNC(Mcu_ResetType, MCU_PUBLIC_CODE) Mcu_GetResetReason
(
    void
);

extern FUNC(Mcu_RawResetType, MCU_PUBLIC_CODE) Mcu_GetResetRawValue
(
    void
);

#if (MCU_PERFORM_RESET_API == STD_ON)
extern FUNC(void, MCU_PUBLIC_CODE) Mcu_PerformReset
(
    void
);
#endif /* (MCU_PERFORM_RESET_API  \== STD_ON) */

#if (MCU_VERSION_INFO_API == STD_ON)
extern FUNC(void, MCU_CODE) Mcu_GetVersionInfo
(
/* #Violation: Mcu_h_REF_2*/
    P2VAR(Std_VersionInfoType, AUTOMATIC, MCU_APPL_DATA) VersionInfoPtr
);
#endif /* (MCU_VERSION_INFO_API  \== STD_ON) */

extern FUNC(void, MCU_PUBLIC_CODE) Mcu_SetMode
(
    Mcu_ModeType McuMode
);
#if (MCU_GET_RAM_STATE_API == STD_ON)

extern FUNC(Mcu_RamStateType, MCU_PUBLIC_CODE) Mcu_GetRamState
(
    void
);
#endif /* (MCU_GET_RAM_STATE_API  \== STD_ON) */
#if (MCU_CLR_COLD_RESET_STAT_API == STD_ON)

extern FUNC(void, MCU_CODE) Mcu_ClearColdResetStatus
(
    void
);
#endif /* (MCU_CLR_COLD_RESET_STAT_API  \== STD_ON) */

extern FUNC(boolean, MCU_CODE) Mcu_GtmWrapperInit
(
    const Mcu_GtmWrapperConfigType *GTMWrapperConfigPtr
);

/* #Violation: Mcu_h_REF_1*/
#define MCU_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Mcu_h_REF_3*/
#include "Mcu_MemMap.h"

#endif /* MCU_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
