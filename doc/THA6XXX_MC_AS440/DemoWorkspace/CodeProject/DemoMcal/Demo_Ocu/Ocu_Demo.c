/****************************************************************************************************
 *
 ****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Ocu_Demo.c
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : GTM-ATOM
 *
 *   brief                 : This file contains Demo application for Ocu Driver
 *
 *   Autosar Version       : 4.4.0
 *
 *   Build Version         : Cortex-R52+/THA6xxx
 *
 *   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
 *
 ****************************************************************************************************/

/****************************************************************************************************
 **                          Includes                                                               **
 ****************************************************************************************************/
#include "Demo_Common.h"
#include "Ocu_Demo.h"
#include "ComStack_Types.h"
#include "Ocu_GeneralTypes.h"
#include "Ocu.h"
#include "Ocu_Irq.h"
#include "Intc.h"
#include "Dio.h"
#include "Ocu_Version.h"

/****************************************************************************************************
 **                          Private Macro Definitions                                              **
 ****************************************************************************************************/
#define OCU_CHANNEL_DEFAULT_THRESHOLD    (1000U)
typedef volatile struct
{
    uint8 CoreCmdExist; /* This variable can only be changed by Core0(master) */
    uint8 CoreExeCmd;
} CoreExeType;

#define OcuConf_OcuChannel_OcuChannel_0                              ((Ocu_ChannelType)0U)
#define OcuConf_OcuChannel_OcuChannel_1                              ((Ocu_ChannelType)1U)
#define OcuConf_OcuChannel_OcuChannel_2                              ((Ocu_ChannelType)2U)
#define OcuConf_OcuChannel_OcuChannel_3                              ((Ocu_ChannelType)3U)

/****************************************************************************************************
 **                          Private Variable Definitions                                           **
 ****************************************************************************************************/
#define OCU_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Ocu_MemMap.h"
/****************************************************************************************************
 **                          Global Variable Definitions                                            **
 ****************************************************************************************************/
static volatile uint32 Channel00_NotificationNumber;
static volatile uint32 Channel02_NotificationNumber;
static volatile uint32 Channel01_NotificationNumber;
static volatile uint32 Channel03_NotificationNumber;

static uint8 Ocu_DemoCoreSelFlg;
static CoreExeType OcuCoreExeFlag;
static uint8 Ocu_DemoCoreInitStatus[MCAL_NUMBER_OF_CORES];

#define OCU_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Ocu_MemMap.h"


/****************************************************************************************************
 **                          Private Constant Definitions                                           **
 ****************************************************************************************************/

/****************************************************************************************************
 **                          Global Constant Definitions                                            **
 ****************************************************************************************************/

/****************************************************************************************************
 **                          Private Function Declarations                                          **
 ****************************************************************************************************/
#define OCU_START_SEC_CODE_ASIL_D_GLOBAL
#include "Ocu_MemMap.h"

/****************************************************************************************************
 **                          Private Function Definitions                                           **
 ****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : Ocu_GetOutputLevel
*
*   Service ID              : None.
*
*   Description             : API is used to get the output level of ocu channel.
*
*   Parameters in           : Channel: Logic channel number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant
*
*   Return value            : None
*
*   Preconditions           : None
*
****************************************************************************************************/
static Gtm_SignalState Ocu_GetOutputLevel(uint32 Channel)
{
    GTM_OBP DevPtr;
    Gtm_SignalState Level;
    uint8 HWConfigIndex;
    const Gtm_Output_Driver *Ocu_GtmTimerIndexPtr;


    HWConfigIndex = Ocu_ConfigSet[0].OcuChannelIdxmapPtr[Channel].HWCfgIndex;

    Ocu_GtmTimerIndexPtr = &Ocu_ConfigSet[0].Ocu_HWGtmAtomConfigPtr[HWConfigIndex].HWChannelIndex;

    DevPtr = Gtm_Atom_Std_GetAtomPointer(Ocu_GtmTimerIndexPtr->moduleIndex);

    Level = Gtm_Atom_Std_GetOutputLevel(DevPtr, Ocu_GtmTimerIndexPtr->channel);

    return Level;
}

/****************************************************************************************************
*   Function Name           : Ocu_CompareMatchPinByAbsoluteThreshold
*
*   Service ID              : None.
*
*   Description             : Example of pin event generated by Ocu absolute 
*                             threshold matching event.
*                             Pin level can be observed by pin(Core0 P10.7/Core1 P14.0)
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : None
*
****************************************************************************************************/
void Ocu_PinByAbsoluteThresholdDemo0
(
    void
)
{
    Mcal_CoreType CoreId;
    uint32 ChannelId;
    Ocu_ValueType CounterValue;
    Ocu_ReturnType RetStatus;
    uint32 Status;
    Gtm_SignalState SignalLevel;
    Gtm_SignalState SignalLevel1;

    Status = 0U;

    CoreId = Mcal_GetCoreId();

    if (MCAL_CORE0 == CoreId)
    {
        ChannelId = 0U;
        Channel00_NotificationNumber = 0U;
    }
    else
    {
        ChannelId = 2U;
        Channel02_NotificationNumber = 0U;
    }

    /* Enable OCU channel notifications */
    Ocu_EnableNotification(ChannelId);
    /* Start the channel */
    Ocu_StartChannel(ChannelId);

    /* Set absolute compare match value, which is generated after CounterValue of
     * 2000ticks(2ms in this demo) */
    CounterValue = Ocu_GetCounter(ChannelId);
    RetStatus = Ocu_SetAbsoluteThreshold(ChannelId, CounterValue, (CounterValue + 2000U));
    /* Set channel pin action when compare match event generated */
    Ocu_SetPinAction(ChannelId, OCU_SET_LOW);

    /* 2ms is enough for Ocu_SetAbsoluteThreshold to set new compare value ,
     * writing must be in the interval */
    if (OCU_CM_IN_REF_INTERVAL != RetStatus)
    {
        Status++;
    }

    Timer_DelayMs(2);

    if ((MCAL_CORE0 == CoreId) && (0U == Channel00_NotificationNumber))
    {
        Status++;
    }
    else if ((MCAL_CORE1 == CoreId) && (0U == Channel02_NotificationNumber))
    {
        Status++;
    }
    else
    {
        Channel00_NotificationNumber = 0U;
        Channel02_NotificationNumber = 0U;
    }

    SignalLevel = Ocu_GetOutputLevel(ChannelId);

    if (GTM_SIGNALSTATE_LOW == SignalLevel)
    {
        DEBUG_PRINTF("Result: Passed!\r\n");
    }
    else
    {
        DEBUG_PRINTF("Result: Failed!\r\n");
        Status++;
    }

    /* Set absolute compare match value, which is generated after CounterValue of
     * 2000ticks(2ms in this demo) */
    CounterValue = Ocu_GetCounter(ChannelId);
    RetStatus = Ocu_SetAbsoluteThreshold(ChannelId, CounterValue, (CounterValue + 2000U));
    /* Set channel pin action when compare match event generated */
    Ocu_SetPinAction(ChannelId, OCU_SET_HIGH);

    /* 2ms is enough for Ocu_SetAbsoluteThreshold to set new compare value ,
     * writing must be in the interval */
    if (OCU_CM_IN_REF_INTERVAL != RetStatus)
    {
        Status++;
    }

    Timer_DelayMs(2);

    if ((MCAL_CORE0 == CoreId) && (0U == Channel00_NotificationNumber))
    {
        Status++;
    }
    else if ((MCAL_CORE1 == CoreId) && (0U == Channel02_NotificationNumber))
    {
        Status++;
    }
    else
    {
        Channel00_NotificationNumber = 0U;
        Channel02_NotificationNumber = 0U;
    }

    SignalLevel = Ocu_GetOutputLevel(ChannelId);

    if (GTM_SIGNALSTATE_HIGH == SignalLevel)
    {
        DEBUG_PRINTF("Result: Passed!\r\n");
    }
    else
    {
        DEBUG_PRINTF("Result: Failed!\r\n");
    }

    SignalLevel = Ocu_GetOutputLevel(ChannelId);
    /* Set absolute compare match value, which is generated after CounterValue of
     * 2000ticks(2ms in this demo) */
    CounterValue = Ocu_GetCounter(ChannelId);
    RetStatus = Ocu_SetAbsoluteThreshold(ChannelId, CounterValue, (CounterValue + 2000U));
    /* Set channel pin action when compare match event generated */
    Ocu_SetPinAction(ChannelId, OCU_TOGGLE);

    /* 2ms is enough for Ocu_SetAbsoluteThreshold to set new compare value ,
     * writing must be in the interval */
    if (OCU_CM_IN_REF_INTERVAL != RetStatus)
    {
        Status++;
    }

    Timer_DelayMs(2);

    if ((MCAL_CORE0 == CoreId) && (0U == Channel00_NotificationNumber))
    {
        Status++;
    }
    else if ((MCAL_CORE1 == CoreId) && (0U == Channel02_NotificationNumber))
    {
        Status++;
    }
    else
    {
        Channel00_NotificationNumber = 0U;
        Channel02_NotificationNumber = 0U;
    }

    SignalLevel1 = Ocu_GetOutputLevel(ChannelId);

    if (SignalLevel1 == SignalLevel)
    {
        Status++;
    }

    Ocu_StopChannel(ChannelId);

    if (0U == Status)
    {
        DEBUG_PRINTF("Result: Passed!\r\n");
    }
    else
    {
        DEBUG_PRINTF("Result: Failed!\r\n");
        Status++;
    }
}

/****************************************************************************************************
*   Function Name           : Ocu_PinByAbsoluteThresholdDemo1
*
*   Service ID              : None.
*
*   Description             : Example of pin event generated by Ocu absolute
*                             threshold matching event.
*                             Pin level can be observed by pin(Core0 P33.4/Core1 P33.8)
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : None
*
****************************************************************************************************/
void Ocu_PinByAbsoluteThresholdDemo1
(
    void
)
{
    Mcal_CoreType CoreId;
    uint32 ChannelId;
    Ocu_ValueType CounterValue;
    Ocu_ReturnType RetStatus;
    uint32 Status;
    Gtm_SignalState SignalLevel;
    Gtm_SignalState SignalLevel1;

    Status = 0U;

    CoreId = Mcal_GetCoreId();

    if (MCAL_CORE0 == CoreId)
    {
        ChannelId = 0U;
        Channel00_NotificationNumber = 0U;
    }
    else
    {
        ChannelId = 2U;
        Channel02_NotificationNumber = 0U;
    }

    /* Enable OCU channel notifications */
    Ocu_EnableNotification(ChannelId);
    /* Set channel pin action when compare match event generated */
    Ocu_SetPinAction(ChannelId, OCU_SET_LOW);
    /* Start the channel */
    Ocu_StartChannel(ChannelId);
    /* Set absolute compare match value, which is generated after CounterValue of
     * 2000ticks(2ms in this demo) */
    CounterValue = Ocu_GetCounter(ChannelId);
    RetStatus = Ocu_SetAbsoluteThreshold(ChannelId, CounterValue, (CounterValue + 2000U));

    /* 2ms is enough for Ocu_SetAbsoluteThreshold to set new compare value ,
     * writing must be in the interval */
    if (OCU_CM_IN_REF_INTERVAL != RetStatus)
    {
        Status++;
    }

    Timer_DelayMs(2);

    if ((MCAL_CORE0 == CoreId) && (0U == Channel00_NotificationNumber))
    {
        Status++;
    }
    else if ((MCAL_CORE1 == CoreId) && (0U == Channel02_NotificationNumber))
    {
        Status++;
    }
    else
    {
        Channel00_NotificationNumber = 0U;
        Channel02_NotificationNumber = 0U;
    }

    SignalLevel = Ocu_GetOutputLevel(ChannelId);

    if (GTM_SIGNALSTATE_LOW == SignalLevel)
    {
        DEBUG_PRINTF("Result: Passed!\r\n");
    }
    else
    {
        DEBUG_PRINTF("Result: Failed!\r\n");
        Status++;
    }

    /* Set absolute compare match value, which is generated after CounterValue of
     * 2000ticks(2ms in this demo) */
    /* Set channel pin action when compare match event generated */
    Ocu_SetPinAction(ChannelId, OCU_SET_HIGH);
    CounterValue = Ocu_GetCounter(ChannelId);
    RetStatus = Ocu_SetAbsoluteThreshold(ChannelId, CounterValue, (CounterValue + 2000U));
    /* 2ms is enough for Ocu_SetAbsoluteThreshold to set new compare value ,
     * writing must be in the interval */
    if (OCU_CM_IN_REF_INTERVAL != RetStatus)
    {
        Status++;
    }

    Timer_DelayMs(2);

    if ((MCAL_CORE0 == CoreId) && (0U == Channel00_NotificationNumber))
    {
        Status++;
    }
    else if ((MCAL_CORE1 == CoreId) && (0U == Channel02_NotificationNumber))
    {
        Status++;
    }
    else
    {
        Channel00_NotificationNumber = 0U;
        Channel02_NotificationNumber = 0U;
    }

    SignalLevel = Ocu_GetOutputLevel(ChannelId);

    if (GTM_SIGNALSTATE_HIGH == SignalLevel)
    {
        DEBUG_PRINTF("Result: Passed!\r\n");
    }
    else
    {
        DEBUG_PRINTF("Result: Failed!\r\n");
        Status++;
    }

    SignalLevel = Ocu_GetOutputLevel(ChannelId);
    /* Set absolute compare match value, which is generated after CounterValue of
     * 2000ticks(2ms in this demo) */
    CounterValue = Ocu_GetCounter(ChannelId);
    RetStatus = Ocu_SetAbsoluteThreshold(ChannelId, CounterValue, (CounterValue + 2000U));
    /* Set channel pin action when compare match event generated */
    Ocu_SetPinAction(ChannelId, OCU_TOGGLE);

    /* 2ms is enough for Ocu_SetAbsoluteThreshold to set new compare value ,
     * writing must be in the interval */
    if (OCU_CM_IN_REF_INTERVAL != RetStatus)
    {
        Status++;
    }

    Timer_DelayMs(2);

    if ((MCAL_CORE0 == CoreId) && (0U == Channel00_NotificationNumber))
    {
        Status++;
    }
    else if ((MCAL_CORE1 == CoreId) && (0U == Channel02_NotificationNumber))
    {
        Status++;
    }
    else
    {
        Channel00_NotificationNumber = 0U;
        Channel02_NotificationNumber = 0U;
    }

    SignalLevel1 = Ocu_GetOutputLevel(ChannelId);

    if (SignalLevel1 == SignalLevel)
    {
        Status++;
    }

    Ocu_StopChannel(ChannelId);

    if (0U == Status)
    {
        DEBUG_PRINTF("Result: Passed!\r\n");
    }
    else
    {
        DEBUG_PRINTF("Result: Failed!\r\n");
    }
}

/****************************************************************************************************
*   Function Name           : Ocu_PinByRelativeThresholdDemo0
*
*   Service ID              : None.
*
*   Description             : Example of pin event generated by Ocu relative 
*                             threshold matching event.
*                             Pin level can be observed by pin(Core0 P10.7/Core1 P14.0)
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : None
*
****************************************************************************************************/
void Ocu_PinByRelativeThresholdDemo0
(
    void
)
{
    Mcal_CoreType CoreId;
    uint32 ChannelId;
    Ocu_ReturnType RetStatus;
    uint32 Status;
    Gtm_SignalState SignalLevel;
    Gtm_SignalState SignalLevel1;

    Status = 0U;

    CoreId = Mcal_GetCoreId();

    if (MCAL_CORE0 == CoreId)
    {
        ChannelId = 0U;
        Channel00_NotificationNumber = 0U;
    }
    else
    {
        ChannelId = 2U;
        Channel02_NotificationNumber = 0U;
    }

    /* Enable OCU channel notifications */
    Ocu_EnableNotification(ChannelId);
    /* Start the channel */
    Ocu_StartChannel(ChannelId);

    /* Set absolute compare match value, which is generated after CounterValue of
     * 2000ticks(2ms in this demo) */
    RetStatus = Ocu_SetRelativeThreshold(ChannelId, 2000U);
    /* Set channel pin action when compare match event generated */
    Ocu_SetPinAction(ChannelId, OCU_SET_LOW);

    /* 2ms is enough for Ocu_SetAbsoluteThreshold to set new compare value ,
     * writing must be in the interval */
    if (OCU_CM_IN_REF_INTERVAL != RetStatus)
    {
        Status++;
    }

    Timer_DelayMs(2);

    if ((MCAL_CORE0 == CoreId) && (0U == Channel00_NotificationNumber))
    {
        Status++;
    }
    else if ((MCAL_CORE1 == CoreId) && (0U == Channel02_NotificationNumber))
    {
        Status++;
    }
    else
    {
        Channel00_NotificationNumber = 0U;
        Channel02_NotificationNumber = 0U;
    }

    SignalLevel = Ocu_GetOutputLevel(ChannelId);

    if (GTM_SIGNALSTATE_LOW == SignalLevel)
    {
        DEBUG_PRINTF("Result: Passed!\r\n");
    }
    else
    {
        DEBUG_PRINTF("Result: Failed!\r\n");
    }

    /* Set absolute compare match value, which is generated after CounterValue of
     * 2000ticks(2ms in this demo) */
    RetStatus = Ocu_SetRelativeThreshold(ChannelId, 2000U);
    /* Set channel pin action when compare match event generated */
    Ocu_SetPinAction(ChannelId, OCU_SET_HIGH);

    /* 2ms is enough for Ocu_SetAbsoluteThreshold to set new compare value ,
     * writing must be in the interval */
    if (OCU_CM_IN_REF_INTERVAL != RetStatus)
    {
        Status++;
    }

    Timer_DelayMs(2);

    if ((MCAL_CORE0 == CoreId) && (0U == Channel00_NotificationNumber))
    {
        Status++;
    }
    else if ((MCAL_CORE1 == CoreId) && (0U == Channel02_NotificationNumber))
    {
        Status++;
    }
    else
    {
        Channel00_NotificationNumber = 0U;
        Channel02_NotificationNumber = 0U;
    }

    SignalLevel = Ocu_GetOutputLevel(ChannelId);

    if (GTM_SIGNALSTATE_HIGH == SignalLevel)
    {
        DEBUG_PRINTF("Result: Passed!\r\n");
    }
    else
    {
        DEBUG_PRINTF("Result: Failed!\r\n");
    }

    /* Set absolute compare match value, which is generated after CounterValue of
     * 2000ticks(2ms in this demo) */
    RetStatus = Ocu_SetRelativeThreshold(ChannelId, 2000U);
    /* Set channel pin action when compare match event generated */
    Ocu_SetPinAction(ChannelId, OCU_SET_HIGH);

    /* 2ms is enough for Ocu_SetAbsoluteThreshold to set new compare value ,
     * writing must be in the interval */
    if (OCU_CM_IN_REF_INTERVAL != RetStatus)
    {
        Status++;
    }

    Timer_DelayMs(2);

    if ((MCAL_CORE0 == CoreId) && (0U == Channel00_NotificationNumber))
    {
        Status++;
    }
    else if ((MCAL_CORE1 == CoreId) && (0U == Channel02_NotificationNumber))
    {
        Status++;
    }
    else
    {
        Channel00_NotificationNumber = 0U;
        Channel02_NotificationNumber = 0U;
    }

    SignalLevel = Ocu_GetOutputLevel(ChannelId);

    if (GTM_SIGNALSTATE_HIGH == SignalLevel)
    {
        DEBUG_PRINTF("Result: Passed!\r\n");
    }
    else
    {
        DEBUG_PRINTF("Result: Failed!\r\n");
    }

    SignalLevel = Ocu_GetOutputLevel(ChannelId);
    /* Set absolute compare match value, which is generated after CounterValue of
     * 2000ticks(2ms in this demo) */
    RetStatus = Ocu_SetRelativeThreshold(ChannelId, 2000U);
    /* Set channel pin action when compare match event generated */
    Ocu_SetPinAction(ChannelId, OCU_TOGGLE);

    /* 2ms is enough for Ocu_SetAbsoluteThreshold to set new compare value ,
     * writing must be in the interval */
    if (OCU_CM_IN_REF_INTERVAL != RetStatus)
    {
        Status++;
    }

    Timer_DelayMs(2);

    if ((MCAL_CORE0 == CoreId) && (0U == Channel00_NotificationNumber))
    {
        Status++;
    }
    else if ((MCAL_CORE1 == CoreId) && (0U == Channel02_NotificationNumber))
    {
        Status++;
    }
    else
    {
        Channel00_NotificationNumber = 0U;
        Channel02_NotificationNumber = 0U;
    }

    SignalLevel1 = Ocu_GetOutputLevel(ChannelId);

    if (SignalLevel1 == SignalLevel)
    {
        Status++;
    }

    if (0U == Status)
    {
        DEBUG_PRINTF("Result: Passed!\r\n");
    }
    else
    {
        DEBUG_PRINTF("Result: Failed!\r\n");
    }

    Ocu_DisableNotification(ChannelId);
    Ocu_StopChannel(ChannelId);
}

/****************************************************************************************************
*   Function Name           : Ocu_PinByRelativeThresholdDemo1
*
*   Service ID              : None.
*
*   Description             : Example of pin event generated by Ocu relative
*                             threshold matching event.
*                             Pin level can be observed by pin(Core0 P33.4/Core1 P33.8)
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : None
*
****************************************************************************************************/
void Ocu_PinByRelativeThresholdDemo1
(
    void
)
{
    Mcal_CoreType CoreId;
    uint32 ChannelId;
    Ocu_ReturnType RetStatus;
    uint32 Status;
    Gtm_SignalState SignalLevel;
    Gtm_SignalState SignalLevel1;

    Status = 0U;

    CoreId = Mcal_GetCoreId();

    if (MCAL_CORE0 == CoreId)
    {
        ChannelId = 0U;
        Channel00_NotificationNumber = 0U;
    }
    else
    {
        ChannelId = 2U;
        Channel02_NotificationNumber = 0U;
    }

    /* Enable OCU channel notifications */
    Ocu_EnableNotification(ChannelId);
    /* Start the channel */
    Ocu_StartChannel(ChannelId);

    /* Set absolute compare match value, which is generated after CounterValue of
     * 2000ticks(2ms in this demo) */
    RetStatus = Ocu_SetRelativeThreshold(ChannelId, 2000U);
    /* Set channel pin action when compare match event generated */
    Ocu_SetPinAction(ChannelId, OCU_SET_LOW);

    /* 2ms is enough for Ocu_SetAbsoluteThreshold to set new compare value ,
     * writing must be in the interval */
    if (OCU_CM_IN_REF_INTERVAL != RetStatus)
    {
        Status++;
    }

    Timer_DelayMs(2);

    if ((MCAL_CORE0 == CoreId) && (0U == Channel00_NotificationNumber))
    {
        Status++;
    }
    else if ((MCAL_CORE1 == CoreId) && (0U == Channel02_NotificationNumber))
    {
        Status++;
    }
    else
    {
        Channel00_NotificationNumber = 0U;
        Channel02_NotificationNumber = 0U;
    }

    SignalLevel = Ocu_GetOutputLevel(ChannelId);

    if (GTM_SIGNALSTATE_LOW == SignalLevel)
    {
        DEBUG_PRINTF("Result: Passed!\r\n");
    }
    else
    {
        DEBUG_PRINTF("Result: Failed!\r\n");
    }

    /* Set absolute compare match value, which is generated after CounterValue of
     * 2000ticks(2ms in this demo) */
    RetStatus = Ocu_SetRelativeThreshold(ChannelId, 2000U);
    /* Set channel pin action when compare match event generated */
    Ocu_SetPinAction(ChannelId, OCU_SET_HIGH);

    /* 2ms is enough for Ocu_SetAbsoluteThreshold to set new compare value ,
     * writing must be in the interval */
    if (OCU_CM_IN_REF_INTERVAL != RetStatus)
    {
        Status++;
    }

    Timer_DelayMs(2);

    if ((MCAL_CORE0 == CoreId) && (0U == Channel00_NotificationNumber))
    {
        Status++;
    }
    else if ((MCAL_CORE1 == CoreId) && (0U == Channel02_NotificationNumber))
    {
        Status++;
    }
    else
    {
        Channel00_NotificationNumber = 0U;
        Channel02_NotificationNumber = 0U;
    }

    SignalLevel = Ocu_GetOutputLevel(ChannelId);

    if (GTM_SIGNALSTATE_HIGH == SignalLevel)
    {
        DEBUG_PRINTF("Result: Passed!\r\n");
    }
    else
    {
        DEBUG_PRINTF("Result: Failed!\r\n");
    }

    /* Set absolute compare match value, which is generated after CounterValue of
     * 2000ticks(2ms in this demo) */
    RetStatus = Ocu_SetRelativeThreshold(ChannelId, 2000U);
    /* Set channel pin action when compare match event generated */
    Ocu_SetPinAction(ChannelId, OCU_SET_HIGH);

    /* 2ms is enough for Ocu_SetAbsoluteThreshold to set new compare value ,
     * writing must be in the interval */
    if (OCU_CM_IN_REF_INTERVAL != RetStatus)
    {
        Status++;
    }

    Timer_DelayMs(2);

    if ((MCAL_CORE0 == CoreId) && (0U == Channel00_NotificationNumber))
    {
        Status++;
    }
    else if ((MCAL_CORE1 == CoreId) && (0U == Channel02_NotificationNumber))
    {
        Status++;
    }
    else
    {
        Channel00_NotificationNumber = 0U;
        Channel02_NotificationNumber = 0U;
    }

    SignalLevel = Ocu_GetOutputLevel(ChannelId);

    if (GTM_SIGNALSTATE_HIGH == SignalLevel)
    {
        DEBUG_PRINTF("Result: Passed!\r\n");
    }
    else
    {
        DEBUG_PRINTF("Result: Failed!\r\n");
    }

    SignalLevel = Ocu_GetOutputLevel(ChannelId);
    /* Set absolute compare match value, which is generated after CounterValue of
     * 2000ticks(2ms in this demo) */
    RetStatus = Ocu_SetRelativeThreshold(ChannelId, 2000U);
    /* Set channel pin action when compare match event generated */
    Ocu_SetPinAction(ChannelId, OCU_TOGGLE);

    /* 2ms is enough for Ocu_SetAbsoluteThreshold to set new compare value ,
     * writing must be in the interval */
    if (OCU_CM_IN_REF_INTERVAL != RetStatus)
    {
        Status++;
    }

    Timer_DelayMs(2);

    if ((MCAL_CORE0 == CoreId) && (0U == Channel00_NotificationNumber))
    {
        Status++;
    }
    else if ((MCAL_CORE1 == CoreId) && (0U == Channel02_NotificationNumber))
    {
        Status++;
    }
    else
    {
        Channel00_NotificationNumber = 0U;
        Channel02_NotificationNumber = 0U;
    }

    SignalLevel1 = Ocu_GetOutputLevel(ChannelId);

    if (SignalLevel1 == SignalLevel)
    {
        Status++;
    }

    if (0U == Status)
    {
        DEBUG_PRINTF("Result: Passed!\r\n");
    }
    else
    {
        DEBUG_PRINTF("Result: Failed!\r\n");
    }

    Ocu_DisableNotification(ChannelId);
    Ocu_StopChannel(ChannelId);
}

/****************************************************************************************************
*   Function Name           : Ocu_CompareMatchAdcByAbsoluteThreshold
*
*   Service ID              : None.
*
*   Description             : Example of ADC trigger signal generated by Ocu absolute 
*                             threshold matching event.
*                             Trigger signal can be observed by pin(Core0 P10.7/Core1 P14.0)
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : None
*
****************************************************************************************************/
void Ocu_CompareMatchAdcByAbsoluteThreshold
(
    void
)
{
    Mcal_CoreType CoreId;
    uint32 ChannelId;
    Ocu_ValueType CounterValue;
    Ocu_ReturnType RetStatus;
    uint32 Status;

    Status = 0U;

    CoreId = Mcal_GetCoreId();

    if (MCAL_CORE0 == CoreId)
    {
        ChannelId = 1U;
        Channel01_NotificationNumber = 0U;
    }
    else
    {
        ChannelId = 3U;
        Channel03_NotificationNumber = 0U;
    }

    /* Enable OCU channel notifications */
    Ocu_EnableNotification(ChannelId);
    /* Start the channel */
    Ocu_StartChannel(ChannelId);
    /* Set absolute compare match value, which is generated after CounterValue of
     * 2000ticks(2ms in this demo) */
    CounterValue = Ocu_GetCounter(ChannelId);
    RetStatus = Ocu_SetAbsoluteThreshold(ChannelId, CounterValue, (CounterValue + 2000U));
    /* 2ms is enough for Ocu_SetAbsoluteThreshold to set new compare value ,
     * writing must be in the interval */
    if (OCU_CM_IN_REF_INTERVAL != RetStatus)
    {
        Status++;
    }

    Timer_DelayMs(2);

    if ((MCAL_CORE0 == CoreId) && (0U == Channel01_NotificationNumber))
    {
        Status++;
    }
    else if ((MCAL_CORE1 == CoreId) && (0U == Channel03_NotificationNumber))
    {
        Status++;
    }
    else
    {
        Channel01_NotificationNumber = 0U;
        Channel03_NotificationNumber = 0U;
    }

    Ocu_DisableNotification(ChannelId);
    Ocu_StopChannel(ChannelId);

    DEBUG_PRINTF("\r\n------------------------------------------\r\n");
    if (0U == Status)
    {
        DEBUG_PRINTF("Result: Passed!\r\n");
    }
    else
    {
        DEBUG_PRINTF("Result: Failed!\r\n");
    }
}

/****************************************************************************************************
*   Function Name           : Ocu_CompareMatchAdcDemoByRelativeThreshold
*
*   Service ID              : None.
*
*   Description             : Example of ADC trigger signal generated by Ocu relative 
*                             threshold matching event.
*                             Trigger signal can be observed by pin(Core0 P10.7/Core1 P14.0)
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : None
*
****************************************************************************************************/
void Ocu_CompareMatchAdcDemoByRelativeThreshold
(
    void
)
{
    Mcal_CoreType CoreId;
    uint32 ChannelId;
    uint32 Status;

    Status = 0U;

    CoreId = Mcal_GetCoreId();

    if (MCAL_CORE0 == CoreId)
    {
        ChannelId = 1U;
        Channel01_NotificationNumber = 0U;
    }
    else
    {
        ChannelId = 3U;
        Channel03_NotificationNumber = 0U;
    }

    /* Enable OCU channel notifications */
    Ocu_EnableNotification(ChannelId);
    /* Start the channel */
    Ocu_StartChannel(ChannelId);

    /* Set relative compare match value, which is generated after
     * 2000ticks(2ms in this demo) of this time point */
    Ocu_SetRelativeThreshold(ChannelId, 2000U);

    Timer_DelayMs(2);

    if ((MCAL_CORE0 == CoreId) && (0U == Channel01_NotificationNumber))
    {
        Status++;
    }
    else if ((MCAL_CORE1 == CoreId) && (0U == Channel03_NotificationNumber))
    {
        Status++;
    }
    else
    {
        /* Do nothing */
    }

    Ocu_DisableNotification(ChannelId);
    Ocu_StopChannel(ChannelId);

    DEBUG_PRINTF("\r\n------------------------------------------\r\n");
    if (0U == Status)
    {
        DEBUG_PRINTF("Result: Passed!\r\n");
    }
    else
    {
        DEBUG_PRINTF("Result: Failed!\r\n");
    }
}

/****************************************************************************************************
*   Function Name           : Ocu_SetPinStateDemo
*
*   Service ID              : None.
*
*   Description             : Example of Ocu calling interface to change pin status.
*                             Change Pin(Core0 P10.7/Core1 P14.0) state by api
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : None
*
****************************************************************************************************/
void Ocu_SetPinStateDemo
(
    void
)
{
    Mcal_CoreType CoreId;
    uint32 ChannelId;

    Gtm_SignalState SignalLevel;

    CoreId = Mcal_GetCoreId();

    if (MCAL_CORE0 == CoreId)
    {
        ChannelId = 0U;
    }
    else
    {
        ChannelId = 2U;
    }

    Ocu_SetPinState(ChannelId, OCU_LOW);
    SignalLevel = Ocu_GetOutputLevel(ChannelId);
    if (GTM_SIGNALSTATE_LOW == SignalLevel)
    {
        DEBUG_PRINTF("Result: Passed!\r\n");
    }
    else
    {
        DEBUG_PRINTF("Result: Failed!\r\n");
    }

    Ocu_SetPinState(ChannelId, OCU_HIGH);
    SignalLevel = Ocu_GetOutputLevel(ChannelId);
    if (OCU_HIGH == SignalLevel)
    {
        DEBUG_PRINTF("Result: Passed!\r\n");
    }
    else
    {
        DEBUG_PRINTF("Result: Failed!\r\n");
    }
}

/****************************************************************************************************
 **                          Global Function Definitions                                            **
 ****************************************************************************************************/

/****************************************************************************************************
 *   Function Name           : Ocu_Demo
 *
 *   Service ID              : None.
 *
 *   Description             : This function is the demo API for Ocu driver.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous
 *
 *   Reentrancy              : Non-Reentrant
 *
 *   Return value            : None
 *
 *   Preconditions           : Ocu_Driver must be uninitialized.
 *
 ****************************************************************************************************/

void Ocu_Demo
(
    void
)
{
    Mcal_CoreType CoreId;
    CoreId = Mcal_GetCoreId ();

    /* If the execute core is current core and the command is valid,
     * execute the related demo */
    if ((Ocu_DemoCoreSelFlg== CoreId) &&(OcuCoreExeFlag.CoreCmdExist == 1U))
    {
        /* Switch demo chosen by user */
        switch (OcuCoreExeFlag.CoreExeCmd)
            {
            /* Change Pin state by api */
            case '1':
                {
                    DEBUG_PRINTF("Demo1: Change pin state by api\r\n");
                    Ocu_SetPinStateDemo();
                    break;
                }
            case '2':
                {
                    DEBUG_PRINTF("Demo2: Change pin state by compare match event(Absolute Threshold)\r\n");
                    Ocu_PinByAbsoluteThresholdDemo0();
                    Ocu_PinByAbsoluteThresholdDemo1();
                    break;
                }
            case '3':
                {
                    DEBUG_PRINTF("Demo3: Change pin state by compare match event(Relative Threshold)\r\n");
                    Ocu_PinByRelativeThresholdDemo0();
                    Ocu_PinByRelativeThresholdDemo1();
                    break;
                }
            case '4':
                {
                    DEBUG_PRINTF("Demo4: Generate ADC trigger signal by compare match event(Absolute Threshold)\r\n");

                    Ocu_CompareMatchAdcByAbsoluteThreshold();
                    break;
                }
            case '5':
                {
                    DEBUG_PRINTF("Demo5: Generate ADC trigger signal by compare match event(Relative Threshold)\r\n");

                    Ocu_CompareMatchAdcDemoByRelativeThreshold();
                    break;
                }
            default:
                {
                    break;
                }
            }
        if (0xFFU != OcuCoreExeFlag.CoreExeCmd)
        {
            OcuCoreExeFlag.CoreExeCmd = 0xFFU;
        }
    }
    if (1U == Ocu_DemoCoreInitStatus[CoreId])
    {
        /* Initialize and each core needs to be initialized once */
        Ocu_DemoCoreInitStatus[CoreId] = 2U;
        if (CoreId != 0U)
        {
            Ocu_Init (&Ocu_ConfigSet[0]);
        }
    }
    else if (3U == Ocu_DemoCoreInitStatus[CoreId])
    {
        Ocu_DemoCoreInitStatus[CoreId] = 0U;
        Ocu_DeInit ();
    }

}/* Ocu_Demo() */



/****************************************************************************************************
*   Function Name           : Ocu_DemoSelect
*
*   Service ID              : None.
*
*   Description             : Select which demo to run.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : None
*
****************************************************************************************************/
static void Ocu_DemoSelect(void)
{
    uint8 Cmd;
    uint8 Ocu_Exit;
    Std_VersionInfoType Ocu_ver;

    Ocu_Exit = 0U;

    while (0U == Ocu_Exit)
    {
        Ocu_GetVersionInfo (&Ocu_ver);
        DEBUG_PRINTF("\n\n\n");
        DEBUG_PRINTF("\n/*********************************************************/");
        DEBUG_PRINTF("\n           OCU DRIVER DEMO MENU V%02d.%02d.%02d            ",
                Ocu_ver.sw_major_version, Ocu_ver.sw_minor_version, Ocu_ver.sw_patch_version);
        DEBUG_PRINTF("\n                                                         ");
        DEBUG_PRINTF("\n <1>:  Change Pin(Core0 P10.7/Core1 P14.0 of Demo0, Core0 P2.8/Core1 P0.11 of Demo1) state by api");
        DEBUG_PRINTF("\n <2>:  Change Pin(Core0 P10.7/Core1 P14.0 of Demo0, Core0 P2.8/Core1 P0.11 of Demo1) state by compare match event(Absolute Threshold)");
        DEBUG_PRINTF("\n <3>:  Change Pin(Core0 P10.7/Core1 P14.0 of Demo0, Core0 P2.8/Core1 P0.11 of Demo1) state by compare match event(Relative Threshold)");
        DEBUG_PRINTF("\n <4>:  Trigger adc by compare even(absolute threshold)");
        DEBUG_PRINTF("\n <5>:  Trigger adc by compare even(relative threshold)");
        DEBUG_PRINTF("\n <x>: Go back to main menu\n");
        DEBUG_PRINTF("\nEnter option Number: ");

        Cmd = DEBUG_GETC();

        if(('1' == Cmd) || ('2' == Cmd) || ('3' == Cmd)|| ('4' == Cmd)|| ('5' == Cmd))
        {
            OcuCoreExeFlag.CoreExeCmd = Cmd;
            /* Set it to inform the Core to running the demo
             * It must be here */
            OcuCoreExeFlag.CoreCmdExist = 1U;
            /* Delay for initialize of the other core  */
            Timer_DelayMs (100);

            /* Call Ocu_Demo direct in Core 0 */
            Ocu_Demo();
            while (0xFFU != OcuCoreExeFlag.CoreExeCmd)
            {
                /* Waiting till Ocu demo test finished */
            }
            /* Clear it to wait next command */
            OcuCoreExeFlag.CoreCmdExist = 0U;
        }
        else if (((char) Cmd == 'x') || ((char) Cmd == 'X'))
        {
            Ocu_Exit = 1U;
            OcuCoreExeFlag.CoreExeCmd = 0xFFU;
        }
        else
        {
            DEBUG_PRINTF("\r\n Entered wrong option Number\r\n");
        }
    }
}

/****************************************************************************************************
*   Function Name           : Ocu_DemoEntry
*
*   Service ID              : None.
*
*   Description             : Ocu demo application entry.
*                             Select which core to use to run Ocu Channel.
*                             This APi shall be called by main core(Core 0).
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : None
*
****************************************************************************************************/
void Ocu_DemoEntry(void)
{
    uint8 Cmd;
    uint8 Ocu_Exit;
    Mcal_CoreType CoreId;

    Ocu_Exit = 0U;

    CoreId = Mcal_GetCoreId ();

    if (0U == Ocu_DemoCoreInitStatus[CoreId])
    {
        /* Initialize and each core needs to be initialized once */
        Ocu_DemoCoreInitStatus[1] = 1U;
        /* Initialize the Ocu in current core */
        Ocu_Init (&Ocu_ConfigSet[0]);
    }

    while (0U == Ocu_Exit)
    {
        DEBUG_PRINTF("\n/*********************************************************/\n");
        DEBUG_PRINTF("\n              OCU DRIVER DEMO MENU V%d.%d.%d                    ",
                     OCU_SW_MAJOR_VERSION,OCU_SW_MINOR_VERSION,OCU_SW_PATCH_VERSION);
        DEBUG_PRINTF("\n                                                         ");
        DEBUG_PRINTF("\n  <1> : Ocu Demo in Core0. ");
#ifndef THA6_THA6104
        DEBUG_PRINTF("\n  <2> : Ocu Demo in Core1. ");
#endif
        DEBUG_PRINTF("\n  <x> : Go back to Main Menu. \n");
        DEBUG_PRINTF("\n  ENTER YOUR OPTION   : ");

        Cmd = DEBUG_GETC();

        switch ((char) Cmd)
            {
            case '1':
                {
                    /* Demo for Core0 */
                    Ocu_DemoCoreSelFlg = MCAL_CORE0;
                    DEBUG_PRINTF("\n  Choose the Core0\n");
                    Ocu_DemoSelect ();
                    break;
                }
#ifndef THA6_THA6104
            case '2':
                {
                    /* Demo for Core1 */
                    Ocu_DemoCoreSelFlg = MCAL_CORE1;
                    DEBUG_PRINTF("\n  Choose the Core1\n");
                    Ocu_DemoSelect ();
                    break;
                }
#endif
            case 'x':
            case 'X':
                {
                  /* Exit OCU Demo */
                    Ocu_Exit = 1U;
                    /* DeInit the Ocu module of current core */
                    Ocu_DeInit();
                    Ocu_DemoCoreInitStatus[0] = 0U;
                    /* Set other core's flag , other core starts to de-initialize */
                    Ocu_DemoCoreInitStatus[1] = 3U;
                    break;
                }
                default:
                {
                    break;
                }
            }
    }
}

/*****************************************************************************************************
 *                            Notification functions                                                  *
 *****************************************************************************************************/
void Ocu_Notification_Channel0
(
    void
)
{
    Channel00_NotificationNumber++;
}

void Ocu_Notification_Channel1
(
    void
)
{
    Channel01_NotificationNumber++;
}

void Ocu_Notification_Channel2
(
    void
)
{
    Channel02_NotificationNumber++;
}

void Ocu_Notification_Channel3
(
    void
)
{
    Channel03_NotificationNumber++;
}

#define OCU_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Ocu_MemMap.h"

