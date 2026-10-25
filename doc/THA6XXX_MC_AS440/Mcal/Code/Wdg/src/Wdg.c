/****************************************************************************************************
 *
 ****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Wdg.c
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : CPUWDT
 *
 *   brief                 : This file contains all functions of Wdg Driver
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
*#Wdg_c_REF_1:MISRAC2012-Dir-4.9;
* Justification: Function like macros are used to reduce code complexity.
*
*#Wdg_c_REF_2:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*#Wdg_c_REF_3:MISRAC2012-Rule-20.1;
* the specification of the sections in which certain parts of the driver must be placed.
*
*#Wdg_c_REF_4:MISRAC2012-Rule-20.10;
* Justification:Use glue operator to construct the exclusive area function name.
*
*#Wdg_c_REF_5:MISRAC2012-Rule-2.1;
* Justification:Reserved API for user access
*
*#Wdg_c_REF_6:MISRAC2012-Rule-11.4;
* Justification:Casting a rigister address to an integral pointer type to obtain it's value.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Wdg.h"
#include "Mcall.h"
#include "Mcall_GeneralTypes.h"
#include "Platform_Types.h"
#include "SchM_Wdg.h"
#include "WdgIf_Types.h"
#include "Wdg_Cfg.h"
#include "sac_hal.h"
#include "Wdg_GeneralTypes.h"
#include "Wdg_Version.h"

#if ((WDG_DISABLE_REJECT_DEM_REPORT == WDG_ENABLE_DEM_REPORT) || \
    (WDG_MODE_FAIL_DEM_REPORT == WDG_ENABLE_DEM_REPORT))
/* DEM header file */
#include "Dem.h"
#endif

#if ((WDG_DEV_ERROR_DETECT == STD_ON) || (WDG_SAFETY_ENABLE == STD_ON))
/* Import of DET functionality */
#include "Det.h"
#endif

/****************************************************************************************************
**                          Version Checks                                                         **
****************************************************************************************************/
#if (WDG_VENDOR_ID != WDG_CFG_VENDOR_ID)
#error "Wdg.c : Mismatch in Vendor ID"
#endif /* (WDG_VENDOR_ID \!= WDG_CFG_VENDOR_ID) */

#if (WDG_MODULE_ID != WDG_CFG_MODULE_ID)
#error "Wdg.c : Mismatch in Module ID"
#endif /* \(WDG_MODULE_ID != WDG_CFG_MODULE_ID) */

#if (WDG_AR_RELEASE_MAJOR_VERSION != WDG_CFG_AR_RELEASE_MAJOR_VERSION)
#error "Wdg.c : Mismatch in Release Major Version"
#endif /* (WDG_AR_RELEASE_MAJOR_VERSION \!= WDG_CFG_AR_RELEASE_MAJOR_VERSION) */
#if (WDG_AR_RELEASE_MINOR_VERSION != WDG_CFG_AR_RELEASE_MINOR_VERSION)
#error "Wdg.c : Mismatch in Release Minor Version"
#endif /* (WDG_AR_RELEASE_MINOR_VERSION \!= WDG_CFG_AR_RELEASE_MINOR_VERSION) */

#if (WDG_AR_RELEASE_REVISION_VERSION != WDG_CFG_AR_RELEASE_REVISION_VERSION)
#error "Wdg.c : Mismatch in Release Revision Version"
#endif /* (WDG_AR_RELEASE_REVISION_VERSION \!= WDG_CFG_AR_RELEASE_REVISION_VERSION) */

#if (WDG_SW_MAJOR_VERSION != WDG_CFG_SW_MAJOR_VERSION)
#error "Wdg.c : Mismatch in Software Major Version"
#endif /* (WDG_SW_MAJOR_VERSION \!= WDG_CFG_SW_MAJOR_VERSION) */

#if (WDG_SW_MINOR_VERSION != WDG_CFG_SW_MINOR_VERSION)
#error "Wdg.c : Mismatch in Software Minor Version"
#endif /* (WDG_SW_MINOR_VERSION \!= WDG_CFG_SW_MINOR_VERSION) */

#if (WDG_SW_PATCH_VERSION != WDG_CFG_SW_PATCH_VERSION)
  #error "Wdg.c : Mismatch in Software Patch Version"
#endif /* (WDG_SW_PATCH_VERSION \!= WDG_CFG_SW_PATCH_VERSION) */
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
/* #Violation: Wdg_c_REF_4 */
#define WDG_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Wdg_##Exclusive_Area()
/* #Violation: Wdg_c_REF_4 */
#define WDG_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Wdg_##Exclusive_Area()

/* Minimum allowed wdt count threshold. */
#define WDG_MINIMUM_COUNT_THRESHOLD       (1U)

/* WDT driver password error, illegal access, unlocking timeout */
#define WDG_HARDWARE_ERROR                (0x20U)
/* Dual bit redundancy error in wdg drive device */
#define WDG_REDUNDANCY_ERROR              (0x26U)
/* Clear error failed */
#define WDG_CLEAR_FAILDED                 (0x36U)
/* Boot core CPU1 */
#define WDG_BOOT_CORE_CPU1                (0xAAU)

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#if defined(WDG_DEVICE0_CONFIGURED)
#if (STD_ON == WDG_DEVICE0_CONFIGURED)
/* #Violation: Wdg_c_REF_2 */
#define WDG_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#include "Wdg_MemMap.h"
/* WDG core0 information */
static Wdg_CoreInformationType Wdg_InformationCore0;
/* #Violation: Wdg_c_REF_2 */
#define WDG_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Wdg_c_REF_3 */
#include "Wdg_MemMap.h"
#endif /* (STD_ON \== WDG_DEVICE0_CONFIGURED) */
#endif /* defined(WDG_DEVICE3_CONFIGURED) */

#if defined(WDG_DEVICE1_CONFIGURED)
#if (STD_ON == WDG_DEVICE1_CONFIGURED)
/* #Violation: Wdg_c_REF_2 */
#define WDG_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Wdg_c_REF_3 */
#include "Wdg_MemMap.h"
/* WDG core1 information */
static Wdg_CoreInformationType Wdg_InformationCore1;
/* #Violation: Wdg_c_REF_2 */
#define WDG_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Wdg_c_REF_3 */
#include "Wdg_MemMap.h"
#endif /* (STD_ON \== WDG_DEVICE1_CONFIGURED) */
#endif /* defined(WDG_DEVICE3_CONFIGURED) */

#if defined(WDG_DEVICE2_CONFIGURED)
#if (STD_ON == WDG_DEVICE2_CONFIGURED)
/* #Violation: Wdg_c_REF_2 */
#define WDG_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Wdg_c_REF_3 */
#include "Wdg_MemMap.h"
/* WDG core2 information */
static Wdg_CoreInformationType Wdg_InformationCore2;
/* #Violation: Wdg_c_REF_2 */
#define WDG_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Wdg_c_REF_3 */
#include "Wdg_MemMap.h"
#endif /* (STD_ON \== WDG_DEVICE2_CONFIGURED) */
#endif /* defined(WDG_DEVICE3_CONFIGURED) */

#if defined(WDG_DEVICE3_CONFIGURED)
#if (STD_ON == WDG_DEVICE3_CONFIGURED)
/* #Violation: Wdg_c_REF_2 */
#define WDG_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Wdg_c_REF_3 */
#include "Wdg_MemMap.h"
/* WDG core3 information */
static Wdg_CoreInformationType Wdg_InformationCore3;
/* #Violation: Wdg_c_REF_2 */
#define WDG_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Wdg_c_REF_3 */
#include "Wdg_MemMap.h"
#endif /* (STD_ON \== WDG_DEVICE3_CONFIGURED) */
#endif /* defined(WDG_DEVICE3_CONFIGURED) */

/* #Violation: Wdg_c_REF_2 */
#define WDG_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Wdg_c_REF_3 */
#include "Wdg_MemMap.h"
static CONSTP2VAR(Wdg_CoreInformationType, WDG_VAR, WDG_APPL_CONST)
    Wdg_CoreStatePtr[MCAL_NUMBER_OF_CORES] =
{
#if defined(WDG_DEVICE0_CONFIGURED)
#if (STD_ON == WDG_DEVICE0_CONFIGURED)
    &Wdg_InformationCore0,
#else
    NULL_PTR,
#endif /* (STD_ON \== WDG_DEVICE0_CONFIGURED) */
#endif /* defined(WDG_DEVICE0_CONFIGURED) */
#if defined(WDG_DEVICE1_CONFIGURED)
#if (STD_ON == WDG_DEVICE1_CONFIGURED)
    &Wdg_InformationCore1,
#else
    NULL_PTR,
#endif /* (STD_ON \== WDG_DEVICE1_CONFIGURED) */
#endif /* defined(WDG_DEVICE1_CONFIGURED) */
#if defined(WDG_DEVICE2_CONFIGURED)
#if (STD_ON == WDG_DEVICE2_CONFIGURED)
    &Wdg_InformationCore2,
#else
    NULL_PTR,
#endif /* (STD_ON \== WDG_DEVICE2_CONFIGURED) */
#endif /* defined(WDG_DEVICE2_CONFIGURED) */
#if defined(WDG_DEVICE3_CONFIGURED)
#if (STD_ON == WDG_DEVICE3_CONFIGURED)
    &Wdg_InformationCore3
#else
    NULL_PTR
#endif /* (STD_ON \== WDG_DEVICE3_CONFIGURED) */
#endif /* defined(WDG_DEVICE3_CONFIGURED) */
};
/* #Violation: Wdg_c_REF_2 */
#define WDG_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Wdg_c_REF_3 */
#include "Wdg_MemMap.h"

/* #Violation: Wdg_c_REF_2 */
#define WDG_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Wdg_c_REF_3 */
#include "Wdg_MemMap.h"

static P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) Wdg_ConfigPtr;

/* #Violation: Wdg_c_REF_2 */
#define WDG_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Wdg_c_REF_3 */
#include "Wdg_MemMap.h"

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
/* #Violation: Wdg_c_REF_2 */
#define WDG_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Wdg_c_REF_3 */
#include "Wdg_MemMap.h"

/****************************************************************************************************
 *   Function Name           : Wdg_CheckAndClrError
 *
 *   Service ID              : None.
 *
 *   Description             : This function shall check if there is a double bit
 *                             redundancy error in the register or Password Error.
 *                             Then clear the error bit.
 *
 *   Parameters in           : void.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : E_OK: Parameter check passed.
 *                             E_NOT_OK: Parameter check failed.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
LOCAL_INLINE FUNC(uint8, WDG_PRIVATE_CODE) Wdg_CheckAndClrError
(
    void
)
{
    Wdg_StatusType WdgStatus;
    uint8          WdgError;
    boolean        RetValue;

    WdgError = E_OK;
    RetValue = TRUE;
    WdgStatus = Cpuwdt_Hal_GetAlarmFlagStatus(CPUWDT_ALARMSTATUSFLAG_PASSWORDERROR);
    if (CPUWDT_STATUS_SET == WdgStatus)
    {
        WdgError = WDG_HARDWARE_ERROR;
        RetValue = Cpuwdt_Hal_ClearFlagStatus(CPUWDT_CLEARSTATUSFLAG_PASSWORDALARM);
    }
    else
    {
        WdgStatus = Cpuwdt_Hal_GetAlarmFlagStatus(CPUWDT_ALARMSTATUSFLAG_REGERROR);
        if (CPUWDT_STATUS_SET == WdgStatus)
        {
            WdgError = WDG_REDUNDANCY_ERROR;
            RetValue = Cpuwdt_Hal_ClearFlagStatus(CPUWDT_CLEARSTATUSFLAG_REGALARM);
        }
    }

    if (FALSE == RetValue)
    {
        WdgError = WDG_CLEAR_FAILDED;
    }

    return WdgError;
}

#if (STD_ON == WDG_DEV_ERROR_DETECT)
/****************************************************************************************************
 *   Function Name           : Wdg_InitDetCheck
 *
 *   Service ID              : None.
 *
 *   Description             : This API returns the Det error of Wdg_Init.
 *
 *   Parameters in           : void.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : E_OK: DET check passed.
 *                             E_NOT_OK: DET check failed.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, WDG_PRIVATE_CODE) Wdg_InitDetCheck
(
    const Wdg_ConfigType* const ConfigPtr, 
    Mcal_CoreType CoreId
)
{
    Std_ReturnType ErrValue;

    ErrValue = E_NOT_OK;
    if (NULL_PTR == ConfigPtr)
    {
        (void)Det_ReportError(WDG_MODULE_ID, WDG_INSTANCE_ID, WDG_SID_INIT, WDG_E_PARAM_POINTER);
    }
    else if (NULL_PTR == ConfigPtr->CoreConfigPtr[CoreId])
    {
        (void)Det_ReportError(WDG_MODULE_ID, WDG_INSTANCE_ID, WDG_SID_INIT, WDG_E_CORE_NOT_CONFIGURED);
    }
    else
    {
        ErrValue = E_OK;
    }

    return ErrValue;
}

/****************************************************************************************************
 *   Function Name           : Wdg_SetModeDetCheck
 *
 *   Service ID              : None.
 *
 *   Description             : This API returns the Det error of Wdg_SetMode.
 *
 *   Parameters in           : void.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : E_OK: DET check passed.
 *                             E_NOT_OK: DET check failed.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, WDG_PRIVATE_CODE) Wdg_SetModeDetCheck
(
    Mcal_CoreType CoreId,
    WdgIf_ModeType Mode
)
{
    Std_ReturnType ErrValue;

    ErrValue = E_NOT_OK;
    if ((WDG_IDLE != Wdg_CoreStatePtr[CoreId]->Wdg_CurrentStatus) || (NULL_PTR == Wdg_ConfigPtr))
    {
        /* Check whether the Wdg module's state is WDG_IDLE. [SWS_Wdg_00035], [SWS_Wdg_00017] */
        (void)Det_ReportError(WDG_MODULE_ID, WDG_INSTANCE_ID, WDG_SID_SETMODE, WDG_E_DRIVER_STATE);
    }
    /* Check if Mode is within allowed range, refer to [SWS_Wdg_00160] */
    else if (WDGIF_FAST_MODE < Mode)
    {
        /* Mode change fail. refer to [SWS_Wdg_00016] */
        (void)Det_ReportError(WDG_MODULE_ID, WDG_INSTANCE_ID, WDG_SID_SETMODE, WDG_E_PARAM_MODE);
    }
    else
    {
        ErrValue = E_OK;
    }

    return ErrValue;
}
#endif /* (WDG_DEV_ERROR_DETECT \== STD_ON) */

/* #Violation: Wdg_c_REF_2 */
#define WDG_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Wdg_c_REF_3 */
#include "Wdg_MemMap.h"

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/* #Violation: Wdg_c_REF_2 */
#define WDG_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Wdg_c_REF_3 */
#include "Wdg_MemMap.h"

/****************************************************************************************************
 *   Function Name           : Wdg_Init
 *
 *   Service ID              : 0x00
 *
 *   Description             : This function shall initialize the Wdg module and watchdog hardwares.
 *
 *   Parameters in           : ConfigPtr: The pointer to configuration set.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : Wdg driver must be uninitialized.
 *
 *   AUTOSAR_Requirement     : SWS_Wdg_00106.
 ****************************************************************************************************/
/* #Violation: Wdg_c_REF_5 */
FUNC(void, WDG_PUBLIC_CODE) Wdg_Init
(
    P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr
)
{
    Mcal_CoreType   CoreId;
    uint8           WdgError;
    boolean         RetValue;
    Sac_CmdExResult RegRetValue;
#if (STD_ON == WDG_DEV_ERROR_DETECT)
    Std_ReturnType  ErrValue;
#endif /* (WDG_DEV_ERROR_DETECT \== STD_ON) */

    RetValue = TRUE;
    /* #Violation: Wdg_c_REF_1 */
    CoreId = Mcal_GetCoreId();
    WdgError = E_NOT_OK;
#if (STD_ON == WDG_DEV_ERROR_DETECT)
    ErrValue = Wdg_InitDetCheck(ConfigPtr, CoreId);
    if (E_OK == ErrValue)
#endif /* (STD_ON \== WDG_DEV_ERROR_DETECT) */
    {
        /* Check if the defaule mode configured is Off-Mode */
        if ((WDGIF_OFF_MODE == ConfigPtr->CoreConfigPtr[CoreId]->DefaultMode) &&
            (FALSE == ConfigPtr->CoreConfigPtr[CoreId]->DisableAllowed))
        /* #Violation: Wdg_c_REF_5 */
        {
#if (WDG_DISABLE_REJECT_DEM_REPORT == WDG_ENABLE_DEM_REPORT)
            /* Disabling of the WatchDog mode failed. [SWS_Wdg_00182], [SWS_Wdg_00025] */
            /* Enable the error flag, as WatchDog Disable is not allowed
               but default mode configured is Off-Mode (WDGIF_OFF_MODE) */
            Dem_SetEventStatus(WDG_E_DISABLE_REJECTED, DEM_EVENT_STATUS_FAILED);
#endif /* (WDG_DISABLE_REJECT_DEM_REPORT \== WDG_ENABLE_DEM_REPORT) */
        }
        else
        {
#if (WDG_DISABLE_REJECT_DEM_REPORT == WDG_ENABLE_DEM_REPORT)
            /* Disabling of the WatchDog mode not failed. [SWS_Wdg_00183] */
            Dem_SetEventStatus(WDG_E_DISABLE_REJECTED, DEM_EVENT_STATUS_PASSED);
#endif /* (WDG_DISABLE_REJECT_DEM_REPORT \== WDG_ENABLE_DEM_REPORT) */
            /* WatchDog Sac init */
            /* Set software alarm1 action to send a reset request */
            /* Enter the critical protection section,
               modify the state machine and operate the CPUWDT hardware unit */
#if (WDG_OVERFLOW_ACTION_RESET == STD_ON)
            /* #Violation: Wdg_c_REF_6 */
            if (MCAL_MASTER_CORE == CoreId)
            {
                WDG_ENTER_CRITICAL_SECTION(Init);
                RetValue = Sac_Hal_SetAlarmAction(SAC_ALARMGROUP_1, SAC_ALARMINDEX_10,
                                                  SAC_ALARMINTERNALACTION_RST, SAC_FIPACTION_NONE);
#if defined(THA6_THA6206D)
                if (NULL_PTR != ConfigPtr->CoreConfigPtr[MCAL_CORE1])
                {
                    RetValue = Sac_Hal_SetAlarmAction(SAC_ALARMGROUP_7, SAC_ALARMINDEX_0,
                                                      SAC_ALARMINTERNALACTION_RST, SAC_FIPACTION_NONE);
                }
#endif

                RegRetValue = Sac_Hal_ActivateRunState();
                /* After modifying the state machine, Exit critical section. */
                WDG_EXIT_CRITICAL_SECTION(Init);
#if (WDG_SAFETY_ENABLE == STD_ON)
                if (SAC_CMDEXRESULT_FAILED == RegRetValue)
                {
                    (void)Det_ReportRuntimeError(WDG_MODULE_ID, WDG_INSTANCE_ID, WDG_SID_INIT,
                                                 WDG_E_REG_CHECK_FAILED);
                }
#else
                MCAL_UNUSED_VAR(RegRetValue);
#endif /* (WDG_SAFETY_ENABLE  \== STD_ON) */
            }
#endif /* (WDG_OVERFLOW_RESET \== STD_ON) */

            /* Initial Wdg hardware and refresh timer */
            /* refer to [SWS_Wdg_00161], [SWS_Wdg_00001] */
            if (TRUE == RetValue)
            {
                RetValue = Cpuwdt_Hal_InitWdt(ConfigPtr->CoreConfigPtr[CoreId]->DeviceConfigPtr);
                if ((TRUE == RetValue) && (WDGIF_OFF_MODE != ConfigPtr->CoreConfigPtr[CoreId]->DefaultMode))
                {
                    /* Wdt enable */
                    RetValue = Cpuwdt_Hal_EnableWdt();
                }
            }

            if (TRUE == RetValue)
            {
                WdgError = Wdg_CheckAndClrError();
            }

            if (E_OK == WdgError)
            {
                /* Save configuration info to local parameter */
                Wdg_ConfigPtr = ConfigPtr;
                Wdg_CoreStatePtr[CoreId]->Wdg_CurrentMode = ConfigPtr->CoreConfigPtr[CoreId]->DefaultMode;
                /* Initialize all global variables. refer to [SWS_Wdg_00100] */
                if (WDGIF_FAST_MODE == ConfigPtr->CoreConfigPtr[CoreId]->DefaultMode)
                {
                    Wdg_CoreStatePtr[CoreId]->Wdg_TriggerConditionTime =
                        (ConfigPtr->CoreConfigPtr[CoreId]->InitialTimeout -
                         ConfigPtr->CoreConfigPtr[CoreId]->TimeBeforeReset) /
                        ConfigPtr->CoreConfigPtr[CoreId]->FastModeRefreshTime;
                }
                /* WDGIF_SLOW_MODE, WDGIF_OFF_MODE */
                else
                {
                    Wdg_CoreStatePtr[CoreId]->Wdg_TriggerConditionTime =
                        (ConfigPtr->CoreConfigPtr[CoreId]->InitialTimeout -
                         ConfigPtr->CoreConfigPtr[CoreId]->TimeBeforeReset) /
                        ConfigPtr->CoreConfigPtr[CoreId]->SlowModeRefreshTime;
                }
#if (WDG_MODE_FAIL_DEM_REPORT == WDG_ENABLE_DEM_REPORT)
                /* Setting of the WatchDog mode not failed. [SWS_Wdg_00181] */
                Dem_SetEventStatus(WDG_E_MODE_FAILED, DEM_EVENT_STATUS_PASSED);
#endif /* (WDG_MODE_FAIL_DEM_REPORT \== WDG_ENABLE_DEM_REPORT) */
#if (STD_ON == WDG_DEV_ERROR_DETECT)
                /* Set the Wdg module's internal state from WDG_UNINIT (the default state
                   indicating a non-initialized module) to WDG_IDLE. Refer to [SWS_Wdg_00019] */
                Wdg_CoreStatePtr[CoreId]->Wdg_CurrentStatus = WDG_IDLE;
#endif /* (STD_ON \== WDG_DEV_ERROR_DETECT) */
            }
            else
            /* #Violation: Wdg_c_REF_5 */
            {
#if (WDG_MODE_FAIL_DEM_REPORT == WDG_ENABLE_DEM_REPORT)
                /* Setting of the WatchDog mode failed. [SWS_Wdg_00180], [SWS_Wdg_00173] */
                Dem_SetEventStatus(WDG_E_MODE_FAILED, DEM_EVENT_STATUS_FAILED);
#endif /* (WDG_MODE_FAIL_DEM_REPORT \== WDG_ENABLE_DEM_REPORT) */
            }
        }
    }
}

/****************************************************************************************************
 *   Function Name           : Wdg_SetMode
 *
 *   Service ID              : 0x01
 *
 *   Description             : This function switches the watchdog into the specified mode.
 *
 *   Parameters in           : Mode: The specified mode that needs to be set.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous
 *
 *   Reentrancy              : Non-Reentrant
 *
 *   Return value            : E_OK: Parameter set successfully.
 *                             E_NOT_OK: Parameter set failed.
 *
 *   Preconditions           : Wdg driver must be initialized.
 *
 *   AUTOSAR_Requirement     : SWS_Wdg_00107.
 ****************************************************************************************************/
/* #Violation: Wdg_c_REF_5 */
FUNC(Std_ReturnType, WDG_PUBLIC_CODE) Wdg_SetMode
(
    WdgIf_ModeType Mode
)
{
    Std_ReturnType ReturnValue;
    Mcal_CoreType  CoreId;
    Std_ReturnType WdgError;
    boolean RetValue;
#if (STD_ON == WDG_DEV_ERROR_DETECT)
    Std_ReturnType  ErrValue;
#endif /* (WDG_DEV_ERROR_DETECT \== STD_ON) */

    /* #Violation: Wdg_c_REF_1 */
    CoreId = Mcal_GetCoreId();
    WdgError = E_NOT_OK;
    ReturnValue = E_NOT_OK;
#if (STD_ON == WDG_DEV_ERROR_DETECT)
    ErrValue = Wdg_SetModeDetCheck(CoreId, Mode);
    if (E_OK == ErrValue)
#endif /* (STD_ON \== WDG_DEV_ERROR_DETECT) */
    {
        /* WDG cannot set off after enable */
        if ((WDGIF_OFF_MODE == Mode) && (FALSE == Wdg_ConfigPtr->CoreConfigPtr[CoreId]->DisableAllowed))
        /* #Violation: Wdg_c_REF_5 */
        {
            /* disabling the watchdog is not allowed. refer to [SWS_Wdg_00026] */
#if (WDG_DISABLE_REJECT_DEM_REPORT == WDG_ENABLE_DEM_REPORT)
            Dem_SetEventStatus(WDG_E_DISABLE_REJECTED, DEM_EVENT_STATUS_FAILED);
#endif /* (WDG_DISABLE_REJECT_DEM_REPORT \== WDG_ENABLE_DEM_REPORT) */
        }
        else
        {
#if (WDG_DISABLE_REJECT_DEM_REPORT == WDG_ENABLE_DEM_REPORT)
            /* Disabling of the WatchDog mode not failed. [SWS_Wdg_00183] */
            Dem_SetEventStatus(WDG_E_DISABLE_REJECTED, DEM_EVENT_STATUS_PASSED);
#endif /* (WDG_DISABLE_REJECT_DEM_REPORT \== WDG_ENABLE_DEM_REPORT) */
            if (Mode != Wdg_CoreStatePtr[CoreId]->Wdg_CurrentMode)
            {
                /* Enter the critical protection section,
                   modify the state machine and operate the CPUWDT hardware unit */
                WDG_ENTER_CRITICAL_SECTION(SetMode);
#if (STD_ON == WDG_DEV_ERROR_DETECT)
                /* watchdog servicing routine set state to WDG_BUSY.
                   refer to [SWS_Wdg_00052], [SWS_Wdg_00018] */
                Wdg_CoreStatePtr[CoreId]->Wdg_CurrentStatus = WDG_BUSY;
#endif /* (STD_ON \== WDG_DEV_ERROR_DETECT) */
                /* Different hardware parameters in different modes. refer to [SWS_Wdg_00051] */
                /* The Wdg_SetMode function shall reset the watchdog timeout counter based on */
                /* the new watchdog mode. refer to [SWS_Wdg_00145] */
                if (WDGIF_FAST_MODE == Mode)
                {
                    if (WDGIF_OFF_MODE == Wdg_CoreStatePtr[CoreId]->Wdg_CurrentMode)
                    {
                        /* The previous status is WDGIF_OFF_MODE */
                        /* Reset the watchdog timeout counter. Timeout = InitialTimeout */
                        Wdg_CoreStatePtr[CoreId]->Wdg_TriggerConditionTime =
                            (Wdg_ConfigPtr->CoreConfigPtr[CoreId]->InitialTimeout -
                             Wdg_ConfigPtr->CoreConfigPtr[CoreId]->TimeBeforeReset) /
                            Wdg_ConfigPtr->CoreConfigPtr[CoreId]->FastModeRefreshTime;
                    }
                    else
                    {
                        /* The previous status is WDGIF_SLOW_MODE */
                        /* Reset the watchdog timeout counter. Timeout = InitialTimeout */
                        Wdg_CoreStatePtr[CoreId]->Wdg_TriggerConditionTime =
                            (Wdg_CoreStatePtr[CoreId]->Wdg_TriggerConditionTime *
                             Wdg_ConfigPtr->CoreConfigPtr[CoreId]->SlowModeRefreshTime) /
                            Wdg_ConfigPtr->CoreConfigPtr[CoreId]->FastModeRefreshTime;
                    }
                    /* Cpuwdt_ChangeHighThv() will disablle cpuwdt count first, the cpuwdt counter
                       will be reset, then change threshold, finally enanle cpuwdt count. */
                    RetValue = Cpuwdt_Hal_ChangeHighThv(
                        Wdg_ConfigPtr->CoreConfigPtr[CoreId]->FastModeRefreshTime,
                        Wdg_ConfigPtr->CoreConfigPtr[CoreId]->DeviceConfigPtr->wdtHighThv1);
                }
                else if (WDGIF_SLOW_MODE == Mode)
                {
                    if (WDGIF_OFF_MODE == Wdg_CoreStatePtr[CoreId]->Wdg_CurrentMode)
                    {
                        /* The previous status is WDGIF_OFF_MODE */
                        /* Reset the watchdog timeout counter */
                        Wdg_CoreStatePtr[CoreId]->Wdg_TriggerConditionTime =
                            (Wdg_ConfigPtr->CoreConfigPtr[CoreId]->InitialTimeout -
                             Wdg_ConfigPtr->CoreConfigPtr[CoreId]->TimeBeforeReset) /
                            Wdg_ConfigPtr->CoreConfigPtr[CoreId]->SlowModeRefreshTime;
                    }
                    else
                    {
                        /* The previous status is WDGIF_FAST_MODE */
                        /* Reset the watchdog timeout counter */
                        Wdg_CoreStatePtr[CoreId]->Wdg_TriggerConditionTime =
                            (Wdg_CoreStatePtr[CoreId]->Wdg_TriggerConditionTime *
                             Wdg_ConfigPtr->CoreConfigPtr[CoreId]->FastModeRefreshTime) /
                            Wdg_ConfigPtr->CoreConfigPtr[CoreId]->SlowModeRefreshTime;
                    }
                    /* Cpuwdt_ChangeHighThv() will disablle cpuwdt count first, the cpuwdt counter
                       will be reset, then change threshold, finally enanle cpuwdt count. */
                    RetValue = Cpuwdt_Hal_ChangeHighThv(
                        Wdg_ConfigPtr->CoreConfigPtr[CoreId]->SlowModeRefreshTime,
                        Wdg_ConfigPtr->CoreConfigPtr[CoreId]->DeviceConfigPtr->wdtHighThv1);
                }
                /* WDGIF_OFF_MODE \== Mode */
                else
                {
                    /* Disable the WDT cnt */
                    RetValue = Cpuwdt_Hal_DisableWdt();
                }
                if (TRUE == RetValue)
                {
                    WdgError = Wdg_CheckAndClrError();
                }
                if (E_OK == WdgError)
                {
#if (WDG_MODE_FAIL_DEM_REPORT == WDG_ENABLE_DEM_REPORT)
                    /* Setting of the WatchDog mode not failed. [SWS_Wdg_00181] */
                    Dem_SetEventStatus(WDG_E_MODE_FAILED, DEM_EVENT_STATUS_PASSED);
#endif /* (WDG_MODE_FAIL_DEM_REPORT \== WDG_ENABLE_DEM_REPORT) */
                    Wdg_CoreStatePtr[CoreId]->Wdg_CurrentMode = Mode;
                    /* return E_OK. refer to [SWS_Wdg_00103] */
                    ReturnValue = E_OK;
                }
                else
                /* #Violation: Wdg_c_REF_5 */
                {
#if (WDG_MODE_FAIL_DEM_REPORT == WDG_ENABLE_DEM_REPORT)
                    /* Setting of the WatchDog mode failed. [SWS_Wdg_00016], [SWS_Wdg_00180] */
                    Dem_SetEventStatus(WDG_E_MODE_FAILED, DEM_EVENT_STATUS_FAILED);
#endif /* (WDG_MODE_FAIL_DEM_REPORT \== WDG_ENABLE_DEM_REPORT) */
                }
#if (STD_ON == WDG_DEV_ERROR_DETECT)
                /* Set state to WDG_IDLE.refer to [SWS_Wdg_00052], [SWS_Wdg_00018] */
                Wdg_CoreStatePtr[CoreId]->Wdg_CurrentStatus = WDG_IDLE;
#endif /* (STD_ON \== WDG_DEV_ERROR_DETECT) */
                /* After modifying the state machine, Exit critical section. */
                WDG_EXIT_CRITICAL_SECTION(SetMode);
            }
            else
            {
                ReturnValue = E_OK;
            }
        }
    }

    return ReturnValue;
}

/****************************************************************************************************
 *   Function Name           : Wdg_SetTriggerCondition
 *
 *   Service ID              : 0x03
 *
 *   Description             : This function sets the timeout value for the trigger counter for the
 *                             Wdg module.
 *
 *   Parameters in           : Timeout: Timeout value (milliseconds) for setting the trigger counter.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous
 *
 *   Reentrancy              : Non-Reentrant
 *
 *   Return value            : None.
 *
 *   Preconditions           : Wdg driver must be initialized.
 *
 *   AUTOSAR_Requirement     : SWS_Wdg_00155.
 ****************************************************************************************************/
/* #Violation: Wdg_c_REF_5 */
FUNC(void, WDG_PUBLIC_CODE) Wdg_SetTriggerCondition
(
    uint16 Timeout
)
{
    Mcal_CoreType CoreId;
    boolean RetValue;
    uint32 FirstLevelTick;
    uint32 TimeoutTick;

    /* #Violation: Wdg_c_REF_1 */
    CoreId = Mcal_GetCoreId();
    RetValue = TRUE;
#if (STD_ON == WDG_DEV_ERROR_DETECT)
    if ((WDG_IDLE != Wdg_CoreStatePtr[CoreId]->Wdg_CurrentStatus) || (NULL_PTR == Wdg_ConfigPtr))
    {
        /* Check whether the Wdg module's state is WDG_IDLE. refer to [SWS_Wdg_00035] */
        (void)Det_ReportError(WDG_MODULE_ID, WDG_INSTANCE_ID, WDG_SID_SETTRIGGERCONDITION,
                              WDG_E_DRIVER_STATE);
    }
    else if (Wdg_ConfigPtr->CoreConfigPtr[CoreId]->MaxTimeout < Timeout)
    {
        /* check that the timeout parameter. refer to [SWS_Wdg_00146] */
        (void)Det_ReportError(WDG_MODULE_ID, WDG_INSTANCE_ID, WDG_SID_SETTRIGGERCONDITION,
                              WDG_E_PARAM_TIMEOUT);
    }
    else
#endif /* (STD_ON \== WDG_DEV_ERROR_DETECT) */
    {
        if (Wdg_CoreStatePtr[CoreId]->Wdg_CurrentMode != WDGIF_OFF_MODE)
        {
            /* Enter the critical protection section,
               modify the state machine and operate the CPUWDT hardware unit */
            WDG_ENTER_CRITICAL_SECTION(SetTriggerCondition);
#if (STD_ON == WDG_DEV_ERROR_DETECT)
            /* Set state to WDG_BUSY. refer to [SWS_Wdg_00052] */
            Wdg_CoreStatePtr[CoreId]->Wdg_CurrentStatus = WDG_BUSY;
#endif /* (STD_ON \== WDG_DEV_ERROR_DETECT) */
            /* timeout is 0, the Wdg driver should immediate reset. refer to [SWS_Wdg_00140] */
            if (0U != Timeout)
            {
                /* Set timeout counter(ms to counter) according to the timeout value passed,
                    refer to [SWS_Wdg_00136], [SWS_Wdg_00138] */
                /* Alculate the remaining timeout counter based on the watchdog mode. */
                TimeoutTick = Wdg_ConfigPtr->CoreConfigPtr[CoreId]->ClockFrequencyKHz * (uint32)Timeout;
                if (TimeoutTick < Wdg_ConfigPtr->CoreConfigPtr[CoreId]->TimeBeforeReset)
                {
                    FirstLevelTick = 0;
                }
                else
                {
                    FirstLevelTick = TimeoutTick - Wdg_ConfigPtr->CoreConfigPtr[CoreId]->TimeBeforeReset;
                }

                if (WDGIF_FAST_MODE == Wdg_CoreStatePtr[CoreId]->Wdg_CurrentMode)
                {
                    /* Consider current mode when calculating counter values. [SWS_Wdg_00139] */
                    Wdg_CoreStatePtr[CoreId]->Wdg_TriggerConditionTime =
                        FirstLevelTick / Wdg_ConfigPtr->CoreConfigPtr[CoreId]->FastModeRefreshTime;
                }
                else
                {
                    /* Consider current mode when calculating counter values. [SWS_Wdg_00139] */
                    Wdg_CoreStatePtr[CoreId]->Wdg_TriggerConditionTime =
                        FirstLevelTick / Wdg_ConfigPtr->CoreConfigPtr[CoreId]->SlowModeRefreshTime;
                }

                /* Trigger watchdog hardware (reset timer). */
                RetValue = Cpuwdt_Hal_ServiceWdt();
            }
            else
            {
                Wdg_CoreStatePtr[CoreId]->Wdg_TriggerConditionTime = 0U;
                /* Reset occurs in the later stage of two cpuwdt cycles. */
                /* Access the hardware directly. refer to [SWS_Wdg_00161] */
                RetValue = Cpuwdt_Hal_ChangeHighThv(WDG_MINIMUM_COUNT_THRESHOLD, WDG_MINIMUM_COUNT_THRESHOLD);
                (void)Wdg_CheckAndClrError();
            }
#if (STD_ON == WDG_DEV_ERROR_DETECT)
            /* Set state to WDG_IDLE. refer to [SWS_Wdg_00052] */
            Wdg_CoreStatePtr[CoreId]->Wdg_CurrentStatus = WDG_IDLE;
#endif /* (STD_ON \== WDG_DEV_ERROR_DETECT) */
            /* After modifying the state machine, Exit critical section. */
            WDG_EXIT_CRITICAL_SECTION(SetTriggerCondition);
#if (STD_ON == WDG_SAFETY_ENABLE)
            if (FALSE == RetValue)
            {
                (void)Det_ReportRuntimeError(WDG_MODULE_ID, WDG_INSTANCE_ID,
                                             WDG_SID_SETTRIGGERCONDITION, WDG_E_REG_CHECK_FAILED);
            }
#endif
        }
    }
}

#if (STD_ON == WDG_VERSION_INFO_API)
/****************************************************************************************************
 *   Function Name           : Wdg_GetVersionInfo
 *
 *   Service ID              : 0x04
 *
 *   Description             : This function returns the Version Information for the WDG module.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : VersionInfoPtr: A pointer to a variable to store version info.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous
 *
 *   Reentrancy              : Reentrant
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Wdg_00109
 ****************************************************************************************************/
/* #Violation: Wdg_c_REF_5 */
FUNC(void, WDG_PUBLIC_CODE) Wdg_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, WDG_APPL_DATA) VersionInfoPtr
)
{
#if (STD_ON == WDG_DEV_ERROR_DETECT)
    if (NULL_PTR == VersionInfoPtr)
    {
        /* refer to [SWS_Wdg_00174] */
        (void)Det_ReportError(
            WDG_MODULE_ID, WDG_INSTANCE_ID, WDG_SID_GETVERSIONINFO, WDG_E_PARAM_POINTER);
    }
    else
#endif /* (STD_ON \== WDG_DEV_ERROR_DETECT) */
    {
        VersionInfoPtr->vendorID = (uint16)WDG_VENDOR_ID;
        VersionInfoPtr->moduleID = (uint16)WDG_MODULE_ID;
        VersionInfoPtr->sw_major_version = (uint8)WDG_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = (uint8)WDG_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = (uint8)WDG_SW_PATCH_VERSION;
    }
}
#endif /* (STD_ON \== WDG_VERSION_INFO_API) */

/****************************************************************************************************
 *   Function Name           : Wdg_RefreshTimer_ISRHandler
 *
 *   Service ID              : 0x10.
 *
 *   Description             : This function is refresh timer interrupt handler.
 *                             The trigger cycle varies under different watch dog modes.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Non-Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Wdg_00166
 ****************************************************************************************************/
FUNC(void, WDG_PUBLIC_CODE) Wdg_RefreshTimer_ISRHandler
(
    void
)
{
    Mcal_CoreType CoreId;
    boolean       RetValue;

    /* The routine servicing an internal watchdog shall be implemented as an interrupt routine */
    /* driven by a hardware timer. [SWS_Wdg_00166] */
    WDG_ENTER_CRITICAL_SECTION(ISRHandler);
    /* #Violation: Wdg_c_REF_1 */
    CoreId = Mcal_GetCoreId();
    /* Clear interrupt bit */
    RetValue = Cpuwdt_Hal_ClearFlagStatus(CPUWDT_CLEARSTATUSFLAG_FIRSTWDTINTERRUPT);
#if (STD_ON == WDG_DEV_ERROR_DETECT)
    if ((WDG_IDLE == Wdg_CoreStatePtr[CoreId]->Wdg_CurrentStatus) && (TRUE == RetValue))
    {
        if (WDGIF_OFF_MODE != Wdg_CoreStatePtr[CoreId]->Wdg_CurrentMode)
        {
#endif /* (STD_ON \== WDG_DEV_ERROR_DETECT) */
            /* If the trigger condition is valid  , feed watchdog. refer to [SWS_Wdg_00144] */
            if (0U != Wdg_CoreStatePtr[CoreId]->Wdg_TriggerConditionTime)
            {
#if (STD_ON == WDG_DEV_ERROR_DETECT)
                /* watchdog servicing routine set state to WDG_BUSY. refer to [SWS_Wdg_00052] */
                Wdg_CoreStatePtr[CoreId]->Wdg_CurrentStatus = WDG_BUSY;
#endif /* (STD_ON \== WDG_DEV_ERROR_DETECT) */
                /* \[SWS_Wdg_00134]If the trigger counter is greater than zero, the watchdog servicing
                   routine shall decrement the trigger counter and trigger the hardware watchdog. */
                Wdg_CoreStatePtr[CoreId]->Wdg_TriggerConditionTime--;
                /* refer to [SWS_Wdg_00161],[SWS_Wdg_00144] */
                RetValue = Cpuwdt_Hal_ServiceWdt();
                (void)Wdg_CheckAndClrError();
#if (STD_ON == WDG_DEV_ERROR_DETECT)
                /* Set state to WDG_BUSY. refer to [SWS_Wdg_00052] */
                Wdg_CoreStatePtr[CoreId]->Wdg_CurrentStatus = WDG_IDLE;
#endif /* (STD_ON \== WDG_DEV_ERROR_DETECT) */
                WDG_EXIT_CRITICAL_SECTION(ISRHandler);
            }
            /* If trigger counter has reached zero, the watchdog servicing
               routine shall do nothing. refer to [SWS_Wdg_00135] */
            else
            {
                WDG_EXIT_CRITICAL_SECTION(ISRHandler);
                if (Wdg_ConfigPtr->CoreConfigPtr[CoreId]->WdgNotificationPtr != NULL_PTR)
                {
                    (Wdg_ConfigPtr->CoreConfigPtr[CoreId]->WdgNotificationPtr)();
                }
            }
#if (STD_ON == WDG_DEV_ERROR_DETECT)
        }
        else
        {
            WDG_EXIT_CRITICAL_SECTION(ISRHandler);
            /* The status is WDGIF_OFF_MODE, but the interrupt is triggered */
            (void)Det_ReportError(WDG_MODULE_ID, WDG_INSTANCE_ID, WDG_SID_REFRESHTIMER_ISRHANDLER,
                                  WDG_E_INT_OFF_MODE);
        }
    }
    else
    {
        WDG_EXIT_CRITICAL_SECTION(ISRHandler);
    }
#endif /* (STD_ON \== WDG_DEV_ERROR_DETECT) */

#if (STD_ON == WDG_SAFETY_ENABLE)
    if (FALSE == RetValue)
    {
        (void)Det_ReportRuntimeError(WDG_MODULE_ID, WDG_INSTANCE_ID, WDG_SID_REFRESHTIMER_ISRHANDLER,
                               WDG_E_REG_CHECK_FAILED);
    }
#endif /* (STD_ON \== WDG_SAFETY_ENABLE) */
}

/****************************************************************************************************
 *   Function Name           : Wdg_GetCurrentTimeout
 *
 *   Service ID              : 0x11.
 *
 *   Description             : This function get the current timeout of wdg notification function.
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
 *   Return value            : The current timeout.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
FUNC(uint16, WDG_PUBLIC_CODE) Wdg_GetCurrentTimeout
(
    void
)
{
    Mcal_CoreType CoreId;
    uint16 Timeout;
    uint32 WdtCounter;
    uint32 RefreshTime;

    /* #Violation: Wdg_c_REF_1 */
    CoreId = Mcal_GetCoreId();
    Timeout = 0;

    WdtCounter = Cpuwdt_Hal_GetWdgCounter();
    if (WDGIF_OFF_MODE != Wdg_CoreStatePtr[CoreId]->Wdg_CurrentMode)
    {
        RefreshTime = (WDGIF_FAST_MODE == Wdg_CoreStatePtr[CoreId]->Wdg_CurrentMode)
                          ? Wdg_ConfigPtr->CoreConfigPtr[CoreId]->FastModeRefreshTime
                          : Wdg_ConfigPtr->CoreConfigPtr[CoreId]->SlowModeRefreshTime;
        if ((Wdg_CoreStatePtr[CoreId]->Wdg_TriggerConditionTime + 1) * RefreshTime > WdtCounter)
        {
            Timeout =
                ((Wdg_CoreStatePtr[CoreId]->Wdg_TriggerConditionTime + 1) * RefreshTime - WdtCounter) /
                Wdg_ConfigPtr->CoreConfigPtr[CoreId]->ClockFrequencyKHz;
        }
    }

    return Timeout;
}
/* #Violation: Wdg_c_REF_2 */
#define WDG_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Wdg_c_REF_3 */
#include "Wdg_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
