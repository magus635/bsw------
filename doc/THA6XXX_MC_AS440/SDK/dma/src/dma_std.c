/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    dma_std.c
 * Author:      01254
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all internal functions of DMA Driver
 *********************************************************************************************************************/

/*
*#Violation Summary
*
*#dma_std_c_REF_1:MISRAC2012-Dir-4.9;
* Justification: Function like macros are used to reduce code complexity.
*
*#dma_std_c_REF_2:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
*#dma_std_c_REF_3:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*#dma_std_c_REF_4:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "dma_std.h"
#include "dma_register.h"
#include "Platform_Types.h"
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: dma_std_c_REF_3 */
#define DMA_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: dma_std_c_REF_4 */
#include "Dma_MemMap.h"

boolean Dma_Std_SetGlobalRequest(DMA_MODULE *const pDma, uint32 req, uint32 globalReq)
{
    uint32 reqNum;
    uint32 gReqNum;
    boolean ret;
    ret = TRUE;
    /* Get DMA  global request lower bound and global request number */
    /* #Violation: dma_std_c_REF_1 */
    /* #Violation: dma_std_c_REF_2 */
    reqNum = (uint32)GET_DMA_REQ_NUM(pDma);
    /* #Violation: dma_std_c_REF_1 */
    /* #Violation: dma_std_c_REF_2 */
    gReqNum = (uint32)GET_DMA_GREQ_NUM(pDma);
    /* Set REQMUX register */
    if((reqNum <= req) && ((reqNum + gReqNum) > req))
    {
        pDma->REQMUX[req - reqNum].U = globalReq;
        ret = Dma_Register_ReadBack_Check(ret, globalReq, pDma->REQMUX[req - reqNum].U);
    }
    return ret;
}

/* #Violation: dma_std_c_REF_3 */
#define DMA_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: dma_std_c_REF_4 */
#include "Dma_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
