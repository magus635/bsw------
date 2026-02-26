/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Dio_PBCfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GPIO
*
*   brief                 : This file contains all configurations of Dio Driver
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
*#Dio_PBcfg_c_REF_1:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts 
* of the driver must be placed.
*
*#Dio_PBcfg_c_REF_2:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers
*/

[!//
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Dio')"!][!//
[!NOCODE!][!//
[!/* Include Code Generator Macros */!][!//
[!INCLUDE "Dio.m"!][!//
[!ENDNOCODE!][!//

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Dio.h"
#include "Dio_Cfg.h"

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
/* #Violation: Dio_PBcfg_c_REF_2 */
#define DIO_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Dio_MemMap.h"
[!VAR "NumOfGroups" = "num:i(count(DioConfig/DioPort/*/DioChannelGroup/*))"!][!//
static const Dio_PortChannelIdType Dio_PortChannelCfgData[DIO_AVAILABEL_PORT_TOTAL_NUMBER]=
{
    [!CALL "CG_GetDioChannelCfgData"!][!//
};

[!IF "$NumOfGroups != num:i(0)"!][!//
static const Dio_ChannelGroupType Dio_GroupConfigData[DIO_CHANNELGROUPCOUNT]=
{
    [!CALL "Dio_CG_GetDioChannelGroupDefinition"!][!//
};
[!ENDIF!][!//

static const uint8 Dio_AvailablePortIndexMap[DIO_MAX_PORT_NUMBER] =
{
    [!CALL "CG_GetAvailablePortIndex"!][!//
};

static const uint16 Dio_AvailablePortPins[DIO_AVAILABEL_PORT_TOTAL_NUMBER] =
{
    [!CALL "CG_GetAvailablePortPins"!][!//
};

const Dio_ConfigType Dio_ConfigSet =
{
    [!INDENT "4"!][!//
        /* DIO single channel configuration parameters */
        &Dio_PortChannelCfgData[0],
        /* DIO channel group configuration parameters set */
        [!IF "$NumOfGroups != num:i(0)"!][!//
            &Dio_GroupConfigData[0],
        [!ELSE!][!//
                NULL_PTR,
        [!ENDIF!][!//
        /* The Port index from available Port */
        &Dio_AvailablePortIndexMap[0],
        /* The PIN available for each port */
        &Dio_AvailablePortPins[0]
    [!ENDINDENT!][!//
};
/* #Violation: Dio_PBcfg_c_REF_2 */
#define DIO_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Dio_PBcfg_c_REF_1 */
#include "Dio_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

[!ENDSELECT!][!//
