/**************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName: compilertypes.h
 * Author:    30032
 * Version:   V1.2.0
 * Date:      2026/02/28
 * Description: This file defines related macro related to compiler.
 ************************************************************************************************/
#ifndef COMPILERTYPES_H_
#define COMPILERTYPES_H_
/* include compiler_ghs.h if use GHS compiler.*/
#if defined(__ghs__)
#include "compiler_ghs.h"
/* include compiler_iar.h if use IAR compiler.*/
#elif defined(__ICCARM__)
#include "compiler_iar.h"
/* include compiler_ads.h if use ADS compiler.*/
#elif defined(__ARMCC_VERSION)
#include "compiler_ads.h"
/* include compiler_hightec.h if use HIGHTEC compiler.*/
#elif defined(__HIGHTEC__)
#include "compiler_hightec.h"
/* include compiler_hightec.h if use TASKING compiler.*/
#elif defined(__TASKING__)
#include "compiler_tasking.h"
#else
#error "Unknown compiler."
#endif

#endif /* COMPILERTYPES_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
