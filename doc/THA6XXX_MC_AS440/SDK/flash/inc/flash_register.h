/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:  flash_register.h
 * Author:    00393
 * Version:   V1.2.0
 * Date:      2026/02/28
 * Description: This file contains all definitions of Flash module registers
 *********************************************************************************************************************/
/*
 *#Violation Summary
 *
 *#flash_register_h_REF_1:MISRAC2012-Rule-2.5;
 * Justification: The macros are reserved for upper layers.
 *
 *#flash_register_h_REF_2:MISRAC2012-Rule-2.3;
 * Justification: The members of the type are used in configuration-generated code.
 *
 *#flash_register_h_REF_3:MISRAC2012-Dir-4.8;
 * Justification: Apply such struct/union definitons to simplify the code structure and reduce the code
 *                complexity.
 * 
 *#flash_register_h_REF_4:DCL12-C;
 * Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity;
 */

#ifndef FLASH_REGISTER_H_
#define FLASH_REGISTER_H_

/**********************************************************************************************************************
 *                                                Includes
 *********************************************************************************************************************/
#include "regtypes.h"
#include "tha6_cfg.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/

/************************************** Control Register Start************************/
/* FLASH_DFCON register */
/* #Violation: flash_register_h_REF_1 */
#define DFCON_RDT_POS (0U)
#define DFCON_STO0_POS (8U)
#define DFCON_STO1_POS (16U)
#define DFCON_CLKDIV_POS (24U)

/* FLASH_PFCON register */
/* #Violation: flash_register_h_REF_1 */
#define PFCON_RDT_POS (0U)
#define PFCON_STO0_POS (8U)
#define PFCON_STO1_POS (16U)
#define PFCON_CLKDIV_POS (24U)

/* FLASH_DFLASH_CTR0 */
/* #Violation: flash_register_h_REF_1 */
#define FLASH_DFLASH_CTR0_MODE_POS (0U)

/* FLASH_DFLASH_CTR1 */
/* #Violation: flash_register_h_REF_1 */
#define FLASH_DFLASH_CTR1_BUFEN_POS (0U)

/************************************** Control Register End************************/

/************************************** Status Register Start************************/
/* #Violation: flash_register_h_REF_1 */
#define FLASH_DFLASH_STS_CF_POS (8U)

/************************************** Status Register End************************/

/************************************** DF Control Register Start************************/
/* FLASH_DFLASH_CTR5 register */
/* #Violation: flash_register_h_REF_1 */
#define FLASH_DFLASH_CTR5_ECEN_POS (0U)
#define FLASH_DFLASH_CTR5_ECLEN_POS (2U)

/* FLASH_DF0_ECCCTR */
/* #Violation: flash_register_h_REF_1 */
#define DF0_ECCCTR_ECCEEN_POS (0U)
/* #Violation: flash_register_h_REF_1 */
#define DF0_ECCCTR_ECCDEN_POS (2U)

/************************************** DF Control Register End************************/

/************************************** PF Control Register Start************************/
/* FLASH_PF_CTR5 register */
/* #Violation: flash_register_h_REF_1 */
#define PF_CTR5_ECEN_POS (0U)
#define PF_CTR5_ECLEN_POS (2U)

/* FLASH_PF_ECCCTR */
/* #Violation: flash_register_h_REF_1 */
#define PF_ECCCTR_ECCEEN_POS (0U)
/* #Violation: flash_register_h_REF_1 */
#define PF_ECCCTR_ECCDEN_POS (2U)

/************************************** PF Control Register End************************/

/************************************** Alarm Register Start************************/

/************************************** Alarm Register End************************/

/************************************** DF Control Register End************************/
#define FLASH_WR_NUMBER 2
#define FLASH_PASSWORD_NUMBER 8
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/

typedef volatile struct
{
    ureg32 IDR;           /* Control id */
    ureg32 DFCON;         /* Control register */
    ureg32 PFCON;         /* Control register */
    ureg32 reserved_C[5]; /* Internal reserved */
    ureg32 SWAPCON;       /* Control register */
} FLASH_COMMON_CTR_MODULE;

/* FLASH alarm mask register structure */
typedef volatile struct
{
    ureg32 PRTMSKINT; /* Mask interrupt register */
    ureg32 SAMSKALM;  /* Mask alarm error register */
    ureg32 SAMSKBE;   /* Mask bus error register */
/* #Violation: flash_register_h_REF_2 */
} FLASH_COMMON_MSK_MODULE;

/* FLASH status register structure */
typedef volatile struct
{
    ureg32 PRTSTS;   /* Status register */
    ureg32 SASTS;    /* Safe status register */
    ureg32 EPRSTSTS; /* Erase/Program Break by Reset Status Register */
    ureg32 RDTSTS;   /* Read Delay Time Switch Status Register */
} FLASH_COMMON_STS_MODULE;

/* FLASH NVR MPU register structure */
typedef volatile struct
{
    ureg32 NVREWMPU;   /* NVR erase write register */
    ureg32 NVRRMPU;    /* NVR read register register */
}FLASH_COMMON_NVRMPU_MODULE;

/* FLASH pflash buffer config register structure */
#if defined(THA6_THA6412) || defined(THA6_THA6104)
/* #Violation: flash_register_h_REF_3 */
typedef volatile struct
{
    ureg32 PF0BUFCFG; /* Status register, for Chip THA6412 and THA6104 */
    ureg32 PF1BUFCFG; /* Safe status register, for Chip THA6412 and THA6104 */
} FLASH_COMMON_BUFCFG_MODULE;
#endif
/* FLASH boot rom mode register structure */

typedef volatile struct
{
    ureg32 BRM_MODE;     /* Boot rom mode register, THA6104 not contain */
    ureg32 BRM_FIT;      /* Fault Injection Test register*/
    ureg32 RES0[62];     /*Reserved*/
    ureg32 BRM_SAMSKALM; /* Mask Alarm Error Register*/
    ureg32 BRM_SAMSKBE;  /* Mask Bus Error Register*/
    ureg32 RES1[62];     /*Reserved*/
    ureg32 BRM_SASTS;    /* Safe Status Register*/
    ureg32 BRM_STS;      /* Status Register, THA6104 not contain */
/* #Violation: flash_register_h_REF_2 */
} FLASH_COMMON_BROMCFG_MODULE;

/* FLASH controller register structure */
typedef volatile struct
{
    ureg32 CTR0;   /* Control register */
    ureg32 CTR1;   /* Control register */
    ureg32 RESERVED;   /* RESERVED */
    ureg32 CTR3;   /* Control register */
    ureg32 CTR4;   /* Control register */
    ureg32 CTR5;   /* Control register */
    ureg32 CTR6;   /* Control register */
    ureg32 CTR7;   /* Control register */
    ureg32 CTR8;   /* Control register */
    ureg32 RES[3]; /* Internal reserved */
    ureg32 FIT0;   /* Fault injection test register */
    ureg32 FIT1;   /* Fault injection test register */
    ureg32 FIT2;   /* Fault injection test register */
    ureg32 ECCCTR; /* Ecc control register */
    ureg32 ECCTESTCTR; /* Ecc test control register */
    ureg32 ECCDATCTR;  /* Ecc test data register for THA6206 and THA6412 */
    ureg32 BUFFIT0;     /* Buffer Fault injection test register for THA6412 and THA6104 */
    ureg32 RES1[1];     /* Internal reserved */
    ureg32 ECCTESTDAT0; /* Ecc test data 0 register for THA6104 */
    ureg32 ECCTESTDAT1; /* Ecc test data 1 register for THA6104 */
    ureg32 ECCTESTDAT2; /* Ecc test data 2 register for THA6104 */
    ureg32 ECCTESTDAT3; /* Ecc test data 3 register for THA6104 */

} FLASH_CTR_MODULE;

/* FLASH alarm mask register structure */
typedef volatile struct
{
    ureg32 MSKINT;    /* Mask interrupt register */
    ureg32 SAMSKALM0; /* Mask alarm/bus error register */
    ureg32 SAMSKBE0;  /* Mask alarm/bus error register */
    ureg32 SAMSKALM1; /* Mask alarm/bus error register */
    ureg32 SAMSKBE1;  /* Mask alarm/bus error register */
} FLASH_MSK_MODULE;

/* FLASH Safe Status  register structure */
typedef volatile struct
{
    ureg32 STS;    /* Status register */
    ureg32 SASTS0; /* Safe status register */
    ureg32 SASTS1; /* Safe status register */
} FLASH_STS_MODULE;

/* FLASH error information register structure */
typedef volatile struct
{
    ureg32 SAINF0; /* Information register 0 */
    ureg32 SAINF1; /* Information register 1 */
    ureg32 SAINF2; /* Information register 2 */
    ureg32 SAINF3; /* Information register 3 */
    ureg32 SAINF4; /* Information register 4 */
    ureg32 SAINF5; /* Information register 5 */
    ureg32 RESERVED18[6]; /* Internal reserved */
    ureg32 BUFSIGN; /* Buffer error information for THA6412 and THA6104 */
    ureg32 RESERVED34[3]; /* Internal reserved for THA6412 and THA6104 */
    ureg32 PBHITCNT; /* PBuffer hit counter for THA6412 and THA6104 */
    ureg32 CDBHITCNT; /* CDBuffer hit counter for THA6412 and THA6104 */
    ureg32 READCNT; /* Read counter for THA6412 and THA6104 */
    ureg32 CNTCLR; /* Clear counter for THA6412 and THA6104 */
/* #Violation: flash_register_h_REF_2 */
}FLASH_SAINF_MODULE;

/* Flash SSU register structure */
typedef volatile struct
{
    ureg32 Wr[FLASH_WR_NUMBER];             /* Write SSU register */
    ureg32 RESERVED_10408[2]; /* Internal reserved */
    ureg32 Rd;                /* Read SSU register */
} FLASH_SSU_MODULE;

/* Flash pin register structure */
typedef volatile struct
{
    ureg32 DFPIN[FLASH_PASSWORD_NUMBER];     /* 0x28000 - Dflash password register */
    ureg32 PFPIN[FLASH_PASSWORD_NUMBER];     /* 0x28020 - Pflash password register */
    ureg32 NVRBSPIN[8];  /* 0x28040 - NVR BS region password register */
    ureg32 NVRCFGPIN[8]; /* 0x28060 - NVR CFG password register */
} FLASH_PININPUT_MODULE;


/*--------------------------------------------------- FLASH Address ---------------------------------------------------*/
/* FLASH Offset */
/* Common register offset */
#define FLASH_COMMON_CTR_OFFSET (0x00000000U) /* FLASH common control register */
/* #Violation: flash_register_h_REF_1 */
#define FLASH_COMMON_MSK_OFFSET (0x00000100U) /* FLASH common alarm mask register */
#define FLASH_COMMON_STS_OFFSET (0x00000200U) /* FLASH common status register */
#define FLASH_COMMON_NVRMPU_OFFSET (0x00000400U) /* FLASH common NVR MPU register */
/* #Violation: flash_register_h_REF_1 */
#define FLASH_COMMON_PF0BUFCFG_OFFSET (0x00000210U) /* PFLASH0 buffer configuration, for Chip THA6412 */
/* #Violation: flash_register_h_REF_1 */
#define FLASH_COMMON_PF1BUFCFG_OFFSET (0x00000214U) /* PFLASH1 buffer configuration, for Chip THA6412 */

/* Flash register offset */
#define FLASH_DFLASH_REG_OFFSET (0x00008000U)  /* DFLASH0 register */
#define FLASH_PFLASH0_REG_OFFSET (0x00010000U) /* PFLASH0 register */
#define FLASH_PFLASH1_REG_OFFSET (0x00011000U) /* PFLASH1 register */
/* #Violation: flash_register_h_REF_1 */
#define FLASH_PFLASH2_REG_OFFSET (0x00010000U) /* PFLASH2 register, for Chip THA6412 */
/* #Violation: flash_register_h_REF_1 */
#define FLASH_PFLASH3_REG_OFFSET (0x00011000U) /* PFLASH3 register, for Chip THA6412 */
#define FLASH_PIN_INPUT_OFFSET (0x00028000U)   /* FLASH pin input register */

/*General register offset*/
#define FLASH_CTR_OFFSET (0x00000000U) /* FLASH control register */
/* #Violation: flash_register_h_REF_1 */
#define FLASH_MSK_OFFSET (0x00000100U) /* FLASH alarm mask register */
#define FLASH_STS_OFFSET (0x00000200U) /* FLASH status register */
#define FLASH_SAINF_OFFSET (0x00000300U) /* FLASH error information register */
#define FLASH_SSU_OFFSET (0x00000400U) /* FLASH ssu register */

/* FLASH General region common register address */
#define FLASH_CLUSTER0_CTR_ADRESS (FLASH_CLUSTER0_BASE_ADDRESS + FLASH_COMMON_CTR_OFFSET) /* Common control*/
#define FLASH_CLUSTER0_CTR ((FLASH_COMMON_CTR_MODULE *)FLASH_CLUSTER0_CTR_ADRESS)         /* FLASH cluster0 control object */
#define FLASH_CLUSTER0_STS ((FLASH_COMMON_STS_MODULE *)(FLASH_CLUSTER0_BASE_ADDRESS + FLASH_COMMON_STS_OFFSET))
#define FLASH_CLUSTER0_NVRMPU ((FLASH_COMMON_NVRMPU_MODULE *)(FLASH_CLUSTER0_BASE_ADDRESS + FLASH_COMMON_NVRMPU_OFFSET))

#if defined(THA6_THA6412) || defined(THA6_THA6104)
/* #Violation: flash_register_h_REF_1 */
#define FLASH_CLUSTER0_BUFCFG ((FLASH_COMMON_BUFCFG_MODULE *)(FLASH_CLUSTER0_BASE_ADDRESS + FLASH_COMMON_PF0BUFCFG_OFFSET))
#endif
#define FLASH_CLUSTER0_PININPUT ((FLASH_PININPUT_MODULE *)(FLASH_CLUSTER0_BASE_ADDRESS + FLASH_PIN_INPUT_OFFSET))

#if defined(THA6_THA6412)
#define FLASH_CLUSTER1_CTR_ADRESS (FLASH_CLUSTER1_BASE_ADDRESS + FLASH_COMMON_CTR_OFFSET) /* Common control*/
#define FLASH_CLUSTER1_CTR ((FLASH_COMMON_CTR_MODULE *)FLASH_CLUSTER1_CTR_ADRESS)         /* FLASH cluster1 control object */
#define FLASH_CLUSTER1_STS ((FLASH_COMMON_STS_MODULE *)(FLASH_CLUSTER1_BASE_ADDRESS + FLASH_COMMON_STS_OFFSET))
/* #Violation: flash_register_h_REF_1 */
#define FLASH_CLUSTER1_BUFCFG ((FLASH_COMMON_BUFCFG_MODULE *)(FLASH_CLUSTER1_BASE_ADDRESS + FLASH_COMMON_PF0BUFCFG_OFFSET))
/* #Violation: flash_register_h_REF_1 */
#define FLASH_CLUSTER1_PININPUT ((FLASH_PININPUT_MODULE *)(FLASH_CLUSTER1_BASE_ADDRESS + FLASH_PIN_INPUT_OFFSET))
#endif /* defined(THA6_THA6412) */

/* General region data DFLASH0 register address */
#define FLASH_DFLASH_REG_ADDRESS (FLASH_CLUSTER0_BASE_ADDRESS + FLASH_DFLASH_REG_OFFSET) /* DFLASH0 */
/* #Violation: flash_register_h_REF_1 */
#define FLASH_DFLASH_CTR_ADDRESS (FLASH_DFLASH_REG_ADDRESS + FLASH_CTR_OFFSET) /* DFLASH0 control*/
/* #Violation: flash_register_h_REF_1 */
#define FLASH_DFLASH_CTR ((FLASH_CTR_MODULE *)FLASH_DFLASH_CTR_ADDRESS) /* DFLASH control object */
/* #Violation: flash_register_h_REF_1 */
#define FLASH_DFLASH_MSK ((FLASH_MSK_MODULE *)(FLASH_DFLASH_REG_ADDRESS + FLASH_MSK_OFFSET)) /* DFLASH mask object */
/* #Violation: flash_register_h_REF_1 */
#define FLASH_DFLASH_STS ((FLASH_STS_MODULE *)(FLASH_DFLASH_REG_ADDRESS + FLASH_STS_OFFSET)) /* DFLASH status object */
#define FLASH_DFLASH_SSU ((FLASH_SSU_MODULE *)(FLASH_DFLASH_REG_ADDRESS + FLASH_SSU_OFFSET)) /* DFLASH status object */
/* #Violation: flash_register_h_REF_1 */
#define FLASH_DFLASH_SAINF ((FLASH_SAINF_MODULE *)(FLASH_DFLASH_REG_ADDRESS + FLASH_SAINF_OFFSET)) /* DFLASH status object */

/* PFLASH0 register address */
#define FLASH_PFLASH0_REG_ADDRESS (FLASH_CLUSTER0_BASE_ADDRESS + FLASH_PFLASH0_REG_OFFSET) /* PFLASH0  */
#define FLASH_PF0_CTR_ADDRESS (FLASH_PFLASH0_REG_ADDRESS + FLASH_CTR_OFFSET)               /* PFLASH0 control */
#define FLASH_PFLASH0_CTR ((FLASH_CTR_MODULE *)FLASH_PF0_CTR_ADDRESS)                      /* PFLASH0 control object */
/* #Violation: flash_register_h_REF_1 */
#define FLASH_PFLASH0_MSK ((FLASH_MSK_MODULE *)(FLASH_PFLASH0_REG_ADDRESS + FLASH_MSK_OFFSET)) /* PFLASH0 mask object */
#define FLASH_PFLASH0_STS ((FLASH_STS_MODULE *)(FLASH_PFLASH0_REG_ADDRESS + FLASH_STS_OFFSET)) /* PFLASH0 status object */
/* #Violation: flash_register_h_REF_1 */
#define FLASH_PFLASH0_SSU ((FLASH_SSU_MODULE *)(FLASH_PFLASH0_REG_ADDRESS + FLASH_SSU_OFFSET)) /* PFLASH0 status object */
/* #Violation: flash_register_h_REF_1 */
#define FLASH_PFLASH0_SAINF ((FLASH_SAINF_MODULE *)(FLASH_PFLASH0_REG_ADDRESS + FLASH_SAINF_OFFSET)) /* PFLASH0 status object */

/* PFLASH1 register address */
#define FLASH_PFLASH1_REG_ADDRESS (FLASH_CLUSTER0_BASE_ADDRESS + FLASH_PFLASH1_REG_OFFSET) /* PFLASH1*/
#define FLASH_PF1_CTR_ADDRESS (FLASH_PFLASH1_REG_ADDRESS + FLASH_CTR_OFFSET)               /* PFLASH1 control*/
#define FLASH_PFLASH1_CTR ((FLASH_CTR_MODULE *)FLASH_PF1_CTR_ADDRESS)                      /* PFLASH1 control object */
/* #Violation: flash_register_h_REF_1 */
#define FLASH_PFLASH1_MSK ((FLASH_MSK_MODULE *)(FLASH_PFLASH1_REG_ADDRESS + FLASH_MSK_OFFSET)) /* PFLASH1 mask object */
#define FLASH_PFLASH1_STS ((FLASH_STS_MODULE *)(FLASH_PFLASH1_REG_ADDRESS + FLASH_STS_OFFSET)) /* PFLASH1 status object */
/* #Violation: flash_register_h_REF_1 */
#define FLASH_PFLASH1_SSU ((FLASH_SSU_MODULE *)(FLASH_PFLASH1_REG_ADDRESS + FLASH_SSU_OFFSET)) /* PFLASH1 status object */
/* #Violation: flash_register_h_REF_1 */
#define FLASH_PFLASH1_SAINF ((FLASH_SAINF_MODULE *)(FLASH_PFLASH1_REG_ADDRESS + FLASH_SAINF_OFFSET)) /* PFLASH1 status object */
#if defined(THA6_THA6412)
/* PFLASH2 register address */
#define FLASH_PFLASH2_REG_ADDRESS (FLASH_CLUSTER1_BASE_ADDRESS + FLASH_PFLASH2_REG_OFFSET) /* PFLASH2 */
#define FLASH_PF2_CTR_ADDRESS (FLASH_PFLASH2_REG_ADDRESS + FLASH_CTR_OFFSET)               /* PFLASH2 control */
#define FLASH_PFLASH2_CTR ((FLASH_CTR_MODULE *)FLASH_PF2_CTR_ADDRESS)                      /* PFLASH2 control object */
/* #Violation: flash_register_h_REF_1 */
#define FLASH_PFLASH2_MSK ((FLASH_MSK_MODULE *)(FLASH_PFLASH2_REG_ADDRESS + FLASH_MSK_OFFSET)) /* PFLASH2 mask object */
#define FLASH_PFLASH2_STS ((FLASH_STS_MODULE *)(FLASH_PFLASH2_REG_ADDRESS + FLASH_STS_OFFSET)) /* PFLASH2 status object */
/* #Violation: flash_register_h_REF_1 */
#define FLASH_PFLASH2_SSU ((FLASH_SSU_MODULE *)(FLASH_PFLASH2_REG_ADDRESS + FLASH_SSU_OFFSET)) /* PFLASH2 status object */
/* #Violation: flash_register_h_REF_1 */
#define FLASH_PFLASH2_SAINF ((FLASH_SAINF_MODULE *)(FLASH_PFLASH2_REG_ADDRESS + FLASH_SAINF_OFFSET)) /* PFLASH2 status object */
/* PFLASH3 register address */
#define FLASH_PFLASH3_REG_ADDRESS (FLASH_CLUSTER1_BASE_ADDRESS + FLASH_PFLASH3_REG_OFFSET) /* PFLASH3 */
#define FLASH_PF3_CTR_ADDRESS (FLASH_PFLASH3_REG_ADDRESS + FLASH_CTR_OFFSET)               /* PFLASH3 control */
#define FLASH_PFLASH3_CTR ((FLASH_CTR_MODULE *)FLASH_PF3_CTR_ADDRESS)                      /* PFLASH3 control object */
/* #Violation: flash_register_h_REF_1 */
#define FLASH_PFLASH3_MSK ((FLASH_MSK_MODULE *)(FLASH_PFLASH3_REG_ADDRESS + FLASH_MSK_OFFSET)) /* PFLASH3 mask object */
#define FLASH_PFLASH3_STS ((FLASH_STS_MODULE *)(FLASH_PFLASH3_REG_ADDRESS + FLASH_STS_OFFSET)) /* PFLASH3 status object */
/* #Violation: flash_register_h_REF_1 */
#define FLASH_PFLASH3_SSU ((FLASH_SSU_MODULE *)(FLASH_PFLASH3_REG_ADDRESS + FLASH_SSU_OFFSET)) /* PFLASH3 status object */
/* #Violation: flash_register_h_REF_1 */
#define FLASH_PFLASH3_SAINF ((FLASH_SAINF_MODULE *)(FLASH_PFLASH3_REG_ADDRESS + FLASH_SAINF_OFFSET)) /* PFLASH3 status object */
#endif                                                                                         /* defined(THA6_THA6412) */

#endif /* FLASH_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
