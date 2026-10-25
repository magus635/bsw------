/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    dflash_std.h
 * Author:      00393
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of interfaces.
 *********************************************************************************************************************/
/*
 *#Violation Summary
 *
 *#dflash_std_h_REF_1:MISRAC2012-Rule-2.5;
 * Justification: The macros are reserved for upper layers
 *
 *#dflash_std_h_REF_2:MISRAC2012-Rule-2.3;
 * Justification: The members of the type are used in configuration-generated code.
 *
 * #dflash_std_h_REF_3:MISRAC2012-Dir-4.8;
 * Justification: Apply such struct/union definitons to simplify the code structure and reduce the code
 *                complexity.
 * 
 * #dflash_std_h_REF_4:DCL12-C;
 * Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity;
 * 
 * #dflash_std_h_REF_5:MISRAC2012-Rule-20.1;
 * Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.

 */

#ifndef DFLASH_STD_H_
#define DFLASH_STD_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "flash_register.h"
#include "compilertypes.h"
#if (INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */

/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* List of type of flash blank check */
typedef enum
{
    BLANK_TYPE_SECTOR = 0U, /* Flash blank check by sector */
    BLANK_TYPE_PWORD,       /* Flash blank check by pword */
} Blank_Type;

/* List of the erase clock division from system clock */
typedef enum
{
    FLASH_CLKDIV_1 = 0U, /* The ratio division is 1:1 */
    FLASH_CLKDIV_2,      /* The ratio division is 1:2 */
    FLASH_CLKDIV_4,      /* the ratio division is 1:4 */
    FLASH_CLKDIV_8,      /* the ratio division is 1:8 */
    FLASH_CLKDIV_16,     /* the ratio division is 1:16 */
    FLASH_CLKDIV_32,     /* the ratio division is 1:32 */
    FLASH_CLKDIV_MAX     /* the ratio division max */
/* #Violation: dflash_std_h_REF_2 */
} Dflash_ClkDiv;

/* List of the Flash return status. */
typedef enum
{
    DFLASH_STDSTATUS_OK = 0U,   /* The return value is successful */
    DFLASH_STDSTATUS_PARAM_ERR, /* The input paramter error */
} Dflash_StdStatus;

/* List of status of Flash operation: program, erase or blank check */
typedef enum
{
    DFLASH_OPERATIONSTATUS_COMPLETED = 0U, /* The status of DFlash operation complete */
    DFLASH_OPERATIONSTATUS_ERROR,          /* The status of DFlash operation has error */
    DFLASH_OPERATIONSTATUS_TIMEOUT,        /* The status of DFlash operation is timeout */
    DFLASH_OPERATIONSTATUS_BUSY,          /* The status of DFlash operation is busy */
    DFLASH_OPERATIONSTATUS_NOACTION,       /* The status of DFlash operation is no action */
} Dflash_OperationStatus;

/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* ^FLASH_DF0_SAMSKBE0^ DF0_SAMSKBE0 register mask value */
#define SAMSKBE0_MUCRE_MASK (0x3000U)
/************************************** Status Register Start************************/
/* ^FLASH_DFLASH_STS_MASK^ FLASH_DFLASH_STS register mask value */
#define DF_STS_ERSF_MASK (0x1U)   /* DFLASH Erase finish mask */
#define DF_STS_PROGF_MASK (0x4U)  /* DFLASH Program finish mask */
#define DF_STS_BCF_MASK (0x10U)   /* DFLASH blank check finish mask */
#define DF_STS_ECSTS_MASK (0x20U) /* DFLASH blank check empty or non-empty mask */
/* #Violation: dflash_std_h_REF_1 */
#define DF_STS_CF_MASK (0x400U)              /* DFLASH Cancel operation mask */
#define DF_STS_POVT_MASK (0x100000U)         /* DFLASH program timeout */
#define DF_STS_ERASE_MASK (0x1000000U)       /* DFLASH erase check mask */
#define DF_STS_PROG_MASK (0x2000000U)        /* DFLASH program mask */
#define DF_STS_BLANK_CHECK_MASK (0x4000000U) /* DFLASH empty/blank check mask */
#define DF_STS_ALL_MASK (0x15053FU)

/* ^FLASH_DF0_SASTS_MASK^ FLASH_DF0_SASTS register mask value */
#define DF0_SASTS0_UCRE_MASK (0x1000U) /* occur unmodified error mask */

/************************************** Status Register End************************/

/************************************** DF Control Register Start************************/
/* ^FLASH_DFCON_MASK^ FLASH_DFCON register mask value */
#define DFCON_RDT_MASK (0xFU)          /* Define the mask for the DFCON_RDT */
#define DFCON_STO0_MASK (0xFF00U)      /* Define the mask for the DFCON_STO0 */
#define DFCON_STO1_MASK (0x1F0000U)    /* Define the mask for the DFCON_STO1 */
#define DFCON_CLKDIV_MASK (0x7000000U) /* Define the mask for the DFCON_CLKDIV  */

/* ^FLASH_DFLASH_CTR1_MASK^ FLASH_DFLASH_CTR1 register mask value */
#define DF_CTR1_BUFEN_MASK (0x3U) /* Define the mask for the FLASH_DFLASH_CTR1_BUFEN */

/* ^FLASH_DFLASH_CTR3_MASK^ FLASH_DFLASH_CTR3 register mask value */
#if defined(THA6_THA6206) || defined(THA6_THA6412) || defined(THA6_THA6206D)
#define DF_CTR3_EADDR_MASK (0xFFFFE000U) /* Define the mask for the FLASH_DFLASH_CTR3_EADDR */
#endif

#if defined(THA6_THA6104)
#define DF_CTR3_EADDR_MASK (0xFFFFFC00U) /* Define the mask for the FLASH_DFLASH_CTR3_EADDR */
#endif
/* ^FLASH_DFLASH_CTR4_MASK^ DFLASH CTR4 register mask value */
#define DF_CTR4_ESTART_MASK (0x3U) /* Define the mask for the FLASH_DFLASH_CTR4_ESTART  */
/* #Violation: dflash_std_h_REF_1 */
#define DF_CTR4_ETYP_MASK (0x70U) /* Define the mask for the FLASH_DFLASH_CTR4_ETYP */

/* ^FLASH_DFLASH_CTR5_MASK^ DFLASH CTR5 register mask value */
#define DF_CTR5_ECEN_MASK (0x3U)          /* Define the mask for the DF_CTR5_ECEN_MASK */
#define DF_CTR5_ECLEN_MASK (0x4U)         /* Define the mask for the DF_CTR5_ECLEN_MASK */
#define DF_CTR5_ECADDR_MASK (0xFFFFFFF0U) /* Define the mask for the DF_CTR5_ECADDR_MASK */

/* ^FLASH_DFLASH_CTR7_MASK^ DFLASH CTR7 register mask value */
/* #Violation: dflash_std_h_REF_1 */
#define DF_CTR7_PBL_MASK (0x7U) /* Define the mask for the DF_CTR7_PBL_MASK */
/* #Violation: dflash_std_h_REF_1 */
#define DF_CTR7_PTYP_MASK (0x300U) /* Define the mask for the DF_CTR7_PTYP_MASK */
/* #Violation: dflash_std_h_REF_1 */
#define DF_CTR7_PTYP_SMP1 (0x0U) /* Define the value for the DF_CTR7_PTYP_SMP1 */
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* #Violation: dflash_std_h_REF_1 */
#define DF_CTR7_PTYP_SMP2 (0x100U)   /* Define the value for the DF_CTR7_PTYP_SMP2 */
#define DF_CTR7_PEXTRA_MASK (0x400U) /* Define the mask for the FLASH_DFLASH_CTR7_PEXTRA */
#endif

/* ^FLASH_DFLASH_CTR8_MASK^ DFLASH CTR8 register mask value */
/* #Violation: dflash_std_h_REF_1 */
#define DF_CTR8_OVTIME_MASK (0xFFFU)    /* Define the mask for the FLASH_DFLASH_CTR8_OVTIME */
#define DF_CTR8_OVTE_MASK (0xC0000000U) /* Define the mask for the FLASH_DFLASH_CTR8_OVTE */

/* ^NVM_DF0_ECCCTR_MASK^ NVM_DF0_ECCCTR register mask value */
/* #Violation: dflash_std_h_REF_1 */
#define DF0_ECCCTR_ECCEEN_MASK (0x3U) /* Define the mask for the DF0_ECCCTR_ECCEEN */
/* #Violation: dflash_std_h_REF_1 */
#define FLA_ECCCTR_ECCDEN_MASK (0xCU) /* Define the mask for the DF0_ECCCTR_ECCDEN  */

/************************************** DF Control Register End************************/

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
/* Dflash timing configuration */

typedef struct
{
    uint8 bRDT;    /* read timing */
    uint8 bSTO0;   /* sto0 */
    uint8 bSTO1;   /* sto1 */
    uint8 bCLKDIV; /* lock divider */
/* #Violation: dflash_std_h_REF_3 */
/* #Violation: dflash_std_h_REF_4 */
} Dflash_ClockCfg;

/* #Violation: dflash_std_h_REF_1 */
#define FLS_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: dflash_std_h_REF_5 */
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
 * Function:             Flash_Std_InitDflash
 * Description:          Initialize DFlash module,include initialize clock cycle
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                pCfg: Dflash clock configuration
 * Inout:                None
 * Output:               None
 * Return:               Dflash_StdStatus: The result status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern Dflash_StdStatus Flash_Std_InitDflash(const Dflash_ClockCfg * const pCfg);

/**********************************************************************************************************************
 * Function:             Flash_Std_CheckDFlashBusy
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
extern boolean Flash_Std_CheckDFlashBusy(void);

/**********************************************************************************************************************
 * Function:             Flash_Std_GetDFlashProgStatus
 * Description:          Get DFlash module program status
 * Sync/Async:           Synchronous
 * Reentrancy:           Reentrant
 * Input:                None
 * Inout:                None
 * Output:               None
 * Return:               Dflash_OperationStatus: The result status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern Dflash_OperationStatus Flash_Std_GetDFlashProgStatus(void);

/**********************************************************************************************************************
 * Function:             Flash_Std_GetDFlashEraseStatus
 * Description:          Get DFlash module erase status
 * Sync/Async:           Synchronous
 * Reentrancy:           Reentrant
 * Input:                None
 * Inout:                None
 * Output:               None
 * Return:               Dflash_OperationStatus: The result status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern Dflash_OperationStatus Flash_Std_GetDFlashEraseStatus(void);

/**********************************************************************************************************************
 * Function:             Flash_Std_GetDFlashBlankStatus
 * Description:          Get DFlash module blank check status
 * Sync/Async:           Synchronous
 * Reentrancy:           Reentrant
 * Input:                None
 * Inout:                None
 * Output:               None
 * Return:               Dflash_OperationStatus: The result status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern Dflash_OperationStatus Flash_Std_GetDFlashBlankStatus(void);

/**********************************************************************************************************************
 * Function:             Flash_Std_ClearDFlashProgStatus
 * Description:          Clear DFlash module program status.
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
extern void Flash_Std_ClearDFlashProgStatus(void);

/**********************************************************************************************************************
 * Function:             Flash_Std_ClearDFlashEraseStatus
 * Description:          Clear DFlash module erase status.
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
extern void Flash_Std_ClearDFlashEraseStatus(void);

/**********************************************************************************************************************
 * Function:             Flash_Std_ClearDFlashBlankStatus
 * Description:          Clear DFlash module blank status.
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
extern void Flash_Std_ClearDFlashBlankStatus(void);

/**********************************************************************************************************************
 * Function:             Flash_Std_EraseDFlash
 * Description:          Erase DFlash in sector and the size of sector for DFlash is 8KB(THA6206/THA6412) or 1KB(THA6104).
 *                       The input address parameter also requires alignment to 8K or 1K.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                uAddress: The address to be erased
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
extern boolean Flash_Std_EraseDFlash(uint32 uAddress);

/**********************************************************************************************************************
 * Function:             Flash_Std_ProgDFlash
 * Description:          Program DFlash in pword and the size of pword for DFlash is 16 Bytes. The input length value
 *                       needs to be a multiple of 16. The maximum data length is 128 bytes.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
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
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern boolean Flash_Std_ProgDFlash(uint32 uAddress, const uint8 *const pData, uint32 uDataLen);


/**********************************************************************************************************************
 * Function:             Flash_Std_CheckDFlashBlank
 * Description:          DFalsh hardware blank check, check whether the DFlash is erased but not programmed.
 *                       The blank check type is pword(16 bytes) or sector.This function is call for the asynchronous mode.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                uAddress: The address to be blank check
 *                       eBlank: The enumeration value in Blank_Type for the check type:sector or pword
 * Inout:                None
 * Output:               None
 * Return:               boolean:
 *                          TRUE:  Register read back check correct
 *                          FALSE: Register read back check incorrect
 * Others: None
 * History:
 * Date          Author    Modified
 * 2023/08/16    00412     Create
 *********************************************************************************************************************/
extern boolean Flash_Std_CheckDFlashBlank(uint32 uAddress, Blank_Type eBlank);

/**********************************************************************************************************************
 * Function:             Flash_Std_EnableDFlashInt
 * Description:          Set the mask value for interrupt.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                uFlashInt: the interrupt to be enable
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
extern boolean Flash_Std_EnableDFlashInt(uint32 uFlashInt);

/**********************************************************************************************************************
 * Function:             Flash_Std_DisableDFlashInt
 * Description:          Set the mask value for interrupt.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                uFlashInt: The interrupt to be disable
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
extern boolean Flash_Std_DisableDFlashInt(uint32 uFlashInt);

/**********************************************************************************************************************
 * Function:             Flash_Std_EnableDFlashEccBusErrorAlarm
 * Description:          Enable the Ecc bus error.
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
extern boolean Flash_Std_EnableDFlashEccBusErrorAlarm(void);

/**********************************************************************************************************************
 * Function:             Flash_Std_DisableDFlashEccBusErrorAlarm
 * Description:          Disable the Ecc bus error.
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
extern boolean Flash_Std_DisableDFlashEccBusErrorAlarm(void);

/**********************************************************************************************************************
 * Function:             Flash_Std_GetDFlashEccStatus
 * Description:          Get the Ecc status.
 * Sync/Async:           Synchronous
 * Reentrancy:           Reentrant
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
extern boolean Flash_Std_GetDFlashEccStatus(void);

/**********************************************************************************************************************
 * Function:             Flash_Std_ClearDFlashEccStatus
 * Description:          Clear the Ecc status.
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
extern void Flash_Std_ClearDFlashEccStatus(void);

/**********************************************************************************************************************
 * Function:             Flash_Std_GetAllDFlashStatus
 * Description:          Get DFlash module all error statuses.
 * Sync/Async:           Synchronous
 * Reentrancy:           Reentrant
 * Input:                None
 * Inout:                None
 * Output:               None
 * Return:               uint32: All status of the dflash
 * Others:               Call the function to get current all errors.
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern uint32 Flash_Std_GetAllDFlashStatus(void);

/**********************************************************************************************************************
 * Function:             Flash_Std_ClearAllDFlashStatus
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
extern void Flash_Std_ClearAllDFlashStatus(void);

#define DFLASH_REG_CHECK
#if defined(DFLASH_REG_CHECK)
LOCAL_FORCEINLINE boolean DFlash_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    boolean ret;

    ret = state;
    if (expect != value)
    {
        ret &= FALSE;
    }

    return ret;
}
#else
LOCAL_FORCEINLINE boolean DFlash_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    (void)state;
    (void)expect;
    (void)value;

    return state;
}
#endif
/* #Violation: dflash_std_h_REF_1 */
#define FLS_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: dflash_std_h_REF_5 */
#include "Fls_MemMap.h"

#endif /* DFLASH_STD_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
