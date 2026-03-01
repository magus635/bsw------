/**
 * @file Os_Cfg.h
 * @brief Pre-Compile Configuration for Os module
 * @note Auto-generated - PRE-COMPILE parameters only
 */

#ifndef OS_CFG_H
#define OS_CFG_H

#include "Std_Types.h"

/* --- Pre-Compile Parameters --- */

#define OS_OSCOREIDMAPPINGCONFIG_0_OSPHYSICALCOREID    (0) /* OsPhysicalCoreId */

#define OS_OSCOREIDMAPPINGCONFIG_0_OSCOREHOOKSTACKCONFIG_OSERRORHOOKSIZE    (1024) /* OsErrorHookSize */

#define OS_OSCOREIDMAPPINGCONFIG_0_OSCOREHOOKSTACKCONFIG_OSPROTECTIONHOOKSIZE    (1024) /* OsProtectionHookSize */

#define OS_OSCOREIDMAPPINGCONFIG_0_OSCOREHOOKSTACKCONFIG_OSSHUTDOWNHOOKSIZE    (1024) /* OsShutdownHookSize */

#define OS_OSCOREIDMAPPINGCONFIG_0_OSCOREHOOKSTACKCONFIG_OSSTARTUPHOOKSIZE    (1024) /* OsStartupHookSize */

#define OS_OSCOREIDMAPPINGCONFIG_1_OSPHYSICALCOREID    (1) /* OsPhysicalCoreId */

#define OS_OSCOREIDMAPPINGCONFIG_1_OSCOREHOOKSTACKCONFIG_OSERRORHOOKSIZE    (1024) /* OsErrorHookSize */

#define OS_OSCOREIDMAPPINGCONFIG_1_OSCOREHOOKSTACKCONFIG_OSPROTECTIONHOOKSIZE    (1024) /* OsProtectionHookSize */

#define OS_OSCOREIDMAPPINGCONFIG_1_OSCOREHOOKSTACKCONFIG_OSSHUTDOWNHOOKSIZE    (1024) /* OsShutdownHookSize */

#define OS_OSCOREIDMAPPINGCONFIG_1_OSCOREHOOKSTACKCONFIG_OSSTARTUPHOOKSIZE    (1024) /* OsStartupHookSize */

#define OS_OSEVENT_0_OSEVENTMASK    (1) /* OsEventMask */

#define OS_OSEVENT_1_OSEVENTMASK    (2) /* OsEventMask */

#define OS_OSEVENT_2_OSEVENTMASK    (4) /* OsEventMask */

#define OS_OSEVENT_3_OSEVENTMASK    (8) /* OsEventMask */

#define OS_OSEVENT_4_OSEVENTMASK    (16) /* OsEventMask */

#define OS_OSISR_BASETIMER1_OSISRTIMINGPROTECTION_0_OSISRALLINTERRUPTLOCKBUDGET    (0.004f) /* OsIsrAllInterruptLockBudget */

#define OS_OSISR_BASETIMER1_OSISRTIMINGPROTECTION_0_OSISREXECUTIONBUDGET    (0.008f) /* OsIsrExecutionBudget */

#define OS_OSISR_BASETIMER1_OSISRTIMINGPROTECTION_0_OSISROSINTERRUPTLOCKBUDGET    (0.006f) /* OsIsrOsInterruptLockBudget */

#define OS_OSISR_BASETIMER1_OSISRTIMINGPROTECTION_0_OSISRTIMEFRAME    (0.0026f) /* OsIsrTimeFrame */

#define OS_OSOS_OSNUMBEROFCORES    (2) /* OsNumberOfCores */

#define OS_OSSCHEDULETABLE_0_OSSCHEDULETBLEXPLICITPRECISION    (0) /* OsScheduleTblExplicitPrecision */

#define OS_OSSCHEDULETABLE_0_OSSCHEDULETABLEAUTOSTART_0_OSSCHEDULETABLESTARTVALUE    (1) /* OsScheduleTableStartValue */

#define OS_OSSCHEDULETABLE_1_OSSCHEDULETBLEXPLICITPRECISION    (0) /* OsScheduleTblExplicitPrecision */

#define OS_OSSCHEDULETABLE_1_OSSCHEDULETABLEAUTOSTART_0_OSSCHEDULETABLESTARTVALUE    (10) /* OsScheduleTableStartValue */


/* --- Pre-Compile References --- */

/* Reference from CALLOUT_CODE_QM_CORE0 to /Os/Os/os_text_callout_qm_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CALLOUT_CODE_QM_CORE1 to /Os/Os/os_text_callout_qm_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CALLOUT_CODE_QM_GLOBAL to /Os/Os/os_text_callout_qm */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CODE_FAST_QM_CORE0 to /Os/Os/os_text_fast_qm_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CODE_FAST_QM_CORE1 to /Os/Os/os_text_fast_qm_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CODE_QM_CORE0 to /Os/Os/os_text_qm_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CODE_QM_CORE1 to /Os/Os/os_text_qm_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CODE_QM_GLOBAL to /Os/Os/os_text_qm */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CODE_QM_PRIVATE_CLONE to /Os/Os/private_clone_code */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONFIG_DATA_QM_CORE0_16 to /Os/Os/os_const_cfg_qm_16_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONFIG_DATA_QM_CORE0_32 to /Os/Os/os_const_cfg_qm_32_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONFIG_DATA_QM_CORE0_8 to /Os/Os/os_const_cfg_qm_8_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONFIG_DATA_QM_CORE0_BOOLEAN to /Os/Os/os_const_cfg_qm_bool_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONFIG_DATA_QM_CORE0_UNSPECIFIED to /Os/Os/os_const_cfg_qm_unspecified_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONFIG_DATA_QM_CORE1_16 to /Os/Os/os_const_cfg_qm_16_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONFIG_DATA_QM_CORE1_32 to /Os/Os/os_const_cfg_qm_32_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONFIG_DATA_QM_CORE1_8 to /Os/Os/os_const_cfg_qm_8_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONFIG_DATA_QM_CORE1_BOOLEAN to /Os/Os/os_const_cfg_qm_bool_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONFIG_DATA_QM_CORE1_UNSPECIFIED to /Os/Os/os_const_cfg_qm_unspecified_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONFIG_DATA_QM_GLOBAL_16 to /Os/Os/os_const_cfg_qm_16 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONFIG_DATA_QM_GLOBAL_32 to /Os/Os/os_const_cfg_qm_32 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONFIG_DATA_QM_GLOBAL_8 to /Os/Os/os_const_cfg_qm_8 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONFIG_DATA_QM_GLOBAL_BOOLEAN to /Os/Os/os_const_cfg_qm_bool */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONFIG_DATA_QM_GLOBAL_UNSPECIFIED to /Os/Os/os_const_cfg_qm_unspecified */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONST_QM_CORE0_16 to /Os/Os/os_const_qm_16_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONST_QM_CORE0_32 to /Os/Os/os_const_qm_32_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONST_QM_CORE0_8 to /Os/Os/os_const_qm_8_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONST_QM_CORE0_BOOLEAN to /Os/Os/os_const_qm_bool_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONST_QM_CORE0_UNSPECIFIED to /Os/Os/os_const_qm_unspecified_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONST_QM_CORE1_16 to /Os/Os/os_const_qm_16_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONST_QM_CORE1_32 to /Os/Os/os_const_qm_32_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONST_QM_CORE1_8 to /Os/Os/os_const_qm_8_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONST_QM_CORE1_BOOLEAN to /Os/Os/os_const_qm_bool_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONST_QM_CORE1_UNSPECIFIED to /Os/Os/os_const_qm_unspecified_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONST_QM_GLOBAL_16 to /Os/Os/os_const_qm_16 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONST_QM_GLOBAL_32 to /Os/Os/os_const_qm_32 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONST_QM_GLOBAL_8 to /Os/Os/os_const_qm_8 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONST_QM_GLOBAL_BOOLEAN to /Os/Os/os_const_qm_bool */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from CONST_QM_GLOBAL_UNSPECIFIED to /Os/Os/os_const_qm_unspecified */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from EX_CODE to /Os/Os/PFLASH0 */
#define OS_MEMORYREGIONREF_REF    

/* Reference from EX_CODE_CORE1 to /Os/Os/PFLASH0 */
#define OS_MEMORYREGIONREF_REF    

/* Reference from EX_CONST_DATA to /Os/Os/PFLASH0 */
#define OS_MEMORYREGIONREF_REF    

/* Reference from EX_CONST_DATA_CORE1 to /Os/Os/PFLASH0 */
#define OS_MEMORYREGIONREF_REF    

/* Reference from GLOBAL_UNCACHED_BSS to /Os/Os/GMU_UNCACHED */
#define OS_MEMORYREGIONREF_REF    

/* Reference from GLOBAL_UNCACHED_DATA to /Os/Os/GMU_UNCACHED */
#define OS_MEMORYREGIONREF_REF    

/* Reference from INT_VECTOR_TABLE to /Os/Os/CPUXATCM */
#define OS_MEMORYREGIONREF_REF    

/* Reference from NONTRUSTED_VAR_CLEARED_QM_CORE0_32 to /Os/Os/os_nontrust_qm_32_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from NONTRUSTED_VAR_CLEARED_QM_CORE1_32 to /Os/Os/os_nontrust_qm_32_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from OS_CORE0_NON_TRUST_BSS to /Os/Os/CPU0BTCM */
#define OS_MEMORYREGIONREF_REF    

/* Reference from OS_CORE0_STACK to /Os/Os/CPU0BTCM */
#define OS_MEMORYREGIONREF_REF    

/* Reference from OS_CORE0_TRUST_BSS to /Os/Os/CPU0BTCM */
#define OS_MEMORYREGIONREF_REF    

/* Reference from OS_CORE1_NON_TRUST_BSS to /Os/Os/CPU1BTCM */
#define OS_MEMORYREGIONREF_REF    

/* Reference from OS_CORE1_STACK to /Os/Os/CPU1BTCM */
#define OS_MEMORYREGIONREF_REF    

/* Reference from OS_CORE1_TRUST_BSS to /Os/Os/CPU1BTCM */
#define OS_MEMORYREGIONREF_REF    

/* Reference from OsAlarm_0 to /Os/Os/OsCounter_Software */
#define OS_OSALARMCOUNTERREF_REF    

/* Reference from OsAlarm_0_OsAlarmAction_OsAlarmActivateTask to /Os/Os/Task20 */
#define OS_OSALARMACTIVATETASKREF_REF    

/* Reference from OsAlarm_1 to /Os/Os/OsCounter_SystemTick */
#define OS_OSALARMCOUNTERREF_REF    

/* Reference from OsAlarm_1_OsAlarmAction_OsAlarmActivateTask to /Os/Os/Task5 */
#define OS_OSALARMACTIVATETASKREF_REF    

/* Reference from OsAlarm_2 to /Os/Os/OsCounter_SystemTick */
#define OS_OSALARMCOUNTERREF_REF    

/* Reference from OsAlarm_2_OsAlarmAction_OsAlarmActivateTask to /Os/Os/Task1 */
#define OS_OSALARMACTIVATETASKREF_REF    

/* Reference from OsAlarm_3 to /Os/Os/OsCounter_Software2 */
#define OS_OSALARMCOUNTERREF_REF    

/* Reference from OsAlarm_3_OsAlarmAction_OsAlarmActivateTask to /Os/Os/Task4 */
#define OS_OSALARMACTIVATETASKREF_REF    

/* Reference from OsAlarm_4 to /Os/Os/OsCounter_Pit */
#define OS_OSALARMCOUNTERREF_REF    

/* Reference from OsAlarm_4_OsAlarmAction_OsAlarmSetEvent to /Os/Os/OsEvent_1 */
#define OS_OSALARMSETEVENTREF_REF    

/* Reference from OsAlarm_4_OsAlarmAction_OsAlarmSetEvent to /Os/Os/Task7 */
#define OS_OSALARMSETEVENTTASKREF_REF    

/* Reference from OsAlarm_5 to /Os/Os/OsCounter_SystemTick_Core1 */
#define OS_OSALARMCOUNTERREF_REF    

/* Reference from OsAlarm_5_OsAlarmAction_OsAlarmActivateTask to /Os/Os/Task0_Core1 */
#define OS_OSALARMACTIVATETASKREF_REF    

/* Reference from OsAlarm_6 to /Os/Os/OsCounter_Software2 */
#define OS_OSALARMCOUNTERREF_REF    

/* Reference from OsAlarm_6_OsAlarmAction_OsAlarmActivateTask to /Os/Os/Task19 */
#define OS_OSALARMACTIVATETASKREF_REF    

/* Reference from OsAlarm_7 to /Os/Os/OsCounter_Software2 */
#define OS_OSALARMCOUNTERREF_REF    

/* Reference from OsAlarm_7_OsAlarmAction_OsAlarmActivateTask to /Os/Os/Task20 */
#define OS_OSALARMACTIVATETASKREF_REF    

/* Reference from OsAlarm_8 to /Os/Os/OsCounter_Software_Core1 */
#define OS_OSALARMCOUNTERREF_REF    

/* Reference from OsAlarm_8_OsAlarmAction_OsAlarmActivateTask to /Os/Os/Task11_Core1 */
#define OS_OSALARMACTIVATETASKREF_REF    

/* Reference from OsAlarm_9 to /Os/Os/OsCounter_Software_Core1 */
#define OS_OSALARMCOUNTERREF_REF    

/* Reference from OsAlarm_9_OsAlarmAction_OsAlarmSetEvent to /Os/Os/OsEvent_1 */
#define OS_OSALARMSETEVENTREF_REF    

/* Reference from OsAlarm_9_OsAlarmAction_OsAlarmSetEvent to /Os/Os/Task12_Core1 */
#define OS_OSALARMSETEVENTTASKREF_REF    

/* Reference from OsApplication_0 to /Os/Os/OsCoreIdMappingConfig_0 */
#define OS_OSAPPLICATIONCOREREF_REF    

/* Reference from OsApplication_1 to /Os/Os/OsCoreIdMappingConfig_0 */
#define OS_OSAPPLICATIONCOREREF_REF    

/* Reference from OsApplication_2 to /Os/Os/OsCoreIdMappingConfig_0 */
#define OS_OSAPPLICATIONCOREREF_REF    

/* Reference from OsApplication_3 to /Os/Os/OsCoreIdMappingConfig_1 */
#define OS_OSAPPLICATIONCOREREF_REF    

/* Reference from OsCoreIdMappingConfig_0 to /EcuC/EcuC/EcucHardware/EcucCoreDefinition_0 */
#define OS_OSCOREID_REF    

/* Reference from OsCoreIdMappingConfig_0 to /Os/Os/OsApplication_0 */
#define OS_OSKERNELAPPLICATION_REF    

/* Reference from OsCoreIdMappingConfig_0 to /Os/Os/OsCounter_Hrt */
#define OS_OSTPCOUNTERREF_REF    

/* Reference from OsCoreIdMappingConfig_0_OsCoreServiceCall_0 to /Os/Os/OsCoreIdMappingConfig_1 */
#define OS_OSRECEIVERCORE_REF    

/* Reference from OsCoreIdMappingConfig_1 to /EcuC/EcuC/EcucHardware/EcucCoreDefinition_1 */
#define OS_OSCOREID_REF    

/* Reference from OsCoreIdMappingConfig_1 to /Os/Os/OsApplication_3 */
#define OS_OSKERNELAPPLICATION_REF    

/* Reference from OsCoreIdMappingConfig_1 to /Os/Os/OsCounter_Hrt_Core1 */
#define OS_OSTPCOUNTERREF_REF    

/* Reference from OsCoreIdMappingConfig_1_OsCoreServiceCall_0 to /Os/Os/OsCoreIdMappingConfig_0 */
#define OS_OSRECEIVERCORE_REF    

/* Reference from OsCounter_Hrt to /Os/Os/Os_IsrCfg_VirtualTimer */
#define OS_OSTIMERTYPEISRREF_REF    

/* Reference from OsCounter_Hrt_Core1 to /Os/Os/OsIsr_IsrCfg_VirtualTimer_Core1 */
#define OS_OSTIMERTYPEISRREF_REF    

/* Reference from OsCounter_Pit to /Os/Os/Os_IsrCfg_BaseTimer0 */
#define OS_OSTIMERTYPEISRREF_REF    

/* Reference from OsCounter_Software to /Os/Os/Os_IsrCfg_SystemTimer */
#define OS_OSTIMERTYPEISRREF_REF    

/* Reference from OsCounter_SystemTick to /Os/Os/Os_IsrCfg_SystemTimer */
#define OS_OSTIMERTYPEISRREF_REF    

/* Reference from OsCounter_SystemTick_Core1 to /Os/Os/Os_IsrCfg_SystemTimer_Core1 */
#define OS_OSTIMERTYPEISRREF_REF    

/* Reference from OsResource_0 to /Os/Os/OsCoreIdMappingConfig_0 */
#define OS_OSRESOURCECOREREF_REF    

/* Reference from OsResource_1 to /Os/Os/OsCoreIdMappingConfig_0 */
#define OS_OSRESOURCECOREREF_REF    

/* Reference from OsResource_2 to /Os/Os/OsCoreIdMappingConfig_1 */
#define OS_OSRESOURCECOREREF_REF    

/* Reference from OsScheduleTable_0 to /Os/Os/OsCounter_SystemTick */
#define OS_OSSCHEDULETABLECOUNTERREF_REF    

/* Reference from OsScheduleTable_0_OsScheduleTableExpiryPoint_0_OsScheduleTableEventSetting_0 to /Os/Os/OsEvent_0 */
#define OS_OSSCHEDULETABLESETEVENTREF_REF    

/* Reference from OsScheduleTable_0_OsScheduleTableExpiryPoint_0_OsScheduleTableEventSetting_0 to /Os/Os/Task3 */
#define OS_OSSCHEDULETABLESETEVENTTASKREF_REF    

/* Reference from OsScheduleTable_0_OsScheduleTableExpiryPoint_0_OsScheduleTableTaskActivation_0 to /Os/Os/Task2 */
#define OS_OSSCHEDULETABLEACTIVATETASKREF_REF    

/* Reference from OsScheduleTable_1 to /Os/Os/OsCounter_SystemTick_Core1 */
#define OS_OSSCHEDULETABLECOUNTERREF_REF    

/* Reference from OsScheduleTable_1_OsScheduleTableExpiryPoint_0_OsScheduleTableTaskActivation_0 to /Os/Os/Task10_Core1 */
#define OS_OSSCHEDULETABLEACTIVATETASKREF_REF    

/* Reference from OsScheduleTable_1_OsScheduleTableExpiryPoint_1_OsScheduleTableEventSetting_0 to /Os/Os/OsEvent_2 */
#define OS_OSSCHEDULETABLESETEVENTREF_REF    

/* Reference from OsScheduleTable_1_OsScheduleTableExpiryPoint_1_OsScheduleTableEventSetting_0 to /Os/Os/Task9_Core1 */
#define OS_OSSCHEDULETABLESETEVENTTASKREF_REF    

/* Reference from PRIVATE_BSS_CLONE to /Os/Os/CPUXCTCM */
#define OS_MEMORYREGIONREF_REF    

/* Reference from PRIVATE_BSS_CORE1 to /Os/Os/CPU1BTCM */
#define OS_MEMORYREGIONREF_REF    

/* Reference from PRIVATE_CODE_CLONE to /Os/Os/CPUXATCM */
#define OS_MEMORYREGIONREF_REF    

/* Reference from PRIVATE_CODE_CORE0 to /Os/Os/CPU0BTCM */
#define OS_MEMORYREGIONREF_REF    

/* Reference from PRIVATE_CODE_CORE1 to /Os/Os/CPU1BTCM */
#define OS_MEMORYREGIONREF_REF    

/* Reference from PRIVATE_DATA_CLONE to /Os/Os/CPUXCTCM */
#define OS_MEMORYREGIONREF_REF    

/* Reference from PRIVATE_DATA_CORE0 to /Os/Os/CPU0BTCM */
#define OS_MEMORYREGIONREF_REF    

/* Reference from PRIVATE_DATA_CORE1 to /Os/Os/CPU1BTCM */
#define OS_MEMORYREGIONREF_REF    

/* Reference from PRI_BSS_CORE0 to /Os/Os/CPU0BTCM */
#define OS_MEMORYREGIONREF_REF    

/* Reference from RAMCODE_QM_CORE0 to /Os/Os/os_ramcode_qm_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from RAMCODE_QM_CORE1 to /Os/Os/os_ramcode_qm_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from SEC_VAR_INIT_QM_GLOBAL_8 to /Os/Os/os_data_qm_8 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from STACKCFG_QM_CORE0_32 to /Os/Os/os_stack_qm_32_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from STACKCFG_QM_CORE1_32 to /Os/Os/os_stack_qm_32_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from SystemModeStack_AbortStack to /Os/Os/CPU0BTCM */
#define OS_CORE0MEMORYREGIONREF_REF    

/* Reference from SystemModeStack_AbortStack to /Os/Os/CPU1BTCM */
#define OS_CORE1MEMORYREGIONREF_REF    

/* Reference from SystemModeStack_FiqStack to /Os/Os/CPU0BTCM */
#define OS_CORE0MEMORYREGIONREF_REF    

/* Reference from SystemModeStack_FiqStack to /Os/Os/CPU1BTCM */
#define OS_CORE1MEMORYREGIONREF_REF    

/* Reference from SystemModeStack_HypervisorStack to /Os/Os/CPU0BTCM */
#define OS_CORE0MEMORYREGIONREF_REF    

/* Reference from SystemModeStack_HypervisorStack to /Os/Os/CPU1BTCM */
#define OS_CORE1MEMORYREGIONREF_REF    

/* Reference from SystemModeStack_IrqStack to /Os/Os/CPU0BTCM */
#define OS_CORE0MEMORYREGIONREF_REF    

/* Reference from SystemModeStack_IrqStack to /Os/Os/CPU1BTCM */
#define OS_CORE1MEMORYREGIONREF_REF    

/* Reference from SystemModeStack_KernelStack to /Os/Os/CPU0BTCM */
#define OS_CORE0MEMORYREGIONREF_REF    

/* Reference from SystemModeStack_KernelStack to /Os/Os/CPU1BTCM */
#define OS_CORE1MEMORYREGIONREF_REF    

/* Reference from SystemModeStack_UndefinedStack to /Os/Os/CPU0BTCM */
#define OS_CORE0MEMORYREGIONREF_REF    

/* Reference from SystemModeStack_UndefinedStack to /Os/Os/CPU1BTCM */
#define OS_CORE1MEMORYREGIONREF_REF    

/* Reference from SystemModeStack_UserStack to /Os/Os/CPU0BTCM */
#define OS_CORE0MEMORYREGIONREF_REF    

/* Reference from SystemModeStack_UserStack to /Os/Os/CPU1BTCM */
#define OS_CORE1MEMORYREGIONREF_REF    

/* Reference from TRUSTED_VAR_CLEARED_QM_CORE0_32 to /Os/Os/os_trust_qm_32_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from TRUSTED_VAR_CLEARED_QM_CORE1_32 to /Os/Os/os_trust_qm_32_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from Task1_OsTaskTimingProtection_0_OsTaskResourceLock_0 to /Os/Os/OsResource_0 */
#define OS_OSTASKRESOURCELOCKRESOURCEREF_REF    

/* Reference from Task12_Core1_OsTaskTimingProtection_0_OsTaskResourceLock_0 to /Os/Os/OsResource_2 */
#define OS_OSTASKRESOURCELOCKRESOURCEREF_REF    

/* Reference from Task5_OsTaskTimingProtection_0_OsTaskResourceLock_0 to /Os/Os/OsResource_1 */
#define OS_OSTASKRESOURCELOCKRESOURCEREF_REF    

/* Reference from UNCLEAR_RAM_BSS to /Os/Os/GMU_NORMAL */
#define OS_MEMORYREGIONREF_REF    

/* Reference from UNDEFINE_RAM_BSS to /Os/Os/GMU_NORMAL */
#define OS_MEMORYREGIONREF_REF    

/* Reference from UNDEFINE_RAM_DATA to /Os/Os/GMU_NORMAL */
#define OS_MEMORYREGIONREF_REF    

/* Reference from VAR_CLEARED_QM_CORE0_16 to /Os/Os/os_bss_qm_16_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_CLEARED_QM_CORE0_32 to /Os/Os/os_bss_qm_32_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_CLEARED_QM_CORE0_8 to /Os/Os/os_bss_qm_8_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_CLEARED_QM_CORE0_BOOLEAN to /Os/Os/os_bss_qm_bool_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_CLEARED_QM_CORE0_UNSPECIFIED to /Os/Os/os_bss_qm_unspecified_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_CLEARED_QM_CORE1_16 to /Os/Os/os_bss_qm_16_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_CLEARED_QM_CORE1_32 to /Os/Os/os_bss_qm_32_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_CLEARED_QM_CORE1_8 to /Os/Os/os_bss_qm_8_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_CLEARED_QM_CORE1_BOOLEAN to /Os/Os/os_bss_qm_bool_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_CLEARED_QM_CORE1_UNSPECIFIED to /Os/Os/os_bss_qm_unspecified_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_CLEARED_QM_GLOBAL_16 to /Os/Os/os_bss_qm_16 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_CLEARED_QM_GLOBAL_16_NO_CACHEABLE to /Os/Os/os_bss_qm_16_uncached */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_CLEARED_QM_GLOBAL_32 to /Os/Os/os_bss_qm_32 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_CLEARED_QM_GLOBAL_32_NO_CACHEABLE to /Os/Os/os_bss_qm_32_uncached */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_CLEARED_QM_GLOBAL_8 to /Os/Os/os_bss_qm_8 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_CLEARED_QM_GLOBAL_8_NO_CACHEABLE to /Os/Os/os_bss_qm_8_uncached */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_CLEARED_QM_GLOBAL_BOOLEAN to /Os/Os/os_bss_qm_bool */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_CLEARED_QM_GLOBAL_BOOLEAN_NO_CACHEABLE to /Os/Os/os_bss_qm_bool_uncached */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_CLEARED_QM_GLOBAL_UNSPECIFIED to /Os/Os/os_bss_qm_unspecified */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_CLEARED_QM_GLOBAL_UNSPECIFIED_NO_CACHEABLE to /Os/Os/os_bss_qm_unspecified_uncached */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_CLEARED_QM_PRIVATE_CLONE to /Os/Os/private_clone_bss */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_INIT_QM_CORE0_16 to /Os/Os/os_data_qm_16_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_INIT_QM_CORE0_32 to /Os/Os/os_data_qm_32_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_INIT_QM_CORE0_8 to /Os/Os/os_data_qm_8_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_INIT_QM_CORE0_BOOLEAN to /Os/Os/os_data_qm_bool_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_INIT_QM_CORE0_UNSPECIFIED to /Os/Os/os_data_qm_unspecified_core0 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_INIT_QM_CORE1_16 to /Os/Os/os_data_qm_16_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_INIT_QM_CORE1_32 to /Os/Os/os_data_qm_32_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_INIT_QM_CORE1_8 to /Os/Os/os_data_qm_8_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_INIT_QM_CORE1_BOOLEAN to /Os/Os/os_data_qm_bool_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_INIT_QM_CORE1_UNSPECIFIED to /Os/Os/os_data_qm_unspecified_core1 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_INIT_QM_GLOBAL_16 to /Os/Os/os_data_qm_16 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_INIT_QM_GLOBAL_16_NO_CACHEABLE to /Os/Os/os_data_qm_16_uncached */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_INIT_QM_GLOBAL_32 to /Os/Os/os_data_qm_32 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_INIT_QM_GLOBAL_32_NO_CACHEABLE to /Os/Os/os_data_qm_32_uncached */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_INIT_QM_GLOBAL_8_NO_CACHEABLE to /Os/Os/os_data_qm_8_uncached */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_INIT_QM_GLOBAL_BOOLEAN to /Os/Os/os_data_qm_bool */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_INIT_QM_GLOBAL_BOOLEAN_NO_CACHEABLE to /Os/Os/os_data_qm_bool_uncached */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_INIT_QM_GLOBAL_UNSPECIFIED to /Os/Os/os_data_qm_unspecified */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_INIT_QM_GLOBAL_UNSPECIFIED_NO_CACHEABLE to /Os/Os/os_data_qm_unspecified_uncached */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_INIT_QM_PRIVATE_CLONE to /Os/Os/private_clone_data */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_NO_INIT_QM_GLOBAL_16 to /Os/Os/os_no_init_qm_16 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_NO_INIT_QM_GLOBAL_32 to /Os/Os/os_no_init_qm_32 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_NO_INIT_QM_GLOBAL_8 to /Os/Os/os_no_init_qm_8 */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_NO_INIT_QM_GLOBAL_BOOLEAN to /Os/Os/os_no_init_qm_bool */
#define OS_MEMORYSECTIONMATCH_REF    

/* Reference from VAR_NO_INIT_QM_GLOBAL_UNSPECIFIED to /Os/Os/os_no_init_qm_unspecified */
#define OS_MEMORYSECTIONMATCH_REF    


#endif /* OS_CFG_H */
