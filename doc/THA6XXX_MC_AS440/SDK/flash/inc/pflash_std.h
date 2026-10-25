/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    flash_std.h
 * Author:      00393
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of interfaces.
 *********************************************************************************************************************/
/*
 *#Violation Summary
 *
 *#pflash_std_h_REF_1:MISRAC2012-Rule-2.5;
 * Justification: The macros are reserved for upper layers.
 *
 *#pflash_std_h_REF_2:MISRAC2012-Rule-2.3;
 * Justification: The members of the type are used in configuration-generated code.
 *
 *#pflash_std_h_REF_3:MISRAC2012-Dir-4.8;
 * Justification: Apply such struct/union definitons to simplify the code structure and reduce the code.
 *                complexity.
 * 
 * #pflash_std_h_REF_4:DCL12-C;
 * Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
 * 
 * #pflash_std_h_REF_5:MISRAC2012-Rule-20.1;
 * Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.

 */

#ifndef FLASH_STD_H_
#define FLASH_STD_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "flash_register.h"
#if (INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */

/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* List of the Flash return status. */
typedef enum
{
    PFLASH_STDSTATUS_OK = 0U,   /* The return value is successful */
    PFLASH_STDSTATUS_PARAM_ERR, /* The input paramter error */
} Pflash_StdStatus;
/* List of type of Flash operation */
typedef enum
{
    PFLASH_OPERATETYPE_PROGARM = 0U, /* Flash program */
    PFLASH_OPERATETYPE_ERASE,        /* Flash erase */
    PFLASH_OPERATETYPE_BLANK_CHECK,  /* Flash blank check */
/* #Violation: pflash_std_h_REF_2 */
} Pflash_OperateType;

/* List of type of flash blank check */
typedef enum
{
    PFLASH_BLANKTYPE_SECTOR = 0U, /* Flash blank check by sector */
    PFLASH_BLANKTYPE_PWORD,       /* Flash blank check by pword */
} Pflash_BlankType;

/* List of the erase clock diviision from system clock */
typedef enum
{
    PFLASH_CLKDIV_1 = 0U, /* The ratio division is 1:1 */
    PFLASH_CLKDIV_2,      /* The ratio division is 1:2 */
    PFLASH_CLKDIV_4,      /* the ratio division is 1:4 */
    PFLASH_CLKDIV_8,      /* the ratio division is 1:8 */
    PFLASH_CLKDIV_16,     /* the ratio division is 1:16 */
    PFLASH_CLKDIV_32,     /* the ratio division is 1:32 */
    PFLASH_CLKDIV_MAX     /* the max ratio divesion */
/* #Violation: pflash_std_h_REF_2 */
} Pflash_ClkDiv;

/* List of status of Flash operation: program, erase or blank check */
typedef enum
{
    PFLASH_OPERATIONSTATUS_COMPLETED = 0U, /* The status of PFlash operation complete */
    PFLASH_OPERATIONSTATUS_ERROR,          /* The status of PFlash operation has error */
    PFLASH_OPERATIONSTATUS_TIMEOUT,        /* The status of PFlash operation is timeout */
    PFLASH_OPERATIONSTATUS_BUSY,          /* The status of PFlash operation is busy */
    PFLASH_OPERATIONSTATUS_NOACTION,       /* The status of PFlash operation is no action */
} Pflash_OperationStatus;

/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/

/************************************** Status Register Start************************/
/* ^FLASH_PF_STS_MASK^ FLASH_PF_STS register mask value */
#define PF_STS_ERSF_MASK (0x1U)   /* PFLASH Erase finish mask */
#define PF_STS_PROGF_MASK (0x4U)  /* PFLASH Program finish mask */
#define PF_STS_BCF_MASK (0x10U)   /* PFLASH blank check finish mask */
#define PF_STS_ECSTS_MASK (0x20U) /* PFLASH blank check empty or non-empty mask */
/* #Violation: pflash_std_h_REF_1 */
#define PF_STS_CF_MASK (0x400U)              /* PFLASH Cancel operation mask */
#define PF_STS_POVT_MASK (0x100000U)         /* PFLASH program timeout */
#define PF_STS_ERASE_MASK (0x1000000U)       /* PFLASH erase check mask */
#define PF_STS_PROG_MASK (0x2000000U)        /* PFLASH program mask */
#define PF_STS_BLANK_CHECK_MASK (0x4000000U) /* PFLASH empty/blank check mask */
#define PF_STS_ALL_MASK (0x15053FU)

/* ^FLASH_PF_BUF_CFG_MASK^ FLASH_PF_BUF_CFG register mask value */
/* #Violation: pflash_std_h_REF_1 */
#define PF_BUFCFG_PBEN_MASK (0x3U) /* PFLASH Code Buffer mask */
/* #Violation: pflash_std_h_REF_1 */
#define PF_BUFCFG_CDBEN_MASK (0xCU) /* PFLASH Data Buffer mask */
/* #Violation: pflash_std_h_REF_1 */
#define PF_BUFCFG_CDBMODE_OFFSET (0x4U) /* PFLASH Program finish mask */

/************************************** Status Register End************************/

/************************************** PF Control Register Start************************/
/* ^FLASH_PFCON_MASK^ FLASH_PFCON register mask value */
#define PFCON_RDT_MASK (0xFU)          /* Define the mask for the PFCON_RDT */
#define PFCON_STO0_MASK (0xFF00U)      /* Define the mask for the PFCON_STO0 */
#define PFCON_STO1_MASK (0x1F0000U)    /* Define the mask for the PFCON_STO1 */
#define PFCON_CLKDIV_MASK (0x7000000U) /* Define the mask for the PFCON_CLKDIV */

/* ^FLASH_PF_BUFCFG^ PF_BUFCFG register mask value */
/* #Violation: pflash_std_h_REF_1 */
#define FLASH_PREFETCH_BUF_ENABLE (0x3U) /* flash prefetch buffer enable */
/* #Violation: pflash_std_h_REF_1 */
#define FLASH_COMMON_DATA_BUFFER_ENABLE (0xCU) /* flash common data buffer enable */

/* ^FLASH_PF_SASTS_MASK^ FLASH_PF_SASTS0 register mask value */
#define PF_SASTS0_UCRE_MASK (0x1000U) /* occur unmodified error mask */
/* ^FLASH_PF_SAMSKBE0^ PF_SAMSKBE0 register mask value */
#define PF_SAMSKBE0_MUCRE_MASK (0x3000U)
/* ^FLASH_PF_CTR1_MASK^ FLASH_PF_CTR1 register mask value */
/* #Violation: pflash_std_h_REF_1 */
#define PF_CTR1_BUFEN_MASK (0x3U) /* Define the mask for the PF_CTR1_BUFEN */

/* ^FLASH_PF_CTR3_MASK^ FLASH_PF_CTR3 register mask value */
#if defined(THA6_THA6206) || defined(THA6_THA6412) || defined(THA6_THA6206D)
#define PF_CTR3_EADDR_MASK (0xFFFFC000U) /* Define the mask for the PF_CTR3_EADDR  */
#endif

#if defined(THA6_THA6104)
#define PF_CTR3_EADDR_MASK (0xFFFFFE00U) /* Define the mask for the PF_CTR3_EADDR  */
#endif

/* ^FLASH_PF_CTR4_MASK^ FLASH_PF_CTR4 register mask value */
#define PF_CTR4_ESTART_MASK (0x3U) /* Define the mask for the PF_CTR4_ESTART  */
/* #Violation: pflash_std_h_REF_1 */
#define PF_CTR4_ETYP_MASK (0x70U) /* Define the mask for the PF_CTR4_ETYP */

/* ^FLASH_PF_CTR5_MASK^ FLASH_DF_CTR5 register mask value */
#define PF_CTR5_ECEN_MASK (0x3U)  /* Define the mask for the PF_CTR5_ECEN */
#define PF_CTR5_ECLEN_MASK (0x4U) /* Define the mask for the PF_CTR5_ECLEN */
#if defined(THA6_THA6206) || defined(THA6_THA6412) || defined(THA6_THA6206D)
#define PF_CTR5_ECADDR_MASK (0xFFFFFFE0U) /* Define the mask for the PF_CTR5_ECADDR   */
#endif

#if defined(THA6_THA6104)
#define PF_CTR5_ECADDR_MASK (0xFFFFFFC0U) /* Define the mask for the PF_CTR5_ECADDR   */
#endif
/* ^FLASH_PF_CTR7_MASK^ FLASH_PF_CTR7 register mask value */
/* #Violation: pflash_std_h_REF_1 */
#define PF_CTR7_PBL_MASK (0x7U) /* Define the mask for the PF_CTR7_PBL */
/* #Violation: pflash_std_h_REF_1 */
#define PF_CTR7_PTYP_MASK (0x300U) /* Define the mask for the PF_CTR7_PTYP */
/* #Violation: pflash_std_h_REF_1 */
#define PF_CTR7_PTYP_SMP1 (0x0U) /* Define the value for the PF_CTR7_PTYP_SMP1 */
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* #Violation: pflash_std_h_REF_1 */
#define PF_CTR7_PTYP_SMP2 (0x100U)   /* Define the value for the PF_CTR7_PTYP_SMP2 */
#define PF_CTR7_PEXTRA_MASK (0x400U) /* Define the mask for the PF_CTR7_PEXTRA */
#endif

/* ^FLASH_PF_CTR8_MASK^ FLASH_PF_CTR8 register mask value */
/* #Violation: pflash_std_h_REF_1 */
#define PF_CTR8_OVTIME_MASK (0xFFFU) /* Define the mask for the FLASH_PF_CTR8_OVTIME */
/* #Violation: pflash_std_h_REF_1 */
#define PF_CTR8_OVTE_MASK (0xC0000000U) /* Define the mask for the FLASH_PF_CTR8_OVTE */

/* ^FLASH_PF_ECCCTR_MASK^ FLASH_PF_ECCCTR register mask value */
/* #Violation: pflash_std_h_REF_1 */
#define PF_ECCCTR_ECCEEN_MASK (0x3U) /* Define the mask for the PF_ECCCTR_ECCEEN */
/* #Violation: pflash_std_h_REF_1 */
#define PF_ECCCTR_ECCDEN_MASK (0xCU) /* Define the mask for the PF_ECCCTR_ECCDEN  */

/************************************** DF Control Register End************************/

/************************************** MPU Register Start************************/

/************************************** MPU Register End************************/

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
/* Pflash timing configuration */
typedef struct
{
    uint8 bRDT;     /* read timing */
    uint8 bSTO0;    /* sto0 */
    uint8 bSTO1;    /* sto1 */
    uint8 bCLKDIV;  /* clock divider */
} Pflash_ClockCfg;

/* #Violation: pflash_std_h_REF_1 */
#define FLS_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: pflash_std_h_REF_5 */
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
 * Function:             Flash_Std_InitPflash
 * Description:          Initialize PFlash module,include initialize clock cycle
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                pCommonCtr: Pflash common control register
 *                       pCfg: Pflash clock configuration
 * Inout:                None
 * Output:               None
 * Return:               Pflash_StdStatus: The result status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern Pflash_StdStatus Flash_Std_InitPflash(FLASH_COMMON_CTR_MODULE * const pCommonCtr, const Pflash_ClockCfg * const pCfg);

/**********************************************************************************************************************
 * Function:             Flash_Std_CheckPFlashBusy
 * Description:          Check if the PFlash is busy
 * Sync/Async:           Synchronous
 * Reentrancy:           Reentrant
 * Input:                pPFx_STS: The pointer to PFlash status register
 * Inout:                None
 * Output:               None
 * Return:               boolean: status: If PFlash is busy, the status is true
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern boolean Flash_Std_CheckPFlashBusy(const FLASH_STS_MODULE * const pPFx_STS);

/**********************************************************************************************************************
 * Function:             Flash_Std_GetPFlashProgStatus
 * Description:          Get PFlash module program status
 * Sync/Async:           Synchronous
 * Reentrancy:           Reentrant
 * Input:                pPFx_STS: The pointer to PFlash status register
 * Inout:                None
 * Output:               None
 * Return:               Pflash_OperationStatus: The result status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern Pflash_OperationStatus Flash_Std_GetPFlashProgStatus(const FLASH_STS_MODULE * const pPFx_STS);

/**********************************************************************************************************************
 * Function:             Flash_Std_GetPFlashEraseStatus
 * Description:          Get PFlash module erase status
 * Sync/Async:           Synchronous
 * Reentrancy:           Reentrant
 * Input:                pPFx_STS: The pointer to PFlash status register
 * Inout:                None
 * Output:               None
 * Return:               Pflash_OperationStatus: The result status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern Pflash_OperationStatus Flash_Std_GetPFlashEraseStatus(const FLASH_STS_MODULE * const pPFx_STS);

/**********************************************************************************************************************
 * Function:             Flash_Std_GetPFlashBlankStatus
 * Description:          Get PFlash module blank check status
 * Sync/Async:           Synchronous
 * Reentrancy:           Reentrant
 * Input:                pPFx_STS: The pointer to PFlash status register
 * Inout:                None
 * Output:               None
 * Return:               Pflash_OperationStatus: The result status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern Pflash_OperationStatus Flash_Std_GetPFlashBlankStatus(const FLASH_STS_MODULE * const pPFx_STS);

/**********************************************************************************************************************
 * Function:             Flash_Std_ClearPFlashProgStatus
 * Description:          Clear PFlash module program status.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                pPFx_STS: The pointer to PFlash status register
 * Inout:                None
 * Output:               None
 * Return:               None
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern void Flash_Std_ClearPFlashProgStatus(FLASH_STS_MODULE * const pPFx_STS);

/**********************************************************************************************************************
 * Function:             Flash_Std_ClearPFlashEraseStatus
 * Description:          Clear PFlash module erase status.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                pPFx_STS: The pointer to PFlash status register
 * Inout:                None
 * Output:               None
 * Return:               None
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern void Flash_Std_ClearPFlashEraseStatus(FLASH_STS_MODULE * const pPFx_STS);

/**********************************************************************************************************************
 * Function:             Flash_Std_ClearPFlashBlankStatus
 * Description:          Clear PFlash module blank status.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                pPFx_STS: The pointer to PFlash status register
 * Inout:                None
 * Output:               None
 * Return:               None
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern void Flash_Std_ClearPFlashBlankStatus(FLASH_STS_MODULE * const pPFx_STS);

/**********************************************************************************************************************
 * Function:             Flash_Std_ErasePFlash
 * Description:          Erase PFlash in sector and the size of sector for PFlash is 16KB.
 *                       The input address parameter also requires alignment to 16K.
 * Sync/Async:           Asynchronous
 * Reentrancy:           Non-Reentrant
 * Input:                pPFx_CTR: The pointer to PFlash ctrl register
 *                       uAddress: The address to be erased
 *                       bEraseType: The erase type
 * Inout:                None
 * Output:               None
 * Return:               boolean:
 *                          TRUE:  Register read back check correct
 *                          FALSE: Register read back check incorrect
 * Others:               Before erasing PFlash, master should get the lock.
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern boolean Flash_Std_ErasePFlash(FLASH_CTR_MODULE *const pPFx_CTR, uint32 uAddress, uint8 bEraseType);


/**********************************************************************************************************************
 * Function:             Flash_Std_ProgPFlash
 * Description:          Program PFlash in pword and the size of pword for PFlash is 32 Bytes. The input length value
 *                       needs to be a multiple of 32. The maximum data length is 256 bytes.
 * Sync/Async:           Asynchronous
 * Reentrancy:           Non-Reentrant
 * Input:                pPFx_CTR: The pointer to PFlash ctrl register
 *                       uAddress: The address to be programmed
 *                       pData: The pointer to the programmed data
 *                       uDataLen: The programmed data length
 * Inout:                None
 * Output:               None
 * Return:               boolean:
 *                          TRUE:  Register read back check correct
 *                          FALSE: Register read back check incorrect
 * Others:               Before programing PFlash, master should get the lock.
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern boolean Flash_Std_ProgPFlash(FLASH_CTR_MODULE *const pPFx_CTR, uint32 uAddress, const uint32 *const pData, uint32 uDataLen);

/**********************************************************************************************************************
 * Function:             Flash_Std_CheckPFlashBlank
 * Description:          PFalsh hardware blank check, check whether the PFlash is erased but not programmed.
 *                       The blank check type is pword(32 bytes) or sector.
 * Sync/Async:           Asynchronous
 * Reentrancy:           Non-Reentrant
 * Input:                pPFx_CTR: The pointer to PFlash ctrl register
 *                       uAddress: The address to be blank check
 *                       eBlank: The enumeration value in Blank_Type for the check type:sector or pword
 * Inout:                None
 * Output:               None
 * Return:               boolean:
 *                          TRUE:  Register read back check correct
 *                          FALSE: Register read back check incorrect
 * Others: None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern boolean Flash_Std_CheckPFlashBlank(FLASH_CTR_MODULE *const pPFx_CTR, uint32 uAddress, Pflash_BlankType eBlank);

/**********************************************************************************************************************
 * Function:             Flash_Std_GetAllPFlashStatus
 * Description:          Get PFlash module all error statuses.
 * Sync/Async:           Synchronous
 * Reentrancy:           Reentrant
 * Input:                pPFx_STS: The pointer to PFlash status registere
 * Inout:                None
 * Output:               None
 * Return:               uint32: PFlash status
 * Others:               Call the function to get current all errors.
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern uint32 Flash_Std_GetAllPFlashStatus(const FLASH_STS_MODULE * const pPFx_STS);

/**********************************************************************************************************************
 * Function:             Flash_Std_ClearAllPFlashStatus
 * Description:          Clear PFlash module all error statuses.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                pPFx_STS: The pointer to PFlash status register
 * Inout:                None
 * Output:               None
 * Return:               None
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern void Flash_Std_ClearAllPFlashStatus(FLASH_STS_MODULE * const pPFx_STS);

/**********************************************************************************************************************
 * Function:             Flash_Std_GetPFlashEccStatus
 * Description:          Get PFlash module ecc error statuses.
 * Sync/Async:           Synchronous
 * Reentrancy:           Reentrant
 * Input:                pPFx_STS: The pointer to PFlash status register
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
extern boolean Flash_Std_GetPFlashEccStatus(const FLASH_STS_MODULE *const pPFx_STS);

/**********************************************************************************************************************
 * Function:             Flash_Std_ClearPFlashEccStatus
 * Description:          Clear PFlash module ecc error statuses.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                pPFx_STS: The pointer to PFlash status register
 * Inout:                None
 * Output:               None
 * Return:               None
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2025/04/09    01361     Create
 *********************************************************************************************************************/
extern void Flash_Std_ClearPFlashEccStatus(FLASH_STS_MODULE *const pPFx_STS);

/**********************************************************************************************************************
 * Function:             Flash_Std_EnablePFlashInt
 * Description:          Enable PFLASH Interrupt.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                pPFx_MSK: The pointer to PFlash maskint register
 *                       uFlashInt: register value
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
extern boolean Flash_Std_EnablePFlashInt(FLASH_MSK_MODULE *const pPFx_MSK , uint32 uFlashInt);

/**********************************************************************************************************************
 * Function:             Flash_Std_DisablePFlashInt
 * Description:          Disable PFLASH Interrupt.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                pPFx_MSK: The pointer to PFlash maskint register
 *                       uFlashInt: register value
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
extern boolean Flash_Std_DisablePFlashInt(FLASH_MSK_MODULE *const pPFx_MSK , uint32 uFlashInt);

/**********************************************************************************************************************
 * Function:             Flash_Std_EnablePFlashEccBusErrorAlarm
 * Description:          Enable PFLASH Ecc Bus Error Alarm.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                pPFx_MSK: The pointer to PFlash maskint register
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
extern boolean Flash_Std_EnablePFlashEccBusErrorAlarm(FLASH_MSK_MODULE *const pPFx_MSK);

/**********************************************************************************************************************
 * Function:             Flash_Std_DisablePFlashEccBusErrorAlarm
 * Description:          Disable PFLASH Ecc Bus Error Alarm.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                pPFx_MSK: The pointer to PFlash maskint register
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
extern boolean Flash_Std_DisablePFlashEccBusErrorAlarm(FLASH_MSK_MODULE *const pPFx_MSK);

/**********************************************************************************************************************
 * Function:             Flash_Std_ConfigPFlashBUf
 * Description:          PFlash buffer configuration.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                pBUFCFG: The pointer to PFlash buffer config register
 *                       regVal: The register value to be set
 * Inout:                None
 * Output:               None
 * Return:               boolean:
 *                          TRUE:  Register read back check correct
 *                          FALSE: Register read back check incorrect
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2024/08/30    00393     Create
 *********************************************************************************************************************/
#if defined(THA6_THA6412) || defined(THA6_THA6104)
 extern boolean Flash_Std_ConfigPFlashBuf(FLASH_COMMON_BUFCFG_MODULE *const pBufcfg, uint32 regVal);
#endif

/**********************************************************************************************************************
 * Function:             Flash_Std_GetPFlashCtr
 * Description:          Get PFlash Controler.
 * Sync/Async:           Synchronous
 * Reentrancy:           Reentrant
 * Input:                uAddress: The access address
 * Inout:                None
 * Output:               None
 * Return:               FLASH_CTR_MODULE*: PFlash controler pointer
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2025/04/17    00393     Create
 *********************************************************************************************************************/
extern FLASH_CTR_MODULE* Flash_Std_GetPFlashCtr(uint32 uAddress);


#define PFLASH_REG_CHECK
#if defined(PFLASH_REG_CHECK)
LOCAL_FORCEINLINE boolean PFlash_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
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
LOCAL_FORCEINLINE boolean PFlash_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    (void)state;
    (void)expect;
    (void)value;

    return state;
}
#endif

/* #Violation: pflash_std_h_REF_1 */
#define FLS_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: pflash_std_h_REF_5 */
#include "Fls_MemMap.h"

#endif /* FLASH_STD_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
