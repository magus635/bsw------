/****************************************************************************************************
 *
 ****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Mcu_GeneralTypes.h
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : RCC,PWRC
 *
 *   brief                 : This file contains all type definitions of Mcu Driver
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
*#Mcu_GeneralTypes_h_REF_1:MISRAC2012-Rule-2.3; 
* Justification: Reserved types are defined in AUTOSAR specifications.
*
*#Mcu_GeneralTypes_h_REF_2:MISRAC2012-Dir-4.8; 
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the 
* code complexity.
*
*/
#ifndef MCU_GENERALTYPES_H_
#define MCU_GENERALTYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
/* \[SWS_Mcu_00152]
 * Included for Type definitions */
#include "Std_Types.h"
/* Included for pre-compile options */
#include "Mcu_Cfg.h"
#include "gtm_timebase_hal.h"
#include "gtm_trig_hal.h"
#include "pwrc_hal.h"
#include "rcc_hal.h"
#include "dflash_hal.h"
#include "pflash_hal.h"
#include "port_hal_esr.h"

/* Macro for GTM TOM/TOM setting */
#include "gtm.h"
#include "gtm_pwm_hal.h"

/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
typedef Gtm_Dsadc_In        Mcu_DsadcConfigType;
typedef Gtm_Dsadc_Out       Mcu_GtmToDsadcConfigType;
typedef Gtm_MscTrigL1Config Mcu_MscConfigType;
typedef Gtm_MscTrigL2Config Mcu_MscSetL2ConfigType;
#else /*donot suport in THA6104*/
typedef uint8 Mcu_DsadcConfigType;
typedef uint8 Mcu_GtmToDsadcConfigType;
typedef uint8 Mcu_MscConfigType;
typedef uint8 Mcu_MscSetL2ConfigType;
#endif
typedef Gtm_FreeTimerConfig      Mcu_TBUConfigType;
typedef Rcc_ModuleClockSource    Mcu_PerClockSrcType;
typedef Gtm_Tim_In               Mcu_TimConfigType;

typedef Gtm_Tout_Out             Mcu_ToutConfigType;

typedef Gtm_AdcTrigConfig        Mcu_AdcConfigType;
typedef Gtm_DmaTrigL1Config      Mcu_DmaConfigType;
typedef Gtm_DmaTrigL2Config      Mcu_DmaL2ConfigType;

typedef Rcc_CpuClockSource       Mcu_SYSClockSrcType;

typedef Rcc_PllConfig            Mcu_PllCfgType;

/* \[SWS_Mcu_00251] [SWS_Mcu_00233]:
 * The type shall be uint8, uint16 or uint32, depending on uC platform*/
/* Type definition for Mcu_ClockType used by the API Mcu_InitClock */
typedef uint32                   Mcu_ClockType;
/* \[SWS_Mcu_00253]*/
/* Type definition for Mcu_RawResetType used by the API Mcu_GetResetRawValue
[SWS_Mcu_00235]:  The type Mcu_RawResetType specifies the reset reason in raw register format, read
from a reset status register. ()*/
typedef uint32                   Mcu_RawResetType;
/* \[SWS_Mcu_00254] [SWS_Mcu_00238]*/
/* Type definition for Mcu_ModeType used by the API Mcu_SetMode */
typedef uint32                   Mcu_ModeType;
/* \[SWS_Mcu_00255] [SWS_Mcu_00240]*/
/* Type definition for Mcu_RamSectionType used by the API Mcu_InitRamSection */
typedef uint32                   Mcu_RamSectionType;

/****************************************************************************************************
**                          Global Enumration Definitions                                          **
****************************************************************************************************/
/* \[SWS_Mcu_00250] [SWS_Mcu_00231]*/
/* Status value returned by the API Mcu_GetPllStatus */
typedef enum
{
    MCU_PLL_LOCKED = 0U,
    MCU_PLL_UNLOCKED,
    MCU_PLL_STATUS_UNDEFINED
} Mcu_PllStatusType;

typedef enum
{
    MCU_UNINITIALIZED = 0U,
    MCU_INITIALIZED
} Mcu_InitStatusType;

/* SWS_Mcu_00256 */
typedef enum
{
    MCU_RAMSTATE_INVALID = 0U,
    MCU_RAMSTATE_VALID
/* #Violation: Mcu_GeneralTypes_h_REF_1*/
} Mcu_RamStateType;

/* \[SWS_Mcu_00252] [SWS_Mcu_00234][SWS_Mcu_00134] */
/* Type of reset supported by the hardware */
/* The enumeration of reset reason definition. */
typedef enum
{
    MCU_RSTREASON_ESR0 = 0U,        /* The last reset was triggered by ESR0 */
    MCU_RSTREASON_ESR1 = 1U,        /* The last reset was triggered by ESR1 */
    MCU_RSTREASON_SAC = 2U,         /* The last reset was triggered by SAC */
    MCU_SW_RESET = 3U,              /* The last reset was triggered by SW */
    MCU_WATCHDOG_RESET = 4U,        /* The last reset was triggered by IWDG */
    MCU_RSTREASON_CPU0WARMRST = 7U, /* The last reset was triggered by CPU0 warm reset */
    MCU_RSTREASON_CPU1WARMRST = 8U, /* The last reset was triggered by CPU1 warm reset */
    MCU_RSTREASON_PORSTPIN = 16U,   /* The last reset was triggered by PORSTPIN */
    MCU_RSTREASON_IST = 17U,        /* The last reset was triggered by IST */
    MCU_RSTREASON_HSMAPP = 18U, /* The last reset was triggered by HSM application reset request */
    MCU_RSTREASON_HSMSYS = 19U, /* The last reset was triggered by HSM system reset request */
    MCU_POWER_ON_RESET = 23U,   /* The last reset was triggered by power-on */
    MCU_RSTREASON_MUTITYPE,     /* The last reset was triggered by multi-reason */
    MCU_RESET_UNDEFINED         /* No reset action happened */
} Mcu_ResetType;

/****************************************************************************************************
**                          Global Union Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/
/* #Violation: Mcu_GeneralTypes_h_REF_2*/
typedef struct
{
    Mcu_SYSClockSrcType ClkSrc; /* source clock for cpu_clk  */
    uint8               CpuDiv; /* div for cpu_clk */
    uint8               SysDiv; /* div for sys_clk */
    uint8               AxiDiv; /* div for axi_clk */
    uint8               ApbDiv; /* div for apb_clk / ahb_clk */
} Mcu_SysClkType;
/*EB config for Peripheral Clock*/
/* #Violation: Mcu_GeneralTypes_h_REF_2*/
typedef struct
{
    Mcu_PerClockSrcType ClkSrc;
    uint32              Div;
} Mcu_PerClkType;
/*EB config for BaseTimer Clock*/
/* #Violation: Mcu_GeneralTypes_h_REF_2*/
typedef struct
{
    Mcu_PerClkType BaseTimer[MCU_NUM_BASETIMER];/*6 basetimer */
} Mcu_BaseTimerClkType;
/*EB config for DMA Clock*/
/* #Violation: Mcu_GeneralTypes_h_REF_2*/
typedef struct
{
    boolean DMA0CkEn; /* (Range : true or false) */
    boolean DMA1CkEn; /* (Range : true or false) */
    boolean DMA2CkEn; /* (Range : true or false) */
    boolean DMA3CkEn; /* (Range : true or false) */

} Mcu_DMAClkType;


/* #Violation: Mcu_GeneralTypes_h_REF_2*/
typedef struct
{
    Rcc_ClockMonConfig ClockMonSysPllCfg; /*syspll clock monitor*/
    Rcc_ClockMonConfig ClockMonPerPllCfg; /*perpll clock monitor*/
    Rcc_ClockMonConfig ClockMonCpuPllCfg; /*cuppll clock monitor*/
 } Mcu_MonitorClkType;

/* #Violation: Mcu_GeneralTypes_h_REF_2*/
typedef struct
{
    const Mcu_PllCfgType       *SysPllCfgPtr; /* sys pll */
    const Mcu_PllCfgType       *PerPllCfgPtr; /* Peripheral pll*/
    const Mcu_SysClkType       *SysClkCfgPtr; /*bus clock */
    const Mcu_PerClkType       *GtmClkCfgPtr;
    const Mcu_PerClkType       *MscClkCfgPtr;
    const Mcu_PerClkType       *EspiClkCfgPtr;
    const Mcu_PerClkType       *QspiClkCfgPtr;
    const Mcu_PerClkType       *WdtClkCfgPtr;
    const Mcu_PerClkType       *CanClkCfgPtr;
    const Mcu_PerClkType       *SarAdcClkCfgPtr;
    const Mcu_PerClkType       *DsadcRdcClkCfgPtr;
    const Mcu_DMAClkType       *DmaClkCfgPtr;
    const Mcu_BaseTimerClkType *BaseTimerClkCfgPtr;
    uint32                      SysClkFrequency;
    const Mcu_MonitorClkType   *MonitorClkPtr;
} Mcu_ClockConfigType;

/* \[SWS_Mcu_00249]*/
/* #Violation: Mcu_GeneralTypes_h_REF_2*/
typedef struct
{
    /* Value of RAM Starting Address */
    uint32 *RamSectionBaseAddrPtr;
    /* Size of RAM Section  */
    uint32  RamSectionSize;
    /* RAM Initial Value */
    uint8   RamDefaultValue;
    /* the size in bytes of data which can be written into RAM at once */
    uint8   RamWriteSize;

} Mcu_RamSettingType;

/* #Violation: Mcu_GeneralTypes_h_REF_2*/
typedef struct
{
    /* SW, ESR0... */
    Rcc_RstSrc  SrcType;
    /* App,system ..Reset  */
    Rcc_RstType ResetType;
} Mcu_ResetConfigType;

/* Type definition for GTM configuration parameters */
/* #Violation: Mcu_GeneralTypes_h_REF_2*/
typedef struct
{
    /* Gtm TOM/ATOM Channel Index */
    Gtm_Output_Driver GtmChannelIndex;
    /* Gtm TOM/ATOM Channel Configuration Information */
    Gtm_Pwm_Config    GtmChannelConfig;
} Mcu_GtmTriggerConfigType;

/* #Violation: Mcu_GeneralTypes_h_REF_2*/
typedef struct
{
    const Mcu_TimConfigType        *TimConfigPtr; /* Pointer to Timer configuration */
    const Mcu_DsadcConfigType      *DsadcConfigPtr;/* Pointer to DSADC configuration */
    const Mcu_ToutConfigType       *ToutConfigPtr;/* Pointer to TOUT configuration */
    const Mcu_AdcConfigType        *AdcConfigPtr;/* Pointer to ADC configuration */
    const Mcu_GtmToDsadcConfigType *GtmToDsadcConfigPtr;/* Pointer to GTM to DSADC configuration */
    const Mcu_MscConfigType        *MscConfigPtr;/* Pointer to MSC configuration */
    const Mcu_MscSetL2ConfigType   *Gtm_MscSetL2ConfigPtr;/* Pointer to GTM MSC L2 configuration */
    const Mcu_DmaConfigType        *DmaConfigPtr;/* Pointer to DMA L1 configuration */
    const Mcu_DmaL2ConfigType      *DmaL2ConfigPtr;/* Pointer to DMA L2 configuration */
    uint8 NumofTimCfg;/* Num of Tim cfg*/
    uint8 NumofDsadcCfg;/* Num of Dsadc CFG*/
    uint8 NumofToutCfg;/* Num of TOUT cfg*/
    uint8 NumofTAdcCfg;/* Num of Adc Cfg*/
    uint8 NumofToDsadcCfg;/* Num of Gtm to Dsadc Cfg */
    uint8 NumofMscCfg;/* Num of Msc Cfg */
    uint8 NumofMscL2Cfg;/* Num of Msc L2 cfg*/
    uint8 NumofDmaCfg;/* Num of Dma L1 Cfg */
    uint8 NumofDmaL2Cfg; /* Num of Dma L2 Cfg */
} Mcu_GtmWrapperConfigType;

/* #Violation: Mcu_GeneralTypes_h_REF_2*/
typedef struct
{
    const uint32 ValidMode;/*Indicate which modes are configed*/
    const Pwrc_StandbySourceConfig *StdbyCfgPtr;/*Parameters for standby mode.*/
    const uint8 NumOfStandbySource;/*Number of Wakeup sources for standby mode.*/
} Mcu_ModeConfigType;
/* \[SWS_Mcu_00054]:  The structure Mcu_ConfigType shall provide a configurable 
(enable/disable) clock failure notification if the MCU provides an interrupt for such 
detection. 
no such interrupt.
*/

/* \[SWS_Mcu_00249]*/
/* \[SWS_Mcu_00131]: The structure Mcu_ConfigType is an external data structure (i.e.
 * implementation specific) and shall contain the initialization data for the MCU module.It shall
 * contain:  MCU dependent properties  Reset Configuration  Definition of MCU modes Definition of
 * Clock settings  Definition of RAM sections */
/* Structure for MCU Init Configuration */
typedef struct
{
    /* Pointer to MCU Clock Setting configuration
    [SWS_Mcu_00031]:   The definitions for each Clock setting within the structure  Mcu_ConfigType
    shall contain:  MCU specific properties as, e.g., clock safety features and special clock
    distribution settings  PLL settings /start lock options  Internal oscillator setting ()*/
    const Mcu_ClockConfigType      *ClockSettingPtr;
    /* Pointer to MCU RAM Setting configuration
    [SWS_Mcu_00030]:   The definitions for each RAM section within the structure  Mcu_ConfigType shall
    contain:  RAM section base address  Section size  Data pre-setting to be initialized  RAM write
    size ()*/
    const uint32                    NoOfRamConfigs;
    const Mcu_RamSettingType       *RamSettingPtr;
    /* Pointer to GTM wrapper configuration */
    const Mcu_GtmWrapperConfigType *GTMWrapperConfigPtr;
    /* Pointer to GTM CMU configuration */
    const Gtm_ClockConfig          *Gtm_ClockConfigPtr;
    /* Pointer to the address of TBU configuration */
    const Mcu_TBUConfigType        *TBUConfigPtr;
    /* Pointer to the address of Gtm Trigger Source configuration */
    const Mcu_GtmTriggerConfigType *GtmTriggerCfgPtr;
    /* Pointer to the address of Reset configuration */
    const Mcu_ResetConfigType      *ResetConfigPtr;
    /* Pointer to the address of Mcu Mode configuration
    [SWS_Mcu_00035]: The definitions for each MCU mode within the structure Mcu_ConfigType shall
    contain: (depending on MCU) MCU specific properties Change of CPU clock Change of Peripheral clock
    Change of PLL settings Change of MCU power supply */
    const Mcu_ModeConfigType       *ModeConfigPtr;
    uint8 NumofTrigCfg; /* Num of Pwm trigger Cfg */
} Mcu_ConfigType;

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
#endif /* MCU_GENERALTYPES_H_ */
