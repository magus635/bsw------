
/****************************************************************************************************
 *
 ****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Eth.h
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : Ethernet
 *
 *   brief                 : This file contains all function declarations of Ethernet Driver
 *                          [SWS_Eth_00011]None of the Ethernet Driver module header files shall
 *                          define global variables
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
 *#Eth_h_REF_1:MISRAC2012-Rule-2.5;
 * Justification: The macros are reserved for upper layers.
 *
 *#Eth_h_REF_2:MISRAC2012-Rule-20.7;
 * Justification: Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
 *
 *#Eth_c_REF_3:MISRAC2012-Rule-20.1;
 * Justification: AUTOSAR imposes the specification of the sections in which certain parts of the
 *driver must be placed.
 *
 */
#ifndef ETH_H
#define ETH_H

/***************************************************************************************************
 *                               Include
 ***************************************************************************************************/
 /* #Violation: Eth_h_REF_1*/

/* \[SWS_Eth_00148]*/
#include "Eth_Types.h"
/* \[SWS_Eth_00006] The header file Eth.h shall include a software and specification version number*/
#include "Eth_Version.h"
#include "Eth_PBcfg.h"

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

/* \[SWS_Eth_00016] Development Errors */
#define ETH_E_INV_CTRL_IDX              (1U) /* invalid Ctrl Index*/
/* Driver is not be initialized 440  replace ETH_E_NOT_INITIALIZED with ETH_E_UNINIT*/
#define ETH_E_UNINIT                    (2U)
#define ETH_E_PARAM_POINTER             (3U) /* Invalid pointer in parameter list */
#define ETH_E_INV_PARAM                 (4U) /* Invalid parameter*/
#define ETH_E_INV_MODE                  (5U) /* Invalid mode*/
/* Extend Error */
#define ETH_E_CORE_MISMATCH             (0xE0U) /* 224 Execution core and allocated core do not match*/
#define ETH_E_REG_CHECK_FAIL            (0xF0U) /* Register check fail */


/* ETH Instance ID */
#define ETH_INSTANCE_ID                 (ETH_INDEX)

/* Service IDs */
#define ETH_SID_INIT                    (0x01U) /* 1 */
#define ETH_SID_SETCONTROLLERMODE       (0x03U) /* 3 */
#define ETH_SID_GETCONTROLLERMODE       (0x04U) /* 4 */
#define ETH_SID_WRITEMII                (0x05U) /* 5 */
#define ETH_SID_READMII                 (0x06U) /* 6 */
#define ETH_SID_GETPHYADDRESS           (0x08U) /* 8 */
#define ETH_SID_PROVIDETXBUFFER         (0x09U) /* 9 */
#define ETH_SID_TRANSMIT                (0x0AU) /* 10 */
#define ETH_SID_RECEIVE                 (0x0BU) /* 11 */
#define ETH_SID_TXCONFIRMATION          (0x0CU) /* 12 */
#define ETH_SID_GETVERSIONINFO          (0x0DU) /* 13 */
#define ETH_SID_SETPHYSADDRESS          (0x13U) /* 19 */
#define ETH_SID_UPDATEPHYSADDRFILTER    (0x12U) /* 18 */
#define ETH_SID_GETDROPCOUNT            (0x14U) /* 20 */
#define ETH_SID_GETETHERSTATS           (0x15U) /* 21 */
#define ETH_SID_GETCURRENTTIME          (0x16U) /* 22 */
#define ETH_SID_ENABLEEGRESS            (0x17U) /* 23 */
#define ETH_SID_GETEGRESSTIME           (0x18U) /* 24 */
#define ETH_SID_GETINGRESSTIME          (0x19U) /* 25 */
/* #Violation: Eth_h_REF_1*/
#define ETH_SID_GETTXSTATS              (0x1CU) /* 28 */
/* #Violation: Eth_h_REF_1*/
#define ETH_SID_GETTXERRORCOUNTERVALUES (0x1DU) /* 29 */

/* Extend SID */
/* #Violation: Eth_h_REF_1*/
#define ETH_SID_TX_ISR                  (0x40U) /* 64 */
/* #Violation: Eth_h_REF_1*/
#define ETH_SID_RX_ISR                  (0x41U) /* 65 */


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
/* #Violation: Eth_h_REF_1*/
#define ETH_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Eth_h_REF_3*/
#include "Eth_MemMap.h"

extern FUNC(void, ETH_PUBLIC_CODE)
    Eth_Init(P2CONST(Eth_ConfigType, AUTOMATIC, ETH_APPL_CONST) CfgPtr);

extern FUNC(Std_ReturnType, ETH_PUBLIC_CODE)
    Eth_SetControllerMode(uint8 CtrlIdx, Eth_ModeType CtrlMode);

extern FUNC(Std_ReturnType, ETH_PUBLIC_CODE)
/* #Violation: Eth_h_REF_2*/
    Eth_GetControllerMode(uint8 CtrlIdx, P2VAR(Eth_ModeType, AUTOMATIC, ETH_APPL_DATA) CtrlModePtr);

extern FUNC(void, ETH_PUBLIC_CODE)
/* #Violation: Eth_h_REF_2*/
    Eth_GetPhysAddr(uint8 CtrlIdx, P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr);

extern FUNC(void, ETH_PUBLIC_CODE)
    Eth_SetPhysAddr(uint8 CtrlIdx, P2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) PhysAddrPtr);


extern FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_UpdatePhysAddrFilter(
    uint8 CtrlIdx,
    P2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) PhysAddrPtr,
    Eth_FilterActionType Action);

#if (ETH_ENA_MII_API == STD_ON)

extern FUNC(Std_ReturnType, ETH_PUBLIC_CODE)
    Eth_WriteMii(uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx, uint16 RegVal);

extern FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_ReadMii(
/* #Violation: Eth_h_REF_2*/
    uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx, P2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) RegValPtr);
#endif /* (ETH_ENA_MII_API  \== STD_ON) */

extern FUNC(BufReq_ReturnType, ETH_PUBLIC_CODE) Eth_ProvideTxBuffer(
    uint8 CtrlIdx,
    uint8 Priority,
/* #Violation: Eth_h_REF_2*/
    P2VAR(Eth_BufIdxType, AUTOMATIC, ETH_APPL_CONST) BufIdxPtr,
/* #Violation: Eth_h_REF_2*/
    P2P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) BufPtr,
/* #Violation: Eth_h_REF_2*/
    P2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LenBytePtr);

extern FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_Transmit(
    uint8          CtrlIdx,
    Eth_BufIdxType BufIdx,
    Eth_FrameType  FrameType,
    boolean        TxConfirmation,
    uint16         LenByte,
    P2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) PhysAddrPtr);

extern FUNC(void, ETH_PUBLIC_CODE) Eth_Receive
(
    uint8 CtrlIdx, 
    uint8 FifoIdx,
/* #Violation: Eth_h_REF_2*/
    P2VAR(Eth_RxStatusType, AUTOMATIC, ETH_APPL_DATA) RxStatusPtr
);

extern FUNC(void, ETH_PUBLIC_CODE) Eth_TxConfirmation(uint8 CtrlIdx);

#if (ETH_VERSION_INFO_API == STD_ON)
extern FUNC(void, ETH_PUBLIC_CODE)
/* #Violation: Eth_h_REF_2*/
    Eth_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, ETH_APPL_DATA) VersionInfoPtr);
#endif

extern FUNC(void, ETH_PUBLIC_CODE) Eth_MainFunction(void);

#if (ETH_GET_DROP_COUNT_API == STD_ON)
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_GetCounterValues
(
    uint8 CtrlIdx, 
    Eth_CounterType* CounterPtr
);
#endif /* (ETH_GET_DROP_COUNT_API  \== STD_ON) */

#if (ETH_GET_ETHER_STATS_API == STD_ON)
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_GetRxStats
(
    uint8 CtrlIdx, 
    Eth_RxStatsType* RxStats
);

#endif /* (ETH_GET_ETHER_STATS_API  \== STD_ON) */
#if (ETH_GETTXSTATS_API == STD_ON)
extern Std_ReturnType Eth_GetTxStats
(
    uint8 CtrlIdx,
    Eth_TxStatsType* TxStats
);
#endif  /* ETH_GETTXSTATS_API == STD_ON */
#if (ETH_GETTXERRCNTRVAL_API == STD_ON)
extern Std_ReturnType Eth_GetTxErrorCounterValues
(
    uint8 CtrlIdx,
    Eth_TxErrorCounterValuesType* TxErrorCounterValues
);
#endif  /* ETH_GETTXERRCNTRVAL_API == STD_ON */

#if (ETH_GLOBAL_TIME_SUPPORT_API == STD_ON)
extern FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_GetCurrentTime(
    uint8 CtrlIdx,
/* #Violation: Eth_h_REF_2*/
    P2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) timeQualPtr,
/* #Violation: Eth_h_REF_2*/
    P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) timeStampPtr);

extern FUNC(void, ETH_PUBLIC_CODE) Eth_EnableEgressTimeStamp(uint8 CtrlIdx, Eth_BufIdxType BufIdx);

extern Std_ReturnType Eth_GetEgressTimeStamp
(
    uint8 CtrlIdx,
    Eth_BufIdxType BufIdx,
    Eth_TimeStampQualType* timeQualPtr,
    Eth_TimeStampType* timeStampPtr
);

extern Std_ReturnType Eth_GetIngressTimeStamp
(
    uint8 CtrlIdx,
    const Eth_DataType* DataPtr,
    Eth_TimeStampQualType* timeQualPtr,
    Eth_TimeStampType* timeStampPtr
);

#endif /* (ETH_GLOBAL_TIME_SUPPORT_API  \== STD_ON) */

/* #Violation: Eth_h_REF_1*/
#define ETH_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Eth_h_REF_3*/
#include "Eth_MemMap.h"

#endif /* ETH_H */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
