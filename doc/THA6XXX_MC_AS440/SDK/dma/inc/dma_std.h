/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    dma_std.h
 * Author:      01254
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of internal functions.
 *********************************************************************************************************************/
#ifndef DMA_STD_H_
#define DMA_STD_H_

/*
*#Violation Summary
*#dma_std_h_REF_1:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*#dma_std_h_REF_2:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "dma_register.h"
#include "Platform_Types.h"
#include "tha6_cfg.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* Enum for double buffer mode  */
typedef enum
{
    DMA_DOUBLEBUFFERACTIVESTATUS_BUFFER0 = 0U, /* Buffer0 is active, the buffer is currently in use */
    DMA_DOUBLEBUFFERACTIVESTATUS_BUFFER1       /* Buffer1 is active, the buffer is currently in use */
} Dma_DoubleBufferActiveStatus;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/* #Violation: dma_std_h_REF_1 */
#define DMA_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: dma_std_h_REF_2 */
#include "Dma_MemMap.h"

/**********************************************************************************************************************
 * Function:     Dma_Register_ReadBack_Check
 * Description:  Register read back check
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        state: Original state
 *               expect: The value expected to be written
 *               value: The value actually written
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If the check is correct, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/03/10    01369     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Dma_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value);
/**********************************************************************************************************************
 * Function:     Dma_Std_EnableDma
 * Description:  Enable one specific DMA module
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDma: Pointer to DMA module
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If dma is enabled, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Dma_Std_EnableDma(DMA_MODULE *const pDma);
/**********************************************************************************************************************
 * Function:     Dma_Std_DisableDma
 * Description:  Disable one specific DMA module
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDma: Pointer to DMA module
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If dma is disabled, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Dma_Std_DisableDma(DMA_MODULE *const pDma);
/**********************************************************************************************************************
 * Function:     Dma_Std_SuspendChannel
 * Description:  Enable or disable suspend a channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               enable: Enable or disable halt a channel
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If the readback state is the same as the input state, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *  2024/07/17    01254     To be compatible with THA6412, add set the halt register
 *  2024/12/30    01369     Distinguish between THA6_THA6412 and THA6_THA6206
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Dma_Std_SuspendChannel(DMA_MODULE *const pDma, uint8 channelID, boolean enable);
/**********************************************************************************************************************
 * Function:     Dma_Std_GetActiveStatus
 * Description:  Get channel active status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If channel active, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Dma_Std_GetActiveStatus(const DMA_MODULE *const pDma, uint8 channelID);
/**********************************************************************************************************************
 * Function:     Dma_Std_SetTerminalCountInterruptMask
 * Description:  Mask terminal count interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               enable: Enable or disable mask
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If the readback state is the same as the input state, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Dma_Std_SetTerminalCountInterruptMask(DMA_MODULE *const pDma, uint8 channelID, boolean enable);
/**********************************************************************************************************************
 * Function:     Dma_Std_SetSourceCircularBufferInterruptMask
 * Description:  Mask source circular buffer interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               enable: Enable or disable mask
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If the readback state is the same as the input state, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Dma_Std_SetSourceCircularBufferInterruptMask(DMA_MODULE *const pDma, uint8 channelID,
                                                                    boolean enable);
/**********************************************************************************************************************
 * Function:     Dma_Std_SetDestinationCircularBufferInterruptMask
 * Description:  Mask destination circular buffer interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               enable: Enable or disable mask
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If the readback state is the same as the input state, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Dma_Std_SetDestinationCircularBufferInterruptMask(DMA_MODULE *const pDma, uint8 channelID,
                                                                         boolean enable);
/**********************************************************************************************************************
 * Function:     Dma_Std_SetMatchPatternInterruptMask
 * Description:  Mask match pattern interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               enable: Enable or disable mask
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If the readback state is the same as the input state, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Dma_Std_SetMatchPatternInterruptMask(DMA_MODULE *const pDma, uint8 channelID, boolean enable);
/**********************************************************************************************************************
 * Function:     Dma_Std_SetTransferSizeThresholdInterruptMask
 * Description:  Mask transfer size threshold interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               enable: Enable or disable mask
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If the readback state is the same as the input state, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Dma_Std_SetTransferSizeThresholdInterruptMask(DMA_MODULE *const pDma, uint8 channelID,
                                                                     boolean enable);
/**********************************************************************************************************************
 * Function:     Dma_Std_SetErrorInterruptMask
 * Description:  Mask error interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               enable: Enable or disable mask
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If the readback state is the same as the input state, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Dma_Std_SetErrorInterruptMask(DMA_MODULE *const pDma, uint8 channelID, boolean enable);
/**********************************************************************************************************************
 * Function:     Dma_Std_SetSourceCircularBufferInterrupt
 * Description:  Set source circular buffer interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               enable: Enable or disable interrupt
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If the readback state is the same as the input state, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Dma_Std_SetSourceCircularBufferInterrupt(DMA_MODULE *const pDma, uint8 channelID,
                                                                boolean enable);
/**********************************************************************************************************************
 * Function:     Dma_Std_SetDestinationCircularBufferBufferInterrupt
 * Description:  Set destination circular buffer interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               enable: Enable or disable interrupt
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If the readback state is the same as the input state, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Dma_Std_SetDestinationCircularBufferBufferInterrupt(DMA_MODULE *const pDma, uint8 channelID,
                                                                           boolean enable);
/**********************************************************************************************************************
 * Function:     Dma_Std_SetMatchPatternInterrupt
 * Description:  Set match pattern interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               enable: Enable or disable interrupt
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If the readback state is the same as the input state, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Dma_Std_SetMatchPatternInterrupt(DMA_MODULE *const pDma, uint8 channelID, boolean enable);
/**********************************************************************************************************************
 * Function:     Dma_Std_SetTransferSizeThresholdInterrupt
 * Description:  Set transfer size threshold interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               enable: Enable or disable interrupt
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If the readback state is the same as the input state, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Dma_Std_SetTransferSizeThresholdInterrupt(DMA_MODULE *const pDma, uint8 channelID,
                                                                 boolean enable);
/**********************************************************************************************************************
 * Function:     Dma_Std_EnableChannel
 * Description:  Enable channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If the dma channel is enabled, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Dma_Std_EnableChannel(DMA_MODULE *const pDma, uint8 channelID);
/**********************************************************************************************************************
 * Function:     Dma_Std_DisableChannel
 * Description:  Disable channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Dma_Std_DisableChannel(DMA_MODULE *const pDma, uint8 channelID);
/**********************************************************************************************************************
 * Function:     Dma_Std_SwitchDoubleBuffer
 * Description:  Software switch double buffer
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Dma_Std_SwitchDoubleBuffer(DMA_MODULE *const pDma, uint8 channelID);
/**********************************************************************************************************************
 * Function:     Dma_Std_GetDoubleBufferActiveStatus
 * Description:  Get channel double buffer active status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 * Inout:        None
 * Output:       None
 * Return:       Dma_DoubleBufferActiveStatus: status: which buffer is active
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE Dma_DoubleBufferActiveStatus Dma_Std_GetDoubleBufferActiveStatus(const DMA_MODULE *const pDma,
                                                                                   uint8 channelID);
/**********************************************************************************************************************
 * Function:     Dma_Std_GetBuffer0FrozenStatus
 * Description:  Get channel buffer0 frozen status in double buffer function
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: buffer0 frozen, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Dma_Std_GetBuffer0FrozenStatus(const DMA_MODULE *const pDma, uint8 channelID);
/**********************************************************************************************************************
 * Function:     Dma_Std_GetBuffer1FrozenStatus
 * Description:  Get channel buffer1 frozen status in double buffer function
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: buffer1 frozen, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Dma_Std_GetBuffer1FrozenStatus(const DMA_MODULE *const pDma, uint8 channelID);
/**********************************************************************************************************************
 * Function:     Dma_Std_ClearBuffer0FrozenStatus
 * Description:  Clear channel buffer0 frozen status in double buffer function
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Dma_Std_ClearBuffer0FrozenStatus(DMA_MODULE *const pDma, uint8 channelID);
/**********************************************************************************************************************
 * Function:     Dma_Std_ClearBuffer1FrozenStatus
 * Description:  Clear channel buffer1 frozen status in double buffer function
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Dma_Std_ClearBuffer1FrozenStatus(DMA_MODULE *const pDma, uint8 channelID);

/**********************************************************************************************************************
 * Function:     Dma_Std_ClearAllStatus
 * Description:  Clear channel all status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Dma_Std_ClearAllStatus(DMA_MODULE *const pDma, uint8 channelID);
/**********************************************************************************************************************
 * Function:     Dma_Std_SetGlobalRequest
 * Description:  Set global request
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDma: Pointer to DMA module
 *               req: Peripheral request selection. If the chip is THA6206, this number is less than or equal to 255
 *               globalReq: Global request mapping. If the chip is THA6206, this number is less than or equal to 255
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: global request is set, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern boolean Dma_Std_SetGlobalRequest(DMA_MODULE *const pDma, uint32 req, uint32 globalReq);
/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
#define DMA_REG_CHECK
#if defined(DMA_REG_CHECK)
LOCAL_FORCEINLINE boolean Dma_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    boolean ret;

    ret = state;
    if (expect != value)
    {
        ret &= FALSE;
    }

    return ret;
}
#else
LOCAL_FORCEINLINE boolean Dma_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    (void)state;
    (void)expect;
    (void)value;

    return state;
}
#endif

LOCAL_FORCEINLINE boolean Dma_Std_EnableDma(DMA_MODULE *const pDma)
{
    boolean ret;
    ret = TRUE;
    pDma->CONFIG.B.E = 1U;
    ret = Dma_Register_ReadBack_Check(ret, 1U, pDma->CONFIG.B.E);
    return ret;
}

LOCAL_FORCEINLINE boolean Dma_Std_DisableDma(DMA_MODULE *const pDma)
{
    boolean ret;
    ret = TRUE;
    pDma->CONFIG.B.E = 0U;
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CONFIG.B.E);
    return ret;
}

LOCAL_FORCEINLINE boolean Dma_Std_SuspendChannel(DMA_MODULE *const pDma, uint8 channelID, boolean enable)
{
    boolean ret;
#if defined(THA6_THA6412) || defined(THA6_THA6104)
    ret = TRUE;
    pDma->CH[channelID].HALT.B.HALT = enable;
    ret = Dma_Register_ReadBack_Check(ret, enable, pDma->CH[channelID].HALT.B.HALT);
#endif/* THA6_THA6412 */
#if defined(THA6_THA6206) || defined(THA6_THA6206D)
    (void)pDma;
    (void)channelID;
    (void)enable;
    /*THA6206 does not support the Halt function*/
    ret = FALSE;
#endif /* THA6_THA6206\THA6_THA6206D */
    return ret;
}

LOCAL_FORCEINLINE boolean Dma_Std_GetActiveStatus(const DMA_MODULE *const pDma, uint8 channelID)
{
    return ((0U != pDma->CH[channelID].CONFIG.B.A) ? TRUE: FALSE);
}

LOCAL_FORCEINLINE boolean Dma_Std_SetTerminalCountInterruptMask(DMA_MODULE *const pDma, uint8 channelID, boolean enable)
{
    boolean ret;
    ret = TRUE;
    pDma->CH[channelID].CONFIG.B.ITC = enable;
    ret = Dma_Register_ReadBack_Check(ret, enable, pDma->CH[channelID].CONFIG.B.ITC);
    return ret;
}

LOCAL_FORCEINLINE boolean Dma_Std_SetSourceCircularBufferInterruptMask(DMA_MODULE *const pDma, uint8 channelID,
                                                                    boolean enable)
{
    boolean ret;
    ret = TRUE;
    pDma->CH[channelID].ADVCONFIG.B.INTSCBMSK = enable;
    ret = Dma_Register_ReadBack_Check(ret, enable, pDma->CH[channelID].ADVCONFIG.B.INTSCBMSK);
    return ret;
}

LOCAL_FORCEINLINE boolean Dma_Std_SetDestinationCircularBufferInterruptMask(DMA_MODULE *const pDma, uint8 channelID,
                                                                         boolean enable)
{
    boolean ret;
    ret = TRUE;
    pDma->CH[channelID].ADVCONFIG.B.INTDCBMSK = enable;
    ret = Dma_Register_ReadBack_Check(ret, enable, pDma->CH[channelID].ADVCONFIG.B.INTDCBMSK);
    return ret;
}

LOCAL_FORCEINLINE boolean Dma_Std_SetTransferSizeThresholdInterruptMask(DMA_MODULE *const pDma, uint8 channelID,
                                                                     boolean enable)
{
    boolean ret;
    ret = TRUE;
    pDma->CH[channelID].THR.B.INTTHRMSK = enable;
    ret = Dma_Register_ReadBack_Check(ret, enable, pDma->CH[channelID].THR.B.INTTHRMSK);
    return ret;
}

LOCAL_FORCEINLINE boolean Dma_Std_SetMatchPatternInterruptMask(DMA_MODULE *const pDma, uint8 channelID, boolean enable)
{
    boolean ret;
    ret = TRUE;
    pDma->CH[channelID].PATCONFIG.B.INTPATMSK = enable;
    ret = Dma_Register_ReadBack_Check(ret, enable, pDma->CH[channelID].PATCONFIG.B.INTPATMSK);
    return ret;
}

LOCAL_FORCEINLINE boolean Dma_Std_SetErrorInterruptMask(DMA_MODULE *const pDma, uint8 channelID, boolean enable)
{
    boolean ret;
    ret = TRUE;
    pDma->CH[channelID].CONFIG.B.IE = enable;
    ret = Dma_Register_ReadBack_Check(ret, enable, pDma->CH[channelID].CONFIG.B.IE);
    return ret;
}

LOCAL_FORCEINLINE boolean Dma_Std_SetSourceCircularBufferInterrupt(DMA_MODULE *const pDma, uint8 channelID, boolean enable)
{
    boolean ret;
    ret = TRUE;
    pDma->CH[channelID].ADVCONFIG.B.INTSCB = enable;
    ret = Dma_Register_ReadBack_Check(ret, enable, pDma->CH[channelID].ADVCONFIG.B.INTSCB);
    return ret;
}

LOCAL_FORCEINLINE boolean Dma_Std_SetDestinationCircularBufferBufferInterrupt(DMA_MODULE *const pDma, uint8 channelID,
                                                                           boolean enable)
{
    boolean ret;
    ret = TRUE;
    pDma->CH[channelID].ADVCONFIG.B.INTDCB = enable;
    ret = Dma_Register_ReadBack_Check(ret, enable, pDma->CH[channelID].ADVCONFIG.B.INTDCB);
    return ret;
}

LOCAL_FORCEINLINE boolean Dma_Std_SetMatchPatternInterrupt(DMA_MODULE *const pDma, uint8 channelID, boolean enable)
{
    boolean ret;
    ret = TRUE;
    pDma->CH[channelID].PATCONFIG.B.INTPATEN = enable;
    ret = Dma_Register_ReadBack_Check(ret, enable, pDma->CH[channelID].PATCONFIG.B.INTPATEN);
    return ret;
}

LOCAL_FORCEINLINE boolean Dma_Std_SetTransferSizeThresholdInterrupt(DMA_MODULE *const pDma, uint8 channelID,
                                                                 boolean enable)
{
    boolean ret;
    ret = TRUE;
    pDma->CH[channelID].THR.B.INTTHREN = enable;
    ret = Dma_Register_ReadBack_Check(ret, enable, pDma->CH[channelID].THR.B.INTTHREN);
    return ret;
}

LOCAL_FORCEINLINE boolean Dma_Std_EnableChannel(DMA_MODULE *const pDma, uint8 channelID)
{
    boolean ret;
    ret = TRUE;
    pDma->CH[channelID].CONFIG.B.E = 1U;
    ret = Dma_Register_ReadBack_Check(ret, 1U, pDma->CH[channelID].CONFIG.B.E);
    return ret;
}

LOCAL_FORCEINLINE void Dma_Std_DisableChannel(DMA_MODULE *const pDma, uint8 channelID)
{
    pDma->CH[channelID].CONFIG.B.E = 0U;
}

LOCAL_FORCEINLINE void Dma_Std_SwitchDoubleBuffer(DMA_MODULE *const pDma, uint8 channelID)
{
    pDma->CH[channelID].DBCONTROL.B.SW = 1U;
}

LOCAL_FORCEINLINE Dma_DoubleBufferActiveStatus Dma_Std_GetDoubleBufferActiveStatus(const DMA_MODULE *const pDma,
                                                                                   uint8 channelID)
{
    return ((0U != pDma->CH[channelID].DBSTS.B.ACTBUF) ? DMA_DOUBLEBUFFERACTIVESTATUS_BUFFER1: DMA_DOUBLEBUFFERACTIVESTATUS_BUFFER0);
}

LOCAL_FORCEINLINE boolean Dma_Std_GetBuffer0FrozenStatus(const DMA_MODULE *const pDma, uint8 channelID)
{
    return ((0U != pDma->CH[channelID].DBSTS.B.FROZEN0) ? TRUE: FALSE);
}

LOCAL_FORCEINLINE boolean Dma_Std_GetBuffer1FrozenStatus(const DMA_MODULE *const pDma, uint8 channelID)
{
    return ((0U != (boolean)pDma->CH[channelID].DBSTS.B.FROZEN1) ? TRUE: FALSE);
}

LOCAL_FORCEINLINE void Dma_Std_ClearBuffer0FrozenStatus(DMA_MODULE *const pDma, uint8 channelID)
{
    pDma->CH[channelID].DBSTS.U = 1U;
}

LOCAL_FORCEINLINE void Dma_Std_ClearBuffer1FrozenStatus(DMA_MODULE *const pDma, uint8 channelID)
{
    pDma->CH[channelID].DBSTS.U = 2U;
}

LOCAL_FORCEINLINE void Dma_Std_ClearAllStatus(DMA_MODULE *const pDma, uint8 channelID)
{
    /* Clear channel all status */
    pDma->CH[channelID].INTCLR.U = 0x3FU;
    pDma->CH[channelID].DBSTS.U = 0x3U;
    /* SE protect register */
    pDma->CH[channelID].ERRCLR.U = 0xFU;
    /* SE protect register */
    pDma->CH[channelID].TSTMPCLR.U = 0x3U;
}

/* #Violation: dma_std_h_REF_1 */
#define DMA_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: dma_std_h_REF_2 */
#include "Dma_MemMap.h"
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
#endif /* DMA_STD_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
