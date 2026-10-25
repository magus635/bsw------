"""Generate Os code from a copy of the T1 project: as it is (Cortex-R52) or cut down to a
single-core SC300 example.

The SC300 example is tied to the layout of T1: it names T1's objects. T1 itself is only read.
"""
import logging
import shutil
from pathlib import Path
from typing import Dict

# T1 objects that do not exist on the SC300 example: the second core, the memory layout (SC300 has
# none), the IOC and one CAN ISR (only two Cat2 ISRs are needed)
DROP_TYPES = {"MemorySection", "OsMemoryMap", "MemoryBlock", "MemoryRegion", "SystemModeStack", "OsIoc"}
DROP_NAMES = {"OsCore1", "SystemApplication_OsCore1", "OsApplication_Trusted_Core1", "Idle_Task_Core1",
              "CounterIsr_SystemTimer_core1", "SystemTimer_core1", "XSignalIsr_OsCore0", "XSignalIsr_OsCore1",
              "Default_BSW_Async_Task_Core1", "StartApplication_Appl_Task_Core1", "Default_Init_Task_Core1",
              "Default_Init_Task_Core1_Trusted", "CAN_00_RXFIFO_ISR"}
MCAL_MODULES = ("Can", "Mcu", "Port", "Resource", "Arti")


def _load(t1: Path, work: Path):
    """Copy T1 (without generated code) to work and load it; the copy is what gets modified"""
    from autosar_configurator.core.workspace_manager import WorkspaceManager

    logging.disable(logging.ERROR)
    if work.exists():
        shutil.rmtree(work)
    shutil.copytree(t1, work, ignore=shutil.ignore_patterns("generateCode", "*.7z"))
    project, errors = WorkspaceManager().load_project(work / "t1.dpa")
    if errors:
        raise RuntimeError(f"T1 did not load: {errors}")
    return project


def _generate_os(project, work: Path, out: Path) -> Path:
    from autosar_configurator.generator.generator import CodeGenerator

    all_configs = {n: (m.module_def, m.configuration) for n, m in project.module_managers.items()
                   if m.module_def and m.configuration}
    manager = project.module_managers["Os"]
    generator = CodeGenerator(manager.module_def, manager.configuration,
                              project_template_dir=work / "templates", all_configurations=all_configs,
                              selected_chip=project.selected_chip, ecu_resources=dict(project.ecu_resources))
    if out.exists():
        shutil.rmtree(out)
    if not generator.generate_all(out, force=True, variant="Default"):
        raise RuntimeError(f"Os code generation failed: {generator.last_status}")
    return out / "Os" / "Default" / "Os"


def generate_t1(t1: Path, work: Path, out: Path) -> Path:
    """Os code of T1 as configured (its selected chip); returns the directory of the generated Os"""
    project = _load(t1, work)
    return _generate_os(project, work, out)


def _kind(container) -> str:
    return container.definition_ref.rstrip("/").rsplit("/", 1)[-1]


def _walk(containers):
    for c in containers:
        yield c
        yield from _walk(c.sub_containers)


def _target(ref) -> str:
    return (ref.value_ref or "").rstrip("/").rsplit("/", 1)[-1]


def generate_sc300_example(t1: Path, work: Path, out: Path) -> Path:
    """Single-core SC300 Os configuration cut down from T1; returns the generated Os directory"""
    project = _load(t1, work)
    for module in MCAL_MODULES:
        if module in project.module_managers:
            project.remove_module(module)

    os_cfg = project.module_managers["Os"].configuration
    dropped = {c.short_name for c in os_cfg.containers if _kind(c) in DROP_TYPES or c.short_name in DROP_NAMES}
    # the alarms of a removed application go with it
    for c in os_cfg.containers:
        if c.short_name in dropped and _kind(c) == "OsApplication":
            refs = list(c.multi_reference_values.get("OsAppAlarmRef", []))
            if "OsAppAlarmRef" in c.reference_values:
                refs.append(c.reference_values["OsAppAlarmRef"])
            dropped.update(_target(r) for r in refs)
    os_cfg.containers = [c for c in os_cfg.containers if c.short_name not in dropped]
    for c in _walk(os_cfg.containers):
        for name in [n for n, r in c.reference_values.items() if _target(r) in dropped]:
            del c.reference_values[name]
        for name, refs in list(c.multi_reference_values.items()):
            c.multi_reference_values[name] = [r for r in refs if _target(r) not in dropped]

    objects: Dict[str, object] = {c.short_name: c for c in _walk(os_cfg.containers)}

    def setp(name: str, param: str, value) -> None:
        objects[name].parameter_values[param].value = value

    setp("OsOS", "OsNumberOfCores", 1)
    setp("OsOS", "OsUseArti", False)
    setp("OsOS", "OsScalabilityClass", "SC1")
    # SysTick (exception 15) drives the system counter; ISR priorities are 1..7 (3 bits)
    setp("CounterIsr_SystemTimer_core0", "OsIsrInterruptSource", 15)
    setp("CounterIsr_SystemTimer_core0", "OsIsrPriority", 6)
    setp("CounterIsr_SystemTimer_core0", "OsIsrInitialEnableInterruptSource", True)
    setp("CounterIsr_SystemTimer_core0", "OsIsrHandler", "Isr_OsCounter_PitService")
    setp("SystemTimer_core0", "OsCounterTicksPerBase", 25000)
    for name, source, priority, handler in (("CAN_00_RX_ISR", 16, 4, "Test_Isr2_Low"),
                                            ("CAN_00_TX_ISR", 17, 3, "Test_Isr2_High")):
        setp(name, "OsIsrInterruptSource", source)
        setp(name, "OsIsrPriority", priority)
        setp(name, "OsIsrHandler", handler)
        setp(name, "OsIsrInitialEnableInterruptSource", True)

    # Idle task lowest; the sync task uses the resource of the async task (resource ceiling test)
    setp("Idle_Task_Core0", "OsTaskPriority", 0)
    async_task = objects["Default_BSW_Async_Task_Core0"]
    shared = (async_task.multi_reference_values.get("OsTaskResourceRef")
              or [async_task.reference_values["OsTaskResourceRef"]])[0]
    import copy
    ref = copy.copy(shared)
    ref.target = None
    objects["Default_BSW_Sync_Task"].multi_reference_values.setdefault("OsTaskResourceRef", []).append(ref)
    # fully preemptive tasks for the ReleaseResource and end-of-ISR preemption checks
    setp("Default_BSW_Async_Task_Core0", "OsTaskSchedule", "FULL")
    setp("StartApplication_Appl_Task_Core0", "OsTaskSchedule", "FULL")

    project.selected_chip = "SC300"
    project.chip_changed()
    project.apply_chip_selectors()
    return _generate_os(project, work, out)
