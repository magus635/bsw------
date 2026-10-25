/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    dma_register.h
 * Author:      01254
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all definitions of DMA module registers.
 *********************************************************************************************************************/

/*
*#Violation Summary
*
*#dma_register_h_REF_1:MISRAC2012-Dir-4.8;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#dma_register_h_REF_2:MISRAC2012-Rule-19.2;
* Justification: Using unions for bit-field access to register.
*
*#dma_register_h_REF_3:CWE-547;
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*
*#dma_register_h_REF_4:CertC-DCL06-C;
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*
*#dma_register_h_REF_5:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*/

#ifndef DMA_REGISTER_H_
#define DMA_REGISTER_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "Platform_Types.h"
#include "regtypes.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                        DMA Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* DMA interrupt status register 0 */
typedef volatile struct
{
    ureg32 INTSTAT0:1;  /* [0:0] Interrupt status for channel 0 -R */
    ureg32 INTSTAT1:1;  /* [1:1] Interrupt status for channel 1 -R */
    ureg32 INTSTAT2:1;  /* [2:2] Interrupt status for channel 2 -R */
    ureg32 INTSTAT3:1;  /* [3:3] Interrupt status for channel 3 -R */
    ureg32 INTSTAT4:1;  /* [4:4] Interrupt status for channel 4 -R */
    ureg32 INTSTAT5:1;  /* [5:5] Interrupt status for channel 5 -R */
    ureg32 INTSTAT6:1;  /* [6:6] Interrupt status for channel 6 -R */
    ureg32 INTSTAT7:1;  /* [7:7] Interrupt status for channel 7 -R */
    ureg32 INTSTAT8:1;  /* [8:8] Interrupt status for channel 8 -R */
    ureg32 INTSTAT9:1;  /* [9:9] Interrupt status for channel 9 -R */
    ureg32 INTSTAT10:1; /* [10:10] Interrupt status for channel 10 -R */
    ureg32 INTSTAT11:1; /* [11:11] Interrupt status for channel 11 -R */
    ureg32 INTSTAT12:1; /* [12:12] Interrupt status for channel 12 -R */
    ureg32 INTSTAT13:1; /* [13:13] Interrupt status for channel 13 -R */
    ureg32 INTSTAT14:1; /* [14:14] Interrupt status for channel 14 -R */
    ureg32 INTSTAT15:1; /* [15:15] Interrupt status for channel 15 -R */
    ureg32 INTSTAT16:1; /* [16:16] Interrupt status for channel 16 -R */
    ureg32 INTSTAT17:1; /* [17:17] Interrupt status for channel 17 -R */
    ureg32 INTSTAT18:1; /* [18:18] Interrupt status for channel 18 -R */
    ureg32 INTSTAT19:1; /* [19:19] Interrupt status for channel 19 -R */
    ureg32 INTSTAT20:1; /* [20:20] Interrupt status for channel 20 -R */
    ureg32 INTSTAT21:1; /* [21:21] Interrupt status for channel 21 -R */
    ureg32 INTSTAT22:1; /* [22:22] Interrupt status for channel 22 -R */
    ureg32 INTSTAT23:1; /* [23:23] Interrupt status for channel 23 -R */
    ureg32 INTSTAT24:1; /* [24:24] Interrupt status for channel 24 -R */
    ureg32 INTSTAT25:1; /* [25:25] Interrupt status for channel 25 -R */
    ureg32 INTSTAT26:1; /* [26:26] Interrupt status for channel 26 -R */
    ureg32 INTSTAT27:1; /* [27:27] Interrupt status for channel 27 -R */
    ureg32 INTSTAT28:1; /* [28:28] Interrupt status for channel 28 -R */
    ureg32 INTSTAT29:1; /* [29:29] Interrupt status for channel 29 -R */
    ureg32 INTSTAT30:1; /* [30:30] Interrupt status for channel 30 -R */
    ureg32 INTSTAT31:1; /* [31:31] Interrupt status for channel 31 -R */
} DMA_INTSTATUS0_Bits;

/* DMA interrupt status register 1 */
typedef volatile struct
{
    ureg32 INTSTAT32:1; /* [0:0] Interrupt status for channel 32 -R */
    ureg32 INTSTAT33:1; /* [1:1] Interrupt status for channel 33 -R */
    ureg32 INTSTAT34:1; /* [2:2] Interrupt status for channel 34 -R */
    ureg32 INTSTAT35:1; /* [3:3] Interrupt status for channel 35 -R */
    ureg32 INTSTAT36:1; /* [4:4] Interrupt status for channel 36 -R */
    ureg32 INTSTAT37:1; /* [5:5] Interrupt status for channel 37 -R */
    ureg32 INTSTAT38:1; /* [6:6] Interrupt status for channel 38 -R */
    ureg32 INTSTAT39:1; /* [7:7] Interrupt status for channel 39 -R */
    ureg32 INTSTAT40:1; /* [8:8] Interrupt status for channel 40 -R */
    ureg32 INTSTAT41:1; /* [9:9] Interrupt status for channel 41 -R */
    ureg32 INTSTAT42:1; /* [10:10] Interrupt status for channel 42 -R */
    ureg32 INTSTAT43:1; /* [11:11] Interrupt status for channel 43 -R */
    ureg32 INTSTAT44:1; /* [12:12] Interrupt status for channel 44 -R */
    ureg32 INTSTAT45:1; /* [13:13] Interrupt status for channel 45 -R */
    ureg32 INTSTAT46:1; /* [14:14] Interrupt status for channel 46 -R */
    ureg32 INTSTAT47:1; /* [15:15] Interrupt status for channel 47 -R */
    ureg32 INTSTAT48:1; /* [16:16] Interrupt status for channel 48 -R */
    ureg32 INTSTAT49:1; /* [17:17] Interrupt status for channel 49 -R */
    ureg32 INTSTAT50:1; /* [18:18] Interrupt status for channel 50 -R */
    ureg32 INTSTAT51:1; /* [19:19] Interrupt status for channel 51 -R */
    ureg32 INTSTAT52:1; /* [20:20] Interrupt status for channel 52 -R */
    ureg32 INTSTAT53:1; /* [21:21] Interrupt status for channel 53 -R */
    ureg32 INTSTAT54:1; /* [22:22] Interrupt status for channel 54 -R */
    ureg32 INTSTAT55:1; /* [23:23] Interrupt status for channel 55 -R */
    ureg32 INTSTAT56:1; /* [24:24] Interrupt status for channel 56 -R */
    ureg32 INTSTAT57:1; /* [25:25] Interrupt status for channel 57 -R */
    ureg32 INTSTAT58:1; /* [26:26] Interrupt status for channel 58 -R */
    ureg32 INTSTAT59:1; /* [27:27] Interrupt status for channel 59 -R */
    ureg32 INTSTAT60:1; /* [28:28] Interrupt status for channel 60 -R */
    ureg32 INTSTAT61:1; /* [29:29] Interrupt status for channel 61 -R */
    ureg32 INTSTAT62:1; /* [30:30] Interrupt status for channel 62 -R */
    ureg32 INTSTAT63:1; /* [31:31] Interrupt status for channel 63 -R */
} DMA_INTSTATUS1_Bits;

/* DMA enabled channel status register 0 */
typedef volatile struct
{
    ureg32 ENBLD0:1;  /* [0:0] Enabled channel status for channel 0 -R */
    ureg32 ENBLD1:1;  /* [1:1] Enabled channel status for channel 1 -R */
    ureg32 ENBLD2:1;  /* [2:2] Enabled channel status for channel 2 -R */
    ureg32 ENBLD3:1;  /* [3:3] Enabled channel status for channel 3 -R */
    ureg32 ENBLD4:1;  /* [4:4] Enabled channel status for channel 4 -R */
    ureg32 ENBLD5:1;  /* [5:5] Enabled channel status for channel 5 -R */
    ureg32 ENBLD6:1;  /* [6:6] Enabled channel status for channel 6 -R */
    ureg32 ENBLD7:1;  /* [7:7] Enabled channel status for channel 7 -R */
    ureg32 ENBLD8:1;  /* [8:8] Enabled channel status for channel 8 -R */
    ureg32 ENBLD9:1;  /* [9:9] Enabled channel status for channel 9 -R */
    ureg32 ENBLD10:1; /* [10:10] Enabled channel status for channel 10 -R */
    ureg32 ENBLD11:1; /* [11:11] Enabled channel status for channel 11 -R */
    ureg32 ENBLD12:1; /* [12:12] Enabled channel status for channel 12 -R */
    ureg32 ENBLD13:1; /* [13:13] Enabled channel status for channel 13 -R */
    ureg32 ENBLD14:1; /* [14:14] Enabled channel status for channel 14 -R */
    ureg32 ENBLD15:1; /* [15:15] Enabled channel status for channel 15 -R */
    ureg32 ENBLD16:1; /* [16:16] Enabled channel status for channel 16 -R */
    ureg32 ENBLD17:1; /* [17:17] Enabled channel status for channel 17 -R */
    ureg32 ENBLD18:1; /* [18:18] Enabled channel status for channel 18 -R */
    ureg32 ENBLD19:1; /* [19:19] Enabled channel status for channel 19 -R */
    ureg32 ENBLD20:1; /* [20:20] Enabled channel status for channel 20 -R */
    ureg32 ENBLD21:1; /* [21:21] Enabled channel status for channel 21 -R */
    ureg32 ENBLD22:1; /* [22:22] Enabled channel status for channel 22 -R */
    ureg32 ENBLD23:1; /* [23:23] Enabled channel status for channel 23 -R */
    ureg32 ENBLD24:1; /* [24:24] Enabled channel status for channel 24 -R */
    ureg32 ENBLD25:1; /* [25:25] Enabled channel status for channel 25 -R */
    ureg32 ENBLD26:1; /* [26:26] Enabled channel status for channel 26 -R */
    ureg32 ENBLD27:1; /* [27:27] Enabled channel status for channel 27 -R */
    ureg32 ENBLD28:1; /* [28:28] Enabled channel status for channel 28 -R */
    ureg32 ENBLD29:1; /* [29:29] Enabled channel status for channel 29 -R */
    ureg32 ENBLD30:1; /* [30:30] Enabled channel status for channel 30 -R */
    ureg32 ENBLD31:1; /* [31:31] Enabled channel status for channel 31 -R */
} DMA_ENBLDCHNS0_Bits;

/* DMA enabled channel status register 1 */
typedef volatile struct
{
    ureg32 ENBLD32:1; /* [0:0] Enabled channel status for channel 32 -R */
    ureg32 ENBLD33:1; /* [1:1] Enabled channel status for channel 33 -R */
    ureg32 ENBLD34:1; /* [2:2] Enabled channel status for channel 34 -R */
    ureg32 ENBLD35:1; /* [3:3] Enabled channel status for channel 35 -R */
    ureg32 ENBLD36:1; /* [4:4] Enabled channel status for channel 36 -R */
    ureg32 ENBLD37:1; /* [5:5] Enabled channel status for channel 37 -R */
    ureg32 ENBLD38:1; /* [6:6] Enabled channel status for channel 38 -R */
    ureg32 ENBLD39:1; /* [7:7] Enabled channel status for channel 39 -R */
    ureg32 ENBLD40:1; /* [8:8] Enabled channel status for channel 40 -R */
    ureg32 ENBLD41:1; /* [9:9] Enabled channel status for channel 41 -R */
    ureg32 ENBLD42:1; /* [10:10] Enabled channel status for channel 42 -R */
    ureg32 ENBLD43:1; /* [11:11] Enabled channel status for channel 43 -R */
    ureg32 ENBLD44:1; /* [12:12] Enabled channel status for channel 44 -R */
    ureg32 ENBLD45:1; /* [13:13] Enabled channel status for channel 45 -R */
    ureg32 ENBLD46:1; /* [14:14] Enabled channel status for channel 46 -R */
    ureg32 ENBLD47:1; /* [15:15] Enabled channel status for channel 47 -R */
    ureg32 ENBLD48:1; /* [16:16] Enabled channel status for channel 48 -R */
    ureg32 ENBLD49:1; /* [17:17] Enabled channel status for channel 49 -R */
    ureg32 ENBLD50:1; /* [18:18] Enabled channel status for channel 50 -R */
    ureg32 ENBLD51:1; /* [19:19] Enabled channel status for channel 51 -R */
    ureg32 ENBLD52:1; /* [20:20] Enabled channel status for channel 52 -R */
    ureg32 ENBLD53:1; /* [21:21] Enabled channel status for channel 53 -R */
    ureg32 ENBLD54:1; /* [22:22] Enabled channel status for channel 54 -R */
    ureg32 ENBLD55:1; /* [23:23] Enabled channel status for channel 55 -R */
    ureg32 ENBLD56:1; /* [24:24] Enabled channel status for channel 56 -R */
    ureg32 ENBLD57:1; /* [25:25] Enabled channel status for channel 57 -R */
    ureg32 ENBLD58:1; /* [26:26] Enabled channel status for channel 58 -R */
    ureg32 ENBLD59:1; /* [27:27] Enabled channel status for channel 59 -R */
    ureg32 ENBLD60:1; /* [28:28] Enabled channel status for channel 60 -R */
    ureg32 ENBLD61:1; /* [29:29] Enabled channel status for channel 61 -R */
    ureg32 ENBLD62:1; /* [30:30] Enabled channel status for channel 62 -R */
    ureg32 ENBLD63:1; /* [31:31] Enabled channel status for channel 63 -R */
} DMA_ENBLDCHNS1_Bits;

/* DMA software burst request register x (x = 0 ~ 7) */
typedef volatile struct
{
    ureg32 SOFTBREQ0:1;  /* [0:0] Generate software burst request on burst request line 0 -RWH */
    ureg32 SOFTBREQ1:1;  /* [1:1] Generate software burst request on burst request line 1 -RWH */
    ureg32 SOFTBREQ2:1;  /* [2:2] Generate software burst request on burst request line 2 -RWH */
    ureg32 SOFTBREQ3:1;  /* [3:3] Generate software burst request on burst request line 3 -RWH */
    ureg32 SOFTBREQ4:1;  /* [4:4] Generate software burst request on burst request line 4 -RWH */
    ureg32 SOFTBREQ5:1;  /* [5:5] Generate software burst request on burst request line 5 -RWH */
    ureg32 SOFTBREQ6:1;  /* [6:6] Generate software burst request on burst request line 6 -RWH */
    ureg32 SOFTBREQ7:1;  /* [7:7] Generate software burst request on burst request line 7 -RWH */
    ureg32 SOFTBREQ8:1;  /* [8:8] Generate software burst request on burst request line 8 -RWH */
    ureg32 SOFTBREQ9:1;  /* [9:9] Generate software burst request on burst request line 9 -RWH */
    ureg32 SOFTBREQ10:1; /* [10:10] Generate software burst request on burst request line 10 -RWH */
    ureg32 SOFTBREQ11:1; /* [11:11] Generate software burst request on burst request line 11 -RWH */
    ureg32 SOFTBREQ12:1; /* [12:12] Generate software burst request on burst request line 12 -RWH */
    ureg32 SOFTBREQ13:1; /* [13:13] Generate software burst request on burst request line 13 -RWH */
    ureg32 SOFTBREQ14:1; /* [14:14] Generate software burst request on burst request line 14 -RWH */
    ureg32 SOFTBREQ15:1; /* [15:15] Generate software burst request on burst request line 15 -RWH */
    ureg32 SOFTBREQ16:1; /* [16:16] Generate software burst request on burst request line 16 -RWH */
    ureg32 SOFTBREQ17:1; /* [17:17] Generate software burst request on burst request line 17 -RWH */
    ureg32 SOFTBREQ18:1; /* [18:18] Generate software burst request on burst request line 18 -RWH */
    ureg32 SOFTBREQ19:1; /* [19:19] Generate software burst request on burst request line 19 -RWH */
    ureg32 SOFTBREQ20:1; /* [20:20] Generate software burst request on burst request line 20 -RWH */
    ureg32 SOFTBREQ21:1; /* [21:21] Generate software burst request on burst request line 21 -RWH */
    ureg32 SOFTBREQ22:1; /* [22:22] Generate software burst request on burst request line 22 -RWH */
    ureg32 SOFTBREQ23:1; /* [23:23] Generate software burst request on burst request line 23 -RWH */
    ureg32 SOFTBREQ24:1; /* [24:24] Generate software burst request on burst request line 24 -RWH */
    ureg32 SOFTBREQ25:1; /* [25:25] Generate software burst request on burst request line 25 -RWH */
    ureg32 SOFTBREQ26:1; /* [26:27] Generate software burst request on burst request line 27 -RWH */
    ureg32 SOFTBREQ27:1; /* [27:27] Generate software burst request on burst request line 27 -RWH */
    ureg32 SOFTBREQ28:1; /* [28:28] Generate software burst request on burst request line 28 -RWH */
    ureg32 SOFTBREQ29:1; /* [29:29] Generate software burst request on burst request line 29 -RWH */
    ureg32 SOFTBREQ30:1; /* [30:30] Generate software burst request on burst request line 30 -RWH */
    ureg32 SOFTBREQ31:1; /* [31:31] Generate software burst request on burst request line 31 -RWH */
} DMA_SOFTBREQ_Bits;

/* DMA software single request register x (x = 0 ~ 7) */
typedef volatile struct
{
    ureg32 SOFTSREQ0:1;  /* [0:0] Generate software single request on single request line 0 -RWH */
    ureg32 SOFTSREQ1:1;  /* [1:1] Generate software single request on single request line 1 -RWH */
    ureg32 SOFTSREQ2:1;  /* [2:2] Generate software single request on single request line 2 -RWH */
    ureg32 SOFTSREQ3:1;  /* [3:3] Generate software single request on single request line 3 -RWH */
    ureg32 SOFTSREQ4:1;  /* [4:4] Generate software single request on single request line 4 -RWH */
    ureg32 SOFTSREQ5:1;  /* [5:5] Generate software single request on single request line 5 -RWH */
    ureg32 SOFTSREQ6:1;  /* [6:6] Generate software single request on single request line 6 -RWH */
    ureg32 SOFTSREQ7:1;  /* [7:7] Generate software single request on single request line 7 -RWH */
    ureg32 SOFTSREQ8:1;  /* [8:8] Generate software single request on single request line 8 -RWH */
    ureg32 SOFTSREQ9:1;  /* [9:9] Generate software single request on single request line 9 -RWH */
    ureg32 SOFTSREQ10:1; /* [10:10] Generate software single request on single request line 10 -RWH */
    ureg32 SOFTSREQ11:1; /* [11:11] Generate software single request on single request line 11 -RWH */
    ureg32 SOFTSREQ12:1; /* [12:12] Generate software single request on single request line 12 -RWH */
    ureg32 SOFTSREQ13:1; /* [13:13] Generate software single request on single request line 13 -RWH */
    ureg32 SOFTSREQ14:1; /* [14:14] Generate software single request on single request line 14 -RWH */
    ureg32 SOFTSREQ15:1; /* [15:15] Generate software single request on single request line 15 -RWH */
    ureg32 SOFTSREQ16:1; /* [16:16] Generate software single request on single request line 16 -RWH */
    ureg32 SOFTSREQ17:1; /* [17:17] Generate software single request on single request line 17 -RWH */
    ureg32 SOFTSREQ18:1; /* [18:18] Generate software single request on single request line 18 -RWH */
    ureg32 SOFTSREQ19:1; /* [19:19] Generate software single request on single request line 19 -RWH */
    ureg32 SOFTSREQ20:1; /* [20:20] Generate software single request on single request line 20 -RWH */
    ureg32 SOFTSREQ21:1; /* [21:21] Generate software single request on single request line 21 -RWH */
    ureg32 SOFTSREQ22:1; /* [22:22] Generate software single request on single request line 22 -RWH */
    ureg32 SOFTSREQ23:1; /* [23:23] Generate software single request on single request line 23 -RWH */
    ureg32 SOFTSREQ24:1; /* [24:24] Generate software single request on single request line 24 -RWH */
    ureg32 SOFTSREQ25:1; /* [25:25] Generate software single request on single request line 25 -RWH */
    ureg32 SOFTSREQ26:1; /* [26:27] Generate software single request on single request line 27 -RWH */
    ureg32 SOFTSREQ27:1; /* [27:27] Generate software single request on single request line 27 -RWH */
    ureg32 SOFTSREQ28:1; /* [28:28] Generate software single request on single request line 28 -RWH */
    ureg32 SOFTSREQ29:1; /* [29:29] Generate software single request on single request line 29 -RWH */
    ureg32 SOFTSREQ30:1; /* [30:30] Generate software single request on single request line 30 -RWH */
    ureg32 SOFTSREQ31:1; /* [31:31] Generate software single request on single request line 31 -RWH */
} DMA_SOFTSREQ_Bits;

/* DMA software last burst request register x (x = 0 ~ 7) */
typedef volatile struct
{
    ureg32 SOFTLBREQ0:1;  /* [0:0] Generate software last burst request on burst request line 0 -RWH */
    ureg32 SOFTLBREQ1:1;  /* [1:1] Generate software last burst request on burst request line 1 -RWH */
    ureg32 SOFTLBREQ2:1;  /* [2:2] Generate software last burst request on burst request line 2 -RWH */
    ureg32 SOFTLBREQ3:1;  /* [3:3] Generate software last burst request on burst request line 3 -RWH */
    ureg32 SOFTLBREQ4:1;  /* [4:4] Generate software last burst request on burst request line 4 -RWH */
    ureg32 SOFTLBREQ5:1;  /* [5:5] Generate software last burst request on burst request line 5 -RWH */
    ureg32 SOFTLBREQ6:1;  /* [6:6] Generate software last burst request on burst request line 6 -RWH */
    ureg32 SOFTLBREQ7:1;  /* [7:7] Generate software last burst request on burst request line 7 -RWH */
    ureg32 SOFTLBREQ8:1;  /* [8:8] Generate software last burst request on burst request line 8 -RWH */
    ureg32 SOFTLBREQ9:1;  /* [9:9] Generate software last burst request on burst request line 9 -RWH */
    ureg32 SOFTLBREQ10:1; /* [10:10] Generate software last burst request on burst request line 10 -RWH */
    ureg32 SOFTLBREQ11:1; /* [11:11] Generate software last burst request on burst request line 11 -RWH */
    ureg32 SOFTLBREQ12:1; /* [12:12] Generate software last burst request on burst request line 12 -RWH */
    ureg32 SOFTLBREQ13:1; /* [13:13] Generate software last burst request on burst request line 13 -RWH */
    ureg32 SOFTLBREQ14:1; /* [14:14] Generate software last burst request on burst request line 14 -RWH */
    ureg32 SOFTLBREQ15:1; /* [15:15] Generate software last burst request on burst request line 15 -RWH */
    ureg32 SOFTLBREQ16:1; /* [16:16] Generate software last burst request on burst request line 16 -RWH */
    ureg32 SOFTLBREQ17:1; /* [17:17] Generate software last burst request on burst request line 17 -RWH */
    ureg32 SOFTLBREQ18:1; /* [18:18] Generate software last burst request on burst request line 18 -RWH */
    ureg32 SOFTLBREQ19:1; /* [19:19] Generate software last burst request on burst request line 19 -RWH */
    ureg32 SOFTLBREQ20:1; /* [20:20] Generate software last burst request on burst request line 20 -RWH */
    ureg32 SOFTLBREQ21:1; /* [21:21] Generate software last burst request on burst request line 21 -RWH */
    ureg32 SOFTLBREQ22:1; /* [22:22] Generate software last burst request on burst request line 22 -RWH */
    ureg32 SOFTLBREQ23:1; /* [23:23] Generate software last burst request on burst request line 23 -RWH */
    ureg32 SOFTLBREQ24:1; /* [24:24] Generate software last burst request on burst request line 24 -RWH */
    ureg32 SOFTLBREQ25:1; /* [25:25] Generate software last burst request on burst request line 25 -RWH */
    ureg32 SOFTLBREQ26:1; /* [26:27] Generate software last burst request on burst request line 27 -RWH */
    ureg32 SOFTLBREQ27:1; /* [27:27] Generate software last burst request on burst request line 27 -RWH */
    ureg32 SOFTLBREQ28:1; /* [28:28] Generate software last burst request on burst request line 28 -RWH */
    ureg32 SOFTLBREQ29:1; /* [29:29] Generate software last burst request on burst request line 29 -RWH */
    ureg32 SOFTLBREQ30:1; /* [30:30] Generate software last burst request on burst request line 30 -RWH */
    ureg32 SOFTLBREQ31:1; /* [31:31] Generate software last burst request on burst request line 31 -RWH */
} DMA_SOFTLBREQ_Bits;

/* DMA software last single request register x (x = 0 ~ 7) */
typedef volatile struct
{
    ureg32 SOFTLSREQ0:1;  /* [0:0] Generate software last single request on last request line 0 -RWH */
    ureg32 SOFTLSREQ1:1;  /* [1:1] Generate software last single request on last request line 1 -RWH */
    ureg32 SOFTLSREQ2:1;  /* [2:2] Generate software last single request on last request line 2 -RWH */
    ureg32 SOFTLSREQ3:1;  /* [3:3] Generate software last single request on last request line 3 -RWH */
    ureg32 SOFTLSREQ4:1;  /* [4:4] Generate software last single request on last request line 4 -RWH */
    ureg32 SOFTLSREQ5:1;  /* [5:5] Generate software last single request on last request line 5 -RWH */
    ureg32 SOFTLSREQ6:1;  /* [6:6] Generate software last single request on last request line 6 -RWH */
    ureg32 SOFTLSREQ7:1;  /* [7:7] Generate software last single request on last request line 7 -RWH */
    ureg32 SOFTLSREQ8:1;  /* [8:8] Generate software last single request on last request line 8 -RWH */
    ureg32 SOFTLSREQ9:1;  /* [9:9] Generate software last single request on last request line 9 -RWH */
    ureg32 SOFTLSREQ10:1; /* [10:10] Generate software last single request on last request line 10 -RWH */
    ureg32 SOFTLSREQ11:1; /* [11:11] Generate software last single request on last request line 11 -RWH */
    ureg32 SOFTLSREQ12:1; /* [12:12] Generate software last single request on last request line 12 -RWH */
    ureg32 SOFTLSREQ13:1; /* [13:13] Generate software last single request on last request line 13 -RWH */
    ureg32 SOFTLSREQ14:1; /* [14:14] Generate software last single request on last request line 14 -RWH */
    ureg32 SOFTLSREQ15:1; /* [15:15] Generate software last single request on last request line 15 -RWH */
    ureg32 SOFTLSREQ16:1; /* [16:16] Generate software last single request on last request line 16 -RWH */
    ureg32 SOFTLSREQ17:1; /* [17:17] Generate software last single request on last request line 17 -RWH */
    ureg32 SOFTLSREQ18:1; /* [18:18] Generate software last single request on last request line 18 -RWH */
    ureg32 SOFTLSREQ19:1; /* [19:19] Generate software last single request on last request line 19 -RWH */
    ureg32 SOFTLSREQ20:1; /* [20:20] Generate software last single request on last request line 20 -RWH */
    ureg32 SOFTLSREQ21:1; /* [21:21] Generate software last single request on last request line 21 -RWH */
    ureg32 SOFTLSREQ22:1; /* [22:22] Generate software last single request on last request line 22 -RWH */
    ureg32 SOFTLSREQ23:1; /* [23:23] Generate software last single request on last request line 23 -RWH */
    ureg32 SOFTLSREQ24:1; /* [24:24] Generate software last single request on last request line 24 -RWH */
    ureg32 SOFTLSREQ25:1; /* [25:25] Generate software last single request on last request line 25 -RWH */
    ureg32 SOFTLSREQ26:1; /* [26:27] Generate software last single request on last request line 27 -RWH */
    ureg32 SOFTLSREQ27:1; /* [27:27] Generate software last single request on last request line 27 -RWH */
    ureg32 SOFTLSREQ28:1; /* [28:28] Generate software last single request on last request line 28 -RWH */
    ureg32 SOFTLSREQ29:1; /* [29:29] Generate software last single request on last request line 29 -RWH */
    ureg32 SOFTLSREQ30:1; /* [30:30] Generate software last single request on last request line 30 -RWH */
    ureg32 SOFTLSREQ31:1; /* [31:31] Generate software last single request on last request line 31 -RWH */
} DMA_SOFTLSREQ_Bits;

/* DMA configuration register */
typedef volatile struct
{
    ureg32 E:1;           /* [0:0] DMA enable -RW */
    ureg32 M1:1;          /* [1:1] AHB Master 1 endianness configuration -RW */
    ureg32 M2:1;          /* [2:2] AHB Master 2 endianness configuration -RW */
    ureg32 reserved_3:29; /* [3:31] Reserved -R*/
} DMA_CONFIG_Bits;

/* DMA safety configuration register */
typedef volatile struct
{
    ureg32 M1RDNEN:2;      /* [0:1] DMA Master1 redundancy check enable  -RW */
    ureg32 M2RDNEN:2;      /* [2:3] DMA Master2 redundancy check enable  -RW */
    ureg32 REGRDNEN:2;     /* [4:5] Register redundancy check enable  -RW */
    ureg32 reserved_6:2;   /* [6:7] Reserved -R */
    ureg32 TSTMPEN:2;      /* [8:9] Time stamp enable -RW */
    ureg32 MRDNSTEA:2;     /* [10:11] Master redundancy error abort transfer -RW */
    ureg32 REGRDNEA:2;     /* [12:13] Register redundancy error abort transfer -RW */
    ureg32 LLICRCEA:2;     /* [14:15] LLI CRC error abort transfer -RW */
    ureg32 M1RDNMSK:2;     /* [16:17] DMA Master1 redundancy check alarm mask -RW */
    ureg32 M2RDNMSK:2;     /* [18:19] DMA Master2 redundancy check alarm mask -RW */
    ureg32 REGRDNMSK:2;    /* [20:21] Register redundancy check alarm mask -RW */
    ureg32 reserved_22:4;  /* [22:25] Reserved -R */
    ureg32 REGPAMSK:2;     /* [26:27] Register privileged access protection error mask -RW */
    ureg32 reserved_28:4;  /* [28:31] Reserved -R */
} DMA_SFCONFIG_Bits;

/* DMA alarm status register */
typedef volatile struct
{
    ureg32 MRDN:1;          /* [0:0] DMA Master redundancy check alarm status -R */
    ureg32 REGRDN:1;        /* [1:1] Register redundancy alarm status -R */
    ureg32 REGACC:1;        /* [2:2] Register safety endinit access protection alarm status -R */
    ureg32 FIFO:1;          /* [3:3] DMA FIFO parity check alarm status -R */
    ureg32 CRC:1;           /* [4:4] CRC check alarm status -R */
    ureg32 reserved_5:27;   /* [5:31] Reserved -R */
} DMA_ALMSTS_Bits;

/* DMA error status register 0 */
typedef volatile struct
{
    ureg32 M1RDNERR:1;      /* [0:0] DMA Master1 redundancy check error status -R */
    ureg32 M2RDNERR:1;      /* [1:1] DMA Master2 redundancy check error status -R */
    ureg32 reserved_2:2;    /* [2:3] Reserved -R */
    ureg32 REGSEERR:1;      /* [4:4] Register safety endinit protection error status -R */
    ureg32 REGPAERR:1;      /* [5:5] Register privileged access protection error status -R */
    ureg32 reserved_6:26;   /* [6:31] Reserved -R */
} DMA_ERRSTS0_Bits;

/* DMA error status register 1 */
typedef volatile struct
{
    ureg32 CHREGERR0:1;  /* [0:0] Register redundancy check error status for channel 0 -R */
    ureg32 CHREGERR1:1;  /* [1:1] Register redundancy check error status for channel 1 -R */
    ureg32 CHREGERR2:1;  /* [2:2] Register redundancy check error status for channel 2 -R */
    ureg32 CHREGERR3:1;  /* [3:3] Register redundancy check error status for channel 3 -R */
    ureg32 CHREGERR4:1;  /* [4:4] Register redundancy check error status for channel 4 -R */
    ureg32 CHREGERR5:1;  /* [5:5] Register redundancy check error status for channel 5 -R */
    ureg32 CHREGERR6:1;  /* [6:6] Register redundancy check error status for channel 6 -R */
    ureg32 CHREGERR7:1;  /* [7:7] Register redundancy check error status for channel 7 -R */
    ureg32 CHREGERR8:1;  /* [8:8] Register redundancy check error status for channel 8 -R */
    ureg32 CHREGERR9:1;  /* [9:9] Register redundancy check error status for channel 9 -R */
    ureg32 CHREGERR10:1; /* [10:10] Register redundancy check error status for channel 10 -R */
    ureg32 CHREGERR11:1; /* [11:11] Register redundancy check error status for channel 11 -R */
    ureg32 CHREGERR12:1; /* [12:12] Register redundancy check error status for channel 12 -R */
    ureg32 CHREGERR13:1; /* [13:13] Register redundancy check error status for channel 13 -R */
    ureg32 CHREGERR14:1; /* [14:14] Register redundancy check error status for channel 14 -R */
    ureg32 CHREGERR15:1; /* [15:15] Register redundancy check error status for channel 15 -R */
    ureg32 CHREGERR16:1; /* [16:16] Register redundancy check error status for channel 16 -R */
    ureg32 CHREGERR17:1; /* [17:17] Register redundancy check error status for channel 17 -R */
    ureg32 CHREGERR18:1; /* [18:18] Register redundancy check error status for channel 18 -R */
    ureg32 CHREGERR19:1; /* [19:19] Register redundancy check error status for channel 19 -R */
    ureg32 CHREGERR20:1; /* [20:20] Register redundancy check error status for channel 20 -R */
    ureg32 CHREGERR21:1; /* [21:21] Register redundancy check error status for channel 21 -R */
    ureg32 CHREGERR22:1; /* [22:22] Register redundancy check error status for channel 22 -R */
    ureg32 CHREGERR23:1; /* [23:23] Register redundancy check error status for channel 23 -R */
    ureg32 CHREGERR24:1; /* [24:24] Register redundancy check error status for channel 24 -R */
    ureg32 CHREGERR25:1; /* [25:25] Register redundancy check error status for channel 25 -R */
    ureg32 CHREGERR26:1; /* [26:26] Register redundancy check error status for channel 26 -R */
    ureg32 CHREGERR27:1; /* [27:27] Register redundancy check error status for channel 27 -R */
    ureg32 CHREGERR28:1; /* [28:28] Register redundancy check error status for channel 28 -R */
    ureg32 CHREGERR29:1; /* [29:29] Register redundancy check error status for channel 29 -R */
    ureg32 CHREGERR30:1; /* [30:30] Register redundancy check error status for channel 30 -R */
    ureg32 CHREGERR31:1; /* [31:31] Register redundancy check error status for channel 31 -R */
} DMA_ERRSTS1_Bits;

/* DMA error status register 2 */
typedef volatile struct
{
    ureg32 CHREGERR32:1;  /* [0:0] Register redundancy check error status for channel 32 -R */
    ureg32 CHREGERR33:1;  /* [1:1] Register redundancy check error status for channel 33 -R */
    ureg32 CHREGERR34:1;  /* [2:2] Register redundancy check error status for channel 34 -R */
    ureg32 CHREGERR35:1;  /* [3:3] Register redundancy check error status for channel 35 -R */
    ureg32 CHREGERR36:1;  /* [4:4] Register redundancy check error status for channel 36 -R */
    ureg32 CHREGERR37:1;  /* [5:5] Register redundancy check error status for channel 37 -R */
    ureg32 CHREGERR38:1;  /* [6:6] Register redundancy check error status for channel 38 -R */
    ureg32 CHREGERR39:1;  /* [7:7] Register redundancy check error status for channel 39 -R */
    ureg32 GLBREGERR:1;   /* [8:8] Global register redundancy check error status -R */
    ureg32 reserved_9:23; /* [9:31] Reserved -R */
} DMA_ERRSTS2_Bits;

/* DMA error status register 3 */
typedef volatile struct
{
    ureg32 CHDCRCERR0:1;  /* [0:0] Data CRC check error status for channel 0 -R */
    ureg32 CHDCRCERR1:1;  /* [1:1] Data CRC check error status for channel 1 -R */
    ureg32 CHDCRCERR2:1;  /* [2:2] Data CRC check error status for channel 2 -R */
    ureg32 CHDCRCERR3:1;  /* [3:3] Data CRC check error status for channel 3 -R */
    ureg32 CHDCRCERR4:1;  /* [4:4] Data CRC check error status for channel 4 -R */
    ureg32 CHDCRCERR5:1;  /* [5:5] Data CRC check error status for channel 5 -R */
    ureg32 CHDCRCERR6:1;  /* [6:6] Data CRC check error status for channel 6 -R */
    ureg32 CHDCRCERR7:1;  /* [7:7] Data CRC check error status for channel 7 -R */
    ureg32 CHDCRCERR8:1;  /* [8:8] Data CRC check error status for channel 8 -R */
    ureg32 CHDCRCERR9:1;  /* [9:9] Data CRC check error status for channel 9 -R */
    ureg32 CHDCRCERR10:1; /* [10:10] Data CRC check error status for channel 10 -R */
    ureg32 CHDCRCERR11:1; /* [11:11] Data CRC check error status for channel 11 -R */
    ureg32 CHDCRCERR12:1; /* [12:12] Data CRC check error status for channel 12 -R */
    ureg32 CHDCRCERR13:1; /* [13:13] Data CRC check error status for channel 13 -R */
    ureg32 CHDCRCERR14:1; /* [14:14] Data CRC check error status for channel 14 -R */
    ureg32 CHDCRCERR15:1; /* [15:15] Data CRC check error status for channel 15 -R */
    ureg32 CHDCRCERR16:1; /* [16:16] Data CRC check error status for channel 16 -R */
    ureg32 CHDCRCERR17:1; /* [17:17] Data CRC check error status for channel 17 -R */
    ureg32 CHDCRCERR18:1; /* [18:18] Data CRC check error status for channel 18 -R */
    ureg32 CHDCRCERR19:1; /* [19:19] Data CRC check error status for channel 19 -R */
    ureg32 CHDCRCERR20:1; /* [20:20] Data CRC check error status for channel 20 -R */
    ureg32 CHDCRCERR21:1; /* [21:21] Data CRC check error status for channel 21 -R */
    ureg32 CHDCRCERR22:1; /* [22:22] Data CRC check error status for channel 22 -R */
    ureg32 CHDCRCERR23:1; /* [23:23] Data CRC check error status for channel 23 -R */
    ureg32 CHDCRCERR24:1; /* [24:24] Data CRC check error status for channel 24 -R */
    ureg32 CHDCRCERR25:1; /* [25:25] Data CRC check error status for channel 25 -R */
    ureg32 CHDCRCERR26:1; /* [26:26] Data CRC check error status for channel 26 -R */
    ureg32 CHDCRCERR27:1; /* [27:27] Data CRC check error status for channel 27 -R */
    ureg32 CHDCRCERR28:1; /* [28:28] Data CRC check error status for channel 28 -R */
    ureg32 CHDCRCERR29:1; /* [29:29] Data CRC check error status for channel 29 -R */
    ureg32 CHDCRCERR30:1; /* [30:30] Data CRC check error status for channel 30 -R */
    ureg32 CHDCRCERR31:1; /* [31:31] Data CRC check error status for channel 31 -R */
} DMA_ERRSTS3_Bits;

/* DMA error status register 4 */
typedef volatile struct
{
    ureg32 CHDCRCERR32:1; /* [0:0] Data CRC check error status for channel 32 -R */
    ureg32 CHDCRCERR33:1; /* [1:1] Data CRC check error status for channel 33 -R */
    ureg32 CHDCRCERR34:1; /* [2:2] Data CRC check error status for channel 34 -R */
    ureg32 CHDCRCERR35:1; /* [3:3] Data CRC check error status for channel 35 -R */
    ureg32 CHDCRCERR36:1; /* [4:4] Data CRC check error status for channel 36 -R */
    ureg32 CHDCRCERR37:1; /* [5:5] Data CRC check error status for channel 37 -R */
    ureg32 CHDCRCERR38:1; /* [6:6] Data CRC check error status for channel 38 -R */
    ureg32 CHDCRCERR39:1; /* [7:7] Data CRC check error status for channel 39 -R */
    ureg32 CHDCRCERR40:1; /* [8:8] Data CRC check error status for channel 40 -R */
    ureg32 CHDCRCERR41:1; /* [9:9] Data CRC check error status for channel 41 -R */
    ureg32 CHDCRCERR42:1; /* [10:10] Data CRC check error status for channel 42 -R */
    ureg32 CHDCRCERR43:1; /* [11:11] Data CRC check error status for channel 43 -R */
    ureg32 CHDCRCERR44:1; /* [12:12] Data CRC check error status for channel 44 -R */
    ureg32 CHDCRCERR45:1; /* [13:13] Data CRC check error status for channel 45 -R */
    ureg32 CHDCRCERR46:1; /* [14:14] Data CRC check error status for channel 46 -R */
    ureg32 CHDCRCERR47:1; /* [15:15] Data CRC check error status for channel 47 -R */
    ureg32 CHDCRCERR48:1; /* [16:16] Data CRC check error status for channel 48 -R */
    ureg32 CHDCRCERR49:1; /* [17:17] Data CRC check error status for channel 49 -R */
    ureg32 CHDCRCERR50:1; /* [18:18] Data CRC check error status for channel 50 -R */
    ureg32 CHDCRCERR51:1; /* [19:19] Data CRC check error status for channel 51 -R */
    ureg32 CHDCRCERR52:1; /* [20:20] Data CRC check error status for channel 52 -R */
    ureg32 CHDCRCERR53:1; /* [21:21] Data CRC check error status for channel 53 -R */
    ureg32 CHDCRCERR54:1; /* [22:22] Data CRC check error status for channel 54 -R */
    ureg32 CHDCRCERR55:1; /* [23:23] Data CRC check error status for channel 55 -R */
    ureg32 CHDCRCERR56:1; /* [24:24] Data CRC check error status for channel 56 -R */
    ureg32 CHDCRCERR57:1; /* [25:25] Data CRC check error status for channel 57 -R */
    ureg32 CHDCRCERR58:1; /* [26:26] Data CRC check error status for channel 58 -R */
    ureg32 CHDCRCERR59:1; /* [27:27] Data CRC check error status for channel 59 -R */
    ureg32 CHDCRCERR60:1; /* [28:28] Data CRC check error status for channel 60 -R */
    ureg32 CHDCRCERR61:1; /* [29:29] Data CRC check error status for channel 61 -R */
    ureg32 CHDCRCERR62:1; /* [30:30] Data CRC check error status for channel 62 -R */
    ureg32 CHDCRCERR63:1; /* [31:31] Data CRC check error status for channel 63 -R */
} DMA_ERRSTS4_Bits;

/* DMA error status register 5 */
typedef volatile struct
{
    ureg32 CHLCRCERR0:1;  /* [0:0] LLI CRC error status for channel 0 -R */
    ureg32 CHLCRCERR1:1;  /* [1:1] LLI CRC error status for channel 1 -R */
    ureg32 CHLCRCERR2:1;  /* [2:2] LLI CRC error status for channel 2 -R */
    ureg32 CHLCRCERR3:1;  /* [3:3] LLI CRC error status for channel 3 -R */
    ureg32 CHLCRCERR4:1;  /* [4:4] LLI CRC error status for channel 4 -R */
    ureg32 CHLCRCERR5:1;  /* [5:5] LLI CRC error status for channel 5 -R */
    ureg32 CHLCRCERR6:1;  /* [6:6] LLI CRC error status for channel 6 -R */
    ureg32 CHLCRCERR7:1;  /* [7:7] LLI CRC error status for channel 7 -R */
    ureg32 CHLCRCERR8:1;  /* [0:0] LLI CRC error status for channel 8 -R */
    ureg32 CHLCRCERR9:1;  /* [1:1] LLI CRC error status for channel 9 -R */
    ureg32 CHLCRCERR10:1; /* [2:2] LLI CRC error status for channel 10 -R */
    ureg32 CHLCRCERR11:1; /* [3:3] LLI CRC error status for channel 11 -R */
    ureg32 CHLCRCERR12:1; /* [4:4] LLI CRC error status for channel 12 -R */
    ureg32 CHLCRCERR13:1; /* [5:5] LLI CRC error status for channel 13 -R */
    ureg32 CHLCRCERR14:1; /* [6:6] LLI CRC error status for channel 14 -R */
    ureg32 CHLCRCERR15:1; /* [7:7] LLI CRC error status for channel 15 -R */
    ureg32 CHLCRCERR16:1; /* [8:8] LLI CRC error status for channel 16 -R */
    ureg32 CHLCRCERR17:1; /* [9:9] LLI CRC error status for channel 17 -R */
    ureg32 CHLCRCERR18:1; /* [10:10] LLI CRC error status for channel 18 -R */
    ureg32 CHLCRCERR19:1; /* [11:11] LLI CRC error status for channel 19 -R */
    ureg32 CHLCRCERR20:1; /* [12:12] LLI CRC error status for channel 20 -R */
    ureg32 CHLCRCERR21:1; /* [13:13] LLI CRC error status for channel 21 -R */
    ureg32 CHLCRCERR22:1; /* [14:14] LLI CRC error status for channel 22 -R */
    ureg32 CHLCRCERR23:1; /* [15:15] LLI CRC error status for channel 23 -R */
    ureg32 CHLCRCERR24:1; /* [16:16] LLI CRC error status for channel 24 -R */
    ureg32 CHLCRCERR25:1; /* [17:17] LLI CRC error status for channel 25 -R */
    ureg32 CHLCRCERR26:1; /* [18:18] LLI CRC error status for channel 26 -R */
    ureg32 CHLCRCERR27:1; /* [19:19] LLI CRC error status for channel 27 -R */
    ureg32 CHLCRCERR28:1; /* [20:20] LLI CRC error status for channel 28 -R */
    ureg32 CHLCRCERR29:1; /* [21:21] LLI CRC error status for channel 29 -R */
    ureg32 CHLCRCERR30:1; /* [22:22] LLI CRC error status for channel 30 -R */
    ureg32 CHLCRCERR31:1; /* [23:23] LLI CRC error status for channel 31 -R */
} DMA_ERRSTS5_Bits;

/* DMA error status register 6 */
typedef volatile struct
{
    ureg32 CHLCRCERR32:1; /* [0:0] LLI CRC check error status for channel 32 -R */
    ureg32 CHLCRCERR33:1; /* [1:1] LLI CRC check error status for channel 33 -R */
    ureg32 CHLCRCERR34:1; /* [2:2] LLI CRC check error status for channel 34 -R */
    ureg32 CHLCRCERR35:1; /* [3:3] LLI CRC check error status for channel 35 -R */
    ureg32 CHLCRCERR36:1; /* [4:4] LLI CRC check error status for channel 36 -R */
    ureg32 CHLCRCERR37:1; /* [5:5] LLI CRC check error status for channel 37 -R */
    ureg32 CHLCRCERR38:1; /* [6:6] LLI CRC check error status for channel 38 -R */
    ureg32 CHLCRCERR39:1; /* [7:7] LLI CRC check error status for channel 39 -R */
    ureg32 CHLCRCERR40:1; /* [8:8] LLI CRC check error status for channel 40 -R */
    ureg32 CHLCRCERR41:1; /* [9:9] LLI CRC check error status for channel 41 -R */
    ureg32 CHLCRCERR42:1; /* [10:10] LLI CRC check error status for channel 42 -R */
    ureg32 CHLCRCERR43:1; /* [11:11] LLI CRC check error status for channel 43 -R */
    ureg32 CHLCRCERR44:1; /* [12:12] LLI CRC check error status for channel 44 -R */
    ureg32 CHLCRCERR45:1; /* [13:13] LLI CRC check error status for channel 45 -R */
    ureg32 CHLCRCERR46:1; /* [14:14] LLI CRC check error status for channel 46 -R */
    ureg32 CHLCRCERR47:1; /* [15:15] LLI CRC check error status for channel 47 -R */
    ureg32 CHLCRCERR48:1; /* [16:16] LLI CRC check error status for channel 48 -R */
    ureg32 CHLCRCERR49:1; /* [17:17] LLI CRC check error status for channel 49 -R */
    ureg32 CHLCRCERR50:1; /* [18:18] LLI CRC check error status for channel 50 -R */
    ureg32 CHLCRCERR51:1; /* [19:19] LLI CRC check error status for channel 51 -R */
    ureg32 CHLCRCERR52:1; /* [20:20] LLI CRC check error status for channel 52 -R */
    ureg32 CHLCRCERR53:1; /* [21:21] LLI CRC check error status for channel 53 -R */
    ureg32 CHLCRCERR54:1; /* [22:22] LLI CRC check error status for channel 54 -R */
    ureg32 CHLCRCERR55:1; /* [23:23] LLI CRC check error status for channel 55 -R */
    ureg32 CHLCRCERR56:1; /* [24:24] LLI CRC check error status for channel 56 -R */
    ureg32 CHLCRCERR57:1; /* [25:25] LLI CRC check error status for channel 57 -R */
    ureg32 CHLCRCERR58:1; /* [26:26] LLI CRC check error status for channel 58 -R */
    ureg32 CHLCRCERR59:1; /* [27:27] LLI CRC check error status for channel 59 -R */
    ureg32 CHLCRCERR60:1; /* [28:28] LLI CRC check error status for channel 60 -R */
    ureg32 CHLCRCERR61:1; /* [29:29] LLI CRC check error status for channel 61 -R */
    ureg32 CHLCRCERR62:1; /* [30:30] LLI CRC check error status for channel 62 -R */
    ureg32 CHLCRCERR63:1; /* [31:31] LLI CRC check error status for channel 63 -R */
} DMA_ERRSTS6_Bits;

/* DMA error status register 7 */
typedef volatile struct
{
    ureg32 CHLCRCERR40:1; /* [0:0] LLI CRC check error status for channel 40 -R */
    ureg32 CHLCRCERR41:1; /* [1:1] LLI CRC check error status for channel 41 -R */
    ureg32 CHLCRCERR42:1; /* [2:2] LLI CRC check error status for channel 42 -R */
    ureg32 CHLCRCERR43:1; /* [3:3] LLI CRC check error status for channel 43 -R */
    ureg32 CHLCRCERR44:1; /* [4:4] LLI CRC check error status for channel 44 -R */
    ureg32 CHLCRCERR45:1; /* [5:5] LLI CRC check error status for channel 45 -R */
    ureg32 CHLCRCERR46:1; /* [6:6] LLI CRC check error status for channel 46 -R */
    ureg32 CHLCRCERR47:1; /* [7:7] LLI CRC check error status for channel 47 -R */
    ureg32 CHLCRCERR48:1; /* [8:8] LLI CRC check error status for channel 48 -R */
    ureg32 CHLCRCERR49:1; /* [9:9] LLI CRC check error status for channel 49 -R */
    ureg32 CHLCRCERR50:1; /* [10:10] LLI CRC check error status for channel 50 -R */
    ureg32 CHLCRCERR51:1; /* [11:11] LLI CRC check error status for channel 51 -R */
    ureg32 CHLCRCERR52:1; /* [12:12] LLI CRC check error status for channel 52 -R */
    ureg32 CHLCRCERR53:1; /* [13:13] LLI CRC check error status for channel 53 -R */
    ureg32 CHLCRCERR54:1; /* [14:14] LLI CRC check error status for channel 54 -R */
    ureg32 CHLCRCERR55:1; /* [15:15] LLI CRC check error status for channel 55 -R */
    ureg32 CHLCRCERR56:1; /* [16:16] LLI CRC check error status for channel 56 -R */
    ureg32 CHLCRCERR57:1; /* [17:17] LLI CRC check error status for channel 57 -R */
    ureg32 CHLCRCERR58:1; /* [18:18] LLI CRC check error status for channel 58 -R */
    ureg32 CHLCRCERR59:1; /* [19:19] LLI CRC check error status for channel 59 -R */
    ureg32 CHLCRCERR60:1; /* [20:20] LLI CRC check error status for channel 60 -R */
    ureg32 CHLCRCERR61:1; /* [21:21] LLI CRC check error status for channel 61 -R */
    ureg32 CHLCRCERR62:1; /* [22:22] LLI CRC check error status for channel 62 -R */
    ureg32 CHLCRCERR63:1; /* [23:23] LLI CRC check error status for channel 63 -R */
    ureg32 reserved_24:8; /* [24:31] Reserved -R */
} DMA_ERRSTS7_Bits;

/* DMA error status register 8 */
typedef volatile struct
{
    ureg32 CHFIFOERR0:1;  /* [0:0] FIFO ECC Single Bit Check error status for channel 0 -R */
    ureg32 CHFIFOERR1:1;  /* [1:1] FIFO ECC Single Bit Check error status for channel 1 -R */
    ureg32 CHFIFOERR2:1;  /* [2:2] FIFO ECC Single Bit Check error status for channel 2 -R */
    ureg32 CHFIFOERR3:1;  /* [3:3] FIFO ECC Single Bit Check error status for channel 3 -R */
    ureg32 CHFIFOERR4:1;  /* [4:4] FIFO ECC Single Bit Check error status for channel 4 -R */
    ureg32 CHFIFOERR5:1;  /* [5:5] FIFO ECC Single Bit Check error status for channel 5 -R */
    ureg32 CHFIFOERR6:1;  /* [6:6] FIFO ECC Single Bit Check error status for channel 6 -R */
    ureg32 CHFIFOERR7:1;  /* [7:7] FIFO ECC Single Bit Check error status for channel 7 -R */
    ureg32 CHFIFOERR8:1;  /* [0:0] FIFO ECC Single Bit Check error status for channel 8 -R */
    ureg32 CHFIFOERR9:1;  /* [1:1] FIFO ECC Single Bit Check error status for channel 9 -R */
    ureg32 CHFIFOERR10:1; /* [2:2] FIFO ECC Single Bit Check error status for channel 10 -R */
    ureg32 CHFIFOERR11:1; /* [3:3] FIFO ECC Single Bit Check error status for channel 11 -R */
    ureg32 CHFIFOERR12:1; /* [4:4] FIFO ECC Single Bit Check error status for channel 12 -R */
    ureg32 CHFIFOERR13:1; /* [5:5] FIFO ECC Single Bit Check error status for channel 13 -R */
    ureg32 CHFIFOERR14:1; /* [6:6] FIFO ECC Single Bit Check error status for channel 14 -R */
    ureg32 CHFIFOERR15:1; /* [7:7] FIFO ECC Single Bit Check error status for channel 15 -R */
    ureg32 CHFIFOERR16:1; /* [8:8] FIFO ECC Single Bit Check error status for channel 16 -R */
    ureg32 CHFIFOERR17:1; /* [9:9] FIFO ECC Single Bit Check error status for channel 17 -R */
    ureg32 CHFIFOERR18:1; /* [10:10] FIFO ECC Single Bit Check error status for channel 18 -R */
    ureg32 CHFIFOERR19:1; /* [11:11] FIFO ECC Single Bit Check error status for channel 19 -R */
    ureg32 CHFIFOERR20:1; /* [12:12] FIFO ECC Single Bit Check error status for channel 20 -R */
    ureg32 CHFIFOERR21:1; /* [13:13] FIFO ECC Single Bit Check error status for channel 21 -R */
    ureg32 CHFIFOERR22:1; /* [14:14] FIFO ECC Single Bit Check error status for channel 22 -R */
    ureg32 CHFIFOERR23:1; /* [15:15] FIFO ECC Single Bit Check error status for channel 23 -R */
    ureg32 CHFIFOERR24:1; /* [16:16] FIFO ECC Single Bit Check error status for channel 24 -R */
    ureg32 CHFIFOERR25:1; /* [17:17] FIFO ECC Single Bit Check error status for channel 25 -R */
    ureg32 CHFIFOERR26:1; /* [18:18] FIFO ECC Single Bit Check error status for channel 26 -R */
    ureg32 CHFIFOERR27:1; /* [19:19] FIFO ECC Single Bit Check error status for channel 27 -R */
    ureg32 CHFIFOERR28:1; /* [20:20] FIFO ECC Single Bit Check error status for channel 28 -R */
    ureg32 CHFIFOERR29:1; /* [21:21] FIFO ECC Single Bit Check error status for channel 29 -R */
    ureg32 CHFIFOERR30:1; /* [22:22] FIFO ECC Single Bit Check error status for channel 30 -R */
    ureg32 CHFIFOERR31:1; /* [23:23] FIFO ECC Single Bit Check error status for channel 31 -R */
} DMA_ERRSTS8_Bits;

/* DMA error status register 9 */
typedef volatile struct
{
    ureg32 CHFIFOERR32:1; /* [0:0] FIFO ECC Single Bit Check check error status for channel 32 -R */
    ureg32 CHFIFOERR33:1; /* [1:1] FIFO ECC Single Bit Check check error status for channel 33 -R */
    ureg32 CHFIFOERR34:1; /* [2:2] FIFO ECC Single Bit Check check error status for channel 34 -R */
    ureg32 CHFIFOERR35:1; /* [3:3] FIFO ECC Single Bit Check check error status for channel 35 -R */
    ureg32 CHFIFOERR36:1; /* [4:4] FIFO ECC Single Bit Check check error status for channel 36 -R */
    ureg32 CHFIFOERR37:1; /* [5:5] FIFO ECC Single Bit Check check error status for channel 37 -R */
    ureg32 CHFIFOERR38:1; /* [6:6] FIFO ECC Single Bit Check check error status for channel 38 -R */
    ureg32 CHFIFOERR39:1; /* [7:7] FIFO ECC Single Bit Check check error status for channel 39 -R */
    ureg32 CHFIFOERR40:1; /* [8:8] FIFO ECC Single Bit Check check error status for channel 40 -R */
    ureg32 CHFIFOERR41:1; /* [9:9] FIFO ECC Single Bit Check check error status for channel 41 -R */
    ureg32 CHFIFOERR42:1; /* [10:10] FIFO ECC Single Bit Check check error status for channel 42 -R */
    ureg32 CHFIFOERR43:1; /* [11:11] FIFO ECC Single Bit Check check error status for channel 43 -R */
    ureg32 CHFIFOERR44:1; /* [12:12] FIFO ECC Single Bit Check check error status for channel 44 -R */
    ureg32 CHFIFOERR45:1; /* [13:13] FIFO ECC Single Bit Check check error status for channel 45 -R */
    ureg32 CHFIFOERR46:1; /* [14:14] FIFO ECC Single Bit Check check error status for channel 46 -R */
    ureg32 CHFIFOERR47:1; /* [15:15] FIFO ECC Single Bit Check check error status for channel 47 -R */
    ureg32 CHFIFOERR48:1; /* [16:16] FIFO ECC Single Bit Check check error status for channel 48 -R */
    ureg32 CHFIFOERR49:1; /* [17:17] FIFO ECC Single Bit Check check error status for channel 49 -R */
    ureg32 CHFIFOERR50:1; /* [18:18] FIFO ECC Single Bit Check check error status for channel 50 -R */
    ureg32 CHFIFOERR51:1; /* [19:19] FIFO ECC Single Bit Check check error status for channel 51 -R */
    ureg32 CHFIFOERR52:1; /* [20:20] FIFO ECC Single Bit Check check error status for channel 52 -R */
    ureg32 CHFIFOERR53:1; /* [21:21] FIFO ECC Single Bit Check check error status for channel 53 -R */
    ureg32 CHFIFOERR54:1; /* [22:22] FIFO ECC Single Bit Check check error status for channel 54 -R */
    ureg32 CHFIFOERR55:1; /* [23:23] FIFO ECC Single Bit Check check error status for channel 55 -R */
    ureg32 CHFIFOERR56:1; /* [24:24] FIFO ECC Single Bit Check check error status for channel 56 -R */
    ureg32 CHFIFOERR57:1; /* [25:25] FIFO ECC Single Bit Check check error status for channel 57 -R */
    ureg32 CHFIFOERR58:1; /* [26:26] FIFO ECC Single Bit Check check error status for channel 58 -R */
    ureg32 CHFIFOERR59:1; /* [27:27] FIFO ECC Single Bit Check check error status for channel 59 -R */
    ureg32 CHFIFOERR60:1; /* [28:28] FIFO ECC Single Bit Check check error status for channel 60 -R */
    ureg32 CHFIFOERR61:1; /* [29:29] FIFO ECC Single Bit Check check error status for channel 61 -R */
    ureg32 CHFIFOERR62:1; /* [30:30] FIFO ECC Single Bit Check check error status for channel 62 -R */
    ureg32 CHFIFOERR63:1; /* [31:31] FIFO ECC Single Bit Check check error status for channel 63 -R */
} DMA_ERRSTS9_Bits;

/* DMA error status register 10 */
typedef volatile struct
{
    ureg32 CHFIFODERR0:1;  /* [0:0] FIFO ECC Double Bit Check error status for channel 0 -R */
    ureg32 CHFIFODERR1:1;  /* [1:1] FIFO ECC Double Bit Check error status for channel 1 -R */
    ureg32 CHFIFODERR2:1;  /* [2:2] FIFO ECC Double Bit Check error status for channel 2 -R */
    ureg32 CHFIFODERR3:1;  /* [3:3] FIFO ECC Double Bit Check error status for channel 3 -R */
    ureg32 CHFIFODERR4:1;  /* [4:4] FIFO ECC Double Bit Check error status for channel 4 -R */
    ureg32 CHFIFODERR5:1;  /* [5:5] FIFO ECC Double Bit Check error status for channel 5 -R */
    ureg32 CHFIFODERR6:1;  /* [6:6] FIFO ECC Double Bit Check error status for channel 6 -R */
    ureg32 CHFIFODERR7:1;  /* [7:7] FIFO ECC Double Bit Check error status for channel 7 -R */
    ureg32 CHFIFODERR8:1;  /* [0:0] FIFO ECC Double Bit Check error status for channel 8 -R */
    ureg32 CHFIFODERR9:1;  /* [1:1] FIFO ECC Double Bit Check error status for channel 9 -R */
    ureg32 CHFIFODERR10:1; /* [2:2] FIFO ECC Double Bit Check error status for channel 10 -R */
    ureg32 CHFIFODERR11:1; /* [3:3] FIFO ECC Double Bit Check error status for channel 11 -R */
    ureg32 CHFIFODERR12:1; /* [4:4] FIFO ECC Double Bit Check error status for channel 12 -R */
    ureg32 CHFIFODERR13:1; /* [5:5] FIFO ECC Double Bit Check error status for channel 13 -R */
    ureg32 CHFIFODERR14:1; /* [6:6] FIFO ECC Double Bit Check error status for channel 14 -R */
    ureg32 CHFIFODERR15:1; /* [7:7] FIFO ECC Double Bit Check error status for channel 15 -R */
    ureg32 CHFIFODERR16:1; /* [8:8] FIFO ECC Double Bit Check error status for channel 16 -R */
    ureg32 CHFIFODERR17:1; /* [9:9] FIFO ECC Double Bit Check error status for channel 17 -R */
    ureg32 CHFIFODERR18:1; /* [10:10] FIFO ECC Double Bit Check error status for channel 18 -R */
    ureg32 CHFIFODERR19:1; /* [11:11] FIFO ECC Double Bit Check error status for channel 19 -R */
    ureg32 CHFIFODERR20:1; /* [12:12] FIFO ECC Double Bit Check error status for channel 20 -R */
    ureg32 CHFIFODERR21:1; /* [13:13] FIFO ECC Double Bit Check error status for channel 21 -R */
    ureg32 CHFIFODERR22:1; /* [14:14] FIFO ECC Double Bit Check error status for channel 22 -R */
    ureg32 CHFIFODERR23:1; /* [15:15] FIFO ECC Double Bit Check error status for channel 23 -R */
    ureg32 CHFIFODERR24:1; /* [16:16] FIFO ECC Double Bit Check error status for channel 24 -R */
    ureg32 CHFIFODERR25:1; /* [17:17] FIFO ECC Double Bit Check error status for channel 25 -R */
    ureg32 CHFIFODERR26:1; /* [18:18] FIFO ECC Double Bit Check error status for channel 26 -R */
    ureg32 CHFIFODERR27:1; /* [19:19] FIFO ECC Double Bit Check error status for channel 27 -R */
    ureg32 CHFIFODERR28:1; /* [20:20] FIFO ECC Double Bit Check error status for channel 28 -R */
    ureg32 CHFIFODERR29:1; /* [21:21] FIFO ECC Double Bit Check error status for channel 29 -R */
    ureg32 CHFIFODERR30:1; /* [22:22] FIFO ECC Double Bit Check error status for channel 30 -R */
    ureg32 CHFIFODERR31:1; /* [23:23] FIFO ECC Double Bit Check error status for channel 31 -R */
} DMA_ERRSTS10_Bits;

/* DMA error status register 11 */
typedef volatile struct
{
    ureg32 CHFIFODERR32:1; /* [0:0] FIFO ECC Double Bit Check check error status for channel 32 -R */
    ureg32 CHFIFODERR33:1; /* [1:1] FIFO ECC Double Bit Check check error status for channel 33 -R */
    ureg32 CHFIFODERR34:1; /* [2:2] FIFO ECC Double Bit Check check error status for channel 34 -R */
    ureg32 CHFIFODERR35:1; /* [3:3] FIFO ECC Double Bit Check check error status for channel 35 -R */
    ureg32 CHFIFODERR36:1; /* [4:4] FIFO ECC Double Bit Check check error status for channel 36 -R */
    ureg32 CHFIFODERR37:1; /* [5:5] FIFO ECC Double Bit Check check error status for channel 37 -R */
    ureg32 CHFIFODERR38:1; /* [6:6] FIFO ECC Double Bit Check check error status for channel 38 -R */
    ureg32 CHFIFODERR39:1; /* [7:7] FIFO ECC Double Bit Check check error status for channel 39 -R */
    ureg32 CHFIFODERR40:1; /* [8:8] FIFO ECC Double Bit Check check error status for channel 40 -R */
    ureg32 CHFIFODERR41:1; /* [9:9] FIFO ECC Double Bit Check check error status for channel 41 -R */
    ureg32 CHFIFODERR42:1; /* [10:10] FIFO ECC Double Bit Check check error status for channel 42 -R */
    ureg32 CHFIFODERR43:1; /* [11:11] FIFO ECC Double Bit Check check error status for channel 43 -R */
    ureg32 CHFIFODERR44:1; /* [12:12] FIFO ECC Double Bit Check check error status for channel 44 -R */
    ureg32 CHFIFODERR45:1; /* [13:13] FIFO ECC Double Bit Check check error status for channel 45 -R */
    ureg32 CHFIFODERR46:1; /* [14:14] FIFO ECC Double Bit Check check error status for channel 46 -R */
    ureg32 CHFIFODERR47:1; /* [15:15] FIFO ECC Double Bit Check check error status for channel 47 -R */
    ureg32 CHFIFODERR48:1; /* [16:16] FIFO ECC Double Bit Check check error status for channel 48 -R */
    ureg32 CHFIFODERR49:1; /* [17:17] FIFO ECC Double Bit Check check error status for channel 49 -R */
    ureg32 CHFIFODERR50:1; /* [18:18] FIFO ECC Double Bit Check check error status for channel 50 -R */
    ureg32 CHFIFODERR51:1; /* [19:19] FIFO ECC Double Bit Check check error status for channel 51 -R */
    ureg32 CHFIFODERR52:1; /* [20:20] FIFO ECC Double Bit Check check error status for channel 52 -R */
    ureg32 CHFIFODERR53:1; /* [21:21] FIFO ECC Double Bit Check check error status for channel 53 -R */
    ureg32 CHFIFODERR54:1; /* [22:22] FIFO ECC Double Bit Check check error status for channel 54 -R */
    ureg32 CHFIFODERR55:1; /* [23:23] FIFO ECC Double Bit Check check error status for channel 55 -R */
    ureg32 CHFIFODERR56:1; /* [24:24] FIFO ECC Double Bit Check check error status for channel 56 -R */
    ureg32 CHFIFODERR57:1; /* [25:25] FIFO ECC Double Bit Check check error status for channel 57 -R */
    ureg32 CHFIFODERR58:1; /* [26:26] FIFO ECC Double Bit Check check error status for channel 58 -R */
    ureg32 CHFIFODERR59:1; /* [27:27] FIFO ECC Double Bit Check check error status for channel 59 -R */
    ureg32 CHFIFODERR60:1; /* [28:28] FIFO ECC Double Bit Check check error status for channel 60 -R */
    ureg32 CHFIFODERR61:1; /* [29:29] FIFO ECC Double Bit Check check error status for channel 61 -R */
    ureg32 CHFIFODERR62:1; /* [30:30] FIFO ECC Double Bit Check check error status for channel 62 -R */
    ureg32 CHFIFODERR63:1; /* [31:31] FIFO ECC Double Bit Check check error status for channel 63 -R */
} DMA_ERRSTS11_Bits;

/* DMA error clear register 0 */
typedef volatile struct
{
    ureg32 M1RDNECLR:1;        /* [0:0] DMA master1 redundancy check error clear -W */
    ureg32 M2RDNECLR:1;        /* [1:2] DMA master2 redundancy check error clear -W */
    ureg32 reserved_2:2;       /* [2:3] Reserved -R */
    ureg32 REGSEECLR:1;        /* [4:4] Register safety endinit protection error clear -W */
    ureg32 REGPAECLR:1;        /* [5:5] Register privileged access protection error clear -W */
    ureg32 reserved_6:26;      /* [6:31] Reserved -R */
} DMA_ERRCLR0_Bits;

/* DMA error clear register 0 */
typedef volatile struct
{
    ureg32 reserved_0:8;       /* [0:7] Reserved -R */
    ureg32 GLBREGECLR:1;       /* [8:8] Global register redundancy check error clear -W */
    ureg32 reserved_9:23;      /* [9:31] Reserved -R */
} DMA_ERRCLR2_Bits;


/* DMA error injection register */
typedef volatile struct
{
    ureg32 M1RDNEINJ:2;        /* [0:1] DMA Master1 Redundancy Check Error Injection -RW */
    ureg32 M2RDNEINJ:2;        /* [2:3] DMA Master2 Redundancy Check Error Injection -RW */
    ureg32 reserved_4:12;      /* [4:15] Reserved -R */
    ureg32 CRCINJ:2;           /* [16:17] DMA CRC Error Injection -RW */
    ureg32 reserved_18:14;     /* [18:31] Reserved -R */
} DMA_ERRINJ_Bits;

/* DMA error injection register 1 */
typedef volatile struct
{
    ureg32 FIFOEINJ:2;         /* [0:1] DMA FIFO Single Bit Error Injection -RW */
    ureg32 REGPEINJ:2;         /* [2:3] DMA Register Parity Error Injection -RW */
    ureg32 FIFODEINJ:2;        /* [4:5] DMA FIFO Double Bit Error Injection -RW, THA6104 is supported,
                               but THA6206 and THA6412 are not supported */
    ureg32 reserved_6:26;      /* [6:31] Reserved -R */
} DMA_ERRINJ1_Bits;

/* DMA internal timer clock divider configuration register */
typedef volatile struct
{
    ureg32 DIV:8;        /* [0:7] Timer clock divider configuration -RW */
    ureg32 CKG:1;        /* [8:8] Timer clock gating -RW */
    ureg32 reserved_9:23; /* [9:31] Reserved -R */
} DMA_ITIMERDIV_Bits;

/* DMA internal timer value register */
typedef volatile struct
{
    ureg32 SRCADDR:32; /* [0:32] DMA Timer clock value -RW */
} DMA_ITIMERVAL_Bits;

/* DMA global request select register */
typedef volatile struct
{
    ureg32 REQMUX:9;      /* [0:8] Global request select -RW */
    ureg32 reserved_9:23; /* [9:31] Reserved -R */
} DMA_REQMUX_Bits;

/* DMA channel source address register */
typedef volatile struct
{
    ureg32 SRCADDR:32; /* [0:32] DMA source address -RW */
} DMA_CH_SRCADDR_Bits;

/* DMA channel destination address register */
typedef volatile struct
{
    ureg32 DESTADDR:32; /* [0:32] DMA destination address -RW */
} DMA_CH_DESTADDR_Bits;

/* DMA linked list item register */
typedef volatile struct
{
    ureg32 LM:1;         /* [0:0] DMA AHB Master select for loading the next LLI -RW */
    ureg32 reserved_1:1; /* [1:1] Reserved -R */
    ureg32 LLI:30;       /* [2:32] DMA Linked list item -RW */
} DMA_CH_LLIREGBits;

/* DMA channel control register */
typedef volatile struct
{
    ureg32 TRANSIZE:12; /* [0:11] Transfer size -RW */
    ureg32 SBSIZE:3;    /* [12:14] Source burst size -RW */
    ureg32 DBSIZE:3;    /* [15:17] Destination burst size -RW */
    ureg32 SWIDTH:3;    /* [18:20] Source transfer width -RW */
    ureg32 DWIDTH:3;    /* [21:23] Destination transfer width -RW */
    ureg32 S:1;         /* [24:24] Source AHB master select -RW */
    ureg32 D:1;         /* [25:25] Destination AHB master select -RW */
    ureg32 SI:1;        /* [26:26] Source increment -RW */
    ureg32 DI:1;        /* [27:27] Destination increment -RW */
    ureg32 AM:1;        /* [28:28] AHB access mode -RW */
    ureg32 BE:1;        /* [29:29] AHB bufferable -RW */
    ureg32 CE:1;        /* [30:30] AHB cacheable -RW */
    ureg32 I:1;         /* [31:31] Terminal count interrupt enable bit -RW */
} DMA_CH_CONTROL_Bits;

/* DMA channel configuration register */
typedef volatile struct
{
    ureg32 E:1;           /* [0:0] Channel enable -RW */
    ureg32 reserved_1:3;  /* [1:3] Reserved -R */
    ureg32 FLOWCTR:3;     /* [4:6] Flow control and transfer type -RW */
    ureg32 reserved_7:1;  /* [7:7] Reserved -R */
    ureg32 IE:1;          /* [8:8] Interrupt error mask -RW */
    ureg32 ITC:1;         /* [9:9] Terminal count interrupt mask -RW */
    ureg32 TC:1;          /* [10:10] Terminal count signal mask -RW */
    ureg32 reserved_11:1; /* [11:11] Reserved -R */
    ureg32 L:1;           /* [12:12] Lock arbiter (THA6206 is not supported,
                                     but THA6104 and THA6412 are supported) -RW */
    ureg32 A:1;           /* [13:13] Channel active status -R */
    ureg32 H:1;           /* [14:14] Halt (THA6206 only) -R */
    ureg32 reserved_15:1; /* [15:15] Reserved -R */
    ureg32 SRCPERH:8;     /* [16:23] Source peripheral request select -RW */
    ureg32 DESTPERH:8;    /* [24:31] Destination peripheral request select -RW */
} DMA_CH_CONFIG_Bits;

/* DMA channel advance configuration register */
typedef volatile struct
{
    ureg32 INTDCBMSK:1;   /* [0:0] Interrupt destination circular buffer mask -RW */
    ureg32 INTSCBMSK:1;   /* [1:1] Interrupt source circular buffer mask -RW */
    ureg32 INTDCB:1;      /* [2:2] Interrupt destination circular buffer enable -RW */
    ureg32 INTSCB:1;      /* [3:3] Interrupt source circular buffer enable -RW */
    ureg32 DCBSIZE:4;     /* [4:7] Destination circular buffer size -RW */
    ureg32 SCBSIZE:4;     /* [8:11] Source circular buffer size -RW */
    ureg32 DCBEN:1;       /* [12:12] Destination circular buffer enable -RW */
    ureg32 SCBEN:1;       /* [13:13] Source circular buffer enable -RW */
    ureg32 DCBWIC:1;      /* [14:14] Destination circular buffer wait for interrupt clear -RW */
    ureg32 reserved_15:1; /* [15:15] Reserved -R */
    ureg32 DBMODE:3;      /* [16:18] Double buffering mode select -RW */
    ureg32 reserved_19:1; /* [19:19] Reserved -R */
    ureg32 CMODEN:1;      /* [20:20] Continue mode enable -RW */
    ureg32 reserved_21:3; /* [21:23] Reserved -R */
    ureg32 DAISYEN:1;     /* [24:24] Daisy chain enable -RW */
    ureg32 reserved_25:3; /* [25:27] Reserved -R */
    ureg32 reserved_28:1; /* [28:28] Reserved, This bit must be kept at the default value of 0,
                                     otherwise unknown errors may occur. -RW */
    ureg32 reserved_29:3; /* [29:31] Reserved -R */
} DMA_CH_ADVCONFIG_Bits;

/* DMA channel data match pattern configuration register */
typedef volatile struct
{
    ureg32 INTPATMSK:1;    /* [0:0] Interrupt pattern matched mask -RW */
    ureg32 INTPATEN:1;     /* [1:1] Interrupt pattern matched enable -RW */
    ureg32 reserved_2:6;   /* [2:7] Reserved -R */
    ureg32 PATSTOP:1;      /* [8:8] Transfer stop when pattern matched -RW */
    ureg32 reserved_9:7;   /* [9:15] Reserved -R */
    ureg32 SIZE:2;         /* [16:17] Pattern size -RW */
    ureg32 reserved_18:14; /* [18:31] Reserved -R */
} DMA_CH_PATCONFIG_Bits;

/* DMA channel n initial source address register */
typedef volatile struct
{
    ureg32 SRCADDR:32; /* [0:31] DMA source address -RW */
} DMA_CH_SRCADDRINIT_Bits;

/* DMA channel n initial destination address register */
typedef volatile struct
{
    ureg32 DESTADDR:32; /* [0:31] DMA destination address -RW */
} DMA_CH_DESTADDRINIT_Bits;

/* DMA channel n initial linked list item register */
typedef volatile struct
{
    ureg32 LM:1;            /* [0:0] AHB master select for loading the next LLI -RW */
    ureg32 reserved_1:1;    /* [1:1] Reserved -R */
    ureg32 LLI:30;          /* [2:31] Linked list item-RW */
} DMA_CH_LLIREGINIT_Bits;

/* DMA channel n initial control register */
typedef volatile struct
{
    ureg32 TRANSIZE:12; /* [0:11] Transfer size -RW */
    ureg32 SBSIZE:3;    /* [12:14] Source burst size -RW */
    ureg32 DBSIZE:3;    /* [15:17] Destination burst size -RW */
    ureg32 SWIDTH:3;    /* [18:20] Source transfer width -RW */
    ureg32 DWIDTH:3;    /* [21:23] Destination transfer width -RW */
    ureg32 S:1;         /* [24:24] Source AHB master select -RW */
    ureg32 D:1;         /* [25:25] Destination AHB master select -RW */
    ureg32 SI:1;        /* [26:26] Source increment -RW */
    ureg32 DI:1;        /* [27:27] Destination increment -RW */
    ureg32 PORT:3;      /* [28:30] AHB access mode -RW */
    ureg32 I:1;         /* [31:31] Terminal count interrupt enable bit -RW */
} DMA_CH_CONTROLINIT_Bits;

/* DMA channel double buffering switch address register */
typedef volatile struct
{
    ureg32 SWADDR:32; /* [0:31] Double buffering switch address -RW */
} DMA_CH_SWADDR_Bits;

/* DMA channel double buffering control register */
typedef volatile struct
{
    ureg32 SW:1;          /* [0:0] Double buffering software switch -W */
    ureg32 reserved_1:31; /* [1:31] Reserved -R */
} DMA_CH_DBCONTROL_Bits;

/* DMA channel double buffering status register */
typedef volatile struct
{
    ureg32 FROZEN0:1;     /* [0:0] Buffer 0 frozen -RW */
    ureg32 FROZEN1:1;     /* [1:1] Buffer 1 frozen -RW */
    ureg32 ACTBUF:1;      /* [2:2] Active buffer -R */
    ureg32 reserved_3:29; /* [3:31] Reserved -R */
} DMA_CH_DBSTS_Bits;

/* DMA channel data match pattern register */
typedef volatile struct
{
    ureg32 PAT:32; /* [0:31] Data for match pattern -RW */
} DMA_CH_PAT_Bits;

/* DMA channel data match pattern mask register */
typedef volatile struct
{
    ureg32 PAT:32; /* [0:31] Data mask for match pattern -RW */
} DMA_CH_PATMSK_Bits;

/* DMA channel interrupt status register */
typedef volatile struct
{
    ureg32 INTTCSTAT:1;   /* [0:0] Interrupt terminal count request status after masking -R */
    ureg32 INTERRSTAT:1;  /* [1:1] Interrupt error status after masking -R */
    ureg32 INTSCBSTAT:1;  /* [2:2] Interrupt source circular buffer status after masking -R */
    ureg32 INTDCBSTAT:1;  /* [3:3] Interrupt destination circular buffer status after masking -R */
    ureg32 INTPATSTAT:1;  /* [4:4] Interrupt pattern request status after masking -R */
    ureg32 INTTHR:1;      /* [5:5] Interrupt transfer size threshold request status after masking -R */
    ureg32 reserved_6:26; /* [6:31] Reserved -R */
} DMA_CH_INT_Bits;

/* DMA channel raw interrupt status register */
typedef volatile struct
{
    ureg32 RAWINTTC:1;    /* [0:0] Interrupt terminal count request status before masking -R */
    ureg32 RAWINTERR:1;   /* [1:1] Interrupt error status before masking -R */
    ureg32 RAWINTSCB:1;   /* [2:2] Interrupt source circular buffer status before masking -R */
    ureg32 RAWINTDCB:1;   /* [3:3] Interrupt destination circular buffer status before masking -R */
    ureg32 RAWINTPAT:1;   /* [4:4] Interrupt pattern request status before masking -R */
    ureg32 RAWINTTHR:1;   /* [5:5] Interrupt transfer size threshold request status before masking -R */
    ureg32 reserved_6:26; /* [6:31] Reserved -R */
} DMA_CH_RAWINT_Bits;

/* DMA channel interrupt clear register */
typedef volatile struct
{
    ureg32 INTTCCLR:1;    /* [0:0] Interrupt terminal count request clear -W */
    ureg32 INTERRCLR:1;   /* [1:1] Interrupt error request clear -W */
    ureg32 INTSCBCLR:1;   /* [2:2] Interrupt source circular buffer request clear -W */
    ureg32 INTDCBCLR:1;   /* [3:3] Interrupt destination circular request clear -W */
    ureg32 INTPATCLR:1;   /* [4:4] Interrupt pattern request clear -W */
    ureg32 INTTHRCLR:1;   /* [5:5] Interrupt transfer size threshold request clear -W */
    ureg32 reserved_6:26; /* [6:31] Reserved -R */
} DMA_CH_INTCLR_Bits;

/* DMA channel error clear register */
typedef volatile struct
{
    ureg32 REG:1;         /* [0:0] Register redundancy check error clear -W */
    ureg32 DCRC:1;        /* [1:1] data CRC error and value and valid clear -W */
    ureg32 LCRC:1;        /* [2:2] LLI CRC error and value and valid clear -W */
    ureg32 FIFO:1;        /* [3:3] FIFO parity check error clear -W */
    ureg32 reserved_4:28; /* [4:31] Reserved -R */
} DMA_CH_ERRCLR_Bits;

/* DMA channel transfer start time stamp register */
typedef volatile struct
{
    ureg32 TSTMP:32; /* [0:31] transfer start time stamp -R */
} DMA_CH_STTSTMP_Bits;

/* DMA channel transfer end time stamp register */
typedef volatile struct
{
    ureg32 TSTMP:32; /* [0:31] transfer end time stamp -R */
} DMA_CH_EDTSTMP_Bits;

/* DMA channel transfer time stamp valid status register */
typedef volatile struct
{
    ureg32 STVLD:1;       /* [0:0] transfer end time stamp valid status -R */
    ureg32 EDVLD:1;       /* [1:1] transfer start time stamp valid status -R */
    ureg32 reserved_2:30; /* [2:31] Reserved -R */
} DMA_CH_TSTMPVLD_Bits;

/* DMA channel transfer time stamp valid status clear register */
typedef volatile struct
{
    ureg32 STCLR:1;       /* [0:0] transfer end time stamp valid status clear -R */
    ureg32 EDCLR:1;       /* [1:1] transfer start time stamp valid status clear -R */
    ureg32 reserved_2:30; /* [2:31] Reserved -R */
} DMA_CH_TSTMPCLR_Bits;

/* DMA channel CRC configuration register */
typedef volatile struct
{
    ureg32 DCRCEN:2;       /* [0:1] data CRC enable -RW */
    ureg32 LLICRCEN:2;     /* [2:3] LLI CRC enable -RW */
    ureg32 reserved_4:12;  /* [4:15] Reserved -R */
    ureg32 DCRCMSK:2;      /* [16:17] data CRC alarm mask -RW */
    ureg32 LLICRCMSK:2;    /* [18:19] LLI CRC alarm mask -RW */
    ureg32 reserved_20:12; /* [20:31] Reserved -R */
} DMA_CH_CRCCONFIG_Bits;

/* DMA channel source CRC register */
typedef volatile struct
{
    ureg32 CRCVAL:8;      /* [0:7] source data CRC value -R */
    ureg32 VLD:1;         /* [8:8] source data CRC valid -R */
    ureg32 reserved_9:23; /* [9:31] Reserved -R */
} DMA_CH_SRCCRC_Bits;

/* DMA channel destination CRC register */
typedef volatile struct
{
    ureg32 CRCVAL:8;      /* [0:7] destination data CRC value -R */
    ureg32 VLD:1;         /* [8:8] destination data CRC valid -R */
    ureg32 reserved_9:23; /* [9:31] Reserved -R */
} DMA_CH_DESTCRC_Bits;

/* DMA channel LLI CRC register */
typedef volatile struct
{
    ureg32 CRCVAL:8;      /* [0:7] LLI data CRC value -R */
    ureg32 VLD:1;         /* [8:8] LLI data CRC valid -R */
    ureg32 reserved_9:23; /* [9:31] Reserved -R */
} DMA_CH_LLICRC_Bits;

/* DMA channel expected LLI CRC register */
typedef volatile struct
{
    ureg32 CRCVAL:8;      /* [0:7] expected LLI data CRC value -RW */
    ureg32 reserved_8:24; /* [8:31] Reserved -R */
} DMA_CH_EXPLLICRC_Bits;

/* DMA channel transfer size threshold register */
typedef volatile struct
{
    ureg32 THR:12;         /* [0:11] transfer size threshold -RW */
    ureg32 INTTHRMSK:1;    /* [12:12] transfer size threshold interrupt mask -RW */
    ureg32 INTTHREN:1;     /* [13:13] transfer size threshold interrupt enable -RW */
    ureg32 reserved_14:18; /* [14:31] Reserved -R */
} DMA_CH_THR_Bits;

/* DMA channel halt register */
typedef volatile struct
{
    ureg32 HALT:1;        /* [0:0] channel halt -RW */
    ureg32 reserved_1:31; /* [1:31] Reserved -R */
} DMA_CH_HALT_Bits;

/* DMA channel FIFO parity check configuration register */
typedef volatile struct
{
    ureg32 FIFOEN:2;        /* [0:1] FIFO parity check enable -RW */
    ureg32 reserved_2:14;   /* [2:15] Reserved -R */
    ureg32 FIFOMSK:2;       /* [16:17] FIFO parity check alarm mask -RW */
    ureg32 reserved_18:14;  /* [18:31] Reserved -R */
} DMA_CH_FIFOCONFIG_Bits;

/**********************************************************************************************************************
 *                                              DMA Register Definitions
 *********************************************************************************************************************/
/* Interrupt Status Register 0*/
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;              /* Unsigned access */
    DMA_INTSTATUS0_Bits B; /* Bit-Field access */
} DMA_INTSTA0;

/* Interrupt Status Register 1*/
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;              /* Unsigned access */
    DMA_INTSTATUS1_Bits B; /* Bit-Field access */
} DMA_INTSTA1;

/* DMA enabled channel status register 0 */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;              /* Unsigned access */
    DMA_ENBLDCHNS0_Bits B; /* Bit-Field access */
} DMA_ENBLDCHNS0;

/* DMA enabled channel status register 1 */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;              /* Unsigned access */
    DMA_ENBLDCHNS1_Bits B; /* Bit-Field access */
} DMA_ENBLDCHNS1;

/* DMA software burst request register 0*/
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;            /* Unsigned access */
    DMA_SOFTBREQ_Bits B; /* Bit-Field access */
} DMA_SOFTBREQ;

/* DMA software single request register 0*/
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;            /* Unsigned access */
    DMA_SOFTSREQ_Bits B; /* Bit-Field access */
} DMA_SOFTSREQ;

/* DMA software last burst request register 0*/
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;            /* Unsigned access */
    DMA_SOFTLBREQ_Bits B; /* Bit-Field access */
} DMA_SOFTLBREQ;

/* DMA software last single request register 0*/
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;            /* Unsigned access */
    DMA_SOFTLSREQ_Bits B; /* Bit-Field access */
} DMA_SOFTLSREQ;

/* DMA configuration register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;              /* Unsigned access */
    DMA_CONFIG_Bits B; /* Bit-Field access */
} DMA_CONFIG;

/* DMA function security configuration register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;            /* Unsigned access */
    DMA_SFCONFIG_Bits B; /* Bit-Field access */
} DMA_SFCONFIG;

/* DMA alarm status register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;            /* Unsigned access */
    DMA_ALMSTS_Bits B; /* Bit-Field access */
} DMA_ALMSTS;

/* DMA error status register 0 */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;           /* Unsigned access */
    DMA_ERRSTS0_Bits B; /* Bit-Field access */
} DMA_ERRSTS0;

/* DMA error status register 1 */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;           /* Unsigned access */
    DMA_ERRSTS1_Bits B; /* Bit-Field access */
} DMA_ERRSTS1;

/* DMA error status register 2 */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;           /* Unsigned access */
    DMA_ERRSTS2_Bits B; /* Bit-Field access */
} DMA_ERRSTS2;

/* DMA error status register 3 */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;           /* Unsigned access */
    DMA_ERRSTS3_Bits B; /* Bit-Field access */
} DMA_ERRSTS3;

/* DMA error status register 4 */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;           /* Unsigned access */
    DMA_ERRSTS4_Bits B; /* Bit-Field access */
} DMA_ERRSTS4;

/* DMA error status register 5 */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;           /* Unsigned access */
    DMA_ERRSTS5_Bits B; /* Bit-Field access */
} DMA_ERRSTS5;

/* DMA error status register 6 */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;           /* Unsigned access */
    DMA_ERRSTS6_Bits B; /* Bit-Field access */
} DMA_ERRSTS6;

/* DMA error status register 7 */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;           /* Unsigned access */
    DMA_ERRSTS7_Bits B; /* Bit-Field access */
} DMA_ERRSTS7;

/* DMA error status register 8 */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;           /* Unsigned access */
    DMA_ERRSTS8_Bits B; /* Bit-Field access */
} DMA_ERRSTS8;

/* DMA error status register 9 */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;           /* Unsigned access */
    DMA_ERRSTS9_Bits B; /* Bit-Field access */
} DMA_ERRSTS9;

/* DMA error status register 10 */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;            /* Unsigned access */
    DMA_ERRSTS10_Bits B; /* Bit-Field access */
} DMA_ERRSTS10;

/* DMA error status register 11 */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;            /* Unsigned access */
    DMA_ERRSTS11_Bits B; /* Bit-Field access */
} DMA_ERRSTS11;

/* DMA error clear register 0 */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;           /* Unsigned access */
    DMA_ERRCLR0_Bits B; /* Bit-Field access */
} DMA_ERRCLR0;

/* DMA error clear register 2 */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;           /* Unsigned access */
    DMA_ERRCLR2_Bits B; /* Bit-Field access */
} DMA_ERRCLR2;

/* DMA error injection register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;             /* Unsigned access */
    DMA_ERRINJ_Bits B; /* Bit-Field access */
} DMA_ERRINJ;

/* DMA error injection register 1 */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;             /* Unsigned access */
    DMA_ERRINJ1_Bits B; /* Bit-Field access */
} DMA_ERRINJ1;

/* DMA internal timer clock divider configuration register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;             /* Unsigned access */
    DMA_ITIMERDIV_Bits B; /* Bit-Field access */
} DMA_ITIMERDIV;

/* DMA internal timer value register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;             /* Unsigned access */
    DMA_ITIMERVAL_Bits B; /* Bit-Field access */
} DMA_ITIMERVAL;

/* DMA global request select register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;          /* Unsigned access */
    DMA_REQMUX_Bits B; /* Bit-Field access */
} DMA_REQMUX;

/* DMA channel source address register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;              /* Unsigned access */
    DMA_CH_SRCADDR_Bits B; /* Bit-Field access */
} DMA_CH_SRCADDR;

/* DMA channel destination address register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;              /* Unsigned access */
    DMA_CH_DESTADDR_Bits B; /* Bit-Field access */
} DMA_CH_DESTADDR;

/* DMA linked list item register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;            /* Unsigned access */
    DMA_CH_LLIREGBits B; /* Bit-Field access */
} DMA_CH_LLIREG;

/* DMA channel control register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;              /* Unsigned access */
    DMA_CH_CONTROL_Bits B; /* Bit-Field access */
} DMA_CH_CONTROL;

/* DMA channel configuration register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;             /* Unsigned access */
    DMA_CH_CONFIG_Bits B; /* Bit-Field access */
} DMA_CH_CONFIG;

/* DMA channel advance configuration register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;                /* Unsigned access */
    DMA_CH_ADVCONFIG_Bits B; /* Bit-Field access */
} DMA_CH_ADVCONFIG;

/* DMA channel data match pattern configuration register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;                /* Unsigned access */
    DMA_CH_PATCONFIG_Bits B; /* Bit-Field access */
} DMA_CH_PATCONFIG;

/* DMA channel initial source address register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;             /* Unsigned access */
    DMA_CH_SRCADDRINIT_Bits B; /* Bit-Field access */
} DMA_CH_SRCADDRINIT;

/* DMA channel initial destination address register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;             /* Unsigned access */
    DMA_CH_DESTADDRINIT_Bits B; /* Bit-Field access */
} DMA_CH_DESTADDRINIT;

/* DMA channel initial linked list item register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;             /* Unsigned access */
    DMA_CH_LLIREGINIT_Bits B; /* Bit-Field access */
} DMA_CH_LLIREGINIT;

/* DMA channel initial control register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;             /* Unsigned access */
    DMA_CH_CONTROLINIT_Bits B; /* Bit-Field access */
} DMA_CH_CONTROLINIT;

/* DMA channel double buffering switch address register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;             /* Unsigned access */
    DMA_CH_SWADDR_Bits B; /* Bit-Field access */
} DMA_CH_SWADDR;

/* DMA channel double buffering control register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;                /* Unsigned access */
    DMA_CH_DBCONTROL_Bits B; /* Bit-Field access */
} DMA_CH_DBCONTROL;

/* DMA channel double buffering status register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;            /* Unsigned access */
    DMA_CH_DBSTS_Bits B; /* Bit-Field access */
} DMA_CH_DBSTS;

/* DMA channel data match pattern register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;          /* Unsigned access */
    DMA_CH_PAT_Bits B; /* Bit-Field access */
} DMA_CH_PAT;

/* DMA channel data match pattern mask register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;             /* Unsigned access */
    DMA_CH_PATMSK_Bits B; /* Bit-Field access */
} DMA_CH_PATMSK;

/* DMA channel interrupt status register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;          /* Unsigned access */
    DMA_CH_INT_Bits B; /* Bit-Field access */
} DMA_CH_INT;

/* DMA channel raw interrupt status register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;             /* Unsigned access */
    DMA_CH_RAWINT_Bits B; /* Bit-Field access */
} DMA_CH_RAWINT;

/* DMA channel interrupt clear register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;             /* Unsigned access */
    DMA_CH_INTCLR_Bits B; /* Bit-Field access */
} DMA_CH_INTCLR;

/* DMA channel error clear register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;             /* Unsigned access */
    DMA_CH_ERRCLR_Bits B; /* Bit-Field access */
} DMA_CH_ERRCLR;

/* DMA channel transfer start time stamp register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;              /* Unsigned access */
    DMA_CH_STTSTMP_Bits B; /* Bit-Field access */
} DMA_CH_STTSTMP;

/* DMA channel transfer end time stamp register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;              /* Unsigned access */
    DMA_CH_EDTSTMP_Bits B; /* Bit-Field access */
} DMA_CH_EDTSTMP;

/* DMA channel time stamp valid status register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;               /* Unsigned access */
    DMA_CH_TSTMPVLD_Bits B; /* Bit-Field access */
} DMA_CH_TSTMPVLD;

/* DMA channel clear time stamp valid status register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;               /* Unsigned access */
    DMA_CH_TSTMPCLR_Bits B; /* Bit-Field access */
} DMA_CH_TSTMPCLR;

/* DMA channel CRC configuration register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;                /* Unsigned access */
    DMA_CH_CRCCONFIG_Bits B; /* Bit-Field access */
} DMA_CH_CRCCONFIG;

/* DMA channel source CRC register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;             /* Unsigned access */
    DMA_CH_SRCCRC_Bits B; /* Bit-Field access */
} DMA_CH_SRCCRC;

/* DMA channel destination CRC register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;              /* Unsigned access */
    DMA_CH_DESTCRC_Bits B; /* Bit-Field access */
} DMA_CH_DESTCRC;

/* DMA channel LLI CRC register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;             /* Unsigned access */
    DMA_CH_LLICRC_Bits B; /* Bit-Field access */
} DMA_CH_LLICRC;

/* DMA channel expected LLI CRC register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;                /* Unsigned access */
    DMA_CH_EXPLLICRC_Bits B; /* Bit-Field access */
} DMA_CH_EXPLLICRC;

/* DMA channel transfer size threshold register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;          /* Unsigned access */
    DMA_CH_THR_Bits B; /* Bit-Field access */
} DMA_CH_THR;

/* DMA channel halt register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;           /* Unsigned access */
    DMA_CH_HALT_Bits B; /* Bit-Field access */
} DMA_CH_HALT;

/* DMA channel FIFO parity check configuration register */
typedef union
/* #Violation: dma_register_h_REF_2 */
{
    uint32 U;           /* Unsigned access */
    DMA_CH_FIFOCONFIG_Bits B; /* Bit-Field access */
} DMA_CH_FIFOCONFIG;
/**********************************************************************************************************************
 *                                        DMA Register Configuration Structure
 *********************************************************************************************************************/
/* DMA Channel Register */
typedef volatile struct
{
    DMA_CH_SRCADDR SRCADDR;          /* 0, Channel n source address register */
    DMA_CH_DESTADDR DESTADDR;        /* 4, Channel n destination address register */
    DMA_CH_LLIREG LLIREG;            /* 8, Channel n linked list item register */
    DMA_CH_CONTROL CONTROL;          /* c, Channel n control register */
    DMA_CH_CONFIG CONFIG;            /* 10, Channel n configuration register */
    DMA_CH_ADVCONFIG ADVCONFIG;      /* 14, Channel n advance configuration register */
    DMA_CH_PATCONFIG PATCONFIG;      /* 18, Channel n data match pattern configuration register */
    DMA_CH_SRCADDRINIT SRCADDRINIT;  /* 1C, Channel n initial source address register */
    DMA_CH_DESTADDRINIT DESTADDRINIT;/* 20, Channel n initial destination address register */
    DMA_CH_LLIREGINIT LLIREGINIT;    /* 24, Channel n initial linked list item register */
    DMA_CH_CONTROLINIT CONTROLINIT;  /* 28, Channel n initial control register */
    DMA_CH_SWADDR SWADDR;            /* 2C, Channel n double buffering switch address register */
    DMA_CH_DBCONTROL DBCONTROL;      /* 30, Channel n double buffering control register */
    DMA_CH_DBSTS DBSTS;              /* 34, Channel n double buffering status register */
    DMA_CH_PAT PAT;                  /* 38, Channel n data match pattern register */
    DMA_CH_PATMSK PATMSK;            /* 3C, Channel n data match pattern register */
    DMA_CH_INT INT;                  /* 40, Channel n interrupt status register */
    DMA_CH_RAWINT RAWINT;            /* 44, Channel n raw interrupt status register */
    DMA_CH_INTCLR INTCLR;            /* 48, Channel n interrupt clear register */
    DMA_CH_ERRCLR ERRCLR;            /* 4C, Channel n error clear register */
    DMA_CH_STTSTMP STTSTMP;          /* 50, Channel n transfer start time stamp register */
    DMA_CH_EDTSTMP EDTSTMP;          /* 54, Channel n transfer end time stamp register */
    DMA_CH_TSTMPVLD TSTMPVLD;        /* 58, Channel n time stamp valid status register */
    DMA_CH_TSTMPCLR TSTMPCLR;        /* 5C, Channel n clear time stamp valid status register */
    DMA_CH_CRCCONFIG CRCCONFIG;      /* 60, Channel n CRC configuration register */
    DMA_CH_SRCCRC SRCCRC;            /* 64, Channel n source CRC register */
    DMA_CH_DESTCRC DESTCRC;          /* 68, Channel n destination CRC register */
    DMA_CH_LLICRC LLICRC;            /* 6C, Channel n LLI CRC register */
    DMA_CH_EXPLLICRC EXPLLICRC;      /* 70, Channel n expected LLI CRC register */
    DMA_CH_THR THR;                  /* 74, Channel n transfer size threshold register */
    DMA_CH_HALT HALT;                /* 78, Channel n halt register (THA6412 & THA6104 only) */
    DMA_CH_FIFOCONFIG FIFOCONFIG;    /* 7C, channel n FIFO parity check configuration register*/
} DMA_CH;

/* DMA Module Register */
typedef volatile struct
/* #Violation: dma_register_h_REF_1 */
/* #Violation: dma_register_h_REF_5 */
{
    DMA_INTSTA0 INTSTA0;            /* 0, Interrupt status register, for channel n (n <= 31) after masking */
    DMA_INTSTA1 INTSTA1;            /* 4, Interrupt status register, for channel n (n > 31) after masking */
    /* #Violation: dma_register_h_REF_3 */
    ureg32 RESERVED_8[26];          /* 8, \internal Reserved */
    DMA_ENBLDCHNS0 ENBLDCHNS0;      /* 70, Channel n (n <= 31) enable status register */
    DMA_ENBLDCHNS1 ENBLDCHNS1;      /* 74, Channel n (n > 31) enable status register */
    /* #Violation: dma_register_h_REF_3 */
    ureg32 RESERVED_78[2];          /* 78, \internal Reserved */
    /* #Violation: dma_register_h_REF_3 */
    DMA_SOFTBREQ SOFTBREQ03[4];     /* 80, Software burst request register, on burst request line 0~31 */
    /* #Violation: dma_register_h_REF_3 */
    DMA_SOFTSREQ SOFTSREQ03[4];     /* 90, Software single request register, on single request line 0~31 */
    /* #Violation: dma_register_h_REF_3 */
    DMA_SOFTLBREQ SOFTLBREQ03[4];   /* A0, Software last burst request register, on last burst request line 0~31 */
    /* #Violation: dma_register_h_REF_3 */
    DMA_SOFTLSREQ SOFTLSREQ03[4];   /* B0, Software last single request register, on last single request line 0~31 */
    DMA_CONFIG CONFIG;              /* C0, DMA configuration register */
    /* #Violation: dma_register_h_REF_3 */
    ureg32 RESERVED_C4[7];          /* C4, \internal Reserved */
    DMA_SFCONFIG SFCONFIG;          /* E0, DMA function security configuration register */
    DMA_ALMSTS ALMSTS;              /* E4, DMA alarm status register */
    DMA_ERRSTS0 ERRSTS0;            /* E8, DMA error status register 0 */
    DMA_ERRSTS1 ERRSTS1;            /* EC, DMA error status register 1 */
    DMA_ERRSTS2 ERRSTS2;            /* F0, DMA error status register 2 */
    DMA_ERRSTS3 ERRSTS3;            /* F4, DMA error status register 3 */
    DMA_ERRSTS4 ERRSTS4;            /* F8, DMA error status register 4 */
    DMA_ERRSTS5 ERRSTS5;            /* FC, DMA error status register 5 */
    DMA_ERRSTS6 ERRSTS6;            /* 100, DMA error status register 6 */
    DMA_ERRCLR0 ERRCLR0;            /* 104, DMA error clear register 0 */
    DMA_ERRCLR2 ERRCLR2;            /* 108, DMA error clear register 2 */
    DMA_ERRINJ ERRINJ;              /* 10C, DMA error injection register */
    DMA_ITIMERDIV ITIMERDIV;        /* 110, internal timer clock divider configuration register*/
    DMA_ITIMERVAL ITIMERVAL;        /* 114, internal timer value register*/
    /* #Violation: dma_register_h_REF_3 */
    ureg32 RESERVED_118[2];         /* 118, \internal Reserved */
    /* #Violation: dma_register_h_REF_3 */
    DMA_SOFTBREQ SOFTBREQ47[4];     /* 120, Software burst request register, on burst request line 128~159 */
    ureg32 RESERVED_130;            /* 130, \internal Reserved */
    /* #Violation: dma_register_h_REF_3 */
    DMA_SOFTSREQ SOFTSREQ47[4];     /* 134, Software single request register, on single request line 128~159 */
    ureg32 RESERVED_144;            /* 144, \internal Reserved */
    /* #Violation: dma_register_h_REF_3 */
    DMA_SOFTLBREQ SOFTLBREQ47[4];   /* 148, Software last burst request register, on last burst request line 128~159 */
    ureg32 RESERVED_158;            /* 158, \internal Reserved */
    /* #Violation: dma_register_h_REF_3 */
    DMA_SOFTLSREQ SOFTLSREQ47[4];   /* 15C, Software last single request register, on last single request line 128~159 */
    ureg32 RESERVED_16C;            /* 16C, \internal Reserved */
    DMA_ERRSTS7 ERRSTS7;            /* 170, DMA error status register 7, THA6104 and THA6412 are supported,
                                    but THA6206 is not supported */
    DMA_ERRSTS8 ERRSTS8;            /* 174, DMA error status register 8, THA6104 and THA6412 are supported,
                                    but THA6206 is not supported */
    DMA_ERRSTS9 ERRSTS9;            /* 178, DMA error status register 9, THA6104 and THA6412 are supported,
                                    but THA6206 is not supported */
    DMA_ERRINJ1 ERRINJ1;            /* 17C, DMA error injection register 1, THA6104 and THA6412 are supported,
                                    but THA6206 is not supported */
    DMA_ERRSTS10 ERRSTS10;          /* 180, DMA error status register 10, THA6104 is supported,
                                    but THA6206 and THA6412 are not supported */
    DMA_ERRSTS11 ERRSTS11;          /* 184, DMA error status register 11, THA6104 is supported,
                                    but THA6206 and THA6412 are not supported */
    /* #Violation: dma_register_h_REF_3 */
    ureg32 RESERVED_188[414];       /* 188, \internal Reserved */
    /* #Violation: dma_register_h_REF_3 */
    /* #Violation: dma_register_h_REF_4 */
    DMA_REQMUX REQMUX[32];          /* 800, DMA global request select register, for global request channel n */
    /* #Violation: dma_register_h_REF_3 */
    ureg32 RESERVED_880[480];       /* 880, \internal Reserved */
    /* #Violation: dma_register_h_REF_3 */
    /* #Violation: dma_register_h_REF_4 */
    DMA_CH CH[64];                  /* 1000, DMA channel n register cluster */
} DMA_MODULE;

#endif /* DMA_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
