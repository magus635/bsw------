/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Spi.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : ESPI
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

#ifndef SCHM_SPI_H_
#define SCHM_SPI_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
extern void SchM_Enter_Spi_WriteIB(void);

extern void SchM_Exit_Spi_WriteIB(void);

extern void SchM_Enter_Spi_ReadIB(void);

extern void SchM_Exit_Spi_ReadIB(void);

extern void SchM_Enter_Spi_SetupEB(void);

extern void SchM_Exit_Spi_SetupEB(void);

extern void SchM_Enter_Spi_SyncTransmit(void);

extern void SchM_Exit_Spi_SyncTransmit(void);

extern void SchM_Enter_Spi_AsyncTransmit(void);

extern void SchM_Exit_Spi_AsyncTransmit(void);

extern void SchM_Enter_Spi_SetAsyncMode(void);

extern void SchM_Exit_Spi_SetAsyncMode(void);

extern void SchM_Enter_Spi_IsrError(void);

extern void SchM_Exit_Spi_IsrError(void);

extern void SchM_Enter_Spi_DeInit(void);

extern void SchM_Exit_Spi_DeInit(void);

extern void SchM_Enter_Spi_GetStatus(void);

extern void SchM_Exit_Spi_GetStatus(void);

#endif /* SCHM_SPI_H_ */
