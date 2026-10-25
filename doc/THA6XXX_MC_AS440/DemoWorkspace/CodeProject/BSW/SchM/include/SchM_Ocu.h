/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Ocu.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-ATOM
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

#ifndef SCHM_OCU_H
#define SCHM_OCU_H

#include "Std_Types.h"

/*==================================================================================================
 GLOBAL FUNCTIONS
 ==================================================================================================*/
extern void SchM_Enter_Ocu_StartChannel
(
    void
);

extern void SchM_Exit_Ocu_StartChannel
(
    void
);

extern void SchM_Enter_Ocu_SetAbsoluteThreshold
(
    void
);

extern void SchM_Exit_Ocu_SetAbsoluteThreshold
(
    void
);

extern void SchM_Enter_Ocu_SetRelativeThreshold
(
    void
);

extern void SchM_Exit_Ocu_SetRelativeThreshold
(
    void
);

extern void SchM_Enter_Ocu_StopChannel
(
  void
);

extern void SchM_Exit_Ocu_StopChannel
(
  void
);

extern void SchM_Enter_Ocu_SetPinAction
(
  void
);

extern void SchM_Exit_Ocu_SetPinAction
(
  void
);

extern void SchM_Enter_Ocu_EnableNotification
(
  void
);

extern void SchM_Exit_Ocu_EnableNotification
(
  void
);

extern void SchM_Enter_Ocu_DisableNotification
(
  void
);

extern void SchM_Exit_Ocu_DisableNotification
(
  void
);

#endif /* SCHM_OCU_H */
