/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Adc.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Saradc
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

#ifndef SCHM_ADC_H
#define SCHM_ADC_H

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/

extern void SchM_Enter_Adc_StartGroup(void);

extern void SchM_Enter_Adc_StopGroup(void);

extern void SchM_Enter_Adc_ReadGroup(void);

extern void SchM_Enter_Adc_EnableHwTrig(void);

extern void SchM_Enter_Adc_DisableHwTrig(void);

extern void SchM_Enter_Adc_GetGrpStatus(void);

extern void SchM_Enter_Adc_GetStreamLastPtr(void);

extern void SchM_Enter_Adc_ScheduleStart(void);

extern void SchM_Enter_Adc_ScheduleStop(void);

extern void SchM_Enter_Adc_ScheduleNext(void);

extern void SchM_Enter_Adc_PushQueue(void);

extern void SchM_Enter_Adc_PopQueue(void);

extern void SchM_Exit_Adc_StartGroup(void);

extern void SchM_Exit_Adc_StopGroup(void);

extern void SchM_Exit_Adc_ReadGroup(void);

extern void SchM_Exit_Adc_EnableHwTrig(void);

extern void SchM_Exit_Adc_DisableHwTrig(void);

extern void SchM_Exit_Adc_GetGrpStatus(void);

extern void SchM_Exit_Adc_GetStreamLastPtr(void);

extern void SchM_Exit_Adc_ScheduleStart(void);

extern void SchM_Exit_Adc_ScheduleStop(void);

extern void SchM_Exit_Adc_ScheduleNext(void);

extern void SchM_Exit_Adc_PushQueue(void);

extern void SchM_Exit_Adc_PopQueue(void);

extern void SchM_Enter_Adc_DisableGroupNotification(void);

extern void SchM_Exit_Adc_DisableGroupNotification(void);

extern void SchM_Enter_Adc_EnableGroupNotification(void);

extern void SchM_Exit_Adc_EnableGroupNotification(void);

extern void SchM_Enter_Adc_Endinit(void);

extern void SchM_Exit_Adc_Endinit(void);

extern void SchM_Enter_Adc_ResultHandling(void);

extern void SchM_Exit_Adc_ResultHandling(void);

extern void SchM_Enter_Adc_DeInit(void);

extern void SchM_Exit_Adc_DeInit(void);

#endif /* SCHM_ADC_H*/

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
