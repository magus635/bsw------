/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Fls.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DFlash
*
*   brief                 : This file contains all function declarations of DFlash Driver
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
*#Fls_h_REF_1:MISRAC2012-Rule-20.7;
* Justification:Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*
*#Fls_h_REF_2:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers
*
*/

#ifndef FLS_H_
#define FLS_H_

/***************************************************************************************************
*                               Include
***************************************************************************************************/
#include "Fls_GeneralTypes.h"
#include "Fls_Cfg.h"
#include "Mcall.h"
#include "Std_Types.h"
#include "Fls_Version.h"
#include "Fls_PBcfg.h"

/* Types and definitions specific for flash driver shall be given in Fls.h. */
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
/* Transient Faults */
#define FLS_E_ERASE_FAILED                (0x01U)
#define FLS_E_WRITE_FAILED                (0x02U)
#define FLS_E_READ_FAILED                 (0x03U)
#define FLS_E_COMPARE_FAILED              (0x04U)
/* #Violation: Fls_h_REF_2 */
#define FLS_E_UNEXPECTED_FLASH_ID         (0x05U)
#define FLS_E_BLANKCHECK_FAILED           (0x20U)

/* runtime error */
/* Erase Verification failed */
#define FLS_E_VERIFY_ERASE_FAILED         (0x07U)
/* Write Verification failed */
#define FLS_E_VERIFY_WRITE_FAILED         (0x08U)
#if (FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON)
/* Timeout for Erase/write jobs */
#define FLS_E_TIMEOUT                     (0x09U)
#endif /* \(FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON) */

/* Error classification. [SWS_Fls_00004] */
/* wrong parameter */
#define FLS_E_PARAM_CONFIG                (0x01U)
/* wrong Address */
#define FLS_E_PARAM_ADDRESS               (0x02U)
/* wrong length */
#define FLS_E_PARAM_LENGTH                (0x03U)
/* wrong Data */
#define FLS_E_PARAM_DATA                  (0x04U)
/* without initialization */
#define FLS_E_UNINIT                      (0x05U)
/* Driver is busy */
#define FLS_E_BUSY                        (0x06U)
/* NULL parameter */
#define FLS_E_PARAM_POINTER               (0x0AU)

#if (FLS_USE_INTERRUPTS == STD_ON)
/* Non-AUTOSAR */
/* The FLS interrupt trigger exception */
#define FLS_E_INTC_TRIGGER_EXCEPTION      (0xE1U)
#endif /* \(FLS_USE_INTERRUPTS == STD_ON) */

/* FLS module initialization failed */
#define FLS_E_INIT_FAILED                 (0xE2U)
/* Report DET FLS module not configured for current Core */
#define FLS_E_CORE_NOT_CONFIGURED         (0xE0U)

#if (STD_ON == FLS_SAFETY_ENABLE)
#define FLS_E_REG_CHECK_FAILED            (0xF0U)
#endif /* \(FLS_SAFETY_ENABLE == STD_ON\) */

/* API Service ID */
#define FLS_SID_INIT                      (0x00U)
#define FLS_SID_ERASE                     (0x01U)
#define FLS_SID_WRITE                     (0x02U)
#define FLS_SID_CANCEL                    (0x03U)
#define FLS_SID_GETSTATUS                 (0x04U)
#define FLS_SID_GETJOBRESULT              (0x05U)
#define FLS_SID_MAIN                      (0x06U)
#define FLS_SID_READ                      (0x07U)
#define FLS_SID_COMPARE                   (0x08U)
#define FLS_SID_SETMODE                   (0x09U)
#define FLS_SID_BLANKCHECK                (0x0AU)
#define FLS_SID_GETVERSIONINFO            (0x10U)
/* Non-AUTOSAR */
#if (FLS_USE_INTERRUPTS == STD_ON)
#define FLS_SID_INTERRUPT                 (0xE1U)
#endif /* \(FLS_USE_INTERRUPTS == STD_ON) */
#define FLS_SID_READSYNC                  (0xE2U)
#define FLS_SID_COMPARESYNC               (0xE3U)
#define FLS_SID_BLANKCHECKSYNC            (0xE4U)

/* Fls_ReadWordsSync Api Return Macro Definitions */
#define FLS_READ_SUCCESS                  (0x00U)
#define FLS_READ_BUSY                     (0x07U)
#define FLS_READ_ECC                      (0x08U)
#define FLS_READ_PARAM_ERR                (0x09U)

/* Fls_CompareWordsSync Api Return Macro Definitions */
#define FLS_COMPARE_EQUAL                 (0x00U)
#define FLS_COMPARE_NOT_EQUAL             (0x01U)
#define FLS_COMPARE_BUSY                  (0x07U)
#define FLS_COMPARE_ECC                   (0x08U)
#define FLS_COMPARE_PARAM_ERR             (0x09U)

/* Fls_BlankCheckSync Api Return Macro Definitions */   
#define FLS_BLANKCHECK_EMPTY              (0x00U)
#define FLS_BLANKCHECK_DIRTY              (0x01U)
#define FLS_BLANKCHECK_OVERTIME           (0x06U)
#define FLS_BLANKCHECK_BUSY               (0x07U)
#define FLS_BLANKCHECK_PARAM_ERR          (0x09U)

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
/* #Violation: Fls_h_REF_2 */
#define FLS_START_SEC_CODE_ASIL_D_GLOBAL
#include "Fls_MemMap.h"
extern FUNC(void, FLS_PUBLIC_CODE) Fls_Init
(
    P2CONST(Fls_ConfigType, AUTOMATIC, FLS_CONFIG_CONST) ConfigPtr
);


extern FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_Erase
(
    Fls_AddressType TargetAddress, 
    Fls_LengthType Length
);


extern FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_Write
(
    Fls_AddressType TargetAddress, 
    P2CONST(uint8, AUTOMATIC, FLS_APPL_CONST) SourceAddressPtr, 
    Fls_LengthType Length
);

#if (FLS_COMPARE_API == STD_ON)
extern FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_Compare
(
    Fls_AddressType SourceAddress, 
    P2CONST(uint8, AUTOMATIC, FLS_APPL_CONST) TargetAddressPtr,
    Fls_LengthType Length
);
#endif /* (FLS_COMPARE_API  \== STD_ON) */

#if (FLS_CANCEL_API == STD_ON)
extern FUNC(void, FLS_PUBLIC_CODE) Fls_Cancel
(
    void
);
#endif /* (FLS_CANCEL_API  \== STD_ON) */

#if (FLS_SET_MODE_API == STD_ON)
extern FUNC(void, FLS_PUBLIC_CODE) Fls_SetMode
(
    MemIf_ModeType Mode
);
#endif /* (FLS_SET_MODE_API  \== STD_ON) */


extern FUNC(void, FLS_PUBLIC_CODE) Fls_MainFunction
(
    void
);

extern FUNC(Std_ReturnType, FLS_PUBLIC_CODE)  Fls_Read
(
    Fls_AddressType SourceAddress,
    /* #Violation: Fls_h_REF_1 */
    P2VAR(uint8, AUTOMATIC, FLS_APPL_DATA) TargetAddressPtr,
    Fls_LengthType Length
);

#if (FLS_BLANK_CHECK_API == STD_ON)
extern FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_BlankCheck
(
    Fls_AddressType TargetAddress, 
    Fls_LengthType Length
);
#endif /* (FLS_BLANK_CHECK_API  \== STD_ON) */

#if (FLS_GET_STATUS_API == STD_ON)
extern FUNC(MemIf_StatusType, FLS_PUBLIC_CODE) Fls_GetStatus
(
    void
);
#endif /* (FLS_GET_STATUS_API  \== STD_ON) */

#if (FLS_GET_JOB_RESULT_API == STD_ON)
extern FUNC(MemIf_JobResultType, FLS_PUBLIC_CODE) Fls_GetJobResult
(
    void
);
#endif /* (FLS_GET_JOB_RESULT_API  \== STD_ON) */

extern FUNC(uint8, FLS_PUBLIC_CODE) Fls_ReadWordsSync
(
    Fls_AddressType SourceAddress, 
    /* #Violation: Fls_h_REF_1 */
    CONSTP2VAR(uint32, AUTOMATIC, FLS_APPL_DATA) TargetAddressPtr,
    Fls_LengthType Length
);

extern FUNC(uint8, FLS_PUBLIC_CODE) Fls_CompareWordsSync
(
    Fls_AddressType SourceAddress, 
    CONSTP2CONST(uint32, AUTOMATIC, FLS_APPL_CONST) TargetAddressPtr,
    Fls_LengthType Length
);

extern FUNC(uint8, FLS_PUBLIC_CODE) Fls_BlankCheckSync
(
    Fls_AddressType TargetAddress,
    Fls_LengthType Length
);

#if (FLS_VERSION_INFO_API == STD_ON)
extern FUNC(void, FLS_PUBLIC_CODE) Fls_GetVersionInfo
(
    /* #Violation: Fls_h_REF_1 */
    P2VAR(Std_VersionInfoType, AUTOMATIC, FLS_APPL_DATA) VersionInfoPtr
);
#endif /* (FLS_VERSION_INFO_API  \== STD_ON) */

#if (FLS_USE_INTERRUPTS == STD_ON)
extern FUNC(void, FLS_PUBLIC_CODE) Fls_Flash_ISRHandler
(
    void
);
#endif /* (FLS_USE_INTERRUPTS  \== STD_ON) */
/* #Violation: Fls_h_REF_2 */
#define FLS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Fls_MemMap.h"

#endif /* FLS_H_ */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

