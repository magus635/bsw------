/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName: itmu.h
 * Author:   00930
 * Version:  V1.2.0
 * Date:     2026/02/28
 * Description: ITMU hardware abstraction layer header file.
 *              This file contains function prototypes for ITMU module hardware abstraction layer.
 *********************************************************************************************************************/
/*
 * #Violation Summary
 *
 * #itmu_h_REF_1:MISRAC2012-Rule-2.5;
 * Justification:provide predefined macros/enum for users to use.
 *
 * #itmu_h_REF_2:MISRAC2012-Rule-20.1; 
 *Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
 *
 */

#ifndef ITMU_H_
#define ITMU_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "Platform_Types.h"

/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                        ITMU Register Configuration Structure
 *********************************************************************************************************************/
typedef volatile struct
{
    uint32 SSWSTS;          /* 0x00, SSW status Register */
    uint32 HWPINCFG;        /* 0x04, external Pin boot mode Register */
    uint32 ORIGCOPYINFO;    /* 0x08, the comparison info between UCB CFG ORIG and copy Register */
    uint32 reserved_0C[5];  /* 0x0C, internal Reserved  */
    uint32 STMEM0;          /* 0x20, indication SSW check stage Register */
    uint32 STMEM1;          /* 0x24, indication SSW check stage Register */
    uint32 STMEM2;          /* 0x28, indication SSW check stage Register */
    uint32 STMEM3;          /* 0x2C, indication SSW check stage Register */
    uint32 CPU0STRADDR;     /* 0x30, the boot address of CPU0 Register */
    uint32 CPU1STRADDR;     /* 0x34, the boot address of CPU1 Register */
    uint32 CPU2STRADDR;     /* 0x38, the boot address of CPU2 Register (THA6412 Only)*/
    uint32 CPU3STRADDR;     /* 0x3c, the boot address of CPU3 Register (THA6412 Only)*/
    uint32 reserved_40[3];  /* 0x40, internal Reserved  */
    uint32 RAMINI;          /* 0x4C, RAM initialization time select Register */
    uint32 RAMINICTRL;      /* 0x50, RAM initialization enable Register */
    uint32 RAMINISTS;       /* 0x54, RAM initialization status Register */
    uint32 BOOTCOREID;      /* 0x58, Boot core ID Register */
    uint32 CPURUN;          /* 0x5C, CPU running start Register */
    uint32 CPUSLVRUN2;      /* 0x60, CPU running start Register (THA6412 Only)*/
    uint32 CPUSLVRUN3;      /* 0x64, CPU running start Register (THA6412 Only)*/
    uint32 reserved_68[2];  /* 0x68, internal Reserved  */
    uint32 SYSMODE;         /* 0x70, System mode Register */
    uint32 INITSYS;         /* 0x74, Flash initialization status Register */
    uint32 INITFAULTCTRL;   /* 0x78, Initialization fault control Register */
    uint32 INITMASK;        /* 0x7c, Bus error mask Register */
    uint32 SERRPORSTS;      /* 0x80, Error status Register */
    uint32 SERRSYSSTS;      /* 0x84, Error status Register */
    uint32 SAFEENINIT;      /* 0x88, Safety enable Register */
    uint32 reserved_8C[30]; /* 0x8c, internal Reserved  */
    uint32 INITSTS1;        /* 0x104, Safety enable Register (THA6412 Only)*/
    uint32 RAMINICTRL1;     /* 0x108, RAM initialization control Register(THA6412 Only) */
    uint32 RAMINISTS1;      /* 0x10c, RAM initialization status Register (THA6412 Only)*/
} ITMUINIT_MODULE;

/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* RAM initialize control */
/* #Violation: itmu_h_REF_1*/
#define ITMU_RMAINI_CPU0ATCM (0x00000003U)
/* #Violation: itmu_h_REF_1*/
#define ITMU_RMAINI_CPU0BTCM0 (0x0000000CU)
/* #Violation: itmu_h_REF_1*/
#define ITMU_RMAINI_CPU0BTCM1 (0x00000030U)
/* #Violation: itmu_h_REF_1*/
#define ITMU_RMAINI_CPU0CTCM (0x000000C0U)
/* #Violation: itmu_h_REF_1*/
#define ITMU_RMAINI_CPU1ATCM (0x00000300U)
/* #Violation: itmu_h_REF_1*/
#define ITMU_RMAINI_CPU1BTCM0 (0x00000C00U)
/* #Violation: itmu_h_REF_1*/
#define ITMU_RMAINI_CPU1BTCM1 (0x00003000U)
/* #Violation: itmu_h_REF_1*/
#define ITMU_RMAINI_CPU1CTCM (0x0000C000U)
/* #Violation: itmu_h_REF_1*/
#define ITMU_RMAINI_GMU (0x00030000U)
/* #Violation: itmu_h_REF_1*/
#define ITMU_RMAINI_CAN (0x000C0000U)
/* #Violation: itmu_h_REF_1*/
#define ITMU_RMAINI_LMU1 (0x00300000U) /* (THA6104 do not support) */
/* #Violation: itmu_h_REF_1*/
#define ITMU_RMAINI_LMU2 (0x00C00000U)
/* #Violation: itmu_h_REF_1*/
#define ITMU_RMAINI_LMU3 (0x03000000U) /* (THA6104 do not support) */

/* The following are valid only for THA6412 */
/* #Violation: itmu_h_REF_1*/
#define ITMU_RMAINI_CPU2ATCM (0x00000003U)
/* #Violation: itmu_h_REF_1*/
#define ITMU_RMAINI_CPU2BTCM0 (0x0000000CU)
/* #Violation: itmu_h_REF_1*/
#define ITMU_RMAINI_CPU2BTCM1 (0x00000030U)
/* #Violation: itmu_h_REF_1*/
#define ITMU_RMAINI_CPU2CTCM (0x000000C0U)
/* #Violation: itmu_h_REF_1*/
#define ITMU_RMAINI_CPU3ATCM (0x00000300U)
/* #Violation: itmu_h_REF_1*/
#define ITMU_RMAINI_CPU3BTCM0 (0x00000C00U)
/* #Violation: itmu_h_REF_1*/
#define ITMU_RMAINI_CPU3BTCM1 (0x00003000U)
/* #Violation: itmu_h_REF_1*/
#define ITMU_RMAINI_CPU3CTCM (0x0000C000U)

/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* enumeration for System reset can trigger SRAM initialization or not */
typedef enum
{
    ITMU_RAMINIONSYSRESETE_ENABLE = 0U, /* System reset can trigger SRAM initialization */
    ITMU_RAMINIONSYSRESETE_DISABLE = 5U /* System reset cann't trigger SRAM initialization */
} Itmu_RamIniOnSysReset;

/* Itmu_Status, enumeration for the ITMU function status  */
typedef enum
{
    ITMU_STATUS_OK = 0U, /* Operation success */
    ITMU_STATUS_ERROR    /* Operation fail */
} Itmu_Status;

/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                        Global Inline Function Declaration
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/

#define ITMU_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: itmu_h_REF_2 */
#include "Itmu_MemMap.h"

/**********************************************************************************************************************
 * Function: Itmu_ClearModuleRam
 * Description: The function shall enable or disable module RAM initialization
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: index: index to be clear. 0-can clear CPU0/1 TCM, GMU, CAN, LMU1/2/3.
 *                                   1-can clear CPU2/3 TCM.
 *        clearBits: Enable the RAM initialization when the relevant bits are set.
 * Inout:  None
 * Output: none
 * Return: boolean:
 *                     ITMU_STATUS_OK: Operation success
 *                     ITMU_STATUS_ERROR: Operation fail
 * Others:
 * Date         Author   Modified
 * 2024/04/15   00930     create
 *********************************************************************************************************************/
extern boolean Itmu_ClearModuleRam(uint32 index, uint32 clearBits);

/**********************************************************************************************************************
 * Function: Itmu_InitRamOnSysReset
 * Description: The function shall enable or disable RAM initialization on system reset
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: ramIniOnSysReset: Specified whether system reset can trigger SRAM initialization.
 * Inout:  None
 * Output: none
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * Date         Author   Modified
 * 2024/04/15    00930     create
 *********************************************************************************************************************/
extern boolean Itmu_InitRamOnSysReset(Itmu_RamIniOnSysReset ramIniOnSysReset);

#define ITMU_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: itmu_h_REF_2 */
#include "Itmu_MemMap.h"

#endif /* ITMU_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
