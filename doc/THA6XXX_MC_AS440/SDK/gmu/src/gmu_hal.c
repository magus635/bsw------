/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    gmu_hal.c
 * Author:      01368
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all functions of GMU module.
 *********************************************************************************************************************/
/*
*#Violation Summary
*#gmu_hal_c_REF_1:MISRAC2012-Rule-2.1;
* Justification:reason Reserved API for user access.
*
*#gmu_hal_c_REF_2:MISRAC2012-Rule-11.4;
* Justification:reason Converting integers to object pointers to reduce register access complexity.
*
*#gmu_hal_c_REF_3:MISRAC2012-Dir-4.9;
* Justification:reason Function like macros are used to reduce code complexity.
*
*#gmu_hal_c_REF_4:MISRAC2012-Rule-8.13;
* Justification:reason Boolean can only be representes as uint8.
*
*#gmu_hal_c_REF_5:MISRAC2012-Rule-10.5;
* Justification: Limitation of Coretex-R52+ Core; Boolean can only be representes as unit8.
*
*#gmu_hal_c_REF_6:MISRAC2012-Rule-20.1;
*Justification: Imposes the specification of the section in which certain parts of the driver must be placed.

*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "gmu_hal.h"
#include "Platform_Types.h"
#include "gmu_register.h"
#include "safewdt_hal.h"
#include "cpuwdt_hal.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
#include "rcc_hal.h"
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Variable Definitions
 *********************************************************************************************************************/

#define GMU_START_SEC_CODE_ASIL_D_GLOBAL
#include "Gmu_MemMap.h"
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: gmu_hal_c_REF_1 */
boolean GMU_Hal_Initialize(const GMU_MODULE *const pGmu)
{
    
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the pSaradc is null pointer */
    /* Check GMU base address */
    /* #Violation: gmu_hal_c_REF_2 */
    /* #Violation: gmu_hal_c_REF_3 */
    Assert((boolean)CHECK_GMU_BASE(pGmu));
#endif
    boolean retSts;
    Rcc_ModuleClkType moduleGmuRccSel;
    retSts = TRUE;
    /* Get GMU mode clock number */
    /* #Violation: gmu_hal_c_REF_5 */
    /* #Violation: gmu_hal_c_REF_2 */
    /* #Violation: gmu_hal_c_REF_3 */
    moduleGmuRccSel = GMU_RCC_MODULECLK_NUM(pGmu);
    /* Enable GMU clock */
    retSts &= Rcc_Hal_SetModuleClk(moduleGmuRccSel, RCC_MODULECLK_ENABLE);
    return retSts;
}

/* #Violation: gmu_hal_c_REF_1 */
uint32 GMU_Hal_GetMemStatus(const GMU_MODULE *const pGmu)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the pSaradc is null pointer */
    /* #Violation: gmu_hal_c_REF_2 */
    /* #Violation: gmu_hal_c_REF_3 */
    Assert((boolean)CHECK_GMU_BASE(pGmu));
#endif
    /* SDK_GMU_Deviation_Rule7_2:1281:pony add for QAC */
    return (pGmu->MEMSTS & GMU_MEM_STATUS_DEF_MASK);
}

/* #Violation: gmu_hal_c_REF_1 */
boolean GMU_Hal_ClearMemStatus(GMU_MODULE *const pGmu, uint32 uStatus)
{
    boolean retSts;
    retSts = TRUE;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pSaradc is null pointer */
    /* Check GMU base address */
    /* #Violation: gmu_hal_c_REF_2 */
    /* #Violation: gmu_hal_c_REF_3 */
    Assert((boolean)(CHECK_GMU_BASE(pGmu)));
#endif
    /* Disable all interrupt */
    DISABLE_ALL_INTERRUPTS();
    /* Clear safety ENDINIT */
    /* SDK_GMU_Deviation_Rule7_2:1281:pony add for QAC */
    retSts &= Safewdt_Hal_ClearSafetyEndinit();
    pGmu->MEMSTS = (uStatus & (uint32)GMU_MEM_STATUS_DEF_MASK);
    /* Set safety ENDINIT */
    retSts &= Safewdt_Hal_SetSafetyEndinit();
    /* Enable all interrupt */ 
    ENABLE_ALL_INTERRUPTS();   
    return retSts;
}

/* #Violation: gmu_hal_c_REF_1 */
uint32 GMU_Hal_GetMemSleepStatus(const GMU_MODULE *const pGmu)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pSaradc is null pointer */
    /* Check GMU base address */
    /* #Violation: gmu_hal_c_REF_2 */
    /* #Violation: gmu_hal_c_REF_3 */
    Assert((boolean)(CHECK_GMU_BASE(pGmu)));
#endif
    /* SDK_GMU_Deviation_Rule7_2:1281:pony add for QAC */
    return (pGmu->SPSTS & GMU_SLEEP_STATUS_DEF_MASK);
}

/* #Violation: gmu_hal_c_REF_1 */
GMU_ResultStatus GMU_Hal_SetSleepMode(GMU_MODULE *const pGmu, const GMU_SleepCfg *const pConfig)
{
    GMU_ResultStatus bRetVal;
    uint32 enable;
    boolean retSts;
    retSts = TRUE;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pSaradc is null pointer */
    /* Check GMU base address */
    /* #Violation: gmu_hal_c_REF_2 */
    /* #Violation: gmu_hal_c_REF_3 */
    Assert((boolean)(CHECK_GMU_BASE(pGmu)));
    /* #Violation: gmu_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pConfig));
#endif
    bRetVal = GMU_STATUS_OK;
    enable = pGmu->SPMCTRL1;
    /* Sleep group is GMU group0 */
    if(pConfig->uGroup == GMU_SPM_GROUP0)
    {
        enable = (enable & ~GMU_GROUP0_SLEEP_MODE_EN_MASK);
        enable = enable | (uint32)(pConfig->uSleepEnable);
    }
    /* Sleep group is GMU group1 */
    else if(pConfig->uGroup == GMU_SPM_GROUP1)
    {
        enable = (enable & ~GMU_GROUP1_SLEEP_MODE_EN_MASK);
        enable = enable | ((uint32)pConfig->uSleepEnable << 2U);
    }
#if defined(THA6_THA6104) || defined(THA6_THA6206) || defined(THA6_THA6206D)
    /* Sleep group is GMU group2 */
    else if(pConfig->uGroup == GMU_SPM_GROUP2)  /* THA6412 haven't the GMU_SPM_GROUP2, THA6206, THA6104 has this group */
    {
        enable = (enable & ~GMU_GROUP2_SLEEP_MODE_EN_MASK);
        enable = enable | ((uint32)pConfig->uSleepEnable << 4U);
    }
#endif /* end THA6_THA6104 and THA6_THA6206 || THA6_THA6206D */
#if defined(THA6_THA6206) || defined(THA6_THA6206D)
    /* Sleep group is GMU group3 */
    else if(pConfig->uGroup == GMU_SPM_GROUP3) /* THA6412, THA6104 haven't the GMU_SPM_GROUP3, THA6206 has this group */
    {
        enable = (enable & ~GMU_GROUP3_SLEEP_MODE_EN_MASK);
        enable = enable | ((uint32)pConfig->uSleepEnable << 6U);
    }
#endif /* end THA6_THA6206 || THA6_THA6206D */    
    /* Input parameter error */
    else
    {
        bRetVal = GMU_STATUS_INPUT_PARAM_ERROR;
    }
    /* The input GMU group is in the range */
    if(bRetVal == GMU_STATUS_OK)
    {   
        /* Disable all interupt */
        DISABLE_ALL_INTERRUPTS();
        /* Clear cpuwdt ENDINIT */
        retSts &= Cpuwdt_Hal_ClearEndinit();
        pGmu->SPMCTRL0 = (uint32)0x0U;
        /* Register readback check */
        retSts = Gmu_Register_ReadBack_Check(retSts, pGmu->SPMCTRL0, 0x0U);
        pGmu->SPMCTRL1 = (uint32)(enable & (uint32)GMU_SLEEP_MODE_EN_MASK);
        /* Register readback check */
        retSts = Gmu_Register_ReadBack_Check(retSts, pGmu->SPMCTRL1, (enable & (uint32)GMU_SLEEP_MODE_EN_MASK));
        /* Set cpuwdt ENDINIT */
        retSts &=Cpuwdt_Hal_SetEndinit();
        /* Enable all interrupt */
        ENABLE_ALL_INTERRUPTS();
        /* Status is false */
        if(FALSE == retSts)
        {
            bRetVal = GMU_STATUS_FAILED;
        }
        /*set the default sleep mode as SBE*/
    }
    
    return bRetVal;
}


#if defined (THA6_THA6412)
/* This function is avaliable in THA6412, disavaliable in THA6206 and THA6104. 
 * Bescuse there are no register MENCFG0 in THA6206 and THA6104 */ 
/* #Violation: gmu_hal_c_REF_1 */
boolean GMU_Hal_SetMemBufConfig(GMU_MODULE *const pGmu, const GMU_MemBufCfg *const pConfig)
{
    uint32 memcfgf;
    uint32 memcfgs;
    boolean retSts;
    retSts = TRUE;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pSaradc is null pointer */
    /* Check GMU base address */
    /* #Violation: gmu_hal_c_REF_2 */
    /* #Violation: gmu_hal_c_REF_3 */
    Assert((boolean)(CHECK_GMU_BASE(pGmu)));
    /* Check the input parameter is not pointer */
    /* #Violation: gmu_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pConfig));
#endif

    memcfgf = pGmu->MEMCFG0;
    memcfgs = pGmu->MEMCFG1;

    memcfgf = (memcfgf & ~GMU_READ_BUFFER_EN_MASK);
    
    memcfgf |= (pConfig->readBufEnable == TRUE) ? (uint32)GMU_READ_BUFFER_EN : 0U;

    memcfgf = (memcfgf & ~GMU_READ_BUFFER_PERMISSION_MASK);
    memcfgf |= pConfig->readBufPermission & GMU_READ_BUFFER_PERMISSION_MASK;

    memcfgf = (memcfgf & ~GMU_READ_BUFFER_START_ADD_MASK);
    memcfgf |= (pConfig->readBufStartAddress >> 4) & GMU_READ_BUFFER_START_ADD_MASK;

    memcfgf = (memcfgf & ~GMU_READ_BUFFER_END_ADD_MASK);
    memcfgf |= (pConfig->readBufEndAddress << 9) & GMU_READ_BUFFER_END_ADD_MASK;

    memcfgs = (memcfgs & ~GMU_RMW_BUFFER_EN_MASK);
    memcfgs |= (pConfig->rmwBufEnable == TRUE) ? (uint32)GMU_RMW_BUFFER_EN : 0U;
    /* Disable all interrupt */
    DISABLE_ALL_INTERRUPTS();
    /* Clear cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_ClearEndinit();

    pGmu->MEMCFG0 = memcfgf;
    /* Register readback check */
    retSts = Gmu_Register_ReadBack_Check(retSts, pGmu->MEMCFG0, memcfgf);
    pGmu->MEMCFG1 = (memcfgs & GMU_MEM_CONFIG1_DEF_MASK);
    /* Register readback check */
    retSts = Gmu_Register_ReadBack_Check(retSts, pGmu->MEMCFG1, (memcfgs & GMU_MEM_CONFIG1_DEF_MASK));
    /* Set cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_SetEndinit();   
    /* Enable all interrupt */
    ENABLE_ALL_INTERRUPTS(); 

    return retSts;
}

/* This function is avaliable in THA6412, disavaliable in THA6206 and THA6104. 
 * Bescuse there are no register MENCFG0 in THA6206 and THA6104 */ 
/* #Violation: gmu_hal_c_REF_1 */
void GMU_Hal_GetMemBufConfig(const GMU_MODULE *const pGmu, GMU_MemBufCfg *const pConfig)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pSaradc is null pointer */
    /* Check GMU base address */
    /* #Violation: gmu_hal_c_REF_2 */
    /* #Violation: gmu_hal_c_REF_3 */
    Assert((boolean)(CHECK_GMU_BASE(pGmu)));
    /* Check the input parameter is not NULL pointer */
    /* #Violation: gmu_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pConfig));
#endif
    
    pConfig->readBufEnable = ((pGmu->MEMCFG0 & GMU_READ_BUFFER_EN_MASK) == GMU_READ_BUFFER_EN) ? TRUE : FALSE;
    pConfig->readBufPermission = (pGmu->MEMCFG0 & GMU_READ_BUFFER_PERMISSION_MASK);
    pConfig->readBufStartAddress = (pGmu->MEMCFG0 & GMU_READ_BUFFER_START_ADD_MASK);
    pConfig->readBufEndAddress = (pGmu->MEMCFG0 & GMU_READ_BUFFER_END_ADD_MASK) >> 13;
    pConfig->rmwBufEnable = ((pGmu->MEMCFG1 & GMU_RMW_BUFFER_EN_MASK) == GMU_RMW_BUFFER_EN) ? TRUE : FALSE;    
}

#endif

/* #Violation: gmu_hal_c_REF_1 */
boolean GMU_Hal_SetMemConfig(GMU_MODULE *const pGmu, uint32 uMask)
{
    boolean retSts;
    retSts = TRUE;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pSaradc is null pointer */
    /* Check GMU base address */
    /* #Violation: gmu_hal_c_REF_2 */
    /* #Violation: gmu_hal_c_REF_3 */
    Assert((boolean)(CHECK_GMU_BASE(pGmu)));
#endif
    /* Disable all interrupt */
    DISABLE_ALL_INTERRUPTS();
    /* Clear cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_ClearEndinit();
    pGmu->MEMCFG1 = (uMask & GMU_MEM_CONFIG1_DEF_MASK);
    /* Register readback check */
    retSts = Gmu_Register_ReadBack_Check(retSts,  pGmu->MEMCFG1, (uMask & GMU_MEM_CONFIG1_DEF_MASK));
    /* Set cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_SetEndinit();
    /* Enable all interrupt */
    ENABLE_ALL_INTERRUPTS();

 return retSts;
}

/* #Violation: gmu_hal_c_REF_1 */
uint32 GMU_Hal_GetMemConfig(const GMU_MODULE *const pGmu)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pSaradc is null pointer */
    /* Check GMU base address */
    /* #Violation: gmu_hal_c_REF_2 */
    /* #Violation: gmu_hal_c_REF_3 */
    Assert((boolean)(CHECK_GMU_BASE(pGmu)));
#endif
    return (pGmu->MEMCFG1 & GMU_MEM_CONFIG1_DEF_MASK);
}

/* #Violation: gmu_hal_c_REF_1 */
GMU_ResultStatus GMU_Hal_SetProtectRegion(GMU_MODULE *const pGmu, uint32 uIndex, const GMU_RegAttr *const pConfig)
{
    GMU_ResultStatus bRetVal;
    bRetVal = GMU_STATUS_OK;
    boolean retSts;
    retSts = TRUE;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pSaradc is null pointer */
    /* Check GMU base address */
    /* #Violation: gmu_hal_c_REF_2 */
    /* #Violation: gmu_hal_c_REF_3 */
    Assert((boolean)(CHECK_GMU_BASE(pGmu)));
    /* Check the input parameter is not NULL pointer */
    Assert((boolean)((NULL_PTR != pConfig) ? TRUE : FALSE));
#endif
    /* Input parameter is NULL pointer or region more than the max number */
    if((uIndex >= NORMAL_PROTECT_REGION_MAX) || (NULL_PTR == pConfig))
    {
        bRetVal = GMU_STATUS_INPUT_PARAM_ERROR;
    }
    /* These input parameters are in range */
    else
    {
        /* Disable all interrupt */
        DISABLE_ALL_INTERRUPTS();  
        /* Clear safewdt ENDINIT */
        retSts &= Safewdt_Hal_ClearSafetyEndinit();
        pGmu->NRGN[uIndex].RGNACCENW = 0xFFFFFFFFU;
        pGmu->NRGN[uIndex].RGNACCENR = 0xFFFFFFFFU;
        pGmu->NRGN[uIndex].RGNLA = (pConfig->uLowerAddress & GMU_REG_LOW_ADDR_MASK);
        pGmu->NRGN[uIndex].RGNHA = (pConfig->uHigherAddress & GMU_REG_HIGH_ADDR_MASK);
        /* Register readback check */
        retSts = Gmu_Register_ReadBack_Check(retSts, pGmu->NRGN[uIndex].RGNLA, (pConfig->uLowerAddress & GMU_REG_LOW_ADDR_MASK));
        /* Register readback check */
        retSts = Gmu_Register_ReadBack_Check(retSts, pGmu->NRGN[uIndex].RGNHA, (pConfig->uHigherAddress & GMU_REG_HIGH_ADDR_MASK));
        pGmu->NRGN[uIndex].RGNACCENW = pConfig->uWritePermission;
        pGmu->NRGN[uIndex].RGNACCENR = pConfig->uReadPermission;
        /* Register readback check */
        retSts = Gmu_Register_ReadBack_Check(retSts, pGmu->NRGN[uIndex].RGNACCENW, pConfig->uWritePermission);
        /* Register readback check */
        retSts = Gmu_Register_ReadBack_Check(retSts, pGmu->NRGN[uIndex].RGNACCENR, pConfig->uReadPermission);
        /* Set safewdt ENDINIT */
        retSts &= Safewdt_Hal_SetSafetyEndinit();
        /* Enable all interrupt */
        ENABLE_ALL_INTERRUPTS();   
        if (FALSE == retSts)
        {
            bRetVal = GMU_STATUS_INPUT_PARAM_ERROR;
        }
    }
    return bRetVal;
}

/* #Violation: gmu_hal_c_REF_1 */
GMU_ResultStatus GMU_Hal_GetProtectRegion(const GMU_MODULE *const pGmu, uint32 uIndex, GMU_RegAttr *const pConfig)
{
    GMU_ResultStatus bRetVal;
    bRetVal = GMU_STATUS_OK;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pSaradc is null pointer */
    /* Check GMU base address */
    /* #Violation: gmu_hal_c_REF_2 */
    /* #Violation: gmu_hal_c_REF_3 */
    Assert((boolean)(CHECK_GMU_BASE(pGmu)));
    /* Check the input parameter is not NULL pointer */
    Assert((boolean)((NULL_PTR != pConfig) ? TRUE : FALSE));
#endif
    /* Input parameter is NULL pointer or region more than the max number */
    if((uIndex >= NORMAL_PROTECT_REGION_MAX) || (NULL_PTR == pConfig))
    {
        bRetVal = GMU_STATUS_INPUT_PARAM_ERROR;
    }
    /* These input parameters are in range */
    else
    {
        /* SDK_GMU_Deviation_Rule7_2:1281:add for QAC */
        pConfig->uLowerAddress = (pGmu->NRGN[uIndex].RGNLA & GMU_REG_LOW_ADDR_MASK);
        pConfig->uLowerAddress |= GMU_ADDR_MASK;
        pConfig->uHigherAddress = (pGmu->NRGN[uIndex].RGNHA & GMU_REG_HIGH_ADDR_MASK);
        pConfig->uHigherAddress |= GMU_ADDR_MASK;
        pConfig->uWritePermission = (pGmu->NRGN[uIndex].RGNACCENW);
        pConfig->uReadPermission = (pGmu->NRGN[uIndex].RGNACCENR);
    }
    return bRetVal;
}

#define GMU_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gmu_hal_c_REF_6 */
#include "Gmu_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
