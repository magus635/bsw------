/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Dma_Demo.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DMA
*
*   brief                 : This file contains all function declarations of Dma Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

#ifndef DMA_DEMO_H_
#define DMA_DEMO_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"
#include "Dma.h"

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#define DMA_DEMO_MAX_DATA_SIZE                       (32U)

/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/
#define DMA_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Dma_MemMap.h"

extern uint8 Dma_SrcBuf0_8bits[DMA_DEMO_MAX_DATA_SIZE];
extern uint8 Dma_DestBuf0_8bits[DMA_DEMO_MAX_DATA_SIZE];

extern uint16 Dma_SrcBuf0_16bits[DMA_DEMO_MAX_DATA_SIZE];
extern uint16 Dma_DestBuf0_16bits[DMA_DEMO_MAX_DATA_SIZE];

extern uint32 Dma_SrcBuf0_32bits[DMA_DEMO_MAX_DATA_SIZE];
extern uint32 Dma_SrcBuf1_32bits[DMA_DEMO_MAX_DATA_SIZE];
extern uint32 Dma_DestBuf0_32bits[DMA_DEMO_MAX_DATA_SIZE];

#define DMA_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Dma_MemMap.h"

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
#define DMA_START_SEC_CODE_ASIL_D_GLOBAL
#include "Dma_MemMap.h"

extern void Dma_Demo(void);
extern void Dma_DemoEntry(void);

#define DMA_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Dma_MemMap.h"

#endif /* _ADC_DEMO_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
