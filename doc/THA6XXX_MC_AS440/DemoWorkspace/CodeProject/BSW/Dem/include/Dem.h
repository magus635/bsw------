/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Det.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Dem
*
*   brief                 : This file contains sample code only. It is not part of the production
*                           code deliverables.
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

#ifndef DEM_H
#define DEM_H

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"
#include "Dem_Cfg.h"
#include "Mcall.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/


#define DEM_EVENT_STATUS_PASSED                ((Dem_EventStatusType)0x00)
#define DEM_EVENT_STATUS_FAILED                ((Dem_EventStatusType)0x01)
#define DEM_EVENT_STATUS_PREPASSED             ((Dem_EventStatusType)0x02)
#define DEM_EVENT_STATUS_PREFAILED             ((Dem_EventStatusType)0x03)
#define DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED ((Dem_EventStatusType)0x04)

#define DEM_ERROR_BUFFER_SIZE 60U

/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
typedef uint16 Dem_EventIdType;           /**< @brief dem event ID type */
typedef uint8  Dem_EventStatusType;      /**< @brief dem event status type */

/* Defining the structure to store the parameters of Dem Report Error
   function */
typedef struct STag_Dem_Error
{
    /* It will store the Event Id of the reporting module */
    Dem_EventIdType EventId[MCAL_NUMBER_OF_CORES];

    /* It will store the Event Status of the reporting module */
    Dem_EventStatusType EventStatus[MCAL_NUMBER_OF_CORES];
}Dem_Error;
/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/
extern Dem_Error GstDemErrBuffer[DEM_ERROR_BUFFER_SIZE];

extern uint8 GstDemBuffIndex[MCAL_NUMBER_OF_CORES];

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
extern FUNC(void, AUTOMATIC) Dem_ReportErrorStatus
(
    Dem_EventIdType EventId,
    Dem_EventStatusType EventStatus
);

extern FUNC(void, AUTOMATIC) Dem_SetEventStatus
(
    Dem_EventIdType EventId,
    Dem_EventStatusType EventStatus
);

#endif /* DEM_H */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
