"""Synthetic THA6-style Os configuration for rendering the Os_Arti.arxml template.

The container/parameter names follow the THA6 Os plugin as seen in
output/Os/Os_PBcfg.c (OsOS/OsUseArti, OsCoreIdMappingConfig/OsPhysicalCoreId,
OsApplication/OsApplicationCoreRef, ...). It is NOT the real Os definition;
replace it with tests/fixtures/os_arti/ once the real files are available.

Layout (2 cores):
  OsCoreIdMappingConfig_0 (phys 0) <- App_Core0: Task_A, Task_B, Isr_Timer0
  OsCoreIdMappingConfig_1 (phys 1) <- App_Core1: Task_C, Isr_Timer1 ; Isr_Cat1 (CATEGORY_1)
"""
from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.model.definition_model import (
    EcucContainerDef, EcucModuleDef, EcucParameterDef, EcucParameterType, EcucReferenceDef)

OS = "/AUTOSAR/EcucDefs/Os"
T = EcucParameterType
ARTI_CLASSES = ("Application", "Task", "Cat2Isr", "ServiceCalls", "Spinlock", "Hook")

TASKS = [  # name, priority, stack, type, core
    ("Task_A", 5, 1024, "BASIC", 0),
    ("Task_B", 2, 2048, "EXTENDED", 0),
    ("Task_C", 7, 512, "BASIC", 1),
]
ISRS = [  # name, category, stack, core
    ("Isr_Timer0", "CATEGORY_2", 256, 0),
    ("Isr_Cat1", "CATEGORY_1", 128, 1),
    ("Isr_Timer1", "CATEGORY_2", 256, 1),
    ("Isr_Cat1_Last", "CATEGORY_1", 128, 0),  # last ISR is CATEGORY_1: NO_ISR must still be count(OsIsr)
]


def _p(container, name, ptype, **kw):
    container.add_parameter(EcucParameterDef(
        short_name=name, param_type=ptype, definition_ref=f"{container.definition_ref}/{name}",
        config_class="PRE-COMPILE", **kw))


def _r(container, name, dest, upper=1):
    container.add_reference(EcucReferenceDef(
        short_name=name, destination_ref=dest, upper_multiplicity=upper,
        definition_ref=f"{container.definition_ref}/{name}"))


def _sub(parent, name):
    c = EcucContainerDef(short_name=name, definition_ref=f"{parent.definition_ref}/{name}",
                         lower_multiplicity=0, upper_multiplicity=1)
    parent.add_sub_container(c)
    return c


def _c(module, name, upper=-1, lower=0):
    c = EcucContainerDef(short_name=name, definition_ref=f"{OS}/{name}",
                         lower_multiplicity=lower, upper_multiplicity=upper)
    module.add_container(c)
    return c


def build_os_def():
    m = EcucModuleDef(short_name="Os", definition_ref=OS)
    # module-level parameter of the plugin Os.xdm; the templates test it with
    # OsResourceSubderivative != 'Os_SC300', which is false when the node does not exist
    m.parameters["OsResourceSubderivative"] = EcucParameterDef(
        short_name="OsResourceSubderivative", param_type=T.ENUMERATION,
        definition_ref=f"{OS}/OsResourceSubderivative", config_class="PRE-COMPILE",
        literals=["Os_THA6206", "Os_THA6412", "Os_SC300"], default_value="Os_THA6206")
    os_os = _c(m, "OsOS", upper=1, lower=1)
    _p(os_os, "OsNumberOfCores", T.INTEGER)
    _p(os_os, "OsUseArti", T.BOOLEAN)
    _p(os_os, "OsStatus", T.ENUMERATION, literals=["STANDARD", "EXTENDED"])
    _p(os_os, "OsScalabilityClass", T.ENUMERATION, literals=["SC1", "SC2", "SC3", "SC4"])
    _p(os_os, "OsStackMonitoring", T.BOOLEAN)
    _p(os_os, "OsUseResScheduler", T.BOOLEAN)
    # vendor parameters of add-arti-hook-tracing (plugin Os.xdm)
    _p(os_os, "OsVendorArtiStateModel", T.ENUMERATION, literals=["ENHANCED", "STANDARD"], default_value="ENHANCED")
    for cls in ARTI_CLASSES:  # defaults as in Os.xdm: everything on except the service calls
        _p(os_os, f"OsVendorArtiTrace{cls}", T.BOOLEAN, default_value=cls != "ServiceCalls")
    os_hooks = _sub(os_os, "OsHooks")
    for hook in ("OsErrorHook", "OsStartupHook", "OsShutdownHook", "OsProtectionHook", "OsPreTaskHook",
                 "OsPostTaskHook"):
        _p(os_hooks, hook, T.BOOLEAN)
    core = _c(m, "OsCoreIdMappingConfig")
    _p(core, "OsPhysicalCoreId", T.INTEGER)
    _r(core, "OsCoreId", "/AUTOSAR/EcucDefs/EcuC/EcucHardware/EcucCoreDefinition")
    _r(core, "OsKernelApplication", f"{OS}/OsApplication")
    app = _c(m, "OsApplication")
    _r(app, "OsApplicationCoreRef", f"{OS}/OsCoreIdMappingConfig")
    _r(app, "OsAppTaskRef", f"{OS}/OsTask", upper=-1)
    _r(app, "OsAppIsrRef", f"{OS}/OsIsr", upper=-1)
    _r(app, "OsAppCounterRef", f"{OS}/OsCounter", upper=-1)
    _r(app, "OsAppAlarmRef", f"{OS}/OsAlarm", upper=-1)
    _r(app, "OsAppScheduleTableRef", f"{OS}/OsScheduleTable", upper=-1)
    app_hooks = _sub(app, "OsApplicationHooks")
    for hook in ("OsAppErrorHook", "OsAppStartupHook", "OsAppShutdownHook"):
        _p(app_hooks, hook, T.BOOLEAN)
    task = _c(m, "OsTask")
    _p(task, "OsTaskPriority", T.INTEGER)
    _p(task, "TaskStackSize", T.INTEGER)
    _p(task, "OsTaskType", T.ENUMERATION, literals=["BASIC", "EXTENDED"])
    _p(task, "OsTaskSchedule", T.ENUMERATION, literals=["NON", "FULL"])
    isr = _c(m, "OsIsr")
    _p(isr, "OsIsrCategory", T.ENUMERATION, literals=["CATEGORY_1", "CATEGORY_2"])
    _p(isr, "IsrStackSize", T.INTEGER)
    _c(m, "OsAppMode")
    _c(m, "OsCounter")
    alarm = _c(m, "OsAlarm")
    _r(alarm, "OsAlarmCounterRef", f"{OS}/OsCounter")
    res = _c(m, "OsResource")
    _p(res, "OsResourceProperty", T.ENUMERATION, literals=["STANDARD", "INTERNAL", "LINKED"])
    _p(res, "OsResourceLinkedToResScheduler", T.BOOLEAN)
    _r(res, "OsResourceCoreRef", f"{OS}/OsCoreIdMappingConfig")
    _r(res, "OsResourceLinkedResourceRef", f"{OS}/OsResource")
    event = _c(m, "OsEvent")
    _p(event, "OsEventMask", T.INTEGER)
    _c(m, "OsScheduleTable")
    spin = _c(m, "OsSpinlock")
    _p(spin, "OsSpinlockLockMethod", T.ENUMERATION, literals=["LOCK_NOTHING", "LOCK_ALL_INTERRUPTS"])
    return m


def build_os_config(use_arti=True, n_cores=2, logical_ids=None, arti=None):
    """Returns (module_def, ConfigurationManager) with the layout in the module docstring.

    arti: optional {OsOS parameter: value} for the add-arti-hook-tracing vendor parameters; parameters
    not given are left out of the configuration, so the templates must apply the Os.xdm defaults."""
    m = build_os_def()
    mgr = ConfigurationManager(m)
    c = m.containers
    new = mgr.create_container_instance

    os_os = new(c["OsOS"], None, "OsOS")
    mgr.set_parameter_value(os_os, "OsNumberOfCores", n_cores)
    mgr.set_parameter_value(os_os, "OsUseArti", use_arti)
    mgr.set_parameter_value(os_os, "OsStatus", "EXTENDED")
    mgr.set_parameter_value(os_os, "OsScalabilityClass", "SC3")
    mgr.set_parameter_value(os_os, "OsStackMonitoring", True)
    for name, value in (arti or {}).items():
        mgr.set_parameter_value(os_os, name, value)
    os_hooks = new(c["OsOS"].sub_containers["OsHooks"], os_os, "OsHooks")
    for hook, on in (("OsErrorHook", True), ("OsStartupHook", True), ("OsShutdownHook", False),
                     ("OsProtectionHook", False)):
        mgr.set_parameter_value(os_hooks, hook, on)

    for i in range(n_cores):
        core = new(c["OsCoreIdMappingConfig"], None, f"OsCoreIdMappingConfig_{i}")
        mgr.set_parameter_value(core, "OsPhysicalCoreId", i)
        core.set_reference_value("OsCoreId",
                                 f"/EcuC/EcuC/EcucHardware/EcucCoreDefinition_{(logical_ids or {}).get(i, i)}",
                                 c["OsCoreIdMappingConfig"].references["OsCoreId"].definition_ref)
        if i == 0:  # core 0 has a kernel application, the other cores do not (both Os_AppCommon.m branches)
            core.set_reference_value("OsKernelApplication", "/Os/Os/App_Core0",
                                     c["OsCoreIdMappingConfig"].references["OsKernelApplication"].definition_ref)

    for name, prio, stack, ttype, _ in TASKS:
        t = new(c["OsTask"], None, name)
        mgr.set_parameter_value(t, "OsTaskPriority", prio)
        mgr.set_parameter_value(t, "TaskStackSize", stack)
        mgr.set_parameter_value(t, "OsTaskType", ttype)
        mgr.set_parameter_value(t, "OsTaskSchedule", "FULL")
    for name, cat, stack, _ in ISRS:
        i = new(c["OsIsr"], None, name)
        mgr.set_parameter_value(i, "OsIsrCategory", cat)
        mgr.set_parameter_value(i, "IsrStackSize", stack)

    app_def = c["OsApplication"]
    for core_idx in range(n_cores):
        app = new(app_def, None, f"App_Core{core_idx}")
        app.set_reference_value("OsApplicationCoreRef", f"/Os/Os/OsCoreIdMappingConfig_{core_idx}",
                                app_def.references["OsApplicationCoreRef"].definition_ref)
        k = 0
        for name, *_rest, core in TASKS:
            if core == core_idx:
                app.add_multi_reference_value("OsAppTaskRef", f"/Os/Os/{name}",
                                              app_def.references["OsAppTaskRef"].definition_ref, k)
                k += 1
        k = 0
        for name, *_rest, core in ISRS:
            if core == core_idx:
                app.add_multi_reference_value("OsAppIsrRef", f"/Os/Os/{name}",
                                              app_def.references["OsAppIsrRef"].definition_ref, k)
                k += 1
        # Objects that take object numbers but are not described by ARTI: counted before the next application
        hooks = new(app_def.sub_containers["OsApplicationHooks"], app, "OsApplicationHooks")
        if core_idx == 0:
            for ref, target in (("OsAppCounterRef", "SystemTick"), ("OsAppAlarmRef", "Alarm_10ms"),
                                ("OsAppScheduleTableRef", "Sch_Main")):
                app.add_multi_reference_value(ref, f"/Os/Os/{target}", app_def.references[ref].definition_ref, 0)
            mgr.set_parameter_value(hooks, "OsAppErrorHook", True)
        else:
            mgr.set_parameter_value(hooks, "OsAppStartupHook", True)
            mgr.set_parameter_value(hooks, "OsAppShutdownHook", True)

    for mode in ("OSDEFAULTAPPMODE", "OSALLRUNNINGMODE"):
        new(c["OsAppMode"], None, mode)
    new(c["OsCounter"], None, "SystemTick")
    alarm = new(c["OsAlarm"], None, "Alarm_10ms")
    alarm.set_reference_value("OsAlarmCounterRef", "/Os/Os/SystemTick",
                              c["OsAlarm"].references["OsAlarmCounterRef"].definition_ref)
    res = new(c["OsResource"], None, "Res_Shared")
    mgr.set_parameter_value(res, "OsResourceProperty", "STANDARD")
    mgr.set_parameter_value(res, "OsResourceLinkedToResScheduler", False)
    res.set_reference_value("OsResourceCoreRef", "/Os/Os/OsCoreIdMappingConfig_0",
                            c["OsResource"].references["OsResourceCoreRef"].definition_ref)
    event_1 = new(c["OsEvent"], None, "Event_Wake")
    mgr.set_parameter_value(event_1, "OsEventMask", 1)
    new(c["OsScheduleTable"], None, "Sch_Main")
    spin_1 = new(c["OsSpinlock"], None, "Spin_Shared")
    mgr.set_parameter_value(spin_1, "OsSpinlockLockMethod", "LOCK_ALL_INTERRUPTS")
    return m, mgr
