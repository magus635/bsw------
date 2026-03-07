/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_application_Cfg.h
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
*   Genaration Time       : 2026-03-05 20:16:07
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
#ifndef OS_APPLICATION_CFG_H_
#define OS_APPLICATION_CFG_H_


/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
/* This brief the object,application,counter ID mask. */
#define OBJECTID_MASK                        ((uint32)0x0000FFFF)
#define APPLICATIONID_MASK                   ((uint32)0x00FF0000)
#define COUNTERID_MASK                       ((uint32)0xFF000000)
#define COREID_MASK                          ((uint32)0xFF000000)
/* This brief the os used application modes */
#define DONOTCARE                   ((AppModeType)0x00000000)
#define OSDEFAULTAPPMODE            ((AppModeType)0x00000001)
#define OSALLRUNNINGMODE            ((AppModeType)0xFFFFFFFF)
#define APPLICATION_COUNTER_INVALID_ID_MASK      ((uint32)0xFF000000)


#define OSTRUSTAPP01MODE         ((AppModeType)0x00000002)
#define OS_APPLICATION_TOTAL_NUM                 ((uint32)4)
#define INVALID_OSAPPLICATION                    ((uint32)4)

#define APPLICATION0_OBJECT_START_NUMBER         ((uint32)0)
#define APPLICATION0_OBJECTCOUNT_NUMBER          ((uint32)30)
#define CORE0_ID_MASK                            ((uint32)0x00000000)
#define APPLICATION0_ID_MASK                     ((uint32)0x00000000)
#define APPLICATION0_ALARM_SCHEDULETABLE_NUMBER  ((uint32)6)


#define APPLICATION1_OBJECT_START_NUMBER         ((uint32)30)
#define APPLICATION1_OBJECTCOUNT_NUMBER          ((uint32)3)
#define CORE0_ID_MASK                            ((uint32)0x00000000)
#define APPLICATION1_ID_MASK                     ((uint32)0x00010000)
#define APPLICATION1_ALARM_SCHEDULETABLE_NUMBER  ((uint32)1)


#define APPLICATION2_OBJECT_START_NUMBER         ((uint32)33)
#define APPLICATION2_OBJECTCOUNT_NUMBER          ((uint32)4)
#define CORE0_ID_MASK                            ((uint32)0x00000000)
#define APPLICATION2_ID_MASK                     ((uint32)0x00020000)
#define APPLICATION2_ALARM_SCHEDULETABLE_NUMBER  ((uint32)1)


#define APPLICATION3_OBJECT_START_NUMBER         ((uint32)37)
#define APPLICATION3_OBJECTCOUNT_NUMBER          ((uint32)24)
#define CORE1_ID_MASK                            ((uint32)0x01000000)
#define APPLICATION3_ID_MASK                     ((uint32)0x00030000)
#define APPLICATION3_ALARM_SCHEDULETABLE_NUMBER  ((uint32)4)




#define TOTALNUM_OF_OBJECT                       ((uint32)61)
#define INVAILD_OBJECT_NUMBER                    ((uint32)61)
#define TOTALNUM_OF_TRUSTEDFUNC                  ((uint32)2)

#define OSAPPLICATION_0                          ((uint32)0)
#define OSAPPLICATION_1                          ((uint32)1)
#define OSAPPLICATION_2                          ((uint32)2)
#define OSAPPLICATION_3                          ((uint32)3)
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


#endif /* OS_APPLICATION_CFG_H_ */

/****************************************************************************************************
**     End of File: Os_application_Cfg.h                                                           **
****************************************************************************************************/

