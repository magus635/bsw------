/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : LinIf.c
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


#include "Lin.h"
#include "Lin_GeneralTypes.h"
#include "LinIf.h"
#include "Dem.h"
#include "EcuM.h"
#include "LinIf_Cbk.h"
#if (LIN_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
#include "Mcall.h"

#define LINIF_HEADER_RECV                 (1U) /* Compatible with LIN_HEADER_RECV */
#define LINIF_RX_INDC                     (2U) /* Compatible with LIN_RX_INDC     */
#define LINIF_TX_INDC                     (3U) /* Compatible with LIN_TX_INDC     */

extern uint8 *Lin_SlaveSduPtr;
extern uint8 Lin_ResponseStatus;

FUNC(void, LINIF_CODE) LinIf_LinErrorIndication
(
    NetworkHandleType Channel,
    Lin_SlaveErrorType ErrorStatus
)
{
    (void)Channel;
    (void)ErrorStatus;
    return;
}

FUNC(void, LINIF_CODE) LinIf_TxConfirmation
(
    NetworkHandleType Channel
)
{
    (void)Channel;
    Lin_ResponseStatus = LINIF_TX_INDC;
    return;
}

FUNC(void, LINIF_CODE) LinIf_RxIndication
(
    NetworkHandleType Channel,
    uint8* Lin_SduPtr
)
{
    uint8 i;

    (void)Channel;
    Lin_ResponseStatus = LINIF_RX_INDC;
    for (i = 0U; i < 8U; i++)
    {
        Lin_SlaveSduPtr[i] = Lin_SduPtr[i];
    }
    return;
}

FUNC(Std_ReturnType, LINIF_CODE) LinIf_HeaderIndication
(
    NetworkHandleType Channel,
    Lin_PduType* PduPtr
)
{
    Std_ReturnType RetVal;
    uint8 i;

    (void)Channel;
    Lin_ResponseStatus = LINIF_HEADER_RECV;
    RetVal = E_OK;
    PduPtr->Cs = LIN_ENHANCED_CS;
    PduPtr->Dl = 8U;
    if (0x2E == PduPtr->Pid)
    {
        PduPtr->Drc = LIN_FRAMERESPONSE_TX;
        for (i = 0U; i < 8U; i++)
        {
            PduPtr->SduPtr[i] = i;
        }
    }
    else if (0x20 == PduPtr->Pid)
    {
        PduPtr->Drc = LIN_FRAMERESPONSE_RX;
    }
    else if (0x80 == PduPtr->Pid)
    {
        PduPtr->Drc = LIN_FRAMERESPONSE_IGNORE;
    }
    else
    {
        RetVal = E_NOT_OK;
    }

    return RetVal;
}

#if (LIN_WAKEUP_SUPPORT == STD_ON)

FUNC(void, LINIF_CODE) LinIf_WakeupConfirmation
(
    EcuM_WakeupSourceType WakeupSource
)
{
    return;
}


FUNC(Std_ReturnType, LINIF_CODE) LinIf_CheckWakeup
(
    EcuM_WakeupSourceType WakeupSource
)
{
    Std_ReturnType Std_Return=0;


    return Std_Return;
}
 
#endif


/* End of File */
