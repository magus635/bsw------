/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:  mpu_hal.h
 * Author:    00412
 * Version:   V1.2.0
 * Date:      2026/02/28
 * Description: This file contains all data type definitions and function declarations
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #mpu_hal_h_REF_1:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*/

#ifndef CORE_MPU_HAL_H_
#define CORE_MPU_HAL_H_

/**********************************************************************************************************************
 *                                                Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* #Violation: mpu_hal_h_REF_1 */
#define MAX_GROUP_MEM_ATT_INDEX 4U
/* #Violation: mpu_hal_h_REF_1 */
#define MAX_TOTAL_MEM_ATT_INDEX 8U
#define LIMIT_ADDRESS_ALIGN_SIZE 64U
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* Enumeration for MPU share ability field */
typedef enum
{
    MPU_NONE_SHAREABLE = 0, /* This region shareability is not shareable */
    MPU_UNPREDICTABLE,      /* This region shareability is unpredictable */
    MPU_OUTER_SHAREABLE,    /* This region shareability is outer shareable */
    MPU_INNER_SHAREABLE,    /* This region shareability is inner shareable */
} MPU_ShareabilityField;

/* Enumeration for exception level access permission */
typedef enum
{
    MPU_EL1RW_EL0NONE = 0, /* To EL1 PMU, the value indicates EL1 has read and write permission on this region,
                              but EL0 has none permission.
                              To EL2 PMU, the value indicate EL2 has read and write permission on this region,
                              but EL1/0 has none permission. */
    MPU_EL1RW_EL0RW,       /* To EL1 PMU, the value indicates both EL1 and EL0 has read
                              and write permission on this region.
                              To EL2 PMU, the value indicates EL2/1/0 has read
                              and write permission on this region. */
    MPU_EL1RO_EL0NONE,     /* To EL1 PMU, the value indicates EL1 has read only permission on this region,
                              but EL0 has none permission.
                              To EL2 PMU, the value indicates EL2 has read only permission on this region,
                              but EL1/0 has none permission. */
    MPU_EL1RO_EL0RO,       /* To EL1 PMU, the value indicates both EL1 and EL0 has read only permission on this region.
                              To EL2 PMU, the value indicates EL2/1/0 has read only permission on this region. */
} MPU_ELAccessPermission;

/* Enumeration for execute permitted */
typedef enum
{
    MPU_EXECUTE_PERMITTED = 0, /* Program permit execute in this region */
    MPU_EXECUTE_NEVER,         /* Program execute never in this region */
} MPU_EN;

/**********************************************************************************************************************
 *                                              Global Union Definitions
 **********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* Structure for region attribute */
typedef struct
{
    uint32 MPU_StartAddress;              /* The start addresses of region */
    uint32 MPU_RegionSize;                /* The size of the region */
    MPU_ShareabilityField MPU_ShareField; /* Shareability field of the region */
    MPU_ELAccessPermission MPU_AccPerm;   /* Data access permission of the region */
    MPU_EN MPU_XN;                        /* Execute never */
    uint16 MPU_RegionEnable;               /* Enable/Disable region */
    uint16 MPU_AttIndex;                   /* Indexes a set of attributes in one of the MAIRx registers. */
} MPU_RegionAtt;

/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Function Definitions
 *********************************************************************************************************************/

#define CORE_START_SEC_CODE_ASIL_D_GLOBAL
#include "Core_MemMap.h"

/**********************************************************************************************************************
 * Function:     MPU_Hal_EnableEL1
 * Description:  Enable EL1 MPU
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       void
 * Others:       Before calling this routine, more than one region should be
 *               set.
 * History:
 * Date          Author    Modified
 * 2022/05/23    00412      create
 *********************************************************************************************************************/
extern void MPU_Hal_EnableEL1(void);
/**********************************************************************************************************************
 * Function:     MPU_Hal_DisableEL1
 * Description:  Disable EL1 MPU
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       void
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/23    00412      create
 *********************************************************************************************************************/
extern void MPU_Hal_DisableEL1(void);
/**********************************************************************************************************************
 * Function:     MPU_Hal_EnableEL2
 * Description:  Enable EL2 MPU
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       void
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/23    00412      create
 *********************************************************************************************************************/
extern void MPU_Hal_EnableEL2(void);
/**********************************************************************************************************************
 * Function:     MPU_Hal_DisableEL2
 * Description:  Disable EL2 MPU
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       void
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/23    00412      create
 *********************************************************************************************************************/
extern void MPU_Hal_DisableEL2(void);
/**********************************************************************************************************************
 * Function:     MPU_Hal_EnableEL2Re
 * Description:  Enable EL2 MPU region
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        bRgNum: The region number, the least value is  0
 * Inout:        None
 * Output:       None
 * Return:       void
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/23    00412      create
 *********************************************************************************************************************/
extern void MPU_Hal_EnableEL2Re(uint32 uRgNum);
/**********************************************************************************************************************
 * Function:     MPU_Hal_DisableEL2Re
 * Description:  Disable EL2 MPU region
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        bRgNum: The region number, the least value is  0
 * Inout:        None
 * Output:       None
 * Return:       void
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/23    00412      create
 *********************************************************************************************************************/
extern void MPU_Hal_DisableEL2Re(uint32 uRgNum);
/**********************************************************************************************************************
 * Function:     MPU_Hal_EnableEL1Bg
 * Description:  Enable EL1 MPU background
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       void
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/23    00412      create
 *********************************************************************************************************************/
extern void MPU_Hal_EnableEL1Bg(void);
/**********************************************************************************************************************
 * Function:     MPU_Hal_DisableEL1Bg
 * Description:  Disable EL1 MPU background
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       void
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/23    00412      create
 *********************************************************************************************************************/
extern void MPU_Hal_DisableEL1Bg(void);
/**********************************************************************************************************************
 * Function:     MPU_Hal_EnableEL2Bg
 * Description:  Enable EL2 MPU background
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       void
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/23    00412      create
 *********************************************************************************************************************/
extern void MPU_Hal_EnableEL2Bg(void);
/**********************************************************************************************************************
 * Function:     MPU_Hal_DisableEL2Bg
 * Description:  Disable EL2 MPU background
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       void
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/23    00412      create
 *********************************************************************************************************************/
extern void MPU_Hal_DisableEL2Bg(void);
/**********************************************************************************************************************
 * Function:     MPU_Hal_SetEL1Re
 * Description:  Set one new EL1 MPU region
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        bRgNum:The region number
 *               pRegionAtt: The pointer to the input parameters
 * Inout:        None
 * Output:       None
 * Return:       void
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/23    00412      create
 *********************************************************************************************************************/
extern void MPU_Hal_SetEL1Re(uint8 bRgNum, const MPU_RegionAtt * const pRegionAtt);
/**********************************************************************************************************************
 * Function:     MPU_Hal_SetEL2Re
 * Description:  Set one new EL2 MPU region
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        bRgNum:The region number
 *               pRegionAtt: The pointer to the input parameters
 * Inout:        None
 * Output:       None
 * Return:       void
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/23    00412      create
 *********************************************************************************************************************/
extern void MPU_Hal_SetEL2Re(uint8 bRgNum, const MPU_RegionAtt * const pRegionAtt);
/**********************************************************************************************************************
 * Function:     MPU_Hal_SetMemAttri
 * Description:  Set new memory attribute
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        bAttIndex:The attribute index,the least value is 0 other than 1
 *               bMemAtt: The value of memory attribute
 * Inout:        None
 * Output:       None
 * Return:       void
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/23    00412      create
 *********************************************************************************************************************/
extern void MPU_Hal_SetMemAttri(uint8 bAttIndex, uint8 bMemAtt);

#define CORE_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Core_MemMap.h"

#endif /* CORE_MPU_HAL_H_ */

/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
