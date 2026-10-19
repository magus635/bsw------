/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_resource_types.h
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
#ifndef OS_RESOURCE_TYPES_H_
#define OS_RESOURCE_TYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "datatypes.h"
#include "Std_Types.h"
#include "Os_GeneralTypes.h"
#include "Os_lock_types.h"
#include "Os_isr_types.h"

/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
typedef uint32 ResourceType;

/****************************************************************************************************
**                          Global Enumeration Definitions                                          **
****************************************************************************************************/
typedef enum
{
    OS_RESOURCETYPE_INTERNAL,
    OS_RESOURCETYPE_LINKED,
    OS_RESOURCETYPE_STANDARD
}Os_ResourceType;

/****************************************************************************************************
**                          Global Union Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/
typedef struct
{
    /* ID list of object that can access resource */
    P2CONST(uint32, AUTOMATIC, OS_CONST) AccessObjectIdList;
    /* Number of object that can access resource */
    uint32 AccessObjectIdNum;
}Os_ResourceAccessObjectListType;

typedef struct
{
    /* Task priority before getting this resource */
    uint32 PreviousTaskPriority;
    /* Isr level before getting this resource */
    uint32 PreviousIsrLevel;
    /* ObjectID of template owner of this resource */
    uint32 OwnerObjectID;
}Os_ResourceRunningDataType;

typedef struct
{
    /* Resource id */
    ResourceType ResID;
    /* Type of resource.
       Internal: Invisible to user.
       Linked: Same behaviour with linked resource.
       Standard: Normal resource. */
    Os_ResourceType ResourceType;
    /* Ceiling priority of task */
    uint32 CeilingPriority;
    /* Ceiling priority of Isr */
    Os_IsrLevelType CeilingIsrLevel;
    Os_LockConfigRefType Lock;
    /* List of object that can access resource */
    Os_ResourceAccessObjectListType AccessObjectList;
    P2VAR(Os_ResourceRunningDataType, AUTOMATIC, OS_VAR) RunningData;
}Os_ResourceConfigType;

typedef P2CONST(Os_ResourceConfigType, TYPEDEF, OS_CONST) Os_ResourceConfigRefType;

#endif /* OS_RESOURCE_TYPES_H_ */

/****************************************************************************************************
**     End of File: Os_resource_types.h                                                            **
****************************************************************************************************/

