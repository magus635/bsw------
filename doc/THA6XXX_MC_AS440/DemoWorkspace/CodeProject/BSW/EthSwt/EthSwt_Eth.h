/****************************************************************************************************
 *
 ****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : EthSwt_Eth.h
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : Ethernet
 *
 *   brief                 : This file contains the functions used by the Ethernet switch used 
 *                           (for unit testing only)
 *
 *   Autosar Version       : xxxx
 *
 *   Build Version         : Cortex-R52+/THA6xxx
 *
 *   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
 *
 ****************************************************************************************************/




#ifndef EthSwt_Eth_H
#define EthSwt_Eth_H
#include "Std_Types.h"
#include "Eth_GeneralTypes.h"
extern Std_ReturnType EthSwt_EthTxFinishedIndication
(
    uint8 CtrlIdx,
    Eth_BufIdxType BufIdx
); 
extern Std_ReturnType EthSwt_EthRxFinishedIndication
(
    uint8 CtrlIdx,
    Eth_BufIdxType BufIdx
); 
extern Std_ReturnType EthSwt_EthTxProcessFrame
(
    uint8 CtrlIdx,
    Eth_BufIdxType BufIdx,
    uint8** DataPtr,
    uint16* LengthPtr
); 
extern void EthSwt_EthTxAdaptBufferLength
(
    uint16* LengthPtr
); 
extern Std_ReturnType EthSwt_EthTxPrepareFrame
(
    uint8 CtrlIdx,
    Eth_BufIdxType BufIdx,
    uint8** DataPtr,
    uint16* LengthPtr
); 
extern Std_ReturnType EthSwt_EthRxProcessFrame
(
    uint8 CtrlIdx,
    Eth_BufIdxType BufIdx,
    uint8** DataPtr,
    uint16* LengthPtr,
    boolean* IsMgmtFrameOnlyPtr
); 
#endif


