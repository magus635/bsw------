/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Port_Cfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GPIO
*
*   brief                 : This file contains all configuration declarations of Port Driver
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
*
*#Port_Cfg_h_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*/
[!NOCODE!][!//
[!INCLUDE "Port.m"!][!//
[!ENDNOCODE!][!//
#ifndef PORT_CFG_H_
#define PORT_CFG_H_
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
/*  SWS_Port_00130:
    Port.h shall include Port_Cfg.h for the API pre-compiler switches and Std_Types.h
*/
#include "Std_Types.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION           ([!"num:i(CommonPublishedInformation/ArReleaseMajorVersion)"!]U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION           ([!"num:i(CommonPublishedInformation/ArReleaseMinorVersion)"!]U)
#define PORT_CFG_AR_RELEASE_REVISION_VERSION        ([!"num:i(CommonPublishedInformation/ArReleaseRevisionVersion)"!]U)

#define PORT_CFG_SW_MAJOR_VERSION                   ([!"num:i(CommonPublishedInformation/SwMajorVersion)"!]U)
#define PORT_CFG_SW_MINOR_VERSION                   ([!"num:i(CommonPublishedInformation/SwMinorVersion)"!]U)
#define PORT_CFG_SW_PATCH_VERSION                   ([!"num:i(CommonPublishedInformation/SwPatchVersion)"!]U)

#define PORT_CFG_VENDOR_ID                          ([!"num:i(CommonPublishedInformation/VendorId)"!]U) /* 0x[!"substring-after(text:toupper(num:inttohex(CommonPublishedInformation/VendorId)), 'X')"!] */
#define PORT_CFG_MODULE_ID                          ([!"num:i(CommonPublishedInformation/ModuleId)"!]U) /* 0x[!"substring-after(text:toupper(num:inttohex(CommonPublishedInformation/ModuleId)), 'X')"!] */

/*
[!WS"2"!]Configuration: PORT_DEV_ERROR_DETECT
- if Selected, DET is Enabled
- if Deselected, DET is Disabled
*/
#define PORT_DEV_ERROR_DETECT                       [!IF "PortGeneral/PortDevErrorDetect = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!//

/*
[!WS"2"!]Configuration: PORT_SAFETY_ENABLE
- if Selected, Safety check is Enabled
- if Deselected, Safety check is Disabled
*/
#define PORT_SAFETY_ENABLE                          [!IF "PortGeneral/PortSafetyErrorDetect = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!//

/*
[!WS"2"!]Configuration: PORT_VERSION_INFO_API
- if Selected,  Function Port_GetVersionInfo is available
- if Deselected, Function Port_GetVersionInfo is not available
*/
#define PORT_VERSION_INFO_API                       [!IF "PortGeneral/PortVersionInfoApi = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!//

/*
[!WS"2"!]Configuration: PORT_SET_PIN_MODE_API
- if Selected,  Function Port_SetPinMode is available
- if Deselected, Function Port_SetPinMode is not available
*/
#define PORT_SET_PIN_MODE_API                       [!IF "PortGeneral/PortSetPinModeApi = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!//


/*  SWS_Port_00086:
[!WS"4"!]The function Port_SetPinDirection shall only be available to the user if the pre-compile
[!WS"4"!]parameter PortSetPinDirectionApi is set to TRUE. If set to FALSE, the function
[!WS"4"!]Port_SetPinDirection is not available.
[!WS"2"!]Configuration: PORT_SET_PIN_DIRECTION_API
- if Selected,  Function Port_SetPinDirection is available
- if Deselected, Function Port_SetPinDirection is not available
*/
#define PORT_SET_PIN_DIRECTION_API                  [!IF "PortGeneral/PortSetPinDirectionApi = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!//

/*
[!WS"2"!]Configuration: PORT_LVDS_FUNCTION_ENABLE
- if Selected,  LVDS function is enabled.
- if Deselected, LVDS function is disabled
*/
#define PORT_LVDS_FUNCTION_ENABLE                   [!IF "PortGeneral/PortLvdsEnable = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/* Definition to specify the available Port total number */
#define PORT_AVAILABEL_TOTAL_NUMBER                 ([!"num:i(ecu:get('Port.AvailablePortsTotalNumber'))"!]U)

/* Definition to specify the available Alternate function register total number */
#define PORT_RXMUX_REG_TOTAL_NUMBER                 ([!"$RxMuxTotalNum"!]U)

/* Maximum Port Number */
#define PORT_MAX_NUMBER                             ([!"num:i(ecu:get('Port.MaxAvailablePortID')+1)"!]U)

/* Maximum Pin Number */
#define PIN_MAX_NUMBER                              ([!"num:i(ecu:get('Port.MaxAvailablePinID')+1)"!]U)

/* Total number of CTRx registers */
#define PORT_CTRX_NUMBER                            (4U)

/* Total number of DSRx registers */
#define PORT_DSRX_NUMBER                            (2U)

/* Total number of port configuration files */
[!NOCODE!][!//
[!VAR "ConfigCount" = "num:i(count(PortConfigSet/*))"!][!//
[!CODE!][!//
#define PORT_CONFIG_COUNT                           ([!"num:i($ConfigCount)"!]U)
[!ENDCODE!][!//
[!ENDNOCODE!][!//

[!CALL "CG_GetPortPinSymbolicName"!][!//

[!CALL "CG_GetPortPinRXMUXSymbolicName"!][!//
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

#endif /* PORT_CFG_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

