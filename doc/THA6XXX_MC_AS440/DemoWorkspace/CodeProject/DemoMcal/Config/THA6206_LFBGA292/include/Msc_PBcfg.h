/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Msc_PBcfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : MSC
*
*   brief                 : This file contains all configurations of MSC module
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

#ifndef MSC_PBCFG_H_
#define MSC_PBCFG_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Msc_GeneralTypes.h"

/***************************************************************************************************
*                            Definitions and Macros
****************************************************************************************************/
#define ICU_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Icu_MemMap.h"

/* Extern declaration of Msc Msc_ConfigSet */
extern const Msc_ConfigType Msc_ConfigSet[1U];


#define ICU_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Icu_MemMap.h"

#endif /* MSC_PBCFG_H */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
