/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    I2c_Hal.h
 * Author:      01107
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of interfaces.
 *********************************************************************************************************************/
#ifndef I2C_STD_H_
#define I2C_STD_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "i2c_register.h"
#include "compilertypes.h"
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* Enumeration for the I2C function status in STD layer code */
typedef enum
{
    I2C_STD_STATUS_OK = 0U,     /* Status available*/
    I2C_STD_STATUS_ERROR,       /* Status errors */
    I2C_STD_STATUS_BUSY,        /* Status busy */
    I2C_STD_STATUS_TIMEOUT,     /* operation timeout */
    I2C_STD_STATUS_PARAM_ERROR, /* Illegal parameter */
} I2c_Std_Status;

/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* ^I2C_STD_SPEED_MODE^ I2C speed mode */
#define I2C_STD_SPEED_MODE_STANDARD ((uint32)100000U)   /* I2C standard speed 100Kbps */
#define I2C_STD_SPEED_MODE_FAST ((uint32)400000U)       /* I2C fast speed 400Kbps */
#define I2C_STD_SPEED_MODE_FAST_PLUS ((uint32)1000000U) /* I2C fast+ speed 1Mbps */
#define I2C_STD_SPEED_MODE_HIGH ((uint32)3400000U)      /* I2C high speed 3.4Mbps */

/* ^I2C_STD_STATUS_MASK^ I2C Status Mask: SR1\SR2\SR3\SR4 */
#define I2C_STD_SR1_MASK (0x00001FFFU) /* I2C SR1 mask value */
#define I2C_STD_SR2_MASK (0x0000FF97U) /* I2C SR2 mask value */
#define I2C_STD_SR3_MASK (0x00007800U) /* I2C SR3 mask value */
#define I2C_STD_SR4_MASK (0x00000009U) /* I2C SR4 mask value */

/* ^I2C_STD_STATUS_CLEARMASK^ I2C Status Clear Mask: SR1\SR3\SR4 */
#define I2C_STD_SR1_CLEARMASK (0x00001F20U)  /* I2C SR1 mask value */
#define I2C_STD_SR4_CLEARMASK (0x90000000U)  /* I2C SR4 mask value */

/* ^I2C_STD_DUTYCYCLE^ I2C duty cycle in fast mode */
#define I2C_STD_DUTYCYCLE_2 (0x00000000U)    /* I2C fast mode Tlow/Thigh = 2 */
#define I2C_STD_DUTYCYCLE_16_9 (0x00000001U) /* I2C fast mode Tlow/Thigh = 16/9 */

/* ^I2C_STD_FIFO_TX_LENGTH_MASK^ The mask value of total transmit bytes length  */
#define I2C_STD_FIFO_TX_LENGTH_MASK (0x00003FFFU) /* The mask value of total transmit bytes length */

/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* Structure for I2C Configuration definition */
typedef struct
{
    uint32 busSpeed;        /* Specifies the bus frequency between 10 ~ 34000000 */
    uint32 dutyCycle;       /* Specifies the I2C fast mode duty cycle, can be a value of I2C_DUTYCYCLE */
    boolean enFifo;         /* Specifies the FIFO function switch.TRUE is enable, FALSE is disable. */
    uint32 fifoRxWaterMark; /* Specifies the RX-FIFO water mark, can be a value of I2C_FIFO_RX_WATERMARK */
    uint32 fifoTxWaterMark; /* Specifies the TX-FIFO water mark, can be a value of I2C_FIFO_TX_WATERMARK */
    uint32 fifoAlignMode;   /* Specifies the FIFO align mode, can be a value of I2C_FIFO_ALIGN */
    uint32 burstSize;       /* Specifies the burst size, can be a value of I2C_FIFO_BURST_SIZE */
    uint32 flowController;  /* Specifies the I2C/DMA flow controller, can be a value of I2C_STD_FLOW_CONTROLLER */
    uint32 coreFrequency;   /* Specifies the I2C module frequency */
} I2C_Std_InitParameter;

/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
#define I2C_START_SEC_CODE_ASIL_D_GLOBAL
#include "I2c_MemMap.h"

/**********************************************************************************************************************
 * Function:    I2c_Std_GenerateStart
 * Description: Generates I2Cx communication START condition.
 * Sync/Async:  Synchronous
 * Reentrancy:  Non-Reentrant
 * Input:       pI2c: Pointer to the I2C module.
 *              generateStart: TRUE is generate a I2C START signal. FALSE is clear START flag.
 * Inout:       None
 * Output:      None
 * Return:      None
 * Others:      None
 * History:
 * Date          Author    Modified
 * 2024/03/21    01107     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void I2c_Std_GenerateStart(I2C_MODULE *const pI2c, uint32 generateStart);

/**********************************************************************************************************************
 * Function:     I2c_Std_GenerateStop
 * Description:  Generates I2Cx communication STOP condition.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 *               generateStop: TRUE is generate a I2C STOP signal. FALSE is clear STOP flag.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/21    01107     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void I2c_Std_GenerateStop(I2C_MODULE *const pI2c, uint32 generateStop);

/**********************************************************************************************************************
 * Function:     I2c_Std_ConfigAck
 * Description:  Enables or disables the specified I2C acknowledge feature.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 *               enableAck: TRUE is enable the ACK function. FALSE is disable this function.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/21    01107     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void I2c_Std_ConfigAck(I2C_MODULE *const pI2c, uint32 enableAck);

/**********************************************************************************************************************
 * Function:     I2c_Std_WriteDr
 * Description:  Write data to the I2Cx DR register.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 *               data: byte to be transmitted
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/21    01107     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void I2c_Std_WriteDr(I2C_MODULE *const pI2c, uint8 data);

/**********************************************************************************************************************
 * Function:     I2c_Std_DrRead
 * Description:  Returns the most recent received data from the I2Cx DR register.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 * Inout:        None
 * Output:       None
 * Return:       uint32: The value of the received data.
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/21    01107     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 I2c_Std_ReadDr(const I2C_MODULE *const pI2c);

/**********************************************************************************************************************
 * Function:     I2c_Std_GetFifoEnableState
 * Description:  Get FIFO enable state.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE is FIFO enable, FALSE is FIFO disable.
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/21    01107     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean I2c_Std_GetFifoEnableState(const I2C_MODULE *const pI2c);

/**********************************************************************************************************************
 * Function:     I2c_Std_FifoReset
 * Description:  FIFO reset
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/21    01107     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void I2c_Std_FifoReset(I2C_MODULE *const pI2c);

/**********************************************************************************************************************
 * Function:     I2c_Std_SetTransmitTotalBytes
 * Description:  Set the number of send bytes
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 *               transmitLength: The number of send bytes
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/21    01107     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void I2c_Std_SetTransmitTotalLength(I2C_MODULE *const pI2c, uint32 transmitLength);

/**********************************************************************************************************************
 * Function:     I2c_Std_WriteFifo
 * Description:  Write TX FIFO
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 *               data: the data which write to TX FIFO
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/21    01107     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void I2c_Std_WriteFifo(I2C_MODULE *const pI2c, uint32 data);

/**********************************************************************************************************************
 * Function:     I2c_Std_ReadFifo
 * Description:  Read RX FIFO
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 * Inout:        None
 * Output:       None
 * Return:       uint32: the data from RX FIFO
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/21    01107     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 I2c_Std_ReadFifo(const I2C_MODULE *const pI2c);

/**********************************************************************************************************************
 * Function:     I2c_Std_SetHSStart
 * Description:  Set start single on high speed master mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 *               enableHsStart: TRUE is transmit HS-start, FALSE is clear HS-start flag.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/30    01208     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void I2c_Std_SetHSStart(I2C_MODULE *const pI2c, boolean enableHsStart);

/**********************************************************************************************************************
 * Function:     I2c_Std_SetDma
 * Description:  Enable or disable DMA request.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 *               enableDma: TRUE is enable DMA request, FALSE is disable DMA request.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/30    01208     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void I2c_Std_SetDma(I2C_MODULE *const pI2c, boolean enableDma);

/**********************************************************************************************************************
 * Function:     I2c_Std_GetSr1
 * Description:  Get I2C SR1 flag
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 * Inout:        None
 * Output:       None
 * Return:       uint32: SR1 register value. Detail see I2C_Status_Flag
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/01/17    01107     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 I2c_Std_GetSr1(const I2C_MODULE *const pI2c);

/**********************************************************************************************************************
 * Function:     I2c_Std_GetSr2
 * Description:  Get I2C SR2 flag
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 * Inout:        None
 * Output:       None
 * Return:       uint32: SR2 register value. Detail see I2C_Status_Flag
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/01/17    01107     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 I2c_Std_GetSr2(const I2C_MODULE *const pI2c);

/**********************************************************************************************************************
 * Function:     I2c_Std_GetSr3
 * Description:  Get I2C SR3 flag
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 * Inout:        None
 * Output:       None
 * Return:       uint32: SR3 register value. Detail see I2C_Status_Flag
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/01/17    01107     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 I2c_Std_GetSr3(const I2C_MODULE *const pI2c);

/**********************************************************************************************************************
 * Function:     I2c_Std_GetSr4
 * Description:  Get I2C SR4 flag
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 * Inout:        None
 * Output:       None
 * Return:       uint32: SR4 register value. Detail see I2C_Status_Flag
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/01/17    01107     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 I2c_Std_GetSr4(const I2C_MODULE *const pI2c);

/**********************************************************************************************************************
 * Function:     I2c_Std_GetFifoAlign
 * Description:  Get I2C FIFO align mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 * Inout:        None
 * Output:       None
 * Return:       uint32: The align mode of FIFO
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/02/19    01358     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 I2c_Std_GetFifoAlign(const I2C_MODULE *const pI2c);

/**********************************************************************************************************************
 * Function:     I2c_Std_GetTxFifoMark
 * Description:  Get I2C Tx FIFO mark
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 * Inout:        None
 * Output:       None
 * Return:       uint32: The mark of Tx FIFO
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/02/19    01358     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 I2c_Std_GetTxFifoMark(const I2C_MODULE *const pI2c);

/**********************************************************************************************************************
 * Function:     I2c_Std_GetRxFifoMark
 * Description:  Get I2C Rx FIFO mark
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 * Inout:        None
 * Output:       None
 * Return:       uint32: The mark of Rx FIFO
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/02/19    01358     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 I2c_Std_GetRxFifoMark(const I2C_MODULE *const pI2c);

/**********************************************************************************************************************
 * Function:     I2c_Std_GetBurstSize
 * Description:  Get I2C burst size
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 * Inout:        None
 * Output:       None
 * Return:       uint32: The burst size
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/02/19    01358     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 I2c_Std_GetBurstSize(const I2C_MODULE *const pI2c);

/**********************************************************************************************************************
 * Function:     I2c_Std_GetHsCcr
 * Description:  Get I2C high speed mode clock division factor
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 * Inout:        None
 * Output:       None
 * Return:       uint32: The high speed mode clock division factor
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/02/19    01358     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 I2c_Std_GetHsCcr(const I2C_MODULE *const pI2c);

/**********************************************************************************************************************
 * Function:     I2c_Std_GetDmaEnableState
 * Description:  Get Dma enable state.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE is DMA enable, FALSE is DMA disable.
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  20254/02/19   01358     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean I2c_Std_GetDmaEnableState(const I2C_MODULE *const pI2c);

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void I2c_Std_GenerateStart(I2C_MODULE *const pI2c, uint32 generateStart)
{
    pI2c->CR1.B.START = generateStart;
}

LOCAL_FORCEINLINE void I2c_Std_GenerateStop(I2C_MODULE *const pI2c, uint32 generateStop)
{
    pI2c->CR1.B.STOP = generateStop;
}

LOCAL_FORCEINLINE void I2c_Std_ConfigAck(I2C_MODULE *const pI2c, uint32 enableAck)
{
    pI2c->CR1.B.ACK = enableAck;
}

LOCAL_FORCEINLINE void I2c_Std_WriteDr(I2C_MODULE *const pI2c, uint8 data)
{
    pI2c->DR.B.DR = data;
}

LOCAL_FORCEINLINE uint32 I2c_Std_ReadDr(const I2C_MODULE *const pI2c)
{
    return pI2c->DR.B.DR;
}

LOCAL_FORCEINLINE boolean I2c_Std_GetFifoEnableState(const I2C_MODULE *const pI2c)
{
    return pI2c->CR3.B.FIFOEN;
}

LOCAL_FORCEINLINE void I2c_Std_FifoReset(I2C_MODULE *const pI2c)
{
    pI2c->CR3.B.FFLS = 1U; /* Reset */

    pI2c->CR3.B.FFLS = 0U; /* Stop reset */
}

LOCAL_FORCEINLINE void I2c_Std_SetTransmitTotalLength(I2C_MODULE *const pI2c, uint32 transmitLength)
{
    pI2c->CR4.B.TBL = transmitLength & I2C_STD_FIFO_TX_LENGTH_MASK;
}

LOCAL_FORCEINLINE void I2c_Std_WriteFifo(I2C_MODULE *const pI2c, uint32 data)
{
    pI2c->FTXD.B.FTXD = data;
}

LOCAL_FORCEINLINE uint32 I2c_Std_ReadFifo(const I2C_MODULE *const pI2c)
{
    return pI2c->FRXD.B.FRXD;
}

LOCAL_FORCEINLINE void I2c_Std_SetHSStart(I2C_MODULE *const pI2c, boolean enableHsStart)
{
    pI2c->CCR1.B.MHS_START = enableHsStart;
}

LOCAL_FORCEINLINE void I2c_Std_SetDma(I2C_MODULE *const pI2c, boolean enableDma)
{
    pI2c->CR2.B.DMAEN = enableDma;
}

LOCAL_FORCEINLINE uint32 I2c_Std_GetSr1(const I2C_MODULE *const pI2c)
{
    /* Bit 0 ~ 12 */
    return pI2c->SR1.U;
}

LOCAL_FORCEINLINE uint32 I2c_Std_GetSr2(const I2C_MODULE *const pI2c)
{
    return (pI2c->SR2.U & I2C_STD_SR2_MASK);
}

LOCAL_FORCEINLINE uint32 I2c_Std_GetSr3(const I2C_MODULE *const pI2c)
{
    /* Bit 11 ~ 14 */
    return (pI2c->SR3.U & I2C_STD_SR3_MASK);
}

LOCAL_FORCEINLINE uint32 I2c_Std_GetSr4(const I2C_MODULE *const pI2c)
{
    /* Bit 0 ~ 3 */
    return (pI2c->SR4.U & I2C_STD_SR4_MASK);
}

LOCAL_FORCEINLINE uint32 I2c_Std_GetFifoAlign(const I2C_MODULE *const pI2c)
{
    return (uint32)pI2c->CR3.B.ALIGN;
}

LOCAL_FORCEINLINE uint32 I2c_Std_GetTxFifoMark(const I2C_MODULE *const pI2c)
{
    return (uint32)pI2c->CR3.B.TF_ALEMPTY;
}

LOCAL_FORCEINLINE uint32 I2c_Std_GetRxFifoMark(const I2C_MODULE *const pI2c)
{
    return (uint32)pI2c->CR3.B.RF_ALFULL;
}

LOCAL_FORCEINLINE uint32 I2c_Std_GetBurstSize(const I2C_MODULE *const pI2c)
{
    return (uint32)pI2c->CR3.B.BS;
}

LOCAL_FORCEINLINE uint32 I2c_Std_GetHsCcr(const I2C_MODULE *const pI2c)
{
    return (uint32)pI2c->CCR1.B.MHS_CCR;
}

LOCAL_FORCEINLINE boolean I2c_Std_GetDmaEnableState(const I2C_MODULE *const pI2c)
{
    return pI2c->CR2.B.DMAEN;
}

/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:     I2c_Std_Init
 * Description:  I2C initialize
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 *               pInitParameter: The I2C initialize parameter, see I2C_InitParameter.
 * Inout:        None
 * Output:       None
 * Return:       I2c_Std_Status: detail see I2c_Std_Status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/21    01107     Create
 *********************************************************************************************************************/
extern I2c_Std_Status I2c_Std_Init(I2C_MODULE *const pI2c, const I2C_Std_InitParameter *const pInitParameter);

/**********************************************************************************************************************
 * Function:     I2c_Std_CheckFlag
 * Description:  Checks whether the specified I2C status bit has occurred or not.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 *               flag: Specifies the bit of SR1\2\3\4 to check.
 *               This parameter can be find in I2C_Status_Flag
 *               setStatus: TRUE indicates that the expected value of the bits are 1,
 *                          and FALSE indicates that the expected value of the bits are 0.
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE indicated that the expected value of the bits equal the register SRx,
 *               FLASE indicated that the expected value of the bits not equal the register SRx.
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/21    01107     Create
 *********************************************************************************************************************/
extern boolean I2c_Std_CheckFlag(const I2C_MODULE *const pI2c, uint32 flag, boolean setStatus);

/**********************************************************************************************************************
 * Function:     I2c_Std_ClearFlag
 * Description:  clear flag.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 *               flag: Specifies the bit of SR1\2\3\4 to check.
 *               This parameter can be one or combination of the following values:
 *                I2C_SR1_BREQ
 *                I2C_SR1_BERR
 *                I2C_SR1_ARLO
 *                I2C_SR1_AF
 *                I2C_SR1_OVR
 *                I2C_SR1_PECERR
 *                I2C_SR3_SHCM
 *                I2C_SR3_FIFOSREQ
 *                I2C_SR4_RFUFL
 *                I2C_SR4_TFOFL
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/21    01107     Create
 *********************************************************************************************************************/
extern void I2c_Std_ClearFlag(I2C_MODULE *const pI2c, uint32 flag);

#define I2C_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "I2c_MemMap.h"

#endif /* I2C_STD_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
