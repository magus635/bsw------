/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    i2c_hal.c
 * Author:      01107
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all functions of i2c module.
 *********************************************************************************************************************/
/*
*#i2c_hal_c_REF_1:MISRAC2012-Rule-11.4;
* Justification:Converting integers to object pointers to reduce register access complexity
*
*#i2c_hal_c_REF_2:MISRAC2012-Dir-4.9;
* Justification:Function like macros are used to reduce code complexity
*
*#i2c_hal_c_REF_3:MISRAC2012-Rule-10.5;
* Justification:Limitation of Cortex-R52+ Core; Boolean can only be representes as uint8
*
*#i2c_hal_c_REF_4:MISRAC2012-Rule-2.1;
* Justification:Reserved API for user access
*
*#i2c_hal_c_REF_5:MISRAC2012-Dir-4.3;
* Justification:Mixing inline assembly with C code reduces code complexity
*
*#i2c_hal_c_REF_6:MISRAC2012-Rule-10.5;
* Justification:Necessary type casting to reduce code complexity; Code review ensure the safety of the casting.
*
*#i2c_hal_c_REF_7:MISRAC2012-Rule-8.7; 
* Justification:The function is used by other file.
*
*#i2c_hal_c_REF_8:CWE-1071; 
* Justification:MISRA-2012 Rule 15.7/Rule 16.4 require reserved empty code block.
*
*#i2c_hal_c_REF_9:CertC-DCL15-C;
* Justification:Reserved API for user access.
*
*#i2c_hal_c_REF_10:MISRAC2012-Rule-1.2;
* Justification:Inline assembly for CPU-specific operations.
*
*#i2c_hal_c_REF_11:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "i2c_std.h"
#include "i2c_hal.h"
#include "rcc_hal.h"
#include "tha6_cfg.h"
#include "compilertypes.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/* ^I2C_DIRECTION^ I2C transfer definition */
#define I2C_DIRECTION_RECEIVE (0x00000000U)  /* direction is receiver */
#define I2C_DIRECTION_TRANSMIT (0x00000001U) /* direction is transmit */

/* I2C High Speed Master Code Mask */
#define I2C_MASTERCODE_MAX (0xFU)  /* MAX Master code */
#define I2C_MASTERCODE_MIN (0x8U)  /* MIN Master code */

/* I2C Hal Status Clear Mask: SR1\SR4 */
#define I2C_SR_CLEARMASK (0x90001F20U) /* I2C SR1/SR4 mask value */
/**********************************************************************************************************************
 *                                            Private Structure Definitions
 *********************************************************************************************************************/
/* Structure for checking timeout function */
typedef struct
{
    boolean (*pFunction)(const I2C_MODULE *const p, uint32 flag, boolean setStatus); /* The input function */
    uint32 expectBits;   /* The bits to be associated with the return value of pFunction */
    boolean setOrClear;  /* if TRUE,  the return value of pFunction and expectBits equal, otherwise not equal. */
    uint64 timeoutValue; /* Timeout value */
} I2C_TimeoutCheck;

/* Structure for I2C transmit data */
typedef struct
{
    uint8 *pData;     /* Pointer to a data address */
    uint32 dataSize;  /* The size of data to be transmitted */
    uint32 flag;      /* Waiting flag */
    uint32 timeOut;   /* Waiting timeout */
    uint32 direction; /* Transmit direction */
} I2C_TransmitData;
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
#define I2C_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: i2c_hal_c_REF_11 */
#include "I2c_MemMap.h"

/**********************************************************************************************************************
 * Function:     I2c_Hal_CheckTimeout
 * Description:  Timeout check
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 *               pVariable: timeout structure, detail see I2C_TimeoutCheck
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE is timeout, FALSE is not timeout.
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/22    01107     Create
 *  2024/03/28    01208     Modify
 *********************************************************************************************************************/
static boolean I2c_Hal_CheckTimeout(const I2C_MODULE *const pI2c, const I2C_TimeoutCheck *const pVariable);

/**********************************************************************************************************************
 * Function:     I2c_Hal_WaitFlagClear
 * Description:  Wait the I2C module flag clear
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 *               flag: Specifies the bit of SR1\2\3\4 to check.
 *               timeOut: timeout value
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE is timeout, FALSE is not timeout.
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/22    01107     Create
 *  2024/03/28    01208     Modify
 *********************************************************************************************************************/
static boolean I2c_Hal_WaitFlagClear(const I2C_MODULE *const pI2c, uint32 flag, uint32 timeOut);

/**********************************************************************************************************************
 * Function:     I2c_Hal_WaitFlagSet
 * Description:  Wait the I2C module flag set
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 *               flag: Specifies the bit of SR1\2\3\4 to check.
 *               timeOut: timeout value
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE is timeout, FALSE is not timeout.
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/22    01107     Create
 *  2024/03/28    01208     Modify
 ********************************************************************************************************************/
static boolean I2c_Hal_WaitFlagSet(const I2C_MODULE *const pI2c, uint32 flag, uint32 timeOut);

/**********************************************************************************************************************
 * Function:     I2c_Hal_WaitEventSet
 * Description:  Wait I2C event set
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 *               i2cEvent: specifies the event to be checked.
 *               This parameter can be one of the following values:
 *               I2C_EV5_MASTER_MODE_SELECT
 *               I2C_EV6_MASTER_TRANSMITTER_MODE_SELECTED
 *               I2C_EV6_MASTER_RECEIVER_MODE_SELECTED
 *               I2C_EV7_MASTER_DATA_RECEIVED
 *               I2C_EV8_MASTER_DATA_TRANSMITTING 
 *               I2C_EV8_2_MASTER_DATA_TRANSMITTED
 *               I2C_EV9_MASTER_MODE_ADDRESS10
 *               timeOut: timeout time
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE is timeout, FALSE is not timeout.
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/22    01107     Create
 *  2024/03/28    01208     Modify
 *********************************************************************************************************************/
static boolean I2c_Hal_WaitEventSet(const I2C_MODULE *const pI2c, uint32 i2cEvent, uint32 timeOut);

/**********************************************************************************************************************
 * Function:     I2c_Hal_Transmit7bitAddress
 * Description:  I2C transmit hardware address
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 *               pDeviceInfo: detail see structure I2C_DeviceInfo.
 *               pTransmitData: detail see structure I2C_TransmitData.
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE is timeout, FALSE is not timeout.
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/22    01107      Create
 *  2024/03/28    01208     Modify
 *********************************************************************************************************************/
static boolean I2c_Hal_Transmit7bitAddress(I2C_MODULE *const pI2c, const I2C_DeviceInfo *const pDeviceInfo, const I2C_TransmitData *const pTransmitData);

/**********************************************************************************************************************
 * Function:     I2c_Hal_ReadDataWithFifo
 * Description:  I2C read data from Rxfifo
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 *               pTransmitData: detail see structure I2C_TransmitData.
 *               pTransmitSize: pointer holding the size of transmit
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE is timeout or read fail, FALSE is not timeout and read success.
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/06/03    01358      Create
 *********************************************************************************************************************/
static boolean I2c_Hal_ReadDataWithFifo(I2C_MODULE *const pI2c, uint32* const pTransmitSize, const I2C_TransmitData *const pTransmitData);

/**********************************************************************************************************************
 * Function:     I2c_Hal_ReadDataWithDr
 * Description:  I2C read data from Dr
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 *               pTransmitData: detail see structure I2C_TransmitData.
 *               pTransmitSize: pointer holding the size of transmit
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE is timeout or read fail, FALSE is not timeout and read success.
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/06/03    01358      Create
 *********************************************************************************************************************/
static boolean I2c_Hal_ReadDataWithDr(I2C_MODULE *const pI2c, uint32* const pTransmitSize, const I2C_TransmitData *const pTransmitData);

/**********************************************************************************************************************
 * Function:     I2c_Hal_ReadData
 * Description:  I2C read data from Rxfifo or DR
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 *               pTransmitData: detail see structure I2C_TransmitData.
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE is timeout or read fail, FALSE is not timeout and read success.
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/02/26    01358      Create
 *********************************************************************************************************************/
static boolean I2c_Hal_ReadData(I2C_MODULE *const pI2c, const I2C_TransmitData *const pTransmitData);

/**********************************************************************************************************************
 * Function:     I2c_Hal_ReadFifoSingle
 * Description:  I2C read data from Rxfifo
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 *               fifoAlignment: The alignment of Rxfifo
 *               transmitDataSize: The size of the received data
 *               pTransmitData: detail see structure I2C_TransmitData.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/02/26    01358      Create
 *********************************************************************************************************************/
static void I2c_Hal_ReadFifoSingle(const I2C_MODULE *const pI2c, uint32 fifoAlignment, uint32 *const transmitDataSize, const I2C_TransmitData *const pTransmitData);

/**********************************************************************************************************************
 * Function:     I2c_Hal_ReadFIfoBurst
 * Description:  I2C read data from Rxfifo
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 *               fifoAlignment: The alignment of Rxfifo
 *               fifoLevel: The watermask of Rxfifo
 *               transmitDataSize: The size of the received data
 *               pTransmitData: detail see structure I2C_TransmitData.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/02/26    01358      Create
 *********************************************************************************************************************/
static void I2c_Hal_ReadFIfoBurst(const I2C_MODULE *const pI2c, uint32 fifoAlignment, uint32 fifoLevel, uint32 *const transmitDataSize, const I2C_TransmitData *const pTransmitData);

/**********************************************************************************************************************
 * Function:     I2c_Hal_WriteData
 * Description:  I2C write data to Txfifo or DR
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 *               pTransmitData: detail see structure I2C_TransmitData.
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE is timeout or write fail, FALSE is not timeout and write success.
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/02/26    01358      Create
 *********************************************************************************************************************/
static boolean I2c_Hal_WriteData(I2C_MODULE *const pI2c, const I2C_TransmitData *const pTransmitData);

/**********************************************************************************************************************
 * Function:     I2c_Hal_WriteData
 * Description:  I2C write data to Txfifo
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 *               fifoAlignment: The alignment of Txfifo
 *               transmitDataSize: The size of the send data
 *               pTransmitData: detail see structure I2C_TransmitData.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/02/26    01358      Create
 *********************************************************************************************************************/
static void I2c_Hal_WriteFIfoSingle(I2C_MODULE *const pI2c, uint32 fifoAlignment, uint32 *const transmitDataSize, const I2C_TransmitData *const pTransmitData);

/**********************************************************************************************************************
 * Function:     I2c_Hal_WriteFIfoBurst
 * Description:  I2C write data to Txfifo
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 *               fifoAlignment: The alignment of Txfifo
 *               fifoLevel: The watermask of Txfifo
 *               transmitDataSize: The size of the send data
 *               pTransmitData: detail see structure I2C_TransmitData.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/02/26    01358      Create
 *********************************************************************************************************************/
static void I2c_Hal_WriteFIfoBurst(I2C_MODULE *const pI2c, uint32 fifoAlignment, uint32 fifoLevel, uint32 *const transmitDataSize, const I2C_TransmitData *const pTransmitData);

/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
static boolean I2c_Hal_CheckTimeout(const I2C_MODULE *const pI2c, const I2C_TimeoutCheck *const pVariable)
{
    boolean timeOutStatus;
    boolean checkResult;
    uint64 tickStart;
    uint64 currentTick;
    uint64 tickEnd;

    timeOutStatus = TRUE;

    tickStart = 0U;
    tickEnd = pVariable->timeoutValue;
    currentTick = tickStart;

    do
    {
        /* get flag set status */
        checkResult = pVariable->pFunction(pI2c, pVariable->expectBits, pVariable->setOrClear);

        if(TRUE == checkResult)
        {
            timeOutStatus = FALSE;
        }
        else
        {
            currentTick++;
        }
    /* flag is not set and the timeout event does not occur */
    } while((currentTick < tickEnd) && (FALSE == checkResult));

    return timeOutStatus;
}

static boolean I2c_Hal_WaitFlagClear(const I2C_MODULE *const pI2c, uint32 flag, uint32 timeOut)
{
    boolean timeOutStatus;
    I2C_TimeoutCheck timeoutCheck;

    /* Wait expectBits */
    timeoutCheck.pFunction = I2c_Std_CheckFlag;
    timeoutCheck.timeoutValue = timeOut;
    timeoutCheck.expectBits = flag;
    timeoutCheck.setOrClear = FALSE; /* the expect bits are 0 */

    /* get timeout status */
    timeOutStatus = I2c_Hal_CheckTimeout(pI2c, &timeoutCheck);

    return timeOutStatus;
}

static boolean I2c_Hal_WaitFlagSet(const I2C_MODULE *const pI2c, uint32 flag, uint32 timeOut)
{
    boolean timeOutStatus;
    I2C_TimeoutCheck timeoutCheck;

    /* Wait expectBits */
    timeoutCheck.pFunction = I2c_Std_CheckFlag;
    timeoutCheck.timeoutValue = timeOut;
    timeoutCheck.expectBits = flag;
    timeoutCheck.setOrClear = TRUE; /* the expect bits are 1 */
    /* get timeout status */
    timeOutStatus = I2c_Hal_CheckTimeout(pI2c, &timeoutCheck);

    return timeOutStatus;
}

static boolean I2c_Hal_WaitEventSet(const I2C_MODULE *const pI2c, uint32 i2cEvent, uint32 timeOut)
{
    boolean timeOutStatus;
    I2C_TimeoutCheck timeoutCheck;

    /* Wait expectBits */
    timeoutCheck.pFunction = I2c_Std_CheckFlag;
    timeoutCheck.timeoutValue = timeOut;
    timeoutCheck.expectBits = i2cEvent;
    timeoutCheck.setOrClear = TRUE; /* the expect bits are 1 */
    /* get timeout status */
    timeOutStatus = I2c_Hal_CheckTimeout(pI2c, &timeoutCheck);

    return timeOutStatus;
}

static void I2c_Hal_WriteFIfoBurst(I2C_MODULE *const pI2c, uint32 fifoAlignment, uint32 fifoLevel, uint32 *const transmitDataSize, const I2C_TransmitData *const pTransmitData)
{
    uint32 levelSize;
    uint32 bsDataSize;
    uint32 transmitSize;
    uint32 writeTime;
    
    transmitSize = *transmitDataSize;
    levelSize = (I2C_FIFO_ALIGNBYTE_1 == fifoAlignment) ? 4U : ((I2C_FIFO_ALIGNBYTE_2 == fifoAlignment) ? 2U : 1U);
    bsDataSize = levelSize * fifoLevel;
    /* The remaining amount of data to be transmitted is greater than or equal to 
       the maximum burst transfer amount supported by the FIFO in a single operation. */
    if((pTransmitData->dataSize - transmitSize) >= bsDataSize)
    {   
        /* The number of writes is less than the FIFO watermark */
        for (writeTime = 0U; writeTime < fifoLevel; writeTime++)
        {
            /* write once data to txfifo */
            I2c_Hal_WriteFIfoSingle(pI2c, fifoAlignment, &transmitSize, pTransmitData);
        }
    }
    else
    {
        /* write once data to txfifo */
        I2c_Hal_WriteFIfoSingle(pI2c, fifoAlignment, &transmitSize, pTransmitData);
    } 

    /* update current transmit size */
    *transmitDataSize = transmitSize;
}

static void I2c_Hal_WriteFIfoSingle(I2C_MODULE *const pI2c, uint32 fifoAlignment, uint32 *const transmitDataSize, const I2C_TransmitData *const pTransmitData)
{
    uint32 fifoData;
    uint32 transmitSize;
    uint8 const *transmitBuff;
    
    transmitSize = *transmitDataSize;
    /* #Violation: i2c_hal_c_REF_1 */
    /* #Violation: i2c_hal_c_REF_1 */
    transmitBuff = (uint8 const *)((uint32)pTransmitData->pData + transmitSize);

    if(I2C_FIFO_ALIGNBYTE_4 == fifoAlignment)
    {
        fifoData = *transmitBuff;
        transmitSize++;
    }
    else if(I2C_FIFO_ALIGNBYTE_2 == fifoAlignment)
    {
        if((pTransmitData->dataSize - transmitSize) >= 2U)
        {
            fifoData = *transmitBuff;
            transmitBuff++;
            fifoData |= ((uint32)(*transmitBuff) << 8U);
            transmitSize += 2U;
        }
        else
        {
            fifoData = *transmitBuff;
            transmitSize++;
        }
    }
    else
    {
        if((pTransmitData->dataSize - transmitSize) >= 4U)
        {
            fifoData = *transmitBuff;
            transmitBuff++;
            fifoData |= (uint32)(*transmitBuff) << 8U;
            transmitBuff++;
            fifoData |= (uint32)(*transmitBuff) << 16U;
            transmitBuff++;
            fifoData |= (uint32)(*transmitBuff) << 24U;
            transmitSize += 4U;
        }
        else if((pTransmitData->dataSize - transmitSize) == 3U)
        {
            fifoData = *transmitBuff;
            transmitBuff++;
            fifoData |= (uint32)(*transmitBuff) << 8U;
            transmitBuff++;
            fifoData |= (uint32)(*transmitBuff) << 16U;
            transmitSize += 3U;
        }
        else if((pTransmitData->dataSize - transmitSize) == 2U)
        {
            fifoData = *transmitBuff;
            transmitBuff++;
            fifoData |= (uint32)(*transmitBuff) << 8U;
            transmitSize += 2U;
        }
        else
        {
            fifoData = *transmitBuff;
            transmitSize++;
        }
    }
    
    /* write once data to txfifo */
    I2c_Std_WriteFifo(pI2c, fifoData);

    /* update current transmit size */
    *transmitDataSize = transmitSize;
}

static boolean I2c_Hal_WriteData(I2C_MODULE *const pI2c, const I2C_TransmitData *const pTransmitData)
{
    uint32 transmitSize;
    uint32 burstSize;
    uint32 fifoAlign;
    uint32 fifoLevel;
    uint8 const *transmitBuffer;
    boolean timeOutStatus;
    boolean fifoEnable;

    transmitSize = 0U;
    timeOutStatus = FALSE;
    /* get fifo burst size */
    burstSize = I2c_Std_GetBurstSize(pI2c);
    /* get fifo enable status */
    fifoEnable = I2c_Std_GetFifoEnableState(pI2c);
    /* fifo is enabled */
    if(TRUE == fifoEnable)
    {   
        /* get fifo alignment mode */
        fifoAlign = I2c_Std_GetFifoAlign(pI2c);

        /* burst size is equal to I2C_FIFO_BURST_SIZE_1*/
        if(I2C_FIFO_BURST_SIZE_1 == burstSize)
        {   
            /* The total cumulative transmitted data is less than the total amount of data to be transmitted, 
               and the timeout event has not occurred. */
            while((transmitSize < pTransmitData->dataSize) && (FALSE == timeOutStatus))
            {
                /* wait for flag to be set and get timeout status */
                timeOutStatus = I2c_Hal_WaitFlagSet(pI2c, I2C_SR3_FIFOSREQ, pTransmitData->timeOut);
                /* The timeout event does not occur */
                if(FALSE == timeOutStatus)
                {
                    /* write a single transfer of data to TXFIFO */
                    I2c_Hal_WriteFIfoSingle(pI2c, fifoAlign, &transmitSize, pTransmitData);
                }
            }
        }
        else
        {   
            /* get txfifo water mark */
            fifoLevel = I2c_Std_GetTxFifoMark(pI2c);
            /* The total cumulative transmitted data is less than the total amount of data to be transmitted, 
               and the timeout event has not occurred. */
            while((transmitSize < pTransmitData->dataSize) && (FALSE == timeOutStatus))
            {
                /* wait for flag to be set and get timeout status */
                timeOutStatus = I2c_Hal_WaitFlagSet(pI2c, I2C_SR1_BREQ, pTransmitData->timeOut);
                /* The timeout event does not occur */
                if(FALSE == timeOutStatus)
                {
                    /* Write a burst of data to the TXFIFO */
                    I2c_Hal_WriteFIfoBurst(pI2c, fifoAlign, fifoLevel, &transmitSize, pTransmitData);
                }
                /* Clear flag */
                I2c_Hal_ClearFlag(pI2c, I2C_SR1_BREQ);
            }
        } 
    }
    else
    {
        transmitBuffer = pTransmitData->pData;
        /* The total cumulative transmitted data is less than the total amount of data to be transmitted, 
            and the timeout event has not occurred. */
        while((transmitSize < pTransmitData->dataSize) && (FALSE == timeOutStatus))
        {
            /* write a single transfer of data to dr register */
            I2c_Std_WriteDr(pI2c, *transmitBuffer);
            /* wait for flag to be set and get timeout status */
            timeOutStatus = I2c_Hal_WaitEventSet(pI2c, pTransmitData->flag, pTransmitData->timeOut);
            transmitSize++;
            transmitBuffer++;
        } 
    }  
    
    return ((transmitSize == pTransmitData->dataSize) && (FALSE == timeOutStatus)) ? FALSE : TRUE;  
}

static boolean I2c_Hal_Transmit7bitAddress(I2C_MODULE *const pI2c, const I2C_DeviceInfo *const pDeviceInfo, const I2C_TransmitData *const pTransmitData)
{
    boolean timeOutStatus;
    uint8 hdAddress;

    /* Device address size: 7Bit*/
    hdAddress = (uint8)pDeviceInfo->devAddress;

    if(I2C_DIRECTION_RECEIVE == pTransmitData->direction)
    {
        hdAddress |= (uint8)(0x01U);
    }
    else
    {
        hdAddress &= (uint8)(0xFEU);
    }

    /* write a single transfer of data to DR register */
    I2c_Std_WriteDr(pI2c, hdAddress);
    /* wait for flag to be set and get timeout status */
    timeOutStatus = I2c_Hal_WaitEventSet(pI2c, pTransmitData->flag, pTransmitData->timeOut);

    return timeOutStatus;
}

static boolean I2c_Hal_ReadDataWithFifo(I2C_MODULE *const pI2c, uint32* const pTransmitSize, const I2C_TransmitData *const pTransmitData)
{
    boolean timeOutStatus;
    uint32 fifoAlign;
    uint32 transmitSize;
    uint32 bsDataSize;
    uint32 burstSize;
    uint32 levelSize;
    uint32 fifoLevel;
    
    timeOutStatus = FALSE;
    /* get fifo alignment mode */
    fifoAlign = I2c_Std_GetFifoAlign(pI2c);
    /* get fifo burst size */
    burstSize = I2c_Std_GetBurstSize(pI2c);
    transmitSize = *pTransmitSize;

    /* burst size is equal to I2C_FIFO_BURST_SIZE_1*/
    if(I2C_FIFO_BURST_SIZE_1 == burstSize)
    {
        /* The total cumulative transmitted data is less than the total amount of data to be transmitted, 
            and the timeout event has not occurred */
        while((transmitSize < pTransmitData->dataSize) && (FALSE == timeOutStatus))
        {
            /* wait for flag to be set and get timeout status */
            timeOutStatus = I2c_Hal_WaitFlagSet(pI2c, I2C_SR3_FIFOSREQ, pTransmitData->timeOut);
            /* The timeout event does not occur */
            if(FALSE == timeOutStatus)
            {
                /* read a single transfer of data from Tthe RXFIFO */
                I2c_Hal_ReadFifoSingle(pI2c, fifoAlign, &transmitSize, pTransmitData);
            }
        }
    }
    else
    {
        /* get rxfifo mark */
        fifoLevel = I2c_Std_GetRxFifoMark(pI2c);
        levelSize = (I2C_FIFO_ALIGNBYTE_1 == fifoAlign) ? 4U : ((I2C_FIFO_ALIGNBYTE_2 == fifoAlign) ? 2U : 1U);
        bsDataSize = fifoLevel * levelSize;
        /* The remaining amount of data to be read is greater than or equal to 
        the maximum burst transfer amount supported by the FIFO in a single operation */
        while(((pTransmitData->dataSize - transmitSize) >= bsDataSize) && (FALSE == timeOutStatus))
        {
            /* wait for flag to be set and get timeout status */
            timeOutStatus = I2c_Hal_WaitFlagSet(pI2c, I2C_SR1_BREQ, pTransmitData->timeOut);
            /* The timeout event does not occur */
            if(FALSE == timeOutStatus)
            {
                /* read a burst of data from the RXFIFO */
                I2c_Hal_ReadFIfoBurst(pI2c, fifoAlign, fifoLevel, &transmitSize, pTransmitData);
            }
            /* clear flag */
            I2c_Hal_ClearFlag(pI2c, I2C_SR1_BREQ);
        }

        /* The cumulative amount of data transmitted is less than the total amount of data to be transmitted */
        if(transmitSize != (pTransmitData->dataSize))
        {
            /* The total cumulative transmitted data is less than the total amount of data to be transmitted, 
            and the timeout event has not occurred */
            while((FALSE == timeOutStatus) && (transmitSize < (pTransmitData->dataSize)))
            {
                /* wait for flag to be set and get timeout status */
                timeOutStatus = I2c_Hal_WaitEventSet(pI2c, I2C_SR3_FIFOSREQ, pTransmitData->timeOut);
                if(FALSE == timeOutStatus)
                {
                    /* read a single of data from the RXFIFO */
                    I2c_Hal_ReadFifoSingle(pI2c, fifoAlign, &transmitSize, pTransmitData);
                }
            }
        }
    } 

    /* Enable the auto-acknowledge function */
    I2c_Std_ConfigAck(pI2c, 1U);
    /* Send STOP condition */
    I2c_Std_GenerateStop(pI2c, 1U);
    /* Flush fifo */
    I2c_Std_FifoReset(pI2c);

    /* update transmit size */
    *pTransmitSize = transmitSize;

    return timeOutStatus;
}

static boolean I2c_Hal_ReadDataWithDr(I2C_MODULE *const pI2c, uint32* const pTransmitSize, const I2C_TransmitData *const pTransmitData)
{
    uint8 *pTransmitBuffer;
    boolean timeOutStatus;
    uint32 transmitSize;

    timeOutStatus = FALSE;
    pTransmitBuffer = pTransmitData->pData;
    transmitSize = *pTransmitSize;
    /* The total cumulative transmitted data is less than the total amount of data to be transmitted, 
        and the timeout event has not occurred */
    while((FALSE == timeOutStatus) && (transmitSize < pTransmitData->dataSize))
    {
        /* The data currently being transmitted is the second last byte */
        if(transmitSize == (pTransmitData->dataSize - 1U))
        {
            /* Disable the auto-acknowledge function */
            I2c_Std_ConfigAck(pI2c, 0U);
            /* Send STOP condition */
            I2c_Std_GenerateStop(pI2c, 1U);
        }

        /* wait for flag to be set and get timeout status */
        timeOutStatus = I2c_Hal_WaitEventSet(pI2c, I2C_EV7_MASTER_DATA_RECEIVED, pTransmitData->timeOut);
        /* The timeout event does not occur */
        if(FALSE == timeOutStatus)
        {
            /* read data from DR register */
            *pTransmitBuffer = (uint8)I2c_Std_ReadDr(pI2c);
            pTransmitBuffer++;
            transmitSize++;
        }
    } 

    /* update transmit size */
    *pTransmitSize = transmitSize;

    return timeOutStatus;
}

static boolean I2c_Hal_ReadData(I2C_MODULE *const pI2c, const I2C_TransmitData *const pTransmitData)
{
    uint32 transmitSize;
    boolean timeOutStatus;
    boolean fifoEnable;

    transmitSize = 0U;
    /* get fifo enable status */
    fifoEnable = I2c_Std_GetFifoEnableState(pI2c);

    /* fifo is enabled */
    if(TRUE == fifoEnable)
    {
        /* read data from fifo and get timeout status */
        timeOutStatus = I2c_Hal_ReadDataWithFifo(pI2c, &transmitSize, pTransmitData);
    }
    /* fifo is disabled */
    else
    {
        /* read data from DR register and get timeout status */
        timeOutStatus = I2c_Hal_ReadDataWithDr(pI2c, &transmitSize, pTransmitData);
    }  
    
    return ((transmitSize == pTransmitData->dataSize) && (FALSE == timeOutStatus)) ? FALSE : TRUE;  
}

static void I2c_Hal_ReadFifoSingle(const I2C_MODULE *const pI2c, uint32 fifoAlignment, uint32 *const transmitDataSize, const I2C_TransmitData *const pTransmitData)
{
    uint32 fifoData;
    uint32 readCounter = *transmitDataSize;
    uint8 *readBuffer;

    /* read data from fifo */
    fifoData = I2c_Std_ReadFifo(pI2c);
    /* #Violation: i2c_hal_c_REF_1 */
    /* #Violation: i2c_hal_c_REF_1 */
    readBuffer = (uint8 *)((uint32)pTransmitData->pData + readCounter);

    if(I2C_FIFO_ALIGNBYTE_4 == fifoAlignment)
    {
        *readBuffer = (uint8)fifoData;
        readCounter++;
    }
    else if(I2C_FIFO_ALIGNBYTE_2 == fifoAlignment)
    {
        if((pTransmitData->dataSize - readCounter) >= 2U)
        {
            *readBuffer = (uint8)(fifoData);
            readBuffer++;
#if defined(THA6_THA6412) || defined(THA6_THA6104)
            *readBuffer = (uint8)(fifoData >> 8U);
#endif /* THA6_THA6412 or THA6_THA6104 */

#if defined(THA6_THA6206) || defined(THA6_THA6206D)
            *readBuffer = (uint8)(fifoData >> 16U);
#endif /* THA6_THA6206 or THA6_THA6206D */
            readCounter += 2U;
        }
        else
        {
            *readBuffer = (uint8)fifoData;
            readCounter++;
        }
    }
    else if(I2C_FIFO_ALIGNBYTE_1 == fifoAlignment)
    {
        if((pTransmitData->dataSize - readCounter) >= 4U)
        {
            *readBuffer = (uint8)(fifoData);
            readBuffer++;
            *readBuffer = (uint8)(fifoData >> 8U);
            readBuffer++;
            *readBuffer = (uint8)(fifoData >> 16U);
            readBuffer++;
            *readBuffer = (uint8)(fifoData >> 24U);
            readCounter += 4U;
        }
        else if((pTransmitData->dataSize - readCounter) == 3U)
        {
            *readBuffer = (uint8)(fifoData);
            readBuffer++;
            *readBuffer = (uint8)(fifoData >> 8U);
            readBuffer++;
            *readBuffer = (uint8)(fifoData >> 16U);
            readCounter += 3U;
        }
        else if((pTransmitData->dataSize - readCounter) == 2U)
        {
            *readBuffer = (uint8)(fifoData);
            readBuffer++;
            *readBuffer = (uint8)(fifoData >> 8U);
            readCounter += 2U;
        }
        else
        {
            *readBuffer = (uint8)(fifoData);
            readCounter++;
        }
    }
    else
    {
        /* N.A */
    }

    *transmitDataSize = readCounter;
}

static void I2c_Hal_ReadFIfoBurst(const I2C_MODULE *const pI2c, uint32 fifoAlignment, uint32 fifoLevel, uint32 *const transmitDataSize, const I2C_TransmitData *const pTransmitData)
{
    uint32 readTime;

    /* The number of reads is less than the FIFO watermark */
    for(readTime = 0U; readTime < fifoLevel; readTime++)
    {
        /* read once data from fifo */
        I2c_Hal_ReadFifoSingle(pI2c, fifoAlignment, transmitDataSize, pTransmitData);
    }
}
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: i2c_hal_c_REF_4 */
I2c_Status I2c_Hal_Init(I2C_MODULE *const pI2c, const I2C_InitParameter *const pInitParameter)
{
    I2c_Status status;
    I2C_Std_InitParameter stdInitParameter;

#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the module pointer is a valid pointer */
    /* Check I2C base address */
    /* #Violation: i2c_hal_c_REF_1 */
    /* #Violation: i2c_hal_c_REF_2 */
    Assert((boolean)(CHECK_I2C_BASE(pI2c)));
    /* Check if the configure parameter pointer is null pointer */
    /* #Violation: i2c_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pInitParameter));
    /* Check if the FIFO alignment mode is less than or equal to I2C_FIFO_ALIGNBYTE_4 */
    /* #Violation: i2c_hal_c_REF_3 */
    Assert((boolean)(pInitParameter->fifoAlignMode <= I2C_FIFO_ALIGNBYTE_4));
    /* Check if the TXFIFO threshold is more than or equal to I2C_FIFO_TX_WATERMARK_1 */
    /* #Violation: i2c_hal_c_REF_3 */
    Assert((boolean)(pInitParameter->fifoTxWaterMark >= I2C_FIFO_TX_WATERMARK_1));
    /* Check if the TXFIFO threshold is less than or equal to I2C_FIFO_TX_WATERMARK_4 */
    /* #Violation: i2c_hal_c_REF_3 */
    Assert((boolean)(pInitParameter->fifoTxWaterMark <= I2C_FIFO_TX_WATERMARK_4));
    /* Check if the RXFIFO threshold is more than or equal to I2C_FIFO_RX_WATERMARK_4 */
    /* #Violation: i2c_hal_c_REF_3 */
    Assert((boolean)(pInitParameter->fifoRxWaterMark >= I2C_FIFO_RX_WATERMARK_4));
     /* Check if the RXFIFO threshold is less than or equal to I2C_FIFO_RX_WATERMARK_7 */
    /* #Violation: i2c_hal_c_REF_3 */
    Assert((boolean)(pInitParameter->fifoRxWaterMark <= I2C_FIFO_RX_WATERMARK_7));
#endif

    stdInitParameter.enFifo = pInitParameter->enFifo;
    stdInitParameter.fifoRxWaterMark = pInitParameter->fifoRxWaterMark;
    stdInitParameter.fifoTxWaterMark = pInitParameter->fifoTxWaterMark;
    stdInitParameter.fifoAlignMode = pInitParameter->fifoAlignMode;
    stdInitParameter.busSpeed = pInitParameter->busSpeed;
    stdInitParameter.dutyCycle = pInitParameter->dutyCycle;
    stdInitParameter.burstSize = pInitParameter->burstSize;
    /* get AHB clock frequency */
    stdInitParameter.coreFrequency = (uint32)Rcc_Hal_GetAhbApbClkFreq();

    /* Initialize the I2C module based on the passed parameters: stdInitParameter 
       and get the initialization completion status*/
    /* #Violation: i2c_hal_c_REF_6 */
    status = (I2c_Status)I2c_Std_Init(pI2c, &stdInitParameter);
    return status;
}

/* #Violation: i2c_hal_c_REF_4 */
/* #Violation: i2c_hal_c_REF_5 */
I2c_Status I2c_Hal_DeInit(const I2C_MODULE *const pI2c)
{
    Rcc_ErrorFlag errorFlag = RCC_ERRORFLAG_TIMEOUT;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the module pointer is a valid pointer */
    /* Check I2C base address */
    /* #Violation: i2c_hal_c_REF_1 */
    /* #Violation: i2c_hal_c_REF_2 */
    Assert((boolean)(CHECK_I2C_BASE(pI2c)));
#endif
    
    /* flag is not set */
    /* get flag set status */
    if(FALSE == I2c_Std_CheckFlag(pI2c, I2C_SR2_BUSY, TRUE))
    {
        /* Ensure that all memory access operations are completed */
        /* #Violation: i2c_hal_c_REF_10 */
        DSB();

        /* module pointer is equal to I2C0 */
        /* #Violation: i2c_hal_c_REF_1 */
        if(I2C0 == pI2c)
        {
            /* Reset I2C0 and get reset flag */
            errorFlag = Rcc_Hal_TrigModuleRst(RCC_MODULERST_I2C0);
        }
        else
        {
            /* #Violation: i2c_hal_c_REF_8 */
#if defined(THA6_THA6412) || defined(THA6_THA6104) 
            /* Reset I2C1 and get reset flag */
            errorFlag = Rcc_Hal_TrigModuleRst(RCC_MODULERST_I2C1);
#endif /* THA6_THA6412 or THA6_THA6104 */
        }
    }

    return (RCC_ERRORFLAG_SUCCESS == errorFlag) ? I2C_STATUS_OK : I2C_STATUS_ERROR;
}

/* #Violation: i2c_hal_c_REF_4 */
I2c_Status I2c_Hal_MasterWrite(I2C_MODULE *const pI2c, const I2C_DeviceInfo *const pDeviceInfo)
{
    boolean timeOutStatus;
    boolean fifoEnable;
    I2C_TransmitData transmitData;

#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the module pointer is a valid pointer */
    /* Check I2C base address */
    /* #Violation: i2c_hal_c_REF_1 */
    /* #Violation: i2c_hal_c_REF_2 */
    Assert((boolean)(CHECK_I2C_BASE(pI2c)));
    /* Check if the parameter configure pointer is null pointer */
    /* #Violation: i2c_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pDeviceInfo));
    /* Check if the data buffer pointer is null pointer */
    /* #Violation: i2c_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != (pDeviceInfo->pData)));
    /* High Speed Mode is enabled */
    /* get High Speed Mode enable status */
    if(0U != I2c_Std_GetHsCcr(pI2c))
    {
        /* Check if the master code does not exceed the maximum value */
        /* #Violation: i2c_hal_c_REF_3 */
        Assert((boolean)(I2C_MASTERCODE_MAX >= (pDeviceInfo->masterCode)));
        /* Check if the master code does not fall below the minimum value */
        /* #Violation: i2c_hal_c_REF_3 */
        Assert((boolean)(I2C_MASTERCODE_MIN <= (pDeviceInfo->masterCode)));
    }
#endif
    
    /* get FIFO enable status */
    fifoEnable = I2c_Std_GetFifoEnableState(pI2c);

    /* wait for flag to be set and get timeout status */
    timeOutStatus = I2c_Hal_WaitFlagClear(pI2c, I2C_SR2_BUSY, pDeviceInfo->timeOut);

    /* The timeout event does not occur */
    if(FALSE == timeOutStatus)
    {
        /* FIFO is enabled */
        if(TRUE == fifoEnable)
        {
            /* configure transmit length */
            I2c_Std_SetTransmitTotalLength(pI2c, pDeviceInfo->dataSize);
        }

        /* High Speed Mode is enabled */
        /* Get High Speed Mode enable information */
        if(0U != I2c_Std_GetHsCcr(pI2c))
        {
            /* Set High Speed Start */
            I2c_Std_SetHSStart(pI2c, TRUE);

            /* wait for flag to be set and get timeout status */
            timeOutStatus = I2c_Hal_WaitFlagSet(pI2c, I2C_SR1_SB, pDeviceInfo->timeOut);

            /* The timeout event does not occur */
            if(FALSE == timeOutStatus)
            {
                /* Note: There is a time limit for transmit high speed master code. In standard mode (100kbit/s), after writing
                   MHS_START, the master code must be written to the DR register within 3 us; in fast mode (400kbit/s), the
                   master code must be written to the DR register within 1 us */
                /* Transmit High Speed Master Code */
                I2c_Std_WriteDr(pI2c, pDeviceInfo->masterCode);

                /* wait for flag to be set and get timeout status */
                timeOutStatus = I2c_Hal_WaitFlagSet(pI2c, I2C_SR1_AF, pDeviceInfo->timeOut);
                /* Clear flag */
                I2c_Hal_ClearFlag(pI2c, I2C_SR1_AF);

                /* The timeout event does not occur */
                if(FALSE == timeOutStatus)
                {
                    /* Repeatedly set High Speed Start condition */
                    I2c_Std_SetHSStart(pI2c, TRUE);
                }
            }
        }
        /* High Speed Mode is not enabled */
        else
        {
            /* send start condition */
            I2c_Std_GenerateStart(pI2c, 1U);
        }

        /* wait for flag to be set and get timeout status */
        timeOutStatus = I2c_Hal_WaitEventSet(pI2c, I2C_EV5_MASTER_MODE_SELECT, pDeviceInfo->timeOut);

        /* The timeout event does not occur */
        if(FALSE == timeOutStatus)
        {
            transmitData.flag = I2C_EV6_MASTER_TRANSMITTER_MODE_SELECTED;
            transmitData.direction = I2C_DIRECTION_TRANSMIT;
            transmitData.timeOut = pDeviceInfo->timeOut;
            /* Send device address and get timeout status */
            timeOutStatus = I2c_Hal_Transmit7bitAddress(pI2c, pDeviceInfo, &transmitData);

            /* The timeout event does not occur */
            if(FALSE == timeOutStatus)
            {
                transmitData.flag = I2C_EV8_MASTER_DATA_TRANSMITTING;
                transmitData.pData = pDeviceInfo->pData;
                transmitData.dataSize = pDeviceInfo->dataSize;
                /* send data and get timeout status */
                timeOutStatus = I2c_Hal_WriteData(pI2c, &transmitData);

                /* The timeout event does not occur */
                if(FALSE == timeOutStatus)
                {
                    /* wait for flag to be set and get timeout status */
                    timeOutStatus = I2c_Hal_WaitEventSet(pI2c, I2C_EV8_2_MASTER_DATA_TRANSMITTED, pDeviceInfo->timeOut);
                }
            }
        }

        /* Send STOP condition */
        I2c_Std_GenerateStop(pI2c, 1U);

        /* Reset FIFO */
        I2c_Std_FifoReset(pI2c);

    }
    return (FALSE == timeOutStatus) ? I2C_STATUS_OK : I2C_STATUS_TIMEOUT;
}

/* #Violation: i2c_hal_c_REF_4 */
I2c_Status I2c_Hal_MasterRead(I2C_MODULE *const pI2c, const I2C_DeviceInfo *const pDeviceInfo)
{
    boolean timeOutStatus;
    boolean fifoEnable;
    I2C_TransmitData transmitData;

#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the module pointer is a valid pointer */
    /* Check I2C base address */
    /* #Violation: i2c_hal_c_REF_1 */
    /* #Violation: i2c_hal_c_REF_2 */
    Assert((boolean)(CHECK_I2C_BASE(pI2c)));
    /* Check if the device information pointer is null pointer */
    /* #Violation: i2c_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pDeviceInfo));
    /* Check if the data buffer pointer is null pointer */
    /* #Violation: i2c_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != (pDeviceInfo->pData)));
    /* High Speed Mode is enabled */
    /* get High Speed Mode enable status */
    if(0U != I2c_Std_GetHsCcr(pI2c))
    {
        /* Check if the master code does not exceed the maximum value */
        /* #Violation: i2c_hal_c_REF_3 */
        Assert((boolean)(I2C_MASTERCODE_MAX >= (pDeviceInfo->masterCode)));
        /* Check if the master code does not fall below the minimum value */
        /* #Violation: i2c_hal_c_REF_3 */
        Assert((boolean)(I2C_MASTERCODE_MIN <= (pDeviceInfo->masterCode)));
    }
#endif
    /* get FIFO enable status */
    fifoEnable = I2c_Std_GetFifoEnableState(pI2c);

    /* wait for flag to be set and get timeout status */
    timeOutStatus = I2c_Hal_WaitFlagClear(pI2c, I2C_SR2_BUSY, pDeviceInfo->timeOut);

    /* The timeout event does not occur */
    if(FALSE == timeOutStatus)
    {
        /* Enable the auto-acknowledge function */
        I2c_Std_ConfigAck(pI2c, 1U);

        /* FIFO is enabled */
        if(TRUE == fifoEnable)
        {
            /* configure transmit length */
            I2c_Std_SetTransmitTotalLength(pI2c, pDeviceInfo->dataSize);
        }

        /* High Speed Mode is enabled */
        /* Get High Speed Mode enable information */
        if(0U != I2c_Std_GetHsCcr(pI2c))
        {
            /* Send High Speed mode start condition*/
            I2c_Std_SetHSStart(pI2c, TRUE);

            /* wait for flag to be set and get timeout status */
            timeOutStatus = I2c_Hal_WaitFlagSet(pI2c, I2C_SR1_SB, pDeviceInfo->timeOut);

            /* The timeout event does not occur */
            if(FALSE == timeOutStatus)
            {
                /* Note: There is a time limit for transmit high speed master code. In standard mode (100kbit/s), after writing
                   MHS_START, the master code must be written to the DR register within 3 us; in fast mode (400kbit/s), the
                   master code must be written to the DR register within 1 us */
                /* Transmit High Speed Master Code */
                I2c_Std_WriteDr(pI2c, pDeviceInfo->masterCode);

                /* wait for flag to be set and get timeout status */
                timeOutStatus = I2c_Hal_WaitFlagSet(pI2c, I2C_SR1_AF, pDeviceInfo->timeOut);

                /* Clear flag */
                I2c_Hal_ClearFlag(pI2c, I2C_SR1_AF);

                /* The timeout event does not occur */
                if(FALSE == timeOutStatus)
                {
                    /* Repeatedly send High Speed Start condition */
                    I2c_Std_SetHSStart(pI2c, TRUE);
                }
            }
        }
        /* High Speed Mode is not enabled */
        else
        {
            /* Send Start condition */
            I2c_Std_GenerateStart(pI2c, 1U);
        }

        /* wait for flag to be set and get timeout status */
        timeOutStatus = I2c_Hal_WaitEventSet(pI2c, I2C_EV5_MASTER_MODE_SELECT, pDeviceInfo->timeOut);

        /* The timeout event does not occur */
        if(FALSE == timeOutStatus)
        {
            /* 7Bit Address is EV6, 10Bit Address is EV9 + EV6 + EV5 + EV6 */
            transmitData.flag = I2C_EV6_MASTER_RECEIVER_MODE_SELECTED;
            transmitData.direction = I2C_DIRECTION_RECEIVE;
            transmitData.timeOut = pDeviceInfo->timeOut;
            transmitData.pData = pDeviceInfo->pData;
            transmitData.dataSize = pDeviceInfo->dataSize;

            /* Send device address and get timeout status */
            timeOutStatus = I2c_Hal_Transmit7bitAddress(pI2c, pDeviceInfo, &transmitData);
        }

        /* The timeout event does not occur */
        if(FALSE == timeOutStatus)
        {
            /* Read data and get timeout status */
            timeOutStatus = I2c_Hal_ReadData(pI2c, &transmitData);
        }
    }

    return (FALSE == timeOutStatus) ? I2C_STATUS_OK : I2C_STATUS_TIMEOUT;
}

/* #Violation: i2c_hal_c_REF_4 */
I2c_Status I2c_Hal_MasterWriteDma(I2C_MODULE *const pI2c, const I2C_DeviceInfo *const pDeviceInfo)
{
    boolean timeOutStatus;
    I2C_TransmitData transmitData;

#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the module pointer is a valid pointer */
    /* Check I2C base address */
    /* #Violation: i2c_hal_c_REF_1 */
    /* #Violation: i2c_hal_c_REF_2 */
    Assert((boolean)(CHECK_I2C_BASE(pI2c)));
    /* Check if the device information pointer is null pointer */
    /* #Violation: i2c_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pDeviceInfo));
    /* High Speed Mode is enabled */
    /* get High Speed Mode enable status */
    if(0U != I2c_Std_GetHsCcr(pI2c))
    {
        /* Check if the master code does not exceed the maximum value */
        /* #Violation: i2c_hal_c_REF_3 */
        Assert((boolean)(I2C_MASTERCODE_MAX >= (pDeviceInfo->masterCode)));
        /* Check if the master code does not fall below the minimum value */
        /* #Violation: i2c_hal_c_REF_3 */
        Assert((boolean)(I2C_MASTERCODE_MIN <= (pDeviceInfo->masterCode)));
    }
#endif

    /* Wait until BUSY flag is reset */
    timeOutStatus = I2c_Hal_WaitFlagClear(pI2c, I2C_SR2_BUSY, pDeviceInfo->timeOut);

    /* dma function is enabled */
    /* get dma function enable status */
    if(0U == I2c_Std_GetDmaEnableState(pI2c))
    {
        /* Enable DMA request */
        I2c_Std_SetDma(pI2c, TRUE);
    }

    /* The timeout event does not occur */
    if(FALSE == timeOutStatus)
    {
        /* configure transmit length */
        I2c_Std_SetTransmitTotalLength(pI2c, pDeviceInfo->dataSize);

        /* High Speed Mode is enabled */
        /* Get High Speed Mode enable information */
        if(0U != I2c_Std_GetHsCcr(pI2c))
        {
            /* Send High Speed mode start condition*/
            I2c_Std_SetHSStart(pI2c, TRUE);

            /* wait for flag to be set and get timeout status */
            timeOutStatus = I2c_Hal_WaitFlagSet(pI2c, I2C_SR1_SB, pDeviceInfo->timeOut);

            /* The timeout event does not occur */
            if(FALSE == timeOutStatus)
            {
                /* Note: There is a time limit for transmit high speed master code. In standard mode (100kbit/s), after writing
                   MHS_START, the master code must be written to the DR register within 3 us; in fast mode (400kbit/s), the
                   master code must be written to the DR register within 1 us */
                /* Transmit High Speed Master Code */
                I2c_Std_WriteDr(pI2c, pDeviceInfo->masterCode);

                /* wait for flag to be set and get timeout status */
                timeOutStatus = I2c_Hal_WaitFlagSet(pI2c, I2C_SR1_AF, pDeviceInfo->timeOut);
                /* Clear flag */
                I2c_Hal_ClearFlag(pI2c, I2C_SR1_AF);

                /* The timeout event does not occur */
                if(FALSE == timeOutStatus)
                {
                    /* Repeatedly send High Speed Start condition */
                    I2c_Std_SetHSStart(pI2c, TRUE);
                }
            }
        }
        /* High Speed Mode is not enabled */
        else
        {
            /* Send Start condition */
            I2c_Std_GenerateStart(pI2c, 1U);
        }

        /* wait for flag to be set and get timeout status */
        timeOutStatus = I2c_Hal_WaitEventSet(pI2c, I2C_EV5_MASTER_MODE_SELECT, pDeviceInfo->timeOut);

        /* The timeout event does not occur */
        if(FALSE == timeOutStatus)
        {
            /* Transmit Address:7Bit Address is EV6, 10Bit Address is EV9 + EV6 */
            transmitData.flag = I2C_EV6_MASTER_TRANSMITTER_MODE_SELECTED;
            transmitData.direction = I2C_DIRECTION_TRANSMIT;
            transmitData.timeOut = pDeviceInfo->timeOut;
            /* Send device address and get timeout status */
            timeOutStatus = I2c_Hal_Transmit7bitAddress(pI2c, pDeviceInfo, &transmitData);
        }
    }

    return (FALSE == timeOutStatus) ? I2C_STATUS_OK : I2C_STATUS_TIMEOUT;
}

/* #Violation: i2c_hal_c_REF_4 */
I2c_Status I2c_Hal_MasterReadDma(I2C_MODULE *const pI2c, const I2C_DeviceInfo *const pDeviceInfo)
{
    boolean timeOutStatus;
    I2C_TransmitData transmitData;

#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the module pointer is a valid pointer */
    /* Check I2C base address */
    /* #Violation: i2c_hal_c_REF_1 */
    /* #Violation: i2c_hal_c_REF_2 */
    Assert((boolean)(CHECK_I2C_BASE(pI2c)));
    /* Check if the device information pointer is null pointer */
    /* #Violation: i2c_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pDeviceInfo));
    /* High Speed Mode is enabled */
    /* get High Speed Mode enable status */
    if(0U != I2c_Std_GetHsCcr(pI2c))
    {
        /* Check if the master code does not exceed the maximum value */
        /* #Violation: i2c_hal_c_REF_3 */
        Assert((boolean)(I2C_MASTERCODE_MAX >= (pDeviceInfo->masterCode)));
        /* Check if the master code does not fall below the minimum value */
        /* #Violation: i2c_hal_c_REF_3 */
        Assert((boolean)(I2C_MASTERCODE_MIN <= (pDeviceInfo->masterCode)));
    }
#endif

    /* wait for flag to be set and get timeout status */
    timeOutStatus = I2c_Hal_WaitFlagClear(pI2c, I2C_SR2_BUSY, pDeviceInfo->timeOut);

    /* The timeout event does not occur */
    if(FALSE == timeOutStatus)
    {
        /* Set transfer length */
        I2c_Std_SetTransmitTotalLength(pI2c, pDeviceInfo->dataSize);

        /* dma function is enabled */
        /* get dma function enable status */
        if(0U == I2c_Std_GetDmaEnableState(pI2c))
        {
            /* Enable DMA request */
            I2c_Std_SetDma(pI2c, TRUE);
        }

        /* Enable the auto-acknowledge function */
        I2c_Std_ConfigAck(pI2c, 1U);

        /* High Speed Mode is enabled */
        /* Get High Speed Mode enable information */
        if(0U != I2c_Std_GetHsCcr(pI2c))
        {
            /* Set High Speed Start */
            I2c_Std_SetHSStart(pI2c, TRUE);

            /* wait for flag to be set and get timeout status */
            timeOutStatus = I2c_Hal_WaitFlagSet(pI2c, I2C_SR1_SB, pDeviceInfo->timeOut);

            /* The timeout event does not occur */
            if(FALSE == timeOutStatus)
            {
                /* Note: There is a time limit for transmit high speed master code. In standard mode (100kbit/s), after writing
                   MHS_START, the master code must be written to the DR register within 3 us; in fast mode (400kbit/s), the
                   master code must be written to the DR register within 1 us */
                /* Transmit High Speed Master Code */
                I2c_Std_WriteDr(pI2c, pDeviceInfo->masterCode);

                /* wait for flag to be set and get timeout status */
                timeOutStatus = I2c_Hal_WaitFlagSet(pI2c, I2C_SR1_AF, pDeviceInfo->timeOut);
                /* Clear flag */
                I2c_Hal_ClearFlag(pI2c, I2C_SR1_AF);

                if(FALSE == timeOutStatus)
                {
                    /* Repeatedly set High Speed Start condition */
                    I2c_Std_SetHSStart(pI2c, TRUE);
                }
            }
        }
        /* High Speed Mode is not enabled */
        else
        {
            /* send start condition */
            I2c_Std_GenerateStart(pI2c, 1U);
        }

        /* wait for flag to be set and get timeout status */
        timeOutStatus = I2c_Hal_WaitEventSet(pI2c, I2C_EV5_MASTER_MODE_SELECT, pDeviceInfo->timeOut);

        if(FALSE == timeOutStatus)
        {
            /* 7Bit Address is EV6, 10Bit Address is EV9 + EV6 + EV5 + EV6 */
            transmitData.flag = I2C_EV6_MASTER_RECEIVER_MODE_SELECTED;
            transmitData.direction = I2C_DIRECTION_RECEIVE;
            transmitData.timeOut = pDeviceInfo->timeOut;
            /* Send device address and get timeout status */
            timeOutStatus = I2c_Hal_Transmit7bitAddress(pI2c, pDeviceInfo, &transmitData);
        }
    }

    return (FALSE == timeOutStatus) ? I2C_STATUS_OK : I2C_STATUS_TIMEOUT;
}

/* #Violation: i2c_hal_c_REF_4 */
I2c_Status I2c_Hal_MasterStopDma(I2C_MODULE *const pI2c, const I2C_DeviceInfo *const pDeviceInfo)
{
    boolean timeOutStatus;
    timeOutStatus = FALSE;

#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the module pointer is a valid pointer */
    /* Check I2C base address */
    /* #Violation: i2c_hal_c_REF_1 */
    /* #Violation: i2c_hal_c_REF_2 */
    Assert((boolean)(CHECK_I2C_BASE(pI2c)));
    /* Check if the pointer is null pointer */
    /* #Violation: i2c_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pDeviceInfo));
#endif

    /* flag is set */
    /* get flag set status */    
    if(TRUE == I2c_Std_CheckFlag(pI2c, I2C_SR2_TRA, TRUE))
    {
        /* wait for flag to be set and get timeout status */
        timeOutStatus = I2c_Hal_WaitFlagSet(pI2c, I2C_SR1_BTF, pDeviceInfo->timeOut);
    }

    /* Send STOP condition */
    I2c_Std_GenerateStop(pI2c, 1U);

    /* Flush FIFO */
    I2c_Std_FifoReset(pI2c);

    /* Disable DMA request */
    I2c_Std_SetDma(pI2c, FALSE);

    return (FALSE == timeOutStatus) ? I2C_STATUS_OK : I2C_STATUS_TIMEOUT;
}

/* #Violation: i2c_hal_c_REF_4 */
uint32 I2c_Hal_GetFlag(const I2C_MODULE *const pI2c)
{
    uint32 RetStatus;

#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the module pointer is a valid pointer */
    /* Check I2C base address */
    /* #Violation: i2c_hal_c_REF_1 */
    /* #Violation: i2c_hal_c_REF_2 */
    Assert((boolean)(CHECK_I2C_BASE(pI2c)));
#endif

    /* Get Sr1 status, (Bit0 ~ 12) */
    RetStatus = I2c_Std_GetSr1(pI2c);
    RetStatus = RetStatus & (I2C_SR1_BTF | I2C_SR1_ARLO | I2C_SR1_AF | I2C_SR1_OVR);
    /* Get Sr3 status, (Bit13 ~ 16) */
    RetStatus |= (I2c_Std_GetSr3(pI2c)) << 2U;
    /* Get Sr4 status, (Bit17 ~ 20) */
    RetStatus |= I2c_Std_GetSr4(pI2c) << 17U;

    return RetStatus;
}

/* #Violation: i2c_hal_c_REF_7 */
/* #Violation: i2c_hal_c_REF_9 */
void I2c_Hal_ClearFlag(I2C_MODULE *const pI2c, uint32 flag)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the module pointer is a valid pointer */
    /* Check I2C base address */
    /* #Violation: i2c_hal_c_REF_1 */
    /* #Violation: i2c_hal_c_REF_2 */
    Assert((boolean)(CHECK_I2C_BASE(pI2c)));
    /* Check if the flag is within a valid range (I2C_SR_CLEARMASK) */
    /* #Violation: i2c_hal_c_REF_3 */
    Assert((boolean)(0U == ((~I2C_SR_CLEARMASK) & flag)));
#endif
    /* clear flag */
    I2c_Std_ClearFlag(pI2c, flag);
}

#define I2C_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: i2c_hal_c_REF_11 */
#include "I2c_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
