/**************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName: startup.c
 * Author:    30011
 * Version:   v0.1
 * Date:     2023/05/31
 * Description: This file startup the system.
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/06/21    30011     create
 ************************************************************************************************/

/*
*#Violation Summary
*
*#startup_c_REF_1:MISRAC2012-Rule-2.5;;
* Justification: The macros are reserved for upper layers
*
*#startup_c_REF_2:MISRAC2012-Rule-20.1;
*Justification:  Imposes the specification of the section in which certain parts of the driver must be placed.
*
*#startup_c_REF_3:MISRAC2012-Dir-4.3;
* Justification: Mixing inline assembly with C code reduces code complexity.
*
*#exception_c_REF_4:MISRAC2012-Rule-1.2;
* Justification: Inline assembly for CPU-specific operations.
*
* #exception_c_REF_5:MISRAC2012-Dir-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
* #exception_c_REF_6:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "multicore.h"
#include "compilertypes.h"
#include "dev.h"
#include "startup.h"
#include "itmu.h"
#include "Mcall_Cfg.h"
#include "mpu_hal.h"
#include "tha6_cfg.h"
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
#include "gipc_hal.h"
#endif
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
/* #Violation: startup_c_REF_1 */
#define RCC_HSI_CLOCK_CONFIG (*(volatile uint32 *)(0xF0000078U))
/* #Violation: startup_c_REF_1 */
#define SAFETY_WDG_KEY_CONFIG (*(volatile uint32 *)(0xF006003CU))
/* Address for control core to halt/running */
#define CORE1_CTRL_ADDR (*(volatile uint32 *)(0xC0020C5CU))
#if defined(THA6_THA6412)
#define CORE2_CTRL_ADDR (*(volatile uint32 *)(0xC0020C60U))
#define CORE3_CTRL_ADDR (*(volatile uint32 *)(0xC0020C64U))

#define CORE3_CTRL_LOCK (*(volatile uint32 *)(0xC0020450U))
#endif /* THA6_THA6412 */


/* Address of CPUWDT0 */
/* #Violation: startup_c_REF_1 */
#define PWLOCK (*(volatile uint32 *)(0xC0070004U))
/* #Violation: startup_c_REF_1 */
#define CEPW (*(volatile uint32 *)(0xC0070018U))
/* #Violation: startup_c_REF_1 */
#define CECNTEN (*(volatile uint32 *)(0xC007001CU))
/* #Violation: startup_c_REF_1 */
#define CECNTC (*(volatile uint32 *)(0xC0070020U))
/* Address of RSTSTAT */
#define RSTSTAT (*(volatile uint32 *)(0xC0000800U))

/* Must be placed in 0x10000000U~0x10000200U*/
/* MULTICORE_SYNCVAR is initialized at Start().0x10000040U */
#define MULTICORE_SYNCVAR  (*(volatile uint32 *)MULTICORE_SYNCVAR_ADDR)
/* PLOCK needs 64 bytes. do not use 0x10000000U~0x10000040U */
#define PLOCK  ((Gipc_Lock *)PLOCK_ADDR)


#define RST_POWERON    (0x00800000U)

/* Macro for core mask */
#define CPU01_MASK (0x00000001U)
#if defined(THA6_THA6412)
#define CPU02_MASK (0x00000002U)
#define CPU03_MASK (0x00000004U)
#endif /* THA6_THA6412 */

/* #Violation: startup_c_REF_1 */
#define INTC_EXCEPTION_CPU_PIN_NUMBER (992U)

#define CPU_ENTER_SYNC_MAGIC01 (0x11110000)
#define CPU_ENTER_SYNC_MAGIC02 (0x5A5A5A5AU)

#define CPU01_ENTER_SYNC_MAGIC (0x00000001U)
#if defined(THA6_THA6412)
#define CPU02_ENTER_SYNC_MAGIC (0x00000002U)
#define CPU03_ENTER_SYNC_MAGIC (0x00000004U)
#endif /* THA6_THA6412 */

#define CPU00_BTCM_CONFIG (0x30100027U)
#define CPU00_CTCM_CONFIG (0x0020001FU)
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
#define CPU01_BTCM_CONFIG (0x30500027U)
#define CPU01_CTCM_CONFIG (0x0020001FU)
#if defined(THA6_THA6412)
#define CPU02_BTCM_CONFIG (0x31100023U)
#define CPU02_CTCM_CONFIG (0x0020001FU)
#define CPU03_BTCM_CONFIG (0x31500023U)
#define CPU03_CTCM_CONFIG (0x0020001FU)
#endif /* THA6_THA6412 */
#endif /* THA6_THA6206 || THA6_THA6412 */

#define CPU_DELAY_LOOP_COUNT (0x50U)

/* #Violation: startup_c_REF_1 */
#define CPUWDT_PWCE_FIXED_PASSWORD (0x3A00U)

/*Set 0b111 to enable core1,core2 and core3.Set 0b101 to enable core1 and core3.And so on.*/

#ifndef CORE_MASK
#define CORE_MASK (MCAL_USED_CORE_MASK)
#endif

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)

#define SDK_START_SEC_VAR_INIT_GLOBAL_NO_CACHEABLE
#include "Sdk_MemMap.h"
ALIGNED(128) static volatile uint32 s_cpu01SyncFlag[4] = {0x1U, 0U, 0U, 0U};
#define SDK_STOP_SEC_VAR_INIT_GLOBAL_NO_CACHEABLE
/* #Violation: startup_c_REF_2 */
#include "Sdk_MemMap.h"
#endif
/* Declare the linker file parameter divide by CoreNumber . */
/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          External Function Definitions                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
static void Startup_InitStack(void);
static void Startup_InitHypStack(void);
void Startup_InitCloneSections(void);
static void Startup_EL1ResetHandler(void);
static void Startup_InitPrivateSections(void);
static void Startup_InitGlobalUncachedSections(void);
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
/****************************************************************************************************
 *   Function Name           : Startup_InitGlobalUncachedSections
 *
 *   Service ID              : 0x06.
 *
 *   Description             : This function for master core to initialize the global and uncached section.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   TraceID                 : None.
 ****************************************************************************************************/
/* #Violation: startup_c_REF_3 */
 static void Startup_InitGlobalUncachedSections(void)
{
    Startup_CopyData globalData = {NULL_PTR, NULL_PTR, NULL_PTR};
    Startup_CopyData uncachedData = {NULL_PTR, NULL_PTR, NULL_PTR};
    Startup_ClearData globalBss = {NULL_PTR, NULL_PTR};
    Startup_ClearData uncachedBss = {NULL_PTR, NULL_PTR};
    Startup_ClearData unclearBss = {NULL_PTR, NULL_PTR};

    /* Load UNDEFINE_RAM_DATA imaged base and limit address,load base address to PrivateCode structure member. */
    /* #Violation: startup_c_REF_4 */
    STARTUP_GETCOPYDATAINFO(UNDEFINE_RAM_DATA, (globalData));
    /* Load GLOBAL_UNCACHED_DATA imaged base and limit address,load base address to PrivateCode structure member. */
    /* #Violation: startup_c_REF_4 */
    STARTUP_GETCOPYDATAINFO(GLOBAL_UNCACHED_DATA, (uncachedData));
    /* Load UNDEFINE_RAM_BSS imaged base and limit address to CloneBss structure member. */
    /* #Violation: startup_c_REF_4 */
    STARTUP_GETBSSDATAINFO(UNDEFINE_RAM_BSS, (globalBss));
    /* Load GLOBAL_UNCACHED_BSS imaged base and limit address to CloneBss structure member. */
    /* #Violation: startup_c_REF_4 */
    STARTUP_GETBSSDATAINFO(GLOBAL_UNCACHED_BSS, (uncachedBss));

    /* Copy global undefined data info from flash load base address to imaged ATCM address to execute */
    Startup_InitDataSection(&globalData);
    /* Copy global uncached data info from flash load base address to imaged ATCM address to execute */
    Startup_InitDataSection(&uncachedData);
    /* Clear global undefined bss section from the imaged base address to limit address. */
    Startup_InitBssSection(&globalBss);
    /* Clear global uncached  bss section from the imaged base address to limit address. */
    Startup_InitBssSection(&uncachedBss);

/*LMU 2*/
    STARTUP_GETCOPYDATAINFO(LMU2_CACHED_DATA, globalData);
    STARTUP_GETCOPYDATAINFO(LMU2_UNCACHED_DATA, uncachedData);
    STARTUP_GETBSSDATAINFO(LMU2_CACHED_BSS, globalBss);
    STARTUP_GETBSSDATAINFO(LMU2_UNCACHED_BSS, uncachedBss);
    Startup_InitDataSection(&globalData);
    Startup_InitDataSection(&uncachedData);
    Startup_InitBssSection(&globalBss);
    Startup_InitBssSection(&uncachedBss);

/*LMU INIT*/
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
/*LMU 1*/
    STARTUP_GETCOPYDATAINFO(LMU1_CACHED_DATA, globalData);
    STARTUP_GETCOPYDATAINFO(LMU1_UNCACHED_DATA, uncachedData);
    STARTUP_GETBSSDATAINFO(LMU1_CACHED_BSS, globalBss);
    STARTUP_GETBSSDATAINFO(LMU1_UNCACHED_BSS, uncachedBss);
    Startup_InitDataSection(&globalData);
    Startup_InitDataSection(&uncachedData);
    Startup_InitBssSection(&globalBss);
    Startup_InitBssSection(&uncachedBss);
/*LMU 3*/
    STARTUP_GETCOPYDATAINFO(LMU3_CACHED_DATA, globalData);
    STARTUP_GETCOPYDATAINFO(LMU3_UNCACHED_DATA, uncachedData);
    STARTUP_GETBSSDATAINFO(LMU3_CACHED_BSS, globalBss);
    STARTUP_GETBSSDATAINFO(LMU3_UNCACHED_BSS, uncachedBss);
    Startup_InitDataSection(&globalData);
    Startup_InitDataSection(&uncachedData);
    Startup_InitBssSection(&globalBss);
    Startup_InitBssSection(&uncachedBss);
#endif /* THA6_THA6206 || THA6_THA6412 */


    /* #Violation: startup_c_REF_5 */
    if(RST_POWERON == RSTSTAT)
    {
        /* Load UNRESET_RAM_BSS imaged base and limit address to CloneBss structure member. */
        /* #Violation: startup_c_REF_4 */
        STARTUP_GETBSSDATAINFO(UNCLEAR_RAM_BSS, (unclearBss));
        /* Clear global unreset  bss section from the imaged base address to limit address. */
        Startup_InitBssSection(&unclearBss);
    }
}
/****************************************************************************************************
 *   Function Name           : Startup_StartSlaveCore
 *
 *   Service ID              : 0x07.
 *
 *   Description             : This function is to run slave core by CORE_MASK.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   TraceID                 : None.
 ****************************************************************************************************/
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
/* #Violation: startup_c_REF_3 */
static void Startup_StartSlaveCore(void)
{
    uint16 loop;

    if(0U < CORE_MASK)
    {
        /* #Violation: startup_c_REF_5 */
        MULTICORE_SYNCVAR = CPU_ENTER_SYNC_MAGIC01;
        if(CPU01_MASK == (CORE_MASK & CPU01_MASK))
        {
            for(loop = 0U; loop < CPU_DELAY_LOOP_COUNT; loop++)
            {
                /* #Violation: startup_c_REF_4 */
                ASM_VOLATILE("nop");
            }

            /* If CPU01 is already running , don't set running again. */
            /* #Violation: startup_c_REF_5 */
            if((MULTICORE_SYNCVAR & CPU01_ENTER_SYNC_MAGIC) != CPU01_ENTER_SYNC_MAGIC)
            {
                /* Run core1 */
                /* #Violation: startup_c_REF_5 */
                CORE1_CTRL_ADDR |= 1U;
            }
        }

#if defined(THA6_THA6412)
        if(CPU02_MASK == (CORE_MASK & CPU02_MASK))
        {
            for(loop = 0U; loop < CPU_DELAY_LOOP_COUNT; loop++)
            {
                /* #Violation: startup_c_REF_4 */
                ASM_VOLATILE("nop");
            }

            /* If CPU02 is already running , don't set running again. */
            /* #Violation: startup_c_REF_5 */
            if((MULTICORE_SYNCVAR & CPU02_ENTER_SYNC_MAGIC) != CPU02_ENTER_SYNC_MAGIC)
            {
                /* Run core2 */
                /* #Violation: startup_c_REF_5 */
                CORE2_CTRL_ADDR |= 1U;
            }
        }
        
        if(CPU03_MASK == (CORE_MASK & CPU03_MASK))
        {
            for(loop = 0U; loop < CPU_DELAY_LOOP_COUNT; loop++)
            {
                /* #Violation: startup_c_REF_4 */
                ASM_VOLATILE("nop");
            }

            /* If CPU03 is already running , don't set running again. */
            /* #Violation: startup_c_REF_5 */
            if((MULTICORE_SYNCVAR & CPU03_ENTER_SYNC_MAGIC) != CPU03_ENTER_SYNC_MAGIC)
            {
                /* #Violation: startup_c_REF_5 */
                if(CORE3_CTRL_LOCK == 0x30U)
                {
                    /* Run core3 */
                    /* #Violation: startup_c_REF_5 */
                    CORE3_CTRL_ADDR |= 1U;
                }
            }
        }
#endif /* THA6_THA6412 */
    }
}
#endif /* THA6_THA6206 || THA6_THA6412 */

/****************************************************************************************************
 *   Function Name           : Startup_InitPrivateSections
 *
 *   Service ID              : 0x05.
 *
 *   Description             : This function is to set EL1 mode stack point and initialize the private section by core
 *id. Then master core initialize the global and uncached section ,and start slave core. The slave core wait until
 *master core set sync flag to run.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   TraceID                 : None.
 ****************************************************************************************************/
/* #Violation: startup_c_REF_3 */
 static void Startup_InitPrivateSections(void)
{

    MultiCoreID id;
    Startup_CopyData privateCode  = {NULL_PTR, NULL_PTR, NULL_PTR};
    Startup_CopyData privateData  = {NULL_PTR, NULL_PTR, NULL_PTR};
    /* Startup_ClearData privateBss  = {NULL_PTR, NULL_PTR}; replaced by itmu init*/ 
    /* Get Core ID. */
    id = Multicore_GetCoreID();

    switch(id)
    {
        case MULTICOREID_CPU0:
            /* Load PRIVATE_CODE_CORE0_CTCM imaged base and limit address,load base address to PrivateCode structure
             * member. */
            /* #Violation: startup_c_REF_4 */
             STARTUP_GETCOPYDATAINFO(PRIVATE_CODE_CORE0, (privateCode));
            /* Load PRIVATE_DATA_CORE0 imaged base and limit address,load base address to PrivateCode structure
             * member. */
            /* #Violation: startup_c_REF_4 */
            STARTUP_GETCOPYDATAINFO(PRIVATE_DATA_CORE0, (privateData));
            /* Load RESERVED_CODE_CORE0_BTCM imaged base and limit address,load base address to PrivateCode
             * structure member. */
            /*  STARTUP_GETBSSDATAINFO(PRIVATE_BSS_CORE0, (privateBss)); replaced by itmu init*/ 
            /* Master core initialize the global and uncached region. */
            /* Sync Core1 Enter EL1 enviroment for EL2 temp SP problem.*/
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)   
            /* #Violation: startup_c_REF_5 */         
            while ((MULTICORE_SYNCVAR != 0U) && ((MULTICORE_SYNCVAR & CORE_MASK) != CORE_MASK))
            {
                ;
            }
#endif /* THA6_THA6206 || THA6_THA6412 */
            /*copy global/uncached data until core1 level EL2 env for temp SP problem.*/
            Startup_InitGlobalUncachedSections();
            /* Set Master Core finished global data copy operation flag. */

            /* Copy private code info from flash load base address to imaged ATCM address to execute */
            Startup_InitDataSection(&privateCode);
            /* Copy private data info from flash load base address to imaged ATCM address to execute */
            Startup_InitDataSection(&privateData);
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)

            /* Clear private bss section from the imaged base address to limit address. */
            /*  Startup_InitBssSection(&privateBss); replaced by itmu init*/ 
            /* Set Master Core finished global data copy operation flag. */
            s_cpu01SyncFlag[0] = CPU_ENTER_SYNC_MAGIC02;
#endif /* THA6_THA6206 || THA6_THA6412 */

            break;

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
        case MULTICOREID_CPU1:
            /* Load PRIVATE_CODE_CORE1_CTCM imaged base and limit address,load base address to PrivateCode structure
             * member. */
            /* #Violation: startup_c_REF_4 */
            STARTUP_GETCOPYDATAINFO(PRIVATE_CODE_CORE1, (privateCode));
            /* Load PRIVATE_DATA_CORE1 imaged base and limit address,load base address to PrivateCode structure
             * member. */
            /* #Violation: startup_c_REF_4 */
            STARTUP_GETCOPYDATAINFO(PRIVATE_DATA_CORE1, (privateData));
            /* Load RESERVED_CODE_CORE1_BTCM imaged base and limit address,load base address to PrivateCode
             * structure member. */
            /*  STARTUP_GETBSSDATAINFO(PRIVATE_BSS_CORE1, (privateBss)); replaced by itmu init*/ 

            /* Copy private code info from flash load base address to imaged ATCM address to execute */
            Startup_InitDataSection(&privateCode);
            /* Copy private data info from flash load base address to imaged ATCM address to execute */
            Startup_InitDataSection(&privateData);
            /* Clear private bss section from the imaged base address to limit address. */
            /*  Startup_InitBssSection(&privateBss); replaced by itmu init*/ 
            /* Slave core wait until master core set sync flag to run. */
            while(CPU_ENTER_SYNC_MAGIC02 != s_cpu01SyncFlag[0])
            {
                ;
            }
            
            break;

#if defined(THA6_THA6412)
        case MULTICOREID_CPU2:
            /* Load PRIVATE_CODE_CORE2_CTCM imaged base and limit address,load base address to PrivateCode structure
             * member. */
            /* #Violation: startup_c_REF_4 */
            STARTUP_GETCOPYDATAINFO(PRIVATE_CODE_CORE2, (privateCode));
            /* Load PRIVATE_DATA_CORE2 imaged base and limit address,load base address to PrivateCode structure
             * member. */
            /* #Violation: startup_c_REF_4 */
            STARTUP_GETCOPYDATAINFO(PRIVATE_DATA_CORE2, (privateData));
            /* Load RESERVED_CODE_CORE2_BTCM imaged base and limit address,load base address to PrivateCode
             * structure member. */
            /*  STARTUP_GETBSSDATAINFO(PRIVATE_BSS_CORE2, (privateBss)); replaced by itmu init*/ 

            /* Copy private code info from flash load base address to imaged ATCM address to execute */
            Startup_InitDataSection(&privateCode);
            /* Copy private data info from flash load base address to imaged ATCM address to execute */
            Startup_InitDataSection(&privateData);
            /* Clear private bss section from the imaged base address to limit address. */
            /*  Startup_InitBssSection(&privateBss); replaced by itmu init*/ 
            /* Slave core wait until master core set sync flag to run. */
            while(CPU_ENTER_SYNC_MAGIC02 != s_cpu01SyncFlag[0])
            {
                ;
            }
            
            break;

        case MULTICOREID_CPU3:
            /* Load PRIVATE_CODE_CORE3_CTCM imaged base and limit address,load base address to PrivateCode structure
             * member. */
            /* #Violation: startup_c_REF_4 */
            STARTUP_GETCOPYDATAINFO(PRIVATE_CODE_CORE3, (privateCode));
            /* Load PRIVATE_DATA_CORE3 imaged base and limit address,load base address to PrivateCode structure
             * member. */
            /* #Violation: startup_c_REF_4 */
            STARTUP_GETCOPYDATAINFO(PRIVATE_DATA_CORE3, (privateData));
            /* Load RESERVED_CODE_CORE3_BTCM imaged base and limit address,load base address to PrivateCode
             * structure member. */
            /*  STARTUP_GETBSSDATAINFO(PRIVATE_BSS_CORE3, (privateBss)); replaced by itmu init*/ 

            /* Copy private code info from flash load base address to imaged ATCM address to execute */
            Startup_InitDataSection(&privateCode);
            /* Copy private data info from flash load base address to imaged ATCM address to execute */
            Startup_InitDataSection(&privateData);
            /* Clear private bss section from the imaged base address to limit address. */
            /*  Startup_InitBssSection(&privateBss); replaced by itmu init*/ 
            /* Slave core wait until master core set sync flag to run. */
            while(CPU_ENTER_SYNC_MAGIC02 != s_cpu01SyncFlag[0])
            {
                ;
            }

            break;
#endif /* THA6_THA6412 */
#endif /* THA6_THA6206 || THA6_THA6412 */
        default:
            /* When get unexpected Core ID then assert false error. */
            Assert(FALSE);

            break;
    }
}
/****************************************************************************************************
 *   Function Name           : Startup_InitCloneSections
 *
 *   Service ID              : 0x01.
 *
 *   Description             : This function is to initialize the IRQ Vector table and cloned code,data,bss by
 *                             loading the data or code from flash, copy to imaged ram section to execute.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   TraceID                 : None.
 ****************************************************************************************************/
/* #Violation: startup_c_REF_3 */
 void Startup_InitCloneSections(void)
{
    MultiCoreID id;
    Startup_CopyData vectorTable = {NULL_PTR, NULL_PTR, NULL_PTR};
    Startup_CopyData cloneCode = {NULL_PTR, NULL_PTR, NULL_PTR};
    Startup_CopyData cloneData = {NULL_PTR, NULL_PTR, NULL_PTR};
    /*  Startup_ClearData cloneBss  = {NULL_PTR, NULL_PTR}; replaced by itmu init*/ 
    uint32 clearBits;

#ifdef ICACHE_ENABLE
    /* Configure the HSCTLR/SCTLR Registers, enable ICache and disable DCache. */
    Startup_InitEL2Configuration();
#endif
    Startup_EnableVFP();
    /* Enable LLPP0/LLPP1 port at EL2/EL1/EL0. */
    Startup_EnableLLPP();

#ifdef BUSTIMEOUT_ENABLE
    /* set Bus Timeout for for accesses to AXIM, Flash interface, and LLPP.*/
    SET_CP(15, 1, 0xFFFFFF77, 15, 3, 2);
#endif

    /* Get Core ID. */
    id = Multicore_GetCoreID();

    switch(id)
    {
        case MULTICOREID_CPU0:
            /* Core0 Ram clear  do not process gmu:1 for temp stack. 2. for unclear ram*/
            clearBits = ITMU_RMAINI_CPU0ATCM | ITMU_RMAINI_CPU0BTCM0 | ITMU_RMAINI_CPU0BTCM1 |
                ITMU_RMAINI_CPU0CTCM | ITMU_RMAINI_LMU2;
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
            clearBits |= ITMU_RMAINI_LMU1 | ITMU_RMAINI_LMU3 ;
            /* #Violation: startup_c_REF_6 */
            while(FALSE == Gipc_Hal_GetLock(PLOCK))
            {
                ;
            }
#endif /* THA6_THA6206 || THA6_THA6412 */
            /*According to ARM errata 5.2 CPU.H001, it is necessary to configure TCM as the external
             * bus AXI address. Currently, the DEMO uses ATCM and CTCM as the clone segment, and there
             * is no situation where the internal bus and external bus access TCM together. If the
             * user usage is different, it is necessary to configure according to the BTCM
             * configuration method to avoid deadlock*/
            /* Set Core0 BTCM and CTCM configuration register */
            Startup_SetTCMAddr(CPU00_BTCM_CONFIG, CPU00_CTCM_CONFIG);
            (void)Itmu_ClearModuleRam(0U,clearBits);

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
            /* #Violation: startup_c_REF_6 */
            Gipc_Hal_ReleaseLock(PLOCK);

            /*Initial s_cpu01SyncFlag area with 128bit alignment according to
             *GMU request to avoid Core1 visiting invalid memory if core1 run fast.*/
            s_cpu01SyncFlag[0] = 0x0U;
            s_cpu01SyncFlag[1] = 0x0U;
            s_cpu01SyncFlag[2] = 0x0U;
            s_cpu01SyncFlag[3] = 0x0U;
            /* Master core start the slave core.*/
            Startup_StartSlaveCore();
#endif /* THA6_THA6206 || THA6_THA6412 */
            break;

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
        case MULTICOREID_CPU1:
            /*Wait for core 0 to execute and start other core stages to prevent problems caused by core asynchrony during debugging*/
            while( MULTICORE_SYNCVAR != CPU_ENTER_SYNC_MAGIC01);
            /* Core1 TCM clear*/
            clearBits = ITMU_RMAINI_CPU1ATCM | ITMU_RMAINI_CPU1BTCM0 | 
                            ITMU_RMAINI_CPU1BTCM1 |ITMU_RMAINI_CPU1CTCM;
            /* #Violation: startup_c_REF_6 */
            while(FALSE == Gipc_Hal_GetLock(PLOCK))
            {
                ;
            }
            /* Set Core1 BTCM and CTCM configuration register */
            Startup_SetTCMAddr(CPU01_BTCM_CONFIG, CPU01_CTCM_CONFIG);
            (void)Itmu_ClearModuleRam(0U,clearBits);
            /* #Violation: startup_c_REF_6 */
            Gipc_Hal_ReleaseLock(PLOCK);

            break;

#if defined(THA6_THA6412)
        case MULTICOREID_CPU2:
            /*Wait for core 0 to execute and start other core stages to prevent problems caused by core asynchrony during debugging*/
            while( MULTICORE_SYNCVAR != CPU_ENTER_SYNC_MAGIC01);
            /* Core2 TCM clear*/
            clearBits = ITMU_RMAINI_CPU2ATCM | ITMU_RMAINI_CPU2BTCM0 | 
                            ITMU_RMAINI_CPU2BTCM1 |ITMU_RMAINI_CPU2CTCM;
            /* #Violation: startup_c_REF_6 */
            while(FALSE == Gipc_Hal_GetLock(PLOCK))
            {
                ;
            }
            /* Set Core2 BTCM and CTCM configuration register */
                        Startup_SetTCMAddr(CPU02_BTCM_CONFIG, CPU02_CTCM_CONFIG);
            (void)Itmu_ClearModuleRam(1U,clearBits);
            /* #Violation: startup_c_REF_6 */
            Gipc_Hal_ReleaseLock(PLOCK);

            break;

        case MULTICOREID_CPU3:
            /*Wait for core 0 to execute and start other core stages to prevent problems caused by core asynchrony during debugging*/
            while( MULTICORE_SYNCVAR != CPU_ENTER_SYNC_MAGIC01);
            /* Core3 TCM clear*/
            clearBits = ITMU_RMAINI_CPU3ATCM | ITMU_RMAINI_CPU3BTCM0 | 
                            ITMU_RMAINI_CPU3BTCM1 |ITMU_RMAINI_CPU3CTCM;
            /* #Violation: startup_c_REF_6 */
            while(FALSE == Gipc_Hal_GetLock(PLOCK))
            {
                ;
            }
            /* Set Core3 BTCM and CTCM configuration register */
                        Startup_SetTCMAddr(CPU03_BTCM_CONFIG, CPU03_CTCM_CONFIG);
            (void)Itmu_ClearModuleRam(1U,clearBits);
            /* #Violation: startup_c_REF_6 */
            Gipc_Hal_ReleaseLock(PLOCK);

            break;
#endif /* THA6_THA6412 */
#endif /* THA6_THA6206 || THA6_THA6412 */
        default:
            /* When get unexpected Core ID then assert false error. */
            Assert(FALSE);
            break;
    }

    /* For stack isn't initialized at this moment. thus software should
     * initialize all variables here to avoid DATA Abort exception.*/
    /* Load INT_VECTOR_TABLE imaged base and limit address,load base address to VectorTable structure member. */
    /* #Violation: startup_c_REF_4 */
    STARTUP_GETCOPYDATAINFO(INT_VECTOR_TABLE, (vectorTable));
    /* Load PRIVATE_CODE_CLONE imaged base and limit address,load base address to CloneCode structure member. */
    /* #Violation: startup_c_REF_4 */
    STARTUP_GETCOPYDATAINFO(CODE_CLONE, (cloneCode));
    /* Load PRIVATE_DATA_CLONE imaged base and limit address,load base address to CloneData structure member. */
    /* #Violation: startup_c_REF_4 */
    STARTUP_GETCOPYDATAINFO(DATA_CLONE, (cloneData));
    /* Load BSS_CLONE imaged base and limit address to CloneBss structure member. */
    /*  STARTUP_GETBSSDATAINFO(BSS_CLONE, cloneBss); replaced by itmu init*/ 

    /* Copy IRQ vector table info from flash load base address to imaged ATCM address to execute */
    Startup_InitATCMDataSection(&vectorTable);
    /* Set EL2 exception base address to Startup_EL2ExceptionTable */
    /* #Violation: startup_c_REF_4 */
    STARTUP_SETEL2EXCEPTIONBASEADDR((Startup_EL2ExceptionTable));
    /* Set EL1 exception base address to Startup_EL1ExceptionTable */
    /* #Violation: startup_c_REF_4 */
    STARTUP_SETEL1EXCEPTIONBASEADDR((Startup_EL1ExceptionTable));
    /* Copy cloned code from flash load base address to imaged ATCM address to execute */
    Startup_InitATCMDataSection(&cloneCode);
    /* Copy cloned data from flash load base address to imaged ATCM address to execute */
    Startup_InitATCMDataSection(&cloneData);
    /* Clear cloned bss section from the imaged base address to limit address. */
    /*  Startup_InitATCMBssSection(&cloneBss); replaced by itmu init*/ 

    /* Jump to Startup_Stack_Init without pop stack */
    Startup_JumpToFunction(Startup_InitStack);
}
/****************************************************************************************************
 *   Function Name           : Startup_InitStack
 *
 *   Service ID              : 0x02.
 *
 *   Description             : Initialize the stack region from user stack to fiq stack by core id.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   TraceID                 : None.
 ****************************************************************************************************/
/* #Violation: startup_c_REF_3 */
 static void Startup_InitStack(void)
{
    /* is replaced by itmu init*/ 
    #if 0
    MultiCoreID id;
    Startup_ClearData stackInit = {NULL_PTR, NULL_PTR};

    /* Get Core ID. */
    id = Multicore_GetCoreID();

    switch(id)
    {
        case MULTICOREID_CPU0:
            /* Load CORE0_USER_STACK imaged base and CORE0_FIQ_STACK limit address to StackInit structure member */
            STARTUP_GETIMAGEBASEADDR(CORE0_USER_STACK, stackInit.clearImageAddr);
            STARTUP_GETIMAGEBSSLIMITADDR(CORE0_FIQ_STACK, stackInit.clearLimitAddr);
            break;

        case MULTICOREID_CPU1:
            /* Load CORE1_USER_STACK imaged base and CORE1_FIQ_STACK limit address to StackInit structure member */
            STARTUP_GETIMAGEBASEADDR(CORE1_USER_STACK, stackInit.clearImageAddr);
            STARTUP_GETIMAGEBSSLIMITADDR(CORE1_FIQ_STACK, stackInit.clearLimitAddr);
            break;
#if defined(THA6_THA6412)
        case MULTICOREID_CPU2:
            /* Load CORE2_USER_STACK imaged base and CORE2_FIQ_STACK limit address to StackInit structure member */
            STARTUP_GETIMAGEBASEADDR(CORE2_USER_STACK, stackInit.clearImageAddr);
            STARTUP_GETIMAGEBSSLIMITADDR(CORE2_FIQ_STACK, stackInit.clearLimitAddr);
            break;

        case MULTICOREID_CPU3:
            /* Load CORE3_USER_STACK imaged base and CORE3_FIQ_STACK limit address to StackInit structure member */
            STARTUP_GETIMAGEBASEADDR(CORE3_USER_STACK, stackInit.clearImageAddr);
            STARTUP_GETIMAGEBSSLIMITADDR(CORE3_FIQ_STACK, stackInit.clearLimitAddr);
            break;
#endif
        default:
            /* When get unexpected Core ID then assert false error. */
            Assert(FALSE);
            break;
    }

    /* Clear stack bss section from the imaged base address to limit address. */
    Startup_InitBssSection(&stackInit);
    #endif 
    /* Jump to Startup_Stack_Init without pop stack */
    Startup_JumpToFunction(Startup_InitHypStack);
}
/****************************************************************************************************
 *   Function Name           : Startup_InitHypStack
 *
 *   Service ID              : 0x03.
 *
 *   Description             : This function is to set Hypervisor sp. Then change mode form EL2 to
 *                             EL1 and set a temporary sp at 0xFF00.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   TraceID                 : None.
 ****************************************************************************************************/
/* #Violation: startup_c_REF_3 */
 static void Startup_InitHypStack(void)
{
    MultiCoreID id;

    /* Get Core ID. */
    id = Multicore_GetCoreID();

    switch(id)
    {
        case MULTICOREID_CPU0:
            /* Set Hyp stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETHYPMODESP(CORE0_HYP_STACK);
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETTEMPSVCSTACK(STARTUP_TEMPSTACKADDR_CORE0);
            break;

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
        case MULTICOREID_CPU1:
            /* Set Hyp stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETHYPMODESP(CORE1_HYP_STACK);
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETTEMPSVCSTACK(STARTUP_TEMPSTACKADDR_CORE1);
            break;

#if defined(THA6_THA6412)
        case MULTICOREID_CPU2:
            /* Set Hyp stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETHYPMODESP(CORE2_HYP_STACK);
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETTEMPSVCSTACK(STARTUP_TEMPSTACKADDR_CORE2);
            break;

        case MULTICOREID_CPU3:
            /* Set Hyp stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETHYPMODESP(CORE3_HYP_STACK);
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETTEMPSVCSTACK(STARTUP_TEMPSTACKADDR_CORE3);
            break;
#endif /* THA6_THA6412 */
#endif /* THA6_THA6206 || THA6_THA6412 */

        default:
            /* When get unexpected Core ID then assert false error. */
            Assert(FALSE);
            break;
    }
    /* Exit EL2 and Enter EL1 with SVC mode. Set temporary sp at STARTUP_TEMPSTACKADDR,
     * then jump to Startup_EL1ResetHandler. */
    Startup_ExitEL2WithSVCMode(Startup_EL1ResetHandler);
}
/****************************************************************************************************
 *   Function Name           : Startup_EL1ResetHandler
 *
 *   Service ID              : 0x04.
 *
 *   Description             : This function is to initial EL1 stack and private section by core id.
 *                             Then master core initialize the global and uncached section, and start slave core.
 *                             The slave core wait until master core set sync flag to run.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   TraceID                 : None.
 ****************************************************************************************************/
/* #Violation: startup_c_REF_3 */
 static void Startup_EL1ResetHandler(void)
{
    MultiCoreID id;
    uint32 Rt;
    /* Get Core ID. */
    id = Multicore_GetCoreID();

    /* set MPU protect XIP region: 0x50000000~0x57FFFFFF(128MB) and 0xA0000000~0xA7FFFFFF(128MB) */
    uint8 bRgNum;
    bRgNum = 0U;
    MPU_RegionAtt xipRegionCfg = {
            .MPU_StartAddress = 0x50000000,
            .MPU_RegionSize =   0x8000000, /* 128M */
            .MPU_ShareField = MPU_NONE_SHAREABLE,
            .MPU_AccPerm = MPU_EL1RO_EL0NONE,
            .MPU_XN = MPU_EXECUTE_NEVER,
            .MPU_RegionEnable = 1U,
            .MPU_AttIndex = 0U,
    };
    MPU_Hal_SetEL1Re(bRgNum, &xipRegionCfg);

    bRgNum = 1U;
    xipRegionCfg.MPU_StartAddress = 0xA0000000UL;
    MPU_Hal_SetEL1Re(bRgNum, &xipRegionCfg);

    MPU_Hal_EnableEL1Bg();

    MPU_Hal_EnableEL1();
    /* Set EL1 different mode StackPoint */
    switch(id)
    {
        case MULTICOREID_CPU0:
            /* Set SYS stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETSTACK(MODE_SYS, CORE0_USER_STACK);
            /* Set FIQ stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETSTACK(MODE_FIQ, CORE0_FIQ_STACK);
            /* Set IRQ stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETSTACK(MODE_IRQ, CORE0_IRQ_STACK);
            /* Set UNDEFINED stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETSTACK(MODE_UND, CORE0_UNDEFINED_STACK);
            /* Set ABORT stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETSTACK(MODE_ABT, CORE0_ABORT_STACK);
            /* Set SVC stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETSTACK(MODE_SVC, CORE0_KERNEL_STACK);
            break;

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
        case MULTICOREID_CPU1:
            /* Set SYS stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETSTACK(MODE_SYS, CORE1_USER_STACK);
            /* Set FIQ stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETSTACK(MODE_FIQ, CORE1_FIQ_STACK);
            /* Set IRQ stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETSTACK(MODE_IRQ, CORE1_IRQ_STACK);
            /* Set UNDEFINED stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETSTACK(MODE_UND, CORE1_UNDEFINED_STACK);
            /* Set ABORT stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETSTACK(MODE_ABT, CORE1_ABORT_STACK);
            /* Set SVC stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETSTACK(MODE_SVC, CORE1_KERNEL_STACK);
            /* Set Core1 Enter EL1 flag. then master core can do global data copy operation.*/
            /* #Violation: startup_c_REF_6 */
            while(FALSE == Gipc_Hal_GetLock(PLOCK))
            {
                ;
            }
            /* #Violation: startup_c_REF_5 */
            MULTICORE_SYNCVAR |= CPU01_ENTER_SYNC_MAGIC;
            /* #Violation: startup_c_REF_6 */
            Gipc_Hal_ReleaseLock(PLOCK);
            break;

#if defined(THA6_THA6412)
        case MULTICOREID_CPU2:
            /* Set SYS stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETSTACK(MODE_SYS, CORE2_USER_STACK);
            /* Set FIQ stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETSTACK(MODE_FIQ, CORE2_FIQ_STACK);
            /* Set IRQ stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETSTACK(MODE_IRQ, CORE2_IRQ_STACK);
            /* Set UNDEFINED stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETSTACK(MODE_UND, CORE2_UNDEFINED_STACK);
            /* Set ABORT stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETSTACK(MODE_ABT, CORE2_ABORT_STACK);
            /* Set SVC stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETSTACK(MODE_SVC, CORE2_KERNEL_STACK);
            /* Set Core2 Enter EL1 flag. then master core can do global data copy operation.*/
            /* #Violation: startup_c_REF_6 */
            while(FALSE == Gipc_Hal_GetLock(PLOCK))
            {
                ;
            }
            /* #Violation: startup_c_REF_5 */
            MULTICORE_SYNCVAR |= CPU02_ENTER_SYNC_MAGIC;
            /* #Violation: startup_c_REF_6 */
            Gipc_Hal_ReleaseLock(PLOCK);
            break;

        case MULTICOREID_CPU3:
            /* Set SYS stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETSTACK(MODE_SYS, CORE3_USER_STACK);
            /* Set FIQ stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETSTACK(MODE_FIQ, CORE3_FIQ_STACK);
            /* Set IRQ stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETSTACK(MODE_IRQ, CORE3_IRQ_STACK);
            /* Set UNDEFINED stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETSTACK(MODE_UND, CORE3_UNDEFINED_STACK);
            /* Set ABORT stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETSTACK(MODE_ABT, CORE3_ABORT_STACK);
            /* Set SVC stack(sp). */
            /* #Violation: startup_c_REF_4 */
            STARTUP_SETSTACK(MODE_SVC, CORE3_KERNEL_STACK);
            /* Set Core3 Enter EL1 flag. then master core can do global data copy operation.*/
            /* #Violation: startup_c_REF_6 */
            while(FALSE == Gipc_Hal_GetLock(PLOCK))
            {
                ;
            }
            /* #Violation: startup_c_REF_5 */
            MULTICORE_SYNCVAR |= CPU03_ENTER_SYNC_MAGIC;
            /* #Violation: startup_c_REF_6 */
            Gipc_Hal_ReleaseLock(PLOCK);
            break;
#endif /* THA6_THA6412 */
#endif /* THA6_THA6206 || THA6_THA6412 */

        default:
            /* When get unexpected Core ID then assert false error. */
            Assert(FALSE);
            break;
    }
    /* Initialize the private core code,data,bss,reserved sections. For master core, copy global
     * code/data/bss, and then start slave core. for slave core, sync with master core. */
    Startup_InitPrivateSections();

#ifdef DCACHE_ENABLE
    /* Enable DCache at startup process. */
    Startup_EnableDCache();
#endif

    /* the PL0PCTEN bit field (bit[0]) of the CNTKCTL register needs 
     * to be configured in EL1 mode first, and then switched to EL0 mode. After that, the function 
     * Stm_Hal_GetValue can be used normally.The reference code for modifying the register is as follows: */
    GET_CP(15, 0, Rt, 14, 1, 0);
    Rt = Rt | 0x1; /* Set the PL0PCTEN of CNTKCTL to 1 */
    SET_CP(15, 0, Rt, 14, 1, 0);

    /* data sync here. */
    /* #Violation: startup_c_REF_4 */
    DMB();
    /* enable interrupt */
    ASM_VOLATILE(" cpsie if  \n");
    /* Go to main. use _main to support tasking compiler */
    (void)_main();
    /* If unexpected return form main, loop in Startup_InfiniteLoop to avoid program shutdown. */
    Startup_InfiniteLoop();
}
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/****************************************************************************************************
 *   Function Name           : Start
 *
 *   Service ID              : 0x00.
 *
 *   Description             : This function is the entry that the program first execute.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   TraceID                 : None.
 ****************************************************************************************************/
#define SDK_START_SEC_CODE_GLOBAL
/* #Violation: startup_c_REF_2 */
#include "Sdk_MemMap.h"
ATTR_NAKED void Start(void)
{
    /* Set temporary sp at STARTUP_TEMPSTACKADDR_CORE0 for core0 and STARTUP_TEMPSTACKADDR_CORE1
     * for core1 to support multicore run at the same time.
     */
    /* #Violation: startup_c_REF_4 */
    ASM_VOLATILE
    (
        " cpsie a \n"
        " ldr r0, =0x10000200 \n"
        " ldr r1, =0x10000400 \n"
        " ldr r2, =0x10000600 \n"
        " ldr r3, =0x10000800 \n"
        " ldr r9, =0xFFFF \n"
        " ldr r10, =0x100 \n"
        " ldr r11, =0x101 \n"
        " mrc p15, 0, r4, c0, c0, 5\n"
        " and r4, r4, r9\n"
        " cmp r4, #0\n"
        " beq core0Pro\n"
        " cmp r4, #1\n"
        " beq core1Pro\n"
        " cmp r4, r10\n"
        " beq core2Pro\n"
        " cmp r4, r11\n"
        " beq core3Pro\n"
        "core0Pro: mov sp, r0\n"
        " b ProEnd\n"
        "core1Pro: mov sp, r1\n"
        " b ProEnd\n"
        "core2Pro: mov sp, r2\n"
        " b ProEnd\n"
        "core3Pro: mov sp, r3\n"
        "ProEnd:mov r0, sp\n"
        " mov r1, #0x21\n" /* 16*(0x21-1) = 0x200 */
        " sub r0, r0, #0x200\n"
        "1:stm r0!, {r5-r8}\n"/* clear teamp stack,MULTICORE_SYNCVAR,PLOCK*/
        " subs r1,r1,#1\n"
#ifdef __TASKING__
        " bgt 1p\n"
#else
        " bgt 1b\n"
#endif
        " isb\n"
        " ldr r0,=Startup_InitCloneSections\n"
        " bx r0"
    );
}
#define SDK_STOP_SEC_CODE_GLOBAL
/* #Violation: startup_c_REF_2 */
#include "Sdk_MemMap.h"

