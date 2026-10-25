/****************************************************************************************************
 *   FileName              : EthTrcv.c
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : Geth
 *
 *   brief                 : This file contain EthTrcv callback function
 *
 *   Autosar Version       : 4.4.0
 *
 *   Build Version         : Cortex-R52+/THA6xxx
 *
 *   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
 *
 ****************************************************************************************************/
#include "EthTrcv.h"
/*autosar bug: uint8 RegVal should be uint16 RegVal*/
void EthTrcv_ReadMiiIndication(uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx, uint16 RegVal)
{
    (void)CtrlIdx;
    (void)TrcvIdx;
    (void)RegIdx;
    (void)RegVal;
}
void EthTrcv_WriteMiiIndication(uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx)
{
    (void)CtrlIdx;
    (void)TrcvIdx;
    (void)RegIdx;
}



