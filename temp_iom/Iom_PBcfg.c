/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Iom_PBCfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : IOM
*
*   brief                 : This file contains all configurations of IOM Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Codeing Rule Violations                                                **
****************************************************************************************************/
/*
*#Violation Summary
*#Iom_PBCfg_c_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*#Iom_PBCfg_c_REF_2:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Iom_PBCfg_c_REF_3:CWE-547; 
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*
*#Iom_PBCfg_c_REF_4:MISRAC2012-Rule-10.5; 
* Justification: Necessary type casting to reduce code complexity; Code review ensure the safety of the casting.
*
*/


/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Iom.h"

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
/* #Violation: Iom_PBCfg_c_REF_1 */
#define IOM_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Iom_MemMap.h"
/* #Violation: Iom_PBCfg_c_REF_3 */
static const Iom_LpuConfigType Iom_LPUConfiguration[1] =
{
    {
        /* LPU channel  */ 
        IOM_LPUID_,
        /* LPU event source and edge triggering configuration */
        {
            ,

        },
        /* LPU eventWindow configuration */
        {
            /* LPU eventWindow source */
            ,
            /* LPU eventWindow edge triggering */
            ,
            /* LPU eventWindow running mode */
            ,
            /* Whether to invert the event window */
            TRUE,
            /* The time the event window lasts */
            U,
        },
        {
        /* EMU configuration */
            /* Which EMU counter is selected for the LPU channel */
            ,
            /* EMU counter threshold */
        }
    }
}; 

/* #Violation: Iom_PBCfg_c_REF_3 */
static const Iom_EmuCombinerType Iom_EMUCombinerCfg[1] =
{
    {
        IOM_LPUID_0,
    }
};
/* #Violation: Iom_PBCfg_c_REF_1 */
#define IOM_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Iom_PBCfg_c_REF_2 */
#include "Iom_MemMap.h"

/* #Violation: Iom_PBCfg_c_REF_1 */
#define IOM_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Iom_PBCfg_c_REF_2 */
#include "Iom_MemMap.h"
const Iom_ConfigType Iom_ConfigSet[1U] =
{
    {
        /* LPU channel configuration */
        &Iom_LPUConfiguration[0U],
        /* EMU combined channel logging */
        65536U,
        /* EMU combined channel configuration */
        &Iom_EMUCombinerCfg[0U],
        /* Iom Clock divide factor */
        (U)
    }
};

/* #Violation: Iom_PBCfg_c_REF_1 */
#define IOM_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Iom_PBCfg_c_REF_2 */
#include "Iom_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
  
