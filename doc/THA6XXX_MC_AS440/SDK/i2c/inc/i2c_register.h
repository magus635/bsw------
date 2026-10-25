/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    i2c_register.h
 * Author:      01107
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all definitions of I2C module registers.
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#i2c_register_h_REF_1:MISRAC2012-Rule-19.2; 
* Justification:Using unions for bit-field access to registers
*
*#i2c_register_h_REF_2:MISRAC2012-Dir-4.8;
* Justification:Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#i2c_register_h_REF_3:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity;
*/
#ifndef I2C_REGISTER_H_
#define I2C_REGISTER_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "Platform_Types.h"
#include "regtypes.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                        I2C Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* I2C Control Register - 1 */
typedef volatile struct
{
    ureg32 PE:1;           /* [0:0] Peripheral enable - RW */
    ureg32 reserved_4:4;   /* [4:1] Internal reserved */
    ureg32 ENPEC:1;        /* [5:5] PEC enable - RW */
    ureg32 ENGC:1;         /* [6:6] General call enable - RW */
    ureg32 NOSTRETCH:1;    /* [7:7] Clock stretching disable (Slave mode) - RW */
    ureg32 START:1;        /* [8:8] Start generation - RW */
    ureg32 STOP:1;         /* [9:9] Stop generation - RW */
    ureg32 ACK:1;          /* [10:10] Acknowledge enable - RW */
    ureg32 POS:1;          /* [11:11] Acknowledge/PEC Position(for data reception) - RW */
    ureg32 PEC:1;          /* [12:12] Packet error checking - RW */
    ureg32 reserved_2:2;   /* [14:13] Internal reserved */
    ureg32 SWRST:1;        /* [15:15] Software reset - RW */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} I2C_CR1_Bits;

/* I2C Control Register - 2 */
typedef volatile struct
{
    ureg32 FREQ:7;         /* [6:0] Peripheral clock frequency - RW */
    ureg32 reserved_1:1;   /* [7:7] Internal reserved */
    ureg32 ITERREN:1;      /* [8:8] Error interrupt enable - RW */
    ureg32 ITEVTEN:1;      /* [9:9] Event interrupt enable - RW */
    ureg32 ITBUFEN:1;      /* [10:10] Buffer interrupt enable - RW */
    ureg32 DMAEN:1;        /* [11:11] DMA requests enable - RW */
    ureg32 reserved_2:2;   /* [13:12] Internal reserved */
    ureg32 IRQ:1;          /* [14:14] Interrupt enable - RW */
    ureg32 ADDMREV:1;      /* [15:15] 10 bit host receiving instructions - RW */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} I2C_CR2_Bits;

/* I2C Own address register 1 */
typedef volatile struct
{
    ureg32 ADD0:1;         /* [0:0] Interface address(0 is 7bit, 1 is 10bit)- RW */
    ureg32 ADD71:7;        /* [7:1] Interface address(7bit address) - RW */
    ureg32 ADD98:2;        /* [9:8] Interface address(10bit address) - RW */
    ureg32 reserved_5:5;   /* [14:10] Internal reserved */
    ureg32 ADDMODE:1;      /* [15:15] Addressing mode - RW */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} I2C_OAR1_Bits;

/* I2C Own address register 2  */
typedef volatile struct
{
    ureg32 ENDUAL:1;       /* [0:0] Dual addressing mode enable - RW */
    ureg32 ADD2:7;         /* [7:1] Interface address in dual - RW */
    ureg32 reserved_24:24; /* [31:8] Internal reserved */
} I2C_OAR2_Bits;

/* I2C Data register */
typedef struct
{
    ureg32 DR:8;           /* [7:0]  8-bit data register - RW */
    ureg32 reserved_24:24; /* [31:8] Internal reserved */
} I2C_DR_Bits;

/* I2C Status register 1  */
typedef struct
{
    ureg32 SB:1;           /* [0:0] Start bit (Master mode) - R */
    ureg32 ADDR:1;         /* [1:1] Address sent (master mode)/matched (slave mode) - R */
    ureg32 BTF:1;          /* [2:2] Byte transfer finished - R */
    ureg32 ADD10:1;        /* [3:3] 10-bit header sent (Master mode) - R */
    ureg32 STOPF:1;        /* [4:4] Stop detection (slave mode)  - R */
    ureg32 BREQ:1;         /* [5:5] FIFO burst request - Rc W0 */
    ureg32 RXNE:1;         /* [6:6] Data register not empty (receivers) - R */
    ureg32 TXE:1;          /* [7:7] Data register empty (transmitters - R */
    ureg32 BERR:1;         /* [8:8] Bus error - Rc W0 */
    ureg32 ARLO:1;         /* [9:9] Arbitration lost  - Rc W0 */
    ureg32 AF:1;           /* [10:10] Acknowledge failure - Rc W0 */
    ureg32 OVR:1;          /* [11:11] Overrun/Underrun - Rc W0 */
    ureg32 PECERR:1;       /* [12:12] PEC Error in reception - Rc W0 */
    ureg32 reserved_19:19; /* [31:13] Internal reserved */
} I2C_SR1_Bits;

/* I2C Status register 2 */
typedef struct
{
    ureg32 MSL:1;          /* [0:0] Master/slave - R */
    ureg32 BUSY:1;         /* [1:1] Bus busy - R */
    ureg32 TRA:1;          /* [2:2] Transmitter/receiver - R */
    ureg32 reserved_1:1;   /* [3:3] Internal reserved */
    ureg32 GENCALL:1;      /* [4:4] General call address (Slave mode)  - R */
    ureg32 reserved_2:2;   /* [6:5] Internal reserved */
    ureg32 DUALF:1;        /* [7:7] Dual flag (Slave mode) - R */
    ureg32 PEC:8;          /* [15:8] Packet error checking register - R */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} I2C_SR2_Bits;

/* I2C Clock control register */
typedef struct
{
    ureg32 CCR:13;         /* [12:0] Clock control register in Fm/Sm mode (Master mode) - RW */
    ureg32 reserved_1:1;   /* [13:13] Internal reserved */
    ureg32 DUTY:1;         /* [14:14] DUTY, Fm mode duty cycle - RW */
    ureg32 FS:1;           /* [15:15] F/S:I2C master mode selection - RW */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} I2C_CCR_Bits;

/* I2C TRISE register */
typedef struct
{
    ureg32 TRISE:7;        /* [6:0] Maximum rise time in Fm/Sm/Hs mode (Master mode) - RW */
    ureg32 reserved_25:25; /* [31:7] Internal reserved */
} I2C_TRISE_Bits;

/* I2C Own address register 3 */
typedef struct
{
    ureg32 SHS_CMD:3;      /* [2:0] High speed host code received from mode - R */
    ureg32 reserved_16:29; /* [31:3] Internal reserved */
} I2C_OAR3_Bits;

/* I2C Clock control register 1 */
typedef struct
{
    ureg32 MHS_CCR:8;      /* [7:0] Clock controlled division coefficient in high-speed mode - RW */
    ureg32 reserved_7:7;   /* [14:8] Internal reserved */
    ureg32 MHS_START:1;    /* [15:15] Start signal in high-speed mode - RW */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} I2C_CCR1_Bits;

/* I2C status register 3  */
typedef struct
{
    ureg32 reserved_11:11;    /* [10:0]  Internal reserved */
    ureg32 CMD_MATCH:1;       /* [11:11] Slave mode, High speed mode 000001 matching - Rc W0 */
    ureg32 S_HS:1;            /* [12:12] Slave mode - R */
    ureg32 FS_HS:1;           /* [13:13] master mode - R */
    ureg32 SREQ:1;            /* [14:14] FIFO single request - Rc W0 */
    ureg32 reserved_17:17;    /* [31:15] Internal reserved */
} I2C_SR3_Bits;

/* I2C TX byte counter */
typedef struct
{
    ureg32 TX_CNT:15;         /* [14:0] I2C transmit bytes counter - Rc W0 */
    ureg32 reserved_17:17;    /* [31:15] Internal reserved */
} I2C_TX_CNT_Bits;

/* I2C control register 3 */
typedef struct
{
    ureg32 reserved_0:1;      /* [0:0] Internal reserved */
    ureg32 FIFOEN:1;          /* [1:1] FIFO mode enable - RW */
    ureg32 FFLS:1;            /* [2:2] FIFO fresh reset - RW */
    ureg32 RF_ALFULL:3;       /* [5:3] FIFO full water mark value - RW */
    ureg32 TF_ALEMPTY:3;      /* [8:6] FIFO empty water mark value - RW */
    ureg32 FC:1;              /* [9:9] FLOW SOURCE: I2C or DMA - RW */
    ureg32 reserved_1:1;      /* [10:10] Internal reserved */
    ureg32 ITFREQEN:1;        /* [11:11] FIFO interrupt request - RW */
    ureg32 ALIGN:2;           /* [13:12] FIFO align mode - RW */
    ureg32 BS:1;              /* [14:14] Burst size - RW */
    ureg32 MASK_IRQ:1;        /* [15:15] Reset when software is set - RW */
    ureg32 reserved_16:16;    /* [31:16] Internal reserved */
} I2C_CR3_Bits;

/* I2C control register 4 */
typedef struct
{
    ureg32 TBL:14;         /* [13:0] Transmit byte length without PEC - RW */
    ureg32 reserved_18:18; /* [31:14] Internal reserved */
} I2C_CR4_Bits;

/* I2C status register 4 */
typedef struct
{
    ureg32 RFUFL:1;        /* [0:0] The underflow flag of RX FIFO - Rc W0 */
    ureg32 reserved_1:2;   /* [2:1] Internal reserved */
    ureg32 TFOFL:1;        /* [3:3] the overflow flag of TX FIFO - Rc W0 */
    ureg32 reserved_28:28; /* [31:4] Internal reserved */
} I2C_SR4_Bits;

/* I2C RX bytes counter */
typedef struct
{
    ureg32 RX_CNT:15;         /* [14:0] The total number of received bytes - Rc W0 */
    ureg32 reserved_17:17;    /* [31:15] Internal reserved */
} I2C_RX_CNT_Bits;

/* I2C FIFO TX data register */
typedef struct
{
    ureg32 FTXD:32; /* [31:0] TX FIFO data register - W */
} I2C_FTXD_Bits;

/* I2C FIFO RX data register */
typedef struct
{
    ureg32 FRXD:32; /* [31:0] RX FIFO data register - R */
} I2C_FRXD_Bits;

/**********************************************************************************************************************
 *                                             I2C Register Definitions
 *********************************************************************************************************************/
/* I2C Control Register 1 */
typedef union
/* #Violation: i2c_register_h_REF_1 */
{
    uint32 U;
    I2C_CR1_Bits B;
} I2C_CR1;

/* I2C Control Register 2 */
typedef union
/* #Violation: i2c_register_h_REF_1 */
{
    uint32 U;
    I2C_CR2_Bits B;
} I2C_CR2;

/* I2C Own address register 1 */
typedef union
/* #Violation: i2c_register_h_REF_1 */
{
    uint32 U;
    I2C_OAR1_Bits B;
} I2C_OAR1;

/* I2C Own address register 2 */
typedef union
/* #Violation: i2c_register_h_REF_1 */
{
    uint32 U;
    I2C_OAR2_Bits B;
} I2C_OAR2;

/* I2C Data register */
typedef union
/* #Violation: i2c_register_h_REF_1 */
{
    uint32 U;
    I2C_DR_Bits B;
} I2C_DR;

/* I2C Status register 1 */
typedef union
/* #Violation: i2c_register_h_REF_1 */
{
    uint32 U;
    I2C_SR1_Bits B;
} I2C_SR1;

/* I2C Status register 2 */
typedef union
/* #Violation: i2c_register_h_REF_1 */
{
    uint32 U;
    I2C_SR2_Bits B;
} I2C_SR2;

/* I2C Clock control register */
typedef union
/* #Violation: i2c_register_h_REF_1 */
{
    uint32 U;
    I2C_CCR_Bits B;
} I2C_CCR;

/* I2C TRISE register */
typedef union
/* #Violation: i2c_register_h_REF_1 */
{
    uint32 U;
    I2C_TRISE_Bits B;
} I2C_TRISE;

/* I2C Own address register 3 */
typedef union
/* #Violation: i2c_register_h_REF_1 */
{
    uint32 U;
    I2C_OAR3_Bits B;
} I2C_OAR3;

/* I2C Clock control register 1 */
typedef union
/* #Violation: i2c_register_h_REF_1 */
{
    uint32 U;
    I2C_CCR1_Bits B;
} I2C_CCR1;

/* I2C status register 3  */
typedef union
/* #Violation: i2c_register_h_REF_1 */
{
    uint32 U;
    I2C_SR3_Bits B;
} I2C_SR3;

/* I2C TX byte counter */
typedef union
/* #Violation: i2c_register_h_REF_1 */
{
    uint32 U;
    I2C_TX_CNT_Bits B;
} I2C_TX_CNT;

/* I2C control register 3 */
typedef union
/* #Violation: i2c_register_h_REF_1 */
{
    uint32 U;
    I2C_CR3_Bits B;
} I2C_CR3;

/* I2C control register 4 */
typedef union
/* #Violation: i2c_register_h_REF_1 */
{
    uint32 U;
    I2C_CR4_Bits B;
} I2C_CR4;

/* I2C status register 4 */
typedef union
/* #Violation: i2c_register_h_REF_1 */
{
    uint32 U;
    I2C_SR4_Bits B;
} I2C_SR4;

/* I2C RX bytes counter */
typedef union
/* #Violation: i2c_register_h_REF_1 */
{
    uint32 U;
    I2C_RX_CNT_Bits B;
} I2C_RX_CNT;

/* I2C FIFO TX data register */
typedef union
/* #Violation: i2c_register_h_REF_1 */
{
    uint32 U;
    I2C_FTXD_Bits B;
} I2C_FTXD;

/* I2C FIFO RX data register */
typedef union
/* #Violation: i2c_register_h_REF_1 */
{
    uint32 U;
    I2C_FRXD_Bits B;
} I2C_FRXD;

/**********************************************************************************************************************
 *                                        I2C Register Configuration Structure
 *********************************************************************************************************************/
/* #Violation: i2c_register_h_REF_2 */
/* #Violation: i2c_register_h_REF_3 */
typedef volatile struct
{
    I2C_CR1 CR1;               /* 0x00 I2C Control Register 1 */
    I2C_CR2 CR2;               /* 0x04 I2C Control Register 2 */
    I2C_OAR1 OAR1;             /* 0x08 I2C Own address register 1 */
    I2C_OAR2 OAR2;             /* 0x0C I2C Own address register 2 */
    I2C_DR DR;                 /* 0x10 I2C Data register */
    I2C_SR1 SR1;               /* 0x14 I2C Status Register 1 */
    I2C_SR2 SR2;               /* 0x18 I2C Status Register 2 */
    I2C_CCR CCR;               /* 0x1C I2C Clock control register */
    I2C_TRISE TRISE;           /* 0x20 I2C Time-Out Control Register */
    I2C_OAR3 OAR3;             /* 0x24 I2C TRISE register */
    I2C_CCR1 CCR1;             /* 0x28 I2C Clock control register 1 */
    I2C_SR3 SR3;               /* 0x2C I2C Status Register 3 */
    I2C_TX_CNT TX_CNT;         /* 0x30 I2C TX bytes counter */
    I2C_CR3 CR3;               /* 0x34 I2C Control Register 3 */
    I2C_CR4 CR4;               /* 0x38 I2C Control Register 4 */
    I2C_SR4 SR4;               /* 0x3C I2C Status Register 4 */
    I2C_RX_CNT RX_CNT;         /* 0x40 I2C RX bytes counter */
    I2C_FTXD FTXD;             /* 0x44 I2C FIFO TX data register */
    I2C_FRXD FRXD;             /* 0x48 I2C FIFO RX data register */
} I2C_MODULE;

#endif /* I2C_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
