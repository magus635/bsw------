/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    gmu_hal.h
 * Author:      01368
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of interfaces.
 *********************************************************************************************************************/
/*
*#Violation Summary
*#gmu_hal_h_REF_1:MISRAC2012-Rule-2.5;
* Justification:reason 1534 The macros are reserved for upper layers. 
*
* #gmu_hal_h_REF_2:MISRAC2012-Rule-2.3;
* Justification: Reserved types are defined in AUTOSAR specifications.
*
*/
#ifndef GMU_HAL_H_
#define GMU_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "gmu_register.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* The GMU MPU register control */
#define GMU_REG_LOW_ADDR_MASK ((uint32)0x000FFFE0U)
#define GMU_REG_HIGH_ADDR_MASK ((uint32)0x000FFFE0U)
#define GMU_ADDR_MASK ((uint32)0x10000000U)

/* The GMU SPMCTRL register:Sleep mode control */
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_SLEEP_MODE_MASK ((uint32)0x00000000FU)
#if defined(THA6_THA6206) || defined(THA6_THA6206D)
#define GMU_SLEEP_MODE_EN_MASK ((uint32)0x0000000FFU)
#endif /* THA6_THA6206 || THA6_THA6206D */
#if defined(THA6_THA6412)
#define GMU_SLEEP_MODE_EN_MASK ((uint32)0x00000000FU)
#endif /* THA6_THA6412 */
#if defined(THA6_THA6104)
#define GMU_SLEEP_MODE_EN_MASK ((uint32)0x00000003FU)
#endif /* THA6_THA6104 */
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_GROUP0_SLEEP_MODE_MASK ((uint32)0x03U)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_GROUP1_SLEEP_MODE_MASK ((uint32)0x0CU)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_GROUP2_SLEEP_MODE_MASK ((uint32)0x30U) /* It support THA6206 and THA6104, not support THA6412 */
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_GROUP3_SLEEP_MODE_MASK ((uint32)0xC0U) /* It support THA6206, not support THA6412 and THA6104 */
#define GMU_GROUP0_SLEEP_MODE_EN_MASK ((uint32)0x03U)
#define GMU_GROUP1_SLEEP_MODE_EN_MASK ((uint32)0x0CU)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_GROUP2_SLEEP_MODE_EN_MASK ((uint32)0x30U) /* It support THA6206 and THA6104, not support THA6412 */
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_GROUP3_SLEEP_MODE_EN_MASK ((uint32)0xC0U) /* It support THA6206, not support THA6412 and THA6104 */

/* The GMU MEMSTS register:Memory State */
#if defined(THA6_THA6412)
#define GMU_MEM_STATUS_DEF_MASK ((uint32)0x037FFC3FU)
#endif /* THA6_THA6412 */
#if defined(THA6_THA6206) || defined(THA6_THA6104) || defined(THA6_THA6206D)
#define GMU_MEM_STATUS_DEF_MASK ((uint32)0x007FFC3FU)
#endif /* THA6_THA6206 || THA6_THA6104 || THA6_THA6206D */
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_SFR_ERR_MASK ((uint32)0x1U)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_SFR_RDN_ERR_MASK ((uint32)0x2U)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_RES_ERR_MASK ((uint32)0x4U)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_MPU_RO_ERR_MASK ((uint32)0x8U)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_MPU_READ_ERR_MASK ((uint32)0x10U)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_MPU_WRITE_ERR_MASK ((uint32)0x20U)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_RD_DOU_BIT_ECC_ERR_MASK ((uint32)0x400U)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_RD_SIN_BIT_OVFL_ERR_MASK ((uint32)0x800U)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_RD_SIN_BIT_ECC_ERR_MASK ((uint32)0x1000U)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_READ_MODIFY_WRITE_ERR_MASK ((uint32)0x2000U)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_CTRL_SIN_PARITY_ERR_MASK ((uint32)0x4000U)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_CTRL_SIN_EDC_ERR_MASK ((uint32)0x8000U)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_WRITE_DATA_EDC_ERR_MASK ((uint32)0x10000U)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_ADDR_EDC_ERR_MASK ((uint32)0x20000U)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_UPSTR_IPBUS_ERR_MASK ((uint32)0x40000U)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_DOWNSTR_IPBUS_ERR_MASK ((uint32)0x80000U)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_UPSTR_GIFBUS_ERR_MASK ((uint32)0x100000U)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_DOWNSTR_GIFBUS_ERR_MASK ((uint32)0x200000U)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_UPSTR_TIMEOUT_ERR_MASK ((uint32)0x400000U)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_RMW_BUFFER_ERR_MASK ((uint32)0x1000000U) /* It's not support THA6206 and THA6104, support THA6412 */
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_READ_BUFFER_ERR_MASK ((uint32)0x2000000U) /* It's not support THA6206 and THA6104, support THA6412 */

/* The GMU SPMCTRL1 register: Sleep Mode Control1  */
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_G0_SLEEP_MODE_DIS ((uint32)0x00U)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_G0_SLEEP_MODE_EN ((uint32)0x03U)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_G1_SLEEP_MODE_DIS ((uint32)0x00U)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_G1_SLEEP_MODE_EN ((uint32)0x0CU)

/* The GMU SPSTS register: Sleep state  */
#if defined (THA6_THA6412)
#define GMU_SLEEP_STATUS_DEF_MASK ((uint32)0x00000003U)
#endif /* THA6_THA6412 */
#if defined (THA6_THA6206) || defined(THA6_THA6206D)
#define GMU_SLEEP_STATUS_DEF_MASK ((uint32)0x0000000FU)
#endif /* THA6_THA6206 || THA6_THA6206D */
#if defined (THA6_THA6104)
#define GMU_SLEEP_STATUS_DEF_MASK ((uint32)0x00000007U)
#endif /* THA6_THA6104 */

/*GMU Master ID Mask*/
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_MASTER_CORE0_MASK ((uint32)0x01U << 0)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_MASTER_CORE1_MASK ((uint32)0x01U << 1) /* It's not support THA6104 */
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_MASTER_CORE2_MASK ((uint32)0x01U << 14) /* It's not support THA6206 and THA6104, support THA6412 */
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_MASTER_CORE3_MASK ((uint32)0x01U << 15) /* It's not support THA6206 and THA6104, support THA6412 */
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_MASTER_ETH_MASK ((uint32)0x01U << 16)


#if defined (THA6_THA6412)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_MASTER_DMA0_MASK ((uint32)0x01U << 17)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_MASTER_HSM_MASK ((uint32)0x01U << 19)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_MASTER_GTM_MASK ((uint32)0x01U << 18)
#endif /* THA6_THA6412 */
#if defined (THA6_THA6206) || defined(THA6_THA6206D)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_MASTER_DMA0_MASK ((uint32)0x01U << 2)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_MASTER_HSM_MASK ((uint32)0x01U << 2)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_MASTER_GTM_MASK ((uint32)0x01U << 18)
#endif /* THA6_THA6206 || THA6_THA6206D */
#if defined (THA6_THA6104)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_MASTER_DMA0_MASK ((uint32)0x01U << 18)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_MASTER_HSM_MASK ((uint32)0x01U << 17)
#endif /* THA6_THA6104 */



/* The GMU MEMCFG0 register mask */
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_MEM_CONFIG0_DEF_MASK ((uint32)0xFFFFFFFFU)  /* It's not support THA6206 and THA6104, support THA6412 */

/* The GMU MEMCFG0 register:Read buffer */
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_READ_BUFFER_EN_MASK ((uint32)0xC0000000U) /* It's not support THA6206 and THA6104, support THA6412 */
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_READ_BUFFER_EN ((uint32)0xC0000000U) /* It's not support THA6206 and THA6104, support THA6412 */
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_READ_BUFFER_PERMISSION_MASK ((uint32)0x3C000000U) /* It's not support THA6206 and THA6104, support THA6412 */
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_READ_BUFFER_MASTER_CORE0 ((uint32)0x04000000U) /* It's not support THA6206 and THA6104, support THA6412 */
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_READ_BUFFER_MASTER_CORE1 ((uint32)0x08000000U) /* It's not support THA6206 and THA6104, support THA6412 */
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_READ_BUFFER_MASTER_CORE2 ((uint32)0x10000000U) /* It's not support THA6206 and THA6104, support THA6412 */
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_READ_BUFFER_MASTER_CORE3 ((uint32)0x20000000U) /* It's not support THA6206 and THA6104, support THA6412 */
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_READ_BUFFER_START_ADD_MASK ((uint32)0x00001FFFU) /* It's not support THA6206 and THA6104, support THA6412 */
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_READ_BUFFER_END_ADD_MASK ((uint32)0x03FFE000U) /* It's not support THA6206 and THA6104, support THA6412 */

/* The GMU MEMCFG1 register mask */
#if defined (THA6_THA6412)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_MEM_CONFIG1_DEF_MASK ((uint32)0x000FFFEFU)
#endif /* THA6_THA6412 */
#if defined (THA6_THA6206) || defined (THA6_THA6104) || defined(THA6_THA6206D)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_MEM_CONFIG1_DEF_MASK ((uint32)0x000FFFE3U)
#endif /* THA6_THA6206 || THA6_THA6104 || THA6_THA6206D */
/* The GMU MEMCFG1 register:RMW buffer enable*/
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_RMW_BUFFER_EN_MASK ((uint32)0x0000000CU)
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_RMW_BUFFER_EN ((uint32)0x0000000CU)

/* The GMU ALMMSK register mask */
/* #Violation: gmu_hal_h_REF_1 */
#define GMU_ALM_MASK_DEF_MASK ((uint32)0x0FFFFC00U)

/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* List of the return status of API function */
typedef enum
{
    GMU_STATUS_OK = 0,            /* The return value is successful */
    GMU_STATUS_FAILED,            /* The return value is failed */
    GMU_STATUS_NOT_INITIALIZED,   /* The GMU module is not initialized */
    GMU_STATUS_INPUT_PARAM_ERROR /* The input parameters have error */
} GMU_ResultStatus;

/* List of the sleep mode group */
typedef enum
{
    GMU_SPM_GROUP0, /* Select sram sleep group0 */
    GMU_SPM_GROUP1, /* Select sram sleep group1 */
#if defined(THA6_THA6104) || defined(THA6_THA6206) || defined(THA6_THA6206D)
    GMU_SPM_GROUP2, /* Select sram sleep group2; It's support THA6206 and THA6104, not support THA6412 */
#endif /* end THA6_THA6104 and THA6_THA6206 || THA6_THA6206D */
#if defined(THA6_THA6206) || defined(THA6_THA6206D)
    GMU_SPM_GROUP3  /* Select sram sleep group3; It's support THA6206, not support THA6412 and THA6104 */ 
#endif /* end THA6_THA6206 || THA6_THA6206D */
} GMU_SleepModeGroup;

/* Enumeration list of sleep mode enable */
typedef enum
{
    GMU_SPM_DISENABLE,     /* Sleep mode disable */
    GMU_SPM_ENABLE = 0x03U /* Sleep mode enable */
} GMU_SleepModeEn;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* Structure of sleep mode configuration */
typedef struct
{
    GMU_SleepModeGroup uGroup;    /* Select sleep group */
    GMU_SleepModeEn uSleepEnable; /* Sleep mode enabled or disable */
} GMU_SleepCfg;

/* Structure of region attributes.   */
typedef struct
{
    uint32 uLowerAddress;    /* The region lower address */
    uint32 uHigherAddress;   /* The region higher address */
    uint32 uWritePermission; /* The write permission to region */
    uint32 uReadPermission;  /* The read permission to region */
} GMU_RegAttr;

/* Structure of memory basic configuration */
typedef struct
{
    boolean rmwBufEnable;       /* RMW buffer function enabled or disable */
    boolean readBufEnable;      /* Read buffer function enabled or disable */
    uint32 readBufStartAddress; /* The region lower address */
    uint32 readBufEndAddress;   /* The region higher address */
    uint32 readBufPermission;   /* The read buffer permission */
/* #Violation: gmu_hal_h_REF_2 */
} GMU_MemBufCfg;


#define GMU_START_SEC_CODE_ASIL_D_GLOBAL
#include "Gmu_MemMap.h"
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
* Function:    Gmu_Register_ReadBack_Check
* Description: Checks whether the register value written is equal to the value read back 
* Sync/Async:  Synchronous
* Reentrancy:  Non-Reentrant
* Input:       expect: Read back the value of the registe
*              value: value written to register
*              state: Wrong initial state
* Output:      None
* Return:      boolean: Flag indicating whether the value written to register is the same as the value read back
* Others:      None
* History:     None
* Date         Author    Modified
* 2025/03/10   01368     create
*********************************************************************************************************************/ 
LOCAL_FORCEINLINE boolean Gmu_Register_ReadBack_Check(boolean state, uint32 value, uint32 expect);
/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
#define GMU_REG_CHECK
#if defined(GMU_REG_CHECK)
LOCAL_FORCEINLINE boolean Gmu_Register_ReadBack_Check(boolean state, uint32 value, uint32 expect)
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
LOCAL_FORCEINLINE boolean Gmu_Register_ReadBack_Check(boolean state, uint32 value, uint32 expect)
{
    (void)state;
    (void)expect;
    (void)value;

    return state;
}
#endif
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:     GMU_Hal_Initialize
 * Description:  This function initializes GMU module, include enable GMU clock, initialize RAM space.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pGmu: Pointer to GMU module
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/08/16    01763     Create
 *********************************************************************************************************************/
extern boolean GMU_Hal_Initialize(const GMU_MODULE *const pGmu);

/**********************************************************************************************************************
 * Function:     GMU_Hal_GetMemStatus
 * Description:  This function gets the status of current memory. If there are some errors in memory,
 *               those error status bits will be set to 1; otherwise the error status bit will be set to 0.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pGmu: Pointer to GMU module
 * Inout:        None
 * Output:       None
 * Return:       uint32: Get the memory status value in MEMSTS register
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/08/16    01763     Create
 *********************************************************************************************************************/
extern uint32 GMU_Hal_GetMemStatus(const GMU_MODULE *const pGmu);

/**********************************************************************************************************************
 * Function:     GMU_Hal_ClearMemStatus
 * Description:  This function clears the status that has been set.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pGmu: Pointer to GMU module
 *               uStatus: The memory status value that want to clear in MEMSTS register.
 *               The value range of uStatus is form 0U - 0x0x7FFC3FU in THA6206 and 
 *               THA6104, 0U - 0x37FFC3FU in THA6412.           
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/08/16    01763     Create
 *********************************************************************************************************************/
extern boolean GMU_Hal_ClearMemStatus(GMU_MODULE *const pGmu, uint32 uStatus);

/**********************************************************************************************************************
 * Function:     GMU_Hal_SetSleepMode
 * Description:  This function enable or disable sleep mode for Sram group.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pGmu: Pointer to GMU module
 *               pConfig: The pointer to structure of Sleep mode.
 * Inout:        None
 * Output:       None
 * Return:       GMU_ResultStatus: Whether Set GMU sleep mode successfull, or check the parameter whether successful
 * Others:       None
 * History:
 * Date          Author    Modified
 * 2024/08/16    01763     Create
 *********************************************************************************************************************/
extern GMU_ResultStatus GMU_Hal_SetSleepMode(GMU_MODULE *const pGmu, const GMU_SleepCfg *const pConfig);

/**********************************************************************************************************************
 * Function:     GMU_Hal_GetMemSleepStatus
 * Description:  This function gets the memory group sleep is active or not.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pGmu: Pointer to GMU module
 * Inout:        None
 * Output:       None
 * Return:       uint32: The memory group sleep status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/08/16    01763     Create
 *********************************************************************************************************************/
extern uint32 GMU_Hal_GetMemSleepStatus(const GMU_MODULE *const pGmu);

/**********************************************************************************************************************
 * Function:     GMU_Hal_SetMemConfig
 * Description:  This function sets the event mask config. Once the error occurs,
 *               the mask determines the system process method.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pGmu: Pointer to GMU module
 *               uMask: The event mask needs to config MEMCFG1 register. 
 *               The value range of uStatus is form 0U - 0xFFFE3U in THA6206 and THA6104, 
 *               0U - 0xFFFEFU in THA6412
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/08/16    01763     Create
 *********************************************************************************************************************/
extern boolean GMU_Hal_SetMemConfig(GMU_MODULE *const pGmu, uint32 uMask);

/**********************************************************************************************************************
 * Function:     GMU_Hal_GetMemConfig
 * Description:  This function gets the current config of the memory. Before setting memory config,
 *               the developer can get the current memory config firstly.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pGmu: Pointer to GMU module
 * Inout:        None
 * Output:       None
 * Return:       uint32: Get the current register value of MEMCFG1 
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/08/16    01763     Create
 *********************************************************************************************************************/
extern uint32 GMU_Hal_GetMemConfig(const GMU_MODULE *const pGmu);


#if defined (THA6_THA6412)
/**********************************************************************************************************************
 * Function:     GMU_Hal_SetMemBufConfig
 * Description:  This function set the current config of the R-buffer function and RMW function.
 *               R-buffer include: enable function,region start and end address,and permission.
 *                 RMW include: enable function. 
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pGmu: Pointer to GMU module
 *               pConfig: R-buffer and RMW function config.
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       Note: This function is avaliable in THA6412, disavaliable in THA6206. 
 *                     Bescuse there are no register MENCFG0 in THA6206.
 * History:
 *  Date          Author    Modified
 *  2024/08/16    01763     Create
 *********************************************************************************************************************/
extern boolean GMU_Hal_SetMemBufConfig(GMU_MODULE *const pGmu, const GMU_MemBufCfg *const pConfig);

/**********************************************************************************************************************
 * Function:     GMU_Hal_GetMemBufConfig
 * Description:  This function gets the current config of the R-buffer function and RMW function.
 *               R-buffer include: enable function,region start and end address,and permission.
 *               RMW include: enable function.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pGmu: Pointer to GMU module
 *               pConfig: R-buffer and RMW function config.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       This function is avaliable in THA6412, disavaliable in THA6206. 
 *               Bescuse there are no register MENCFG0 in THA6206
 * History:
 *  Date          Author    Modified
 *  2024/08/16    01763     Create
 *********************************************************************************************************************/
extern void GMU_Hal_GetMemBufConfig(const GMU_MODULE *const pGmu, GMU_MemBufCfg *const pConfig);

#endif

/**********************************************************************************************************************
 * Function:     GMU_Hal_SetProtectRegion
 * Description:  This function sets the normal protect region. The parameters of normal protect region include:
 *               region lower address, region upper address, master write and read access.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pGmu: Pointer to GMU module
 *               uIndex: region number, the value range of uIndex is 0 ~ 31.
 *               pConfig: The pointer to structure of protect region input from upper layer.
 * Inout:        None
 * Output:       None
 * Return:       GMU_ResultStatus: The return status value, or an error occured when check paramater
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/08/16    01763     Create
 *********************************************************************************************************************/
extern GMU_ResultStatus GMU_Hal_SetProtectRegion(GMU_MODULE *const pGmu, uint32 uIndex, const GMU_RegAttr *const pConfig);

/**********************************************************************************************************************
 * Function:     GMU_Hal_GetProtectRegion
 * Description:  This function gets the attribute values of normal protect region according to the input index value.
 *               If the index value is right, the region structure will be returned, otherwise ,
 *               the return value is NULL pointer.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pGmu: Pointer to GMU module
 *               uIndex: region number, the value range of uIndex is 0 ~ 31.
 *               pConfig: The pointer to structure of protect region input from upper layer.
 * Inout:        None
 * Output:       None
 * Return:       GMU_ResultStatus: The return status value
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/08/16    01763     Create
 *********************************************************************************************************************/
extern GMU_ResultStatus GMU_Hal_GetProtectRegion(const GMU_MODULE *const pGmu, uint32 uIndex, GMU_RegAttr *const pConfig);

#define GMU_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Gmu_MemMap.h"

#endif /* GMU_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
