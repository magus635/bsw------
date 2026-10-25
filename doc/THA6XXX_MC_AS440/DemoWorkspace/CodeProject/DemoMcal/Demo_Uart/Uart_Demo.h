/****************************************************************************************************
 *
****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Uart_Demo.h
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : ASI
 *
 *   brief                 : This file contains all function declarations of ASI Driver
 *
 *   Autosar Version       : 4.4.0
 *
 *   Build Version         : Cortex-R52+/THA6xxx
 *
 *   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
 *
****************************************************************************************************/

/****************************************************************************************************
**                          WARNING!!!                                                             **
* All APIs covered in Uart_Demo.c and Uart_Demo.h are only suitable for Demo testing and           **
* provide no functionality or performance guarantees for OTHER PROJECTS.                           **
****************************************************************************************************/

#ifndef UART_DEMO_H_
#define UART_DEMO_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"
#include "Platform_Types.h"
#include "stdarg.h"
#include "Uart.h"
#include "Demo_Common.h"
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/* Redefine the logical channel ID of Debug printing */
#define DebugChannel                    UartConf_UartChannel_DebugChannel
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
/* Type for printf data type */
typedef struct
{
    char         *BufferPtr;
    uint8        *SizePtr;
    boolean     DirectPrintFlag;
} PrintfbufferType;

typedef union {
    float64 f64;
    uint64 u64;
} F64Union;

typedef union {
    float32 f32;
    uint32 u32;
}F32Union;

#if (STD_ON == DEMO_PRINTQUEUEMODE)
/* Define the width of the single-level Queue */
#define PRINTF_EACH_BUFFER_LEN        (256U)
/* Define the overall depth of the Queue */
#define PRINTF_QUEUE_DEPTH            (10U)
/* Define the overall storage amount of the Queue */
#define PRINTF_QUEUE_BUFFER_LEN       (PRINTF_EACH_BUFFER_LEN * PRINTF_QUEUE_DEPTH)
/* Index position of cross core communication data length */
#define MCAL_CORE_COMM_LEN_POS         (0U)
/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/
typedef struct
{
    uint8         data[PRINTF_EACH_BUFFER_LEN];
    uint16        size;
} TXDataBufferType;
/*********************************Define Queue related data types**********************************/
/* Type for queue length */
typedef uint16   Mcal_QueueLenType;

/* Type for sequence queue */
typedef struct
{
    /* Pointer to the buffer that save the data */
    uint8                  *QueueElemPtr;
    /* Buffer length of queue(unit: Byte) */
    Mcal_QueueLenType      QueueSize;
    /* First position index of queue */
    Mcal_QueueLenType      QueueFront;
    /* Last position index of queue */
    Mcal_QueueLenType      QueueRear;
    /* Valid Element count */
    Mcal_QueueLenType      QueueCount;
} Mcal_SeqQueueType;

typedef enum
{
    /* Queue is empty */
    MCAL_QUEUE_EMPTY = 0,
    /* Queue is full */
    MCAL_QUEUE_FULL,
    /* Queue is normal */
    MCAL_QUEUE_NORMAL,
    /* Queue element is not initialization */
    MCAL_QUEUE_NOT_INIT,
    /* Queue is not pointer a valid address */
    MCAL_QUEUE_NULL,
    /* Queue buffer is not pointer a valid address */
    MCAL_QUEUE_BUF_NULL,
    /* Queue length is 0 */
    MCAL_QUEUE_LEN_ZERO,
    /* Invalid data */
    MCAL_QUEUE_DATA_INVALID
} Mcal_QueueStatusType;
#endif /* (STD_ON == DEMO_PRINTQUEUEMODE) */

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
#define UART_START_SEC_CODE_ASIL_D_GLOBAL
#include "Uart_MemMap.h"

#if (STD_ON == DEMO_PRINTQUEUEMODE)
/*********************************Declare Queue related functions**********************************/
FUNC(Mcal_QueueStatusType, MCAL_PUBLIC_CODE) Mcal_QueueCreate
(
    P2VAR(Mcal_SeqQueueType, AUTOMATIC, INTC_APPL_CONST) SeqQueuePtr,
    P2VAR(uint8, AUTOMATIC, INTC_APPL_CONST) ElemBufferPtr,
    Mcal_QueueLenType ElemBufferLen
);
FUNC(void, MCAL_PUBLIC_CODE) Printf_QueueInit
(
    void
);
FUNC(Std_ReturnType, MCAL_PUBLIC_CODE) Mcal_QueuePush
(
    P2VAR(Mcal_SeqQueueType, AUTOMATIC, INTC_APPL_CONST) SeqQueuePtr,
    P2VAR(uint8, AUTOMATIC, INTC_APPL_CONST) DataPtr
);

FUNC(Std_ReturnType, MCAL_PUBLIC_CODE) Mcal_QueuePop
(
    P2VAR(Mcal_SeqQueueType, AUTOMATIC, INTC_APPL_CONST) SeqQueuePtr,
    P2VAR(uint8, AUTOMATIC, INTC_APPL_CONST) DataPtr
);
FUNC(Mcal_QueueStatusType, MCAL_PUBLIC_CODE) Mcal_GetQueueFullStatus
(
    P2VAR(Mcal_SeqQueueType, AUTOMATIC, INTC_APPL_CONST) SeqQueuePtr,
    P2VAR(uint8, AUTOMATIC, INTC_APPL_CONST) DataPtr
);
FUNC(Mcal_QueueStatusType, MCAL_PUBLIC_CODE) Mcal_GetQueueEmptyStatus
(
    P2VAR(Mcal_SeqQueueType, AUTOMATIC, INTC_APPL_CONST) SeqQueuePtr
);
extern void PrintfPrint(void);
#endif /* (STD_ON == DEMO_PRINTQUEUEMODE) */

extern uint8 TmcPrintf(char* str, const uint8* fmt, ...);
extern char getChar(void);
extern void Gpt_UartPrintf5Ms_5(void);

#define UART_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Uart_MemMap.h"

#ifdef __cplusplus
#endif

#endif /* _UART_DEMO_H_ */

