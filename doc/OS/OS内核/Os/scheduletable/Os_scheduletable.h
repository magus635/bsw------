/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_scheduletable.h
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
*  V0.1.0   1-July-2024    Pony(00412)                           Add Initial Code
****************************************************************************************************/
#ifndef OS_SCHEDULETABLE_H_
#define OS_SCHEDULETABLE_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
//#define SCHT_TEST

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

/****************************************************************************************************
*   Function Name           : OsSchT_Init
*   Service ID              : None.
*   Description             : The application or other upper layer call this function to initialize the schedule.
*   Parameters in           : SchTID: The cschedule need to be initialized.
*                           : AppMode: The application mode.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsSchT_Init(ScheduleTableType SchTID, AppModeType AppMode );

/****************************************************************************************************
*   Function Name           : OsSchT_DeInit
*   Service ID              : None.
*   Description             : The application or other upper layer call this function to reinitialize the schedule.
*   Parameters in           : SchTID: The cschedule need to be initialized.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) OsSchT_DeInit(ScheduleTableType SchTID );

/****************************************************************************************************
*   Function Name           : OsSchedT_DoSchedulTable
*   Service ID              : None.
*   Description             : Callback function used for counter.
*   Parameters in           : Object: Pointer to Os_AppObjectType Inforamtion of related SchTID.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsSchedT_DoSchedulTable
(
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) Object
);

#endif /* OS_SCHEDULETABLE_H_ */

/****************************************************************************************************
**     End of File: Os_scheduletable.h                                                             **
****************************************************************************************************/

