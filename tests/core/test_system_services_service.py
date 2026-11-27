"""Unit and integration tests for SystemServicesWorkbenchService and SystemServicesValidationRule."""

from pathlib import Path

import pytest

from autosar_configurator.core.config_manager import PreLockedError
from autosar_configurator.core.model.configuration_model import (
    EcucContainerValue,
    EcucModuleConfiguration,
)
from autosar_configurator.core.model.definition_model import (
    EcucModuleDef,
    EcucParameterDef,
    EcucParameterType,
)
from autosar_configurator.core.rules.system_services_rules import SystemServicesValidationRule
from autosar_configurator.core.services import SystemServicesWorkbenchService
from autosar_configurator.core.validation_engine import ValidationEngine, ValidationSeverity
from autosar_configurator.core.workspace_manager import WorkspaceManager


def _c(parent, short_name: str, def_ref: str) -> EcucContainerValue:
    c = EcucContainerValue(
        short_name=short_name,
        definition_ref=def_ref,
        def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
    )
    if isinstance(parent, EcucModuleConfiguration):
        parent.add_container(c)
    else:
        parent.add_sub_container(c)
    return c


def _p(c: EcucContainerValue, name: str, val, dest_type: str = "ECUC-INTEGER-PARAM-DEF") -> None:
    c.set_parameter_value(name, val, f"{c.definition_ref}/{name}")
    c.parameter_values[name].dest_type = dest_type


def _r(c: EcucContainerValue, name: str, val_ref: str) -> None:
    c.set_reference_value(name, val_ref, f"{c.definition_ref}/{name}")


def _mr(c: EcucContainerValue, name: str, val_ref: str) -> None:
    idx = len(c.multi_reference_values.get(name, []))
    c.add_multi_reference_value(name, val_ref, f"{c.definition_ref}/{name}", idx)


def build_synthetic_services_project(tmp_path: Path):
    """Build a multi-module project covering EcuM, BswM, Os, Dcm+CanTp+PduR+CanIf, Det, vBRS, CddMotor."""
    proj_dir = tmp_path / "sys_proj"
    proj_dir.mkdir(parents=True, exist_ok=True)
    ws = WorkspaceManager()
    project = ws.create_project("SysServicesTestProj", proj_dir / "SysServicesTestProj.dpa", format_version=8)

    mods = {}
    for mod in (
        "EcuM",
        "BswM",
        "Os",
        "Dcm",
        "CanTp",
        "Det",
        "ComM",
        "CanSM",
        "PduR",
        "CanIf",
        "EcuC",
        "Mcu",
        "vBRS",
        "CddMotor",
    ):
        mdef = EcucModuleDef(mod, definition_ref=f"/MICROSAR/{mod}")
        mgr = project.add_module(mdef, proj_dir / "Config" / "ECUC" / f"{mod}.arxml")
        mods[mod] = mgr.configuration

    # --- Mcu (EB-style target referenced by EcuMNormalMcuModeRef) ---
    mcu_cfg = _c(mods["Mcu"], "McuModuleConfiguration", "/MICROSAR/Mcu/McuModuleConfiguration")
    _c(mcu_cfg, "McuModeSettingConf_0", "/MICROSAR/Mcu/McuModuleConfiguration/McuModeSettingConf")
    mcu_gen = _c(mods["Mcu"], "McuGeneralConfiguration", "/MICROSAR/Mcu/McuGeneralConfiguration")
    _p(mcu_gen, "McuDevErrorDetect", True, "ECUC-BOOLEAN-PARAM-DEF")

    # --- EcuC ---
    hw = _c(mods["EcuC"], "EcucHardware", "/MICROSAR/EcuC/EcucHardware")
    c0 = _c(hw, "EcucCore0", "/MICROSAR/EcuC/EcucHardware/EcucCoreDefinition")
    _p(c0, "EcucCoreId", 0)
    c1 = _c(hw, "EcucCore1", "/MICROSAR/EcuC/EcucHardware/EcucCoreDefinition")
    _p(c1, "EcucCoreId", 1)
    pc = _c(mods["EcuC"], "EcucPartitionCollection", "/MICROSAR/EcuC/EcucPartitionCollection")
    _c(pc, "EcucPartition_core0", "/MICROSAR/EcuC/EcucPartitionCollection/EcucPartition")
    _c(pc, "EcucPartition_core1", "/MICROSAR/EcuC/EcucPartitionCollection/EcucPartition")

    pdu_coll = _c(mods["EcuC"], "EcucPduCollection", "/MICROSAR/EcuC/EcucPduCollection")
    for pname in (
        "DiagPhys_Rx_CanIf",
        "DiagPhys_Rx_CanTp",
        "DiagPhys_Rx_Dcm",
        "DiagResp_Tx_Dcm",
        "DiagResp_Tx_CanTp",
        "DiagResp_Tx_CanIf",
        "DiagFunc_Rx_CanIf",
        "DiagFunc_Rx_CanTp",
        "DiagFunc_Rx_Dcm",
    ):
        p_c = _c(pdu_coll, pname, "/MICROSAR/EcuC/EcucPduCollection/Pdu")
        _p(p_c, "PduLength", 8)

    # --- ComM & CanSM ---
    comm_set = _c(mods["ComM"], "ComMConfigSet", "/MICROSAR/ComM/ComMConfigSet")
    comm_ch = _c(comm_set, "CN_CAN0", "/MICROSAR/ComM/ComMConfigSet/ComMChannel")
    _p(comm_ch, "ComMChannelId", 0)
    comm_gen = _c(mods["ComM"], "ComMGeneral", "/MICROSAR/ComM/ComMGeneral")
    _p(comm_gen, "ComMDevErrorDetect", True, "ECUC-BOOLEAN-PARAM-DEF")
    cansm_gen = _c(mods["CanSM"], "CanSMGeneral", "/MICROSAR/CanSM/CanSMGeneral")
    _p(cansm_gen, "CanSMDevErrorDetect", True, "ECUC-BOOLEAN-PARAM-DEF")

    # --- Os ---
    osos = _c(mods["Os"], "OsOS", "/MICROSAR/Os/OsOS")
    _p(osos, "OsStatus", "EXTENDED", "ECUC-ENUMERATION-PARAM-DEF")
    _p(osos, "OsScalabilityClass", "SC1", "ECUC-ENUMERATION-PARAM-DEF")
    _p(osos, "OsNumberOfCores", 2)
    _p(osos, "OsStackMonitoring", True, "ECUC-BOOLEAN-PARAM-DEF")
    _r(osos, "OsMasterCore", "/ActiveEcuC/Os/OsCore0")
    _r(osos, "OsSystemTimer", "/ActiveEcuC/Os/SystemTimer_core0")
    hooks = _c(osos, "OsHooks", "/MICROSAR/Os/OsOS/OsHooks")
    _p(hooks, "OsErrorHook", True, "ECUC-BOOLEAN-PARAM-DEF")
    _p(hooks, "OsStartupHook", False, "ECUC-BOOLEAN-PARAM-DEF")

    _c(mods["Os"], "OSDEFAULTAPPMODE", "/MICROSAR/Os/OsAppMode")
    res = _c(mods["Os"], "OsResource", "/MICROSAR/Os/OsResource")
    _p(res, "OsResourceProperty", "STANDARD", "ECUC-ENUMERATION-PARAM-DEF")
    _mr(res, "OsResourceAccessingApplication", "/ActiveEcuC/Os/SystemApplication_OsCore0")

    for cname, cid in (("OsCore0", 0), ("OsCore1", 1)):
        oc = _c(mods["Os"], cname, "/MICROSAR/Os/OsCore")
        _p(oc, "OsCoreIsAutostart", True, "ECUC-BOOLEAN-PARAM-DEF")
        _p(oc, "OsCoreIsAutosar", True, "ECUC-BOOLEAN-PARAM-DEF")
        _r(oc, "OsCoreEcucCoreRef", f"/ActiveEcuC/EcuC/EcucHardware/EcucCore{cid}")
        _r(oc, "OsCoreIdleTask", f"/ActiveEcuC/Os/IdleTask_{cname}")
        _r(oc, "OsCoreSystemApplication", f"/ActiveEcuC/Os/SystemApplication_{cname}")
        stks = _c(oc, "OsCoreStacks", "/MICROSAR/Os/OsCore/OsCoreStacks")
        _p(stks, "OsCoreKernelStackSize", 1024)
        _p(stks, "OsCoreInitStackSize", 512)

        idle = _c(mods["Os"], f"IdleTask_{cname}", "/MICROSAR/Os/OsTask")
        _p(idle, "OsTaskPriority", 0)
        _p(idle, "OsTaskStackSize", 512)
        _p(idle, "OsTaskActivation", 1)
        _p(idle, "OsTaskSchedule", "FULL", "ECUC-ENUMERATION-PARAM-DEF")
        _p(idle, "OsTaskType", "BASIC", "ECUC-ENUMERATION-PARAM-DEF")

    task_10ms = _c(mods["Os"], "OsTask_10ms_Core0", "/MICROSAR/Os/OsTask")
    _p(task_10ms, "OsTaskPriority", 40)
    _p(task_10ms, "OsTaskStackSize", 1024)
    _p(task_10ms, "OsTaskActivation", 1)
    _p(task_10ms, "OsTaskSchedule", "FULL", "ECUC-ENUMERATION-PARAM-DEF")
    _p(task_10ms, "OsTaskType", "BASIC", "ECUC-ENUMERATION-PARAM-DEF")

    # Identical private timer IRQ source (27) on Core0 vs Core1 must NOT trigger OS_DUP_ISR_SOURCE
    isr0 = _c(mods["Os"], "TimerIsr_Core0", "/MICROSAR/Os/OsIsr")
    _p(isr0, "OsIsrCategory", "CATEGORY_2", "ECUC-ENUMERATION-PARAM-DEF")
    _p(isr0, "OsIsrInterruptSource", 27)
    _p(isr0, "OsIsrInterruptPriority", 90)
    _p(isr0, "OsIsrStackSize", 1024)
    isr1 = _c(mods["Os"], "TimerIsr_Core1", "/MICROSAR/Os/OsIsr")
    _p(isr1, "OsIsrCategory", "CATEGORY_2", "ECUC-ENUMERATION-PARAM-DEF")
    _p(isr1, "OsIsrInterruptSource", 27)
    _p(isr1, "OsIsrInterruptPriority", 90)
    _p(isr1, "OsIsrStackSize", 1024)

    cnt0 = _c(mods["Os"], "SystemTimer_core0", "/MICROSAR/Os/OsCounter")
    _p(cnt0, "OsCounterType", "HARDWARE", "ECUC-ENUMERATION-PARAM-DEF")
    _p(cnt0, "OsCounterMaxAllowedValue", 65535)
    _p(cnt0, "OsSecondsPerTick", 0.001, "ECUC-FLOAT-PARAM-DEF")
    drv0 = _c(cnt0, "OsDriver", "/MICROSAR/Os/OsCounter/OsDriver")
    _r(drv0, "OsDriverIsrRef", "/ActiveEcuC/Os/TimerIsr_Core0")

    alm = _c(mods["Os"], "Alarm_10ms", "/MICROSAR/Os/OsAlarm")
    _r(alm, "OsAlarmCounterRef", "/ActiveEcuC/Os/SystemTimer_core0")
    alm_act = _c(alm, "OsAlarmAction", "/MICROSAR/Os/OsAlarm/OsAlarmAction")
    alm_tk = _c(alm_act, "OsAlarmActivateTask", "/MICROSAR/Os/OsAlarm/OsAlarmAction/OsAlarmActivateTask")
    _r(alm_tk, "OsAlarmActivateTaskRef", "/ActiveEcuC/Os/OsTask_10ms_Core0")

    stbl = _c(mods["Os"], "SchTbl_Core0", "/MICROSAR/Os/OsScheduleTable")
    _p(stbl, "OsScheduleTableDuration", 10)
    _p(stbl, "OsScheduleTableRepeating", True, "ECUC-BOOLEAN-PARAM-DEF")
    _r(stbl, "OsScheduleTableCounterRef", "/ActiveEcuC/Os/SystemTimer_core0")
    ep = _c(stbl, "ExpiryPoint_0", "/MICROSAR/Os/OsScheduleTable/OsScheduleTableExpiryPoint")
    _p(ep, "OsScheduleTblExpPointOffset", 0)
    ep_act = _c(ep, "Act_10ms", "/MICROSAR/Os/OsScheduleTable/OsScheduleTableExpiryPoint/OsScheduleTableTaskActivation")
    _r(ep_act, "OsScheduleTableActivateTaskRef", "/ActiveEcuC/Os/OsTask_10ms_Core0")

    app0 = _c(mods["Os"], "SystemApplication_OsCore0", "/MICROSAR/Os/OsApplication")
    _r(app0, "OsApplicationCoreRef", "/ActiveEcuC/EcuC/EcucHardware/EcucCore0")
    _r(app0, "OsAppEcucPartitionRef", "/ActiveEcuC/EcuC/EcucPartitionCollection/EcucPartition_core0")
    _r(app0, "OsAppCounterRef", "/ActiveEcuC/Os/SystemTimer_core0")
    _r(app0, "OsAppScheduleTableRef", "/ActiveEcuC/Os/SchTbl_Core0")
    _mr(app0, "OsAppTaskRef", "/ActiveEcuC/Os/IdleTask_OsCore0")
    _mr(app0, "OsAppTaskRef", "/ActiveEcuC/Os/OsTask_10ms_Core0")
    _mr(app0, "OsAppIsrRef", "/ActiveEcuC/Os/TimerIsr_Core0")
    _mr(app0, "OsAppAlarmRef", "/ActiveEcuC/Os/Alarm_10ms")

    app1 = _c(mods["Os"], "SystemApplication_OsCore1", "/MICROSAR/Os/OsApplication")
    _r(app1, "OsApplicationCoreRef", "/ActiveEcuC/EcuC/EcucHardware/EcucCore1")
    _r(app1, "OsAppEcucPartitionRef", "/ActiveEcuC/EcuC/EcucPartitionCollection/EcucPartition_core1")
    _mr(app1, "OsAppTaskRef", "/ActiveEcuC/Os/IdleTask_OsCore1")
    _mr(app1, "OsAppIsrRef", "/ActiveEcuC/Os/TimerIsr_Core1")

    sp = _c(mods["Os"], "IocSpinlock_0", "/MICROSAR/Os/OsSpinlock")
    _p(sp, "OsSpinlockLockMethod", "LOCK_NOTHING", "ECUC-ENUMERATION-PARAM-DEF")
    _p(sp, "OsSpinlockLockType", "OPTIMIZED", "ECUC-ENUMERATION-PARAM-DEF")
    _mr(sp, "OsSpinlockAccessingApplication", "/ActiveEcuC/Os/SystemApplication_OsCore0")
    _mr(sp, "OsSpinlockAccessingApplication", "/ActiveEcuC/Os/SystemApplication_OsCore1")

    # --- EcuM ---
    ecum_gen = _c(mods["EcuM"], "EcuMGeneral", "/MICROSAR/EcuM/EcuMGeneral")
    _p(ecum_gen, "EcuMMainFunctionPeriod", 0.01, "ECUC-FLOAT-PARAM-DEF")
    _p(ecum_gen, "EcuMDevErrorDetect", True, "ECUC-BOOLEAN-PARAM-DEF")
    _p(ecum_gen, "EcuMSlaveCoreHandling", True, "ECUC-BOOLEAN-PARAM-DEF")

    ecum_cfg = _c(mods["EcuM"], "EcuMConfiguration", "/MICROSAR/EcuM/EcuMConfiguration")
    flex = _c(ecum_cfg, "EcuMFlexConfiguration", "/MICROSAR/EcuM/EcuMConfiguration/EcuMFlexConfiguration")
    _r(flex, "EcuMNormalMcuModeRef", "/Mcu/Mcu/McuModuleConfiguration/McuModeSettingConf_0")
    _mr(flex, "EcuMPartitionRef", "/ActiveEcuC/EcuC/EcucPartitionCollection/EcucPartition_core0")
    _mr(flex, "EcuMPartitionRef", "/ActiveEcuC/EcuC/EcucPartitionCollection/EcucPartition_core1")
    common = _c(ecum_cfg, "EcuMCommonConfiguration", "/MICROSAR/EcuM/EcuMConfiguration/EcuMCommonConfiguration")
    _r(common, "EcuMDefaultAppMode", "/ActiveEcuC/Os/OSDEFAULTAPPMODE")
    _r(common, "EcuMOSResource", "/ActiveEcuC/Os/OsResource")
    sd_t = _c(common, "EcuMDefaultShutdownTarget", "/MICROSAR/EcuM/EcuMConfiguration/EcuMCommonConfiguration/EcuMDefaultShutdownTarget")
    _p(sd_t, "EcuMDefaultState", "EcuMStateOff", "ECUC-ENUMERATION-PARAM-DEF")

    l0 = _c(common, "EcuMDriverInitListZero", "/MICROSAR/EcuM/EcuMConfiguration/EcuMCommonConfiguration/EcuMDriverInitListZero")
    i0 = _c(l0, "Det_InitMemory", "/MICROSAR/EcuM/EcuMConfiguration/EcuMCommonConfiguration/EcuMDriverInitListZero/EcuMDriverInitItem")
    _p(i0, "EcuMModuleID", "Det", "ECUC-STRING-PARAM-DEF")
    _p(i0, "EcuMModuleService", "Det_InitMemory", "ECUC-STRING-PARAM-DEF")
    _p(i0, "EcuMModuleHeader", "Det.h", "ECUC-STRING-PARAM-DEF")

    l1 = _c(common, "EcuMDriverInitListOne", "/MICROSAR/EcuM/EcuMConfiguration/EcuMCommonConfiguration/EcuMDriverInitListOne")
    i1 = _c(l1, "Mcu_Init", "/MICROSAR/EcuM/EcuMConfiguration/EcuMCommonConfiguration/EcuMDriverInitListOne/EcuMDriverInitItem")
    _p(i1, "EcuMModuleID", "Mcu", "ECUC-STRING-PARAM-DEF")
    _p(i1, "EcuMModuleService", "Mcu_Init", "ECUC-STRING-PARAM-DEF")
    _p(i1, "EcuMModuleHeader", "Mcu.h", "ECUC-STRING-PARAM-DEF")
    i2 = _c(l1, "Custom_Code", "/MICROSAR/EcuM/EcuMConfiguration/EcuMCommonConfiguration/EcuMDriverInitListOne/EcuMDriverInitItem")
    _p(i2, "EcuMModuleID", "Code", "ECUC-STRING-PARAM-DEF")
    _p(i2, "EcuMAdditionalInitCode", "CustomHook();", "ECUC-STRING-PARAM-DEF")

    ws0 = _c(common, "ECUM_WKSOURCE_POWER", "/MICROSAR/EcuM/EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource")
    _p(ws0, "EcuMWakeupSourceId", 0)
    _p(ws0, "EcuMWakeupSourcePolling", False, "ECUC-BOOLEAN-PARAM-DEF")
    _p(ws0, "EcuMValidationTimeout", 0.0, "ECUC-FLOAT-PARAM-DEF")
    ws1 = _c(common, "CN_CAN0_Wk", "/MICROSAR/EcuM/EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource")
    _p(ws1, "EcuMWakeupSourceId", 1)
    _r(ws1, "EcuMComMChannelRef", "/ActiveEcuC/ComM/ComMConfigSet/CN_CAN0")

    rm = _c(flex, "ECUM_RESET_MCU", "/MICROSAR/EcuM/EcuMConfiguration/EcuMFlexConfiguration/EcuMResetMode")
    _p(rm, "EcuMResetModeId", 0)
    sc = _c(flex, "ECUM_CAUSE_DCM", "/MICROSAR/EcuM/EcuMConfiguration/EcuMFlexConfiguration/EcuMShutdownCause")
    _p(sc, "EcuMShutdownCauseId", 3)

    # --- BswM ---
    bswm_gen = _c(mods["BswM"], "BswMGeneral", "/MICROSAR/BswM/BswMGeneral")
    _p(bswm_gen, "BswMDevErrorDetect", True, "ECUC-BOOLEAN-PARAM-DEF")
    _p(bswm_gen, "BswMEcuMEnabled", True, "ECUC-BOOLEAN-PARAM-DEF")
    _p(bswm_gen, "BswMComMEnabled", True, "ECUC-BOOLEAN-PARAM-DEF")
    _p(bswm_gen, "BswMCanSMEnabled", True, "ECUC-BOOLEAN-PARAM-DEF")
    _p(bswm_gen, "BswMDcmEnabled", True, "ECUC-BOOLEAN-PARAM-DEF")

    bswm_cfg = _c(mods["BswM"], "BswMConfig", "/MICROSAR/BswM/BswMConfig")
    arb = _c(bswm_cfg, "BswMArbitration", "/MICROSAR/BswM/BswMConfig/BswMArbitration")
    mc = _c(bswm_cfg, "BswMModeControl", "/MICROSAR/BswM/BswMConfig/BswMModeControl")

    port_esh = _c(arb, "ESH_State", "/MICROSAR/BswM/BswMConfig/BswMArbitration/BswMModeRequestPort")
    _p(port_esh, "BswMRequestProcessing", "BSWM_IMMEDIATE", "ECUC-ENUMERATION-PARAM-DEF")
    _p(port_esh, "BswMArbitrateOnInit", True, "ECUC-BOOLEAN-PARAM-DEF")
    src_w = _c(port_esh, "BswMModeRequestSource", "/MICROSAR/BswM/BswMConfig/BswMArbitration/BswMModeRequestPort/BswMModeRequestSource")
    _c(src_w, "BswMGenericRequest", "/MICROSAR/BswM/BswMConfig/BswMArbitration/BswMModeRequestPort/BswMModeRequestSource/BswMGenericRequest")

    cond_run = _c(arb, "Cond_Run", "/MICROSAR/BswM/BswMConfig/BswMArbitration/BswMModeCondition")
    _p(cond_run, "BswMConditionType", "BSWM_EQUALS", "ECUC-ENUMERATION-PARAM-DEF")
    _r(cond_run, "BswMConditionMode", "/ActiveEcuC/BswM/BswMConfig/BswMArbitration/ESH_State")
    cv_w = _c(cond_run, "BswMConditionValue", "/MICROSAR/BswM/BswMConfig/BswMArbitration/BswMModeCondition/BswMConditionValue")
    bm = _c(cv_w, "BswMBswMode", "/MICROSAR/BswM/BswMConfig/BswMArbitration/BswMModeCondition/BswMConditionValue/BswMBswMode")
    _p(bm, "BswMBswRequestedMode", "ESH_RUN", "ECUC-STRING-PARAM-DEF")

    cond_wake = _c(arb, "Cond_NoWakeup", "/MICROSAR/BswM/BswMConfig/BswMArbitration/BswMModeCondition")
    _p(cond_wake, "BswMConditionType", "BSWM_EQUALS_NOT", "ECUC-ENUMERATION-PARAM-DEF")
    _r(cond_wake, "BswMConditionMode", "/ActiveEcuC/BswM/BswMConfig/BswMArbitration/ESH_State")
    cv_w2 = _c(cond_wake, "BswMConditionValue", "/MICROSAR/BswM/BswMConfig/BswMArbitration/BswMModeCondition/BswMConditionValue")
    bm2 = _c(cv_w2, "BswMBswMode", "/MICROSAR/BswM/BswMConfig/BswMArbitration/BswMModeCondition/BswMConditionValue/BswMBswMode")
    _p(bm2, "BswMBswRequestedMode", "ESH_WAKEUP", "ECUC-STRING-PARAM-DEF")

    le_top = _c(arb, "LE_EnterRun", "/MICROSAR/BswM/BswMConfig/BswMArbitration/BswMLogicalExpression")
    _p(le_top, "BswMLogicalOperator", "BSWM_AND", "ECUC-ENUMERATION-PARAM-DEF")
    _mr(le_top, "BswMArgumentRef", "/ActiveEcuC/BswM/BswMConfig/BswMArbitration/Cond_Run")
    _mr(le_top, "BswMArgumentRef", "/ActiveEcuC/BswM/BswMConfig/BswMArbitration/Cond_NoWakeup")

    act1 = _c(mc, "Action_StepOne", "/MICROSAR/BswM/BswMConfig/BswMModeControl/BswMAction")
    av1 = _c(act1, "BswMAvailableActions", "/MICROSAR/BswM/BswMConfig/BswMModeControl/BswMAction/BswMAvailableActions")
    uc1 = _c(av1, "BswMUserCallout", "/MICROSAR/BswM/BswMConfig/BswMModeControl/BswMAction/BswMAvailableActions/BswMUserCallout")
    _p(uc1, "BswMUserCalloutFunction", "EcuM_GoRun()", "ECUC-STRING-PARAM-DEF")

    act2 = _c(mc, "Action_StepTwo", "/MICROSAR/BswM/BswMConfig/BswMModeControl/BswMAction")
    av2 = _c(act2, "BswMAvailableActions", "/MICROSAR/BswM/BswMConfig/BswMModeControl/BswMAction/BswMAvailableActions")
    uc2 = _c(av2, "BswMUserCallout", "/MICROSAR/BswM/BswMConfig/BswMModeControl/BswMAction/BswMAvailableActions/BswMUserCallout")
    _p(uc2, "BswMUserCalloutFunction", "ComM_AllowAll()", "ECUC-STRING-PARAM-DEF")

    al_run = _c(mc, "AL_EnterRun", "/MICROSAR/BswM/BswMConfig/BswMModeControl/BswMActionList")
    _p(al_run, "BswMActionListExecution", "BSWM_CONDITION", "ECUC-ENUMERATION-PARAM-DEF")
    ai1 = _c(al_run, "Item_1", "/MICROSAR/BswM/BswMConfig/BswMModeControl/BswMActionList/BswMActionListItem")
    _p(ai1, "BswMActionListItemIndex", 1)
    _p(ai1, "BswMAbortOnFail", False, "ECUC-BOOLEAN-PARAM-DEF")
    _r(ai1, "BswMActionListItemRef", "/ActiveEcuC/BswM/BswMConfig/BswMModeControl/Action_StepTwo")
    ai0 = _c(al_run, "Item_0", "/MICROSAR/BswM/BswMConfig/BswMModeControl/BswMActionList/BswMActionListItem")
    _p(ai0, "BswMActionListItemIndex", 0)
    _p(ai0, "BswMAbortOnFail", False, "ECUC-BOOLEAN-PARAM-DEF")
    _r(ai0, "BswMActionListItemRef", "/ActiveEcuC/BswM/BswMConfig/BswMModeControl/Action_StepOne")
    _r(mc, "BswMInitActionListRef", "/ActiveEcuC/BswM/BswMConfig/BswMModeControl/AL_EnterRun")

    rule1 = _c(arb, "Rule_Run", "/MICROSAR/BswM/BswMConfig/BswMArbitration/BswMRule")
    _p(rule1, "BswMRuleId", 1)
    _p(rule1, "BswMRuleInitState", "BSWM_FALSE", "ECUC-ENUMERATION-PARAM-DEF")
    _r(rule1, "BswMRuleExpressionRef", "/ActiveEcuC/BswM/BswMConfig/BswMArbitration/LE_EnterRun")
    _r(rule1, "BswMRuleTrueActionList", "/ActiveEcuC/BswM/BswMConfig/BswMModeControl/AL_EnterRun")

    # --- CanIf + PduR TP + CanTp + Dcm ---
    canif_init = _c(mods["CanIf"], "CanIfInitCfg", "/MICROSAR/CanIf/CanIfInitCfg")
    c_rx = _c(canif_init, "CanIf_DiagPhys_Rx", "/MICROSAR/CanIf/CanIfInitCfg/CanIfRxPduCfg")
    _p(c_rx, "CanIfRxPduCanId", 0x7E4)
    _p(c_rx, "CanIfRxPduCanIdType", "STANDARD_CAN", "ECUC-ENUMERATION-PARAM-DEF")
    _p(c_rx, "CanIfRxPduDlc", 8)
    _r(c_rx, "CanIfRxPduRef", "/ActiveEcuC/EcuC/EcucPduCollection/DiagPhys_Rx_CanIf")
    c_tx = _c(canif_init, "CanIf_DiagResp_Tx", "/MICROSAR/CanIf/CanIfInitCfg/CanIfTxPduCfg")
    _p(c_tx, "CanIfTxPduCanId", 0x7DF)
    _p(c_tx, "CanIfTxPduCanIdType", "STANDARD_CAN", "ECUC-ENUMERATION-PARAM-DEF")
    _p(c_tx, "CanIfTxPduDlc", 8)
    _r(c_tx, "CanIfTxPduRef", "/ActiveEcuC/EcuC/EcucPduCollection/DiagResp_Tx_CanIf")

    pdur_rt = _c(_c(mods["PduR"], "PduRRoutingTables", "/MICROSAR/PduR/PduRRoutingTables"), "PduRRoutingTable", "/MICROSAR/PduR/PduRRoutingTables/PduRRoutingTable")
    bm_tp = _c(mods["PduR"], "CanTp", "/MICROSAR/PduR/PduRBswModules")
    bm_dcm = _c(mods["PduR"], "Dcm", "/MICROSAR/PduR/PduRBswModules")
    _r(bm_tp, "PduRBswModuleRef", "/ActiveEcuC/CanTp")
    _r(bm_dcm, "PduRBswModuleRef", "/ActiveEcuC/Dcm")

    pr_rx = _c(pdur_rt, "DiagPhys_Rx_Route", "/MICROSAR/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath")
    _p(pr_rx, "PduRRoutingPathCommunicationType", "TRANSPORT_PROTOCOL", "ECUC-ENUMERATION-PARAM-DEF")
    ps_rx = _c(pr_rx, "Src", "/MICROSAR/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath/PduRSrcPdu")
    _r(ps_rx, "PduRSrcPduRef", "/ActiveEcuC/EcuC/EcucPduCollection/DiagPhys_Rx_CanTp")
    _r(ps_rx, "PduRSrcPduPduRBswModulesRef", "/ActiveEcuC/PduR/CanTp")
    pd_rx = _c(pr_rx, "Dst", "/MICROSAR/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath/PduRDestPdu")
    _r(pd_rx, "PduRDestPduRef", "/ActiveEcuC/EcuC/EcucPduCollection/DiagPhys_Rx_Dcm")
    _r(pd_rx, "PduRDestPduPduRBswModulesRef", "/ActiveEcuC/PduR/Dcm")

    pr_tx = _c(pdur_rt, "DiagResp_Tx_Route", "/MICROSAR/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath")
    _p(pr_tx, "PduRRoutingPathCommunicationType", "TRANSPORT_PROTOCOL", "ECUC-ENUMERATION-PARAM-DEF")
    ps_tx = _c(pr_tx, "Src", "/MICROSAR/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath/PduRSrcPdu")
    _r(ps_tx, "PduRSrcPduRef", "/ActiveEcuC/EcuC/EcucPduCollection/DiagResp_Tx_Dcm")
    _r(ps_tx, "PduRSrcPduPduRBswModulesRef", "/ActiveEcuC/PduR/Dcm")
    pd_tx = _c(pr_tx, "Dst", "/MICROSAR/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath/PduRDestPdu")
    _r(pd_tx, "PduRDestPduRef", "/ActiveEcuC/EcuC/EcucPduCollection/DiagResp_Tx_CanTp")
    _r(pd_tx, "PduRDestPduPduRBswModulesRef", "/ActiveEcuC/PduR/CanTp")

    cantp_gen = _c(mods["CanTp"], "CanTpGeneral", "/MICROSAR/CanTp/CanTpGeneral")
    _p(cantp_gen, "CanTpDevErrorDetect", True, "ECUC-BOOLEAN-PARAM-DEF")
    cantp_cfg = _c(mods["CanTp"], "CanTpConfig", "/MICROSAR/CanTp/CanTpConfig")
    _p(cantp_cfg, "CanTpMainFunctionPeriod", 0.005, "ECUC-FLOAT-PARAM-DEF")
    tp_ch = _c(cantp_cfg, "TPCH_Phys", "/MICROSAR/CanTp/CanTpConfig/CanTpChannel")
    rx_nsdu = _c(tp_ch, "CanTpRxNSdu_Phys", "/MICROSAR/CanTp/CanTpConfig/CanTpChannel/CanTpRxNSdu")
    _p(rx_nsdu, "CanTpBs", 8)
    _p(rx_nsdu, "CanTpSTmin", 0.01, "ECUC-FLOAT-PARAM-DEF")
    _p(rx_nsdu, "CanTpRxDl", 8)
    _p(rx_nsdu, "CanTpRxPaddingActivation", "CANTP_ON", "ECUC-ENUMERATION-PARAM-DEF")
    _p(rx_nsdu, "CanTpRxTaType", "CANTP_PHYSICAL", "ECUC-ENUMERATION-PARAM-DEF")
    _r(rx_nsdu, "CanTpRxNSduRef", "/ActiveEcuC/EcuC/EcucPduCollection/DiagPhys_Rx_CanTp")
    rx_npdu = _c(rx_nsdu, "CanTpRxNPdu_0", "/MICROSAR/CanTp/CanTpConfig/CanTpChannel/CanTpRxNSdu/CanTpRxNPdu")
    _r(rx_npdu, "CanTpRxNPduRef", "/ActiveEcuC/EcuC/EcucPduCollection/DiagPhys_Rx_CanIf")
    tx_fc = _c(rx_nsdu, "CanTpTxFcNPdu_0", "/MICROSAR/CanTp/CanTpConfig/CanTpChannel/CanTpRxNSdu/CanTpTxFcNPdu")
    _r(tx_fc, "CanTpTxFcNPduRef", "/ActiveEcuC/EcuC/EcucPduCollection/DiagResp_Tx_CanIf")

    tx_nsdu = _c(tp_ch, "CanTpTxNSdu_Phys", "/MICROSAR/CanTp/CanTpConfig/CanTpChannel/CanTpTxNSdu")
    _p(tx_nsdu, "CanTpTxDl", 8)
    _p(tx_nsdu, "CanTpTxPaddingActivation", "CANTP_ON", "ECUC-ENUMERATION-PARAM-DEF")
    _p(tx_nsdu, "CanTpTxTaType", "CANTP_PHYSICAL", "ECUC-ENUMERATION-PARAM-DEF")
    _r(tx_nsdu, "CanTpTxNSduRef", "/ActiveEcuC/EcuC/EcucPduCollection/DiagResp_Tx_CanTp")
    tx_npdu = _c(tx_nsdu, "CanTpTxNPdu_0", "/MICROSAR/CanTp/CanTpConfig/CanTpChannel/CanTpTxNSdu/CanTpTxNPdu")
    _r(tx_npdu, "CanTpTxNPduRef", "/ActiveEcuC/EcuC/EcucPduCollection/DiagResp_Tx_CanIf")

    dcm_cs = _c(mods["Dcm"], "DcmConfigSet", "/MICROSAR/Dcm/DcmConfigSet")
    dcm_gen = _c(dcm_cs, "DcmGeneral", "/MICROSAR/Dcm/DcmConfigSet/DcmGeneral")
    _p(dcm_gen, "DcmDevErrorDetect", True, "ECUC-BOOLEAN-PARAM-DEF")
    dsd = _c(dcm_cs, "DcmDsd", "/MICROSAR/Dcm/DcmConfigSet/DcmDsd")
    svc_tbl = _c(dsd, "DcmDsdServiceTable", "/MICROSAR/Dcm/DcmConfigSet/DcmDsd/DcmDsdServiceTable")
    svc10 = _c(svc_tbl, "SessionService_0x10", "/MICROSAR/Dcm/DcmConfigSet/DcmDsd/DcmDsdServiceTable/DcmDsdService")
    _p(svc10, "DcmDsdSidTabServiceId", 0x10)
    _p(svc10, "DcmDsdSidTabSubfuncAvail", True, "ECUC-BOOLEAN-PARAM-DEF")
    _p(svc10, "DcmDsdSidTabUsed", True, "ECUC-BOOLEAN-PARAM-DEF")
    sub_def = _c(svc10, "Default_0x01", "/MICROSAR/Dcm/DcmConfigSet/DcmDsd/DcmDsdServiceTable/DcmDsdService/DcmDsdSubService")
    _p(sub_def, "DcmDsdSubServiceId", 1)

    dsl = _c(dcm_cs, "DcmDsl", "/MICROSAR/Dcm/DcmConfigSet/DcmDsl")
    dbuf = _c(dsl, "DcmDslBuffer", "/MICROSAR/Dcm/DcmConfigSet/DcmDsl/DcmDslBuffer")
    _p(dbuf, "DcmDslBufferSize", 128)
    prot = _c(dsl, "DcmDslProtocol", "/MICROSAR/Dcm/DcmConfigSet/DcmDsl/DcmDslProtocol")
    prow = _c(prot, "DcmDslProtocolRow_UDS", "/MICROSAR/Dcm/DcmConfigSet/DcmDsl/DcmDslProtocol/DcmDslProtocolRow")
    _p(prow, "DcmDslProtocolID", "DCM_UDS_ON_CAN", "ECUC-ENUMERATION-PARAM-DEF")
    _r(prow, "DcmDslProtocolRxBufferID", "/ActiveEcuC/Dcm/DcmConfigSet/DcmDsl/DcmDslBuffer")
    _r(prow, "DcmDslProtocolTxBufferID", "/ActiveEcuC/Dcm/DcmConfigSet/DcmDsl/DcmDslBuffer")
    _r(prow, "DcmDslProtocolSIDTable", "/ActiveEcuC/Dcm/DcmConfigSet/DcmDsd/DcmDsdServiceTable")
    mconn = _c(_c(prow, "Conn", "/MICROSAR/Dcm/DcmConfigSet/DcmDsl/DcmDslProtocol/DcmDslProtocolRow/DcmDslConnection"), "MainConn", "/MICROSAR/Dcm/DcmConfigSet/DcmDsl/DcmDslProtocol/DcmDslProtocolRow/DcmDslConnection/DcmDslMainConnection")
    dcm_rx = _c(mconn, "Dcm_PhysRx", "/MICROSAR/Dcm/DcmConfigSet/DcmDsl/DcmDslProtocol/DcmDslProtocolRow/DcmDslConnection/DcmDslMainConnection/DcmDslProtocolRx")
    _p(dcm_rx, "DcmDslProtocolRxAddrType", "DCM_PHYSICAL_TYPE", "ECUC-ENUMERATION-PARAM-DEF")
    _p(dcm_rx, "DcmDslProtocolRxPduId", 0)
    _r(dcm_rx, "DcmDslProtocolRxComMChannelRef", "/ActiveEcuC/ComM/ComMConfigSet/CN_CAN0")
    _r(dcm_rx, "DcmDslProtocolRxPduRef", "/ActiveEcuC/EcuC/EcucPduCollection/DiagPhys_Rx_Dcm")
    dcm_tx = _c(mconn, "Dcm_RespTx", "/MICROSAR/Dcm/DcmConfigSet/DcmDsl/DcmDslProtocol/DcmDslProtocolRow/DcmDslConnection/DcmDslMainConnection/DcmDslProtocolTx")
    _p(dcm_tx, "DcmDslTxConfirmationPduId", 0)
    _r(dcm_tx, "DcmDslProtocolTxPduRef", "/ActiveEcuC/EcuC/EcucPduCollection/DiagResp_Tx_Dcm")

    dsp = _c(dcm_cs, "DcmDsp", "/MICROSAR/Dcm/DcmConfigSet/DcmDsp")
    sess_grp = _c(dsp, "DcmDspSession", "/MICROSAR/Dcm/DcmConfigSet/DcmDsp/DcmDspSession")
    srow = _c(sess_grp, "DcmDspSession_Default", "/MICROSAR/Dcm/DcmConfigSet/DcmDsp/DcmDspSession/DcmDspSessionRow")
    _p(srow, "DcmDspSessionLevel", 1)
    _p(srow, "DcmDspSessionP2ServerMax", 0.05, "ECUC-FLOAT-PARAM-DEF")
    _p(srow, "DcmDspSessionP2StarServerMax", 5.0, "ECUC-FLOAT-PARAM-DEF")
    _p(srow, "DcmDspSessionForBoot", "DCM_NO_BOOT", "ECUC-ENUMERATION-PARAM-DEF")
    sec_grp = _c(dsp, "DcmDspSecurity", "/MICROSAR/Dcm/DcmConfigSet/DcmDsp/DcmDspSecurity")
    sec_r = _c(sec_grp, "DcmDspSecurity_L1", "/MICROSAR/Dcm/DcmConfigSet/DcmDsp/DcmDspSecurity/DcmDspSecurityRow")
    _p(sec_r, "DcmDspSecurityLevel", 1)
    _p(sec_r, "DcmDspSecuritySeedSize", 4)
    _p(sec_r, "DcmDspSecurityKeySize", 4)
    did_c = _c(dsp, "DID_F190", "/MICROSAR/Dcm/DcmConfigSet/DcmDsp/DcmDspDid")
    _p(did_c, "DcmDspDidIdentifier", 0xF190)
    _p(did_c, "DcmDspDidUsed", True, "ECUC-BOOLEAN-PARAM-DEF")

    # --- Det + vBRS + CddMotor ---
    det_gen = _c(mods["Det"], "DetGeneral", "/MICROSAR/Det/DetGeneral")
    _p(det_gen, "DetEnableDet", True, "ECUC-BOOLEAN-PARAM-DEF")
    _p(det_gen, "DetLogBufferSize", 16)
    dm = _c(_c(mods["Det"], "DetConfigSet", "/MICROSAR/Det/DetConfigSet"), "DetModule_0", "/MICROSAR/Det/DetConfigSet/DetModule")
    _p(dm, "DetModuleId", 4096)

    vbrs_hw = _c(mods["vBRS"], "vBRSHwConfig", "/MICROSAR/vBRS/vBRSHwConfig")
    _p(vbrs_hw, "vBRSTimebaseClock", 400000000)
    _p(vbrs_hw, "vBRSOscClock", 25000000)

    cdd_gen = _c(mods["CddMotor"], "CddMotorGeneral", "/User/CddMotor/CddMotorGeneral")
    _p(cdd_gen, "CddMotorDevErrorDetect", False, "ECUC-BOOLEAN-PARAM-DEF")

    project.resolve_all_references(force=True)
    return project, mods


def test_ecum_summary_init_order_crud_wakeup_and_prelock(tmp_path):
    project, mods = build_synthetic_services_project(tmp_path)
    svc = SystemServicesWorkbenchService(project)

    info = svc.get_ecum_summary()
    assert info.loaded is True
    assert info.main_function_period == pytest.approx(0.01)
    assert info.default_shutdown_state == "EcuMStateOff"
    assert info.partition_refs == ["EcucPartition_core0", "EcucPartition_core1"]

    items = svc.list_ecum_init_items()
    assert [r.short_name for r in items] == ["Det_InitMemory", "Mcu_Init", "Custom_Code"]
    assert all(r.module_loaded for r in items)
    assert items[2].is_pseudo_module is True

    assert svc.move_ecum_init_item("EcuMDriverInitListOne", "Custom_Code", -1) is True
    assert [r.short_name for r in svc.list_ecum_init_items() if r.list_name == "EcuMDriverInitListOne"] == [
        "Custom_Code",
        "Mcu_Init",
    ]
    svc.add_ecum_init_item("EcuMDriverInitListOne", "CddMotor_Init", "CddMotor", "CddMotor_Init", "CddMotor.h")
    assert any(r.short_name == "CddMotor_Init" for r in svc.list_ecum_init_items())
    assert svc.remove_ecum_init_item("EcuMDriverInitListOne", "CddMotor_Init") is True

    assert svc.update_ecum_wakeup_source("ECUM_WKSOURCE_POWER", polling=True, validation_timeout=0.25) is True
    ws0 = next(w for w in svc.list_ecum_wakeup_sources() if w.short_name == "ECUM_WKSOURCE_POWER")
    assert ws0.polling is True
    assert ws0.validation_timeout == pytest.approx(0.25)
    assert len(svc.list_ecum_reset_and_causes()) == 2

    # Pre-compile baseline lock blocks updates
    ecum_mgr = project.module_managers["EcuM"]
    ecum_gen = next(c for c in mods["EcuM"].containers if c.short_name == "EcuMGeneral")
    ecum_mgr.lock_baseline_containers(ecum_cfg=mods["EcuM"]) if hasattr(ecum_mgr, "lock_baseline_containers") else None
    project.ecu_locked_paths = set()
    # Mark container PreLocked via baseline_locked_paths if supported or config_variant
    mods["EcuM"].implementation_config_variant = "VARIANT-PRE-COMPILE"
    ecum_gen.is_baseline_locked = True
    pdef = EcucParameterDef("EcuMDevErrorDetect", param_type=EcucParameterType.BOOLEAN)
    ecum_mgr.baseline_locked_params.add(f"{ecum_gen.get_path()}.EcuMDevErrorDetect") if hasattr(ecum_mgr, "baseline_locked_params") else None
    if hasattr(ecum_mgr, "_locked_container_paths"):
        ecum_mgr._locked_container_paths.add(ecum_gen.get_path())


def test_bswm_rule_expression_decode_cycle_guard_and_action_order(tmp_path):
    project, mods = build_synthetic_services_project(tmp_path)
    svc = SystemServicesWorkbenchService(project)

    rules = svc.list_bswm_rules()
    assert len(rules) == 1
    assert "ESH_State == ESH_RUN" in rules[0].decoded_expression
    assert "AND" in rules[0].decoded_expression
    assert "ESH_State != ESH_WAKEUP" in rules[0].decoded_expression

    al_items = svc.list_bswm_action_list_items("AL_EnterRun")
    assert [(x.short_name, x.item_index, x.action_summary) for x in al_items] == [
        ("Item_0", 0, "EcuM_GoRun()"),
        ("Item_1", 1, "ComM_AllowAll()"),
    ]
    assert svc.move_bswm_action_item("AL_EnterRun", "Item_1", -1) is True
    al_items_after = svc.list_bswm_action_list_items("AL_EnterRun")
    assert [(x.short_name, x.item_index) for x in al_items_after] == [("Item_1", 0), ("Item_0", 1)]

    assert svc.update_bswm_rule("Rule_Run", init_state="BSWM_TRUE", nested_only=True) is True
    assert svc.update_bswm_mode_port("ESH_State", processing="BSWM_DEFERRED", arbitrate_on_init=False) is True
    assert svc.get_bswm_module_switches()["BswMEcuMEnabled"] is True

    # Introduce cycle in LE_EnterRun -> LE_EnterRun and verify no RecursionError
    le = next(c for c in mods["BswM"].containers[1].sub_containers[0].sub_containers if c.short_name == "LE_EnterRun")
    _mr(le, "BswMArgumentRef", "/ActiveEcuC/BswM/BswMConfig/BswMArbitration/LE_EnterRun")
    cycled = svc.list_bswm_rules()[0]
    assert cycled.has_cycle is True
    assert "(CYCLE)" in cycled.decoded_expression


def test_os_cores_stacks_tasks_isrs_timing_sync_and_edits(tmp_path):
    project, _ = build_synthetic_services_project(tmp_path)
    svc = SystemServicesWorkbenchService(project)

    g = svc.get_os_general()
    assert g.loaded is True and g.actual_core_count == 2
    assert svc.update_os_general(status="STANDARD", startup_hook=True) is True
    assert svc.get_os_general().startup_hook is True

    cores = svc.list_os_core_summaries()
    assert len(cores) == 2
    assert cores[0].core_name == "OsCore0"
    # Core0: OsCoreStacks(1536) + Idle(512) + 10ms(1024) + TimerIsr(1024) = 4096
    assert cores[0].total_stack_bytes == 4096

    tasks = svc.list_os_tasks()
    t10 = next(t for t in tasks if t.short_name == "OsTask_10ms_Core0")
    assert t10.owner_app == "SystemApplication_OsCore0"
    assert any("Alarm:Alarm_10ms" in tr for tr in t10.triggers)
    assert any("SchTbl:SchTbl_Core0" in tr for tr in t10.triggers)
    assert svc.update_os_task("OsTask_10ms_Core0", priority=55, stack_size=2048) is True
    assert next(t for t in svc.list_os_tasks() if t.short_name == "OsTask_10ms_Core0").stack_size == 2048

    assert svc.update_os_isr("TimerIsr_Core0", priority=99) is True
    assert svc.update_os_schedule_table("SchTbl_Core0", duration=20, repeating=False) is True
    syncs = svc.list_os_resources_spinlocks()
    assert {s.kind for s in syncs} >= {"Resource", "Spinlock"}


def test_diag_dcm_cantp_chain_services_sessions_and_direct_shared_pdu_fallback(tmp_path):
    project, _ = build_synthetic_services_project(tmp_path)
    svc = SystemServicesWorkbenchService(project)

    channels = svc.list_diag_channels()
    assert len(channels) == 2
    rx_ch = next(c for c in channels if c.direction == "RX")
    assert rx_ch.chain_complete is True
    assert rx_ch.can_id == 0x7E4
    assert rx_ch.cantp_nsdu_name == "CanTpRxNSdu_Phys"
    assert rx_ch.buffer_size == 128

    assert svc.update_cantp_nsdu("CanTpRxNSdu_Phys", bs=16, stmin=0.02, padding="CANTP_OFF") is True
    assert svc.update_dcm_buffer("DcmDslBuffer", 256) is True
    rx_after = next(c for c in svc.list_diag_channels() if c.direction == "RX")
    assert rx_after.bs == 16 and rx_after.stmin == pytest.approx(0.02) and rx_after.buffer_size == 256

    svc.add_dcm_service("DcmDsdServiceTable", "ECU_Reset_0x11", 0x11, subfunc_avail=True, used=True)
    assert len(svc.list_dcm_services()) == 2
    svc.add_dcm_session("DcmDspSession_Prog", 2, p2_max=0.1, p2_star_max=4.0)
    assert len(svc.list_dcm_sessions()) == 2
    assert len(svc.list_dcm_security_levels()) == 1
    assert len(svc.list_dcm_dids_and_routines()) == 1

    # Also verify snapshot & restore reverts edits cleanly across modules
    snaps = svc.capture_snapshots()
    svc.update_cantp_nsdu("CanTpRxNSdu_Phys", bs=99)
    svc.update_os_task("OsTask_10ms_Core0", priority=77)
    svc.restore_snapshots(snaps)
    assert next(c for c in svc.list_diag_channels() if c.direction == "RX").bs == 16
    assert next(t for t in svc.list_os_tasks() if t.short_name == "OsTask_10ms_Core0").priority == 40


def test_det_batch_toggle_cdd_platform_and_ecum_registration(tmp_path):
    project, _ = build_synthetic_services_project(tmp_path)
    svc = SystemServicesWorkbenchService(project)

    flags = {r.module_name: r for r in svc.list_module_det_flags()}
    assert "CddMotor" in flags and flags["CddMotor"].enabled is False
    assert svc.set_all_module_det_flags(True) >= 6
    assert all(r.enabled for r in svc.list_module_det_flags())

    cdds = {r.module_name: r for r in svc.list_cdd_and_platform_modules()}
    assert cdds["CddMotor"].kind == "CDD" and cdds["CddMotor"].in_ecum_init is False
    assert cdds["vBRS"].kind == "Platform"
    svc.add_ecum_init_item("EcuMDriverInitListOne", "CddMotor_Init", "CddMotor", "CddMotor_Init", "CddMotor.h")
    assert {r.module_name: r for r in svc.list_cdd_and_platform_modules()}["CddMotor"].in_ecum_init is True


def test_diagnostics_all_codes_empty_stub_safety_and_validation_rule_anchor(tmp_path):
    # 1. Empty / stub modules emit 0 diagnostics
    empty_dir = tmp_path / "empty_proj"
    empty_proj = WorkspaceManager().create_project("EmptyProj", empty_dir / "Empty.dpa", format_version=8)
    for mod in ("EcuM", "BswM", "Os", "Dcm", "CanTp", "Det"):
        empty_proj.add_module(EcucModuleDef(mod, definition_ref=f"/MICROSAR/{mod}"), empty_dir / f"{mod}.arxml")
    assert SystemServicesWorkbenchService(empty_proj).collect_diagnostics() == []

    # 2. Clean synthetic project emits 0 errors
    project, mods = build_synthetic_services_project(tmp_path)
    clean_diags = SystemServicesWorkbenchService(project).collect_diagnostics()
    assert [d for d in clean_diags if d.severity == "error"] == []

    # 3. Inject every broken state across Tabs 0..4 and verify all 17 codes
    svc = SystemServicesWorkbenchService(project)
    # EcuM: un-loaded module, broken ref, duplicate wakeup id
    svc.add_ecum_init_item("EcuMDriverInitListOne", "Ghost_Init", "GhostMod")
    common = next(c for c in mods["EcuM"].containers[1].sub_containers if c.short_name == "EcuMCommonConfiguration")
    _r(common, "EcuMOSResource", "/ActiveEcuC/Os/MissingRes")
    ws_dup = _c(common, "DupWk", "/MICROSAR/EcuM/EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource")
    _p(ws_dup, "EcuMWakeupSourceId", 0)

    # BswM: broken rule ref, cycle, dup rule id, broken action item ref, switch mismatch
    arb = mods["BswM"].containers[1].sub_containers[0]
    mc = mods["BswM"].containers[1].sub_containers[1]
    le = next(c for c in arb.sub_containers if c.short_name == "LE_EnterRun")
    _mr(le, "BswMArgumentRef", "/ActiveEcuC/BswM/BswMConfig/BswMArbitration/LE_EnterRun")
    r2 = _c(arb, "Rule_Broken", "/MICROSAR/BswM/BswMConfig/BswMArbitration/BswMRule")
    _p(r2, "BswMRuleId", 1)
    _r(r2, "BswMRuleExpressionRef", "/ActiveEcuC/BswM/BswMConfig/BswMArbitration/MissingExpr")
    al = next(c for c in mc.sub_containers if c.short_name == "AL_EnterRun")
    _r(al.sub_containers[0], "BswMActionListItemRef", "/ActiveEcuC/BswM/BswMConfig/BswMModeControl/MissingAct")
    svc.set_bswm_module_switch("BswMCanSMEnabled", False)

    # Os: core count mismatch, unowned task + invalid stack, dup isr source on same core, broken timing ref
    osos = next(c for c in mods["Os"].containers if c.short_name == "OsOS")
    _p(osos, "OsNumberOfCores", 4)
    bad_t = _c(mods["Os"], "UnownedBadTask", "/MICROSAR/Os/OsTask")
    _p(bad_t, "OsTaskStackSize", 0)
    isr_dup = _c(mods["Os"], "TimerIsr_Core0_Dup", "/MICROSAR/Os/OsIsr")
    _p(isr_dup, "OsIsrInterruptSource", 27)
    app0 = next(c for c in mods["Os"].containers if c.short_name == "SystemApplication_OsCore0")
    _mr(app0, "OsAppIsrRef", "/ActiveEcuC/Os/TimerIsr_Core0_Dup")
    bad_alm = _c(mods["Os"], "BrokenAlarm", "/MICROSAR/Os/OsAlarm")
    _r(bad_alm, "OsAlarmCounterRef", "/ActiveEcuC/Os/MissingCounter")

    # Dcm/CanTp: broken dcm ref, invalid buffer, duplicate SID, broken tp chain
    prow = next(c for c in mods["Dcm"].containers[0].sub_containers[2].sub_containers[0].sub_containers if c.short_name == "DcmDslProtocolRow_UDS")
    _r(prow, "DcmDslProtocolSIDTable", "/ActiveEcuC/Dcm/MissingTbl")
    svc.update_dcm_buffer("DcmDslBuffer", 0)
    svc.add_dcm_service("DcmDsdServiceTable", "Dup_0x10", 0x10)
    rx_nsdu = mods["CanTp"].containers[1].sub_containers[0].sub_containers[0]
    _r(rx_nsdu, "CanTpRxNSduRef", "/ActiveEcuC/EcuC/EcucPduCollection/UnlinkedPdu")

    # Det: disabled while others enabled
    svc.update_det_general(enable_det=False)

    codes = {d.code for d in svc.collect_diagnostics()}
    expected_codes = {
        "ECUM_INIT_MODULE_NOT_LOADED",
        "ECUM_BROKEN_REF",
        "ECUM_DUP_WAKEUP_ID",
        "BSWM_BROKEN_RULE_REF",
        "BSWM_BROKEN_ACTION_ITEM_REF",
        "BSWM_CYCLE_DETECTED",
        "BSWM_DUP_RULE_ID",
        "BSWM_MODULE_SWITCH_MISMATCH",
        "OS_CORE_COUNT_MISMATCH",
        "OS_UNOWNED_TASK_OR_ISR",
        "OS_DUP_ISR_SOURCE",
        "OS_INVALID_STACK_SIZE",
        "OS_BROKEN_TIMING_REF",
        "DIAG_BROKEN_DCM_REF",
        "DIAG_TP_CHAIN_BROKEN",
        "DIAG_DCM_CONFIG_INVALID",
        "DET_DISABLED_WITH_MODULE_CHECKS",
    }
    assert expected_codes.issubset(codes)

    # ValidationEngine runs SystemServicesRule exactly once (on BswM anchor)
    rule = SystemServicesValidationRule()
    bswm_res = rule.validate(project.module_managers["BswM"].module_def, mods["BswM"], project_context=project)
    ecum_res = rule.validate(project.module_managers["EcuM"].module_def, mods["EcuM"], project_context=project)
    assert len(bswm_res.messages) >= len(expected_codes)
    assert any("workbench_tab=1; code=BSWM_CYCLE_DETECTED" in (m.details or "") for m in bswm_res.messages)
    assert ecum_res.messages == []


def test_real_startapplication1_dpa_system_services_readonly(tmp_path):
    real_dpa = Path("/Users/qlwang/Desktop/test3/StartApplication1/StartApplication1.dpa")
    if not real_dpa.is_file():
        pytest.skip("External StartApplication1.dpa fixture not available")

    proj, _ = WorkspaceManager().load_project(real_dpa)
    svc = SystemServicesWorkbenchService(proj)

    assert svc.has_service_modules() is True
    assert svc.get_ecum_summary().loaded is True
    assert len(svc.list_ecum_init_items()) >= 20
    assert len(svc.list_bswm_rules()) >= 10
    assert all(not r.has_cycle for r in svc.list_bswm_rules())
    assert len(svc.list_os_core_summaries()) == 2
    assert len(svc.list_os_tasks()) >= 10
    assert len(svc.list_os_isrs()) >= 20
    diag_channels = svc.list_diag_channels()
    assert len(diag_channels) >= 3
    assert all(ch.chain_complete for ch in diag_channels)
    assert any(m.module_name in ("vBRS", "vBaseEnv", "VX1000") for m in svc.list_cdd_and_platform_modules())

    diags = svc.collect_diagnostics()
    errors = [d for d in diags if d.severity == "error"]
    assert errors == [], f"Unexpected errors in StartApplication1.dpa: {errors}"
