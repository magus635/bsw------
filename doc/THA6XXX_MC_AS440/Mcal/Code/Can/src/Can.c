/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Can.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : MCAN
*
*   brief                 : This file contains all functions of Can Driver
*
*   Autosar Version      : 4.4.0
*
*   Build Version        : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                         Coding Rule Violations                                                  **
****************************************************************************************************/
/*
*#Violation Summary
*
*#Can_c_REF_2:MISRAC2012-Dir-4.2;
* Justification: Mixing inline assembly with C code reduces code complexity.
*
*#Can_c_REF_3:MISRAC2012-Dir-4.3;
* Justification: Mixing inline assembly with C code reduces code complexity.
*
*#Can_c_REF_4:MISRAC2012-Dir-4.9;
* Justification: Function like macros are used to reduce code complexity.
*
*#Can_c_REF_6:MISRAC2012-Rule-2.1; 
* Justification: Reserved API for user access.
*
*#Can_c_REF_7:MISRAC2012-Rule-2.2;
* Justification: Value used in assembly code.
*
*#Can_c_REF_9:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*#Can_c_REF_10:MISRAC2012-Rule-8.9;
* Justification: The value should be placed in the const data sections to reduce code complexity and stack size.
*
*#Can_c_REF_11:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Can_c_REF_12:MISRAC2012-Rule-20.10;
* Justification: Use glue operator to construct the exclusive area function name.
*
*#Can_c_REF_13:CertC-DCL00-C;
* Justification: Parameter declared refer to AUTOSAR specifications.
*
*#Can_c_REF_14:CertC-PRE00-C; 
* Justification: Function like macros are used to reduce code complexity.
*
*#Can_c_REF_15:CWE-1071; 
* Justification: MISRA-2012 Rule 15.7/Rule 16.4 require reserved empty code block.
*
*#Can_c_REF_16:MISRAC2012-Rule-19.2; 
* Justification: Using unions for bit-field access to registers.
*
*#Can_c_REF_17:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#Can_c_REF_18:MISRAC2012-Rule-8.7; 
* Justification:The function is used by other file.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Can.h"
#include "Can_GeneralTypes.h"
#include "CanIf_Can.h"
#include "CanIf.h"
#include "EcuM.h"
#include "SchM_Can.h"
#include "Det.h"

#if (CAN_LPDU_CALLOUT_FUNCTION_SUPPORT == STD_ON)
#include "Can_Callout.h"
#endif /* (CAN_LPDU_CALLOUT_FUNCTION_SUPPORT  \== STD_ON) */

#if (CAN_WAKEUP_SUPPORT == STD_ON)
#include "EcuM_Externals.h"
#endif /* (CAN_WAKEUP_SUPPORT  \== STD_ON) */

/****************************************************************************************************
**                          Version Checks                                                         **
****************************************************************************************************/
/* Check if current file and CAN header file are of the same vendor */
#if (CAN_VENDOR_ID != CAN_CFG_H_VENDOR_ID)
    #error "Can.c : Mismatch in Vendor ID"
#endif /* (CAN_VENDOR_ID \!= CAN_CFG_H_VENDOR_ID) */

#if (CAN_MODULE_ID != CAN_CFG_H_MODULE_ID)
  #error "Can.c : Mismatch in Module ID"
#endif /* (CAN_MODULE_ID \!= CAN_CFG_MODULE_ID) */

#if (CAN_AR_RELEASE_MAJOR_VERSION != CAN_CFG_H_AR_RELEASE_MAJOR_VERSION)
    #error "Can.c : Mismatch in Release Major Version"
#endif /* (CAN_AR_RELEASE_MAJOR_VERSION \!= CAN_CFG_H_AR_RELEASE_MAJOR_VERSION) */

#if (CAN_AR_RELEASE_MINOR_VERSION != CAN_CFG_H_AR_RELEASE_MINOR_VERSION)
    #error "Can.c : Mismatch in Release Minor Version"
#endif /* (CAN_AR_RELEASE_MINOR_VERSION \!= CAN_CFG_H_AR_RELEASE_MINOR_VERSION) */

#if (CAN_AR_RELEASE_REVISION_VERSION != CAN_CFG_H_AR_RELEASE_REVISION_VERSION)
    #error "Can.c : Mismatch in Release Revision Version"
#endif /* (CAN_AR_RELEASE_REVISION_VERSION \!= CAN_CFG_H_AR_RELEASE_REVISION_VERSION) */

/* Check if current file and CAN configuration header file are of the same software version */
#if (CAN_SW_MAJOR_VERSION != CAN_CFG_H_SW_MAJOR_VERSION)
  #error "Can.c : Mismatch in Software Major Version"
#endif /* (CAN_SW_MAJOR_VERSION \!= CAN_CFG_H_SW_MAJOR_VERSION) */

#if (CAN_SW_MINOR_VERSION != CAN_CFG_H_SW_MINOR_VERSION)
  #error "Can.c : Mismatch in Software Minor Version"
#endif /* (CAN_SW_MINOR_VERSION \!= CAN_CFG_H_SW_MINOR_VERSION) */

#if (CAN_SW_PATCH_VERSION != CAN_CFG_H_SW_PATCH_VERSION)
  #error "Can.c : Mismatch in Software Patch Version"
#endif /* (CAN_SW_PATCH_VERSION \!= CAN_CFG_SW_PATCH_VERSION) */

/****************************************************************************************************
*                          SchM Critical Section Protection Macros                                 **
****************************************************************************************************/
/* #Violation: Can_c_REF_12*/
/* #Violation: Can_c_REF_14 */
#define CAN_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Can_##Exclusive_Area()
/* #Violation: Can_c_REF_12*/
/* #Violation: Can_c_REF_14 */
#define CAN_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Can_##Exclusive_Area()
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
/* #Violation: Can_c_REF_4 */
/* #Violation: Can_c_REF_14 */
#define CAN_CORE_CFG(CoreId,Member) \
(Can_ConfigPtr->CoreConfigPtr[CoreId]->Member)

/* #Violation: Can_c_REF_4 */
/* #Violation: Can_c_REF_14 */
#define CAN_CONTROLLER_CFG(CoreId,ControllerId,Member) \
CAN_CORE_CFG(CoreId,CanControllerCfgPtr[ControllerId].Member)

/* #Violation: Can_c_REF_4 */
/* #Violation: Can_c_REF_14 */
#define CAN_BAUDRATE_CFG(CoreId,ControllerId,BaudIndex,Member) \
(CAN_CONTROLLER_CFG(CoreId,ControllerId,BaudrateCfgPtr[BaudIndex].Member))

/* #Violation: Can_c_REF_4 */
/* #Violation: Can_c_REF_14 */
#define CANFD_BAUDRATE_CFG(CoreId,ControllerId,BaudIndex,Member) \
(CAN_CONTROLLER_CFG(CoreId,ControllerId,BaudrateCfgPtr[BaudIndex].FdDefaultCfgPtr->Member))

/* #Violation: Can_c_REF_4 */
/* #Violation: Can_c_REF_14 */
#define CAN_HWOBJ_CFG(HohToCore,Member) \
(Can_ConfigPtr->HardwareObjectCfgPtr[HohToCore].Member)

/* #Violation: Can_c_REF_4 */
/* #Violation: Can_c_REF_14 */
#define CAN_CONTROLLER_STATUS(CoreId,ControllerId,Member) \
(Can_CoreStateArray[CoreId]->ControllerStatusPtr[ControllerId].Member)

/* #Violation: Can_c_REF_4 */
/* #Violation: Can_c_REF_14 */
#define CAN_BASE_ADDR(CoreId,ControllerId) \
(CAN_CONTROLLER_CFG(CoreId,ControllerId,PhysicalAddress))

/* Change the number of <BitLen> bits starting from the least significant bit <BitPos>
 * of the value of the address <OptData> to 0, leaving the other bits unchanged */
/* #Violation: Can_c_REF_4 */
/* #Violation: Can_c_REF_14 */
#define CAN_CLRBITS(OptDataPtr, BitPos) (*(OptDataPtr) &= (~(1ULL << (BitPos))))

/* Tx Buffer Data Field Size */
#define CAN_DATA_LENGTH_CODE_SIZE             (16U)
#define CAN_DATA_LENGTH_CODE_SIZE_MASK        (0x0FU)
/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Core0 Private Variable Definitions                                     **
****************************************************************************************************/
#if ((MCAL_NUMBER_OF_CORES > 0U)&& \
     ((defined(CAN_USED_CONTROLLER_MAX_NUM_TO_CORE0))&&(CAN_USED_CONTROLLER_MAX_NUM_TO_CORE0 > 0U)))
/* #Violation: Can_c_REF_9*/
#define CAN_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Can_c_REF_11 */
#include "Can_MemMap.h"

/* Holding core0 specific CAN Controller Mailbox status */
static VAR(Can_MBStatusType, CAN_VAR)
    Can_MBGlobalStatus_Core0[CAN_USED_HOH_ELEMENTS_MAX_NUM_TO_CORE0];

/* Holding core0 specific CAN Controller global status */
static VAR(Can_ControllerRuntimeType, CAN_VAR)
    Can_ControllerGlobalStatus_Core0[CAN_USED_CONTROLLER_MAX_NUM_TO_CORE0];

/* SWS_Can_00103:
    After power-up/reset, the Can module shall be in the state CAN_UNINIT.  */
static VAR(Can_InitType, CAN_VAR)Can_InitStatus_Core0;

/* #Violation: Can_c_REF_9*/
#define CAN_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Can_c_REF_11 */
#include "Can_MemMap.h"

/* #Violation: Can_c_REF_9*/
#define CAN_START_SEC_VAR_INIT_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Can_c_REF_11 */
#include "Can_MemMap.h"

/* Holding core0 specific CAN Controller status */
static VAR(Can_CoreStatusType, CAN_VAR) Can_CoreStatusCore0 =
{
    &Can_InitStatus_Core0,
    &Can_MBGlobalStatus_Core0[0],
    &Can_ControllerGlobalStatus_Core0[0],
};

/* #Violation: Can_c_REF_9*/
#define CAN_STOP_SEC_VAR_INIT_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Can_c_REF_11 */
#include "Can_MemMap.h"
#endif

/****************************************************************************************************
**                          Core1 Private Variable Definitions                                     **
****************************************************************************************************/
#if ((MCAL_NUMBER_OF_CORES > 1U)&& \
     ((defined(CAN_USED_CONTROLLER_MAX_NUM_TO_CORE1))&&(CAN_USED_CONTROLLER_MAX_NUM_TO_CORE1 > 0U)))

/* #Violation: Can_c_REF_9*/
#define CAN_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Can_c_REF_11 */
#include "Can_MemMap.h"

/* Holding core1 specific CAN Controller Mailbox status */
static VAR(Can_MBStatusType, CAN_VAR)
    Can_MBGlobal_Config_Core1[CAN_USED_HOH_ELEMENTS_MAX_NUM_TO_CORE1];

/* Holding core1 specific CAN Controller global status */
static VAR(Can_ControllerRuntimeType, CAN_VAR)
    Can_ControllerGlobalStatus_Core1[CAN_USED_CONTROLLER_MAX_NUM_TO_CORE1];

/* SWS_Can_00103:
    After power-up/reset, the Can module shall be in the state CAN_UNINIT. */
static VAR(Can_InitType, CAN_VAR) Can_InitStatus_Core1;

/* #Violation: Can_c_REF_9*/
#define CAN_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Can_c_REF_11 */
#include "Can_MemMap.h"

/* #Violation: Can_c_REF_9*/
#define CAN_START_SEC_VAR_INIT_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Can_c_REF_11 */
#include "Can_MemMap.h"

/* Holding core1 specific CAN Controller status */
static VAR(Can_CoreStatusType, CAN_VAR) Can_CoreStatusCore1 = \
{
    &Can_InitStatus_Core1,
    &Can_MBGlobal_Config_Core1[0],
    &Can_ControllerGlobalStatus_Core1[0],
};
/* #Violation: Can_c_REF_9*/
#define CAN_STOP_SEC_VAR_INIT_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Can_c_REF_11 */
#include "Can_MemMap.h"
#endif

/****************************************************************************************************
**                          Core2 Private Variable Definitions                                     **
****************************************************************************************************/
#if ((MCAL_NUMBER_OF_CORES > 2U)&& \
     ((defined(CAN_USED_CONTROLLER_MAX_NUM_TO_CORE2))&&(CAN_USED_CONTROLLER_MAX_NUM_TO_CORE2 > 0U)))

#define CAN_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Can_c_REF_11 */
#include "Can_MemMap.h"

/* Holding core2 specific CAN Controller Mailbox status */
static VAR(Can_MBStatusType, CAN_VAR)
    Can_MBGlobal_Config_Core2[CAN_USED_HOH_ELEMENTS_MAX_NUM_TO_CORE2];

/* Holding core2 specific CAN Controller global status */
static VAR(Can_ControllerRuntimeType, CAN_VAR)
    Can_ControllerGlobalStatus_Core2[CAN_USED_CONTROLLER_MAX_NUM_TO_CORE2];

/* SWS_Can_00103:
 After power-up/reset, the Can module shall be in the state CAN_UNINIT. */
static VAR(Can_InitType, CAN_VAR) Can_InitStatus_Core2;

#define CAN_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Can_c_REF_11 */
#include "Can_MemMap.h"

#define CAN_START_SEC_VAR_INIT_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Can_c_REF_11 */
#include "Can_MemMap.h"

/* Holding core2 specific CAN Controller status */
static VAR(Can_CoreStatusType, CAN_VAR) Can_CoreStatusCore2 = \
{
    &Can_InitStatus_Core2,
    &Can_MBGlobal_Config_Core2[0],
    &Can_ControllerGlobalStatus_Core2[0],
};
#define CAN_STOP_SEC_VAR_INIT_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Can_c_REF_11 */
#include "Can_MemMap.h"
#endif

/****************************************************************************************************
**                          Core3 Private Variable Definitions                                     **
****************************************************************************************************/
#if ((MCAL_NUMBER_OF_CORES > 3U)&& \
     ((defined(CAN_USED_CONTROLLER_MAX_NUM_TO_CORE3))&&(CAN_USED_CONTROLLER_MAX_NUM_TO_CORE3 > 0U)))

#define CAN_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Can_c_REF_11 */
#include "Can_MemMap.h"

/* Holding core3 specific CAN Controller Mailbox status */
static VAR(Can_MBStatusType, CAN_VAR)
    Can_MBGlobal_Config_Core3[CAN_USED_HOH_ELEMENTS_MAX_NUM_TO_CORE3];

/* Holding core3 specific CAN Controller global status */
static VAR(Can_ControllerRuntimeType, CAN_VAR)
    Can_ControllerGlobalStatus_Core3[CAN_USED_CONTROLLER_MAX_NUM_TO_CORE3];

/* SWS_Can_00103:
 After power-up/reset, the Can module shall be in the state CAN_UNINIT. */
static VAR(Can_InitType, CAN_VAR) Can_InitStatus_Core3;

#define CAN_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Can_c_REF_11 */
#include "Can_MemMap.h"

#define CAN_START_SEC_VAR_INIT_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Can_c_REF_11 */
#include "Can_MemMap.h"

/* Holding core3 specific CAN Controller status */
static VAR(Can_CoreStatusType, CAN_VAR) Can_CoreStatusCore3 = \
{
    &Can_InitStatus_Core3,
    &Can_MBGlobal_Config_Core3[0],
    &Can_ControllerGlobalStatus_Core3[0],
};
#define CAN_STOP_SEC_VAR_INIT_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Can_c_REF_11 */
#include "Can_MemMap.h"
#endif

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
/* #Violation: Can_c_REF_9*/
#define CAN_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Can_c_REF_11 */
#include "Can_MemMap.h"

/* Data length code for CANFD frame */
/* #Violation: Can_c_REF_10 */
static CONST(uint8, CAN_CONST) Can_FdGlobalDlcTB[CAN_DATA_LENGTH_CODE_SIZE] = \
{0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 12U, 16U, 20U, 24U, 32U, 48U, 64U};

/* An array of constant pointers to the status of all channels assigned all cores. */
static CONSTP2VAR(Can_CoreStatusType, CAN_VAR, CAN_APPL_CONST)
                    Can_CoreStateArray[MCAL_NUMBER_OF_CORES] = \
{
/* CanController status of all channels assigned to Core0 */
#if (MCAL_NUMBER_OF_CORES > 0U)
#if ((defined(CAN_USED_CONTROLLER_MAX_NUM_TO_CORE0))&&(CAN_USED_CONTROLLER_MAX_NUM_TO_CORE0 > 0U))
    &Can_CoreStatusCore0
#else
    NULL_PTR
#endif /* ((defined(CAN_USED_CONTROLLER_MAX_NUM_TO_CORE0))\&&(CAN_USED_CONTROLLER_MAX_NUM_TO_CORE0 > 0U)) */
#endif /* (MCAL_NUMBER_OF_CORES \> 0U) */

/* CanController status of all channels assigned to Core1 */
#if (MCAL_NUMBER_OF_CORES > 1U)
#if ((defined(CAN_USED_CONTROLLER_MAX_NUM_TO_CORE1))&&(CAN_USED_CONTROLLER_MAX_NUM_TO_CORE1 > 0U))
    ,&Can_CoreStatusCore1
#else
    ,NULL_PTR
#endif /* ((defined(CAN_USED_CONTROLLER_MAX_NUM_TO_CORE1))&&(CAN_USED_CONTROLLER_MAX_NUM_TO_CORE1 \> 0U)) */
#endif /* (MCAL_NUMBER_OF_CORES \> 1U) */

/* CanController status of all channels assigned to Core2 */
#if (MCAL_NUMBER_OF_CORES > 2U)
#if ((defined(CAN_USED_CONTROLLER_MAX_NUM_TO_CORE2))&&(CAN_USED_CONTROLLER_MAX_NUM_TO_CORE2 > 0U))
    ,&Can_CoreStatusCore2
#else
    ,NULL_PTR
#endif /* ((defined(CAN_USED_CONTROLLER_MAX_NUM_TO_CORE2))&&(CAN_USED_CONTROLLER_MAX_NUM_TO_CORE2 \> 0U)) */
#endif /* (MCAL_NUMBER_OF_CORES \> 2U) */

/* CanController status of all channels assigned to Core3 */
#if (MCAL_NUMBER_OF_CORES > 3U)
#if ((defined(CAN_USED_CONTROLLER_MAX_NUM_TO_CORE3))&&(CAN_USED_CONTROLLER_MAX_NUM_TO_CORE3 > 0U))
    ,&Can_CoreStatusCore3
#else
    ,NULL_PTR
#endif /* ((defined(CAN_USED_CONTROLLER_MAX_NUM_TO_CORE3))&&(CAN_USED_CONTROLLER_MAX_NUM_TO_CORE3 \> 0U)) */
#endif /* (MCAL_NUMBER_OF_CORES \> 3U) */
};

/* #Violation: Can_c_REF_9*/
#define CAN_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Can_c_REF_11 */
#include "Can_MemMap.h"
/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/
/* #Violation: Can_c_REF_9*/
#define CAN_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Can_c_REF_11 */
#include "Can_MemMap.h"

/* This pointer shall be store to copy field, not non-cache field */
static P2CONST(Can_ConfigType,AUTOMATIC, CAN_APPL_DATA) Can_ConfigPtr = NULL_PTR;

/* #Violation: Can_c_REF_9*/
#define CAN_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Can_c_REF_11 */
#include "Can_MemMap.h"

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/


/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
/* #Violation: Can_c_REF_9*/
#define CAN_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Can_c_REF_11 */
#include "Can_MemMap.h"

static inline FUNC(uint16, CAN_PRIVATE_CODE) Can_Clz64
(
    CONSTP2CONST(uint64, AUTOMATIC, CAN_APPL_CONST) Data
);

static FUNC(Std_ReturnType, CAN_PRIVATE_CODE) Can_SetControllerModeToStart
(
    uint8 Controller
);

static FUNC(Std_ReturnType, CAN_PRIVATE_CODE) Can_SetControllerModeToStop
(
    uint8 Controller
);

static FUNC(Std_ReturnType, CAN_PRIVATE_CODE) Can_SetControllerModeToSleep
(
    uint8 Controller
);

static FUNC(Std_ReturnType, CAN_PRIVATE_CODE) Can_CheckModeStart
(
    uint8 Controller
);

static FUNC(Std_ReturnType, CAN_PRIVATE_CODE) Can_CheckModeStop
(
    uint8 Controller
);

static FUNC(void, CAN_PRIVATE_CODE) Can_CheckBusOffEvent
(
    uint8 Controller
);

#if (CAN_WAKEUP_SUPPORT == STD_ON)
static FUNC(Std_ReturnType, CAN_PRIVATE_CODE) Can_CheckModeSleep
(
    uint8 Controller
);
#endif /* (CAN_WAKEUP_SUPPORT  \== STD_ON) */

static FUNC(Std_ReturnType, CAN_PRIVATE_CODE) Can_InitController
(
    uint8 Controller
);

static FUNC(boolean, CAN_PRIVATE_CODE) Can_EnableController_Interrupts
(
    uint8 Controller
);

static FUNC(boolean, CAN_PRIVATE_CODE) Can_DisableController_Interrupts
(
    uint8 Controller
);

static FUNC(void, CAN_PRIVATE_CODE) Can_RxProcessing
(
    uint8 Controller,
    Can_HwHandleType Hrh,
    Can_MsgRamType Ramtype
);
static FUNC(void, CAN_PRIVATE_CODE) Can_TxProcessing
(
    uint8 Controller,
    Can_HwHandleType Hth    
);

static FUNC(Std_ReturnType, CAN_PRIVATE_CODE) Can_WriteMsgObj
(
    uint8 Controller,
    Can_HwHandleType HardwareObjectID, 
    CONSTP2CONST(Can_PduType, AUTOMATIC, CAN_APPL_CONST) PduInfoPtr
);

static FUNC(void, CAN_PRIVATE_CODE) Can_MainFunctionWriteHandler
(
    uint8 MainFunction_Index
);

#if (CAN_SET_BAUDRATE_API == STD_ON)
#if (CAN_DEV_ERROR_DETECT == STD_ON)
static FUNC(Std_ReturnType, CAN_PRIVATE_CODE) Can_SetBaudrateDetCheck
(
    uint8 Controller, 
    Mcal_CoreType  CoreId
);
#endif /* (CAN_SET_BAUDRATE_API  \== STD_ON) */
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : Can_Clz64
*
*   Service ID              : None.
*
*   Description             : This function is used to Init the Controller Hardware Unit by static
*                             Configuration.It change the specific Controller of CAN to Freeeze Mode.
*                             Init the MCRregister to common started configuration.Clear the Tx and
*                             Rx MB buffer.
*                     
*   Parameters in           : Controller: CAN controller for which need to Init. The controller to
*                                         current core map.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : E_OK: Controller Init succeed.
*                             E_NOT_OK: Controller init failed,register init error .
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Can_00250
****************************************************************************************************/
/* #Violation: Can_c_REF_3 */
static inline FUNC(uint16, CAN_PRIVATE_CODE) Can_Clz64
(
    CONSTP2CONST(uint64, AUTOMATIC, CAN_APPL_CONST) Data
)
{
    uint16 high_clz;
    uint16 low_clz;
    uint32 high;
    uint32 low;

    /* Avoid static scanning warnings */
    high_clz = 0U;
    /* #Violation: Can_c_REF_7*/
    low_clz = 0U;
    /* #Violation: Can_c_REF_7*/
    high = (uint32)(*Data >> 32U);
    /* #Violation: Can_c_REF_7*/
    low = (uint32)(*Data & 0xFFFFFFFFUL);
    /* #Violation: Can_c_REF_2 */
    ASM_VOLATILE("   clz %0, %2        \n"
                 "   clz %1, %3        \n"
                 "   cmp %0, #32       \n"    
                 "   it eq             \n"
                 "   addeq %0, %0, %1  \n"
                 : "=&r" (high_clz), "=&r" (low_clz)
                 : "r" (high), "r" (low)
                 : "r0","cc");
    /* The value should not be greater than or equal to 64 */
    return (high_clz & 0x3FU);
}
/****************************************************************************************************
*   Function Name           : Can_InitController
*
*   Service ID              : None.
*
*   Description             : This function is used to Init the Controller Hardware Unit by static
*                             Configuration.It change the specific Controller of CAN to Freeeze Mode.
*                             Init the MCRregister to common started configuration.Clear the Tx and
*                             Rx MB buffer.
*                     
*   Parameters in           : Controller: CAN controller for which need to Init. The controller to
*                                         current core map.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : E_OK: Controller Init succeed.
*                             E_NOT_OK: Controller init failed,register init error .
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Can_00250
****************************************************************************************************/
static FUNC(Std_ReturnType, CAN_PRIVATE_CODE) Can_InitController
(
    uint8 Controller
)
{
    Can_HwHandleType Hoh;
    Can_HwHandleType HohToCore;
    uint8            ControllerToCore;
    uint8            BaudrateCfgIndex;
    uint8            IntLineOffset;
    Std_ReturnType   Ret;
    Can_Status       ApiStatus;
    Mcal_CoreType    CoreId;
    CAN_NODE        *CanNodePtr;
    boolean          CanRet;
    uint16           HobCount;
    uint16           HohIndex;


    /* Set E_NOT_OK as default */
    Ret = E_NOT_OK;

    /* Set TRUE as default */
    CanRet = TRUE;

    /* Get core id executing currently */
    /* #Violation: Can_c_REF_4*/
    CoreId = Mcal_GetCoreId();

    /* Get the controller config set index */
    ControllerToCore = Can_ConfigPtr->ControllerToCorePtr[Controller];

    /* Get the current baud-rate index from global status */
    BaudrateCfgIndex = CAN_CONTROLLER_STATUS(CoreId,ControllerToCore,BaudrateIndexCfg);

    /* Set interrupt line assignment */
    /* INFO:Each module that contains 3 nodes shares the Int_group [0:15]*/
    /*
        %3U: Each CAN hardware unit occupies three nodes.
        <<2U: Each CAN node occupies 4 interrupt signal lines.
     */
    IntLineOffset = (CAN_CONTROLLER_CFG(CoreId,ControllerToCore,PhysicalID) % 3U) << 2U;

    /* Get the controller node address */
    /* #Violation: Can_c_REF_4*/
    CanNodePtr = CAN_BASE_ADDR(CoreId,ControllerToCore);

    /*
       CAN_IT_ROUTER_LINE0:CAN_IT_MSGDEDICATEDRXBUF
       CAN_IT_ROUTER_LINE1:CAN_IT_TXEVENTFIFONEWENTRY
       CAN_IT_ROUTER_LINE2:CAN_IT_BUSOFFSTATUS
       CAN_IT_ROUTER_LINE3:CAN_IT_RXFIFO0WMREACHED\CAN_IT_RXFIFO1WMREACHED\
                           CAN_IT_RXFIFO0FULL\CAN_IT_RXFIFO1FULL
    */
    CanRet &= Can_Hal_SelectRouterInterruptLine( \
                CanNodePtr, \
                CAN_IT_MSGDEDICATEDRXBUF,IntLineOffset);
    CanRet &= Can_Hal_SelectRouterInterruptLine( \
                CanNodePtr, \
                CAN_IT_TXEVENTFIFONEWENTRY,CAN_IT_ROUTER_LINE1 + IntLineOffset);
    CanRet &= Can_Hal_SelectRouterInterruptLine( \
                CanNodePtr, \
                CAN_IT_BUSOFFSTATUS,CAN_IT_ROUTER_LINE2 + IntLineOffset);
    CanRet &= Can_Hal_SelectRouterInterruptLine( \
                CanNodePtr, \
                CAN_IT_RXFIFO0WMREACHED,CAN_IT_ROUTER_LINE3 + IntLineOffset);
    CanRet &= Can_Hal_SelectRouterInterruptLine( \
                CanNodePtr, \
                CAN_IT_RXFIFO1WMREACHED,CAN_IT_ROUTER_LINE3 + IntLineOffset);
    CanRet &= Can_Hal_SelectRouterInterruptLine( \
                CanNodePtr, \
                CAN_IT_RXFIFO0FULL,CAN_IT_ROUTER_LINE3 + IntLineOffset);
    CanRet &= Can_Hal_SelectRouterInterruptLine( \
                CanNodePtr, \
                CAN_IT_RXFIFO1FULL,CAN_IT_ROUTER_LINE3 + IntLineOffset);

    /* Set and check Configuration Change Enable bit */
    ApiStatus = Can_Hal_EnterInitMode(CanNodePtr);

    if((CAN_STATUS_OK == ApiStatus) && (TRUE == CanRet))
    {
        /* Disable loop-back functionality */
        CanRet &= Can_Hal_ConfigOperationMode(CanNodePtr, \
            CAN_OPERATION_MODE_NORMAL);

        /* Initialize nominal bit timing and pre-scaler */
        CanRet &= Can_Hal_ConfigBaudrate( \
                    CanNodePtr, (const Can_BaudRate *) \
                    &(CAN_BAUDRATE_CFG(CoreId,ControllerToCore,BaudrateCfgIndex,BaudrateParam)));

#if (CANFD_MODE_SUPPORT == STD_ON)
        /* Enable CANFD mode with bit rate switching */
        if ((TRUE == CAN_CONTROLLER_CFG(CoreId, ControllerToCore, CanFDSupport)) &&
        (NULL_PTR != CAN_BAUDRATE_CFG(CoreId, ControllerToCore, BaudrateCfgIndex, FdDefaultCfgPtr)))
        {
            /* Initialize data bit timing and pre-scaler */
            CanRet &= Can_Hal_ConfigFastBaudrate( \
                        CanNodePtr,(const Can_FastBaudRate *) \
                        &CANFD_BAUDRATE_CFG(CoreId,ControllerToCore,BaudrateCfgIndex,DataBaudRate));

            /* Enable CANFD mode with bit rate switching */
            ApiStatus = Can_Hal_ConfigFrameFormat( \
                            CanNodePtr, \
                            CAN_FRAME_FORMAT_FDFAST);
        }
        /* Enable CANFD mode without bit rate switching */
        /* #Violation: Can_c_REF_4*/
        else if ((TRUE == CAN_CONTROLLER_CFG(CoreId, ControllerToCore, CanFDSupport)) &&
        (NULL_PTR == CAN_BAUDRATE_CFG(CoreId, ControllerToCore, BaudrateCfgIndex, FdDefaultCfgPtr)))
        {
            ApiStatus = Can_Hal_ConfigFrameFormat( \
                            CanNodePtr, \
                            CAN_FRAME_FORMAT_FD_NO_BRS);
        }
        else
#endif /* (CANFD_MODE_SUPPORT  \== STD_ON) */
        /* Enable classic CAN mode */
        {
            ApiStatus = Can_Hal_ConfigFrameFormat( \
                            CanNodePtr, \
                            CAN_FRAME_FORMAT_STANDARD);
        }

        /* Clear the controller all pending interrupts flag */
        Can_Hal_ClearInterruptFlag(CanNodePtr,CAN_IT_MASK);

        /* Clear transmission and receive message flag */
        Can_Hal_ClearMessageFlag(CanNodePtr);

        /* Initialize the controller message ram:
           Receive  : Filter/FIFO0/FIFO1/Queue/Buffer
           Transmit : Filter/FIFO/Queue/Buffer
        */
       CanRet &= Can_Hal_InitMessageRam(CanNodePtr, \
            (const Can_FilterConfig *) \
                &CAN_CONTROLLER_CFG(CoreId,ControllerToCore,MsgRAMMapConfigPtr->FilterHandleConfig),\
            (const Can_RxConfig *) \
                &CAN_CONTROLLER_CFG(CoreId,ControllerToCore,MsgRAMMapConfigPtr->RxHandleConfig), \
            (const Can_TxConfig *) \
                &CAN_CONTROLLER_CFG(CoreId,ControllerToCore,MsgRAMMapConfigPtr->TxHandleConfig), \
            (const Can_MessageRAM *) \
                &CAN_CONTROLLER_CFG(CoreId,ControllerToCore,MsgRAMMapConfigPtr->MsgRAMMap));

        /* Initialize each filters which belong to the controller with detail rules */
        for(Hoh = 0U; (Hoh < CAN_CORE_CFG(CoreId,MaxCoreHohChannels)) && (CAN_STATUS_OK == ApiStatus);Hoh++)
        {
            /* Convert hardware object ID to hardware object list index. */
            HohToCore = CAN_CORE_CFG(CoreId,CanHohToCoreCfgPtr[Hoh]);

            /* Check the hardware object is belong to the controller? */
            if(CAN_HWOBJ_CFG(HohToCore,ControllerId) == Controller)
            {
                /* Check the hardware object is valid and CAN_RECEIVE type? */
                if (CAN_RECEIVE == CAN_HWOBJ_CFG(HohToCore,ObjectType))
                {
                    /* Filter Settings */
                    /* #Violation: Can_c_REF_4*/
                    ApiStatus = Can_Hal_ConfigureFilter(CanNodePtr,
                        (const Can_Filter *)CAN_HWOBJ_CFG(HohToCore,HwFilterPtr));
                }
                
                /* Get the depth of the current email and cycle to clear the global MB status value */
                for (HobCount = 0; HobCount < CAN_HWOBJ_CFG(HohToCore,HwObjectCount); HobCount++)
                {
                    /* Calculate the mapping between HohID and MB status array */
                    HohIndex = Can_ConfigPtr->HwObjToCoreMapPtr[HohToCore] + HobCount;
                    Can_CoreStateArray[CoreId]->CanMBStatusPtr[HohIndex].Can_TxPduIdBuff = 0U;
                    Can_CoreStateArray[CoreId]->CanMBStatusPtr[HohIndex].Can_TxEventCnt = 0U;
                    Can_CoreStateArray[CoreId]->CanMBStatusPtr[HohIndex].Can_TxPduIdBuffBusy = FALSE;
                }
            }
        }

        /* Check error occurred during register configuration */
        if ((CAN_STATUS_OK == ApiStatus) && (TRUE == CanRet))
        {
            Ret = E_OK;
        }
    }

    return Ret;
}

/****************************************************************************************************
*   Function Name           : Can_EnableController_Interrupts
*
*   Service ID              : None.
*
*   Description             : This function is used to enable the controller interrupt.
*                     
*   Parameters in           : Controller: CAN controller for which to enable interrupt.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant
*
*   Return value            : None. 
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, CAN_PRIVATE_CODE) Can_EnableController_Interrupts
(
    uint8 Controller
)
{
    Mcal_CoreType CoreId;
    uint32 InterruptBitSet;
    uint8 ControllerToCore;
    boolean CanRet;

    InterruptBitSet = 0U;

    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4*/
    CoreId = Mcal_GetCoreId();

    /* Get the controller config set index */
    ControllerToCore = Can_ConfigPtr->ControllerToCorePtr[Controller];

    /* Check processing transmit message completed with interrupt? */
    if(CAN_POLLING != CAN_CONTROLLER_CFG(CoreId,ControllerToCore,TxProcessing))
    {
        /* Enable the TxFIFO event Interrupt */
        InterruptBitSet |= CAN_IT_TXEVENTFIFONEWENTRY;
    }

    /* Check processing receive message with interrupt? */
    if(CAN_POLLING != CAN_CONTROLLER_CFG(CoreId,ControllerToCore,RxProcessing))
    {
        /* Enable Message stored to dedicated Rx buffer interrupt. */
        InterruptBitSet |= CAN_IT_MSGDEDICATEDRXBUF;
        /* Enable Rx FIFO 0 watermark reached interrupt. */
        InterruptBitSet |= CAN_IT_RXFIFO0WMREACHED;
        /* Enable Rx FIFO 0 full interrupt. */
        InterruptBitSet |= CAN_IT_RXFIFO0FULL;
        /* Enable Rx FIFO 1 watermark reached interrupt. */
        InterruptBitSet |= CAN_IT_RXFIFO1WMREACHED;
        /* Enable Rx FIFO 1 full interrupt. */
        InterruptBitSet |= CAN_IT_RXFIFO1FULL;
    }

    /* Check processing busoff event with interrupt? */
    if(CAN_INTERRUPT == CAN_CONTROLLER_CFG(CoreId,ControllerToCore,BusoffProcessing))
    {
        /* Enable the BusOff interrupt. */
        InterruptBitSet |= CAN_IT_BUSOFFSTATUS;
    }

    /* Enable Receive associated interrupts */
    /* #Violation: Can_c_REF_4*/
    CanRet = Can_Hal_EnableRouterInterrupt(CAN_BASE_ADDR(CoreId,ControllerToCore), \
                                  InterruptBitSet, \
                                  0xFFFFFFFFU);

    return CanRet;
}

/****************************************************************************************************
*   Function Name           : Can_DisableController_Interrupts
*
*   Service ID              : None.
*
*   Description             : This function is used to enable the controller interrupt.
*                     
*   Parameters in           : Controller: CAN controller for which to enable interrupt.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant
*
*   Return value            : None. 
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, CAN_PRIVATE_CODE) Can_DisableController_Interrupts
(
    uint8 Controller
)
{
    Mcal_CoreType CoreId;
    uint32 InterruptBitSet;
    uint8 ControllerToCore;
    boolean CanRet;

    InterruptBitSet = 0U;

    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4*/
    CoreId = Mcal_GetCoreId();

    /* Get the controller config set index */
    ControllerToCore = Can_ConfigPtr->ControllerToCorePtr[Controller];

    /* Check processing transmit message completed with interrupt? */
    if(CAN_POLLING != CAN_CONTROLLER_CFG(CoreId,ControllerToCore,TxProcessing))
    {
        /* Enable the TxFIFO event Interrupt */
        InterruptBitSet |= CAN_IT_TXEVENTFIFONEWENTRY;
    }

    /* Check processing receive message with interrupt? */
    if(CAN_POLLING != CAN_CONTROLLER_CFG(CoreId,ControllerToCore,RxProcessing))
    {
        /* Disable Message stored to dedicated Rx buffer interrupt. */
        InterruptBitSet |= CAN_IT_MSGDEDICATEDRXBUF;
        /* Disable Rx FIFO 0 watermark reached interrupt. */
        InterruptBitSet |= CAN_IT_RXFIFO0WMREACHED;
        /* Disable Rx FIFO 0 full interrupt. */
        InterruptBitSet |= CAN_IT_RXFIFO0FULL;
        /* Disable Rx FIFO 1 watermark reached interrupt. */
        InterruptBitSet |= CAN_IT_RXFIFO1WMREACHED;
        /* Disable Rx FIFO 1 full interrupt. */
        InterruptBitSet |= CAN_IT_RXFIFO1FULL;
    }

    /* Check processing busoff event with interrupt? */
    if(CAN_INTERRUPT == CAN_CONTROLLER_CFG(CoreId,ControllerToCore,BusoffProcessing))
    {
        /* Disable bus off event interrupt. */
        InterruptBitSet |= CAN_IT_BUSOFFSTATUS;
    }

    /* Disable Receive associat interrupt */
    /* #Violation: Can_c_REF_4*/
    CanRet = Can_Hal_DisableRouterInterrupt(CAN_BASE_ADDR(CoreId,ControllerToCore),InterruptBitSet);

    return CanRet;
}

/****************************************************************************************************
*   Function Name           : Can_WriteMsgObj
*
*   Service ID              : None.
*
*   Description             : Programs Message Object for transmission.
*                     
*   Parameters in           : CoreId: Current CPU core ID.
*                           : HardwareObjectID: Hth index are unique inside one core.
*                           : Hth: information which HW-transmit handle shall be used for transmit. 
*                                  Implicitly this is also the information about the controller to
*                                  use, because the Hth numbers are unique inside one hardware unit.
*
*                             PduInfoPtr: pointer to SDU user memory, DLC and Identifier.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant
*
*   Return value            : E_OK: Write command has been accepted
*
*                             E_NOT_OK: Development error occurred
*
*                             CAN_BUSY: No TX hardware buffer available or pre-emptive call of
*                                         Can_Write that can't be implemented reentrant
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, CAN_PRIVATE_CODE) Can_WriteMsgObj
(
    uint8 Controller,
    Can_HwHandleType HardwareObjectID, 
    CONSTP2CONST(Can_PduType, AUTOMATIC, CAN_APPL_CONST) PduInfoPtr
)
{
    uint8              *MBPduDataPtr;
    uint8               ControllerToCore;
    Mcal_CoreType       CoreId;
    Std_ReturnType      ApiStatus;
    uint32              txLocation;
    /* #Violation: Can_c_REF_16 */
    /* #Violation: Can_c_REF_17 */
    CAN_TxHeaderPack    MBPduInfo;
    boolean             TxBufferPending;
    boolean             IsDedicatedBuffer;
    boolean             LockReleased;
    CAN_NODE            *CanNodePtr;
    uint16              PduHandleLocation;
    uint32              TmpDataLength;
    uint32              TmpIdentifier;

#if (CANFD_MODE_SUPPORT == STD_ON)
    uint32 PadValueIndex;
    uint32 TempDLC;
    uint8  DefaultBaudrate;
#endif /* (CANFD_MODE_SUPPORT  \== STD_ON) */

#if (CAN_TRIGGER_TRANSMIT_SUPPORT == STD_ON)
    PduInfoType    Trigger_PduInfo;
    Std_ReturnType TriggerStatus;
#endif /* (CAN_TRIGGER_TRANSMIT_SUPPORT  \== STD_ON) */

#if (CAN_MULTIPLEXED_TRANSMISSION == STD_ON)
    Can_FifoStatus CanFifoStatus;
    uint16 TxFiFoQueuePutIndex;
    uint16 TxFiFoQueuePutIndexMax;
    uint16 TxFiFoQueuePutIndexMin;
#endif /* (CAN_MULTIPLEXED_TRANSMISSION \== STD_ON)  */

    ApiStatus = E_OK;
    LockReleased = FALSE;

    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4*/
    CoreId = Mcal_GetCoreId();

    /* Get the controller config set index */
    ControllerToCore = Can_ConfigPtr->ControllerToCorePtr[Controller];

    /* Get the controller node address */
    /* #Violation: Can_c_REF_4*/
    CanNodePtr = CAN_BASE_ADDR(CoreId,ControllerToCore);

    /* Enter Critical Section */
    CAN_ENTER_CRITICAL_SECTION(WriteMsgObj);

    /* SWS_Can_00212:
        The function Can_Write shall perform following actions if the hardware transmit object is
       free: */
    /* Dedicated buffer type */
    IsDedicatedBuffer = (boolean)(CAN_MSG_DED_BUFFER == CAN_HWOBJ_CFG(HardwareObjectID,MsgRamType));
    if (TRUE == IsDedicatedBuffer)
    {
        /* Get the element index from hardware object */
        txLocation = CAN_HWOBJ_CFG(HardwareObjectID,ElementsIndex);

        /* Calculate the swPduHandle Location in Dedicated buffer mode. */
        PduHandleLocation = Can_ConfigPtr->HwObjToCoreMapPtr[HardwareObjectID];

        /* SWS_Can_00212:
            5-1:The mutex for that HTH is set to 'signaled'
            5-4:The function returns with CAN_OK. */
        TxBufferPending = Can_Hal_GetTxBufferPendingStatus(
                                CanNodePtr,\
                                txLocation);
        if (TRUE == TxBufferPending)
        {
            /* SWS_Can_00213:
                Shall perform no actions if the hardware transmit object is busy
                with another transmit request for an L-PDU:
                2-2:The function Can_Write shall return CAN_BUSY. */
            ApiStatus = CAN_BUSY; 
        }
    }
#if (CAN_MULTIPLEXED_TRANSMISSION == STD_ON)   
    /* FIFO/QUEUE type */
    else
    {
        /* Get the controller Tx-FIFO free level.
           Number of elements stored in FIFO, range 0 to 64(Max). */
        Can_Hal_GetFifoStatus(CanNodePtr, CAN_FIFO_TYPE_TXFIFO, &CanFifoStatus);

        /* Check Tx queue is full? 
           The number of idle elements exceeds the actual number of configured elements, 
           which is abnormal and means that the Hoh is not consistent with the configuration.
           In this case, it is necessary to return busy to avoid PduHandleLocation calculation errors */
        if ((0U == CanFifoStatus.fifoFreeLevel) || \
            (CanFifoStatus.fifoFreeLevel > CAN_HWOBJ_CFG(HardwareObjectID,HwObjectCount)))
        {
            /* SWS_Can_00213:
                Shall perform no actions if the hardware transmit object is busy with another
               transmit request for an L-PDU: 
               2-2:The function Can_Write shall return CAN_BUSY. */
            ApiStatus = CAN_BUSY;
        }

        /* Set the element index with fixed value in FIFO/QUEUE mode. */
        txLocation = CAN_TX_FIFOQUEUE;

        /* Calculate the swPduHandle Location in FIFO/QUEUE mode.
           Tx FIFO/Queue write index pointer, range 0 to 31(Max). New transmit messages have to be
           written to the Tx FIFO starting with the Tx Buffer referenced by the Put Index TXFQSi.TFQPI. 
           An Add Request increments the Put Index to the next free Tx FIFO element. 
           Note: in case of mixed configurations where dedicated Tx Buffers are combined with a Tx FIFO
                 or a Tx Queue, the Put and Get indices indicate the number of the Tx Buffer starting
                 with the first dedicated ix Buffers.
           Example: For a configuration of 12 dedicated Tx Buffers and a Tx FIFO of 20 Buffers a
                 Put Index of 15 points to the fourth buffer of the Tx FIFO.*/
        /* Calculated TxFIFOQueue bounds */
        TxFiFoQueuePutIndexMin = CAN_HWOBJ_CFG(HardwareObjectID,ElementsIndex);
        TxFiFoQueuePutIndexMax = CAN_HWOBJ_CFG(HardwareObjectID,ElementsIndex)\
                                 + CAN_HWOBJ_CFG(HardwareObjectID,HwObjectCount); 

        /* Avoid overflow causing index out of bounds */
        if ((CanFifoStatus.fifoPutIdx >= TxFiFoQueuePutIndexMin) &&\
            (CanFifoStatus.fifoPutIdx < TxFiFoQueuePutIndexMax))
        {
            /* Calculate the swPduHandle Location. */
            TxFiFoQueuePutIndex = 
                ((uint16)CanFifoStatus.fifoPutIdx) - ((uint16)CAN_HWOBJ_CFG(HardwareObjectID,ElementsIndex));
            PduHandleLocation = Can_ConfigPtr->HwObjToCoreMapPtr[HardwareObjectID] + TxFiFoQueuePutIndex;
        }
        else
        {
            /* swPduHandle offset out of range.
               When CanController exits initialization mode (CCCR. INIT=0), TxFiFo PutIndex only applies
               mentioned ' Example ', otherwise it may cause this error.
               A typical use case: Set CanController to STOP and then call CanWrite function.
             */
            ApiStatus = E_NOT_OK;
        }
    }
#endif /* (CAN_MULTIPLEXED_TRANSMISSION \== STD_ON)  */

    /* Perform a busy check only when PduHandleLocation is within a valid range */
    if (ApiStatus == E_OK)
    {
        /* There are still Tx events(with PduId) in the current MB that have not been processed.
           Sending them again will result in the loss of the Tx events. */
       if (TRUE == Can_CoreStateArray[CoreId]->CanMBStatusPtr[PduHandleLocation].Can_TxPduIdBuffBusy)
       {
           /* SWS_Can_00213:
               Shall perform no actions if the hardware transmit object is busy with another
           transmit request for an L-PDU: 
           2-2:The function Can_Write shall return CAN_BUSY. */
           ApiStatus = CAN_BUSY;
       }
       else
       {
           /* Set the PduId Buffer as busy to avoid the loss of the Tx events(PduId be overwrited). */
           Can_CoreStateArray[CoreId]->CanMBStatusPtr[PduHandleLocation].Can_TxPduIdBuffBusy = TRUE;
       }
    }

    /* Release the WriteMsgObj lock before CanIf_TriggerTransmit()/Can_Hal_FastWriteMessage() for
       dedicated-buffer objects, so an unbounded upper-layer callback no longer runs with all
       interrupts suspended. This is NOT safe for FIFO/multiplexed objects: Can_Hal_FastWriteMessage
       re-reads the live FIFO put index (TX.FQS.B.TFQPI) at write time, while PduHandleLocation above
       was computed from an earlier snapshot of that same register -- releasing the lock here for
       FIFO mode would let a concurrent Can_Write for a different PduHandleLocation on the same FIFO
       advance TFQPI first, so the bookkeeping and the actual written buffer would no longer agree. */
    if ((ApiStatus == E_OK) && (TRUE == IsDedicatedBuffer))
    {
        CAN_EXIT_CRITICAL_SECTION(WriteMsgObj);
        LockReleased = TRUE;
    }

    /* SWS_Can_00213:
        The function Can_Write shall perform no actions if the hardware transmit object is busy with
       another transmit request for an L-PDU:
       2-1:The transmission of the other L-PDU shall not be cancelled and the function Can_Write is
       left without any actions.
       2-2:The function Can_Write shall return CAN_BUSY. */
    if (ApiStatus == E_OK)
    {
        /* SWS_Can_00212:
            5-2:The ID, DLC and SDU are put in a format appropriate for the hardware (if
             necessary) and copied in the appropriate hardware registers/buffers. */
        /* Default use TX Dedicated buffer when CAN_MULTIPLEXED_TRANSMISSION is not turned on. */
        TmpIdentifier = PduInfoPtr->id;
        TmpDataLength = (uint32)PduInfoPtr->length;
        MBPduDataPtr  = PduInfoPtr->sdu;

        /* SWS_Can_00276:
            The function Can_Write shall store the swPduHandle that is given inside the parameter
           PduInfo until the Can module calls the CanIf_TxConfirmation for this request where the
           swPduHandle is given as parameter.  */
        Can_CoreStateArray[CoreId]->CanMBStatusPtr[PduHandleLocation].Can_TxPduIdBuff = \
            PduInfoPtr->swPduHandle;

        MBPduInfo.B.messageMarkerLow = PduHandleLocation;
        /* messageMarkerLow is only 8 bits wide and silently truncates PduHandleLocation to its
           low byte. messageMarkerHigh carries the remaining high byte for wide indices; it is
           consumed by Can_Hal_FastWriteMessage's internal "<<8U" repositioning into T1[15:8]
           (can_hal.c) and, when wideMessageMark is enabled, is echoed back by the Tx Event FIFO
           into the high byte of the Can_TxProcessing lookup index (can_hal.c:1966-1972). Leaving
           it unset here means CAN_TxHeaderPack MBPduInfo's uninitialized stack bits get written
           into Message RAM and later used as an out-of-range CanMBStatusPtr[] index. */
        MBPduInfo.B.messageMarkerHigh = (uint16)(PduHandleLocation >> 8);

        /* Hardware control informations. */
        MBPduInfo.B.idType                = (uint8)CAN_ID_TYPE_STANDARD;
        MBPduInfo.B.eventControl          = (uint8)CAN_ENABLE;
        MBPduInfo.B.frameType             = (uint8)CAN_FRAME_TYPE_DATA;
        MBPduInfo.B.isErrorStateIndicator = (uint8)CAN_DISABLE;

        /* SWS_Can_00503:
            Can_Write() shall accept a null pointer as SDU (Can_PduType.Can_SduPtrType = NULL) if the
           trigger transmit API is enabled for this hardware object (CanTriggerTransmitEnable =
           TRUE).*/
        /* SWS_Can_00504:
            If the trigger transmit API is enabled for the hardware object, Can_Write() shall
           interpret a null pointer as SDU (Can_PduType.Can_SduPtrType = NULL) as request for using
           the trigger transmit interface. If so and the hardware object is free, Can_Write() shall
           call CanIf_TriggerTransmit() with the maximum size of the message buffer to acquire the
           PDU's data.*/
#if (CAN_TRIGGER_TRANSMIT_SUPPORT == STD_ON)
        TriggerStatus = E_NOT_OK;
        /* SWS_CAN_00505:
            If development error detection for CanDrv is enabled: Can_Write() shall raise
           CAN_E_PARAM_POINTER and shall return E_NOT_OK if the trigger transmit API is disabled for
           this hardware object (CanTriggerTransmitEnable = FALSE) and the SDU pointer inside PduInfo
           is a null pointer. */
        if (TRUE == CAN_HWOBJ_CFG(HardwareObjectID,TriggerTxEN))
        {
            /*Store Data pointer and Data length before trigger transmition. */
            Trigger_PduInfo.SduDataPtr = PduInfoPtr->sdu;
            Trigger_PduInfo.SduLength =  (uint32)PduInfoPtr->length;

            /* Invoke the function to trigger transmition. */
            TriggerStatus = CanIf_TriggerTransmit(PduInfoPtr->swPduHandle, &Trigger_PduInfo);
            
            /* Check the trigger transmition is fine? */
            if(E_OK == TriggerStatus)
            {
                /* Update the Pdu data length and MBPduDataPtr with users */
                TmpDataLength = Trigger_PduInfo.SduLength;
                MBPduDataPtr  = Trigger_PduInfo.SduDataPtr;
            }
            else
            {
                ApiStatus = E_NOT_OK;
            }
        }
#endif /* (CAN_TRIGGER_TRANSMIT_SUPPORT  \== STD_ON) */

        /* SWS_Can_00212:
            5-3:All necessary control operations to initiate the transmit are done. */
        /* Initialize as standard mode. */
        MBPduInfo.B.FDFormat      = CAN_DISABLE;
        MBPduInfo.B.bitRateSwitch = CAN_DISABLE;

#if (CANFD_MODE_SUPPORT == STD_ON)
        /* Check CanFD is enable? */
        if(TRUE == CAN_CONTROLLER_CFG(CoreId,ControllerToCore,CanFDSupport))
        {
            /* Enable Can FD frame type.
                However, there may be cases where conventional CAN 2.0 messages need to be 
                transmitted in networks supporting CAN-FD messages for example to facilitate CAN
                selective wakeup. In these cases it is necessary to support transmitting interleaved
                conventional CAN messages with CAN-FD messages. This can be achieved on frame level
                by using the two most significant bits of the CanId (see Can_IdType, SWS_Can_00416)
                passed during Can_Write to indicate which kind of frame shall be used. */
            if (0UL != (TmpIdentifier & CAN_FD_FRAME_FORMAT))
            {
                /* Enable CANFD Format */
                MBPduInfo.B.FDFormat = CAN_ENABLE;

                /* Configures the bit rate switch */
                DefaultBaudrate = CAN_CONTROLLER_STATUS(CoreId,ControllerToCore,BaudrateIndexCfg);
                MBPduInfo.B.bitRateSwitch = \
                            CANFD_BAUDRATE_CFG(CoreId,ControllerToCore,DefaultBaudrate,TBRS);
            }
        }
#endif /* (CANFD_MODE_SUPPORT  \== STD_ON) */

        /* SWS_CAN_00486:
            The CAN Frame has to be sent according to the two most significant bits of
           Can_PduType->id. The CAN FD frame bit is only evaluated if CAN Controller is in CAN FD
           mode. */
#if (CAN_EXTENED_ID_SUPPORT == STD_ON)
        /* Check the identifier is extended type? */
        if(0UL != (uint32)(TmpIdentifier & CAN_EXTENDED_IDMASK))
        {
            /* Clear the CAN message with Extended CAN ID Mask */
            TmpIdentifier     &= ~CAN_EXTENDED_IDMASK;
            MBPduInfo.B.idType = (uint8)CAN_ID_TYPE_EXTENDED;
        }
#if (CANFD_MODE_SUPPORT == STD_ON)
        /* Check the identifier is CanFD extended type? */
        if(0UL != (uint32)(TmpIdentifier & CAN_FD_FRAME_FORMAT))
        {
            /* Clear the CAN FD frame with Standard CAN ID Mask */
            TmpIdentifier &= ~CAN_FD_FRAME_FORMAT;
        }
#endif /* (CANFD_MODE_SUPPORT  \== STD_ON) */

#else /* (CAN_EXTENED_ID_SUPPORT  \== STD_OFF) */
#if (CANFD_MODE_SUPPORT == STD_ON)
        /*Clear the CAN FD frame with Standard CAN ID Mask*/
        TmpIdentifier &= ~CAN_STANDARD_FD_IDMASK;
#endif /* (CANFD_MODE_SUPPORT  \== STD_ON) */
#endif /* (CAN_EXTENED_ID_SUPPORT  \== STD_ON) */

        /* SWS_CAN_00502:
            If PduInfo->SduLength does not match possible DLC values CanDrv shall use the next higher
           valid DLC for transmission with initialization of unused bytes to the value of the
           corresponding CanFdPaddingValue*/
#if (CANFD_MODE_SUPPORT == STD_ON)
        /* Check DLC length and calculate the Hw support value if DLC > 24 */
        if (TmpDataLength > 24U)
        {
            /* Set DLC length with Hw Supported value */
            TempDLC = (((TmpDataLength + 15U) >> 4U) + 11U);
        }
        /* Check DLC length and calculate the Hw support value if DLC > 8 */
        else if (TmpDataLength > 8U)
        {
            /* Set DLC length with Hw Supported value */
            TempDLC = (((TmpDataLength + 3U) >> 2U) + 6U);
        }
        else
        {
            /* Set DLC length with Hw Supported value */
            TempDLC = TmpDataLength;
        }

        /* Check message padding when message length is more than 8 bytes and Enable padding */
        if((TmpDataLength > CAN_STANDARD_MAX_PAYLOAD_LENGTH)&& \
          (TRUE == CAN_HWOBJ_CFG(HardwareObjectID,FdPaddingEnable)))
        {
            /* Update the FDPaddingValue. Whether the FDPadding function is enable or not.
            * When the function is disable, the default value is 0xFF. */
            for(PadValueIndex = TmpDataLength; 
                PadValueIndex < Can_FdGlobalDlcTB[TempDLC & CAN_DATA_LENGTH_CODE_SIZE_MASK];
                PadValueIndex++)
            {
                /* Set FD Padding value */
                MBPduDataPtr[PadValueIndex] = CAN_HWOBJ_CFG(HardwareObjectID,FdPaddingValue);
            }
        }

        /* Convert data length to DLC */
        TmpDataLength = TempDLC;

#endif /* (CANFD_MODE_SUPPORT  \== STD_ON) */

        MBPduInfo.B.dataLength = TmpDataLength;
        MBPduInfo.B.identifier = TmpIdentifier;

        /* SWS_Can_00275:
            The function Can_Write shall be non-blocking. */
        /* #Violation: Can_c_REF_4*/
        Can_Hal_FastWriteMessage(CanNodePtr, txLocation, &MBPduInfo, MBPduDataPtr);
    }

    /* Exit Critical Section (skip if already released above for a dedicated-buffer object) */
    if (FALSE == LockReleased)
    {
        CAN_EXIT_CRITICAL_SECTION(WriteMsgObj);
    }

    return ApiStatus;
}

/****************************************************************************************************
*   Function Name           : Can_MainFunctionWriteHandler
*
*   Service ID              : None.
*
*   Description             : This function performs the polling of TX confirmation when
*                             CAN_TX_PROCESSING is set to POLLING.
*
*   Parameters in           : MainFunction_Index: The Index of Read and Write mainfunction.
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
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Can_00225
****************************************************************************************************/
static FUNC(void, CAN_PRIVATE_CODE) Can_MainFunctionWriteHandler
(
    uint8 MainFunction_Index
)
{
#if ((CAN_CONTROLLER_TX_POLLING_SUPPORT == STD_OFF) || (CAN_NUMBER_OF_MAINFUNCTION_RW_PERIOD == 0U))
    MCAL_UNUSED_VAR(MainFunction_Index);
#endif /* (CAN_CONTROLLER_TX_POLLING_SUPPORT \== STD_OFF) || 
            (CAN_NUMBER_OF_MAINFUNCTION_RW_PERIOD \== 0U) */

    /* SWS_Can_00178:
        The Can module may implement the function Can_MainFunction_Write as empty define in case no
       polling at all is used. */
#if (CAN_CONTROLLER_TX_POLLING_SUPPORT == STD_ON)
    Can_HwHandleType Hth;
    uint8            Controller;
    uint32           InterruptFlag;
    Mcal_CoreType    CoreId;
    Can_HwHandleType HthCount;
    uint8            ControllerLoop;

    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4*/
    CoreId = Mcal_GetCoreId();

#if (CAN_DEV_ERROR_DETECT == STD_ON)
    if(NULL_PTR == Can_ConfigPtr->CoreConfigPtr[CoreId])
    {
        /* The current core is not used, check the controller configuration.*/
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_MAIN_FUNCTION_WRITE, \
                              (uint8)CAN_E_CORE_NOT_CONFIGURED);
    }
    else if(CAN_UNINIT == *(Can_CoreStateArray[CoreId]->CanInitStatusPtr))
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_MAIN_FUNCTION_WRITE, \
                              (uint8)CAN_E_UNINIT);
    }
    else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_OFF) */
    {
        /* SWS_Can_00178:
            The Can module may implement the function Can_MainFunction_Write as empty define in case
           no polling at all is used. */

        for(ControllerLoop = 0U; 
            ControllerLoop < CAN_CORE_CFG(CoreId,MaxCoreController); ControllerLoop++)
        {
            /* Get the controller to HardwareObject map. */
            Controller = CAN_CONTROLLER_CFG(CoreId,ControllerLoop,LogicalID);

            /* Update interrupt flag */
            /* #Violation: Can_c_REF_4 */
            InterruptFlag = Can_Hal_GetInterruptFlag(CAN_BASE_ADDR(CoreId,ControllerLoop));

            if(0U != (CAN_IT_TXEVENTFIFOEVENTLOST & InterruptFlag))
            {
                /* Clear Tx Event FIFO Element Lost flags  */
                /* #Violation: Can_c_REF_4 */
                Can_Hal_ClearInterruptFlag(CAN_BASE_ADDR(CoreId,ControllerLoop), \
                    CAN_IT_TXEVENTFIFOEVENTLOST);

                /* SWS_Can_00395:
                    Can module shall raise the runtime error CAN_E_DATALOST in case of "overwrite" or
                "overrun" event detection. */
                (void)Det_ReportRuntimeError((uint16)CAN_MODULE_ID, \
                                            (uint8)CAN_INSTANCE_ID, \
                                            (uint8)CAN_SID_MAIN_FUNCTION_WRITE, \
                                            (uint8)CAN_E_DATALOST);
            }
            /* Detect the Controller is current Core or not.
                Avoid access an undefined region. */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
            else if(CoreId != Can_ConfigPtr->ControllerMapListPtr[Controller])
            {
                /* Not Can Controller configured in current core */
                (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                                    (uint8)CAN_INSTANCE_ID, \
                                    (uint8)CAN_SID_MAIN_FUNCTION_WRITE, \
                                    (uint8)CAN_E_CORE_CONTROLLER_MISMATCH);
            }
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
            else
            {
                for(HthCount = 0U; HthCount < CAN_CONTROLLER_CFG(CoreId,
                        ControllerLoop,MsgRAMMapConfigPtr->HthNum); HthCount++)
                {
                    /* Get the ID number of the receiving FIFO mailbox */
                    Hth = CAN_CONTROLLER_CFG(CoreId,ControllerLoop,MsgRAMMapConfigPtr->HthIndexMap[HthCount]);

#if (CAN_NUMBER_OF_MAINFUNCTION_RW_PERIOD > 0U)
                    if (CAN_HWOBJ_CFG(Hth,CanMainFuncRWPeriodRef) == MainFunction_Index)
#endif /* (CAN_NUMBER_OF_MAINFUNCTION_RW_PERIOD \> 0U) */
                    {
                        /**
                         * +---------------------------------------+---------+-------+-----------+
                         * |                                       | POLLING | MIXED | INTERRUPT |
                         * +---------------------------------------+---------+-------+-----------+
                         * | CanHardwareObjectUsesPolling  = TRUE  |   O     |  O    |    X      |
                         * | CanHardwareObjectUsesPolling  = FALSE |   O     |  X    |    X      |
                         * +---------------------------------------+---------+-------+-----------+
                         */
                        /* SWS_Can_00031:
                            The function Can_MainFunction_Write shall perform the polling of TX
                         confirmation when CanTxProcessing  is set to POLLING or MIXED. In case of
                         MIXED processing only the hardware objects for which CanHardwareObjectUsesPolling
                         is set to TRUE shall be polled. */
                        if (TRUE == CAN_HWOBJ_CFG(Hth,UsesPolling))
                        {
                            /* Process the Tx events */
                            Can_TxProcessing(Controller,Hth);
                        }
                    }
                }
            }
        }
    }
#endif /* (CAN_CONTROLLER_TX_POLLING_SUPPORT  \== STD_ON) */
}
/****************************************************************************************************
*   Function Name           : Can_RxProcessing
*
*   Service ID              : None.
*
*   Description             : The function is used to process the Rx.Include check Error status,
*                             get the result of data from the MB buffer.Period call in the Rx
*                             mainfunction.
* 
*   Parameters in           : Controller: CAN controller for which to process the Rx.
*                             Hrh: The Index of MB that used to receive the data.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant
*
*   Return value            : None.
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Can_00300 SWS_Can_00012
****************************************************************************************************/
static FUNC(void, CAN_PRIVATE_CODE) Can_RxProcessing
(
    uint8 Controller,
    Can_HwHandleType Hrh,
    Can_MsgRamType Ramtype
)
{
    uint8               CanMBData[CANFD_MODE_MAX_PAYLOAD_LENGTH];
    PduInfoType         PduInfo;
    Mcal_CoreType       CoreId;
    /* #Violation: Can_c_REF_16 */
    /* #Violation: Can_c_REF_17 */
    CAN_RxHeaderPack    Message;
    uint32              FifoLevel;
    uint32              FifoProcessedCount;
    uint8               ControllerToCore;
    boolean             Available;
    CAN_NODE            *CanNodePtr;
    Can_Status          ApiStatus;
    uint8               TmpDataLength;
    uint32              TmpIdentifier;
    uint32              RxFIFOLocation;
    uint32 (*pCan_Hal_GetRxFifoFillLevel)(const CAN_NODE *const pNode);
    /* Avoid CertC-DCL39-C */
    Can_HwType Mailbox;

#if (CAN_LPDU_CALLOUT_FUNCTION_SUPPORT == STD_ON)
    boolean CalloutResult;
#endif /* (Can_PDU_CALLOUT_FUNCTION_SUPPORT  \== STD_ON) */

    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4*/
    CoreId = Mcal_GetCoreId();

    /* Get the controller config set index */
    ControllerToCore = Can_ConfigPtr->ControllerToCorePtr[Controller];

    /* Get the controller node address */
    /* #Violation: Can_c_REF_4 */
    CanNodePtr = CAN_BASE_ADDR(CoreId,ControllerToCore);

    /* Chenck the hardware object is Rx dedicated buffer type? */
    if (CAN_MSG_DED_BUFFER == Ramtype)
    {
        /* Check Rx new data arrived with NDAT1 and NDAT2? */
        Available = Can_Hal_GetRxBufferMessageAvailableStatus(
            CanNodePtr,\
            CAN_HWOBJ_CFG(Hrh,ElementsIndex));

        if(TRUE == Available)
        {
            /* SWS_Can_00299:
                The Can module shall copy the L-SDU in a shadow buffer after reception, if the RX
               buffer cannot be protected (locked) by CAN Hardware against overwriting by a newly
               received message.*/
            /* Receive new message from dedicate buffer. */
            ApiStatus = Can_Hal_FastReadMessage(CanNodePtr,\
                                                CAN_HWOBJ_CFG(Hrh,ElementsIndex),\
                                                &Message, CanMBData);

            TmpDataLength = Can_FdGlobalDlcTB[Message.B.dataLength];
            TmpIdentifier = Message.B.identifier;

#if(CAN_LPDU_CALLOUT_FUNCTION_SUPPORT == STD_ON)
            CalloutResult = CAN_LPDU_RECEIVE_CALLOUT_FUNCTION(Hrh, \
                                                              TmpIdentifier, \
                                                              TmpDataLength, \
                                                              CanMBData);
            /* SWS_Can_00444:
                If the L-PDU callout returns false, the L-PDU shall not be
                processed any further. */
            if((FALSE != CalloutResult) && (CAN_STATUS_OK == ApiStatus))
#else
            if(CAN_STATUS_OK == ApiStatus)
#endif /* (CAN_LPDU_CALLOUT_FUNCTION_SUPPORT  \== STD_OFF) */
            {
                /* SWS_Can_00416:
                    Represents the Identifier of an L-PDU. 
                    The two most significant bits specify the frame type:
                    00 CAN   frame with Standard CAN ID
                    01 CANFD frame with Standard CAN ID
                    10 CAN   frame with Extended CAN ID
                    11 CANFD frame with Extended CAN ID */
                if(CAN_ID_TYPE_EXTENDED == Message.B.idType)
                {
                    TmpIdentifier |= CAN_EXTENDED_IDMASK;
                }
#if (CANFD_MODE_SUPPORT == STD_ON)
                if(CAN_FRAME_FORMAT_STANDARD != Message.B.FDFormat)
                {
                    TmpIdentifier |= CAN_FD_FRAME_FORMAT;
                }
#endif /* (CANFD_MODE_SUPPORT  \== STD_ON) */
                Mailbox.CanId        = TmpIdentifier;
                Mailbox.Hoh          = Hrh;
                Mailbox.ControllerId = Controller;
                PduInfo.SduLength    = TmpDataLength;
                PduInfo.SduDataPtr   = CanMBData;
                /* SWS_Can_00396:
                    The RX-interrupt service routine of the corresponding HW resource or the function
                   Can_MainFunction_Read in case of polling mode shall call the callback function
                   CanIf_RxIndication. */
                CanIf_RxIndication(&Mailbox, &PduInfo);
            }
#if (CAN_SAFETY_ENABLE == STD_ON)
            else
            {
                /* Safety Error Tracer */
                (void)Det_ReportRuntimeError((uint16)CAN_MODULE_ID, \
                                             (uint8)CAN_INSTANCE_ID, \
                                             (uint8)CAN_SID_RX_PROCESSING, \
                                             (uint8)CAN_E_DATALOST);
            }
#endif /* (CAN_SAFETY_ENABLE \== STD_ON) */      
        }
    }
    /* Check the hardware object is Rx Queue type,Just because the enumeration variable defines this
       type, the hardware not supported Rx Queue Mode and this condition should not be met.
    */
    else if(CAN_MSG_QUEUE == Ramtype)
    /* #Violation: Can_c_REF_15 */
    {
        /* do nothing */
    }
    /* Default the hardware object is Rx FIFO type? */
    else
    {
        /* M_CAN_AN003 Interrupt Handling Hints:
            Carefully design your interrupt handling strategy, i.e. how you handle individual
            interrupts and how you clear the corresponding flag. 
            1.Clear interrupt flag IR.RF0N and then read all messages from Rx FIFO0.
              This is because the interrupt flag IR.RF0N will be set again if a new message arrives 
              during reading Rx FIFO0. Consequently, the ISR will be called again and the Host will
              read the new message from the Rx FIFO0 at that time.(This method ensures that all 
              messages will be read by the ISR from Rx FIFO0.)
            2.Read all messages from Rx FIFO0 and clear interrupt flag IR.RF0N.
              Imagine the case that after reading the messages from Rx FIFO0, but before clearing
              the interrupt flag IR.RF0N, a new message arrives. Since in this case the interrupt
              flag IR.RF0N is cleared before reading the message, the ISR won't be called again.
              This means this message is forgotten in Rx FIFO0.(This method does not ensure that all
              messages will be read by the ISR from Rx FIFO0.) */

        /*  Get the Fifo0 level api pointer and FiFo location. */      
        if (CAN_MSG_FIFO0 == Ramtype)
        {
            pCan_Hal_GetRxFifoFillLevel = &Can_Hal_GetRxFifo0FillLevel;
            RxFIFOLocation = CAN_RX_FIFO0;
        }
        /*  Get the Fifo1 level api pointer and FiFo location. */      
        else
        {
            pCan_Hal_GetRxFifoFillLevel = &Can_Hal_GetRxFifo1FillLevel;
            RxFIFOLocation = CAN_RX_FIFO1;
        }
        
        /* Clear the Fifo Processed Count variable */
        FifoProcessedCount = 0;
        do
        {
            /* Update the Rx FIFO0 fill level */
            FifoLevel = pCan_Hal_GetRxFifoFillLevel(CanNodePtr);
            
            /* The Fifo Processed Count shall be less than FIFO Threshold */
            if ((FifoLevel > 0U) && (FifoProcessedCount < CAN_HWOBJ_CFG(Hrh,HwObjectCount)))
            {
                /* Count messages processed with FIFO0 */
                FifoProcessedCount += 1U;

                /* Receive new message from FIFO0. */
                ApiStatus = Can_Hal_FastReadMessage(CanNodePtr,\
                                                    RxFIFOLocation,\
                                                    &Message, \
                                                    CanMBData);

                TmpDataLength = Can_FdGlobalDlcTB[Message.B.dataLength];
                TmpIdentifier = Message.B.identifier;
      
#if(CAN_LPDU_CALLOUT_FUNCTION_SUPPORT == STD_ON)
                CalloutResult = CAN_LPDU_RECEIVE_CALLOUT_FUNCTION(Hrh, \
                                                                  TmpIdentifier, \
                                                                  TmpDataLength, \
                                                                  CanMBData);
                /* SWS_Can_00444:
                    If the L-PDU callout returns false, the L-PDU shall not be
                    processed any further. */
                if((FALSE != CalloutResult) && (CAN_STATUS_OK == ApiStatus))
#else
                if(CAN_STATUS_OK == ApiStatus)
#endif /* (CAN_LPDU_CALLOUT_FUNCTION_SUPPORT  \== STD_OFF) */
                {
                    /* SWS_Can_00416:
                        Represents the Identifier of an L-PDU. 
                        The two most significant bits specify the frame type:
                        00 CAN   frame with Standard CAN ID
                        01 CANFD frame with Standard CAN ID
                        10 CAN   frame with Extended CAN ID
                        11 CANFD frame with Extended CAN ID */
                    if(CAN_ID_TYPE_EXTENDED == Message.B.idType)
                    {
                        TmpIdentifier |= CAN_EXTENDED_IDMASK;
                    }
#if (CANFD_MODE_SUPPORT == STD_ON)
                    if(CAN_FRAME_FORMAT_STANDARD != Message.B.FDFormat)
                    {
                        TmpIdentifier |= CAN_FD_FRAME_FORMAT;
                    }
#endif /* (CANFD_MODE_SUPPORT  \== STD_ON) */
                    /* SWS_Can_00279:
                        On L-PDU reception, the Can module shall call the RX indication callback
                       function CanIf_RxIndication with ID, Hoh, abstract CanIf ControllerId in
                       parameter Mailbox, and the Data Length and pointer to the L-SDU buffer in
                       parameter PduInfoPtr. */
                    Mailbox.CanId        = TmpIdentifier;
                    Mailbox.Hoh          = Hrh;
                    Mailbox.ControllerId = Controller;
                    PduInfo.SduLength    = TmpDataLength;
                    PduInfo.SduDataPtr   = CanMBData;
                    CanIf_RxIndication(&Mailbox, &PduInfo);
                }
#if (CAN_SAFETY_ENABLE == STD_ON)
                else
                {
                    /* Safety Error Tracer */
                    (void)Det_ReportRuntimeError((uint16)CAN_MODULE_ID, \
                                                 (uint8)CAN_INSTANCE_ID, \
                                                 (uint8)CAN_SID_RX_PROCESSING, \
                                                 (uint8)CAN_E_DATALOST);
                }
#endif /* (CAN_SAFETY_ENABLE \== STD_ON) */  
            }
        } while((FifoLevel > 0U) && (FifoProcessedCount < CAN_HWOBJ_CFG(Hrh,HwObjectCount))); 
    }
}
/****************************************************************************************************
*   Function Name           : Can_TxProcessing
*
*   Service ID              : None.
*
*   Description             : The function is used to process the Tx.Include check Error status,
*                             get the result of data from the TxEvent buffer.
* 
*   Parameters in           : Controller: CAN controller for which to process the Rx.
*                             Hth: The Index of buffer that used to Transmit the data.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant
*
*   Return value            : None.
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, CAN_PRIVATE_CODE) Can_TxProcessing
(
    uint8 Controller,
    Can_HwHandleType Hth
)
{
    uint8                   ControllerToCore;
    Mcal_CoreType           CoreId;
    uint32                  TxEvntFillLvlVal;
    CAN_TxEvenHeaderTypeDef TxEvenHeader;
    CAN_NODE                *CanNodePtr;
    uint32                  PduHandleIndex;
    uint32                  PduHandleBase;
    PduIdType               TmpTxPduId;

    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4*/
    CoreId = Mcal_GetCoreId();

    /* Get the controller config set index */
    ControllerToCore = Can_ConfigPtr->ControllerToCorePtr[Controller];

    /* Get the controller node address */
    /* #Violation: Can_c_REF_4*/
    CanNodePtr = CAN_BASE_ADDR(CoreId,ControllerToCore);

    /* Read Tx event fifo fill level value */
    /* #Violation: Can_c_REF_4*/
    TxEvntFillLvlVal = Can_Hal_GetTxEventFifoLevel(CanNodePtr);

    /* Loop read and store all TxEvents from FIFO.
       When multiple TxEvent events occur, as long as the CPU responds once, it can ensure that all
       events are processed correctly.
       INFO: Regardless of whether the caller is MainFunc or IRQ, the Mailbox ID corresponding to the
             event should be read and recorded from the register. */
    while (TxEvntFillLvlVal > 0U)
    {
        /* Read Message Marker */
        /* #Violation: Can_c_REF_4*/
        (void)Can_Hal_ReadTxEvent(CanNodePtr,&TxEvenHeader);

        /* Avoid self-adding report++ overflow */
        if(0xFFU > Can_CoreStateArray[CoreId]->CanMBStatusPtr[TxEvenHeader.messageMarker].Can_TxEventCnt)
        {
            /* Increment the TxEvent count that has been transmitted. */
            Can_CoreStateArray[CoreId]->CanMBStatusPtr[TxEvenHeader.messageMarker].Can_TxEventCnt++;
        }
        /* Update Tx event fifo fill level value */
        /* #Violation: Can_c_REF_4*/
        TxEvntFillLvlVal = Can_Hal_GetTxEventFifoLevel(CanNodePtr);
    }

    /* Get PDUID Stored base address */
    PduHandleBase = Can_ConfigPtr->HwObjToCoreMapPtr[Hth];

    /* Process the TxEvent directly with dedicate buffer */
    if (CAN_MSG_DED_BUFFER == CAN_HWOBJ_CFG(Hth,MsgRamType))
    {

        /* Only all stored TxEvents that belong the hth shall be processed. */
        while (Can_CoreStateArray[CoreId]->CanMBStatusPtr[PduHandleBase].Can_TxEventCnt > 0U)
        {

            /* Read PduId in advance, store it in the stack, and clear the mailbox busy flag
               Even if interrupted before invoicing CanIf_TxCConfirmation, PduId can still be
               reported correctly at this time. */
            TmpTxPduId = Can_CoreStateArray[CoreId]->CanMBStatusPtr[PduHandleBase].Can_TxPduIdBuff;

            /* Set the PduId Buffer as free. so that allow next transmit.*/
            Can_CoreStateArray[CoreId]->CanMBStatusPtr[PduHandleBase].Can_TxPduIdBuffBusy = FALSE;

            /* Enter Critical Section */
            CAN_ENTER_CRITICAL_SECTION(TxProcessing);

            /* Avoid self-deducting overflow */
            if (Can_CoreStateArray[CoreId]->CanMBStatusPtr[PduHandleBase].Can_TxEventCnt > 0U)
            {
                /* Deducting the TxEvent count that has been transmitted. */
                Can_CoreStateArray[CoreId]->CanMBStatusPtr[PduHandleBase].Can_TxEventCnt -= 1U;
            }

            /* Exit Critical Section */
            CAN_EXIT_CRITICAL_SECTION(TxProcessing);

            /* SWS_Can_00016:
                The Can module shall call CanIf_TxConfirmation to indicate a successful transmission. It
            shall either called by the TX-interrupt service routine of the corresponding HW resource
            or inside the Can_MainFunction_Write in case of polling mode.*/
            /* Call Transmission confirmation to upper-layer with L-PDU handle */
            CanIf_TxConfirmation(TmpTxPduId);
        }
    }
    /* Process the TxEvent directly with FIFI/QUEUE */
    else
    {
        for (PduHandleIndex = 0; PduHandleIndex < CAN_HWOBJ_CFG(Hth,HwObjectCount); PduHandleIndex++)
        {
            /* Only all stored TxEvents that belong the hth shall be processed. */
            while (Can_CoreStateArray[CoreId]->CanMBStatusPtr[PduHandleBase + PduHandleIndex].Can_TxEventCnt > 0U)
            {
               /* Read PduId in advance, store it in the stack, and clear the mailbox busy flag
                  Even if interrupted before invoicing CanIf_TxCConfirmation, PduId can still be
                  reported correctly at this time. */
                TmpTxPduId = Can_CoreStateArray[CoreId]->CanMBStatusPtr[PduHandleBase + PduHandleIndex].Can_TxPduIdBuff;
                
                /* Set the PduId Buffer as free. so that allow next transmit.*/
                Can_CoreStateArray[CoreId]->CanMBStatusPtr[PduHandleBase + PduHandleIndex].Can_TxPduIdBuffBusy = FALSE;

                /* Enter Critical Section */
                CAN_ENTER_CRITICAL_SECTION(TxProcessing);

                /* Avoid self-deducting overflow */
                if (Can_CoreStateArray[CoreId]->CanMBStatusPtr[PduHandleBase + PduHandleIndex].Can_TxEventCnt > 0U)
                {
                    /* Deducting the TxEvent count that has been transmitted. */
                    Can_CoreStateArray[CoreId]->CanMBStatusPtr[PduHandleBase + PduHandleIndex].Can_TxEventCnt -= 1U;
                }

                /* Exit Critical Section */
                CAN_EXIT_CRITICAL_SECTION(TxProcessing);

                /* SWS_Can_00016:
                   The Can module shall call CanIf_TxConfirmation to indicate a successful transmission. It
                   shall either called by the TX-interrupt service routine of the corresponding HW resource
                   or inside the Can_MainFunction_Write in case of polling mode.*/
                /* Call Transmission confirmation to upper-layer with L-PDU handle */
                CanIf_TxConfirmation(TmpTxPduId);
            }
        }
        
    }
}

/****************************************************************************************************
*   Function Name           : Can_CheckModeStart
*
*   Service ID              : None.
*
*   Description             : This function is used to set the controller to start mode and then
*                             check the translation whether succeed or not.
*                     
*   Parameters in           : Controller: CAN controller for which the status shall be changed.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : E_OK: request accepted
*                             E_NOT_OK: request not accepted, a development error occurred
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, CAN_PRIVATE_CODE) Can_CheckModeStart
(
    uint8 Controller
)
{
    Std_ReturnType Ret;
    Can_Status     ApiStatus;
    Mcal_CoreType  CoreId;
    uint8          ControllerToCore;
    boolean        CanRet;
    uint32         ProtocolStatus;
    volatile uint64     TimerFreq;
    volatile uint64     TimeOutCount;
    volatile uint64     CurrentCount;

    /* Set Ret as E_NOT_OK */
    Ret = E_NOT_OK;
    CanRet = TRUE;


    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4*/
    CoreId = Mcal_GetCoreId();

    /* Get the controller config set index */
    ControllerToCore = Can_ConfigPtr->ControllerToCorePtr[Controller];

    /* Activate Controller: Set the controller to normal mode by LLD interface;
            1. Check the CCCR register flag whether has been changed or not.
            2. Disable configuration change CCCR.CCE = 0, CCCR.INIT = 0
    */
    /* #Violation: Can_c_REF_4*/
    ApiStatus = Can_Hal_ExitInitMode(CAN_BASE_ADDR(CoreId,ControllerToCore));

    if(CAN_STATUS_OK == ApiStatus)
    {
        /* SWS_Can_00196:
            Shall enable interrupts that are needed in the new state.*/
        /* SWS_Can_00425:
            Enabling of CAN interrupts shall not be executed, when CAN
            interrupts have been disabled by function Can_DisableControllerInterrupts. */
        if(((sint32)0 == CAN_CONTROLLER_STATUS(CoreId,ControllerToCore,DisableIntrpCount)) &&
           (CAN_INTERRUPT_ACTIVE == CAN_CONTROLLER_CFG(CoreId,ControllerToCore,InterruptState)))
        {
            CanRet = Can_EnableController_Interrupts(Controller);
#if (CAN_SAFETY_ENABLE == STD_ON)
            if (FALSE == CanRet)
            {
                /* Safety Error Tracer */
                (void)Det_ReportRuntimeError((uint16)CAN_MODULE_ID, \
                                             (uint8)CAN_INSTANCE_ID, \
                                             (uint8)CAN_SID_SET_CONTROLLER_MODE, \
                                             (uint8)CAN_E_ENABLE_CONTROLLER_INTERRUPTS);
            }
#endif /* (CAN_SAFETY_ENABLE \== STD_ON) */                    
        }

        /* Module interrupt register setup completed */
        if (TRUE == CanRet)
        {
            /* Get the Stm system clock frequency */
            /* #Violation: Can_c_REF_4 */
            TimerFreq = (uint64)Mcal_GetSystemTimerFreq();

            /* Calculate the count value required for delay *us */
            TimeOutCount = (CAN_TIMEOUT_LOOP_TIME * TimerFreq) / 1000000ULL;

            /* Calculate the timeout count value of delay *us */
            /* #Violation: Can_c_REF_4 */
            TimeOutCount += Mcal_GetSystemTimerCount();

            /* SWS_Can_00372:
                In case the flag signals that the change takes no effect and the maximum time
                CanTimeoutDuration is elapsed, the function Can_SetControllerMode shall be left
                and the function Can_Mainfunction_Mode shall continue to poll the flag. */
            do
            {
                /* Monitors the module's CAN communication state by Can_Hal_GetProtocolStatus
                Note:PSR.ACT Bits 4:3 ACT[1:0]: Activity
                    00 = Synchronizing - node is synchronizing on CAN communication
                    01 = Idle - node is neither receiver nor transmitter
                    10 = Receiver - node is operating as receiver
                    11 = Transmitter - node is operating as transmitter */
                /* #Violation: Can_c_REF_4 */
                ProtocolStatus = Can_Hal_GetProtocolStatus(CAN_BASE_ADDR(CoreId,ControllerToCore));

                /* SWS_Can_00261:
                    The function Can_SetControllerMode(CAN_CS_STARTED) shall set the hardware registers
                    in a way that makes the CAN controller participating on the network. */
                /* If the Can node is not in the 'synchronizing' state, it means that the CAN controller
                    is participatingon the network. */
                if(0UL != (CAN_PROTOCOL_ACT & ProtocolStatus)) 
                {
                    /* Set the current state to start */
                    CAN_CONTROLLER_STATUS(CoreId,ControllerToCore,CurrentStatus) = CAN_CS_STARTED;

                    /* SWS_Can_00373:
                        The function Can_Mainfunction_Mode shall call the function CanIf_ControllerModeIndication
                        to notify the upper layer about a successful state transition of the corresponding CAN
                        controller referred by abstract CanIf ControllerId,in case the state transition was
                        triggered by function Can_SetControllerMode. */
                    /*  SWS_Can_00370:
                            The function Can_Mainfunction_Mode shall poll a flag of the CAN status register
                            until the flag signals that the change takes effect and notify the upper layer
                            with function CanIf_ControllerModeIndication about a successful state transition
                            referring to the corresponding CAN controller with the abstract CanIf ControllerId.*/
                    CanIf_ControllerModeIndication(CAN_CONTROLLER_CFG(CoreId,ControllerToCore,LogicalID), 
                                                    CAN_CS_STARTED);
                }

                /* SWS_Can_00262:
                    The function Can_SetControllerMode(CAN_CS_STARTED) shall wait for limited time
                    until the CAN controller is fully operational. */
                /* Get the current count value of Stm */
                /* #Violation: Can_c_REF_4 */
                CurrentCount = Mcal_GetSystemTimerCount();

            }while ((CurrentCount < TimeOutCount) && (0UL == (CAN_PROTOCOL_ACT & ProtocolStatus)));
          
            /* SWS_Can_00262:
                Transmit requests that are initiated before the CAN controller is operational get lost.
                The only indicator for operability is the reception of TX confirmations or RX
                indications. The sending entities might get a confirmation timeout and need to be
                able to cope with that. */
            Ret = E_OK;
        }
    }

    return Ret;
}
/****************************************************************************************************
*   Function Name           : Can_CheckModeStop
*
*   Service ID              : None.
*
*   Description             : This function is used to set the controller to stop mode and then check
*                             the translation whether succeed or not.
*                     
*   Parameters in           : Controller: CAN controller for which the status shall be changed
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : E_OK: request accepted
*                             E_NOT_OK: request not accepted, a development error occurred
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Can_00272
****************************************************************************************************/
static FUNC(Std_ReturnType, CAN_PRIVATE_CODE) Can_CheckModeStop
(
    uint8 Controller
)
{
    Std_ReturnType   Ret;
    Can_HwHandleType Hoh;
    Can_HwHandleType HohToCore;
    Mcal_CoreType    CoreId;
    uint8            TxBufferIndex;
    uint8            ControllerToCore;
    Can_Status       ApiStatus;
    CAN_NODE         *CanNodePtr;
    boolean          CanRet;
    uint32           ProtocolStatus;

    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4*/
    CoreId = Mcal_GetCoreId();

    /* Get the controller config set index */
    ControllerToCore = Can_ConfigPtr->ControllerToCorePtr[Controller];

    /* Get the controller node address */
    /* #Violation: Can_c_REF_4 */
    CanNodePtr = CAN_BASE_ADDR(CoreId,ControllerToCore);

    /* The transition START -> STOP can also be triggered concurrently by a real bus-off event
       (Can_CheckBusOffEvent, called from Can_BusOff_IRQHandler or Can_MainFunction_BusOff), which
       can preempt at any point below (the abort loop and Can_Hal_EnterInitMode's hardware polling
       both take real time and are not protected). Atomically claim the transition here, before
       doing any of that work, under the same ModeTransition lock Can_CheckBusOffEvent() uses:
       whichever side observes CurrentStatus==STARTED first "wins" and proceeds; the other backs
       off immediately instead of redundantly aborting pending Tx requests and issuing a second
       CanIf_ControllerBusOff()/CanIf_ControllerModeIndication() notification for the same event. */
    CAN_ENTER_CRITICAL_SECTION(ModeTransition);
    if (CAN_CS_STARTED != CAN_CONTROLLER_STATUS(CoreId,ControllerToCore,CurrentStatus))
    {
        /* Bus-off already claimed and completed this transition -> the desired STOPPED state is
           already reached and already notified, nothing left to do here. */
        CAN_EXIT_CRITICAL_SECTION(ModeTransition);
        return E_OK;
    }
    CAN_CONTROLLER_STATUS(CoreId,ControllerToCore,CurrentStatus) = CAN_CS_STOPPED;
    CAN_EXIT_CRITICAL_SECTION(ModeTransition);

    /* Cancel all pending transmit request  */
    for(Hoh = 0U; Hoh < CAN_CORE_CFG(CoreId,MaxCoreHohChannels); Hoh++)
    {
        /* Convert hardware object ID to hardware object index. */
        HohToCore = CAN_CORE_CFG(CoreId,CanHohToCoreCfgPtr[Hoh]);

        /* SWS_Can_00282:
           The function Can_SetControllerMode(CAN_CS_STOPPED) shall cancel pending messages. */
        if((CAN_HWOBJ_CFG(HohToCore,ControllerId) == Controller) &&
                (CAN_TRANSMIT == CAN_HWOBJ_CFG(HohToCore,ObjectType)))
        {
            /* Get the hardware Object with index. */
            TxBufferIndex = CAN_HWOBJ_CFG(HohToCore, ElementsIndex);
            /* SWS_Can_00282:
            The function Can_SetControllerMode(CAN_T_STOP) shall cancel pending messages. */

            /* SWS_Can_00273:
                After bus-off detection, the Can module shall cancel still pending messages. */
            Can_Hal_AbortTxRequest(CanNodePtr, TxBufferIndex);
        }
    }

    /* SWS_Can_00197:
        The function Can_SetControllerMode shall disable interrupts that are not allowed in the new
       state. */
    /* SWS_Can_00426:
        Disabling of CAN interrupts shall not be executed, when CAN interrupts have been disabled by
       function Can_DisableControllerInterrupts. */
    /* SWS_Can_00274:
        The Can module shall disable or suppress automatic bus-off recovery.*/
    if(((sint32)0 == CAN_CONTROLLER_STATUS(CoreId,ControllerToCore,DisableIntrpCount)) && \
       (CAN_INTERRUPT_ACTIVE == CAN_CONTROLLER_CFG(CoreId,ControllerToCore,InterruptState)))
    {
        /* Disable all the Can Controller interrupts. */
        CanRet = Can_DisableController_Interrupts(Controller);
#if (CAN_SAFETY_ENABLE == STD_ON)
        if (FALSE == CanRet)
        {
            /* Safety Error Tracer */
            (void)Det_ReportRuntimeError((uint16)CAN_MODULE_ID, \
                                         (uint8)CAN_INSTANCE_ID, \
                                         (uint8)CAN_SID_SET_CONTROLLER_MODE, \
                                         (uint8)CAN_E_DISABLE_CONTROLLER_INTERRUPTS);
        }
#else
        /* Just avoid MISRAC Rules */
        (void)CanRet;
#endif /* (CAN_SAFETY_ENABLE \== STD_ON) */        
    }

    /* Set the Controller into the STOP mode,
       For many controllers entering an 'initialization'-mode causes the controller to be stopped.*/
    /* SWS_Can_00263:
       The function Can_SetControllerMode(CAN_CS_STOPPED) shall set the bits inside the CAN hardware
       such that the CAN controller stops participating on the network. */
    /* SWS_Can_00264:
       The function Can_SetControllerMode(CAN_CS_STOPPED) shall wait for a limited time, until the
       CAN controller is really switched off.  */
    /* Set the Controller to an inactive state */
    ApiStatus = Can_Hal_EnterInitMode(CanNodePtr);

    /* Check the CCCR.CCE is set? */
    if(CAN_STATUS_OK == ApiStatus)
    {
        /* CurrentStatus was already claimed as CAN_CS_STOPPED above (under ModeTransition lock,
           before this hardware work started) -- no need to set it again here. */

        /* Check the controller is happened BUSOFF event by Can_Hal_GetProtocolStatus
        Note: Bus off notification to application will be provided only once */
        ProtocolStatus = Can_Hal_GetProtocolStatus(CanNodePtr);
        if(0U == (CAN_PROTOCOL_BO & ProtocolStatus))
        {
            CanIf_ControllerModeIndication(Controller, CAN_CS_STOPPED);
        }
        /* If the state translate to stop is result of BUSOFF, then call the CanIf_ControllerBusOff */
        else
        {
            /* SWS_Can_00020:
                State transition caused by Bus-Off (triggered by state change of CAN controller)
                3. The CanIf module is notified with the function CanIf_ControllerBusOff after
                    STOPPED state is reached referring to the corresponding CAN controller with the
                    abstract CanIf ControllerId. (SRS_Can_01055)State transition caused by Bus-Off */
            CanIf_ControllerBusOff(Controller);
        }

        Ret = E_OK;
    }
    else
    {
        /* Hardware never actually reached STOPPED: roll back the early claim so a later retry of
           Can_SetControllerMode(CAN_CS_STOPPED), or a genuine bus-off, can still claim this
           transition. Safe without the lock: nothing else can have taken this transition while
           CurrentStatus reads non-STARTED (see the claim above), so no one else is racing on it
           right now either. */
        CAN_CONTROLLER_STATUS(CoreId,ControllerToCore,CurrentStatus) = CAN_CS_STARTED;
        Ret = E_NOT_OK;
    }

    return Ret;
}
#if(CAN_WAKEUP_SUPPORT == STD_ON)
/****************************************************************************************************
*   Function Name           : Can_CheckModeSleep
*
*   Service ID              : None.
*
*   Description             : This function is used to set the controller to sleep mode and then
*                             check the translation whether succeed or not.
*                     
*   Parameters in           : Controller: CAN controller for which the status shall be changed
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : E_OK: request accepted
*                             E_NOT_OK: request not accepted, a development error occurred
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, CAN_PRIVATE_CODE) Can_CheckModeSleep
(
    uint8 Controller
)
{
    Std_ReturnType Ret;
    Mcal_CoreType  CoreId;
    Can_Status     ApiStatus;
    uint8          ControllerToCore;

    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4*/
    CoreId = Mcal_GetCoreId();

    /* Get the controller config set index */
    ControllerToCore = Can_ConfigPtr->ControllerToCorePtr[Controller];

    /* SWS_Can_00404:
       The CAN hardware shall remain in state STOPPED, while the logical SLEEP state is active. */
    /* #Violation: Can_c_REF_4*/
    ApiStatus = Can_Hal_EnterPowerDownMode(CAN_BASE_ADDR(CoreId,ControllerToCore));

    if(CAN_STATUS_OK == ApiStatus)
    {
        /* SWS_Can_00258:
           When the CAN hardware does not support sleep mode and is triggered to transition
           into SLEEP state,the Can module shall emulate a logical SLEEP state from which it
           returns only, when it is triggered by software to transition into STOPPED state.*/
        /* Set the current state to sleep */
        CAN_CONTROLLER_STATUS(CoreId,ControllerToCore,CurrentStatus) = CAN_CS_SLEEP;

        /* SWS_Can_00373:
            notify the upper layer about a successful state
            transition of the corresponding CAN controller */
        CanIf_ControllerModeIndication(Controller, CAN_CS_SLEEP);

        Ret = E_OK;
    }
    else
    {
        Ret = E_NOT_OK;
    }

    return Ret;
}
#endif /* (CAN_WAKEUP_SUPPORT  \== STD_ON) */
/****************************************************************************************************
*   Function Name           : Can_CheckBusOffEvent
*
*   Service ID              : None.
*
*   Description             : This function is used to check the Controller is happened BusOff event
*                             or not.
*
*   Parameters in           : Controller: CAN controller for which check the BUSOFF processing.
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
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : None
****************************************************************************************************/
static FUNC(void, CAN_PRIVATE_CODE) Can_CheckBusOffEvent
(
    uint8 Controller
)
{
    uint32           ProtocolStatus;
    Mcal_CoreType    CoreId;
    uint8            ControllerToCore;
    Can_HwHandleType Hoh;
    Can_HwHandleType HohToCore;
    uint8            TxBufferIndex;
    CAN_NODE         *CanNodePtr;
    
    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4*/
    CoreId = Mcal_GetCoreId();

    /* Get the controller config set index */
    ControllerToCore = Can_ConfigPtr->ControllerToCorePtr[Controller];

    /* Get the controller node address */
    /* #Violation: Can_c_REF_4*/
    CanNodePtr = CAN_BASE_ADDR(CoreId,ControllerToCore);

    /* Check the controller is happened BUSOFF event by Can_Hal_GetProtocolStatus
       Note: Bus off notification to application will be provided only once */
    ProtocolStatus = Can_Hal_GetProtocolStatus(CanNodePtr);

    /* The transition START -> STOP is done by the following triggers:
        - Can_SetControllerMode(CAN_CS_STOPPED)
        - Bus-off
        To avoid the state transition is done twice by both of triggers,
        the exclusive control is required.
        If the state transition START to STOP has been started by Can_SetControllerMode,
        just clear error flags and do nothing further operations.
    */
    /* Claim the transition atomically under the same ModeTransition lock Can_CheckModeStop()
       uses: only the side that observes CurrentStatus==STARTED here proceeds to abort pending Tx
       requests and notify CanIf; the loser backs off, avoiding a duplicate
       CanIf_ControllerBusOff() call for the same physical bus-off event. */
    CAN_ENTER_CRITICAL_SECTION(ModeTransition);
    if((0U != (CAN_PROTOCOL_BO & ProtocolStatus)) \
        && (CAN_CS_STARTED == CAN_CONTROLLER_STATUS(CoreId,ControllerToCore,CurrentStatus)))
    {
        /* SWS_Can_00020:
            State transition caused by Bus-Off (triggered by state change of CAN controller)
            1. STARTED ----> STOPPED*/
        /* SWS_Can_00272:
            After bus-off detection, the CAN controller shall transition to the state STOPPED and the
           Can module shall ensure that the CAN controller doesn't participate on the network
           anymore. */
        /* Set controller mode with STOP state */
        CAN_CONTROLLER_STATUS(CoreId,ControllerToCore,CurrentStatus) = CAN_CS_STOPPED;
        CAN_EXIT_CRITICAL_SECTION(ModeTransition);

        /* Cancel all pending transmit request  */
        for(Hoh = 0U; Hoh < CAN_CORE_CFG(CoreId,MaxCoreHohChannels); Hoh++)
        {
            /* Convert hardware object ID to hardware object index. */
            HohToCore = CAN_CORE_CFG(CoreId,CanHohToCoreCfgPtr[Hoh]);

            /* Check if the canceled function belongs to the current Controller */
            if((CAN_HWOBJ_CFG(HohToCore,ControllerId) == Controller) &&
                (CAN_TRANSMIT == CAN_HWOBJ_CFG(HohToCore,ObjectType)))
            {
                /* Get the hardware Object with index. */
                TxBufferIndex = CAN_HWOBJ_CFG(HohToCore, ElementsIndex);
                /* SWS_Can_00282:
                The function Can_SetControllerMode(CAN_T_STOP) shall cancel pending messages. */
                Can_Hal_AbortTxRequest(CanNodePtr, TxBufferIndex);
            }
        }

        /* SWS_Can_00020: State transition caused by Bus-Off */
        CanIf_ControllerBusOff(Controller);
    }
    else
    {
        /* Either no bus-off is actually pending, or Can_CheckModeStop() already claimed this
           transition -> nothing further to do here, avoids a duplicate notification. */
        CAN_EXIT_CRITICAL_SECTION(ModeTransition);
    }
}
/****************************************************************************************************
*   Function Name           : Can_SetControllerModeToStart
*
*   Service ID              : None.
*
*   Description             : This function is used to translate the Mode to start mode.
*                     
*   Parameters in           : Controller: CAN controller for which the status shall be changed
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : E_OK: request accepted
*                             E_NOT_OK: request not accepted, a development error occurred
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, CAN_PRIVATE_CODE) Can_SetControllerModeToStart
(
    uint8 Controller
)
{
    Std_ReturnType Ret;
    Mcal_CoreType CoreId;
    uint8 ControllerToCore;

    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4*/
    CoreId = Mcal_GetCoreId();

    /* Get the controller config set index */
    ControllerToCore = Can_ConfigPtr->ControllerToCorePtr[Controller];

    /* Set E_NOT_OK as default */
    Ret = E_NOT_OK;

    /* SWS_Can_00409:
        When the function Can_SetControllerMode (CAN_CS_STARTED) is entered and the CAN
        controller is not in state STOPPED it shall detect a invalid state transition */
    if (CAN_CS_STOPPED == CAN_CONTROLLER_STATUS(CoreId,ControllerToCore,CurrentStatus))
    {
        /* SWS_Can_00261:
            The function Can_SetControllerMode(CAN_CS_STARTED) shall set the hardware registers in a
           way that makes the CAN controller participating on the network. */
        /* SWS_Can_00384:
           Each time the CAN controller state machine is triggered with the state transition value
           CAN_CS_STARTED, the function Can_SetControllerMode shall re-initialize the CAN controller
           with the same controller configuration set previously used by functions Can_SetBaudrate or
           Can_Init. */

        /* SWS_Can_00425:
            Enabling of CAN interrupts shall not be executed, when CAN interrupts have been disabled
           by function Can_DisableControllerInterrupts. INFO: API Can_InitController() only Only
           configuring interrupt routing will not enable interrupts */
        Ret = Can_InitController(Controller);

        /* Check InitController succeed? */
        /* SWS_Can_00262:
            The function Can_SetControllerMode(CAN_CS_STARTED) shall wait for limited time until the
           CAN controller is fully operational. */
        if(E_OK == Ret)
        {
            /* Go to start mode and check whether has been entered or not. */
            Ret = Can_CheckModeStart(Controller);
        }
    }
#if (CAN_DEV_ERROR_DETECT == STD_ON)
    else
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_SET_CONTROLLER_MODE, \
                              (uint8)CAN_E_TRANSITION);
    }
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
    return Ret;
}
/****************************************************************************************************
*   Function Name           : Can_SetControllerModeToStop
*
*   Service ID              : None.
*
*   Description             : This function is used to translate the Mode to Stop mode.
*                     
*   Parameters in           : Controller: CAN controller for which the status shall be changed
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : E_OK: request accepted
*                             E_NOT_OK: request not accepted, a development error occurred
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, CAN_PRIVATE_CODE) Can_SetControllerModeToStop
(
    uint8 Controller
)
{
    Std_ReturnType Ret;

    /* SWS_Can_00268:
        The function Can_SetControllerMode(CAN_CS_STOPPED) shall wait for a limited time until the
       CAN controller is in STOPPED state. */

    /* After initialization is completed, any state can be switched to SLEEP state. */
    Ret = Can_CheckModeStop(Controller);

    return Ret;
}
/****************************************************************************************************
*   Function Name           : Can_SetControllerModeToSleep
*
*   Service ID              : None.
*
*   Description             : This function is used to translate the Mode to Sleep mode.
*                     
*   Parameters in           : Controller: CAN controller for which the status shall be changed
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : E_OK: request accepted
*                             E_NOT_OK: request not accepted, a development error occurred
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, CAN_PRIVATE_CODE) Can_SetControllerModeToSleep
(
    uint8 Controller
)
{
    Std_ReturnType Ret;
    Mcal_CoreType  CoreId;
    uint8          ControllerToCore;

    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4*/
    CoreId = Mcal_GetCoreId();

    /* Get the controller config set index */
    ControllerToCore = Can_ConfigPtr->ControllerToCorePtr[Controller];

    /* Set E_NOT_OK as default */
    Ret = E_NOT_OK;
    
    /* SWS_Can_00411:
       When the function Can_SetControllerMode(CAN_CS_SLEEP) is entered and the CAN controller is
       neither in state STOPPED nor in state SLEEP, it shall detect a invalid state transition */
    if (CAN_CS_STARTED != CAN_CONTROLLER_STATUS(CoreId,ControllerToCore,CurrentStatus))
    {
        /* SWS_Can_00266:
           If the CAN HW does support a sleep mode, the function Can_SetControllerMode(CAN_CS_SLEEP)
           shall wait for a limited time until the CAN controller is in SLEEP state and it is assured
           that the CAN hardware is wake able. */
        /* Support software sleep */
#if(CAN_WAKEUP_SUPPORT == STD_OFF)
        Ret = E_OK;
        /* SWS_Can_00290:
           If the CAN HW does not support a sleep mode, the function Can_SetControllerMode
           (CAN_CS_SLEEP) shall set the CAN controller to the logical sleep mode */
        /* SWS_Can_00405:
            This logical sleep mode shall left only, if function
           Can_SetControllerMode(CAN_CS_STOPPED) is called. */
        CAN_CONTROLLER_STATUS(CoreId,ControllerToCore,CurrentStatus) = CAN_CS_SLEEP;
        CAN_CONTROLLER_STATUS(CoreId,ControllerToCore,WakeupState)   = CAN_NOT_WAKEUP;

        /* \[SWS_Can_00370]:
            Notify the upper layer with function CanIf_ControllerModeIndication
            about a successful state transition */
        CanIf_ControllerModeIndication(Controller, CAN_CS_SLEEP);
#else
        Ret = Can_CheckModeSleep(Controller);
#endif /* (CAN_WAKEUP_SUPPORT  \== STD_OFF) */
    }
#if (CAN_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Can_00411:
       When the function Can_SetControllerMode(CAN_CS_SLEEP) is entered and the CAN controller is
       neither in state STOPPED nor in state SLEEP, it shall detect a invalid state transition */
    else
    {
        /* Valid transitions to Sleep state are only from Stop state. */
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_SET_CONTROLLER_MODE, \
                              (uint8)CAN_E_TRANSITION);
    }
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */  

    return Ret;
}

#if (CAN_DEV_ERROR_DETECT == STD_ON)
#if (CAN_SET_BAUDRATE_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Can_SetBaudrateDetCheck
*
*   Service ID              : 0x0F.
*
*   Description             : Check Det error for Can_SetBaudrate API.
*                     
*   Parameters in           : Controller: CAN controller, whose baud rate shall be set.
*                             BaudRateConfigID: references a baud rate configuration by ID, 
*                             see CanControllerBaudRateConfigID
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : None.
*
*   Return value            : E_OK : DET exists;
*                             E_NOT_OK : DET not exists.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, CAN_PRIVATE_CODE) Can_SetBaudrateDetCheck
(
    uint8 Controller, 
    Mcal_CoreType  CoreId
)
{
    Std_ReturnType Ret;

    Ret = E_NOT_OK;
    /* SWS_Can_00492:
        If development error detection for the Can module is enabled: The function Can_SetBaudrate
       shall raise the error CAN_E_UNINIT and return E_NOT_OK if the driver is not yet initialized.
     */
    if((NULL_PTR ==(Can_CoreStateArray[CoreId]))|| \
       (CAN_UNINIT == *(Can_CoreStateArray[CoreId]->CanInitStatusPtr)))
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_SET_BAUDRATE, \
                              (uint8)CAN_E_UNINIT);
    }

    /* SWS_Can_00494:
        If development error detection for the Can module is enabled the function Can_SetBaudrate
       shall raise the error CAN_E_PARAM_CONTROLLER and return E_NOT_OK if the parameter Controller
       is out of range. */
    else if(Controller >= CAN_USED_CONTROLLER_MAX_NUM)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_SET_BAUDRATE, \
                              (uint8)CAN_E_PARAM_CONTROLLER);
    }

    /* Non-AUTOSAR:
        CAN Controller is not allocated to current core.*/
    else if(CoreId != (Can_ConfigPtr->ControllerMapListPtr[Controller]))
    {
        /* Not Can Controller configured in current core */
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_SET_BAUDRATE, \
                              (uint8)CAN_E_CORE_CONTROLLER_MISMATCH);
    }
    else
    {
        Ret = E_OK;
    }

    return Ret;
}
#endif /* (CAN_SET_BAUDRATE_API  \== STD_ON) */
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : Can_Init
*
*   Service ID              : 0x00.
*
*   Description             : This function initializes the module.  
*                     
*   Parameters in           : ConfigPtr: Pointer to driver configuration.
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
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Can_00236 SWS_Can_00239 SWS_Can_00250 SWS_Can_00053 SWS_Can_00407
                              SWS_Can_00056 SWS_Can_00021 SWS_Can_00291 SWS_Can_00233
****************************************************************************************************/
/* #Violation: Can_c_REF_6 */
FUNC(void, CAN_PUBLIC_CODE) Can_Init
(
    CONSTP2CONST(Can_ConfigType, AUTOMATIC, CAN_APPL_CONST) ConfigPtr
)
{
    uint8           Index;
    Mcal_CoreType   CoreId;
    Std_ReturnType  Ret;

    Ret = E_OK;

    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4*/
    CoreId = Mcal_GetCoreId();

#if(CAN_DEV_ERROR_DETECT == STD_ON)
    /* Non-AUTOSAR:
        API Service called with wrong parameter: Config is a null pointer.*/
    if(NULL_PTR == ConfigPtr)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID,\
                              (uint8)CAN_SID_INIT, \
                              (uint8)CAN_E_PARAM_POINTER);
    }   
    /* Non-AUTOSAR:
        The current core is not used, check the controller configuration.*/
    else if(NULL_PTR == ConfigPtr->CoreConfigPtr[CoreId])
    {
        
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                                (uint8)CAN_INSTANCE_ID, \
                                (uint8)CAN_SID_INIT, \
                                (uint8)CAN_E_CORE_NOT_CONFIGURED);
    }

    /* SWS_Can_00174:
        Shall raise the error CAN_E_TRANSITION if the driver is not in state CAN_UNINIT. */
    /* SWS_Can_00408:
        Shall raise the error CAN_E_TRANSITION if the CAN controllers are not in state CAN_UNINIT. */
    else if (CAN_UNINIT != *(Can_CoreStateArray[CoreId]->CanInitStatusPtr))
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID,\
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_INIT, \
                              (uint8)CAN_E_TRANSITION);
    }     
    else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */    
    {
        /* Copy pointer to current Can Driver configuration.
           Can_ConfigPtr is a single global (not one per core, unlike Can_CoreStateArray), and
           every core calls Can_Init() independently at startup -- protect the write so two cores
           initializing back-to-back don't race on it. Note: SchM_Enter/Exit_Can_Init are, like the
           rest of SchM_Can.c, only a same-core SuspendAllInterrupts()/ResumeAllInterrupts() pair;
           closing this gap for a true multi-core race still requires a real cross-core lock. */
        CAN_ENTER_CRITICAL_SECTION(Init);
        Can_ConfigPtr = ConfigPtr;
        CAN_EXIT_CRITICAL_SECTION(Init);

        /* SWS_Can_00443:
            The L-PDU-Callout API shall be invoke. */
#if (CAN_LPDU_CALLOUT_FUNCTION_SUPPORT == STD_ON)
        (void)Can_Callout_Data_Init();
#endif /* (CAN_LPDU_CALLOUT_FUNCTION_SUPPORT  \== STD_ON) */

        /* SWS_Can_00245:
            The function Can_Init shall initialize all CAN controllers according to their
           configuration. */
        /* SWS_Can_00250:
                The function Can_Init shall initialize:static variables, including flags,Common
           setting for the complete CAN HW unit CAN controller specific settings for each CAN
           controller */
        for (Index = 0U; (Index < CAN_CORE_CFG(CoreId, MaxCoreController)) && (E_OK == Ret); Index++)
        {
            /* Reset default baud rate configuration */
            CAN_CONTROLLER_STATUS(CoreId, Index, BaudrateIndexCfg) =
                CAN_CONTROLLER_CFG(CoreId, Index, DefaultBaudrate);

            /* Clean the interrupt count */
            CAN_CONTROLLER_STATUS(CoreId,Index,DisableIntrpCount) = (sint32)0;

            /* Reset wakeup type and status */
#if (CAN_WAKEUP_SUPPORT == STD_ON)
            CAN_CONTROLLER_STATUS(CoreId,Index,WakeupType) = DEFAULT_STATE;
            CAN_CONTROLLER_STATUS(CoreId,Index,WakeupState) = CAN_NOT_WAKEUP;
#endif /* (CAN_WAKEUP_SUPPORT  \== STD_ON) */

            /* SWS_Can_00259:
                The function Can_Init shall set all CAN controllers in the state STOPPED. */
            CAN_CONTROLLER_STATUS(CoreId,Index,CurrentStatus) = CAN_CS_STOPPED;

            /* SWS_Can_00053:
                Can_Init shall not change registers of CAN controller Hardware resources that are not
               used. */
            if(TRUE == CAN_CONTROLLER_CFG(CoreId,Index,Activation))
            {
                /* Initialize the CAN controller */
                Ret = Can_InitController(CAN_CONTROLLER_CFG(CoreId,Index,LogicalID));

#if (CAN_SAFETY_ENABLE == STD_ON)
                if (E_NOT_OK == Ret)
                {
                    /* Safety Error Tracer */
                    (void)Det_ReportRuntimeError((uint16)CAN_MODULE_ID, \
                                                 (uint8)CAN_INSTANCE_ID, \
                                                 (uint8)CAN_SID_INIT, \
                                                 (uint8)CAN_E_INIT_FAILED);
                }
#endif /* (CAN_SAFETY_ENABLE \== STD_ON) */    
            }
        }

        /* SWS_Can_00246:
            The function Can_Init shall change the module state to CAN_READY, after initializing all
           controllers inside the HW Unit. */
        if (E_OK == Ret)
        {
            *(Can_CoreStateArray[CoreId]->CanInitStatusPtr) = CAN_READY;
        }
        else
        {
            *(Can_CoreStateArray[CoreId]->CanInitStatusPtr) = CAN_UNINIT;
        }
    }
}

/****************************************************************************************************
*   Function Name           : Can_DeInit
*
*   Service ID              : 0x01
*
*   Description             : Service for Can de-initialization.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : E_OK: de-initialisation command has been accepted.
*                             E_NOT_OK: de-initialisation command has not been accepted.
*
*   Preconditions           : Can driver must be initialized.
*
*                             Caller of the Can_DeInit function has to be sure no CAN controller
*                             is in the state STARTED.
*
*                             SWS_BSW_00152: Call to De-Initialization functions is restricted
*                             Only the ECU State Manager and Basic Software Mode Manager are
*                             allowed to call De-Initialization functions.
*
*                             SWS_BSW_00232: Call to De-Initialization functions The module
*                             De-Initialization function shall be called only if the module was
*                             initialized before (initialization function was called).
*                          
*   AUTOSAR_Requirement     : SWS_Can_91002
****************************************************************************************************/
/* #Violation: Can_c_REF_6 */
FUNC(Std_ReturnType, CAN_CODE) Can_DeInit
(
    void
)
{
    Mcal_CoreType   CoreId;
    Can_Status      ApiStatus;
    Std_ReturnType  RetStatus;
    uint8           Index;

    RetStatus = E_OK;
    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4*/
    CoreId = Mcal_GetCoreId();

    /* SWS_Can_91011:
        The function Can_DeInit shall raise the error CAN_E_TRANSITION if the driver is not in state
       CAN_READY. */
    if (CAN_READY != *(Can_CoreStateArray[CoreId]->CanInitStatusPtr))
    {
#if(CAN_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_DEINIT, \
                              (uint8)CAN_E_TRANSITION);
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */   
        RetStatus = E_NOT_OK;
    }   
    else 
    {
        /* Traverse all controllers and initialize with the configurations */
        for (Index = 0U; (Index < CAN_CORE_CFG(CoreId, MaxCoreController)) && (E_OK == RetStatus);
             Index++)
        {

            /* SWS_Can_91012:
                The function Can_DeInit shall raise the error CAN_E_TRANSITION if any of the CAN
               controllers is in state STARTED. */
            /* SWS_Can_91002:
                Caller of the Can_DeInit function has to be sure no CAN controller is in the state
               STARTED.
            */
            if (CAN_CS_STARTED == CAN_CONTROLLER_STATUS(CoreId,Index,CurrentStatus))
            {
#if(CAN_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                                    (uint8)CAN_INSTANCE_ID, \
                                    (uint8)CAN_SID_DEINIT, \
                                    (uint8)CAN_E_TRANSITION);
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */   
                RetStatus = E_NOT_OK;
            }
            if ((TRUE == CAN_CONTROLLER_CFG(CoreId,Index,Activation)) && (E_OK == RetStatus))
            {
                /* Reset the registers of CAN controller */
                /* #Violation: Can_c_REF_4*/
                ApiStatus = Can_Hal_Deinit(CAN_BASE_ADDR(CoreId,Index));
                if(CAN_STATUS_OK == ApiStatus)
                {
                    /* 7.3.1 CAN Controller State Description
                    - The CAN controller is not initialized.
                    - All registers of the CAN module are in reset state, 
                        CAN interrupts are disabled.
                    - The CAN Controller is not participating on the CAN bus. */
                    /* SWS_Can_91010:
                        The function Can_DeInit shall set all CAN controllers in the state UNINIT.
                        */
                    CAN_CONTROLLER_STATUS(CoreId,Index,CurrentStatus) = CAN_CS_UNINIT;
                }
                else
                {
#if (CAN_SAFETY_ENABLE == STD_ON)
                    /* Safety Error Tracer */
                    (void)Det_ReportRuntimeError((uint16)CAN_MODULE_ID, \
                                                 (uint8)CAN_INSTANCE_ID, \
                                                 (uint8)CAN_SID_DEINIT, \
                                                 (uint8)CAN_E_INIT_FAILED);
#endif /* (CAN_SAFETY_ENABLE \== STD_ON) */

                    /* Break if any controller fails to reverse initialization */
                    RetStatus = E_NOT_OK;
                }
            }
        }
        if(E_OK == RetStatus)
        {
            /* SWS_Can_91009:
                The function Can_DeInit shall change the module state to CAN_UNINIT before
               de-initializing all controllers inside the HW unit. */
            *(Can_CoreStateArray[CoreId]->CanInitStatusPtr) = CAN_UNINIT;
        }
    }

    return RetStatus;
}

#if (CAN_VERSION_INFO_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Can_GetVersionInfo
*
*   Service ID              : 0x07.
*
*   Description             : This function returns the version information of this module. 
*                     
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : VersioninfoPtr: Pointer to where to store the version information
*                                             of this module.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant
*
*   Return value            : None. 
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Can_00224
****************************************************************************************************/
/* #Violation: Can_c_REF_6 */
FUNC(void, CAN_PUBLIC_CODE) Can_GetVersionInfo
(
    CONSTP2VAR(Std_VersionInfoType, AUTOMATIC, CAN_APPL_DATA) VersioninfoPtr
)
{
#if (CAN_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Can_00177:
         If development error detection for the Can module is enabled:The function Can_GetVersionInfo
       shall raise the error CAN_E_PARAM_POINTER if the parameter versionInfo is a null pointer. */
    if (NULL_PTR == VersioninfoPtr)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_GET_VERSION_INFO, \
                              (uint8)CAN_E_PARAM_POINTER);
    }
    else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */    
    {
        VersioninfoPtr->vendorID         = (uint16)CAN_VENDOR_ID;
        VersioninfoPtr->moduleID         = (uint16)CAN_MODULE_ID;
        VersioninfoPtr->sw_major_version = (uint8)CAN_SW_MAJOR_VERSION;
        VersioninfoPtr->sw_minor_version = (uint8)CAN_SW_MINOR_VERSION;
        VersioninfoPtr->sw_patch_version = (uint8)CAN_SW_PATCH_VERSION;
    }
}
#endif /* (CAN_VERSION_INFO_API  \== STD_ON) */

#if (CAN_SET_BAUDRATE_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Can_SetBaudrate
*
*   Service ID              : 0x0F.
*
*   Description             : This service shall set the baud rate configuration of the CAN
*                             controller. Depending on necessary baud rate modifications the
*                             controller might have to reset.
*                     
*   Parameters in           : Controller: CAN controller, whose baud rate shall be set.
*                             BaudRateConfigID: references a baud rate configuration by ID, 
*                             see CanControllerBaudRateConfigID
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant for different Controllers. Non reentrant for the
*                             same Controller.
*
*   Return value            : E_OK: Service request accepted, setting of (new) baud rate started
*                             E_NOT_OK: Service request not accepted
*
*   Preconditions           : The CAN controller must be in state STOPPED when this function is
*                             called.
*
*   AUTOSAR_Requirement     : SWS_Can_00491
****************************************************************************************************/
/* #Violation: Can_c_REF_6 */
FUNC(Std_ReturnType, CAN_PUBLIC_CODE) Can_SetBaudrate
(
    uint8 Controller, 
    uint16 BaudRateConfigID
)
{
    Std_ReturnType Ret;
    uint8          Index;
    uint8          ControllerToCore;
    Mcal_CoreType  CoreId;
    CAN_NODE       *CanNodePtr;
    boolean        CanRet;
        
#if (CANFD_MODE_SUPPORT == STD_ON)
    Can_Status     ApiStatus;
#endif /* (CANFD_MODE_SUPPORT  \== STD_ON) */

    CanRet = TRUE;

    /* SWS_Can_00500:
        If the requested baud rate change can not performed without a re-initialization
        of the CAN Controller E_NO_OK shall be returned. 
    */
    Index = 0U;
    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4*/
    CoreId = Mcal_GetCoreId();

#if (CAN_DEV_ERROR_DETECT == STD_ON)
    Ret = Can_SetBaudrateDetCheck(Controller, CoreId);
    if (E_OK == Ret)
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
    {
        Ret = E_NOT_OK;
        /* Get the controller to current core map. */
        ControllerToCore = Can_ConfigPtr->ControllerToCorePtr[Controller];

        /* Get the controller node address */
        /* #Violation: Can_c_REF_4*/
        CanNodePtr = CAN_BASE_ADDR(CoreId,ControllerToCore);

        /* Non-AUTOSAR:
            CAN Controller allocated to current core is not activated. */
        if(FALSE == Can_ConfigPtr->CoreConfigPtr[CoreId]-> \
                        CanControllerCfgPtr[ControllerToCore].Activation)
        {
#if (CAN_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                                  (uint8)CAN_INSTANCE_ID, \
                                  (uint8)CAN_SID_SET_BAUDRATE, \
                                  (uint8)CAN_E_PARAM_CONTROLLER);
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
        }
        /* SWS_Can_00256:
            If the call of Can_SetBaudrate() would cause a re-initialization of the CAN Controller
           and the CAN Controller is not in state STOPPED, it shall return E_NOT_OK.
        */
        else if(CAN_CS_STOPPED != Can_CoreStateArray[CoreId]-> \
                                   ControllerStatusPtr[ControllerToCore].CurrentStatus)
        {
#if (CAN_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                                  (uint8)CAN_INSTANCE_ID, \
                                  (uint8)CAN_SID_SET_BAUDRATE, \
                                  (uint8)CAN_E_TRANSITION);
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
        }
        else
        {
            /* Check the baudrate index which is belong to the Controller. */
            while((Ret == E_NOT_OK) && \
                  (Index < CAN_CONTROLLER_CFG(CoreId,ControllerToCore,NumberofBaudrate)))
            {
                if(BaudRateConfigID == CAN_BAUDRATE_CFG(CoreId,ControllerToCore,Index,BaudRateCfgID))
                {
                    /* Set the default baudrate index to global buffer. */
                    CAN_CONTROLLER_STATUS(CoreId,ControllerToCore,BaudrateIndexCfg) = Index;

                    Ret = E_OK;
                }
                else
                {
                    Index++;
                }
            }

            /* SWS_Can_00493:
                Shall raise the error CAN_E_PARAM_BAUDRATE and return E_NOT_OK,
                if the parameter BaudRateConfigID has an invalid value. */
            if(Ret != E_OK)
            {
#if (CAN_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                                      (uint8)CAN_INSTANCE_ID, \
                                      (uint8)CAN_SID_SET_BAUDRATE, \
                                      (uint8)CAN_E_PARAM_BAUDRATE);
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
            }
            else
            {
                /* Multiple API interface return values need to be processed
                   and the default E_NOT-OK can simplify the code logic. */
                Ret = E_NOT_OK;
                /* SWS_Can_00062:
                    If Can_SetBaudrate determines that the aimed configuration change requires a
                   re-initialization and the CAN Controller is in STOPPED, the function
                   Can_SetBaudrate shall re-initialize the CAN controller and the controller specific
                   settings.
                */
                /* SWS_Can_00255:
                    The function Can_SetBaudrate shall only affect register areas that contain
                   specific configuration for a single CAN controller.
                */
                /* The CAN Controller is aready in STOPPED(CCCR.INIT = 1 && CCCR.CCE = 1)
                   So there is no need to actively call and enter the initialization state. */

                /* Initialize nominal bit timing and pre-scaler */
                CanRet &= Can_Hal_ConfigBaudrate(CanNodePtr,\
                    (const Can_BaudRate *)&CAN_BAUDRATE_CFG(CoreId,ControllerToCore,Index,BaudrateParam));

#if (CANFD_MODE_SUPPORT == STD_ON)
                /* Check the timing bit rate switch is enable? */
                if(TRUE == CANFD_BAUDRATE_CFG(CoreId,ControllerToCore,Index,TBRS))
                {
                    /* Initialize data bit timing and pre-scaler */
                    CanRet &= Can_Hal_ConfigFastBaudrate(CanNodePtr,\
                                (const Can_FastBaudRate *)&CANFD_BAUDRATE_CFG(CoreId,ControllerToCore,Index,DataBaudRate));

                    /* Enable bit rate switching */
                    ApiStatus = Can_Hal_ConfigFrameFormat(CanNodePtr,CAN_FRAME_FORMAT_FDFAST);
                }
                else
                {
                    /* Enable CANFD without bit rate switching */
                    ApiStatus = Can_Hal_ConfigFrameFormat(CanNodePtr,CAN_FRAME_FORMAT_FD_NO_BRS);
                }
                if((CAN_STATUS_OK == ApiStatus) && (TRUE == CanRet))
#else
                if(TRUE == CanRet)
#endif /* (CANFD_MODE_SUPPORT  \== STD_ON) */
                {
                    Ret = E_OK;
                }
            }
        }
    }
    return Ret;
}
#endif /* (CAN_SET_BAUDRATE_API  \== STD_ON) */

/****************************************************************************************************
*   Function Name           : Can_SetControllerMode
*
*   Service ID              : 0x03.
*
*   Description             : This function performs software triggered state transitions of the CAN 
*                             controller State machine.
*                     
*   Parameters in           : Controller: CAN controller for which the status shall be changed
*                             Transition: Transition value to request new CAN controller state
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : E_OK: request accepted
*                             E_NOT_OK: request not accepted, a development error occurred
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Can_00245 SWS_Can_00230
****************************************************************************************************/
/* #Violation: Can_c_REF_6 */
FUNC(Std_ReturnType, CAN_PUBLIC_CODE) Can_SetControllerMode
(
    uint8 Controller, 
    Can_ControllerStateType Can_Transition
)
{
    Std_ReturnType Ret;
#if (CAN_DEV_ERROR_DETECT == STD_ON)
    uint8         ControllerToCore;
    Mcal_CoreType CoreId;
    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4 */
    CoreId = Mcal_GetCoreId();
    /* Set E_NOT_OK as default */
    Ret = E_NOT_OK;
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */


#if (CAN_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Can_00198:
        If development error detection for the Can module is enabled: if the module is not yet
       initialized, the function Can_SetControllerMode shall raise development error CAN_E_UNINIT and
       return E_NOT_OK. */
    if((NULL_PTR ==(Can_CoreStateArray[CoreId]))|| \
       (CAN_UNINIT == *(Can_CoreStateArray[CoreId]->CanInitStatusPtr)))
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_SET_CONTROLLER_MODE, \
                              (uint8)CAN_E_UNINIT);
    }

    /* SWS_Can_00199:
        If development error detection for the Can module is enabled: if the parameter Controller is
       out of range, the function Can_SetControllerMode shall raise development error
       CAN_E_PARAM_CONTROLLER and return E_NOT_OK. */
    else if(Controller >= CAN_USED_CONTROLLER_MAX_NUM)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_SET_CONTROLLER_MODE, \
                              (uint8)CAN_E_PARAM_CONTROLLER);
    }

    /* Non-AUTOSAR:
        CAN Controller is not allocated to current core.*/
    else if(CoreId != Can_ConfigPtr->ControllerMapListPtr[Controller])
    {
        /* Not Can Controller configured in current core */
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_SET_CONTROLLER_MODE,\
                              (uint8)CAN_E_CORE_CONTROLLER_MISMATCH);
    }
    else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
    {

#if (CAN_DEV_ERROR_DETECT == STD_ON)
        /* Get the controller to current core map. */
        ControllerToCore = Can_ConfigPtr->ControllerToCorePtr[Controller];

        /* Non-AUTOSAR:
            CAN Controller allocated to current core is not activated. */
        if(FALSE == Can_ConfigPtr->CoreConfigPtr[CoreId]-> \
                        CanControllerCfgPtr[ControllerToCore].Activation)
        {
            (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                                  (uint8)CAN_INSTANCE_ID, \
                                  (uint8)CAN_SID_SET_CONTROLLER_MODE, \
                                  (uint8)CAN_E_PARAM_CONTROLLER);
        }
        else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
        {
            /* SWS_Can_00017:
                The function Can_SetControllerMode shall perform software triggered state transitions
               of the CAN controller State machine. */
            switch (Can_Transition)
            {
                /* CAN_CS_STOPPED -> CAN_CS_STARTED. */
                case (CAN_CS_STARTED):
                {
                    Ret = Can_SetControllerModeToStart(Controller);
                    break;
                }
                /* CAN_CS_STARTED -> CAN_CS_STOPPED. */
                case (CAN_CS_STOPPED):
                {
                    Ret = Can_SetControllerModeToStop(Controller);
                    break;
                }
                /* CAN_CS_STOPPED -> CAN_CS_SLEEP. */
                /* SWS_Can_00265:
                    The function Can_SetControllerMode(CAN_CS_SLEEP) shall set the controller into
                   sleep mode. */
                case (CAN_CS_SLEEP):
                {
                    Ret = Can_SetControllerModeToSleep(Controller);
                    break;
                }
                default:
#if (CAN_DEV_ERROR_DETECT == STD_ON)
                    /* SWS_Can_00200:
                        If development error detection for the Can module is enabled: if an invalid
                       transition has been requested, the function Can_SetControllerMode shall raise
                       the error CAN_E_TRANSITION and return E_NOT_OK. */
                    (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                                          (uint8)CAN_INSTANCE_ID, \
                                          (uint8)CAN_SID_SET_CONTROLLER_MODE,\
                                          (uint8)CAN_E_TRANSITION);
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */                                            
                    Ret = E_NOT_OK;
                    break;
            }
        }
    }

    return Ret;
}
/****************************************************************************************************
*   Function Name           : Can_DisableControllerInterrupts
*
*   Service ID              : 0x04.
*
*   Description             : This function disables all interrupts for this CAN controller.
*                     
*   Parameters in           : Controller: CAN controller for which interrupts shall be disabled.
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
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Can_00425 SWS_Can_00426 SWS_Can_00231
****************************************************************************************************/
/* #Violation: Can_c_REF_6 */
FUNC(void, CAN_PUBLIC_CODE) Can_DisableControllerInterrupts
(
    uint8 Controller
)
{
    uint8         ControllerToCore;
    Mcal_CoreType CoreId;
    boolean       CanRet;

    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4*/
    CoreId = Mcal_GetCoreId();

#if (CAN_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Can_00205:
        If development error detection for the Can module is enabled: The function
       Can_DisableControllerInterrupts shall raise the error CAN_E_UNINIT if the driver not yet
       initialized. */
    if((NULL_PTR ==(Can_CoreStateArray[CoreId]))|| \
       (CAN_UNINIT == *(Can_CoreStateArray[CoreId]->CanInitStatusPtr)))
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_DISABLE_CONTROLLER_INTERRUPTS, \
                              (uint8)CAN_E_UNINIT);
    }

    /* SWS_Can_00206:
        If development error detection for the Can module is enabled: The function
       Can_DisableControllerInterrupts shall raise the error CAN_E_PARAM_CONTROLLER if the parameter
       Controller is out of range. */
    else if(Controller >= CAN_USED_CONTROLLER_MAX_NUM)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_DISABLE_CONTROLLER_INTERRUPTS, \
                              (uint8)CAN_E_PARAM_CONTROLLER);
    }

    /* Non-AUTOSAR:
        CAN Controller is not allocated to current core.*/
    else if(CoreId != (Can_ConfigPtr->ControllerMapListPtr[Controller]))
    {
        /* Not Can Controller configured in current core */
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_DISABLE_CONTROLLER_INTERRUPTS,\
                              (uint8)CAN_E_CORE_CONTROLLER_MISMATCH);
    }
    else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Get the controller index with controller ID. */
        ControllerToCore = Can_ConfigPtr->ControllerToCorePtr[Controller];

#if (CAN_DEV_ERROR_DETECT == STD_ON)
        /* Non-AUTOSAR:
            CAN Controller allocated to current core is not activated. */
        if(FALSE == CAN_CONTROLLER_CFG(CoreId,ControllerToCore,Activation))
        {
            (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                                  (uint8)CAN_INSTANCE_ID, \
                                  (uint8)CAN_SID_DISABLE_CONTROLLER_INTERRUPTS,\
                                  (uint8)CAN_E_PARAM_CONTROLLER);
        }
        else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
        /* SWS_Can_00049:
            The function Can_DisableControllerInterrupts shall access the CAN controller
            registers to disable all interrupts for that CAN controller only, if interrupts for
            that CAN Controller are enabled. */
        if (CAN_INTERRUPT_ACTIVE == CAN_CONTROLLER_CFG(CoreId, ControllerToCore, InterruptState))
        {
            /* Avoid self-adding report++ overflow */
            if((sint32)0x7FFFFFFFUL > 
                CAN_CONTROLLER_STATUS(CoreId, ControllerToCore, DisableIntrpCount))
            {
                /* SWS_Can_00202:
                    The function Can_DisableControllerInterrupts can increase a counter on every
                    execution that indicates how many Can_EnableControllerInterrupts need to be called
                    before the interrupts will be enabled */
                CAN_CONTROLLER_STATUS(CoreId, ControllerToCore, DisableIntrpCount++);
            }
#if (CAN_SAFETY_ENABLE == STD_ON)            
            else
            {
                /* Safety Error Tracer */
                (void)Det_ReportRuntimeError((uint16)CAN_MODULE_ID, \
                                             (uint8)CAN_INSTANCE_ID, \
                                             (uint8)CAN_SID_DISABLE_CONTROLLER_INTERRUPTS, \
                                             (uint8)CAN_E_DISABLE_CONTROLLER_INTERRUPTS);
            }
#endif /* (CAN_SAFETY_ENABLE \== STD_ON) */ 

            CAN_ENTER_CRITICAL_SECTION(DisableControllerInterrupts);
            /* If lager than 1,means Can controller interrupts required has been disabled.
                For performance reasons, Can_DisableController_Interrupts()
                will no longer be called repeatedly. */
            if ((sint32)1 == CAN_CONTROLLER_STATUS(CoreId, ControllerToCore, DisableIntrpCount))
            {
                /* SWS_Can_00204:
                    The Can module shall track all individual enabling and disabling of
                    interrupts in other functions (i.e. Can_SetControllerMode), so that the
                    correct interrupt enable state can be restored. */
                CanRet = Can_DisableController_Interrupts(Controller);

                CAN_EXIT_CRITICAL_SECTION(DisableControllerInterrupts);
#if (CAN_SAFETY_ENABLE == STD_ON)
                if (FALSE == CanRet)
                {
                    /* Safety Error Tracer */
                    (void)Det_ReportRuntimeError((uint16)CAN_MODULE_ID, \
                                                 (uint8)CAN_INSTANCE_ID, \
                                                 (uint8)CAN_SID_DISABLE_CONTROLLER_INTERRUPTS, \
                                                 (uint8)CAN_E_DISABLE_CONTROLLER_INTERRUPTS);
                }
#else
                /* Just avoid MISRAC Rules */
                (void)CanRet;
#endif /* (CAN_SAFETY_ENABLE \== STD_ON) */ 
            }
            else
            {
                CAN_EXIT_CRITICAL_SECTION(DisableControllerInterrupts);
            }
        }
#if (CAN_DEV_ERROR_DETECT == STD_ON)
        else
        /* #Violation: Can_c_REF_15 */
        {
            /* Do Nothing */
        }
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
    }
}
/****************************************************************************************************
*   Function Name           : Can_EnableControllerInterrupts
*
*   Service ID              : 0x05.
*
*   Description             : This function enables all allowed interrupts.
*                     
*   Parameters in           : Controller: CAN controller for which interrupts shall be re-enabled
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
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Can_00232
****************************************************************************************************/
/* #Violation: Can_c_REF_6 */
FUNC(void, CAN_PUBLIC_CODE) Can_EnableControllerInterrupts
(
    uint8 Controller
)
{
    Mcal_CoreType CoreId;
    uint8         ControllerToCore;
    boolean       DisCalledBefore;
    boolean       CanRet;

    DisCalledBefore = FALSE;

    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4*/
    CoreId = Mcal_GetCoreId();

#if (CAN_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Can_00209:
        If development error detection for the Can module is enabled: The function
       Can_EnableControllerInterrupts shall raise the error CAN_E_UNINIT if the driver not yet
       initialized. */
    if((NULL_PTR ==(Can_CoreStateArray[CoreId]))|| \
       (CAN_UNINIT == *(Can_CoreStateArray[CoreId]->CanInitStatusPtr)))
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_ENABLE_CONTROLLER_INTERRUPTS, \
                              (uint8)CAN_E_UNINIT);
    }

    /* SWS_Can_00210:
        If development error detection for the Can module is enabled: The function
       Can_EnableControllerInterrupts shall raise the error CAN_E_PARAM_CONTROLLER if the parameter
       Controller is out of range. */
    else if(Controller >= CAN_USED_CONTROLLER_MAX_NUM)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_ENABLE_CONTROLLER_INTERRUPTS,\
                              (uint8)CAN_E_PARAM_CONTROLLER);
    }

    /* Non-AUTOSAR:
        CAN Controller is not allocated to current core.*/
    else if(CoreId != (Can_ConfigPtr->ControllerMapListPtr[Controller]))
    {
        /* Not Can Controller configured in current core */
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_ENABLE_CONTROLLER_INTERRUPTS, \
                              (uint8)CAN_E_CORE_CONTROLLER_MISMATCH);
    }
    else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Get the controller to current core map. */
        ControllerToCore = Can_ConfigPtr->ControllerToCorePtr[Controller];

#if (CAN_DEV_ERROR_DETECT == STD_ON)
        /* Non-AUTOSAR:
            CAN Controller allocated to current core is not activated. */
        if(FALSE == CAN_CONTROLLER_CFG(CoreId,ControllerToCore,Activation))
        {
            (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                                  (uint8)CAN_INSTANCE_ID,\
                                  (uint8)CAN_SID_ENABLE_CONTROLLER_INTERRUPTS,\
                                  (uint8)CAN_E_PARAM_CONTROLLER);
        }
        /* Non-AUTOSAR:
            Shall only access the CAN controller registers to enable all interrupts,
            if interrupts for that CAN Controller are enabled. */
        else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
        if (CAN_INTERRUPT_ACTIVE == CAN_CONTROLLER_CFG(CoreId,ControllerToCore,InterruptState))
        {
            CAN_ENTER_CRITICAL_SECTION(EnableControllerInterrupts);

            /* Check the controller interrupt is not active */
            if((sint32)0 < CAN_CONTROLLER_STATUS(CoreId,ControllerToCore,DisableIntrpCount))
            {
                /* SWS_Can_00202:
                    The function Can_DisableControllerInterrupts can increase a counter on every
                    execution that indicates how many Can_EnableControllerInterrupts
                    need to be called before the interrupts will be enabled. */
                CAN_CONTROLLER_STATUS(CoreId,ControllerToCore,DisableIntrpCount -= 1);

                /* Set as TURE to indicate Can_DisableControllerInterrupts has not been called
                   before. */
                DisCalledBefore = TRUE;
            }

            CAN_EXIT_CRITICAL_SECTION(EnableControllerInterrupts);

#if (CAN_SAFETY_ENABLE == STD_ON)
            /* Check the DisableIntrpCount is out of range? */
            if((sint32)0 > CAN_CONTROLLER_STATUS(CoreId,ControllerToCore,DisableIntrpCount))
            {
                /* Safety Error Tracer */
                (void)Det_ReportRuntimeError((uint16)CAN_MODULE_ID, \
                                             (uint8)CAN_INSTANCE_ID, \
                                             (uint8)CAN_SID_ENABLE_CONTROLLER_INTERRUPTS, \
                                             (uint8)CAN_E_ENABLE_CONTROLLER_INTERRUPTS);
            }
#endif /* (CAN_SAFETY_ENABLE \== STD_ON) */ 

            CAN_ENTER_CRITICAL_SECTION(EnableControllerInterrupts);
            /* \[SWS_Can_00208]
                The function Can_EnableControllerInterrupts shall perform no action when
               Can_DisableControllerInterrupts has not been called before. */
            if(((sint32)0 == CAN_CONTROLLER_STATUS(CoreId,ControllerToCore,DisableIntrpCount))\
                && (TRUE == DisCalledBefore))
            {
                /* SWS_Can_00050:
                    The function Can_EnableControllerInterrupts shall enable all interrupts that must
                   be enabled according the current software status. */
                CanRet = Can_EnableController_Interrupts(Controller);

                CAN_EXIT_CRITICAL_SECTION(EnableControllerInterrupts);
#if (CAN_SAFETY_ENABLE == STD_ON)
                if (FALSE == CanRet)
                {
                    /* Safety Error Tracer */
                    (void)Det_ReportRuntimeError((uint16)CAN_MODULE_ID, \
                                                 (uint8)CAN_INSTANCE_ID, \
                                                 (uint8)CAN_SID_ENABLE_CONTROLLER_INTERRUPTS, \
                                                 (uint8)CAN_E_ENABLE_CONTROLLER_INTERRUPTS);
                }
#else
                /* Just avoid MISRAC Rules */
                (void)CanRet;
#endif /* (CAN_SAFETY_ENABLE \== STD_ON) */ 
            }
            else
            {
                CAN_EXIT_CRITICAL_SECTION(EnableControllerInterrupts);
            }
        }
#if (CAN_DEV_ERROR_DETECT == STD_ON)
        else
        /* #Violation: Can_c_REF_15 */
        {
            /* Do Nothing */
        }
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
    }
}

/* SWS_Can_00485:
    The function Can_CheckWakeup shall be pre compile time configurable On/Off by the configuration
   parameter: CanWakeupFunctionalityAPI */
#if (CAN_CHECK_WAKEUP_API_SUPPORT == STD_ON)
/****************************************************************************************************
*   Function Name           : Can_CheckWakeup
*
*   Service ID              : 0x0B.
*
*   Description             : This function checks if a wakeup has occurred for the given controller.
*                     
*   Parameters in           : Controller: Controller to be checked for a wakeup.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non Reentrant
*
*   Return value            : E_OK: API call has been accepted
*                             E_NOT_OK: API call has not been accepted
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Can_00360
****************************************************************************************************/
/* #Violation: Can_c_REF_6 */
FUNC(Std_ReturnType, CAN_PUBLIC_CODE) Can_CheckWakeup
(
    uint8 Controller
)
{
    Std_ReturnType Ret;
    uint8          ControllerToCore;
    Mcal_CoreType  CoreId;
    /* Set E_NOT_OK as default */
    Ret = E_NOT_OK;
    
    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4*/
    CoreId = Mcal_GetCoreId();


#if (CAN_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Can_00362:
        If development error detection for the Can module is enabled: The function Can_CheckWakeup
       shall raise the error CAN_E_UNINIT if the driver is not yet initialized. */
    if((NULL_PTR ==(Can_CoreStateArray[CoreId]))|| \
       (CAN_UNINIT == *(Can_CoreStateArray[CoreId]->CanInitStatusPtr)))
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_CBK_CHECK_WAKEUP, \
                              (uint8)CAN_E_UNINIT);
    }
    /* SWS_Can_00363:
        If development error detection for the Can module is enabled: The function Can_CheckWakeup
       shall raise the error CAN_E_PARAM_CONTROLLER if the parameter Controller is out of range. */
    else if(Controller >= CAN_USED_CONTROLLER_MAX_NUM)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_CBK_CHECK_WAKEUP, \
                              (uint8)CAN_E_PARAM_CONTROLLER);
    }
    /* Non-AUTOSAR:
     CAN Controller is not allocated to current core. */
    else if(CoreId != (Can_ConfigPtr->ControllerMapListPtr[Controller]))
    {
        /* Not Can Controller configured in current core */
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_CBK_CHECK_WAKEUP,\
                              (uint8)CAN_E_CORE_CONTROLLER_MISMATCH);
    }
    else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Get the controller to current core map. */
        ControllerToCore = Can_ConfigPtr->ControllerToCorePtr[Controller];

#if (CAN_DEV_ERROR_DETECT == STD_ON)
        /* Non-AUTOSAR:
         CAN Controller allocated to current core is not activated. */
        if(FALSE == CAN_CONTROLLER_CFG(CoreId,ControllerToCore,Activation))
        {
            (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                                  (uint8)CAN_INSTANCE_ID, \
                                  (uint8)CAN_SID_CBK_CHECK_WAKEUP, \
                                  (uint8)CAN_E_PARAM_CONTROLLER);
        }
        else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
        {
#if (CAN_WAKEUP_SUPPORT == STD_ON)
            /* SWS_Can_00361:
                The function Can_CheckWakeup shall check if the requested CAN controller has detected
               a wakeup. If a wakeup event was successfully detected, reporting shall be done to EcuM
               via API EcuM_SetWakeupEvent. */
            if(CAN_WAKEUP == CAN_CONTROLLER_STATUS(CoreId,ControllerToCore,WakeupState))
            {
                CAN_CONTROLLER_STATUS(CoreId,ControllerToCore,WakeupState) = CAN_NOT_WAKEUP;
                EcuM_SetWakeupEvent(CAN_CONTROLLER_CFG(CoreId,ControllerToCore,WakeupSourceId));
                Ret = E_OK;
            }
#endif /* (CAN_WAKEUP_SUPPORT  \== STD_ON) */
        }
    }

    return Ret;
}
#endif /* (CAN_CHECK_WAKEUP_API_SUPPORT  \== STD_ON) */

/****************************************************************************************************
*   Function Name           : Can_GetControllerErrorState
*
*   Service ID              : 0x11.
*
*   Description             : This service obtains the error state of the CAN controller.
*                     
*   Parameters in           : Controller - Abstracted CanIf ControllerId which is assigned to
*                             a CAN controller, which is requested for ErrorState.
*
*   Parameters inout        : None.
*
*   Parameters out          : ErrorStatePtr: Pointer to a memory location, where the error state
*                             of the CAN controller will be stored.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non Reentrant for the same ControllerId
*
*   Return value            : E_OK:  Error state request has been accepted.
*                             E_NOT_OK: Error state request has not been accepted.
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Can_91004
****************************************************************************************************/
/* #Violation: Can_c_REF_6 */
FUNC(Std_ReturnType, CAN_PUBLIC_CODE) Can_GetControllerErrorState
(
    uint8 Controller,
    CONSTP2VAR(Can_ErrorStateType, AUTOMATIC, CAN_APPL_CONST) ErrorStatePtr
)
{
    Std_ReturnType Ret;
    uint8          ControllerToCore;
    Mcal_CoreType  CoreId;
    uint32         ErrorState;
    
    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4*/
    CoreId = Mcal_GetCoreId();

#if (CAN_DEV_ERROR_DETECT == STD_ON)
    /* Set E_NOT_OK as default */
    Ret = E_NOT_OK;

    /* SWS_Can_91005:
        If development error detection for the Can module is enabled: if the module is not yet
       initialized, the function Can_GetControllerErrorState shall raise development error
       CAN_E_UNINIT and return E_NOT_OK. */
    if((NULL_PTR ==(Can_CoreStateArray[CoreId]))|| \
       (CAN_UNINIT == *(Can_CoreStateArray[CoreId]->CanInitStatusPtr)))
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_GET_CONTROLLER_ERROR_STATE, \
                              (uint8)CAN_E_UNINIT);
    }
    /* SWS_Can_91006:
        If development error detection for the Can module is enabled: if the parameter ControllerId
       is out of range, the function Can_GetControllerErrorState shall raise development error
       CAN_E_PARAM_CONTROLLER and return E_NOT_OK. */
    else if(Controller >= CAN_USED_CONTROLLER_MAX_NUM)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_GET_CONTROLLER_ERROR_STATE, \
                              (uint8)CAN_E_PARAM_CONTROLLER);
    }
    /* SWS_Can_91007:
        If development error detection for the Can module is enabled: if the parameter ErrorStatePtr
       is a null pointer, the function Can_GetControllerErrorState shall raise development error
       CAN_E_PARAM_POINTER and return E_NOT_OK. */
    else if(NULL_PTR == ErrorStatePtr)
    {
        /* Not Can Controller configured in current core */
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_GET_CONTROLLER_ERROR_STATE,\
                              (uint8)CAN_E_PARAM_POINTER);
    }
    else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Get the controller to current core map. */
        ControllerToCore = Can_ConfigPtr->ControllerToCorePtr[Controller];

#if (CAN_DEV_ERROR_DETECT == STD_ON)
        /* Non-AUTOSAR:
            CAN Controller allocated to current core is not activated. */
        if(FALSE == CAN_CONTROLLER_CFG(CoreId,ControllerToCore,Activation))
        {
            (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                                  (uint8)CAN_INSTANCE_ID, \
                                  (uint8)CAN_SID_GET_CONTROLLER_ERROR_STATE, \
                                  (uint8)CAN_E_PARAM_CONTROLLER);
        }
        else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
        {
            /* SWS_Can_91008:
                When the API Can_GetControllerErrorState()  is called with Controller Id as input
               parameter then Can driver shall read the error state register of Can Controller and
               shall return the error status to upper layer. */
            /* #Violation: Can_c_REF_4*/
            ErrorState = Can_Hal_GetProtocolStatus(CAN_BASE_ADDR(CoreId,ControllerToCore));
            
            /* SWS_Can_91003:
                Error states of a CAN controller. */
            if ( 0U != (CAN_PROTOCOL_BO & ErrorState) )
            {
                *ErrorStatePtr = CAN_ERRORSTATE_BUSOFF;
            }
            else if ( 0U != (CAN_PROTOCOL_EP & ErrorState) )
            {
                *ErrorStatePtr = CAN_ERRORSTATE_PASSIVE;
            }
            else
            {
                *ErrorStatePtr = CAN_ERRORSTATE_ACTIVE;
            }

            /* Set the API status as E_OK */
            Ret = E_OK;
        }
    }

    return Ret;
}

/****************************************************************************************************
*   Function Name           : Can_GetControllerMode
*
*   Service ID              : 0x12.
*
*   Description             : This service reports about the current status of the requested CAN
*                             controller.
*                     
*   Parameters in           : Controller: CAN controller for which the status shall be requested.
*
*   Parameters inout        : None.
*
*   Parameters out          : ControllerModePtr: Pointer to a memory location, where the current mode
*                             of the CAN controller will be stored.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non Reentrant
*
*   Return value            : E_OK:  Error state request has been accepted.
*                             E_NOT_OK: Error state request has not been accepted.
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Can_91014
****************************************************************************************************/
/* #Violation: Can_c_REF_6 */
FUNC(Std_ReturnType, CAN_PUBLIC_CODE) Can_GetControllerMode
(
    uint8 Controller,
    CONSTP2VAR(Can_ControllerStateType, AUTOMATIC, CAN_APPL_CONST) ControllerModePtr
)
{
    Std_ReturnType Ret;
    uint8          ControllerToCore;
    Mcal_CoreType  CoreId;

    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4*/
    CoreId = Mcal_GetCoreId();

#if (CAN_DEV_ERROR_DETECT == STD_ON)
    /* Set E_NOT_OK as default */
    Ret = E_NOT_OK;

    /* SWS_Can_91016:
        If development error detection for the Can module is enabled: The function
       Can_GetControllerMode shall raise the error CAN_E_UNINIT and return E_NOT_OK if the driver is
       not yet initialized. */
    if((NULL_PTR ==(Can_CoreStateArray[CoreId]))|| \
       (CAN_UNINIT == *(Can_CoreStateArray[CoreId]->CanInitStatusPtr)))
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_GET_CONTROLLER_MODE, \
                              (uint8)CAN_E_UNINIT);
    }
    /* SWS_Can_91017:
        If parameter Controller of Can_GetControllerMode() has an invalid value, the CanDrv shall
       report development error code CAN_E_PARAM_CONTROLLER to the Det_ReportError service of the
       DET. */
    else if(Controller >= CAN_USED_CONTROLLER_MAX_NUM)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_GET_CONTROLLER_MODE, \
                              (uint8)CAN_E_PARAM_CONTROLLER);
    }
    /* SWS_Can_91018:
        If parameter ControllerModePtr of Can_GetControllerMode() has an null pointer, the CanDrv
       shall report development error code CAN_E_PARAM_POINTER to the Det_ReportError service of the
       DET. */
    else if(NULL_PTR == ControllerModePtr)
    {
        /* Not Can Controller configured in current core */
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_GET_CONTROLLER_MODE,\
                              (uint8)CAN_E_PARAM_POINTER);
    }
    else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Get the controller to current core map. */
        ControllerToCore = Can_ConfigPtr->ControllerToCorePtr[Controller];

#if (CAN_DEV_ERROR_DETECT == STD_ON)
        /* Non-AUTOSAR:
            CAN Controller allocated to current core is not activated. */
        if(FALSE == Can_ConfigPtr->CoreConfigPtr[CoreId]-> \
                        CanControllerCfgPtr[ControllerToCore].Activation)
        {
            (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                                  (uint8)CAN_INSTANCE_ID, \
                                  (uint8)CAN_SID_GET_CONTROLLER_MODE, \
                                  (uint8)CAN_E_PARAM_CONTROLLER);
        }
        else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
        {
            /* SWS_Can_91015:
                The service Can_GetControllerMode shall return the mode of the requested CAN
               controller. */
            *ControllerModePtr = CAN_CONTROLLER_STATUS(CoreId,ControllerToCore,CurrentStatus);

            /* Set the API status as E_OK */
            Ret = E_OK;
        }
    }

    return Ret;
    
}

/****************************************************************************************************
*   Function Name           : Can_GetControllerRxErrorCounter
*
*   Service ID              : 0x30.
*
*   Description             : Returns the Rx error counter for a CAN controller. 
*                             This value might not be available for all CAN controllers, in which 
*                             case E_NOT_OK would be returned.
*                     
*   Parameters in           : ControllerId: CAN controller, whose current Rx error counter shall be
*                             acquired.
*
*   Parameters inout        : None.
*
*   Parameters out          : ControllerModePtr: Pointer to a memory location, where the current mode
*                             of the CAN controller will be stored.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non Reentrant for the same ControllerId
*
*   Return value            : E_OK: Rx error counter available.
*                             E_NOT_OK: Wrong ControllerId, or Rx error counter not available.
*
*   Preconditions           : Please note that the value of the counter might not be correct at the
*                             moment the API returns it, because the Rx counter is handled
*                             asynchronously in hardware. Applications should not trust this value
*                             for any assumption about the current bus state.
*
*   AUTOSAR_Requirement     : SWS_Can_00511
****************************************************************************************************/
/* #Violation: Can_c_REF_6 */
FUNC(Std_ReturnType, CAN_PUBLIC_CODE) Can_GetControllerRxErrorCounter
(
    uint8 Controller,
    /* #Violation: Can_c_REF_13*/
    P2VAR(uint8, AUTOMATIC, CAN_APPL_CONST) RxErrorCounterPtr
)
{
    Std_ReturnType           Ret;
    uint8                    ControllerToCore;
    Mcal_CoreType            CoreId;
    CAN_ErrorCountersTypeDef ErrorCounters;

    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4*/
    CoreId = Mcal_GetCoreId();

#if (CAN_DEV_ERROR_DETECT == STD_ON)
    /* Set E_NOT_OK as default */
    Ret = E_NOT_OK;

    /* SWS_Can_00512:
        If development error detection for the Can module is enabled: if the module is not yet
       initialized, the function Can_GetControllerRxErrorCounter shall raise development error
       CAN_E_UNINIT and return E_NOT_OK. */
    if((NULL_PTR ==(Can_CoreStateArray[CoreId]))|| \
       (CAN_UNINIT == *(Can_CoreStateArray[CoreId]->CanInitStatusPtr)))
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_GET_CONTROLLER_RX_ERROR_COUNTER, \
                              (uint8)CAN_E_UNINIT);
    }
    /* SWS_Can_00513:
        If development error detection for the Can module is enabled: if the parameter ControllerId
       is out of range, the function Can_GetControllerRxErrorCounter shall raise development error
       CAN_E_PARAM_CONTROLLER and return E_NOT_OK. */
    else if(Controller >= CAN_USED_CONTROLLER_MAX_NUM)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_GET_CONTROLLER_RX_ERROR_COUNTER, \
                              (uint8)CAN_E_PARAM_CONTROLLER);
    }
    /* SWS_Can_00514:
        If development error detection for the Can module is enabled: if the parameter
       RxErrorCounterPtr is a null pointer, the function Can_GetControllerRxErrorCounter shall raise
       development error CAN_E_PARAM_POINTER and return E_NOT_OK. */
    else if(NULL_PTR == RxErrorCounterPtr)
    {
        /* Not Can Controller configured in current core */
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_GET_CONTROLLER_RX_ERROR_COUNTER,\
                              (uint8)CAN_E_PARAM_POINTER);
    }
    else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Get the controller to current core map. */
        ControllerToCore = Can_ConfigPtr->ControllerToCorePtr[Controller];

#if (CAN_DEV_ERROR_DETECT == STD_ON)
        /* Non-AUTOSAR:
            CAN Controller allocated to current core is not activated. */
        if(FALSE == CAN_CONTROLLER_CFG(CoreId,ControllerToCore,Activation))
        {
            (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                                  (uint8)CAN_INSTANCE_ID, \
                                  (uint8)CAN_SID_GET_CONTROLLER_RX_ERROR_COUNTER, \
                                  (uint8)CAN_E_PARAM_CONTROLLER);
        }
        else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
        {
            /* SWS_Can_00515:
                When the API Can_GetControllerRxErrorCounter is called with Controller Id as input
               parameter then Can driver shall read the Rx error counter register of Can Controller
               and shall return the Rx error count to upper layer. */
            /* #Violation: Can_c_REF_4*/
            Can_Hal_GetErrorCounters(CAN_BASE_ADDR(CoreId,ControllerToCore),\
                                     &ErrorCounters);
            
            /* Update the Rx error count to upper layer */
            *RxErrorCounterPtr = ErrorCounters.rxErrorCnt;

            /* Set the API status as E_OK */
            Ret = E_OK;
        }
    }

    return Ret;
}

/****************************************************************************************************
*   Function Name           : Can_GetControllerTxErrorCounter
*
*   Service ID              : 0x31.
*
*   Description             : Returns the Tx error counter for a CAN controller. 
*                             This value might not be available for all CAN controllers, in which case
*                             E_NOT_OK would be returned.
*                     
*   Parameters in           : Controller: CAN controller, whose current Tx error counter shall be
*                             acquired.
*
*   Parameters inout        : None.
*
*   Parameters out          : TxErrorCounterPtr: Pointer to a memory location, where the current mode
*                             of the CAN controller will be stored.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non Reentrant for the same ControllerId
*
*   Return value            : E_OK: Tx error counter available.
*                             E_NOT_OK: Wrong ControllerId, or Tx error counter not available.
*
*   Preconditions           : Please note that the value of the counter might not be correct at the
*                             moment the API returns it, because the Tx counter is handled
*                             asynchronously in hardware. Applications should not trust this value
*                             for any assumption about the current bus state.
*
*   AUTOSAR_Requirement     : SWS_Can_00516
****************************************************************************************************/
/* #Violation: Can_c_REF_6 */
FUNC(Std_ReturnType, CAN_PUBLIC_CODE) Can_GetControllerTxErrorCounter
(
    uint8 Controller,
    CONSTP2VAR(uint8, AUTOMATIC, CAN_APPL_CONST) TxErrorCounterPtr
)
{
    Std_ReturnType           Ret;
    uint8                    ControllerToCore;
    Mcal_CoreType            CoreId;
    CAN_ErrorCountersTypeDef ErrorCounters;

    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4*/
    CoreId = Mcal_GetCoreId();

#if (CAN_DEV_ERROR_DETECT == STD_ON)
    /* Set E_NOT_OK as default */
    Ret = E_NOT_OK;

    /* SWS_Can_00517:
        If development error detection for the Can module is enabled: if the module is not yet
       initialized, the function Can_GetControllerTxErrorCounter shall raise development error
       CAN_E_UNINIT and return E_NOT_OK. */
    if((NULL_PTR ==(Can_CoreStateArray[CoreId]))|| \
       (CAN_UNINIT == *(Can_CoreStateArray[CoreId]->CanInitStatusPtr)))
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_GET_CONTROLLER_TX_ERROR_COUNTER, \
                              (uint8)CAN_E_UNINIT);
    }
    /* SWS_Can_00518:
        If development error detection for the Can module is enabled: if the parameter ControllerId
       is out of range, the function Can_GetControllerTxErrorCounter shall raise development error
       CAN_E_PARAM_CONTROLLER and return E_NOT_OK. */
    else if(Controller >= CAN_USED_CONTROLLER_MAX_NUM)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_GET_CONTROLLER_TX_ERROR_COUNTER, \
                              (uint8)CAN_E_PARAM_CONTROLLER);
    }
    /* SWS_Can_00519:
        If development error detection for the Can module is enabled: if the parameter
       TxErrorCounterPtr is a null pointer, the function Can_GetControllerTxErrorCounter shall raise
       development error CAN_E_PARAM_POINTER and return E_NOT_OK. */
    else if(NULL_PTR == TxErrorCounterPtr)
    {
        /* Not Can Controller configured in current core */
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_GET_CONTROLLER_TX_ERROR_COUNTER,\
                              (uint8)CAN_E_PARAM_POINTER);
    }
    else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Get the controller to current core map. */
        ControllerToCore = Can_ConfigPtr->ControllerToCorePtr[Controller];

#if (CAN_DEV_ERROR_DETECT == STD_ON)
        /* Non-AUTOSAR:
            CAN Controller allocated to current core is not activated. */
        if(FALSE == CAN_CONTROLLER_CFG(CoreId,ControllerToCore,Activation))
        {
            (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                                  (uint8)CAN_INSTANCE_ID, \
                                  (uint8)CAN_SID_GET_CONTROLLER_TX_ERROR_COUNTER, \
                                  (uint8)CAN_E_PARAM_CONTROLLER);
        }
        else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
        {
            /* SWS_Can_00520:
                When the API Can_GetControllerTxErrorCounter is called with Controller Id as input
               parameter then Can driver shall read the Tx error counter register of Can Controller
               and shall return the Tx error count to upper layer. */
            /* #Violation: Can_c_REF_4*/
            Can_Hal_GetErrorCounters(CAN_BASE_ADDR(CoreId,ControllerToCore),\
                                     &ErrorCounters);
            
            /* Update the Tx error count to upper layer */
            *TxErrorCounterPtr = ErrorCounters.txErrorCnt;

            /* Set the API status as E_OK */
            Ret = E_OK;
        }
    }

    return Ret;
}

/****************************************************************************************************
*   Function Name           : Can_Write
*
*   Service ID              : 0x06.
*
*   Description             : This function is called by CanIf to pass a CAN message to CanDrv for 
*                             transmission.
*                     
*   Parameters in           : Hth: information which HW-transmit handle shall be used for transmit. 
*                                  Implicitly this is also the information about the controller to
*                                  use, because the Hth numbers are unique inside one hardware unit.
*
*                             PduInfoPtr: pointer to SDU user memory, DLC and Identifier.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant
*
*   Return value            : E_OK: Write command has been accepted
*
*                             E_NOT_OK: Development error occurred
*
*                             CAN_BUSY: No TX hardware buffer available or pre-emptive call of
*                                         Can_Write that can't be implemented reentrant
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Can_00059 SWS_Can_00011 SWS_Can_00060 SWS_Can_00233 SWS_Can_00214
****************************************************************************************************/
/* #Violation: Can_c_REF_6 */
FUNC(Std_ReturnType, CAN_PUBLIC_CODE) Can_Write
(
    Can_HwHandleType Hth, 
    CONSTP2CONST(Can_PduType, AUTOMATIC, CAN_APPL_CONST) PduInfoPtr
)
{
    Std_ReturnType Ret;
    uint8          Controller;
#if (CAN_DEV_ERROR_DETECT == STD_ON)
    Mcal_CoreType CoreId;
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */

#if (CAN_DEV_ERROR_DETECT == STD_ON)
    /* Set E_NOT_OK as default */
    Ret = E_NOT_OK;

    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4 */
    CoreId = Mcal_GetCoreId();

    /* SWS_Can_00216:
        If development error detection for the Can module is enabled: The function Can_Write shall
       raise the error CAN_E_UNINIT and shall return E_NOT_OK if the driver is not yet initialized.
     */
    if((NULL_PTR ==(Can_CoreStateArray[CoreId]))|| \
        (CAN_UNINIT == *(Can_CoreStateArray[CoreId]->CanInitStatusPtr)))
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_WRITE, \
                              (uint8)CAN_E_UNINIT);
    }

    /* SWS_Can_00217:
        If development error detection for the Can module is enabled: The function Can_Write shall
       raise the error CAN_E_PARAM_HANDLE and shall return E_NOT_OK if the parameter Hth is not a
       configured Hardware Transmit Handle. */
    else if((CAN_RECEIVE == CAN_HWOBJ_CFG(Hth,ObjectType)) || (Hth >= CAN_USED_HOH_MB_MAX_NUM))
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_WRITE, \
                              (uint8)CAN_E_PARAM_HANDLE);
    }

    /* SWS_Can_00219:
        If development error detection for CanDrv is enabled: Can_Write() shall raise
       CAN_E_PARAM_POINTER and shall return E_NOT_OK if the parameter PduInfo is a null pointer. */
    else if(NULL_PTR == PduInfoPtr)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_WRITE, \
                              (uint8)CAN_E_PARAM_POINTER);
    }

    /* SWS_CAN_00505:
        If development error detection for CanDrv is enabled: Can_Write() shall raise
       CAN_E_PARAM_POINTER and shall return E_NOT_OK if the trigger transmit API is disabled for this
       hardware object (CanTriggerTransmitEnable = FALSE) and the SDU pointer inside PduInfo is a
       null pointer. */
    else if((NULL_PTR == PduInfoPtr->sdu) 
#if (CAN_TRIGGER_TRANSMIT_SUPPORT == STD_ON)
            && (FALSE == CAN_HWOBJ_CFG(Hth,TriggerTxEN))
#endif /* (CAN_TRIGGER_TRANSMIT_SUPPORT \== STD_ON) */
            )
    {
        (void)Det_ReportError(CAN_MODULE_ID, \
                              CAN_INSTANCE_ID, \
                              CAN_SID_WRITE, \
                              CAN_E_PARAM_POINTER);
    }

    /* SWS_Can_00218:
        The function Can_Write shall return E_NOT_OK and if development error detection for the CAN
      module is enabled shall raise the error CAN_E_PARAM_DATA_LENGTH:      
      3-1: If the length is more than 64 byte.
      3-2: If the length is more than 8 byte and the CAN controller is not in CAN FD mode.
      3-3: If the length is more than 8 byte and the CAN controller is in CAN FD mode,
           but the CAN FD flag in Can_PduType->id is not set */
    else if ((PduInfoPtr->length > CANFD_MODE_MAX_PAYLOAD_LENGTH) ||
             ((PduInfoPtr->length > CAN_STANDARD_MAX_PAYLOAD_LENGTH)
#if (CANFD_MODE_SUPPORT == STD_OFF)
            || (CAN_FD_FRAME_FORMAT == (uint32)(PduInfoPtr->id & CAN_FD_FRAME_FORMAT))))
#else
            && (CAN_FD_FRAME_FORMAT != (uint32)(PduInfoPtr->id & CAN_FD_FRAME_FORMAT))))
#endif /* (CANFD_MODE_SUPPORT  \== STD_OFF) */
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_WRITE, \
                              (uint8)CAN_E_PARAM_DATA_LENGTH);
    }
    else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Get current ControllerId by Hth. */
        Controller = CAN_HWOBJ_CFG(Hth,ControllerId);

#if (CAN_DEV_ERROR_DETECT == STD_ON)
        /* Non-AUTOSAR:
         CAN Controller is not allocated to current core. */
        if(CoreId != (Can_ConfigPtr->ControllerMapListPtr[Controller]))
        {
            /* Not Can Controller configured in current core */
            (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                                  (uint8)CAN_INSTANCE_ID, \
                                  (uint8)CAN_SID_WRITE, \
                                  (uint8)CAN_E_CORE_CONTROLLER_MISMATCH);
        }
        else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
        {
#if (CAN_LPDU_TX_CALLOUT_FUNCTION_SUPPORT == STD_ON)
            CAN_LPDU_TRANSMIT_CALLOUT_FUNCTION(Controller, PduInfoPtr);
#endif /* (CAN_LPDU_TX_CALLOUT_FUNCTION_SUPPORT  \== STD_ON) */

            /* Invoke low-level interface to send message. */
            Ret = Can_WriteMsgObj(Controller,Hth,PduInfoPtr);
        }
    }

    return Ret;
}

/****************************************************************************************************
*   Function Name           : Can_MainFunction_Write
*
*   Service ID              : None.
*
*   Description             : This function performs the polling of TX confirmation when
*                             CAN_TX_PROCESSING is set to POLLING.
*                     
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Can_00225
****************************************************************************************************/
/* #Violation: Can_c_REF_6 */
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write
(
    void
)
{
    Can_MainFunctionWriteHandler(0U);
}
/****************************************************************************************************
*   Function Name           : Can_MainFunction_Read
*
*   Service ID              : 0x08.
*
*   Description             : This function performs the polling of RX indications when
*                             Can_RxProcessing is set to POLLING.
*                     
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Can_00226
****************************************************************************************************/
/* #Violation: Can_c_REF_6 */
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read
(
    void
)
{
    Can_MainFunction_CommonRead(0U);
}
/****************************************************************************************************
*   Function Name           : Can_MainFunction_BusOff
*
*   Service ID              : 0x09.
*
*   Description             : This function performs the polling of bus-off events that are
*                             configured statically as 'to be polled'.
*                     
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Can_00227
****************************************************************************************************/
/* #Violation: Can_c_REF_6 */
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_BusOff
(
    void
)
{
    /* SWS_Can_00109:
        The function Can_MainFunction_BusOff shall perform the polling of bus-off events that are configured statically as 'to be polled'. */
#if (CAN_CONTROLLER_BUSOFF_POLLING_SUPPORT == STD_ON)
    uint8 Index;
    Mcal_CoreType CoreId;

    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4*/
    CoreId = Mcal_GetCoreId();

#if (CAN_DEV_ERROR_DETECT == STD_ON)
    if((NULL_PTR ==(Can_CoreStateArray[CoreId]))|| \
        (CAN_UNINIT == *(Can_CoreStateArray[CoreId]->CanInitStatusPtr)))
    {
        /* SWS_Can_00184:
            Shall raise the error CAN_E_UNINIT if the driver is not yet initialized. */
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_MAIN_FUNCTION_BUS_OFF, \
                              (uint8)CAN_E_UNINIT);
    }
    else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* SWS_Can_00109:
            The function Can_MainFunction_BusOff shall perform the polling of bus-off events that are
           configured statically as 'to be polled'. */
        /* SWS_Can_00183:
            The Can module may implement the function Can_MainFunction_BusOff as empty define in case
           no polling at all is used.*/
        for(Index = 0U; Index < CAN_CORE_CFG(CoreId,MaxCoreController);
            Index++)
        {
            /* Check bus-off processing is POLLING ? */
            if(CAN_POLLING == CAN_CONTROLLER_CFG(CoreId,Index,BusoffProcessing))
            {
                /* Period to check whether BUSOFF event happened */
                Can_CheckBusOffEvent(CAN_CONTROLLER_CFG(CoreId,Index,LogicalID));
            }
        }
    }
#endif /* (CAN_CONTROLLER_BUSOFF_POLLING_SUPPORT  \== STD_ON) */
} 
/****************************************************************************************************
*   Function Name           : Can_MainFunction_Wakeup
*
*   Service ID              : 0x0A.
*
*   Description             : This function performs the polling of wake-up events that are
*                             configured statically as 'to be polled .
*                     
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Can_00228
****************************************************************************************************/
/* #Violation: Can_c_REF_6 */
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Wakeup
(
    void
)
{
    /* SWS_Can_00112:
        The function Can_MainFunction_Wakeup shall perform the polling of wake-up events that are
       configured statically as 'to be polled'. */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
    Mcal_CoreType   CoreId;

    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4 */
    CoreId = Mcal_GetCoreId();
#endif /* (CAN_DEV_ERROR_DETECT \== STD_ON) */

#if (CAN_DEV_ERROR_DETECT == STD_ON)
    if((NULL_PTR ==(Can_CoreStateArray[CoreId]))|| \
        (CAN_UNINIT == *(Can_CoreStateArray[CoreId]->CanInitStatusPtr)))
    {
        /* SWS_Can_00186:
            Shall raise the error CAN_E_UNINIT if the driver is not yet initialized. */
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_MAIN_FUNCTION_WAKEUP, \
                              (uint8)CAN_E_UNINIT);
    }
    else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
    /* #Violation: Can_c_REF_15 */
    {
        /* SWS_Can_00185:
           The Can module may implement the function Can_MainFunction_Wakeup as empty define in case
           no polling at all is used. */

        /* 7.3.6 State transition caused by Hardware Events
           State transition caused by Hardware Wakeup (triggered by wake-up event from CAN bus)
           This state transition will only occur when sleep mode is supported by hardware.*/
    }
}
/****************************************************************************************************
*   Function Name           : Can_MainFunction_Mode
*
*   Service ID              : 0x0C.
*
*   Description             : This function performs the polling of CAN controller mode transitions.
*                     
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Can_00368
****************************************************************************************************/
/* #Violation: Can_c_REF_6 */
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Mode
(
    void
)
{
    uint8            Index;
    Mcal_CoreType    CoreId;
    uint8            Controller;
    uint8            ControllerToCore;
    uint32           ProtocolStatus;
    
    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4*/
    CoreId = Mcal_GetCoreId();

#if (CAN_DEV_ERROR_DETECT == STD_ON)
    /* Check current core state is CAN_UNINIT or invalid? */
    if((NULL_PTR == (Can_CoreStateArray[CoreId]))|| \
        (CAN_UNINIT == *(Can_CoreStateArray[CoreId]->CanInitStatusPtr)))
    {
        /* SWS_Can_00379:
            Shall raise the error CAN_E_UNINIT if the driver is not yet initialized. */
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_MAIN_FUNCTION_MODE, \
                              (uint8)CAN_E_UNINIT);
    }
    else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Traverse all controllers and check mode */
        for(Index = 0U; Index < CAN_CORE_CFG(CoreId,MaxCoreController);
            Index++)
        {
            /* Get the controller logic id */
            Controller = CAN_CONTROLLER_CFG(CoreId,Index,LogicalID);
            
            /* Get the controller config set index */
            ControllerToCore = Can_ConfigPtr->ControllerToCorePtr[Controller];

            /* [SWS_Can_00369]:
                The function Can_MainFunction_Mode shall implement the polling of CAN status register
               flags to detect transition of CAN Controller state.  */
            /* #Violation: Can_c_REF_4*/
            ProtocolStatus = Can_Hal_GetProtocolStatus(CAN_BASE_ADDR(CoreId,ControllerToCore));

            /* [SWS_Can_00370]:
                The function Can_Mainfunction_Mode shall poll a flag of the CAN status register
                until the flag signals that the change takes effect and notify the upper layer
                with function CanIf_ControllerModeIndication about a successful state transition
                referring to the corresponding CAN controller with the abstract CanIf ControllerId. */
            switch (CAN_CONTROLLER_STATUS(CoreId,Index,CurrentStatus))
            {
                case CAN_CS_STARTED:
                {
                    /* BusOff eventsand Message Ram Ecc error can cause PSR.ACT to be cleared which
                       should be avoided when switching CanController modes.
                       Message Ram Ecc error occurred will causing PSR.ACT to be cleared.It should be
                       reported to Alarm through SAC for processing. */
                    if(0UL == ((CAN_PROTOCOL_ACT|CAN_PROTOCOL_BO) & ProtocolStatus)) 
                    {
                        /* [SWS_Can_00372]:
                              In case the flag signals that the change takes no effect and the maximum
                            time CanTimeoutDuration is elapsed, the function Can_SetControllerMode
                            shall be left and the function Can_Mainfunction_Mode shall continue to
                            poll the flag. */
                        CAN_CONTROLLER_STATUS(CoreId,Index,CurrentStatus) = CAN_CS_STOPPED;

                        /* [SWS_Can_00373]:
                               The function Can_Mainfunction_Mode shall call the function
                            CanIf_ControllerModeIndication to notify the upper layer about a successful
                            state transition of the corresponding CAN controller referred by abstract
                            CanIf ControllerId,in case the state transition was triggered by function
                            Can_SetControllerMode. */
                        CanIf_ControllerModeIndication(Controller, CAN_CS_STOPPED);    
                    }
                    break;
                }
                case CAN_CS_STOPPED:
                {
                    if(0UL != (CAN_PROTOCOL_ACT & ProtocolStatus)) 
                    {
                        /* [SWS_Can_00372]:
                            In case the flag signals that the change takes no effect and the maximum
                        time CanTimeoutDuration is elapsed, the function Can_SetControllerMode
                        shall be left and the function Can_Mainfunction_Mode shall continue to
                        poll the flag. */
                        CAN_CONTROLLER_STATUS(CoreId,Index,CurrentStatus) = CAN_CS_STARTED;

                        /* [SWS_Can_00373]:
                                The function Can_Mainfunction_Mode shall call the function
                            CanIf_ControllerModeIndication to notify the upper layer about a successful
                            state transition of the corresponding CAN controller referred by abstract
                            CanIf ControllerId,in case the state transition was triggered by function
                            Can_SetControllerMode. */
                        CanIf_ControllerModeIndication(Controller, CAN_CS_STARTED);    
                    }
                    break;
                }
                case CAN_CS_SLEEP:
                {
                    /* No request trigger */
                    break;
                }
                default:
                {
#if (CAN_DEV_ERROR_DETECT == STD_ON) 
                    /* Safety Error Tracer */
                    (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                                          (uint8)CAN_INSTANCE_ID, \
                                          (uint8)CAN_SID_MAIN_FUNCTION_MODE, \
                                          (uint8)CAN_E_TRANSITION);
#endif /* (CAN_DEV_ERROR_DETECT \== STD_ON) */   
                    break;
                }
            }
        }
    }
}
/***************************************************************************************************
*                               Interrupt Service Function
****************************************************************************************************/
/* SWS_Can_00033:
    The Can module shall implement the interrupt service routines for all CAN Hardware Unit
   interrupts that are needed. */
#if ((CAN_CONTROLLER_RX_INTERRUPT_SUPPORT == STD_ON))
/****************************************************************************************************
*   Function Name           : Can_MB_IRQHandler
*
*   Service ID              : 0xE1.
*
*   Description             : This function is used to handle the MB interrupt.
*
*   Parameters in           : Controller: CAN controller for which result of the interrupt.
*                                         It's the logical controller.
*
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant for different HW, Non-Reentrant for same HW
*
*   Return value            : None
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, CAN_PUBLIC_CODE) Can_MB_IRQHandler
(
    CONST(uint8, AUTOMATIC) Controller
)
{
    Mcal_CoreType    CoreId;
    Can_HwHandleType Hrh;
    uint8            ControllerToCore;
    CAN_NODE         *CanNodePtr;
    uint64           MessageIdxMask;

    if(NULL_PTR != Can_ConfigPtr)
    {
        /* Get core id which is executing currently */
        /* #Violation: Can_c_REF_4*/
        CoreId = Mcal_GetCoreId();

        /* Get the controller config set index */
        ControllerToCore = Can_ConfigPtr->ControllerToCorePtr[Controller];

        /* Get the controller node address */
        /* #Violation: Can_c_REF_4*/
        CanNodePtr = CAN_BASE_ADDR(CoreId,ControllerToCore);

#if (CAN_DEV_ERROR_DETECT == STD_ON)
        if((NULL_PTR ==(Can_CoreStateArray[CoreId]))|| \
            (CAN_UNINIT == *(Can_CoreStateArray[CoreId]->CanInitStatusPtr)))
        {
            /* Not initialized Controller */
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                                (uint8)CAN_INSTANCE_ID, \
                                (uint8)CAN_SID_MB_IRQHANDLE, \
                                (uint8)CAN_E_UNINIT);
        }
        else if(CoreId != (Can_ConfigPtr->ControllerMapListPtr[Controller]))
        {
        /* Not Can Controller configured in current core */
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                                (uint8)CAN_INSTANCE_ID, \
                                    (uint8)CAN_SID_MB_IRQHANDLE, \
                                (uint8)CAN_E_CORE_CONTROLLER_MISMATCH);
        }
        else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
        {
            /* Clean the interrupt flag */
            /* SWS_Can_00420:
                The Can module shall reset the interrupt flag at the end of the ISR (if not done
            automatically by hardware). */
            Can_Hal_ClearInterruptFlag(CanNodePtr, CAN_IT_MSGDEDICATEDRXBUF);

            /* Update current controller RxBufferMessage info */
            MessageIdxMask = Can_Hal_GetRxBufferMessageIndex(CanNodePtr);

            /* Polling the index of the set Message */
            while (0ULL != MessageIdxMask)
            {
                /* Get the index of the Message mailbox */
                Hrh = Can_Clz64(&MessageIdxMask);
                
                /* Clear the corresponding bit in the Mask */
                /* #Violation: Can_c_REF_4 */
                CAN_CLRBITS(&MessageIdxMask, (63U - Hrh)); 

                /* Get the real ID of mailbox */
                Hrh = CAN_CONTROLLER_CFG(CoreId,ControllerToCore,
                        MsgRAMMapConfigPtr->RxBufferIndexMap[(63U - Hrh)]);

                /* Check the interrupt mode currently used by the mailbox */
                if(FALSE == CAN_HWOBJ_CFG(Hrh,UsesPolling))
                {
                    /* Process the message with Hoh index */
                    Can_RxProcessing(Controller, Hrh, CAN_MSG_DED_BUFFER);
                }
            }
        }
    }
}
#endif /* ((CAN_CONTROLLER_RX_INTERRUPT_SUPPORT \== STD_ON)) */

#if ((CAN_CONTROLLER_RXFIFO_INTERRUPT_SUPPORT == STD_ON))
/****************************************************************************************************
*   Function Name           : Can_RXFIFO_IRQHandler
*
*   Service ID              : 0xE5.
*
*   Description             : This function is used to handle the RXFIFO interrupt.
*                     
*   Parameters in           : Controller: CAN controller for which result of the interrupt.
*                                         It's the logical controller.

*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant for different HW, Non-Reentrant for same HW
*
*   Return value            : None
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None
****************************************************************************************************/
FUNC(void, CAN_PUBLIC_CODE) Can_RXFIFO_IRQHandler
(
    CONST(uint8, AUTOMATIC) Controller
)
{
    Mcal_CoreType    CoreId;
    Can_HwHandleType Hrh;
    Can_HwHandleType HrhCount;
    uint32           InterruptFlag;
    uint8            ControllerToCore;
    CAN_NODE         *CanNodePtr;

    if(NULL_PTR != Can_ConfigPtr)
    {
        /* Get core id which is executing currently */
        /* #Violation: Can_c_REF_4*/
        CoreId = Mcal_GetCoreId();

        /* Get the controller config set index */
        ControllerToCore = Can_ConfigPtr->ControllerToCorePtr[Controller];

        /* Get the controller node address */
        /* #Violation: Can_c_REF_4*/
        CanNodePtr = CAN_BASE_ADDR(CoreId,ControllerToCore);
#if (CAN_DEV_ERROR_DETECT == STD_ON)
        if((NULL_PTR ==(Can_CoreStateArray[CoreId]))|| \
            (CAN_UNINIT == *(Can_CoreStateArray[CoreId]->CanInitStatusPtr)))
        {
            /* Not initialized Controller */
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                                (uint8)CAN_INSTANCE_ID, \
                                (uint8)CAN_SID_RXFIFO_IRQHANDLE, \
                                (uint8)CAN_E_UNINIT);
        }
        else if(CoreId != (Can_ConfigPtr->ControllerMapListPtr[Controller]))
        {
        /* Not Can Controller configured in current core */
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                                (uint8)CAN_INSTANCE_ID, \
                                    (uint8)CAN_SID_RXFIFO_IRQHANDLE, \
                                (uint8)CAN_E_CORE_CONTROLLER_MISMATCH);
        }
        else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
        {
            InterruptFlag = Can_Hal_GetInterruptFlag(CanNodePtr);
            /* Check RXFIFO0 */
            if(0U != (CAN_IT_RXFIFO0MSGLOST & InterruptFlag))
            {
                /* SWS_Can_00420:
                    The Can module shall reset the interrupt flag at the end of the ISR (if not done
                automatically by hardware). */
                /* Clear Rx FIFO 0 "overwrite" or "overrun" flags  */
                Can_Hal_ClearInterruptFlag(CanNodePtr,CAN_IT_RXFIFO0MSGLOST);

                /* SWS_Can_00395:(For RxFIFO0)
                    Can module shall raise the runtime error CAN_E_DATALOST in case of "overwrite" or
                "overrun" event detection. */
                (void)Det_ReportRuntimeError((uint16)CAN_MODULE_ID, \
                                            (uint8)CAN_INSTANCE_ID, \
                                            (uint8)CAN_SID_RXFIFO_IRQHANDLE, \
                                            (uint8)CAN_E_DATALOST);
            }
            else
            {
                /* SWS_Can_00420:
                    The Can module shall reset the interrupt flag at the end of the ISR (if not done
                automatically by hardware). */
                /* Clean the interrupt flag, only enable RXFIFO WMREACHED and FULL Interrupt */
                Can_Hal_ClearInterruptFlag(CanNodePtr, \
                        CAN_IT_RXFIFO0MSG | CAN_IT_RXFIFO0WMREACHED | CAN_IT_RXFIFO0FULL);
            }

            /* Check RXFIFO1 */
            if( 0U != (CAN_IT_RXFIFO1MSGLOST & InterruptFlag))
            {
                /* SWS_Can_00420:
                    The Can module shall reset the interrupt flag at the end of the ISR (if not done
                automatically by hardware). */
                /* Clear Rx FIFO 1 'overwrite' or 'overrun' flags  */
                Can_Hal_ClearInterruptFlag(CanNodePtr,CAN_IT_RXFIFO1MSGLOST);

                /* SWS_Can_00395:(For RxFIFO1)
                    Can module shall raise the runtime error CAN_E_DATALOST in case of "overwrite" or
                "overrun" event detection. */
                (void)Det_ReportRuntimeError((uint16)CAN_MODULE_ID, \
                                            (uint8)CAN_INSTANCE_ID, \
                                            (uint8)CAN_SID_RXFIFO_IRQHANDLE, \
                                            (uint8)CAN_E_DATALOST);
            }
            else
            {
                /* SWS_Can_00420:
                    The Can module shall reset the interrupt flag at the end of the ISR (if not done
                automatically by hardware). */
                /* Clean the interrupt flag,only enable RXFIFO WMREACHED and FULL Interrupt */
                Can_Hal_ClearInterruptFlag(CanNodePtr, \
                        CAN_IT_RXFIFO1MSG | CAN_IT_RXFIFO1WMREACHED | CAN_IT_RXFIFO1FULL);
            }

            /* Find out maximum MaxCoreHrhChannels */
            for(HrhCount = 0U; HrhCount < CAN_CONTROLLER_CFG(CoreId,
                        ControllerToCore,MsgRAMMapConfigPtr->RxFIFONum); HrhCount++)
            {
                /* Get the ID number of the receiving FIFO mailbox */
                Hrh = CAN_CONTROLLER_CFG(CoreId,ControllerToCore,
                            MsgRAMMapConfigPtr->RxFIFOIndexMap[HrhCount]);

                /* Check the Hrh is belong to the controller and hardware object not uses polling */
                if(FALSE == CAN_HWOBJ_CFG(Hrh,UsesPolling))
                {
                    /* Process the message with Hrh index */
                    Can_RxProcessing(Controller,Hrh,CAN_HWOBJ_CFG(Hrh,MsgRamType));
                }
            }
        }
    }
}
#endif /* ((CAN_CONTROLLER_RXFIFO_INTERRUPT_SUPPORT \== STD_ON)) */

#if ((CAN_CONTROLLER_TX_INTERRUPT_SUPPORT == STD_ON))
/****************************************************************************************************
*   Function Name           : Can_TxEvent_IRQHandler
*
*   Service ID              : 0xE4.
*
*   Description             : This function is used to handle the Txevent interrupt.
*                     
*   Parameters in           : Controller: CAN controller for which result of the interrupt.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant for different HW, Non-Reentrant for same HW
*
*   Return value            : None
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, CAN_PUBLIC_CODE) Can_TxEvent_IRQHandler
(
    CONST(uint8, AUTOMATIC) Controller
)
{
    Mcal_CoreType    CoreId;
    uint8            ControllerToCore;
    uint32           InterruptFlag;
    Can_HwHandleType Hth;
    Can_HwHandleType HthCount;

    /* Non-AUTOSAR: guard against a TX-event interrupt firing before Can_Init() has run (or after
       Can_DeInit()), matching the same NULL check already used by Can_MB_IRQHandler/
       Can_RXFIFO_IRQHandler. */
    if(NULL_PTR != Can_ConfigPtr)
    {
        /* Get core id which is executing currently */
        CoreId = Mcal_GetCoreId();

        /* Get the controller config set index */
        ControllerToCore = Can_ConfigPtr->ControllerToCorePtr[Controller];

#if (CAN_DEV_ERROR_DETECT == STD_ON)
        if((NULL_PTR ==(Can_CoreStateArray[CoreId]))|| \
            (CAN_UNINIT == *(Can_CoreStateArray[CoreId]->CanInitStatusPtr)))
        {
           (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                                 (uint8)CAN_INSTANCE_ID, \
                                 (uint8)CAN_SID_TXEVENT_IRQHANDLE, \
                                 (uint8)CAN_E_UNINIT);
        }
        else if(CoreId != Can_ConfigPtr->ControllerMapListPtr[Controller])
        {
            /* Not Can Controller configured in current core */
           (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                                 (uint8)CAN_INSTANCE_ID, \
                                    (uint8)CAN_SID_TXEVENT_IRQHANDLE, \
                                 (uint8)CAN_E_CORE_CONTROLLER_MISMATCH);
        }
        else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
        {
            /* Check TX event FIFO data lost? */
            InterruptFlag = Can_Hal_GetInterruptFlag(CAN_BASE_ADDR(CoreId,ControllerToCore));
            if (0U != (CAN_IT_TXEVENTFIFOEVENTLOST & InterruptFlag))
            {
                /* Clean all Tx event flag */
                Can_Hal_ClearInterruptFlag(CAN_BASE_ADDR(CoreId,ControllerToCore),
                    CAN_IT_TXEVENTFIFOEVENTLOST);

                /* SWS_Can_00395:
                    Can module shall raise the runtime error CAN_E_DATALOST in case of "overwrite" or
                   "overrun" event detection. */
                (void)Det_ReportRuntimeError((uint16)CAN_MODULE_ID, \
                                             (uint8)CAN_INSTANCE_ID, \
                                             (uint8)CAN_SID_TXEVENT_IRQHANDLE, \
                                             (uint8)CAN_E_DATALOST);
            }
            else
            {
                /* Clean the interrupt flag */
                Can_Hal_ClearInterruptFlag(CAN_BASE_ADDR(CoreId,ControllerToCore), \
                            CAN_IT_TXEVENTFIFONEWENTRY | CAN_IT_TXEVENTFIFOWMREACHED);
            }

            /* SWS_Can_00178:
                The Can module may implement the function Can_MainFunction_Write as empty define in case
               no polling at all is used. */
            for(HthCount = 0U; HthCount < CAN_CONTROLLER_CFG(CoreId,
                        ControllerToCore,MsgRAMMapConfigPtr->HthNum); HthCount++)
            {
                /* Get the ID number of the TX mailbox */
                Hth = CAN_CONTROLLER_CFG(CoreId,ControllerToCore,
                                MsgRAMMapConfigPtr->HthIndexMap[HthCount]);
                /**
                 * +---------------------------------------+---------+-------+-----------+
                 * |                                       | POLLING | MIXED | INTERRUPT |
                 * +---------------------------------------+---------+-------+-----------+
                 * | CanHardwareObjectUsesPolling  = TRUE  |   O     |  O    |    X      |
                 * | CanHardwareObjectUsesPolling  = FALSE |   O     |  X    |    X      |
                 * +---------------------------------------+---------+-------+-----------+
                 */
                /* SWS_Can_00031:
                    The function Can_MainFunction_Write shall perform the polling of TX
                    confirmation when CanTxProcessing  is set to POLLING or MIXED. In case of
                    MIXED processing only the hardware objects for which CanHardwareObjectUsesPolling
                    is set to TRUE shall be polled. */
                if (FALSE == CAN_HWOBJ_CFG(Hth,UsesPolling))
                {
                    /* Process the Tx events */
                    Can_TxProcessing(Controller,Hth);
                }
            }
        }
    }
}
#endif /* ((CAN_CONTROLLER_TX_INTERRUPT_SUPPORT \== STD_ON)) */

#if (CAN_CONTROLLER_BUSOFF_INTERRUPT_SUPPORT == STD_ON)
/****************************************************************************************************
*   Function Name           : Can_BusOff_IRQHandler
*
*   Service ID              : 0xE2.
*
*   Description             : This function is used to handle the BusOff interrupt.
*                     
*   Parameters in           : Controller: CAN controller for which result of the interrupt.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant for different HW, Non-Reentrant for same HW
*
*   Return value            : None
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None
****************************************************************************************************/
FUNC(void, CAN_PUBLIC_CODE) Can_BusOff_IRQHandler
(
    CONST(uint8, AUTOMATIC) Controller
)
{
    Mcal_CoreType CoreId;
    uint8 ControllerToCore;

    /* Non-AUTOSAR: guard against a bus-off interrupt firing before Can_Init() has run (or after
       Can_DeInit()), matching the same NULL check already used by Can_MB_IRQHandler/
       Can_RXFIFO_IRQHandler. */
    if(NULL_PTR != Can_ConfigPtr)
    {
        /* Get core id which is executing currently */
        CoreId = Mcal_GetCoreId();

        /* Get the controller config set index */
        ControllerToCore = Can_ConfigPtr->ControllerToCorePtr[Controller];

#if (CAN_DEV_ERROR_DETECT == STD_ON)
        if((NULL_PTR ==(Can_CoreStateArray[CoreId]))|| \
            (CAN_UNINIT == *(Can_CoreStateArray[CoreId]->CanInitStatusPtr)))
        {
            (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                                  (uint8)CAN_INSTANCE_ID, \
                                  (uint8)CAN_SID_BUSOFF_IRQHANDLE, \
                                  (uint8)CAN_E_UNINIT);
        }
        else if(CoreId != Can_ConfigPtr->ControllerMapListPtr[Controller])
        {
            /* Not Can Controller configured in current core */
            (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                                  (uint8)CAN_INSTANCE_ID, \
                                  (uint8)CAN_SID_BUSOFF_IRQHANDLE, \
                                  (uint8)CAN_E_CORE_CONTROLLER_MISMATCH);
        }
        else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
        {
            /* Clean the interrupt flag */
            Can_Hal_ClearInterruptFlag(CAN_BASE_ADDR(CoreId,ControllerToCore),CAN_IT_BUSOFFSTATUS);

            /* Process BUSOFF interrupt */
            Can_CheckBusOffEvent(Controller);
        }
    }
}
#endif /* (CAN_CONTROLLER_BUSOFF_INTERRUPT_SUPPORT  \== STD_ON) */

#if (CAN_NOACK_ERR_SUPPORTED == STD_ON)
/****************************************************************************************************
*   Function Name           : Can_MainFunction_NoAck
*
*   Service ID              : None.
*
*   Description             : This function is used to handle the ACKERR.
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
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_NoAck
(
    void
)
{
    uint8 Index;
    uint32 ProtocolStatus;
    Mcal_CoreType CoreId;

    /* Get core id which is executing currently */
    CoreId = Mcal_GetCoreId();

#if (CAN_DEV_ERROR_DETECT == STD_ON)
    if((NULL_PTR ==(Can_CoreStateArray[CoreId]))|| \
        (CAN_UNINIT == *(Can_CoreStateArray[CoreId]->CanInitStatusPtr)))
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_MAIN_FUNCTION_NO_ACK, \
                              (uint8)CAN_E_UNINIT);
    }
    else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_ON) */
    {
         for(Index = 0U; Index < CAN_CORE_CFG(CoreId,MaxCoreController);
             Index++)
         {
             /* Check the controller of the physical controller */
            ProtocolStatus = Can_Hal_GetProtocolStatus(CAN_BASE_ADDR(CoreId,Index));

            /* Check is noack event occur? */
            if(0x03UL == (CAN_PROTOCOL_LEC & ProtocolStatus)) 
             {
                 (void)CanIf_ControllerNoAck(Can_ConfigPtr->CoreConfigPtr[CoreId]-> \
                                                 CanControllerCfgPtr[Index].LogicalID);
             }
         }
    }
}
#endif /* (CAN_NOACK_ERR_SUPPORTED  \== STD_ON) */

/****************************************************************************************************
*   Function Name           : Can_MainFunction_CommonWrite
*
*   Service ID              : None.
*
*   Description             : This function performs the polling of TX confirmation when
*                             CAN_TX_PROCESSING is set to POLLING.
*
*   Parameters in           : MainFunction_Index: The Index of Read and Write mainfunction.
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
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Can_00225
****************************************************************************************************/
/* #Violation: Can_c_REF_6 */
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_CommonWrite
(
    uint8 MainFunction_Index
)
{
    Can_MainFunctionWriteHandler(MainFunction_Index);
}

/****************************************************************************************************
*   Function Name           : Can_MainFunction_CommonRead
*
*   Service ID              : None.
*
*   Description             : This function performs the polling of RX indications when
*                             Can_RxProcessing is set to POLLING.
*
*   Parameters in           : MainFunction_Index: The Index of Read and Write mainfunction.
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
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Can_00226
****************************************************************************************************/
/* #Violation: Can_c_REF_18 */
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_CommonRead
(
    uint8 MainFunction_Index
)
{
#if ((CAN_CONTROLLER_RX_POLLING_SUPPORT == STD_OFF) || (CAN_NUMBER_OF_MAINFUNCTION_RW_PERIOD == 0U))
    MCAL_UNUSED_VAR(MainFunction_Index);
#endif /* (CAN_CONTROLLER_RX_POLLING_SUPPORT \== STD_OFF) || 
            (CAN_NUMBER_OF_MAINFUNCTION_RW_PERIOD \== 0U) */

    /* SWS_Can_00180:
        The Can module may implement the function Can_MainFunction_Read as empty define in case no
       polling at all is used. */
#if (CAN_CONTROLLER_RX_POLLING_SUPPORT == STD_ON)
    Can_HwHandleType Hrh;
    uint8            Controller;
    uint8            ControllerLoop;
    uint32           FifoLevel;
    Mcal_CoreType    CoreId;
    uint32           InterruptFlag;
    uint64           MessageIdxMask;
    CAN_NODE         *CanNodePtr;

    /* Get core id which is executing currently */
    /* #Violation: Can_c_REF_4*/
    CoreId = Mcal_GetCoreId();

#if (CAN_DEV_ERROR_DETECT == STD_ON)
    if(NULL_PTR == Can_ConfigPtr->CoreConfigPtr[CoreId])
    {
        /* The current core is not used, check the controller configuration.*/
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_MAIN_FUNCTION_READ, \
                              (uint8)CAN_E_CORE_NOT_CONFIGURED);
    }
    else if(CAN_UNINIT == *(Can_CoreStateArray[CoreId]->CanInitStatusPtr))
    {

        /* SWS_Can_00181:
         Shall raise the error CAN_E_UNINIT if the driver is not yet initialized. */
        (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                              (uint8)CAN_INSTANCE_ID, \
                              (uint8)CAN_SID_MAIN_FUNCTION_READ, \
                              (uint8)CAN_E_UNINIT);
    }
    else
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_OFF) */
    {
        /* SWS_Can_00180:
            The Can module may implement the function Can_MainFunction_Read as empty define in case
           no polling at all is used. */  
        for(ControllerLoop = 0U; 
            ControllerLoop < CAN_CORE_CFG(CoreId,MaxCoreController); ControllerLoop++)
        {
        /* Get the controller node address */
            /* #Violation: Can_c_REF_4*/
            CanNodePtr = CAN_BASE_ADDR(CoreId,ControllerLoop);

            /* Get the controller to HardwareObject map. */
            Controller = CAN_CONTROLLER_CFG(CoreId,ControllerLoop,LogicalID);

            /* Update interrupt flag */
            InterruptFlag = Can_Hal_GetInterruptFlag(CanNodePtr);

            if( 0U != (CAN_IT_RXFIFO0MSGLOST & InterruptFlag) )
            {
                /* Clear Rx FIFO 0 "overwrite" or "overrun" flags  */
                Can_Hal_ClearInterruptFlag(CanNodePtr, CAN_IT_RXFIFO0MSGLOST);

                /* SWS_Can_00395:(For RxFIFO0)
                    Can module shall raise the runtime error CAN_E_DATALOST in case of "overwrite" or
                "overrun" event detection. */
                (void)Det_ReportRuntimeError((uint16)CAN_MODULE_ID, \
                                            (uint8)CAN_INSTANCE_ID, \
                                            (uint8)CAN_SID_MAIN_FUNCTION_READ, \
                                            (uint8)CAN_E_DATALOST);
            }
            else if( 0U != (CAN_IT_RXFIFO1MSGLOST & InterruptFlag) )
            {
                /* Clear Rx FIFO 1 "overwrite" or "overrun" flags  */
                Can_Hal_ClearInterruptFlag(CanNodePtr, CAN_IT_RXFIFO1MSGLOST);

                /* SWS_Can_00395:(For RxFIFO1)
                    Can module shall raise the runtime error CAN_E_DATALOST in case of "overwrite" or
                "overrun" event detection. */
                (void)Det_ReportRuntimeError((uint16)CAN_MODULE_ID, \
                                            (uint8)CAN_INSTANCE_ID, \
                                            (uint8)CAN_SID_MAIN_FUNCTION_READ, \
                                            (uint8)CAN_E_DATALOST);
            }
#if (CAN_DEV_ERROR_DETECT == STD_ON)
            /* Detect the ControllerToCore is current Core or not.
            * Avoid access an undefined region. */
            else if(CoreId != (Can_ConfigPtr->ControllerMapListPtr[Controller]))
            {
                /* Not Can Controller configured in current core */
                (void)Det_ReportError((uint16)CAN_MODULE_ID, \
                                    (uint8)CAN_INSTANCE_ID,\
                                    (uint8)CAN_SID_MAIN_FUNCTION_READ,\
                                    (uint8)CAN_E_CORE_CONTROLLER_MISMATCH);
            }
#endif /* (CAN_DEV_ERROR_DETECT  \== STD_OFF) */
            else
            {
                /* Check the Rx FIFO0 fill level is over threshold? */
                FifoLevel = Can_Hal_GetRxFifo0FillLevel(CanNodePtr);

                if((0U < FifoLevel) && 
                    (0U < CAN_CONTROLLER_CFG(CoreId,ControllerLoop, MsgRAMMapConfigPtr->RxFIFONum)))
                {
                    /* Get the ID number of the receiving FIFO mailbox */
                    Hrh = CAN_CONTROLLER_CFG(CoreId,ControllerLoop,
                                MsgRAMMapConfigPtr->RxFIFOIndexMap[0U]);

                    if((CAN_INTERRUPT != CAN_CONTROLLER_CFG(CoreId,ControllerLoop,RxProcessing))
                        &&(FifoLevel >= CAN_HWOBJ_CFG(Hrh,HwObjectFIFOThreshold))
#if (CAN_NUMBER_OF_MAINFUNCTION_RW_PERIOD > 0U)
                    /* Only HOBs that match the period can be processed when more than one main function
                    period is configured */
                        &&(MainFunction_Index == (uint32)CAN_HWOBJ_CFG(Hrh,CanMainFuncRWPeriodRef))
#endif /* (CAN_NUMBER_OF_MAINFUNCTION_RW_PERIOD \> 0U) */
                    )
                    {
                        Can_RxProcessing(Controller, Hrh,CAN_MSG_FIFO0);
                    }
                }

                /* Check the Rx FIFO1 fill level is over threshold? */
                FifoLevel = Can_Hal_GetRxFifo1FillLevel(CanNodePtr);

                if((0U < FifoLevel) &&
                    (0U < CAN_CONTROLLER_CFG(CoreId,ControllerLoop, MsgRAMMapConfigPtr->RxFIFONum)))
                {
                    /* Get the ID number of the receiving FIFO mailbox */
                    Hrh = CAN_CONTROLLER_CFG(CoreId,ControllerLoop,
                                MsgRAMMapConfigPtr->RxFIFOIndexMap[1U]);

                    if((CAN_INTERRUPT != CAN_CONTROLLER_CFG(CoreId,ControllerLoop,RxProcessing))
                        &&(FifoLevel >= CAN_HWOBJ_CFG(Hrh,HwObjectFIFOThreshold))
#if (CAN_NUMBER_OF_MAINFUNCTION_RW_PERIOD > 0U)
                    /* Only HOBs that match the period can be processed when more than one main function
                    period is configured */
                        &&(MainFunction_Index == (uint32)CAN_HWOBJ_CFG(Hrh,CanMainFuncRWPeriodRef))
#endif /* (CAN_NUMBER_OF_MAINFUNCTION_RW_PERIOD \> 0U) */
                    )
                    {
                        Can_RxProcessing(Controller, Hrh,CAN_MSG_FIFO1);
                    }
                }

                /* Update current controller RxBufferMessage info */
                MessageIdxMask = Can_Hal_GetRxBufferMessageIndex(CanNodePtr);

                /* Polling the index of the set Message */
                while (0UL != MessageIdxMask)
                {
                    /* Get the index of the Message foxmail */
                    Hrh = Can_Clz64(&MessageIdxMask);
                    
                    /* Clear the corresponding bit in the Mask */
                    /* #Violation: Can_c_REF_4 */
                    CAN_CLRBITS(&MessageIdxMask, (63U - Hrh));
                    
                    /* Get the real ID of foxmail */
                    Hrh = CAN_CONTROLLER_CFG(CoreId,ControllerLoop,MsgRAMMapConfigPtr->RxBufferIndexMap[(63U - Hrh)]);

                    if((CAN_INTERRUPT != CAN_CONTROLLER_CFG(CoreId,ControllerLoop,RxProcessing))
#if (CAN_NUMBER_OF_MAINFUNCTION_RW_PERIOD > 0U)
                    /* Only HOBs that match the period can be processed when more than one main function
                    period is configured */
                    &&(MainFunction_Index == (uint32)CAN_HWOBJ_CFG(Hrh,CanMainFuncRWPeriodRef))
#endif /* (CAN_NUMBER_OF_MAINFUNCTION_RW_PERIOD \> 0U) */
                    )
                    {
                        /**
                        * +---------------------------------------+---------+-------+-----------+
                        * |                                       | POLLING | MIXED | INTERRUPT |
                        * +---------------------------------------+---------+-------+-----------+
                        * | CanHardwareObjectUsesPolling  = TRUE  |   O     |  O    |    X      |
                        * | CanHardwareObjectUsesPolling  = FALSE |   O     |  X    |    X      |
                        * +---------------------------------------+---------+-------+-----------+
                        */
                        /* SWS_Can_00031:
                            The function Can_MainFunction_Write shall perform the polling of TX
                         confirmation when CanTxProcessing  is set to POLLING or MIXED. In case of
                         MIXED processing only the hardware objects for which CanHardwareObjectUsesPolling
                         is set to TRUE shall be polled. */
                        if(TRUE == CAN_HWOBJ_CFG(Hrh,UsesPolling))
                        {
                            /* Process the message with Hoh index */
                            Can_RxProcessing(Controller, Hrh, CAN_MSG_DED_BUFFER);
                        }
                    }
                }
            }
        }
    }
#endif /* (CAN_CONTROLLER_RX_POLLING_SUPPORT  \== STD_ON) */
}
/* #Violation: Can_c_REF_9*/
#define CAN_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Can_c_REF_11 */
#include "Can_MemMap.h"

