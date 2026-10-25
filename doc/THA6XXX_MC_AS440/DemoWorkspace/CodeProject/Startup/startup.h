/**************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName: startup.h
 * Author:    30032
 * Version:   v1.0
 * Date:     2023/05/14
 * Description: This file defines related macro related to compiler.
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/14    30032     create
 ************************************************************************************************/
#ifndef STARTUP_H_
#define STARTUP_H_

#if defined(__ghs__)
#include "startup_ghs.h"
#elif defined(__ICCARM__)
#include "startup_iar.h"
#elif defined(__ARMCC_VERSION)
#include "startup_ads.h"
/* include compiler_hightec.h if use HIGHTEC compiler.*/
#elif defined(__HIGHTEC__)
#include "startup_hightec.h"
#elif defined(__TASKING__)
#include "startup_tasking.h"
#else
#error "Unknown compiler."
#endif

extern int _main(void);

#endif /* STARTUP_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
