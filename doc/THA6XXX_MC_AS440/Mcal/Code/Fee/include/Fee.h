/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Fee.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DFlash
*
*   brief                 : This file contains all function declarations of FEE module
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
*#Fee_h_REF_1:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*/

#ifndef FEE_H_
#define FEE_H_

/***************************************************************************************************
*                               Include
***************************************************************************************************/
/* The types shall not be changed or extended. Refer to [SWS_Fee_00084], [SWS_Fee_00016] */
#include "Fee_GeneralTypes.h"
#include "Fee_Cfg.h"
#include "Std_Types.h"

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
/* FEE instance ID */
#define FEE_INSTANCE_ID                  (0U)

#define FEE_INIT_ID                      (0x00U)
#define FEE_SETMODE_ID                   (0x01U)
#define FEE_READ_ID                      (0x02U)
#define FEE_WRITE_ID                     (0x03U)
#define FEE_CANCEL_ID                    (0x04U)
#define FEE_GETSTATUS_ID                 (0x05U)
#define FEE_GETJOBRESULT_ID              (0x06U)
#define FEE_INVALIDATEBLOCK_ID           (0x07U)
#define FEE_GETVERSIONINFO_ID            (0x08U)
#define FEE_JOBENDNOTIFICATION_ID        (0x10U)
#define FEE_JOBERRORNOTIFICATION_ID      (0x11U)
#define FEE_MAINFUNCTION_ID              (0x12U)
#define FEE_SID_GETCYCLECOUNT            (0x13U)

#if (FEE_DEV_ERROR_DETECT == STD_ON)
#define FEE_E_UNINIT                     (0x01U)
#define FEE_E_INVALID_BLOCK_NO           (0x02U)
#define FEE_E_INVALID_BLOCK_OFS          (0x03U)
#define FEE_E_PARAM_POINTER              (0x04U)
#define FEE_E_INVALID_BLOCK_LEN          (0x05U)
#define FEE_E_INIT_FAILED                (0x09U)
/* Non-AUTOSAR */
/* Report DET FEE module not configured for current Core */
#define FEE_E_CORE_NOT_CONFIGURED        (0xE0U)
#define FEE_E_UNCONFIG_BLOCK_EXCEEDED    (0xE1U)
#endif /* (FEE_DEV_ERROR_DETECT \== STD_ON) */

/* Runtime error */
#define FEE_E_BUSY                       (0x06U)
#define FEE_E_INVALID_CANCEL             (0x08U)
/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/


/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/
extern const Fee_ConfigType Fee_ConfigSet[FEE_CONFIG_COUNT];

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
/* #Violation: Fee_h_REF_1 */
#define FEE_START_SEC_CODE_ASIL_D_GLOBAL
#include "Fee_MemMap.h"

#if (FEE_VERSION_INFO_API == STD_ON)
extern FUNC(void, FEE_PUBLIC_CODE) Fee_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, FEE_APPL_DATA) VersionInfoPtr
);
#endif /* (FEE_VERSION_INFO_API  \== STD_ON) */

extern FUNC(void, FEE_PUBLIC_CODE) Fee_Init
(
    P2CONST(Fee_ConfigType, AUTOMATIC, FEE_CONFIG_CONST) ConfigPtr
);

#if (FEE_SETMODE_API == STD_ON)
extern FUNC(void, FEE_PUBLIC_CODE) Fee_SetMode
(
    MemIf_ModeType Mode
);
#endif /* (FEE_SETMODE_API  \== STD_ON) */

extern FUNC(Std_ReturnType, FEE_PUBLIC_CODE) Fee_Read
(
    uint16 BlockNumber,
    uint16 BlockOffset,
    P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA) DataBufferPtr,
    uint16 Length
);

extern FUNC(Std_ReturnType, FEE_PUBLIC_CODE) Fee_Write
(
    uint16 BlockNumber,
    P2CONST(uint8, AUTOMATIC, FEE_APPL_CONST) DataBufferPtr
);

extern FUNC(void, FEE_PUBLIC_CODE) Fee_Cancel
(
    void
);

extern FUNC(MemIf_StatusType, FEE_PUBLIC_CODE) Fee_GetStatus
(
    void
);

extern FUNC(MemIf_JobResultType, FEE_PUBLIC_CODE) Fee_GetJobResult
(
    void
);

extern FUNC(Std_ReturnType, FEE_PUBLIC_CODE) Fee_InvalidateBlock
(
    uint16 BlockNumber
);

extern FUNC(Std_ReturnType, FEE_PUBLIC_CODE) Fee_EraseImmediateBlock
(
    uint16 BlockNumber
);

extern FUNC(void, FEE_PUBLIC_CODE) Fee_MainFunction
(
    void
);

/* Function declaration of Fls Job End Notification */
extern void Fee_JobEndNotification
(
    void
);

/* Function declaration of Fls Job Error Notifications */
extern void Fee_JobErrorNotification
(
    void
);

extern Std_ReturnType Fee_GetCycleCount
(
    uint16 BlockNumber,
    P2VAR(uint32, AUTOMATIC, FEE_APPL_DATA) CountPtr
);
/* #Violation: Fee_h_REF_1 */
#define FEE_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Fee_MemMap.h"
#endif /* FEE_H_ */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

