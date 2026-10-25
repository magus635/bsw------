/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Dma.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Dma
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

#ifndef SCHM_DMA_H_
#define SCHM_DMA_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

#include "Std_Types.h"

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/

extern void SchM_Enter_Dma_GetChannelStatus(void);
extern void SchM_Exit_Dma_GetChannelStatus(void);
extern void SchM_Enter_Dma_ChannelStart(void);
extern void SchM_Exit_Dma_ChannelStart(void);
extern void SchM_Enter_Dma_ChannelCancel(void);
extern void SchM_Exit_Dma_ChannelCancel(void);
extern void SchM_Enter_Dma_ChannelSuspend(void);
extern void SchM_Exit_Dma_ChannelSuspend(void);
extern void SchM_Enter_Dma_ChannelResume(void);
extern void SchM_Exit_Dma_ChannelResume(void);
extern void SchM_Enter_Dma_ChannelUpdate(void);
extern void SchM_Exit_Dma_ChannelUpdate(void);
extern void SchM_Enter_Dma_ChannelShadowingUpdate(void);
extern void SchM_Exit_Dma_ChannelShadowingUpdate(void);
extern void SchM_Enter_Dma_DeInit(void);
extern void SchM_Exit_Dma_DeInit(void);

#endif /* SCHM_DMA_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
