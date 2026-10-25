/****************************************************************************************************
 *
****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Spi.c
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : ESPI
 *
 *   brief                 : This file contains all functions of Spi Driver
 *
 *   Autosar Version       : 4.4.0
 *
 *   Build Version         : Cortex-R52+/THA6xxx
 *
 *   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
 *
****************************************************************************************************/
/*
*#Violation Summary
*
*#Spi_c_REF_1:MISRAC2012-Dir-4.9;
* Justification: Function like macros are used to reduce code complexity.
*
*#Spi_c_REF_2:CWE-1071;
* Justification: MISRA-2012 Rule 15.7/Rule 16.4 require reserved empty code block.
*
*#Spi_c_REF_3:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access.
*
*#Spi_c_REF_4:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*#Spi_c_REF_5:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
*#Spi_c_REF_6:MISRAC2012-Rule-11.8;
* Justification: In the software design, a non-const pointer references both IB and EB buffers to reduce code complexity. The software design ensures the source buffer remains unmodified during EB operations.
*
*#Spi_c_REF_7:MISRAC2012-Rule-20.1;
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Spi_c_REF_8:MISRAC2012-Rule-20.10; 
* Justification: Use glue operator to construct the exclusive area function name.
*
*#Spi_c_REF_9:CertC-DCL00-C; 
* Justification: Parameter declared refer to AUTOSAR specifications.
*
*#Spi_c_REF_10:CertC-EXP05-C;
* Justification: In the software design, a non-const pointer references both IB and EB buffers to reduce code complexity. The software design ensures the source buffer remains unmodified during EB operations.
*
*#Spi_c_REF_11:CertC-PRE00-C;
* Justification: Function like macros are used to reduce code complexity.
*
*#Spi_c_REF_12:MISRAC2012-Rule-2.2;
* Justification: Platform-based design with configurable macros.
*
*#Spi_c_REF_13:MISRAC2012-Rule-8.9;
* Justification: Static global variables are placed in non-cached RAM regions to ensure accessibility by multiple cores.
*
*/
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Spi.h"
#include "Mcall.h"
#include "Spi_Cfg.h"
#include "SchM_Spi.h"
#include "espi_hal.h"
#include "rcc_hal.h"
#include "Spi_Version.h"
#if (SPI_CUSTOMIZED_CS_EN == STD_ON)
#include "Dio.h"
#endif /* (SPI_CUSTOMIZED_CS_EN \== STD_ON) */
/* Included for the declaration of Det_ReportError() */
#include "Det.h"

#if (SPI_DEM_REPORT_ERROR_STATUS == STD_ON)
/* Included for the declaration of Dem_SetEventStatus() */
#include "Dem.h"
#endif /* (SPI_DEM_REPORT_ERROR_STATUS  \== STD_ON) */
/****************************************************************************************************
**                          Version Checks                                                         **
****************************************************************************************************/
#if (SPI_VENDOR_ID != SPI_CFG_VENDOR_ID)
  #error "Spi.c : Mismatch in Vendor ID"
#endif /* (SPI_VENDOR_ID \!= SPI_CFG_VENDOR_ID) */

#if (SPI_MODULE_ID != SPI_CFG_MODULE_ID)
  #error "Spi.c : Mismatch in Module ID"
#endif /* \(SPI_MODULE_ID != SPI_CFG_MODULE_ID) */

#if (SPI_AR_RELEASE_MAJOR_VERSION != SPI_CFG_AR_RELEASE_MAJOR_VERSION)
  #error "Spi.c : Mismatch in Release Major Version"
#endif /* (SPI_AR_RELEASE_MAJOR_VERSION \!= SPI_CFG_AR_RELEASE_MAJOR_VERSION) */

#if (SPI_AR_RELEASE_MINOR_VERSION != SPI_CFG_AR_RELEASE_MINOR_VERSION)
  #error "Spi.c : Mismatch in Release Minor Version"
#endif /* (SPI_AR_RELEASE_MINOR_VERSION \!= SPI_CFG_AR_RELEASE_MINOR_VERSION) */

#if (SPI_AR_RELEASE_REVISION_VERSION != SPI_CFG_AR_RELEASE_REVISION_VERSION)
  #error "Spi.c : Mismatch in Release Revision Version"
#endif /* (SPI_AR_RELEASE_REVISION_VERSION \!= SPI_CFG_AR_RELEASE_REVISION_VERSION) */

#if (SPI_SW_MAJOR_VERSION != SPI_CFG_SW_MAJOR_VERSION)
  #error "Spi.c : Mismatch in Software Major Version"
#endif /* (SPI_SW_MAJOR_VERSION \!= SPI_CFG_SW_MAJOR_VERSION) */

#if (SPI_SW_MINOR_VERSION != SPI_CFG_SW_MINOR_VERSION)
  #error "Spi.c : Mismatch in Software Minor Version"
#endif /* (SPI_SW_MINOR_VERSION \!= SPI_CFG_SW_MINOR_VERSION) */

#if (SPI_SW_PATCH_VERSION != SPI_CFG_SW_PATCH_VERSION)
  #error "Spi.c : Mismatch in Software Patch Version"
#endif /* \(SPI_SW_PATCH_VERSION != SPI_CFG_SW_PATCH_VERSION) */

#if (SPI_ENABLE_DMA == STD_ON)
#if (DMA_CFG_CHANNEL_CANCEL_API != STD_ON)
  #error "Spi.c : SPI DMA requires DMA_CFG_CHANNEL_CANCEL_API == STD_ON to abort a DMA Job"
#endif /* (DMA_CFG_CHANNEL_CANCEL_API \!= STD_ON) */
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
#define SPI_JOB_NULL                                   ((Spi_JobType)(0xFFFFU))
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */

/* Mask: FIFO maximum settable threshold */
#define SPI_AVAILABLE_FIFOLEVEL                        (0x0FU)
/* Mask: Clear the data length and data shift direction bits in the channel dynamic configuration */
#define SPI_CH_CONFIG_CLR                              (0xF05FFFFFUL)
/* Mask: Get the data length bits in the channel dynamic configuration */
#define SPI_DATAWIDTH_MASK                             (23U)
/* Mask: Get the data shift direction bits in the channel dynamic configuration */
#define SPI_SHIFTORDER_MASK                            (21U)
/* Mask: DMA channels not used */
#define SPI_DMACHNOUSED_MASK                           (0xFFU)
#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
/* Mask: half of the range of the free running 64 bit system timer. A deadline whose unsigned
   distance to the current count exceeds half of the range has already been passed: comparing the
   difference instead of the counts keeps the decision correct across a counter wrap */
#define SPI_TIMEOUT_TIMER_HALFRANGE                    (0x8000000000000000ULL)
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */
/* Mask: Mask value range 0~3 */
#define SPI_RANGE_0TO3_MASK                            (0x03U)

/* Get Sequence configuration information structure pointer */
/* #Violation: Spi_c_REF_11 */ 
/* #Violation: Spi_c_REF_1 */
#define SPI_SEQ_CONFIGPTR(CoreId, Sequence) \
(&(Spi_ConfigPtr->CoreConfigPtr[CoreId]->SeqCfgPtr[Spi_ConfigPtr->SequenceToCorePtr[Sequence]])) 
/* Get Sequence status information structure pointer */
/* #Violation: Spi_c_REF_11 */ 
/* #Violation: Spi_c_REF_1 */
#define SPI_SEQ_STATUSPTR(CoreId, Sequence) \
(&(Spi_CoreStatus[CoreId]->SequenceStatusPtr[Spi_ConfigPtr->SequenceToCorePtr[Sequence]])) 
/* Get Sequence status information, the input parameter is the Sequence ID */
/* #Violation: Spi_c_REF_11 */ 
/* #Violation: Spi_c_REF_1 */
#define SPI_SEQ_STATUS(CoreId, Sequence) \
(Spi_CoreStatus[CoreId]->SequenceStatusPtr[Spi_ConfigPtr->SequenceToCorePtr[Sequence]].SeqResult) 

/* Get Job configuration information structure pointer */
/* #Violation: Spi_c_REF_11 */ 
/* #Violation: Spi_c_REF_1 */
#define SPI_JOB_CONFIGPTR(CoreId, Job) \
(&(Spi_ConfigPtr->CoreConfigPtr[CoreId]->JobCfgPtr[Spi_ConfigPtr->JobToCorePtr[(Job)]])) 
/* Get Job configuration information structure pointer */
/* #Violation: Spi_c_REF_11 */ 
/* #Violation: Spi_c_REF_1 */
#define SPI_CURJOB_CONFIGPTR(CoreId, PhyUnit) \
(Spi_CoreStatus[CoreId]->DeviceStatePtr[Spi_ConfigPtr->PhyUnitToCorePtr[(PhyUnit)]].CurJobPtr) 
/* Get Job status information, the input parameter is the Job ID */
/* #Violation: Spi_c_REF_11 */ 
/* #Violation: Spi_c_REF_1 */
#define SPI_JOB_STATUS(CoreId, Job) \
(Spi_ConfigPtr->CoreConfigPtr[CoreId]->JobCfgPtr[Spi_ConfigPtr->JobToCorePtr[(Job)]].JobStatePtr->JobResult) 

/* Get Channel configuration information structure pointer */
/* #Violation: Spi_c_REF_11 */ 
/* #Violation: Spi_c_REF_1 */
#define SPI_CH_CONFIGPTR(CoreId, Channel) \
(&(Spi_ConfigPtr->CoreConfigPtr[CoreId]->ChannelCfgPtr[Spi_ConfigPtr->ChannelToCorePtr[(Channel)]])) 
/* Get external device configuration information structure pointer */
/* #Violation: Spi_c_REF_11 */ 
/* #Violation: Spi_c_REF_1 */
#define SPI_EXD_CONFIGPTR(CoreId, ExDevice) \
(&(Spi_ConfigPtr->CoreConfigPtr[CoreId]->ExDeviceCfgPtr[Spi_ConfigPtr->ExDeviceToCorePtr[(ExDevice)]])) 
/* Get external status information structure pointer */
/* #Violation: Spi_c_REF_11 */ 
/* #Violation: Spi_c_REF_1 */
#define SPI_EXD_STATUSPTR(CoreId, PhyUnit) \
(&(Spi_CoreStatus[CoreId]->DeviceStatePtr[Spi_ConfigPtr->PhyUnitToCorePtr[(PhyUnit)]])) 

/* Get PhyUnit configuration information structure pointer */
/* #Violation: Spi_c_REF_11 */ 
/* #Violation: Spi_c_REF_1 */
#define SPI_HWUNIT_CONFIGPTR(CoreId, PhyUnit) \
(&(Spi_ConfigPtr->CoreConfigPtr[CoreId]->PhyUnitCfgPtr[Spi_ConfigPtr->PhyUnitToCorePtr[(PhyUnit)]])) 
/* Get PhyUnit status information structure pointer */
/* #Violation: Spi_c_REF_11 */ 
/* #Violation: Spi_c_REF_1 */
#define SPI_HWUNIT_STATUSPTR(CoreId, PhyUnit) \
(&(Spi_CoreStatus[CoreId]->PhyUnitStatusPtr[Spi_ConfigPtr->PhyUnitToCorePtr[(PhyUnit)]])) 
/* Get PhyUnit status information, the input parameter is the PhyUnit ID */
/* #Violation: Spi_c_REF_11 */ 
/* #Violation: Spi_c_REF_1 */
#define SPI_HWUNIT_STATUS(CoreId, PhyUnit) \
(Spi_CoreStatus[CoreId]->PhyUnitStatusPtr[Spi_ConfigPtr->PhyUnitToCorePtr[(PhyUnit)]].PhyUnitStatus) 

/* Get the asynchronous communication working Mode */
/* #Violation: Spi_c_REF_11 */ 
/* #Violation: Spi_c_REF_1 */
#define SPI_ASYNC_MODE(CoreId) \
(*(Spi_CoreStatus[CoreId]->AsyncMode)) 
/****************************************************************************************************
*                          SchM Critical Section Protection Macros                                 **
****************************************************************************************************/
/* #Violation: Spi_c_REF_11 */
/* #Violation: Spi_c_REF_8 */ 
#define SPI_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Spi_##Exclusive_Area() 
/* #Violation: Spi_c_REF_11 */
/* #Violation: Spi_c_REF_8 */ 
#define SPI_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Spi_##Exclusive_Area() 
/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
/* Define the channel state structure on multi-Core0 */
#if (SPI_MAX_HWUNIT_CORE0 > 0U)

/* #Violation: Spi_c_REF_4 */ 
#define SPI_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED 
#include "Spi_MemMap.h" 

static Spi_SequenceStateType             Spi_SequenceStateCore0[SPI_MAX_SEQUENCE_CORE0];
static Spi_PhyUnitStateType              Spi_PhyUnitStateCore0[SPI_MAX_HWUNIT_CORE0];
static Spi_DeviceStateType               Spi_DeviceStateCore0[SPI_MAX_HWUNIT_CORE0];
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
/* Records whether a synchronous sequence is being transmitted
* 0: idle
* 1: busy  */
static uint16                            Spi_SyncTransferStatusCore0;
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */
/* bitx = 1 means Spix belongs to a declared Sequence whose teardown is not yet complete;
   see Spi_CoreStatusType::PhyUnitPendingTeardownStatusPtr */
static uint16                            Spi_PendingTeardownStatusCore0;
#if (SPI_DEV_ERROR_DETECT == STD_ON)
static Spi_DriverStateType               Spi_InitStatusCore0;
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */

/* #Violation: Spi_c_REF_4 */ 
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED 
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h" 


#if (SPI_LEVEL_DELIVERED == SPI_LEVEL1)
/* #Violation: Spi_c_REF_4 */ 
#define SPI_START_SEC_VAR_INIT_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h"
/* Asynchronous operating mode of the ESPI unit */
static Spi_AsyncModeType                 Spi_AsyncModeCore0 = SPI_INTERRUPT_MODE;
/* #Violation: Spi_c_REF_4 */ 
#define SPI_STOP_SEC_VAR_INIT_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h"
#elif (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
/* #Violation: Spi_c_REF_4 */ 
#define SPI_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED 
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h"
static Spi_AsyncModeType                 Spi_AsyncModeCore0;
/* #Violation: Spi_c_REF_4 */ 
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED 
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h"
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */

/* #Violation: Spi_c_REF_4 */ 
#define SPI_START_SEC_CONST_ASIL_D_CORE0_UNSPECIFIED 
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h" 
static const Spi_CoreStatusType Spi_StatusSetCore0 =
{
    &Spi_SequenceStateCore0[0]
    ,&Spi_PhyUnitStateCore0[0]
    ,&Spi_DeviceStateCore0[0]
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    ,&Spi_InitStatusCore0
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
    ,&Spi_AsyncModeCore0
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
    ,&Spi_SyncTransferStatusCore0
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */
    ,&Spi_PendingTeardownStatusCore0
};

/* #Violation: Spi_c_REF_4 */
#define SPI_STOP_SEC_CONST_ASIL_D_CORE0_UNSPECIFIED 
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h" 

#endif /* (SPI_MAX_HWUNIT_CORE0 \> 0U) */

/* Define the channel state structure on multi-Core1 */
#if (MCAL_NUMBER_OF_CORES > 1U)
#if (SPI_MAX_HWUNIT_CORE1 > 0U)

/* #Violation: Spi_c_REF_4 */ 
#define SPI_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED 
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h" 

static Spi_SequenceStateType             Spi_SequenceStateCore1[SPI_MAX_SEQUENCE_CORE1];
static Spi_PhyUnitStateType              Spi_PhyUnitStateCore1[SPI_MAX_HWUNIT_CORE1];
static Spi_DeviceStateType               Spi_DeviceStateCore1[SPI_MAX_HWUNIT_CORE1];
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
/* Records whether a synchronous sequence is being transmitted
* 0: idle
* 1: busy  */
static uint16                            Spi_SyncTransferStatusCore1;
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */
static uint16                            Spi_PendingTeardownStatusCore1;
#if (SPI_DEV_ERROR_DETECT == STD_ON)
static Spi_DriverStateType               Spi_InitStatusCore1;
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */

/* #Violation: Spi_c_REF_4 */ 
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED 
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h" 

#if (SPI_LEVEL_DELIVERED == SPI_LEVEL1)
/* #Violation: Spi_c_REF_4 */ 
#define SPI_START_SEC_VAR_INIT_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h"
/* Asynchronous operating mode of the ESPI unit */
static Spi_AsyncModeType                 Spi_AsyncModeCore1 = SPI_INTERRUPT_MODE;
/* #Violation: Spi_c_REF_4 */ 
#define SPI_STOP_SEC_VAR_INIT_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h"
#elif (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
/* #Violation: Spi_c_REF_4 */ 
#define SPI_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED 
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h" 
static Spi_AsyncModeType                 Spi_AsyncModeCore1;
/* #Violation: Spi_c_REF_4 */ 
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED 
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h"
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */

/* #Violation: Spi_c_REF_4 */ 
#define SPI_START_SEC_CONST_ASIL_D_CORE1_UNSPECIFIED 
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h" 

static const Spi_CoreStatusType Spi_StatusSetCore1 =
{
    &Spi_SequenceStateCore1[0]
    ,&Spi_PhyUnitStateCore1[0]
    ,&Spi_DeviceStateCore1[0]
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    ,&Spi_InitStatusCore1
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
    ,&Spi_AsyncModeCore1
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
    ,&Spi_SyncTransferStatusCore1
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */
    ,&Spi_PendingTeardownStatusCore1
};

/* #Violation: Spi_c_REF_4 */
#define SPI_STOP_SEC_CONST_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h" 

#endif /* (SPI_MAX_HWUNIT_CORE1 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 1U) */

/* Define the channel state structure on multi-Core2 */
#if (MCAL_NUMBER_OF_CORES > 2U)
#if (SPI_MAX_HWUNIT_CORE2 > 0U)
/* #Violation: Spi_c_REF_4 */ 
#define SPI_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED 
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h" 

static Spi_SequenceStateType             Spi_SequenceStateCore2[SPI_MAX_SEQUENCE_CORE2];
static Spi_PhyUnitStateType              Spi_PhyUnitStateCore2[SPI_MAX_HWUNIT_CORE2];
static Spi_DeviceStateType               Spi_DeviceStateCore2[SPI_MAX_HWUNIT_CORE2];
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
/* Records whether a synchronous sequence is being transmitted
* 0: idle
* 1: busy  */
static uint16                            Spi_SyncTransferStatusCore2;
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */
static uint16                            Spi_PendingTeardownStatusCore2;
#if (SPI_DEV_ERROR_DETECT == STD_ON)
static Spi_DriverStateType               Spi_InitStatusCore2;
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */

/* #Violation: Spi_c_REF_4 */ 
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED 
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h" 

#if (SPI_LEVEL_DELIVERED == SPI_LEVEL1)
/* #Violation: Spi_c_REF_4 */ 
#define SPI_START_SEC_VAR_INIT_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h"
/* Asynchronous operating mode of the ESPI unit */
static Spi_AsyncModeType                 Spi_AsyncModeCore2 = SPI_INTERRUPT_MODE;
/* #Violation: Spi_c_REF_4 */ 
#define SPI_STOP_SEC_VAR_INIT_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h"
#elif (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
/* #Violation: Spi_c_REF_4 */ 
#define SPI_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED 
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h" 
static Spi_AsyncModeType                 Spi_AsyncModeCore2;
/* #Violation: Spi_c_REF_4 */ 
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED 
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h" 
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */

/* #Violation: Spi_c_REF_4 */ 
#define SPI_START_SEC_CONST_ASIL_D_CORE2_UNSPECIFIED 
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h" 

static const Spi_CoreStatusType Spi_StatusSetCore2 =
{
    &Spi_SequenceStateCore2[0]
    ,&Spi_PhyUnitStateCore2[0]
    ,&Spi_DeviceStateCore2[0]
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    ,&Spi_InitStatusCore2
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
    ,&Spi_AsyncModeCore2
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
    ,&Spi_SyncTransferStatusCore2
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */
    ,&Spi_PendingTeardownStatusCore2
};

/* #Violation: Spi_c_REF_4 */
#define SPI_STOP_SEC_CONST_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h" 
#endif /* (SPI_MAX_HWUNIT_CORE2 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 2U) */

/* Define the channel state structure on multi-Core3 */
#if (MCAL_NUMBER_OF_CORES > 3U)
#if (SPI_MAX_HWUNIT_CORE3 > 0U)
/* #Violation: Spi_c_REF_4 */ 
#define SPI_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED 
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h" 

static Spi_SequenceStateType             Spi_SequenceStateCore3[SPI_MAX_SEQUENCE_CORE3];
static Spi_PhyUnitStateType              Spi_PhyUnitStateCore3[SPI_MAX_HWUNIT_CORE3];
static Spi_DeviceStateType               Spi_DeviceStateCore3[SPI_MAX_HWUNIT_CORE3];
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
/* Records whether a synchronous sequence is being transmitted
* 0: idle
* 1: busy  */
static uint16                            Spi_SyncTransferStatusCore3;
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */
static uint16                            Spi_PendingTeardownStatusCore3;
#if (SPI_DEV_ERROR_DETECT == STD_ON)
static Spi_DriverStateType               Spi_InitStatusCore3;
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */

/* #Violation: Spi_c_REF_4 */ 
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED 
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h" 


#if (SPI_LEVEL_DELIVERED == SPI_LEVEL1)
/* #Violation: Spi_c_REF_4 */ 
#define SPI_START_SEC_VAR_INIT_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h"
/* Asynchronous operating mode of the ESPI unit */
static Spi_AsyncModeType                 Spi_AsyncModeCore3 = SPI_INTERRUPT_MODE;
/* #Violation: Spi_c_REF_4 */ 
#define SPI_STOP_SEC_VAR_INIT_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h"
#elif (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
/* #Violation: Spi_c_REF_4 */ 
#define SPI_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED 
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h" 
static Spi_AsyncModeType                 Spi_AsyncModeCore3;
/* #Violation: Spi_c_REF_4 */ 
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED 
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h" 
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */

/* #Violation: Spi_c_REF_4 */ 
#define SPI_START_SEC_CONST_ASIL_D_CORE3_UNSPECIFIED 
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h" 

static const Spi_CoreStatusType Spi_StatusSetCore3 =
{
    &Spi_SequenceStateCore3[0]
    ,&Spi_PhyUnitStateCore3[0]
    ,&Spi_DeviceStateCore3[0]
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    ,&Spi_InitStatusCore3
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
    ,&Spi_AsyncModeCore3
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
    ,&Spi_SyncTransferStatusCore3
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */
    ,&Spi_PendingTeardownStatusCore3
};

/* #Violation: Spi_c_REF_4 */ 
#define SPI_STOP_SEC_CONST_ASIL_D_CORE3_UNSPECIFIED 
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h" 
#endif /* (SPI_MAX_HWUNIT_CORE3 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 3U) */

/* #Violation: Spi_c_REF_4 */ 
#define SPI_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE 
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h" 

#if (SPI_ENABLE_DMA == STD_ON)
/* #Violation: Spi_c_REF_13 */ 
static uint32                           Spi_RxBuffer;
#endif /* SPI_ENABLE_DMA \== STD_ON */
static P2CONST(Spi_ConfigType, AUTOMATIC, SPI_APPL_DATA) Spi_ConfigPtr;

/* #Violation: Spi_c_REF_4 */ 
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE 
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h" 
/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/
/* #Violation: Spi_c_REF_4 */ 
#define SPI_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED 
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h" 

/* Pointer to the SPI HW unit data structure set for each core */
static CONSTP2CONST(Spi_CoreStatusType, SPI_VAR, SPI_APPL_CONST)
                                        Spi_CoreStatus[MCAL_NUMBER_OF_CORES] =
{
/* Define the channel state structure on multi-Core0 */
#if (SPI_MAX_HWUNIT_CORE0 > 0U)
    &Spi_StatusSetCore0
#else
    NULL_PTR
#endif /* (SPI_MAX_HWUNIT_CORE0 \> 0U) */

/* Define the channel state structure on multi-Core1 */
#if (MCAL_NUMBER_OF_CORES > 1U)
#if (SPI_MAX_HWUNIT_CORE1 > 0U)
    ,&Spi_StatusSetCore1
#else
    ,NULL_PTR
#endif /* (SPI_MAX_HWUNIT_CORE1 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 1U) */

/* Define the channel state structure on multi-Core2 */
#if (MCAL_NUMBER_OF_CORES > 2U)
#if (SPI_MAX_HWUNIT_CORE2 > 0U)
    ,&Spi_StatusSetCore2
#else
    ,NULL_PTR
#endif /* (SPI_MAX_HWUNIT_CORE2 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 2U) */

/* Define the channel state structure on multi-Core3 */
#if (MCAL_NUMBER_OF_CORES > 3U)
#if (SPI_MAX_HWUNIT_CORE3 > 0U)
    ,&Spi_StatusSetCore3
#else
    ,NULL_PTR
#endif /* (SPI_MAX_HWUNIT_CORE3 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 3U) */
};

/* #Violation: Spi_c_REF_4 */ 
#define SPI_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED 
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h" 
/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
/* #Violation: Spi_c_REF_4 */ 
#define SPI_START_SEC_CODE_ASIL_D_GLOBAL 
/* #Violation: Spi_c_REF_7 */ 
#include "Spi_MemMap.h" 

#if (SPI_DEV_ERROR_DETECT == STD_ON)
static FUNC(Std_ReturnType, SPI_PRIVATE_CODE) Spi_GetCommonDetStatus
(
    Mcal_CoreType       CoreId,
    uint8               ServiceId
);
static FUNC(Std_ReturnType, SPI_PRIVATE_CODE) Spi_GetSeqDetStatus
(
    Mcal_CoreType       CoreId,
    uint8               ServiceId,
    Spi_SequenceType    Sequence
);
static FUNC(Std_ReturnType, SPI_PRIVATE_CODE) Spi_GetJobDetStatus
(
    Mcal_CoreType   CoreId,
    uint8           ServiceId,
    Spi_JobType     Job
);
static FUNC(Std_ReturnType, SPI_PRIVATE_CODE) Spi_GetChannelDetStatus
(
    Mcal_CoreType   CoreId,
    uint8           ServiceId,
    Spi_ChannelType Channel
);
static FUNC(Std_ReturnType, SPI_PRIVATE_CODE) Spi_GetPhyUnitDetStatus
(
    Mcal_CoreType   CoreId,
    uint8           ServiceId,
    Spi_HWUnitType  PhyUnit
);
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */

static FUNC(Spi_StatusType, SPI_PRIVATE_CODE) Spi_GetDriverStatus
(
    Mcal_CoreType CoreId
);

#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
static FUNC(Spi_StatusType, SPI_PRIVATE_CODE) Spi_AsyncGetPhyUnitStatus
(
    Mcal_CoreType   CoreId
);
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
static FUNC(boolean, SPI_PRIVATE_CODE) Spi_SyncStartTransmit
(
    Mcal_CoreType           CoreId,
    Spi_SequenceType        Sequence
);
static FUNC(boolean, SPI_PRIVATE_CODE) Spi_SyncTransmitJob
(
    Mcal_CoreType           CoreId,
    Spi_JobType             Job
);
static FUNC(boolean, SPI_PRIVATE_CODE) Spi_SyncWaitTransFinish
(
    Mcal_CoreType           CoreId,
    Spi_HWUnitType          PhyUnit
);
static FUNC(Std_ReturnType, SPI_PRIVATE_CODE) Spi_SyncCheckPhyUnitsFree
(
    Mcal_CoreType           CoreId,
    Spi_SequenceType        Sequence
);
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
static FUNC(Std_ReturnType, SPI_PRIVATE_CODE) Spi_AsyncCheckJobLinkStatus
(
    Mcal_CoreType           CoreId,
    Spi_SequenceType        Sequence
);
static FUNC(boolean, SPI_PRIVATE_CODE) Spi_AsyncScheduleJob
(
    Mcal_CoreType           CoreId,
    Spi_JobType             Job,
    boolean                 CallNotification
);
static FUNC(boolean, SPI_PRIVATE_CODE) Spi_AsyncJobTransfer
(
    Mcal_CoreType           CoreId,
    Spi_JobType             Job
);
#if (SPI_ENABLE_DMA == STD_ON)
static FUNC(boolean, SPI_PRIVATE_CODE) Spi_AsyncJobDmaTransfer
(
    Mcal_CoreType           CoreId,
    Spi_JobType             Job
);
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */
static FUNC(void, SPI_PRIVATE_CODE) Spi_AsyncLinkJobList
(
    Mcal_CoreType           CoreId,
    Spi_JobType             Job
);
static FUNC(boolean, SPI_PRIVATE_CODE) Spi_AsyncJobTransferChannel
(
    Mcal_CoreType           CoreId,
    Spi_HWUnitType          PhyUnit,
    boolean                 NewChannel
);
static FUNC(boolean, SPI_PRIVATE_CODE) Spi_AsyncJobTransferFinished
(
    Mcal_CoreType           CoreId,
    Spi_JobType             Job
);
static FUNC(boolean, SPI_PRIVATE_CODE) Spi_AsyncStartScheduledJob
(
    Mcal_CoreType           CoreId,
    Spi_JobType             Job,
    boolean                 CheckPhyUnitIdle,
    P2VAR(Spi_JobType, AUTOMATIC, SPI_APPL_DATA) AbortedJobPtr,
    P2VAR(P2CONST(Spi_SequenceConfigType, AUTOMATIC, SPI_APPL_CONST), AUTOMATIC, SPI_APPL_DATA) AbortedSeqCfgPtrPtr,
    P2VAR(boolean, AUTOMATIC, SPI_APPL_DATA) SeqCancelledPtr
);
static FUNC(boolean, SPI_PRIVATE_CODE) Spi_AsyncScheduleNextJob
(
    Mcal_CoreType           CoreId,
    Spi_JobType             Job,
    boolean                 PhyUnitReleased
);
static FUNC(boolean, SPI_PRIVATE_CODE) Spi_AsyncIsrFifoRx
(
    Mcal_CoreType           CoreId,
    Spi_HWUnitType          PhyUnit
);

static FUNC(void, SPI_PRIVATE_CODE) Spi_AsyncUnlockRemainingJobs
(
    Mcal_CoreType           CoreId,
    Spi_SequenceType        Sequence
);

static FUNC(void, SPI_PRIVATE_CODE) Spi_AsyncReleaseSeqPhyUnits
(
    Mcal_CoreType                                               CoreId,
    P2CONST(Spi_SequenceConfigType, AUTOMATIC, SPI_APPL_CONST)  SeqCfgPtr
);

static FUNC_P2CONST(Spi_SequenceConfigType, SPI_APPL_CONST, SPI_PRIVATE_CODE) Spi_AsyncAbortJob
(
    Mcal_CoreType           CoreId,
    Spi_JobType             Job
);

static FUNC(void, SPI_PRIVATE_CODE) Spi_AsyncReportAbortedJob
(
    Mcal_CoreType           CoreId,
    Spi_JobType             Job,
    P2CONST(Spi_SequenceConfigType, AUTOMATIC, SPI_APPL_CONST) SeqCfgPtr,
    boolean                 CallNotification
);

static FUNC_P2CONST(Spi_SequenceConfigType, SPI_APPL_CONST, SPI_PRIVATE_CODE) Spi_AsyncReleaseCancelledJob
(
    Mcal_CoreType           CoreId,
    Spi_JobType             Job
);

static FUNC(void, SPI_PRIVATE_CODE) Spi_AsyncReportCancelledSeq
(
    Mcal_CoreType           CoreId,
    P2CONST(Spi_SequenceConfigType, AUTOMATIC, SPI_APPL_CONST) SeqCfgPtr
);

static FUNC(boolean, SPI_PRIVATE_CODE) Spi_AsyncAbortRunningJob
(
    Mcal_CoreType           CoreId,
    Spi_HWUnitType          PhyUnit,
    boolean                 CheckDeadline
);
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */

#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
static FUNC(uint64, SPI_PRIVATE_CODE) Spi_AsyncStampDeadline
(
    uint32                  Rounds
);

static FUNC(void, SPI_PRIVATE_CODE) Spi_AsyncSuperviseTimeout
(
    Mcal_CoreType           CoreId,
    Spi_HWUnitType          PhyUnit,
    uint64                  Deadline
);
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */

#if (SPI_CUSTOMIZED_CS_EN == STD_ON)
static FUNC(boolean, SPI_PRIVATE_CODE) Spi_WaitPhaseStatus
(
    Spi_HWUnitType          PhyUnit
);
#endif /* (SPI_CUSTOMIZED_CS_EN \== STD_ON) */

static FUNC(uint32, SPI_PRIVATE_CODE) Spi_GetDataTotalNumOfJob
(
    Mcal_CoreType           CoreId,
    Spi_JobType             Job
);

static FUNC(Std_ReturnType, SPI_PRIVATE_CODE) Spi_CheckSeqDataLength
(
    Mcal_CoreType           CoreId,
    Spi_SequenceType        Sequence
);

static FUNC(void, SPI_PRIVATE_CODE) Spi_IsrError
(
    Mcal_CoreType           CoreId,
    Spi_HWUnitType          PhyUnit
);

static FUNC(boolean, SPI_PRIVATE_CODE) Spi_InitDriver
(
    Mcal_CoreType           CoreId,
    P2CONST(Spi_ConfigType, AUTOMATIC, SPI_APPL_CONST) ConfigPtr
);

static FUNC(Std_ReturnType, SPI_PRIVATE_CODE) Spi_DeInitDriver
(
    Mcal_CoreType           CoreId
);
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
#if (SPI_DEV_ERROR_DETECT == STD_ON)
/****************************************************************************************************
*   Function Name           : Spi_GetCommonDetStatus
*
*   Service ID              : None.
*
*   Description             : DET check without input parameter and return check RetStatus.
*
*   Parameters in           : CoreId:   Current execution core ID
*                             ServiceId: API service ID
*                             ConfigPtr: configuration parameter pointer ,If there is no
*                                        configuration parameter, it is marked with NULL_PTR
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK: No DET error
*                             E_NOT_OK: DET error.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, SPI_PRIVATE_CODE) Spi_GetCommonDetStatus
(
    Mcal_CoreType       CoreId,
    uint8               ServiceId
)
{
    Std_ReturnType                  RetStatus;

    RetStatus = E_NOT_OK;
    /* Not Spi driver status information storage variable in current core */
    if(NULL_PTR == Spi_CoreStatus[CoreId])
    {
        (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                SPI_E_CORE_NOT_STATUS_STORAGEVAR);
    }
    /*  SWS_Spi_00046:
        If development error detection for the SPI module is enabled and the SPI Handler/Driver's
        environment calls any API function before initialization, an error should be reported to
        the DET with the error value SPI_E_UNINIT according to the configuration.
        SWS_Spi_00242:
        API service used without module initialization
    */
    else if(SPI_UNINITIALIZE == *(Spi_CoreStatus[CoreId]->CoreInitStatusPtr))
    {
        (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                SPI_E_UNINIT);
    }
    /* Not Spi configured in current core */
    else if(NULL_PTR == (Spi_ConfigPtr->CoreConfigPtr[CoreId]))
    {
        (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID,ServiceId,
                                SPI_E_CORE_NOT_CONFIGURED);
    }
    else
    {
        RetStatus = E_OK;
    }

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Spi_GetSeqDetStatus
*
*   Service ID              : None.
*
*   Description             : DET check with input parameter Sequence and return check RetStatus.
*
*   Parameters in           : CoreId:   Current execution core ID
*                             Sequence: Sequence number for DET check
*                             ServiceId: API service ID
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK: No DET error
*                             E_NOT_OK: DET error.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, SPI_PRIVATE_CODE) Spi_GetSeqDetStatus
(
    Mcal_CoreType       CoreId,
    uint8               ServiceId,
    Spi_SequenceType    Sequence
)
{
    Std_ReturnType                  RetStatus;
    Spi_SequenceType                CorexSeqIdx;
    const Spi_CoreConfigType        *CurrentCoreConfigPtr;

    RetStatus = E_NOT_OK;
    /* Not Spi driver status information storage variable in current core */
    if(NULL_PTR == Spi_CoreStatus[CoreId])
    {
        (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                SPI_E_CORE_NOT_STATUS_STORAGEVAR);
    }
    /*  SWS_Spi_00046:
        If development error detection for the SPI module is enabled and the SPI Handler/Driver's
        environment calls any API function before initialization, an error should be reported to
        the DET with the error value SPI_E_UNINIT according to the configuration.
        SWS_Spi_00242:
        API service used without module initialization
    */
    else if(SPI_UNINITIALIZE == *(Spi_CoreStatus[CoreId]->CoreInitStatusPtr))
    {
        (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                SPI_E_UNINIT);
    }
    else
    {
        /* Get Corex configuration information structure pointer */
        CurrentCoreConfigPtr = Spi_ConfigPtr->CoreConfigPtr[CoreId];
        /* Not Spi configured in current core */
        if (NULL_PTR == CurrentCoreConfigPtr)
        {
            (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                    SPI_E_CORE_NOT_CONFIGURED);
        }
        /*  SWS_Spi_00238:
            API service called with wrong Sequence parameter
            SWS_Spi_00032:
            The API parameters Sequence and Job shall have values within the specified range of values. Related errors values: SPI_E_PARAM_SEQ or SPI_E_PARAM_JOB.
        */
        else if (Sequence >= Spi_ConfigPtr->MaxSequence)
        {
            (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                SPI_E_PARAM_SEQ);
        }
        else
        {
            /* Get the Sequence index in current executing core */
            CorexSeqIdx = Spi_ConfigPtr->SequenceToCorePtr[Sequence];
            /*  SWS_Spi_00238:
                API service called with wrong Sequence parameter
                SWS_Spi_00032:
                The API parameters Sequence and Job shall have values within the specified range of values. Related errors values: SPI_E_PARAM_SEQ or SPI_E_PARAM_JOB.
            */
            if(CorexSeqIdx >= (CurrentCoreConfigPtr->MaxSeq))
            {
                (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                        SPI_E_PARAM_SEQ);
            }
            /* The Sequence ID of the query does not match the one passed in */
            else if(Sequence != CurrentCoreConfigPtr->SeqCfgPtr[CorexSeqIdx].SequenceId)
            {
                (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                        SPI_E_CORE_SEQUENCE_MISMATCH);
            }
            /* No Job is allocated in the current Sequence */
            else if (0U == CurrentCoreConfigPtr->SeqCfgPtr[CorexSeqIdx].NumJobs)
            {
                (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                        SPI_E_SEQ_EMPTY);
            }
            else
            {
                RetStatus = E_OK;
            }
        }
    }

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Spi_GetJobDetStatus
*
*   Service ID              : None.
*
*   Description             : DET check with input parameter Job and return check RetStatus.
*
*   Parameters in           : CoreId:   Current execution core ID
*                             Job:      Job number for DET check
*                             ServiceId: API service ID
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK: No DET error
*                             E_NOT_OK: DET error.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, SPI_PRIVATE_CODE) Spi_GetJobDetStatus
(
    Mcal_CoreType   CoreId,
    uint8           ServiceId,
    Spi_JobType     Job
)
{
    Std_ReturnType                  RetStatus;
    Spi_JobType                     JobIndex;
    const Spi_CoreConfigType        *CurrentCoreConfigPtr;

    RetStatus = E_NOT_OK;
    /* Not Spi driver status information storage variable in current core */
    if(NULL_PTR == Spi_CoreStatus[CoreId])
    {
        (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                SPI_E_CORE_NOT_STATUS_STORAGEVAR);
    }
    /*  SWS_Spi_00046:
        If development error detection for the SPI module is enabled and the SPI Handler/Driver's
        environment calls any API function before initialization, an error should be reported to
        the DET with the error value SPI_E_UNINIT according to the configuration.
        SWS_Spi_00242:
        API service used without module initialization
    */
    else if(SPI_UNINITIALIZE == *(Spi_CoreStatus[CoreId]->CoreInitStatusPtr))
    {
        (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                SPI_E_UNINIT);
    }
    else
    {
        /* Get Corex configuration information structure pointer */
        CurrentCoreConfigPtr = Spi_ConfigPtr->CoreConfigPtr[CoreId];
        /* Not Spi configured in current core */
        if (NULL_PTR == CurrentCoreConfigPtr)
        {
            (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                    SPI_E_CORE_NOT_CONFIGURED);
        }
        /*  SWS_Spi_00237:
            API service called with wrong Job parameter
            SWS_Spi_00032:
            The API parameters Sequence and Job shall have values within the specified range of values. Related errors values: SPI_E_PARAM_SEQ or SPI_E_PARAM_JOB.
        */
        else if (Job >= Spi_ConfigPtr->MaxJob)
        {
            (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                SPI_E_PARAM_JOB);
        }
        else
        {
            /* Get the Channel index in current executing core */
            JobIndex = Spi_ConfigPtr->JobToCorePtr[Job];
            /*  SWS_Spi_00237:
                API service called with wrong Job parameter
                SWS_Spi_00032:
                The API parameters Sequence and Job shall have values within the specified range of values. Related errors values: SPI_E_PARAM_SEQ or SPI_E_PARAM_JOB.
            */
            /* The queried Job ID does not match the one passed in */
            if(JobIndex >= (CurrentCoreConfigPtr->MaxJob))
            {
                (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                        SPI_E_PARAM_JOB);
            }
            /* The channel index of executing core is out of range */
            else if(Job != CurrentCoreConfigPtr->JobCfgPtr[JobIndex].JobId)
            {
                (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                        SPI_E_CORE_JOB_MISMATCH);
            }
            /* No Job is allocated in the current Sequence */
            else if (0U == CurrentCoreConfigPtr->JobCfgPtr[JobIndex].NumChannels)
            {
                (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                        SPI_E_JOB_EMPTY);
            }
            else
            {
                RetStatus = E_OK;
            }
        }
    }

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Spi_GetChannelDetStatus
*
*   Service ID              : None.
*
*   Description             : DET check with input parameter Channel and return check RetStatus.
*
*   Parameters in           : CoreId:   Current execution core ID
*                             Channel:  Channel number for DET check
*                             ServiceId: API service ID
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK: No DET error
*                             E_NOT_OK: DET error.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, SPI_PRIVATE_CODE) Spi_GetChannelDetStatus
(
    Mcal_CoreType   CoreId,
    uint8           ServiceId,
    Spi_ChannelType Channel
)
{
    Spi_ChannelType                 CoreChIdx;
    Std_ReturnType                  RetStatus;
    const Spi_CoreConfigType        *CurrentCoreConfigPtr;

    RetStatus = E_NOT_OK;
    /* Not Spi driver status information storage variable in current core */
    if(NULL_PTR == Spi_CoreStatus[CoreId])
    {
        (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                SPI_E_CORE_NOT_STATUS_STORAGEVAR);
    }
    /*  SWS_Spi_00046:
        If development error detection for the SPI module is enabled and the SPI Handler/Driver's
        environment calls any API function before initialization, an error should be reported to
        the DET with the error value SPI_E_UNINIT according to the configuration.
        SWS_Spi_00242:
        API service used without module initialization
    */
    else if(SPI_UNINITIALIZE == *(Spi_CoreStatus[CoreId]->CoreInitStatusPtr))
    {
        (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                SPI_E_UNINIT);
    }
    else
    {
        /* Get Corex configuration information structure pointer */
        CurrentCoreConfigPtr = Spi_ConfigPtr->CoreConfigPtr[CoreId];
        /* Not Spi configured in current core */
        if(NULL_PTR == CurrentCoreConfigPtr)
        {
            (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                    SPI_E_CORE_NOT_CONFIGURED);
        }
        /* SWS_Spi_00004: API service called with wrong Channel parameter */
        else if(Channel >= Spi_ConfigPtr->MaxChannel)
        {
            (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                SPI_E_PARAM_CHANNEL);
        }
        else
        {
            /* Get the index of Channel in Corex */
            CoreChIdx = Spi_ConfigPtr->ChannelToCorePtr[Channel];
            /* SWS_Spi_00004: API service called with wrong Channel parameter */
            if(CoreChIdx >= (CurrentCoreConfigPtr->MaxChannel))
            {
            (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                    SPI_E_PARAM_CHANNEL);
            }
            /* The channel index of executing core is out of range */
            else if(Channel != CurrentCoreConfigPtr->ChannelCfgPtr[CoreChIdx].LogicChId)
            {
                (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                        SPI_E_CORE_CHANNEL_MISMATCH);
            }
            else
            {
                RetStatus = E_OK;
            }
        }
    }

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Spi_GetPhyUnitDetStatus
*
*   Service ID              : None.
*
*   Description             : DET check with input parameter PhyUnit and return check RetStatus.
*
*   Parameters in           : CoreId:   Current execution core ID
*                             PhyUnit:   PhyUnit number for DET check
*                             ServiceId: API service ID
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK: No DET error
*                             E_NOT_OK: DET error.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, SPI_PRIVATE_CODE) Spi_GetPhyUnitDetStatus
(
    Mcal_CoreType   CoreId,
    uint8           ServiceId,
    Spi_HWUnitType  PhyUnit
)
{
    Std_ReturnType                  RetStatus;
    Spi_HWUnitType                  CorePhyUnitIdx;
    const Spi_CoreConfigType        *CurrentCoreConfigPtr;

    RetStatus = E_NOT_OK;
    /* Not Spi driver status information storage variable in current core */
    if(NULL_PTR == Spi_CoreStatus[CoreId])
    {
        (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                SPI_E_CORE_NOT_STATUS_STORAGEVAR);
    }
    /*  SWS_Spi_00046:
        If development error detection for the SPI module is enabled and the SPI Handler/Driver's
        environment calls any API function before initialization, an error should be reported to
        the DET with the error value SPI_E_UNINIT according to the configuration.
        SWS_Spi_00242:
        API service used without module initialization
    */
    else if(SPI_UNINITIALIZE == *(Spi_CoreStatus[CoreId]->CoreInitStatusPtr))
    {
        (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                SPI_E_UNINIT);
    }
    else
    {
        /* Get Corex configuration information structure pointer */
        CurrentCoreConfigPtr = Spi_ConfigPtr->CoreConfigPtr[CoreId];
        /* Not Spi configured in current core */
        if (NULL_PTR == CurrentCoreConfigPtr)
        {
            (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                    SPI_E_CORE_NOT_CONFIGURED);
        }
        /*  SWS_Spi_00143:
            The API parameter PhyUnit shall have a value within the specified range of values.
            Related error value: SPI_E_PARAM_UNIT.
            SWS_Spi_00241:
             API service called with wrong SPI PhyUnit parameter.
        */
        else if (PhyUnit >= Spi_ConfigPtr->MaxPhyUnit)
        {
            (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                SPI_E_PARAM_UNIT);
        }
        else
        {
            /* Get the Channel index in current executing core */
            CorePhyUnitIdx = Spi_ConfigPtr->PhyUnitToCorePtr[PhyUnit];
            /*  SWS_Spi_00143:
                The API parameter PhyUnit shall have a value within the specified range of values.
                Related error value: SPI_E_PARAM_UNIT.
                SWS_Spi_00241:
                API service called with wrong SPI PhyUnit parameter.
            */
            if(CorePhyUnitIdx >= (CurrentCoreConfigPtr->MaxPhyUnit))
            {
            (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                    SPI_E_PARAM_UNIT);
            }
            /* The channel index of executing core is out of range */
            else if(PhyUnit != CurrentCoreConfigPtr->PhyUnitCfgPtr[CorePhyUnitIdx].SpiNumber)
            {
                (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ServiceId,
                                        SPI_E_CORE_HWUNIT_MISMATCH);
            }
            else
            {
                RetStatus = E_OK;
            }
        }
    }

    return RetStatus;
}
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */

/****************************************************************************************************
*   Function Name           : Spi_GetDriverStatus
*
*   Service ID              : None
*
*   Description             : Service returns the SPI Handler/Driver software module RetStatus.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : SPI_UNINIT: Spi is uninitialized
*                             SPI_IDLE: Spi is idle
*                             SPI_BUSY: Spi is busy
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Spi_StatusType, SPI_PRIVATE_CODE) Spi_GetDriverStatus
(
    Mcal_CoreType CoreId
)
{
    Spi_StatusType                  SpiStatus;
    Spi_HWUnitType                  PhyUnitIndex;
    /*  SWS_Spi_00346:
        API service Spi_GetStatus shall return SPI_IDLE when The SPI Handler/Driver is not
        currently transmitting any Job.
        SWS_Spi_00347:
        API service Spi_GetStatus shall return SPI_BUSY when The SPI Handler/Driver is
        performing a SPI Job transmit.
    */
    SpiStatus = SPI_IDLE;
    /* A PhyUnit stays reserved in PhyUnitPendingTeardownStatusPtr for the whole duration
       of any Sequence (synchronous or asynchronous) that uses it, including the gaps
       where PhyUnitStatus alone would look IDLE: between two Jobs of an ongoing
       synchronous Sequence, and between a Sequence being declared and its teardown
       (incl. end notification) actually completing. Report BUSY while any such
       reservation is held, so DeInit/GetStatus are never fooled by those gaps. */
    if (0U != *(Spi_CoreStatus[CoreId]->PhyUnitPendingTeardownStatusPtr))
    {
        SpiStatus = SPI_BUSY;
    }
    /* Check if there is any hardware that is not IDLE */
    for(PhyUnitIndex = 0U; ((PhyUnitIndex < Spi_ConfigPtr->CoreConfigPtr[CoreId]->MaxPhyUnit) &&
        (SPI_IDLE == SpiStatus)); PhyUnitIndex++)
    {
        /* Update driver status via hardware status */
        SpiStatus = Spi_CoreStatus[CoreId]->PhyUnitStatusPtr[PhyUnitIndex].PhyUnitStatus;
    }

    return SpiStatus;
}

#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
/****************************************************************************************************
*   Function Name           : Spi_AsyncGetPhyUnitStatus
*
*   Service ID              : None.
*
*   Description             : This function shall returns the status of the SPI driver related to
*                             async HW Units.
*
*   Parameters in           : CoreId:   Current execution core ID
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non-Reentrant(Same HwUnit).
*
*   Return value            : SPI_UNINIT: Spi is uninitialized
*                             SPI_IDLE: Spi is idle
*                             SPI_BUSY: Spi is busy
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL2.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Spi_StatusType, SPI_PRIVATE_CODE) Spi_AsyncGetPhyUnitStatus
(
    Mcal_CoreType   CoreId
)
{
    boolean                 FindBusyAsyncHW;
    Spi_StatusType          SpiStatus;
    Spi_HWUnitType          PhyUnitIndex;

    /* Reset SPI PhyUnit status to 'SPI_IDLE' */
    SpiStatus = SPI_IDLE;
    /* Reset polling index value to '0' */
    PhyUnitIndex = 0U;
    /* The reset flag PhyUnit is occupied by an asynchronous sequence */
    FindBusyAsyncHW = FALSE;
    /* Check if PhyUnit exists for asynchronous communication */
    while((FALSE == FindBusyAsyncHW) &&
          (PhyUnitIndex < Spi_ConfigPtr->CoreConfigPtr[CoreId]->MaxPhyUnit))
    {
        if ((SPI_BUSY == Spi_CoreStatus[CoreId]->PhyUnitStatusPtr[PhyUnitIndex].PhyUnitStatus) &&
            (TRUE == Spi_CoreStatus[CoreId]->PhyUnitStatusPtr[PhyUnitIndex].IsAsync))
        {
            SpiStatus = SPI_BUSY;
            FindBusyAsyncHW = TRUE;
        }
        else
        {
            PhyUnitIndex++;
        }
    }

    return SpiStatus;
}
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
/****************************************************************************************************
*   Function Name           : Spi_SyncStartTransmit
*
*   Service ID              : None
*
*   Description             : This function performs the synchronous transmission for a sequence.
*
*   Parameters in           : CoreId    : Execution Core ID Number.
*                             Sequence  : Sequence ID Number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK: Sequence sending completed.
*                             E_NOT_OK: Sequence sending failed.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL0 or SPI_LEVEL2
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, SPI_PRIVATE_CODE) Spi_SyncStartTransmit
(
    Mcal_CoreType           CoreId,
    Spi_SequenceType        Sequence
)
{
    boolean                         RetStatus;
    Spi_JobType                     JobNumberInSeq;
    const Spi_JobConfigType         *JobCfgPtr;
    const Spi_JobType               *JobIndexPtr;
    const Spi_SequenceConfigType    *SeqCfgPtr;

    RetStatus = TRUE;
    /* Get Sequence configuration information structure pointer */
    /* #Violation: Spi_c_REF_1 */ 
    SeqCfgPtr = SPI_SEQ_CONFIGPTR(CoreId, Sequence); 
    /* Get the number of jobs in the sequence */
    JobNumberInSeq = SeqCfgPtr->NumJobs;
    /* Get Job index in current Sequence */
    JobIndexPtr = SeqCfgPtr->JobIndexListPtr;
    while (0U < JobNumberInSeq)
    {
        /*  SWS_Spi_00134:
            When the function Spi_SyncTransmit is called, shall take over the given parameter
            and set the SPI Handler/Driver status to SPI_BUSY can be obtained calling the API
            service SPI_GetStatus.
        */
        /* Get Job configuration information structure pointer */
        /* #Violation: Spi_c_REF_1 */ 
        JobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, *JobIndexPtr); 
        /* Entering synchronous transmission critical protection */
        SPI_ENTER_CRITICAL_SECTION(SyncTransmit);
        /*  SWS_Spi_00157:
            When the function Spi_AsyncTransmit is called, the SPI Handler/Driver shall handle the
            Job results. Result shall be SPI_JOB_PENDING when the transmission of Jobs is started.
            SWS_Spi_00286:
            When the function Spi_SyncTransmit is called, shall take over the given parameter
            and set the Job status to SPI_JOB_PENDING can be obtained calling the API service
            Spi_GetJobResult.
        */
        /* Get Job status information, the input parameter is the Job ID */
        /* #Violation: Spi_c_REF_1 */ 
        SPI_JOB_STATUS(CoreId, *JobIndexPtr) = SPI_JOB_PENDING; 
        /* Get PhyUnit status information, the input parameter is the PhyUnit ID */
        /* #Violation: Spi_c_REF_1 */ 
        SPI_HWUNIT_STATUS(CoreId, JobCfgPtr->SpiNumber) = SPI_BUSY; 
        /* Exit synchronous transmission critical protection */
        SPI_EXIT_CRITICAL_SECTION(SyncTransmit);
        /* Initialize external device status pointer => Current Job configuration information */
        /* #Violation: Spi_c_REF_1 */ 
        SPI_CURJOB_CONFIGPTR(CoreId, JobCfgPtr->SpiNumber) = JobCfgPtr; 
        /* Synchronous transmission for a Job */
        RetStatus &= Spi_SyncTransmitJob(CoreId, JobCfgPtr->JobId);
        /* Entering synchronous transmission critical protection */
        SPI_ENTER_CRITICAL_SECTION(SyncTransmit);
        /* Get PhyUnit status information, the input parameter is the PhyUnit ID */
        /* #Violation: Spi_c_REF_1 */ 
        SPI_HWUNIT_STATUS(CoreId, JobCfgPtr->SpiNumber) = SPI_IDLE; 
        if (TRUE == RetStatus)
        {
            /*Total number of jobs decrement in currnet Sequence */
            JobNumberInSeq--;
            /*
            The following processing must be performed first: Prevent users from obtaining the job
            status and sending the sequence in the Notification
            */
            /* Get Job status information, the input parameter is the Job ID */
            /* #Violation: Spi_c_REF_1 */ 
            SPI_JOB_STATUS(CoreId, *JobIndexPtr) = SPI_JOB_OK; 
            JobIndexPtr++;
            /* Exit synchronous transmission critical protection */
            SPI_EXIT_CRITICAL_SECTION(SyncTransmit);
            /*  SWS_Spi_00270:
                In case call end notification function and rescheduling are fully done by software,
                the order between these shall be first scheduling and then the call of end notification
                function executed.
                SWS_Spi_00071:
                If the SpiJobEndNotification is configured (i.e. not a null pointer), the SPI
                Handler/Driver shall call the configured callback notification at the end of a Job
                transmission. Note: This routine might be called on interrupt level, depending on the
                calling function.
            */
            /* Perform job EndNotification (if there is one) */
            if (NULL_PTR != JobCfgPtr->JobEndNotificationPtr)
            {
                JobCfgPtr->JobEndNotificationPtr();
            }
#if (SPI_DEM_REPORT_ERROR_STATUS == STD_ON)
            /*  SWS_Spi_00384:
                When a hardware error is detected, the SPI Handler/Driver shall stop the current
                sequence, report an error to the DEM as configured and set the state of the Job to
                SPI_JOB_FAILED and the state of the Sequence to SPI_SEQ_FAILED.
                SWS_Spi_00386:
                When no error bit inside the SPI transmit status register is set, the SPI transmit
                status register information shall be reported to DEM as Dem_SetEventStatus
                (SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_PASSED)
            */
            /* Report DEM error - hardware error occurred */
            Dem_SetEventStatus(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_PASSED);
#endif /* (SPI_DEM_REPORT_ERROR_STATUS  \== STD_ON) */
        }
        else
        {
            /* Set the remaining job status as FAILED */
            while (0U < JobNumberInSeq)
            {
                /*Total number of jobs decrement in currnet Sequence */
                JobNumberInSeq--;
                /*  SWS_Spi_00254:
                    If the Sequence and Job related service is not done and, depending on services,
                    either the return value shall be E_NOT_OK or a failed result (SPI_JOB_FAILED or
                    SPI_SEQ_FAILED).
                */
                /* Get Job status information, the input parameter is the Job ID */
                /* #Violation: Spi_c_REF_1 */ 
                SPI_JOB_STATUS(CoreId, *JobIndexPtr) = SPI_JOB_FAILED; 
                if(0U < JobNumberInSeq)
                {
                    /* iterate to next job in sequence */
                    JobIndexPtr++;
                }
            }
            /* Exit synchronous transmission critical protection */
            SPI_EXIT_CRITICAL_SECTION(SyncTransmit);
#if (SPI_DEM_REPORT_ERROR_STATUS == STD_ON)
            /*  SWS_Spi_00384:
                When a hardware error is detected, the SPI Handler/Driver shall stop the current
                sequence, report an error to the DEM as configured and set the state of the Job to
                SPI_JOB_FAILED and the state of the Sequence to SPI_SEQ_FAILED.
                SWS_Spi_00385:
                When any error bit inside the SPI transmit status register is set, the SPI transmit
                status register information shall be reported to DEM as Dem_SetEventStatus
                (SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED)
            */
            /* Report DEM error - hardware error occurred */
            Dem_SetEventStatus(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif /* (SPI_DEM_REPORT_ERROR_STATUS  \== STD_ON) */
        }
    }

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Spi_SyncTransmitJob
*
*   Service ID              : None.
*
*   Description             : Sets up the SPI HW According to Job Parameters. After any failure the
*                             HW unit is reset, so that no data of the failed Job is left in the FIFOs
*                             for the next transmission.
*
*   Parameters in           : CoreId    : Execution Core ID Number.
*                             Job       : Job ID Number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK: Job sending completed.
*                             E_NOT_OK Job sending failed.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL0 or SPI_LEVEL2.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, SPI_PRIVATE_CODE) Spi_SyncTransmitJob
(
    Mcal_CoreType           CoreId,
    Spi_JobType             Job
)
{
    uint8                                       Level;
    uint8                                       Threshold;
    uint32                                      DataTotalNum;
    uint32                                      TxBufferIndex;
    uint32                                      RxBufferIndex;
    uint32                                      ChDynamicCfg;
    uint32                                      TempRxBuffer;
    boolean                                     RetStatus;
    Spi_ChannelType                             ChNumberInJob;
    Spi_NumberOfDataType                        FramesCount;
    ESPI_MODULE                                 *PhyUnit;
    const Spi_ChannelType                       *ChannelIndexPtr;
    const Spi_ChannelConfigType                 *ChannelCfgPtr;
    const Spi_ExternalDeviceConfigType          *ExDeviceCfgPtr;
    Spi_ChannelDynamicConfigType                ChDynamicConfig;
    const Spi_JobConfigType                     *JobCfgPtr;

    /* Get Job configuration information structure pointer */
    /* #Violation: Spi_c_REF_1 */ 
    JobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, Job); 
    /* Get the number of Channel in the Job */
    ChNumberInJob = JobCfgPtr->NumChannels;
    /* Get Channel index in current Job */
    ChannelIndexPtr = JobCfgPtr->ChannelIndexListPtr;
    /* Get hardware unit address */
    PhyUnit = Spi_ConfigPtr->PhyUnitMapPtr[JobCfgPtr->SpiNumber];
    /* Get the total amount of all channel data in the job */
    DataTotalNum = Spi_GetDataTotalNumOfJob(CoreId, JobCfgPtr->JobId);
    /* The Move Counter data length register can only hold ESPI_MOVE_STEP_MASK frames */
    if (DataTotalNum > (uint32)ESPI_MOVE_STEP_MASK)
    {
        RetStatus = FALSE;
    }
    else
    {
        /* Configure the total amount of data to be transferred in Move Counter mode */
        RetStatus = Espi_Hal_SetMoveCounterDataLength(PhyUnit, (uint16)DataTotalNum);
    }
    /* Get external device configuration information structure pointer */
    /* #Violation: Spi_c_REF_1 */ 
    ExDeviceCfgPtr = SPI_EXD_CONFIGPTR(CoreId, JobCfgPtr->ExDeviceUnit); 
    /* Configure data transmission parity check mode */
    ChDynamicConfig.parityMode = ExDeviceCfgPtr->ParitySelection;
    /* Configure data transmission delay parameters */
    ChDynamicConfig.delayTime = ExDeviceCfgPtr->DelayParam;
    /* Configure move counter mode */
    ChDynamicConfig.dataMode = ESPI_MASTER_MODE_MOVECOUNTER;
    /* Configure output transmission bit order  */
    ChDynamicConfig.bitOrder = ESPI_BITORDER_LSB;
    /* Configure output transmission data width  */
    ChDynamicConfig.dataWidth = ESPI_DATAWIDTH_8;
    /* Calculate channel configuration register value */
    ChDynamicCfg = Espi_Hal_CalculateChannelDynamicConfiguration(ExDeviceCfgPtr->
                    Spi_ExDeviceCfgInfoPtr->csChannel, &ChDynamicConfig);
    /* Disable SPI DMA transfer function */
    RetStatus &= Espi_Hal_SetDma(PhyUnit, FALSE);
#if (SPI_CUSTOMIZED_CS_EN == STD_ON)
    /* Check whether the peripherals used by the current job use GPIO for chip selection */
    if ((SPI_CS_VIA_GPIO == ExDeviceCfgPtr->CsSelection) && (FALSE == JobCfgPtr->PullCSbyData))
    {
        /* Flip the CS signal to prepare for the SLSO transition edge before SPI communication. */
        (void)Dio_FlipChannel(ExDeviceCfgPtr->GpioPortPin);
    }
#endif /* (SPI_CUSTOMIZED_CS_EN \== STD_ON) */
    /* One cyclic transmission of one channel */
    while((0U < ChNumberInJob) && (TRUE == RetStatus))
    {
        ChNumberInJob--;
        /* Get Channel configuration information structure pointer */
        /* #Violation: Spi_c_REF_1 */ 
        ChannelCfgPtr = SPI_CH_CONFIGPTR(CoreId, *ChannelIndexPtr);  
        ChannelIndexPtr++;
        /* Get the actual data length of frames to be sent */
        FramesCount = *(ChannelCfgPtr->ActualDataLengthPtr);
        /* Clear the DL + MSB bit bit in the EMCON register */
        ChDynamicCfg &= SPI_CH_CONFIG_CLR;
        /* Configure the data width bit in the EMCON register */
        ChDynamicCfg |= ((uint32)ChannelCfgPtr->DataFrameWidth) << SPI_DATAWIDTH_MASK;
        /* Configure the shift sequence bits in the EMCON register */
        ChDynamicCfg |= ((uint32)ChannelCfgPtr->TransferStart) << SPI_SHIFTORDER_MASK;
        /* Write the EMCON register and configure the Last bit */
        Espi_Hal_WriteConfiguration(PhyUnit, ChDynamicCfg, JobCfgPtr->PullCSbyData);
        /* Reset Buffer index */
        TxBufferIndex = 0U;
        RxBufferIndex = 0U;
        /* One cyclic transmission of one channel data */
        while((0U < FramesCount) && (TRUE == RetStatus))
        {
            /* Calculate FIFO threshold based on data volume */
            if(SPI_AVAILABLE_FIFOLEVEL < FramesCount)
            {
                Threshold = SPI_AVAILABLE_FIFOLEVEL;
            }
            else
            {
                Threshold = (uint8)FramesCount;
            }
            /* Update the current total amount of data sent */
            Level = Threshold;
            /* Update the length of remaining data to be sent */
            FramesCount -= (uint16)Threshold;
            /* Enter synchronous transmission critical protection */
            SPI_ENTER_CRITICAL_SECTION(SyncTransmit);
            /* Configure FIFO threshold in Move Counter mode */
            RetStatus &= Espi_Hal_SetFifoLevel(PhyUnit, (uint8)ESPI_TXFIFO_THRESHOLD_ONE, Threshold);
            /* One cyclic transmission of one 'Threshold' data */
            while ((0U < Threshold) && (TRUE == RetStatus))
            {
#if (SPI_CUSTOMIZED_CS_EN == STD_ON)
                /* Select chip select before data transmission */
                if ((SPI_CS_VIA_GPIO == ExDeviceCfgPtr->CsSelection) &&
                    (TRUE == JobCfgPtr->PullCSbyData))
                {
                    (void)Dio_FlipChannel(ExDeviceCfgPtr->GpioPortPin);
                }
#endif /* (SPI_CUSTOMIZED_CS_EN \== STD_ON) */
                /*  SWS_Spi_00437:
                    Data buffers are accessed as uint8, uint16 or uint32 according to SpiDataWidth
                    independently to Spi_DataBufferType.
                    SWS_Spi_00023:
                    If the given parameter "DataBufferPtr" is null, the function Spi_WriteIB shall
                    assume that the data to be transmitted is not relevant and the default transmit
                    value of the given channel shall be used instead.
                */
                /* Write transfer data to TXFIFO */
                if(NULL_PTR == ChannelCfgPtr->BufferDescriptorPtr->TXBuffPtr)
                {
                    (void)Espi_Hal_SendData(PhyUnit,
                            ((const uint8 *)&(ChannelCfgPtr->BufferDescriptorPtr->ChDefaultData)),
                            ChannelCfgPtr->FrameWidth); 
                }
                else
                {
                    TxBufferIndex += Espi_Hal_SendData(PhyUnit, &(ChannelCfgPtr->
                        BufferDescriptorPtr->TXBuffPtr[TxBufferIndex]), ChannelCfgPtr->FrameWidth);
                }
#if (SPI_CUSTOMIZED_CS_EN == STD_ON)
                /* The chip select is released after the data transfer is completed. */
                if ((SPI_CS_VIA_GPIO == ExDeviceCfgPtr->CsSelection) &&
                    (TRUE == JobCfgPtr->PullCSbyData))
                {
                    /* #Violation: Spi_c_REF_12 */
                    RetStatus &= Spi_WaitPhaseStatus(JobCfgPtr->SpiNumber);
                    (void)Dio_FlipChannel(ExDeviceCfgPtr->GpioPortPin);
                }
#endif /* (SPI_CUSTOMIZED_CS_EN \== STD_ON) */
                Threshold--;
            }
            /* Exit synchronous transmission critical protection */
            SPI_EXIT_CRITICAL_SECTION(SyncTransmit);
            if(TRUE == RetStatus)
            {
                /* Wait for receive flag to be set */
                /* #Violation: Spi_c_REF_12 */
                RetStatus &= Spi_SyncWaitTransFinish(CoreId, JobCfgPtr->SpiNumber);
                /* Enter synchronous transmission critical protection */
                SPI_ENTER_CRITICAL_SECTION(SyncTransmit);
                /*  SWS_Spi_00028:
                    When the function Spi_SetupEB is called with the parameter DesDataBufferPtr being
                    a Null pointer, the SPI Handler/Driver shall ignore the received data after a
                    Transmit method is requested.(See also [SWS_Spi_00036])
                */
                while ((0U < Level) && (TRUE == RetStatus))
                {
                    /*  SWS_Spi_00437:
                        Data buffers are accessed as uint8, uint16 or uint32 according to SpiDataWidth
                        independently to Spi_DataBufferType.
                    */
                    /* Receive data */
                    if((NULL_PTR == ChannelCfgPtr->BufferDescriptorPtr->RXBuffPtr))
                    {
                        (void)Espi_Hal_ReceiveData(
                                PhyUnit, (uint8 *)&TempRxBuffer, ChannelCfgPtr->FrameWidth);
                    }
                    else
                    {
                        RxBufferIndex += Espi_Hal_ReceiveData(PhyUnit,
                            &(ChannelCfgPtr->BufferDescriptorPtr->RXBuffPtr[RxBufferIndex]),
                            ChannelCfgPtr->FrameWidth);
                    }
                    Level--;
                }
                /* Exit synchronous transmission critical protection */
                SPI_EXIT_CRITICAL_SECTION(SyncTransmit);
            }
            /* Clear event status flags */
            Espi_Hal_ClearFlagStatus(PhyUnit, ESPI_ALL_FLAGS_RW_STATES);
        }
    }
    if (FALSE == RetStatus)
    {
        /*  Reset the PhyUnit after any failure (receive timeout, hardware error, phase timeout or
            register read back error): frames of the failed Job left in the TX or RX FIFO shall neither
            be transmitted later nor be read by the next transmission on this PhyUnit.
        */
        Espi_Hal_ClearFlagStatus(PhyUnit, (ESPI_ALL_FLAGS_RW_STATES | ESPI_SRSTB_SET));
    }
#if (SPI_CUSTOMIZED_CS_EN == STD_ON)
    /* Job transfer ends and releases chip select */
    if ((SPI_CS_VIA_GPIO == ExDeviceCfgPtr->CsSelection) && (FALSE == JobCfgPtr->PullCSbyData))
    {
        (void)Dio_FlipChannel(ExDeviceCfgPtr->GpioPortPin);
    }
#endif /* (SPI_CUSTOMIZED_CS_EN \== STD_ON) */

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Spi_SyncWaitTransFinish
*
*   Service ID              : None.
*
*   Description             : Waiting for data transmission complete flag.
*
*   Parameters in           : CoreId    : Execution Core ID Number.
*                             PhyUnit    : Hardware ID Number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK: data transfer completed.
*                             E_NOT_OK: data transfer failed.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, SPI_PRIVATE_CODE) Spi_SyncWaitTransFinish
(
    Mcal_CoreType           CoreId,
    Spi_HWUnitType          PhyUnit
)
{
    boolean             RetStatus;
    uint32              RegValue;
    uint64              TimerFreq;
    uint64              TimeOutCount;
    uint64              CurrentCount;

    RetStatus = FALSE;
    /* Get the Stm system clock frequency */
    /* #Violation: Spi_c_REF_1 */
    TimerFreq = (uint64)Mcal_GetSystemTimerFreq();
    /* Calculate the count value required for delay *us */
    TimeOutCount = (SPI_TIMEOUT_US * TimerFreq) / 1000000ULL;
    /* Calculate the timeout count value of delay *us */
    /* #Violation: Spi_c_REF_1 */
    TimeOutCount += Mcal_GetSystemTimerCount();
    /* Wait for the receive flag to be set and no error status */
    do
    {
        /* Get receive and error flag status */
        RegValue = Espi_Hal_GetFlagStatus(
            Spi_ConfigPtr->PhyUnitMapPtr[PhyUnit], (ESPI_INTC_FLAG_RX | ESPI_INTC_ALL_ERROR_FLAGS));
        /* Get the current count value of Stm */
        /* #Violation: Spi_c_REF_1 */
        CurrentCount = Mcal_GetSystemTimerCount();
    } while ((CurrentCount < TimeOutCount) && (0U == RegValue));

    /* RXF is set and there is no hardware error */
    if (ESPI_INTC_FLAG_RX == RegValue)
    {
        RetStatus = TRUE;
    }
    else if (CurrentCount >= TimeOutCount)
    {
        /* Raise development error SPI_E_TIMEOUT_ERROR */
        (void)Det_ReportRuntimeError(
                SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_SYNCTRANSMIT, SPI_E_TIMEOUT_ERROR);
    }
    /* There is a hardware error, error checking */
    else
    {
        Spi_IsrError(CoreId, PhyUnit);
    }
    /* On timeout or hardware error the PhyUnit is reset by Spi_SyncTransmitJob before it is released */

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Spi_SyncCheckPhyUnitsFree
*
*   Service ID              : None.
*
*   Description             : This function checks whether the HW units used by a Sequence are free
*                             for a synchronous transmission: they shall neither be reserved by
*                             another synchronous Sequence nor be busy.
*
*   Parameters in           : CoreId    : Execution Core ID Number.
*                             Sequence  : Sequence ID Number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK: All HW units used by the Sequence are free.
*                             E_NOT_OK: At least one HW unit is reserved or busy.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL0 or SPI_LEVEL2.
*                             Shall be called inside of the SyncTransmit critical section, together
*                             with the reservation of the HW units.
*
*   AUTOSAR_Requirement     : SWS_Spi_00245 SWS_Spi_00135.
****************************************************************************************************/
static FUNC(Std_ReturnType, SPI_PRIVATE_CODE) Spi_SyncCheckPhyUnitsFree
(
    Mcal_CoreType           CoreId,
    Spi_SequenceType        Sequence
)
{
    Std_ReturnType                  RetStatus;
    Spi_JobType                     JobIndex;
    const Spi_JobConfigType         *JobCfgPtr;
    const Spi_SequenceConfigType    *SeqCfgPtr;

    RetStatus = E_OK;
    /* Get Sequence configuration information structure pointer */
    /* #Violation: Spi_c_REF_1 */
    SeqCfgPtr = SPI_SEQ_CONFIGPTR(CoreId, Sequence);
    /* Check if there are HW units already reserved by a synchronous Sequence */
    if (0U != (SeqCfgPtr->MaskSeqUsedPhyUnit & *(Spi_CoreStatus[CoreId]->PhyUnitBusySyncStatusPtr)))
    {
        RetStatus = E_NOT_OK;
    }
    /* Check if there are HW units reserved by any Sequence (synchronous or asynchronous)
       still being declared or torn down: this catches an asynchronous Sequence between
       Spi_AsyncTransmit marking it PENDING and its first Job's PhyUnit actually being
       marked BUSY, a gap PhyUnitBusySyncStatusPtr alone cannot see */
    if ((E_OK == RetStatus) &&
        (0U != (SeqCfgPtr->MaskSeqUsedPhyUnit &
                *(Spi_CoreStatus[CoreId]->PhyUnitPendingTeardownStatusPtr))))
    {
        RetStatus = E_NOT_OK;
    }
    for (JobIndex = 0U; (E_OK == RetStatus) && (JobIndex < SeqCfgPtr->NumJobs); JobIndex++)
    {
        /* Get Job configuration information structure pointer */
        /* #Violation: Spi_c_REF_1 */
        JobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, SeqCfgPtr->JobIndexListPtr[JobIndex]);
        /* Check whether the hardware used by the job is Busy, also for a cancelled Sequence: its
           last started Job may still be transmitted */
        /* #Violation: Spi_c_REF_1 */
        if (SPI_BUSY == SPI_HWUNIT_STATUS(CoreId, JobCfgPtr->SpiNumber))
        {
            RetStatus = E_NOT_OK;
        }
    }

    return RetStatus;
}
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
/****************************************************************************************************
*   Function Name           : Spi_AsyncCheckJobLinkStatus
*
*   Service ID              : None.
*
*   Description             : This function is called in order to mark the jobs of a sequence
*                             as ready to be transmitted.
*
*   Parameters in           : CoreId    : Execution Core ID Number.
*                             Sequence  : Sequence ID Number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non-Reentrant(Same HwUnit).
*
*   Return value            : E_OK: The job in the sequence is ready for transmission.
*                             E_NOT_OK: The job in the sequence is not ready for transmission.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, SPI_PRIVATE_CODE) Spi_AsyncCheckJobLinkStatus
(
    Mcal_CoreType           CoreId,
    Spi_SequenceType        Sequence
)
{
    Std_ReturnType                  RetStatus;
    Spi_JobType                     JobNumberInSeq;
    const Spi_JobType               *JobIndexPtr;
    const Spi_JobConfigType         *JobCfgPtr;
    const Spi_SequenceConfigType    *SeqCfgPtr;

    /* Set API return state initial value */
    RetStatus = E_OK;
    /* Get Sequence configuration information structure pointer */
    /* #Violation: Spi_c_REF_1 */ 
    SeqCfgPtr = SPI_SEQ_CONFIGPTR(CoreId, Sequence); 
    /* Get the number of jobs in current sequence */
    JobNumberInSeq = SeqCfgPtr->NumJobs;
    /* Get Job index in current Seq */
    JobIndexPtr = SeqCfgPtr->JobIndexListPtr;
    while ((E_OK == RetStatus) && (0U < JobNumberInSeq))
    {
        /* Get Job configuration information structure pointer */
        /* #Violation: Spi_c_REF_1 */ 
        JobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, *JobIndexPtr);
        if (NULL_PTR == JobCfgPtr->JobStatePtr->AsyncSeqStatePtr)
        {
            /* Job not yet linked => link it to the current sequence */
            /* #Violation: Spi_c_REF_1 */ 
            JobCfgPtr->JobStatePtr->AsyncSeqStatePtr = SPI_SEQ_STATUSPTR(CoreId, Sequence); 
            /* The number of pending jobs in the sequence is reduced by 1 */
            JobNumberInSeq--;
            /* Offset to the next pending job in the sequence */
            JobIndexPtr++;
        }
        else
        {
            /* SWS_Spi_00086:
             When the function Spi_AsyncTransmit is called and the re-quested Sequence shares Jobs
             with another sequence that is in the state SPI_SEQ_PENDING, the SPI Handler/Driver
             shall not take into account this new re-quest and this function shall return the value
             E_NOT_OK. In this case and according to [SWS_BSW_00042] and [SWS_BSW_00045], the SPI
             Handler/Driver shall report the SPI_E_SEQ_PENDING error.
             */
            /* The Job is already locked by a pending sequence =>
                Rollback all the previous locks.
               '++JobNumberInSeq': Rollback Job number that has been set =>
                The total number of Jobs has been reduced, Therefore need to withdraw */
            while(JobNumberInSeq < SeqCfgPtr->NumJobs)
            {
                /* The number of pending jobs in the sequence increases by 1 */
                JobNumberInSeq++;
                /* Offset to the previous pending job in the sequence */
                --JobIndexPtr;
                /* Rollback Job index that has been set =>
                    Current Job not yet linked, Only rollback previous Job*/
                /* #Violation: Spi_c_REF_1 */ 
                JobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, *JobIndexPtr); 
                /* Cancel asynchronous Job's link in current Sequence */
                JobCfgPtr->JobStatePtr->AsyncSeqStatePtr = NULL_PTR;
            }
            RetStatus = E_NOT_OK;
        }
    }

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Spi_AsyncScheduleJob
*
*   Service ID              : None.
*
*   Description             : This function shall schedule a job for a given HW unit. If the Job
*                             can not be started, the Job and its Sequence are aborted, the HW unit
*                             is handed over to the scheduler and the abort is reported.
*
*   Parameters in           : CoreId           : Execution Core ID Number.
*                             Job              : Job ID Number.
*                             CallNotification : TRUE: call the Job and Sequence end notifications
*                                                if the Job is aborted.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non-Reentrant(Same HwUnit).
*
*   Return value            : TRUE: The Job has been started or queued.
*                             FALSE: The Job could not be started and has been aborted.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, SPI_PRIVATE_CODE) Spi_AsyncScheduleJob
(
    Mcal_CoreType           CoreId,
    Spi_JobType             Job,
    boolean                 CallNotification
)
{
    boolean                         RetStatus;
    boolean                         PhyUnitAvailable;
    const Spi_JobConfigType         *JobCfgPtr;
    const Spi_SequenceConfigType    *AbortedSeqCfgPtr;
    const Spi_SequenceConfigType    *CancelledSeqCfgPtr;
#if (SPI_ENABLE_DMA == STD_ON)
    boolean                         TriggerDmaFlag;
    Spi_PhyUnitStateType            const *SpiPhyUnitStatusPtr;
    const Spi_PhyUnitConfigType     *PhyUnitCfgPtr;

    TriggerDmaFlag = FALSE;
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */

    /* Initialization function return value */
    RetStatus = TRUE;
    /* Get Job configuration information structure pointer */
    /* #Violation: Spi_c_REF_1 */ 
    JobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, Job); 
    /* No Job aborted or released yet */
    AbortedSeqCfgPtr = NULL_PTR;
    CancelledSeqCfgPtr = NULL_PTR;
    /* Enter asynchronous transmission critical protection */
    SPI_ENTER_CRITICAL_SECTION(AsyncTransmit);
    /* check whether the job used HW unit is busy */
    PhyUnitAvailable = FALSE;
    /* #Violation: Spi_c_REF_1 */
    if (SPI_IDLE == SPI_HWUNIT_STATUS(CoreId, JobCfgPtr->SpiNumber))
    {
        PhyUnitAvailable = TRUE;
    }
#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
    /* A HW unit reserved by a synchronous Sequence is not available, also while it is IDLE between
       two synchronous Jobs: the Job is only queued and started at the end of the synchronous Sequence */
    if (0U != (*(Spi_CoreStatus[CoreId]->PhyUnitBusySyncStatusPtr) & ((uint16)1U << JobCfgPtr->SpiNumber)))
    {
        PhyUnitAvailable = FALSE;
    }
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */
    if ((TRUE == PhyUnitAvailable) &&
        (NULL_PTR != JobCfgPtr->JobStatePtr->AsyncSeqStatePtr) &&
        (SPI_SEQ_CANCELLED == JobCfgPtr->JobStatePtr->AsyncSeqStatePtr->SeqResult))
    {
        /*  SWS_Spi_00145: the Sequence has been cancelled after the Job has been requested, the Job
            is not started and the Sequence end notification is called instead */
        CancelledSeqCfgPtr = Spi_AsyncReleaseCancelledJob(CoreId, Job);
    }
    else if (TRUE == PhyUnitAvailable)
    {
#if (SPI_ENABLE_DMA == STD_ON)
        /* Get PhyUnit status information structure pointer */
        /* #Violation: Spi_c_REF_1 */ 
        SpiPhyUnitStatusPtr = SPI_HWUNIT_STATUSPTR(CoreId, JobCfgPtr->SpiNumber); 
        if(TRUE == SpiPhyUnitStatusPtr->DmaEnable)
        {
            TriggerDmaFlag = Spi_AsyncJobDmaTransfer(CoreId, Job);
            RetStatus &= TriggerDmaFlag;
        }
        else
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */
        {
            /* Job is IDLE,Use Job to transmit data*/
            RetStatus &= Spi_AsyncJobTransfer(CoreId, Job);
        }
        if (FALSE == RetStatus)
        {
            /* The Job can not be started => abort the Job and its Sequence in a deterministic state */
            AbortedSeqCfgPtr = Spi_AsyncAbortJob(CoreId, Job);
        }
    }
    else
    {
        /*  SWS_Spi_00055:
            When the function Spi_AsyncTransmit is used for a Sequence with linked Jobs, the function
            shall transmit from the first Job up to the last Job in the sequence.
        */
        Spi_AsyncLinkJobList(CoreId, Job);

    }
    /* Exit asynchronous transmission critical protection */
    SPI_EXIT_CRITICAL_SECTION(AsyncTransmit);

#if (SPI_ENABLE_DMA == STD_ON)
    if(TRUE == TriggerDmaFlag)
    {
        /* Get PhyUnit configuration information structure pointer */
        /* #Violation: Spi_c_REF_1 */ 
        PhyUnitCfgPtr = SPI_HWUNIT_CONFIGPTR(CoreId, JobCfgPtr->SpiNumber);

        /* Enable DMA channel transfer */
        Dma_ChannelStart(PhyUnitCfgPtr->RxDmaChannel);
        Dma_ChannelStart(PhyUnitCfgPtr->TxDmaChannel);
    }
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */

    if (FALSE == RetStatus)
    {
        /* Hand over the released PhyUnit to the scheduler first: start the next queued Job or set
           it IDLE. The Job abort is already reported by the return value. */
        (void)Spi_AsyncScheduleNextJob(CoreId, Job, TRUE);
        /* Then report the aborted Job (SWS_Spi_00270: scheduling before end notification) */
        Spi_AsyncReportAbortedJob(CoreId, Job, AbortedSeqCfgPtr, CallNotification);
    }
    else if (NULL_PTR != CancelledSeqCfgPtr)
    {
        /* Hand over the released PhyUnit to the scheduler first, then call the Sequence end
           notification of the cancelled Sequence */
        (void)Spi_AsyncScheduleNextJob(CoreId, Job, TRUE);
        Spi_AsyncReportCancelledSeq(CoreId, CancelledSeqCfgPtr);
    }
    else
    /* #Violation: Spi_c_REF_2 */
    {
        /* The Job has been started or queued */
    }

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Spi_AsyncJobTransfer
*
*   Service ID              : None
*
*   Description             : Job transfer
*
*   Parameters in           : CoreId    : Execution Core ID Number.
*                             Job       : Job ID Number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non-Reentrant(Same HwUnit).
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, SPI_PRIVATE_CODE) Spi_AsyncJobTransfer
(
    Mcal_CoreType           CoreId,
    Spi_JobType             Job
)
{
    boolean                                 RetStatus;
    uint32                                  DataTotalNum;
    Spi_DeviceStateType                     *DevStatePtr;
    Spi_ChannelDynamicConfigType            ChDynamicConfig;
    const Spi_ExternalDeviceConfigType      *ExDeviceCfgPtr;
    const Spi_JobConfigType                 *JobCfgPtr;

    /*  SWS_Spi_00157:
        When the function Spi_AsyncTransmit is called, the SPI Handler/Driver shall handle the
        Job results. Result shall be SPI_JOB_PENDING when the transmission of Jobs is started.
    */
    /* Get Job status information, the input parameter is the Job ID */
    /* #Violation: Spi_c_REF_1 */ 
    SPI_JOB_STATUS(CoreId, Job) = SPI_JOB_PENDING; 
    /* Get Job configuration information structure pointer */
    /* #Violation: Spi_c_REF_1 */ 
    JobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, Job); 
    /*  SWS_Spi_00020:
        The function Spi_AsyncTransmit shall take over the given parameter, initiate a
        transmission, set the SPI Handler/Driver status to SPI_BUSY, set the sequence
        result to SPI_SEQ_PENDING and return.
    */
    /* Get PhyUnit status information, the input parameter is the PhyUnit ID */
    /* #Violation: Spi_c_REF_1 */ 
    SPI_HWUNIT_STATUS(CoreId, JobCfgPtr->SpiNumber) = SPI_BUSY; 
#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
    /* Set hardware occupied by asynchronous sequence */
    Spi_CoreStatus[CoreId]->PhyUnitStatusPtr
        [Spi_ConfigPtr->PhyUnitToCorePtr[JobCfgPtr->SpiNumber]].IsAsync = TRUE;
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */
    /* Get the total amount of all channel data in the job */
    DataTotalNum = Spi_GetDataTotalNumOfJob(CoreId, JobCfgPtr->JobId);
    /* The Move Counter data length register can only hold ESPI_MOVE_STEP_MASK frames */
    if (DataTotalNum > (uint32)ESPI_MOVE_STEP_MASK)
    {
        RetStatus = FALSE;
    }
    else
    {
        /* Configure the total amount of data to be transferred in Move Counter mode */
        RetStatus = Espi_Hal_SetMoveCounterDataLength(
            Spi_ConfigPtr->PhyUnitMapPtr[JobCfgPtr->SpiNumber], (uint16)DataTotalNum);
    }
    if(TRUE == RetStatus)
    {
        /* Get external status information structure pointer */
        /* #Violation: Spi_c_REF_1 */ 
        DevStatePtr = SPI_EXD_STATUSPTR(CoreId, JobCfgPtr->SpiNumber); 
        /* Initialize external device status pointer => current channel index */
        DevStatePtr->CurChannelIndexPtr = JobCfgPtr->ChannelIndexListPtr;
        /* Initialize external device status pointer => Total remaining channels */
        DevStatePtr->RemainingChannels = JobCfgPtr->NumChannels - 1U;
        /* Initialize external device status pointer => Current Job configuration information */
        DevStatePtr->CurJobPtr = JobCfgPtr;
        /* Initialize external device status pointer =>
           Set the job end flag, IsEndOfJob's defaults is FALSE in new Sequence */
        DevStatePtr->IsEndOfJob = (boolean)FALSE;
        /* Get external device configuration information structure pointer */
        /* #Violation: Spi_c_REF_1 */ 
        ExDeviceCfgPtr = SPI_EXD_CONFIGPTR(CoreId, JobCfgPtr->ExDeviceUnit); 
        /* Configure data transmission parity check mode */
        ChDynamicConfig.parityMode = ExDeviceCfgPtr->ParitySelection;
        /* Configure data transmission delay parameters */
        ChDynamicConfig.delayTime = ExDeviceCfgPtr->DelayParam;
        /* Configure move counter mode */
        ChDynamicConfig.dataMode = ESPI_MASTER_MODE_MOVECOUNTER;
        /* Configure output transmission bit order  */
        ChDynamicConfig.bitOrder = ESPI_BITORDER_LSB;
        /* Configure output transmission data width  */
        ChDynamicConfig.dataWidth = ESPI_DATAWIDTH_8;
        /* Calculate channel configuration register value */
        DevStatePtr->ChDynamicCfg = Espi_Hal_CalculateChannelDynamicConfiguration(ExDeviceCfgPtr->
                                                Spi_ExDeviceCfgInfoPtr->csChannel, &ChDynamicConfig);
#if (SPI_CUSTOMIZED_CS_EN == STD_ON)
        /* Select the chip select signal when using IO for chip select */
        if ((SPI_CS_VIA_GPIO == ExDeviceCfgPtr->CsSelection) && (FALSE == JobCfgPtr->PullCSbyData))
        {
            /* The Chip Select (CS) is attached to the Job definition. Chip Select
            ** shall be handled during Job transmission and shall be released at the end of
            ** it.This Chip Select handling shall be done according to the Job configuration
            ** parameters. */
            (void)Dio_FlipChannel(ExDeviceCfgPtr->GpioPortPin);
        }
#endif /* (SPI_CUSTOMIZED_CS_EN \== STD_ON) */

#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
        /* #Violation: Spi_c_REF_1 */ 
        if(SPI_INTERRUPT_MODE == SPI_ASYNC_MODE(CoreId)) 
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */
        {
            /* Enable RX and ERROR Interrupt */
            RetStatus &= Espi_Hal_SetInterrupt(Spi_ConfigPtr->PhyUnitMapPtr[JobCfgPtr->SpiNumber],
                                            (ESPI_INTC_FLAG_RX | ESPI_INTC_ALL_ERROR_FLAGS), TRUE);
        }
        if(TRUE == RetStatus)
        {
            /* Disable SPI DMA transfer function */
            RetStatus &= Espi_Hal_SetDma(Spi_ConfigPtr->PhyUnitMapPtr[JobCfgPtr->SpiNumber], FALSE);
        }
        /* Stop at the first failure: no data shall be sent with an incompletely configured PhyUnit */
        if(TRUE == RetStatus)
        {
            /* Initialize and transmit the transfer parameters for the first channel =>
            NewChannel's defaults is FALSE in new Sequence*/
            RetStatus &= Spi_AsyncJobTransferChannel(CoreId, JobCfgPtr->SpiNumber, TRUE);
        }
    }

    return RetStatus;
}

#if (SPI_ENABLE_DMA == STD_ON)
/****************************************************************************************************
*   Function Name           : Spi_AsyncJobDmaTransfer
*
*   Service ID              : None
*
*   Description             : Job transfer
*
*   Parameters in           : CoreId    : Execution Core ID Number.
*                             Job       : Job ID Number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non-Reentrant(Same HwUnit).
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, SPI_PRIVATE_CODE) Spi_AsyncJobDmaTransfer
(
    Mcal_CoreType           CoreId,
    Spi_JobType             Job
)
{
    boolean                                 RetStatus;
    Std_ReturnType                          RetResult;
    Spi_ChannelType                         ChCount;
    Spi_ChannelType                         ChannelTotalNum;
    uint32                                  DataTotalNum;
    uint32                                  ChDynamicCfg;
    const Spi_ChannelType                   *ChannelIndexPtr;
    const Spi_JobConfigType                 *JobCfgPtr;
    const Spi_ChannelConfigType             *ChannelCfgPtr;
    const Spi_PhyUnitConfigType              *PhyUnitCfgPtr;
    const Spi_ExternalDeviceConfigType      *ExDeviceCfgPtr;
    Dma_LliCfgType                          LliConfig;
    Spi_ChannelDynamicConfigType            ChDynamicConfig;

    RetResult = E_OK;
    /*  SWS_Spi_00157:
        When the function Spi_AsyncTransmit is called, the SPI Handler/Driver shall handle the
        Job results. Result shall be SPI_JOB_PENDING when the transmission of Jobs is started.
    */
    /* #Violation: Spi_c_REF_1 */ 
    SPI_JOB_STATUS(CoreId, Job) = SPI_JOB_PENDING; 
    /* Get Job configuration information structure pointer */
    /* #Violation: Spi_c_REF_1 */ 
    JobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, Job); 
    /*  SWS_Spi_00020:
        The function Spi_AsyncTransmit shall take over the given parameter, initiate a
        transmission, set the SPI Handler/Driver status to SPI_BUSY, set the sequence
        result to SPI_SEQ_PENDING and return.
    */
    /* Get PhyUnit status information, the input parameter is the PhyUnit ID */
    /* #Violation: Spi_c_REF_1 */ 
    SPI_HWUNIT_STATUS(CoreId, JobCfgPtr->SpiNumber) = SPI_BUSY;
#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
    /* Set hardware occupied by asynchronous sequence */
    Spi_CoreStatus[CoreId]->PhyUnitStatusPtr
        [Spi_ConfigPtr->PhyUnitToCorePtr[JobCfgPtr->SpiNumber]].IsAsync = TRUE;
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */
    /* Initialize external device status pointer ==> Current Job configuration information */
    /* #Violation: Spi_c_REF_1 */ 
    SPI_CURJOB_CONFIGPTR(CoreId, JobCfgPtr->SpiNumber) = JobCfgPtr; 
    /*  The DMA requests are still enabled from a previous DMA Job on this PhyUnit: they are disabled
        before the receive FIFO is flushed, so that the flush can not raise a spurious request */
    RetStatus = Espi_Hal_SetDma(Spi_ConfigPtr->PhyUnitMapPtr[JobCfgPtr->SpiNumber], FALSE);
    if (TRUE == RetStatus)
    {
        /*  Flush the receive FIFO before a DMA Job is started: a frame left over by a previous
            transfer would be moved into the first destination buffer of this Job and would shift
            every following frame. The reset also resets the Move Counter, so it is done before the
            Move Counter is programmed */
        RetStatus &= Espi_Hal_FlushRxFifo(Spi_ConfigPtr->PhyUnitMapPtr[JobCfgPtr->SpiNumber]);
        /* Clear the status flags raised by the reset and by the receive FIFO mode toggle */
        Espi_Hal_ClearFlagStatus(
            Spi_ConfigPtr->PhyUnitMapPtr[JobCfgPtr->SpiNumber], ESPI_ALL_FLAGS_RW_STATES);
    }
    /* Get the total amount of all channel data in the job */
    DataTotalNum = Spi_GetDataTotalNumOfJob(CoreId, JobCfgPtr->JobId);
    /* The Move Counter data length register can only hold ESPI_MOVE_STEP_MASK frames */
    if (DataTotalNum > (uint32)ESPI_MOVE_STEP_MASK)
    {
        RetStatus = FALSE;
    }
    else
    {
        /* Configure the total amount of data to be transferred in Move Counter mode */
        RetStatus &= Espi_Hal_SetMoveCounterDataLength(
                        Spi_ConfigPtr->PhyUnitMapPtr[JobCfgPtr->SpiNumber], (uint16)DataTotalNum);
    }
    if(TRUE == RetStatus)
    {
        /* Get external device configuration information structure pointer */
        /* #Violation: Spi_c_REF_1 */ 
        ExDeviceCfgPtr = SPI_EXD_CONFIGPTR(CoreId, JobCfgPtr->ExDeviceUnit); 
        /* Configure data transmission parity check mode */
        ChDynamicConfig.parityMode = ExDeviceCfgPtr->ParitySelection;
        /* Configure data transmission delay parameters */
        ChDynamicConfig.delayTime = ExDeviceCfgPtr->DelayParam;
        /* Configure move counter mode */
        ChDynamicConfig.dataMode = ESPI_MASTER_MODE_MOVECOUNTER;
        /* Configure output transmission bit order  */
        ChDynamicConfig.bitOrder = ESPI_BITORDER_LSB;
        /* Configure output transmission data width  */
        ChDynamicConfig.dataWidth = ESPI_DATAWIDTH_8;
        /* Calculate channel configuration register value */
        ChDynamicCfg = Espi_Hal_CalculateChannelDynamicConfiguration(
                ExDeviceCfgPtr->Spi_ExDeviceCfgInfoPtr->csChannel, &ChDynamicConfig);
        /* Configure the last bit in Move Counter mode */
        ChDynamicCfg |= JobCfgPtr->PullCSbyData;
        /* Get the index pointer of the channel in the Job*/
        ChannelIndexPtr = JobCfgPtr->ChannelIndexListPtr;
        /* Initialize the burstsize of the linked list source address */
        LliConfig.source.burstSize = DMA_CHANNELBURSTSIZE_1;
        /* Initialize the burstsize of the linked list destination address */
        LliConfig.destination.burstSize = DMA_CHANNELBURSTSIZE_1;
        /* Get PhyUnit configuration information structure pointer */
        /* #Violation: Spi_c_REF_1 */ 
        PhyUnitCfgPtr = SPI_HWUNIT_CONFIGPTR(CoreId, JobCfgPtr->SpiNumber); 
        /* Get the total number of channels bound to the job */
        ChannelTotalNum = JobCfgPtr->NumChannels;
        /* Polling Processing Channel in Job */
         for(ChCount = 0U; ((ChCount < ChannelTotalNum) && (E_OK == RetResult)); ChCount++)
        {
            /* #Violation: Spi_c_REF_1 */ 
            ChannelCfgPtr = SPI_CH_CONFIGPTR(CoreId, *ChannelIndexPtr); 
            /* Offset to the next Channel bound to the Job */
            ChannelIndexPtr++;
            /* Clear the DL + MSB bit in the EMCON register */
            ChDynamicCfg &= SPI_CH_CONFIG_CLR;
            /* Configure the data width bit in the EMCON register */
            ChDynamicCfg |= ((uint32)ChannelCfgPtr->DataFrameWidth) << SPI_DATAWIDTH_MASK;
            /* Configure the shift sequence bits in the EMCON register */
            ChDynamicCfg |= ((uint32)ChannelCfgPtr->TransferStart) << SPI_SHIFTORDER_MASK;
            /* Save channel dynamic configuration to global buffer */
            PhyUnitCfgPtr->ChDynamicCfgPtr[ChCount] = ChDynamicCfg;
            /* Configure the DMA linked list for SPI channel dynamic configuration */
            /* #Violation: Spi_c_REF_5 */ 
            LliConfig.source.address = (uint32)&PhyUnitCfgPtr->ChDynamicCfgPtr[ChCount];
            LliConfig.source.increment = DMA_CHANNELADDRESSINCREMENT_NO_INCREASE;
            LliConfig.destination.address =
                /* #Violation: Spi_c_REF_5 */
                (uint32)&Spi_ConfigPtr->PhyUnitMapPtr[JobCfgPtr->SpiNumber]->EMCONENTRY; 
            LliConfig.destination.increment = DMA_CHANNELADDRESSINCREMENT_NO_INCREASE;
            LliConfig.transferWidth = DMA_CHANNELTRANSFERWIDTH_32BIT;
            LliConfig.transferSize = 1U;
            /* Point to the next member in linked list ==> TXBuffer(1, 3, 5, ...) */
            LliConfig.linkedListItemAddress =
                    /* #Violation: Spi_c_REF_5 */
                    (uint32)&PhyUnitCfgPtr->DmaTcsBufferPtr[(ChCount * 2U) + 1U];
            /* TC interrupt disabled */
            LliConfig.terminaCountInterEn = FALSE;
            /* Write the linked list configuration information into linked list array */
            /* #Violation: Spi_c_REF_12 */ 
            RetResult |= Dma_LliMemberInsertManual(
                PhyUnitCfgPtr->TxDmaChannel,
                &PhyUnitCfgPtr->DmaTcsBufferPtr[ChCount * 2U],
                &LliConfig);
            
            /* Configure the DMA linked list for SPI channel TXBuffPtr configuration */
            if (NULL_PTR != ChannelCfgPtr->BufferDescriptorPtr->TXBuffPtr)
            {
                /* #Violation: Spi_c_REF_1 */
                /* #Violation: Spi_c_REF_5 */ 
                LliConfig.source.address = MCAL_PFLASH_ADDR_INTERNALTODEVICE(
                                    (uint32)ChannelCfgPtr->BufferDescriptorPtr->TXBuffPtr);
                LliConfig.source.increment = DMA_CHANNELADDRESSINCREMENT_INCREASE;
            }
            /* Send using default data */
            else
            {
                LliConfig.source.address =
                    /* #Violation: Spi_c_REF_5 */
                    (uint32)&ChannelCfgPtr->BufferDescriptorPtr->ChDefaultData;
                LliConfig.source.increment = DMA_CHANNELADDRESSINCREMENT_NO_INCREASE;
            }
            LliConfig.destination.address =
                /* #Violation: Spi_c_REF_5 */ 
                (uint32)&Spi_ConfigPtr->PhyUnitMapPtr[JobCfgPtr->SpiNumber]->DATAENTRY; 
            LliConfig.destination.increment = DMA_CHANNELADDRESSINCREMENT_NO_INCREASE;
            LliConfig.transferSize = *(ChannelCfgPtr->ActualDataLengthPtr);
            if(ChannelCfgPtr->FrameWidth == ESPI_DATABUFFER_8BITS)
            {
                LliConfig.transferWidth = DMA_CHANNELTRANSFERWIDTH_8BIT;
            }
            else if(ChannelCfgPtr->FrameWidth == ESPI_DATABUFFER_16BITS)
            {
                LliConfig.transferWidth = DMA_CHANNELTRANSFERWIDTH_16BIT;
            }
            else
            {
                LliConfig.transferWidth = DMA_CHANNELTRANSFERWIDTH_32BIT;
            }
            if ((ChannelTotalNum - 1U) == ChCount)
            {
                /* Last member in linked list */
                LliConfig.linkedListItemAddress = (uint32)0U;
                /* TC interrupt enabled (include polling mode) */
                LliConfig.terminaCountInterEn = TRUE;
            }
            else
            {
                /* Point to the next member in linked list ==> EMCON(2, 4, 6, ...) */
                LliConfig.linkedListItemAddress =
                    /* #Violation: Spi_c_REF_5 */
                    (uint32)&PhyUnitCfgPtr->DmaTcsBufferPtr[(ChCount + 1U  )* 2U]; 
                /* TC interrupt disabled */
                LliConfig.terminaCountInterEn = FALSE;
            }
            /* Write the linked list configuration information into linked list array */
            RetResult |= Dma_LliMemberInsertManual(
                PhyUnitCfgPtr->TxDmaChannel,
                /* #Violation: Spi_c_REF_5 */
                &PhyUnitCfgPtr->DmaTcsBufferPtr[(ChCount * 2U) + 1U],
                &LliConfig); 

            /* Configure the DMA linked list for SPI channel RXBuffPtr configuration */
            LliConfig.source.address =
                /* #Violation: Spi_c_REF_5 */
                (uint32)&Spi_ConfigPtr->PhyUnitMapPtr[JobCfgPtr->SpiNumber]->RDR;
            LliConfig.source.increment = DMA_CHANNELADDRESSINCREMENT_NO_INCREASE;
            /* Received data needs to be retained */
            if (NULL_PTR != ChannelCfgPtr->BufferDescriptorPtr->RXBuffPtr)
            {
                LliConfig.destination.address =
                    /* #Violation: Spi_c_REF_5 */
                    (uint32)ChannelCfgPtr->BufferDescriptorPtr->RXBuffPtr;
                LliConfig.destination.increment = DMA_CHANNELADDRESSINCREMENT_INCREASE;
            }
            /* Received data needs to be discarded */
            else
            {
                /* #Violation: Spi_c_REF_5 */
                LliConfig.destination.address = (uint32)&Spi_RxBuffer;
                LliConfig.destination.increment = DMA_CHANNELADDRESSINCREMENT_NO_INCREASE;
            }
            /* "LliConfig.transferWidth" is the same as TX DMA channel */
            /* "LliConfig.transferSize" is the same as TX DMA channel */
            if ((ChannelTotalNum - 1U) == ChCount)
            {
                /* Last member in linked list */
                LliConfig.linkedListItemAddress = (uint32)0U;
                /* TC interrupt enabled (include polling mode) */
                LliConfig.terminaCountInterEn = TRUE;
            }
            else
            {
                /* Point to the next member in linked list ==> RXBuffer(n+1, n+2, n+3, ...) */
                LliConfig.linkedListItemAddress =
                    /* #Violation: Spi_c_REF_5 */ 
                    (uint32)(&PhyUnitCfgPtr->DmaTcsBufferPtr[(ChannelTotalNum * 2U) + ChCount + 1U]); 
                /* TC interrupt disabled */
                LliConfig.terminaCountInterEn = FALSE;
            }
            /* Write the linked list configuration information into linked list array */
            RetResult |= Dma_LliMemberInsertManual(
                PhyUnitCfgPtr->RxDmaChannel,
                /* #Violation: Spi_c_REF_5 */
                &PhyUnitCfgPtr->DmaTcsBufferPtr[(ChannelTotalNum * 2U) + ChCount],
                &LliConfig);
        }
        /* Stop at the first failure: the PhyUnit shall not be configured further and the DMA
           transfer shall not be requested if a linked list member could not be inserted */
        if (E_OK != RetResult)
        {
            RetStatus = FALSE;
        }
        if (TRUE == RetStatus)
        {
            /* Initialize linked list transmission head node */
            (void)Dma_LliInsertCompleteManual(PhyUnitCfgPtr->TxDmaChannel, &PhyUnitCfgPtr->DmaTcsBufferPtr[0]);
            (void)Dma_LliInsertCompleteManual(
                    PhyUnitCfgPtr->RxDmaChannel, &PhyUnitCfgPtr->DmaTcsBufferPtr[ChannelTotalNum * 2U]);
            /* Enable ERROR Interrupt */
            RetStatus &= Espi_Hal_SetInterrupt(Spi_ConfigPtr->PhyUnitMapPtr[JobCfgPtr->SpiNumber],
                                    ESPI_INTC_ALL_ERROR_FLAGS, TRUE);
        }
        if (TRUE == RetStatus)
        {
            /* Configuring the threshold in DMA mode */
            RetStatus &= Espi_Hal_SetFifoLevel(Spi_ConfigPtr->PhyUnitMapPtr[JobCfgPtr->SpiNumber],
                                (uint8)ESPI_TXFIFO_THRESHOLD_ONE, (uint8)ESPI_RXFIFO_THRESHOLD_ONE);
        }
        if (TRUE == RetStatus)
        {
            /* Enable SPI DMA transfer function */
            RetStatus &= Espi_Hal_SetDma(Spi_ConfigPtr->PhyUnitMapPtr[JobCfgPtr->SpiNumber], TRUE);
        }
        if (TRUE == RetStatus)
        {
            /* Set STS.TXF to enable DMA linked list transmission */
            RetStatus &= Espi_Hal_TriggerDmaRequest(Spi_ConfigPtr->PhyUnitMapPtr[JobCfgPtr->SpiNumber]);
        }
    }
    if((TRUE == RetStatus) && (E_OK== RetResult))
    {
        RetStatus = TRUE;
#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
        /*  The DMA transfers the whole Job without SPI interaction: one SPI_TIMEOUT_US budget per
            FIFO round of at most SPI_AVAILABLE_FIFOLEVEL frames, rounded up */
        /* #Violation: Spi_c_REF_1 */
        SPI_EXD_STATUSPTR(CoreId, JobCfgPtr->SpiNumber)->AsyncDeadline = Spi_AsyncStampDeadline(
            (DataTotalNum + ((uint32)SPI_AVAILABLE_FIFOLEVEL - 1UL)) / (uint32)SPI_AVAILABLE_FIFOLEVEL);
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */
#if (SPI_CUSTOMIZED_CS_EN == STD_ON)
        if ((SPI_CS_VIA_GPIO == ExDeviceCfgPtr->CsSelection) && (FALSE == JobCfgPtr->PullCSbyData))
        {
            /* The Chip Select (CS) is attached to the Job definition. Chip Select
            ** shall be handled during Job transmission and shall be released at the end of
            ** it.This Chip Select handling shall be done according to the Job configuration
            ** parameters. */
            (void)Dio_FlipChannel(ExDeviceCfgPtr->GpioPortPin);
        }
#endif /* (SPI_CUSTOMIZED_CS_EN \== STD_ON) */
    }
    else
    {
        RetStatus = FALSE;
    }

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Spi_DmaNotification
*
*   Service ID              : None
*
*   Description             : Notification callback function after DMA transfer is completed.
*
*   Parameters in           : Channel    : DMA logical channel ID.
*                             ChIntrEvt  : DMA interrupt event flag.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, SPI_PUBLIC_CODE) Spi_DmaNotification
(
    Dma_ChannelType Channel,
    Dma_ChEventType ChIntrEvt
)
{
#if (SPI_SAFETY_ENABLE == STD_ON)
    boolean                             RetResult;
#endif /* (SPI_SAFETY_ENABLE \== STD_ON) */
    Mcal_CoreType                       CoreId;
    uint32                              DmaChannelStatus;
    Spi_HWUnitType                      PhyUnit;
    Spi_JobType                         Job;
    boolean                             TransferOk;
    const Spi_JobConfigType             *JobCfgPtr;
    const Spi_PhyUnitConfigType         *PhyUnitCfgPtr;

    /* Get core id which is executing currently */
    /* #Violation: Spi_c_REF_1 */
    CoreId = Mcal_GetCoreId();
    PhyUnit = Spi_ConfigPtr->DmaChToPhyUnitPtr[Channel];
    /*  A DMA channel which is not assigned to a hardware unit of this driver shall not be used as an
        index into the state tables */
    if (SPI_DMACHNOUSED_MASK != PhyUnit)
    {
        TransferOk = FALSE;
        Job = SPI_JOB_NULL;
        /* Enter asynchronous transmission critical protection */
        SPI_ENTER_CRITICAL_SECTION(AsyncTransmit);
        /* Get the Job configuration information pointer occupied by the current hardware */
        /* #Violation: Spi_c_REF_1 */
        JobCfgPtr = SPI_CURJOB_CONFIGPTR(CoreId, PhyUnit);
        if (NULL_PTR != JobCfgPtr)
        {
            Job = JobCfgPtr->JobId;
        }
        /* Exit asynchronous transmission critical protection */
        SPI_EXIT_CRITICAL_SECTION(AsyncTransmit);
        if (SPI_JOB_NULL != Job)
        {
            if (DMA_CH_INT_TC != ChIntrEvt)
            {
                /*  DMA_CH_INT_ERROR: the DMA transfer of the Job has failed and can not be
                    completed. Dropping the notification would leave the Job SPI_JOB_PENDING and the
                    hardware unit SPI_BUSY for ever */
                TransferOk = FALSE;
            }
            else
            {
                /* Get PhyUnit configuration information structure pointer */
                /* #Violation: Spi_c_REF_1 */
                PhyUnitCfgPtr = SPI_HWUNIT_CONFIGPTR(CoreId, PhyUnit);
                /*  The TX DMA channel has no terminal count interrupt, its status is only refreshed
                    by this call, which also clears the hardware terminal count flag: it is called
                    once per DMA Job and its result is always acted on. Dma_GetChannelStatus enters
                    its own critical section and is not called while a SPI one is held */
                DmaChannelStatus =  Dma_GetChannelStatus(PhyUnitCfgPtr->TxDmaChannel);
                /* Check the TX DMA Channel status is "DMA_CH_TRANSFER_COMPLETE" and without error */
                if (((DmaChannelStatus & (uint32)DMA_CH_TRANSFER_COMPLETE) ==
                        (uint32)DMA_CH_TRANSFER_COMPLETE) &&
                    ((uint32)0U == (DmaChannelStatus & (uint32)DMA_CH_ERROR)))
                {
                    TransferOk = TRUE;
                }
            }
            if (TRUE == TransferOk)
            {
#if (SPI_SAFETY_ENABLE == STD_ON)
                /* Call the Job transfer completion Handler */
                RetResult = Spi_AsyncJobTransferFinished(CoreId, Job);
                if(FALSE == RetResult)
                {
                    (void)Det_ReportRuntimeError(SPI_MODULE_ID, SPI_INSTANCE_ID,
                                        SPI_SID_DMA_NOTIFICATION, SPI_E_SAFETY_ERROR);
                }
#else
                /* Call hardware for asynchronous data reception */
                (void)Spi_AsyncJobTransferFinished(CoreId, Job);
#endif /* (SPI_SAFETY_ENABLE \== STD_ON) */
            }
            else
            {
                /*  The DMA reported an error, or the RX channel finished while the TX channel did
                    not: the Job can not be completed and is aborted instead of dropping the
                    notification. The claim inside Spi_AsyncAbortRunningJob denies this call if the
                    Job has already been finished or aborted by another context */
                (void)Spi_AsyncAbortRunningJob(CoreId, PhyUnit, FALSE);
            }
        }
    }
}
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */
/****************************************************************************************************
*   Function Name           : Spi_AsyncLinkJobList
*
*   Service ID              : None.
*
*   Description             : This function shall add a job to the queue.
*
*   Parameters in           : CoreId    : Execution Core ID Number.
*                             Job       : Job ID Number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non-Reentrant(Same HwUnit).
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2.
*
*   AUTOSAR_Requirement     : SWS_Spi_00055
****************************************************************************************************/
static FUNC(void, SPI_PRIVATE_CODE) Spi_AsyncLinkJobList
(
    Mcal_CoreType           CoreId,
    Spi_JobType             Job
)
{
    uint8                       Priority;
    Spi_JobType                 *JobListTailPtr;
    Spi_PhyUnitStateType         *SpiPhyUnitStatusPtr;
    const Spi_JobConfigType     *JobCfgPtr;
    const Spi_JobConfigType     *TailJobCfgPtr;

    /* Get Job configuration information structure pointer */
    /* #Violation: Spi_c_REF_1 */
    JobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, Job); 
    /* Reset the new linked list tail event */
    JobCfgPtr->JobStatePtr->AsyncNextJob = SPI_JOB_NULL;
    /* Get the Priority of the linked new Job */
    Priority = JobCfgPtr->Priority;
    /* Get PhyUnit status information structure pointer */
    /* #Violation: Spi_c_REF_1 */
    SpiPhyUnitStatusPtr = SPI_HWUNIT_STATUSPTR(CoreId, JobCfgPtr->SpiNumber); 
    /* Get the tail pointer of the linked list under the priority of the new Job */
    JobListTailPtr = &SpiPhyUnitStatusPtr->ScheduledJobsListTail[Priority];
    /* Check whether list tail under the current priority is empty */
    if (SPI_JOB_NULL == *JobListTailPtr)
    {
        /* the list is empty =>
           Update the head of the list use the CoreJobIdx of the current Job */
        SpiPhyUnitStatusPtr->ScheduledJobsListHead[Priority] = Job;
    }
    else
    {
        /* Get the Job configuration at the tail of the linked list */
        /* #Violation: Spi_c_REF_1 */
        TailJobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, *JobListTailPtr); 
        /* the list isn't empty =>
           Update the next event at the tail of the old linked list */
        TailJobCfgPtr->JobStatePtr->AsyncNextJob = Job;
    }
    /* Update the tail of the list use the CoreJobIdx of the new Job */
    *JobListTailPtr = Job;
    /* The maximum priority level occupied by updates */
    if (SpiPhyUnitStatusPtr->MaxScheduledPriority < (sint8)Priority)
    {
        SpiPhyUnitStatusPtr->MaxScheduledPriority = (sint8)Priority;
    }
}

/****************************************************************************************************
*   Function Name           : Spi_AsyncJobTransferChannel
*
*   Service ID              : None.
*
*   Description             : This function fills ESPI FIFO Transmit buffer with the predefined data
*                             assigned or transmit the default buffer values in case of the lack of
*                             transmit data buffer.
*
*   Parameters in           : CoreId     : Execution Core ID Number.
*                             PhyUnit     : Hardware ID Number.
*                             NewChannel : New channel flag.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non-Reentrant(Same HwUnit).
*
*   Return value            : None
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, SPI_PRIVATE_CODE) Spi_AsyncJobTransferChannel
(
    Mcal_CoreType           CoreId,
    Spi_HWUnitType          PhyUnit,
    boolean                 NewChannel
)
{
    uint8                                           Threshold;
    boolean                                         RetStatus;
    uint32                                          TxBufferIndex;
    Spi_DeviceStateType                             *DevStatePtr;
    const Spi_ChannelConfigType                     *ChannelCfgPtr;
#if (SPI_CUSTOMIZED_CS_EN == STD_ON)
    const Spi_ExternalDeviceConfigType              *ExDeviceCfgPtr;
#endif /* (SPI_CUSTOMIZED_CS_EN \== STD_ON) */

    /* Get external status information structure pointer */
    /* #Violation: Spi_c_REF_1 */
    DevStatePtr = SPI_EXD_STATUSPTR(CoreId, PhyUnit); 
    /* Get Channel configuration information structure pointer */
    /* #Violation: Spi_c_REF_1 */
    ChannelCfgPtr = SPI_CH_CONFIGPTR(CoreId, *(DevStatePtr->CurChannelIndexPtr)); 
    /* Determine whether it is a new Chanel */
    if (TRUE == NewChannel)
    {
        /* Updates the width of Sent frames in a pending channel */
        DevStatePtr->SentFramesWidth = ChannelCfgPtr->FrameWidth;
        /* Set the total number of data to be sent */
        DevStatePtr->RemainingData = *(ChannelCfgPtr->ActualDataLengthPtr);
        /* Set actual receive data length */
        DevStatePtr->ReceivedData = *(ChannelCfgPtr->ActualDataLengthPtr);
        /* Set TX buffer */
        DevStatePtr->CurTxBufPtr = ChannelCfgPtr->BufferDescriptorPtr->TXBuffPtr;
        /* Set RX buffer */
        DevStatePtr->CurRxBufPtr = ChannelCfgPtr->BufferDescriptorPtr->RXBuffPtr;
        /* Clear the DL + MSB bit bit in the EMCON register */
        DevStatePtr->ChDynamicCfg &= SPI_CH_CONFIG_CLR;
        /* Configure the data width bit in the EMCON register */
        DevStatePtr->ChDynamicCfg |= ((uint32)ChannelCfgPtr->DataFrameWidth) << SPI_DATAWIDTH_MASK;
        /* Configure the shift sequence bits in the EMCON register */
        DevStatePtr->ChDynamicCfg |= ((uint32)ChannelCfgPtr->TransferStart) << SPI_SHIFTORDER_MASK;
        /* Write the EMCON register and configure the Last bit */
        Espi_Hal_WriteConfiguration(Spi_ConfigPtr->PhyUnitMapPtr[PhyUnit],
                    DevStatePtr->ChDynamicCfg, DevStatePtr->CurJobPtr->PullCSbyData);
    }
    /* Calculate FIFO threshold based on data volume */
    if(SPI_AVAILABLE_FIFOLEVEL < DevStatePtr->RemainingData)
    {
        Threshold = SPI_AVAILABLE_FIFOLEVEL;
    }
    else
    {
        Threshold = (uint8)DevStatePtr->RemainingData;
    }
    /* Reset TxBuffer Index */
    TxBufferIndex = (((uint32)*(ChannelCfgPtr->ActualDataLengthPtr) - (uint32)DevStatePtr->RemainingData) *
                        (uint32)DevStatePtr->SentFramesWidth);
    /* update remaining data length */
    DevStatePtr->RemainingData -= (uint16)Threshold;
    /* Updates the number of frames sent, which must be read back in the next ISR call */
    DevStatePtr->SentFrames = Threshold;
    /* Check if the channel is the last channel and last frame */
    if ((0U == DevStatePtr->RemainingChannels) && (0U == DevStatePtr->RemainingData))
    {
        DevStatePtr->IsEndOfJob = TRUE;
    }
    /* Configure FIFO threshold in Move Counter mode */
    RetStatus = Espi_Hal_SetFifoLevel(Spi_ConfigPtr->PhyUnitMapPtr[PhyUnit],
                                      (uint8)ESPI_TXFIFO_THRESHOLD_ONE, Threshold);
    /* Clear event status flags */
    Espi_Hal_ClearFlagStatus(
        Spi_ConfigPtr->PhyUnitMapPtr[PhyUnit], ESPI_ALL_FLAGS_RW_STATES);
#if (SPI_CUSTOMIZED_CS_EN == STD_ON)
    /* Get external device configuration information structure pointer */
    /* #Violation: Spi_c_REF_1 */
    ExDeviceCfgPtr = SPI_EXD_CONFIGPTR(CoreId, DevStatePtr->CurJobPtr->ExDeviceUnit); 
#endif /* (SPI_CUSTOMIZED_CS_EN \== STD_ON) */
    while ((0U < Threshold) && (TRUE == RetStatus))
    {
        /* Decrement count value */
        Threshold--;
#if (SPI_CUSTOMIZED_CS_EN == STD_ON)
        /* Select chip select before data transmission */
        if ((SPI_CS_VIA_GPIO == ExDeviceCfgPtr->CsSelection) &&
            (TRUE == DevStatePtr->CurJobPtr->PullCSbyData))
        {
            (void)Dio_FlipChannel(ExDeviceCfgPtr->GpioPortPin);
        }
#endif /* (SPI_CUSTOMIZED_CS_EN \== STD_ON) */
        /*  SWS_Spi_00437:
            Data buffers are accessed as uint8, uint16 or uint32 according to SpiDataWidth
            independently to Spi_DataBufferType.
            SWS_Spi_00023:
            If the given parameter "DataBufferPtr" is null, the function Spi_WriteIB shall
            assume that the data to be transmitted is not relevant and the default transmit
            value of the given channel shall be used instead.
            SWS_Spi_00028:
            When the SPI Handler/Driver's environment is calling the function Spi_SetupEB with the
            parameter SrcDataBufferPtr being a Null pointer, the function shall transmit the default
            transmit value configured for the channel after a Transmit method is requested.
            See also [SWS_Spi_00035]
        */
        /* Write transfer data to TXFIFO */
#if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE1) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE2))
        if(NULL_PTR == DevStatePtr->CurTxBufPtr)
        {
            (void)Espi_Hal_SendData(Spi_ConfigPtr->PhyUnitMapPtr[PhyUnit],
                    ((const uint8 *)&(ChannelCfgPtr->BufferDescriptorPtr->ChDefaultData)),
                    ChannelCfgPtr->FrameWidth);
        }
        else
#endif /* ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE1) \|| (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE2)) */
        {
            TxBufferIndex += Espi_Hal_SendData(Spi_ConfigPtr->
                    PhyUnitMapPtr[PhyUnit], &(DevStatePtr->CurTxBufPtr[TxBufferIndex]), ChannelCfgPtr->FrameWidth);
        }
#if (SPI_CUSTOMIZED_CS_EN == STD_ON)
        /* The chip select is released after the data transfer is completed. */
        if ((SPI_CS_VIA_GPIO == ExDeviceCfgPtr->CsSelection) &&
            (TRUE == DevStatePtr->CurJobPtr->PullCSbyData))
        {
            /* #Violation: Spi_c_REF_12 */
            RetStatus &= Spi_WaitPhaseStatus(PhyUnit);
            (void)Dio_FlipChannel(ExDeviceCfgPtr->GpioPortPin);
        }
#endif /* (SPI_CUSTOMIZED_CS_EN \== STD_ON) */
    }
#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
    if (TRUE == RetStatus)
    {
        /*  One FIFO round has been written: restart the timeout supervision of the hardware unit.
            A round is at most SPI_AVAILABLE_FIFOLEVEL frames and gets one SPI_TIMEOUT_US budget */
        DevStatePtr->AsyncDeadline = Spi_AsyncStampDeadline(1UL);
    }
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Spi_AsyncJobTransferFinished
*
*   Service ID              : None.
*
*   Description             : This function is called after a Job has been executed The function
*                             calls Job and Sequence end notifications and schedules the next job of
*                             the sequence or on the liberated HW Unit.
*
*   Parameters in           : CoreId    : Execution Core ID Number.
*                             Job       : Job ID Number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non-Reentrant(Same HwUnit).
*
*   Return value            : None
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2.
*
*   AUTOSAR_Requirement     : SWS_Spi_00116.
****************************************************************************************************/
static FUNC(boolean, SPI_PRIVATE_CODE) Spi_AsyncJobTransferFinished
(
    Mcal_CoreType           CoreId,
    Spi_JobType             Job
)
{
    Spi_JobType                         NextJob;
    boolean                             RetStatus;
    Spi_SequenceStateType               *SeqStatePtr;
    boolean                             NextJobStarted;
    boolean                             IsJobClaimed;
    const Spi_JobConfigType             *NextJobCfgPtr;
    const Spi_JobConfigType             *JobCfgPtr;
    const Spi_SequenceConfigType        *AbortedSeqCfgPtr;
    const Spi_SequenceConfigType        *CancelledSeqCfgPtr;
#if (SPI_CUSTOMIZED_CS_EN == STD_ON)
    const Spi_ExternalDeviceConfigType  *ExDeviceCfgPtr;
#endif /* (SPI_CUSTOMIZED_CS_EN \== STD_ON) */
#if (SPI_ENABLE_DMA == STD_ON)
    boolean                             TriggerDmaFlag;
    const Spi_PhyUnitStateType          *SpiPhyUnitStatusPtr;
    const Spi_PhyUnitConfigType         *PhyUnitCfgPtr;

    /* Initialize DMA trigger flag */
    TriggerDmaFlag = FALSE;
#endif /* ((SPI_LEVEL_DELIVERED != SPI_LEVEL1) \&& (SPI_ENABLE_DMA != STD_OFF)) */
    /* Initialization function return value */
    RetStatus = TRUE;
    NextJob = 0U;
    NextJobCfgPtr = NULL_PTR;
    NextJobStarted = TRUE;
    AbortedSeqCfgPtr = NULL_PTR;
    CancelledSeqCfgPtr = NULL_PTR;
    /* Get Job configuration information structure pointer */
    /* #Violation: Spi_c_REF_1 */
    JobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, Job);
    /*  Claim the end of the Job. An abort claimed by Spi_AsyncAbortRunningJob has already brought
        the Job, its Sequence and the HW unit into a deterministic state and calls the end
        notifications itself: this call shall then not release the chip select, not set the Job
        result and not schedule the HW unit a second time.
        SWS_Spi_00292: Result shall be SPI_JOB_OK when the transmission of Jobs is success.
    */
    IsJobClaimed = FALSE;
    /* Enter asynchronous transmission critical protection */
    SPI_ENTER_CRITICAL_SECTION(AsyncTransmit);
    if (SPI_JOB_PENDING == JobCfgPtr->JobStatePtr->JobResult)
    {
        JobCfgPtr->JobStatePtr->JobResult = SPI_JOB_OK;
        IsJobClaimed = TRUE;
    }
    /* Exit asynchronous transmission critical protection */
    SPI_EXIT_CRITICAL_SECTION(AsyncTransmit);
    if (FALSE == IsJobClaimed)
    {
        /* The Job has already been aborted, the aborting context owns the recovery */
        return TRUE;
    }
#if (SPI_CUSTOMIZED_CS_EN == STD_ON)
    /* Get external device configuration information structure pointer */
    /* #Violation: Spi_c_REF_1 */
    ExDeviceCfgPtr = SPI_EXD_CONFIGPTR(CoreId, JobCfgPtr->ExDeviceUnit); 
    /* Check whether GPIO chip select is used and release the chip select with Job */
    if ((SPI_CS_VIA_GPIO == ExDeviceCfgPtr->CsSelection) && (FALSE == JobCfgPtr->PullCSbyData))
    {
        /* toggle chip select signal */
        (void)Dio_FlipChannel(ExDeviceCfgPtr->GpioPortPin);
    }
#endif /* (SPI_CUSTOMIZED_CS_EN \== STD_ON) */
    /*  SWS_Spi_00118:
        If Jobs are configured with a specific end notification function, the SPI Handler/Driver
        shall call this notification function at the end of the Job transmission.
        SWS_Spi_00119:
        When a valid notification function pointer is configured (see [SWS_Spi_00071]), the SPI
        Handler/Driver shall call this notification function at the end of a Job transmission
        regardless of the result of the Job transmission being either SPI_JOB_FAILED or SPI_JOB_OK
        (rational: avoid deadlocks or endless loops).
        SWS_Spi_00088:
        For asynchronous levels, LEVEL 1 and LEVEL 2, the SPI Handler/Driver can call end
        notification functions at the end of a Job.
        SWS_Spi_00270:
        In case call end notification function and rescheduling are fully done by software,
        the order between these shall be first scheduling and then the call of end notification
        function executed.
        SWS_Spi_00270:
        In case call end notification function and rescheduling are fully done by software,
        the order between these shall be first scheduling and then the call of end notification
        function executed.
        SWS_Spi_00071:
        If the SpiJobEndNotification is configured (i.e. not a null pointer), the SPI Handler/Driver
        shall call the configured callback notification at the end of a Job transmission.
        Note: This routine might be called on interrupt level, depending on the calling function.
    */
    /* Run Job EndNotification (if there is one) */
    if (NULL_PTR != JobCfgPtr->JobEndNotificationPtr)
    {
        JobCfgPtr->JobEndNotificationPtr();
    }

    /* Enter asynchronous transmission critical protection */
    SPI_ENTER_CRITICAL_SECTION(AsyncTransmit);
#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
    /*  The Job is finished: stop supervising the hardware unit. A next Job started further down in
        this critical section stamps its own deadline */
    /* #Violation: Spi_c_REF_1 */
    SPI_EXD_STATUSPTR(CoreId, JobCfgPtr->SpiNumber)->AsyncDeadline = 0ULL;
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */
    /* This variable is not used only when DMA is STD_OFF at LEVEL1 */
#if (SPI_ENABLE_DMA == STD_ON)
    /* #Violation: Spi_c_REF_1 */
    SpiPhyUnitStatusPtr = SPI_HWUNIT_STATUSPTR(CoreId, JobCfgPtr->SpiNumber); 

    if(TRUE == SpiPhyUnitStatusPtr->DmaEnable)
    {
        /* Disable ERROR Interrupt */
#if (SPI_SAFETY_ENABLE == STD_ON)
        RetStatus &= Espi_Hal_SetInterrupt(Spi_ConfigPtr->PhyUnitMapPtr[JobCfgPtr->SpiNumber],
                                ESPI_INTC_ALL_ERROR_FLAGS, FALSE);
#else
        (void)Espi_Hal_SetInterrupt(Spi_ConfigPtr->PhyUnitMapPtr[JobCfgPtr->SpiNumber],
                                ESPI_INTC_ALL_ERROR_FLAGS, FALSE);
#endif /* (SPI_SAFETY_ENABLE \== STD_ON) */
    }
    else
#endif  /* (SPI_ENABLE_DMA  \== STD_ON) */
    {
        /* Disable RX and ERROR Interrupt */
#if (SPI_SAFETY_ENABLE == STD_ON)
        RetStatus &= Espi_Hal_SetInterrupt(Spi_ConfigPtr->PhyUnitMapPtr[JobCfgPtr->SpiNumber],
                            (ESPI_INTC_FLAG_RX | ESPI_INTC_ALL_ERROR_FLAGS), FALSE);
#else
        (void)Espi_Hal_SetInterrupt(Spi_ConfigPtr->PhyUnitMapPtr[JobCfgPtr->SpiNumber],
                            (ESPI_INTC_FLAG_RX | ESPI_INTC_ALL_ERROR_FLAGS), FALSE);
#endif /* (SPI_SAFETY_ENABLE \== STD_ON) */
    }
    /*
     The following processing must be performed first: Prevent users from obtaining the job status
     and sending the sequence in the Notification
    */
    /*  SWS_Spi_00292:
        When the function Spi_AsyncTransmit is called, the SPI Handler/Driver shall handle the
        Job results. Result shall be SPI_JOB_OK when the transmission of Jobs is success.
    */
    /* Get Async Sequence status Pointer */
    SeqStatePtr = JobCfgPtr->JobStatePtr->AsyncSeqStatePtr;
    /* Unlink the Job from its sequence */
    JobCfgPtr->JobStatePtr->AsyncSeqStatePtr = NULL_PTR;
    /* Only move to the next Job while Jobs remain in the Sequence. When the last Job is finished
       (RemainingJobs is 0), CurJobIndexPtr already points to the last element of JobIndexListPtr,
       moving and dereferencing it would read beyond the end of the Job list. */
    if (0U != SeqStatePtr->RemainingJobs)
    {
        /* Get the next Job ID to be transferred */
        ++SeqStatePtr->CurJobIndexPtr;
        /* Get the next Job ID */
        NextJob = *(SeqStatePtr->CurJobIndexPtr);
        /* Get Job configuration information structure pointer */
        /* #Violation: Spi_c_REF_1 */
        NextJobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, NextJob);
    }
#if (SPI_CANCEL_API == STD_ON)
    /* Current sequence has been cancelled => unlink the job from its sequence*/
    if ((SPI_SEQ_CANCELLED == SeqStatePtr->SeqResult) ||
                    (SPI_SEQ_FAILED == SeqStatePtr->SeqResult))
#else
    if (SPI_SEQ_FAILED == SeqStatePtr->SeqResult)
#endif /* (SPI_CANCEL_API  \== STD_ON) */
    {
#if (SPI_CANCEL_API == STD_ON)
        if(SPI_SEQ_FAILED == SeqStatePtr->SeqResult)
#endif /* (SPI_CANCEL_API  \== STD_ON) */
        {
            /* Get Job status information, the input parameter is the Job ID */
            /* #Violation: Spi_c_REF_1 */
            SPI_JOB_STATUS(CoreId, Job) = SPI_JOB_FAILED; 
        }
        /* Unlink the Job from current sequence */
        Spi_AsyncUnlockRemainingJobs(CoreId, SeqStatePtr->SeqConfigPtr->SequenceId);
        if (SPI_SEQ_FAILED == SeqStatePtr->SeqResult)
        {
            /* Reset the receive state of the PhyUnit used by the failed Job before it is reused */
            (void)Espi_Hal_FlushRxFifo(Spi_ConfigPtr->PhyUnitMapPtr[JobCfgPtr->SpiNumber]);
            Espi_Hal_ClearFlagStatus(
                Spi_ConfigPtr->PhyUnitMapPtr[JobCfgPtr->SpiNumber], ESPI_ALL_FLAGS_RW_STATES);
        }
        /* Exit asynchronous transmission critical protection */
        SPI_EXIT_CRITICAL_SECTION(AsyncTransmit);
        /*  SWS_Spi_00295:
            The LEVEL 1 SPI Handler/Driver shall offer an asynchronous transfer service for SPI
            buses. Furthermore, the user can be notified at the end of transmission.
            SWS_Spi_00281:
            If Sequences are configured with a specific end notification function, the SPI Handler/
            Driver shall call this notification function at the end of the Sequence transmission.
            SWS_Spi_00120:
            When a valid notification function pointer is configured (see [SWS_Spi_00073]), the SPI
            Handler/Driver shall call this notification function at the end of a Sequence transmission
            regardless of the result of the Sequence transmission being either SPI_SEQ_FAILED, SPI_SEQ_OK
            or SPI_SEQ_CANCELLED (rational: avoid deadlocks or endless loops).
            SWS_Spi_00088:
            For asynchronous levels, LEVEL 1 and LEVEL 2, the SPI Handler/Driver can call end
            notification functions at the end of a Job.
            SWS_Spi_00268:
            For asynchronous levels, LEVEL 1 and LEVEL 2, the SPI Handler/Driver can call end notification
            functions at the end of a Sequence transmission.
            SWS_Spi_00270:
            In case call end notification function and rescheduling are fully done by software,
            the order between these shall be first scheduling and then the call of end notification
            function executed.
            SWS_Spi_00270:
            In case call end notification function and rescheduling are fully done by software,
            the order between these shall be first scheduling and then the call of end notification
            function executed.
            SWS_Spi_00057:
            At the end of a sequence transmission initiated by the function Spi_AsyncTransmit and if
            configured, the SPI Handler/Driver shall invoke the sequence notification call-back function
            after the last Job end notification if this one is also configured.
            SWS_Spi_00145:
            When the sequence is cancelled by the function Spi_Cancel and if configured, the SPI
            Handler/Driver shall call the sequence notification call-back function instead of starting
            a potential next job belonging to it.
            SWS_Spi_00073:
            If the SpiSeqEndNotification is configured (i.e. not a null pointer), the SPI Handler/Driver
            shall call the configured callback notification at the end of a Sequence transmission.
        */
        /* Call Sequence end notification function */
        if (NULL_PTR != SeqStatePtr->SeqConfigPtr->SeqEndNotificationPtr)
        {
            SeqStatePtr->SeqConfigPtr->SeqEndNotificationPtr();
        }
        /* Schedule the next job based on the current job */
        RetStatus &= Spi_AsyncScheduleNextJob(CoreId, Job, FALSE);
        /* The Sequence's teardown, incl. its end notification, is complete: release its
           whole-Sequence PhyUnit reservation */
        Spi_AsyncReleaseSeqPhyUnits(CoreId, SeqStatePtr->SeqConfigPtr);
    }
    /* All jobs in the current sequence have been transferred */
    else if (0U == SeqStatePtr->RemainingJobs)
    {
        /* SWS_Spi_00352:
            Spi_GetSequenceResult function shall return SPI_SEQ_OK when the last
            transmission of the Sequence has been finished successfully.
        */
        SeqStatePtr->SeqResult = SPI_SEQ_OK;
        /* Exit asynchronous transmission critical protection */
        SPI_EXIT_CRITICAL_SECTION(AsyncTransmit);
        /* Call Sequence end notification function */
        if (NULL_PTR != SeqStatePtr->SeqConfigPtr->SeqEndNotificationPtr)
        {
            SeqStatePtr->SeqConfigPtr->SeqEndNotificationPtr();
        }
        /* Schedule the next job based on the current job */
        RetStatus &= Spi_AsyncScheduleNextJob(CoreId, Job, FALSE);
        /* The Sequence's teardown, incl. its end notification, is complete: release its
           whole-Sequence PhyUnit reservation */
        Spi_AsyncReleaseSeqPhyUnits(CoreId, SeqStatePtr->SeqConfigPtr);
    }
    /* The next job uses different hardware than the current job. 
        ==> If the new hardware is SPI_IDLE, send normally.
        ==> If the new hardware is SPI_BUSY, Add to new hardware list. */
    else if (JobCfgPtr->SpiNumber != NextJobCfgPtr->SpiNumber)
    {
        /* Update the remaining job */
        SeqStatePtr->RemainingJobs--;
        /* Exit asynchronous transmission critical protection */
        SPI_EXIT_CRITICAL_SECTION(AsyncTransmit);
        /* schedule the next job on the new ESPI unit */
        RetStatus &= Spi_AsyncScheduleJob(CoreId, NextJob, TRUE);
        /* Schedule the next job based on the current job */
        RetStatus &= Spi_AsyncScheduleNextJob(CoreId, Job, FALSE);
    }
    else
    {
        /* Update the remaining job */
        SeqStatePtr->RemainingJobs--;
        /* Exit asynchronous transmission critical protection */
        SPI_EXIT_CRITICAL_SECTION(AsyncTransmit);
        /* The next Job and the current Job use the same hardware */
#if (SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON)
        /* if the sequence allow interruptible, then schedule the next job */
        /* ESPI is marked as BUSY => New jobs are only put into the list */
        if (TRUE == SeqStatePtr->SeqConfigPtr->Interruptible)
        {
            RetStatus &= Spi_AsyncScheduleJob(CoreId, NextJob, TRUE);
            /* Schedule the next job based on the current job */
            RetStatus &= Spi_AsyncScheduleNextJob(CoreId, Job, FALSE);
        }
        else
#endif /* (SPI_INTERRUPTIBLE_SEQ_ALLOWED  \== STD_ON) */
        /* If the Sequence does not allow interruption, Immediately transfer sequence */
        {
            /* Enter asynchronous transmission critical protection */
            SPI_ENTER_CRITICAL_SECTION(AsyncTransmit);
            /*  SWS_Spi_00145: the Sequence may have been cancelled between the two critical sections,
                then the next Job is not started and the Sequence end notification is called instead */
            if (SPI_SEQ_CANCELLED == SeqStatePtr->SeqResult)
            {
                CancelledSeqCfgPtr = Spi_AsyncReleaseCancelledJob(CoreId, NextJob);
            }
            else
#if (SPI_ENABLE_DMA == STD_ON)
            if(TRUE == SpiPhyUnitStatusPtr->DmaEnable)
            {
                TriggerDmaFlag = Spi_AsyncJobDmaTransfer(CoreId, NextJob);
                NextJobStarted = TriggerDmaFlag;
            }
            else
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */
            {
                /* Job is IDLE,Use Job to transmit data*/
                NextJobStarted = Spi_AsyncJobTransfer(CoreId, NextJob);
            }
            if (FALSE == NextJobStarted)
            {
                /* The next Job can not be started => abort it together with its Sequence */
                AbortedSeqCfgPtr = Spi_AsyncAbortJob(CoreId, NextJob);
            }
            /* Exit asynchronous transmission critical protection */
            SPI_EXIT_CRITICAL_SECTION(AsyncTransmit);
            if (FALSE == NextJobStarted)
            {
                RetStatus = FALSE;
                /* Hand over the released PhyUnit to the scheduler first, then report the aborted Job */
                (void)Spi_AsyncScheduleNextJob(CoreId, NextJob, TRUE);
                Spi_AsyncReportAbortedJob(CoreId, NextJob, AbortedSeqCfgPtr, TRUE);
            }
            if (NULL_PTR != CancelledSeqCfgPtr)
            {
                /* Hand over the released PhyUnit to the scheduler first, then call the Sequence end
                   notification of the cancelled Sequence */
                (void)Spi_AsyncScheduleNextJob(CoreId, NextJob, TRUE);
                Spi_AsyncReportCancelledSeq(CoreId, CancelledSeqCfgPtr);
            }
        }
    }
#if (SPI_ENABLE_DMA == STD_ON)
    if(TRUE == TriggerDmaFlag)
    {
        /* Get PhyUnit configuration information structure pointer */
        /* #Violation: Spi_c_REF_1 */ 
        PhyUnitCfgPtr = SPI_HWUNIT_CONFIGPTR(CoreId, NextJobCfgPtr->SpiNumber);

        /* Enable DMA channel transfer */
        Dma_ChannelStart(PhyUnitCfgPtr->RxDmaChannel);
        Dma_ChannelStart(PhyUnitCfgPtr->TxDmaChannel);
    }
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Spi_AsyncStartScheduledJob
*
*   Service ID              : None.
*
*   Description             : This function starts the transfer of the first scheduled job for
*                             a given HW unit.If the list of scheduled jobs is not empty, pop the
*                             first job and start the transfer. Elsewhere, mark the HW unit as IDLE
*                             If the popped Job can not be started, it is aborted together with its
*                             Sequence and returned to the caller for reporting.
*
*   Parameters in           : CoreId           : Execution Core ID Number.
*                             Job              : Job ID Number, the last Job which used the HW unit.
*                             CheckPhyUnitIdle : TRUE: only start a scheduled Job if the HW unit is
*                                                IDLE, i.e. it has been released by an aborted Job.
*
*   Parameters inout        : None.
*
*   Parameters out          : AbortedJobPtr       : Aborted Job, or Job of a cancelled Sequence which is
*                                                   not started. SPI_JOB_NULL if there is no such Job.
*                             AbortedSeqCfgPtrPtr : Sequence configuration of that Job.
*                             SeqCancelledPtr     : TRUE: the Job is not started because its Sequence
*                                                   has been cancelled. FALSE: the Job is aborted.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non-Reentrant(Same HwUnit).
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2.
*
*   AUTOSAR_Requirement     : SWS_Spi_00269.
****************************************************************************************************/
static FUNC(boolean, SPI_PRIVATE_CODE) Spi_AsyncStartScheduledJob
(
    Mcal_CoreType           CoreId,
    Spi_JobType             Job,
    boolean                 CheckPhyUnitIdle,
    P2VAR(Spi_JobType, AUTOMATIC, SPI_APPL_DATA) AbortedJobPtr,
    P2VAR(P2CONST(Spi_SequenceConfigType, AUTOMATIC, SPI_APPL_CONST), AUTOMATIC, SPI_APPL_DATA) AbortedSeqCfgPtrPtr,
    P2VAR(boolean, AUTOMATIC, SPI_APPL_DATA) SeqCancelledPtr
)
{
    boolean                         RetStatus;
    boolean                         PhyUnitAvailable;
    sint8                           MaxPriority;
    Spi_JobType                     *JobListHeadPtr;
    Spi_PhyUnitStateType            *SpiPhyUnitStatusPtr;
    const Spi_JobConfigType         *JobCfgPtr;
    const Spi_JobConfigType         *NewJobCfgPtr;
#if (SPI_ENABLE_DMA == STD_ON)
    boolean                         TriggerDmaFlag;
    const Spi_PhyUnitConfigType     *PhyUnitCfgPtr;
    
    TriggerDmaFlag = FALSE;
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */
    RetStatus = TRUE;
    /* No Job aborted yet */
    *AbortedJobPtr = SPI_JOB_NULL;
    *AbortedSeqCfgPtrPtr = NULL_PTR;
    *SeqCancelledPtr = FALSE;
    SPI_ENTER_CRITICAL_SECTION(AsyncTransmit);
    /* Get Job configuration information structure pointer */
    /* #Violation: Spi_c_REF_1 */
    JobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, Job); 
    /* Get PhyUnit status information structure pointer */
    /* #Violation: Spi_c_REF_1 */
    SpiPhyUnitStatusPtr = SPI_HWUNIT_STATUSPTR(CoreId, JobCfgPtr->SpiNumber); 
    /*  SWS_Spi_00163:
        For an SPI Handler/Driver operating in LEVEL 1, when there is no on-going Sequence
        transmission, the SPI Handler/Driver shall be in the idle state (SPI_IDLE).
    */
    PhyUnitAvailable = TRUE;
    if ((TRUE == CheckPhyUnitIdle) && (SPI_IDLE != SpiPhyUnitStatusPtr->PhyUnitStatus))
    {
        /* The released PhyUnit has been occupied by another Job in the meantime, the scheduled
           Jobs will be started at the end of that Job */
        PhyUnitAvailable = FALSE;
    }
#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
    if (0U != (*(Spi_CoreStatus[CoreId]->PhyUnitBusySyncStatusPtr) & ((uint16)1U << JobCfgPtr->SpiNumber)))
    {
        /* The PhyUnit is reserved by a synchronous Sequence, the scheduled Jobs will be started at
           the end of that Sequence */
        PhyUnitAvailable = FALSE;
    }
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */
    if (FALSE == PhyUnitAvailable)
    /* #Violation: Spi_c_REF_2 */
    {
        /* The scheduled Jobs are kept in the list */
    }
    /* Current PhyUnit not Job waiting*/
    else if (0 > SpiPhyUnitStatusPtr->MaxScheduledPriority)
    {
        /* no Job waiting => Reset the current PhyUnit to 'SPI_IDLE' */
        SpiPhyUnitStatusPtr->PhyUnitStatus = SPI_IDLE;
#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
        /* Set hardware occupied by asynchronous sequence */
        SpiPhyUnitStatusPtr->IsAsync = FALSE;
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */
    }
    else
    {
        /*  SWS_Spi_00002:
            Jobs have priorities assigned. Jobs linked in a Sequence shall have same or de-creasing
            priorities. That means the first Job shall have the equal priority or the highest
            priority of all Jobs within the Sequence.
            SWS_Spi_00093:
            Priority order of jobs shall be from the lower to the higher value defined, higher value
            higher priority (from 0, the lower to 3, the higher, limited to 4 priority levels see
            [SWS_Spi_00009]).
            SWS_Spi_00059:
            The SPI Handler/Driver scheduling method shall schedule Jobs in order to send the highest
            priority Job first.
        */
        do
        {
            /* Get the priority level of the current hardware being polled */
            MaxPriority = SpiPhyUnitStatusPtr->MaxScheduledPriority;
            /* A job is waiting => Get the Job index in Corex of the current priority level */
            JobListHeadPtr =
                &SpiPhyUnitStatusPtr->ScheduledJobsListHead[((uint8)MaxPriority) & SPI_RANGE_0TO3_MASK];
            /* Get the new Job configuration at the current priority level */
            /* #Violation: Spi_c_REF_1 */
            NewJobCfgPtr = SPI_JOB_CONFIGPTR(CoreId,*JobListHeadPtr); 
            /* Update the new list head at priority x */
            *JobListHeadPtr = NewJobCfgPtr->JobStatePtr->AsyncNextJob;
            /* Check if there is a Next Job bound to the current Job */
            if (SPI_JOB_NULL == *JobListHeadPtr)
            {
                /* Reset the list at the current priority level */
                SpiPhyUnitStatusPtr->ScheduledJobsListTail[((uint8)MaxPriority) & SPI_RANGE_0TO3_MASK] =
                                                                                        SPI_JOB_NULL;
                /* Poll the next priority level to check if there is a job waiting to be transmitted */
                while ((SPI_JOB_NULL == SpiPhyUnitStatusPtr->
                        ScheduledJobsListHead[((uint8)MaxPriority) & SPI_RANGE_0TO3_MASK])
                        && (0 <= MaxPriority))
                {
                    MaxPriority--;
                }
                /* Priority is set on the highest priority queue having scheduled jobs,
                or -1 if no other jobs scheduled */
                SpiPhyUnitStatusPtr->MaxScheduledPriority = MaxPriority;
            }
            /* Exit:Priority > -1 && the polled Job is not CANCEL or FAILED */
        } while ((NULL_PTR == NewJobCfgPtr->JobStatePtr->AsyncSeqStatePtr) && (-1 < MaxPriority));
        /*  SWS_Spi_00145: a valid Job of a cancelled Sequence is not started, the Sequence end
            notification is called instead */
        if ((NULL_PTR != NewJobCfgPtr->JobStatePtr->AsyncSeqStatePtr) &&
            (SPI_SEQ_CANCELLED == NewJobCfgPtr->JobStatePtr->AsyncSeqStatePtr->SeqResult))
        {
            *AbortedJobPtr = NewJobCfgPtr->JobId;
            *AbortedSeqCfgPtrPtr = Spi_AsyncReleaseCancelledJob(CoreId, NewJobCfgPtr->JobId);
            *SeqCancelledPtr = TRUE;
        }
        else
        /* A valid job exists && no timeout */
#if (SPI_ENABLE_DMA == STD_ON)
        if((NULL_PTR != NewJobCfgPtr->JobStatePtr->AsyncSeqStatePtr)
            && (TRUE == SpiPhyUnitStatusPtr->DmaEnable))
        {
            /* Enter the DMA transfer processing branch */
            TriggerDmaFlag = Spi_AsyncJobDmaTransfer(CoreId, NewJobCfgPtr->JobId);
            RetStatus &= TriggerDmaFlag;
        }
        else
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */
        /* A valid job exists && Disable DMA Function */
        if (NULL_PTR != NewJobCfgPtr->JobStatePtr->AsyncSeqStatePtr)
        {
            RetStatus &= Spi_AsyncJobTransfer(CoreId, NewJobCfgPtr->JobId);
        }
        /* No available jobs exist */
        else
        {
            /* no Job waiting => Reset the current PhyUnit to 'SPI_IDLE' */
            SpiPhyUnitStatusPtr->PhyUnitStatus = SPI_IDLE;
#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
            /* The PhyUnit is no longer occupied by an asynchronous sequence */
            SpiPhyUnitStatusPtr->IsAsync = FALSE;
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */
        }
        if (FALSE == RetStatus)
        {
            /* The popped Job can not be started => abort it together with its Sequence */
            *AbortedJobPtr = NewJobCfgPtr->JobId;
            *AbortedSeqCfgPtrPtr = Spi_AsyncAbortJob(CoreId, NewJobCfgPtr->JobId);
        }
    }
    SPI_EXIT_CRITICAL_SECTION(AsyncTransmit);

#if (SPI_ENABLE_DMA == STD_ON)
    if(TRUE == TriggerDmaFlag)
    {
        /* Get PhyUnit configuration information structure pointer */
        /* #Violation: Spi_c_REF_1 */ 
        PhyUnitCfgPtr = SPI_HWUNIT_CONFIGPTR(CoreId, NewJobCfgPtr->SpiNumber);

        /* Enable DMA channel transfer */
        Dma_ChannelStart(PhyUnitCfgPtr->RxDmaChannel);
        Dma_ChannelStart(PhyUnitCfgPtr->TxDmaChannel);
    }
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Spi_AsyncScheduleNextJob
*
*   Service ID              : None.
*
*   Description             : This function hands over a HW unit to the scheduler after a Job has
*                             finished or has been aborted. The scheduled Jobs are tried one after
*                             another until one Job is started or no Job is waiting. Every Job which
*                             can not be started is aborted and reported outside of the critical
*                             section. A Job of a cancelled Sequence is not started and the Sequence
*                             end notification is called instead (SWS_Spi_00145). An aborted or not
*                             started Job leaves the HW unit IDLE, so a Job requested
*                             again from its end notification is started directly (or fails
*                             synchronously) instead of being queued: the loop always terminates.
*
*   Parameters in           : CoreId          : Execution Core ID Number.
*                             Job             : Job ID Number, the last Job which used the HW unit.
*                             PhyUnitReleased : FALSE: the HW unit is still occupied by Job.
*                                               TRUE: Job has been aborted and the HW unit has been
*                                               released, it is only scheduled if it is still IDLE.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non-Reentrant(Same HwUnit).
*
*   Return value            : TRUE: No scheduled Job has been aborted.
*                             FALSE: At least one scheduled Job has been aborted.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2.
*                             Shall be called outside of the AsyncTransmit critical section.
*
*   AUTOSAR_Requirement     : SWS_Spi_00269 SWS_Spi_00119 SWS_Spi_00120.
****************************************************************************************************/
static FUNC(boolean, SPI_PRIVATE_CODE) Spi_AsyncScheduleNextJob
(
    Mcal_CoreType           CoreId,
    Spi_JobType             Job,
    boolean                 PhyUnitReleased
)
{
    boolean                         RetStatus;
    boolean                         CheckPhyUnitIdle;
    boolean                         SeqCancelled;
    Spi_JobType                     AbortedJob;
    const Spi_SequenceConfigType    *AbortedSeqCfgPtr;

    RetStatus = TRUE;
    /* Only a released HW unit has to be checked for IDLE before a scheduled Job is started */
    CheckPhyUnitIdle = PhyUnitReleased;
    do
    {
        /* Try to start the next scheduled Job on the HW unit */
        RetStatus &= Spi_AsyncStartScheduledJob(CoreId, Job, CheckPhyUnitIdle,
                                                &AbortedJob, &AbortedSeqCfgPtr, &SeqCancelled);
        if ((SPI_JOB_NULL != AbortedJob) && (TRUE == SeqCancelled))
        {
            /* Call the Sequence end notification of the cancelled Sequence outside of the critical
               section */
            Spi_AsyncReportCancelledSeq(CoreId, AbortedSeqCfgPtr);
        }
        else if (SPI_JOB_NULL != AbortedJob)
        {
            /* Report the aborted Job outside of the critical section */
            Spi_AsyncReportAbortedJob(CoreId, AbortedJob, AbortedSeqCfgPtr, TRUE);
        }
        else
        /* #Violation: Spi_c_REF_2 */
        {
            /* A scheduled Job has been started or no Job is waiting */
        }
        /* The HW unit has been released by the aborted or not started Job and may have been occupied
           by a Job requested again in its end notification */
        CheckPhyUnitIdle = TRUE;
    } while (SPI_JOB_NULL != AbortedJob);

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Spi_AsyncIsrFifoRx
*
*   Service ID              : None
*
*   Description             : This function is called by RXF ISR for the ESPI units
*
*   Parameters in           : CoreId    : Execution Core ID Number.
*                             PhyUnit    : Hardware ID Number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non-Reentrant(Same HwUnit).
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, SPI_PRIVATE_CODE) Spi_AsyncIsrFifoRx
(
    Mcal_CoreType           CoreId,
    Spi_HWUnitType          PhyUnit
)
{
    boolean                                 RetStatus;
    boolean                                 IsJobRunning;
    uint32                                  RxBufIndex;
    uint32                                  TempRxBuffer;
    uint32                                  IsPollRequest;
    const Spi_PhyUnitStateType              *SpiPhyUnitStatusPtr;
    Spi_DeviceStateType                     *DevStatePtr;
    const Spi_JobConfigType                 *JobCfgPtr;
    const Spi_ChannelConfigType             *ChannelCfgPtr;
    const Spi_SequenceConfigType            *AbortedSeqCfgPtr;

    RetStatus = TRUE;
    AbortedSeqCfgPtr = NULL_PTR;
    /* Get external status information structure pointer */
    /* #Violation: Spi_c_REF_1 */
    DevStatePtr = SPI_EXD_STATUSPTR(CoreId, PhyUnit);
    /* Get PhyUnit status information structure pointer */
    /* #Violation: Spi_c_REF_1 */
    SpiPhyUnitStatusPtr = SPI_HWUNIT_STATUSPTR(CoreId, PhyUnit);
    /* Enter asynchronous transmission critical protection */
    SPI_ENTER_CRITICAL_SECTION(AsyncTransmit);
    /*  A spurious or late receive interrupt shall not touch the device state: the Job may have been
        finished, aborted or replaced since the interrupt was raised, and the device state of a HW
        unit which has never been used asynchronously is not initialized. The state is only
        consistent while an asynchronous Job is running on the HW unit, the abort has not been
        claimed, a FIFO round is outstanding and the receive request is still pending.
    */
    IsJobRunning = FALSE;
    /* Get the Spi Job configuration parameters */
    JobCfgPtr = DevStatePtr->CurJobPtr;
    IsPollRequest = Espi_Hal_GetFlagStatus(Spi_ConfigPtr->PhyUnitMapPtr[PhyUnit], ESPI_INTC_FLAG_RX);
    if ((SPI_BUSY == SpiPhyUnitStatusPtr->PhyUnitStatus) &&
#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
        (TRUE == SpiPhyUnitStatusPtr->IsAsync) &&
        (0U == (*(Spi_CoreStatus[CoreId]->PhyUnitBusySyncStatusPtr) & ((uint16)1U << PhyUnit))) &&
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */
        (NULL_PTR != JobCfgPtr) &&
        (SPI_JOB_PENDING == JobCfgPtr->JobStatePtr->JobResult) &&
        (0U != DevStatePtr->SentFrames) &&
        (0U != IsPollRequest))
    {
        IsJobRunning = TRUE;
    }
    if (FALSE == IsJobRunning)
    {
        /* Exit asynchronous transmission critical protection */
        SPI_EXIT_CRITICAL_SECTION(AsyncTransmit);
        return TRUE;
    }
    /* Get Channel configuration information structure pointer */
    /* #Violation: Spi_c_REF_1 */
    ChannelCfgPtr = SPI_CH_CONFIGPTR(CoreId, *(DevStatePtr->CurChannelIndexPtr));
    /* Reset current RxBuffer Index */
    RxBufIndex = (((uint32)*(ChannelCfgPtr->ActualDataLengthPtr) - (uint32)DevStatePtr->ReceivedData) *
                    (uint32)DevStatePtr->SentFramesWidth);
    /* Update the length of the received data: The following statements must precede the while */
    DevStatePtr->ReceivedData -= DevStatePtr->SentFrames;
    /* Loop to receive data */
    /*  SWS_Spi_00036:
        When the function Spi_AsyncTransmit is used with EB and the destination data pointer has been
        provided as NULL using the Spi_SetupEB method, the SPI Handler/Driver shall ignore receiving
        data. See also [SWS_Spi_00030]
        SWS_Spi_00028:
        When the function Spi_SetupEB is called with the parameter DesDataBufferPtr being a Null
        pointer, the SPI Handler/Driver shall ignore the received data after a Transmit method is
        requested.See also [SWS_Spi_00036]
    */
    while (0U < DevStatePtr->SentFrames)
    {
        /*  SWS_Spi_00437:
            Data buffers are accessed as uint8, uint16 or uint32 according to SpiDataWidth
            independently to Spi_DataBufferType.
        */
        if(NULL_PTR == DevStatePtr->CurRxBufPtr)
        {
            (void)Espi_Hal_ReceiveData(Spi_ConfigPtr->PhyUnitMapPtr[JobCfgPtr->
                            SpiNumber], (uint8 *)&TempRxBuffer, DevStatePtr->SentFramesWidth);
        }
        else
        {
            /* Receive data */
            RxBufIndex += Espi_Hal_ReceiveData(Spi_ConfigPtr->PhyUnitMapPtr[JobCfgPtr->
                            SpiNumber], &(DevStatePtr->CurRxBufPtr[RxBufIndex]), DevStatePtr->SentFramesWidth);
        }
        DevStatePtr->SentFrames--;
    }
    /* Clear RX status flags */
    Espi_Hal_ClearFlagStatus(
        Spi_ConfigPtr->PhyUnitMapPtr[JobCfgPtr->SpiNumber], ESPI_INTC_FLAG_RX);
    /* Check whether it is the last channel in current job */
    if ((boolean)FALSE == DevStatePtr->IsEndOfJob)
    {
        /* The current channel is sent and there is still more than one channel to be sent */
        if ((0U == DevStatePtr->ReceivedData) && (0U != DevStatePtr->RemainingChannels))
        {
            /* Reached the end of channel => move to the next channel */
            DevStatePtr->RemainingChannels--;
            /* Increase Channel indexes */
            DevStatePtr->CurChannelIndexPtr++;
            /* Send data & Config Channel */
            RetStatus &= Spi_AsyncJobTransferChannel(CoreId, PhyUnit, TRUE);
        }
        else
        {
            RetStatus &= Spi_AsyncJobTransferChannel(CoreId, PhyUnit, FALSE);
        }
        if (FALSE == RetStatus)
        {
            /* The next frames can not be sent => abort the Job together with its Sequence */
            AbortedSeqCfgPtr = Spi_AsyncAbortJob(CoreId, JobCfgPtr->JobId);
        }
        /* Exit asynchronous transmission critical protection */
        SPI_EXIT_CRITICAL_SECTION(AsyncTransmit);
        if (FALSE == RetStatus)
        {
            /* Hand over the released PhyUnit to the scheduler first, then report the aborted Job */
            (void)Spi_AsyncScheduleNextJob(CoreId, JobCfgPtr->JobId, TRUE);
            Spi_AsyncReportAbortedJob(CoreId, JobCfgPtr->JobId, AbortedSeqCfgPtr, TRUE);
        }
    }
    else
    {
        /* Exit asynchronous transmission critical protection */
        SPI_EXIT_CRITICAL_SECTION(AsyncTransmit);
        /* No data to receive && Channel transmission completed in current Job.
            Indicates that all Channel transmissions in the Job are completed. */
        /* The current Job transfer is completed */
        RetStatus &= Spi_AsyncJobTransferFinished(CoreId, JobCfgPtr->JobId);
    }
#if (SPI_DEM_REPORT_ERROR_STATUS == STD_ON)
    /*  SWS_Spi_00267:
        When a hardware error is detected, the SPI Handler/Driver shall stop the current
        sequence, report an error to the DEM as configured and set the state of the Job to
        SPI_JOB_FAILED and the state of the Sequence to SPI_SEQ_FAILED.
        SWS_Spi_00386:
        When no error bit inside the SPI transmit status register is set, the SPI transmit
        status register information shall be reported to DEM as Dem_SetEventStatus
        (SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_PASSED)
        SWS_Spi_00195:
        SPI Handler/driver shall be able to detect the error SPI_E_HARDWARE_ERROR when an hardware
        error occur during asynchronous or synchronous transmit. Please see also SWS_Spi_00267 and
        SWS_Spi_00384.
    */
    if (TRUE == RetStatus)
    {
        /* Report DEM status - no hardware error occurred */
        Dem_SetEventStatus(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_PASSED);
    }
#endif /* (SPI_DEM_REPORT_ERROR_STATUS  \== STD_ON) */

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Spi_AsyncUnlockRemainingJobs
*
*   Service ID              : None.
*
*   Description             : This function is called to release the jobs at the end of an async
*                             sequence transmission, Mark the linked sequence for all jobs as NULL_PTR
*
*   Parameters in           : CoreId    : Execution Core ID Number.
*                             Sequence  : SequenceID Number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non-Reentrant(Same HwUnit).
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2
*                             and SPI_CANCEL_API shall be STD_ON.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, SPI_PRIVATE_CODE) Spi_AsyncUnlockRemainingJobs
(
    Mcal_CoreType           CoreId,
    Spi_SequenceType        Sequence
)
{
    Spi_JobType                     JobIdx;
    Spi_JobType                     NumJobsInSeq;
    const Spi_SequenceStateType     *SeqStatusPtr;
    const Spi_JobConfigType         *JobCfgPtr;
    const Spi_SequenceConfigType    *SeqCfgPtr;

    /* Get Sequence configuration information structure pointer */
    /* #Violation: Spi_c_REF_1 */
    SeqCfgPtr = SPI_SEQ_CONFIGPTR(CoreId, Sequence); 
    /* Get Sequence status information structure pointer */
    /* #Violation: Spi_c_REF_1 */
    SeqStatusPtr = SPI_SEQ_STATUSPTR(CoreId, Sequence); 
    /* Get total Job number in Sequence */
    NumJobsInSeq = SeqCfgPtr->NumJobs - SeqStatusPtr->RemainingJobs;
    /* unlink the remaining job from its sequence*/
    for (JobIdx = NumJobsInSeq; JobIdx < SeqCfgPtr->NumJobs; JobIdx++)
    {
        /* Get Job configuration information structure pointer */
        /* #Violation: Spi_c_REF_1 */
        JobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, SeqCfgPtr->JobIndexListPtr[JobIdx]); 
        /* unlink the job from its sequence */
        JobCfgPtr->JobStatePtr->AsyncSeqStatePtr = NULL_PTR;
        /* If the Sequence is CANCEL, Reset the Job status to SPI_JOB_OK */
        /* #Violation: Spi_c_REF_1 */
        if(SPI_SEQ_CANCELLED == SPI_SEQ_STATUS(CoreId, Sequence)) 
        {
            /* Reset the job status to SPI_JOB_OK */
            JobCfgPtr->JobStatePtr->JobResult = SPI_JOB_OK;
        }
        else
        {
            /* Reset the job status to SPI_JOB_FAILED */
            JobCfgPtr->JobStatePtr->JobResult = SPI_JOB_FAILED;
        }
        /* The PhyUnit of a remaining Job is not reset here: the Job has not been started yet and
           its PhyUnit may be in use by a Job of another Sequence */
    }
}

/****************************************************************************************************
*   Function Name           : Spi_AsyncReleaseSeqPhyUnits
*
*   Service ID              : None.
*
*   Description             : Releases the whole-Sequence PhyUnit reservation taken by
*                             Spi_AsyncTransmit in PhyUnitPendingTeardownStatusPtr. Called once a
*                             Sequence has truly finished, i.e. after its end notification has been
*                             called, so that busy-detection (Spi_GetDriverStatus,
*                             Spi_SyncCheckPhyUnitsFree) is never fooled by a gap where PhyUnitStatus
*                             or PhyUnitBusySyncStatusPtr already look idle/free while this
*                             Sequence's teardown is still in progress.
*
*   Parameters in           : CoreId    : Execution Core ID Number.
*                             SeqCfgPtr : Configuration of the finished Sequence.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2.
*                             Shall be called outside of every critical section.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, SPI_PRIVATE_CODE) Spi_AsyncReleaseSeqPhyUnits
(
    Mcal_CoreType                                               CoreId,
    P2CONST(Spi_SequenceConfigType, AUTOMATIC, SPI_APPL_CONST)  SeqCfgPtr
)
{
    Spi_JobType                     JobIdx;
    const Spi_JobConfigType         *JobCfgPtr;

    /* Enter asynchronous transmission critical protection */
    SPI_ENTER_CRITICAL_SECTION(AsyncTransmit);
    for (JobIdx = 0U; JobIdx < SeqCfgPtr->NumJobs; JobIdx++)
    {
        /* Get Job configuration information structure pointer */
        /* #Violation: Spi_c_REF_1 */
        JobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, SeqCfgPtr->JobIndexListPtr[JobIdx]);
        *(Spi_CoreStatus[CoreId]->PhyUnitPendingTeardownStatusPtr) &=
                                    (~((uint16)1U << JobCfgPtr->SpiNumber));
    }
    /* Exit asynchronous transmission critical protection */
    SPI_EXIT_CRITICAL_SECTION(AsyncTransmit);
}

/****************************************************************************************************
*   Function Name           : Spi_AsyncAbortJob
*
*   Service ID              : None.
*
*   Description             : This function aborts an asynchronous Job which can not be started or
*                             continued, and brings the Job, its Sequence and the HW unit into a
*                             deterministic state:
*                             - RX and error interrupts and DMA of the HW unit are disabled, the
*                               status flags are cleared and the HW unit is reset. This is done
*                               best effort, the register read back results are ignored;
*                             - a chip select via GPIO is set to its inactive level;
*                             - the Job result is set to SPI_JOB_FAILED, the Sequence result is set
*                               to SPI_SEQ_FAILED (a cancelled Sequence keeps SPI_SEQ_CANCELLED),
*                               the Job and the remaining Jobs of the Sequence are unlinked;
*                             - the HW unit is set to SPI_IDLE, so that a Job requested again from
*                               an end notification is started directly instead of being queued.
*                             The end notifications are not called here, see
*                             Spi_AsyncReportAbortedJob.
*
*   Parameters in           : CoreId    : Execution Core ID Number.
*                             Job       : Job ID Number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non-Reentrant(Same HwUnit).
*
*   Return value            : Configuration of the Sequence the Job was linked to, NULL_PTR if the
*                             Job was not linked to a Sequence.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2.
*                             Shall be called inside of the AsyncTransmit critical section, which
*                             can not be nested.
*
*   AUTOSAR_Requirement     : SWS_Spi_00254 SWS_Spi_00267.
****************************************************************************************************/
static FUNC_P2CONST(Spi_SequenceConfigType, SPI_APPL_CONST, SPI_PRIVATE_CODE) Spi_AsyncAbortJob
(
    Mcal_CoreType           CoreId,
    Spi_JobType             Job
)
{
    ESPI_MODULE                         *PhyUnitPtr;
    Spi_PhyUnitStateType                *SpiPhyUnitStatusPtr;
    Spi_SequenceStateType               *SeqStatePtr;
    const Spi_SequenceConfigType        *SeqCfgPtr;
    const Spi_JobConfigType             *JobCfgPtr;
#if (SPI_CUSTOMIZED_CS_EN == STD_ON)
    const Spi_ExternalDeviceConfigType  *ExDeviceCfgPtr;
#endif /* (SPI_CUSTOMIZED_CS_EN \== STD_ON) */

    SeqCfgPtr = NULL_PTR;
    /* Get Job configuration information structure pointer */
    /* #Violation: Spi_c_REF_1 */
    JobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, Job);
    /* Get hardware unit address */
    PhyUnitPtr = Spi_ConfigPtr->PhyUnitMapPtr[JobCfgPtr->SpiNumber];
    /* Stop the HW unit. The read back results are ignored, as the HW unit is being recovered */
    (void)Espi_Hal_SetInterrupt(PhyUnitPtr, (ESPI_INTC_FLAG_RX | ESPI_INTC_ALL_ERROR_FLAGS), FALSE);
    (void)Espi_Hal_SetDma(PhyUnitPtr, FALSE);
    /* Flush the receive FIFO and clear the status flags before the HW unit is reused */
    (void)Espi_Hal_FlushRxFifo(PhyUnitPtr);
    Espi_Hal_ClearFlagStatus(PhyUnitPtr, ESPI_ALL_FLAGS_RW_STATES);
#if (SPI_CUSTOMIZED_CS_EN == STD_ON)
    /* Get external device configuration information structure pointer */
    /* #Violation: Spi_c_REF_1 */
    ExDeviceCfgPtr = SPI_EXD_CONFIGPTR(CoreId, JobCfgPtr->ExDeviceUnit);
    if (SPI_CS_VIA_GPIO == ExDeviceCfgPtr->CsSelection)
    {
        /* Release the chip select. The inactive level is written, as it is unknown whether the
           chip select has already been toggled to its active level before the failure */
        Dio_WriteChannel(ExDeviceCfgPtr->GpioPortPin,
            ((uint8)ExDeviceCfgPtr->Spi_ExDeviceCfgInfoPtr->slsoActiveLevel) ^ 1U);
    }
#endif /* (SPI_CUSTOMIZED_CS_EN \== STD_ON) */
    /*  SWS_Spi_00267:
        When a hardware error is detected, the SPI Handler/Driver shall stop the current
        sequence, report an error to the DEM as configured and set the state of the Job to
        SPI_JOB_FAILED and the state of the Sequence to SPI_SEQ_FAILED.
    */
    JobCfgPtr->JobStatePtr->JobResult = SPI_JOB_FAILED;
    /* Get Async Sequence status Pointer */
    SeqStatePtr = JobCfgPtr->JobStatePtr->AsyncSeqStatePtr;
    /* Unlink the Job from its sequence */
    JobCfgPtr->JobStatePtr->AsyncSeqStatePtr = NULL_PTR;
    if (NULL_PTR != SeqStatePtr)
    {
        /* A cancelled Sequence keeps its result */
        if (SPI_SEQ_CANCELLED != SeqStatePtr->SeqResult)
        {
            SeqStatePtr->SeqResult = SPI_SEQ_FAILED;
        }
        SeqCfgPtr = SeqStatePtr->SeqConfigPtr;
        /* Unlink the remaining Jobs of the Sequence */
        Spi_AsyncUnlockRemainingJobs(CoreId, SeqCfgPtr->SequenceId);
    }
    /* Get PhyUnit status information structure pointer */
    /* #Violation: Spi_c_REF_1 */
    SpiPhyUnitStatusPtr = SPI_HWUNIT_STATUSPTR(CoreId, JobCfgPtr->SpiNumber);
    /* Release the HW unit */
    SpiPhyUnitStatusPtr->PhyUnitStatus = SPI_IDLE;
#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
    /* The HW unit is no longer occupied by an asynchronous sequence */
    SpiPhyUnitStatusPtr->IsAsync = FALSE;
    /* The hardware unit is no longer supervised */
    /* #Violation: Spi_c_REF_1 */
    SPI_EXD_STATUSPTR(CoreId, JobCfgPtr->SpiNumber)->AsyncDeadline = 0ULL;
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */

    return SeqCfgPtr;
}

/****************************************************************************************************
*   Function Name           : Spi_AsyncReportAbortedJob
*
*   Service ID              : None.
*
*   Description             : This function reports a Job aborted by Spi_AsyncAbortJob: the DEM
*                             event is reported if configured and, if requested, the Job end
*                             notification and the Sequence end notification are called.
*
*   Parameters in           : CoreId           : Execution Core ID Number.
*                             Job              : Aborted Job ID Number.
*                             SeqCfgPtr        : Configuration of the aborted Sequence, NULL_PTR if
*                                                the Job was not linked to a Sequence.
*                             CallNotification : TRUE: call the end notifications.
*                                                FALSE: the abort is reported synchronously to the
*                                                caller of Spi_AsyncTransmit via E_NOT_OK. No
*                                                notification is called, so that a request repeated
*                                                in a notification can not recurse endlessly.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2.
*                             Shall be called outside of the AsyncTransmit critical section.
*
*   AUTOSAR_Requirement     : SWS_Spi_00119 SWS_Spi_00120 SWS_Spi_00057 SWS_Spi_00267.
****************************************************************************************************/
static FUNC(void, SPI_PRIVATE_CODE) Spi_AsyncReportAbortedJob
(
    Mcal_CoreType           CoreId,
    Spi_JobType             Job,
    P2CONST(Spi_SequenceConfigType, AUTOMATIC, SPI_APPL_CONST) SeqCfgPtr,
    boolean                 CallNotification
)
{
    const Spi_JobConfigType         *JobCfgPtr;

#if (SPI_DEM_REPORT_ERROR_STATUS == STD_ON)
    /*  SWS_Spi_00385:
        When any error bit inside the SPI transmit status register is set, the SPI transmit
        status register information shall be reported to DEM as Dem_SetEventStatus
        (SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED)
    */
    /* Report DEM error - hardware error occurred */
    Dem_SetEventStatus(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif /* (SPI_DEM_REPORT_ERROR_STATUS  \== STD_ON) */
    if (TRUE == CallNotification)
    {
        /* Get Job configuration information structure pointer */
        /* #Violation: Spi_c_REF_1 */
        JobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, Job);
        /*  SWS_Spi_00119:
            When a valid notification function pointer is configured, the SPI Handler/Driver shall
            call this notification function at the end of a Job transmission regardless of the
            result of the Job transmission being either SPI_JOB_FAILED or SPI_JOB_OK.
        */
        if (NULL_PTR != JobCfgPtr->JobEndNotificationPtr)
        {
            JobCfgPtr->JobEndNotificationPtr();
        }
        /*  SWS_Spi_00120 / SWS_Spi_00057:
            The Sequence end notification is called regardless of the result of the Sequence,
            after the last Job end notification.
        */
        if ((NULL_PTR != SeqCfgPtr) && (NULL_PTR != SeqCfgPtr->SeqEndNotificationPtr))
        {
            SeqCfgPtr->SeqEndNotificationPtr();
        }
    }
    /* The Sequence's teardown is complete regardless of CallNotification: when FALSE, the
       abort is reported synchronously and no notification is ever called for it. Release
       its whole-Sequence PhyUnit reservation, if the aborted Job was linked to one. */
    if (NULL_PTR != SeqCfgPtr)
    {
        Spi_AsyncReleaseSeqPhyUnits(CoreId, SeqCfgPtr);
    }
}

/****************************************************************************************************
*   Function Name           : Spi_AsyncAbortRunningJob
*
*   Service ID              : None.
*
*   Description             : This function aborts the asynchronous Job which is currently running on
*                             a HW unit, when the transfer can not be continued: a hardware error, a
*                             DMA error or a supervision timeout. The first caller which sees a
*                             running asynchronous Job claims the abort by setting the Job result from
*                             SPI_JOB_PENDING to SPI_JOB_FAILED inside the AsyncTransmit critical
*                             section. Only that caller aborts the Job, schedules the HW unit and
*                             calls the end notifications: every other caller and the normal
*                             completion path return without doing anything.
*                             The abort is done in three steps, because the critical sections can not
*                             be nested and a DMA service enters its own one:
*                             - the claim disables the RX and ERROR interrupts and the DMA requests of
*                               the HW unit, which is left SPI_BUSY so that no other Job is started on
*                               it and no synchronous Sequence reserves it while its DMA channels are
*                               still being cancelled;
*                             - both DMA channels are cancelled outside of the critical section;
*                             - Spi_AsyncAbortJob brings the Job, its Sequence and the HW unit into a
*                               deterministic state and releases the HW unit.
*                             The HW unit is then handed over to the scheduler and the aborted Job is
*                             reported (SWS_Spi_00270: scheduling before end notification).
*
*   Parameters in           : CoreId        : Execution Core ID Number.
*                             PhyUnit       : Hardware ID Number.
*                             CheckDeadline : TRUE: the Job is only aborted if the supervision
*                                             deadline of the HW unit has been passed, re-checked
*                                             inside the critical section.
*                                             FALSE: the running Job is aborted unconditionally.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non-Reentrant(Same HwUnit).
*
*   Return value            : TRUE: the Job has been claimed and aborted by this call.
*                             FALSE: no asynchronous Job is running on the HW unit, the deadline has
*                             not been passed, or the Job has already been claimed.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2.
*                             Shall be called outside of every critical section.
*
*   AUTOSAR_Requirement     : SWS_Spi_00254 SWS_Spi_00267 SWS_Spi_00270.
****************************************************************************************************/
static FUNC(boolean, SPI_PRIVATE_CODE) Spi_AsyncAbortRunningJob
(
    Mcal_CoreType           CoreId,
    Spi_HWUnitType          PhyUnit,
    boolean                 CheckDeadline
)
{
    boolean                             Claimed;
    Spi_JobType                         Job;
    ESPI_MODULE                         *PhyUnitPtr;
    const Spi_DeviceStateType           *DevStatePtr;
    const Spi_JobConfigType             *JobCfgPtr;
    const Spi_PhyUnitStateType          *SpiPhyUnitStatusPtr;
    const Spi_SequenceConfigType        *AbortedSeqCfgPtr;
#if (SPI_ENABLE_DMA == STD_ON)
    boolean                             IsDmaTransfer;
    uint32                              DmaChannelStatus;
    const Spi_PhyUnitConfigType         *PhyUnitCfgPtr;
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */
#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
    uint64                              TimerCount;
    boolean                             DeadlineReached;
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */

#if (SPI_LEVEL_DELIVERED != SPI_LEVEL2)
    /* #Violation: Spi_c_REF_1 */
    MCAL_UNUSED_VAR(CheckDeadline);
#endif /* (SPI_LEVEL_DELIVERED \!= SPI_LEVEL2) */
#if (SPI_ENABLE_DMA == STD_ON)
    IsDmaTransfer = FALSE;
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */
    Claimed = FALSE;
    Job = SPI_JOB_NULL;
    AbortedSeqCfgPtr = NULL_PTR;
    /* Get hardware unit address */
    PhyUnitPtr = Spi_ConfigPtr->PhyUnitMapPtr[PhyUnit];
    /* Get external status information structure pointer */
    /* #Violation: Spi_c_REF_1 */
    DevStatePtr = SPI_EXD_STATUSPTR(CoreId, PhyUnit);
    /* Get PhyUnit status information structure pointer */
    /* #Violation: Spi_c_REF_1 */
    SpiPhyUnitStatusPtr = SPI_HWUNIT_STATUSPTR(CoreId, PhyUnit);
    /*  Claim the abort: only the first caller which sees an asynchronous Job running on the HW unit
        owns it, every later caller and the normal completion path see a Job result which is no
        longer SPI_JOB_PENDING */
    /* Enter asynchronous transmission critical protection */
    SPI_ENTER_CRITICAL_SECTION(AsyncTransmit);
    JobCfgPtr = DevStatePtr->CurJobPtr;
#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
    /*  A supervision timeout is re-validated with the interrupts disabled: a Job which has made
        progress, or which has been finished and started again, has stamped a fresh deadline and is
        not aborted. The timer is read into a local, so that the condition has no side effect */
    DeadlineReached = FALSE;
    /* #Violation: Spi_c_REF_1 */
    TimerCount = Mcal_GetSystemTimerCount();
    if ((0ULL != DevStatePtr->AsyncDeadline) &&
        (SPI_TIMEOUT_TIMER_HALFRANGE < (DevStatePtr->AsyncDeadline - TimerCount)))
    {
        DeadlineReached = TRUE;
    }
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */
    if ((SPI_BUSY == SpiPhyUnitStatusPtr->PhyUnitStatus) &&
#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
        (TRUE == SpiPhyUnitStatusPtr->IsAsync) &&
        (0U == (*(Spi_CoreStatus[CoreId]->PhyUnitBusySyncStatusPtr) & ((uint16)1U << PhyUnit))) &&
        ((FALSE == CheckDeadline) || (TRUE == DeadlineReached)) &&
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */
        (NULL_PTR != JobCfgPtr) &&
        (SPI_JOB_PENDING == JobCfgPtr->JobStatePtr->JobResult))
    {
        /* Take the claim: no other context aborts or finishes this Job any more */
        JobCfgPtr->JobStatePtr->JobResult = SPI_JOB_FAILED;
        Job = JobCfgPtr->JobId;
        Claimed = TRUE;
        /*  Stop the sources of further interrupts and DMA requests before the DMA channels are
            cancelled. The read back results are ignored, the HW unit is being recovered */
        (void)Espi_Hal_SetInterrupt(PhyUnitPtr,
                                    (ESPI_INTC_FLAG_RX | ESPI_INTC_ALL_ERROR_FLAGS), FALSE);
        (void)Espi_Hal_SetDma(PhyUnitPtr, FALSE);
#if (SPI_ENABLE_DMA == STD_ON)
        IsDmaTransfer = SpiPhyUnitStatusPtr->DmaEnable;
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */
    }
    /*  The HW unit is left SPI_BUSY here on purpose: no Job shall be started on it and no
        synchronous Sequence shall reserve it while its DMA channels are still being cancelled */
    /* Exit asynchronous transmission critical protection */
    SPI_EXIT_CRITICAL_SECTION(AsyncTransmit);
#if (SPI_ENABLE_DMA == STD_ON)
    if (TRUE == IsDmaTransfer)
    {
        /*  Cancel both DMA channels of the HW unit outside of every SPI critical section:
            Dma_GetChannelStatus and Dma_ChannelCancel enter their own one. A channel which reports
            no event was never started or is already stopped, cancelling it would be reported as
            DMA_E_CHANNEL_IDLE; a channel which reports DMA_CH_ERROR has already been disabled by
            Dma_GetChannelStatus. DMA_CH_CANCEL_DIRECT is used, DMA_CH_CANCEL_SAFE polls the channel
            with all interrupts disabled. The TX channel feeds the ESPI and is stopped first */
        /* #Violation: Spi_c_REF_1 */
        PhyUnitCfgPtr = SPI_HWUNIT_CONFIGPTR(CoreId, PhyUnit);
        DmaChannelStatus = Dma_GetChannelStatus(PhyUnitCfgPtr->TxDmaChannel);
        if (((uint32)DMA_CH_NONE != DmaChannelStatus) &&
            ((uint32)0U == (DmaChannelStatus & (uint32)DMA_CH_ERROR)))
        {
            Dma_ChannelCancel(PhyUnitCfgPtr->TxDmaChannel, DMA_CH_CANCEL_DIRECT);
        }
        DmaChannelStatus = Dma_GetChannelStatus(PhyUnitCfgPtr->RxDmaChannel);
        if (((uint32)DMA_CH_NONE != DmaChannelStatus) &&
            ((uint32)0U == (DmaChannelStatus & (uint32)DMA_CH_ERROR)))
        {
            Dma_ChannelCancel(PhyUnitCfgPtr->RxDmaChannel, DMA_CH_CANCEL_DIRECT);
        }
    }
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */
    if (TRUE == Claimed)
    {
        /*  Bring the Job, its Sequence and the HW unit into a deterministic state. The receive FIFO
            is flushed there, after both DMA engines have been stopped */
        /* Enter asynchronous transmission critical protection */
        SPI_ENTER_CRITICAL_SECTION(AsyncTransmit);
        AbortedSeqCfgPtr = Spi_AsyncAbortJob(CoreId, Job);
        /* Exit asynchronous transmission critical protection */
        SPI_EXIT_CRITICAL_SECTION(AsyncTransmit);
        /*  Hand over the released PhyUnit to the scheduler first, then report the aborted Job
            (SWS_Spi_00270: scheduling before end notification) */
        (void)Spi_AsyncScheduleNextJob(CoreId, Job, TRUE);
        Spi_AsyncReportAbortedJob(CoreId, Job, AbortedSeqCfgPtr, TRUE);
    }

    return Claimed;
}

/****************************************************************************************************
*   Function Name           : Spi_AsyncReleaseCancelledJob
*
*   Service ID              : None.
*
*   Description             : This function releases a Job of a cancelled Sequence which has not been
*                             started yet, so that it is not started any more (SWS_Spi_00145):
*                             - the Job result is reset to SPI_JOB_OK, the same as for the remaining
*                               Jobs of a cancelled Sequence in Spi_AsyncUnlockRemainingJobs;
*                             - the Job and the remaining Jobs of the Sequence are unlinked;
*                             - the HW unit is set to SPI_IDLE, so that a Sequence requested again from
*                               the Sequence end notification is started directly.
*                             The HW unit registers are not touched, as the Job has not been started.
*                             The Sequence end notification is not called here, see
*                             Spi_AsyncReportCancelledSeq.
*
*   Parameters in           : CoreId    : Execution Core ID Number.
*                             Job       : Job ID Number, the Job shall be linked to its Sequence.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non-Reentrant(Same HwUnit).
*
*   Return value            : Configuration of the cancelled Sequence.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2.
*                             Shall be called inside of the AsyncTransmit critical section, while no
*                             Job is transmitted on the HW unit of the Job.
*
*   AUTOSAR_Requirement     : SWS_Spi_00145.
****************************************************************************************************/
static FUNC_P2CONST(Spi_SequenceConfigType, SPI_APPL_CONST, SPI_PRIVATE_CODE) Spi_AsyncReleaseCancelledJob
(
    Mcal_CoreType           CoreId,
    Spi_JobType             Job
)
{
    Spi_PhyUnitStateType                *SpiPhyUnitStatusPtr;
    const Spi_SequenceStateType         *SeqStatePtr;
    const Spi_JobConfigType             *JobCfgPtr;

    /* Get Job configuration information structure pointer */
    /* #Violation: Spi_c_REF_1 */
    JobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, Job);
    /* Get Async Sequence status Pointer */
    SeqStatePtr = JobCfgPtr->JobStatePtr->AsyncSeqStatePtr;
    /* The Job has not been transmitted, reset its result as for the remaining Jobs */
    JobCfgPtr->JobStatePtr->JobResult = SPI_JOB_OK;
    /* Unlink the Job from its sequence */
    JobCfgPtr->JobStatePtr->AsyncSeqStatePtr = NULL_PTR;
    /* Unlink the remaining Jobs of the Sequence */
    Spi_AsyncUnlockRemainingJobs(CoreId, SeqStatePtr->SeqConfigPtr->SequenceId);
    /* Get PhyUnit status information structure pointer */
    /* #Violation: Spi_c_REF_1 */
    SpiPhyUnitStatusPtr = SPI_HWUNIT_STATUSPTR(CoreId, JobCfgPtr->SpiNumber);
    /* Release the HW unit */
    SpiPhyUnitStatusPtr->PhyUnitStatus = SPI_IDLE;
#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
    /* The HW unit is no longer occupied by an asynchronous sequence */
    SpiPhyUnitStatusPtr->IsAsync = FALSE;
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */

    return SeqStatePtr->SeqConfigPtr;
}

/****************************************************************************************************
*   Function Name           : Spi_AsyncReportCancelledSeq
*
*   Service ID              : None.
*
*   Description             : This function calls the Sequence end notification of a cancelled
*                             Sequence whose next Job has not been started.
*
*   Parameters in           : CoreId    : Execution Core ID Number.
*                             SeqCfgPtr : Configuration of the cancelled Sequence.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2.
*                             Shall be called outside of the AsyncTransmit critical section.
*
*   AUTOSAR_Requirement     : SWS_Spi_00145 SWS_Spi_00120.
****************************************************************************************************/
static FUNC(void, SPI_PRIVATE_CODE) Spi_AsyncReportCancelledSeq
(
    Mcal_CoreType           CoreId,
    P2CONST(Spi_SequenceConfigType, AUTOMATIC, SPI_APPL_CONST) SeqCfgPtr
)
{
    /*  SWS_Spi_00145:
        When the sequence is cancelled by the function Spi_Cancel and if configured, the SPI
        Handler/Driver shall call the sequence notification call-back function instead of starting
        a potential next job belonging to it.
    */
    if ((NULL_PTR != SeqCfgPtr) && (NULL_PTR != SeqCfgPtr->SeqEndNotificationPtr))
    {
        SeqCfgPtr->SeqEndNotificationPtr();
    }
    /* The cancelled Sequence's teardown is complete: release its whole-Sequence PhyUnit
       reservation, if it was linked to one */
    if (NULL_PTR != SeqCfgPtr)
    {
        Spi_AsyncReleaseSeqPhyUnits(CoreId, SeqCfgPtr);
    }
}
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */

#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
/****************************************************************************************************
*   Function Name           : Spi_AsyncStampDeadline
*
*   Service ID              : None.
*
*   Description             : This function calculates the system timer count at which an asynchronous
*                             transfer is supervised as timed out. The budget is SPI_TIMEOUT_US per
*                             FIFO round, a FIFO round being at most SPI_AVAILABLE_FIFOLEVEL frames.
*                             A DMA Job transfers all its rounds without SPI interaction and gets the
*                             same budget per round, so that one configuration parameter covers the
*                             FIFO and the DMA path.
*
*   Parameters in           : Rounds    : Number of FIFO rounds to be supervised, at least 1.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : System timer count at which the transfer is supervised as timed out,
*                             never 0, which is reserved for a transfer which is not supervised.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL2.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(uint64, SPI_PRIVATE_CODE) Spi_AsyncStampDeadline
(
    uint32                  Rounds
)
{
    uint64              TimerFreq;
    uint64              Deadline;

    /* Get the Stm system clock frequency */
    /* #Violation: Spi_c_REF_1 */
    TimerFreq = (uint64)Mcal_GetSystemTimerFreq();
    /* Calculate the count value required for delay *us, one budget per FIFO round */
    Deadline = ((SPI_TIMEOUT_US * TimerFreq) / 1000000ULL) * (uint64)Rounds;
    /* Calculate the timeout count value of delay *us */
    /* #Violation: Spi_c_REF_1 */
    Deadline += Mcal_GetSystemTimerCount();
    if (0ULL == Deadline)
    {
        /* The value 0 is reserved for 'no transfer supervised' */
        Deadline = 1ULL;
    }

    return Deadline;
}

/****************************************************************************************************
*   Function Name           : Spi_AsyncSuperviseTimeout
*
*   Service ID              : None.
*
*   Description             : This function supervises the timeout of the asynchronous transfer of a
*                             HW unit. The deadline handed over by Spi_MainFunction_Handling is only a
*                             pre-filter: the transfer can have made progress in an interrupt since
*                             the snapshot was taken, so Spi_AsyncAbortRunningJob re-validates the
*                             deadline with the interrupts disabled and aborts the Job in the same
*                             critical section. The development error is only reported when the Job
*                             has really been aborted by this call.
*
*   Parameters in           : CoreId    : Execution Core ID Number.
*                             PhyUnit   : Hardware ID Number.
*                             Deadline  : Supervision deadline of the HW unit, 0 if the HW unit is not
*                                         supervised.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant(Same HwUnit).
*
*   Return value            : None.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL2.
*                             Shall be called outside of every critical section.
*
*   AUTOSAR_Requirement     : SWS_Spi_00254 SWS_Spi_00267.
****************************************************************************************************/
static FUNC(void, SPI_PRIVATE_CODE) Spi_AsyncSuperviseTimeout
(
    Mcal_CoreType           CoreId,
    Spi_HWUnitType          PhyUnit,
    uint64                  Deadline
)
{
    uint64              TimerCount;

    /* Get the current count value of Stm */
    /* #Violation: Spi_c_REF_1 */
    TimerCount = Mcal_GetSystemTimerCount();
    if ((0ULL != Deadline) && (SPI_TIMEOUT_TIMER_HALFRANGE < (Deadline - TimerCount)))
    {
        /*  SWS_Spi_00254 SWS_Spi_00267: the transfer did not progress within its budget, the Job is
            aborted together with its Sequence */
        if (TRUE == Spi_AsyncAbortRunningJob(CoreId, PhyUnit, TRUE))
        {
            /* Raise runtime error SPI_E_TIMEOUT_ERROR */
            (void)Det_ReportRuntimeError(SPI_MODULE_ID, SPI_INSTANCE_ID,
                                    SPI_SID_MAINFUNCTION_HANDLING, SPI_E_TIMEOUT_ERROR);
        }
    }
}
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */

#if (SPI_CUSTOMIZED_CS_EN == STD_ON)
/****************************************************************************************************
*   Function Name           : Spi_WaitPhaseStatus
*
*   Service ID              : None.
*
*   Description             : Wait till the trailing delay is over and enter wait phase.
*
*   Parameters in           : PhyUnit    : Hardware ID Number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK: data transfer completed.
*                             E_NOT_OK: data transfer failed.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, SPI_PRIVATE_CODE) Spi_WaitPhaseStatus
(
    Spi_HWUnitType          PhyUnit
)
{
    boolean             RegStatus;
    uint32              RegValue;
    volatile uint64     TimerFreq;
    volatile uint64     TimeOutCount;
    volatile uint64     CurrentCount;

    RegStatus = FALSE;
    /* Get the Stm system clock frequency */
    /* #Violation: Spi_c_REF_1 */
    TimerFreq = (uint64)Mcal_GetSystemTimerFreq();
    /* Calculate the count value required for delay *us */
    TimeOutCount = (SPI_TIMEOUT_US * TimerFreq) / 1000000ULL;
    /* Calculate the timeout count value of delay *us */
    /* #Violation: Spi_c_REF_1 */
    TimeOutCount += Mcal_GetSystemTimerCount();

    /* Wait till the trailing delay is over and enter wait phase */
    do
    {
        /* Get SPI event status */
        RegValue =
            Espi_Hal_GetFlagStatus(Spi_ConfigPtr->PhyUnitMapPtr[PhyUnit], ESPI_PHASE_ALL_FLAGS);
        if((ESPI_PHASE_FLAG_WAIT == RegValue) ||
           (ESPI_PHASE_FLAG_EXPECT == (RegValue & ESPI_PHASE_FLAG_EXPECT)) ||
           (ESPI_PHASE_FLAG_TRAIL_STROBE == RegValue))
        {
            RegStatus = TRUE;
        }
        /* Get the current count value of Stm */
        /* #Violation: Spi_c_REF_1 */
        CurrentCount = Mcal_GetSystemTimerCount();
    }
    while ((CurrentCount < TimeOutCount) && (FALSE == RegStatus));

    return RegStatus;
}
#endif /* (SPI_CUSTOMIZED_CS_EN \== STD_ON) */
/****************************************************************************************************
*   Function Name           : Spi_GetDataTotalNumOfJob
*
*   Service ID              : None
*
*   Description             : This function performs the synchronous transmission for a sequence.
*
*   Parameters in           : CoreId    : Execution Core ID Number.
*                             Job       : Job ID Number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK: Sequence sending completed.
*                             E_NOT_OK: Sequence sending failed.
*
*   Preconditions           : Pre-compile parameter SPI_LEVEL_DELIVERED shall be SPI_LEVEL0 or SPI_LEVEL2
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(uint32, SPI_PRIVATE_CODE) Spi_GetDataTotalNumOfJob
(
    Mcal_CoreType           CoreId,
    Spi_JobType             Job
)
{
    uint16                          ChIndex;
    uint32                          DataTotalNum;
    const Spi_ChannelType           *ChannelIndexPtr;
    const Spi_JobConfigType         *JobCfgPtr;

    /* Set API return state initial value */
    DataTotalNum = 0UL;
    /* Get Job configuration information structure pointer */
    /* #Violation: Spi_c_REF_1 */
    JobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, Job); 
    /* Get Channel index in current Job */
    ChannelIndexPtr = JobCfgPtr->ChannelIndexListPtr;
    /* Poll all SPI channels in the job */
    for (ChIndex = 0U; ChIndex < JobCfgPtr->NumChannels; ChIndex++)
    {
        /* Get the total amount of data to be transmitted in the SPI channel */
        DataTotalNum += (uint32)*(Spi_ConfigPtr->CoreConfigPtr[CoreId]->
            ChannelCfgPtr[Spi_ConfigPtr->ChannelToCorePtr[*ChannelIndexPtr]].ActualDataLengthPtr);
        /* update ChannelIndexList */
        ChannelIndexPtr++;
    }

    /* Returns the amount of data transmitted by all channels in the job */
    return DataTotalNum;
}

/****************************************************************************************************
*   Function Name           : Spi_CheckSeqDataLength
*
*   Service ID              : None
*
*   Description             : This function checks the data length of all Jobs in a Sequence before
*                             the Sequence is accepted for transmission: every Channel shall have at
*                             least one frame and the total number of frames of a Job shall fit into
*                             the Move Counter data length register (ESPI_MOVE_STEP_MASK). A Job
*                             which violates it can never be transmitted completely.
*
*   Parameters in           : CoreId    : Execution Core ID Number.
*                             Sequence  : Sequence ID Number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK: The data length of all Jobs in the Sequence is valid.
*                             E_NOT_OK: At least one Job has an invalid data length.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Spi_00060.
****************************************************************************************************/
static FUNC(Std_ReturnType, SPI_PRIVATE_CODE) Spi_CheckSeqDataLength
(
    Mcal_CoreType           CoreId,
    Spi_SequenceType        Sequence
)
{
    Std_ReturnType                  RetStatus;
    Spi_JobType                     JobIdx;
    Spi_ChannelType                 ChIdx;
    uint32                          DataTotalNum;
    const Spi_JobConfigType         *JobCfgPtr;
    const Spi_ChannelConfigType     *ChannelCfgPtr;
    const Spi_SequenceConfigType    *SeqCfgPtr;

    RetStatus = E_OK;
    /* Get Sequence configuration information structure pointer */
    /* #Violation: Spi_c_REF_1 */
    SeqCfgPtr = SPI_SEQ_CONFIGPTR(CoreId, Sequence);
    for (JobIdx = 0U; (E_OK == RetStatus) && (JobIdx < SeqCfgPtr->NumJobs); JobIdx++)
    {
        /* Get Job configuration information structure pointer */
        /* #Violation: Spi_c_REF_1 */
        JobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, SeqCfgPtr->JobIndexListPtr[JobIdx]);
        DataTotalNum = 0UL;
        for (ChIdx = 0U; (E_OK == RetStatus) && (ChIdx < JobCfgPtr->NumChannels); ChIdx++)
        {
            /* Get Channel configuration information structure pointer */
            /* #Violation: Spi_c_REF_1 */
            ChannelCfgPtr = SPI_CH_CONFIGPTR(CoreId, JobCfgPtr->ChannelIndexListPtr[ChIdx]);
            /* A Channel without any frame can never complete its transmission */
            if (0U == *(ChannelCfgPtr->ActualDataLengthPtr))
            {
                RetStatus = E_NOT_OK;
            }
            else
            {
                DataTotalNum += (uint32)*(ChannelCfgPtr->ActualDataLengthPtr);
            }
        }
        /* The total number of frames of the Job shall fit into the Move Counter data length register */
        if ((0UL == DataTotalNum) || (DataTotalNum > (uint32)ESPI_MOVE_STEP_MASK))
        {
            RetStatus = E_NOT_OK;
        }
    }

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Spi_IsrError
*
*   Service ID              : None
*
*   Description             : This function is called by ERROR ISR for the ESPI units
*
*   Parameters in           : CoreId    : Execution Core ID Number.
*                             PhyUnit    : Hardware ID Number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, SPI_PRIVATE_CODE) Spi_IsrError
(
    Mcal_CoreType           CoreId,
    Spi_HWUnitType          PhyUnit
)
{
    uint32                      RegStatus;
    boolean                     ErrorDetected;

    ErrorDetected = FALSE;
    /* Entering the clear status flag critical protection */
    SPI_ENTER_CRITICAL_SECTION(IsrError);
    /* Get all error status flag */
    RegStatus = Espi_Hal_GetFlagStatus(
                Spi_ConfigPtr->PhyUnitMapPtr[PhyUnit], ESPI_INTC_ALL_ERROR_FLAGS);
    /* Check if PhyUnit error exists */
    if(0U != (RegStatus & ESPI_INTC_ALL_ERROR_FLAGS))
    {
        ErrorDetected = TRUE;
        /* Clearing all error status flag */
        Espi_Hal_ClearFlagStatus(
            Spi_ConfigPtr->PhyUnitMapPtr[PhyUnit], ESPI_INTC_ALL_ERROR_FLAGS);
        /*  SWS_Spi_00254:
            If the Sequence and Job related service is not done and, depending on services,
            either the return value shall be E_NOT_OK or a failed result (SPI_JOB_FAILED or
            SPI_SEQ_FAILED).
        */
        /*  The Job running on the HW unit, its Sequence and the HW unit itself are brought into a
            deterministic state by Spi_AsyncAbortRunningJob at the end of this function, outside of
            the critical section */
        /* Exit the clear status flag critical protection */
        SPI_EXIT_CRITICAL_SECTION(IsrError);
#if (SPI_DEV_ERROR_DETECT == STD_ON)
        /* Parity Error [Master/Slave] */
        if(0U != (RegStatus & ESPI_INTC_FLAG_PARITY_ERROR))
        {
            (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_ERROR_ISR,
                                SPI_E_STATE_PARITY_ERROR);
        }
        /* Unexpected Configuration Error (Master/Slave) */
        else if(0U != (RegStatus & ESPI_INTC_FLAG_UNEXPECT_CFG_ERROR))
        {
            (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_ERROR_ISR,
                                SPI_E_STATE_UNEXPECTCONFIG_ERROR);
        }
        /* TXFIFO Overflow Error (Master/Slave)*/
        else if(0U != (RegStatus & ESPI_INTC_FLAG_TX_OVF_ERROR))
        {
            (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_ERROR_ISR,
                                SPI_E_STATE_TXFIFO_OVERFLOW_ERROR);
        }
        /* RXFIFO Overflow Error (Master/Slave) */
        else if(0U != (RegStatus & ESPI_INTC_FLAG_RX_OVF_ERROR))
        {
            (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_ERROR_ISR,
                                SPI_E_STATE_RXFIFO_OVERFLOW_ERROR);
        }
        else
        {
            (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_ERROR_ISR,
                                SPI_E_STATE_UNKNOWN_ERROR);
        }
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
#if (SPI_DEM_REPORT_ERROR_STATUS == STD_ON)
        /*  SWS_Spi_00384 SWS_Spi_00267:
            When a hardware error is detected, the SPI Handler/Driver shall stop the current
            sequence, report an error to the DEM as configured and set the state of the Job to
            SPI_JOB_FAILED and the state of the Sequence to SPI_SEQ_FAILED.
            SWS_Spi_00385:
            When any error bit inside the SPI transmit status register is set, the SPI transmit
            status register information shall be reported to DEM as Dem_SetEventStatus
            (SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED)
            SWS_Spi_00195:
            SPI Handler/driver shall be able to detect the error SPI_E_HARDWARE_ERROR when an hardware
            error occur during asynchronous or synchronous transmit. Please see also SWS_Spi_00267 and
            SWS_Spi_00384.
        */
        /* Report DEM error - hardware error occurred */
        Dem_SetEventStatus(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif /* (SPI_DEM_REPORT_ERROR_STATUS  \== STD_ON) */
    }
    else
    {
        /* Exit the clear status flag critical protection */
        SPI_EXIT_CRITICAL_SECTION(IsrError);
    }
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
    if (TRUE == ErrorDetected)
    {
        /*  SWS_Spi_00267: a hardware error stops the current Sequence. The Job running on the HW
            unit is aborted immediately instead of only marking the Sequence FAILED, so that the HW
            unit is recovered and handed over to the scheduler. A synchronous transfer is not
            aborted here: it waits for its own reception in Spi_SyncWaitTransFinish and the claim
            inside Spi_AsyncAbortRunningJob denies it */
        (void)Spi_AsyncAbortRunningJob(CoreId, PhyUnit, FALSE);
    }
#else
    /* #Violation: Spi_c_REF_1 */
    MCAL_UNUSED_VAR(ErrorDetected);
    /* #Violation: Spi_c_REF_1 */
    MCAL_UNUSED_VAR(CoreId);
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */
}
/****************************************************************************************************
*   Function Name           : Spi_InitDriver
*
*   Service ID              : None
*
*   Description             : This function performs Spi driver initialization
*
*   Parameters in           : CoreId    : Execution Core ID Number.
*                             ConfigPtr : HW unit queue pointer.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : TRUE: The Spi driver is initialized successfully.
*                             FALSE: The Spi driver is not initialized.
*
*   Preconditions           : Spi driver must be uninitialized.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, SPI_PRIVATE_CODE) Spi_InitDriver
(
    Mcal_CoreType           CoreId,
    P2CONST(Spi_ConfigType, AUTOMATIC, SPI_APPL_CONST) ConfigPtr
)
{
    boolean                         RetStatus;
    Spi_JobType                     JobIndex;
    Spi_SequenceType                SeqIndex;
    Spi_HWUnitType                  PhyUnitIndex;
    Spi_ExternalDeviceType          ExDevNo;
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
    uint8                           Priority;
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */
#if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE0) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE2))
    Spi_ChannelType                 ChannelIndex;
    const Spi_ChannelConfigType     *ChannelCfgPtr;
#endif /* ((SPI_CHANNEL_BUFFERS_ALLOWED \== SPI_USAGE0) \|| (SPI_CHANNEL_BUFFERS_ALLOWED \== SPI_USAGE2)) */
    const Spi_CoreConfigType        *CurrentCoreConfigPtr;

    /* Update the global configuration parameter structure pointer */
    Spi_ConfigPtr = ConfigPtr;
    /* Get Corex configuration information structure pointer */
    CurrentCoreConfigPtr = Spi_ConfigPtr->CoreConfigPtr[CoreId];

    /* Initialize all Jobs */
    for (JobIndex = 0U; JobIndex < CurrentCoreConfigPtr->MaxJob; JobIndex++)
    {
        /* Reset Sequence status to 'SPI_JOB_OK' */
        /*  SWS_Spi_00015:
            After the module initialization using the function Spi_Init, the SPI Handler/Driver
            shall set its state to SPI_IDLE, the Sequences result to SPI_SEQ_OK and the jobs
            result to SPI_JOB_OK.
        */
        CurrentCoreConfigPtr->JobCfgPtr[JobIndex].JobStatePtr->JobResult = SPI_JOB_OK;
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
        /* Reset asynchronous Seq status pointer in Job configuration structure to 'NULL_PTR' */
        CurrentCoreConfigPtr->JobCfgPtr[JobIndex].JobStatePtr->AsyncSeqStatePtr = NULL_PTR;
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */
    }

    /* Initialize all Sequences */
    for (SeqIndex = 0U; SeqIndex < CurrentCoreConfigPtr->MaxSeq; SeqIndex++)
    {
        /* Reset Sequence status to 'SPI_SEQ_OK' */
        /*  SWS_Spi_00015:
            After the module initialization using the function Spi_Init, the SPI Handler/Driver
            shall set its state to SPI_IDLE, the Sequences result to SPI_SEQ_OK and the jobs
            result to SPI_JOB_OK.
        */
        /* Get Sequence status information, the input parameter is index */
        /* #Violation: Spi_c_REF_1 */
        Spi_CoreStatus[CoreId]->SequenceStatusPtr[SeqIndex].SeqResult = SPI_SEQ_OK;
#if((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
        /* Link the Sequence configuration structure pointer to the status structure pointer */
        Spi_CoreStatus[CoreId]->SequenceStatusPtr[SeqIndex].SeqConfigPtr =
                                                     &(CurrentCoreConfigPtr->SeqCfgPtr[SeqIndex]);
        Spi_CoreStatus[CoreId]->SequenceStatusPtr[SeqIndex].CurJobIndexPtr = NULL_PTR;
        Spi_CoreStatus[CoreId]->SequenceStatusPtr[SeqIndex].RemainingJobs = 0U;
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */
    }
#if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE0) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE2))
    /* Initialize the data length of all IB Channels */
    for (ChannelIndex = 0U; ChannelIndex < CurrentCoreConfigPtr->MaxChannel; ChannelIndex++)
    {
        /* Get Channel configuration information structure pointer */
        ChannelCfgPtr = &(CurrentCoreConfigPtr->ChannelCfgPtr[ChannelIndex]);
        /*  SWS_Spi_00052:
            For the IB Channels, the Handler/Driver shall provide the buffering but it is not able to
            take care of the consistency of the data in the buffer during transmission. The size of
            the Channel buffer is fixed.
        */
        /* The data length of an IB Channel is fixed to SpiIbNBuffers, it shall be valid for a
           transmission also before the first call of Spi_WriteIB */
        if (SPI_IB == ChannelCfgPtr->ChannelType)
        {
            *(ChannelCfgPtr->ActualDataLengthPtr) = ChannelCfgPtr->DataLength;
        }
    }
#endif /* ((SPI_CHANNEL_BUFFERS_ALLOWED \== SPI_USAGE0) \|| (SPI_CHANNEL_BUFFERS_ALLOWED \== SPI_USAGE2)) */
#if (SPI_LEVEL_DELIVERED == SPI_LEVEL1)
    /* Reset asynchronous operation mode to 'SPI_INTERRUPT_MODE' */
    *(Spi_CoreStatus[CoreId]->AsyncMode) = SPI_INTERRUPT_MODE;
#elif(SPI_LEVEL_DELIVERED == SPI_LEVEL2)
    /* Reset asynchronous operation mode to 'SPI_POLLING_MODE' */
    *(Spi_CoreStatus[CoreId]->AsyncMode) = SPI_POLLING_MODE;
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
    /* Reset synchronous transfer flag to '0U'*/
    *(Spi_CoreStatus[CoreId]->PhyUnitBusySyncStatusPtr) = 0U;
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */
    /* Reset the pending-teardown flag to '0U' */
    *(Spi_CoreStatus[CoreId]->PhyUnitPendingTeardownStatusPtr) = 0U;

    /* Initialize API execution result status variables */
    RetStatus = TRUE;
    /* Initialize all physical PhyUnits */
    for (PhyUnitIndex = 0U;
           ((PhyUnitIndex < CurrentCoreConfigPtr->MaxPhyUnit) && (TRUE == RetStatus));
             PhyUnitIndex++)
    {
#if (SPI_ENABLE_DMA == STD_ON)
        /*  DMA is used for asynchronous transfers in interrupt mode only, the same as in
            Spi_SetAsyncMode (SWS_Spi_00361: in polling mode the interrupts related to SPI busses
            handled asynchronously are disabled). The asynchronous mode has been reset above.
        */
        Spi_CoreStatus[CoreId]->PhyUnitStatusPtr[PhyUnitIndex].DmaEnable = FALSE;
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
        /* Check whether the current hardware enables DMA */
        /* #Violation: Spi_c_REF_1 */
        if ((SPI_INTERRUPT_MODE == SPI_ASYNC_MODE(CoreId)) &&
            (SPI_DMACHNOUSED_MASK != CurrentCoreConfigPtr->PhyUnitCfgPtr[PhyUnitIndex].TxDmaChannel))
        {
            /* Set PhyUnit status flags using DMA */
            Spi_CoreStatus[CoreId]->PhyUnitStatusPtr[PhyUnitIndex].DmaEnable = TRUE;
        }
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */
#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
            /* Reset hardware occupied by asynchronous sequence */
                Spi_CoreStatus[CoreId]->PhyUnitStatusPtr[PhyUnitIndex].IsAsync = FALSE;
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */
            /*  SWS_Spi_00161
                For an SPI Handler/Driver operating in LEVEL 0, when there is no on going Sequence
                transmission, the SPI Handler/Driver shall be in the idle state SPI_IDLE.
                SWS_Spi_00015:
                After the module initialization using the function Spi_Init, the SPI Handler/Driver
                shall set its state to SPI_IDLE, the Sequences result to SPI_SEQ_OK and the jobs
                result to SPI_JOB_OK.
            */
            /* Reset the hardware unit status to 'SPI_IDLE' */
            Spi_CoreStatus[CoreId]->PhyUnitStatusPtr[PhyUnitIndex].PhyUnitStatus = SPI_IDLE;
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
            /* Initialize the four-level priority list of SPIx */
            for (Priority = 0U; (Priority < SPI_JOB_PRIORITY_LEVELS_COUNT); Priority++)
            {
                /* Reset priority list head to 'SPI_JOB_NULL' */
                Spi_CoreStatus[CoreId]->
                    PhyUnitStatusPtr[PhyUnitIndex].ScheduledJobsListHead[Priority] = SPI_JOB_NULL;
                /* Reset priority list tail to 'SPI_JOB_NULL' */
                Spi_CoreStatus[CoreId]->
                    PhyUnitStatusPtr[PhyUnitIndex].ScheduledJobsListTail[Priority] = SPI_JOB_NULL;
            }
            /* Resets the maximum used priority to '-1' */
            Spi_CoreStatus[CoreId]->PhyUnitStatusPtr[PhyUnitIndex].MaxScheduledPriority = -1;
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */

            /* Configure the Spi chip select */
        for (ExDevNo = 0U;
            ((ExDevNo < CurrentCoreConfigPtr->MaxExDevice) && (TRUE == RetStatus));
                 ExDevNo++)
        {
            /* Initialize hardware unit module */
            RetStatus &= Espi_Master_Hal_InitModule(
                Spi_ConfigPtr->PhyUnitMapPtr[CurrentCoreConfigPtr->
                PhyUnitCfgPtr[PhyUnitIndex].SpiNumber], CurrentCoreConfigPtr->
                 PhyUnitCfgPtr[PhyUnitIndex].Spi_PhyUnitConfigParamPtr);
                /* Check whether the hardware unit number is correct */
            if (CurrentCoreConfigPtr->ExDeviceCfgPtr[ExDevNo].SpiNumber ==
                        CurrentCoreConfigPtr->PhyUnitCfgPtr[PhyUnitIndex].SpiNumber)
            {
#if (SPI_CUSTOMIZED_CS_EN == STD_ON)
                /* Check whether the peripherals used by the current job use GPIO for chip selection */
                if(SPI_CS_VIA_GPIO == CurrentCoreConfigPtr->ExDeviceCfgPtr[ExDevNo].CsSelection)
                {
                    /* Initialize IO levels to desired state */
                    Dio_WriteChannel(CurrentCoreConfigPtr->ExDeviceCfgPtr[ExDevNo].GpioPortPin,
                        ((uint8)CurrentCoreConfigPtr->ExDeviceCfgPtr
                            [ExDevNo].Spi_ExDeviceCfgInfoPtr->slsoActiveLevel) ^ 1U);
                }
#endif /* (SPI_CUSTOMIZED_CS_EN \== STD_ON) */
                /* Initialize SPI chip select channel */
                RetStatus &= Espi_Master_Hal_InitChannel(
                        Spi_ConfigPtr->PhyUnitMapPtr[CurrentCoreConfigPtr->
                        PhyUnitCfgPtr[PhyUnitIndex].SpiNumber],CurrentCoreConfigPtr->
                        ExDeviceCfgPtr[ExDevNo].Spi_ExDeviceCfgInfoPtr);
            }
        }
    }
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Update the current Core Spi driver initialization status to 'SPI_INITIALIZED'  */
    *(Spi_CoreStatus[CoreId]->CoreInitStatusPtr) = SPI_INITIALIZED;
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Spi_DeInitDriver
*
*   Service ID              : None
*
*   Description             : This function performs Spi driver de-initialization.
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
*   Return value            : E_OK: de-initialisation command has been accepted.
*                             E_NOT_OK: de-initialisation command has not been accepted.
*
*   Preconditions           : Spi driver must be initialized and not busy.
*
****************************************************************************************************/
static FUNC(Std_ReturnType, SPI_PRIVATE_CODE) Spi_DeInitDriver
(
    Mcal_CoreType           CoreId
)
{
    Std_ReturnType                  RetStatus;
    Rcc_ErrorFlag                   ResetStatus;
    Spi_HWUnitType                  PhyUnitIndex;
    Spi_JobType                     JobIndex;
    Spi_SequenceType                SeqIndex;
    const Spi_CoreConfigType        *CurrentCoreConfigPtr;

    /* Initialize API execution result status variables */
    RetStatus = E_OK;
    /* Get Corex configuration information structure pointer */
    CurrentCoreConfigPtr = Spi_ConfigPtr->CoreConfigPtr[CoreId];
    /* De-initialize all physical PhyUnits */
    for(PhyUnitIndex = 0U;
       (PhyUnitIndex < CurrentCoreConfigPtr->MaxPhyUnit) && (E_OK == RetStatus);
        PhyUnitIndex++)
    {
        /* Lock for disable interrupts */
        RetStatus = Mcal_GetLock(MCAL_LOCK_ID_RCC);
        if (E_OK == RetStatus)
        {
            /* Reset physical PhyUnits */
            ResetStatus = Espi_Hal_ResetModule(Spi_ConfigPtr->PhyUnitMapPtr[Spi_ConfigPtr->
                CoreConfigPtr[CoreId]->PhyUnitCfgPtr[PhyUnitIndex].SpiNumber]);
            /* Release software lock for SPI */
            Mcal_ReleaseLock(MCAL_LOCK_ID_RCC);
            if(RCC_ERRORFLAG_SUCCESS == ResetStatus)
            {
                /*  SWS_Spi_00011:
                    After reset, the type Spi_StatusType shall have the default value SPI_UNINIT
                    with the numeric value 0.
                    SWS_Spi_00252:
                    In case of the SPI Handler/Driver state is not SPI_BUSY, the deInitialization
                    function shall put all already initialized microcontroller SPI peripherals
                    into the same state such as Power On Reset.
                    SWS_Spi_00022:
                    After the module de-initialization using the function Spi_DeInit, the SPI
                    Handler/Driver shall set its state to SPI_UNINIT.
                */
                Spi_CoreStatus[CoreId]->PhyUnitStatusPtr[PhyUnitIndex].PhyUnitStatus = SPI_UNINIT;
            }
            else
            {
                RetStatus = E_NOT_OK;
            }
        }
    }
    /*  SWS_Spi_00012:
        After reset, the type Spi_JobResultType shall have the default value SPI_JOB_OK
        with the numeric value 0.
    */
    for (JobIndex = 0U;
        (JobIndex < CurrentCoreConfigPtr->MaxJob) && (E_OK == RetStatus);
        JobIndex++)
    {
        /* Reset Sequence status to 'SPI_JOB_OK' */
        CurrentCoreConfigPtr->JobCfgPtr[JobIndex].JobStatePtr->JobResult = SPI_JOB_OK;
    }
    /*  SWS_Spi_00017:
        After reset, the type Spi_SeqResultType shall have the default value SPI_SEQ_OK
        with the numeric value 0.
    */
    for (SeqIndex = 0U;
        (SeqIndex < CurrentCoreConfigPtr->MaxSeq) && (E_OK == RetStatus);
         SeqIndex++)
    {
        /* Get Sequence status information, the input parameter is index */
        Spi_CoreStatus[CoreId]->SequenceStatusPtr[SeqIndex].SeqResult = SPI_SEQ_OK;
    }
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    if (E_OK == RetStatus)
    {
        /* Update the current Core Spi driver initialization status to 'SPI_UNINITIALIZE'  */
        *(Spi_CoreStatus[CoreId]->CoreInitStatusPtr) = SPI_UNINITIALIZE;
    }
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */

    /*  SWS_Spi_00301:
        When the API Spi_DeInit has been accepted the return value of this function shall be E_OK.
        SWS_Spi_00302:
        When the API Spi_DeInit has not been accepted the return value of this function shall be E_NOT_OK.
    */
    return RetStatus;
}
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
*   Function Name           : Spi_Init
*
*   Service ID              : 0x00
*
*   Description             : Driver Module Initialization function Service for SPI initialization.
*                             The Initialization function initialize all SPI relevant registers with
*                             the values of the structure referenced by the parameter ConfigPtr.
*
*   Parameters in           : ConfigPtr: HW unit queue pointer.
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
*   Preconditions           : Spi driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Spi_00175 SWS_Spi_00298 SWS_Spi_00299 SWS_Spi_00013 SWS_Spi_00082
                              SWS_Spi_00015 SWS_Spi_00151 SWS_Spi_00233 SWS_Spi_00246 SWS_Spi_00015
                              SWS_Spi_00161
****************************************************************************************************/
/* #Violation: Spi_c_REF_3 */
FUNC(void, SPI_PUBLIC_CODE) Spi_Init
(
    /* #Violation: Spi_c_REF_9 */
    P2CONST(Spi_ConfigType, AUTOMATIC, SPI_APPL_CONST) ConfigPtr
)
{
#if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
    boolean                         RetStatus;
#endif /* ((SPI_DEV_ERROR_DETECT \== STD_ON) || (SPI_SAFETY_ENABLE \== STD_ON)) */
    Mcal_CoreType                   CoreId;

    /* Get core id which is executing currently */
    /* #Violation: Spi_c_REF_1 */
    CoreId = Mcal_GetCoreId(); 

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Initialize API execution result status variables */
    RetStatus = FALSE;
    /* Not Spi driver status information storage variable in current core */
    if(NULL_PTR == Spi_CoreStatus[CoreId])
    {
        (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_INIT,
                                SPI_E_CORE_NOT_STATUS_STORAGEVAR);
    }
    /*  SWS_Spi_00233:
        If development error detection for the SPI module is enabled, the calling of the routine
        SPI_Init() while the SPI driver is already initialized will cause a development error
        SPI_E_ALREADY_INITIALIZED and the desired functionality shall be left without any action.
        SWS_Spi_00246:
        The SPI driver has already been initialized time.
    */
    else if(SPI_INITIALIZED == *(Spi_CoreStatus[CoreId]->CoreInitStatusPtr))
    {
        (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_INIT,
                                SPI_E_ALREADY_INITIALIZED);
    }
    /* SWS_Spi_00371: APIs called with a Null Pointer */
    else if(NULL_PTR == ConfigPtr)
    {
        (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_INIT,
                                SPI_E_PARAM_POINTER);
    }
    else
    {
        RetStatus = TRUE;
    }
    if(TRUE == RetStatus)
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
    {

#if (SPI_SAFETY_ENABLE == STD_ON)

        /* Initialize Spi Driver */
        RetStatus = Spi_InitDriver(CoreId, ConfigPtr);

        if(FALSE == RetStatus)
        {
            (void)Det_ReportRuntimeError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_INIT,
                SPI_E_SAFETY_ERROR);
        }
#else
        /* Initialize Spi Driver */
        Spi_InitDriver(CoreId, ConfigPtr);

#endif /* (SPI_SAFETY_ENABLE \== STD_ON) */
    }
}

/****************************************************************************************************
*   Function Name           : Spi_DeInit
*
*   Service ID              : 0x01
*
*   Description             : Service for Spi de-initialization.
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
*   Return value            : E_OK: de-initialisation command has been accepted.
*                             E_NOT_OK: de-initialisation command has not been accepted.
*
*   Preconditions           : Spi driver must be initialized.
*
*   AUTOSAR_Requirement     : SWS_Spi_00176 SWS_Spi_00300 SWS_Spi_00301 SWS_Spi_00302 SWS_Spi_00303
                              SWS_Spi_00021 SWS_Spi_00046 SWS_Spi_00242 SWS_Spi_00243 SWS_Spi_00253
                              SWS_Spi_00011 SWS_Spi_00252 SWS_Spi_00022 SWS_Spi_00012 SWS_Spi_00017
                              SWS_Spi_00301 SWS_Spi_00302
****************************************************************************************************/
/* #Violation: Spi_c_REF_3 */
FUNC(Std_ReturnType, SPI_PUBLIC_CODE) Spi_DeInit
(
    void
)
{
    Mcal_CoreType                   CoreId;
    Std_ReturnType                  RetStatus;
    Spi_StatusType                  SpiStatus;

    /* Get core id which is executing currently */
    /* #Violation: Spi_c_REF_1 */
    CoreId = Mcal_GetCoreId(); 
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Initialize API execution result status variables */
    RetStatus = E_NOT_OK;
    if(NULL_PTR == Spi_CoreStatus[CoreId])
    {
        (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_DEINIT,
                                SPI_E_CORE_NOT_STATUS_STORAGEVAR);
    }
    /*  SWS_Spi_00046:
        If development error detection for the SPI module is enabled and the SPI Handler/Driver's
        environment calls any API function before initialization, an error should be reported to
        the DET with the error value SPI_E_UNINIT according to the configuration.
        SWS_Spi_00242:
        API service used without module initialization
    */
    else if(SPI_UNINITIALIZE == *(Spi_CoreStatus[CoreId]->CoreInitStatusPtr))
    {
        (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_DEINIT,
                                SPI_E_UNINIT);
    }
    else
    {
        RetStatus = E_OK;
    }
    if (E_OK == RetStatus)
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Entering the clear status flag critical protection */
        SPI_ENTER_CRITICAL_SECTION(DeInit);
        /* Get SPI hardware unit execution status */
        SpiStatus = Spi_GetDriverStatus(CoreId);
        /*  SWS_Spi_00243:
            API services called in a wrong sequence(Pending)
            SWS_Spi_00253:
            The function call Spi_DeInit shall be rejected if the status of
            SPI Handler/Driver is SPI_BUSY.
        */
        if(SPI_BUSY == SpiStatus)
        {
            /* Exit the clear status flag critical protection */
            SPI_EXIT_CRITICAL_SECTION(DeInit);
            RetStatus = E_NOT_OK;
            (void)Det_ReportRuntimeError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_DEINIT,
                            SPI_E_SEQ_PENDING);
        }
        else
        {
            /* De-intialize Spi Driver*/
            RetStatus = Spi_DeInitDriver(CoreId);

            /* Exit the clear status flag critical protection */
            SPI_EXIT_CRITICAL_SECTION(DeInit);
        }
    }
    /*  SWS_Spi_00301:
        When the API Spi_DeInit has been accepted the return value of this function shall be E_OK.
        SWS_Spi_00302:
        When the API Spi_DeInit has not been accepted the return value of this function shall be E_NOT_OK.
    */
    return RetStatus;
}

#if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE0) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE2))
/****************************************************************************************************
*   Function Name           : Spi_WriteIB
*
*   Service ID              : 0x02
*
*   Description             : Service for writing one or more data to an IB SPI Handler/Driver
*                             Channel specified by parameter. In case of 16bit Channel Data Width
*                             the DataBufferPtr must be 16bit aligned. This service is only relevant
*                             for Channels with IB. Different Jobs, consequently also Sequences,
*                             can have in common Channels. But the use of those shared Channels is
*                             restricted. Read and Write functions can not guarantee the data
*                             integrity while Channel data is being transmitted. User must ensure
*                             that Read and/or Write functions are not called during transmission.
*
*   Parameters in           : Channel: Channel ID.
*                             DataBufferPtr: Pointer to source data buffer. If this pointer is null,
*                                            it is assumed that the data to be transmitted is not
*                                            relevant and the default transmit value of this channel
*                                            will be used instead.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK: write command has been accepted.
*                             E_NOT_OK: write command has not been accepted.
*
*   Preconditions           : Spi driver must be initialized and pre-compile parameter
*                             SPI_CHANNEL_BUFFERS_ALLOWED shall be SPI_USAGE0 or SPI_USAGE2.
*
*   AUTOSAR_Requirement     : SWS_Spi_00177 SWS_Spi_00304 SWS_Spi_00305 SWS_Spi_00306 SWS_Spi_00307
                              SWS_Spi_00018 SWS_Spi_00024 SWS_Spi_00137 SWS_Spi_00085 SWS_Spi_00004
                              SWS_Spi_00031 SWS_Spi_00236 SWS_Spi_00051 SWS_Spi_00024 SWS_Spi_00305
                              SWS_Spi_00306
****************************************************************************************************/
/* #Violation: Spi_c_REF_3 */
FUNC(Std_ReturnType, SPI_PUBLIC_CODE) Spi_WriteIB
(
    Spi_ChannelType Channel,
    /* #Violation: Spi_c_REF_9 */
    P2CONST(Spi_DataBufferType, AUTOMATIC, SPI_APPL_CONST) DataBufferPtr
)
{
    Mcal_CoreType                   CoreId;
    Std_ReturnType                  RetStatus;
    uint32                          DataIndex;
    uint32                          FrameByteIndex;
    uint32                          BufferSize;
    const uint8                     *DefaultDataPtr;
    const Spi_ChannelConfigType     *ChannelCfgPtr;

    /* Get core id which is executing currently */
    /* #Violation: Spi_c_REF_1 */
    CoreId = Mcal_GetCoreId(); 
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Get Channel DET diagnostic results */
    RetStatus = Spi_GetChannelDetStatus(CoreId, SPI_SID_WRITEIB, Channel);
    if(E_OK == RetStatus)
#else
    /* Reset API execution status variables */
    RetStatus = E_OK;
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /*  SWS_Spi_00004:
            API service called with wrong Channel parameter
            SWS_Spi_00031:
            The API parameter Channel shall have a value within the defined channels in the
            initialization data structure, and the correct type of channel (IB or EB) has to be
            used with services. Related error value: SPI_E_PARAM_CHANNEL. Otherwise, the service
            is not done and the return value shall be E_NOT_OK.
        */
        /* Get Channel configuration information structure pointer */
        /* #Violation: Spi_c_REF_1 */
        ChannelCfgPtr = SPI_CH_CONFIGPTR(CoreId, Channel); 
        if(SPI_IB != ChannelCfgPtr->ChannelType)
        {
            RetStatus = E_NOT_OK;
#if (SPI_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_WRITEIB,
                                    SPI_E_PARAM_CHANNEL);
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
        }
        else
        {
            /* Entering write internal buffer critical protection */
            SPI_ENTER_CRITICAL_SECTION(WriteIB);
            /* Calculate actual number of bytes to be transmitted */
            *(ChannelCfgPtr->ActualDataLengthPtr) = ChannelCfgPtr->DataLength;
            /* Calculate the size of the internal TX buffer in bytes */
            BufferSize = ((uint32)ChannelCfgPtr->DataLength) * ((uint32)ChannelCfgPtr->FrameWidth);

            /*  SWS_Spi_00236:
            A Channel used for a transmission should have its parameters configured but it is allowed
            to pass Null pointers as source and destination pointers to generate a dummy transmission.
            */
            /* Check whether the data buffer is 'NULL_PTR' */
            if (NULL_PTR == DataBufferPtr)
            {
                /*  SWS_Spi_00023:
                    If the given parameter "DataBufferPtr" is null, the function Spi_WriteIB shall
                    assume that the data to be transmitted is not relevant and the default transmit
                    value of the given channel shall be used instead.
                */
                /* TXBuffPtr of an IB channel is the only reference to the internal TX buffer and
                   shall never be changed. Fill each frame of the internal TX buffer with the default
                   transmit value instead, using the same 'FrameWidth' bytes of ChDefaultData that
                   Espi_Hal_SendData reads when sending the default transmit value directly. */
                DefaultDataPtr = (const uint8 *)&(ChannelCfgPtr->BufferDescriptorPtr->ChDefaultData);
                for (DataIndex = 0UL; DataIndex < BufferSize;
                     DataIndex += (uint32)ChannelCfgPtr->FrameWidth)
                {
                    for (FrameByteIndex = 0UL; FrameByteIndex < (uint32)ChannelCfgPtr->FrameWidth;
                         FrameByteIndex++)
                    {
                        /* Copy default transmit value to the SPI internal TX buffer */
                        ChannelCfgPtr->BufferDescriptorPtr->TXBuffPtr[DataIndex + FrameByteIndex] =
                                                                DefaultDataPtr[FrameByteIndex];
                    }
                }
            }
            else
            {
                /*  SWS_Spi_00051:
                    The channel data to be transmitted shall be copied in 1 entry deep internal
                    buffers by channel.
                    SWS_Spi_00024:
                    The function Spi_WriteIB shall take over the given parameters, and save the
                    pointed data to the internal buffer defined with the function Spi_Init.
                */
                /* Copy SPI user data to the SPI internal TX buffer */
                
                for (DataIndex = 0UL; DataIndex < BufferSize; DataIndex++)
                {
                    /* Copy SPI user data to the SPI internal TX buffer */
                    ChannelCfgPtr->BufferDescriptorPtr->TXBuffPtr[DataIndex] =
                                                                DataBufferPtr[DataIndex];
                }
            }
            /* Exit write internal buffer critical protection */
            SPI_EXIT_CRITICAL_SECTION(WriteIB);
        }
    }
    /*  SWS_Spi_00305:
        When the API Spi_WriteIB command has been accepted the function returns the value E_OK.
        SWS_Spi_00306:
        When the API Spi_WriteIB command has not been accepted the function returns
        the value E_NOT_OK.
    */
    return RetStatus;
}
#endif /* ((SPI_CHANNEL_BUFFERS_ALLOWED \== SPI_USAGE0)
        || (SPI_CHANNEL_BUFFERS_ALLOWED \== SPI_USAGE2)) */

/*  SWS_Spi_00133:
    The function Spi_AsyncTransmit is pre-compile time selectable by the configuration parameter
    SpiLevelDelivered. This function is only relevant for LEVEL 1 and LEVEL 2.
*/
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
/****************************************************************************************************
*   Function Name           : Spi_AsyncTransmit
*
*   Service ID              : 0x03
*
*   Description             : Service to transmit data on the SPI bus. This service take over the
*                             given parameter, initiate a transmission, and set the SPI Handler
*                             Driver status to SPI_BUSY, set the sequence result to SPI_SEQ_PENDING,
*                             set the first job result to SPI_JOB_PENDING and return. The function
*                             allows transmitting more than one Sequence at the same time. That means
*                             during a Sequence on-going transmission, all requests to transmit
*                             another Sequence shall be evaluated, using the lead Job, for an
*                             acceptance if different SPI buses or for set to pending state for
*                             transmission later. This method shall be called after a Spi_SetupEB
*                             method for EB Channels or Spi_WriteIB method for IB Channels but
*                             before the Spi_ReadIB method.
*
*   Parameters in           : Sequence: Sequence ID.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK: Transmission command has been accepted.
*                             E_NOT_OK: Transmission command has not been accepted.
*
*   Preconditions           : Spi driver must be initialized and pre-compile parameter
*                             SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2.
*
*   AUTOSAR_Requirement     : SWS_Spi_00178 SWS_Spi_00308 SWS_Spi_00311 SWS_Spi_00081 SWS_Spi_00266
                              SWS_Spi_00353 SWS_Spi_00020 SWS_Spi_00194 SWS_Spi_00243 SWS_Spi_00086
                              SWS_Spi_00309 SWS_Spi_00310 SWS_Spi_00133
****************************************************************************************************/
/* #Violation: Spi_c_REF_3 */
FUNC(Std_ReturnType, SPI_PUBLIC_CODE) Spi_AsyncTransmit
(
    Spi_SequenceType Sequence
)
{
    boolean                         RetResult;
    Mcal_CoreType                   CoreId;
    Std_ReturnType                  RetStatus;
    Spi_JobType                     NumJobsInSequence;
    Spi_JobType                     JobIdx;
    Spi_SequenceStateType           *SeqStatePtr;
    const Spi_JobType               *JobIndexPtr;
    const Spi_SequenceConfigType    *SeqCfgPtr;
    const Spi_JobConfigType         *PendingJobCfgPtr;
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    const Spi_JobConfigType         *JobCfgPtr;
#if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE1) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE2))
    Spi_ChannelType                 ChannelIdx;
    const Spi_ChannelConfigType     *ChannelCfgPtr;
#endif /* ((SPI_CHANNEL_BUFFERS_ALLOWED \== SPI_USAGE1)||(SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE2)) */
    uint8                           ErrorFlag;
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */

    /* Initialize local variables */
    RetResult = TRUE;
    RetStatus = E_OK;
    /* Get core id which is executing currently */
    /* #Violation: Spi_c_REF_1 */
    CoreId = Mcal_GetCoreId(); 
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Get Sequence DET check results */
    RetStatus = Spi_GetSeqDetStatus(CoreId, SPI_SID_ASYNCTRANSMIT, Sequence);
    if (E_OK == RetStatus)
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Get Sequence configuration information structure pointer */
        /* #Violation: Spi_c_REF_1 */
        SeqCfgPtr = SPI_SEQ_CONFIGPTR(CoreId, Sequence); 
        /* Get the total number of jobs in Sequnce */
        NumJobsInSequence = SeqCfgPtr->NumJobs;
#if (SPI_DEV_ERROR_DETECT == STD_ON)
        /* Enter asynchronous transmission critical protection */
        SPI_ENTER_CRITICAL_SECTION(AsyncTransmit);
        /* Check if the jobs in the current Sequence */
        for(JobIdx = 0U; ((E_OK == RetStatus) && (JobIdx < NumJobsInSequence)); JobIdx++)
        {
            /* Get Job configuration information structure pointer */
            /* #Violation: Spi_c_REF_1 */
            JobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, SeqCfgPtr->JobIndexListPtr[JobIdx]); 
            /* Check whether the total number of channels in the job is '0U' */
            if (0U == JobCfgPtr->NumChannels)
            {
                ErrorFlag = SPI_E_JOB_EMPTY;
                RetStatus = E_NOT_OK;
            }
#if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE1) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE2))
            /* Whether the Channel index is less than the total number in current Job */
            for(ChannelIdx = 0U;
                (E_OK == RetStatus) && (ChannelIdx < JobCfgPtr->NumChannels);
                ChannelIdx++)
            {
                /* Get Channel configuration information structure pointer */
                /* #Violation: Spi_c_REF_1 */
                ChannelCfgPtr = SPI_CH_CONFIGPTR(CoreId, JobCfgPtr->ChannelIndexListPtr[ChannelIdx]); 
                /* Check whether the Channel buffer type is 'EB' && data length is '0U'*/
                if ((SPI_EB == ChannelCfgPtr->ChannelType) 
                        && (0U == *ChannelCfgPtr->ActualDataLengthPtr))
                {
                    ErrorFlag = SPI_E_PARAM_EB_UNIT;
                    RetStatus = E_NOT_OK;
                }
            }
#endif /* ((SPI_CHANNEL_BUFFERS_ALLOWED \== SPI_USAGE1)\||(SPI_CHANNEL_BUFFERS_ALLOWED \== SPI_USAGE2)) */
        }
        /* Exit asynchronous transmission critical protection */
        SPI_EXIT_CRITICAL_SECTION(AsyncTransmit);

        if (E_NOT_OK == RetStatus)
        {
            (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID,
                                    SPI_SID_ASYNCTRANSMIT, ErrorFlag);
        }
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
    }
    if (E_OK == RetStatus)
    {
        /*  SWS_Spi_00060:
            Check the data length of all Jobs before any state is changed. This check does not
            depend on SPI_DEV_ERROR_DETECT: a Job with an invalid data length can never be
            transmitted and would block its Sequence and PhyUnit.
        */
        RetStatus = Spi_CheckSeqDataLength(CoreId, Sequence);
#if (SPI_DEV_ERROR_DETECT == STD_ON)
        if (E_NOT_OK == RetStatus)
        {
            (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_ASYNCTRANSMIT,
                                    SPI_E_PARAM_LENGTH);
        }
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
    }
    if (E_OK == RetStatus)
    {
        /* Enter asynchronous transmission critical protection */
        SPI_ENTER_CRITICAL_SECTION(AsyncTransmit);
        /* Get Sequence status information, the input parameter is the Sequence ID */
        /* #Violation: Spi_c_REF_1 */
        if(SPI_SEQ_PENDING == SPI_SEQ_STATUS(CoreId, Sequence)) 
        {
            /* Exit asynchronous transmission critical protection */
            SPI_EXIT_CRITICAL_SECTION(AsyncTransmit);
            /*  SWS_Spi_00081:
                When the function Spi_AsyncTransmit is called and the requested Sequence is already in
                state SPI_SEQ_PENDING, the SPI Handler/Driver shall not take in account this new request
                and this function shall return with value E_NOT_OK, in this case.
            */
            RetStatus = E_NOT_OK;
            /*  SWS_Spi_00266:
                When the function Spi_AsyncTransmit is called and the requested Sequence is already in
                state SPI_SEQ_PENDING the SPI Handler/Driver shall report the SPI_E_SEQ_PENDING error
                according to [SWS_BSW_00042] and [SWS_BSW_00045].
            */
            (void)Det_ReportRuntimeError(SPI_MODULE_ID, SPI_INSTANCE_ID,
                                    SPI_SID_ASYNCTRANSMIT, SPI_E_SEQ_PENDING);
        }
        else
        {
            /* Get result if the Job is linked to the current Sequence */
            RetStatus = Spi_AsyncCheckJobLinkStatus(CoreId, Sequence);
            /* Check if the Job is linked to the current Sequence */
            if(E_OK == RetStatus)
            {
                /*  SWS_Spi_00353:
                    Spi_GetSequenceResult function shall return SPI_SEQ_PENDING when the SPI
                    Handler/Driver is performing a SPI Sequence. The meaning of this status
                    is equal to SPI_BUSY.
                    SWS_Spi_00020:
                    The function Spi_AsyncTransmit shall take over the given parameter, initiate a
                    transmission, set the SPI Handler/Driver status to SPI_BUSY, set the sequence
                    result to SPI_SEQ_PENDING and return.
                */
                /* Update the Sequence status to 'SPI_SEQ_PENDING' => Mark sequence pending */
                /* #Violation: Spi_c_REF_1 */
                SPI_SEQ_STATUS(CoreId, Sequence) = SPI_SEQ_PENDING;
                /* Update the status of all jobs in Sequence to 'SPI_JOB_QUEUED' */
                for(JobIdx = 0U; JobIdx < NumJobsInSequence; JobIdx++)
                {
                    /*  SWS_Spi_00194:
                        When the function Spi_AsyncTransmit is called, shall take over the given
                        parameter and set the Job status to SPI_JOB_QUEUED, which can be obtained
                        by calling the API service Spi_GetJobResult.
                    */
                    /* Get Job status information, the input parameter is the Job ID */
                    /* #Violation: Spi_c_REF_1 */
                    SPI_JOB_STATUS(CoreId, SeqCfgPtr->JobIndexListPtr[JobIdx]) = SPI_JOB_QUEUED;
                    /* Reserve every PhyUnit the Sequence uses for its whole duration, so
                       busy-detection is not fooled between now and this Sequence's teardown */
                    /* #Violation: Spi_c_REF_1 */
                    PendingJobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, SeqCfgPtr->JobIndexListPtr[JobIdx]);
                    *(Spi_CoreStatus[CoreId]->PhyUnitPendingTeardownStatusPtr) |=
                                                (uint16)1U << PendingJobCfgPtr->SpiNumber;
                }
                /* Get the Sequence state structure pointer */
                /* #Violation: Spi_c_REF_1 */
                SeqStatePtr = SPI_SEQ_STATUSPTR(CoreId, Sequence); 
                /* Update the number of Jobs to be transferred */
                SeqStatePtr->RemainingJobs = NumJobsInSequence - 1U;
                /* Get the link status of the Job in the current Sequence */
                JobIndexPtr = &(SeqCfgPtr->JobIndexListPtr[0]);
                /* Update the current Job index pointer first addressed */
                SeqStatePtr->CurJobIndexPtr = JobIndexPtr;
                /* Exit asynchronous transmission critical protection */
                SPI_EXIT_CRITICAL_SECTION(AsyncTransmit);
                /* Schedule a job for a given HW unit. If the first Job can not be started, the
                   Sequence is aborted and reported synchronously via E_NOT_OK: no end notification
                   is called, so a request repeated in a notification can not recurse endlessly. */
                RetResult = Spi_AsyncScheduleJob(CoreId, *JobIndexPtr, FALSE);
            }
            else
            {
                /* Exit asynchronous transmission critical protection */
                SPI_EXIT_CRITICAL_SECTION(AsyncTransmit);
                /*  SWS_Spi_00243:
                    API services called in a wrong sequence(Pending)
                    SWS_Spi_00086:
                    When the function Spi_AsyncTransmit is called and the re-quested Sequence shares
                    Jobs with another sequence that is in the state SPI_SEQ_PENDING, the SPI Handler/
                    Driver shall not take into account this new re-quest and this function shall
                    return the value E_NOT_OK. In this case and according to [SWS_BSW_00042] and
                    [SWS_BSW_00045], the SPI Handler/Driver shall report the SPI_E_SEQ_PENDING error.
                */
                (void)Det_ReportRuntimeError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_ASYNCTRANSMIT,
                                    SPI_E_SEQ_PENDING);
            }
        }
    }

    if(FALSE == RetResult)
    {
        RetStatus = E_NOT_OK;
#if (SPI_SAFETY_ENABLE == STD_ON)
        (void)Det_ReportRuntimeError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_ASYNCTRANSMIT,
                                     SPI_E_SAFETY_ERROR);
#endif /* (SPI_SAFETY_ENABLE \== STD_ON) */
    }

    /*  SWS_Spi_00309:
        When the API Spi_AsyncTransmit command has been accepted the function shall return
        the value E_OK.
        SWS_Spi_00310:
        When the API Spi_AsyncTransmit command has not been accepted the function shall return
        the value E_NOT_OK.
    */
    return RetStatus;
}
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */

/*  SWS_Spi_00138:
    The function Spi_ReadIB is pre-compile time configurable by the parameter
    SpiChannelBuffersAllowed. This function is only relevant for Channels with IB.
*/
#if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE0) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE2))
/****************************************************************************************************
*   Function Name           : Spi_ReadIB
*
*   Service ID              : 0x04
*
*   Description             : Service for reading synchronously one or more data from an IB SPI
*                             Handler/Driver Channel specified by parameter.In case of 16bit Channel
*                             Data Width the DataBufferPtr must be 16bit aligned Different Jobs,
*                             consequently also Sequences, can have in common Channels. But the use
*                             of those shared Channels is restricted. Read and Write functions can
*                             not guarantee the data integrity while Channel data is being
*                             transmitted. User must ensure that Read and/or Write functions are not
*                             called during transmission.This method shall be called after one
*                             Transmit method call to have relevant data within IB Channel.
*
*   Parameters in           : Channel: Channel ID.
*
*   Parameters inout        : None.
*
*   Parameters out          : DataBufferPointer: Pointer to destination data buffer in RAM.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK: read command has been accepted.
*                             E_NOT_OK: read command has not been accepted.
*
*   Preconditions           : Spi driver must be initialized and pre-compile parameter
*                             SPI_CHANNEL_BUFFERS_ALLOWED shall be SPI_USAGE0 or SPI_USAGE2.
*
*   AUTOSAR_Requirement     : SWS_Spi_00179 SWS_Spi_00312 SWS_Spi_00315 SWS_Spi_00016 SWS_Spi_00027
                              SWS_Spi_00085 SWS_Spi_00004 SWS_Spi_00031 SWS_Spi_00313 SWS_Spi_00314
                              SWS_Spi_00138
****************************************************************************************************/
/* #Violation: Spi_c_REF_3 */
FUNC(Std_ReturnType, SPI_PUBLIC_CODE) Spi_ReadIB
(
    Spi_ChannelType Channel,
    /* #Violation: Spi_c_REF_9 */
    P2VAR(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) DataBufferPtr
)
{
    Mcal_CoreType                   CoreId;
    Std_ReturnType                  RetStatus;
    uint32                          DataIndex;
    const Spi_ChannelConfigType     *ChannelCfgPtr;

    /* Get core id which is executing currently */
    /* #Violation: Spi_c_REF_1 */
    CoreId = Mcal_GetCoreId(); 
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Get Channel DET diagnostic results */
    RetStatus = Spi_GetChannelDetStatus(CoreId, SPI_SID_READIB, Channel);
    /* Check whether the data receiving buffer is 'NULL_PTR' */
    if((E_OK == RetStatus) && (NULL_PTR == DataBufferPtr))
    {
        /* SWS_Spi_00004: API service called with wrong parameter */
        (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_READIB,
                                SPI_E_PARAM_CHANNEL);
        RetStatus = E_NOT_OK;
    }
    if(E_OK == RetStatus)
#else
    /* Reset API execution status variables */
    RetStatus = E_OK;
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /*  SWS_Spi_00004: API service called with wrong Channel parameter */
        /*  SWS_Spi_00031:
            The API parameter Channel shall have a value within the defined channels in the
            initialization data structure, and the correct type of channel (IB or EB) has to be
            used with services. Related error value: SPI_E_PARAM_CHANNEL. Otherwise, the service
            is not done and the return value shall be E_NOT_OK.
        */
        /* Get Channel configuration information structure pointer */
        /* #Violation: Spi_c_REF_1 */
        ChannelCfgPtr = SPI_CH_CONFIGPTR(CoreId, Channel); 
        if(SPI_IB != ChannelCfgPtr->ChannelType)
        {
            RetStatus = E_NOT_OK;
#if (SPI_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_READIB,
                                    SPI_E_PARAM_CHANNEL);
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
        }
        else
        {
            /* Entering write internal buffer critical protection */
            SPI_ENTER_CRITICAL_SECTION(ReadIB);
            /* Copy Channel internal RX buffer to user-specified RX buffer */
            for (DataIndex = 0UL; DataIndex < (((uint32)ChannelCfgPtr->DataLength) *
                                        ((uint32)ChannelCfgPtr->FrameWidth)); DataIndex++)
            {
                /* Update the receive buffer value */
                DataBufferPtr[DataIndex] = ChannelCfgPtr->BufferDescriptorPtr->RXBuffPtr[DataIndex];
            }
            /* Exit write internal buffer critical protection */
            SPI_EXIT_CRITICAL_SECTION(ReadIB);
        }
    }

    /*  SWS_Spi_00313:
        The function Spi_ReadIB return values E_OK: read command has been accepted.
        SWS_Spi_00314:
        The function Spi_ReadIB return values E_NOT_OK: read command has not been accepted.
    */
    return RetStatus;
}
#endif /* ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE0) \|| (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE2)) */

/*  SWS_Spi_00139:
    The function Spi_SetupEB is pre-compile time configurable by the parameter
    SpiChannelBuffersAllowed. This function is only relevant for Channels with EB.
*/
#if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE1) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE2))
/****************************************************************************************************
*   Function Name           : Spi_SetupEB
*
*   Service ID              : 0x05
*
*   Description             : Service to setup the buffers and the length of data for the EB SPI
*                             Handler/Driver Channel specified. This service shall update the buffer
*                             pointers and length attributes of the specified Channel with the
*                             provided values. As these attributes are persistent, they will be used
*                             for all succeeding calls to one Transmit method (for the specified
*                             Channel). To transmit a variable number of data, it is mandatory to
*                             call Spi_SetupBuffers function to store new parameters within SPI
*                             Handler/Driver before each Spi_Transmit function calls.To transmit a
*                             constant number of data, it is only mandatory to call Spi_SetupBuffers
*                             function to store parameters within SPI Handler/Driver before the
*                             first Spi_Transmit function call.For EB Channels the application shall
*                             provide the buffering,and shall take care of the consistency of the
*                             data in the buffer during transmission. The size of the Channel buffer
*                             is either fixed or variable.A maximum size for the Channel buffer is
*                             fixed by configuration,but the size of the buffer provided by the User
*                             can change. In case of 16 bit Channel Data Width, The SrcDataBufferPtr
*                             and DesDataBufferPtr must be 16bit aligned. Different Jobs,
*                             consequently also Sequences, can have in common Channels. But the use
*                             of those shared Channels is restricted. Read and Write functions can
*                             not guarantee the data integrity while Channel data is being
*                             transmitted. User must ensure that Read and/or Write functions are not
*                             called during transmission. This method shall be called one time for
*                             all Channels with EB declared before to call a Transmit method for them
*
*   Parameters in           : Channel: Channel ID.
*                             SrcDataBufferPtr: Pointer to source data buffer.
*                             DesDataBufferPtr: Pointer to destination data buffer in RAM.
*                             Length: Length (number of data elements) of the data to be transmitted
*                             from SrcDataBufferPtr and/or received from DesDataBufferPtr
*
*   Parameters inout        : None.
*
*   Parameters out          : DataBufferPointer: Pointer to destination data buffer in RAM.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK: Setup command has been accepted.
*                             E_NOT_OK: Setup command has not been accepted.
*
*   Preconditions           : Spi driver must be initialized and pre-compile parameter
*                             SPI_CHANNEL_BUFFERS_ALLOWED shall be SPI_USAGE0 or SPI_USAGE2.
*
*   AUTOSAR_Requirement     : SWS_Spi_00180 SWS_Spi_00316 SWS_Spi_00318 SWS_Spi_00058 SWS_Spi_00067
                              SWS_Spi_00037 SWS_Spi_00085 SWS_Spi_00112 SWS_Spi_00060 SWS_Spi_00240
                              SWS_Spi_00258 SWS_Spi_00004 SWS_Spi_00031 SWS_Spi_00077 SWS_Spi_00078
                              SWS_Spi_00317 SWS_Spi_00139
****************************************************************************************************/
/* #Violation: Spi_c_REF_3 */
FUNC(Std_ReturnType, SPI_PUBLIC_CODE) Spi_SetupEB
(
    Spi_ChannelType Channel,
    /* #Violation: Spi_c_REF_9 */
    P2CONST(Spi_DataBufferType, AUTOMATIC, SPI_APPL_CONST) SrcDataBufferPtr,
    /* #Violation: Spi_c_REF_9 */
    P2VAR(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) DesDataBufferPtr,
    Spi_NumberOfDataType Length
)
{
    Mcal_CoreType                   CoreId;
    Std_ReturnType                  RetStatus;
    const Spi_ChannelConfigType     *ChannelCfgPtr;

    /* Get core id which is executing currently */
    /* #Violation: Spi_c_REF_1 */
    CoreId = Mcal_GetCoreId(); 
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Get Channel DET diagnostic results */
    RetStatus = Spi_GetChannelDetStatus(CoreId, SPI_SID_SETUPEB, Channel);
    if(E_OK == RetStatus)
#else
    RetStatus = E_OK;
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /*  SWS_Spi_00112:
            The size of the Channel buffer is either fixed or variable. A maximum size for the Channel
            buffer shall be defined by the configuration.
            SWS_Spi_00060:
            The API parameter Length of data shall have a value within the specified buffer maximum value.
            Related error value: SPI_E_PARAM_LENGTH.
            SWS_Spi_00240:
            API service called with wrong Lenth parameter
        */
        /* Get Channel configuration information structure pointer */
        /* #Violation: Spi_c_REF_1 */
        ChannelCfgPtr = SPI_CH_CONFIGPTR(CoreId, Channel); 
        if((0U == Length) || (Length > ChannelCfgPtr->DataLength))
        {
            /*  SWS_Spi_00258:
                If the API parameter Length related service is not done and the return value shall be
                E_NOT_OK.
            */
            RetStatus = E_NOT_OK;
#if (SPI_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_SETUPEB,
                                    SPI_E_PARAM_LENGTH);
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
        }
        /*  SWS_Spi_00004: API service called with wrong Channel parameter */
        /*  SWS_Spi_00031:
            The API parameter Channel shall have a value within the defined channels in the
            initialization data structure, and the correct type of channel (IB or EB) has to be
            used with services. Related error value: SPI_E_PARAM_CHANNEL. Otherwise, the service
            is not done and the return value shall be E_NOT_OK.
        */
        else if(SPI_EB != ChannelCfgPtr->ChannelType)
        {
            RetStatus = E_NOT_OK;
    #if (SPI_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_SETUPEB,
                                    SPI_E_PARAM_CHANNEL);
    #endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
        }
        else
        {
            /* Entering write internal buffer critical protection */
            SPI_ENTER_CRITICAL_SECTION(SetupEB);
            /* The user data buffer points to the internal TX buffer */
            /*  SWS_Spi_00077:
                To transmit a variable number of data, it is mandatory to call the Spi_SetupEB
                function to store new parameters within SPI Handler/Driver before each
                Spi_AsyncTransmit function call.
                SWS_Spi_00078:
                To transmit a constant number of data, it is only mandatory to call the Spi_SetupEB
                function to store parameters within SPI Handler/Driver before the first
                Spi_AsyncTransmit function call.
            */
            /* #Violation: Spi_c_REF_6 */
            /* #Violation: Spi_c_REF_10 */
            ChannelCfgPtr->BufferDescriptorPtr->TXBuffPtr = (Spi_DataBufferType *)SrcDataBufferPtr;
            /* The user-specified RX buffer points to the SPI driver internal RX buffer */
            ChannelCfgPtr->BufferDescriptorPtr->RXBuffPtr = DesDataBufferPtr;
            /* Calculate actual number of bytes to be transmitted */
            *(ChannelCfgPtr->ActualDataLengthPtr) = Length;
            /* Exit write internal buffer critical protection */
            SPI_EXIT_CRITICAL_SECTION(SetupEB);
        }
    }

    /*  SWS_Spi_00317:
        Return values of the function Spi_SetupEB are E_OK: Setup command has been accepted
        and E_NOT_OK: Setup command has not been accepted.
    */
    return RetStatus;
}
#endif /* ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE1) \|| (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE2)) */

/****************************************************************************************************
*   Function Name           : Spi_GetStatus
*
*   Service ID              : 0x06
*
*   Description             : Service returns the SPI Handler/Driver software module RetStatus.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : SPI_UNINIT: Spi is uninitialized
*                             SPI_IDLE: Spi is idle
*                             SPI_BUSY: Spi is busy
*
*   Preconditions           : Spi driver must be initialized.
*
*   AUTOSAR_Requirement     : SWS_Spi_00181 SWS_Spi_00259 SWS_Spi_00319 SWS_Spi_00346 SWS_Spi_00288
                              SWS_Spi_00345 SWS_Spi_00347 SWS_Spi_00320 SWS_Spi_00025
****************************************************************************************************/
/* #Violation: Spi_c_REF_3 */ 
FUNC(Spi_StatusType, SPI_PUBLIC_CODE) Spi_GetStatus
(
    void
)
{
    Mcal_CoreType                   CoreId;
    Spi_StatusType                  SpiStatus;
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType                  RetStatus;
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */

    /*  SWS_Spi_00288:
        If PhyUnit related service is not done and the return value shall be SPI_UNINIT.
        SWS_Spi_00345:
        API service Spi_GetStatus shall return SPI_UNINIT when the SPI Handler/Driver is
        not initialized or not usable.
    */
    SpiStatus = SPI_UNINIT;
    /* Get core id which is executing currently */
    /* #Violation: Spi_c_REF_1 */
    CoreId = Mcal_GetCoreId(); 

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Get basic DET diagnostic results */
    RetStatus = Spi_GetCommonDetStatus(CoreId, SPI_SID_GETSTATUS);
    if(E_OK == RetStatus)
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Enter GetStatus transmission critical protection */
        SPI_ENTER_CRITICAL_SECTION(GetStatus);
        SpiStatus = Spi_GetDriverStatus(CoreId);
        /* Exit GetStatus transmission critical protection */
        SPI_EXIT_CRITICAL_SECTION(GetStatus);
    }

    /*  SWS_Spi_00320:
        The function Spi_GetStatus returns the SPI Handler/Driver software module status.
        SWS_Spi_00025:
        The function Spi_GetStatus shall return the SPI Handler/Driver software module status.
    */
    return SpiStatus;
}

/****************************************************************************************************
*   Function Name           : Spi_GetJobResult
*
*   Service ID              : 0x07
*
*   Description             : This service returns the last transmission result of the specified Job.
*
*   Parameters in           : Job: Job ID. An invalid job ID will return an undefined result.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : SPI_JOB_OK: Job is completed.
*                             SPI_JOB_PENDING: Job is pending.
*                             SPI_JOB_FAILED: Job is failed.
*
*   Preconditions           : Spi driver must be initialized.
*
*   AUTOSAR_Requirement     : SWS_Spi_00182 SWS_Spi_00062 SWS_Spi_00261 SWS_Spi_00321 SWS_Spi_00038
                              SWS_Spi_00085 SWS_Spi_00254 SWS_Spi_00350 SWS_Spi_00322 SWS_Spi_00026
****************************************************************************************************/
/* #Violation: Spi_c_REF_3 */
FUNC(Spi_JobResultType, SPI_PUBLIC_CODE) Spi_GetJobResult
(
    Spi_JobType Job
)
{
    Mcal_CoreType        CoreId;
    Spi_JobResultType    JobResult;
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType       RetStatus;
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */

    /*  SWS_Spi_00254:
        If the Sequence and Job related service is not done and, depending on services,
        either the return value shall be E_NOT_OK or a failed result (SPI_JOB_FAILED or
        SPI_SEQ_FAILED).
    */
    /* Update the job status to 'SPI_JOB_FAILED' */
    JobResult = SPI_JOB_FAILED;
    /* Get core id which is executing currently */
    /* #Violation: Spi_c_REF_1 */
    CoreId = Mcal_GetCoreId(); 

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Get Job DET diagnostic results */
    RetStatus = Spi_GetJobDetStatus(CoreId, SPI_SID_GETJOBRESULT, Job);
    if(E_OK == RetStatus)
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /*  SWS_Spi_00350:
            The function Spi_GetJobResult shall return SPI_JOB_OK when the last transmission of the
            Job has been finished successfully.
        */
        /* Get Job status information, the input parameter is the Job ID */
        /* #Violation: Spi_c_REF_1 */
        JobResult = SPI_JOB_STATUS(CoreId, Job); 
    }

    /*  SWS_Spi_00322 SWS_Spi_00026:
        The function Spi_GetJobResult shall return the last transmission result of the specified Job.
    */
    return JobResult;
}

/****************************************************************************************************
*   Function Name           : Spi_GetSequenceResult
*
*   Service ID              : 0x08
*
*   Description             : This service returns the last transmission result of the specified
*                             Sequence.
*
*   Parameters in           : Sequence: Sequence ID. An invalid sequence ID will return an undefined
*                             result.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : SPI_SEQ_OK: Sequence is completed.
*                             SPI_SEQ_PENDING: Sequence is pending.
*                             SPI_SEQ_FAILED: Sequence is failed.
*                             SPI_SEQ_CANCELLED: Sequence is cancelled.
*
*   Preconditions           : Spi driver must be initialized.
*
*   AUTOSAR_Requirement     : SWS_Spi_00183 SWS_Spi_00351 SWS_Spi_00251 SWS_Spi_00323 SWS_Spi_00042
                              SWS_Spi_00085 SWS_Spi_00254 SWS_Spi_00324 SWS_Spi_00039
****************************************************************************************************/
/* #Violation: Spi_c_REF_3 */
FUNC(Spi_SeqResultType, SPI_PUBLIC_CODE) Spi_GetSequenceResult
(
    Spi_SequenceType Sequence
)
{
    Mcal_CoreType        CoreId;
    Spi_SeqResultType    SeqResult;
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType       RetStatus;
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */

    /*  SWS_Spi_00254:
        If the Sequence and Job related service is not done and, depending on services,
        either the return value shall be E_NOT_OK or a failed result (SPI_JOB_FAILED or
        SPI_SEQ_FAILED).
    */
    /* Update the Sequence status to 'SPI_SEQ_FAILED' */
    SeqResult = SPI_SEQ_FAILED;
    /* Get core id which is executing currently */
    /* #Violation: Spi_c_REF_1 */
    CoreId = Mcal_GetCoreId(); 

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Get Sequence DET diagnostic results */
    RetStatus = Spi_GetSeqDetStatus(CoreId, SPI_SID_GETSEQUENCERESULT, Sequence);
    if(E_OK == RetStatus)
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Get Sequence status information, the input parameter is the Sequence ID */
        /* #Violation: Spi_c_REF_1 */
        SeqResult = SPI_SEQ_STATUS(CoreId, Sequence); 
    }
    /*  SWS_Spi_00324 SWS_Spi_00039:
        The function Spi_GetSequenceResult shall return the last transmission result of
        the specified Sequence.
    */
    return SeqResult;
}

#if (SPI_VERSION_INFO_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Spi_GetVersionInfo
*
*   Service ID              : 0x09
*
*   Description             : This service returns the version information of this module.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : VersionInfoPtr: Pointer to where to store the version information of
*                             this module.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Spi_00184 SWS_Spi_00325
****************************************************************************************************/
/* #Violation: Spi_c_REF_3 */
FUNC(void, SPI_PUBLIC_CODE) Spi_GetVersionInfo
(
    /* #Violation: Spi_c_REF_9 */
    P2VAR(Std_VersionInfoType, AUTOMATIC, SPI_APPL_DATA) VersionInfoPtr
)
{
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /*  SWS_Spi_00371:
        If Det is enabled, the parameter versioninfo shall be checked for being NULL. The error
        SPI_E_PARAM_POINTER shall be reported in case the value is a NULL pointer.
    */
    if(NULL_PTR == VersionInfoPtr)
    {
        (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_GETVERSIONINFO,
                              SPI_E_PARAM_POINTER);
    }
    else
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
    {

        VersionInfoPtr->vendorID = (uint16)SPI_VENDOR_ID;
        VersionInfoPtr->moduleID = (uint16)SPI_MODULE_ID;
        VersionInfoPtr->sw_major_version = (uint8)SPI_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = (uint8)SPI_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = (uint8)SPI_SW_PATCH_VERSION;
    }
}
#endif /* (SPI_VERSION_INFO_API  \== STD_ON) */

/*  SWS_Spi_00136:
    The function Spi_SyncTransmit is pre-compile time selectable by the configuration parameter
    SpiLevelDelivered. This function is only relevant for LEVEL 0 and LEVEL 2.
*/
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
/****************************************************************************************************
*   Function Name           : Spi_SyncTransmit
*
*   Service ID              : 0x0A
*
*   Description             : Sync Service to transmit data on the SPI bus. This service shall take
*                             over the given parameter, initiate a transmission, and set the SPI
*                             Handler/Driver status to SPI_BUSY, set the sequence result to
*                             SPI_SEQ_PENDING, set the first job result to SPI_JOB_PENDING and return
*                             The LEVEL 0 SPI Handler/Driver shall offer a synchronous transfer
*                             service for SPI busses. When there is no on-going Sequence transmission
*                             the SPI Handler/Driver shall be in idle state (SPI_IDLE). Hence the
*                             SPI_LEVEL0 SPI Handler/Driver shall not allow transmitting more than one
*                             Sequence at the same time. That means during a Sequence on-going
*                             transmission, all requests to transmit another Sequence shall be
*                             rejected.
*                             The LEVEL 2 SPI Handler/Driver shall offer a synchronous transfer
*                             service for a dedicated SPI bus and it shall also offer an asynchronous
*                             transfer service for others SPI busses. When there is no on-going
*                             Sequence transmission, the SPI Handler/Driver shall be in idle state
*                             (SPI_IDLE).
*
*   Parameters in           : Sequence: Sequence ID.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK: Transmission command has been accepted.
*                             E_NOT_OK: Transmission command has not been accepted.
*
*   Preconditions           : Spi driver must be initialized and pre-compile parameter
*                             SPI_LEVEL_DELIVERED shall be SPI_LEVEL1 or SPI_LEVEL2.
*
*   AUTOSAR_Requirement     : SWS_Spi_00185 SWS_Spi_00327 SWS_Spi_00330 SWS_Spi_00245 SWS_Spi_00035
                              SWS_Spi_00135 SWS_Spi_00353 SWS_Spi_00285 SWS_Spi_00352 SWS_Spi_00384
                              SWS_Spi_00386 SWS_Spi_00254 SWS_Spi_00354 SWS_Spi_00384 SWS_Spi_00385
                              SWS_Spi_00270 SWS_Spi_00073 SWS_Spi_00328 SWS_Spi_00329 SWS_Spi_00136
****************************************************************************************************/
/* #Violation: Spi_c_REF_3 */
FUNC(Std_ReturnType, SPI_PUBLIC_CODE) Spi_SyncTransmit
(
    Spi_SequenceType Sequence
)
{
    Mcal_CoreType                   CoreId;
    boolean                         RetResult;
    Std_ReturnType                  RetStatus;
    Spi_JobType                     JobIndex;
    const Spi_JobConfigType         *JobCfgPtr;
    const Spi_SequenceConfigType    *SeqCfgPtr;
#if (SPI_DEV_ERROR_DETECT == STD_ON)
#if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE1) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE2))
    Spi_ChannelType                 ChannelIndex;
    const Spi_ChannelConfigType     *ChannelCfgPtr;
#endif /* ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE1) \|| (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE2)) */
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
    uint8                           ErrorFlag;
    
    ErrorFlag = 0U;
    RetResult = TRUE;
    /* Get core id which is executing currently */
    /* #Violation: Spi_c_REF_1 */
    CoreId = Mcal_GetCoreId(); 
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Get Sequence DET diagnostic results */
    RetStatus = Spi_GetSeqDetStatus(CoreId, SPI_SID_SYNCTRANSMIT, Sequence);
    if(E_OK == RetStatus)
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
    {
        RetStatus = E_OK;
        /* Get Sequence configuration information structure pointer */
        /* #Violation: Spi_c_REF_1 */
        SeqCfgPtr = SPI_SEQ_CONFIGPTR(CoreId, Sequence); 
        /*  SWS_Spi_00245:
            Synchronous transmission service called at wrong time.
            SWS_Spi_00035
            When the function Spi_SyncTransmit is called while a se-quence is on transmission and
            SPI_SUPPORT_CONCURRENT_SYNC_TRANSMIT is disabled or another sequence is on
            transmition on same bus, the SPI Handler/Driver shall not take into account this new
            transmission request and the function shall return the value E_NOT_OK
            (see [SWS_Spi_00114]). In this case and according to [SWS_BSW_00042] and
            [SWS_BSW_00045], the SPI Handler/Driver shall report the SPI_E_SEQ_IN_PROCESS error.)
            SWS_Spi_00135:
            When the function Spi_SyncTransmit is called while a sequence is on transmission and SPI_SUPPORT_CONCURRENT_SYNC_TRANSMIT is disabled or another sequence is on
            transmition on same bus, the SPI Handler/Driver shall not take into account this new
            transmission request and the function shall return the value E_NOT_OK
            (see [SWS_Spi_00114]). In this case and according to [SWS_Spi_00100],
            the SPI Handler/Driver shall report the SPI_E_SEQ_IN_PROCESS error.
        */
        /* Enter synchronous transmission critical protection */
        SPI_ENTER_CRITICAL_SECTION(SyncTransmit);
        /* Check if there are HW units already running */
        if(0U ==
            (SeqCfgPtr->MaskSeqUsedPhyUnit & *(Spi_CoreStatus[CoreId]->PhyUnitBusySyncStatusPtr)))
        {
            /* SWS_Spi_00245: Synchronous transmission service called at wrong time. */
            /* DET check Jobs in the current Sequence */
            for(JobIndex = 0U; ((E_OK == RetStatus) && (JobIndex < SeqCfgPtr->NumJobs)); JobIndex++)
            {
                /* Get Job configuration information structure pointer */
                /* #Violation: Spi_c_REF_1 */
                JobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, SeqCfgPtr->JobIndexListPtr[JobIndex]); 
                /* SWS_Spi_00245: Synchronous transmission service called at wrong time. */
                /* Check whether the hardware used by the job is Busy, also for a cancelled Sequence:
                   its last started Job may still be transmitted */
                /* #Violation: Spi_c_REF_1 */
                if (SPI_BUSY == SPI_HWUNIT_STATUS(CoreId, JobCfgPtr->SpiNumber))
                {
                    ErrorFlag = SPI_E_SEQ_IN_PROCESS;
                    RetStatus = E_NOT_OK;
                }
    #if (SPI_DEV_ERROR_DETECT == STD_ON)
    #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE1) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE2))
                /* Check the external buffer used by the current Sequence (EB)*/
                for(ChannelIndex = 0U;((E_OK == RetStatus) &&
                                        (ChannelIndex < JobCfgPtr->NumChannels)); ChannelIndex++)
                {
                    /* Get Channel configuration information structure pointer */
                    /* #Violation: Spi_c_REF_1 */
                    ChannelCfgPtr = SPI_CH_CONFIGPTR(CoreId, JobCfgPtr->ChannelIndexListPtr[ChannelIndex]); 
                    /* Check whether the Channel buffer type is 'EB' && data length is '0U' (Spi_SetupEB
                       not called), the same as in Spi_AsyncTransmit. The data length of IB Channels
                       is checked by Spi_CheckSeqDataLength (SPI_E_PARAM_LENGTH). */
                    if ((SPI_EB == ChannelCfgPtr->ChannelType) &&
                        (0U == *(ChannelCfgPtr->ActualDataLengthPtr)))
                    {
                        ErrorFlag = SPI_E_PARAM_EB_UNIT;
                        RetStatus = E_NOT_OK;
                    }
                }
    #endif /* ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE1) \|| (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_USAGE2)) */
    #endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
            }
        }
        else
        {
            ErrorFlag = SPI_E_SEQ_IN_PROCESS;
            RetStatus = E_NOT_OK;
        }
        /* Exit synchronous transmission critical protection */
        SPI_EXIT_CRITICAL_SECTION(SyncTransmit);

        if(SPI_E_SEQ_IN_PROCESS == ErrorFlag)
        {
            (void)Det_ReportRuntimeError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_SYNCTRANSMIT,
                                        SPI_E_SEQ_IN_PROCESS);
        }
#if (SPI_DEV_ERROR_DETECT == STD_ON)
        else if(SPI_E_PARAM_EB_UNIT == ErrorFlag)
        {
            (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID,
                                        SPI_SID_SYNCTRANSMIT, SPI_E_PARAM_EB_UNIT);
        }
        else
        /* #Violation: Spi_c_REF_2 */ 
        {
            /* Do Nothing */
        }
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
    }
    if(E_OK == RetStatus)
    {
        /*  SWS_Spi_00060:
            Check the data length of all Jobs before any state is changed. This check does not
            depend on SPI_DEV_ERROR_DETECT: a Job with an invalid data length can never be
            transmitted.
        */
        RetStatus = Spi_CheckSeqDataLength(CoreId, Sequence);
#if (SPI_DEV_ERROR_DETECT == STD_ON)
        if (E_NOT_OK == RetStatus)
        {
            (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_SYNCTRANSMIT,
                                    SPI_E_PARAM_LENGTH);
        }
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
    }
    if(E_OK == RetStatus)
    {
        /* Enter synchronous transmission critical protection */
        SPI_ENTER_CRITICAL_SECTION(SyncTransmit);
        /*  The HW units have been checked above in a separate critical section. Check them again
            together with their reservation: an asynchronous Job may have been started on them in
            the meantime.
        */
        RetStatus = Spi_SyncCheckPhyUnitsFree(CoreId, Sequence);
        if (E_OK == RetStatus)
        {
            /* Update the Sequence status to 'SPI_SEQ_PENDING' */
            /*  SWS_Spi_00353:
                Spi_GetSequenceResult function shall return SPI_SEQ_PENDING when the SPI
                Handler/Driver is performing a SPI Sequence. The meaning of this status
                is equal to SPI_BUSY.
                SWS_Spi_00285:
                When the function Spi_SyncTransmit is called, shall take over the given
                parameter and set the Sequence status to SPI_SEQ_PENDING can be obtained
                calling the API service Spi_GetSequenceResult.
            */
            /* Get Sequence status information, the input parameter is the Sequence ID */
            /* #Violation: Spi_c_REF_1 */
            SPI_SEQ_STATUS(CoreId, Sequence) = SPI_SEQ_PENDING;
            /* Reserve the used HW units for the whole Sequence, also between its Jobs: an
               asynchronous Job is not started on a reserved HW unit, it is only queued */
            for (JobIndex = 0U; JobIndex < SeqCfgPtr->NumJobs; JobIndex++)
            {
                /* Get Job configuration information structure pointer */
                /* #Violation: Spi_c_REF_1 */
                JobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, SeqCfgPtr->JobIndexListPtr[JobIndex]);
                /* Update PhyUnit transmission occupancy mask to 'Busy' */
                *(Spi_CoreStatus[CoreId]->PhyUnitBusySyncStatusPtr) |=
                                                (uint16)1U << JobCfgPtr->SpiNumber;
                /* Reserve the same PhyUnits until this Sequence's teardown, incl. its end
                   notification, is complete: see PhyUnitPendingTeardownStatusPtr */
                *(Spi_CoreStatus[CoreId]->PhyUnitPendingTeardownStatusPtr) |=
                                                (uint16)1U << JobCfgPtr->SpiNumber;
            }
        }
        /* Exit synchronous transmission critical protection */
        SPI_EXIT_CRITICAL_SECTION(SyncTransmit);
        if (E_NOT_OK == RetStatus)
        {
            /*  SWS_Spi_00135: another sequence is on transmission on the same bus */
            (void)Det_ReportRuntimeError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_SYNCTRANSMIT,
                                        SPI_E_SEQ_IN_PROCESS);
        }
    }
    if(E_OK == RetStatus)
    {
        /* Get Sequence synchronization transmission status */
        RetResult &= Spi_SyncStartTransmit(CoreId, Sequence);
        if (TRUE == RetResult)
        {

            /*  SWS_Spi_00352:
                Spi_GetSequenceResult function shall return SPI_SEQ_OK when the last
                transmission of the Sequence has been finished successfully.
            */
            /* Get Sequence status information, the input parameter is the Sequence ID */
            /* #Violation: Spi_c_REF_1 */
            SPI_SEQ_STATUS(CoreId, Sequence) = SPI_SEQ_OK; 
#if (SPI_DEM_REPORT_ERROR_STATUS == STD_ON)
            /*  SWS_Spi_00384:
                When a hardware error is detected, the SPI Handler/Driver shall stop the
                current sequence, report an error to the DEM as configured and set the
                state of the Job to SPI_JOB_FAILED and the state of the Sequence to
                SPI_SEQ_FAILED.
                SWS_Spi_00386:
                When no error bit inside the SPI transmit status register is set, the SPI
                transmit status register information shall be reported to DEM as
                Dem_SetEventStatus (SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_PASSED)
            */
            /* Report DEM error - hardware error occurred */
            Dem_SetEventStatus(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_PASSED);
#endif /* (SPI_DEM_REPORT_ERROR_STATUS  \== STD_ON) */
        }
        else
        {
            /*  SWS_Spi_00254:
                If the Sequence and Job related service is not done and, depending on
                services, either the return value shall be E_NOT_OK or a failed result
                (SPI_JOB_FAILED or SPI_SEQ_FAILED).
                SWS_Spi_00354:
                Spi_GetSequenceResult function shall return SPI_SEQ_FAILED  when the
                last transmission of the Sequence has failed.
            */
            /* Get Sequence status information, the input parameter is the Sequence ID */
            /* #Violation: Spi_c_REF_1 */
            SPI_SEQ_STATUS(CoreId, Sequence) = SPI_SEQ_FAILED; 
#if (SPI_DEM_REPORT_ERROR_STATUS == STD_ON)
            /*  SWS_Spi_00384:
                When a hardware error is detected, the SPI Handler/Driver shall stop the
                current sequence, report an error to the DEM as configured and set the
                state of the Job to SPI_JOB_FAILED and the state of the Sequence to
                SPI_SEQ_FAILED.
                SWS_Spi_00385:
                When any error bit inside the SPI transmit status register is set, the
                SPI transmit status register information shall be reported to DEM as
                Dem_SetEventStatus (SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED)
            */
            /* Report DEM error - hardware error occurred */
            Dem_SetEventStatus(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif /* (SPI_DEM_REPORT_ERROR_STATUS  \== STD_ON) */
        }
        /* set used HW units as idle */
        for (JobIndex = 0U; JobIndex < SeqCfgPtr->NumJobs; JobIndex++)
        {
            /* Get Job configuration information structure pointer */
            /* #Violation: Spi_c_REF_1 */
            JobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, SeqCfgPtr->JobIndexListPtr[JobIndex]); 
            /* Enter synchronous transmission critical protection */
            SPI_ENTER_CRITICAL_SECTION(SyncTransmit);
            /* Update PhyUnit transmission occupancy mask to 'IDLE' */
            *(Spi_CoreStatus[CoreId]->PhyUnitBusySyncStatusPtr) &=
                                        (~((uint16)1U << JobCfgPtr->SpiNumber));
            /* Exit synchronous transmission critical protection */
            SPI_EXIT_CRITICAL_SECTION(SyncTransmit);
#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
            /* Start the asynchronous Jobs queued while the HW unit was reserved. The HW unit is only
               scheduled if it is still IDLE: if several Jobs of the Sequence use the same HW unit,
               only the first call starts a queued Job. */
            RetResult &= Spi_AsyncScheduleNextJob(CoreId, JobCfgPtr->JobId, TRUE);
#endif /* SPI_LEVEL_DELIVERED \== SPI_LEVEL2 */
        }
        /*  SWS_Spi_00270:
            In case call end notification function and rescheduling are fully done by
            software, the order between these shall be first scheduling and then the
            call of end notification function executed.
            SWS_Spi_00073:
            If the SpiSeqEndNotification is configured (i.e. not a null pointer), the SPI
            Handler/Driver shall call the configured callback notification at the end of a
            Sequence transmission.
        */
        if (NULL_PTR != SeqCfgPtr->SeqEndNotificationPtr)
        {
            /* Call Sequence transfer end notification function */
            SeqCfgPtr->SeqEndNotificationPtr();
        }
        /* The Sequence's teardown, incl. its end notification, is now complete: release its
           whole-Sequence PhyUnit reservation. See PhyUnitPendingTeardownStatusPtr: unlike
           PhyUnitBusySyncStatusPtr above, this is cleared only now, not before rescheduling
           and the notification, so busy-detection stays accurate until here. */
        for (JobIndex = 0U; JobIndex < SeqCfgPtr->NumJobs; JobIndex++)
        {
            /* Get Job configuration information structure pointer */
            /* #Violation: Spi_c_REF_1 */
            JobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, SeqCfgPtr->JobIndexListPtr[JobIndex]);
            /* Enter synchronous transmission critical protection */
            SPI_ENTER_CRITICAL_SECTION(SyncTransmit);
            *(Spi_CoreStatus[CoreId]->PhyUnitPendingTeardownStatusPtr) &=
                                        (~((uint16)1U << JobCfgPtr->SpiNumber));
            /* Exit synchronous transmission critical protection */
            SPI_EXIT_CRITICAL_SECTION(SyncTransmit);
        }
    }
    if(FALSE == RetResult)
    {
        RetStatus = E_NOT_OK;
#if (SPI_SAFETY_ENABLE == STD_ON)
        (void)Det_ReportRuntimeError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_SYNCTRANSMIT,
                                        SPI_E_SAFETY_ERROR);
#endif /* (SPI_SAFETY_ENABLE \== STD_ON) */
    }
    /*  SWS_Spi_00328:
        Return value of the function Spi_SyncTransmit is E_OK: when Transmission command has
        been accepted.
        SWS_Spi_00329:
        Return value of the function Spi_SyncTransmit is E_NOT_OK: When Transmission command
        has not been accepted.
    */
    return RetStatus;
}
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */

#if (SPI_HW_STATUS_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Spi_GetHWUnitStatus
*
*   Service ID              : 0x0B
*
*   Description             : This service return the status of the specified SPI Hardware
*                             microcontroller peripheral.The user call this function to know if the
*                             specified SPI Hardware microcontroller peripheral is SPI_IDLE or
*                             SPI_BUSY. Note that the HW Bus is busy only if a Job is running on it.
*                             If the HW Bus is Idle it can be assumed that no job is running on it
*                             currently but a job could be pending and can be scheduled to run on
*                             the bus later.
*
*   Parameters in           : HWUnit: SPI Hardware microcontroller peripheral (unit) ID.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : SPI_UNINIT: Spi is uninitialized
*                             SPI_IDLE: Spi is idle
*                             SPI_BUSY: Spi is busy
*
*   Preconditions           : Spi driver must be initialized and pre-compile parameter
*                             SPI_HW_STATUS_API shall be STD_ON.
*
*   AUTOSAR_Requirement     : SWS_Spi_00186 SWS_Spi_00259 SWS_Spi_00331 SWS_Spi_00287 SWS_Spi_00085
                              SWS_Spi_00288 SWS_Spi_00348 SWS_Spi_00349 SWS_Spi_00332 SWS_Spi_00141
****************************************************************************************************/
/* #Violation: Spi_c_REF_3 */
FUNC(Spi_StatusType, SPI_PUBLIC_CODE) Spi_GetHWUnitStatus
(
    Spi_HWUnitType HWUnit
)
{
    Mcal_CoreType        CoreId;
    Spi_StatusType       PhyUnitStatus;
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType       RetStatus;
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */

    /*  SWS_Spi_00288:
        If PhyUnit related service is not done and the return value shall be SPI_UNINIT.
    */
    PhyUnitStatus = SPI_UNINIT;
    /* Get core id which is executing currently */
    /* #Violation: Spi_c_REF_1 */
    CoreId = Mcal_GetCoreId(); 

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* SPI driver PhyUnit DET check */
    RetStatus = Spi_GetPhyUnitDetStatus(CoreId, SPI_SID_GETHWUNITSTATUS, HWUnit);
    if(E_OK == RetStatus)
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /*  SWS_Spi_00348:
            Spi_GetHWUnitStatus function shall return SPI_IDLE when The SPI Hardware microcontroller
            peripheral is not currently transmitting any Job
            SWS_Spi_00349:
            Spi_GetHWUnitStatus function shall return SPI_BUSY when The SPI Hardware microcontroller
            peripheral is performing a SPI Job transmit.
        */
        /* Update the PhyUnit status to 'SPI_IDLE' */
        /* #Violation: Spi_c_REF_1 */
        PhyUnitStatus = SPI_HWUNIT_STATUS(CoreId, HWUnit); 
    }
    /*  SWS_Spi_00332 SWS_Spi_00141:
        The function Spi_GetHWUnitStatus service returns the status of the specified SPI Hardware
        microcontroller peripheral.
    */
    return PhyUnitStatus;
}
#endif /* (SPI_HW_STATUS_API  \== STD_ON) */

#if (SPI_CANCEL_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Spi_Cancel
*
*   Service ID              : 0x0C
*
*   Description             : This service cancel the specified on-going sequence transmission.
*                             without canceling any Job transmission and the SPI Handler/Driver
*                             will set the sequence result to SPI_SEQ_CANCELLED.The SPI Handler
*                             Driver is not responsible on external devices damages or undefined
*                             state due to canceling a sequence transmission. It is up to the user
*                             to be aware of what user is doing!
*                             Only an on-going asynchronous Sequence is cancelled: the result of a
*                             finished Sequence is kept and a synchronous Sequence can not be
*                             cancelled. A Job of the cancelled Sequence which has not been started
*                             yet is not started any more (SWS_Spi_00145).
*
*   Parameters in           : Sequence: Sequence ID.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Spi driver must be initialized and pre-compile parameter
*                             SPI_CANCEL_API shall be STD_ON.
*
*   AUTOSAR_Requirement     : SWS_Spi_00187 SWS_Spi_00333 SWS_Spi_00334 SWS_Spi_00085 SWS_Spi_00144
****************************************************************************************************/
/* #Violation: Spi_c_REF_3 */
FUNC(void, SPI_PUBLIC_CODE) Spi_Cancel
(
    Spi_SequenceType Sequence
)
{
    Mcal_CoreType                   CoreId;
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType                  RetStatus;
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
    Spi_SequenceStateType           *SeqStatePtr;
    const Spi_JobConfigType         *LastJobCfgPtr;
    const Spi_SequenceConfigType    *SeqCfgPtr;
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */

    /* Get core id which is executing currently */
    /* #Violation: Spi_c_REF_1 */
    CoreId = Mcal_GetCoreId(); 

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Get Sequence DET diagnostic results */
    RetStatus = Spi_GetSeqDetStatus(CoreId, SPI_SID_CANCEL, Sequence);
    if(E_OK == RetStatus)
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /*  SWS_Spi_00144:
            The function Spi_Cancel shall cancel the specified on-going sequence transmission
            without cancelling any Job transmission and set the sequence result to SPI_SEQ_CANCELLED.
        */
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
        /* Get Sequence configuration information structure pointer */
        /* #Violation: Spi_c_REF_1 */
        SeqCfgPtr = SPI_SEQ_CONFIGPTR(CoreId, Sequence);
        /* Get Sequence status information structure pointer */
        /* #Violation: Spi_c_REF_1 */
        SeqStatePtr = SPI_SEQ_STATUSPTR(CoreId, Sequence);
        /* Enter asynchronous transmission critical protection */
        SPI_ENTER_CRITICAL_SECTION(AsyncTransmit);
        /*  Only an on-going asynchronous Sequence is cancelled: it is pending and its last Job is still
            linked to it (Spi_AsyncTransmit links all Jobs, each finished Job is unlinked). The result
            of a finished Sequence is kept, and a synchronous Sequence, whose Jobs are not linked,
            can not be cancelled.
        */
        if ((SPI_SEQ_PENDING == SeqStatePtr->SeqResult) && (0U < SeqCfgPtr->NumJobs))
        {
            /* Get the configuration of the last Job in the Sequence */
            /* #Violation: Spi_c_REF_1 */
            LastJobCfgPtr = SPI_JOB_CONFIGPTR(CoreId, SeqCfgPtr->JobIndexListPtr[SeqCfgPtr->NumJobs - 1U]);
            if (SeqStatePtr == LastJobCfgPtr->JobStatePtr->AsyncSeqStatePtr)
            {
                SeqStatePtr->SeqResult = SPI_SEQ_CANCELLED;
            }
        }
        /* Exit asynchronous transmission critical protection */
        SPI_EXIT_CRITICAL_SECTION(AsyncTransmit);
#else
        /* LEVEL0: only synchronous Sequences exist, they can not be cancelled */
        MCAL_UNUSED_VAR(CoreId);
        MCAL_UNUSED_VAR(Sequence);
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */
    }
}
#endif /* (SPI_CANCEL_API  \== STD_ON) */

/*  SWS_Spi_00154:
    The function Spi_SetAsyncMode is pre-compile time selectable by the configuration parameter
    SpiLevelDelivered. This function is only relevant for LEVEL 2.
*/
#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
/****************************************************************************************************
*   Function Name           : Spi_SetAsyncMode
*
*   Service ID              : 0x0D
*
*   Description             : This function is pre-compile time selectable by the configuration
*                             parameter: SPI_LEVEL_DELIVERED. This function is only relevant for
*                             LEVEL 2 and implemented with one polling mechanism mode and one with
*                             interrupt mechanism mode for SPI busses handled asynchronously.
*                             Both mechanisms are selectable during execution time.
*
*   Parameters in           : Mode: New Asynchronous transfer mode.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : E_OK: Setting command has been done.
*                             E_NOT_OK: setting command has not been accepted.
*
*   Preconditions           : Spi driver must be initialized and pre-compile parameter
*                             SPI_LEVEL_DELIVERED shall be SPI_LEVEL2.
*
*   AUTOSAR_Requirement     : SWS_Spi_00188 SWS_Spi_00156 SWS_Spi_00360 SWS_Spi_00361 SWS_Spi_00362
                              SWS_Spi_00335 SWS_Spi_00338 SWS_Spi_00152 SWS_Spi_00172 SWS_Spi_00243
                              SWS_Spi_00171 SWS_Spi_00336 SWS_Spi_00337 SWS_Spi_00154
****************************************************************************************************/
/* #Violation: Spi_c_REF_3 */
FUNC(Std_ReturnType, SPI_PUBLIC_CODE) Spi_SetAsyncMode
(
    Spi_AsyncModeType   Mode
)
{
    Mcal_CoreType                   CoreId;
    Std_ReturnType                  RetStatus;
    Spi_StatusType                  SpiStatus;
#if (SPI_ENABLE_DMA == STD_ON)
    Spi_HWUnitType                  PhyUnitIndex;
    const Spi_CoreConfigType        *CurrentCoreConfigPtr;
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */

    /* Get core id which is executing currently */
    /* #Violation: Spi_c_REF_1 */
    CoreId = Mcal_GetCoreId(); 
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Get basic DET diagnostic results */
    RetStatus = Spi_GetCommonDetStatus(CoreId, SPI_SID_SETASYNCMODE);
    if(E_OK == RetStatus)
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Enter SetAsyncMode transmission critical protection */
        SPI_ENTER_CRITICAL_SECTION(SetAsyncMode);
        /* Get asynchronous hardware unit execution status */
        SpiStatus = Spi_AsyncGetPhyUnitStatus(CoreId);
        /* Exit SetAsyncMode transmission critical protection */
        SPI_EXIT_CRITICAL_SECTION(SetAsyncMode);
        /*  SWS_Spi_00243:
            API services called in a wrong sequence(Pending)
            SWS_Spi_00171:
            If the function Spi_SetAsyncMode is called while the SPI Handler/Driver status is
            SPI_BUSY and an asynchronous transmition is in progress, the SPI Handler/Driver
            shall not change the AsyncModeType and keep the mode type as it is. The function
            shall return the value E_NOT_OK.
        */
        if(SPI_BUSY == SpiStatus)
        {
            RetStatus = E_NOT_OK;
            (void)Det_ReportRuntimeError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_SETASYNCMODE,
                                    SPI_E_SEQ_PENDING);
        }
        else
        {
            /* Update Asynchronous Transfer Mode */
            /* #Violation: Spi_c_REF_1 */
            SPI_ASYNC_MODE(CoreId) = Mode; 
#if (SPI_ENABLE_DMA == STD_ON)
            /* Get Corex configuration information structure pointer */
            CurrentCoreConfigPtr = Spi_ConfigPtr->CoreConfigPtr[CoreId];

            /* Initialize all physical PhyUnits */
            for (PhyUnitIndex = 0U;
                ((PhyUnitIndex < CurrentCoreConfigPtr->MaxPhyUnit));
                PhyUnitIndex++)
            {
                /* Set PhyUnit status flags using DMA */
                if ((SPI_INTERRUPT_MODE == Mode) &&
                    (SPI_DMACHNOUSED_MASK != CurrentCoreConfigPtr->PhyUnitCfgPtr[PhyUnitIndex].TxDmaChannel))
                {
                    Spi_CoreStatus[CoreId]->PhyUnitStatusPtr[PhyUnitIndex].DmaEnable = TRUE;
                }
                else
                {
                    Spi_CoreStatus[CoreId]->PhyUnitStatusPtr[PhyUnitIndex].DmaEnable = FALSE;
                }
            }
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */
            RetStatus = E_OK;
        }
    }
    /*  SWS_Spi_00336:
        Return value of the function Spi_SetAsyncMode is E_OK: Setting command has been done.
        SWS_Spi_00337:
        Return value of the function Spi_SetAsyncMode is E_NOT_OK: setting command has
        not been accepted.
    */
    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Spi_MainFunction_Handling
*
*   Service ID              : 0x10
*
*   Description             : This function replaces the interrupt mechanism used to handle jobs on
*                             the bus. The function polls for the completion of a channel
*                             transmission and calls the function: Spi_AsyncIsrFifoRx.
*                             In addition this function also checks for errors on the SPI bus and
*                             performs the needed error handling (calls Spi_IsrError)
*                             Only HW units occupied by an asynchronous transmission are polled: a HW
*                             unit used by a synchronous Sequence is skipped, and the receive FIFO of
*                             a DMA transfer is not read.
*                             This function also supervises the timeout of the asynchronous transfers:
*                             a transfer which does not progress within SPI_TIMEOUT_US per FIFO round
*                             of at most SPI_AVAILABLE_FIFOLEVEL frames is aborted together with its
*                             Sequence. The supervision runs in SPI_POLLING_MODE and in
*                             SPI_INTERRUPT_MODE, so this function shall be scheduled every
*                             SPI_MAIN_FUNCTION_PERIOD in both modes. In SPI_INTERRUPT_MODE it does
*                             nothing else. An integrator who does not schedule it gets no timeout
*                             supervision, and SPI_LEVEL1 has no main function and is not supervised.
*                             The detection latency is up to SPI_TIMEOUT_US plus one
*                             SPI_MAIN_FUNCTION_PERIOD.
*                             The asynchronous mode is sampled once per hardware unit together with
*                             the state snapshot instead of in the loop condition, so a
*                             Spi_SetAsyncMode called from an end notification no longer aborts the
*                             loop in the middle.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Spi driver must be initialized and pre-compile parameter
*                             SPI_LEVEL_DELIVERED shall be SPI_LEVEL2.
*
*   AUTOSAR_Requirement     : SWS_Spi_00189 SWS_Spi_00155
****************************************************************************************************/
/* #Violation: Spi_c_REF_3 */
FUNC(void, SPI_PUBLIC_CODE) Spi_MainFunction_Handling
(
    void
)
{
#if (SPI_SAFETY_ENABLE == STD_ON)
    boolean                 RetResult;
#endif /* (SPI_SAFETY_ENABLE \== STD_ON) */
    Mcal_CoreType           CoreId;
    Spi_HWUnitType          PhyUnit;
    Spi_HWUnitType          PhyUnitIndex;
    uint32                  IsPollRequest;
    boolean                 IsAsyncBusy;
    Spi_AsyncModeType       AsyncMode;
    uint64                  Deadline;
#if (SPI_ENABLE_DMA == STD_ON)
    boolean                 IsDmaTransfer;
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType          RetStatus;
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */

    /* Get core id which is executing currently */
    /* #Violation: Spi_c_REF_1 */
    CoreId = Mcal_GetCoreId(); 
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Get basic DET diagnostic results */
    RetStatus = Spi_GetCommonDetStatus(CoreId, SPI_SID_MAINFUNCTION_HANDLING);
    if(E_OK == RetStatus)
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
    {
        for (PhyUnitIndex = 0U;
             (PhyUnitIndex < Spi_ConfigPtr->CoreConfigPtr[CoreId]->MaxPhyUnit); PhyUnitIndex++)
        {
            /* Get actually hardware unit ID from the configuration: the current Job of the device
               state is NULL_PTR for a hardware unit which has never been used */
            PhyUnit = Spi_ConfigPtr->CoreConfigPtr[CoreId]->PhyUnitCfgPtr[PhyUnitIndex].SpiNumber;
            IsAsyncBusy = FALSE;
            Deadline = 0ULL;
            /* Take a consistent snapshot of the hardware unit state */
            SPI_ENTER_CRITICAL_SECTION(AsyncTransmit);
            /*  Only a hardware unit occupied by an asynchronous transmission shall be polled. A
                synchronous transmission waits for its own reception and handles its errors in
                Spi_SyncWaitTransFinish: polling it would clear its error flags and read its receive
                FIFO. A synchronous Sequence marks its hardware units in PhyUnitBusySyncStatusPtr for
                the whole Sequence, also between its Jobs.
            */
            if ((SPI_BUSY == Spi_CoreStatus[CoreId]->PhyUnitStatusPtr[PhyUnitIndex].PhyUnitStatus) &&
                (TRUE == Spi_CoreStatus[CoreId]->PhyUnitStatusPtr[PhyUnitIndex].IsAsync) &&
                (0U == (*(Spi_CoreStatus[CoreId]->PhyUnitBusySyncStatusPtr) & ((uint16)1U << PhyUnit))))
            {
                IsAsyncBusy = TRUE;
                /* The deadline is only meaningful while the unit is busy asynchronously */
                /* #Violation: Spi_c_REF_1 */
                Deadline = SPI_EXD_STATUSPTR(CoreId, PhyUnit)->AsyncDeadline;
            }
#if (SPI_ENABLE_DMA == STD_ON)
            /* The transfer type can not change while the hardware unit is occupied asynchronously */
            IsDmaTransfer = Spi_CoreStatus[CoreId]->PhyUnitStatusPtr[PhyUnitIndex].DmaEnable;
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */
            /*  The asynchronous mode is read together with the unit state, so that the polling
                decision is consistent with the snapshot */
            /* #Violation: Spi_c_REF_1 */
            AsyncMode = SPI_ASYNC_MODE(CoreId);
            SPI_EXIT_CRITICAL_SECTION(AsyncTransmit);
            if (TRUE == IsAsyncBusy)
            {
                /*  The error polling and the receive polling replace the interrupts and are done in
                    SPI_POLLING_MODE only. In SPI_INTERRUPT_MODE the hardware unit is served by
                    Spi_FifoRx_ISRHandler, Spi_Error_ISRHandler and Spi_DmaNotification */
                if (SPI_POLLING_MODE == AsyncMode)
                {
                    /* Polling error handling function */
                    Spi_IsrError(CoreId, PhyUnit);
#if (SPI_ENABLE_DMA == STD_ON)
                    /* The reception of a DMA transfer is done by the DMA and finished in
                       Spi_DmaNotification: the receive FIFO shall not be read here */
                    if (FALSE == IsDmaTransfer)
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */
                    {
                        /* Get the receive request flag */
                        IsPollRequest = Espi_Hal_GetFlagStatus(
                                Spi_ConfigPtr->PhyUnitMapPtr[PhyUnit], ESPI_INTC_FLAG_RX);
                        /* Check if the current Job is in receiving status */
                        if (0U != IsPollRequest)
                        {
#if (SPI_SAFETY_ENABLE == STD_ON)
                            /* Call hardware for asynchronous data reception */
                            RetResult = Spi_AsyncIsrFifoRx(CoreId, PhyUnit);
                            if(FALSE == RetResult)
                            {
                                (void)Det_ReportRuntimeError(SPI_MODULE_ID, SPI_INSTANCE_ID,
                                                SPI_SID_MAINFUNCTION_HANDLING, SPI_E_SAFETY_ERROR);
                            }
#else
                            /* Call hardware for asynchronous data reception */
                            (void)Spi_AsyncIsrFifoRx(CoreId, PhyUnit);
#endif /* (SPI_SAFETY_ENABLE \== STD_ON) */
                        }
                    }
                }
                /*  The timeout supervision runs in both asynchronous modes: an interrupt which never
                    arrives can only be detected here */
                Spi_AsyncSuperviseTimeout(CoreId, PhyUnit, Deadline);
            }
        }
    }
}
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
/****************************************************************************************************
*   Function Name           : Spi_FifoRx_ISRHandler
*
*   Service ID              : 0xE0.
*
*   Description             : SPI Receive FIFO interrupt service function.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Spi_00155.
****************************************************************************************************/
FUNC(void, SPI_PUBLIC_CODE) Spi_FifoRx_ISRHandler
(
    Spi_HWUnitType PhyUnit
)
{
#if (SPI_SAFETY_ENABLE == STD_ON)
    boolean             RetResult;
#endif /* (SPI_SAFETY_ENABLE \== STD_ON) */
    Mcal_CoreType       CoreId;

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType RetStatus;
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */

    /* Get core id which is executing currently */
    /* #Violation: Spi_c_REF_1 */
    CoreId = Mcal_GetCoreId(); 

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Get PhyUnit DET diagnostic results */
    RetStatus = Spi_GetPhyUnitDetStatus(CoreId, SPI_SID_FIFO_RX_ISR, PhyUnit);
    if(E_OK == RetStatus)
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
    {
#if (SPI_SAFETY_ENABLE == STD_ON)
        /* Call hardware for asynchronous data reception */
        RetResult = Spi_AsyncIsrFifoRx(CoreId, PhyUnit);
        if(FALSE == RetResult)
        {
            (void)Det_ReportRuntimeError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SID_FIFO_RX_ISR,
                                        SPI_E_SAFETY_ERROR);
        }
#else
        /* Call hardware for asynchronous data reception */
        (void)Spi_AsyncIsrFifoRx(CoreId, PhyUnit);
#endif /* (SPI_SAFETY_ENABLE \== STD_ON) */
    }
}
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */

/****************************************************************************************************
*   Function Name           : Spi_Error_ISRHandler
*
*   Service ID              : 0xE1.
*
*   Description             : SPI error interrupt service function.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : FSwR_MCAL_SPI_002.
****************************************************************************************************/
FUNC(void, SPI_PUBLIC_CODE) Spi_Error_ISRHandler
(
    Spi_HWUnitType PhyUnit
)
{
    Mcal_CoreType               CoreId;
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType              RetStatus;
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */

    /* Get core id which is executing currently */
    /* #Violation: Spi_c_REF_1 */
    CoreId = Mcal_GetCoreId(); 

#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Get PhyUnit DET diagnostic results */
    RetStatus = Spi_GetPhyUnitDetStatus(CoreId, SPI_SID_ERROR_ISR, PhyUnit);
    if(E_OK == RetStatus)
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Call hardware unit error handler */
        Spi_IsrError(CoreId, PhyUnit);
    }
}
/* #Violation: Spi_c_REF_4 */
#define SPI_STOP_SEC_CODE_ASIL_D_GLOBAL  
/* #Violation: Spi_c_REF_7 */
#include "Spi_MemMap.h"  
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
