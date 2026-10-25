/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co. - Ltd. All Rights Reserved.
 * FileName:    gtm_register.h
 * Author:      01031
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all definitions of GTM module registers.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
* #Violation Summary
*#gtm_register_h_REF_1:MISRAC2012-Rule-19.2; 
* Justification: Necessary union type for bitwise access to register. Data integrity and correctness will be ensured by
*                code review.
*
*#gtm_register_h_REF_2:CertC-DCL06-C; CWE-547;
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
* 
*#gtm_register_h_REF_3:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*/
#ifndef GTM_REGISTER_H_
#define GTM_REGISTER_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "Platform_Types.h"
#include "regtypes.h"
#include "tha6_cfg.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                        GTM Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* GTM version control register */
typedef struct
{
    ureg32 REL_ITER:4;           /* [3:0] Delivery number - RO */
    ureg32 REL_BASE:8;           /* [11:4] Release step - RO */
    ureg32 reserved_12:4;        /* [15:12] Internal  reserved */
    ureg32 VENDOR_CODE:4;        /* [19:16] Device encoding digit 1 - RO */
    ureg32 DEVICE_CODE:4;        /* [23:20] Device encoding digit 0 - RO */
    ureg32 VER_MINOR:4;          /* [27:24] Minor version number - RO */
    ureg32 VER_MAJOR:4;          /* [31:28] Major version number - RO */
} GTM_REV_Bits;

/* GTM global reset register */
typedef struct
{
    ureg32 RST:1;                      /* [0:0] GTM IP Reset - RW */
    ureg32 reserved_1:26;              /* [26:1] Internal  reserved */
    ureg32 BRIDGE_MODE_WRDIS:1;        /* [27:27] BRIDGE_MODE write disable - RW */
    ureg32 reserved_28:4;              /* [31:28] Internal  reserved */
} GTM_RST_Bits;

/* GTM global control register */
typedef struct
{
    ureg32 RF_PROT:1;             /* [0:0] RST and FORCINT protection - RW */
    ureg32 TO_MODE:2;             /* [2:1] AEI timeout mode - RW */
    ureg32 reserved_3:1;          /* [3:3] Internal  reserved */
    ureg32 TO_VAL:8;              /* [11:4] AEI timeout value - RW */
    ureg32 AEIM_CLUSTER:4;        /* [15:12] AEIM cluster number - RO */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_CTRL_Bits;

/* GTM configuration register */
typedef struct
{
    ureg32 SRC_IN_MUX:1;         /* [0:0] Input source selection for signal TIM[i]_AUX_IN ( input port AUX_IN at module TIM) - RW */
    ureg32 reserved_1:31;        /* [31:1] Internal  reserved */
} GTM_CFG_Bits;

/* GTM AEI timeout exception address register */
typedef struct
{
    ureg32 TO_ADDR:21;           /* [20:0] AEI timeout address - RO */
    ureg32 reserved_21:3;        /* [23:21] Internal  reserved */
    ureg32 TO_W1R0:1;            /* [24:24] AEI timeout Read/Write flag - RO */
    ureg32 reserved_25:7;        /* [31:25] Internal  reserved */
} GTM_AEI_ADDR_XPT_Bits;

/* GTM AEI non zero status register */
typedef struct
{
    ureg32 ADDR:21;              /* [20:0] AEI exception address - RO */
    ureg32 reserved_21:3;        /* [23:21] Internal  reserved */
    ureg32 W1R0:1;               /* [24:24] AEI exception Read/Write flag - RO */
    ureg32 reserved_25:7;        /* [31:25] Internal  reserved */
} GTM_AEI_STA_XPT_Bits;

/* GTM Interrupt notification register */
typedef struct
{
    ureg32 AEI_TO_XPT:1;           /* [0:0] AEI timeout exception occurred - RW */
    ureg32 AEI_USP_ADDR:1;         /* [1:1] AEI unsupported address interrupt - RW */
    ureg32 AEI_IM_ADDR:1;          /* [2:2] AEI illegal Module address interrupt - RW */
    ureg32 AEI_USP_BE:1;           /* [3:3] AEI unsupported byte enable interrupt - RW */
    ureg32 AEIM_USP_ADDR:1;        /* [4:4] AEI master port unsupported address interrupt - RW */
    ureg32 AEIM_IM_ADDR:1;         /* [5:5] AEI master port illegal Module address interrupt - RW */
    ureg32 AEIM_USP_BE:1;          /* [6:6] AEI master port unsupported byte enable interrupt - RW */
    ureg32 CLK_EN_ERR:1;           /* [7:7] Clock enable error interrupt - RW */
    ureg32 CLK_PER_ERR:1;          /* [8:8] Clock period error interrupt - RW */
    ureg32 reserved_9:23;          /* [31:9] Internal  reserved */
} GTM_IRQ_NOTIFY_Bits;

/* GTM interrupt enable register */
typedef struct
{
    ureg32 AEI_TO_XPT_IRQ_EN:1;           /* [0:0] AEI_TO_XPT_IRQ interrupt enable - RW */
    ureg32 AEI_USP_ADDR_IRQ_EN:1;         /* [1:1] AEI_USP_ADDR_IRQ interrupt enable - RW */
    ureg32 AEI_IM_ADDR_IRQ_EN:1;          /* [2:2] AEI_IM_ADDR_IRQ interrupt enable - RW */
    ureg32 AEI_USP_BE_IRQ_EN:1;           /* [3:3] AEI_USP_BE_IRQ interrupt enable - RW */
    ureg32 AEIM_USP_ADDR_IRQ_EN:1;        /* [4:4] AEI_USP_ADDR_IRQ interrupt enable - RW */
    ureg32 AEIM_IM_ADDR_IRQ_EN:1;         /* [5:5] AEIM_IM_ADDR_IRQ interrupt enable - RW */
    ureg32 AEIM_USP_BE_IRQ_EN:1;          /* [6:6] AEIM_USP_BE_IRQ interrupt enable - RW */
    ureg32 CLK_EN_ERR_IRQ_EN:1;           /* [7:7] CLK_EN_ERR_IRQ interrupt enable - RW */
    ureg32 CLK_PER_ERR_IRQ_EN:1;          /* [8:8] CLK_PER_ERR_IRQ interrupt enable - RW */
    ureg32 reserved_9:23;                 /* [31:9] Internal  reserved */
} GTM_IRQ_EN_Bits;

/* GTM error interrupt enable register */
typedef struct
{
    ureg32 AEI_TO_XPT_EIRQ_EN:1;           /* [0:0] AEI_TO_XPT_EIRQ error interrupt enable - RW */
    ureg32 AEI_USP_ADDR_EIRQ_EN:1;         /* [1:1] AEI_USP_ADDR_EIRQ error interrupt enable - RW */
    ureg32 AEI_IM_ADDR_EIRQ_EN:1;          /* [2:2] AEI_IM_ADDR_EIRQ error interrupt enable - RW */
    ureg32 AEI_USP_BE_EIRQ_EN:1;           /* [3:3] AEI_USP_BE_EIRQ error interrupt enable - RW */
    ureg32 AEIM_USP_ADDR_EIRQ_EN:1;        /* [4:4] AEIM_USP_ADDR_EIRQ error interrupt enable - RW */
    ureg32 AEIM_IM_ADDR_EIRQ_EN:1;         /* [5:5] AEIM_IM_ADDR_EIRQ error interrupt enable - RW */
    ureg32 AEIM_USP_BE_EIRQ_EN:1;          /* [6:6] AEIM_USP_BE_EIRQ error interrupt enable - RW */
    ureg32 CLK_EN_ERR_EIRQ_EN:1;           /* [7:7] CLK_EN_ERR_EIRQ interrupt enable - RW */
    ureg32 CLK_PER_ERR_EIRQ_EN:1;          /* [8:8] CLK_PER_ERR_EIRQ interrupt enable - RW */
    ureg32 reserved_9:23;                  /* [31:9] Internal  reserved */
} GTM_EIRQ_EN_Bits;

/* GTM Software interrupt generation register */
typedef struct
{
    ureg32 TRG_AEI_TO_XPT:1;           /* [0:0] Trigger the bit GTM_IRQ_NOTIFY.AEI_TO_XPT by software. - RW */
    ureg32 TRG_AEI_USP_ADDR:1;         /* [1:1] Trigger the bit GTM_IRQ_NOTIFY.AEI_USP_ADDR by software. - RW */
    ureg32 TRG_AEI_IM_ADDR:1;          /* [2:2] Trigger the bit GTM_IRQ_NOTIFY.AEI_IM_ADDR by software. - RW */
    ureg32 TRG_AEI_USP_BE:1;           /* [3:3] Trigger the bit GTM_IRQ_NOTIFY.AEI_USP_BE by software. - RW */
    ureg32 TRG_AEIM_USP_ADDR:1;        /* [4:4] Trigger the bit GTM_IRQ_NOTIFY.AEIM_USP_ADDR by software. - RW */
    ureg32 TRG_AEIM_IM_ADDR:1;         /* [5:5] Trigger the bit GTM_IRQ_NOTIFY.AEIM_IM_ADDR by software. - RW */
    ureg32 TRG_AEIM_USP_BE:1;          /* [6:6] Trigger the bit GTM_IRQ_NOTIFY.AEIM_USP_BE by software. - RW */
    ureg32 TRG_CLK_EN_ERR:1;           /* [7:7] Trigger the bit GTM_IRQ_NOTIFY.CLK_EN_ERR by software. - RW */
    ureg32 TRG_CLK_PER_ERR:1;          /* [8:8] Trigger the bit GTM_IRQ_NOTIFY.CLK_PER_ERR by software. - RW */
    ureg32 reserved_9:23;              /* [31:9] Internal  reserved */
} GTM_IRQ_FORCINT_Bits;

/* GTM top level interrupts mode selection */
typedef struct
{
    ureg32 IRQ_MODE:2;           /* [1:0] Interrupt strategy mode selection for the AEI timeout and address monitoring interrupts. - RW */
    ureg32 reserved_2:30;        /* [31:2] Internal  reserved */
} GTM_IRQ_MODE_Bits;

/* GTM Cluster Clock Configuration */
typedef struct
{
    ureg32 CLS0_CLK_DIV:2;        /* [1:0] Cluster [j] Clock Divider - RW */
    ureg32 CLS1_CLK_DIV:2;        /* [3:2] Cluster [j] Clock Divider - RW */
    ureg32 CLS2_CLK_DIV:2;        /* [5:4] Cluster [j] Clock Divider - RW */
    ureg32 CLS3_CLK_DIV:2;        /* [7:6] Cluster [j] Clock Divider - RW */
    ureg32 CLS4_CLK_DIV:2;        /* [9:8] Cluster [j] Clock Divider - RW */
    ureg32 CLS5_CLK_DIV:2;        /* [11:10] Cluster [j] Clock Divider - RW */
    ureg32 CLS6_CLK_DIV:2;        /* [13:12] Cluster [j] Clock Divider - RW */
    ureg32 CLS7_CLK_DIV:2;        /* [15:14] Cluster [j] Clock Divider - RW */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_CLS_CLK_CFG_Bits;

/* GTM ARU communication disable */
typedef struct
{
    ureg32 CLS0_DIS:1;           /* [0:0] Disable cluster [j] ARU communication - RW */
    ureg32 CLS1_DIS:1;           /* [1:1] Disable cluster [j] ARU communication - RW */
    ureg32 CLS2_DIS:1;           /* [2:2] Disable cluster [j] ARU communication - RW */
    ureg32 CLS3_DIS:1;           /* [3:3] Disable cluster [j] ARU communication - RW */
    ureg32 reserved_4:28;        /* [31:4] Internal  reserved */
} GTM_ARU_COM_DIS_Bits;

/* GTM AEI bridge mode register */
typedef struct
{
    ureg32 BRG_MODE:1;              /* [0:0] Defines the operation mode for the AEI bridge - RW */
    ureg32 MSK_WR_RSP:1;            /* [1:1] Mask write response - RW */
    ureg32 BYPASS_SYNC:1;           /* [2:2] Bypass synchronizer flip-flops - RW */
    ureg32 reserved_3:5;            /* [7:3] Internal  reserved */
    ureg32 MODE_UP_PGR:1;           /* [8:8] Mode update in progress. - RO */
    ureg32 BUFF_OVL:1;              /* [9:9] Buffer overflow register - RW */
    ureg32 reserved_10:2;           /* [11:10] Internal  reserved */
    ureg32 SYNC_INPUT_REG:1;        /* [12:12] Additional pipelined stage in synchronous bridge mode - RO */
    ureg32 reserved_13:3;           /* [15:13] Internal  reserved */
    ureg32 BRG_RST:1;               /* [16:16] Bridge software reset - RW */
    ureg32 reserved_17:7;           /* [23:17] Internal  reserved */
    ureg32 BUFF_DPT:8;              /* [31:24] Buffer depth of AEI bridge - RO */
} GTM_BRIDGE_MODE_Bits;

/* GTM AEI bridge pointer 1 register */
typedef struct
{
    ureg32 NEW_TRAN_PTR:5;         /* [4:0] New transaction pointer - RO */
    ureg32 FIRST_RSP_PTR:5;        /* [9:5] First response pointer - RO */
    ureg32 TRAN_IN_PGR:5;          /* [14:10] Transaction in progress pointer (acquire) - RO */
    ureg32 ABT_TRAN_PGR:5;         /* [19:15] Aborted transaction in progress pointer - RO */
    ureg32 FBC:6;                  /* [25:20] Free buffer count - RO */
    ureg32 RSP_TRAN_RDY:6;         /* [31:26] Response transactions ready - RO */
} GTM_BRIDGE_PTR1_Bits;

/* GTM AEI bridge pointer 2 register */
typedef struct
{
    ureg32 TRAN_IN_PGR2:5;        /* [4:0] Transaction in progress pointer (aquire2) - RO */
    ureg32 reserved_5:27;         /* [31:5] Internal  reserved */
} GTM_BRIDGE_PTR2_Bits;

/* GTM MCS master port disable register */
typedef struct
{
    ureg32 DIS_CLS0:2;            /* [1:0] Disable MCS AEIM access in cluster [j]  - RW */
    ureg32 DIS_CLS1:2;            /* [3:2] Disable MCS AEIM access in cluster [j]  - RW */
    ureg32 DIS_CLS2:2;            /* [5:4] Disable MCS AEIM access in cluster [j]  - RW */
    ureg32 DIS_CLS3:2;            /* [7:6] Disable MCS AEIM access in cluster [j]  - RW */
    ureg32 DIS_CLS4:2;            /* [9:8] Disable MCS AEIM access in cluster [j]  - RW */
    ureg32 reserved_10:22;        /* [31:10] Internal  reserved */
} GTM_MCS_AEM_DIS_Bits;

/* CMU clock enable */
typedef struct
{
    ureg32 EN_CLK0:2;            /* [1:0] Enable clock resolution CMU_CLK_RES[x:x] - RW */
    ureg32 EN_CLK1:2;            /* [3:2] Enable clock resolution CMU_CLK_RES[x:x] - RW */
    ureg32 EN_CLK2:2;            /* [5:4] Enable clock resolution CMU_CLK_RES[x:x] - RW */
    ureg32 EN_CLK3:2;            /* [7:6] Enable clock resolution CMU_CLK_RES[x:x] - RW */
    ureg32 EN_CLK4:2;            /* [9:8] Enable clock resolution CMU_CLK_RES[x:x] - RW */
    ureg32 EN_CLK5:2;            /* [11:10] Enable clock resolution CMU_CLK_RES[x:x] - RW */
    ureg32 EN_CLK6:2;            /* [13:12] Enable clock resolution CMU_CLK_RES[x:x] - RW */
    ureg32 EN_CLK7:2;            /* [15:14] Enable clock resolution CMU_CLK_RES[x:x] - RW */
    ureg32 EN_ECLK0:2;           /* [17:16] Enable clock CMU_ECLK[z:z]  - RW */
    ureg32 EN_ECLK1:2;           /* [19:18] Enable clock CMU_ECLK[z:z]  - RW */
    ureg32 EN_ECLK2:2;           /* [21:20] Enable clock CMU_ECLK[z:z]  - RW */
    ureg32 EN_FXCLK:2;           /* [23:22] Enable clock resolution CMU_FXCLK_RES - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_CMU_CLK_EN_Bits;

/* The numerator for CMU global clock resolution generator */
typedef struct
{
    ureg32 GCLK_NUM:24;          /* [23:0] Numerator for global clock resolution generator. Defines numerator of the fractional divider. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_CMU_GCLK_NUM_Bits;

/* The denominator for CMU global clock resolution generator */
typedef struct
{
    ureg32 GCLK_DEN:24;          /* [23:0] Denominator for global resolution generator. Defines denominator of the fractional divider. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_CMU_GCLK_DEN_Bits;

/* CMU control for clock resolution generator [x] */
typedef struct
{
    ureg32 CLK_CNT:24;           /* [23:0] Clock count. Defines count value for the clock divider. - RW */
    ureg32 CLK_SEL:2;            /* [25:24] Source selection - RW */
    ureg32 reserved_26:6;        /* [31:26] Internal  reserved */
} GTM_CMU_CLK__CTRL_Bits;

/* The numerator for the external clock resolution generator [z] */
typedef struct
{
    ureg32 ECLK_NUM:24;          /* [23:0] The numerator for external clock resolution generator. Defines numerator of the fractional divider. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_CMU_ECLK_NUM_Bits;

/* The denominator for the external clock resolution generator [z] */
typedef struct
{
    ureg32 ECLK_DEN:24;          /* [23:0] The denominator for external clock resolution generator. Defines denominator of the fractional divider. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_CMU_ECLK_DEN_Bits;

/* CMU control for selection of FCR subblock input */
typedef struct
{
    ureg32 FXCLK_SEL:4;          /* [3:0] Input selection for EN_FXCLK line - RW */
    ureg32 reserved_4:28;        /* [31:4] Internal  reserved */
} GTM_CMU_FXCLK_CTRL_Bits;

/* CMU synchronizing ARU and clock source */
typedef struct
{
    ureg32 ARU_ADDR_RSTGLB:1;        /* [0:0] Reset ARU caddr counter and ARU dynamic route counter - RW */
    ureg32 reserved_1:31;            /* [31:1] Internal  reserved */
} GTM_CMU_GLB_CTRL_Bits;

/* CMU control for clock resolution generator */
typedef struct
{
    ureg32 CLK0_EXT_DIVIDER:1;        /* [0:0] Input selection for Clock Resolution Generator [x] - RW */
    ureg32 CLK1_EXT_DIVIDER:1;        /* [1:1] Input selection for Clock Resolution Generator [x] - RW */
    ureg32 CLK2_EXT_DIVIDER:1;        /* [2:2] Input selection for Clock Resolution Generator [x] - RW */
    ureg32 CLK3_EXT_DIVIDER:1;        /* [3:3] Input selection for Clock Resolution Generator [x] - RW */
    ureg32 CLK4_EXT_DIVIDER:1;        /* [4:4] Input selection for Clock Resolution Generator [x] - RW */
    ureg32 CLK5_EXT_DIVIDER:1;        /* [5:5] Input selection for Clock Resolution Generator [x] - RW */
    ureg32 CLK6_EXT_DIVIDER:1;        /* [6:6] Input selection for Clock Resolution Generator [x] - RW */
    ureg32 CLK7_EXT_DIVIDER:1;        /* [7:7] Input selection for Clock Resolution Generator [x] - RW */
    ureg32 CLK8_EXT_DIVIDER:1;        /* [8:8] Source selection for CMU_CLK_RES[8:8] - RW */
    ureg32 reserved_9:23;             /* [31:9] Internal  reserved */
} GTM_CMU_CLK_CTRL_Bits;

/* TBU global channel enable */
typedef struct
{
    ureg32 ENDIS_CH0:2;          /* [1:0] TBU channel [y] enable/disable control - RW */
    ureg32 ENDIS_CH1:2;          /* [3:2] TBU channel [y] enable/disable control - RW */
    ureg32 ENDIS_CH2:2;          /* [5:4] TBU channel [y] enable/disable control - RW */
    ureg32 ENDIS_CH3:2;          /* [7:6] TBU channel [y] enable/disable control - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TBU_CHEN_Bits;

/* TBU channel 0 control */
typedef struct
{
    ureg32 LOW_RES:1;            /* [0:0] TBU_CH0_BASE register resolution - RW */
    ureg32 CH_CLK_SRC:3;         /* [3:1] Clock source for channel 0 - channel 1 and channel 2 time base counter - RW */
    ureg32 reserved_4:28;        /* [31:4] Internal  reserved */
} GTM_TBU_CH0_CTRL_Bits;

/* TBU channel 0 base */
typedef struct
{
    ureg32 BASE:27;              /* [26:0] Time base value for channel 0 - RW */
    ureg32 reserved_27:5;        /* [31:27] Internal  reserved */
} GTM_TBU_CH_0_BASE_Bits;

/* TBU channel 1 control */
typedef struct
{
    ureg32 CH_MODE:1;            /* [0:0] Channel mode - RW */
    ureg32 CH_CLK_SRC:3;         /* [3:1] Clock source for channel 1 time base counter - RW */
    ureg32 reserved_4:28;        /* [31:4] Internal  reserved */
} GTM_TBU_CH1_CTRL_Bits;

/* TBU channel [x] base */
typedef struct
{
    ureg32 BASE:24;              /* [23:0] Time base value for channel [x] - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_TBU_CH_X_BASE_Bits;

/* TBU channel 2 control */
typedef struct
{
    ureg32 CH_MODE:1;            /* [0:0] Channel mode - RW */
    ureg32 CH_CLK_SRC:3;         /* [3:1] Clock source for channel 2 time base counter - RW */
    ureg32 reserved_4:28;        /* [31:4] Internal  reserved */
} GTM_TBU_CH2_CTRL_Bits;

/* TBU channel 3 control */
typedef struct
{
    ureg32 CH_MODE:1;            /* [0:0] Channel mode - RO */
    ureg32 reserved_1:3;         /* [3:1] Internal  reserved */
    ureg32 USE_CH2:1;            /* [4:4] Channel selector for modulo counter - RW */
    ureg32 reserved_5:27;        /* [31:5] Internal  reserved */
} GTM_TBU_CH3_CTRL_Bits;

/* TBU channel 3 modulo value */
typedef struct
{
    ureg32 BASE_MARK:24;         /* [23:0] Modulo value for channel 3 - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_TBU_CH3_BASE_MARK_Bits;

/* TBU channel 3 base captured */
typedef struct
{
    ureg32 BASE_CAPTURE:24;        /* [23:0] Captured value of time base channel 1 or channel 2  - RO */
    ureg32 reserved_24:8;          /* [31:24] Internal  reserved */
} GTM_TBU_CH3_BASE_CAPTURE_Bits;

/* ARU access register */
typedef struct
{
    ureg32 ADDR:9;                /* [8:0] ARU address - RW */
    ureg32 reserved_9:3;          /* [11:9] Internal  reserved */
    ureg32 RREQ:1;                /* [12:12] Initiate read request - RW */
    ureg32 WREQ:1;                /* [13:13] Initiate write request - RW */
    ureg32 reserved_14:18;        /* [31:14] Internal  reserved */
} GTM_ARU_ACCESS_Bits;

/* ARU access register upper data word */
typedef struct
{
    ureg32 DATA:29;              /* [28:0] Upper ARU data word - RW */
    ureg32 reserved_29:3;        /* [31:29] Internal  reserved */
} GTM_ARU_DATA_H_Bits;

/* ARU access register lower data word */
typedef struct
{
    ureg32 DATA:29;              /* [28:0] Lower ARU data word - RW */
    ureg32 reserved_29:3;        /* [31:29] Internal  reserved */
} GTM_ARU_DATA_L_Bits;

/* ARU debug access channel 0 */
typedef struct
{
    ureg32 ADDR:9;               /* [8:0] ARU debugging address  - RW */
    ureg32 reserved_9:23;        /* [31:9] Internal  reserved */
} GTM_ARU_DBG_ACCESS0_Bits;

/* ARU debug access 0 transfer register upper data word */
typedef struct
{
    ureg32 DATA:29;              /* [28:0] Upper debug data word - RO */
    ureg32 reserved_29:3;        /* [31:29] Internal  reserved */
} GTM_ARU_DBG_DATA0_H_Bits;

/* ARU debug access 0 transfer register lower data word */
typedef struct
{
    ureg32 DATA:29;              /* [28:0] Lower debug data word - RO */
    ureg32 reserved_29:3;        /* [31:29] Internal  reserved */
} GTM_ARU_DBG_DATA0_L_Bits;

/* ARU debug access channel 0 */
typedef struct
{
    ureg32 ADDR:9;               /* [8:0] ARU debugging address  - RW */
    ureg32 reserved_9:23;        /* [31:9] Internal  reserved */
} GTM_ARU_DBG_ACCESS1_Bits;

/* ARU debug access 1 transfer register upper data word */
typedef struct
{
    ureg32 DATA:29;              /* [28:0] Upper debug data word - RO */
    ureg32 reserved_29:3;        /* [31:29] Internal  reserved */
} GTM_ARU_DBG_DATA1_H_Bits;

/* ARU debug access 1 transfer register lower data word */
typedef struct
{
    ureg32 DATA:29;              /* [28:0] Lower debug data word - RO */
    ureg32 reserved_29:3;        /* [31:29] Internal  reserved */
} GTM_ARU_DBG_DATA1_L_Bits;

/* ARU interrupt notification register */
typedef struct
{
    ureg32 NEW_DATA0:1;          /* [0:0] Data was transferred for addr ARU_DBG_ACCESS0 - RW */
    ureg32 NEW_DATA1:1;          /* [1:1] Data was transferred for addr ARU_DBG_ACCESS1 - RW */
    ureg32 ACC_ACK:1;            /* [2:2] AEI to ARU access finished - on read access data are valid - RW */
    ureg32 reserved_3:29;        /* [31:3] Internal  reserved */
} GTM_ARU_IRQ_NOTIFY_Bits;

/* ARU interrupt enable register */
typedef struct
{
    ureg32 NEW_DATA0_IRQ_EN:1;        /* [0:0] ARU_NEW_DATA0_IRQ interrupt enable - RW */
    ureg32 NEW_DATA1_IRQ_EN:1;        /* [1:1] ARU_NEW_DATA1_IRQ interrupt enable - RW */
    ureg32 ACC_ACK_IRQ_EN:1;          /* [2:2] ARU_ACC_ACK_IRQ interrupt enable - RW */
    ureg32 reserved_3:29;             /* [31:3] Internal  reserved */
} GTM_ARU_IRQ_EN_Bits;

/* ARU force interrupt register */
typedef struct
{
    ureg32 TRG_NEW_DATA0:1;        /* [0:0] Trigger the bit ARU_IRQ_NOTIFY.NEW_DATA0 by software - RW */
    ureg32 TRG_NEW_DATA1:1;        /* [1:1] Trigger the bit ARU_IRQ_NOTIFY.NEW_DATA1 by software - RW */
    ureg32 TRG_ACC_ACK:1;          /* [2:2] Trigger the bit ARU_IRQ_NOTIFY.ACC_ACK by software - RW */
    ureg32 reserved_3:29;          /* [31:3] Internal  reserved */
} GTM_ARU_IRQ_FORCINT_Bits;

/* ARU interrupt mode register */
typedef struct
{
    ureg32 IRQ_MODE:2;           /* [1:0] IRQ mode selection - RW */
    ureg32 reserved_2:30;        /* [31:2] Internal  reserved */
} GTM_ARU_IRQ_MODE_Bits;

/* ARU caddr counter end value */
typedef struct
{
    ureg32 CADDR_END:7;          /* [6:0] Set end value of ARU caddr counter - RW */
    ureg32 reserved_7:25;        /* [31:7] Internal  reserved */
} GTM_ARU_CADDR_END_Bits;

/* ARU enable dynamic routing */
typedef struct
{
    ureg32 ARU_0_DYN_EN:2;             /* [1:0] Enable dynamic routing for ARU of sub-channel k - RW */
    ureg32 ARU_1_DYN_EN:2;             /* [3:2] Enable dynamic routing for ARU of sub-channel k - RW */
    ureg32 ARU_DYN_RING_MODE:1;        /* [4:4] Enable dynamic routing ring mode - RW */
    ureg32 reserved_5:27;              /* [31:5] Internal  reserved */
} GTM_ARU_CTRL_Bits;

/* ARU [g] dynamic routing control register */
typedef struct
{
    ureg32 DYN_ARU_UPDATE_EN:1;        /* [0:0] Enable reload of DYN_ROUTE register from ARU itself - RW */
    ureg32 DYN_ROUTE_SWAP:1;           /* [1:1] Enable swapping DYN_ROUTE_SR with DYN_ROUTE register - RW */
    ureg32 reserved_2:30;              /* [31:2] Internal  reserved */
} GTM_ARU_DYN_CTRL_Bits;

/* ARU [g] lower bits of DYN_ROUTE register */
typedef struct
{
    ureg32 DYN_READ_ID0:8;        /* [7:0] ARU master ID_0 - RW */
    ureg32 DYN_READ_ID1:8;        /* [15:8] ARU master ID_1 - RW */
    ureg32 DYN_READ_ID2:8;        /* [23:16] ARU master ID_2 - RW */
    ureg32 reserved_24:8;         /* [31:24] Internal  reserved */
} GTM_ARU_DYN_ROUTE_LOW_Bits;

/* ARU [g] higher bits of DYN_ROUTE register */
typedef struct
{
    ureg32 DYN_READ_ID3:8;        /* [7:0] ARU master ID_3 - RW */
    ureg32 DYN_READ_ID4:8;        /* [15:8] ARU master ID_4 - RW */
    ureg32 DYN_READ_ID5:8;        /* [23:16] ARU master ID_5 - RW */
    ureg32 DYN_CLK_WAIT:4;        /* [27:24] Number of clk cycles for dynamic routing - RW */
    ureg32 reserved_28:4;         /* [31:28] Internal  reserved */
} GTM_ARU_DYN_ROUTE_HIGH_Bits;

/* ARU [g] shadow register of DYN_ROUTE register lower bits */
typedef struct
{
    ureg32 DYN_READ_ID6:8;        /* [7:0] ARU master ID_6 - RW */
    ureg32 DYN_READ_ID7:8;        /* [15:8] ARU master ID_7 - RW */
    ureg32 DYN_READ_ID8:8;        /* [23:16] ARU master ID_8 - RW */
    ureg32 reserved_24:8;         /* [31:24] Internal  reserved */
} GTM_ARU_DYN_ROUTE_SR_LOW_Bits;

/* ARU [g] shadow register of DYN_ROUTE register higher bits */
typedef struct
{
    ureg32 DYN_READ_ID9:8;         /* [7:0] ARU master ID_9 - RW */
    ureg32 DYN_READ_ID10:8;        /* [15:8] ARU master ID_10 - RW */
    ureg32 DYN_READ_ID11:8;        /* [23:16] ARU master ID_11 - RW */
    ureg32 DYN_CLK_WAIT:4;         /* [27:24] Number of clk cycles for dynamic routing - RW */
    ureg32 DYN_UPDATE_EN:1;        /* [28:28] Update enable from shadow register - RW */
    ureg32 reserved_29:3;          /* [31:29] Internal  reserved */
} GTM_ARU_DYN_ROUTE_SR_HIGH_Bits;

/* ARU [g] master ID for dynamic routing */
typedef struct
{
    ureg32 DYN_ARU_RDADDR:9;        /* [8:0] ARU read address ID to reload the dynamic routing register - RW */
    ureg32 reserved_9:23;           /* [31:9] Internal  reserved */
} GTM_ARU_DYN_RDADDR_Bits;

/* ARU caddr counter value */
typedef struct
{
    ureg32 CADDR_0:7;            /* [6:0] Value of ARU_0 caddr counter - RO */
    ureg32 reserved_7:9;         /* [15:7] Internal  reserved */
    ureg32 CADDR_1:7;            /* [22:16] Value of ARU_1 caddr counter - RO */
    ureg32 reserved_23:9;        /* [31:23] Internal  reserved */
} GTM_ARU_CADDR_Bits;

/* BRC read address for input channel [x] */
typedef struct
{
    ureg32 ADDR:9;                /* [8:0] Source ARU address. Define an ARU read address used as data source for input channel[x].  - RW */
    ureg32 reserved_9:3;          /* [11:9] Internal  reserved */
    ureg32 BRC_MODE:1;            /* [12:12] BRC Operation mode select - RW */
    ureg32 reserved_13:19;        /* [31:13] Internal  reserved */
} GTM_BRC_SRC_ADDR_Bits;

/* BRC destination channels for input channel [x] */
typedef struct
{
    ureg32 EN_DEST0:1;           /* [0:0] Enable BRC destination address [z] - RW */
    ureg32 EN_DEST1:1;           /* [1:1] Enable BRC destination address [z] - RW */
    ureg32 EN_DEST2:1;           /* [2:2] Enable BRC destination address [z] - RW */
    ureg32 EN_DEST3:1;           /* [3:3] Enable BRC destination address [z] - RW */
    ureg32 EN_DEST4:1;           /* [4:4] Enable BRC destination address [z] - RW */
    ureg32 EN_DEST5:1;           /* [5:5] Enable BRC destination address [z] - RW */
    ureg32 EN_DEST6:1;           /* [6:6] Enable BRC destination address [z] - RW */
    ureg32 EN_DEST7:1;           /* [7:7] Enable BRC destination address [z] - RW */
    ureg32 EN_DEST8:1;           /* [8:8] Enable BRC destination address [z] - RW */
    ureg32 EN_DEST9:1;           /* [9:9] Enable BRC destination address [z] - RW */
    ureg32 EN_DEST10:1;          /* [10:10] Enable BRC destination address [z] - RW */
    ureg32 EN_DEST11:1;          /* [11:11] Enable BRC destination address [z] - RW */
    ureg32 EN_DEST12:1;          /* [12:12] Enable BRC destination address [z] - RW */
    ureg32 EN_DEST13:1;          /* [13:13] Enable BRC destination address [z] - RW */
    ureg32 EN_DEST14:1;          /* [14:14] Enable BRC destination address [z] - RW */
    ureg32 EN_DEST15:1;          /* [15:15] Enable BRC destination address [z] - RW */
    ureg32 EN_DEST16:1;          /* [16:16] Enable BRC destination address [z] - RW */
    ureg32 EN_DEST17:1;          /* [17:17] Enable BRC destination address [z] - RW */
    ureg32 EN_DEST18:1;          /* [18:18] Enable BRC destination address [z] - RW */
    ureg32 EN_DEST19:1;          /* [19:19] Enable BRC destination address [z] - RW */
    ureg32 EN_DEST20:1;          /* [20:20] Enable BRC destination address [z] - RW */
    ureg32 EN_DEST21:1;          /* [21:21] Enable BRC destination address [z] - RW */
    ureg32 EN_TRASHBIN:1;        /* [22:22] Control trash bin functionality. - RW */
    ureg32 reserved_23:9;        /* [31:23] Internal  reserved */
} GTM_BRC_SRC_DEST_Bits;

/* BRC interrupt notification register */
typedef struct
{
    ureg32 DEST_ERR:1;            /* [0:0] Configuration error interrupt for BRC sub-module - RW */
    ureg32 DID0:1;                /* [1:1] Data inconsistency occurred in MTM mode for channel [x]. - RW */
    ureg32 DID1:1;                /* [2:2] Data inconsistency occurred in MTM mode for channel [x]. - RW */
    ureg32 DID2:1;                /* [3:3] Data inconsistency occurred in MTM mode for channel [x]. - RW */
    ureg32 DID3:1;                /* [4:4] Data inconsistency occurred in MTM mode for channel [x]. - RW */
    ureg32 DID4:1;                /* [5:5] Data inconsistency occurred in MTM mode for channel [x]. - RW */
    ureg32 DID5:1;                /* [6:6] Data inconsistency occurred in MTM mode for channel [x]. - RW */
    ureg32 DID6:1;                /* [7:7] Data inconsistency occurred in MTM mode for channel [x]. - RW */
    ureg32 DID7:1;                /* [8:8] Data inconsistency occurred in MTM mode for channel [x]. - RW */
    ureg32 DID8:1;                /* [9:9] Data inconsistency occurred in MTM mode for channel [x]. - RW */
    ureg32 DID9:1;                /* [10:10] Data inconsistency occurred in MTM mode for channel [x]. - RW */
    ureg32 DID10:1;               /* [11:11] Data inconsistency occurred in MTM mode for channel [x]. - RW */
    ureg32 DID11:1;               /* [12:12] Data inconsistency occurred in MTM mode for channel [x]. - RW */
    ureg32 reserved_13:19;        /* [31:13] Internal  reserved */
} GTM_BRC_IRQ_NOTIFY_Bits;

/* BRC interrupt enable register */
typedef struct
{
    ureg32 DEST_ERR_IRQ_EN:1;        /* [0:0] BRC_DEST_ERR_IRQ interrupt enable - RW */
    ureg32 DID_IRQ_EN0:1;            /* [1:1] Enable BRC_DID_IRQ for channel [x] - RW */
    ureg32 DID_IRQ_EN1:1;            /* [2:2] Enable BRC_DID_IRQ for channel [x] - RW */
    ureg32 DID_IRQ_EN2:1;            /* [3:3] Enable BRC_DID_IRQ for channel [x] - RW */
    ureg32 DID_IRQ_EN3:1;            /* [4:4] Enable BRC_DID_IRQ for channel [x] - RW */
    ureg32 DID_IRQ_EN4:1;            /* [5:5] Enable BRC_DID_IRQ for channel [x] - RW */
    ureg32 DID_IRQ_EN5:1;            /* [6:6] Enable BRC_DID_IRQ for channel [x] - RW */
    ureg32 DID_IRQ_EN6:1;            /* [7:7] Enable BRC_DID_IRQ for channel [x] - RW */
    ureg32 DID_IRQ_EN7:1;            /* [8:8] Enable BRC_DID_IRQ for channel [x] - RW */
    ureg32 DID_IRQ_EN8:1;            /* [9:9] Enable BRC_DID_IRQ for channel [x] - RW */
    ureg32 DID_IRQ_EN9:1;            /* [10:10] Enable BRC_DID_IRQ for channel [x] - RW */
    ureg32 DID_IRQ_EN10:1;           /* [11:11] Enable BRC_DID_IRQ for channel [x] - RW */
    ureg32 DID_IRQ_EN11:1;           /* [12:12] Enable BRC_DID_IRQ for channel [x] - RW */
    ureg32 reserved_13:19;           /* [31:13] Internal  reserved */
} GTM_BRC_IRQ_EN_Bits;

/* BRC force interrupt register */
typedef struct
{
    ureg32 TRG_DEST_ERR:1;        /* [0:0] Trigger the bit BRC_IRQ_NOTIFY.DEST_ERR by software - RW */
    ureg32 TRG_DID0:1;            /* [1:1] Trigger the bit BRC_IRQ_NOTIFY.DID[x] by software - RW */
    ureg32 TRG_DID1:1;            /* [2:2] Trigger the bit BRC_IRQ_NOTIFY.DID[x] by software - RW */
    ureg32 TRG_DID2:1;            /* [3:3] Trigger the bit BRC_IRQ_NOTIFY.DID[x] by software - RW */
    ureg32 TRG_DID3:1;            /* [4:4] Trigger the bit BRC_IRQ_NOTIFY.DID[x] by software - RW */
    ureg32 TRG_DID4:1;            /* [5:5] Trigger the bit BRC_IRQ_NOTIFY.DID[x] by software - RW */
    ureg32 TRG_DID5:1;            /* [6:6] Trigger the bit BRC_IRQ_NOTIFY.DID[x] by software - RW */
    ureg32 TRG_DID6:1;            /* [7:7] Trigger the bit BRC_IRQ_NOTIFY.DID[x] by software - RW */
    ureg32 TRG_DID7:1;            /* [8:8] Trigger the bit BRC_IRQ_NOTIFY.DID[x] by software - RW */
    ureg32 TRG_DID8:1;            /* [9:9] Trigger the bit BRC_IRQ_NOTIFY.DID[x] by software - RW */
    ureg32 TRG_DID9:1;            /* [10:10] Trigger the bit BRC_IRQ_NOTIFY.DID[x] by software - RW */
    ureg32 TRG_DID10:1;           /* [11:11] Trigger the bit BRC_IRQ_NOTIFY.DID[x] by software - RW */
    ureg32 TRG_DID11:1;           /* [12:12] Trigger the bit BRC_IRQ_NOTIFY.DID[x] by software - RW */
    ureg32 reserved_13:19;        /* [31:13] Internal  reserved */
} GTM_BRC_IRQ_FORCINT_Bits;

/* BRC interrupt mode configuration register */
typedef struct
{
    ureg32 IRQ_MODE:2;           /* [1:0]  IRQ mode selection - RW */
    ureg32 reserved_2:30;        /* [31:2] Internal  reserved */
} GTM_BRC_IRQ_MODE_Bits;

/* BRC software reset register */
typedef struct
{
    ureg32 RST:1;                /* [0:0] Software reset - RW */
    ureg32 reserved_1:31;        /* [31:1] Internal  reserved */
} GTM_BRC_RST_Bits;

/* BRC error interrupt enable register */
typedef struct
{
    ureg32 DEST_ERR_EIRQ_EN:1;        /* [0:0] BRC_DEST_ERR_EIRQ error interrupt enable - RW */
    ureg32 DID_EIRQ_EN0:1;            /* [1:1] Enable BRC_DID_EIRQ for channel [x] - RW */
    ureg32 DID_EIRQ_EN1:1;            /* [2:2] Enable BRC_DID_EIRQ for channel [x] - RW */
    ureg32 DID_EIRQ_EN2:1;            /* [3:3] Enable BRC_DID_EIRQ for channel [x] - RW */
    ureg32 DID_EIRQ_EN3:1;            /* [4:4] Enable BRC_DID_EIRQ for channel [x] - RW */
    ureg32 DID_EIRQ_EN4:1;            /* [5:5] Enable BRC_DID_EIRQ for channel [x] - RW */
    ureg32 DID_EIRQ_EN5:1;            /* [6:6] Enable BRC_DID_EIRQ for channel [x] - RW */
    ureg32 DID_EIRQ_EN6:1;            /* [7:7] Enable BRC_DID_EIRQ for channel [x] - RW */
    ureg32 DID_EIRQ_EN7:1;            /* [8:8] Enable BRC_DID_EIRQ for channel [x] - RW */
    ureg32 DID_EIRQ_EN8:1;            /* [9:9] Enable BRC_DID_EIRQ for channel [x] - RW */
    ureg32 DID_EIRQ_EN9:1;            /* [10:10] Enable BRC_DID_EIRQ for channel [x] - RW */
    ureg32 DID_EIRQ_EN10:1;           /* [11:11] Enable BRC_DID_EIRQ for channel [x] - RW */
    ureg32 DID_EIRQ_EN11:1;           /* [12:12] Enable BRC_DID_EIRQ for channel [x] - RW */
    ureg32 reserved_13:19;            /* [31:13] Internal  reserved */
} GTM_BRC_EIRQ_EN_Bits;

/* ICM Interrupt group register covering infrastructural and safety components (ARU - BRC - AEI - PSM0 - PSM1 - MAP - CMP,SPE) */
typedef struct
{
    ureg32 ARU_NEW_DATA0_IRQ:1;        /* [0:0] ARU_NEW_DATA0_I interrupt - RO */
    ureg32 ARU_NEW_DATA1_IRQ:1;        /* [1:1] ARU_NEW_DATA1_I interrupt - RO */
    ureg32 ARU_ACC_ACK_IRQ:1;          /* [2:2] ARU_ACC_ACK_I interrupt - RO */
    ureg32 BRC_IRQ:1;                  /* [3:3] BRC shared sub-module interrupt - RO */
    ureg32 AEI_IRQ:1;                  /* [4:4] ICM_IRQG_0.AEI_IRQ: AEI_IRQ interrupt - RO */
    ureg32 CMP_IRQ:1;                  /* [5:5] CMP shared sub-module interrupt - RO */
    ureg32 SPE0_IRQ:1;                 /* [6:6] SPE[j] shared sub-module interrupt - RO */
    ureg32 SPE1_IRQ:1;                 /* [7:7] SPE[j] shared sub-module interrupt - RO */
    ureg32 SPE2_IRQ:1;                 /* [8:8] SPE[j] shared sub-module interrupt - RO */
    ureg32 reserved_9:7;               /* [15:9] Internal  reserved */
    ureg32 PSM0_CH0_IRQ:1;             /* [16:16] PSM0 shared sub-module channel [x] interrupt. - RO */
    ureg32 PSM0_CH1_IRQ:1;             /* [17:17] PSM0 shared sub-module channel [x] interrupt. - RO */
    ureg32 PSM0_CH2_IRQ:1;             /* [18:18] PSM0 shared sub-module channel [x] interrupt. - RO */
    ureg32 PSM0_CH3_IRQ:1;             /* [19:19] PSM0 shared sub-module channel [x] interrupt. - RO */
    ureg32 PSM0_CH4_IRQ:1;             /* [20:20] PSM0 shared sub-module channel [x] interrupt. - RO */
    ureg32 PSM0_CH5_IRQ:1;             /* [21:21] PSM0 shared sub-module channel [x] interrupt. - RO */
    ureg32 PSM0_CH6_IRQ:1;             /* [22:22] PSM0 shared sub-module channel [x] interrupt. - RO */
    ureg32 PSM0_CH7_IRQ:1;             /* [23:23] PSM0 shared sub-module channel [x] interrupt. - RO */
    ureg32 PSM1_CH0_IRQ:1;             /* [24:24] PSM1 shared sub-module channel [x] interrupt. - RO */
    ureg32 PSM1_CH1_IRQ:1;             /* [25:25] PSM1 shared sub-module channel [x] interrupt. - RO */
    ureg32 PSM1_CH2_IRQ:1;             /* [26:26] PSM1 shared sub-module channel [x] interrupt. - RO */
    ureg32 PSM1_CH3_IRQ:1;             /* [27:27] PSM1 shared sub-module channel [x] interrupt. - RO */
    ureg32 PSM1_CH4_IRQ:1;             /* [28:28] PSM1 shared sub-module channel [x] interrupt. - RO */
    ureg32 PSM1_CH5_IRQ:1;             /* [29:29] PSM1 shared sub-module channel [x] interrupt. - RO */
    ureg32 PSM1_CH6_IRQ:1;             /* [30:30] PSM1 shared sub-module channel [x] interrupt. - RO */
    ureg32 PSM1_CH7_IRQ:1;             /* [31:31] PSM1 shared sub-module channel [x] interrupt. - RO */
} GTM_ICM_IRQG_0_Bits;

/* ICM Interrupt group register covering DPLL */
typedef struct
{
    ureg32 DPLL_DCGI_IRQ:1;        /* [0:0] TRIGGER direction change detected. - RO */
    ureg32 DPLL_EDI_IRQ:1;         /* [1:1] DPLL enable/disable interrupt - RO */
    ureg32 DPLL_TINI_IRQ:1;        /* [2:2] TRIGGER minimum hold time (THMI) violation detected interrupt.  - RO */
    ureg32 DPLL_TAXI_IRQ:1;        /* [3:3] TRIGGER maximum hold time (THMA) violation detected interrupt.  - RO */
    ureg32 DPLL_SISI_IRQ:1;        /* [4:4] STATE inactive slope detected interrupt.  - RO */
    ureg32 DPLL_TISI_IRQ:1;        /* [5:5] TRIGGER inactive slope detected interrupt.  - RO */
    ureg32 DPLL_MSI_IRQ:1;         /* [6:6] Missing STATE interrupt - RO */
    ureg32 DPLL_MTI_IRQ:1;         /* [7:7] Missing TRIGGER interrupt.  - RO */
    ureg32 DPLL_SASI_IRQ:1;        /* [8:8] STATE active slope detected.  - RO */
    ureg32 DPLL_TASI_IRQ:1;        /* [9:9] TRIGGER active slope detected while DPLL_NTI_CNT.NTI_CNT is zero.  - RO */
    ureg32 DPLL_PWI_IRQ:1;         /* [10:10] Plausibility window (PVT) violation interrupt of TRIGGER.  - RO */
    ureg32 DPLL_W2I_IRQ:1;         /* [11:11] Write access to RAM region 2 interrupt.  - RO */
    ureg32 DPLL_W1I_IRQ:1;         /* [12:12] Write access to RAM region 1b or 1c interrupt.  - RO */
    ureg32 DPLL_GL1I_IRQ:1;        /* [13:13] Get lock interrupt for SUB_INC1 - RO */
    ureg32 DPLL_LL1I_IRQ:1;        /* [14:14] Loss of lock interrupt for SUB_INC1 - RO */
    ureg32 DPLL_EI_IRQ:1;          /* [15:15] Error interrupt - RO */
    ureg32 DPLL_GL2I_IRQ:1;        /* [16:16] Get lock interrupt for SUB_INC2 - RO */
    ureg32 DPLL_LL2I_IRQ:1;        /* [17:17] Loss of lock interrupt for SUB_INC2 - RO */
    ureg32 DPLL_TE0I_IRQ:1;        /* [18:18] TRIGGER event interrupt 0 - RO */
    ureg32 DPLL_TE1I_IRQ:1;        /* [19:19] TRIGGER event interrupt 1 - RO */
    ureg32 DPLL_TE2I_IRQ:1;        /* [20:20] TRIGGER event interrupt 2 - RO */
    ureg32 DPLL_TE3I_IRQ:1;        /* [21:21] TRIGGER event interrupt 3 - RO */
    ureg32 DPLL_TE4I_IRQ:1;        /* [22:22] TRIGGER event interrupt 4 - RO */
    ureg32 DPLL_CDTI_IRQ:1;        /* [23:23] DPLL calculated duration interrupt for trigger.  - RO */
    ureg32 DPLL_CDSI_IRQ:1;        /* [24:24] DPLL calculated duration interrupt for state.  - RO */
    ureg32 DPLL_TORI_IRQ:1;        /* [25:25] DPLL calculated duration interrupt for state. - RO */
    ureg32 DPLL_SORI_IRQ:1;        /* [26:26] DPLL calculated duration interrupt for state. - RO */
    ureg32 reserved_27:5;          /* [31:27] Internal  reserved */
} GTM_ICM_IRQG_1_Bits;

/* ICM Interrupt group register covering TIM0 - TIM1 - TIM2 - TIM3 */
typedef struct
{
    ureg32 TIM0_CH0_IRQ:1;        /* [0:0] TIM0 shared interrupt channel [x] - RO */
    ureg32 TIM0_CH1_IRQ:1;        /* [1:1] TIM0 shared interrupt channel [x] - RO */
    ureg32 TIM0_CH2_IRQ:1;        /* [2:2] TIM0 shared interrupt channel [x] - RO */
    ureg32 TIM0_CH3_IRQ:1;        /* [3:3] TIM0 shared interrupt channel [x] - RO */
    ureg32 TIM0_CH4_IRQ:1;        /* [4:4] TIM0 shared interrupt channel [x] - RO */
    ureg32 TIM0_CH5_IRQ:1;        /* [5:5] TIM0 shared interrupt channel [x] - RO */
    ureg32 TIM0_CH6_IRQ:1;        /* [6:6] TIM0 shared interrupt channel [x] - RO */
    ureg32 TIM0_CH7_IRQ:1;        /* [7:7] TIM0 shared interrupt channel [x] - RO */
    ureg32 TIM1_CH0_IRQ:1;        /* [8:8] TIM1 shared interrupt channel [x] - RO */
    ureg32 TIM1_CH1_IRQ:1;        /* [9:9] TIM1 shared interrupt channel [x] - RO */
    ureg32 TIM1_CH2_IRQ:1;        /* [10:10] TIM1 shared interrupt channel [x] - RO */
    ureg32 TIM1_CH3_IRQ:1;        /* [11:11] TIM1 shared interrupt channel [x] - RO */
    ureg32 TIM1_CH4_IRQ:1;        /* [12:12] TIM1 shared interrupt channel [x] - RO */
    ureg32 TIM1_CH5_IRQ:1;        /* [13:13] TIM1 shared interrupt channel [x] - RO */
    ureg32 TIM1_CH6_IRQ:1;        /* [14:14] TIM1 shared interrupt channel [x] - RO */
    ureg32 TIM1_CH7_IRQ:1;        /* [15:15] TIM1 shared interrupt channel [x] - RO */
    ureg32 TIM2_CH0_IRQ:1;        /* [16:16] TIM2 shared interrupt channel [x] - RO */
    ureg32 TIM2_CH1_IRQ:1;        /* [17:17] TIM2 shared interrupt channel [x] - RO */
    ureg32 TIM2_CH2_IRQ:1;        /* [18:18] TIM2 shared interrupt channel [x] - RO */
    ureg32 TIM2_CH3_IRQ:1;        /* [19:19] TIM2 shared interrupt channel [x] - RO */
    ureg32 TIM2_CH4_IRQ:1;        /* [20:20] TIM2 shared interrupt channel [x] - RO */
    ureg32 TIM2_CH5_IRQ:1;        /* [21:21] TIM2 shared interrupt channel [x] - RO */
    ureg32 TIM2_CH6_IRQ:1;        /* [22:22] TIM2 shared interrupt channel [x] - RO */
    ureg32 TIM2_CH7_IRQ:1;        /* [23:23] TIM2 shared interrupt channel [x] - RO */
    ureg32 TIM3_CH0_IRQ:1;        /* [24:24] TIM3 shared interrupt channel [x] - RO */
    ureg32 TIM3_CH1_IRQ:1;        /* [25:25] TIM3 shared interrupt channel [x] - RO */
    ureg32 TIM3_CH2_IRQ:1;        /* [26:26] TIM3 shared interrupt channel [x] - RO */
    ureg32 TIM3_CH3_IRQ:1;        /* [27:27] TIM3 shared interrupt channel [x] - RO */
    ureg32 TIM3_CH4_IRQ:1;        /* [28:28] TIM3 shared interrupt channel [x] - RO */
    ureg32 TIM3_CH5_IRQ:1;        /* [29:29] TIM3 shared interrupt channel [x] - RO */
    ureg32 TIM3_CH6_IRQ:1;        /* [30:30] TIM3 shared interrupt channel [x] - RO */
    ureg32 TIM3_CH7_IRQ:1;        /* [31:31] TIM3 shared interrupt channel [x] - RO */
} GTM_ICM_IRQG_2_Bits;

/* ICM Interrupt group register covering TIM4 - TIM5 - TIM6 - TIM7 */
typedef struct
{
    ureg32 TIM4_CH0_IRQ:1;        /* [0:0] TIM4 shared interrupt channel [x] - RO */
    ureg32 TIM4_CH1_IRQ:1;        /* [1:1] TIM4 shared interrupt channel [x] - RO */
    ureg32 TIM4_CH2_IRQ:1;        /* [2:2] TIM4 shared interrupt channel [x] - RO */
    ureg32 TIM4_CH3_IRQ:1;        /* [3:3] TIM4 shared interrupt channel [x] - RO */
    ureg32 TIM4_CH4_IRQ:1;        /* [4:4] TIM4 shared interrupt channel [x] - RO */
    ureg32 TIM4_CH5_IRQ:1;        /* [5:5] TIM4 shared interrupt channel [x] - RO */
    ureg32 TIM4_CH6_IRQ:1;        /* [6:6] TIM4 shared interrupt channel [x] - RO */
    ureg32 TIM4_CH7_IRQ:1;        /* [7:7] TIM4 shared interrupt channel [x] - RO */
    ureg32 TIM5_CH0_IRQ:1;        /* [8:8] TIM5 shared interrupt channel [x] - RO */
    ureg32 TIM5_CH1_IRQ:1;        /* [9:9] TIM5 shared interrupt channel [x] - RO */
    ureg32 TIM5_CH2_IRQ:1;        /* [10:10] TIM5 shared interrupt channel [x] - RO */
    ureg32 TIM5_CH3_IRQ:1;        /* [11:11] TIM5 shared interrupt channel [x] - RO */
    ureg32 TIM5_CH4_IRQ:1;        /* [12:12] TIM5 shared interrupt channel [x] - RO */
    ureg32 TIM5_CH5_IRQ:1;        /* [13:13] TIM5 shared interrupt channel [x] - RO */
    ureg32 TIM5_CH6_IRQ:1;        /* [14:14] TIM5 shared interrupt channel [x] - RO */
    ureg32 TIM5_CH7_IRQ:1;        /* [15:15] TIM5 shared interrupt channel [x] - RO */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_ICM_IRQG_3_Bits;

/* ICM Interrupt group register covering MCS0 to MCS3 sub-modules */
typedef struct
{
    ureg32 MCS0_CH0_IRQ:1;        /* [0:0] MCS0 channel [x] interrupt - RO */
    ureg32 MCS0_CH1_IRQ:1;        /* [1:1] MCS0 channel [x] interrupt - RO */
    ureg32 MCS0_CH2_IRQ:1;        /* [2:2] MCS0 channel [x] interrupt - RO */
    ureg32 MCS0_CH3_IRQ:1;        /* [3:3] MCS0 channel [x] interrupt - RO */
    ureg32 MCS0_CH4_IRQ:1;        /* [4:4] MCS0 channel [x] interrupt - RO */
    ureg32 MCS0_CH5_IRQ:1;        /* [5:5] MCS0 channel [x] interrupt - RO */
    ureg32 MCS0_CH6_IRQ:1;        /* [6:6] MCS0 channel [x] interrupt - RO */
    ureg32 MCS0_CH7_IRQ:1;        /* [7:7] MCS0 channel [x] interrupt - RO */
    ureg32 MCS1_CH0_IRQ:1;        /* [8:8] MCS1 channel [x] interrupt - RO */
    ureg32 MCS1_CH1_IRQ:1;        /* [9:9] MCS1 channel [x] interrupt - RO */
    ureg32 MCS1_CH2_IRQ:1;        /* [10:10] MCS1 channel [x] interrupt - RO */
    ureg32 MCS1_CH3_IRQ:1;        /* [11:11] MCS1 channel [x] interrupt - RO */
    ureg32 MCS1_CH4_IRQ:1;        /* [12:12] MCS1 channel [x] interrupt - RO */
    ureg32 MCS1_CH5_IRQ:1;        /* [13:13] MCS1 channel [x] interrupt - RO */
    ureg32 MCS1_CH6_IRQ:1;        /* [14:14] MCS1 channel [x] interrupt - RO */
    ureg32 MCS1_CH7_IRQ:1;        /* [15:15] MCS1 channel [x] interrupt - RO */
    ureg32 MCS2_CH0_IRQ:1;        /* [16:16] MCS2 channel [x] interrupt - RO */
    ureg32 MCS2_CH1_IRQ:1;        /* [17:17] MCS2 channel [x] interrupt - RO */
    ureg32 MCS2_CH2_IRQ:1;        /* [18:18] MCS2 channel [x] interrupt - RO */
    ureg32 MCS2_CH3_IRQ:1;        /* [19:19] MCS2 channel [x] interrupt - RO */
    ureg32 MCS2_CH4_IRQ:1;        /* [20:20] MCS2 channel [x] interrupt - RO */
    ureg32 MCS2_CH5_IRQ:1;        /* [21:21] MCS2 channel [x] interrupt - RO */
    ureg32 MCS2_CH6_IRQ:1;        /* [22:22] MCS2 channel [x] interrupt - RO */
    ureg32 MCS2_CH7_IRQ:1;        /* [23:23] MCS2 channel [x] interrupt - RO */
    ureg32 MCS3_CH0_IRQ:1;        /* [24:24] MCS3 channel [x] interrupt - RO */
    ureg32 MCS3_CH1_IRQ:1;        /* [25:25] MCS3 channel [x] interrupt - RO */
    ureg32 MCS3_CH2_IRQ:1;        /* [26:26] MCS3 channel [x] interrupt - RO */
    ureg32 MCS3_CH3_IRQ:1;        /* [27:27] MCS3 channel [x] interrupt - RO */
    ureg32 MCS3_CH4_IRQ:1;        /* [28:28] MCS3 channel [x] interrupt - RO */
    ureg32 MCS3_CH5_IRQ:1;        /* [29:29] MCS3 channel [x] interrupt - RO */
    ureg32 MCS3_CH6_IRQ:1;        /* [30:30] MCS3 channel [x] interrupt - RO */
    ureg32 MCS3_CH7_IRQ:1;        /* [31:31] MCS3 channel [x] interrupt - RO */
} GTM_ICM_IRQG_4_Bits;

/* ICM Interrupt group register covering MCS4 to MCS7 sub-modules */
typedef struct
{
    ureg32 MCS4_CH0_IRQ:1;        /* [0:0] MCS4 channel [x] interrupt - RO */
    ureg32 MCS4_CH1_IRQ:1;        /* [1:1] MCS4 channel [x] interrupt - RO */
    ureg32 MCS4_CH2_IRQ:1;        /* [2:2] MCS4 channel [x] interrupt - RO */
    ureg32 MCS4_CH3_IRQ:1;        /* [3:3] MCS4 channel [x] interrupt - RO */
    ureg32 MCS4_CH4_IRQ:1;        /* [4:4] MCS4 channel [x] interrupt - RO */
    ureg32 MCS4_CH5_IRQ:1;        /* [5:5] MCS4 channel [x] interrupt - RO */
    ureg32 MCS4_CH6_IRQ:1;        /* [6:6] MCS4 channel [x] interrupt - RO */
    ureg32 MCS4_CH7_IRQ:1;        /* [7:7] MCS4 channel [x] interrupt - RO */
    ureg32 reserved_8:24;         /* [31:8] Internal  reserved */
} GTM_ICM_IRQG_5_Bits;

/* ICM Interrupt group register for module error interrupt information */
typedef struct
{
    ureg32 GTM_EIRQ:1;           /* [0:0] AEI error interrupt request - RO */
    ureg32 BRC_EIRQ:1;           /* [1:1] BRC error interrupt - RO */
    ureg32 FIFO0_EIRQ:1;         /* [2:2] FIFO[j] error interrupt - RO */
    ureg32 FIFO1_EIRQ:1;         /* [3:3] FIFO[j] error interrupt - RO */
    ureg32 TIM0_EIRQ:1;          /* [4:4] TIM[j] error interrupt - RO */
    ureg32 TIM1_EIRQ:1;          /* [5:5] TIM[j] error interrupt - RO */
    ureg32 TIM2_EIRQ:1;          /* [6:6] TIM[j] error interrupt - RO */
    ureg32 TIM3_EIRQ:1;          /* [7:7] TIM[j] error interrupt - RO */
    ureg32 TIM4_EIRQ:1;          /* [8:8] TIM[j] error interrupt - RO */
    ureg32 TIM5_EIRQ:1;          /* [9:9] TIM[j] error interrupt - RO */
    ureg32 reserved_10:2;        /* [11:10] Internal  reserved */
    ureg32 MCS0_EIRQ:1;          /* [12:12] MCS[j] error interrupt - RO */
    ureg32 MCS1_EIRQ:1;          /* [13:13] MCS[j] error interrupt - RO */
    ureg32 MCS2_EIRQ:1;          /* [14:14] MCS[j] error interrupt - RO */
    ureg32 MCS3_EIRQ:1;          /* [15:15] MCS[j] error interrupt - RO */
    ureg32 MCS4_EIRQ:1;          /* [16:16] MCS[j] error interrupt - RO */
    ureg32 reserved_17:3;        /* [19:17] Internal  reserved */
    ureg32 SPE0_EIRQ:1;          /* [20:20] SPE[j] error interrupt - RO */
    ureg32 SPE1_EIRQ:1;          /* [21:21] SPE[j] error interrupt - RO */
    ureg32 SPE2_EIRQ:1;          /* [22:22] SPE[j] error interrupt - RO */
    ureg32 reserved_23:1;        /* [23:23] Internal  reserved */
    ureg32 CMP_EIRQ:1;           /* [24:24] CMP error interrupt - RO */
    ureg32 DPLL_EIRQ:1;          /* [25:25] DPLL error interrupt - RO */
    ureg32 reserved_26:6;        /* [31:26] Internal  reserved */
} GTM_ICM_IRQG_MEI_Bits;

/* ICM Interrupt group register 0 for channel error interrupt information */
typedef struct
{
    ureg32 FIFO0_CH0_EIRQ:1;        /* [0:0] FIFO0 channel [x] error interrupt - RO */
    ureg32 FIFO0_CH1_EIRQ:1;        /* [1:1] FIFO0 channel [x] error interrupt - RO */
    ureg32 FIFO0_CH2_EIRQ:1;        /* [2:2] FIFO0 channel [x] error interrupt - RO */
    ureg32 FIFO0_CH3_EIRQ:1;        /* [3:3] FIFO0 channel [x] error interrupt - RO */
    ureg32 FIFO0_CH4_EIRQ:1;        /* [4:4] FIFO0 channel [x] error interrupt - RO */
    ureg32 FIFO0_CH5_EIRQ:1;        /* [5:5] FIFO0 channel [x] error interrupt - RO */
    ureg32 FIFO0_CH6_EIRQ:1;        /* [6:6] FIFO0 channel [x] error interrupt - RO */
    ureg32 FIFO0_CH7_EIRQ:1;        /* [7:7] FIFO0 channel [x] error interrupt - RO */
    ureg32 FIFO1_CH0_EIRQ:1;        /* [8:8] FIFO1 channel [x] error interrupt - RO */
    ureg32 FIFO1_CH1_EIRQ:1;        /* [9:9] FIFO1 channel [x] error interrupt - RO */
    ureg32 FIFO1_CH2_EIRQ:1;        /* [10:10] FIFO1 channel [x] error interrupt - RO */
    ureg32 FIFO1_CH3_EIRQ:1;        /* [11:11] FIFO1 channel [x] error interrupt - RO */
    ureg32 FIFO1_CH4_EIRQ:1;        /* [12:12] FIFO1 channel [x] error interrupt - RO */
    ureg32 FIFO1_CH5_EIRQ:1;        /* [13:13] FIFO1 channel [x] error interrupt - RO */
    ureg32 FIFO1_CH6_EIRQ:1;        /* [14:14] FIFO1 channel [x] error interrupt - RO */
    ureg32 FIFO1_CH7_EIRQ:1;        /* [15:15] FIFO1 channel [x] error interrupt - RO */
    ureg32 FIFO2_CH0_EIRQ:1;        /* [16:16] FIFO2 channel [x] error interrupt - RO */
    ureg32 FIFO2_CH1_EIRQ:1;        /* [17:17] FIFO2 channel [x] error interrupt - RO */
    ureg32 FIFO2_CH2_EIRQ:1;        /* [18:18] FIFO2 channel [x] error interrupt - RO */
    ureg32 FIFO2_CH3_EIRQ:1;        /* [19:19] FIFO2 channel [x] error interrupt - RO */
    ureg32 FIFO2_CH4_EIRQ:1;        /* [20:20] FIFO2 channel [x] error interrupt - RO */
    ureg32 FIFO2_CH5_EIRQ:1;        /* [21:21] FIFO2 channel [x] error interrupt - RO */
    ureg32 FIFO2_CH6_EIRQ:1;        /* [22:22] FIFO2 channel [x] error interrupt - RO */
    ureg32 FIFO2_CH7_EIRQ:1;        /* [23:23] FIFO2 channel [x] error interrupt - RO */
    ureg32 reserved_24:8;           /* [31:24] Internal  reserved */
} GTM_ICM_IRQG_CEI0_Bits;

/* ICM Interrupt group register 1 for channel error interrupt information */
typedef struct
{
    ureg32 TIM0_CH0_EIRQ:1;        /* [0:0] TIM0 channel [x] error interrupt - RO */
    ureg32 TIM0_CH1_EIRQ:1;        /* [1:1] TIM0 channel [x] error interrupt - RO */
    ureg32 TIM0_CH2_EIRQ:1;        /* [2:2] TIM0 channel [x] error interrupt - RO */
    ureg32 TIM0_CH3_EIRQ:1;        /* [3:3] TIM0 channel [x] error interrupt - RO */
    ureg32 TIM0_CH4_EIRQ:1;        /* [4:4] TIM0 channel [x] error interrupt - RO */
    ureg32 TIM0_CH5_EIRQ:1;        /* [5:5] TIM0 channel [x] error interrupt - RO */
    ureg32 TIM0_CH6_EIRQ:1;        /* [6:6] TIM0 channel [x] error interrupt - RO */
    ureg32 TIM0_CH7_EIRQ:1;        /* [7:7] TIM0 channel [x] error interrupt - RO */
    ureg32 TIM1_CH0_EIRQ:1;        /* [8:8] TIM1 channel [x] error interrupt - RO */
    ureg32 TIM1_CH1_EIRQ:1;        /* [9:9] TIM1 channel [x] error interrupt - RO */
    ureg32 TIM1_CH2_EIRQ:1;        /* [10:10] TIM1 channel [x] error interrupt - RO */
    ureg32 TIM1_CH3_EIRQ:1;        /* [11:11] TIM1 channel [x] error interrupt - RO */
    ureg32 TIM1_CH4_EIRQ:1;        /* [12:12] TIM1 channel [x] error interrupt - RO */
    ureg32 TIM1_CH5_EIRQ:1;        /* [13:13] TIM1 channel [x] error interrupt - RO */
    ureg32 TIM1_CH6_EIRQ:1;        /* [14:14] TIM1 channel [x] error interrupt - RO */
    ureg32 TIM1_CH7_EIRQ:1;        /* [15:15] TIM1 channel [x] error interrupt - RO */
    ureg32 TIM2_CH0_EIRQ:1;        /* [16:16] TIM2 channel [x] error interrupt - RO */
    ureg32 TIM2_CH1_EIRQ:1;        /* [17:17] TIM2 channel [x] error interrupt - RO */
    ureg32 TIM2_CH2_EIRQ:1;        /* [18:18] TIM2 channel [x] error interrupt - RO */
    ureg32 TIM2_CH3_EIRQ:1;        /* [19:19] TIM2 channel [x] error interrupt - RO */
    ureg32 TIM2_CH4_EIRQ:1;        /* [20:20] TIM2 channel [x] error interrupt - RO */
    ureg32 TIM2_CH5_EIRQ:1;        /* [21:21] TIM2 channel [x] error interrupt - RO */
    ureg32 TIM2_CH6_EIRQ:1;        /* [22:22] TIM2 channel [x] error interrupt - RO */
    ureg32 TIM2_CH7_EIRQ:1;        /* [23:23] TIM2 channel [x] error interrupt - RO */
    ureg32 TIM3_CH0_EIRQ:1;        /* [24:24] TIM3 channel [x] error interrupt - RO */
    ureg32 TIM3_CH1_EIRQ:1;        /* [25:25] TIM3 channel [x] error interrupt - RO */
    ureg32 TIM3_CH2_EIRQ:1;        /* [26:26] TIM3 channel [x] error interrupt - RO */
    ureg32 TIM3_CH3_EIRQ:1;        /* [27:27] TIM3 channel [x] error interrupt - RO */
    ureg32 TIM3_CH4_EIRQ:1;        /* [28:28] TIM3 channel [x] error interrupt - RO */
    ureg32 TIM3_CH5_EIRQ:1;        /* [29:29] TIM3 channel [x] error interrupt - RO */
    ureg32 TIM3_CH6_EIRQ:1;        /* [30:30] TIM3 channel [x] error interrupt - RO */
    ureg32 TIM3_CH7_EIRQ:1;        /* [31:31] TIM3 channel [x] error interrupt - RO */
} GTM_ICM_IRQG_CEI1_Bits;

/* ICM Interrupt group register 2 for channel error interrupt information */
typedef struct
{
    ureg32 TIM4_CH0_EIRQ:1;        /* [0:0] TIM4 channel [x] error interrupt - RO */
    ureg32 TIM4_CH1_EIRQ:1;        /* [1:1] TIM4 channel [x] error interrupt - RO */
    ureg32 TIM4_CH2_EIRQ:1;        /* [2:2] TIM4 channel [x] error interrupt - RO */
    ureg32 TIM4_CH3_EIRQ:1;        /* [3:3] TIM4 channel [x] error interrupt - RO */
    ureg32 TIM4_CH4_EIRQ:1;        /* [4:4] TIM4 channel [x] error interrupt - RO */
    ureg32 TIM4_CH5_EIRQ:1;        /* [5:5] TIM4 channel [x] error interrupt - RO */
    ureg32 TIM4_CH6_EIRQ:1;        /* [6:6] TIM4 channel [x] error interrupt - RO */
    ureg32 TIM4_CH7_EIRQ:1;        /* [7:7] TIM4 channel [x] error interrupt - RO */
    ureg32 TIM5_CH0_EIRQ:1;        /* [8:8] TIM5 channel [x] error interrupt - RO */
    ureg32 TIM5_CH1_EIRQ:1;        /* [9:9] TIM5 channel [x] error interrupt - RO */
    ureg32 TIM5_CH2_EIRQ:1;        /* [10:10] TIM5 channel [x] error interrupt - RO */
    ureg32 TIM5_CH3_EIRQ:1;        /* [11:11] TIM5 channel [x] error interrupt - RO */
    ureg32 TIM5_CH4_EIRQ:1;        /* [12:12] TIM5 channel [x] error interrupt - RO */
    ureg32 TIM5_CH5_EIRQ:1;        /* [13:13] TIM5 channel [x] error interrupt - RO */
    ureg32 TIM5_CH6_EIRQ:1;        /* [14:14] TIM5 channel [x] error interrupt - RO */
    ureg32 TIM5_CH7_EIRQ:1;        /* [15:15] TIM5 channel [x] error interrupt - RO */
    ureg32 reserved_16:16;         /* [31:16] Internal  reserved */
} GTM_ICM_IRQG_CEI2_Bits;

/* ICM Interrupt group register 3 for channel error interrupt information */
typedef struct
{
    ureg32 MCS0_CH0_EIRQ:1;        /* [0:0] MCS0 channel [x] error interrupt - RO */
    ureg32 MCS0_CH1_EIRQ:1;        /* [1:1] MCS0 channel [x] error interrupt - RO */
    ureg32 MCS0_CH2_EIRQ:1;        /* [2:2] MCS0 channel [x] error interrupt - RO */
    ureg32 MCS0_CH3_EIRQ:1;        /* [3:3] MCS0 channel [x] error interrupt - RO */
    ureg32 MCS0_CH4_EIRQ:1;        /* [4:4] MCS0 channel [x] error interrupt - RO */
    ureg32 MCS0_CH5_EIRQ:1;        /* [5:5] MCS0 channel [x] error interrupt - RO */
    ureg32 MCS0_CH6_EIRQ:1;        /* [6:6] MCS0 channel [x] error interrupt - RO */
    ureg32 MCS0_CH7_EIRQ:1;        /* [7:7] MCS0 channel [x] error interrupt - RO */
    ureg32 MCS1_CH0_EIRQ:1;        /* [8:8] MCS1 channel [x] error interrupt - RO */
    ureg32 MCS1_CH1_EIRQ:1;        /* [9:9] MCS1 channel [x] error interrupt - RO */
    ureg32 MCS1_CH2_EIRQ:1;        /* [10:10] MCS1 channel [x] error interrupt - RO */
    ureg32 MCS1_CH3_EIRQ:1;        /* [11:11] MCS1 channel [x] error interrupt - RO */
    ureg32 MCS1_CH4_EIRQ:1;        /* [12:12] MCS1 channel [x] error interrupt - RO */
    ureg32 MCS1_CH5_EIRQ:1;        /* [13:13] MCS1 channel [x] error interrupt - RO */
    ureg32 MCS1_CH6_EIRQ:1;        /* [14:14] MCS1 channel [x] error interrupt - RO */
    ureg32 MCS1_CH7_EIRQ:1;        /* [15:15] MCS1 channel [x] error interrupt - RO */
    ureg32 MCS2_CH0_EIRQ:1;        /* [16:16] MCS2 channel [x] error interrupt - RO */
    ureg32 MCS2_CH1_EIRQ:1;        /* [17:17] MCS2 channel [x] error interrupt - RO */
    ureg32 MCS2_CH2_EIRQ:1;        /* [18:18] MCS2 channel [x] error interrupt - RO */
    ureg32 MCS2_CH3_EIRQ:1;        /* [19:19] MCS2 channel [x] error interrupt - RO */
    ureg32 MCS2_CH4_EIRQ:1;        /* [20:20] MCS2 channel [x] error interrupt - RO */
    ureg32 MCS2_CH5_EIRQ:1;        /* [21:21] MCS2 channel [x] error interrupt - RO */
    ureg32 MCS2_CH6_EIRQ:1;        /* [22:22] MCS2 channel [x] error interrupt - RO */
    ureg32 MCS2_CH7_EIRQ:1;        /* [23:23] MCS2 channel [x] error interrupt - RO */
    ureg32 MCS3_CH0_EIRQ:1;        /* [24:24] MCS3 channel [x] error interrupt - RO */
    ureg32 MCS3_CH1_EIRQ:1;        /* [25:25] MCS3 channel [x] error interrupt - RO */
    ureg32 MCS3_CH2_EIRQ:1;        /* [26:26] MCS3 channel [x] error interrupt - RO */
    ureg32 MCS3_CH3_EIRQ:1;        /* [27:27] MCS3 channel [x] error interrupt - RO */
    ureg32 MCS3_CH4_EIRQ:1;        /* [28:28] MCS3 channel [x] error interrupt - RO */
    ureg32 MCS3_CH5_EIRQ:1;        /* [29:29] MCS3 channel [x] error interrupt - RO */
    ureg32 MCS3_CH6_EIRQ:1;        /* [30:30] MCS3 channel [x] error interrupt - RO */
    ureg32 MCS3_CH7_EIRQ:1;        /* [31:31] MCS3 channel [x] error interrupt - RO */
} GTM_ICM_IRQG_CEI3_Bits;

/* ICM Interrupt group register 4 for channel error interrupt information */
typedef struct
{
    ureg32 MCS4_CH0_EIRQ:1;        /* [0:0] MCS4 channel [x] error interrupt - RO */
    ureg32 MCS4_CH1_EIRQ:1;        /* [1:1] MCS4 channel [x] error interrupt - RO */
    ureg32 MCS4_CH2_EIRQ:1;        /* [2:2] MCS4 channel [x] error interrupt - RO */
    ureg32 MCS4_CH3_EIRQ:1;        /* [3:3] MCS4 channel [x] error interrupt - RO */
    ureg32 MCS4_CH4_EIRQ:1;        /* [4:4] MCS4 channel [x] error interrupt - RO */
    ureg32 MCS4_CH5_EIRQ:1;        /* [5:5] MCS4 channel [x] error interrupt - RO */
    ureg32 MCS4_CH6_EIRQ:1;        /* [6:6] MCS4 channel [x] error interrupt - RO */
    ureg32 MCS4_CH7_EIRQ:1;        /* [7:7] MCS4 channel [x] error interrupt - RO */
    ureg32 reserved_8:24;          /* [31:8] Internal  reserved */
} GTM_ICM_IRQG_CEI4_Bits;

/* ICM Interrupt group MCS[j] for Channel Error Interrupt information */
typedef struct
{
    ureg32 MCS_CH0_EIRQ:1;        /* [0:0] MCS channel [x] error interrupt - RO */
    ureg32 MCS_CH1_EIRQ:1;        /* [1:1] MCS channel [x] error interrupt - RO */
    ureg32 MCS_CH2_EIRQ:1;        /* [2:2] MCS channel [x] error interrupt - RO */
    ureg32 MCS_CH3_EIRQ:1;        /* [3:3] MCS channel [x] error interrupt - RO */
    ureg32 MCS_CH4_EIRQ:1;        /* [4:4] MCS channel [x] error interrupt - RO */
    ureg32 MCS_CH5_EIRQ:1;        /* [5:5] MCS channel [x] error interrupt - RO */
    ureg32 MCS_CH6_EIRQ:1;        /* [6:6] MCS channel [x] error interrupt - RO */
    ureg32 MCS_CH7_EIRQ:1;        /* [7:7] MCS channel [x] error interrupt - RO */
    ureg32 reserved_8:24;         /* [31:8] Internal  reserved */
} GTM_ICM_IRQG_MCS_CEI_Bits;

/* ICM Interrupt group PSM 0 for Channel Error Interrupt information of FIFO0 - FIFO1 - FIFO2 */
typedef struct
{
    ureg32 PSM_M0_CH0_EIRQ:1;        /* [0:0] PSMm channel [x] error interrupt ([j]=4*0+0) - RO */
    ureg32 PSM_M0_CH1_EIRQ:1;        /* [1:1] PSMm channel [x] error interrupt ([j]=4*0+0) - RO */
    ureg32 PSM_M0_CH2_EIRQ:1;        /* [2:2] PSMm channel [x] error interrupt ([j]=4*0+0) - RO */
    ureg32 PSM_M0_CH3_EIRQ:1;        /* [3:3] PSMm channel [x] error interrupt ([j]=4*0+0) - RO */
    ureg32 PSM_M0_CH4_EIRQ:1;        /* [4:4] PSMm channel [x] error interrupt ([j]=4*0+0) - RO */
    ureg32 PSM_M0_CH5_EIRQ:1;        /* [5:5] PSMm channel [x] error interrupt ([j]=4*0+0) - RO */
    ureg32 PSM_M0_CH6_EIRQ:1;        /* [6:6] PSMm channel [x] error interrupt ([j]=4*0+0) - RO */
    ureg32 PSM_M0_CH7_EIRQ:1;        /* [7:7] PSMm channel [x] error interrupt ([j]=4*0+0) - RO */
    ureg32 PSM_M1_CH0_EIRQ:1;        /* [8:8] PSM[j] channel [x] error interrupt ([j]=4*0+1) - RO */
    ureg32 PSM_M1_CH1_EIRQ:1;        /* [9:9] PSM[j] channel [x] error interrupt ([j]=4*0+1) - RO */
    ureg32 PSM_M1_CH2_EIRQ:1;        /* [10:10] PSM[j] channel [x] error interrupt ([j]=4*0+1) - RO */
    ureg32 PSM_M1_CH3_EIRQ:1;        /* [11:11] PSM[j] channel [x] error interrupt ([j]=4*0+1) - RO */
    ureg32 PSM_M1_CH4_EIRQ:1;        /* [12:12] PSM[j] channel [x] error interrupt ([j]=4*0+1) - RO */
    ureg32 PSM_M1_CH5_EIRQ:1;        /* [13:13] PSM[j] channel [x] error interrupt ([j]=4*0+1) - RO */
    ureg32 PSM_M1_CH6_EIRQ:1;        /* [14:14] PSM[j] channel [x] error interrupt ([j]=4*0+1) - RO */
    ureg32 PSM_M1_CH7_EIRQ:1;        /* [15:15] PSM[j] channel [x] error interrupt ([j]=4*0+1) - RO */
    ureg32 PSM_M2_CH0_EIRQ:1;        /* [16:16] PSM[j] channel [x] error interrupt ([j]=4*0+2) - RO */
    ureg32 PSM_M2_CH1_EIRQ:1;        /* [17:17] PSM[j] channel [x] error interrupt ([j]=4*0+2) - RO */
    ureg32 PSM_M2_CH2_EIRQ:1;        /* [18:18] PSM[j] channel [x] error interrupt ([j]=4*0+2) - RO */
    ureg32 PSM_M2_CH3_EIRQ:1;        /* [19:19] PSM[j] channel [x] error interrupt ([j]=4*0+2) - RO */
    ureg32 PSM_M2_CH4_EIRQ:1;        /* [20:20] PSM[j] channel [x] error interrupt ([j]=4*0+2) - RO */
    ureg32 PSM_M2_CH5_EIRQ:1;        /* [21:21] PSM[j] channel [x] error interrupt ([j]=4*0+2) - RO */
    ureg32 PSM_M2_CH6_EIRQ:1;        /* [22:22] PSM[j] channel [x] error interrupt ([j]=4*0+2) - RO */
    ureg32 PSM_M2_CH7_EIRQ:1;        /* [23:23] PSM[j] channel [x] error interrupt ([j]=4*0+2) - RO */
    ureg32 reserved_24:8;            /* [31:24] Internal  reserved */
} GTM_ICM_IRQG_PSM_CEI_Bits;

/* ICM Interrupt group SPE for module Error Interrupt information */
typedef struct
{
    ureg32 SPE0_EIRQ:1;          /* [0:0] SPE[j] error interrupt - RO */
    ureg32 SPE1_EIRQ:1;          /* [1:1] SPE[j] error interrupt - RO */
    ureg32 SPE2_EIRQ:1;          /* [2:2] SPE[j] error interrupt - RO */
    ureg32 reserved_3:29;        /* [31:3] Internal  reserved */
} GTM_ICM_IRQG_SPE_CEI_Bits;

/* ICM Interrupt group for module Error Interrupt information for each TIM[j] - MCS[j] - SPE[j] - FIFO[j] (j=4*[g]+k, k=0-3) */
typedef struct
{
    ureg32 TIM_M0_EIRQ:1;         /* [0:0] Error interrupt TIM[j]_EIRQ (j=4*[g]) - RO */
    ureg32 MCS_M0_EIRQ:1;         /* [1:1] Error interrupt MCS[j]_EIRQ (j=4*[g]) - RO */
    ureg32 SPE_M0_EIRQ:1;         /* [2:2] Error interrupt SPE[j]_EIRQ ([j]=4*[g]+0) - RO */
    ureg32 FIFO_M0_EIRQ:1;        /* [3:3] Error interrupt FIFO[j]_EIRQ ([j]=4*[g]+0) - RO */
    ureg32 reserved_4:4;          /* [7:4] Internal  reserved */
    ureg32 TIM_M1_EIRQ:1;         /* [8:8] Error interrupt TIM[j]_EIRQ ([j]=4*[g]+1) - RO */
    ureg32 MCS_M1_EIRQ:1;         /* [9:9] Error interrupt MCS[j]_EIRQ ([j]=4*[g]+1) - RO */
    ureg32 SPE_M1_EIRQ:1;         /* [10:10] Error interrupt SPE[j]_EIRQ ([j]=4*[g]+1) - RO */
    ureg32 FIFO_M1_EIRQ:1;        /* [11:11] Error interrupt FIFO[j]_EIRQ ([j]=4*[g]+1) - RO */
    ureg32 reserved_12:4;         /* [15:12] Internal  reserved */
    ureg32 TIM_M2_EIRQ:1;         /* [16:16] Error interrupt TIM[j]_EIRQ ([j]=4*[g]+2) - RO */
    ureg32 MCS_M2_EIRQ:1;         /* [17:17] Error interrupt MCS[j]_EIRQ ([j]=4*[g]+2) - RO */
    ureg32 SPE_M2_EIRQ:1;         /* [18:18] Error interrupt SPE[j]_EIRQ ([j]=4*[g]+2) - RO */
    ureg32 FIFO_M2_EIRQ:1;        /* [19:19] Error interrupt FIFO[j]_EIRQ ([j]=4*[g]+2) - RO */
    ureg32 reserved_20:4;         /* [23:20] Internal  reserved */
    ureg32 TIM_M3_EIRQ:1;         /* [24:24] Error interrupt TIM[j]_EIRQ ([j]=4*[g]+3) - RO */
    ureg32 MCS_M3_EIRQ:1;         /* [25:25] Error interrupt MCS[j]_EIRQ ([j]=4*[g]+3) - RO */
    ureg32 reserved_26:6;         /* [31:26] Internal  reserved */
} GTM_ICM_IRQG_CLS_0_MEI_Bits;

/* ICM Interrupt group for module Error Interrupt information for each TIM[j] - MCS[j] - SPE[j] - FIFO[j] (j=4*[g]+k - k, k=0-3{0 - ... ,3}) */
typedef struct
{
    ureg32 TIM_M0_EIRQ:1;        /* [0:0] Error interrupt TIM[j]_EIRQ (j=4*[g]) - RO */
    ureg32 MCS_M0_EIRQ:1;        /* [1:1] Error interrupt MCS[j]_EIRQ (j=4*[g]) - RO */
    ureg32 reserved_2:6;         /* [7:2] Internal  reserved */
    ureg32 TIM_M1_EIRQ:1;        /* [8:8] Error interrupt TIM[j]_EIRQ ([j]=4*[g]+1) - RO */
    ureg32 reserved_9:23;        /* [31:9] Internal  reserved */
} GTM_ICM_IRQG_CLS_1_MEI_Bits;

/* ICM Interrupt group MCS[j] for Channel Interrupt information */
typedef struct
{
    ureg32 MCS_CH0_IRQ:1;        /* [0:0] MCS channel [x] interrupt - RO */
    ureg32 MCS_CH1_IRQ:1;        /* [1:1] MCS channel [x] interrupt - RO */
    ureg32 MCS_CH2_IRQ:1;        /* [2:2] MCS channel [x] interrupt - RO */
    ureg32 MCS_CH3_IRQ:1;        /* [3:3] MCS channel [x] interrupt - RO */
    ureg32 MCS_CH4_IRQ:1;        /* [4:4] MCS channel [x] interrupt - RO */
    ureg32 MCS_CH5_IRQ:1;        /* [5:5] MCS channel [x] interrupt - RO */
    ureg32 MCS_CH6_IRQ:1;        /* [6:6] MCS channel [x] interrupt - RO */
    ureg32 MCS_CH7_IRQ:1;        /* [7:7] MCS channel [x] interrupt - RO */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_ICM_IRQG_MCS_CI_Bits;

/* ICM Interrupt group PSM 0 for Channel Interrupt information of FIFO0 - FIFO1 - FIFO2 */
typedef struct
{
    ureg32 PSM_M0_CH0_IRQ:1;        /* [0:0] PSM0 channel [x] shared interrupt - RO */
    ureg32 PSM_M0_CH1_IRQ:1;        /* [1:1] PSM0 channel [x] shared interrupt - RO */
    ureg32 PSM_M0_CH2_IRQ:1;        /* [2:2] PSM0 channel [x] shared interrupt - RO */
    ureg32 PSM_M0_CH3_IRQ:1;        /* [3:3] PSM0 channel [x] shared interrupt - RO */
    ureg32 PSM_M0_CH4_IRQ:1;        /* [4:4] PSM0 channel [x] shared interrupt - RO */
    ureg32 PSM_M0_CH5_IRQ:1;        /* [5:5] PSM0 channel [x] shared interrupt - RO */
    ureg32 PSM_M0_CH6_IRQ:1;        /* [6:6] PSM0 channel [x] shared interrupt - RO */
    ureg32 PSM_M0_CH7_IRQ:1;        /* [7:7] PSM0 channel [x] shared interrupt - RO */
    ureg32 PSM_M1_CH0_IRQ:1;        /* [8:8] PSMm channel [x] shared interrupt ([j]=4*0+1) - RO */
    ureg32 PSM_M1_CH1_IRQ:1;        /* [9:9] PSMm channel [x] shared interrupt ([j]=4*0+1) - RO */
    ureg32 PSM_M1_CH2_IRQ:1;        /* [10:10] PSMm channel [x] shared interrupt ([j]=4*0+1) - RO */
    ureg32 PSM_M1_CH3_IRQ:1;        /* [11:11] PSMm channel [x] shared interrupt ([j]=4*0+1) - RO */
    ureg32 PSM_M1_CH4_IRQ:1;        /* [12:12] PSMm channel [x] shared interrupt ([j]=4*0+1) - RO */
    ureg32 PSM_M1_CH5_IRQ:1;        /* [13:13] PSMm channel [x] shared interrupt ([j]=4*0+1) - RO */
    ureg32 PSM_M1_CH6_IRQ:1;        /* [14:14] PSMm channel [x] shared interrupt ([j]=4*0+1) - RO */
    ureg32 PSM_M1_CH7_IRQ:1;        /* [15:15] PSMm channel [x] shared interrupt ([j]=4*0+1) - RO */
    ureg32 PSM_M2_CH0_IRQ:1;        /* [16:16] PSMm channel [x] shared interrupt ([j]=4*0+2) - RO */
    ureg32 PSM_M2_CH1_IRQ:1;        /* [17:17] PSMm channel [x] shared interrupt ([j]=4*0+2) - RO */
    ureg32 PSM_M2_CH2_IRQ:1;        /* [18:18] PSMm channel [x] shared interrupt ([j]=4*0+2) - RO */
    ureg32 PSM_M2_CH3_IRQ:1;        /* [19:19] PSMm channel [x] shared interrupt ([j]=4*0+2) - RO */
    ureg32 PSM_M2_CH4_IRQ:1;        /* [20:20] PSMm channel [x] shared interrupt ([j]=4*0+2) - RO */
    ureg32 PSM_M2_CH5_IRQ:1;        /* [21:21] PSMm channel [x] shared interrupt ([j]=4*0+2) - RO */
    ureg32 PSM_M2_CH6_IRQ:1;        /* [22:22] PSMm channel [x] shared interrupt ([j]=4*0+2) - RO */
    ureg32 PSM_M2_CH7_IRQ:1;        /* [23:23] PSMm channel [x] shared interrupt ([j]=4*0+2) - RO */
    ureg32 reserved_24:8;           /* [31:24] Internal  reserved */
} GTM_ICM_IRQG_PSM_CI_Bits;

/* ICM Interrupt group SPE for module Interrupt information */
typedef struct
{
    ureg32 SPE0_IRQ:1;           /* [0:0] SPE[j] interrupt - RO */
    ureg32 SPE1_IRQ:1;           /* [1:1] SPE[j] interrupt - RO */
    ureg32 SPE2_IRQ:1;           /* [2:2] SPE[j] interrupt - RO */
    ureg32 reserved_3:29;        /* [31:3] Internal  reserved */
} GTM_ICM_IRQG_SPE_CI_Bits;

/* ICM Interrupt group ATOM [g] for Channel Interrupt information of ATOM[j] (m=4*[g]+(0..3)) */
typedef struct
{
    ureg32 ATOM_M0_CH0_IRQ:1;        /* [0:0] ATOM[j] channel [x] interrupt ([j]=4*[g]+0) - RO */
    ureg32 ATOM_M0_CH1_IRQ:1;        /* [1:1] ATOM[j] channel [x] interrupt ([j]=4*[g]+0) - RO */
    ureg32 ATOM_M0_CH2_IRQ:1;        /* [2:2] ATOM[j] channel [x] interrupt ([j]=4*[g]+0) - RO */
    ureg32 ATOM_M0_CH3_IRQ:1;        /* [3:3] ATOM[j] channel [x] interrupt ([j]=4*[g]+0) - RO */
    ureg32 ATOM_M0_CH4_IRQ:1;        /* [4:4] ATOM[j] channel [x] interrupt ([j]=4*[g]+0) - RO */
    ureg32 ATOM_M0_CH5_IRQ:1;        /* [5:5] ATOM[j] channel [x] interrupt ([j]=4*[g]+0) - RO */
    ureg32 ATOM_M0_CH6_IRQ:1;        /* [6:6] ATOM[j] channel [x] interrupt ([j]=4*[g]+0) - RO */
    ureg32 ATOM_M0_CH7_IRQ:1;        /* [7:7] ATOM[j] channel [x] interrupt ([j]=4*[g]+0) - RO */
    ureg32 ATOM_M1_CH0_IRQ:1;        /* [8:8] ATOM[j] channel [x] interrupt ([j]=4*[g]+1) - RO */
    ureg32 ATOM_M1_CH1_IRQ:1;        /* [9:9] ATOM[j] channel [x] interrupt ([j]=4*[g]+1) - RO */
    ureg32 ATOM_M1_CH2_IRQ:1;        /* [10:10] ATOM[j] channel [x] interrupt ([j]=4*[g]+1) - RO */
    ureg32 ATOM_M1_CH3_IRQ:1;        /* [11:11] ATOM[j] channel [x] interrupt ([j]=4*[g]+1) - RO */
    ureg32 ATOM_M1_CH4_IRQ:1;        /* [12:12] ATOM[j] channel [x] interrupt ([j]=4*[g]+1) - RO */
    ureg32 ATOM_M1_CH5_IRQ:1;        /* [13:13] ATOM[j] channel [x] interrupt ([j]=4*[g]+1) - RO */
    ureg32 ATOM_M1_CH6_IRQ:1;        /* [14:14] ATOM[j] channel [x] interrupt ([j]=4*[g]+1) - RO */
    ureg32 ATOM_M1_CH7_IRQ:1;        /* [15:15] ATOM[j] channel [x] interrupt ([j]=4*[g]+1) - RO */
    ureg32 ATOM_M2_CH0_IRQ:1;        /* [16:16] ATOMm channel [x] interrupt ([j]=4*[g]+2) - RO */
    ureg32 ATOM_M2_CH1_IRQ:1;        /* [17:17] ATOMm channel [x] interrupt ([j]=4*[g]+2) - RO */
    ureg32 ATOM_M2_CH2_IRQ:1;        /* [18:18] ATOMm channel [x] interrupt ([j]=4*[g]+2) - RO */
    ureg32 ATOM_M2_CH3_IRQ:1;        /* [19:19] ATOMm channel [x] interrupt ([j]=4*[g]+2) - RO */
    ureg32 ATOM_M2_CH4_IRQ:1;        /* [20:20] ATOMm channel [x] interrupt ([j]=4*[g]+2) - RO */
    ureg32 ATOM_M2_CH5_IRQ:1;        /* [21:21] ATOMm channel [x] interrupt ([j]=4*[g]+2) - RO */
    ureg32 ATOM_M2_CH6_IRQ:1;        /* [22:22] ATOMm channel [x] interrupt ([j]=4*[g]+2) - RO */
    ureg32 ATOM_M2_CH7_IRQ:1;        /* [23:23] ATOMm channel [x] interrupt ([j]=4*[g]+2) - RO */
    ureg32 ATOM_M3_CH0_IRQ:1;        /* [24:24] ATOM[j] channel [x] interrupt ([j]=4*[g]+3) - RO */
    ureg32 ATOM_M3_CH1_IRQ:1;        /* [25:25] ATOM[j] channel [x] interrupt ([j]=4*[g]+3) - RO */
    ureg32 ATOM_M3_CH2_IRQ:1;        /* [26:26] ATOM[j] channel [x] interrupt ([j]=4*[g]+3) - RO */
    ureg32 ATOM_M3_CH3_IRQ:1;        /* [27:27] ATOM[j] channel [x] interrupt ([j]=4*[g]+3) - RO */
    ureg32 ATOM_M3_CH4_IRQ:1;        /* [28:28] ATOM[j] channel [x] interrupt ([j]=4*[g]+3) - RO */
    ureg32 ATOM_M3_CH5_IRQ:1;        /* [29:29] ATOM[j] channel [x] interrupt ([j]=4*[g]+3) - RO */
    ureg32 ATOM_M3_CH6_IRQ:1;        /* [30:30] ATOM[j] channel [x] interrupt ([j]=4*[g]+3) - RO */
    ureg32 ATOM_M3_CH7_IRQ:1;        /* [31:31] ATOM[j] channel [x] interrupt ([j]=4*[g]+3) - RO */
} GTM_ICM_IRQG_ATOM_CI_Bits;

/* ICM Interrupt group TOM [g] for Channel Interrupt information of TOMm ([j]=2*[g]+(0..1)) */
typedef struct
{
    ureg32 TOM_M0_CH0_IRQ:1;         /* [0:0] TOM[j] channel [x] interrupt ([j]=2*[g]+0) - RO */
    ureg32 TOM_M0_CH1_IRQ:1;         /* [1:1] TOM[j] channel [x] interrupt ([j]=2*[g]+0) - RO */
    ureg32 TOM_M0_CH2_IRQ:1;         /* [2:2] TOM[j] channel [x] interrupt ([j]=2*[g]+0) - RO */
    ureg32 TOM_M0_CH3_IRQ:1;         /* [3:3] TOM[j] channel [x] interrupt ([j]=2*[g]+0) - RO */
    ureg32 TOM_M0_CH4_IRQ:1;         /* [4:4] TOM[j] channel [x] interrupt ([j]=2*[g]+0) - RO */
    ureg32 TOM_M0_CH5_IRQ:1;         /* [5:5] TOM[j] channel [x] interrupt ([j]=2*[g]+0) - RO */
    ureg32 TOM_M0_CH6_IRQ:1;         /* [6:6] TOM[j] channel [x] interrupt ([j]=2*[g]+0) - RO */
    ureg32 TOM_M0_CH7_IRQ:1;         /* [7:7] TOM[j] channel [x] interrupt ([j]=2*[g]+0) - RO */
    ureg32 TOM_M0_CH8_IRQ:1;         /* [8:8] TOM[j] channel [x] interrupt ([j]=2*[g]+0) - RO */
    ureg32 TOM_M0_CH9_IRQ:1;         /* [9:9] TOM[j] channel [x] interrupt ([j]=2*[g]+0) - RO */
    ureg32 TOM_M0_CH10_IRQ:1;        /* [10:10] TOM[j] channel [x] interrupt ([j]=2*[g]+0) - RO */
    ureg32 TOM_M0_CH11_IRQ:1;        /* [11:11] TOM[j] channel [x] interrupt ([j]=2*[g]+0) - RO */
    ureg32 TOM_M0_CH12_IRQ:1;        /* [12:12] TOM[j] channel [x] interrupt ([j]=2*[g]+0) - RO */
    ureg32 TOM_M0_CH13_IRQ:1;        /* [13:13] TOM[j] channel [x] interrupt ([j]=2*[g]+0) - RO */
    ureg32 TOM_M0_CH14_IRQ:1;        /* [14:14] TOM[j] channel [x] interrupt ([j]=2*[g]+0) - RO */
    ureg32 TOM_M0_CH15_IRQ:1;        /* [15:15] TOM[j] channel [x] interrupt ([j]=2*[g]+0) - RO */
    ureg32 TOM_M1_CH0_IRQ:1;         /* [16:16] TOM[j] channel [x] interrupt ([j]=2*[g]+1) - RO */
    ureg32 TOM_M1_CH1_IRQ:1;         /* [17:17] TOM[j] channel [x] interrupt ([j]=2*[g]+1) - RO */
    ureg32 TOM_M1_CH2_IRQ:1;         /* [18:18] TOM[j] channel [x] interrupt ([j]=2*[g]+1) - RO */
    ureg32 TOM_M1_CH3_IRQ:1;         /* [19:19] TOM[j] channel [x] interrupt ([j]=2*[g]+1) - RO */
    ureg32 TOM_M1_CH4_IRQ:1;         /* [20:20] TOM[j] channel [x] interrupt ([j]=2*[g]+1) - RO */
    ureg32 TOM_M1_CH5_IRQ:1;         /* [21:21] TOM[j] channel [x] interrupt ([j]=2*[g]+1) - RO */
    ureg32 TOM_M1_CH6_IRQ:1;         /* [22:22] TOM[j] channel [x] interrupt ([j]=2*[g]+1) - RO */
    ureg32 TOM_M1_CH7_IRQ:1;         /* [23:23] TOM[j] channel [x] interrupt ([j]=2*[g]+1) - RO */
    ureg32 TOM_M1_CH8_IRQ:1;         /* [24:24] TOM[j] channel [x] interrupt ([j]=2*[g]+1) - RO */
    ureg32 TOM_M1_CH9_IRQ:1;         /* [25:25] TOM[j] channel [x] interrupt ([j]=2*[g]+1) - RO */
    ureg32 TOM_M1_CH10_IRQ:1;        /* [26:26] TOM[j] channel [x] interrupt ([j]=2*[g]+1) - RO */
    ureg32 TOM_M1_CH11_IRQ:1;        /* [27:27] TOM[j] channel [x] interrupt ([j]=2*[g]+1) - RO */
    ureg32 TOM_M1_CH12_IRQ:1;        /* [28:28] TOM[j] channel [x] interrupt ([j]=2*[g]+1) - RO */
    ureg32 TOM_M1_CH13_IRQ:1;        /* [29:29] TOM[j] channel [x] interrupt ([j]=2*[g]+1) - RO */
    ureg32 TOM_M1_CH14_IRQ:1;        /* [30:30] TOM[j] channel [x] interrupt ([j]=2*[g]+1) - RO */
    ureg32 TOM_M1_CH15_IRQ:1;        /* [31:31] TOM[j] channel [x] interrupt ([j]=2*[g]+1) - RO */
} GTM_ICM_IRQG_TOM_CI_Bits;

/* MAP Control register */
typedef struct
{
    ureg32 TSEL:1;               /* [0:0] TRIGGER signal output select. - RW */
    ureg32 SSL:3;                /* [3:1] STATE signal output select - RW */
    ureg32 LSEL:1;               /* [4:4] TIM_MAP_DATA[6] input level selection - RW */
    ureg32 reserved_5:11;        /* [15:5] Internal  reserved */
    ureg32 TSPP0_EN:1;           /* [16:16] Enable of TSPP0 sub-unit - RW */
    ureg32 TSPP0_DLD:1;          /* [17:17] DIR level definition bit - RW */
    ureg32 reserved_18:2;        /* [19:18] Internal  reserved */
    ureg32 TSPP0_I0V:1;          /* [20:20] Disable of TSPP0 TIM_MAP_DATA[x][48:48] input line - RW */
    ureg32 TSPP0_I1V:1;          /* [21:21] Disable of TSPP0 TIM_MAP_DATA[y][48:48] input line - RW */
    ureg32 TSPP0_I2V:1;          /* [22:22] Disable of TSPP0 TIM_MAP_DATA[z][48:48] input line - RW */
    ureg32 reserved_23:1;        /* [23:23] Internal  reserved */
    ureg32 TSPP1_EN:1;           /* [24:24] Enable of TSPP1 sub-unit - RW */
    ureg32 TSPP1_DLD:1;          /* [25:25] DIR level definition bit - RW */
    ureg32 reserved_26:2;        /* [27:26] Internal  reserved */
    ureg32 TSPP1_I0V:1;          /* [28:28] Disable of TSPP1 TIM_MAP_DATA[x][48:48] input line - RW */
    ureg32 TSPP1_I1V:1;          /* [29:29] Disable of TSPP1 TIM_MAP_DATA[y][48:48] input line - RW */
    ureg32 TSPP1_I2V:1;          /* [30:30] Disable of TSPP1 TIM_MAP_DATA[z][48:48] input line - RW */
    ureg32 reserved_31:1;        /* [31:31] Internal  reserved */
} GTM_MAP_CTRL_Bits;

/* MON status register */
typedef struct
{
    ureg32 ACT_CMU0:1;           /* [0:0] CCM[1]_CLK_RES activity - RW */
    ureg32 ACT_CMU1:1;           /* [1:1] CCM[1]_CLK_RES activity - RW */
    ureg32 ACT_CMU2:1;           /* [2:2] CCM[1]_CLK_RES activity - RW */
    ureg32 ACT_CMU3:1;           /* [3:3] CCM[1]_CLK_RES activity - RW */
    ureg32 ACT_CMU4:1;           /* [4:4] CCM[1]_CLK_RES activity - RW */
    ureg32 ACT_CMU5:1;           /* [5:5] CCM[1]_CLK_RES activity - RW */
    ureg32 ACT_CMU6:1;           /* [6:6] CCM[1]_CLK_RES activity - RW */
    ureg32 ACT_CMU7:1;           /* [7:7] CCM[1]_CLK_RES activity - RW */
    ureg32 ACT_CMUFX0:1;         /* [8:8] CCM[1]_FXCLK_RES activity - RW */
    ureg32 ACT_CMUFX1:1;         /* [9:9] CCM[1]_FXCLK_RES activity - RW */
    ureg32 ACT_CMUFX2:1;         /* [10:10] CCM[1]_FXCLK_RES activity - RW */
    ureg32 ACT_CMUFX3:1;         /* [11:11] CCM[1]_FXCLK_RES activity - RW */
    ureg32 ACT_CMUFX4:1;         /* [12:12] CCM[1]_FXCLK_RES activity - RW */
    ureg32 reserved_13:1;        /* [13:13] Internal  reserved */
    ureg32 ACT_CMU8:1;           /* [14:14] CCM[1]_CLK_RES[8:8] activity - RW */
    ureg32 reserved_15:1;        /* [15:15] Internal  reserved */
    ureg32 CMP_ERR:1;            /* [16:16] Error detected at CMP  - RO */
    ureg32 reserved_17:3;        /* [19:17] Internal  reserved */
    ureg32 MCS0_ERR:1;           /* [20:20] Error detected at MCS[j] - RO */
    ureg32 MCS1_ERR:1;           /* [21:21] Error detected at MCS[j] - RO */
    ureg32 MCS2_ERR:1;           /* [22:22] Error detected at MCS[j] - RO */
    ureg32 MCS3_ERR:1;           /* [23:23] Error detected at MCS[j] - RO */
    ureg32 MCS4_ERR:1;           /* [24:24] Error detected at MCS[j] - RO */
    ureg32 reserved_25:7;        /* [31:25] Internal  reserved */
} GTM_MON_STATUS_Bits;

/* MON activity register 0 */
typedef struct
{
    ureg32 MCA_0_0:1;        /* [0:0] Activity of check performed in module MCS0 at channel [x] - RW */
    ureg32 MCA_0_1:1;        /* [1:1] Activity of check performed in module MCS0 at channel [x] - RW */
    ureg32 MCA_0_2:1;        /* [2:2] Activity of check performed in module MCS0 at channel [x] - RW */
    ureg32 MCA_0_3:1;        /* [3:3] Activity of check performed in module MCS0 at channel [x] - RW */
    ureg32 MCA_0_4:1;        /* [4:4] Activity of check performed in module MCS0 at channel [x] - RW */
    ureg32 MCA_0_5:1;        /* [5:5] Activity of check performed in module MCS0 at channel [x] - RW */
    ureg32 MCA_0_6:1;        /* [6:6] Activity of check performed in module MCS0 at channel [x] - RW */
    ureg32 MCA_0_7:1;        /* [7:7] Activity of check performed in module MCS0 at channel [x] - RW */
    ureg32 MCA_1_0:1;        /* [8:8] Activity of check performed in module MCS1 at channel [x] - RW */
    ureg32 MCA_1_1:1;        /* [9:9] Activity of check performed in module MCS1 at channel [x] - RW */
    ureg32 MCA_1_2:1;        /* [10:10] Activity of check performed in module MCS1 at channel [x] - RW */
    ureg32 MCA_1_3:1;        /* [11:11] Activity of check performed in module MCS1 at channel [x] - RW */
    ureg32 MCA_1_4:1;        /* [12:12] Activity of check performed in module MCS1 at channel [x] - RW */
    ureg32 MCA_1_5:1;        /* [13:13] Activity of check performed in module MCS1 at channel [x] - RW */
    ureg32 MCA_1_6:1;        /* [14:14] Activity of check performed in module MCS1 at channel [x] - RW */
    ureg32 MCA_1_7:1;        /* [15:15] Activity of check performed in module MCS1 at channel [x] - RW */
    ureg32 MCA_2_0:1;        /* [16:16] Activity of check performed in module MCS2 at channel [x] - RW */
    ureg32 MCA_2_1:1;        /* [17:17] Activity of check performed in module MCS2 at channel [x] - RW */
    ureg32 MCA_2_2:1;        /* [18:18] Activity of check performed in module MCS2 at channel [x] - RW */
    ureg32 MCA_2_3:1;        /* [19:19] Activity of check performed in module MCS2 at channel [x] - RW */
    ureg32 MCA_2_4:1;        /* [20:20] Activity of check performed in module MCS2 at channel [x] - RW */
    ureg32 MCA_2_5:1;        /* [21:21] Activity of check performed in module MCS2 at channel [x] - RW */
    ureg32 MCA_2_6:1;        /* [22:22] Activity of check performed in module MCS2 at channel [x] - RW */
    ureg32 MCA_2_7:1;        /* [23:23] Activity of check performed in module MCS2 at channel [x] - RW */
    ureg32 MCA_3_0:1;        /* [24:24] Activity of check performed in module MCS3 at channel [x] - RW */
    ureg32 MCA_3_1:1;        /* [25:25] Activity of check performed in module MCS3 at channel [x] - RW */
    ureg32 MCA_3_2:1;        /* [26:26] Activity of check performed in module MCS3 at channel [x] - RW */
    ureg32 MCA_3_3:1;        /* [27:27] Activity of check performed in module MCS3 at channel [x] - RW */
    ureg32 MCA_3_4:1;        /* [28:28] Activity of check performed in module MCS3 at channel [x] - RW */
    ureg32 MCA_3_5:1;        /* [29:29] Activity of check performed in module MCS3 at channel [x] - RW */
    ureg32 MCA_3_6:1;        /* [30:30] Activity of check performed in module MCS3 at channel [x] - RW */
    ureg32 MCA_3_7:1;        /* [31:31] Activity of check performed in module MCS3 at channel [x] - RW */
} GTM_MON_ACTIVITY_0_Bits;

/* MON activity register 1 */
typedef struct
{
    ureg32 MCA_4_0:1;            /* [0:0] Activity of check performed in module MCS4 at channel [x] - RW */
    ureg32 MCA_4_1:1;            /* [1:1] Activity of check performed in module MCS4 at channel [x] - RW */
    ureg32 MCA_4_2:1;            /* [2:2] Activity of check performed in module MCS4 at channel [x] - RW */
    ureg32 MCA_4_3:1;            /* [3:3] Activity of check performed in module MCS4 at channel [x] - RW */
    ureg32 MCA_4_4:1;            /* [4:4] Activity of check performed in module MCS4 at channel [x] - RW */
    ureg32 MCA_4_5:1;            /* [5:5] Activity of check performed in module MCS4 at channel [x] - RW */
    ureg32 MCA_4_6:1;            /* [6:6] Activity of check performed in module MCS4 at channel [x] - RW */
    ureg32 MCA_4_7:1;            /* [7:7] Activity of check performed in module MCS4 at channel [x] - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_MON_ACTIVITY_1_Bits;

/* MON activity register for MCS [j] */
typedef struct
{
    ureg32 MCA_0:1;              /* [0:0] Activity of check performed in module MCS [j] at channel [x] - RW */
    ureg32 MCA_1:1;              /* [1:1] Activity of check performed in module MCS [j] at channel [x] - RW */
    ureg32 MCA_2:1;              /* [2:2] Activity of check performed in module MCS [j] at channel [x] - RW */
    ureg32 MCA_3:1;              /* [3:3] Activity of check performed in module MCS [j] at channel [x] - RW */
    ureg32 MCA_4:1;              /* [4:4] Activity of check performed in module MCS [j] at channel [x] - RW */
    ureg32 MCA_5:1;              /* [5:5] Activity of check performed in module MCS [j] at channel [x] - RW */
    ureg32 MCA_6:1;              /* [6:6] Activity of check performed in module MCS [j] at channel [x] - RW */
    ureg32 MCA_7:1;              /* [7:7] Activity of check performed in module MCS [j] at channel [x] - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_MON_ACTIVITY_MCS_Bits;

/* CMP comparator enable register */
typedef struct
{
    ureg32 ABWC0_EN:1;           /* [0:0] Enable comparator channel [c] in ABWC - RW */
    ureg32 ABWC1_EN:1;           /* [1:1] Enable comparator channel [c] in ABWC - RW */
    ureg32 ABWC2_EN:1;           /* [2:2] Enable comparator channel [c] in ABWC - RW */
    ureg32 ABWC3_EN:1;           /* [3:3] Enable comparator channel [c] in ABWC - RW */
    ureg32 ABWC4_EN:1;           /* [4:4] Enable comparator channel [c] in ABWC - RW */
    ureg32 ABWC5_EN:1;           /* [5:5] Enable comparator channel [c] in ABWC - RW */
    ureg32 ABWC6_EN:1;           /* [6:6] Enable comparator channel [c] in ABWC - RW */
    ureg32 ABWC7_EN:1;           /* [7:7] Enable comparator channel [c] in ABWC - RW */
    ureg32 ABWC8_EN:1;           /* [8:8] Enable comparator channel [c] in ABWC - RW */
    ureg32 ABWC9_EN:1;           /* [9:9] Enable comparator channel [c] in ABWC - RW */
    ureg32 ABWC10_EN:1;          /* [10:10] Enable comparator channel [c] in ABWC - RW */
    ureg32 ABWC11_EN:1;          /* [11:11] Enable comparator channel [c] in ABWC - RW */
    ureg32 TBWC0_EN:1;           /* [12:12] Enable comparator channel [c] in TBWC - RW */
    ureg32 TBWC1_EN:1;           /* [13:13] Enable comparator channel [c] in TBWC - RW */
    ureg32 TBWC2_EN:1;           /* [14:14] Enable comparator channel [c] in TBWC - RW */
    ureg32 TBWC3_EN:1;           /* [15:15] Enable comparator channel [c] in TBWC - RW */
    ureg32 TBWC4_EN:1;           /* [16:16] Enable comparator channel [c] in TBWC - RW */
    ureg32 TBWC5_EN:1;           /* [17:17] Enable comparator channel [c] in TBWC - RW */
    ureg32 TBWC6_EN:1;           /* [18:18] Enable comparator channel [c] in TBWC - RW */
    ureg32 TBWC7_EN:1;           /* [19:19] Enable comparator channel [c] in TBWC - RW */
    ureg32 TBWC8_EN:1;           /* [20:20] Enable comparator channel [c] in TBWC - RW */
    ureg32 TBWC9_EN:1;           /* [21:21] Enable comparator channel [c] in TBWC - RW */
    ureg32 TBWC10_EN:1;          /* [22:22] Enable comparator channel [c] in TBWC - RW */
    ureg32 TBWC11_EN:1;          /* [23:23] Enable comparator channel [c] in TBWC - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_CMP_EN_Bits;

/* CMP event notification register */
typedef struct
{
    ureg32 ABWC0:1;              /* [0:0] ATOM sub-modules output bitwise comparator [c] error indication - RW */
    ureg32 ABWC1:1;              /* [1:1] ATOM sub-modules output bitwise comparator [c] error indication - RW */
    ureg32 ABWC2:1;              /* [2:2] ATOM sub-modules output bitwise comparator [c] error indication - RW */
    ureg32 ABWC3:1;              /* [3:3] ATOM sub-modules output bitwise comparator [c] error indication - RW */
    ureg32 ABWC4:1;              /* [4:4] ATOM sub-modules output bitwise comparator [c] error indication - RW */
    ureg32 ABWC5:1;              /* [5:5] ATOM sub-modules output bitwise comparator [c] error indication - RW */
    ureg32 ABWC6:1;              /* [6:6] ATOM sub-modules output bitwise comparator [c] error indication - RW */
    ureg32 ABWC7:1;              /* [7:7] ATOM sub-modules output bitwise comparator [c] error indication - RW */
    ureg32 ABWC8:1;              /* [8:8] ATOM sub-modules output bitwise comparator [c] error indication - RW */
    ureg32 ABWC9:1;              /* [9:9] ATOM sub-modules output bitwise comparator [c] error indication - RW */
    ureg32 ABWC10:1;             /* [10:10] ATOM sub-modules output bitwise comparator [c] error indication - RW */
    ureg32 ABWC11:1;             /* [11:11] ATOM sub-modules output bitwise comparator [c] error indication - RW */
    ureg32 TBWC0:1;              /* [12:12] TOM sub-modules output bitwise comparator [c] error indication - RW */
    ureg32 TBWC1:1;              /* [13:13] TOM sub-modules output bitwise comparator [c] error indication - RW */
    ureg32 TBWC2:1;              /* [14:14] TOM sub-modules output bitwise comparator [c] error indication - RW */
    ureg32 TBWC3:1;              /* [15:15] TOM sub-modules output bitwise comparator [c] error indication - RW */
    ureg32 TBWC4:1;              /* [16:16] TOM sub-modules output bitwise comparator [c] error indication - RW */
    ureg32 TBWC5:1;              /* [17:17] TOM sub-modules output bitwise comparator [c] error indication - RW */
    ureg32 TBWC6:1;              /* [18:18] TOM sub-modules output bitwise comparator [c] error indication - RW */
    ureg32 TBWC7:1;              /* [19:19] TOM sub-modules output bitwise comparator [c] error indication - RW */
    ureg32 TBWC8:1;              /* [20:20] TOM sub-modules output bitwise comparator [c] error indication - RW */
    ureg32 TBWC9:1;              /* [21:21] TOM sub-modules output bitwise comparator [c] error indication - RW */
    ureg32 TBWC10:1;             /* [22:22] TOM sub-modules output bitwise comparator [c] error indication - RW */
    ureg32 TBWC11:1;             /* [23:23] TOM sub-modules output bitwise comparator [c] error indication - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_CMP_IRQ_NOTIFY_Bits;

/* CMP interrupt enable register */
typedef struct
{
    ureg32 ABWC0_EN_IRQ:1;         /* [0:0] Enable CMP_IRQ_NOTIFY.ABWC[c] interrupt source for CMP_IRQ line - RW */
    ureg32 ABWC1_EN_IRQ:1;         /* [1:1] Enable CMP_IRQ_NOTIFY.ABWC[c] interrupt source for CMP_IRQ line - RW */
    ureg32 ABWC2_EN_IRQ:1;         /* [2:2] Enable CMP_IRQ_NOTIFY.ABWC[c] interrupt source for CMP_IRQ line - RW */
    ureg32 ABWC3_EN_IRQ:1;         /* [3:3] Enable CMP_IRQ_NOTIFY.ABWC[c] interrupt source for CMP_IRQ line - RW */
    ureg32 ABWC4_EN_IRQ:1;         /* [4:4] Enable CMP_IRQ_NOTIFY.ABWC[c] interrupt source for CMP_IRQ line - RW */
    ureg32 ABWC5_EN_IRQ:1;         /* [5:5] Enable CMP_IRQ_NOTIFY.ABWC[c] interrupt source for CMP_IRQ line - RW */
    ureg32 ABWC6_EN_IRQ:1;         /* [6:6] Enable CMP_IRQ_NOTIFY.ABWC[c] interrupt source for CMP_IRQ line - RW */
    ureg32 ABWC7_EN_IRQ:1;         /* [7:7] Enable CMP_IRQ_NOTIFY.ABWC[c] interrupt source for CMP_IRQ line - RW */
    ureg32 ABWC8_EN_IRQ:1;         /* [8:8] Enable CMP_IRQ_NOTIFY.ABWC[c] interrupt source for CMP_IRQ line - RW */
    ureg32 ABWC9_EN_IRQ:1;         /* [9:9] Enable CMP_IRQ_NOTIFY.ABWC[c] interrupt source for CMP_IRQ line - RW */
    ureg32 ABWC10_EN_IRQ:1;        /* [10:10] Enable CMP_IRQ_NOTIFY.ABWC[c] interrupt source for CMP_IRQ line - RW */
    ureg32 ABWC11_EN_IRQ:1;        /* [11:11] Enable CMP_IRQ_NOTIFY.ABWC[c] interrupt source for CMP_IRQ line - RW */
    ureg32 TBWC0_EN_IRQ:1;         /* [12:12] Enable CMP_IRQ_NOTIFY.TBWC[c] interrupt source for CMP_IRQ line - RW */
    ureg32 TBWC1_EN_IRQ:1;         /* [13:13] Enable CMP_IRQ_NOTIFY.TBWC[c] interrupt source for CMP_IRQ line - RW */
    ureg32 TBWC2_EN_IRQ:1;         /* [14:14] Enable CMP_IRQ_NOTIFY.TBWC[c] interrupt source for CMP_IRQ line - RW */
    ureg32 TBWC3_EN_IRQ:1;         /* [15:15] Enable CMP_IRQ_NOTIFY.TBWC[c] interrupt source for CMP_IRQ line - RW */
    ureg32 TBWC4_EN_IRQ:1;         /* [16:16] Enable CMP_IRQ_NOTIFY.TBWC[c] interrupt source for CMP_IRQ line - RW */
    ureg32 TBWC5_EN_IRQ:1;         /* [17:17] Enable CMP_IRQ_NOTIFY.TBWC[c] interrupt source for CMP_IRQ line - RW */
    ureg32 TBWC6_EN_IRQ:1;         /* [18:18] Enable CMP_IRQ_NOTIFY.TBWC[c] interrupt source for CMP_IRQ line - RW */
    ureg32 TBWC7_EN_IRQ:1;         /* [19:19] Enable CMP_IRQ_NOTIFY.TBWC[c] interrupt source for CMP_IRQ line - RW */
    ureg32 TBWC8_EN_IRQ:1;         /* [20:20] Enable CMP_IRQ_NOTIFY.TBWC[c] interrupt source for CMP_IRQ line - RW */
    ureg32 TBWC9_EN_IRQ:1;         /* [21:21] Enable CMP_IRQ_NOTIFY.TBWC[c] interrupt source for CMP_IRQ line - RW */
    ureg32 TBWC10_EN_IRQ:1;        /* [22:22] Enable CMP_IRQ_NOTIFY.TBWC[c] interrupt source for CMP_IRQ line - RW */
    ureg32 TBWC11_EN_IRQ:1;        /* [23:23] Enable CMP_IRQ_NOTIFY.TBWC[c] interrupt source for CMP_IRQ line - RW */
    ureg32 reserved_24:8;          /* [31:24] Internal  reserved */
} GTM_CMP_IRQ_EN_Bits;

/* CMP interrupt force register */
typedef struct
{
    ureg32 TRG_ABWC0:1;          /* [0:0] Trigger the bit CMP_IRQ_NOTIFY.ABWC[c] bit by software - RW */
    ureg32 TRG_ABWC1:1;          /* [1:1] Trigger the bit CMP_IRQ_NOTIFY.ABWC[c] bit by software - RW */
    ureg32 TRG_ABWC2:1;          /* [2:2] Trigger the bit CMP_IRQ_NOTIFY.ABWC[c] bit by software - RW */
    ureg32 TRG_ABWC3:1;          /* [3:3] Trigger the bit CMP_IRQ_NOTIFY.ABWC[c] bit by software - RW */
    ureg32 TRG_ABWC4:1;          /* [4:4] Trigger the bit CMP_IRQ_NOTIFY.ABWC[c] bit by software - RW */
    ureg32 TRG_ABWC5:1;          /* [5:5] Trigger the bit CMP_IRQ_NOTIFY.ABWC[c] bit by software - RW */
    ureg32 TRG_ABWC6:1;          /* [6:6] Trigger the bit CMP_IRQ_NOTIFY.ABWC[c] bit by software - RW */
    ureg32 TRG_ABWC7:1;          /* [7:7] Trigger the bit CMP_IRQ_NOTIFY.ABWC[c] bit by software - RW */
    ureg32 TRG_ABWC8:1;          /* [8:8] Trigger the bit CMP_IRQ_NOTIFY.ABWC[c] bit by software - RW */
    ureg32 TRG_ABWC9:1;          /* [9:9] Trigger the bit CMP_IRQ_NOTIFY.ABWC[c] bit by software - RW */
    ureg32 TRG_ABWC10:1;         /* [10:10] Trigger the bit CMP_IRQ_NOTIFY.ABWC[c] bit by software - RW */
    ureg32 TRG_ABWC11:1;         /* [11:11] Trigger the bit CMP_IRQ_NOTIFY.ABWC[c] bit by software - RW */
    ureg32 TRG_TBWC0:1;          /* [12:12] Trigger CMP_IRQ_NOTIFY.TBWC[c] bit by software - RW */
    ureg32 TRG_TBWC1:1;          /* [13:13] Trigger CMP_IRQ_NOTIFY.TBWC[c] bit by software - RW */
    ureg32 TRG_TBWC2:1;          /* [14:14] Trigger CMP_IRQ_NOTIFY.TBWC[c] bit by software - RW */
    ureg32 TRG_TBWC3:1;          /* [15:15] Trigger CMP_IRQ_NOTIFY.TBWC[c] bit by software - RW */
    ureg32 TRG_TBWC4:1;          /* [16:16] Trigger CMP_IRQ_NOTIFY.TBWC[c] bit by software - RW */
    ureg32 TRG_TBWC5:1;          /* [17:17] Trigger CMP_IRQ_NOTIFY.TBWC[c] bit by software - RW */
    ureg32 TRG_TBWC6:1;          /* [18:18] Trigger CMP_IRQ_NOTIFY.TBWC[c] bit by software - RW */
    ureg32 TRG_TBWC7:1;          /* [19:19] Trigger CMP_IRQ_NOTIFY.TBWC[c] bit by software - RW */
    ureg32 TRG_TBWC8:1;          /* [20:20] Trigger CMP_IRQ_NOTIFY.TBWC[c] bit by software - RW */
    ureg32 TRG_TBWC9:1;          /* [21:21] Trigger CMP_IRQ_NOTIFY.TBWC[c] bit by software - RW */
    ureg32 TRG_TBWC10:1;         /* [22:22] Trigger CMP_IRQ_NOTIFY.TBWC[c] bit by software - RW */
    ureg32 TRG_TBWC11:1;         /* [23:23] Trigger CMP_IRQ_NOTIFY.TBWC[c] bit by software - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_CMP_IRQ_FORCINT_Bits;

/* CMP interrupt mode configuration register */
typedef struct
{
    ureg32 IRQ_MODE:2;           /* [1:0] IRQ mode selection - RW */
    ureg32 reserved_2:30;        /* [31:2] Internal  reserved */
} GTM_CMP_IRQ_MODE_Bits;

/* CMP error interrupt enable register */
typedef struct
{
    ureg32 ABWC0_EN_EIRQ:1;         /* [0:0] Enable ABWC comparator [c] interrupt source for CMP_EIRQ line - RW */
    ureg32 ABWC1_EN_EIRQ:1;         /* [1:1] Enable ABWC comparator [c] interrupt source for CMP_EIRQ line - RW */
    ureg32 ABWC2_EN_EIRQ:1;         /* [2:2] Enable ABWC comparator [c] interrupt source for CMP_EIRQ line - RW */
    ureg32 ABWC3_EN_EIRQ:1;         /* [3:3] Enable ABWC comparator [c] interrupt source for CMP_EIRQ line - RW */
    ureg32 ABWC4_EN_EIRQ:1;         /* [4:4] Enable ABWC comparator [c] interrupt source for CMP_EIRQ line - RW */
    ureg32 ABWC5_EN_EIRQ:1;         /* [5:5] Enable ABWC comparator [c] interrupt source for CMP_EIRQ line - RW */
    ureg32 ABWC6_EN_EIRQ:1;         /* [6:6] Enable ABWC comparator [c] interrupt source for CMP_EIRQ line - RW */
    ureg32 ABWC7_EN_EIRQ:1;         /* [7:7] Enable ABWC comparator [c] interrupt source for CMP_EIRQ line - RW */
    ureg32 ABWC8_EN_EIRQ:1;         /* [8:8] Enable ABWC comparator [c] interrupt source for CMP_EIRQ line - RW */
    ureg32 ABWC9_EN_EIRQ:1;         /* [9:9] Enable ABWC comparator [c] interrupt source for CMP_EIRQ line - RW */
    ureg32 ABWC10_EN_EIRQ:1;        /* [10:10] Enable ABWC comparator [c] interrupt source for CMP_EIRQ line - RW */
    ureg32 ABWC11_EN_EIRQ:1;        /* [11:11] Enable ABWC comparator [c] interrupt source for CMP_EIRQ line - RW */
    ureg32 TBWC0_EN_EIRQ:1;         /* [12:12] Enable TBWC comparator [c] interrupt source for CMP_EIRQ line - RW */
    ureg32 TBWC1_EN_EIRQ:1;         /* [13:13] Enable TBWC comparator [c] interrupt source for CMP_EIRQ line - RW */
    ureg32 TBWC2_EN_EIRQ:1;         /* [14:14] Enable TBWC comparator [c] interrupt source for CMP_EIRQ line - RW */
    ureg32 TBWC3_EN_EIRQ:1;         /* [15:15] Enable TBWC comparator [c] interrupt source for CMP_EIRQ line - RW */
    ureg32 TBWC4_EN_EIRQ:1;         /* [16:16] Enable TBWC comparator [c] interrupt source for CMP_EIRQ line - RW */
    ureg32 TBWC5_EN_EIRQ:1;         /* [17:17] Enable TBWC comparator [c] interrupt source for CMP_EIRQ line - RW */
    ureg32 TBWC6_EN_EIRQ:1;         /* [18:18] Enable TBWC comparator [c] interrupt source for CMP_EIRQ line - RW */
    ureg32 TBWC7_EN_EIRQ:1;         /* [19:19] Enable TBWC comparator [c] interrupt source for CMP_EIRQ line - RW */
    ureg32 TBWC8_EN_EIRQ:1;         /* [20:20] Enable TBWC comparator [c] interrupt source for CMP_EIRQ line - RW */
    ureg32 TBWC9_EN_EIRQ:1;         /* [21:21] Enable TBWC comparator [c] interrupt source for CMP_EIRQ line - RW */
    ureg32 TBWC10_EN_EIRQ:1;        /* [22:22] Enable TBWC comparator [c] interrupt source for CMP_EIRQ line - RW */
    ureg32 TBWC11_EN_EIRQ:1;        /* [23:23] Enable TBWC comparator [c] interrupt source for CMP_EIRQ line - RW */
    ureg32 reserved_24:8;           /* [31:24] Internal  reserved */
} GTM_CMP_EIRQ_EN_Bits;

/* TIM[i] channel [x] general purpose 0 register */
typedef struct
{
    ureg32 GPR0:24;        /* [23:0] Input signal characteristic parameter 0 - RW */
    ureg32 ECNT:8;         /* [31:24] Edge counter - value refers to TIM[i]_CH[x]_ECNT.ECNT[7:0]. - RO */
} GTM_TIM_CH_GPR0_Bits;

/* TIM[i] channel [x] general purpose 1 register */
typedef struct
{
    ureg32 GPR1:24;        /* [23:0] Input signal characteristic parameter 1 - RW */
    ureg32 ECNT:8;         /* [31:24] Edge counter - value refers to TIM[i]_CH[x]_ECNT.ECNT[7:0]. - RO */
} GTM_TIM_CH_GPR1_Bits;

/* TIM[i] channel [x] SMU counter register */
typedef struct
{
    ureg32 CNT:24;               /* [23:0] Actual SMU counter value - RO */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_TIM_CH_CNT_Bits;

/* TIM[i] channel [x] SMU edge counter register */
typedef struct
{
    ureg32 ECNT:16;               /* [15:0] Edge counter - RO */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_TIM_CH_ECNT_Bits;

/* TIM[i] channel [x] SMU shadow counter register */
typedef struct
{
    ureg32 CNTS:24;        /* [23:0] Counter shadow register - RW */
    ureg32 ECNT:8;         /* [31:24] Edge counter - RO */
} GTM_TIM_CH_CNTS_Bits;

/* TIM[i] channel [x] TDU counter register */
typedef struct
{
    ureg32 TO_CNT:8;             /* [7:0] Current Timeout value slice0 for channel [y] - RW */
    ureg32 TO_CNT1:8;            /* [15:8] Current Timeout value slice1 for channel [y] - RW */
    ureg32 TO_CNT2:8;            /* [23:16] Current Timeout value slice2 for channel [y] - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_TIM_CH_TDUC_Bits;

/* TIM[i] channel [x] TDU control register */
typedef struct
{
    ureg32 TOV:8;                       /* [7:0] Time out compare value slice0 for channel [y] - RW */
    ureg32 TOV1:8;                      /* [15:8] Time out compare value slice1 for channel [y]  - RW */
    ureg32 TOV2:8;                      /* [23:16] Time out compare value slice2 for channel [y]  - RW */
    ureg32 SLICING:2;                   /* [25:24] Cascading of counter slices  - RW */
    ureg32 TCS_USE_SAMPLE_EVT:1;        /* [26:26] Use TDU_SAMPLE_EVT as Timeout Clock - RW */
    ureg32 TDU_SAME_CNT_CLK:1;          /* [27:27] Define clocking of TO_CNT - TO_CNT1 - RW */
    ureg32 TCS:3;                       /* [30:28] Timeout clock selection - RW */
    ureg32 reserved_31:1;               /* [31:31] Internal  reserved */
} GTM_TIM_CH_TDUV_Bits;

/* TIM[i] channel [x] filter parameter 0 register */
typedef struct
{
    ureg32 FLT_RE:24;            /* [23:0] Filter parameter for rising edge - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_TIM_CH_FLT_RE_Bits;

/* TIM[i] channel [x] filter parameter 1 register */
typedef struct
{
    ureg32 FLT_FE:24;            /* [23:0] Filter parameter for falling edge - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_TIM_CH_FLT_FE_Bits;

/* TIM[i] channel [x] control register */
typedef struct
{
    ureg32 TIM_EN:1;             /* [0:0] TIM channel [x] enable - RW */
    ureg32 TIM_MODE:3;           /* [3:1] TIM channel [x] mode - RW */
    ureg32 OSM:1;                /* [4:4] One-shot mode - RW */
    ureg32 ARU_EN:1;             /* [5:5] TIM[i]_CH[x]_GPR0 and TIM[i]_CH[x]_GPR1 register values routed to ARU. - RW */
    ureg32 CICTRL:1;             /* [6:6] Channel Input Control - RW */
    ureg32 TBU0_SEL:1;           /* [7:7] TIM_TBU_TS0 bits input select for TIM0_CH[x]_GPR0 and TIM0_CH[x]_GPR1 - RW */
    ureg32 GPR0_SEL:2;           /* [9:8] Selection for TIM[i]_CH[x]_GPR0 register - RW */
    ureg32 GPR1_SEL:2;           /* [11:10] Selection for TIM[i]_CH[x]_GPR1 register - RW */
    ureg32 CNTS_SEL:1;           /* [12:12] Selection for TIM[i]_CH[x]_CNTS register - RW */
    ureg32 DSL:1;                /* [13:13] Signal level control - RW */
    ureg32 ISL:1;                /* [14:14] Ignore signal level - RW */
    ureg32 ECNT_RESET:1;         /* [15:15] Enables resetting of counter in certain modes - RW */
    ureg32 FLT_EN:1;             /* [16:16] Filter enable for channel [x] - RW */
    ureg32 FLT_CNT_FRQ:2;        /* [18:17] Filter counter frequency select - RW */
    ureg32 EXT_CAP_EN:1;         /* [19:19] Enables external capture mode. The selected TIM mode is only sensitive to external capture pulses the input event changes are ignored. - RW */
    ureg32 FLT_MODE_RE:1;        /* [20:20] Filter mode for rising edge - RW */
    ureg32 FLT_CTR_RE:1;         /* [21:21] Filter counter mode for rising edge - RW */
    ureg32 FLT_MODE_FE:1;        /* [22:22] Filter mode for falling edge - RW */
    ureg32 FLT_CTR_FE:1;         /* [23:23] Filter counter mode for falling edge - RW */
    ureg32 CLK_SEL:3;            /* [26:24] CMU clock source select for channel - RW */
    ureg32 FR_ECNT_OFL:1;        /* [27:27] Extended Edge counter overflow behavior - RW */
    ureg32 EGPR0_SEL:1;          /* [28:28] Extension of TIM[i]_CH[x]_CTRL.GPR0_SEL bit field - RW */
    ureg32 EGPR1_SEL:1;          /* [29:29] Extension of TIM[i]_CH[x]_CTRL.GPR1_SEL bit field - RW */
    ureg32 TOCTRL:2;             /* [31:30] Timeout control - RW */
} GTM_TIM_CH_CTRL_Bits;

/* TIM[i] channel [x] extended control register */
typedef struct
{
    ureg32 EXT_CAP_SRC:4;            /* [3:0] Defines selected source for triggering the TIM_EXT_CAPTURE functionality.  - RW */
    ureg32 reserved_4:1;             /* [4:4] Internal  reserved */
    ureg32 USE_PREV_TDU_IN:1;        /* [5:5] Select input data source for TDU - RW */
    ureg32 TODET_IRQ_SRC:2;          /* [7:6] Selection of source for TIM_TODET_IRQ - RW */
    ureg32 TDU_START:3;              /* [10:8] Defines condition which will start the TDU unit.  - RW */
    ureg32 reserved_11:1;            /* [11:11] Internal  reserved */
    ureg32 TDU_STOP:3;               /* [14:12] Defines condition which will stop the TDU unit.  - RW */
    ureg32 reserved_15:1;            /* [15:15] Internal  reserved */
    ureg32 TDU_RESYNC:4;             /* [19:16] Defines condition which will resynchronize the TDU unit.  - RW */
    ureg32 reserved_20:2;            /* [21:20] Internal  reserved */
    ureg32 USE_LUT:2;                /* [23:22] Generate filter input by lookup table - RW */
    ureg32 EFLT_CTR_RE:1;            /* [24:24] Extension of bit field TIM[i]_CH[x]_CTRL.FLT_CTR_RE - RW */
    ureg32 EFLT_CTR_FE:1;            /* [25:25] Extension of bit field TIM[i]_CH[x]_CTRL.FLT_CTR_FE - RW */
    ureg32 reserved_26:2;            /* [27:26] Internal  reserved */
    ureg32 SWAP_CAPTURE:1;           /* [28:28] Swap point in time of capturing TIM[i]_CH[x]_CNTS and TIM[i]_CH[x]_GPR1 - RW */
    ureg32 IMM_START:1;              /* [29:29] Start the measurement immediately - RW */
    ureg32 ECLK_SEL:1;               /* [30:30] Extension of bit field TIM[i]_CH[x]_CTRL.CLK_SEL  - RW */
    ureg32 USE_PREV_CH_IN:1;         /* [31:31] Select input data source for TIM channel - RW */
} GTM_TIM_CH_ECTRL_Bits;

/* TIM[i] channel [x] interrupt notification register */
typedef struct
{
    ureg32 NEWVAL:1;             /* [0:0] New measurement value detected by the channel [x] ([x]:0...m-1) - RW */
    ureg32 ECNTOFL:1;            /* [1:1] ECNT counter overflow of channel [x] ([x]:0...m-1) - RW */
    ureg32 CNTOFL:1;             /* [2:2] SMU TIM[i]_CH[x]_CNT counter overflow of channel [x] - ([x]:0...m-1) - RW */
    ureg32 GPROFL:1;             /* [3:3] TIM[i]_CH[x]_GPR0 and TIM[i]_CH[x]_GPR1 data overflow - old data not read out before new data has arrived at input pin - ([x]:0...m-1) - RW */
    ureg32 TODET:1;              /* [4:4] Timeout reached for input signal of channel [x] - ([x]:0...m-1) - RW */
    ureg32 GLITCHDET:1;          /* [5:5] Glitch detected on channel [x] - ([x]:0...m-1) - RW */
    ureg32 reserved_6:26;        /* [31:6] Internal  reserved */
} GTM_TIM_CH_IRQ_NOTIFY_Bits;

/* TIM[i] channel [x] interrupt enable register */
typedef struct
{
    ureg32 NEWVAL_IRQ_EN:1;           /* [0:0] TIM_NEWVAL_IRQ[x:x] interrupt enable - RW */
    ureg32 ECNTOFL_IRQ_EN:1;          /* [1:1] TIM_ECNTOFL_IRQ[x:x] interrupt enable - RW */
    ureg32 CNTOFL_IRQ_EN:1;           /* [2:2] TIM_CNTOFL_IRQ[x:x] interrupt enable - RW */
    ureg32 GPROFL_IRQ_EN:1;           /* [3:3] TIM_GPROFL_IRQ[x:x] interrupt enable - RW */
    ureg32 TODET_IRQ_EN:1;            /* [4:4] TIM_TODET_IRQ[x:x] interrupt enable - RW */
    ureg32 GLITCHDET_IRQ_EN:1;        /* [5:5] TIM_GLITCHDET_IRQ[x:x] interrupt enable - RW */
    ureg32 reserved_6:26;             /* [31:6] Internal  reserved */
} GTM_TIM_CH_IRQ_EN_Bits;

/* TIM[i] channel [x] force interrupt register */
typedef struct
{
    ureg32 TRG_NEWVAL:1;           /* [0:0] Trigger the bit TIM_CH[x]_IRQ_NOTIFY.NEWVAL by software - RW */
    ureg32 TRG_ECNTOFL:1;          /* [1:1] Trigger the bit TIM_CHx_IRQ_NOTIFY.ECNTOFL by software - RW */
    ureg32 TRG_CNTOFL:1;           /* [2:2] Trigger the bit TIM_CH[x]_IRQ_NOTIFY.CNTOFL by software - RW */
    ureg32 TRG_GPROFL:1;           /* [3:3] Trigger the bit TIM_CH[x]_IRQ_NOTIFY.GPROFL by software - RW */
    ureg32 TRG_TODET:1;            /* [4:4] Trigger the bit TIM_CH[x]_IRQ_NOTIFY.TODET by software - RW */
    ureg32 TRG_GLITCHDET:1;        /* [5:5] Trigger the bit TIM_CH[x]_IRQ_NOTIFY.GLITCHDET by software - RW */
    ureg32 reserved_6:26;          /* [31:6] Internal  reserved */
} GTM_TIM_CH_IRQ_FORCINT_Bits;

/* TIM[i] channel [x] interrupt mode configuration register */
typedef struct
{
    ureg32 IRQ_MODE:2;           /* [1:0] IRQ mode selection of channel [x] - RW */
    ureg32 reserved_2:30;        /* [31:2] Internal  reserved */
} GTM_TIM_CH_IRQ_MODE_Bits;

/* TIM[i] channel [x] error interrupt enable register */
typedef struct
{
    ureg32 NEWVAL_EIRQ_EN:1;           /* [0:0] TIM_NEWVAL[x]_EIRQ error interrupt enable - RW */
    ureg32 ECNTOFL_EIRQ_EN:1;          /* [1:1] TIM_ECNTOFL_IRQ[x:x] interrupt enable - RW */
    ureg32 CNTOFL_EIRQ_EN:1;           /* [2:2] TIM_CNTOFL_IRQ[x:x] interrupt enable - RW */
    ureg32 GPROFL_EIRQ_EN:1;           /* [3:3] TIM_GPROFL_IRQ[x:x] interrupt enable - RW */
    ureg32 TODET_EIRQ_EN:1;            /* [4:4] TIM_TODET_IRQ[x:x] interrupt enable - RW */
    ureg32 GLITCHDET_EIRQ_EN:1;        /* [5:5] TIM_GLITCHDET_IRQ[x:x] interrupt enable - RW */
    ureg32 reserved_6:26;              /* [31:6] Internal  reserved */
} GTM_TIM_CH_EIRQ_EN_Bits;

/* TIM[i] input value observation register */
typedef struct
{
    ureg32 F_OUT0:1;             /* [0:0] Signal channel [x] after TIM FLT unit - RO */
    ureg32 F_OUT1:1;             /* [1:1] Signal channel [x] after TIM FLT unit - RO */
    ureg32 F_OUT2:1;             /* [2:2] Signal channel [x] after TIM FLT unit - RO */
    ureg32 F_OUT3:1;             /* [3:3] Signal channel [x] after TIM FLT unit - RO */
    ureg32 F_OUT4:1;             /* [4:4] Signal channel [x] after TIM FLT unit - RO */
    ureg32 F_OUT5:1;             /* [5:5] Signal channel [x] after TIM FLT unit - RO */
    ureg32 F_OUT6:1;             /* [6:6] Signal channel [x] after TIM FLT unit - RO */
    ureg32 F_OUT7:1;             /* [7:7] Signal channel [x] after TIM FLT unit - RO */
    ureg32 F_IN0:1;              /* [8:8] Signal channel [x] after INPSRC selection - before TIM FLT unit - RO */
    ureg32 F_IN1:1;              /* [9:9] Signal channel [x] after INPSRC selection - before TIM FLT unit - RO */
    ureg32 F_IN2:1;              /* [10:10] Signal channel [x] after INPSRC selection - before TIM FLT unit - RO */
    ureg32 F_IN3:1;              /* [11:11] Signal channel [x] after INPSRC selection - before TIM FLT unit - RO */
    ureg32 F_IN4:1;              /* [12:12] Signal channel [x] after INPSRC selection - before TIM FLT unit - RO */
    ureg32 F_IN5:1;              /* [13:13] Signal channel [x] after INPSRC selection - before TIM FLT unit - RO */
    ureg32 F_IN6:1;              /* [14:14] Signal channel [x] after INPSRC selection - before TIM FLT unit - RO */
    ureg32 F_IN7:1;              /* [15:15] Signal channel [x] after INPSRC selection - before TIM FLT unit - RO */
    ureg32 TIM_IN0:1;            /* [16:16] Signal channel [x] after TIM input signal synchronization - RO */
    ureg32 TIM_IN1:1;            /* [17:17] Signal channel [x] after TIM input signal synchronization - RO */
    ureg32 TIM_IN2:1;            /* [18:18] Signal channel [x] after TIM input signal synchronization - RO */
    ureg32 TIM_IN3:1;            /* [19:19] Signal channel [x] after TIM input signal synchronization - RO */
    ureg32 TIM_IN4:1;            /* [20:20] Signal channel [x] after TIM input signal synchronization - RO */
    ureg32 TIM_IN5:1;            /* [21:21] Signal channel [x] after TIM input signal synchronization - RO */
    ureg32 TIM_IN6:1;            /* [22:22] Signal channel [x] after TIM input signal synchronization - RO */
    ureg32 TIM_IN7:1;            /* [23:23] Signal channel [x] after TIM input signal synchronization - RO */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_TIM_INP_VAL_Bits;

/* TIM[i] AUX IN source selection register */
typedef struct
{
    ureg32 VAL_0:2;         /* [1:0] Value to be fed to channel [x] - RW */
    ureg32 MODE_0:2;        /* [3:2] Input source to channel [x] - RW */
    ureg32 VAL_1:2;         /* [5:4] Value to be fed to channel [x] - RW */
    ureg32 MODE_1:2;        /* [7:6] Input source to channel [x] - RW */
    ureg32 VAL_2:2;         /* [9:8] Value to be fed to channel [x] - RW */
    ureg32 MODE_2:2;        /* [11:10] Input source to channel [x] - RW */
    ureg32 VAL_3:2;         /* [13:12] Value to be fed to channel [x] - RW */
    ureg32 MODE_3:2;        /* [15:14] Input source to channel [x] - RW */
    ureg32 VAL_4:2;         /* [17:16] Value to be fed to channel [x] - RW */
    ureg32 MODE_4:2;        /* [19:18] Input source to channel [x] - RW */
    ureg32 VAL_5:2;         /* [21:20] Value to be fed to channel [x] - RW */
    ureg32 MODE_5:2;        /* [23:22] Input source to channel [x] - RW */
    ureg32 VAL_6:2;         /* [25:24] Value to be fed to channel [x] - RW */
    ureg32 MODE_6:2;        /* [27:26] Input source to channel [x] - RW */
    ureg32 VAL_7:2;         /* [29:28] Value to be fed to channel [x] - RW */
    ureg32 MODE_7:2;        /* [31:30] Input source to channel [x] - RW */
} GTM_TIM_IN_SRC_Bits;

/* TIM[i] global software reset register */
typedef struct
{
    ureg32 RST_CH0:1;            /* [0:0] Software reset of channel [x] - RW */
    ureg32 RST_CH1:1;            /* [1:1] Software reset of channel [x] - RW */
    ureg32 RST_CH2:1;            /* [2:2] Software reset of channel [x] - RW */
    ureg32 RST_CH3:1;            /* [3:3] Software reset of channel [x] - RW */
    ureg32 RST_CH4:1;            /* [4:4] Software reset of channel [x] - RW */
    ureg32 RST_CH5:1;            /* [5:5] Software reset of channel [x] - RW */
    ureg32 RST_CH6:1;            /* [6:6] Software reset of channel [x] - RW */
    ureg32 RST_CH7:1;            /* [7:7] Software reset of channel [x] - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIM_RST_Bits;

/* TOM[i] channel [x] control register */
typedef struct
{
    ureg32 reserved_0:7;         /* [6:0] Internal  reserved */
    ureg32 SR0_TRIG:1;           /* [7:7] TOM[i]_CH[x]_SR0 is used to generate a trigger on output TOM_OUT_T[x:x] if equal to TOM[i]_CH[x]_CN0. - RW */
    ureg32 reserved_8:3;         /* [10:8] Internal  reserved */
    ureg32 SL:1;                 /* [11:11] Signal level for pulse width - RW */
    ureg32 CLK_SRC:4;            /* [15:12] Clock source select for channel - RW */
    ureg32 reserved_16:1;        /* [16:16] Internal  reserved */
    ureg32 TRIG_PULSE:1;         /* [17:17] Trigger output pulse length of one cluster clock period - RW */
    ureg32 UDMODE:2;             /* [19:18] Up-down counter mode - RW */
    ureg32 RST_CCU0:1;           /* [20:20] Reset source of CCU0 - RW */
    ureg32 OSM_TRIG:1;           /* [21:21] One-shot pulse generation enabled by the selected trigger signal - RW */
    ureg32 EXT_TRIG:1;           /* [22:22] Select TOM_EXT_TRIGIN[x:x] as trigger signal - RW */
    ureg32 EXTTRIGOUT:1;         /* [23:23] Select TOM_EXT_TRIGIN[x:x] as potential output signal TOM_CH_TRIGOUT[x:x] - RW */
    ureg32 TRIGOUT:1;            /* [24:24] Trigger output selection (output signal TOM_CH_TRIGOUT[x:x]) of module TOM channel [x] - RW */
    ureg32 SPE_TRIG:1;           /* [25:25] SPE trigger to reset TOM[i]_CH[x]_CN0 - RW */
    ureg32 OSM:1;                /* [26:26] One-shot mode. In this mode the counter TOM[i]_CH[x]_CN0 counts for only one period. The length of period is defined by TOM[i]_CH[x]_CM0. A write access to the register TOM[i]_CH[x]_CN0 triggers the start of counting. - RW */
    ureg32 BITREV:1;             /* [27:27] Bit-reversing of output of counter TOM[i]_CH[x]_CN0. - RW */
    ureg32 SPEM:1;               /* [28:28] SPE output mode enable for channel. - RW */
    ureg32 GCM:1;                /* [29:29] Gated Counter Mode enable - RW */
    ureg32 reserved_30:1;        /* [30:30] Internal  reserved */
    ureg32 FREEZE:1;             /* [31:31] TOM[i] Freeze Mode enable - RW */
} GTM_TOM_CH_CTRL_Bits;

/* TOM[i] channel [x] CCU0 compare shadow register */
typedef struct
{
    ureg32 SR0:16;                /* [15:0] TOM[i] channel [x] shadow register TOM[i]_CH[x]_SR0 for update of compare register TOM[i]_CH[x]_CM0 - RW */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_TOM_CH_SR0_Bits;

/* TOM[i] channel [x] CCU1 compare shadow register */
typedef struct
{
    ureg32 SR1:16;                /* [15:0] TOM[i] channel [x] shadow register TOM[i]_CH[x]_SR1 for update of compare register TOM[i]_CH[x]_CM1 - RW */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_TOM_CH_SR1_Bits;

/* TOM[i] channel [x] CCU0 compare register */
typedef struct
{
    ureg32 CM0:16;                /* [15:0] TOM[i] channel [x] CCU0 compare register - RW */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_TOM_CH_CM0_Bits;

/* TOM[i] channel [x] CCU1 compare register */
typedef struct
{
    ureg32 CM1:16;                /* [15:0] TOM[i] channel [x] CCU1 compare register - RW */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_TOM_CH_CM1_Bits;

/* TOM[i] channel [x] CCU0 counter */
typedef struct
{
    ureg32 CN0:16;                /* [15:0] TOM[i] CCU0 counter  - RW */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_TOM_CH_CN0_Bits;

/* TOM[i] channel [x] status register */
typedef struct
{
    ureg32 OL:1;                 /* [0:0] Output level of output TOM_OUT[x:x] - RO */
    ureg32 reserved_1:28;        /* [28:1] Internal  reserved */
    ureg32 OSM_RTF:1;            /* [29:29] Oneshot mode retrigger failed flag - RW */
    ureg32 reserved_30:2;        /* [31:30] Internal  reserved */
} GTM_TOM_CH_STAT_Bits;

/* TOM[i] channel [x] interrupt notification register */
typedef struct
{
    ureg32 CCU0TC:1;             /* [0:0] CCU0 Trigger condition interrupt for channel [x] - RW */
    ureg32 CCU1TC:1;             /* [1:1] CCU1 Trigger condition interrupt for channel [x] - RW */
    ureg32 reserved_2:30;        /* [31:2] Internal  reserved */
} GTM_TOM_CH_IRQ_NOTIFY_Bits;

/* TOM[i] channel [x] interrupt enable register */
typedef struct
{
    ureg32 CCU0TC_IRQ_EN:1;        /* [0:0] TOM_CCU0TC[x]_IRQ interrupt enable - RW */
    ureg32 CCU1TC_IRQ_EN:1;        /* [1:1] TOM_CCU1TC[x]_IRQ interrupt enable - RW */
    ureg32 reserved_2:30;          /* [31:2] Internal  reserved */
} GTM_TOM_CH_IRQ_EN_Bits;

/* TOM[i] channel [x] force interrupt register */
typedef struct
{
    ureg32 TRG_CCU0TC:1;         /* [0:0] Trigger the bit TOM[i]_CH[x]_IRQ_NOTIFY.CCU0TC by software - RW */
    ureg32 TRG_CCU1TC:1;         /* [1:1] Trigger the bit TOM[i]_CH[x]_IRQ_NOTIFY.CCU1TC by software - RW */
    ureg32 reserved_2:30;        /* [31:2] Internal  reserved */
} GTM_TOM_CH_IRQ_FORCINT_Bits;

/* TOM[i] channel [x] interrupt mode register */
typedef struct
{
    ureg32 IRQ_MODE:2;           /* [1:0] IRQ mode selection - RW */
    ureg32 reserved_2:30;        /* [31:2] Internal  reserved */
} GTM_TOM_CH_IRQ_MODE_Bits;

/* TOM[i] channel [x] control register */
typedef struct
{
    ureg32 HRES:1;               /* [0:0] TOM[i] high resolution support  - RW */
    ureg32 reserved_1:31;        /* [31:1] Internal  reserved */
} GTM_TOM_CH_CTRL2_Bits;

/* TOM[i] channel [x] control shadow register */
typedef struct
{
    ureg32 reserved_0:11;         /* [10:0] Internal  reserved */
    ureg32 SL_SR:1;               /* [11:11] Shadow register for TOM[i]_CH[x]_CTRL.SL - RW */
    ureg32 CLK_SRC_SR:4;          /* [15:12] Shadow register for TOM[i]_CH[x]_CTRL.CLK_SRC - RW */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_TOM_CH_CTRL_SR_Bits;

/* TOM[i] TGC [g] global control register */
typedef struct
{
    ureg32 HOST_TRIG:1;         /* [0:0] Trigger request signal to update the register TOM[i]_TGC[g]_ENDIS_STAT - TOM[i]_TGC[g]_OUTEN_STAT - RW */
    ureg32 reserved_1:7;        /* [7:1] Internal  reserved */
    ureg32 RST_CH0:1;           /* [8:8] Software reset of channel [x]; x = c + g*8 - RW */
    ureg32 RST_CH1:1;           /* [9:9] Software reset of channel [x]; x = c + g*8 - RW */
    ureg32 RST_CH2:1;           /* [10:10] Software reset of channel [x]; x = c + g*8 - RW */
    ureg32 RST_CH3:1;           /* [11:11] Software reset of channel [x]; x = c + g*8 - RW */
    ureg32 RST_CH4:1;           /* [12:12] Software reset of channel [x]; x = c + g*8 - RW */
    ureg32 RST_CH5:1;           /* [13:13] Software reset of channel [x]; x = c + g*8 - RW */
    ureg32 RST_CH6:1;           /* [14:14] Software reset of channel [x]; x = c + g*8 - RW */
    ureg32 RST_CH7:1;           /* [15:15] Software reset of channel [x]; x = c + g*8 - RW */
    ureg32 UPEN_CTRL0:2;        /* [17:16] TOM[i] channel [x] ( x=c + g*8 ) enable update of register TOM[i]_CH[x]_CM0 - TOM[i]_CH[x]_CM1 - TOM[i]_CH[x]_CTRL.SL and TOM[i]_CH[x]_CTRL.CLK_SRC from TOM[i]_CH[x]_SR0 - TOM[i]_CH[x]_SR1 - TOM[i]_CH[x]_CTRL_SL.SL_SR and TOM[i]_CH[x]_CTRL_SR.CLK_SRC_SR. - RW */
    ureg32 UPEN_CTRL1:2;        /* [19:18] TOM[i] channel [x] ( x=c + g*8 ) enable update of register TOM[i]_CH[x]_CM0 - TOM[i]_CH[x]_CM1 - TOM[i]_CH[x]_CTRL.SL and TOM[i]_CH[x]_CTRL.CLK_SRC from TOM[i]_CH[x]_SR0 - TOM[i]_CH[x]_SR1 - TOM[i]_CH[x]_CTRL_SL.SL_SR and TOM[i]_CH[x]_CTRL_SR.CLK_SRC_SR. - RW */
    ureg32 UPEN_CTRL2:2;        /* [21:20] TOM[i] channel [x] ( x=c + g*8 ) enable update of register TOM[i]_CH[x]_CM0 - TOM[i]_CH[x]_CM1 - TOM[i]_CH[x]_CTRL.SL and TOM[i]_CH[x]_CTRL.CLK_SRC from TOM[i]_CH[x]_SR0 - TOM[i]_CH[x]_SR1 - TOM[i]_CH[x]_CTRL_SL.SL_SR and TOM[i]_CH[x]_CTRL_SR.CLK_SRC_SR. - RW */
    ureg32 UPEN_CTRL3:2;        /* [23:22] TOM[i] channel [x] ( x=c + g*8 ) enable update of register TOM[i]_CH[x]_CM0 - TOM[i]_CH[x]_CM1 - TOM[i]_CH[x]_CTRL.SL and TOM[i]_CH[x]_CTRL.CLK_SRC from TOM[i]_CH[x]_SR0 - TOM[i]_CH[x]_SR1 - TOM[i]_CH[x]_CTRL_SL.SL_SR and TOM[i]_CH[x]_CTRL_SR.CLK_SRC_SR. - RW */
    ureg32 UPEN_CTRL4:2;        /* [25:24] TOM[i] channel [x] ( x=c + g*8 ) enable update of register TOM[i]_CH[x]_CM0 - TOM[i]_CH[x]_CM1 - TOM[i]_CH[x]_CTRL.SL and TOM[i]_CH[x]_CTRL.CLK_SRC from TOM[i]_CH[x]_SR0 - TOM[i]_CH[x]_SR1 - TOM[i]_CH[x]_CTRL_SL.SL_SR and TOM[i]_CH[x]_CTRL_SR.CLK_SRC_SR. - RW */
    ureg32 UPEN_CTRL5:2;        /* [27:26] TOM[i] channel [x] ( x=c + g*8 ) enable update of register TOM[i]_CH[x]_CM0 - TOM[i]_CH[x]_CM1 - TOM[i]_CH[x]_CTRL.SL and TOM[i]_CH[x]_CTRL.CLK_SRC from TOM[i]_CH[x]_SR0 - TOM[i]_CH[x]_SR1 - TOM[i]_CH[x]_CTRL_SL.SL_SR and TOM[i]_CH[x]_CTRL_SR.CLK_SRC_SR. - RW */
    ureg32 UPEN_CTRL6:2;        /* [29:28] TOM[i] channel [x] ( x=c + g*8 ) enable update of register TOM[i]_CH[x]_CM0 - TOM[i]_CH[x]_CM1 - TOM[i]_CH[x]_CTRL.SL and TOM[i]_CH[x]_CTRL.CLK_SRC from TOM[i]_CH[x]_SR0 - TOM[i]_CH[x]_SR1 - TOM[i]_CH[x]_CTRL_SL.SL_SR and TOM[i]_CH[x]_CTRL_SR.CLK_SRC_SR. - RW */
    ureg32 UPEN_CTRL7:2;        /* [31:30] TOM[i] channel [x] ( x=c + g*8 ) enable update of register TOM[i]_CH[x]_CM0 - TOM[i]_CH[x]_CM1 - TOM[i]_CH[x]_CTRL.SL and TOM[i]_CH[x]_CTRL.CLK_SRC from TOM[i]_CH[x]_SR0 - TOM[i]_CH[x]_SR1 - TOM[i]_CH[x]_CTRL_SL.SL_SR and TOM[i]_CH[x]_CTRL_SR.CLK_SRC_SR. - RW */
} GTM_TOM_TGC_GLB_CTRL_Bits;

/* TOM[i] TGC [g] action time base register */
typedef struct
{
    ureg32 ACT_TB:24;            /* [23:0] Specifies the signed compare value with selected signal CCM[i]_TBU_TS0 - CCM[i]_TBU_TS1 and CCM[i]_TBU_TS2. If selected CCM[i]_TBU_TS0 - CCM[i]_TBU_TS1 and CCM[i]_TBU_TS2 value is in the interval [TOM[i]_TGC[g]_ACT_TB.ACT_TB-007FFFFFh,TOM[i]_TGC[g]_ACT_TB.ACT_TB] the event is in the past and the trigger is generated immediately. Otherwise the event is in the future and the trigger is generated if selected CCM[i]_TBU_TS0 - CCM[i]_TBU_TS1 and CCM[i]_TBU_TS2 is equal to TOM[i]_TGC[g]_ACT_TB.ACT_TB. - RW */
    ureg32 TB_TRIG:1;            /* [24:24] Set trigger request - RW */
    ureg32 TBU_SEL:2;            /* [26:25] Selection of time base used for comparison - RW */
    ureg32 reserved_27:5;        /* [31:27] Internal  reserved */
} GTM_TOM_TGC_ACT_TB_Bits;

/* TOM[i] TGC [g] force update control register */
typedef struct
{
    ureg32 FUPD_CTRL0:2;        /* [1:0] Force update control of operation registers of TOM[i] channel [x] (x = c + g*8) - RW */
    ureg32 FUPD_CTRL1:2;        /* [3:2] Force update control of operation registers of TOM[i] channel [x] (x = c + g*8) - RW */
    ureg32 FUPD_CTRL2:2;        /* [5:4] Force update control of operation registers of TOM[i] channel [x] (x = c + g*8) - RW */
    ureg32 FUPD_CTRL3:2;        /* [7:6] Force update control of operation registers of TOM[i] channel [x] (x = c + g*8) - RW */
    ureg32 FUPD_CTRL4:2;        /* [9:8] Force update control of operation registers of TOM[i] channel [x] (x = c + g*8) - RW */
    ureg32 FUPD_CTRL5:2;        /* [11:10] Force update control of operation registers of TOM[i] channel [x] (x = c + g*8) - RW */
    ureg32 FUPD_CTRL6:2;        /* [13:12] Force update control of operation registers of TOM[i] channel [x] (x = c + g*8) - RW */
    ureg32 FUPD_CTRL7:2;        /* [15:14] Force update control of operation registers of TOM[i] channel [x] (x = c + g*8) - RW */
    ureg32 RSTCN0_CH0:2;        /* [17:16] Reset TOM[i]_CH[x]_CN0 of channel [x] (x=c + g*8) with the force update event - RW */
    ureg32 RSTCN0_CH1:2;        /* [19:18] Reset TOM[i]_CH[x]_CN0 of channel [x] (x=c + g*8) with the force update event - RW */
    ureg32 RSTCN0_CH2:2;        /* [21:20] Reset TOM[i]_CH[x]_CN0 of channel [x] (x=c + g*8) with the force update event - RW */
    ureg32 RSTCN0_CH3:2;        /* [23:22] Reset TOM[i]_CH[x]_CN0 of channel [x] (x=c + g*8) with the force update event - RW */
    ureg32 RSTCN0_CH4:2;        /* [25:24] Reset TOM[i]_CH[x]_CN0 of channel [x] (x=c + g*8) with the force update event - RW */
    ureg32 RSTCN0_CH5:2;        /* [27:26] Reset TOM[i]_CH[x]_CN0 of channel [x] (x=c + g*8) with the force update event - RW */
    ureg32 RSTCN0_CH6:2;        /* [29:28] Reset TOM[i]_CH[x]_CN0 of channel [x] (x=c + g*8) with the force update event - RW */
    ureg32 RSTCN0_CH7:2;        /* [31:30] Reset TOM[i]_CH[x]_CN0 of channel [x] (x=c + g*8) with the force update event - RW */
} GTM_TOM_TGC_FUPD_CTRL_Bits;

/* TOM[i] TGC [g] internal trigger control register */
typedef struct
{
    ureg32 INT_TRIG0:2;           /* [1:0] Select input signal TOM_CH_TRIGOUT[x:x] as a trigger source for TGC[g] (x=c + g*8) - RW */
    ureg32 INT_TRIG1:2;           /* [3:2] Select input signal TOM_CH_TRIGOUT[x:x] as a trigger source for TGC[g] (x=c + g*8) - RW */
    ureg32 INT_TRIG2:2;           /* [5:4] Select input signal TOM_CH_TRIGOUT[x:x] as a trigger source for TGC[g] (x=c + g*8) - RW */
    ureg32 INT_TRIG3:2;           /* [7:6] Select input signal TOM_CH_TRIGOUT[x:x] as a trigger source for TGC[g] (x=c + g*8) - RW */
    ureg32 INT_TRIG4:2;           /* [9:8] Select input signal TOM_CH_TRIGOUT[x:x] as a trigger source for TGC[g] (x=c + g*8) - RW */
    ureg32 INT_TRIG5:2;           /* [11:10] Select input signal TOM_CH_TRIGOUT[x:x] as a trigger source for TGC[g] (x=c + g*8) - RW */
    ureg32 INT_TRIG6:2;           /* [13:12] Select input signal TOM_CH_TRIGOUT[x:x] as a trigger source for TGC[g] (x=c + g*8) - RW */
    ureg32 INT_TRIG7:2;           /* [15:14] Select input signal TOM_CH_TRIGOUT[x:x] as a trigger source for TGC[g] (x=c + g*8) - RW */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_TOM_TGC_INT_TRIG_Bits;

/* TOM[i] TGC [g] enable/disable control register */
typedef struct
{
    ureg32 ENDIS_CTRL0:2;         /* [1:0] TOM[i] channel [x] (x=c + g*8) enable/disable control register. - RW */
    ureg32 ENDIS_CTRL1:2;         /* [3:2] TOM[i] channel [x] (x=c + g*8) enable/disable control register. - RW */
    ureg32 ENDIS_CTRL2:2;         /* [5:4] TOM[i] channel [x] (x=c + g*8) enable/disable control register. - RW */
    ureg32 ENDIS_CTRL3:2;         /* [7:6] TOM[i] channel [x] (x=c + g*8) enable/disable control register. - RW */
    ureg32 ENDIS_CTRL4:2;         /* [9:8] TOM[i] channel [x] (x=c + g*8) enable/disable control register. - RW */
    ureg32 ENDIS_CTRL5:2;         /* [11:10] TOM[i] channel [x] (x=c + g*8) enable/disable control register. - RW */
    ureg32 ENDIS_CTRL6:2;         /* [13:12] TOM[i] channel [x] (x=c + g*8) enable/disable control register. - RW */
    ureg32 ENDIS_CTRL7:2;         /* [15:14] TOM[i] channel [x] (x=c + g*8) enable/disable control register. - RW */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_TOM_TGC_ENDIS_CTRL_Bits;

/* TOM[i] TGC [g] enable/disable status register */
typedef struct
{
    ureg32 ENDIS_STAT0:2;         /* [1:0] TOM[i] channel [x] ( x=c + g*8 ) enable/disable status register - RW */
    ureg32 ENDIS_STAT1:2;         /* [3:2] TOM[i] channel [x] ( x=c + g*8 ) enable/disable status register - RW */
    ureg32 ENDIS_STAT2:2;         /* [5:4] TOM[i] channel [x] ( x=c + g*8 ) enable/disable status register - RW */
    ureg32 ENDIS_STAT3:2;         /* [7:6] TOM[i] channel [x] ( x=c + g*8 ) enable/disable status register - RW */
    ureg32 ENDIS_STAT4:2;         /* [9:8] TOM[i] channel [x] ( x=c + g*8 ) enable/disable status register - RW */
    ureg32 ENDIS_STAT5:2;         /* [11:10] TOM[i] channel [x] ( x=c + g*8 ) enable/disable status register - RW */
    ureg32 ENDIS_STAT6:2;         /* [13:12] TOM[i] channel [x] ( x=c + g*8 ) enable/disable status register - RW */
    ureg32 ENDIS_STAT7:2;         /* [15:14] TOM[i] channel [x] ( x=c + g*8 ) enable/disable status register - RW */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_TOM_TGC_ENDIS_STAT_Bits;

/* TOM[i] TGC [g] output enable control register */
typedef struct
{
    ureg32 OUTEN_CTRL0:2;         /* [1:0] Output enable control of TOM [i] channel [x] ouput TOM_OUT[x:x] - x=c+g*8 - RW */
    ureg32 OUTEN_CTRL1:2;         /* [3:2] Output enable control of TOM [i] channel [x] ouput TOM_OUT[x:x] - x=c+g*8 - RW */
    ureg32 OUTEN_CTRL2:2;         /* [5:4] Output enable control of TOM [i] channel [x] ouput TOM_OUT[x:x] - x=c+g*8 - RW */
    ureg32 OUTEN_CTRL3:2;         /* [7:6] Output enable control of TOM [i] channel [x] ouput TOM_OUT[x:x] - x=c+g*8 - RW */
    ureg32 OUTEN_CTRL4:2;         /* [9:8] Output enable control of TOM [i] channel [x] ouput TOM_OUT[x:x] - x=c+g*8 - RW */
    ureg32 OUTEN_CTRL5:2;         /* [11:10] Output enable control of TOM [i] channel [x] ouput TOM_OUT[x:x] - x=c+g*8 - RW */
    ureg32 OUTEN_CTRL6:2;         /* [13:12] Output enable control of TOM [i] channel [x] ouput TOM_OUT[x:x] - x=c+g*8 - RW */
    ureg32 OUTEN_CTRL7:2;         /* [15:14] Output enable control of TOM [i] channel [x] ouput TOM_OUT[x:x] - x=c+g*8 - RW */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_TOM_TGC_OUTEN_CTRL_Bits;

/* TOM[i] TGC [g] output enable status register */
typedef struct
{
    ureg32 OUTEN_STAT0:2;         /* [1:0] Output enable status of TOM [i] channel [x] ouput TOM_OUT[x:x] - x=c+g*8 - RW */
    ureg32 OUTEN_STAT1:2;         /* [3:2] Output enable status of TOM [i] channel [x] ouput TOM_OUT[x:x] - x=c+g*8 - RW */
    ureg32 OUTEN_STAT2:2;         /* [5:4] Output enable status of TOM [i] channel [x] ouput TOM_OUT[x:x] - x=c+g*8 - RW */
    ureg32 OUTEN_STAT3:2;         /* [7:6] Output enable status of TOM [i] channel [x] ouput TOM_OUT[x:x] - x=c+g*8 - RW */
    ureg32 OUTEN_STAT4:2;         /* [9:8] Output enable status of TOM [i] channel [x] ouput TOM_OUT[x:x] - x=c+g*8 - RW */
    ureg32 OUTEN_STAT5:2;         /* [11:10] Output enable status of TOM [i] channel [x] ouput TOM_OUT[x:x] - x=c+g*8 - RW */
    ureg32 OUTEN_STAT6:2;         /* [13:12] Output enable status of TOM [i] channel [x] ouput TOM_OUT[x:x] - x=c+g*8 - RW */
    ureg32 OUTEN_STAT7:2;         /* [15:14] Output enable status of TOM [i] channel [x] ouput TOM_OUT[x:x] - x=c+g*8 - RW */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_TOM_TGC_OUTEN_STAT_Bits;

/* ATOM[i] channel[x] ARU read address register */
typedef struct
{
    ureg32 RDADDR0:9;            /* [8:0] ARU Read address 0. - RW */
    ureg32 reserved_9:7;         /* [15:9] Internal  reserved */
    ureg32 RDADDR1:9;            /* [24:16] ARU Read address 1. - RW */
    ureg32 reserved_25:7;        /* [31:25] Internal  reserved */
} GTM_ATOM_CH_RDADDR_Bits;

/* ATOM[i] channel [x] control register */
typedef struct
{
    ureg32 MODE:2;               /* [1:0] ATOM channel mode select. - RW */
    ureg32 TB12_SEL:1;           /* [2:2] Select time base value CCM[i]_TBU_TS1 or CCM[i]_TBU_TS2. - RW */
    ureg32 ARU_EN:1;             /* [3:3] ARU Input stream enable. - RW */
    ureg32 ACB:5;                /* [8:4] ATOM Mode control bits. - RW */
    ureg32 CMP_CTRL:1;           /* [9:9] CCU[x] compare strategy select. - RW */
    ureg32 EUPM:1;               /* [10:10] Extended update mode - RW */
    ureg32 SL:1;                 /* [11:11] Initial signal level. - RW */
    ureg32 CLK_SRC:4;            /* [15:12] CMU clock source - RW */
    ureg32 WR_REQ:1;             /* [16:16] CPU Write request bit for late compare register update. - RW */
    ureg32 TRIG_PULSE:1;         /* [17:17] Trigger output pulse length of one cluster clock period - RW */
    ureg32 UDMODE:2;             /* [19:18] Up/down counter mode - RW */
    ureg32 RST_CCU0:1;           /* [20:20] Reset source of CCU0 - RW */
    ureg32 OSM_TRIG:1;           /* [21:21] Enable trigger of one-shot pulse by the selected trigger signal - RW */
    ureg32 EXT_TRIG:1;           /* [22:22] Select EXT_TRIGIN[x:x] as trigger signal - RW */
    ureg32 EXTTRIGOUT:1;         /* [23:23] Select EXT_TRIGIN[x:x] as potential output signal ATOM_CH_TRIGOUT[x:x] - RW */
    ureg32 TRIGOUT:1;            /* [24:24] Trigger output selection (output signal ATOM_CH_TRIGOUT[x:x]) of module ATOM [i] channel [x]. - RW */
    ureg32 SLA:1;                /* [25:25] 'Serve last' ARU communication strategy - RW */
    ureg32 OSM:1;                /* [26:26] One-shot mode - RW */
    ureg32 ABM:1;                /* [27:27] ARU blocking mode - RW */
    ureg32 reserved_28:1;        /* [28:28] Internal  reserved */
    ureg32 EXT_FUPD:1;           /* [29:29] Enable force update by external trigger signal - RW */
    ureg32 SOMB:1;               /* [30:30] SOMB mode - RW */
    ureg32 FREEZE:1;             /* [31:31] ATOM Freeze Mode enable - RW */
} GTM_ATOM_CH_CTRL_Bits;

/* ATOM[i] Channel[i] Control Register in SOMB Mode */
typedef struct
{
    ureg32 MODE:2;              /* [1:0] ATOM channel mode select - RW */
    ureg32 TB12_SEL:1;          /* [2:2] Select time base value TBU_TS1 or TBU_TS2 - RW */
    ureg32 ARU_EN:1;            /* [3:3] ARU Input stream enable - RW */
    ureg32 ACB10:2;               /* [5:4] Signal level control bits - RW */
    ureg32 ACB42:3;             /* [8:6] ATOM SOMB compare strategy - RW */
    ureg32 CMP_CTRL:1;          /* [9:9] CCUx compare strategy select - RW */
    ureg32 EUPM:1;              /* [10:10] Extended update mode - RW */
    ureg32 SL:1;                /* [11:11] Initial signal level after channel enable - RW */
    ureg32 reserved_12:4;        /* [15:12] Internal  reserved */
    ureg32 WR_REQ:1;            /* [16:16] CPU Write request bit for late compare register update - RW */
    ureg32 reserved_17:6;        /* [22:17] Internal  reserved */
    ureg32 EXTTRIGOUT:1;        /* [23:23] TIM_EXT_CAPTURE(x) as potential output signal TRIG_[x] - RW */
    ureg32 TRIGOUT:1;           /* [24:24] Trigger output selection (output signal TRIG_CHx) of module ATOM_CHx - RW */
    ureg32 reserved_25:2;        /* [26:25] Internal  reserved */
    ureg32 ABM:1;               /* [27:27] ARU blocking mode - RW */
    ureg32 reserved_28:1;        /* [28:28] Internal  reserved */
    ureg32 EXT_FUPD:1;          /* [29:29] Enable force update by external trigger signal - RW */
    ureg32 SOMB:1;              /* [30:30] SOMB: Set ATOM[i]_CH[x]_CTRL_SOMB.SOMB = 1 for ATOM SOMB mode - RW */
    ureg32 FREEZE:1;            /* [31:31] FREEZE - RW */
} GTM_ATOM_CH_SOMB_Bits;

/* ATOM[i] Channel[i] Control Register in SOMC Mode */
typedef struct
{
    ureg32 MODE:2;              /* [1:0] ATOM channel mode select - RW */
    ureg32 TB12_SEL:1;          /* [2:2] Select time base value TBU_TS1 or TBU_TS2 - RW */
    ureg32 ARU_EN:1;            /* [3:3] ARU Input stream enable - RW */
    ureg32 ACB10:2;               /* [5:4] Signal level control bits - RW */
    ureg32 ACB42:3;             /* [8:6] ATOM control bits ACB(4) - ACB(3) - ACB(2) - RW */
    ureg32 CMP_CTRL:1;          /* [9:9] CCUx compare strategy select - RW */
    ureg32 EUPM:1;              /* [10:10] Extended Update Mode - RW */
    ureg32 SL:1;                /* [11:11] Initial signal level after channel enable - RW */
    ureg32 reserved_12:4;        /* [15:12] Internal  reserved */
    ureg32 WR_REQ:1;            /* [16:16] CPU write request bit - RW */
    ureg32 reserved_17:6;        /* [22:17] Internal  reserved */
    ureg32 EXTTRIGOUT:1;        /* [23:23] Select TIM_EXT_CAPTURE(x) as potential output signal TRIG_[x] - RW */
    ureg32 TRIGOUT:1;           /* [24:24] TRIGOUT: Trigger output selection (output signal TRIG_CHx) of module ATOM_CHx - RW */
    ureg32 SLA:1;               /* [25:25] Serve last ARU communication strategy - RW */
    ureg32 reserved_26:1;        /* [26:26] Internal  reserved */
    ureg32 ABM:1;               /* [27:27] ARU blocking mode - RW */
    ureg32 reserved_28:2;        /* [29:28] Internal  reserved */
    ureg32 SOMB:1;              /* [30:30] SOMB: SOMB mode (Set ATOM[i]_CH[x]_CTRL_SOMC.SOMB = 0 in SOMC mode) - RW */
    ureg32 FREEZE:1;        /* [31:31] FREEZE - RW */
} GTM_ATOM_CH_SOMC_Bits;

/* ATOM[i] Channel[i] Control Register in SOMI Mode */
typedef struct
{
    ureg32 MODE:2;              /* [1:0] ATOM channel mode select - RW */
    ureg32 reserved_2:1;        /* [2:2] Internal  reserved */
    ureg32 ARU_EN:1;            /* [3:3] ARU Input stream enable - RW */
    ureg32 ACB0:1;              /* [4:4] ACB bit 0 - RW */
    ureg32 reserved_5:6;        /* [10:5] Internal  reserved */
    ureg32 SL:1;                /* [11:11] Initial signal level after channel is enabled - RW */
    ureg32 reserved_12:11;        /* [22:12] Internal  reserved */
    ureg32 EXTTRIGOUT:1;        /* [23:23] Select TIM_EXT_CAPTURE(x) as potential output signal TRIG_[x] - RW */
    ureg32 TRIGOUT:1;           /* [24:24] TRIGOUT: Trigger output selection (output signal TRIG_CHx) of module ATOM_CHx - RW */
    ureg32 reserved_25:4;        /* [28:25] Internal  reserved */
    ureg32 EXT_FUPD:1;          /* [29:29] Enable force update by external trigger signal - RW */
    ureg32 SOMB:1;              /* [30:30] SOMB: SOMB mode (Set ATOM[i]_CH[x]_CTRL_SOMI.SOMB = 0 for SOMI mode) - RW */
    ureg32 FREEZE:1;            /* [31:31] FREEZE - RW */
} GTM_ATOM_CH_SOMI_Bits;

/* ATOM[i] Channel[i] Control Register in SOMP Mode */
typedef struct
{
    ureg32 MODE:2;              /* [1:0] ATOM channel mode select - RW */
    ureg32 reserved_2:1;        /* [2:2] Internal  reserved */
    ureg32 ARU_EN:1;            /* [3:3] ARU Input stream enable - RW */
    ureg32 ADL:2;               /* [5:4] ARU data select for SOMP - RW */
    ureg32 BITREV:1;            /* [6:6] Bit-reversing of output of counter register CN0. This bit enables the PCM mode - RW */
    ureg32 SR0_TRIG:1;          /* [7:7] SR0 is used to generate a trigger on output ATOM[i]_CH[x]_OUT_T if equal to CN0 - RW */
    ureg32 reserved_8:3;        /* [10:8] Internal  reserved */
    ureg32 SL:1;                /* [11:11] Signal level for pulse of PWM - RW */
    ureg32 CLK_SRC:4;            /* [15:12] CMU clock source - RW */
    ureg32 reserved_16:1;        /* [16:16] Internal  reserved */
    ureg32 TRIG_PULSE:1;        /* [17:17] Trigger output pulse length of one SYS_CLK period - RW */
    ureg32 UDMODE:2;            /* [19:18] Up/down counter mode - RW */
    ureg32 RST_CCU0:1;          /* [20:20] Reset source of CCU0 - RW */
    ureg32 OSM_TRIG:1;          /* [21:21] Enable trigger of one-shot pulse by trigger signal OSM_TRIG - RW */
    ureg32 EXT_TRIG:1;          /* [22:22] Select TIM_EXT_CAPTURE(x) as trigger signal - RW */
    ureg32 EXTTRIGOUT:1;        /* [23:23] Select TIM_EXT_CAPTURE(x) as potential output signal TRIG_[x] - RW */
    ureg32 TRIGOUT:1;           /* [24:24] Trigger output selection (output signal TRIG_CHx) of module ATOM_CHx - RW */
    ureg32 reserved_25:1;        /* [25:25] Internal  reserved */
    ureg32 OSM:1;               /* [26:26] One-shot mode - RW */
    ureg32 reserved_27:2;        /* [28:27] Internal  reserved */
    ureg32 EXT_FUPD:1;          /* [29:29] External forced update - RW */
    ureg32 SOMB:1;              /* [30:30] SOMB: Set ATOM[i]_CH[x]_CTRL_SOMP.SOMB = 0 for SOMP mode - RW */
    ureg32 FREEZE:1;            /* [31:31] FREEZE - RW */
} GTM_ATOM_CH_SOMP_Bits;

/* ATOM[i] Channel[i] Control Register in SOMS Mode */
typedef struct
{
    ureg32 MODE:2;              /* [1:0] ATOM channel mode select - RW */
    ureg32 reserved_2:1;        /* [2:2] Internal  reserved */
    ureg32 ARU_EN:1;            /* [3:3] ARU Input stream enable - RW */
    ureg32 ACB0:1;              /* [4:4] Shift direction for CM1 register - RW */
    ureg32 reserved_5:2;        /* [6:5] Internal  reserved */
    ureg32 DSO:1;               /* [7:7] Double Shift Output - RW */
    ureg32 reserved_8:3;        /* [10:8] Internal  reserved */
    ureg32 SL:1;                /* [11:11] Defines signal level when channel and output is disabling - RW */
    ureg32 CLK_SRC:4;            /* [15:12] CMU clock source - RW */
    ureg32 reserved_16:7;        /* [22:16] Internal  reserved */
    ureg32 EXTTRIGOUT:1;        /* [23:23] Select TIM_EXT_CAPTURE(x) as potential output signal TRIG_[x] - RW */
    ureg32 TRIGOUT:1;           /* [24:24] Trigger output selection (output signal TRIG_CHx) of module ATOM_CHx - RW */
    ureg32 reserved_25:1;        /* [25:25] Internal  reserved */
    ureg32 OSM:1;               /* [26:26] One-shot mode - RW */
    ureg32 reserved_27:2;        /* [28:27] Internal  reserved */
    ureg32 EXT_FUPD:1;          /* [29:29] External forced update - RW */
    ureg32 SOMB:1;              /* [30:30] SOMB: Set ATOM[i]_CH[x]_CTRL_SOMS.SOMB = 0 for SOMS mode - RW */
    ureg32 FREEZE:1;            /* [31:31] FREEZE - RW */
} GTM_ATOM_CH_SOMS_Bits;

/* ATOM[i] channel [x] CCU0 compare shadow register */
typedef struct
{
    ureg32 SR0:24;               /* [23:0] ATOM channel [x] shadow register SR0. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_ATOM_CH_SR0_Bits;

/* ATOM[i] channel [x] CCU1 compare shadow register */
typedef struct
{
    ureg32 SR1:24;               /* [23:0] ATOM channel [x] shadow register SR1. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_ATOM_CH_SR1_Bits;

/* ATOM[i] channel [x] CCU0 compare register */
typedef struct
{
    ureg32 CM0:24;               /* [23:0] ATOM CCU0 compare register. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_ATOM_CH_CM0_Bits;

/* ATOM[i] channel [x] CCU1 compare register */
typedef struct
{
    ureg32 CM1:24;               /* [23:0] ATOM CCU1 compare register. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_ATOM_CH_CM1_Bits;

/* ATOM[i] channel [x] CCU0 counter register */
typedef struct
{
    ureg32 CN0:24;               /* [23:0] ATOM CCU0 counter register. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_ATOM_CH_CN0_Bits;

/* ATOM[i] channel [x] status register */
typedef struct
{
    ureg32 OL:1;                 /* [0:0] Output signal level of ATOM_OUT[x:x]. - RO */
    ureg32 reserved_1:15;        /* [15:1] Internal  reserved */
    ureg32 ACBI:5;               /* [20:16] ATOM Mode control bits. - RO */
    ureg32 DV:1;                 /* [21:21] Valid ARU Data stored in compare registers. - RO */
    ureg32 WRF:1;                /* [22:22] Write request of CPU failed for late update. - RW */
    ureg32 DR:1;                 /* [23:23] ARU data rejected flag - RO */
    ureg32 ACBO:5;               /* [28:24] ATOM Internal status bits. - RO */
    ureg32 OSM_RTF:1;            /* [29:29] One-shot mode retrigger failed flag. - RW */
    ureg32 reserved_30:2;        /* [31:30] Internal  reserved */
} GTM_ATOM_CH_STAT_Bits;

/* ATOM[i] channel [x] interrupt notification register */
typedef struct
{
    ureg32 CCU0TC:1;             /* [0:0] CCU0 Trigger condition interrupt for channel [x]. - RW */
    ureg32 CCU1TC:1;             /* [1:1] CCU Trigger condition interrupt for channel [x]. - RW */
    ureg32 reserved_2:30;        /* [31:2] Internal  reserved */
} GTM_ATOM_CH_IRQ_NOTIFY_Bits;

/* ATOM[i] channel [x] interrupt enable register */
typedef struct
{
    ureg32 CCU0TC_IRQ_EN:1;        /* [0:0] ATOM_CCU0TC[x]_IRQ interrupt enable. - RW */
    ureg32 CCU1TC_IRQ_EN:1;        /* [1:1] ATOM_CCU1TC[x]_IRQ interrupt enable. - RW */
    ureg32 reserved_2:30;          /* [31:2] Internal  reserved */
} GTM_ATOM_CH_IRQ_EN_Bits;

/* ATOM[i] channel [x] software interrupt generation */
typedef struct
{
    ureg32 TRG_CCU0TC:1;         /* [0:0] Trigger the bit ATOM[i]_CH[x]_IRQ_NOTIFY.CCU0TC by software. - RW */
    ureg32 TRG_CCU1TC:1;         /* [1:1] Trigger the bit ATOM[i]_CH[x]_IRQ_NOTIFY.CCU1TC by software. - RW */
    ureg32 reserved_2:30;        /* [31:2] Internal  reserved */
} GTM_ATOM_CH_IRQ_FORCINT_Bits;

/* ATOM[i] channel [x] interrupt mode configuration register */
typedef struct
{
    ureg32 IRQ_MODE:2;           /* [1:0] IRQ mode selection - RW */
    ureg32 reserved_2:30;        /* [31:2] Internal  reserved */
} GTM_ATOM_CH_IRQ_MODE_Bits;

/* ATOM[i] channel [x] control2 register */
typedef struct
{
    ureg32 HRES:1;               /* [0:0] ATOM[i]_CH[x]_CTRL2.HRES: ATOM high resolution support  - RW */
    ureg32 reserved_1:31;        /* [31:1] Internal  reserved */
} GTM_ATOM_CH_CTRL2_Bits;

/* ATOM[i] channel [x] control shadow register */
typedef struct
{
    ureg32 reserved_0:11;         /* [10:0] Internal  reserved */
    ureg32 SL_SR:1;               /* [11:11] Shadow register for ATOM[i]_CH[x]_CTRL.SL - RW */
    ureg32 CLK_SRC_SR:4;          /* [15:12] Shadow register for ATOM[i]_CH[x]_CTRL.CLK_SRC - RW */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_ATOM_CH_CTRL_SR_Bits;

/* ATOM[i] AGC global control register */
typedef struct
{
    ureg32 HOST_TRIG:1;         /* [0:0] Trigger request signal (see AGC) to update the register ATOM[i]_AGC_ENDIS_STAT and ATOM[i]_AGC_OUTEN_STAT - RW */
    ureg32 reserved_1:7;        /* [7:1] Internal  reserved */
    ureg32 RST_CH0:1;           /* [8:8] Software reset of channel [k] - RW */
    ureg32 RST_CH1:1;           /* [9:9] Software reset of channel [k] - RW */
    ureg32 RST_CH2:1;           /* [10:10] Software reset of channel [k] - RW */
    ureg32 RST_CH3:1;           /* [11:11] Software reset of channel [k] - RW */
    ureg32 RST_CH4:1;           /* [12:12] Software reset of channel [k] - RW */
    ureg32 RST_CH5:1;           /* [13:13] Software reset of channel [k] - RW */
    ureg32 RST_CH6:1;           /* [14:14] Software reset of channel [k] - RW */
    ureg32 RST_CH7:1;           /* [15:15] Software reset of channel [k] - RW */
    ureg32 UPEN_CTRL0:2;        /* [17:16] ATOM channel [k] enable update of register ATOM[i]_CH[k]_CM0 - ATOM[i]_CH[k]_CM1 - ATOM[i]_CH[k]_CTRL.SL and ATOM[i]_CH[k]_CTRL.CLK_SRC from ATOM[i]_CH[k]_SR0 - ATOM[i]_CH[k]_SR1 - ATOM[i]_CH[k]_CTRL_SR.SL_SR and ATOM[i]_CH[k]_CTRL_SR.CLK_SRC_SR. - RW */
    ureg32 UPEN_CTRL1:2;        /* [19:18] ATOM channel [k] enable update of register ATOM[i]_CH[k]_CM0 - ATOM[i]_CH[k]_CM1 - ATOM[i]_CH[k]_CTRL.SL and ATOM[i]_CH[k]_CTRL.CLK_SRC from ATOM[i]_CH[k]_SR0 - ATOM[i]_CH[k]_SR1 - ATOM[i]_CH[k]_CTRL_SR.SL_SR and ATOM[i]_CH[k]_CTRL_SR.CLK_SRC_SR. - RW */
    ureg32 UPEN_CTRL2:2;        /* [21:20] ATOM channel [k] enable update of register ATOM[i]_CH[k]_CM0 - ATOM[i]_CH[k]_CM1 - ATOM[i]_CH[k]_CTRL.SL and ATOM[i]_CH[k]_CTRL.CLK_SRC from ATOM[i]_CH[k]_SR0 - ATOM[i]_CH[k]_SR1 - ATOM[i]_CH[k]_CTRL_SR.SL_SR and ATOM[i]_CH[k]_CTRL_SR.CLK_SRC_SR. - RW */
    ureg32 UPEN_CTRL3:2;        /* [23:22] ATOM channel [k] enable update of register ATOM[i]_CH[k]_CM0 - ATOM[i]_CH[k]_CM1 - ATOM[i]_CH[k]_CTRL.SL and ATOM[i]_CH[k]_CTRL.CLK_SRC from ATOM[i]_CH[k]_SR0 - ATOM[i]_CH[k]_SR1 - ATOM[i]_CH[k]_CTRL_SR.SL_SR and ATOM[i]_CH[k]_CTRL_SR.CLK_SRC_SR. - RW */
    ureg32 UPEN_CTRL4:2;        /* [25:24] ATOM channel [k] enable update of register ATOM[i]_CH[k]_CM0 - ATOM[i]_CH[k]_CM1 - ATOM[i]_CH[k]_CTRL.SL and ATOM[i]_CH[k]_CTRL.CLK_SRC from ATOM[i]_CH[k]_SR0 - ATOM[i]_CH[k]_SR1 - ATOM[i]_CH[k]_CTRL_SR.SL_SR and ATOM[i]_CH[k]_CTRL_SR.CLK_SRC_SR. - RW */
    ureg32 UPEN_CTRL5:2;        /* [27:26] ATOM channel [k] enable update of register ATOM[i]_CH[k]_CM0 - ATOM[i]_CH[k]_CM1 - ATOM[i]_CH[k]_CTRL.SL and ATOM[i]_CH[k]_CTRL.CLK_SRC from ATOM[i]_CH[k]_SR0 - ATOM[i]_CH[k]_SR1 - ATOM[i]_CH[k]_CTRL_SR.SL_SR and ATOM[i]_CH[k]_CTRL_SR.CLK_SRC_SR. - RW */
    ureg32 UPEN_CTRL6:2;        /* [29:28] ATOM channel [k] enable update of register ATOM[i]_CH[k]_CM0 - ATOM[i]_CH[k]_CM1 - ATOM[i]_CH[k]_CTRL.SL and ATOM[i]_CH[k]_CTRL.CLK_SRC from ATOM[i]_CH[k]_SR0 - ATOM[i]_CH[k]_SR1 - ATOM[i]_CH[k]_CTRL_SR.SL_SR and ATOM[i]_CH[k]_CTRL_SR.CLK_SRC_SR. - RW */
    ureg32 UPEN_CTRL7:2;        /* [31:30] ATOM channel [k] enable update of register ATOM[i]_CH[k]_CM0 - ATOM[i]_CH[k]_CM1 - ATOM[i]_CH[k]_CTRL.SL and ATOM[i]_CH[k]_CTRL.CLK_SRC from ATOM[i]_CH[k]_SR0 - ATOM[i]_CH[k]_SR1 - ATOM[i]_CH[k]_CTRL_SR.SL_SR and ATOM[i]_CH[k]_CTRL_SR.CLK_SRC_SR. - RW */
} GTM_ATOM_AGC_GLB_CTRL_Bits;

/* ATOM[i] AGC enable/disable control register */
typedef struct
{
    ureg32 ENDIS_CTRL0:2;         /* [1:0] ATOM [i] channel [x] enable/disable control register.  - RW */
    ureg32 ENDIS_CTRL1:2;         /* [3:2] ATOM [i] channel [x] enable/disable control register.  - RW */
    ureg32 ENDIS_CTRL2:2;         /* [5:4] ATOM [i] channel [x] enable/disable control register.  - RW */
    ureg32 ENDIS_CTRL3:2;         /* [7:6] ATOM [i] channel [x] enable/disable control register.  - RW */
    ureg32 ENDIS_CTRL4:2;         /* [9:8] ATOM [i] channel [x] enable/disable control register.  - RW */
    ureg32 ENDIS_CTRL5:2;         /* [11:10] ATOM [i] channel [x] enable/disable control register.  - RW */
    ureg32 ENDIS_CTRL6:2;         /* [13:12] ATOM [i] channel [x] enable/disable control register.  - RW */
    ureg32 ENDIS_CTRL7:2;         /* [15:14] ATOM [i] channel [x] enable/disable control register.  - RW */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_ATOM_AGC_ENDIS_CTRL_Bits;

/* ATOM[i] AGC enable/disable status register */
typedef struct
{
    ureg32 ENDIS_STAT0:2;         /* [1:0] ATOM [i] channel [k] enable/disable status register - RW */
    ureg32 ENDIS_STAT1:2;         /* [3:2] ATOM [i] channel [k] enable/disable status register - RW */
    ureg32 ENDIS_STAT2:2;         /* [5:4] ATOM [i] channel [k] enable/disable status register - RW */
    ureg32 ENDIS_STAT3:2;         /* [7:6] ATOM [i] channel [k] enable/disable status register - RW */
    ureg32 ENDIS_STAT4:2;         /* [9:8] ATOM [i] channel [k] enable/disable status register - RW */
    ureg32 ENDIS_STAT5:2;         /* [11:10] ATOM [i] channel [k] enable/disable status register - RW */
    ureg32 ENDIS_STAT6:2;         /* [13:12] ATOM [i] channel [k] enable/disable status register - RW */
    ureg32 ENDIS_STAT7:2;         /* [15:14] ATOM [i] channel [k] enable/disable status register - RW */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_ATOM_AGC_ENDIS_STAT_Bits;

/* ATOM[i] AGC action time base register */
typedef struct
{
    ureg32 ACT_TB:24;            /* [23:0] Specifies the signed compare value with selected signal CCM[i]_TBU_TS0/CCM[i]_TBU_TS1/CCM[i]_TBU_TS2. If selected CCM[i]_TBU_TS0/CCM[i]_TBU_TS1/CCM[i]_TBU_TS2 value is in the interval [ATOM[i]_AGC_ACT_TB.ACT_TB-007FFFFFh,ATOM[i]_AGC_ACT_TB.ACT_TB] the event is in the past and the trigger is generated immediately. Otherwise the event is in the future and the trigger is generated if selected CCM[i]_TBU_TS0/CCM[i]_TBU_TS1/CCM[i]_TBU_TS2 is equal to ATOM[i]_AGC_ACT_TB.ACT_TB. - RW */
    ureg32 TB_TRIG:1;            /* [24:24] Set trigger request - RW */
    ureg32 TBU_SEL:2;            /* [26:25] Selection of time base used for comparison - RW */
    ureg32 reserved_27:5;        /* [31:27] Internal  reserved */
} GTM_ATOM_AGC_ACT_TB_Bits;

/* ATOM[i] AGC output enable control register */
typedef struct
{
    ureg32 OUTEN_CTRL0:2;         /* [1:0] Output enable control of ATOM [i] channel [k] ouput ATOM_OUT[x:x] - RW */
    ureg32 OUTEN_CTRL1:2;         /* [3:2] Output enable control of ATOM [i] channel [k] ouput ATOM_OUT[x:x] - RW */
    ureg32 OUTEN_CTRL2:2;         /* [5:4] Output enable control of ATOM [i] channel [k] ouput ATOM_OUT[x:x] - RW */
    ureg32 OUTEN_CTRL3:2;         /* [7:6] Output enable control of ATOM [i] channel [k] ouput ATOM_OUT[x:x] - RW */
    ureg32 OUTEN_CTRL4:2;         /* [9:8] Output enable control of ATOM [i] channel [k] ouput ATOM_OUT[x:x] - RW */
    ureg32 OUTEN_CTRL5:2;         /* [11:10] Output enable control of ATOM [i] channel [k] ouput ATOM_OUT[x:x] - RW */
    ureg32 OUTEN_CTRL6:2;         /* [13:12] Output enable control of ATOM [i] channel [k] ouput ATOM_OUT[x:x] - RW */
    ureg32 OUTEN_CTRL7:2;         /* [15:14] Output enable control of ATOM [i] channel [k] ouput ATOM_OUT[x:x] - RW */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_ATOM_AGC_OUTEN_CTRL_Bits;

/* ATOM[i] AGC output enable status register */
typedef struct
{
    ureg32 OUTEN_STAT0:2;         /* [1:0] Output enable status of ATOM [i] channel [x] ouput ATOM_OUT[k:k] - RW */
    ureg32 OUTEN_STAT1:2;         /* [3:2] Output enable status of ATOM [i] channel [x] ouput ATOM_OUT[k:k] - RW */
    ureg32 OUTEN_STAT2:2;         /* [5:4] Output enable status of ATOM [i] channel [x] ouput ATOM_OUT[k:k] - RW */
    ureg32 OUTEN_STAT3:2;         /* [7:6] Output enable status of ATOM [i] channel [x] ouput ATOM_OUT[k:k] - RW */
    ureg32 OUTEN_STAT4:2;         /* [9:8] Output enable status of ATOM [i] channel [x] ouput ATOM_OUT[k:k] - RW */
    ureg32 OUTEN_STAT5:2;         /* [11:10] Output enable status of ATOM [i] channel [x] ouput ATOM_OUT[k:k] - RW */
    ureg32 OUTEN_STAT6:2;         /* [13:12] Output enable status of ATOM [i] channel [x] ouput ATOM_OUT[k:k] - RW */
    ureg32 OUTEN_STAT7:2;         /* [15:14] Output enable status of ATOM [i] channel [x] ouput ATOM_OUT[k:k] - RW */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_ATOM_AGC_OUTEN_STAT_Bits;

/* ATOM[i] AGC force update control register */
typedef struct
{
    ureg32 FUPD_CTRL0:2;        /* [1:0] Force update of ATOM channel [k] operation registers - RW */
    ureg32 FUPD_CTRL1:2;        /* [3:2] Force update of ATOM channel [k] operation registers - RW */
    ureg32 FUPD_CTRL2:2;        /* [5:4] Force update of ATOM channel [k] operation registers - RW */
    ureg32 FUPD_CTRL3:2;        /* [7:6] Force update of ATOM channel [k] operation registers - RW */
    ureg32 FUPD_CTRL4:2;        /* [9:8] Force update of ATOM channel [k] operation registers - RW */
    ureg32 FUPD_CTRL5:2;        /* [11:10] Force update of ATOM channel [k] operation registers - RW */
    ureg32 FUPD_CTRL6:2;        /* [13:12] Force update of ATOM channel [k] operation registers - RW */
    ureg32 FUPD_CTRL7:2;        /* [15:14] Force update of ATOM channel [k] operation registers - RW */
    ureg32 RSTCN0_CH0:2;        /* [17:16] Reset ATOM[i]_CH[k]_CN0 of channel [k] on force update event - RW */
    ureg32 RSTCN0_CH1:2;        /* [19:18] Reset ATOM[i]_CH[k]_CN0 of channel [k] on force update event - RW */
    ureg32 RSTCN0_CH2:2;        /* [21:20] Reset ATOM[i]_CH[k]_CN0 of channel [k] on force update event - RW */
    ureg32 RSTCN0_CH3:2;        /* [23:22] Reset ATOM[i]_CH[k]_CN0 of channel [k] on force update event - RW */
    ureg32 RSTCN0_CH4:2;        /* [25:24] Reset ATOM[i]_CH[k]_CN0 of channel [k] on force update event - RW */
    ureg32 RSTCN0_CH5:2;        /* [27:26] Reset ATOM[i]_CH[k]_CN0 of channel [k] on force update event - RW */
    ureg32 RSTCN0_CH6:2;        /* [29:28] Reset ATOM[i]_CH[k]_CN0 of channel [k] on force update event - RW */
    ureg32 RSTCN0_CH7:2;        /* [31:30] Reset ATOM[i]_CH[k]_CN0 of channel [k] on force update event - RW */
} GTM_ATOM_AGC_FUPD_CTRL_Bits;

/* ATOM[i] AGC internal trigger control register */
typedef struct
{
    ureg32 INT_TRIG0:2;           /* [1:0] Select input signal ATOM_CH_TRIGOUT[k:k] as a trigger source - RW */
    ureg32 INT_TRIG1:2;           /* [3:2] Select input signal ATOM_CH_TRIGOUT[k:k] as a trigger source - RW */
    ureg32 INT_TRIG2:2;           /* [5:4] Select input signal ATOM_CH_TRIGOUT[k:k] as a trigger source - RW */
    ureg32 INT_TRIG3:2;           /* [7:6] Select input signal ATOM_CH_TRIGOUT[k:k] as a trigger source - RW */
    ureg32 INT_TRIG4:2;           /* [9:8] Select input signal ATOM_CH_TRIGOUT[k:k] as a trigger source - RW */
    ureg32 INT_TRIG5:2;           /* [11:10] Select input signal ATOM_CH_TRIGOUT[k:k] as a trigger source - RW */
    ureg32 INT_TRIG6:2;           /* [13:12] Select input signal ATOM_CH_TRIGOUT[k:k] as a trigger source - RW */
    ureg32 INT_TRIG7:2;           /* [15:14] Select input signal ATOM_CH_TRIGOUT[k:k] as a trigger source - RW */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_ATOM_AGC_INT_TRIG_Bits;

/* MCS[i] channel x general purpose register [y] */
typedef struct
{
    ureg32 DATA:24;              /* [23:0] Data of general purpose register R[y] - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_MCS_CH_R_Bits;

/* MCS[i] channel x control register */
typedef struct
{
    ureg32 EN:1;                  /* [0:0] Enable/Disable Request of MCS-channel x - RW */
    ureg32 IRQ:1;                 /* [1:1] Interrupt state - RO */
    ureg32 ERR:1;                 /* [2:2] Error state - RO */
    ureg32 reserved_3:1;          /* [3:3] Internal  reserved */
    ureg32 CY:1;                  /* [4:4] Carry bit state - RO */
    ureg32 Z:1;                   /* [5:5] Zero bit state - RO */
    ureg32 V:1;                   /* [6:6] Overflow bit state - RO */
    ureg32 N:1;                   /* [7:7] Negative bit state - RO */
    ureg32 CAT:1;                 /* [8:8] Cancel ARU transfer state - RO */
    ureg32 CWT:1;                 /* [9:9] Cancel WURM instruction state - RO */
    ureg32 SAT:1;                 /* [10:10] Successful ARU transfer bit - RO */
    ureg32 reserved_11:21;        /* [31:11] Internal  reserved */
} GTM_MCS_CH_CTRL_Bits;

/* MCS[i] channel x ARU control Bit register  */
typedef struct
{
    ureg32 ACB0:1;               /* [0:0] ARU Control bit [k] - RO */
    ureg32 ACB1:1;               /* [1:1] ARU Control bit [k] - RO */
    ureg32 ACB2:1;               /* [2:2] ARU Control bit [k] - RO */
    ureg32 ACB3:1;               /* [3:3] ARU Control bit [k] - RO */
    ureg32 ACB4:1;               /* [4:4] ARU Control bit [k] - RO */
    ureg32 reserved_5:27;        /* [31:5] Internal  reserved */
} GTM_MCS_CH_ACB_Bits;

/* MCS[i] channel x memory high byte register  */
typedef struct
{
    ureg32 DATA:8;               /* [7:0] Data of memory high bit register MHB - RO */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_MCS_CH_MHB_Bits;

/* MCS[i] channel x program counter register  */
typedef struct
{
    ureg32 PC:16;                 /* [15:0] Current Program Counter - RW */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_MCS_CH_PC_Bits;

/* MCS[i] channel x interrupt notification register */
typedef struct
{
    ureg32 MCS_IRQ:1;            /* [0:0] Interrupt request by MCS-channel x - RW */
    ureg32 reserved_1:1;         /* [1:1] Internal  reserved */
    ureg32 ERR_IRQ:1;            /* [2:2] MCS channel x ERR interrupt. - RW */
    ureg32 reserved_3:29;        /* [31:3] Internal  reserved */
} GTM_MCS_CH_IRQ_NOTIFY_Bits;

/* MCS[i] channel x interrupt enable register  */
typedef struct
{
    ureg32 MCS_IRQ_EN:1;         /* [0:0] MCS channel x MCS[i]_CH[x]_IRQ_NOTIFY.MCS_IRQ interrupt enable - RW */
    ureg32 reserved_1:1;         /* [1:1] Internal  reserved */
    ureg32 ERR_IRQ_EN:1;         /* [2:2] MCS channel x MCS[i]_CH[x]_IRQ_NOTIFY.ERR_IRQ interrupt enable - RW */
    ureg32 reserved_3:29;        /* [31:3] Internal  reserved */
} GTM_MCS_CH_IRQ_EN_Bits;

/* MCS[i] channel x force interrupt register */
typedef struct
{
    ureg32 TRG_MCS_IRQ:1;        /* [0:0] Trigger the bit MCS[i]_CH[x]_IRQ_NOTIFY.MCS_IRQ by software - RW */
    ureg32 reserved_1:1;         /* [1:1] Internal  reserved */
    ureg32 TRG_ERR_IRQ:1;        /* [2:2] Trigger the bit MCS[i]_CH[x]_IRQ_NOTIFY.ERR_IRQ by software - RW */
    ureg32 reserved_3:29;        /* [31:3] Internal  reserved */
} GTM_MCS_CH_IRQ_FORCINT_Bits;

/* MCS[i] channel x IRQ mode configuration register  */
typedef struct
{
    ureg32 IRQ_MODE:2;           /* [1:0] IRQ mode selection - RW */
    ureg32 reserved_2:30;        /* [31:2] Internal  reserved */
} GTM_MCS_CH_IRQ_MODE_Bits;

/* MCS[i] channel x error interrupt enable register */
typedef struct
{
    ureg32 MCS_EIRQ_EN:1;        /* [0:0] MCS[i]_CH[x]_EIRQ_EN.MCS_EIRQ_EN: MCS channel x MCS_EIRQ error interrupt enable - RW */
    ureg32 reserved_1:1;         /* [1:1] Internal  reserved */
    ureg32 ERR_EIRQ_EN:1;        /* [2:2] MCS channel x ERR_EIRQ error interrupt enable - RW */
    ureg32 reserved_3:29;        /* [31:3] Internal  reserved */
} GTM_MCS_CH_EIRQ_EN_Bits;

/* MCS[i] clear trigger control register */
typedef struct
{
    ureg32 TRG0:1;               /* [0:0] Trigger bit [m]. - RW */
    ureg32 TRG1:1;               /* [1:1] Trigger bit [m]. - RW */
    ureg32 TRG2:1;               /* [2:2] Trigger bit [m]. - RW */
    ureg32 TRG3:1;               /* [3:3] Trigger bit [m]. - RW */
    ureg32 TRG4:1;               /* [4:4] Trigger bit [m]. - RW */
    ureg32 TRG5:1;               /* [5:5] Trigger bit [m]. - RW */
    ureg32 TRG6:1;               /* [6:6] Trigger bit [m]. - RW */
    ureg32 TRG7:1;               /* [7:7] Trigger bit [m]. - RW */
    ureg32 TRG8:1;               /* [8:8] Trigger bit [n]. - RW */
    ureg32 TRG9:1;               /* [9:9] Trigger bit [n]. - RW */
    ureg32 TRG10:1;              /* [10:10] Trigger bit [n]. - RW */
    ureg32 TRG11:1;              /* [11:11] Trigger bit [n]. - RW */
    ureg32 TRG12:1;              /* [12:12] Trigger bit [n]. - RW */
    ureg32 TRG13:1;              /* [13:13] Trigger bit [n]. - RW */
    ureg32 TRG14:1;              /* [14:14] Trigger bit [n]. - RW */
    ureg32 TRG15:1;              /* [15:15] Trigger bit [n]. - RW */
    ureg32 TRG16:1;              /* [16:16] Trigger bit [o] - RW */
    ureg32 TRG17:1;              /* [17:17] Trigger bit [o] - RW */
    ureg32 TRG18:1;              /* [18:18] Trigger bit [o] - RW */
    ureg32 TRG19:1;              /* [19:19] Trigger bit [o] - RW */
    ureg32 TRG20:1;              /* [20:20] Trigger bit [o] - RW */
    ureg32 TRG21:1;              /* [21:21] Trigger bit [o] - RW */
    ureg32 TRG22:1;              /* [22:22] Trigger bit [o] - RW */
    ureg32 TRG23:1;              /* [23:23] Trigger bit [o] - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_MCS_CTRG_Bits;

/* MCS[i] set trigger control register */
typedef struct
{
    ureg32 TRG0:1;               /* [0:0] Trigger bit [k]. - RW */
    ureg32 TRG1:1;               /* [1:1] Trigger bit [k]. - RW */
    ureg32 TRG2:1;               /* [2:2] Trigger bit [k]. - RW */
    ureg32 TRG3:1;               /* [3:3] Trigger bit [k]. - RW */
    ureg32 TRG4:1;               /* [4:4] Trigger bit [k]. - RW */
    ureg32 TRG5:1;               /* [5:5] Trigger bit [k]. - RW */
    ureg32 TRG6:1;               /* [6:6] Trigger bit [k]. - RW */
    ureg32 TRG7:1;               /* [7:7] Trigger bit [k]. - RW */
    ureg32 TRG8:1;               /* [8:8] Trigger bit [k]. - RW */
    ureg32 TRG9:1;               /* [9:9] Trigger bit [k]. - RW */
    ureg32 TRG10:1;              /* [10:10] Trigger bit [k]. - RW */
    ureg32 TRG11:1;              /* [11:11] Trigger bit [k]. - RW */
    ureg32 TRG12:1;              /* [12:12] Trigger bit [k]. - RW */
    ureg32 TRG13:1;              /* [13:13] Trigger bit [k]. - RW */
    ureg32 TRG14:1;              /* [14:14] Trigger bit [k]. - RW */
    ureg32 TRG15:1;              /* [15:15] Trigger bit [k]. - RW */
    ureg32 TRG16:1;              /* [16:16] Trigger bit [k]. - RW */
    ureg32 TRG17:1;              /* [17:17] Trigger bit [k]. - RW */
    ureg32 TRG18:1;              /* [18:18] Trigger bit [k]. - RW */
    ureg32 TRG19:1;              /* [19:19] Trigger bit [k]. - RW */
    ureg32 TRG20:1;              /* [20:20] Trigger bit [k]. - RW */
    ureg32 TRG21:1;              /* [21:21] Trigger bit [k]. - RW */
    ureg32 TRG22:1;              /* [22:22] Trigger bit [k]. - RW */
    ureg32 TRG23:1;              /* [23:23] Trigger bit [k]. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_MCS_STRG_Bits;

/* MCS[i] control and status register */
typedef struct
{
    ureg32 SCD_MODE:2;            /* [1:0] Select MCS scheduling mode - RW */
    ureg32 reserved_2:6;          /* [7:2] Internal  reserved */
    ureg32 SCD_CH:4;              /* [11:8] Channel selection for scheduling algorithm - RW */
    ureg32 reserved_12:4;         /* [15:12] Internal  reserved */
    ureg32 RAM_RST:1;             /* [16:16] RAM reset bit - RW */
    ureg32 reserved_17:3;         /* [19:17] Internal  reserved */
    ureg32 ERR_SRC_ID:3;          /* [22:20] Error source identifier - RO */
    ureg32 reserved_23:1;         /* [23:23] Internal  reserved */
    ureg32 EN_TIM_FOUT:1;         /* [24:24] Enable routing of TIM[i]_CH[x]_F_OUT signal. - RW */
    ureg32 EN_HVD:1;              /* [25:25] Enable Modified Harvard architecture. - RW */
    ureg32 HLT_AEIM_ERR:1;        /* [26:26] Halt on AEI bus master error. - RW */
    ureg32 reserved_27:5;         /* [31:27] Internal  reserved */
} GTM_MCS_CTRL_STAT_Bits;

/* MCS[i] reset register */
typedef struct
{
    ureg32 RST0:1;               /* [0:0] Software reset of channel x - RW */
    ureg32 RST1:1;               /* [1:1] Software reset of channel x - RW */
    ureg32 RST2:1;               /* [2:2] Software reset of channel x - RW */
    ureg32 RST3:1;               /* [3:3] Software reset of channel x - RW */
    ureg32 RST4:1;               /* [4:4] Software reset of channel x - RW */
    ureg32 RST5:1;               /* [5:5] Software reset of channel x - RW */
    ureg32 RST6:1;               /* [6:6] Software reset of channel x - RW */
    ureg32 RST7:1;               /* [7:7] Software reset of channel x - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_MCS_RESET_Bits;

/* MCS[i] cancel ARU transfer instruction */
typedef struct
{
    ureg32 CAT0:1;               /* [0:0] Cancel ARU transfer of channel x - RW */
    ureg32 CAT1:1;               /* [1:1] Cancel ARU transfer of channel x - RW */
    ureg32 CAT2:1;               /* [2:2] Cancel ARU transfer of channel x - RW */
    ureg32 CAT3:1;               /* [3:3] Cancel ARU transfer of channel x - RW */
    ureg32 CAT4:1;               /* [4:4] Cancel ARU transfer of channel x - RW */
    ureg32 CAT5:1;               /* [5:5] Cancel ARU transfer of channel x - RW */
    ureg32 CAT6:1;               /* [6:6] Cancel ARU transfer of channel x - RW */
    ureg32 CAT7:1;               /* [7:7] Cancel ARU transfer of channel x - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_MCS_CAT_Bits;

/* MCS[i] cancel waiting instruction */
typedef struct
{
    ureg32 CWT0:1;               /* [0:0] Cancel waiting instruction for channel x - RW */
    ureg32 CWT1:1;               /* [1:1] Cancel waiting instruction for channel x - RW */
    ureg32 CWT2:1;               /* [2:2] Cancel waiting instruction for channel x - RW */
    ureg32 CWT3:1;               /* [3:3] Cancel waiting instruction for channel x - RW */
    ureg32 CWT4:1;               /* [4:4] Cancel waiting instruction for channel x - RW */
    ureg32 CWT5:1;               /* [5:5] Cancel waiting instruction for channel x - RW */
    ureg32 CWT6:1;               /* [6:6] Cancel waiting instruction for channel x - RW */
    ureg32 CWT7:1;               /* [7:7] Cancel waiting instruction for channel x - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_MCS_CWT_Bits;

/* MCS[i] error register */
typedef struct
{
    ureg32 ERR0:1;               /* [0:0] Error State of MCS-channel x  - RW */
    ureg32 ERR1:1;               /* [1:1] Error State of MCS-channel x  - RW */
    ureg32 ERR2:1;               /* [2:2] Error State of MCS-channel x  - RW */
    ureg32 ERR3:1;               /* [3:3] Error State of MCS-channel x  - RW */
    ureg32 ERR4:1;               /* [4:4] Error State of MCS-channel x  - RW */
    ureg32 ERR5:1;               /* [5:5] Error State of MCS-channel x  - RW */
    ureg32 ERR6:1;               /* [6:6] Error State of MCS-channel x  - RW */
    ureg32 ERR7:1;               /* [7:7] Error State of MCS-channel x  - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_MCS_ERR_Bits;

/* MCS[i] write protection register */
typedef struct
{
    ureg32 WPROT0:2;              /* [1:0] Register Write Protection of MCS-channel [x]  - RW */
    ureg32 WPROT1:2;              /* [3:2] Register Write Protection of MCS-channel [x]  - RW */
    ureg32 WPROT2:2;              /* [5:4] Register Write Protection of MCS-channel [x]  - RW */
    ureg32 WPROT3:2;              /* [7:6] Register Write Protection of MCS-channel [x]  - RW */
    ureg32 WPROT4:2;              /* [9:8] Register Write Protection of MCS-channel [x]  - RW */
    ureg32 WPROT5:2;              /* [11:10] Register Write Protection of MCS-channel [x]  - RW */
    ureg32 WPROT6:2;              /* [13:12] Register Write Protection of MCS-channel [x]  - RW */
    ureg32 WPROT7:2;              /* [15:14] Register Write Protection of MCS-channel [x]  - RW */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_MCS_REG_PROT_Bits;

/* MCS[i] shared interrupt notification register */
typedef struct
{
    ureg32 S_IRQ0:1;             /* [0:0] Shared interrupt [k] notify flag. - RW */
    ureg32 S_IRQ1:1;             /* [1:1] Shared interrupt [k] notify flag. - RW */
    ureg32 S_IRQ2:1;             /* [2:2] Shared interrupt [k] notify flag. - RW */
    ureg32 S_IRQ3:1;             /* [3:3] Shared interrupt [k] notify flag. - RW */
    ureg32 S_IRQ4:1;             /* [4:4] Shared interrupt [k] notify flag. - RW */
    ureg32 S_IRQ5:1;             /* [5:5] Shared interrupt [k] notify flag. - RW */
    ureg32 S_IRQ6:1;             /* [6:6] Shared interrupt [k] notify flag. - RW */
    ureg32 S_IRQ7:1;             /* [7:7] Shared interrupt [k] notify flag. - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_MCS_SINT_IRQ_NOTIFY_Bits;

/* MCS[i] shared interrupt enable register  */
typedef struct
{
    ureg32 S_IRQ0_EN:1;          /* [0:0] Shared interrupt [k] - RW */
    ureg32 S_IRQ1_EN:1;          /* [1:1] Shared interrupt [k] - RW */
    ureg32 S_IRQ2_EN:1;          /* [2:2] Shared interrupt [k] - RW */
    ureg32 S_IRQ3_EN:1;          /* [3:3] Shared interrupt [k] - RW */
    ureg32 S_IRQ4_EN:1;          /* [4:4] Shared interrupt [k] - RW */
    ureg32 S_IRQ5_EN:1;          /* [5:5] Shared interrupt [k] - RW */
    ureg32 S_IRQ6_EN:1;          /* [6:6] Shared interrupt [k] - RW */
    ureg32 S_IRQ7_EN:1;          /* [7:7] Shared interrupt [k] - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_MCS_SINT_IRQ_EN_Bits;

/* MCS[i] force shared interrupt register */
typedef struct
{
    ureg32 TRG_S_IRQ0:1;         /* [0:0] Trigger the bit MCS[i]_SINT_IRQ_NOTIFY.S_IRQ[k] by software - RW */
    ureg32 TRG_S_IRQ1:1;         /* [1:1] Trigger the bit MCS[i]_SINT_IRQ_NOTIFY.S_IRQ[k] by software - RW */
    ureg32 TRG_S_IRQ2:1;         /* [2:2] Trigger the bit MCS[i]_SINT_IRQ_NOTIFY.S_IRQ[k] by software - RW */
    ureg32 TRG_S_IRQ3:1;         /* [3:3] Trigger the bit MCS[i]_SINT_IRQ_NOTIFY.S_IRQ[k] by software - RW */
    ureg32 TRG_S_IRQ4:1;         /* [4:4] Trigger the bit MCS[i]_SINT_IRQ_NOTIFY.S_IRQ[k] by software - RW */
    ureg32 TRG_S_IRQ5:1;         /* [5:5] Trigger the bit MCS[i]_SINT_IRQ_NOTIFY.S_IRQ[k] by software - RW */
    ureg32 TRG_S_IRQ6:1;         /* [6:6] Trigger the bit MCS[i]_SINT_IRQ_NOTIFY.S_IRQ[k] by software - RW */
    ureg32 TRG_S_IRQ7:1;         /* [7:7] Trigger the bit MCS[i]_SINT_IRQ_NOTIFY.S_IRQ[k] by software - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_MCS_SINT_IRQ_FORCINT_Bits;

/* MCS[i] shared interrupt mode configuration register  */
typedef struct
{
    ureg32 IRQ_MODE:2;           /* [1:0] IRQ mode selection - RW */
    ureg32 reserved_2:30;        /* [31:2] Internal  reserved */
} GTM_MCS_SINT_IRQ_MODE_Bits;

/* MCS[i] hardware break point h control register */
typedef struct
{
    ureg32 EN_CH0:1;              /* [0:0] Enable h-th hardware break point for channel x. - RW */
    ureg32 EN_CH1:1;              /* [1:1] Enable h-th hardware break point for channel x. - RW */
    ureg32 EN_CH2:1;              /* [2:2] Enable h-th hardware break point for channel x. - RW */
    ureg32 EN_CH3:1;              /* [3:3] Enable h-th hardware break point for channel x. - RW */
    ureg32 EN_CH4:1;              /* [4:4] Enable h-th hardware break point for channel x. - RW */
    ureg32 EN_CH5:1;              /* [5:5] Enable h-th hardware break point for channel x. - RW */
    ureg32 EN_CH6:1;              /* [6:6] Enable h-th hardware break point for channel x. - RW */
    ureg32 EN_CH7:1;              /* [7:7] Enable h-th hardware break point for channel x. - RW */
    ureg32 SCOPE:2;               /* [9:8] Define scope of h-th hardware break point. - RW */
    ureg32 reserved_10:2;         /* [11:10] Internal  reserved */
    ureg32 TYPE:3;                /* [14:12] Define type of h-th hardware break point. - RW */
    ureg32 reserved_15:1;         /* [15:15] Internal  reserved */
    ureg32 AND:1;                 /* [16:16] Logical AND conjunction of h-th hardware break point - RW */
    ureg32 NOT:1;                 /* [17:17] Logical negation of h-th hardware break point - RW */
    ureg32 reserved_18:14;        /* [31:18] Internal  reserved */
} GTM_MCS_HBP_CTRL_Bits;

/* MCS[i] hardware break point pattern register */
typedef struct
{
    ureg32 DATA:32;        /* [31:0] Define pattern or address of h-th hardware break point. - RW */
} GTM_MCS_HBP_PATTERN_Bits;

/* MCS[i] hardware break point status register */
typedef struct
{
    ureg32 HALT_CH0:1;           /* [0:0] Indicate that MCS channel x has fired the h-th hardware break point and either MCS channel x or the entire GTM was halted due to that break point - depending on the state of bit field MCS[i]_HBP[h]_CTRL.SCOPE. - RW */
    ureg32 HALT_CH1:1;           /* [1:1] Indicate that MCS channel x has fired the h-th hardware break point and either MCS channel x or the entire GTM was halted due to that break point - depending on the state of bit field MCS[i]_HBP[h]_CTRL.SCOPE. - RW */
    ureg32 HALT_CH2:1;           /* [2:2] Indicate that MCS channel x has fired the h-th hardware break point and either MCS channel x or the entire GTM was halted due to that break point - depending on the state of bit field MCS[i]_HBP[h]_CTRL.SCOPE. - RW */
    ureg32 HALT_CH3:1;           /* [3:3] Indicate that MCS channel x has fired the h-th hardware break point and either MCS channel x or the entire GTM was halted due to that break point - depending on the state of bit field MCS[i]_HBP[h]_CTRL.SCOPE. - RW */
    ureg32 HALT_CH4:1;           /* [4:4] Indicate that MCS channel x has fired the h-th hardware break point and either MCS channel x or the entire GTM was halted due to that break point - depending on the state of bit field MCS[i]_HBP[h]_CTRL.SCOPE. - RW */
    ureg32 HALT_CH5:1;           /* [5:5] Indicate that MCS channel x has fired the h-th hardware break point and either MCS channel x or the entire GTM was halted due to that break point - depending on the state of bit field MCS[i]_HBP[h]_CTRL.SCOPE. - RW */
    ureg32 HALT_CH6:1;           /* [6:6] Indicate that MCS channel x has fired the h-th hardware break point and either MCS channel x or the entire GTM was halted due to that break point - depending on the state of bit field MCS[i]_HBP[h]_CTRL.SCOPE. - RW */
    ureg32 HALT_CH7:1;           /* [7:7] Indicate that MCS channel x has fired the h-th hardware break point and either MCS channel x or the entire GTM was halted due to that break point - depending on the state of bit field MCS[i]_HBP[h]_CTRL.SCOPE. - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_MCS_HBP_STATUS_Bits;

/* MCS[i] hardware break point interrupt notification register */
typedef struct
{
    ureg32 HBP_IRQ:1;            /* [0:0] Interrupt notify flag of the h-th hardware break point - RW */
    ureg32 reserved_1:31;        /* [31:1] Internal  reserved */
} GTM_MCS_HBP_IRQ_NOTIFY_Bits;

/* MCS[i] hardware break point interrupt enable register  */
typedef struct
{
    ureg32 HBP_IRQ_EN:1;         /* [0:0] Interrupt Enable bit of the h-th hardware break point  - RW */
    ureg32 reserved_1:31;        /* [31:1] Internal  reserved */
} GTM_MCS_HBP_IRQ_EN_Bits;

/* MCS[i] force hardware break point interrupt register */
typedef struct
{
    ureg32 TRG_HBP_IRQ:1;        /* [0:0] Trigger the bit MCS[i]_HBP[h]_IRQ_NOTIFY.HBP_IRQ by software - RW */
    ureg32 reserved_1:31;        /* [31:1] Internal  reserved */
} GTM_MCS_HBP_IRQ_FORCINT_Bits;

/* MCS[i] break point h interrupt mode configuration register  */
typedef struct
{
    ureg32 IRQ_MODE:2;           /* [1:0] IRQ mode selection for all break point interrupts - RW */
    ureg32 reserved_2:30;        /* [31:2] Internal  reserved */
} GTM_MCS_HBP_IRQ_MODE_Bits;

/* TIO[i] group [g] channel [c] control register */
typedef struct
{
    ureg32 TRIG_OUT_EN_S_RE:1;                   /* [0:0] TIO[i] channel [c] Trigger Output source: Rising edge S[c] enable - RW */
    ureg32 TRIG_OUT_EN_S_FE:1;                   /* [1:1] TIO[i] channel [c] Trigger Output source: Falling edge S[c] enable - RW */
    ureg32 TRIG_OUT_EN_O_RE:1;                   /* [2:2] TIO[i] channel [c] Trigger Output source: Rising edge O[c] enable - RW */
    ureg32 TRIG_OUT_EN_O_FE:1;                   /* [3:3] TIO[i] channel [c] Trigger Output source: Falling edge O[c] enable - RW */
    ureg32 TRIG_OUT_EN_PREV_TRIG:1;              /* [4:4] TIO[i] channel [c] Trigger Output source: TRIG_OUT[c]-1enable - RW */
    ureg32 TRIG_OUT_EN_PL_EVT:1;                 /* [5:5] TIO[i] channel [c] Trigger Output source: PL_EVT[c] enable - RW */
    ureg32 TRIG_OUT_EN_PREV_PL_TRIG:1;           /* [6:6] TIO[i] channel [c] Trigger Output source: PL_TRIG_OUT[c]-1enable - RW */
    ureg32 PL_CYCLIC_INIT_TRIG_EN:1;             /* [7:7] Enable usage of TRIG_OUT[c] as init trigger of cyclic buffer functionality in channel [c]. - RW */
    ureg32 UPDATE_SRC:4;                         /* [11:8] Select update source of channel [c]. - RW */
    ureg32 PL_S_MODE:2;                          /* [13:12] Select mode of operation for S resource channel [c]. - RW */
    ureg32 PL_FREEZE_S_EN:1;                     /* [14:14] Enable S buffer freeze in channel [c]. - RW */
    ureg32 PL_CYCLIC_BUFF:1;                     /* [15:15] Enable circular buffer functionality in channel [c]. - RW */
    ureg32 PL_O_MODE:3;                          /* [18:16] Select mode of operation for O resource channel [c]. - RW */
    ureg32 PL_FREEZE_O_EN:1;                     /* [19:19] Enable O buffer freeze in channel [c]. - RW */
    ureg32 PL_ODIS:1;                            /* [20:20] Disable change of TIO[i]_O.CH[x] bit x = [g] * 8 + [c] - RW */
    ureg32 PL_SEL_IN:1;                          /* [21:21] Select input source for O resource channel [c].  - RW */
    ureg32 PL_O_TRIG_OUT_EN:1;                   /* [22:22] Enable usage of TRIG_OUT[c] in instruction of O resource channel [c]. - RW */
    ureg32 PL_S_TRIG_OUT_EN:1;                   /* [23:23] Enable usage of TRIG_OUT[c] in instruction of S resource channel [c]. - RW */
    ureg32 PL_TRIG_OUT_EN_S_RE:1;                /* [24:24] TIO[i] channel [c] PL_TRIG_OUT source: Rising edge S[c] enable - RW */
    ureg32 PL_TRIG_OUT_EN_S_FE:1;                /* [25:25] TIO[i] channel [c] PL_TRIG_OUT source: Falling edge S[c] enable - RW */
    ureg32 PL_TRIG_OUT_EN_O_RE:1;                /* [26:26] TIO[i] channel [c] PL_TRIG_OUT source: Rising edge O[c] enable - RW */
    ureg32 PL_TRIG_OUT_EN_O_FE:1;                /* [27:27] TIO[i] channel [c] PL_TRIG_OUT source: Falling edge O[c] enable - RW */
    ureg32 PL_TRIG_OUT_EN_PREV_TRIG:1;           /* [28:28] TIO[i] channel [c] PL_TRIG_OUT source: TRIG_OUT[c]-1 enable - RW */
    ureg32 PL_TRIG_OUT_EN_PL_EVT:1;              /* [29:29] TIO[i] channel [c] PL_TRIG_OUT source: PL_EVT[c] enable - RW */
    ureg32 PL_TRIG_OUT_EN_PREV_PL_TRIG:1;        /* [30:30] TIO[i] channel [c] PL_TRIG_OUT source: PL_TRIG_OUT[c]-1 enable - RW */
    ureg32 PL_TRIG_OUT_UPD_EN:1;                 /* [31:31] Select TIO[i] basic update source of channel [c].  - RW */
} GTM_TIO_G_CH_CTRL_Bits;

/* TIO[i] channel [c] interrupt notification register */
typedef struct
{
    ureg32 S_RE_IRQ:1;           /* [0:0] Interrupt request Rising edge S[c] - RW */
    ureg32 S_FE_IRQ:1;           /* [1:1] Interrupt request Falling edge S[c] - RW */
    ureg32 O_RE_IRQ:1;           /* [2:2] Interrupt request Rising edge O[c] - RW */
    ureg32 O_FE_IRQ:1;           /* [3:3] Interrupt request Falling edge O[c] - RW */
    ureg32 UPDATE_IRQ:1;         /* [4:4] Interrupt request for update of channel [c] - RW */
    ureg32 PL_EVT_IRQ:1;         /* [5:5] Interrupt request PL_EVT of channel [c] - RW */
    ureg32 reserved_6:26;        /* [31:6] Internal  reserved */
} GTM_TIO_G_CH_IRQ_NOTIFY_Bits;

/* TIO[i] channel [c] interrupt enable register */
typedef struct
{
    ureg32 S_RE_IRQ_EN:1;          /* [0:0] Interrupt enable request Rising edge S[c] - RW */
    ureg32 S_FE_IRQ_EN:1;          /* [1:1] Interrupt enable request Falling edge S[c] - RW */
    ureg32 O_RE_IRQ_EN:1;          /* [2:2] Interrupt enable request Rising edge O[c] - RW */
    ureg32 O_FE_IRQ_EN:1;          /* [3:3] Interrupt enable request Falling edge O[c] - RW */
    ureg32 UPDATE_IRQ_EN:1;        /* [4:4] Interrupt enable request for update of channel [c] - RW */
    ureg32 PL_EVT_IRQ_EN:1;        /* [5:5] Interrupt enable request PL_EVT of channel [c] - RW */
    ureg32 reserved_6:26;          /* [31:6] Internal  reserved */
} GTM_TIO_G_CH_IRQ_EN_Bits;

/* TIO[i] channel [c] force interrupt register */
typedef struct
{
    ureg32 TRG_S_RE_IRQ:1;          /* [0:0] Trigger the bit TIO[i]_G[g]_CH[c]_IRQ_NOTIFY.S_RE_IRQ by software. - RW */
    ureg32 TRG_S_FE_IRQ:1;          /* [1:1] Trigger the bit TIO[i]_G[g]_CH[c]_IRQ_NOTIFY.S_FE_IRQ by software. - RW */
    ureg32 TRG_O_RE_IRQ:1;          /* [2:2] Trigger the bit TIO[i]_G[g]_CH[c]_IRQ_NOTIFY.O_RE_IRQ by software. - RW */
    ureg32 TRG_O_FE_IRQ:1;          /* [3:3] Trigger the bit TIO[i]_G[g]_CH[c]_IRQ_NOTIFY.O_FE_IRQ by software. - RW */
    ureg32 TRG_UPDATE_IRQ:1;        /* [4:4] Trigger the bit TIO[i]_G[g]_CH[c]_IRQ_NOTIFY.UPDATE_IRQ by software. - RW */
    ureg32 TRG_PL_EVT_IRQ:1;        /* [5:5] Trigger the bit TIO[i]_G[g]_CH[c]_IRQ_NOTIFY.PL_EVT_IRQ by software. - RW */
    ureg32 reserved_6:26;           /* [31:6] Internal  reserved */
} GTM_TIO_G_CH_IRQ_FORCINT_Bits;

/* TIO[i] channel [c] IRQ mode configuration register */
typedef struct
{
    ureg32 IRQ_MODE:2;           /* [1:0] IRQ mode selection - RW */
    ureg32 reserved_2:30;        /* [31:2] Internal  reserved */
} GTM_TIO_G_CH_IRQ_MODE_Bits;

/* TIO[i] group [g] channel [c] control register */
typedef struct
{
    ureg32 DUAL_CMP_EN:1;            /* [0:0] TIO[i] channel [c] Trigger Output source: Rising edge S[c] enable - RW */
    ureg32 DUAL_CMP_MST_EN:1;        /* [1:1] TIO[i] channel [c] Trigger Output source: Falling edge S[c] enable - RW */
    ureg32 reserved_2:30;            /* [31:2] Internal  reserved */
} GTM_TIO_G_CH_CTRL2_Bits;

/* TIO[i] channel [c] resource S instruction register (buffer operation)

TIO[i]_G[g]_CH[c]_CTRL.PL_S_MODE=0b0- */
typedef struct
{
    ureg32 OP:24;                  /* [23:0] Operand - RW */
    ureg32 CMD:6;                  /* [29:24] Command - RW */
    ureg32 DATA_PUSH_EN:1;         /* [30:30] Enable data capture - RW */
    ureg32 INSTR_PULL_EN:1;        /* [31:31] Enable instruction fetch - RW */
} GTM_TIO_G_CH_SINST_Bits;

/* TIO[i] channel [c] resource S command register (buffer operation)

TIO[i]_G[g]_CH[c]_CTRL.PL_S_MODE=0b0- */
typedef struct
{
    ureg32 reserved_0:24;          /* [23:0] Internal  reserved */
    ureg32 CMD:6;                  /* [29:24] Command - RW */
    ureg32 DATA_PUSH_EN:1;         /* [30:30] Enable data capture - RW */
    ureg32 INSTR_PULL_EN:1;        /* [31:31] Enable instruction fetch - RW */
} GTM_TIO_G_CH_SCMD_Bits;

/* TIO[i] channel [c] resource S command register (counter operation) TIO[i]_G[g]_CH[c]_CTRL.PL_S_MODE=0b1- */
typedef struct
{
    ureg32 reserved_0:24;          /* [23:0] Internal  reserved */
    ureg32 CNT_COND:3;             /* [26:24] Command - RW */
    ureg32 CNT_ITERATIONS:2;       /* [28:27] Amount of activations - RW */
    ureg32 CMD_ACTIVE:1;           /* [29:29] Counter active - RW */
    ureg32 DATA_PUSH_EN:1;         /* [30:30] Enable data capture - RW */
    ureg32 INSTR_PULL_EN:1;        /* [31:31] Enable instruction fetch - RW */
} GTM_TIO_G_CH_SCMD_COUNT_Bits;

/* TIO[i] channel [c] resource S operand register

TIO[i]_G[g]_CH[c]_CTRL.PL_S_MODE=0b0- or (TIO[i]_G[g]_OP_USAGE.MODE[c]=0b10- or TIO[i]_G[g]_OP_USAGE.MODE[c]=0b1-0 ) */
typedef struct
{
    ureg32 OP:24;                /* [23:0] Operand - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_TIO_G_CH_SOP_Bits;

/* TIO[i] channel [c] resource O instruction register (buffer operation)

TIO[i]_G[g]_CH[c]_CTRL.PL_O_MODE =0b00- */
typedef struct
{
    ureg32 OP:24;                  /* [23:0] Operand - RW */
    ureg32 CMD:6;                  /* [29:24] Command - RW */
    ureg32 DATA_PUSH_EN:1;         /* [30:30] Enable data capture - RW */
    ureg32 INSTR_PULL_EN:1;        /* [31:31] Enable instruction fetch - RW */
} GTM_TIO_G_CH_OINST_Bits;

/* TIO[i] channel [c] resource O command register (buffer operation)

TIO[i]_G[g]_CH[c]_CTRL.PL_O_MODE=0b00- */
typedef struct
{
    ureg32 reserved_0:24;          /* [23:0] Internal  reserved */
    ureg32 CMD:6;                  /* [29:24] Command - RW */
    ureg32 DATA_PUSH_EN:1;         /* [30:30] Enable data capture - RW */
    ureg32 INSTR_PULL_EN:1;        /* [31:31] Enable instruction fetch - RW */
} GTM_TIO_G_CH_OCMD_Bits;

/* TIO[i] channel [c] resource O command register (compare operation) */
typedef struct
{
    ureg32 reserved_0:24;          /* [23:0] Internal  reserved */
    ureg32 O_ACTION:2;             /* [25:24] Action on compare - RW */
    ureg32 SEL_TB:2;               /* [27:26] TB source selection - RW */
    ureg32 CMD_ACTIVE_CC:2;        /* [29:28] Compare function in use - RW */
    ureg32 DATA_PUSH_EN:1;         /* [30:30] Enable data capture - RW */
    ureg32 INSTR_PULL_EN:1;        /* [31:31] Enable instruction fetch - RW */
} GTM_TIO_G_CH_OCMD_COMP_Bits;

/* TIO[i] channel [c] resource O command register (capture operation) */
typedef struct
{
    ureg32 reserved_0:24;          /* [23:0] Internal  reserved */
    ureg32 O_OUT:1;                /* [24:24] value of O at capture - RW */
    ureg32 S_OUT:1;                /* [25:25] value of S at capture - RW */
    ureg32 SEL_TB:2;               /* [27:26] TB source selection - RW */
    ureg32 CMD_ACTIVE_CC:2;        /* [29:28] capture function in use - RW */
    ureg32 DATA_PUSH_EN:1;         /* [30:30] Enable data capture - RW */
    ureg32 INSTR_PULL_EN:1;        /* [31:31] Enable instruction fetch - RW */
} GTM_TIO_G_CH_OCMD_CAP_Bits;

/* TIO[i] channel [c] resource O operand register

!(TIO[i]_G[g]_CH[c]_CTRL.PL_O_MODE=0b1--) or (TIO[i]_G[g]_OP_USAGE.MODE[c]=0b11-) */
typedef struct
{
    ureg32 OP:24;                /* [23:0] Operand - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_TIO_G_CH_OOP_Bits;

/* TIO[i] channel [c] resource O capture register */
typedef struct
{
    ureg32 OP:24;                /* [23:0] Operand - RW */
    ureg32 O_OUT:1;              /* [24:24] value of O at capture - RW */
    ureg32 S_OUT:1;              /* [25:25] value of S at capture - RW */
    ureg32 SEL_TB:2;             /* [27:26] TB source selection - RW */
    ureg32 CMD_ACTIVE_CC:2;      /* [29:28] Compare function in use - RW */
    ureg32 DATA_PUSH_EN:1;       /* [30:30] Enable data capture - RW */
    ureg32 INSTR_PULL_EN:1;      /* [31:31] Enable instruction fetch - RW */
} GTM_TIO_G_CH_OCAPTURE_Bits;

/* TIO[i] channel [c] resource shift count register */
typedef struct
{
    ureg32 CNT:5;                /* [4:0] Shift counter value - RO */
    ureg32 reserved_5:27;        /* [31:5] Internal  reserved */
} GTM_TIO_G_CH_SHIFTCNT_Bits;

/* TIO[i] input selection register 1 */
typedef struct
{
    ureg32 LUT2_0:4;             /* [3:0] 2 bit Lookup table function for channel c=[q]*4+[k] - RW */
    ureg32 LUT2_1:4;             /* [7:4] 2 bit Lookup table function for channel c=[q]*4+[k] - RW */
    ureg32 LUT2_2:4;             /* [11:8] 2 bit Lookup table function for channel c=[q]*4+[k] - RW */
    ureg32 LUT2_3:4;             /* [15:12] 2 bit Lookup table function for channel c=[q]*4+[k] - RW */
    ureg32 OUT_SEL0:1;           /* [16:16] select signal for ISEL_OUT[c] where c =[q]*4+[k] - RW */
    ureg32 OUT_SEL1:1;           /* [17:17] select signal for ISEL_OUT[c] where c =[q]*4+[k] - RW */
    ureg32 OUT_SEL2:1;           /* [18:18] select signal for ISEL_OUT[c] where c =[q]*4+[k] - RW */
    ureg32 OUT_SEL3:1;           /* [19:19] select signal for ISEL_OUT[c] where c =[q]*4+[k] - RW */
    ureg32 reserved_20:4;        /* [23:20] Internal  reserved */
    ureg32 WRITE_EN0:1;          /* [24:24] enable writing of configuration bit fields LUT2_[k] - OUT_SEL[k] - RW */
    ureg32 WRITE_EN1:1;          /* [25:25] enable writing of configuration bit fields LUT2_[k] - OUT_SEL[k] - RW */
    ureg32 WRITE_EN2:1;          /* [26:26] enable writing of configuration bit fields LUT2_[k] - OUT_SEL[k] - RW */
    ureg32 WRITE_EN3:1;          /* [27:27] enable writing of configuration bit fields LUT2_[k] - OUT_SEL[k] - RW */
    ureg32 reserved_28:4;        /* [31:28] Internal  reserved */
} GTM_TIO_G_ISEL_CTRL1_Bits;

/* TIO[i] input selection register 2 */
typedef struct
{
    ureg32 LUT3:8;               /* [7:0] 3 bit Lookup table function for quad=[q]; channels [q]*4+2 .. [q]*4 - RW */
    ureg32 reserved_8:8;         /* [15:8] Internal  reserved */
    ureg32 QOUT_SEL:2;           /* [17:16] select source for ISEL_QOUT[q] signal in quad = [q]  - RW */
    ureg32 reserved_18:2;        /* [19:18] Internal  reserved */
    ureg32 LUT3IN_SEL0:1;        /* [20:20] select source for LUT3_IN[k] signal in quad = [q] - RW */
    ureg32 LUT3IN_SEL1:1;        /* [21:21] select source for LUT3_IN[k] signal in quad = [q] - RW */
    ureg32 LUT3IN_SEL2:1;        /* [22:22] select source for LUT3_IN[k] signal in quad = [q] - RW */
    ureg32 reserved_23:9;        /* [31:23] Internal  reserved */
} GTM_TIO_G_ISEL_CTRL2_Bits;

/* TIO[i] operand usage selection register */
typedef struct
{
    ureg32 MODE0:3;            /* [2:0] operand usage of S/ O resource - RW */
    ureg32 MODE1:3;            /* [5:3] operand usage of S/ O resource - RW */
    ureg32 MODE2:3;            /* [8:6] operand usage of S/ O resource - RW */
    ureg32 MODE3:3;            /* [11:9] operand usage of S/ O resource - RW */
    ureg32 MODE4:3;            /* [14:12] operand usage of S/ O resource - RW */
    ureg32 MODE5:3;            /* [17:15] operand usage of S/ O resource - RW */
    ureg32 MODE6:3;            /* [20:18] operand usage of S/ O resource - RW */
    ureg32 MODE7:3;            /* [23:21] operand usage of S/ O resource - RW */
    ureg32 WRITE_EN0:1;        /* [24:24] enable writing of configuration bit fields TIO[i]_G[g]_OP_USAGE.MODE[c] - RW */
    ureg32 WRITE_EN1:1;        /* [25:25] enable writing of configuration bit fields TIO[i]_G[g]_OP_USAGE.MODE[c] - RW */
    ureg32 WRITE_EN2:1;        /* [26:26] enable writing of configuration bit fields TIO[i]_G[g]_OP_USAGE.MODE[c] - RW */
    ureg32 WRITE_EN3:1;        /* [27:27] enable writing of configuration bit fields TIO[i]_G[g]_OP_USAGE.MODE[c] - RW */
    ureg32 WRITE_EN4:1;        /* [28:28] enable writing of configuration bit fields TIO[i]_G[g]_OP_USAGE.MODE[c] - RW */
    ureg32 WRITE_EN5:1;        /* [29:29] enable writing of configuration bit fields TIO[i]_G[g]_OP_USAGE.MODE[c] - RW */
    ureg32 WRITE_EN6:1;        /* [30:30] enable writing of configuration bit fields TIO[i]_G[g]_OP_USAGE.MODE[c] - RW */
    ureg32 WRITE_EN7:1;        /* [31:31] enable writing of configuration bit fields TIO[i]_G[g]_OP_USAGE.MODE[c] - RW */
} GTM_TIO_G_OP_USAGE_Bits;

/* TIO[i] signal sampling register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] Value of channel [x] - RW */
    ureg32 CH1:1;                /* [1:1] Value of channel [x] - RW */
    ureg32 CH2:1;                /* [2:2] Value of channel [x] - RW */
    ureg32 CH3:1;                /* [3:3] Value of channel [x] - RW */
    ureg32 CH4:1;                /* [4:4] Value of channel [x] - RW */
    ureg32 CH5:1;                /* [5:5] Value of channel [x] - RW */
    ureg32 CH6:1;                /* [6:6] Value of channel [x] - RW */
    ureg32 CH7:1;                /* [7:7] Value of channel [x] - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_S_Bits;

/* TIO[i] output register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] Value driven on output of channel [x]. - RW */
    ureg32 CH1:1;                /* [1:1] Value driven on output of channel [x]. - RW */
    ureg32 CH2:1;                /* [2:2] Value driven on output of channel [x]. - RW */
    ureg32 CH3:1;                /* [3:3] Value driven on output of channel [x]. - RW */
    ureg32 CH4:1;                /* [4:4] Value driven on output of channel [x]. - RW */
    ureg32 CH5:1;                /* [5:5] Value driven on output of channel [x]. - RW */
    ureg32 CH6:1;                /* [6:6] Value driven on output of channel [x]. - RW */
    ureg32 CH7:1;                /* [7:7] Value driven on output of channel [x]. - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_O_Bits;

/* TIO[i] enable/disable register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] Enable/Disable request of channel [x]. - RW */
    ureg32 CH1:1;                /* [1:1] Enable/Disable request of channel [x]. - RW */
    ureg32 CH2:1;                /* [2:2] Enable/Disable request of channel [x]. - RW */
    ureg32 CH3:1;                /* [3:3] Enable/Disable request of channel [x]. - RW */
    ureg32 CH4:1;                /* [4:4] Enable/Disable request of channel [x]. - RW */
    ureg32 CH5:1;                /* [5:5] Enable/Disable request of channel [x]. - RW */
    ureg32 CH6:1;                /* [6:6] Enable/Disable request of channel [x]. - RW */
    ureg32 CH7:1;                /* [7:7] Enable/Disable request of channel [x]. - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_ENDIS_Bits;

/* TIO[i] signal invert register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] Enable/Disable signal inversion of channel [x]. - RW */
    ureg32 CH1:1;                /* [1:1] Enable/Disable signal inversion of channel [x]. - RW */
    ureg32 CH2:1;                /* [2:2] Enable/Disable signal inversion of channel [x]. - RW */
    ureg32 CH3:1;                /* [3:3] Enable/Disable signal inversion of channel [x]. - RW */
    ureg32 CH4:1;                /* [4:4] Enable/Disable signal inversion of channel [x]. - RW */
    ureg32 CH5:1;                /* [5:5] Enable/Disable signal inversion of channel [x]. - RW */
    ureg32 CH6:1;                /* [6:6] Enable/Disable signal inversion of channel [x]. - RW */
    ureg32 CH7:1;                /* [7:7] Enable/Disable signal inversion of channel [x]. - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_INVERT_Bits;

/* TIO[i] input mode register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] Enable/Disable input mode of channel [x]. - RW */
    ureg32 CH1:1;                /* [1:1] Enable/Disable input mode of channel [x]. - RW */
    ureg32 CH2:1;                /* [2:2] Enable/Disable input mode of channel [x]. - RW */
    ureg32 CH3:1;                /* [3:3] Enable/Disable input mode of channel [x]. - RW */
    ureg32 CH4:1;                /* [4:4] Enable/Disable input mode of channel [x]. - RW */
    ureg32 CH5:1;                /* [5:5] Enable/Disable input mode of channel [x]. - RW */
    ureg32 CH6:1;                /* [6:6] Enable/Disable input mode of channel [x]. - RW */
    ureg32 CH7:1;                /* [7:7] Enable/Disable input mode of channel [x]. - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_INPUT_MODE_Bits;

/* TIO[i] cyclic mode register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] Enable/Disable cyclic mode of channel [x]. - RW */
    ureg32 CH1:1;                /* [1:1] Enable/Disable cyclic mode of channel [x]. - RW */
    ureg32 CH2:1;                /* [2:2] Enable/Disable cyclic mode of channel [x]. - RW */
    ureg32 CH3:1;                /* [3:3] Enable/Disable cyclic mode of channel [x]. - RW */
    ureg32 CH4:1;                /* [4:4] Enable/Disable cyclic mode of channel [x]. - RW */
    ureg32 CH5:1;                /* [5:5] Enable/Disable cyclic mode of channel [x]. - RW */
    ureg32 CH6:1;                /* [6:6] Enable/Disable cyclic mode of channel [x]. - RW */
    ureg32 CH7:1;                /* [7:7] Enable/Disable cyclic mode of channel [x]. - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_CYCLIC_MODE_Bits;

/* TIO[i] enable Trigger Output - output gating register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] enable gating of Trigger Output events of channel [x] - RW */
    ureg32 CH1:1;                /* [1:1] enable gating of Trigger Output events of channel [x] - RW */
    ureg32 CH2:1;                /* [2:2] enable gating of Trigger Output events of channel [x] - RW */
    ureg32 CH3:1;                /* [3:3] enable gating of Trigger Output events of channel [x] - RW */
    ureg32 CH4:1;                /* [4:4] enable gating of Trigger Output events of channel [x] - RW */
    ureg32 CH5:1;                /* [5:5] enable gating of Trigger Output events of channel [x] - RW */
    ureg32 CH6:1;                /* [6:6] enable gating of Trigger Output events of channel [x] - RW */
    ureg32 CH7:1;                /* [7:7] enable gating of Trigger Output events of channel [x] - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_TRIG_OUT_GATE_EN_Bits;

/* TIO[i] enable PL_TRIG_OUT output gating register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] enable gating of PL_TRIG_OUT events of channel [x] - RW */
    ureg32 CH1:1;                /* [1:1] enable gating of PL_TRIG_OUT events of channel [x] - RW */
    ureg32 CH2:1;                /* [2:2] enable gating of PL_TRIG_OUT events of channel [x] - RW */
    ureg32 CH3:1;                /* [3:3] enable gating of PL_TRIG_OUT events of channel [x] - RW */
    ureg32 CH4:1;                /* [4:4] enable gating of PL_TRIG_OUT events of channel [x] - RW */
    ureg32 CH5:1;                /* [5:5] enable gating of PL_TRIG_OUT events of channel [x] - RW */
    ureg32 CH6:1;                /* [6:6] enable gating of PL_TRIG_OUT events of channel [x] - RW */
    ureg32 CH7:1;                /* [7:7] enable gating of PL_TRIG_OUT events of channel [x] - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_PLTRIG_OUT_GATE_EN_Bits;

/* TIO[i] clear signal sampling register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] Clear channel [x] - RW */
    ureg32 CH1:1;                /* [1:1] Clear channel [x] - RW */
    ureg32 CH2:1;                /* [2:2] Clear channel [x] - RW */
    ureg32 CH3:1;                /* [3:3] Clear channel [x] - RW */
    ureg32 CH4:1;                /* [4:4] Clear channel [x] - RW */
    ureg32 CH5:1;                /* [5:5] Clear channel [x] - RW */
    ureg32 CH6:1;                /* [6:6] Clear channel [x] - RW */
    ureg32 CH7:1;                /* [7:7] Clear channel [x] - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_CS_Bits;

/* TIO[i] clear output register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] Clear channel [x]. - RW */
    ureg32 CH1:1;                /* [1:1] Clear channel [x]. - RW */
    ureg32 CH2:1;                /* [2:2] Clear channel [x]. - RW */
    ureg32 CH3:1;                /* [3:3] Clear channel [x]. - RW */
    ureg32 CH4:1;                /* [4:4] Clear channel [x]. - RW */
    ureg32 CH5:1;                /* [5:5] Clear channel [x]. - RW */
    ureg32 CH6:1;                /* [6:6] Clear channel [x]. - RW */
    ureg32 CH7:1;                /* [7:7] Clear channel [x]. - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_CO_Bits;

/* TIO[i] disable register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] Disable request of channel [x]. - RW */
    ureg32 CH1:1;                /* [1:1] Disable request of channel [x]. - RW */
    ureg32 CH2:1;                /* [2:2] Disable request of channel [x]. - RW */
    ureg32 CH3:1;                /* [3:3] Disable request of channel [x]. - RW */
    ureg32 CH4:1;                /* [4:4] Disable request of channel [x]. - RW */
    ureg32 CH5:1;                /* [5:5] Disable request of channel [x]. - RW */
    ureg32 CH6:1;                /* [6:6] Disable request of channel [x]. - RW */
    ureg32 CH7:1;                /* [7:7] Disable request of channel [x]. - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_CENDIS_Bits;

/* TIO[i] clear signal invert register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] Disable signal inversion of channel [x]. - RW */
    ureg32 CH1:1;                /* [1:1] Disable signal inversion of channel [x]. - RW */
    ureg32 CH2:1;                /* [2:2] Disable signal inversion of channel [x]. - RW */
    ureg32 CH3:1;                /* [3:3] Disable signal inversion of channel [x]. - RW */
    ureg32 CH4:1;                /* [4:4] Disable signal inversion of channel [x]. - RW */
    ureg32 CH5:1;                /* [5:5] Disable signal inversion of channel [x]. - RW */
    ureg32 CH6:1;                /* [6:6] Disable signal inversion of channel [x]. - RW */
    ureg32 CH7:1;                /* [7:7] Disable signal inversion of channel [x]. - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_CINVERT_Bits;

/* TIO[i] disable input mode register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] Disable input mode of channel [x]. - RW */
    ureg32 CH1:1;                /* [1:1] Disable input mode of channel [x]. - RW */
    ureg32 CH2:1;                /* [2:2] Disable input mode of channel [x]. - RW */
    ureg32 CH3:1;                /* [3:3] Disable input mode of channel [x]. - RW */
    ureg32 CH4:1;                /* [4:4] Disable input mode of channel [x]. - RW */
    ureg32 CH5:1;                /* [5:5] Disable input mode of channel [x]. - RW */
    ureg32 CH6:1;                /* [6:6] Disable input mode of channel [x]. - RW */
    ureg32 CH7:1;                /* [7:7] Disable input mode of channel [x]. - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_CINPUT_MODE_Bits;

/* TIO[i] disable cyclic mode register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] Disable cyclic mode of channel [x]. - RW */
    ureg32 CH1:1;                /* [1:1] Disable cyclic mode of channel [x]. - RW */
    ureg32 CH2:1;                /* [2:2] Disable cyclic mode of channel [x]. - RW */
    ureg32 CH3:1;                /* [3:3] Disable cyclic mode of channel [x]. - RW */
    ureg32 CH4:1;                /* [4:4] Disable cyclic mode of channel [x]. - RW */
    ureg32 CH5:1;                /* [5:5] Disable cyclic mode of channel [x]. - RW */
    ureg32 CH6:1;                /* [6:6] Disable cyclic mode of channel [x]. - RW */
    ureg32 CH7:1;                /* [7:7] Disable cyclic mode of channel [x]. - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_CCYCLIC_MODE_Bits;

/* TIO[i] clear Trigger Output - output gating register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] disable gating of Trigger Output events of channel [x] - RW */
    ureg32 CH1:1;                /* [1:1] disable gating of Trigger Output events of channel [x] - RW */
    ureg32 CH2:1;                /* [2:2] disable gating of Trigger Output events of channel [x] - RW */
    ureg32 CH3:1;                /* [3:3] disable gating of Trigger Output events of channel [x] - RW */
    ureg32 CH4:1;                /* [4:4] disable gating of Trigger Output events of channel [x] - RW */
    ureg32 CH5:1;                /* [5:5] disable gating of Trigger Output events of channel [x] - RW */
    ureg32 CH6:1;                /* [6:6] disable gating of Trigger Output events of channel [x] - RW */
    ureg32 CH7:1;                /* [7:7] disable gating of Trigger Output events of channel [x] - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_CTRIG_OUT_GATE_EN_Bits;

/* TIO[i] clear PL_TRIG_OUT output gating register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] disable gating of PL_TRIG_OUT events of channel [x] - RW */
    ureg32 CH1:1;                /* [1:1] disable gating of PL_TRIG_OUT events of channel [x] - RW */
    ureg32 CH2:1;                /* [2:2] disable gating of PL_TRIG_OUT events of channel [x] - RW */
    ureg32 CH3:1;                /* [3:3] disable gating of PL_TRIG_OUT events of channel [x] - RW */
    ureg32 CH4:1;                /* [4:4] disable gating of PL_TRIG_OUT events of channel [x] - RW */
    ureg32 CH5:1;                /* [5:5] disable gating of PL_TRIG_OUT events of channel [x] - RW */
    ureg32 CH6:1;                /* [6:6] disable gating of PL_TRIG_OUT events of channel [x] - RW */
    ureg32 CH7:1;                /* [7:7] disable gating of PL_TRIG_OUT events of channel [x] - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_CPLTRIG_OUT_GATE_EN_Bits;

/* TIO[i] set signal sampling register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] Set channel [x]. - RW */
    ureg32 CH1:1;                /* [1:1] Set channel [x]. - RW */
    ureg32 CH2:1;                /* [2:2] Set channel [x]. - RW */
    ureg32 CH3:1;                /* [3:3] Set channel [x]. - RW */
    ureg32 CH4:1;                /* [4:4] Set channel [x]. - RW */
    ureg32 CH5:1;                /* [5:5] Set channel [x]. - RW */
    ureg32 CH6:1;                /* [6:6] Set channel [x]. - RW */
    ureg32 CH7:1;                /* [7:7] Set channel [x]. - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_SS_Bits;

/* TIO[i] set output register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] Set channel [x]. - RW */
    ureg32 CH1:1;                /* [1:1] Set channel [x]. - RW */
    ureg32 CH2:1;                /* [2:2] Set channel [x]. - RW */
    ureg32 CH3:1;                /* [3:3] Set channel [x]. - RW */
    ureg32 CH4:1;                /* [4:4] Set channel [x]. - RW */
    ureg32 CH5:1;                /* [5:5] Set channel [x]. - RW */
    ureg32 CH6:1;                /* [6:6] Set channel [x]. - RW */
    ureg32 CH7:1;                /* [7:7] Set channel [x]. - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_SO_Bits;

/* TIO[i] enable register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] Enable request of channel [x]. - RW */
    ureg32 CH1:1;                /* [1:1] Enable request of channel [x]. - RW */
    ureg32 CH2:1;                /* [2:2] Enable request of channel [x]. - RW */
    ureg32 CH3:1;                /* [3:3] Enable request of channel [x]. - RW */
    ureg32 CH4:1;                /* [4:4] Enable request of channel [x]. - RW */
    ureg32 CH5:1;                /* [5:5] Enable request of channel [x]. - RW */
    ureg32 CH6:1;                /* [6:6] Enable request of channel [x]. - RW */
    ureg32 CH7:1;                /* [7:7] Enable request of channel [x]. - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_SENDIS_Bits;

/* TIO[i] set signal invert register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] Enable signal inversion of channel [x]. - RW */
    ureg32 CH1:1;                /* [1:1] Enable signal inversion of channel [x]. - RW */
    ureg32 CH2:1;                /* [2:2] Enable signal inversion of channel [x]. - RW */
    ureg32 CH3:1;                /* [3:3] Enable signal inversion of channel [x]. - RW */
    ureg32 CH4:1;                /* [4:4] Enable signal inversion of channel [x]. - RW */
    ureg32 CH5:1;                /* [5:5] Enable signal inversion of channel [x]. - RW */
    ureg32 CH6:1;                /* [6:6] Enable signal inversion of channel [x]. - RW */
    ureg32 CH7:1;                /* [7:7] Enable signal inversion of channel [x]. - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_SINVERT_Bits;

/* TIO[i] enable input mode register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] Enable input mode of channel [x]. - RW */
    ureg32 CH1:1;                /* [1:1] Enable input mode of channel [x]. - RW */
    ureg32 CH2:1;                /* [2:2] Enable input mode of channel [x]. - RW */
    ureg32 CH3:1;                /* [3:3] Enable input mode of channel [x]. - RW */
    ureg32 CH4:1;                /* [4:4] Enable input mode of channel [x]. - RW */
    ureg32 CH5:1;                /* [5:5] Enable input mode of channel [x]. - RW */
    ureg32 CH6:1;                /* [6:6] Enable input mode of channel [x]. - RW */
    ureg32 CH7:1;                /* [7:7] Enable input mode of channel [x]. - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_SINPUT_MODE_Bits;

/* TIO[i] enable cyclic mode register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] Enable cyclic mode of channel [x]. - RW */
    ureg32 CH1:1;                /* [1:1] Enable cyclic mode of channel [x]. - RW */
    ureg32 CH2:1;                /* [2:2] Enable cyclic mode of channel [x]. - RW */
    ureg32 CH3:1;                /* [3:3] Enable cyclic mode of channel [x]. - RW */
    ureg32 CH4:1;                /* [4:4] Enable cyclic mode of channel [x]. - RW */
    ureg32 CH5:1;                /* [5:5] Enable cyclic mode of channel [x]. - RW */
    ureg32 CH6:1;                /* [6:6] Enable cyclic mode of channel [x]. - RW */
    ureg32 CH7:1;                /* [7:7] Enable cyclic mode of channel [x]. - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_SCYCLIC_MODE_Bits;

/* TIO[i] set Trigger Output - output gating register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] enable gating of Trigger Output events of channel [x] - RW */
    ureg32 CH1:1;                /* [1:1] enable gating of Trigger Output events of channel [x] - RW */
    ureg32 CH2:1;                /* [2:2] enable gating of Trigger Output events of channel [x] - RW */
    ureg32 CH3:1;                /* [3:3] enable gating of Trigger Output events of channel [x] - RW */
    ureg32 CH4:1;                /* [4:4] enable gating of Trigger Output events of channel [x] - RW */
    ureg32 CH5:1;                /* [5:5] enable gating of Trigger Output events of channel [x] - RW */
    ureg32 CH6:1;                /* [6:6] enable gating of Trigger Output events of channel [x] - RW */
    ureg32 CH7:1;                /* [7:7] enable gating of Trigger Output events of channel [x] - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_STRIG_OUT_GATE_EN_Bits;

/* TIO[i] set PL_TRIG_OUT output gating register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] enable gating of PL_TRIG_OUT events of channel [x] - RW */
    ureg32 CH1:1;                /* [1:1] enable gating of PL_TRIG_OUT events of channel [x] - RW */
    ureg32 CH2:1;                /* [2:2] enable gating of PL_TRIG_OUT events of channel [x] - RW */
    ureg32 CH3:1;                /* [3:3] enable gating of PL_TRIG_OUT events of channel [x] - RW */
    ureg32 CH4:1;                /* [4:4] enable gating of PL_TRIG_OUT events of channel [x] - RW */
    ureg32 CH5:1;                /* [5:5] enable gating of PL_TRIG_OUT events of channel [x] - RW */
    ureg32 CH6:1;                /* [6:6] enable gating of PL_TRIG_OUT events of channel [x] - RW */
    ureg32 CH7:1;                /* [7:7] enable gating of PL_TRIG_OUT events of channel [x] - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_SPLTRIG_OUT_GATE_EN_Bits;

/* TIO[i] invert signal sampling register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] Invert channel [x]. - RW */
    ureg32 CH1:1;                /* [1:1] Invert channel [x]. - RW */
    ureg32 CH2:1;                /* [2:2] Invert channel [x]. - RW */
    ureg32 CH3:1;                /* [3:3] Invert channel [x]. - RW */
    ureg32 CH4:1;                /* [4:4] Invert channel [x]. - RW */
    ureg32 CH5:1;                /* [5:5] Invert channel [x]. - RW */
    ureg32 CH6:1;                /* [6:6] Invert channel [x]. - RW */
    ureg32 CH7:1;                /* [7:7] Invert channel [x]. - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_IS_Bits;

/* TIO[i] invert output register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] Invert channel [x]. - RW */
    ureg32 CH1:1;                /* [1:1] Invert channel [x]. - RW */
    ureg32 CH2:1;                /* [2:2] Invert channel [x]. - RW */
    ureg32 CH3:1;                /* [3:3] Invert channel [x]. - RW */
    ureg32 CH4:1;                /* [4:4] Invert channel [x]. - RW */
    ureg32 CH5:1;                /* [5:5] Invert channel [x]. - RW */
    ureg32 CH6:1;                /* [6:6] Invert channel [x]. - RW */
    ureg32 CH7:1;                /* [7:7] Invert channel [x]. - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_IO_Bits;

/* TIO[i] toggle enable/disable register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] Toggle state request of channel [x]. - RW */
    ureg32 CH1:1;                /* [1:1] Toggle state request of channel [x]. - RW */
    ureg32 CH2:1;                /* [2:2] Toggle state request of channel [x]. - RW */
    ureg32 CH3:1;                /* [3:3] Toggle state request of channel [x]. - RW */
    ureg32 CH4:1;                /* [4:4] Toggle state request of channel [x]. - RW */
    ureg32 CH5:1;                /* [5:5] Toggle state request of channel [x]. - RW */
    ureg32 CH6:1;                /* [6:6] Toggle state request of channel [x]. - RW */
    ureg32 CH7:1;                /* [7:7] Toggle state request of channel [x]. - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_IENDIS_Bits;

/* TIO[i] toggle signal invert register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] Invert signal inversion of channel [x]. - RW */
    ureg32 CH1:1;                /* [1:1] Invert signal inversion of channel [x]. - RW */
    ureg32 CH2:1;                /* [2:2] Invert signal inversion of channel [x]. - RW */
    ureg32 CH3:1;                /* [3:3] Invert signal inversion of channel [x]. - RW */
    ureg32 CH4:1;                /* [4:4] Invert signal inversion of channel [x]. - RW */
    ureg32 CH5:1;                /* [5:5] Invert signal inversion of channel [x]. - RW */
    ureg32 CH6:1;                /* [6:6] Invert signal inversion of channel [x]. - RW */
    ureg32 CH7:1;                /* [7:7] Invert signal inversion of channel [x]. - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_IINVERT_Bits;

/* TIO[i] enable input mode register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] Toggle input mode of channel [x]. - RW */
    ureg32 CH1:1;                /* [1:1] Toggle input mode of channel [x]. - RW */
    ureg32 CH2:1;                /* [2:2] Toggle input mode of channel [x]. - RW */
    ureg32 CH3:1;                /* [3:3] Toggle input mode of channel [x]. - RW */
    ureg32 CH4:1;                /* [4:4] Toggle input mode of channel [x]. - RW */
    ureg32 CH5:1;                /* [5:5] Toggle input mode of channel [x]. - RW */
    ureg32 CH6:1;                /* [6:6] Toggle input mode of channel [x]. - RW */
    ureg32 CH7:1;                /* [7:7] Toggle input mode of channel [x]. - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_IINPUT_MODE_Bits;

/* TIO[i] enable cyclic mode register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] Toggle cyclic mode of channel [x]. - RW */
    ureg32 CH1:1;                /* [1:1] Toggle cyclic mode of channel [x]. - RW */
    ureg32 CH2:1;                /* [2:2] Toggle cyclic mode of channel [x]. - RW */
    ureg32 CH3:1;                /* [3:3] Toggle cyclic mode of channel [x]. - RW */
    ureg32 CH4:1;                /* [4:4] Toggle cyclic mode of channel [x]. - RW */
    ureg32 CH5:1;                /* [5:5] Toggle cyclic mode of channel [x]. - RW */
    ureg32 CH6:1;                /* [6:6] Toggle cyclic mode of channel [x]. - RW */
    ureg32 CH7:1;                /* [7:7] Toggle cyclic mode of channel [x]. - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_ICYCLIC_MODE_Bits;

/* TIO[i] force update register */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] issue immediately a signal pulse on the update signal of channel [x]  - RW */
    ureg32 CH1:1;                /* [1:1] issue immediately a signal pulse on the update signal of channel [x]  - RW */
    ureg32 CH2:1;                /* [2:2] issue immediately a signal pulse on the update signal of channel [x]  - RW */
    ureg32 CH3:1;                /* [3:3] issue immediately a signal pulse on the update signal of channel [x]  - RW */
    ureg32 CH4:1;                /* [4:4] issue immediately a signal pulse on the update signal of channel [x]  - RW */
    ureg32 CH5:1;                /* [5:5] issue immediately a signal pulse on the update signal of channel [x]  - RW */
    ureg32 CH6:1;                /* [6:6] issue immediately a signal pulse on the update signal of channel [x]  - RW */
    ureg32 CH7:1;                /* [7:7] issue immediately a signal pulse on the update signal of channel [x]  - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_FUPD_Bits;

/* TIO[i] configuration register */
typedef struct
{
    ureg32 NTIO_CH8:2;           /* [1:0] signals availability of amount of channels   - RO */
    ureg32 reserved_2:2;         /* [3:2] Internal  reserved */
    ureg32 TIO_PLUS:1;           /* [4:4] signals availability of TIOplus functionality - RO */
    ureg32 reserved_5:27;        /* [31:5] Internal  reserved */
} GTM_TIO_HW_CONF_Bits;

/* TIO[i] resource selection control register 1 */
typedef struct
{
    ureg32 reserved_0:24;         /* [23:0] Internal  reserved */
    ureg32 SEL_CLKEN6_0:1;        /* [24:24] select source of RS_CLKEN[g][6:6] for channels [g]*8 .. [g]*8+7 - RW */
    ureg32 reserved_25:3;         /* [27:25] Internal  reserved */
    ureg32 SEL_CLKEN7_0:1;        /* [28:28] select source of RS_CLKEN[g][7:7] for channels [g]*8 .. [g]*8+7 - RW */
    ureg32 reserved_29:3;         /* [31:29] Internal  reserved */
} GTM_TIO_RSEL_CTRL1_Bits;

/* TIO[i] resource selection control register 2 */
typedef struct
{
    ureg32 reserved_0:4;         /* [3:0] Internal  reserved */
    ureg32 SEL_TB1_0:1;          /* [4:4] select source of RS_TB1[g] for channels [g]*8 .. [g]*8+7 - RW */
    ureg32 reserved_5:3;         /* [7:5] Internal  reserved */
    ureg32 SEL_TB2_0:1;          /* [8:8] select source of RS_TB2[g] for channels [g]*8 .. [g]*8+7 - RW */
    ureg32 reserved_9:23;        /* [31:9] Internal  reserved */
} GTM_TIO_RSEL_CTRL2_Bits;

/* TIO[i] software reset for TIO Plus functionality */
typedef struct
{
    ureg32 CH0:1;                /* [0:0] reset TIO_Plus resources of channel [x]  - RW */
    ureg32 CH1:1;                /* [1:1] reset TIO_Plus resources of channel [x]  - RW */
    ureg32 CH2:1;                /* [2:2] reset TIO_Plus resources of channel [x]  - RW */
    ureg32 CH3:1;                /* [3:3] reset TIO_Plus resources of channel [x]  - RW */
    ureg32 CH4:1;                /* [4:4] reset TIO_Plus resources of channel [x]  - RW */
    ureg32 CH5:1;                /* [5:5] reset TIO_Plus resources of channel [x]  - RW */
    ureg32 CH6:1;                /* [6:6] reset TIO_Plus resources of channel [x]  - RW */
    ureg32 CH7:1;                /* [7:7] reset TIO_Plus resources of channel [x]  - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_TIO_PL_SWRST_Bits;

/* CCM[i] Address Range Protector [a] Control Register */
typedef struct
{
    ureg32 ADDR:16;              /* [15:0] ARP base address.  - RW */
    ureg32 SIZE:4;               /* [19:16] Size of ARP - RW */
    ureg32 reserved_20:4;        /* [23:20] Internal  reserved */
    ureg32 DIS_PROT:1;           /* [24:24] Disable ARP protection. - RW */
    ureg32 reserved_25:6;        /* [30:25] Internal  reserved */
    ureg32 WPROT_AEI:1;          /* [31:31] AEI slave write protection. - RW */
} GTM_CCM_ARP_CTRL_Bits;

/* CCM[i] Address Range Protector [a] Protection Register */
typedef struct
{
    ureg32 WPROT0:1;             /* [0:0] Write Protection MCS channel [x]. - RW */
    ureg32 WPROT1:1;             /* [1:1] Write Protection MCS channel [x]. - RW */
    ureg32 WPROT2:1;             /* [2:2] Write Protection MCS channel [x]. - RW */
    ureg32 WPROT3:1;             /* [3:3] Write Protection MCS channel [x]. - RW */
    ureg32 WPROT4:1;             /* [4:4] Write Protection MCS channel [x]. - RW */
    ureg32 WPROT5:1;             /* [5:5] Write Protection MCS channel [x]. - RW */
    ureg32 WPROT6:1;             /* [6:6] Write Protection MCS channel [x]. - RW */
    ureg32 WPROT7:1;             /* [7:7] Write Protection MCS channel [x]. - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_CCM_ARP_PROT_Bits;

/* CCM[i] TIO Group 0,1 Output Register */
typedef struct
{
    ureg32 TIO_G0_OUT0:1;          /* [0:0] Output level snapshot of TIO[i]_G0_OUT channel [c] - RO */
    ureg32 TIO_G0_OUT1:1;          /* [1:1] Output level snapshot of TIO[i]_G0_OUT channel [c] - RO */
    ureg32 TIO_G0_OUT2:1;          /* [2:2] Output level snapshot of TIO[i]_G0_OUT channel [c] - RO */
    ureg32 TIO_G0_OUT3:1;          /* [3:3] Output level snapshot of TIO[i]_G0_OUT channel [c] - RO */
    ureg32 TIO_G0_OUT4:1;          /* [4:4] Output level snapshot of TIO[i]_G0_OUT channel [c] - RO */
    ureg32 TIO_G0_OUT5:1;          /* [5:5] Output level snapshot of TIO[i]_G0_OUT channel [c] - RO */
    ureg32 TIO_G0_OUT6:1;          /* [6:6] Output level snapshot of TIO[i]_G0_OUT channel [c] - RO */
    ureg32 TIO_G0_OUT7:1;          /* [7:7] Output level snapshot of TIO[i]_G0_OUT channel [c] - RO */
    ureg32 reserved_8:8;           /* [15:8] Internal  reserved */
    ureg32 TIO_G0_OUT_N0:1;        /* [16:16] Output level snapshot of channel [c]. - RO */
    ureg32 TIO_G0_OUT_N1:1;        /* [17:17] Output level snapshot of channel [c]. - RO */
    ureg32 TIO_G0_OUT_N2:1;        /* [18:18] Output level snapshot of channel [c]. - RO */
    ureg32 TIO_G0_OUT_N3:1;        /* [19:19] Output level snapshot of channel [c]. - RO */
    ureg32 TIO_G0_OUT_N4:1;        /* [20:20] Output level snapshot of channel [c]. - RO */
    ureg32 TIO_G0_OUT_N5:1;        /* [21:21] Output level snapshot of channel [c]. - RO */
    ureg32 TIO_G0_OUT_N6:1;        /* [22:22] Output level snapshot of channel [c]. - RO */
    ureg32 TIO_G0_OUT_N7:1;        /* [23:23] Output level snapshot of channel [c]. - RO */
    ureg32 reserved_24:8;          /* [31:24] Internal  reserved */
} GTM_CCM_TIO_G_OUT_Bits;

/* CCM[i] 2. Hardware Configuration Register */
typedef struct
{
    ureg32 AXIM_ID_WIDTH:5;            /* [4:0] Defines which LSB of AXIM_ID are send to the bus - RO */
    ureg32 AXIM_PRIV_ACC:1;            /* [5:5] Privileged AXI master access constant - RO */
    ureg32 AXIM_SEC_ACC:1;             /* [6:6] Secure AXI master access constant - RO */
    ureg32 AXIM_POSTED_WRITE:1;        /* [7:7] Write transaction without response - RO */
    ureg32 reserved_8:1;               /* [8:8] Internal  reserved */
    ureg32 TIO_OUT_RST:1;              /* [9:9] Reset level for all TIO output signals. - RO */
    ureg32 reserved_10:6;              /* [15:10] Internal  reserved */
    ureg32 AXIS_DATA_SIZE:1;           /* [16:16] Defines the data bus width of the AXI slave interface - RO */
    ureg32 reserved_17:1;              /* [17:17] Internal  reserved */
    ureg32 AXIM_DATA_SIZE:1;           /* [18:18] Defines the data bus width of the AXI master interface - RO */
    ureg32 reserved_19:13;             /* [31:19] Internal  reserved */
} GTM_CCM_HW_CONF2_Bits;

/* CCM[i] MCS Bus Master Status Register */
typedef struct
{
    ureg32 AEIM_XPT_ADDR:16;        /* [15:0] Exception address - RW */
    ureg32 reserved_16:8;           /* [23:16] Internal  reserved */
    ureg32 AEIM_XPT_STA:2;          /* [25:24] AEIM exception status - RW */
    ureg32 reserved_26:6;           /* [31:26] Internal  reserved */
} GTM_CCM_AEIM_STA_Bits;

/* CCM[i] Hardware Configuration Register */
typedef struct
{
    ureg32 GRSTEN:1;                          /* [0:0] Global Reset Enable - RO */
    ureg32 BRIDGE_MODE_RST:1;                 /* [1:1] Bridge mode after reset - RO */
    ureg32 SYNC_INPUT_REG:1;                  /* [2:2] Additional pipelined stage in synchronous bridge mode - RO */
    ureg32 CFG_CLOCK_RATE:1;                  /* [3:3] Clocks per ARU transfer - RO */
    ureg32 ATOM_OUT_RST:1;                    /* [4:4] CCM_ATOM_OUT reset level - RO */
    ureg32 ATOM_TRIG_CHAIN:3;                 /* [7:5] ATOM trigger chain length without synchronization register - RO */
    ureg32 TOM_OUT_RST:1;                     /* [8:8] CCM_TOM_OUT reset level - RO */
    ureg32 TOM_TRIG_CHAIN:3;                  /* [11:9] TOM trigger chain length without synchronization register - RO */
    ureg32 RAM_INIT_RST:1;                    /* [12:12] RAM initialization from reset - RO */
    ureg32 ERM:1;                             /* [13:13] Enable RAM1 MSB for available MCS modules - RO */
    ureg32 reserved_14:1;                     /* [14:14] Internal  reserved */
    ureg32 RESET_ACTIVE:1;                    /* [15:15] Active level of asynchronous reset - RO */
    ureg32 IRQ_MODE_LEVEL:1;                  /* [16:16] Signalize availability of Level IRQ mode - RO */
    ureg32 IRQ_MODE_PULSE:1;                  /* [17:17] Signalize availability of Pulse IRQ mode - RO */
    ureg32 IRQ_MODE_PULSE_NOTIFY:1;           /* [18:18] Signalize availability of Pulse Notoify IRQ mode - RO */
    ureg32 IRQ_MODE_SINGLE_PULSE:1;           /* [19:19] Signalize availability of Single Pulse IRQ mode - RO */
    ureg32 ATOM_TRIG_INTCHAIN:4;              /* [23:20] ATOM internal trigger chain length for pipeline register - RO */
    ureg32 TOM_TRIG_INTCHAIN:5;               /* [28:24] TOM internal trigger chain length for pipeline register - RO */
    ureg32 INT_CLK_EN_GEN:1;                  /* [29:29] Internal clock enable generation - RO */
    ureg32 AEI_ADDR_PIPELINE_STAGE:1;         /* [30:30] Address pipeline stage implemented - RO */
    ureg32 AEI_RDATA_PIPELINE_STAGE:1;        /* [31:31] Read data pipeline stage implemented - RO */
} GTM_CCM_HW_CONF_Bits;

/* CCM[i] TIM AUX Input Source Register */
typedef struct
{
    ureg32 SRC_CH0:1;              /* [0:0] Defines CCM_AUX_IN source of TIM[i] channel 0 - RW */
    ureg32 SRC_CH1:1;              /* [1:1] Defines AUX_IN source of TIM[i] channel 1 - RW */
    ureg32 SRC_CH2:1;              /* [2:2] Defines CCM_AUX_IN source of TIM[i] channel 2 - RW */
    ureg32 SRC_CH3:1;              /* [3:3] Defines CCM_AUX_IN source of TIM[i] channel 3 - RW */
    ureg32 SRC_CH4:1;              /* [4:4] Defines CCM_AUX_IN source of TIM[i] channel 4 - RW */
    ureg32 SRC_CH5:1;              /* [5:5] Defines CCM_AUX_IN source of TIM[i] channel 5 - RW */
    ureg32 SRC_CH6:1;              /* [6:6] Defines CCM_AUX_IN source of TIM[i] channel 6 - RW */
    ureg32 SRC_CH7:1;              /* [7:7] Defines CCM_AUX_IN source of TIM[i] channel 7 - RW */
    ureg32 reserved_8:8;           /* [15:8] Internal  reserved */
    ureg32 SEL_OUT_N_CH0:1;        /* [16:16] Use DTM_OUT[q] or DTM_OUT[q]_N signals as CCM_AUX_IN source of TIM[i] channel [x]  - RW */
    ureg32 SEL_OUT_N_CH1:1;        /* [17:17] Use DTM_OUT[q] or DTM_OUT[q]_N signals as CCM_AUX_IN source of TIM[i] channel [x]  - RW */
    ureg32 SEL_OUT_N_CH2:1;        /* [18:18] Use DTM_OUT[q] or DTM_OUT[q]_N signals as CCM_AUX_IN source of TIM[i] channel [x]  - RW */
    ureg32 SEL_OUT_N_CH3:1;        /* [19:19] Use DTM_OUT[q] or DTM_OUT[q]_N signals as CCM_AUX_IN source of TIM[i] channel [x]  - RW */
    ureg32 SEL_OUT_N_CH4:1;        /* [20:20] Use DTM_OUT[q] or DTM_OUT[q]_N signals as CCM_AUX_IN source of TIM[i] channel [x]  - RW */
    ureg32 SEL_OUT_N_CH5:1;        /* [21:21] Use DTM_OUT[q] or DTM_OUT[q]_N signals as CCM_AUX_IN source of TIM[i] channel [x]  - RW */
    ureg32 SEL_OUT_N_CH6:1;        /* [22:22] Use DTM_OUT[q] or DTM_OUT[q]_N signals as CCM_AUX_IN source of TIM[i] channel [x]  - RW */
    ureg32 SEL_OUT_N_CH7:1;        /* [23:23] Use DTM_OUT[q] or DTM_OUT[q]_N signals as CCM_AUX_IN source of TIM[i] channel [x]  - RW */
    ureg32 reserved_24:8;          /* [31:24] Internal  reserved */
} GTM_CCM_TIM_AUX_IN_SRC_Bits;

/* CCM[i] External Capture Enable Register */
typedef struct
{
    ureg32 TIM_I_EXT_CAP_EN0:1;          /* [0:0] TIM_EXT_CAPTURE signal [x] forwarding enable - RW */
    ureg32 TIM_I_EXT_CAP_EN1:1;          /* [1:1] TIM_EXT_CAPTURE signal [x] forwarding enable - RW */
    ureg32 TIM_I_EXT_CAP_EN2:1;          /* [2:2] TIM_EXT_CAPTURE signal [x] forwarding enable - RW */
    ureg32 TIM_I_EXT_CAP_EN3:1;          /* [3:3] TIM_EXT_CAPTURE signal [x] forwarding enable - RW */
    ureg32 TIM_I_EXT_CAP_EN4:1;          /* [4:4] TIM_EXT_CAPTURE signal [x] forwarding enable - RW */
    ureg32 TIM_I_EXT_CAP_EN5:1;          /* [5:5] TIM_EXT_CAPTURE signal [x] forwarding enable - RW */
    ureg32 TIM_I_EXT_CAP_EN6:1;          /* [6:6] TIM_EXT_CAPTURE signal [x] forwarding enable - RW */
    ureg32 TIM_I_EXT_CAP_EN7:1;          /* [7:7] TIM_EXT_CAPTURE signal [x] forwarding enable - RW */
    ureg32 TIM_IP1_EXT_CAP_EN0:1;        /* [8:8] TIM_EXT_CAPTURE[x:x] of instance TIM[i+1] signal [x] forwarding enable - RW */
    ureg32 TIM_IP1_EXT_CAP_EN1:1;        /* [9:9] TIM_EXT_CAPTURE[x:x] of instance TIM[i+1] signal [x] forwarding enable - RW */
    ureg32 TIM_IP1_EXT_CAP_EN2:1;        /* [10:10] TIM_EXT_CAPTURE[x:x] of instance TIM[i+1] signal [x] forwarding enable - RW */
    ureg32 TIM_IP1_EXT_CAP_EN3:1;        /* [11:11] TIM_EXT_CAPTURE[x:x] of instance TIM[i+1] signal [x] forwarding enable - RW */
    ureg32 TIM_IP1_EXT_CAP_EN4:1;        /* [12:12] TIM_EXT_CAPTURE[x:x] of instance TIM[i+1] signal [x] forwarding enable - RW */
    ureg32 TIM_IP1_EXT_CAP_EN5:1;        /* [13:13] TIM_EXT_CAPTURE[x:x] of instance TIM[i+1] signal [x] forwarding enable - RW */
    ureg32 TIM_IP1_EXT_CAP_EN6:1;        /* [14:14] TIM_EXT_CAPTURE[x:x] of instance TIM[i+1] signal [x] forwarding enable - RW */
    ureg32 TIM_IP1_EXT_CAP_EN7:1;        /* [15:15] TIM_EXT_CAPTURE[x:x] of instance TIM[i+1] signal [x] forwarding enable - RW */
    ureg32 reserved_16:16;               /* [31:16] Internal  reserved */
} GTM_CCM_EXT_CAP_EN_Bits;

/* CCM[i] TOM Output Register */
typedef struct
{
    ureg32 TOM_OUT0:1;           /* [0:0] Output level snapshot of CCM_TOM_OUT channel [x] - RO */
    ureg32 TOM_OUT1:1;           /* [1:1] Output level snapshot of CCM_TOM_OUT channel [x] - RO */
    ureg32 TOM_OUT2:1;           /* [2:2] Output level snapshot of CCM_TOM_OUT channel [x] - RO */
    ureg32 TOM_OUT3:1;           /* [3:3] Output level snapshot of CCM_TOM_OUT channel [x] - RO */
    ureg32 TOM_OUT4:1;           /* [4:4] Output level snapshot of CCM_TOM_OUT channel [x] - RO */
    ureg32 TOM_OUT5:1;           /* [5:5] Output level snapshot of CCM_TOM_OUT channel [x] - RO */
    ureg32 TOM_OUT6:1;           /* [6:6] Output level snapshot of CCM_TOM_OUT channel [x] - RO */
    ureg32 TOM_OUT7:1;           /* [7:7] Output level snapshot of CCM_TOM_OUT channel [x] - RO */
    ureg32 TOM_OUT8:1;           /* [8:8] Output level snapshot of CCM_TOM_OUT channel [x] - RO */
    ureg32 TOM_OUT9:1;           /* [9:9] Output level snapshot of CCM_TOM_OUT channel [x] - RO */
    ureg32 TOM_OUT10:1;          /* [10:10] Output level snapshot of CCM_TOM_OUT channel [x] - RO */
    ureg32 TOM_OUT11:1;          /* [11:11] Output level snapshot of CCM_TOM_OUT channel [x] - RO */
    ureg32 TOM_OUT12:1;          /* [12:12] Output level snapshot of CCM_TOM_OUT channel [x] - RO */
    ureg32 TOM_OUT13:1;          /* [13:13] Output level snapshot of CCM_TOM_OUT channel [x] - RO */
    ureg32 TOM_OUT14:1;          /* [14:14] Output level snapshot of CCM_TOM_OUT channel [x] - RO */
    ureg32 TOM_OUT15:1;          /* [15:15] Output level snapshot of CCM_TOM_OUT channel [x] - RO */
    ureg32 TOM_OUT_N0:1;         /* [16:16] Output level snapshot of CCM_TOM_OUT_N channel [x] - RO */
    ureg32 TOM_OUT_N1:1;         /* [17:17] Output level snapshot of CCM_TOM_OUT_N channel [x] - RO */
    ureg32 TOM_OUT_N2:1;         /* [18:18] Output level snapshot of CCM_TOM_OUT_N channel [x] - RO */
    ureg32 TOM_OUT_N3:1;         /* [19:19] Output level snapshot of CCM_TOM_OUT_N channel [x] - RO */
    ureg32 TOM_OUT_N4:1;         /* [20:20] Output level snapshot of CCM_TOM_OUT_N channel [x] - RO */
    ureg32 TOM_OUT_N5:1;         /* [21:21] Output level snapshot of CCM_TOM_OUT_N channel [x] - RO */
    ureg32 TOM_OUT_N6:1;         /* [22:22] Output level snapshot of CCM_TOM_OUT_N channel [x] - RO */
    ureg32 TOM_OUT_N7:1;         /* [23:23] Output level snapshot of CCM_TOM_OUT_N channel [x] - RO */
    ureg32 TOM_OUT_N8:1;         /* [24:24] Output level snapshot of CCM_TOM_OUT_N channel [x] - RO */
    ureg32 TOM_OUT_N9:1;         /* [25:25] Output level snapshot of CCM_TOM_OUT_N channel [x] - RO */
    ureg32 TOM_OUT_N10:1;        /* [26:26] Output level snapshot of CCM_TOM_OUT_N channel [x] - RO */
    ureg32 TOM_OUT_N11:1;        /* [27:27] Output level snapshot of CCM_TOM_OUT_N channel [x] - RO */
    ureg32 TOM_OUT_N12:1;        /* [28:28] Output level snapshot of CCM_TOM_OUT_N channel [x] - RO */
    ureg32 TOM_OUT_N13:1;        /* [29:29] Output level snapshot of CCM_TOM_OUT_N channel [x] - RO */
    ureg32 TOM_OUT_N14:1;        /* [30:30] Output level snapshot of CCM_TOM_OUT_N channel [x] - RO */
    ureg32 TOM_OUT_N15:1;        /* [31:31] Output level snapshot of CCM_TOM_OUT_N channel [x] - RO */
} GTM_CCM_TOM_OUT_Bits;

/* CCM[i] ATOM Output Register */
typedef struct
{
    ureg32 ATOM_I_OUT0:1;            /* [0:0] Output level snapshot of CCM_ATOM_OUT channel [x] - RO */
    ureg32 ATOM_I_OUT1:1;            /* [1:1] Output level snapshot of CCM_ATOM_OUT channel [x] - RO */
    ureg32 ATOM_I_OUT2:1;            /* [2:2] Output level snapshot of CCM_ATOM_OUT channel [x] - RO */
    ureg32 ATOM_I_OUT3:1;            /* [3:3] Output level snapshot of CCM_ATOM_OUT channel [x] - RO */
    ureg32 ATOM_I_OUT4:1;            /* [4:4] Output level snapshot of CCM_ATOM_OUT channel [x] - RO */
    ureg32 ATOM_I_OUT5:1;            /* [5:5] Output level snapshot of CCM_ATOM_OUT channel [x] - RO */
    ureg32 ATOM_I_OUT6:1;            /* [6:6] Output level snapshot of CCM_ATOM_OUT channel [x] - RO */
    ureg32 ATOM_I_OUT7:1;            /* [7:7] Output level snapshot of CCM_ATOM_OUT channel [x] - RO */
    ureg32 ATOM_I_OUT_N0:1;          /* [8:8] Output level snapshot of CCM_ATOM_OUT_N channel [x] - RO */
    ureg32 ATOM_I_OUT_N1:1;          /* [9:9] Output level snapshot of CCM_ATOM_OUT_N channel [x] - RO */
    ureg32 ATOM_I_OUT_N2:1;          /* [10:10] Output level snapshot of CCM_ATOM_OUT_N channel [x] - RO */
    ureg32 ATOM_I_OUT_N3:1;          /* [11:11] Output level snapshot of CCM_ATOM_OUT_N channel [x] - RO */
    ureg32 ATOM_I_OUT_N4:1;          /* [12:12] Output level snapshot of CCM_ATOM_OUT_N channel [x] - RO */
    ureg32 ATOM_I_OUT_N5:1;          /* [13:13] Output level snapshot of CCM_ATOM_OUT_N channel [x] - RO */
    ureg32 ATOM_I_OUT_N6:1;          /* [14:14] Output level snapshot of CCM_ATOM_OUT_N channel [x] - RO */
    ureg32 ATOM_I_OUT_N7:1;          /* [15:15] Output level snapshot of CCM_ATOM_OUT_N channel [x] - RO */
    ureg32 ATOM_IP1_OUT0:1;          /* [16:16] Output level snapshot of ATOM[i+1]_OUT channel [x] - RO */
    ureg32 ATOM_IP1_OUT1:1;          /* [17:17] Output level snapshot of ATOM[i+1]_OUT channel [x] - RO */
    ureg32 ATOM_IP1_OUT2:1;          /* [18:18] Output level snapshot of ATOM[i+1]_OUT channel [x] - RO */
    ureg32 ATOM_IP1_OUT3:1;          /* [19:19] Output level snapshot of ATOM[i+1]_OUT channel [x] - RO */
    ureg32 ATOM_IP1_OUT4:1;          /* [20:20] Output level snapshot of ATOM[i+1]_OUT channel [x] - RO */
    ureg32 ATOM_IP1_OUT5:1;          /* [21:21] Output level snapshot of ATOM[i+1]_OUT channel [x] - RO */
    ureg32 ATOM_IP1_OUT6:1;          /* [22:22] Output level snapshot of ATOM[i+1]_OUT channel [x] - RO */
    ureg32 ATOM_IP1_OUT7:1;          /* [23:23] Output level snapshot of ATOM[i+1]_OUT channel [x] - RO */
    ureg32 ATOM_IP1_OUT_N0:1;        /* [24:24] Output level snapshot of CCM_ATOM_OUT[x:x] of instance i+1 channel x - RO */
    ureg32 ATOM_IP1_OUT_N1:1;        /* [25:25] Output level snapshot of CCM_ATOM_OUT[x:x] of instance i+1 channel x - RO */
    ureg32 ATOM_IP1_OUT_N2:1;        /* [26:26] Output level snapshot of CCM_ATOM_OUT[x:x] of instance i+1 channel x - RO */
    ureg32 ATOM_IP1_OUT_N3:1;        /* [27:27] Output level snapshot of CCM_ATOM_OUT[x:x] of instance i+1 channel x - RO */
    ureg32 ATOM_IP1_OUT_N4:1;        /* [28:28] Output level snapshot of CCM_ATOM_OUT[x:x] of instance i+1 channel x - RO */
    ureg32 ATOM_IP1_OUT_N5:1;        /* [29:29] Output level snapshot of CCM_ATOM_OUT[x:x] of instance i+1 channel x - RO */
    ureg32 ATOM_IP1_OUT_N6:1;        /* [30:30] Output level snapshot of CCM_ATOM_OUT[x:x] of instance i+1 channel x - RO */
    ureg32 ATOM_IP1_OUT_N7:1;        /* [31:31] Output level snapshot of CCM_ATOM_OUT[x:x] of instance i+1 channel x - RO */
} GTM_CCM_ATOM_OUT_Bits;

/* CCM[i] CMU Clock Configuration Register */
typedef struct
{
    ureg32 CLK0_SRC:2;           /* [1:0] Clock [y] source signal selector - RW */
    ureg32 reserved_2:2;         /* [3:2] Internal  reserved */
    ureg32 CLK1_SRC:2;           /* [5:4] Clock [y] source signal selector - RW */
    ureg32 reserved_6:2;         /* [7:6] Internal  reserved */
    ureg32 CLK2_SRC:2;           /* [9:8] Clock [y] source signal selector - RW */
    ureg32 reserved_10:2;        /* [11:10] Internal  reserved */
    ureg32 CLK3_SRC:2;           /* [13:12] Clock [y] source signal selector - RW */
    ureg32 reserved_14:2;        /* [15:14] Internal  reserved */
    ureg32 CLK4_SRC:2;           /* [17:16] Clock [y] source signal selector - RW */
    ureg32 reserved_18:2;        /* [19:18] Internal  reserved */
    ureg32 CLK5_SRC:2;           /* [21:20] Clock [y] source signal selector - RW */
    ureg32 reserved_22:2;        /* [23:22] Internal  reserved */
    ureg32 CLK6_SRC:2;           /* [25:24] Clock [y] source signal selector - RW */
    ureg32 reserved_26:2;        /* [27:26] Internal  reserved */
    ureg32 CLK7_SRC:2;           /* [29:28] Clock [y] source signal selector - RW */
    ureg32 reserved_30:2;        /* [31:30] Internal  reserved */
} GTM_CCM_CMU_CLK_CFG_Bits;

/* CCM[i] CMU Fixed Clock Configuration Register */
typedef struct
{
    ureg32 FXCLK0_SRC:4;         /* [3:0] Fixed clock 0 source signal selector - RW */
    ureg32 reserved_4:28;        /* [31:4] Internal  reserved */
} GTM_CCM_CMU_FXCLK_CFG_Bits;

/* CCM[i] Configuration Register */
typedef struct
{
    ureg32 EN_TIM:1;                 /* [0:0] Enable TIM - RW */
    ureg32 EN_TOM_SPE_TDTM:1;        /* [1:1] Enable TOM - SPE and TDTM  - RW */
    ureg32 EN_ATOM_ADTM:1;           /* [2:2] Enable ATOM and ADTM  - RW */
    ureg32 EN_MCS:1;                 /* [3:3] Enable MCS  - RW */
    ureg32 EN_DPLL_MAP:1;            /* [4:4] Enable DPLL and MAP  - RW */
    ureg32 EN_BRC:1;                 /* [5:5] Enable BRC - RW */
    ureg32 EN_PSM:1;                 /* [6:6] Enable PSM  - RW */
    ureg32 EN_CMP_MON:1;             /* [7:7] Enable CMP and MON - RW */
    ureg32 EN_TIO_DTM:1;             /* [8:8] Enable TIO and connected DTM - RW */
    ureg32 reserved_9:7;             /* [15:9] Internal  reserved */
    ureg32 CLS_CLK_DIV:2;            /* [17:16] Cluster Clock Divider - RO */
    ureg32 reserved_18:12;           /* [29:18] Internal  reserved */
    ureg32 TBU_DIR1:1;               /* [30:30] DIR1 input signal of module TBU timebase [z]. - RO */
    ureg32 TBU_DIR2:1;               /* [31:31] DIR1 input signal of module TBU timebase [z]. - RO */
} GTM_CCM_CFG_Bits;

/* CCM[i] Protection Register */
typedef struct
{
    ureg32 CLS_PROT:1;           /* [0:0] Cluster Protection - RW */
    ureg32 reserved_1:31;        /* [31:1] Internal  reserved */
} GTM_CCM_PROT_Bits;

/* CDTM[i]_DTM[d] global configuration and control register */
typedef struct
{
    ureg32 CLK_SEL:2;              /* [1:0] Clock resolution selection - RW */
    ureg32 DTM_SEL:2;              /* [3:2] Select DTM update and PSU_SHUT_OFF reset signal - RW */
    ureg32 UPD_MODE:3;             /* [6:4] Update mode - RW */
    ureg32 CH_SHUTOFF_EN:1;        /* [7:7] Individual shutoff feature enable - RW */
    ureg32 SR_UPD_EN:1;            /* [8:8] Shadow register update enable  - RW */
    ureg32 reserved_9:7;           /* [15:9] Internal  reserved */
    ureg32 SHUT_OFF_RST:1;         /* [16:16] Shut off reset - RW */
    ureg32 reserved_17:15;         /* [31:17] Internal  reserved */
} GTM_CDTM_DTM_CTRL_Bits;

/* CDTM[i]_DTM[d] channel control register 1 */
typedef struct
{
    ureg32 O1SEL_0:1;            /* [0:0] Output 1 select channel 0 - RW */
    ureg32 I1SEL_0:1;            /* [1:1] Input 1 select channel 0 - RW */
    ureg32 reserved_2:1;         /* [2:2] Internal  reserved */
    ureg32 SWAP_0:1;             /* [3:3] Swap outputs DTM_OUT0[0:0] of instance d and DTM_OUT1[0:0] of instance d (before final output register) - RW */
    ureg32 O1F_0:2;              /* [5:4] Output 1 function channel 0 - RW */
    ureg32 XDT_EN_0_1:1;         /* [6:6] Cross dead time enable on channel 0 and 1 - RW */
    ureg32 reserved_7:1;         /* [7:7] Internal  reserved */
    ureg32 O1SEL_1:1;            /* [8:8] Output 1 select channel 1 - RW */
    ureg32 I1SEL_1:1;            /* [9:9] Input 1 select channel 1 - RW */
    ureg32 SH_EN_1:1;            /* [10:10] Shift enable channel 1 - RW */
    ureg32 SWAP_1:1;             /* [11:11] Swap outputs DTM_OUT0[1:1] of instance d and DTM_OUT1[1:1] of instance d (before final output register) - RW */
    ureg32 O1F_1:2;              /* [13:12] Output 1 function channel 1 - RW */
    ureg32 reserved_14:2;        /* [15:14] Internal  reserved */
    ureg32 O1SEL_2:1;            /* [16:16] Output 1 select channel 2 - RW */
    ureg32 I1SEL_2:1;            /* [17:17] Input 1 select channel 2 - RW */
    ureg32 SH_EN_2:1;            /* [18:18] Shift enable channel 2 - RW */
    ureg32 SWAP_2:1;             /* [19:19] Swap outputs DTM_OUT0[2:2] of instance d and DTM_OUT1[2:2] of instance d (before final output register) - RW */
    ureg32 O1F_2:2;              /* [21:20] Output 1 function channel 2 - RW */
    ureg32 XDT_EN_2_3:1;         /* [22:22] Cross dead time enable on channel 2 and 3 - RW */
    ureg32 reserved_23:1;        /* [23:23] Internal  reserved */
    ureg32 O1SEL_3:1;            /* [24:24] Output 1 select channel 3 - RW */
    ureg32 I1SEL_3:1;            /* [25:25] Input 1 select channel 3 - RW */
    ureg32 SH_EN_3:1;            /* [26:26] Shift enable channel 3 - RW */
    ureg32 SWAP_3:1;             /* [27:27] Swap outputs DTM_OUT0[3:3] of instance d and DTM_OUT1[3:3] of instance d (before final output register) - RW */
    ureg32 O1F_3:2;              /* [29:28] Output 1 function channel 3 - RW */
    ureg32 reserved_30:2;        /* [31:30] Internal  reserved */
} GTM_CDTM_DTM_CH_CTRL1_Bits;

/* CDTM[i]_DTM[d] channel control register 2 */
typedef struct
{
    ureg32 POL0_0:1;        /* [0:0] Polarity on output 0 channel 0 - RW */
    ureg32 OC0_0:1;         /* [1:1] Output 0 control channel 0 - RW */
    ureg32 SL0_0:1;         /* [2:2] Signal level on output 0 channel 0 - RW */
    ureg32 DT0_0:1;         /* [3:3] Dead time path enable on output 0 channel 0 - RW */
    ureg32 POL1_0:1;        /* [4:4] Polarity on output 1 channel 0 - RW */
    ureg32 OC1_0:1;         /* [5:5] Output 1 control channel 0 - RW */
    ureg32 SL1_0:1;         /* [6:6] Signal level on output 1 channel 0 - RW */
    ureg32 DT1_0:1;         /* [7:7] Dead time path enable on output 1 channel 0 - RW */
    ureg32 POL0_1:1;        /* [8:8] Polarity on output 0 channel 1 - RW */
    ureg32 OC0_1:1;         /* [9:9] Output 0 control channel 1 - RW */
    ureg32 SL0_1:1;         /* [10:10] Signal level on output 0 channel 1 - RW */
    ureg32 DT0_1:1;         /* [11:11] Dead time path enable on output 0 channel 1 - RW */
    ureg32 POL1_1:1;        /* [12:12] Polarity on output 1 channel 1 - RW */
    ureg32 OC1_1:1;         /* [13:13] Output 1 control channel 1 - RW */
    ureg32 SL1_1:1;         /* [14:14] Signal level on output 1 channel 1 - RW */
    ureg32 DT1_1:1;         /* [15:15] Dead time path enable on output 1 channel 1 - RW */
    ureg32 POL0_2:1;        /* [16:16] Polarity on output 0 channel 2 - RW */
    ureg32 OC0_2:1;         /* [17:17] Output 0 control channel 2 - RW */
    ureg32 SL0_2:1;         /* [18:18] Signal level on output 0 channel 2 - RW */
    ureg32 DT0_2:1;         /* [19:19] Dead time path enable on output 0 channel 2 - RW */
    ureg32 POL1_2:1;        /* [20:20] Polarity on output 1 channel 2 - RW */
    ureg32 OC1_2:1;         /* [21:21] Output 1 control channel 2 - RW */
    ureg32 SL1_2:1;         /* [22:22] Signal level on output 1 channel 2 - RW */
    ureg32 DT1_2:1;         /* [23:23] Dead time path enable on output 1 channel 2 - RW */
    ureg32 POL0_3:1;        /* [24:24] Polarity on output 0 channel 3 - RW */
    ureg32 OC0_3:1;         /* [25:25] Output 0 control channel 3 - RW */
    ureg32 SL0_3:1;         /* [26:26] Signal level on output 0 channel 3 - RW */
    ureg32 DT0_3:1;         /* [27:27] Dead time path enable on output 0 channel 3 - RW */
    ureg32 POL1_3:1;        /* [28:28] Polarity on output 1 channel 3 - RW */
    ureg32 OC1_3:1;         /* [29:29] Output 1 control channel 3 - RW */
    ureg32 SL1_3:1;         /* [30:30] Signal level on output 1 channel 3 - RW */
    ureg32 DT1_3:1;         /* [31:31] Dead time path enable on output 1 channel 3 - RW */
} GTM_CDTM_DTM_CH_CTRL2_Bits;

/* CDTM[i] DTM[j] channel control register 2 shadow */
typedef struct
{
    ureg32 POL0_0_SR:1;        /* [0:0] Polarity on output 0 channel 0 shadow register - RW */
    ureg32 OC0_0_SR:1;         /* [1:1] Output 0 control channel 0 shadow register - RW */
    ureg32 SL0_0_SR:1;         /* [2:2] Signal level on output 0 channel 0 shadow register - RW */
    ureg32 DT0_0_SR:1;         /* [3:3] Dead time path enable on output 0 channel 0 shadow register - RW */
    ureg32 POL1_0_SR:1;        /* [4:4] Polarity on output 1 channel 0 shadow register - RW */
    ureg32 OC1_0_SR:1;         /* [5:5] Output 1 control channel 0 shadow register - RW */
    ureg32 SL1_0_SR:1;         /* [6:6] Signal level on output 1 channel 0 shadow register - RW */
    ureg32 DT1_0_SR:1;         /* [7:7] Dead time path enable on output 1 channel 0 shadow register - RW */
    ureg32 POL0_1_SR:1;        /* [8:8] Polarity on output 0 channel 1 shadow register - RW */
    ureg32 OC0_1_SR:1;         /* [9:9] Output 0 control channel 1 shadow register - RW */
    ureg32 SL0_1_SR:1;         /* [10:10] Signal level on output 0 channel 1 shadow register - RW */
    ureg32 DT0_1_SR:1;         /* [11:11] Dead time path enable on output 0 channel 1 shadow register - RW */
    ureg32 POL1_1_SR:1;        /* [12:12] Polarity on output 1 channel 1 shadow register - RW */
    ureg32 OC1_1_SR:1;         /* [13:13] Output 1 control channel 1 shadow register - RW */
    ureg32 SL1_1_SR:1;         /* [14:14] Signal level on output 1 channel 1 shadow register - RW */
    ureg32 DT1_1_SR:1;         /* [15:15] Dead time path enable on output 1 channel 1 shadow register - RW */
    ureg32 POL0_2_SR:1;        /* [16:16] Polarity on output 0 channel 2 shadow register - RW */
    ureg32 OC0_2_SR:1;         /* [17:17] Output 0 control channel 2 shadow register - RW */
    ureg32 SL0_2_SR:1;         /* [18:18] Signal level on output 0 channel 2 shadow register - RW */
    ureg32 DT0_2_SR:1;         /* [19:19] Dead time path enable on output 0 channel 2 shadow register - RW */
    ureg32 POL1_2_SR:1;        /* [20:20] Polarity on output 1 channel 2 shadow register - RW */
    ureg32 OC1_2_SR:1;         /* [21:21] Output 1 control channel 2 shadow register - RW */
    ureg32 SL1_2_SR:1;         /* [22:22] Signal level on output 1 channel 2 shadow register - RW */
    ureg32 DT1_2_SR:1;         /* [23:23] Dead time path enable on output 1 channel 2 shadow register - RW */
    ureg32 POL0_3_SR:1;        /* [24:24] Polarity on output 0 channel 3 shadow register - RW */
    ureg32 OC0_3_SR:1;         /* [25:25] Output 0 control channel 3 shadow register - RW */
    ureg32 SL0_3_SR:1;         /* [26:26] Signal level on output 0 channel 3 shadow register - RW */
    ureg32 DT0_3_SR:1;         /* [27:27] Dead time path enable on output 0 channel 3 shadow register - RW */
    ureg32 POL1_3_SR:1;        /* [28:28] Polarity on output 1 channel 3 shadow register - RW */
    ureg32 OC1_3_SR:1;         /* [29:29] Output 1 control channel 3 shadow register - RW */
    ureg32 SL1_3_SR:1;         /* [30:30] Signal level on output 1 channel 3 shadow register - RW */
    ureg32 DT1_3_SR:1;         /* [31:31] Dead time path enable on output 1 channel 3 shadow register - RW */
} GTM_CDTM_DTM_CH_CTRL2_SR_Bits;

/* CDTM[i]_DTM[d] phase shift unit configuration and control register */
typedef struct
{
    ureg32 RELBLK:10;             /* [9:0] Reload value blanking window - RW */
    ureg32 reserved_10:6;         /* [15:10] Internal  reserved */
    ureg32 PSU_IN_SEL:1;          /* [16:16] PSU input select - RW */
    ureg32 IN_POL:1;              /* [17:17] Input polarity - RW */
    ureg32 TIM_SEL:1;             /* [18:18] TIM input select - RW */
    ureg32 reserved_19:1;         /* [19:19] Internal  reserved */
    ureg32 SHIFT_SEL:2;           /* [21:20] Shift select - RW */
    ureg32 reserved_22:10;        /* [31:22] Internal  reserved */
} GTM_CDTM_DTM_PS_CTRL_Bits;

/* CDTM[i]_DTM[d] channel [x] dead time reload values */
typedef struct
{
    ureg32 RELRISE:13;           /* [12:0] Reload value for rising edge dead time - RW */
    ureg32 reserved_13:3;        /* [15:13] Internal  reserved */
    ureg32 RELFALL:13;           /* [28:16] Reload value for falling edge dead time  - RW */
    ureg32 reserved_29:2;        /* [30:29] Internal  reserved */
    ureg32 HRES:1;               /* [31:31] high resolution PWM support - RW */
} GTM_CDTM_DTM_CH_DTV_Bits;

/* CDTM[i]_DTM[d] channel shadow register */
typedef struct
{
    ureg32 SL0_0_SR_SR:1;        /* [0:0] Shadow register for bit CDTM[i]_DTM[d]_CH_CTRL2_SR.SL0_0_SR - RW */
    ureg32 SL1_0_SR_SR:1;        /* [1:1] Shadow register for bit CDTM[i]_DTM[d]_CH_CTRL2_SR.SL1_0_SR - RW */
    ureg32 SL0_1_SR_SR:1;        /* [2:2] Shadow register for bit CDTM[i]_DTM[d]_CH_CTRL2_SR.SL0_1_SR - RW */
    ureg32 SL1_1_SR_SR:1;        /* [3:3] Shadow register for bit CDTM[i]_DTM[d]_CH_CTRL2_SR.SL1_1_SR - RW */
    ureg32 SL0_2_SR_SR:1;        /* [4:4] Shadow register for bit CDTM[i]_DTM[d]_CH_CTRL2_SR.SL0_2_SR - RW */
    ureg32 SL1_2_SR_SR:1;        /* [5:5] Shadow register for bit CDTM[i]_DTM[d]_CH_CTRL2_SR.SL1_2_SR - RW */
    ureg32 SL0_3_SR_SR:1;        /* [6:6] Shadow register for bit CDTM[i]_DTM[d]_CH_CTRL2_SR.SL0_3_SR - RW */
    ureg32 SL1_3_SR_SR:1;        /* [7:7] Shadow register for bit CDTM[i]_DTM[d]_CH_CTRL2_SR.SL1_3_SR - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_CDTM_DTM_CH_SR_Bits;

/* CDTM[i]_DTM[d] channel control register 3 */
typedef struct
{
    ureg32 CII0:1;               /* [0:0] Combinational input invert channel 0 - RW */
    ureg32 CIS0:1;               /* [1:1] Combinational input select channel 0 - RW */
    ureg32 TSEL0_0:1;            /* [2:2] Input selection for dead time / edge trigger generation - RW */
    ureg32 TSEL1_0:1;            /* [3:3] Input selection combinational logic path - RW */
    ureg32 reserved_4:4;         /* [7:4] Internal  reserved */
    ureg32 CII1:1;               /* [8:8] Combinational input invert channel 1 - RW */
    ureg32 CIS1:1;               /* [9:9] Combinational input select channel 1 - RW */
    ureg32 TSEL0_1:1;            /* [10:10] Input selection for dead time / edge trigger generation - RW */
    ureg32 TSEL1_1:1;            /* [11:11] Input selection combinational logic path - RW */
    ureg32 reserved_12:4;        /* [15:12] Internal  reserved */
    ureg32 CII2:1;               /* [16:16] Combinational input invert channel 2 - RW */
    ureg32 CIS2:1;               /* [17:17] Combinational input select channel 2 - RW */
    ureg32 TSEL0_2:1;            /* [18:18] Input selection for dead time / edge trigger generation - RW */
    ureg32 TSEL1_2:1;            /* [19:19] Input selection combinational logic path - RW */
    ureg32 reserved_20:4;        /* [23:20] Internal  reserved */
    ureg32 CII3:1;               /* [24:24] Combinational input invert channel 3 - RW */
    ureg32 CIS3:1;               /* [25:25] Combinational input select channel 3 - RW */
    ureg32 TSEL0_3:1;            /* [26:26] Input selection for dead time / edge trigger generation - RW */
    ureg32 TSEL1_3:1;            /* [27:27] Input selection combinational logic path - RW */
    ureg32 reserved_28:4;        /* [31:28] Internal  reserved */
} GTM_CDTM_DTM_CH_CTRL3_Bits;

/* CDTM[i]_DTM[d] global configuration and control register 2 */
typedef struct
{
    ureg32 SHUTOFF_SEL_0:3;         /* [2:0] Channel 0: Select input signal to be used as shut off signal. - RW */
    ureg32 SHUTOFF_POL_0:1;         /* [3:3] Channel 0: Configure if the selected shut off input signal used as shut off output signal is inverted or not. - RW */
    ureg32 UPD_MODE_0:2;            /* [5:4] Channel 0: Control the update mode of the internal SHUTOFF_SYNC_0 signal.  - RW */
    ureg32 SHUT_OFF_RST_0:1;        /* [6:6] Channel 0: Clear of internal signal SHUTOFF_SYNC_0 if selected as control source. - RW */
    ureg32 WR_EN_0:1;               /* [7:7] Channel 0: Write enable of Bitfields - RW */
    ureg32 SHUTOFF_SEL_1:3;         /* [10:8] Channel 1: Select input signal to be used as shut off signal. - RW */
    ureg32 SHUTOFF_POL_1:1;         /* [11:11] Channel 1: Configure if the selected shut off input signal used as shut off output signal is inverted or not. - RW */
    ureg32 UPD_MODE_1:2;            /* [13:12] Channel 1: Control the update mode of the internal SHUTOFF_SYNC_1 signal.  - RW */
    ureg32 SHUT_OFF_RST_1:1;        /* [14:14] Channel 1: Clear of internal signal SHUTOFF_SYNC_1 if selected as control source. - RW */
    ureg32 WR_EN_1:1;               /* [15:15] Channel 1: Write enable of Bitfields - RW */
    ureg32 SHUTOFF_SEL_2:3;         /* [18:16] Channel 2: Select input signal to be used as shut off signal. - RW */
    ureg32 SHUTOFF_POL_2:1;         /* [19:19] Channel 2: Configure if the selected shut off input signal used as shut off output signal is inverted or not. - RW */
    ureg32 UPD_MODE_2:2;            /* [21:20] Channel 2: Control the update mode of the internal SHUTOFF_SYNC_2 signal.  - RW */
    ureg32 SHUT_OFF_RST_2:1;        /* [22:22] Channel 2: Clear of internal signal SHUTOFF_SYNC_2 if selected as control source. - RW */
    ureg32 WR_EN_2:1;               /* [23:23] Channel 2: Write enable of Bitfields - RW */
    ureg32 SHUTOFF_SEL_3:3;         /* [26:24] Channel 3: Select input signal to be used as shut off signal. - RW */
    ureg32 SHUTOFF_POL_3:1;         /* [27:27] Channel 3: Configure if the selected shut off input signal used as shut off output signal is inverted or not. - RW */
    ureg32 UPD_MODE_3:2;            /* [29:28] Channel 3: Control the update mode of the internal SHUTOFF_SYNC_3 signal.  - RW */
    ureg32 SHUT_OFF_RST_3:1;        /* [30:30] Channel 3: Clear of internal signal SHUTOFF_SYNC_3 if selected as control source. - RW */
    ureg32 WR_EN_3:1;               /* [31:31] Channel 3: Write enable of Bitfields - RW */
} GTM_CDTM_DTM_CTRL2_Bits;

/* CDTM[i]_DTM[d] channel [x] dead time shadow values */
typedef struct
{
    ureg32 RELRISE_SR:13;               /* [12:0] Shadow value for rising edge dead time - RW */
    ureg32 reserved_13:1;               /* [13:13] Internal  reserved */
    ureg32 RELRISE_UPD_FE0RE1:1;        /* [14:14] Control if falling edge or rising edge triggers update of CDTM[i]_DTM[d]_CH[x]_DTV.RELRISE - RW */
    ureg32 RELRISE_UPD_EN:1;            /* [15:15] Control bit to enable update of CDTM[i]_DTM[d]_CH[x]_DTV.RELRISE - RW */
    ureg32 RELFALL_SR:13;               /* [28:16] Shadow value for falling edge dead time  - RW */
    ureg32 reserved_29:1;               /* [29:29] Internal  reserved */
    ureg32 RELFALL_UPD_FE0RE1:1;        /* [30:30] Control if falling edge or rising edge triggers update of CDTM[i]_DTM[d]_CH[x]_DTV.RELFALL - RW */
    ureg32 RELFALL_UPD_EN:1;            /* [31:31] Control bit to enable update of CDTM[i]_DTM[d]_CH[x]_DTV.RELFALL - RW */
} GTM_CDTM_DTM_CH_DTV_SR_Bits;

/* F2A[i] stream [x] ARU read register */
typedef struct
{
    ureg32 ADDR:9;               /* [8:0] ARU Read address - RW */
    ureg32 reserved_9:23;        /* [31:9] Internal  reserved */
} GTM_F2A_CH_ARU_RD_FIFO_Bits;

/* F2A[i] stream [x] configuration register */
typedef struct
{
    ureg32 reserved_0:16;         /* [15:0] Internal  reserved */
    ureg32 TMODE:2;               /* [17:16] Transfer mode for 53 bit ARU data from/to FIFO - RW */
    ureg32 DIR:1;                 /* [18:18] Data transfer direction - RW */
    ureg32 reserved_19:13;        /* [31:19] Internal  reserved */
} GTM_F2A_CH_STR_CFG_Bits;

/* F2A[i] stream activation register */
typedef struct
{
    ureg32 STR0_EN:2;             /* [1:0] Enable/disable stream [y] - RW */
    ureg32 STR1_EN:2;             /* [3:2] Enable/disable stream [y] - RW */
    ureg32 STR2_EN:2;             /* [5:4] Enable/disable stream [y] - RW */
    ureg32 STR3_EN:2;             /* [7:6] Enable/disable stream [y] - RW */
    ureg32 STR4_EN:2;             /* [9:8] Enable/disable stream [y] - RW */
    ureg32 STR5_EN:2;             /* [11:10] Enable/disable stream [y] - RW */
    ureg32 STR6_EN:2;             /* [13:12] Enable/disable stream [y] - RW */
    ureg32 STR7_EN:2;             /* [15:14] Enable/disable stream [y] - RW */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_F2A_ENABLE_Bits;

/* F2A[i] stream control register */
typedef struct
{
    ureg32 STR4_CONF:2;          /* [1:0] Reconfiguration of stream [y] to FIFO channel [y]-4 - RW */
    ureg32 STR5_CONF:2;          /* [3:2] Reconfiguration of stream [y] to FIFO channel [y]-4 - RW */
    ureg32 STR6_CONF:2;          /* [5:4] Reconfiguration of stream [y] to FIFO channel [y]-4 - RW */
    ureg32 STR7_CONF:2;          /* [7:6] Reconfiguration of stream [y] to FIFO channel [y]-4 - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_F2A_CTRL_Bits;

/* AFD [i] FIFO [x] buffer access register */
typedef struct
{
    ureg32 DATA:29;              /* [28:0] Read/write data from/to FIFO  - RW */
    ureg32 reserved_29:3;        /* [31:29] Internal  reserved */
} GTM_AFD_CH_BUF_ACC_Bits;

/* FIFO[i] channel [x] control register */
typedef struct
{
    ureg32 RBM:1;                /* [0:0] Ring buffer mode enable - RW */
    ureg32 RAP:1;                /* [1:1] RAM access priority - RW */
    ureg32 FLUSH:1;              /* [2:2] FIFO flush control - RW */
    ureg32 WULOCK:1;             /* [3:3] RAM write unlock. Enable/disable direct RAM write access to the memory mapped FIFO region. - RW */
    ureg32 reserved_4:28;        /* [31:4] Internal  reserved */
} GTM_FIFO_CH_CTRL_Bits;

/* FIFO[i] channel [x] end address register */
typedef struct
{
    ureg32 ADDR:10;               /* [9:0] End address for FIFO channel [x] - RW */
    ureg32 reserved_10:22;        /* [31:10] Internal  reserved */
} GTM_FIFO_CH_END_ADDR_Bits;

/* FIFO[i] channel [x] start address register */
typedef struct
{
    ureg32 ADDR:10;               /* [9:0] Start address for FIFO channel [x] - RW */
    ureg32 reserved_10:22;        /* [31:10] Internal  reserved */
} GTM_FIFO_CH_START_ADDR_Bits;

/* FIFO[i] channel [x] upper watermark register */
typedef struct
{
    ureg32 ADDR:10;               /* [9:0] Upper watermark address - RW */
    ureg32 reserved_10:22;        /* [31:10] Internal  reserved */
} GTM_FIFO_CH_UPPER_WM_Bits;

/* FIFO[i] channel [x] lower watermark register */
typedef struct
{
    ureg32 ADDR:10;               /* [9:0] Lower watermark address - RW */
    ureg32 reserved_10:22;        /* [31:10] Internal  reserved */
} GTM_FIFO_CH_LOWER_WM_Bits;

/* FIFO[i] channel [x] status register */
typedef struct
{
    ureg32 EMPTY:1;              /* [0:0] FIFO is empty - RO */
    ureg32 FULL:1;               /* [1:1] FIFO is full - RO */
    ureg32 LOW_WM:1;             /* [2:2] Lower watermark reached - RO */
    ureg32 UP_WM:1;              /* [3:3] Upper watermark reached - RO */
    ureg32 reserved_4:28;        /* [31:4] Internal  reserved */
} GTM_FIFO_CH_STATUS_Bits;

/* FIFO[i] channel [x] fill level register */
typedef struct
{
    ureg32 LEVEL:11;              /* [10:0] Fill level of the current FIFO - RO */
    ureg32 reserved_11:21;        /* [31:11] Internal  reserved */
} GTM_FIFO_CH_FILL_LEVEL_Bits;

/* FIFO[i] channel [x] write pointer register */
typedef struct
{
    ureg32 ADDR:10;               /* [9:0] Position of the write pointer - RO */
    ureg32 reserved_10:22;        /* [31:10] Internal  reserved */
} GTM_FIFO_CH_WR_PTR_Bits;

/* FIFO[i] channel [x] read pointer register */
typedef struct
{
    ureg32 ADDR:10;               /* [9:0] Position of the read pointer - RO */
    ureg32 reserved_10:22;        /* [31:10] Internal  reserved */
} GTM_FIFO_CH_RD_PTR_Bits;

/* FIFO[i] channel [x] interrupt notification register */
typedef struct
{
    ureg32 FIFO_EMPTY:1;         /* [0:0] FIFO is empty - RW */
    ureg32 FIFO_FULL:1;          /* [1:1] FIFO is full - RW */
    ureg32 FIFO_LWM:1;           /* [2:2] FIFO Lower watermark was under-run - RW */
    ureg32 FIFO_UWM:1;           /* [3:3] FIFO Upper watermark was overrun - RW */
    ureg32 reserved_4:28;        /* [31:4] Internal  reserved */
} GTM_FIFO_CH_IRQ_NOTIFY_Bits;

/* FIFO[i] channel [x] interrupt enable register */
typedef struct
{
    ureg32 FIFO_EMPTY_IRQ_EN:1;        /* [0:0] Interrupt enable - RW */
    ureg32 FIFO_FULL_IRQ_EN:1;         /* [1:1] Interrupt enable - RW */
    ureg32 FIFO_LWM_IRQ_EN:1;          /* [2:2] Interrupt enable - RW */
    ureg32 FIFO_UWM_IRQ_EN:1;          /* [3:3] Interrupt enable - RW */
    ureg32 reserved_4:28;              /* [31:4] Internal  reserved */
} GTM_FIFO_CH_IRQ_EN_Bits;

/* FIFO[i] channel [x] force interrupt register */
typedef struct
{
    ureg32 TRG_FIFO_EMPTY:1;        /* [0:0] Trigger the bit XXX by software FIFO[i]_CH[x]_IRQ_NOTIFY.FIFO_EMPTY by software - RW */
    ureg32 TRG_FIFO_FULL:1;         /* [1:1] Trigger the bit XXX by software FIFO[i]_CH[x]_IRQ_NOTIFY.FIFO_FULL by software - RW */
    ureg32 TRG_FIFO_LWM:1;          /* [2:2] Trigger the bit XXX by software FIFO[i]_CH[x]_IRQ_NOTIFY.FIFO_LWM by software - RW */
    ureg32 TRG_FIFO_UWM:1;          /* [3:3] Trigger the bit XXX by software FIFO[i]_CH[x]_IRQ_NOTIFY.FIFO_UWM by software - RW */
    ureg32 reserved_4:28;           /* [31:4] Internal  reserved */
} GTM_FIFO_CH_IRQ_FORCINT_Bits;

/* FIFO[i] channel [x] interrupt mode control register */
typedef struct
{
    ureg32 IRQ_MODE:2;              /* [1:0] IRQ mode selection - RW */
    ureg32 DMA_HYSTERESIS:1;        /* [2:2] Enable DMA hysteresis mode - RW */
    ureg32 DMA_HYST_DIR:1;          /* [3:3] DMA direction in hysteresis mode - RW */
    ureg32 reserved_4:28;           /* [31:4] Internal  reserved */
} GTM_FIFO_CH_IRQ_MODE_Bits;

/* FIFO[i] channel [x] error interrupt enable register */
typedef struct
{
    ureg32 FIFO_EMPTY_EIRQ_EN:1;        /* [0:0] Error interrupt enable - RW */
    ureg32 FIFO_FULL_EIRQ_EN:1;         /* [1:1] Interrupt enable - RW */
    ureg32 FIFO_LWM_EIRQ_EN:1;          /* [2:2] Interrupt enable - RW */
    ureg32 FIFO_UWM_EIRQ_EN:1;          /* [3:3] Interrupt enable - RW */
    ureg32 reserved_4:28;               /* [31:4] Internal  reserved */
} GTM_FIFO_CH_EIRQ_EN_Bits;

/* SPE[i] Control Status Register */
typedef struct
{
    ureg32 EN:1;                 /* [0:0] SPE Submodule enable - RW */
    ureg32 SIE0:1;               /* [1:1] SPE Input [k] enable for TIM[i]_CH[x:x] - TIM[i]_CH[y:y] - TIM[i]_CH[z:z]. - RW */
    ureg32 SIE1:1;               /* [2:2] SPE Input [k] enable for TIM[i]_CH[x:x] - TIM[i]_CH[y:y] - TIM[i]_CH[z:z]. - RW */
    ureg32 SIE2:1;               /* [3:3] SPE Input [k] enable for TIM[i]_CH[x:x] - TIM[i]_CH[y:y] - TIM[i]_CH[z:z]. - RW */
    ureg32 TRIG_SEL:2;           /* [5:4] Select trigger input signal - RW */
    ureg32 TIM_SEL:1;            /* [6:6] Select TIM input signal - RW */
    ureg32 FSOM:1;               /* [7:7] Fast Shutoff Mode - RW */
    ureg32 SPE_PAT_PTR:3;        /* [10:8] Pattern selector for TOM output signals. - RW */
    ureg32 reserved_11:1;        /* [11:11] Internal  reserved */
    ureg32 AIP:3;                /* [14:12] Input pattern that was detected by a regular input pattern change. - RW */
    ureg32 ADIR:1;               /* [15:15] Rotation direction. Will be reflected in the signal SPE[i]_DIR. - RW */
    ureg32 PIP:3;                /* [18:16] Previous input pattern that was detected by a regular input pattern change. - RW */
    ureg32 PDIR:1;               /* [19:19] Previous rotation direction - RW */
    ureg32 NIP:3;                /* [22:20] New input pattern that was detected. - RO */
    ureg32 ETRIG_SEL:1;          /* [23:23] Extended trigger selection of signal TRIG_SEL - RW */
    ureg32 FSOL:8;               /* [31:24] Fast Shutoff Level for TOM[i] channel 0 to 7 - RW */
} GTM_SPE_CTRL_STAT_Bits;

/* SPE[i] Input Pattern Definition Register */
typedef struct
{
    ureg32 IP0_VAL:1;        /* [0:0] Input pattern [t] is a valid pattern. - RW */
    ureg32 IP0_PAT:3;        /* [3:1] Input pattern [t] - RW */
    ureg32 IP1_VAL:1;        /* [4:4] Input pattern [t] is a valid pattern. - RW */
    ureg32 IP1_PAT:3;        /* [7:5] Input pattern [t] - RW */
    ureg32 IP2_VAL:1;        /* [8:8] Input pattern [t] is a valid pattern. - RW */
    ureg32 IP2_PAT:3;        /* [11:9] Input pattern [t] - RW */
    ureg32 IP3_VAL:1;        /* [12:12] Input pattern [t] is a valid pattern. - RW */
    ureg32 IP3_PAT:3;        /* [15:13] Input pattern [t] - RW */
    ureg32 IP4_VAL:1;        /* [16:16] Input pattern [t] is a valid pattern. - RW */
    ureg32 IP4_PAT:3;        /* [19:17] Input pattern [t] - RW */
    ureg32 IP5_VAL:1;        /* [20:20] Input pattern [t] is a valid pattern. - RW */
    ureg32 IP5_PAT:3;        /* [23:21] Input pattern [t] - RW */
    ureg32 IP6_VAL:1;        /* [24:24] Input pattern [t] is a valid pattern. - RW */
    ureg32 IP6_PAT:3;        /* [27:25] Input pattern [t] - RW */
    ureg32 IP7_VAL:1;        /* [28:28] Input pattern [t] is a valid pattern. - RW */
    ureg32 IP7_PAT:3;        /* [31:29] Input pattern [t] - RW */
} GTM_SPE_PAT_Bits;

/* SPE[i] Output Definition Register */
typedef struct
{
    ureg32 SPE_OUT_PAT0:2;        /* [1:0] SPE output control value for TOM channel0 to TOM channel7 - RW */
    ureg32 SPE_OUT_PAT1:2;        /* [3:2] SPE output control value for TOM channel0 to TOM channel7 - RW */
    ureg32 SPE_OUT_PAT2:2;        /* [5:4] SPE output control value for TOM channel0 to TOM channel7 - RW */
    ureg32 SPE_OUT_PAT3:2;        /* [7:6] SPE output control value for TOM channel0 to TOM channel7 - RW */
    ureg32 SPE_OUT_PAT4:2;        /* [9:8] SPE output control value for TOM channel0 to TOM channel7 - RW */
    ureg32 SPE_OUT_PAT5:2;        /* [11:10] SPE output control value for TOM channel0 to TOM channel7 - RW */
    ureg32 SPE_OUT_PAT6:2;        /* [13:12] SPE output control value for TOM channel0 to TOM channel7 - RW */
    ureg32 SPE_OUT_PAT7:2;        /* [15:14] SPE output control value for TOM channel0 to TOM channel7 - RW */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_SPE_OUT_PAT_Bits;

/* SPE[i] Output Control Register */
typedef struct
{
    ureg32 SPE_OUT_CTRL0:2;        /* [1:0] SPE output control value for TOM channel0 to TOM channel7 - RW */
    ureg32 SPE_OUT_CTRL1:2;        /* [3:2] SPE output control value for TOM channel0 to TOM channel7 - RW */
    ureg32 SPE_OUT_CTRL2:2;        /* [5:4] SPE output control value for TOM channel0 to TOM channel7 - RW */
    ureg32 SPE_OUT_CTRL3:2;        /* [7:6] SPE output control value for TOM channel0 to TOM channel7 - RW */
    ureg32 SPE_OUT_CTRL4:2;        /* [9:8] SPE output control value for TOM channel0 to TOM channel7 - RW */
    ureg32 SPE_OUT_CTRL5:2;        /* [11:10] SPE output control value for TOM channel0 to TOM channel7 - RW */
    ureg32 SPE_OUT_CTRL6:2;        /* [13:12] SPE output control value for TOM channel0 to TOM channel7 - RW */
    ureg32 SPE_OUT_CTRL7:2;        /* [15:14] SPE output control value for TOM channel0 to TOM channel7 - RW */
    ureg32 reserved_16:16;         /* [31:16] Internal  reserved */
} GTM_SPE_OUT_CTRL_Bits;

/* SPE[i] Interrupt Notification Register */
typedef struct
{
    ureg32 SPE_NIPD:1;           /* [0:0] New input pattern interrupt occurred - RW */
    ureg32 SPE_DCHG:1;           /* [1:1] SPE_DIR bit changed on behalf of new input pattern. - RW */
    ureg32 SPE_PERR:1;           /* [2:2] Wrong or invalid pattern detected at input. - RW */
    ureg32 SPE_BIS:1;            /* [3:3] Bouncing input signal detected - RW */
    ureg32 SPE_RCMP:1;           /* [4:4] SPE revolution counter match event - RW */
    ureg32 reserved_5:27;        /* [31:5] Internal  reserved */
} GTM_SPE_IRQ_NOTIFY_Bits;

/* SPE[i] Interrupt Enable Register */
typedef struct
{
    ureg32 SPE_NIPD_IRQ_EN:1;        /* [0:0] SPE_NIPD_IRQ interrupt enable - RW */
    ureg32 SPE_DCHG_IRQ_EN:1;        /* [1:1] SPE_DCHG_IRQ interrupt enable - RW */
    ureg32 SPE_PERR_IRQ_EN:1;        /* [2:2] SPE_PERR_IRQ interrupt enable - RW */
    ureg32 SPE_BIS_IRQ_EN:1;         /* [3:3] SPE_BIS_IRQ interrupt enable - RW */
    ureg32 SPE_RCMP_IRQ_EN:1;        /* [4:4] SPE_RCMP_IRQ interrupt enable - RW */
    ureg32 reserved_5:27;            /* [31:5] Internal  reserved */
} GTM_SPE_IRQ_EN_Bits;

/* SPE[i] Interrupt Generation By Software */
typedef struct
{
    ureg32 TRG_SPE_NIPD:1;        /* [0:0] Trigger SPE[i]_IRQ_NOTIFY.SPE_NIPD by software - RW */
    ureg32 TRG_SPE_DCHG:1;        /* [1:1] Trigger SPE[i]_IRQ_NOTIFY.SPE_DCHG by software. - RW */
    ureg32 TRG_SPE_PERR:1;        /* [2:2] Trigger SPE[i]_IRQ_NOTIFY.SPE_PERR by software. - RW */
    ureg32 TRG_SPE_BIS:1;         /* [3:3] Trigger SPE[i]_IRQ_NOTIFY.SPE_BIS by software. - RW */
    ureg32 TRG_SPE_RCMP:1;        /* [4:4] Trigger SPE[i]_IRQ_NOTIFY.SPE_RCMP by software. - RW */
    ureg32 reserved_5:27;         /* [31:5] Internal  reserved */
} GTM_SPE_IRQ_FORCINT_Bits;

/* SPE[i] Interrupt Mode Configuration Register */
typedef struct
{
    ureg32 IRQ_MODE:2;           /* [1:0] IRQ mode selection - RW */
    ureg32 reserved_2:30;        /* [31:2] Internal  reserved */
} GTM_SPE_IRQ_MODE_Bits;

/* SPE[i] Error Interrupt Enable Register */
typedef struct
{
    ureg32 SPE_NIPD_EIRQ_EN:1;        /* [0:0] SPE_NIPD_EIRQ interrupt enable - RW */
    ureg32 SPE_DCHG_EIRQ_EN:1;        /* [1:1] SPE_DCHG_EIRQ error interrupt enable - RW */
    ureg32 SPE_PERR_EIRQ_EN:1;        /* [2:2] SPE_PERR_EIRQ error interrupt enable - RW */
    ureg32 SPE_BIS_EIRQ_EN:1;         /* [3:3] SPE[i]_BIS_EIRQ error interrupt enable - RW */
    ureg32 SPE_RCMP_EIRQ_EN:1;        /* [4:4] SPE[i]_RCMP_EIRQ error interrupt enable - RW */
    ureg32 reserved_5:27;             /* [31:5] Internal  reserved */
} GTM_SPE_EIRQ_EN_Bits;

/* SPE[i] Input Revolution Counter */
typedef struct
{
    ureg32 REV_CNT:24;           /* [23:0] Input signal revolution counter - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_SPE_REV_CNT_Bits;

/* SPE[i] Revolution Counter Compare Value */
typedef struct
{
    ureg32 REV_CMP:24;           /* [23:0] Input signal revolution counter compare value - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_SPE_REV_CMP_Bits;

/* SPE[i] Control Status Register 2 */
typedef struct
{
    ureg32 reserved_0:8;             /* [7:0] Internal  reserved */
    ureg32 SPE_PAT_PTR_BWD:3;        /* [10:8] Pattern selector for TOM output signals in case of SPE[i]_CMD.SPE_CTRL_CMD = 0b01 (e.g. backward direction). - RW */
    ureg32 reserved_11:21;           /* [31:11] Internal  reserved */
} GTM_SPE_CTRL_STAT2_Bits;

/* SPE[i] Command Register */
typedef struct
{
    ureg32 SPE_CTRL_CMD:2;        /* [1:0] SPE control command - RW */
    ureg32 reserved_2:14;         /* [15:2] Internal  reserved */
    ureg32 SPE_UPD_TRIG:1;        /* [16:16] SPE updater trigger - RW */
    ureg32 reserved_17:15;        /* [31:17] Internal  reserved */
} GTM_SPE_CMD_Bits;

/* AXIM[i] slot allocation status. */
typedef struct
{
    ureg32 FREE0:1;              /* [0:0] This bit represents the allocation status of the slot [t]. - RO */
    ureg32 FREE1:1;              /* [1:1] This bit represents the allocation status of the slot [t]. - RO */
    ureg32 FREE2:1;              /* [2:2] This bit represents the allocation status of the slot [t]. - RO */
    ureg32 FREE3:1;              /* [3:3] This bit represents the allocation status of the slot [t]. - RO */
    ureg32 reserved_4:28;        /* [31:4] Internal  reserved */
} GTM_AXIM_FREE_Bits;

/* AXIM[i] slot request (allocation). */
typedef struct
{
    ureg32 REQ1HOT0:1;           /* [0:0] A read to the AXIM[i]_REQUEST register will allocate a new slot if any slot is available. This bit field shows the new allocated slot as 1-hot encoded vector. If no slot could be allocated - this bit field is read as all 0. - RO */
    ureg32 REQ1HOT1:1;           /* [1:1] A read to the AXIM[i]_REQUEST register will allocate a new slot if any slot is available. This bit field shows the new allocated slot as 1-hot encoded vector. If no slot could be allocated - this bit field is read as all 0. - RO */
    ureg32 REQ1HOT2:1;           /* [2:2] A read to the AXIM[i]_REQUEST register will allocate a new slot if any slot is available. This bit field shows the new allocated slot as 1-hot encoded vector. If no slot could be allocated - this bit field is read as all 0. - RO */
    ureg32 REQ1HOT3:1;           /* [3:3] A read to the AXIM[i]_REQUEST register will allocate a new slot if any slot is available. This bit field shows the new allocated slot as 1-hot encoded vector. If no slot could be allocated - this bit field is read as all 0. - RO */
    ureg32 reserved_4:20;        /* [23:4] Internal  reserved */
    ureg32 REQID:8;              /* [31:24] This bit field shows the new allocated slot as binary encoded index. If no slot could be allocated - this bit field is read as all 1 (0xff). - RO */
} GTM_AXIM_REQUEST_Bits;

/* AXIM[i] slot release (de-allocation). */
typedef struct
{
    ureg32 RELREQ0:1;            /* [0:0] Slot [t] release request: A write to AXIM[i]_RELEASE.RELREQ[t] de-allocates one or more slots. Each bit in AXIM[i]_RELEASE.RELREQ[t] represents one slot. - RW */
    ureg32 RELREQ1:1;            /* [1:1] Slot [t] release request: A write to AXIM[i]_RELEASE.RELREQ[t] de-allocates one or more slots. Each bit in AXIM[i]_RELEASE.RELREQ[t] represents one slot. - RW */
    ureg32 RELREQ2:1;            /* [2:2] Slot [t] release request: A write to AXIM[i]_RELEASE.RELREQ[t] de-allocates one or more slots. Each bit in AXIM[i]_RELEASE.RELREQ[t] represents one slot. - RW */
    ureg32 RELREQ3:1;            /* [3:3] Slot [t] release request: A write to AXIM[i]_RELEASE.RELREQ[t] de-allocates one or more slots. Each bit in AXIM[i]_RELEASE.RELREQ[t] represents one slot. - RW */
    ureg32 reserved_4:28;        /* [31:4] Internal  reserved */
} GTM_AXIM_RELEASE_Bits;

/* AXIM[i] slot[s] address bits 31:0 of AXI transaction. */
typedef struct
{
    ureg32 AXI_ADDR:32;        /* [31:0] Address for the AXI transaction.  - RW */
} GTM_AXIM_SLOT_ADDR_LOW_Bits;

/* AXIM[i] slot[s] data bits 31:0 of AXI transaction. */
typedef struct
{
    ureg32 AXI_DATA_LOW:32;        /* [31:0] Read or write data. - RW */
} GTM_AXIM_SLOT_DATA_LOW_Bits;

/* AXIM[i] slot [s] configuration 1 */
typedef struct
{
    ureg32 INCR:4;               /* [3:0] Address increment for auto-increment mode - RW */
    ureg32 AUTO_INCR:1;          /* [4:4] Enable or disable auto-increment mode - RW */
    ureg32 PRIO:2;               /* [6:5] Slot priority. Priority used for slot arbitration. Lowest priority is 0 - highest priority is 3. - RW */
    ureg32 reserved_7:4;         /* [10:7] Internal  reserved */
    ureg32 AXI_PROT:3;           /* [13:11] AXI priority mode - RW */
    ureg32 AXI_CACHE:4;          /* [17:14] AxCACHE bit field (see ARM AXI-3 spec) - RW */
    ureg32 AXI_LOCK:2;           /* [19:18] AXI Lock indication - RW */
    ureg32 reserved_20:2;        /* [21:20] Internal  reserved */
    ureg32 AXI_SIZE:3;           /* [24:22] AXI data size - RW */
    ureg32 AXI_RW:1;             /* [25:25] AXI Read Write indication - RW */
    ureg32 reserved_26:6;        /* [31:26] Internal  reserved */
} GTM_AXIM_SLOT_CFG1_Bits;

/* AXIM[i] slot[s] configuration 2 */
typedef struct
{
    ureg32 AXI_ID:16;             /* [15:0] AXI ID for transaction. If posted writes are enabled (device configuration variable) - the lower bit of the AXIM[i]_SLOT[s]_CFG2.AXI_ID selects between posted and none-posted writes. - RW */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_AXIM_SLOT_CFG2_Bits;

/* AXIM[i] slot[s] status */
typedef struct
{
    ureg32 ALLOC:1;              /* [0:0] AXI Slot occupation indication - RO */
    ureg32 QUEUED:1;             /* [1:1] This bit represents the slot AXIM[i]_SLOT[s]_STATUS.QUEUED state. - RO */
    ureg32 STARTED:1;            /* [2:2] This bit represents the slot AXIM[i]_SLOT[s]_STATUS.STARTED state. - RO */
    ureg32 READY:1;              /* [3:3] This bit represents the slot AXIM[i]_SLOT[s]_STATUS.READY state. - RO */
    ureg32 RESP:2;               /* [5:4] AXI response from last AXI transaction - RO */
    ureg32 reserved_6:26;        /* [31:6] Internal  reserved */
} GTM_AXIM_SLOT_STATUS_Bits;

/* FIFO data memory */
typedef struct
{
    ureg32 DATA:29;              /* [28:0] FIFO memory location - RW */
    ureg32 reserved_29:3;        /* [31:29] Internal  reserved */
} GTM_FIFO_MEMORY_Bits;

/* Control Register 0 */
typedef struct
{
    ureg32 MLT:10;        /* [9:0] Multiplier for TRIGGER. - RW */
    ureg32 IFP:1;         /* [10:10] Input filter position. - RW */
    ureg32 SNU:5;         /* [15:11] STATE number. - RW */
    ureg32 TNU:9;         /* [24:16] TRIGGER number. - RW */
    ureg32 AMS:1;         /* [25:25] Adapt mode STATE. - RW */
    ureg32 AMT:1;         /* [26:26] Adapt mode TRIGGER. - RW */
    ureg32 IDS:1;         /* [27:27] Input delay STATE. - RW */
    ureg32 IDT:1;         /* [28:28] Input delay TRIGGER. - RW */
    ureg32 SEN:1;         /* [29:29] STATE enable. - RW */
    ureg32 TEN:1;         /* [30:30] TRIGGER enable. - RW */
    ureg32 RMO:1;         /* [31:31] Reference mode. - RW */
} GTM_DPLL_CTRL_0_Bits;

/* Control Register 1 */
typedef struct
{
    ureg32 DMO:1;            /* [0:0] DPLL mode select. - RW */
    ureg32 DEN:1;            /* [1:1] DPLL enable. - RW */
    ureg32 IDDS:1;           /* [2:2] Input direction detection strategy in the case of DPLL_CTRL_1.SMC=0. - RW */
    ureg32 COA:1;            /* [3:3] Correction strategy in automatic end mode (DPLL_CTRL_1.DMO=0). - RW */
    ureg32 PIT:1;            /* [4:4] Plausibility value DPLL_PVT.PVT to next active TRIGGER is time related. - RW */
    ureg32 SGE1:1;           /* [5:5] SUB_INC1 generator enable. - RW */
    ureg32 DLM1:1;           /* [6:6] Direct Load Mode for SUB_INC1 generation. - RW */
    ureg32 PCM1:1;           /* [7:7] Pulse Correction Mode for SUB_INC1 generation. - RW */
    ureg32 SGE2:1;           /* [8:8] SUB_INC2 generator enable. - RW */
    ureg32 DLM2:1;           /* [9:9] Direct Load Mode for SUB_INC2 generation. - RW */
    ureg32 PCM2:1;           /* [10:10] Pulse Correction Mode for SUB_INC2 generation. - RW */
    ureg32 SYN_NS:5;         /* [15:11] Synchronization number of DPLL STATE events. summarized number of virtual increments in Half Scale Mode. - RW */
    ureg32 SYN_NT:6;         /* [21:16] Synchronization number of DPLL TRIGGER events. summarized number of virtual increments in Half Scale Mode. - RW */
    ureg32 LCD:1;            /* [22:22] Locking condition definition - RW */
    ureg32 SWR:1;            /* [23:23] Software reset - RW */
    ureg32 SYSF:1;           /* [24:24] DPLL_CTRL_EXT.SYN_NS for FULL_SCALE  - RW */
    ureg32 TS0_HRS:1;        /* [25:25] Time stamp high resolution STATE  - RW */
    ureg32 TS0_HRT:1;        /* [26:26] Time stamp high resolution TRIGGER  - RW */
    ureg32 SMC:1;            /* [27:27] Synchronous Motor Control - RW */
    ureg32 SSL:2;            /* [29:28] State slope select  - RW */
    ureg32 TSL:2;            /* [31:30] Trigger slope select - RW */
} GTM_DPLL_CTRL_1_Bits;

/* Action Enable Register  */
typedef struct
{
    ureg32 reserved_0:8;         /* [7:0] Internal  reserved */
    ureg32 AEN0:1;               /* [8:8] Action [n] enable. - RW */
    ureg32 AEN1:1;               /* [9:9] Action [n] enable. - RW */
    ureg32 AEN2:1;               /* [10:10] Action [n] enable. - RW */
    ureg32 AEN3:1;               /* [11:11] Action [n] enable. - RW */
    ureg32 AEN4:1;               /* [12:12] Action [n] enable. - RW */
    ureg32 AEN5:1;               /* [13:13] Action [n] enable. - RW */
    ureg32 AEN6:1;               /* [14:14] Action [n] enable. - RW */
    ureg32 AEN7:1;               /* [15:15] Action [n] enable. - RW */
    ureg32 WAD0:1;               /* [16:16] Write control bit of Action [m]. - RW */
    ureg32 WAD1:1;               /* [17:17] Write control bit of Action [m]. - RW */
    ureg32 WAD2:1;               /* [18:18] Write control bit of Action [m]. - RW */
    ureg32 WAD3:1;               /* [19:19] Write control bit of Action [m]. - RW */
    ureg32 WAD4:1;               /* [20:20] Write control bit of Action [m]. - RW */
    ureg32 WAD5:1;               /* [21:21] Write control bit of Action [m]. - RW */
    ureg32 WAD6:1;               /* [22:22] Write control bit of Action [m]. - RW */
    ureg32 WAD7:1;               /* [23:23] Write control bit of Action [m]. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_CTRL_2_Bits;

/* Action Enable Register */
typedef struct
{
    ureg32 reserved_0:8;         /* [7:0] Internal  reserved */
    ureg32 AEN8:1;               /* [8:8] Action [n] enable. - RW */
    ureg32 AEN9:1;               /* [9:9] Action [n] enable. - RW */
    ureg32 AEN10:1;              /* [10:10] Action [n] enable. - RW */
    ureg32 AEN11:1;              /* [11:11] Action [n] enable. - RW */
    ureg32 AEN12:1;              /* [12:12] Action [n] enable. - RW */
    ureg32 AEN13:1;              /* [13:13] Action [n] enable. - RW */
    ureg32 AEN14:1;              /* [14:14] Action [n] enable. - RW */
    ureg32 AEN15:1;              /* [15:15] Action [n] enable. - RW */
    ureg32 WAD8:1;               /* [16:16] Write control bit of Action [m]. - RW */
    ureg32 WAD9:1;               /* [17:17] Write control bit of Action [m]. - RW */
    ureg32 WAD10:1;              /* [18:18] Write control bit of Action [m]. - RW */
    ureg32 WAD11:1;              /* [19:19] Write control bit of Action [m]. - RW */
    ureg32 WAD12:1;              /* [20:20] Write control bit of Action [m]. - RW */
    ureg32 WAD13:1;              /* [21:21] Write control bit of Action [m]. - RW */
    ureg32 WAD14:1;              /* [22:22] Write control bit of Action [m]. - RW */
    ureg32 WAD15:1;              /* [23:23] Write control bit of Action [m]. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_CTRL_3_Bits;

/* Action Enable Register */
typedef struct
{
    ureg32 reserved_0:8;         /* [7:0] Internal  reserved */
    ureg32 AEN16:1;              /* [8:8] Action [n] enable. - RW */
    ureg32 AEN17:1;              /* [9:9] Action [n] enable. - RW */
    ureg32 AEN18:1;              /* [10:10] Action [n] enable. - RW */
    ureg32 AEN19:1;              /* [11:11] Action [n] enable. - RW */
    ureg32 AEN20:1;              /* [12:12] Action [n] enable. - RW */
    ureg32 AEN21:1;              /* [13:13] Action [n] enable. - RW */
    ureg32 AEN22:1;              /* [14:14] Action [n] enable. - RW */
    ureg32 AEN23:1;              /* [15:15] Action [n] enable. - RW */
    ureg32 WAD16:1;              /* [16:16] Write control bit of Action [m]. - RW */
    ureg32 WAD17:1;              /* [17:17] Write control bit of Action [m]. - RW */
    ureg32 WAD18:1;              /* [18:18] Write control bit of Action [m]. - RW */
    ureg32 WAD19:1;              /* [19:19] Write control bit of Action [m]. - RW */
    ureg32 WAD20:1;              /* [20:20] Write control bit of Action [m]. - RW */
    ureg32 WAD21:1;              /* [21:21] Write control bit of Action [m]. - RW */
    ureg32 WAD22:1;              /* [22:22] Write control bit of Action [m]. - RW */
    ureg32 WAD23:1;              /* [23:23] Write control bit of Action [m]. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_CTRL_4_Bits;

/* Action Enable Register */
typedef struct
{
    ureg32 reserved_0:8;         /* [7:0] Internal  reserved */
    ureg32 AEN24:1;              /* [8:8] Action [n] enable. - RW */
    ureg32 AEN25:1;              /* [9:9] Action [n] enable. - RW */
    ureg32 AEN26:1;              /* [10:10] Action [n] enable. - RW */
    ureg32 AEN27:1;              /* [11:11] Action [n] enable. - RW */
    ureg32 AEN28:1;              /* [12:12] Action [n] enable. - RW */
    ureg32 AEN29:1;              /* [13:13] Action [n] enable. - RW */
    ureg32 AEN30:1;              /* [14:14] Action [n] enable. - RW */
    ureg32 AEN31:1;              /* [15:15] Action [n] enable. - RW */
    ureg32 WAD24:1;              /* [16:16] Write control bit of Action [m]. - RW */
    ureg32 WAD25:1;              /* [17:17] Write control bit of Action [m]. - RW */
    ureg32 WAD26:1;              /* [18:18] Write control bit of Action [m]. - RW */
    ureg32 WAD27:1;              /* [19:19] Write control bit of Action [m]. - RW */
    ureg32 WAD28:1;              /* [20:20] Write control bit of Action [m]. - RW */
    ureg32 WAD29:1;              /* [21:21] Write control bit of Action [m]. - RW */
    ureg32 WAD30:1;              /* [22:22] Write control bit of Action [m]. - RW */
    ureg32 WAD31:1;              /* [23:23] Write control bit of Action [m]. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_CTRL_5_Bits;

/* Action Status Register including Shadow Register */
typedef struct
{
    ureg32 ACT_N0:1;         /* [0:0] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N1:1;         /* [1:1] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N2:1;         /* [2:2] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N3:1;         /* [3:3] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N4:1;         /* [4:4] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N5:1;         /* [5:5] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N6:1;         /* [6:6] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N7:1;         /* [7:7] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N8:1;         /* [8:8] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N9:1;         /* [9:9] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N10:1;        /* [10:10] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N11:1;        /* [11:11] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N12:1;        /* [12:12] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N13:1;        /* [13:13] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N14:1;        /* [14:14] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N15:1;        /* [15:15] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N16:1;        /* [16:16] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N17:1;        /* [17:17] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N18:1;        /* [18:18] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N19:1;        /* [19:19] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N20:1;        /* [20:20] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N21:1;        /* [21:21] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N22:1;        /* [22:22] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N23:1;        /* [23:23] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N24:1;        /* [24:24] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N25:1;        /* [25:25] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N26:1;        /* [26:26] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N27:1;        /* [27:27] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N28:1;        /* [28:28] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N29:1;        /* [29:29] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N30:1;        /* [30:30] New output data values concerning to Action n provided.  - RW */
    ureg32 ACT_N31:1;        /* [31:31] New output data values concerning to Action n provided.  - RW */
} GTM_DPLL_ACT_STA_Bits;

/* Offset and Switch old/new Address Register */
typedef struct
{
    ureg32 SWON_S:1;              /* [0:0] Switch of new DPLL STATE. Switch bit for LSB address of STATE. - RO */
    ureg32 SWON_T:1;              /* [1:1] Switch of new TRIGGER. Switch bit for LSB address of TRIGGER. - RO */
    ureg32 reserved_2:6;          /* [7:2] Internal  reserved */
    ureg32 OSS:2;                 /* [9:8] Offset size of RAM region 2 - RW */
    ureg32 reserved_10:22;        /* [31:10] Internal  reserved */
} GTM_DPLL_OSW_Bits;

/* Address Offset Register of RAM 2 Regions */
typedef struct
{
    ureg32 AOSV_2A:8;        /* [7:0] Address offset value of the RAM 2A region. - RO */
    ureg32 AOSV_2B:8;        /* [15:8] Address offset value of the RAM 2B region. - RO */
    ureg32 AOSV_2C:8;        /* [23:16] Address offset value of the RAM 2C region. - RO */
    ureg32 AOSV_2D:8;        /* [31:24] Address offset value of the RAM 2D region. - RO */
} GTM_DPLL_AOSV_2_Bits;

/* Actual RAM Pointer Address for TRIGGER */
typedef struct
{
    ureg32 reserved_0:1;         /* [0:0] Internal  reserved */
    ureg32 WAPT:1;               /* [1:1] Write bit for address pointer DPLL_APT.APT - read as zero. - RW */
    ureg32 APT:10;               /* [11:2] Address pointer DPLL TRIGGER:  - RW */
    ureg32 reserved_12:1;        /* [12:12] Internal  reserved */
    ureg32 WAPT_2B:1;            /* [13:13] Write bit for address pointer DPLL_APT.APT_2B - read as zero. - RW */
    ureg32 APT_2B:10;            /* [23:14] Address pointer TRIGGER for RAM region 2b.  - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_APT_Bits;

/* Actual RAM Pointer Address for STATE */
typedef struct
{
    ureg32 reserved_0:1;          /* [0:0] Internal  reserved */
    ureg32 WAPS:1;                /* [1:1] Write bit for address pointer DPLL_APS.APS - read as zero. - RW */
    ureg32 APS:6;                 /* [7:2] Address pointer STATE: Actual RAM pointer address value for DPLL_DT_S[p] and DPLL_RDT_S[p] - RW */
    ureg32 reserved_8:5;          /* [12:8] Internal  reserved */
    ureg32 WAPS_1C2:1;            /* [13:13] Write bit for address pointer DPLL_APS.APS_1C2 - read as zero. - RW */
    ureg32 APS_1C2:6;             /* [19:14] Actual RAM pointer address value for DPLL_TSF_S[p]. - RW */
    ureg32 reserved_20:12;        /* [31:20] Internal  reserved */
} GTM_DPLL_APS_Bits;

/* Actual RAM Pointer Address for Region 2c */
typedef struct
{
    ureg32 reserved_0:2;          /* [1:0] Internal  reserved */
    ureg32 APT_2C:10;             /* [11:2] Address pointer TRIGGER for RAM region 2c: Actual RAM pointer address value for DPLL_ADT_T[p]. - RW */
    ureg32 reserved_12:20;        /* [31:12] Internal  reserved */
} GTM_DPLL_APT_2C_Bits;

/* Actual RAM Pointer Address for RAM region 1c3 */
typedef struct
{
    ureg32 reserved_0:2;         /* [1:0] Internal  reserved */
    ureg32 APS_1C3:6;            /* [7:2] Address pointer STATE for RAM region 1c3: Actual RAM pointer address value for DPLL_ADT_S[p] - RW */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_DPLL_APS_1C3_Bits;

/* Number of Recent TRIGGER Events used for Calculations */
typedef struct
{
    ureg32 NUTE:10;              /* [9:0] Number of recent TRIGGER events used for SUB_INC1 and Action calculations modulo 2*(TNU_max+1). - RW */
    ureg32 FST:1;                /* [10:10] FULL_SCALE of TRIGGER.  - RW */
    ureg32 reserved_11:2;        /* [12:11] Internal  reserved */
    ureg32 SYN_T:3;              /* [15:13] Number of real and virtual events to be considered for the current increment. - RW */
    ureg32 SYN_T_OLD:3;          /* [18:16] Number of real and virtual events to be considered for the last increment. - RW */
    ureg32 VTN:6;                /* [24:19] Virtual DPLL TRIGGER number:  - RW */
    ureg32 reserved_25:4;        /* [28:25] Internal  reserved */
    ureg32 WNUT:1;               /* [29:29] Write control bit for DPLL_NUTC.NUTE and DPLL_NUTC.FST. read as zero. - RW */
    ureg32 WSYN:1;               /* [30:30] Write control bit for DPLL_NUTC.SYN_T and DPLL_NUTC.SYN_T_OLD. read as zero.  - RW */
    ureg32 WVTN:1;               /* [31:31] Write control bit for DPLL_NUTC.VTN. read as zero. - RW */
} GTM_DPLL_NUTC_Bits;

/* Number of Recent STATE Events used for Calculations */
typedef struct
{
    ureg32 NUSE:6;               /* [5:0] Number of recent STATE events used for SUB_INC1 and SUB_INC2 calculations modulo 2*(DPLL_CTRL_0.SNU+1). - RW */
    ureg32 FSS:1;                /* [6:6] Full scale of STATE.  - RW */
    ureg32 SYN_S:6;              /* [12:7] Number of real and virtual events to be considered for the current increment. - RW */
    ureg32 SYN_S_OLD:6;          /* [18:13] Number of real and virtual events to be considered for the last increment. - RW */
    ureg32 VSN:6;                /* [24:19] Virtual STATE number.  - RW */
    ureg32 reserved_25:4;        /* [28:25] Internal  reserved */
    ureg32 WNUS:1;               /* [29:29] Write control bit for DPLL_NUSC.NUSE - read as zero. - RW */
    ureg32 WSYN:1;               /* [30:30] Write control bit for DPLL_NUSC.SYN_S and DPLL_NUSC.SYN_S_OLD - read as zero. - RW */
    ureg32 WVSN:1;               /* [31:31] Write control bit for DPLL_NUSC.VSN - read as zero. - RW */
} GTM_DPLL_NUSC_Bits;

/* Number of Active TRIGGER Events to Interrupt */
typedef struct
{
    ureg32 NTI_CNT:10;            /* [9:0] Number of triggers to interrupt.  - RW */
    ureg32 reserved_10:22;        /* [31:10] Internal  reserved */
} GTM_DPLL_NTI_CNT_Bits;

/* Interrupt Register */
typedef struct
{
    ureg32 PDI:1;                /* [0:0] DPLL disable interrupt.  - RW */
    ureg32 PEI:1;                /* [1:1] DPLL enable interrupt. - RW */
    ureg32 TINI:1;               /* [2:2] TRIGGER minimum hold time violation interrupt (dt <= DPLL_THMI.THMI > 0). - RW */
    ureg32 TAXI:1;               /* [3:3] TRIGGER maximum hold time violation interrupt (dt > DPLL_THMA.THMA > 0). - RW */
    ureg32 SISI:1;               /* [4:4] STATE inactive slope interrupt. - RW */
    ureg32 TISI:1;               /* [5:5] TRIGGER inactive slope interrupt. - RW */
    ureg32 MSI:1;                /* [6:6] Missing STATE interrupt. - RW */
    ureg32 MTI:1;                /* [7:7] Missing TRIGGER interrupt. - RW */
    ureg32 SASI:1;               /* [8:8] STATE active slope interrupt. - RW */
    ureg32 TASI:1;               /* [9:9] TRIGGER active slope interrupt. - RW */
    ureg32 PWI:1;                /* [10:10] Plausibility window (PVT) violation interrupt of TRIGGER. - RW */
    ureg32 W2I:1;                /* [11:11] RAM write access to RAM region 2 interrupt. - RW */
    ureg32 W1I:1;                /* [12:12] Write access to RAM region 1b or 1c interrupt. - RW */
    ureg32 GL1I:1;               /* [13:13] Get lock interrupt for SUB_INC1. - RW */
    ureg32 LL1I:1;               /* [14:14] Loss of lock interrupt for SUB_INC1. - RW */
    ureg32 EI:1;                 /* [15:15] Error interrupt (see status register bit 31). - RW */
    ureg32 GL2I:1;               /* [16:16] Get lock interrupt for SUB_INC2. - RW */
    ureg32 LL2I:1;               /* [17:17] Loss of lock interrupt for SUB_INC2. - RW */
    ureg32 TE0I:1;               /* [18:18] TRIGGER event interrupt 0. - RW */
    ureg32 TE1I:1;               /* [19:19] TRIGGER event interrupt 1. - RW */
    ureg32 TE2I:1;               /* [20:20] TRIGGER event interrupt 2. - RW */
    ureg32 TE3I:1;               /* [21:21] TRIGGER event interrupt 3. - RW */
    ureg32 TE4I:1;               /* [22:22] TRIGGER event interrupt 4. - RW */
    ureg32 CDTI:1;               /* [23:23] TRIGGER duration is calculated only when DPLL_NTI_CNT.NTI_CNT is zero. - RW */
    ureg32 CDSI:1;               /* [24:24] Calculation of STATE duration done - RW */
    ureg32 TORI:1;               /* [25:25] TRIGGER out of range interrupt - RW */
    ureg32 SORI:1;               /* [26:26] STATE out of range - RW */
    ureg32 DCGI:1;               /* [27:27] Direction change interrupt - RW */
    ureg32 reserved_28:4;        /* [31:28] Internal  reserved */
} GTM_DPLL_IRQ_NOTIFY_Bits;

/* Interrupt Enable Register */
typedef struct
{
    ureg32 PDI_IRQ_EN:1;         /* [0:0] DPLL disable interrupt enable - when switch off of the DPLL_CTRL_1.DEN bit. - RW */
    ureg32 PEI_IRQ_EN:1;         /* [1:1] DPLL enable interrupt enable - when switch on of the DPLL_CTRL_1.DEN bit. - RW */
    ureg32 TINI_IRQ_EN:1;        /* [2:2] TRIGGER minimum hold time violation interrupt enable bit. - RW */
    ureg32 TAXI_IRQ_EN:1;        /* [3:3] TRIGGER maximum hold time violation interrupt enable bit. - RW */
    ureg32 SISI_IRQ_EN:1;        /* [4:4] STATE inactive slope interrupt enable bit. - RW */
    ureg32 TISI_IRQ_EN:1;        /* [5:5] TRIGGER inactive slope interrupt enable bit. - RW */
    ureg32 MSI_IRQ_EN:1;         /* [6:6] Missing STATE interrupt enable. - RW */
    ureg32 MTI_IRQ_EN:1;         /* [7:7] Missing TRIGGER interrupt enable. - RW */
    ureg32 SASI_IRQ_EN:1;        /* [8:8] STATE active slope interrupt enable. - RW */
    ureg32 TASI_IRQ_EN:1;        /* [9:9] TRIGGER active slope interrupt enable. - RW */
    ureg32 PWI_IRQ_EN:1;         /* [10:10] Plausibility window (PVT) violation interrupt of TRIGGER enable. - RW */
    ureg32 W2I_IRQ_EN:1;         /* [11:11] RAM write access to RAM region 2 interrupt enable. - RW */
    ureg32 W1I_IRQ_EN:1;         /* [12:12] Write access to RAM region 1b or 1c interrupt. - RW */
    ureg32 GL1I_IRQ_EN:1;        /* [13:13] Get lock interrupt enable - when lock arises. - RW */
    ureg32 LL1I_IRQ_EN:1;        /* [14:14] Loss of lock interrupt enable. - RW */
    ureg32 EI_IRQ_EN:1;          /* [15:15] Error interrupt enable (see status register). - RW */
    ureg32 GL2I_IRQ_EN:1;        /* [16:16] Get lock interrupt enable for SUB_INC2. - RW */
    ureg32 LL2I_IRQ_EN:1;        /* [17:17] Loss of lock interrupt enable for SUB_INC2. - RW */
    ureg32 TE0I_IRQ_EN:1;        /* [18:18] TRIGGER event interrupt 0 enable. - RW */
    ureg32 TE1I_IRQ_EN:1;        /* [19:19] TRIGGER event interrupt 1 enable. - RW */
    ureg32 TE2I_IRQ_EN:1;        /* [20:20] TRIGGER event interrupt 2 enable. - RW */
    ureg32 TE3I_IRQ_EN:1;        /* [21:21] TRIGGER event interrupt 3 enable. - RW */
    ureg32 TE4I_IRQ_EN:1;        /* [22:22] TRIGGER event interrupt 4 enable. - RW */
    ureg32 CDTI_IRQ_EN:1;        /* [23:23] Enable interrupt when calculation of TRIGGER duration done - RW */
    ureg32 CDSI_IRQ_EN:1;        /* [24:24] Enable interrupt when calculation of TRIGGER duration done - RW */
    ureg32 TORI_IRQ_EN:1;        /* [25:25] TRIGGER out of range interrupt - RW */
    ureg32 SORI_IRQ_EN:1;        /* [26:26] STATE out of range - RW */
    ureg32 DCGI_IRQ_EN:1;        /* [27:27] Direction change interrupt - RW */
    ureg32 reserved_28:4;        /* [31:28] Internal  reserved */
} GTM_DPLL_IRQ_EN_Bits;

/* Force Interrupt Register */
typedef struct
{
    ureg32 TRG_PDI:1;            /* [0:0] Trigger the bit DPLL_IRQ_NOTIFY.PDI by software. - RW */
    ureg32 TRG_PEI:1;            /* [1:1] Trigger the bit DPLL_IRQ_NOTIFY.PEI by software. - RW */
    ureg32 TRG_TINI:1;           /* [2:2] Trigger the bit DPLL_IRQ_NOTIFY.TINI by software. - RW */
    ureg32 TRG_TAXI:1;           /* [3:3] Trigger the bit DPLL_IRQ_NOTIFY.TAXI by software. - RW */
    ureg32 TRG_SISI:1;           /* [4:4] Trigger the bit DPLL_IRQ_NOTIFY.SISI by software. - RW */
    ureg32 TRG_TISI:1;           /* [5:5] Trigger the bit DPLL_IRQ_NOTIFY.TISI by software. - RW */
    ureg32 TRG_MSI:1;            /* [6:6] Trigger the bit DPLL_IRQ_NOTIFY.MSI  by software. - RW */
    ureg32 TRG_MTI:1;            /* [7:7] Trigger the bit DPLL_IRQ_NOTIFY.MTI  by software. - RW */
    ureg32 TRG_SASI:1;           /* [8:8] Trigger the bit DPLL_IRQ_NOTIFY.SASI  by software. - RW */
    ureg32 TRG_TASI:1;           /* [9:9] Trigger the bit DPLL_IRQ_NOTIFY.TASI  by software. - RW */
    ureg32 TRG_PWI:1;            /* [10:10] Trigger the bit DPLL_IRQ_NOTIFY.PWI  by software. - RW */
    ureg32 TRG_W2I:1;            /* [11:11] Trigger the bit DPLL_IRQ_NOTIFY.W2I  by software. - RW */
    ureg32 TRG_W1I:1;            /* [12:12] Trigger the bit DPLL_IRQ_NOTIFY.W1I  by software. - RW */
    ureg32 TRG_GL1I:1;           /* [13:13] Trigger the bit DPLL_IRQ_NOTIFY.GL1I  by software. - RW */
    ureg32 TRG_LL1I:1;           /* [14:14] Trigger the bit DPLL_IRQ_NOTIFY.LL1I  by software. - RW */
    ureg32 TRG_EI:1;             /* [15:15] Trigger the bit DPLL_IRQ_NOTIFY.EI  by software. - RW */
    ureg32 TRG_GL2I:1;           /* [16:16] Trigger the bit DPLL_IRQ_NOTIFY.GL2I by software. - RW */
    ureg32 TRG_LL2I:1;           /* [17:17] Trigger the bit DPLL_IRQ_NOTIFY.LL2I by software. - RW */
    ureg32 TRG_TE0I:1;           /* [18:18] Trigger the bit DPLL_IRQ_NOTIFY.TE0I by software. - RW */
    ureg32 TRG_TE1I:1;           /* [19:19] Trigger the bit DPLL_IRQ_NOTIFY.TE1I by software. - RW */
    ureg32 TRG_TE2I:1;           /* [20:20] Trigger the bit DPLL_IRQ_NOTIFY.TE2I by software. - RW */
    ureg32 TRG_TE3I:1;           /* [21:21] Trigger the bit DPLL_IRQ_NOTIFY.TE3I by software. - RW */
    ureg32 TRG_TE4I:1;           /* [22:22] Trigger the bit DPLL_IRQ_NOTIFY.TE4I by software. - RW */
    ureg32 TRG_CDTI:1;           /* [23:23] Trigger the bit DPLL_IRQ_NOTIFY.CDTI by software. - RW */
    ureg32 TRG_CDSI:1;           /* [24:24] Trigger the bit DPLL_IRQ_NOTIFY.CDSI by software. - RW */
    ureg32 TRG_TORI:1;           /* [25:25] Trigger the bit DPLL_IRQ_NOTIFY.TORI by software. - RW */
    ureg32 TRG_SORI:1;           /* [26:26] Trigger the bit DPLL_IRQ_NOTIFY.SORI by software. - RW */
    ureg32 TRG_DCGI:1;           /* [27:27] Trigger the bit DPLL_IRQ_NOTIFY.DCGI by software. - RW */
    ureg32 reserved_28:4;        /* [31:28] Internal  reserved */
} GTM_DPLL_IRQ_FORCINT_Bits;

/* Interrupt Request Mode */
typedef struct
{
    ureg32 IRQ_MODE:2;           /* [1:0] IRQ mode selection - RW */
    ureg32 reserved_2:30;        /* [31:2] Internal  reserved */
} GTM_DPLL_IRQ_MODE_Bits;

/* Error Interrupt Enable Register */
typedef struct
{
    ureg32 PDI_EIRQ_EN:1;         /* [0:0] DPLL disable interrupt enable - when switch off of the DPLL_CTRL_1.DEN bit. - RW */
    ureg32 PEI_EIRQ_EN:1;         /* [1:1] Enabling of DPLL interrupt enable - while switching on the DPLL_CTRL_1.DEN bit. - RW */
    ureg32 TINI_EIRQ_EN:1;        /* [2:2] TRIGGER minimum hold time violation interrupt enable bit. - RW */
    ureg32 TAXI_EIRQ_EN:1;        /* [3:3] TRIGGER maximum hold time violation interrupt enable bit. - RW */
    ureg32 SISI_EIRQ_EN:1;        /* [4:4] STATE inactive slope interrupt enable bit. - RW */
    ureg32 TISI_EIRQ_EN:1;        /* [5:5] TRIGGER inactive slope interrupt enable bit. - RW */
    ureg32 MSI_EIRQ_EN:1;         /* [6:6] Missing STATE interrupt enable. - RW */
    ureg32 MTI_EIRQ_EN:1;         /* [7:7] Missing TRIGGER interrupt enable. - RW */
    ureg32 SASI_EIRQ_EN:1;        /* [8:8] STATE active slope interrupt enable. - RW */
    ureg32 TASI_EIRQ_EN:1;        /* [9:9] TRIGGER active slope interrupt enable. - RW */
    ureg32 PWI_EIRQ_EN:1;         /* [10:10] Plausibility window (PVT) violation interrupt of TRIGGER enable. - RW */
    ureg32 W2I_EIRQ_EN:1;         /* [11:11] RAM write access to RAM region 2 interrupt enable. - RW */
    ureg32 W1I_EIRQ_EN:1;         /* [12:12] Write access to RAM region 1b or 1c interrupt. - RW */
    ureg32 GL1I_EIRQ_EN:1;        /* [13:13] Get lock interrupt enable - when lock is available. - RW */
    ureg32 LL1I_EIRQ_EN:1;        /* [14:14] Loss of lock interrupt enable. - RW */
    ureg32 EI_EIRQ_EN:1;          /* [15:15] Error interrupt enable (see status register). - RW */
    ureg32 GL2I_EIRQ_EN:1;        /* [16:16] Get lock interrupt enable for SUB_INC2. - RW */
    ureg32 LL2I_EIRQ_EN:1;        /* [17:17] Loss of lock interrupt enable for SUB_INC2. - RW */
    ureg32 TE0I_EIRQ_EN:1;        /* [18:18] TRIGGER event interrupt 0 enable. - RW */
    ureg32 TE1I_EIRQ_EN:1;        /* [19:19] TRIGGER event interrupt 1 enable. - RW */
    ureg32 TE2I_EIRQ_EN:1;        /* [20:20] TRIGGER event interrupt 2 enable. - RW */
    ureg32 TE3I_EIRQ_EN:1;        /* [21:21] TRIGGER event interrupt 3 enable. - RW */
    ureg32 TE4I_EIRQ_EN:1;        /* [22:22] TRIGGER event interrupt 4 enable. - RW */
    ureg32 CDTI_EIRQ_EN:1;        /* [23:23] Enable interrupt when calculation of TRIGGER duration done - RW */
    ureg32 CDSI_EIRQ_EN:1;        /* [24:24] Enable interrupt when calculation of TRIGGER duration done - RW */
    ureg32 TORI_EIRQ_EN:1;        /* [25:25] TRIGGER out of range interrupt - RW */
    ureg32 SORI_EIRQ_EN:1;        /* [26:26] STATE out of range - RW */
    ureg32 DCGI_EIRQ_EN:1;        /* [27:27] Direction change interrupt - RW */
    ureg32 reserved_28:4;         /* [31:28] Internal  reserved */
} GTM_DPLL_EIRQ_EN_Bits;

/* Counter Value of Sent SUB_INC1 Pulses */
typedef struct
{
    ureg32 INC_CNT1:24;          /* [23:0] Actual number of pulses yet to be sent out at the current increment until the next active input signal in automatic end mode; - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_INC_CNT1_Bits;

/* Counter Value of sent SUB_INC2 values (for DPLL_CTRL_1.SMC=1 and DPLL_CTRL_0.RMO=1) */
typedef struct
{
    ureg32 INC_CNT2:24;          /* [23:0] Actual number of pulses yet to be sent out at the current increment until the next active input signal in automatic end mode; - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_INC_CNT2_Bits;

/* TRIGGER Time Stamp Field Offset at Synchronization Time */
typedef struct
{
    ureg32 APT_2B_EXT:6;           /* [5:0] Address pointer 2b extension; this offset value determines - by which value the DPLL_APT.APT_2B is changed at the synchronization time; set by CPU before the synchronization is performed.  - RW */
    ureg32 APT_2B_STATUS:1;        /* [6:6] Address pointer 2b status; set by the CPU before the synchronization is performed. The value is cleared when the DPLL_APT_SYNC.APT_2B_OLD value is written. - RW */
    ureg32 reserved_7:7;           /* [13:7] Internal  reserved */
    ureg32 APT_2B_OLD:10;          /* [23:14] Address pointer TRIGGER for RAM region 2b at synchronization time; this value is set by the current DPLL_APT.APT_2B value when the synchronization takes place for the first active TRIGGER event after writing DPLL_APT_2C.APT_2C but before adding the offset value DPLL_APT_SYNC.APT_2B_EXT (that means: when DPLL_APT_SYNC.APT_2B_STATUS=1). - RW */
    ureg32 reserved_24:8;          /* [31:24] Internal  reserved */
} GTM_DPLL_APT_SYNC_Bits;

/* STATE Time Stamp Field Offset at Synchronization Time */
typedef struct
{
    ureg32 APS_1C2_EXT:6;           /* [5:0] Address pointer 1c2 extension; this offset value determines - by which value the DPLL_APS_EXT.APS_1C2 is changed at the time of synchronization; set by CPU before the synchronization is performed. - RW */
    ureg32 APS_1C2_STATUS:1;        /* [6:6] Address pointer 1c2 status; set by CPU before the synchronization is performed. The value is cleared automatically when the DPLL_APS_SYNC.APS_1C2_OLD value is written. - RW */
    ureg32 reserved_7:7;            /* [13:7] Internal  reserved */
    ureg32 APS_1C2_OLD:6;           /* [19:14] Address pointer STATE for RAM region 1c2 at synchronization time; this value is set by the current DPLL_APS_EXT.APS_1C2 value when the synchronization takes place for the first active STATE event after writing DPLL_APS_1C3_EXT.APS_1C3 but before adding the offset value DPLL_APS_SYNC.APS_1C2_EXT (that means: when DPLL_APS_SYNC.APS_1C2_STATUS=1). - RW */
    ureg32 reserved_20:12;          /* [31:20] Internal  reserved */
} GTM_DPLL_APS_SYNC_Bits;

/* Time Stamp Value for the last active TRIGGER */
typedef struct
{
    ureg32 DPLL_TBU_TS0_T:24;        /* [23:0] Value of CCM[0]_TBU_TS0 at the last TRIGGER event; - RW */
    ureg32 reserved_24:8;            /* [31:24] Internal  reserved */
} GTM_DPLL_TBU_TS0_T_Bits;

/* Time Stamp Value for the last active STATE */
typedef struct
{
    ureg32 DPLL_TBU_TS0_S:24;        /* [23:0] Value of CCM[0]_TBU_TS0 at the last STATE event; - RW */
    ureg32 reserved_24:8;            /* [31:24] Internal  reserved */
} GTM_DPLL_TBU_TS0_S_Bits;

/* ADD_IN Value in Direct Load Mode for TRIGGER */
typedef struct
{
    ureg32 ADD_IN_LD1:24;        /* [23:0] Input value for SUB_INC1 generation - given by CPU. This value can be used in normal and emergency mode (DPLL_CTRL_1.SMC=0) as well as for DPLL_CTRL_1.SMC=1. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_ADD_IN_LD1_Bits;

/* ADD_IN Value in Direct Load Mode for STATE */
typedef struct
{
    ureg32 ADD_IN_LD2:24;        /* [23:0] ADD_IN_LD2: Input value for SUB_INC2 generation - given by CPU. This value can be used for DPLL_CTRL_1.SMC=1 while DPLL_CTRL_0.RMO=1. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_ADD_IN_LD2_Bits;

/* Status Register */
typedef struct
{
    ureg32 FPCE:1;               /* [0:0] Fast pulse correction error - RW */
    ureg32 CSO:1;                /* [1:1] Calculated STATE duration overflow. - RW */
    ureg32 reserved_2:1;         /* [2:2] Internal  reserved */
    ureg32 CTO:1;                /* [3:3] Calculated TRIGGER duration overflow. - RW */
    ureg32 CRO:1;                /* [4:4] Calculated Reciprocal value overflow. - RW */
    ureg32 RCS:1;                /* [5:5] Resolution conflict STATE.  - RO */
    ureg32 RCT:1;                /* [6:6] Resolution conflict TRIGGER. - RO */
    ureg32 PSE:1;                /* [7:7] Prediction space configuration error - RO */
    ureg32 SOR:1;                /* [8:8] STATE out of range - RW */
    ureg32 MS:1;                 /* [9:9] Missing STATE detected according to DPLL_SOV. - RW */
    ureg32 TOR:1;                /* [10:10] TRIGGER out of range - RW */
    ureg32 MT:1;                 /* [11:11] Missing TRIGGER detected according to DPLL_TOV - RW */
    ureg32 RAM2_ERR:1;           /* [12:12] DPLL internal access to not configured RAM2 memory space - RW */
    ureg32 reserved_13:2;        /* [14:13] Internal  reserved */
    ureg32 LOW_RES:1;            /* [15:15] Low resolution of CCM[0]_TBU_TS0 is used for DPLL input; this value reflects the input signal LOW_RES - RO */
    ureg32 CSVS:1;               /* [16:16] Current signal value STATE - RO */
    ureg32 CSVT:1;               /* [17:17] Current signal value TRIGGER - RO */
    ureg32 CAIP2:1;              /* [18:18] Calculation of upper half Actions in progress - RO */
    ureg32 CAIP1:1;              /* [19:19] Calculation of lower half Actions in progress - RO */
    ureg32 ISN:1;                /* [20:20] Incrementing number of STATE events is not plausible; Bit is set when the number of states is different from profile - RO */
    ureg32 ITN:1;                /* [21:21] Incrementing number of TRIGGER events is not plausible; Bit is set when the number of TRIGGERS is different from profile - RO */
    ureg32 BWD2:1;               /* [22:22] Backward drive of SUB_INC2 - RO */
    ureg32 BWD1:1;               /* [23:23] Backwards drive of SUB_INC1 - RO */
    ureg32 reserved_24:1;        /* [24:24] Internal  reserved */
    ureg32 LOCK2:1;              /* [25:25] DPLL Lock status concerning SUB_INC2 - RO */
    ureg32 SYS:1;                /* [26:26] Synchronization condition of STATE fixed. - RO */
    ureg32 SYT:1;                /* [27:27] Synchronization condition of TRIGGER fixed. - RO */
    ureg32 FSD:1;                /* [28:28] First STATE detected. - RO */
    ureg32 FTD:1;                /* [29:29] First TRIGGER detected. - RO */
    ureg32 LOCK1:1;              /* [30:30] DPLL Lock status concerning SUB_INC1. - RO */
    ureg32 ERR:1;                /* [31:31] Error during configuration or operation resulting in unexpected values. - RO */
} GTM_DPLL_STATUS_Bits;

/* ID Information for Input Signal PMTR[n] (Position minus Time Request) */
typedef struct
{
    ureg32 ID_PMTR:9;            /* [8:0] ID information to the input signal PMTR[n] from the ARU. - RW */
    ureg32 reserved_9:23;        /* [31:9] Internal  reserved */
} GTM_DPLL_ID_PMTR_Bits;

/* Shadow Register of DPLL_CTRL_0 controlled by an active TRIGGER Slope */
typedef struct
{
    ureg32 MLT:10;                /* [9:0] Multiplier for TRIGGER; MLT+1 is number of SUB_INC1 pulses between two TRIGGER events in normal mode (1...1024);  - RO */
    ureg32 IFP:1;                 /* [10:10] Input filter position; value contains position or time related information. - RO */
    ureg32 reserved_11:15;        /* [25:11] Internal  reserved */
    ureg32 AMT:1;                 /* [26:26] Use of adaptation information of Adapt mode TRIGGER;  - RO */
    ureg32 reserved_27:1;         /* [27:27] Internal  reserved */
    ureg32 IDT:1;                 /* [28:28] Input delay TRIGGER; use of input delay information transmitted in FT part of the TRIGGER signal. - RO */
    ureg32 reserved_29:2;         /* [30:29] Internal  reserved */
    ureg32 RMO:1;                 /* [31:31] Reference mode; selection of the relevant the input signal for generation of SUB_INC1. - RO */
} GTM_DPLL_CTRL_0_SHADOW_TRIGGER_Bits;

/* Shadow Register of DPLL_CTRL_0 controlled by an active STATE Slope */
typedef struct
{
    ureg32 reserved_0:10;         /* [9:0] Internal  reserved */
    ureg32 IFP:1;                 /* [10:10] Input filter position; value contains position or time related information. - RO */
    ureg32 reserved_11:14;        /* [24:11] Internal  reserved */
    ureg32 AMS:1;                 /* [25:25] Adapt mode STATE; Use of adaptation information of STATE. - RO */
    ureg32 reserved_26:1;         /* [26:26] Internal  reserved */
    ureg32 IDS:1;                 /* [27:27] Input delay STATE; Use of input delay information transmitted in FT part of the STATE signal. - RO */
    ureg32 reserved_28:3;         /* [30:28] Internal  reserved */
    ureg32 RMO:1;                 /* [31:31] Reference mode; selection of the relevant the input signal for generation of SUB_INC1. - RO */
} GTM_DPLL_CTRL_0_SHADOW_STATE_Bits;

/* Shadow Register of DPLL_CTRL_1 controlled by an active TRIGGER Slope */
typedef struct
{
    ureg32 DMO:1;                /* [0:0] DPLL mode select. - RO */
    ureg32 reserved_1:2;         /* [2:1] Internal  reserved */
    ureg32 COA:1;                /* [3:3] Correction strategy in automatic end mode (DPLL_CTRL_1.DMO=0). - RO */
    ureg32 PIT:1;                /* [4:4] Plausibility value PVT to next active TRIGGER is time related - RO */
    ureg32 SGE1:1;               /* [5:5] SUB_INC1 generator enable. - RO */
    ureg32 DLM1:1;               /* [6:6] Direct Load Mode for SUB_INC1 generation - RO */
    ureg32 PCM1:1;               /* [7:7] Pulse Correction Mode for SUB_INC1 generation. - RO */
    ureg32 reserved_8:24;        /* [31:8] Internal  reserved */
} GTM_DPLL_CTRL_1_SHADOW_TRIGGER_Bits;

/* DPLL Shadow Register of DPLL_CTRL_1 controlled by an active STATE Slope */
typedef struct
{
    ureg32 DMO:1;                 /* [0:0] DPLL mode select. - RO */
    ureg32 reserved_1:2;          /* [2:1] Internal  reserved */
    ureg32 COA:1;                 /* [3:3] Correction strategy in automatic end mode (DPLL_CTRL_1.DMO=0). - RO */
    ureg32 reserved_4:1;          /* [4:4] Internal  reserved */
    ureg32 SGE1:1;                /* [5:5] SUB_INC1 generator enable. - RO */
    ureg32 DLM1:1;                /* [6:6] Direct Load Mode for SUB_INC1 generation - RO */
    ureg32 PCM1:1;                /* [7:7] Pulse Correction Mode for SUB_INC1 generation. - RO */
    ureg32 SGE2:1;                /* [8:8] SUB_INC2 generator enable. - RO */
    ureg32 DLM2:1;                /* [9:9] Direct Load Mode for SUB_INC2 generation - RO */
    ureg32 PCM2:1;                /* [10:10] Pulse Correction Mode for SUB_INC2 generation. - RO */
    ureg32 reserved_11:21;        /* [31:11] Internal  reserved */
} GTM_DPLL_CTRL_1_SHADOW_STATE_Bits;

/* Register to control the RAM Initialization */
typedef struct
{
    ureg32 INIT_1A:1;            /* [0:0] RAM region 1a initialization in progress - RO */
    ureg32 INIT_1BC:1;           /* [1:1] RAM region 1b and 1c initialization in progress - RO */
    ureg32 INIT_2:1;             /* [2:2] RAM region 2 initialization in progress - RO */
    ureg32 reserved_3:1;         /* [3:3] Internal  reserved */
    ureg32 INIT_RAM:1;           /* [4:4] RAM regions 1a - 1b and 2 are to be initialized. - RW */
    ureg32 reserved_5:27;        /* [31:5] Internal  reserved */
} GTM_DPLL_RAM_INI_Bits;

/* Position Request for Action [n] */
typedef struct
{
    ureg32 PSA:24;               /* [23:0] Position information of a desired Action [n] - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_PSA_Bits;

/* Time to React for Action [n] */
typedef struct
{
    ureg32 DLA:24;               /* [23:0] Time to react before the corresponding position value of a desired Action [n] is reached . - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_DLA_Bits;

/* Calculated Relative Time to Action [n] */
typedef struct
{
    ureg32 DB:10;                /* [9:0] Number of events to Action [n] (fractional part). - RW */
    ureg32 DW:10;                /* [19:10] Number of events to Action [n] (integer part). - RW */
    ureg32 NOT_USED:4;           /* [23:20] Not used - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_NA_Bits;

/* Calculated Relative Time to Action [n] */
typedef struct
{
    ureg32 DTA:24;               /* [23:0] Calculated relative time to Action [n]  - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_DTA_Bits;

/* Actual TRIGGER Time Stamp Value */
typedef struct
{
    ureg32 TRIGGER_TS:24;        /* [23:0] Time stamp value of the last active TRIGGER input. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_TS_T_Bits;

/* Previous TRIGGER Time Stamp Value */
typedef struct
{
    ureg32 TRIGGER_TS_OLD:24;        /* [23:0] Time stamp value of the last but one active TRIGGER input. - RW */
    ureg32 reserved_24:8;            /* [31:24] Internal  reserved */
} GTM_DPLL_TS_T_OLD_Bits;

/* Actual TRIGGER Filter value */
typedef struct
{
    ureg32 TRIGGER_FT:24;        /* [23:0] Filter value of the last active TRIGGER input. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_FTV_T_Bits;

/* DPLL RAM1B reserved  data */
typedef struct
{
    ureg32 RSVD:24;              /* [23:0] Reserved Data word - no DPLL internal use. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_RAM1B_RSVD_Bits;

/* Actual STATE Time Stamp Register */
typedef struct
{
    ureg32 STATE_TS:24;          /* [23:0] Time stamp value of the last active STATE input. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_TS_S_Bits;

/* Previous STATE Time Stamp Register */
typedef struct
{
    ureg32 STATE_TS_OLD:24;        /* [23:0] Time stamp value of the last active STATE input. - RW */
    ureg32 reserved_24:8;          /* [31:24] Internal  reserved */
} GTM_DPLL_TS_S_OLD_Bits;

/* Actual STATE Filter Value */
typedef struct
{
    ureg32 STATE_FT:24;          /* [23:0] Filter value of the last active STATE input. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_FTV_S_Bits;

/* TRIGGER Hold Time Min. Value */
typedef struct
{
    ureg32 THMI:16;              /* [15:0] Minimal time between active and inactive TRIGGER slope; the time value corresponds to the time stamp clock counts: This means the clock selected for the TBU_CH0_BASE (see TBU_CH0_CTRL register) - RW */
    ureg32 NOT_USED:8;           /* [23:16] Not used - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_THMI_Bits;

/* TRIGGER Hold Time Max. Value */
typedef struct
{
    ureg32 THMA:16;              /* [15:0] Maximal time between active and inactive TRIGGER slope; the time value corresponds to the time stamp clock counts: This means the clock selected for the TBU_CH0_BASE (see TBU_CH0_CTRL register) - RW */
    ureg32 NOT_USED:8;           /* [23:16] Not used - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_THMA_Bits;

/* Measured TRIGGER Hold Time Value */
typedef struct
{
    ureg32 THVAL:24;             /* [23:0] Measured time from the last active slope to the next inactive TRIGGER slope in time stamp clock counts: This means the clock selected for the TBU_CH0_BASE; - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_THVAL_Bits;

/* Time Out Value of Active TRIGGER Slope (for missing TRIGGER generation) */
typedef struct
{
    ureg32 TOV_DB:10;            /* [9:0] Decision value (fractional part) for missing TRIGGER interrupt. - RW */
    ureg32 TOV_DW:6;             /* [15:10] Decision value (integer part) for missing TRIGGER interrupt. - RW */
    ureg32 NOT_USED:8;           /* [23:16] Not used - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_TOV_Bits;

/* Time Out Value of active STATE Slope (for missing STATE generation) */
typedef struct
{
    ureg32 DB:10;                /* [9:0] Decision value (fractional part) for missing STATE interrupt. - RW */
    ureg32 DW:6;                 /* [15:10] Decision value (integer part) for missing STATE interrupt. - RW */
    ureg32 NOT_USED:8;           /* [23:16] Not used - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_TOV_S_Bits;

/* Calculated ADD_IN Value for SUB_INC1 Generation */
typedef struct
{
    ureg32 ADD_IN_CAL1:24;        /* [23:0] Calculated input value for SUB_INC1 generation - calculated by the DPLL. - RW */
    ureg32 reserved_24:8;         /* [31:24] Internal  reserved */
} GTM_DPLL_ADD_IN_CAL1_Bits;

/* Calculated ADD_IN Value for SUB_INC2 Generation */
typedef struct
{
    ureg32 ADD_IN_CAL2:24;        /* [23:0] Input value for SUB_INC2 generation - calculated by the DPLL for DPLL_CTRL_1.SMC=DPLL_CTRL_0.RMO=1. - RW */
    ureg32 reserved_24:8;         /* [31:24] Internal  reserved */
} GTM_DPLL_ADD_IN_CAL2_Bits;

/* Missing Pulses to be Added or Subtracted Directly  */
typedef struct
{
    ureg32 MPVAL1:16;            /* [15:0] Missing pulses for direct correction of SUB_INC1 pulses by the CPU; - RW */
    ureg32 SIX1:8;               /* [23:16] Sign extension for DPLL_MPVAL1.MPVAL1 - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_MPVAL1_Bits;

/* Missing Pulses to be Added or Subtracted Directly */
typedef struct
{
    ureg32 MPVAL2:16;            /* [15:0] Missing pulses for direct correction of SUB_INC2 pulses by the CPU; - RW */
    ureg32 SIX2:8;               /* [23:16] Sign extension for DPLL_MPVAL2.MPVAL2 - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_MPVAL2_Bits;

/* Target Number of Pulses to be sent in Normal Mode */
typedef struct
{
    ureg32 NMB_T_TAR:16;         /* [15:0] Target number of pulses for TRIGGER; calculated target number of pulses in normal mode for the current TRIGGER increment without missing pulses. - RW */
    ureg32 NOT_USED:8;           /* [23:16] Not used - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_NMB_T_TAR_Bits;

/* Last but one Target Number of Pulses to be sent in Normal Mode  */
typedef struct
{
    ureg32 NMB_T_TAR_OLD:16;        /* [15:0] Target number of pulses for TRIGGER; calculated number of pulses in normal mode for the current TRIGGER increment without missing pulses. - RW */
    ureg32 NOT_USED:8;              /* [23:16] Not used - RW */
    ureg32 reserved_24:8;           /* [31:24] Internal  reserved */
} GTM_DPLL_NMB_T_TAR_OLD_Bits;

/* Target Number of Pulses to be sent in Emergency Mode */
typedef struct
{
    ureg32 NMB_S_TAR:20;         /* [19:0] Target number of pulses for STATE; calculated number of pulses in emergency mode for the current STATE increment without missing pulses. - RW */
    ureg32 NOT_USED:4;           /* [23:20] Not used - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_NMB_S_TAR_Bits;

/* Last but one Target Number of Pulses to be sent in Emergency Mode */
typedef struct
{
    ureg32 NMB_S_TAR_OLD:20;        /* [19:0] Target number of pulses for STATE; calculated number of pulses in emergency mode for the current STATE increment without missing pulses. - RW */
    ureg32 NOT_USED:4;              /* [23:20] Not used - RW */
    ureg32 reserved_24:8;           /* [31:24] Internal  reserved */
} GTM_DPLL_NMB_S_TAR_OLD_Bits;

/* Reciprocal Value of the Expected Increment Duration of TRIGGER */
typedef struct
{
    ureg32 RCDT_TX:24;           /* [23:0] Reciprocal value of expected increment duration *2^32 while only the lower 24 bits are used. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_RCDT_TX_Bits;

/* Reciprocal Value of the Expected Increment Duration of STATE */
typedef struct
{
    ureg32 RCDT_SX:24;           /* [23:0] Reciprocal value of expected increment duration *2^32 while only the lower 24 bits are used. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_RCDT_SX_Bits;

/* Reciprocal Value of the Expected Nominal Increment Duration of TRIGGER */
typedef struct
{
    ureg32 RCDT_TX_NOM:24;        /* [23:0] Reciprocal value of expected increment duration *2^32 while only the lower 24 bits are used. - RW */
    ureg32 reserved_24:8;         /* [31:24] Internal  reserved */
} GTM_DPLL_RCDT_TX_NOM_Bits;

/* Reciprocal Value of the Expected Nominal Increment Duration of STATE */
typedef struct
{
    ureg32 RCDT_SX_NOM:24;        /* [23:0] Reciprocal value of expected increment duration *2^32 while only the lower 24 bits are used. - RW */
    ureg32 reserved_24:8;         /* [31:24] Internal  reserved */
} GTM_DPLL_RCDT_SX_NOM_Bits;

/* Reciprocal Value of the Last Increment of TRIGGER */
typedef struct
{
    ureg32 RDT_T_ACT:24;         /* [23:0] Reciprocal value of last TRIGGER increment *2^32 - only the lower 24 bits are used; the LSB is rounded up when the next truncated bit is 1. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_RDT_T_ACT_Bits;

/* Reciprocal Value of the Last Increment of STATE */
typedef struct
{
    ureg32 RDT_S_ACT:24;         /* [23:0] Reciprocal value of last STATE increment *2^32 - only the lower 24 bits are used; the LSB is rounded up when the next truncated bit is 1.  - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_RDT_S_ACT_Bits;

/* Duration of the Last TRIGGER Increment */
typedef struct
{
    ureg32 DT_T_ACT:24;          /* [23:0] Calculated duration of the last TRIGGER increment. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_DT_T_ACT_Bits;

/* Duration of the Last STATE Increment */
typedef struct
{
    ureg32 DT_S_ACT:24;          /* [23:0] Calculated duration of the last STATE increment. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_DT_S_ACT_Bits;

/* Difference of Prediction to Actual Value of the Last TRIGGER Increment */
typedef struct
{
    ureg32 EDT_T:24;             /* [23:0] Signed difference between actual value and a simple prediction of the last TRIGGER increment:  - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_EDT_T_Bits;

/* Weighted Difference of Prediction Errors of TRIGGER */
typedef struct
{
    ureg32 MEDT_T:24;            /* [23:0] Signed middle weighted difference between actual value and prediction of the last TRIGGER increments; only calculated for DPLL_STATUS.SYT=1 - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_MEDT_T_Bits;

/* Difference of Prediction to Actual Value of the Last STATE Increment */
typedef struct
{
    ureg32 EDT_S:24;             /* [23:0] Signed difference between actual value and prediction of the last STATE increment - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_EDT_S_Bits;

/* Weighted Difference of Prediction Errors of STATE */
typedef struct
{
    ureg32 MEDT_S:24;            /* [23:0] Signed middle weighted difference between actual value and prediction of the last STATE increments; only calculated for DPLL_STATUS.SYS=1 - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_MEDT_S_Bits;

/* Prediction of the Actual TRIGGER Increment Duration */
typedef struct
{
    ureg32 CDT_TX:24;            /* [23:0] Calculated duration of the current TRIGGER increment. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_CDT_TX_Bits;

/* Prediction of the Actual STATE Increment Duration */
typedef struct
{
    ureg32 CDT_SX:24;            /* [23:0] Calculated duration of the current STATE increment. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_CDT_SX_Bits;

/* Prediction of the Nominal TRIGGER Increment Duration */
typedef struct
{
    ureg32 CDT_TX_NOM:24;        /* [23:0] Calculated duration of the current nominal TRIGGER event. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_CDT_TX_NOM_Bits;

/* Prediction of the Nominal STATE Increment Duration */
typedef struct
{
    ureg32 CDT_SX_NOM:24;        /* [23:0] Calculated duration of the current nominal STATE event. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_CDT_SX_NOM_Bits;

/* TRIGGER Locking Range */
typedef struct
{
    ureg32 TLR:8;                /* [7:0] Value is to be multiplied with the last nominal TRIGGER duration in order to get the range for the next TRIGGER event without setting DPLL_STATUS.TOR. - RW */
    ureg32 NOT_USED:16;          /* [23:8] Not used - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_TLR_Bits;

/* STATE Locking Range */
typedef struct
{
    ureg32 SLR:8;                /* [7:0] Value is to be multiplied with the last nominal STATE duration in order to get the range for the next STATE event without setting DPLL_STATUS.SOR - RW */
    ureg32 NOT_USED:16;          /* [23:8] Not used - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_SLR_Bits;

/* Projected Increment Sum Relations for Action [n] */
typedef struct
{
    ureg32 DB:14;                /* [13:0] fractional part of relation between TRIGGER and STATE increments. - RW */
    ureg32 DW:10;                /* [23:14] Integer part of relation between TRIGGER and STATE increments. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_PDT_Bits;

/* Calculated Number of Sub-Pulses between two nominal STATE Events for DPLL_CTRL_1.SMC = 0 */
typedef struct
{
    ureg32 MLS1:18;              /* [17:0] Number of pulses between two STATE events (to be set and updated by the CPU). - RW */
    ureg32 NOT_USED:6;           /* [23:18] Not used - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_MLS1_Bits;

/* Calculated Number of Sub-Pulses between two nominal STATE Events for DPLL_CTRL_1.SMC=1 and RMO=1 */
typedef struct
{
    ureg32 MLS2:18;              /* [17:0] Number of pulses between two STATE events (to be set and updated by the CPU). - RW */
    ureg32 NOT_USED:6;           /* [23:18] Not used - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_MLS2_Bits;

/* Number of SUB_INC1 pulses in continuous mode */
typedef struct
{
    ureg32 CNT_NUM_1:24;         /* [23:0] Counter for number of SUB_INC1 pulses; Number of pulses in continuous mode for a nominal increment in normal and emergency mode for SUB_INC1 - given and updated by CPU only. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_CNT_NUM_1_Bits;

/* Number of SUB_INC2 pulses in continuous mode */
typedef struct
{
    ureg32 CNT_NUM_2:24;         /* [23:0] Counter for number of SUB_INC2 pulses; Number of pulses in continuous mode for a nominal increment in normal and emergency mode for SUB_INC2 - given and updated by CPU only. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_CNT_NUM_2_Bits;

/* Plausibility Value of Next TRIGGER Slope */
typedef struct
{
    ureg32 PVT:24;               /* [23:0] Plausibility value of next active TRIGGER slope. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_PVT_Bits;

/* Actual Calculated Position Stamp of TRIGGER */
typedef struct
{
    ureg32 PSTC:24;              /* [23:0] Calculated position stamp of last TRIGGER input; - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_PSTC_Bits;

/* Actual Calculated Position Stamp of STATE */
typedef struct
{
    ureg32 PSSC:24;              /* [23:0] Calculated position stamp for the last STATE input; - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_PSSC_Bits;

/* Measured Position Stamp at Last TRIGGER Input */
typedef struct
{
    ureg32 PSTM:24;              /* [23:0] Position stamp of TRIGGER - measured; Measured position stamp of last active TRIGGER input. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_PSTM_Bits;

/* Measured Position Stamp at Last but one TRIGGER Input */
typedef struct
{
    ureg32 PSTM_OLD:24;          /* [23:0] Last but one position stamp of TRIGGER - measured; Measured position stamp of last but one active TRIGGER input. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_PSTM_OLD_Bits;

/* Measured Position Stamp at Last STATE Input */
typedef struct
{
    ureg32 PSSM:24;              /* [23:0] Position stamp of STATE - measured; Measured position stamp of last active STATE input. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_PSSM_Bits;

/* Measured Position Stamp at Last but one STATE Input */
typedef struct
{
    ureg32 PSSM_OLD:24;          /* [23:0] Last but one position stamp of STATE - measured; Measured position stamp of last but one active STATE input. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_PSSM_OLD_Bits;

/* Number of Pulses to be sent in Normal Mode */
typedef struct
{
    ureg32 NMB_T:16;             /* [15:0] Number of pulses for TRIGGER; calculated number of pulses in normal mode for the current TRIGGER increment. - RW */
    ureg32 NOT_USED:8;           /* [23:16] Not used - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_NMB_T_Bits;

/* Number of Pulses to be sent in Emergency Mode */
typedef struct
{
    ureg32 NMB_S:20;             /* [19:0] NMB_S: Number of pulses for STATE; calculated number of pulses in emergency mode for the current STATE increment. - RW */
    ureg32 NOT_USED:4;           /* [23:20] Not used - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_NMB_S_Bits;

/* Reciprocal Values of the Nominal STATE Increment Duration in FULL_SCALE for maximum [p] entries in profile for STATE (DPLL_ADT_S[p]) */
typedef struct
{
    ureg32 RDT_S:24;             /* [23:0] Reciprocal difference time of STATE; nominal reciprocal value of the number of time stamp clocks measured in the corresponding increment *2^32 while only the lower 24 bits are used; no gap considered. The LSB is rounded up when the next truncated bit is 1. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_RDT_S_Bits;

/* Time Stamp Values of the Nominal STATE Events in FULL_SCALE for maximum [p] entries in profile for STATE (DPLL_ADT_S[p]) */
typedef struct
{
    ureg32 TSF_S:24;             /* [23:0] Time stamp field of STATE; Time stamp value of each active STATE event. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_TSF_S_Bits;

/* Adapt and Profile Values of the STATE Increments in FULL_SCALE for maximum [p] entries */
typedef struct
{
    ureg32 PD_S:16;              /* [15:0] Physical deviation of STATE; Adapt values for each nominal STATE increment in FULL_SCALE; - RW */
    ureg32 NS:6;                 /* [21:16] Number of STATE events; number of nominal STATE parts in the corresponding increment. - RW */
    ureg32 NOT_USED:2;           /* [23:22] Not used - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_ADT_S_Bits;

/* Nominal STATE Increment Duration in FULL_SCALE for maximum [p] entries in profile for STATE (DPLL_ADT_S[p]) */
typedef struct
{
    ureg32 DT_S:24;              /* [23:0] Difference time of STATE; nominal increment duration values for each STATE increment in FULL_SCALE (considering no gap). - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_DT_S_Bits;

/* Calculated Time Value to start Action [n] */
typedef struct
{
    ureg32 TSAC:24;              /* [23:0] Calculated time stamp for Action [n]  - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_TSAC_Bits;

/* Calculated Position Value to start Action [n] */
typedef struct
{
    ureg32 PSAC:24;              /* [23:0] Calculated position value for the start of Action [n]. - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_PSAC_Bits;

/* Control Bits for NOAC Actions */
typedef struct
{
    ureg32 ACB_0:5;              /* [4:0] Action Control Bits of Action [m] - reflects ACT_D[m][52:48] - [m]=4*[n] - RW */
    ureg32 reserved_5:3;         /* [7:5] Internal  reserved */
    ureg32 ACB_1:5;              /* [12:8] Action Control Bits of Action [m] - reflects ACT_D[m][52:48] - [m]=4*[n] - RW */
    ureg32 reserved_13:3;        /* [15:13] Internal  reserved */
    ureg32 ACB_2:5;              /* [20:16] Action Control Bits of Action [m] - reflects ACT_D[m][52:48] - [m]=4*[n] - RW */
    ureg32 reserved_21:3;        /* [23:21] Internal  reserved */
    ureg32 ACB_3:5;              /* [28:24] Action Control Bits of Action [m] - reflects ACT_D[m][52:48] - [m]=4*[n] - RW */
    ureg32 reserved_29:3;        /* [31:29] Internal  reserved */
} GTM_DPLL_ACB_Bits;

/* Control Register 11 */
typedef struct
{
    ureg32 SIP1:1;                   /* [0:0] Simplified increment prediction in normal mode and for the first engine in the case DPLL_CTRL_1.SMC=1. - RW */
    ureg32 ERZ1:1;                   /* [1:1] Error is assumed as zero  in normal mode and for the first engine for DPLL_CTRL_1.SMC=1. - RW */
    ureg32 PCMF1:1;                  /* [2:2] Pulse correction mode fast  for DPLL_INC_CNT1.INC_CNT1 - RW */
    ureg32 FSYL1:1;                  /* [3:3] Force Synchronization Loss of DPLL_STATUS.LOCK1. - RW */
    ureg32 INCF1:1;                  /* [4:4] DPLL_INC_CNT1.INC_CNT1 fast correction - RW */
    ureg32 PCMF1_INCCNT_B:1;         /* [5:5] No increment of DPLL_INC_CNT1.INC_CNT1 when DPLL_CTRL_11.PCMF1 active (automatic end mode). - RW */
    ureg32 ADT:1;                    /* [6:6] Correction of DPLL_DT_T_ACT.DT_T_ACT - DPLL_CDT_TX_NOM.CDT_TX_NOM_corr by PD_T - RW */
    ureg32 ADS:1;                    /* [7:7] Correction of DPLL_DT_S_ACT.DT_S_ACT - DPLL_CDT_SX_NOM.CDT_SX_NOM_corr by DPLL_ADT_S[p].PD_S - RW */
    ureg32 SIP2:1;                   /* [8:8] Simplified increment prediction  in emergency  mode and for the second engine in the case DPLL_CTRL_0.RMO=1. - RW */
    ureg32 ERZ2:1;                   /* [9:9] Error is assumed as zero  in emergency mode and for the second engine for DPLL_CTRL_1.SMC=1. - RW */
    ureg32 PCMF2:1;                  /* [10:10] Pulse correction mode fast for DPLL_INC_CNT2.INC_CNT2 - RW */
    ureg32 FSYL2:1;                  /* [11:11] Force Synchronization Loss of DPLL_STATUS.LOCK2. - RW */
    ureg32 INCF2:1;                  /* [12:12] DPLL_INC_CNT2.INC_CNT2 fast - RW */
    ureg32 PCMF2_INCCNT_B:1;         /* [13:13] No increment of DPLL_INC_CNT2.INC_CNT2 when DPLL_CTRL_11.PCMF2 active (automatic end mode). - RW */
    ureg32 STATE_EXT:1;              /* [14:14] Use of STATE engine extension - RW */
    ureg32 ACBU:1;                   /* [15:15] DPLL_CTRL_11.ACBU use; the DPLL_CTRL_11.ACBU values of PMTR are used to decide if an Action is in the past - RW */
    ureg32 WSIP1:1;                  /* [16:16] Write enable for simplified increment prediction 1. - RW */
    ureg32 WERZ1:1;                  /* [17:17] Write enable for error zero 1. - RW */
    ureg32 WPCMF1:1;                 /* [18:18] Write enable for pulse correction mode fast 1 - RW */
    ureg32 WFSYL1:1;                 /* [19:19] Write enable for Force Synchronization Loss 1. - RW */
    ureg32 WINCF1:1;                 /* [20:20] Write enable for DPLL_INC_CNT1.INC_CNT1 fast - RW */
    ureg32 WPCMF1_INCCNT_B:1;        /* [21:21] Write enable of DPLL_CTRL_11.PCMF1_INCCNT_B - RW */
    ureg32 WADT:1;                   /* [22:22] Write enable of DPLL_CTRL_11.ADT - RW */
    ureg32 WADS:1;                   /* [23:23] Write enable of DPLL_CTRL_11.ADS - RW */
    ureg32 WSIP2:1;                  /* [24:24] Write enable for simplified increment prediction 2. - RW */
    ureg32 WERZ2:1;                  /* [25:25] Write enable for error zero 2. - RW */
    ureg32 WPCMF2:1;                 /* [26:26] Write enable for pulse correction mode fast 2 - RW */
    ureg32 WFSYL2:1;                 /* [27:27] Write enable for Force Synchronization Loss 2. - RW */
    ureg32 WINCF2:1;                 /* [28:28] Write enable for DPLL_INC_CNT2.INC_CNT2 fast - RW */
    ureg32 WPCMF2_INCCNT_B:1;        /* [29:29] Write enable of DPLL_CTRL_11.PCMF2_INCCNT_B - RW */
    ureg32 WSTATE_EXT:1;             /* [30:30] Write enable of DPLL_CTRL_11.STATE_EXT - RW */
    ureg32 WACBU:1;                  /* [31:31] Write enable for DPLL_CTRL_11.ACBU use; the DPLL_CTRL_11.ACBU values of DPLL_ID_PMTR_[n].ID_PMTR are used to decide if an Action is in the past - RW */
} GTM_DPLL_CTRL_11_Bits;

/* Measured TRIGGER Hold Time Value 2 */
typedef struct
{
    ureg32 THVAL:24;             /* [23:0] Measured last pulse time from active to inactive slope of TRIGGER after correction of input slope filter delays  - RO */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_THVAL2_Bits;

/* TRIGGER input delay */
typedef struct
{
    ureg32 TIDEL:24;             /* [23:0] TRIGGER input delay - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_TIDEL_Bits;

/* STATE input delay */
typedef struct
{
    ureg32 SIDEL:24;             /* [23:0] STATE input delay - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_SIDEL_Bits;

/* STATE Time Stamp Field Offset at Synchronization Time */
typedef struct
{
    ureg32 APS_1C2_EXT:7;           /* [6:0] Address pointer 1c2 extension; this offset value determines - by which value the DPLL_APS_EXT.APS_1C2 is changed at the time of synchronization; set by CPU before the synchronization is performed. - RW */
    ureg32 reserved_7:8;            /* [14:7] Internal  reserved */
    ureg32 APS_1C2_STATUS:1;        /* [15:15] Address pointer 1c2 status; set by CPU before the synchronization is performed. The value is cleared automatically when the DPLL_APS_SYNC_EXT.APS_1C2_OLD value is written. - RW */
    ureg32 APS_1C2_OLD:7;           /* [22:16] Address pointer STATE for RAM region 1c2 at synchronization time; this value is set by the current DPLL_APS_EXT.APS_1C2 value when the synchronization takes place for the first active STATE event after writing DPLL_APS_1C3_EXT.APS_1C3 but before adding the offset value DPLL_APS_SYNC_EXT.APS_1C2_EXT (that means: when DPLL_APS_SYNC_EXT.APS_1C2_STATUS=1). - RW */
    ureg32 reserved_23:9;           /* [31:23] Internal  reserved */
} GTM_DPLL_APS_SYNC_EXT_Bits;

/* STATE Time Stamp Field Offset at Synchronization Time */
typedef struct
{
    ureg32 SNU:6;                 /* [5:0] STATE number; SNU+1 is number of nominal STATE events in HALF_SCALE (1...32). - RW */
    ureg32 reserved_6:10;         /* [15:6] Internal  reserved */
    ureg32 SYN_NS:6;              /* [21:16] Synchronization number of STATE; summarized number of virtual increments in HALF_SCALE - RW */
    ureg32 reserved_22:10;        /* [31:22] Internal  reserved */
} GTM_DPLL_CTRL_EXT_Bits;

/* Actual RAM Pointer Address for STATE */
typedef struct
{
    ureg32 reserved_0:1;          /* [0:0] Internal  reserved */
    ureg32 WAPS:1;                /* [1:1] Write bit for address pointer DPLL_APS_EXT.APS - read as zero. - RW */
    ureg32 APS:7;                 /* [8:2] Address pointer STATE; Actual RAM pointer address value for DPLL_DT_S[p] and DPLL_RDT_S[p] - RW */
    ureg32 reserved_9:4;          /* [12:9] Internal  reserved */
    ureg32 WAPS_1C2:1;            /* [13:13] Write bit for address pointer DPLL_APS_EXT.APS_1C2 - read as zero. - RW */
    ureg32 APS_1C2:7;             /* [20:14] Address pointer STATE for RAM region 1c2; Actual RAM pointer address value for DPLL_TSF_S[p]. - RW */
    ureg32 reserved_21:11;        /* [31:21] Internal  reserved */
} GTM_DPLL_APS_EXT_Bits;

/* Actual RAM Pointer Address for RAM region 1c3 (DPLL_CTRL_11.STATE_EXT=1) */
typedef struct
{
    ureg32 reserved_0:2;         /* [1:0] Internal  reserved */
    ureg32 APS_1C3:7;            /* [8:2] Address pointer STATE for RAM region 1c3; Actual RAM pointer address value for DPLL_ADT_S[p] - RW */
    ureg32 reserved_9:23;        /* [31:9] Internal  reserved */
} GTM_DPLL_APS_1C3_EXT_Bits;

/* Status of the state machine states */
typedef struct
{
    ureg32 STA_T:8;              /* [7:0] Status of TRIGGER state machine; state binary coded  - RO */
    ureg32 reserved_8:1;         /* [8:8] Internal  reserved */
    ureg32 CNT_T:3;              /* [11:9] Count TRIGGER; this reflects the count of active TRIGGER slopes (mod8). - RO */
    ureg32 STA_S:8;              /* [19:12] Status of STATE state machine; state binary coded  - RO */
    ureg32 reserved_20:1;        /* [20:20] Internal  reserved */
    ureg32 CNT_S:3;              /* [23:21] Count STATE; this reflects the count of active STATE slopes (mod8). - RO */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_STA_Bits;

/* Start value of ADD_IN_ADDER1  */
typedef struct
{
    ureg32 INCF1_OFFSET:24;        /* [23:0] Start value of the ADD_IN_ADDER1 - RW */
    ureg32 reserved_24:8;          /* [31:24] Internal  reserved */
} GTM_DPLL_INCF1_OFFSET_Bits;

/* Start value of the ADD_IN_ADDER2 */
typedef struct
{
    ureg32 INCF2_OFFSET:24;        /* [23:0] Start value of the ADD_IN_ADDER2 - RW */
    ureg32 reserved_24:8;          /* [31:24] Internal  reserved */
} GTM_DPLL_INCF2_OFFSET_Bits;

/* Start value of DT_T_ACT */
typedef struct
{
    ureg32 DT_T_START:24;        /* [23:0] Start value of DPLL_DT_T_ACT for the first increment after DPLL_CTRL_11.SIP1 is set to 1 - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_DT_T_START_Bits;

/* Start value of DT_S_ACT */
typedef struct
{
    ureg32 DT_S_START:24;        /* [23:0] Start value of DPLL_DT_S_ACT for the first increment after DPLL_CTRL_11.SIP2 is set to 1 - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_DT_S_START_Bits;

/* Notify values for DPLL_STA */
typedef struct
{
    ureg32 STA_NOTIFY_T:8;        /* [7:0] Notify value for DPLL_STA.STA_T. - RW */
    ureg32 STA_NOTIFY_S:8;        /* [15:8] Notify value for DPLL_STA.STA_S. - RW */
    ureg32 reserved_16:16;        /* [31:16] Internal  reserved */
} GTM_DPLL_STA_MASK_Bits;

/* DPLL STA Flags */
typedef struct
{
    ureg32 STA_FLAG_T:1;           /* [0:0] Flag according to DPLL_MASK.STA_NOTIFY_T - RW */
    ureg32 reserved_1:7;           /* [7:1] Internal  reserved */
    ureg32 STA_FLAG_S:1;           /* [8:8] Flag according to DPLL_STA_MASK.STA_NOTIFY_S - RW */
    ureg32 INC_CNT1_FLAG:1;        /* [9:9] Flag according to DPLL_INC_CNT1_MASK.INC_CNT1_NOTIFY - RW */
    ureg32 INC_CNT2_FLAG:1;        /* [10:10] Flag according to DPLL_INC_CNT2_MASK.INC_CNT2_NOTIFY - RW */
    ureg32 reserved_11:21;         /* [31:11] Internal  reserved */
} GTM_DPLL_STA_FLAG_Bits;

/* Notify value of DPLL_INC_CNT1 */
typedef struct
{
    ureg32 INC_CNT1_NOTIFY:24;        /* [23:0] Notify value for DPLL_INC_CNT1.INC_CNT1. - RW */
    ureg32 reserved_24:8;             /* [31:24] Internal  reserved */
} GTM_DPLL_INC_CNT1_MASK_Bits;

/* Notify value of DPLL_INC_CNT2 */
typedef struct
{
    ureg32 INC_CNT2_NOTIFY:24;        /* [23:0] Notify value for DPLL_INC_CNT2.INC_CNT2 of register DPLL_INC_CNT2. - RW */
    ureg32 reserved_24:8;             /* [31:24] Internal  reserved */
} GTM_DPLL_INC_CNT2_MASK_Bits;

/* Number of Recent STATE Events used for Calculations */
typedef struct
{
    ureg32 SYN_S:7;              /* [6:0] Number of real and virtual events to be considered for the current increment. - RW */
    ureg32 reserved_7:9;         /* [15:7] Internal  reserved */
    ureg32 SYN_S_OLD:7;          /* [22:16] Number of real and virtual events to be considered for the last increment. - RW */
    ureg32 reserved_23:7;        /* [29:23] Internal  reserved */
    ureg32 WSYN:1;               /* [30:30] Write control bit for DPLL_NUSC_EXT1.SYN_S and DPLL_NUSC_EXT1.SYN_S_OLD; read as zero. - RW */
    ureg32 reserved_31:1;        /* [31:31] Internal  reserved */
} GTM_DPLL_NUSC_EXT1_Bits;

/* Number of Recent STATE Events used for Calculations */
typedef struct
{
    ureg32 NUSE:7;               /* [6:0] Number of recent STATE events used for SUB_INC1 and SUB_INC1 calculations modulo 2*(DPLL_CTRL_0.SNU+1). - RW */
    ureg32 reserved_7:8;         /* [14:7] Internal  reserved */
    ureg32 FSS:1;                /* [15:15] FULL_SCALE of STATE; this value is to be set - when DPLL_NUSC_EXT2.NUSE is set to FULL_SCALE - RW */
    ureg32 VSN:7;                /* [22:16] Virtual STATE number; number of virtual STATE increments in the current DPLL_NUSC_EXT2.NUSE region. - RW */
    ureg32 reserved_23:6;        /* [28:23] Internal  reserved */
    ureg32 WNUS:1;               /* [29:29] Write control bit for DPLL_NUSC_EXT2.NUSE; read as zero. - RW */
    ureg32 reserved_30:1;        /* [30:30] Internal  reserved */
    ureg32 WVSN:1;               /* [31:31] Write control bit for DPLL_NUSC_EXT2.VSN; read as zero. - RW */
} GTM_DPLL_NUSC_EXT2_Bits;

/* Minmum value of predicted nominal increment of TRIGGER */
typedef struct
{
    ureg32 CTN_MIN:24;           /* [23:0] DPLL_CDT_TX_NOM.CDT_TX_NOM min value - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_CTN_MIN_Bits;

/* Maximum value of predicted nominal increment of TRIGGER */
typedef struct
{
    ureg32 CTN_MAX:24;           /* [23:0] DPLL_CDT_TX_NOM.CDT_TX_NOM max value - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_CTN_MAX_Bits;

/* Minmum value of predicted nominal increment of STATE */
typedef struct
{
    ureg32 CSN_MIN:24;           /* [23:0] DPLL_CDT_SX_NOM.CDT_SX_NOM min value - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_CSN_MIN_Bits;

/* Maximum value of predicted nominal increment of STATE */
typedef struct
{
    ureg32 CSN_MAX:24;           /* [23:0] DPLL_CDT_SX_NOM.CDT_SX_NOM max value - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_CSN_MAX_Bits;

/* Software triggered input events */
typedef struct
{
    ureg32 TRIG_EVENT:1;          /* [0:0] Software triggered input event for TRIGGER - RW */
    ureg32 WTRIG_EVENT:1;         /* [1:1] Write enable for DPLL_SW_TRIG.TRIG_EVENT - RW */
    ureg32 TRIG_LEVEL:1;          /* [2:2] Input signal level of software triggered input event for TRIGGER - RW */
    ureg32 WTRIG_LEVEL:1;         /* [3:3] Write enable for DPLL_SW_TRIG.TRIG_LEVEL - RW */
    ureg32 STATE_EVENT:1;         /* [4:4] Software triggered input event for STATE - RW */
    ureg32 WSTATE_EVENT:1;        /* [5:5] Write enable for DPLL_SW_TRIG.STATE_EVENT - RW */
    ureg32 STATE_LEVEL:1;         /* [6:6] Input signal level of software triggered input event for STATE - RW */
    ureg32 WSTATE_LEVEL:1;        /* [7:7] Write enable for DPLL_SW_TRIG.STATE_LEVEL - RW */
    ureg32 reserved_8:24;         /* [31:8] Internal  reserved */
} GTM_DPLL_SW_TRIG_Bits;

/* Missing pulses of TRIGGER */
typedef struct
{
    ureg32 MP_T:24;              /* [23:0] Number of missing pulses of the SUB_INC1 pulses in automatic end mode (DPLL_CTRL_1.DMO=0). - RO */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_MP_T_Bits;

/* Missing pulses of STATE */
typedef struct
{
    ureg32 MP_S:24;              /* [23:0] Number of missing pulses of the SUB_INC1/SUB_INC2 pulses in automatic end mode (DPLL_CTRL_1.DMO=0). - RO */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_MP_S_Bits;

/* DPLL control register 12 */
typedef struct
{
    ureg32 SUBINC_MUX_SEL:1;         /* [0:0] Selection of DPLL sub increment source for CCM[0]_TBU_TS1 angle base. - RW */
    ureg32 reserved_1:15;            /* [15:1] Internal  reserved */
    ureg32 WSUBINC_MUX_SEL:1;        /* [16:16] Write enable for DPLL_CTRL_12.SUBINC_MUX_SEL. - RW */
    ureg32 reserved_17:15;           /* [31:17] Internal  reserved */
} GTM_DPLL_CTRL_12_Bits;

/* DPLL memory RR2 */
typedef struct
{
    ureg32 DATA:24;              /* [23:0] Data - RW */
    ureg32 reserved_24:8;        /* [31:24] Internal  reserved */
} GTM_DPLL_RR2_Bits;

/* MCS[i] memory region */
typedef struct
{
    ureg32 DATA:32;        /* [31:0] MCS memory location - RW */
} GTM_MCS_MEM_Bits;

/* TIM[i] input select register */
typedef struct
{
    ureg32 CH0SEL:4;        /* [3:0] TIM channel 0 input selection - RW */
    ureg32 CH1SEL:4;        /* [7:4] TIM channel 1 input selection - RW */
    ureg32 CH2SEL:4;        /* [11:8] TIM channel 2 input selection - RW */
    ureg32 CH3SEL:4;        /* [15:12] TIM channel 3 input selection - RW */
    ureg32 CH4SEL:4;        /* [19:16] TIM channel 4 input selection - RW */
    ureg32 CH5SEL:4;        /* [23:20] TIM channel 5 input selection - RW */
    ureg32 CH6SEL:4;        /* [27:24] TIM channel 6 input selection - RW */
    ureg32 CH7SEL:4;        /* [31:28] TIM channel 7 input selection - RW */
} GTM_TIMINMUX_Bits;

/* TOM output select register */
typedef struct
{
    ureg32 SEL0:4;        /* [3:0] TOUT(n*8 + 0) output selection - RW */
    ureg32 SEL1:4;        /* [7:4] TOUT(n*8 + 1) output selection - RW */
    ureg32 SEL2:4;        /* [11:8] TOUT(n*8 + 2) output selection - RW */
    ureg32 SEL3:4;        /* [15:12] TOUT(n*8 + 3) output selection - RW */
    ureg32 SEL4:4;        /* [19:16] TOUT(n*8 + 4) output selection - RW */
    ureg32 SEL5:4;        /* [23:20] TOUT(n*8 + 5) output selection - RW */
    ureg32 SEL6:4;        /* [27:24] TOUT(n*8 + 6) output selection - RW */
    ureg32 SEL7:4;        /* [31:28] TOUT(n*8 + 7) output selection - RW */
} GTM_TOUTMUX_Bits;

/* DSADC input select register */
typedef struct
{
    ureg32 INSEL0:4;        /* [3:0] Input selection for DSADCn GTM connection - RW */
    ureg32 INSEL1:4;        /* [7:4] Input selection for DSADCn GTM connection - RW */
    ureg32 INSEL2:4;        /* [11:8] Input selection for DSADCn GTM connection - RW */
    ureg32 INSEL3:4;        /* [15:12] Input selection for DSADCn GTM connection - RW */
    ureg32 INSEL4:4;        /* [19:16] Input selection for DSADCn GTM connection - RW */
    ureg32 INSEL5:4;        /* [23:20] Input selection for DSADCn GTM connection - RW */
    ureg32 INSEL6:4;        /* [27:24] Input selection for DSADCn GTM connection - RW */
    ureg32 INSEL7:4;        /* [31:28] Input selection for DSADCn GTM connection - RW */
} GTM_DSADCINMUX_Bits;

/* DSADC output select register */
typedef struct
{
    ureg32 SEL0:4;            /* [3:0] Output selection for DSADC0 GTM connection - RW */
    ureg32 SEL1:4;            /* [7:4] Output selection for DSADC1 GTM connection - RW */
    ureg32 SEL2:4;            /* [11:8] Output selection for DSADC2 GTM connection - RW */
    ureg32 SEL3:4;            /* [15:12] Output selection for DSADC3 GTM connection - RW */
    ureg32 SEL4:4;            /* [19:16] Output selection for DSADC4 GTM connection (THA6412 only) - RW  */
    ureg32 SEL5:4;            /* [23:20] Output selection for DSADC5 GTM connection (THA6412 only) - RW */
    ureg32 SEL6:4;            /* [27:24] Output selection for DSADC6 GTM connection (THA6412 only) - RW */
    ureg32 SEL7:4;            /* [31:28] Output selection for DSADC7 GTM connection (THA6412 only) - RW */
} GTM_DSADCOUTMUX_Bits;

/* DSADC output select 1 register (THA6412 only) */
typedef struct
{
    ureg32 SEL8:4;            /* [3:0] Output selection for DSADC8 GTM connection - RW */
    ureg32 SEL9:4;            /* [7:4] Output selection for DSADC9 GTM connection - RW */
    ureg32 reserved_8:24;   /* [31:8] Internal reserved */
} GTM_DSADCOUTMUX1_Bits;

/* ADCTRIG[i] output select 0 register */
typedef struct
{
    ureg32 SEL0:4;            /* [3:0] Output selection for GTM to ADC0 connection - RW */
    ureg32 SEL1:4;            /* [7:4] Output selection for GTM to ADC1 connection - RW */
    ureg32 SEL2:4;            /* [11:8] Output selection for GTM to ADC2 connection - RW */
    ureg32 SEL3:4;            /* [15:12] Output selection for GTM to ADC3 connection - RW */
    ureg32 SEL4:4;            /* [19:16] Output selection for GTM to ADC4 connection - RW */
    ureg32 SEL5:4;            /* [23:20] Output selection for GTM to ADC5 connection - RW */
    ureg32 SEL6:4;            /* [27:24] Output selection for GTM to ADC6 connection - RW */
    ureg32 SEL7:4;            /* [31:28] Output selection for GTM to ADC7 connection - RW */
} GTM_ADCTRIG_OUTMUX0_Bits;

/* ADCTRIG[i] output select 1 register */
typedef struct
{
    ureg32 SEL0:4;            /* [3:0] Output selection for GTM to ADC0 connection - RW */
    ureg32 SEL1:4;            /* [7:4] Output selection for GTM to ADC1 connection - RW */
    ureg32 SEL2:4;            /* [11:8] Output selection for GTM to ADC2 connection - RW */
    ureg32 SEL3:4;            /* [15:12] Output selection for GTM to ADC3 connection - RW */
    ureg32 reserved_16:16;  /* [31:16] Internal  reserved */
} GTM_ADCTRIG_OUTMUX1_Bits;

/* Data exchange output control register */
typedef struct
{
    ureg32 OUT0:1;            /* [0:0] Output 00 control - RW */
    ureg32 OUT1:1;            /* [1:1] Output 01 control - RW */
    ureg32 OUT2:1;            /* [2:2] Output 02 control - RW */
    ureg32 OUT3:1;            /* [3:3] Output 03 control - RW */
    ureg32 OUT4:1;            /* [4:4] Output 04 control (THA6412 only) - RW */
    ureg32 OUT5:1;            /* [5:5] Output 05 control (THA6412 only) - RW */
    ureg32 OUT6:1;            /* [6:6] Output 06 control (THA6412 only) - RW */
    ureg32 OUT7:1;            /* [7:7] Output 07 control (THA6412 only) - RW */
    ureg32 reserved_8:24;     /* [31:8] Internal  reserved */
} GTM_DEXOUTCON_Bits;

/* Trigger output register */
typedef struct
{
    ureg32 TRIG0:2;            /* [1:0] Trigger 0 (w) */
    ureg32 TRIG1:2;            /* [3:2] Trigger 1 (w) */
    ureg32 TRIG2:2;            /* [5:4] Trigger 2 (w) */
    ureg32 TRIG3:2;            /* [7:6] Trigger 3 (w) */
    ureg32 TRIG4:2;            /* [9:8] Trigger 4 (w) */
    ureg32 TRIG5:2;            /* [11:10] Trigger 5 (w) */
    ureg32 TRIG6:2;            /* [13:12] Trigger 6 (w) */
    ureg32 TRIG7:2;            /* [15:14] Trigger 7 (w) */
    ureg32 reserved_16:16;     /* [31:16] Internal  reserved */
} GTM_TRIGOUTCON_Bits;

/* Interrupt output register */
typedef struct
{
    ureg32 INT0:2;            /* [1:0] Interrupt trigger request 0 (w) */
    ureg32 reserved_2:30;     /* [31:2] Internal  reserved */
} GTM_INTOUTCON_Bits;

/* Trigger output select register */
typedef struct
{
    ureg32 SEL0:4;            /* [3:0] Selects which MCS triggers go to FC0BFDAT/SEL - RW */
    ureg32 SEL1:4;            /* [7:4] Selects which MCS triggers go to FC1BFDAT/SEL - RW */
    ureg32 SEL2:4;            /* [11:8] Selects which MCS triggers go to FC2BFDAT/SEL (THA6412 only) - RW */
    ureg32 SEL3:4;            /* [15:12] Selects which MCS triggers go to FC3BFDAT/SEL (THA6412 only) - RW */
    ureg32 reserved_16:16;    /* [31:16] Internal  reserved */
} GTM_TRIGOUTMUX_Bits;

/* MCS interrupt status register */
typedef struct
{
    ureg32 MCS0:1;            /* [0:0] MCS0 RAM0 interrupt status flag - RO */
    ureg32 MCS1:1;            /* [1:1] MCS1 RAM0 interrupt status flag - RO */
    ureg32 MCS2:1;            /* [2:2] MCS2 RAM0 interrupt status flag - RO */
    ureg32 MCS3:1;            /* [3:3] MCS3 RAM0 interrupt status flag - RO */
    ureg32 MCS4:1;            /* [4:4] MCS4 RAM0 interrupt status flag (THA6412 only) - RO */
    ureg32 MCS5:1;            /* [5:5] MCS5 RAM0 interrupt status flag (THA6412 only) - RO */
    ureg32 MCS6:1;            /* [6:6] MCS6 RAM0 interrupt status flag (THA6412 only) - RO */
    ureg32 MCS7:1;            /* [7:7] MCS7 RAM0 interrupt status flag (THA6412 only) - RO */
    ureg32 reserved_8:24;     /* [31:8] Internal  reserved */
} GTM_INTSTS_Bits;

/* MCS interrupt clear register */
typedef struct
{
    ureg32 MCS0:1;            /* [0:0] MCS0 RAM0 interrupt status clear bit - W1C */
    ureg32 MCS1:1;            /* [1:1] MCS1 RAM0 interrupt status clear bit - W1C */
    ureg32 MCS2:1;            /* [2:2] MCS2 RAM0 interrupt status clear bit - W1C */
    ureg32 MCS3:1;            /* [3:3] MCS3 RAM0 interrupt status clear bit - W1C */
    ureg32 MCS4:1;            /* [4:4] MCS4 RAM0 interrupt status clear bit (THA6412 only) - W1C */
    ureg32 MCS5:1;            /* [5:5] MCS5 RAM0 interrupt status clear bit (THA6412 only) - W1C */
    ureg32 MCS6:1;            /* [6:6] MCS6 RAM0 interrupt status clear bit (THA6412 only) - W1C */
    ureg32 MCS7:1;            /* [7:7] MCS7 RAM0 interrupt status clear bit (THA6412 only) - W1C */
    ureg32 reserved_8:24;     /* [31:8] Internal  reserved */
} GTM_INTSTSCLR_Bits;

/* Data exchange input control register */
typedef struct
{
    ureg32 IN0:1;            /* [0:0] Input 00 control - RW */
    ureg32 IN1:1;            /* [1:1] Input 01 control - RW */
    ureg32 IN2:1;            /* [2:2] Input 02 control - RW */
    ureg32 IN3:1;            /* [3:3] Input 03 control - RW */
    ureg32 IN4:1;            /* [4:4] Input 04 control (THA6412 only) - RW */
    ureg32 IN5:1;            /* [5:5] Input 05 control (THA6412 only) - RW */
    ureg32 IN6:1;            /* [6:6] Input 06 control (THA6412 only) - RW */
    ureg32 IN7:1;            /* [7:7] Input 07 control (THA6412 only) - RW */
    ureg32 reserved_8:8;     /* [15:8] Internal  reserved */
    ureg32 DSS0:1;             /* [16:16] Data source select 00 control - RW */
    ureg32 DSS1:1;             /* [17:17] Data source select 01 control - RW */
    ureg32 DSS2:1;             /* [18:18] Data source select 02 control - RW */
    ureg32 DSS3:1;             /* [19:19] Data source select 03 control - RW */
    ureg32 DSS4:1;             /* [20:20] Data source select 04 control (THA6412 only) - RW */
    ureg32 DSS5:1;             /* [21:21] Data source select 05 control (THA6412 only) - RW */
    ureg32 DSS6:1;             /* [22:22] Data source select 06 control (THA6412 only) - RW */
    ureg32 DSS7:1;             /* [23:23] Data source select 07 control (THA6412 only) - RW */
    ureg32 reserved_24:8;    /* [31:24] Internal  reserved */
} GTM_DEXINCON_Bits;

/* Data input register */
typedef struct
{
    ureg32 DATA:32;            /* [31:0] Data - RW */
} GTM_DATAIN_Bits;

/* MSC set [i] control 0 register */
typedef struct
{
    ureg32 MUX0:5;            /* [4:0] Set x[0] input selection - RW */
    ureg32 reserved_5:3;      /* [7:5] Internal  reserved */
    ureg32 MUX1:5;            /* [12:8] Set x[1] input selection - RW */
    ureg32 reserved_13:3;     /* [15:13] Internal  reserved */
    ureg32 MUX2:5;            /* [20:16] Set x[2] input selection - RW */
    ureg32 reserved_21:3;     /* [23:21] Internal  reserved */
    ureg32 MUX3:5;            /* [28:24] Set x[3] input selection - RW */
    ureg32 reserved_29:3;     /* [31:29] Internal  reserved */
} GTM_MSCSET_MUX0_Bits;

/* MSC set [i] control 1 register */
typedef struct
{
    ureg32 MUX4:5;            /* [4:0] Set x[4] input selection - RW */
    ureg32 reserved_5:3;      /* [7:5] Internal  reserved */
    ureg32 MUX5:5;            /* [12:8] Set x[5] input selection - RW */
    ureg32 reserved_13:3;     /* [15:13] Internal  reserved */
    ureg32 MUX6:5;            /* [20:16] Set x[6] input selection - RW */
    ureg32 reserved_21:3;     /* [23:21] Internal  reserved */
    ureg32 MUX7:5;            /* [28:24] Set x[7] input selection - RW */
    ureg32 reserved_29:3;     /* [31:29] Internal  reserved */
} GTM_MSCSET_MUX1_Bits;

/* MSC set [i] control 2 register */
typedef struct
{
    ureg32 MUX8:5;            /* [4:0] Set x[8] input selection - RW */
    ureg32 reserved_5:3;      /* [7:5] Internal  reserved */
    ureg32 MUX9:5;            /* [12:8] Set x[9] input selection - RW */
    ureg32 reserved_13:3;     /* [15:13] Internal  reserved */
    ureg32 MUX10:5;           /* [20:16] Set x[10] input selection - RW */
    ureg32 reserved_21:3;     /* [23:21] Internal  reserved */
    ureg32 MUX11:5;           /* [28:24] Set x[11] input selection - RW */
    ureg32 reserved_29:3;     /* [31:29] Internal  reserved */
} GTM_MSCSET_MUX2_Bits;

/* MSC set [i] control 3 register */
typedef struct
{
    ureg32 MUX12:5;           /* [4:0] Set x[12] input selection - RW */
    ureg32 reserved_5:3;      /* [7:5] Internal  reserved */
    ureg32 MUX13:5;           /* [12:8] Set x[13] input selection - RW */
    ureg32 reserved_13:3;     /* [15:13] Internal  reserved */
    ureg32 MUX14:5;           /* [20:16] Set x[14] input selection - RW */
    ureg32 reserved_21:3;     /* [23:21] Internal  reserved */
    ureg32 MUX15:5;           /* [28:24] Set x[15] input selection - RW */
    ureg32 reserved_29:3;     /* [31:29] Internal  reserved */
} GTM_MSCSET_MUX3_Bits;

/* MSC0 input low multiplex register */
typedef struct
{
    ureg32 MUX0:2;           /* [1:0] GTM MSC0 output multiplexing - RW */
    ureg32 MUX1:2;           /* [3:2] GTM MSC0 output multiplexing - RW */
    ureg32 MUX2:2;           /* [5:4] GTM MSC0 output multiplexing - RW */
    ureg32 MUX3:2;           /* [7:6] GTM MSC0 output multiplexing - RW */
    ureg32 MUX4:2;           /* [9:8] GTM MSC0 output multiplexing - RW */
    ureg32 MUX5:2;           /* [11:10] GTM MSC0 output multiplexing - RW */
    ureg32 MUX6:2;           /* [13:12] GTM MSC0 output multiplexing - RW */
    ureg32 MUX7:2;           /* [15:14] GTM MSC0 output multiplexing - RW */
    ureg32 MUX8:2;           /* [17:16] GTM MSC0 output multiplexing - RW */
    ureg32 MUX9:2;           /* [19:18] GTM MSC0 output multiplexing - RW */
    ureg32 MUX10:2;          /* [21:20] GTM MSC0 output multiplexing - RW */
    ureg32 MUX11:2;          /* [23:22] GTM MSC0 output multiplexing - RW */
    ureg32 MUX12:2;          /* [25:24] GTM MSC0 output multiplexing - RW */
    ureg32 MUX13:2;          /* [27:26] GTM MSC0 output multiplexing - RW */
    ureg32 MUX14:2;          /* [29:28] GTM MSC0 output multiplexing - RW */
    ureg32 MUX15:2;          /* [31:30] GTM MSC0 output multiplexing - RW */
} GTM_MSCMUX_Bits;

/* DTM_AUX input low multiplex register */
typedef struct
{
    ureg32 MUXA0:2;            /* [1:0] CDTM0_DTM4_AUX input multiplexing(ATOM0_CH0...3) - RW */
    ureg32 MUXA1:2;            /* [3:2] CDTM1_DTM4_AUX input multiplexing(ATOM1_CH0...3) - RW */
    ureg32 MUXA2:2;            /* [5:4] CDTM2_DTM4_AUX input multiplexing(ATOM2_CH0...3) - RW */
    ureg32 MUXA3:2;            /* [7:6] CDTM3_DTM4_AUX input multiplexing(ATOM3_CH0...3) - RW */
    ureg32 MUXA4:2;            /* [9:8] CDTM4_DTM4_AUX input multiplexing(ATOM4_CH0...3) (THA6412 only) - RW */
    ureg32 MUXA5:2;            /* [11:10] CDTM5_DTM4_AUX input multiplexing(ATOM5_CH0...3) (THA6412 only) - RW */
    ureg32 reserved_12:4;    /* [15:12] Internal  reserved */
    ureg32 MUXT0:2;            /* [17:16] CDTM0_DTM0_AUX input multiplexing(TOM0_CH0...3) - RW */
    ureg32 MUXT1:2;            /* [19:18] CDTM1_DTM0_AUX input multiplexing(TOM1_CH0...3) - RW */
    ureg32 MUXT2:2;            /* [21:20] CDTM2_DTM0_AUX input multiplexing(TOM2_CH0...3) (THA6412 only) - RW */
    ureg32 MUXT3:2;            /* [23:22] CDTM3_DTM0_AUX input multiplexing(TOM3_CH0...3) (THA6412 only) - RW */
    ureg32 reserved_24:8;    /* [31:24] Internal  reserved */
} GTM_DTMAUXINMUX_Bits;

/* CAN output multiplex register */
typedef struct
{
    ureg32 MUX0:4;        /* [3:0] Output multiplexing for GTM to CAN connection 0 - RW */
    ureg32 MUX1:4;        /* [7:4] Output multiplexing for GTM to CAN connection 1 - RW */
    ureg32 MUX2:4;        /* [11:8] Output multiplexing for GTM to CAN connection 2 - RW */
    ureg32 MUX3:4;        /* [15:12] Output multiplexing for GTM to CAN connection 3 - RW */
    ureg32 MUX4:4;        /* [19:16] Output multiplexing for GTM to CAN connection 4 - RW */
    ureg32 MUX5:4;        /* [23:20] Output multiplexing for GTM to CAN connection 5 - RW */
    ureg32 MUX6:4;        /* [27:24] Output multiplexing for GTM to CAN connection 6 - RW */
    ureg32 MUX7:4;        /* [31:28] Output multiplexing for GTM to CAN connection 7 - RW */
} GTM_CANOUTMUX_Bits;

/* RDC output multiplex register */
typedef struct
{
    ureg32 MUX0:5;            /* [4:0] Output multiplexing for GTM to RDC connection 0 - RW */
    ureg32 reserved_5:3;    /* [7:5] Internal  reserved */
    ureg32 MUX1:5;            /* [12:8] Output multiplexing for GTM to RDC connection 1 - RW */
    ureg32 reserved_13:19;    /* [31:13] Internal  reserved */
} GTM_RDCOUTMUX_Bits;

/* RDC L2 output multiplex register (THA6412 only) */
typedef struct
{
    ureg32 MUX0:2;            /* [1:0] RDC0 Trigger - RW */
    ureg32 MUX1:2;            /* [3:2] RDC1 Trigger - RW */
    ureg32 reserved_13:28;    /* [31:4] Internal  reserved */
} GTM_RDCOUTL2MUX_Bits;

/* Interrupt Request and DMA Request Enable register */
typedef struct
{
    ureg32 EN0:2;            /* [1:0] Interrupt output enable - RW */
    ureg32 EN1:2;            /* [3:2] DMA request output enable - RW */
    ureg32 reserved_4:28;    /* [31:4] Internal  reserved */
} GTM_IDRQEN_Bits;

/* DMA Level 1 Multiplex register */
typedef struct
{
    ureg32 MUX:6;            /* [5:0] DMA request form ICM outputs - RW */
    ureg32 reserved_2:26;    /* [31:6] Internal  reserved */
} GTM_DMAL1MUXN_Bits;

/* DMA Level 1 Common Multiplex register */
typedef struct
{
    ureg32 MUX:6;            /* [5:0] DMA request form ICM outputs - RW */
    ureg32 reserved_2:26;    /* [31:6] Internal  reserved */
} GTM_DMAL1COMMUX_Bits;

/* DMA Level 2 Multiplex register */
typedef struct
{
    ureg32 MUX:7;            /* [6:0] Select the output of the level 1 multiplexer - RW */
    ureg32 reserved_2:25;    /* [31:7] Internal  reserved */
} GTM_DMAL2MUX_Bits;

/* GTM Debug Control register */
typedef struct
{
    ureg32 HALTSTS:1;        /* [0:0] GTM halt state - RO */
    ureg32 RESTORE:1;        /* [1:1] Indicates memory restore phase after leaving GTM halt state - RO */
    ureg32 HALTREQ:1;        /* [2:2] Request signal to stop GTM functional operation - RW */
    ureg32 reserved_3:29;    /* [31:3] Internal  reserved */
} GTM_DBGCTRL_Bits;

/* GTM TIO Input Multiplex register */
typedef struct
{
    ureg32 CH0MUX:4;        /* [3:0] TIO channel 0 input multiplexing - RW */
    ureg32 CH1MUX:4;        /* [7:4] TIO channel 1 input multiplexing - RW */
    ureg32 CH2MUX:4;        /* [11:8] TIO channel 2 input multiplexing - RW */
    ureg32 CH3MUX:4;        /* [15:12] TIO channel 3 input multiplexing - RW */
    ureg32 CH4MUX:4;        /* [19:16] TIO channel 4 input multiplexing - RW */
    ureg32 CH5MUX:4;        /* [23:20] TIO channel 5 input multiplexing - RW */
    ureg32 CH6MUX:4;        /* [27:24] TIO channel 6 input multiplexing - RW */
    ureg32 CH7MUX:4;        /* [31:28] TIO channel 7 input multiplexing - RW */
} GTM_TIOINMUX_Bits;

/* GTM High Resolution PWM Control register (THA6412 only) */
typedef struct
{
    ureg32 EN:1;            /* [0:0] HRPWM enable - RW */
    ureg32 reserved_2:31;    /* [31:1] Internal  reserved */
} GTM_HRPWMCTRL_Bits;

/* GTM High Resolution PWM Control register (THA6412 only) */
typedef struct
{
    ureg32 SEL:2;            /* [1:0] Delaychain select according to cornel - RW */
    ureg32 reserved_2:30;    /* [31:2] Internal  reserved */
} GTM_HRPWMCORNELSEL_Bits;

/* GTM High Resolution PWM Output Multiplex register (THA6412 only) */
typedef struct
{
    ureg32 MUX0:4;        /* [3:0] Output multiplexing for High Resolution PWM - RW */
    ureg32 MUX1:4;        /* [7:4] Output multiplexing for High Resolution PWM - RW */
    ureg32 MUX2:4;        /* [11:8] Output multiplexing for High Resolution PWM - RW */
    ureg32 MUX3:4;        /* [15:12] Output multiplexing for High Resolution PWM - RW */
    ureg32 MUX4:4;        /* [19:16] Output multiplexing for High Resolution PWM - RW */
    ureg32 MUX5:4;        /* [23:20] Output multiplexing for High Resolution PWM - RW */
    ureg32 MUX6:4;        /* [27:24] Output multiplexing for High Resolution PWM - RW */
    ureg32 MUX7:4;        /* [31:28] Output multiplexing for High Resolution PWM - RW */
} GTM_HRPWMOUTMUX_Bits;

/* PSI5 Output Multiplex register (THA6412 only) */
typedef struct
{
    ureg32 MUX0:4;        /* [3:0] Output multiplexing for PSI5 - RW */
    ureg32 MUX1:4;        /* [7:4] Output multiplexing for PSI5 - RW */
    ureg32 MUX2:4;        /* [11:8] Output multiplexing for PSI5 - RW */
    ureg32 MUX3:4;        /* [15:12] Output multiplexing for PSI5 - RW */
    ureg32 MUX4:4;        /* [19:16] Output multiplexing for PSI5 - RW */
    ureg32 MUX5:4;        /* [23:20] Output multiplexing for PSI5 - RW */
    ureg32 reserved_24:8;    /* [31:24] Internal  reserved */
} GTM_PSI5OUTMUX_Bits;

/* TIO Output Multiplex register (THA6412 only) */
typedef struct
{
    ureg32 MUX0:4;        /* [3:0] Output multiplexing for TIO - RW */
    ureg32 MUX1:4;        /* [7:4] Output multiplexing for TIO - RW */
    ureg32 MUX2:4;        /* [11:8] Output multiplexing for TIO - RW */
    ureg32 MUX3:4;        /* [15:12] Output multiplexing for TIO - RW */
    ureg32 MUX4:4;        /* [19:16] Output multiplexing for TIO - RW */
    ureg32 MUX5:4;        /* [23:20] Output multiplexing for TIO - RW */
    ureg32 MUX6:4;        /* [27:24] Output multiplexing for TIO - RW */
    ureg32 reserved_28:4;    /* [31:28] Internal  reserved */
} GTM_TIOOUTMUX_Bits;

/* RAM Data ECC Check Enable register */
typedef struct
{
    ureg32 EN:2;            /* [1:0] ECC enable - RW */
    ureg32 reserved_2:30;    /* [31:2] Internal  reserved */
} GTM_RAMECCEN_Bits;

/* RAM Data REMAP Function Enable register */
typedef struct
{
    ureg32 EN0:2;            /* [1:0] FIFO0 REMAP enable - RW */
    ureg32 EN1:2;            /* [3:2] FIFO1 REMAP enable - RW */
    ureg32 EN2:2;            /* [5:4] FIFO2 REMAP enable - RW */
    ureg32 EN3:2;            /* [7:6] DPLL 1A REMAP enable - RW */
    ureg32 EN4:2;            /* [9:8] DPLL 1B REMAP enable - RW */
    ureg32 EN5:2;            /* [11:10] DPLL2 REMAP enable - RW */
    ureg32 reserved_2:20;    /* [31:12] Internal  reserved */
} GTM_RAMREMAPEN_Bits;

/* RAM Hardware Fault Injection Enable register */
typedef struct
{
    ureg32 EN0:2;            /* [1:0] FIFO0 single bit hardware fault injection enable - RW */
    ureg32 EN1:2;            /* [3:2] FIFO1 single bit hardware fault injection enable - RW */
    ureg32 EN2:2;            /* [5:4] FIFO2 single bit hardware fault injection enable - RW */
    ureg32 EN3:2;            /* [7:6] DPLL 1A single bit hardware fault injection enable - RW */
    ureg32 EN4:2;            /* [9:8] DPLL 1B single bit hardware fault injection enable - RW */
    ureg32 EN5:2;            /* [11:10] DPLL2 single bit hardware fault injection enable - RW */
    ureg32 EN6:2;            /* [13:12] FIFO0 multi-bit hardware fault injection enable - RW */
    ureg32 EN7:2;            /* [15:14] FIFO1 multi-bit hardware fault injection enable - RW */
    ureg32 EN8:2;            /* [17:16] FIFO2 multi-bit hardware fault injection enable - RW */
    ureg32 EN9:2;            /* [19:18] DPLL 1A multi-bit hardware fault injection enable - RW */
    ureg32 EN10:2;            /* [21:20] DPLL 1B multi-bit hardware fault injection enable - RW */
    ureg32 EN11:2;            /* [23:22] DPLL2 multi-bit hardware fault injection enable - RW */
    ureg32 reserved_24:8;    /* [31:24] Internal  reserved */
} GTM_RAMHWINJ_Bits;

/* FIFO RAM Alarm Clear Register */
typedef struct
{
    ureg32 CLR0:2;            /* [1:0] Single bit error alarm clear - W1C */
    ureg32 CLR1:2;            /* [3:2] Multi-bit error alarm clear - W1C */
    ureg32 CLR2:2;            /* [5:4] Single bit error count overflow alarm clear - W1C */
    ureg32 reserved_6:26;    /* [31:6] Internal  reserved */
} GTM_FIFORAM_ALARMCLR_Bits;

/* FIFO Error Address Valid Signal Clear Register */
typedef struct
{
    ureg32 CLR0:1;            /* [0:0] Single bit error address valid clear - W1C */
    ureg32 CLR1:1;            /* [1:1] Single bit error address valid clear - W1C */
    ureg32 CLR2:1;            /* [2:2] Single bit error address valid clear - W1C */
    ureg32 CLR3:1;            /* [3:3] Single bit error address valid clear - W1C */
    ureg32 CLR4:1;            /* [4:4] Single bit error address valid clear - W1C */
    ureg32 CLR5:1;            /* [5:5] Multi-bit error address valid clear - W1C */
    ureg32 reserved_6:26;    /* [31:6] Internal  reserved */
} GTM_FIFORAM_ERRADDRVLDCLR_Bits;

/* FIFO Single Bit Error Address Recording Register */
typedef struct
{
    ureg32 ADDR:32;            /* [31:0] Single bit error address reporting - W1C */
} GTM_FIFORAM_SERRADDR_Bits;

/* FIFO Multi-bit Error Address Recording Register */
typedef struct
{
    ureg32 ADDR:32;            /* [31:0] Multi-bit error address reporting - W1C */
} GTM_FIFORAM_MERRADDR_Bits;

/* DPLL RAM Alarm Clear Register */
typedef struct
{
    ureg32 CLR0:2;            /* [1:0] Single bit error alarm clear - W1C */
    ureg32 CLR1:2;            /* [3:2] Multi-bit error alarm clear - W1C */
    ureg32 CLR2:2;            /* [5:4] Single bit error count overflow alarm clear - W1C */
    ureg32 reserved_6:26;    /* [31:6] Internal  reserved */
} GTM_DPLLRAM_ALARMCLR_Bits;

/* DPLL Error Address Valid Signal Clear Register */
typedef struct
{
    ureg32 CLR0:1;            /* [0:0] Single bit error address valid clear - W1C */
    ureg32 CLR1:1;            /* [1:1] Single bit error address valid clear - W1C */
    ureg32 CLR2:1;            /* [2:2] Single bit error address valid clear - W1C */
    ureg32 CLR3:1;            /* [3:3] Single bit error address valid clear - W1C */
    ureg32 CLR4:1;            /* [4:4] Single bit error address valid clear - W1C */
    ureg32 CLR5:1;            /* [5:5] Multi-bit error address valid clear - W1C */
    ureg32 reserved_6:26;    /* [31:6] Internal  reserved */
} GTM_DPLLRAM_ERRADDRVLDCLR_Bits;

/* DPLL Single Bit Error Address Recording Register */
typedef struct
{
    ureg32 ADDR:32;            /* [31:0] Single bit error address reporting - W1C */
} GTM_DPLLRAM_SERRADDR_Bits;

/* DPLL Multi-bit Error Address Recording Register */
typedef struct
{
    ureg32 ADDR:32;            /* [31:0] Multi-bit error address reporting - W1C */
} GTM_DPLLRAM_MERRADDR_Bits;

/* Single Bit Error Status Register */
typedef struct
{
    ureg32 STS0:1;            /* [0:0] FIFO0 RAM single bit error alarm status - RO */
    ureg32 STS1:1;            /* [1:1] FIFO1 RAM single bit error alarm status - RO */
    ureg32 STS2:1;            /* [2:2] FIFO2 RAM single bit error alarm status - RO */
    ureg32 STS3:1;            /* [3:3] DPLL RAM 1A single bit error alarm status - RO */
    ureg32 STS4:1;            /* [4:4] DPLL RAM 1B single bit error alarm status - RO */
    ureg32 STS5:1;            /* [5:5] DPLL RAM 2 single bit error alarm status - RO */
    ureg32 reserved_6:26;    /* [31:6] Internal  reserved */
} GTM_SBESTS_Bits;

/* Multi-bit Error Status Register */
typedef struct
{
    ureg32 STS0:1;            /* [0:0] FIFO0 RAM multi-bit error alarm status - RO */
    ureg32 STS1:1;            /* [1:1] FIFO1 RAM multi-bit error alarm status - RO */
    ureg32 STS2:1;            /* [2:2] FIFO2 RAM multi-bit error alarm status - RO */
    ureg32 STS3:1;            /* [3:3] DPLL RAM 1A multi-bit error alarm status - RO */
    ureg32 STS4:1;            /* [4:4] DPLL RAM 1B multi-bit error alarm status - RO */
    ureg32 STS5:1;            /* [5:5] DPLL RAM 2 multi-bit error alarm status - RO */
    ureg32 reserved_6:26;    /* [31:6] Internal  reserved */
} GTM_MBESTS_Bits;

/* Single Bit Error Overflow State Register */
typedef struct
{
    ureg32 STS0:1;            /* [0:0] FIFO0 RAM single bit error overflow alarm status - RO */
    ureg32 STS1:1;            /* [1:1] FIFO1 RAM single bit error overflow alarm status - RO */
    ureg32 STS2:1;            /* [2:2] FIFO2 RAMsingle bit error overflow alarm status - RO */
    ureg32 STS3:1;            /* [3:3] DPLL RAM 1A single bit error overflow alarm status - RO */
    ureg32 STS4:1;            /* [4:4] DPLL RAM 1B single bit error overflow alarm status - RO */
    ureg32 STS5:1;            /* [5:5] DPLL RAM 2 single bit error overflow alarm status - RO */
    ureg32 reserved_6:26;    /* [31:6] Internal  reserved */
} GTM_SROSTS_Bits;

/* DMA Timeout Configuration Register */
typedef struct
{
    ureg32 CNT:32;            /* [31:0] DMA timeout counter - RW */
} GTM_DMATOCFG_Bits;

/* DMA Timeout Safety Mechanism Enable Register */
typedef struct
{
    ureg32 EN:2;            /* [1:0] DMA timeout safety mechanism enable - RW */
    ureg32 reserved_2:30;    /* [31:2] Internal  reserved */
} GTM_DMATOSAFETYEN_Bits;

/* DMA Timeout Fault Injection Enable Register */
typedef struct
{
    ureg32 EN:2;            /* [1:0] DMA timeout fault injection enable - RW */
    ureg32 reserved_2:30;    /* [31:2] Internal  reserved */
} GTM_DMATOFAULTINJ_Bits;

/* DMA Timeout Alarm Clear Register */
typedef struct
{
    ureg32 CLR0:2;            /* [1:0] DMA timeout alarm clear - W1C */
    ureg32 reserved_2:30;    /* [31:2] Internal  reserved */
} GTM_DMATOALARMCLR_Bits;

/* DMA Timeout Channel Status Register */
typedef struct
{
    ureg32 STATUS0:1;        /* [0:0] DMA ch0 timeout alarm status - RO */
    ureg32 STATUS1:1;        /* [1:1] DMA ch1 timeout alarm status - RO */
    ureg32 STATUS2:1;        /* [2:2] DMA ch2 timeout alarm status - RO */
    ureg32 STATUS3:1;        /* [3:3] DMA ch3 timeout alarm status - RO */
    ureg32 STATUS4:1;        /* [4:4] DMA ch4 timeout alarm status - RO */
    ureg32 STATUS5:1;        /* [5:5] DMA ch5 timeout alarm status - RO */
    ureg32 STATUS6:1;        /* [6:6] DMA ch6 timeout alarm status - RO */
    ureg32 STATUS7:1;        /* [7:7] DMA ch7 timeout alarm status - RO */
    ureg32 reserved_8:24;    /* [31:8] Internal  reserved */
} GTM_DMATOCHSTS_Bits;

/* Register Safety Mechanism */
typedef struct
{
    ureg32 EN:2;            /* [1:0] Register safety mechanism enable - RW */
    ureg32 reserved_2:30;    /* [31:2] Internal  reserved */
} GTM_REGSAFETYEN_Bits;

/* Register Alarm Status Clear */
typedef struct
{
    ureg32 CLR0:2;            /* [1:0] Clear signal for the register alarm - WO */
    ureg32 reserved_2:30;    /* [31:2] Internal  reserved */
} GTM_REGALARMCLR_Bits;

/* Register Alarm Status */
typedef struct
{
    ureg32 STS0:1;        /* [0:0] Register safety enable signal status - RO */
    ureg32 STS1:1;        /* [1:1] Register safety enable signal status - RO */
    ureg32 STS2:1;        /* [2:2] Register safety enable signal status - RO */
    ureg32 STS3:1;        /* [3:3] Register safety enable signal status - RO */
    ureg32 STS4:1;        /* [4:4] Register safety enable signal status - RO */
    ureg32 STS5:1;        /* [5:5] Register safety enable signal status - RO */
    ureg32 STS6:1;        /* [6:6] Register safety enable signal status - RO */
    ureg32 STS7:1;        /* [7:7] Register safety enable signal status - RO */
    ureg32 STS8:1;        /* [8:8] Register safety enable signal status - RO */
    ureg32 STS9:1;        /* [9:9] Register safety enable signal status - RO */
    ureg32 STS10:1;        /* [10:10] Register safety enable signal status - RO */
    ureg32 STS11:1;        /* [11:11] Register safety enable signal status - RO */
    ureg32 STS12:1;        /* [12:12] Register safety enable signal status - RO */
    ureg32 STS13:1;        /* [13:13] Register safety enable signal status - RO */
    ureg32 reserved_14:18;    /* [31:14] Internal  reserved */
} GTM_REGALARMSTS_Bits;

/* Illegal access alarm clearing register */
typedef struct
{
    ureg32 CLR0:2;           /* [1:0] Illegal access alarm clear - WO */
    ureg32 reserved_2:30;    /* [31:2] Internal  reserved */
} GTM_REGIACLR_Bits;

/* Illegal access alarm status register */
typedef struct
{
    ureg32 STS:1;            /* [0:0] Illegal access alarm status - RO */
    ureg32 reserved_1:31;    /* [31:1] Internal  reserved */
} GTM_REGIAALARMSTS_Bits;

/* ADC Data Ecc Alarm Enable Register */
typedef struct
{
    ureg32 EN:2;            /* [1:0] ADC data ecc alarm enable - RW */
    ureg32 reserved_2:30;    /* [31:2] Internal  reserved */
} GTM_ADALARMEN_Bits;

/* ADC Data Ecc Alarm Clear Register */
typedef struct
{
    ureg32 CLR:2;            /* [1:0] ADC data ecc alarm clear - WO */
    ureg32 reserved_2:30;    /* [31:2] Internal  reserved */
} GTM_ADALARMCLR_Bits;

/* ADC Data Ecc Alarm Clear Register */
typedef struct
{
    ureg32 STS0:1;            /* [0:0] MCS0 ADC data error - RO */
    ureg32 STS1:1;            /* [1:1] MCS1 ADC data error - RO */
    ureg32 STS2:1;            /* [2:2] MCS2 ADC data error - RO */
    ureg32 STS3:1;            /* [3:3] MCS3 ADC data error - RO */
    ureg32 STS4:1;            /* [4:4] MCS4 ADC data error - RO */
    ureg32 STS5:1;            /* [5:5] MCS5 ADC data error - RO */
    ureg32 STS6:1;            /* [6:6] MCS6 ADC data error - RO */
    ureg32 reserved_7:25;     /* [31:7] Internal  reserved */
} GTM_ADALARMSTS_Bits;

/* GTM Debug Global Control Register */
typedef struct
{
    ureg32 GEN:1;             /* [0:0] Global debug enable - RW */
    ureg32 HLTTREN:1;         /* [1:1] GTM halt trigger enable - RW */
    ureg32 reserved_2:30;     /* [31:2] Internal  reserved */
} GTM_DGCR_Bits;

/* GTM Debug Halt Control Register */
typedef struct
{
    ureg32 HLTREQ:1;          /* [0:0] GTM halt request - WO */
    ureg32 HLTCLR:1;          /* [1:1] GTM halt clear - WO */
    ureg32 reserved_2:30;     /* [31:2] Internal  reserved */
} GTM_DHCR_Bits;

/* GTM Debug Halt Status Register */
typedef struct
{
    ureg32 MCS0_BPEN:1;       /* [0:0] MCS0 break point enable - RW */
    ureg32 MCS1_BPEN:1;       /* [1:1] MCS1 break point enable - RW */
    ureg32 MCS2_BPEN:1;       /* [2:2] MCS2 break point enable - RW */
    ureg32 MCS3_BPEN:1;       /* [3:3] MCS3 break point enable - RW */
    ureg32 MCS4_BPEN:1;       /* [4:4] MCS4 break point enable - RW */
    ureg32 MCS5_BPEN:1;       /* [5:5] MCS5 break point enable - RW */
    ureg32 MCS6_BPEN:1;       /* [6:6] MCS6 break point enable - RW */
    ureg32 MCS7_BPEN:1;       /* [7:7] MCS7 break point enable - RW */
    ureg32 reserved_8:24;     /* [31:8] Internal  reserved */
} GTM_DHSR_Bits;

/* MCS Break Point Enable Register */
typedef struct
{
    ureg32 HLT:1;             /* [0:0] GTM halt status - RO */
    ureg32 reserved_1:31;     /* [31:1] Internal  reserved */
} GTM_DMCSBPEN_Bits;
/**********************************************************************************************************************
 *                                              GTM Register Definitions
 *********************************************************************************************************************/
/* GTM version control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_REV_Bits B;                  /* Bit-Field access */
} GTM_REV;

/* GTM global reset register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_RST_Bits B;                  /* Bit-Field access */
} GTM_RST;

/* GTM global control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CTRL_Bits B;                 /* Bit-Field access */
} GTM_CTRL;

/* GTM configuration register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CFG_Bits B;                  /* Bit-Field access */
} GTM_CFG;

/* GTM AEI timeout exception address register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_AEI_ADDR_XPT_Bits B;         /* Bit-Field access */
} GTM_AEI_ADDR_XPT;

/* GTM AEI non zero status register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_AEI_STA_XPT_Bits B;          /* Bit-Field access */
} GTM_AEI_STA_XPT;

/* GTM Interrupt notification register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_IRQ_NOTIFY_Bits B;           /* Bit-Field access */
} GTM_IRQ_NOTIFY;

/* GTM interrupt enable register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_IRQ_EN_Bits B;               /* Bit-Field access */
} GTM_IRQ_EN;

/* GTM error interrupt enable register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_EIRQ_EN_Bits B;              /* Bit-Field access */
} GTM_EIRQ_EN;

/* GTM Software interrupt generation register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_IRQ_FORCINT_Bits B;          /* Bit-Field access */
} GTM_IRQ_FORCINT;

/* GTM top level interrupts mode selection */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_IRQ_MODE_Bits B;             /* Bit-Field access */
} GTM_IRQ_MODE;

/* GTM Cluster Clock Configuration */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CLS_CLK_CFG_Bits B;          /* Bit-Field access */
} GTM_CLS_CLK_CFG;

/* GTM ARU communication disable */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ARU_COM_DIS_Bits B;          /* Bit-Field access */
} GTM_ARU_COM_DIS;

/* GTM AEI bridge mode register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_BRIDGE_MODE_Bits B;          /* Bit-Field access */
} GTM_BRIDGE_MODE;

/* GTM AEI bridge pointer 1 register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_BRIDGE_PTR1_Bits B;          /* Bit-Field access */
} GTM_BRIDGE_PTR1;

/* GTM AEI bridge pointer 2 register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_BRIDGE_PTR2_Bits B;          /* Bit-Field access */
} GTM_BRIDGE_PTR2;

/* GTM MCS master port disable register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_AEM_DIS_Bits B;          /* Bit-Field access */
} GTM_MCS_AEM_DIS;

/* CMU clock enable */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CMU_CLK_EN_Bits B;           /* Bit-Field access */
} GTM_CMU_CLK_EN;

/* The numerator for CMU global clock resolution generator */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CMU_GCLK_NUM_Bits B;         /* Bit-Field access */
} GTM_CMU_GCLK_NUM;

/* The denominator for CMU global clock resolution generator */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CMU_GCLK_DEN_Bits B;         /* Bit-Field access */
} GTM_CMU_GCLK_DEN;

/* CMU control for clock resolution generator [x] */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CMU_CLK__CTRL_Bits B;        /* Bit-Field access */
} GTM_CMU_CLK__CTRL;

/* The numerator for the external clock resolution generator [z] */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CMU_ECLK_NUM_Bits B;         /* Bit-Field access */
} GTM_CMU_ECLK_NUM;

/* The denominator for the external clock resolution generator [z] */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CMU_ECLK_DEN_Bits B;         /* Bit-Field access */
} GTM_CMU_ECLK_DEN;

/* CMU control for selection of FCR subblock input */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CMU_FXCLK_CTRL_Bits B;       /* Bit-Field access */
} GTM_CMU_FXCLK_CTRL;

/* CMU synchronizing ARU and clock source */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CMU_GLB_CTRL_Bits B;         /* Bit-Field access */
} GTM_CMU_GLB_CTRL;

/* CMU control for clock resolution generator */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CMU_CLK_CTRL_Bits B;         /* Bit-Field access */
} GTM_CMU_CLK_CTRL;

/* TBU global channel enable */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TBU_CHEN_Bits B;             /* Bit-Field access */
} GTM_TBU_CHEN;

/* TBU channel 0 control */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TBU_CH0_CTRL_Bits B;         /* Bit-Field access */
} GTM_TBU_CH0_CTRL;

/* TBU channel 0 base */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TBU_CH_0_BASE_Bits B;        /* Bit-Field access */
} GTM_TBU_CH_0_BASE;

/* TBU channel 1 control */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TBU_CH1_CTRL_Bits B;         /* Bit-Field access */
} GTM_TBU_CH1_CTRL;

/* TBU channel [x] base */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TBU_CH_X_BASE_Bits B;        /* Bit-Field access */
} GTM_TBU_CH_X_BASE;

/* TBU channel 2 control */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TBU_CH2_CTRL_Bits B;         /* Bit-Field access */
} GTM_TBU_CH2_CTRL;

/* TBU channel 3 control */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TBU_CH3_CTRL_Bits B;         /* Bit-Field access */
} GTM_TBU_CH3_CTRL;

/* TBU channel 3 modulo value */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TBU_CH3_BASE_MARK_Bits B;    /* Bit-Field access */
} GTM_TBU_CH3_BASE_MARK;

/* TBU channel 3 base captured */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TBU_CH3_BASE_CAPTURE_Bits B; /* Bit-Field access */
} GTM_TBU_CH3_BASE_CAPTURE;

/* ARU access register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ARU_ACCESS_Bits B;           /* Bit-Field access */
} GTM_ARU_ACCESS;

/* ARU access register upper data word */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ARU_DATA_H_Bits B;           /* Bit-Field access */
} GTM_ARU_DATA_H;

/* ARU access register lower data word */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ARU_DATA_L_Bits B;           /* Bit-Field access */
} GTM_ARU_DATA_L;

/* ARU debug access channel 0 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ARU_DBG_ACCESS0_Bits B;      /* Bit-Field access */
} GTM_ARU_DBG_ACCESS0;

/* ARU debug access 0 transfer register upper data word */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ARU_DBG_DATA0_H_Bits B;      /* Bit-Field access */
} GTM_ARU_DBG_DATA0_H;

/* ARU debug access 0 transfer register lower data word */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ARU_DBG_DATA0_L_Bits B;      /* Bit-Field access */
} GTM_ARU_DBG_DATA0_L;

/* ARU debug access channel 0 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ARU_DBG_ACCESS1_Bits B;      /* Bit-Field access */
} GTM_ARU_DBG_ACCESS1;

/* ARU debug access 1 transfer register upper data word */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ARU_DBG_DATA1_H_Bits B;      /* Bit-Field access */
} GTM_ARU_DBG_DATA1_H;

/* ARU debug access 1 transfer register lower data word */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ARU_DBG_DATA1_L_Bits B;      /* Bit-Field access */
} GTM_ARU_DBG_DATA1_L;

/* ARU interrupt notification register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ARU_IRQ_NOTIFY_Bits B;       /* Bit-Field access */
} GTM_ARU_IRQ_NOTIFY;

/* ARU interrupt enable register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ARU_IRQ_EN_Bits B;           /* Bit-Field access */
} GTM_ARU_IRQ_EN;

/* ARU force interrupt register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ARU_IRQ_FORCINT_Bits B;      /* Bit-Field access */
} GTM_ARU_IRQ_FORCINT;

/* ARU interrupt mode register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ARU_IRQ_MODE_Bits B;         /* Bit-Field access */
} GTM_ARU_IRQ_MODE;

/* ARU caddr counter end value */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ARU_CADDR_END_Bits B;        /* Bit-Field access */
} GTM_ARU_CADDR_END;

/* ARU enable dynamic routing */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ARU_CTRL_Bits B;             /* Bit-Field access */
} GTM_ARU_CTRL;

/* ARU [g] dynamic routing control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ARU_DYN_CTRL_Bits B;         /* Bit-Field access */
} GTM_ARU_DYN_CTRL;

/* ARU [g] lower bits of DYN_ROUTE register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ARU_DYN_ROUTE_LOW_Bits B;    /* Bit-Field access */
} GTM_ARU_DYN_ROUTE_LOW;

/* ARU [g] higher bits of DYN_ROUTE register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ARU_DYN_ROUTE_HIGH_Bits B;   /* Bit-Field access */
} GTM_ARU_DYN_ROUTE_HIGH;

/* ARU [g] shadow register of DYN_ROUTE register lower bits */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ARU_DYN_ROUTE_SR_LOW_Bits B; /* Bit-Field access */
} GTM_ARU_DYN_ROUTE_SR_LOW;

/* ARU [g] shadow register of DYN_ROUTE register higher bits */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ARU_DYN_ROUTE_SR_HIGH_Bits B;    /* Bit-Field access */
} GTM_ARU_DYN_ROUTE_SR_HIGH;

/* ARU [g] master ID for dynamic routing */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ARU_DYN_RDADDR_Bits B;       /* Bit-Field access */
} GTM_ARU_DYN_RDADDR;

/* ARU caddr counter value */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ARU_CADDR_Bits B;            /* Bit-Field access */
} GTM_ARU_CADDR;

/* BRC read address for input channel [x] */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_BRC_SRC_ADDR_Bits B;         /* Bit-Field access */
} GTM_BRC_SRC_ADDR;

/* BRC destination channels for input channel [x] */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_BRC_SRC_DEST_Bits B;         /* Bit-Field access */
} GTM_BRC_SRC_DEST;

/* BRC interrupt notification register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_BRC_IRQ_NOTIFY_Bits B;       /* Bit-Field access */
} GTM_BRC_IRQ_NOTIFY;

/* BRC interrupt enable register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_BRC_IRQ_EN_Bits B;           /* Bit-Field access */
} GTM_BRC_IRQ_EN;

/* BRC force interrupt register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_BRC_IRQ_FORCINT_Bits B;      /* Bit-Field access */
} GTM_BRC_IRQ_FORCINT;

/* BRC interrupt mode configuration register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_BRC_IRQ_MODE_Bits B;         /* Bit-Field access */
} GTM_BRC_IRQ_MODE;

/* BRC software reset register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_BRC_RST_Bits B;              /* Bit-Field access */
} GTM_BRC_RST;

/* BRC error interrupt enable register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_BRC_EIRQ_EN_Bits B;          /* Bit-Field access */
} GTM_BRC_EIRQ_EN;

/* ICM Interrupt group register covering infrastructural and safety components (ARU - BRC - AEI - PSM0 - PSM1 - MAP - CMP,SPE) */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ICM_IRQG_0_Bits B;           /* Bit-Field access */
} GTM_ICM_IRQG_0;

/* ICM Interrupt group register covering DPLL */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ICM_IRQG_1_Bits B;           /* Bit-Field access */
} GTM_ICM_IRQG_1;

/* ICM Interrupt group register covering TIM0 - TIM1 - TIM2 - TIM3 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ICM_IRQG_2_Bits B;           /* Bit-Field access */
} GTM_ICM_IRQG_2;

/* ICM Interrupt group register covering TIM4 - TIM5 - TIM6 - TIM7 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ICM_IRQG_3_Bits B;           /* Bit-Field access */
} GTM_ICM_IRQG_3;

/* ICM Interrupt group register covering MCS0 to MCS3 sub-modules */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ICM_IRQG_4_Bits B;           /* Bit-Field access */
} GTM_ICM_IRQG_4;

/* ICM Interrupt group register covering MCS4 to MCS7 sub-modules */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ICM_IRQG_5_Bits B;           /* Bit-Field access */
} GTM_ICM_IRQG_5;

/* ICM Interrupt group register for module error interrupt information */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ICM_IRQG_MEI_Bits B;         /* Bit-Field access */
} GTM_ICM_IRQG_MEI;

/* ICM Interrupt group register 0 for channel error interrupt information */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ICM_IRQG_CEI0_Bits B;        /* Bit-Field access */
} GTM_ICM_IRQG_CEI0;

/* ICM Interrupt group register 1 for channel error interrupt information */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ICM_IRQG_CEI1_Bits B;        /* Bit-Field access */
} GTM_ICM_IRQG_CEI1;

/* ICM Interrupt group register 2 for channel error interrupt information */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ICM_IRQG_CEI2_Bits B;        /* Bit-Field access */
} GTM_ICM_IRQG_CEI2;

/* ICM Interrupt group register 3 for channel error interrupt information */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ICM_IRQG_CEI3_Bits B;        /* Bit-Field access */
} GTM_ICM_IRQG_CEI3;

/* ICM Interrupt group register 4 for channel error interrupt information */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ICM_IRQG_CEI4_Bits B;        /* Bit-Field access */
} GTM_ICM_IRQG_CEI4;

/* ICM Interrupt group MCS[j] for Channel Error Interrupt information */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ICM_IRQG_MCS_CEI_Bits B;     /* Bit-Field access */
} GTM_ICM_IRQG_MCS_CEI;

/* ICM Interrupt group PSM 0 for Channel Error Interrupt information of FIFO0 - FIFO1 - FIFO2 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ICM_IRQG_PSM_CEI_Bits B;     /* Bit-Field access */
} GTM_ICM_IRQG_PSM_CEI;

/* ICM Interrupt group SPE for module Error Interrupt information */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ICM_IRQG_SPE_CEI_Bits B;     /* Bit-Field access */
} GTM_ICM_IRQG_SPE_CEI;

/* ICM Interrupt group for module Error Interrupt information for each TIM[j] - MCS[j] - SPE[j] - FIFO[j] (j=4*[g]+k - k, k=0-3{0 - ... ,3}) */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ICM_IRQG_CLS_0_MEI_Bits B;   /* Bit-Field access */
} GTM_ICM_IRQG_CLS_0_MEI;

/* ICM Interrupt group for module Error Interrupt information for each TIM[j] - MCS[j] - SPE[j] - FIFO[j] (j=4*[g]+k - k, k=0-3{0 - ... ,3}) */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ICM_IRQG_CLS_1_MEI_Bits B;   /* Bit-Field access */
} GTM_ICM_IRQG_CLS_1_MEI;

/* ICM Interrupt group MCS[j] for Channel Interrupt information */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ICM_IRQG_MCS_CI_Bits B;      /* Bit-Field access */
} GTM_ICM_IRQG_MCS_CI;

/* ICM Interrupt group PSM 0 for Channel Interrupt information of FIFO0 - FIFO1 - FIFO2 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ICM_IRQG_PSM_CI_Bits B;      /* Bit-Field access */
} GTM_ICM_IRQG_PSM_CI;

/* ICM Interrupt group SPE for module Interrupt information */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ICM_IRQG_SPE_CI_Bits B;      /* Bit-Field access */
} GTM_ICM_IRQG_SPE_CI;

/* ICM Interrupt group ATOM [g] for Channel Interrupt information of ATOM[j] (m=4*[g]+(0..3)) */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ICM_IRQG_ATOM_CI_Bits B;     /* Bit-Field access */
} GTM_ICM_IRQG_ATOM_CI;

/* ICM Interrupt group TOM [g] for Channel Interrupt information of TOMm ([j]=2*[g]+(0..1)) */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ICM_IRQG_TOM_CI_Bits B;      /* Bit-Field access */
} GTM_ICM_IRQG_TOM_CI;

/* MAP Control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MAP_CTRL_Bits B;             /* Bit-Field access */
} GTM_MAP_CTRL;

/* MON status register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MON_STATUS_Bits B;           /* Bit-Field access */
} GTM_MON_STATUS;

/* MON activity register 0 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MON_ACTIVITY_0_Bits B;       /* Bit-Field access */
} GTM_MON_ACTIVITY_0;

/* MON activity register 1 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MON_ACTIVITY_1_Bits B;       /* Bit-Field access */
} GTM_MON_ACTIVITY_1;

/* MON activity register for MCS [j] */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MON_ACTIVITY_MCS_Bits B;     /* Bit-Field access */
} GTM_MON_ACTIVITY_MCS;

/* CMP comparator enable register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CMP_EN_Bits B;               /* Bit-Field access */
} GTM_CMP_EN;

/* CMP event notification register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CMP_IRQ_NOTIFY_Bits B;       /* Bit-Field access */
} GTM_CMP_IRQ_NOTIFY;

/* CMP interrupt enable register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CMP_IRQ_EN_Bits B;           /* Bit-Field access */
} GTM_CMP_IRQ_EN;

/* CMP interrupt force register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CMP_IRQ_FORCINT_Bits B;      /* Bit-Field access */
} GTM_CMP_IRQ_FORCINT;

/* CMP interrupt mode configuration register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CMP_IRQ_MODE_Bits B;         /* Bit-Field access */
} GTM_CMP_IRQ_MODE;

/* CMP error interrupt enable register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CMP_EIRQ_EN_Bits B;          /* Bit-Field access */
} GTM_CMP_EIRQ_EN;

/* TIM[i] channel [x] general purpose 0 register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIM_CH_GPR0_Bits B;          /* Bit-Field access */
} GTM_TIM_CH_GPR0;

/* TIM[i] channel [x] general purpose 1 register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIM_CH_GPR1_Bits B;          /* Bit-Field access */
} GTM_TIM_CH_GPR1;

/* TIM[i] channel [x] SMU counter register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIM_CH_CNT_Bits B;           /* Bit-Field access */
} GTM_TIM_CH_CNT;

/* TIM[i] channel [x] SMU edge counter register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIM_CH_ECNT_Bits B;          /* Bit-Field access */
} GTM_TIM_CH_ECNT;

/* TIM[i] channel [x] SMU shadow counter register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIM_CH_CNTS_Bits B;          /* Bit-Field access */
} GTM_TIM_CH_CNTS;

/* TIM[i] channel [x] TDU counter register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIM_CH_TDUC_Bits B;          /* Bit-Field access */
} GTM_TIM_CH_TDUC;

/* TIM[i] channel [x] TDU control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIM_CH_TDUV_Bits B;          /* Bit-Field access */
} GTM_TIM_CH_TDUV;

/* TIM[i] channel [x] filter parameter 0 register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIM_CH_FLT_RE_Bits B;        /* Bit-Field access */
} GTM_TIM_CH_FLT_RE;

/* TIM[i] channel [x] filter parameter 1 register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIM_CH_FLT_FE_Bits B;        /* Bit-Field access */
} GTM_TIM_CH_FLT_FE;

/* TIM[i] channel [x] control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIM_CH_CTRL_Bits B;          /* Bit-Field access */
} GTM_TIM_CH_CTRL;

/* TIM[i] channel [x] extended control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIM_CH_ECTRL_Bits B;         /* Bit-Field access */
} GTM_TIM_CH_ECTRL;

/* TIM[i] channel [x] interrupt notification register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIM_CH_IRQ_NOTIFY_Bits B;    /* Bit-Field access */
} GTM_TIM_CH_IRQ_NOTIFY;

/* TIM[i] channel [x] interrupt enable register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIM_CH_IRQ_EN_Bits B;        /* Bit-Field access */
} GTM_TIM_CH_IRQ_EN;

/* TIM[i] channel [x] force interrupt register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIM_CH_IRQ_FORCINT_Bits B;   /* Bit-Field access */
} GTM_TIM_CH_IRQ_FORCINT;

/* TIM[i] channel [x] interrupt mode configuration register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIM_CH_IRQ_MODE_Bits B;      /* Bit-Field access */
} GTM_TIM_CH_IRQ_MODE;

/* TIM[i] channel [x] error interrupt enable register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIM_CH_EIRQ_EN_Bits B;       /* Bit-Field access */
} GTM_TIM_CH_EIRQ_EN;

/* TIM[i] input value observation register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIM_INP_VAL_Bits B;          /* Bit-Field access */
} GTM_TIM_INP_VAL;

/* TIM[i] AUX IN source selection register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIM_IN_SRC_Bits B;           /* Bit-Field access */
} GTM_TIM_IN_SRC;

/* TIM[i] global software reset register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIM_RST_Bits B;              /* Bit-Field access */
} GTM_TIM_RST;

/* TOM[i] channel [x] control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TOM_CH_CTRL_Bits B;          /* Bit-Field access */
} GTM_TOM_CH_CTRL;

/* TOM[i] channel [x] CCU0 compare shadow register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TOM_CH_SR0_Bits B;           /* Bit-Field access */
} GTM_TOM_CH_SR0;

/* TOM[i] channel [x] CCU1 compare shadow register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TOM_CH_SR1_Bits B;           /* Bit-Field access */
} GTM_TOM_CH_SR1;

/* TOM[i] channel [x] CCU0 compare register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TOM_CH_CM0_Bits B;           /* Bit-Field access */
} GTM_TOM_CH_CM0;

/* TOM[i] channel [x] CCU1 compare register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TOM_CH_CM1_Bits B;           /* Bit-Field access */
} GTM_TOM_CH_CM1;

/* TOM[i] channel [x] CCU0 counter */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TOM_CH_CN0_Bits B;           /* Bit-Field access */
} GTM_TOM_CH_CN0;

/* TOM[i] channel [x] status register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TOM_CH_STAT_Bits B;          /* Bit-Field access */
} GTM_TOM_CH_STAT;

/* TOM[i] channel [x] interrupt notification register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TOM_CH_IRQ_NOTIFY_Bits B;    /* Bit-Field access */
} GTM_TOM_CH_IRQ_NOTIFY;

/* TOM[i] channel [x] interrupt enable register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TOM_CH_IRQ_EN_Bits B;        /* Bit-Field access */
} GTM_TOM_CH_IRQ_EN;

/* TOM[i] channel [x] force interrupt register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TOM_CH_IRQ_FORCINT_Bits B;   /* Bit-Field access */
} GTM_TOM_CH_IRQ_FORCINT;

/* TOM[i] channel [x] interrupt mode register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TOM_CH_IRQ_MODE_Bits B;      /* Bit-Field access */
} GTM_TOM_CH_IRQ_MODE;

/* TOM[i] channel [x] control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TOM_CH_CTRL2_Bits B;         /* Bit-Field access */
} GTM_TOM_CH_CTRL2;

/* TOM[i] channel [x] control shadow register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TOM_CH_CTRL_SR_Bits B;       /* Bit-Field access */
} GTM_TOM_CH_CTRL_SR;

/* TOM[i] TGC [g] global control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TOM_TGC_GLB_CTRL_Bits B;     /* Bit-Field access */
} GTM_TOM_TGC_GLB_CTRL;

/* TOM[i] TGC [g] action time base register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TOM_TGC_ACT_TB_Bits B;       /* Bit-Field access */
} GTM_TOM_TGC_ACT_TB;

/* TOM[i] TGC [g] force update control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TOM_TGC_FUPD_CTRL_Bits B;    /* Bit-Field access */
} GTM_TOM_TGC_FUPD_CTRL;

/* TOM[i] TGC [g] internal trigger control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TOM_TGC_INT_TRIG_Bits B;     /* Bit-Field access */
} GTM_TOM_TGC_INT_TRIG;

/* TOM[i] TGC [g] enable/disable control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TOM_TGC_ENDIS_CTRL_Bits B;   /* Bit-Field access */
} GTM_TOM_TGC_ENDIS_CTRL;

/* TOM[i] TGC [g] enable/disable status register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TOM_TGC_ENDIS_STAT_Bits B;   /* Bit-Field access */
} GTM_TOM_TGC_ENDIS_STAT;

/* TOM[i] TGC [g] output enable control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TOM_TGC_OUTEN_CTRL_Bits B;   /* Bit-Field access */
} GTM_TOM_TGC_OUTEN_CTRL;

/* TOM[i] TGC [g] output enable status register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TOM_TGC_OUTEN_STAT_Bits B;   /* Bit-Field access */
} GTM_TOM_TGC_OUTEN_STAT;

/* ATOM[i] channel[x] ARU read address register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ATOM_CH_RDADDR_Bits B;       /* Bit-Field access */
} GTM_ATOM_CH_RDADDR;

/* ATOM[i] channel [x] control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ATOM_CH_CTRL_Bits B;         /* Bit-Field access */
} GTM_ATOM_CH_CTRL;

/* ATOM[i] channel[x] Control Register in SOMB Mode   */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                 /* Unsigned access */
    GTM_ATOM_CH_SOMB_Bits B;      /* Bit-Field access */
} GTM_ATOM_CH_SOMB;

/* ATOM[i] channel[x] Control Register in SOMC Mode   */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                 /* Unsigned access */
    GTM_ATOM_CH_SOMC_Bits B;      /* Bit-Field access */
} GTM_ATOM_CH_SOMC;

/* ATOM[i] channel[x] Control Register in SOMI Mode   */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                 /* Unsigned access */
    GTM_ATOM_CH_SOMI_Bits B;      /* Bit-Field access */
} GTM_ATOM_CH_SOMI;

/* ATOM[i] channel[x] Control Register in SOMP Mode   */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                 /* Unsigned access */
    GTM_ATOM_CH_SOMP_Bits B;      /* Bit-Field access */
} GTM_ATOM_CH_SOMP;

/* ATOM[i] channel[x] Control Register in SOMS Mode   */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                 /* Unsigned access */
    GTM_ATOM_CH_SOMS_Bits B;      /* Bit-Field access */
} GTM_ATOM_CH_SOMS;

/* ATOM[i] channel [x] CCU0 compare shadow register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ATOM_CH_SR0_Bits B;          /* Bit-Field access */
} GTM_ATOM_CH_SR0;

/* ATOM[i] channel [x] CCU1 compare shadow register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ATOM_CH_SR1_Bits B;          /* Bit-Field access */
} GTM_ATOM_CH_SR1;

/* ATOM[i] channel [x] CCU0 compare register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ATOM_CH_CM0_Bits B;          /* Bit-Field access */
} GTM_ATOM_CH_CM0;

/* ATOM[i] channel [x] CCU1 compare register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ATOM_CH_CM1_Bits B;          /* Bit-Field access */
} GTM_ATOM_CH_CM1;

/* ATOM[i] channel [x] CCU0 counter register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ATOM_CH_CN0_Bits B;          /* Bit-Field access */
} GTM_ATOM_CH_CN0;

/* ATOM[i] channel [x] status register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ATOM_CH_STAT_Bits B;         /* Bit-Field access */
} GTM_ATOM_CH_STAT;

/* ATOM[i] channel [x] interrupt notification register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ATOM_CH_IRQ_NOTIFY_Bits B;   /* Bit-Field access */
} GTM_ATOM_CH_IRQ_NOTIFY;

/* ATOM[i] channel [x] interrupt enable register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ATOM_CH_IRQ_EN_Bits B;       /* Bit-Field access */
} GTM_ATOM_CH_IRQ_EN;

/* ATOM[i] channel [x] software interrupt generation */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ATOM_CH_IRQ_FORCINT_Bits B;  /* Bit-Field access */
} GTM_ATOM_CH_IRQ_FORCINT;

/* ATOM[i] channel [x] interrupt mode configuration register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ATOM_CH_IRQ_MODE_Bits B;     /* Bit-Field access */
} GTM_ATOM_CH_IRQ_MODE;

/* ATOM[i] channel [x] control2 register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ATOM_CH_CTRL2_Bits B;        /* Bit-Field access */
} GTM_ATOM_CH_CTRL2;

/* ATOM[i] channel [x] control shadow register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ATOM_CH_CTRL_SR_Bits B;      /* Bit-Field access */
} GTM_ATOM_CH_CTRL_SR;

/* ATOM[i] AGC global control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ATOM_AGC_GLB_CTRL_Bits B;    /* Bit-Field access */
} GTM_ATOM_AGC_GLB_CTRL;

/* ATOM[i] AGC enable/disable control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ATOM_AGC_ENDIS_CTRL_Bits B;  /* Bit-Field access */
} GTM_ATOM_AGC_ENDIS_CTRL;

/* ATOM[i] AGC enable/disable status register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ATOM_AGC_ENDIS_STAT_Bits B;  /* Bit-Field access */
} GTM_ATOM_AGC_ENDIS_STAT;

/* ATOM[i] AGC action time base register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ATOM_AGC_ACT_TB_Bits B;      /* Bit-Field access */
} GTM_ATOM_AGC_ACT_TB;

/* ATOM[i] AGC output enable control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ATOM_AGC_OUTEN_CTRL_Bits B;  /* Bit-Field access */
} GTM_ATOM_AGC_OUTEN_CTRL;

/* ATOM[i] AGC output enable status register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ATOM_AGC_OUTEN_STAT_Bits B;  /* Bit-Field access */
} GTM_ATOM_AGC_OUTEN_STAT;

/* ATOM[i] AGC force update control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ATOM_AGC_FUPD_CTRL_Bits B;   /* Bit-Field access */
} GTM_ATOM_AGC_FUPD_CTRL;

/* ATOM[i] AGC internal trigger control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ATOM_AGC_INT_TRIG_Bits B;    /* Bit-Field access */
} GTM_ATOM_AGC_INT_TRIG;

/* MCS[i] channel x general purpose register [y] */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_CH_R_Bits B;             /* Bit-Field access */
} GTM_MCS_CH_R;

/* MCS[i] channel x control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_CH_CTRL_Bits B;          /* Bit-Field access */
} GTM_MCS_CH_CTRL;

/* MCS[i] channel x ARU control Bit register  */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_CH_ACB_Bits B;           /* Bit-Field access */
} GTM_MCS_CH_ACB;

/* MCS[i] channel x memory high byte register  */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_CH_MHB_Bits B;           /* Bit-Field access */
} GTM_MCS_CH_MHB;

/* MCS[i] channel x program counter register  */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_CH_PC_Bits B;            /* Bit-Field access */
} GTM_MCS_CH_PC;

/* MCS[i] channel x interrupt notification register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_CH_IRQ_NOTIFY_Bits B;    /* Bit-Field access */
} GTM_MCS_CH_IRQ_NOTIFY;

/* MCS[i] channel x interrupt enable register  */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_CH_IRQ_EN_Bits B;        /* Bit-Field access */
} GTM_MCS_CH_IRQ_EN;

/* MCS[i] channel x force interrupt register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_CH_IRQ_FORCINT_Bits B;   /* Bit-Field access */
} GTM_MCS_CH_IRQ_FORCINT;

/* MCS[i] channel x IRQ mode configuration register  */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_CH_IRQ_MODE_Bits B;      /* Bit-Field access */
} GTM_MCS_CH_IRQ_MODE;

/* MCS[i] channel x error interrupt enable register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_CH_EIRQ_EN_Bits B;       /* Bit-Field access */
} GTM_MCS_CH_EIRQ_EN;

/* MCS[i] clear trigger control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_CTRG_Bits B;             /* Bit-Field access */
} GTM_MCS_CTRG;

/* MCS[i] set trigger control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_STRG_Bits B;             /* Bit-Field access */
} GTM_MCS_STRG;

/* MCS[i] control and status register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_CTRL_STAT_Bits B;        /* Bit-Field access */
} GTM_MCS_CTRL_STAT;

/* MCS[i] reset register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_RESET_Bits B;            /* Bit-Field access */
} GTM_MCS_RESET;

/* MCS[i] cancel ARU transfer instruction */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_CAT_Bits B;              /* Bit-Field access */
} GTM_MCS_CAT;

/* MCS[i] cancel waiting instruction */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_CWT_Bits B;              /* Bit-Field access */
} GTM_MCS_CWT;

/* MCS[i] error register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_ERR_Bits B;              /* Bit-Field access */
} GTM_MCS_ERR;

/* MCS[i] write protection register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_REG_PROT_Bits B;         /* Bit-Field access */
} GTM_MCS_REG_PROT;

/* MCS[i] shared interrupt notification register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_SINT_IRQ_NOTIFY_Bits B;  /* Bit-Field access */
} GTM_MCS_SINT_IRQ_NOTIFY;

/* MCS[i] shared interrupt enable register  */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_SINT_IRQ_EN_Bits B;      /* Bit-Field access */
} GTM_MCS_SINT_IRQ_EN;

/* MCS[i] force shared interrupt register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_SINT_IRQ_FORCINT_Bits B; /* Bit-Field access */
} GTM_MCS_SINT_IRQ_FORCINT;

/* MCS[i] shared interrupt mode configuration register  */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_SINT_IRQ_MODE_Bits B;    /* Bit-Field access */
} GTM_MCS_SINT_IRQ_MODE;

/* MCS[i] hardware break point h control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_HBP_CTRL_Bits B;         /* Bit-Field access */
} GTM_MCS_HBP_CTRL;

/* MCS[i] hardware break point pattern register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_HBP_PATTERN_Bits B;      /* Bit-Field access */
} GTM_MCS_HBP_PATTERN;

/* MCS[i] hardware break point status register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_HBP_STATUS_Bits B;       /* Bit-Field access */
} GTM_MCS_HBP_STATUS;

/* MCS[i] hardware break point interrupt notification register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_HBP_IRQ_NOTIFY_Bits B;   /* Bit-Field access */
} GTM_MCS_HBP_IRQ_NOTIFY;

/* MCS[i] hardware break point interrupt enable register  */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_HBP_IRQ_EN_Bits B;       /* Bit-Field access */
} GTM_MCS_HBP_IRQ_EN;

/* MCS[i] force hardware break point interrupt register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_HBP_IRQ_FORCINT_Bits B;  /* Bit-Field access */
} GTM_MCS_HBP_IRQ_FORCINT;

/* MCS[i] break point h interrupt mode configuration register  */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_HBP_IRQ_MODE_Bits B;     /* Bit-Field access */
} GTM_MCS_HBP_IRQ_MODE;

/* TIO[i] group [g] channel [c] control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_G_CH_CTRL_Bits B;        /* Bit-Field access */
} GTM_TIO_G_CH_CTRL;

/* TIO[i] channel [c] interrupt notification register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_G_CH_IRQ_NOTIFY_Bits B;  /* Bit-Field access */
} GTM_TIO_G_CH_IRQ_NOTIFY;

/* TIO[i] channel [c] interrupt enable register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_G_CH_IRQ_EN_Bits B;      /* Bit-Field access */
} GTM_TIO_G_CH_IRQ_EN;

/* TIO[i] channel [c] force interrupt register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_G_CH_IRQ_FORCINT_Bits B; /* Bit-Field access */
} GTM_TIO_G_CH_IRQ_FORCINT;

/* TIO[i] channel [c] IRQ mode configuration register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_G_CH_IRQ_MODE_Bits B;    /* Bit-Field access */
} GTM_TIO_G_CH_IRQ_MODE;

/* TIO[i] group [g] channel [c] control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_G_CH_CTRL2_Bits B;       /* Bit-Field access */
} GTM_TIO_G_CH_CTRL2;

/* TIO[i] channel [c] resource S instruction register (buffer operation)

TIO[i]_G[g]_CH[c]_CTRL.PL_S_MODE=0b0- */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_G_CH_SINST_Bits B;       /* Bit-Field access */
} GTM_TIO_G_CH_SINST;

/* TIO[i] channel [c] resource S command register (buffer operation)

TIO[i]_G[g]_CH[c]_CTRL.PL_S_MODE=0b0- */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_G_CH_SCMD_Bits B;        /* Bit-Field access */
    GTM_TIO_G_CH_SCMD_COUNT_Bits B1; /* Bit-Field access */
} GTM_TIO_G_CH_SCMD;

/* TIO[i] channel [c] resource S operand register

TIO[i]_G[g]_CH[c]_CTRL.PL_S_MODE=0b0- or (TIO[i]_G[g]_OP_USAGE.MODE[c]=0b10- or TIO[i]_G[g]_OP_USAGE.MODE[c]=0b1-0 ) */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_G_CH_SOP_Bits B;         /* Bit-Field access */
} GTM_TIO_G_CH_SOP;

/* TIO[i] channel [c] resource O instruction register (buffer operation)

TIO[i]_G[g]_CH[c]_CTRL.PL_O_MODE =0b00- */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_G_CH_OINST_Bits B;       /* Bit-Field access */
} GTM_TIO_G_CH_OINST;

/* TIO[i] channel [c] resource O command register (buffer operation)

TIO[i]_G[g]_CH[c]_CTRL.PL_O_MODE=0b00- */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_G_CH_OCMD_Bits B;        /* Bit-Field access */
    GTM_TIO_G_CH_OCMD_COMP_Bits B1;  /* Bit-Field access, compare operation*/
    GTM_TIO_G_CH_OCMD_CAP_Bits  B2;  /* Bit-Field access, capture operation*/
} GTM_TIO_G_CH_OCMD;

/* TIO[i] channel [c] resource O operand register

!(TIO[i]_G[g]_CH[c]_CTRL.PL_O_MODE=0b1--) or (TIO[i]_G[g]_OP_USAGE.MODE[c]=0b11-) */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_G_CH_OOP_Bits B;         /* Bit-Field access */
    GTM_TIO_G_CH_OCAPTURE_Bits B1;   /* Bit-Field access */
} GTM_TIO_G_CH_OOP;

/* TIO[i] channel [c] resource shift count register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_G_CH_SHIFTCNT_Bits B;    /* Bit-Field access */
} GTM_TIO_G_CH_SHIFTCNT;

/* TIO[i] input selection register 1 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_G_ISEL_CTRL1_Bits B;     /* Bit-Field access */
} GTM_TIO_G_ISEL_CTRL1;

/* TIO[i] input selection register 2 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_G_ISEL_CTRL2_Bits B;     /* Bit-Field access */
} GTM_TIO_G_ISEL_CTRL2;

/* TIO[i] operand usage selection register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_G_OP_USAGE_Bits B;       /* Bit-Field access */
} GTM_TIO_G_OP_USAGE;

/* TIO[i] signal sampling register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_S_Bits B;                /* Bit-Field access */
} GTM_TIO_S;

/* TIO[i] output register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_O_Bits B;                /* Bit-Field access */
} GTM_TIO_O;

/* TIO[i] enable/disable register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_ENDIS_Bits B;            /* Bit-Field access */
} GTM_TIO_ENDIS;

/* TIO[i] signal invert register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_INVERT_Bits B;           /* Bit-Field access */
} GTM_TIO_INVERT;

/* TIO[i] input mode register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_INPUT_MODE_Bits B;       /* Bit-Field access */
} GTM_TIO_INPUT_MODE;

/* TIO[i] cyclic mode register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_CYCLIC_MODE_Bits B;      /* Bit-Field access */
} GTM_TIO_CYCLIC_MODE;

/* TIO[i] enable Trigger Output - output gating register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_TRIG_OUT_GATE_EN_Bits B; /* Bit-Field access */
} GTM_TIO_TRIG_OUT_GATE_EN;

/* TIO[i] enable PL_TRIG_OUT output gating register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_PLTRIG_OUT_GATE_EN_Bits B;    /* Bit-Field access */
} GTM_TIO_PLTRIG_OUT_GATE_EN;

/* TIO[i] clear signal sampling register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_CS_Bits B;               /* Bit-Field access */
} GTM_TIO_CS;

/* TIO[i] clear output register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_CO_Bits B;               /* Bit-Field access */
} GTM_TIO_CO;

/* TIO[i] disable register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_CENDIS_Bits B;           /* Bit-Field access */
} GTM_TIO_CENDIS;

/* TIO[i] clear signal invert register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_CINVERT_Bits B;          /* Bit-Field access */
} GTM_TIO_CINVERT;

/* TIO[i] disable input mode register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_CINPUT_MODE_Bits B;      /* Bit-Field access */
} GTM_TIO_CINPUT_MODE;

/* TIO[i] disable cyclic mode register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_CCYCLIC_MODE_Bits B;     /* Bit-Field access */
} GTM_TIO_CCYCLIC_MODE;

/* TIO[i] clear Trigger Output - output gating register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_CTRIG_OUT_GATE_EN_Bits B;    /* Bit-Field access */
} GTM_TIO_CTRIG_OUT_GATE_EN;

/* TIO[i] clear PL_TRIG_OUT output gating register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_CPLTRIG_OUT_GATE_EN_Bits B;    /* Bit-Field access */
} GTM_TIO_CPLTRIG_OUT_GATE_EN;

/* TIO[i] set signal sampling register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_SS_Bits B;               /* Bit-Field access */
} GTM_TIO_SS;

/* TIO[i] set output register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_SO_Bits B;               /* Bit-Field access */
} GTM_TIO_SO;

/* TIO[i] enable register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_SENDIS_Bits B;           /* Bit-Field access */
} GTM_TIO_SENDIS;

/* TIO[i] set signal invert register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_SINVERT_Bits B;          /* Bit-Field access */
} GTM_TIO_SINVERT;

/* TIO[i] enable input mode register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_SINPUT_MODE_Bits B;      /* Bit-Field access */
} GTM_TIO_SINPUT_MODE;

/* TIO[i] enable cyclic mode register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_SCYCLIC_MODE_Bits B;     /* Bit-Field access */
} GTM_TIO_SCYCLIC_MODE;

/* TIO[i] set Trigger Output - output gating register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_STRIG_OUT_GATE_EN_Bits B;    /* Bit-Field access */
} GTM_TIO_STRIG_OUT_GATE_EN;

/* TIO[i] set PL_TRIG_OUT output gating register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_SPLTRIG_OUT_GATE_EN_Bits B;    /* Bit-Field access */
} GTM_TIO_SPLTRIG_OUT_GATE_EN;

/* TIO[i] invert signal sampling register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_IS_Bits B;               /* Bit-Field access */
} GTM_TIO_IS;

/* TIO[i] invert output register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_IO_Bits B;               /* Bit-Field access */
} GTM_TIO_IO;

/* TIO[i] toggle enable/disable register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_IENDIS_Bits B;           /* Bit-Field access */
} GTM_TIO_IENDIS;

/* TIO[i] toggle signal invert register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_IINVERT_Bits B;          /* Bit-Field access */
} GTM_TIO_IINVERT;

/* TIO[i] enable input mode register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_IINPUT_MODE_Bits B;      /* Bit-Field access */
} GTM_TIO_IINPUT_MODE;

/* TIO[i] enable cyclic mode register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_ICYCLIC_MODE_Bits B;     /* Bit-Field access */
} GTM_TIO_ICYCLIC_MODE;

/* TIO[i] force update register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_FUPD_Bits B;             /* Bit-Field access */
} GTM_TIO_FUPD;

/* TIO[i] configuration register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_HW_CONF_Bits B;          /* Bit-Field access */
} GTM_TIO_HW_CONF;

/* TIO[i] resource selection control register 1 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_RSEL_CTRL1_Bits B;       /* Bit-Field access */
} GTM_TIO_RSEL_CTRL1;

/* TIO[i] resource selection control register 2 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_RSEL_CTRL2_Bits B;       /* Bit-Field access */
} GTM_TIO_RSEL_CTRL2;

/* TIO[i] software reset for TIO Plus functionality */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIO_PL_SWRST_Bits B;         /* Bit-Field access */
} GTM_TIO_PL_SWRST;

/* CCM[i] Address Range Protector [a] Control Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CCM_ARP_CTRL_Bits B;         /* Bit-Field access */
} GTM_CCM_ARP_CTRL;

/* CCM[i] Address Range Protector [a] Protection Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CCM_ARP_PROT_Bits B;         /* Bit-Field access */
} GTM_CCM_ARP_PROT;

/* CCM[i] TIO Group 0,1 Output Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CCM_TIO_G_OUT_Bits B;        /* Bit-Field access */
} GTM_CCM_TIO_G_OUT;

/* CCM[i] 2. Hardware Configuration Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CCM_HW_CONF2_Bits B;         /* Bit-Field access */
} GTM_CCM_HW_CONF2;

/* CCM[i] MCS Bus Master Status Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CCM_AEIM_STA_Bits B;         /* Bit-Field access */
} GTM_CCM_AEIM_STA;

/* CCM[i] Hardware Configuration Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CCM_HW_CONF_Bits B;          /* Bit-Field access */
} GTM_CCM_HW_CONF;

/* CCM[i] TIM AUX Input Source Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CCM_TIM_AUX_IN_SRC_Bits B;   /* Bit-Field access */
} GTM_CCM_TIM_AUX_IN_SRC;

/* CCM[i] External Capture Enable Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CCM_EXT_CAP_EN_Bits B;       /* Bit-Field access */
} GTM_CCM_EXT_CAP_EN;

/* CCM[i] TOM Output Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CCM_TOM_OUT_Bits B;          /* Bit-Field access */
} GTM_CCM_TOM_OUT;

/* CCM[i] ATOM Output Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CCM_ATOM_OUT_Bits B;         /* Bit-Field access */
} GTM_CCM_ATOM_OUT;

/* CCM[i] CMU Clock Configuration Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CCM_CMU_CLK_CFG_Bits B;      /* Bit-Field access */
} GTM_CCM_CMU_CLK_CFG;

/* CCM[i] CMU Fixed Clock Configuration Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CCM_CMU_FXCLK_CFG_Bits B;    /* Bit-Field access */
} GTM_CCM_CMU_FXCLK_CFG;

/* CCM[i] Configuration Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CCM_CFG_Bits B;              /* Bit-Field access */
} GTM_CCM_CFG;

/* CCM[i] Protection Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CCM_PROT_Bits B;             /* Bit-Field access */
} GTM_CCM_PROT;

/* CDTM[i]_DTM[d] global configuration and control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CDTM_DTM_CTRL_Bits B;        /* Bit-Field access */
} GTM_CDTM_DTM_CTRL;

/* CDTM[i]_DTM[d] channel control register 1 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CDTM_DTM_CH_CTRL1_Bits B;    /* Bit-Field access */
} GTM_CDTM_DTM_CH_CTRL1;

/* CDTM[i]_DTM[d] channel control register 2 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CDTM_DTM_CH_CTRL2_Bits B;    /* Bit-Field access */
} GTM_CDTM_DTM_CH_CTRL2;

/* CDTM[i] DTM[j] channel control register 2 shadow */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CDTM_DTM_CH_CTRL2_SR_Bits B; /* Bit-Field access */
} GTM_CDTM_DTM_CH_CTRL2_SR;

/* CDTM[i]_DTM[d] phase shift unit configuration and control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CDTM_DTM_PS_CTRL_Bits B;     /* Bit-Field access */
} GTM_CDTM_DTM_PS_CTRL;

/* CDTM[i]_DTM[d] channel [x] dead time reload values */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CDTM_DTM_CH_DTV_Bits B;      /* Bit-Field access */
} GTM_CDTM_DTM_CH_DTV;

/* CDTM[i]_DTM[d] channel shadow register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CDTM_DTM_CH_SR_Bits B;       /* Bit-Field access */
} GTM_CDTM_DTM_CH_SR;

/* CDTM[i]_DTM[d] channel control register 3 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CDTM_DTM_CH_CTRL3_Bits B;    /* Bit-Field access */
} GTM_CDTM_DTM_CH_CTRL3;

/* CDTM[i]_DTM[d] global configuration and control register 2 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CDTM_DTM_CTRL2_Bits B;       /* Bit-Field access */
} GTM_CDTM_DTM_CTRL2;

/* CDTM[i]_DTM[d] channel [x] dead time shadow values */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CDTM_DTM_CH_DTV_SR_Bits B;   /* Bit-Field access */
} GTM_CDTM_DTM_CH_DTV_SR;

/* F2A[i] stream [x] ARU read register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_F2A_CH_ARU_RD_FIFO_Bits B;   /* Bit-Field access */
} GTM_F2A_CH_ARU_RD_FIFO;

/* F2A[i] stream [x] configuration register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_F2A_CH_STR_CFG_Bits B;       /* Bit-Field access */
} GTM_F2A_CH_STR_CFG;

/* F2A[i] stream activation register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_F2A_ENABLE_Bits B;           /* Bit-Field access */
} GTM_F2A_ENABLE;

/* F2A[i] stream control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_F2A_CTRL_Bits B;             /* Bit-Field access */
} GTM_F2A_CTRL;

/* AFD [i] FIFO [x] buffer access register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_AFD_CH_BUF_ACC_Bits B;       /* Bit-Field access */
} GTM_AFD_CH_BUF_ACC;

/* FIFO[i] channel [x] control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_FIFO_CH_CTRL_Bits B;         /* Bit-Field access */
} GTM_FIFO_CH_CTRL;

/* FIFO[i] channel [x] end address register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_FIFO_CH_END_ADDR_Bits B;     /* Bit-Field access */
} GTM_FIFO_CH_END_ADDR;

/* FIFO[i] channel [x] start address register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_FIFO_CH_START_ADDR_Bits B;   /* Bit-Field access */
} GTM_FIFO_CH_START_ADDR;

/* FIFO[i] channel [x] upper watermark register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_FIFO_CH_UPPER_WM_Bits B;     /* Bit-Field access */
} GTM_FIFO_CH_UPPER_WM;

/* FIFO[i] channel [x] lower watermark register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_FIFO_CH_LOWER_WM_Bits B;     /* Bit-Field access */
} GTM_FIFO_CH_LOWER_WM;

/* FIFO[i] channel [x] status register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_FIFO_CH_STATUS_Bits B;       /* Bit-Field access */
} GTM_FIFO_CH_STATUS;

/* FIFO[i] channel [x] fill level register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_FIFO_CH_FILL_LEVEL_Bits B;   /* Bit-Field access */
} GTM_FIFO_CH_FILL_LEVEL;

/* FIFO[i] channel [x] write pointer register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_FIFO_CH_WR_PTR_Bits B;       /* Bit-Field access */
} GTM_FIFO_CH_WR_PTR;

/* FIFO[i] channel [x] read pointer register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_FIFO_CH_RD_PTR_Bits B;       /* Bit-Field access */
} GTM_FIFO_CH_RD_PTR;

/* FIFO[i] channel [x] interrupt notification register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_FIFO_CH_IRQ_NOTIFY_Bits B;   /* Bit-Field access */
} GTM_FIFO_CH_IRQ_NOTIFY;

/* FIFO[i] channel [x] interrupt enable register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_FIFO_CH_IRQ_EN_Bits B;       /* Bit-Field access */
} GTM_FIFO_CH_IRQ_EN;

/* FIFO[i] channel [x] force interrupt register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_FIFO_CH_IRQ_FORCINT_Bits B;  /* Bit-Field access */
} GTM_FIFO_CH_IRQ_FORCINT;

/* FIFO[i] channel [x] interrupt mode control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_FIFO_CH_IRQ_MODE_Bits B;     /* Bit-Field access */
} GTM_FIFO_CH_IRQ_MODE;

/* FIFO[i] channel [x] error interrupt enable register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_FIFO_CH_EIRQ_EN_Bits B;      /* Bit-Field access */
} GTM_FIFO_CH_EIRQ_EN;

/* SPE[i] Control Status Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_SPE_CTRL_STAT_Bits B;        /* Bit-Field access */
} GTM_SPE_CTRL_STAT;

/* SPE[i] Input Pattern Definition Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_SPE_PAT_Bits B;              /* Bit-Field access */
} GTM_SPE_PAT;

/* SPE[i] Output Definition Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_SPE_OUT_PAT_Bits B;          /* Bit-Field access */
} GTM_SPE_OUT_PAT;

/* SPE[i] Output Control Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_SPE_OUT_CTRL_Bits B;         /* Bit-Field access */
} GTM_SPE_OUT_CTRL;

/* SPE[i] Interrupt Notification Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_SPE_IRQ_NOTIFY_Bits B;       /* Bit-Field access */
} GTM_SPE_IRQ_NOTIFY;

/* SPE[i] Interrupt Enable Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_SPE_IRQ_EN_Bits B;           /* Bit-Field access */
} GTM_SPE_IRQ_EN;

/* SPE[i] Interrupt Generation By Software */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_SPE_IRQ_FORCINT_Bits B;      /* Bit-Field access */
} GTM_SPE_IRQ_FORCINT;

/* SPE[i] Interrupt Mode Configuration Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_SPE_IRQ_MODE_Bits B;         /* Bit-Field access */
} GTM_SPE_IRQ_MODE;

/* SPE[i] Error Interrupt Enable Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_SPE_EIRQ_EN_Bits B;          /* Bit-Field access */
} GTM_SPE_EIRQ_EN;

/* SPE[i] Input Revolution Counter */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_SPE_REV_CNT_Bits B;          /* Bit-Field access */
} GTM_SPE_REV_CNT;

/* SPE[i] Revolution Counter Compare Value */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_SPE_REV_CMP_Bits B;          /* Bit-Field access */
} GTM_SPE_REV_CMP;

/* SPE[i] Control Status Register 2 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_SPE_CTRL_STAT2_Bits B;       /* Bit-Field access */
} GTM_SPE_CTRL_STAT2;

/* SPE[i] Command Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_SPE_CMD_Bits B;              /* Bit-Field access */
} GTM_SPE_CMD;

/* AXIM[i] slot allocation status. */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_AXIM_FREE_Bits B;            /* Bit-Field access */
} GTM_AXIM_FREE;

/* AXIM[i] slot request (allocation). */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_AXIM_REQUEST_Bits B;         /* Bit-Field access */
} GTM_AXIM_REQUEST;

/* AXIM[i] slot release (de-allocation). */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_AXIM_RELEASE_Bits B;         /* Bit-Field access */
} GTM_AXIM_RELEASE;

/* AXIM[i] slot[s] address bits 31:0 of AXI transaction. */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_AXIM_SLOT_ADDR_LOW_Bits B;   /* Bit-Field access */
} GTM_AXIM_SLOT_ADDR_LOW;

/* AXIM[i] slot[s] data bits 31:0 of AXI transaction. */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_AXIM_SLOT_DATA_LOW_Bits B;   /* Bit-Field access */
} GTM_AXIM_SLOT_DATA_LOW;

/* AXIM[i] slot [s] configuration 1 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_AXIM_SLOT_CFG1_Bits B;       /* Bit-Field access */
} GTM_AXIM_SLOT_CFG1;

/* AXIM[i] slot[s] configuration 2 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_AXIM_SLOT_CFG2_Bits B;       /* Bit-Field access */
} GTM_AXIM_SLOT_CFG2;

/* AXIM[i] slot[s] status */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_AXIM_SLOT_STATUS_Bits B;     /* Bit-Field access */
} GTM_AXIM_SLOT_STATUS;

/* FIFO data memory */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_FIFO_MEMORY_Bits B;          /* Bit-Field access */
} GTM_FIFO_MEMORY;

/* Control Register 0 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_CTRL_0_Bits B;          /* Bit-Field access */
} GTM_DPLL_CTRL_0;

/* Control Register 1 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_CTRL_1_Bits B;          /* Bit-Field access */
} GTM_DPLL_CTRL_1;

/* Action Enable Register  */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_CTRL_2_Bits B;          /* Bit-Field access */
} GTM_DPLL_CTRL_2;

/* Action Enable Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_CTRL_3_Bits B;          /* Bit-Field access */
} GTM_DPLL_CTRL_3;

/* Action Enable Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_CTRL_4_Bits B;          /* Bit-Field access */
} GTM_DPLL_CTRL_4;

/* Action Enable Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_CTRL_5_Bits B;          /* Bit-Field access */
} GTM_DPLL_CTRL_5;

/* Action Status Register including Shadow Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_ACT_STA_Bits B;         /* Bit-Field access */
} GTM_DPLL_ACT_STA;

/* Offset and Switch old/new Address Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_OSW_Bits B;             /* Bit-Field access */
} GTM_DPLL_OSW;

/* Address Offset Register of RAM 2 Regions */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_AOSV_2_Bits B;          /* Bit-Field access */
} GTM_DPLL_AOSV_2;

/* Actual RAM Pointer Address for TRIGGER */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_APT_Bits B;             /* Bit-Field access */
} GTM_DPLL_APT;

/* Actual RAM Pointer Address for STATE */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_APS_Bits B;             /* Bit-Field access */
} GTM_DPLL_APS;

/* Actual RAM Pointer Address for Region 2c */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_APT_2C_Bits B;          /* Bit-Field access */
} GTM_DPLL_APT_2C;

/* Actual RAM Pointer Address for RAM region 1c3 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_APS_1C3_Bits B;         /* Bit-Field access */
} GTM_DPLL_APS_1C3;

/* Number of Recent TRIGGER Events used for Calculations */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_NUTC_Bits B;            /* Bit-Field access */
} GTM_DPLL_NUTC;

/* Number of Recent STATE Events used for Calculations */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_NUSC_Bits B;            /* Bit-Field access */
} GTM_DPLL_NUSC;

/* Number of Active TRIGGER Events to Interrupt */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_NTI_CNT_Bits B;         /* Bit-Field access */
} GTM_DPLL_NTI_CNT;

/* Interrupt Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_IRQ_NOTIFY_Bits B;      /* Bit-Field access */
} GTM_DPLL_IRQ_NOTIFY;

/* Interrupt Enable Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_IRQ_EN_Bits B;          /* Bit-Field access */
} GTM_DPLL_IRQ_EN;

/* Force Interrupt Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_IRQ_FORCINT_Bits B;     /* Bit-Field access */
} GTM_DPLL_IRQ_FORCINT;

/* Interrupt Request Mode */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_IRQ_MODE_Bits B;        /* Bit-Field access */
} GTM_DPLL_IRQ_MODE;

/* Error Interrupt Enable Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_EIRQ_EN_Bits B;         /* Bit-Field access */
} GTM_DPLL_EIRQ_EN;

/* Counter Value of Sent SUB_INC1 Pulses */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_INC_CNT1_Bits B;        /* Bit-Field access */
} GTM_DPLL_INC_CNT1;

/* Counter Value of sent SUB_INC2 values (for DPLL_CTRL_1.SMC=1 and DPLL_CTRL_0.RMO=1) */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_INC_CNT2_Bits B;        /* Bit-Field access */
} GTM_DPLL_INC_CNT2;

/* TRIGGER Time Stamp Field Offset at Synchronization Time */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_APT_SYNC_Bits B;        /* Bit-Field access */
} GTM_DPLL_APT_SYNC;

/* STATE Time Stamp Field Offset at Synchronization Time */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_APS_SYNC_Bits B;        /* Bit-Field access */
} GTM_DPLL_APS_SYNC;

/* Time Stamp Value for the last active TRIGGER */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_TBU_TS0_T_Bits B;       /* Bit-Field access */
} GTM_DPLL_TBU_TS0_T;

/* Time Stamp Value for the last active STATE */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_TBU_TS0_S_Bits B;       /* Bit-Field access */
} GTM_DPLL_TBU_TS0_S;

/* ADD_IN Value in Direct Load Mode for TRIGGER */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_ADD_IN_LD1_Bits B;      /* Bit-Field access */
} GTM_DPLL_ADD_IN_LD1;

/* ADD_IN Value in Direct Load Mode for STATE */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_ADD_IN_LD2_Bits B;      /* Bit-Field access */
} GTM_DPLL_ADD_IN_LD2;

/* Status Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_STATUS_Bits B;          /* Bit-Field access */
} GTM_DPLL_STATUS;

/* ID Information for Input Signal PMTR[n] (Position minus Time Request) */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_ID_PMTR_Bits B;         /* Bit-Field access */
} GTM_DPLL_ID_PMTR;

/* Shadow Register of DPLL_CTRL_0 controlled by an active TRIGGER Slope */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_CTRL_0_SHADOW_TRIGGER_Bits B;    /* Bit-Field access */
} GTM_DPLL_CTRL_0_SHADOW_TRIGGER;

/* Shadow Register of DPLL_CTRL_0 controlled by an active STATE Slope */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_CTRL_0_SHADOW_STATE_Bits B;    /* Bit-Field access */
} GTM_DPLL_CTRL_0_SHADOW_STATE;

/* Shadow Register of DPLL_CTRL_1 controlled by an active TRIGGER Slope */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_CTRL_1_SHADOW_TRIGGER_Bits B;    /* Bit-Field access */
} GTM_DPLL_CTRL_1_SHADOW_TRIGGER;

/* DPLL Shadow Register of DPLL_CTRL_1 controlled by an active STATE Slope */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_CTRL_1_SHADOW_STATE_Bits B;    /* Bit-Field access */
} GTM_DPLL_CTRL_1_SHADOW_STATE;

/* Register to control the RAM Initialization */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_RAM_INI_Bits B;         /* Bit-Field access */
} GTM_DPLL_RAM_INI;

/* Position Request for Action [n] */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_PSA_Bits B;             /* Bit-Field access */
} GTM_DPLL_PSA;

/* Time to React for Action [n] */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_DLA_Bits B;             /* Bit-Field access */
} GTM_DPLL_DLA;

/* Calculated Relative Time to Action [n] */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_NA_Bits B;              /* Bit-Field access */
} GTM_DPLL_NA;

/* Calculated Relative Time to Action [n] */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_DTA_Bits B;             /* Bit-Field access */
} GTM_DPLL_DTA;

/* Actual TRIGGER Time Stamp Value */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_TS_T_Bits B;            /* Bit-Field access */
} GTM_DPLL_TS_T;

/* Previous TRIGGER Time Stamp Value */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_TS_T_OLD_Bits B;        /* Bit-Field access */
} GTM_DPLL_TS_T_OLD;

/* Actual TRIGGER Filter value */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_FTV_T_Bits B;           /* Bit-Field access */
} GTM_DPLL_FTV_T;

/* DPLL RAM1B reserved  data */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_RAM1B_RSVD_Bits B;      /* Bit-Field access */
} GTM_DPLL_RAM1B_RSVD;

/* Actual STATE Time Stamp Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_TS_S_Bits B;            /* Bit-Field access */
} GTM_DPLL_TS_S;

/* Previous STATE Time Stamp Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_TS_S_OLD_Bits B;        /* Bit-Field access */
} GTM_DPLL_TS_S_OLD;

/* Actual STATE Filter Value */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_FTV_S_Bits B;           /* Bit-Field access */
} GTM_DPLL_FTV_S;

/* TRIGGER Hold Time Min. Value */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_THMI_Bits B;            /* Bit-Field access */
} GTM_DPLL_THMI;

/* TRIGGER Hold Time Max. Value */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_THMA_Bits B;            /* Bit-Field access */
} GTM_DPLL_THMA;

/* Measured TRIGGER Hold Time Value */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_THVAL_Bits B;           /* Bit-Field access */
} GTM_DPLL_THVAL;

/* Time Out Value of Active TRIGGER Slope (for missing TRIGGER generation) */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_TOV_Bits B;             /* Bit-Field access */
} GTM_DPLL_TOV;

/* Time Out Value of active STATE Slope (for missing STATE generation) */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_TOV_S_Bits B;           /* Bit-Field access */
} GTM_DPLL_TOV_S;

/* Calculated ADD_IN Value for SUB_INC1 Generation */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_ADD_IN_CAL1_Bits B;     /* Bit-Field access */
} GTM_DPLL_ADD_IN_CAL1;

/* Calculated ADD_IN Value for SUB_INC2 Generation */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_ADD_IN_CAL2_Bits B;     /* Bit-Field access */
} GTM_DPLL_ADD_IN_CAL2;

/* Missing Pulses to be Added or Subtracted Directly  */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_MPVAL1_Bits B;          /* Bit-Field access */
} GTM_DPLL_MPVAL1;

/* Missing Pulses to be Added or Subtracted Directly */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_MPVAL2_Bits B;          /* Bit-Field access */
} GTM_DPLL_MPVAL2;

/* Target Number of Pulses to be sent in Normal Mode */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_NMB_T_TAR_Bits B;       /* Bit-Field access */
} GTM_DPLL_NMB_T_TAR;

/* Last but one Target Number of Pulses to be sent in Normal Mode  */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_NMB_T_TAR_OLD_Bits B;   /* Bit-Field access */
} GTM_DPLL_NMB_T_TAR_OLD;

/* Target Number of Pulses to be sent in Emergency Mode */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_NMB_S_TAR_Bits B;       /* Bit-Field access */
} GTM_DPLL_NMB_S_TAR;

/* Last but one Target Number of Pulses to be sent in Emergency Mode */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_NMB_S_TAR_OLD_Bits B;   /* Bit-Field access */
} GTM_DPLL_NMB_S_TAR_OLD;

/* Reciprocal Value of the Expected Increment Duration of TRIGGER */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_RCDT_TX_Bits B;         /* Bit-Field access */
} GTM_DPLL_RCDT_TX;

/* Reciprocal Value of the Expected Increment Duration of STATE */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_RCDT_SX_Bits B;         /* Bit-Field access */
} GTM_DPLL_RCDT_SX;

/* Reciprocal Value of the Expected Nominal Increment Duration of TRIGGER */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_RCDT_TX_NOM_Bits B;     /* Bit-Field access */
} GTM_DPLL_RCDT_TX_NOM;

/* Reciprocal Value of the Expected Nominal Increment Duration of STATE */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_RCDT_SX_NOM_Bits B;     /* Bit-Field access */
} GTM_DPLL_RCDT_SX_NOM;

/* Reciprocal Value of the Last Increment of TRIGGER */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_RDT_T_ACT_Bits B;       /* Bit-Field access */
} GTM_DPLL_RDT_T_ACT;

/* Reciprocal Value of the Last Increment of STATE */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_RDT_S_ACT_Bits B;       /* Bit-Field access */
} GTM_DPLL_RDT_S_ACT;

/* Duration of the Last TRIGGER Increment */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_DT_T_ACT_Bits B;        /* Bit-Field access */
} GTM_DPLL_DT_T_ACT;

/* Duration of the Last STATE Increment */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_DT_S_ACT_Bits B;        /* Bit-Field access */
} GTM_DPLL_DT_S_ACT;

/* Difference of Prediction to Actual Value of the Last TRIGGER Increment */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_EDT_T_Bits B;           /* Bit-Field access */
} GTM_DPLL_EDT_T;

/* Weighted Difference of Prediction Errors of TRIGGER */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_MEDT_T_Bits B;          /* Bit-Field access */
} GTM_DPLL_MEDT_T;

/* Difference of Prediction to Actual Value of the Last STATE Increment */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_EDT_S_Bits B;           /* Bit-Field access */
} GTM_DPLL_EDT_S;

/* Weighted Difference of Prediction Errors of STATE */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_MEDT_S_Bits B;          /* Bit-Field access */
} GTM_DPLL_MEDT_S;

/* Prediction of the Actual TRIGGER Increment Duration */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_CDT_TX_Bits B;          /* Bit-Field access */
} GTM_DPLL_CDT_TX;

/* Prediction of the Actual STATE Increment Duration */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_CDT_SX_Bits B;          /* Bit-Field access */
} GTM_DPLL_CDT_SX;

/* Prediction of the Nominal TRIGGER Increment Duration */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_CDT_TX_NOM_Bits B;      /* Bit-Field access */
} GTM_DPLL_CDT_TX_NOM;

/* Prediction of the Nominal STATE Increment Duration */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_CDT_SX_NOM_Bits B;      /* Bit-Field access */
} GTM_DPLL_CDT_SX_NOM;

/* TRIGGER Locking Range */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_TLR_Bits B;             /* Bit-Field access */
} GTM_DPLL_TLR;

/* STATE Locking Range */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_SLR_Bits B;             /* Bit-Field access */
} GTM_DPLL_SLR;

/* Projected Increment Sum Relations for Action [n] */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_PDT_Bits B;             /* Bit-Field access */
} GTM_DPLL_PDT;

/* Calculated Number of Sub-Pulses between two nominal STATE Events for DPLL_CTRL_1.SMC = 0 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_MLS1_Bits B;            /* Bit-Field access */
} GTM_DPLL_MLS1;

/* Calculated Number of Sub-Pulses between two nominal STATE Events for DPLL_CTRL_1.SMC=1 and RMO=1 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_MLS2_Bits B;            /* Bit-Field access */
} GTM_DPLL_MLS2;

/* Number of SUB_INC1 pulses in continuous mode */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_CNT_NUM_1_Bits B;       /* Bit-Field access */
} GTM_DPLL_CNT_NUM_1;

/* Number of SUB_INC2 pulses in continuous mode */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_CNT_NUM_2_Bits B;       /* Bit-Field access */
} GTM_DPLL_CNT_NUM_2;

/* Plausibility Value of Next TRIGGER Slope */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_PVT_Bits B;             /* Bit-Field access */
} GTM_DPLL_PVT;

/* Actual Calculated Position Stamp of TRIGGER */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_PSTC_Bits B;            /* Bit-Field access */
} GTM_DPLL_PSTC;

/* Actual Calculated Position Stamp of STATE */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_PSSC_Bits B;            /* Bit-Field access */
} GTM_DPLL_PSSC;

/* Measured Position Stamp at Last TRIGGER Input */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_PSTM_Bits B;            /* Bit-Field access */
} GTM_DPLL_PSTM;

/* Measured Position Stamp at Last but one TRIGGER Input */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_PSTM_OLD_Bits B;        /* Bit-Field access */
} GTM_DPLL_PSTM_OLD;

/* Measured Position Stamp at Last STATE Input */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_PSSM_Bits B;            /* Bit-Field access */
} GTM_DPLL_PSSM;

/* Measured Position Stamp at Last but one STATE Input */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_PSSM_OLD_Bits B;        /* Bit-Field access */
} GTM_DPLL_PSSM_OLD;

/* Number of Pulses to be sent in Normal Mode */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_NMB_T_Bits B;           /* Bit-Field access */
} GTM_DPLL_NMB_T;

/* Number of Pulses to be sent in Emergency Mode */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_NMB_S_Bits B;           /* Bit-Field access */
} GTM_DPLL_NMB_S;

/* Reciprocal Values of the Nominal STATE Increment Duration in FULL_SCALE for maximum [p] entries in profile for STATE (DPLL_ADT_S[p]) */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_RDT_S_Bits B;           /* Bit-Field access */
} GTM_DPLL_RDT_S;

/* Time Stamp Values of the Nominal STATE Events in FULL_SCALE for maximum [p] entries in profile for STATE (DPLL_ADT_S[p]) */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_TSF_S_Bits B;           /* Bit-Field access */
} GTM_DPLL_TSF_S;

/* Adapt and Profile Values of the STATE Increments in FULL_SCALE for maximum [p] entries */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_ADT_S_Bits B;           /* Bit-Field access */
} GTM_DPLL_ADT_S;

/* Nominal STATE Increment Duration in FULL_SCALE for maximum [p] entries in profile for STATE (DPLL_ADT_S[p]) */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_DT_S_Bits B;            /* Bit-Field access */
} GTM_DPLL_DT_S;

/* Calculated Time Value to start Action [n] */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_TSAC_Bits B;            /* Bit-Field access */
} GTM_DPLL_TSAC;

/* Calculated Position Value to start Action [n] */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_PSAC_Bits B;            /* Bit-Field access */
} GTM_DPLL_PSAC;

/* Control Bits for NOAC Actions */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_ACB_Bits B;             /* Bit-Field access */
} GTM_DPLL_ACB;

/* Control Register 11 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_CTRL_11_Bits B;         /* Bit-Field access */
} GTM_DPLL_CTRL_11;

/* Measured TRIGGER Hold Time Value 2 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_THVAL2_Bits B;          /* Bit-Field access */
} GTM_DPLL_THVAL2;

/* TRIGGER input delay */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_TIDEL_Bits B;           /* Bit-Field access */
} GTM_DPLL_TIDEL;

/* STATE input delay */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_SIDEL_Bits B;           /* Bit-Field access */
} GTM_DPLL_SIDEL;

/* STATE Time Stamp Field Offset at Synchronization Time */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_APS_SYNC_EXT_Bits B;    /* Bit-Field access */
} GTM_DPLL_APS_SYNC_EXT;

/* STATE Time Stamp Field Offset at Synchronization Time */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_CTRL_EXT_Bits B;        /* Bit-Field access */
} GTM_DPLL_CTRL_EXT;

/* Actual RAM Pointer Address for STATE */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_APS_EXT_Bits B;         /* Bit-Field access */
} GTM_DPLL_APS_EXT;

/* Actual RAM Pointer Address for RAM region 1c3 (DPLL_CTRL_11.STATE_EXT=1) */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_APS_1C3_EXT_Bits B;     /* Bit-Field access */
} GTM_DPLL_APS_1C3_EXT;

/* Status of the state machine states */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_STA_Bits B;             /* Bit-Field access */
} GTM_DPLL_STA;

/* Start value of ADD_IN_ADDER1  */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_INCF1_OFFSET_Bits B;    /* Bit-Field access */
} GTM_DPLL_INCF1_OFFSET;

/* Start value of the ADD_IN_ADDER2 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_INCF2_OFFSET_Bits B;    /* Bit-Field access */
} GTM_DPLL_INCF2_OFFSET;

/* Start value of DT_T_ACT */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_DT_T_START_Bits B;      /* Bit-Field access */
} GTM_DPLL_DT_T_START;

/* Start value of DT_S_ACT */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_DT_S_START_Bits B;      /* Bit-Field access */
} GTM_DPLL_DT_S_START;

/* Notify values for DPLL_STA */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_STA_MASK_Bits B;        /* Bit-Field access */
} GTM_DPLL_STA_MASK;

/* DPLL STA Flags */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_STA_FLAG_Bits B;        /* Bit-Field access */
} GTM_DPLL_STA_FLAG;

/* Notify value of DPLL_INC_CNT1 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_INC_CNT1_MASK_Bits B;   /* Bit-Field access */
} GTM_DPLL_INC_CNT1_MASK;

/* Notify value of DPLL_INC_CNT2 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_INC_CNT2_MASK_Bits B;   /* Bit-Field access */
} GTM_DPLL_INC_CNT2_MASK;

/* Number of Recent STATE Events used for Calculations */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_NUSC_EXT1_Bits B;       /* Bit-Field access */
} GTM_DPLL_NUSC_EXT1;

/* Number of Recent STATE Events used for Calculations */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_NUSC_EXT2_Bits B;       /* Bit-Field access */
} GTM_DPLL_NUSC_EXT2;

/* Minmum value of predicted nominal increment of TRIGGER */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_CTN_MIN_Bits B;         /* Bit-Field access */
} GTM_DPLL_CTN_MIN;

/* Maximum value of predicted nominal increment of TRIGGER */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_CTN_MAX_Bits B;         /* Bit-Field access */
} GTM_DPLL_CTN_MAX;

/* Minmum value of predicted nominal increment of STATE */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_CSN_MIN_Bits B;         /* Bit-Field access */
} GTM_DPLL_CSN_MIN;

/* Maximum value of predicted nominal increment of STATE */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_CSN_MAX_Bits B;         /* Bit-Field access */
} GTM_DPLL_CSN_MAX;

/* Software triggered input events */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_SW_TRIG_Bits B;         /* Bit-Field access */
} GTM_DPLL_SW_TRIG;

/* Missing pulses of TRIGGER */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_MP_T_Bits B;            /* Bit-Field access */
} GTM_DPLL_MP_T;

/* Missing pulses of STATE */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_MP_S_Bits B;            /* Bit-Field access */
} GTM_DPLL_MP_S;

/* DPLL control register 12 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_CTRL_12_Bits B;         /* Bit-Field access */
} GTM_DPLL_CTRL_12;

/* DPLL memory RR2 */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLL_RR2_Bits B;             /* Bit-Field access */
} GTM_DPLL_RR2;

/* MCS[i] memory region */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MCS_MEM_Bits B;              /* Bit-Field access */
} GTM_MCS_MEM;

/* TIM[i] input select register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIMINMUX_Bits B;             /* Bit-Field access */
} GTM_TIMINMUX;

/* TOM output select register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TOUTMUX_Bits B;              /* Bit-Field access */
} GTM_TOUTMUX;

/* DSADC input select register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DSADCINMUX_Bits B;           /* Bit-Field access */
} GTM_DSADCINMUX;

/* DSADC output select register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DSADCOUTMUX_Bits B;          /* Bit-Field access */
} GTM_DSADCOUTMUX;

/* DSADC output select register (THA6412 only) */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DSADCOUTMUX1_Bits B;         /* Bit-Field access */
} GTM_DSADCOUTMUX1;

/* ADCTRIG[i] output select 0 register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ADCTRIG_OUTMUX0_Bits B;         /* Bit-Field access */
} GTM_ADCTRIG_OUTMUX0;

/* ADCTRIG[i] output select 1 register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_ADCTRIG_OUTMUX1_Bits B;         /* Bit-Field access */
} GTM_ADCTRIG_OUTMUX1;

/* Data exchange output control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DEXOUTCON_Bits B;             /* Bit-Field access */
} GTM_DEXOUTCON;

/* Trigger output register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TRIGOUTCON_Bits B;              /* Bit-Field access */
} GTM_TRIGOUTCON;

/* Interrupt output register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_INTOUTCON_Bits B;               /* Bit-Field access */
} GTM_INTOUTCON;

/* Trigger output select register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TRIGOUTMUX_Bits B;        /* Bit-Field access */
} GTM_TRIGOUTMUX;

/* MCS interrupt status register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_INTSTS_Bits B;           /* Bit-Field access */
} GTM_INTSTS;

/* MCS interrupt clear register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_INTSTSCLR_Bits B;            /* Bit-Field access */
} GTM_INTSTSCLR;

/* Data exchange input control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DEXINCON_Bits B;             /* Bit-Field access */
} GTM_DEXINCON;

/* Data input input register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DATAIN_Bits B;               /* Bit-Field access */
} GTM_DATAIN;

/* MSC set [i] control 0 register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MSCSET_MUX0_Bits B;          /* Bit-Field access */
} GTM_MSCSET_MUX0;

/* MSC set [i] control 1 register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MSCSET_MUX1_Bits B;          /* Bit-Field access */
} GTM_MSCSET_MUX1;

/* MSC set [i] control 2 register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MSCSET_MUX2_Bits B;          /* Bit-Field access */
} GTM_MSCSET_MUX2;

/* MSC set [i] control 3 register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MSCSET_MUX3_Bits B;          /* Bit-Field access */
} GTM_MSCSET_MUX3;

/* MSC0 input multiplex register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_MSCMUX_Bits B;               /* Bit-Field access */
} GTM_MSCMUX;

/* DTM_AUX input multiplex register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DTMAUXINMUX_Bits B;          /* Bit-Field access */
} GTM_DTMAUXINMUX;

/* CAN output multiplex register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_CANOUTMUX_Bits B;            /* Bit-Field access */
} GTM_CANOUTMUX;

/* RDC output multiplex register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_RDCOUTMUX_Bits B;            /* Bit-Field access */
} GTM_RDCOUTMUX;

/* RDC L2 output multiplex register (THA6412 only) */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_RDCOUTL2MUX_Bits B;          /* Bit-Field access */
} GTM_RDCOUTL2MUX;

/* Interrupt Request and DMA Request Enable register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_IDRQEN_Bits B;                 /* Bit-Field access */
} GTM_IDRQEN;

/* DMA Level 1 Multiplex register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DMAL1MUXN_Bits B;            /* Bit-Field access */
} GTM_DMAL1MUX;

/* DMA Level 1 Common Multiplex register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DMAL1COMMUX_Bits B;          /* Bit-Field access */
} GTM_DMAL1COMMUX;

/* DMA Level 2 Multiplex register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DMAL2MUX_Bits B;               /* Bit-Field access */
} GTM_DMAL2MUX;

/* GTM Debug Control register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DBGCTRL_Bits B;               /* Bit-Field access */
} GTM_DBGCTRL;

/* GTM TIO Input Multiplex register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIOINMUX_Bits B;               /* Bit-Field access */
} GTM_TIOINMUX;

/* GTM High Resolution PWM Control register (THA6412 only) */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_HRPWMCTRL_Bits B;               /* Bit-Field access */
} GTM_HRPWMCTRL;

/* GTM High Resolution PWM Control Select register (THA6412 only) */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_HRPWMCORNELSEL_Bits B;       /* Bit-Field access */
} GTM_HRPWMCORNELSEL;

/* GTM High Resolution PWM Output Multiplex register (THA6412 only) */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_HRPWMOUTMUX_Bits B;          /* Bit-Field access */
} GTM_HRPWMOUTMUX;

/* PSI5 Output Multiplex register (THA6412 only) */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_PSI5OUTMUX_Bits B;               /* Bit-Field access */
} GTM_PSI5OUTMUX;

/* TIO Output Multiplex register (THA6412 only) */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_TIOOUTMUX_Bits B;               /* Bit-Field access */
} GTM_TIOOUTMUX;

/* RAM Data ECC Check Enable register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_RAMECCEN_Bits B;               /* Bit-Field access */
} GTM_RAMECCEN;

/* RAM Data REMAP Function Enable register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_RAMREMAPEN_Bits B;           /* Bit-Field access */
} GTM_RAMREMAPEN;

/* RAM Hardware Fault Injection Enable register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_RAMHWINJ_Bits B;                /* Bit-Field access */
} GTM_RAMHWINJ;

/* FIFO RAM Alarm Clear Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_FIFORAM_ALARMCLR_Bits B;     /* Bit-Field access */
} GTM_FIFORAM_ALARMCLR;

/* FIFO Error Address Valid Signal Clear Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                            /* Unsigned access */
    GTM_FIFORAM_ERRADDRVLDCLR_Bits B;   /* Bit-Field access */
} GTM_FIFORAM_ERRADDRVLDCLR;

/* FIFO Single Bit Error Address Recording Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                            /* Unsigned access */
    GTM_FIFORAM_SERRADDR_Bits B;           /* Bit-Field access */
} GTM_FIFORAM_SERRADDR;

/* FIFO Multi-bit Error Address Recording Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                            /* Unsigned access */
    GTM_FIFORAM_MERRADDR_Bits B;           /* Bit-Field access */
} GTM_FIFORAM_MERRADDR;

/* DPLL RAM Alarm Clear Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                        /* Unsigned access */
    GTM_DPLLRAM_ALARMCLR_Bits B;     /* Bit-Field access */
} GTM_DPLLRAM_ALARMCLR;

/* DPLL Error Address Valid Signal Clear Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                            /* Unsigned access */
    GTM_DPLLRAM_ERRADDRVLDCLR_Bits B;   /* Bit-Field access */
} GTM_DPLLRAM_ERRADDRVLDCLR;

/* DPLL Single Bit Error Address Recording Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                            /* Unsigned access */
    GTM_DPLLRAM_SERRADDR_Bits B;           /* Bit-Field access */
} GTM_DPLLRAM_SERRADDR;

/* DPLL Multi-bit Error Address Recording Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                            /* Unsigned access */
    GTM_DPLLRAM_MERRADDR_Bits B;           /* Bit-Field access */
} GTM_DPLLRAM_MERRADDR;

/* Single Bit Error Status Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                            /* Unsigned access */
    GTM_SBESTS_Bits B;                   /* Bit-Field access */
} GTM_SBESTS;

/* Multi-bit Error Status Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                            /* Unsigned access */
    GTM_MBESTS_Bits B;                   /* Bit-Field access */
} GTM_MBESTS;

/* Single Bit Error Overflow State Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                            /* Unsigned access */
    GTM_SROSTS_Bits B;                   /* Bit-Field access */
} GTM_SROSTS;

/* DMA Timeout Configuration Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                            /* Unsigned access */
    GTM_DMATOCFG_Bits B;                   /* Bit-Field access */
} GTM_DMATOCFG;

/* DMA Timeout Safety Mechanism Enable Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                            /* Unsigned access */
    GTM_DMATOSAFETYEN_Bits B;           /* Bit-Field access */
} GTM_DMATOSAFETYEN;

/* DMA Timeout Fault Injection Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                            /* Unsigned access */
    GTM_DMATOFAULTINJ_Bits B;           /* Bit-Field access */
} GTM_DMATOFAULTINJ;

/* DMA Timeout Alarm Clear Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                            /* Unsigned access */
    GTM_DMATOALARMCLR_Bits B;           /* Bit-Field access */
} GTM_DMATOALARMCLR;

/* DMA Timeout Channel Status Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                            /* Unsigned access */
    GTM_DMATOCHSTS_Bits B;               /* Bit-Field access */
} GTM_DMATOCHSTS;

/* Register Safety Mechanism */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                            /* Unsigned access */
    GTM_REGSAFETYEN_Bits B;               /* Bit-Field access */
} GTM_REGSAFETYEN;

/* Register Alarm Status Clear */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                            /* Unsigned access */
    GTM_REGALARMCLR_Bits B;               /* Bit-Field access */
} GTM_REGALARMCLR;

/* Register Alarm Status */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                            /* Unsigned access */
    GTM_REGALARMSTS_Bits B;               /* Bit-Field access */
} GTM_REGALARMSTS;

/* Illegal Access Alarm Clearing Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                            /* Unsigned access */
    GTM_REGIACLR_Bits B;                   /* Bit-Field access */
} GTM_REGIACLR;

/* Illegal Access Alarm Status Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                            /* Unsigned access */
    GTM_REGIAALARMSTS_Bits B;            /* Bit-Field access */
} GTM_REGIAALARMSTS;

/* ADC Data Ecc Alarm Enable Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                            /* Unsigned access */
    GTM_ADALARMEN_Bits B;                /* Bit-Field access */
} GTM_ADALARMEN;

/* ADC Data Ecc Alarm Clear Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                            /* Unsigned access */
    GTM_ADALARMCLR_Bits B;                /* Bit-Field access */
} GTM_ADALARMCLR;

/* ADC Data Ecc Alarm Status Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                            /* Unsigned access */
    GTM_ADALARMSTS_Bits B;               /* Bit-Field access */
} GTM_ADALARMSTS;

/* GTM Debug Global Control Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                            /* Unsigned access */
    GTM_DGCR_Bits B;                     /* Bit-Field access */
} GTM_DGCR;

/* GTM Debug Halt Control Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                            /* Unsigned access */
    GTM_DHCR_Bits B;                     /* Bit-Field access */
} GTM_DHCR;

/* GTM Debug Halt Status Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                            /* Unsigned access */
    GTM_DHSR_Bits B;                     /* Bit-Field access */
} GTM_DHSR;

/* MCS Break Point Enable Register */
typedef union
/* #Violation: gtm_register_h_REF_1 */
{
    ureg32 U;                            /* Unsigned access */
    GTM_DMCSBPEN_Bits B;                 /* Bit-Field access */
} GTM_DMCSBPEN;

/* BRIDGE object */
typedef volatile struct
{
    GTM_BRIDGE_MODE        MODE;        /* 0x0 - GTM AEI bridge mode register */
    GTM_BRIDGE_PTR1        PTR1;        /* 0x4 - GTM AEI bridge pointer 1 register */
    GTM_BRIDGE_PTR2        PTR2;        /* 0x8 - GTM AEI bridge pointer 2 register */
} GTM_BRIDGE;

/* CMU_CLK object */
/* #Violation: gtm_register_h_REF_3 */
typedef volatile struct
{
    GTM_CMU_CLK__CTRL        CTRL;        /* 0x0 - CMU control for clock resolution generator [x] */
} GTM_CMU_CLK;

/* CMU_ECLK object */
/* #Violation: gtm_register_h_REF_3 */
typedef volatile struct
{
    GTM_CMU_ECLK_NUM        NUM;        /* 0x0 - The numerator for the external clock resolution generator [z] */
    GTM_CMU_ECLK_DEN        DEN;        /* 0x4 - The denominator for the external clock resolution generator [z] */
} GTM_CMU_ECLK;

/* CMU_FXCLK object */
typedef volatile struct
{
    GTM_CMU_FXCLK_CTRL        CTRL;        /* 0x0 - CMU control for selection of FCR subblock input */
} GTM_CMU_FXCLK;

/* CMU object */
/* #Violation: gtm_register_h_REF_3 */
typedef volatile struct
{
    GTM_CMU_CLK_EN          CLK_EN;          /* 0x0 - CMU clock enable */
    GTM_CMU_GCLK_NUM        GCLK_NUM;        /* 0x4 - The numerator for CMU global clock resolution generator */
    GTM_CMU_GCLK_DEN        GCLK_DEN;        /* 0x8 - The denominator for CMU global clock resolution generator */
    /* #Violation: gtm_register_h_REF_2 */
    GTM_CMU_CLK             CLK[8];          /* 0xC - GTM_CMU_CLK */
    /* #Violation: gtm_register_h_REF_2 */
    GTM_CMU_ECLK            ECLK[3];         /* 0x2C - GTM_CMU_ECLK */
    GTM_CMU_FXCLK           FXCLK;           /* 0x44 - GTM_CMU_FXCLK */
    GTM_CMU_GLB_CTRL        GLB_CTRL;        /* 0x48 - CMU synchronizing ARU and clock source */
    GTM_CMU_CLK_CTRL        CLK_CTRL;        /* 0x4C - CMU control for clock resolution generator */
} GTM_CMU;

/* TBU object */
typedef volatile struct
{
    GTM_TBU_CHEN                    CHEN;                    /* 0x0 - TBU global channel enable */
    GTM_TBU_CH0_CTRL                CH0_CTRL;                /* 0x4 - TBU channel 0 control */
    GTM_TBU_CH_0_BASE               CH0_BASE;                /* 0x8 - TBU channel 0 base */
    GTM_TBU_CH1_CTRL                CH1_CTRL;                /* 0xC - TBU channel 1 control */
    GTM_TBU_CH_X_BASE               CH1_BASE;                /* 0x10 - TBU channel 1 base */
    GTM_TBU_CH2_CTRL                CH2_CTRL;                /* 0x14 - TBU channel 2 control */
    GTM_TBU_CH_X_BASE               CH2_BASE;                /* 0x18 - TBU channel 2 base */
    GTM_TBU_CH3_CTRL                CH3_CTRL;                /* 0x1C - TBU channel 3 control */
    GTM_TBU_CH_X_BASE               CH3_BASE;                /* 0x20 - TBU channel 3 base */
    GTM_TBU_CH3_BASE_MARK           CH3_BASE_MARK;           /* 0x24 - TBU channel 3 modulo value */
    GTM_TBU_CH3_BASE_CAPTURE        CH3_BASE_CAPTURE;        /* 0x28 - TBU channel 3 base captured */
} GTM_TBU;

/* ARU_DBG object */
typedef volatile struct
{
    GTM_ARU_DBG_ACCESS0        ACCESS0;        /* 0x0 - ARU debug access channel 0 */
    GTM_ARU_DBG_DATA0_H        DATA0_H;        /* 0x4 - ARU debug access 0 transfer register upper data word */
    GTM_ARU_DBG_DATA0_L        DATA0_L;        /* 0x8 - ARU debug access 0 transfer register lower data word */
    GTM_ARU_DBG_ACCESS1        ACCESS1;        /* 0xC - ARU debug access channel 0 */
    GTM_ARU_DBG_DATA1_H        DATA1_H;        /* 0x10 - ARU debug access 1 transfer register upper data word */
    GTM_ARU_DBG_DATA1_L        DATA1_L;        /* 0x14 - ARU debug access 1 transfer register lower data word */
} GTM_ARU_DBG;

/* ARU_IRQ object */
typedef volatile struct
{
    GTM_ARU_IRQ_NOTIFY         NOTIFY;         /* 0x0 - ARU interrupt notification register */
    GTM_ARU_IRQ_EN             EN;             /* 0x4 - ARU interrupt enable register */
    GTM_ARU_IRQ_FORCINT        FORCINT;        /* 0x8 - ARU force interrupt register */
    GTM_ARU_IRQ_MODE           MODE;           /* 0xC - ARU interrupt mode register */
} GTM_ARU_IRQ;

/* ARU object */
typedef volatile struct
{
    GTM_ARU_ACCESS                   ACCESS;                      /* 0x0 - ARU access register */
    GTM_ARU_DATA_H                   DATA_H;                      /* 0x4 - ARU access register upper data word */
    GTM_ARU_DATA_L                   DATA_L;                      /* 0x8 - ARU access register lower data word */
    GTM_ARU_DBG                      DBG;                         /* 0xC - GTM_ARU_DBG */
    GTM_ARU_IRQ                      IRQ;                         /* 0x24 - GTM_ARU_IRQ */
    GTM_ARU_CADDR_END                CADDR_END;                   /* 0x34 - ARU caddr counter end value */
    uint8                            reserved_38[4];              /* 0x38 - Internal  reserved */
    GTM_ARU_CTRL                     CTRL;                        /* 0x3C - ARU enable dynamic routing */
    GTM_ARU_DYN_CTRL                 DYN_CTRL[2];                 /* 0x40 - ARU [g] dynamic routing control register */
    GTM_ARU_DYN_ROUTE_LOW            DYN_ROUTE_LOW[2];            /* 0x48 - ARU [g] lower bits of DYN_ROUTE register */
    GTM_ARU_DYN_ROUTE_HIGH           DYN_ROUTE_HIGH[2];           /* 0x50 - ARU [g] higher bits of DYN_ROUTE register */
    GTM_ARU_DYN_ROUTE_SR_LOW         DYN_ROUTE_SR_LOW[2];         /* 0x58 - ARU [g] shadow register of DYN_ROUTE register lower bits */
    GTM_ARU_DYN_ROUTE_SR_HIGH        DYN_ROUTE_SR_HIGH[2];        /* 0x60 - ARU [g] shadow register of DYN_ROUTE register higher bits */
    GTM_ARU_DYN_RDADDR               DYN_RDADDR[2];               /* 0x68 - ARU [g] master ID for dynamic routing */
    uint8                            reserved_70[12];             /* 0x70 - Internal  reserved */
    GTM_ARU_CADDR                    CADDR;                       /* 0x7C - ARU caddr counter value */
} GTM_ARU;

/* BRC_SRC object */
typedef volatile struct
{
    GTM_BRC_SRC_ADDR        ADDR;        /* 0x0 - BRC read address for input channel [x] */
    GTM_BRC_SRC_DEST        DEST;        /* 0x4 - BRC destination channels for input channel [x] */
} GTM_BRC_SRC;

/* BRC_IRQ object */
typedef volatile struct
{
    GTM_BRC_IRQ_NOTIFY         NOTIFY;         /* 0x0 - BRC interrupt notification register */
    GTM_BRC_IRQ_EN             EN;             /* 0x4 - BRC interrupt enable register */
    GTM_BRC_IRQ_FORCINT        FORCINT;        /* 0x8 - BRC force interrupt register */
    GTM_BRC_IRQ_MODE           MODE;           /* 0xC - BRC interrupt mode configuration register */
} GTM_BRC_IRQ;

/* BRC object */
typedef volatile struct
{
    GTM_BRC_SRC            SRC[12];        /* 0x0 - GTM_BRC_SRC */
    GTM_BRC_IRQ            IRQ;            /* 0x60 - GTM_BRC_IRQ */
    GTM_BRC_RST            RST;            /* 0x70 - BRC software reset register */
    GTM_BRC_EIRQ_EN        EIRQ_EN;        /* 0x74 - BRC error interrupt enable register */
} GTM_BRC;

/* ICM_IRQG object */
typedef volatile struct
{
    GTM_ICM_IRQG_0                R0;                      /* 0x0 - ICM Interrupt group register covering infrastructural and safety components (ARU - BRC - AEI - PSM0 - PSM1 - MAP - CMP,SPE) */
    GTM_ICM_IRQG_1                R1;                      /* 0x4 - ICM Interrupt group register covering DPLL */
    GTM_ICM_IRQG_2                R2;                      /* 0x8 - ICM Interrupt group register covering TIM0 - TIM1 - TIM2 - TIM3 */
    GTM_ICM_IRQG_3                R3;                      /* 0xC - ICM Interrupt group register covering TIM4 - TIM5 - TIM6 - TIM7 */
    GTM_ICM_IRQG_4                R4;                      /* 0x10 - ICM Interrupt group register covering MCS0 to MCS3 sub-modules */
    GTM_ICM_IRQG_5                R5;                      /* 0x14 - ICM Interrupt group register covering MCS4 to MCS7 sub-modules */
    uint8                         reserved_18[24];         /* 0x18 - Internal  reserved */
    GTM_ICM_IRQG_MEI              MEI;                     /* 0x30 - ICM Interrupt group register for module error interrupt information */
    GTM_ICM_IRQG_CEI0             CEI0;                    /* 0x34 - ICM Interrupt group register 0 for channel error interrupt information */
    GTM_ICM_IRQG_CEI1             CEI1;                    /* 0x38 - ICM Interrupt group register 1 for channel error interrupt information */
    GTM_ICM_IRQG_CEI2             CEI2;                    /* 0x3C - ICM Interrupt group register 2 for channel error interrupt information */
    GTM_ICM_IRQG_CEI3             CEI3;                    /* 0x40 - ICM Interrupt group register 3 for channel error interrupt information */
    GTM_ICM_IRQG_CEI4             CEI4;                    /* 0x44 - ICM Interrupt group register 4 for channel error interrupt information */
    uint8                         reserved_48[28];         /* 0x48 - Internal  reserved */
    GTM_ICM_IRQG_MCS_CEI          CEI_MCS[5];              /* 0x64 - ICM Interrupt group MCS[j] for Channel Error Interrupt information */
    uint8                         reserved_78[44];         /* 0x78 - Internal  reserved */
    GTM_ICM_IRQG_PSM_CEI          CEI_PSM[1];              /* 0xA4 - ICM Interrupt group PSM 0 for Channel Error Interrupt information of FIFO0 - FIFO1 - FIFO2 */
    uint8                         reserved_A8[12];         /* 0xA8 - Internal  reserved */
    GTM_ICM_IRQG_SPE_CEI          CEI_SPE;                 /* 0xB4 - ICM Interrupt group SPE for module Error Interrupt information */
    uint8                         reserved_B8[88];         /* 0xB8 - Internal  reserved */
    GTM_ICM_IRQG_CLS_0_MEI        CLS_0_MEI;               /* 0x110 - ICM Interrupt group for module Error Interrupt information for each TIM[j] - MCS[j] - SPE[j] - FIFO[j] (j=4*[g]+k - k, k=0-3{0 - ... ,3}) */
    GTM_ICM_IRQG_CLS_1_MEI        CLS_1_MEI;               /* 0x114 - ICM Interrupt group for module Error Interrupt information for each TIM[j] - MCS[j] - SPE[j] - FIFO[j] (j=4*[g]+k - k, k=0-3{0 - ... ,3}) */
    uint8                         reserved_118[8];         /* 0x118 - Internal  reserved */
    GTM_ICM_IRQG_MCS_CI           CI_MCS[5];               /* 0x120 - ICM Interrupt group MCS[j] for Channel Interrupt information */
    uint8                         reserved_134[44];        /* 0x134 - Internal  reserved */
    GTM_ICM_IRQG_PSM_CI           CI_PSM[1];               /* 0x160 - ICM Interrupt group PSM 0 for Channel Interrupt information of FIFO0 - FIFO1 - FIFO2 */
    uint8                         reserved_164[12];        /* 0x164 - Internal  reserved */
    GTM_ICM_IRQG_SPE_CI           CI_SPE;                  /* 0x170 - ICM Interrupt group SPE for module Interrupt information */
    uint8                         reserved_174[28];        /* 0x174 - Internal  reserved */
    GTM_ICM_IRQG_ATOM_CI          CI_ATOM[2];              /* 0x190 - ICM Interrupt group ATOM [g] for Channel Interrupt information of ATOM[j] (m=4*[g]+(0..3)) */
    uint8                         reserved_198[8];         /* 0x198 - Internal  reserved */
    GTM_ICM_IRQG_TOM_CI           CI_TOM[2];               /* 0x1A0 - ICM Interrupt group TOM [g] for Channel Interrupt information of TOMm ([j]=2*[g]+(0..1)) */
} GTM_ICM_IRQG;

/* ICM object */
typedef volatile struct
{
    GTM_ICM_IRQG        IRQG;        /* 0x0 - GTM_ICM_IRQG */
} GTM_ICM;

/* MON_ACTIVITY object */
typedef volatile struct
{
    GTM_MON_ACTIVITY_0          R0;            /* 0x0 - MON activity register 0 */
    GTM_MON_ACTIVITY_1          R1;            /* 0x4 - MON activity register 1 */
    GTM_MON_ACTIVITY_MCS        MCS[5];        /* 0x8 - MON activity register for MCS [j] */
} GTM_MON_ACTIVITY;

/* MON object */
typedef volatile struct
{
    GTM_MON_STATUS          STATUS;          /* 0x0 - MON status register */
    GTM_MON_ACTIVITY        ACTIVITY;        /* 0x4 - GTM_MON_ACTIVITY */
} GTM_MON;

/* CMP_IRQ object */
typedef volatile struct
{
    GTM_CMP_IRQ_NOTIFY         NOTIFY;         /* 0x0 - CMP event notification register */
    GTM_CMP_IRQ_EN             EN;             /* 0x4 - CMP interrupt enable register */
    GTM_CMP_IRQ_FORCINT        FORCINT;        /* 0x8 - CMP interrupt force register */
    GTM_CMP_IRQ_MODE           MODE;           /* 0xC - CMP interrupt mode configuration register */
} GTM_CMP_IRQ;

/* CMP object */
typedef volatile struct
{
    GTM_CMP_EN             EN;             /* 0x0 - CMP comparator enable register */
    GTM_CMP_IRQ            IRQ;            /* 0x4 - GTM_CMP_IRQ */
    GTM_CMP_EIRQ_EN        EIRQ_EN;        /* 0x14 - CMP error interrupt enable register */
} GTM_CMP;

/* TIM_CH_IRQ object */
typedef volatile struct
{
    GTM_TIM_CH_IRQ_NOTIFY         NOTIFY;         /* 0x0 - TIM[i] channel [x] interrupt notification register */
    GTM_TIM_CH_IRQ_EN             EN;             /* 0x4 - TIM[i] channel [x] interrupt enable register */
    GTM_TIM_CH_IRQ_FORCINT        FORCINT;        /* 0x8 - TIM[i] channel [x] force interrupt register */
    GTM_TIM_CH_IRQ_MODE           MODE;           /* 0xC - TIM[i] channel [x] interrupt mode configuration register */
} GTM_TIM_CH_IRQ;

/* TIM_CH object */
/* #Violation: gtm_register_h_REF_3 */
typedef volatile struct
{
    GTM_TIM_CH_GPR0           GPR0;                   /* 0x0 - TIM[i] channel [x] general purpose 0 register */
    GTM_TIM_CH_GPR1           GPR1;                   /* 0x4 - TIM[i] channel [x] general purpose 1 register */
    GTM_TIM_CH_CNT            CNT;                    /* 0x8 - TIM[i] channel [x] SMU counter register */
    GTM_TIM_CH_ECNT           ECNT;                   /* 0xC - TIM[i] channel [x] SMU edge counter register */
    GTM_TIM_CH_CNTS           CNTS;                   /* 0x10 - TIM[i] channel [x] SMU shadow counter register */
    GTM_TIM_CH_TDUC           TDUC;                   /* 0x14 - TIM[i] channel [x] TDU counter register */
    GTM_TIM_CH_TDUV           TDUV;                   /* 0x18 - TIM[i] channel [x] TDU control register */
    GTM_TIM_CH_FLT_RE         FLT_RE;                 /* 0x1C - TIM[i] channel [x] filter parameter 0 register */
    GTM_TIM_CH_FLT_FE         FLT_FE;                 /* 0x20 - TIM[i] channel [x] filter parameter 1 register */
    GTM_TIM_CH_CTRL           CTRL;                   /* 0x24 - TIM[i] channel [x] control register */
    GTM_TIM_CH_ECTRL          ECTRL;                  /* 0x28 - TIM[i] channel [x] extended control register */
    GTM_TIM_CH_IRQ            IRQ;                    /* 0x2C - GTM_TIM_CH_IRQ */
    GTM_TIM_CH_EIRQ_EN        EIRQ_EN;                /* 0x3C - TIM[i] channel [x] error interrupt enable register */
    uint8                     reserved_40[64];        /* 0x40 - Internal  reserved */
} GTM_TIM_CH;

/* TIM object */
/* #Violation: gtm_register_h_REF_3 */
typedef volatile struct
{
    /* #Violation: gtm_register_h_REF_2 */
    GTM_TIM_CH             CH[8];          /* 0x0 - GTM_TIM_CH */
    GTM_TIM_INP_VAL        INP_VAL;        /* 0x400 - TIM[i] input value observation register */
    GTM_TIM_IN_SRC         IN_SRC;         /* 0x404 - TIM[i] AUX IN source selection register */
    GTM_TIM_RST            RST;            /* 0x408 - TIM[i] global software reset register */
} GTM_TIM_t;

/* TOM_CH_IRQ object */
typedef volatile struct
{
    GTM_TOM_CH_IRQ_NOTIFY         NOTIFY;         /* 0x0 - TOM[i] channel [x] interrupt notification register */
    GTM_TOM_CH_IRQ_EN             EN;             /* 0x4 - TOM[i] channel [x] interrupt enable register */
    GTM_TOM_CH_IRQ_FORCINT        FORCINT;        /* 0x8 - TOM[i] channel [x] force interrupt register */
    GTM_TOM_CH_IRQ_MODE           MODE;           /* 0xC - TOM[i] channel [x] interrupt mode register */
} GTM_TOM_CH_IRQ;

/* TOM_CH object */
/* #Violation: gtm_register_h_REF_3 */
typedef volatile struct
{
    GTM_TOM_CH_CTRL           CTRL;                   /* 0x0 - TOM[i] channel [x] control register */
    GTM_TOM_CH_SR0            SR0;                    /* 0x4 - TOM[i] channel [x] CCU0 compare shadow register */
    GTM_TOM_CH_SR1            SR1;                    /* 0x8 - TOM[i] channel [x] CCU1 compare shadow register */
    GTM_TOM_CH_CM0            CM0;                    /* 0xC - TOM[i] channel [x] CCU0 compare register */
    GTM_TOM_CH_CM1            CM1;                    /* 0x10 - TOM[i] channel [x] CCU1 compare register */
    GTM_TOM_CH_CN0            CN0;                    /* 0x14 - TOM[i] channel [x] CCU0 counter */
    GTM_TOM_CH_STAT           STAT;                   /* 0x18 - TOM[i] channel [x] status register */
    GTM_TOM_CH_IRQ            IRQ;                    /* 0x1C - GTM_TOM_CH_IRQ */
    GTM_TOM_CH_CTRL2          CTRL2;                  /* 0x2C - TOM[i] channel [x] control register */
    GTM_TOM_CH_CTRL_SR        CTRL_SR;                /* 0x30 - TOM[i] channel [x] control shadow register */
    uint8                     reserved_34[12];        /* 0x34 - Internal  reserved */
} GTM_TOM_CH;

/* TOM_TGC object */
typedef volatile struct
{
    GTM_TOM_TGC_GLB_CTRL          GLB_CTRL;               /* 0x0 - TOM[i] TGC [g] global control register */
    GTM_TOM_TGC_ACT_TB            ACT_TB;                 /* 0x4 - TOM[i] TGC [g] action time base register */
    GTM_TOM_TGC_FUPD_CTRL         FUPD_CTRL;              /* 0x8 - TOM[i] TGC [g] force update control register */
    GTM_TOM_TGC_INT_TRIG          INT_TRIG;               /* 0xC - TOM[i] TGC [g] internal trigger control register */
    uint8                         reserved_10[48];        /* 0x10 - Internal  reserved */
    GTM_TOM_TGC_ENDIS_CTRL        ENDIS_CTRL;             /* 0x40 - TOM[i] TGC [g] enable/disable control register */
    GTM_TOM_TGC_ENDIS_STAT        ENDIS_STAT;             /* 0x44 - TOM[i] TGC [g] enable/disable status register */
    GTM_TOM_TGC_OUTEN_CTRL        OUTEN_CTRL;             /* 0x48 - TOM[i] TGC [g] output enable control register */
    GTM_TOM_TGC_OUTEN_STAT        OUTEN_STAT;             /* 0x4C - TOM[i] TGC [g] output enable status register */
    uint8                         reserved_50[48];        /* 0x50 - Internal  reserved */
} GTM_TOM_TGC;

/* TOM object */
/* #Violation: gtm_register_h_REF_3 */
typedef volatile struct
{
    /* #Violation: gtm_register_h_REF_2 */
    GTM_TOM_CH         CH[16];                  /* 0x0 - GTM_TOM_CH */
    uint8              reserved_400[48];        /* 0x400 - Internal  reserved */
    /* #Violation: gtm_register_h_REF_2 */
    GTM_TOM_TGC        TGC[2];                  /* 0x430 - GTM_TOM_TGC */
} GTM_TOM_t;

/* ATOM_CH_IRQ object */
typedef volatile struct
{
    GTM_ATOM_CH_IRQ_NOTIFY         NOTIFY;         /* 0x0 - ATOM[i] channel [x] interrupt notification register */
    GTM_ATOM_CH_IRQ_EN             EN;             /* 0x4 - ATOM[i] channel [x] interrupt enable register */
    GTM_ATOM_CH_IRQ_FORCINT        FORCINT;        /* 0x8 - ATOM[i] channel [x] software interrupt generation */
    GTM_ATOM_CH_IRQ_MODE           MODE;           /* 0xC - ATOM[i] channel [x] interrupt mode configuration register */
} GTM_ATOM_CH_IRQ;

/* ATOM_CH object */
/* #Violation: gtm_register_h_REF_3 */
typedef volatile struct
{
    GTM_ATOM_CH_RDADDR         RDADDR;                 /* 0x0 - ATOM[i] channel[x] ARU read address register */
    union
    /* #Violation: gtm_register_h_REF_1 */
    {
        GTM_ATOM_CH_CTRL       CTRL;                   /* 0x4 ATOM[i] channel [x] control register */
        GTM_ATOM_CH_SOMB       SOMB;                   /* 0x4 ATOM[i] channel [x] control register in SOMB mode */
        GTM_ATOM_CH_SOMC       SOMC;                   /* 0x4 ATOM[i] channel [x] control register in SOMC mode */
        GTM_ATOM_CH_SOMI       SOMI;                   /* 0x4 ATOM[i] channel [x] control register in SOMI mode */
        GTM_ATOM_CH_SOMP       SOMP;                   /* 0x4 ATOM[i] channel [x] control register in SOMP mode */
        GTM_ATOM_CH_SOMS       SOMS;                   /* 0x4 ATOM[i] channel [x] control register in SOMS mode */
    } AC;
    GTM_ATOM_CH_SR0            SR0;                    /* 0x8 - ATOM[i] channel [x] CCU0 compare shadow register */
    GTM_ATOM_CH_SR1            SR1;                    /* 0xC - ATOM[i] channel [x] CCU1 compare shadow register */
    GTM_ATOM_CH_CM0            CM0;                    /* 0x10 - ATOM[i] channel [x] CCU0 compare register */
    GTM_ATOM_CH_CM1            CM1;                    /* 0x14 - ATOM[i] channel [x] CCU1 compare register */
    GTM_ATOM_CH_CN0            CN0;                    /* 0x18 - ATOM[i] channel [x] CCU0 counter register */
    GTM_ATOM_CH_STAT           STAT;                   /* 0x1C - ATOM[i] channel [x] status register */
    GTM_ATOM_CH_IRQ            IRQ;                    /* 0x20 - GTM_ATOM_CH_IRQ */
    GTM_ATOM_CH_CTRL2          CTRL2;                  /* 0x30 - ATOM[i] channel [x] control2 register */
    GTM_ATOM_CH_CTRL_SR        CTRL_SR;                /* 0x34 - ATOM[i] channel [x] control shadow register */
    uint8                      reserved_38[72];        /* 0x38 - Internal  reserved */
} GTM_ATOM_CH;

/* ATOM_AGC object */
typedef volatile struct
{
    GTM_ATOM_AGC_GLB_CTRL          GLB_CTRL;          /* 0x0 - ATOM[i] AGC global control register */
    GTM_ATOM_AGC_ENDIS_CTRL        ENDIS_CTRL;        /* 0x4 - ATOM[i] AGC enable/disable control register */
    GTM_ATOM_AGC_ENDIS_STAT        ENDIS_STAT;        /* 0x8 - ATOM[i] AGC enable/disable status register */
    GTM_ATOM_AGC_ACT_TB            ACT_TB;            /* 0xC - ATOM[i] AGC action time base register */
    GTM_ATOM_AGC_OUTEN_CTRL        OUTEN_CTRL;        /* 0x10 - ATOM[i] AGC output enable control register */
    GTM_ATOM_AGC_OUTEN_STAT        OUTEN_STAT;        /* 0x14 - ATOM[i] AGC output enable status register */
    GTM_ATOM_AGC_FUPD_CTRL         FUPD_CTRL;         /* 0x18 - ATOM[i] AGC force update control register */
    GTM_ATOM_AGC_INT_TRIG          INT_TRIG;          /* 0x1C - ATOM[i] AGC internal trigger control register */
} GTM_ATOM_AGC;

/* ATOM object */
/* #Violation: gtm_register_h_REF_3 */
typedef volatile struct
{
    /* #Violation: gtm_register_h_REF_2 */
    GTM_ATOM_CH         CH[8];                   /* 0x0 - GTM_ATOM_CH */
    uint8               reserved_400[64];        /* 0x400 - Internal  reserved */
    GTM_ATOM_AGC        AGC;                     /* 0x440 - GTM_ATOM_AGC */
} GTM_ATOM_t;

/* MCS_CH_IRQ object */
typedef volatile struct
{
    GTM_MCS_CH_IRQ_NOTIFY         NOTIFY;         /* 0x0 - MCS[i] channel x interrupt notification register */
    GTM_MCS_CH_IRQ_EN             EN;             /* 0x4 - MCS[i] channel x interrupt enable register  */
    GTM_MCS_CH_IRQ_FORCINT        FORCINT;        /* 0x8 - MCS[i] channel x force interrupt register */
    GTM_MCS_CH_IRQ_MODE           MODE;           /* 0xC - MCS[i] channel x IRQ mode configuration register  */
} GTM_MCS_CH_IRQ;

/* MCS_CH object */
typedef volatile struct
{
    GTM_MCS_CH_R              R[8];                    /* 0x0 - MCS[i] channel x general purpose register [y] */
    GTM_MCS_CH_CTRL           CTRL;                    /* 0x20 - MCS[i] channel x control register */
    GTM_MCS_CH_ACB            ACB;                     /* 0x24 - MCS[i] channel x ARU control Bit register  */
    uint8                     reserved_28[20];         /* 0x28 - Internal  reserved */
    GTM_MCS_CH_MHB            MHB;                     /* 0x3C - MCS[i] channel x memory high byte register  */
    uint8                     reserved_40[160];        /* 0x40 - Internal  reserved */
    GTM_MCS_CH_PC             PC;                      /* 0xE0 - MCS[i] channel x program counter register  */
    GTM_MCS_CH_IRQ            IRQ;                     /* 0xE4 - GTM_MCS_CH_IRQ */
    GTM_MCS_CH_EIRQ_EN        EIRQ_EN;                 /* 0xF4 - MCS[i] channel x error interrupt enable register */
    uint8                     reserved_F8[8];          /* 0xF8 - Internal  reserved */
} GTM_MCS_CH;

/* MCS_SINT_IRQ object */
typedef volatile struct
{
    GTM_MCS_SINT_IRQ_NOTIFY         NOTIFY;         /* 0x0 - MCS[i] shared interrupt notification register */
    GTM_MCS_SINT_IRQ_EN             EN;             /* 0x4 - MCS[i] shared interrupt enable register  */
    GTM_MCS_SINT_IRQ_FORCINT        FORCINT;        /* 0x8 - MCS[i] force shared interrupt register */
    GTM_MCS_SINT_IRQ_MODE           MODE;           /* 0xC - MCS[i] shared interrupt mode configuration register  */
} GTM_MCS_SINT_IRQ;

/* MCS_HBP object */
typedef volatile struct
{
    GTM_MCS_HBP_CTRL               CTRL;                  /* 0x0 - MCS[i] hardware break point h control register */
    GTM_MCS_HBP_PATTERN            PATTERN;               /* 0x4 - MCS[i] hardware break point pattern register */
    GTM_MCS_HBP_STATUS             STATUS;                /* 0x8 - MCS[i] hardware break point status register */
    GTM_MCS_HBP_IRQ_NOTIFY         IRQ_NOTIFY;            /* 0xC - MCS[i] hardware break point interrupt notification register */
    GTM_MCS_HBP_IRQ_EN             IRQ_EN;                /* 0x10 - MCS[i] hardware break point interrupt enable register  */
    GTM_MCS_HBP_IRQ_FORCINT        IRQ_FORCINT;           /* 0x14 - MCS[i] force hardware break point interrupt register */
    GTM_MCS_HBP_IRQ_MODE           IRQ_MODE;              /* 0x18 - MCS[i] break point h interrupt mode configuration register  */
    uint8                          reserved_1C[4];        /* 0x1C - Internal  reserved */
} GTM_MCS_HBP;

/* MCS object */
typedef volatile struct
{
    GTM_MCS_CH               CH[8];                     /* 0x0 - GTM_MCS_CH */
    uint8                    reserved_800[1576];        /* 0x800 - Internal  reserved */
    GTM_MCS_CTRG             CTRG;                      /* 0xE28 - MCS[i] clear trigger control register */
    GTM_MCS_STRG             STRG;                      /* 0xE2C - MCS[i] set trigger control register */
    uint8                    reserved_E30[208];         /* 0xE30 - Internal  reserved */
    GTM_MCS_CTRL_STAT        CTRL_STAT;                 /* 0xF00 - MCS[i] control and status register */
    GTM_MCS_RESET            RESET;                     /* 0xF04 - MCS[i] reset register */
    GTM_MCS_CAT              CAT;                       /* 0xF08 - MCS[i] cancel ARU transfer instruction */
    GTM_MCS_CWT              CWT;                       /* 0xF0C - MCS[i] cancel waiting instruction */
    GTM_MCS_ERR              ERR;                       /* 0xF10 - MCS[i] error register */
    uint8                    reserved_F14[8];           /* 0xF14 - Internal  reserved */
    GTM_MCS_REG_PROT         REG_PROT;                  /* 0xF1C - MCS[i] write protection register */
    GTM_MCS_SINT_IRQ         IRQ;                       /* 0xF20 - GTM_MCS_SINT_IRQ */
    uint8                    reserved_F30[16];          /* 0xF30 - Internal  reserved */
    GTM_MCS_HBP              HBP[2];                    /* 0xF40 - GTM_MCS_HBP */
} GTM_MCS;

/* TIO_G_CH object */
typedef volatile struct
{
    GTM_TIO_G_CH_CTRL               CTRL;                  /* 0x0 - TIO[i] group [g] channel [c] control register */
    GTM_TIO_G_CH_IRQ_NOTIFY         IRQ_NOTIFY;            /* 0x4 - TIO[i] channel [c] interrupt notification register */
    GTM_TIO_G_CH_IRQ_EN             IRQ_EN;                /* 0x8 - TIO[i] channel [c] interrupt enable register */
    GTM_TIO_G_CH_IRQ_FORCINT        IRQ_FORCINT;           /* 0xC - TIO[i] channel [c] force interrupt register */
    GTM_TIO_G_CH_IRQ_MODE           IRQ_MODE;              /* 0x10 - TIO[i] channel [c] IRQ mode configuration register */
    GTM_TIO_G_CH_CTRL2              CTRL2;                 /* 0x14 - TIO[i] group [g] channel [c] control register */
    uint8                           reserved_18[8];        /* 0x18 - Internal  reserved */
    GTM_TIO_G_CH_SINST              SINST;                 /* 0x20 - TIO[i] channel [c] resource S instruction register (buffer operation)TIO[i]_G[g]_CH[c]_CTRL.PL_S_MODE=0b0- */
    GTM_TIO_G_CH_SCMD               SCMD;                  /* 0x24 - TIO[i] channel [c] resource S command register (buffer operation)TIO[i]_G[g]_CH[c]_CTRL.PL_S_MODE=0b0- */
    GTM_TIO_G_CH_SOP                SOP;                   /* 0x28 - TIO[i] channel [c] resource S operand registerTIO[i]_G[g]_CH[c]_CTRL.PL_S_MODE=0b0- or (TIO[i]_G[g]_OP_USAGE.MODE[c]=0b10- or TIO[i]_G[g]_OP_USAGE.MODE[c]=0b1-0 ) */
    uint8                           reserved_2C[4];        /* 0x2C - Internal  reserved */
    GTM_TIO_G_CH_OINST              OINST;                 /* 0x30 - TIO[i] channel [c] resource O instruction register (buffer operation)TIO[i]_G[g]_CH[c]_CTRL.PL_O_MODE =0b00- */
    GTM_TIO_G_CH_OCMD               OCMD;                  /* 0x34 - TIO[i] channel [c] resource O command register (buffer operation)TIO[i]_G[g]_CH[c]_CTRL.PL_O_MODE=0b00- */
    GTM_TIO_G_CH_OOP                OOP;                   /* 0x38 - TIO[i] channel [c] resource O operand register!(TIO[i]_G[g]_CH[c]_CTRL.PL_O_MODE=0b1--) or (TIO[i]_G[g]_OP_USAGE.MODE[c]=0b11-) */
    GTM_TIO_G_CH_SHIFTCNT           SHIFTCNT;              /* 0x3C - TIO[i] channel [c] resource shift count register */
} GTM_TIO_G_CH;

/* TIO_G object */
typedef volatile struct
{
    GTM_TIO_G_CH                CH[8];                   /* 0x0 - GTM_TIO_G_CH */
    GTM_TIO_G_ISEL_CTRL1        ISEL0_CTRL1;             /* 0x200 - TIO[i] input selection register 1 */
    GTM_TIO_G_ISEL_CTRL2        ISEL0_CTRL2;             /* 0x204 - TIO[i] input selection register 2 */
    uint8                       reserved_208[24];        /* 0x208 - Internal  reserved */
    GTM_TIO_G_ISEL_CTRL1        ISEL1_CTRL1;             /* 0x220 - TIO[i] input selection register 1 */
    GTM_TIO_G_ISEL_CTRL2        ISEL1_CTRL2;             /* 0x224 - TIO[i] input selection register 2 */
    uint8                       reserved_228[24];        /* 0x228 - Internal  reserved */
    GTM_TIO_G_OP_USAGE          OP_USAGE;                /* 0x240 - TIO[i] operand usage selection register */
} GTM_TIO_G;

/* TIO object */
typedef volatile struct
{
    GTM_TIO_G                          G0[1];                      /* 0x0 - GTM_TIO_G */
    uint8                              reserved_244[2492];         /* 0x244 - Internal  reserved */
    GTM_TIO_S                          S;                          /* 0xC00 - TIO[i] signal sampling register */
    GTM_TIO_O                          O;                          /* 0xC04 - TIO[i] output register */
    GTM_TIO_ENDIS                      ENDIS;                      /* 0xC08 - TIO[i] enable/disable register */
    GTM_TIO_INVERT                     INVERT;                     /* 0xC0C - TIO[i] signal invert register */
    GTM_TIO_INPUT_MODE                 INPUT_MODE;                 /* 0xC10 - TIO[i] input mode register */
    GTM_TIO_CYCLIC_MODE                CYCLIC_MODE;                /* 0xC14 - TIO[i] cyclic mode register */
    GTM_TIO_TRIG_OUT_GATE_EN           TRIG_OUT_GATE_EN;           /* 0xC18 - TIO[i] enable Trigger Output - output gating register */
    GTM_TIO_PLTRIG_OUT_GATE_EN         PLTRIG_OUT_GATE_EN;         /* 0xC1C - TIO[i] enable PL_TRIG_OUT output gating register */
    uint8                              reserved_C20[32];           /* 0xC20 - Internal  reserved */
    GTM_TIO_CS                         CS;                         /* 0xC40 - TIO[i] clear signal sampling register */
    GTM_TIO_CO                         CO;                         /* 0xC44 - TIO[i] clear output register */
    GTM_TIO_CENDIS                     CENDIS;                     /* 0xC48 - TIO[i] disable register */
    GTM_TIO_CINVERT                    CINVERT;                    /* 0xC4C - TIO[i] clear signal invert register */
    GTM_TIO_CINPUT_MODE                CINPUT_MODE;                /* 0xC50 - TIO[i] disable input mode register */
    GTM_TIO_CCYCLIC_MODE               CCYCLIC_MODE;               /* 0xC54 - TIO[i] disable cyclic mode register */
    GTM_TIO_CTRIG_OUT_GATE_EN          CTRIG_OUT_GATE_EN;          /* 0xC58 - TIO[i] clear Trigger Output - output gating register */
    GTM_TIO_CPLTRIG_OUT_GATE_EN        CPLTRIG_OUT_GATE_EN;        /* 0xC5C - TIO[i] clear PL_TRIG_OUT output gating register */
    uint8                              reserved_C60[32];           /* 0xC60 - Internal  reserved */
    GTM_TIO_SS                         SS;                         /* 0xC80 - TIO[i] set signal sampling register */
    GTM_TIO_SO                         SO;                         /* 0xC84 - TIO[i] set output register */
    GTM_TIO_SENDIS                     SENDIS;                     /* 0xC88 - TIO[i] enable register */
    GTM_TIO_SINVERT                    SINVERT;                    /* 0xC8C - TIO[i] set signal invert register */
    GTM_TIO_SINPUT_MODE                SINPUT_MODE;                /* 0xC90 - TIO[i] enable input mode register */
    GTM_TIO_SCYCLIC_MODE               SCYCLIC_MODE;               /* 0xC94 - TIO[i] enable cyclic mode register */
    GTM_TIO_STRIG_OUT_GATE_EN          STRIG_OUT_GATE_EN;          /* 0xC98 - TIO[i] set Trigger Output - output gating register */
    GTM_TIO_SPLTRIG_OUT_GATE_EN        SPLTRIG_OUT_GATE_EN;        /* 0xC9C - TIO[i] set PL_TRIG_OUT output gating register */
    uint8                              reserved_CA0[32];           /* 0xCA0 - Internal  reserved */
    GTM_TIO_IS                         IS;                         /* 0xCC0 - TIO[i] invert signal sampling register */
    GTM_TIO_IO                         IO;                         /* 0xCC4 - TIO[i] invert output register */
    GTM_TIO_IENDIS                     IENDIS;                     /* 0xCC8 - TIO[i] toggle enable/disable register */
    GTM_TIO_IINVERT                    IINVERT;                    /* 0xCCC - TIO[i] toggle signal invert register */
    GTM_TIO_IINPUT_MODE                IINPUT_MODE;                /* 0xCD0 - TIO[i] enable input mode register */
    GTM_TIO_ICYCLIC_MODE               ICYCLIC_MODE;               /* 0xCD4 - TIO[i] enable cyclic mode register */
    uint8                              reserved_CD8[40];           /* 0xCD8 - Internal  reserved */
    GTM_TIO_FUPD                       FUPD;                       /* 0xD00 - TIO[i] force update register */
    GTM_TIO_HW_CONF                    HW_CONF;                    /* 0xD04 - TIO[i] configuration register */
    GTM_TIO_RSEL_CTRL1                 RSEL_CTRL1;                 /* 0xD08 - TIO[i] resource selection control register 1 */
    GTM_TIO_RSEL_CTRL2                 RSEL_CTRL2;                 /* 0xD0C - TIO[i] resource selection control register 2 */
    GTM_TIO_PL_SWRST                   PL_SWRST;                   /* 0xD10 - TIO[i] software reset for TIO Plus functionality */
} GTM_TIO;

/* CCM_ARP object */
typedef volatile struct
{
    GTM_CCM_ARP_CTRL        CTRL;        /* 0x0 - CCM[i] Address Range Protector [a] Control Register */
    GTM_CCM_ARP_PROT        PROT;        /* 0x4 - CCM[i] Address Range Protector [a] Protection Register */
} GTM_CCM_ARP;

/* CCM object */
typedef volatile struct
{
    GTM_CCM_ARP                   ARP[10];                 /* 0x0 - GTM_CCM_ARP */
    uint8                         reserved_50[380];        /* 0x50 - Internal  reserved */
    GTM_CCM_TIO_G_OUT             TIO_G0_OUT;              /* 0x1CC - CCM[i] TIO Group 0,1 Output Register */
    uint8                         reserved_1D0[4];         /* 0x1D0 - Internal  reserved */
    GTM_CCM_HW_CONF2              HW_CONF2;                /* 0x1D4 - CCM[i] 2. Hardware Configuration Register */
    GTM_CCM_AEIM_STA              AEIM_STA;                /* 0x1D8 - CCM[i] MCS Bus Master Status Register */
    GTM_CCM_HW_CONF               HW_CONF;                 /* 0x1DC - CCM[i] Hardware Configuration Register */
    GTM_CCM_TIM_AUX_IN_SRC        TIM_AUX_IN_SRC;          /* 0x1E0 - CCM[i] TIM AUX Input Source Register */
    GTM_CCM_EXT_CAP_EN            EXT_CAP_EN;              /* 0x1E4 - CCM[i] External Capture Enable Register */
    GTM_CCM_TOM_OUT               TOM_OUT;                 /* 0x1E8 - CCM[i] TOM Output Register */
    GTM_CCM_ATOM_OUT              ATOM_OUT;                /* 0x1EC - CCM[i] ATOM Output Register */
    GTM_CCM_CMU_CLK_CFG           CMU_CLK_CFG;             /* 0x1F0 - CCM[i] CMU Clock Configuration Register */
    GTM_CCM_CMU_FXCLK_CFG         CMU_FXCLK_CFG;           /* 0x1F4 - CCM[i] CMU Fixed Clock Configuration Register */
    GTM_CCM_CFG                   CFG;                     /* 0x1F8 - CCM[i] Configuration Register */
    GTM_CCM_PROT                  PROT;                    /* 0x1FC - CCM[i] Protection Register */
} GTM_CCM;

/* CDTM_DTM_CH object */
typedef volatile struct
{
    GTM_CDTM_DTM_CH_DTV        DTV;        /* 0x0 - CDTM[i]_DTM[d] channel [x] dead time reload values */
} GTM_CDTM_DTM_CH;

/* CDTM_DTM_SR_CH object */
typedef volatile struct
{
    GTM_CDTM_DTM_CH_DTV_SR        SR;        /* 0x0 - CDTM[i]_DTM[d] channel [x] dead time shadow values */
} GTM_CDTM_DTM_SR_CH;

/* CDTM_DTM object */
typedef volatile struct
{
    GTM_CDTM_DTM_CTRL               CTRL;               /* 0x0 - CDTM[i]_DTM[d] global configuration and control register */
    GTM_CDTM_DTM_CH_CTRL1           CH_CTRL1;           /* 0x4 - CDTM[i]_DTM[d] channel control register 1 */
    GTM_CDTM_DTM_CH_CTRL2           CH_CTRL2;           /* 0x8 - CDTM[i]_DTM[d] channel control register 2 */
    GTM_CDTM_DTM_CH_CTRL2_SR        CH_CTRL2_SR;        /* 0xC - CDTM[i] DTM[j] channel control register 2 shadow */
    GTM_CDTM_DTM_PS_CTRL            PS_CTRL;            /* 0x10 - CDTM[i]_DTM[d] phase shift unit configuration and control register */
    GTM_CDTM_DTM_CH                 CH[4];              /* 0x14 - GTM_CDTM_DTM_CH */
    GTM_CDTM_DTM_CH_SR              CH_SR;              /* 0x24 - CDTM[i]_DTM[d] channel shadow register */
    GTM_CDTM_DTM_CH_CTRL3           CH_CTRL3;           /* 0x28 - CDTM[i]_DTM[d] channel control register 3 */
    GTM_CDTM_DTM_CTRL2              CTRL2;              /* 0x2C - CDTM[i]_DTM[d] global configuration and control register 2 */
    GTM_CDTM_DTM_SR_CH              SR[4];              /* 0x30 - GTM_CDTM_DTM_SR_CH */
} GTM_CDTM_DTM;

/* CDTM object */
typedef volatile struct
{
    GTM_CDTM_DTM        DTM[12];        /* 0x0 - GTM_CDTM_DTM */
} GTM_CDTM;

/* F2A_CH_ARU object */
typedef volatile struct
{
    GTM_F2A_CH_ARU_RD_FIFO        RD_FIFO;        /* 0x0 - F2A[i] stream [x] ARU read register */
} GTM_F2A_CH_ARU;

/* F2A_CH_STR object */
typedef volatile struct
{
    GTM_F2A_CH_STR_CFG        CFG;        /* 0x0 - F2A[i] stream [x] configuration register */
} GTM_F2A_CH_STR;

/* F2A object */
typedef volatile struct
{
    GTM_F2A_CH_ARU        FIFO[8];        /* 0x0 - GTM_F2A_CH_ARU */
    GTM_F2A_CH_STR        CFG[8];         /* 0x20 - GTM_F2A_CH_STR */
    GTM_F2A_ENABLE        ENABLE;         /* 0x40 - F2A[i] stream activation register */
    GTM_F2A_CTRL          CTRL;           /* 0x44 - F2A[i] stream control register */
} GTM_F2A;

/* AFD_CH object */
typedef volatile struct
{
    GTM_AFD_CH_BUF_ACC        BUF_ACC;               /* 0x0 - AFD [i] FIFO [x] buffer access register */
    uint8                     reserved_4[12];        /* 0x4 - Internal  reserved */
} GTM_AFD_CH;

/* AFD object */
typedef volatile struct
{
    GTM_AFD_CH        CH[8];        /* 0x0 - GTM_AFD_CH */
} GTM_AFD;

/* FIFO_CH_IRQ object */
typedef volatile struct
{
    GTM_FIFO_CH_IRQ_NOTIFY         NOTIFY;         /* 0x0 - FIFO[i] channel [x] interrupt notification register */
    GTM_FIFO_CH_IRQ_EN             EN;             /* 0x4 - FIFO[i] channel [x] interrupt enable register */
    GTM_FIFO_CH_IRQ_FORCINT        FORCINT;        /* 0x8 - FIFO[i] channel [x] force interrupt register */
    GTM_FIFO_CH_IRQ_MODE           MODE;           /* 0xC - FIFO[i] channel [x] interrupt mode control register */
} GTM_FIFO_CH_IRQ;

/* FIFO_CH object */
typedef volatile struct
{
    GTM_FIFO_CH_CTRL              CTRL;                  /* 0x0 - FIFO[i] channel [x] control register */
    GTM_FIFO_CH_END_ADDR          END_ADDR;              /* 0x4 - FIFO[i] channel [x] end address register */
    GTM_FIFO_CH_START_ADDR        START_ADDR;            /* 0x8 - FIFO[i] channel [x] start address register */
    GTM_FIFO_CH_UPPER_WM          UPPER_WM;              /* 0xC - FIFO[i] channel [x] upper watermark register */
    GTM_FIFO_CH_LOWER_WM          LOWER_WM;              /* 0x10 - FIFO[i] channel [x] lower watermark register */
    GTM_FIFO_CH_STATUS            STATUS;                /* 0x14 - FIFO[i] channel [x] status register */
    GTM_FIFO_CH_FILL_LEVEL        FILL_LEVEL;            /* 0x18 - FIFO[i] channel [x] fill level register */
    GTM_FIFO_CH_WR_PTR            WR_PTR;                /* 0x1C - FIFO[i] channel [x] write pointer register */
    GTM_FIFO_CH_RD_PTR            RD_PTR;                /* 0x20 - FIFO[i] channel [x] read pointer register */
    GTM_FIFO_CH_IRQ               IRQ;                   /* 0x24 - GTM_FIFO_CH_IRQ */
    GTM_FIFO_CH_EIRQ_EN           EIRQ_EN;               /* 0x34 - FIFO[i] channel [x] error interrupt enable register */
    uint8                         reserved_38[8];        /* 0x38 - Internal  reserved */
} GTM_FIFO_CH;

/* FIFO object */
typedef volatile struct
{
    GTM_FIFO_CH        CH[8];        /* 0x0 - GTM_FIFO_CH */
} GTM_FIFO;

/* SPE_IRQ object */
typedef volatile struct
{
    GTM_SPE_IRQ_NOTIFY         NOTIFY;         /* 0x0 - SPE[i] Interrupt Notification Register */
    GTM_SPE_IRQ_EN             EN;             /* 0x4 - SPE[i] Interrupt Enable Register */
    GTM_SPE_IRQ_FORCINT        FORCINT;        /* 0x8 - SPE[i] Interrupt Generation By Software */
    GTM_SPE_IRQ_MODE           MODE;           /* 0xC - SPE[i] Interrupt Mode Configuration Register */
} GTM_SPE_IRQ;

/* SPE object */
typedef volatile struct
{
    GTM_SPE_CTRL_STAT         CTRL_STAT;         /* 0x0 - SPE[i] Control Status Register */
    GTM_SPE_PAT               PAT;               /* 0x4 - SPE[i] Input Pattern Definition Register */
    GTM_SPE_OUT_PAT           OUT_PAT[8];        /* 0x8 - SPE[i] Output Definition Register */
    GTM_SPE_OUT_CTRL          OUT_CTRL;          /* 0x28 - SPE[i] Output Control Register */
    GTM_SPE_IRQ               IRQ;               /* 0x2C - GTM_SPE_IRQ */
    GTM_SPE_EIRQ_EN           EIRQ_EN;           /* 0x3C - SPE[i] Error Interrupt Enable Register */
    GTM_SPE_REV_CNT           REV_CNT;           /* 0x40 - SPE[i] Input Revolution Counter */
    GTM_SPE_REV_CMP           REV_CMP;           /* 0x44 - SPE[i] Revolution Counter Compare Value */
    GTM_SPE_CTRL_STAT2        CTRL_STAT2;        /* 0x48 - SPE[i] Control Status Register 2 */
    GTM_SPE_CMD               CMD;               /* 0x4C - SPE[i] Command Register */
} GTM_SPE;

/* AXIM_SLOT object */
typedef volatile struct
{
    GTM_AXIM_SLOT_ADDR_LOW        ADDR_LOW;              /* 0x0 - AXIM[i] slot[s] address bits 31:0 of AXI transaction. */
    uint8                         reserved_4[4];         /* 0x4 - Internal  reserved */
    GTM_AXIM_SLOT_DATA_LOW        DATA_LOW;              /* 0x8 - AXIM[i] slot[s] data bits 31:0 of AXI transaction. */
    uint8                         reserved_C[4];         /* 0xC - Internal  reserved */
    GTM_AXIM_SLOT_CFG1            CFG1;                  /* 0x10 - AXIM[i] slot [s] configuration 1 */
    GTM_AXIM_SLOT_CFG2            CFG2;                  /* 0x14 - AXIM[i] slot[s] configuration 2 */
    GTM_AXIM_SLOT_STATUS          STATUS;                /* 0x18 - AXIM[i] slot[s] status */
    uint8                         reserved_1C[4];        /* 0x1C - Internal  reserved */
} GTM_AXIM_SLOT;

/* AXIM object */
typedef volatile struct
{
    GTM_AXIM_FREE           FREE;                  /* 0x0 - AXIM[i] slot allocation status. */
    GTM_AXIM_REQUEST        REQUEST;               /* 0x4 - AXIM[i] slot request (allocation). */
    GTM_AXIM_RELEASE        RELEASE;               /* 0x8 - AXIM[i] slot release (de-allocation). */
    uint8                   reserved_C[20];        /* 0xC - Internal  reserved */
    GTM_AXIM_SLOT           SLOT[4];               /* 0x20 - GTM_AXIM_SLOT */
} GTM_AXIM;

/* DPLL_IRQ object */
typedef volatile struct
{
    GTM_DPLL_IRQ_NOTIFY         NOTIFY;         /* 0x0 - Interrupt Register */
    GTM_DPLL_IRQ_EN             EN;             /* 0x4 - Interrupt Enable Register */
    GTM_DPLL_IRQ_FORCINT        FORCINT;        /* 0x8 - Force Interrupt Register */
    GTM_DPLL_IRQ_MODE           MODE;           /* 0xC - Interrupt Request Mode */
} GTM_DPLL_IRQ;

/* DPLL object */
typedef volatile struct
{
    GTM_DPLL_CTRL_0                       CTRL_0;                       /* 0x0 - Control Register 0 */
    GTM_DPLL_CTRL_1                       CTRL_1;                       /* 0x4 - Control Register 1 */
    GTM_DPLL_CTRL_2                       CTRL_2;                       /* 0x8 - Action Enable Register  */
    GTM_DPLL_CTRL_3                       CTRL_3;                       /* 0xC - Action Enable Register */
    GTM_DPLL_CTRL_4                       CTRL_4;                       /* 0x10 - Action Enable Register */
    GTM_DPLL_CTRL_5                       CTRL_5;                       /* 0x14 - Action Enable Register */
    GTM_DPLL_ACT_STA                      ACT_STA;                      /* 0x18 - Action Status Register including Shadow Register */
    GTM_DPLL_OSW                          OSW;                          /* 0x1C - Offset and Switch old/new Address Register */
    GTM_DPLL_AOSV_2                       AOSV_2;                       /* 0x20 - Address Offset Register of RAM 2 Regions */
    GTM_DPLL_APT                          APT;                          /* 0x24 - Actual RAM Pointer Address for TRIGGER */
    GTM_DPLL_APS                          APS;                          /* 0x28 - Actual RAM Pointer Address for STATE */
    GTM_DPLL_APT_2C                       APT_2C;                       /* 0x2C - Actual RAM Pointer Address for Region 2c */
    GTM_DPLL_APS_1C3                      APS_1C3;                      /* 0x30 - Actual RAM Pointer Address for RAM region 1c3 */
    GTM_DPLL_NUTC                         NUTC;                         /* 0x34 - Number of Recent TRIGGER Events used for Calculations */
    GTM_DPLL_NUSC                         NUSC;                         /* 0x38 - Number of Recent STATE Events used for Calculations */
    GTM_DPLL_NTI_CNT                      NTI_CNT;                      /* 0x3C - Number of Active TRIGGER Events to Interrupt */
    GTM_DPLL_IRQ                          IRQ;                          /* 0x40 - GTM_DPLL_IRQ */
    GTM_DPLL_EIRQ_EN                      EIRQ_EN;                      /* 0x50 - Error Interrupt Enable Register */
    uint8                                 reserved_54[92];              /* 0x54 - Internal  reserved */
    GTM_DPLL_INC_CNT1                     INC_CNT1;                     /* 0xB0 - Counter Value of Sent SUB_INC1 Pulses */
    GTM_DPLL_INC_CNT2                     INC_CNT2;                     /* 0xB4 - Counter Value of sent SUB_INC2 values (for DPLL_CTRL_1.SMC=1 and DPLL_CTRL_0.RMO=1) */
    GTM_DPLL_APT_SYNC                     APT_SYNC;                     /* 0xB8 - TRIGGER Time Stamp Field Offset at Synchronization Time */
    GTM_DPLL_APS_SYNC                     APS_SYNC;                     /* 0xBC - STATE Time Stamp Field Offset at Synchronization Time */
    GTM_DPLL_TBU_TS0_T                    TBU_TS0_T;                    /* 0xC0 - Time Stamp Value for the last active TRIGGER */
    GTM_DPLL_TBU_TS0_S                    TBU_TS0_S;                    /* 0xC4 - Time Stamp Value for the last active STATE */
    GTM_DPLL_ADD_IN_LD1                   ADD_IN_LD1;                   /* 0xC8 - ADD_IN Value in Direct Load Mode for TRIGGER */
    GTM_DPLL_ADD_IN_LD2                   ADD_IN_LD2;                   /* 0xCC - ADD_IN Value in Direct Load Mode for STATE */
    uint8                                 reserved_D0[44];              /* 0xD0 - Internal  reserved */
    GTM_DPLL_STATUS                       STATUS;                       /* 0xFC - Status Register */
    GTM_DPLL_ID_PMTR                      ID_PMTR[32];                  /* 0x100 - ID Information for Input Signal PMTR[n] (Position minus Time Request) */
    uint8                                 reserved_180[96];             /* 0x180 - Internal  reserved */
    GTM_DPLL_CTRL_0_SHADOW_TRIGGER        CTRL_0_SHADOW_TRIGGER;        /* 0x1E0 - Shadow Register of DPLL_CTRL_0 controlled by an active TRIGGER Slope */
    GTM_DPLL_CTRL_0_SHADOW_STATE          CTRL_0_SHADOW_STATE;          /* 0x1E4 - Shadow Register of DPLL_CTRL_0 controlled by an active STATE Slope */
    GTM_DPLL_CTRL_1_SHADOW_TRIGGER        CTRL_1_SHADOW_TRIGGER;        /* 0x1E8 - Shadow Register of DPLL_CTRL_1 controlled by an active TRIGGER Slope */
    GTM_DPLL_CTRL_1_SHADOW_STATE          CTRL_1_SHADOW_STATE;          /* 0x1EC - DPLL Shadow Register of DPLL_CTRL_1 controlled by an active STATE Slope */
    uint8                                 reserved_1F0[12];             /* 0x1F0 - Internal  reserved */
    GTM_DPLL_RAM_INI                      RAM_INI;                      /* 0x1FC - Register to control the RAM Initialization */
    GTM_DPLL_PSA                          PSA[32];                      /* 0x200 - Position Request for Action [n] */
    GTM_DPLL_DLA                          DLA[32];                      /* 0x280 - Time to React for Action [n] */
    GTM_DPLL_NA                           NA[32];                       /* 0x300 - Calculated Relative Time to Action [n] */
    GTM_DPLL_DTA                          DTA[32];                      /* 0x380 - Calculated Relative Time to Action [n] */
    GTM_DPLL_TS_T                         TS_T;                         /* 0x400 - Actual TRIGGER Time Stamp Value */
    GTM_DPLL_TS_T_OLD                     TS_T_OLD;                     /* 0x404 - Previous TRIGGER Time Stamp Value */
    GTM_DPLL_FTV_T                        FTV_T;                        /* 0x408 - Actual TRIGGER Filter value */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_0;                 /* 0x40C - DPLL RAM1B reserved  data */
    GTM_DPLL_TS_S                         TS_S;                         /* 0x410 - Actual STATE Time Stamp Register */
    GTM_DPLL_TS_S_OLD                     TS_S_OLD;                     /* 0x414 - Previous STATE Time Stamp Register */
    GTM_DPLL_FTV_S                        FTV_S;                        /* 0x418 - Actual STATE Filter Value */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_1;                 /* 0x41C - DPLL RAM1B reserved  data */
    GTM_DPLL_THMI                         THMI;                         /* 0x420 - TRIGGER Hold Time Min. Value */
    GTM_DPLL_THMA                         THMA;                         /* 0x424 - TRIGGER Hold Time Max. Value */
    GTM_DPLL_THVAL                        THVAL;                        /* 0x428 - Measured TRIGGER Hold Time Value */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_2;                 /* 0x42C - DPLL RAM1B reserved  data */
    GTM_DPLL_TOV                          TOV;                          /* 0x430 - Time Out Value of Active TRIGGER Slope (for missing TRIGGER generation) */
    GTM_DPLL_TOV_S                        TOV_S;                        /* 0x434 - Time Out Value of active STATE Slope (for missing STATE generation) */
    GTM_DPLL_ADD_IN_CAL1                  ADD_IN_CAL1;                  /* 0x438 - Calculated ADD_IN Value for SUB_INC1 Generation */
    GTM_DPLL_ADD_IN_CAL2                  ADD_IN_CAL2;                  /* 0x43C - Calculated ADD_IN Value for SUB_INC2 Generation */
    GTM_DPLL_MPVAL1                       MPVAL1;                       /* 0x440 - Missing Pulses to be Added or Subtracted Directly  */
    GTM_DPLL_MPVAL2                       MPVAL2;                       /* 0x444 - Missing Pulses to be Added or Subtracted Directly */
    GTM_DPLL_NMB_T_TAR                    NMB_T_TAR;                    /* 0x448 - Target Number of Pulses to be sent in Normal Mode */
    GTM_DPLL_NMB_T_TAR_OLD                NMB_T_TAR_OLD;                /* 0x44C - Last but one Target Number of Pulses to be sent in Normal Mode  */
    GTM_DPLL_NMB_S_TAR                    NMB_S_TAR;                    /* 0x450 - Target Number of Pulses to be sent in Emergency Mode */
    GTM_DPLL_NMB_S_TAR_OLD                NMB_S_TAR_OLD;                /* 0x454 - Last but one Target Number of Pulses to be sent in Emergency Mode */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_3_0;               /* 0x458 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_3_1;               /* 0x45C - DPLL RAM1B reserved  data */
    GTM_DPLL_RCDT_TX                      RCDT_TX;                      /* 0x460 - Reciprocal Value of the Expected Increment Duration of TRIGGER */
    GTM_DPLL_RCDT_SX                      RCDT_SX;                      /* 0x464 - Reciprocal Value of the Expected Increment Duration of STATE */
    GTM_DPLL_RCDT_TX_NOM                  RCDT_TX_NOM;                  /* 0x468 - Reciprocal Value of the Expected Nominal Increment Duration of TRIGGER */
    GTM_DPLL_RCDT_SX_NOM                  RCDT_SX_NOM;                  /* 0x46C - Reciprocal Value of the Expected Nominal Increment Duration of STATE */
    GTM_DPLL_RDT_T_ACT                    RDT_T_ACT;                    /* 0x470 - Reciprocal Value of the Last Increment of TRIGGER */
    GTM_DPLL_RDT_S_ACT                    RDT_S_ACT;                    /* 0x474 - Reciprocal Value of the Last Increment of STATE */
    GTM_DPLL_DT_T_ACT                     DT_T_ACT;                     /* 0x478 - Duration of the Last TRIGGER Increment */
    GTM_DPLL_DT_S_ACT                     DT_S_ACT;                     /* 0x47C - Duration of the Last STATE Increment */
    GTM_DPLL_EDT_T                        EDT_T;                        /* 0x480 - Difference of Prediction to Actual Value of the Last TRIGGER Increment */
    GTM_DPLL_MEDT_T                       MEDT_T;                       /* 0x484 - Weighted Difference of Prediction Errors of TRIGGER */
    GTM_DPLL_EDT_S                        EDT_S;                        /* 0x488 - Difference of Prediction to Actual Value of the Last STATE Increment */
    GTM_DPLL_MEDT_S                       MEDT_S;                       /* 0x48C - Weighted Difference of Prediction Errors of STATE */
    GTM_DPLL_CDT_TX                       CDT_TX;                       /* 0x490 - Prediction of the Actual TRIGGER Increment Duration */
    GTM_DPLL_CDT_SX                       CDT_SX;                       /* 0x494 - Prediction of the Actual STATE Increment Duration */
    GTM_DPLL_CDT_TX_NOM                   CDT_TX_NOM;                   /* 0x498 - Prediction of the Nominal TRIGGER Increment Duration */
    GTM_DPLL_CDT_SX_NOM                   CDT_SX_NOM;                   /* 0x49C - Prediction of the Nominal STATE Increment Duration */
    GTM_DPLL_TLR                          TLR;                          /* 0x4A0 - TRIGGER Locking Range */
    GTM_DPLL_SLR                          SLR;                          /* 0x4A4 - STATE Locking Range */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_4_0;               /* 0x4A8 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_4_1;               /* 0x4AC - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_4_2;               /* 0x4B0 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_4_3;               /* 0x4B4 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_4_4;               /* 0x4B8 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_4_5;               /* 0x4BC - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_4_6;               /* 0x4C0 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_4_7;               /* 0x4C4 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_4_8;               /* 0x4C8 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_4_9;               /* 0x4CC - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_4_10;              /* 0x4D0 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_4_11;              /* 0x4D4 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_4_12;              /* 0x4D8 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_4_13;              /* 0x4DC - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_4_14;              /* 0x4E0 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_4_15;              /* 0x4E4 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_4_16;              /* 0x4E8 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_4_17;              /* 0x4EC - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_4_18;              /* 0x4F0 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_4_19;              /* 0x4F4 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_4_20;              /* 0x4F8 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_4_21;              /* 0x4FC - DPLL RAM1B reserved  data */
    GTM_DPLL_PDT                          PDT[32];                      /* 0x500 - Projected Increment Sum Relations for Action [n] */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_5_0;               /* 0x580 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_5_1;               /* 0x584 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_5_2;               /* 0x588 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_5_3;               /* 0x58C - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_5_4;               /* 0x590 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_5_5;               /* 0x594 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_5_6;               /* 0x598 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_5_7;               /* 0x59C - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_5_8;               /* 0x5A0 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_5_9;               /* 0x5A4 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_5_10;              /* 0x5A8 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_5_11;              /* 0x5AC - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_5_12;              /* 0x5B0 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_5_13;              /* 0x5B4 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_5_14;              /* 0x5B8 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_5_15;              /* 0x5BC - DPLL RAM1B reserved  data */
    GTM_DPLL_MLS1                         MLS1;                         /* 0x5C0 - Calculated Number of Sub-Pulses between two nominal STATE Events for DPLL_CTRL_1.SMC = 0 */
    GTM_DPLL_MLS2                         MLS2;                         /* 0x5C4 - Calculated Number of Sub-Pulses between two nominal STATE Events for DPLL_CTRL_1.SMC=1 and RMO=1 */
    GTM_DPLL_CNT_NUM_1                    CNT_NUM_1;                    /* 0x5C8 - Number of SUB_INC1 pulses in continuous mode */
    GTM_DPLL_CNT_NUM_2                    CNT_NUM_2;                    /* 0x5CC - Number of SUB_INC2 pulses in continuous mode */
    GTM_DPLL_PVT                          PVT;                          /* 0x5D0 - Plausibility Value of Next TRIGGER Slope */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_6_0;               /* 0x5D4 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_6_1;               /* 0x5D8 - DPLL RAM1B reserved  data */
    GTM_DPLL_RAM1B_RSVD                   RAM1B_RSVD_6_2;               /* 0x5DC - DPLL RAM1B reserved  data */
    GTM_DPLL_PSTC                         PSTC;                         /* 0x5E0 - Actual Calculated Position Stamp of TRIGGER */
    GTM_DPLL_PSSC                         PSSC;                         /* 0x5E4 - Actual Calculated Position Stamp of STATE */
    GTM_DPLL_PSTM                         PSTM;                         /* 0x5E8 - Measured Position Stamp at Last TRIGGER Input */
    GTM_DPLL_PSTM_OLD                     PSTM_OLD;                     /* 0x5EC - Measured Position Stamp at Last but one TRIGGER Input */
    GTM_DPLL_PSSM                         PSSM;                         /* 0x5F0 - Measured Position Stamp at Last STATE Input */
    GTM_DPLL_PSSM_OLD                     PSSM_OLD;                     /* 0x5F4 - Measured Position Stamp at Last but one STATE Input */
    GTM_DPLL_NMB_T                        NMB_T;                        /* 0x5F8 - Number of Pulses to be sent in Normal Mode */
    GTM_DPLL_NMB_S                        NMB_S;                        /* 0x5FC - Number of Pulses to be sent in Emergency Mode */
    GTM_DPLL_RDT_S                        RDT_S[64];                    /* 0x600 - Reciprocal Values of the Nominal STATE Increment Duration in FULL_SCALE for maximum [p] entries in profile for STATE (DPLL_ADT_S[p]) */
    GTM_DPLL_TSF_S                        TSF_S[64];                    /* 0x700 - Time Stamp Values of the Nominal STATE Events in FULL_SCALE for maximum [p] entries in profile for STATE (DPLL_ADT_S[p]) */
    GTM_DPLL_ADT_S                        ADT_S[64];                    /* 0x800 - Adapt and Profile Values of the STATE Increments in FULL_SCALE for maximum [p] entries */
    GTM_DPLL_DT_S                         DT_S[64];                     /* 0x900 - Nominal STATE Increment Duration in FULL_SCALE for maximum [p] entries in profile for STATE (DPLL_ADT_S[p]) */
    uint8                                 reserved_A00[1024];           /* 0xA00 - Internal  reserved */
    GTM_DPLL_TSAC                         TSAC[32];                     /* 0xE00 - Calculated Time Value to start Action [n] */
    GTM_DPLL_PSAC                         PSAC[32];                     /* 0xE80 - Calculated Position Value to start Action [n] */
    GTM_DPLL_ACB                          ACB[8];                       /* 0xF00 - Control Bits for NOAC Actions */
    GTM_DPLL_CTRL_11                      CTRL_11;                      /* 0xF20 - Control Register 11 */
    GTM_DPLL_THVAL2                       THVAL2;                       /* 0xF24 - Measured TRIGGER Hold Time Value 2 */
    GTM_DPLL_TIDEL                        TIDEL;                        /* 0xF28 - TRIGGER input delay */
    GTM_DPLL_SIDEL                        SIDEL;                        /* 0xF2C - STATE input delay */
    GTM_DPLL_APS_SYNC_EXT                 APS_SYNC_EXT;                 /* 0xF30 - STATE Time Stamp Field Offset at Synchronization Time */
    GTM_DPLL_CTRL_EXT                     CTRL_EXT;                     /* 0xF34 - STATE Time Stamp Field Offset at Synchronization Time */
    GTM_DPLL_APS_EXT                      APS_EXT;                      /* 0xF38 - Actual RAM Pointer Address for STATE */
    GTM_DPLL_APS_1C3_EXT                  APS_1C3_EXT;                  /* 0xF3C - Actual RAM Pointer Address for RAM region 1c3 (DPLL_CTRL_11.STATE_EXT=1) */
    GTM_DPLL_STA                          STA;                          /* 0xF40 - Status of the state machine states */
    GTM_DPLL_INCF1_OFFSET                 INCF1_OFFSET;                 /* 0xF44 - Start value of ADD_IN_ADDER1  */
    GTM_DPLL_INCF2_OFFSET                 INCF2_OFFSET;                 /* 0xF48 - Start value of the ADD_IN_ADDER2 */
    GTM_DPLL_DT_T_START                   DT_T_START;                   /* 0xF4C - Start value of DT_T_ACT */
    GTM_DPLL_DT_S_START                   DT_S_START;                   /* 0xF50 - Start value of DT_S_ACT */
    GTM_DPLL_STA_MASK                     STA_MASK;                     /* 0xF54 - Notify values for DPLL_STA */
    GTM_DPLL_STA_FLAG                     STA_FLAG;                     /* 0xF58 - DPLL STA Flags */
    GTM_DPLL_INC_CNT1_MASK                INC_CNT1_MASK;                /* 0xF5C - Notify value of DPLL_INC_CNT1 */
    GTM_DPLL_INC_CNT2_MASK                INC_CNT2_MASK;                /* 0xF60 - Notify value of DPLL_INC_CNT2 */
    GTM_DPLL_NUSC_EXT1                    NUSC_EXT1;                    /* 0xF64 - Number of Recent STATE Events used for Calculations */
    GTM_DPLL_NUSC_EXT2                    NUSC_EXT2;                    /* 0xF68 - Number of Recent STATE Events used for Calculations */
    GTM_DPLL_CTN_MIN                      CTN_MIN;                      /* 0xF6C - Minmum value of predicted nominal increment of TRIGGER */
    GTM_DPLL_CTN_MAX                      CTN_MAX;                      /* 0xF70 - Maximum value of predicted nominal increment of TRIGGER */
    GTM_DPLL_CSN_MIN                      CSN_MIN;                      /* 0xF74 - Minmum value of predicted nominal increment of STATE */
    GTM_DPLL_CSN_MAX                      CSN_MAX;                      /* 0xF78 - Maximum value of predicted nominal increment of STATE */
    GTM_DPLL_SW_TRIG                      SW_TRIG;                      /* 0xF7C - Software triggered input events */
    GTM_DPLL_MP_T                         MP_T;                         /* 0xF80 - Missing pulses of TRIGGER */
    GTM_DPLL_MP_S                         MP_S;                         /* 0xF84 - Missing pulses of STATE */
    GTM_DPLL_CTRL_12                      CTRL_12;                      /* 0xF88 - DPLL control register 12 */
    uint8                                 reserved_F8C[12404];          /* 0xF8C - Internal  reserved */
    GTM_DPLL_RR2                          RR2;                          /* 0x4000 - DPLL memory RR2 */
} GTM_DPLL;

/* ADCTRIG object */
typedef volatile struct
{
    GTM_ADCTRIG_OUTMUX0            OUTMUX0;        /* 0x0 - ADC trigger [i] output select 0 register */
    GTM_ADCTRIG_OUTMUX1            OUTMUX1;        /* 0x4 - ADC trigger [i] output select 0 register */
} GTM_ADCTRIG;

/* MSCSET object */
typedef volatile struct
{
    GTM_MSCSET_MUX0            MUX0;            /* 0x0 - MSC set [i] control [j] register */
    GTM_MSCSET_MUX1            MUX1;            /* 0x4 - MSC set [i] control [j] register */
    GTM_MSCSET_MUX2            MUX2;            /* 0x8 - MSC set [i] control [j] register */
    GTM_MSCSET_MUX3            MUX3;            /* 0xC - MSC set [i] control [j] register */
} GTM_MSCSET;

/* MSC0 input multiplex object */
typedef volatile struct
{
    GTM_MSCMUX            INL;            /* 0x0 - MSC0 input low multiplex register */
    GTM_MSCMUX            HNL;            /* 0x4 - MSC0 input high multiplex register */
    GTM_MSCMUX            INLEXT;            /* 0x8 - MSC0 input low extended multiplex register */
} GTM_MSC;

/* DMA Level 1 Multiplex object */
typedef volatile struct
{
    /* #Violation: gtm_register_h_REF_2 */
    GTM_DMAL1MUX        MUX[8];            /* 0x0 - MSC set [i] control [j] register */
} GTM_DMAL1;

/* FIFO RAM object */
typedef volatile struct
{
    GTM_FIFORAM_ALARMCLR            ALARMCLR;            /* 0x0 - FIFO RAM alarm clear register */
    GTM_FIFORAM_ERRADDRVLDCLR        ERRADDRVLDCLR;        /* 0x4 - FIFO error address valid signal clear register */
    GTM_FIFORAM_SERRADDR            SERRADDR[5];        /* 0x8 - FIFO single bit error address recording register */
    GTM_FIFORAM_MERRADDR            MERRADDR;            /* 0x1c - FIFO multi-bit error address recording register */
} GTM_FIFORAM;

/* DPLL RAM object */
typedef volatile struct
{
    GTM_DPLLRAM_ALARMCLR            ALARMCLR;            /* 0x0 - DPLL RAM alarm clear register */
    GTM_DPLLRAM_ERRADDRVLDCLR        ERRADDRVLDCLR;        /* 0x4 - DPLL error address valid signal clear register */
    GTM_DPLLRAM_SERRADDR            SERRADDR[5];        /* 0x8 - DPLL single bit error address recording register */
    GTM_DPLLRAM_MERRADDR            MERRADDR;            /* 0x1c - DPLL multi-bit error address recording register */
} GTM_DPLLRAM;
/**********************************************************************************************************************
 *                                        GTM Register Configuration Structure
 *********************************************************************************************************************/
/* GTM cluster object */
/* #Violation: gtm_register_h_REF_3 */
typedef volatile struct
{
    GTM_REV                 REV;                          /* 0x0 - GTM version control register */
    GTM_RST                 RST;                          /* 0x4 - GTM global reset register */
    GTM_CTRL                CTRL;                         /* 0x8 - GTM global control register */
    GTM_CFG                 CFG;                          /* 0xC - GTM configuration register */
    GTM_AEI_ADDR_XPT        AEI_ADDR_XPT;                 /* 0x10 - GTM AEI timeout exception address register */
    GTM_AEI_STA_XPT         AEI_STA_XPT;                  /* 0x14 - GTM AEI non zero status register */
    GTM_IRQ_NOTIFY          IRQ_NOTIFY;                   /* 0x18 - GTM Interrupt notification register */
    GTM_IRQ_EN              IRQ_EN;                       /* 0x1C - GTM interrupt enable register */
    GTM_EIRQ_EN             EIRQ_EN;                      /* 0x20 - GTM error interrupt enable register */
    GTM_IRQ_FORCINT         IRQ_FORCINT;                  /* 0x24 - GTM Software interrupt generation register */
    GTM_IRQ_MODE            IRQ_MODE;                     /* 0x28 - GTM top level interrupts mode selection */
    GTM_CLS_CLK_CFG         CLS_CLK_CFG;                  /* 0x2C - GTM Cluster Clock Configuration */
    GTM_ARU_COM_DIS         ARU_COM_DIS;                  /* 0x30 - GTM ARU communication disable */
    uint8                   reserved_34[12];              /* 0x34 - Internal  reserved */
    GTM_BRIDGE              BRIDGE;                       /* 0x40 - GTM_BRIDGE */
    GTM_MCS_AEM_DIS         MCS_AEM_DIS;                  /* 0x4C - GTM MCS master port disable register */
    uint8                   reserved_50[48];              /* 0x50 - Internal  reserved */
    GTM_CMU                 CMU;                          /* 0x80 - GTM_CMU */
    uint8                   reserved_D0[48];              /* 0xD0 - Internal  reserved */
    GTM_TBU                 TBU;                          /* 0x100 - GTM_TBU */
    uint8                   reserved_12C[84];             /* 0x12C - Internal  reserved */
    GTM_ARU                 ARU;                          /* 0x180 - GTM_ARU */
    GTM_BRC                 BRC;                          /* 0x200 - GTM_BRC */
    uint8                   reserved_278[392];            /* 0x278 - Internal  reserved */
    GTM_ICM                 ICM;                          /* 0x400 - GTM_ICM */
    uint8                   reserved_5A8[152];            /* 0x5A8 - Internal  reserved */
    GTM_MAP_CTRL            MAP_CTRL;                     /* 0x640 - MAP Control register */
    uint8                   reserved_644[60];             /* 0x644 - Internal  reserved */
    GTM_MON                 MON;                          /* 0x680 - GTM_MON */
    uint8                   reserved_6A0[32];             /* 0x6A0 - Internal  reserved */
    GTM_CMP                 CMP;                          /* 0x6C0 - GTM_CMP */
    uint8                   reserved_6D8[296];            /* 0x6D8 - Internal  reserved */
    GTM_TIM_t                 TIM;                        /* 0x800 - GTM_TIM */
    uint8                   reserved_C0C[1012];           /* 0xC0C - Internal  reserved */
    GTM_TOM_t                 TOM;                          /* 0x1000 - GTM_TOM */
    uint8                   reserved_1530[720];           /* 0x1530 - Internal  reserved */
    GTM_ATOM_t                ATOM;                         /* 0x1800 - GTM_ATOM */
    uint8                   reserved_1C60[928];           /* 0x1C60 - Internal  reserved */
    GTM_MCS                 MCS;                          /* 0x2000 - GTM_MCS */
    uint8                   reserved_2F80[128];           /* 0x2F80 - Internal  reserved */
    GTM_TIO                 TIO;                          /* 0x3000 - GTM_TIO */
    uint8                   reserved_3D14[748];           /* 0x3D14 - Internal  reserved */
    GTM_CCM                 CCM;                          /* 0x4000 - GTM_CCM */
    uint8                   reserved_4200[512];           /* 0x4200 - Internal  reserved */
    GTM_CDTM                CDTM;                         /* 0x4400 - GTM_CDTM */
    uint8                   reserved_4700[256];           /* 0x4700 - Internal  reserved */
    GTM_F2A                 F2A;                          /* 0x4800 - GTM_F2A */
    uint8                   reserved_4848[56];            /* 0x4848 - Internal  reserved */
    GTM_AFD                 AFD;                          /* 0x4880 - GTM_AFD */
    uint8                   reserved_4900[256];           /* 0x4900 - Internal  reserved */
    GTM_FIFO                FIFO;                         /* 0x4A00 - GTM_FIFO */
    GTM_SPE                 SPE;                          /* 0x4C00 - GTM_SPE */
    uint8                   reserved_4C50[944];           /* 0x4C50 - Internal  reserved */
    GTM_AXIM                AXIM;                         /* 0x5000 - GTM_AXIM */
    uint8                   reserved_50A0[3936];          /* 0x50A0 - Internal  reserved */
    GTM_FIFO_MEMORY         FIFO0_MEMORY;                 /* 0x6000 - FIFO data memory */
    uint8                   reserved_6004[8188];          /* 0x6004 - Internal  reserved */
    GTM_DPLL                DPLL;                         /* 0x8000 - GTM_DPLL */
    uint8                   reserved_C004[16380];         /* 0xC004 - Internal  reserved */
    GTM_MCS_MEM             MCS_MEM;                      /* 0x10000 - MCS[i] memory region */
    uint8                   reserved_10004[65532];        /* 0x10004 - Internal  reserved */
} GTM_CLUSTER;

/* GTM object */
/* #Violation: gtm_register_h_REF_3 */
typedef volatile struct
{
    GTM_CLUSTER                GTM_CLUSTER[GTM_CLUSTER_NUM];        /* GTM cluster object */
} GTM_MODULE;

/* GTM WRAPPER object */
typedef volatile struct
{
    /* #Violation: gtm_register_h_REF_2 */
    GTM_TIMINMUX               TIMINMUX[3];        /* 0x0 - TIM[i] input select register */
    /* #Violation: gtm_register_h_REF_2 */
    GTM_TOUTMUX                TOUTMUX[17];        /* 0xC - TOM output select register */
    /* #Violation: gtm_register_h_REF_2 */
    GTM_DSADCINMUX             DSADCINMUX[3];      /* 0x50 - DSADC input select register */
    /* #Violation: gtm_register_h_REF_2 */
    GTM_DSADCOUTMUX            DSADCOUTMUX[4];     /* 0x5C - DSADC output select register */
    /* #Violation: gtm_register_h_REF_2 */
    GTM_ADCTRIG                ADCTRIG[5];         /* 0x6C - ADCTRIG object */
    GTM_DEXOUTCON              DEXOUTCON;          /* 0x94 - Data exchange output control register */
    GTM_TRIGOUTCON             TRIGOUTCON[4];      /* 0x98 - Data exchange output control register */
    GTM_INTOUTCON              INTOUTCON[4];       /* 0xA8 - Data exchange output control register */
    GTM_TRIGOUTMUX             TRIGOUTMUX;         /* 0xB8 - Trigger output select register */
    GTM_INTSTS                 INTSTS;             /* 0xBC - MCS interrupt status register */
    GTM_INTSTSCLR              INTSTSCLR;          /* 0xC0 - MCS interrupt clear register */
    GTM_DEXINCON               DEXINCON;           /* 0xC4 - Data exchange input control register */
    GTM_DATAIN                 DATAIN[4];          /* 0xC8 - Data input input register */
    /* #Violation: gtm_register_h_REF_2 */
    GTM_MSCSET                 MSCSET[4];          /* 0xD8 - MSCSET object */
    GTM_MSC                    MSC0MUX;            /* 0x118 - MSC0 input multiplex object */
    GTM_DTMAUXINMUX            DTMAUXINMUX;        /* 0x124 - DTM_AUX input multiplex register */
    GTM_CANOUTMUX              CANOUTMUX;          /* 0x128 - CAN output multiplex register */
    GTM_RDCOUTMUX              RDCOUTMUX;          /* 0x12C - RDC output multiplex register */
    GTM_IDRQEN                 IDRQEN;             /* 0x130 - Interrupt Request and DMA Request Enable register */
    /* #Violation: gtm_register_h_REF_2 */
    GTM_DMAL1                  DMAL1MUX[4];        /* 0x134 - DMA Level 1 Multiplex object */
    /* #Violation: gtm_register_h_REF_2 */
    GTM_DMAL1COMMUX            DMAL1COMMUX[10];    /* 0x1B4 - DMA Level 1 Common Multiplex register */
    /* #Violation: gtm_register_h_REF_2 */
    GTM_DMAL2MUX               DMAL2MUX[8];        /* 0x1DC - DMA Level 2 Multiplex register */
    GTM_DBGCTRL                DBGCTRL;            /* 0x1FC - GTM Debug Control register */
    GTM_TIOINMUX               TIOINMUX[3];        /* 0x200 - GTM TIO Input Multiplex register */
    uint8                      reserved_20C[244];  /* 0x20C - Internal  reserved */
    GTM_RAMECCEN               RAMECCEN;           /* 0x300 - RAM Data ECC Check Enable register */
    GTM_RAMREMAPEN             RAMREMAPEN;         /* 0x304 - RAM Data REMAP Function Enable register */
    GTM_RAMHWINJ               RAMHWINJ;           /* 0x308 - RAM Hardware Fault Injection Enable register */
    GTM_FIFORAM                FIFORAM[3];         /* 0x30C - FIFO RAM object */
    GTM_DPLLRAM                DPLLRAM[3];         /* 0x36C - DPLL RAM object */
    GTM_SBESTS                 SBESTS;             /* 0x3CC - Single Bit Error Status Register */
    GTM_MBESTS                 MBESTS;             /* 0x3D0 - Multi-bit Error Status Register */
    GTM_SROSTS                 SROSTS;             /* 0x3D4 - Single Bit Error Overflow State Register */
    GTM_DMATOCFG               DMATOCFG;           /* 0x3D8 - DMA Timeout Configuration Register */
    GTM_DMATOSAFETYEN          DMATOSAFETYEN;      /* 0x3DC - DMA Timeout Safety Mechanism Enable Register */
    GTM_DMATOFAULTINJ          DMATOFAULTINJ;      /* 0x3E0 - DMA Timeout Fault Injection Register */
    GTM_DMATOALARMCLR          DMATOALARMCLR;      /* 0x3E4 - DMA Timeout Alarm Clear Register */
    GTM_DMATOCHSTS             DMATOCHSTS;         /* 0x3E8 - DMA Timeout Channel Status Register */
    GTM_REGSAFETYEN            REGSAFETYEN;        /* 0x3EC - Register Safety Mechanism */
    GTM_REGALARMCLR            REGALARMCLR;        /* 0x3F0 - Register Alarm Status Clear */
    GTM_REGALARMSTS            REGALARMSTS;        /* 0x3F4 - Register Alarm Status */
    GTM_REGIACLR               REGIACLR;           /* 0x3F8 - Illegal Access Alarm Clearing Register */
    GTM_REGIAALARMSTS          REGIAALARMSTS;      /* 0x3FC - Illegal Access Alarm Status rRegister */
    GTM_ADALARMEN              ADALARMEN;          /* 0x400 - ADC Data Ecc Alarm Enable Register */
    GTM_ADALARMCLR             ADALARMCLR;         /* 0x404 - ADC Data Ecc Alarm Clear Register */
    GTM_ADALARMSTS             ADALARMSTS;         /* 0x408 - ADC Data Ecc Alarm Status Register */
    uint8                      reserved_40C[500];  /* 0x40C - Internal  reserved */
    GTM_DGCR                   DGCR;               /* 0x600 - GTM Debug Global Control Register */
    GTM_DHCR                   DHCR;               /* 0x604 - GTM Debug Halt Control Register */
    GTM_DHSR                   DHSR;               /* 0x608 - GTM Debug Halt Status Register */
    uint8                      reserved_60C[436];  /* 0x60C - Internal  reserved */
    GTM_DMCSBPEN               DMCSBPEN;           /* 0x7C0 - MCS Break Point Enable Register */
    uint8                      reserved_7C4[60];   /* 0x7C4 - Internal  reserved */
    /* #Violation: gtm_register_h_REF_2 */
    GTM_TIMINMUX               TIMINMUX1[5];       /* 0x800 - TIM[i] input select register (THA6412 only) */
    /* #Violation: gtm_register_h_REF_2 */
    GTM_TOUTMUX                TOUTMUX1[17];       /* 0x814 - TOM output select register (THA6412 only) */
    /* #Violation: gtm_register_h_REF_2 */
    GTM_DSADCINMUX             DSADCINMUX1[3];     /* 0x858 - DSADC input select register (THA6412 only) */
    /* #Violation: gtm_register_h_REF_2 */
    GTM_DSADCOUTMUX1           DSADCOUTMUX1[4];    /* 0x864 - DSADC output select register (THA6412 only) */
    GTM_TRIGOUTCON             TRIGOUTCON1[4];     /* 0x874 - Data exchange output control register (THA6412 only) */
    uint8                      reserved_884[8];    /* 0x884 - Internal  reserved */
    GTM_INTOUTCON              INTOUTCON1[4];      /* 0x88C - Data input output control register (THA6412 only) */
    uint8                      reserved_89C[8];    /* 0x89C - Internal  reserved */
    GTM_DATAIN                 DATAIN1[4];         /* 0x8A4 - Data input input register (THA6412 only) */
    uint8                      reserved_8B4[8];    /* 0x8B4 - Internal  reserved */
    /* #Violation: gtm_register_h_REF_2 */
    GTM_MSCSET                 MSCSET1[3];         /* 0x8BC - MSCSET object (THA6412 only) */
    uint8                      reserved_8EC[32];   /* 0x8EC - Internal  reserved */
    GTM_MSC                    MSC1MUX;            /* 0x90C - MSC1 input multiplex object (THA6412 only) */
    GTM_MSC                    MSC2MUX;            /* 0x918 - MSC2 input multiplex object (THA6412 only) */
    uint8                      reserved_924[12];   /* 0x924 - Internal  reserved */
    GTM_CANOUTMUX              CANOUTMUX1;         /* 0x930 - CAN output multiplex register (THA6412 only) */
    /* #Violation: gtm_register_h_REF_2 */
    GTM_DMAL1                  DMAL1MUX1[4];       /* 0x934 - DMA Level 1 Multiplex object (THA6412 only) */
    uint8                      reserved_9B4[128];  /* 0x9B4 - Internal  reserved */
    GTM_TIOINMUX               TIOINMUX1[2];       /* 0xA34 - GTM TIO Input Multiplex register (THA6412 only) */
    uint8                      reserved_A40[16];   /* 0xA40 - Internal  reserved */
    GTM_HRPWMCTRL              HRPWMCTRL;          /* 0xA4C - GTM High Resolution PWM Control register (THA6412 only) */
    GTM_HRPWMCORNELSEL         HRPWMCORNELSEL;     /* 0xA50 - GTM High Resolution PWM Control Select register (THA6412 only) */
    GTM_HRPWMOUTMUX            HRPWMOUTMUX[2];     /* 0xA54 - GTM High Resolution PWM Output Multiplex register (THA6412 only) */
    GTM_PSI5OUTMUX             PSI5OUTMUX;         /* 0xA5C - PSI5 Output Multiplex register (THA6412 only) */
    GTM_TIOOUTMUX              TIOOUTMUX[2];       /* 0xA60 - TIO Output Multiplex register (THA6412 only) */
    GTM_RDCOUTMUX              RDCOUTMUX1;         /* 0xA68 - RDC output multiplex1 register (THA6412 only) */
    GTM_RDCOUTL2MUX            RDCOUTL2MUX;        /* 0xA6C - RDC output multiplex register (THA6412 only) */
} GTM_WRAPPER;


#endif /* GTM_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
