/****************************************************************************************************
 *
****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Spi.h
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : Espi
 *
 *   brief                 : This file contains all function declarations of Spi Driver
 *
 *   Autosar Version       : 4.4.0
 *
 *   Build Version         : Cortex-R52+/THA6xxx
 *
 *   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
 *
****************************************************************************************************/
/*
*#Violation Summary
*
*#Spi_h_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*/
#ifndef SPI_H_
#define SPI_H_
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Spi_Cfg.h"
#include "Spi_PBcfg.h"
#include "Std_Types.h"
#include "Spi_Version.h"
#include "Spi_GeneralTypes.h"
#if (SPI_ENABLE_DMA == STD_ON)
#include "Dma.h"
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
/* Error Values */
/* SWS_Spi_00004: Service is called with wrong Channel parameter */
#define SPI_E_PARAM_CHANNEL                ((uint8)0x0AU)
/* SWS_Spi_00237: Service is called with wrong Job parameter */
#define SPI_E_PARAM_JOB                    ((uint8)0x0BU)
/* SWS_Spi_00238: Service is called with wrong Seq parameter */
#define SPI_E_PARAM_SEQ                    ((uint8)0x0CU)
/* SWS_Spi_00240: Service is called with wrong Length parameter */
#define SPI_E_PARAM_LENGTH                 ((uint8)0x0DU)
/* SWS_Spi_00241: Service is called with uninitialized parameters */
#define SPI_E_PARAM_UNIT                   ((uint8)0x0EU)
/* SWS_Spi_00371: Service is called with NULL parameter */
#define SPI_E_PARAM_POINTER                ((uint8)0x10U)
/*  SWS_Spi_00242: Service is called used without module initialization */
#define SPI_E_UNINIT                       ((uint8)0x1AU)
/* SWS_Spi_00243: Service is called with pending Sequence parameter */
#define SPI_E_SEQ_PENDING                  ((uint8)0x2AU)
/* SWS_Spi_00245: Synchronous transmission service called at wrong time */
#define SPI_E_SEQ_IN_PROCESS               ((uint8)0x3AU)
/* SWS_Spi_00246: SPI_Init service called while the SPI driver has already been initialized time */
#define SPI_E_ALREADY_INITIALIZED          ((uint8)0x4AU)

/* Non-AUTOSAR */
/* Report DET SPI module not Job is assigned to the current Sequence */
#define SPI_E_SEQ_EMPTY                    ((uint8)0xA0U)
/* Report DET SPI module not Channel is assigned to the current Job */
#define SPI_E_JOB_EMPTY                    ((uint8)0xA1U)
/* Report DET SPI module not configured for current Core */
#define SPI_E_CORE_NOT_CONFIGURED          ((uint8)0xA2U)
/* The pointer point to a address is NULL, such as 'Spi_CoreStatus'.*/
#define SPI_E_CORE_NOT_STATUS_STORAGEVAR   ((uint8)0xA3U)
/* SPI Sequence is not allocated to current core or out of range */
#define SPI_E_CORE_SEQUENCE_MISMATCH       ((uint8)0xA4U)
/* SPI Job is not allocated to current core or out of range */
#define SPI_E_CORE_JOB_MISMATCH            ((uint8)0xA5U)
/* SPI Channel is not allocated to current core or out of range */
#define SPI_E_CORE_CHANNEL_MISMATCH        ((uint8)0xA6U)
/* SPI PhyUnit is not allocated to current core */
#define SPI_E_CORE_HWUNIT_MISMATCH         ((uint8)0xA8U)
/* The generated EB configuration parameters have not been initialized */
#define SPI_E_PARAM_EB_UNIT                ((uint8)0xA9U)

/* Non-AUTOSAR: Used by error Interrupt*/
/* Report DET SPI module Parity Error (Master/Slave) */
#define SPI_E_STATE_PARITY_ERROR           ((uint8)0xE0U)
/* Report DET SPI module Unexpected Configuration Error (Master/Slave) */
#define SPI_E_STATE_UNEXPECTCONFIG_ERROR   ((uint8)0xE1U)
/* Report DET SPI module TXFIFO Overflow Error (Master/Slave) */
#define SPI_E_STATE_TXFIFO_OVERFLOW_ERROR  ((uint8)0xE3U)
/* Report DET SPI module RXFIFO Overflow Error (Master/Slave) */
#define SPI_E_STATE_RXFIFO_OVERFLOW_ERROR  ((uint8)0xE5U)
/* Report DET SPI module RXFIFO Underflow Error (Master/Slave) */
#define SPI_E_STATE_UNKNOWN_ERROR          ((uint8)0xE7U)
/* Report DET SPI module safety mechanism check error */
#define SPI_E_SAFETY_ERROR                 ((uint8)0xE8U)
/* Report DET SPI module safety mechanism check error */
#define SPI_E_TIMEOUT_ERROR                ((uint8)0xE9U)

/* SWS_Spi_00175: Spi_Init Service ID. */
#define SPI_SID_INIT                       ((uint8)0x00U)
/* SWS_Spi_00176: Spi_DeInit Service ID. */
#define SPI_SID_DEINIT                     ((uint8)0x01U)
/* SWS_Spi_00177: Spi_WriteIB Service ID. */
#define SPI_SID_WRITEIB                    ((uint8)0x02U)
/* SWS_Spi_00178: Spi_AsyncTransmit Service ID. */
#define SPI_SID_ASYNCTRANSMIT              ((uint8)0x03U)
/* SWS_Spi_00179: Spi_ReadIB Service ID. */
#define SPI_SID_READIB                     ((uint8)0x04U)
/* SWS_Spi_00180: Spi_SetupEB Service ID. */
#define SPI_SID_SETUPEB                    ((uint8)0x05U)
/* SWS_Spi_00181: Spi_GetStatus Service ID. */
#define SPI_SID_GETSTATUS                  ((uint8)0x06U)
/* SWS_Spi_00182: Spi_GetJobResult Service ID. */
#define SPI_SID_GETJOBRESULT               ((uint8)0x07U)
/* SWS_Spi_00183: Spi_GetSequenceResult Service ID. */
#define SPI_SID_GETSEQUENCERESULT          ((uint8)0x08U)
/* SWS_Spi_00184: Spi_GetVersionInfo Service ID. */
#define SPI_SID_GETVERSIONINFO             ((uint8)0x09U)
/* SWS_Spi_00185: Spi_SyncTransmit Service ID. */
#define SPI_SID_SYNCTRANSMIT               ((uint8)0x0AU)
/* SWS_Spi_00186: Spi_GetHWUnitStatus Service ID. */
#define SPI_SID_GETHWUNITSTATUS            ((uint8)0x0BU)
/* SWS_Spi_00187: Spi_Cancel Service ID. */
#define SPI_SID_CANCEL                     ((uint8)0x0CU)
/* SWS_Spi_00188: Spi_SetAsyncMode Service ID. */
#define SPI_SID_SETASYNCMODE               ((uint8)0x0DU)
/* SWS_Spi_00189: Spi_MainFunction_Handling Service ID. */
#define SPI_SID_MAINFUNCTION_HANDLING      ((uint8)0x10U)

/* Non-AUTOSAR */
/* Service ID for interrupt handler - Fifo Rx interrupt */
#define SPI_SID_FIFO_RX_ISR                ((uint8)0xE0U)
/* Service ID for interrupt handler - error interrupt */
#define SPI_SID_ERROR_ISR                  ((uint8)0xE1U)
/* Service ID for Dma Notification handler */
#define SPI_SID_DMA_NOTIFICATION           ((uint8)0xE2U)
/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/
/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/
/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
/* #Violation: Spi_h_REF_1 */
#define SPI_START_SEC_CODE_ASIL_D_GLOBAL
#include "Spi_MemMap.h"
/************************************* General API *************************************************/
extern FUNC(void, SPI_PUBLIC_CODE) Spi_Init
(
    P2CONST(Spi_ConfigType, AUTOMATIC, SPI_APPL_CONST) ConfigPtr
);
extern FUNC(Std_ReturnType, SPI_PUBLIC_CODE) Spi_DeInit
(
    void
);

#if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE0) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE2))
extern FUNC(Std_ReturnType, SPI_PUBLIC_CODE) Spi_WriteIB
(
    Spi_ChannelType Channel,
    P2CONST(Spi_DataBufferType, AUTOMATIC, SPI_APPL_CONST) DataBufferPtr
);
#endif /* ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE0) \|| (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE2)) */

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
extern FUNC(Std_ReturnType, SPI_PUBLIC_CODE) Spi_AsyncTransmit
(
    Spi_SequenceType Sequence
);

#if (SPI_ENABLE_DMA == STD_ON)
extern FUNC(void, SPI_PUBLIC_CODE) Spi_DmaNotification
(
    Dma_ChannelType Channel,
    Dma_ChEventType ChIntrEvt
);
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */

#if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE0) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE2))
extern FUNC(Std_ReturnType, SPI_PUBLIC_CODE) Spi_ReadIB
(
    Spi_ChannelType Channel,
    P2VAR(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) DataBufferPtr
);
#endif /* ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE0) \|| (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE2)) */

#if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE1) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE2))
extern FUNC(Std_ReturnType, SPI_PUBLIC_CODE) Spi_SetupEB
(
    Spi_ChannelType Channel,
    P2CONST(Spi_DataBufferType, AUTOMATIC, SPI_APPL_CONST) SrcDataBufferPtr,
    P2VAR(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) DesDataBufferPtr,
    Spi_NumberOfDataType Length
);
#endif /* ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE1) \|| (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE2)) */

extern FUNC(Spi_StatusType, SPI_PUBLIC_CODE) Spi_GetStatus
(
    void
);
extern FUNC(Spi_JobResultType, SPI_PUBLIC_CODE) Spi_GetJobResult
(
    Spi_JobType Job
);
extern FUNC(Spi_SeqResultType, SPI_PUBLIC_CODE) Spi_GetSequenceResult
(
    Spi_SequenceType Sequence
);

#if (SPI_VERSION_INFO_API == STD_ON)
extern FUNC(void, SPI_PUBLIC_CODE) Spi_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, SPI_APPL_DATA) VersionInfoPtr
);
#endif /* (SPI_VERSION_INFO_API  \== STD_ON) */

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
extern FUNC(Std_ReturnType, SPI_PUBLIC_CODE) Spi_SyncTransmit
(
    Spi_SequenceType Sequence
);
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */

#if (SPI_HW_STATUS_API == STD_ON)
extern FUNC(Spi_StatusType, SPI_PUBLIC_CODE) Spi_GetHWUnitStatus
(
    Spi_HWUnitType HWUnit
);
#endif /* (SPI_HW_STATUS_API  \== STD_ON) */

#if (SPI_CANCEL_API == STD_ON)
extern FUNC(void, SPI_PUBLIC_CODE) Spi_Cancel
(
    Spi_SequenceType Sequence
);
#endif /* (SPI_CANCEL_API  \== STD_ON) */

#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
extern FUNC(Std_ReturnType, SPI_PUBLIC_CODE) Spi_SetAsyncMode
(
    Spi_AsyncModeType   Mode
);

extern FUNC(void, SPI_PUBLIC_CODE) Spi_MainFunction_Handling
(
    void
);
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
extern FUNC(void, SPI_PUBLIC_CODE) Spi_FifoRx_ISRHandler
(
    Spi_HWUnitType PhyUnit
);
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */

extern FUNC(void, SPI_PUBLIC_CODE) Spi_Error_ISRHandler
(
    Spi_HWUnitType PhyUnit
);

/* #Violation: Spi_h_REF_1 */
#define SPI_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Spi_MemMap.h"

#endif /* SPI_H */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
