/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    can_hal.c
 * Author:      00949
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains basic  implementation function of CAN module.
 *********************************************************************************************************************/

/*
*#Violation Summary
*
*#can_hal_c_REF_1:CERTC-DCL15-C;
* Justification:Reserved API for user access.
*
*#can_hal_c_REF_2:CERTC-INT36-C;
* Justification:Cast a numeric value to a pointer type for accessing data at a specified memory address.
*
*#can_hal_c_REF_3:MISRAC2012-Rule-2.1;
* Justification:Reserved API for user access.
*
*#can_hal_c_REF_4:MISRAC2012-Rule-11.4;
* Justification:Converting integers to object pointers to reduce register access complexity.
*
*#can_hal_c_REF_5:CERTC-DCL19-C;
* Justification:Reserved API for user access.
*
*#can_hal_c_REF_6:CWE-704;
* Justification:Cast a numeric value to a pointer type for accessing data at a specified memory address.
*
*#can_hal_c_REF_7:CERTC-DCL02-C;
* Justification:Company-specific naming conventions  are applied. Developers will not be confused.
*
*#can_hal_c_REF_8:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#can_hal_c_REF_9:MISRAC2012-Rule-8.7; 
* Justification:The function is used by other file.
*
*#can_hal_c_REF_10:MISRAC2012-Dir-2.7;
* Justification: Parameters are used by assembly code.
*
*#can_hal_c_REF_11:MISRAC2012-Rule-1.2; 
* Justification: Inline assembly for CPU-specific operations.
*
* #can_hal_c_REF_12:MISRAC2012-Rule-10.5
* Justification:Necessary type casting to reduce code complexity; Code review ensure the safety of the casting.
*
*#can_hal_c_REF_13:MISRAC2012-Dir-4.9;
* Justification:Function like macros are used to reduce code complexity.
*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "can_register.h"
#include "can_std.h"
#include "can_hal.h"
#include "stm_hal.h"
#include "itmu.h"
#if(STD_ON == INPUT_ARG_DETECT)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                            Private Variables Definition
 *********************************************************************************************************************/
/* CAN function callback pointer */
typedef uint32 (*const canFunCbPtr)(const CAN_NODE *const p);
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
#define CAN_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: can_hal_c_REF_8 */
#include "Can_MemMap.h"
/**********************************************************************************************************************
 * Function:     Can_Hal_CheckTimeout
 * Description:  Whether it has timed out within the specified time, by checking
 *               the value returned by the function and the expected value
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode:Specifies the pointer to the CAN node registers
 *               actualFun: Specify the function pointer
 *               expectValue: the expect value
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE if timeout, FALSE if not timeout
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/06   01107      Create
 *********************************************************************************************************************/
static boolean Can_Hal_CheckTimeout(const CAN_NODE *const pNode, canFunCbPtr actualFun, uint32 expectValue);
/**********************************************************************************************************************
 * Function:     Can_Hal_StartInitialization
 * Description:  Returns the address of message RAM
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       boolean: ENABLE is success, DISABLE is fail
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/06   01107      Create
 *********************************************************************************************************************/
static boolean Can_Hal_StartInitialization(CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Hal_ArrayCopy32NByte
 * Description:  Copy 32*N(N=1,2,3,4...) bytes data from source address to destination address
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        src: source address pointer
 *               dest: destination address pointer
 *               count: copy data count in byte unit
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       count value must be an integer multiple of 32
 * History:
 *  Date          Author    Modified
 *  2023/09/06    00976      Create
 *********************************************************************************************************************/
static void Can_Hal_ArrayCopy32NByte(uint32 const volatile *src, uint32 *dest, uint32 count);
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
static boolean Can_Hal_CheckTimeout(const CAN_NODE *const pNode, canFunCbPtr actualFun, uint32 expectValue)
{
    boolean timeout = TRUE;

    uint64 tickStart;

    uint64 currentTick;

    uint64 tickEnd;

    uint32 actualValue;
    
    tickStart = Stm_Hal_GetValue();

    tickEnd = tickStart + CAN_INITIALIZATION_TIMEOUT;

    currentTick = Stm_Hal_GetValue();

    do
    {
        actualValue = actualFun(pNode);
        if (actualValue == expectValue)
        {
            timeout = FALSE;
        }
        else
        {
            currentTick = Stm_Hal_GetValue();
        }
    } while ((currentTick < tickEnd) && (actualValue != expectValue));

    return timeout;
}

static boolean Can_Hal_StartInitialization(CAN_NODE *const pNode)
{
    boolean timeout;

    boolean initScuuess;

    /* Exit from Sleep mode */
    initScuuess = Can_Std_SetCccrClockRequestStop(pNode, CAN_DISABLE);

    /* Check Sleep mode acknowledge */
    timeout = Can_Hal_CheckTimeout(pNode, Can_Std_GetCccrClockStopACK, 0U);

    if (FALSE == timeout)
    {
        /* Request initialisation */
        Can_Std_SetCccrInit(pNode, CAN_ENABLE);

        /* Wait until the INIT bit into CCCR register is set */
        timeout = Can_Hal_CheckTimeout(pNode, Can_Std_GetCccrInit, 1U);

        /* Check for the Timeout */
        if (FALSE == timeout)
        {
            /* Configuration Change Enable */
            initScuuess &= Can_Std_SetCccrConfigurationChange(pNode, CAN_ENABLE);

            initScuuess &= CAN_ENABLE;
        }
        else
        {
            initScuuess &= CAN_DISABLE;
        }
    }
    else
    {
        initScuuess = CAN_DISABLE;
    }

    return initScuuess;
}

/* #Violation: can_hal_c_REF_10 */
/* #Violation: can_hal_c_REF_10 */
/* #Violation: can_hal_c_REF_10 */
static void Can_Hal_ArrayCopy32NByte(uint32 const volatile *src, uint32 *dest, uint32 count)
{
    /* #Violation: can_hal_c_REF_11 */
    ASM_VOLATILE(
        "1:\n"
        " ldmia %0!, {r3-r10}\n"
        " stmia %1!, {r3-r10}\n"
        " subs %2, %2, #32\n"
#ifdef __TASKING__
        " bgt 1p\n"
#else
        " bgt 1b\n"
#endif
        :
        : "r" (src), "r" (dest), "r" (count)
        : "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "memory"
        );
}

/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
Can_Status Can_Hal_ModuleRamClear(void)
{
    boolean statusItmu;

    statusItmu = Itmu_ClearModuleRam(0U, ITMU_RMAINI_CAN);

    return (statusItmu == TRUE) ? CAN_STATUS_OK : CAN_STATUS_ERROR;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
Can_Status Can_Hal_Init(CAN_NODE *const pNode, const Can_NodeConfig *const cfg, uint32 *const msgEndAddress)
{
    uint32 successful;

    uint32 address;

    uint32 endAddress;

    uint32 msgStartAddress;

    Can_Status status;

    Can_MessageRAM msgRam = {0};

    uint32 enable;

    boolean ret;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != msgEndAddress));
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != cfg));
    /* messageRAMOffset must be 4-byte aligned */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(0U == (cfg->messageRAMOffset % 4U)));
#endif

    ret = TRUE;

    status = CAN_STATUS_ERROR;

    successful = Can_Hal_StartInitialization(pNode);

    if (CAN_ENABLE == successful)
    {
        /* Set the automatic retransmission */
        enable = (cfg->retransmission > 0U) ? 0U : 1U;
        ret &= Can_Std_SetCccrDisableAutomaticRetransmission(pNode, enable);

        /* Set the transmit pause feature */
        ret &= Can_Std_SetCccrTransmissionPause(pNode, cfg->transmitPause);

        /* Set the Protocol Exception Handling */
        enable = (cfg->protocolException > 0U) ? 0U : 1U;
        ret &= Can_Std_SetCccrDisableProtocolExceptionHandling(pNode, enable);

        /* Set the wide message mark mode */
        ret &= Can_Std_SetWideMessageMark(pNode, cfg->wideMessageMark);

        /* Set edge filtering during Bus Integration */
        ret &= Can_Std_SetCccrEdgeFiltering(pNode, cfg->edgeFilter);

        /* Set operation mode */
        ret &= Can_Hal_ConfigOperationMode(pNode, cfg->opsMode);

        /* Set the nominal bit timing register */
        ret &= Can_Hal_ConfigBaudrate(pNode, &cfg->baudRate);

        /* Sets frame format */
        status = Can_Hal_ConfigFrameFormat(pNode, cfg->frameFormat);

        /* Set XIDAM */
        if (0U != cfg->xidamConfig.enable)
        {
            ret &= Can_Std_SetExtendedFilterXIDAM(pNode, cfg->xidamConfig.XIDAM);
        }

        /* Set DMU request line */
        ret &= Can_Std_SetDmuRequest(pNode, CAN_STD_DMU_REQUEST_TX, cfg->dmuLineConfig.enableTX);
        ret &= Can_Std_SetDmuRequest(pNode, CAN_STD_DMU_REQUEST_RX_0, cfg->dmuLineConfig.enableRX0);
        ret &= Can_Std_SetDmuRequest(pNode, CAN_STD_DMU_REQUEST_RX_1, cfg->dmuLineConfig.enableRX1);
        ret &= Can_Std_SetDmuRequest(pNode, CAN_STD_DMU_REQUEST_TXE, cfg->dmuLineConfig.enableTXE);

        if (CAN_STATUS_OK == status)
        {
            /* Sets Fast Baud Rate */
            ret &= Can_Hal_ConfigFastBaudrate(pNode, &cfg->fdBaudRate);

            /* Get CAN module base address */
            msgStartAddress = Can_Std_GetModuleRAMStartAddr(pNode);
            if (0U != msgStartAddress)
            {
                /* Start address: Standard\Extended filter list */
                /* Start address: [FIFO 0] + [FIFO 1] + [Dedicated buffer]   */
                /* Start address: Tx event fifo list */
                /* Start address: Tx [FIFO\Queue] + [dedicated buffer] list */
                msgRam.standardFilterSA = msgStartAddress         +  cfg->messageRAMOffset;
                msgRam.extendedFilterSA = msgRam.standardFilterSA + (cfg->filterConfig.stdFiltersNbr * 4U);
                msgRam.rxFIFO0SA        = msgRam.extendedFilterSA + (cfg->filterConfig.extFiltersNbr * 8U);
                msgRam.rxFIFO1SA        = msgRam.rxFIFO0SA        + (cfg->rxConfig.fifo0ElmtsNbr     * Can_Std_ElementSzieToBytes(cfg->rxConfig.fifo0ElmtSize));
                msgRam.rxBufferSA       = msgRam.rxFIFO1SA        + (cfg->rxConfig.fifo1ElmtsNbr     * Can_Std_ElementSzieToBytes(cfg->rxConfig.fifo1ElmtSize));
                msgRam.txEventFIFOSA    = msgRam.rxBufferSA       + (cfg->rxConfig.buffersNbr        * Can_Std_ElementSzieToBytes(cfg->rxConfig.bufferElmSize));
                msgRam.txBufferSA       = msgRam.txEventFIFOSA    + (cfg->txConfig.eventsNbr         * 8U);

                ret &= Can_Hal_InitMessageRam(pNode, &cfg->filterConfig, &cfg->rxConfig, &cfg->txConfig, &msgRam);

                /* CAN node end address */
                address = msgRam.txBufferSA + ((cfg->txConfig.buffersNbr + cfg->txConfig.fifoQueueElmtsNbr) * Can_Std_ElementSzieToBytes(cfg->txConfig.elmtSize));
                /* CAN module end address */
                endAddress = Can_Std_GetModuleRAMEndAddr(pNode);

                if (address <= endAddress)
                {
                    status = Can_Hal_ExitInitMode(pNode);
                    if (CAN_STATUS_OK == status)
                    {
                        *msgEndAddress = address - msgStartAddress;
                    }
                    else
                    {
                        *msgEndAddress = 0U;
                    }
                }
                else
                {
                    status = CAN_STATUS_PARAM_ERROR;
                }
            }
        }
    }

    if (FALSE == ret)
    {
        status = CAN_STATUS_ERROR;
    }

    return status;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
Can_Status Can_Hal_Deinit(CAN_NODE *const pNode)
{
    uint32 successful;

 #if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    successful = Can_Hal_StartInitialization(pNode);

    if (successful == CAN_ENABLE)
    {
        successful &= Can_Std_SetIleEnt0(pNode, CAN_DISABLE);

        successful &= Can_Std_SetIleEnt1(pNode, CAN_DISABLE);
    }

    return (successful == CAN_ENABLE) ? CAN_STATUS_OK : CAN_STATUS_ERROR;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
Can_Status Can_Hal_EnterPowerDownMode(CAN_NODE *const pNode)
{
    boolean ret = TRUE;
    boolean timeout;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

     ret &= Can_Std_SetCccrClockRequestStop(pNode, CAN_ENABLE);

    timeout = Can_Hal_CheckTimeout(pNode, Can_Std_GetCccrClockStopACK, 1U);
    if (TRUE != ret)
    {
        timeout = TRUE;
    }

    return (timeout == FALSE) ? CAN_STATUS_OK : CAN_STATUS_TIMEOUT;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
Can_Status Can_Hal_ExitPowerDownMode(CAN_NODE *const pNode)
{
    boolean ret = TRUE;
    boolean timeout;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    ret &= Can_Std_SetCccrClockRequestStop(pNode, CAN_DISABLE);

    timeout = Can_Hal_CheckTimeout(pNode, Can_Std_GetCccrClockStopACK, 0U);
    if (TRUE != ret)
    {
        timeout = TRUE;
    }

    return (timeout == FALSE) ? CAN_STATUS_OK : CAN_STATUS_TIMEOUT;
}


/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
uint32 Can_Hal_GetPowerStatus(const CAN_NODE *const pNode)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    return Can_Std_GetCccrClockStopACK(pNode);
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_ConfigWideMessageMark(CAN_NODE *const pNode, uint32 enable)
{
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif
    ret = TRUE;

    ret &= Can_Std_SetWideMessageMark(pNode, enable);

    return ret;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_ConfigAutomaticRetransmission(CAN_NODE *const pNode, uint32 enable)
{
    uint32 enctrl;
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif
    ret = TRUE;

    enctrl = (enable > 0U) ? CAN_DISABLE : CAN_ENABLE;

    ret &= Can_Std_SetCccrDisableAutomaticRetransmission(pNode, enctrl);

    return ret;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
/* #Violation: can_hal_c_REF_5 */
/* #Violation: can_hal_c_REF_9 */
Can_Status Can_Hal_ConfigFrameFormat(CAN_NODE *const pNode, uint32 frameFormat)
{
    boolean ret = TRUE;
    Can_Status status;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));

#endif

    status = CAN_STATUS_OK;

    switch(frameFormat)
    {
      case CAN_FRAME_FORMAT_STANDARD:
        ret &= Can_Std_SetCccrFD(pNode, CAN_DISABLE);
        ret &= Can_Std_SetCccrBRS(pNode, CAN_DISABLE);
        break;
      case CAN_FRAME_FORMAT_FD_NO_BRS:
        ret &= Can_Std_SetCccrFD(pNode, CAN_ENABLE);
        ret &= Can_Std_SetCccrBRS(pNode, CAN_DISABLE);
        break;
      case CAN_FRAME_FORMAT_FDFAST:
        ret &= Can_Std_SetCccrFD(pNode, CAN_ENABLE);
        ret &= Can_Std_SetCccrBRS(pNode, CAN_ENABLE);
        break;
      default:
        status = CAN_STATUS_PARAM_ERROR;
        break;
    }

    if (TRUE != ret)
    {
        status = CAN_STATUS_PARAM_ERROR;
    }

    return status;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
/* #Violation: can_hal_c_REF_5 */
/* #Violation: can_hal_c_REF_9 */
boolean Can_Hal_ConfigBaudrate(CAN_NODE *const pNode, const Can_BaudRate *const pBaudRate)
{
    boolean ret = TRUE;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));

    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != pBaudRate));
#endif

    ret &= Can_Std_SetBaudrate(pNode, pBaudRate->prescaler,
                               pBaudRate->syncJumpWidth,
                               pBaudRate->timeSegment1,
                               pBaudRate->timeSegment2);

    return ret;
}


/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
/* #Violation: can_hal_c_REF_5 */
/* #Violation: can_hal_c_REF_9 */
boolean Can_Hal_ConfigFastBaudrate(CAN_NODE *const pNode, const Can_FastBaudRate *const pFastBaudRate)
{
    boolean ret = TRUE;
    
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));

    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != pFastBaudRate));

#endif

   ret &= Can_Std_SetFDBaudrate(pNode, pFastBaudRate->prescaler,
                                pFastBaudRate->syncJumpWidth,
                                pFastBaudRate->timeSegment1,
                                pFastBaudRate->timeSegment2);

    /* set transceiver delay compensation offset */
    if(pFastBaudRate->compDlyOffset > 0U)
    {
        /* enable Transceiver Delay Compensation */
        ret &= Can_Std_SetTxDelayCompensation(pNode, CAN_ENABLE);

        /* set Transceiver Delay Compensation offset and filter window */
        ret &= Can_Std_ConfigTxDelayCompensation(pNode, pFastBaudRate->compDlyOffset,
                                                 pFastBaudRate->compFilterWindow);
    }

    return ret;
}


/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
/* #Violation: can_hal_c_REF_5 */
/* #Violation: can_hal_c_REF_9 */
boolean Can_Hal_ConfigOperationMode(CAN_NODE *const pNode, uint32 mode)
{
    boolean ret = TRUE;
    
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    /* Reset CAN Operation Mode */
    ret &= Can_Std_SetMonitorMode(pNode, CAN_DISABLE);
    ret &= Can_Std_SetCccrRestricted(pNode, CAN_DISABLE);
    ret &= Can_Std_SetCccrTest(pNode, CAN_DISABLE);
    ret &= Can_Std_SetTestLBCK(pNode, CAN_DISABLE);

   /* Set CAN Operating Mode:
               | Normal | Restricted |    Bus     | Internal | External
               |        | Operation  | Monitoring | LoopBack | LoopBack
     CCCR.TEST |   0    |     0      |     0      |    1     |    1
     TEST.LBCK |   0    |     0      |     0      |    1     |    1
     CCCR.MON  |   0    |     0      |     1      |    1     |    0
     CCCR.ASM  |   0    |     1      |     0      |    0     |    0
  */

    switch(mode)
    {
      case CAN_OPERATION_MODE_NORMAL:
        ret = TRUE;
        break;
      case CAN_OPERATION_MODE_ASM:
        ret &= Can_Std_SetCccrRestricted(pNode, CAN_ENABLE);
        break;
      case CAN_OPERATION_MODE_MONITOR:
        ret &= Can_Std_SetMonitorMode(pNode, CAN_ENABLE);
        break;
      case CAN_OPERATION_MODE_INLOOPBACK:
        ret &= Can_Std_SetTestMode(pNode, TRUE);
        break;
      case CAN_OPERATION_MODE_EXLOOPBACK:
        ret &= Can_Std_SetTestMode(pNode, FALSE);
        break;
      default:
        ret = FALSE;
        break;
    }

    return ret;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_ConfigTransmissionPause(CAN_NODE *const pNode, boolean enable)
{
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    ret = TRUE;

    ret &= Can_Std_SetCccrTransmissionPause(pNode, enable);

    return ret;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
/* #Violation: can_hal_c_REF_5 */
/* #Violation: can_hal_c_REF_9 */
boolean Can_Hal_InitMessageRam(CAN_NODE *const pNode,
                               const Can_FilterConfig *const pFilterConfig,
                               const Can_RxConfig *const pRxConfig,
                               const Can_TxConfig *const pTxConfig,
                               const Can_MessageRAM *const pMessageRam)
{
    boolean ret = TRUE;
    
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));

    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != pTxConfig));

    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != pMessageRam));

    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != pRxConfig));

    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != pFilterConfig));
#endif

    /* Set gloabl filter */
    ret &= Can_Std_ConfigGlobalFilter(pNode,
                                      pFilterConfig->stdNotMatch,
                                      pFilterConfig->extNotMatch,
                                      pFilterConfig->stdRejectRemoteFrame,
                                      pFilterConfig->extRejectRemoteFrame);

    /* Config standard filter */
    if (pFilterConfig->stdFiltersNbr > 0U)
    {
        /* Set standard filter start address in the Message RAM */
        ret &= Can_Std_SetStdFilterListStartAddress(pNode, pMessageRam->standardFilterSA);

        /* Set standard filter element number */
        ret &= Can_Std_SetStandardFilterListSize(pNode, pFilterConfig->stdFiltersNbr);
    }

    /* Config extendard filter */
    if (pFilterConfig->extFiltersNbr > 0U)
    {
        /* Set extendard filter start address in the Message RAM */
        ret &= Can_Std_SetExtFilterStartAddress(pNode, pMessageRam->extendedFilterSA);

        /* Set extendard filter element number */
        ret &= Can_Std_SetExtendedFilterListSize(pNode, pFilterConfig->extFiltersNbr);
    }

    /* Config RX FIFO-0 */
    if (pRxConfig->fifo0ElmtsNbr > 0U)
    {
        /* Set Rx FIFO 0 start address in the Message RAM */
        ret &= Can_Std_SetRxFifo0StartAddress(pNode, pMessageRam->rxFIFO0SA);

        /* Set Rx FIFO 0 element unit size */
        ret &= Can_Std_SetRxFifo0DataFieldSize(pNode, pRxConfig->fifo0ElmtSize);

        /* Set Rx FIFO 0 element number */
        ret &= Can_Std_SetRxFifo0Size(pNode, pRxConfig->fifo0ElmtsNbr);

        /* Set Rx FIFO 0 operating mode */
        ret &= Can_Std_SetRxFifo0OperatingMode(pNode, pRxConfig->fifo0OperatingMode);

        /* Set Rx FIFO 0 watermark level */
        ret &= Can_Std_SetRxFifo0WatermarkLevel(pNode, pRxConfig->fifo0WatermarkLevel);
    }

    /* Config RX FIFO-1 */
    if (pRxConfig->fifo1ElmtsNbr > 0U)
    {
        /* Set Rx FIFO 1 start address in the Message RAM */
        ret &= Can_Std_SetRxFifo1StartAddress(pNode, pMessageRam->rxFIFO1SA);

        /* Set Rx FIFO 1 element unit size */
        ret &= Can_Std_SetRxFifo1DataFieldSize(pNode, pRxConfig->fifo1ElmtSize);

        /* Set Rx FIFO 1 element number */
        ret &= Can_Std_SetRxFifo1Size(pNode, pRxConfig->fifo1ElmtsNbr);

        /* Set Rx FIFO 1 operating mode */
        ret &= Can_Std_SetRxFifo1OperatingMode(pNode, pRxConfig->fifo1OperatingMode);

        /* Set Rx FIFO 1 watermark level */
        ret &= Can_Std_SetRxFifo1WatermarkLevel(pNode, pRxConfig->fifo1WatermarkLevel);
    }

    /* Config RX dedicated buffer */
    if (pRxConfig->buffersNbr > 0U)
    {
        /* Set Rx buffers start address in the Message RAM */
        ret &= Can_Std_SetRxBuffersStartAddress(pNode, pMessageRam->rxBufferSA);

        /* Set Rx buffer element unit size */
        ret &= Can_Std_SetRxBufferDataFieldSize(pNode, pRxConfig->bufferElmSize);
    }

    /* Config TX event */
    if (pTxConfig->eventsNbr > 0U)
    {
        /* Set TX event start address */
        ret &= Can_Std_SetTxEventFifoStartAddress(pNode, pMessageRam->txEventFIFOSA);

        /* Set event number */
        ret &= Can_Std_SetTxEventFifoSize(pNode, pTxConfig->eventsNbr);

        /* Set event water makr level */
        ret &= Can_Std_SetTxEventFifoWatermarkLevel(pNode, pTxConfig->eventFifoWatermarkLevel);
    }

    /* Config TX */
    if ((pTxConfig->fifoQueueElmtsNbr + pTxConfig->buffersNbr) > 0U)
    {
        /* Set Tx buffers start address in the Message RAM */
        ret &= Can_Std_SetTxBuffersStartAddress(pNode, pMessageRam->txBufferSA);

        /* Set Tx element unit size */
        ret &= Can_Std_SetTxBufferElrSize(pNode, pTxConfig->elmtSize);

        /* Set Tx FIFO/Queue number */
        ret &= Can_Std_SetTransmitFifoQueueSize(pNode, pTxConfig->fifoQueueElmtsNbr);

        /* Set Tx FIFO/Queue operation mode */
        ret &= Can_Std_SetTransmitFifoQueueMode(pNode, pTxConfig->fifoQueueMode);

        /* Set Tx dedicated buffer number */
        ret &= Can_Std_SetDedicatedTxBuffersNumber(pNode, pTxConfig->buffersNbr);
    }
    
    return ret;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
Can_Status Can_Hal_ConfigureFilter(const CAN_NODE *const pNode, const Can_Filter *const pFilter)
{
    Can_Status status;

    CAN_STDMSG *StdFilterElement;

    CAN_EXTMSG *ExddFilterElement;

    uint32 moduleBaseAddr;

    /* #Violation: can_hal_c_REF_7 */
    uint32 tempAddress;
    
    boolean ret = TRUE;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));

    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != pFilter));
#endif

    moduleBaseAddr = Can_Std_GetModuleBase(pNode);

    if (0U != moduleBaseAddr)
    {
        if ((CAN_FILTER_ID_TYPE_STANDARD == pFilter->idType) || (CAN_FILTER_ID_TYPE_MIXED == pFilter->idType))
        {
            /* get the standard filter element address */
            tempAddress = Can_Std_GetStdFilterListStartAddress(pNode);
            /* #Violation: can_hal_c_REF_2 */
            /* #Violation: can_hal_c_REF_4 */
            /* #Violation: can_hal_c_REF_6 */
            StdFilterElement = (CAN_STDMSG *)(moduleBaseAddr + tempAddress + (pFilter->stdIndex * 4U));

            if(pFilter->elmConfig == CAN_FILTERELECFG_STORE_RXBUFFER)
            {
                ret &= Can_Std_SetStandardFilterId2(StdFilterElement, pFilter->rxBufferOffset);
            }
            else
            {
                ret &= Can_Std_SetStandardFilterId2(StdFilterElement, (CAN_FILTER_ID_TYPE_MIXED == pFilter->idType) ?
                                                          (pFilter->id2 >> 18U) : pFilter->id2);
            }

            ret &= Can_Std_SetStandardFilterId1(StdFilterElement, (CAN_FILTER_ID_TYPE_MIXED == pFilter->idType) ?
                                                      (pFilter->id1 >> 18U) : pFilter->id1);
            ret &= Can_Std_SetStandardFilterConfiguration(StdFilterElement, pFilter->elmConfig);
            ret &= Can_Std_SetStandardFilterType(StdFilterElement, pFilter->type);
        }

        if ((CAN_FILTER_ID_TYPE_EXTENDED == pFilter->idType) || (CAN_FILTER_ID_TYPE_MIXED == pFilter->idType))
        {
            /* get the Extended filter element address */
            tempAddress = Can_Std_GetExtFilterStartAddress(pNode);
            /* #Violation: can_hal_c_REF_2 */
            /* #Violation: can_hal_c_REF_4 */
            /* #Violation: can_hal_c_REF_6 */
            ExddFilterElement = (CAN_EXTMSG *)(moduleBaseAddr + tempAddress + (pFilter->extIndex * 8U));

            if(CAN_FILTERELECFG_STORE_RXBUFFER == pFilter->elmConfig)
            {
                ret &= Can_Std_SetExtendedFilterId2(ExddFilterElement, pFilter->rxBufferOffset);
            }
            else
            {
                ret &= Can_Std_SetExtendedFilterId2(ExddFilterElement, pFilter->id2);
            }

            ret &= Can_Std_SetExtendedFilterId1(ExddFilterElement, pFilter->id1);
            ret &= Can_Std_SetExtendedFilterConfiguration(ExddFilterElement, pFilter->elmConfig);
            ret &= Can_Std_SetExtendedFilterType(ExddFilterElement, pFilter->type);
        }

        if (TRUE == ret)
        {
            status = CAN_STATUS_OK;
        }
        else
        {
            status = CAN_STATUS_ERROR;
        }
    }
    else
    {
        status = CAN_STATUS_PARAM_ERROR;
    }

    return status;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_ConfigExtendedFilterXIDAM(CAN_NODE *const pNode, uint32 mask)
{
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif
    ret = TRUE;

    ret &= Can_Std_SetExtendedFilterXIDAM(pNode, mask);

    return ret;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
Can_Status Can_Hal_ConfigFifoWatermark(CAN_NODE *const pNode, uint32 fifoType, uint32 watermark)
{
    boolean ret;
    Can_Status status = CAN_STATUS_OK;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    ret = TRUE;

    /* Set the level for FIFO water mark interrupt */
    if (CAN_WATERMARK_TX_EVENT_FIFO == fifoType)
    {
        ret &= Can_Std_SetTxEventFifoWatermarkLevel(pNode, watermark);
    }
    else if (CAN_WATERMARK_RX_FIFO0 == fifoType)
    {
        ret &= Can_Std_SetRxFifo0WatermarkLevel(pNode,watermark);
    }
    else if (CAN_WATERMARK_RX_FIFO1 == fifoType)
    {
        ret &= Can_Std_SetRxFifo1WatermarkLevel(pNode,watermark);
    }
    else {
        status = CAN_STATUS_PARAM_ERROR;
    }

    if (FALSE == ret)
    {
        status = CAN_STATUS_PARAM_ERROR;
    }

    return status;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_ConfigExternalTimestamp(CAN_NODE *const pNode, uint32 timeStampUnit)
{
    boolean ret;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif
    ret = TRUE;

    ret &= Can_Std_ConfigExternalTimeStamp(pNode, timeStampUnit);

    return ret;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_ConfigInternalTimestamp(CAN_NODE *const pNode, uint32 timestampPrescaler)
{
    boolean ret;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    ret = TRUE;

    ret &= Can_Std_SetimestampCounter(pNode, timestampPrescaler);

    return ret;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_StartTimestampCounter(CAN_NODE *const pNode, uint32 timestampOperation)
{
    boolean ret;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif
    ret = TRUE;

    ret &= Can_Std_SetTimestampCounterOperation(pNode, timestampOperation);

    return ret;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_StopTimestampCounter(CAN_NODE *const pNode)
{
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif
    ret = TRUE;

    ret &= Can_Std_SetTimestampCounterOperation(pNode, CAN_TIMESTAMP_OPS_STOP);

    return ret;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
uint32 Can_Hal_GetTimestampCounter(const CAN_NODE *const pNode)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    return Can_Std_GetTimestampCounter(pNode);
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_ResetTimestampCounter(CAN_NODE *const pNode)
{
    boolean ret;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif
   
    ret = Can_Std_ResetTimestampCounter(pNode);

    return ret;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_ConfigTimeoutCounter(CAN_NODE *const pNode, uint32 timeoutOperation, uint32 timeoutPeriod)
{
    boolean ret = TRUE;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    ret &= Can_Std_ConfigTimeoutCounter(pNode, timeoutOperation, timeoutPeriod);

    return ret;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_StartTimeoutCounter(CAN_NODE *const pNode)
{
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif
    ret = TRUE;
    ret &= Can_Std_SetTimeoutCounter(pNode, CAN_ENABLE);
    return ret;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_StopTimeoutCounter(CAN_NODE *const pNode)
{
    boolean ret;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif
    ret = TRUE;
    ret &= Can_Std_SetTimeoutCounter(pNode, CAN_DISABLE);
    return ret;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
uint32 Can_Hal_GetTimeoutCounter(const CAN_NODE *const pNode)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    return Can_Std_GetTimeoutCounter(pNode);
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
void Can_Hal_ResetTimeoutCounter(CAN_NODE *const pNode)
{

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    Can_Std_ResetTimeoutCounter(pNode);
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_ConfigTxDelayCompensation(CAN_NODE *const pNode, uint32 offset, uint32 filter, uint32 enable)
{
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif
    ret = TRUE;

    ret &= Can_Std_ConfigTxDelayCompensation(pNode, offset, filter);

    ret &= Can_Std_SetTxDelayCompensation(pNode, enable);

    return ret;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
Can_Status Can_Hal_EnterInitMode(CAN_NODE *const pNode)
{
    boolean res;
    
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    res = Can_Hal_StartInitialization(pNode);

    return (CAN_ENABLE == res) ? CAN_STATUS_OK : CAN_STATUS_TIMEOUT;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_5 */
/* #Violation: can_hal_c_REF_9 */
Can_Status Can_Hal_ExitInitMode(CAN_NODE *const pNode)
{
    boolean timeout;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    Can_Std_SetCccrInit(pNode, CAN_DISABLE);

    timeout = Can_Hal_CheckTimeout(pNode, Can_Std_GetCccrInit, 0U);

    return (FALSE == timeout) ? CAN_STATUS_OK : CAN_STATUS_TIMEOUT;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
void Can_Hal_WriteMessage(CAN_NODE *const pNode, uint32 txLocation, const CAN_TxHeaderTypeDef *const pTxHeader,
                          const uint8 *const pTxData)
{
    CAN_TXMSG header = {0};

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));

    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != pTxHeader));

    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != pTxData));

    /* Check correct tx-location */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(txLocation <= CAN_TX_FIFOQUEUE));
#endif

    header.T0.B.ESI = pTxHeader->isErrorStateIndicator;

    header.T0.B.XTD = pTxHeader->idType;

    header.T0.B.RTR = pTxHeader->frameType;

    if (CAN_ID_TYPE_STANDARD == pTxHeader->idType)
    {
        header.T0.B.ID = pTxHeader->identifier << 18;
    }
    else
    {
        header.T0.B.ID = pTxHeader->identifier;
    }

    header.T1.B.MM = (uint8)pTxHeader->messageMarker;

    if (0U != Can_Std_GetWideMessageMark(pNode))
    {
        header.T1.B.MM_H = pTxHeader->messageMarker >> 8U;
    }

    header.T1.B.EFC = pTxHeader->eventControl;

    header.T1.B.FDF = pTxHeader->FDFormat;

    header.T1.B.BRS = pTxHeader->bitRateSwitch;

    header.T1.B.DLC = pTxHeader->dataLength;

    Can_Std_AddMessageToTxBuffer(pNode, txLocation, &header, pTxHeader->immediatelySend, pTxData);
}


/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
void Can_Hal_WriteMessageDMA(const CAN_NODE *const pNode, uint32 srcAddress, const CAN_TxHeaderTypeDef *const pTxHeader, uint8 **const pTxData)
{
    CAN_TXMSG *pHeader;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != pTxHeader));
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != pTxData));
#endif
    /* #Violation: can_hal_c_REF_4 */
    pHeader = (CAN_TXMSG *)srcAddress;

    pHeader->T0.B.ESI = pTxHeader->isErrorStateIndicator;

    pHeader->T0.B.XTD = pTxHeader->idType;

    pHeader->T0.B.RTR = pTxHeader->frameType;

    if (CAN_ID_TYPE_STANDARD == pTxHeader->idType)
    {
        pHeader->T0.B.ID = pTxHeader->identifier << 18;
    }
    else
    {
        pHeader->T0.B.ID = pTxHeader->identifier;
    }

    pHeader->T1.B.MM = (uint8)pTxHeader->messageMarker;

    if (0U != Can_Std_GetWideMessageMark(pNode))
    {
        pHeader->T1.B.MM_H = pTxHeader->messageMarker >> 8U;
    }

    pHeader->T1.B.EFC = pTxHeader->eventControl;

    pHeader->T1.B.FDF = pTxHeader->FDFormat;

    pHeader->T1.B.BRS = pTxHeader->bitRateSwitch;

    pHeader->T1.B.DLC = pTxHeader->dataLength;

    /* #Violation: can_hal_c_REF_4 */
    *pTxData = (uint8 *)(srcAddress + 8U);
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
void Can_Hal_FastWriteMessage(CAN_NODE *const pNode, uint32 txLocation,  CAN_TxHeaderPack *const pTxHeader,
                          const uint8 *const pTxData)
{
    boolean pending;
    uint32 txAddress;
    uint32 loopCount;
    uint32 actualDataLen;
    volatile uint32 * pAddr;
    uint32 putIndex;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));

    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != pTxHeader));

    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != pTxData));

    /* Check correct tx-location */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(txLocation <= CAN_TX_FIFOQUEUE));
#endif
    pending = FALSE;

    actualDataLen = Can_Std_DlcToBytes(pTxHeader->B.dataLength);

    txAddress = Can_Std_GetModuleBase(pNode);
    txAddress += ((uint32)pNode->TX.BC.B.TBSA << 2U);

    if (CAN_ID_TYPE_STANDARD == pTxHeader->B.idType)
    {
        pTxHeader->B.identifier = pTxHeader->B.identifier << 18U;
    }

    pTxHeader->B.messageMarkerHigh = pTxHeader->B.messageMarkerHigh << 8U;
    pTxHeader->B.FDFormat &= 1U;

    if (txLocation < CAN_STD_TXLOCATION_FIFO_QUEUE)
    {
        putIndex = txLocation;
    }
    else 
    {
        /* txLocation = CAN_STD_TXLOCATION_FIFO_QUEUE */
        putIndex = pNode->TX.FQS.B.TFQPI;
    }

    txAddress += Can_Std_ElementSzieToBytes(pNode->TX.ESC.B.TBDS) * putIndex;


    if (0U != (pNode->TX.BRP.U & ((uint32)1U << putIndex)))
    {
        pending = TRUE;
    }

    if (FALSE == pending)
    {
        /* #Violation: can_std_c_REF_1 */
        /* #Violation: can_std_c_REF_5 */
        /* #Violation: can_std_c_REF_8 */
        /* #Violation: can_hal_c_REF_12 */
        pAddr = (uint32 *)txAddress;
        pAddr[0] = pTxHeader->T[0];
        pAddr[1] = pTxHeader->T[1];
   
        /* #Violation: can_std_c_REF_1 */
        /* #Violation: can_std_c_REF_5 */
        /* #Violation: can_std_c_REF_8 */
        /* #Violation: can_hal_c_REF_12 */
        pAddr = (uint32 *)(txAddress + 8U);

        /* write data into the data section of Tx Buffer element  */
        for(loopCount = 0U; loopCount < actualDataLen; loopCount += 4U)
        {
            *pAddr = (((uint32)pTxData[loopCount + 3U] << 24U) |
                     ((uint32)pTxData[loopCount + 2U] << 16U)  |
                     ((uint32)pTxData[loopCount + 1U] << 8U)   |
                     ((uint32)pTxData[loopCount]));
            pAddr++;
        }

        /* TXBAR bits are set only for those Tx Buffers configured via TXBC. */
        pNode->TX.BAR.U = ((uint32)1U << putIndex);
    }
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_GetTxBufferPendingStatus(const CAN_NODE *const pNode, uint32 bufferIndex)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));

    /* Check buffer index */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(bufferIndex <= CAN_TX_BUFFER31));
#endif

    return ((Can_Std_GetTxBufferPending(pNode) & ((uint32)1U << bufferIndex)) > 0U) ? TRUE : FALSE;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_GetTxBufferTransFinishedStatus(const CAN_NODE *const pNode, uint32 bufferIndex)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));

    /* Check buffer index */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(bufferIndex <= CAN_TX_BUFFER31));
#endif

    return ((Can_Std_GetTxBufferTransOccured(pNode) & ((uint32)1U << bufferIndex)) > 0U) ? TRUE : FALSE;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_GetTxBufferAbortFinishedStatus(const CAN_NODE *const pNode, uint32 bufferIndex)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));

    /* Check buffer index */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(bufferIndex <= CAN_TX_BUFFER31));
#endif

    return ((Can_Std_GetTxBufferAbortFinished(pNode) & ((uint32)1U << bufferIndex)) > 0U) ? TRUE : FALSE;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
void Can_Hal_TxBufferRequest(CAN_NODE *const pNode, uint32 bufferIndex)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));

    /* Check buffer index */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(bufferIndex <= CAN_TX_BUFFER31));
#endif

    Can_Std_TxBufferRequest(pNode, ((uint32)1U << bufferIndex));
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
void Can_Hal_AbortTxRequest(CAN_NODE *const pNode, uint32 bufferIndex)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));

    /* Check buffer index */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(bufferIndex <= CAN_TX_BUFFER31));
#endif
    Can_Std_AbortTxRequest(pNode, ((uint32)1U << bufferIndex));
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
void Can_Hal_ClearMessageFlag(CAN_NODE *const pNode)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    Can_Std_ClearMessageFlag(pNode);
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_GetRxBufferMessageAvailableStatus(const CAN_NODE *const pNode, uint32 bufferIndex)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));

    /* Check dedicated buffer index */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(bufferIndex <= CAN_RX_BUFFER63));
#endif

    return ((Can_Std_GetRxBufferMessageAvailable(pNode) & ((uint64)1U << bufferIndex)) > 0U) ? TRUE : FALSE;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
uint64 Can_Hal_GetRxBufferMessageIndex(const CAN_NODE *const pNode)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    return Can_Std_GetRxBufferMessageAvailable(pNode);
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
Can_Status Can_Hal_ReadMessage(CAN_NODE *const pNode, uint32 rxLocation, CAN_RxHeaderTypeDef *const pRxHeader, uint8 *const pRxData)
{
    Can_Status status;

    CAN_RXMSG header = {0};

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));

    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != pRxHeader));

    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != pRxData));
#endif

    status = CAN_STATUS_OK;

    if (rxLocation <= CAN_STD_RXLOCATION_FIFO1)
    {
        /* Read by DMU or CAN buffer */
        Can_Std_GetRxMessage(pNode, rxLocation, &header, pRxData);

        pRxHeader->isErrorStateIndicator = header.R0.B.ESI;

        pRxHeader->idType    = header.R0.B.XTD;

        pRxHeader->frameType = header.R0.B.RTR;

        if (CAN_ID_TYPE_STANDARD == pRxHeader->idType)
        {
            pRxHeader->identifier = header.R0.B.ID >> 18;
        }
        else
        {
            pRxHeader->identifier = header.R0.B.ID;
        }

        pRxHeader->isFilterMatchingFrame = header.R1.B.ANMF;

        pRxHeader->filterIndex    = header.R1.B.FIDX;

        pRxHeader->FDFormat       = header.R1.B.FDF;

        pRxHeader->dataLength     = Can_Std_DlcToBytes(header.R1.B.DLC);

        pRxHeader->bitRateSwitch  = header.R1.B.BRS;

        pRxHeader->rxTimestamp    = header.R1.B.RXTS;
    }
    else
    {
        status = CAN_STATUS_PARAM_ERROR;
    }

    return status;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
void Can_Hal_ReadMessageDMA(uint32 srcAddress, CAN_RxHeaderTypeDef *const pRxHeader, uint8 **const pRxData)
{
    CAN_RXMSG const volatile *pSrcHeader;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != pRxHeader));
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != pRxData));
#endif

    /* #Violation: can_hal_c_REF_4 */
    pSrcHeader = (CAN_RXMSG*)srcAddress;

    pRxHeader->isErrorStateIndicator = pSrcHeader->R0.B.ESI;

    pRxHeader->idType = pSrcHeader->R0.B.XTD;

    pRxHeader->frameType = pSrcHeader->R0.B.RTR;

    if (CAN_ID_TYPE_STANDARD == pRxHeader->idType)
    {
        pRxHeader->identifier = pSrcHeader->R0.B.ID >> 18U;
    }
    else
    {
        pRxHeader->identifier = pSrcHeader->R0.B.ID;
    }

    pRxHeader->isFilterMatchingFrame = pSrcHeader->R1.B.ANMF;

    pRxHeader->filterIndex = pSrcHeader->R1.B.FIDX;

    pRxHeader->FDFormat = pSrcHeader->R1.B.FDF;

    pRxHeader->dataLength = Can_Std_DlcToBytes(pSrcHeader->R1.B.DLC);

    pRxHeader->bitRateSwitch = pSrcHeader->R1.B.BRS;

    pRxHeader->rxTimestamp = pSrcHeader->R1.B.RXTS;

    /* #Violation: can_hal_c_REF_4 */
    *pRxData = (uint8 *)(srcAddress + 8U);
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
Can_Status Can_Hal_FastReadMessage(CAN_NODE *const pNode, uint32 rxLocation, CAN_RxHeaderPack *const pRxHeader, uint8 *const pRxData)
{
    Can_Status status;

    uint32 rxAddress;

    uint32 const volatile *pAddr32Bit;

    uint32 rxLocationTmp;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));

    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != pRxHeader));

    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != pRxData));

    /* Check correct rx-location */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(rxLocation <= CAN_STD_RXLOCATION_FIFO1));
#endif

    status = CAN_STATUS_OK;

    rxLocationTmp = rxLocation;

    rxAddress = Can_Std_GetModuleBase(pNode);

    if (rxLocation <= CAN_STD_RXLOCATION_BUFFER_63)
    {
        rxAddress += ((uint32)pNode->RX.BC.B.RBSA << 2U) + (Can_Std_ElementSzieToBytes(pNode->RX.ESC.B.RBDS) * rxLocationTmp);

        /* #Violation: can_std_c_REF_1 */
        /* #Violation: can_std_c_REF_5 */
        /* #Violation: can_std_c_REF_8 */
        /* #Violation: can_hal_c_REF_12 */
        pAddr32Bit = (uint32 *)rxAddress;

        pRxHeader->R[0] = pAddr32Bit[0];
        pRxHeader->R[1] = pAddr32Bit[1];
        
        /* #Violation: can_std_c_REF_1 */
        /* #Violation: can_std_c_REF_5 */
        /* #Violation: can_std_c_REF_8 */
        /* #Violation: can_hal_c_REF_12 */
        pAddr32Bit = (uint32 *)(rxAddress + 8U);

        /* #Violation: can_hal_c_REF_12 */
        Can_Hal_ArrayCopy32NByte(pAddr32Bit, (uint32 *)(void*)pRxData, 64U);

        if (rxLocationTmp < CAN_STD_RXLOCATION_BUFFER_32)
        {
            pNode->NDAT1.U = ((uint32)1U << rxLocationTmp);
        }
        else
        {
            rxLocationTmp -= 32U;
            pNode->NDAT2.U = ((uint32)1U << rxLocationTmp);
        }
    }
    else if (rxLocation == CAN_STD_RXLOCATION_FIFO0)
    {
        /* Check that the Rx FIFO 0 is full & overwrite mode is on*/
        if ((0U != pNode->RX.F0S.B.F0F) && (0U != pNode->RX.F0C.B.F0OM))
        {
            /* When overwrite status is on discard first message in FIFO */
            pNode->RX.F0A.B.F0AI = pNode->RX.F0S.B.F0GI;
        }

        rxLocationTmp = pNode->RX.F0S.B.F0GI;

        rxAddress += ((uint32)pNode->RX.F0C.B.F0SA << 2U) + (Can_Std_ElementSzieToBytes(pNode->RX.ESC.B.F0DS) * rxLocationTmp);
        
        /* #Violation: can_std_c_REF_1 */
        /* #Violation: can_std_c_REF_5 */
        /* #Violation: can_std_c_REF_8 */
        /* #Violation: can_hal_c_REF_12 */
        pAddr32Bit = (uint32 *)rxAddress;

        pRxHeader->R[0] = pAddr32Bit[0];
        pRxHeader->R[1] = pAddr32Bit[1];
        /* #Violation: can_std_c_REF_1 */
        /* #Violation: can_std_c_REF_5 */
        /* #Violation: can_std_c_REF_8 */
        /* #Violation: can_hal_c_REF_12 */
        pAddr32Bit = (uint32 *)(rxAddress + 8U);

        /* #Violation: can_hal_c_REF_12 */
        Can_Hal_ArrayCopy32NByte(pAddr32Bit, (uint32 *)(void*)pRxData, 64U);

        /* ack */
        pNode->RX.F0A.B.F0AI = rxLocationTmp;
    }
    else if (rxLocation == CAN_STD_RXLOCATION_FIFO1)
    {
        /* Check that the Rx FIFO 1 is full and overwrite mode is on*/
        if ((0U != pNode->RX.F1S.B.F1F) && (0U != pNode->RX.F1C.B.F1OM))
        {
            /* When overwrite status is on discard first message in FIFO */
            pNode->RX.F1A.B.F1AI = pNode->RX.F1S.B.F1GI;
        }

        rxLocationTmp = pNode->RX.F1S.B.F1GI;

        rxAddress += ((uint32)pNode->RX.F1C.B.F1SA << 2U) + (Can_Std_ElementSzieToBytes(pNode->RX.ESC.B.F1DS) * rxLocationTmp);

        /* #Violation: can_std_c_REF_1 */
        /* #Violation: can_std_c_REF_5 */
        /* #Violation: can_std_c_REF_8 */
        /* #Violation: can_hal_c_REF_12 */
        pAddr32Bit = (uint32 *)rxAddress;

        pRxHeader->R[0] = pAddr32Bit[0];
        pRxHeader->R[1] = pAddr32Bit[1];
        /* #Violation: can_std_c_REF_1 */
        /* #Violation: can_std_c_REF_5 */
        /* #Violation: can_std_c_REF_8 */
        /* #Violation: can_hal_c_REF_12 */
        pAddr32Bit = (uint32 *)(rxAddress + 8U);

        /* #Violation: can_hal_c_REF_12 */
        Can_Hal_ArrayCopy32NByte(pAddr32Bit, (uint32 *)(void*)pRxData, 64U);

        /* ack */
        pNode->RX.F1A.B.F1AI = rxLocationTmp;
    }
    else
    {
        status = CAN_STATUS_ERROR;
    }

    pRxHeader->B.FDFormat &= 1U;
    if (CAN_ID_TYPE_STANDARD == pRxHeader->B.idType)
    {
        pRxHeader->B.identifier = pRxHeader->B.identifier >> 18U;
    }

    return status;
}


/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
void Can_Hal_ReadTxEvent(CAN_NODE *const pNode, CAN_TxEvenHeaderTypeDef *const pEvHeader)
{
    CAN_TXEVENT header;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));

    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != pEvHeader));
#endif

    Can_Std_GetTxEvent(pNode, &header);

    pEvHeader->isErrorStateIndicator = header.E0.B.ESI;

    pEvHeader->idType = header.E0.B.XTD;

    pEvHeader->frameType = header.E0.B.RTR;

    if (CAN_ID_TYPE_STANDARD == pEvHeader->idType)
    {
        pEvHeader->identifier = header.E0.B.ID >> 18U;
    }
    else
    {
        pEvHeader->identifier = header.E0.B.ID;
    }

    pEvHeader->FDFormat = header.E1.B.FDF;

    pEvHeader->dataLength = Can_Std_DlcToBytes(header.E1.B.DLC);

    pEvHeader->bitRateSwitch = header.E1.B.BRS;

    pEvHeader->txTimestamp = header.E1.B.TXTS;

    pEvHeader->messageMarker = header.E1.B.MM;

    if (0U != Can_Std_GetWideMessageMark(pNode))
    {
        pEvHeader->txTimestamp = 0;

        pEvHeader->messageMarker += (uint16) (header.E1.B.TXTS & 0xFF00U);
    }

    pEvHeader->eventType = header.E1.B.ET;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
void Can_Hal_ReadTxEventDMA(const CAN_NODE *const pNode, uint32 srcAddress, CAN_TxEvenHeaderTypeDef *const pEvHeader)
{
    CAN_TXEVENT const volatile *pHeader;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));

    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != pEvHeader));
#endif
    /* #Violation: can_hal_c_REF_4 */
    pHeader = (CAN_TXEVENT *)srcAddress;

    pEvHeader->isErrorStateIndicator = pHeader->E0.B.ESI;

    pEvHeader->idType = pHeader->E0.B.XTD;

    pEvHeader->frameType = pHeader->E0.B.RTR;

    if (CAN_ID_TYPE_STANDARD == pEvHeader->idType)
    {
        pEvHeader->identifier = pHeader->E0.B.ID >> 18U;
    }
    else
    {
        pEvHeader->identifier = pHeader->E0.B.ID;
    }

    pEvHeader->FDFormat = pHeader->E1.B.FDF;

    pEvHeader->dataLength = Can_Std_DlcToBytes(pHeader->E1.B.DLC);

    pEvHeader->bitRateSwitch = pHeader->E1.B.BRS;

    pEvHeader->txTimestamp = pHeader->E1.B.TXTS;

    pEvHeader->messageMarker = pHeader->E1.B.MM;

    if (0U != Can_Std_GetWideMessageMark(pNode))
    {
        pEvHeader->txTimestamp = 0;

        pEvHeader->messageMarker += (uint16) (pHeader->E1.B.TXTS & 0xFF00U);
    }

    pEvHeader->eventType = pHeader->E1.B.ET;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
void Can_Hal_GetHighPriorityMessageStatus(const CAN_NODE *const pNode, CAN_HpMsgStatusTypeDef *const pHpMsgStatus)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));

    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != pHpMsgStatus));
#endif
    Can_Std_GetHighProotityStatus(pNode,
                                  &pHpMsgStatus->filterList,
                                  &pHpMsgStatus->filterIndex,
                                  &pHpMsgStatus->messageStorage,
                                  &pHpMsgStatus->messageIndex);
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
uint32 Can_Hal_GetProtocolStatus(const CAN_NODE *const pNode)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    return Can_Std_GetProtocolStatus(pNode);
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
uint32 Can_Hal_GetOperationStatus(const CAN_NODE *const pNode)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    return Can_Std_GetCccrInit(pNode);
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
void Can_Hal_GetErrorCounters(const CAN_NODE *const pNode, CAN_ErrorCountersTypeDef *const pErrorCounters)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != pErrorCounters));
#endif
    Can_Std_GetErrorCounters(pNode,
                             &pErrorCounters->txErrorCnt,
                             &pErrorCounters->rxErrorCnt,
                             &pErrorCounters->rxErrorPassive,
                             &pErrorCounters->errorLogging);
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
uint32 Can_Hal_GetTxEventFifoLevel(const CAN_NODE *const pNode)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    return Can_Std_GetTxEventFifoLevel(pNode);
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
uint32 Can_Hal_GetRxFifo0FillLevel(const CAN_NODE *const pNode)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif
    return Can_Std_GetRxFifo0FillLevel(pNode);
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
uint32 Can_Hal_GetRxFifo1FillLevel(const CAN_NODE *const pNode)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif
    return Can_Std_GetRxFifo1FillLevel(pNode);
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
uint32 Can_Hal_GetTxFifoFreeLevel(const CAN_NODE *const pNode)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif
    return Can_Std_GetTxFifoFreeLevel(pNode);
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
void Can_Hal_GetFifoStatus(const CAN_NODE *const pNode, Can_FifoType fifoType, Can_FifoStatus* fifoSta)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != fifoSta));
#endif

    switch (fifoType)
    {
    case CAN_FIFO_TYPE_RXFIFO0:
        fifoSta->fifoFreeLevel = pNode->RX.F0S.B.F0FL;
        fifoSta->fifoFull = pNode->RX.F0S.B.F0F;
        fifoSta->fifoGettIdx = pNode->RX.F0S.B.F0GI;
        fifoSta->fifoPutIdx =pNode->RX.F0S.B.F0PI;
        fifoSta->fifoMsgLost = pNode->RX.F0S.B.RF0L;
        break;
    
    case CAN_FIFO_TYPE_RXFIFO1:
        fifoSta->fifoFreeLevel = pNode->RX.F1S.B.F1FL;
        fifoSta->fifoFull = pNode->RX.F1S.B.F1F;
        fifoSta->fifoGettIdx = pNode->RX.F1S.B.F1GI;
        fifoSta->fifoPutIdx =pNode->RX.F1S.B.F1PI;
        fifoSta->fifoMsgLost = pNode->RX.F1S.B.RF1L;
        break;

    case CAN_FIFO_TYPE_TXEVENTFIFO:
        fifoSta->fifoFreeLevel = pNode->TX.EFS.B.EFFL;
        fifoSta->fifoFull = pNode->TX.EFS.B.EFF;
        fifoSta->fifoGettIdx = pNode->TX.EFS.B.EFGI;
        fifoSta->fifoPutIdx =pNode->TX.EFS.B.EFPI;
        fifoSta->fifoMsgLost = pNode->TX.EFS.B.TEFL;
        break;

    case CAN_FIFO_TYPE_TXFIFO:
        fifoSta->fifoFreeLevel = pNode->TX.FQS.B.TFFL;
        fifoSta->fifoFull = pNode->TX.FQS.B.TFQF;
        fifoSta->fifoGettIdx = pNode->TX.FQS.B.TFGI;
        fifoSta->fifoPutIdx =pNode->TX.FQS.B.TFQPI;
        fifoSta->fifoMsgLost = FALSE;
        break;

    default:
        fifoSta->fifoFreeLevel = 0xffU;
        fifoSta->fifoFull = 0xffU;
        fifoSta->fifoGettIdx = 0xffU;
        fifoSta->fifoPutIdx = 0xffU;
        fifoSta->fifoMsgLost = FALSE;
        break;
    }
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
uint32 Can_Hal_IsRestrictedOperationMode(const CAN_NODE *const pNode)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    return Can_Std_GetCccrRestricted(pNode);
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_ExitRestrictedOperationMode(CAN_NODE *const pNode)
{
    boolean ret;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    ret = Can_Std_SetCccrRestricted(pNode, CAN_DISABLE);

    return ret;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_SelectInterruptLine(CAN_NODE *const pNode, uint32 it, uint32 itLine)
{
    uint32 tempIt;
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));

    /* Check interrupt line */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(itLine <= CAN_IT_LINE1));
#endif
    tempIt = it;
    tempIt &= CAN_IT_MASK;

    ret = Can_Std_SetITLine(pNode, tempIt, itLine);

    return ret;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_SelectRouterInterruptLine(CAN_NODE *const pNode, uint32 it, uint32 itLine)
{
    boolean ret = TRUE;
    
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));

    /* Check correct the router IT line */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(itLine <= CAN_IT_ROUTER_LINE15));
#endif

    ret &= Can_Std_SetITRouterLine(pNode, (it & CAN_IT_MASK), itLine);
    return ret;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_EnableRouterInterrupt(CAN_NODE *const pNode, uint32 it, uint32 bufferIndexes)
{
    boolean ret = TRUE;
    
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif
    ret &= Can_Std_ActivateRouterInterrupt(pNode, (it & CAN_IT_MASK), bufferIndexes);
    return ret;  
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_DisableRouterInterrupt(CAN_NODE *const pNode, uint32 it)
{
    boolean ret = TRUE;
    
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif
    ret &= Can_Std_DeactivateRouterInterrupt(pNode, (it & CAN_IT_MASK));
    return ret;   
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
uint32 Can_Hal_GetInterruptFlag(const CAN_NODE *const pNode)
{
    uint32 irVaule;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif
    irVaule = Can_Std_GetInterruptFlag(pNode);

    irVaule &= CAN_IT_MASK;

    return irVaule;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
void Can_Hal_ClearInterruptFlag(CAN_NODE *const pNode, uint32 it)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    Can_Std_ClearInterruptFlag(pNode, (it & CAN_IT_MASK));
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_EnableInterrupt(CAN_NODE *const pNode, uint32 it, uint32 bufferIndexes)
{
    boolean ret;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif
    
    ret = Can_Std_ActivateNotification(pNode, (it&CAN_IT_MASK), bufferIndexes);

    return ret;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_DisableInterrupt(CAN_NODE *const pNode, uint32 it)
{
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    ret = Can_Std_DeactivateNotification(pNode, (it&CAN_IT_MASK));

    return ret;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
Can_Status Can_Hal_GetDmuAddress(const CAN_NODE *const pNode, uint32 dmuAddressType, uint32 *const elementAddress)
{
    Can_Status status;

    uint32 address;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));

    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    Assert((boolean)(NULL_PTR != elementAddress));
#endif
    
    address = Can_Std_DmuGetAddress(pNode, dmuAddressType);

    if (0U != address)
    {
        status = CAN_STATUS_OK;

        *elementAddress = address;
    }
    else
    {
        status = CAN_STATUS_PARAM_ERROR;
    }

    return status;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_DmuRequestLine(CAN_NODE *const pNode, uint32 dmuRequestType, boolean enable)
{
    boolean ret;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    ret = TRUE;

    ret &= Can_Std_SetDmuRequest(pNode, dmuRequestType, enable);

    return ret;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
uint32 Can_Hal_GetDmuInterruptFlag(const CAN_NODE *const pNode)
{
    uint32 irValue;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    irValue = Can_Std_GetDmuIR(pNode);

    irValue &= CAN_IT_DMU_MASK;

    return irValue;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
void Can_Hal_ClearDmuInterruptFlag(CAN_NODE *const pNode, uint32 it)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    Can_Std_ClearDmuIR(pNode, (it & CAN_IT_DMU_MASK));
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_EnableDmuInterrupt(CAN_NODE *const pNode, uint32 it)
{
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    ret = Can_Std_SetDmuIE(pNode, (it & CAN_IT_DMU_MASK), CAN_ENABLE);

    return ret;
}

/* #Violation: can_hal_c_REF_1 */
/* #Violation: can_hal_c_REF_3 */
boolean Can_Hal_DisableDmuInterrupt(CAN_NODE *const pNode, uint32 it)
{
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the Pointer is null pointer */
    /* #Violation: can_hal_c_REF_3 */
    /* #Violation: can_hal_c_REF_12 */
    /* #Violation: can_hal_c_REF_13 */
    Assert((boolean)(CHECK_CANNODE_BASE(pNode)));
#endif

    ret = Can_Std_SetDmuIE(pNode, (it & CAN_IT_DMU_MASK), CAN_DISABLE);

    return ret;
}

#define CAN_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: can_hal_c_REF_8 */
#include "Can_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
