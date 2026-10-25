/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    port_register.h
 * Author:      01077
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all definitions of PORT module registers.
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#port_register_h_REF_1:MISRAC2012-Rule-2.3; 
* Justification:This type is used by other file or inline assembly.
*
*#port_register_h_REF_2:MISRAC2012-Rule-19.2; 
* Justification:Unions are defined to simplify register assignment.
*
*#port_register_h_REF_3:MISRAC2012-Dir-4.8;
* Justification:Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#port_register_h_REF_4:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity
*
*#port_register_h_REF_5:CertC-DCL06-C;
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*
*#port_register_h_REF_6:CWE-547;
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*/
#ifndef PORT_REGISTER_H_
#define PORT_REGISTER_H_

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "regtypes.h"
#include "Platform_Types.h"
#include "tha6_cfg.h"

/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/************************************************* PORT Base Address *************************************************/
/**********************************************************************************************************************
 *                                        PORT Register Bit-Fields Definitions
 *********************************************************************************************************************/
/**************************************************** General IO *****************************************************/
/* Port n output data register */
typedef struct
{
    ureg32 ODR0:1;         /* [ 0: 0] Output bit 0 - RWH */
    ureg32 ODR1:1;         /* [ 1: 1] Output bit 1 - RWH */
    ureg32 ODR2:1;         /* [ 2: 2] Output bit 2 - RWH */
    ureg32 ODR3:1;         /* [ 3: 3] Output bit 3 - RWH */
    ureg32 ODR4:1;         /* [ 4: 4] Output bit 4 - RWH */
    ureg32 ODR5:1;         /* [ 5: 5] Output bit 5 - RWH */
    ureg32 ODR6:1;         /* [ 6: 6] Output bit 6 - RWH */
    ureg32 ODR7:1;         /* [ 7: 7] Output bit 7 - RWH */
    ureg32 ODR8:1;         /* [ 8: 8] Output bit 8 - RWH */
    ureg32 ODR9:1;         /* [ 9: 9] Output bit 9 - RWH */
    ureg32 ODR10:1;        /* [10:10] Output bit 10 - RWH */
    ureg32 ODR11:1;        /* [11:11] Output bit 11 - RWH */
    ureg32 ODR12:1;        /* [12:12] Output bit 12 - RWH */
    ureg32 ODR13:1;        /* [13:13] Output bit 13 - RWH */
    ureg32 ODR14:1;        /* [14:14] Output bit 14 - RWH */
    ureg32 ODR15:1;        /* [15:15] Output bit 15 - RWH */
    ureg32 reserved_16:16; /* [16:31] Internal reserved */
} PORT_ODR_Bits;

/* Port n output data set reset register */
typedef struct
{
    ureg32 BR0:1;  /* [ 0: 0] Reset bit 0  - W0 */
    ureg32 BR1:1;  /* [ 1: 1] Reset bit 1  - W0 */
    ureg32 BR2:1;  /* [ 2: 2] Reset bit 2  - W0 */
    ureg32 BR3:1;  /* [ 3: 3] Reset bit 3  - W0 */
    ureg32 BR4:1;  /* [ 4: 4] Reset bit 4  - W0 */
    ureg32 BR5:1;  /* [ 5: 5] Reset bit 5  - W0 */
    ureg32 BR6:1;  /* [ 6: 6] Reset bit 6  - W0 */
    ureg32 BR7:1;  /* [ 7: 7] Reset bit 7  - W0 */
    ureg32 BR8:1;  /* [ 8: 8] Reset bit 8  - W0 */
    ureg32 BR9:1;  /* [ 9: 9] Reset bit 9  - W0 */
    ureg32 BR10:1; /* [10:10] Reset bit 10 - W0 */
    ureg32 BR11:1; /* [11:11] Reset bit 11 - W0 */
    ureg32 BR12:1; /* [12:12] Reset bit 12 - W0 */
    ureg32 BR13:1; /* [13:13] Reset bit 13 - W0 */
    ureg32 BR14:1; /* [14:14] Reset bit 14 - W0 */
    ureg32 BR15:1; /* [15:15] Reset bit 15 - W0 */
    ureg32 BS0:1;  /* [16:16] Set bit 0 - W0 */
    ureg32 BS1:1;  /* [17:17] Set bit 1 - W0 */
    ureg32 BS2:1;  /* [18:18] Set bit 2 - W0 */
    ureg32 BS3:1;  /* [19:19] Set bit 3 - W0 */
    ureg32 BS4:1;  /* [20:20] Set bit 4 - W0 */
    ureg32 BS5:1;  /* [21:21] Set bit 5 - W0 */
    ureg32 BS6:1;  /* [22:22] Set bit 6 - W0 */
    ureg32 BS7:1;  /* [23:23] Set bit 7 - W0 */
    ureg32 BS8:1;  /* [24:24] Set bit 8 - W0 */
    ureg32 BS9:1;  /* [25:25] Set bit 9 - W0 */
    ureg32 BS10:1; /* [26:26] Set bit 10 - W0 */
    ureg32 BS11:1; /* [27:27] Set bit 11 - W0 */
    ureg32 BS12:1; /* [28:28] Set bit 12 - W0 */
    ureg32 BS13:1; /* [29:29] Set bit 13 - W0 */
    ureg32 BS14:1; /* [30:30] Set bit 14 - W0 */
    ureg32 BS15:1; /* [31:31] Set bit 15 - W0 */
} PORT_BSRR_Bits;

/* Port n control register 0 */
typedef struct
{
    ureg32 SEL0:4;        /* [ 3: 0] IO0 output multiplexing function selection - RW */
    ureg32 reserved_4:1;  /* [ 4: 4] Internal reserved */
    ureg32 OD0:1;         /* [ 5: 5] IO0 output push-pull/open-drain control - RW */
    ureg32 ENO0:1;        /* [ 6: 6] IO0 digital output channel enable control - RW */
    ureg32 DSI0:1;        /* [ 7: 7] IO0 digital input channel shutdown control - RW */
    ureg32 SEL1:4;        /* [11: 8] IO1 output multiplexing function selection - RW */
    ureg32 reserved_12:1; /* [12:12] Internal reserved */
    ureg32 OD1:1;         /* [13:13] IO1 output push-pull/open-drain control - RW */
    ureg32 ENO1:1;        /* [14:14] IO1 digital output channel enable control - RW */
    ureg32 DSI1:1;        /* [15:15] IO1 digital input channel shutdown control - RW */
    ureg32 SEL2:3;        /* [18:16] IO2 output multiplexing function selection - RW */
    ureg32 reserved_19:2; /* [20:19] Internal reserved */
    ureg32 OD2:1;         /* [21:21] IO2 output push-pull/open-drain control - RW */
    ureg32 ENO2:1;        /* [22:22] IO2 digital output channel enable control - RW */
    ureg32 DSI2:1;        /* [23:23] IO2 digital input channel shutdown control - RW */
    ureg32 SEL3:3;        /* [26:24] IO3 output multiplexing function selection - RW */
    ureg32 reserved_27:2; /* [28:27] Internal reserved */
    ureg32 OD3:1;         /* [29:29] IO3 output push-pull/open-drain control - RW */
    ureg32 ENO3:1;        /* [30:30] IO3 digital output channel enable control - RW */
    ureg32 DSI3:1;        /* [31:31] IO3 digital input channel shutdown control - RW */
} PORT_CTR0_Bits;

/* Port n control register 4 */
typedef struct
{
    ureg32 SEL4:3;        /* [ 2: 0] IO4 output multiplexing function selection - RW */
    ureg32 reserved_3:2;  /* [ 4: 3] Internal reserved */
    ureg32 OD4:1;         /* [ 5: 5] IO4 output push-pull/open-drain control - RW */
    ureg32 ENO4:1;        /* [ 6: 6] IO4 digital output channel enable control - RW */
    ureg32 DSI4:1;        /* [ 7: 7] IO4 digital input channel shutdown control - RW */
    ureg32 SEL5:4;        /* [11: 8] IO5 output multiplexing function selection - RW */
    ureg32 reserved_12:1; /* [12:12] Internal reserved */
    ureg32 OD5:1;         /* [13:13] IO5 output push-pull/open-drain control - RW */
    ureg32 ENO5:1;        /* [14:14] IO5 digital output channel enable control - RW */
    ureg32 DSI5:1;        /* [15:15] IO5 digital input channel shutdown control - RW */
    ureg32 SEL6:4;        /* [19:16] IO6 output multiplexing function selection - RW */
    ureg32 reserved_20:1; /* [20:20] Internal reserved */
    ureg32 OD6:1;         /* [21:21] IO6 output push-pull/open-drain control - RW */
    ureg32 ENO6:1;        /* [22:22] IO6 digital output channel enable control - RW */
    ureg32 DSI6:1;        /* [23:23] IO6 digital input channel shutdown control - RW */
    ureg32 SEL7:3;        /* [26:24] IO7 output multiplexing function selection - RW */
    ureg32 reserved_27:2; /* [28:27] Internal reserved */
    ureg32 OD7:1;         /* [29:29] IO7 output push-pull/open-drain control - RW */
    ureg32 ENO7:1;        /* [30:30] IO7 digital output channel enable control - RW */
    ureg32 DSI7:1;        /* [31:31] IO7 digital input channel shutdown control - RW */
} PORT_CTR4_Bits;

/* Port n control register 8 */
typedef struct
{
    ureg32 SEL8:3;        /* [ 2: 0] IO8 output multiplexing function selection - RW */
    ureg32 reserved_3:2;  /* [ 4: 3] Internal reserved */
    ureg32 OD8:1;         /* [ 5: 5] IO8 output push-pull/open-drain control - RW */
    ureg32 ENO8:1;        /* [ 6: 6] IO8 digital output channel enable control - RW */
    ureg32 DSI8:1;        /* [ 7: 7] IO8 digital input channel shutdown control - RW */
    ureg32 SEL9:4;        /* [11: 8] IO9 output multiplexing function selection - RW */
    ureg32 reserved_12:1; /* [12:12] Internal reserved */
    ureg32 OD9:1;         /* [13:13] IO9 output push-pull/open-drain control - RW */
    ureg32 ENO9:1;        /* [14:14] IO9 digital output channel enable control - RW */
    ureg32 DSI9:1;        /* [15:15] IO9 digital input channel shutdown control - RW */
    ureg32 SEL10:4;       /* [19:16] IO10 output multiplexing function selection - RW */
    ureg32 reserved_20:1; /* [20:20] Internal reserved */
    ureg32 OD10:1;        /* [21:21] IO10 output push-pull/open-drain control - RW */
    ureg32 ENO10:1;       /* [22:22] IO10 digital output channel enable control - RW */
    ureg32 DSI10:1;       /* [23:23] IO10 digital input channel shutdown control - RW */
    ureg32 SEL11:3;       /* [26:24] IO11 output multiplexing function selection - RW */
    ureg32 reserved_27:2; /* [28:27] Internal reserved */
    ureg32 OD11:1;        /* [29:29] IO11 output push-pull/open-drain control - RW */
    ureg32 ENO11:1;       /* [30:30] IO11 digital output channel enable control - RW */
    ureg32 DSI11:1;       /* [31:31] IO11 digital input channel shutdown control - RW */
} PORT_CTR8_Bits;

/* Port n control register 12 */
typedef struct
{
    ureg32 SEL12:4;       /* [ 3: 0] IO12 output multiplexing function selection - RW */
    ureg32 reserved_4:1;  /* [ 4: 4] Internal reserved */
    ureg32 OD12:1;        /* [ 5: 5] IO12 output push-pull/open-drain control - RW */
    ureg32 ENO12:1;       /* [ 6: 6] IO12 digital output channel enable control - RW */
    ureg32 DSI12:1;       /* [ 7: 7] IO12 digital input channel shutdown control - RW */
    ureg32 SEL13:3;       /* [10: 8] IO13 output multiplexing function selection - RW */
    ureg32 reserved_11:2; /* [12:11] Internal reserved */
    ureg32 OD13:1;        /* [13:13] IO13 output push-pull/open-drain control - RW */
    ureg32 ENO13:1;       /* [14:14] IO13 digital output channel enable control - RW */
    ureg32 DSI13:1;       /* [15:15] IO13 digital input channel shutdown control - RW */
    ureg32 SEL14:3;       /* [18:16] IO14 output multiplexing function selection - RW */
    ureg32 reserved_19:2; /* [20:19] Internal reserved */
    ureg32 OD14:1;        /* [21:21] IO14 output push-pull/open-drain control - RW */
    ureg32 ENO14:1;       /* [22:22] IO14 digital output channel enable control - RW */
    ureg32 DSI14:1;       /* [23:23] IO14 digital input channel shutdown control - RW */
    ureg32 SEL15:3;       /* [26:24] IO15 output multiplexing function selection - RW */
    ureg32 reserved_27:2; /* [28:27] Internal reserved */
    ureg32 OD15:1;        /* [29:29] IO15 output push-pull/open-drain control - RW */
    ureg32 ENO15:1;       /* [30:30] IO15 digital output channel enable control - RW */
    ureg32 DSI15:1;       /* [31:31] IO15 digital input channel shutdown control - RW */
} PORT_CTR12_Bits;

/* Port n input data register */
typedef struct
{
    ureg32 IDR0:1;         /* [ 0: 0] IO0 input data - RH */
    ureg32 IDR1:1;         /* [ 1: 1] IO1 input data - RH */
    ureg32 IDR2:1;         /* [ 2: 2] IO2 input data - RH */
    ureg32 IDR3:1;         /* [ 3: 3] IO3 input data - RH */
    ureg32 IDR4:1;         /* [ 4: 4] IO4 input data - RH */
    ureg32 IDR5:1;         /* [ 5: 5] IO5 input data - RH */
    ureg32 IDR6:1;         /* [ 6: 6] IO6 input data - RH */
    ureg32 IDR7:1;         /* [ 7: 7] IO7 input data - RH */
    ureg32 IDR8:1;         /* [ 8: 8] IO8 input data - RH */
    ureg32 IDR9:1;         /* [ 9: 9] IO9 input data - RH */
    ureg32 IDR10:1;        /* [10:10] IO10 input data - RH */
    ureg32 IDR11:1;        /* [11:11] IO11 input data - RH */
    ureg32 IDR12:1;        /* [12:12] IO12 input data - RH */
    ureg32 IDR13:1;        /* [13:13] IO13 input data - RH */
    ureg32 IDR14:1;        /* [14:14] IO14 input data - RH */
    ureg32 IDR15:1;        /* [15:15] IO15 input data - RH */
    ureg32 reserved_16:16; /* [16:31] Internal reserved */
} PORT_IDR_Bits;

/* Port n STTL Control Register */
typedef struct
{
    ureg32 STTL0:1;        /* [ 0: 0] IO0 select TTL voltage level- RW */
    ureg32 STTL1:1;        /* [ 1: 1] IO1 select TTL voltage level- RW */
    ureg32 STTL2:1;        /* [ 2: 2] IO2 select TTL voltage level- RW */
    ureg32 STTL3:1;        /* [ 3: 3] IO3 select TTL voltage level- RW */
    ureg32 STTL4:1;        /* [ 4: 4] IO4 select TTL voltage level- RW */
    ureg32 STTL5:1;        /* [ 5: 5] IO5 select TTL voltage level- RW */
    ureg32 STTL6:1;        /* [ 6: 6] IO6 select TTL voltage level- RW */
    ureg32 STTL7:1;        /* [ 7: 7] IO7 select TTL voltage level- RW */
    ureg32 STTL8:1;        /* [ 8: 8] IO8 select TTL voltage level- RW */
    ureg32 STTL9:1;        /* [ 9: 9] IO9 select TTL voltage level- RW */
    ureg32 STTL10:1;       /* [10:10] IO10 select TTL voltage level- RW */
    ureg32 STTL11:1;       /* [11:11] IO11 select TTL voltage level- RW */
    ureg32 STTL12:1;       /* [12:12] IO12 select TTL voltage level- RW */
    ureg32 STTL13:1;       /* [13:13] IO13 select TTL voltage level- RW */
    ureg32 STTL14:1;       /* [14:14] IO14 select TTL voltage level- RW */
    ureg32 STTL15:1;       /* [15:15] IO15 select TTL voltage level- RW */
    ureg32 reserved_16:16; /* [16:31] Internal reserved */
} PORT_STTL_Bits;

/* Port n pad drive mode register 0 */
typedef struct
{
    ureg32 DR0:1; /* [ 0: 0] IO0 pad drive strength selection - RW */
    ureg32 IS0:1; /* [ 1: 1] IO0 pad input mode selection - RW */
    ureg32 SR0:1; /* [ 2: 2] IO0 slew rate enable/disable - RW */
    ureg32 PL0:1; /* [ 3: 3] IO0 pad level (AL, TTL) selection - RW */
    ureg32 DR1:1; /* [ 4: 4] IO1 pad drive strength selection - RW */
    ureg32 IS1:1; /* [ 5: 5] IO1 pad input mode selection - RW */
    ureg32 SR1:1; /* [ 6: 6] IO1 slew rate enable/disable - RW */
    ureg32 PL1:1; /* [ 7: 7] IO1 pad level (AL, TTL) selection - RW */
    ureg32 DR2:1; /* [ 8: 8] IO2 pad drive strength selection - RW */
    ureg32 IS2:1; /* [ 9: 9] IO2 pad input mode selection - RW */
    ureg32 SR2:1; /* [10:10] IO2 slew rate enable/disable - RW */
    ureg32 PL2:1; /* [11:11] IO2 pad level (AL, TTL) selection - RW */
    ureg32 DR3:1; /* [12:12] IO3 pad drive strength selection - RW */
    ureg32 IS3:1; /* [13:13] IO3 pad input mode selection - RW */
    ureg32 SR3:1; /* [14:14] IO3 slew rate enable/disable - RW */
    ureg32 PL3:1; /* [15:15] IO3 pad level (AL, TTL) selection - RW */
    ureg32 DR4:1; /* [16:16] IO4 pad drive strength selection - RW */
    ureg32 IS4:1; /* [17:17] IO4 pad input mode selection - RW */
    ureg32 SR4:1; /* [18:18] IO4 slew rate enable/disable - RW */
    ureg32 PL4:1; /* [19:19] IO4 pad level (AL, TTL) selection - RW */
    ureg32 DR5:1; /* [20:20] IO5 pad drive strength selection - RW */
    ureg32 IS5:1; /* [21:21] IO5 pad input mode selection - RW */
    ureg32 SR5:1; /* [22:22] IO5 slew rate enable/disable - RW */
    ureg32 PL5:1; /* [23:23] IO5 pad level (AL, TTL) selection - RW */
    ureg32 DR6:1; /* [24:24] IO6 pad drive strength selection - RW */
    ureg32 IS6:1; /* [25:25] IO6 pad input mode selection - RW */
    ureg32 SR6:1; /* [26:26] IO6 slew rate enable/disable - RW */
    ureg32 PL6:1; /* [27:27] IO6 pad level (AL, TTL) selection - RW */
    ureg32 DR7:1; /* [28:28] IO7 pad drive strength selection - RW */
    ureg32 IS7:1; /* [29:29] IO7 pad input mode selection - RW */
    ureg32 SR7:1; /* [30:30] IO7 slew rate enable/disable - RW */
    ureg32 PL7:1; /* [31:31] IO7 pad level (AL, TTL) selection - RW */
} PORT_DSR0_Bits;

/* Port n pad drive mode register 8 */
typedef struct
{
    ureg32 DR8:1;  /* [ 0: 0] IO8 pad drive strength selection - RW */
    ureg32 IS8:1;  /* [ 1: 1] IO8 pad input mode selection - RW */
    ureg32 SR8:1;  /* [ 2: 2] IO8 slew rate enable/disable - RW */
    ureg32 PL8:1;  /* [ 3: 3] IO8 pad level (AL, TTL) selection - RW */
    ureg32 DR9:1;  /* [ 4: 4] IO9 pad drive strength selection - RW */
    ureg32 IS9:1;  /* [ 5: 5] IO9 pad input mode selection - RW */
    ureg32 SR9:1;  /* [ 6: 6] IO9 slew rate enable/disable - RW */
    ureg32 PL9:1;  /* [ 7: 7] IO9 pad level (AL, TTL) selection - RW */
    ureg32 DR10:1; /* [ 8: 8] IO10 pad drive strength selection - RW */
    ureg32 IS10:1; /* [ 9: 9] IO10 pad input mode selection - RW */
    ureg32 SR10:1; /* [10:10] IO10 slew rate enable/disable - RW */
    ureg32 PL10:1; /* [11:11] IO10 pad level (AL, TTL) selection - RW */
    ureg32 DR11:1; /* [12:12] IO11 pad drive strength selection - RW */
    ureg32 IS11:1; /* [13:13] IO11 pad input mode selection - RW */
    ureg32 SR11:1; /* [14:14] IO11 slew rate enable/disable - RW */
    ureg32 PL11:1; /* [15:15] IO11 pad level (AL, TTL) selection - RW */
    ureg32 DR12:1; /* [16:16] IO12 pad drive strength selection - RW */
    ureg32 IS12:1; /* [17:17] IO12 pad input mode selection - RW */
    ureg32 SR12:1; /* [18:18] IO12 slew rate enable/disable - RW */
    ureg32 PL12:1; /* [19:19] IO12 pad level (AL, TTL) selection - RW */
    ureg32 DR13:1; /* [20:20] IO13 pad drive strength selection - RW */
    ureg32 IS13:1; /* [21:21] IO13 pad input mode selection - RW */
    ureg32 SR13:1; /* [22:22] IO13 slew rate enable/disable - RW */
    ureg32 PL13:1; /* [23:23] IO13 pad level (AL, TTL) selection - RW */
    ureg32 DR14:1; /* [24:24] IO14 pad drive strength selection - RW */
    ureg32 IS14:1; /* [25:25] IO14 pad input mode selection - RW */
    ureg32 SR14:1; /* [26:26] IO14 slew rate enable/disable - RW */
    ureg32 PL14:1; /* [27:27] IO14 pad level (AL, TTL) selection - RW */
    ureg32 DR15:1; /* [28:28] IO15 pad drive strength selection - RW */
    ureg32 IS15:1; /* [29:29] IO15 pad input mode selection - RW */
    ureg32 SR15:1; /* [30:30] IO15 slew rate enable/disable - RW */
    ureg32 PL15:1; /* [31:31] IO15 pad level (AL, TTL) selection - RW */
} PORT_DSR8_Bits;

/* Port n emergency stop register */
typedef struct
{
    ureg32 EN0:2;  /* [ 1: 0] IO0 emergency stop function enable - RW */
    ureg32 EN1:2;  /* [ 3: 2] IO1 emergency stop function enable - RW */
    ureg32 EN2:2;  /* [ 5: 4] IO2 emergency stop function enable - RW */
    ureg32 EN3:2;  /* [ 7: 6] IO3 emergency stop function enable - RW */
    ureg32 EN4:2;  /* [ 9: 8] IO4 emergency stop function enable - RW */
    ureg32 EN5:2;  /* [11:10] IO5 emergency stop function enable - RW */
    ureg32 EN6:2;  /* [13:12] IO6 emergency stop function enable - RW */
    ureg32 EN7:2;  /* [15:14] IO7 emergency stop function enable - RW */
    ureg32 EN8:2;  /* [17:16] IO8 emergency stop function enable - RW */
    ureg32 EN9:2;  /* [19:18] IO9 emergency stop function enable - RW */
    ureg32 EN10:2; /* [21:20] IO10 emergency stop function enable - RW */
    ureg32 EN11:2; /* [23:22] IO11 emergency stop function enable - RW */
    ureg32 EN12:2; /* [25:24] IO12 emergency stop function enable - RW */
    ureg32 EN13:2; /* [27:26] IO13 emergency stop function enable - RW */
    ureg32 EN14:2; /* [29:28] IO14 emergency stop function enable - RW */
    ureg32 EN15:2; /* [31:30] IO15 emergency stop function enable - RW */
} PORT_ESR_Bits;

/* Port n digital function register */
typedef struct
{
    ureg32 DFR0:2;  /* [ 1: 0] IO0 digital function configure - RW */
    ureg32 DFR1:2;  /* [ 3: 2] IO1 digital function configure - RW */
    ureg32 DFR2:2;  /* [ 5: 4] IO2 digital function configure - RW */
    ureg32 DFR3:2;  /* [ 7: 6] IO3 digital function configure - RW */
    ureg32 DFR4:2;  /* [ 9: 8] IO4 digital function configure - RW */
    ureg32 DFR5:2;  /* [11:10] IO5 digital function configure - RW */
    ureg32 DFR6:2;  /* [13:12] IO6 digital function configure - RW */
    ureg32 DFR7:2;  /* [15:14] IO7 digital function configure - RW */
    ureg32 DFR8:2;  /* [17:16] IO8 digital function configure - RW */
    ureg32 DFR9:2;  /* [19:18] IO9 digital function configure - RW */
    ureg32 DFR10:2; /* [21:20] IO10 digital function configure - RW */
    ureg32 DFR11:2; /* [23:22] IO11 digital function configure - RW */
    ureg32 DFR12:2; /* [25:24] IO12 digital function configure - RW */
    ureg32 DFR13:2; /* [27:26] IO13 digital function configure - RW */
    ureg32 DFR14:2; /* [29:28] IO14 digital function configure - RW */
    ureg32 DFR15:2; /* [31:30] IO15 digital function configure - RW */
} PORT_DFR_Bits;

/* Port n hardware control register */
typedef struct
{
    ureg32 SEL0:2;  /* [ 1: 0] IO0 hardware control select - RW */
    ureg32 SEL1:2;  /* [ 3: 2] IO1 hardware control select - RW */
    ureg32 SEL2:2;  /* [ 5: 4] IO2 hardware control select - RW */
    ureg32 SEL3:2;  /* [ 7: 6] IO3 hardware control select - RW */
    ureg32 SEL4:2;  /* [ 9: 8] IO4 hardware control select - RW */
    ureg32 SEL5:2;  /* [11:10] IO5 hardware control select - RW */
    ureg32 SEL6:2;  /* [13:12] IO6 hardware control select - RW */
    ureg32 SEL7:2;  /* [15:14] IO7 hardware control select - RW */
    ureg32 SEL8:2;  /* [17:16] IO8 hardware control select - RW */
    ureg32 SEL9:2;  /* [19:18] IO9 hardware control select - RW */
    ureg32 SEL10:2; /* [21:20] IO10 hardware control select - RW */
    ureg32 SEL11:2; /* [23:22] IO11 hardware control select - RW */
    ureg32 SEL12:2; /* [25:24] IO12 hardware control select - RW */
    ureg32 SEL13:2; /* [27:26] IO13 hardware control select - RW */
    ureg32 SEL14:2; /* [29:28] IO14 hardware control select - RW */
    ureg32 SEL15:2; /* [31:30] IO15 hardware control select - RW */
} PORT_HWCR_Bits;

/* Port n pull select register */
typedef struct
{
    ureg32 PS0:2;  /* [ 1: 0] IO0 pull select - RW */
    ureg32 PS1:2;  /* [ 3: 2] IO1 pull select - RW */
    ureg32 PS2:2;  /* [ 5: 4] IO2 pull select - RW */
    ureg32 PS3:2;  /* [ 7: 6] IO3 pull select - RW */
    ureg32 PS4:2;  /* [ 9: 8] IO4 pull select - RW */
    ureg32 PS5:2;  /* [11:10] IO5 pull select - RW */
    ureg32 PS6:2;  /* [13:12] IO6 pull select - RW */
    ureg32 PS7:2;  /* [15:14] IO7 pull select - RW */
    ureg32 PS8:2;  /* [17:16] IO8 pull select - RW */
    ureg32 PS9:2;  /* [19:18] IO9 pull select - RW */
    ureg32 PS10:2; /* [21:20] IO10 pull select - RW */
    ureg32 PS11:2; /* [23:22] IO11 pull select - RW */
    ureg32 PS12:2; /* [25:24] IO12 pull select - RW */
    ureg32 PS13:2; /* [27:26] IO13 pull select - RW */
    ureg32 PS14:2; /* [29:28] IO14 pull select - RW */
    ureg32 PS15:2; /* [31:30] IO15 pull select - RW */
} PORT_PSR_Bits;

/* Port n output data bit set register 0 */
typedef struct
{
    ureg32 reserved_0:16;  /* [15: 0] Internal reserved */
    ureg32 BS0:1;          /* [16:16] IO0 output data set bit - W0 */
    ureg32 BS1:1;          /* [17:17] IO1 output data set bit - W0 */
    ureg32 BS2:1;          /* [18:18] IO2 output data set bit - W0 */
    ureg32 BS3:1;          /* [19:19] IO3 output data set bit - W0 */
    ureg32 reserved_20:12; /* [31:20] Internal reserved */
} PORT_BSR0_Bits;

/* Port n output data bit set register 4 */
typedef struct
{
    ureg32 reserved_0:20; /* [19: 0] Internal reserved */
    ureg32 BS4:1;         /* [20:20] IO4 output data set bit - W0 */
    ureg32 BS5:1;         /* [21:21] IO5 output data set bit - W0 */
    ureg32 BS6:1;         /* [22:22] IO6 output data set bit - W0 */
    ureg32 BS7:1;         /* [23:23] IO7 output data set bit - W0 */
    ureg32 reserved_24:8; /* [31:24] Internal reserved */
} PORT_BSR4_Bits;

/* Port output data bit set register 8 */
typedef struct
{
    ureg32 reserved_0:24; /* [23: 0] Internal reserved */
    ureg32 BS8:1;         /* [24:24] IO8 output data set bit - W0 */
    ureg32 BS9:1;         /* [25:25] IO9 output data set bit - W0 */
    ureg32 BS10:1;        /* [26:26] IO10 output data set bit - W0 */
    ureg32 BS11:1;        /* [27:27] IO11 output data set bit - W0 */
    ureg32 reserved_28:4; /* [31:28] Internal reserved */
} PORT_BSR8_Bits;

/* Port n output data bit set register 12 */
typedef struct
{
    ureg32 reserved_0:28; /* [27: 0] Internal reserved */
    ureg32 BS12:1;        /* [28:28] IO12 output data set bit - W0 */
    ureg32 BS13:1;        /* [29:29] IO13 output data set bit - W0 */
    ureg32 BS14:1;        /* [30:30] IO14 output data set bit - W0 */
    ureg32 BS15:1;        /* [31:31] IO15 output data set bit - W0 */
} PORT_BSR12_Bits;

/* Port n output data bit reset register 0 */
typedef struct
{
    ureg32 BR0:1;         /* [0: 0] IO0 output data reset bit - W0 */
    ureg32 BR1:1;         /* [1: 1] IO1 output data reset bit - W0 */
    ureg32 BR2:1;         /* [2: 2] IO2 output data reset bit - W0 */
    ureg32 BR3:1;         /* [3: 3] IO3 output data reset bit - W0 */
    ureg32 reserved_4:28; /* [31:4] Internal reserved */
} PORT_BRR0_Bits;

/* Port n output data bit reset register 4 */
typedef struct
{
    ureg32 reserved_0:4;  /* [ 3: 0] Internal reserved */
    ureg32 BR4:1;         /* [ 4: 4] IO4 output data reset bit - W0 */
    ureg32 BR5:1;         /* [ 5: 5] IO5 output data reset bit - W0 */
    ureg32 BR6:1;         /* [ 6: 6] IO6 output data reset bit - W0 */
    ureg32 BR7:1;         /* [ 7: 7] IO7 output data reset bit - W0 */
    ureg32 reserved_8:24; /* [31: 8] Internal reserved */
} PORT_BRR4_Bits;

/* Port n output data bit reset register 8 */
typedef struct
{
    ureg32 reserved_0:8;   /* [ 7: 0] Internal reserved */
    ureg32 BR8:1;          /* [ 8: 8] IO8 output data reset bit - W0 */
    ureg32 BR9:1;          /* [ 9: 9] IO9 output data reset bit - W0 */
    ureg32 BR10:1;         /* [10:10] IO10 output data reset bit - W0 */
    ureg32 BR11:1;         /* [11:11] IO11 output data reset bit - W0 */
    ureg32 reserved_12:20; /* [31:12] Internal reserved */
} PORT_BRR8_Bits;

/* Port n output data bit reset register 12 */
typedef struct
{
    ureg32 reserved_0:12;  /* [11: 0] Internal reserved */
    ureg32 BR12:1;         /* [12:12] IO12 output data reset bit - W0 */
    ureg32 BR13:1;         /* [13:13] IO13 output data reset bit - W0 */
    ureg32 BR14:1;         /* [14:14] IO14 output data reset bit - W0 */
    ureg32 BR15:1;         /* [15:15] IO15 output data reset bit - W0 */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} PORT_BRR12_Bits;

/* Port n output data set register */
typedef struct
{
    ureg32 BS0:1;          /* [ 0: 0] IO0 output data set bit - W0 */
    ureg32 BS1:1;          /* [ 1: 1] IO1 output data set bit - W0 */
    ureg32 BS2:1;          /* [ 2: 2] IO2 output data set bit - W0 */
    ureg32 BS3:1;          /* [ 3: 3] IO3 output data set bit - W0 */
    ureg32 BS4:1;          /* [ 4: 4] IO4 output data set bit - W0 */
    ureg32 BS5:1;          /* [ 5: 5] IO5 output data set bit - W0 */
    ureg32 BS6:1;          /* [ 6: 6] IO6 output data set bit - W0 */
    ureg32 BS7:1;          /* [ 7: 7] IO7 output data set bit - W0 */
    ureg32 BS8:1;          /* [ 8: 8] IO8 output data set bit - W0 */
    ureg32 BS9:1;          /* [ 9: 9] IO9 output data set bit - W0 */
    ureg32 BS10:1;         /* [10:10] IO10 output data set bit - W0 */
    ureg32 BS11:1;         /* [11:11] IO11 output data set bit - W0 */
    ureg32 BS12:1;         /* [12:12] IO12 output data set bit - W0 */
    ureg32 BS13:1;         /* [13:13] IO13 output data set bit - W0 */
    ureg32 BS14:1;         /* [14:14] IO14 output data set bit - W0 */
    ureg32 BS15:1;         /* [15:15] IO15 output data set bit - W0 */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} PORT_BSR_Bits;

/* Port n output data reset register */
typedef struct
{
    ureg32 reserved_0:16; /* [15: 0] Internal reserved */
    ureg32 BR0:1;         /* [16:16] IO0 output data reset bit - W0 */
    ureg32 BR1:1;         /* [17:17] IO1 output data reset bit - W0 */
    ureg32 BR2:1;         /* [18:18] IO2 output data reset bit - W0 */
    ureg32 BR3:1;         /* [19:19] IO3 output data reset bit - W0 */
    ureg32 BR4:1;         /* [20:20] IO4 output data reset bit - W0 */
    ureg32 BR5:1;         /* [21:21] IO5 output data reset bit - W0 */
    ureg32 BR6:1;         /* [22:22] IO6 output data reset bit - W0 */
    ureg32 BR7:1;         /* [23:23] IO7 output data reset bit - W0 */
    ureg32 BR8:1;         /* [24:24] IO8 output data reset bit - W0 */
    ureg32 BR9:1;         /* [25:25] IO9 output data reset bit - W0 */
    ureg32 BR10:1;        /* [26:26] IO10 output data reset bit - W0 */
    ureg32 BR11:1;        /* [27:27] IO11 output data reset bit - W0 */
    ureg32 BR12:1;        /* [28:28] IO12 output data reset bit - W0 */
    ureg32 BR13:1;        /* [29:29] IO13 output data reset bit - W0 */
    ureg32 BR14:1;        /* [30:30] IO14 output data reset bit - W0 */
    ureg32 BR15:1;        /* [31:31] IO15 output data reset bit - W0 */
} PORT_BRR_Bits;

/* Port n LVDS pad control register */
typedef struct
{
    ureg32 TXEN:1;         /* [ 0: 0] LVDS transmit driver enable - RW */
    ureg32 BIASEN:1;       /* [ 1: 1] Bias circuit enable  - RW */
    ureg32 VBIASSEL:1;     /* [ 2: 2] Select bias voltage for I/O - RW */
    ureg32 TXCM:1;         /* [ 3: 3] Transmitter common mode select - RW */
    ureg32 IRATIO:2;       /* [ 5: 4] Output current ratio trim - RW */
    ureg32 VOD:2;          /* [ 7: 6] Drive current and differential output voltage magnitude select - RW */
    ureg32 RTERMVAL:3;     /* [10: 8] Termination value set bits - RW */
    ureg32 RTERMEN:1;      /* [11:11] Termination Resistor enable/disable - RW */
    ureg32 reserved_12:20; /* [31:12] Internal reserved */
} PORT_LVDSR_Bits;

/* Port n error status register */
typedef struct
{
    ureg32 SFRRDN:1;       /* [0:0] SFR redundant error - RWH */
    ureg32 reserved_1:3;   /* [3:1] Internal reserved */
    ureg32 SFRACC:1;       /* [4:4] SFR invalid access error - RWH */
    ureg32 reserved_5:27;  /* [31:5] Internal reserved */
} PORT_ERSTS_Bits;

/* Port n error status mask register */
typedef struct
{
    ureg32 SFRRDN:1;       /* [0:0] SFR redundant error mask - RW */
    ureg32 reserved_1:3;   /* [3:1] Internal reserved */
    ureg32 SFRACC:1;       /* [4:4] SFR invalid access error mask - RW */
    ureg32 reserved_5:27;  /* [31:5] Internal reserved */
} PORT_ERRMSK_Bits;

/* Port n backup request register */
typedef struct
{
    ureg32 REQ0:1;         /* [0:0] IO0 backup Request - RWH */
    ureg32 REQ1:1;         /* [1:1] IO1 backup Request - RWH */
    ureg32 REQ2:1;         /* [2:2] IO2 backup Request - RWH */
    ureg32 REQ3:1;         /* [3:3] IO3 backup Request - RWH */
    ureg32 REQ4:1;         /* [4:4] IO4 backup Request - RWH */
    ureg32 REQ5:1;         /* [5:5] IO5 backup Request - RWH */
    ureg32 REQ6:1;         /* [6:6] IO6 backup Request - RWH */
    ureg32 REQ7:1;         /* [7:7] IO7 backup Request - RWH */
    ureg32 REQ8:1;         /* [8:8] IO8 backup Request - RWH */
    ureg32 REQ9:1;         /* [9:9] IO9 backup Request - RWH */
    ureg32 REQ10:1;        /* [10:10] IO10 backup Request - RWH */
    ureg32 REQ11:1;        /* [11:11] IO11 backup Request - RWH */
    ureg32 REQ12:1;        /* [12:12] IO12 backup Request - RWH */
    ureg32 REQ13:1;        /* [13:13] IO13 backup Request - RWH */
    ureg32 REQ14:1;        /* [14:14] IO14 backup Request - RWH */
    ureg32 REQ15:1;        /* [15:15] IO15 backup Request - RWH */
    ureg32 reserved_16:16; /* [31:16] Internal reserved - RO */
} PORT_BACKUPREQ_Bits;

/* Port n backup clear register */
typedef struct
{
    ureg32 CLR0:1;         /* [0:0] IO0 backup Clear - RWH */
    ureg32 CLR1:1;         /* [1:1] IO1 backup Clear - RWH */
    ureg32 CLR2:1;         /* [2:2] IO2 backup Clear - RWH */
    ureg32 CLR3:1;         /* [3:3] IO3 backup Clear - RWH */
    ureg32 CLR4:1;         /* [4:4] IO4 backup Clear - RWH */
    ureg32 CLR5:1;         /* [5:5] IO5 backup Clear - RWH */
    ureg32 CLR6:1;         /* [6:6] IO6 backup Clear - RWH */
    ureg32 CLR7:1;         /* [7:7] IO7 backup Clear - RWH */
    ureg32 CLR8:1;         /* [8:8] IO8 backup Clear - RWH */
    ureg32 CLR9:1;         /* [9:9] IO9 backup Clear - RWH */
    ureg32 CLR10:1;        /* [10:10] IO10 backup Clear - RWH */
    ureg32 CLR11:1;        /* [11:11] IO11 backup Clear - RWH */
    ureg32 CLR12:1;        /* [12:12] IO12 backup Clear - RWH */
    ureg32 CLR13:1;        /* [13:13] IO13 backup Clear - RWH */
    ureg32 CLR14:1;        /* [14:14] IO14 backup Clear - RWH */
    ureg32 CLR15:1;        /* [15:15] IO15 backup Clear - RWH */
    ureg32 reserved_16:16; /* [31:16] Internal reserved - RO */
} PORT_BACKUPCLR_Bits;

/* Port n backup active status register */
typedef struct
{
    ureg32 ACTSTS0:1;      /* [0:0] IO0 backup Active Status - RH */
    ureg32 ACTSTS1:1;      /* [1:1] IO1 backup Active Status - RH */
    ureg32 ACTSTS2:1;      /* [2:2] IO2 backup Active Status - RH */
    ureg32 ACTSTS3:1;      /* [3:3] IO3 backup Active Status - RH */
    ureg32 ACTSTS4:1;      /* [4:4] IO4 backup Active Status - RH */
    ureg32 ACTSTS5:1;      /* [5:5] IO5 backup Active Status - RH */
    ureg32 ACTSTS6:1;      /* [6:6] IO6 backup Active Status - RH */
    ureg32 ACTSTS7:1;      /* [7:7] IO7 backup Active Status - RH */
    ureg32 ACTSTS8:1;      /* [8:8] IO8 backup Active Status - RH */
    ureg32 ACTSTS9:1;      /* [9:9] IO9 backup Active Status - RH */
    ureg32 ACTSTS10:1;     /* [10:10] IO10 backup Active Status - RH */
    ureg32 ACTSTS11:1;     /* [11:11] IO11 backup Active Status - RH */
    ureg32 ACTSTS12:1;     /* [12:12] IO12 backup Active Status - RH */
    ureg32 ACTSTS13:1;     /* [13:13] IO13 backup Active Status - RH */
    ureg32 ACTSTS14:1;     /* [14:14] IO14 backup Active Status - RH */
    ureg32 ACTSTS15:1;     /* [15:15] IO15 backup Active Status - RH */
    ureg32 reserved_16:16; /* [31:16] Internal reserved - RO */
} PORT_BACKUPSTS_Bits;

/******************************************************* ESR IO *****************************************************/
/* ESR output data register */
typedef struct
{
    ureg32 ODR0:1;        /* [ 0: 0] Output bit 0 - RW */
    ureg32 ODR1:1;        /* [ 1: 1] Output bit 1 - RW */
    ureg32 reserved_2:30; /* [ 31:2] Internal reserved */
} ESR_ODR_Bits;

/* ESR output data set reset register */
typedef struct
{
    ureg32 BR0:1;          /* [ 0: 0] IO0 output data reset bit - W0 */
    ureg32 BR1:1;          /* [ 1: 1] IO1 output data reset bit - W0 */
    ureg32 reserved_2:14;  /* [15: 2] Internal reserved */
    ureg32 BS0:1;          /* [16:16] IO0 output data set bit - W0 */
    ureg32 BS1:1;          /* [17:17] IO1 output data set bit - W0 */
    ureg32 reserved_18:14; /* [31:18] Internal reserved */
} ESR_BSRR_Bits;

/* ESR input/output control register */
typedef struct
{
    ureg32 SEL0:3;         /* [ 2: 0] IO0 output multiplexing function selection - RW */
    ureg32 reserved_3:2;   /* [ 4: 3] Internal reserved */
    ureg32 OD0:1;          /* [ 5: 5] IO0 output push-pull/open-drain control - RW */
    ureg32 ENO0:1;         /* [ 6: 6] IO0 digital output channel enable control - RW */
    ureg32 DSI0:1;         /* [ 7: 7] IO0 digital input channel shutdown control - RW */
    ureg32 SEL1:3;         /* [10: 8] IO1 output multiplexing function selection - RW */
    ureg32 reserved_11:2;  /* [12: 11] Internal reserved */
    ureg32 OD1:1;          /* [13:13] IO1 output push-pull/open-drain control - RW */
    ureg32 ENO1:1;         /* [14:14] IO1 digital output channel enable control - RW */
    ureg32 DSI1:1;         /* [15:15] IO1 digital input channel shutdown control - RW */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} ESR_CTR0_Bits;

/* ESR input data register */
typedef struct
{
    ureg32 IDR0:1;        /* [ 0: 0] IO0 input data - RH */
    ureg32 IDR1:1;        /* [ 1: 1] IO1 input data - RH */
    ureg32 reserved_2:30; /* [31: 2] Internal reserved */
} ESR_IDR_Bits;

/* ESR drive mode control register */
typedef struct
{
    ureg32 DR0:1;         /* [ 0: 0] IO0 pad drive strength selection - RW */
    ureg32 IS0:1;         /* [ 1: 1] IO0 Input Mode Selection - RW */
    ureg32 SR0:1;         /* [ 2: 2] IO0 slew rate enable/disable - RW */
    ureg32 PL0:1;         /* [ 3: 3] IO0 pad level (AL, TTL) selection - RW */
    ureg32 DR1:1;         /* [ 4: 4] IO1 pad drive strength selection - RW */
    ureg32 IS1:1;         /* [ 5: 5] IO1 Input Mode Selection - RW */
    ureg32 SR1:1;         /* [ 6: 6] IO1 slew rate enable/disable - RW */
    ureg32 PL1:1;         /* [ 7: 7] IO1 pad level (AL, TTL) selection - RW */
    ureg32 reserved_8:24; /* [ 31: 8] Internal reserved */
} ESR_DSR0_Bits;

/* ESR digital function register */
typedef struct
{
    ureg32 DFR0:2;        /* [ 1: 0] IO0 digital function configure - RW */
    ureg32 DFR1:2;        /* [ 3: 2] IO1 digital function configure - RW */
    ureg32 reserved_4:28; /* [31: 4] Internal reserved */
} ESR_DFR_Bits;

/* ESR hardware control register */
typedef struct
{
    ureg32 SEL0:2;        /* [ 1: 0] IO0 hardware control select - RW */
    ureg32 SEL1:2;        /* [ 3: 2] IO1 hardware control select - RW */
    ureg32 reserved_4:28; /* [31: 4] Internal reserved */
} ESR_HWCR_Bits;

/* ESR pull select register */
typedef struct
{
    ureg32 PS0:2;         /* [ 1: 0] IO0 pull select - RW */
    ureg32 PS1:2;         /* [ 3: 2] IO1 pull select - RW */
    ureg32 reserved_4:28; /* [31: 4] Internal reserved */
} ESR_PSR_Bits;

/* ESR output data bit set register 0 */
typedef struct
{
    ureg32 reserved_0:16;  /* [15: 0] Internal reserved */
    ureg32 BS0:1;          /* [16:16] IO0 output data set bit - W0 */
    ureg32 BS1:1;          /* [17:17] IO1 output data set bit - W0 */
    ureg32 reserved_18:14; /* [31:18] Internal reserved */
} ESR_BSR0_Bits;

/* ESR output data bit reset register 0 */
typedef struct
{
    ureg32 BR0:1;         /* [ 0: 0] IO0 output data reset bit - W0 */
    ureg32 BR1:1;         /* [ 1: 1] IO1 output data reset bit - W0 */
    ureg32 reserved_2:30; /* [31: 2] Internal reserved */
} ESR_BRR0_Bits;

/* ESR output data bit set register */
typedef struct
{
    ureg32 reserved_0:16;  /* [15: 0] Internal reserved */
    ureg32 BS0:1;          /* [16:16] IO0 output data set bit - W0 */
    ureg32 BS1:1;          /* [17:17] IO1 output data set bit - W0 */
    ureg32 reserved_18:14; /* [31:18] Internal reserved */
} ESR_BSR_Bits;

/* ESR output data bit reset register */
typedef struct
{
    ureg32 BR0:1;         /* [ 0: 0] IO0 output data reset bit - W0 */
    ureg32 BR1:1;         /* [ 1: 1] IO1 output data reset bit - W0 */
    ureg32 reserved_2:30; /* [31: 2] Internal reserved */
} ESR_BRR_Bits;

/* ESR error status register */
typedef struct
{
    ureg32 SFRRDN:1;       /* [0:0] SFR redundant error - RWH */
    ureg32 reserved_1:3;   /* [3:1] Internal reserved */
    ureg32 SFRACC:1;       /* [4:4] SFR invalid access error - RWH */
    ureg32 reserved_5:27;  /* [31:5] Internal reserved */
} ESR_ERSTS_Bits;

/* ESR error status mask register */
typedef struct
{
    ureg32 SFRRDN:1;       /* [0:0] SFR redundant error mask - RW */
    ureg32 reserved_1:3;   /* [3:1] Internal reserved */
    ureg32 SFRACC:1;       /* [4:4] SFR invalid access error mask - RW */
    ureg32 reserved_5:27;  /* [31:5] Internal reserved */
} ESR_ERRMSK_Bits;

/* ESR port output configure register */
typedef struct
{
    ureg32 ARI:1;         /* [ 0: 0] Application reset indicator - RH */
    ureg32 ARC:1;         /* [ 1: 1] Application reset indicator clear - W1 */
    ureg32 MSKI:1;        /* [ 2: 2] Application reset indicator - RH */
    ureg32 MSKC:1;        /* [ 3: 3] Application reset indicator - RH */
    ureg32 reserved_2:28; /* [31: 4] Internal reserved */
} ESR_OCFG_Bits;

/******************************************************* RXMUX *******************************************************/
/* RXMUX */
typedef struct
{
    ureg32 INSEL0:4; /* [ 3: 0] Input multiplexer select 0 - RW */
    ureg32 INSEL1:4; /* [ 7: 4] Input multiplexer select 1 - RW */
    ureg32 INSEL2:4; /* [11: 8] Input multiplexer select 2 - RW */
    ureg32 INSEL3:4; /* [15:12] Input multiplexer select 3 - RW */
    ureg32 INSEL4:4; /* [19:16] Input multiplexer select 4 - RW */
    ureg32 INSEL5:4; /* [23:20] Input multiplexer select 5 - RW */
    ureg32 INSEL6:4; /* [27:24] Input multiplexer select 6 - RW */
    ureg32 INSEL7:4; /* [32:28] Input multiplexer select 7 - RW */
} RXMUX_INSEL_Bits;

/* RXMUX PSI5RXSEL */
typedef struct
{
    ureg32 RX0SEL:2;       /* [1:0] Receive select for PSI5RX - RW */
    ureg32 reserved_1:2;   /* [3:2] Internal reserved - RO */
    ureg32 RX1SEL:2;       /* [5:4] Receive select for PSI5RX - RW */
    ureg32 reserved_6:2;   /* [7:6] Internal reserved - RO */
    ureg32 RX2SEL:2;       /* [9:8] Receive select for PSI5RX - RW */
    ureg32 reserved_10:2;  /* [11:10] Internal reserved - RO */
    ureg32 RX3SEL:2;       /* [13:12] Receive select for PSI5RX - RW */
    ureg32 reserved_14:18; /* [31:14] Internal reserved - RO */
/* #Violation: port_register_h_REF_1 */
} RXMUX_PSI5RXSEL_Bits;

/**********************************************************************************************************************
 *                                           PORT Register Union Definitions
 *********************************************************************************************************************/
/**************************************************** General IO *****************************************************/
/* Port n output data register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;        /* Unsigned access */
    PORT_ODR_Bits B; /* Bitfield access */
} PORT_ODR;

/* Port n output data set reset register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;         /* Unsigned access */
    PORT_BSRR_Bits B; /* Bitfield access */
} PORT_BSRR;

/* Port n input/output control register 0 */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;         /* Unsigned access */
    PORT_CTR0_Bits B; /* Bitfield access */
} PORT_CTR0;

/* Port n input/output control register 4 */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;         /* Unsigned access */
    PORT_CTR4_Bits B; /* Bitfield access */
} PORT_CTR4;

/* Port n input/output control register 8 */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;         /* Unsigned access */
    PORT_CTR8_Bits B; /* Bitfield access */
} PORT_CTR8;

/* Port n input/output control register 12 */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;          /* Unsigned access */
    PORT_CTR12_Bits B; /* Bitfield access */
} PORT_CTR12;

/* Port n input data register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;        /* Unsigned access */
    PORT_IDR_Bits B; /* Bitfield access */
} PORT_IDR;

/* Port n STTL Control Register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;         /* Unsigned access */
    PORT_STTL_Bits B; /* Bitfield access */
} PORT_STTL;

/* Port n pad drive mode control register 0 */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;         /* Unsigned access */
    PORT_DSR0_Bits B; /* Bitfield access */
} PORT_DSR0;

/* Port n pad drive mode control register 8 */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;         /* Unsigned access */
    PORT_DSR8_Bits B; /* Bitfield access */
} PORT_DSR8;

/* Port n emergency stop register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;        /* Unsigned access */
    PORT_ESR_Bits B; /* Bitfield access */
} PORT_ESR;

/* Port n pin function select control register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;        /* Unsigned access */
    PORT_DFR_Bits B; /* Bitfield access */
} PORT_DFR;

/* Port n pin controller select register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;         /* Unsigned access */
    PORT_HWCR_Bits B; /* Bitfield access */
} PORT_HWCR;

/* Port n pin pull-up and pull-down select register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;        /* Unsigned access */
    PORT_PSR_Bits B; /* Bitfield access */
} PORT_PSR;

/* Port n output data bit set register 0 */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;         /* Unsigned access */
    PORT_BSR0_Bits B; /* Bitfield access */
} PORT_BSR0;

/* Port n output data bit set register 4 */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;         /* Unsigned access */
    PORT_BSR4_Bits B; /* Bitfield access */
} PORT_BSR4;

/* Port n output data bit set register 8   */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;         /* Unsigned access */
    PORT_BSR8_Bits B; /* Bitfield access */
} PORT_BSR8;

/* Port n output data bit set register 12   */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;          /* Unsigned access */
    PORT_BSR12_Bits B; /* Bitfield access */
} PORT_BSR12;

/* Port n output data bit reset register 0   */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;         /* Unsigned access */
    PORT_BRR0_Bits B; /* Bitfield access */
} PORT_BRR0;

/* Port n output data bit reset register 4   */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;         /* Unsigned access */
    PORT_BRR4_Bits B; /* Bitfield access */
} PORT_BRR4;

/* Port n output data bit reset register 8   */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;         /* Unsigned access */
    PORT_BRR8_Bits B; /* Bitfield access */
} PORT_BRR8;

/* Port n output data bit reset register 12   */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;          /* Unsigned access */
    PORT_BRR12_Bits B; /* Bitfield access */
} PORT_BRR12;

/* Port n output data set register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;        /* Unsigned access */
    PORT_BSR_Bits B; /* Bitfield access */
} PORT_BSR;

/* Port n output data bit reset register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;        /* Unsigned access */
    PORT_BRR_Bits B; /* Bitfield access */
} PORT_BRR;

/* Port n LVDS pad control register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;          /* Unsigned access */
    PORT_LVDSR_Bits B; /* Bitfield access */
} PORT_LVDSR;

/* Port n error status register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;          /* Unsigned access */
    PORT_ERSTS_Bits B; /* Bitfield access */
} PORT_ERSTS;

/* Port n error status mask register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;           /* Unsigned access */
    PORT_ERRMSK_Bits B; /* Bitfield access */
} PORT_ERRMSK;

/* Port n backup request register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;              /* Unsigned access */
    PORT_BACKUPREQ_Bits B; /* Bitfield access */
} PORT_BACKUPREQ;

/* Port n backup clear register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;              /* Unsigned access */
    PORT_BACKUPCLR_Bits B; /* Bitfield access */
} PORT_BACKUPCLR;

/* Port n backup active status register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;              /* Unsigned access */
    PORT_BACKUPSTS_Bits B; /* Bitfield access */
} PORT_BACKUPSTS;

/******************************************************* ESR IO ******************************************************/
/* ESR port output data register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;       /* Unsigned access */
    ESR_ODR_Bits B; /* Bitfield access */
} ESR_ODR;

/* ESR port output data bit set reset register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;        /* Unsigned access */
    ESR_BSRR_Bits B; /* Bitfield access */
} ESR_BSRR;

/* ESR port input output control register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;        /* Unsigned access */
    ESR_CTR0_Bits B; /* Bitfield access */
} ESR_CTR0;

/* ESR port input data register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;       /* Unsigned access */
    ESR_IDR_Bits B; /* Bitfield access */
} ESR_IDR;

/* ESR port pad driver mode register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;        /* Unsigned access */
    ESR_DSR0_Bits B; /* Bitfield access */
} ESR_DSR0;

/* ESR port pin function decision control register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;       /* Unsigned access */
    ESR_DFR_Bits B; /* Bitfield access */
} ESR_DFR;

/* ESR port pin controller select register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;        /* Unsigned access */
    ESR_HWCR_Bits B; /* Bitfield access */
} ESR_HWCR;

/* ESR port pull-up and pull-down selection register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;       /* Unsigned access */
    ESR_PSR_Bits B; /* Bitfield access */
} ESR_PSR;

/* ESR port output data bit set register 0 */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;        /* Unsigned access */
    ESR_BSR0_Bits B; /* Bitfield access */
} ESR_BSR0;

/* ESR port output data bit reset register 0 */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;        /* Unsigned access */
    ESR_BRR0_Bits B; /* Bitfield access */
} ESR_BRR0;

/* ESR port output data bit set register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;       /* Unsigned access */
    ESR_BSR_Bits B; /* Bitfield access */
} ESR_BSR;

/* ESR port output data bit reset register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;       /* Unsigned access */
    ESR_BRR_Bits B; /* Bitfield access */
} ESR_BRR;

/* ESR error status register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;          /* Unsigned access */
    ESR_ERSTS_Bits B;  /* Bitfield access */
} ESR_ERSTS;

/* ESR error status mask register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;           /* Unsigned access */
    ESR_ERRMSK_Bits B;  /* Bitfield access */
} ESR_ERRMSK;

/* ESR port output configure register */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;        /* Unsigned access */
    ESR_OCFG_Bits B; /* Bitfield access */
} ESR_OCFG;

/******************************************************* RXMUX *******************************************************/
/* RXMUX INSEL */
typedef union
/* #Violation: port_register_h_REF_2 */
{
    uint32 U;           /* Unsigned access */
    RXMUX_INSEL_Bits B; /* Bitfield access */
} RXMUX_INSEL;

/**********************************************************************************************************************
 *                                                PORT Register Structure
 *********************************************************************************************************************/
/* PORT register structure */
/* #Violation: port_register_h_REF_3 */
/* #Violation: port_register_h_REF_4 */
typedef volatile struct
{
    PORT_ODR ODR;                               /* 0x00, Port n output data register */
    PORT_BSRR BSRR;                             /* 0x04, Port output modification register */
    ureg32 RESERVED_8[2];                       /* 0x08, Internal reserved */
    PORT_CTR0 CTR0;                             /* 0x10, Port input/output control register 0 */
    PORT_CTR4 CTR4;                             /* 0x14, Port input/output control register 4 */
    PORT_CTR8 CTR8;                             /* 0x18, Port input/output control register 8 */
    PORT_CTR12 CTR12;                           /* 0x1C, Port input/output control register 12 */
    ureg32 RESERVED_20[1];                      /* 0x20, Internal reserved */
    PORT_IDR IDR;                               /* 0x24, Port input register */
    ureg32 RESERVED_28[2];                      /* 0x28, Internal reserved */
    PORT_STTL STTL;                             /* 0x30, Port STTL Control Register (THA6412 and THA6104 only) */
    ureg32 RESERVED_34[3];                      /* 0x34, Internal reserved */
    PORT_DSR0 DSR0;                             /* 0x40, Port pad driver mode 0 register */
    PORT_DSR8 DSR8;                             /* 0x44, Port pad driver mode 1 register */
    ureg32 RESERVED_48[2];                      /* 0x48, Internal reserved */
    PORT_ESR ESR;                               /* 0x50, Port emergency stop register */
    ureg32 RESERVED_54[3];                      /* 0x54, Internal reserved */
    PORT_DFR DFR;                               /* 0x60, Port pin function decision control register */
    PORT_HWCR HWCR;                             /* 0x64, Port pin controller select register */
    PORT_PSR PSR;                               /* 0x68, Port pin pull-device select register */
    ureg32 RESERVED_6C[1];                      /* 0x6C, Internal reserved */
    PORT_BSR0 BSR0;                             /* 0x70, Port output modification set register 0 */
    PORT_BSR4 BSR4;                             /* 0x74, Port output modification set register 4 */
    PORT_BSR8 BSR8;                             /* 0x78, Port output modification set register 8 */
    PORT_BSR12 BSR12;                           /* 0x7C, Port output modification set register 12 */
    PORT_BRR0 BRR0;                             /* 0x80, Port output modification clear register 0 */
    PORT_BRR4 BRR4;                             /* 0x84, Port output modification clear register 4 */
    PORT_BRR8 BRR8;                             /* 0x88, Port output modification clear register 8 */
    PORT_BRR12 BRR12;                           /* 0x8C, Port output modification clear register 12 */
    PORT_BSR BSR;                               /* 0x90, Port output modification set register */
    PORT_BRR BRR;                               /* 0x94, Port output modification clear register */
    ureg32 RESERVED_98[2];                      /* 0x98, Internal reserved */
    /* #Violation: port_register_h_REF_5 */
    /* #Violation: port_register_h_REF_6 */
    PORT_LVDSR LVDS[4];                         /* 0xA0, Port lvds pad control register 0 (THA6412 and THA6206 only) */
    ureg32 RESERVED_B0[4];                      /* 0xB0, Internal reserved */
    PORT_ERSTS ERSTS;                           /* 0xC0, Port error status register */
    PORT_ERRMSK ERRMSK;                         /* 0xC4, Port error status mask register */
    ureg32 RESERVED_C8[10];                     /* 0xC8, Internal reserved */
    PORT_BACKUPREQ BACKUPREQ;                   /* 0xF0, Port output modification set register (THA6412 and THA6104 only) */
    PORT_BACKUPCLR BACKUPCLR;                   /* 0xF4, Port output modification set register (THA6412 and THA6104 only) */
    PORT_BACKUPSTS BACKUPSTS;                   /* 0xF8, Port output modification set register (THA6412 and THA6104 only) */
} PORT_MODULE;

/* ESR port register structure */
typedef volatile struct
{
    ESR_ODR ODR;            /* 0x00, ESR output data register */
    ESR_BSRR BSRR;          /* 0x04, ESR Output Data Bit Set Reset Register */
    ureg32 RESERVED_8[2];   /* 0x08, Internal reserved */
    ESR_CTR0 CTR0;          /* 0x10, ESR Control Register 0 */
    ureg32 RESERVED_14[4];  /* 0x14, Internal reserved */
    ESR_IDR IDR;            /* 0x24, ESR Input Data Register */
    ureg32 RESERVED_28[6];  /* 0x28, Internal reserved */
    ESR_DSR0 DSR0;          /* 0x40, ESR Pad Driver Select Register 0 */
    ureg32 RESERVED_44[7];  /* 0x44, Internal reserved */
    ESR_DFR DFR;            /* 0x60, ESR Digital Function Register */
    ESR_HWCR HWCR;          /* 0x64, ESR Hardware Control Register */
    ESR_PSR PSR;            /* 0x68, ESR Pull Select Register */
    ureg32 RESERVED_6C[1];  /* 0x6C, Internal reserved */
    ESR_BSR0 BSR0;          /* 0x70, ESR Output Data Bit Set Register 0 */
    ureg32 RESERVED_74[3];  /* 0x74, Internal reserved */
    ESR_BRR0 BRR0;          /* 0x80, ESR Output Data Reset Register 0 */
    ureg32 RESERVED_84[3];  /* 0x84, Internal reserved */
    ESR_BSR BSR;            /* 0x90, ESR Output Data Bit Set Register */
    ESR_BRR BRR;            /* 0x94, ESR Output Data Reset Register */
    ureg32 RESERVED_98[10]; /* 0x98, Internal reserved */
    ESR_ERSTS ERSTS;        /* 0xC0, ESR error status register */
    ESR_ERRMSK ERRMSK;      /* 0xC4, ESR error status mask register */
    ureg32 RESERVED_C8[2];  /* 0xC8, Internal reserved */
    ESR_OCFG OCFG;          /* 0xD0, ESR Output Configuration Register */
} PORT_ESR_MODULE;

/* RXMUX register structure */
typedef volatile struct
{
    RXMUX_INSEL INSEL[PORT_RXMUX_MODU_CNT]; /* RXMUX input select register */
} PORT_RXMUX_MODULE;
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                                  PORT Module Object
 *********************************************************************************************************************/

#endif /* PORT_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
