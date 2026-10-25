/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Eth.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Eth
*
*   brief                 : This file contains sample code only. It is not part of the production
*                           code deliverables.
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

#ifndef SCHM_ETH_H
#define SCHM_ETH_H

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

#include "Std_Types.h"

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/

extern void SchM_Enter_Eth_SetControllerMode(void);

extern void SchM_Exit_Eth_SetControllerMode(void);

extern void SchM_Enter_Eth_GetEgressTimeStamp(void);

extern void SchM_Exit_Eth_GetEgressTimeStamp(void);
extern void SchM_Enter_Eth_GetIngressTimeStamp(void);

extern void SchM_Exit_Eth_GetIngressTimeStamp(void);

extern void SchM_Enter_Eth_ProvideTxBuffer(void);

extern void SchM_Exit_Eth_ProvideTxBuffer(void);


#endif /* SCHM_ETH_H*/
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
