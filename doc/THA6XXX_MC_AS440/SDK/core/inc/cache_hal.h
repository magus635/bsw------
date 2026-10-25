/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:  cache_hal.h
 * Author:    00412
 * Version:   V1.2.0
 * Date:      2026/02/28
 * Description: This file contains all data type definitions and function declarations
 *********************************************************************************************************************/

#ifndef CORE_CACHE_HAL_H_
#define CORE_CACHE_HAL_H_

/**********************************************************************************************************************
 *                                                Includes
 *********************************************************************************************************************/
#include "Platform_Types.h"

/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                              Global Union Definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                         Global Function Definitions
 *********************************************************************************************************************/
#define CORE_START_SEC_CODE_ASIL_D_GLOBAL
#include "Core_MemMap.h"
/**********************************************************************************************************************
 * Function:     Cache_Hal_EnableD
 * Description:  Enable D-Cache
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       void
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/16    00412      create
 *********************************************************************************************************************/
extern void Cache_Hal_EnableD(void);
/**********************************************************************************************************************
 * Function:     Cache_Hal_DisableD
 * Description:  Disable D-Cache
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       void
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/17    00412      create
 *********************************************************************************************************************/
extern void Cache_Hal_DisableD(void);
/**********************************************************************************************************************
 * Function:     Cache_Hal_EnableI
 * Description:  Enable I-Cache
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       void
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/17    00412      create
 *********************************************************************************************************************/
extern void Cache_Hal_EnableI(void);
/**********************************************************************************************************************
 * Function:     Cache_Hal_DisableI
 * Description:  Disable I-Cache
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       void
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/17    00412      create
 *********************************************************************************************************************/
extern void Cache_Hal_DisableI(void);
/**********************************************************************************************************************
 * Function:     Cache_Hal_InvalidateI
 * Description:  Invalidate I-Cache
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       void
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/17    00412      create
 *********************************************************************************************************************/
extern void Cache_Hal_InvalidateI(void);
/**********************************************************************************************************************
 * Function:     Cache_Hal_InvalidateD
 * Description:  Invalidate D-Cache
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       void
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/18    00412      create
 *********************************************************************************************************************/
extern void Cache_Hal_InvalidateD(void);
/**********************************************************************************************************************
 * Function:     Cache_Hal_CleanD
 * Description:  Clean D-Cache
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       void
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/16    00412      create
 *********************************************************************************************************************/
extern void Cache_Hal_CleanD(void);
/**********************************************************************************************************************
 * Function:     Cache_Hal_CleanInvalidateD
 * Description:  Clean & Invalidate D-Cache
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       void
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/18    00412      create
 *********************************************************************************************************************/
extern void Cache_Hal_CleanInvalidateD(void);

#define CORE_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Core_MemMap.h"

#endif /* CORE_CACHE_HAL_H_ */

/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
