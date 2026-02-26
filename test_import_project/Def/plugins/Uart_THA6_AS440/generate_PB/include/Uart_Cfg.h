/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Uart_Cfg.h
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


/***************************************************************************************************/
[!NOCODE!][!//
[!INCLUDE "Uart.m"!][!//
[!ENDNOCODE!][!//

/***************************************************************************************************/
#ifndef UART_CFG_H_
#define UART_CFG_H_
/****************************************************************************************************
*                            Global Macro Definitions
****************************************************************************************************/
/***************************************************************************************************
*                               Version Information
***************************************************************************************************/
#define UART_CFG_AR_RELEASE_MAJOR_VERSION        ([!"num:i(CommonPublishedInformation/ArReleaseMajorVersion)"!]U)
#define UART_CFG_AR_RELEASE_MINOR_VERSION        ([!"num:i(CommonPublishedInformation/ArReleaseMinorVersion)"!]U)
#define UART_CFG_AR_RELEASE_REVISION_VERSION     ([!"num:i(CommonPublishedInformation/ArReleaseRevisionVersion)"!]U)

#define UART_CFG_SW_MAJOR_VERSION                ([!"num:i(CommonPublishedInformation/SwMajorVersion)"!]U)
#define UART_CFG_SW_MINOR_VERSION                ([!"num:i(CommonPublishedInformation/SwMinorVersion)"!]U)
#define UART_CFG_SW_PATCH_VERSION                ([!"num:i(CommonPublishedInformation/SwPatchVersion)"!]U)


#define UART_CFG_VENDOR_ID                       ([!"num:i(CommonPublishedInformation/VendorId)"!]U) /* 0x[!"substring-after(text:toupper(num:inttohex(CommonPublishedInformation/VendorId)), 'X')"!] */
#define UART_CFG_MODULE_ID                       ([!"num:i(CommonPublishedInformation/ModuleId)"!]U) /* 0x[!"substring-after(text:toupper(num:inttohex(CommonPublishedInformation/ModuleId)), 'X')"!] */


/****************************************************************************************************
**                           Diagnostic report settings                                            **
****************************************************************************************************/
/*
Configuration: UART_DEV_ERROR_DETECT
- if Selected, DET is Enabled
- if Deselected, DET is Disabled
*/
#define UART_DEV_ERROR_DETECT                    [!IF "UartGeneral/UartDevErrorDetect = 'true'"!](STD_ON) [!ELSE!](STD_OFF)[!ENDIF!]
/*
Configuration: UART_VERSION_INFO_API
- if Selected, Function Uart_GetVersionInfo is Enabled
- if Deselected, Function Uart_GetVersionInfo is Enabled
*/
#define UART_VERSION_INFO_API                    [!IF "UartGeneral/UartVersionInfoApi = 'true'"!](STD_ON) [!ELSE!](STD_OFF)[!ENDIF!]
/****************************************************************************************************
**                               interrupt settings                                                **
****************************************************************************************************/
/*
Configuration: UART_TIMEOUT_DURATION
 Specifies duration of UART channel timeout.
*/
#define UART_TIMEOUT_DURATION                    ([!"num:i(UartGeneral/UartTimeoutDuration)"!]U)

/*
Configuration: UART_CONFIG_COUNT
 Defines the total number of UART Config infomation.
*/
#define UART_CONFIG_COUNT                        (1U)

/*
Configuration: UART_MAX_HWUNIT_COUNT
 Defines the total number of UART HwUnit.
*/
#define UART_MAX_HWUNIT_COUNT                    ([!"num:i(ecu:get('Asi.MaxHwUnit'))"!]U)

/*
Configuration: UART_TOTAL_CFG_CHANNEL_NUM
 Define the total number of UART channels.
*/
#define UART_TOTAL_CFG_CHANNEL_NUM               ([!"num:i(count(UartGlobalConfig/UartChannel/*))"!]U)

/*
Configuration: UART_MAX_CHANNEL_TO_COREx
 Defines the total number of channels mapped to Corex.
*/
[!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
[!VAR "UartChannelNumCorex" = "num:i(substring-after(text:split($UartChannelTotalNumCorex)[num:i($CoreIndex + 1)], ':'))"!][!/* CoreId:Num--->1:2 */!][!//
#define UART_MAX_CHANNEL_TO_CORE[!"$CoreIndex"!]    [!WS "12"!]([!"$UartChannelNumCorex"!]U)
[!ENDFOR!][!//

[!CALL "CG_GenerateInterruptEnableMacro"!][!//
/*
Macro definition: UART Channel name
 Generate the macro definition for UART Channel name.
*/
[!CALL "CG_GeneUartChannelIdMacro"!]

/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/

#endif /* _UART_CFG_H_ */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/