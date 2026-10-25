/****************************************************************************************************
*   FileName              : EthIf_Cbk.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Geth
*
*   brief                 : This file contain EthIf callback function
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

#ifndef ETHIF_CBK_H
#define ETHIF_CBK_H

#include "Std_Types.h"
#include "Eth.h"








extern void EthIf_RxIndication
(
    uint8               CtrlIdx,
    Eth_FrameType       FrameType,
    boolean             IsBroadcast,
    const uint8        *PhysAddrPtr,
    const Eth_DataType *DataPtr,
    uint16              LenByte
);
extern void EthIf_TxConfirmation
(
    uint8 CtrlIdx,
    Eth_BufIdxType BufIdx,
    Std_ReturnType Result
);
extern void EthIf_CtrlModeIndication( uint8 CtrlIdx, Eth_ModeType CtrlMode );

#endif /* end of ETHIF_CBK_H */
