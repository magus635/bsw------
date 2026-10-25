/****************************************************************************************************
 *
****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Port_TLLD.h
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : GPIO
 *
 *   brief                 : This file contains internal function declarations of Port Driver
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
*#Port_TLLD_h_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*#Port_TLLD_h_REF_2:MISRAC2012-Rule-20.10; 
* Justification: Use glue operator to construct the exclusive area function name.
*
*#Port_TLLD_h_REF_3:CertC-INT36-C;
* Justification: Cast a numeric value to a pointer type for accessing data at a specified memory address.
*
*#Port_TLLD_h_REF_4:CertC-PRE00-C;
* Justification: Function like macros are used to reduce code complexity.
*
*/

#ifndef PORT_TLLD_H_
#define PORT_TLLD_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Port_GeneralTypes.h"
#include "Port_Cfg.h"
#include "port_register.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
/* Macro definition Port-Pin direction control register bit field mask */
#define PORT_REG_DIR_MASK                              (0xC0UL)

/* Macro definition of Port-Pin multiplexing function register bit field mask */
#define PORT_REG_MODE_MASK                             (0x0FUL)

/* Macro definition invalid value */
#define PORT_NULL_MASK                                 (0xFFUL)

/* Macro definition output function select mask */
#define PORT_SEL_MASK                                 (0x7070707UL)
/****************************************************************************************************
*                          SchM Critical Section Protection Macros                                 **
****************************************************************************************************/
/* #Violation: Port_TLLD_h_REF_2 */
/* #Violation: Port_TLLD_h_REF_4 */
#define PORT_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Port_##Exclusive_Area()

/* #Violation: Port_TLLD_h_REF_2 */
/* #Violation: Port_TLLD_h_REF_4 */
#define PORT_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Port_##Exclusive_Area()
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
/* #Violation: Port_TLLD_h_REF_1 */
#define PORT_START_SEC_CODE_ASIL_D_GLOBAL
#include "Port_MemMap.h"

extern FUNC(boolean, PORT_PRIVATE_CODE) Port_TLLD_Init
(
    P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr
);

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
extern FUNC(boolean, PORT_PRIVATE_CODE) Port_TLLD_SetPinDirection
(
    uint8 PortNumber,
    uint8 PinNumber,
    Port_PinDirectionType Direction,
    P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr
);
#endif /* (PORT_SET_PIN_DIRECTION_API \== STD_ON)*/

#if (PORT_SET_PIN_MODE_API == STD_ON)
extern FUNC(boolean, PORT_PRIVATE_CODE) Port_TLLD_SetPinMode
(
    uint8 PortNumber,
    uint8 PinNumber,
    Port_PinModeType Mode,
    P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr
);
#endif /* (PORT_SET_PIN_MODE_API  \== STD_ON) */

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
extern FUNC(boolean, PORT_PRIVATE_CODE) Port_TLLD_RefreshPortDirection
(
    uint8 PortNumber,
    uint8 PinNumber,
    uint8 PinCfgData,
    P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr
);
#endif /* (PORT_SET_PIN_DIRECTION_API  \== STD_ON) */

#if ((PORT_SET_PIN_DIRECTION_API == STD_ON) || (PORT_SET_PIN_MODE_API == STD_ON))
extern FUNC(uint8, PORT_PRIVATE_CODE) Port_TLLD_GetPinCTRCfg
(
    uint8 PortNumber,
    uint8 PinNumber,
    P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr
);
#endif /* ((PORT_SET_PIN_DIRECTION_API == STD_ON) || (PORT_SET_PIN_MODE_API \== STD_ON)) */

/* #Violation: Port_TLLD_h_REF_1 */
#define PORT_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Port_MemMap.h"

#endif /* PORT_TLLD_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

