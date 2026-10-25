/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Dio_GeneralTypes.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GPIO
*
*   brief                 : This file contains all type definitions of Dio Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright /(c)
*   All Rights Reserved.
*
****************************************************************************************************/

/*
*#Violation Summary
*#Dio_GeneralTypes_h_REF_1:MISRAC2012-Dir-4.8; 
* Justification:Apply such struct/union definitons to simplify the code structure and reduce the 
*   code complexity.
*
*/
 
/****************************************************************************************************/

#ifndef DIO_GENERALTYPES_H_
#define DIO_GENERALTYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"
/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
typedef uint16 Dio_ChannelType;
typedef uint8  Dio_PortType;
typedef uint8  Dio_LevelType;
typedef uint16 Dio_PortLevelType;
/****************************************************************************************************
**                          Global Enumration Definitions                                          **
****************************************************************************************************/
typedef enum
{
    DIO_PORT_NOT_CONFIGURED = 0U,
    DIO_PORT_CONFIGURED
}Dio_Port_ConfigType;
/****************************************************************************************************
**                          Global Union Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/
/* #Violation: Dio_GeneralTypes_h_REF_1*/
typedef struct
{
    Dio_PortType  port;
    uint8         offset;
    uint16        mask;
}Dio_ChannelGroupType;

/* #Violation: Dio_GeneralTypes_h_REF_1*/
typedef struct
{
    /*Configuration Status of port*/
    Dio_Port_ConfigType   Dio_PortConfig;
    /*Define configured channels of port bit =1*/
    uint16  Dio_ChannelConfig;
}Dio_PortChannelIdType;

typedef struct
{
    /* DIO single channel configuration parameters */
    const Dio_PortChannelIdType *Dio_ChCfgDataPtr;
    /* DIO channel group configuration parameters */
    const Dio_ChannelGroupType  *Dio_ChGroupDataPtr;
    /* The Port index from available Port */
    const uint8                 *Dio_AvailablePortIndexPtr;
    /* The PIN available for each port */
    const uint16                *Dio_AvailablePortPinsPtr;
}Dio_ConfigType;

#endif /* DIO_GENERALTYPES_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

