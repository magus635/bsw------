/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Fls.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DFLASH
*
*   brief                 : SchM file for Fls Driver.
*                           This file contains sample code only. It is not part of the
*                           production code deliverables.
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

#ifndef SCHM_FLS_H_
#define SCHM_FLS_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

#include "Std_Types.h"

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
extern void SchM_Enter_Fls_EraseProtection(void);
extern void SchM_Exit_Fls_EraseProtection(void);
extern void SchM_Enter_Fls_WriteProtection(void);
extern void SchM_Exit_Fls_WriteProtection(void);
extern void SchM_Enter_Fls_CancelProtection(void);
extern void SchM_Exit_Fls_CancelProtection(void);
extern void SchM_Enter_Fls_Erase(void);
extern void SchM_Exit_Fls_Erase(void);
extern void SchM_Enter_Fls_Write(void);
extern void SchM_Exit_Fls_Write(void);
extern void SchM_Enter_Fls_Read(void);
extern void SchM_Exit_Fls_Read(void);
extern void SchM_Enter_Fls_Compare(void);
extern void SchM_Exit_Fls_Compare(void);
extern void SchM_Enter_Fls_BlankCheck(void);
extern void SchM_Exit_Fls_BlankCheck(void);
extern void SchM_Enter_Fls_ReadWordsSync(void);
extern void SchM_Exit_Fls_ReadWordsSync(void);
extern void SchM_Enter_Fls_CompareWordsSync(void);
extern void SchM_Exit_Fls_CompareWordsSync(void);
extern void SchM_Enter_Fls_BlankCheckSync(void);
extern void SchM_Exit_Fls_BlankCheckSync(void);
#endif /* SCHM_FLS_H_ */

