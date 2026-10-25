/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Pwm.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-TOM, GTM-ATOM
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

#ifndef SCHM_PWM_H_
#define SCHM_PWM_H_

#include "Std_Types.h"

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

extern void SchM_Enter_Pwm_Init
(
    void
);

extern void SchM_Exit_Pwm_Init
(
    void
);

extern void SchM_Enter_Pwm_DeInit
(
    void
);

extern void SchM_Exit_Pwm_DeInit
(
    void
);

extern void SchM_Enter_Pwm_SetDutyCycle
(
  void
);

extern void SchM_Exit_Pwm_SetDutyCycle
(
  void
);

extern void SchM_Enter_Pwm_SetPeriodAndDuty
(
  void
);

extern void SchM_Exit_Pwm_SetPeriodAndDuty
(
  void
);

extern void SchM_Enter_Pwm_SetOutputToIdle
(
  void
);

extern void SchM_Exit_Pwm_SetOutputToIdle
(
  void
);

extern void SchM_Enter_Pwm_DisableNotification
(
  void
);

extern void SchM_Exit_Pwm_DisableNotification
(
  void
);

extern void SchM_Enter_Pwm_EnableNotification
(
  void
);

extern void SchM_Exit_Pwm_EnableNotification
(
  void
);

#endif /* SCHM_PWM_H */
