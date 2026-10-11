"""ArtiHardware / ArtiOs containers, from AUTOSAR CP R21-11 SWS OS, section 10.4."""
from tools.arti.gen_arti_def import (BASE, N, container, ref, string_param, func_param, int_param, enum_param)

G = BASE + "/ArtiGeneric"
V = BASE + "/ArtiValues"
OS = BASE + "/ArtiOs"
HW = BASE + "/ArtiHardware"
GEN_CLS = G + "/ArtiGenericComponentClass"
GEN_INST = G + "/ArtiGenericComponentInstance"
CLS_PARAM = V + "/ArtiObjectClassParameter"
INST_PARAM = V + "/ArtiObjectInstanceParameter"
# EcucCoreDefinition: SWS OS names the type but gives no path. In the standard ECUC parameter
# definitions EcucHardware is a container of the EcuC module; THA6 Os configurations reference
# cores as /EcuC/EcuC/EcucHardware/EcucCoreDefinition_N (OsCoreIdMappingConfig/OsCoreId).
ECUC_CORE = "/AUTOSAR/EcucDefs/EcuC/EcucHardware/EcucCoreDefinition"
ECUC_OS = "/AUTOSAR/EcucDefs/Os"

U = 10 ** 9  # sentinel, unused


def refs(n, items):
    """items: (name, id, lo, hi, dest, description)"""
    return "".join(ref(n, nm, d, lo, hi, i, dst) for nm, i, lo, hi, dst, d in items)


def cls_p(name, i, d, lo=0, hi=1):
    return (name, i, lo, hi, CLS_PARAM, d)


def inst_p(name, i, d, lo=0, hi=1):
    return (name, i, lo, hi, INST_PARAM, d)


def valid(name, i, obj):
    return inst_p(name, i, f'Refers to the ArtiObjectInstanceParameter that contains the evaluation for the "validity" of this {obj}.')


def gen_cls(name, i, obj):
    return (name, i, 0, 1, GEN_CLS, f"Refers to an ArtiGenericComponentClass that extends the {obj}.")


def gen_inst(name, i, obj):
    return (name, i, 0, 1, GEN_INST, f"Refers to an ArtiGenericComponentInstance that extends the {obj}.")


def build_hardware():
    n = N
    cls = container(
        n + 1, "ArtiHardwareCoreClass",
        'Contains the layout of an ARTI "Core" object, extending the EcucCoreDefinition.', 0, 1, "ECUC_Arti_00062",
        refs=refs(n + 3, [
            cls_p("ArtiHardwareCoreClassCurrentApplicationRef", "ECUC_Arti_00054",
                  "Refers to the ArtiObjectClassParameter that defines the ArtiCurrentApplicationInstance parameter.", 1, 1),
            cls_p("ArtiHardwareCoreClassCurrentIsrRef", "ECUC_Arti_00056",
                  "Refers to the ArtiObjectClassParameter that defines the ArtiCurrentIsrInstance parameter."),
            cls_p("ArtiHardwareCoreClassCurrentTaskRef", "ECUC_Arti_00058",
                  "Refers to the ArtiObjectClassParameter that defines the ArtiCurrentTaskInstance parameter.", 1, 1),
            ("ArtiHardwareCoreClassGenericComponentRef", "ECUC_Arti_00064", 0, 1, GEN_CLS,
             "Refers to an ArtiGenericComponentClass that extends the core description."),
            cls_p("ArtiHardwareCoreClassLastErrorRef", "ECUC_Arti_00066",
                  "Refers to the ArtiObjectClassParameter that defines the ArtiLastErrorInstance parameter."),
            cls_p("ArtiHardwareCoreClassRunningTaskPriorityRef", "ECUC_Arti_00094",
                  "Refers to the ArtiObjectClassParameter that defines the ArtiHwCoreInstanceRunningTaskPriority parameter."),
        ]))
    inst = container(
        n + 1, "ArtiHardwareCoreInstance",
        'Represents an instance of an ARTI "Core" object, extending the EcucCoreDefinition. When using ARTI for debugging or hardware based tracing, this is mandatory (i.e. multiplicity 1..*), else optional.',
        0, "*", "ECUC_Arti_00063",
        params=int_param(n + 3, "ArtiHardwareCoreInstanceCoreId",
                         'This parameter represents the "CoreID" as given by the OS, returned by GetCoreID().', 1, 1,
                         "ECUC_Arti_00091", 0, "18446744073709551615"),
        refs=refs(n + 3, [
            inst_p("ArtiHardwareCoreInstanceCurrentApplicationRef", "ECUC_Arti_00055",
                   'Refers to the ArtiObjectInstanceParameter that contains the evaluation for the "current application" that is running on this core.', 1, 1),
            inst_p("ArtiHardwareCoreInstanceCurrentIsrRef", "ECUC_Arti_00057",
                   'Refers to the ArtiObjectInstanceParameter that contains the evaluation for the "current ISR" that is running on this core.'),
            inst_p("ArtiHardwareCoreInstanceCurrentTaskRef", "ECUC_Arti_00059",
                   'Refers to the ArtiObjectInstanceParameter that contains the evaluation for the "current task" that is running on this core.', 1, 1),
            ("ArtiHardwareCoreInstanceEcucCoreRef", "ECUC_Arti_00060", 1, 1, ECUC_CORE,
             "Refers to the EcucCoreDefinition of this core."),
            ("ArtiHardwareCoreInstanceGenericComponentRef", "ECUC_Arti_00065", 0, 1, GEN_INST,
             "Refers to an ArtiGenericComponentInstance that extends a core."),
            inst_p("ArtiHardwareCoreInstanceLastErrorRef", "ECUC_Arti_00067",
                   'Refers to the ArtiObjectInstanceParameter that contains the evaluation for the "last error" that happened on this core.'),
            inst_p("ArtiHardwareCoreInstanceRunningTaskPriorityRef", "ECUC_Arti_00095",
                   'Refers to the ArtiObjectInstanceParameter that contains the evaluation for the "running task priority" that is on this core.'),
            valid("ArtiHardwareCoreInstanceValidRef", "ECUC_Arti_00096", "ArtiHwCoreInstance"),
        ]))
    return container(
        n, "ArtiHardware", "The ArtiHardware container contains ARTI extensions to the EcucHardware module.",
        0, 1, "ECUC_Arti_00061", subs=cls + inst)


def build_os():
    n = N + 1
    s = n + 2   # indent of a sub-container's body items
    subs = []

    def add(name, eid, desc, lo, hi, params="", rs=None):
        subs.append(container(n, name, desc, lo, hi, eid, params=params, refs=refs(n + 2, rs) if rs else ""))

    add("ArtiOsAlarmClass", "ECUC_Arti_00108", "Contains the layout of an ArtiOsAlarm object.", 0, 1, rs=[
        gen_cls("ArtiOsAlarmClassGenericComponentClassRef", "ECUC_Arti_00110", "ArtiOsAlarmClass"),
        cls_p("ArtiOsAlarmClassStateRef", "ECUC_Arti_00111",
              'Refers to the ArtiObjectClassParameter that declares the attribute ArtiOsAlarmStateRef in ArtiOsAlarmInstances. This attribute specifies if an alarm is "RUNNING" or "STOPPED".')])
    add("ArtiOsAlarmInstance", "ECUC_Arti_00109",
        "Represents an instance of an ArtiOsAlarm object, extending the EcuC OsTaskAlarm.", 0, "*",
        params=(string_param(s + 2, "ArtiOsAlarmInstanceAction",
                             "This attribute provides a string containing the action of this alarm.", 0, 1, "ECUC_Arti_00112")
                + string_param(s + 2, "ArtiOsAlarmInstanceCounter",
                               "This attribute provides a string containing the name of the counter used by this alarm.",
                               0, 1, "ECUC_Arti_00113")),
        rs=[inst_p("ArtiOsAlarmInstanceAlarmTimeRef", "ECUC_Arti_00156",
                   "This attribute specifies how to evaluate the time until the alarm expires next. The time should be represented in seconds."),
            inst_p("ArtiOsAlarmInstanceCycleTimeRef", "ECUC_Arti_00114",
                   'This attribute specifies how to evaluate the cycle time for cyclic alarms. The value of "cycle time" is 0 for non-cyclic alarms.'),
            ("ArtiOsAlarmInstanceEcuCRef", "ECUC_Arti_00115", 0, 1, ECUC_OS + "/OsAlarm",
             "Refers to an EcuC OsAlarm that is beeing extended."),
            gen_inst("ArtiOsAlarmInstanceGenericComponentInstanceRef", "ECUC_Arti_00116", "ArtiOsAlarmInstance"),
            inst_p("ArtiOsAlarmInstanceStateRef", "ECUC_Arti_00117",
                   'Refers to the ArtiObjectInstanceParameter that contains the evaluation for the "state" of this alarm.'),
            valid("ArtiOsAlarmInstanceValidRef", "ECUC_Arti_00118", "alarm")])
    add("ArtiOsClass", "ECUC_Arti_00074", 'Contains the layout of an ARTI "Os" object, extending the EcuC OsOS.', 0, 1, rs=[
        cls_p("ArtiOsClassAppModeRef", "ECUC_Arti_00072",
              "Refers to the ArtiObjectClassParameter that defines the application mode of this OS.", 1, 1),
        ("ArtiOsClassGenericComponentRef", "ECUC_Arti_00076", 0, 1, GEN_CLS,
         "Refers to an ArtiGenericComponentClass that extends the OS."),
        cls_p("ArtiOsClassServiceTraceRef", "ECUC_Arti_00097",
              "Refers to the ArtiObjectClassParameter that defines the ArtiOsInstanceServiceTrace parameter. This attribute indicates the entry or exit of a service routine and the ID of this service routine.")])
    add("ArtiOsContextClass", "ECUC_Arti_00119", 'Contains the layout of an ARTI "OsContext" object.', 0, 1, rs=[
        gen_cls("ArtiOsContextClassGenericComponentClassRef", "ECUC_Arti_00121", "ArtiOsContext")])
    add("ArtiOsContextInstance", "ECUC_Arti_00120", 'Represents an instance of an "ArtiContext" object.', 0, "*", rs=[
        inst_p("ArtiOsContextInstanceAddressRef", "ECUC_Arti_00122",
               'Refers to the ArtiObjectInstanceParameter that contains the evaluation for the "address" of this ArtiOsContext.'),
        gen_inst("ArtiOsContextInstanceGenericComponentInstanceRef", "ECUC_Arti_00123", "ArtiOsContext"),
        inst_p("ArtiOsContextInstanceSizeRef", "ECUC_Arti_00124",
               'Refers to the ArtiObjectInstanceParameter that contains the evaluation for the "size" of this ArtiOsContext.'),
        valid("ArtiOsContextInstanceValidRef", "ECUC_Arti_00125", "ArtiOsContextInstance")])
    add("ArtiOsInstance", "ECUC_Arti_00080", 'Represents an instance of an ARTI "Os" object, extending the EcuC OsOS.', 0, 1, rs=[
        inst_p("ArtiOsInstanceAppModeRef", "ECUC_Arti_00073",
               'Refers to the ArtiObjectInstanceParameter that contains the evaluation for the "application mode" of this OS.', 1, 1),
        ("ArtiOsInstanceEcucRef", "ECUC_Arti_00075", 1, 1, ECUC_OS + "/OsOS", "Refers to the EcucDefs/Os/OsOS of this OS."),
        gen_inst("ArtiOsInstanceGenericComponentRef", "ECUC_Arti_00078", "OS"),
        ("ArtiOsInstanceHookRef", "ECUC_Arti_00079", 0, "*", V + "/ArtiHook", "Refers to a hook defined in the OS."),
        inst_p("ArtiOsInstanceServiceTraceRef", "ECUC_Arti_00098", "Refers to a hook defined in the OS."),
        valid("ArtiOsInstanceValidRef", "ECUC_Arti_00099", "ArtiOsInstance")])
    add("ArtiOsIsrClass", "ECUC_Arti_00081", 'Contains the layout of an ARTI "OsIsr" object, extending the EcuC OsIsr.', 0, 1, rs=[
        gen_cls("ArtiOsIsrClassGenericComponentRef", "ECUC_Arti_00084", "OsIsr")])
    add("ArtiOsIsrInstance", "ECUC_Arti_00086", 'Represents an instance of an ARTI "OsIsr" object, extending the EcuC OsIsr.',
        0, "*",
        params=(enum_param(s + 2, "ArtiOsIsrInstanceCategory",
                           "Specifies category of this ISR. If omitted the instance is related to a CATEGORY_2.", 0, 1,
                           "ECUC_Arti_00174", ["CATEGORY_1", "CATEGORY_2"])
                + func_param(s + 2, "ArtiOsIsrInstanceFunction", "This parameter represents the C function name of the ISR routine.",
                             0, 1, "ECUC_Arti_00083")
                + int_param(s + 2, "ArtiOsIsrInstanceId", 'This parameter represents the "ISRID" as given by the OS, returned by GetISRID().',
                            1, 1, "ECUC_Arti_00093", 0, "18446744073709551615")),
        rs=[("ArtiOsIsrInstanceEcucRef", "ECUC_Arti_00082", 0, 1, ECUC_OS + "/OsIsr", "Refers to the EcucDefs/Os/OsIsr of this ISR."),
            gen_inst("ArtiOsIsrInstanceGenericComponentRef", "ECUC_Arti_00085", "OsIsr"),
            valid("ArtiOsIsrInstanceValidRef", "ECUC_Arti_00157", "ArtiOsIsrInstance")])
    add("ArtiOsMessageContainerClass", "ECUC_Arti_00126",
        'Contains the layout of an ARTI "OsMessageContainer" object. The "OsMessageContainer" object represents an existing combination of OSEK messages.',
        0, 1, rs=[gen_cls("ArtiOsMessageContainerClassGenericComponentClassRef", "ECUC_Arti_00128", "ArtiOsMessageContainerClass")])
    add("ArtiOsMessageContainerInstance", "ECUC_Arti_00127", 'Represents an instance of an "ArtiMessageContainer" object.', 0, "*",
        params=(string_param(s + 2, "ArtiOsMessageContainerInstanceMsgName", "Name of the message.", 0, 1, "ECUC_Arti_00129")
                + string_param(s + 2, "ArtiOsMessageContainerInstanceMsgType", "Type of the message.", 0, 1, "ECUC_Arti_00130")),
        rs=[inst_p("ArtiOsMessageContainerInstanceFirstElementRef", "ECUC_Arti_00131",
                   "Refers to the first element of the message queue. This message will be received next."),
            gen_inst("ArtiOsMessageContainerInstanceGenericComponentInstanceRef", "ECUC_Arti_00132", "ArtiOsMessageContainerInstance"),
            inst_p("ArtiOsMessageContainerInstanceQueueCountRef", "ECUC_Arti_00133",
                   'Refers to the ArtiObjectInstanceParameter that contains the evaluation for the "queuecount" of this ArtiOsMessageContainer.'),
            inst_p("ArtiOsMessageContainerInstanceQueueSizeRef", "ECUC_Arti_00134",
                   'Refers to the ArtiObjectInstanceParameter that contains the evaluation for the "queuesize" of this ArtiOsMessageContainer.'),
            valid("ArtiOsMessageContainerInstanceValidRef", "ECUC_Arti_00135", "ArtiOsMessageContainerInstance")])
    add("ArtiOsResourceClass", "ECUC_Arti_00136",
        "Contains the layout of an ArtiOsResource object. The ArtiOsResource object represents an OSEK resource.", 0, 1, rs=[
            gen_cls("ArtiOsResourceClassGenericComponentClassRef", "ECUC_Arti_00138", "ArtiOsResourceClass"),
            cls_p("ArtiOsResourceClassLockerRef", "ECUC_Arti_00139",
                  "Refers to the ArtiObjectClassParameter that declares the attribute ArtiOsResourceLockerRef in ArtiOsResourceInstances."),
            cls_p("ArtiOsResourceClassStateRef", "ECUC_Arti_00140",
                  "Refers to the ArtiObjectClassParameter that declares the attribute ArtiOsResourceStateRef in ArtiOsResourceInstances.")])
    add("ArtiOsResourceInstance", "ECUC_Arti_00137", "Represents an instance of an ArtiOsResource object.", 0, "*",
        params=string_param(s + 2, "ArtiOsResourceInstancePriority",
                            "This attribute has two components that state: that the RESOURCE is used by TASKs only or by TASKs and ISRs, and the priority that will be used when locking the RESOURCE.",
                            0, 1, "ECUC_Arti_00141"),
        rs=[("ArtiOsResourceInstanceEcuCRef", "ECUC_Arti_00142", 0, 1, ECUC_OS + "/OsResource", "Refers to an EcuC OsResource that is being extended."),
            gen_inst("ArtiOsResourceInstanceGenericComponentInstanceRef", "ECUC_Arti_00143", "ArtiOsResourceInstance"),
            inst_p("ArtiOsResourceInstanceLockerRef", "ECUC_Arti_00145",
                   'Refers to the ArtiObjectInstanceParameter that contains the evaluation for the "locker" of this ArtiOsResource.'),
            inst_p("ArtiOsResourceInstanceStateRef", "ECUC_Arti_00144",
                   'Refers to the ArtiObjectInstanceParameter that contains the evaluation for the "state" of this ArtiOsResource.'),
            valid("ArtiOsResourceInstanceValidRef", "ECUC_Arti_00146", "ArtiOsResourceInstance")])
    add("ArtiOsStackClass", "ECUC_Arti_00147",
        "Contains the layout of an ArtiOsStack object. The ArtiOsStack object defines the memory area of any stack in the system.",
        0, 1, rs=[gen_cls("ArtiOsStackClassGenericComponentClassRef", "ECUC_Arti_00149", "ArtiOsStackClass")])
    add("ArtiOsStackInstance", "ECUC_Arti_00148", "Represents an instance of an ArtiOsStack object.", 0, "*",
        params=string_param(s + 2, "ArtiOsStackInstanceDirection",
                            'This attribute specifies the direction of stack growth and may have either "UP" or "DOWN" as its value.',
                            0, 1, "ECUC_Arti_00150"),
        rs=[inst_p("ArtiOsStackInstanceBaseAddressRef", "ECUC_Arti_00151",
                   'Refers to the ArtiObjectInstanceParameter that contains the evaluation for the "base address" of this ArtiOsStack.'),
            inst_p("ArtiOsStackInstanceFillPatternRef", "ECUC_Arti_00152",
                   'Refers to the ArtiObjectInstanceParameter that contains the evaluation for the "fillpattern" of this ArtiOsStack.'),
            gen_inst("ArtiOsStackInstanceGenericComponentInstanceRef", "ECUC_Arti_00153", "ArtiOsStackInstance"),
            inst_p("ArtiOsStackInstanceSizeRef", "ECUC_Arti_00154",
                   'Refers to the ArtiObjectInstanceParameter that contains the evaluation for the "size" of this ArtiOsStack.'),
            valid("ArtiOsStackInstanceValidRef", "ECUC_Arti_00155", "ArtiOsStack")])
    add("ArtiOsTaskClass", "ECUC_Arti_00087", 'Contains the layout of an ARTI "OsTask" object, extending the EcuC OsTask.', 0, 1, rs=[
        ("ArtiOsTaskClassClassGenericComponentRef", "ECUC_Arti_00077", 0, 1, GEN_CLS,
         "Refers to an ArtiGenericComponentClass that extends the OsTask."),
        cls_p("ArtiOsTaskClassContextRef", "ECUC_Arti_00100",
              "Declares the attribute ArtiOsTaskContextRef in ArtiOsTaskInstances: a reference to the context object that the task is currently using."),
        cls_p("ArtiOsTaskClassCurrentTaskStateRef", "ECUC_Arti_00068",
              "Refers to the ArtiObjectClassParameter that defines the ArtiCurrentTaskStateInstance parameter including the task state mapping."),
        cls_p("ArtiOsTaskClassPriorityRef", "ECUC_Arti_00101",
              "Declares the attribute ArtiOsTaskPriorityRef in ArtiOsTaskInstances: the current priority of the TASK object."),
        cls_p("ArtiOsTaskClassStackRef", "ECUC_Arti_00102",
              "Declares the attribute ArtiOsTaskStackRef in ArtiOsTaskInstances: a reference to the stack object that the task is currently using.")])
    add("ArtiOsTaskInstance", "ECUC_Arti_00090", 'Represents an instance of an ARTI "OsTask" object, extending the EcuC OsTask.',
        0, "*",
        params=(func_param(s + 2, "ArtiOsTaskInstanceFunction", "This parameter represents the C function name of the task body.",
                           0, 1, "ECUC_Arti_00089")
                + int_param(s + 2, "ArtiOsTaskInstanceId", 'This parameter represents the "TaskID" as given by the OSEK OS, returned by GetTaskID().',
                            1, 1, "ECUC_Arti_00092", 0, "18446744073709551615")),
        rs=[inst_p("ArtiOsTaskInstanceContextRef", "ECUC_Arti_00104",
                   "Refers to the ArtiObjectInstanceParameter that contains the evaluation for the ArtiOsContext of this ArtiOsTask."),
            inst_p("ArtiOsTaskInstanceCurrentActivationsRef", "ECUC_Arti_00105",
                   'Refers to the ArtiObjectInstanceParameter that contains the evaluation for the "current activations" of this task.'),
            inst_p("ArtiOsTaskInstanceCurrentTaskStateRef", "ECUC_Arti_00069",
                   'Refers to the ArtiObjectInstanceParameter that contains the evaluation for the "current state" of this task.'),
            ("ArtiOsTaskInstanceEcucRef", "ECUC_Arti_00088", 1, 1, ECUC_OS + "/OsTask", "Refers to the EcuC OsTask that is being extended."),
            gen_inst("ArtiOsTaskInstanceGenericComponentRef", "ECUC_Arti_00070", "OsTask"),
            inst_p("ArtiOsTaskInstancePriorityRef", "ECUC_Arti_00106",
                   'Refers to the ArtiObjectInstanceParameter that contains the evaluation for the "task priority" of this task.'),
            inst_p("ArtiOsTaskInstanceStackRef", "ECUC_Arti_00107",
                   "Refers to the ArtiObjectInstanceParameter that contains the evaluation for the ArtiOsStack of this ArtiOsTask."),
            valid("ArtiOsTaskInstanceValidRef", "ECUC_Arti_00103", "ArtiOsTaskInstance")])
    own_refs = ref(n + 2, "ArtiOsGenericComponentRef", "Refers to an ArtiGenericComponentClass that relates to the OS.", 0, "*",
                   "ECUC_Arti_00178", GEN_CLS)
    return container(n - 1, "ArtiOs", "The ArtiOs container contains ARTI extensions to the EcucDefs/Os module.", 0, 1,
                     "ECUC_Arti_00071", refs=own_refs, subs="".join(subs))
