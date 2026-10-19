/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_application_types.h
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
*  V0.1.0   28-May-2024    Pony(00412)                           Add Initial Code
****************************************************************************************************/
#ifndef OS_APPLICATION_TYPES_H_
#define OS_APPLICATION_TYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"
#include "Os_GeneralTypes.h"
#include "Os_application_Cfg.h"
#include "Os_kernel_Cfg.h"
#include "Os_context_types.h"
#include "Os_isr_types.h"
#include "Os_task_types.h"
/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/

typedef P2CONST(Os_ContextType, TYPEDEF, OS_CONST) Os_ContextRefType;

struct OsApp_ObjectType;
typedef struct OsApp_ObjectType  Os_AppObjectType;
typedef P2CONST(Os_AppObjectType, TYPEDEF, OS_VAR)  Os_AppObjectRefType;
/****************************************************************************************************
**                          Global Enumeration Definitions                                          **
****************************************************************************************************/

/*[SWS_Os_00773] Definition of datatype ApplicationStateType */
typedef enum
{
    APPLICATION_TERMINATED = 0,     /* The application is terminated */
    APPLICATION_ACCESSIBLE,          /* The application is accessible and accessible */
    APPLICATION_RESTARTING           /* The application is in the restart */
} ApplicationStateType;

/* [SWS_Os_00774] Definition of datatype ApplicationStateRefType */
typedef P2VAR(ApplicationStateType, TYPEDEF, OS_VAR) ApplicationStateRefType;

/*[SWS_Os_00778] Definition of datatype ObjectAccessType*/
typedef enum
{
    ACCESS,
    NO_ACCESS

}ObjectAccessType;

/*[SWS_Os_00788] Definition of datatype RestartType*/
typedef enum
{
    OS_OSAPPLICATION_RESTART,
    OS_OSAPPLICATION_NO_RESTART
} RestartType;

/****************************************************************************************************
**                          Global Union Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/

/*The running data for Alarm and Schedule Table */
typedef struct
{
    CounterType  CounterID;
    P2VAR(TickType, TYPEDEF, OS_CONST) ExpTime;
} Os_NodeConfigType;

typedef P2CONST(Os_NodeConfigType, TYPEDEF, OS_CONST) Os_NodeConfigRefType;

/*The data format for Object, which is defined to union. To Task ,Hook or ISR, it
 * is defined to context format, to Alarm or Schedule table , it is defined to Node format*/
typedef union
{
    /* Point to the ContextInfo configuration set point address. */
    P2CONST(Os_ContextRefType, TYPEDEF, OS_CONST)  ObjectContextInfoPtr;
    /*The Node information for Alarm and Schedule Table*/
    Os_NodeConfigRefType NodeInfo;
} Os_AppObjectDataInfoType;

/*The data definition for Object*/
struct OsApp_ObjectType
{
    /* The index in the global configuration object array for this object */
    uint32 ObjectIDIndex;
    /* Include the AppID and ObjectType ID(e.g TaskID, ISR2ID) information */
    uint32 AppObjIDInfo;
    /* Indicate the ObjectType */
    ObjectTypeType ObjectType;
    /* The running data for object */
    Os_AppObjectDataInfoType ObjectDataInfo;
    /*The applications ID can access this object   */
    uint32 AccessingAppMask;
    /* The previous object content,  the data field for nested of Task,and Hook*/
    P2VAR(Os_AppObjectRefType, TYPEDEF, OS_VAR) PreviousObjectInfoRef;
};

typedef struct 
{
    /* This indication the ID of Application */
    uint32 ApplicationID;
    /* This indication the application in which logical core.  */
    uint32 LogicalCoreID;
    /* This indication the application in which logical core.  */
    uint32 PhysicalCoreID;
    /* This member indication each application start objectID index  */
    uint32 ObjectID_StartNum;      
    /* This Application has the total numbers of Object. */
    uint32 ObjectIDCount;
    /* Indicate the Application Restart Task */
    TaskType RestartTask;
    /* This Application is trusted or not. */
    boolean AppIsTrusted;
    /*[ECUC_Os_00395] The Tp delay flag*/
    boolean OsTrustedApplicationDelayTimingViolationCall;
    /* This member indication the Application status variant pointer. */
    P2VAR(ApplicationStateType, TYPEDEF, OS_VAR) AppStatusRef;
}Os_ApplicationConfigType;

typedef struct 
{
    /* SWS_Os_00797 The current application ID*/
    ApplicationType Current_ApplicationID;
    /* SWS_Os_00016 This ID should be changed in trusted function*/
    ApplicationType Current_Config_ApplicationID;
    /* This member indication the current running thread is which ISR2 or Task. */
    uint32 Current_RunningObjectID;
    /* This member indication the current core is call the trust function. */
    boolean TrustFunctionIsCalled;
}Os_ApplicationRunningTimeDataType;

typedef struct 
{
    /* Indication the Application Config point. */
    P2CONST(Os_ApplicationConfigType, TYPEDEF, OS_CONST) AppConfigPtr[OS_APPLICATION_TOTAL_NUM];
    /* Indication the Object list Config point arrry. */
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) ObjectRef;

}Os_AppConfigType;

/*The expiration time for Alarm and Schedule Table*/
typedef struct
{
    uint32    ExpirationTime;
}Os_AppJobRunningDataType;

/*The configuration data for counter job*/
typedef struct
{
    /*The counter ID for job*/
    uint32    CounterID;

    /*The  running data for Job*/
    P2CONST(Os_AppJobRunningDataType, TYPEDEF, OS_CONST) RunningData;
}Os_AppJobConfigType;

#endif /* OS_APPLICATION_TYPES_H_ */

/****************************************************************************************************
**     End of File: Os_application_types.h                                                         **
****************************************************************************************************/

