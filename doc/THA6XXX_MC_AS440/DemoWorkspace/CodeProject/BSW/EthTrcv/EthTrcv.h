/****************************************************************************************************
 *   FileName              : EthTrcv.H
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

#ifndef ETHTRCV_CBK_H
#define ETHTRCV_CBK_H

#include "Std_Types.h"

extern void EthTrcv_ReadMiiIndication(uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx, uint16 RegVal);

extern void EthTrcv_WriteMiiIndication(uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx);

#endif /* end of ETHTRCV_CBK_H */
