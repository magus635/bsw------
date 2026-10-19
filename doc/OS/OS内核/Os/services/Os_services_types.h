/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_services_types.h
*
*   Platform              : AUTOSAR
*
*   BSW Module            : Os
*
*   brief                 : xxx
*
*   Autosar Version       : R23-11
*
*   Build Version         : Cortex-R52/THA6206
*
*   Copyright (c) @#
*   All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Revision Control History                                               **
****************************************************************************************************/
/*
*  -------------------------------------------------------------------------------------------------
*  Version    Date           Author(ID)      SVN_Version         Description
*  -------------------------------------------------------------------------------------------------
*  V0.0.1   22-May-2024    zhangtr(30011)                        Initial Version
*
****************************************************************************************************/
#ifndef OS_SERVICES_TYPES_H_
#define OS_SERVICES_TYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "datatypes.h"
#include "Compiler.h"
#include "Os_GeneralTypes.h"
#include "Os_mpu_types.h"
/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
/*[SWS_Os_00775] This data type identifies a trusted function*/
typedef uint32 TrustedFunctionIndexType;

/*[SWS_Os_00776] This data type points to a structure which holds the arguments for a call to a trusted function*/
typedef P2VAR(void, TYPEDEF, OS_APPL_DATA) TrustedFunctionParameterRefType;

/****************************************************************************************************
**                          Global Enumeration Definitions                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Union Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/

/*[SWS_Os_00312] The called trusted function*/
typedef P2FUNC(void, OS_CODE, OsService_TrustedFunc)(TrustedFunctionIndexType,TrustedFunctionParameterRefType);

/*The configuration data of Trusted function*/
typedef struct
{
    /* The Application ID of the service function */
    ApplicationType ApplicationID;

    /*The Trusted function entry */
    OsService_TrustedFunc Callback;
}OsServices_TFConfigType;

/*The parameters and configuration data for each Trusted function*/
typedef struct
{
    TrustedFunctionParameterRefType         OsServices_Param;
    P2CONST(OsServices_TFConfigType, TYPEDEF, OS_CONST)  OsServices_TF;
}OsServices_ConfigType;

#endif /* OS_SCHEDULETABLE_TYPES_H_ */

/****************************************************************************************************
**     End of File: Os_scheduletable_types.h                                                       **
****************************************************************************************************/

