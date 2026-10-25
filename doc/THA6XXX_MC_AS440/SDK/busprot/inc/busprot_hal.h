/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName: busprot_hal.h
 * Author:   00930
 * Version:  V1.2.0
 * Date:     2026/02/28
 * Description: BUSPROT hardware abstraction layer header file.
 *              This file contains function prototypes for BUSPROT module hardware abstraction layer.
 *********************************************************************************************************************/
/*
 *#Violation Summary
 *
 *#busprot_hal_h_REF_1:MISRAC2012-Rule-2.5;
 * Justification: The macros are reserved for upper layers.
 *
 * #busprot_hal_h_REF_2:MISRAC2012-Rule-20.1;
 * Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
 */

#ifndef BUSPROT_HAL_H_
#define BUSPROT_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "compilertypes.h"
#include "busprot_register.h"
#include "tha6_cfg.h"
#if (INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */

/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* Master ID */
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_ALL_MASTERID_ENABLE (0x0007FFFFU)   /* Master ID all enable */
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_DMA0_M0_M1 (0x40000U)               /* Master ID: DMA0_M0/DMA0_M1, for CHIP THA6104 */
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_CLUSTER1_LLPP1 (0x20000U)           /* Master ID: CLUSTER1_LLPP1, for CHIP THA6412 */
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_CLUSTER1_LLPP0 (0x10000U)           /* Master ID: CLUSTER1_LLPP0, for CHIP THA6412 */
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_CLUSTER1_AXIM1 (0x8000U)            /* Master ID: CLUSTER1_AXIM1, for CHIP THA6412 */
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_CLUSTER1_AXIM0 (0x4000U)            /* Master ID: CLUSTER1_AXIM0, for CHIP THA6412 */
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_DMA3_M2 (0x2000U)                   /* Master ID: DMA3_M2, for THA6206 and THA6412 */
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_DMA3_M1 (0x1000U)                   /* Master ID: DMA3_M1 , for THA6206 and THA6412*/
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_DMA2_M2 (0x800U)                    /* Master ID: DMA2_M2 */
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_DMA2_M1 (0x400U)                    /* Master ID: DMA2_M1 */
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_DMA1_M2 (0x200U)                    /* Master ID: DMA1_M2, for THA6206 and THA6412 */
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_DMA1_M1 (0x100U)                    /* Master ID: DMA1_M1, for THA6206 and THA6412 */
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_ITMU (0x080U)                       /* Master ID: ITMU */
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_CLUSTER0_LLPP1 (0x040U)             /* Master ID: CLUSTER0_LLPP1, for THA6206 and THA6412 */
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_CLUSTER0_LLPP0 (0x020U)             /* Master ID: CLUSTER0_LLPP0 */
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_DBGTRACE (0x010U)                   /* Master ID: DBGTRACE */
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_MASTER_DEV_SET1 (0x008U)            /* Master ID: Master Device Set1 */
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_MASTER_DEV_SET0 (0x004U)            /* Master ID: (GTM/HSM/ETH/DMA0_M1/DMA0_M2 for THA6412 and THA6206) (HSM/ETH for THA6206) */
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_CLUSTER0_AXIM1 (0x002U)             /* Master ID: CLUSTER0_AXIM1 */
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_CLUSTER0_AXIM0 (0x001U)             /* Master ID: CLUSTER0_AXIM0 */

/* Bus protect alarm clear,the relevant bits are 0x11 to clear alarm */
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_REDUNDANCY_ALARM_CLR (0xC0U)    /* Clear redundancy alarm */
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_MASTERID_ALARM_CLR (0x30U)      /* Clear master Id alarm */
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_TIMEOUT_ALARM_CLR (0x0CU)       /* Clear timeout alarm */
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_SEWDG_ALARM_CLR (0x03U)         /* Clear safewdg endinit alarm */

/* Bus protect alarm status,the relevant bit is 1 to display alarm */
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_CLRALM_STS (0x800U)             /* Clear alarm status*/
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_PFIJALM_STS (0x400U)            /* Parity fault injection alarm status*/
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_BYPASSALM_STS (0x200U)          /* Bypass alarm status*/
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_ACTRLALM_STS (0x100U)           /* ACTRL alarm status*/
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_AERRCLRALM_STS (0x080U)         /* AERRCLR alarm status*/
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_HERRCLRALM_STS (0x040U)         /* HERRCLR alarm status*/
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_PERRCLRALM_STS (0x020U)         /* PERRCLR alarm status*/
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_TMOUTCTRL_STS (0x010U)          /* TMOUTCTRL alarm status*/
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_MSKALM_STS (0x008U)             /* MASK alarm status*/
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_MIDALM_STS (0x004U)             /* Master ID alarm status*/
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_TMOUTALM_STS (0x002U)           /* Timeout alarm status*/
/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_SEALM_STS (0x001U)              /* Safewdg endinit alarm status*/

/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* Define the BUSPROT return status */
typedef enum
{
    BUSPROT_STATUS_SUCCESS = 0U, /* Return success state */
    BUSPROT_STATUS_FAIL          /* Return failure state */
} Busprot_Status;

/* Define the BUSPROT alarm mask */
typedef enum
{
    BUSPROT_ALARM_NO_MASK = 0U, /* Busprot alarm no mask,can emerge alarm */
    BUSPROT_ALARM_MASK = 1U     /* Busprot alarm mask,cann't emerge alarm */
} Busprot_Alarm_Mask;

/* Define the BUSPROT alarm type */
typedef enum
{
    BUSPROT_ALARM_TYPE_MASTERID = (0x300U),   /* Master ID alarm */
    BUSPROT_ALARM_TYPE_TIMEOUT = (0x0C0U),    /* Timeout alarm */
    BUSPROT_ALARM_TYPE_REDUNDANCY = (0x030U), /* Redundancy alarm */
    BUSPROT_ALARM_TYPE_BUSERR = (0x00CU),     /* Bus error alarm */
    BUSPROT_ALARM_TYPE_EDC_PTY = (0x003U),    /* EDC/PTY check alarm */
    BUSPROT_ALARM_TYPE_ALL = (0x3FFU)         /* All alarm */
} Busprot_Alarm_Type;

/* Bus protect module offset address */
typedef enum
{
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
    BUSPROT_AHB0_M_PROT0 = 0x0B0000U,         /* Offset address of AHB0_M_PROT0 BUSPROT module */
    BUSPROT_AHB0_M_PROT4 = 0x0B0100U,         /* Offset address of AHB0_M_PROT4 BUSPROT module */
    BUSPROT_AHB0_S_PROT0 = 0x0B0200U,         /* Offset address of AHB0_S_PROT0 BUSPROT module */
    BUSPROT_CLUSTER0_AXI_M_PROT2 = 0x0B0300U, /* Offset address of CLUSTER0_AXI_M_PROT2 BUSPROT module */
    BUSPROT_CLUSTER0_AXI_M_PROT3 = 0x0B0400U, /* Offset address of CLUSTER0_AXI_M_PROT3 BUSPROT module */
    BUSPROT_MBUS_AXI_M_PROT2 = 0x0B0500U,     /* Offset address of MBUS_AXI_M_PROT2 BUSPROT module */
    BUSPROT_MBUS_AXI_M_PROT3 = 0x0B0600U,     /* Offset address of MBUS_AXI_M_PROT3 BUSPROT module */
    BUSPROT_CLUSTER0_AXI_S_PROT0 = 0x0B0700U, /* Offset address of CLUSTER0_AXI_S_PROT0 BUSPROT module */
    BUSPROT_MBUS_AXI_S_PROT3 = 0x0B0800U,     /* Offset address of MBUS_AXI_S_PROT3 BUSPROT module */
    BUSPROT_MBUS_AXI_S_PROT4 = 0x0B0900U,     /* Offset address of MBUS_AXI_S_PROT4 BUSPROT module */
    BUSPROT_MBUS_AXI_S_PROT5 = 0x0B0A00U,     /* Offset address of MBUS_AXI_S_PROT5 BUSPROT module */
    BUSPROT_CLUSTER1_AXI_M_PROT2 = 0x601800U, /* Offset address of CLUSTER1_AXI_M_PROT2 BUSPROT module, for CHIP THA6412 */
    BUSPROT_CLUSTER1_AXI_M_PROT3 = 0x601900U, /* Offset address of CLUSTER1_AXI_M_PROT3 BUSPROT module, for CHIP THA6412 */
    BUSPROT_CLUSTER1_AXI_S_PROT0 = 0x601A00U, /* Offset address of CLUSTER1_AXI_S_PROT0 module, for CHIP THA6412 */
    BUSPROT_ADB_AXI_M_PROT0 = 0x602800U,      /* Offset address of ADB_AXI_M_PROT0 module, for CHIP THA6412 */
    BUSPROT_ADB_AXI_S_PROT0 = 0x602900U,      /* Offset address of ADB_AXI_S_PROT0 module, for CHIP THA6412 */
    BUSPROT_AHB1_M_PROT0 = 0x0B1000U,         /* Offset address of AHB1_M_PROT0 BUSPROT module */
    BUSPROT_AHB1_M_PROT1 = 0x0B1100U,         /* Offset address of AHB1_M_PROT1 BUSPROT module */
    BUSPROT_AHB1_M_PROT5 = 0x0B1200U,         /* Offset address of AHB1_M_PROT5 BUSPROT module */
    BUSPROT_AHB1_M_PROT6 = 0x0B1300U,         /* Offset address of AHB1_M_PROT6 BUSPROT module */
    BUSPROT_AHB1_S_PROT0 = 0x0B1400U,         /* Offset address of AHB1_S_PROT0 BUSPROT module */
    BUSPROT_AHB1_S_PROT1 = 0x0B1500U,         /* Offset address of AHB1_S_PROT1 BUSPROT module */
    BUSPROT_AHB1_S_PROT2 = 0x0B1600U,         /* Offset address of AHB1_S_PROT2 BUSPROT module */
    BUSPROT_AHB1_S_PROT4 = 0x0B1700U,         /* Offset address of AHB1_S_PROT4 BUSPROT module */
    BUSPROT_AHB1_APB_S_PROT0 = 0x0B1800U,     /* Offset address of AHB1_APB_S_PROT0 BUSPROT module */
    BUSPROT_AHB1_M_PROT2 = 0x0B1900U,         /* Offset address of AHB1_M_PROT2 BUSPROT module , for CHIP THA6412*/
    BUSPROT_AHB1_M_PROT3 = 0x0B1A00U,         /* Offset address of AHB1_M_PROT3 BUSPROT module, for CHIP THA6412 */
    BUSPROT_AHB1_S_PROT3 = 0x0B1B00U,         /* Offset address of AHB1_S_PROT3 BUSPROT module, for CHIP THA6412 */
    BUSPROT_AHB2_M_PROT1 = 0x0B2000U,         /* Offset address of AHB2_M_PROT1 BUSPROT module */
    BUSPROT_AHB2_M_PROT2 = 0x0B2100U,         /* Offset address of AHB2_M_PROT2 BUSPROT module */
    BUSPROT_AHB2_M_PROT3 = 0x0B2200U,         /* Offset address of AHB2_M_PROT3 BUSPROT module */
    BUSPROT_AHB2_APB_S_PROT0 = 0x0B2300U,     /* Offset address of AHB2_APB_S_PROT0 BUSPROT module */
    BUSPROT_AHB2_APB_S_PROT1 = 0x0B2400U,     /* Offset address of AHB2_APB_S_PROT1 BUSPROT module */
    BUSPROT_AHB2_APB_S_PROT2 = 0x0B2500U,     /* Offset address of AHB2_APB_S_PROT2 BUSPROT module */
    BUSPROT_AHB2_APB_S_PROT3 = 0x0B2600U,     /* Offset address of AHB2_APB_S_PROT3 BUSPROT module */
    BUSPROT_AHB2_S_PROT4 = 0x0B2700U,         /* Offset address of AHB2_S_PROT4 BUSPROT module */
    BUSPROT_AHB2_S_PROT5 = 0x0B2800U,         /* Offset address of AHB2_S_PROT5 BUSPROT module */
    BUSPROT_AHB2_S_PROT6 = 0x0B2900U,         /* Offset address of AHB2_S_PROT6 BUSPROT module */
    BUSPROT_AHB2_S_PROT7 = 0x0B2A00U,         /* Offset address of AHB2_S_PROT7 BUSPROT module */
    BUSPROT_AHB2_S_PROT8 = 0x0B2B00U,         /* Offset address of AHB2_S_PROT8 BUSPROT module */
    BUSPROT_AHB2_S_PROT10 = 0x0B2C00U,        /* Offset address of AHB2_S_PROT10 BUSPROT module, for CHIP THA6412 */
    BUSPROT_AHB2_S_PROT11 = 0x0B2D00U,        /* Offset address of AHB2_S_PROT11 BUSPROT module */
    BUSPROT_AHB3_M_PROT1 = 0x0B3000U,         /* Offset address of AHB3_M_PROT1 BUSPROT module */
    BUSPROT_AHB3_M_PROT2 = 0x0B3100U,         /* Offset address of AHB3_M_PROT2 BUSPROT module */
    BUSPROT_AHB3_S_PROT1 = 0x0B3200U,         /* Offset address of AHB3_S_PROT1 BUSPROT module */
    BUSPROT_AHB3_S_PROT2 = 0x0B3300U,         /* Offset address of AHB3_S_PROT2 BUSPROT module */
    BUSPROT_AHB3_S_PROT3 = 0x0B3400U,         /* Offset address of AHB3_S_PROT3 BUSPROT module */
    BUSPROT_AHB3_APB_S_PROT0 = 0x0B3500U,     /* Offset address of AHB3_APB_S_PROT0 BUSPROT module */
    BUSPROT_AHB3_APB_S_PROT1 = 0x0B3600U,     /* Offset address of AHB3_APB_S_PROT1 BUSPROT module */
    BUSPROT_AHB3_APB_S_PROT2 = 0x0B3700U,     /* Offset address of AHB3_APB_S_PROT2 BUSPROT module */
    BUSPROT_AHB3_APB_S_PROT3 = 0x0B3800U,     /* Offset address of AHB3_APB_S_PROT3 BUSPROT module */
    BUSPROT_AHB3_APB_S_PROT4 = 0x0B3900U,     /* Offset address of AHB3_APB_S_PROT4 BUSPROT module */
    BUSPROT_AHB3_APB_S_PROT7 = 0x0B3A00U,     /* Offset address of AHB3_APB_S_PROT7 BUSPROT module */
    BUSPROT_AHB3_APB_S_PROT5 = 0x0B3B00U,     /* Offset address of AHB3_APB_S_PROT5 BUSPROT module, for CHIP THA6412 */
    BUSPROT_AHB3_APB_S_PROT6 = 0x0B3C00U,     /* Offset address of AHB3_APB_S_PROT6 BUSPROT module, for CHIP THA6412 */
    BUSPROT_AHB3_S_PROT4 = 0x0B3D00U          /* Offset address of AHB3_S_PROT4 BUSPROT module, for CHIP THA6412 */
#endif
#if defined(THA6_THA6104)
    BUSPROT_AHB0_M_PROT0 = 0x0B0000U,         /* Offset address of AHB0_M_PROT0 BUSPROT module */
    BUSPROT_AHB0_M_PROT2 = 0x0B0100U,         /* Offset address of AHB0_M_PROT2 BUSPROT module */
    BUSPROT_AHB0_M_PROT5 = 0x0B0200U,         /* Offset address of AHB0_M_PROT5 BUSPROT module */
    BUSPROT_AHB0_S_PROT0 = 0x0B0300U,         /* Offset address of AHB0_S_PROT0 BUSPROT module */
    BUSPROT_CLUSTER0_AXI_M_PROT1 = 0x0B0400U, /* Offset address of CLUSTER0_AXI_M_PROT1 BUSPROT module */
    BUSPROT_CLUSTER0_AXI_M_PROT2 = 0x0B0500U, /* Offset address of CLUSTER0_AXI_M_PROT2 BUSPROT module */
    BUSPROT_CLUSTER0_AXI_S_PROT0 = 0x0B0600U, /* Offset address of CLUSTER0_AXI_S_PROT0 BUSPROT module */
    BUSPROT_MBUS_AXI_M_PROT1 = 0x0B0700U,     /* Offset address of MBUS_AXI_M_PROT1 BUSPROT module */
    BUSPROT_MBUS_AXI_M_PROT2 = 0x0B0800U,     /* Offset address of MBUS_AXI_M_PROT2 BUSPROT module */
    BUSPROT_MBUS_AXI_M_PROT3 = 0x0B0900U,     /* Offset address of MBUS_AXI_M_PROT3 BUSPROT module */
    BUSPROT_MBUS_AXI_S_PROT2 = 0x0B0A00U,     /* Offset address of MBUS_AXI_S_PROT2 BUSPROT module */
    BUSPROT_MBUS_AXI_S_PROT3 = 0x0B0B00U,     /* Offset address of MBUS_AXI_S_PROT3 BUSPROT module */
    BUSPROT_MBUS_AXI_S_PROT4 = 0x0B0C00U,     /* Offset address of MBUS_AXI_S_PROT4 BUSPROT module */
    BUSPROT_AHB1_M_PROT1 = 0x0B1000U,         /* Offset address of AHB1_M_PROT1 BUSPROT module */
    BUSPROT_AHB1_S_PROT1 = 0x0B1100U,         /* Offset address of AHB1_S_PROT1 BUSPROT module */
    BUSPROT_AHB1_S_PROT2 = 0x0B1200U,         /* Offset address of AHB1_S_PROT2 BUSPROT module */
    BUSPROT_AHB1_APB_S_PROT0 = 0x0B1300U,     /* Offset address of AHB1_APB_S_PROT0 BUSPROT module */
    BUSPROT_AHB1_APB_S_PROT1 = 0x0B1400U,     /* Offset address of AHB1_APB_S_PROT1 BUSPROT module */
    BUSPROT_AHB1_S_PROT5 = 0x0B1500U,         /* Offset address of AHB1_S_PROT5 BUSPROT module */
    BUSPROT_AHB1_APB_S_PROT3 = 0x0B1600U,     /* Offset address of AHB1_APB_S_PROT3 BUSPROT module */
    BUSPROT_AHB1_S_PROT7 = 0x0B1700U,         /* Offset address of AHB1_S_PROT7 BUSPROT module */
    BUSPROT_AHB1_APB_S_PROT5 = 0x0B1800U,     /* Offset address of AHB1_APB_S_PROT5 BUSPROT module */
    BUSPROT_AHB1_APB_S_PROT6 = 0x0B1900U,     /* Offset address of AHB1_APB_S_PROT6 BUSPROT module */
    BUSPROT_AHB0_M_PROT3 = 0x0B2000U,         /* Offset address of AHB0_M_PROT3 BUSPROT module */
    BUSPROT_AHB0_M_PROT4 = 0x0B2100U,         /* Offset address of AHB0_M_PROT4 BUSPROT module */
    BUSPROT_AHB0_APB_S_PROT0 = 0x0B2200U,     /* Offset address of AHB0_APB_S_PROT0 BUSPROT module */
    BUSPROT_AHB0_APB_S_PROT1 = 0x0B2300U,     /* Offset address of AHB0_APB_S_PROT1 BUSPROT module */
    BUSPROT_AHB0_APB_S_PROT2 = 0x0B2400U,     /* Offset address of AHB0_APB_S_PROT2 BUSPROT module */
    BUSPROT_AHB0_APB_S_PROT3 = 0x0B2500U,     /* Offset address of AHB0_APB_S_PROT3 BUSPROT module */
    BUSPROT_AHB0_S_PROT6 = 0x0B2600U,         /* Offset address of AHB0_S_PROT6 BUSPROT module */
    BUSPROT_AHB0_S_PROT7 = 0x0B2700U,         /* Offset address of AHB0_S_PROT7 BUSPROT module */
    BUSPROT_AHB0_S_PROT8 = 0x0B2800U,         /* Offset address of AHB0_S_PROT8 BUSPROT module */
    BUSPROT_AHB0_S_PROT9 = 0x0B2900U,         /* Offset address of AHB0_S_PROT9 BUSPROT module */
    BUSPROT_AHB0_S_PROT10 = 0x0B2A00U,        /* Offset address of AHB0_S_PROT10 BUSPROT module */
    BUSPROT_AHB0_S_PROT11 = 0x0B2B00U,        /* Offset address of AHB0_S_PROT11 BUSPROT module */
    BUSPROT_AHB0_S_PROT12 = 0x0B2C00U,        /* Offset address of AHB0_S_PROT12 BUSPROT module */
    BUSPROT_AHB0_S_PROT13 = 0x0B2D00U,        /* Offset address of AHB0_S_PROT13 BUSPROT module */
    BUSPROT_AHB0_S_PROT14 = 0x0B2E00U,        /* Offset address of AHB0_S_PROT14 BUSPROT module */
    BUSPROT_AHB0_APB_S_PROT4 = 0x0B2F00U,     /* Offset address of AHB0_APB_S_PROT4 BUSPROT module */

#endif
} Busprot_OffsetAddress;

/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* Structure for BUSPROT error information */
typedef struct
{
    uint32 errStatus; /* Error status for AXI/AHB/APB bus */
    uint32 errInfo;   /* Error information, only for AHB bus */
    uint32 errAddr;   /* AHB/APB error address for first EDC/parity check error */
    uint32 errData;   /* AHB/APB error data for first EDC/parity check error */
} Busprot_ErrInfo;

/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: busprot_hal_h_REF_2 */
#include "Busprot_MemMap.h"

/**********************************************************************************************************************
 *                                        Global Inline Function Declaration
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:            Busprot_Hal_SetMasterId
 * Description:         Set master Id access enable/disable according to bits
 * Sync/Async:          Synchronous
 * Reentrancy:          Non-Reentrant
 * Input:               busprotOffAddr: Bus protect module offset address
 *                      accessEnable: Set master Id access enable/disable according to bits,
 *                      0-disable master Id write access,1-enable master Id write
 * Inout:               None
 * Output:              none
 * Return:              boolean:
 *                          TRUE:  Register read back check correct
 *                          FALSE: Register read back check incorrect
 * Others:
 * Date         Author   Modified
 * 2023/08/21   00930     create
 *********************************************************************************************************************/
extern boolean Busprot_Hal_SetMasterId(Busprot_OffsetAddress busprotOffAddr, uint32 accessEnable);

/**********************************************************************************************************************
 * Function:            Busprot_Hal_EnableTimeoutProt
 * Description:         Enable timeout protection
 * Sync/Async:          Synchronous
 * Reentrancy:          Non-Reentrant
 * Input:               busprotOffAddr: Bus protect module offset address
 *                      timeoutThreshold: Time out threshold value
 * Inout:               None
 * Output:              none
 * Return:              boolean:
 *                          TRUE:  Register read back check correct
 *                          FALSE: Register read back check incorrect
 * Others:
 * Date         Author   Modified
 * 2023/08/21   00930     create
 *********************************************************************************************************************/
extern boolean Busprot_Hal_EnableTimeoutProt(Busprot_OffsetAddress busprotOffAddr, uint32 timeoutThreshold);

/**********************************************************************************************************************
 * Function:            Busprot_Hal_DisableTimeoutProt
 * Description:         Disable timeout protection
 * Sync/Async:          Synchronous
 * Reentrancy:          Non-Reentrant
 * Input:               busprotOffAddr: Bus protect module offset address
 * Inout:               None
 * Output:              none
 * Return:              boolean:
 *                          TRUE:  Register read back check correct
 *                          FALSE: Register read back check incorrect
 * Others:
 * Date         Author   Modified
 * 2023/08/21   00930     create
 *********************************************************************************************************************/
extern boolean Busprot_Hal_DisableTimeoutProt(Busprot_OffsetAddress busprotOffAddr);

/**********************************************************************************************************************
 * Function:            Busprot_Hal_GetErrScene
 * Description:         Get error scene information
 * Sync/Async:          Synchronous
 * Reentrancy:          Reentrant
 * Input:               busprotOffAddr: Bus protect module offset address
 * Inout:               None
 * Output:              pErrInfo: Pointer to the structure for BUSPROT error information
 * Return:              Busprot_Status:
 *                          BUSPROT_STATUS_SUCCESS: There is no busprot error happen
 *                          BUSPROT_STATUS_FAIL: There is busprot error happen and get error scene
 * Others:
 * Date         Author   Modified
 * 2023/08/21   00930     create
 *********************************************************************************************************************/
extern Busprot_Status Busprot_Hal_GetErrScene(Busprot_OffsetAddress busprotOffAddr, Busprot_ErrInfo *const pErrInfo);

/**********************************************************************************************************************
 * Function:            Busprot_Hal_ClearErrStatus
 * Description:         Clear check error status
 * Sync/Async:          Synchronous
 * Reentrancy:          Non-Reentrant
 * Input:               busprotOffAddr: Bus protect module offset address
 * Inout:               None
 * Output:              none
 * Return:              boolean:
 *                          TRUE:  Register read back check correct
 *                          FALSE: Register read back check incorrect
 * Others:
 * Date         Author   Modified
 * 2023/08/21   00930     create
 *********************************************************************************************************************/
extern boolean Busprot_Hal_ClearErrStatus(Busprot_OffsetAddress busprotOffAddr);

/**********************************************************************************************************************
 * Function:            Busprot_Hal_SetAlarm
 * Description:         Enable/disable SAC alarm function
 * Sync/Async:          Synchronous
 * Reentrancy:          Non-Reentrant
 * Input:               busprotOffAddr: Bus protect module offset address
 *                          alarmType: Busprot alarm type
 *                          maskType: Mask type
 * Inout:               None
 * Output:              none
 * Return:              boolean:
 *                          TRUE:  Register read back check correct
 *                          FALSE: Register read back check incorrect
 * Others:
 * Date         Author   Modified
 * 2023/08/21   00930     create
 *********************************************************************************************************************/
extern boolean Busprot_Hal_SetAlarm(Busprot_OffsetAddress busprotOffAddr, Busprot_Alarm_Type alarmType,
                                 Busprot_Alarm_Mask maskType);

/**********************************************************************************************************************
 * Function:            Busprot_Hal_GetAlarm
 * Description:         Get alarm status
 * Sync/Async:          Synchronous
 * Reentrancy:          Reentrant
 * Input:               busprotOffAddr: Bus protect module offset address
 * Inout:               None
 * Output:              none
 * Return:              uint32: Alarm status
 * Others:
 * Date         Author   Modified
 * 2023/08/21   00930     create
 *********************************************************************************************************************/
extern uint32 Busprot_Hal_GetAlarmStatus(Busprot_OffsetAddress busprotOffAddr);

/**********************************************************************************************************************
 * Function:            Busprot_Hal_ClearAlarm
 * Description:         Clear alarm status
 * Sync/Async:          Synchronous
 * Reentrancy:          Non-Reentrant
 * Input:               busprotOffAddr: Bus protect module offset address
 *                      clearValue: When the corresponding bits are 0x11, should clear SAC alarm
 * Inout:               None
 * Output:              None
 * Return:              boolean:
 *                          TRUE:  Register read back check correct
 *                          FALSE: Register read back check incorrect
 * Others:
 * Date         Author   Modified
 * 2023/08/21   00930     create
 *********************************************************************************************************************/
extern boolean Busprot_Hal_ClearAlarmStatus(Busprot_OffsetAddress busprotOffAddr, uint32 clearValue);


#define BUSPROT_REG_CHECK
#if defined(BUSPROT_REG_CHECK)
LOCAL_FORCEINLINE boolean Busprot_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    boolean ret;

    ret = state;
    if (expect != value)
    {
        ret &= FALSE;
    }

    return ret;
}
#else
LOCAL_FORCEINLINE boolean Busprot_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    (void)state;
    (void)expect;
    (void)value;

    return state;
}
#endif

/* #Violation: busprot_hal_h_REF_1 */
#define BUSPROT_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: busprot_hal_h_REF_2 */
#include "Busprot_MemMap.h"

#endif /* BUSPROT_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
