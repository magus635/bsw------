/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_GeneralTypes.h
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
*  V0.0.1   28-May-2024    zhangtr(30011)                        Initial Version
*
****************************************************************************************************/
#ifndef OS_GENERALTYPES_H_
#define OS_GENERALTYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#define IDLE_NO_HALT                        ((IdleModeType)0)
#define TASK(TaskName)                      void Task_##TaskName(void)
#define ISR(IsrName)                        void Isr_##IsrName(void)

typedef enum
{
    E_OS_ACCESS                = 0x01,
    E_OS_CALLEVEL              = 0x02,
    E_OS_ID                    = 0x03,
    E_OS_LIMIT                 = 0x04,
    E_OS_NOFUNC                = 0x05,
    E_OS_RESOURCE              = 0x06,
    E_OS_STATE                 = 0x07,
    E_OS_VALUE                 = 0x08,
    E_OS_SERVICEID             = 0x09,
    E_OS_ILLEGAL_ADDRESS       = 0x0A,
    E_OS_MISSINGEND            = 0x0B,
    E_OS_DISABLEDINT           = 0x0C,
    E_OS_STACKFAULT            = 0x0D,
    E_OS_PROTECTION_MEMORY     = 0x0E,
    E_OS_PROTECTION_TIME       = 0x0F,
    E_OS_PROTECTION_ARRIVAL    = 0x10,
    E_OS_PROTECTION_LOCKED     = 0x11,
    E_OS_PROTECTION_EXCEPTION  = 0x12,
    E_OS_SPINLOCK              = 0x13,
    E_OS_INTERFERENCE_DEADLOCK = 0x14,
    E_OS_NESTING_DEADLOCK      = 0x15,
    E_OS_CORE                  = 0x16,
    E_OS_PARAM_POINTER         = 0x17,
    /*Internal errors of the OS should use E_OS_SYS_xxx as OSEK recommend*/
    E_OS_SYS_API_ERROR         = 0x18,
    E_OS_STATUS_ACCESSRIGHTS   = 0x19,
    E_OS_SYS_UNDEFINED_IRQ     = 0x20,
    E_OS_NO_PRE_TASK           = 0x21
} Os_StatusType;

/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
typedef uint32     AppModeType;
typedef uint16     TotalNumberOfCores;
typedef uint32     ApplicationType;
typedef uint8      CoreIdType;
typedef uint32     IdleModeType;
typedef uint32     TickType;
typedef sint64    Os_TickDiffType;
typedef TickType*  TickRefType;
typedef uint32     AlarmType;
typedef uint32     CounterType;
typedef uint32     PhysicalTimeType;


/****************************************************************************************************
**                          Global Enumeration Definitions                                          **
****************************************************************************************************/
/*[SWS_Os_00779] Definition of datatype ObjectTypeType*/
typedef enum
{
    OBJECT_TASK,                   /* The object type is a task. */
    OBJECT_ISR,                    /* The object type is an ISR. */
    OBJECT_ALARM,                  /* The object type is an alarm. */
    OBJECT_RESOURCE,               /* The object type is a resource. */
    OBJECT_COUNTER,                /* The object type is a counter. */
    OBJECT_SCHEDULETABLE,          /* The object type is a schedule table. */
    OBJECT_APPHOOK,                /* The object type is a Application Hook. */
    OBJECT_KERNELHOOK,             /* The object type is a Kernel Hook. */
    OBJECT_APPTRUSTFUNC,           /* The object type is a Application Trust function table. */
    OBJECT_APPIOCCALLBACK,         /* The object type is a Application IOC Channel. */
    OBJECT_STARTOSINITFUNCTION    /* The object type is a StartOS Init function. */
} ObjectTypeType;

typedef enum
{
    /*AUTOSAR 23-11 Version Definitions*/
    OS_SERVICEID_GETAPPLICATIONID            = 0x00,
    OS_SERVICEID_GETISRID                    = 0x01,
    OS_SERVICEID_CALLTRUSTEDFUNCTION         = 0x02,
    OS_SERVICEID_CHECKISRMEMORYACCESS        = 0x03,
    OS_SERVICEID_CHECKTASKMEMORYACCESS       = 0x04,
    OS_SERVICEID_CHECKOBJECTACCESS           = 0x05,
    OS_SERVICEID_CHECKOBJECTOWNERSHIP        = 0x06,
    OS_SERVICEID_STARTSCHEDULETABLEREL       = 0x07,
    OS_SERVICEID_STARTSCHEDULETABLEABS       = 0x08,
    OS_SERVICEID_STOPSCHEDULETABLE           = 0x09,
    OS_SERVICEID_NEXTSCHEDULETABLE           = 0x0a,
    OS_SERVICEID_STARTSCHEDULETABLESYNCHRON  = 0x0b,
    OS_SERVICEID_SYNCSCHEDULETABLE           = 0x0c,
    OS_SERVICEID_SETSCHEDULETABLEASYNC       = 0x0d,
    OS_SERVICEID_GETSCHEDULETABLESTATUS      = 0x0e,
    OS_SERVICEID_INCREMENTCOUNTER            = 0x0f,
    OS_SERVICEID_GETCOUNTERVALUE             = 0x10,
    OS_SERVICEID_GETELAPSEDVALUE             = 0x11,
    OS_SERVICEID_TERMINATEAPPLICATION        = 0x12,
    OS_SERVICEID_ALLOWACCESS                 = 0x13,
    OS_SERVICEID_GETAPPLICATIONSTATE         = 0x14,
    OS_SERVICEID_GETNUMBEROFACTIVATEDCORES   = 0x15,
    OS_SERVICEID_GETCOREID                   = 0x16,
    OS_SERVICEID_STARTCORE                   = 0x17,
    OS_SERVICEID_GETSPINLOCK                 = 0x19,
    OS_SERVICEID_RELEASESPINLOCK             = 0x1a,
    OS_SERVICEID_TRYTOGETSPINLOCK            = 0x1b,
    OS_SERVICEID_SHUTDOWNALLCORES            = 0x1c,
    OS_SERVICEID_CONTROLIDLE                 = 0x1d,
    OS_SERVICEID_IOCSENDIOCIDSENDERID        = 0x1e,
    OS_SERVICEID_IOCWRITEIOCIDSENDERID       = 0x1f,
    OS_SERVICEID_IOCSENDGROUPIOCID           = 0x20,
    OS_SERVICEID_IOCWRITEGROUPIOCID          = 0x21,
    OS_SERVICEID_IOCRECEIVEIOCID             = 0x22,
    OS_SERVICEID_IOCREADIOCIDRECEIVERID      = 0x23,
    OS_SERVICEID_IOCRECEIVEGROUPIOCID        = 0x24,
    OS_SERVICEID_IOCREADGROUPIOCID           = 0x25,
    OS_SERVICEID_IOCEMPTYQUEUE               = 0x26,
    OS_SERVICEID_GETCURRENTAPPLICATIONID     = 0x27,
    OS_SERVICEID_READPERIPHERAL8             = 0x28,
    OS_SERVICEID_READPERIPHERAL16            = 0x29,
    OS_SERVICEID_READPERIPHERAL32            = 0x2a,
    OS_SERVICEID_WRITEPERIPHERAL8            = 0x2b,
    OS_SERVICEID_WRITEPERIPHERAL16           = 0x2c,
    OS_SERVICEID_WRITEPERIPHERAL32           = 0x2d,
    OS_SERVICEID_MODIFYPERIPHERAL8           = 0x2e,
    OS_SERVICEID_MODIFYPERIPHERAL32          = 0x2f,
    OS_SERVICEID_DISABLEINTERRUPTSOURCE      = 0x30,
    OS_SERVICEID_ENABLEINTERRUPTSOURCE       = 0x31,
    OS_SERVICEID_CLEARPENDINGINTERRUPT       = 0x32,
    OS_SERVICEID_ACTIVATETASKASYN            = 0x33,
    OS_SERVICEID_SETEVENTASYN                = 0x34,
    OS_SERVICEID_MODIFYPERIPHERAL16          = 0x35,
    OS_SERVICEID_ISOSSTARTED                 = 0x36,

    /*OSEK Definitions.*/
    OS_SERVICEID_STARTOS                     = 0xd0,
    OS_SERVICEID_GETACTIVATEAPPLICATIONMODE  = 0xd2,
    OS_SERVICEID_DISABLEALLINTERRUPTS        = 0xd3,
    OS_SERVICEID_ENABLEALLINTERRUPTS         = 0xd4,
    OS_SERVICEID_SUSPENDALLINTERRUPTS        = 0xd5,
    OS_SERVICEID_RESUMEALLINTERRUPTS         = 0xd6,
    OS_SERVICEID_SUSPENDOSINTERRUPTS         = 0xd7,
    OS_SERVICEID_RESUMEOSINTERRUPTS          = 0xd8,
    OS_SERVICEID_TERMINATETASK               = 0xda,
    OS_SERVICEID_ACTIVATETASK                = 0xd9,
    OS_SERVICEID_CHAINTASK                   = 0xdb,
    OS_SERVICEID_GETTASKID                   = 0xdc,
    OS_SERVICEID_GETTASKSTATE                = 0xdd,
    OS_SERVICEID_SCHEDULE                    = 0xde,
    OS_SERVICEID_SETEVENT                    = 0xdf,
    OS_SERVICEID_CLEAREVENT                  = 0xe0,
    OS_SERVICEID_GETEVENT                    = 0xe1,
    OS_SERVICEID_WAITEVENT                   = 0xe2,
    OS_SERVICEID_GETALARMBASE                = 0xe3,
    OS_SERVICEID_GETALARM                    = 0xe4,
    OS_SERVICEID_SETRELALARM                 = 0xe5,
    OS_SERVICEID_SETABSALARM                 = 0xe6,
    OS_SERVICEID_CANCELALARM                 = 0xe7,
    OS_SERVICEID_GETRESOURCE                 = 0xe8,
    OS_SERVICEID_RELEASERESOURCE             = 0xe9,

    /*Self Definitions*/
    OS_SERVICEID_POSTISR                     = 0xea,
    OS_SERVICEID_IOCCALLCALLBACK             = 0xeb,
    OS_SERVICEID_DOALARM                       = 0xec
} Os_ServiceType;

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/

#endif /* OS_GENERALTYPES_H_ */

/****************************************************************************************************
**     End of File: Os_GeneralTypes.h                                                              **
****************************************************************************************************/
