/**************************************************************************************************
*
***************************************************************************************************/
/**************************************************************************************************
*   FileName             : Std_Types.h
*
*   Platform             : AUTOSAR
*
*   brief                : This document specifies the AUTOSAR standard types header file. It contains 
*                          all that are used across several modules of the basic software and that are 
*                          platform and compiler independent.
*
*   Autosar Version      : 4.4.0
*
*   SW Version           : 1.0.0
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/
#ifndef STD_TYPES_H_
#define STD_TYPES_H_
/***************************************************************************************************
*                               Include
***************************************************************************************************/
#include "Compiler.h"
#include "Platform_Types.h"

/***************************************************************************************************
*                               Symbol Definitions
***************************************************************************************************/
/*SWS_Std_00007 Physical state*/
#define STD_HIGH    0x01u
#define STD_LOW     0x00u

/*SWS_Std_00013 Logical state*/
#define STD_ACTIVE  0x01u
#define STD_IDLE    0x00u
/*SWS_Std_0005*/
typedef uint8 Std_ReturnType;


#ifndef STD_ON
#define STD_ON     0x01u      /* Standard ON */
#endif

#ifndef STD_OFF
#define STD_OFF    0x00u      /* Standard OFF */
#endif
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

/*SWS_Std_0015*/
typedef struct
{
    uint16  vendorID;               /*vendor ID */
    uint16  moduleID;               /*BSW module ID */
    uint8   sw_major_version;       /*BSW module software major version */
    uint8   sw_minor_version;       /*BSW module software minor version */
    uint8   sw_patch_version;       /*BSW module software patch version */
}Std_VersionInfoType;


#endif /* STD_TYPES_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
