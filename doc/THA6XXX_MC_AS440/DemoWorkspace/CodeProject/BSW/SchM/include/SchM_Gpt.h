/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Gpt.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-TOM
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
#ifndef SCHM_GPT_H
#define SCHM_GPT_H

#include "Std_Types.h"

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
extern void SchM_Enter_Gpt_StartTimer
(
        void
);

extern void SchM_Exit_Gpt_StartTimer
(
        void
);

extern void SchM_Enter_Gpt_StopTimer
(
        void
);

extern void SchM_Exit_Gpt_StopTimer
(
        void
);

extern void SchM_Enter_Gpt_EnableNotification
(
        void
);

extern void SchM_Exit_Gpt_EnableNotification
(
        void
);

extern void SchM_Enter_Gpt_DisableNotification
(
        void
);

extern void SchM_Exit_Gpt_DisableNotification
(
        void
);

extern void SchM_Enter_Gpt_SetMode
(
        void
);

extern void SchM_Exit_Gpt_SetMode
(
        void
);

#endif /* SCHM_GPT_H */
