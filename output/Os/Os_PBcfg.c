/**
 * @file Os_PBcfg.c
 * @brief Post-Build Configuration for Os module
 */

#include "Os_Cfg.h"
#include "Os_MemMap.h"

#define OS_START_SEC_CONFIG_DATA_POSTBUILD
#include "Os_MemMap.h"

/* Post-Build Parameters Configuration */
CONST(Os_ConfigType, OS_CONST) Os_PBConfig = {


    /* Container: OsCoreIdMappingConfig_0 */
    
        /* Param: OsPhysicalCoreId = 0 */
    
    
        /* Ref: OsCoreId = &EcuC_EcuC_EcucHardware_EcucCoreDefinition_0_Config */
    
        /* Ref: OsKernelApplication = &Os_Os_OsApplication_0_Config */
    
        /* Ref: OsTpCounterRef = &Os_Os_OsCounter_Hrt_Config */
    

    /* Container: OsCoreIdMappingConfig_1 */
    
        /* Param: OsPhysicalCoreId = 1 */
    
    
        /* Ref: OsCoreId = &EcuC_EcuC_EcucHardware_EcucCoreDefinition_1_Config */
    
        /* Ref: OsKernelApplication = &Os_Os_OsApplication_3_Config */
    
        /* Ref: OsTpCounterRef = &Os_Os_OsCounter_Hrt_Core1_Config */
    

    /* Container: OsAlarm_0 */
    
        /* Param: OsAlarmUseAutostart = 1 */
    
    
        /* Ref: OsAlarmCounterRef = &Os_Os_OsCounter_Software_Config */
    

    /* Container: OsAlarm_1 */
    
        /* Param: OsAlarmUseAutostart = 1 */
    
    
        /* Ref: OsAlarmCounterRef = &Os_Os_OsCounter_SystemTick_Config */
    

    /* Container: OsAlarm_2 */
    
        /* Param: OsAlarmUseAutostart = 1 */
    
    
        /* Ref: OsAlarmCounterRef = &Os_Os_OsCounter_SystemTick_Config */
    

    /* Container: OsAlarm_3 */
    
        /* Param: OsAlarmUseAutostart = 1 */
    
    
        /* Ref: OsAlarmCounterRef = &Os_Os_OsCounter_Software2_Config */
    

    /* Container: OsAlarm_4 */
    
        /* Param: OsAlarmUseAutostart = 1 */
    
    
        /* Ref: OsAlarmCounterRef = &Os_Os_OsCounter_Pit_Config */
    

    /* Container: OsAlarm_5 */
    
        /* Param: OsAlarmUseAutostart = 1 */
    
    
        /* Ref: OsAlarmCounterRef = &Os_Os_OsCounter_SystemTick_Core1_Config */
    

    /* Container: OsAlarm_6 */
    
        /* Param: OsAlarmUseAutostart = 1 */
    
    
        /* Ref: OsAlarmCounterRef = &Os_Os_OsCounter_Software2_Config */
    

    /* Container: OsAlarm_7 */
    
        /* Param: OsAlarmUseAutostart = 1 */
    
    
        /* Ref: OsAlarmCounterRef = &Os_Os_OsCounter_Software2_Config */
    

    /* Container: OsAlarm_8 */
    
        /* Param: OsAlarmUseAutostart = 1 */
    
    
        /* Ref: OsAlarmCounterRef = &Os_Os_OsCounter_Software_Core1_Config */
    

    /* Container: OsAlarm_9 */
    
        /* Param: OsAlarmUseAutostart = 1 */
    
    
        /* Ref: OsAlarmCounterRef = &Os_Os_OsCounter_Software_Core1_Config */
    

    /* Container: OSDEFAULTAPPMODE */
    
    

    /* Container: OSALLRUNNINGMODE */
    
    

    /* Container: OSTRUSTAPP01MODE */
    
    

    /* Container: OsApplication_0 */
    
        /* Param: OsTrusted = 1 */
    
        /* Param: OsTrustedApplicationDelayTimingViolationCall = 1 */
    
        /* Param: OsTrustedApplicationWithProtection = 0 */
    
    
        /* Ref: OsApplicationCoreRef = &Os_Os_OsCoreIdMappingConfig_0_Config */
    

    /* Container: OsApplication_1 */
    
        /* Param: OsTrusted = 0 */
    
        /* Param: OsTrustedApplicationDelayTimingViolationCall = 1 */
    
        /* Param: OsTrustedApplicationWithProtection = 0 */
    
    
        /* Ref: OsApplicationCoreRef = &Os_Os_OsCoreIdMappingConfig_0_Config */
    

    /* Container: OsApplication_2 */
    
        /* Param: OsTrusted = 1 */
    
        /* Param: OsTrustedApplicationDelayTimingViolationCall = 0 */
    
        /* Param: OsTrustedApplicationWithProtection = 0 */
    
    
        /* Ref: OsApplicationCoreRef = &Os_Os_OsCoreIdMappingConfig_0_Config */
    

    /* Container: OsApplication_3 */
    
        /* Param: OsTrusted = 1 */
    
        /* Param: OsTrustedApplicationDelayTimingViolationCall = 1 */
    
        /* Param: OsTrustedApplicationWithProtection = 0 */
    
    
        /* Ref: OsApplicationCoreRef = &Os_Os_OsCoreIdMappingConfig_1_Config */
    

    /* Container: OsCounter_Software */
    
        /* Param: OsCounterMaxAllowedValue = 1000 */
    
        /* Param: OsCounterMinCycle = 1 */
    
        /* Param: OsCounterTicksPerBase = 1 */
    
        /* Param: OsCounterType = SOFTWARE */
    
        /* Param: OsTimerHighResolution = 1 */
    
        /* Param: OsSecondsPerTick = 0.01 */
    
    
        /* Ref: OsTimerTypeIsrRef = &Os_Os_Os_IsrCfg_SystemTimer_Config */
    

    /* Container: OsCounter_SystemTick */
    
        /* Param: OsCounterMaxAllowedValue = 1000 */
    
        /* Param: OsCounterMinCycle = 1 */
    
        /* Param: OsCounterTicksPerBase = 25000 */
    
        /* Param: OsCounterType = HARDWARE */
    
        /* Param: OsTimerHighResolution = 0 */
    
        /* Param: OsSecondsPerTick = 0.001 */
    
    
        /* Ref: OsTimerTypeIsrRef = &Os_Os_Os_IsrCfg_SystemTimer_Config */
    

    /* Container: OsCounter_Hrt */
    
        /* Param: OsCounterMaxAllowedValue = 1073741823 */
    
        /* Param: OsCounterMinCycle = 1 */
    
        /* Param: OsCounterTicksPerBase = 1 */
    
        /* Param: OsCounterType = HARDWARE */
    
        /* Param: OsTimerHighResolution = 1 */
    
        /* Param: OsSecondsPerTick = 4E-08 */
    
    
        /* Ref: OsTimerTypeIsrRef = &Os_Os_Os_IsrCfg_VirtualTimer_Config */
    

    /* Container: OsCounter_Pit */
    
        /* Param: OsCounterMaxAllowedValue = 1000 */
    
        /* Param: OsCounterMinCycle = 1 */
    
        /* Param: OsCounterTicksPerBase = 100000 */
    
        /* Param: OsCounterType = HARDWARE */
    
        /* Param: OsTimerHighResolution = 0 */
    
        /* Param: OsSecondsPerTick = 0.001 */
    
    
        /* Ref: OsTimerTypeIsrRef = &Os_Os_Os_IsrCfg_BaseTimer0_Config */
    

    /* Container: OsCounter_Software2 */
    
        /* Param: OsCounterMaxAllowedValue = 200 */
    
        /* Param: OsCounterMinCycle = 1 */
    
        /* Param: OsCounterTicksPerBase = 1 */
    
        /* Param: OsCounterType = SOFTWARE */
    
        /* Param: OsTimerHighResolution = 0 */
    
        /* Param: OsSecondsPerTick = 0.001 */
    
    

    /* Container: OsCounter_SystemTick_Core1 */
    
        /* Param: OsCounterMaxAllowedValue = 1000 */
    
        /* Param: OsCounterMinCycle = 1 */
    
        /* Param: OsCounterTicksPerBase = 25000 */
    
        /* Param: OsCounterType = HARDWARE */
    
        /* Param: OsTimerHighResolution = 0 */
    
        /* Param: OsSecondsPerTick = 0.001 */
    
    
        /* Ref: OsTimerTypeIsrRef = &Os_Os_Os_IsrCfg_SystemTimer_Core1_Config */
    

    /* Container: OsCounter_Hrt_Core1 */
    
        /* Param: OsCounterMaxAllowedValue = 1073741823 */
    
        /* Param: OsCounterMinCycle = 1 */
    
        /* Param: OsCounterTicksPerBase = 1 */
    
        /* Param: OsCounterType = HARDWARE */
    
        /* Param: OsTimerHighResolution = 1 */
    
        /* Param: OsSecondsPerTick = 4E-08 */
    
    
        /* Ref: OsTimerTypeIsrRef = &Os_Os_OsIsr_IsrCfg_VirtualTimer_Core1_Config */
    

    /* Container: OsCounter_Software_Core1 */
    
        /* Param: OsCounterMaxAllowedValue = 300 */
    
        /* Param: OsCounterMinCycle = 1 */
    
        /* Param: OsCounterTicksPerBase = 1 */
    
        /* Param: OsCounterType = SOFTWARE */
    
        /* Param: OsTimerHighResolution = 0 */
    
        /* Param: OsSecondsPerTick = 0.001 */
    
    

    /* Container: OsEvent_0 */
    
        /* Param: OsEventMask = 1 */
    
    

    /* Container: OsEvent_1 */
    
        /* Param: OsEventMask = 2 */
    
    

    /* Container: OsEvent_2 */
    
        /* Param: OsEventMask = 4 */
    
    

    /* Container: OsEvent_3 */
    
        /* Param: OsEventMask = 8 */
    
    

    /* Container: OsEvent_4 */
    
        /* Param: OsEventMask = 16 */
    
    

    /* Container: Os_IsrCfg_VirtualTimer */
    
        /* Param: OsIsrCategory = CATEGORY_2 */
    
        /* Param: OsIsrInterruptSource = 27 */
    
        /* Param: OsIsrPriority = 27 */
    
        /* Param: OsIsrTriggerMethod = EDGE */
    
        /* Param: OsIsrSrcAssignedTo = IRQ */
    
        /* Param: OsIsrHandler = ISR_TIMINGPROTECTIONSERVICE */
    
        /* Param: OsIsrInitialEnableInterruptSource = 1 */
    
        /* Param: IsrStackSize = 1024 */
    
        /* Param: IsCrossCoreServiceCallIsr = 0 */
    
    

    /* Container: Os_IsrCfg_SystemTimer */
    
        /* Param: OsIsrCategory = CATEGORY_2 */
    
        /* Param: OsIsrInterruptSource = 30 */
    
        /* Param: OsIsrPriority = 30 */
    
        /* Param: OsIsrTriggerMethod = EDGE */
    
        /* Param: OsIsrSrcAssignedTo = IRQ */
    
        /* Param: OsIsrHandler = ISR_OSCOUNTER_PFRTSERVICE */
    
        /* Param: OsIsrInitialEnableInterruptSource = 1 */
    
        /* Param: IsrStackSize = 1024 */
    
        /* Param: IsCrossCoreServiceCallIsr = 0 */
    
    

    /* Container: Os_IsrCfg_BaseTimer0 */
    
        /* Param: OsIsrCategory = CATEGORY_2 */
    
        /* Param: OsIsrInterruptSource = 246 */
    
        /* Param: OsIsrPriority = 28 */
    
        /* Param: OsIsrTriggerMethod = LEVEL */
    
        /* Param: OsIsrSrcAssignedTo = IRQ */
    
        /* Param: OsIsrHandler = ISR_OSCOUNTER_PITSERVICE */
    
        /* Param: OsIsrInitialEnableInterruptSource = 1 */
    
        /* Param: IsrStackSize = 1024 */
    
        /* Param: IsCrossCoreServiceCallIsr = 0 */
    
    

    /* Container: Os_IsrCfg_SystemTimer_Core1 */
    
        /* Param: OsIsrCategory = CATEGORY_2 */
    
        /* Param: OsIsrInterruptSource = 30 */
    
        /* Param: OsIsrPriority = 30 */
    
        /* Param: OsIsrTriggerMethod = EDGE */
    
        /* Param: OsIsrSrcAssignedTo = IRQ */
    
        /* Param: OsIsrHandler = ISR_OSCOUNTER_PFRTSERVICE */
    
        /* Param: OsIsrInitialEnableInterruptSource = 1 */
    
        /* Param: IsrStackSize = 1024 */
    
        /* Param: IsCrossCoreServiceCallIsr = 0 */
    
    

    /* Container: OsIsr_BaseTimer1 */
    
        /* Param: OsIsrCategory = CATEGORY_2 */
    
        /* Param: OsIsrInterruptSource = 247 */
    
        /* Param: OsIsrPriority = 29 */
    
        /* Param: OsIsrTriggerMethod = EDGE */
    
        /* Param: OsIsrSrcAssignedTo = IRQ */
    
        /* Param: OsIsrHandler = ISR_ISR2TEST */
    
        /* Param: OsIsrInitialEnableInterruptSource = 1 */
    
        /* Param: IsrStackSize = 1024 */
    
        /* Param: IsCrossCoreServiceCallIsr = 0 */
    
    

    /* Container: OsIsr_IsrCfg_VirtualTimer_Core1 */
    
        /* Param: OsIsrCategory = CATEGORY_2 */
    
        /* Param: OsIsrInterruptSource = 27 */
    
        /* Param: OsIsrPriority = 27 */
    
        /* Param: OsIsrTriggerMethod = EDGE */
    
        /* Param: OsIsrSrcAssignedTo = IRQ */
    
        /* Param: OsIsrHandler = ISR_TIMINGPROTECTIONSERVICE */
    
        /* Param: OsIsrInitialEnableInterruptSource = 1 */
    
        /* Param: IsrStackSize = 1024 */
    
        /* Param: IsCrossCoreServiceCallIsr = 0 */
    
    

    /* Container: OsIsr_0 */
    
        /* Param: OsIsrCategory = CATEGORY_2 */
    
        /* Param: OsIsrInterruptSource = 0 */
    
        /* Param: OsIsrPriority = 28 */
    
        /* Param: OsIsrTriggerMethod = EDGE */
    
        /* Param: OsIsrSrcAssignedTo = IRQ */
    
        /* Param: OsIsrHandler =  */
    
        /* Param: OsIsrInitialEnableInterruptSource = 1 */
    
        /* Param: IsrStackSize = 1024 */
    
        /* Param: IsCrossCoreServiceCallIsr = 1 */
    
    

    /* Container: OsIsr_1 */
    
        /* Param: OsIsrCategory = CATEGORY_2 */
    
        /* Param: OsIsrInterruptSource = 0 */
    
        /* Param: OsIsrPriority = 28 */
    
        /* Param: OsIsrTriggerMethod = EDGE */
    
        /* Param: OsIsrSrcAssignedTo = IRQ */
    
        /* Param: OsIsrHandler =  */
    
        /* Param: OsIsrInitialEnableInterruptSource = 1 */
    
        /* Param: IsrStackSize = 1024 */
    
        /* Param: IsCrossCoreServiceCallIsr = 1 */
    
    

    /* Container: OsOS */
    
        /* Param: OsNumberOfCores = 2 */
    
        /* Param: OsScalabilityClass = SC4 */
    
        /* Param: OsStackMonitoring = 0 */
    
        /* Param: OsStatus = EXTENDED */
    
        /* Param: OsUseServiceProtection = 0 */
    
        /* Param: OsUseArti = 0 */
    
        /* Param: OsUseGetServiceId = 1 */
    
        /* Param: OsUseParameterAccess = 1 */
    
        /* Param: OsUseResScheduler = 1 */
    
    

    /* Container: OsResource_0 */
    
        /* Param: OsResourceProperty = STANDARD */
    
        /* Param: OsResourceLinkedToResScheduler = 0 */
    
    
        /* Ref: OsResourceCoreRef = &Os_Os_OsCoreIdMappingConfig_0_Config */
    

    /* Container: OsResource_1 */
    
        /* Param: OsResourceProperty = STANDARD */
    
        /* Param: OsResourceLinkedToResScheduler = 0 */
    
    
        /* Ref: OsResourceCoreRef = &Os_Os_OsCoreIdMappingConfig_0_Config */
    

    /* Container: OsResource_2 */
    
        /* Param: OsResourceProperty = STANDARD */
    
        /* Param: OsResourceLinkedToResScheduler = 0 */
    
    
        /* Ref: OsResourceCoreRef = &Os_Os_OsCoreIdMappingConfig_1_Config */
    

    /* Container: OsScheduleTable_0 */
    
        /* Param: OsScheduleTableDuration = 100 */
    
        /* Param: OsScheduleTableRepeating = 1 */
    
        /* Param: OsScheduleTblSyncStrategy = NONE */
    
        /* Param: OsScheduleTblExplicitPrecision = 0 */
    
    
        /* Ref: OsScheduleTableCounterRef = &Os_Os_OsCounter_SystemTick_Config */
    

    /* Container: OsScheduleTable_1 */
    
        /* Param: OsScheduleTableDuration = 100 */
    
        /* Param: OsScheduleTableRepeating = 1 */
    
        /* Param: OsScheduleTblSyncStrategy = NONE */
    
        /* Param: OsScheduleTblExplicitPrecision = 0 */
    
    
        /* Ref: OsScheduleTableCounterRef = &Os_Os_OsCounter_SystemTick_Core1_Config */
    

    /* Container: OsSpinlock_0 */
    
        /* Param: OsSpinlockLockMethod = LOCK_NOTHING */
    
    

    /* Container: Idle_Task_Core0 */
    
        /* Param: OsTaskActivation = 1 */
    
        /* Param: OsTaskPriority = 0 */
    
        /* Param: OsTaskSchedule = FULL */
    
        /* Param: OsTaskType = BASIC */
    
        /* Param: OsTaskUseAutostart = 1 */
    
        /* Param: TaskStackSize = 1024 */
    
    

    /* Container: Idle_Task_Core1 */
    
        /* Param: OsTaskActivation = 1 */
    
        /* Param: OsTaskPriority = 0 */
    
        /* Param: OsTaskSchedule = FULL */
    
        /* Param: OsTaskType = BASIC */
    
        /* Param: OsTaskUseAutostart = 1 */
    
        /* Param: TaskStackSize = 1024 */
    
    

    /* Container: Task1 */
    
        /* Param: OsTaskActivation = 1 */
    
        /* Param: OsTaskPriority = 1 */
    
        /* Param: OsTaskSchedule = FULL */
    
        /* Param: OsTaskType = BASIC */
    
        /* Param: OsTaskUseAutostart = 1 */
    
        /* Param: TaskStackSize = 1024 */
    
    

    /* Container: Task2 */
    
        /* Param: OsTaskActivation = 1 */
    
        /* Param: OsTaskPriority = 6 */
    
        /* Param: OsTaskSchedule = FULL */
    
        /* Param: OsTaskType = BASIC */
    
        /* Param: OsTaskUseAutostart = 1 */
    
        /* Param: TaskStackSize = 1024 */
    
    

    /* Container: Task3 */
    
        /* Param: OsTaskActivation = 1 */
    
        /* Param: OsTaskPriority = 1 */
    
        /* Param: OsTaskSchedule = FULL */
    
        /* Param: OsTaskType = EXTENDED */
    
        /* Param: OsTaskUseAutostart = 1 */
    
        /* Param: TaskStackSize = 1024 */
    
    

    /* Container: Task4 */
    
        /* Param: OsTaskActivation = 1 */
    
        /* Param: OsTaskPriority = 2 */
    
        /* Param: OsTaskSchedule = FULL */
    
        /* Param: OsTaskType = BASIC */
    
        /* Param: OsTaskUseAutostart = 1 */
    
        /* Param: TaskStackSize = 1024 */
    
    

    /* Container: Task5 */
    
        /* Param: OsTaskActivation = 1 */
    
        /* Param: OsTaskPriority = 4 */
    
        /* Param: OsTaskSchedule = FULL */
    
        /* Param: OsTaskType = BASIC */
    
        /* Param: OsTaskUseAutostart = 1 */
    
        /* Param: TaskStackSize = 1024 */
    
    

    /* Container: Task6 */
    
        /* Param: OsTaskActivation = 100 */
    
        /* Param: OsTaskPriority = 3 */
    
        /* Param: OsTaskSchedule = FULL */
    
        /* Param: OsTaskType = BASIC */
    
        /* Param: OsTaskUseAutostart = 0 */
    
        /* Param: TaskStackSize = 1024 */
    
    

    /* Container: Task7 */
    
        /* Param: OsTaskActivation = 1 */
    
        /* Param: OsTaskPriority = 50 */
    
        /* Param: OsTaskSchedule = FULL */
    
        /* Param: OsTaskType = EXTENDED */
    
        /* Param: OsTaskUseAutostart = 1 */
    
        /* Param: TaskStackSize = 1024 */
    
    

    /* Container: Default_Init_Task */
    
        /* Param: OsTaskActivation = 1 */
    
        /* Param: OsTaskPriority = 100 */
    
        /* Param: OsTaskSchedule = NON */
    
        /* Param: OsTaskType = BASIC */
    
        /* Param: OsTaskUseAutostart = 1 */
    
        /* Param: TaskStackSize = 1024 */
    
    

    /* Container: Default_Init_Task_Core1 */
    
        /* Param: OsTaskActivation = 1 */
    
        /* Param: OsTaskPriority = 100 */
    
        /* Param: OsTaskSchedule = NON */
    
        /* Param: OsTaskType = BASIC */
    
        /* Param: OsTaskUseAutostart = 1 */
    
        /* Param: TaskStackSize = 1024 */
    
    

    /* Container: Task0_Core1 */
    
        /* Param: OsTaskActivation = 1 */
    
        /* Param: OsTaskPriority = 1 */
    
        /* Param: OsTaskSchedule = FULL */
    
        /* Param: OsTaskType = BASIC */
    
        /* Param: OsTaskUseAutostart = 1 */
    
        /* Param: TaskStackSize = 1024 */
    
    

    /* Container: Task8 */
    
        /* Param: OsTaskActivation = 1 */
    
        /* Param: OsTaskPriority = 5 */
    
        /* Param: OsTaskSchedule = FULL */
    
        /* Param: OsTaskType = BASIC */
    
        /* Param: OsTaskUseAutostart = 0 */
    
        /* Param: TaskStackSize = 1024 */
    
    

    /* Container: Task9_Core1 */
    
        /* Param: OsTaskActivation = 1 */
    
        /* Param: OsTaskPriority = 3 */
    
        /* Param: OsTaskSchedule = FULL */
    
        /* Param: OsTaskType = EXTENDED */
    
        /* Param: OsTaskUseAutostart = 1 */
    
        /* Param: TaskStackSize = 1024 */
    
    

    /* Container: Task10_Core1 */
    
        /* Param: OsTaskActivation = 1 */
    
        /* Param: OsTaskPriority = 2 */
    
        /* Param: OsTaskSchedule = FULL */
    
        /* Param: OsTaskType = BASIC */
    
        /* Param: OsTaskUseAutostart = 0 */
    
        /* Param: TaskStackSize = 1024 */
    
    

    /* Container: Task11_Core1 */
    
        /* Param: OsTaskActivation = 1 */
    
        /* Param: OsTaskPriority = 4 */
    
        /* Param: OsTaskSchedule = FULL */
    
        /* Param: OsTaskType = BASIC */
    
        /* Param: OsTaskUseAutostart = 1 */
    
        /* Param: TaskStackSize = 1024 */
    
    

    /* Container: Task12_Core1 */
    
        /* Param: OsTaskActivation = 1 */
    
        /* Param: OsTaskPriority = 5 */
    
        /* Param: OsTaskSchedule = FULL */
    
        /* Param: OsTaskType = EXTENDED */
    
        /* Param: OsTaskUseAutostart = 1 */
    
        /* Param: TaskStackSize = 1024 */
    
    

    /* Container: Task13_Core1 */
    
        /* Param: OsTaskActivation = 1 */
    
        /* Param: OsTaskPriority = 3 */
    
        /* Param: OsTaskSchedule = FULL */
    
        /* Param: OsTaskType = EXTENDED */
    
        /* Param: OsTaskUseAutostart = 1 */
    
        /* Param: TaskStackSize = 1024 */
    
    

    /* Container: Task14_Core1 */
    
        /* Param: OsTaskActivation = 1 */
    
        /* Param: OsTaskPriority = 2 */
    
        /* Param: OsTaskSchedule = FULL */
    
        /* Param: OsTaskType = BASIC */
    
        /* Param: OsTaskUseAutostart = 0 */
    
        /* Param: TaskStackSize = 1024 */
    
    

    /* Container: Task15_Core1 */
    
        /* Param: OsTaskActivation = 1 */
    
        /* Param: OsTaskPriority = 1 */
    
        /* Param: OsTaskSchedule = FULL */
    
        /* Param: OsTaskType = BASIC */
    
        /* Param: OsTaskUseAutostart = 1 */
    
        /* Param: TaskStackSize = 1024 */
    
    

    /* Container: Task16 */
    
        /* Param: OsTaskActivation = 1 */
    
        /* Param: OsTaskPriority = 4 */
    
        /* Param: OsTaskSchedule = FULL */
    
        /* Param: OsTaskType = EXTENDED */
    
        /* Param: OsTaskUseAutostart = 1 */
    
        /* Param: TaskStackSize = 1024 */
    
    

    /* Container: Task17 */
    
        /* Param: OsTaskActivation = 1 */
    
        /* Param: OsTaskPriority = 3 */
    
        /* Param: OsTaskSchedule = FULL */
    
        /* Param: OsTaskType = BASIC */
    
        /* Param: OsTaskUseAutostart = 0 */
    
        /* Param: TaskStackSize = 1024 */
    
    

    /* Container: Task18 */
    
        /* Param: OsTaskActivation = 1 */
    
        /* Param: OsTaskPriority = 1 */
    
        /* Param: OsTaskSchedule = FULL */
    
        /* Param: OsTaskType = BASIC */
    
        /* Param: OsTaskUseAutostart = 1 */
    
        /* Param: TaskStackSize = 1024 */
    
    

    /* Container: Task19 */
    
        /* Param: OsTaskActivation = 1 */
    
        /* Param: OsTaskPriority = 1 */
    
        /* Param: OsTaskSchedule = FULL */
    
        /* Param: OsTaskType = BASIC */
    
        /* Param: OsTaskUseAutostart = 0 */
    
        /* Param: TaskStackSize = 1024 */
    
    

    /* Container: Task20 */
    
        /* Param: OsTaskActivation = 1 */
    
        /* Param: OsTaskPriority = 1 */
    
        /* Param: OsTaskSchedule = FULL */
    
        /* Param: OsTaskType = BASIC */
    
        /* Param: OsTaskUseAutostart = 0 */
    
        /* Param: TaskStackSize = 1024 */
    
    

    /* Container: CPUXATCM */
    
        /* Param: MemoryRegionStartAddress = 0 */
    
        /* Param: MemoryRegionEndAddress = 65535 */
    
        /* Param: MemoryRegionAttribute = RAM */
    
        /* Param: MemoryRegionCopy = ALL */
    
        /* Param: AllMemoryStored = 0 */
    
    

    /* Container: PFLASH0 */
    
        /* Param: MemoryRegionStartAddress = 134217728 */
    
        /* Param: MemoryRegionEndAddress = 137363455 */
    
        /* Param: MemoryRegionAttribute = FLASH */
    
        /* Param: MemoryRegionCopy = NON */
    
        /* Param: AllMemoryStored = 1 */
    
    

    /* Container: CPU0BTCM */
    
        /* Param: MemoryRegionStartAddress = 806354944 */
    
        /* Param: MemoryRegionEndAddress = 806551551 */
    
        /* Param: MemoryRegionAttribute = RAM */
    
        /* Param: MemoryRegionCopy = CORE0 */
    
        /* Param: AllMemoryStored = 0 */
    
    

    /* Container: CPUXCTCM */
    
        /* Param: MemoryRegionStartAddress = 2097152 */
    
        /* Param: MemoryRegionEndAddress = 2162687 */
    
        /* Param: MemoryRegionAttribute = RAM */
    
        /* Param: MemoryRegionCopy = ALL */
    
        /* Param: AllMemoryStored = 0 */
    
    

    /* Container: CPU1BTCM */
    
        /* Param: MemoryRegionStartAddress = 810549248 */
    
        /* Param: MemoryRegionEndAddress = 810745855 */
    
        /* Param: MemoryRegionAttribute = RAM */
    
        /* Param: MemoryRegionCopy = CORE1 */
    
        /* Param: AllMemoryStored = 0 */
    
    

    /* Container: PFLASH1 */
    
        /* Param: MemoryRegionStartAddress = 137363456 */
    
        /* Param: MemoryRegionEndAddress = 140509183 */
    
        /* Param: MemoryRegionAttribute = FLASH */
    
        /* Param: MemoryRegionCopy = NON */
    
        /* Param: AllMemoryStored = 0 */
    
    

    /* Container: GMU_NORMAL */
    
        /* Param: MemoryRegionStartAddress = 268435456 */
    
        /* Param: MemoryRegionEndAddress = 268567551 */
    
        /* Param: MemoryRegionAttribute = RAM */
    
        /* Param: MemoryRegionCopy = CORE0 */
    
        /* Param: AllMemoryStored = 0 */
    
    

    /* Container: GMU_UNCACHED */
    
        /* Param: MemoryRegionStartAddress = 2181170176 */
    
        /* Param: MemoryRegionEndAddress = 2181300223 */
    
        /* Param: MemoryRegionAttribute = RAM */
    
        /* Param: MemoryRegionCopy = CORE0 */
    
        /* Param: AllMemoryStored = 0 */
    
    

    /* Container: INT_VECTOR_TABLE */
    
        /* Param: MemoryBlockSize = 4096 */
    
        /* Param: MemoryBlockAlign = 64 */
    
        /* Param: MemoryRegionType = RO_CODE */
    
        /* Param: MemoryCopyStage = STAGEONE */
    
    
        /* Ref: MemoryRegionRef = &Os_Os_CPUXATCM_Config */
    

    /* Container: PRIVATE_CODE_CLONE */
    
        /* Param: MemoryBlockSize = 61440 */
    
        /* Param: MemoryBlockAlign = 64 */
    
        /* Param: MemoryRegionType = RO_CODE */
    
        /* Param: MemoryCopyStage = STAGEONE */
    
    
        /* Ref: MemoryRegionRef = &Os_Os_CPUXATCM_Config */
    

    /* Container: EX_CODE */
    
        /* Param: MemoryBlockSize = 212992 */
    
        /* Param: MemoryBlockAlign = 64 */
    
        /* Param: MemoryRegionType = RO_CODE */
    
        /* Param: MemoryCopyStage = NON */
    
    
        /* Ref: MemoryRegionRef = &Os_Os_PFLASH0_Config */
    

    /* Container: EX_CONST_DATA */
    
        /* Param: MemoryBlockSize = 32768 */
    
        /* Param: MemoryBlockAlign = 64 */
    
        /* Param: MemoryRegionType = RO_DATA */
    
        /* Param: MemoryCopyStage = NON */
    
    
        /* Ref: MemoryRegionRef = &Os_Os_PFLASH0_Config */
    

    /* Container: EX_CODE_CORE1 */
    
        /* Param: MemoryBlockSize = 3145728 */
    
        /* Param: MemoryBlockAlign = 64 */
    
        /* Param: MemoryRegionType = RO_CODE */
    
        /* Param: MemoryCopyStage = NON */
    
    
        /* Ref: MemoryRegionRef = &Os_Os_PFLASH0_Config */
    

    /* Container: EX_CONST_DATA_CORE1 */
    
        /* Param: MemoryBlockSize = 3145728 */
    
        /* Param: MemoryBlockAlign = 64 */
    
        /* Param: MemoryRegionType = RO_DATA */
    
        /* Param: MemoryCopyStage = NON */
    
    
        /* Ref: MemoryRegionRef = &Os_Os_PFLASH0_Config */
    

    /* Container: PRIVATE_DATA_CLONE */
    
        /* Param: MemoryBlockSize = 32768 */
    
        /* Param: MemoryBlockAlign = 64 */
    
        /* Param: MemoryRegionType = VARIABLE */
    
        /* Param: MemoryCopyStage = STAGEONE */
    
    
        /* Ref: MemoryRegionRef = &Os_Os_CPUXCTCM_Config */
    

    /* Container: PRIVATE_BSS_CLONE */
    
        /* Param: MemoryBlockSize = 32768 */
    
        /* Param: MemoryBlockAlign = 64 */
    
        /* Param: MemoryRegionType = BSS */
    
        /* Param: MemoryCopyStage = STAGEONE */
    
    
        /* Ref: MemoryRegionRef = &Os_Os_CPUXCTCM_Config */
    

    /* Container: PRIVATE_CODE_CORE0 */
    
        /* Param: MemoryBlockSize = 32768 */
    
        /* Param: MemoryBlockAlign = 64 */
    
        /* Param: MemoryRegionType = RO_CODE */
    
        /* Param: MemoryCopyStage = STAGETHREE */
    
    
        /* Ref: MemoryRegionRef = &Os_Os_CPU0BTCM_Config */
    

    /* Container: PRIVATE_DATA_CORE0 */
    
        /* Param: MemoryBlockSize = 32768 */
    
        /* Param: MemoryBlockAlign = 64 */
    
        /* Param: MemoryRegionType = VARIABLE */
    
        /* Param: MemoryCopyStage = STAGETHREE */
    
    
        /* Ref: MemoryRegionRef = &Os_Os_CPU0BTCM_Config */
    

    /* Container: OS_CORE0_STACK */
    
        /* Param: MemoryBlockSize = 98304 */
    
        /* Param: MemoryBlockAlign = 64 */
    
        /* Param: MemoryRegionType = BSS */
    
        /* Param: MemoryCopyStage = STAGETHREE */
    
    
        /* Ref: MemoryRegionRef = &Os_Os_CPU0BTCM_Config */
    

    /* Container: OS_CORE0_TRUST_BSS */
    
        /* Param: MemoryBlockSize = 98304 */
    
        /* Param: MemoryBlockAlign = 64 */
    
        /* Param: MemoryRegionType = BSS */
    
        /* Param: MemoryCopyStage = STAGETHREE */
    
    
        /* Ref: MemoryRegionRef = &Os_Os_CPU0BTCM_Config */
    

    /* Container: OS_CORE0_NON_TRUST_BSS */
    
        /* Param: MemoryBlockSize = 32768 */
    
        /* Param: MemoryBlockAlign = 64 */
    
        /* Param: MemoryRegionType = BSS */
    
        /* Param: MemoryCopyStage = STAGETHREE */
    
    
        /* Ref: MemoryRegionRef = &Os_Os_CPU0BTCM_Config */
    

    /* Container: PRI_BSS_CORE0 */
    
        /* Param: MemoryBlockSize = 32768 */
    
        /* Param: MemoryBlockAlign = 64 */
    
        /* Param: MemoryRegionType = BSS */
    
        /* Param: MemoryCopyStage = STAGETHREE */
    
    
        /* Ref: MemoryRegionRef = &Os_Os_CPU0BTCM_Config */
    

    /* Container: PRIVATE_CODE_CORE1 */
    
        /* Param: MemoryBlockSize = 98304 */
    
        /* Param: MemoryBlockAlign = 64 */
    
        /* Param: MemoryRegionType = RO_CODE */
    
        /* Param: MemoryCopyStage = STAGETHREE */
    
    
        /* Ref: MemoryRegionRef = &Os_Os_CPU1BTCM_Config */
    

    /* Container: PRIVATE_DATA_CORE1 */
    
        /* Param: MemoryBlockSize = 32768 */
    
        /* Param: MemoryBlockAlign = 64 */
    
        /* Param: MemoryRegionType = VARIABLE */
    
        /* Param: MemoryCopyStage = STAGETHREE */
    
    
        /* Ref: MemoryRegionRef = &Os_Os_CPU1BTCM_Config */
    

    /* Container: OS_CORE1_STACK */
    
        /* Param: MemoryBlockSize = 98304 */
    
        /* Param: MemoryBlockAlign = 64 */
    
        /* Param: MemoryRegionType = BSS */
    
        /* Param: MemoryCopyStage = STAGETHREE */
    
    
        /* Ref: MemoryRegionRef = &Os_Os_CPU1BTCM_Config */
    

    /* Container: OS_CORE1_TRUST_BSS */
    
        /* Param: MemoryBlockSize = 98304 */
    
        /* Param: MemoryBlockAlign = 64 */
    
        /* Param: MemoryRegionType = BSS */
    
        /* Param: MemoryCopyStage = STAGETHREE */
    
    
        /* Ref: MemoryRegionRef = &Os_Os_CPU1BTCM_Config */
    

    /* Container: OS_CORE1_NON_TRUST_BSS */
    
        /* Param: MemoryBlockSize = 32768 */
    
        /* Param: MemoryBlockAlign = 64 */
    
        /* Param: MemoryRegionType = BSS */
    
        /* Param: MemoryCopyStage = STAGETHREE */
    
    
        /* Ref: MemoryRegionRef = &Os_Os_CPU1BTCM_Config */
    

    /* Container: PRIVATE_BSS_CORE1 */
    
        /* Param: MemoryBlockSize = 36864 */
    
        /* Param: MemoryBlockAlign = 64 */
    
        /* Param: MemoryRegionType = BSS */
    
        /* Param: MemoryCopyStage = STAGETHREE */
    
    
        /* Ref: MemoryRegionRef = &Os_Os_CPU1BTCM_Config */
    

    /* Container: UNDEFINE_RAM_DATA */
    
        /* Param: MemoryBlockSize = 65536 */
    
        /* Param: MemoryBlockAlign = 64 */
    
        /* Param: MemoryRegionType = VARIABLE */
    
        /* Param: MemoryCopyStage = STAGETWO */
    
    
        /* Ref: MemoryRegionRef = &Os_Os_GMU_NORMAL_Config */
    

    /* Container: UNDEFINE_RAM_BSS */
    
        /* Param: MemoryBlockSize = 65536 */
    
        /* Param: MemoryBlockAlign = 64 */
    
        /* Param: MemoryRegionType = BSS */
    
        /* Param: MemoryCopyStage = STAGETWO */
    
    
        /* Ref: MemoryRegionRef = &Os_Os_GMU_NORMAL_Config */
    

    /* Container: UNCLEAR_RAM_BSS */
    
        /* Param: MemoryBlockSize = 1024 */
    
        /* Param: MemoryBlockAlign = 64 */
    
        /* Param: MemoryRegionType = BSS */
    
        /* Param: MemoryCopyStage = STAGEUNCLEAR */
    
    
        /* Ref: MemoryRegionRef = &Os_Os_GMU_NORMAL_Config */
    

    /* Container: GLOBAL_UNCACHED_DATA */
    
        /* Param: MemoryBlockSize = 64512 */
    
        /* Param: MemoryBlockAlign = 64 */
    
        /* Param: MemoryRegionType = VARIABLE */
    
        /* Param: MemoryCopyStage = STAGETWO */
    
    
        /* Ref: MemoryRegionRef = &Os_Os_GMU_UNCACHED_Config */
    

    /* Container: GLOBAL_UNCACHED_BSS */
    
        /* Param: MemoryBlockSize = 65536 */
    
        /* Param: MemoryBlockAlign = 64 */
    
        /* Param: MemoryRegionType = BSS */
    
        /* Param: MemoryCopyStage = STAGETWO */
    
    
        /* Ref: MemoryRegionRef = &Os_Os_GMU_UNCACHED_Config */
    

    /* Container: init_default_vector */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 1 */
    
    

    /* Container: IRQ_init_vector */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: private_clone_code */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: user_code */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 1 */
    
    

    /* Container: exceptionHandler */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: ROCODE */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_text_qm */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_text_callout_qm */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: RODATA */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_cfg_qm_bool */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_cfg_qm_unspecified */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_cfg_qm_8 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_cfg_qm_16 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_cfg_qm_32 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_qm_bool */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_qm_8 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_qm_16 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_qm_32 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_qm_unspecified */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_cfg_qm_bool_core0 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_cfg_qm_8_core0 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_cfg_qm_16_core0 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_cfg_qm_32_core0 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_cfg_qm_unspecified_core0 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_qm_bool_core0 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_qm_8_core0 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_qm_16_core0 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_qm_32_core0 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_qm_unspecified_core0 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_text_qm_core1 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_text_callout_qm_core1 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_cfg_qm_bool_core1 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_cfg_qm_8_core1 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_cfg_qm_16_core1 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_cfg_qm_32_core1 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_cfg_qm_unspecified_core1 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_qm_bool_core1 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_qm_8_core1 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_qm_16_core1 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_qm_32_core1 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_const_qm_unspecified_core1 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: private_Core0_code */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_ramcode_qm_core0 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_text_qm_core0 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_text_fast_qm_core0 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_text_callout_qm_core0 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: private_Core0_data */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_data_qm_bool_core0 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_data_qm_8_core0 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_data_qm_16_core0 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_data_qm_32_core0 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_data_qm_unspecified_core0 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_stack_qm_32_core0 */
    
        /* Param: MemorySectionAlign = 64 */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_trust_qm_32_core0 */
    
        /* Param: MemorySectionAlign = 64 */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_nontrust_qm_32_core0 */
    
        /* Param: MemorySectionAlign = 64 */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: private_Core0_bss */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: private_bss_Core0 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_bss_qm_bool_core0 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_bss_qm_8_core0 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_bss_qm_16_core0 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_bss_qm_32_core0 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_bss_qm_unspecified_core0 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: exceptionRegInfo */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: private_clone_data */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: private_clone_bss */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: private_Core1_code */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_ramcode_qm_core1 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_text_fast_qm_core1 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: private_Core1_data */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_data_qm_bool_core1 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_data_qm_8_core1 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_data_qm_16_core1 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_data_qm_32_core1 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_data_qm_unspecified_core1 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_stack_qm_32_core1 */
    
        /* Param: MemorySectionAlign = 64 */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_trust_qm_32_core1 */
    
        /* Param: MemorySectionAlign = 64 */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_nontrust_qm_32_core1 */
    
        /* Param: MemorySectionAlign = 64 */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: private_Core1_bss */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_bss_qm_bool_core1 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_bss_qm_8_core1 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_bss_qm_16_core1 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_bss_qm_32_core1 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_bss_qm_unspecified_core1 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: RWDATA */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: global_data */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_data */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_data_qm_bool */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_data_qm_8 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_data_qm_16 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_data_qm_32 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_data_qm_unspecified */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: BSS */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: global_bss */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_bss_qm_bool */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_bss_qm_8 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_bss_qm_16 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_bss_qm_32 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_bss_qm_unspecified */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_cleared */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_bss */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: unclear_bss */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_no_init_qm_bool */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_no_init_qm_8 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_no_init_qm_16 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_no_init_qm_32 */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_no_init_qm_unspecified */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: uncached_data */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_data_qm_bool_uncached */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_data_qm_8_uncached */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_data_qm_16_uncached */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_data_qm_32_uncached */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_data_qm_unspecified_uncached */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: uncached_bss */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_bss_qm_bool_uncached */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_bss_qm_8_uncached */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_bss_qm_16_uncached */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_bss_qm_32_uncached */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: os_bss_qm_unspecified_uncached */
    
        /* Param: MemorySectionAlign = NON */
    
        /* Param: MemorySectionFirst = 0 */
    
    

    /* Container: SystemModeStack */
    
    

    /* Container: CONFIG_DATA_QM_GLOBAL_BOOLEAN */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_cfg_qm_bool_Config */
    

    /* Container: CONFIG_DATA_QM_GLOBAL_8 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_cfg_qm_8_Config */
    

    /* Container: CONFIG_DATA_QM_GLOBAL_16 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_cfg_qm_16_Config */
    

    /* Container: CONFIG_DATA_QM_GLOBAL_32 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_cfg_qm_32_Config */
    

    /* Container: CONFIG_DATA_QM_GLOBAL_UNSPECIFIED */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_cfg_qm_unspecified_Config */
    

    /* Container: CONST_QM_GLOBAL_BOOLEAN */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_qm_bool_Config */
    

    /* Container: CONST_QM_GLOBAL_8 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_qm_8_Config */
    

    /* Container: CONST_QM_GLOBAL_16 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_qm_16_Config */
    

    /* Container: CONST_QM_GLOBAL_32 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_qm_32_Config */
    

    /* Container: CONST_QM_GLOBAL_UNSPECIFIED */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_qm_unspecified_Config */
    

    /* Container: VAR_NO_INIT_QM_GLOBAL_BOOLEAN */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_no_init_qm_bool_Config */
    

    /* Container: VAR_NO_INIT_QM_GLOBAL_8 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_no_init_qm_8_Config */
    

    /* Container: VAR_NO_INIT_QM_GLOBAL_16 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_no_init_qm_16_Config */
    

    /* Container: VAR_NO_INIT_QM_GLOBAL_32 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_no_init_qm_32_Config */
    

    /* Container: VAR_NO_INIT_QM_GLOBAL_UNSPECIFIED */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_no_init_qm_unspecified_Config */
    

    /* Container: VAR_INIT_QM_GLOBAL_BOOLEAN */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_data_qm_bool_Config */
    

    /* Container: SEC_VAR_INIT_QM_GLOBAL_8 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_data_qm_8_Config */
    

    /* Container: VAR_INIT_QM_GLOBAL_16 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_data_qm_16_Config */
    

    /* Container: VAR_INIT_QM_GLOBAL_32 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_data_qm_32_Config */
    

    /* Container: VAR_INIT_QM_GLOBAL_UNSPECIFIED */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_data_qm_unspecified_Config */
    

    /* Container: VAR_CLEARED_QM_GLOBAL_BOOLEAN */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_bss_qm_bool_Config */
    

    /* Container: VAR_CLEARED_QM_GLOBAL_8 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_bss_qm_8_Config */
    

    /* Container: VAR_CLEARED_QM_GLOBAL_16 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_bss_qm_16_Config */
    

    /* Container: VAR_CLEARED_QM_GLOBAL_32 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_bss_qm_32_Config */
    

    /* Container: VAR_CLEARED_QM_GLOBAL_UNSPECIFIED */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_bss_qm_unspecified_Config */
    

    /* Container: VAR_INIT_QM_GLOBAL_BOOLEAN_NO_CACHEABLE */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_data_qm_bool_uncached_Config */
    

    /* Container: VAR_INIT_QM_GLOBAL_8_NO_CACHEABLE */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_data_qm_8_uncached_Config */
    

    /* Container: VAR_INIT_QM_GLOBAL_16_NO_CACHEABLE */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_data_qm_16_uncached_Config */
    

    /* Container: VAR_INIT_QM_GLOBAL_32_NO_CACHEABLE */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_data_qm_32_uncached_Config */
    

    /* Container: VAR_INIT_QM_GLOBAL_UNSPECIFIED_NO_CACHEABLE */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_data_qm_unspecified_uncached_Config */
    

    /* Container: VAR_CLEARED_QM_GLOBAL_BOOLEAN_NO_CACHEABLE */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_bss_qm_bool_uncached_Config */
    

    /* Container: VAR_CLEARED_QM_GLOBAL_8_NO_CACHEABLE */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_bss_qm_8_uncached_Config */
    

    /* Container: VAR_CLEARED_QM_GLOBAL_16_NO_CACHEABLE */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_bss_qm_16_uncached_Config */
    

    /* Container: VAR_CLEARED_QM_GLOBAL_32_NO_CACHEABLE */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_bss_qm_32_uncached_Config */
    

    /* Container: VAR_CLEARED_QM_GLOBAL_UNSPECIFIED_NO_CACHEABLE */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_bss_qm_unspecified_uncached_Config */
    

    /* Container: CODE_QM_GLOBAL */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_text_qm_Config */
    

    /* Container: CALLOUT_CODE_QM_GLOBAL */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_text_callout_qm_Config */
    

    /* Container: CONFIG_DATA_QM_CORE0_BOOLEAN */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_cfg_qm_bool_core0_Config */
    

    /* Container: CONFIG_DATA_QM_CORE0_8 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_cfg_qm_8_core0_Config */
    

    /* Container: CONFIG_DATA_QM_CORE0_16 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_cfg_qm_16_core0_Config */
    

    /* Container: CONFIG_DATA_QM_CORE0_32 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_cfg_qm_32_core0_Config */
    

    /* Container: CONFIG_DATA_QM_CORE0_UNSPECIFIED */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_cfg_qm_unspecified_core0_Config */
    

    /* Container: CONST_QM_CORE0_BOOLEAN */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_qm_bool_core0_Config */
    

    /* Container: CONST_QM_CORE0_8 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_qm_8_core0_Config */
    

    /* Container: CONST_QM_CORE0_16 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_qm_16_core0_Config */
    

    /* Container: CONST_QM_CORE0_32 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_qm_32_core0_Config */
    

    /* Container: CONST_QM_CORE0_UNSPECIFIED */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_qm_unspecified_core0_Config */
    

    /* Container: VAR_INIT_QM_CORE0_BOOLEAN */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_data_qm_bool_core0_Config */
    

    /* Container: VAR_INIT_QM_CORE0_8 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_data_qm_8_core0_Config */
    

    /* Container: VAR_INIT_QM_CORE0_16 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_data_qm_16_core0_Config */
    

    /* Container: VAR_INIT_QM_CORE0_32 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_data_qm_32_core0_Config */
    

    /* Container: VAR_INIT_QM_CORE0_UNSPECIFIED */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_data_qm_unspecified_core0_Config */
    

    /* Container: VAR_CLEARED_QM_CORE0_BOOLEAN */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_bss_qm_bool_core0_Config */
    

    /* Container: VAR_CLEARED_QM_CORE0_8 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_bss_qm_8_core0_Config */
    

    /* Container: VAR_CLEARED_QM_CORE0_16 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_bss_qm_16_core0_Config */
    

    /* Container: VAR_CLEARED_QM_CORE0_32 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_bss_qm_32_core0_Config */
    

    /* Container: VAR_CLEARED_QM_CORE0_UNSPECIFIED */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_bss_qm_unspecified_core0_Config */
    

    /* Container: TRUSTED_VAR_CLEARED_QM_CORE0_32 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_trust_qm_32_core0_Config */
    

    /* Container: NONTRUSTED_VAR_CLEARED_QM_CORE0_32 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_nontrust_qm_32_core0_Config */
    

    /* Container: CODE_QM_CORE0 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_text_qm_core0_Config */
    

    /* Container: RAMCODE_QM_CORE0 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_ramcode_qm_core0_Config */
    

    /* Container: CALLOUT_CODE_QM_CORE0 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_text_callout_qm_core0_Config */
    

    /* Container: CODE_FAST_QM_CORE0 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_text_fast_qm_core0_Config */
    

    /* Container: CONFIG_DATA_QM_CORE1_BOOLEAN */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_cfg_qm_bool_core1_Config */
    

    /* Container: CONFIG_DATA_QM_CORE1_8 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_cfg_qm_8_core1_Config */
    

    /* Container: CONFIG_DATA_QM_CORE1_16 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_cfg_qm_16_core1_Config */
    

    /* Container: CONFIG_DATA_QM_CORE1_32 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_cfg_qm_32_core1_Config */
    

    /* Container: CONFIG_DATA_QM_CORE1_UNSPECIFIED */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_cfg_qm_unspecified_core1_Config */
    

    /* Container: CONST_QM_CORE1_BOOLEAN */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_qm_bool_core1_Config */
    

    /* Container: CONST_QM_CORE1_8 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_qm_8_core1_Config */
    

    /* Container: CONST_QM_CORE1_16 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_qm_16_core1_Config */
    

    /* Container: CONST_QM_CORE1_32 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_qm_32_core1_Config */
    

    /* Container: CONST_QM_CORE1_UNSPECIFIED */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_const_qm_unspecified_core1_Config */
    

    /* Container: VAR_INIT_QM_CORE1_BOOLEAN */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_data_qm_bool_core1_Config */
    

    /* Container: VAR_INIT_QM_CORE1_8 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_data_qm_8_core1_Config */
    

    /* Container: VAR_INIT_QM_CORE1_16 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_data_qm_16_core1_Config */
    

    /* Container: VAR_INIT_QM_CORE1_32 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_data_qm_32_core1_Config */
    

    /* Container: VAR_INIT_QM_CORE1_UNSPECIFIED */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_data_qm_unspecified_core1_Config */
    

    /* Container: VAR_CLEARED_QM_CORE1_BOOLEAN */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_bss_qm_bool_core1_Config */
    

    /* Container: VAR_CLEARED_QM_CORE1_8 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_bss_qm_8_core1_Config */
    

    /* Container: VAR_CLEARED_QM_CORE1_16 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_bss_qm_16_core1_Config */
    

    /* Container: VAR_CLEARED_QM_CORE1_32 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_bss_qm_32_core1_Config */
    

    /* Container: VAR_CLEARED_QM_CORE1_UNSPECIFIED */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_bss_qm_unspecified_core1_Config */
    

    /* Container: TRUSTED_VAR_CLEARED_QM_CORE1_32 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_trust_qm_32_core1_Config */
    

    /* Container: NONTRUSTED_VAR_CLEARED_QM_CORE1_32 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_nontrust_qm_32_core1_Config */
    

    /* Container: CODE_QM_CORE1 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_text_qm_core1_Config */
    

    /* Container: RAMCODE_QM_CORE1 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_ramcode_qm_core1_Config */
    

    /* Container: CALLOUT_CODE_QM_CORE1 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_text_callout_qm_core1_Config */
    

    /* Container: CODE_FAST_QM_CORE1 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_text_fast_qm_core1_Config */
    

    /* Container: VAR_CLEARED_QM_PRIVATE_CLONE */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_private_clone_bss_Config */
    

    /* Container: VAR_INIT_QM_PRIVATE_CLONE */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_private_clone_data_Config */
    

    /* Container: CODE_QM_PRIVATE_CLONE */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_private_clone_code_Config */
    

    /* Container: STACKCFG_QM_CORE0_32 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_stack_qm_32_core0_Config */
    

    /* Container: STACKCFG_QM_CORE1_32 */
    
    
        /* Ref: MemorySectionMatch = &Os_Os_os_stack_qm_32_core1_Config */
    

};

#define OS_STOP_SEC_CONFIG_DATA_POSTBUILD
#include "Os_MemMap.h"
