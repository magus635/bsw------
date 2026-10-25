/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Wdg_PBCfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : CPUWDT
*
*   brief                 : This file contains all configurations of Wdg Driver
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
*
*#Wdg_PBcfg_c_REF_1:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*#Wdg_PBcfg_c_REF_2:MISRAC2012-Rule-8.9;
* Justification:The value should be placed in the const data sections to reduce code complexity 
* and stack size.
*
*#Wdg_PBcfg_c_REF_3:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts 
* of the driver must be placed.
*
*/


/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Wdg.h"
#include "Wdg_Cfg.h"

/***************************************************************************************************
*                         Function declaration
***************************************************************************************************/

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
/* #Violation: Wdg_PBcfg_c_REF_1 */
#define WDG_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Wdg_PBcfg_c_REF_3 */
#include "Wdg_MemMap.h"
/* CpuWdt0 device configuration. */
static const Wdg_DeviceConfigType Wdg_Device0ConfigSet =
{
    /* WDT password initial value */
    0xA30U,
    /* WDT low threshold value of first dog feeding interval */
    0U,
    /* WDT low threshold value of second dog feeding interval */
    0U,
    /* WDT high threshold value of first dog feeding interval */
    15625U,
    /* WDT high threshold value of second dog feeding interval */
    7812U,
    /* WDT error output mode of first interval */
    CPUWDT_OUTMODE_INTERRUPT,
    /* WDT password generation mode */
    CPUWDT_PWMODE_FIXED,
    /* WDT clock divisor coefficient */
    CPUWDT_CLKDIV_64
};
/* #Violation: Wdg_PBcfg_c_REF_1 */
#define WDG_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Wdg_PBcfg_c_REF_3 */
#include "Wdg_MemMap.h"

/* #Violation: Wdg_PBcfg_c_REF_1 */
#define WDG_START_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Wdg_PBcfg_c_REF_3 */
#include "Wdg_MemMap.h"
/* CpuWdt1 device configuration. */
static const Wdg_DeviceConfigType Wdg_Device1ConfigSet =
{
    /* WDT password initial value */
    0xA30U,
    /* WDT low threshold value of first dog feeding interval */
    0U,
    /* WDT low threshold value of second dog feeding interval */
    0U,
    /* WDT high threshold value of first dog feeding interval */
    7812U,
    /* WDT high threshold value of second dog feeding interval */
    7812U,
    /* WDT error output mode of first interval */
    CPUWDT_OUTMODE_INTERRUPT,
    /* WDT password generation mode */
    CPUWDT_PWMODE_FIXED,
    /* WDT clock divisor coefficient */
    CPUWDT_CLKDIV_64
};
/* #Violation: Wdg_PBcfg_c_REF_1 */
#define WDG_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Wdg_PBcfg_c_REF_3 */
#include "Wdg_MemMap.h"


/* #Violation: Wdg_PBcfg_c_REF_1 */
#define WDG_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Wdg_PBcfg_c_REF_3 */
#include "Wdg_MemMap.h"
/* WDG Core0 configuration. */
static const Wdg_CoreConfigType Wdg_Core0ConfigSet =
{
    /* DeviceConfigPtr */
    &Wdg_Device0ConfigSet,
    /* Fast RefreshTime Counter 0.01s */
    7812U,
    /* Slow RefreshTime Counter 0.02s */
    15625U,
    /* WdgDeviceInitialTimeout(Counter) 10.0s */
    7812500U,
    /* WdgProcessTimeBeforeReset(Counter) 0.01s */
    7812U,
    /* WdgDeviceMaxTimeout(ms) 10.0s */
    10000U,
    /* Wdg clock kHz */
    781U,
    /* WdgNotification */
    NULL_PTR,
    /* DefaultMode */
    WDGIF_SLOW_MODE,
    /* DisableAllowed */
    (boolean)(TRUE)
};
/* #Violation: Wdg_PBcfg_c_REF_1 */
#define WDG_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Wdg_PBcfg_c_REF_3 */
#include "Wdg_MemMap.h"

/* #Violation: Wdg_PBcfg_c_REF_1 */
#define WDG_START_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Wdg_PBcfg_c_REF_3 */
#include "Wdg_MemMap.h"
/* WDG Core1 configuration. */
static const Wdg_CoreConfigType Wdg_Core1ConfigSet =
{
    /* DeviceConfigPtr */
    &Wdg_Device1ConfigSet,
    /* Fast RefreshTime Counter 0.01s */
    7812U,
    /* Slow RefreshTime Counter 0.02s */
    15625U,
    /* WdgDeviceInitialTimeout(Counter) 10.0s */
    7812500U,
    /* WdgProcessTimeBeforeReset(Counter) 0.01s */
    7812U,
    /* WdgDeviceMaxTimeout(ms) 10.0s */
    10000U,
    /* Wdg clock kHz */
    781U,
    /* WdgNotification */
    NULL_PTR,
    /* DefaultMode */
    WDGIF_FAST_MODE,
    /* DisableAllowed */
    (boolean)(FALSE)
};
/* #Violation: Wdg_PBcfg_c_REF_1 */
#define WDG_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Wdg_PBcfg_c_REF_3 */
#include "Wdg_MemMap.h"


/* #Violation: Wdg_PBcfg_c_REF_1 */
#define WDG_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Wdg_PBcfg_c_REF_3 */
#include "Wdg_MemMap.h"
/* WDG module initialization routine for configuration. */
/* #Violation: Wdg_PBcfg_c_REF_2 */

const Wdg_ConfigType Wdg_ConfigSet[WDG_CONFIG_COUNT] =
{
    {
        {
            &Wdg_Core0ConfigSet,
            &Wdg_Core1ConfigSet
        }
    }
};
/* #Violation: Wdg_PBcfg_c_REF_1 */
#define WDG_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Wdg_PBcfg_c_REF_3 */
#include "Wdg_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
