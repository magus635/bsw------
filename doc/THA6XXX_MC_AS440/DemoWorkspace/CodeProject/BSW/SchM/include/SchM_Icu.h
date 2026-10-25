/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Icu.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Icu
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

#ifndef SCHM_ICU_H
#define SCHM_ICU_H

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
extern void SchM_Enter_Icu_GetInputState
(
    void
);

extern void SchM_Exit_Icu_GetInputState
(
    void
);


extern void SchM_Enter_Icu_StartTimestamp
(
    void
);

extern void SchM_Exit_Icu_StartTimestamp
(
    void
);


extern void SchM_Enter_Icu_StopTimestamp
(
    void
);

extern void SchM_Exit_Icu_StopTimestamp
(
    void
);

extern void SchM_Enter_Icu_GetTimestampIndex
(
    void
);

extern void SchM_Exit_Icu_GetTimestampIndex
(
    void
);
extern void SchM_Enter_Icu_ResetEdgeCount
(
    void
);

extern void SchM_Exit_Icu_ResetEdgeCount
(
    void
);


extern void SchM_Enter_Icu_EnableEdgeCount
(
    void
);

extern void SchM_Exit_Icu_EnableEdgeCount
(
    void
);


extern void SchM_Enter_Icu_DisableEdgeCount
(
    void
);

extern void SchM_Exit_Icu_DisableEdgeCount
(
    void
);


extern void SchM_Enter_Icu_EnableEdgeDetection
(
    void
);

extern void SchM_Exit_Icu_EnableEdgeDetection
(
    void
);


extern void SchM_Enter_Icu_EnableMultiEdgeDetection
(
    void
);

extern void SchM_Exit_Icu_EnableMultiEdgeDetection
(
    void
);


extern void SchM_Enter_Icu_DisableEdgeDetection
(
    void
);

extern void SchM_Exit_Icu_DisableEdgeDetection
(
    void
);


extern void SchM_Enter_Icu_StartSignalMeasurement
(
    void
);

extern void SchM_Exit_Icu_StartSignalMeasurement
(
    void
);


extern void SchM_Enter_Icu_StopSignalMeasurement
(
    void
);

extern void SchM_Exit_Icu_StopSignalMeasurement
(
    void
);


extern void SchM_Enter_Icu_GetTimeElapsed
(
    void
);

extern void SchM_Exit_Icu_GetTimeElapsed
(
    void
);


extern void SchM_Enter_Icu_GetDutyCycleValues
(
    void
);

extern void SchM_Exit_Icu_GetDutyCycleValues
(
    void
);


extern void SchM_Enter_Icu_Tim_ISRHandler
(
    void
);

extern void SchM_Exit_Icu_Tim_ISRHandler
(
    void
);


#endif /* SCHM_Icu_H */


/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
