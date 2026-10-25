/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Can.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : MCAN
*
*   brief                 : This file contains all function declarations of Can Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
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
*#Can_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*/
#ifndef CAN_H_
#define CAN_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Can_Version.h"
#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"
#include "Can_Cfg.h"
#include "Can_PBcfg.h"
#include "can_hal.h"

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
/*Development errors*/
/* API Service called with wrong parameter */
#define CAN_E_PARAM_POINTER                        ((uint8)0x01U)
#define CAN_E_PARAM_HANDLE                         ((uint8)0x02U)
#define CAN_E_PARAM_DATA_LENGTH                    ((uint8)0x03U)
#define CAN_E_PARAM_CONTROLLER                     ((uint8)0x04U)
/* API Service used without initialization */     
#define CAN_E_UNINIT                               ((uint8)0x05U)
/* Invalid transition for the current mode */     
#define CAN_E_TRANSITION                           ((uint8)0x06U)
/* Parameter Baudrate has an invalid value */     
#define CAN_E_PARAM_BAUDRATE                       ((uint8)0x07U)
/* Invalid ICOM Configuration Id */     
/* #Violation: Can_h_REF_1 */
#define CAN_E_ICOM_CONFIG_INVALID                  ((uint8)0x08U)
/* Invalid configuration set selection */     
/* #Violation: Can_h_REF_1 */
#define CAN_E_INIT_FAILED                          ((uint8)0x09U)
     
/*Runtime errors*/     
/* Received CAN message is lost */     
#define CAN_E_DATALOST                             ((uint8)0x01U)

/* Non-AUTOSAR */
/* Report DET CAN module not configured for current Core */
#define CAN_E_CORE_NOT_CONFIGURED                  ((uint8)0xE0U)
/* CAN Controller is not allocated to current      core */
#define CAN_E_CORE_CONTROLLER_MISMATCH             ((uint8)0xE1U)
/* CAN Abort pending messages failed */
/* #Violation: Can_h_REF_1 */
#define CAN_E_ABORT_PENGING_MSG                    ((uint8)0xE2U)
/* CAN Disable Controller_Interrupts failed */
#define CAN_E_DISABLE_CONTROLLER_INTERRUPTS        ((uint8)0xE3U)
/* CAN Enable Controller_Interrupts failed */
#define CAN_E_ENABLE_CONTROLLER_INTERRUPTS         ((uint8)0xE4U)

/*Service ID (APIs) for Det reporting*/
#define CAN_SID_INIT                               ((uint8)0x00U)
#define CAN_SID_MAIN_FUNCTION_WRITE                ((uint8)0x01U)
#define CAN_SID_SET_CONTROLLER_MODE                ((uint8)0x03U)
#define CAN_SID_DISABLE_CONTROLLER_INTERRUPTS      ((uint8)0x04U)
#define CAN_SID_ENABLE_CONTROLLER_INTERRUPTS       ((uint8)0x05U)
#define CAN_SID_WRITE                              ((uint8)0x06U)
#define CAN_SID_GET_VERSION_INFO                   ((uint8)0x07U)
#define CAN_SID_MAIN_FUNCTION_READ                 ((uint8)0x08U)
#define CAN_SID_MAIN_FUNCTION_BUS_OFF              ((uint8)0x09U)
#define CAN_SID_MAIN_FUNCTION_WAKEUP               ((uint8)0x0AU)
#define CAN_SID_CBK_CHECK_WAKEUP                   ((uint8)0x0BU)
#define CAN_SID_MAIN_FUNCTION_MODE                 ((uint8)0x0CU)
#define CAN_SID_SET_BAUDRATE                       ((uint8)0x0FU)
#define CAN_SID_DEINIT                             ((uint8)0x10U)
#define CAN_SID_GET_CONTROLLER_ERROR_STATE         ((uint8)0x11U)
#define CAN_SID_GET_CONTROLLER_MODE                ((uint8)0x12U)
/* #Violation: Can_h_REF_1 */
#define CAN_SID_LPDU_CALLOUT                       ((uint8)0x20U)
/* #Violation: Can_h_REF_1 */
#define CAN_SID_SET_ICOM_CONFIG                    ((uint8)0x21U)
#define CAN_SID_GET_CONTROLLER_RX_ERROR_COUNTER    ((uint8)0x30U)
#define CAN_SID_GET_CONTROLLER_TX_ERROR_COUNTER    ((uint8)0x31U)

/* Non-AUTOSAR */
/* #Violation: Can_h_REF_1 */
#define CAN_SID_MAIN_FUNCTION_NO_ACK               ((uint8)0xE0U)
#define CAN_SID_MB_IRQHANDLE                       ((uint8)0xE1U)
/* #Violation: Can_h_REF_1 */
#define CAN_SID_BUSOFF_IRQHANDLE                   ((uint8)0xE2U)
/* #Violation: Can_h_REF_1 */
#define CAN_SID_WAKEUP_IRQHANDLE                   ((uint8)0xE3U)
/* #Violation: Can_h_REF_1 */
#define CAN_SID_TXEVENT_IRQHANDLE                  ((uint8)0xE4U)
#define CAN_SID_RXFIFO_IRQHANDLE                   ((uint8)0xE5U)
#define CAN_SID_RX_PROCESSING                      ((uint8)0xE6U)

/* Values used for FD mask and Extended Id Mask */
/* #Violation: Can_h_REF_1 */
#define CAN_EXTENDED_IDMASK                        ((Can_IdType)0x80000000UL)
/* #Violation: Can_h_REF_1 */
#define CAN_STANDARD_FD_IDMASK                     ((Can_IdType)0x40000000UL)
#define CAN_FD_FRAME_FORMAT                        ((Can_IdType)0x40000000UL)
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
*   AUTOSAR_Requirement     : SWS_Can_00223
****************************************************************************************************/
extern FUNC(void, CAN_PUBLIC_CODE) Can_Init
(
    CONSTP2CONST(Can_ConfigType, AUTOMATIC, CAN_APPL_CONST) ConfigPtr
);

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
#if (CAN_VERSION_INFO_API == STD_ON)
extern FUNC(void, CAN_PUBLIC_CODE) Can_GetVersionInfo
(
    CONSTP2VAR(Std_VersionInfoType, AUTOMATIC, CAN_APPL_DATA) VersioninfoPtr
);
#endif /* (CAN_VERSION_INFO_API  \== STD_ON) */

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
extern FUNC(Std_ReturnType, CAN_CODE) Can_DeInit
(
    void
);

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
*                             BaudRateConfigID: references a baud rate configuration by ID 
*                             ,see CanControllerBaudRateConfigID
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
#if (CAN_SET_BAUDRATE_API == STD_ON)
extern FUNC(Std_ReturnType, CAN_PUBLIC_CODE) Can_SetBaudrate
(
    uint8 Controller, 
    uint16 BaudRateConfigID
);
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
*   Return value            : CAN_OK: request accepted
*                             CAN_NOT_OK: request not accepted, a development error occurred
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Can_00230
****************************************************************************************************/
extern FUNC(Std_ReturnType, CAN_PUBLIC_CODE) Can_SetControllerMode
(
    uint8 Controller, 
    Can_ControllerStateType Can_Transition
);

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
*   AUTOSAR_Requirement     : SWS_Can_00231
****************************************************************************************************/
extern FUNC(void, CAN_PUBLIC_CODE) Can_DisableControllerInterrupts
(
    uint8 Controller
);

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
extern FUNC(void, CAN_PUBLIC_CODE) Can_EnableControllerInterrupts
(
    uint8 Controller
);

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
*   Return value            : CAN_OK: API call has been accepted
*                             CAN_NOT_OK: API call has not been accepted
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Can_00360
****************************************************************************************************/
#if (CAN_CHECK_WAKEUP_API_SUPPORT == STD_ON)
extern FUNC(Std_ReturnType, CAN_PUBLIC_CODE) Can_CheckWakeup
(
    uint8 Controller
);
#endif /* (CAN_CHECK_WAKEUP_API_SUPPORT  \== STD_ON) */

/****************************************************************************************************
*   Function Name           : Can_GetControllerErrorState
*
*   Service ID              : 0x11.
*
*   Description             : This service obtains the error state of the CAN controller.
*                     
*   Parameters in           : Controller: Abstracted CanIf ControllerId which is assigned to
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
extern FUNC(Std_ReturnType, CAN_PUBLIC_CODE) Can_GetControllerErrorState
(
    uint8 Controller,
    CONSTP2VAR(Can_ErrorStateType, AUTOMATIC, CAN_APPL_CONST) ErrorStatePtr
);

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
*   Return value            : E_OK: Error state request has been accepted.
*                             E_NOT_OK: Error state request has not been accepted.
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Can_91014
****************************************************************************************************/
extern FUNC(Std_ReturnType, CAN_PUBLIC_CODE) Can_GetControllerMode
(
    uint8 Controller,
    CONSTP2VAR(Can_ControllerStateType, AUTOMATIC, CAN_APPL_CONST) ControllerModePtr
);

/****************************************************************************************************
*   Function Name           : Can_GetControllerRxErrorCounter
*
*   Service ID              : 0x30.
*
*   Description             : Returns the Rx error counter for a CAN controller. 
*                             This value might not be available for all CAN controllers, in which case
*                             E_NOT_OK would be returned.
*                     
*   Parameters in           : Controller: CAN controller, whose current Rx error counter shall be
*                             acquired.
*
*   Parameters inout        : None.
*
*   Parameters out          : RxErrorCounterPtr: Pointer to a memory location, where the current mode
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
extern FUNC(Std_ReturnType, CAN_PUBLIC_CODE) Can_GetControllerRxErrorCounter
(
    uint8 Controller,
    P2VAR(uint8, AUTOMATIC, CAN_APPL_CONST) RxErrorCounterPtr
);

/****************************************************************************************************
*   Function Name           : Can_GetControllerTxErrorCounter
*
*   Service ID              : 0x31.
*
*   Description             : Returns the Tx error counter for a CAN controller. 
*                             This value might not be available for all CAN controllers, in which case
*                             E_NOT_OK would be returned.
*                     
*   Parameters in           : ControllerId: CAN controller, whose current Tx error counter shall be
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
extern FUNC(Std_ReturnType, CAN_PUBLIC_CODE) Can_GetControllerTxErrorCounter
(
    uint8 Controller,
    CONSTP2VAR(uint8, AUTOMATIC, CAN_APPL_CONST) TxErrorCounterPtr
);

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
*   Return value            : CAN_OK: Write command has been accepted
*
*                             CAN_NOT_OK: Development error occurred
*
*                             CAN_BUSY: No TX hardware buffer available or pre-emptive call of
*                                         Can_Write that can't be implemented reentrant
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Can_00233
****************************************************************************************************/
extern FUNC(Std_ReturnType, CAN_PUBLIC_CODE) Can_Write
(
    Can_HwHandleType Hth, 
    CONSTP2CONST(Can_PduType, AUTOMATIC, CAN_APPL_CONST) PduInfoPtr
);

/****************************************************************************************************
*   Function Name           : Can_MainFunction_Write
*
*   Service ID              : 0x01.
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
extern FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write
(
    void
);

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
extern FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read
(
    void
);

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
extern FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_BusOff
(
    void
);

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
extern FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Wakeup
(
    void
);

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
extern FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Mode
(
    void
);

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
);
#endif /* (CAN_NOACK_ERR_SUPPORTED  \== STD_ON) */

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
#if((CAN_CONTROLLER_RX_INTERRUPT_SUPPORT == STD_ON) || \
    (CAN_CONTROLLER_TX_INTERRUPT_SUPPORT == STD_ON))
extern FUNC(void, CAN_PUBLIC_CODE) Can_MB_IRQHandler
(
    CONST(uint8, AUTOMATIC) Controller
);
#endif /* (CAN_CONTROLLER_RX_INTERRUPT_SUPPORT == STD_ON) || \
          (CAN_CONTROLLER_TX_INTERRUPT_SUPPORT  \== STD_ON) */

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
#if(CAN_CONTROLLER_TX_INTERRUPT_SUPPORT == STD_ON)
extern FUNC(void, CAN_PUBLIC_CODE) Can_TxEvent_IRQHandler
(
    CONST(uint8, AUTOMATIC) Controller
);
#endif /* (CAN_CONTROLLER_TX_INTERRUPT_SUPPORT  \== STD_ON) */

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
#if(CAN_CONTROLLER_BUSOFF_INTERRUPT_SUPPORT == STD_ON)
extern FUNC(void, CAN_PUBLIC_CODE) Can_BusOff_IRQHandler
(
    CONST(uint8, AUTOMATIC) Controller
);
#endif /* (CAN_CONTROLLER_BUSOFF_INTERRUPT_SUPPORT  \== STD_ON) */

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
#if(CAN_CONTROLLER_RXFIFO_INTERRUPT_SUPPORT == STD_ON)
extern FUNC(void, CAN_PUBLIC_CODE) Can_RXFIFO_IRQHandler
(
    CONST(uint8, AUTOMATIC) Controller
);
#endif /* (CAN_CONTROLLER_RXFIFO_INTERRUPT_SUPPORT  \== STD_ON) */

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
extern FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_CommonWrite
(
    uint8 MainFunction_Index
);
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
extern FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_CommonRead
(
    uint8 MainFunction_Index
);

#endif /* CAN_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/


