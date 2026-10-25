/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Det.c
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

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Dem.h"

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/


/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/
Dem_Error GstDemErrBuffer[DEM_ERROR_BUFFER_SIZE];
uint8 GstDemBuffIndex[MCAL_NUMBER_OF_CORES] = {0x00};

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
FUNC(void, AUTOMATIC) Dem_ReportErrorStatus
(
    Dem_EventIdType EventId,
    Dem_EventStatusType EventStatus
)
{
    Dem_Error     *DemBufferPtr;
    Mcal_CoreType CoreId;

    CoreId = Mcal_GetCoreId();
    /* DET error is reported */
    if (GstDemBuffIndex[CoreId] < DEM_ERROR_BUFFER_SIZE)
    {
        DemBufferPtr = &GstDemErrBuffer[GstDemBuffIndex[CoreId]++];
        DemBufferPtr->EventId[CoreId] = EventId;
        DemBufferPtr->EventStatus[CoreId] = EventStatus;
    }
    else
    {
        /* Do nothing */
    }
}

FUNC(void, AUTOMATIC) Dem_SetEventStatus
(
    Dem_EventIdType EventId,
    Dem_EventStatusType EventStatus
)
{
    Dem_Error     *DemBufferPtr;
    Mcal_CoreType CoreId;

    CoreId = Mcal_GetCoreId();
    /* DET error is reported */
    if (GstDemBuffIndex[CoreId] < DEM_ERROR_BUFFER_SIZE)
    {
        DemBufferPtr = &GstDemErrBuffer[GstDemBuffIndex[CoreId]++];
        DemBufferPtr->EventId[CoreId] = EventId;
        DemBufferPtr->EventStatus[CoreId] = EventStatus;
    }
    else
    {
        /* Do nothing */
    }
}


/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

