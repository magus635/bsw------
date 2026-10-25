/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    eth_std.h
 * Author:      00930
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of internal functions.
 *********************************************************************************************************************/
#ifndef ETH_STD_H_
#define ETH_STD_H_

/*
*#Violation Summary
*#eth_std_h_REF_1:MISRAC2012-Rule-2.3;
* Justification: The members of the type are used in configuration-generated code.
*
*#eth_std_h_REF_2:MISRAC2012-Dir-4.3;
* Justification:Mixing inline assembly with C code reduces code complexity.
*
*#eth_std_h_REF_3:MISRAC2012-Dir-1.1;
* Justification: Inline assembly for CPU-specific operations.
*
*#eth_std_h_REF_4:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*#eth_std_h_REF_5:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "eth_register.h"
#include "Platform_Types.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* Maximum timeout count for hardware timeout errors,400Mhz,1000us */
#define ETH_MAXTIMEOUT_COUNT (400000U)
/* Timer set wait ticks,400Mhz,200us */
#define ETH_TIMERSET_TICKS (80000U)
/* Timer set wait ticks,25Mhz,200us */
#define ETH_TIMERSET_TICKS1 (5000U)
/* Value of One second in Nano seconds - That is 10^9 */
#define ETH_ONE_SEC_TO_NANOSEC (1000000000U)
/* Value - 2^32 */
#define ETH_TWO_POW_32_VAL (4294967296ULL)

#define ETH_BIT_DISABLE (0U)
#define ETH_BIT_ENABLE (1U)

#define ETH_REG_CHECK
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* List of the Return State */
typedef enum
{
    ETH_RETURN_FALSE = 0U, /* Return failure state */
    ETH_RETURN_TRUE        /* Return success state */
} Eth_ReturnState;

/* Define System time correction offset */
typedef enum
{
    ETH_SYSTIME_CORR_NEGATIVE = 0U, /* Correction value is subtracted from the system time(False) */
    ETH_SYSTIME_CORR_POSITIVE       /* Correction value is added to the system time(True) */
} Eth_SysTimeCorrect;

/* Define MTL_Qn_Interrupt_Control_Status */
typedef enum
{
    ETH_MTL_TXQUEUEUNDERFLOW_FLAG = 0x1U,    /* Transmit Queue Underflow Status */
    ETH_MTL_AVERAGEBITSPERSLOT_FLAG = 0x2U,  /* Average Bits Per Slot Status */
    ETH_MTL_RXQUEUEOVERFLOW_FLAG = 0x10000U, /* Receive Queue Overflow Status */
    ETH_MTL_TXQUEUEUNDERFLOW_EN = 0x100U,    /* Transmit Queue Underflow Enable */
    ETH_MTL_AVERAGEBITSPERSLOT_EN = 0x200U,  /* Average Bits Per Slot Interrupt Enable */
    ETH_MTL_RXQUEUEOVERFLOW_EN = 0x1000000U  /* Receive Queue Overflow Enable */
} Eth_MtlInterruptFlagOrEnable;

/* Define PHY_TXCTR_O of ETH PTR register in RGMII mode */
typedef enum
{
    ETH_TX_CTRL = 0x00U, /* Select tx_ctrl */
    ETH_TX_EN            /* Select tx_en */
/* #Violation: eth_std_h_REF_1 */
} Eth_PhyTxctrO;

/* Define TXQEN of register MTL_TxQ_Operation_Mode */
typedef enum
{
    ETH_TXQUEUE_DISABLE = 0x00U,   /* Not enable */
    ETH_TXQUEUE_AV_ENABLE,         /* Enable in AV mode */
    ETH_TXQUEUE_ENABLE             /* Enable */
} Eth_MtlTxqen;

/* Define RXQEN of register MAC_RxQ_Ctrl0 */
typedef enum
{
    ETH_RXQUEUE_DISABLE = 0x00U,   /* Not enable */
    ETH_RXQUEUE_AV_ENABLE,         /* Enable in AV mode */
    ETH_RXQUEUE_ENABLE             /* Enable */
/* #Violation: eth_std_h_REF_1 */
} Eth_MacRxqen;

/* Preamble Length for Transmit packets,Definition in MAC_CONFIGURATION.B.PRELEN */
typedef enum
{
    ETH_PREAMBLELENGTH_7BYTES, /* 7 bytes of preamble */
    ETH_PREAMBLELENGTH_5BYTES, /* 5 bytes of preamble */
    ETH_PREAMBLELENGTH_3BYTES, /* 3 bytes of preamble */
/* #Violation: eth_std_h_REF_1 */
} Eth_PreambleLength;

/* Define the OWN bit of descriptor */
typedef enum
{
    ETH_APPLICATION_OWN = 0x00U, /* Application owns the descriptor */
    ETH_DMA_OWN                  /* DMA owns the descriptor */
/* #Violation: eth_std_h_REF_1 */
} Eth_DescrOwn;

/* Define GMII operation command */
typedef enum
{
    ETH_GOC_WRITE = 1U,      /* Write command */
    ETH_GOC_POSTREADINCADDR, /* Post Read Increment Address for Clause 45 PHY */
    ETH_GOC_READ             /* Read command */
/* #Violation: eth_std_h_REF_1 */
} Eth_GmiiOperationCommand;

/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/* #Violation: eth_std_h_REF_4 */
#define ETH_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: eth_std_h_REF_5 */
#include "Eth_MemMap.h"
/**********************************************************************************************************************
 * Function:     Eth_Register_ReadBack_Check
 * Description:  Register read back check
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        state: Original state
 *               expect: The value expected to be written
 *               value: The value actually written
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/03/07    01359     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Eth_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value);
 /**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
#if defined(ETH_REG_CHECK)
LOCAL_FORCEINLINE boolean Eth_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
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
LOCAL_FORCEINLINE boolean Eth_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    (void)state;
    (void)expect;
    (void)value;

    return state;
}
#endif

 /**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:     Eth_Std_ResetModule
 * Description:  Reset the ETH module
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthModule: Pointer to the ETH module registers
 * Inout:        None
 * Output:       None
 * Return:       Eth_ReturnState:
 *                 ETH_RETURN_TRUE: Success
 *                 ETH_RETURN_FALSE: Fail
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
extern Eth_ReturnState Eth_Std_ResetModule(ETH_MODULE *const pEthModule);

/**********************************************************************************************************************
 * Function:     Eth_Std_InitTime
 * Description:  initialize the time
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthModule: Pointer to the ETH module registers
 *               ethOpetnFreq: The source clock of Eth is AXI clock in Hz(200000000Hz)
 * Inout:        None
 * Output:       pPrevFreqCompensationValue: previous frequency compensation value
 * Return:       Eth_ReturnState:
 *                 ETH_RETURN_TRUE: Success
 *                 ETH_RETURN_FALSE: Fail
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
extern Eth_ReturnState Eth_Std_InitTime(ETH_MODULE *const pEthModule, const uint32 ethOpetnFreq,
                                        float64 *const pPrevFreqCompensationValue);

/**********************************************************************************************************************
 * Function:     Eth_Std_ClearDaFilter
 * Description:  Enable/disable to clear the DA filters
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pEthModule: Pointer to the ETH module registers
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
extern boolean Eth_Std_ClearDaFilter(ETH_MODULE *const pEthModule);

/**********************************************************************************************************************
 * Function:     Eth_Std_SetMacMaxPacketSize
 * Description:  Set MAC max packet size
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthModule: Pointer to the ETH module registers
 *               maxPacketSize: Maximum size of the ethernet packet
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
extern boolean Eth_Std_SetMacMaxPacketSize(ETH_MODULE *const pEthModule, uint16 maxPacketSize);

/**********************************************************************************************************************
 * Function:     Eth_Std_SetMulticast
 * Description:  Enable/disable the multicast traffic
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthModule: Pointer to the ETH module registers
 *               enableMulticast: Enable/disable the multicast traffic
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
extern boolean Eth_Std_SetMulticast(ETH_MODULE *const pEthModule, boolean enableMulticast);

/**********************************************************************************************************************
 * Function:     Eth_Std_SetPromiscuous
 * Description:  The function shall enable/disable the Promiscuous Mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthModule: Pointer to the ETH module registers
 *               enablePromiscuous: Enable/disable the Promiscuous Mode
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
extern boolean Eth_Std_SetPromiscuous(ETH_MODULE *const pEthModule, boolean enablePromiscuous);

/**********************************************************************************************************************
 * Function:     Eth_Std_AddDaFilter
 * Description:  Add MAC address as a DA address filtering
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthModule: Pointer to the ETH module registers
 *               addrHigh: High address
 *               addrLow: Low address
 * Inout:        None
 * Output:       None
 * Return:       Eth_ReturnState:
 *                 ETH_RETURN_TRUE: Successed to add MAC address as a DA address filter and register read back check correct
 *                 ETH_RETURN_FALSE: Failed to add MAC address as a DA address filter or register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
extern Eth_ReturnState Eth_Std_AddDaFilter(ETH_MODULE *const pEthModule, uint32 addrHigh, uint32 addrLow);

/**********************************************************************************************************************
 * Function:     Eth_Std_RemoveDaFilter
 * Description:  Remove MAC address as a DA address filtering
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pEthModule: Pointer to the ETH module registers
 *               addrHigh: High address
 *               addrLow: Low address
 * Inout:        None
 * Output:       None
 * Return:       Eth_ReturnState:
 *                 ETH_RETURN_TRUE: Successed to remove MAC address as a DA address filter and register read back check correct
 *                 ETH_RETURN_FALSE: Failed to remove MAC address as a DA address filter or register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    00930      Create
 *********************************************************************************************************************/
extern Eth_ReturnState Eth_Std_RemoveDaFilter(ETH_MODULE *const pEthModule, uint32 addrHigh, uint32 addrLow);

/**********************************************************************************************************************
 * Function:    Eth_Std_SetCorrectTime
 * Description: Correct the current time either adding or subtracting
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:       pEthModule: Pointer to the ETH module registers
 *              correctType:
 *                POSITIVE: Correction value is added to the system time.
 *                NEGATIVE: Correction value is subtracted from the system time.
 *              secondsHiUpdate: High 16bits second to update
 *              secondsUpdate: The seconds to update
 *              nanoSecondsUpdate: The nanoSeconds to update
 * Inout:        None
 * Output:      None
 * Return:      Eth_ReturnState:
 *                 ETH_RETURN_TRUE: Successed to correct time and register read back check correct
 *                 ETH_RETURN_FALSE: Failed to correct time or register read back check incorrect
 * Others:      None
 * History:
 *  Date        Author    Modified
 *  2023/06/19  00930      Create
 *********************************************************************************************************************/
extern Eth_ReturnState Eth_Std_SetCorrectTime(ETH_MODULE *const pEthModule, Eth_SysTimeCorrect correctType,
                                              uint16 secondsHiUpdate, uint32 secondsUpdate, uint32 nanoSecondsUpdate);

/**********************************************************************************************************************
 * Function:    Eth_Std_SetCorrectRateRatio
 * Description: Correct the system rate ratio
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:       pEthModule: Pointer to the ETH module registers
 *              freqCompensationValue: The frequency compensation value
 * Inout:        None
 * Output:      None
 * Return:      Eth_ReturnState:
 *                 ETH_RETURN_TRUE: Successed to correct rate ratio and register read back check correct
 *                 ETH_RETURN_FALSE: Failed to correct rate ratio or register read back check incorrect
 * Others:      None
 * History:
 *  Date        Author    Modified
 *  2023/06/19  00930      Create
 *********************************************************************************************************************/
extern Eth_ReturnState Eth_Std_SetCorrectRateRatio(ETH_MODULE *const pEthModule, float64 freqCompensationValue);

/**********************************************************************************************************************
 * Function:    Eth_Std_WaitGmiiFree
 * Description: Wait until GMII is free
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:       pEthModule: Pointer to the ETH module registers
 *              timeOut: the max delay time
 * Inout:        None
 * Output:      None
 * Return:      Eth_ReturnState:
 *                ETH_RETURN_TRUE: Success
 *                ETH_RETURN_FALSE: Fail
 * Others:      None
 * History:
 *  Date        Author    Modified
 *  2023/06/19  00930      Create
 *********************************************************************************************************************/
extern Eth_ReturnState Eth_Std_WaitGmiiFree(const ETH_MODULE *const pEthModule, uint32 timeOut);

/**********************************************************************************************************************
 * Function:    Eth_Std_WaitTsinitFree
 * Description: Wait until time-stamp can be initialized
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:       pEthModule: Pointer to the ETH module registers
 *              timeOut: the max delay time
 * Inout:        None
 * Output:      None
 * Return:      Eth_ReturnState:
 *                ETH_RETURN_TRUE: Success
 *                ETH_RETURN_FALSE: Fail
 * Others:      None
 * History:
 *  Date        Author    Modified
 *  2023/06/19  00930      Create
 *********************************************************************************************************************/
extern Eth_ReturnState Eth_Std_WaitTsinitFree(const ETH_MODULE *const pEthModule, uint32 timeOut);

/* #Violation: eth_std_h_REF_4 */
#define ETH_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: eth_std_h_REF_5 */
#include "Eth_MemMap.h"

#endif /* ETH_STD_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
