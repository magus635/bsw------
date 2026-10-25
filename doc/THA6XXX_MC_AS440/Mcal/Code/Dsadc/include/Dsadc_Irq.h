/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Dsadc_Irq.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Dsadc
*
*   brief                 : This file contains all ISR function declarations of Dsadc Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

#ifndef DSADC_IRQ_H_
#define DSADC_IRQ_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Dsadc.h"

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
#define DSADC_START_SEC_CODE_ASIL_D_GLOBAL
#include "Dsadc_MemMap.h"

#if defined(DSADC_HWUNIT_DSADC0)
#if (defined(DSADC_HWUNIT_INT_EN_DSADC0) && (DSADC_HWUNIT_INT_EN_DSADC0 == STD_ON))
#if (defined(DSADC_HWUNIT_AUX_INT_EN_DSADC0) && (DSADC_HWUNIT_AUX_INT_EN_DSADC0 == STD_ON))
extern FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC0SRA_ISR
(
    void
);
#endif /* \(defined(DSADC_HWUNIT_AUX_INT_EN_DSADC0) && (DSADC_HWUNIT_AUX_INT_EN_DSADC0 == STD_ON)) */
extern FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC0SRM_ISR
(
    void
);
#endif /* \(defined(DSADC_HWUNIT_INT_EN_DSADC0) && (DSADC_HWUNIT_INT_EN_DSADC0 == STD_ON)) */
#endif /* \defined(DSADC_HWUNIT_DSADC0) */

#if defined(DSADC_HWUNIT_DSADC1)
#if (defined(DSADC_HWUNIT_INT_EN_DSADC1) && (DSADC_HWUNIT_INT_EN_DSADC1 == STD_ON))
#if (defined(DSADC_HWUNIT_AUX_INT_EN_DSADC1) && (DSADC_HWUNIT_AUX_INT_EN_DSADC1 == STD_ON))
extern FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC1SRA_ISR
(
    void
);
#endif /* \(defined(DSADC_HWUNIT_AUX_INT_EN_DSADC1) && (DSADC_HWUNIT_AUX_INT_EN_DSADC1 == STD_ON)) */
extern FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC1SRM_ISR
(
    void
);
#endif /* \(defined(DSADC_HWUNIT_INT_EN_DSADC1) && (DSADC_HWUNIT_INT_EN_DSADC1 == STD_ON)) */
#endif /* \defined(DSADC_HWUNIT_DSADC1) */

#if defined(DSADC_HWUNIT_DSADC2)
#if (defined(DSADC_HWUNIT_INT_EN_DSADC2) && (DSADC_HWUNIT_INT_EN_DSADC2 == STD_ON))
#if (defined(DSADC_HWUNIT_AUX_INT_EN_DSADC2) && (DSADC_HWUNIT_AUX_INT_EN_DSADC2 == STD_ON))
extern FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC2SRA_ISR
(
    void
);
#endif /* \(defined(DSADC_HWUNIT_AUX_INT_EN_DSADC2) && (DSADC_HWUNIT_AUX_INT_EN_DSADC2 == STD_ON)) */
extern FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC2SRM_ISR
(
    void
);
#endif /* \(defined(DSADC_HWUNIT_INT_EN_DSADC2) && (DSADC_HWUNIT_INT_EN_DSADC2 == STD_ON)) */
#endif /* \defined(DSADC_HWUNIT_DSADC2) */

#if defined(DSADC_HWUNIT_DSADC3)
#if (defined(DSADC_HWUNIT_INT_EN_DSADC3) && (DSADC_HWUNIT_INT_EN_DSADC3 == STD_ON))
#if (defined(DSADC_HWUNIT_AUX_INT_EN_DSADC3) && (DSADC_HWUNIT_AUX_INT_EN_DSADC3 == STD_ON))
extern FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC3SRA_ISR
(
    void
);
#endif /* \(defined(DSADC_HWUNIT_AUX_INT_EN_DSADC3) && (DSADC_HWUNIT_AUX_INT_EN_DSADC3 == STD_ON)) */
extern FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC3SRM_ISR
(
    void
);
#endif /* \(defined(DSADC_HWUNIT_INT_EN_DSADC3) && (DSADC_HWUNIT_INT_EN_DSADC3 == STD_ON)) */
#endif /* \defined(DSADC_HWUNIT_DSADC3) */

#if defined(DSADC_HWUNIT_DSADC4)
#if (defined(DSADC_HWUNIT_INT_EN_DSADC4) && (DSADC_HWUNIT_INT_EN_DSADC4 == STD_ON))
#if (defined(DSADC_HWUNIT_AUX_INT_EN_DSADC4) && (DSADC_HWUNIT_AUX_INT_EN_DSADC4 == STD_ON))
extern FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC4SRA_ISR
(
    void
);
#endif /* \(defined(DSADC_HWUNIT_AUX_INT_EN_DSADC4) && (DSADC_HWUNIT_AUX_INT_EN_DSADC4 == STD_ON)) */
extern FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC4SRM_ISR
(
    void
);
#endif /* \(defined(DSADC_HWUNIT_INT_EN_DSADC4) && (DSADC_HWUNIT_INT_EN_DSADC4 == STD_ON)) */
#endif /* \defined(DSADC_HWUNIT_DSADC4) */

#if defined(DSADC_HWUNIT_DSADC5)
#if (defined(DSADC_HWUNIT_INT_EN_DSADC5) && (DSADC_HWUNIT_INT_EN_DSADC5 == STD_ON))
#if (defined(DSADC_HWUNIT_AUX_INT_EN_DSADC5) && (DSADC_HWUNIT_AUX_INT_EN_DSADC5 == STD_ON))
extern FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC5SRA_ISR
(
    void
);
#endif /* \(defined(DSADC_HWUNIT_AUX_INT_EN_DSADC5) && (DSADC_HWUNIT_AUX_INT_EN_DSADC5 == STD_ON)) */
extern FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC5SRM_ISR
(
    void
);
#endif /* \(defined(DSADC_HWUNIT_INT_EN_DSADC5) && (DSADC_HWUNIT_INT_EN_DSADC5 == STD_ON)) */
#endif /* \defined(DSADC_HWUNIT_DSADC5) */

#if defined(DSADC_HWUNIT_DSADC6)
#if (defined(DSADC_HWUNIT_INT_EN_DSADC6) && (DSADC_HWUNIT_INT_EN_DSADC6 == STD_ON))
#if (defined(DSADC_HWUNIT_AUX_INT_EN_DSADC6) && (DSADC_HWUNIT_AUX_INT_EN_DSADC6 == STD_ON))
extern FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC6SRA_ISR
(
    void
);
#endif /* \(defined(DSADC_HWUNIT_AUX_INT_EN_DSADC6) && (DSADC_HWUNIT_AUX_INT_EN_DSADC6 == STD_ON)) */
extern FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC6SRM_ISR
(
    void
);
#endif /* \(defined(DSADC_HWUNIT_INT_EN_DSADC6) && (DSADC_HWUNIT_INT_EN_DSADC6 == STD_ON)) */
#endif /* \defined(DSADC_HWUNIT_DSADC6) */

#if defined(DSADC_HWUNIT_DSADC7)
#if (defined(DSADC_HWUNIT_INT_EN_DSADC7) && (DSADC_HWUNIT_INT_EN_DSADC7 == STD_ON))
#if (defined(DSADC_HWUNIT_AUX_INT_EN_DSADC7) && (DSADC_HWUNIT_AUX_INT_EN_DSADC7 == STD_ON))
extern FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC7SRA_ISR
(
    void
);
#endif /* \(defined(DSADC_HWUNIT_AUX_INT_EN_DSADC7) && (DSADC_HWUNIT_AUX_INT_EN_DSADC7 == STD_ON)) */
extern FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC7SRM_ISR
(
    void
);
#endif /* \(defined(DSADC_HWUNIT_INT_EN_DSADC7) && (DSADC_HWUNIT_INT_EN_DSADC7 == STD_ON)) */
#endif /* \defined(DSADC_HWUNIT_DSADC7) */

#if defined(DSADC_HWUNIT_DSADC8)
#if (defined(DSADC_HWUNIT_INT_EN_DSADC8) && (DSADC_HWUNIT_INT_EN_DSADC8 == STD_ON))
#if (defined(DSADC_HWUNIT_AUX_INT_EN_DSADC8) && (DSADC_HWUNIT_AUX_INT_EN_DSADC8 == STD_ON))
extern FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC8SRA_ISR
(
    void
);
#endif /* \(defined(DSADC_HWUNIT_AUX_INT_EN_DSADC8) && (DSADC_HWUNIT_AUX_INT_EN_DSADC8 == STD_ON)) */
extern FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC8SRM_ISR
(
    void
);
#endif /* \(defined(DSADC_HWUNIT_INT_EN_DSADC8) && (DSADC_HWUNIT_INT_EN_DSADC8 == STD_ON)) */
#endif /* \defined(DSADC_HWUNIT_DSADC8) */

#if defined(DSADC_HWUNIT_DSADC9)
#if (defined(DSADC_HWUNIT_INT_EN_DSADC9) && (DSADC_HWUNIT_INT_EN_DSADC9 == STD_ON))
#if (defined(DSADC_HWUNIT_AUX_INT_EN_DSADC9) && (DSADC_HWUNIT_AUX_INT_EN_DSADC9 == STD_ON))
extern FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC9SRA_ISR
(
    void
);
#endif /* \(defined(DSADC_HWUNIT_AUX_INT_EN_DSADC9) && (DSADC_HWUNIT_AUX_INT_EN_DSADC9 == STD_ON)) */
extern FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC9SRM_ISR
(
    void
);
#endif /* \(defined(DSADC_HWUNIT_INT_EN_DSADC9) && (DSADC_HWUNIT_INT_EN_DSADC9 == STD_ON)) */
#endif /* \defined(DSADC_HWUNIT_DSADC9) */

#define DSADC_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Dsadc_MemMap.h"

#endif /* \DSADC_IRQ_H_ */

/****************************************************************************************************
**                      End of File
****************************************************************************************************/
