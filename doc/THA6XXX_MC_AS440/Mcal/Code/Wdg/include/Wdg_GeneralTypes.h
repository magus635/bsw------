/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Wdg_GeneralTypes.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : CPUWDT
*
*   brief                 : This file contains all type definitions of Wdg Driver
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
*#Wdg_GeneralTypes_h_REF_1:MISRAC2012-Dir-4.8;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#Wdg_GeneralTypes_h_REF_2:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*/

#ifndef WDG_GENERALTYPES_H_
#define WDG_GENERALTYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Mcall.h"
#include "cpuwdt_hal.h"
#include "WdgIf_Types.h"

/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
/* Function pointer for Notification */
typedef void (*Wdg_NotifFunctionPtrType)(void);
/* CpuWdt device config */
typedef Cpuwdt_WdtConfig Wdg_DeviceConfigType;
/* CpuWdt device status */
typedef Cpuwdt_Status Wdg_StatusType;

/****************************************************************************************************
**                          Global Enumeration Definitions                                          **
****************************************************************************************************/
typedef enum
{
    WDG_UNINIT = 0U,
    WDG_IDLE,
    WDG_BUSY
} Wdg_StateType;

/****************************************************************************************************
**                          Global Union Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/
/* This type is used to save WDG information of each core */
typedef struct
{
    /* WDG trigger condition time variable. */
    uint32                            Wdg_TriggerConditionTime;
    /* WDG status. */
    Wdg_StateType                     Wdg_CurrentStatus;
    /* WDG current mode. */
    WdgIf_ModeType                    Wdg_CurrentMode;
} Wdg_CoreInformationType;

/* #Violation: Wdg_GeneralTypes_h_REF_1 */
/* #Violation: Wdg_GeneralTypes_h_REF_2 */
typedef struct
{
    /* Wdg device configuration pointer */
    const Wdg_DeviceConfigType *      DeviceConfigPtr;
    /* watchdog servicing routine time in Fast mode (tick) */
    uint32                            FastModeRefreshTime;
    /* watchdog servicing routine time in Slow mode (tick) */
    uint32                            SlowModeRefreshTime;
    /* Initial timeout time (counter) */
    uint32                            InitialTimeout;
    /* Time between notification function call and Reset(tick) */
    uint32                            TimeBeforeReset;
    /* Maximum timeout time (ms) */
    uint32                            MaxTimeout;
    /* Wdg clock frequency (unit:KHz) */
    uint32                            ClockFrequencyKHz;
    /* Wdg notification function */
    Wdg_NotifFunctionPtrType          WdgNotificationPtr;
    /* Initial mode */
    WdgIf_ModeType                    DefaultMode;
    /* Wdg disable allowed */
    boolean                           DisableAllowed;
}Wdg_CoreConfigType;

/* #Violation: Wdg_GeneralTypes_h_REF_2 */
typedef struct
{
    /* The pointer to the core configuration */
    const Wdg_CoreConfigType*         CoreConfigPtr[MCAL_NUMBER_OF_CORES];
}Wdg_ConfigType;
/* refer to [SWS_Wdg_00171] */

#endif/* WDG_GENERALTYPES_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

