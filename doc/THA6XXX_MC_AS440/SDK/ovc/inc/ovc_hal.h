/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    ovc_hal.h
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations.
 *********************************************************************************************************************/
/*
 *#Violation Summary
 *
 *#ovc_hal_h_REF_1:MISRAC2012-Rule-2.5;
 * Justification: The macros are reserved for upper layers.
 * 
 * #ovc_hal_h_REF_2:MISRAC2012-Rule-20.1;
 * Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
 */

#ifndef OVC_HAL_H_
#define OVC_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "ovc_register.h"
#include "tha6_cfg.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* Indication of no error */
/* #Violation: ovc_hal_h_REF_1 */
#define OVC_ERROR_FLAG_STATUS_RESET (0U)
/* Indication of mapping error */
/* #Violation: ovc_hal_h_REF_1 */
#define OVC_ERROR_FLAG_STATUS_MAPPING (0x1U)
/* Indication of invalid address error */
/* #Violation: ovc_hal_h_REF_1 */
#define OVC_ERROR_FLAG_STATUS_INVALID_ADDRESS (0x2U)
/* Indication of mapping and invalid address error */
/* #Violation: ovc_hal_h_REF_1 */
#define OVC_ERROR_FLAG_STATUS_MAPPING_AND_INVALID (0x3U)
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* List of the available core id */
typedef enum
{
    OVC_CORE_ID_0 = 0U, /* core 0 */
#if defined(THA6_THA6206) || defined(THA6_THA6412) || defined(THA6_THA6206D)
    OVC_CORE_ID_1,      /* core 1, for CHIP THA6206 and THA6412 */
#endif
} Ovc_CoreId;

/* List of the redirection memory type */
typedef enum
{
    OVC_REDIRECT_MEM_TYPE_CORE0_TCM = 0U, /* redirection to the Core 0 TCM */
    OVC_REDIRECT_MEM_TYPE_CORE1_TCM,      /* redirection to the Core 1 TCM, for CHIP THA6206 and THA6412 */
    OVC_REDIRECT_MEM_TYPE_GMU_MEM,        /* redirection to the global SRAM (GMU0/1, Memory Domain Address) */
    OVC_REDIRECT_MEM_TYPE_GMU_DEV         /* redirection to the global SRAM (GMU0/1, Device Domain Address) */
} Ovc_RedirectMemType;

/* List of the overlay block size */
typedef enum
{
    OVC_BLOCK_SIZE_64BYTE = 0xFFEU,  /* 64 byte overlay block size */
    OVC_BLOCK_SIZE_128BYTE = 0xFFCU, /* 128 byte overlay block size */
    OVC_BLOCK_SIZE_256BYTE = 0xFF8U, /* 256 byte overlay block size */
    OVC_BLOCK_SIZE_512BYTE = 0xFF0U, /* 512 byte overlay block size */
    OVC_BLOCK_SIZE_1KB = 0xFE0U,     /* 1kb overlay block size */
    OVC_BLOCK_SIZE_2KB = 0xFC0U,     /* 2kb overlay block size */
    OVC_BLOCK_SIZE_4KB = 0xF80U,     /* 4kb overlay block size */
    OVC_BLOCK_SIZE_8KB = 0xF00U,     /* 8kb overlay block size */
    OVC_BLOCK_SIZE_16KB = 0xE00U,    /* 16kb overlay block size */
    OVC_BLOCK_SIZE_32KB = 0xC00U,    /* 32kb overlay block size */
    OVC_BLOCK_SIZE_64KB = 0x800U,    /* 64kb overlay block size */
    OVC_BLOCK_SIZE_128KB = 0x0U      /* 128kb overlay block size */
} Ovc_BlockSize;

/* List of the available block IDs */
typedef enum
{
    OVC_BLOCK_ID_0 = 0U, /* Block 0 */
    OVC_BLOCK_ID_1,      /* Block 1 */
    OVC_BLOCK_ID_2,      /* Block 2 */
    OVC_BLOCK_ID_3,      /* Block 3 */
    OVC_BLOCK_ID_4,      /* Block 4 */
    OVC_BLOCK_ID_5,      /* Block 5 */
    OVC_BLOCK_ID_6,      /* Block 6 */
    OVC_BLOCK_ID_7,      /* Block 7 */
    OVC_BLOCK_ID_8,      /* Block 8 */
    OVC_BLOCK_ID_9,      /* Block 9 */
    OVC_BLOCK_ID_10,     /* Block 10 */
    OVC_BLOCK_ID_11,     /* Block 11 */
    OVC_BLOCK_ID_12,     /* Block 12 */
    OVC_BLOCK_ID_13,     /* Block 13 */
    OVC_BLOCK_ID_14,     /* Block 14 */
    OVC_BLOCK_ID_15,     /* Block 15 */
    OVC_BLOCK_ID_16,     /* Block 16 */
    OVC_BLOCK_ID_17,     /* Block 17 */
    OVC_BLOCK_ID_18,     /* Block 18 */
    OVC_BLOCK_ID_19,     /* Block 19 */
    OVC_BLOCK_ID_20,     /* Block 20 */
    OVC_BLOCK_ID_21,     /* Block 21 */
    OVC_BLOCK_ID_22,     /* Block 22 */
    OVC_BLOCK_ID_23,     /* Block 23 */
    OVC_BLOCK_ID_24,     /* Block 24 */
    OVC_BLOCK_ID_25,     /* Block 25 */
    OVC_BLOCK_ID_26,     /* Block 26 */
    OVC_BLOCK_ID_27,     /* Block 27 */
    OVC_BLOCK_ID_28,     /* Block 28 */
    OVC_BLOCK_ID_29,     /* Block 29 */
    OVC_BLOCK_ID_30,     /* Block 30 */
    OVC_BLOCK_ID_31,     /* Block 31 */

} Ovc_BlockId;

/* List of bypass flags */
typedef enum
{
    OVC_BYPASS_FLAGS = 0U,    /* The address passes through without any processing */
    OVC_NON_BYPASS_FLAGS = 3U /* The address need overlay */
} Ovc_BypassFlags;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* Structure of OVC Block Configuration */
typedef struct
{
    Ovc_BlockId blockId;                 /* overlay block id */
    Ovc_BlockSize blockSize;             /* overlay block size */
    Ovc_RedirectMemType redirectMemType; /* redirection memory type */
    Ovc_CoreId coreId;                   /* core id */
    uint32 targetBaseAddress;            /* target base address */
    uint32 redirectionBaseAddress;       /* redirection base address */
} Ovc_BlockConfig;

/* #Violation: ovc_hal_h_REF_1 */
#define OVC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: ovc_hal_h_REF_2 */
#include "Ovc_MemMap.h"



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
 * Function:     Ovc_Hal_InitBlock
 * Description:  This function initializes the overlay block
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (This function is non-reentrant when operating on the same OVC, 
 *                   but reentrant when operating on different OVC.)
 * Input:        pOvc: pointer to the OVC module
 *               pConfig: Configuration structure of the block
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/01    01208     Create
 *********************************************************************************************************************/
extern boolean Ovc_Hal_InitBlock(OVC_MODULE *const pOvc, const Ovc_BlockConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Ovc_Hal_EnableBlock
 * Description:  This function enables the overlay block function
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (This function is non-reentrant when operating on the same block ID, 
 *                   but reentrant when operating on different Block ID.)
 * Input:        pOvc: pointer to the OVC module
 *               coreId: Core id
 *               blockId: Block id
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/01    01208     Create
 *********************************************************************************************************************/
extern boolean Ovc_Hal_EnableBlock(OVC_MODULE *const pOvc, Ovc_CoreId coreId, Ovc_BlockId blockId);

/**********************************************************************************************************************
 * Function:     Ovc_Hal_DisableBlock
 * Description:  This function disables the overlay block function
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (This function is non-reentrant when operating on the same block ID, 
 *                   but reentrant when operating on different Block ID.)
 * Input:        pOvc: pointer to the OVC module
 *               coreId: Core id
 *               blockId: Block id
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/01    01208     Create
 *********************************************************************************************************************/
extern boolean Ovc_Hal_DisableBlock(OVC_MODULE *const pOvc, Ovc_CoreId coreId, Ovc_BlockId blockId);

/**********************************************************************************************************************
 * Function:     Ovc_Hal_EnableCore
 * Description:  This function enables the core for overlay function
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (This function is non-reentrant when operating on the same OVC, 
 *                   but reentrant when operating on different OVC.)
 * Input:        pOvc: pointer to the OVC module
 *               coreId: Core id
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/01    01208     Create
 *********************************************************************************************************************/
extern boolean Ovc_Hal_EnableCore(OVC_MODULE *const pOvc, Ovc_CoreId coreId);

/**********************************************************************************************************************
 * Function:     Ovc_Hal_DisableCore
 * Description:  This function disables the core for overlay function
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (This function is non-reentrant when operating on the same OVC, 
 *                   but reentrant when operating on different OVC.)
 * Input:        pOvc: pointer to the OVC module
 *               coreId: Core id
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/01    01208     Create
 *********************************************************************************************************************/
extern boolean Ovc_Hal_DisableCore(OVC_MODULE *const pOvc, Ovc_CoreId coreId);

/**********************************************************************************************************************
 * Function:     Ovc_Hal_GetErrorFlagStatus
 * Description:  This function gets error flag status
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pOvc: pointer to the OVC module
 *               coreId: Core id
 * Inout:        None
 * Output:       None
 * Return:       uint32: Error flag status macro
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/01    01208     Create
 *********************************************************************************************************************/
extern uint32 Ovc_Hal_GetErrorFlagStatus(const OVC_MODULE *const pOvc, Ovc_CoreId coreId);

/**********************************************************************************************************************
 * Function:     Ovc_Hal_ClearErrorFlagStatus
 * Description:  This function clears error flag status
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (This function is non-reentrant when operating on the same OVC Core ID, 
 *                   but reentrant when operating on different OVC Core ID.)
 * Input:        pOvc: Pointer to the OVC module
 *               coreId: Core id
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/01    01208     Create
 *********************************************************************************************************************/
extern void Ovc_Hal_ClearErrorFlagStatus(OVC_MODULE *const pOvc, Ovc_CoreId coreId);

/**********************************************************************************************************************
 * Function:     Ovc_Hal_BypassControl
 * Description:  This function control bypass function
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pOvc: pointer to the OVC module
 *               coreId: Core id
 *               flags: bypass or non-bypass
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       BYPASS register is protected by E permission
 * History:
 *  Date          Author    Modified
 *  2023/10/12    01208     Create
 *  2024/08/13    01208     Modify the register object
 *********************************************************************************************************************/
extern boolean Ovc_Hal_BypassControl(OVC_MODULE *const pOvc, Ovc_CoreId coreId, Ovc_BypassFlags flags);

/* #Violation: ovc_hal_h_REF_1 */
#define OVC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: ovc_hal_h_REF_2 */
#include "Ovc_MemMap.h"

#endif /* OVC_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
