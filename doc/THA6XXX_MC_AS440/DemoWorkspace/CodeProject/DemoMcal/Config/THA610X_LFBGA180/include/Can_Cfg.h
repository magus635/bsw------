/**************************************************************************************************
*
***************************************************************************************************/

/**************************************************************************************************
*   FileName             : Can_Cfg.h
*
*   Platform             : AUTOSAR
*
*   Peripheral           : MCAN
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*
*   Build Version        : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/
/**************************************************************************************************/
#ifndef CAN_CFG_H
#define CAN_CFG_H
/***************************************************************************************************
*                            Global Definitions and Macros
****************************************************************************************************/

/***************************************************************************************************
*                               Version Information
***************************************************************************************************/
#define CAN_CFG_H_AR_RELEASE_MAJOR_VERSION           (4U)
#define CAN_CFG_H_AR_RELEASE_MINOR_VERSION           (4U)
#define CAN_CFG_H_AR_RELEASE_REVISION_VERSION        (0U)

#define CAN_CFG_H_SW_MAJOR_VERSION                   (1U)
#define CAN_CFG_H_SW_MINOR_VERSION                   (2U)
#define CAN_CFG_H_SW_PATCH_VERSION                   (0U)

#define CAN_CFG_H_VENDOR_ID                          (175U)
#define CAN_CFG_H_MODULE_ID                          (80U)       /* 0x50U */
/***************************************************************************************************
*                            Definitions and Macros
****************************************************************************************************/
/*The Macros CAN_CONTROLLER_XX defines logical ID corresponding to hardware unit */
#define CAN_CONTROLLER_00                             (0U)
#define CAN_CONTROLLER_00_LOGIC_ID                    (0U)
#define CAN_CONTROLLER_00_BASE_ADDRESS                (CAN00)
#define CAN_CONTROLLER_00_TX_INTERRUPT                (STD_OFF)
#define CAN_CONTROLLER_00_RX_INTERRUPT                (STD_OFF)
#define CAN_CONTROLLER_00_BUSOFF_INTERRUPT            (STD_OFF)
#define CAN_CONTROLLER_00_WAKEUP_INTERRUPT            (STD_OFF)
#define CAN_CONTROLLER_00_RXFIFO_INTERRUPT            (STD_OFF)
/*The Macros CAN_CONTROLLER_XX defines logical ID corresponding to hardware unit */
#define CAN_CONTROLLER_01                             (1U)
#define CAN_CONTROLLER_01_LOGIC_ID                    (1U)
#define CAN_CONTROLLER_01_BASE_ADDRESS                (CAN01)
#define CAN_CONTROLLER_01_TX_INTERRUPT                (STD_OFF)
#define CAN_CONTROLLER_01_RX_INTERRUPT                (STD_ON)
#define CAN_CONTROLLER_01_BUSOFF_INTERRUPT            (STD_OFF)
#define CAN_CONTROLLER_01_WAKEUP_INTERRUPT            (STD_OFF)
#define CAN_CONTROLLER_01_RXFIFO_INTERRUPT            (STD_ON)
/*The Macros CAN_CONTROLLER_XX defines logical ID corresponding to hardware unit */
#define CAN_CONTROLLER_02                             (2U)
#define CAN_CONTROLLER_02_LOGIC_ID                    (2U)
#define CAN_CONTROLLER_02_BASE_ADDRESS                (CAN02)
#define CAN_CONTROLLER_02_TX_INTERRUPT                (STD_OFF)
#define CAN_CONTROLLER_02_RX_INTERRUPT                (STD_OFF)
#define CAN_CONTROLLER_02_BUSOFF_INTERRUPT            (STD_OFF)
#define CAN_CONTROLLER_02_WAKEUP_INTERRUPT            (STD_OFF)
#define CAN_CONTROLLER_02_RXFIFO_INTERRUPT            (STD_OFF)
/*The Macros CAN_CONTROLLER_XX defines logical ID corresponding to hardware unit */
#define CAN_CONTROLLER_10                             (3U)
#define CAN_CONTROLLER_10_LOGIC_ID                    (3U)
#define CAN_CONTROLLER_10_BASE_ADDRESS                (CAN10)
#define CAN_CONTROLLER_10_TX_INTERRUPT                (STD_OFF)
#define CAN_CONTROLLER_10_RX_INTERRUPT                (STD_OFF)
#define CAN_CONTROLLER_10_BUSOFF_INTERRUPT            (STD_OFF)
#define CAN_CONTROLLER_10_WAKEUP_INTERRUPT            (STD_OFF)
#define CAN_CONTROLLER_10_RXFIFO_INTERRUPT            (STD_OFF)
/*The Macros CAN_CONTROLLER_XX defines logical ID corresponding to hardware unit */
#define CAN_CONTROLLER_11                             (4U)
#define CAN_CONTROLLER_11_LOGIC_ID                    (4U)
#define CAN_CONTROLLER_11_BASE_ADDRESS                (CAN11)
#define CAN_CONTROLLER_11_TX_INTERRUPT                (STD_OFF)
#define CAN_CONTROLLER_11_RX_INTERRUPT                (STD_OFF)
#define CAN_CONTROLLER_11_BUSOFF_INTERRUPT            (STD_OFF)
#define CAN_CONTROLLER_11_WAKEUP_INTERRUPT            (STD_OFF)
#define CAN_CONTROLLER_11_RXFIFO_INTERRUPT            (STD_OFF)
/***************************************************************************************************
*                            Functional Configuration
****************************************************************************************************/
/*Safety Error Tracer*/
#define CAN_SAFETY_ENABLE                            (STD_ON)
/*ECUC_Can_00106*/
#define CAN_VERSION_INFO_API                         (STD_ON)
/*ECUC_Can_00064*/
#define CAN_DEV_ERROR_DETECT                         (STD_ON)
/*SWS_Can_00416*/
#define CAN_EXTENED_ID_SUPPORT                       (STD_ON)
/*SWS_CAN_00495,ECUC_Can_00483*/
#define CAN_PUBLIC_ICOM_SUPPORT                      (STD_OFF)
/*ECUC_Can_00330*/
#define CAN_WAKEUP_SUPPORT                           (STD_ON)
/*ECUC_Can_00466*/
#define CAN_CHECK_WAKEUP_API_SUPPORT                 (STD_ON)
/*ECUC_Can_00482*/
#define CAN_SET_BAUDRATE_API                         (STD_ON)
/*ECUC_Can_00486*/
#define CAN_TRIGGER_TRANSMIT_SUPPORT                 (STD_OFF)
/*ECUC_Can_00431*/
#define CAN_OS_COUNTER_SUPPORTED                     (STD_OFF)
/*ECUC_Can_00095*/
#define CAN_MULTIPLEXED_TRANSMISSION                 (STD_ON)
/*SWS_Can_00443*/
#define CAN_LPDU_CALLOUT_FUNCTION_SUPPORT            (STD_OFF)
/* Configure the callback function before sending data */
#define CAN_LPDU_TX_CALLOUT_FUNCTION_SUPPORT         (STD_OFF)
/*ECUC_Can_00376*/
#define CAN_MAINFUNCTION_MODE_PERIOD                 (1U)
#define CAN_TIMEOUT_LOOP_TIME                        (1000ULL)
/***************************************************************************************************
*                            User Definition Configuration
****************************************************************************************************/
#define CANFD_MODE_SUPPORT                           (STD_ON)
#define CAN_NOACK_ERR_SUPPORTED                      (STD_OFF)
#define CAN_CONTROLLER_RXFIFO_POLLING_SUPPORT        (STD_ON)
#define CAN_CONTROLLER_RXFIFO_INTERRUPT_SUPPORT      (STD_ON)
#define CAN_CONTROLLER_RX_POLLING_SUPPORT            (STD_ON)
#define CAN_CONTROLLER_RX_INTERRUPT_SUPPORT          (STD_ON)
#define CAN_CONTROLLER_TX_POLLING_SUPPORT            (STD_ON)
#define CAN_CONTROLLER_TX_INTERRUPT_SUPPORT          (STD_OFF)
#define CAN_CONTROLLER_BUSOFF_POLLING_SUPPORT        (STD_ON)
#define CAN_CONTROLLER_BUSOFF_INTERRUPT_SUPPORT      (STD_OFF)
#define CAN_CONTROLLER_WAKEUP_POLLING_SUPPORT        (STD_ON)
#define CAN_CONTROLLER_WAKEUP_INTERRUPT_SUPPORT      (STD_OFF)

#define CAN_CONFIG_COUNT                             (1U)
#define CAN_USED_CONTROLLER_MAX_NUM                  (5U)
#define CAN_USED_HOH_MB_MAX_NUM                      (10U)
#define CAN_NUMBER_OF_MAINFUNCTION_RW_PERIOD         (2U)
#define CANFD_MODE_MAX_PAYLOAD_LENGTH                (64U)
#define CAN_STANDARD_MAX_PAYLOAD_LENGTH              (8U)

/* CAN Controller mapped to Core0 */
#define CAN_USED_CONTROLLER_MAX_NUM_TO_CORE0         (5U)
#define CAN_USED_HOH_MB_MAX_NUM_TO_CORE0             (10U)
#define CAN_USED_HOH_ELEMENTS_MAX_NUM_TO_CORE0       (24U)

/*
  Configuration: CanController Name
  Generate the macro definition for CanController name.
*/
#ifndef CanConf_CanController_CanController_0
#define CanConf_CanController_CanController_0         (0U)
#endif  /* CanConf_CanController_CanController_0 */

#ifndef CanConf_CanController_CanController_1
#define CanConf_CanController_CanController_1         (1U)
#endif  /* CanConf_CanController_CanController_1 */

#ifndef CanConf_CanController_CanController_2
#define CanConf_CanController_CanController_2         (2U)
#endif  /* CanConf_CanController_CanController_2 */

#ifndef CanConf_CanController_CanController_3
#define CanConf_CanController_CanController_3         (3U)
#endif  /* CanConf_CanController_CanController_3 */

#ifndef CanConf_CanController_CanController_4
#define CanConf_CanController_CanController_4         (4U)
#endif  /* CanConf_CanController_CanController_4 */


/*
  Configuration: CanHardwareObject Name
  Generate the macro definition for CanHardwareObject name.
*/
#ifndef CanConf_CanHardwareObject_CAN4_Tx_Stand_Test0
#define CanConf_CanHardwareObject_CAN4_Tx_Stand_Test0          ((Can_HwHandleType)0U)
#endif  /* CanConf_CanHardwareObject_CAN4_Tx_Stand_Test0 */

#ifndef CanConf_CanHardwareObject_CAN1_Rx_Standard
#define CanConf_CanHardwareObject_CAN1_Rx_Standard          ((Can_HwHandleType)1U)
#endif  /* CanConf_CanHardwareObject_CAN1_Rx_Standard */

#ifndef CanConf_CanHardwareObject_CAN2_Tx_FD_Extended_Test1
#define CanConf_CanHardwareObject_CAN2_Tx_FD_Extended_Test1          ((Can_HwHandleType)2U)
#endif  /* CanConf_CanHardwareObject_CAN2_Tx_FD_Extended_Test1 */

#ifndef CanConf_CanHardwareObject_CAN1_Rx_Standard_FIFO
#define CanConf_CanHardwareObject_CAN1_Rx_Standard_FIFO          ((Can_HwHandleType)3U)
#endif  /* CanConf_CanHardwareObject_CAN1_Rx_Standard_FIFO */

#ifndef CanConf_CanHardwareObject_CAN1_Rx_Extended
#define CanConf_CanHardwareObject_CAN1_Rx_Extended          ((Can_HwHandleType)4U)
#endif  /* CanConf_CanHardwareObject_CAN1_Rx_Extended */

#ifndef CanConf_CanHardwareObject_CAN3_Rx_FD_Standard
#define CanConf_CanHardwareObject_CAN3_Rx_FD_Standard          ((Can_HwHandleType)5U)
#endif  /* CanConf_CanHardwareObject_CAN3_Rx_FD_Standard */

#ifndef CanConf_CanHardwareObject_CAN3_Rx_FD_Extended
#define CanConf_CanHardwareObject_CAN3_Rx_FD_Extended          ((Can_HwHandleType)6U)
#endif  /* CanConf_CanHardwareObject_CAN3_Rx_FD_Extended */

#ifndef CanConf_CanHardwareObject_CAN0_Tx_Standard_Test0
#define CanConf_CanHardwareObject_CAN0_Tx_Standard_Test0          ((Can_HwHandleType)7U)
#endif  /* CanConf_CanHardwareObject_CAN0_Tx_Standard_Test0 */

#ifndef CanConf_CanHardwareObject_CAN0_Tx_Extended_Test1
#define CanConf_CanHardwareObject_CAN0_Tx_Extended_Test1          ((Can_HwHandleType)8U)
#endif  /* CanConf_CanHardwareObject_CAN0_Tx_Extended_Test1 */

#ifndef CanConf_CanHardwareObject_CAN2_Tx_FD_Standard_Test0
#define CanConf_CanHardwareObject_CAN2_Tx_FD_Standard_Test0          ((Can_HwHandleType)9U)
#endif  /* CanConf_CanHardwareObject_CAN2_Tx_FD_Standard_Test0 */


/***************************************************************************************************
*                               Function Prototypes
***************************************************************************************************/
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
*   Function Name           : Can_MainFunction_Read_<CanMainFunctionRWPeriods.ShortName>
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
/****************************************************************************************************
  MISRA C:2012 Rule 5.1:
  External identifi ers shall be distinct,In C99 the minimum requirement is that the first 31
  characters of external identifiers are significant.
****************************************************************************************************/
#define Can_MainFunction_Read_0()      Can_MainFunction_CommonRead(0U)
/****************************************************************************************************
  MISRA C:2012 Rule 5.1:
  External identifi ers shall be distinct,In C99 the minimum requirement is that the first 31
  characters of external identifiers are significant.
****************************************************************************************************/
#define Can_MainFunction_Read_1()      Can_MainFunction_CommonRead(1U)

/****************************************************************************************************
*   Function Name           : Can_MainFunction_Read_<CanMainFunctionRWPeriods.ShortName>
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
/****************************************************************************************************
  MISRA C:2012 Rule 5.1:
  External identifi ers shall be distinct,In C99 the minimum requirement is that the first 31
  characters of external identifiers are significant.
****************************************************************************************************/
#define Can_MainFunction_Write_0()      Can_MainFunction_CommonWrite(0U)
/****************************************************************************************************
  MISRA C:2012 Rule 5.1:
  External identifi ers shall be distinct,In C99 the minimum requirement is that the first 31
  characters of external identifiers are significant.
****************************************************************************************************/
#define Can_MainFunction_Write_1()      Can_MainFunction_CommonWrite(1U)

#endif /* CAN_CFG_H */
