/****************************************************************************************************
 *   FileName              : EthSwt.c
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : Geth
 *
 *   brief                 : This file contain EthSwt callback function
 *
 *   Autosar Version       : 4.4.0
 *
 *   Build Version         : Cortex-R52+/THA6xxx
 *
 *   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
 *
 ****************************************************************************************************/
#include "EthSwt_Eth.h"
Std_ReturnType EthSwt_EthRxFinishedIndication
(
    uint8 CtrlIdx,
    Eth_BufIdxType BufIdx
)
{    
    (void)CtrlIdx;
    (void)BufIdx;
    return E_OK;
}
Std_ReturnType EthSwt_EthTxFinishedIndication
(
    uint8 CtrlIdx,
    Eth_BufIdxType BufIdx
)
{    
    (void)CtrlIdx;
    (void)BufIdx;
    return E_OK;
}
/****************************************************************************************************/
/****************************************************************************************************/
Std_ReturnType EthSwt_EthTxProcessFrame
(
    uint8 CtrlIdx,
    Eth_BufIdxType BufIdx,
    uint8** DataPtr,
    uint16* LengthPtr
)
{
    (void)CtrlIdx;
    (void)BufIdx;
    (void)DataPtr;
    (void)LengthPtr;
    return E_OK;
}

/****************************************************************************************************/
/****************************************************************************************************/
void EthSwt_EthTxAdaptBufferLength
(
    uint16* LengthPtr
)
{
    (void)LengthPtr;
}

/****************************************************************************************************/
/****************************************************************************************************/
Std_ReturnType EthSwt_EthTxPrepareFrame
(
    uint8 CtrlIdx,
    Eth_BufIdxType BufIdx,
    uint8** DataPtr,
    uint16* LengthPtr
)
{
    (void)CtrlIdx;
    (void)BufIdx;
    (void)DataPtr;
    (void)LengthPtr;
    return E_OK;
}

/****************************************************************************************************/
/****************************************************************************************************/
Std_ReturnType EthSwt_EthRxProcessFrame
(
    uint8 CtrlIdx,
    Eth_BufIdxType BufIdx,
    uint8** DataPtr,
    uint16* LengthPtr,
    boolean* IsMgmtFrameOnlyPtr
)
{
    (void)CtrlIdx;
    (void)BufIdx;
    (void)DataPtr;
    (void)LengthPtr;
    (void)IsMgmtFrameOnlyPtr;
    return E_OK;
}


