/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Mcu_PBCfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : RCC PWRC
*
*   brief                 : This file contains all configurations of Mcu Driver
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
*#Mcu_PBcfg_c_REF_1:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Mcu_PBcfg_c_REF_2:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers
*
*#Mcu_PBcfg_c_REF_4:MISRAC2012-Rule-11.4; 
* Justification:Converting integers to object pointers to reduce register access complexity.
*
*#Mcu_PBcfg_c_REF_5:MISRAC2012-Rule-10.5; 
* Justification: Necessary type casting to reduce code complexity; Code review ensure the safety of the casting.
*
*#Mcu_PBcfg_c_REF_6:CWE-547; 
* Justification: The Tresos-generated code does not use symbolic constants for buffer size 
* substitution.
*
*
*/


/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Mcu_Cfg.h"
#include "Mcu.h"

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
[!NOCODE!][!//
[!INCLUDE "Mcu.m"!][!//
[!CALL "GTM_TOUT_REPEAT_ERROR_CHECK"!][!//
[!CALL "GTM_TIM_REPEAT_ERROR_CHECK"!][!//
[!CALL "GTM_GET_SARADC_TRIGGER"!][!//
[!CALL "GTM_GET_TRIGGER_NUM"!][!//
[!ENDNOCODE!][!//
[!IF "$McuGtmSourceNum != 0"!][!//
#include "gtm.h"
#include "gtm_pwm_hal.h"
[!ENDIF!][!//
/* #Violation: Mcu_PBcfg_c_REF_2 */
#define MCU_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Mcu_PBcfg_c_REF_1*/
#include "Mcu_MemMap.h"
[!NOCODE!][!//
[!VAR "GTM_TBU_EN" = "num:i(0)"!][!//
[!VAR "IsTha6104" = "num:i(0)"!][!//

[!IF "node:containsValue(as:modconf('Resource')/ResourceGeneral/ResourceSubderivative, 'THA610X_LFBGA180')"!][!//
[!VAR "IsTha6104" = "num:i(1)"!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
[!AUTOSPACING!][!//
[!INDENT "0"!][!//
[!IF "num:i(count(McuModuleConfiguration/McuRamSectorSettingConf/*)) > 0"!][!//
/***************************************************************************************************
*                        Mcu_RamConfiguration Structure Description
****************************************************************************************************/
/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_RamSettingType Mcu_RamConfiguration[[!"num:i(count(McuModuleConfiguration/McuRamSectorSettingConf/*))"!]U] = 
{
    [!INDENT "4"!][!//
    [!LOOP "McuModuleConfiguration/McuRamSectorSettingConf/*"!][!//
    {
        [!NOCODE!][!//
        [!VAR "BaseAdr" = "./McuRamSectionBaseAddress"!][!//
        [!VAR "Size" = "./McuRamSectionSize"!][!//
        [!IF "not((($BaseAdr >= ecu:get('Mcu.GMU_CACHED_Start')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.GMU_CACHED_End'))) or
                (($BaseAdr >= ecu:get('Mcu.ATCM_AXIM_Start')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.ATCM_AXIM_End'))) or
                (($BaseAdr >= ecu:get('Mcu.BTCM_AXIM_Start')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.BTCM_AXIM_End'))) or
                (($BaseAdr >= ecu:get('Mcu.CTCM_AXIM_Start')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.CTCM_AXIM_End'))) or
                (($BaseAdr >= ecu:get('Mcu.ATCMStart')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.ATCMEnd'))) or
                (($BaseAdr >= ecu:get('Mcu.CTCMStart')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.CTCMEnd'))) or

                (($BaseAdr >= ecu:get('Mcu.LMU_CACHED_Start')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.LMU_CACHED_End'))) or
                (($BaseAdr >= ecu:get('Mcu.LMU1_NON_CACHED_Start')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.LMU1_NON_CACHED_End'))) or
                (($BaseAdr >= ecu:get('Mcu.LMU2_NON_CACHED_Start')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.LMU2_NON_CACHED_End'))) or
                (($BaseAdr >= ecu:get('Mcu.LMU3_NON_CACHED_Start')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.LMU3_NON_CACHED_End'))) or



                (($BaseAdr >= ecu:get('Mcu.GMU_NON_CACHED_Start')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.GMU_NON_CACHED_End'))))"!][!//
        [!ERROR!][!//
          [101-00-00-ERROR]: Ram Base address or size is out of possible ram ranges.
        [!ENDERROR!][!//
        [!ENDIF!][!//

        [!ENDNOCODE!][!//
        [!INDENT "8"!][!//
        /* pRamSectionBaseAddress*/
        /* #Violation: Mcu_PBcfg_c_REF_4*/
        (uint32*)[!"num:inttohex(McuRamSectionBaseAddress)"!]U, 
        /* ulRamSectionSize*/
        (uint32)[!"num:inttohex(McuRamSectionSize)"!]U,  
        /* ucRamDefaultValue*/
        (uint8)[!"num:inttohex(McuRamDefaultValue)"!]U,
        /* RamWriteSize*/
        (uint8)[!"num:inttohex(McuRamSectionWriteSize)"!]U
        [!ENDINDENT!][!//
    },
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};
[!ENDIF!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
/***************************************************************************************************
*                        Mcu_PBClockSysPllConfigData Structure Description
****************************************************************************************************/
/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_PllCfgType Mcu_PBClockSysPllConfigData[[!"num:i(count(McuModuleConfiguration/McuClockSettingConfig/*))"!]U] =
{
    [!INDENT "4"!][!//
    [!LOOP "node:order(McuModuleConfiguration/McuClockSettingConfig/*,'node:value(McuClockSettingId)')"!][!//
    {
        [!NOCODE!][!//
        [!VAR "foutvco" = "0"!][!//
        [!VAR "source" = "node:value(McuSysPllClk_Configuration/McuSysPllSource)"!][!//
        [!VAR "mode" = "node:value(McuSysPllClk_Configuration/McuSysPllMode)"!][!//
        [!VAR "Hse" = "num:i(McuSysPllClk_Configuration/McuHSEClkFrequency)"!][!//
        [!VAR "Hsi" = "num:i(McuSysPllClk_Configuration/McuHSIClkFrequency)"!][!//
        [!VAR "FBDiv" = "num:i(McuSysPllClk_Configuration/McuSysPllFBDiv)"!][!//
        [!VAR "RefDiv" = "num:i(McuSysPllClk_Configuration/McuSysPllRefDiv)"!][!//
        [!VAR "frac" = "num:i(McuSysPllClk_Configuration/McuSysPllFRAC)"!][!//
        [!IF "$mode = 'RCC_PLLMODE_INTEGER'"!][!//
            [!IF "$source = 'RCC_PLLCLOCKSOURCE_HSE'"!][!//
                [!VAR "foutvco" = "$Hse * $FBDiv div $RefDiv "!][!//
            [!ELSE!]
                [!VAR "foutvco" = "$Hsi * $FBDiv div $RefDiv "!][!//
            [!ENDIF!][!//
        [!ELSE!]
            [!IF "$source = 'RCC_PLLCLOCKSOURCE_HSE'"!][!//
                [!VAR "foutvco" = "$Hse * ($FBDiv + (frac div num:i(16777216)) ) div $RefDiv "!][!//
            [!ELSE!]
                [!VAR "foutvco" = "$Hsi * ($FBDiv + (frac div num:i(16777216)) ) div $RefDiv "!][!//
            [!ENDIF!][!//
        [!ENDIF!][!//
        [!IF "(400000000 < $foutvco) and (1600000000 > $foutvco)"!][!//
        [!ELSE!]
            [!ERROR!][!//
            [101-00-07-ERROR]: Invalid clock set of [!"node:name(.)"!] McuSysPllClk_Configuration,400MHz < FOUTVCO < 1600MHz. FOUTVCO = FREF*FBDIV/REFDIV and FOUTVCO = [!"$foutvco"!].
            [!ENDERROR!][!//
        [!ENDIF!][!//
        [!ENDNOCODE!][!//
        [!INDENT "8"!][!//
        /*Rcc_PllClockSource*/
        [!"node:value(McuSysPllClk_Configuration/McuSysPllSource)"!],
        /*Rcc_PllMode*/
        [!"node:value(McuSysPllClk_Configuration/McuSysPllMode)"!],
        /*RefDiv*/
        [!"node:value(McuSysPllClk_Configuration/McuSysPllRefDiv)"!]U,
        /* uint8 PostDiv1 */
        [!"node:value(McuSysPllClk_Configuration/McuSysPllPostDiv1)"!]U,
        /* uint8 PostDiv2 */
        [!"node:value(McuSysPllClk_Configuration/McuSysPllPostDiv2)"!]U, 
        /*postDiv3 reserve for tha6104*/
        0U,     
        /* uint32 FBDiv */
        [!"node:value(McuSysPllClk_Configuration/McuSysPllFBDiv)"!]U,
        /* uint32 FRAC */                 
        [!"node:value(McuSysPllClk_Configuration/McuSysPllFRAC)"!]U           
        [!ENDINDENT!][!//
    },
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};
[!ENDINDENT!][!//

[!INDENT "0"!][!//
/***************************************************************************************************
*                        Mcu_PBClockPerPllConfigData Structure Description
****************************************************************************************************/
/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_PllCfgType Mcu_PBClockPerPllConfigData[[!"num:i(count(McuModuleConfiguration/McuClockSettingConfig/*))"!]U] =
{
    [!INDENT "4"!][!//
    [!LOOP "node:order(McuModuleConfiguration/McuClockSettingConfig/*,'node:value(McuClockSettingId)')"!][!//
    {
        [!NOCODE!][!//
        [!VAR "foutvco" = "0"!][!//
        //fix 80MHZ can clock.
        [!VAR "postdiv3" = "num:i(0)"!][!//
        [!VAR "source" = "node:value(McuPerPllClk_Configuration/McuPerPllSource  )"!][!//
        [!VAR "mode" = "node:value(McuPerPllClk_Configuration/McuPerPllMode  )"!][!//
        [!VAR "Hse" = "num:i(McuSysPllClk_Configuration/McuHSEClkFrequency)"!][!//
        [!VAR "Hsi" = "num:i(McuSysPllClk_Configuration/McuHSIClkFrequency)"!][!//
        [!VAR "FBDiv" = "num:i(McuPerPllClk_Configuration/McuPerPllFBDiv )"!][!//
        [!VAR "RefDiv" = "num:i(McuPerPllClk_Configuration/McuPerPllRefDiv )"!][!//
        [!VAR "frac" = "num:i(McuPerPllClk_Configuration/McuPerPllFRAC )"!][!//
        [!VAR "fout1ph0" = "num:i(McuPerPllClk_Configuration/McuPerPllFrequency)"!][!//
        [!IF "$mode = 'RCC_PLLMODE_INTEGER'"!][!//
            [!IF "$source = 'RCC_PLLCLOCKSOURCE_HSE'"!][!//
                [!VAR "foutvco" = "$Hse * $FBDiv div $RefDiv "!][!//
            [!ELSE!]
                [!VAR "foutvco" = "$Hsi * $FBDiv div $RefDiv "!][!//
            [!ENDIF!][!//
        [!ELSE!]
            [!IF "$source = 'RCC_PLLCLOCKSOURCE_HSE'"!][!//
                [!VAR "foutvco" = "$Hse * ($FBDiv + (frac div num:i(16777216)) ) div $RefDiv "!][!//
            [!ELSE!]
                [!VAR "foutvco" = "$Hsi * ($FBDiv + (frac div num:i(16777216)) ) div $RefDiv "!][!//
            [!ENDIF!][!//
        [!ENDIF!][!//
        [!IF "(400000000 < $foutvco) and (1600000000 > $foutvco)"!][!//
            [!IF "$IsTha6104 = num:i(1)"!][!//
            [!VAR "postdiv3" = "num:i(5)"!][!//
            [!IF "$fout1ph0 = num:i(200000000)"!][!//
            [!ELSE!]
             [!VAR "postdiv3" = "num:i($fout1ph0 *  num:i(2) div  num:i(80000000))"!][!//
                [!IF "num:i(80000000) != $fout1ph0 *  num:i(2) div  num:i($postdiv3)"!][!//
                    [!WARNING!][!//
                    Clock of CAN cannot be divided to 80MHz, please modify the per PLL clock configuration. 
                    [!ENDWARNING!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
            [!ENDIF!][!//

        [!ELSE!]
            [!ERROR!][!//
            [101-00-07-ERROR]: Invalid clock set of [!"node:name(.)"!] McuPerPllClk_Configuration,400MHz < FOUTVCO < 1600MHz. FOUTVCO = FREF*FBDIV/REFDIV and FOUTVCO = [!"$foutvco"!].
            [!ENDERROR!][!//
        [!ENDIF!][!//

        [!ENDNOCODE!][!//
        [!INDENT "8"!][!//
        /*Rcc_PllClockSource*/
        [!"node:value(McuPerPllClk_Configuration/McuPerPllSource)"!],
        /*Rcc_PllMode*/
        [!"node:value(McuPerPllClk_Configuration/McuPerPllMode)"!],
        /*RefDiv*/
        [!"node:value(McuPerPllClk_Configuration/McuPerPllRefDiv)"!]U,
        /* uint8 PostDiv1 */
        [!"node:value(McuPerPllClk_Configuration/McuPerPllPostDiv1)"!]U,
        /* uint8 PostDiv2 */
        [!"node:value(McuPerPllClk_Configuration/McuPerPllPostDiv2)"!]U, 
        /*postDiv3 reserve for tha6104*/
        [!"$postdiv3"!]U, 
        /* uint32 FBDiv */
        [!"node:value(McuPerPllClk_Configuration/McuPerPllFBDiv)"!]U,
        /* uint32 FRAC */                 
        [!"node:value(McuPerPllClk_Configuration/McuPerPllFRAC)"!]U
        [!ENDINDENT!][!//
    },
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};
[!ENDINDENT!][!//

[!INDENT "0"!][!//
/***************************************************************************************************
*                        Mcu_PBClockSysConfigData Structure Description
****************************************************************************************************/
/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_SysClkType Mcu_PBClockSysConfigData[[!"num:i(count(McuModuleConfiguration/McuClockSettingConfig/*))"!]U] =
{
    [!INDENT "4"!][!//
    [!LOOP "node:order(McuModuleConfiguration/McuClockSettingConfig/*,'node:value(McuClockSettingId)')"!][!//
    {
        [!INDENT "8"!][!//
        /* Mcu_SYSClockSrcType */
        [!"node:value(McuSysClkDiv_Configuration/McuSysClockSource)"!],
        /* CpuClkDiv */
        [!"node:value(McuSysClkDiv_Configuration/CpuClkDiv)"!]U,
        /* SysClkDiv */
        [!"node:value(McuSysClkDiv_Configuration/SysClkDiv)"!]U,
        /* AxiDiv */
        [!"node:value(McuSysClkDiv_Configuration/AxiDiv)"!]U,     
        /* AHBDiv */
        [!"node:value(McuSysClkDiv_Configuration/AhbDiv)"!]U,
        [!ENDINDENT!][!//
    },
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};
[!ENDINDENT!][!//

[!INDENT "0"!][!//
/***************************************************************************************************
*                        Mcu_PBClockGtmConfigData Structure Description
****************************************************************************************************/
/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_PerClkType Mcu_PBClockGtmConfigData[[!"num:i(count(McuModuleConfiguration/McuClockSettingConfig/*))"!]U] =
{
    [!INDENT "4"!][!//
    [!LOOP "node:order(McuModuleConfiguration/McuClockSettingConfig/*,'node:value(McuClockSettingId)')"!][!//
    {
        [!INDENT "8"!][!//
        [!"node:value(McuGTMClk_Configuration/GTMClockSource)"!],    /* PLL_Clk_Src ClkSrc */
        [!"node:value(McuGTMClk_Configuration/GTMClockDiv)"!]U       /* ClkDiv */
        [!ENDINDENT!][!//
    },
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};
[!ENDINDENT!][!//

[!INDENT "0"!][!//
/***************************************************************************************************
*                        Mcu_PBClockSarAdcConfigData Structure Description
****************************************************************************************************/
/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_PerClkType Mcu_PBClockSarAdcConfigData[[!"num:i(count(McuModuleConfiguration/McuClockSettingConfig/*))"!]U] =
{
    [!INDENT "4"!][!//
    [!LOOP "node:order(McuModuleConfiguration/McuClockSettingConfig/*,'node:value(McuClockSettingId)')"!][!//
    {
        [!INDENT "8"!][!//
        [!"node:value(McuSarAdcClk_Configuration/SarAdcClockSource)"!],    /* PLL_Clk_Src ClkSrc */
        0U       /* NOT USE */
        [!ENDINDENT!][!//
    },
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!IF "$IsTha6104 = num:i(0)"!][!//
/***************************************************************************************************
*                        Mcu_PBClockDsadcRdcConfigData Structure Description
****************************************************************************************************/
/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_PerClkType Mcu_PBClockDsadcRdcConfigData[[!"num:i(count(McuModuleConfiguration/McuClockSettingConfig/*))"!]U] =
{
    [!INDENT "4"!][!//
    [!LOOP "node:order(McuModuleConfiguration/McuClockSettingConfig/*,'node:value(McuClockSettingId)')"!][!//
    {
        [!INDENT "8"!][!//
        [!"node:value(Mcu_Dsadc_Rdc_Clk_Configuration/ClockSource)"!],    /* PLL_Clk_Src ClkSrc */
        /*Rdcdiv:[!"node:value(Mcu_Dsadc_Rdc_Clk_Configuration/RDCClockDiv)"!]U   , dsadcDiv: [!"node:value(Mcu_Dsadc_Rdc_Clk_Configuration/DSADCClockDiv)"!]U */
        [!"num:i( node:value(Mcu_Dsadc_Rdc_Clk_Configuration/RDCClockDiv)*256 +node:value(Mcu_Dsadc_Rdc_Clk_Configuration/DSADCClockDiv))"!]U       /* rdcDiv<<8 + dsadcDiv */
        [!ENDINDENT!][!//
    },
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};
[!ENDIF!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!IF "$IsTha6104 = num:i(0)"!][!//
/***************************************************************************************************
*                        Mcu_PBClockMscConfigData Structure Description
****************************************************************************************************/
/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_PerClkType Mcu_PBClockMscConfigData[[!"num:i(count(McuModuleConfiguration/McuClockSettingConfig/*))"!]U] =
{
    [!INDENT "4"!][!//
    [!LOOP "node:order(McuModuleConfiguration/McuClockSettingConfig/*,'node:value(McuClockSettingId)')"!][!//
    {
        [!INDENT "8"!][!//
        [!"node:value(McuMSCClk_Configuration/MSCClockSource)"!],    /* Msc ClkSrc */
        0U                                                           /* ClkDiv */
        [!ENDINDENT!][!//
    },
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};
[!ENDIF!][!//
[!ENDINDENT!][!//
[!INDENT "0"!][!//
/***************************************************************************************************
*                        Mcu_PBClockEspiConfigData Structure Description
****************************************************************************************************/
/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_PerClkType Mcu_PBClockEspiConfigData[[!"num:i(count(McuModuleConfiguration/McuClockSettingConfig/*))"!]U] =
{
    [!INDENT "4"!][!//
    [!LOOP "node:order(McuModuleConfiguration/McuClockSettingConfig/*,'node:value(McuClockSettingId)')"!][!//
    {
        [!INDENT "8"!][!//
        [!"node:value(McuESPIClk_Configuration/ESPIClockSource)"!],    /* PLL_Clk_Src ClkSrc */
        [!"node:value(McuESPIClk_Configuration/ESPIClockDiv)"!]U       /* ClkDiv */
        [!ENDINDENT!][!//
    },
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};
[!ENDINDENT!][!//

[!INDENT "0"!][!//
/***************************************************************************************************
*                        Mcu_PBClockWdtConfigData Structure Description
****************************************************************************************************/
/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_PerClkType Mcu_PBClockWdtConfigData[[!"num:i(count(McuModuleConfiguration/McuClockSettingConfig/*))"!]U] =
{
    [!INDENT "4"!][!//
    [!LOOP "node:order(McuModuleConfiguration/McuClockSettingConfig/*,'node:value(McuClockSettingId)')"!][!//
    {
        [!INDENT "8"!][!//
        [!"node:value(McuWDTClk_Configuration/CpuWDTClockSource)"!],    /* PLL_Clk_Src ClkSrc */
        [!"node:value(McuWDTClk_Configuration/CpuWDTClockDiv)"!]U       /* ClkDiv */
        [!ENDINDENT!][!//
    },
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};
[!ENDINDENT!][!//

[!INDENT "0"!][!//
/***************************************************************************************************
*                        Mcu_PBClockBaseTimerConfigData Structure Description
****************************************************************************************************/
[!VAR "BaseTimerId" = "num:i(0)"!][!//
[!VAR "BaseTimerString" = "num:i(0)"!][!//
/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_BaseTimerClkType Mcu_PBClockBaseTimerConfigData[[!"num:i(count(McuModuleConfiguration/McuClockSettingConfig/*))"!]U] =
{
    [!INDENT "4"!][!//
    [!LOOP "node:order(McuModuleConfiguration/McuClockSettingConfig/*,'node:value(McuClockSettingId)')"!][!//
    {
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            [!FOR "BaseTimerId" = "0" TO "ecu:get('Basetimer.MaxHwUnit')-1"!][!//
            /*BaseTimer[!"$BaseTimerId"!]*/
            {
                [!INDENT "16"!][!//
                [!VAR "BaseTimerString" = "concat('McuBaseTimerClk_Configuration/BaseTimer',$BaseTimerId,'ClockSource')"!][!//
                [!"node:value($BaseTimerString)"!],    /* PLL_Clk_Src ClkSrc */
                [!VAR "BaseTimerString" = "concat('McuBaseTimerClk_Configuration/BaseTimer',$BaseTimerId,'ClockDiv')"!][!//
                [!"node:value($BaseTimerString)"!]U       /* ClkDiv */
                [!ENDINDENT!][!//
            },
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
        },        
        [!ENDINDENT!][!//
    },
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};
[!ENDINDENT!][!//
[!INDENT "0"!][!//

/***************************************************************************************************
*                        Mcu_PBClockCanConfigData Structure Description
****************************************************************************************************/
/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_PerClkType Mcu_PBClockCanConfigData[[!"num:i(count(McuModuleConfiguration/McuClockSettingConfig/*))"!]U] =
{
    [!INDENT "4"!][!//
    [!LOOP "node:order(McuModuleConfiguration/McuClockSettingConfig/*,'node:value(McuClockSettingId)')"!][!//
    {
        [!INDENT "8"!][!//
        [!"node:value(McuCanClk_Configuration/CANClockSource)"!],    /* PLL_Clk_Src ClkSrc */
        [!"node:value(McuCanClk_Configuration/CANClockDiv)"!]U       /* ClkDiv */
        [!ENDINDENT!][!//
    },
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};
[!ENDINDENT!][!//

[!INDENT "0"!][!//
/***************************************************************************************************
*                        Mcu_PBClockDmaConfigData Structure Description
****************************************************************************************************/
/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_DMAClkType Mcu_PBClockDmaConfigData[[!"num:i(count(McuModuleConfiguration/McuClockSettingConfig/*))"!]U] =
{
    [!INDENT "4"!][!//
    [!LOOP "node:order(McuModuleConfiguration/McuClockSettingConfig/*,'node:value(McuClockSettingId)')"!][!//
    {
        [!INDENT "8"!][!//
        [!IF "node:value(McuDMAClk_Configuration/DMA0_CLKEN) = 'true'"!][!//
        TRUE,    /* DMA0CkEn */
        [!ELSE!][!//
        FALSE,   /* DMA0CkEn */
        [!ENDIF!][!//
        [!IF "node:value(McuDMAClk_Configuration/DMA1_CLKEN) = 'true'"!][!//
        TRUE,    /* DMA1CkEn */
        [!ELSE!][!//
        FALSE,   /* DMA1CkEn */
        [!ENDIF!][!//
        [!IF "node:value(McuDMAClk_Configuration/DMA2_CLKEN) = 'true'"!][!//
        TRUE,    /* DMA2CkEn */
        [!ELSE!][!//
        FALSE,   /* DMA2CkEn */
        [!ENDIF!][!//
        [!IF "node:value(McuDMAClk_Configuration/DMA3_CLKEN) = 'true'"!][!//
        TRUE    /* DMA3CkEn */
        [!ELSE!][!//
        FALSE    /* DMA3CkEn */
        [!ENDIF!][!//
        [!ENDINDENT!][!//
    },
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};
[!ENDINDENT!][!//

/***************************************************************************************************
*                        Mcu_ClockMonitorConfig Structure Description
****************************************************************************************************/
[!VAR "SysPllFre" = "num:i(node:value(McuModuleConfiguration/McuClockSettingConfig/*[1]/McuSysPllClk_Configuration/McuSysPllFrequency))"!][!//
    [!VAR "SysDiv" = "7"!]
    [!VAR "SysLow" = "114"!]
    [!VAR "SysHigh" = "132"!]
[!IF "$SysPllFre != num:i(400000000)"!][!//
    [!VAR "index"= "num:i(0)"!][!//
    [!VAR "found" = "'false'"!] 
    [!FOR "index" = "num:i(0)" TO "num:i(7)"!][!//
        [!VAR "FreTemp" = "num:i($SysPllFre div (bit:shl(2,$index)))"!][!//
            [!IF "$FreTemp >= 1000000"!][!// 检查 FreTemp 是否大于等于 1
                [!IF "$FreTemp < 2000000"!][!// 检查 FreTemp 是否小于 2
                    [!VAR "found" = "'true'"!]
                    [!VAR "SysDiv" = "num:i($index)"!]
                    [!BREAK!]
                [!ENDIF!]
            [!ENDIF!]
    [!ENDFOR!][!//
    [!IF "$found = 'false'"!][!// 如果没有找到合适的 FreTemp
        [!WARNING!][!//
            Warning: Alive Monitor Division caculation failed.
        [!ENDWARNING!][!//
    [!ENDIF!]
    [!VAR "SysLow" = "0.96*92800000*512 div $SysPllFre"!]
    [!VAR "SysHigh" = "1.04*99600000*512 div $SysPllFre"!]
[!ENDIF!][!//
[!VAR "PerPllFre" = "num:i(node:value(McuModuleConfiguration/McuClockSettingConfig/*[1]/McuPerPllClk_Configuration/McuPerPllFrequency))"!][!//
    [!VAR "PerDiv" = "7"!]
    [!VAR "PerLow" = "114"!]
    [!VAR "PerHigh" = "132"!]
[!IF "$PerPllFre != num:i(400000000)"!][!//
    [!VAR "index"= "num:i(0)"!][!//
    [!VAR "found" = "'false'"!] 
    [!FOR "index" = "num:i(0)" TO "num:i(7)"!][!//
        [!VAR "FreTemp" = "num:i($PerPllFre div (bit:shl(2,$index)))"!][!//
            [!IF "$FreTemp >= 1000000"!][!// 检查 FreTemp 是否大于等于 1
                [!IF "$FreTemp < 2000000"!][!// 检查 FreTemp 是否小于 2
                    [!VAR "found" = "'true'"!]
                    [!VAR "PerDiv" = "num:i($index)"!]
                    [!BREAK!]
                [!ENDIF!]
            [!ENDIF!]
    [!ENDFOR!][!//
    [!IF "$found = 'false'"!][!// 如果没有找到合适的 FreTemp
        [!WARNING!][!//
            Warning: Alive Monitor Division caculation failed.
        [!ENDWARNING!][!//
    [!ENDIF!]
    [!VAR "PerLow" = "0.96*92800000*512 div $PerPllFre"!]
    [!VAR "PerHigh" = "1.04*99600000*512 div $PerPllFre"!]
[!ENDIF!][!//
[!VAR "CpuPllFre" = "num:i(node:value(McuModuleConfiguration/McuClockSettingConfig/*[1]/McuSysClkDiv_Configuration/McuCpuClkFrequency ))"!][!//
    [!VAR "CpuDiv" = "7"!]
    [!VAR "CpuLow" = "114"!]
    [!VAR "CpuHigh" = "132"!]
[!IF "$CpuPllFre != num:i(400000000)"!][!//
    [!VAR "index"= "num:i(0)"!][!//
    [!VAR "found" = "'false'"!] 
    [!FOR "index" = "num:i(0)" TO "num:i(7)"!][!//
        [!VAR "FreTemp" = "num:i($CpuPllFre div (bit:shl(2,$index)))"!][!//
            [!IF "$FreTemp >= 1000000"!][!// 检查 FreTemp 是否大于等于 1
                [!IF "$FreTemp < 2000000"!][!// 检查 FreTemp 是否小于 2
                    [!VAR "found" = "'true'"!]
                    [!VAR "CpuDiv" = "num:i($index)"!]
                    [!BREAK!]
                [!ENDIF!]
            [!ENDIF!]
    [!ENDFOR!][!//
    [!IF "$found = 'false'"!][!// 如果没有找到合适的 FreTemp
        [!WARNING!][!//
            Warning: Alive Monitor Division caculation failed.
        [!ENDWARNING!][!//
    [!ENDIF!]
    [!VAR "CpuLow" = "0.96*92800000*512 div $CpuPllFre"!]
    [!VAR "CpuHigh" = "1.04*99600000*512 div $CpuPllFre"!]
[!ENDIF!][!//
static const Mcu_MonitorClkType Mcu_MonitorClkCfg[]=
{
    {
        /*syspll clock monitor*/
        {
            RCC_CLOCK_FREQMON_SYSPLL,
            /* #Violation: Mcu_PBcfg_c_REF_5 */
            (Rcc_ClockAliveMonDiv)[!"num:i($SysDiv)"!]U,
            [!"num:i($SysLow)"!]U,
            [!"num:i($SysHigh)"!]U,
        },
        /*Perpll clock monitor*/
        {
            RCC_CLOCK_FREQMON_PERPLL,
            /* #Violation: Mcu_PBcfg_c_REF_5 */
            (Rcc_ClockAliveMonDiv)[!"num:i($PerDiv)"!]U,
            [!"num:i($PerLow)"!]U,
            [!"num:i($PerHigh)"!]U,
        },
        /*syspll clock monitor*/
        {
            RCC_CLOCK_FREQMON_CLUSTER0CPU,
            /* #Violation: Mcu_PBcfg_c_REF_5 */
            (Rcc_ClockAliveMonDiv)[!"num:i($CpuDiv)"!]U,
            [!"num:i($CpuLow)"!]U,
            [!"num:i($CpuHigh)"!]U,
        },        
    },
};

/***************************************************************************************************
*                        Mcu_ClockConfig Structure Description
****************************************************************************************************/
static const Mcu_ClockConfigType Mcu_ClockConfig[MCU_NUM_CLOCK_SETTING] =
{        
    [!INDENT "4"!][!//
    [!LOOP "node:order(McuModuleConfiguration/McuClockSettingConfig/*,'node:value(McuClockSettingId)')"!][!//
    {
        [!INDENT "8"!][!//
        &Mcu_PBClockSysPllConfigData[[!"num:i(McuClockSettingId)"!]],
        &Mcu_PBClockPerPllConfigData[[!"num:i(McuClockSettingId)"!]],
        &Mcu_PBClockSysConfigData[[!"num:i(McuClockSettingId)"!]],
        &Mcu_PBClockGtmConfigData[[!"num:i(McuClockSettingId)"!]],
        [!IF "$IsTha6104 = num:i(0)"!][!//
        &Mcu_PBClockMscConfigData[[!"num:i(McuClockSettingId)"!]],
        [!ELSE!][!//
        NULL_PTR,
        [!ENDIF!][!//
        &Mcu_PBClockEspiConfigData[[!"num:i(McuClockSettingId)"!]],
        NULL_PTR,
        &Mcu_PBClockWdtConfigData[[!"num:i(McuClockSettingId)"!]],
        &Mcu_PBClockCanConfigData[[!"num:i(McuClockSettingId)"!]],
        &Mcu_PBClockSarAdcConfigData[[!"num:i(McuClockSettingId)"!]],
        [!IF "$IsTha6104 = num:i(0)"!][!//
        &Mcu_PBClockDsadcRdcConfigData[[!"num:i(McuClockSettingId)"!]],
        [!ELSE!][!//
        NULL_PTR,
        [!ENDIF!][!//
        &Mcu_PBClockDmaConfigData[[!"num:i(McuClockSettingId)"!]],
        &Mcu_PBClockBaseTimerConfigData[[!"num:i(McuClockSettingId)"!]],
        [!"num:i(node:value(McuSysClkDiv_Configuration/McuSysClkFrequency))"!]U,
        &Mcu_MonitorClkCfg[0],/* do not use*/
        [!ENDINDENT!][!//
    },
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};

[!INDENT "0"!][!//
[!IF "node:exists(GtmConfiguration/*[1])"!][!//
[!SELECT "GtmConfiguration/*[1]"!]
/***************************************************************************************************
*                        Mcu_CMUConfig Structure Description
****************************************************************************************************/
[!VAR "CMUClusterClockCfgValue" = "num:i(GtmGeneral/CMUClusterClockCfg)"!][!//
static const Gtm_ClockConfig Gtm_CMUConfig[] =
{
    [!INDENT "4"!][!//
    {
        [!INDENT "8"!][!//
        /* GTM cluster clock configuration */
        {
            [!INDENT "12"!][!//
            [!FOR "ClusterIndex" = "0" TO "ecu:get('Gtm.NumberOfCluster')-1"!][!//
            /* #Violation: Mcu_PBcfg_c_REF_5*/
            (Gtm_Cluster_Clk)[!"bit:and($CMUClusterClockCfgValue , 3)"!]U,/* Enable / disable GTM cluster [!"$ClusterIndex"!] clock */
            [!VAR "CMUClusterClockCfgValue" = "bit:shr($CMUClusterClockCfgValue,2)"!][!//
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
        },
        /* CMU global clock configuration */
        {
            [!INDENT "12"!][!//
            [!"num:i(GtmGeneral/CMUGlobalClkDivNumerator)"!]U, /* The numerator for CMU global clock resolution generator */
            [!"num:i(GtmGeneral/CMUGlobalClkDivDenominator)"!]U, /* The denominator for CMU global clock resolution generator */
            [!ENDINDENT!][!//
        },
        [!IF "node:exists(Cmu/*[1])"!][!//
        [!SELECT "Cmu/*[1]"!][!//
        /* CMU external clock configuration */
        {
            [!INDENT "12"!][!//
            /* The configuration of the external clock 0 */
            {
                [!INDENT "16"!][!//
                [!"num:i(CmuExternalClock/CmuExternalClk0Numerator)"!]U, /* The numerator for the external clock resolution generator */
                [!"num:i(CmuExternalClock/CmuExternalClk0Denominator)"!]U, /* The denominator for the external clock resolution generator */
                [!IF "CmuExternalClock/CmuEnableExternalClk0 = 'true'"!][!//
                TRUE /* Clock enable control */
                [!ELSE!]
                FALSE /* Clock enable control */
                [!ENDIF!]
                [!ENDINDENT!][!//
            },
            /* The configuration of the external clock 1 */
            {
                [!INDENT "16"!][!//
                [!"num:i(CmuExternalClock/CmuExternalClk1Numerator)"!], /* The numerator for the external clock resolution generator */
                [!"num:i(CmuExternalClock/CmuExternalClk1Denominator)"!], /* The denominator for the external clock resolution generator */
                [!IF "CmuExternalClock/CmuEnableExternalClk1 = 'true'"!][!//
                TRUE /* Clock enable control */
                [!ELSE!]
                FALSE /* Clock enable control */
                [!ENDIF!]
                [!ENDINDENT!][!//
            },
            /* The configuration of the external clock 2 */
            {
                [!INDENT "16"!][!//
                [!"num:i(CmuExternalClock/CmuExternalClk2Numerator)"!]U, /* The numerator for the external clock resolution generator */
                [!"num:i(CmuExternalClock/CmuExternalClk2Denominator)"!]U, /* The denominator for the external clock resolution generator */
                [!IF "CmuExternalClock/CmuEnableExternalClk2 = 'true'"!][!//
                TRUE /* Clock enable control */
                [!ELSE!]
                FALSE /* Clock enable control */
                [!ENDIF!]
                [!ENDINDENT!][!//
            }
            [!ENDINDENT!][!//
        },
        /* CMU configurable clock configuration */
        {
        {
            [!INDENT "12"!][!//
            [!"num:i(CmuConfigurableClock/CmuConfigurableClk0Div )"!]U, /* Count value for the clock divider */
            GTM_CMU_CLK_SRC_GCLK, /* Input selection for Clock Resolution Generator */
            [!IF "CmuConfigurableClock/CmuEnableConfigurableClk0 = 'true'"!][!//
            TRUE /*CmuClock 0 enable control */
            [!ELSE!]
            FALSE /*CmuClock 0 enable control */
            [!ENDIF!]
            [!ENDINDENT!][!//
        },
        {
            [!INDENT "12"!][!//
            [!"num:i(CmuConfigurableClock/CmuConfigurableClk1Div )"!]U, /* Count value for the clock divider */
            GTM_CMU_CLK_SRC_GCLK, /* Input selection for Clock Resolution Generator */
            [!IF "CmuConfigurableClock/CmuEnableConfigurableClk1 = 'true'"!][!//
            TRUE /*CmuClock 1 enable control */
            [!ELSE!]
            FALSE /*CmuClock 1 enable control */
            [!ENDIF!]
            [!ENDINDENT!][!//
        },
        {
            [!INDENT "12"!][!//
            [!"num:i(CmuConfigurableClock/CmuConfigurableClk2Div )"!]U, /* Count value for the clock divider */
            GTM_CMU_CLK_SRC_GCLK, /* Input selection for Clock Resolution Generator */
            [!IF "CmuConfigurableClock/CmuEnableConfigurableClk2 = 'true'"!][!//
            TRUE /*CmuClock 2 enable control */
            [!ELSE!]
            FALSE /*CmuClock 2 enable control */
            [!ENDIF!]
            [!ENDINDENT!][!//
        },
        {
            [!INDENT "12"!][!//
            [!"num:i(CmuConfigurableClock/CmuConfigurableClk3Div )"!]U, /* Count value for the clock divider */
            GTM_CMU_CLK_SRC_GCLK, /* Input selection for Clock Resolution Generator */
            [!IF "CmuConfigurableClock/CmuEnableConfigurableClk3 = 'true'"!][!//
            TRUE /*CmuClock 3 enable control */
            [!ELSE!]
            FALSE /*CmuClock 3 enable control */
            [!ENDIF!]
            [!ENDINDENT!][!//
        },
        {
            [!INDENT "12"!][!//
            [!"num:i(CmuConfigurableClock/CmuConfigurableClk4Div )"!]U, /* Count value for the clock divider */
            GTM_CMU_CLK_SRC_GCLK, /* Input selection for Clock Resolution Generator */
            [!IF "CmuConfigurableClock/CmuEnableConfigurableClk4 = 'true'"!][!//
            TRUE /*CmuClock 4 enable control */
            [!ELSE!]
            FALSE /*CmuClock 4 enable control */
            [!ENDIF!]
            [!ENDINDENT!][!//
        },
        {
            [!INDENT "12"!][!//
            [!"num:i(CmuConfigurableClock/CmuConfigurableClk5Div )"!]U, /* Count value for the clock divider */
            GTM_CMU_CLK_SRC_GCLK, /* Input selection for Clock Resolution Generator */
            [!IF "CmuConfigurableClock/CmuEnableConfigurableClk5 = 'true'"!][!//
            TRUE /*CmuClock 5 enable control */
            [!ELSE!]
            FALSE /*CmuClock 5 enable control */
            [!ENDIF!]
            [!ENDINDENT!][!//
        },
        {
            [!INDENT "12"!][!//
            [!"num:i(CmuConfigurableClock/CmuConfigurableClk6Div )"!]U, /* Count value for the clock divider */
            GTM_CMU_CLK_SRC_GCLK, /* Input selection for Clock Resolution Generator */
            [!IF "CmuConfigurableClock/CmuEnableConfigurableClk6 = 'true'"!][!//
            TRUE /*CmuClock 6 enable control */
            [!ELSE!]
            FALSE /*CmuClock 6 enable control */
            [!ENDIF!]
            [!ENDINDENT!][!//
        },
        {
            [!INDENT "12"!][!//
            [!"num:i(CmuConfigurableClock/CmuConfigurableClk7Div )"!]U, /* Count value for the clock divider */
            GTM_CMU_CLK_SRC_GCLK, /* Input selection for Clock Resolution Generator */
            [!IF "CmuConfigurableClock/CmuEnableConfigurableClk7 = 'true'"!][!//
            TRUE /*CmuClock 7 enable control */
            [!ELSE!]
            FALSE /*CmuClock 7 enable control */
            [!ENDIF!]
            [!ENDINDENT!][!//
        },
        },
        /* CMU fixed clock configuration */
        {
            [!INDENT "12"!][!//
            [!"CmuFixedClock/CmuFxdClkSourceSelect"!], /* Input selection for CMU fixed clock */
            [!IF "CmuFixedClock/CmuEnableAllFixedClocks = 'true'"!][!//
            TRUE /*fixed enable control */
            [!ELSE!]
            FALSE /*fixed enable control */
            [!ENDIF!]
            [!ENDINDENT!][!//
        }
        [!ENDSELECT!][!//
        [!ENDIF!]
        [!ENDINDENT!][!//
    }
    [!ENDINDENT!][!//
};
[!ENDSELECT!][!//
[!ENDIF!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!IF "GtmConfiguration/*[1]/GtmGeneral/GTM_TBU_Support = 'true'"!][!//
[!VAR "GTM_TBU_EN" = "num:i(1)"!][!//
[!SELECT "GtmConfiguration/*[1]/Tbu"!]
/***************************************************************************************************
*                        Mcu_TBUConfig Structure Description
****************************************************************************************************/
[!LOOP "node:order(*[1]/TbuChannel/*,'node:value(TbuChannelID)')"!][!//
    [!IF "TbuChannelID = '0'"!][!//
        [!IF "TbuEnableChannel = 'true'"!][!//
        /* The configuration of the TBU channel [!"TbuChannelID"!] */
        static const Gtm_Tbu_Channel0 Tbu_Channel0=
        {
            [!INDENT "4"!][!//
            /* Free timer offset value */
            [!"TbuTimebaseValue"!]U,
            /* Free timer clock source */
            [!"TbuChannelClockSource"!],
            /* Count value alignment */
            [!"TbuChannelResolution"!],
            /* Enable / disable free timer */
            TRUE
            [!ENDINDENT!][!//
        };
        [!ENDIF!]
    [!ELSE!][!//]
        [!IF "TbuEnableChannel = 'true'"!][!//
        static const Gtm_Tbu_Channel12 Tbu_Channel[!"TbuChannelID"!]=
        {
            [!INDENT "4"!][!//
            /* Free timer offset value */
            [!"TbuTimebaseValue"!]U,
            /* Free timer clock source */
            [!"TbuChannelClockSource"!],
            /* Counting mode */
            [!"TbuChannelModeSelect"!],
            /* Enable / disable free timer */
            TRUE
            [!ENDINDENT!][!//
        };

        [!ENDIF!]
    [!ENDIF!][!//
[!ENDLOOP!][!//

  /* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_TBUConfigType Mcu_TBUConfig[1U] =
{
    [!INDENT "4"!][!//
    {    
    [!LOOP "node:order(*[1]/TbuChannel/*,'node:value(TbuChannelID)')"!][!//
        [!INDENT "8"!][!//
        /* The configuration of the TBU channel [!"TbuChannelID"!] */
        [!IF "TbuEnableChannel = 'true'"!][!//
        &Tbu_Channel[!"TbuChannelID"!],
        [!ELSE!]
        NULL_PTR,
        [!ENDIF!]     
      [!ENDINDENT!][!//
    [!ENDLOOP!][!//
    }
    [!ENDINDENT!][!//
};
[!ENDSELECT!][!//
[!ENDIF!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
/***************************************************************************************************
*                        Mcu_GTMWrapperConfig Structure Description
****************************************************************************************************/
[!NOCODE!][!//
[!CALL "GTM_GET_TIM_NUMBER"!][!//
[!CALL "GTM_GET_DSADC_NUMBER"!][!//
[!CALL "GTM_GET_TOUTSEL_NUMBER"!][!//
[!CALL "GTM_GET_MSC"!][!//
[!CALL "GTM_GET_MSC_LEVEL2"!][!//
[!CALL "GTM_GET_DMA"!][!//
[!CALL "GTM_GET_DMA_LEVEL2"!][!//
[!CALL "GTM_GET_DSADC_TRIGGER"!][!//

[!ENDNOCODE!][!//

[!IF "$ValidTimChannel != 0"!][!//
static const Mcu_TimConfigType Mcu_TimConfig[[!"num:i($ValidTimChannel)"!]] =
{
    [!INDENT "4"!][!//
    /*TIM Id, Tim Channel Id, SelNum */
    [!CALL "GTM_GET_TIM_NUMBER"!][!//
    [!ENDINDENT!][!//
};

[!ENDIF!][!//
[!IF "$ValidDsadcChannel != 0"!][!//
static const Mcu_DsadcConfigType Mcu_DsadcConfig[[!"num:i($ValidDsadcChannel)"!]] =
{
    [!INDENT "4"!][!//
    /*DSADC Id, Dsadc Channel Id, SelNum */
    [!CALL "GTM_GET_DSADC_NUMBER"!][!//
    [!ENDINDENT!][!//
};

[!ENDIF!][!//
[!IF "$ValidDsadcTrigChannel != 0"!][!//
static const Mcu_GtmToDsadcConfigType Mcu_GtmToDsadcConfig[[!"num:i($ValidDsadcTrigChannel)"!]] =
{
    [!INDENT "4"!][!//
    /*GtmToDsadcTrigGroup Id, Dsadc Channel Id, SelNum */
    [!CALL "GTM_GET_DSADC_TRIGGER"!][!//
    [!ENDINDENT!][!//
};

[!ENDIF!][!//
[!IF "$ValidTomChannel != 0"!][!//
static const Mcu_ToutConfigType Mcu_ToutConfig[[!"num:i($ValidTomChannel)"!]] =
{
    [!INDENT "4"!][!//
    /*SelNum , ToutNum*/
    [!CALL "GTM_GET_TOUTSEL_NUMBER"!][!//
    [!ENDINDENT!][!//
};

[!ENDIF!][!//
[!IF "$ValidAdcChannel != 0"!][!//
/***************************************************************************************************
*                        Mcu_AdcConfigType Structure Description
****************************************************************************************************/
static const Mcu_AdcConfigType Mcu_AdcConfig[[!"num:i($ValidAdcChannel)"!]] =
{
    [!INDENT "4"!][!//
    /*ADC id,    Trigger Group Id, SelValue */
    [!CALL "GTM_GET_SARADC_TRIGGER"!][!//
    [!ENDINDENT!][!//
};
[!ENDIF!][!//

[!IF "$McuGtmSourceNum != 0"!][!//
/* GTM trigger source configuration parameters */
static const Mcu_GtmTriggerConfigType GtmTriggerConfig[[!"num:i($McuGtmSourceNum)"!]] = 
{
[!SELECT "GtmConfiguration/*[1]/GtmToPeripheral/*[1]/GtmOutput"!][!//
    [!FOR "TrigIndex" = "0" TO "num:i(count(./*) - 1)"!][!//
    [!NOCODE!][!//
    [!VAR "McuClockReference" = "./*[num:i($TrigIndex + 1)]/GtmMcuClockReference"!][!//
    [!VAR "Var_GtmTimer" = "./*[num:i($TrigIndex + 1)]/GtmTimerUsed"!][!//
    [!VAR "GtmTimerType" = "num:i(0)"!][!//
    [!VAR "GtmTimerModNo" = "num:i(0)"!][!//
    [!VAR "GtmTimerChNo" = "num:i(0)"!][!//
    [!ENDNOCODE!][!//
    [!INDENT "4"!][!//
    {
        [!NOCODE!][!//
        [!IF "node:exists(node:ref($Var_GtmTimer)/GtmAtomChannel)"!][!//
            [!VAR "GtmTimerModule" = "'GTM_OUTPUT_MODULE_ATOM'"!][!//
        [!ELSE!][!//
            [!VAR "GtmTimerModule" = "'GTM_OUTPUT_MODULE_TOM'"!][!//
        [!ENDIF!][!//
        [!VAR "GtmTimerModuleIndex" = "node:ref($Var_GtmTimer)/ModuleId"!][!//
        [!VAR "GtmTimerModuleChIndex" = "node:ref($Var_GtmTimer)/ChannelId"!][!//
        [!VAR "GtmTimerClockRef" = "./*[num:i($TrigIndex + 1)]/GtmMcuClockReference"!][!//
        [!IF "not(node:exists(node:ref($Var_GtmTimer)/GtmAtomChannel))"!][!//
            [!VAR "McuTimerClockSource" = "concat('GTM_PWM_CLOCK_', ./*[num:i($TrigIndex + 1)]/GtmTimerClockSelect)"!][!//
        [!ELSE!][!//
            [!VAR "McuTimerClockSource" = "concat('GTM_PWM_CLOCK_CMUCLK', text:split(node:ref(./*[num:i($TrigIndex + 1)]/GtmMcuClockReference)/McuClockReferenceSelect, 'CMU_CLK')[last()])"!][!//
        [!ENDIF!][!//
        [!VAR "McuTimerClockFrequency" = "node:value(node:ref($GtmTimerClockRef)/CmuClockReferencePointFrequency)"!][!//
        [!VAR "GtmTimerPeriod" = "./*[num:i($TrigIndex + 1)]/GtmTimerTimePeriod"!][!//
        [!VAR "GtmTimerPeriodSecond" = "./*[num:i($TrigIndex + 1)]/GtmTimerTimePeriod"!][!//
        [!IF "$GtmTimerPeriodSecond != num:i(0)"!][!//
            [!VAR "GtmTimerPeriodInTicks" = "$GtmTimerPeriodSecond * $McuTimerClockFrequency  div 1000000"!][!//
        [!ELSE!][!//
            [!VAR "GtmTimerPeriodInTicks" = "./*[num:i($TrigIndex + 1)]/GtmTimerCM0Ticks"!][!//
        [!ENDIF!][!//
        [!IF "$GtmTimerModule = 'GTM_OUTPUT_MODULE_ATOM'"!][!//
            [!IF "$GtmTimerPeriodInTicks > 16777215"!][!//
                [!ERROR!][!//
                [101-00-08-ERROR]: GtmTimer exceeds the maximum count value of the ATOM channel
                [!ENDERROR!][!//
            [!ENDIF!][!//
        [!ELSE!][!//
            [!IF "$GtmTimerPeriodInTicks > 65535"!][!//
                [!ERROR!][!//
                [101-00-08-ERROR]: GtmTimer exceeds the maximum count value of the TOM channel
                [!ENDERROR!][!//
            [!ENDIF!][!//
        [!ENDIF!][!//
        /*mcu CHECK*/
        /*[!"$Var_GtmTimer"!]
        [!"$McuClockReference"!]
        */
        /*call getgtmparams*/
        [!CALL "GetGtmParams","ref1"= "$Var_GtmTimer",
        "GtmTimerType"="$GtmTimerType",
        "GtmTimerModNo"="$GtmTimerModNo",
        "GtmTimerChNo"="$GtmTimerChNo"!][!//
        /*
                    [!"$GtmTimerType"!],
                    [!"$GtmTimerModNo"!],
                    [!"$GtmTimerChNo"!],
        */
        /*check atom use cmu clk, and tom use fxclk*/
        [!VAR "McuClockRef" = "node:value(node:ref($McuClockReference)/McuClockReferenceSelect)"!][!//
        /*[!"$McuClockRef"!] [!"$GtmTimerType"!]*/
        [!IF "$McuClockRef != 'CMU_FXCLK' and $GtmTimerType = 'TOM'"!][!//
        [!ERROR!][!//
            [101-00-05-ERROR]: Invalid clock source of [!"node:name(.)"!], the reference clock based on TOM must be CMU_FXCLK.in Gtmtrigger.
        [!ENDERROR!][!//
        [!ELSEIF "not(contains($McuClockRef, 'CMU_CLK')) and $GtmTimerType = 'ATOM'"!][!//
        [!ERROR!][!//
            [101-00-06-ERROR]: Invalid clock source of [!"node:name(.)"!], the reference clock based on ATOM must be CMU_CLK[x], x=0-7. in Gtmtrigger.
        [!ENDERROR!][!//
        [!ENDIF!][!//$McuClockRef != 'CMU_FXCLK' and $GtmTimerType = TOM

        [!ENDNOCODE!][!//
        [!INDENT "8"!][!//
        /* GtmOutputSignal[!"$TrigIndex"!] */
        {
            [!INDENT "12"!][!//
            /* Hardware Channel Type */
            (uint8)[!"$GtmTimerModule"!],
            /* Hardware Timer Module Index */
            [!"$GtmTimerModuleIndex"!]U,
            /* Group index, only used for TIO module */
            0U,
            /* Hardware Channel Index */
            [!"$GtmTimerModuleChIndex"!]U
            [!ENDINDENT!][!//
        },
        {
            [!INDENT "12"!][!//
            /* Clock Source */
            [!"$McuTimerClockSource"!],
            /* Period */
            [!"num:i($GtmTimerPeriodInTicks)"!]U,
            /* Duty Cycle */
            [!"num:i($GtmTimerPeriodInTicks div 2)"!]U,
            /* Initial Counter Shift */
            0U,
            /* reserve*/
            {
                0U,
                0U,
                0U,
            },
            /* Channel Counter Reset Source */
            GTM_PWM_RESETEVENT_ONCM0,
            /* Signal Level */
            GTM_SIGNALSTATE_LOW,
            {
                [!INDENT "16"!][!//
                /* CCU0 Trigger Interrupt */
                FALSE,
                /* CCU1 Trigger Interrupt */
                FALSE,
                /* Interrupt Mode */
                GTM_IRQMODE_LEVEL
                [!ENDINDENT!][!//
            },
            /* Trigger Output Signal Select */
            GTM_PWM_TRIGOUT_FORWARD,
            /*PWM channel count mode*/
            GTM_PWM_COUNTMODE_UP,
            /* Update Mechanism */
            TRUE,
            /* Channel Control */
            TRUE,
            /* Channel Output Control */
            TRUE,
            /* Update Immediate Control */
            TRUE
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    },
    [!ENDINDENT!][!//
    [!ENDFOR!][!//
[!ENDSELECT!][!//
};

[!ENDIF!][!//
/***************************************************************************************************
*                        Mcu_GTM_MscTypeConfig Structure Description
****************************************************************************************************/
[!IF "$MSC_ValidCh != 0"!][!//
static const Mcu_MscConfigType Mcu_MscConfig[[!"num:i($MSC_ValidCh)"!]] =
{
    [!INDENT "4"!][!//
    /*SetId, signal Id, SelValue */
    [!CALL "GTM_GET_MSC"!][!//
    [!ENDINDENT!][!//
};

[!ENDIF!][!//
[!IF "$MscL2_ValidCh != 0"!][!//
static const Mcu_MscSetL2ConfigType Gtm_MscSetL2Config[[!"num:i($MscL2_ValidCh)"!]] =
{
    [!INDENT "4"!][!//
    /*SetId,RegisterName,signal Id,MSC num */
    [!CALL "GTM_GET_MSC_LEVEL2"!][!//
    [!ENDINDENT!][!//
};

[!ENDIF!][!//
/***************************************************************************************************
*                        Mcu_GTM_DmaTypeConfig Structure Description
****************************************************************************************************/
[!IF "$DMA_ValidCh != 0"!][!//
static const Mcu_DmaConfigType Mcu_DmaConfig[[!"num:i($DMA_ValidCh)"!]] =
{
    [!INDENT "4"!][!//
    /*RegsterOffset, SelValue */
    [!CALL "GTM_GET_DMA"!][!//
    [!ENDINDENT!][!//
};

[!ENDIF!][!//
[!IF "$DmaL2_ValidCh != 0"!][!//
static const Mcu_DmaL2ConfigType Mcu_DmaL2Config[[!"num:i($DmaL2_ValidCh)"!]] =
{
    [!INDENT "4"!][!//
    /*RegsterOffset,Channel */
    [!CALL "GTM_GET_DMA_LEVEL2"!][!//
    [!ENDINDENT!][!//
};

[!ENDIF!][!//
static const Mcu_GtmWrapperConfigType Mcu_GtmWrapperConfig[1U]=
{
    [!INDENT "4"!][!//
    {
        [!INDENT "8"!][!//
        /* Tim Setting */
        [!IF "$ValidTimChannel != 0"!][!//
        &Mcu_TimConfig[0],
        [!ELSE!]
        NULL_PTR,   
        [!ENDIF!][!//
        /* Dsadc Setting */
        [!IF "$ValidDsadcChannel != 0"!][!//
        &Mcu_DsadcConfig[0],
        [!ELSE!]
        NULL_PTR,   
        [!ENDIF!][!//
        /* Tout Setting */
        [!IF "$ValidTomChannel != 0"!][!//
        &Mcu_ToutConfig[0],
        [!ELSE!]
        NULL_PTR,   
        [!ENDIF!][!//
        /* Adc Setting */
        [!IF "$ValidAdcChannel != 0"!][!//
        &Mcu_AdcConfig[0],
        [!ELSE!]
        NULL_PTR,   
        [!ENDIF!][!//
        /* GtmToDsadc Setting */
        [!IF "$ValidDsadcTrigChannel != 0"!][!//
        &Mcu_GtmToDsadcConfig[0],
        [!ELSE!]
        NULL_PTR,
        [!ENDIF!][!//
        /* Msc Setting */
        [!IF "$MSC_ValidCh != 0"!][!//
        &Mcu_MscConfig[0],
        [!ELSE!]
        NULL_PTR,
        [!ENDIF!][!//
        [!IF "$MscL2_ValidCh != 0"!][!//
        &Gtm_MscSetL2Config[0],
        [!ELSE!]
        NULL_PTR,
        [!ENDIF!][!//
        /* Dma Setting */
        [!IF "$DmaL2_ValidCh != 0"!][!//
        &Mcu_DmaConfig[0],
        &Mcu_DmaL2Config[0],
        [!ELSE!]
        NULL_PTR,
        NULL_PTR,
        [!ENDIF!][!//
        [!"num:i($ValidTimChannel)"!]U, /* Num of Tim cfg*/
        [!"num:i($ValidDsadcChannel)"!]U, /* Num of Dsadc CFG*/
        [!"num:i($ValidTomChannel)"!]U, /* Num of TOUT cfg*/
        [!"num:i($ValidAdcChannel)"!]U, /* Num of Adc Cfg*/
        [!"num:i($ValidDsadcTrigChannel)"!]U, /* Num of Gtm to Dsadc Cfg */
        [!"num:i($MSC_ValidCh)"!]U, /* Num of Msc Cfg */
        [!"num:i($MscL2_ValidCh)"!]U, /* Num of Msc L2 cfg*/
        [!"num:i($DMA_ValidCh)"!]U, /* Num of Dma L1 Cfg */
        [!"num:i($DmaL2_ValidCh)"!]U, /* Num of Dma L2 Cfg */
        [!ENDINDENT!][!//
    }
    [!ENDINDENT!][!//
};

[!ENDINDENT!][!//
[!INDENT "0"!][!//
[!ENDINDENT!][!//
[!IF "node:exists(McuModuleConfiguration/McuResetConfig)"!][!//
/* Reset setting */
static const Mcu_ResetConfigType Mcu_ResetConfig[MCU_RESET_CONFIG_NUM] =
{
    {RCC_RSTSRC_SW,[!"McuModuleConfiguration/McuResetConfig/McuSWResetConf"!]},
    {RCC_RSTSRC_ESR0,[!"McuModuleConfiguration/McuResetConfig/McuESR0ResetConf"!]},
    {RCC_RSTSRC_ESR1,[!"McuModuleConfiguration/McuResetConfig/McuESR1ResetConf"!]},
    {RCC_RSTSRC_SAC,[!"McuModuleConfiguration/McuResetConfig/McuSACResetConf"!]},
    {RCC_RSTSRC_IWDG,[!"McuModuleConfiguration/McuResetConfig/McuIWDGResetConf"!]},
    {RCC_RSTSRC_CPU0REQ,[!"McuModuleConfiguration/McuResetConfig/McuCPU0REQResetConf"!]},
    {RCC_RSTSRC_CPU1REQ,[!"McuModuleConfiguration/McuResetConfig/McuCPU1REQResetConf"!]},
};

[!ENDIF!][!//
[!NOCODE!]
[!VAR "WakeupReason" = "num:i(0)"!][!//
[!VAR "ValidMode" = "num:i(0)"!][!//
[!VAR "StandbyModeEnable" = "num:i(0)"!][!//
[!LOOP "node:order(McuModuleConfiguration/McuModeSettingConf/*,'node:value(McuMode)')"!][!//
    [!VAR "ValidMode" = "num:i($ValidMode + bit:shl(1,num:i(node:value(McuMode))) )"!][!//
    [!IF "node:value(McuMode) = '1' "!][!//
        [!VAR "StandbyModeEnable" = "num:i(1)"!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!]
[!IF "$StandbyModeEnable = 1"!][!//
/* parameter for standby mode */
static const Pwrc_StandbySourceConfig Mcu_StdbyCfg[] =
{
[!NOCODE!]
[!VAR "WakeupSourceNum" = "num:i(0)"!][!//
[!LOOP "node:order(McuModuleConfiguration/McuModeSettingConf/*,'node:value(McuMode)')"!][!//
    [!IF "node:value(McuMode) = '1' "!][!//
        [!CODE!]
        [!IF "./McuStdbySettingConf/McuStdbyWakeupSource/ESR0  = 'true' "!][!//
        [!VAR "WakeupSourceNum" = "num:i($WakeupSourceNum + 1)"!][!//
    {
        PWRC_STBWAKEUPSOURCE_ESR0,
        PWRC_STBWAKEUPPINEDGE_[!"node:value(./McuStdbySettingConf/McuStdbyWakeupSource/ESR0Edge)"!]
    },
        [!ENDIF!][!//
        [!IF "./McuStdbySettingConf/McuStdbyWakeupSource/ESR1  = 'true' "!][!//
        [!VAR "WakeupSourceNum" = "num:i($WakeupSourceNum + 1)"!][!// 
    {
        PWRC_STBWAKEUPSOURCE_ESR1,
        PWRC_STBWAKEUPPINEDGE_[!"node:value(./McuStdbySettingConf/McuStdbyWakeupSource/ESR1Edge)"!]
    },
        [!ENDIF!][!//
        [!IF "./McuStdbySettingConf/McuStdbyWakeupSource/PINA  = 'true' "!][!//
        [!VAR "WakeupSourceNum" = "num:i($WakeupSourceNum + 1)"!][!// 
    {
        PWRC_STBWAKEUPSOURCE_PINA,
        PWRC_STBWAKEUPPINEDGE_[!"node:value(./McuStdbySettingConf/McuStdbyWakeupSource/PINAEdge)"!]
    },
        [!ENDIF!][!//
        [!IF "./McuStdbySettingConf/McuStdbyWakeupSource/PINB  = 'true' "!][!//
        [!VAR "WakeupSourceNum" = "num:i($WakeupSourceNum + 1)"!][!// 
    {
        PWRC_STBWAKEUPSOURCE_PINB,
        PWRC_STBWAKEUPPINEDGE_[!"node:value(./McuStdbySettingConf/McuStdbyWakeupSource/PINBEdge)"!]
    },
        [!ENDIF!][!//
        [!IF "./McuStdbySettingConf/McuStdbyWakeupSource/PORST  = 'true' "!][!//
        [!VAR "WakeupSourceNum" = "num:i($WakeupSourceNum + 1)"!][!// 
    {
        PWRC_STBWAKEUPSOURCE_PORST,
        PWRC_STBWAKEUPPINEDGE_[!"node:value(./McuStdbySettingConf/McuStdbyWakeupSource/PORSTEdge)"!]
    },
        [!ENDIF!][!//
        [!IF "./McuStdbySettingConf/McuStdbyWakeupSource/VEXT  = 'true' "!][!//
        [!VAR "WakeupSourceNum" = "num:i($WakeupSourceNum + 1)"!][!// 
    {
        PWRC_STBWAKEUPSOURCE_VEXT,
        PWRC_STBWAKEUPPINEDGE_[!"node:value(./McuStdbySettingConf/McuStdbyWakeupSource/VEXTEdge)"!]
    },
        [!ENDIF!][!//
        [!IF "./McuStdbySettingConf/McuStdbyWakeupSource/P33_00  = 'true' "!][!//
        [!VAR "WakeupSourceNum" = "num:i($WakeupSourceNum + 1)"!][!// 
    {
        PWRC_STBWAKEUPSOURCE_P33_00,
        PWRC_STBWAKEUPPINEDGE_[!"node:value(./McuStdbySettingConf/McuStdbyWakeupSource/P33_00Edge)"!]
    },
        [!ENDIF!][!//
        [!IF "./McuStdbySettingConf/McuStdbyWakeupSource/P33_01  = 'true' "!][!//
        [!VAR "WakeupSourceNum" = "num:i($WakeupSourceNum + 1)"!][!// 
    {
        PWRC_STBWAKEUPSOURCE_P33_01,
        PWRC_STBWAKEUPPINEDGE_[!"node:value(./McuStdbySettingConf/McuStdbyWakeupSource/P33_01Edge)"!]
    },
        [!ENDIF!][!//
        [!IF "./McuStdbySettingConf/McuStdbyWakeupSource/P33_02  = 'true' "!][!//
        [!VAR "WakeupSourceNum" = "num:i($WakeupSourceNum + 1)"!][!// 
    {
        PWRC_STBWAKEUPSOURCE_P33_02,
        PWRC_STBWAKEUPPINEDGE_[!"node:value(./McuStdbySettingConf/McuStdbyWakeupSource/P33_02Edge)"!]
    },
        [!ENDIF!][!//
        [!IF "./McuStdbySettingConf/McuStdbyWakeupSource/P33_03  = 'true' "!][!//
        [!VAR "WakeupSourceNum" = "num:i($WakeupSourceNum + 1)"!][!// 
    {
        PWRC_STBWAKEUPSOURCE_P33_03,
        PWRC_STBWAKEUPPINEDGE_[!"node:value(./McuStdbySettingConf/McuStdbyWakeupSource/P33_03Edge)"!]
    },
        [!ENDIF!][!//
        [!IF "./McuStdbySettingConf/McuStdbyWakeupSource/P33_04  = 'true' "!][!//
        [!VAR "WakeupSourceNum" = "num:i($WakeupSourceNum + 1)"!][!// 
    {
        PWRC_STBWAKEUPSOURCE_P33_04,
        PWRC_STBWAKEUPPINEDGE_[!"node:value(./McuStdbySettingConf/McuStdbyWakeupSource/P33_04Edge)"!]
    },
        [!ENDIF!][!//
        [!IF "./McuStdbySettingConf/McuStdbyWakeupSource/P33_05  = 'true' "!][!//
        [!VAR "WakeupSourceNum" = "num:i($WakeupSourceNum + 1)"!][!// 
    {
        PWRC_STBWAKEUPSOURCE_P33_05,
        PWRC_STBWAKEUPPINEDGE_[!"node:value(./McuStdbySettingConf/McuStdbyWakeupSource/P33_05Edge)"!]
    },
        [!ENDIF!][!//
        [!IF "./McuStdbySettingConf/McuStdbyWakeupSource/P33_06  = 'true' "!][!//
        [!VAR "WakeupSourceNum" = "num:i($WakeupSourceNum + 1)"!][!// 
    {
        PWRC_STBWAKEUPSOURCE_P33_06,
        PWRC_STBWAKEUPPINEDGE_[!"node:value(./McuStdbySettingConf/McuStdbyWakeupSource/P33_06Edge)"!]
    },
        [!ENDIF!][!//
        [!IF "./McuStdbySettingConf/McuStdbyWakeupSource/P33_07  = 'true' "!][!//
        [!VAR "WakeupSourceNum" = "num:i($WakeupSourceNum + 1)"!][!// 
    {
        PWRC_STBWAKEUPSOURCE_P33_07,
        PWRC_STBWAKEUPPINEDGE_[!"node:value(./McuStdbySettingConf/McuStdbyWakeupSource/P33_07Edge)"!]
    },
        [!ENDIF!][!//
        [!IF "./McuStdbySettingConf/McuStdbyWakeupSource/P33_08  = 'true' "!][!//
        [!VAR "WakeupSourceNum" = "num:i($WakeupSourceNum + 1)"!][!// 
    {
        PWRC_STBWAKEUPSOURCE_P33_08,
        PWRC_STBWAKEUPPINEDGE_[!"node:value(./McuStdbySettingConf/McuStdbyWakeupSource/P33_08Edge)"!]
    },
        [!ENDIF!][!//
        [!IF "./McuStdbySettingConf/McuStdbyWakeupSource/P33_09  = 'true' "!][!//
        [!VAR "WakeupSourceNum" = "num:i($WakeupSourceNum + 1)"!][!// 
    {
        PWRC_STBWAKEUPSOURCE_P33_09,
        PWRC_STBWAKEUPPINEDGE_[!"node:value(./McuStdbySettingConf/McuStdbyWakeupSource/P33_09Edge)"!]
    },
        [!ENDIF!][!//
        [!IF "./McuStdbySettingConf/McuStdbyWakeupSource/P33_10  = 'true' "!][!//
        [!VAR "WakeupSourceNum" = "num:i($WakeupSourceNum + 1)"!][!// 
    {
        PWRC_STBWAKEUPSOURCE_P33_10,
        PWRC_STBWAKEUPPINEDGE_[!"node:value(./McuStdbySettingConf/McuStdbyWakeupSource/P33_10Edge)"!]
    },
        [!ENDIF!][!//
        [!IF "./McuStdbySettingConf/McuStdbyWakeupSource/P33_11  = 'true' "!][!//
        [!VAR "WakeupSourceNum" = "num:i($WakeupSourceNum + 1)"!][!// 
    {
        PWRC_STBWAKEUPSOURCE_P33_11,
        PWRC_STBWAKEUPPINEDGE_[!"node:value(./McuStdbySettingConf/McuStdbyWakeupSource/P33_11Edge)"!]
    },
        [!ENDIF!][!//
        [!IF "./McuStdbySettingConf/McuStdbyWakeupSource/P33_13  = 'true' "!][!//
        [!VAR "WakeupSourceNum" = "num:i($WakeupSourceNum + 1)"!][!// 
    {
        PWRC_STBWAKEUPSOURCE_P33_13,
        PWRC_STBWAKEUPPINEDGE_[!"node:value(./McuStdbySettingConf/McuStdbyWakeupSource/P33_13Edge)"!]
    },
        [!ENDIF!][!//
        [!IF "./McuStdbySettingConf/McuStdbyWakeupSource/P33_14  = 'true' "!][!//
        [!VAR "WakeupSourceNum" = "num:i($WakeupSourceNum + 1)"!][!// 
    {
        PWRC_STBWAKEUPSOURCE_P33_14,
        PWRC_STBWAKEUPPINEDGE_[!"node:value(./McuStdbySettingConf/McuStdbyWakeupSource/P33_14Edge)"!]
    },
        [!ENDIF!][!//
        [!IF "./McuStdbySettingConf/McuStdbyWakeupSource/P33_15  = 'true' "!][!//
        [!VAR "WakeupSourceNum" = "num:i($WakeupSourceNum + 1)"!][!// 
    {
        PWRC_STBWAKEUPSOURCE_P33_15,
        PWRC_STBWAKEUPPINEDGE_[!"node:value(./McuStdbySettingConf/McuStdbyWakeupSource/P33_15Edge)"!]
    },
        [!ENDIF!][!//
        [!IF "./McuStdbySettingConf/McuStdbyWakeupSource/P34_01  = 'true' "!][!//
        [!VAR "WakeupSourceNum" = "num:i($WakeupSourceNum + 1)"!][!// 
    {
        PWRC_STBWAKEUPSOURCE_P34_01,
        PWRC_STBWAKEUPPINEDGE_[!"node:value(./McuStdbySettingConf/McuStdbyWakeupSource/P34_01Edge)"!]
    },
        [!ENDIF!][!//
        [!IF "./McuStdbySettingConf/McuStdbyWakeupSource/P34_02  = 'true' "!][!//
        [!VAR "WakeupSourceNum" = "num:i($WakeupSourceNum + 1)"!][!// 
    {
        PWRC_STBWAKEUPSOURCE_P34_02,
        PWRC_STBWAKEUPPINEDGE_[!"node:value(./McuStdbySettingConf/McuStdbyWakeupSource/P34_02Edge)"!]
    },
        [!ENDIF!][!//
        [!IF "./McuStdbySettingConf/McuStdbyWakeupSource/P34_03  = 'true' "!][!//
        [!VAR "WakeupSourceNum" = "num:i($WakeupSourceNum + 1)"!][!// 
    {
        PWRC_STBWAKEUPSOURCE_P34_03,
        PWRC_STBWAKEUPPINEDGE_[!"node:value(./McuStdbySettingConf/McuStdbyWakeupSource/P34_03Edge)"!]
    },
        [!ENDIF!][!//
        [!IF "./McuStdbySettingConf/McuStdbyWakeupSource/P34_04  = 'true' "!][!//
        [!VAR "WakeupSourceNum" = "num:i($WakeupSourceNum + 1)"!][!// 
    {
        PWRC_STBWAKEUPSOURCE_P34_04,
        PWRC_STBWAKEUPPINEDGE_[!"node:value(./McuStdbySettingConf/McuStdbyWakeupSource/P34_04Edge)"!]
    },
        [!ENDIF!][!//
        [!IF "./McuStdbySettingConf/McuStdbyWakeupSource/P34_05  = 'true' "!][!//
        [!VAR "WakeupSourceNum" = "num:i($WakeupSourceNum + 1)"!][!// 
    {
        PWRC_STBWAKEUPSOURCE_P34_05,
        PWRC_STBWAKEUPPINEDGE_[!"node:value(./McuStdbySettingConf/McuStdbyWakeupSource/P34_05Edge)"!]
    },
        [!ENDIF!][!//
        [!ENDCODE!]
    [!IF "$WakeupSourceNum = '0' "!][!//
        [!ERROR!][!//
            [101-00-09-ERROR]: In standby mode, it is necessary to set the wake-up source.
        [!ENDERROR!][!//
    [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!]
};

[!ENDIF!][!//
/* be used by setmode() */
static const Mcu_ModeConfigType Mcu_ModeConfig[] =
{
    {
        /* Valid mode  */
        [!"$ValidMode"!]U,
        /* parameter for standby mode */
        [!IF "$StandbyModeEnable = 1"!][!//
        &Mcu_StdbyCfg[0],
        /*Num of stanby wakeup source*/
        [!"$WakeupSourceNum"!]U
        [!ELSE!]
        NULL_PTR,
        0U
        [!ENDIF!][!//        
    }
};

[!SELECT "McuModuleConfiguration"!][!//
/***************************************************************************************************
*                        Mcu_ConfigSet Structure Description
****************************************************************************************************/
[!IF "variant:name() != ''"!][!//
const Mcu_ConfigType Mcu_ConfigSet_[!"variant:name()"!][MCU_CONFIG_COUNT] =
[!ELSE!][!//
const Mcu_ConfigType Mcu_ConfigSet[MCU_CONFIG_COUNT] =
[!ENDIF!][!//
{
    {
        /* ClockSettingPtr */
        &Mcu_ClockConfig[0],
        /* RamSettingPtr; */
        MCU_NUM_RAM_SECTORS,
        [!IF "num:i(count(./McuRamSectorSettingConf/*)) > 0"!][!//
        &Mcu_RamConfiguration[0],
        [!ELSE!]
        NULL_PTR,
        [!ENDIF!][!//
        /* GTMConfigPtr */
        &Mcu_GtmWrapperConfig[0],
        /* CMUConfigPtr */
        &Gtm_CMUConfig[0],
        /* TBUConfigPtr */
        [!IF "$GTM_TBU_EN = 1"!][!//
        &Mcu_TBUConfig[0],
        [!ELSE!]
        NULL_PTR,
        [!ENDIF!][!//
        /* GTMtriggerConfigPtr */
        [!IF "$McuGtmSourceNum != 0"!][!//
        &GtmTriggerConfig[0],
        [!ELSE!]
        NULL_PTR,
        /* ResetConfigPtr */
        [!ENDIF!][!//
[!IF "node:exists(./McuResetConfig)"!][!//
        &Mcu_ResetConfig[0],
[!ELSE!][!//
        NULL_PTR,
[!ENDIF!][!//
        /* ModeConfigPtr */
        &Mcu_ModeConfig[0],
        [!"$McuGtmSourceNum"!]U,
    }
};

[!ENDSELECT!][!//
/* #Violation: Mcu_PBcfg_c_REF_2 */
#define MCU_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Mcu_PBcfg_c_REF_1*/
#include "Mcu_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

