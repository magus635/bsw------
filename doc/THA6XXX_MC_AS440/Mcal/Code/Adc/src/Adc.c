/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Adc.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : SARADC
*
*   brief                 : This file contains all functions of Adc Driver
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
*#Adc_c_REF_1:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the 
*     driver must be placed.
*
*#Adc_c_REF_2:MISRAC2012-Rule-11.4;
* Justification:Converting integers to object pointers to reduce register access complexity.
*
*#Adc_c_REF_3:MISRAC2012-Rule-20.10;
* Justification:Use glue operator to construct the exclusive area function name.
*
*#Adc_c_REF_5:MISRAC2012-Dir-4.9;
* Justification:Function like macros are used to reduce code complexity.
*
*#Adc_c_REF_6:MISRAC2012-Rule-10.5;
* Justification:Cortex-R52+ lacks bool type; minimum unit is uint8.
*
*#Adc_c_REF_7:MISRAC2012-Rule-10.5;
* Justification:Unsigned to enum type do not exceed the enum range.
*
*#Adc_c_REF_8:CertC-DCL00-C;
* Justification:Parameter declared refer to AUTOSAR specifications.
*
*#Adc_c_REF_9:MISRAC2012-Rule-20.7;
* Justification:Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*
*#Adc_c_REF_10:MISRAC2012-Dir-4.9;
* Justification:Function like macros are used to reduce code complexity.
*
*#Adc_c_REF_11:MISRAC2012-Rule-8.9;
* Justification:The value should be placed in the const data sections to reduce code complexity 
* and stack size.
*
*#Adc_c_REF_12:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*#Adc_c_REF_13:MISRAC2012-Rule-2.1;
* Justification:Reserved API for user access.
*
*#Adc_c_REF_14:PRE00-C;
* Justification:Function like macros are used to reduce code complexity.
*
*#Adc_c_REF_15:MISRAC2012-Rule-2.2;
* Justification:Platform-based design with configurable macros.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Adc.h"
#include "Adc_Version.h"
#include "SchM_Adc.h"
#include "Mcall.h"
/* SWS_Adc_00377 */
#include "Det.h"
/* Included the saradc driver of HAL layer */
#include "tha6_cfg.h"
#include "saradc_hal.h"

/****************************************************************************************************
**                          Version Checks                                                         **
****************************************************************************************************/
#if (ADC_VENDOR_ID != ADC_CFG_VENDOR_ID)
  #error "Adc.c : Mismatch in Vendor ID"
#endif /* \(ADC_VENDOR_ID != ADC_CFG_VENDOR_ID) */

#if (ADC_MODULE_ID != ADC_CFG_MODULE_ID)
  #error "Adc.c : Mismatch in Module ID"
#endif /* \(ADC_MODULE_ID != ADC_CFG_MODULE_ID) */

#if (ADC_AR_RELEASE_MAJOR_VERSION != ADC_CFG_AR_RELEASE_MAJOR_VERSION)
  #error "Adc.c : Mismatch in Release Major Version"
#endif /* \(ADC_AR_RELEASE_MAJOR_VERSION != ADC_CFG_AR_RELEASE_MAJOR_VERSION) */

#if (ADC_AR_RELEASE_MINOR_VERSION != ADC_CFG_AR_RELEASE_MINOR_VERSION)
  #error "Adc.c : Mismatch in Release Minor Version"
#endif /* \(ADC_AR_RELEASE_MINOR_VERSION != ADC_CFG_AR_RELEASE_MINOR_VERSION) */

#if (ADC_AR_RELEASE_REVISION_VERSION != ADC_CFG_AR_RELEASE_REVISION_VERSION)
  #error "Adc.c : Mismatch in Release Revision Version"
#endif /* \(ADC_AR_RELEASE_REVISION_VERSION != ADC_CFG_AR_RELEASE_REVISION_VERSION) */

#if (ADC_SW_MAJOR_VERSION != ADC_CFG_SW_MAJOR_VERSION)
  #error "Adc.c : Mismatch in Software Major Version"
#endif /* \(ADC_SW_MAJOR_VERSION != ADC_CFG_SW_MAJOR_VERSION) */

#if (ADC_SW_MINOR_VERSION != ADC_CFG_SW_MINOR_VERSION)
  #error "Adc.c : Mismatch in Software Minor Version"
#endif /* \(ADC_SW_MINOR_VERSION != ADC_CFG_SW_MINOR_VERSION) */

#if (ADC_SW_PATCH_VERSION != ADC_CFG_SW_PATCH_VERSION)
  #error "Adc.c : Mismatch in Software Patch Version"
#endif /* \(ADC_SW_PATCH_VERSION != ADC_CFG_SW_PATCH_VERSION) */

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
/* SW priority considered */
#if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
/* Macro for Maximum Group Possible */
#define ADC_MAX_GROUP_POSSIBLE                     ((uint32)32)
#endif /* (ADC_PRIORITY_IMPLEMENTATION \== ADC_PRIORITY_HW_SW) */

#if (ADC_DEV_ERROR_DETECT == STD_ON)
/* Status to indicate that ADC is un-initialized */
#define ADC_UNINITIALIZE                           ((uint8)0)
/* Status to indicate that ADC is initialized */
#define ADC_INITIALIZED                            ((uint8)1)
#endif /* (ADC_DEV_ERROR_DETECT  \== STD_ON) */

/* Macro indicating request source is free */
#define ADC_GRP_REQ_SRC_FREE                       ((Adc_GroupType)0xFFFF)

/* Invalid values for Global variables */
#define ADC_INVALID_PRIORITY                       ((Adc_GroupPriorityType)0xFF)

/* Flag value to enable interrupt service */
#define ADC_ISR_REQ_SEV                            ((uint8)0x00)
/* Flag value to disable interrupt service */
#define ADC_NO_SERVICE                             ((uint8)0x01)

#if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
/* Status of group in scheduler either in No priority with Queue or HW SW Priority */
#define ADC_START_CONVERSION                       ((uint32)0x01)
#endif /* (ADC_PRIORITY_IMPLEMENTATION \== ADC_PRIORITY_HW_SW) */

#if (ADC_ENABLE_QUEUING == STD_ON)
/* Group ID which is invalid */
#define ADC_INVALID_GROUP_ID                       ((Adc_GroupType)0xFF)
#endif /* \(ADC_ENABLE_QUEUING == STD_ON) */

/* Start bit for parsing the HW unit */
#define ADC_KERNEL_NUM_START_BIT                   (5U)
/* Mask bits for parsing the HW unit */
#define ADC_HWUNIT_GOUP_MASK                       (0x0FU)
/* Mask bits for parsing the group ID  */
#define ADC_KERNEL_GROUP_ID_MASK                   (0x1FU)

/* Macro for timeout while HW unit enable */
#define ADC_HWUNIT_ENABLE_TIMEOUT                  (0x3FU)

/* Macro definition for parsing out the group id from the channel group ID */
/* #Violation: Adc_c_REF_5 */
/* #Violation: Adc_c_REF_14 */
#define ADC_GET_GROUPID(Group)           (((Group) & (Adc_GroupType)ADC_KERNEL_GROUP_ID_MASK))

/* Macro definition for parsing out the HW unit id from the channel group ID */
/* #Violation: Adc_c_REF_5 */
/* #Violation: Adc_c_REF_14 */
#define ADC_GET_HWUNITID(Group)          (((Group) >> ADC_KERNEL_NUM_START_BIT) & \
                                          ADC_HWUNIT_GOUP_MASK)

/* Macro for conversion results accumulation */
#define ADC_NO_RESULT_ACCUMU                       (0U)

/* Get group buffer end status, 'buffer end status' indicate that all buffer is filled */
/* #Violation: Adc_c_REF_5 */
/* #Violation: Adc_c_REF_14 */
#define ADC_GET_RESBUFENDSTATUS(EndStatus, Group)    \
                     MCAL_GETBITS((EndStatus), (uint32)(Group), (uint32)(1U))

/* Set group buffer end status */
/* #Violation: Adc_c_REF_5 */
/* #Violation: Adc_c_REF_14 */
#define ADC_SET_RESBUFENDSTATUS(EndStatus, Group)    \
                     MCAL_SETBITS(&(EndStatus), (uint32)(Group), (uint32)(1U), (uint32)(1U))

/* Clear group buffer end status */
/* #Violation: Adc_c_REF_5 */
/* #Violation: Adc_c_REF_14 */
#define ADC_CLR_RESBUFENDSTATUS(EndStatus, Group)    \
                     MCAL_CLRBITS(&(EndStatus), (Group), (1U))

/* Get group status */
/* #Violation: Adc_c_REF_5 */
/* #Violation: Adc_c_REF_14 */
#define ADC_GET_GROUPSTATUS(GroupStatus, Group)      \
                     (Adc_StatusType)MCAL_GETBITS((GroupStatus), (uint32)(Group), (uint32)(1U))

/* Set group status as busy status */
/* #Violation: Adc_c_REF_5 */
/* #Violation: Adc_c_REF_14 */
#define ADC_SET_GROUPSTATUS(GroupStatus, Group)      \
                     MCAL_SETBITS(&(GroupStatus), (uint32)(Group), (uint32)(1U), (uint32)(ADC_BUSY))
/* Set group status as idle status */
/* #Violation: Adc_c_REF_5 */
/* #Violation: Adc_c_REF_14 */
#define ADC_CLR_GROUPSTATUS(GroupStatus, Group)      \
                     MCAL_CLRBITS(&(GroupStatus), (Group), (1U))

/* Get group result status */
/* #Violation: Adc_c_REF_5 */
/* #Violation: Adc_c_REF_14 */
#define ADC_GET_RESULTSTATUS(ResultStatus, Group)    \
                     (Adc_StatusType)MCAL_GETBITS((ResultStatus), (uint32)(Group), (uint32)(1U))
/* Set group result status */
/* #Violation: Adc_c_REF_5 */
/* #Violation: Adc_c_REF_14 */
#define ADC_SET_RESULTSTATUS(ResultStatus, Group)    \
                     MCAL_SETBITS(&(ResultStatus), (uint32)(Group), (uint32)(1U), (uint32)(1U))
/* Clear group result status */
/* #Violation: Adc_c_REF_5 */
/* #Violation: Adc_c_REF_14 */
#define ADC_CLR_RESULTSTATUS(ResultStatus, Group)    \
                     MCAL_CLRBITS(&(ResultStatus), (Group), (1U))

/* Clear notification flag */
/* #Violation: Adc_c_REF_5 */
/* #Violation: Adc_c_REF_14 */
#define ADC_DISABLE_NOTIF(NotifStatus, Group)        \
                     MCAL_CLRBITS(&(NotifStatus), (Group), (1U))

/* Get HW unit data address in memory */
/* #Violation: Adc_c_REF_14 */
#define ADC_GET_DATAADDRESS(CoreId, HwUnitId)        \
                     (Adc_GlobalDataType *)&(Adc_InstanceDataSet[(CoreId)]->GlobalDataSetPtr[\
                                     Adc_ConfigPtr->HwUnitToCorePtr[(HwUnitId)].CoreHwUnitIdx])

/* Get Data buffer address */
/* #Violation: Adc_c_REF_5 */
/* #Violation: Adc_c_REF_14 */
#define ADC_GET_RESULTBUFFERADDRESS(CoreId, HwUnitId, Group) \
                     (Adc_InstanceDataSet[(CoreId)]->GlobalDataSetPtr[\
                                    Adc_ConfigPtr->HwUnitToCorePtr[(HwUnitId)].CoreHwUnitIdx].\
                                    GroupResultBufferPtr[(Group)])


#if (ADC_DEV_ERROR_DETECT == STD_ON)
/* Macro for report the ADC DET error */
/* SWS_Adc_00377 */
/* #Violation: Adc_c_REF_14 */
#define Adc_ReportError(ServiceId, ErrCode)        \
                    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ServiceId, ErrCode)
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
/* Macro for report the runtime error */
/* SWS_Adc_00530 */
#define Adc_ReportRuntimeError(ServiceId, ErrCode) \
                    (void)Det_ReportRuntimeError(ADC_MODULE_ID, ADC_INSTANCE_ID, ServiceId, ErrCode)

/****************************************************************************************************
*                          SchM Critical Section Protection Macros                                 **
****************************************************************************************************/
/* Macro for enter critical section */
/* #Violation: Adc_c_REF_3 */
#define ADC_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Adc_##Exclusive_Area()
/* Macro for exit critical section */
/* #Violation: Adc_c_REF_3 */
#define ADC_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Adc_##Exclusive_Area()

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
/**                         Private Variable Definitions - Core0                                  **/
#if (ADC_MAX_HWUNIT_TO_CORE0 > 0U)
/* #Violation: Adc_c_REF_12 */
#define ADC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#include "Adc_MemMap.h"

#if (ADC_DEV_ERROR_DETECT == STD_ON)
/* Adc initialization status in core0.*/
static uint8 Adc_InitStatusCore0;
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */

/* Adc Runtime data variable of core0  */
static Adc_GlobalDataType Adc_InstanceDataCore0[ADC_MAX_HWUNIT_TO_CORE0];

/* Group Result buffer of core0 */
static Adc_ValueGroupType *Adc_GroupResultBufferCore0[ADC_TOTAL_GROUPS_CORE0];

/* Number of conversion result set available for each ADC channel group of core0 */
static Adc_StreamNumSampleType Adc_NumValidConResCore0[ADC_TOTAL_GROUPS_CORE0];

#if (ADC_ENABLE_QUEUING == STD_ON)
/* Array of Queue information of core0 */
static Adc_QueueDataType Adc_QueueOfSwGroupCore0[ADC_TOTAL_GROUPS_CORE0];
#endif /* \(ADC_ENABLE_QUEUING == STD_ON) */
/* #Violation: Adc_c_REF_12 */
#define ADC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Adc_c_REF_1 */
#include "Adc_MemMap.h"

/* #Violation: Adc_c_REF_12 */
#define ADC_START_SEC_CONST_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Adc_c_REF_1 */
#include "Adc_MemMap.h"


/* Runtime data set of core0 */
static const Adc_GlobalDataSetType Adc_InstanceDataSetCore0 =
{
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    &Adc_InitStatusCore0,
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
    &Adc_InstanceDataCore0[0],
#if (ADC_ENABLE_QUEUING == STD_ON)
    &Adc_QueueOfSwGroupCore0[0],
#endif /* \(ADC_ENABLE_QUEUING == STD_ON) */
    &Adc_NumValidConResCore0[0],
    Adc_GroupResultBufferCore0
};
/* #Violation: Adc_c_REF_12 */
#define ADC_STOP_SEC_CONST_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Adc_c_REF_1 */
#include "Adc_MemMap.h"

#endif /* \(ADC_MAX_HWUNIT_TO_CORE0 > 0U) */

/**                         Private Variable Definitions - Core1                                  **/
#if (MCAL_NUMBER_OF_CORES > 1U)
#if (ADC_MAX_HWUNIT_TO_CORE1 > 0U)
/* #Violation: Adc_c_REF_12 */
#define ADC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Adc_c_REF_1 */
#include "Adc_MemMap.h"

#if (ADC_DEV_ERROR_DETECT == STD_ON)
/* Adc initialization status in core1.*/
static uint8 Adc_InitStatusCore1;
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */

/* Adc Runtime data variable of core1  */
static Adc_GlobalDataType Adc_InstanceDataCore1[ADC_MAX_HWUNIT_TO_CORE1];

/* Group Result buffer of core1 */
static Adc_ValueGroupType *Adc_GroupResultBufferCore1[ADC_TOTAL_GROUPS_CORE1];

/* Number of conversion result set available for each ADC channel group of core1*/
static Adc_StreamNumSampleType Adc_NumValidConResCore1[ADC_TOTAL_GROUPS_CORE1];

#if (ADC_ENABLE_QUEUING == STD_ON)
/* Array of Queue information of core1 */
static Adc_QueueDataType Adc_QueueOfSwGroupCore1[ADC_TOTAL_GROUPS_CORE1];
#endif /* \(ADC_ENABLE_QUEUING == STD_ON) */
/* #Violation: Adc_c_REF_12 */
#define ADC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Adc_c_REF_1 */
#include "Adc_MemMap.h"
/* #Violation: Adc_c_REF_12 */
#define ADC_START_SEC_CONST_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Adc_c_REF_1 */
#include "Adc_MemMap.h"

/* Runtime data set of core1 */
static const Adc_GlobalDataSetType Adc_InstanceDataSetCore1 =
{
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    &Adc_InitStatusCore1,
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
    &Adc_InstanceDataCore1[0],
#if (ADC_ENABLE_QUEUING == STD_ON)
    &Adc_QueueOfSwGroupCore1[0],
#endif /* \(ADC_ENABLE_QUEUING == STD_ON) */
    &Adc_NumValidConResCore1[0],
    Adc_GroupResultBufferCore1
};
/* #Violation: Adc_c_REF_12 */
#define ADC_STOP_SEC_CONST_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Adc_c_REF_1 */
#include "Adc_MemMap.h"

#endif /* \(MCAL_NUMBER_OF_CORES > 1U) */
#endif /* \(ADC_MAX_HWUNIT_TO_CORE1 > 0U) */

/**                         Private Variable Definitions - Core2                                  **/
#if (MCAL_NUMBER_OF_CORES > 2U)
#if (ADC_MAX_HWUNIT_TO_CORE2 > 0U)

#define ADC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
#include "Adc_MemMap.h"

#if (ADC_DEV_ERROR_DETECT == STD_ON)
/* Adc initialization status in core2.*/
static uint8 Adc_InitStatusCore2;
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */

/* Adc Runtime data variable of core2  */
static Adc_GlobalDataType Adc_InstanceDataCore2[ADC_MAX_HWUNIT_TO_CORE2];

/* Group Result buffer of core2 */
static Adc_ValueGroupType *Adc_GroupResultBufferCore2[ADC_TOTAL_GROUPS_CORE2];

/* Number of conversion result set available for each ADC channel group of core2*/
static Adc_StreamNumSampleType Adc_NumValidConResCore2[ADC_TOTAL_GROUPS_CORE2];

#if (ADC_ENABLE_QUEUING == STD_ON)
/* Array of Queue information of core2 */
static Adc_QueueDataType Adc_QueueOfSwGroupCore1[ADC_TOTAL_GROUPS_CORE2];
#endif /* \(ADC_ENABLE_QUEUING == STD_ON) */

#define ADC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
#include "Adc_MemMap.h"

#define ADC_START_SEC_CONST_ASIL_D_CORE2_UNSPECIFIED
#include "Adc_MemMap.h"

/* Runtime data set of core2 */
static const Adc_GlobalDataSetType Adc_InstanceDataSetCore2 =
{
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    &Adc_InitStatusCore2,
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
    &Adc_InstanceDataCore2[0],
#if (ADC_ENABLE_QUEUING == STD_ON)
    &Adc_QueueOfSwGroupCore2[0],
#endif /* \(ADC_ENABLE_QUEUING == STD_ON) */
    &Adc_NumValidConResCore2[0],
    Adc_GroupResultBufferCore2
};

#define ADC_STOP_SEC_CONST_ASIL_D_CORE2_UNSPECIFIED
#include "Adc_MemMap.h"

#endif /* \(MCAL_NUMBER_OF_CORES > 2U) */
#endif /* \(ADC_MAX_HWUNIT_TO_CORE2 > 0U) */

/**                          Private Variable Definitions - Core3                                 **/
#if (MCAL_NUMBER_OF_CORES > 3U)
#if (ADC_MAX_HWUNIT_TO_CORE3 > 0U)

#define ADC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
#include "Adc_MemMap.h"

#if (ADC_DEV_ERROR_DETECT == STD_ON)
/* Adc initialization status in core1.*/
static uint8 Adc_InitStatusCore3;
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */

/* Adc Runtime data variable of core3  */
static Adc_GlobalDataType Adc_InstanceDataCore3[ADC_MAX_HWUNIT_TO_CORE3];

/* Group Result buffer of core3 */
static Adc_ValueGroupType *Adc_GroupResultBufferCore3[ADC_TOTAL_GROUPS_CORE3];

/* Number of conversion result set available for each ADC channel group of core3*/
static Adc_StreamNumSampleType Adc_NumValidConResCore3[ADC_TOTAL_GROUPS_CORE3];

#if (ADC_ENABLE_QUEUING == STD_ON)
/* Array of Queue information of core3 */
static Adc_QueueDataType Adc_QueueOfSwGroupCore3[ADC_TOTAL_GROUPS_CORE3];
#endif /* \(ADC_ENABLE_QUEUING == STD_ON) */

#define ADC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
#include "Adc_MemMap.h"

#define ADC_START_SEC_CONST_ASIL_D_CORE3_UNSPECIFIED
#include "Adc_MemMap.h"

/* Runtime data set of core3 */
static const Adc_GlobalDataSetType Adc_InstanceDataSetCore3 =
{
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    &Adc_InitStatusCore3,
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
    &Adc_InstanceDataCore3[0],
#if (ADC_ENABLE_QUEUING == STD_ON)
    &Adc_QueueOfSwGroupCore3[0],
#endif /* \(ADC_ENABLE_QUEUING == STD_ON) */
    &Adc_NumValidConResCore3[0],
    Adc_GroupResultBufferCore3
};

#define ADC_STOP_SEC_CONST_ASIL_D_CORE3_UNSPECIFIED
#include "Adc_MemMap.h"

#endif /* \(MCAL_NUMBER_OF_CORES > 3U) */
#endif /* \(ADC_MAX_HWUNIT_TO_CORE3 > 0U) */
/* #Violation: Adc_c_REF_12 */
#define ADC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Adc_c_REF_1 */
#include "Adc_MemMap.h"

/* To store the Adc driver configuration pointer */
static P2CONST(Adc_ConfigType, AUTOMATIC, ADC_APPL_DATA) Adc_ConfigPtr;

/* #Violation: Adc_c_REF_12 */
#define ADC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Adc_c_REF_1 */
#include "Adc_MemMap.h"

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/
/* #Violation: Adc_c_REF_12 */
#define ADC_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Adc_c_REF_1 */
#include "Adc_MemMap.h"

/* Pointer to the ADC HW unit data structure set for each core */
static CONSTP2CONST(Adc_GlobalDataSetType, ADC_VAR, ADC_APPL_CONST)
                                       Adc_InstanceDataSet[MCAL_NUMBER_OF_CORES] =
{
#if (ADC_MAX_HWUNIT_TO_CORE0 > 0U)
    &Adc_InstanceDataSetCore0
#else
    NULL_PTR
#endif /* \(ADC_MAX_CHANNEL_TO_CORE0 > 0U) */

#if (MCAL_NUMBER_OF_CORES > 1U)
#if (ADC_MAX_HWUNIT_TO_CORE1 > 0U)
    ,&Adc_InstanceDataSetCore1
#else
    ,NULL_PTR
#endif /* \(ADC_MAX_HWUNIT_TO_CORE1 > 0U) */
#endif /* \(MCAL_NUMBER_OF_CORES > 1U) */

#if (MCAL_NUMBER_OF_CORES > 2U)
#if (ADC_MAX_HWUNIT_TO_CORE2 > 0U)
    ,&Adc_InstanceDataSetCore2
#else
    ,NULL_PTR
#endif /* \(ADC_MAX_HWUNIT_TO_CORE2 > 0U) */
#endif /* \(MCAL_NUMBER_OF_CORES > 2U) */

#if (MCAL_NUMBER_OF_CORES > 3U)
#if (ADC_MAX_HWUNIT_TO_CORE3 > 0U)
    ,&Adc_InstanceDataSetCore3
#else
    ,NULL_PTR
#endif /* \(ADC_MAX_HWUNIT_TO_CORE3 > 0U) */
#endif /* \(MCAL_NUMBER_OF_CORES > 3U) */
};

/* Pointer to the address of each ADC HW unit */
/* #Violation: Adc_c_REF_9 */
static CONSTP2VAR(SARADC_MODULE, ADC_VAR, ADC_APPL_CONST) Adc_BaseAddrs[ADC_MAX_KERNELS] =
{
#if ((defined(ADC_HWUNIT_ADC0)) && (ADC_HWUNIT_ADC0 == 0U))
/* #Violation: Adc_c_REF_2 */
    SARADC0
#else /* \!defined(ADC_HWUNIT_ADC0) */
    NULL_PTR
#endif /* \((defined(ADC_HWUNIT_ADC0)) && (ADC_HWUNIT_ADC0 == 0U)) */

#if (ADC_MAX_KERNELS > 1U)
#if ((defined(ADC_HWUNIT_ADC1)) && (ADC_HWUNIT_ADC1 == 1U))
/* #Violation: Adc_c_REF_2 */
    ,SARADC1
#else /* \!defined(ADC_HWUNIT_ADC1) */
    ,NULL_PTR
#endif /* \((defined(ADC_HWUNIT_ADC1)) && (ADC_HWUNIT_ADC1 == 1U)) */
#endif /* \(ADC_MAX_KERNELS > 1U) */

#if (ADC_MAX_KERNELS > 2U)
#if ((defined(ADC_HWUNIT_ADC2)) && (ADC_HWUNIT_ADC2 == 2U))
/* #Violation: Adc_c_REF_2 */
    ,SARADC2
#else /* \!defined(ADC_HWUNIT_ADC2) */
    ,NULL_PTR
#endif /* \((defined(ADC_HWUNIT_ADC2)) && (ADC_HWUNIT_ADC2 == 2U)) */
#endif /* \(ADC_MAX_KERNELS > 2U) */

#if (ADC_MAX_KERNELS > 3U)
#if ((defined(ADC_HWUNIT_ADC3)) && (ADC_HWUNIT_ADC3 == 3U))
/* #Violation: Adc_c_REF_2 */
    ,SARADC3
#else /* \!defined(ADC_HWUNIT_ADC3) */
    ,NULL_PTR
#endif /* \((defined(ADC_HWUNIT_ADC3)) && (ADC_HWUNIT_ADC3 == 3U)) */
#endif /* \(ADC_MAX_KERNELS > 3U) */

#if (ADC_MAX_KERNELS > 4U)
#if ((defined(ADC_HWUNIT_ADC4)) && (ADC_HWUNIT_ADC4 == 4U))
/* #Violation: Adc_c_REF_2 */
    ,SARADC4
#else /* \!defined(ADC_HWUNIT_ADC4) */
    ,NULL_PTR
#endif /* \((defined(ADC_HWUNIT_ADC4)) && (ADC_HWUNIT_ADC4 == 4U)) */
#endif /* \(ADC_MAX_KERNELS > 4U) */

#if (ADC_MAX_KERNELS > 5U)
#if ((defined(ADC_HWUNIT_ADC5)) && (ADC_HWUNIT_ADC5 == 5U))
/* #Violation: Adc_c_REF_2 */
    ,SARADC5
#else /* \!defined(ADC_HWUNIT_ADC5) */
    ,NULL_PTR
#endif /* \((defined(ADC_HWUNIT_ADC5)) && (ADC_HWUNIT_ADC5 == 5U)) */
#endif /* \(ADC_MAX_KERNELS > 5U) */

#if (ADC_MAX_KERNELS > 6U)
#if ((defined(ADC_HWUNIT_ADC6)) && (ADC_HWUNIT_ADC6 == 6U))
/* #Violation: Adc_c_REF_2 */
    ,SARADC6
#else /* \!defined(ADC_HWUNIT_ADC6) */
    ,NULL_PTR
#endif /* \((defined(ADC_HWUNIT_ADC6)) && (ADC_HWUNIT_ADC6 == 6U)) */
#endif /* \(ADC_MAX_KERNELS > 6U) */

#if (ADC_MAX_KERNELS > 7U)
#if ((defined(ADC_HWUNIT_ADC7)) && (ADC_HWUNIT_ADC7 == 7U))
/* #Violation: Adc_c_REF_2 */
    ,SARADC7
#else /* \!defined(ADC_HWUNIT_ADC7) */
    ,NULL_PTR
#endif /* \((defined(ADC_HWUNIT_ADC7)) && (ADC_HWUNIT_ADC7 == 7U)) */
#endif /* \(ADC_MAX_KERNELS > 7U) */

#if (ADC_MAX_KERNELS > 8U)
#if ((defined(ADC_HWUNIT_ADC8)) && (ADC_HWUNIT_ADC8 == 8U))
/* #Violation: Adc_c_REF_2 */
    ,SARADC8
#else /* \!defined(ADC_HWUNIT_ADC8) */
    ,NULL_PTR
#endif /* \((defined(ADC_HWUNIT_ADC8)) && (ADC_HWUNIT_ADC8 == 8U)) */
#endif /* \(ADC_MAX_KERNELS > 8U) */

#if (ADC_MAX_KERNELS > 9U)
#if ((defined(ADC_HWUNIT_ADC9)) && (ADC_HWUNIT_ADC9 == 9U))
/* #Violation: Adc_c_REF_2 */
    ,SARADC9
#else /* \!defined(ADC_HWUNIT_ADC9) */
    ,NULL_PTR
#endif /* \((defined(ADC_HWUNIT_ADC9)) && (ADC_HWUNIT_ADC9 == 9U)) */
#endif /* \(ADC_MAX_KERNELS > 9U) */

#if (ADC_MAX_KERNELS > 10U)
#if ((defined(ADC_HWUNIT_ADC10)) && (ADC_HWUNIT_ADC10 == 10U))
/* #Violation: Adc_c_REF_2 */
    ,SARADC10
#else /* \!defined(ADC_HWUNIT_ADC10) */
    ,NULL_PTR
#endif /* \((defined(ADC_HWUNIT_ADC10)) && (ADC_HWUNIT_ADC10 == 10U)) */
#endif /* \(ADC_MAX_KERNELS > 10U) */

#if (ADC_MAX_KERNELS > 11U)
#if ((defined(ADC_HWUNIT_ADC11)) && (ADC_HWUNIT_ADC11 == 11U))
/* #Violation: Adc_c_REF_2 */
    ,SARADC11
#else /* \!defined(ADC_HWUNIT_ADC11) */
    ,NULL_PTR
#endif /* \((defined(ADC_HWUNIT_ADC11)) && (ADC_HWUNIT_ADC11 == 11U)) */
#endif /* \(ADC_MAX_KERNELS > 11U) */
};

#if (defined(ADC_ENABLE_LIMIT_CHECK) && (ADC_ENABLE_LIMIT_CHECK == STD_ON))
/* Default value for bound configuration mode */
/* #Violation: Adc_c_REF_11 */
static const Saradc_BoundaryConfig Adc_BoundDefaultConfig = {0U, 0xFFFU};
#endif /* \(defined(ADC_ENABLE_LIMIT_CHECK) && (ADC_ENABLE_LIMIT_CHECK \== STD_ON)) */

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
/* Configuration for SW continuous conversion mode.
 * To solve the issue of automatic conversion of queue not empty. */
/* #Violation: Adc_c_REF_11 */
static const Saradc_GatingTriggerConfig Adc_ContinuousTimerConfig =
{
    /* Default */
    SARADC_GATINGSOURCE_GTM_TRIGGER0,
    /* Default */
    SARADC_TRIGGERSOURCE_RDC_TRIGGER,
    /* Open gate */
    SARADC_GATINGMODE_ALWAYS,
    /* Always triggers */
    SARADC_TRIGGERMODE_ANYEDGE,
    {
        /* Disable the external trigger */
        FALSE,
        /* Minimum timer value */
        1U,
        /* Only the first conversion is triggered by the timer, and then the
           conversion request is issued immediately after the queue is not empty */
        SARADC_TIMERMODE_FOLLOWTIMER_ONLYONCE
    }
};
#endif /* \(ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */

/* #Violation: Adc_c_REF_12 */
#define ADC_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Adc_c_REF_1 */
#include "Adc_MemMap.h"


/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
/* #Violation: Adc_c_REF_12 */
#define ADC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Adc_c_REF_1 */
#include "Adc_MemMap.h"

#if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || (ADC_HW_TRIGGER_API == STD_ON))
static FUNC(void, ADC_PRIVATE_CODE) Adc_UpdateResBuffer
(
    Adc_HwUnitType HwUnitId,
    Adc_GroupType Group,
    CONSTP2CONST(Adc_KernelConfigType, AUTOMATIC, ADC_APPL_DATA) AdcKernelPtr
);
#endif /* \ADC_ENABLE_START_STOP_GROUP_API or ADC_HW_TRIGGER_API is STD_ON */

#if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
static FUNC(boolean, ADC_PRIVATE_CODE) Adc_SchedulerOnStart
(
    Adc_HwUnitType HwUnitId,
    Adc_GroupType Group,
    P2CONST(Adc_KernelConfigType, AUTOMATIC, ADC_APPL_DATA) AdcKernelPtr
);

static FUNC(boolean, ADC_PRIVATE_CODE) Adc_SchedulerOnStop
(
    Adc_HwUnitType HwUnitId,
    Adc_GroupType Group,
    P2CONST(Adc_KernelConfigType, AUTOMATIC, ADC_APPL_DATA) AdcKernelPtr
);

static FUNC(boolean, ADC_PRIVATE_CODE) Adc_ScheduleNext
(
    Adc_HwUnitType HwUnitId,
    uint8 GrpReqSource,
    P2CONST(Adc_KernelConfigType, AUTOMATIC, ADC_APPL_DATA) AdcKernelPtr,
    P2VAR(Adc_GlobalDataType, AUTOMATIC, ADC_APPL_DATA) DataPtr
);
#endif /* \(ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */

#if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || (ADC_HW_TRIGGER_API == STD_ON))
static FUNC(boolean, ADC_PRIVATE_CODE) Adc_StopConvRequestSource
(
    CONSTP2CONST(Adc_GroupCfgType, AUTOMATIC, ADC_APPL_DATA) GrpPtr,
    Adc_HwUnitType HwUnitId
);
#endif /* \((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || (ADC_HW_TRIGGER_API== STD_ON)) */

#if (ADC_ENABLE_QUEUING == STD_ON)
static FUNC(boolean, ADC_PRIVATE_CODE) Adc_PushOnQueue
(
    Adc_HwUnitType HwUnitId,
    Adc_GroupType Group,
    P2CONST(Adc_KernelConfigType, AUTOMATIC, ADC_APPL_DATA) AdcKernelPtr
);

static FUNC(boolean, ADC_PRIVATE_CODE) Adc_PopFromQueue
(
    Adc_HwUnitType HwUnitId,
    Adc_GroupType Group,
    P2CONST(Adc_KernelConfigType, AUTOMATIC, ADC_APPL_DATA) AdcKernelPtr
);

static FUNC(void, ADC_PRIVATE_CODE) Adc_RemoveFromQueue
(
    P2VAR(Adc_GlobalDataType, AUTOMATIC, ADC_APPL_DATA) DataPtr,
    Adc_GroupType Group
);
#endif /* \(ADC_ENABLE_QUEUING == STD_ON) */

static FUNC(void, ADC_PRIVATE_CODE) Adc_InitGlobalVariables
(
    Adc_HwUnitType HwUnitId
);

static FUNC(boolean, ADC_PRIVATE_CODE) Adc_RSInterruptHandler
(
    Adc_HwUnitType HwUnitId,
    Adc_GroupType GroupId,
    CONSTP2CONST(Adc_KernelConfigType, AUTOMATIC, ADC_APPL_DATA) AdcKernelPtr,
    /* #Violation: Adc_c_REF_9 */
    P2VAR(Adc_GlobalDataType, AUTOMATIC, ADC_APPL_DATA) DataPtr
);

static FUNC(boolean, ADC_PRIVATE_CODE) Adc_IsrEventHandler
(
    Adc_HwUnitType HwUnitId,
    Saradc_RequestSource ReqSrc,
    CONSTP2CONST(Adc_KernelConfigType, AUTOMATIC, ADC_APPL_DATA) HwUnitConfigPtr,
    /* #Violation: Adc_c_REF_9 */
    CONSTP2VAR(Adc_GlobalDataType, AUTOMATIC, DSADC_APPL_VAR) DataPtr
);

#if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || (ADC_HW_TRIGGER_API == STD_ON))
static FUNC(boolean, ADC_PRIVATE_CODE) Adc_StartConversion
(
    Adc_HwUnitType HwUnitId,
    CONSTP2CONST(Adc_KernelConfigType, AUTOMATIC, ADC_APPL_DATA) AdcKernelPtr,
    CONSTP2CONST(Adc_GroupCfgType, AUTOMATIC, ADC_APPL_DATA) GrpPtr,
    Adc_TriggerSourceType TriggerSrc
);
#endif /* \((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || (ADC_HW_TRIGGER_API== STD_ON)) */

#if (ADC_DEINIT_API == STD_ON)
static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_CheckGroupStatusAll
(
    void
);
#endif /* \(ADC_DEINIT_API == STD_ON) */

#if (ADC_HW_TRIGGER_API == STD_ON)
/* DET check for Driver status when Enable Group API service is called */
static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_CheckStateForEnableGroup
(
    Adc_GroupType Group,
    Adc_HwUnitType HwUnitId
);
#endif /* \(ADC_HW_TRIGGER_API == STD_ON) */

#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
/* DET check for resource conflict when Start / Enable Group API service is called */
static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_CheckResourceConflict
(
    P2VAR(Adc_GlobalDataType, AUTOMATIC, ADC_APPL_DATA) DataPtr,
    P2CONST(Adc_GroupCfgType, AUTOMATIC, ADC_APPL_DATA) GrpPtr
);
#endif /* \(ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */

#if ((ADC_INTERRUPT_MODE_ENABLE == STD_ON) || (ADC_POLLING_MODE_ENABLE == STD_ON))
/* DET check for Driver status when API service is called */
static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_CheckDriverState
(
    Adc_GroupType Group,
    Adc_HwUnitType HwUnitId
);
#endif /* \((ADC_INTERRUPT_MODE_ENABLE == STD_ON) || (ADC_POLLING_MODE_ENABLE == STD_ON)) */

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
/* DET check for Driver status when Start Group API service is called */
static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_CheckStateForStartGroup
(
    Adc_GroupType Group,
    Adc_HwUnitType HwUnitId
);
#endif /* \(ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */

#if (ADC_DEV_ERROR_DETECT == STD_ON)

/* DET check for initialization status */
static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_CheckInit
(
    uint8 ServiceId
);

/* DET check for API input parameters */
static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_CommDetCheck
(
    uint8 ServiceId,
    Adc_GroupType Group,
    Adc_HwUnitType HwUnitId
);

/* DET check for Adc status, Common Det and resource allocation */
static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_DetErrorCheck
(
    uint8 ServiceId,
    Adc_GroupType Group,
    Adc_HwUnitType HwUnitId
);

/* DET check function: ADC_E_ALREADY_INITIALIZED*/
static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_CheckInitParam
(
    CONSTP2CONST(Adc_ConfigType, AUTOMATIC, ADC_APPL_CONST) ConfigPtr
);

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_CheckSwConv
(
    Mcal_CoreType CoreId,
    Adc_HwUnitType HwUnitId,
    Adc_GroupType Group,
    CONSTP2CONST(Adc_KernelConfigType, AUTOMATIC, ADC_APPL_DATA) AdcKernelPtr
);
#endif /* \((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) ) */

#if (ADC_HW_TRIGGER_API == STD_ON)
static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_CheckParamGrpEnableHwTrigg
(
    Mcal_CoreType CoreId,
    Adc_GroupType Group,
    Adc_HwUnitType HwUnitId,
    CONSTP2CONST(Adc_KernelConfigType, AUTOMATIC, ADC_APPL_DATA) AdcKernelPtr
);

static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_CheckParamGrpDisableHwTrigg
(
    uint8 ServiceId,
    CONSTP2CONST(Adc_GroupCfgType, AUTOMATIC, ADC_APPL_DATA) GrpPtr
);
#endif /* \(ADC_HW_TRIGGER_API == STD_ON) */

static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_CheckMulticoreAllocateError
(
    uint8 ServiceId,
    Adc_HwUnitType HwUnitId
);
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */

static FUNC(void, ADC_PRIVATE_CODE) Adc_ResetTrigSrcData
(
    CONSTP2CONST(Adc_GroupCfgType, AUTOMATIC, ADC_APPL_DATA) GrpPtr,
    /* #Violation: Adc_c_REF_12 */
    CONSTP2VAR(Adc_GlobalDataType, AUTOMATIC, ADC_APPL_DATA) DataPtr
);

#if (ADC_READ_GROUP_API == STD_ON)
#if ((ADC_INTERRUPT_MODE_ENABLE == STD_ON) || (ADC_POLLING_MODE_ENABLE == STD_ON))
#if (ADC_DEV_ERROR_DETECT == STD_ON)
static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_ReadGroupDetCheck
(
    Adc_GroupType GroupId,
    Adc_HwUnitType PhyHwUnitId,
    P2CONST(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) DataBufferPtr
);
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
#endif /* \((ADC_INTERRUPT_MODE_ENABLE == STD_ON) || (ADC_POLLING_MODE_ENABLE== STD_ON)) */
#endif /* \(ADC_READ_GROUP_API == STD_ON) */

#if (ADC_HW_TRIGGER_API == STD_ON)
static FUNC(boolean, ADC_PRIVATE_CODE) Adc_LocalDisableHardwareTrigger
(
    Adc_GroupType    GroupId,
    Adc_HwUnitType   PhyHwUnitId,
    P2VAR(Adc_GlobalDataType, AUTOMATIC, ADC_APPL_DATA) DataPtr,
    Mcal_CoreType    CoreId
);
#endif /* \(ADC_HW_TRIGGER_API == STD_ON) */

/* #Violation: Adc_c_REF_12 */
#define ADC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Adc_c_REF_1 */
#include "Adc_MemMap.h"
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
/* #Violation: Adc_c_REF_12 */
#define ADC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Adc_c_REF_1 */
#include "Adc_MemMap.h"

#if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || (ADC_HW_TRIGGER_API == STD_ON))
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
/****************************************************************************************************
*   Function Name           : Adc_CheckResourceConflict
*
*   Service ID              : None.
*
*   Description             : This function shall check ADC_E_BUSY for any channel conflict.
*
*   Parameters in           : DataPtr: pointer to ADC runtime.
*                             GrpPtr: pointer to current group configuration.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK : DET exists;
*                             E_NOT_OK : DET not exists.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_CheckResourceConflict
(
    P2VAR(Adc_GlobalDataType, AUTOMATIC, ADC_APPL_DATA) DataPtr,
    P2CONST(Adc_GroupCfgType, AUTOMATIC, ADC_APPL_DATA) GrpPtr
)
{
    Std_ReturnType RetErr;

    if ((GrpPtr->IntChMask & DataPtr->AllRunningCh) != 0U)
    {
        /* Report DET error when same channel conflict */
        RetErr = E_NOT_OK;
    }
    else
    {
        /* Set the channels of the Group to be started as currently running channels */
        DataPtr->AllRunningCh = ((DataPtr->AllRunningCh) | (GrpPtr->IntChMask));

        RetErr = E_OK;
    }

    return RetErr;
}
#endif /* \(ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)*/
#endif /* \(ADC_ENABLE_START_STOP_GROUP_API == STD_ON)||(ADC_HW_TRIGGER_API== STD_ON)*/

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Adc_CheckStateForStartGroup
*
*   Service ID              : None.
*
*   Description             : This function shall check ADC_E_BUSY for start group API.
*
*   Parameters in           : Group: Group ID.
*                             HwUnitId: Adc HwUnitId number
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK : DET exists;
*                             E_NOT_OK : DET not exists.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_CheckStateForStartGroup
(
    Adc_GroupType Group,
    Adc_HwUnitType HwUnitId
)
{
    Std_ReturnType              RetErr;
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
    uint8                       HwUnitCoreIdx;
    const Adc_KernelConfigType  *CfgPtr;
    const Adc_GroupCfgType      *GrpPtr;
#else /* \(ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_NONE) */
#if (ADC_ENABLE_QUEUING == STD_OFF)
    uint32                      AllGrpStat;
#endif /* \(ADC_ENABLE_QUEUING  \== STD_OFF) */
#endif /* \(ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
#if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW)
    uint8                       GroupReqSrc;
#endif /* \(ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW) */
#if ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING != STD_OFF))
    Adc_StatusType              GrpStatus;
#endif /* \((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING != STD_OFF)) */
    Mcal_CoreType               CoreId;
#if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_NONE)
    const Adc_GlobalDataType    *DataPtr;
#else /* \(ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
    Adc_GlobalDataType          *DataPtr;
#endif /* \(ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */

    /* Get core id which core is currently executing */
    /* #Violation: Adc_c_REF_5 */
    CoreId = Mcal_GetCoreId();

    /* Get global data pointer of current ADC*/
    DataPtr = ADC_GET_DATAADDRESS(CoreId, HwUnitId);

#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
    /* Find the sub-index according to the Adc number */
    HwUnitCoreIdx = Adc_ConfigPtr->HwUnitToCorePtr[HwUnitId].CoreHwUnitIdx;
    CfgPtr = &(Adc_ConfigPtr->CoreConfigPtr[CoreId]->HwUnitConfigPtr[HwUnitCoreIdx]);

    GrpPtr = (CfgPtr->GrpCfgPtr + Group);

    /* Partial Priority mechanism considered */
#if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW)
    GroupReqSrc = GrpPtr->GrpRequestSrc;
    /* Check for HW trigger source free */
    if (DataPtr->TriggSrcData[GroupReqSrc].GrpId != ADC_GRP_REQ_SRC_FREE)
    {
        /* Report DET error when the HW queue is in busy */
        RetErr = E_NOT_OK;
    }
    else
    {
        /* Check the group channel overlapping */
        RetErr = Adc_CheckResourceConflict(DataPtr, GrpPtr);
    }
#endif /* \(ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW) */
    /* Full priority mechanism considered */
#if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
    GrpStatus = ADC_GET_GROUPSTATUS(DataPtr->GroupStatus, Group);
    /* Check the group whether is not issued */
    if (GrpStatus != ADC_IDLE)
    {
        /* Report DET error when group is already issued */
        RetErr = E_NOT_OK;
    }
    else
    {
        /* Check the group channel overlapping */
        RetErr = Adc_CheckResourceConflict(DataPtr, GrpPtr);
    }
#endif /* \(ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */

#else /* \(ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_NONE) */
    /* Priority implementation switched off */
    RetErr = E_OK;

#if (ADC_ENABLE_QUEUING == STD_OFF)
    AllGrpStat = DataPtr->GroupStatus;
    /* Check if any group is in the busy status */
    if (AllGrpStat != (uint32)0)
    {
        /* Report DET error when ADC is in busy */
        RetErr = E_NOT_OK;
    }
    /* #Violation: Adc_c_REF_5 */
    MCAL_UNUSED_VAR(Group);
#else /* \(ADC_ENABLE_QUEUING == STD_ON) */
    GrpStatus = ADC_GET_GROUPSTATUS(DataPtr->GroupStatus, Group);
    /* Check the group is already in queue */
    if (GrpStatus != ADC_IDLE)
    {
        /* Report DET error when group already in queue */
        RetErr = E_NOT_OK;
    }
#endif /* \(ADC_ENABLE_QUEUING == STD_ON) */
#endif /* \(ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_NONE) */

    return RetErr;
}
#endif /* \ADC_ENABLE_START_STOP_GROUP_API */

#if (ADC_HW_TRIGGER_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Adc_CheckStateForEnableGroup
*
*   Service ID              : None.
*
*   Description             : This function shall check ADC_E_BUSY for enable hardware trigger group.
*
*   Parameters in           : Group: Group ID.
*                             HwUnitId: Adc HwUnitId number
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK : DET exists;
*                             E_NOT_OK : DET not exists.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_CheckStateForEnableGroup
(
    Adc_GroupType Group,
    Adc_HwUnitType HwUnitId
)
{
    Std_ReturnType             RetErr;
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
    uint8                      GroupReqSrc;
    uint8                      HwUnitCoreIdx;
    const Adc_KernelConfigType *CfgPtr;
    const Adc_GroupCfgType     *GrpPtr;
#else /* \(ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
    uint32                     AllGrpStat;
#endif /* \(ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
#if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_NONE)
    const Adc_GlobalDataType    *DataPtr;
#else /* \(ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
    Adc_GlobalDataType          *DataPtr;
#endif /* \(ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
    Mcal_CoreType              CoreId;

    /* Get core id which core is currently executing */
    /* #Violation: Adc_c_REF_5 */
    CoreId = Mcal_GetCoreId();

    /* Get global data pointer of current ADC*/
    DataPtr = ADC_GET_DATAADDRESS(CoreId, HwUnitId);

#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
    /* Find the sub-index according to the Adc number */
    HwUnitCoreIdx = Adc_ConfigPtr->HwUnitToCorePtr[HwUnitId].CoreHwUnitIdx;
    CfgPtr = &(Adc_ConfigPtr->CoreConfigPtr[CoreId]->HwUnitConfigPtr[HwUnitCoreIdx]);

    GrpPtr = (CfgPtr->GrpCfgPtr + Group);
    GroupReqSrc = GrpPtr->GrpRequestSrc;

    /* Hardware Priority mechanism considered  or Full priority considered */
    /* Check for HW trigger source free */
    if (DataPtr->TriggSrcData[GroupReqSrc].GrpId != ADC_GRP_REQ_SRC_FREE)
    {
        /* Report DET error when the queue is busy */
        RetErr = E_NOT_OK;
    }
    else
    {
         /* Check the group channel overlapping */
        RetErr = Adc_CheckResourceConflict(DataPtr, GrpPtr);
    }
#else /* \(ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
    /* to remove the unused param warning in GNU */
    /* #Violation: Adc_c_REF_5 */
    MCAL_UNUSED_VAR(Group);

    RetErr = E_OK;
    /* Check if any group is in the busy status */
    AllGrpStat = DataPtr->GroupStatus;
    if (AllGrpStat != (uint32)0)
    {
        /* Service is called while ADC is busy in conversion.
           Priority mechanism switched off. Report DET error */
        RetErr = E_NOT_OK;
    }
#endif /* \(ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */

    return RetErr;
}
#endif /* \(ADC_HW_TRIGGER_API == STD_ON) */

#if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || (ADC_HW_TRIGGER_API == STD_ON))
/****************************************************************************************************
*   Function Name           : Adc_UpdateResBuffer
*
*   Service ID              : None.
*
*   Description             : This function shall retrieve conversion result to the buffer.
*
*   Parameters in           : HwUnitId: the ADC number.
*                             Group: the group number for the ADC configuration.
*                             AdcKernelPtr: Pointer to the HW unit configuration parameters.
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
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, ADC_PRIVATE_CODE) Adc_UpdateResBuffer
(
    Adc_HwUnitType HwUnitId,
    Adc_GroupType Group,
    CONSTP2CONST(Adc_KernelConfigType, AUTOMATIC, ADC_APPL_DATA) AdcKernelPtr
)
{
    Adc_StreamNumSampleType NoOfSamples;
    Adc_StreamNumSampleType CurrBufPos;
    Adc_ChannelType         ChannelNum;
    uint8                   NoOfChannels;
#if (ADC_HW_SYNC_CONV_GROUP_EN == STD_ON)
    uint8                   HwUnitCnt;
    uint8                   ChIdx;
    uint16                  SyncGrpSlaveRsltStartPos;
#endif /* \(ADC_HW_SYNC_CONV_GROUP_EN == STD_ON) */
    Adc_GlobalDataType      *DataPtr;
    const Adc_GroupCfgType  *GrpPtr;
    uint32                  LoopCnt;
    Adc_ValueGroupType      *CurrentResBufPtr;
    Adc_ValueGroupType      *GrpBufferBasePtr;
    Mcal_CoreType           CoreId;

    /* #Violation: Adc_c_REF_5 */
    CoreId = Mcal_GetCoreId();

    /* Get global data pointer of current ADC*/
    DataPtr = ADC_GET_DATAADDRESS(CoreId, HwUnitId);

    /* Get the Group result buffer base address */
    GrpBufferBasePtr = DataPtr->GroupResultBufferPtr[Group];

    /* Get the Group configuration data pointer */
    GrpPtr = &(AdcKernelPtr->GrpCfgPtr[Group]);

    /* Streaming number of samples will decide the ResBufPtr increment value */
    NoOfSamples = (GrpPtr->NumSamples);

    /* Get the number of valid conversion result to find the write location to buffer */
    CurrBufPos = DataPtr->NumValidConResPtr[Group];
    if (CurrBufPos == NoOfSamples)
    {
        /* Reset index to base address */
        CurrBufPos = (Adc_StreamNumSampleType)0;
    }

    /* SWS_Adc_00431 */
    /* SWS_Adc_00432 */
    /* Get the result buffer pointer for updating the result */
    CurrentResBufPtr = &GrpBufferBasePtr[CurrBufPos];

    /* Get the total assigned channel number from Group */
    NoOfChannels = (uint8)(GrpPtr->GroupDefinitionPtr)[0];

#if (ADC_HW_SYNC_CONV_GROUP_EN == STD_ON)
    /* Starting index of slave hardware unit in sync group */
    SyncGrpSlaveRsltStartPos = (uint16)NoOfChannels * (uint16)NoOfSamples;
#endif /* \(ADC_HW_SYNC_CONV_GROUP_EN == STD_ON) */

    /* SWS_Adc_00318, SWS_Adc_00319 */
    /* Update the result of all channels  */
    LoopCnt = 0U;
    while (NoOfChannels > 0U)
    {
        /* Get the Internal physical channel number from RS Group data variable */
        ChannelNum = DataPtr->RsGroupData[(uint8)(GrpPtr->GrpRequestSrc)].GrpChannels[LoopCnt];

        /* SWS_Adc_00122, SWS_Adc_00418 */
        /* Get the conversion Result of the channel */
        *CurrentResBufPtr = (Adc_ValueGroupType)Saradc_Hal_GetResult(Adc_BaseAddrs[HwUnitId],
                                                            /* #Violation: Adc_c_REF_7 */
                                                            (Saradc_ChannelResult)ChannelNum); 

#if (ADC_HW_SYNC_CONV_GROUP_EN == STD_ON)
        if ((AdcKernelPtr->SyncGrpSlaveHwPtr != NULL_PTR) && (TRUE == GrpPtr->IsSyncChExists))
        {
            /* Sync group is enabled and this is the master in sync group */
            for (HwUnitCnt = 1U; HwUnitCnt <= AdcKernelPtr->SyncGrpSlaveHwPtr[0]; HwUnitCnt++)
            {
                ChIdx = (GrpPtr->GroupDefinitionPtr)[LoopCnt + 1U];
                if (TRUE == AdcKernelPtr->ChCfgPtr[ChIdx].ChRuntimeConfigData.enableSynchronize)
                {
                    /* Get the conversion Result of the same channel with master and save it to
                     * buffer */
                    CurrentResBufPtr[(SyncGrpSlaveRsltStartPos * HwUnitCnt)] = 
                            (Adc_ValueGroupType)Saradc_Hal_GetResult(
                                Adc_BaseAddrs[AdcKernelPtr->SyncGrpSlaveHwPtr[HwUnitCnt]], 
                                /* #Violation: Adc_c_REF_7 */
                                (Saradc_ChannelResult)ChannelNum);
                }
                else
                {
                    /* This channel is not a sync channel, so write 0xFFFF to it */
                    CurrentResBufPtr[(SyncGrpSlaveRsltStartPos * HwUnitCnt)] = 0xFFFFU;
                }
            }
        }
#endif /* \(ADC_HW_SYNC_CONV_GROUP_EN == STD_ON) */

        /* Pointer to the next channel result element of the group */
        CurrentResBufPtr = &CurrentResBufPtr[NoOfSamples];

        /* Decrement the NoOfChannels by 1 */
        NoOfChannels--;

        LoopCnt++;
    }

    /* Increment the no. of valid conversion result */
    CurrBufPos++;

    /* Update the Number of conversion result */
    DataPtr->NumValidConResPtr[Group] = CurrBufPos;

    /* Check if the current updated buffer location has reached maximum */
    if (CurrBufPos == NoOfSamples)
    {
        /* Then set the status of End buffer */
        /* #Violation: Adc_c_REF_10 */
        ADC_SET_RESBUFENDSTATUS(DataPtr->GrpBufferEndResultStatus, Group);
    }
}
#endif /* \((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || (ADC_HW_TRIGGER_API== STD_ON)) */

#if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
/****************************************************************************************************
*   Function Name           : Adc_SchedulerOnStart
*
*   Service ID              : None.
*
*   Description             : This function shall schedule the group for start group API.
*
*   Parameters in           : HwUnitId: the ADC number.
*                             GroupId: the group number for the ADC configuration.
*                             AdcKernelPtr: Pointer to the HW unit configuration parameters.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : TRUE: No Safety error.
*                             FALSE: Safety error exists.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, ADC_PRIVATE_CODE) Adc_SchedulerOnStart
(
    Adc_HwUnitType HwUnitId,
    Adc_GroupType GroupId,
    P2CONST(Adc_KernelConfigType, AUTOMATIC, ADC_APPL_DATA) AdcKernelPtr
)
{
    uint8                  GrpReqSource;
    Adc_GroupType          StopGroup;
    Adc_GlobalDataType     *DataPtr;
    const Adc_GroupCfgType *GrpPtr;
    const Adc_GroupCfgType *StopGrpPtr;
    uint32                 GroupReqStatus;
    Mcal_CoreType          CoreId;
    boolean                OperationRslt;

    GroupReqStatus = (uint32)0;
    OperationRslt  = TRUE;

    CoreId = Mcal_GetCoreId();
    /* Get global data pointer of current ADC*/
    DataPtr = ADC_GET_DATAADDRESS(CoreId, HwUnitId);

    /* Get the Group Configuration data pointer */
    GrpPtr = (AdcKernelPtr->GrpCfgPtr) + GroupId;

    /* Get the Group request source */
    GrpReqSource = GrpPtr->GrpRequestSrc;

    /* Enter Critical Section */
    ADC_ENTER_CRITICAL_SECTION(ScheduleStart);

    /* Initialize the number of conversion result set available to 0 */
    DataPtr->NumValidConResPtr[GroupId] = (Adc_StreamNumSampleType)0;

    /* Group status of given group is made ADC_BUSY */
    ADC_SET_GROUPSTATUS(DataPtr->GroupStatus, GroupId);

    /* Clear ADC Group Result Status */
    ADC_CLR_RESULTSTATUS(DataPtr->GroupResultStatus, GroupId);

    /* Reset the End result status to 0 */
    ADC_CLR_RESBUFENDSTATUS(DataPtr->GrpBufferEndResultStatus, GroupId);

    /* Check if the requested Group trigger source is free */
    if (ADC_GRP_REQ_SRC_FREE == DataPtr->TriggSrcData[GrpReqSource].GrpId)
    {
        /* Group is allowed to start the conversion */
        GroupReqStatus = ADC_START_CONVERSION;
    }
    else /* Trigger source is occupied by some other group */
    {
        /* Compare the priority, request group priority is greater than priority of ongoing group */
        if ((GrpPtr->PriorityLevel) > DataPtr->TriggSrcData[GrpReqSource].GrpPriority)
        {
            /* Get the group config data pointer for the group to be aborted/Suspended */
            StopGroup = DataPtr->TriggSrcData[GrpReqSource].GrpId;

            StopGrpPtr = (AdcKernelPtr->GrpCfgPtr) + StopGroup;

            /* To stop ISR calling */
            DataPtr->TriggSrcData[GrpReqSource].IsrServReqFlg = ADC_NO_SERVICE;

            /* Ongoing conversion is suspended/Aborted */
            OperationRslt &= Adc_StopConvRequestSource(StopGrpPtr, HwUnitId);

            /* Reset HW Trigger source data and Adc_AllRunningCh */
            Adc_ResetTrigSrcData(StopGrpPtr, DataPtr);

            /* Return the status of the group to start the conversion */
            GroupReqStatus = ADC_START_CONVERSION;
        }
    }

    /* Start new conversion request */
    if (ADC_START_CONVERSION == GroupReqStatus)
    {
        /* GrpId is updated with the requested Group */
        DataPtr->TriggSrcData[GrpReqSource].GrpId = GroupId;

        /* Update the Trigger source data with group priority level */
        DataPtr->TriggSrcData[GrpReqSource].GrpPriority = GrpPtr->PriorityLevel;

        /* Permit ISR calling */
        DataPtr->TriggSrcData[GrpReqSource].IsrServReqFlg = ADC_ISR_REQ_SEV;

        /* Trigger the Conversion Request Source */
        OperationRslt &= Adc_StartConversion(HwUnitId, AdcKernelPtr, GrpPtr, ADC_TRIGG_SRC_SW);
    }
    /* Exit Critical Section */
    ADC_EXIT_CRITICAL_SECTION(ScheduleStart);

    return OperationRslt;
}

/****************************************************************************************************
*   Function Name           : Adc_SchedulerOnStop
*
*   Service ID              : None.
*
*   Description             : This function shall stop the group and schedule next one for stop
*                             group API.
*
*   Parameters in           : HwUnitId: the ADC number.
*                             Group: the group number for the ADC configuration.
*                             AdcKernelPtr: Pointer to the HW unit configuration parameters.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : TRUE: No Safety error.
*                             FALSE: Safety error exists.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, ADC_PRIVATE_CODE) Adc_SchedulerOnStop
(
    Adc_HwUnitType HwUnitId,
    Adc_GroupType Group,
    P2CONST(Adc_KernelConfigType, AUTOMATIC, ADC_APPL_DATA) AdcKernelPtr
)
{
    uint8                      GrpReqSource;
    Adc_StatusType             GrpStatus;
    Adc_GlobalDataType         *DataPtr;
    const Adc_GroupCfgType     *GrpPtr;
    Mcal_CoreType              CoreId;
    boolean                    OperationRslt;

    OperationRslt = TRUE;
    CoreId = Mcal_GetCoreId();
    /* Get global data pointer of current HW unit*/
    DataPtr = ADC_GET_DATAADDRESS(CoreId, HwUnitId);

    /* Enter Critical section */
    ADC_ENTER_CRITICAL_SECTION(ScheduleStop);

    GrpStatus = ADC_GET_GROUPSTATUS(DataPtr->GroupStatus, Group);
    /* check and handle to stop group */
    if (GrpStatus != ADC_IDLE)
    {
        /* Group status of given group is made ADC_IDLE */
        ADC_CLR_GROUPSTATUS(DataPtr->GroupStatus, Group);

        GrpPtr = (AdcKernelPtr->GrpCfgPtr) + Group;

        /* Get the Group configured trigger source */
        GrpReqSource = GrpPtr->GrpRequestSrc;

        /* The group is currently on conversion */
        if (DataPtr->TriggSrcData[GrpReqSource].GrpId == Group)
        {
            /* Get the group config data pointer for the requested group */
            DataPtr->TriggSrcData[GrpReqSource].IsrServReqFlg = ADC_NO_SERVICE;

            /* Trigger the Conversion Request Source */
            OperationRslt &= Adc_StopConvRequestSource(GrpPtr, HwUnitId);

            /* Reset HW Trigger source data and Adc_AllRunningCh */
            Adc_ResetTrigSrcData(GrpPtr, DataPtr);

            /* Schedule the next conversion in the stopped trigger source */
            OperationRslt &= Adc_ScheduleNext(HwUnitId, GrpReqSource, AdcKernelPtr, DataPtr);
        }
    }

    /* Clear ADC Group Result Status */
    ADC_CLR_RESULTSTATUS(DataPtr->GroupResultStatus, Group);

    /* Reset the End result status to 0 */
    ADC_CLR_RESBUFENDSTATUS(DataPtr->GrpBufferEndResultStatus, Group);

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    /* Disable the group notification */
    MCAL_SETBITS(&(DataPtr->GrpNotifStatus),
                       (uint32)Group,
                       (uint32)1U,
                       (uint32)0U);
#endif /* \(ADC_GRP_NOTIF_CAPABILITY == STD_ON) */

    /* Exit Critical Section */
    ADC_EXIT_CRITICAL_SECTION(ScheduleStop);

    return OperationRslt;
}

/****************************************************************************************************
*   Function Name           : Adc_ScheduleNext
*
*   Service ID              : None.
*
*   Description             : This function shall schedule next group for the Adc and the queue.
*
*   Parameters in           : HwUnitId: the ADC number.
*                             GrpReqSource: the queue which can be scheduled for next one.
*                             AdcKernelPtr: Pointer to the HW unit configuration parameters.
*                             DataPtr: Pointer to the global runtime variable.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : TRUE: No Safety error.
*                             FALSE: Safety error exists.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, ADC_PRIVATE_CODE) Adc_ScheduleNext
(
    Adc_HwUnitType HwUnitId,
    uint8 GrpReqSource,
    P2CONST(Adc_KernelConfigType, AUTOMATIC, ADC_APPL_DATA) AdcKernelPtr,
    P2VAR(Adc_GlobalDataType, AUTOMATIC, ADC_APPL_DATA) DataPtr
)
{
    const Adc_GroupCfgType     *GrpPtr;
    uint32                     LocalGroupStatus;
    uint32                     GrpTriggerMask;
    sint32                     CurrentGroupPriority;
    Adc_GroupType              GrpId;
    Adc_GroupType              CurrentGroupId;
    Adc_GroupPriorityType      GroupPriority;
    uint32                     AllGrpStat;
    uint16                     LeadingCount;
    boolean                    OperationRslt;

    OperationRslt = TRUE;
    /* Reset the group priority to invalid */
    CurrentGroupPriority = (sint32)(-1);
    /* Reset the group ID to invalid */
    CurrentGroupId = ADC_GRP_REQ_SRC_FREE;

    /* Initialize with No groups are for conversion in the requested trigger source */
    DataPtr->TriggSrcData[GrpReqSource].GrpId = ADC_GRP_REQ_SRC_FREE;
    DataPtr->TriggSrcData[GrpReqSource].GrpPriority = ADC_INVALID_PRIORITY;
    DataPtr->TriggSrcData[GrpReqSource].IsrServReqFlg = ADC_NO_SERVICE;

    /* Get the all group status */
    AllGrpStat = DataPtr->GroupStatus;

    /* Get the Group mask for a requested trigger source */
    GrpTriggerMask = (AdcKernelPtr->TriggSrcGroupMaskPtr[GrpReqSource]);
    /* Extract the Group status of the requested trigger source */
    LocalGroupStatus = (AllGrpStat & GrpTriggerMask);

    while (LocalGroupStatus != 0U)
    {
        /* Some groups are in busy status, find the busy group */
        /* Count leading zeros counts */
        MCAL_CLZ(&LeadingCount, LocalGroupStatus);
        /* To find the first group which in busy status */
        GrpId = ADC_MAX_GROUP_POSSIBLE - LeadingCount - 1U;
        /* Get the Group configuration data pointer */
        GrpPtr = (AdcKernelPtr->GrpCfgPtr) + GrpId;
        GroupPriority = GrpPtr->PriorityLevel;
        /* Find the highest priority group */
        if ((sint32)GroupPriority > CurrentGroupPriority)
        {
            CurrentGroupId = GrpId;
            CurrentGroupPriority = (sint32)GroupPriority;
        }

        /* Clear current group id busy status */
        LocalGroupStatus &= (~((uint32)ADC_BUSY << GrpId));
    }

    /* To check if schedule next one */
    if (CurrentGroupId != ADC_GRP_REQ_SRC_FREE)
    {
        /* Update the TriggSrcData for next group in the priority queue */
        GrpPtr = AdcKernelPtr->GrpCfgPtr + CurrentGroupId;

        /* GrpId is updated with the next Group for conversion */
        DataPtr->TriggSrcData[GrpReqSource].GrpId = CurrentGroupId;

        /* GrpPriority is updated with the next Group priority level */
        DataPtr->TriggSrcData[GrpReqSource].GrpPriority =
            (Adc_GroupPriorityType)CurrentGroupPriority;

        /* Permit ISR calling */
        DataPtr->TriggSrcData[GrpReqSource].IsrServReqFlg = ADC_ISR_REQ_SEV;
        /* Note: In case of short conversion time, ISR no service flag has to be
           cleared before the first conversion complete interrupt */

        /* Start the next group in the priority queue */
        OperationRslt &= Adc_StartConversion(HwUnitId, AdcKernelPtr, GrpPtr, ADC_TRIGG_SRC_SW);
    }

    return OperationRslt;
}
#endif /* \(ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */

#if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || (ADC_HW_TRIGGER_API == STD_ON))
/****************************************************************************************************
*   Function Name           : Adc_StopConvRequestSource
*
*   Service ID              : None.
*
*   Description             : This function shall stop the queue of the ADC.
*
*   Parameters in           : GrpPtr: the group configuration pointer.
*                             HwUnitId: the ADC number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : TRUE: No Safety error.
*                             FALSE: Safety error exists.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, ADC_PRIVATE_CODE) Adc_StopConvRequestSource
(
    CONSTP2CONST(Adc_GroupCfgType, AUTOMATIC, ADC_APPL_DATA) GrpPtr,
    Adc_HwUnitType HwUnitId
)
{
    Adc_ChannelType               LastChannelNum;
    const Adc_GlobalDataType      *DataPtr;
    Saradc_InterruptConfig        RsltIntConfig;
    Mcal_CoreType                 CoreId;
    boolean                       OperationRslt;

    OperationRslt = TRUE;
    /* The next and all Queue entry are cleared */
    OperationRslt &= Saradc_Hal_FlushQueue(Adc_BaseAddrs[HwUnitId], 
                                    (Saradc_RequestSource)GrpPtr->GrpRequestSrc);
    /* #Violation: Adc_c_REF_5 */
    CoreId = Mcal_GetCoreId();

    /* Get Data set address */
    DataPtr = ADC_GET_DATAADDRESS(CoreId, HwUnitId);
    /* Get the channel ID of last channel in the list */
    LastChannelNum = DataPtr->RsGroupData[GrpPtr->GrpRequestSrc].
                    GrpChannels[DataPtr->RsGroupData[GrpPtr->GrpRequestSrc].NoOfChannels - 1U];
    /* Disable the result interrupt */
    RsltIntConfig.interruptEnable = FALSE;
    RsltIntConfig.interruptMapping = SARADC_MAPPING_INTERRUPT0;
    OperationRslt &= Saradc_Hal_SetResultInterrupt(Adc_BaseAddrs[HwUnitId],
                                  /* #Violation: Adc_c_REF_7 */
                                    (Saradc_ChannelResult)LastChannelNum, &RsltIntConfig);
    /* Clear the Result register event flag */
    Saradc_Hal_ClearInterruptStatus(Adc_BaseAddrs[HwUnitId],
                                    SARADC_INTERRUPTSOURCE_RESULT,
                                    (uint32)(GrpPtr->IntChMask));
    return OperationRslt;
}
#endif /* \((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || (ADC_HW_TRIGGER_API== STD_ON)) */

#if (ADC_ENABLE_QUEUING == STD_ON)
/****************************************************************************************************
*   Function Name           : Adc_PushOnQueue
*
*   Service ID              : None.
*
*   Description             : This function shall schedule the group to conversion or put on queue.
*
*   Parameters in           : HwUnitId: ADC HW unit ID.
*                             Group: group number for the specified ADC HW unit.
*                             AdcKernelPtr: Pointer to the HW unit configuration set.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : TRUE: No Safety error.
*                             FALSE: Safety error exists.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, ADC_PRIVATE_CODE) Adc_PushOnQueue
(
    Adc_HwUnitType HwUnitId,
    Adc_GroupType Group,
    P2CONST(Adc_KernelConfigType, AUTOMATIC, ADC_APPL_DATA) AdcKernelPtr
)
{
    Adc_GlobalDataType      *DataPtr;
    const Adc_GroupCfgType  *GrpPtr;
    Mcal_CoreType           CoreId;
    boolean                 OperationRslt;

    OperationRslt = TRUE;
    CoreId = Mcal_GetCoreId();
    /* Get global data pointer of current ADC*/
    DataPtr = ADC_GET_DATAADDRESS(CoreId, HwUnitId);

    /* Enter Critical Section */
    ADC_ENTER_CRITICAL_SECTION(PushQueue);

    /* Initialize the number of conversion result set available to 0 */
    DataPtr->NumValidConResPtr[Group] = (Adc_StreamNumSampleType)0;

    /* Group status of given group is made ADC_BUSY */
    ADC_SET_GROUPSTATUS(DataPtr->GroupStatus, Group);

    /* Clear ADC Group Result Status */
    ADC_CLR_RESULTSTATUS(DataPtr->GroupResultStatus, Group);

    /* Reset the End result status to 0 */
    ADC_CLR_RESBUFENDSTATUS(DataPtr->GrpBufferEndResultStatus, Group);

    /* Check if Queue is empty */
    if (ADC_INVALID_GROUP_ID == DataPtr->PushGroupId)
    {
        /* Initialize the Pop Index and Push Index to the Requested Group */
        DataPtr->PushGroupId = Group;
        DataPtr->PopGroupId = Group;

        /* Get the Group configuration data pointer */
        GrpPtr = (AdcKernelPtr->GrpCfgPtr) + DataPtr->PopGroupId;

        /* GrpId is updated with the requested Group */
        DataPtr->TriggSrcData[GrpPtr->GrpRequestSrc].GrpId = DataPtr->PopGroupId;

        /* Permit ISR calling */
        DataPtr->TriggSrcData[GrpPtr->GrpRequestSrc].IsrServReqFlg = ADC_ISR_REQ_SEV;

        /* Trigger the Conversion Request Source */
        OperationRslt &= Adc_StartConversion(HwUnitId, AdcKernelPtr, GrpPtr, ADC_TRIGG_SRC_SW);
    }
    else
    {
        /* SWS_Adc_00332, SWS_Adc_00417 */
        /* Latest Group in Queue will point the NextGroup as requested Group */
        DataPtr->QueueOfSwGroupPtr[DataPtr->PushGroupId].NextGroup = Group;

        /* Requested Group in Queue will point the Previous Group as latest group
         * which is given by Push index */
        DataPtr->QueueOfSwGroupPtr[Group].PreviousGroup = DataPtr->PushGroupId;

        /* The latest Group in Queue now is updated to requested group in push index */
        DataPtr->PushGroupId = Group;
    }

    /* Exit Critical Section */
    ADC_EXIT_CRITICAL_SECTION(PushQueue);

    return OperationRslt;
}

/****************************************************************************************************
*   Function Name           : Adc_PopFromQueue
*
*   Service ID              : None.
*
*   Description             : This function shall stop the group and schedule next one for queuing
*                             mode.
*
*   Parameters in           : HwUnitId: the ADC number.
*                             Group: the group number for the ADC configuration.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : TRUE: No Safety error.
*                             FALSE: Safety error exists.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, ADC_PRIVATE_CODE) Adc_PopFromQueue
(
    Adc_HwUnitType HwUnitId,
    Adc_GroupType Group,
    P2CONST(Adc_KernelConfigType, AUTOMATIC, ADC_APPL_DATA) AdcKernelPtr
)
{
    Adc_GlobalDataType      *DataPtr;
    const Adc_GroupCfgType  *GrpPtr;
    Adc_GroupType           TempPrevGroupId;
    Adc_GroupType           TempNextGroupId;
    Mcal_CoreType           CoreId;
    boolean                 OperationRslt;

    OperationRslt = TRUE;
    /* Get the Core ID of the current core */
    CoreId = Mcal_GetCoreId();
    /* Get global data pointer of current ADC*/
    DataPtr = ADC_GET_DATAADDRESS(CoreId, HwUnitId);

    /* Enter Critical Section */
    ADC_ENTER_CRITICAL_SECTION(PopQueue);

    /* Group status of stop request group is made ADC_IDLE */
    ADC_CLR_GROUPSTATUS(DataPtr->GroupStatus, Group);

    /* Clear ADC Group Result Status */
    ADC_CLR_RESULTSTATUS(DataPtr->GroupResultStatus, Group);

    /* Reset the End result status to 0 */
    ADC_CLR_RESBUFENDSTATUS(DataPtr->GrpBufferEndResultStatus, Group);

    /* If the requested Group is pointed by pop index.
     * i.e. the Group which is the first element in the Queue and enabled in hardware */
    if (DataPtr->PopGroupId == Group)
    {
        /* Get the group configuration data pointer for the requested group */
        GrpPtr = (AdcKernelPtr->GrpCfgPtr) + Group;

        /* Disable interrupt request */
        DataPtr->TriggSrcData[GrpPtr->GrpRequestSrc].IsrServReqFlg = ADC_NO_SERVICE;

        /* Trigger the Conversion Request Source */
        OperationRslt &= Adc_StopConvRequestSource(GrpPtr, HwUnitId);

        /* Reset HW Trigger source data and AllRunningCh */
        Adc_ResetTrigSrcData(GrpPtr, DataPtr);

        /* Pop index will be the next Group in Queue */
        DataPtr->PopGroupId = DataPtr->QueueOfSwGroupPtr[Group].NextGroup;

        /* If Pop group ID is a valid Group ID, request for start conversion */
        if (DataPtr->PopGroupId != ADC_INVALID_GROUP_ID)
        {
            /* Reset, next Group need to be invalid */
            DataPtr->QueueOfSwGroupPtr[Group].NextGroup = ADC_INVALID_GROUP_ID;
            DataPtr->QueueOfSwGroupPtr[DataPtr->PopGroupId].PreviousGroup = ADC_INVALID_GROUP_ID;

            /* Scheduler function needs to be called only when Group is not Idle.
               If Group has implicitly become Idle, it would have scheduled
               the next group for conversion. */
            /* schedule next group */
            /* Get the Group configuration data pointer */
            GrpPtr = (AdcKernelPtr->GrpCfgPtr) + DataPtr->PopGroupId;

            /* GrpId is updated with the requested Group */
            DataPtr->TriggSrcData[GrpPtr->GrpRequestSrc].GrpId = DataPtr->PopGroupId;

            /* Permit ISR calling */
            DataPtr->TriggSrcData[GrpPtr->GrpRequestSrc].IsrServReqFlg = ADC_ISR_REQ_SEV;

            /* Trigger the Conversion Request Source */
            OperationRslt &= Adc_StartConversion(HwUnitId, AdcKernelPtr, GrpPtr, ADC_TRIGG_SRC_SW);
        }
        else /* If Pop Group ID is invalid, then there is no Group in the Queue,
                Reset Push Group ID to invalid */
        {
            DataPtr->PushGroupId = ADC_INVALID_GROUP_ID;
        }
    }
    else /* The requested Group is not pop group, then remove it from queue */
    {
        /* Link through Previous and Next are rearranged in Queue */
        TempPrevGroupId = DataPtr->QueueOfSwGroupPtr[Group].PreviousGroup;
        TempNextGroupId = DataPtr->QueueOfSwGroupPtr[Group].NextGroup;

        if (TempPrevGroupId != ADC_INVALID_GROUP_ID)
        {
            DataPtr->QueueOfSwGroupPtr[TempPrevGroupId].NextGroup =
                                            DataPtr->QueueOfSwGroupPtr[Group].NextGroup;
        }
        if (TempNextGroupId != ADC_INVALID_GROUP_ID)
        {
            DataPtr->QueueOfSwGroupPtr[TempNextGroupId].PreviousGroup =
                                            DataPtr->QueueOfSwGroupPtr[Group].PreviousGroup;
        }
        /* Group is de-linked from Queue */
        DataPtr->QueueOfSwGroupPtr[Group].PreviousGroup = ADC_INVALID_GROUP_ID;
        DataPtr->QueueOfSwGroupPtr[Group].NextGroup = ADC_INVALID_GROUP_ID;

        if (Group == DataPtr->PushGroupId)
        {
            /* If the removed group is the last one in the queue, 
               update the push group ID to that of the previous group */
            DataPtr->PushGroupId = TempPrevGroupId;
        }
    }

    /* Exit Critical Section */
    ADC_EXIT_CRITICAL_SECTION(PopQueue);

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    /* Enter Critical Section */
    ADC_ENTER_CRITICAL_SECTION(PopQueue);

    /* SWS_Adc_00155: Disable the group notification */
    MCAL_SETBITS(&(DataPtr->GrpNotifStatus),
                       (uint32)Group,
                       (uint32)1U,
                       (uint32)0U);

    /* Exit Critical Section */
    ADC_EXIT_CRITICAL_SECTION(PopQueue);
#endif /* \(ADC_GRP_NOTIF_CAPABILITY == STD_ON) */

    return OperationRslt;
}

/****************************************************************************************************
*   Function Name           : Adc_RemoveFromQueue
*
*   Service ID              : None.
*
*   Description             : This function shall check ADC_E_BUSY for any channel conflict.
*
*   Parameters in           : DataPtr: pointer to ADC runtime.
*                             Group: the group number for the ADC configuration.
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
static FUNC(void, ADC_PRIVATE_CODE) Adc_RemoveFromQueue
(
    P2VAR(Adc_GlobalDataType, AUTOMATIC, ADC_APPL_DATA) DataPtr,
    Adc_GroupType Group
)
{
    /* Pop Index is updated to next Group */
    DataPtr->PopGroupId = DataPtr->QueueOfSwGroupPtr[Group].NextGroup;

    /* Release the Group from Queue by resetting the Group next pointer in Queue to invalid Group Id
       The Group Previous pointer is already released as the Group was first element in Queue
       (since just completed conversion). */
    DataPtr->QueueOfSwGroupPtr[Group].NextGroup = ADC_INVALID_GROUP_ID;
}
#endif /* \(ADC_ENABLE_QUEUING == STD_ON) */

/****************************************************************************************************
*   Function Name           : Adc_InitGlobalVariables
*
*   Service ID              : None.
*
*   Description             : This function shall initialize all ADC runtime.
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
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, ADC_PRIVATE_CODE) Adc_InitGlobalVariables
(
    Adc_HwUnitType HwUnitId
)
{
    Adc_GlobalDataType         *DataPtr;
    uint32                     LoopCtr;
    Mcal_CoreType              CoreId;
    uint8                      HwUnitCoreIdx;
    uint8                      GrpIndex;

    /* Get core id which core is currently executing */
    /* #Violation: Adc_c_REF_5 */
    CoreId = Mcal_GetCoreId();

    /* Find the sub-index according to the Adc number */
    HwUnitCoreIdx = Adc_ConfigPtr->HwUnitToCorePtr[HwUnitId].CoreHwUnitIdx;

    /* Get the group index of the group start position in the buffers of HwUnitId in the
     * specified core */
    GrpIndex = Adc_ConfigPtr->CoreConfigPtr[CoreId]->HwUnitConfigPtr[HwUnitCoreIdx].IndexGrpsCore;

    /* Get ADC instance data pointer */
    DataPtr = &(Adc_InstanceDataSet[CoreId]->GlobalDataSetPtr[HwUnitCoreIdx]);

    /* Initialize the group member 'GroupResultBufferPtr',
     * pointer to the 'Adc_GroupResultBufferCorex' */
    DataPtr->GroupResultBufferPtr = &(Adc_InstanceDataSet[CoreId]->GrpRsltDataBfPtr[GrpIndex]);

    /* Initialize the group member 'NumValidConResPtr',
     * pointer to the 'Adc_NumValidConResCorex' */
    DataPtr->NumValidConResPtr = &(Adc_InstanceDataSet[CoreId]->GroupNumValidConResPtr[GrpIndex]);

#if (ADC_ENABLE_QUEUING == STD_ON)
    /* Initialize the group member 'QueueOfSwGroupPtr',
     * pointer to the 'Adc_QueueOfSwGroupCorex(x=0~4)' */
    DataPtr->QueueOfSwGroupPtr = &(Adc_InstanceDataSet[CoreId]->GrpQueueOfSwPtr[GrpIndex]);
#endif /* \(ADC_ENABLE_QUEUING == STD_ON) */

    /* Initialize the trigger source data */
    LoopCtr = 0U;
    while (LoopCtr < ADC_REQSRC_COUNT)
    {
        /* Initialize runtime data for the queue */
        DataPtr->TriggSrcData[LoopCtr].GrpId = ADC_GRP_REQ_SRC_FREE;

        /* Initialize runtime data for the queue */
        DataPtr->TriggSrcData[LoopCtr].GrpPriority = ADC_INVALID_PRIORITY;

        /* Initialize runtime data for the queue */
        DataPtr->TriggSrcData[LoopCtr].IsrServReqFlg = ADC_NO_SERVICE;

        LoopCtr++;
    }

    /* Initialize the group result buffer end status for all groups */
    DataPtr->GrpBufferEndResultStatus = 0U;

    /* Reset Group Result Status, set it to no result available*/
    DataPtr->GroupResultStatus = 0U;

    LoopCtr = 0U;
    while (LoopCtr <
                 Adc_ConfigPtr->CoreConfigPtr[CoreId]->HwUnitConfigPtr[HwUnitCoreIdx].TotCfgGrps)
    {
        /* LoopCtr will give the Group ID Reset the Group result buffer address */
        DataPtr->GroupResultBufferPtr[LoopCtr] = NULL_PTR;
        /* Initialize the number of conversion result set available to 0 */
        DataPtr->NumValidConResPtr[LoopCtr] = 0U;

        /* Queue Enable is STD_ON only during No priority */
#if (ADC_ENABLE_QUEUING == STD_ON)
        /* LoopCtr will give the Group ID */
        /* Reset the Queue array to Invalid data */
        DataPtr->QueueOfSwGroupPtr[LoopCtr].NextGroup = ADC_INVALID_GROUP_ID;
        DataPtr->QueueOfSwGroupPtr[LoopCtr].PreviousGroup = ADC_INVALID_GROUP_ID;
#endif /* \(ADC_ENABLE_QUEUING == STD_ON) */

        LoopCtr++;
    }

    /* SWS_Adc_00307: The function Adc_Init shall set all groups to ADC_IDLE state */
    DataPtr->GroupStatus = (uint32)0;

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    /* SWS_Adc_00077: The function Adc_Init shall disable the notifications and hardware trigger
     * capability (if statically configured as active) */
    /* Disable the group notification */
    DataPtr->GrpNotifStatus = (uint32)0;
#endif /* \(ADC_GRP_NOTIF_CAPABILITY == STD_ON) */

    /* Queue Enable is STD_ON only during No priority */
#if (ADC_ENABLE_QUEUING == STD_ON)
    /* Reset the Poping Group Id to Invalid */
    DataPtr->PopGroupId = ADC_INVALID_GROUP_ID;
    /* Reset the Pushed Group Id to Invalid */
    DataPtr->PushGroupId = ADC_INVALID_GROUP_ID;
#endif /* \(ADC_ENABLE_QUEUING == STD_ON) */

#if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || (ADC_HW_TRIGGER_API == STD_ON))
    /* For Partial priority considered */
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
    /* Initialize all running channels for channel sharing checking to 0 */
    DataPtr->AllRunningCh = (uint16)0;
#endif /* \(ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
#endif /* \((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || (ADC_HW_TRIGGER_API== STD_ON)) */
}

/****************************************************************************************************
*   Function Name           : Adc_RSInterruptHandler
*
*   Service ID              : None.
*
*   Description             : This function shall process ADC group interrupt in the specified
*                             queue.
*
*   Parameters in           : HwUnitId: the ADC number.
*                             GroupId: Group: the group number for the ADC configuration.
*                             AdcKernelPtr: Pointer to the HW unit configuration parameters.
*                             DataPtr: Pointer to the global runtime variable.
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
static FUNC(boolean, ADC_PRIVATE_CODE) Adc_RSInterruptHandler
(
    Adc_HwUnitType HwUnitId,
    Adc_GroupType GroupId,
    CONSTP2CONST(Adc_KernelConfigType, AUTOMATIC, ADC_APPL_DATA) AdcKernelPtr,
    /* #Violation: Adc_c_REF_9 */
    P2VAR(Adc_GlobalDataType, AUTOMATIC, ADC_APPL_DATA) DataPtr
)
{
    uint8                  GrpRequestSrc;
    boolean                EndGrpFlg;
#if (ADC_ENABLE_QUEUING == STD_ON)
    Adc_GroupType          PopGrpId;
#endif /* \(ADC_ENABLE_QUEUING == STD_ON) */
    uint32                 BufEndStatus;
    const Adc_GroupCfgType *GrpPtr;
    boolean                OperationRslt;

    OperationRslt = TRUE;
    EndGrpFlg = FALSE;

    /* Get the address of Group configuration structure */
    GrpPtr = &(AdcKernelPtr->GrpCfgPtr[GroupId]);

    /* Get the Group request source */
    GrpRequestSrc = (uint8)GrpPtr->GrpRequestSrc;
    /* Any request source can be configured in SW trigger type and HW trigger type */
    if ((ADC_TRIGG_SRC_SW == GrpPtr->TriggSrc) && (ADC_CONV_MODE_ONESHOT == GrpPtr->ConvMode))
    {
        /* Stop group conversion */
        EndGrpFlg = TRUE;
    }
    else if ((ADC_ACCESS_MODE_STREAMING == GrpPtr->AccessMode) &&
                (ADC_STREAM_BUFFER_LINEAR == GrpPtr->StreamBufferMode))
    {
        /* Streaming mode with linear buffer will check for only linearity */
        /* #Violation: Adc_c_REF_5 */
        BufEndStatus = ADC_GET_RESBUFENDSTATUS(DataPtr->GrpBufferEndResultStatus, GroupId);

        /* Number of conversion reaches number of samples configured */
        if (BufEndStatus != 0U)
        {
            /* Stop group conversion */
            EndGrpFlg = TRUE;
        }
    }
    else
    {
        /* SW trigger with continuous mode */
        /* HW trigger with Single result access will be default Circular buffer */
        /* Not automatic stop */
        EndGrpFlg = FALSE;
    }

    if (TRUE == EndGrpFlg)
    {
        /* to stop ISR calling */
        DataPtr->TriggSrcData[GrpRequestSrc].IsrServReqFlg = ADC_NO_SERVICE;

#if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || (ADC_HW_TRIGGER_API == STD_ON))
        OperationRslt = Adc_StopConvRequestSource(GrpPtr, HwUnitId);
#endif /* \((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || (ADC_HW_TRIGGER_API== STD_ON)) */

        /* SWS_Adc_00330 */
        /* Group is configured in one shot mode, conversion is done only once */
        /* #Violation: Adc_c_REF_10 */
        ADC_CLR_GROUPSTATUS(DataPtr->GroupStatus, GroupId);

        /* Reset the HW Trigger source data on conversion stop and Adc_AllRunningCh */
        Adc_ResetTrigSrcData(GrpPtr, DataPtr);

#if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) /* HW/SW priority enabled */
        /* Call to schedule next group */
        OperationRslt &= Adc_ScheduleNext(HwUnitId, GrpRequestSrc, AdcKernelPtr, DataPtr);
#endif /* \(ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */

#if (ADC_ENABLE_QUEUING == STD_ON) /* Queue Enable is STD_ON only during No priority */
        Adc_RemoveFromQueue(DataPtr, GroupId);

        PopGrpId = DataPtr->PopGroupId;

        if (PopGrpId != ADC_INVALID_GROUP_ID)
        {
            /* The Previous Group pointer of Group which is for
             * scheduling has to be reset to invalid */
            DataPtr->QueueOfSwGroupPtr[PopGrpId].PreviousGroup = ADC_INVALID_GROUP_ID;

            /* Get the Group configuration data pointer */
            GrpPtr = (AdcKernelPtr->GrpCfgPtr) + DataPtr->PopGroupId;

            /* GrpId is updated with the requested Group */
            DataPtr->TriggSrcData[GrpPtr->GrpRequestSrc].GrpId = DataPtr->PopGroupId;

            /* Permit ISR calling */
            DataPtr->TriggSrcData[GrpPtr->GrpRequestSrc].IsrServReqFlg = ADC_ISR_REQ_SEV;

            /* Trigger the Conversion Request Source */
            OperationRslt &= Adc_StartConversion(HwUnitId, AdcKernelPtr, GrpPtr, ADC_TRIGG_SRC_SW);
        }
        else/* If Pop Group ID is invalid, then there is no Group in the Queue,
               Reset Push Group Id to invalid */
        {
            DataPtr->PushGroupId = ADC_INVALID_GROUP_ID;
        }
#endif /* \(ADC_ENABLE_QUEUING == STD_ON) */
    }
    /* SWS_Adc_00328: Do not change group status */

    return OperationRslt;
}

/****************************************************************************************************
*   Function Name           : Adc_IsrEventHandler
*
*   Service ID              : None.
*
*   Description             : This function shall process ADC channel event interrupt in the
*                             specified queue.
*
*   Parameters in           : HwUnitId: the ADC number.
*                             GroupId: Group: the group number for the ADC configuration.
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
static FUNC(boolean, ADC_PRIVATE_CODE) Adc_IsrEventHandler
(
    Adc_HwUnitType HwUnitId,
    Saradc_RequestSource ReqSrc,
    CONSTP2CONST(Adc_KernelConfigType, AUTOMATIC, ADC_APPL_DATA) HwUnitConfigPtr,
    /* #Violation: Adc_c_REF_9 */
    CONSTP2VAR(Adc_GlobalDataType, AUTOMATIC, DSADC_APPL_VAR) DataPtr
)
{
    boolean                    OperationRslt;
    Adc_GroupType              GrpNr;
    Adc_ChannelType            LastChannelNum;
    uint32                     RetValue;
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    const Adc_GroupCfgType     *GrpPtr;
#endif /* \(ADC_GRP_NOTIF_CAPABILITY == STD_ON) */

    OperationRslt = TRUE;

    /* Get the channel ID of last channel in the list */
    LastChannelNum = DataPtr->RsGroupData[ReqSrc].
                                 GrpChannels[DataPtr->RsGroupData[ReqSrc].NoOfChannels - 1U];

    ADC_ENTER_CRITICAL_SECTION(ResultHandling);

    /* Get result interrupt flag */
    RetValue = Saradc_Hal_GetInterruptStatus(Adc_BaseAddrs[HwUnitId],
                                             SARADC_INTERRUPTSOURCE_RESULT);
    /* Judge whether the result interrupt is triggered by last channel */
    if((RetValue & (1UL << LastChannelNum)) != 0U)
    {
        /* Clear result event flag */
        Saradc_Hal_ClearInterruptStatus(Adc_BaseAddrs[HwUnitId],
                                            SARADC_INTERRUPTSOURCE_RESULT,
                                            (uint32)((uint32)1U << LastChannelNum));

        if (DataPtr->TriggSrcData[ReqSrc].IsrServReqFlg != ADC_NO_SERVICE)
        {
            /* If interrupt is used */
            /* Get the ADC0: Group Id from the TriggSrcData */
            GrpNr = DataPtr->TriggSrcData[ReqSrc].GrpId;

#if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || (ADC_HW_TRIGGER_API == STD_ON))
#if (ADC_DMA_MODE_ENABLE == STD_ON)
            /* Update the buffer when DMA is not used for this HW unit */
            if (ADC_RESULT_HANDLING_DMA_MODE == HwUnitConfigPtr->RsltHldMthd)
            {
                /* Set the result buffer end status */
                /* #Violation: Adc_c_REF_10 */
                ADC_SET_RESBUFENDSTATUS(DataPtr->GrpBufferEndResultStatus, GrpNr);
            }
            else
#endif /* \(ADC_DMA_MODE_ENABLE == STD_ON) */
            {
                /* Update result buffer for the group */
                Adc_UpdateResBuffer(HwUnitId, GrpNr, HwUnitConfigPtr);
            }
#endif /* \((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || (ADC_HW_TRIGGER_API== STD_ON)) */

            /* Update the status of group to ADC_COMPLETED */
            /* #Violation: Adc_c_REF_10 */
            ADC_SET_RESULTSTATUS(DataPtr->GroupResultStatus, GrpNr);

            /* Call Request source interrupt handler */
            OperationRslt = Adc_RSInterruptHandler(HwUnitId, GrpNr, HwUnitConfigPtr, DataPtr);

            ADC_EXIT_CRITICAL_SECTION(ResultHandling);

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
            /* SWS_Adc_00060 */
            /* SWS_Adc_00416 */
            /* Call notification function */
            if ((DataPtr->GrpNotifStatus & ((uint32)1 << GrpNr) ) > 0U)
            {
                /* Get the address of Group configuration structure */
                GrpPtr = &(HwUnitConfigPtr->GrpCfgPtr)[GrpNr];

                /* Call to notification function */
                GrpPtr->NotifFctPtr();
            }
            /* SWS_Adc_00083: Do not call notification when notification mechanism is disabled */
#endif /* \(ADC_GRP_NOTIF_CAPABILITY == STD_ON) */
        }
        else
        {
            ADC_EXIT_CRITICAL_SECTION(ResultHandling);
        }
    }
    else
    {
        ADC_EXIT_CRITICAL_SECTION(ResultHandling);
    }

    return OperationRslt;
}

#if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || (ADC_HW_TRIGGER_API == STD_ON))
/****************************************************************************************************
*   Function Name           : Adc_StartConversion
*
*   Service ID              : None.
*
*   Description             : This function shall start conversion by configure the
*                             register.
*
*   Parameters in           : HwUnitId: HW unit number.
*                             AdcKernelPtr: HW unit configuration pointer.
*                             GrpPtr: Group configuration pointer.
*                             TriggerSrc: Group trigger method - SW or HW.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : TRUE: No Safety error.
*                             FALSE: Safety error exists.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, ADC_PRIVATE_CODE) Adc_StartConversion
(
    Adc_HwUnitType HwUnitId,
    CONSTP2CONST(Adc_KernelConfigType, AUTOMATIC, ADC_APPL_DATA) AdcKernelPtr,
    CONSTP2CONST(Adc_GroupCfgType, AUTOMATIC, ADC_APPL_DATA) GrpPtr,
    Adc_TriggerSourceType TriggerSrc
)
{
    uint8                         GrpReqSrc;
    uint8                         ChCnt;
    uint8                         TotalGrpCh;
    uint8                         ChIdx;
    Adc_ChannelType               IntChNr;
    uint32                        ConversionMode;
#if (ADC_HW_SYNC_CONV_GROUP_EN == STD_ON)
    Adc_HwUnitType                HwUnitCnt;
#endif /* \(ADC_HW_SYNC_CONV_GROUP_EN == STD_ON) */
    Adc_GlobalDataType            *DataPtr;
    Saradc_InterruptConfig        RsltIntConfig;
    Mcal_CoreType                 CoreId;
    boolean                       OperationRslt;
    Saradc_DynaChannleConfig      ChConfig;

    OperationRslt = TRUE;
    /* Initialize the local variables */
    ConversionMode = SARADC_QUEUEOPTION_REFILL;

    GrpReqSrc = (uint8)GrpPtr->GrpRequestSrc;

    /* The next and all Queue entry are cleared */
    /* #Violation: Adc_c_REF_7 */
    OperationRslt &= Saradc_Hal_FlushQueue(Adc_BaseAddrs[HwUnitId], (Saradc_RequestSource)GrpReqSrc);
    
    /* Clear the Result register event flag */
    /* Only result interrupts are used because channel interrupts may lead to an issue
     * where the channels result may not have been written to the result register when
     * it is read during the interrupt handler. */
    Saradc_Hal_ClearInterruptStatus(Adc_BaseAddrs[HwUnitId],
                                    SARADC_INTERRUPTSOURCE_RESULT,
                                    (GrpPtr->IntChMask));

    /* The first element in the Group definition will give total number of channels in Group */
    TotalGrpCh = (uint8)(GrpPtr->GroupDefinitionPtr)[0];

    /* #Violation: Adc_c_REF_5 */
    CoreId = Mcal_GetCoreId();
    
    /* Get global data pointer of current ADC*/
    DataPtr = ADC_GET_DATAADDRESS(CoreId, HwUnitId);
    /* Write the channel number of current group */
    DataPtr->RsGroupData[GrpReqSrc].NoOfChannels = TotalGrpCh;

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
    if ((ADC_TRIGG_SRC_SW == TriggerSrc) && (ADC_CONV_MODE_ONESHOT == GrpPtr->ConvMode))
    {
        /* SWS_Adc_00380 */
        /* SWS_Adc_00381 */
        /* SWS_Adc_00326 */
        if (ADC_NO_RESULT_ACCUMU == GrpPtr->ResultAccumNum)
        {
            /* one-shot, not refill */
            ConversionMode = 0U;
        }
    }
#endif /* \(ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */

    /* SWS_Adc_00061 */
    ChIdx = 0U;
    IntChNr = (Adc_ChannelType)0U;
    /* Configure the all channels in a group */
    for (ChCnt = 0U; (ChCnt < TotalGrpCh)
#if (ADC_SAFETY_ENABLE == STD_ON)
        && (TRUE == OperationRslt)
#endif /* \(ADC_SAFETY_ENABLE == STD_ON) */
    ; ChCnt++)
    {
        /* Get the channel configured data via the channel index in group definition */
        ChIdx = (GrpPtr->GroupDefinitionPtr)[ChCnt + 1U];
        
        /* Get channel configuration data */
        ChConfig = AdcKernelPtr->ChCfgPtr[ChIdx].ChRuntimeConfigData;
        /* Get HW unit channel ID from channel configuration data */
        IntChNr = (Adc_ChannelType)ChConfig.channelResult;
#if (ADC_DMA_MODE_ENABLE == STD_ON)
        if (GrpPtr->GroupResRegPtr != NULL_PTR)
        {
            /* User-defined conversion result register */
            /* Assign the result register for channel conversion results to a 
               user-defined register */
            /* #Violation: Adc_c_REF_7 */
            ChConfig.channelResult = (Saradc_ChannelResult)(GrpPtr->GroupResRegPtr)[ChIdx];
        }
#endif /* \(ADC_DMA_MODE_ENABLE == STD_ON) */

        /* Assign the Analog channel number into RS Group data variable */
        DataPtr->RsGroupData[GrpReqSrc].GrpChannels[ChCnt] = IntChNr;

        /* Configure the channel */
        /* #Violation: Adc_c_REF_7 */
        OperationRslt &= Saradc_Hal_DynamicChannelConfig(
                                Adc_BaseAddrs[HwUnitId],
                                /* #Violation: Adc_c_REF_7 */
                                (Saradc_ChannelID)IntChNr,
                                &ChConfig);
        if (ADC_NO_RESULT_ACCUMU != GrpPtr->ResultAccumNum)
        {
            /* Set channel to data reduction mode(conversion result accumulation mode) */
            /* #Violation: Adc_c_REF_7 */
            OperationRslt &= Saradc_Hal_SetDataReduction(
                                        Adc_BaseAddrs[HwUnitId],
                                        /* #Violation: Adc_c_REF_7 */
                                        (Saradc_ChannelID)IntChNr,
                                        /* #Violation: Adc_c_REF_7 */
                                        (Saradc_DataReductionMode)GrpPtr->ResultAccumNum);
        }

#if (ADC_HW_SYNC_CONV_GROUP_EN == STD_ON)
        if ((AdcKernelPtr->SyncGrpSlaveHwPtr != NULL_PTR) && (TRUE == GrpPtr->IsSyncChExists))
        {
            if (TRUE == ChConfig.enableSynchronize)
            {
                for (HwUnitCnt = 1U; HwUnitCnt <= AdcKernelPtr->SyncGrpSlaveHwPtr[0]; HwUnitCnt++)
                {
                    /* Configure the slave channel */
                    OperationRslt &= Saradc_Hal_DynamicChannelConfig(
                                        Adc_BaseAddrs[AdcKernelPtr->SyncGrpSlaveHwPtr[HwUnitCnt]],
                                        /* #Violation: Adc_c_REF_7 */
                                        (Saradc_ChannelID)IntChNr,
                                        &ChConfig);
                    if (ADC_NO_RESULT_ACCUMU != GrpPtr->ResultAccumNum)
                    {
                        /* Set slave channel to data reduction mode(conversion result 
                        accumulation mode) */
                        OperationRslt &= Saradc_Hal_SetDataReduction(
                                        Adc_BaseAddrs[AdcKernelPtr->SyncGrpSlaveHwPtr[HwUnitCnt]],
                                        /* #Violation: Adc_c_REF_7 */
                                        (Saradc_ChannelID)IntChNr,
                                        /* #Violation: Adc_c_REF_7 */
                                        (Saradc_DataReductionMode)GrpPtr->ResultAccumNum);
                    }
                }
            }
        }
#endif /* \(ADC_HW_SYNC_CONV_GROUP_EN == STD_ON) */

        /* Enable the external trigger only for first channel */
        ConversionMode = (0U == ChCnt) ? (ConversionMode | SARADC_QUEUEOPTION_EXTERNALTRIGGER) :
                                         (ConversionMode & (~SARADC_QUEUEOPTION_EXTERNALTRIGGER));
        /* Fill the request to FIFO */
        OperationRslt &= Saradc_Hal_FillQueue(
                                /* #Violation: Adc_c_REF_7 */
                                Adc_BaseAddrs[HwUnitId], (Saradc_ChannelID)IntChNr,
                                /* #Violation: Adc_c_REF_7 */
                                (Saradc_RequestSource)GrpReqSrc,
                                ConversionMode);
    }

#if (defined(ADC_ENABLE_LIMIT_CHECK) && (ADC_ENABLE_LIMIT_CHECK == STD_ON))
    /* Limit checking enabled */
    if (NULL_PTR != AdcKernelPtr->ChCfgPtr[ChIdx].ChLimitCheckingConfigPtr)
    {
        /* Configure the Limit checking boundary */
        OperationRslt &= Saradc_Hal_SetBoundary(Adc_BaseAddrs[HwUnitId],
                    &AdcKernelPtr->ChCfgPtr[ChIdx].ChLimitCheckingConfigPtr->ChLimitChkConfigData);
    }
    else
    {
        /* Reset the bound setting */
        OperationRslt &= Saradc_Hal_SetBoundary(Adc_BaseAddrs[HwUnitId], &Adc_BoundDefaultConfig);
    }
#endif /* \(defined(ADC_ENABLE_LIMIT_CHECK) && (ADC_ENABLE_LIMIT_CHECK == STD_ON))  */

    /* Configuration result interrupt routing */
    RsltIntConfig.interruptEnable = TRUE;
    /* #Violation: Adc_c_REF_7 */
    RsltIntConfig.interruptMapping = (Saradc_InterruptMapping)GrpReqSrc;
    /* Set the result interrupt */
    OperationRslt &= Saradc_Hal_SetResultInterrupt(Adc_BaseAddrs[HwUnitId],
                                /* #Violation: Adc_c_REF_7 */
                                (Saradc_ChannelResult)IntChNr, &RsltIntConfig);

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
    if (ADC_TRIGG_SRC_SW == TriggerSrc)
    {
        if ((ADC_CONV_MODE_ONESHOT == GrpPtr->ConvMode) &&
            (ADC_NO_RESULT_ACCUMU == GrpPtr->ResultAccumNum))
        {
            /* Start software trigger conversion */
            OperationRslt &= Saradc_Hal_SetAlwaysGatingMode(Adc_BaseAddrs[HwUnitId],
                                                           /* #Violation: Adc_c_REF_7 */
                                                           (Saradc_RequestSource)GrpReqSrc);
            /* Start software trigger */
            /* #Violation: Adc_c_REF_7 */
            Saradc_Hal_TriggerBySoftware(Adc_BaseAddrs[HwUnitId], (Saradc_RequestSource)GrpReqSrc);
        }
        else
        {
            /* Use the internal timer to implement the SW continuous mode */
            OperationRslt &= Saradc_Hal_SetTriggerGating(Adc_BaseAddrs[HwUnitId],
                                                         &Adc_ContinuousTimerConfig,
                                                         /* #Violation: Adc_c_REF_7 */
                                                         (Saradc_RequestSource)GrpReqSrc);
            /* #Violation: Adc_c_REF_7 */
            Saradc_Hal_TrigTimerBySoftware(Adc_BaseAddrs[HwUnitId], (Saradc_RequestSource)GrpReqSrc);
        }
    }
    else
#endif /* \(ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */
    {
#if (ADC_HW_TRIGGER_API == STD_ON)
        /* SWS_Adc_00114 */
        /* Enable HW trigger gating */
        OperationRslt &= Saradc_Hal_SetTriggerGating(Adc_BaseAddrs[HwUnitId], 
                                    GrpPtr->HwTrigConfigPtr,
                                    /* #Violation: Adc_c_REF_7 */
                                    (Saradc_RequestSource)GrpReqSrc);
#endif /* \(ADC_HW_TRIGGER_API == STD_ON) */
    }

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_OFF)
    /* #Violation: Adc_c_REF_5 */
    MCAL_UNUSED_VAR(TriggerSrc);
#endif /* \(ADC_ENABLE_START_STOP_GROUP_API == STD_OFF) */

    return OperationRslt;
}
#endif /* \((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || (ADC_HW_TRIGGER_API== STD_ON)) */

#if (ADC_DEINIT_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Adc_CheckGroupStatusAll
*
*   Service ID              : None.
*
*   Description             : This function shall check ADC_E_BUSY for all ADCs are busy or not.
*
*   Parameters in           : None
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK : DET exists;
*                             E_NOT_OK : DET not exists.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_CheckGroupStatusAll
(
    void
)
{
    const Adc_GlobalDataType   *DataPtr;
    Std_ReturnType             RetErr;
    uint8                      LoopCtr;
    uint32                     AllGrpStat;
    Mcal_CoreType              CoreId;
    const Adc_KernelConfigType *KernelPtr;

    RetErr = E_OK;

    /* Get core id which core is currently executing */
    /* #Violation: Adc_c_REF_5 */
    CoreId = Mcal_GetCoreId();

    LoopCtr = 0U;
    /* Loop all HW unit of specified cores */
    while ((LoopCtr < Adc_ConfigPtr->CoreConfigPtr[CoreId]->MaxCoreHwUnit) &&
        /* Exit loop when any one group is not in 'ADC_E_DET_NO_ERR' status */
        (E_OK == RetErr))
    {
        KernelPtr = &(Adc_ConfigPtr->CoreConfigPtr[CoreId]->HwUnitConfigPtr[LoopCtr]);
        /* Get global data pointer of current ADC*/
        DataPtr = ADC_GET_DATAADDRESS(CoreId, KernelPtr->AdcHwUnit);
        /* Get the current ADC HW Unit Group status */
        AllGrpStat = DataPtr->GroupStatus;
        if (AllGrpStat > 0U)
        {
            RetErr = E_NOT_OK;
            /* SWS_Adc_00112: while not all groups are either in state ADC_IDLE or state
                    * ADC_STREAM_COMPLETED */
            /* Service is called while queue is still not empty */
            Adc_ReportRuntimeError(ADC_SID_DEINIT, ADC_E_BUSY);
        }

        LoopCtr++;
    }

    return RetErr;
}

#endif /* \(ADC_DEINIT_API == STD_ON) */

#if ((ADC_INTERRUPT_MODE_ENABLE == STD_ON) || (ADC_POLLING_MODE_ENABLE == STD_ON))
/****************************************************************************************************
*   Function Name           : Adc_CheckDriverState
*
*   Service ID              : None.
*
*   Description             : This function shall check ADC_E_BUSY/ADC_E_IDLE.
*
*   Parameters in           : ServiceId: Service id of calling API.
*                             Group: Group ID.
*                             HwUnitId: Adc HwUnitId number
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK : DET exists;
*                             E_NOT_OK : DET not exists.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_CheckDriverState
(
    Adc_GroupType Group,
    Adc_HwUnitType HwUnitId
)
{
    const Adc_GlobalDataType    *DataPtr;
    Std_ReturnType              RetErr;
    Adc_StatusType              GrpStatus;
    Adc_StatusType              GrpRes;
    Adc_StreamNumSampleType     NoOfValidConv;
    Mcal_CoreType               CoreId;

    RetErr = E_OK;

    /* #Violation: Adc_c_REF_5 */
    CoreId = Mcal_GetCoreId();
    
    /* Get global data pointer of current ADC*/
    DataPtr = ADC_GET_DATAADDRESS(CoreId, HwUnitId);

    /* Get group status */
    /* #Violation: Adc_c_REF_7 */
    GrpStatus = ADC_GET_GROUPSTATUS(DataPtr->GroupStatus, Group);

    /* Get group result status*/
    /* #Violation: Adc_c_REF_7 */
    GrpRes = ADC_GET_RESULTSTATUS(DataPtr->GroupResultStatus, Group);

    /* Read the no. of valid conversation results available */
    NoOfValidConv = DataPtr->NumValidConResPtr[Group];

    /* Check for group status and valid result number */
    if (((ADC_IDLE == GrpStatus) && (ADC_IDLE == GrpRes)) && (0U == NoOfValidConv))
    {
        RetErr = E_NOT_OK;
    }

    return RetErr;
}
#endif /* \((ADC_INTERRUPT_MODE_ENABLE == STD_ON) || (ADC_POLLING_MODE_ENABLE == STD_ON)) */

#if (ADC_DEV_ERROR_DETECT == STD_ON)
/****************************************************************************************************
*   Function Name           : Adc_CheckInit
*
*   Service ID              : None.
*
*   Description             : This function shall check ADC_E_UNINIT DET.
*
*   Parameters in           : ServiceId: Service id of calling API.
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK : DET exists;
*                             E_NOT_OK : DET not exists.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_CheckInit
(
    uint8 ServiceId
)
{
    Std_ReturnType RetErr;
    Mcal_CoreType  CoreId;

    RetErr = E_NOT_OK;

    /* Get core id which core is currently executing */
    /* #Violation: Adc_c_REF_5 */
    CoreId = Mcal_GetCoreId();
    
    if (NULL_PTR == Adc_InstanceDataSet[CoreId])
    {
        /* No HW UNIT are configured for specified core "CoreId" */
        Adc_ReportError(ServiceId, ADC_E_CORE_NOT_CONFIGURED);
    }
    else if (ADC_INITIALIZED != *(Adc_InstanceDataSet[CoreId]->InitStatusPtr))
    {
        /* Reporting of error ADC_E_UNINIT */
        Adc_ReportError(ServiceId, ADC_E_UNINIT);
    }
    else
    {
        RetErr = E_OK;
    }

    return RetErr;
}

/****************************************************************************************************
*   Function Name           : Adc_CommDetCheck
*
*   Service ID              : None.
*
*   Description             : This function shall validate DET error.
*
*   Parameters in           : ServiceId: Service id of calling API.
*                             Group: Group ID.
*                             HwUnitId: Adc HwUnitId number(Hw unit number)
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK : DET exists;
*                             E_NOT_OK : DET not exists.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_CommDetCheck
(
    uint8 ServiceId,
    Adc_GroupType Group,
    Adc_HwUnitType HwUnitId
)
{
    const Adc_GroupCfgType     *GrpPtr;
    const Adc_KernelConfigType *CfgPtr;
    Std_ReturnType             RetErr;
    Mcal_CoreType              CoreId;
    uint8                      HwUnitCoreIdx;

    RetErr = E_OK;

    /* Get core id which core is currently executing */
    /* #Violation: Adc_c_REF_5 */
    CoreId = Mcal_GetCoreId();

    /* Find the sub-index according to the Adc number */
    HwUnitCoreIdx = Adc_ConfigPtr->HwUnitToCorePtr[HwUnitId].CoreHwUnitIdx;

    /* Find the configuration information of current ADC */
    CfgPtr = &(Adc_ConfigPtr->CoreConfigPtr[CoreId]->HwUnitConfigPtr[HwUnitCoreIdx]);

    /*Group id is out of range*/
    if (Group >= CfgPtr->TotCfgGrps)
    {
        /* Invalid group ID passed, report DET error */
        Adc_ReportError(ServiceId, ADC_E_PARAM_GROUP);
        RetErr = E_NOT_OK;
    }
    else
    {
        /* Parameter Group ID is valid check for other errors */
        GrpPtr = &(CfgPtr->GrpCfgPtr[Group]);

        switch (ServiceId)
        {
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
            case ADC_SID_START_GROUP_CONVERSION:
            {
                RetErr = Adc_CheckSwConv(CoreId, HwUnitId, Group, CfgPtr);
                break;
            }
            case ADC_SID_STOP_GROUP_CONVERSION:
            {
                if (GrpPtr->TriggSrc != ADC_TRIGG_SRC_SW)
                {
                    /* Group with trigger source not configured as Software */
                    Adc_ReportError(ServiceId, ADC_E_WRONG_TRIGG_SRC);
                    RetErr = E_NOT_OK;
                }
                break;
            }
#endif /* \(ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */
#if (ADC_HW_TRIGGER_API == STD_ON)
            case ADC_SID_ENABLE_HARDWARE_TRIGGER:
            {
                /* Error check function for Enable Hardware trigger */
                RetErr = Adc_CheckParamGrpEnableHwTrigg(CoreId, Group, HwUnitId, CfgPtr);
                break;
            }
            case ADC_SID_DISABLE_HARDWARE_TRIGGER:
            {
                /* Error check function for Enable Hardware trigger */
                RetErr = Adc_CheckParamGrpDisableHwTrigg(ServiceId, GrpPtr);
                break;
            }
#endif /* \(ADC_HW_TRIGGER_API == STD_ON) */
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
            case ADC_SID_ENABLE_GROUP_NOTIFICATION:
            case ADC_SID_DISABLE_GROUP_NOTIFICATION:
            {
                /* SWS_Adc_00080 */
                /* If function pointer is NULL, DET is reported */
                if (NULL_PTR == GrpPtr->NotifFctPtr)
                {
                    Adc_ReportError(ServiceId, ADC_E_NOTIF_CAPABILITY);
                    RetErr = E_NOT_OK;
                }
                break;
            }
#endif /* \(ADC_GRP_NOTIF_CAPABILITY == STD_ON) */
#if (ADC_DMA_MODE_ENABLE == STD_ON)
            case ADC_SID_GET_GROUP_STATUS:
            {
                if (NULL_PTR != GrpPtr->GroupResRegPtr)
                {
                    /* The function must not be called when using manual result 
                       register configuration. */
                    Adc_ReportError(ServiceId, ADC_E_MANUAL_RESREG_ENABLED);
                    RetErr = E_NOT_OK;
                }
                break;
            }
#endif /* \ (ADC_DMA_MODE_ENABLE == STD_ON) */
            default:
            {
                /* Do Nothing */
                break;
            }
        }
    }

    return RetErr;
}

/****************************************************************************************************
*   Function Name           : Adc_DetErrorCheck
*
*   Service ID              : None
*
*   Description             : DET check for Adc status, Common Det and resource allocation.
*
*   Parameters in           : ServiceId:   Service id of calling API.
*                             Group:       Numeric ID of requested ADC Channel group.
*                             HwUnitId: The Group Id for particular HwUnitId.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : None
*
*   Return value            : E_OK :     DET error exists;
*                             E_NOT_OK : DET error not exists.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None
****************************************************************************************************/
/* #Violation: Adc_c_REF_13 */
static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_DetErrorCheck
(
    uint8 ServiceId,
    Adc_GroupType Group,
    Adc_HwUnitType HwUnitId
)
{
    Std_ReturnType Error;

    /* Check Initialization status */
    Error = Adc_CheckInit(ServiceId);
    if (E_OK == (Std_ReturnType)Error)
    {
        /* Check multi-core resources */
        Error = Adc_CheckMulticoreAllocateError(ServiceId, HwUnitId);
        if (E_OK == Error)
        {
            /* Common check */
            Error = Adc_CommDetCheck(ServiceId, Group, HwUnitId);
        }
    }

    return Error;
}

/****************************************************************************************************
*   Function Name           : Adc_CheckInitParam
*
*   Service ID              : None.
*
*   Description             : This function shall check ADC_E_ALREADY_INITIALIZED and
*                             ADC_E_PARAM_CONFIG DET.
*
*   Parameters in           : ConfigPtr: configuration pointer.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK : DET exists;
*                             E_NOT_OK : DET not exists.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_CheckInitParam
(
    CONSTP2CONST(Adc_ConfigType, AUTOMATIC, ADC_APPL_CONST) ConfigPtr
)
{
    Mcal_CoreType      CoreId;
    Std_ReturnType     RetErr;

    RetErr = E_NOT_OK;

    /* Get core id which core is currently executing */
    /* #Violation: Adc_c_REF_5 */
    CoreId = Mcal_GetCoreId();

    if (NULL_PTR == Adc_InstanceDataSet[CoreId])
    {
        /* No HW UNIT are configured for specified core "CoreId" */
        Adc_ReportError(ADC_SID_INIT, ADC_E_CORE_NOT_CONFIGURED);
    }
    else if (ADC_INITIALIZED == *(Adc_InstanceDataSet[CoreId]->InitStatusPtr))
    {
        /* SWS_Adc_00107: DET for ADC_E_ALREADY_INITIALIZED */
        /* ADC Driver initialization is called twice before De-init */
        Adc_ReportError(ADC_SID_INIT, ADC_E_ALREADY_INITIALIZED);
    }
    else if (NULL_PTR == ConfigPtr)
    {
        /* SWS_Adc_00343: DET for ADC_E_PARAM_CONFIG */
        /* ConfigPtr is NULL_PTR, report DET error for variant PB */
        Adc_ReportError(ADC_SID_INIT, ADC_E_PARAM_CONFIG);
    }
    else if (NULL_PTR == ConfigPtr->CoreConfigPtr[CoreId])
    {
        /* No configuration information in specified core */
        Adc_ReportError(ADC_SID_INIT, ADC_E_CORE_NOT_CONFIGURED);
    }
    else
    {
        RetErr = E_OK;
    }

    return RetErr;
}

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Adc_CheckSwConv
*
*   Service ID              : None.
*
*   Description             : This function shall check trigger source and result buffer.
*
*   Parameters in           : ServiceId: Service id of calling API.
*                             HwUnitId: the ADC number.
*                             Group: Group ID.
*                             AdcKernelPtr: Pointer to the HW unit configuration parameters.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK : DET exists;
*                             E_NOT_OK : DET not exists.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_CheckSwConv
(
    Mcal_CoreType CoreId,
    Adc_HwUnitType HwUnitId,
    Adc_GroupType Group,
    CONSTP2CONST(Adc_KernelConfigType, AUTOMATIC, ADC_APPL_DATA) AdcKernelPtr
)
{
    const Adc_ValueGroupType *DataValueBfPtr;
    const Adc_GroupCfgType   *GrpPtr;
    Std_ReturnType           RetErr;

    RetErr = E_NOT_OK;

    /* Parameter Group ID is valid check for other errors */
    GrpPtr = &(AdcKernelPtr->GrpCfgPtr[Group]);

    if (GrpPtr->TriggSrc != ADC_TRIGG_SRC_SW)
    {
        /* Group with trigger source not configured as Software */
        Adc_ReportError(ADC_SID_START_GROUP_CONVERSION, ADC_E_WRONG_TRIGG_SRC);
    }
    else
    {
#if (ADC_DMA_MODE_ENABLE == STD_ON)
        if (ADC_RESULT_HANDLING_DMA_MODE == AdcKernelPtr->RsltHldMthd)
        {
            RetErr = E_OK;
        }
        else
#endif /* \(ADC_DMA_MODE_ENABLE == STD_ON) */
        {
            /* Not in DMA mode */
            /* Get global data value buffer pointer of current ADC*/
            /* #Violation: Adc_c_REF_5 */
            DataValueBfPtr = ADC_GET_RESULTBUFFERADDRESS(CoreId, HwUnitId, Group);
            if (NULL_PTR == DataValueBfPtr)
            {
                /* Group is not initialized for Result buffer */
                Adc_ReportError(ADC_SID_START_GROUP_CONVERSION, ADC_E_BUFFER_UNINIT);
            }
            else
            {
                RetErr = E_OK;
            }
        }
    }

    return RetErr;
}
#endif /* \(ADC_ENABLE_START_STOP_GROUP_API== STD_ON)*/

#if (ADC_HW_TRIGGER_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Adc_CheckParamGrpEnableHwTrigg
*
*   Service ID              : None.
*
*   Description             : This function shall check trigger source, conversion mode
*                             and result buffer. When enable Adc hardware trigger.
*
*   Parameters in           : ServiceId: Service id of calling API.
*                             Group: Group ID.
*                             HwUnitId: the ADC number.
*                             AdcKernelPtr: Pointer to the ADC configuration information
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK : DET exists;
*                             E_NOT_OK : DET not exists.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_CheckParamGrpEnableHwTrigg
(
    Mcal_CoreType CoreId,
    Adc_GroupType Group,
    Adc_HwUnitType HwUnitId,
    CONSTP2CONST(Adc_KernelConfigType, AUTOMATIC, ADC_APPL_DATA) AdcKernelPtr
)
{
    const Adc_ValueGroupType *DataValueBfPtr;
    const Adc_GroupCfgType   *GrpPtr;
    Std_ReturnType           RetErr;

    RetErr = E_NOT_OK;

    /* Parameter Group ID is valid check for other errors */
    GrpPtr = &(AdcKernelPtr->GrpCfgPtr[Group]);

    if (GrpPtr->TriggSrc != ADC_TRIGG_SRC_HW)
    {
        /* Group with trigger source not configured as Hardware */
        Adc_ReportError(ADC_SID_ENABLE_HARDWARE_TRIGGER, ADC_E_WRONG_TRIGG_SRC);
    }
    else if (ADC_CONV_MODE_CONTINUOUS == GrpPtr->ConvMode)
    {
        /* Service is called for group with continuous mode,
           report the DET error */
        Adc_ReportError(ADC_SID_ENABLE_HARDWARE_TRIGGER, ADC_E_WRONG_CONV_MODE);
    }
    else
    {
#if (ADC_DMA_MODE_ENABLE == STD_ON)
        if (ADC_RESULT_HANDLING_DMA_MODE == AdcKernelPtr->RsltHldMthd)
        {
            RetErr = E_OK;
        }
        else
#endif /* \(ADC_DMA_MODE_ENABLE == STD_ON) */
        {
            /* Get global data value buffer pointer of current ADC*/
            /* #Violation: Adc_c_REF_5 */
            DataValueBfPtr = ADC_GET_RESULTBUFFERADDRESS(CoreId, HwUnitId, Group);
            if (NULL_PTR == DataValueBfPtr)
            {
                /* Group is not initialized for Result buffer */
                Adc_ReportError(ADC_SID_ENABLE_HARDWARE_TRIGGER, ADC_E_BUFFER_UNINIT);
            }
            else
            {
                RetErr = E_OK;
            }
        }
    }

    return RetErr;
}

/****************************************************************************************************
*   Function Name           : Adc_CheckParamGrpDisableHwTrigg
*
*   Service ID              : None.
*
*   Description             : This function shall check trigger source, conversion mode
*                             and result buffer. When disable Adc hardware trigger.
*
*   Parameters in           : ServiceId: Service id of calling API.
*                             GrpPtr: the configuration information of current ADC.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK : DET exists;
*                             E_NOT_OK : DET not exists.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_CheckParamGrpDisableHwTrigg
(
    uint8 ServiceId,
    CONSTP2CONST(Adc_GroupCfgType, AUTOMATIC, ADC_APPL_DATA) GrpPtr
)
{
    Std_ReturnType           RetErr;

    if (GrpPtr->TriggSrc != ADC_TRIGG_SRC_HW)
    {
        /* Group with trigger source not configured as Hardware */
        Adc_ReportError(ServiceId, ADC_E_WRONG_TRIGG_SRC);
        RetErr = E_NOT_OK;
    }
    else if (ADC_CONV_MODE_CONTINUOUS == GrpPtr->ConvMode)
    {
        /* Service is called for group with continuous mode,
           report the DET error */
        Adc_ReportError(ServiceId, ADC_E_WRONG_CONV_MODE);
        RetErr = E_NOT_OK;
    }
    else
    {
        /* Condition Satisfied */
        RetErr = E_OK;
    }

    return RetErr;
}
#endif /* \(ADC_HW_TRIGGER_API == STD_ON) */
#endif /* \(ADC_DEV_ERROR_DETECT== STD_ON)*/

#if (ADC_DEV_ERROR_DETECT == STD_ON)
/****************************************************************************************************
*   Function Name           : Adc_CheckMulticoreAllocateError
*
*   Service ID              : None.
*
*   Description             : This function shall check ADC_E_CORE_NOT_CONFIGURED and
*                             ADC_E_CORE_HWUNIT_MISMATCH DET.
*
*   Parameters in           : ServiceId: Service API ID;
*                             HwUnitId: ADC HW unit number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK : DET exists;
*                             E_NOT_OK : DET not exists.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_CheckMulticoreAllocateError
(
    uint8 ServiceId,
    Adc_HwUnitType HwUnitId
)
{
    Std_ReturnType             RetErr;
    Mcal_CoreType              CoreId;
    uint8                      HwUnitCoreIdx;
    const Adc_KernelConfigType *CfgPtr;

    RetErr = E_NOT_OK;

    if (HwUnitId >= ADC_MAX_KERNELS)
    {
        /* HW unit is wrong */
        Adc_ReportError(ServiceId, ADC_E_PARAM_GROUP);
    }
    else
    {
        /* Get core id which core is currently executing */
        /* #Violation: Adc_c_REF_5 */
        CoreId = Mcal_GetCoreId();

        /* Find the sub-index according to the Adc number */
        HwUnitCoreIdx = Adc_ConfigPtr->HwUnitToCorePtr[HwUnitId].CoreHwUnitIdx;
        if (HwUnitCoreIdx >= Adc_ConfigPtr->CoreConfigPtr[CoreId]->MaxCoreHwUnit)
        {
            /* Parameter of ADC Hwunit is out of range */
            Adc_ReportError(ServiceId, ADC_E_CORE_HWUNIT_MISMATCH);
        }
        else
        {
            CfgPtr = &Adc_ConfigPtr->CoreConfigPtr[CoreId]->HwUnitConfigPtr[HwUnitCoreIdx];
            if (NULL_PTR == CfgPtr)
            {
                /* No HW UNIT are configured for specified core "CoreId" */
                Adc_ReportError(ServiceId, ADC_E_CORE_NOT_CONFIGURED);
            }
            else if (HwUnitId !=
                      Adc_ConfigPtr->CoreConfigPtr[CoreId]->HwUnitConfigPtr[HwUnitCoreIdx].AdcHwUnit)
            {
                /* Parameter of ADC Hwunit is not equal to the actual assigned ADC HW unit
                 * for specified core */
                Adc_ReportError(ServiceId, ADC_E_CORE_HWUNIT_MISMATCH);
            }
            else
            {
                RetErr = E_OK;
            }
        }
    }

    return RetErr;
}

#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */

/****************************************************************************************************
*   Function Name           : Adc_ResetTrigSrcData
*
*   Service ID              : None.
*
*   Description             : Reset the queue data in the ADC runtime.
*
*   Parameters in           : GrpPtr: the group configuration pointer.
*                             DataPtr: pointer to ADC runtime.
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
static FUNC(void, ADC_PRIVATE_CODE) Adc_ResetTrigSrcData
(
    CONSTP2CONST(Adc_GroupCfgType, AUTOMATIC, ADC_APPL_DATA) GrpPtr,
    /* #Violation: Adc_c_REF_12 */
    CONSTP2VAR(Adc_GlobalDataType, AUTOMATIC, ADC_APPL_DATA) DataPtr
)
{
    /* Update the Trigger source data */
    DataPtr->TriggSrcData[(uint8)GrpPtr->GrpRequestSrc].GrpId = ADC_GRP_REQ_SRC_FREE;
    DataPtr->TriggSrcData[(uint8)GrpPtr->GrpRequestSrc].GrpPriority = ADC_INVALID_PRIORITY;

#if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || (ADC_HW_TRIGGER_API == STD_ON))
    /* Hardware priority or Full Priority considered */
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
    /* Clears the currently running channel mask with the channels that are part of the 
       stopped group */
    DataPtr->AllRunningCh &= (uint16)(~(GrpPtr->IntChMask));
#endif /* (ADC_PRIORITY_IMPLEMENTATION \!= ADC_PRIORITY_NONE) */
#endif /* ((ADC_ENABLE_START_STOP_GROUP_API \== STD_ON) || (ADC_HW_TRIGGER_API \== STD_ON)) */
}

#if (ADC_READ_GROUP_API == STD_ON)
#if ((ADC_INTERRUPT_MODE_ENABLE == STD_ON) || (ADC_POLLING_MODE_ENABLE == STD_ON))
#if (ADC_DEV_ERROR_DETECT == STD_ON)
/****************************************************************************************************
*   Function Name           : Adc_ReadGroupDetCheck
*
*   Service ID              : None
*
*   Description             : API Adc_ReadGroup Det check function.
*
*   Parameters in           : Group:         Numeric ID of requested ADC Channel group.
*                             PhyHwUnitId:   The Group Id for particular PhyHwUnitId.
*                             DataBufferPtr: ADC results of all channels of the selected group are
*                                            stored in the data buffer addressed with the pointer.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : None
*
*   Return value            : E_OK :     DET exists;
*                             E_NOT_OK : DET not exists.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None
****************************************************************************************************/
static FUNC(Std_ReturnType, ADC_PRIVATE_CODE) Adc_ReadGroupDetCheck
(
    Adc_GroupType GroupId,
    Adc_HwUnitType PhyHwUnitId,
    P2CONST(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) DataBufferPtr
)
{
#if (ADC_DMA_MODE_ENABLE == STD_ON)
    Mcal_CoreType  CoreId;
    uint8          HwUnitCoreIdx;
#endif /* \(ADC_DMA_MODE_ENABLE == STD_ON) */
    Std_ReturnType Error;

    /* The Adc_DetErrorCheck function covers the following SWS */
    /* SWS_Adc_00296: called prior to initializing the driver */
    /* SWS_Adc_00152: group ID is non-existing */
    /* Check for ADC_E_PARAM_GROUP */
    Error = Adc_DetErrorCheck(ADC_SID_READ_GROUP, GroupId, PhyHwUnitId);
    if (E_OK == Error)
    {
        if(NULL_PTR == DataBufferPtr)
        {
            /* SWS_Adc_00457: when called with a NULL_PTR as DataBufferPtr */
            Adc_ReportError(ADC_SID_READ_GROUP, ADC_E_PARAM_POINTER);
            Error = E_NOT_OK;
        }
        else
        {
#if (ADC_DMA_MODE_ENABLE == STD_ON)
            /* #Violation: Adc_c_REF_5 */
            CoreId = Mcal_GetCoreId();
            /* Find the sub-index according to the Adc number */
            HwUnitCoreIdx = Adc_ConfigPtr->HwUnitToCorePtr[PhyHwUnitId].CoreHwUnitIdx;
            if (ADC_RESULT_HANDLING_DMA_MODE == Adc_ConfigPtr->CoreConfigPtr[CoreId]->
                                        HwUnitConfigPtr[HwUnitCoreIdx].RsltHldMthd)
            {
                /* This group of HW unit is in DMA mode */
                Adc_ReportError(ADC_SID_READ_GROUP, ADC_E_DMA_CHANNEL_ENABLED);
                Error = E_NOT_OK;
            }
#endif /* \(ADC_DMA_MODE_ENABLE == STD_ON) */
        }
    }

    return Error;
}
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
#endif /* \((ADC_INTERRUPT_MODE_ENABLE == STD_ON) || (ADC_POLLING_MODE_ENABLE== STD_ON)) */
#endif /* \(ADC_READ_GROUP_API == STD_ON) */

#if (ADC_HW_TRIGGER_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Adc_LocalDisableHardwareTrigger
*
*   Service ID              : None
*
*   Description             : Disables the hardware trigger for the requested ADC Channel group.
*
*   Parameters in           : Group: Numeric ID of requested ADC Channel group.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : None.
*
*   Return value            : TRUE: No Safety error.
*                             FALSE: Safety error exists.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Adc_91002, SWS_Adc_00413
****************************************************************************************************/
static FUNC(boolean, ADC_PRIVATE_CODE) Adc_LocalDisableHardwareTrigger
(
    Adc_GroupType    GroupId,
    Adc_HwUnitType   PhyHwUnitId,
    P2VAR(Adc_GlobalDataType, AUTOMATIC, ADC_APPL_DATA) DataPtr,
    Mcal_CoreType    CoreId
)
{
    uint8                      HwUnitCoreIdx;
    boolean                    OperationRslt;
    const Adc_GroupCfgType     *GrpPtr;
    const Adc_KernelConfigType *AdcKernelPtr;

    OperationRslt = TRUE;

    /* Find the sub-index according to the Adc number */
    HwUnitCoreIdx = Adc_ConfigPtr->HwUnitToCorePtr[PhyHwUnitId].CoreHwUnitIdx;
    /* Get PhyHwUnitId configuration Pointer */
    AdcKernelPtr =
            &(Adc_ConfigPtr->CoreConfigPtr[CoreId]->HwUnitConfigPtr[HwUnitCoreIdx]);

    /* Find the configuration information of current ADC */
    GrpPtr = &(AdcKernelPtr->GrpCfgPtr[GroupId]);

    /* Enter Critical section */
    ADC_ENTER_CRITICAL_SECTION(DisableHwTrig);

    /* Clear ADC Group Result Status */
    /* #Violation: Adc_c_REF_10 */
    ADC_CLR_RESULTSTATUS(DataPtr->GroupResultStatus, GroupId);

    /* Reset the End result status to 0 */
    /* #Violation: Adc_c_REF_10 */
    ADC_CLR_RESBUFENDSTATUS(DataPtr->GrpBufferEndResultStatus, GroupId);

    /* check and handle to stop group */
    /* #Violation: Adc_c_REF_7 */
    if (ADC_IDLE != ADC_GET_GROUPSTATUS(DataPtr->GroupStatus, GroupId))
    {
        DataPtr->TriggSrcData[GrpPtr->GrpRequestSrc].IsrServReqFlg = ADC_NO_SERVICE;

        /* SWS_Adc_00116: shall disable the hardware trigger */
        /* SWS_Adc_00145: shall abort an ongoing conversion */
        /* Stop the Conversion Request Source */
        OperationRslt = Adc_StopConvRequestSource(GrpPtr, PhyHwUnitId);

        /* Update request source data and Adc_AllRunningCh */
        Adc_ResetTrigSrcData(GrpPtr, DataPtr);

        /* SWS_Adc_00361: shall set the group status to state ADC_IDLE */
        /* Group status of given group is made ADC_IDLE */
        /* #Violation: Adc_c_REF_10 */
        ADC_CLR_GROUPSTATUS(DataPtr->GroupStatus, GroupId);

#if (ADC_ENABLE_QUEUING == STD_ON)
        /* SWS_Adc_00429: shall remove any queued start/restart request if
        * queuing is enabled */
        /* Queue Enable is STD_ON only during No priority */
        /* If a group from SW trigger is exists in queue */
        /* Pop index will be the next Group in Queue */
        DataPtr->PopGroupId = DataPtr->QueueOfSwGroupPtr[GroupId].NextGroup;

        /* If Pop index has valid Group Id, request for start conversion */
        if (DataPtr->PopGroupId != ADC_INVALID_GROUP_ID)
        {
            /* Reset, next Group to invalid */
            DataPtr->QueueOfSwGroupPtr[GroupId].NextGroup = ADC_INVALID_GROUP_ID;

            DataPtr->QueueOfSwGroupPtr[DataPtr->PopGroupId].PreviousGroup =
                                                            ADC_INVALID_GROUP_ID;

            /* Get the Group configuration data pointer */
            GrpPtr = (AdcKernelPtr->GrpCfgPtr) + DataPtr->PopGroupId;

            /* GrpId is updated with the requested Group */
            DataPtr->TriggSrcData[GrpPtr->GrpRequestSrc].GrpId = DataPtr->PopGroupId;

            /* Permit ISR calling */
            DataPtr->TriggSrcData[GrpPtr->GrpRequestSrc].IsrServReqFlg = ADC_ISR_REQ_SEV;

            /* Trigger the Conversion Request Source */
            OperationRslt &= Adc_StartConversion(PhyHwUnitId, AdcKernelPtr, GrpPtr,
                                                                    ADC_TRIGG_SRC_SW);
        }
        else /* If Pop Group ID is invalid, then there is no Group in the Queue,
                Reset Push Group Id to invalid */
        {
            DataPtr->PushGroupId = ADC_INVALID_GROUP_ID;
        }
#endif /* \(ADC_ENABLE_QUEUING == STD_ON) */

#if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
        /* Full priority considered */
        /* Schedule the next conversion in the stopped trigger source */
        OperationRslt &= Adc_ScheduleNext(PhyHwUnitId, GrpPtr->GrpRequestSrc,
                                                                AdcKernelPtr, DataPtr);
#endif /* \(ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */
    }
    /* Clear ADC Group Result Status */
    /* #Violation: Adc_c_REF_10 */
    /* #Violation: Adc_c_REF_15 */
    ADC_CLR_RESULTSTATUS(DataPtr->GroupResultStatus, GroupId);
    /* Reset the End result status to 0 */
    /* #Violation: Adc_c_REF_10 */
    /* #Violation: Adc_c_REF_15 */
    ADC_CLR_RESBUFENDSTATUS(DataPtr->GrpBufferEndResultStatus, GroupId);

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    /* SWS_Adc_00157: shall disable the notification mechanism */
    /* #Violation: Adc_c_REF_10 */
    ADC_DISABLE_NOTIF(DataPtr->GrpNotifStatus, GroupId);
#endif /* \(ADC_GRP_NOTIF_CAPABILITY == STD_ON) */

    /* Exit Critical section */
    ADC_EXIT_CRITICAL_SECTION(DisableHwTrig);

#if ((ADC_ENABLE_QUEUING != STD_ON) && (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_HW_SW))
    /* #Violation: Adc_c_REF_5 */
    MCAL_UNUSED_VAR(AdcKernelPtr);
#endif /* (\(ADC_ENABLE_QUEUING != STD_ON)&&\(ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_HW_SW)) */

    return OperationRslt;
}
#endif /* \(ADC_HW_TRIGGER_API == STD_ON) */

/* #Violation: Adc_c_REF_12 */
#define ADC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Adc_c_REF_1 */
#include "Adc_MemMap.h"

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/* #Violation: Adc_c_REF_12 */
#define ADC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Adc_c_REF_1 */
#include "Adc_MemMap.h"

/****************************************************************************************************
*   Function Name           : Adc_Init
*
*   Service ID              : 0x00
*
*   Description             : Initializes the ADC hardware units and driver.
*                     
*   Parameters in           : ConfigPtr: Pointer to configuration set in Variant PB.
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
*   Preconditions           : Adc driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Adc_00365.
****************************************************************************************************/
/* #Violation: Adc_c_REF_13 */
FUNC(void, ADC_PUBLIC_CODE) Adc_Init
(
    /* #Violation: Adc_c_REF_8 */
    P2CONST(Adc_ConfigType, AUTOMATIC, ADC_APPL_CONST) ConfigPtr
)
{
    uint8                      Cnt;
    boolean                    HwUnitReadFlag;
    uint8                      HWUnitIdx;
    uint8                      ChIdx;
    const Adc_KernelConfigType *KernelPtr;
    Mcal_CoreType              CoreId;
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    uint32                     Err;
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
    uint32                     OperationRslt;

    OperationRslt = TRUE;
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    Err = Adc_CheckInitParam(ConfigPtr);
    if (E_OK == Err)
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
    {
        /* SWS_Adc_00054: In case of Variant PB: The function Adc_Init shall initialize the
         * ADC hardware units and driver according to the configuration set referenced
         * by ConfigPtr */
        /* Store ConfigPtr to use for other APIs when 'Adc_ConfigPtr' is not NULL
         * For avoid repeat-set when multi-core used */
        Adc_ConfigPtr = ConfigPtr;

        /* Get core id which core is currently executing */
        /* #Violation: Adc_c_REF_5 */
        CoreId = Mcal_GetCoreId();
        
        /* SWS_Adc_00056: initialize the configured resources */
        for (HWUnitIdx = 0U; (HWUnitIdx < ConfigPtr->CoreConfigPtr[CoreId]->MaxCoreHwUnit)
#if (ADC_SAFETY_ENABLE == STD_ON)
                && (TRUE == OperationRslt)
#endif /* \(ADC_SAFETY_ENABLE == STD_ON) */
        ;HWUnitIdx++)
        {
            /* Find the configuration parameters of current ADC */
            /* Assign the ADC HwUnitId Configuration point to the local pointer */
            KernelPtr = &(ConfigPtr->CoreConfigPtr[CoreId]->HwUnitConfigPtr[HWUnitIdx]);

            ADC_ENTER_CRITICAL_SECTION(Endinit);

            /* Critical protection for register update with Endinit */
            /* Initialize ADC HW units */
            OperationRslt &= Saradc_Hal_InitModule(Adc_BaseAddrs[KernelPtr->AdcHwUnit], 
                                                KernelPtr->HwCfgPtr);

            ADC_EXIT_CRITICAL_SECTION(Endinit);

            Cnt = 0U;
            do
            {
                Cnt++;
                /* Get HWunit enable status */
                HwUnitReadFlag = Saradc_Hal_GetAnalogReadyFlg(Adc_BaseAddrs[KernelPtr->AdcHwUnit]);
            } while ((Cnt < ADC_HWUNIT_ENABLE_TIMEOUT) && (FALSE == HwUnitReadFlag));

            if (FALSE == HwUnitReadFlag)
            {
                OperationRslt = FALSE;
            }
            else
            {
                ADC_ENTER_CRITICAL_SECTION(Endinit);

#if (ADC_STARTUP_CALIBRATION == STD_ON)
                OperationRslt &= Saradc_Hal_OpenCalibration(Adc_BaseAddrs[KernelPtr->AdcHwUnit]);
#endif /* \(ADC_STARTUP_CALIBRATION == STD_ON) */

                /* Initialize the channels */
                for (ChIdx = 0U; ChIdx < KernelPtr->ChNum; ChIdx++)
                {
                    OperationRslt &= Saradc_Hal_InitChannel(Adc_BaseAddrs[KernelPtr->AdcHwUnit],
                            /* #Violation: Adc_c_REF_7 */
                            (Saradc_ChannelID)KernelPtr->ChCfgPtr[ChIdx].ChConfigData.channelResult,
                            &KernelPtr->ChCfgPtr[ChIdx].ChConfigData);
                }

#if (ADC_POLLING_MODE_ENABLE == STD_ON)
                if (ADC_RESULT_HANDLING_POLLING_MODE == KernelPtr->RsltHldMthd)
                {
                    /* Mask the result interrupt */
                    OperationRslt &=
                        Saradc_Hal_MaskResultInterrupt(Adc_BaseAddrs[KernelPtr->AdcHwUnit], TRUE);
                }
                else
#endif /* \(ADC_POLLING_MODE_ENABLE == STD_ON) */
#if (ADC_DMA_MODE_ENABLE == STD_ON)
                if (FALSE == KernelPtr->IsIntEn)
                {
                    /* Interrupt is not enabled when in DMA mode */
                    /* Mask the result interrupt */
                    OperationRslt &=
                        Saradc_Hal_MaskResultInterrupt(Adc_BaseAddrs[KernelPtr->AdcHwUnit], TRUE);
                }
                else
#endif /* \(ADC_DMA_MODE_ENABLE == STD_ON) */
                {
                    /* Un-Mask the result interrupt */
                    OperationRslt &=
                        Saradc_Hal_MaskResultInterrupt(Adc_BaseAddrs[KernelPtr->AdcHwUnit], FALSE);
                }

                ADC_EXIT_CRITICAL_SECTION(Endinit);
            }

            /* Initialize global variable */
            Adc_InitGlobalVariables(KernelPtr->AdcHwUnit);
        }

#if (ADC_DEV_ERROR_DETECT == STD_ON)
#if (ADC_SAFETY_ENABLE == STD_ON)
        if (TRUE == OperationRslt)
#endif /* \(ADC_SAFETY_ENABLE == STD_ON) */
        {
            /* Set Status to indicate that initialization is done */
            *(Adc_InstanceDataSet[CoreId]->InitStatusPtr) = ADC_INITIALIZED;
        }
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
    }

#if (ADC_SAFETY_ENABLE == STD_ON)
    if (OperationRslt == FALSE)
    {
        Adc_ReportRuntimeError(ADC_SID_INIT, ADC_E_REG_CHECK_FAIL);
    }
#else /* \(ADC_SAFETY_ENABLE == STD_ON) */
    /* #Violation: Adc_c_REF_5 */
    MCAL_UNUSED_VAR(OperationRslt);
#endif /* \(ADC_SAFETY_ENABLE == STD_ON) */

}

/* SWS_Adc_00228: shall be pre compile time configurable On/Off */
#if (ADC_DEINIT_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Adc_DeInit
*
*   Service ID              : 0x01
*
*   Description             : Returns all ADC HW Units to a state comparable to their power
*                             on reset state.
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
*   AUTOSAR_Requirement     : SWS_Adc_00366.
****************************************************************************************************/
/* #Violation: Adc_c_REF_13 */
FUNC(void, ADC_PUBLIC_CODE) Adc_DeInit
(
    void
)
{
    Std_ReturnType             Err;
    Std_ReturnType             LockStatus;
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    Adc_GlobalDataType         *DataPtr;
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
    uint8                      PhyHwUnitId;
    boolean                    OperationRslt;
#if ((ADC_GRP_NOTIF_CAPABILITY == STD_ON) || (ADC_HW_TRIGGER_API == STD_ON))
    const Adc_KernelConfigType *KernelPtr;
#endif /* \((ADC_GRP_NOTIF_CAPABILITY == STD_ON) || (ADC_HW_TRIGGER_API== STD_ON)) */
    Mcal_CoreType              CoreId;
    
    OperationRslt = TRUE;

#if (ADC_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Adc_00154: Check for DET error ADC_E_UNINIT */
    Err = Adc_CheckInit(ADC_SID_DEINIT);
    if (E_OK == Err)
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
    {
        /* SWS_Adc_00358: environment shall not call this function while any group in BUSY status */
        /* Check for ADC_E_BUSY */
        Err = Adc_CheckGroupStatusAll();
        if (E_OK == Err)
        {
            /* Get core id which core is currently executing */
            /* #Violation: Adc_c_REF_5 */
            CoreId = Mcal_GetCoreId();
            
            for (PhyHwUnitId = 0U; 
                        (PhyHwUnitId < Adc_ConfigPtr->CoreConfigPtr[CoreId]->MaxCoreHwUnit)
                        && (TRUE == OperationRslt)
                        ; PhyHwUnitId++)
            {
                /* Find the configuration information of current HW unit */
                KernelPtr = &(Adc_ConfigPtr->CoreConfigPtr[CoreId]->HwUnitConfigPtr[PhyHwUnitId]);

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
                /* Disable notification for all groups in a ADC */
                /* Get global data pointer of current ADC */
                DataPtr = ADC_GET_DATAADDRESS(CoreId, KernelPtr->AdcHwUnit);
                /* SWS_Adc_00111: Disable all notification */
                DataPtr->GrpNotifStatus = 0U;
#endif /* \(ADC_GRP_NOTIF_CAPABILITY == STD_ON) */

                ADC_ENTER_CRITICAL_SECTION(DeInit);
                /* Lock for disable interrupts */
                LockStatus = Mcal_GetLock(MCAL_LOCK_ID_RCC);
                if (E_OK == LockStatus)
                {
                    /* SWS_Adc_00110 */
                    /* Reset HW unit */
                    OperationRslt &= Saradc_Hal_DeInitModule(Adc_BaseAddrs[KernelPtr->AdcHwUnit]);

                    /* Release software lock for INTC */
                    Mcal_ReleaseLock(MCAL_LOCK_ID_RCC);
                }
                else 
                {
                    /* Get lock failed */
                    OperationRslt = FALSE;
                }
                ADC_EXIT_CRITICAL_SECTION(DeInit);
            }
            
#if (ADC_SAFETY_ENABLE == STD_ON)
            if (FALSE == OperationRslt)
            {
                /* Safety error check failed */
                Adc_ReportRuntimeError(ADC_SID_DEINIT, ADC_E_REG_CHECK_FAIL);
            }
            else
#endif /* \(ADC_SAFETY_ENABLE == STD_ON) */
            {
#if (ADC_DEV_ERROR_DETECT == STD_ON)
                *(Adc_InstanceDataSet[CoreId]->InitStatusPtr) = ADC_UNINITIALIZE;
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
            }
        }
    }
}
#endif /* \(ADC_DEINIT_API == STD_ON) */

#if ((ADC_INTERRUPT_MODE_ENABLE == STD_ON) || (ADC_POLLING_MODE_ENABLE == STD_ON))
/****************************************************************************************************
*   Function Name           : Adc_SetupResultBuffer
*
*   Service ID              : 0x0C
*
*   Description             : Initializes ADC driver with the group specific result buffer start
*                             address where the conversion results will be stored. The application
*                             has to ensure that the application buffer, where DataBufferPtr points
*                             to, can hold all the conversion results of the specified group. The
*                             initialization with Adc_SetupResultBuffer is required after reset,
*                             before a group conversion can be started.
*
*   Parameters in           : Group: Numeric ID of requested ADC channel group.
*                             DataBufferPtr: Pointer to result data buffer.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK:  result buffer pointer initialized correctly
*                             E_NOT_OK: operation failed or development error occurred
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Adc_91000, SWS_Adc_00413.
****************************************************************************************************/
/* #Violation: Adc_c_REF_13 */
FUNC(Std_ReturnType, ADC_PUBLIC_CODE) Adc_SetupResultBuffer
(
    Adc_GroupType Group,
    /* #Violation: Adc_c_REF_8 */
    /* #Violation: Adc_c_REF_9 */
    P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) DataBufferPtr
)
{
#if (ADC_DEV_ERROR_DETECT == STD_ON)
#if (ADC_DMA_MODE_ENABLE == STD_ON)
    uint8                    HwUnitIndex;
#endif /* \(ADC_DMA_MODE_ENABLE == STD_ON) */
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
    Adc_GroupType            GroupId;
    Std_ReturnType           RetStatus;
    Adc_HwUnitType           PhyHwUnitId;
    Mcal_CoreType            CoreId;
    const Adc_GlobalDataType *DataPtr;

    /* Get PhyHwUnitId number from Group Id */
    /* #Violation: Adc_c_REF_5 */
    PhyHwUnitId = (Adc_HwUnitType)ADC_GET_HWUNITID(Group);

    /* Get the Group Id for specified PhyHwUnitId */
    /* #Violation: Adc_c_REF_5 */
    GroupId = (Adc_GroupType)ADC_GET_GROUPID(Group);

#if (ADC_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Adc_00434: when called prior to initializing the driver */
    /* Check for DET error ADC_E_UNINIT */
    RetStatus = Adc_CheckInit(ADC_SID_SETUP_RESULT_BUFFER);
    if (E_OK == RetStatus)
#endif /* \ADC_DEV_ERROR_DETECT == STD_ON) */
    {
        /* #Violation: Adc_c_REF_5 */
        CoreId = Mcal_GetCoreId();

#if (ADC_DEV_ERROR_DETECT == STD_ON)
        /* SWS_Adc_00423: group is non-existing */
        RetStatus = Adc_CheckMulticoreAllocateError(ADC_SID_SETUP_RESULT_BUFFER, PhyHwUnitId);
        if (E_OK == RetStatus)
        {
            /* SWS_Adc_00423: group is non-existing */
            /* Check for ADC_E_PARAM_GROUP */
            RetStatus = Adc_CommDetCheck(ADC_SID_SETUP_RESULT_BUFFER, GroupId, PhyHwUnitId);
        }

        if (E_OK == RetStatus)
        {
            /* Check for ADC_E_PARAM_POINTER */
            if(NULL_PTR == DataBufferPtr)
            {
                /* SWS_Adc_00457: when called with a NULL_PTR as DataBufferPtr */
                Adc_ReportError(ADC_SID_SETUP_RESULT_BUFFER, ADC_E_PARAM_POINTER);

                RetStatus = E_NOT_OK;
            }
#if (ADC_DMA_MODE_ENABLE == STD_ON)
            else
            {
                HwUnitIndex = Adc_ConfigPtr->HwUnitToCorePtr[PhyHwUnitId].CoreHwUnitIdx;
                if (ADC_RESULT_HANDLING_DMA_MODE == Adc_ConfigPtr->CoreConfigPtr[CoreId]->
                                                        HwUnitConfigPtr[HwUnitIndex].RsltHldMthd)
                {
                    /* This group of HW unit is in DMA mode */
                    Adc_ReportError(ADC_SID_SETUP_RESULT_BUFFER, ADC_E_DMA_CHANNEL_ENABLED);
                    RetStatus = E_NOT_OK;
                }
            }
#endif /* \(ADC_DMA_MODE_ENABLE == STD_ON) */
        }

        if (E_OK == RetStatus)
#endif /* \(ADC_DEV_ERROR_DETECT== STD_ON)*/
        {
            /* Get global data pointer of current ADC*/
            DataPtr = ADC_GET_DATAADDRESS(CoreId, PhyHwUnitId);
            /* #Violation: Adc_c_REF_7 */
            if (ADC_IDLE == ADC_GET_GROUPSTATUS(DataPtr->GroupStatus, GroupId))
            {
                /* SWS_Adc_00420: initialize the result buffer pointer of the selected group
                * with the address value passed as parameter */
                DataPtr->GroupResultBufferPtr[GroupId] = DataBufferPtr;
                /* Initialize the number of conversion result set available to 0 */
                DataPtr->NumValidConResPtr[GroupId] = 0U;

                RetStatus = E_OK;
            }
            else
            {
                RetStatus = E_NOT_OK;
                /* SWS_Adc_00433: Check for ADC_E_BUSY
                    If called while group is not in state ADC_IDLE, function 
                    Adc_SetupResultBuffer shall report a runtime error ADC_E_BUSY.
                */
               Adc_ReportRuntimeError(ADC_SID_SETUP_RESULT_BUFFER, ADC_E_BUSY);
            }
        }
    }

    return RetStatus;
}
#endif /* \((ADC_INTERRUPT_MODE_ENABLE == STD_ON) || (ADC_POLLING_MODE_ENABLE== STD_ON)) */

/* SWS_Adc_00259: shall be pre-compile time configurable On/Off */
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Adc_StartGroupConversion
*
*   Service ID              : 0x02
*
*   Description             : Starts the conversion of all channels of the requested ADC Channel
*                             group.
*
*   Parameters in           : Group: Numeric ID of requested ADC Channel group.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Reentrant for different group, Non-reentrant for same group.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Adc_00367, SWS_Adc_00156, SWS_Adc_00356,
*                             SWS_Adc_00413
****************************************************************************************************/
/* #Violation: Adc_c_REF_13 */
FUNC(void, ADC_PUBLIC_CODE) Adc_StartGroupConversion
(
    Adc_GroupType Group
)
{
    const Adc_KernelConfigType *AdcKernelPtr;
    Adc_GroupType              GroupId;
    Adc_HwUnitType             PhyHwUnitId;
    Mcal_CoreType              CoreId;
    uint8                      HwUnitCoreIdx;
#if ((ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_HW_SW) && (ADC_ENABLE_QUEUING == STD_OFF))
    Adc_GlobalDataType         *DataPtr;
    const Adc_GroupCfgType     *GrpPtr;
    uint32                     GrpRequestSource;
#endif /* \(ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_HW_SW) && (ADC_ENABLE_QUEUING  \== STD_OFF) */
    uint32                     Err;
    boolean                    OperationRslt;

    OperationRslt = TRUE;
    /* Get PhyHwUnitId number from Group ID */
    /* #Violation: Adc_c_REF_5 */
    PhyHwUnitId = (Adc_HwUnitType)ADC_GET_HWUNITID(Group);
    
    /* Get the Group Id for particular PhyHwUnitId */
    /* #Violation: Adc_c_REF_5 */
    GroupId = (Adc_GroupType)ADC_GET_GROUPID(Group);
    
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    Err = Adc_CheckInit(ADC_SID_START_GROUP_CONVERSION);
    if (E_OK == Err)
#endif /* \ADC_DEV_ERROR_DETECT == STD_ON) */
    {
#if (ADC_DEV_ERROR_DETECT == STD_ON)
        /* SWS_Adc_00125: Check for DET error ADC_E_UNINIT */
        Err = Adc_CheckMulticoreAllocateError(ADC_SID_START_GROUP_CONVERSION, PhyHwUnitId);
        if (E_OK == Err)
        {
            /* SWS_Adc_00146: environment shall only call this function for groups configured
             * with software trigger source */
            /* SWS_Adc_00133:DET check */
            /* Check for ADC_E_PARAM_GROUP
               Check for ADC_E_WRONG_TRIGG_SRC
               Check for ADC_E_BUFFER_UNINIT
            */
            Err = Adc_CommDetCheck(ADC_SID_START_GROUP_CONVERSION, GroupId, PhyHwUnitId);
        }

        if (E_OK == Err)
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
        {
            /* Enter Critical Section */
            ADC_ENTER_CRITICAL_SECTION(StartGroup);
            /* SWS_Adc_00346, SWS_Adc_00426, SWS_Adc_00348, SWS_Adc_00427 */
            /* SWS_Adc_00428, SWS_Adc_00351, SWS_Adc_00294, SWS_Adc_00424 */
            /* SWS_Adc_00335 */
            /* SWS_Adc_00338 */
            /* SWS_Adc_00280 */
            Err = Adc_CheckStateForStartGroup(GroupId, PhyHwUnitId);
            /* Exit Critical Section */
            ADC_EXIT_CRITICAL_SECTION(StartGroup);

            if (E_OK == Err)
            {
                /* Get core id which core is currently executing */
                /* #Violation: Adc_c_REF_5 */
                CoreId = Mcal_GetCoreId();

                /* Find the sub-index according to the Adc number */
                HwUnitCoreIdx = Adc_ConfigPtr->HwUnitToCorePtr[PhyHwUnitId].CoreHwUnitIdx;
                /* Find the configuration information of current ADC */
                AdcKernelPtr =
                        &(Adc_ConfigPtr->CoreConfigPtr[CoreId]->HwUnitConfigPtr[HwUnitCoreIdx]);

#if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
                /* Call the Priority Scheduler */
                OperationRslt &= Adc_SchedulerOnStart(PhyHwUnitId, GroupId, AdcKernelPtr);
#elif (ADC_ENABLE_QUEUING == STD_ON) /* Queue Enable is STD_ON only during No priority */
                /* Call the Push on Queue function which handles the start of the Group
                * through Queue */
                OperationRslt &= Adc_PushOnQueue(PhyHwUnitId, GroupId, AdcKernelPtr);
#else /* \Queue mechanism disabled in No priority or HW priority */
                /* Get the ADC Group Configuration Pointer */
                GrpPtr = &(AdcKernelPtr->GrpCfgPtr[GroupId]);

                /* Get the configured Group request source */
                GrpRequestSource = (uint32)(GrpPtr->GrpRequestSrc);

                /* Get global data pointer of current ADC */
                DataPtr = ADC_GET_DATAADDRESS(CoreId, PhyHwUnitId);

                /* Enter Critical Section */
                ADC_ENTER_CRITICAL_SECTION(StartGroup);

                /* Group status of given group is made ADC_BUSY */
                /* #Violation: Adc_c_REF_10 */
                ADC_SET_GROUPSTATUS(DataPtr->GroupStatus, GroupId);

                /* GrpId is updated with the requested Group */
                DataPtr->TriggSrcData[GrpRequestSource].GrpId = GroupId;

                /* Clear ADC Group Result Status */
                /* #Violation: Adc_c_REF_10 */
                ADC_CLR_RESULTSTATUS(DataPtr->GroupResultStatus, GroupId);

                /* Reset the End result status to 0 */
                /* #Violation: Adc_c_REF_10 */
                ADC_CLR_RESBUFENDSTATUS(DataPtr->GrpBufferEndResultStatus, GroupId);

                /* Initialize the number of conversion result set available to 0 */
                DataPtr->NumValidConResPtr[GroupId] = 0U;

                /* Permit ISR calling */
                DataPtr->TriggSrcData[GrpRequestSource].IsrServReqFlg = ADC_ISR_REQ_SEV;

                /* Trigger Conversion Source: Trigger the appropriate Conversion Request
                * Source */
                OperationRslt &= Adc_StartConversion(PhyHwUnitId, AdcKernelPtr, GrpPtr, 
                                                                                ADC_TRIGG_SRC_SW);

                /* Exit Critical Section */
                ADC_EXIT_CRITICAL_SECTION(StartGroup);
#endif /* \No Priority No Queue / HW Priority */
#if (ADC_SAFETY_ENABLE == STD_ON)
                if (OperationRslt == FALSE)
                {
                    Adc_ReportRuntimeError(ADC_SID_START_GROUP_CONVERSION, ADC_E_REG_CHECK_FAIL);
                }
#else /* \(ADC_SAFETY_ENABLE == STD_ON) */
                /* #Violation: Adc_c_REF_5 */
                MCAL_UNUSED_VAR(OperationRslt);
#endif /* \(ADC_SAFETY_ENABLE == STD_ON) */
            }
            else
            {
                /* Report DET error when the HW queue is in busy */
                Adc_ReportRuntimeError(ADC_SID_START_GROUP_CONVERSION, ADC_E_BUSY);
            }
        }
    }
}
#endif /* \(ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */

/* SWS_Adc_00260:  shall be pre compile time configurable On/Off */
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Adc_StopGroupConversion
*
*   Service ID              : 0x03
*
*   Description             : Stops the conversion of the requested ADC Channel group.
*
*   Parameters in           : Group: Numeric ID of requested ADC Channel group.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant for different group, Non-reentrant for same group.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Adc_00368, SWS_Adc_00356, SWS_Adc_00413
****************************************************************************************************/
/* #Violation: Adc_c_REF_13 */
FUNC(void, ADC_PUBLIC_CODE) Adc_StopGroupConversion
(
    Adc_GroupType Group
)
{
    Adc_GlobalDataType         *DataPtr;
#if ((ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_HW_SW) && (ADC_ENABLE_QUEUING == STD_OFF))
    const Adc_GroupCfgType     *GrpPtr;
#endif /* \(ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_HW_SW) && (ADC_ENABLE_QUEUING != STD_ON) */
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType             Err;
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
    Adc_GroupType              GroupId;
    Adc_HwUnitType             PhyHwUnitId;
#if ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON))
    const Adc_KernelConfigType *AdcKernelPtr;
#endif /* \(ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON) */
    Mcal_CoreType              CoreId;
    uint8                      HwUnitCoreIdx;
    boolean                    OperationRslt;

    OperationRslt = TRUE;
    /* #Violation: Adc_c_REF_5 */
    PhyHwUnitId = (Adc_HwUnitType)ADC_GET_HWUNITID(Group);
    
    /* Get the Group Id for particular PhyHwUnitId */
    /* #Violation: Adc_c_REF_5 */
    GroupId = (Adc_GroupType)ADC_GET_GROUPID(Group);

#if (ADC_DEV_ERROR_DETECT == STD_ON)
    /* The Adc_DetErrorCheck function covers the following SWS. */
    /* SWS_Adc_00295: called prior to initializing the module */
    /* SWS_Adc_00126: Group ID is non-existing */
    /* SWS_Adc_00126: Group ID is non-existing */
    /* SWS_Adc_00164: Group has a trigger source configured as hardware */
    /* Check for ADC_E_PARAM_GROUP, Check for ADC_E_WRONG_TRIGG_SRC. */
    Err = Adc_DetErrorCheck(ADC_SID_STOP_GROUP_CONVERSION, GroupId, PhyHwUnitId);
    if (E_OK == Err)
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Get core id which core is currently executing */
        /* #Violation: Adc_c_REF_5 */
        CoreId = Mcal_GetCoreId();

        /* Get global data pointer of current ADC*/
        DataPtr = ADC_GET_DATAADDRESS(CoreId, PhyHwUnitId);

        /* Enter Critical section */
        ADC_ENTER_CRITICAL_SECTION(StopGroup);

        /* If Group status and Group result status are Idle */
        /* #Violation: Adc_c_REF_7 */
        if ((ADC_IDLE != ADC_GET_GROUPSTATUS(DataPtr->GroupStatus, GroupId)) ||
            /* #Violation: Adc_c_REF_7 */
            (ADC_IDLE != ADC_GET_RESULTSTATUS(DataPtr->GroupResultStatus, GroupId)))
        {
            /* Exit Critical section */
            ADC_EXIT_CRITICAL_SECTION(StopGroup);

            /* Find the sub-index according to the Adc number */
            HwUnitCoreIdx = Adc_ConfigPtr->HwUnitToCorePtr[PhyHwUnitId].CoreHwUnitIdx;

            /* Full priority considered */
#if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
            /* Get PhyHwUnitId configuration Pointer */
            /* Find the configuration information of current ADC */
            AdcKernelPtr =
                    &(Adc_ConfigPtr->CoreConfigPtr[CoreId]->HwUnitConfigPtr[HwUnitCoreIdx]);
            /* Call scheduler */
            OperationRslt = Adc_SchedulerOnStop(PhyHwUnitId, GroupId, AdcKernelPtr);
            /* Queue Enable is STD_ON only during No priority */
#elif (ADC_ENABLE_QUEUING == STD_ON)
            /* SWS_Adc_00437, SWS_Adc_00438: Remove a start/restart request from the queue */
            /* Get PhyHwUnitId configuration Pointer */
            /* Find the configuration information of current ADC */
            AdcKernelPtr =
                    &(Adc_ConfigPtr->CoreConfigPtr[CoreId]->HwUnitConfigPtr[HwUnitCoreIdx]);
            /* Call the Pop From Queue function which handles the stop
            * request of the Group */
            OperationRslt = Adc_PopFromQueue(PhyHwUnitId, GroupId, AdcKernelPtr);
#else /* \If Queue mechanism not enabled in No priority / HW priority */
            /* Get the Adc Group Configuration Pointer */
            /* Find the configuration information of current ADC */
            GrpPtr = &(Adc_ConfigPtr->CoreConfigPtr[CoreId]->
                HwUnitConfigPtr[HwUnitCoreIdx].GrpCfgPtr[GroupId]);

            /* Enter Critical section */
            ADC_ENTER_CRITICAL_SECTION(StopGroup);

            /* check and handle to stop group */
            /* #Violation: Adc_c_REF_7 */
            if (ADC_IDLE != ADC_GET_GROUPSTATUS(DataPtr->GroupStatus, GroupId))
            {
                /* SWS_Adc_00385: Stop an ongoing conversion when one-shot and
                * software-trigger mode */
                /* SWS_Adc_00386: Stop an ongoing conversion when continuous-conversion and
                * software-trigger mode
                * */
                DataPtr->TriggSrcData[GrpPtr->GrpRequestSrc].IsrServReqFlg = ADC_NO_SERVICE;

                /* Stop the Conversion Request Source */
                OperationRslt = Adc_StopConvRequestSource(GrpPtr, PhyHwUnitId);

                /* Update request source data and Adc_AllRunningCh */
                Adc_ResetTrigSrcData(GrpPtr, DataPtr);

                /* SWS_Adc_00360: Set the group status to state ADC_IDLE */
                /* Group status of given group is made ADC_IDLE */
                /* #Violation: Adc_c_REF_10 */
                ADC_CLR_GROUPSTATUS(DataPtr->GroupStatus, GroupId);
            }

            /* Clear ADC Group Result Status */
            /* #Violation: Adc_c_REF_10 */
            ADC_CLR_RESULTSTATUS(DataPtr->GroupResultStatus, GroupId);

            /* Reset the End result status to 0 */
            /* #Violation: Adc_c_REF_10 */
            ADC_CLR_RESBUFENDSTATUS(DataPtr->GrpBufferEndResultStatus, GroupId);

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
            /* SWS_Adc_00155: Disable the group notification for the requested group */
            /* #Violation: Adc_c_REF_10 */
            ADC_DISABLE_NOTIF(DataPtr->GrpNotifStatus, GroupId);
#endif /* \(ADC_GRP_NOTIF_CAPABILITY == STD_ON) */

            /* Exit Critical section */
            ADC_EXIT_CRITICAL_SECTION(StopGroup);
#endif /* \No Priority No Queue / HW Priority */

#if (ADC_SAFETY_ENABLE == STD_ON)
            if (OperationRslt == FALSE)
            {
                Adc_ReportRuntimeError(ADC_SID_STOP_GROUP_CONVERSION, ADC_E_REG_CHECK_FAIL);
            }
#else /* \(ADC_SAFETY_ENABLE == STD_ON) */
                /* #Violation: Adc_c_REF_5 */
                MCAL_UNUSED_VAR(OperationRslt);
#endif /* \(ADC_SAFETY_ENABLE == STD_ON)*/
        }
        else
        {
            /* Exit Critical section */
            ADC_EXIT_CRITICAL_SECTION(StopGroup);

            /* Report DET error when group is in idle and no any result*/
            Adc_ReportRuntimeError(ADC_SID_STOP_GROUP_CONVERSION, ADC_E_IDLE);
        }
    }
}
#endif /* \(ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */

/* SWS_Adc_00359: shall be pre-compile configurable On/Off */
#if (ADC_READ_GROUP_API == STD_ON)
#if ((ADC_INTERRUPT_MODE_ENABLE == STD_ON) || (ADC_POLLING_MODE_ENABLE == STD_ON))
/****************************************************************************************************
*   Function Name           : Adc_ReadGroup
*
*   Service ID              : 0x04
*
*   Description             : Reads the group conversion result of the last completed conversion
*                             round of the requested group and stores the channel values starting
*                             at the DataBufferPtr address. The group channel values are stored in
*                             ascending channel number order(in contrast to the storage layout of
*                             the result buffer if streaming access is configured).
*
*   Parameters in           : Group: Numeric ID of requested ADC channel group.
*
*   Parameters inout        : None.
*
*   Parameters out          : DataBufferPtr: ADC results of all channels of the selected group are
*                             stored in the data buffer addressed with the pointer.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK: results are available and written to the data buffer
*                             E_NOT_OK: no results are available or development error occurred
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Adc_00369, SWS_Adc_00357,
*                             SWS_Adc_00383, SWS_Adc_00413, SWS_Adc_00503
****************************************************************************************************/
/* #Violation: Adc_c_REF_13 */
FUNC(Std_ReturnType, ADC_PUBLIC_CODE) Adc_ReadGroup
(
    Adc_GroupType Group,
    /* #Violation: Adc_c_REF_8 */
    /* #Violation: Adc_c_REF_9 */
    P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) DataBufferPtr
)
{
    uint8                     NoOfChannels;
    Adc_GroupType             GroupId;
    Std_ReturnType            RetStatus;
    Adc_StreamNumSampleType   NoOfValidConv;
    Adc_StreamNumSampleType   StreamNumOfSamples;
    Adc_StatusType            GrpStatus;
    Adc_StatusType            GrpRes;
    Adc_HwUnitType            PhyHwUnitId;
    Mcal_CoreType             CoreId;
    uint8                     HwUnitCoreIdx;
#if (ADC_HW_SYNC_CONV_GROUP_EN == STD_ON)
    uint8                      HwUnitCnt;
    uint16                     SyncGrpSlaveRsltStartPos;
    const Adc_KernelConfigType *AdcKernelPtr;
#endif /* \(ADC_HW_SYNC_CONV_GROUP_EN == STD_ON) */
    Adc_GlobalDataType        *DataPtr;
    const Adc_GroupCfgType    *GrpPtr;
    const Adc_ValueGroupType  *CurrentResBufPtr;
    Adc_ValueGroupType        *TargetDataBufPtr;

    /* Get PhyHwUnitId number from Group ID */
    /* #Violation: Adc_c_REF_5 */
    PhyHwUnitId = (Adc_HwUnitType)ADC_GET_HWUNITID(Group);

    /* Get the Group Id for particular PhyHwUnitId */
    /* #Violation: Adc_c_REF_5 */
    GroupId = (Adc_GroupType)ADC_GET_GROUPID(Group);

    /* Get core id which core is currently executing */
    /* #Violation: Adc_c_REF_5 */
    CoreId = Mcal_GetCoreId();

#if (ADC_DEV_ERROR_DETECT == STD_ON)
    RetStatus = Adc_ReadGroupDetCheck(GroupId, PhyHwUnitId, DataBufferPtr);
    if (E_OK == RetStatus)
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Enter Critical Section */
        ADC_ENTER_CRITICAL_SECTION(ReadGroup);
        /* SWS_Adc_00388: called while the group status is ADC_IDLE and the group conversion was
         * not started (no results are available from previous conversions) */
        RetStatus = Adc_CheckDriverState(GroupId, PhyHwUnitId);
        /* Exit Critical Section */
        ADC_EXIT_CRITICAL_SECTION(ReadGroup);

        if (E_OK == RetStatus)
        {
            /* Find the sub-index according to the Adc number */
            HwUnitCoreIdx = Adc_ConfigPtr->HwUnitToCorePtr[PhyHwUnitId].CoreHwUnitIdx;
            /* Find the configuration information of current ADC */
            GrpPtr = &(Adc_ConfigPtr->CoreConfigPtr[CoreId]->
                            HwUnitConfigPtr[HwUnitCoreIdx].GrpCfgPtr[GroupId]);
            /* Get global data pointer of current ADC*/
            DataPtr = ADC_GET_DATAADDRESS(CoreId, PhyHwUnitId);

            /* Enter Critical Section */
            ADC_ENTER_CRITICAL_SECTION(ReadGroup);

            /* Note: Read of Number of valid conversion result, buffer end status,
             * Group status update are protected from ISR */
            /* #Violation: Adc_c_REF_7 */
            GrpStatus = ADC_GET_GROUPSTATUS(DataPtr->GroupStatus, GroupId);
            /* #Violation: Adc_c_REF_7 */
            GrpRes = ADC_GET_RESULTSTATUS(DataPtr->GroupResultStatus, GroupId);

            /* If Group is in ADC_BUSY state (no matter of result availability),
             * then return E_NOT_OK without any action */
            if ((GrpStatus != ADC_IDLE) && (ADC_IDLE == GrpRes))
            {
                /* Exit Critical section */
                ADC_EXIT_CRITICAL_SECTION(ReadGroup);
                /* Group status is ADC_BUSY, return E_NOT_OK without any action */
                RetStatus = E_NOT_OK;
            }
            else
            {
                /* SWS_Adc_00329, SWS_Adc_00331: Not clear group status */
                /* Clear ADC Group Result Status on read */
                /* #Violation: Adc_c_REF_10 */
                ADC_CLR_RESULTSTATUS(DataPtr->GroupResultStatus, GroupId);

                /* Clear the Buffer end status */
                /* #Violation: Adc_c_REF_10 */
                ADC_CLR_RESBUFENDSTATUS(DataPtr->GrpBufferEndResultStatus, GroupId);

                /* SWS_Adc_00075 */
                /* Read the number of valid conversation results available */
                NoOfValidConv = DataPtr->NumValidConResPtr[GroupId];
                /* Latest valid data location in result buffer */
                CurrentResBufPtr = &(DataPtr->GroupResultBufferPtr[GroupId])[NoOfValidConv - 1U];

                /* Get the configured number of samples for the Group */
                StreamNumOfSamples = GrpPtr->NumSamples;
                /* Get the configured number of channels in a group */
                NoOfChannels = (uint8)(GrpPtr->GroupDefinitionPtr)[0];

#if (ADC_HW_SYNC_CONV_GROUP_EN == STD_ON)
                /* Starting index of slave hardware unit in sync group */
                SyncGrpSlaveRsltStartPos = (uint16)NoOfChannels * (uint16)StreamNumOfSamples;
#endif /* \(ADC_HW_SYNC_CONV_GROUP_EN == STD_ON) */

                /* Total number of channels in a Group will be at least one */
                TargetDataBufPtr = DataBufferPtr;
                while (NoOfChannels > 0U)
                {
                    /* SWS_Adc_00113: Shall read the raw converted values without further
                     * scaling */
                    /* Store the channel conversion result into the requested buffer */
                    /* Increment the TargetDataBufPtr to point to the next location */
                    *TargetDataBufPtr = *CurrentResBufPtr;

#if (ADC_HW_SYNC_CONV_GROUP_EN == STD_ON)
                    /* Get the HW unit configuration information */
                    AdcKernelPtr =
                            &Adc_ConfigPtr->CoreConfigPtr[CoreId]->HwUnitConfigPtr[PhyHwUnitId];
                    if ((AdcKernelPtr->SyncGrpSlaveHwPtr != NULL_PTR) &&
                            (TRUE == GrpPtr->IsSyncChExists))
                    {
                        /* Sync group is enabled and this is the master in sync group */
                        for (HwUnitCnt = 1U; HwUnitCnt <= AdcKernelPtr->SyncGrpSlaveHwPtr[0];
                                HwUnitCnt++)
                        {
                            /* Copy the slave conversion results to user buffer */
                            TargetDataBufPtr[(GrpPtr->GroupDefinitionPtr)[0] * HwUnitCnt] =
                                         CurrentResBufPtr[SyncGrpSlaveRsltStartPos * HwUnitCnt];
                        }
                    }
#endif /* \(ADC_HW_SYNC_CONV_GROUP_EN == STD_ON) */

                    TargetDataBufPtr++;
                    /* Get the latest result location of the next channel in the group */
                    CurrentResBufPtr = &CurrentResBufPtr[(uint32)StreamNumOfSamples];
                    /* Decrement the loop count */
                    NoOfChannels--;
                }
                /* Exit Critical section */
                ADC_EXIT_CRITICAL_SECTION(ReadGroup);
                /* Set the return status to E_OK */
                RetStatus = E_OK;
            }
        }
        else
        {
            /* Service is while the group is in Idle state */
            Adc_ReportRuntimeError(ADC_SID_READ_GROUP, ADC_E_IDLE);
        }
    }

    return RetStatus;
}
#endif /* \((ADC_INTERRUPT_MODE_ENABLE == STD_ON) || (ADC_POLLING_MODE_ENABLE== STD_ON)) */
#endif /* \(ADC_READ_GROUP_API == STD_ON) */

/* SWS_Adc_00265:shall be pre-compile time configurable On/Off */
#if (ADC_HW_TRIGGER_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Adc_EnableHardwareTrigger
*
*   Service ID              : 0x05
*
*   Description             : Enables the hardware trigger for the requested ADC Channel group.
*
*   Parameters in           : Group: Numeric ID of requested ADC Channel group.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Reentrant for different group, Non-reentrant for same group.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Adc_91001, SWS_Adc_00413
****************************************************************************************************/
/* #Violation: Adc_c_REF_13 */
FUNC(void, ADC_PUBLIC_CODE) Adc_EnableHardwareTrigger
(
    Adc_GroupType Group
)
{
    Adc_GlobalDataType         *DataPtr;
    const Adc_GroupCfgType     *GrpPtr;
    Adc_GroupType              GroupId;
    uint8                      GrpRequestSource;
    Adc_HwUnitType             PhyHwUnitId;
    const Adc_KernelConfigType *AdcKernelPtr;
    Mcal_CoreType              CoreId;
    uint8                      HwUnitCoreIdx;
    uint32                     Err;
    boolean                    OperationRslt;

    /* Get PhyHwUnitId number from Group ID */
    /* #Violation: Adc_c_REF_5 */
    PhyHwUnitId = (Adc_HwUnitType)ADC_GET_HWUNITID(Group);
    
    /* Get the Group Id for particular PhyHwUnitId */
    /* #Violation: Adc_c_REF_5 */
    GroupId = (Adc_GroupType)ADC_GET_GROUPID(Group);

#if (ADC_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Adc_0029: Check for DET error ADC_E_UNINIT */
    Err = Adc_CheckInit(ADC_SID_ENABLE_HARDWARE_TRIGGER);
    if (E_OK == (Std_ReturnType)Err)
#endif /* \ADC_DEV_ERROR_DETECT == STD_ON) */
    {
#if (ADC_DEV_ERROR_DETECT == STD_ON)
        /* SWS_Adc_00128: channel group ID is invalid */
        Err = Adc_CheckMulticoreAllocateError(ADC_SID_ENABLE_HARDWARE_TRIGGER, PhyHwUnitId);
        if (E_OK == Err)
        {
            /* SWS_Adc_00128: Channel group ID is invalid, for ADC_E_PARAM_GROUP */
            /* SWS_Adc_00120, SWS_Adc_00136: Group is configured for software API trigger mode,
             * for ADC_E_WRONG_TRIGG_SRC */
            /* SWS_Adc_00281: A HW group is erroneously configured for continuous conversion mode,
             * for ADC_E_WRONG_CONV_MODE */
            /* SWS_Adc_00425: when called prior to initializing the result buffer pointer,
             * for ADC_E_BUFFER_UNINIT */
            Err = Adc_CommDetCheck(ADC_SID_ENABLE_HARDWARE_TRIGGER, GroupId, PhyHwUnitId);
        }

        if (E_OK == Err)
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
        {
            /* Enter Critical Section */
            ADC_ENTER_CRITICAL_SECTION(EnableHwTrig);
            /* SWS_Adc_00321, SWS_Adc_00349, SWS_Adc_00353 */
            /* SWS_Adc_00335 */
            /* SWS_Adc_00338 */
            /* SWS_Adc_00280 */
            /* Check for ADC_E_BUSY */
            Err = Adc_CheckStateForEnableGroup(GroupId, PhyHwUnitId);
            /* Exit Critical Section */
            ADC_EXIT_CRITICAL_SECTION(EnableHwTrig);

            if (E_OK == Err)
            {
                /* Get core id which core is currently executing */
                /* #Violation: Adc_c_REF_5 */
                CoreId = Mcal_GetCoreId();

                /* Get PhyHwUnitId configuration Pointer */
                /* Find the sub-index according to the Adc number */
                HwUnitCoreIdx = Adc_ConfigPtr->HwUnitToCorePtr[PhyHwUnitId].CoreHwUnitIdx;
                /* Find the configuration information of current ADC */
                AdcKernelPtr =
                        &(Adc_ConfigPtr->CoreConfigPtr[CoreId]->HwUnitConfigPtr[HwUnitCoreIdx]);

                /* Get the ADC Group Configuration Pointer */
                GrpPtr = &(Adc_ConfigPtr->CoreConfigPtr[CoreId]->HwUnitConfigPtr[HwUnitCoreIdx]
                                                                                .GrpCfgPtr[GroupId]);
                /* Get global data pointer of current ADC*/
                DataPtr = ADC_GET_DATAADDRESS(CoreId, PhyHwUnitId);

                /* Update all Status Variables */
                /* Enter Critical Section */
                ADC_ENTER_CRITICAL_SECTION(EnableHwTrig);

                /* Queue Enable is STD_ON only during No priority */
#if (ADC_ENABLE_QUEUING == STD_ON)
                /* Initialize the Pop Index and Push Index to the Requested Group */
                DataPtr->PushGroupId = GroupId;
                DataPtr->PopGroupId = GroupId;
#endif /* \(ADC_ENABLE_QUEUING == STD_ON) */

                /* Group status of given group is made ADC_BUSY */
                /* #Violation: Adc_c_REF_10 */
                ADC_SET_GROUPSTATUS(DataPtr->GroupStatus, GroupId);

                /* Clear ADC Group Result Status */
                /* #Violation: Adc_c_REF_10 */
                ADC_CLR_RESULTSTATUS(DataPtr->GroupResultStatus, GroupId);

                /* Reset the End result status to 0 */
                /* #Violation: Adc_c_REF_10 */
                ADC_CLR_RESBUFENDSTATUS(DataPtr->GrpBufferEndResultStatus, GroupId);

                /* Initialize the number of conversion result set available to 0 */
                DataPtr->NumValidConResPtr[GroupId] = (Adc_StreamNumSampleType)0;

                /* Get the configured Group request source */
                GrpRequestSource = (uint8)GrpPtr->GrpRequestSrc;
                /* GrpId is updated with the requested Group */
                DataPtr->TriggSrcData[GrpRequestSource].GrpId = GroupId;

                /* permit ISR calling */
                DataPtr->TriggSrcData[GrpRequestSource].IsrServReqFlg = ADC_ISR_REQ_SEV;

                /* SWS_Adc_00432: reset the internal group result buffer pointer */
                /* configure trigger and the queue data for HW-trigger group */
                OperationRslt =
                        Adc_StartConversion(PhyHwUnitId, AdcKernelPtr, GrpPtr, ADC_TRIGG_SRC_HW);

                /* Exit Critical Section */
                ADC_EXIT_CRITICAL_SECTION(EnableHwTrig);

#if (ADC_SAFETY_ENABLE == STD_ON)
                if (OperationRslt == FALSE)
                {
                    Adc_ReportRuntimeError(ADC_SID_ENABLE_HARDWARE_TRIGGER, ADC_E_REG_CHECK_FAIL);
                }
#else /* \(ADC_SAFETY_ENABLE == STD_ON) */
                /* #Violation: Adc_c_REF_5 */
                MCAL_UNUSED_VAR(OperationRslt);
#endif /* \(ADC_SAFETY_ENABLE == STD_ON) */
            }
            else
            {
                /* Report DET error when the queue is busy */
                Adc_ReportRuntimeError(ADC_SID_ENABLE_HARDWARE_TRIGGER, ADC_E_BUSY);
            }
        }
    }
}
#endif /* \(ADC_HW_TRIGGER_API == STD_ON) */

/* SWS_Adc_00266: shall be pre-compile time configurable On/Off */
#if (ADC_HW_TRIGGER_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Adc_DisableHardwareTrigger
*
*   Service ID              : 0x06
*
*   Description             : Disables the hardware trigger for the requested ADC Channel group.
*
*   Parameters in           : Group: Numeric ID of requested ADC Channel group.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Reentrant for different group, Non-reentrant for same group.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Adc_91002, SWS_Adc_00413
****************************************************************************************************/
/* #Violation: Adc_c_REF_13 */
FUNC(void, ADC_PUBLIC_CODE) Adc_DisableHardwareTrigger
(
    Adc_GroupType Group
)
{
    Adc_GlobalDataType         *DataPtr;
    Adc_GroupType              GroupId;
    Adc_HwUnitType             PhyHwUnitId;
    Mcal_CoreType              CoreId;
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    uint32                     Err;
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
    boolean                    OperationRslt;

    /* #Violation: Adc_c_REF_5 */
    PhyHwUnitId = (Adc_HwUnitType)ADC_GET_HWUNITID(Group);

    /* Get the Group Id for particular PhyHwUnitId */
    /* #Violation: Adc_c_REF_5 */
    GroupId = (Adc_GroupType)ADC_GET_GROUPID(Group);

#if (ADC_DEV_ERROR_DETECT == STD_ON)
    /* The Adc_DetErrorCheck function covers the following SWS */
    /* SWS_Adc_00298: called prior to initializing the ADC module */
    /* SWS_Adc_00129: channel group ID is non-existing */
    /* SWS_Adc_00129: channel group ID is non-existing */
    /* SWS_Adc_00121, SWS_Adc_00137: group is configured for software API trigger mode,
     * for ADC_E_WRONG_TRIGG_SRC */
    /* SWS_Adc_00282: a HW group is erroneously configured for continuous conversion mode,
     * for ADC_E_WRONG_CONV_MODE */
    Err = Adc_DetErrorCheck(ADC_SID_DISABLE_HARDWARE_TRIGGER, GroupId, PhyHwUnitId);
    if (E_OK == Err)
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Get core id which core is currently executing */
        /* #Violation: Adc_c_REF_5 */
        CoreId = Mcal_GetCoreId();

        /* Get global data pointer of current ADC*/
        DataPtr = ADC_GET_DATAADDRESS(CoreId, PhyHwUnitId);

        /* Enter Critical section */
        ADC_ENTER_CRITICAL_SECTION(DisableHwTrig);

        /* If Group status and Group result status are Idle */
        /* #Violation: Adc_c_REF_7 */
        if ((ADC_IDLE != ADC_GET_GROUPSTATUS(DataPtr->GroupStatus, GroupId)) ||
            /* #Violation: Adc_c_REF_7 */
            (ADC_IDLE != ADC_GET_RESULTSTATUS(DataPtr->GroupResultStatus, GroupId)))
        {
            /* Exit Critical section */
            ADC_EXIT_CRITICAL_SECTION(DisableHwTrig);

            /* Call the local function to Disables the hardware trigger 
             * for the requested ADC Channel group. */
            OperationRslt = Adc_LocalDisableHardwareTrigger(GroupId, PhyHwUnitId, DataPtr, CoreId);

#if (ADC_SAFETY_ENABLE == STD_ON)
            if (OperationRslt == FALSE)
            {
                Adc_ReportRuntimeError(ADC_SID_DISABLE_HARDWARE_TRIGGER, ADC_E_REG_CHECK_FAIL);
            }
#else /* \(ADC_SAFETY_ENABLE == STD_ON) */
            /* #Violation: Adc_c_REF_5 */
            MCAL_UNUSED_VAR(OperationRslt);
#endif /* \(ADC_SAFETY_ENABLE == STD_ON) */
        }
        else
        {
            /* Exit Critical section */
            ADC_EXIT_CRITICAL_SECTION(DisableHwTrig);

            /* Report DET error when group is in idle and no any result*/
            Adc_ReportRuntimeError(ADC_SID_DISABLE_HARDWARE_TRIGGER, ADC_E_IDLE);
        }
    }
}
#endif /* \(ADC_HW_TRIGGER_API == STD_ON) */

/* SWS_Adc_00100: shall be pre-compile time configurable On/Off */
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
/****************************************************************************************************
*   Function Name           : Adc_EnableGroupNotification
*
*   Service ID              : 0x07
*
*   Description             : Enables the notification mechanism for the requested ADC Channel group.
*
*   Parameters in           : Group: Numeric ID of requested ADC Channel group.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Reentrant for different group, Non-reentrant for same group.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Adc_91003, SWS_Adc_00413
****************************************************************************************************/
/* #Violation: Adc_c_REF_13 */
FUNC(void, ADC_PUBLIC_CODE) Adc_EnableGroupNotification
(
    Adc_GroupType Group
)
{
    Adc_GlobalDataType   *DataPtr;
    Adc_GroupType        GroupId;
    Adc_HwUnitType       HwUnitId;
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    uint32               Err;
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
    Mcal_CoreType        CoreId;

    /* Get the ADC HW Unit Id */
    /* #Violation: Adc_c_REF_5 */
    HwUnitId = (Adc_HwUnitType)ADC_GET_HWUNITID(Group);

    /* Get the Group Id for particular HwUnitId */
    /* #Violation: Adc_c_REF_5 */
    GroupId = (Adc_GroupType)ADC_GET_GROUPID(Group);

#if (ADC_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Adc_00299: called prior to initializing the ADC module */
    Err = Adc_CheckInit(ADC_SID_ENABLE_GROUP_NOTIFICATION);
    if (E_OK == (Std_ReturnType)Err)
#endif /* \ADC_DEV_ERROR_DETECT == STD_ON) */
    {
#if (ADC_DEV_ERROR_DETECT == STD_ON)
        /* SWS_Adc_00130: channel group ID is non-existing */
        Err = Adc_CheckMulticoreAllocateError(ADC_SID_ENABLE_GROUP_NOTIFICATION, HwUnitId);
        if (E_OK == Err)
        {
            /* SWS_Adc_00130: channel group ID is non-existing */
            /* SWS_Adc_00165: group notification function pointer is NULL */
            Err = Adc_CommDetCheck(ADC_SID_ENABLE_GROUP_NOTIFICATION, GroupId, HwUnitId);
        }

        if (E_OK == Err)
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
        {
            /* #Violation: Adc_c_REF_5 */
            CoreId = Mcal_GetCoreId();

            /* Get global data pointer of current HW unit*/
            DataPtr = ADC_GET_DATAADDRESS(CoreId, HwUnitId);

            /* Enter Critical section */
            ADC_ENTER_CRITICAL_SECTION(EnableGroupNotification);

            /* SWS_Adc_00057 */
            /* Enable the group notification */
            /* #Violation: Adc_c_REF_5 */
            MCAL_SETBITS(&(DataPtr->GrpNotifStatus),
                               (uint32)GroupId,
                               (uint32)1U,
                               (uint32)1U);

            /* Exit Critical section */
            ADC_EXIT_CRITICAL_SECTION(EnableGroupNotification);
        }
    }
}
#endif /* \(ADC_GRP_NOTIF_CAPABILITY == STD_ON) */

/* SWS_Adc_00101: shall be pre-compile time configurable On/Off */
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
/****************************************************************************************************
*   Function Name           : Adc_DisableGroupNotification
*
*   Service ID              : 0x08
*
*   Description             : Disables the notification mechanism for the requested ADC Channel group.
*
*   Parameters in           : Group: Numeric ID of requested ADC Channel group.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Reentrant for different group, Non-reentrant for same group.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Adc_91004, SWS_Adc_00413
****************************************************************************************************/
/* #Violation: Adc_c_REF_13 */
FUNC(void, ADC_PUBLIC_CODE) Adc_DisableGroupNotification
(
    Adc_GroupType Group
)
{
    Adc_GlobalDataType   *DataPtr;
    Adc_GroupType        GroupId;
    Adc_HwUnitType       PhyHwUnitId;
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    uint32               Err;
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
    Mcal_CoreType        CoreId;

    /* Get the ADC HW Unit Id */
    /* #Violation: Adc_c_REF_5 */
    PhyHwUnitId = (Adc_HwUnitType)ADC_GET_HWUNITID(Group);

    /* Get the Group Id for particular PhyHwUnitId */
    /* #Violation: Adc_c_REF_5 */
    GroupId = (Adc_GroupType)ADC_GET_GROUPID(Group);
    
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Adc_00300: called prior to initializing the ADC module */
    Err = Adc_CheckInit(ADC_SID_DISABLE_GROUP_NOTIFICATION);
    if (E_OK == (Std_ReturnType)Err)
#endif /* \ADC_DEV_ERROR_DETECT == STD_ON) */
    {
#if (ADC_DEV_ERROR_DETECT == STD_ON)
        /* SWS_Adc_00131: channel group ID is non-existing */
        Err = Adc_CheckMulticoreAllocateError(ADC_SID_DISABLE_GROUP_NOTIFICATION, PhyHwUnitId);
        if (E_OK == Err)
        {
            /* SWS_Adc_00131: channel group ID is non-existing */
            /* SWS_Adc_00166: group notification function pointer is NULL */
            Err = Adc_CommDetCheck(ADC_SID_DISABLE_GROUP_NOTIFICATION, GroupId, PhyHwUnitId);
        }

        if (E_OK == Err)
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
        {
            /* #Violation: Adc_c_REF_5 */
            CoreId = Mcal_GetCoreId();

            /* Get global data pointer of current Adc*/
            DataPtr = ADC_GET_DATAADDRESS(CoreId, PhyHwUnitId);

            /* Enter Critical section */
            ADC_ENTER_CRITICAL_SECTION(DisableGroupNotification);

            /* SWS_Adc_00058 */
            /* Disable the group notification */
            /* #Violation: Adc_c_REF_10 */
            ADC_DISABLE_NOTIF(DataPtr->GrpNotifStatus, GroupId);

            /* Exit Critical section */
            ADC_EXIT_CRITICAL_SECTION(DisableGroupNotification);
        }
    }
}
#endif /* \(ADC_GRP_NOTIF_CAPABILITY == STD_ON) */

/****************************************************************************************************
*   Function Name           : Adc_GetGroupStatus
*
*   Service ID              : 0x09
*
*   Description             : Returns the conversion status of the requested ADC Channel group.
*
*   Parameters in           : Group: Numeric ID of requested ADC Channel group.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : Conversion status for the requested group.
*                             ADC_IDLE
*                             ADC_BUSY
*                             ADC_COMPLETED
*                             ADC_STREAM_COMPLETED
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Adc_00374, SWS_Adc_00220, SWS_Adc_00413, SWS_Adc_00503,
*                             SWS_Adc_00436
****************************************************************************************************/
/* #Violation: Adc_c_REF_13 */
FUNC(Adc_StatusType, ADC_PUBLIC_CODE) Adc_GetGroupStatus
(
    Adc_GroupType Group
)
{
#if ((ADC_POLLING_MODE_ENABLE == STD_ON) || (ADC_DMA_MODE_ENABLE == STD_ON))
    boolean                    OperationRslt;
    boolean                    PollingFlg;
    uint8                      HwUnitCoreIdx;
    const Adc_KernelConfigType *HwUnitConfigPtr;
    Saradc_RequestSource       ReqSrc;
#endif /* \((ADC_POLLING_MODE_ENABLE == STD_ON) || (ADC_DMA_MODE_ENABLE == STD_ON)) */
    Adc_GlobalDataType         *DataPtr;
    Adc_GroupType              GroupId;
    Adc_StatusType             RetStatus;
    Adc_HwUnitType             PhyHwUnitId;
    uint32                     EndStatus;
    Adc_StatusType             GrpRes;
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    uint32                     Err;
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
    Mcal_CoreType              CoreId;

    RetStatus = ADC_IDLE;

    /* Get PhyHwUnitId number from Group ID */
    /* #Violation: Adc_c_REF_5 */
    PhyHwUnitId = (Adc_HwUnitType)ADC_GET_HWUNITID(Group);

    /* Get the Group Id for particular PhyHwUnitId */
    /* #Violation: Adc_c_REF_5 */
    GroupId = (Adc_GroupType)ADC_GET_GROUPID(Group);

#if (ADC_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Adc_00301: called prior to initializing the ADC module */
    Err = Adc_CheckInit(ADC_SID_GET_GROUP_STATUS);
    if (E_OK == Err)
#endif /* \ADC_DEV_ERROR_DETECT == STD_ON) */
    {
#if (ADC_DEV_ERROR_DETECT == STD_ON)
        /* SWS_Adc_00225: channel group ID is non-existing */
        Err = Adc_CheckMulticoreAllocateError(ADC_SID_GET_GROUP_STATUS, PhyHwUnitId);
        if (E_OK == Err)
        {
            /* Check for ADC_E_PARAM_GROUP */
            Err = Adc_CommDetCheck(ADC_SID_GET_GROUP_STATUS, GroupId, PhyHwUnitId);
        }

        if (E_OK == Err)
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
        {
            /* #Violation: Adc_c_REF_5 */
            CoreId = Mcal_GetCoreId();

            /* Get global data pointer of current ADC*/
            DataPtr = ADC_GET_DATAADDRESS(CoreId, PhyHwUnitId);

#if ((ADC_POLLING_MODE_ENABLE == STD_ON) || (ADC_DMA_MODE_ENABLE == STD_ON))
            HwUnitCoreIdx = Adc_ConfigPtr->HwUnitToCorePtr[PhyHwUnitId].CoreHwUnitIdx;
            HwUnitConfigPtr =
                    &(Adc_ConfigPtr->CoreConfigPtr[CoreId]-> HwUnitConfigPtr[HwUnitCoreIdx]);

#if (ADC_POLLING_MODE_ENABLE == STD_ON)
            if (ADC_RESULT_HANDLING_POLLING_MODE == HwUnitConfigPtr->RsltHldMthd)
            {
                /* Polling mode is enabled */
                PollingFlg = TRUE;
            }
            else
#endif /* \(ADC_POLLING_MODE_ENABLE == STD_ON) */
#if (ADC_DMA_MODE_ENABLE == STD_ON)
            if (FALSE == HwUnitConfigPtr->IsIntEn)
            {
                /* Interrupt is enabled when in DMA mode, polling for refresh the status machine */
                PollingFlg = TRUE;
            }
            else
#endif /* \(ADC_DMA_MODE_ENABLE == STD_ON) */
            {
                /* Not polling */
                PollingFlg = FALSE;
            }

            if (TRUE == PollingFlg)
            {
                /* Group working in polling mode */
                /* Get the request source */
                ReqSrc = HwUnitConfigPtr->GrpCfgPtr[GroupId].GrpRequestSrc;
                OperationRslt = Adc_IsrEventHandler(PhyHwUnitId, ReqSrc, HwUnitConfigPtr, DataPtr);

#if (ADC_SAFETY_ENABLE == STD_ON)
                if (FALSE == OperationRslt)
                {
                    Adc_ReportRuntimeError(ADC_SID_GET_GROUP_STATUS, ADC_E_REG_CHECK_FAIL);
                }
#else /* \(ADC_SAFETY_ENABLE == STD_ON) */
                /* #Violation: Adc_c_REF_5 */
                MCAL_UNUSED_VAR(OperationRslt);
#endif /* \(ADC_SAFETY_ENABLE == STD_ON) */
            }
#endif /* \(ADC_POLLING_MODE_ENABLE == STD_ON) */

            /* SWS_Adc_00226: shall provide atomic access to the status data by the use of
             * atomic instructions */
            /* Enter Critical section */
            ADC_ENTER_CRITICAL_SECTION(GetGrpStatus);

            /* Return status of the group */
            /* Check if the result buffer is full */
            /* #Violation: Adc_c_REF_5 */
            EndStatus = ADC_GET_RESBUFENDSTATUS(DataPtr->GrpBufferEndResultStatus, GroupId);

            if (1U == EndStatus)
            {
                /* SWS_Adc_00325: shall return ADC_STREAM_COMPLETED */
                RetStatus = ADC_STREAM_COMPLETED;
            }
            else
            {
                /* #Violation: Adc_c_REF_7 */
                GrpRes = ADC_GET_RESULTSTATUS(DataPtr->GroupResultStatus, GroupId);
                /* check if at least one set of results of Group available */
                if (ADC_BUSY == GrpRes)
                {
                    /* SWS_Adc_00224: shall return ADC_COMPLETED */
                    RetStatus = ADC_COMPLETED;
                }
                /* Group is either in ADC_BUSY state or ADC_IDLE state */
                else
                {
                    /* SWS_Adc_00221: shall return ADC_IDLE */
                    /* SWS_Adc_00222: shall return ADC_BUSY */
                    /* #Violation: Adc_c_REF_7 */
                    RetStatus = ADC_GET_GROUPSTATUS(DataPtr->GroupStatus, GroupId);
                }
            }

            /* Exit Critical section */
            ADC_EXIT_CRITICAL_SECTION(GetGrpStatus);
        }
    }

    return RetStatus;
}

#if ((ADC_INTERRUPT_MODE_ENABLE == STD_ON) || (ADC_POLLING_MODE_ENABLE == STD_ON))
/****************************************************************************************************
*   Function Name           : Adc_GetStreamLastPointer
*
*   Service ID              : 0x0b
*
*   Description             : Returns the number of valid samples per channel, stored in the result
*                             buffer. Reads a pointer, pointing to a position in the group result
*                             buffer. With the pointer position, the results of all group channels
*                             of the last completed conversion round can be accessed.
*                             With the pointer and the return value, all valid group conversion
*                             results can be accessed (the user has to take the layout of the result
*                             buffer into account).
*
*   Parameters in           : Group: Numeric ID of requested ADC Channel group.
*
*   Parameters inout        : None.
*
*   Parameters out          : SamplePtr: Pointer to result buffer pointer.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant for different group, Non-reentrant for same group.
*
*   Return value            : Number of valid samples per channel.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Adc_00375, SWS_Adc_00214, SWS_Adc_00382,
*                             SWS_Adc_00413
****************************************************************************************************/
/* #Violation: Adc_c_REF_13 */
FUNC(Adc_StreamNumSampleType, ADC_PUBLIC_CODE) Adc_GetStreamLastPointer
(
    Adc_GroupType Group,
    /* #Violation: Adc_c_REF_8 */
    /* #Violation: Adc_c_REF_9 */
    P2P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) PtrToSamplePtr
)
{
    Adc_GlobalDataType        *DataPtr;
    const Adc_GroupCfgType    *GrpPtr;
    uint32                    BufEndStatus;
    Adc_ValueGroupType        *CurrentResBufPtr;
    Adc_GroupType             GroupId;
    Adc_StreamNumSampleType   NoOfValidConv;
    Adc_StreamNumSampleType   RetVal;
    Adc_StatusType            GrpStatus;
    Adc_StatusType            GrpRes;
    Adc_HwUnitType            PhyHwUnitId;
    Mcal_CoreType             CoreId;
    uint8                     HwUnitCoreIdx;
    uint32                    Err;

    /* Get PhyHwUnitId number from Group ID */
    /* #Violation: Adc_c_REF_5 */
    PhyHwUnitId = (Adc_HwUnitType)ADC_GET_HWUNITID(Group);

    /* Get the Group Id for particular PhyHwUnitId */
    /* #Violation: Adc_c_REF_5 */
    GroupId = (Adc_GroupType)ADC_GET_GROUPID(Group);

    /* SWS_Adc_00216: When called while the group status is ADC_BUSY (a conversion of the group is
     * in progress), the function Adc_GetStreamLastPointer shall set the pointer, passed as
     * parameter (PtrToSamplePtr), to NULL and return 0 */
    /* Initialize the out parameter to NULL_PTR */
    *PtrToSamplePtr = (Adc_ValueGroupType*)NULL_PTR;
    /* Initialize the service return value to 0 */
    RetVal = 0U;

    /* Get core id which core is currently executing */
    /* #Violation: Adc_c_REF_5 */
    CoreId = Mcal_GetCoreId();

#if (ADC_DEV_ERROR_DETECT == STD_ON)
    /* The Adc_DetErrorCheck function covers the following SWS */
    /* SWS_Adc_00302: called prior to initializing the driver */
    /* SWS_Adc_00218: group ID is non-existent */
    Err = Adc_DetErrorCheck(ADC_SID_GET_STREAM_LAST_POINTER, GroupId, PhyHwUnitId);
#if (ADC_DMA_MODE_ENABLE == STD_ON)
    if (E_OK == Err)
    {
        /* Find the sub-index according to the Adc number */
        HwUnitCoreIdx = Adc_ConfigPtr->HwUnitToCorePtr[PhyHwUnitId].CoreHwUnitIdx;
        if (ADC_RESULT_HANDLING_DMA_MODE == Adc_ConfigPtr->CoreConfigPtr[CoreId]->
                                                  HwUnitConfigPtr[HwUnitCoreIdx].RsltHldMthd)
        {
            /* This group of HW unit is in DMA mode */
            Adc_ReportError(ADC_SID_GET_STREAM_LAST_POINTER, ADC_E_DMA_CHANNEL_ENABLED);
            Err = E_NOT_OK;
        }
    }
#endif /* \(ADC_DMA_MODE_ENABLE == STD_ON) */
    if (E_OK == Err)
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Enter Critical Section */
        ADC_ENTER_CRITICAL_SECTION(GetStreamLastPtr);
        /* SWS_Adc_00215: when called while the group status is ADC_IDLE and the group
         * conversion was not started (no results are available from previous conversions) */
        Err = Adc_CheckDriverState(GroupId, PhyHwUnitId);
        /* Exit Critical Section */
        ADC_EXIT_CRITICAL_SECTION(GetStreamLastPtr);

        if (E_OK == Err)
        {
            /* Find the sub-index according to the Adc number */
            HwUnitCoreIdx = Adc_ConfigPtr->HwUnitToCorePtr[PhyHwUnitId].CoreHwUnitIdx;
            /* Find the configuration information of current ADC */
            GrpPtr = &(Adc_ConfigPtr->CoreConfigPtr[CoreId]->HwUnitConfigPtr[HwUnitCoreIdx]
                                                                            .GrpCfgPtr[GroupId]);

              /* Get global data pointer of current ADC*/
            DataPtr = ADC_GET_DATAADDRESS(CoreId, PhyHwUnitId);

            /* Enter Critical section */
            ADC_ENTER_CRITICAL_SECTION(GetStreamLastPtr);

            /* Note: Read group status and group result status */
            /* #Violation: Adc_c_REF_7 */
            GrpStatus = ADC_GET_GROUPSTATUS(DataPtr->GroupStatus, GroupId);
            /* #Violation: Adc_c_REF_7 */
            GrpRes = ADC_GET_RESULTSTATUS(DataPtr->GroupResultStatus, GroupId);

            /* If Group is in ADC_BUSY state the valid conversion number is 0 */
            /* #Violation: Adc_c_REF_7 */
            if ((GrpStatus != ADC_IDLE) && (GrpRes == (Adc_StatusType)0U))
            {
                /* Exit Critical section */
                ADC_EXIT_CRITICAL_SECTION(GetStreamLastPtr);

                /* Group status is ADC_BUSY, return 0 */
                NoOfValidConv = 0U;
            }
            else
            {
                BufEndStatus =
                /* #Violation: Adc_c_REF_5 */
                        ADC_GET_RESBUFENDSTATUS(DataPtr->GrpBufferEndResultStatus, GroupId);

                /* Clear ADC Group Result Status on read */
                /* #Violation: Adc_c_REF_10 */
                ADC_CLR_RESULTSTATUS(DataPtr->GroupResultStatus, GroupId);

                /* Clear the Buffer end status */
                /* #Violation: Adc_c_REF_10 */
                ADC_CLR_RESBUFENDSTATUS(DataPtr->GrpBufferEndResultStatus, GroupId);

                /* Read the no. of valid conversation results available */
                NoOfValidConv = DataPtr->NumValidConResPtr[GroupId];
                /* latest valid data location in result buffer */
                CurrentResBufPtr = &(DataPtr->GroupResultBufferPtr[GroupId][NoOfValidConv - 1U]);

                /* Exit Critical section */
                ADC_EXIT_CRITICAL_SECTION(GetStreamLastPtr);

                if (BufEndStatus != 0U)
                {
                    /* All the location in result buffer is filled with valid data */
                    NoOfValidConv = GrpPtr->NumSamples;
                }

                /* SWS_Adc_00214 */
                /* SWS_Adc_00418: All values stores in the result buffer and left without
                 * further scaling */
                /* set result buffer pointer for user */
                *PtrToSamplePtr = CurrentResBufPtr;
            }

            /* SWS_Adc_00387: shall return the number of valid samples per channel,
             * stored in the result buffer */
            RetVal = NoOfValidConv;
        }
        else
        {
            /* Service is while the group is in Idle state */
            Adc_ReportRuntimeError(ADC_SID_GET_STREAM_LAST_POINTER, ADC_E_IDLE);
        }
    }

    return RetVal;
}
#endif /* \((ADC_INTERRUPT_MODE_ENABLE == STD_ON) || (ADC_POLLING_MODE_ENABLE== STD_ON)) */

#if (ADC_VERSION_INFO_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Adc_GetVersionInfo
*
*   Service ID              : 0x0a
*
*   Description             : Returns the version information of this module.
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
*   AUTOSAR_Requirement     : SWS_Adc_00376.
****************************************************************************************************/
/* #Violation: Adc_c_REF_13 */
FUNC(void, ADC_PUBLIC_CODE) Adc_GetVersionInfo
(
    /* #Violation: Adc_c_REF_8 */
    /* #Violation: Adc_c_REF_9 */
    P2VAR(Std_VersionInfoType , AUTOMATIC, ADC_APPL_DATA) VersionInfoPtr
)
{
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    /* Check for DET: ADC_E_PARAM_POINTER */
    if (VersionInfoPtr == NULL_PTR)
    {
        /* SWS_Adc_00458: check the parameter version info is NULL */
        Adc_ReportError(ADC_SID_GET_VERSION_INFO, ADC_E_PARAM_POINTER);
    }
    else
#endif
    {
       VersionInfoPtr->moduleID = (uint16)ADC_MODULE_ID;
       VersionInfoPtr->vendorID = (uint16)ADC_VENDOR_ID;
       VersionInfoPtr->sw_major_version = (uint8)ADC_SW_MAJOR_VERSION;
       VersionInfoPtr->sw_minor_version = (uint8)ADC_SW_MINOR_VERSION;
       VersionInfoPtr->sw_patch_version = (uint8)ADC_SW_PATCH_VERSION;
    }
}
#endif /* \(ADC_VERSION_INFO_API == STD_ON) */

#if (ADC_POWER_STATE_SUPPORTED == STD_ON)
/****************************************************************************************************
*   Function Name           : Adc_SetPowerState
*
*   Service ID              : 0x10
*
*   Description             : This API configures the Adc module so that it enters the already
*                             prepared power state, chosen between a predefined set of configured
*                             ones.
*
*   Parameters in           : Group: Group ID.
*
*   Parameters inout        : None.
*
*   Parameters out          : ResultPtr:
*                             If the API returns E_OK:
*                                - ADC_SERVICE_ACCEPTED: Power state change executed.
*                             If the API returns E_NOT_OK:
*                                - ADC_NOT_INIT: ADC Module not initialized.
*                                - ADC_SEQUENCE_ERROR: wrong API call sequence.
*                                - ADC_HW_FAILURE: the HW module has a failure which prevents it to
*                                         enter the required power state.
*
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : E_OK: Power Mode changed
*                             E_NOT_OK: request rejected
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Adc_00475, SWS_Adc_00481.
****************************************************************************************************/
FUNC(Std_ReturnType, ADC_PUBLIC_CODE) Adc_SetPowerState
(
    P2VAR(Adc_PowerStateRequestResultType, AUTOMATIC, ADC_APPL_DATA) ResultPtr
)
{
    Std_ReturnType RetVal = E_NOT_OK;

#if (ADC_DEV_ERROR_DETECT == STD_ON)
    Adc_ReportError(ADC_SID_SET_POWER_STATE, ADC_E_POWER_STATE_NOT_SUPPORTED);
#endif
    *ResultPtr = ADC_NOT_INIT;

    return RetVal;
}

/****************************************************************************************************
*   Function Name           : Adc_GetCurrentPowerState
*
*   Service ID              : 0x11
*
*   Description             : This API returns the current power state of the ADC HW unit.
*
*   Parameters in           : Group: Group ID.
*
*   Parameters inout        : None.
*
*   Parameters out          : CurrentPowerState: The current power mode of the ADC HW Unit is
*                                returned in this parameter
*                             ResultPtr: as follows:
*                               - If the API returns E_OK: ADC_SERVICE_ACCEPTED: Current power
*                                  mode was returned.
*                               - If the API returns E_NOT_OK: ADC_NOT_INIT: ADC Module not
*                                  initialized.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : E_OK: Mode could be read
*                             E_NOT_OK: Service is rejected
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Adc_00476, SWS_Adc_00491.
****************************************************************************************************/
FUNC(Std_ReturnType, ADC_PUBLIC_CODE) Adc_GetCurrentPowerState
(
    P2VAR(Adc_PowerStateType, AUTOMATIC, ADC_APPL_DATA) CurrentPowerState,
    P2VAR(Adc_PowerStateRequestResultType, AUTOMATIC, ADC_APPL_DATA) ResultPtr
)
{
    Std_ReturnType RetVal = E_NOT_OK;

#if (ADC_DEV_ERROR_DETECT == STD_ON)
    Adc_ReportError(ADC_SID_GET_CURRENT_POWER_STATE, ADC_E_POWER_STATE_NOT_SUPPORTED);
#endif
    *ResultPtr = ADC_NOT_INIT;

    return RetVal;
}

/****************************************************************************************************
*   Function Name           : Adc_GetTargetPowerState
*
*   Service ID              : 0x12
*
*   Description             : This API returns the Target power state of the ADC HW unit.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : CurrentPowerState: The Target power mode of the ADC HW Unit is
*                               returned in this parameter.
*                             ResultPtr: as follows:
*                               - If the API returns E_OK: ADC_SERVICE_ACCEPTED:Target power
*                                   mode was returned.
*                               - If the API returns E_NOT_OK: ADC_NOT_INIT: ADC Module not
*                                   initialized.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : E_OK: Mode could be read
*                             E_NOT_OK: Service is rejected
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Adc_00492.
****************************************************************************************************/

FUNC(Std_ReturnType, ADC_PUBLIC_CODE) Adc_GetTargetPowerState
(
    P2VAR(Adc_PowerStateType, AUTOMATIC, ADC_APPL_DATA) TargetPowerState,
    P2VAR(Adc_PowerStateRequestResultType, AUTOMATIC, ADC_APPL_DATA) ResultPtr
)
{
    Std_ReturnType RetVal = E_NOT_OK;

#if (ADC_DEV_ERROR_DETECT == STD_ON)
    Adc_ReportError(ADC_SID_GET_TARGET_POWER_STATE, ADC_E_POWER_STATE_NOT_SUPPORTED);
#endif
    *ResultPtr = ADC_NOT_INIT;

    return RetVal;
}

/****************************************************************************************************
*   Function Name           : Adc_PreparePowerState
*
*   Service ID              : 0x13
*
*   Description             : This API starts the needed process to allow the ADC HW module to enter
*                             the requested power state.
*
*   Parameters in           : PowerState: The target power state intended to be attained.
*
*   Parameters inout        : None.
*
*   Parameters out          : ResultPtr:
*                               - If the API returns E_OK:
*                                   - ADC_SERVICE_ACCEPTED: ADC Module power state preparation was
*                                       started.
*                               - If the API returns E_NOT_OK:
*                                   - ADC_NOT_INIT: ADC Module not initialized.
*                                   - ADC_SEQUENCE_ERROR: wrong API call sequence (Current power
*                                       State = Target Power State).
*                                   - ADC_POWER_STATE_NOT_SUPP: ADC Module does not support the
*                                       requested power state.
*                                   - ADC_TRANS_NOT_POSSIBLE: ADC Module cannot transition directly
*                                       from the current power state to the requested power state
*                                       or the HW peripheral is still busy.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : E_OK: Preparation process started
*                             E_NOT_OK: Service is rejected
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Adc_00478, SWS_Adc_00494.
****************************************************************************************************/
FUNC(Std_ReturnType, ADC_PUBLIC_CODE) Adc_PreparePowerState
(
    Adc_PowerStateType PowerState,
    P2VAR(Adc_PowerStateRequestResultType, AUTOMATIC, ADC_APPL_DATA) ResultPtr
)
{
    Std_ReturnType RetVal = E_NOT_OK;

#if (ADC_DEV_ERROR_DETECT == STD_ON)
    Adc_ReportError(ADC_SID_PREPARE_POWER_STATE, ADC_E_POWER_STATE_NOT_SUPPORTED);
#endif
    *ResultPtr = ADC_POWER_STATE_NOT_SUPP;

    return RetVal;
}

#endif /* \(ADC_POWER_STATE_SUPPORTED == STD_ON) */

#if ((ADC_INTERRUPT_MODE_ENABLE == STD_ON) || (ADC_DMA_MODE_ENABLE == STD_ON))
/****************************************************************************************************
*   Function Name           : Adc_QueueRequest_ISRHandler
*
*   Service ID              : 0xE0.
*
*   Description             : Conversion completed interrupt.
*
*   Parameters in           : PhyHwUnitId: the ADC number.
*                             ReqSrc: interrupt source from which queue.
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
*   AUTOSAR_Requirement     : SWS_Adc_00078.
****************************************************************************************************/
FUNC(void, ADC_PUBLIC_CODE) Adc_QueueRequest_ISRHandler
(
    Adc_HwUnitType PhyHwUnitId,
    Saradc_RequestSource ReqSrc
)
{
    uint8                      HwUnitCoreIdx;
    boolean                    OperationRslt;
    Adc_GlobalDataType         *DataPtr;
    Mcal_CoreType              CoreId;
    const Adc_KernelConfigType *HwUnitConfigPtr;
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    uint32                     Err;
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */

#if (ADC_DEV_ERROR_DETECT == STD_ON)
    Err = Adc_CheckInit(ADC_SID_REQ_QUEUE_ISR);
    if (E_OK == Err)
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
    {
#if (ADC_DEV_ERROR_DETECT == STD_ON)
        Err = Adc_CheckMulticoreAllocateError(ADC_SID_REQ_QUEUE_ISR, PhyHwUnitId);
        if (E_OK == Err)
#endif /* \(ADC_DEV_ERROR_DETECT == STD_ON) */
        {
            /* #Violation: Adc_c_REF_5 */
            CoreId = Mcal_GetCoreId();

            /* Get global data pointer of current ADC*/
            DataPtr = ADC_GET_DATAADDRESS(CoreId, PhyHwUnitId);
            HwUnitCoreIdx = Adc_ConfigPtr->HwUnitToCorePtr[PhyHwUnitId].CoreHwUnitIdx;
            /* HW unit configuration parameter */
            HwUnitConfigPtr =
                    &(Adc_ConfigPtr->CoreConfigPtr[CoreId]->HwUnitConfigPtr[HwUnitCoreIdx]);
            /* To process interrupt event */
            OperationRslt = Adc_IsrEventHandler(PhyHwUnitId, ReqSrc, HwUnitConfigPtr, DataPtr);
#if (ADC_SAFETY_ENABLE == STD_ON)
            if (FALSE == OperationRslt)
            {
                Adc_ReportRuntimeError(ADC_SID_REQ_QUEUE_ISR, ADC_E_REG_CHECK_FAIL);
            }
#else /* \(ADC_SAFETY_ENABLE == STD_ON) */
            /* #Violation: Adc_c_REF_5 */
            MCAL_UNUSED_VAR(OperationRslt);
#endif /* \(ADC_SAFETY_ENABLE == STD_ON) */
        }
    }
}
#endif /* \((ADC_INTERRUPT_MODE_ENABLE == STD_ON) || (ADC_DMA_MODE_ENABLE== STD_ON)) */
/* #Violation: Adc_c_REF_12 */
#define ADC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Adc_c_REF_1 */
#include "Adc_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
