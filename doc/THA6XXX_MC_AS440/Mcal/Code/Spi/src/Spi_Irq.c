/****************************************************************************************************
 *
****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Spi_Irq.c
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : Espi
 *
 *   brief                 : This file contains all ISR functions of Spi Driver
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
*#Spi_Irq_c_REF_1:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access.
*
*#Spi_Irq_c_REF_2:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*#Spi_Irq_c_REF_3:MISRAC2012-Rule-20.1;
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Spi_Cfg.h"
#include "Spi_GeneralTypes.h"
#include "Mcall.h"
#include "Spi.h"
#include "Spi_Irq.h"

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/* #Violation: Spi_Irq_c_REF_2 */ 
#define SPI_START_SEC_CODE_ASIL_D_GLOBAL
#include "Spi_MemMap.h"

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))

#ifdef SPI_HWUNIT_EXISTS_SPI0
/****************************************************************************************************
*   Function Name           : Spi_ESPI0_FifoRx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ESPI0 receive interrupt service entry function.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2
*                             and Pre-compile parameter SPI_HWUNIT_EXISTS_SPI0 shall be define.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Spi_Irq_c_REF_1 */
FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI0_FifoRx_ISR
(
    void
)
{
    Spi_FifoRx_ISRHandler(0U);
}
/****************************************************************************************************
*   Function Name           : Spi_ESPI0_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ESPI0 error interrupt service entry function.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2
*                             and Pre-compile parameter SPI_HWUNIT_EXISTS_SPI0 shall be define.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI0_Error_ISR
(
    void
)
{
    Spi_Error_ISRHandler(0U);
}
#endif /* #ifdef \SPI_HWUNIT_EXISTS_SPI0 */

#ifdef SPI_HWUNIT_EXISTS_SPI1
/****************************************************************************************************
*   Function Name           : Spi_ESPI1_FifoRx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ESPI1 receive interrupt service entry function.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2
*                             and Pre-compile parameter SPI_HWUNIT_EXISTS_SPI1 shall be define.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI1_FifoRx_ISR
(
    void
)
{
    Spi_FifoRx_ISRHandler(1U);
}
/****************************************************************************************************
*   Function Name           : Spi_ESPI1_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ESPI1 error interrupt service entry function.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2
*                             and Pre-compile parameter SPI_HWUNIT_EXISTS_SPI1 shall be define.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI1_Error_ISR
(
    void
)
{
    Spi_Error_ISRHandler(1U);
}
#endif /* \#ifdef SPI_HWUNIT_EXISTS_SPI1 */

#ifdef SPI_HWUNIT_EXISTS_SPI2
/****************************************************************************************************
*   Function Name           : Spi_ESPI2_FifoRx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ESPI2 receive interrupt service entry function.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2
*                             and Pre-compile parameter SPI_HWUNIT_EXISTS_SPI2 shall be define.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Spi_Irq_c_REF_1 */
FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI2_FifoRx_ISR
(
    void
)
{
    Spi_FifoRx_ISRHandler(2U);
}
/****************************************************************************************************
*   Function Name           : Spi_ESPI2_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ESPI2 error interrupt service entry function.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2
*                             and Pre-compile parameter SPI_HWUNIT_EXISTS_SPI2 shall be define.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI2_Error_ISR
(
    void
)
{
    Spi_Error_ISRHandler(2U);
}
#endif /* \#ifdef SPI_HWUNIT_EXISTS_SPI2 */

#ifdef SPI_HWUNIT_EXISTS_SPI3
/****************************************************************************************************
*   Function Name           : Spi_ESPI3_FifoRx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ESPI3 receive interrupt service entry function.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2
*                             and Pre-compile parameter SPI_HWUNIT_EXISTS_SPI3 shall be define.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI3_FifoRx_ISR
(
    void
)
{
    Spi_FifoRx_ISRHandler(3U);
}
/****************************************************************************************************
*   Function Name           : Spi_ESPI3_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ESPI3 error interrupt service entry function.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2
*                             and Pre-compile parameter SPI_HWUNIT_EXISTS_SPI3 shall be define.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI3_Error_ISR
(
    void
)
{
    Spi_Error_ISRHandler(3U);
}
#endif /* \#ifdef SPI_HWUNIT_EXISTS_SPI3 */

#ifdef SPI_HWUNIT_EXISTS_SPI4
/****************************************************************************************************
*   Function Name           : Spi_ESPI4_FifoRx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ESPI4 receive interrupt service entry function.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2
*                             and Pre-compile parameter SPI_HWUNIT_EXISTS_SPI4 shall be define.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI4_FifoRx_ISR
(
    void
)
{
    Spi_FifoRx_ISRHandler(4U);
}
/****************************************************************************************************
*   Function Name           : Spi_ESPI4_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ESPI4 error interrupt service entry function.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2
*                             and Pre-compile parameter SPI_HWUNIT_EXISTS_SPI4 shall be define.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI4_Error_ISR
(
    void
)
{
    Spi_Error_ISRHandler(4U);
}
#endif /* \#ifdef SPI_HWUNIT_EXISTS_SPI4 */

#ifdef SPI_HWUNIT_EXISTS_SPI5
/****************************************************************************************************
*   Function Name           : Spi_ESPI5_FifoRx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ESPI5 receive interrupt service entry function.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2
*                             and Pre-compile parameter SPI_HWUNIT_EXISTS_SPI5 shall be define.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI5_FifoRx_ISR
(
    void
)
{
    Spi_FifoRx_ISRHandler(5U);
}
/****************************************************************************************************
*   Function Name           : Spi_ESPI5_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ESPI5 error interrupt service entry function.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2
*                             and Pre-compile parameter SPI_HWUNIT_EXISTS_SPI5 shall be define.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI5_Error_ISR
(
    void
)
{
    Spi_Error_ISRHandler(5U);
}
#endif /* \#ifdef SPI_HWUNIT_EXISTS_SPI5 */

#ifdef SPI_HWUNIT_EXISTS_SPI6
/****************************************************************************************************
*   Function Name           : Spi_ESPI6_FifoRx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ESPI6 receive interrupt service entry function.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2
*                             and Pre-compile parameter SPI_HWUNIT_EXISTS_SPI6 shall be define.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI6_FifoRx_ISR
(
    void
)
{
    Spi_FifoRx_ISRHandler(6U);
}
/****************************************************************************************************
*   Function Name           : Spi_ESPI6_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ESPI6 error interrupt service entry function.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2
*                             and Pre-compile parameter SPI_HWUNIT_EXISTS_SPI6 shall be define.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI6_Error_ISR
(
    void
)
{
    Spi_Error_ISRHandler(6U);
}
#endif /* \#ifdef SPI_HWUNIT_EXISTS_SPI6 */

#ifdef SPI_HWUNIT_EXISTS_SPI7
/****************************************************************************************************
*   Function Name           : Spi_ESPI7_FifoRx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ESPI7 receive interrupt service entry function.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2
*                             and Pre-compile parameter SPI_HWUNIT_EXISTS_SPI7 shall be define.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI7_FifoRx_ISR
(
    void
)
{
    Spi_FifoRx_ISRHandler(7U);
}
/****************************************************************************************************
*   Function Name           : Spi_ESPI7_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ESPI7 error interrupt service entry function.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2
*                             and Pre-compile parameter SPI_HWUNIT_EXISTS_SPI7 shall be define.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI7_Error_ISR
(
    void
)
{
    Spi_Error_ISRHandler(7U);
}
#endif /* \#ifdef SPI_HWUNIT_EXISTS_SPI7 */

#ifdef SPI_HWUNIT_EXISTS_SPI8
/****************************************************************************************************
*   Function Name           : Spi_ESPI8_FifoRx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ESPI8 receive interrupt service entry function.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2
*                             and Pre-compile parameter SPI_HWUNIT_EXISTS_SPI8 shall be define.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Spi_Irq_c_REF_1 */
FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI8_FifoRx_ISR
(
    void
)
{
    Spi_FifoRx_ISRHandler(8U);
}
/****************************************************************************************************
*   Function Name           : Spi_ESPI8_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ESPI8 error interrupt service entry function.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2
*                             and Pre-compile parameter SPI_HWUNIT_EXISTS_SPI8 shall be define.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, SPI_PUBLIC_CODE) Spi_ESPI8_Error_ISR
(
    void
)
{
    Spi_Error_ISRHandler(8U);
}
#endif /* \#ifdef SPI_HWUNIT_EXISTS_SPI8 */

#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */


/* #Violation: Spi_Irq_c_REF_2 */
#define SPI_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Spi_Irq_c_REF_3 */
#include "Spi_MemMap.h"
 /****************************************************************************************************
 **                          End of File                                                            **
 ****************************************************************************************************/
