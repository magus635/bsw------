/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : LinIf.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : ASI
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


#ifndef LIN_IF_H
#define LIN_IF_H

#include "ComStack_Types.h"
#include "Lin.h"
#include "EcuM.h"

#if (LIN_WAKEUP_SUPPORT == STD_ON)
extern FUNC(Std_ReturnType, LINIF_CODE) LinIf_CheckWakeup
(
    EcuM_WakeupSourceType WakeupSource
);
#endif

extern FUNC(void, LINIF_CODE) LinIf_LinErrorIndication
(
    NetworkHandleType Channel,
    Lin_SlaveErrorType ErrorStatus
);

extern FUNC(void, LINIF_CODE) LinIf_TxConfirmation
(
    NetworkHandleType Channel
);

extern FUNC(void, LINIF_CODE) LinIf_RxIndication
(
    NetworkHandleType Channel,
    uint8* Lin_SduPtr
);

extern FUNC(Std_ReturnType, LINIF_CODE) LinIf_HeaderIndication
(
    NetworkHandleType Channel,
    Lin_PduType* PduPtr
);

#if (LIN_WAKEUP_SUPPORT == STD_ON)
extern FUNC(void, LINIF_CODE) LinIf_WakeupConfirmation
(
    EcuM_WakeupSourceType WakeupSource
);

FUNC(Std_ReturnType, LINIF_CODE) LinIf_CheckWakeup
(
    EcuM_WakeupSourceType WakeupSource
);
#endif
#endif /* LIN_IF_H */

