/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    fc_register.h
 * Author:      01254
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all definitions of FC module registers.
 *********************************************************************************************************************/
#ifndef FC_REGISTER_H_
#define FC_REGISTER_H_

/*
*#Violation Summary
*#fc_regiter_h_REF_1:MISRAC2012-Rule-19.2;
* Justification: Using unions for bit-field access to registers.
*/

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
/* Analog IP enable control register */
typedef volatile struct
{
    ureg32 ANAEN:1;       /* [0:0] analog IP enable control -RW */
    ureg32 reserved_1:31; /* [1:31] Reserved -R */
} FC_ANEN_Bits;

/* FC control register 0 */
typedef volatile struct
{
    ureg32 STCON:2;       /* [0:1] sample time control for fast comparisons -RW */
    ureg32 reserved_2:6;  /* [2:7] Reserved -R */
    ureg32 CHEGMODE:2;    /* [8:9] channel event generation -RW */
    ureg32 reserved_10:3; /* [10:12] Reserved -R */
    ureg32 CKDIVA:3;      /* [13:15] divider factor for the analog internal clock -RW */
    ureg32 reserved_16:4; /* [16:19] Reserved -R */
    ureg32 TRISEL:4;      /* [20:23] trigger input selection -RW */
    ureg32 TRILVL:1;      /* [24:24] trigger level -R */
    ureg32 reserved_25:3; /* [25:27] Reserved -R */
    ureg32 TRIMODE:2;     /* [28:29] trigger event generation mode control -RW */
    ureg32 reserved_30:2; /* [30:31] Reserved -R */
} FC_CON0_Bits;

/* FC control register 1 */
typedef volatile struct
{
    ureg32 TRINV:1;        /* [0:0] trigger invert selection -RW */
    ureg32 reserved_1:3;   /* [1:3] Reserved -R */
    ureg32 GCONMODE:2;     /* [4:5] gate control mode of reference value generation -RW */
    ureg32 reserved_6:2;   /* [6:7] Reserved -R */
    ureg32 CVCH:2;         /* [8:9] compare value input channel -RW */
    ureg32 reserved_10:2;  /* [10:11] Reserved -R */
    ureg32 CTCON:2;        /* [12:13] compare time control for fast comparisons -RW */
    ureg32 reserved_14:18; /* [14:31] Reserved -R */
} FC_CON1_Bits;

/* FC mode register */
typedef volatile struct
{
    ureg32 RAMPON:2;       /* [0:1] run control for ramp -RW */
    ureg32 reserved_2:2;   /* [2:3] Reserved -R */
    ureg32 RAMDIR:1;       /* [4:4] fast compare ramp direction -RW */
    ureg32 reserved_5:3;   /* [5:7] Reserved -R */
    ureg32 FCINTVL:8;      /* [8:15] fast compare interval -RW */
    ureg32 INTG:2;         /* [16:17] interrupt generation -RW */
    ureg32 reserved_18:2;  /* [18:19] Reserved -R */
    ureg32 REFG:2;         /* [20:21] reference value generation -RW */
    ureg32 reserved_22:10; /* [22:31] Reserved -R */
} FC_MODE_Bits;

/* FC reference value */
typedef volatile struct
{
    ureg32 REFVALUE:10;   /* [0:9] fast compare reference value -R */
    ureg32 reserved_10:6; /* [10:15] Reserved -R */
    ureg32 REFVALSW:10;   /* [16:25] software configured reference value -RW */
    ureg32 reserved_26:6; /* [26:31] Reserved -R */
} FC_REFVAL_Bits;

/* FC ramp register 0 */
typedef volatile struct
{
    ureg32 RAMPCMP0:10;   /* [0:9] fast compare ramp compare value 0 -RW */
    ureg32 reserved_10:6; /* [10:15] Reserved -R */
    ureg32 RAMPSTEP:8;    /* [16:23] fast compare ramp step width -RW */
    ureg32 reserved_24:8; /* [24:31] Reserved -R */
} FC_RAMP0_Bits;

/* FC ramp register 1 */
typedef volatile struct
{
    ureg32 RAMPCMP1:10;    /* [0:9] fast compare ramp compare value 1 -RW */
    ureg32 reserved_10:22; /* [10:31] Reserved -R */
} FC_RAMP1_Bits;

/* FC hysteresis register */
typedef volatile struct
{
    ureg32 LOWDELTA:10;   /* [0:9] lower delta value -RW */
    ureg32 reserved_10:6; /* [10:15] Reserved -R */
    ureg32 UPDELTA:10;    /* [16:25] upper delta value -RW */
    ureg32 reserved_26:6; /* [26:31] Reserved -R */
} FC_HYST_Bits;

/* Boundary flag register */
typedef volatile struct
{
    ureg32 BDFLAG:1;      /* [0:0] boundary flag -R */
    ureg32 BFSEL:1;       /* [1:1] boundary flag source select -R */
    ureg32 BFDAT:1;       /* [2:2] boundary flag alternate data -R */
    ureg32 BFOUTSEL:1;    /* [3:3] boundary out source select -RW */
    ureg32 BFACT:1;       /* [4:4] boundary flag activation select -RW */
    ureg32 reserved_5:3;  /* [5:7] Reserved -R */
    ureg32 BFINV:1;       /* [8:8] boundary flag inversion control -RW */
    ureg32 reserved_9:3;  /* [9:11] Reserved -R */
    ureg32 BFSW:2;        /* [12:13] boundary flag software control -RW */
    ureg32 reserved_14:2; /* [14:15] Reserved -R */
    ureg32 BFHW:1;        /* [16:16] boundary flag hardware control -RW */
    ureg32 BFRSW:1;       /* [17:17] boundary flag replaced by software configured value -RW */
    ureg32 reserved_18:6; /* [18:23] Reserved -R */
    ureg32 BFP:4;         /* [24:27] boundary flag pointer -RW */
    ureg32 CR:1;          /* [28:28] compare result -R */
    ureg32 reserved_29:2; /* [29:30] Reserved -R */
    ureg32 CRVF:1;        /* [31:31] compare result valid flag -R */
} FC_BDFL_Bits;

/* FC interrupt and DMA control register */
typedef volatile struct
{
    ureg32 INTST:1;        /* [0:0] interrupt status -RWH */
    ureg32 reserved_1:15;  /* [1:15] Reserved -R */
    ureg32 DMAEN:1;        /* [16:16] DMA enable -RW */
    ureg32 reserved_17:15; /* [17:31] Reserved -R */
} FC_FCINT_Bits;

/* Run control for compare channel */
typedef volatile struct
{
    ureg32 COMPEN:1;      /* [0:0] compare channel enable control -RW */
    ureg32 reserved_1:31; /* [1:31] Reserved -R */
} FC_FCON_Bits;

/* Safety mechanism enable register */
typedef volatile struct
{
    ureg32 REGSMEN:2;     /* [0:1] register bit redundancy safety mechanism enable -RW */
    ureg32 DMASMEN:2;     /* [2:3] DMA feedback timeout monitor safety mechanism enable -RW */
    ureg32 MONIEN:2;      /* [4:5] trigger signal time monitor safety mechanism enable -RW */
    ureg32 DMALSEN:2;     /* [6:7] DMA request loss monitor mechanism enable -RW */
    ureg32 reserved_8:24; /* [8:31] Reserved -R */
} FC_SMEN_Bits;

/* Alarm register */
typedef volatile struct
{
    ureg32 SMENALM:1;     /* [0:0] SMEN register alarm -RH */
    ureg32 DMALM:1;       /* [1:1] DMA feedback timeout monitor safety mechanism alarm -RH */
    ureg32 MONIALM:1;     /* [2:2] trigger signal timeout monitor safety mechanism alarm -RH */
    ureg32 EALM:1;        /* [3:3] ENDINIT alarm -RH */
    ureg32 SEALM:1;       /* [4:4] safety ENDINIT alarm -RH */
    ureg32 CLRALM:1;      /* [5:5] ALMCLR register alarm -RH */
    ureg32 FAULTALM:1;    /* [6:6] FAULTEN register alarm -RH */
    ureg32 CVCHALM:1;     /* [7:7] CVCH register alarm -RH */
    ureg32 DMALSALM:1;    /* [8:8] DMA request loss monitor mechanism alarm -RH */
    ureg32 reserved_9:23; /* [9:31] Reserved -R */
} FC_ALM_Bits;

/* Alarm clear register */
typedef volatile struct
{
    ureg32 REGSMCLR:2;     /* [0:1] register two bits redundancy safety mechanism alarm clear -W */
    ureg32 DMACLR:2;       /* [2:3] DMA feedback timeout monitor safety mechanism alarm clear -W */
    ureg32 MONICLR:2;      /* [4:5] trigger signal timeout monitor safety mechanism alarm clear -W */
    ureg32 ECLR:2;         /* [6:7] ENDINIT alarm Clear -W */
    ureg32 SECLR:2;        /* [8:9] safety ENDINIT alarm Clear -W */
    ureg32 DMALSCLR:2;     /* [10:11] DMA Request Loss Alarm Clear -W */
    ureg32 reserved_12:20; /* [12:31] Reserved -R */
} FC_ALMCLR_Bits;

/* Analog IP state */
typedef volatile struct
{
    ureg32 COMFL:1;       /* [0:0] analog IP compare flag -RW */
    ureg32 ANAINIT:1;     /* [1:1] analog IP initialize flag -RW */
    ureg32 reserved_2:30; /* [2:31] Reserved -R */
} FC_ANSTS_Bits;

/* Mask register */
typedef volatile struct
{
    ureg32 BEMASK:1;      /* [0:0] bus error mask -RW */
    ureg32 INTMASK:1;     /* [1:1] interrupt mask -RW */
    ureg32 CINTMASK:1;    /* [2:2] common interrupt mask -RW */
    ureg32 reserved_3:29; /* [3:31] Reserved -R */
} FC_MASKR_Bits;

/**********************************************************************************************************************
 *                                              FC Register Definitions
 *********************************************************************************************************************/
/* Analog IP enable control register */
typedef union
/* #Violation: fc_regiter_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    FC_ANEN_Bits B; /* Bit-Field access */
} FC_ANEN;

/* FC control register 0*/
typedef union
/* #Violation: fc_regiter_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    FC_CON0_Bits B; /* Bit-Field access */
} FC_CON0;

/* FC control register 1 */
typedef union
/* #Violation: fc_regiter_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    FC_CON1_Bits B; /* Bit-Field access */
} FC_CON1;

/* FC mode register */
typedef union
/* #Violation: fc_regiter_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    FC_MODE_Bits B; /* Bit-Field access */
} FC_MODE;

/* FC reference value */
typedef union
/* #Violation: fc_regiter_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    FC_REFVAL_Bits B; /* Bit-Field access */
} FC_REFVAL;

/* FC ramp register 0 */
typedef union
/* #Violation: fc_regiter_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    FC_RAMP0_Bits B; /* Bit-Field access */
} FC_RAMP0;

/* FC ramp register 1 */
typedef union
/* #Violation: fc_regiter_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    FC_RAMP1_Bits B; /* Bit-Field access */
} FC_RAMP1;

/* FC hysteresis register */
typedef union
/* #Violation: fc_regiter_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    FC_HYST_Bits B; /* Bit-Field access */
} FC_HYST;

/* Boundary flag register */
typedef union
/* #Violation: fc_regiter_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    FC_BDFL_Bits B; /* Bit-Field access */
} FC_BDFL;

/* FC interrupt and DMA control register */
typedef union
/* #Violation: fc_regiter_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    FC_FCINT_Bits B; /* Bit-Field access */
} FC_FCINT;

/* Run control for compare channel */
typedef union
/* #Violation: fc_regiter_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    FC_FCON_Bits B; /* Bit-Field access */
} FC_FCON;

/* Safety mechanism enable register */
typedef union
/* #Violation: fc_regiter_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    FC_SMEN_Bits B; /* Bit-Field access */
} FC_SMEN;

/* Alarm register */
typedef union
/* #Violation: fc_regiter_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    FC_ALM_Bits B; /* Bit-Field access */
} FC_ALM;

/* Alarm clear register */
typedef union
/* #Violation: fc_regiter_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    FC_ALMCLR_Bits B; /* Bit-Field access */
} FC_ALMCLR;

/* Analog IP state */
typedef union
/* #Violation: fc_regiter_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    FC_ANSTS_Bits B; /* Bit-Field access */
} FC_ANSTS;

/* Mask register */
typedef union
/* #Violation: fc_regiter_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    FC_MASKR_Bits B; /* Bit-Field access */
} FC_MASKR;
/**********************************************************************************************************************
 *                                        FC Register Configuration Structure
 *********************************************************************************************************************/
/* FC Module Register */
typedef volatile struct
{
    FC_ANEN ANEN;          /* 0x0, Analog IP enable control register */
    FC_CON0 CON0;          /* 0x4, FC control register 0 */
    FC_CON1 CON1;          /* 0x8, FC control register 1 */
    FC_MODE MODE;          /* 0xC, FC mode register */
    FC_REFVAL REFVAL;      /* 0x10, FC reference value */
    FC_RAMP0 RAMP0;        /* 0x14, FC ramp register 0 */
    FC_RAMP1 RAMP1;        /* 0x18, FC ramp register 1 */
    FC_HYST HYST;          /* 0x1C, FC hysteresis register */
    FC_BDFL BDFL;          /* 0x20, Boundary flag register */
    FC_FCINT FCINT;        /* 0x24, FC interrupt and DMA control register */
    FC_FCON FCON;          /* 0x28, Run control for compare channel */
    FC_SMEN SMEN;          /* 0x2C, Safety mechanism enable register */
    FC_ALM ALM;            /* 0x30, Alarm register */
    FC_ALMCLR ALMCLR;      /* 0x34, Alarm clear register */
    ureg32 RESERVED_38;    /* 0x38, \internal Reserved */
    ureg32 MONICNT;        /* 0x3C, Load value of the pulse monitor counter register */
    ureg32 DMACNT;         /* 0x40, DMA monitor counter register */
    FC_ANSTS ANSTS;        /* 0x44, Analog IP state */
    FC_MASKR MASKR;        /* 0x48, Mask register */
} FC_MODULE;

#endif /* FC_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
