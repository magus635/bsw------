/****************************************************************************************************
 *
****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Port.h
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : GPIO
 *
 *   brief                 : This file contains all function declarations of Port Driver
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
*#Port_h_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*/

#ifndef PORT_H_
#define PORT_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Mcall.h"
/*  SWS_Port_00130:
    Port.h shall include Port_Cfg.h for the API pre-compiler switches and Std_Types.h.
    SWS_Port_00208:
    The PORT Driver module's implementer shall publish the symbolic names through the file Port.h
*/
#include "Port_Cfg.h"
#include "Port_PBcfg.h"
#include "Port_Version.h"
#include "Port_GeneralTypes.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
/* SWS_Port_00051:
    The following errors and exceptions shall be detectable by the  PORT driver depending on its
   build version (development/production).
 */
/* Service is called with invalid parameter Pin */
#define PORT_E_PARAM_PIN                ((uint8)0x0AU)
/* Service is called for a Pin that is configured as direction  not changeable during runtime */
#define PORT_E_DIRECTION_UNCHANGEABLE   ((uint8)0x0BU)
/* Init Service is called with NULL configuration pointer */
#define PORT_E_INIT_FAILED              ((uint8)0x0CU)
/* Service is called for Pin with invalid mode */
#define PORT_E_PARAM_INVALID_MODE       ((uint8)0x0DU)
/* Service is called for a Pin that is configured as mode
   not changeable during runtime */
#define PORT_E_MODE_UNCHANGEABLE        ((uint8)0x0EU)
/* Service is called before Port_Init (Vendor Specific) */
#define PORT_E_UNINIT                   ((uint8)0x0FU)
/* Service is called with NULL_PTR */
#define PORT_E_PARAM_POINTER            ((uint8)0x10U)

/* No-AUTOSAR: Service is called safety mechanism check error */
#define PORT_E_SAFETY_ERROR             ((uint8)0xE1U)

/*  Service ID number for all PORT driver services*/
/* SWS_Port_00140: Service ID for Port_Init */
#define PORT_SID_INIT                   ((uint8)0x00U)
/* SWS_Port_00141: Service ID for Port_SetPinDirection */
#define PORT_SID_SETPINDIRECTION        ((uint8)0x01U)
/* SWS_Port_00142: Service ID for Port_RefreshPortDirection */
#define PORT_SID_REFRESHPORTDIR         ((uint8)0x02U)
/* SWS_Port_00143: Service ID for Port_GetVersionInfo */
#define PORT_SID_GETVERSIONINFO         ((uint8)0x03U)
/* SWS_Port_00145: Service ID for Port_SetPinMode */
#define PORT_SID_SETPINMODE             ((uint8)0x04U)
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
/* #Violation: Port_h_REF_1 */
#define PORT_START_SEC_CODE_ASIL_D_GLOBAL
#include "Port_MemMap.h"

extern FUNC(void, PORT_PUBLIC_CODE) Port_Init
(
    P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr
);

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
extern FUNC(void, PORT_PUBLIC_CODE) Port_SetPinDirection
(
    Port_PinType Pin,
    Port_PinDirectionType Direction
);

extern FUNC(void, PORT_PUBLIC_CODE) Port_RefreshPortDirection
(
    void
);
#endif /* (PORT_SET_PIN_DIRECTION_API  \== STD_ON) */

#if (PORT_VERSION_INFO_API == STD_ON)
extern FUNC(void, PORT_PUBLIC_CODE) Port_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, PORT_APPL_DATA) VersionInfoPtr
);
#endif /* (PORT_VERSION_INFO_API  \== STD_ON) */


#if (PORT_SET_PIN_MODE_API == STD_ON)
extern FUNC(void, PORT_PUBLIC_CODE) Port_SetPinMode
(
    Port_PinType Pin,
    Port_PinModeType Mode
);
#endif /* (PORT_SET_PIN_MODE_API  \== STD_ON) */

/* #Violation: Port_h_REF_1 */
#define PORT_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Port_MemMap.h"

#endif /* PORT_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

