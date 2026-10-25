/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName   : exti_register.h
 * Author     : 01077
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all definitions of EXTI module registers.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
* #Violation Summary
*
*#exti_register_h_REF_1:MISRAC2012-Rule-19.2;
* Justification: Union is used to define the registers type.
*
*/
#ifndef EXTI_REGISTER_H_
#define EXTI_REGISTER_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "regtypes.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                        EXTI Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* External input filter register */
typedef struct
{
    ureg32 FLTEQ0A:1;     /* [0:0]   Filter enable for REQ0A - RW */
    ureg32 FLTEQ5A:1;     /* [1:1]   Filter enable for REQ5A - RW */
    ureg32 FLTEQ2A:1;     /* [2:2]   Filter enable for REQ2A - RW */
    ureg32 FLTEQ3A:1;     /* [3:3]   Filter enable for REQ3A - RW */
    ureg32 FLTEQ0C:1;     /* [4:4]   Filter enable for REQ0C - RW */
    ureg32 FLTEQ1C:1;     /* [5:5]   Filter enable for REQ1C - RW */
    ureg32 FLTEQ3C:1;     /* [6:6]   Filter enable for REQ3C - RW */
    ureg32 FLTEQ2C:1;     /* [7:7]   Filter enable for REQ2C - RW */
    ureg32 FLTEQ4A:1;     /* [8:8]   Filter enable for REQ4A - RW */
    ureg32 FLTEQ6A:1;     /* [9:9]   Filter enable for REQ6A - RW */
    ureg32 FLTEQ1A:1;     /* [10:10] Filter enable for REQ1A - RW */
    ureg32 FLTEQ7A:1;     /* [11:11] Filter enable for REQ7A - RW */
    ureg32 FLTEQ6D:1;     /* [12:12] Filter enable for REQ6D - RW */
    ureg32 FLTEQ4D:1;     /* [13:13] Filter enable for REQ4D - RW */
    ureg32 FLTEQ2B:1;     /* [14:14] Filter enable for REQ2B - RW */
    ureg32 FLTEQ3B:1;     /* [15:15] Filter enable for REQ3B - RW */
    ureg32 FLTEQ7C:1;     /* [16:16] Filter enable for REQ7C - RW */
    ureg32 FLTEQ6B:1;     /* [17:17] Filter enable for REQ6B - RW */
    ureg32 FLTEQ7B:1;     /* [18:18] Filter enable for REQ7B - RW */
    ureg32 reserved_19:5; /* [23:19] Internal reserved */
    ureg32 FDCDFSC:4;     /* [27:24] Frequency division coefficient of digital filter sampling clock - RW */
    ureg32 DFDTH:4;       /* [31:28] Digital filter depth - RW */
} EXTI_EXIFLT_Bits;

/* ETIPCj(j = 0,1,2,3), external input channel register */
typedef struct
{
    ureg32 reserved_0:4;  /* [3:0]   Internal reserved */
    ureg32 ETIPS0:3;      /* [6:4]   ETL(2j) external input selection 0 - RW */
    ureg32 reserved_7:1;  /* [7:7]   Internal reserved */
    ureg32 FAEEN0:1;      /* [8:8]   ETL(2j) falling edge enable 0 - RW */
    ureg32 RIEEN0:1;      /* [9:9]   ETL(2j) rising edge enable 0 - RW */
    ureg32 LEDEEN0:1;     /* [10:10] ETL(2j) level detection enable 0 - RW */
    ureg32 ETIPEN0:1;     /* [11:11] ETL(2j) external input enable 0 - RW */
    ureg32 INNOP0:3;      /* [14:12] ETL(2j) input node pointer - RW */
    ureg32 reserved_15:5; /* [19:15] Internal reserved */
    ureg32 ETIPS1:3;      /* [22:20] ETL(2j+1) external input selection 1 - RW */
    ureg32 reserved_23:1; /* [23:23] Internal reserved */
    ureg32 FAEEN1:1;      /* [24:24] ETL(2j+1) falling edge enable 1 - RW */
    ureg32 RIEEN1:1;      /* [25:25] ETL(2j+1) rising edge enable 1 - RW */
    ureg32 LEDEEN1:1;     /* [26:26] ETL(2j+1) level detection enable 1 - RW */
    ureg32 ETIPEN1:1;     /* [27:27] ETL(2j+1) external input enable 1 - RW */
    ureg32 INNOP1:3;      /* [30:28] ETL(2j+1) input node pointer - RW */
    ureg32 reserved_31:1; /* [31:31] Internal reserved */
} EXTI_ETIPC_Bits;

/* External input flag register */
typedef struct
{
    ureg32 EIFBIC0:1;     /* [0:0]  External event flag of channel 0 - R */
    ureg32 EIFBIC1:1;     /* [1:1]  External event flag of channel 1 - R */
    ureg32 EIFBIC2:1;     /* [2:2]  External event flag of channel 2 - R */
    ureg32 EIFBIC3:1;     /* [3:3]  External event flag of channel 3 - R */
    ureg32 EIFBIC4:1;     /* [4:4]  External event flag of channel 4 - R */
    ureg32 EIFBIC5:1;     /* [5:5]  External event flag of channel 5 - R */
    ureg32 EIFBIC6:1;     /* [6:6]  External event flag of channel 6 - R */
    ureg32 EIFBIC7:1;     /* [7:7]  External event flag of channel 7 - R */
    ureg32 reserved_8:24; /* [31:8] Internal reserved */
} EXTI_ETIPF_Bits;

/* Flag modification register */
typedef struct
{
    ureg32 SFBIC0:1;      /* [0:0]   Set the flag bit of input channel 0 - W */
    ureg32 SFBIC1:1;      /* [1:1]   Set the flag bit of input channel 1 - W */
    ureg32 SFBIC2:1;      /* [2:2]   Set the flag bit of input channel 2 - W */
    ureg32 SFBIC3:1;      /* [3:3]   Set the flag bit of input channel 3 - W */
    ureg32 SFBIC4:1;      /* [4:4]   Set the flag bit of input channel 4 - W */
    ureg32 SFBIC5:1;      /* [5:5]   Set the flag bit of input channel 5 - W */
    ureg32 SFBIC6:1;      /* [6:6]   Set the flag bit of input channel 6 - W */
    ureg32 SFBIC7:1;      /* [7:7]   Set the flag bit of input channel 7 - W */
    ureg32 reserved_8:8;  /* [15:8]  Internal reserved */
    ureg32 CICFB0:1;      /* [16:16] Clear the flag bit of input channel 0 - W */
    ureg32 CICFB1:1;      /* [17:17] Clear the flag bit of input channel 1 - W */
    ureg32 CICFB2:1;      /* [18:18] Clear the flag bit of input channel 2 - W */
    ureg32 CICFB3:1;      /* [19:19] Clear the flag bit of input channel 3 - W */
    ureg32 CICFB4:1;      /* [20:20] Clear the flag bit of input channel 4 - W */
    ureg32 CICFB5:1;      /* [21:21] Clear the flag bit of input channel 5 - W */
    ureg32 CICFB6:1;      /* [22:22] Clear the flag bit of input channel 6 - W */
    ureg32 CICFB7:1;      /* [23:23] Clear the flag bit of input channel 7 - W */
    ureg32 reserved_24:8; /* [31:24] Internal reserved */
} EXTI_FLBMR_Bits;

/* Pattern detection result register */
typedef struct
{
    ureg32 MDRC0:1;       /* [0:0] Pattern detection result of channel 0 - R */
    ureg32 MDRC1:1;       /* [1:1] Pattern detection result of channel 1 - R */
    ureg32 MDRC2:1;       /* [2:2] Pattern detection result of channel 2 - R */
    ureg32 MDRC3:1;       /* [3:3] Pattern detection result of channel 3 - R */
    ureg32 MDRC4:1;       /* [4:4] Pattern detection result of channel 4 - R */
    ureg32 MDRC5:1;       /* [5:5] Pattern detection result of channel 5 - R */
    ureg32 MDRC6:1;       /* [6:6] Pattern detection result of channel 6 - R */
    ureg32 MDRC7:1;       /* [7:7] Pattern detection result of channel 7 - R */
    ureg32 reserved_8:24; /* [31:8] Internal reserved */
} EXTI_PADERR_Bits;

/* INTGCj(j = 0,1,2,3), flag gating register */
typedef struct
{
    ureg32 IMCEN00:1;     /* [0:0]   OGU(2j) select ETL0 participate in pattern detect - RW */
    ureg32 IMCEN01:1;     /* [1:1]   OGU(2j) select ETL1 participate in pattern detect - RW */
    ureg32 IMCEN02:1;     /* [2:2]   OGU(2j) select ETL2 participate in pattern detect - RW */
    ureg32 IMCEN03:1;     /* [3:3]   OGU(2j) select ETL3 participate in pattern detect - RW */
    ureg32 IMCEN04:1;     /* [4:4]   OGU(2j) select ETL4 participate in pattern detect - RW */
    ureg32 IMCEN05:1;     /* [5:5]   OGU(2j) select ETL5 participate in pattern detect - RW */
    ureg32 IMCEN06:1;     /* [6:6]   OGU(2j) select ETL6 participate in pattern detect - RW */
    ureg32 IMCEN07:1;     /* [7:7]   OGU(2j) select ETL7 participate in pattern detect - RW */
    ureg32 reserved_8:5;  /* [12:8]  Internal reserved */
    ureg32 EGEN0:1;       /* [13:13] Event generation enable 0 - RW */
    ureg32 IGM0:2;        /* [15:14] Interrupt gating mode 0 - RW */
    ureg32 IMCEN10:1;     /* [16:16] OGU(2j+1) select ETL0 participate in pattern detect - RW */
    ureg32 IMCEN11:1;     /* [17:17] OGU(2j+1) select ETL1 participate in pattern detect - RW */
    ureg32 IMCEN12:1;     /* [18:18] OGU(2j+1) select ETL2 participate in pattern detect - RW */
    ureg32 IMCEN13:1;     /* [19:19] OGU(2j+1) select ETL3 participate in pattern detect - RW */
    ureg32 IMCEN14:1;     /* [20:20] OGU(2j+1) select ETL4 participate in pattern detect - RW */
    ureg32 IMCEN15:1;     /* [21:21] OGU(2j+1) select ETL5 participate in pattern detect - RW */
    ureg32 IMCEN16:1;     /* [22:22] OGU(2j+1) select ETL6 participate in pattern detect - RW */
    ureg32 IMCEN17:1;     /* [23:23] OGU(2j+1) select ETL7 participate in pattern detect - RW */
    ureg32 reserved_24:5; /* [28:24] Internal reserved */
    ureg32 EGEN1:1;       /* [29:29] Event generation enable 1 - RW */
    ureg32 IGM1:2;        /* [31:30] Interrupt gating mode 1 - RW */
} EXTI_INTGC_Bits;

/* Interrupt and Alarm Status Register */
typedef struct
{
    ureg32 SAF:19;        /* [18:0]  ETL alarm status - RW */
    ureg32 SAE:8;         /* [26:19] Filter alarm enable - RW */
    ureg32 reserved_27:5; /* [31:27] Internal reserved */
} EXTI_IASSR0_Bits;

/* Interrupt and Alarm Status Register */
typedef struct
{
    ureg32 SAO:8;          /* [7:0]  OGU alarm status - RW */
    ureg32 SAM:8;          /* [15:8] Connection matrix alarm status - RW */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} EXTI_IASSR1_Bits;

/* Interrupt and Alarm Status Register */
typedef struct
{
    ureg32 SAERCE:1;       /* [0:0]  Error clear register redundancy alarm status - RW */
    ureg32 SAEREE:1;       /* [1:1]  Safe enable register redundancy alarm status - RW */
    ureg32 SAER:1;         /* [2:2]  E protection register redundancy alarm status - RW */
    ureg32 SAERSE:1;       /* [3:3]  SE protection register access alarm status - RW */
    ureg32 SAERE:1;        /* [4:4]  E protection register access alarm status - RW */
    ureg32 SAEX:1;         /* [5:5]  EXTI module alarm status - RW */
    ureg32 reserved_16:26; /* [31:6] Internal reserved */
} EXTI_IASSR2_Bits;

/* Interrupt and Alarm Enable Register */
typedef struct
{
    ureg32 SAFE:19;       /* [18:0]  ETL alarm enable - RW */
    ureg32 SAEE:8;        /* [26:19] Filter alarm enable - RW */
    ureg32 reserved_27:5; /* [31:27] Internal reserved */
} EXTI_INTENR0_Bits;

/* Interrupt and Alarm Enable Register */
typedef struct
{
    ureg32 SAOE:8;         /* [7:0]  OGU alarm enable - RW */
    ureg32 SAME:8;         /* [15:8] Connection matrix alarm enable - RW */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} EXTI_INTENR1_Bits;

/* Interrupt and Alarm Enable Register */
typedef struct
{
    ureg32 SAERCEE:1;       /* [0:0]  Error clear register redundancy alarm enable - RW */
    ureg32 SAEREEE:1;       /* [1:1]  Safe enable register redundancy alarm enable - RW */
    ureg32 SAERE:1;         /* [2:2]  E protection register redundancy alarm enable - RW */
    ureg32 SAERSEE:1;       /* [3:3]  SE protection register access alarm enable - RW */
    ureg32 SAEREE:1;        /* [4:4]  E protection register access alarm enable - RW */
    ureg32 SAEXE:1;         /* [5:5]  EXTI module alarm enable - RW */
    ureg32 reserved_16:26;  /* [31:6] Internal reserved */
} EXTI_INTENR2_Bits;

/* Interrupt and Alarm Clear Register */
typedef struct
{
    ureg32 SAFC:19;       /* [18:0]  ETL alarm clear - RW */
    ureg32 SAEC:8;        /* [26:19] Filter alarm clear - RW */
    ureg32 reserved_27:5; /* [31:27] Internal reserved */
} EXTI_INTCL0_Bits;

/* Interrupt and Alarm Clear Register */
typedef struct
{
    ureg32 SAOC:8;         /* [7:0]  OGU alarm clear - RW */
    ureg32 SAMC:8;         /* [15:8] Connection matrix alarm clear - RW */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} EXTI_INTCL1_Bits;

/* Interrupt and Alarm Clear Register */
typedef struct
{
    ureg32 SAERCEC:1;       /* [0:0]  Error clear register redundancy alarm clear - RW */
    ureg32 SAEREEC:1;       /* [1:1]  Safe enable register redundancy alarm clear - RW */
    ureg32 SAERC:1;         /* [2:2]  E protection register redundancy alarm clear - RW */
    ureg32 SAERSEC:1;       /* [3:3]  SE protection register access alarm clear - RW */
    ureg32 SAEREC:1;        /* [4:4]  E protection register access alarm clear - RW */
    ureg32 SAEXC:1;         /* [5:5]  EXTI module alarm clear - RW */
    ureg32 reserved_16:26;  /* [31:6] Internal reserved */
} EXTI_INTCL2_Bits;

/* APB Bus Error Mask Register */
typedef struct
{
    ureg32 APBEMR:1;        /* [0:0]  APB bus error mask - RW */
    ureg32 reserved_1:31;   /* [31:1] Internal reserved */
} EXTI_APBEMR_Bits;
/**********************************************************************************************************************
 *                                           EXTI Register Union Definitions
 *********************************************************************************************************************/
/* External input filter register */
typedef union
/* #Violation: exti_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    EXTI_EXIFLT_Bits B; /* Bitfield access */
} EXTI_EXIFLT;

/* External input channel register */
typedef union
/* #Violation: exti_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    EXTI_ETIPC_Bits B; /* Bitfield access */
} EXTI_ETIPC;

/* External input flag register */
typedef union
/* #Violation: exti_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    EXTI_ETIPF_Bits B; /* Bitfield access */
} EXTI_ETIPF;

/* Flag modification register */
typedef union
/* #Violation: exti_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    EXTI_FLBMR_Bits B; /* Bitfield access */
} EXTI_FLBMR;

/* Pattern detection result register */
typedef union
/* #Violation: exti_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    EXTI_PADERR_Bits B; /* Bitfield access */
} EXTI_PADERR;

/* Flag gating register */
typedef union
/* #Violation: exti_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    EXTI_INTGC_Bits B; /* Bitfield access */
} EXTI_INTGC;

/* Interrupt and Alarm Status Register */
typedef union
/* #Violation: exti_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    EXTI_IASSR0_Bits B; /* Bitfield access */
} EXTI_IASSR0;

/* Interrupt and Alarm Status Register */
typedef union
/* #Violation: exti_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    EXTI_IASSR1_Bits B; /* Bitfield access */
} EXTI_IASSR1;

/* Interrupt and Alarm Status Register */
typedef union
/* #Violation: exti_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    EXTI_IASSR2_Bits B; /* Bitfield access */
} EXTI_IASSR2;

/* Interrupt and Alarm Enable Register */
typedef union
/* #Violation: exti_register_h_REF_1 */
{
    ureg32 U;            /* Unsigned access */
    EXTI_INTENR0_Bits B; /* Bitfield access */
} EXTI_INTENR0;

/* Interrupt and Alarm Enable Register */
typedef union
/* #Violation: exti_register_h_REF_1 */
{
    ureg32 U;            /* Unsigned access */
    EXTI_INTENR1_Bits B; /* Bitfield access */
} EXTI_INTENR1;

/* Interrupt and Alarm Enable Register */
typedef union
/* #Violation: exti_register_h_REF_1 */
{
    ureg32 U;            /* Unsigned access */
    EXTI_INTENR2_Bits B; /* Bitfield access */
} EXTI_INTENR2;

/* Interrupt and Alarm Clear Register */
typedef union
/* #Violation: exti_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    EXTI_INTCL0_Bits B; /* Bitfield access */
} EXTI_INTCL0;

/* Interrupt and Alarm Clear Register */
typedef union
/* #Violation: exti_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    EXTI_INTCL1_Bits B; /* Bitfield access */
} EXTI_INTCL1;

/* Interrupt and Alarm Clear Register */
typedef union
/* #Violation: exti_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    EXTI_INTCL2_Bits B; /* Bitfield access */
} EXTI_INTCL2;

/* APB Bus Error Mask Register */
typedef union
/* #Violation: exti_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    EXTI_APBEMR_Bits B; /* Bitfield access */
} EXTI_APBEMR;
/**********************************************************************************************************************
 *                                        EXTI Register Configuration Structure
 *********************************************************************************************************************/
/* EXTI object */
typedef volatile struct
{
    EXTI_EXIFLT  EXIFLT;   /* 20C, External Input Channel Filter Register */
    EXTI_ETIPC   ETIPC[4]; /* 210, External Input Channel Control Register */
    EXTI_ETIPF   ETIPF;    /* 220, External Input Flag Register */
    EXTI_FLBMR   FLBMR;    /* 224, Flag Modification Register */
    EXTI_PADERR  PADERR;   /* 228, Pattern Detection Result Register */
    EXTI_INTGC   INTGC[4]; /* 22C, Interrupt gate Register */
    EXTI_IASSR0  IASSR0;   /* 23C, Interrupt and Alarm Status Register 0 */
    EXTI_IASSR1  IASSR1;   /* 240, Interrupt and Alarm Status Register 1 */
    EXTI_IASSR2  IASSR2;   /* 244, Interrupt and Alarm Status Register 2 */
    EXTI_INTENR0 INTENR0;  /* 248, Interrupt and Alarm Enable Register 0 */
    EXTI_INTENR1 INTENR1;  /* 24C, Interrupt and Alarm Enable Register 1 */
    EXTI_INTENR2 INTENR2;  /* 250, Interrupt and Alarm Enable Register 2 */
    EXTI_INTCL0  INTCL0;   /* 254, Interrupt and Alarm Clear Register 0 */
    EXTI_INTCL1  INTCL1;   /* 258, Interrupt and Alarm Clear Register 1 */
    EXTI_INTCL2  INTCL2;   /* 25C, Interrupt and Alarm Clear Register 2 */
    EXTI_APBEMR  APBEMR;   /* 260, APB Bus Error Mask Register */
} EXTI_MODULE;

#endif /* EXTI_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
