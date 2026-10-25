/****************************************************************************************************
 *
****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Spi_Irq.h
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : Espi
 *
 *   brief                 : This file contains all ISR function declarations of Spi Driver
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
*#Spi_Irq_h_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*/
#ifndef SPI_IRQ_H_
#define SPI_IRQ_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Spi_Cfg.h"
#include "Mcall.h"

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
/* #Violation: Spi_Irq_h_REF_1 */ 
#define SPI_START_SEC_CODE_ASIL_D_GLOBAL 
#include "Spi_MemMap.h"

#ifdef SPI_HWUNIT_EXISTS_SPI0
extern FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI0_FifoRx_ISR
(
    void
);
extern FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI0_Error_ISR
(
    void
);
#endif /* \#ifdef SPI_HWUNIT_EXISTS_SPI0 */

#ifdef SPI_HWUNIT_EXISTS_SPI1
extern FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI1_FifoRx_ISR
(
    void
);
extern FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI1_Error_ISR
(
    void
);
#endif /* \#ifdef SPI_HWUNIT_EXISTS_SPI1 */

#ifdef SPI_HWUNIT_EXISTS_SPI2
extern FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI2_FifoRx_ISR
(
    void
);
extern FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI2_Error_ISR
(
    void
);
#endif /* \#ifdef SPI_HWUNIT_EXISTS_SPI2 */

#ifdef SPI_HWUNIT_EXISTS_SPI3
extern FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI3_FifoRx_ISR
(
    void
);
extern FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI3_Error_ISR
(
    void
);
#endif /* \#ifdef SPI_HWUNIT_EXISTS_SPI3 */

#ifdef SPI_HWUNIT_EXISTS_SPI4
extern FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI4_FifoRx_ISR
(
    void
);
extern FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI4_Error_ISR
(
    void
);
#endif /* \#ifdef SPI_HWUNIT_EXISTS_SPI4 */

#ifdef SPI_HWUNIT_EXISTS_SPI5
extern FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI5_FifoRx_ISR
(
    void
);
extern FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI5_Error_ISR
(
    void
);
#endif /* \#ifdef SPI_HWUNIT_EXISTS_SPI5 */

#ifdef SPI_HWUNIT_EXISTS_SPI6
extern FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI6_FifoRx_ISR
(
    void
);
extern FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI6_Error_ISR
(
    void
);
#endif /* \#ifdef SPI_HWUNIT_EXISTS_SPI6 */

#ifdef SPI_HWUNIT_EXISTS_SPI7
extern FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI7_FifoRx_ISR
(
    void
);
extern FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI7_Error_ISR
(
    void
);
#endif /* \#ifdef SPI_HWUNIT_EXISTS_SPI7 */

#ifdef SPI_HWUNIT_EXISTS_SPI8
extern FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI8_FifoRx_ISR
(
    void
);
extern FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI8_Error_ISR
(
    void
);
#endif /* \#ifdef SPI_HWUNIT_EXISTS_SPI8 */

/* #Violation: Spi_Irq_h_REF_1 */ 
#define SPI_STOP_SEC_CODE_ASIL_D_GLOBAL 
#include "Spi_MemMap.h"

#endif /* SPI_IRQ_H */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

