/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_mpu_types.h
*
*   Platform              : AUTOSAR
*
*   BSW Module            : Os
*
*   brief                 : xxx
*
*   Autosar Version       : R23-11
*
*   Build Version         : Cortex-R52/THA6206
*
*   Copyright (c) @#
*   All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Revision Control History                                               **
****************************************************************************************************/
/*
*  -------------------------------------------------------------------------------------------------
*  Version    Date           Author(ID)      SVN_Version         Description
*  -------------------------------------------------------------------------------------------------
*  V0.0.1   22-May-2024    zhangtr(30011)                        Initial Version
*  V0.1.0   4-June-2024    Pony(00412)                           Add Initial Code
****************************************************************************************************/
#ifndef OS_MPU_TYPES_H_
#define OS_MPU_TYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
//#include "Os_mpu_hal.h"
#include "datatypes.h"
#include "Compiler.h"

/****************************************************************************************************
**                          Global Macro  Definitions                                          **
****************************************************************************************************/
/*PRBAR Register Start */
#define  MPU_EXECUTE_ALLOWED           (0x0U << 0U)  /*allowed execute */
#define  MPU_EXECUTE_NEVER             (0x01U<< 0U)  /*execute never */

/*Data access permissions for EL1-controlled MPU */
#define MPU_EL1_RW_EL0_NONE     (0x0U<<1U)        /* EL1 Read and Write,EL0 None     */
#define MPU_EL1_RW_EL0_RW       (0x1U<<1U)        /* EL1 Read and Write,EL0 Read and Write  */                                               /* EL1 Read and Write,EL0 Read and Write  */
#define MPU_EL1_R_EL0_NONE      (0x2U<<1U)        /* EL1 Read only,EL0 None  */
#define MPU_EL1_R_EL0_R         (0x3U<<1U)        /* EL1 Read only,EL0 Read only  */

/*field encoding for Normal memory*/
#define MPU_NON_SHAREABLE       (0x0U<<3U)       /* Non-shareable  */
#define MPU_UNPREDICTABLE       (0x1U<<3U)       /* UNPREDICTABLE */
#define MPU_OUTER_SHAREABLE     (0x2U<<3U)       /* Outer Shareable */
#define MPU_INNER_SHAREABLE     (0x3U<<3U)       /* Inner Shareable  */
/*PRBAR Register End */

/*PRLAR Register Start */
#define MPU_REGION_ENABLE              (0x01U << 0U)
/*PRLAR Register End */

/*The alignment of each chip MPU*/
#define MPU_REGION_ALIGNMENT_MASK          (uint32)(0x3FU)

#define MPU_REGION_ALIGNMENT                (uint32)(0x40U)

/*Memory attribute index */

/* Device memory : non Gathering, non Re-ordering, non Early Write Acknowledgment. */
#define  MPU_MEMORY_TYPE_DEVICE_nGnRnE  (uint8)(0x0U<<0U)

/* Device memory : non Gathering, non Re-ordering, Early Write Acknowledgment. */
#define MPU_MEMORY_TYPE_DEVICE_nGnRE   (uint8)(0x1U<<2U)

/* Device memory : non Gathering, Re-ordering, Early Write Acknowledgment. */
#define MPU_MEMORY_TYPE_DEVICE_nGRE    (uint8)(0x1U<<3U)

/* Device memory : Gathering, Re-ordering, Early Write Acknowledgment. */
#define MPU_MEMORYS_TYPE_DEVICE_GRE     (uint8)(0x3U<<0U)

/* Normal Memory, Outer Write-Back transient */
#define MPU_MEMORY_NORMAL_OUTER_WRITEBACK_TRANSIENT         (uint8)(0x04U << 4U)

/* Normal Memory, Outer Write-Through non-transient */
#define MPU_MEMORY_TYPE_NORMAL_OUTER_WRITETHROUGH_NON_TRANSIENT  (uint8)(0x02U << 4U)

/* Normal Memory, Outer Write-Back non-transient */
#define MPU_MEMORY_TYPE_NORMAL_OUTER_WRITEBACK_NON_TRANSIENT  (uint8)(0x03U << 4U)

enum {
    ATT_NORMAL_OUTER_WRITEBACK_NON_TRANSIENT_INDEX = 0,
    ATT_NORMAL_OUTER_WRITETHROUGH_NON_TRANSIENT_INDEX,
    ATT_NORMAL_OUTER_WRITEBACK_TRANSIENT_INDEX,
    ATT_DEVICE_nGnRnE_INDEX,
    ATT_DEVICE_nGnRE_INDEX,
    ATT_DEVICE_nGRE_INDEX,
    ATT_DEVICE_GRE_INDEX,
    ATT_MAX_COUNT
};

/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/

/* [SWS_Os_00780] This data type is a pointer which is able to point to any location in the MCU address space*/
typedef P2CONST(void, TYPEDEF, OS_VAR_NOINIT) MemoryStartAddressType;

/*[SWS_Os_00781] This data type holds the size (in bytes) of a memory region*/
typedef uint32 MemorySizeType;

typedef uint32 AccessObjectType;
/*[SWS_Os_91000] AreaIdType identifies a peripheral area and is used by the API functions: ReadPeripheralX, Write
PeripheralX and ModifyPeripheralX*/
typedef uint16 AreaIdType;

/****************************************************************************************************
**                          Global Enumeration Definitions                                          **
****************************************************************************************************/
typedef enum
{
    OS_MEM_ACCESS_NON     = 0U<<0U,                                                /* No access     */
    OS_MEM_ACCESS_READ    = 1U<<0U,                                                /* Read access   */
    OS_MEM_ACCESS_WRITE   = 1U<<1U,                                                /* Write access  */
    OS_MEM_ACCESS_RW      = OS_MEM_ACCESS_READ|OS_MEM_ACCESS_WRITE,                /* Read and Write access  */
    OS_MEM_ACCESS_EXECUTE = 1U<<2U,                                                /* Execution  access  */
    OS_MEM_ACCESS_REX     = OS_MEM_ACCESS_READ|OS_MEM_ACCESS_EXECUTE,              /*Read and Execute  */
    OS_MEM_ACCESS_WEX     = OS_MEM_ACCESS_WRITE|OS_MEM_ACCESS_EXECUTE,             /* Write and Execute   */
    OS_MEM_ACCESS_RWEX    = OS_MEM_ACCESS_READ|OS_MEM_ACCESS_WRITE|OS_MEM_ACCESS_EXECUTE,  /* Read Write  and Execute */
    OS_MEM_ACCESS_STACK   = 1U<<3U,
    OS_MEM_ACCESS_SR      = OS_MEM_ACCESS_READ|OS_MEM_ACCESS_STACK,
    OS_MEM_ACCESS_SW      = OS_MEM_ACCESS_WRITE|OS_MEM_ACCESS_STACK,
    OS_MEM_ACCESS_SRW     = OS_MEM_ACCESS_READ|OS_MEM_ACCESS_WRITE|OS_MEM_ACCESS_STACK,
    OS_MEM_ACCESS_SEX     = OS_MEM_ACCESS_EXECUTE| OS_MEM_ACCESS_STACK,
    OS_MEM_ACCESS_SREX    = OS_MEM_ACCESS_READ|OS_MEM_ACCESS_EXECUTE| OS_MEM_ACCESS_STACK,
    OS_MEM_ACCESS_SWEX    = OS_MEM_ACCESS_WRITE|OS_MEM_ACCESS_EXECUTE| OS_MEM_ACCESS_STACK,
    OS_MEM_ACCESS_SRWEX   = OS_MEM_ACCESS_READ|OS_MEM_ACCESS_WRITE|OS_MEM_ACCESS_EXECUTE| OS_MEM_ACCESS_STACK,
} OsAccess_RightType;

typedef enum
{
    MPU_INIT_STACK_REGION       = 0x01U,                           /* Initialize the stack region in starting processing   */
    MPU_SWITCH_STACK_REGION     = 0x02U,                           /* switch the stack region during context switch   */
} OsMpu_SwitchType;

/****************************************************************************************************
**                          Global Union Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/
/*The definition used to set region: region number, PRBAR register,which include base address and access right
* and PRLAR register,which include end address and attribute index.
*/
typedef struct
{
    uint32 RegionNum;                    /* PRSELR Register- Region number */
    uint32 RegionBaseAddr;               /* PRBAR Register - Region start address*/
    uint32 RegionEndAddr;                /* PRLAR Register - Region end address*/
    uint32 AccessControl;               /*!< Region base address (PRBAR). */
    uint32 EnableFlags;                 /*!< Region base address (PRLAR). */
} Os_HalMpuRegionType;

/*The definition of region configuration, the fields include region count and region information*/
typedef struct
{
    uint32 RegionCounts;   /*Region count */
    P2CONST(Os_HalMpuRegionType, TYPEDEF, OS_CONST) MpuRegions;  /* type parameters */
} Os_MpuConfigType;

/*The definition of the stack region: start address and end address of the Object stack*/
typedef struct 
{
    uint32 StartAddress;
    uint32 EndAddress;
} Os_HalStackConfigAddressType;

typedef struct
{
    P2CONST(Os_MpuConfigType, TYPEDEF, OS_CONST)  CoreMpuCfg;
    P2CONST(Os_HalStackConfigAddressType, TYPEDEF, OS_CONST)  CoreStackCfg;
} Os_HalCoreMpuConfigType;

/*The struct define the access right of region for Object*/
typedef struct
{
    uint32 StartAddress;
    uint32 EndAddress;
    OsAccess_RightType AccessRights;    /* The access right incudes Read, Write, Execute and combined of each one*/
} Os_AccessRegionConfig;

/*The struct define the region count and region information for Object*/
typedef struct 
{
    uint32 RegionCount;
    P2CONST(Os_AccessRegionConfig, TYPEDEF, OS_CONST) RegionInfo;
} Os_AccessConfigType;

/*The struct define the region count and region information for Peripheral*/
typedef struct 
{
    uint32 StartAddress;
    uint32 EndAddress;
    uint32 ApplicationMask;
} Os_PeripheralConfigType;

#endif /* OS_MPU_TYPES_H_ */

/****************************************************************************************************
**     End of File: Os_mpu_types.h                                                                 **
****************************************************************************************************/
