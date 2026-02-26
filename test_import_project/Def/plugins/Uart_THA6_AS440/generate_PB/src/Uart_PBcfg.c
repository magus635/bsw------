/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Uart_PBCfg.c
*
*   Platform             : AUTOSAR
*
*   Peripheral           : Uart
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*
*   Build Version        : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/*
*#Violation Summary
*#Uart_PBcfg_c_REF_1:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts 
* of the driver must be placed.
*
*#Uart_PBcfg_c_REF_2:MISRAC2012-Rule-11.4;
* Justification:Converting integers to object pointers to reduce register access complexity.
*
*#Uart_PBcfg_c_REF_3:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers
*
*/

/***************************************************************************************************
 *                               Include
 ***************************************************************************************************/
[!NOCODE!][!//
[!INCLUDE "Uart.m"!][!//
[!ENDNOCODE!][!//
[!INDENT "0"!][!//
#include "Uart.h"
#include "Uart_Cfg.h"
#include "tha6_cfg.h"
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
**                          External Function Declarations                                         **
****************************************************************************************************/
[!CALL "CG_GenerateChannelNotification"!][!//
/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
[!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
    [!VAR "UartChannelNumCorex" = "num:i(substring-after(text:split($UartChannelTotalNumCorex)[num:i($CoreIndex + 1)], ':'))"!][!/* CoreId:Num--->1:2 */!][!//
    [!IF "$UartChannelNumCorex != num:i(0)"!][!//
        /* #Violation: Uart_PBcfg_c_REF_3 */
        #define UART_START_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreIndex"!]_UNSPECIFIED
        /* #Violation: Uart_PBcfg_c_REF_1 */
        #include "Uart_MemMap.h"

        static const Uart_HwUnitConfigType Uart_HWUnitConfigSetCore[!"$CoreIndex"!][UART_MAX_CHANNEL_TO_CORE[!"$CoreIndex"!]] =
        {
            [!CALL "CG_GeneUartHwUnitConfig", "CoreID"="$CoreIndex"!][!//
        };

        /* Uart channel configuration parameters of Core[!"$CoreIndex"!] */
        static const Uart_ChannelConfigType Uart_ChannelConfigSetCore[!"$CoreIndex"!][UART_MAX_CHANNEL_TO_CORE[!"$CoreIndex"!]] =
        {
            [!CALL "CG_GeneUartChannelConfig", "CoreID"="$CoreIndex"!][!//
        };

        /* Uart channel number and configuration information in Core[!"$CoreIndex"!] */
        static const Uart_CoreConfigType Uart_ConfigSetCore[!"$CoreIndex"!] =
        {
            [!INDENT "4"!][!//
            /* Maximum number of the channels allocated to the core[!"$CoreIndex"!] */
            UART_MAX_CHANNEL_TO_CORE[!"$CoreIndex"!],
            /* Uart configuration information of core[!"$CoreIndex"!] */
            &Uart_ChannelConfigSetCore[!"$CoreIndex"!][0]
            [!ENDINDENT!][!//
        };
        /* #Violation: Uart_PBcfg_c_REF_3 */
        #define UART_STOP_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreIndex"!]_UNSPECIFIED
        /* #Violation: Uart_PBcfg_c_REF_1 */
        #include "Uart_MemMap.h"

    [!ENDIF!][!//
[!ENDFOR!][!//
/* #Violation: Uart_PBcfg_c_REF_3 */
#define UART_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Uart_PBcfg_c_REF_1 */
#include "Uart_MemMap.h"

/*
This array is used for mapping Uart Channel to the Core.
Array index is Uart channel -> array member is index of Corex[x=0~[!"ecu:get('Resource.NumOfCores')"!]]
*/
static const uint8 Uart_ChannelToCoreMap[UART_TOTAL_CFG_CHANNEL_NUM] =
{
    [!CALL "CG_GeneChannelToCoreMap"!][!//
};

/*
This array is used for mapping UART hardware unit to the Uart channel.
Array index is hardware unit -> array member is Uart channel
*/
static const uint8 Uart_HwToChannel[UART_MAX_HWUNIT_COUNT] =
{
    [!CALL "CG_GeneHwUnitNumToUartChannel"!][!//
};

/* Uart available ASI hardware unit mapping table.*/
static ASI_MODULE *const Uart_HwUnitMap[UART_MAX_HWUNIT_COUNT] =
{
    [!CALL "CG_GeneHwUnitMap"!][!//
};

/* Configuration parameters */
[!IF "variant:name() != ''"!][!//
const Uart_ConfigType Uart_ConfigSet_[!"variant:name()"!][UART_CONFIG_COUNT] =
[!ELSE!][!//
const Uart_ConfigType Uart_ConfigSet[UART_CONFIG_COUNT] =
[!ENDIF!][!//
{
    [!INDENT "4"!][!//
    {
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            [!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
                /* Uart Channels configuration of Core[!"$CoreIndex"!] */
                [!VAR "UartChannelNumCorex" = "num:i(substring-after(text:split($UartChannelTotalNumCorex)[num:i($CoreIndex + 1)], ':'))"!][!/* CoreId:Num */!][!//
                [!IF "$UartChannelNumCorex != num:i(0)"!][!//
                    &Uart_ConfigSetCore[!"$CoreIndex"!][!IF "num:i($CoreIndex) != num:i(ecu:get('Resource.NumOfCores') - 1)"!],[!ENDIF!]
                [!ELSE!][!//
                    NULL_PTR[!IF "num:i($CoreIndex) != num:i(ecu:get('Resource.NumOfCores') - 1)"!],[!ENDIF!]
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
        },
        /* Table for relationship between channel ID in specified core and UART channel ID */
        &Uart_ChannelToCoreMap[0],
        /* Table for relationship between hardware unit and logical UART channel ID */
        &Uart_HwToChannel[0],
        /* Uart available ASI hardware unit mapping table.*/
        &Uart_HwUnitMap[0]
        [!ENDINDENT!][!//
    }
    [!ENDINDENT!][!//
};
[!ENDINDENT!][!//
/* #Violation: Uart_PBcfg_c_REF_3 */
#define UART_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Uart_PBcfg_c_REF_1 */
#include "Uart_MemMap.h"
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
