/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    msc_hal.h
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of interfaces.
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#msc_hal_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification:Reserved macros for upper layer application.
*
*#msc_hal_h_REF_2:MISRAC2012-Dir-4.8;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#msc_hal_h_REF_3:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity;
*/

#ifndef MSC_HAL_H_
#define MSC_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "msc_std.h"
#include "Platform_Types.h"
#include "rcc_hal.h"
#include "tha6_cfg.h"
#include "compilertypes.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* ^MSC_INTR_ENABLE_FLAG^ Interrupt enable control mask */
/* #Violation: msc_hal_h_REF_1 */
#define MSC_INTR_ENABLE_FLAG_DF (0x8U) /* Enable downstream channel data frame interrupt */
/* #Violation: msc_hal_h_REF_1 */
#define MSC_INTR_ENABLE_FLAG_CF (0x80U) /* Enable downstream channel command frame interrupt */
/* #Violation: msc_hal_h_REF_1 */
#define MSC_INTR_ENABLE_FLAG_TF (0x800U) /* Enable downstream channel time frame interrupt */
/* #Violation: msc_hal_h_REF_1 */
#define MSC_INTR_ENABLE_FLAG_RX (0x40000U) /* Enable upstream channel receive data interrupt */
/* #Violation: msc_hal_h_REF_1 */
#define MSC_INTR_ENABLE_FLAG_ALL (0x40888U) /* Enable all interrupt */
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                              Global Type Definitions
 *********************************************************************************************************************/
/* Redefine interrupt configuration structure */
typedef Msc_InterruptConfig Msc_IntrConfig;
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* MSC downstream transmit status flag */
typedef enum
{
    MSC_TRANSMITSTSFLAG_DATP = 0U, /* Specifies the data pending status flag */
    MSC_TRANSMITSTSFLAG_COMP,      /* Specifies the command pending status flag */
    MSC_TRANSMITSTSFLAG_ENDIS      /* Specifies the downstream disabled status flag */
} Msc_TransmitStsFlag;

/* MSC channel interrupt status flag */
typedef enum
{
    MSC_INTRSTSFLAG_DF = 0U, /* Specifies the data frame interrupt status flag */
    MSC_INTRSTSFLAG_CF,      /* Specifies the command frame interrupt status flag */
    MSC_INTRSTSFLAG_TF,      /* Specifies the time frame interrupt status flag */
    MSC_INTRSTSFLAG_RX,      /* Specifies the receive data interrupt status flag */
    MSC_INTRSTSFLAG_TO       /* Specifies the upstream timeout interrupt status flag */
} Msc_IntrStsFlag;

/* MSC status  */
typedef enum
{
    MSC_STATUS_RESET = 0U, /* Status flag is reset */
    MSC_STATUS_SET         /* Status flag is set */
} Msc_Status;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* Upstream timeout configuration structure */
/* #Violation: msc_hal_h_REF_3 */
typedef struct
{
    Msc_TimeoutValue timeoutValue;         /* Specifies the upstream timeout value */
    Msc_TimeoutPrescaler timeoutPrescaler; /* Specifies the upstream timeout prescaler */
    Msc_AlIntrNode node;                   /* Specifies the upstream timeout interrupt node */
} Msc_TimeoutConfig;

/* DMA handling configuration structure */
typedef struct
{
    Msc_Dma dmaEn;       /* To enable or disable DMA handling request */
    Msc_Mirror mirrorEn; /* To enable or disable mirror register */
} Msc_DmaConfig;

/* MSC module configuration structure */
/* #Violation: msc_hal_h_REF_2 */
/* #Violation: msc_hal_h_REF_3 */
typedef struct
{
    Msc_ClockConfig clockConfig;           /* Specifies the clock configuration */
    Msc_UpstreamConfig upstreamConfig;     /* Specifies the upstream reception configuration */
    Msc_DownstreamConfig downstreamConfig; /* Specifies the downstream frame transmission configuration */
} Msc_ModuleConfig;
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
#define MSC_START_SEC_CODE_ASIL_D_GLOBAL
#include "Msc_MemMap.h"

/**********************************************************************************************************************
 * Function:     Msc_Hal_DeInitModule
 * Description:  De-initialize the MSC module
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pMsc: Pointer to the MSC module
 * Inout:        None
 * Output:       None
 * Return:       Rcc_ErrorFlag: Error indicating flag
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *********************************************************************************************************************/
extern Rcc_ErrorFlag Msc_Hal_DeInitModule(const MSC_MODULE *const pMsc);

/**********************************************************************************************************************
 * Function:     Msc_Hal_InitModule
 * Description:  Initialize the MSC module
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pMsc: Pointer to the MSC module
 *               pConfig: Specifies the pointer to the MSC module configuration, 
 *                        the value of pConfig->clockConfig.baud must more than MSC_MIN_DOWNSTREAM_BAUDRATE
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       Downstream channel support maximum baud-rate is 50MHz
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *********************************************************************************************************************/
extern boolean Msc_Hal_InitModule(MSC_MODULE *const pMsc, const Msc_ModuleConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Msc_Hal_InitInterrupt
 * Description:  Initialize interrupt mode and node selection
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different MSC modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pMsc: Pointer to the MSC module
 *               pInterruptConfig: Specifies the interrupt configuration pointer
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *********************************************************************************************************************/
extern void Msc_Hal_InitInterrupt(MSC_MODULE *const pMsc, const Msc_IntrConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Msc_Hal_InitDma
 * Description:  Initialize DMA handling interrupt and mirror register selection
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different MSC modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pMsc: Pointer to the MSC module
 *               pConfig: DMA handling configuration
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *********************************************************************************************************************/
extern void Msc_Hal_InitDma(MSC_MODULE *const pMsc, const Msc_DmaConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Msc_Hal_SendCommand
 * Description:  Send downstream command (for THA6206 D version chip, this API can not be used in repetition mode).
 * Sync/Async:   Asynchronous
 * Reentrancy:   Non-Reentrant (When writting command to different MSC modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pMsc: Pointer to the MSC module
 *               command: command to be transmitted up to 32 bits
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *********************************************************************************************************************/
extern void Msc_Hal_SendCommand(MSC_MODULE *const pMsc, uint32 command);

/**********************************************************************************************************************
 * Function:     Msc_Hal_SyncSendCommand
 * Description:  Send downstream command, this API can be only used in repetition mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pMsc: Pointer to the MSC module
 *               command: command to be transmitted up to 32 bits
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Command frame send successful
 *               FALSE: Command frame send failed
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2026/03/13    01358     Create
 *********************************************************************************************************************/
#if defined(THA6_THA6206D)
extern boolean Msc_Hal_SyncSendCommand(MSC_MODULE *const pMsc, uint32 command);
#endif

/**********************************************************************************************************************
 * Function:     Msc_Hal_SendData
 * Description:  Send complete downstream data, both high and low
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When writting data to different MSC modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pMsc: Pointer to the MSC module
 *               data: data to be transmitted
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *********************************************************************************************************************/
extern void Msc_Hal_SendData(MSC_MODULE *const pMsc, uint32 data);

/**********************************************************************************************************************
 * Function:     Msc_Hal_ReceiveData
 * Description:  Receive upstream frame data
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When reading data from different MSC modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pMsc: Pointer to the MSC module
 *               upstreamIdx: index of the upstream data register
 *               pData: Specifies the data received
 * Inout:        None
 * Output:       None
 * Return:       Msc_RxStatus: reception status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *********************************************************************************************************************/
extern Msc_RxStatus Msc_Hal_ReceiveData(MSC_MODULE *const pMsc, Msc_UpstreamRegType upstreamIdx, uint8 *const pData);

/**********************************************************************************************************************
 * Function:     Msc_Hal_ControlDownstream
 * Description:  Enable or disable downstream channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different MSC modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pMsc: Pointer to the MSC module
 *               downstreamEn: To disable or enable downstream channel
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *********************************************************************************************************************/
extern void Msc_Hal_ControlDownstream(MSC_MODULE *const pMsc, Msc_DownstreamEn downstreamEn);

/**********************************************************************************************************************
 * Function:     Msc_Hal_StartTimeoutDetection
 * Description:  Start the upstream channel timeout detection
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different MSC modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pMsc: Pointer to the MSC module
 *               pConfig: Specifies the upstream timeout configuration pointer
 *               enable: To enable or disable the upstream timeout interrupt
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *********************************************************************************************************************/
extern void Msc_Hal_StartTimeoutDetection(MSC_MODULE *const pMsc, const Msc_TimeoutConfig *const pConfig, Msc_IntrEn enable);

/**********************************************************************************************************************
 * Function:     Msc_Hal_SetDataTarget
 * Description:  Set downstream data target
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different MSC modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pMsc: Pointer to the MSC module
 *               enXHigh: Specifies the chip select enable line
 *               enXLow: Specifies the chip select enable line
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *********************************************************************************************************************/
extern void Msc_Hal_SetDataTarget(MSC_MODULE *const pMsc, Msc_Target enXHigh, Msc_Target enXLow);

/**********************************************************************************************************************
 * Function:     Msc_Hal_SetCommandTarget
 * Description:  Set downstream command target
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different MSC modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pMsc: Pointer to the MSC module
 *               enX: Specifies the chip select enable line
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *********************************************************************************************************************/
extern void Msc_Hal_SetCommandTarget(MSC_MODULE *const pMsc, Msc_Target enX);

/**********************************************************************************************************************
 * Function:     Msc_Hal_ControlUpstream
 * Description:  To enable or disable upstream channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different MSC modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pMsc: Pointer to the MSC module
 *               upDiv: Specifies the upstream division coefficient
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *********************************************************************************************************************/
extern void Msc_Hal_ControlUpstream(MSC_MODULE *const pMsc, Msc_UpDiv upDiv);

/**********************************************************************************************************************
 * Function:     Msc_Hal_SelectReceivingDevice
 * Description:  Configure upstream input signals
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different MSC modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pMsc: Pointer to the MSC module
 *               sdi:Specifies the serial data input line
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *********************************************************************************************************************/
extern void Msc_Hal_SelectReceivingDevice(MSC_MODULE *const pMsc, Msc_Sdi sdi);

/**********************************************************************************************************************
 * Function:     Msc_Hal_EnableInterrupt
 * Description:  Enable interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different MSC modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pMsc: Pointer to the MSC module
 *               flag: Specifies the type of interrupt
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *********************************************************************************************************************/
extern void Msc_Hal_EnableInterrupt(MSC_MODULE *const pMsc, uint32 flag);

/**********************************************************************************************************************
 * Function:     Msc_Hal_DisableInterrupt
 * Description:  Enable or disable downstream interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different MSC modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pMsc: Pointer to the MSC module
 *               flag: interrupt status flag
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *********************************************************************************************************************/
extern void Msc_Hal_DisableInterrupt(MSC_MODULE *const pMsc, uint32 flag);

/**********************************************************************************************************************
 * Function:     Msc_Hal_GetInterruptEnabledStatus
 * Description:  Get interrupt enabled status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pMsc: Pointer to the MSC module
 *               flag: Specifies the type of interrupt
 * Inout:        None
 * Output:       None
 * Return:       Msc_IntrEn: interrupt enabled status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *********************************************************************************************************************/
extern Msc_IntrEn Msc_Hal_GetInterruptEnabledStatus(const MSC_MODULE *const pMsc, Msc_IntrStsFlag flag);

/**********************************************************************************************************************
 * Function:     Msc_Hal_GetServiceNodeNumber
 * Description:  Get interrupt service node number
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pMsc: Pointer to the MSC module
 *               flag: Specifies the type of interrupt
 * Inout:        None
 * Output:       None
 * Return:       uint8: service node number
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *********************************************************************************************************************/
extern uint8 Msc_Hal_GetServiceNodeNumber(const MSC_MODULE *const pMsc, Msc_IntrStsFlag flag);

/**********************************************************************************************************************
 * Function:     Msc_Hal_GetIntrStatusFlag
 * Description:  Get the interrupt status flag
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pMsc: Pointer to the MSC module
 *               flag: MSC interrupt status flag
 * Inout:        None
 * Output:       None
 * Return:       Msc_Status: Status flag is set or reset
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *********************************************************************************************************************/
extern Msc_Status Msc_Hal_GetIntrStatusFlag(const MSC_MODULE *const pMsc, Msc_IntrStsFlag flag);

/**********************************************************************************************************************
 * Function:     Msc_Hal_GetTransmitStatusFlag
 * Description:  Get the MSC transmission status flag
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pMsc: Pointer to the MSC module
 *               flag: MSC downstream status flag
 * Inout:        None
 * Output:       None
 * Return:       Msc_Status: Status flag is set or reset
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *********************************************************************************************************************/
extern Msc_Status Msc_Hal_GetTransmitStatusFlag(const MSC_MODULE *const pMsc, Msc_TransmitStsFlag flag);

/**********************************************************************************************************************
 * Function:     Msc_Hal_ClearIntrStatusFlag
 * Description:  Clear the MSC interrupt status flag
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pMsc: Pointer to the MSC module
 *               flag: MSC interrupt status flag
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *********************************************************************************************************************/
extern void Msc_Hal_ClearIntrStatusFlag(MSC_MODULE *const pMsc, Msc_IntrStsFlag flag);

#define MSC_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Msc_MemMap.h"

#endif /* MSC_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
