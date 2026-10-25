/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Intc.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Intc/GIC
*
*   brief                 : This file contains all function declarations of Intc Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright \(c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/*
*#Violation Summary
*
*#Intc_h_REF_1:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*/

#ifndef INTC_H_
#define INTC_H_
/****************************************************************************************************
*                               Include
****************************************************************************************************/
#include "Intc_Version.h"
#include "Intc_GeneralTypes.h"
#include "Intc_Cfg.h"
#include "Intc_PBcfg.h"

/****************************************************************************************************
*                            Definitions and Macros
****************************************************************************************************/
/*Development errors*/
#if (INTC_DEV_ERROR_DETECT == STD_ON)

/* External interrupt source number is out of range */
#define INTC_E_INTSRC_NUM_OUT_RANGE          ((uint8)0x0AU)
/* Interrupt not installed or install failed */
#define INTC_E_INTSRC_UNINSTALLED            ((uint8)0x0BU)
/* Already Installed */
#define INTC_E_INT_ALREADY_INSTALLED         ((uint8)0x0CU)
/* The interrupt with the specified interrupt ID is not configured */
#define INTC_E_INTID_NOT_CONFIGURED          ((uint8)0x0DU)
/* Null pointer */
#define INTC_E_PARAM_POINTER                 ((uint8)0x0EU)
/* Interrupt source or interrupt in core is already enabled */
#define INTC_E_ALREADY_ENABLED               ((uint8)0x0FU)
/* Interrupt source or interrupt in core is already disabled */
#define INTC_E_ALREADY_DISABLED              ((uint8)0x10U)
/* Specified core error when generating the SGI interrupt */
#define INTC_E_GENSGI_WRONG_CORE             ((uint8)0x11U)
/* Interrupt install failed */
#define INTC_E_INSTALL_FAILED                ((uint8)0x12U)
/* Generate soft interrupt failed */
#define INTC_E_GENSGI_FAILED                 ((uint8)0x13U)
/* Timeout when get lock */
#define INTC_E_LOCK_TIMEOUT                  ((uint8)0x20U)

#endif /* (INTC_DEV_ERROR_DETECT  \== STD_ON) */

#if (INTC_DEV_ERROR_DETECT == STD_ON)

/*  Service ID number for all INTC driver services*/
#define INTC_SID_INSTALLINT                  ((uint8)0x00U)
#define INTC_SID_DISABLEINT                  ((uint8)0x01U)
#define INTC_SID_ENABLEINT                   ((uint8)0x02U)
#define INTC_SID_GENSWTINTERRUPT             ((uint8)0x03U)
#define INTC_SID_GETVERSIONINFO              ((uint8)0x05U)

#endif /* (INTC_DEV_ERROR_DETECT \== STD_ON)*/

/* Interrupt category */
#define INTC_SRC_TYPE_CAT1                  (1U)
/* #Violation: Intc_h_REF_1 */
#define INTC_SRC_TYPE_CAT2                  (2U)


/* Maximum number of SPI INTID */
#define INTC_MAX_SPI_INTID                  (991U)
/* Maximum number of SGI INTID */
#define INTC_MAX_SGI_INTID                  (15U)
/* Maximum number of PPI INTID */
#define INTC_MAX_PPI_INTID                  (31U)

/* SPI software interrupt range */
/* Range0: software interrupt INTID is 56 ~ 59 */
#define INTC_MIN_SPI_SOFTINT_INTID          (56U)
#define INTC_MAX_SPI_SOFTINT_INTID          (59U)
/* Range1: software interrupt INTID is 89 ~ 92 */
#define INTC_MIN_SPI_SOFTINT_INTID_1        (89U)
#define INTC_MAX_SPI_SOFTINT_INTID_1        (92U)

/****************************************************************************************************
*                               Extern Data Declaration
****************************************************************************************************/

/****************************************************************************************************
*                               Extern Function Declaration
****************************************************************************************************/
/* #Violation: Intc_h_REF_1 */
#define INTC_START_SEC_CODE_ASIL_D_GLOBAL
#include "Intc_MemMap.h"

extern FUNC(Intc_InsStaType, INTC_PUBLIC_CODE) Intc_InstallInterrupt
(
    CONSTP2CONST(Intc_ConfigType, AUTOMATIC, INTC_APPL_CONST) ConfigPtr,
    P2VAR(Intc_HandlerType, AUTOMATIC, INTC_APPL_DATA) IntTablePtr
);

extern FUNC(void, INTC_PUBLIC_CODE) Intc_DisableInterrupt
(
    Intc_IntSrcType IntSrcId
);

extern FUNC(void, INTC_PUBLIC_CODE) Intc_EnableInterrupt
(
    Intc_IntSrcType IntSrcId
);

#if (INTC_CFG_SGI_INT_EN == STD_ON)
extern FUNC(Std_ReturnType, INTC_PUBLIC_CODE) Intc_GenSwInterrupt
(
    Intc_IntSrcType IntSrcId,
    Intc_TargetCoreType TargetCore
);
#endif /* (INTC_CFG_SGI_INT_EN  \== STD_ON) */

#if (INTC_CFG_VERSION_INFO_API == STD_ON)
extern FUNC(void, INTC_PUBLIC_CODE) Intc_GetVersionInfo
(
    CONSTP2VAR(Std_VersionInfoType, AUTOMATIC, INTC_APPL_DATA) VersionInfoPtr
);
#endif /* (INTC_CFG_VERSION_INFO_API  \== STD_ON) */

/* #Violation: Intc_h_REF_1 */
#define INTC_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Intc_MemMap.h"

#endif /* INTC_H_ */

/****************************************************************************************************
**                      End of File
****************************************************************************************************/
