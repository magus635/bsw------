/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Intc_PBCfg.c
*
*   Platform             : AUTOSAR
*
*   Peripheral           : Intc
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*
*   Build Version        : Cortex-R52+/THA6xxx
*
*  Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/*
*#Violation Summary
*
*#Intc_PBcfg_c_REF_1:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*#Intc_PBcfg_c_REF_2:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts 
* of the driver must be placed.
*
*#Intc_PBcfg_c_REF_3:MISRAC2012-Dir-1.1;
* Justification:Compiler can handle more than 4095 macro identifiers.
*
*/

[!NOCODE!][!//
[!INCLUDE "Intc_Cfg_Common.m"!][!//
[!ENDNOCODE!][!//
/***************************************************************************************************
 *                               Include
 ***************************************************************************************************/
/* #Violation: Intc_PBcfg_c_REF_3 */
#include "Intc_Irq.h"
#include "Intc.h"
#include "Mcall.h"

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
[!CODE!][!//
[!INDENT "0"!][!//
[!FOR "Var_CoreIdx" = "num:i(0)" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
    [!IF "num:i($Var_CoreIdx) = num:i(0)"!][!//
        [!VAR "Var_Temp_IntSrcNum" = "$Var_IntSrcNumCore0"!][!//
    [!ELSEIF "num:i($Var_CoreIdx) = num:i(1)"!][!//
        [!VAR "Var_Temp_IntSrcNum" = "$Var_IntSrcNumCore1"!][!//
    [!ELSEIF "num:i($Var_CoreIdx) = num:i(2)"!][!//
        [!VAR "Var_Temp_IntSrcNum" = "$Var_IntSrcNumCore2"!][!//
    [!ELSEIF "num:i($Var_CoreIdx) = num:i(3)"!][!//
        [!VAR "Var_Temp_IntSrcNum" = "$Var_IntSrcNumCore3"!][!//
    [!ENDIF!][!//
    [!IF "num:i($Var_Temp_IntSrcNum) != 0"!][!//

/* Configuration informations which mapped to Core[!"$Var_CoreIdx"!] */
/* #Violation: Intc_PBcfg_c_REF_1 */
#define INTC_START_SEC_CONFIG_DATA_ASIL_D_CORE[!"$Var_CoreIdx"!]_UNSPECIFIED
/* #Violation: Intc_PBcfg_c_REF_2 */
#include "Intc_MemMap.h"

/* Iterrupt(SGI ,PPI and SPI) sources configuration list of Core[!"num:i($Var_CoreIdx)"!] */
static const Intc_IntSrcConfigType
[!INDENT "20"!][!//
                    Intc_IntSrcConfigSetCore[!"num:i($Var_CoreIdx)"!][INTC_CFG_INTSRC_NUM_CORE[!"num:i($Var_CoreIdx)"!]] = 
[!ENDINDENT!][!//
{
[!INDENT "4"!][!//
    [!VAR "Var_IntSrcCnt" = "num:i(0)"!][!//
    [!LOOP "IntcConfigSet/IntcContainer/*"!][!//
        [!LOOP "node:order(IntcIntSrcSubClassContainer/*, 'IntcIntSrcSubClassId')"!][!//
            [!LOOP "node:order(IntcIntSrcContainer/*, 'IntcIntSrcId')"!][!//
                [!IF "(IntcIntSrcEnable = 'true') and (text:split(IntcIntSrcCoreMapping, 'CORE')[1] = num:i($Var_CoreIdx))"!][!//
                    [!IF "IntcIntSrcCategory = 'CAT1'"!][!//
                        [!VAR "Var_IntSrcCnt" = "num:i($Var_IntSrcCnt + 1)"!][!//
                        /* Interrupt source: [!"node:name(.)"!] - [!"node:value(./IntcIntSrcName)"!] */
                        {
                        [!INDENT "8"!][!//
                            [!IF "(text:contains(ecu:list('Intc.CoreFixedIntClass'), ../../../../IntcIntSrcClass))"!][!//
                                [!CALL "CG_GenIntConfigurationPara", "Para_IntType" = "'InternalInt'"!][!//
                            [!ELSE!][!//
                                [!CALL "CG_GenIntConfigurationPara", "Para_IntType" = "'ExternalInt'"!][!//
                            [!ENDIF!][!//
                        [!ENDINDENT!][!//
                        }[!//
                        [!IF "$Var_IntSrcCnt < $Var_Temp_IntSrcNum"!][!//
                            ,
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
[!ENDINDENT!]
};

/* #Violation: Intc_PBcfg_c_REF_1 */
#define INTC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE[!"$Var_CoreIdx"!]_UNSPECIFIED
/* #Violation: Intc_PBcfg_c_REF_2 */
#include "Intc_MemMap.h"
    [!ENDIF!][!//
[!ENDFOR!][!//
[!ENDINDENT!][!//
[!ENDCODE!][!//

/* #Violation: Intc_PBcfg_c_REF_1 */
#define INTC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Intc_PBcfg_c_REF_2 */
#include "Intc_MemMap.h"

[!CODE!][!//
[!INDENT "0"!][!//
/* Intc configuration set parameters */
[!IF "variant:name() != ''"!][!//
const Intc_ConfigType Intc_ConfigSet_[!"variant:name()"!][INTC_CONFIGSET_CNT] =
[!ELSE!][!//
const Intc_ConfigType Intc_ConfigSet[INTC_CONFIGSET_CNT] =
[!ENDIF!][!//
{
[!INDENT "4"!][!//
    {
    [!INDENT "8"!][!//
        {
    [!INDENT "12"!][!//
    [!FOR "Var_CoreIdx" = "num:i(0)" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
        {
            [!INDENT "16"!][!//
            /* Total interrupt in core[!"$Var_CoreIdx"!] */
            INTC_CFG_INTSRC_NUM_CORE[!"num:i($Var_CoreIdx)"!],
            [!IF "num:i($Var_CoreIdx) = num:i(0)"!][!//
                [!VAR "Var_Temp_IntSrcNum" = "$Var_IntSrcNumCore0"!][!//
            [!ELSEIF "num:i($Var_CoreIdx) = num:i(1)"!][!//
                [!VAR "Var_Temp_IntSrcNum" = "$Var_IntSrcNumCore1"!][!//
            [!ELSEIF "num:i($Var_CoreIdx) = num:i(2)"!][!//
                [!VAR "Var_Temp_IntSrcNum" = "$Var_IntSrcNumCore2"!][!//
            [!ELSEIF "num:i($Var_CoreIdx) = num:i(3)"!][!//
                [!VAR "Var_Temp_IntSrcNum" = "$Var_IntSrcNumCore3"!][!//
            [!ENDIF!][!//
            [!IF "num:i($Var_Temp_IntSrcNum) != 0"!][!//
                /* Interrupt Configuration set */
                &Intc_IntSrcConfigSetCore[!"num:i($Var_CoreIdx)"!][0]
            [!ELSE!][!//
                /* No interrupt configured in core[!"$Var_CoreIdx"!] */
                NULL_PTR
            [!ENDIF!][!//
            [!ENDINDENT!][!//
        }[!//
        [!IF "num:i($Var_CoreIdx) < num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
        ,
        [!ELSE!][!//
            [!/* Line feed */!]
        [!ENDIF!][!//
    [!ENDFOR!][!//
    [!ENDINDENT!][!//
        }
    [!ENDINDENT!][!//
    }
[!ENDINDENT!][!//
};
[!ENDINDENT!][!//
[!ENDCODE!][!//

/* #Violation: Intc_PBcfg_c_REF_1 */
#define INTC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Intc_PBcfg_c_REF_2 */
#include "Intc_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
