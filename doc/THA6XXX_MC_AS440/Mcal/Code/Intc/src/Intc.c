/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Intc.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Intc/GIC
*
*   brief                 : This file contains all functions of Intc Driver
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
*#Intc_c_REF_1:MISRAC2012-Dir-4.9;
* Justification: Function like macros are used to reduce code complexity.
*
*#Intc_c_REF_2:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*#Intc_c_REF_3:MISRAC2012-Rule-8.9;
* Justification:The value should be placed in the const data sections to reduce code complexity 
* and stack size.
*
*#Intc_c_REF_4:MISRAC2012-Rule-10.5;
* Necessary type casting to reduce code complexity; Code review ensure the safety of the casting.
*
*#Intc_c_REF_5:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts 
* of the driver must be placed.
*
*#Intc_c_REF_6:MISRAC2012-Rule-20.10;
* Justification:Use glue operator to construct the exclusive area function name.
*
*#Intc_c_REF_7:MISRAC2012-Dir-1.1-C99;
* Justification:Compiler can handle more than 4095 macro identifiers.
*
*#Intc_c_REF_8:CertC-PRE00-C;
* Justification: Function like macros are used to reduce code complexity.
*
*#Intc_c_REF_9:CertC-DCL19-C;
* Justification:The value should be placed in the const data sections to reduce code complexity 
* and stack size.
*
*#Intc_c_REF_10:MISRAC2012-Rule-2.1;
* Justification:Reserved API for user access
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
/* #Violation: Intc_c_REF_7 */
#include "Intc.h"
#include "Intc_Cfg.h"
#include "Intc_GeneralTypes.h"
#include "Intc_Version.h"
#include "SchM_Intc.h"
#include "Platform_Types.h"
#if (INTC_DEV_ERROR_DETECT == STD_ON)
/* Included the declaration of Det_ReportError() */
#include "Det.h"
#endif /* (INTC_DEV_ERROR_DETECT \== STD_ON) */
/* Included the intc driver of HAL layer */
#include "intc_hal.h"
#include "tha6_cfg.h"

/****************************************************************************************************
**                          Version Checks                                                         **
****************************************************************************************************/
/* Check if current file and INTC header file are of the same vendor */
#if (INTC_VENDOR_ID != INTC_CFG_VENDOR_ID)
  #error "Intc.c : Mismatch in Vendor ID"
#endif /* (INTC_VENDOR_ID \!= INTC_CFG_VENDOR_ID) */

#if (INTC_MODULE_ID != INTC_CFG_MODULE_ID)
#error "Intc.c : Mismatch in Module ID"
#endif /* \(INTC_MODULE_ID != INTC_CFG_MODULE_ID) */

#if (INTC_AR_RELEASE_MAJOR_VERSION != INTC_CFG_AR_RELEASE_MAJOR_VERSION)
  #error "Intc.c : Mismatch in Release Major Version"
#endif /* (INTC_AR_RELEASE_MAJOR_VERSION \!= INTC_CFG_AR_RELEASE_MAJOR_VERSION) */

#if (INTC_AR_RELEASE_MINOR_VERSION != INTC_CFG_AR_RELEASE_MINOR_VERSION)
  #error "Intc.c : Mismatch in Release Minor Version"
#endif /* (INTC_AR_RELEASE_MINOR_VERSION \!= INTC_CFG_AR_RELEASE_MINOR_VERSION) */

#if (INTC_AR_RELEASE_REVISION_VERSION != INTC_CFG_AR_RELEASE_REVISION_VERSION)
  #error "Intc.c : Mismatch in Release Revision Version"
#endif /* (INTC_AR_RELEASE_REVISION_VERSION \!= INTC_CFG_AR_RELEASE_REVISION_VERSION) */

#if (INTC_SW_MAJOR_VERSION != INTC_CFG_SW_MAJOR_VERSION)
  #error "Intc.c : Mismatch in Software Major Version"
#endif /* (INTC_SW_MAJOR_VERSION \!= INTC_CFG_SW_MAJOR_VERSION) */

#if (INTC_SW_MINOR_VERSION != INTC_CFG_SW_MINOR_VERSION)
  #error "Intc.c : Mismatch in Software Minor Version"
#endif /* (INTC_SW_MINOR_VERSION \!= INTC_CFG_SW_MINOR_VERSION) */

#if (INTC_SW_PATCH_VERSION != INTC_CFG_SW_PATCH_VERSION)
  #error "Intc.c : Mismatch in Software Patch Version"
#endif /* (INTC_SW_PATCH_VERSION \!= INTC_CFG_SW_PATCH_VERSION) */
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
/* Macro for report the INTC DET error */
/* #Violation: Intc_c_REF_8 */
#define Intc_ReportError(ServiceId, ErrCode)        \
                         (void)Det_ReportError(INTC_MODULE_ID, INTC_INSTANCE_ID, ServiceId, ErrCode)

/****************************************************************************************************
*                          SchM Critical Section Protection Macros                                 **
****************************************************************************************************/
/* #Violation: Intc_c_REF_6 */
/* #Violation: Intc_c_REF_8 */
#define INTC_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Intc_##Exclusive_Area()
/* #Violation: Intc_c_REF_6 */
/* #Violation: Intc_c_REF_8 */
#define INTC_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Intc_##Exclusive_Area()

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
/**                         Private Variable Definitions - Core0                                  **/
#if (INTC_DEV_ERROR_DETECT == STD_ON)

/* #Violation: Intc_c_REF_2 */
#define INTC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#include "Intc_MemMap.h"

/* Intc installed flag for Core 0 */
static Intc_InitType Intc_IntSrcInstallFlgCore0;

/* #Violation: Intc_c_REF_2 */
#define INTC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Intc_c_REF_5 */
#include "Intc_MemMap.h"

/**                         Private Variable Definitions - Core1                                  **/
#if (MCAL_NUMBER_OF_CORES > 1U)
#if (INTC_CFG_INTSRC_NUM_CORE1 > 0U)

/* #Violation: Intc_c_REF_2 */
#define INTC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Intc_c_REF_5 */
#include "Intc_MemMap.h"

/* Intc installed flag for Core 1 */
static Intc_InitType Intc_IntSrcInstallFlgCore1;

/* #Violation: Intc_c_REF_2 */
#define INTC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Intc_c_REF_5 */
#include "Intc_MemMap.h"

#endif /* (INTC_CFG_INTSRC_NUM_CORE1 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 1U) */

/**                         Private Variable Definitions - Core2                                  **/
#if (MCAL_NUMBER_OF_CORES > 2U)
#if (INTC_CFG_INTSRC_NUM_CORE2 > 0U)

/* #Violation: Intc_c_REF_2 */
#define INTC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Intc_c_REF_5 */
#include "Intc_MemMap.h"

/* Intc installed flag for Core 2 */
static Intc_InitType Intc_IntSrcInstallFlgCore2;

/* #Violation: Intc_c_REF_2 */
#define INTC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Intc_c_REF_5 */
#include "Intc_MemMap.h"

#endif /* (INTC_CFG_INTSRC_NUM_CORE2 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 2U) */

/**                         Private Variable Definitions - Core3                                  **/
#if (MCAL_NUMBER_OF_CORES > 3U)
#if (INTC_CFG_INTSRC_NUM_CORE3 > 0U)

/* #Violation: Intc_c_REF_2 */
#define INTC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Intc_c_REF_5 */
#include "Intc_MemMap.h"

/* Intc installed flag for Core 3 */
static Intc_InitType Intc_IntSrcInstallFlgCore3;

/* #Violation: Intc_c_REF_2 */
#define INTC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Intc_c_REF_5 */
#include "Intc_MemMap.h"

#endif /* (INTC_CFG_INTSRC_NUM_CORE3 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 3U) */

#endif /* (INTC_DEV_ERROR_DETECT \== STD_ON) */

/* #Violation: Intc_c_REF_2 */
#define INTC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Intc_c_REF_5 */
#include "Intc_MemMap.h"

/* Interrupt map status by master core, slave core will install interrupt sources to core pin
 * after master core finished */
/* #Violation: Intc_c_REF_3 */
/* #Violation: Intc_c_REF_9 */
static Intc_MapStatusType Intc_IntSrcMapStatus;

#if (INTC_DEV_ERROR_DETECT == STD_ON)
/* To store the Intc driver configuration pointer */
static P2CONST(Intc_ConfigType, AUTOMATIC, INTC_APPL_DATA) Intc_ConfigPtr;
#endif /* (INTC_DEV_ERROR_DETECT \== STD_ON) */

/* #Violation: Intc_c_REF_2 */
#define INTC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Intc_c_REF_5 */
#include "Intc_MemMap.h"

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/
/* #Violation: Intc_c_REF_2 */
#define INTC_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Intc_c_REF_5 */
#include "Intc_MemMap.h"

#if (INTC_DEV_ERROR_DETECT == STD_ON)
static CONSTP2VAR(Intc_InitType, INTC_VAR, INTC_APPL_CONST)
                             Intc_CoreInstallStatusPtr[MCAL_NUMBER_OF_CORES] =
{
    &Intc_IntSrcInstallFlgCore0
#if (MCAL_NUMBER_OF_CORES > 1U)
#if (INTC_CFG_INTSRC_NUM_CORE1 > 0U)
    ,&Intc_IntSrcInstallFlgCore1
#endif /* (INTC_CFG_INTSRC_NUM_CORE1 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 1U) */
#if (MCAL_NUMBER_OF_CORES > 2U)
#if (INTC_CFG_INTSRC_NUM_CORE2 > 0U)
    ,&Intc_IntSrcInstallFlgCore2
#endif /* (INTC_CFG_INTSRC_NUM_CORE2 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 2U) */
#if (MCAL_NUMBER_OF_CORES > 3U)
#if (INTC_CFG_INTSRC_NUM_CORE3 > 0U)
    ,&Intc_IntSrcInstallFlgCore3
#endif /* (INTC_CFG_INTSRC_NUM_CORE3 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 3U) */
};
#endif /* (INTC_DEV_ERROR_DETECT \== STD_ON) */

/* #Violation: Intc_c_REF_2 */
#define INTC_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Intc_c_REF_5 */
#include "Intc_MemMap.h"

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
/* #Violation: Intc_c_REF_2 */
#define INTC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Intc_c_REF_5 */
#include "Intc_MemMap.h"

#if (INTC_DEV_ERROR_DETECT == STD_ON)

static FUNC(Std_ReturnType, INTC_PRIVATE_CODE) Intc_CheckInitErrStatus
(
    CONSTP2CONST(Intc_ConfigType, AUTOMATIC, INTC_APPL_CONST) ConfigPtr
);

static FUNC(Std_ReturnType, INTC_PRIVATE_CODE) Intc_CheckIntSrcInstallStatus
(
    Intc_IntSrcType IntSrcId,
    Mcal_CoreType   CoreId
);

static FUNC(Std_ReturnType, INTC_PRIVATE_CODE) Intc_CheckIntSrcStatus
(
    Intc_IntSrcType IntSrcId,
    uint8 ServiceId
);

#if (INTC_CFG_SGI_INT_EN == STD_ON)
static FUNC(Std_ReturnType, INTC_PRIVATE_CODE) Intc_CheckGenSwIntStatus
(
    Intc_IntSrcType IntSrcId,
    uint8 ServiceId,
    Intc_TargetCoreType TargetCore
);
#endif /* (INTC_CFG_SGI_INT_EN \== STD_ON) */

#endif /* (INTC_DEV_ERROR_DETECT \== STD_ON) */

/* #Violation: Intc_c_REF_2 */
#define INTC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Intc_c_REF_5 */
#include "Intc_MemMap.h"
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
/* #Violation: Intc_c_REF_2 */
#define INTC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Intc_c_REF_5 */
#include "Intc_MemMap.h"

#if (INTC_DEV_ERROR_DETECT == STD_ON)
/****************************************************************************************************
*   Function Name           : Intc_CheckInitErrStatus
*
*   Service ID              : None.
*
*   Description             : DET check for initialization
*
*   Parameters in           : ConfigPtr: pointer to the configuration data
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant\(thread-safe)
*
*   Return value            : Std_ReturnType: Return the DET check status
*                             - E_OK: No error
*                             - E_NOT_OK: Error exists
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, INTC_PRIVATE_CODE) Intc_CheckInitErrStatus
(
    CONSTP2CONST(Intc_ConfigType, AUTOMATIC, INTC_APPL_CONST) ConfigPtr
)
{
    Std_ReturnType RetStatus;
    Mcal_CoreType  CoreId;

    RetStatus = E_OK;
    /* Get core id which is executing currently */
    /* #Violation: Intc_c_REF_1 */
    CoreId = Mcal_GetCoreId();

    if (NULL_PTR == ConfigPtr)
    {
        /* Invalid configuration data pointer */
        Intc_ReportError((uint8)INTC_SID_INSTALLINT, (uint8)INTC_E_PARAM_POINTER);

        RetStatus = E_NOT_OK;
    }
    else
    {
        /* #Violation: Intc_c_REF_1 */
        if (INTC_INITIALIZED == *Intc_CoreInstallStatusPtr[CoreId])
        {
            /* Already initialized */
            Intc_ReportError((uint8)INTC_SID_INSTALLINT, (uint8)INTC_E_INT_ALREADY_INSTALLED);

            RetStatus = E_NOT_OK;
        }
    }

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Intc_CheckIntSrcInstallStatus
*
*   Service ID              : None.
*
*   Description             : Detect whether the interrupt source has been installed.
*
*   Parameters in           : IntSrcId: Interrupt source ID
*                             CoreId: Core ID
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant\(thread-safe)
*
*   Return value            : Std_ReturnType: Return the DET check status
*                             - E_OK: No error
*                             - E_NOT_OK: Error exists
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, INTC_PRIVATE_CODE) Intc_CheckIntSrcInstallStatus
(
    Intc_IntSrcType IntSrcId,
    Mcal_CoreType   CoreId
)
{
    Std_ReturnType               RetStatus;
    Intc_IntSrcType              IntSrcNum;
    Intc_IntSrcType              IntSrcCnt;
    const Intc_IntSrcConfigType *IntSrcConfigPtr;

    RetStatus = E_NOT_OK;

    /* Get interrupt configuration informations */
    IntSrcConfigPtr = Intc_ConfigPtr->CoreConfigPtr[CoreId].IntSrcConfigPtr;
    if (NULL_PTR != IntSrcConfigPtr)
    {
        /* Get total number of interrupts in core */
        IntSrcNum = Intc_ConfigPtr->CoreConfigPtr[CoreId].TotalIntSrcNum;

        /* Loop to check if the specified interrupt is installed */
        IntSrcCnt = 0U;
        while ((IntSrcCnt < IntSrcNum) && (E_NOT_OK == RetStatus))
        {
            /* Find the specified interrupt id 'IntSrcId' */
            if (IntSrcConfigPtr[IntSrcCnt].intID == IntSrcId)
            {
                RetStatus = E_OK;
            }
            IntSrcCnt++;
        }
    }

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Intc_CheckIntSrcStatus
*
*   Service ID              : None.
*
*   Description             : Detect whether the interrupt source is valid and whether the interrupt
*                               source has been installed.
*
*   Parameters in           : IntSrcId: Interrupt source ID
*                             ServiceId: Function service ID
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant\(thread-safe)
*
*   Return value            : Std_ReturnType: Return the DET check status
*                             - E_OK: No error
*                             - E_NOT_OK: Error exists
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, INTC_PRIVATE_CODE) Intc_CheckIntSrcStatus
(
    Intc_IntSrcType IntSrcId,
    uint8 ServiceId
)
{
    uint8          CoreIdx;
    Std_ReturnType Status;
    /* 'ThisCoreId' indicate current core number which called this API */
    Mcal_CoreType  CoreId;

    Status = E_NOT_OK;

    /* #Violation: Intc_c_REF_1 */
    CoreId = Mcal_GetCoreId();

    if (INTC_INITIALIZED == *Intc_CoreInstallStatusPtr[CoreId])
    {
        if (IntSrcId > INTC_MAX_SPI_INTID)
        {
            /* INTID is out of range */
            Intc_ReportError((uint8)ServiceId, (uint8)INTC_E_INTSRC_NUM_OUT_RANGE);
        }
        else
        {
            if (IntSrcId <= INTC_MAX_PPI_INTID)
            {
                /* Check whether the interrupt is installed */
                Status = Intc_CheckIntSrcInstallStatus(IntSrcId, CoreId);
            }
            else
            {
                /* Loop whether the interrupt is installed on a specific core  */
                for (CoreIdx = 0U; (CoreIdx < MCAL_NUMBER_OF_CORES) && (E_NOT_OK == Status); CoreIdx++)
                {
                    /* #Violation: Intc_c_REF_4 */
                    Status = Intc_CheckIntSrcInstallStatus(IntSrcId, (Mcal_CoreType)CoreIdx);
                }
            }

            if (E_NOT_OK == Status)
            {
                /* Specified interrupt "IntSrcId" is not configured */
                Intc_ReportError((uint8)ServiceId, (uint8)INTC_E_INTID_NOT_CONFIGURED);
            }
        }
    }
    else
    {
        /* INTC module has not finished initialization */
        Intc_ReportError((uint8)ServiceId, (uint8)INTC_E_INTSRC_UNINSTALLED);
    }

    return Status;
}

#if (INTC_CFG_SGI_INT_EN == STD_ON)
/****************************************************************************************************
 *   Function Name           : Intc_CheckGenSwIntStatusDetCheck
 *
 *   Service ID              : None.
 *
 *   Description             : This API returns the Det error of Intc_CheckGenSwIntStatus.
 *
 *   Parameters in           : CoreId: Core id.
 *                             IntSrcId: Interrupt source ID
 *                             ServiceId: Function service ID
 *                             TargetCore: The target core(s) of the software interrupt.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : E_OK: DET check passed.
 *                             E_NOT_OK: DET check failed.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, INTC_PRIVATE_CODE) Intc_CheckGenSwIntStatusDetCheck
(
    Mcal_CoreType CoreId,
    Intc_IntSrcType IntSrcId,
    uint8 ServiceId,
    Intc_TargetCoreType TargetCore
)
{
    uint8          TargetCluster;
    Std_ReturnType RetStatus;

    RetStatus = E_OK;
    if (IntSrcId <= INTC_MAX_SGI_INTID)
    {
        /* SGI interrupt */
        /* Get bit position of core ID */
        /* Check whether the core is correct */
        TargetCluster = ((TargetCore <= INTC_TARGET_CORE1) || (TargetCore == INTC_TARGET_CORE0_CORE1))
                            ? 0U
                            : ((TargetCore > INTC_TARGET_CORE2_CORE3) ? 0xFFU : 1U);
        if (((uint8)CoreId >> 1U) != TargetCluster)
        {
            /* Core0 and core1 can only trigger SGI interrupt that are in GIC0,
                * Core2 and core3 can only trigger SGI interrupt that are in GIC1,
                * SGI interrupts are not allowed to be triggered across clusters. */
            Intc_ReportError((uint8)INTC_SID_GENSWTINTERRUPT, (uint8)INTC_E_GENSGI_WRONG_CORE);
            RetStatus = E_NOT_OK;
        }
    }
    else if ((IntSrcId >= INTC_MIN_SPI_SOFTINT_INTID) && (IntSrcId <= INTC_MAX_SPI_SOFTINT_INTID))
    {
        /* SPI software interrupt(To Core0 or Core2), Implemented by INTC */
        if ((INTC_TARGET_CORE2_CORE3 == TargetCore) || (INTC_TARGET_CORE0_CORE1 == TargetCore) ||
            (INTC_TARGET_CORE1 == TargetCore) || (INTC_TARGET_CORE3 == TargetCore))
        {
            /* The target core of the SPI software interrupt can only be core0 or core2  */
            Intc_ReportError((uint8)INTC_SID_GENSWTINTERRUPT, (uint8)INTC_E_GENSGI_WRONG_CORE);
            RetStatus = E_NOT_OK;
        }
    }
    else if ((IntSrcId >= INTC_MIN_SPI_SOFTINT_INTID_1) && (IntSrcId <= INTC_MAX_SPI_SOFTINT_INTID_1))
    {
        /* SPI software interrupt(To Core1 or Core3), Implemented by INTC */
        if ((INTC_TARGET_CORE2_CORE3 == TargetCore) || (INTC_TARGET_CORE0_CORE1 == TargetCore) ||
            (INTC_TARGET_CORE0 == TargetCore) || (INTC_TARGET_CORE2 == TargetCore))
        {
            /* The target core of the SPI software interrupt can only be core1 or core3  */
            Intc_ReportError((uint8)INTC_SID_GENSWTINTERRUPT, (uint8)INTC_E_GENSGI_WRONG_CORE);
            RetStatus = E_NOT_OK;
        }
    }
    else
    {
        /* Interrupt ID is greater than threshold: out of range */
        Intc_ReportError((uint8)ServiceId, (uint8)INTC_E_INTSRC_NUM_OUT_RANGE);
        RetStatus = E_NOT_OK;
    }
    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Intc_CheckGenSwIntStatus
*
*   Service ID              : None.
*
*   Description             : Detect whether the interrupt source is valid and whether the interrupt
*                               source has been installed.
*
*   Parameters in           : IntSrcId: Interrupt source ID
*                             ServiceId: Function service ID
*                             CoreListBits: The target core(s) of the software interrupt.
*                                           Bit0 represents core0, bit1 represents core1.
*                                           - core0: 0x01
*                                           - core1: 0x02
*                                           - core0 and core1: 0x03
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant\(thread-safe)
*
*   Return value            : Std_ReturnType: Return the DET check status
*                             - E_OK: No error
*                             - E_NOT_OK: Error exists
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, INTC_PRIVATE_CODE) Intc_CheckGenSwIntStatus
(
    Intc_IntSrcType IntSrcId,
    uint8 ServiceId,
    Intc_TargetCoreType TargetCore
)
{
    Std_ReturnType RetStatus;
    /* 'ThisCoreId' indicate current core number which called this API */
    Mcal_CoreType  CoreId;

    RetStatus = E_OK;

    /* #Violation: Intc_c_REF_1 */
    CoreId = Mcal_GetCoreId();
    if (INTC_INITIALIZED == *Intc_CoreInstallStatusPtr[CoreId])
    {
        RetStatus = Intc_CheckGenSwIntStatusDetCheck(CoreId, IntSrcId, ServiceId, TargetCore);

        if (E_OK == RetStatus)
        {
            RetStatus = E_NOT_OK;
            if ((INTC_TARGET_CORE0 == TargetCore) || (INTC_TARGET_CORE0_CORE1 == TargetCore))
            {
                /* Target core is core0 */
                /* Check if the target interrupt source has been installed in core0 */
                RetStatus = Intc_CheckIntSrcInstallStatus(IntSrcId, MCAL_CORE0);
            }

            if ((INTC_TARGET_CORE1 == TargetCore) || (INTC_TARGET_CORE0_CORE1 == TargetCore))
            {
                /* Target core is core1 */
                /* Check if the target interrupt source has been installed in core1 */
                RetStatus = Intc_CheckIntSrcInstallStatus(IntSrcId, MCAL_CORE1);
            }

#if (MCAL_NUMBER_OF_CORES > 2U)
            if ((INTC_TARGET_CORE2 == TargetCore) || (INTC_TARGET_CORE2_CORE3 == TargetCore))
            {
                /* Target core is core2 */
                /* Check if the target interrupt source has been installed in core2 */
                RetStatus = Intc_CheckIntSrcInstallStatus(IntSrcId, MCAL_CORE2);
            }
#endif /* (MCAL_NUMBER_OF_CORES \> 2U) */

#if (MCAL_NUMBER_OF_CORES > 3U)
            if ((INTC_TARGET_CORE3 == TargetCore) || (INTC_TARGET_CORE2_CORE3 == TargetCore))
            {
                /* Target core is core3 */
                /* Check if the target interrupt source has been installed in core3 */
                RetStatus = Intc_CheckIntSrcInstallStatus(IntSrcId, MCAL_CORE3);
            }
#endif /* (MCAL_NUMBER_OF_CORES \> 3U) */

            if (E_NOT_OK == RetStatus)
            {
                /* Specified interrupt "IntSrcId" is not configured */
                Intc_ReportError((uint8)ServiceId, (uint8)INTC_E_INTID_NOT_CONFIGURED);
            }
        }
    }
    else
    {
        /* INTC module has not finished initialization */
        Intc_ReportError((uint8)ServiceId, (uint8)INTC_E_INTSRC_UNINSTALLED);
        RetStatus = E_NOT_OK;
    }

    return RetStatus;
}
#endif /* (INTC_CFG_SGI_INT_EN \== STD_ON) */
#endif /* (INTC_DEV_ERROR_DETECT \== STD_ON) */

/* #Violation: Intc_c_REF_2 */
#define INTC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Intc_c_REF_5 */
#include "Intc_MemMap.h"
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/* #Violation: Intc_c_REF_2 */
#define INTC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Intc_c_REF_5 */
#include "Intc_MemMap.h"

/****************************************************************************************************
*   Function Name           : Intc_InstallInterrupt
*
*   Service ID              : 0x00.
*
*   Description             : Install the interrupts.
*                             Master core must invoke this API first, then the slave core can invoke 
*                             it.
*
*   Parameters in           : ConfigPtr: Pointer to Intc configuration set list
*                             IntTable: Pointer to Interrupt table
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : None.
*
*   Return value            : Intc_InsStaType:
*                               INTC_STA_ERR: Interrupt source list parameter error
*                               INTC_STA_INSTALLING: Installing the interrupt source
*                               INTC_STA_INS_FINISHED: All interrupt source installed successfully
*                               INTC_STA_INS_BLOCKED: The interrupt is not installed because the 
                                    master core is installing the interrupt source
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Intc_c_REF_10 */
FUNC(Intc_InsStaType, INTC_PUBLIC_CODE) Intc_InstallInterrupt
(
    CONSTP2CONST(Intc_ConfigType, AUTOMATIC, INTC_APPL_CONST) ConfigPtr,
    P2VAR(Intc_HandlerType, AUTOMATIC, INTC_APPL_DATA) IntTablePtr
)
{
#if (INTC_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType Status;
#endif /* (INTC_DEV_ERROR_DETECT \== STD_ON) */
    Std_ReturnType              LockStatus;
    const Intc_InterruptConfig *MapConfigPtr;
    Intc_InsStaType             InstStatus;
    Mcal_CoreType               CoreId;
    Intc_ErrorFlag              ErrStatus;

    InstStatus = INTC_STA_ERR;
    LockStatus = E_OK;

#if (INTC_DEV_ERROR_DETECT == STD_ON)
    Status = Intc_CheckInitErrStatus(ConfigPtr);
    if (E_OK == Status)
#endif /* (INTC_DEV_ERROR_DETECT \== STD_ON) */
    {
        /* Get core id that is currently executing */
        /* #Violation: Intc_c_REF_1 */
        CoreId = Mcal_GetCoreId();
        /* This API has to be called by the master core first */
        if ((MCAL_MASTER_CORE == CoreId) || (INTC_MASTER_CORE_MAPPED == Intc_IntSrcMapStatus))
        {
            InstStatus = INTC_STA_INSTALLING;
        }
        else
        {
            /* Master core is installing the interrupts */
            InstStatus = INTC_STA_INS_BLOCKED;
        }

        if (INTC_STA_INSTALLING == InstStatus)
        {
            if (MCAL_MASTER_CORE != CoreId)
            {
                /* A lock for the slave core to install SPI interrupts */
                LockStatus = Mcal_GetLock(MCAL_LOCK_ID_INTC);
            }

            if (E_OK == LockStatus)
            {
                /* Installing all interrupt sources */
                MapConfigPtr = ConfigPtr->CoreConfigPtr[CoreId].IntSrcConfigPtr;
                ErrStatus = Intc_Hal_InstallInterrupt(
                    MapConfigPtr, ConfigPtr->CoreConfigPtr[CoreId].TotalIntSrcNum, IntTablePtr);

                if (MCAL_MASTER_CORE != CoreId)
                {
                    /* Release the software lock for the slave core */
                    Mcal_ReleaseLock(MCAL_LOCK_ID_INTC);
                }

                if (INTC_ERRORFLAG_SUCCESS != ErrStatus)
                {
                    InstStatus = INTC_STA_ERR;
#if (INTC_DEV_ERROR_DETECT == STD_ON)
                    /* Install the interrupts failed */
                    Intc_ReportError((uint8)INTC_SID_INSTALLINT, (uint8)INTC_E_INSTALL_FAILED);
#endif /* (INTC_DEV_ERROR_DETECT \== STD_ON) */
                }
                else
                {
                    if (MCAL_MASTER_CORE == CoreId)
                    {
                        /* All external interrupt sources installed successfully */
                        Intc_IntSrcMapStatus = INTC_MASTER_CORE_MAPPED;
#if (INTC_DEV_ERROR_DETECT == STD_ON)
                        Intc_ConfigPtr = ConfigPtr;
#endif /* (INTC_DEV_ERROR_DETECT \== STD_ON) */
                    }
                    /* Set group priority and sub-priority */
                    Intc_Hal_SetMinGroupPriority(INTC_FIQ_MIN_PRIORITY, INTC_IRQ_MIN_PRIORITY);

#if (INTC_DEV_ERROR_DETECT == STD_ON)
                    *Intc_CoreInstallStatusPtr[CoreId] = INTC_INITIALIZED;
#endif /* (INTC_DEV_ERROR_DETECT \== STD_ON) */
                    InstStatus = INTC_STA_INS_FINISHED;
                }
            }
            else
            {
                /* Get lock failed */
                InstStatus = INTC_STA_ERR;

#if (INTC_DEV_ERROR_DETECT == STD_ON)
                /* Get lock timeout */
                Intc_ReportError((uint8)INTC_SID_INSTALLINT, (uint8)INTC_E_LOCK_TIMEOUT);
#endif /* (INTC_DEV_ERROR_DETECT \== STD_ON) */
            }
        }
    }

    return InstStatus;
}

/****************************************************************************************************
*   Function Name           : Intc_DisableInterrupt
*
*   Service ID              : 0x01.
*
*   Description             : Disable a specified interrupt source.
*
*   Parameters in           : IntSrcId: Interrupt ID.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant\(thread-safe)
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Intc_c_REF_10 */
FUNC(void, INTC_PUBLIC_CODE) Intc_DisableInterrupt
(
    Intc_IntSrcType IntSrcId
)
{
#if (INTC_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType DetErr;
#endif /* (INTC_DEV_ERROR_DETECT \== STD_ON) */
    Std_ReturnType LockStatus;
    Intc_ErrorFlag ErrStatus;

#if (INTC_DEV_ERROR_DETECT == STD_ON)
    ErrStatus = INTC_ERRORFLAG_SUCCESS;

    DetErr = Intc_CheckIntSrcStatus(IntSrcId, INTC_SID_DISABLEINT);
    if (E_OK == DetErr)
#endif /* (INTC_DEV_ERROR_DETECT \== STD_ON) */
    {
        INTC_ENTER_CRITICAL_SECTION(DisableInterrupt);
        if (IntSrcId <= (Intc_IntSrcType)INTC_MAX_PPI_INTID)
        {
            /* Disable the internal interrupt sources */
            ErrStatus = Intc_Hal_DisableInterrupt(IntSrcId);
            INTC_EXIT_CRITICAL_SECTION(DisableInterrupt);
        }
        else
        {
            /* Lock for disable interrupts */
            LockStatus = Mcal_GetLock(MCAL_LOCK_ID_INTC);
            if (E_OK == LockStatus)
            {
                /* Disable the shared peripheral interrupt sources */
                ErrStatus = Intc_Hal_DisableInterrupt(IntSrcId);
                /* Release software lock for INTC */
                Mcal_ReleaseLock(MCAL_LOCK_ID_INTC);
                INTC_EXIT_CRITICAL_SECTION(DisableInterrupt);
            }
            else
            {
                INTC_EXIT_CRITICAL_SECTION(DisableInterrupt);
#if (INTC_DEV_ERROR_DETECT == STD_ON)
                /* Get lock timeout */
                Intc_ReportError((uint8)INTC_SID_DISABLEINT, (uint8)INTC_E_LOCK_TIMEOUT);
#endif /* (INTC_DEV_ERROR_DETECT \== STD_ON) */
            }
        }

#if (INTC_DEV_ERROR_DETECT == STD_ON)
        if (INTC_ERRORFLAG_REPEAT == ErrStatus)
        {
            /* Interrupt "IntSrcId" have already been disabled */
            Intc_ReportError((uint8)INTC_SID_DISABLEINT, (uint8)INTC_E_ALREADY_DISABLED);
        }
#else  /* (INTC_DEV_ERROR_DETECT \== STD_ON) */
        MCAL_UNUSED_VAR(ErrStatus);
#endif /* (INTC_DEV_ERROR_DETECT \== STD_ON) */
    }
}

/****************************************************************************************************
*   Function Name           : Intc_EnableInterrupt
*
*   Service ID              : 0x02.
*
*   Description             : Enable a specified interrupt source
*
*   Parameters in           : IntSrcId: Interrupt ID.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant\(thread-safe)
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Intc_c_REF_10 */
FUNC(void, INTC_PUBLIC_CODE) Intc_EnableInterrupt
(
    Intc_IntSrcType IntSrcId
)
{
#if (INTC_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType Err;
#endif /* (INTC_DEV_ERROR_DETECT \== STD_ON) */
    Std_ReturnType LockStatus;
    Intc_ErrorFlag ErrStatus;

#if (INTC_DEV_ERROR_DETECT == STD_ON)
    ErrStatus = INTC_ERRORFLAG_SUCCESS;

    Err = Intc_CheckIntSrcStatus(IntSrcId, INTC_SID_ENABLEINT);
    if (E_OK == Err)
#endif /* (INTC_DEV_ERROR_DETECT \== STD_ON) */
    {
        INTC_ENTER_CRITICAL_SECTION(EnableInterrupt);
        if (IntSrcId <= (Intc_IntSrcType)INTC_MAX_PPI_INTID)
        {
            /* Enable the internal interrupt sources */
            ErrStatus = Intc_Hal_EnableInterrupt(IntSrcId);
            INTC_EXIT_CRITICAL_SECTION(EnableInterrupt);
        }
        else
        {
            /* Lock for enable interrupts */
            LockStatus = Mcal_GetLock(MCAL_LOCK_ID_INTC);
            if (E_OK == LockStatus)
            {
                /* Enable the shared peripheral interrupt sources */
                ErrStatus = Intc_Hal_EnableInterrupt(IntSrcId);
                /* Release lock */
                Mcal_ReleaseLock(MCAL_LOCK_ID_INTC);
                INTC_EXIT_CRITICAL_SECTION(EnableInterrupt);
            }
            else
            {
                INTC_EXIT_CRITICAL_SECTION(EnableInterrupt);
#if (INTC_DEV_ERROR_DETECT == STD_ON)
                /* Get lock timeout */
                Intc_ReportError((uint8)INTC_SID_ENABLEINT, (uint8)INTC_E_LOCK_TIMEOUT);
#endif /* (INTC_DEV_ERROR_DETECT \== STD_ON) */
            }
        }

#if (INTC_DEV_ERROR_DETECT == STD_ON)
        if (INTC_ERRORFLAG_REPEAT == ErrStatus)
        {
            /* Interrupt "IntSrcId" have already been enabled */
            Intc_ReportError((uint8)INTC_SID_ENABLEINT, (uint8)INTC_E_ALREADY_ENABLED);
        }
#else /* (INTC_DEV_ERROR_DETECT \== STD_ON) */
        MCAL_UNUSED_VAR(ErrStatus);
#endif  /* (INTC_DEV_ERROR_DETECT \== STD_ON) */
    }
}

#if (INTC_CFG_SGI_INT_EN == STD_ON)
/****************************************************************************************************
*   Function Name           : Intc_GenSwInterrupt
*
*   Service ID              : 0x03.
*
*   Description             : Trigger a software interrupt(SGI interrupt)
*
*   Parameters in           : IntSrcId: Software interrupt ID
*                             TargetCore: Target core to be triggered
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant\(thread-safe)
*
*   Return value            : E_OK: No error.
*                             E_NOT_OK: Trigger fail.
*                             INTC_ATOMIC_BUSY: Atomic busy.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Intc_c_REF_10 */
FUNC(Std_ReturnType, INTC_PUBLIC_CODE) Intc_GenSwInterrupt
(
    Intc_IntSrcType IntSrcId,
    Intc_TargetCoreType TargetCore
)
{
#if (INTC_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType Err;
#endif /* (INTC_DEV_ERROR_DETECT \== STD_ON) */
    Intc_ErrorFlag ErrStatus;
    Std_ReturnType ReturnValue;

    ReturnValue = E_NOT_OK;
#if (INTC_DEV_ERROR_DETECT == STD_ON)
    Err = Intc_CheckGenSwIntStatus(IntSrcId, INTC_SID_GENSWTINTERRUPT, TargetCore);
    if (E_OK == Err)
#endif /* (INTC_DEV_ERROR_DETECT \== STD_ON) */
    {
        /* Generate the software interrupt */
        INTC_ENTER_CRITICAL_SECTION(GenSwInterrupt);
        ErrStatus = Intc_Hal_GenerateSoftwareInterrupt(IntSrcId, TargetCore);
        INTC_EXIT_CRITICAL_SECTION(GenSwInterrupt);
        if (INTC_ERRORFLAG_ATOMIC_BUSY == ErrStatus)
        {
            ReturnValue = INTC_ATOMIC_BUSY;
        }
#if (INTC_DEV_ERROR_DETECT == STD_ON)
        else if (INTC_ERRORFLAG_FAILURE == ErrStatus)
        {
            /* Wrong target core */
            Intc_ReportError((uint8)INTC_SID_GENSWTINTERRUPT, (uint8)INTC_E_GENSGI_FAILED);
        }
#endif /* (INTC_DEV_ERROR_DETECT \== STD_ON) */
        else
        {
            ReturnValue = E_OK;
        }
    }

    return ReturnValue;
}
#endif /* (INTC_CFG_GEN_SW_INT_API \== STD_ON) */


#if (INTC_CFG_VERSION_INFO_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Intc_GetVersionInfo
*
*   Service ID              : 0x05.
*
*   Description             : This service returns the version information of this module.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : VersionInfoPtr: Pointer to where to store the version information of 
*                             this module.
*
*   Sync/Async              : Asynchronous
*
*   Reentrancy              : Reentrant
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Intc_c_REF_10 */
FUNC(void, INTC_PUBLIC_CODE) Intc_GetVersionInfo
(
    CONSTP2VAR(Std_VersionInfoType, AUTOMATIC, INTC_APPL_DATA) VersionInfoPtr
)
{
#if (INTC_DEV_ERROR_DETECT == STD_ON)
    if (NULL_PTR == VersionInfoPtr)
    {
        Intc_ReportError((uint8)INTC_SID_GETVERSIONINFO, (uint8)INTC_E_PARAM_POINTER);
    }
    else
#endif /* (INTC_DEV_ERROR_DETECT \== STD_ON) */
    {
        VersionInfoPtr->vendorID = (uint16)INTC_VENDOR_ID;
        VersionInfoPtr->moduleID = (uint16)INTC_MODULE_ID;
        VersionInfoPtr->sw_major_version = (uint8)INTC_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = (uint8)INTC_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = (uint8)INTC_SW_PATCH_VERSION;
    }
}
#endif /* (INTC_VERSION_INFO_API \== STD_ON) */

/* #Violation: Intc_c_REF_2 */
#define INTC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Intc_c_REF_5 */
#include "Intc_MemMap.h"

/****************************************************************************************************
**                                  End of File                                                    **
****************************************************************************************************/
