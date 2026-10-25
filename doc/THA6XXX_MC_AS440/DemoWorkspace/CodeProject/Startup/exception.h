/**************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName: exception.h
 * Author:    30032
 * Version:   v1.0
 * Date:      2023/05/14
 * Description: This file defines APIs and structures provided by exception framework.
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/14    30032     create
 ************************************************************************************************/
/*
* #Violation Summary
*
* #exception_h_REF_1:MISRAC2012-Rule-18.5;
* Justification:Dedicated to write back.
*
* #exception_h_REF_2:MISRAC2012-Dir-4.8;
* Justification:Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*/

#ifndef EXCEPTION_H_
#define EXCEPTION_H_
#include "Platform_Types.h"

/* defined interrupt routine prototype.*/
typedef void (*Isr)(void);

/* ExceptionInfo structure is used as Exception Callback function parameter. */
/* #Violation: exception_h_REF_2 */
typedef struct
{
    boolean el1Flag; /* EL1 Flag. TRUE indicate in EL1 env. */
    uint32 lr;       /* register LR value to indicate where to execute when exit exception */
    uint32 hsr;      /* register HSR value if el1Flag is 0, otherwise it is 0. */
    uint32 haifsr;   /* register HAIFSR value if el1Flag is 0, otherwise it is 0. */
    uint32 hpfar;    /* register HPFAR value if el1Flag is 0, otherwise it is 0. */
    uint32 aifsr;    /* register AIFSR value. */
    uint32 adfsr;    /* register ADFSR value. */
    uint32 dfar;     /* register DFAR value. */
    uint32 dfsr;     /* register DFSR value. */
    uint32 ifar;     /* register IFAR value. */
    uint32 ifsr;     /* register IFSR value. */
    uint32 isr;      /* register ISR value. */
} ExceptionInfo;

/*********************************************************************
 * Function: Exception_GetIntVectorInfo
 * Description: Get information about the base address of IRQ/FIQ Interrupt vector table and element numbers.
 * Input:   None
 * Output:  IntHandler** ppIntVectorBaseAddr, pointer to base address of IRQ/FIQ Interrupt vector table
 * Output:  uint32* pElemSize, point to the memory which is used to save the element numbers of interrupt vector table.
 * Return:  0 indicates success and others indicate failure
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/14    30032      create
 ***********************************************************************/
/* #Violation: exception_h_REF_1 */
extern uint32 Exception_GetIntVectorInfo(Isr *ppIntVectorBaseAddr[], uint32 *pElemSize);

/*********************************************************************
 * Function: Exception_UndefinedCallback
 * Description: Callback function for Undefined Instruction exception. it is implemented by user. and
 * suggest to enter infinite loop when this callback is called.
 * Input:   const ExceptionInfo* info, point to the structure which save related register value.
 * Output:  None
 * Return:  uint32: 0: Return to the next instruction where the exception occurred.
 *                  1: Return to the instruction where the exception occurred.
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/14    30032      create
 ***********************************************************************/
extern uint32 Exception_UndefinedCallback(const ExceptionInfo *info);

/*********************************************************************
 * Function: Exception_PrefetchAbortCallback
 * Description: Callback function for Prefetch Abort exception. it is implemented by user. and
 * suggest to enter infinite loop when this callback is called.
 * Input:  const ExceptionInfo* info, point to the structure which save related register value.
 * Output:  None
 * Return:  None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/14    30032      create
 ***********************************************************************/
extern void Exception_PrefetchAbortCallback(const ExceptionInfo *info);

/*********************************************************************
 * Function: Exception_DataAbortCallback
 * Description: Callback function for Data Abort exception. it is implemented by user. and
 * suggest to enter infinite loop when this callback is called.
 * Input:  const ExceptionInfo* info, point to the structure which save related register value.
 * Output:  None
 * Return:  uint32: 0: Return to the next instruction where the exception occurred.
 *                  1: Return to the instruction where the exception occurred.
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/14    30032      create
 ***********************************************************************/
extern uint32 Exception_DataAbortCallback(const ExceptionInfo *info);

#endif /* END EXCEPTION_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
