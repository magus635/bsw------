/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Sent_Demo.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : SENT
*
*   brief                 : This file contains Demo application for Sent Driver
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
#include "Sent_Demo.h"

#include "Demo_Common.h"
#include "Sent.h"
#include "Intc.h"

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/
/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
#define SENT_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32
#include "Sent_MemMap.h"
uint32 Sent_Data[SENT_HW_MAX_CHANNELS];
Sent_RxSerialDataType Sent_SlowData[SENT_HW_MAX_CHANNELS];
Sent_ChanStatusType Sent_State[SENT_HW_MAX_CHANNELS];

uint32 Sent_Init_Status = 0;

#define SENT_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32
#include "Sent_MemMap.h"

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
typedef struct
{
    uint8 CoreCmdExist;    /* This variable can only be changed by Core0(master) */
    uint8 CoreExeCmd;
} Sent_ChannelCoreExeType;

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#define SENT_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
#include "Sent_MemMap.h"

#define SENT_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
#include "Sent_MemMap.h"

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
#define SENT_START_SEC_CODE_ASIL_D_GLOBAL
#include "Sent_MemMap.h"

/****************************************************************************************************
*   Function Name           : Sent_DemoEntry
*
*   Service ID              : None.
*
*   Description             : Sent demo application entry.
*                             Select which core to use to run Sent demo.
*                             This APi shall be called by main core(Core 0).
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : None
*
****************************************************************************************************/
void Sent_DemoEntry(void)
{
    char cmd;
    uint8 ChannelId = 0U;
    int pollMode = 1;

    if(!Sent_Init_Status)
    {
        Sent_Init(&Sent_ConfigSet);
        Sent_Init_Status++;
    }

restart:
    DEBUG_PRINTF("\n/*********************************************************/\n");
    DEBUG_PRINTF("\n                SENT DRIVER CONFIG INFORMATION             \n ");
    DEBUG_PRINTF("\n                                                          \n ");
#if defined(THA6_THA6104)
    DEBUG_PRINTF("     0:  Sent 0 map to SENT_SPC2 (SPC by SOFT) on P0.3  \n ");
    DEBUG_PRINTF("     1:  Sent 1 map to SENT4C                  on P33.6 \n ");
    DEBUG_PRINTF("     2:  Sent 2 map to SENT_SPC5 (SPC by GTM)  on P0.6  \n ");
    DEBUG_PRINTF("\n/*********************************************************/\n");
    DEBUG_PRINTF("\n  Enter Logic Channel Num(SentChLogiIndex):0~2 ");
#else
    DEBUG_PRINTF("     0:  Sent 0 map to SENT2B                  on P0.3 \n  ");
    DEBUG_PRINTF("     1:  Sent 1 map to SENT_SPC3 (SPC by SOFT) on P0.4 \n  ");
    DEBUG_PRINTF("     2:  Sent 2 map to SENT_SPC6 (SPC by GTM)  on P0.7 \n  ");
    DEBUG_PRINTF("     3:  Sent 3 map to SENT_SPC7               on P0.8 \n  ");
    DEBUG_PRINTF("     4:  Sent 4 map to SENT9C                  on P33.1 \n ");
    DEBUG_PRINTF("     5:  Sent 4 map to SENT5C                  on P33.5 \n ");
    DEBUG_PRINTF("\n/*********************************************************/\n");
    DEBUG_PRINTF("\n  Enter Logic Channel Num(SentChLogiIndex):0~5 ");
#endif /* THA6_THA6104 */
    cmd = DEBUG_GETC();

    ChannelId = cmd - '0';
    if(ChannelId > 9)
    {
        ChannelId = 0;
    }

    while (1)
    {
        DEBUG_PRINTF("\n");
        DEBUG_PRINTF("\n/**************** For Logic Channel Id: %d *****************/", ChannelId);
        DEBUG_PRINTF("\n/*********************************************************/\n");
        DEBUG_PRINTF("     1.  Enable SENT Channel                                \n");
        DEBUG_PRINTF("     2.  Disable SENT Channel                               \n");
        DEBUG_PRINTF("     3.  Get SENT Channel Data and Status (Interrupt mode)  \n");
        DEBUG_PRINTF("     4.  Get SENT Channel Data and Status (Poll mode)       \n");
#if (SENT_SPC_USED == STD_ON)
        DEBUG_PRINTF("     5.  Start SPC Sync Master Pulse                        \n");
#endif
        DEBUG_PRINTF("     6.  Get Sent version information                        \n");
        DEBUG_PRINTF("     7.  Interrupt mode %s\n", pollMode? "":"(Current)");
        DEBUG_PRINTF("     8.  Poll mode %s\n", pollMode? "(Current)":"");
        DEBUG_PRINTF("     x.  Reconfigure SENT Channel                            \n");
        DEBUG_PRINTF("     q.  Go back to Main Menu.                               \n");
        DEBUG_PRINTF("                                                             \n");
        DEBUG_PRINTF("\n/*********************************************************/\n");
        DEBUG_PRINTF("  Enter Your Option : ");

        cmd = DEBUG_GETC();

        switch (cmd)
        {
            case '1':
            {
                Sent_SetChannel(ChannelId, SENT_ENABLE);
                break;
            }

            case '2' :
            {
                Sent_SetChannel(ChannelId, SENT_DISABLE);
                break;
            }

            case '3' :
            {
                DEBUG_PRINTF("\n");
                DEBUG_PRINTF("Data: %x\r\n", (unsigned int)Sent_Data[ChannelId]);
                DEBUG_PRINTF("Serial.Data: %x\r\n", (unsigned int)Sent_SlowData[ChannelId].Data);
                DEBUG_PRINTF("Serial.MsgId: %x\r\n", (unsigned int)Sent_SlowData[ChannelId].MsgId);
                DEBUG_PRINTF("Serial.Crc: %x\r\n", (unsigned int)Sent_SlowData[ChannelId].Crc);
                DEBUG_PRINTF("Serial.Configuration: %x\r\n", (unsigned int)Sent_SlowData[ChannelId].Configuration);
                DEBUG_PRINTF("Sent_CrcErr: %x\r\n", (unsigned int)Sent_State[ChannelId].IsCRCErr);
                DEBUG_PRINTF("Sent_FrameErr: %x\r\n", (unsigned int)Sent_State[ChannelId].IsFrameErr);
                DEBUG_PRINTF("Sent_SlowCrcErr: %x\r\n", (unsigned int)Sent_State[ChannelId].IsSlowCRCErr);
                DEBUG_PRINTF("Sent_SlowFrameErr: %x\r\n", (unsigned int)Sent_State[ChannelId].IsSlowFrameErr);
                break;
            }

            case '4' :
            {
                DEBUG_PRINTF("\n");
                Sent_ReadChannelStatus(ChannelId, &Sent_State[ChannelId]);
                if(Sent_State[ChannelId].IsDone != 0U)
                {
                    /* The fast channel serial message is done. */
                    Sent_Data[ChannelId] = Sent_ReadData(ChannelId);
                    DEBUG_PRINTF("Data: %x\r\n", (unsigned int)Sent_Data[ChannelId]);
                }

                if(Sent_State[ChannelId].IsSlowDone != 0U)
                {
                    Sent_ReadSerialData(ChannelId, &Sent_SlowData[ChannelId]);
                    DEBUG_PRINTF("Serial.Data: %x\r\n", (unsigned int)Sent_SlowData[ChannelId].Data);
                    DEBUG_PRINTF("Serial.MsgId: %x\r\n", (unsigned int)Sent_SlowData[ChannelId].MsgId);
                    DEBUG_PRINTF("Serial.Crc: %x\r\n", (unsigned int)Sent_SlowData[ChannelId].Crc);
                    DEBUG_PRINTF("Serial.Configuration: %x\r\n", (unsigned int)Sent_SlowData[ChannelId].Configuration);
                }

                DEBUG_PRINTF("Sent_CrcErr: %x\r\n", (unsigned int)Sent_State[ChannelId].IsCRCErr);
                DEBUG_PRINTF("Sent_FrameErr: %x\r\n", (unsigned int)Sent_State[ChannelId].IsFrameErr);
                DEBUG_PRINTF("Sent_SlowCrcErr: %x\r\n", (unsigned int)Sent_State[ChannelId].IsSlowCRCErr);
                DEBUG_PRINTF("Sent_SlowFrameErr: %x\r\n", (unsigned int)Sent_State[ChannelId].IsSlowFrameErr);
                DEBUG_PRINTF("\r\nSENT Channel status:");
                break;
            }

    #if (SENT_SPC_USED == STD_ON)
            case '5' :
            {
                Sent_SpcGenPulse(ChannelId);
                break;
            }
    #endif
            case '6' :
            {
                DEBUG_PRINTF("\n");
                Std_VersionInfoType Version;
                Sent_GetVersionInfo(&Version);
                DEBUG_PRINTF("vendorID: %x\r\n",        Version.vendorID);
                DEBUG_PRINTF("moduleID: %x\r\n",        Version.moduleID);
                DEBUG_PRINTF("sw_major_version: %x\r\n",Version.sw_major_version);
                DEBUG_PRINTF("sw_minor_version: %x\r\n",Version.sw_minor_version);
                DEBUG_PRINTF("sw_patch_version: %x\r\n",Version.sw_patch_version);
                break;
            }

            case '7' :
            {
#if defined(THA6_THA6104)
                Intc_EnableInterrupt(INTC_INTSRC_SENT2_RX_ERROR);
                Intc_EnableInterrupt(INTC_INTSRC_SENT2_RX_VALID);

                Intc_EnableInterrupt(INTC_INTSRC_SENT4_RX_ERROR);
                Intc_EnableInterrupt(INTC_INTSRC_SENT4_RX_VALID);

                Intc_EnableInterrupt(INTC_INTSRC_SENT5_RX_ERROR);
                Intc_EnableInterrupt(INTC_INTSRC_SENT5_RX_VALID);
#else
                Intc_EnableInterrupt(INTC_INTSRC_SENT2_RX_ERROR);
                Intc_EnableInterrupt(INTC_INTSRC_SENT2_RX_VALID);

                Intc_EnableInterrupt(INTC_INTSRC_SENT3_RX_ERROR);
                Intc_EnableInterrupt(INTC_INTSRC_SENT3_RX_VALID);

                Intc_EnableInterrupt(INTC_INTSRC_SENT6_RX_ERROR);
                Intc_EnableInterrupt(INTC_INTSRC_SENT6_RX_VALID);
#endif /* THA6_THA6104 */                

                pollMode = 0;
                break;
            }

            case '8' :
            {
#if defined(THA6_THA6104)
                Intc_DisableInterrupt(INTC_INTSRC_SENT2_RX_ERROR);
                Intc_DisableInterrupt(INTC_INTSRC_SENT2_RX_VALID);

                Intc_DisableInterrupt(INTC_INTSRC_SENT4_RX_ERROR);
                Intc_DisableInterrupt(INTC_INTSRC_SENT4_RX_VALID);

                Intc_DisableInterrupt(INTC_INTSRC_SENT5_RX_ERROR);
                Intc_DisableInterrupt(INTC_INTSRC_SENT5_RX_VALID);
#else
                Intc_DisableInterrupt(INTC_INTSRC_SENT2_RX_ERROR);
                Intc_DisableInterrupt(INTC_INTSRC_SENT2_RX_VALID);

                Intc_DisableInterrupt(INTC_INTSRC_SENT3_RX_ERROR);
                Intc_DisableInterrupt(INTC_INTSRC_SENT3_RX_VALID);

                Intc_DisableInterrupt(INTC_INTSRC_SENT6_RX_ERROR);
                Intc_DisableInterrupt(INTC_INTSRC_SENT6_RX_VALID);
                pollMode = 1;
#endif /* THA6_THA6104 */   
                break;
            }

            case 'x':
            case 'X':
                goto restart;

            case 'q':
            case 'Q':
                goto exit;

            default :
                DEBUG_PRINTF(" \n\n Invalid option \n ");
                break;
        }
    }
exit:
    Sent_DeInit();
}

/*******************************************************************************
** Syntax : Sent_DemoAppCbk (Sent_ChannelIdxType ChannelId,                   **
**                                         Sent_NotifType Stat)               **
**                                                                            **
** Service ID:   : NA                                                         **
**                                                                            **
** Sync/Async:   : Synchronous                                                **
**                                                                            **
** Reentrancy:   : Non Reentrant                                              **
**                                                                            **
** Parameters (in): ChannelId - SENT logical channel number                   **
**                  Stat - Interrupt Status                                   **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : API for checking Sent Channel events in interrupt mode       **
**                                                                            **
*******************************************************************************/
void Sent_DemoAppCbk (Sent_ChannelIdxType ChannelId, Sent_NotifType *StatPtr)
{
    if(StatPtr->IsDone != 0U)
    {
        /* The fast channel serial message is done. */
        Sent_Data[ChannelId] = Sent_ReadData(ChannelId);
    }

    if(StatPtr->IsSlowDone != 0U)
    {
        Sent_ReadSerialData(ChannelId, &Sent_SlowData[ChannelId]);
    }

    Sent_State[ChannelId] = *StatPtr;
}

/* Call-out function for Channel 0 */
void Sent_CalloutChan0 (Sent_ChannelIdxType ChannelId, Sent_NotifType *pState)
{
    Sent_DemoAppCbk(ChannelId, pState);
}
void Sent_ErrCalloutChan0 (Sent_ChannelIdxType ChannelId, Sent_NotifType *pState)
{
    Sent_DemoAppCbk(ChannelId, pState);
}

void Sent_CalloutChan1 (Sent_ChannelIdxType ChannelId, Sent_NotifType *pState)
{
    Sent_DemoAppCbk(ChannelId, pState);
}
void Sent_ErrCalloutChan1 (Sent_ChannelIdxType ChannelId, Sent_NotifType *pState)
{
    Sent_DemoAppCbk(ChannelId, pState);
}

void Sent_CalloutChan2 (Sent_ChannelIdxType ChannelId, Sent_NotifType *pState)
{
    Sent_DemoAppCbk(ChannelId, pState);
}
void Sent_ErrCalloutChan2 (Sent_ChannelIdxType ChannelId, Sent_NotifType *pState)
{
    Sent_DemoAppCbk(ChannelId, pState);
}

void Sent_CalloutChan3 (Sent_ChannelIdxType ChannelId, Sent_NotifType *pState)
{
    Sent_DemoAppCbk(ChannelId, pState);
}
void Sent_ErrCalloutChan3 (Sent_ChannelIdxType ChannelId, Sent_NotifType *pState)
{
    Sent_DemoAppCbk(ChannelId, pState);
}

void Sent_CalloutChan4 (Sent_ChannelIdxType ChannelId, Sent_NotifType *pState)
{
    Sent_DemoAppCbk(ChannelId, pState);
}
void Sent_ErrCalloutChan4 (Sent_ChannelIdxType ChannelId, Sent_NotifType *pState)
{
    Sent_DemoAppCbk(ChannelId, pState);
}

void Sent_CalloutChan5 (Sent_ChannelIdxType ChannelId, Sent_NotifType *pState)
{
    Sent_DemoAppCbk(ChannelId, pState);
}
void Sent_ErrCalloutChan5 (Sent_ChannelIdxType ChannelId, Sent_NotifType *pState)
{
    Sent_DemoAppCbk(ChannelId, pState);
}

void Sent_CalloutChan6 (Sent_ChannelIdxType ChannelId, Sent_NotifType *pState)
{
    Sent_DemoAppCbk(ChannelId, pState);
}
void Sent_ErrCalloutChan6 (Sent_ChannelIdxType ChannelId, Sent_NotifType *pState)
{
    Sent_DemoAppCbk(ChannelId, pState);
}

void Sent_CalloutChan7 (Sent_ChannelIdxType ChannelId, Sent_NotifType *pState)
{
    Sent_DemoAppCbk(ChannelId, pState);
}
void Sent_ErrCalloutChan7 (Sent_ChannelIdxType ChannelId, Sent_NotifType *pState)
{
    Sent_DemoAppCbk(ChannelId, pState);
}

void Sent_CalloutChan8 (Sent_ChannelIdxType ChannelId, Sent_NotifType *pState)
{
    Sent_DemoAppCbk(ChannelId, pState);
}
void Sent_ErrCalloutChan8 (Sent_ChannelIdxType ChannelId, Sent_NotifType *pState)
{
    Sent_DemoAppCbk(ChannelId, pState);
}

void Sent_CalloutChan9 (Sent_ChannelIdxType ChannelId, Sent_NotifType *pState)
{
    Sent_DemoAppCbk(ChannelId, pState);
}
void Sent_ErrCalloutChan9 (Sent_ChannelIdxType ChannelId, Sent_NotifType *pState)
{
    Sent_DemoAppCbk(ChannelId, pState);
}

#define SENT_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Sent_MemMap.h"


