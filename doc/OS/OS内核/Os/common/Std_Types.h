/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Std_Types.h
*
*   Platform              : AUTOSAR
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
#ifndef STD_TYPES_H_
#define STD_TYPES_H_
/***************************************************************************************************
*                               Include
***************************************************************************************************/
#include "Platform_Types.h"
#include "common.h"
#include "Compiler.h"

/***************************************************************************************************
*                               Symbol Definitions
***************************************************************************************************/
/*SWS_Std_00007 Physical state*/
#define STD_HIGH    0x01u
#define STD_LOW     0x00u

/*SWS_Std_00013 Logical state*/
#define STD_ACTIVE  0x01u
#define STD_IDLE    0x00u

/*SWS_Std_00006 Return code*/
#ifndef STATUSTYPEDEFINED 
#define STATUSTYPEDEFINED 
#define E_OK                (Std_ReturnType)(0x00u)
typedef unsigned char StatusType; /* This type is defined for OSEK compliance */
#endif 
#define E_NOT_OK            (Std_ReturnType)(0x01u)
/***************************************************************************************************
*                               Type Definitions
***************************************************************************************************/
/*SWS_Std_0005*/
typedef uint8 Std_ReturnType;
/*SWS_Std_0015*/
typedef struct
{
    uint16  vendorID;               /*vendor ID */
    uint16  moduleID;               /*BSW module ID */
    uint8   sw_major_version;       /*BSW module software major version */
    uint8   sw_minor_version;       /*BSW module software minor version */
    uint8   sw_patch_version;       /*BSW module software patch version */
}Std_VersionInfoType;
/***************************************************************************************************
*                               Version Information
***************************************************************************************************/
#define STD_VENDOR_ID                     175

#define STD_SW_MAJOR_VERSION              1
#define STD_SW_MINOR_VERSION              0
#define STD_SW_PATCH_VERSION              0

#endif /* STD_TYPES_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
