/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.E
 * FileName:    intc_hal.c
 * Author:      01369
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all functions of INTC module.
 *********************************************************************************************************************/

/*
*#Violation Summary
*
*#intc_hal_c_REF_1:MISRAC2012-Dir-1.1;
* Justification: Inline assembly for CPU-specific operations.
*
*#intc_hal_c_REF_2:MISRAC2012-Dir-4.3;
* Justification: Mixing inline assembly with C code reduces code complexity.
*
*#intc_hal_c_REF_3:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access.
*
*#intc_hal_c_REF_4:MISRAC2012-Rule-2.2;
* Justification: Value used in assembly code.
*
*#intc_hal_c_REF_5:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*#intc_hal_c_REF_6:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
*#intc_hal_c_REF_7:MISRAC2012-Rule-10.5;
* Justification: Limitation of Coretex-R52+ Core; Boolean can only be representes as unit8.
*
*#intc_hal_c_REF_8:MISRAC2012-Dir-4.9;
* Justification: Function like macros are used to reduce code complexity.
*
*#intc_hal_c_REF_9:MISRAC2012-Dir-1.2; 
* Justification: Inline assembly for CPU-specific operations.
*
*#intc_hal_c_REF_10:MISRAC2012-Dir-4.2;
* Justification: Inline assembly for CPU-specific operations.
*
*#intc_hal_c_REF_11:MISRAC2012-Rule-20.1;
*Justification: Imposes the specification of the section in which certain parts of the driver must be placed.
*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "multicore.h"
#include "Platform_Types.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
#include "safewdt_hal.h"
#include "intc_register.h"
#include "intc_hal.h"
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/* All alarm */
/* #Violation: intc_hal_c_REF_5 */
#define INTC_ALL_ALARM  (0x3FFFFFFU)
/* Minimum peak value of IRQ group priority */
/* #Violation: intc_hal_c_REF_5 */
#define INTC_MINPEAK_IRQ_GROUP_PRIORITY (1U)

/* #Violation: intc_hal_c_REF_5 */
#define INTC_SOFTINT_MAXTIMEOUT     (0xFFFFU)
/* #Violation: intc_hal_c_REF_5 */
#define INTC_SOFTINT_RESOURCE_BUSY  (0x00U)
#define INTC_SOFTINT_RESOURCE_FREE  (0x03U)

/* Enable read clear */
#define INTC_SOFTINT_ENABLE_RDCLEAR (0x03U)
#define INTC_SEMAP_SEMFPSW          (0x5A5A0000U)
#define INTC_SFINTCR_SFINTPSW       (0x55AA0000U)

#define INTC_SOFTINT_DISABLE        (0x00U)
#define INTC_SOFTINT_ENABLE         (0x03U)

/* MAX core number for one GIC */
/* #Violation: intc_hal_c_REF_5 */
#define MAX_CORE_NUM_GIC            (0x2U) 

/* Maximum number of SGIs and PPIs */
/* #Violation: intc_hal_c_REF_5 */
#define INTC_MAX_INT_NUMBER         (992U)
/* Maximum value of SPI intID */
/* #Violation: intc_hal_c_REF_5 */
#define INTC_MAX_SPI_ID             (991U)
/* Minimum value of SPI intID */
/* #Violation: intc_hal_c_REF_5 */
#define INTC_MIN_SPI_ID             (32U)
/* Maximum value of PPI intID */
/* #Violation: intc_hal_c_REF_5 */
#define INTC_MAX_PPI_ID             (31U)
/* Minimum value of PPI intID */
/* #Violation: intc_hal_c_REF_5 */
#define INTC_MIN_PPI_ID             (16U)
/* Maximum value of SGI intID */
/* #Violation: intc_hal_c_REF_5 */
#define INTC_MAX_SGI_ID             (15U)
/* Maximun value of group */
/* #Violation: intc_hal_c_REF_5 */
#define INTC_MAX_GROUP              (1U)
/* Maximun value of trigger method */
/* #Violation: intc_hal_c_REF_5 */
#define INTC_MAX_TRIGGER_METHOD     (1U)





#define INTC_START_SEC_CODE_ASIL_D_GLOBAL
#include "Intc_MemMap.h"
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:     Intc_Hal_InstallInternalInterrupt
 * Description:  Install a PPI or SGI.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pGic: Pointer to GIC module
 *               coreNoForGic: Core number for this GIC
 *               pIntCfg: Pointer to interrupt config structure
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/10/02    01200      Create
 *********************************************************************************************************************/
static void Intc_Hal_InstallInternalInterrupt(INTC_GIC_MODULE *const pGic, uint32 coreNoForGic, const Intc_InterruptConfig *const pIntCfg);

/**********************************************************************************************************************
 * Function:     Intc_Hal_InstallPeripheralInterrupt
 * Description:  Install a SPI.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pGic: Pointer to GIC module
 *               coreNoForGic: Core number for this GIC
 *               pIntCfg: Pointer to interrupt config structure
 * Inout:        None
 * Output:       None
 * Return:       boolean: if peripheral interrupt is set, the stat is TRUE
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/10/02    01200      Create
 *********************************************************************************************************************/
static boolean Intc_Hal_InstallPeripheralInterrupt(INTC_GIC_MODULE *const pGic, uint32 coreNoForGic, const Intc_InterruptConfig *const pIntCfg);

/**********************************************************************************************************************
 * Function:     Intc_Hal_SetGtmtrigger
 * Description:  Set GTM interrupt trigger mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        intID: Interrupt ID
 *               triggerMethod: Trigger method, level or edge
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:
 * History:
 *  Date          Author    Modified
 *  2024/08/12    00930      Create
 *********************************************************************************************************************/
static boolean Intc_Hal_SetGtmtrigger(Intc_IntID intID, Intc_TriggerMethod triggerMethod);

/**********************************************************************************************************************
 * Function:     Intc_Hal_GenerateSpiSoftwareInterrupt
 * Description:  Generate SPI Software Interrupt from a core to the target core(s)
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        intID: The INTID of interrupt
 *               targetCore: The target core(s) of the software interrupt.
 * Inout:        None
 * Output:       None
 * Return:       Intc_ErrorFlag: Error indicating flag
 * Others:       None
 * History:
 * Date          Author    Modified
 * 2023/05/15    01200      Create
 *********************************************************************************************************************/
static Intc_ErrorFlag Intc_Hal_GenerateSpiSoftwareInterrupt(Intc_IntID intID, Intc_TargetCore targetCore);

/**********************************************************************************************************************
 * Function:     Intc_Hal_InitializeSpiSoftwareInterrupt
 * Description:  Initialize the SPI Software Interrupt according to the input parameters
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        intID: The INTID of interrupt
 *               coreID: Core ID
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/08/08    00930      Create
 *********************************************************************************************************************/
static boolean Intc_Hal_InitializeSpiSoftwareInterrupt(Intc_IntID intID, MultiCoreID coreID);

/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
static void Intc_Hal_InstallInternalInterrupt(INTC_GIC_MODULE *const pGic, uint32 coreNoForGic,
                                             const Intc_InterruptConfig *const pIntCfg)
{
    uint32 registerShift;
    uint32 bitShift;
    /* Set interrupt group */
    pGic->REDISTRIBUTOR[coreNoForGic].GICRIGROUPR |= ((uint32)(pIntCfg->group) << pIntCfg->intID);

    /* Set interrupt priority */
    /* Calculate the register offset, 4 interrupts per register */
    registerShift = (uint32)(pIntCfg->intID) >> 2U;
    /* Calculate the bit offset */
    bitShift = ((uint32)(pIntCfg->intID) % 4U) << 3U;
    /* Set priority, 4 bits per interrupt */
    pGic->REDISTRIBUTOR[coreNoForGic].GICRIPRIORITY[registerShift] |= ((uint32)(pIntCfg->priority) << (3U + bitShift));

    /* The interrupt ID is not SGI */
    if(pIntCfg->intID > INTC_MAX_SGI_ID)
    {
        /* Calculate the bit offset, 2 bits per interrupt */
        bitShift = ((uint32)pIntCfg->intID - INTC_MIN_PPI_ID) << 1U;
        /* Set trigger method, only the higher bit of 2 bits is valid */
        pGic->REDISTRIBUTOR[coreNoForGic].GICRICFGR1 |= ((uint32)(pIntCfg->triggerMethod) << (1U + bitShift));
    }

    /* Enable the interrupt */
    if(TRUE == pIntCfg->enable)
    {
        pGic->REDISTRIBUTOR[coreNoForGic].GICRISENABLER = (uint32)1U << (uint32)(pIntCfg->intID);
    }
}

static boolean Intc_Hal_SetGtmtrigger(Intc_IntID intID, Intc_TriggerMethod triggerMethod)
{
    uint32 registerShift;
    uint32 bitShift;
    uint32 expValue;
    boolean ret;

#if defined(THA6_THA6412)    
    uint32 iCount;
    const uint16 levedgsel9Value[INTC_INTID_GTM_LEVEDGSEL9_0][INTC_INTID_GTM_LEVEDGSEL9_1] =
    {   /* INTID, BIT of LEVEDGSEL9 register */
        {INTC_INTID_GTM_MCS5_IRQ_5, 17U}, {INTC_INTID_GTM_MCS5_IRQ_6, 18U}, {INTC_INTID_GTM_MCS5_IRQ_7, 19U},
        {INTC_INTID_GTM_MCS6_IRQ_0, 20U}, {INTC_INTID_GTM_MCS6_IRQ_1, 21U}, {INTC_INTID_GTM_MCS6_IRQ_2, 22U},
        {INTC_INTID_GTM_MCS6_IRQ_3, 23U}, {INTC_INTID_GTM_MCS6_IRQ_4, 24U}, {INTC_INTID_GTM_MCS6_IRQ_5, 25U},
        {INTC_INTID_GTM_MCS6_IRQ_6, 26U}, {INTC_INTID_GTM_MCS6_IRQ_7, 27U}, {INTC_INTID_GTM_MCS7_IRQ_0, 28U},
        {INTC_INTID_GTM_MCS7_IRQ_1, 29U}, {INTC_INTID_GTM_MCS7_IRQ_2, 30U}, {INTC_INTID_GTM_MCS7_IRQ_3, 31U}
    };

    const uint16 levedgsel10Value[INTC_INTID_GTM_LEVEDGSEL10_0][INTC_INTID_GTM_LEVEDGSEL10_1] =
    {   /* INTID, BIT of LEVEDGSEL10 register */
        {INTC_INTID_GTM_MCS7_IRQ_4, 0U}, {INTC_INTID_GTM_MCS7_IRQ_5, 1U}, {INTC_INTID_GTM_MCS7_IRQ_6, 2U},
        {INTC_INTID_GTM_MCS7_IRQ_7, 3U}, {INTC_INTID_GTM_MCS4_S_IRQ, 4U}, {INTC_INTID_GTM_MCS5_S_IRQ, 5U},
        {INTC_INTID_GTM_MCS6_S_IRQ, 6U}, {INTC_INTID_GTM_MCS7_S_IRQ, 7U}, {INTC_INTID_GTM_MCSW_ORED_INT, 8U}
    };
#endif /* End THA6_THA6412 */
    ret = TRUE;
    /* Interrupt ID is equal or great than Gtm error interrupt, and equal or less than Gtm time3 IRQ5 interrupt */
    if((intID >= INTC_INTID_GTM_ERR_IRQ) && (intID <= INTC_INTID_GTM_TIM3_IRQ_5))
    { 
        /* LEVEDGESEL(0~6)*/
        /* Calculate the register offset, 32 interrupts per register */
        registerShift = ((uint32)intID - INTC_INTID_GTM_ERR_IRQ) >> 5U;
        /* Calculate the bit offset, 1 bit per interrupt */
        bitShift = ((uint32)intID - INTC_INTID_GTM_ERR_IRQ) % 32U;
        /* Clear the corresponding bit */
        /* #Violation: intc_hal_c_REF_6 */
        expValue = INTC_HAL->LEVEDGSEL0[registerShift];
        expValue &= ~((uint32)1U << bitShift);
        /* #Violation: intc_hal_c_REF_6 */
        INTC_HAL->LEVEDGSEL0[registerShift] = expValue;
        /* Check register readback check value meet expectation */
        /* #Violation: intc_hal_c_REF_6 */
        ret = Intc_Register_ReadBack_Check(ret, expValue, INTC_HAL->LEVEDGSEL0[registerShift]);
        
        /* Set trigger method in INTC module */
        /* #Violation: intc_hal_c_REF_6 */
        expValue = INTC_HAL->LEVEDGSEL0[registerShift];
        expValue |= ((uint32)triggerMethod << bitShift);
        /* #Violation: intc_hal_c_REF_6 */
        INTC_HAL->LEVEDGSEL0[registerShift] = expValue;
        /* Check register readback check value meet expectation */
        /* #Violation: intc_hal_c_REF_6 */
        ret = Intc_Register_ReadBack_Check(ret, expValue, INTC_HAL->LEVEDGSEL0[registerShift]);
    }
#if defined(THA6_THA6412)
    /* Interrupt ID is equal or great than Gtm time3 IRQ6 interrupt, and equal or less than Gtm MCS5 IRQ4 interrupt */
    else if((intID >= INTC_INTID_GTM_TIM3_IRQ_6) && (intID <= INTC_INTID_GTM_MCS5_IRQ_4))
    {   /* LEVEDGESEL(7~8,or part 9)*/
        /* Calculate the register offset, 32 interrupts per register */
        registerShift = ((uint32)intID - INTC_INTID_GTM_TIM3_IRQ_6) >> 5U;
        /* Calculate the bit offset, 1 bit per interrupt */
        bitShift = ((uint32)intID - INTC_INTID_GTM_TIM3_IRQ_6) % 32U;
        /* Clear the corresponding bit */
        /* #Violation: intc_hal_c_REF_6 */
        expValue = INTC_HAL->LEVEDGSEL1[registerShift];
        expValue &= ~((uint32)1U << bitShift);
        /* #Violation: intc_hal_c_REF_6 */
        INTC_HAL->LEVEDGSEL1[registerShift] = expValue;
        /* Check register readback check value meet expectation */
        /* #Violation: intc_hal_c_REF_6 */
        ret = Intc_Register_ReadBack_Check(ret, expValue, INTC_HAL->LEVEDGSEL1[registerShift]);
    
        /* Set trigger method in INTC module */
        /* #Violation: intc_hal_c_REF_6 */
        expValue = INTC_HAL->LEVEDGSEL1[registerShift];
        expValue |= ((uint32)triggerMethod << bitShift);
        /* #Violation: intc_hal_c_REF_6 */
        INTC_HAL->LEVEDGSEL1[registerShift] = expValue;
        /* Check register readback check value meet expectation */
        /* #Violation: intc_hal_c_REF_6 */
        ret = Intc_Register_ReadBack_Check(ret, expValue, INTC_HAL->LEVEDGSEL1[registerShift]);    
    }
    /* Interrupt ID is equal or great than Gtm MCS7 IRQ4 interrupt, and equal or less than Gtm MCSW interrupt */
    else if((intID >= INTC_INTID_GTM_MCS7_IRQ_4) && (intID <= INTC_INTID_GTM_MCSW_ORED_INT))
    {     
        /* LEVEDGESEL10 */
        iCount = 0;
        /* The count less than INTC_INTID_GTM_LEVEDGSEL10_0 */
        while(iCount < INTC_INTID_GTM_LEVEDGSEL10_0)
        {
            /* The interrupt ID equal to the expected ID */
            if(intID == levedgsel10Value[iCount][0])
            {
                /* Get the bit offset, 1 bit per interrupt */
                bitShift = levedgsel10Value[iCount][1];
                /* Clear the corresponding bit */
                /* #Violation: intc_hal_c_REF_6 */
                expValue = INTC_HAL->LEVEDGSEL1[3];
                expValue &= ~((uint32)1U << bitShift);
                /* #Violation: intc_hal_c_REF_6 */
                INTC_HAL->LEVEDGSEL1[3] = expValue;
                /* Check register readback check value meet expectation */
                /* #Violation: intc_hal_c_REF_6 */
                ret = Intc_Register_ReadBack_Check(ret, expValue, INTC_HAL->LEVEDGSEL1[3]);
              
                /* Set trigger method in INTC module */
                /* #Violation: intc_hal_c_REF_6 */
                expValue = INTC_HAL->LEVEDGSEL1[3];
                expValue |= ((uint32)triggerMethod << bitShift);
                /* #Violation: intc_hal_c_REF_6 */
                INTC_HAL->LEVEDGSEL1[3] = expValue;
                /* Check register readback check value meet expectation */
                /* #Violation: intc_hal_c_REF_6 */
                ret = Intc_Register_ReadBack_Check(ret, expValue, INTC_HAL->LEVEDGSEL1[3]);
                iCount = INTC_INTID_GTM_LEVEDGSEL10_0;
            }
            iCount++;
        }
    }
    /* Other interrupt ID */
    else
    {     
        /* LEVEDGESEL(part 9),intID(66,67,82,83,...)*/
        iCount = 0;
        /* The count less than INTC_INTID_GTM_LEVEDGSEL9_0 */
        while(iCount < INTC_INTID_GTM_LEVEDGSEL9_0)
        {
            /* The interrupt ID equal to the expected ID */
            if(intID == levedgsel9Value[iCount][0])
            {
                /* Get the bit offset, 1 bit per interrupt */
                bitShift = levedgsel9Value[iCount][1];
                /* #Violation: intc_hal_c_REF_6 */
                expValue = INTC_HAL->LEVEDGSEL1[2];
                expValue &= ~((uint32)1U << bitShift);
                /* Clear the corresponding bit */
                /* #Violation: intc_hal_c_REF_6 */
                INTC_HAL->LEVEDGSEL1[2] = expValue;
                /* Check register readback check value meet expectation */
                /* #Violation: intc_hal_c_REF_6 */
                ret = Intc_Register_ReadBack_Check(ret, expValue, INTC_HAL->LEVEDGSEL1[2]);
                /* Set trigger method in INTC module */
                /* #Violation: intc_hal_c_REF_6 */
                expValue = INTC_HAL->LEVEDGSEL1[2];
                expValue |= ((uint32)triggerMethod << bitShift);
                /* #Violation: intc_hal_c_REF_6 */
                INTC_HAL->LEVEDGSEL1[2] = expValue;
                /* Check register readback check value meet expectation */
                /* #Violation: intc_hal_c_REF_6 */
                ret = Intc_Register_ReadBack_Check(ret, expValue, INTC_HAL->LEVEDGSEL1[2]);
                iCount = INTC_INTID_GTM_LEVEDGSEL9_0;
            }
            iCount++;
        }
    }
#endif /* End THA6_THA6412 */
    return ret;
}

static boolean Intc_Hal_InstallPeripheralInterrupt(INTC_GIC_MODULE *const pGic, uint32 coreNoForGic,
                                                const Intc_InterruptConfig *const pIntCfg)
{
    uint32 registerShift;
    uint32 bitShift;
    uint32 intID;
    uint32 divIntID;
    boolean ret;
    ret = TRUE;
    intID = (uint32)(pIntCfg->intID) - INTC_MIN_SPI_ID;
    
    /* First need to disable the interrupt, disable forwarding of the corresponding SPI from the distributor to the
     * CPU interface */
    /* Disable the interrupt */
    /* 32 interrupts per register, 1 bit per interrupt */
    divIntID = intID % 32U;
    pGic->DISTRIBUTOR.GICDICENABLER[intID >> 5U] = (uint32)1U << divIntID;
    
    /* Set interrupt group:control whether the corresponding SPI is in Group0 or Group1 */
    /* Calculate the register offset, 32 interrupts per register */
    registerShift = intID >> 5U;
    /* Calculate the bit offset, 1 bit per interrupt */
    bitShift = intID % 32U;
    /* Set interrupt group */
    pGic->DISTRIBUTOR.GICDIGROUP[registerShift] |= ((uint32)(pIntCfg->group) << bitShift);

    /* Set interrupt priority:0~31 */
    /* Calculate the register offset, 4 interrupts per register */
    registerShift = intID >> 2U;
    /* Calculate the bit offset */
    bitShift = (intID % 4U) << 3U;
    /* Set priority, 4 bits per interrupt */
    pGic->DISTRIBUTOR.GICDIPRIORITYR[registerShift] |= ((uint32)(pIntCfg->priority) << (3U + bitShift));

    /* Set trigger method: rising edge-triggered or active-high level-sensitive */
    /* Calculate the register offset, 16 interrupts per register */
    registerShift = intID >> 4U;
    /* Calculate the bit offset, 2 bits per interrupt */
    bitShift = (intID % 16U) << 1U;
    /* Set trigger method, only the higher bit of 2 bits is valid */
    pGic->DISTRIBUTOR.GICDICFGR[registerShift] |= ((uint32)(pIntCfg->triggerMethod) << (1U + bitShift));

    /* Set GTM interrupt trigger mode */
    ret &= Intc_Hal_SetGtmtrigger(pIntCfg->intID, pIntCfg->triggerMethod);

    /* Set target core of SPI */
    pGic->DISTRIBUTOR.GICDIROUTER[intID].B.AFF0 = coreNoForGic;

    /* If need to enable the interrupt, enable forwarding of the corresponding SPI from the distributor to the
     * CPU interface */
    /* Enable the interrupt */
    if(TRUE == pIntCfg->enable)
    {
        /* 32 interrupts per register, 1 bit per interrupt */
        pGic->DISTRIBUTOR.GICDISENABLER[intID >> 5U] = (uint32)1U << divIntID;
    }
    return ret;
}

static boolean Intc_Hal_InitializeSpiSoftwareInterrupt(Intc_IntID intID, MultiCoreID coreID)
{
    uint32 softIntOffsetBit;
    uint32 regOffset;
    uint32 tempValue;
    boolean ret;
    ret = TRUE;
   /* coreID:0~3 */
   /* Core id equal to Core0 or Core2 */
    if((MULTICOREID_CPU0 == coreID)||(MULTICOREID_CPU2 == coreID))
    {
        softIntOffsetBit = (uint32)intID - (uint32)INTC_INTID_SOFT_INT_CORE0_0;
    }
    /* Core id equal to Core1 or Core3 */
    else
    {
        softIntOffsetBit = (uint32)intID - (uint32)INTC_INTID_SOFT_INT_CORE1_0;
    }


    regOffset = ((uint32)coreID * 4U) + softIntOffsetBit;
    /* Semaphore enable,enable read clear */
    /* #Violation: intc_hal_c_REF_6 */
    tempValue = INTC_HAL->SEMAPEN.U;
    tempValue |= (uint32)INTC_SOFTINT_ENABLE_RDCLEAR << (2U * regOffset);
    /* #Violation: intc_hal_c_REF_6 */
    INTC_HAL->SEMAPEN.U = tempValue;
    /* Check register readback check value meet expectation */
    /* #Violation: intc_hal_c_REF_6 */
    ret = Intc_Register_ReadBack_Check(ret, tempValue, INTC_HAL->SEMAPEN.U);
    /* #Violation: intc_hal_c_REF_6 */
    INTC_HAL->SEMAP[regOffset].U = INTC_SEMAP_SEMFPSW | INTC_SOFTINT_RESOURCE_FREE;  /* Free software INT resource */
    return ret;
}

static Intc_ErrorFlag Intc_Hal_GenerateSpiSoftwareInterrupt(Intc_IntID intID, Intc_TargetCore targetCore)
{
    Intc_ErrorFlag retState;
    uint32 softIntOffsetBit;
    uint32 regOffset;
    boolean ret;

    ret = TRUE;
   /* targetCore:0~3 */
   /* The target Core is equal Core0 or Core2 */
    if((INTC_TARGET_CORE0 == targetCore)||(INTC_TARGET_CORE2 == targetCore))
    {
        if((uint32)intID > (uint32)INTC_INTID_SOFT_INT_CORE0_0)
        {
            softIntOffsetBit = (uint32)intID - (uint32)INTC_INTID_SOFT_INT_CORE0_0;
        }
        else
        {
            softIntOffsetBit = 0U;
        }    
    }
    /* The target Core is equal Core1 or Core3 */
    else
    {
        if((uint32)intID > (uint32)INTC_INTID_SOFT_INT_CORE1_0)
        {
            softIntOffsetBit = (uint32)intID - (uint32)INTC_INTID_SOFT_INT_CORE1_0;
        }
        else
        {
            softIntOffsetBit = 0U;
        }    
    }

    regOffset = ((uint32)targetCore * 4U) + softIntOffsetBit;

    /* Check for software interrupt resource is free(SEMAPn.SEMF == 1) */
    /* The resource is idle */
    /* #Violation: intc_hal_c_REF_6 */
    if(INTC_SOFTINT_RESOURCE_FREE == INTC_HAL->SEMAP[regOffset].B.SEMF)
    {
        retState = INTC_ERRORFLAG_SUCCESS;
    }
    /* The resource is busy */
    else
    {
        retState = INTC_ERRORFLAG_ATOMIC_BUSY;
    }
    /* The resource is idle */
    if(INTC_ERRORFLAG_SUCCESS == retState)
    {   
        /* Generate software INT */
        /* #Violation: intc_hal_c_REF_6 */
        INTC_HAL->SFINTCR[regOffset].U = INTC_SFINTCR_SFINTPSW|INTC_SOFTINT_ENABLE;    
        /* Check register readback check value meet expectation */
        /* #Violation: intc_hal_c_REF_6 */
        ret = Intc_Register_ReadBack_Check(ret, (INTC_SFINTCR_SFINTPSW|INTC_SOFTINT_ENABLE), INTC_HAL->SFINTCR[regOffset].U);
        if(TRUE != ret)
        {
            retState = INTC_ERRORFLAG_FAILURE;
        }
    }

    return retState;
}

/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: intc_hal_c_REF_2 */
/* #Violation: intc_hal_c_REF_3 */
Intc_ErrorFlag Intc_Hal_InstallInterrupt(const Intc_InterruptConfig *const pIntList, uint32 intSum, IntHandler* pIntTblBaseAddr)
{
    /*****************************************************************************************************
     * Usage Restrictions
     *- If user want to Initialize Software SPI interrupt in the API branch (Intc_Hal_InitializeSpiSoftwareInterrupt)
     *  It is recommended that users use the locking mechanism to protect "Intc_Hal_InstallInterrupt" API.
     * 
     ******************************************************************************************************/
    uint32 loopCount = 0U;
    /* Size of interrupt vector table */
    boolean tempValue;
    INTC_GIC_MODULE *pGic;
    MultiCoreID coreID;
    Intc_ErrorFlag flag;
    uint32 coreNoInGic;
    const Intc_InterruptConfig *pIntListLocal;
    flag = INTC_ERRORFLAG_SUCCESS;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check interrupt priority is in the normal range */
    Assert((boolean)((INTC_MAX_PRIORITY >= pIntList->priority) ? TRUE : FALSE));
    /* Check interrupt group is in the normal range */
    Assert((boolean)((INTC_MAX_GROUP >= pIntList->group) ? TRUE : FALSE));
    /* Check interrupt trigger method is in the normal range */
    Assert((boolean)((INTC_MAX_TRIGGER_METHOD >= pIntList->triggerMethod) ? TRUE : FALSE));
    /* Check interrupt ID is equal or less than INTC_INTID_GTM_MAXID */
    Assert((boolean)((INTC_INTID_GTM_MAXID >= pIntList->intID) ? TRUE : FALSE));
    /* Check the number of interrupts is in the normal range */
    /* #Violation: intc_hal_c_REF_7 */
    Assert((boolean)(intSum <= INTC_MAX_INT_NUMBER));
#endif
    pIntListLocal = pIntList;
    /* Get the Core ID */
    coreID = Multicore_GetCoreID();
#if defined(THA6_THA6412)
    /* The Core ID is Core2 or Core3 */
    if((MULTICOREID_CPU2 == coreID)||(MULTICOREID_CPU3 == coreID))
    {
        /* #Violation: intc_hal_c_REF_6 */
        pGic = GIC1;
        coreNoInGic = (uint32)coreID - 2U;
        /* Enable FIQ and IRQ in GICD */
        /* #Violation: intc_hal_c_REF_6 */
        GIC1->DISTRIBUTOR.GICDCTRL.B.ENABLEGRP0 = 1U;
        /* #Violation: intc_hal_c_REF_6 */
        GIC1->DISTRIBUTOR.GICDCTRL.B.ENABLEGRP1 = 1U;
    }
    /* The Core ID is Core0 or Core1 */
    else
#endif
    {
        /* #Violation: intc_hal_c_REF_6 */
        pGic = GIC0;
        coreNoInGic = (uint32)coreID;
        /* Enable FIQ and IRQ in GICD */
        /* #Violation: intc_hal_c_REF_6 */
        GIC0->DISTRIBUTOR.GICDCTRL.B.ENABLEGRP0 = 1U;
        /* #Violation: intc_hal_c_REF_6 */
        GIC0->DISTRIBUTOR.GICDCTRL.B.ENABLEGRP1 = 1U;
    }

    /* Wake the redistributor path to the CPU Interface */
    pGic->REDISTRIBUTOR[coreNoInGic].GICRWAKER.B.PROCESSORSLEEP = 0U;
    /* Dummy instruction */
    /* #Violation: intc_hal_c_REF_1 */
    /* #Violation: intc_hal_c_REF_9 */
    /* #Violation: intc_hal_c_REF_10 */
    ASM_VOLATILE(" nop   \n"
                 " nop   \n");
    /* Set priority mask to 31: MCR p15,0,<Rt>,c4,c6,0.Writes the initial priority mask value to the corresponding
        system control register ICC_PMR of <Coprocessor 15, 0, c4, c6, 0> */
    /* Set priority mask */
    /* #Violation: intc_hal_c_REF_1 */
    /* #Violation: intc_hal_c_REF_9 */
    /* #Violation: intc_hal_c_REF_10 */
    SET_CP(15, 0, 0xF8U, 4, 6, 0);
    /* Enable IRQ interrupt: MCR p15,0,<Rt>,c12,c12,7.Writes 1 to the corresponding system control register ICC_IGRPEN1
        <Coprocessor 15, 0, c12, c12, 7> */
    /* Enable IRQ interrupt */
    /* #Violation: intc_hal_c_REF_1 */
    /* #Violation: intc_hal_c_REF_9 */
    /* #Violation: intc_hal_c_REF_10 */
    SET_CP(15, 0, 1U, 12, 12, 7);
    /* Enable FIQ interrupt: MCR p15,0,<Rt>,c12,c12,6.Writes 1 to the corresponding system control register ICC_IGRPEN0
        <Coprocessor 15, 0, c12, c12, 6> */
    /* Enable FIQ interrupt */
    /* #Violation: intc_hal_c_REF_1 */
    /* #Violation: intc_hal_c_REF_9 */
    /* #Violation: intc_hal_c_REF_10 */
    SET_CP(15, 0, 1U, 12, 12, 6);

    /* The interrupt vector table is NULL pointer */
    if(NULL_PTR == pIntTblBaseAddr)
    {
        flag = INTC_ERRORFLAG_SET_HANDLER_FAIL;
    }
    /* The interrupt vector table is not NULL pointer */
    else
    {
        /* Install all the interrupts of list */
        while(loopCount < intSum)
        {   
            /* The interrupt hander is not NULL pointer */
            if(NULL_PTR != pIntListLocal->handler)
            {
                /* Install interrupt */
                /* Set handler */
                pIntTblBaseAddr[pIntListLocal->intID] = pIntListLocal->handler;
                /* Interrupt is SPI */
                if(pIntListLocal->intID >= INTC_MIN_SPI_ID)
                {
                    /* Install SPI interrupt */
                    tempValue = Intc_Hal_InstallPeripheralInterrupt(pGic, coreNoInGic, pIntListLocal);
                    if(tempValue != TRUE)
                    {
                        flag = INTC_ERRORFLAG_SET_HANDLER_FAIL;
                    }
                    
                    /* Check the intID range,if it is SPI software interrupt, initialize SPI Software Interrupt */
                    /* Interrupt is Software SPI interrupt */
                    if(((pIntListLocal->intID <= INTC_INTID_SOFT_INT_CORE0_3) &&
                            (pIntListLocal->intID >= INTC_INTID_SOFT_INT_CORE0_0))||
                            ((pIntListLocal->intID <= INTC_INTID_SOFT_INT_CORE1_3) &&
                                (pIntListLocal->intID >= INTC_INTID_SOFT_INT_CORE1_0)))
                    {
                        /* Initialize  Software SPI interrupt */
                        tempValue = Intc_Hal_InitializeSpiSoftwareInterrupt(pIntListLocal->intID,coreID);
                        if(tempValue != TRUE)
                        {
                            flag = INTC_ERRORFLAG_SET_HANDLER_FAIL;
                        }
                    }
                }
                /* Interrupt is not SPI */
                else
                {   
                    /* Install SGI/PPI interrupt */
                    Intc_Hal_InstallInternalInterrupt(pGic, coreNoInGic,pIntListLocal);
                }
            }
            loopCount++;
            pIntListLocal++;
        }
        if(flag != INTC_ERRORFLAG_SUCCESS)
        {
            flag = INTC_ERRORFLAG_SET_HANDLER_FAIL;
        }
    }
    /* Enable interrupts */
    /* #Violation: intc_hal_c_REF_1 */
    /* #Violation: intc_hal_c_REF_9 */
    /* #Violation: intc_hal_c_REF_10 */
    ASM_VOLATILE(" cpsie if  \n");
    return flag;
}

/* #Violation: intc_hal_c_REF_3 */
Intc_ErrorFlag Intc_Hal_EnableInterrupt(Intc_IntID intID)
{
    INTC_GIC_MODULE *pGic;
    Intc_ErrorFlag flag;
    MultiCoreID coreID;
    uint32 coreNoInGic;
    uint32 subIntID;
    uint32 tempIntID;
    uint32 divIntID;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check the interrupt ID is in normal range */
    /* #Violation: intc_hal_c_REF_7 */
    Assert((boolean)(intID <= INTC_MAX_SPI_ID));
#endif /* INPUT_ARG_DETECT */
    /* Get the Core ID */
    coreID = Multicore_GetCoreID();
#if defined(THA6_THA6412)
    /* The Core ID is Core2 or Core3 */
    if((MULTICOREID_CPU2 == coreID) || (MULTICOREID_CPU3 == coreID))
    {
        /* #Violation: intc_hal_c_REF_6 */
        pGic = GIC1;
        coreNoInGic = (uint32)coreID - 2U;    
    }
    /* The Core ID is Core0 or Core1 */
    else
#endif
    {
        /* #Violation: intc_hal_c_REF_6 */
        pGic = GIC0;
        coreNoInGic = (uint32)coreID;
    }

    /* The interrupt is SPI */
    if(intID >= INTC_MIN_SPI_ID)
    {
        /* Check if the interrupt has been already enabled */
        /* If is enable */
        subIntID = (uint32)intID - INTC_MIN_SPI_ID;
        divIntID = (uint32)intID % 32U;
        tempIntID = pGic->DISTRIBUTOR.GICDISENABLER[subIntID >> 5U] >> divIntID;
        /* The interrupt have enabled */
        if(1U == (tempIntID & 1U))
        {
            flag = INTC_ERRORFLAG_REPEAT;
        }
        /* The interrupt is disable */
        else
        {
            flag = INTC_ERRORFLAG_SUCCESS;
            /* 32 interrupts per register, 1 bit per interrupt */
            pGic->DISTRIBUTOR.GICDISENABLER[subIntID >> 5U] = (uint32)1U << divIntID;
        }
    }
    /* The interrupt is SGI or PPI */
    else
    {
        /* Check if the interrupt has been already enabled */
        /* The interrupt have enabled */
        if(1U == ((pGic->REDISTRIBUTOR[coreNoInGic].GICRISENABLER >> intID) & 1U))
        {
            flag = INTC_ERRORFLAG_REPEAT;
        }
        /* The interrupt is disable */
        else
        {
            flag = INTC_ERRORFLAG_SUCCESS;
            pGic->REDISTRIBUTOR[coreNoInGic].GICRISENABLER = (uint32)1U << intID;
        }
    }
    return flag;
}

/* #Violation: intc_hal_c_REF_3 */
Intc_ErrorFlag Intc_Hal_DisableInterrupt(Intc_IntID intID)
{
    INTC_GIC_MODULE *pGic;
    Intc_ErrorFlag flag;
    MultiCoreID coreID;
    uint32 coreNoInGic;
    uint32 subIntID;
    uint32 tempIntID;
    uint32 divIntID;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check the interrupt ID is in normal range */
    /* #Violation: intc_hal_c_REF_7 */
    Assert((boolean)(intID <= INTC_MAX_SPI_ID));
#endif /* INPUT_ARG_DETECT */
    /* Get the Core ID */
    coreID = Multicore_GetCoreID();
#if defined(THA6_THA6412)
    /* The Core ID is Core2 or Core3 */
    if((MULTICOREID_CPU2 == coreID) || (MULTICOREID_CPU3 == coreID))
    {
        /* #Violation: intc_hal_c_REF_6 */
        pGic = GIC1;
        coreNoInGic = (uint32)coreID - 2U;
    }
    /* The Core ID is Core0 or Core1 */
    else
#endif
    {
        /* #Violation: intc_hal_c_REF_6 */
        pGic = GIC0;
        coreNoInGic = (uint32)coreID;
    }

    /* The interrupt is SPI */
    if(intID >= INTC_MIN_SPI_ID)
    {
        /* Check if the interrupt has been already disabled */
        /* If is disable */
        subIntID = (uint32)intID - INTC_MIN_SPI_ID;
        divIntID = (uint32)subIntID % 32U;
        tempIntID = pGic->DISTRIBUTOR.GICDICENABLER[subIntID >> 5U] >> divIntID;
        if(0U == (tempIntID & 1U))
        {
            flag = INTC_ERRORFLAG_REPEAT;
        }
        /* If is enable */
        else
        {
            flag = INTC_ERRORFLAG_SUCCESS;
            /* 32 interrupts per register, 1 bit per interrupt */
            pGic->DISTRIBUTOR.GICDICENABLER[subIntID >> 5U] = (uint32)1U << divIntID;
        }
    }
    /* The interrupt is SGI or PPI */
    else
    {
        /* Check if the interrupt has been already disabled */
        /* The interrupt have disabled */
        if(0U == ((pGic->REDISTRIBUTOR[coreNoInGic].GICRICENABLER >> intID) & 1U))
        {
            flag = INTC_ERRORFLAG_REPEAT;
        }
        /* The interrupt is enable */
        else
        {
            flag = INTC_ERRORFLAG_SUCCESS;
            pGic->REDISTRIBUTOR[coreNoInGic].GICRICENABLER = (uint32)1U << intID;
        }
    }
    return flag;
}

/* #Violation: intc_hal_c_REF_2 */
/* #Violation: intc_hal_c_REF_3 */
void Intc_Hal_SetMinGroupPriority(uint32 fiqGroupMinPriority, uint32 irqGroupMinPriority)
{
    uint32 fiqBinaryPoint;
    uint32 irqBinaryPoint;
    uint32 fiqGroupMinPriorityLocal;
    uint32 irqGroupMinPriorityLocal;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the fiq group priority is in the normal range */
    /* #Violation: intc_hal_c_REF_7 */
    Assert((boolean)(fiqGroupMinPriority <= INTC_MAX_PRIORITY));
    /* Check if the irq group priority is in the normal range */
    /* #Violation: intc_hal_c_REF_7 */
    Assert((boolean)((irqGroupMinPriority <= INTC_MAX_PRIORITY) &&
                     (irqGroupMinPriority >= INTC_MINPEAK_IRQ_GROUP_PRIORITY)));
#endif /* INPUT_ARG_DETECT */
    fiqBinaryPoint = 7U;
    irqBinaryPoint = 8U;
    fiqGroupMinPriorityLocal = fiqGroupMinPriority;
    irqGroupMinPriorityLocal = irqGroupMinPriority;

    /* Get number of bit1 */
    while (fiqGroupMinPriorityLocal > 0U)
    {
        fiqBinaryPoint--;
        fiqGroupMinPriorityLocal = fiqGroupMinPriorityLocal >> 1U;
    }
    /* Get number of bit1 */
    while (irqGroupMinPriorityLocal > 0U)
    {
        irqBinaryPoint--;
        irqGroupMinPriorityLocal = irqGroupMinPriorityLocal >> 1U;
    }

    /* Set FIQ binary point: MCR p15,0,<Rt>,c12,c8,3. Writes the value of fiqPriorityBinaryPoint to the corresponding
       system control register ICC_BPR0 of <Coprocessor 15, 0, c12, c8, 3> */
    /* Set FIQ binary point value */
    /* #Violation: intc_hal_c_REF_1 */
    /* #Violation: intc_hal_c_REF_9 */
    /* #Violation: intc_hal_c_REF_10 */
    SET_CP(15, 0, fiqBinaryPoint, 12, 8, 3);

    /* Set IRQ binary point: MCR p15,0,<Rt>,c12,c12,3. Writes the value of irqPriorityBinaryPoint to the corresponding
       system control register ICC_BPR1 of <Coprocessor 15, 0, c12, c12, 3> */
    /* Set IRQ binary point value */   
    /* #Violation: intc_hal_c_REF_1 */
    /* #Violation: intc_hal_c_REF_9 */
    /* #Violation: intc_hal_c_REF_10 */
    SET_CP(15, 0, irqBinaryPoint, 12, 12, 3);
}

/* #Violation: intc_hal_c_REF_3 */
boolean Intc_Hal_ClearSpiSoftwareInterrupt(Intc_IntID intID)
{
    MultiCoreID coreID;
    uint32 softIntOffsetBit;
    uint32 regOffset;
    boolean ret;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the intID is in the normal range */
    /* #Violation: intc_hal_c_REF_7 */
    Assert((boolean)(((intID <= INTC_INTID_SOFT_INT_CORE0_3) && (intID >= INTC_INTID_SOFT_INT_CORE0_0))||
                    ((intID <= INTC_INTID_SOFT_INT_CORE1_3) && (intID >= INTC_INTID_SOFT_INT_CORE1_0))));
#endif /* INPUT_ARG_DETECT */
    /* Get core ID */
    coreID = Multicore_GetCoreID();
    ret = TRUE;

    /* The coreID is Core0 or Core2 */
    if((MULTICOREID_CPU0 == coreID)||(MULTICOREID_CPU2 == coreID))
    {
        softIntOffsetBit = (uint32)intID - (uint32)INTC_INTID_SOFT_INT_CORE0_0;
    }
     /* The coreID is Core1 or Core3 */
    else
    {
        softIntOffsetBit = (uint32)intID - (uint32)INTC_INTID_SOFT_INT_CORE1_0;
    }

    regOffset = ((uint32)coreID * 4U) + softIntOffsetBit;

    /* Invalid software Int */
    /* #Violation: intc_hal_c_REF_6 */
    INTC_HAL->SFINTCR[regOffset].U = INTC_SFINTCR_SFINTPSW|INTC_SOFTINT_DISABLE;    /* clear software INT */
    /* Check register readback check value meet expectation */
    /* #Violation: intc_hal_c_REF_6 */
    ret = Intc_Register_ReadBack_Check(ret, INTC_SFINTCR_SFINTPSW|INTC_SOFTINT_DISABLE, INTC_HAL->SFINTCR[regOffset].U);
    /* #Violation: intc_hal_c_REF_6 */
    INTC_HAL->SEMAP[regOffset].U = INTC_SEMAP_SEMFPSW|INTC_SOFTINT_RESOURCE_FREE;   /* Free software INT resource */
    return ret;
}

/* #Violation: intc_hal_c_REF_2 */
/* #Violation: intc_hal_c_REF_3 */
Intc_ErrorFlag Intc_Hal_GenerateSoftwareInterrupt(Intc_IntID intID, Intc_TargetCore targetCore)
{
    /* 64 bits, the value of SGI generated register */
    uint64 intInfo;
    uint32 targetList;
    Intc_ErrorFlag retState;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check the interrupt ID is in normal range */
    Assert((boolean)((INTC_INTID_GTM_MAXID >= intID) ? TRUE : FALSE));
#endif  
    /* The interrupt ID is SGI */
    if(intID <= INTC_MAX_SGI_ID)
    {
        retState = INTC_ERRORFLAG_SUCCESS;
#if defined(THA6_THA6412) 
        MultiCoreID coreID;
        /* Get the core ID */
        coreID = Multicore_GetCoreID();

        /* One core can't generate SGI interrupt to other cluster's core  */
        /* Get the Core ID is Core0 or Core1 */
        if((MULTICOREID_CPU0 == coreID) || (MULTICOREID_CPU1 == coreID)) /* Core of cluster0 */
        {
            /* The target core is not Core0 or Core1 */
            if((INTC_TARGET_CORE2 == targetCore)||(INTC_TARGET_CORE3 == targetCore)||
               (INTC_TARGET_CORE2_CORE3 == targetCore))
            {
                retState = INTC_ERRORFLAG_FAILURE;
            }
        }
        /* Get the Core ID is Core2 or Core3 */
        else
        {
            /* The target core is not Core2 or Core3 */
            if((INTC_TARGET_CORE0 == targetCore)||(INTC_TARGET_CORE1 == targetCore)||
               (INTC_TARGET_CORE0_CORE1 == targetCore))
            {
                retState = INTC_ERRORFLAG_FAILURE;
            }
        }

        /* #Violation: intc_hal_c_REF_4 */  
        if(INTC_ERRORFLAG_SUCCESS == retState)
        {
#endif/* End if THA6_THA6412 */            
            /* Get the value of targetList */
            if(INTC_TARGET_CORE0_CORE1 == targetCore)
            {
                targetList = 0x03U;    /*two cores can respond the interrupt in the same cluster */
            }
            else if(INTC_TARGET_CORE2_CORE3 == targetCore)
            {
                targetList = (uint32)0x03U | ((uint32)0x1 << 16U);  /*two cores can respond the interrupt in the same cluster */
            }
            else if((INTC_TARGET_CORE2 == targetCore) || (INTC_TARGET_CORE3 == targetCore))
            {
                targetList = (uint32)targetCore - (uint32)INTC_TARGET_CORE2;
                targetList = ((uint32)1U << targetList) | ((uint32)0x1 << 16U);
            }
            else
            {
                targetList = (uint32)1U << (uint32)targetCore;
            }

            /* Set intID of SGI and write targetList */
            /* SDK_INTC_Deviation_Rule2_2 */
            intInfo = ((uint64)intID << 24ULL) | ((uint64)targetList);

            /* Write intInfo into register: MCR p15, 0, <Rt>, c12.Writes intInfo to the corresponding system control register
               ICC_SGI1R of <Coprocessor 15, 0, c12> */
            /* Writes intInfo to the corresponding system control register */
            /* #Violation: intc_hal_c_REF_4 */
            /* #Violation: intc_hal_c_REF_1 */
            /* #Violation: intc_hal_c_REF_9 */
            /* #Violation: intc_hal_c_REF_10 */
            SET_CP64(15, 0, (intInfo), 12);
#if defined(THA6_THA6412)     
        }
#endif/* End if THA6_THA6412 */         
    }
    /* The interrupt ID is SPI */
    else  /* intID is SPI intID, should generate SPI software interrupt */
    {
        retState = Intc_Hal_GenerateSpiSoftwareInterrupt(intID, targetCore);
    }
    return retState;
}

/* #Violation: intc_hal_c_REF_3 */
uint32 Intc_Hal_GetAlarmStatus(uint32 index)
{
    uint32 alarmStatus;
    /* Get alarm status */
    if(0U == index)
    {
        /* #Violation: intc_hal_c_REF_6 */
        alarmStatus = INTC_HAL->ALMSTS0.U;
    }
    else
    {
        /* #Violation: intc_hal_c_REF_6 */
        alarmStatus = INTC_HAL->ALMSTS1.U;
    }
    /* Return alarm status */
    return alarmStatus;
}

/* #Violation: intc_hal_c_REF_3 */
boolean Intc_Hal_ClearAlarmStatus(uint32 alarmClear)
{ 
    boolean retSts;

    retSts = TRUE;
    /* Disable all interrupt */
    DISABLE_ALL_INTERRUPTS();
    /* Clear safewdt ENDINIT */
    retSts &= Safewdt_Hal_ClearSafetyEndinit();
    /* Clear the corresponding alarms */
    /* #Violation: intc_hal_c_REF_6 */
    INTC_HAL->ALMCLR.U = alarmClear;
    /* Set safewdt ENDINIT */
    retSts &= Safewdt_Hal_SetSafetyEndinit();
    /* Enable all interrupt */
    ENABLE_ALL_INTERRUPTS();
    return retSts;
}

/* #Violation: intc_hal_c_REF_3 */
boolean Intc_Hal_SetAlarmStatus(uint32 alarm)
{
    boolean ret;
    ret = TRUE;
    /* Set the corresponding alarms */
    /* #Violation: intc_hal_c_REF_6 */
    INTC_HAL->ALMEN.U = alarm;
    /* Check register readback check value meet expectation */
    /* #Violation: intc_hal_c_REF_6 */
    ret = Intc_Register_ReadBack_Check(ret, alarm, INTC_HAL->ALMEN.U);
    return ret;
}

#define INTC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: intc_hal_c_REF_11 */
#include "Intc_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
