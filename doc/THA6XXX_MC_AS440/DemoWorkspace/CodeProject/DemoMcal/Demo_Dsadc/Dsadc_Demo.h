/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Dsadc_Demo.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DSADC
*
*   brief                 : This file contains all function declarations of Dsadc Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/
#ifndef THA6_THA6104
/* No DSADC HW unit for THA610X */

#ifndef DSADC_DEMO_H_
#define DSADC_DEMO_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"
#include "Dsadc.h"

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#define DSADC_DEMO_CONVERSION_NUM               (10U)

/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/
#define DSADC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Dsadc_MemMap.h"

extern Dsadc_ResultType DsadcDemo_MainConvResult[DSADC_DEMO_CONVERSION_NUM];

#define DSADC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Dsadc_MemMap.h"

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
#define DSADC_START_SEC_CODE_ASIL_D_GLOBAL
#include "Dsadc_MemMap.h"

extern void Dsadc_DemoEntry(void);
extern void Dsadc_Demo(void);

extern void DsadcDemo_CircularBufferFull(void);

#define DSADC_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Dsadc_MemMap.h"

#endif /* DSA_DEMO_H_ */

#endif /* #ifndef THA6_THA6104 */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
