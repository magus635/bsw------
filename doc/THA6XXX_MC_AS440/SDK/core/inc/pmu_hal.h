/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:  pmu_hal.h
 * Author:    00412
 * Version:   V1.2.0
 * Date:      2026/02/28
 * Description: This file contains all data type definitions and function declarations
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #pmu_hal_h_REF_1:MISRAC2012-Rule-2.3;
* Justification:The members of the type are used in configuration-generated code.
*
* #pmu_hal_h_REF_2:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*/

#ifndef CORE_PMU_HAL_H_
#define CORE_PMU_HAL_H_

/**********************************************************************************************************************
 *                                                Includes
 *********************************************************************************************************************/
#include "Platform_Types.h"

/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* Violation: pmu_hal_h_REF_2 */
#define PMU_COUNT_DIVIDER_SINGLE 0U
#define PMU_COUNT_DIVIDER_64 1U

/*All the  Event Counter index*/
#define PMU_EVENT_COUNTER_NONE 0U
#define PMU_FIRST_EVENT_COUNTER_POS 0x0U
#define PMU_SECOND_EVENT_COUNTER_POS 0x1U
#define PMU_THIRD_EVENT_COUNTER_POS 0x2U
#define PMU_FOURTH_EVENT_COUNTER_POS 0x3U
/* Violation: pmu_hal_h_REF_2 */
#define PMU_MAX_EVENT_COUNTER 0x4U

#define PMU_FIRST_EVENT_COUNTER_MASK (1U << PMU_FIRST_EVENT_COUNTER_POS)
#define PMU_SECOND_EVENT_COUNTER_MASK (1U << PMU_SECOND_EVENT_COUNTER_POS)
#define PMU_THIRD_EVENT_COUNTER_MASK (1U << PMU_THIRD_EVENT_COUNTER_POS)
#define PMU_FOURTH_EVENT_COUNTER_MASK (1U << PMU_FOURTH_EVENT_COUNTER_POS)

/*PMEVTYPER Privileged filtering bit*/
/* Violation: pmu_hal_h_REF_2 */
#define PMEVTYPER_PRIV_FILTER (0x80000000U)
/*PMEVTYPER User filtering bit*/
/* Violation: pmu_hal_h_REF_2 */
#define PMEVTYPER_USER_FILTER (0x40000000U)
/*PMEVTYPER Non-secure EL1  modes filtering bit*/
/* Violation: pmu_hal_h_REF_2 */
#define PMEVTYPER_NSK_FILTER (0x20000000U)
/*PMEVTYPER Non-secure EL0 modes filtering bit*/
/* Violation: pmu_hal_h_REF_2 */
#define PMEVTYPER_NSU_FILTER (0x10000000U)

/*PMEVTYPER EL2 (Hyp mode) filtering bit */
/* Violation: pmu_hal_h_REF_2 */
#define PMEVTYPER_NSH_FILTER (0x8000000U)

/*PMEVTYPER Realm EL0 (unprivileged) filtering bit */
/* Violation: pmu_hal_h_REF_2 */
#define PMEVTYPER_RLU_FILTER (0x200000U)

#define PMEVTYPER_MASK (0xFA20FFFFU)
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* Enumeration for PMU event counter ID */
typedef enum
{
    SW_INCR = 0x0,             /*Software increment*/
    L1I_CACHE_REFILL = 0x001,  /*L1 instruction cache refill*/
    L1D_CACHE_REFILL = 0x003,  /*L1 data cache refill*/
    L1D_CACHE = 0x004,         /*L1 data cache access*/
    LD_RETIRED = 0x006,        /*Instruction architecturally executed,condition check pass - load*/
    ST_RETIRED = 0x007,        /*Instruction architecturally executed,condition check pass - store*/
    INST_RETIRED = 0x008,      /*Instruction architecturally executed*/
    EXC_TAKEN = 0x009,         /*Exception taken*/
    EXC_RETURN = 0x00A,        /*Instruction architecturally executed, condition code check pass, exception return*/
    CID_WRITE_RETIRED = 0x00B, /*Instruction architecturally executed, condition code check pass, write to CONTEXTIDR*/
    PC_WRITE_RETIRED = 0x00C,  /*Instruction architecturally executed, condition check pass, software change of the PC*/
    BR_IMMED_RETIRED = 0x00D,  /*Instruction architecturally executed, immediate branch*/
    BR_RETURN_RETIRED = 0x00E, /*Instruction architecturally executed, condition code check pass, procedure return*/
    UNALIGNED_LDST_RETIRED = 0x00F,            /*Instruction architecturally executed, condition code check pass, unaligned load or store*/
    BR_MIS_PRED = 0x010,  /*Mispredicted or not predicted branch speculatively executed*/
    CPU_CYCLES = 0x011,   /*Cycle*/
    BR_PRED = 0x012,      /*Predictable branch speculatively executed*/
    MEM_ACCESS = 0x013,   /*Data memory access*/
    L1I_CACHE = 0x014,    /*L1 instruction cache access*/
    BUS_ACCESS = 0x019,   /*AXIM, Flash, or LLPP bus access*/
    MEMORY_ERROR = 0x01A, /*Local memory error*/
    INST_SPEC = 0x01B,    /*Operation speculatively executed*/
    BUS_CYCLES = 0x01D,   /*Bus cycle (AXIM)*/
    CHAIN = 0x01E,        /*For odd-numbered counters*/
    BR_RETIRED = 0x021,   /*Instruction architecturally executed, branch*/
    BR_MIS_PRED_RETIRED = 0x022,          /*Instruction architecturally executed, mispredicted branch*/
    STALL_FRONTEND = 0x023,               /*No operation issued due to the front end*/
    STALL_BACKEND = 0x024,                /*No operation issued due to the back end*/
    BUS_ACCESS_RD = 0x060,                /*Bus access - Read (AXIM, Flash, or LLPP)*/
    BUS_ACCESS_WR = 0x061,                /*Bus access - Write (AXIM, Flash, or LLPP).*/
    EXC_SVC = 0x082,                      /*Exception taken, supervisor call*/
    EXC_IRQ = 0x086,                      /*Exception taken, IRQ*/
    EXC_FIQ = 0x087,                      /*Exception taken, FIQ*/
    EXC_HVC = 0x08A,                      /*Exception taken, Hypervisor Call*/
    EXC_TRAP_IRQ = 0x08E,                 /*Exception taken, IRQ not taken locally*/
    EXC_TRAP_FIQ = 0x08F,                 /*Exception taken, FIQ not taken locally*/
    HIRZER_AXI_READ = 0x0C0,                /*External memory request, AXIM read*/
    HIRZER_AXI_WRITE = 0x0C1,               /*External memory request, AXIM write*/
    HIRZER_FLASH_READ = 0x0C2,              /*External memory request, Flash*/
    HIRZER_LLPP_READ = 0x0C3,               /*External memory request, LLPP read*/
    HIRZER_LLPP_WRITE = 0x0C4,              /*External memory request, LLPP write*/
    HIRZER_NC_AXI_READ = 0x0C5,             /*Non-cacheable external memory request, AXIM read*/
    HIRZER_NC_AXI_WRITE = 0x0C6,            /*Non-cacheable external memory request, AXIM write*/
    HIRZER_NC_FLASH_READ = 0x0C7,           /*Non-cacheable external memory request, Flash*/
    HIRZER_REFILL_PF_AXI = 0x0C8,           /*L1 data cache refill because of prefetch*/
    HIRZER_REFILL_LS_AXI = 0x0C9,           /*L1 data cache refill because of load or store, AXIM*/
    HIRZER_REFILL_LS_FLASH = 0x0CA,         /*L1 data cache refill because of load or store, Flash*/
    HIRZER_DC_ACCESS_AXI = 0x0CB,           /*L1 data cache access in a way reserved for AXIM*/
    HIRZER_DC_ACCESS_FLASH = 0x0CC,         /*L1 data cache access in a way reserved for Flash*/
    HIRZER_IC_ACCESS_AXI = 0x0CD,           /*L1 instruction cache access in a way reserved for AXIM*/
    HIRZER_IC_ACCESS_FLASH = 0x0CE,         /*L1 instruction cache access in a way reserved for Flash*/
    HIRZER_NC_LS_HINTED_AXI = 0x0CF,        /*Non-cacheable external memory request because of load was hinted, AXIM*/
    HIRZER_NC_LS_HINTED_FLASH_READ = 0x0D0, /*Non-cacheable external memory request because of load was hinted, Flash*/
    HIRZER_REFILL_IC_AXI = 0x0D1,           /*L1 Instruction cache refill, AXIM*/
    HIRZER_REFILL_IC_FLASH = 0x0D2,         /*L1 Instruction cache refill, Flash*/
    HIRZER_NC_LS_AXI_READ = 0x0D3,          /*Non-cacheable external memory request because of load, AXIM*/
    HIRZER_NC_LS_FLASH_READ = 0x0D4,        /*Non-cacheable external memory request because of load, Flash*/
    HIRZER_COND_BR_RETIRED = 0x0D5,         /*Conditional branch executed*/
    HIRZER_MIS_PRED_COND_BR = 0x0D6,        /*Conditional branch mispredicted*/
    HIRZER_BTAC_BR_RETIRED = 0x0D7,         /*BTAC branch executed*/
    HIRZER_MIS_PRED_BTAC_BR = 0x0D8,        /*Conditional branch mispredicted*/
    HIRZER_VSCTLR_CHANGED = 0x0D9,          /*Instruction architecturally executed, MCR to VSCTLR*/
    HIRZER_DSB_ALL_RETIRED = 0x0DA,         /*Instruction architecturally executed, strong DSB, DFB*/
    HIRZER_SIMULT_ACCESS_AXI = 0x0DB,       /*Simultaneous accesses from instruction side and data side to AXIM*/
    HIRZER_SIMULT_ACCESS_FLASH = 0x0DC,     /*Simultaneous accesses from instruction side and data side to Flash*/
    HIRZER_EL2_ENTERED = 0x0DD,             /*Exception taken to EL2*/
    HIRZER_CRS_BR_RETIRED = 0x0DE,          /*Implementation defined event. CRS branch executed*/
    HIRZER_MIS_PRED_CRS_BR = 0x0DF,         /*CRS branch mispredicted*/
    HIRZER_COR_ERR_MEM = 0x0F0,             /*Correctable memory error occurred from any source*/
    HIRZER_FAT_ERR_MEM = 0x0F1,             /*Fatal memory error occurred from any source */
    HIRZER_BUS_COR_DATA = 0x0F2,            /*Correctable data payload bus error occurred from any source */
    HIRZER_BUS_FAT_OTHER = 0x0F3,           /*Fatal non-protocol bus error*/
    HIRZER_BUS_PROTOCOL_ANY = 0x0F4,        /*Fatal protocol bus error occurred from any source*/
    HIRZER_IQ_EMPTY_NO_MISS = 0x100, /*Counts every cycle that the DPU IQ is empty and that is not because of a recent instruction cache miss in any cache way*/
    HIRZER_IQ_EMPTY_AXI_MISS = 0x101, /*there is an instruction cache miss being processed for a cache way reserved for AXI Master*/
    HIRZER_IQ_EMPTY_FLASH_MISS = 0x102, /*there is an instruction cache miss being processed for a cache way reserved for Flash*/
    HIRZER_INTERLOCK_OTHER = 0x103, /*that is not because of an Advanced SIMD or floating-point instruction*/
    HIRZER_INTERLOCK_AGU = 0x104, /* that is because of a load/ store instruction waiting for data to calculate the address in the AGU*/
    HIRZER_INTERLOCK_FPASIMD = 0x105, /*that is because of an Advanced SIMD or floating-point instruction,*/
    HIRZER_LOAD_STALL_AXI = 0x106, /*Counts every cycle there is a stall in the Wr stage because of a load miss from the AXIM*/
    HIRZER_LOAD_STALL_FLASH = 0x107, /*Counts every cycle there is a stall in the Wr stage because of a load miss from Flash*/
    HIRZER_WR_STALL_STORE = 0x108,         /*Counts every cycle there is a stall in the Wr stage because of a store*/
    HIRZER_WR_STALL_AXI_STB_FULL = 0x109,  /*Store stalled because the AXIM part of the store buffer was full*/
    HIRZER_WR_STALL_TCM_STB_FULL = 0x10A,  /*Store stalled because the TCM part of the store buffer was full*/
    HIRZER_WR_STALL_LLPP_STB_FULL = 0x10B, /*Store stalled because the LLPP part of the store buffer was full*/
    HIRZER_BARRIER_STALL_BARRIER = 0x10C,  /*Barrier stalled because store buffer was busy with another barrier*/
    HIRZER_BARRIER_STORE_AXIWRITE = 0x10D,                 /*Barrier stalled because it was waiting for a write to complete on the AXIM bus*/
    HIRZER_IC_WT_HIT = 0x200,    /* L1 instruction cache way tracker hit*/
    HIRZER_DC_WT_HIT = 0x201,    /*L1 data cache way tracker hit*/
    HIRZER_I_UMPU_HIT = 0x202,   /*Instruction side micro MPU hit*/
    HIRZER_D_UMPU_HIT = 0x203,   /*Data side micro MPU hit. This can also be counted on a pipeline stall*/
    HIRZER_IC_CACHE_HIT = 0x204, /*L1 instruction cache hit*/
    HIRZER_IC_LFB_HIT = 0x205,   /*L1 instruction cache linefill buffer hit*/
    HIRZER_IC_BIU_HIT = 0x206,   /*L1 instruction cache hit on BIU response*/
    HIRZER_IC_HINT_REQ = 0x207,  /*L1 instruction cache hint request sent*/
    HIRZER_DC_TAG_ACCESS = 0x208, /* L1 data cache tag memory accessed. */
    HIRZER_DC_DATA_ACCESS = 0x209, /* L1 data cache data memory accessed. */
    HIRZER_TCM_ACCESS = 0x20A,   /* TCM memory accessed */
} PMU_EventCounterID;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 **********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Function Declarations
 *********************************************************************************************************************/
#define CORE_START_SEC_CODE_ASIL_D_GLOBAL
#include "Core_MemMap.h"

/**********************************************************************************************************************
 * Function:     PMU_Hal_Initialize
 * Description:  Initialize PMU module
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different processor element, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        bClockDiv: The clock divider
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/19    00412      create
 *********************************************************************************************************************/
extern void PMU_Hal_Initialize(uint8 bClockDiv);
/**********************************************************************************************************************
 * Function:     PMU_Hal_Deinitialize
 * Description:  De-Initialize PMU module
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/19    00412      create
 *********************************************************************************************************************/
extern void PMU_Hal_Deinitialize(void);
/**********************************************************************************************************************
 * Function:     PMU_Hal_ResetCycCnt
 * Description:  Reset cycle counter
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/19    00412      create
 *********************************************************************************************************************/
extern void PMU_Hal_ResetCycCnt(void);
/**********************************************************************************************************************
 * Function:     PMU_Hal_EnCycCnt
 * Description:  Enable cycle counter
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/19    00412      create
 *********************************************************************************************************************/
extern void PMU_Hal_EnCycCnt(void);
/**********************************************************************************************************************
 * Function:     PMU_Hal_DisCycCnt
 * Description:  Disable cycle counter
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/19    00412      create
 *********************************************************************************************************************/
extern void PMU_Hal_DisCycCnt(void);
/**********************************************************************************************************************
 * Function:     PMU_Hal_GetCycCntVal
 * Description:  Get cycle counter value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       uint64: The cycle counter value
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/19    00412      create
 *********************************************************************************************************************/
extern uint64 PMU_Hal_GetCycCntVal(void);
/**********************************************************************************************************************
 * Function:     PMU_Hal_ResetAllEvtCnt
 * Description:  Reset all event counter
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/19    00412      create
 *********************************************************************************************************************/
extern void PMU_Hal_ResetAllEvtCnt(void);
/**********************************************************************************************************************
 * Function:     PMU_Hal_EnEvtCnt
 * Description:  Enable event counter
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        uMask: The mask value of event counter
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2022/05/19    00412      create
 *********************************************************************************************************************/
extern void PMU_Hal_EnEvtCnt(uint32 uMask);
/**********************************************************************************************************************
 * Function:     PMU_Hal_DisEvtCnt
 * Description:  Disable event counter
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        uMask: The mask value of event counter
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/19    00412      create
 *********************************************************************************************************************/
extern void PMU_Hal_DisEvtCnt(uint32 uMask);
/**********************************************************************************************************************
 * Function:     PMU_Hal_GetEvtCntVal
 * Description:  Get event counter value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        uCntIndex: The index of event counter
 * Inout:        None
 * Output:       None
 * Return:       uint32: The event counter value
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/19    00412      create
 *********************************************************************************************************************/
extern uint32 PMU_Hal_GetEvtCntVal(uint32 uCntIndex);
/**********************************************************************************************************************
 * Function:     PMU_Hal_SetEvtCntType
 * Description:  Set event counter to one index
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        uCntIndex: The index of event counter
 *               uCntType: The event counter ID
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/19    00412      create
 *********************************************************************************************************************/
extern void PMU_Hal_SetEvtCntType(uint32 uCntIndex, PMU_EventCounterID uCntType);
/**********************************************************************************************************************
 * Function:     PMU_Hal_GetEvtCntOvsStatus
 * Description:  Get event counter overflow status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        uCntIndex: The event index to get overflow status
 * Inout:        None
 * Output:       None
 * Return:       uint32: The event counter overflow status
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/19    00412      create
 *********************************************************************************************************************/
extern uint32 PMU_Hal_GetEvtCntOvsStatus(uint32 uCntIndex);
/**********************************************************************************************************************
 * Function:     PMU_Hal_EnEvtOvsIrq
 * Description:  Enable event counter overflow interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        uMask:The mask value of event counter
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/19    00412      create
 *********************************************************************************************************************/
extern void PMU_Hal_EnEvtOvsIrq(uint32 uMask);
/**********************************************************************************************************************
 * Function:     PMU_Hal_DisEvtOvsIrq
 * Description:  Disable event counter overflow interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        uMask:The mask value of event counter
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/19    00412      create
 *********************************************************************************************************************/
extern void PMU_Hal_DisEvtOvsIrq(uint32 uMask);
/**********************************************************************************************************************
 * Function:     PMU_Hal_EvtIncrement
 * Description:  Increment  software event value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        uCntIndex:The index value of event counter
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/19    00412      create
 *********************************************************************************************************************/
extern void PMU_Hal_EvtIncrement(uint32 uCntIndex);
/**********************************************************************************************************************
 * Function:     PMU_Hal_EnableUserMode
 * Description:  Enable user mode access PMU
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        uMode: The mode values need to be enabled for user mode access
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/19    00412      create
 *********************************************************************************************************************/
extern void PMU_Hal_EnableUserMode(uint32 uMode);
/**********************************************************************************************************************
 * Function:     PMU_Hal_ClearEvCnOvs
 * Description:  Clear event counter overflow status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        uMask: The mask value of event counter
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/31    00412      create
 *********************************************************************************************************************/
extern void PMU_Hal_ClearEvCnOvs(uint32 uMask);
/**********************************************************************************************************************
 * Function:     PMU_Hal_ClearEvCnOvs
 * Description:  Set event counter value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        uCntIndex: The index of event counter
 *               uVal: The value set to the specific event counter
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 * Date          Author    Modified
 * 2022/05/31    00412      create
 *********************************************************************************************************************/
extern void PMU_Hal_SetEvtCntVal(uint32 uCntIndex, uint32 uVal);

#define CORE_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Core_MemMap.h"

#endif /* CORE_PMU_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
