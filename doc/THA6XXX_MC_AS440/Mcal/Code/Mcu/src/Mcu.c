/****************************************************************************************************
 *
 ****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Mcu.c
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : RCC,PWRC
 *
 *   brief                 : This file contains all functions of MCU Driver
 *
 *   Autosar Version       : 4.4.0
 *
 *   Build Version         : Cortex-R52+/THA6xxx
 *
 *   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
 *
 ****************************************************************************************************/
/*
 *#Violation Summary
 *#Mcu_c_REF_1:MISRAC2012-Rule-20.1;
 * Justification: AUTOSAR imposes the specification of the sections in which certain parts of the
 *driver must be placed.
 *
 *#Mcu_c_REF_2:MISRAC2012-Rule-11.4;
 * Justification: The register must load the buffer's address.
 *
 *#Mcu_c_REF_3:MISRAC2012-Rule-20.10;
 * Justification: Use glue operator to construct the exclusive area function name.
 *
 *#Mcu_c_REF_4:MISRAC2012-Rule-1.2;
 * Justification: Inline assembly for CPU-specific operations.
 *
 *#Mcu_c_REF_20:MISRAC2012-Rule-2.7;
 * Justification: Inline assembly for CPU-specific operations.
 *
 *#Mcu_c_REF_21:MISRAC2012-Dir-1.1;
 * Justification: Inline assembly for CPU-specific operations.
 *
 *#Mcu_c_REF_22:MISRAC2012-Dir-4.2;
 * Justification: Inline assembly for CPU-specific operations.
 *
 *#Mcu_c_REF_5:MISRAC2012-Dir-4.1;
 * Justification: Number of loops is set by different configurations.
 *
 *#Mcu_c_REF_6:MISRAC2012-Dir-4.3;
 * Justification: Mixing inline assembly with C code reduces code complexity.
 *
 *#Mcu_c_REF_7:MISRAC2012-Rule-2.7;
 * Justification: Parameters are used by assembly code.
 *
 *#Mcu_c_REF_8:MISRAC2012-Dir-4.9;
 * Justification: Function like macros are used to reduce code complexity.
 *
 *#Mcu_c_REF_9:MISRAC2012-Rule-10.5;
 * Justification: Unsigned  to enum type do not exceed the enum range.
 *
 *#Mcu_c_REF_10:MISRAC2012-Rule-20.7;
 * Justification: Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
 *
 *#Mcu_c_REF_19:MISRAC2012-Rule-2.5; 
 * Justification: The macros are reserved for upper layers.
 * 
 *#Mcu_c_REF_17:MISRAC2012-Rule-2.1;
 * Justification: Reserved API for user access.
 *
 *#Mcu_c_REF_18:MISRAC2012-Rule-10.8;
 * Justification: Necessary cast from floating to uint32 for register accessing; Data integrity is
 *ensured via code review.
 *
 *#Mcu_c_REF_23:MISRAC2012-Rule-8.7;
 * Justification:The interface is called by the application layer.
 *
 *#Mcu_c_REF_24:MISRAC2012-Rule-2.2;
 * Justification:Platform-based design with configurable macros..
 *
 *#Mcu_c_REF_11:CWE-1071;
 * Justification: MISRA-2012 Rule 15.7/Rule 16.4 require reserved empty code block.
 *
 *#Mcu_c_REF_12:CWE-704;
 * Justification: Cast a numeric value to a pointer type for accessing data at a specified memory
 *address.
 *
 *#Mcu_c_REF_13:CertC-PRE00-C;
 * Justification: Function like macros are used to reduce code complexity.
 *
 *#Mcu_c_REF_14:CertC-INT36-C;
 * Justification: Cast a numeric value to a pointer type for accessing data at a specified memory
 *address.
 *
 *#Mcu_c_REF_15:CertC-DCL00-C;
 * Justification: Parameter declared refer to AUTOSAR specifications.
 *
 *#Mcu_c_REF_16:CertC-DCL02-C;
 * Justification: Company-specific naming conventions  are applied. Developers will not be confused.
 *
 */

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Mcu.h"
#include "Mcall.h"
/* Included for Header file inclusion */
/* \[SWS_Mcu_00017]
 *shall check the following API parameters, report detected errors */
/* \[SWS_Mcu_00163] */
/* Included for the declaration of Det_ReportError() */
#include "Det.h"
/* \[SWS_Mcu_00166] [SWS_Mcu_00152] */
/* Included for declaration of the function Dem_ReportErrorStatus() and Dem_SetEventStatus() */
#if (MCU_DEM_REPORT_ERROR_STATUS == STD_ON)
#include "Dem.h"
#endif /* (MCU_DEM_REPORT_ERROR_STATUS  \== STD_ON) */
#include "SchM_Mcu.h"
#include "tha6_cfg.h"

/****************************************************************************************************
**                          Version Checks                                                         **
****************************************************************************************************/

#if (MCU_VENDOR_ID != MCU_CFG_VENDOR_ID)
#error "Mcu.c : Mismatch in Vendor ID"
#endif /* (MCU_VENDOR_ID !\= MCU_CFG_VENDOR_ID) */

#if (MCU_MODULE_ID != MCU_CFG_MODULE_ID)
#error "Mcu.c : Mismatch in Module ID"
#endif /* \(MCU_MODULE_ID != MCU_CFG_MODULE_ID) */

#if (MCU_AR_RELEASE_MAJOR_VERSION != MCU_CFG_AR_RELEASE_MAJOR_VERSION)
#error "Mcu.c : Mismatch in Release Major Version"
#endif /* (MCU_AR_RELEASE_MAJOR_VERSION !\= MCU_CFG_AR_RELEASE_MAJOR_VERSION) */

#if (MCU_AR_RELEASE_MINOR_VERSION != MCU_CFG_AR_RELEASE_MINOR_VERSION)
#error "Mcu.c : Mismatch in Release Minor Version"
#endif /* (MCU_AR_RELEASE_MINOR_VERSION !\= MCU_CFG_AR_RELEASE_MINOR_VERSION) */

#if (MCU_AR_RELEASE_REVISION_VERSION != MCU_CFG_AR_RELEASE_REVISION_VERSION)
#error "Mcu.c : Mismatch in Release Revision Version"
#endif /* (MCU_AR_RELEASE_REVISION_VERSION !\= MCU_CFG_AR_RELEASE_REVISION_VERSION) */

#if (MCU_SW_MAJOR_VERSION != MCU_CFG_SW_MAJOR_VERSION)
#error "Mcu.c : Mismatch in Software Major Version"
#endif /* (MCU_SW_MAJOR_VERSION !\= MCU_CFG_SW_MAJOR_VERSION) */

#if (MCU_SW_MINOR_VERSION != MCU_CFG_SW_MINOR_VERSION)
#error "Mcu.c : Mismatch in Software Minor Version"
#endif /* (MCU_SW_MINOR_VERSION !\= MCU_CFG_SW_MINOR_VERSION) */

#if (MCU_SW_PATCH_VERSION != MCU_CFG_SW_PATCH_VERSION)
#error "Mcu.c : Mismatch in Software Patch Version"
#endif /* \(MCU_SW_PATCH_VERSION != MCU_CFG_SW_PATCH_VERSION) */

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
/* #Violation: Mcu_c_REF_3*/
/* #Violation: Mcu_c_REF_13*/
#define MCU_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_##Exclusive_Area()
/* #Violation: Mcu_c_REF_3*/
/* #Violation: Mcu_c_REF_13*/
#define MCU_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_##Exclusive_Area()
#define MCU_STM_FRENQUENCE_F                       (25000000.0f)
#define MCU_ROUGH_DELAY_500US                      (200000U) /* 400M * 500US */
#define MCU_SLEEP_MODE                             (0U)
#define MCU_TIME_OUT_COUNT                         (100000U) /* 4ms  time out,normally 2ms is OK*/

#if defined(THA6_THA6206D) || defined(THA6_THA6206)
#define CHIP_VER  (*(volatile uint32 *)CHIP_VERSION_ADDR)

#define CHIP_THA6206C_ASSCII (0X43000000U)  /* ASSC II 'C' */
#define CHIP_THA6206D_ASSCII (0X44000000U)  /* ASSC II 'D' */
#endif /* defined(\THA6_THA6206D)  */       

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
/* #Violation: Mcu_c_REF_19*/
#define MCU_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Mcu_c_REF_1*/
#include "Mcu_MemMap.h"

static Mcu_ResetType    Mcu_ResetStatus;
static Mcu_RawResetType Mcu_ResetRawStatus;
static uint32           Mcu_ClockSetId;
static P2CONST(Mcu_ConfigType, MCU_VAR_CLEARED, MCU_CONFIG_DATA) Mcu_ConfigPtr;
#if (MCU_DEV_ERROR_DETECT == STD_ON)
/* Global variable to store Initialization status of MCU Driver */
static Mcu_InitStatusType Mcu_InitialStatus;
#endif /* (MCU_DEV_ERROR_DETECT  \== STD_ON) */

/* #Violation: Mcu_c_REF_19*/
#define MCU_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Mcu_c_REF_1*/
#include "Mcu_MemMap.h"

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
/* #Violation: Mcu_c_REF_19*/
#define MCU_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Mcu_c_REF_1*/
#include "Mcu_MemMap.h"

static FUNC(Mcu_PllStatusType, MCU_CODE) Mcu_PllStatus
(
    void
);

static FUNC(boolean, MCU_PRIVATE_CODE) Mcu_InitGtmTriggers
(
    CONSTP2CONST(Mcu_GtmWrapperConfigType, AUTOMATIC, MCU_APPL_CONST) GTMWrapperConfigPtr
);

static FUNC(void, MCU_PRIVATE_CODE) Mcu_InitRamSectionInternal
(
    Mcu_RamSectionType RamSection
);

static FUNC(void, MCU_PRIVATE_CODE) Mcu_CalculateStmClockDivider
(
    P2VAR(boolean, AUTOMATIC, MCU_APPL_DATA) RegCheck,
    P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) Div
);

static FUNC(void, MCU_PRIVATE_CODE) Mcu_DistributePllClockInternal
(
    P2VAR(boolean, AUTOMATIC, MCU_APPL_DATA) RegCheck,
    P2VAR(Std_ReturnType, AUTOMATIC, MCU_APPL_DATA) ReturnValue
);

LOCAL_FORCEINLINE void Mcu_CopyDataToRam
(
    uint32 DataL, 
    uint32 DataH, 
    uint32* const Memory
);
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
 *   Function Name           : Mcu_PllStatus
 *
 *   Service ID              : 0xF1
 *
 *   Description             : This service return the integrated lock status of multiple PLLs.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : MCU_PLL_LOCKED: .
 *                             MCU_PLL_UNLOCKED: .
 *
 *   Preconditions           : MCU Driver component must be initialized.
 *
 *   AUTOSAR_Requirement
 ****************************************************************************************************/
static FUNC(Mcu_PllStatusType, MCU_CODE) Mcu_PllStatus
(
    void
)
{
    /* \[SWS_Mcu_00230]
     *The type Mcu_PllStatusType is the type of the return value of the function Mcu_GetPllStatus */
    Mcu_PllStatusType PllLockStatus;
    Rcc_PllStatus     PerPllStatus;
    Rcc_PllStatus     SysPllStatus;

    PllLockStatus = MCU_PLL_UNLOCKED;
    PerPllStatus = Rcc_Hal_GetPllStatus(RCC_PLLTYPE_PER);
    SysPllStatus = Rcc_Hal_GetPllStatus(RCC_PLLTYPE_SYS);
    /* both per, sys PLL are locked */
    if ((RCC_PLLSTATUS_READY == PerPllStatus) && (RCC_PLLSTATUS_READY == SysPllStatus))
    {
        PllLockStatus = MCU_PLL_LOCKED;
    }

    return PllLockStatus;
}

/****************************************************************************************************
*   Function Name           : Mcu_InitGtmTriggers
*
*   Service ID              : None
*
*   Description             : Initializes all GTM trigger configurations.
*
*   Parameters in           : GTMWrapperConfigPtr: Pointer to GTM wrapper configuration.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : boolean: TRUE if all initializations successful, FALSE otherwise.
*
*   Preconditions           : Configuration pointer is not NULL.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, MCU_PRIVATE_CODE) Mcu_InitGtmTriggers
(
    CONSTP2CONST(Mcu_GtmWrapperConfigType, AUTOMATIC, MCU_APPL_CONST) GTMWrapperConfigPtr
)
{
    uint8   Index;
    boolean RegCheck;

    RegCheck = TRUE;

    /* #Violation: Mcu_c_REF_5*/
    for (Index = 0U; Index < GTMWrapperConfigPtr->NumofToutCfg; Index++)
    {
        RegCheck &= Gtm_Trig_Hal_ToutOut(&GTMWrapperConfigPtr->ToutConfigPtr[Index]);
    }

    /* init Port to TIM*/
    /* #Violation: Mcu_c_REF_5*/
    for (Index = 0U; Index < GTMWrapperConfigPtr->NumofTimCfg; Index++)
    {
        RegCheck &= Gtm_Trig_Hal_TimIn(&GTMWrapperConfigPtr->TimConfigPtr[Index]);
    }

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    /* init TIM to DSADC */
    /* #Violation: Mcu_c_REF_5*/
    for (Index = 0U; Index < GTMWrapperConfigPtr->NumofDsadcCfg; Index++)
    {
        RegCheck &= Gtm_Trig_Hal_DsadcIn(&GTMWrapperConfigPtr->DsadcConfigPtr[Index]);
    }
    /* init GTM to DSADC */
    /* #Violation: Mcu_c_REF_5*/
    for (Index = 0U; Index < GTMWrapperConfigPtr->NumofToDsadcCfg; Index++)
    {
        RegCheck &= Gtm_Trig_Hal_ToDsadc(&GTMWrapperConfigPtr->GtmToDsadcConfigPtr[Index]);
    }
    /* init GTM to MSC level1 */
    /* #Violation: Mcu_c_REF_5*/
    for (Index = 0U; Index < GTMWrapperConfigPtr->NumofMscCfg; Index++)
    {
        RegCheck &= Gtm_Trig_Hal_ToMscL1(&GTMWrapperConfigPtr->MscConfigPtr[Index]);
    }
    /* init GTM to MSC Level2 */
    /* #Violation: Mcu_c_REF_5*/
    for (Index = 0U; Index < GTMWrapperConfigPtr->NumofMscL2Cfg; Index++)
    {
        RegCheck &= Gtm_Trig_Hal_ToMscL2(&GTMWrapperConfigPtr->Gtm_MscSetL2ConfigPtr[Index]);
    }
#endif /* (THA6_THA6206) (THA6_THA6412)*/

    /* init GTM to SARADC */
    /* #Violation: Mcu_c_REF_5*/
    for (Index = 0U; Index < GTMWrapperConfigPtr->NumofTAdcCfg; Index++)
    {
        RegCheck &= Gtm_Trig_Hal_ToSaradc(&GTMWrapperConfigPtr->AdcConfigPtr[Index]);
    }

    /* init GTM to DMA */
    /* #Violation: Mcu_c_REF_5*/
    for (Index = 0U; Index < GTMWrapperConfigPtr->NumofDmaCfg; Index++)
    {
        RegCheck &= Gtm_Trig_Hal_ToDmaL1(&GTMWrapperConfigPtr->DmaConfigPtr[Index]);
    }
    /* init GTM to DMA LEVEL2 */
    /* #Violation: Mcu_c_REF_5*/
    for (Index = 0U; Index < GTMWrapperConfigPtr->NumofDmaL2Cfg; Index++)
    {
        RegCheck &= Gtm_Trig_Hal_ToDmaL2(&GTMWrapperConfigPtr->DmaL2ConfigPtr[Index]);
    }

    return RegCheck;
}

/****************************************************************************************************
*   Function Name           : Mcu_InitRamSectionInternal
*
*   Service ID              : None
*
*   Description             : Internal function to initialize RAM section with critical section protection.
*
*   Parameters in           : RamSection: RAM section identifier.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Parameters validated and module initialized.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, MCU_PRIVATE_CODE) Mcu_InitRamSectionInternal
(
    Mcu_RamSectionType RamSection
)
{
    uint32 RamStartAddress;
    uint32 WriteSize;
    uint32 NoOfByte;
    uint32 DataLword;

    /* #Violation: Mcu_c_REF_2*/
    RamStartAddress = (uint32)Mcu_ConfigPtr->RamSettingPtr[RamSection].RamSectionBaseAddrPtr;
    /* Get the size of RAM section */
    NoOfByte = Mcu_ConfigPtr->RamSettingPtr[RamSection].RamSectionSize;
    /* Get initial value */
    DataLword = (uint32)Mcu_ConfigPtr->RamSettingPtr[RamSection].RamDefaultValue;
    /* Set WriteSize for one write operation */
    WriteSize = (uint32)Mcu_ConfigPtr->RamSettingPtr[RamSection].RamWriteSize;
    
    MCU_ENTER_CRITICAL_SECTION(Mcu_InitRamSection);
    /* \[SWS_Mcu_00011] */
    if (MCAL_EIGHT == WriteSize)
    {
        DataLword |= (DataLword << 8U);
        DataLword |= (DataLword << 16U);

        /* the NoOfByte and RamStartAddress are align with 16bytes. Restricted by EB tools */
        while (MCAL_EIGHT <= NoOfByte)
        {
        /* Initialize RAM area with the value */
        /* #Violation: Mcu_c_REF_4*/
        /* #Violation: Mcu_c_REF_21*/
        /* #Violation: Mcu_c_REF_22*/
        /* #Violation: Mcu_c_REF_2*/
        /* #Violation: Mcu_c_REF_12*/
        /* #Violation: Mcu_c_REF_14*/
        Mcu_CopyDataToRam((uint32)DataLword, (uint32)DataLword, (uint32 *)RamStartAddress);
        /* Decrement the size */
        NoOfByte -= WriteSize;
        /* Increment the pointer of RAM Section address */
        RamStartAddress += WriteSize;
        }
    }
    else if (MCAL_ONE == WriteSize)
    {
        /* the NoOfByte and RamStartAddress are align with 16bytes. Restricted by EB tools */
        while (MCAL_ONE <= NoOfByte)
        {
        /* Initialize RAM area with the value */
        /* #Violation: Mcu_c_REF_2*/
        /* #Violation: Mcu_c_REF_12*/
        /* #Violation: Mcu_c_REF_14*/
        *(uint8 *)RamStartAddress = (uint8)DataLword;
        /* Decrement the size */
        NoOfByte -= WriteSize;
        /* Increment the pointer of RAM Section address */
        RamStartAddress += WriteSize;
        }
    }
    else if (MCAL_FOUR == WriteSize)
    {
        DataLword |= (DataLword << 8U);
        DataLword |= (DataLword << 16U);
        /* the NoOfByte and RamStartAddress are align with 16bytes. Restricted by EB tools */
        while (MCAL_FOUR <= NoOfByte)
        {
        /* Initialize RAM area with the value */
        /* #Violation: Mcu_c_REF_2*/
        /* #Violation: Mcu_c_REF_12*/
        /* #Violation: Mcu_c_REF_14*/
        *(uint32 *)RamStartAddress = (uint32)DataLword;
        /* Decrement the size */
        NoOfByte -= WriteSize;
        /* Increment the pointer of RAM Section address */
        RamStartAddress += WriteSize;
        }
    }
    else if (MCAL_TWO == WriteSize)
    {
        DataLword |= (DataLword << 8U);
        /* the NoOfByte and RamStartAddress are align with 16bytes. Restricted by EB tools */
        while (MCAL_TWO <= NoOfByte)
        {
        /* Initialize RAM area with the value */
        /* #Violation: Mcu_c_REF_2*/
        /* #Violation: Mcu_c_REF_12*/
        /* #Violation: Mcu_c_REF_14*/
        *(uint16 *)RamStartAddress = (uint16)DataLword;
        /* Decrement the size */
        NoOfByte -= WriteSize;
        /* Increment the pointer of RAM Section address */
        RamStartAddress += WriteSize;
        }
    }
    /* #Violation: Mcu_c_REF_11*/
    else
    {
        /* error */
    }
    MCU_EXIT_CRITICAL_SECTION(Mcu_InitRamSection);
}

/****************************************************************************************************
*   Function Name           : Mcu_CalculateStmClockDivider
*
*   Service ID              : None
*
*   Description             : Calculates the STM clock divider based on system clock source frequency.
*
*   Parameters in           : None.
*
*   Parameters inout        : RegCheck: Pointer to register check status.
*                             Div: Pointer to store calculated divider value.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, MCU_PRIVATE_CODE) Mcu_CalculateStmClockDivider
(
    P2VAR(boolean, AUTOMATIC, MCU_APPL_DATA) RegCheck,
    P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) Div
)
{
    float32 SystemClockSourceFreq;

    /* HSI source change to SYSPLL, STM clock is 25MHz */
    SystemClockSourceFreq = Rcc_Hal_GetSysClkSrcFreq();
    if (SystemClockSourceFreq >= MCU_STM_FRENQUENCE_F)
    {
        *Div = (uint32)((uint32)SystemClockSourceFreq / (uint32)MCU_STM_FRENQUENCE_F);
        if (*Div > 32U)
        {
            *Div = 32U;
        }
    }
    else
    {
        *Div = 1U;
        /* error */
        *RegCheck = 0U;
    }
}
/****************************************************************************************************
*   Function Name           : Mcu_DistributePllClockInternal
*
*   Service ID              : None
*
*   Description             : Internal function to distribute PLL clock with all configurations.
*
*   Parameters in           : None.
*
*   Parameters inout        : RegCheck: Pointer to register check status.
*                             ReturnValue: Pointer to return value.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : PLL is locked and parameters are validated.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, MCU_PRIVATE_CODE) Mcu_DistributePllClockInternal
(
    P2VAR(boolean, AUTOMATIC, MCU_APPL_DATA) RegCheck,
    P2VAR(Std_ReturnType, AUTOMATIC, MCU_APPL_DATA) ReturnValue
)
{
    Mcu_PllStatusType   PllLockStatus;
    Mcu_PerClockSrcType Mcu_PerClockSrc;
    uint32              Div;
    uint32              Index;
    float32             SysClk;
    boolean             NewFreqIsHigher;
    Std_ReturnType      LockStatus;
    uint8               cpuclkdiv;
    uint64              StartTime;
    uint64              OverTime;
    uint64              EndTime;
    uint32              StmFrequency;

    PllLockStatus = Mcu_PllStatus();

    /* \[SWS_Mcu_00142]  called before PLL has locked*/
    /* Report to DET, if PLL has been detected as non-locked */
    if (MCU_PLL_UNLOCKED == PllLockStatus)
    {
        /* \[SWS_Mcu_00122] [SWS_Mcu_00142]:If the function Mcu_DistributePllClock is called
         * before PLL has locked, this function shall return E_NOT_OK immediately, without any
         * further action.()*/
#if (MCU_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void)Det_ReportError(
            MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_DISTRIBUTEPLLCLOCK_SID, MCU_E_PLL_NOT_LOCKED);
#endif /* (MCU_DEV_ERROR_DETECT  \== STD_ON) */
    }
    else
    {
        SysClk = Rcc_Hal_GetSysClkFreq();
        if ((uint32)SysClk <= Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId].SysClkFrequency)
        {
            NewFreqIsHigher = TRUE;
            /*update Rdt time*/
            (void)Flash_Hal_PFlashSwitchFreq(
                Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId].SysClkFrequency);
            (void)Flash_Hal_DFlashSwitchFreq(
                Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId].SysClkFrequency);
        }
        else
        {
            NewFreqIsHigher = FALSE;
        }
        MCU_ENTER_CRITICAL_SECTION(Mcu_DistributePllClock);

        /* All pointers are not NULLPTR, which is restricted by EB  */
        *RegCheck &= Rcc_Hal_ConfigSaradcClk(
            Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId].SarAdcClkCfgPtr->ClkSrc);
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
        /*dsadc div is lower8 bit, rdc div is from 8 to 15 bit*/
        *RegCheck &= Rcc_Hal_ConfigRdcDsadcClk(
            Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId].DsadcRdcClkCfgPtr->ClkSrc,
            (uint8)(Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId].DsadcRdcClkCfgPtr->Div >> 8U),
            (uint8)(Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId].DsadcRdcClkCfgPtr->Div));
        *RegCheck &= Rcc_Hal_ConfigMscClk(
            Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId].MscClkCfgPtr->ClkSrc);                
#endif

        *RegCheck &= Rcc_Hal_ConfigEspiClk(
            Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId].EspiClkCfgPtr->ClkSrc,
            (uint8)Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId].EspiClkCfgPtr->Div);

        *RegCheck &= Rcc_Hal_ConfigWdtClk(
            Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId].WdtClkCfgPtr->ClkSrc,
            (uint8)Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId].WdtClkCfgPtr->Div);

        *RegCheck &= Rcc_Hal_ConfigCanClk(
            Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId].CanClkCfgPtr->ClkSrc,
            (uint8)Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId].CanClkCfgPtr->Div);
#if defined(THA6_THA6104)
        /* fixed the ASI baud bus clock and buad clock as max (100MHZ AIS BAUD), (50MHZ ASI baud BUS)  */
        *RegCheck &= Rcc_Hal_ConfigAsiBaudBusClk(RCC_MODULECLOCKSOURCE_PERPLL, 3U);
#endif /* THA6_THA6104 */
        /* Enable the DMA0_EN RCC_CLKEN1 */
        /* #Violation: Mcu_c_REF_18*/
        *RegCheck &= Rcc_Hal_SetModuleClk(
            RCC_MODULECLKTYPE_DMA0CLK,
            /* #Violation: Mcu_c_REF_9*/
            (Rcc_ModuleClkSet)Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId]
                .DmaClkCfgPtr->DMA0CkEn);
        /* Enable the DMA2_EN RCC_CLKEN1 */
        /* #Violation: Mcu_c_REF_18*/
        *RegCheck &= Rcc_Hal_SetModuleClk(
            RCC_MODULECLKTYPE_DMA2CLK,
            /* #Violation: Mcu_c_REF_9*/
            (Rcc_ModuleClkSet)Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId]
                .DmaClkCfgPtr->DMA2CkEn);

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
        /* Enable the DMA1_EN RCC_CLKEN1 *//* #Violation: Mcu_c_REF_9*/
        *RegCheck &= Rcc_Hal_SetModuleClk(
            RCC_MODULECLKTYPE_DMA1CLK,
            /* #Violation: Mcu_c_REF_9*/
            (Rcc_ModuleClkSet)Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId]
                .DmaClkCfgPtr->DMA1CkEn);
        /* Enable the DMA3_EN RCC_CLKEN1 *//* #Violation: Mcu_c_REF_9*/
        *RegCheck &= Rcc_Hal_SetModuleClk(
            RCC_MODULECLKTYPE_DMA3CLK,
            /* #Violation: Mcu_c_REF_9*/
            (Rcc_ModuleClkSet)Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId]
                .DmaClkCfgPtr->DMA3CkEn);
#endif /* THA6_THA6412 / THA6_THA6206 */

        MCU_EXIT_CRITICAL_SECTION(Mcu_DistributePllClock);
        for (Index = 0U; Index < MCU_NUM_BASETIMER; Index++)
        {
            Mcu_PerClockSrc = Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId]
                                  .BaseTimerClkCfgPtr->BaseTimer[Index]
                                  .ClkSrc;
            Div = Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId]
                      .BaseTimerClkCfgPtr->BaseTimer[Index]
                      .Div;
            *RegCheck &=
            /* #Violation: Mcu_c_REF_9*/
                Rcc_Hal_ConfigBaseTimerClk((Rcc_BasetimerIdx)Index, Mcu_PerClockSrc, (uint16)Div);
        }

        /* GTM cmu tbu init */
        if (NULL_PTR != Mcu_ConfigPtr->TBUConfigPtr)
        {
            *RegCheck &= Gtm_TimeBase_Hal_InitFreeTimer(
                (const Gtm_FreeTimerConfig *)Mcu_ConfigPtr->TBUConfigPtr);
        }

        /* GTM clock cmu init */
        *RegCheck &= Gtm_TimeBase_Hal_InitClock(Mcu_ConfigPtr->Gtm_ClockConfigPtr);
        /* GTM cmu clk init */
        MCU_ENTER_CRITICAL_SECTION(Mcu_DistributePllClock);

        *RegCheck &= Rcc_Hal_ConfigGtmClk(
            Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId].GtmClkCfgPtr->ClkSrc,
            (uint8)Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId].GtmClkCfgPtr->Div);
        /* \[SWS_Mcu_00140] The function Mcu_DistributePllClock shall activate the PLL clock to
         * the MCU clock distribution*/

        *RegCheck &= Rcc_Hal_ConfigBusClk(
            Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId].SysClkCfgPtr->SysDiv,
            Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId].SysClkCfgPtr->AxiDiv,
            Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId].SysClkCfgPtr->ApbDiv);

        /* When all cores of THA6412 are activated, the clock frequency is directly increased from
         * 100MHz to 400MHz. The sudden change in current may affect the startup of VDD low
         * voltage, and it may not be able to start at 0.81V. It is necessary to perform a
         * step-by-step startup of the clock.*/
        /* make sure cpuclk > (stmclk*2) */
        *RegCheck &= Rcc_Hal_ConfigStmClk(31);

        *RegCheck &= Rcc_Hal_ConfigCpuClk(
            Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId].SysClkCfgPtr->ClkSrc, 15U);
        MCU_EXIT_CRITICAL_SECTION(Mcu_DistributePllClock);
        cpuclkdiv = 8U;

        /*Configure CPU_CLK with step. 25 to 400MHZ */
        while (cpuclkdiv != 0U)
        {                
            MCU_ENTER_CRITICAL_SECTION(Mcu_DistributePllClock);
            *RegCheck &= Rcc_Hal_ConfigCpuClk(
                Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId].SysClkCfgPtr->ClkSrc, (cpuclkdiv-1U));
            MCU_EXIT_CRITICAL_SECTION(Mcu_DistributePllClock);
            /* #Violation: Mcu_c_REF_8*/
            StmFrequency = (uint32)Mcal_GetSystemTimerFreq();
            /*Delay 100us*/
            OverTime = (uint64)100ULL * StmFrequency / 1000000ULL;
            /* #Violation: Mcu_c_REF_8*/
            StartTime = Mcal_GetSystemTimerCount(); /* Get system counter */
            do
            {
            /* #Violation: Mcu_c_REF_8*/
                EndTime = Mcal_GetSystemTimerCount() - StartTime;
            } while (EndTime < OverTime);
            /* step */
            cpuclkdiv = cpuclkdiv >> 1U;
        }
        MCU_ENTER_CRITICAL_SECTION(Mcu_DistributePllClock);

        /* Set Cpu clock to configurate value */
        /* #Violation: Mcu_c_REF_24*/
        *RegCheck &= Rcc_Hal_ConfigCpuClk(
            Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId].SysClkCfgPtr->ClkSrc,
            Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId].SysClkCfgPtr->CpuDiv);

        /* Calculate STM clock divider */
        Mcu_CalculateStmClockDivider(RegCheck, &Div);

        *RegCheck &= Rcc_Hal_ConfigStmClk((uint8)(Div - 1U));
    
        MCU_EXIT_CRITICAL_SECTION(Mcu_DistributePllClock);

        if (FALSE == NewFreqIsHigher)
        {
            /*update Rdt time*/
            (void)Flash_Hal_PFlashSwitchFreq(
                Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId].SysClkFrequency);
            (void)Flash_Hal_DFlashSwitchFreq(
                Mcu_ConfigPtr->ClockSettingPtr[Mcu_ClockSetId].SysClkFrequency);
        }

        LockStatus = Mcal_GetLock(MCAL_LOCK_ID_MCU);
        if(E_OK == LockStatus)
        {  
            /* GTM trigger source init ,after all clock is set*/
            for (Index = 0U; Index < Mcu_ConfigPtr->NumofTrigCfg; Index++)
            {
                *RegCheck &= Gtm_Pwm_Hal_InitChannel(
                    &(Mcu_ConfigPtr->GtmTriggerCfgPtr[Index].GtmChannelIndex),
                    &(Mcu_ConfigPtr->GtmTriggerCfgPtr[Index].GtmChannelConfig));
            }
            Mcal_ReleaseLock(MCAL_LOCK_ID_MCU);
        }
        else
        {
            *RegCheck = FALSE;
        }
        *ReturnValue = E_OK;
    }
}
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
 *   Function Name           : Mcu_Init
 *
 *   Service ID              : 0x00
 *
 *   Description             : This service initializes the MCU driver.
 *
 *   Parameters in           : ConfigPtr - Pointer to MCU Driver Configuration set.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Mcu_00153.[SWS_Mcu_00026] [SWS_Mcu_00116] [SWS_Mcu_00244]
 *   [SWS_Mcu_00245] [SWS_Mcu_00246] [SWS_Mcu_00247]:[SWS_Mcu_00126]:
 ****************************************************************************************************/
/* #Violation: Mcu_c_REF_17*/
FUNC(void, MCU_CODE) Mcu_Init
(
/* #Violation: Mcu_c_REF_15*/
    P2CONST(Mcu_ConfigType, AUTOMATIC, MCU_CONFIG_DATA) ConfigPtr
)
{
    /* #Violation: Mcu_c_REF_16*/
    uint8 Index;
#if (MCU_DEV_ERROR_DETECT == STD_ON)
    Mcal_CoreType CoreId;
#endif /* (MCU_DEV_ERROR_DETECT  \== STD_ON) */
    boolean RegCheck;
    Port_EsrConfig Port_Esr;
    Port_Esr.inputDis = FALSE;
    Port_Esr.pPadDriverCfg = NULL_PTR;
    Port_Esr.outputEn = FALSE;
    Port_Esr.pullResistor = PORT_ESR_PULL_NO;
    RegCheck = TRUE;
    
#if defined(THA6_THA6206)
    if(CHIP_THA6206D_ASSCII == CHIP_VER) /* C series or earlier series */
    {
        (void)Det_ReportRuntimeError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_INIT_SID, MCU_E_CHIP_MISMATCH);
    }
    
#endif /* defined(\THA6_THA6206)  */       
#if defined(THA6_THA6206D)

    if(CHIP_THA6206D_ASSCII != CHIP_VER)/* assc II 'D' */
    {
        (void)Det_ReportRuntimeError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_INIT_SID, MCU_E_CHIP_MISMATCH);
    }
    
#endif /* defined(\THA6_THA6206D)  */

#if (MCU_DEV_ERROR_DETECT == STD_ON)
    /* #Violation: Mcu_c_REF_8*/
    CoreId = Mcal_GetCoreId();

    /* Report to DET, if configuration pointer is NULL pointer */
    if (NULL_PTR == ConfigPtr)
    {
        /* Report to DET */
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_INIT_SID, MCU_E_PARAM_CONFIG);
    }
    else if (CoreId != MCAL_MASTER_CORE)
    {
        /* Report to DET */
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_INIT_SID, MCU_E_CORE_MISMATCH);
    }
    else
#endif /* (MCU_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* GTM wrapper init */
        RegCheck &= Mcu_GtmWrapperInit(ConfigPtr->GTMWrapperConfigPtr);

        /* \[SWS_Mcu_00144] The function Mcu_PerformReset shall perform the reset type which is
         * configured in the configuration set */
        /* \ECUC_Mcu_00173 Reset Init */
        for (Index = 0U; Index < MCU_RESET_CONFIG_NUM; Index++)
        {
            if (RCC_RSTTYPE_NONE != ConfigPtr->ResetConfigPtr[Index].ResetType)
            {
                if (RCC_RSTSRC_ESR0 == ConfigPtr->ResetConfigPtr[Index].SrcType)
                {
                    MCU_ENTER_CRITICAL_SECTION(Mcu_Init);
                    (void)Port_Hal_Esr_ClearAppResetIndicator();
                    Port_Esr.pin = PORT_ESR_PIN_0;
                    Port_Esr.outputSel = PORT_ESR_OUTPUTSEL_SYSRESET;
                    RegCheck &= Port_Hal_Esr_Init(&Port_Esr);
                    MCU_EXIT_CRITICAL_SECTION(Mcu_Init);

                }
                else if (RCC_RSTSRC_ESR1 == ConfigPtr->ResetConfigPtr[Index].SrcType)
                {
                    MCU_ENTER_CRITICAL_SECTION(Mcu_Init);
                    (void)Port_Hal_Esr_ClearAppResetIndicator();
                    Port_Esr.pin = PORT_ESR_PIN_1;
                    Port_Esr.outputSel = PORT_ESR_OUTPUTSEL_APPRESET;
                    RegCheck &= Port_Hal_Esr_Init(&Port_Esr);
                    MCU_EXIT_CRITICAL_SECTION(Mcu_Init);
                }
                else
                {
                    /*DO NONE*/
                }
            }
            MCU_ENTER_CRITICAL_SECTION(Mcu_Init);
            /* Reset type init */
            RegCheck &= Rcc_Hal_InitRstType(
                ConfigPtr->ResetConfigPtr[Index].SrcType, ConfigPtr->ResetConfigPtr[Index].ResetType);
            MCU_EXIT_CRITICAL_SECTION(Mcu_Init);
        }
        MCU_ENTER_CRITICAL_SECTION(Mcu_Init);
        RegCheck &= Rcc_Hal_SetRstTimeoutCnt(MCU_RSTSOURCE_TIMEOUT_VALUE);
        MCU_EXIT_CRITICAL_SECTION(Mcu_Init);
        /* \[SWS_Mcu_00235] [SWS_Mcu_00236]*/
        Mcu_ResetRawStatus = Rcc_Hal_ReadRstStatusReg();
        /* #Violation: Mcu_c_REF_9*/
        Mcu_ResetStatus = (Mcu_ResetType)Rcc_Hal_ReadRstStatus();

#if (MCU_CLR_COLD_RESET_STAT_API == STD_OFF)
        MCU_ENTER_CRITICAL_SECTION(Mcu_Init);
        /* #Violation: Mcu_c_REF_9*/
        RegCheck &= Rcc_Hal_ClearRstStatus((Rcc_RstReason)Mcu_ResetStatus);
        MCU_EXIT_CRITICAL_SECTION(Mcu_Init);
#endif

#if (defined(MCAL_MODULE_CFG_DSADC_USED) && (MCAL_MODULE_CFG_DSADC_USED == STD_ON))
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)

        MCU_ENTER_CRITICAL_SECTION(Mcu_Init);
        RegCheck &= Pwrc_Hal_SetDsadcRefCurrent(PWRC_FUNCTION_ENABLE);
        MCU_EXIT_CRITICAL_SECTION(Mcu_Init);
#endif /* defined(\THA6_THA6412) || defined(\THA6_THA6206) */       
#endif /* (defined(MCAL_MODULE_CFG_DSADC_USED) && (MCAL_MODULE_CFG_DSADC_USED \== STD_ON)) */
        Mcu_ConfigPtr = ConfigPtr;

#if (MCU_DEV_ERROR_DETECT == STD_ON)
        /* Set the Global Status */
        Mcu_InitialStatus = MCU_INITIALIZED;
#endif /* (MCU_DEV_ERROR_DETECT  \== STD_ON) */
    }
    if (FALSE == RegCheck)
    {
#if (MCU_SAFETY_ENABLE == STD_ON)
        (void)Det_ReportRuntimeError(
            MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_INIT_SID, MCU_E_REG_CHECK_FAIL);
#endif /* (MCU_SAFETY_ENABLE  \== STD_ON) */
    }

}

/****************************************************************************************************
 *   Function Name           : Mcu_CopyDataToRam
 *
 *   Service ID              :
 *
 *   Description             : This service initializes the RAM, 64 bits each time. to avoid ecc error
 *
 *   Parameters in           : DataL data low word
                               DataH data high word
                               Memory addr to be write.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            :
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Mcu_00154.
 *
 ****************************************************************************************************/
/* #Violation: Mcu_c_REF_7*/
LOCAL_FORCEINLINE void Mcu_CopyDataToRam
(
/* #Violation: Mcu_c_REF_20*/
    uint32 DataL, 
/* #Violation: Mcu_c_REF_20*/
    uint32 DataH, 
/* #Violation: Mcu_c_REF_20*/
    uint32* const Memory
)
{
    /* #Violation: Mcu_c_REF_4*/
    /* #Violation: Mcu_c_REF_21*/
    /* #Violation: Mcu_c_REF_22*/
    ASM_VOLATILE("   mov r4, %0         \n"
                 "   mov r5, %1         \n"
                 "   mov r6, %2         \n"
                 "   strd r4, r5, [r6]  \n"
                 :
                 : "r"(DataL), "r"(DataH), "r"(Memory)
                 : "r4", "r5", "r6");
}

/****************************************************************************************************
 *   Function Name           : Mcu_InitRamSection
 *
 *   Service ID              : 0x01
 *
 *   Description             : This service initializes the RAM section wise.
 *
 *   Parameters in           : RamSection - Id for RAM section.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : E_OK: Ram is initialized successfully.
 *                             E_NOT_OK: Ram is failed to initialized.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Mcu_00154.[SWS_Mcu_00030]:
 *   [SWS_Mcu_00239] The Mcu_RamSectionType specifies the identification (ID) for a RAM section,
 *   configured via the configuration structure
 *   [SWS_Mcu_00011]
 ****************************************************************************************************/
/* #Violation: Mcu_c_REF_17*/
FUNC(Std_ReturnType, MCU_CODE) Mcu_InitRamSection
(
    Mcu_RamSectionType RamSection
)
{
    Std_ReturnType ReturnValue;
    /* \[SWS_Mcu_00017] */
    /* Initialize return value with E_NOT_OK */
    ReturnValue = E_NOT_OK;

#if (MCU_DEV_ERROR_DETECT == STD_ON)
    /* \[SWS_Mcu_00136]*/
    /* Report to DET, if the component is not initialized */
    if (MCU_UNINITIALIZED == Mcu_InitialStatus)
    {
        /* Report to DET */
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_INITRAMSECTION_SID, MCU_E_UNINIT);
    }
    /* \[SWS_Mcu_00021] RamSection shall be within the sections defined in the
       configuration data structure. Related error value: MCU_E_PARAM_RAMSECTION*/
    else if (Mcu_ConfigPtr->NoOfRamConfigs <= RamSection)
    {
        /* Report to DET */
        (void)Det_ReportError(
            MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_INITRAMSECTION_SID, MCU_E_PARAM_RAMSECTION);
    }
    else
#endif /* (MCU_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Get the start address of the RAM section */
        /* EB guarantees that when NoOfRamConfig is not 0, RamSettingDtr is not NULL_PTR */
        Mcu_InitRamSectionInternal(RamSection);
        ReturnValue = E_OK;
    }

    /* Return the value of RAM initialization result */
    return ReturnValue;
}

/* \[SWS_Mcu_00210] function is available if the former parameter is set to TRUE */
#if (MCU_INIT_CLOCK == STD_ON)

/****************************************************************************************************
 *   Function Name           : Mcu_InitClock
 *
 *   Service ID              : 0x02
 *
 *   Description             : This service initializes the PLL and other MCU specific
 *                             clock options.
 *
 *   Parameters in           : ClockSetting - Id for Clock setting.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : E_OK: Clock is initialized successfully.
 *                             E_NOT_OK: Clock is failed to initialized.
 *
 *   Preconditions           : MCU Driver component must be initialized.
 *
 *   AUTOSAR_Requirement     : SWS_Mcu_00155.
 *   [SWS_Mcu_00248]
 *    provide a service to enable and set the MCU clock
 *    [SWS_Mcu_00232]:The type Mcu_ClockType defines the identification (ID) for clock setting
 *    configured via the configuration structure
 ****************************************************************************************************/
/* #Violation: Mcu_c_REF_17*/
FUNC(Std_ReturnType, MCU_CODE) Mcu_InitClock
(
    Mcu_ClockType ClockSetting
)
{
    Std_ReturnType ReturnValue;
    /* #Violation: Mcu_c_REF_16*/
    boolean        RegCheck;
#if (MCU_DEV_ERROR_DETECT == STD_ON)
    Mcal_CoreType CoreId;
#endif /* (MCU_DEV_ERROR_DETECT  \== STD_ON) */
    ReturnValue = E_NOT_OK;
    RegCheck    = TRUE;
#if (MCU_DEV_ERROR_DETECT == STD_ON)
    /* #Violation: Mcu_c_REF_8*/
    CoreId = Mcal_GetCoreId();
    /* \[SWS_Mcu_00139]*/
    /* Report to DET, if the component is not initialized */
    if (MCU_UNINITIALIZED == Mcu_InitialStatus)
    {
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_INITCLOCK_SID, MCU_E_UNINIT);
    }
    else if (CoreId != MCAL_MASTER_CORE)
    {
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_INITCLOCK_SID, MCU_E_CORE_MISMATCH);
    }
    /* \[SWS_Mcu_00019] ClockSetting shall be within the settings defined in the
       configuration data structure. Related error value: MCU_E_PARAM_CLOCK*/
    else if ((MCU_NUM_CLOCK_SETTING - MCAL_ONE) < ClockSetting)
    {
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_INITCLOCK_SID, MCU_E_PARAM_CLOCK);
    }
    else
#endif /* (MCU_DEV_ERROR_DETECT  \== STD_ON) */
    {
        MCU_ENTER_CRITICAL_SECTION(Mcu_InitClock);

        ReturnValue = (Std_ReturnType)Rcc_Hal_EnableHse(MCU_TIME_OUT_COUNT);
        MCU_EXIT_CRITICAL_SECTION(Mcu_InitClock);
        /* \[SWS_Mcu_00051] The MCU driver follows the standardized AUTOSAR concept    to
         * report production errors. The provided callback routines are specified in the
         * Diagnostic Event Manager (DEM) specification*/
        /* \[SWS_Mcu_00226]: Production Errors shall not be used as the return value of the called
         * function. */
        /* \[SWS_Mcu_00257] Fail criteria for MCU_E_CLOCK_FAILURE: a clock source failure occurs ()
         * [SWS_Mcu_00258]Pass criteria for MCU_E_CLOCK_FAILURE: no clock source failure occurs
         * () */
        if (E_OK != ReturnValue)
        {
#if (MCU_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(
                MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_INITCLOCK_SID, MCU_E_INIT_FAILED);
#endif /* (MCU_DEV_ERROR_DETECT  \== STD_ON) */

#if (MCU_DEM_REPORT_ERROR_STATUS == STD_ON)
            Dem_SetEventStatus(MCU_E_CLOCK_FAILURE, DEM_EVENT_STATUS_FAILED);
#endif /* (MCU_DEM_REPORT_ERROR_STATUS  \== STD_ON) */
        }
        else
        {
#if (MCU_DEM_REPORT_ERROR_STATUS == STD_ON)
            Dem_SetEventStatus(MCU_E_CLOCK_FAILURE, DEM_EVENT_STATUS_PASSED);
#endif /* (MCU_DEM_REPORT_ERROR_STATUS  \== STD_ON) */

            /* \[SWS_Mcu_00137] initialize the PLL and other MCU specific clock options*/
            /* \[SWS_Mcu_00138]  shall return without waiting until the PLL is locked*/
            /* SysPllCfgPtr and PerPllCfgPtr never be nullptr */
            MCU_ENTER_CRITICAL_SECTION(Mcu_InitClock);
            RegCheck &= Rcc_Hal_ConfigSysPll(Mcu_ConfigPtr->ClockSettingPtr[ClockSetting].SysPllCfgPtr);
            RegCheck &= Rcc_Hal_ConfigPerPll(Mcu_ConfigPtr->ClockSettingPtr[ClockSetting].PerPllCfgPtr);
            MCU_EXIT_CRITICAL_SECTION(Mcu_InitClock);

            Mcu_ClockSetId = ClockSetting;
            ReturnValue = E_OK;
        }
    }
    if (FALSE == RegCheck)
    {
        ReturnValue = E_NOT_OK;
#if (MCU_SAFETY_ENABLE == STD_ON)
        (void)Det_ReportRuntimeError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_INITCLOCK_SID, MCU_E_REG_CHECK_FAIL);
#endif /* (MCU_SAFETY_ENABLE \== STD_ON)*/
    }
    /* Return the value of clock initialization result */
    return ReturnValue;
}
#endif /* (MCU_INIT_CLOCK  \== STD_ON) */


/* \[SWS_Mcu_00205] available if the pre-compile parameter McuNoPll is set to FALSE*/
#if (MCU_NO_PLL == STD_OFF)
/****************************************************************************************************
 *   Function Name           : Mcu_DistributePllClock
 *
 *   Service ID              : 0x03
 *
 *   Description             : This service activates the PLL clock to the MCU clock distribution.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : E_OK: Command has been accepted.
 *                             E_NOT_OK: Command has not been accepted .
 *
 *   Preconditions           : MCU Driver component must be initialized.
 *
 *   AUTOSAR_Requirement     : SWS_Mcu_00156.[SWS_Mcu_00141]
 *                           [SWS_Mcu_00056]: (Not Applicable) The function Mcu_DistributePllClock
 *                            shall return without affecting the MCU hardware if the PLL clock has 
 *                            been automatically activated by the MCU hardware
 ****************************************************************************************************/
/* #Violation: Mcu_c_REF_17*/
FUNC(Std_ReturnType, MCU_CODE) Mcu_DistributePllClock
(
    void
)
{
    Std_ReturnType      ReturnValue;
    boolean             RegCheck;

    /* \[SWS_Mcu_00125]: */
#if (MCU_DEV_ERROR_DETECT == STD_ON)
    Mcal_CoreType CoreId;
#endif /* (MCU_DEV_ERROR_DETECT  \== STD_ON) */

    ReturnValue = E_NOT_OK;
    RegCheck = TRUE;
#if (MCU_DEV_ERROR_DETECT == STD_ON)
    /* #Violation: Mcu_c_REF_8*/
    CoreId = Mcal_GetCoreId();

    /* Report to DET, if module is not initialized */
    if (MCU_UNINITIALIZED == Mcu_InitialStatus)
    {
        /* Report to DET */
        (void)Det_ReportError(
            MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_DISTRIBUTEPLLCLOCK_SID, MCU_E_UNINIT);
    }
    else if (CoreId != MCAL_MASTER_CORE)
    {
        /* Report to DET */
        (void)Det_ReportError(
            MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_DISTRIBUTEPLLCLOCK_SID, MCU_E_CORE_MISMATCH);
    }
    else
#endif /* (MCU_DEV_ERROR_DETECT  \== STD_ON) */
    {
        Mcu_DistributePllClockInternal(&RegCheck, &ReturnValue);
    }

    if (FALSE == RegCheck)
    {            
        ReturnValue = E_NOT_OK;
#if (MCU_SAFETY_ENABLE == STD_ON)
        (void)Det_ReportRuntimeError(
            MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_DISTRIBUTEPLLCLOCK_SID, MCU_E_REG_CHECK_FAIL);
#endif /* (MCU_SAFETY_ENABLE \== STD_ON)*/
    }

    return ReturnValue;
}
#endif /* (MCU_NO_PLL  \== STD_OFF) */

/****************************************************************************************************
 *   Function Name           : Mcu_GetPllStatus
 *
 *   Service ID              : 0x04
 *
 *   Description             : This service provides the lock status of the PLL.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : MCU_PLL_LOCKED: The lock status of the PLL is MCU_PLL_LOCKED.
 *                             MCU_PLL_UNLOCKED: The lock status of the PLL is MCU_PLL_UNLOCKED.
 *                             MCU_PLL_STATUS_UNDEFINED: The lock status of the PLL is UNDEFINED.
 *
 *   Preconditions           : MCU Driver component must be initialized.
 *
 *   AUTOSAR_Requirement     : SWS_Mcu_00157.
 ****************************************************************************************************/
/* #Violation: Mcu_c_REF_17*/
FUNC(Mcu_PllStatusType, MCU_CODE) Mcu_GetPllStatus
(
    void
)
{
    /* \[SWS_Mcu_00008] The function Mcu_GetPllStatus shall return the lock status of the PLL */
    Mcu_PllStatusType PllLockStatus;
    /* \[SWS_Mcu_00132] The function Mcu_GetPllStatus shall return MCU_PLL_STATUS_UNDEFINED if this
     * function is called prior to calling of the function Mcu_Init*/
    /* Set PLL status to undefined */
    PllLockStatus = MCU_PLL_STATUS_UNDEFINED;
#if (MCU_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET, if module is not initialized */
    if (MCU_UNINITIALIZED == Mcu_InitialStatus)
    {
        /* Report to DET */
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_GETPLLSTATUS_SID, MCU_E_UNINIT);
    }
    else
#endif /* (MCU_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* \[SWS_Mcu_00008] return the lock status of the PLL*/
        /* \[SWS_Mcu_00206] Mcu_GetPllStatus shall also return MCU_PLL_STATUS_UNDEFINED if the
         * pre-compile parameter McuNoPll is set to TRUE*/
#if (MCU_NO_PLL == STD_OFF)
        PllLockStatus = Mcu_PllStatus();
#endif /* (MCU_NO_PLL  \== STD_OFF) */
    }

    return PllLockStatus;
}

/****************************************************************************************************
 *   Function Name           : Mcu_GetResetReason
 *
 *   Service ID              : 0x05
 *
 *   Description             : The service reads the reset type from the hardware, if supported.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : Mcu_ResetType The reset reason .
 *
 *   Preconditions           : .
 *
 *   AUTOSAR_Requirement     : SWS_Mcu_00158.
 ****************************************************************************************************/
/* #Violation: Mcu_c_REF_17*/
FUNC(Mcu_ResetType, MCU_CODE) Mcu_GetResetReason
(
    void
)
{
    /* \[SWS_Mcu_00052]
     * provide services to get the reset reason of the last reset*/
/* #Violation: Mcu_c_REF_16*/
    Mcu_ResetType ResetSource;
    /* \[SWS_Mcu_00133]  Mcu_GetResetReason shall return MCU_RESET_UNDEFINED if this function is
     * called prior to calling of the function Mcu_Init*/
    ResetSource = MCU_RESET_UNDEFINED;

    /* Report to DET, if module is not initialized */
    if (NULL_PTR == Mcu_ConfigPtr)
    {
#if (MCU_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_GETRESETREASON_SID, MCU_E_UNINIT);
#endif /* (MCU_DEV_ERROR_DETECT  \== STD_ON) */
    }
    else
    {
        ResetSource = Mcu_ResetStatus;
    }
    /* \[SWS_Mcu_00005] (Not applicable)The function Mcu_GetResetReason shall read the reset reason
     * from the hardware and return this reason if supported by the hardware. If the hardware does not
     * support the hardware detection of the reset reason, the return value from the function
     * Mcu_GetResetReason shall always be MCU_POWER_ON_RESET */
    return ResetSource;
}

/****************************************************************************************************
 *   Function Name           : Mcu_GetResetRawValue
 *
 *   Service ID              : 0x06
 *
 *   Description             : The service return reset type value from the hardware
 *                             register.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : reset type value from the hardware register.
 *
 *   Preconditions           : MCU Driver component must be initialized.
 *
 *   AUTOSAR_Requirement     : SWS_Mcu_00159.[SWS_Mcu_00006]
 ****************************************************************************************************/
/* #Violation: Mcu_c_REF_17*/
FUNC(Mcu_RawResetType, MCU_CODE) Mcu_GetResetRawValue
(
    void
)
{
    Mcu_RawResetType ResetValue;
    /* \[SWS_Mcu_00135]The function Mcu_GetResetRawValue shall return an implementation
     * specific value which does not correspond to a valid value of the reset status
     * register and is not equal to 0 if this function is called prior to calling of the
     * function Mcu_Init, and if supported by the hardware*/
    ResetValue = MCU_RESET_RAW_UNDEFINED;
    /* \[SWS_Mcu_00125] */
    /* Report to DET, if module is not initialized */
    if (NULL_PTR == Mcu_ConfigPtr)
    {
#if (MCU_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_GETRESETRAWVAULE_SID, MCU_E_UNINIT);
#endif /* (MCU_DEV_ERROR_DETECT  \== STD_ON) */        
    }
    else
    {
        /* \[SWS_Mcu_00135] */
        /* the Init function is already been called */
        /* \[SWS_Mcu_00006]:(Not applicable) The function Mcu_GetResetRawValue shall read the 
        reset raw value from the hardware register if the hardware supports this. If the 
        hardware does not have a reset status register, the return value shall be 0x0 */
        ResetValue = Mcu_ResetRawStatus;
    }
    return ResetValue;
}

/* \[SWS_Mcu_00146] The function Mcu_PerformReset is only available if the pre compile parameter 
McuPerformResetApi is set to TRUE. If set to FALSE, the function Mcu_PerformReset is not applicable.
*/
#if (MCU_PERFORM_RESET_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Mcu_PerformReset
 *
 *   Service ID              : 0x07
 *
 *   Description             : The service performs a microcontroller reset..
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : .
 *
 *   AUTOSAR_Requirement     : SWS_Mcu_00160.
 ****************************************************************************************************/
/* #Violation: Mcu_c_REF_17*/
FUNC(void, MCU_CODE) Mcu_PerformReset
(
    void
)
{
    volatile uint32 DelayCnt;
    /* Report to DET, if module is not initialized */
    if (NULL_PTR == Mcu_ConfigPtr)
    {
#if (MCU_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_PERFORMRESET_SID, MCU_E_UNINIT);
#endif /* (MCU_DEV_ERROR_DETECT  \== STD_ON) */
    }
    else
    {
        /* \[SWS_Mcu_00145] the MCU module's environment shall only call the function Mcu_PerformReset
         *  after the MCU module has been initialized by the function Mcu_Init*/
        /* \[SWS_Mcu_00143] The function Mcu_PerformReset shall perform a
           microcontroller reset by using the hardware feature of the microcontroller
         * [SWS_Mcu_00055]
         *provide a service to provide software triggering of a hardware reset */
        /* \[SWS_Mcu_00144]: The function Mcu_PerformReset shall perform the reset
           type which is configured in the configuration set */
        /*check it without register value check*/
        MCU_ENTER_CRITICAL_SECTION(Mcu_PerformReset);
        (void)Rcc_Hal_ReqSwTrigRst();
        MCU_EXIT_CRITICAL_SECTION(Mcu_PerformReset);

        /* Consider the delayed reset function, with a maximum delay time of 250us.  */
        DelayCnt = MCU_ROUGH_DELAY_500US;
        while (0U != DelayCnt)
        {
            DelayCnt -= 1U;
        }
#if (MCU_DEV_RUNTIME_ERROR_DETECT == STD_ON)
        (void)Det_ReportRuntimeError(
            MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_PERFORMRESET_SID, MCU_E_RESET_FAILED);
#endif /* (MCU_DEV_RUNTIME_ERROR_DETECT  \== STD_ON) */
    }
}
#endif /* (MCU_PERFORM_RESET_API  \== STD_ON) */

/****************************************************************************************************
 *   Function Name           : Mcu_SetMode
 *
 *   Service ID              : 0x08
 *
 *   Description             : This service activates the MCU power modes.
 *
 *   Parameters in           : McuMode - Id for power mode setting.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : MCU Driver component must be initialized.
 *
 *   AUTOSAR_Requirement     : SWS_Mcu_00161.
 *   [SWS_Mcu_00164]:
 *   The MCU module shall provide a service to activate MCU reduced power modes
 *   [SWS_Mcu_00237]:The Mcu_ModeType specifies the identification (ID) for a MCUmode, configured
 *   via configuration structure
 ****************************************************************************************************/
/* #Violation: Mcu_c_REF_6*/
/* #Violation: Mcu_c_REF_17*/
FUNC(void, MCU_CODE) Mcu_SetMode
(
    Mcu_ModeType McuMode
)
{
    boolean RegCheck;
    RegCheck = TRUE;
#if (MCU_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET, if the component is not initialized */
    if (NULL_PTR == Mcu_ConfigPtr)
    {
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SETMODE_SID, MCU_E_UNINIT);
    }
    /* \[SWS_Mcu_00020]: McuMode shall be within the modes defined in the 
       configuration data structure. Related error value: MCU_E_PARAM_MODE*/
    /* Report to DET, if Mode Setting Id is out of range */
    else if (
        (McuMode > MCU_NUM_MODE_CONFIG) ||
        (0U == (((uint32)1U << (uint32)McuMode) & (uint32)Mcu_ConfigPtr->ModeConfigPtr->ValidMode)))
    {
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SETMODE_SID, MCU_E_PARAM_MODE);
    }
    else
#endif /* (MCU_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* \[SWS_Mcu_00148] The MCU module's environment shall only call the function Mcu_SetMode
         *  after the MCU module has been initialized by the function Mcu_Init*/
        /* \[SWS_Mcu_00147] The function Mcu_SetMode shall set the MCU power mode. In case of
         * CPU power down mode, the function Mcu_SetMode returns after it has performed a
         * wake-up*/
        if (MCU_SLEEP_MODE == McuMode)
        {
            MCU_ENTER_CRITICAL_SECTION(Mcu_SetMode);
            /* Set low power mode:sleep */
            RegCheck &= Pwrc_Hal_SetLowpowerMode(PWRC_LOWPOWERMODE_SLEEP);
            MCU_EXIT_CRITICAL_SECTION(Mcu_SetMode);
            /* #Violation: Mcu_c_REF_22*/
            ISB();

            /* Clear Event register if it is set*/
            /* #Violation: Mcu_c_REF_4*/
            /* #Violation: Mcu_c_REF_21*/
            /* #Violation: Mcu_c_REF_22*/
            ASM_VOLATILE("WFE");
            /* set to sleep*/
            /* #Violation: Mcu_c_REF_4*/
            /* #Violation: Mcu_c_REF_21*/
            /* #Violation: Mcu_c_REF_22*/
            ASM_VOLATILE("WFE");
        }
        /* MCU STANDBY MODE */
        else
        {

            MCU_ENTER_CRITICAL_SECTION(Mcu_SetMode);
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
            RegCheck &= Pwrc_Hal_SetStbEvrcSpreadSpectrum(7U, PWRC_FUNCTION_DISABLE);
#endif
            RegCheck &= Pwrc_Hal_ClearStbWakeupSource(0x2EFU); /* Clear standby wakeup source  */
            RegCheck &=
                Pwrc_Hal_SetLowpowerMode(PWRC_LOWPOWERMODE_STANDBY); /* Set low power mode:standby */
            /* SET wakeup source. ModeConfigPtr is not NULLPTR is guaranteed by EB */
            RegCheck &= Pwrc_Hal_InitStandbyMode(
                Mcu_ConfigPtr->ModeConfigPtr->StdbyCfgPtr,
                Mcu_ConfigPtr->ModeConfigPtr->NumOfStandbySource,
                0xF0U);
            MCU_EXIT_CRITICAL_SECTION(Mcu_SetMode);
            /* #Violation: Mcu_c_REF_22*/
            ISB();

            /* set to standby */
            /* #Violation: Mcu_c_REF_4*/
            /* #Violation: Mcu_c_REF_21*/
            /* #Violation: Mcu_c_REF_22*/
            ASM_VOLATILE("WFI");
        }
    }
    if (FALSE == RegCheck)
    {
#if (MCU_SAFETY_ENABLE == STD_ON)
        (void)Det_ReportRuntimeError(
            MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SETMODE_SID, MCU_E_REG_CHECK_FAIL);
#endif /* (MCU_SAFETY_ENABLE \== STD_ON)*/
        (void)RegCheck ;
    }

    return;
}
/* \[SWS_Mcu_00209]: The function Mcu_GetRamState shall be available to the 
user if the pre-compile parameter McuGetRamStateApi is set to TRUE. Instead, if 
the former parameter is set to FALSE, this function shall be disabled
(e.g. the hardware does not support this functionality). */
#if (MCU_GET_RAM_STATE_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Mcu_GetRamState
 *
 *   Service ID              : 0x0A
 *
 *   Description             : This service provides the actual status of the
 *                             microcontroller RAM area.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : Mcu_RamStateType: The actual status of the
 *                             microcontroller RAM area.
 *
 *   Preconditions           : MCU Driver component must be initialized.
 *
 *   AUTOSAR_Requirement     : SWS_Mcu_00207.
 ****************************************************************************************************/
FUNC(Mcu_RamStateType, MCU_PUBLIC_CODE) Mcu_GetRamState
(
    void
)
{
    Mcu_RamStateType RamStatus;
    uint32           States;
    States = 0U;
    RamStatus = MCU_RAMSTATE_INVALID;

#if (MCU_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET, if the component is not initialized
    [SWS_Mcu_00208]: The MCU module environment shall call this function only if
    the MCU module has been already initialized using the function MCU_Init. */
    if (MCU_UNINITIALIZED == Mcu_InitialStatus)
    {
            /* Report to DET */
            (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_GETRAMSTATE_SID, MCU_E_UNINIT);
    }
    /* if no development error occurred */
    else
#endif /* (MCU_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* read memery states registers of GMU and LMU */
#if defined(THA6_THA6104)

            States |= *(volatile uint32 *)(GMU0_BASE_ADDR + GMU_MEMSTS_OFFSET_ADDR);
            States |= *(volatile uint32 *)(LMU2_BASE_ADDR + LMU_MEMSTS_OFFSET_ADDR);
#endif /* defined(THA6_THA6104) */

/* THA6206 */
#if defined(THA6_THA6206) || defined(THA6_THA6206D)
            States |= *(volatile uint32 *)(GMU0_BASE_ADDR + GMU_MEMSTS_OFFSET_ADDR);
            States |= *(volatile uint32 *)(LMU3_BASE_ADDR + LMU_MEMSTS_OFFSET_ADDR);
            States |= *(volatile uint32 *)(LMU1_BASE_ADDR + LMU_MEMSTS_OFFSET_ADDR);
            States |= *(volatile uint32 *)(LMU2_BASE_ADDR + LMU_MEMSTS_OFFSET_ADDR);

#endif /* defined(THA6_THA6206) */

            /* THA6412 */
#if defined(THA6_THA6412)
            States |= *(volatile uint32 *)(GMU0_BASE_ADDR + GMU_MEMSTS_OFFSET_ADDR);
            States |= *(volatile uint32 *)(GMU1_BASE_ADDR + GMU_MEMSTS_OFFSET_ADDR);
            States |= *(volatile uint32 *)(LMU3_BASE_ADDR + LMU_MEMSTS_OFFSET_ADDR);
            States |= *(volatile uint32 *)(LMU1_BASE_ADDR + LMU_MEMSTS_OFFSET_ADDR);
            States |= *(volatile uint32 *)(LMU2_BASE_ADDR + LMU_MEMSTS_OFFSET_ADDR);

#endif /* defined(THA6_THA6412) */

            if (States == E_OK)
            {
                RamStatus = MCU_RAMSTATE_VALID;
            }
    }

    /* Return the value of RAM status result */
    return RamStatus;
}
#endif /* (MCU_GET_RAM_STATE_API  \== STD_ON) */




#if (MCU_CLR_COLD_RESET_STAT_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Mcu_ClearColdResetStatus
 *
 *   Service ID              : 0X20
 *
 *   Description             : This service clear reset reason.
 *                             module.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : none.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : void.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : .
 ****************************************************************************************************/
/* #Violation: Mcu_c_REF_17*/
FUNC(void, MCU_CODE) Mcu_ClearColdResetStatus
(
    void
)
{
    boolean RegCheck;
    RegCheck = TRUE;
#if (MCU_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET, if the component is not initialized*/
    if (MCU_UNINITIALIZED == Mcu_InitialStatus)
    {
        /* Report to DET */
        (void)Det_ReportError(
            MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_CLEARCOLDRESETSTATUS_SID, MCU_E_UNINIT);
    }
    /* if no development error occurred */
    else
#endif /* (MCU_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /*this api is avalible in initialization phase.*/
        MCU_ENTER_CRITICAL_SECTION(Mcu_ClearColdResetStatus);
        /* #Violation: Mcu_c_REF_9*/
        RegCheck &= Rcc_Hal_ClearRstStatus((Rcc_RstReason)Mcu_ResetStatus);
        MCU_EXIT_CRITICAL_SECTION(Mcu_ClearColdResetStatus);
        if (FALSE == RegCheck)
        {
#if (MCU_SAFETY_ENABLE == STD_ON)
            (void)Det_ReportRuntimeError(
                MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_CLEARCOLDRESETSTATUS_SID, MCU_E_REG_CHECK_FAIL);
#endif /* (MCU_SAFETY_ENABLE  \== STD_ON) */
        }
    }
}
#endif /* (MCU_CLR_COLD_RESET_STAT_API  \== STD_ON) */

#if (MCU_VERSION_INFO_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Mcu_GetVersionInfo
 *
 *   Service ID              : 0x09
 *
 *   Description             : This service returns the version information of this
 *                             module.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : VersionInfoPtr: Pointer to where to store the version information 
 *                                             of this module.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : void.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Mcu_00162.
 ****************************************************************************************************/
/* #Violation: Mcu_c_REF_17*/
FUNC(void, MCU_CODE) Mcu_GetVersionInfo
(
/* #Violation: Mcu_c_REF_10*/
/* #Violation: Mcu_c_REF_15*/
    P2VAR(Std_VersionInfoType, AUTOMATIC, MCU_APPL_DATA) VersionInfoPtr
)
{
#if (MCU_DEV_ERROR_DETECT == STD_ON)
    /* Check if parameter passed is equal to Null pointer */
    if (NULL_PTR == VersionInfoPtr)
    {
        (void)Det_ReportError(
            MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_GETVERSIONINFO_SID, MCU_E_PARAM_POINTER);
    }
    else
#endif /* (MCU_DEV_ERROR_DETECT  \== STD_ON) */
    {
        VersionInfoPtr->vendorID = (uint16)MCU_VENDOR_ID;
        VersionInfoPtr->moduleID = (uint16)MCU_MODULE_ID;
        VersionInfoPtr->sw_major_version = (uint8)MCU_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = (uint8)MCU_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = (uint8)MCU_SW_PATCH_VERSION;
    }
}
#endif /* (MCU_VERSION_INFO_API  \== STD_ON) */

/****************************************************************************************************
 *   Function Name           : Mcu_GtmWrapperInit
 *
 *   Service ID              : 0xF2
 *
 *   Description             : This service Init the GTM wrapper.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : boolean
 *
 *   Preconditions           :
 *
 *   AUTOSAR_Requirement
 ****************************************************************************************************/
/* #Violation: Mcu_c_REF_23*/
FUNC(boolean, MCU_CODE) Mcu_GtmWrapperInit
(
    /* #Violation: Mcu_c_REF_15*/
    const Mcu_GtmWrapperConfigType *GTMWrapperConfigPtr
)
{
    /* #Violation: Mcu_c_REF_16*/
    boolean RegCheck;
    RegCheck = TRUE;
    /* Warpper init */
    if (NULL_PTR != GTMWrapperConfigPtr)
    {
        /* init GTM to Port */
        RegCheck = Mcu_InitGtmTriggers(GTMWrapperConfigPtr);
    }

    return RegCheck;
}

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
/* #Violation: Mcu_c_REF_19*/
#define MCU_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Mcu_c_REF_1*/
#include "Mcu_MemMap.h"
