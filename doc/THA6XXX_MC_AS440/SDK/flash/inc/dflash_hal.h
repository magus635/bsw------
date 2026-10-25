/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    dflash_hal.h
 * Author:      00393
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of interfaces.
 *********************************************************************************************************************/
/*
 *#Violation Summary
 *
 *#dflash_hal_h_REF_1:MISRAC2012-Rule-2.5;
 * Justification: The macros are reserved for upper layers.
 * 
 * #dflash_hal_h_REF_2:MISRAC2012-Rule-20.1;
 * Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
 */

#ifndef DFLASH_HAL_H_
#define DFLASH_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "dflash_std.h"
#include "tha6_cfg.h"
#if (INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */

/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/

/* List of type of DFlash error status. */
typedef enum
{
    DFLASH_STATUSID_BLANK = 0U, /* Flash blank check status:non-start,checking,success,error,timeout */
    DFLASH_STATUSID_PROG,       /* Flash programstatus:non-start,programing,success,error,timeout */
    DFLASH_STATUSID_ERASE,      /* Flash erase status:non-start,erasing,success,error,timeout */
} Dflash_StatusID;

/* List of type of Flash */
typedef enum
{
    DFLASH_TYPE_DFLASH = 0U, /* The flash type is Dflash */
    DFLASH_TYPE_OTHER,       /* The flash type error */
} Dflash_Type;
/* List of the DFlash return status. */
typedef enum
{
    DFLASH_RESULTSTATUS_OK = 0U,   /* The return value is successful */
    DFLASH_RESULTSTATUS_FAILED,    /* The return value is failed */
    DFLASH_RESULTSTATUS_TIMEOUT,   /* The return value is timeout */
    DFLASH_RESULTSTATUS_PARAM_ERR, /* The input parameters have error */
} Dflash_ResultStatus;

/* list of the mask operate */
typedef enum
{
    DFLASH_INTOP_ENABLE = 0U, /* enable */
    DFLASH_INTOP_DISABLE,     /* disable */
} Dflash_IntOp;
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* ^FLASH_DFLASH_MSKINT^ FLASH_DFLASH_MSKINT register mask value */
/* #Violation: dflash_hal_h_REF_1 */
#define FLASH_INT_ERASE (0x3U) /* flash erase interrupt */
/* #Violation: dflash_hal_h_REF_1 */
#define FLASH_INT_PROG (0xCU) /* flash program interrupt */

/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
/* #Violation: dflash_hal_h_REF_1 */
#define FLS_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: dflash_hal_h_REF_2 */
#include "Fls_MemMap.h"
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function:             Flash_Hal_InitDFlash
 * Description:          Initialize DFlash module,include initialize clock cycle
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                None
 * Inout:                None
 * Output:               None
 * Return:               Dflash_ResultStatus: The result status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern Dflash_ResultStatus Flash_Hal_InitDFlash(void);

/**********************************************************************************************************************
 * Function:             Flash_Hal_DFlashSwitchFreq
 * Description:          Use this function to switch the frequency when Flash switches to a higher operating frequency
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                uClockFreq: The clock frequency the flash is about to switch to
 * Inout:                None
 * Output:               None
 * Return:               Dflash_ResultStatus: The result status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2024/5/27     00393     Create
 *********************************************************************************************************************/
extern Dflash_ResultStatus Flash_Hal_DFlashSwitchFreq(uint32 uClockFreq);

/**********************************************************************************************************************
 * Function:             Flash_Hal_CheckDFlashBusy
 * Description:          Check if the DFlash is busy
 * Sync/Async:           Synchronous
 * Reentrancy:           Reentrant
 * Input:                None
 * Inout:                None
 * Output:               None
 * Return:               boolean: If DFlash is busy, the status is true
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern boolean Flash_Hal_CheckDFlashBusy(void);

/**********************************************************************************************************************
 * Function:             Flash_Hal_GetDFlashStatus
 * Description:          Get DFlash module operation status(program, erase or blank check).
 * Sync/Async:           Synchronous
 * Reentrancy:           Reentrant
 * Input:                eStatusID: The enumeration value in Dflash_StatusID for the status type ID.
 * Inout:                None
 * Output:               None
 * Return:               Dflash_ResultStatus: The result status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern Dflash_ResultStatus Flash_Hal_GetDFlashStatus(Dflash_StatusID eStatusID);

/**********************************************************************************************************************
 * Function:             Flash_Hal_ClearDFlashStatus
 * Description:          Clear DFlash module operation status(program, erase or blank check).
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                eStatusID: The enumeration value in Dflash_StatusID for the status type ID.
 * Inout:                None
 * Output:               None
 * Return:               None
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern void Flash_Hal_ClearDFlashStatus(Dflash_StatusID eStatusID);

/**********************************************************************************************************************
 * Function:             Flash_Hal_GetAllDFlashStatus
 * Description:          Get DFlash module all error statuses.
 * Sync/Async:           Synchronous
 * Reentrancy:           Reentrant
 * Input:                None
 * Inout:                None
 * Output:               None
 * Return:               uint32: The status value.
 * Others:               Call the function to get current all errors.
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern uint32 Flash_Hal_GetAllDFlashStatus(void);

/**********************************************************************************************************************
 * Function:             Flash_Hal_ClearAllDFlashStatus
 * Description:          Clear DFlash module all error statuses.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                None
 * Inout:                None
 * Output:               None
 * Return:               None
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern void Flash_Hal_ClearAllDFlashStatus(void);

/**********************************************************************************************************************
 * Function:             Flash_Hal_EraseDFlash
 * Description:          Erase DFlash in sector and the size of sector for DFlash is 8KB.
 *                       The input address parameter also requires alignment to 8K.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                uAddress: The address to be erased
 * Inout:                None
 * Output:               None
 * Return:               Dflash_ResultStatus: The result status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern Dflash_ResultStatus Flash_Hal_EraseDFlash(uint32 uAddress);

/**********************************************************************************************************************
 * Function:             Flash_Hal_ProgDFlash
 * Description:          Program DFlash in pword and the size of pword for DFlash is 16 Bytes. The input length value
 *                       needs to be a multiple of 16. The maximum data length is 128 bytes.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                uAddress: The address to be programmed
 *                       pData: The pointer to the programmed data
 *                       uDataLen: The programmed data length
 * Inout:                None
 * Output:               None
 * Return:               Dflash_ResultStatus: Programe status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern Dflash_ResultStatus Flash_Hal_ProgDFlash(uint32 uAddress, const uint8 * const pData, uint32 uDataLen);

/**********************************************************************************************************************
 * Function:             Flash_Hal_DFlashProgCheck
 * Description:          DFlash Program check.
 * Sync/Async:           Synchronous
 * Reentrancy:           Reentrant
 * Input:                uAddress: The address to be programmed
 *                       pData: The pointer to the programmed data
 *                       uDataLen: The programmed data length
 * Inout:                None
 * Output:               None
 * Return:               Dflash_ResultStatus: Programe status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2025/09/20    01361     Create
 *********************************************************************************************************************/
extern Dflash_ResultStatus Flash_Hal_DFlashProgCheck(uint32 uAddress, const uint8 *const pData, uint32 uDataLen);

/**********************************************************************************************************************
 * Function:             Flash_Hal_CheckDFlashBlankSync
 * Description:          DFalsh hardware blank check, check whether the DFlash is erased but not programmed.
 *                       The blank check type is pword(16 bytes).This function is call for the synchronous mode.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                uAddress: The address to be blank check
 *                       uLen: The input length value needs to be a multiple of 16. 
 * Inout:                None
 * Output:               None
 * Return:               Dflash_ResultStatus: The result status
 * Others: None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern Dflash_ResultStatus Flash_Hal_CheckDFlashBlankSync(uint32 uAddress, uint32 uLen);

/**********************************************************************************************************************
 * Function:             Flash_Hal_CheckDFlashSectorBlankSync
 * Description:          DFalsh hardware blank check, check whether the DFlash is erased but not programmed.
 *                       The blank check type is sector.This function is call for the synchronous mode.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                uAddress: The address to be blank check
 * Inout:                None
 * Output:               None
 * Return:               Dflash_ResultStatus: The result status
 * Others: None
 * History:
 * Date          Author    Modified
 * 2025/09/21    01361     Create
 *********************************************************************************************************************/
extern Dflash_ResultStatus Flash_Hal_CheckDFlashSectorBlankSync(uint32 uAddress);

/**********************************************************************************************************************
 * Function:             Flash_Hal_ConfigDFlashInt
 * Description:          Set the mask value for interrupt.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                uFlashInt: The interrupt value
 *                       eOp: The enumeration value in DFLASH_INTOP_ENABLE for interrupt enable or disable. 
 * Inout:                None
 * Output:               None
 * Return:               boolean:
 *                          TRUE:  Register read back check correct
 *                          FALSE: Register read back check incorrect
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern boolean Flash_Hal_ConfigDFlashInt(uint32 uFlashInt, Dflash_IntOp eOp);

/**********************************************************************************************************************
 * Function:             Flash_Hal_ConfigDFlashEccBusErrorAlarm
 * Description:          Set the mask value for Ecc bus error alarm.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                eOp: The enumeration value in DFLASH_INTOP_ENABLE for interrupt enable or disable. 
 * Inout:                None
 * Output:               None
 * Return:               boolean:
 *                          TRUE:  Register read back check correct
 *                          FALSE: Register read back check incorrect
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern boolean Flash_Hal_ConfigDFlashEccBusErrorAlarm(Dflash_IntOp eOp);

/**********************************************************************************************************************
 * Function:             Flash_Hal_GetDFlashEccStatus
 * Description:          Get the Ecc status.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                None
 * Inout:                None
 * Output:               None
 * Return:               boolean: True or False
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern boolean Flash_Hal_GetDFlashEccStatus(void);

/**********************************************************************************************************************
 * Function:             Flash_Hal_ClearDFlashEccStatus
 * Description:          Clear the Ecc status.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                None
 * Inout:                None
 * Output:               None
 * Return:               boolean:
 *                          TRUE:  Register read back check correct
 *                          FALSE: Register read back check incorrect
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern boolean Flash_Hal_ClearDFlashEccStatus(void);

/* #Violation: dflash_hal_h_REF_1 */
#define FLS_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: dflash_hal_h_REF_2 */
#include "Fls_MemMap.h"

#endif /* DFLASH_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
