/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    gtm_cmu_std.h
 * Author:      01031
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all the data type definitions for the CMU module.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #gtm_cmu_std_h_REF_1:MISRAC2012-Rule-2.5;
* Justification: May be used in other scenarios.
*
* #gtm_cmu_std_h_REF_2:MISRAC2012-Rule-2.3;
* Justification: The members of the type are used in configuration-gererated code.
*
* #gtm_cmu_std_h_REF_3:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
* #gtm_cmu_std_h_REF_4:MISRAC2012-Rule-19.2;
* Justification: Necessary union type for bitwise access to register. Data integrity and correctness will be ensured 
*                by code review.
*
* #gtm_cmu_std_h_REF_5:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
* #gtm_cmu_std_h_REF_6:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #gtm_cmu_std_h_REF_7:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*/
#ifndef GTM_CMU_STD_H_
#define GTM_CMU_STD_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "gtm_register.h"
#include "gtm.h"
#include "compilertypes.h"
#include "Platform_Types.h"
#include "tha6_cfg.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* Mask for CMU_CLK_EN register (Enable): ALL clocks */
#define GTM_DISABLE_ALL_CMU_CLK (0x555555U)

#define  GTM_CMU_CLK_ENABLE      (2U)  /* 0b10 = enable clock signal */

#define  GTM_CMU_EN_ECLK0_POS   (16U) /* The position of enable ECLK 0 generation sub-unit */
#define  GTM_CMU_EN_ECLK1_POS   (18U) /* The position of enable ECLK 1 generation sub-unit */
#define  GTM_CMU_EN_ECLK2_POS   (20U) /* The position of enable ECLK 2 generation sub-unit */
#define  GTM_CMU_EN_FXCLK_POS   (22U) /* The position of enable all CMU_FXCLK */

/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* CMU configurable clock source selection */
typedef enum
{
    GTM_CMU_CLK_SRC_GCLK = 0U,    /* CMU global clock */
    GTM_CMU_CLK_SRC_ECLK1        /* CMU external clock */
} Gtm_Cmu_Clk_Src;

/* CMU fixed clock input selection */
typedef enum
{
    GTM_CMU_GCLK_EN = 0U,    /* GTM_CMU_GCLK_EN as FXCLK input */
    GTM_CMU_CLK0,            /* GTM_CMU_CLK0 as FXCLK input */
    GTM_CMU_CLK1,            /* GTM_CMU_CLK1 as FXCLK input */
    GTM_CMU_CLK2,            /* GTM_CMU_CLK2 as FXCLK input */
    GTM_CMU_CLK3,            /* GTM_CMU_CLK3 as FXCLK input */
    GTM_CMU_CLK4,            /* GTM_CMU_CLK4 as FXCLK input */
    GTM_CMU_CLK5,            /* GTM_CMU_CLK5 as FXCLK input */
    GTM_CMU_CLK6,            /* GTM_CMU_CLK6 as FXCLK input */
    GTM_CMU_CLK7             /* GTM_CMU_CLK7 as FXCLK input */
} Gtm_Cmu_Fxclk_Src;

/* GTM cluster clock control */
typedef enum
{
    GTM_CLUSTER_CLK_DISABLE = 0U,        /* Cluster clock disable */
    GTM_CLUSTER_CLK_INVALIDCLKDIVIDER,   /* Cluster clock enable without divider */
    GTM_CLUSTER_CLK_VALIDCLKDIVIDER      /* Cluster clock enable with divider 2 */
} Gtm_Cluster_Clk;

/* CMU configurable clock */
typedef enum
{
    GTM_CMU_CLK_0 = 0U,     /* Cmu configurable clock 0 */
    GTM_CMU_CLK_1,          /* Cmu configurable clock 1 */
    GTM_CMU_CLK_2,          /* Cmu configurable clock 2 */
    GTM_CMU_CLK_3,          /* Cmu configurable clock 3 */
    GTM_CMU_CLK_4,          /* Cmu configurable clock 4 */
    GTM_CMU_CLK_5,          /* Cmu configurable clock 5 */
    GTM_CMU_CLK_6,          /* Cmu configurable clock 6 */
    GTM_CMU_CLK_7           /* Cmu configurable clock 7 */
} Gtm_Cmu_Clk;

/* CMU external clock */
typedef enum
{
    GTM_CMU_ECLK_0 = 0U,    /* CMU external clock 0 */
    GTM_CMU_ECLK_1,         /* CMU external clock 1 */
    GTM_CMU_ECLK_2          /* CMU external clock 2 */
/* #Violation: gtm_cmu_std_h_REF_2 */
} Gtm_Cmu_Eclk;

/* CMU fixed clock */
typedef enum
{
    GTM_CMU_FXCLK_0 = 0U,   /* CMU fixed clock 0 */
    GTM_CMU_FXCLK_1,        /* CMU fixed clock 1 */
    GTM_CMU_FXCLK_2,        /* CMU fixed clock 2 */
    GTM_CMU_FXCLK_3,        /* CMU fixed clock 3 */
    GTM_CMU_FXCLK_4         /* CMU fixed clock 4 */
/* #Violation: gtm_cmu_std_h_REF_2 */
} Gtm_Cmu_Fxclk;

/* TIM filter counter frequency selection */
typedef enum
{
    GTM_CMU_TIM_FILTER_CLK_0 = 0U,  /* FLT_CNT counts with CMU_CLK0 */
    GTM_CMU_TIM_FILTER_CLK_1,       /* FLT_CNT counts with CMU_CLK1 */
    GTM_CMU_TIM_FILTER_CLK_6,       /* FLT_CNT counts with CMU_CLK6 */
    GTM_CMU_TIM_FILTER_CLK_7        /* FLT_CNT counts with CMU_CLK7 */
} Gtm_Cmu_Tim_Filter_Clk;


/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* GTM cluster clock configuration */
/* #Violation: gtm_cmu_std_h_REF_5 */
typedef struct
{
    Gtm_Cluster_Clk        cluster0; /* Enable / disable GTM cluster 0 clock */
    Gtm_Cluster_Clk        cluster1; /* Enable / disable GTM cluster 1 clock */
#if defined (THA6_THA6206) || defined(THA6_THA6206D) || defined (THA6_THA6412)
    Gtm_Cluster_Clk        cluster2; /* Enable / disable GTM cluster 2 clock */
    Gtm_Cluster_Clk        cluster3; /* Enable / disable GTM cluster 3 clock */
#endif
#if defined (THA6_THA6412)
    Gtm_Cluster_Clk        cluster4; /* Enable / disable GTM cluster 4 clock */
    Gtm_Cluster_Clk        cluster5; /* Enable / disable GTM cluster 5 clock */
    Gtm_Cluster_Clk        cluster6; /* Enable / disable GTM cluster 6 clock */
    Gtm_Cluster_Clk        cluster7; /* Enable / disable GTM cluster 7 clock */
#endif
} Gtm_Cluster_ClkConfig;
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/* #Violation: gtm_cmu_std_h_REF_7 */
#define GTM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_cmu_std_h_REF_6 */
#include "Gtm_MemMap.h"

/**********************************************************************************************************************
 * Function:     Gtm_Cmu_Std_SetClusterClocks
 * Description:  Set Clusters Clock Divider
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        config: The pointer of cluster Clock divider configuration
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/26    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Cmu_Std_SetClusterClocks(const Gtm_Cluster_ClkConfig *const config);

/**********************************************************************************************************************
 * Function:     Gtm_Cmu_Std_DisableAllClocks
 * Description:  Disable all the CMU clocks
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pCmu: The pointer of CMU object
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/26    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Cmu_Std_DisableAllClocks(GTM_CMU *const pCmu);

/**********************************************************************************************************************
 * Function:     Gtm_Cmu_Std_GetCmuPointer
 * Description:  Gets the CMU pointer
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       GTM_CMU *: The pointer of CMU object
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/26    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE GTM_CMU * Gtm_Cmu_Std_GetCmuPointer(void);

/**********************************************************************************************************************
 * Function:     Gtm_Cmu_Std_SetGlobalNUM
 * Description:  Set the numerator for global clock divider
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pCmu: The pointer of CMU object
 *               num: Numerator for global clock divider
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/26    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Cmu_Std_SetGlobalNUM(GTM_CMU *const pCmu, uint32 num);

/**********************************************************************************************************************
 * Function:     Gtm_Cmu_Std_SetGlobalDEN
 * Description:  Set the denominator for global clock divider
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pCmu: The pointer of CMU object
 *               den: Denominator for global clock divider
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/26    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Cmu_Std_SetGlobalDEN(GTM_CMU *const pCmu, uint32 den);

/**********************************************************************************************************************
 * Function:     Gtm_Cmu_Std_SetECLKDivider
 * Description:  Set the numerator and denominator for external clock divider
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pCmu: The pointer of CMU object
 *               index: The external clock index(0~2)
 *               num: Denominator for external clock divider
 *               den: Denominator for external clock divider
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/26    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Cmu_Std_SetECLKDivider(GTM_CMU *const pCmu, uint8 index, uint32 num, uint32 den);

/**********************************************************************************************************************
 * Function:     Gtm_Cmu_Std_SetCLKDivider
 * Description:  Set the count value for the clock divider
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pCmu: The pointer of CMU object
 *               index: The external clock index(0~7)
 *               divider: Defines count value for the clock divider
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/26    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Cmu_Std_SetCLKDivider(GTM_CMU *const pCmu, uint8 index, uint32 divider);

/**********************************************************************************************************************
 * Function:     Gtm_Cmu_Std_SetFXCLKSelection
 * Description:  Set the clock selection for FXCLK
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pCmu: The pointer of CMU object
 *               sel: Input clock selection for FXCLK
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/26    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Cmu_Std_SetFXCLKSelection(GTM_CMU *const pCmu, uint8 sel);


/**********************************************************************************************************************
 * Function:     Gtm_Cmu_Std_SetClockCtrl
 * Description:  Set CMU control for clock resolution generator
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pCmu: The pointer of CMU object
 *               clkCtrl: CMU control for clock resolution generator register value
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/27    01177     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Cmu_Std_SetClockCtrl(GTM_CMU *const pCmu, uint32 clkCtrl);

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Cmu_Std_SetClusterClocks(const Gtm_Cluster_ClkConfig *const config)
{
    /* #Violation: gtm_cmu_std_h_REF_4 */
    GTM_CLS_CLK_CFG        clsConfig;
    boolean ret;
    ret = TRUE;

    /* #Violation: gtm_cmu_std_h_REF_3 */
    clsConfig.U = GTM_HAL->GTM_CLUSTER[0].CLS_CLK_CFG.U;
    clsConfig.B.CLS0_CLK_DIV = (uint32)config->cluster0;
    clsConfig.B.CLS1_CLK_DIV = (uint32)config->cluster1;
#if defined (THA6_THA6206) || defined(THA6_THA6206D) || defined (THA6_THA6412)
    clsConfig.B.CLS2_CLK_DIV = (uint32)config->cluster2;
    clsConfig.B.CLS3_CLK_DIV = (uint32)config->cluster3;
#endif
#if defined(THA6_THA6412)
    clsConfig.B.CLS4_CLK_DIV = (uint32)config->cluster4;
    clsConfig.B.CLS5_CLK_DIV = (uint32)config->cluster5;
    clsConfig.B.CLS6_CLK_DIV = (uint32)config->cluster6;
    clsConfig.B.CLS7_CLK_DIV = (uint32)config->cluster7;
#endif

    /* Clear this bit to allow writing protected register */
    /* #Violation: gtm_cmu_std_h_REF_3 */
    GTM_HAL->GTM_CLUSTER[0].CTRL.B.RF_PROT = 0U;
    /* #Violation: gtm_cmu_std_h_REF_3 */
    GTM_HAL->GTM_CLUSTER[0].CLS_CLK_CFG.U  = clsConfig.U;
    /* #Violation: gtm_cmu_std_h_REF_3 */
    GTM_HAL->GTM_CLUSTER[0].CTRL.B.RF_PROT = 1U;
    /* #Violation: gtm_cmu_std_h_REF_3 */
    ret = Gtm_Register_ReadBack_Check(ret, clsConfig.U, GTM_HAL->GTM_CLUSTER[0].CLS_CLK_CFG.U);
    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Cmu_Std_DisableAllClocks(GTM_CMU *const pCmu)
{
    boolean ret;

    ret = TRUE;
    pCmu->CLK_EN.U = GTM_DISABLE_ALL_CMU_CLK;

    ret = Gtm_Register_ReadBack_Check(ret, 0U, pCmu->CLK_EN.U);

    return ret;
}

LOCAL_FORCEINLINE GTM_CMU * Gtm_Cmu_Std_GetCmuPointer(void)
{
    /* #Violation: gtm_cmu_std_h_REF_3 */
    return (GTM_CMU *)&GTM_HAL->GTM_CLUSTER[0].CMU;
}

LOCAL_FORCEINLINE boolean Gtm_Cmu_Std_SetGlobalNUM(GTM_CMU *const pCmu, uint32 num)
{
    boolean ret;

    ret = TRUE;
    pCmu->GCLK_NUM.B.GCLK_NUM = num;

    ret = Gtm_Register_ReadBack_Check(ret, num, pCmu->GCLK_NUM.B.GCLK_NUM);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Cmu_Std_SetGlobalDEN(GTM_CMU *const pCmu, uint32 den)
{
    boolean ret;

    ret = TRUE;
    pCmu->GCLK_DEN.B.GCLK_DEN = den;

    ret = Gtm_Register_ReadBack_Check(ret, den, pCmu->GCLK_DEN.B.GCLK_DEN);
    
    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Cmu_Std_SetECLKDivider(GTM_CMU *const pCmu, uint8 index, uint32 num, uint32 den)
{
    boolean ret;

    ret = TRUE;
    pCmu->ECLK[index].NUM.B.ECLK_NUM = num;
    pCmu->ECLK[index].DEN.B.ECLK_DEN = den;

    ret = Gtm_Register_ReadBack_Check(ret, num, pCmu->ECLK[index].NUM.B.ECLK_NUM);
    ret = Gtm_Register_ReadBack_Check(ret, den, pCmu->ECLK[index].DEN.B.ECLK_DEN);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Cmu_Std_SetCLKDivider(GTM_CMU *const pCmu, uint8 index, uint32 divider)
{
    boolean ret;

    ret = TRUE;
    pCmu->CLK[index].CTRL.B.CLK_CNT = divider;

    ret = Gtm_Register_ReadBack_Check(ret, divider, pCmu->CLK[index].CTRL.B.CLK_CNT);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Cmu_Std_SetFXCLKSelection(GTM_CMU *const pCmu, uint8 sel)
{
    boolean ret;

    ret = TRUE;
    pCmu->FXCLK.CTRL.B.FXCLK_SEL = sel;

    ret = Gtm_Register_ReadBack_Check(ret, sel, pCmu->FXCLK.CTRL.B.FXCLK_SEL);

    return ret;
}


LOCAL_FORCEINLINE boolean Gtm_Cmu_Std_SetClockCtrl(GTM_CMU *const pCmu, uint32 clkCtrl)
{
    boolean ret;

    ret = TRUE;
    pCmu->CLK_CTRL.U = clkCtrl;

    ret = Gtm_Register_ReadBack_Check(ret, clkCtrl, pCmu->CLK_CTRL.U);

    return ret;
}

/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/

 /* #Violation: gtm_cmu_std_h_REF_7 */
#define GTM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_cmu_std_h_REF_6 */
#include "Gtm_MemMap.h"
#endif /* GTM_CMU_STD_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
