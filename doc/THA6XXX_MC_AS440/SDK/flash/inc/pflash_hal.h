/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    pflash_hal.h
 * Author:      00393
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of interfaces.
 *********************************************************************************************************************/
/*
 *#Violation Summary
 *
 *#pflash_hal_h_REF_1:MISRAC2012-Rule-2.5;
 * Justification: The macros are reserved for upper layers
 *
 *#pflash_hal_h_REF_2:MISRAC2012-Rule-2.3;
 * Justification: The members of the type are used in configuration-generated code.
 *
 *#pflash_hal_h_REF_3:MISRAC2012-Dir-4.8;
 * Justification: Apply such struct/union definitons to simplify the code structure and reduce the code
 *                complexity.
 * 
 * #pflash_hal_h_REF_4:DCL12-C;
 * Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity;
 * 
 * #pflash_hal_h_REF_5:MISRAC2012-Rule-20.1;
 * Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.

 */

#ifndef PFLASH_HAL_H_
#define PFLASH_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "pflash_std.h"
#include "tha6_cfg.h"
#if (INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */

/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* List of the PFlash return status. */
typedef enum
{
    PFLASH_RESULTSTATUS_OK = 0, /* The return value is successful */
    PFLASH_RESULTSTATUS_FAILED, /* The return value is failed */
    PFLASH_RESULTSTATUS_TIMEOUT,
    PFLASH_RESULTSTATUS_PARAM_ERR, /* The input parameters have error */
    PFLASH_RESULTSTATUS_BUSY, /* The Async interface get status */
} Pflash_ResultStatus;
/* List of type of flash erase */
typedef enum
{
    PFLASH_ERASETYPE_SECTOR = 0U, /* The erase flash by sector */
    PFLASH_ERASETYPE_BLOCK = 3U,  /* The erase flash by block */
} Pflash_EraseType;
/* list of the mask operate */
/* #Violation: pflash_hal_h_REF_2 */
typedef enum
{
    PFLASH_INTOP_ENABLE = 0U, /* enable */
    PFLASH_INTOP_DISABLE,     /* disable */
} Pflash_IntOp;

typedef enum
{
    PFLASH_CDBUF_UPDATE_DATA = 0U, /* common data buffer update data */
    PFLASH_CDBUF_UPDATE_CODE,      /* common data buffer update code */
    PFLASH_CDBUF_UPDATE_ALL,       /* common data buffer update data and code */
} Pflash_CommonDataBufferMode;
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* ^FLASH_PF_MSKINT^ PF_MSKINT register mask value */
/* #Violation: pflash_hal_h_REF_1 */
#define FLASH_INT_ERASE (0x3U) /* flash erase interrupt */
/* #Violation: pflash_hal_h_REF_1 */
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
/* Pflash buffer configuration */

typedef struct
{
    boolean prefetchBufEn;                         /* prefetch buffer enabled or disable, for THA6104 and THA6412 */
    boolean commonDataBufEn;                       /* common data buffer enabled or disable, only for THA6412 */
    Pflash_CommonDataBufferMode CommonDataBufMode; /* common data buffer mode, only for THA6412 */
/* #Violation: pflash_hal_h_REF_2 */
} FLASH_PflashBufCfg;

/* #Violation: pflash_hal_h_REF_1 */
#define FLS_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: pflash_hal_h_REF_5 */
#include "Fls_MemMap.h"
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:             Flash_Hal_InitPFlash
 * Description:          Initialize PFlash module,include initialize clock cycle
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                None
 * Inout:                None
 * Output:               None
 * Return:               Pflash_ResultStatus: The result status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern Pflash_ResultStatus Flash_Hal_InitPFlash(void);

/**********************************************************************************************************************
 * Function:             Flash_Hal_PFlashSwitchFreq
 * Description:          Use this function to switch the frequency when Flash switches to a higher operating frequency
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                uClockFreq: The clock frequency the flash is about to switch to
 * Inout:                None
 * Output:               None
 * Return:               Pflash_ResultStatus: The result status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2024/5/27     00393     Create
 *********************************************************************************************************************/
extern Pflash_ResultStatus Flash_Hal_PFlashSwitchFreq(uint32 uClockFreq);

 /**********************************************************************************************************************
 * Function:             Flash_Hal_ErasePFlashSync
 * Description:          Erase PFlash in sector or block.This function is call for the synchronous mode.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant (This function is non-reentrant when operating on the same PFLASH, 
 *                           but reentrant when operating on different PFLASHs.)
 * Input:                uAddress: The address to be erased
 *                       eBlank: The erase type: sector or block.
 * Inout:                None
 * Output:               None
 * Return:               Pflash_ResultStatus: The result status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern Pflash_ResultStatus Flash_Hal_ErasePFlashSync(uint32 uAddress, Pflash_EraseType eErType);

 /**********************************************************************************************************************
 * Function:             Flash_Hal_ErasePFlashAsync
 * Description:          Erase PFlash in sector or block.This function is call for the Async mode.
 * Sync/Async:           Asynchronous
 * Reentrancy:           Non-Reentrant (This function is non-reentrant when operating on the same PFLASH, 
 *                           but reentrant when operating on different PFLASHs.)
 * Input:                uAddress: The address to be erased
 *                       eBlank: The erase type:sector or block.
 * Inout:                None
 * Output:               None
 * Return:               boolean:
 *                          TRUE:  Register read back check correct
 *                          FALSE: Register read back check incorrect
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2025/03/25    01361     Create
 *********************************************************************************************************************/
extern boolean Flash_Hal_ErasePFlashAsync(uint32 uAddress, Pflash_EraseType eErType);

 /**********************************************************************************************************************
 * Function:             Flash_Hal_GetPFlashEraseStatus
 * Description:          Get Erase PFlash in sector or block status.This function is call for the Async mode.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant (This function is non-reentrant when operating on the same PFLASH, 
 *                           but reentrant when operating on different PFLASHs.)
 * Input:                uAddress: The address to be erased
 * Inout:                None
 * Output:               None
 * Return:               Pflash_ResultStatus: The result status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2025/03/25    01361     Create
 *********************************************************************************************************************/
extern Pflash_ResultStatus Flash_Hal_GetPFlashEraseStatus(uint32 uAddress);

/**********************************************************************************************************************
 * Function:             Flash_Hal_ClearPFlashEraseStatus
 * Description:          Clear Erase PFlash in sector or block status.This function is call for the Async mode.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant (This function is non-reentrant when operating on the same PFLASH, 
 *                           but reentrant when operating on different PFLASHs.)
 * Input:                uAddress: The address to be erased
 * Inout:                None
 * Output:               None
 * Return:               None
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2025/03/25    01361     Create
 *********************************************************************************************************************/
extern void Flash_Hal_ClearPFlashEraseStatus(uint32 uAddress);

/**********************************************************************************************************************
 * Function:             Flash_Hal_ProgPFlashSync
 * Description:          Program PFlash in pword and the size of pword for PFlash is 32 Bytes. The input length value
 *                       needs to be a multiple of 32. The maximum data length is 256 bytes.This function is call for
 *                       the synchronous mode.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant (This function is non-reentrant when operating on the same PFLASH, 
 *                           but reentrant when operating on different PFLASHs.)
 * Input:                uAddress: The address to be programmed
 *                       pData: The pointer to the programmed data
 *                       uDataLen: The programmed data length
 * Inout:                None
 * Output:               None
 * Return:               Pflash_ResultStatus: The result status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern Pflash_ResultStatus Flash_Hal_ProgPFlashSync(uint32 uAddress, const uint32 * const pData, uint32 uDataLen);

/**********************************************************************************************************************
 * Function:             Flash_Hal_PFlashProgCheck
 * Description:          PFlash program check.
 * Sync/Async:           Synchronous
 * Reentrancy:           Reentrant
 * Input:                uAddress: The address to be programmed
 *                       pData: The pointer to the programmed data
 *                       uDataLen: The programmed data length
 * Inout:                None
 * Output:               None
 * Return:               Pflash_ResultStatus: The result status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2025/09/20    01361     Create
 *********************************************************************************************************************/
extern Pflash_ResultStatus Flash_Hal_PFlashProgCheck(uint32 uAddress, const uint32 *const pData, uint32 uDataLen);

/**********************************************************************************************************************
 * Function:             Flash_Hal_ProgPFlashAsync
 * Description:          Program PFlash in pword and the size of pword for PFlash is 32 Bytes. The input length value
 *                       needs to be a multiple of 32. The maximum data length is 256 bytes.This function is call for
 *                       the Async mode.
 * Sync/Async:           Asynchronous
 * Reentrancy:           Non-Reentrant (This function is non-reentrant when operating on the same PFLASH, 
 *                           but reentrant when operating on different PFLASHs.)
 * Input:                uAddress: The address to be programmed
 *                       pData: The pointer to the programmed data
 *                       uDataLen: The programmed data length
 * Inout:                None
 * Output:               None
 * Return:               boolean:
 *                          TRUE:  Register read back check correct
 *                          FALSE: Register read back check incorrect
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2025/03/25    01361     Create
 *********************************************************************************************************************/
extern boolean Flash_Hal_ProgPFlashAsync(uint32 uAddress, const uint32 *const pData, uint32 uDataLen);

/**********************************************************************************************************************
 * Function:             Flash_Hal_GetPFlashProgStatus
 * Description:          Get Program PFlash in pword and the size of pword for PFlash is 32 Bytes status. The input length value
 *                       needs to be a multiple of 32. The maximum data length is 256 bytes.This function is call for
 *                       the Async mode.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant (This function is non-reentrant when operating on the same PFLASH, 
 *                           but reentrant when operating on different PFLASHs.)
 * Input:                uAddress: The address to be programmed
 * Inout:                None
 * Output:               None
 * Return:               Pflash_ResultStatus: The result status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2025/03/25    01361     Create
 *********************************************************************************************************************/
extern Pflash_ResultStatus Flash_Hal_GetPFlashProgStatus(uint32 uAddress);

/**********************************************************************************************************************
 * Function:             Flash_Hal_ClearPFlashProgStatus
 * Description:          Clear Program PFlash in pword and the size of pword for PFlash is 32 Bytes status. The input length value
 *                       needs to be a multiple of 32. The maximum data length is 256 bytes.This function is call for
 *                       the Async mode.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant (This function is non-reentrant when operating on the same PFLASH, 
 *                           but reentrant when operating on different PFLASHs.)
 * Input:                uAddress: The address to be programmed
 * Inout:                None
 * Output:               None
 * Return:               None
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2025/03/25    01361     Create
 *********************************************************************************************************************/
extern void Flash_Hal_ClearPFlashProgStatus(uint32 uAddress);

/**********************************************************************************************************************
 * Function:             Flash_Hal_ClearAllPFlashStatus
 * Description:          Clear  PFlash  All Status
 *                       the Async mode.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant (This function is non-reentrant when operating on the same PFLASH, 
 *                           but reentrant when operating on different PFLASHs.)
 * Input:                uAddress: The address to be programmed
 * Inout:                None
 * Output:               None
 * Return:               None
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2025/03/25    01361     Create
 *********************************************************************************************************************/
extern void Flash_Hal_ClearAllPFlashStatus(uint32 uAddress);

/**********************************************************************************************************************
 * Function:             Flash_Hal_GetAllPFlashStatus
 * Description:          Get  PFlash  All Status
 *                       the Async mode.
 * Sync/Async:           Synchronous
 * Reentrancy:           Reentrant
 * Input:                uAddress: The address to be programmed
 * Inout:                None
 * Output:               None
 * Return:               uint32: status result
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2025/04/09    01361     Create
 *********************************************************************************************************************/
extern uint32 Flash_Hal_GetAllPFlashStatus(uint32 uAddress);

/**********************************************************************************************************************
 * Function:             Flash_Hal_GetPFlashEccStatus
 * Description:          Get  PFlash  Ecc Status
 *                       the Async mode.
 * Sync/Async:           Synchronous
 * Reentrancy:           Reentrant
 * Input:                uAddress: The address to be programmed
 * Inout:                None
 * Output:               None
 * Return:               boolean: 
 *                          TRUE: Get ECC error
 *                          FALSE: Not Get ECC error
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2025/04/09    01361     Create
 *********************************************************************************************************************/
extern boolean Flash_Hal_GetPFlashEccStatus(uint32 uAddress);

/**********************************************************************************************************************
 * Function:             Flash_Hal_ClearPFlashEccStatus
 * Description:          Clear  PFlash  Ecc Status
 *                       the Async mode.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                uAddress: The address to be programmed
 * Inout:                None
 * Output:               None
 * Return:               boolean: 
 *                          TRUE: Get ECC error
 *                          FALSE: Not Get ECC error
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2025/04/09    01361     Create
 *********************************************************************************************************************/
extern boolean Flash_Hal_ClearPFlashEccStatus(uint32 uAddress);

/**********************************************************************************************************************
 * Function:             Flash_Hal_ConfigPFlashInt
 * Description:          Configure  PFlash  Interrupt 
 *                       the Async mode.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant (This function is non-reentrant when operating on the same PFLASH, 
 *                           but reentrant when operating on different PFLASHs.)
 * Input:                uAddress: The address to be programmed
 *                       uFlashInt: the interrupt value
 *                       eOp: The enumeration value in PFLASH_INTOP_ENABLE for interrupt enable or disable.
 * Inout:                None
 * Output:               None
 * Return:               boolean:
 *                          TRUE:  Register read back check correct
 *                          FALSE: Register read back check incorrect
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2025/04/09    01361     Create
 *********************************************************************************************************************/
extern boolean Flash_Hal_ConfigPFlashInt(uint32 uAddress, uint32 uFlashInt, Pflash_IntOp eOp);

/**********************************************************************************************************************
 * Function:             Flash_Hal_ConfigAllPFlashInt
 * Description:          Configure  all PFlash  Interrupt 
 *                       the Async mode.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                uAddress: The address to be programmed
 *                       uFlashInt: the interrupt value
 *                       eOp: The enumeration value in PFLASH_INTOP_ENABLE for interrupt enable or disable.
 * Inout:                None
 * Output:               None
 * Return:               boolean:
 *                          TRUE:  Register read back check correct
 *                          FALSE: Register read back check incorrect
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2025/04/09    01361     Create
 *********************************************************************************************************************/
extern boolean Flash_Hal_ConfigAllPFlashInt(uint32 uFlashInt, Pflash_IntOp eOp);

/**********************************************************************************************************************
 * Function:             Flash_Hal_ConfigPFlashEccBusErrorAlarm
 * Description:          Configure  PFlash Ecc bus error alarm 
 *                       the Async mode.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant (This function is non-reentrant when operating on the same PFLASH, 
 *                           but reentrant when operating on different PFLASHs.)
 * Input:                uAddress: The address to be programmed
 *                       eOp: The enumeration value in PFLASH_INTOP_ENABLE for alarm enable or disable.
 * Inout:                None
 * Output:               None
 * Return:               boolean:
 *                          TRUE:  Register read back check correct
 *                          FALSE: Register read back check incorrect
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2025/04/09    01361     Create
 *********************************************************************************************************************/
extern boolean Flash_Hal_ConfigPFlashEccBusErrorAlarm(uint32 uAddress, Pflash_IntOp eOp);

/**********************************************************************************************************************
 * Function:             Flash_Hal_CheckPFlashBlankSync
 * Description:          PFalsh hardware blank check, check whether the PFlash is erased but not programmed.
 *                       The blank check type is pword(32 bytes) or sector.This function is call for the 
 *                       synchronous mode.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant (This function is non-reentrant when operating on the same PFLASH, 
 *                           but reentrant when operating on different PFLASHs.)
 * Input:                uAddress: The address to be erase
 *                       eBlank: The check type:sector or pword. 
 * Inout:                None
 * Output:               None
 * Return:               Pflash_ResultStatus: The result status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern Pflash_ResultStatus Flash_Hal_CheckPFlashBlankSync(uint32 uAddress, Pflash_BlankType eBlank);

/**********************************************************************************************************************
 * Function:             Flash_Hal_PFlashBufferConfig
 * Description:          PFalsh buffer configuration.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                pConfig: The pointer to the configuration
 * Inout:                None
 * Output:               None
 * Return:               Pflash_ResultStatus: The result status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
#if defined(THA6_THA6104) || defined(THA6_THA6412)
extern Pflash_ResultStatus Flash_Hal_PFlashBufferConfig(const FLASH_PflashBufCfg * const pConfig);
#endif

/**********************************************************************************************************************
 * Function:             Flash_Hal_CheckPFlashBusy
 * Description:          Check PFLASH busy state.
 * Sync/Async:           Synchronous
 * Reentrancy:           Reentrant
 * Input:                uAddress: The address to be check
 * Inout:                None
 * Output:               None
 * Return:               boolean: 
 *                          TRUE: PFlash is busy
 *                          FALSE: PFlash ont busy
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern boolean Flash_Hal_CheckPFlashBusy(uint32 uAddress);

/* #Violation: pflash_hal_h_REF_1 */
#define FLS_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: pflash_hal_h_REF_5 */
#include "Fls_MemMap.h"


#endif /* PFlash_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
