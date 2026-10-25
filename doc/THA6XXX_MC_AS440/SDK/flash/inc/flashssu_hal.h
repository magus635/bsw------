/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    flashssu_hal.h
 * Author:      00393
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of interfaces.
 *********************************************************************************************************************/
/*
 *#Violation Summary
 *
 *#flashssu_hal_h_REF_1:MISRAC2012-Rule-2.5;
 * Justification: The macros are reserved for upper layers.
 * 
 * #flashssu_hal_h_REF_2:MISRAC2012-Rule-20.1;
 * Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
 *
 */

#ifndef FLASHSSU_HAL_H_
#define FLASHSSU_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "flash_register.h"
#include "tha6_cfg.h"
#if (INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */

/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* List of the SSU return status. */
typedef enum
{
    FLASH_SSUSTATUS_OK = 0U,   /* The return value is successful */
    FLASH_SSUSTATUS_FAILED,    /* The return value is failed */
    FLASH_SSUSTATUS_PARAM_ERR, /* The input parameters have error */
} Flash_SSUStatus;
/* List of SSU write access permission */
typedef enum
{
    FLASH_SSUWRPERM_MTP = 0U,  /* The write access permission is MTP */
    FLASH_SSUWRPERM_OTP,       /* The write access permission is OTP */
    FLASH_SSUWRPERM_RO,        /* The write access permission is None, just read only */
    FLASH_SSUWRPERM_SHADOW_MTP /* The write access permission is MTP,same as MPU_WR_MTP */
} Flash_SSUWrPerm;
/* List of SSU read access permission */
typedef enum
{
    FLASH_SSURDPERM_NO_RD = 0U, /* The read access permission is none readable */
    FLASH_SSURDPERM_RD,         /* The read access permission is readable */
} Flash_SSURdPerm;
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* ^DFLASH_SSU_CONFIG^ DFLASH_SSU_CONFIG register value */
#define DF_SSU_WR_PERM (1U) /* SSU write */
#define DF_SSU_RD_PERM (2U) /* SSU read */
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
/* #Violation: flashssu_hal_h_REF_1 */
#define FLS_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: flashssu_hal_h_REF_2 */
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
 * Function:             Flash_Hal_CheckDFlashSSUPwd
 * Description:          Check the password to modify DFlash main region.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                pPIN: The input password, the length is 32 bytes.
 * Inout:                None
 * Output:               None
 * Return:               Flash_SSUStatus: The result status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern Flash_SSUStatus Flash_Hal_CheckDFlashSSUPwd(const uint8 * const pPIN);

/**********************************************************************************************************************
 * Function:             Flash_Hal_ConfigDFlashSSU
 * Description:          Check the password to modify DFlash main region.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                bPermType: update permission of writing or reading or both, the defined macro 
 *                       "DF_SSU_XX_PERM" can be used.
 *                       RdVal: The value in Flash_SSURdPerm for reading permission value .
 *                       WrVal: The value in Flash_SSUWrPerm for writing permission value .
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
extern boolean Flash_Hal_ConfigDFlashSSU(uint8 bPermType, Flash_SSURdPerm RdVal, Flash_SSUWrPerm WrVal);

/**********************************************************************************************************************
 * Function:             Flash_Hal_CheckPFlashSSUPwd
 * Description:          Check the password to modify PFlash region.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                pPIN: The input password, the length is 32 bytes.
 * Inout:                None
 * Output:               None
 * Return:               Flash_SSUStatus: The result status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
extern Flash_SSUStatus Flash_Hal_CheckPFlashSSUPwd(FLASH_PININPUT_MODULE * const pPFx_PININPUT, const uint8 * const pPIN);

/**********************************************************************************************************************
 * Function:             Flash_Hal_ConfigPFlashSSU
 * Description:          Set the Pflash.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                pPFx_SSU: The pointer to PFlash SSU register
 *                       RdVal: The value in Flash_SSURdPerm for reading permission value.
 *                       WrVal1: The value for writing permission value(block0~block15)
 *                       WrVal2: The value for writing permission value(block16~block24)
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
extern boolean Flash_Hal_ConfigPFlashSSU(FLASH_SSU_MODULE *const pPFx_SSU, Flash_SSURdPerm RdVal, uint32 WrVal1, uint32 WrVal2);

/**********************************************************************************************************************
 * Function:             Flash_Hal_CheckNVRBS_SSUPwd
 * Description:          Check the password to modify DF INFO0 region.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                pPIN: The input password, the length is 32 bytes.
 * Inout:                None
 * Output:               None
 * Return:               Flash_SSUStatus: The result status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2025/04/21    01361     Create
 *********************************************************************************************************************/
extern Flash_SSUStatus Flash_Hal_CheckNVRBS_SSUPwd(const uint8 *const pPIN);


/**********************************************************************************************************************
 * Function:             Flash_Hal_CheckNVRNF_SSUPwd
 * Description:          Check the password to modify DF INFO0 region.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                pPIN: The input password, the length is 32 bytes.
 * Inout:                None
 * Output:               None
 * Return:               Flash_SSUStatus: The result status
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2025/04/21    01361     Create
 *********************************************************************************************************************/
extern Flash_SSUStatus Flash_Hal_CheckNVRNF_SSUPwd(const uint8 *const pPIN);

/**********************************************************************************************************************
 * Function:             Flash_Hal_ConfigCluster0NVRSSU
 * Description:          Configure NVR MPU.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                writeMPU: The value for erase and write permission value(NVRWMPU register)
 *                       readMPU: The value for read permission value(NVRRMPU regsiter)
 * Inout:                None
 * Output:               None
 * Return:               boolean:
 *                          TRUE:  Register read back check correct
 *                          FALSE: Register read back check incorrect
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2025/04/21    01361     Create
 *********************************************************************************************************************/
extern boolean Flash_Hal_ConfigCluster0NVRSSU(uint32 writeMPU, uint32 readMPU);

/* #Violation: flashssu_hal_h_REF_1 */
#define FLS_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: flashssu_hal_h_REF_2 */
#include "Fls_MemMap.h"

#endif /* FLASHSSU_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
