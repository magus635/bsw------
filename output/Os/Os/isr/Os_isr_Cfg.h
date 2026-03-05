/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_isr_Cfg.h
*
*   Platform              : AUTOSAR
*
*   BSW Module            : Os
*
*   brief                 : xxx
*
*   Autosar Version       : R23-11
*
*   Build Version         : Cortex-R52/THA6206
*
*   Genaration Time       : 2026-03-05 20:05:00
*
*   Copyright (c) @#
*   All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Revision Control History                                               **
****************************************************************************************************/
/*
*  -------------------------------------------------------------------------------------------------
*  Version    Date           Author(ID)      SVN_Version         Description
*  -------------------------------------------------------------------------------------------------
*  V0.0.1   22-May-2024    zhangtr(30011)                        Initial Version
*
****************************************************************************************************/
#ifndef OS_ISR_CFG_H_
#define OS_ISR_CFG_H_


/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#define NONE
#define GICv3(x)              ((GIC_MODULE*)(Os_IsrGICAddr[x]))
/* Trigger methods of interrupt */
#define OS_ISR_TRIGGERMETHOD_LEVEL (0U)
#define OS_ISR_TRIGGERMETHOD_EDGE  (1U)
/* Identification of two kinds of interrupt */
#define OS_ISR_INTERRUPTGROUP_FIQ  (0U)
#define OS_ISR_INTERRUPTGROUP_IRQ  (1U)

#define OS_ISR_SPI_TOTAL_NUM            (960U)
#define OS_ISR_INTERNALINT_TOTAL_NUM    (32U)
#define OS_ISRCFG_VIRTUALTIMER        (ISRType)(0)
#define OS_ISRCFG_SYSTEMTIMER        (ISRType)(1)
#define OS_ISRCFG_BASETIMER0        (ISRType)(2)
#define OS_ISRCFG_SYSTEMTIMER_CORE1        (ISRType)(3)
#define OSISR_BASETIMER1        (ISRType)(4)
#define OSISR_ISRCFG_VIRTUALTIMER_CORE1        (ISRType)(5)
#define OSISR_0        (ISRType)(6)
#define OSISR_1        (ISRType)(7)

#define OS_ISR_TOTAL_NUM    (8U)
#define INVALID_ISR  OS_ISR_TOTAL_NUM
/* ISR1 interrupt disable level, except tp interrupt */
#define OS_ISR_CAT1_DISABLE_LEVEL   (28UL)
/* ISR2 interrupt disable level */
#define OS_ISR_CAT2_DISABLE_LEVEL   (28UL)
/* ISR1 interrupt disable level, including tp interrupt */
#define OS_ISR_TP_DISABLE_LEVEL     (27UL)
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




#endif /* OS_ISR_CFG_H_ */

/****************************************************************************************************
**     End of File: Os_isr_Cfg.h                                                                 **
****************************************************************************************************/

