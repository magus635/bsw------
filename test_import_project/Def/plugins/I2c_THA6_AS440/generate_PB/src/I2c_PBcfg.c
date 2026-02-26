/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : I2c_PBCfg.c
*
*   Platform             : AUTOSAR
*
*   Peripheral           : I2C
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
* 
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright /(c) 2021,Beijing Tongxin Microelectroics co.Ltd
*
****************************************************************************************************/

/*
*#Violation Summary
*
*#I2c_PBcfg_c_REF_1:MISRAC2012-Rule-20.1;
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#I2c_PBcfg_c_REF_2:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*/

[!NOCODE!][!//
[!INCLUDE "I2c.m"!][!//
[!ENDNOCODE!][!//
/***************************************************************************************************
 *                               Include
 ***************************************************************************************************/
#include "I2c_Cfg.h"
#include "I2c_GeneralTypes.h"
#include "I2c.h"
#include "i2c_hal.h"

/****************************************************************************************************
**                          Configurations                                                         **
****************************************************************************************************/
/* Notification Function Declarations */
[!INDENT "0"!][!//
[!LOOP "I2cGlobalConfig/I2cChannel/*"!][!//
    [!IF "./I2cNotification = 'true' and 
          node:exists(I2cPacketEndNotification) and
          node:value(I2cPacketEndNotification) != 'NULL_PTR' and
          node:value(I2cPacketEndNotification) != ''"!][!//
        extern void [!"I2cPacketEndNotification"!](I2c_ChannelErrorType ErrorId);
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDINDENT!][!//
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
    [!VAR "I2cChannelNumCorex" = "num:i(substring-after(text:split($I2cChannelTotalNumCorex)[num:i($CoreIndex + 1)], ':'))"!][!/* CoreId:Num--->1:2 */!][!//
    [!IF "num:i($I2cChannelNumCorex) != '0'"!][!//
    /* #Violation: I2c_PBcfg_c_REF_2 */
    #define I2C_START_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreIndex"!]_UNSPECIFIED
    /* #Violation: I2c_PBcfg_c_REF_1 */ 
    #include "I2c_MemMap.h"

         /* I2c HwUnit configuration parameters of Core[!"$CoreIndex"!] */
        static const I2c_InitConfigType I2c_HWUnitConfigSetCore[!"$CoreIndex"!][I2C_MAX_CHANNEL_TO_CORE[!"$CoreIndex"!]] =
        {
            [!CALL "CG_GeneI2cHwUnitConfig", "CoreID"="$CoreIndex"!][!//
        };

       /* I2c channel configuration parameters of Core[!"$CoreIndex"!] */
        static const I2c_ChannelConfigType I2c_ChannelConfigSetCore[!"$CoreIndex"!][I2C_MAX_CHANNEL_TO_CORE[!"$CoreIndex"!]] =
        {
            [!CALL "CG_GeneI2cChannelConfig", "CoreID"="$CoreIndex"!][!//
        };

        /* I2c channel number and configuration information in Core[!"$CoreIndex"!] */
        static const I2c_InitCoreConfigType I2c_ConfigSetCore[!"$CoreIndex"!] =
        {
            [!INDENT "4"!][!//
            /* I2c configuration information of core[!"$CoreIndex"!] */
            &I2c_ChannelConfigSetCore[!"$CoreIndex"!][0],
            /* Maximum number of the channels allocated to the core[!"$CoreIndex"!] */
            I2C_MAX_CHANNEL_TO_CORE[!"$CoreIndex"!]
            [!ENDINDENT!][!//
        };

    /* #Violation: I2c_PBcfg_c_REF_2 */
    #define I2C_STOP_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreIndex"!]_UNSPECIFIED
    /* #Violation: I2c_PBcfg_c_REF_1 */ 
    #include "I2c_MemMap.h"
    [!ENDIF!][!//
[!ENDFOR!][!//

/* #Violation: I2c_PBcfg_c_REF_2 */
#define I2C_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: I2c_PBcfg_c_REF_1 */ 
#include "I2c_MemMap.h"

/* 
This array is used for mapping I2c Channel to the Core. 
Array index is I2c channel -> array member is index of I2c_ChannelConfigSetCorex[x=0~1]
*/
static const uint8 I2c_ChannelToCoreMap[I2C_TOTAL_CFG_CHANNEL_NUM] =
{
    [!CALL "CG_GeneChannelToCoreMap"!][!//
};

/* 
This array is used for mapping I2c hardware unit to the I2c channel. 
Array index is hardware unit -> array member is I2c channel
*/
static const uint8 I2c_HwToChannel[I2C_MAX_HWUNIT_COUNT] =
{
    [!CALL "CG_GeneHwUnitNumToI2cChannel"!][!//
};

/* #Violation: I2c_PBcfg_c_REF_2 */
#define I2C_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: I2c_PBcfg_c_REF_1 */ 
#include "I2c_MemMap.h"
/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
/* #Violation: I2c_PBcfg_c_REF_2 */
#define I2C_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: I2c_PBcfg_c_REF_1 */ 
#include "I2c_MemMap.h"

[!IF "variant:name() != ''"!][!//
const I2c_ConfigType I2c_ConfigSet_[!"variant:name()"!][I2C_CONFIG_COUNT] =
[!ELSE!][!//
/* Configuration parameters */
const I2c_ConfigType I2c_ConfigSet[I2C_CONFIG_COUNT] =
[!ENDIF!][!//
{
    [!INDENT "4"!][!//
    {
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            [!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
                [!VAR "I2cChannelNumCorex" = "num:i(substring-after(text:split($I2cChannelTotalNumCorex)[num:i($CoreIndex + 1)], ':'))"!][!/* CoreId:Num--->1:2 */!][!//
                /* I2C channels configuration of Core[!"$CoreIndex"!] */
                [!IF "$I2cChannelNumCorex != num:i(0)"!][!//
                    &I2c_ConfigSetCore[!"$CoreIndex"!][!IF "num:i($CoreIndex) != num:i(ecu:get('Resource.NumOfCores') - 1)"!],[!ENDIF!]
                [!ELSE!][!//
                    NULL_PTR[!IF "num:i($CoreIndex) != num:i(ecu:get('Resource.NumOfCores') - 1)"!],[!ENDIF!]
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
        },
        /* Table for relationship between channel ID in specified core and I2c channel ID */
        &I2c_ChannelToCoreMap[0],
        /* Table for relationship between hardware unit and logical I2c channel ID */
        &I2c_HwToChannel[0]
        [!ENDINDENT!][!//
    }
    [!ENDINDENT!][!//
};

[!ENDINDENT!][!//

/* #Violation: I2c_PBcfg_c_REF_2 */
#define I2C_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: I2c_PBcfg_c_REF_1 */
#include "I2c_MemMap.h"
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
