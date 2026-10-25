/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Dio_Cfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GPIO
*
*   brief                 : This file contains all configuration declarations of Dio Driver
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
*#Dio_Cfg_h_REF_1:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers
*
*/

#ifndef DIO_CFG_H_
#define DIO_CFG_H_


#include "Dio_GeneralTypes.h"

[!/* Include Code Generator Macros */!][!//
[!NOCODE!][!//
[!INCLUDE "Dio.m"!][!//
[!ENDNOCODE!][!//


[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Dio')"!][!//
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#define DIO_CFG_AR_RELEASE_MAJOR_VERSION         ([!"num:i(CommonPublishedInformation/ArReleaseMajorVersion)"!]U)
#define DIO_CFG_AR_RELEASE_MINOR_VERSION         ([!"num:i(CommonPublishedInformation/ArReleaseMinorVersion)"!]U)
#define DIO_CFG_AR_RELEASE_REVISION_VERSION      ([!"num:i(CommonPublishedInformation/ArReleaseRevisionVersion)"!]U)

#define DIO_CFG_SW_MAJOR_VERSION                 ([!"num:i(CommonPublishedInformation/SwMajorVersion)"!]U)
#define DIO_CFG_SW_MINOR_VERSION                 ([!"num:i(CommonPublishedInformation/SwMinorVersion)"!]U)
#define DIO_CFG_SW_PATCH_VERSION                 ([!"num:i(CommonPublishedInformation/SwPatchVersion)"!]U)

#define DIO_CFG_VENDOR_ID                        ([!"num:i(CommonPublishedInformation/VendorId)"!]U) /*([!"text:toupper(num:inttohex(CommonPublishedInformation/VendorId))"!])*/
#define DIO_CFG_MODULE_ID                        ([!"num:i(CommonPublishedInformation/ModuleId)"!]U) /*([!"text:toupper(num:inttohex(CommonPublishedInformation/ModuleId))"!])*/

/*
Configuration: DIO_DEV_ERROR_DETECT
- if Selected, DET is Enabled 
- if Deselected, DET is Disabled 
*/
#define DIO_DEV_ERROR_DETECT                     [!IF "DioGeneral/DioDevErrorDetect = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: DIO_VERSION_INFO_API 
- if Selected,  Function Dio_GetVersionInfo is available  
- if Deselected, Function Dio_GetVersionInfo is not available 
*/
#define DIO_VERSION_INFO_API                     [!IF "DioGeneral/DioVersionInfoApi = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: DIO_FLIP_CHANNEL_API 
- if Selected,  Function DioFlipChannelApi is available  
- if Deselected, Function DioFlipChannelApi is not available 
*/     
#define DIO_FLIP_CHANNEL_API                     [!IF "DioGeneral/DioFlipChannelApi = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

#define DIO_MASKED_WRITE_PORT_API                [!IF "DioGeneral/DioMaskedWritePortApi = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]


/* Definition to specify the available Port total number */
#define DIO_AVAILABEL_PORT_TOTAL_NUMBER          ([!"num:i(ecu:get('Port.AvailablePortsTotalNumber'))"!]U)

/* Maximum Port Number(Hex) */
#define DIO_MAX_PORT_NUMBER                      ([!"num:i(ecu:get('Port.MaxAvailablePortID')+1)"!]U)

#define DIO_PIN_MAX_NUMBER                       ([!"num:i(ecu:get('Port.MaxAvailablePinID')+1)"!]U)

/* Macro to define the maximum portPinId available */
#define DIO_MAX_AVAILABEL_PORT_PIN_ID            ([!"text:toupper(num:inttohex(bit:or(bit:shl(num:i(ecu:get('Port.MaxAvailablePortID')),num:i(4)),num:max(text:grep(text:split(ecu:get(concat('Port.Port' , ecu:get('Port.MaxAvailablePortID'), '_AvailablePins')), '_'), '[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]')))))"!]U)

/* Macro to define the Num of channel groups configured */
#define DIO_CHANNELGROUPCOUNT                   ([!"num:i(count(DioConfig/DioPort/*/DioChannelGroup/*))"!]U)

/* Definition to specify the ports that are read only ports on the
   microcontroller
   Bit value = 0 implies the port readable/writable
   Bit value = 1 implies the port is read only port
   Bit 0 is for Port 0, Bit 1 is for Port 1, ... , Bit 31 is for Port 31 
*/
[!CALL "Dio_CG_GetReadOnlyPorts00to31"!][!//
/* Definition to specify the ports that are read only ports on the
   microcontroller
   Bit value = 0 implies the port readable/writable
   Bit value = 1 implies the port is read only port
   Bit 0 is for Port 32, Bit 1 is for Port 33, ... , Bit 9 is for Port 41 
*/
[!CALL "Dio_CG_GetReadOnlyPorts32to63"!][!//

/*
                       Symbolic names for Channels
*/
[!FOR "PortNumber" = "num:i(0)" TO "ecu:get('Port.MaxAvailablePortID')"!][!//
[!//
[!IF "contains(ecu:get('Port.AvailablePortsID'),concat('_',$PortNumber,'_'))"!][!//
[!CALL "Dio_CG_GetDioChannelSymbolicNames","PortNumber" = "$PortNumber"!][!//
[!ENDIF!][!//
[!//
[!ENDFOR!][!//
/*
                      Symbolic names for DIO ports
*/
[!CALL "Dio_CG_GetDioPortSymbolicNames"!][!//

/*
      User Defined Symbolic Names for the DIO Ports, Channels & Channel Groups
*/
[!CALL "CG_GetUserDefinedSymbolicNames"!][!//
[!ENDSELECT!][!//
/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/
extern const Dio_ConfigType Dio_ConfigSet;
/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/

#endif /* DIO_CFG_H_ */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/