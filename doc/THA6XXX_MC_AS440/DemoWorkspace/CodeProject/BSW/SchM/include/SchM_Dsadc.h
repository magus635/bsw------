/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Dsadc.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DSADC
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

#ifndef SCHM_DSADC_H
#define SCHM_DSADC_H

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
extern void SchM_Enter_Dsadc_StartConversion(void);
extern void SchM_Exit_Dsadc_StartConversion(void);

extern void SchM_Enter_Dsadc_StopConversion(void);
extern void SchM_Exit_Dsadc_StopConversion(void);

extern void SchM_Enter_Dsadc_GetStreamLastPointer(void);
extern void SchM_Exit_Dsadc_GetStreamLastPointer(void);

extern void SchM_Enter_Dsadc_GetChannelStatus(void);
extern void SchM_Exit_Dsadc_GetChannelStatus(void);

extern void SchM_Enter_Dsadc_ResultHandling(void);
extern void SchM_Exit_Dsadc_ResultHandling(void);

extern void SchM_Enter_Dsadc_DeInit(void);
extern void SchM_Exit_Dsadc_DeInit(void);


#endif /* SCHM_DSADC_H*/

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
