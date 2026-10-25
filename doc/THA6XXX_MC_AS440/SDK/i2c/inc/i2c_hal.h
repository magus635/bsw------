/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    I2c_Hal.h
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of interfaces.
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#i2c_hal_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers
*
*#i2c_hal_h_REF_2:MISRAC2012-Dir-4.8;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#i2c_hal_h_REF_3:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity;
*/
#ifndef I2C_HAL_H_
#define I2C_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "i2c_register.h"
#include "compilertypes.h"
#include "tha6_cfg.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* ^I2C_SPEED_MODE^ I2C speed mode */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_SPEED_MODE_STANDARD ((uint32)100000U)   /* I2C standard speed 100Kbps */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_SPEED_MODE_FAST ((uint32)400000U)       /* I2C fast speed 400Kbps */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_SPEED_MODE_FAST_PLUS ((uint32)1000000U) /* I2C fast+ speed 1Mbps */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_SPEED_MODE_HIGH ((uint32)3400000U)      /* I2C high speed 3.4Mbps */

/* ^I2C_STATUS_MASK^ I2c_Status Mask: SR1\SR2\SR3\SR4 */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_SR1_MASK (0x00001FFFU) /* I2C SR1 mask value */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_SR2_MASK (0x0000FF97U) /* I2C SR2 mask value */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_SR3_MASK (0x00007800U) /* I2C SR3 mask value */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_SR4_MASK (0x00000009U) /* I2C SR4 mask value */

/* #Violation: i2c_hal_h_REF_1 */
#define I2C_SR1_CLEARMASK (0x00001F20U) /* I2C SR1 clear mask value */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_SR3_CLEARMASK (0x00004800U) /* I2C SR3 clear mask value */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_SR4_CLEARMASK (0x00000009U) /* I2C SR4 clear mask value */

/* ^I2C_STATUS_FLAG^ I2c_Status Flag: SR1\SR2\SR3\SR4 */
#define I2C_SR1_SB (0x00000001U)     /* Start bit (Master mode) */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_SR1_ADDR (0x00000002U)   /* Address sent (master mode) or matched (slave mode) */
#define I2C_SR1_BTF (0x00000004U)    /* Byte transfer finished */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_SR1_ADD10 (0x00000008U)  /* 10-bit header sent (Master mode) */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_SR1_STOPF (0x00000010U)  /* Stop detection (slave mode) */
#define I2C_SR1_BREQ (0x00000020U)   /* FIFO burst transfer request */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_SR1_RXNE (0x00000040U)   /* Data register not empty (receivers) */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_SR1_TXE (0x00000080U)    /* Data register empty transmitters */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_SR1_BERR (0x00000100U)   /* Bus error */
#define I2C_SR1_ARLO (0x00000200U)   /* Arbitration lost (master mode) */
#define I2C_SR1_AF (0x00000400U)     /* Acknowledge failure */
#define I2C_SR1_OVR (0x00000800U)    /* Over-run or Under-run */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_SR1_PECERR (0x00001000U) /* PEC Error in reception */

/* #Violation: i2c_hal_h_REF_1 */
#define I2C_SR2_MSL (0x00010000U)     /* Master/slave */
#define I2C_SR2_BUSY (0x00020000U)    /* Bus busy */
#define I2C_SR2_TRA (0x00040000U)     /* Transmitter/Receiver */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_SR2_GENCALL (0x00100000U) /* General call address */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_SR2_DUALF (0x00800000U)   /* Dual flag(Slave mode) */

/* #Violation: i2c_hal_h_REF_1 */
#define I2C_SR3_SHCM (0x01000000U)     /* Matching high speed mode on slave mode */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_SR3_SHS (0x02000000U)      /* High speed flag on slave mode */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_SR3_MHS (0x04000000U)      /* High speed flag on master mode*/
#define I2C_SR3_FIFOSREQ (0x08000000U) /* FIFO single request */

/* #Violation: i2c_hal_h_REF_1 */
#define I2C_SR4_RFUFL (0x10000000U) /* RX FIFO underflow */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_SR4_TFOFL (0x80000000U) /* TX FIFO over flow flag */

/* ^I2C_DUTYCYCLE^ I2C duty cycle in fast mode */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_DUTYCYCLE_2 (0x00000000U)    /* I2C fast mode Tlow/Thigh = 2 */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_DUTYCYCLE_16_9 (0x00000001U) /* I2C fast mode Tlow/Thigh = 16/9 */

/* ^I2C_FIFO_TX_LENGTH_MASK^ The mask value of total transmit bytes length  */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_FIFO_TX_LENGTH_MASK (0x00003FFFU) /* The mask value of total transmit bytes length */

/* ^I2C_FIFO_RX_WATERMARK^ The RX FIFO water mark value */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_FIFO_RX_WATERMARK_4 (0x00000004U) /* The RX FIFO water mark >=4 will trigger */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_FIFO_RX_WATERMARK_5 (0x00000005U) /* The RX FIFO water mark >=5 will trigger */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_FIFO_RX_WATERMARK_6 (0x00000006U) /* The RX FIFO water mark >=6 will trigger */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_FIFO_RX_WATERMARK_7 (0x00000007U) /* The RX FIFO water mark >=7 will trigger */

/* ^I2C_FIFO_TX_WATERMARK^ The TX FIFO water mark value */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_FIFO_TX_WATERMARK_1 (0x00000001U) /* The TX FIFO water mark value <=1 will trigger */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_FIFO_TX_WATERMARK_2 (0x00000002U) /* The TX FIFO water mark value <=2 will trigger */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_FIFO_TX_WATERMARK_3 (0x00000003U) /* The TX FIFO water mark value <=3 will trigger */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_FIFO_TX_WATERMARK_4 (0x00000004U) /* The TX FIFO water mark value <=4 will trigger */

/* ^I2C_FIFO_ALIGN^ I2C FIFO align mode */
#define I2C_FIFO_ALIGNBYTE_1 (0x00000000U) /* FIFO align is 1 byte */
#define I2C_FIFO_ALIGNBYTE_2 (0x00000001U) /* FIFO align is 2 byte, for the FIFO + DMA mode, THA6206 not support configuring the FIFO alignment as I2C_FIFO_ALIGNBYTE_2 */
#define I2C_FIFO_ALIGNBYTE_4 (0x00000002U) /* FIFO align is 4 byte */

/* ^I2C_FIFO_BURST_SIZE^ I2C burst size */
#define I2C_FIFO_BURST_SIZE_1 (0x00000000U) /* FIFO burst transmit is 1 byte */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_FIFO_BURST_SIZE_4 (0x00000001U) /* FIFO burst transmit is 4 byte */

/* ^I2C_EVENT^ I2C events grouped in order of communication */
#define I2C_EV5_MASTER_MODE_SELECT (0x00030001U)               /* BUSY, MSL and SB flag */
#define I2C_EV6_MASTER_TRANSMITTER_MODE_SELECTED (0x00070082U) /* TRA, BUSY, MSL, ADDR, TXE flags */
#define I2C_EV6_MASTER_RECEIVER_MODE_SELECTED (0x00030002U)    /* BUSY, MSL and ADDR flags */
#define I2C_EV7_MASTER_DATA_RECEIVED (0x00000040U)             /* RXNE flags */
#define I2C_EV8_MASTER_DATA_TRANSMITTING (0x00070080U)         /* TRA, BUSY, MSL, TXE flags */
#define I2C_EV8_2_MASTER_DATA_TRANSMITTED (0x00070084U)        /* TRA, BUSY, MSL, TXE and BTF flags */
/* #Violation: i2c_hal_h_REF_1 */
#define I2C_EV9_MASTER_MODE_ADDRESS10 (0x00030008U)            /* BUSY, MSL and ADD10 flags */

/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* Enumeration for the I2C function status  */
typedef enum
{
    I2C_STATUS_OK = 0U,     /* Status available*/
    I2C_STATUS_ERROR,       /* Status errors */
    I2C_STATUS_BUSY,        /* Status busy */
    I2C_STATUS_TIMEOUT,     /* operation timeout */
    I2C_STATUS_PARAM_ERROR  /* Illegal parameter */
} I2c_Status;

/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* Structure for I2C Configuration definition */
/* #Violation: i2c_hal_h_REF_2 */
/* #Violation: i2c_hal_h_REF_3 */
typedef struct
{
    boolean enFifo;         /* Specifies the FIFO function switch.TRUE is enable, FALSE is disable. */
    uint32 fifoRxWaterMark; /* Specifies the RX-FIFO water mark, can be a value of I2C_FIFO_RX_WATERMARK */
    uint32 fifoTxWaterMark; /* Specifies the TX-FIFO water mark, can be a value of I2C_FIFO_TX_WATERMARK */
    uint32 fifoAlignMode;   /* Specifies the FIFO align mode, can be a value of I2C_FIFO_ALIGN */
    uint32 busSpeed;        /* Specifies the bus frequency, can be a value of I2C_SPEED_MODE */
    uint32 dutyCycle;       /* Specifies the I2C fast mode duty cycle, can be a value of I2C_DUTYCYCLE */
    uint32 burstSize;       /* Specifies the burst size used with DMA, can be a value of I2C_FIFO_BURST_SIZE */
} I2C_InitParameter;

/* Structure for I2C transmit device information */
/* #Violation: i2c_hal_h_REF_3 */
typedef struct
{
    uint16 devAddress;       /* device address, SDK only support 7-bit address. When assigning a value to the device address, 
                                it is necessary to shift the address left by one bit to ensure that the last bit is the R/W bit */
    uint8 *pData;            /* Pointer to a data address */
    uint32 dataSize;         /* The size of data to be transmitted */
    uint32 timeOut;          /* Waiting timeout */
    uint8 masterCode;        /* High speed master code */
} I2C_DeviceInfo;

/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
#define I2C_START_SEC_CODE_ASIL_D_GLOBAL
#include "I2c_MemMap.h"

/**********************************************************************************************************************
 * Function:     I2c_Hal_Init
 * Description:  The main function of this interface is to initialize the I2C module. The initialization parameters include: whether to enable the FIFO, 
 *               the threshold value of the FIFO, the alignment mode of the FIFO, the operating speed of the I2C module, the duty cycle, and the burst size.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different I2C modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pI2c: Pointer to the I2C module.
 *               pInitParameter: The I2C initialize parameter, see I2C_InitParameter.
 * Inout:        None
 * Output:       None
 * Return:       I2c_Status: detail see I2c_Status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/01/17    01107     Create
 *  2024/03/28    01208     Modify
 *********************************************************************************************************************/
extern I2c_Status I2c_Hal_Init(I2C_MODULE *const pI2c, const I2C_InitParameter *const pInitParameter);

/**********************************************************************************************************************
 * Function:     I2c_Hal_DeInit
 * Description:  The main function of this interface is to reset the I2C module. Before resetting the I2C module, 
 *               it first checks whether the I2C module is in a busy state. If it is busy, the interface will exit immediately and return RCC_ERRORFLAG_TIMEOUT. 
 *               Otherwise, it will perform the reset operation on the I2C module.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 * Inout:        None
 * Output:       None
 * Return:       I2c_Status: detail see I2c_Status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/01/17    01107     Create
 *********************************************************************************************************************/
extern I2c_Status I2c_Hal_DeInit(const I2C_MODULE *const pI2c);

/**********************************************************************************************************************
 * Function:     I2c_Hal_MasterWrite
 * Description:  The main function of this function is to write data to the I2C slave device. The required parameters include: the device address of the slave, 
 *               the address of the data to be sent, the data length, timeout parameters, and the master code.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When writing data to different I2C modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pI2c: Pointer to the I2C module.
 *               pDeviceInfo: details see structure I2C_DeviceInfo.
 * Inout:        None
 * Output:       None
 * Return:       I2c_Status: details see I2c_Status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/22    01107      Create
 *  2024/03/28    01208      Modify
 *********************************************************************************************************************/
extern I2c_Status I2c_Hal_MasterWrite(I2C_MODULE *const pI2c, const I2C_DeviceInfo *const pDeviceInfo);

/**********************************************************************************************************************
 * Function:     I2c_Hal_MasterRead
 * Description:  I2C master mode read synchronously
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When reading data from different I2C modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pI2c: Pointer to the I2C module.
 *               pDeviceInfo: details see structure I2C_DeviceInfo.
 * Inout:        None
 * Output:       None
 * Return:       I2c_Status: details see I2c_Status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/22    01107      Create
 *  2024/03/28    01208      Modify
 *********************************************************************************************************************/
extern I2c_Status I2c_Hal_MasterRead(I2C_MODULE *const pI2c, const I2C_DeviceInfo *const pDeviceInfo);

/**********************************************************************************************************************
 * Function:     I2c_Hal_MasterWriteDma
 * Description:  I2C master mode write by using DMA+FIFO
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When writing data to different I2C modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pI2c: Pointer to the I2C module.
 *               pDeviceInfo: details see structure I2C_DeviceInfo.
 * Inout:        None
 * Output:       None
 * Return:       I2c_Status: details see I2c_Status
 * Others:       FIFO must be enabled during initialization phase
 * History:
 *  Date          Author    Modified
 *  2024/03/22    01107      Create
 *  2024/03/28    01208      Modify
 *********************************************************************************************************************/
extern I2c_Status I2c_Hal_MasterWriteDma(I2C_MODULE *const pI2c, const I2C_DeviceInfo *const pDeviceInfo);

/**********************************************************************************************************************
 * Function:     I2c_Hal_MasterReadDma
 * Description:  I2C master mode read by using DMA+FIFO
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When reading data from different I2C modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pI2c: Pointer to the I2C module.
 *               pDeviceInfo: details see structure I2C_DeviceInfo.
 * Inout:        None
 * Output:       None
 * Return:       I2c_Status: details see I2c_Status
 * Others:       FIFO must be enabled during initialization phase
 * History:
 *  Date          Author    Modified
 *  2024/03/22    01107      Create
 *  2024/03/28    01208      Modify
 *********************************************************************************************************************/
extern I2c_Status I2c_Hal_MasterReadDma(I2C_MODULE *const pI2c, const I2C_DeviceInfo *const pDeviceInfo);

/**********************************************************************************************************************
 * Function:     I2c_Hal_MasterStopDma
 * Description:  I2C master mode stop communication of using DMA+FIFO
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When controlling different I2C modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pI2c: Pointer to the I2C module.
 *               pDeviceInfo: details see structure I2C_DeviceInfo.
 * Inout:        None
 * Output:       None
 * Return:       I2c_Status: details see I2c_Status
 * Others:       Only used in DMA+FIFO scenarios.
 * History:
 *  Date          Author    Modified
 *  2024/03/22    01107      Create
 *  2024/03/28    01208      Modify
 *********************************************************************************************************************/
extern I2c_Status I2c_Hal_MasterStopDma(I2C_MODULE *const pI2c, const I2C_DeviceInfo *const pDeviceInfo);

/**********************************************************************************************************************
 * Function:     I2c_Hal_GetFlag
 * Description:  Get I2C flag
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 * Inout:        None
 * Output:       None
 * Return:       uint32: Get the status bit of SR1/3/4.
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/01/17    01107     Create
 *********************************************************************************************************************/
extern uint32 I2c_Hal_GetFlag(const I2C_MODULE *const pI2c);

/**********************************************************************************************************************
 * Function:     I2c_Hal_ClearFlag
 * Description:  clear flag.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 *               flag: Specifies the bit of SR1\4 to clear.
 *               This parameter can be one of the following values:
 *                I2C_SR1_BREQ
 *                I2C_SR1_BERR
 *                I2C_SR1_ARLO
 *                I2C_SR1_AF
 *                I2C_SR1_OVR
 *                I2C_SR1_PECERR
 *                I2C_SR4_RFUFL
 *                I2C_SR4_TFOFL
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/01/17    01107     Create
 *********************************************************************************************************************/
extern void I2c_Hal_ClearFlag(I2C_MODULE *const pI2c, uint32 flag);

#define I2C_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "I2c_MemMap.h"

#endif /* I2C_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
