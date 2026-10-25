/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Demo_Common.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : None
*
*   brief                 :
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

#ifndef DEMO_COMMON_H_
#define DEMO_COMMON_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"

#include "Demo_TestTime.h"
#include "Demo_Version.h"

#include "Mcall.h"

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
/* Macro for print method */
#define DEMO_PRINT_UART                          (0U)
#define DEMO_PRINT_TOOLCHAIN                     (1U)
#define DEMO_NO_PRINT                            (255U)
#define DEMO_PRINT_METHOD                        (DEMO_PRINT_UART)

/* When printing across cores, you need to configure the macro value to STD_ON */
#define DEMO_PRINTQUEUEMODE                       STD_ON
/* To use GPT timer interrupt to send data, you need to configure the macro value */
#define DEMO_PRINTINTERRUPT                       STD_ON

/* Macro for UART */
#if (DEMO_PRINT_METHOD != DEMO_NO_PRINT)

#if (DEMO_PRINT_METHOD == DEMO_PRINT_TOOLCHAIN)
/* Print supported by toolchain */
#include <stdio.h>
#define DEBUG_PRINTF(fmt, ...)                printf(fmt, ##__VA_ARGS__)
/* Get a character without new line */
LOCAL_INLINE char Demo_GetOneChar(void)
{
    char a = getchar();
    getchar();
    return a;
}
#define DEBUG_GETC()                          Demo_GetOneChar()

#else /* (DEMO_PRINT_METHOD == DEMO_PRINT_UART) */
/* Print supported by UART */
#include "Uart_Demo.h"
#define DEBUG_PRINTF(fmt, ...)                (void)TmcPrintf(NULL_PTR, (const uint8 *)fmt, ##__VA_ARGS__)
/* UART received one character */
#define DEBUG_GETC()                          getChar()
#endif /* (DEMO_PRINT_METHOD == DEMO_PRINT_UART) */

#else /* (DEMO_PRINT_METHOD == DEMO_NO_PRINT) */

/* Do not supported print function */
#define DEBUG_PRINTF(fmt, ...)
/* Do not supported scanf function */
#define DEBUG_GETC()                          '\0'

#endif /* (DEMO_PRINT_METHOD != DEMO_NO_PRINT) */


/* Demo initialize status */
#define DEMO_UNINITIALIZE                     (0U)
#define DEMO_INITIALIZED                      (1U)

/* Upper case convert to lower case */
#define DEMO_UPPER_TO_LOWER(c)                   (((c >= 'A') && (c <= 'A')) ? (c + 32) : (c))

/****************************************************************************************************
*                               Typedef Definition
****************************************************************************************************/
/* Type definition for demo entry flag */
typedef enum
{
    DEMO_IDLE    = 0U,
    DEMO_STARTED
} Demo_StartupType;

typedef void (*Demo_EntryFuncType)(void);

/* Type definition for Demo entry function information */
typedef struct
{
    const char InputCmd;
    /* Entry demo function */
    Demo_EntryFuncType DemoEntryFuncPtr;
    /* core1 demo function */
    Demo_EntryFuncType DemoCore1FuncPtr;
    /* core2 demo function */
    Demo_EntryFuncType DemoCore2FuncPtr;
    /* core3 demo function */
    Demo_EntryFuncType DemoCore3FuncPtr;
    /* Description information */
    const char *DescInfoPtr;
} Demo_EntryInfoType;

/* Type definition for multi-core running */
typedef volatile struct
{
    /* This variable can only be changed by Core0(master) */
    Mcal_CoreType    ExeCmdCore;
    /* The command need to be executed */
    uint8            ExeCmdId;
    /* Demo Entry flag */
    Demo_StartupType DemoStartupFlg;
} Demo_CoreExeType;

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


#endif /* DEMO_PRINT_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
