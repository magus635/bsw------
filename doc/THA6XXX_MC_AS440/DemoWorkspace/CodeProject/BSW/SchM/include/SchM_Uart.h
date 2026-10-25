/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Uart.h
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

#ifndef SCHM_UART_H_
#define SCHM_UART_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
extern void SchM_Enter_Uart_Init(void);
extern void SchM_Exit_Uart_Init(void);

extern void SchM_Enter_Uart_GetStatus(void);
extern void SchM_Exit_Uart_GetStatus(void);

extern void SchM_Enter_Uart_Write(void);
extern void SchM_Exit_Uart_Write(void);

extern void SchM_Enter_Uart_Read(void);
extern void SchM_Exit_Uart_Read(void);

extern void SchM_Enter_Uart_DeInit(void);
extern void SchM_Exit_Uart_DeInit(void);

#endif /* SCHM_UART_H_ */
