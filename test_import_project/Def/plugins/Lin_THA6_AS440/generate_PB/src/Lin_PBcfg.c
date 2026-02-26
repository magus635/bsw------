/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Lin_PBCfg.c
*
*   Platform             : AUTOSAR
*
*   Peripheral           : ASI
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
* 
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/*
*#Violation Summary
*#Lin_PBcfg_c_REF_1:MISRAC2012-Rule-20.1;
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the 
* driver must be placed.
*
*#Lin_PBcfg_c_REF_2:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*/

[!NOCODE!][!//
[!INCLUDE "Lin.m"!][!//
[!ENDNOCODE!][!//
/***************************************************************************************************
 *                               Include
 ***************************************************************************************************/
#include "Lin_Cfg.h"
#include "Lin_GeneralTypes.h"
#include "Lin.h"

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/
[!INDENT "0"!][!//
[!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
    [!INDENT "0"!][!//
        [!CALL "CG_GetVauleInStringDictByKey", "StringDict" = "$G_LinChannelMappedCoreIdDict", "Key" = "$CoreIndex"!][!//
        [!VAR "LinChannelNumberInCorex" = "$CG_GetVauleInStringDictByKey_ReturnObject"!][!//
        [!VAR "LinTotalHWUnitNum" = "num:i($LinChannelNumberInCorex)"!][!//
    [!ENDINDENT!][!//
    [!IF "num:i($LinTotalHWUnitNum) != '0'"!][!//
    /* Lin Channel(s) configuration informations which mapped to Core[!"$CoreIndex"!] */
    /* #Violation: Lin_PBcfg_c_REF_2 */
    #define LIN_START_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreIndex"!]_UNSPECIFIED
    /* #Violation: Lin_PBcfg_c_REF_1 */ 
    #include "Lin_MemMap.h"

         /* Lin HwUnit configuration parameters of Core[!"$CoreIndex"!] */
        static const Lin_HwUnitConfigType Lin_HWUnitConfigSetCore[!"$CoreIndex"!][LIN_MAX_CHANNEL_TO_CORE[!"$CoreIndex"!]] =
        {
            [!CALL "CG_GeneLinHwUnitConfig", "CoreID"="$CoreIndex"!][!//
        };

       /* Lin channel configuration parameters of Core[!"$CoreIndex"!] */
        static const Lin_ChannelConfigType Lin_ChannelConfigSetCore[!"$CoreIndex"!][LIN_MAX_CHANNEL_TO_CORE[!"$CoreIndex"!]] =
        {
            [!CALL "CG_GeneLinChannelConfig", "CoreID"="$CoreIndex"!][!//
        };

        /* Lin channel number and configuration information in Core[!"$CoreIndex"!] */
        static const Lin_CoreConfigType Lin_ConfigSetCore[!"$CoreIndex"!] =
        {
            [!INDENT "4"!][!//
            /* Maximum number of the channels allocated to the core[!"$CoreIndex"!] */
            LIN_MAX_CHANNEL_TO_CORE[!"$CoreIndex"!],
            /* Lin configuration information of core[!"$CoreIndex"!] */
            &Lin_ChannelConfigSetCore[!"$CoreIndex"!][0]
            [!ENDINDENT!][!//
        };
        /* #Violation: Lin_PBcfg_c_REF_2 */
        #define LIN_STOP_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreIndex"!]_UNSPECIFIED
        /* #Violation: Lin_PBcfg_c_REF_1 */ 
        #include "Lin_MemMap.h"
    [!ENDIF!][!//
[!ENDFOR!][!//
    /* #Violation: Lin_PBcfg_c_REF_2 */
    #define LIN_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
    /* #Violation: Lin_PBcfg_c_REF_1 */ 
    #include "Lin_MemMap.h"
    /* Shared configuration const data for all cores. */

/* 
This array is used for mapping Lin Channel to the Core. 
Array index is Lin channel -> array member is index of Lin_ChannelConfigSetCorex[x=0~4]
*/
static const uint8 Lin_ChannelToCoreMap[LIN_TOTAL_CFG_CHANNEL_NUM] =
{
    [!CALL "CG_GeneChannelToCoreMap"!][!//
};

/* Relationship between ASI hardware unit and LIN channel */
/* 
This array is used for mapping LIN hardware unit to the Lin channel. 
Array index is hardware unit -> array member is Lin channel
*/
static const uint8 Lin_HwToChannel[LIN_MAX_HWUNIT_COUNT] =
{
    [!CALL "CG_GeneHwUnitNumToLinChannel"!][!//
};

/* #Violation: Lin_PBcfg_c_REF_2 */
#define LIN_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Lin_PBcfg_c_REF_1 */ 
#include "Lin_MemMap.h"
/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
/* #Violation: Lin_PBcfg_c_REF_2 */
#define LIN_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Lin_PBcfg_c_REF_1 */ 
#include "Lin_MemMap.h"

/* Configuration parameters */
[!IF "variant:name() != ''"!][!//
const Lin_ConfigType Lin_ConfigSet_[!"variant:name()"!][LIN_CONFIG_COUNT] =
[!ELSE!][!//
const Lin_ConfigType Lin_ConfigSet[LIN_CONFIG_COUNT] =  
[!ENDIF!][!//
{
    [!INDENT "4"!][!//
    {
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            [!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
                [!CALL "CG_GetVauleInStringDictByKey", "StringDict" = "$G_LinChannelMappedCoreIdDict", "Key" = "$CoreIndex"!][!//
                [!VAR "LinChannelNumberToCoreX" = "$CG_GetVauleInStringDictByKey_ReturnObject"!][!//
                /* LIN channels configuration of core[!"$CoreIndex"!] */
                [!IF "num:i($LinChannelNumberToCoreX) != '0'"!][!//
                &Lin_ConfigSetCore[!"$CoreIndex"!][!IF "$CoreIndex != num:i(ecu:get('Resource.NumOfCores') - 1)"!],[!ENDIF!]
                [!ELSE!][!//
                NULL_PTR[!IF "$LinChannelNumberToCoreX != num:i(ecu:get('Resource.NumOfCores') - 1)"!],[!ENDIF!]
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
        },
        /* Table for relationship between channel ID in specified core and LIN channel ID */
        &Lin_ChannelToCoreMap[0],
        /* Table for relationship between hardware unit and logical LIN channel ID */
        &Lin_HwToChannel[0]
        [!ENDINDENT!][!//
    }
    [!ENDINDENT!][!//
};

[!ENDINDENT!][!//
/* #Violation: Lin_PBcfg_c_REF_2 */
#define LIN_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Lin_PBcfg_c_REF_1 */ 
#include "Lin_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
