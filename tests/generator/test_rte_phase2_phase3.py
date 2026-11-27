"""Unit, Clang syntax-check, and real-project smoke tests for RTE Phase 2/3 & Service Mapping."""

from pathlib import Path
import shutil
import subprocess
from textwrap import dedent

import pytest

from autosar_configurator.core.model.configuration_model import EcucContainerValue
from autosar_configurator.core.workspace_manager import WorkspaceManager
from tests.generator.test_rte_bootstrap import _minimal_module_def_arxml
from autosar_configurator.generator.rte import (
    RteModelExtractor,
    RteSchMGenerator,
    RteWorkbenchService,
    SwcSystemIndex,
)


def _c(parent, name: str, dref: str) -> EcucContainerValue:
    c = EcucContainerValue(
        short_name=name,
        definition_ref=dref,
        def_dest_type="ECUC-PARAM-CONF-CONTAINER-DEF",
    )
    if hasattr(parent, "add_container"):
        parent.add_container(c)
    else:
        parent.add_sub_container(c)
    return c


def _p(c: EcucContainerValue, name: str, val, dt: str = "ECUC-BOOLEAN-PARAM-DEF"):
    c.set_parameter_value(name, val, f"{c.definition_ref}/{name}")
    c.parameter_values[name].dest_type = dt


def _r(c: EcucContainerValue, name: str, ref: str, *, dt: str = "ECUC-REFERENCE-DEF", vdest: str = "ECUC-CONTAINER-VALUE"):
    c.set_reference_value(name, ref, f"{c.definition_ref}/{name}", dest_type=dt, value_ref_dest=vdest)


def _mr(c: EcucContainerValue, name: str, refs):
    for idx, ref in enumerate(refs):
        c.add_multi_reference_value(name, ref, f"{c.definition_ref}/{name}", idx)


def build_phase23_project(tmp_path: Path):
    """Build a dual-core AUTOSAR project with system/ SWC ARXMLs, Os, Com, and Rte."""
    proj_dir = tmp_path / "p2_proj"
    sys_dir = proj_dir / "system"
    (sys_dir / "AUTOSAR").mkdir(parents=True, exist_ok=True)
    (sys_dir / "Developer/ComponentTypes").mkdir(parents=True, exist_ok=True)
    (sys_dir / "ServiceComponents").mkdir(parents=True, exist_ok=True)
    (sys_dir / "System").mkdir(parents=True, exist_ok=True)

    # 1. Platform base types
    (sys_dir / "AUTOSAR/PlatformTypes.arxml").write_text(
        dedent("""\
            <?xml version="1.0" encoding="UTF-8"?>
            <AUTOSAR xmlns="http://autosar.org/schema/r4.0">
              <AR-PACKAGES>
                <AR-PACKAGE><SHORT-NAME>AUTOSAR_Platform</SHORT-NAME>
                  <AR-PACKAGES>
                    <AR-PACKAGE><SHORT-NAME>BaseTypes</SHORT-NAME><ELEMENTS>
                      <SW-BASE-TYPE><SHORT-NAME>uint8</SHORT-NAME><NATIVE-DECLARATION>uint8</NATIVE-DECLARATION></SW-BASE-TYPE>
                      <SW-BASE-TYPE><SHORT-NAME>uint16</SHORT-NAME><NATIVE-DECLARATION>uint16</NATIVE-DECLARATION></SW-BASE-TYPE>
                      <SW-BASE-TYPE><SHORT-NAME>boolean</SHORT-NAME><NATIVE-DECLARATION>boolean</NATIVE-DECLARATION></SW-BASE-TYPE>
                    </ELEMENTS></AR-PACKAGE>
                    <AR-PACKAGE><SHORT-NAME>ImplementationDataTypes</SHORT-NAME><ELEMENTS>
                      <IMPLEMENTATION-DATA-TYPE><SHORT-NAME>uint8</SHORT-NAME><CATEGORY>VALUE</CATEGORY>
                        <SW-DATA-DEF-PROPS><SW-DATA-DEF-PROPS-VARIANTS><SW-DATA-DEF-PROPS-CONDITIONAL>
                          <BASE-TYPE-REF DEST="SW-BASE-TYPE">/AUTOSAR_Platform/BaseTypes/uint8</BASE-TYPE-REF>
                        </SW-DATA-DEF-PROPS-CONDITIONAL></SW-DATA-DEF-PROPS-VARIANTS></SW-DATA-DEF-PROPS>
                      </IMPLEMENTATION-DATA-TYPE>
                      <IMPLEMENTATION-DATA-TYPE><SHORT-NAME>uint16</SHORT-NAME><CATEGORY>VALUE</CATEGORY>
                        <SW-DATA-DEF-PROPS><SW-DATA-DEF-PROPS-VARIANTS><SW-DATA-DEF-PROPS-CONDITIONAL>
                          <BASE-TYPE-REF DEST="SW-BASE-TYPE">/AUTOSAR_Platform/BaseTypes/uint16</BASE-TYPE-REF>
                        </SW-DATA-DEF-PROPS-CONDITIONAL></SW-DATA-DEF-PROPS-VARIANTS></SW-DATA-DEF-PROPS>
                      </IMPLEMENTATION-DATA-TYPE>
                    </ELEMENTS></AR-PACKAGE>
                  </AR-PACKAGES>
                </AR-PACKAGE>
              </AR-PACKAGES>
            </AUTOSAR>
        """),
        encoding="utf-8",
    )

    # 2. DataTypes (TYPE_REFERENCE, ARRAY, STRUCTURE, DATA-TYPE-MAP)
    (sys_dir / "Developer/DataTypes.arxml").write_text(
        dedent("""\
            <?xml version="1.0" encoding="UTF-8"?>
            <AUTOSAR xmlns="http://autosar.org/schema/r4.0">
              <AR-PACKAGES>
                <AR-PACKAGE><SHORT-NAME>DataTypes</SHORT-NAME><ELEMENTS>
                  <IMPLEMENTATION-DATA-TYPE><SHORT-NAME>SigTrq_Type</SHORT-NAME><CATEGORY>TYPE_REFERENCE</CATEGORY>
                    <SW-DATA-DEF-PROPS><SW-DATA-DEF-PROPS-VARIANTS><SW-DATA-DEF-PROPS-CONDITIONAL>
                      <IMPLEMENTATION-DATA-TYPE-REF DEST="IMPLEMENTATION-DATA-TYPE">/AUTOSAR_Platform/ImplementationDataTypes/uint16</IMPLEMENTATION-DATA-TYPE-REF>
                    </SW-DATA-DEF-PROPS-CONDITIONAL></SW-DATA-DEF-PROPS-VARIANTS></SW-DATA-DEF-PROPS>
                  </IMPLEMENTATION-DATA-TYPE>
                  <IMPLEMENTATION-DATA-TYPE><SHORT-NAME>FsmState_Type</SHORT-NAME><CATEGORY>TYPE_REFERENCE</CATEGORY>
                    <SW-DATA-DEF-PROPS><SW-DATA-DEF-PROPS-VARIANTS><SW-DATA-DEF-PROPS-CONDITIONAL>
                      <IMPLEMENTATION-DATA-TYPE-REF DEST="IMPLEMENTATION-DATA-TYPE">/AUTOSAR_Platform/ImplementationDataTypes/uint8</IMPLEMENTATION-DATA-TYPE-REF>
                    </SW-DATA-DEF-PROPS-CONDITIONAL></SW-DATA-DEF-PROPS-VARIANTS></SW-DATA-DEF-PROPS>
                  </IMPLEMENTATION-DATA-TYPE>
                  <IMPLEMENTATION-DATA-TYPE><SHORT-NAME>DiagBytes8_Type</SHORT-NAME><CATEGORY>ARRAY</CATEGORY>
                    <SUB-ELEMENTS><IMPLEMENTATION-DATA-TYPE-ELEMENT><SHORT-NAME>Element</SHORT-NAME>
                      <ARRAY-SIZE>8</ARRAY-SIZE>
                      <IMPLEMENTATION-DATA-TYPE-REF DEST="IMPLEMENTATION-DATA-TYPE">/AUTOSAR_Platform/ImplementationDataTypes/uint8</IMPLEMENTATION-DATA-TYPE-REF>
                    </IMPLEMENTATION-DATA-TYPE-ELEMENT></SUB-ELEMENTS>
                  </IMPLEMENTATION-DATA-TYPE>
                  <IMPLEMENTATION-DATA-TYPE><SHORT-NAME>MotorInfo_Struct</SHORT-NAME><CATEGORY>STRUCTURE</CATEGORY>
                    <SUB-ELEMENTS>
                      <IMPLEMENTATION-DATA-TYPE-ELEMENT><SHORT-NAME>Torque</SHORT-NAME>
                        <IMPLEMENTATION-DATA-TYPE-REF DEST="IMPLEMENTATION-DATA-TYPE">/DataTypes/SigTrq_Type</IMPLEMENTATION-DATA-TYPE-REF>
                      </IMPLEMENTATION-DATA-TYPE-ELEMENT>
                      <IMPLEMENTATION-DATA-TYPE-ELEMENT><SHORT-NAME>State</SHORT-NAME>
                        <IMPLEMENTATION-DATA-TYPE-REF DEST="IMPLEMENTATION-DATA-TYPE">/DataTypes/FsmState_Type</IMPLEMENTATION-DATA-TYPE-REF>
                      </IMPLEMENTATION-DATA-TYPE-ELEMENT>
                    </SUB-ELEMENTS>
                  </IMPLEMENTATION-DATA-TYPE>
                  <APPLICATION-PRIMITIVE-DATA-TYPE><SHORT-NAME>SigTrq_ADT</SHORT-NAME></APPLICATION-PRIMITIVE-DATA-TYPE>
                  <DATA-TYPE-MAPPING-SET><SHORT-NAME>MapSet</SHORT-NAME><DATA-TYPE-MAPS>
                    <DATA-TYPE-MAP>
                      <APPLICATION-DATA-TYPE-REF DEST="APPLICATION-PRIMITIVE-DATA-TYPE">/DataTypes/SigTrq_ADT</APPLICATION-DATA-TYPE-REF>
                      <IMPLEMENTATION-DATA-TYPE-REF DEST="IMPLEMENTATION-DATA-TYPE">/DataTypes/SigTrq_Type</IMPLEMENTATION-DATA-TYPE-REF>
                    </DATA-TYPE-MAP>
                  </DATA-TYPE-MAPS></DATA-TYPE-MAPPING-SET>
                </ELEMENTS></AR-PACKAGE>
              </AR-PACKAGES>
            </AUTOSAR>
        """),
        encoding="utf-8",
    )

    # 3. PortInterfaces & ModeGroups
    (sys_dir / "Developer/PortInterfaces.arxml").write_text(
        dedent("""\
            <?xml version="1.0" encoding="UTF-8"?>
            <AUTOSAR xmlns="http://autosar.org/schema/r4.0">
              <AR-PACKAGES>
                <AR-PACKAGE><SHORT-NAME>PortInterfaces</SHORT-NAME><ELEMENTS>
                  <SENDER-RECEIVER-INTERFACE><SHORT-NAME>If_TrqMeas</SHORT-NAME><IS-SERVICE>false</IS-SERVICE>
                    <DATA-ELEMENTS><VARIABLE-DATA-PROTOTYPE><SHORT-NAME>Val</SHORT-NAME>
                      <TYPE-TREF DEST="APPLICATION-PRIMITIVE-DATA-TYPE">/DataTypes/SigTrq_ADT</TYPE-TREF>
                    </VARIABLE-DATA-PROTOTYPE></DATA-ELEMENTS>
                  </SENDER-RECEIVER-INTERFACE>
                  <SENDER-RECEIVER-INTERFACE><SHORT-NAME>If_VcuCmd</SHORT-NAME><IS-SERVICE>false</IS-SERVICE>
                    <DATA-ELEMENTS><VARIABLE-DATA-PROTOTYPE><SHORT-NAME>Cmd</SHORT-NAME>
                      <TYPE-TREF DEST="IMPLEMENTATION-DATA-TYPE">/DataTypes/FsmState_Type</TYPE-TREF>
                    </VARIABLE-DATA-PROTOTYPE></DATA-ELEMENTS>
                  </SENDER-RECEIVER-INTERFACE>
                  <SENDER-RECEIVER-INTERFACE><SHORT-NAME>If_FsmState</SHORT-NAME><IS-SERVICE>false</IS-SERVICE>
                    <DATA-ELEMENTS><VARIABLE-DATA-PROTOTYPE><SHORT-NAME>State</SHORT-NAME>
                      <TYPE-TREF DEST="IMPLEMENTATION-DATA-TYPE">/DataTypes/FsmState_Type</TYPE-TREF>
                    </VARIABLE-DATA-PROTOTYPE></DATA-ELEMENTS>
                  </SENDER-RECEIVER-INTERFACE>
                </ELEMENTS></AR-PACKAGE>
              </AR-PACKAGES>
            </AUTOSAR>
        """),
        encoding="utf-8",
    )

    # 4. ComM ServiceComponent
    (sys_dir / "ServiceComponents/ComM_swc.arxml").write_text(
        dedent("""\
            <?xml version="1.0" encoding="UTF-8"?>
            <AUTOSAR xmlns="http://autosar.org/schema/r4.0">
              <AR-PACKAGES>
                <AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME>
                  <AR-PACKAGES>
                    <AR-PACKAGE><SHORT-NAME>ComM_swc</SHORT-NAME>
                      <AR-PACKAGES>
                        <AR-PACKAGE><SHORT-NAME>DataTypes</SHORT-NAME><ELEMENTS>
                          <IMPLEMENTATION-DATA-TYPE><SHORT-NAME>ComM_ModeType</SHORT-NAME><CATEGORY>TYPE_REFERENCE</CATEGORY>
                            <SW-DATA-DEF-PROPS><SW-DATA-DEF-PROPS-VARIANTS><SW-DATA-DEF-PROPS-CONDITIONAL>
                              <IMPLEMENTATION-DATA-TYPE-REF DEST="IMPLEMENTATION-DATA-TYPE">/AUTOSAR_Platform/ImplementationDataTypes/uint8</IMPLEMENTATION-DATA-TYPE-REF>
                            </SW-DATA-DEF-PROPS-CONDITIONAL></SW-DATA-DEF-PROPS-VARIANTS></SW-DATA-DEF-PROPS>
                          </IMPLEMENTATION-DATA-TYPE>
                          <IMPLEMENTATION-DATA-TYPE><SHORT-NAME>ComM_UserHandleType</SHORT-NAME><CATEGORY>TYPE_REFERENCE</CATEGORY>
                            <SW-DATA-DEF-PROPS><SW-DATA-DEF-PROPS-VARIANTS><SW-DATA-DEF-PROPS-CONDITIONAL>
                              <IMPLEMENTATION-DATA-TYPE-REF DEST="IMPLEMENTATION-DATA-TYPE">/AUTOSAR_Platform/ImplementationDataTypes/uint8</IMPLEMENTATION-DATA-TYPE-REF>
                            </SW-DATA-DEF-PROPS-CONDITIONAL></SW-DATA-DEF-PROPS-VARIANTS></SW-DATA-DEF-PROPS>
                          </IMPLEMENTATION-DATA-TYPE>
                        </ELEMENTS></AR-PACKAGE>
                        <AR-PACKAGE><SHORT-NAME>Interfaces</SHORT-NAME><ELEMENTS>
                          <CLIENT-SERVER-INTERFACE><SHORT-NAME>ComM_UserRequest</SHORT-NAME><IS-SERVICE>true</IS-SERVICE>
                            <OPERATIONS><CLIENT-SERVER-OPERATION><SHORT-NAME>RequestComMode</SHORT-NAME>
                              <ARGUMENTS><ARGUMENT-DATA-PROTOTYPE><SHORT-NAME>ComMode</SHORT-NAME>
                                <TYPE-TREF DEST="IMPLEMENTATION-DATA-TYPE">/MICROSAR/ComM_swc/DataTypes/ComM_ModeType</TYPE-TREF>
                                <DIRECTION>IN</DIRECTION>
                              </ARGUMENT-DATA-PROTOTYPE></ARGUMENTS>
                              <POSSIBLE-ERROR-REFS><POSSIBLE-ERROR-REF DEST="APPLICATION-ERROR">/Err</POSSIBLE-ERROR-REF></POSSIBLE-ERROR-REFS>
                            </CLIENT-SERVER-OPERATION></OPERATIONS>
                          </CLIENT-SERVER-INTERFACE>
                        </ELEMENTS></AR-PACKAGE>
                        <AR-PACKAGE><SHORT-NAME>ComponentTypes</SHORT-NAME><ELEMENTS>
                          <SERVICE-SW-COMPONENT-TYPE><SHORT-NAME>ComM</SHORT-NAME>
                            <PORTS><P-PORT-PROTOTYPE><SHORT-NAME>UR_CN_CAN00</SHORT-NAME>
                              <PROVIDED-INTERFACE-TREF DEST="CLIENT-SERVER-INTERFACE">/MICROSAR/ComM_swc/Interfaces/ComM_UserRequest</PROVIDED-INTERFACE-TREF>
                            </P-PORT-PROTOTYPE></PORTS>
                            <INTERNAL-BEHAVIORS><SWC-INTERNAL-BEHAVIOR><SHORT-NAME>ComMInternalBehavior</SHORT-NAME>
                              <EVENTS>
                                <OPERATION-INVOKED-EVENT><SHORT-NAME>OIE_Req</SHORT-NAME>
                                  <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/MICROSAR/ComM_swc/ComponentTypes/ComM/ComMInternalBehavior/RequestComMode</START-ON-EVENT-REF>
                                  <OPERATION-IREF>
                                    <CONTEXT-P-PORT-REF DEST="P-PORT-PROTOTYPE">/MICROSAR/ComM_swc/ComponentTypes/ComM/UR_CN_CAN00</CONTEXT-P-PORT-REF>
                                    <TARGET-PROVIDED-OPERATION-REF DEST="CLIENT-SERVER-OPERATION">/MICROSAR/ComM_swc/Interfaces/ComM_UserRequest/RequestComMode</TARGET-PROVIDED-OPERATION-REF>
                                  </OPERATION-IREF>
                                </OPERATION-INVOKED-EVENT>
                              </EVENTS>
                              <PORT-API-OPTIONS><PORT-API-OPTION>
                                <PORT-ARG-VALUES><PORT-DEFINED-ARGUMENT-VALUE>
                                  <VALUE><NUMERICAL-VALUE-SPECIFICATION><VALUE>0</VALUE></NUMERICAL-VALUE-SPECIFICATION></VALUE>
                                  <VALUE-TYPE-TREF DEST="IMPLEMENTATION-DATA-TYPE">/MICROSAR/ComM_swc/DataTypes/ComM_UserHandleType</VALUE-TYPE-TREF>
                                </PORT-DEFINED-ARGUMENT-VALUE></PORT-ARG-VALUES>
                                <PORT-REF DEST="P-PORT-PROTOTYPE">/MICROSAR/ComM_swc/ComponentTypes/ComM/UR_CN_CAN00</PORT-REF>
                              </PORT-API-OPTION></PORT-API-OPTIONS>
                              <RUNNABLES><RUNNABLE-ENTITY><SHORT-NAME>RequestComMode</SHORT-NAME><SYMBOL>ComM_RequestComMode</SYMBOL></RUNNABLE-ENTITY></RUNNABLES>
                            </SWC-INTERNAL-BEHAVIOR></INTERNAL-BEHAVIORS>
                          </SERVICE-SW-COMPONENT-TYPE>
                        </ELEMENTS></AR-PACKAGE>
                      </AR-PACKAGES>
                    </AR-PACKAGE>
                  </AR-PACKAGES>
                </AR-PACKAGE>
              </AR-PACKAGES>
            </AUTOSAR>
        """),
        encoding="utf-8",
    )

    # 5. MotorCtrl (Core 0) & Core1DiagSwc (Core 1)
    (sys_dir / "Developer/ComponentTypes/MotorCtrl.arxml").write_text(
        dedent("""\
            <?xml version="1.0" encoding="UTF-8"?>
            <AUTOSAR xmlns="http://autosar.org/schema/r4.0">
              <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ComponentTypes</SHORT-NAME><ELEMENTS>
                <APPLICATION-SW-COMPONENT-TYPE><SHORT-NAME>MotorCtrl</SHORT-NAME>
                  <PORTS>
                    <P-PORT-PROTOTYPE><SHORT-NAME>SigPP_Proto_TrqMeas</SHORT-NAME>
                      <PROVIDED-COM-SPECS><NONQUEUED-SENDER-COM-SPEC>
                        <DATA-ELEMENT-REF DEST="VARIABLE-DATA-PROTOTYPE">/PortInterfaces/If_TrqMeas/Val</DATA-ELEMENT-REF>
                        <INIT-VALUE><NUMERICAL-VALUE-SPECIFICATION><VALUE>100</VALUE></NUMERICAL-VALUE-SPECIFICATION></INIT-VALUE>
                      </NONQUEUED-SENDER-COM-SPEC></PROVIDED-COM-SPECS>
                      <PROVIDED-INTERFACE-TREF DEST="SENDER-RECEIVER-INTERFACE">/PortInterfaces/If_TrqMeas</PROVIDED-INTERFACE-TREF>
                    </P-PORT-PROTOTYPE>
                    <R-PORT-PROTOTYPE><SHORT-NAME>SigRP_Proto_VcuCmd</SHORT-NAME>
                      <REQUIRED-COM-SPECS><NONQUEUED-RECEIVER-COM-SPEC>
                        <DATA-ELEMENT-REF DEST="VARIABLE-DATA-PROTOTYPE">/PortInterfaces/If_VcuCmd/Cmd</DATA-ELEMENT-REF>
                        <INIT-VALUE><NUMERICAL-VALUE-SPECIFICATION><VALUE>0</VALUE></NUMERICAL-VALUE-SPECIFICATION></INIT-VALUE>
                      </NONQUEUED-RECEIVER-COM-SPEC></REQUIRED-COM-SPECS>
                      <REQUIRED-INTERFACE-TREF DEST="SENDER-RECEIVER-INTERFACE">/PortInterfaces/If_VcuCmd</REQUIRED-INTERFACE-TREF>
                    </R-PORT-PROTOTYPE>
                    <P-PORT-PROTOTYPE><SHORT-NAME>PpInterFsm</SHORT-NAME>
                      <PROVIDED-COM-SPECS><NONQUEUED-SENDER-COM-SPEC>
                        <DATA-ELEMENT-REF DEST="VARIABLE-DATA-PROTOTYPE">/PortInterfaces/If_FsmState/State</DATA-ELEMENT-REF>
                        <INIT-VALUE><NUMERICAL-VALUE-SPECIFICATION><VALUE>1</VALUE></NUMERICAL-VALUE-SPECIFICATION></INIT-VALUE>
                      </NONQUEUED-SENDER-COM-SPEC></PROVIDED-COM-SPECS>
                      <PROVIDED-INTERFACE-TREF DEST="SENDER-RECEIVER-INTERFACE">/PortInterfaces/If_FsmState</PROVIDED-INTERFACE-TREF>
                    </P-PORT-PROTOTYPE>
                    <R-PORT-PROTOTYPE><SHORT-NAME>UR_CN_CAN00</SHORT-NAME>
                      <REQUIRED-INTERFACE-TREF DEST="CLIENT-SERVER-INTERFACE">/MICROSAR/ComM_swc/Interfaces/ComM_UserRequest</REQUIRED-INTERFACE-TREF>
                    </R-PORT-PROTOTYPE>
                  </PORTS>
                  <INTERNAL-BEHAVIORS><SWC-INTERNAL-BEHAVIOR><SHORT-NAME>MotorCtrl_IB</SHORT-NAME>
                    <EVENTS>
                      <INIT-EVENT><SHORT-NAME>Init_MotorCtrl</SHORT-NAME>
                        <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentTypes/MotorCtrl/MotorCtrl_IB/MotorCtrl_Init</START-ON-EVENT-REF>
                      </INIT-EVENT>
                      <TIMING-EVENT><SHORT-NAME>Tmr_MotorCtrl_10ms</SHORT-NAME>
                        <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentTypes/MotorCtrl/MotorCtrl_IB/MotorCtrl_10ms</START-ON-EVENT-REF>
                        <PERIOD>0.01</PERIOD>
                      </TIMING-EVENT>
                    </EVENTS>
                    <RUNNABLES>
                      <RUNNABLE-ENTITY><SHORT-NAME>MotorCtrl_Init</SHORT-NAME><SYMBOL>MotorCtrl_Init</SYMBOL></RUNNABLE-ENTITY>
                      <RUNNABLE-ENTITY><SHORT-NAME>MotorCtrl_10ms</SHORT-NAME><SYMBOL>MotorCtrl_10ms</SYMBOL></RUNNABLE-ENTITY>
                    </RUNNABLES>
                  </SWC-INTERNAL-BEHAVIOR></INTERNAL-BEHAVIORS>
                </APPLICATION-SW-COMPONENT-TYPE>
              </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
            </AUTOSAR>
        """),
        encoding="utf-8",
    )

    (sys_dir / "Developer/ComponentTypes/Core1DiagSwc.arxml").write_text(
        dedent("""\
            <?xml version="1.0" encoding="UTF-8"?>
            <AUTOSAR xmlns="http://autosar.org/schema/r4.0">
              <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>ComponentTypes</SHORT-NAME><ELEMENTS>
                <APPLICATION-SW-COMPONENT-TYPE><SHORT-NAME>Core1DiagSwc</SHORT-NAME>
                  <PORTS>
                    <R-PORT-PROTOTYPE><SHORT-NAME>RpInterFsm</SHORT-NAME>
                      <REQUIRED-INTERFACE-TREF DEST="SENDER-RECEIVER-INTERFACE">/PortInterfaces/If_FsmState</REQUIRED-INTERFACE-TREF>
                    </R-PORT-PROTOTYPE>
                  </PORTS>
                  <INTERNAL-BEHAVIORS><SWC-INTERNAL-BEHAVIOR><SHORT-NAME>Core1DiagSwc_IB</SHORT-NAME>
                    <EVENTS>
                      <TIMING-EVENT><SHORT-NAME>Tmr_Core1Diag_10ms</SHORT-NAME>
                        <START-ON-EVENT-REF DEST="RUNNABLE-ENTITY">/ComponentTypes/Core1DiagSwc/Core1DiagSwc_IB/Core1Diag_10ms</START-ON-EVENT-REF>
                        <PERIOD>0.01</PERIOD>
                      </TIMING-EVENT>
                    </EVENTS>
                    <RUNNABLES>
                      <RUNNABLE-ENTITY><SHORT-NAME>Core1Diag_10ms</SHORT-NAME><SYMBOL>Core1Diag_10ms</SYMBOL></RUNNABLE-ENTITY>
                    </RUNNABLES>
                  </SWC-INTERNAL-BEHAVIOR></INTERNAL-BEHAVIORS>
                </APPLICATION-SW-COMPONENT-TYPE>
              </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
            </AUTOSAR>
        """),
        encoding="utf-8",
    )

    # 6. System Communication.arxml & FlatExtract.arxml
    (sys_dir / "System/Communication.arxml").write_text(
        dedent("""\
            <?xml version="1.0" encoding="UTF-8"?>
            <AUTOSAR xmlns="http://autosar.org/schema/r4.0">
              <AR-PACKAGES>
                <AR-PACKAGE><SHORT-NAME>Signal</SHORT-NAME><ELEMENTS>
                  <SYSTEM-SIGNAL><SHORT-NAME>TrqMeas</SHORT-NAME></SYSTEM-SIGNAL>
                  <SYSTEM-SIGNAL><SHORT-NAME>VcuCmd</SHORT-NAME></SYSTEM-SIGNAL>
                </ELEMENTS></AR-PACKAGE>
                <AR-PACKAGE><SHORT-NAME>ISignal</SHORT-NAME><ELEMENTS>
                  <I-SIGNAL><SHORT-NAME>TrqMeas_oMCU</SHORT-NAME><SYSTEM-SIGNAL-REF DEST="SYSTEM-SIGNAL">/Signal/TrqMeas</SYSTEM-SIGNAL-REF></I-SIGNAL>
                </ELEMENTS></AR-PACKAGE>
                <AR-PACKAGE><SHORT-NAME>PDU</SHORT-NAME><AR-PACKAGES>
                  <AR-PACKAGE><SHORT-NAME>MCU_Out</SHORT-NAME><ELEMENTS>
                    <I-SIGNAL-I-PDU><SHORT-NAME>MCU_Out_PDU</SHORT-NAME><I-SIGNAL-TO-PDU-MAPPINGS>
                      <I-SIGNAL-TO-I-PDU-MAPPING><SHORT-NAME>TrqMeas</SHORT-NAME>
                        <I-SIGNAL-REF DEST="I-SIGNAL">/ISignal/TrqMeas_oMCU</I-SIGNAL-REF>
                      </I-SIGNAL-TO-I-PDU-MAPPING>
                    </I-SIGNAL-TO-PDU-MAPPINGS></I-SIGNAL-I-PDU>
                  </ELEMENTS></AR-PACKAGE>
                </AR-PACKAGES></AR-PACKAGE>
              </AR-PACKAGES>
            </AUTOSAR>
        """),
        encoding="utf-8",
    )

    (sys_dir / "System/FlatExtract.arxml").write_text(
        dedent("""\
            <?xml version="1.0" encoding="UTF-8"?>
            <AUTOSAR xmlns="http://autosar.org/schema/r4.0">
              <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>COM</SHORT-NAME><ELEMENTS>
                <COMPOSITION-SW-COMPONENT-TYPE><SHORT-NAME>COMPOSITIONTYPE</SHORT-NAME>
                  <PORTS>
                    <P-PORT-PROTOTYPE><SHORT-NAME>SigPP_Proto_TrqMeas</SHORT-NAME></P-PORT-PROTOTYPE>
                  </PORTS>
                  <COMPONENTS>
                    <SW-COMPONENT-PROTOTYPE><SHORT-NAME>MotorCtrl</SHORT-NAME><TYPE-TREF DEST="APPLICATION-SW-COMPONENT-TYPE">/ComponentTypes/MotorCtrl</TYPE-TREF></SW-COMPONENT-PROTOTYPE>
                    <SW-COMPONENT-PROTOTYPE><SHORT-NAME>Core1DiagSwc</SHORT-NAME><TYPE-TREF DEST="APPLICATION-SW-COMPONENT-TYPE">/ComponentTypes/Core1DiagSwc</TYPE-TREF></SW-COMPONENT-PROTOTYPE>
                    <SW-COMPONENT-PROTOTYPE><SHORT-NAME>ComM</SHORT-NAME><TYPE-TREF DEST="SERVICE-SW-COMPONENT-TYPE">/MICROSAR/ComM_swc/ComponentTypes/ComM</TYPE-TREF></SW-COMPONENT-PROTOTYPE>
                  </COMPONENTS>
                  <CONNECTORS>
                    <DELEGATION-SW-CONNECTOR><SHORT-NAME>Deleg_Trq</SHORT-NAME>
                      <INNER-PORT-IREF><P-PORT-IN-COMPOSITION-INSTANCE-REF>
                        <CONTEXT-COMPONENT-REF DEST="SW-COMPONENT-PROTOTYPE">/COM/COMPOSITIONTYPE/MotorCtrl</CONTEXT-COMPONENT-REF>
                        <TARGET-P-PORT-REF DEST="P-PORT-PROTOTYPE">/ComponentTypes/MotorCtrl/SigPP_Proto_TrqMeas</TARGET-P-PORT-REF>
                      </P-PORT-IN-COMPOSITION-INSTANCE-REF></INNER-PORT-IREF>
                      <OUTER-PORT-REF DEST="P-PORT-PROTOTYPE">/COM/COMPOSITIONTYPE/SigPP_Proto_TrqMeas</OUTER-PORT-REF>
                    </DELEGATION-SW-CONNECTOR>
                    <ASSEMBLY-SW-CONNECTOR><SHORT-NAME>MotorCtrl_PpInterFsm_Core1Diag</SHORT-NAME>
                      <PROVIDER-IREF><P-PORT-IN-COMPOSITION-INSTANCE-REF>
                        <CONTEXT-COMPONENT-REF DEST="SW-COMPONENT-PROTOTYPE">/COM/COMPOSITIONTYPE/MotorCtrl</CONTEXT-COMPONENT-REF>
                        <TARGET-P-PORT-REF DEST="P-PORT-PROTOTYPE">/ComponentTypes/MotorCtrl/PpInterFsm</TARGET-P-PORT-REF>
                      </P-PORT-IN-COMPOSITION-INSTANCE-REF></PROVIDER-IREF>
                      <REQUESTER-IREF><R-PORT-IN-COMPOSITION-INSTANCE-REF>
                        <CONTEXT-COMPONENT-REF DEST="SW-COMPONENT-PROTOTYPE">/COM/COMPOSITIONTYPE/Core1DiagSwc</CONTEXT-COMPONENT-REF>
                        <TARGET-R-PORT-REF DEST="R-PORT-PROTOTYPE">/ComponentTypes/Core1DiagSwc/RpInterFsm</TARGET-R-PORT-REF>
                      </R-PORT-IN-COMPOSITION-INSTANCE-REF></REQUESTER-IREF>
                    </ASSEMBLY-SW-CONNECTOR>
                  </CONNECTORS>
                </COMPOSITION-SW-COMPONENT-TYPE>
                <SYSTEM><SHORT-NAME>System</SHORT-NAME><MAPPINGS><SYSTEM-MAPPING><SHORT-NAME>Mappings</SHORT-NAME>
                  <DATA-MAPPINGS>
                    <SENDER-RECEIVER-TO-SIGNAL-MAPPING>
                      <DATA-ELEMENT-IREF>
                        <CONTEXT-COMPOSITION-REF DEST="ROOT-SW-COMPOSITION-PROTOTYPE">/COM/System/Root</CONTEXT-COMPOSITION-REF>
                        <CONTEXT-PORT-REF DEST="P-PORT-PROTOTYPE">/COM/COMPOSITIONTYPE/SigPP_Proto_TrqMeas</CONTEXT-PORT-REF>
                        <TARGET-DATA-PROTOTYPE-REF DEST="VARIABLE-DATA-PROTOTYPE">/PortInterfaces/If_TrqMeas/Val</TARGET-DATA-PROTOTYPE-REF>
                      </DATA-ELEMENT-IREF>
                      <SYSTEM-SIGNAL-REF DEST="SYSTEM-SIGNAL">/Signal/TrqMeas</SYSTEM-SIGNAL-REF>
                    </SENDER-RECEIVER-TO-SIGNAL-MAPPING>
                  </DATA-MAPPINGS>
                </SYSTEM-MAPPING></MAPPINGS></SYSTEM>
              </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
            </AUTOSAR>
        """),
        encoding="utf-8",
    )

    # 7. WorkspaceProject with Os, Com, ComM, Rte ECUC (added as custom packages so format_version=8 save/reload works cleanly)
    ws = WorkspaceManager()
    project = ws.create_project("Phase23Test", proj_dir / "Phase23Test.dpa", format_version=8)
    bswmd_dir = tmp_path / "bswmds"
    bswmd_dir.mkdir(parents=True, exist_ok=True)

    def _add_mod(name: str):
        p = bswmd_dir / f"{name}_bswmd.arxml"
        p.write_bytes(_minimal_module_def_arxml(name, pkg_prefix="MICROSAR"))
        return project.add_custom_module_from_file(p)

    # Os
    os_mgr = _add_mod("Os")
    os_cfg = os_mgr.configuration
    _c(os_cfg, "OsCore0", "/MICROSAR/Os/OsCore")
    _c(os_cfg, "OsCore1", "/MICROSAR/Os/OsCore")
    t_init0 = _c(os_cfg, "OsTask_ApplicationInit_Core0", "/MICROSAR/Os/OsTask")
    _p(t_init0, "OsTaskPriority", 50, "ECUC-INTEGER-PARAM-DEF")
    _p(t_init0, "OsTaskType", "BASIC", "ECUC-ENUMERATION-PARAM-DEF")
    t_c0 = _c(os_cfg, "OsTask_10ms_Core0", "/MICROSAR/Os/OsTask")
    _p(t_c0, "OsTaskPriority", 40, "ECUC-INTEGER-PARAM-DEF")
    _p(t_c0, "OsTaskType", "BASIC", "ECUC-ENUMERATION-PARAM-DEF")
    t_c1 = _c(os_cfg, "OsTask_10ms_Core1", "/MICROSAR/Os/OsTask")
    _p(t_c1, "OsTaskPriority", 40, "ECUC-INTEGER-PARAM-DEF")
    _p(t_c1, "OsTaskType", "BASIC", "ECUC-ENUMERATION-PARAM-DEF")
    _c(os_cfg, "OsAlarm_10ms_Core0", "/MICROSAR/Os/OsAlarm")

    app0 = _c(os_cfg, "SystemApplication_OsCore0", "/MICROSAR/Os/OsApplication")
    _r(app0, "OsApplicationCoreRef", "/ActiveEcuC/Os/OsCore0")
    _mr(app0, "OsAppTaskRef", ["/ActiveEcuC/Os/OsTask_ApplicationInit_Core0", "/ActiveEcuC/Os/OsTask_10ms_Core0"])
    _r(app0, "OsAppAlarmRef", "/ActiveEcuC/Os/OsAlarm_10ms_Core0")

    app1 = _c(os_cfg, "SystemApplication_OsCore1", "/MICROSAR/Os/OsApplication")
    _r(app1, "OsApplicationCoreRef", "/ActiveEcuC/Os/OsCore1")
    _r(app1, "OsAppTaskRef", "/ActiveEcuC/Os/OsTask_10ms_Core1")

    # Com
    com_mgr = _add_mod("Com")
    com_cc = _c(com_mgr.configuration, "ComConfig", "/MICROSAR/Com/ComConfig")
    s_tx = _c(com_cc, "TrqMeas_Tx", "/MICROSAR/Com/ComConfig/ComSignal")
    _r(s_tx, "ComSystemTemplateSystemSignalRef", "/PDU/MCU_Out/MCU_Out_PDU/TrqMeas", dt="ECUC-FOREIGN-REFERENCE-DEF", vdest="I-SIGNAL-TO-I-PDU-MAPPING")
    s_rx = _c(com_cc, "VcuCmd_Rx", "/MICROSAR/Com/ComConfig/ComSignal")
    _r(s_rx, "ComSystemTemplateSystemSignalRef", "/Signal/VcuCmd", dt="ECUC-FOREIGN-REFERENCE-DEF", vdest="SYSTEM-SIGNAL")
    ipdu_tx = _c(com_cc, "MCU_Out_Tx", "/MICROSAR/Com/ComConfig/ComIPdu")
    _p(ipdu_tx, "ComIPduDirection", "SEND", "ECUC-ENUMERATION-PARAM-DEF")
    _r(ipdu_tx, "ComIPduSignalRef", "/ActiveEcuC/Com/ComConfig/TrqMeas_Tx")
    ipdu_rx = _c(com_cc, "VCU_In_Rx", "/MICROSAR/Com/ComConfig/ComIPdu")
    _p(ipdu_rx, "ComIPduDirection", "RECEIVE", "ECUC-ENUMERATION-PARAM-DEF")
    _r(ipdu_rx, "ComIPduSignalRef", "/ActiveEcuC/Com/ComConfig/VcuCmd_Rx")

    # ComM module
    _add_mod("ComM")

    # Rte
    rte_mgr = _add_mod("Rte")
    rte_cfg = rte_mgr.configuration
    rgen = _c(rte_cfg, "RteGeneration", "/MICROSAR/Rte/RteGeneration")
    _p(rgen, "RteEnableMultiCore", True)
    _p(rgen, "RteDisableRteInitMemory", False)

    comm_bsw = _c(rte_cfg, "ComM", "/MICROSAR/Rte/RteBswModuleInstance")
    _r(comm_bsw, "RteBswModuleConfigurationRef", "/ActiveEcuC/ComM", dt="ECUC-FOREIGN-REFERENCE-DEF")
    com_bsw = _c(rte_cfg, "Com", "/MICROSAR/Rte/RteBswModuleInstance")
    _r(com_bsw, "RteBswModuleConfigurationRef", "/ActiveEcuC/Com", dt="ECUC-FOREIGN-REFERENCE-DEF")

    # SWC Instances in Rte ECUC
    mc_ecuc = _c(rte_cfg, "MotorCtrl_EcuSwComposition", "/MICROSAR/Rte/RteSwComponentInstance")
    _r(mc_ecuc, "RteSoftwareComponentInstanceRef", "/COM/COMPOSITIONTYPE/MotorCtrl", dt="ECUC-FOREIGN-REFERENCE-DEF", vdest="SW-COMPONENT-PROTOTYPE")
    mc_map = _c(mc_ecuc, "Tmr_MotorCtrl_10ms", "/MICROSAR/Rte/RteSwComponentInstance/RteEventToTaskMapping")
    _r(mc_map, "RteEventRef", "/ComponentTypes/MotorCtrl/MotorCtrl_IB/Tmr_MotorCtrl_10ms", dt="ECUC-FOREIGN-REFERENCE-DEF", vdest="TIMING-EVENT")
    _r(mc_map, "RteMappedToTaskRef", "/ActiveEcuC/Os/OsTask_10ms_Core0")
    _p(mc_map, "RtePositionInTask", 0, "ECUC-INTEGER-PARAM-DEF")

    c1_ecuc = _c(rte_cfg, "Core1DiagSwc_EcuSwComposition", "/MICROSAR/Rte/RteSwComponentInstance")
    _r(c1_ecuc, "RteSoftwareComponentInstanceRef", "/COM/COMPOSITIONTYPE/Core1DiagSwc", dt="ECUC-FOREIGN-REFERENCE-DEF", vdest="SW-COMPONENT-PROTOTYPE")
    c1_map = _c(c1_ecuc, "Tmr_Core1Diag_10ms", "/MICROSAR/Rte/RteSwComponentInstance/RteEventToTaskMapping")
    _r(c1_map, "RteEventRef", "/ComponentTypes/Core1DiagSwc/Core1DiagSwc_IB/Tmr_Core1Diag_10ms", dt="ECUC-FOREIGN-REFERENCE-DEF", vdest="TIMING-EVENT")
    _r(c1_map, "RteMappedToTaskRef", "/ActiveEcuC/Os/OsTask_10ms_Core1")
    _p(c1_map, "RtePositionInTask", 0, "ECUC-INTEGER-PARAM-DEF")

    cm_ecuc = _c(rte_cfg, "ComM_EcuSwComposition", "/MICROSAR/Rte/RteSwComponentInstance")
    _r(cm_ecuc, "RteSoftwareComponentInstanceRef", "/COM/COMPOSITIONTYPE/ComM", dt="ECUC-FOREIGN-REFERENCE-DEF", vdest="SW-COMPONENT-PROTOTYPE")

    os_int = _c(rte_cfg, "RteOsInteraction", "/MICROSAR/Rte/RteOsInteraction")
    act0 = _c(os_int, "Act_OsTask_10ms_Core0", "/MICROSAR/Rte/RteOsInteraction/RteUsedOsActivation")
    _r(act0, "RteActivationOsTaskRef", "/ActiveEcuC/Os/OsTask_10ms_Core0")
    _r(act0, "RteActivationOsAlarmRef", "/ActiveEcuC/Os/OsAlarm_10ms_Core0")
    _p(act0, "RteExpectedTickDuration", 0.01, "ECUC-FLOAT-PARAM-DEF")

    ws.save_project()
    return project, proj_dir, ws


def test_swc_parser_indexes_types_interfaces_connectors_and_isignal(tmp_path):
    project, proj_dir, _ = build_phase23_project(tmp_path)
    idx = SwcSystemIndex.load_directory(proj_dir / "system")

    assert "MotorCtrl" in idx.swc_types_by_name
    assert "ComM" in idx.swc_types_by_name and idx.swc_types_by_name["ComM"].is_service is True
    assert idx.isig_mapping_to_sys_sig.get("/PDU/MCU_Out/MCU_Out_PDU/TrqMeas") == "/Signal/TrqMeas"
    assert ("MotorCtrl", "SigPP_Proto_TrqMeas") in idx.sr_mapping_by_comp_port
    assert idx.resolve_c_type_name("/DataTypes/SigTrq_ADT") == "SigTrq_Type"
    assert idx.swc_types_by_name["ComM"].ports["UR_CN_CAN00"].port_arg_values[0][1] == "0"


def test_data_mapping_service_mapping_auto_match_and_dpa_roundtrip(tmp_path):
    project, proj_dir, ws = build_phase23_project(tmp_path)
    svc = RteWorkbenchService(project)

    dm_rows = {(r.component_name, r.port_name): r for r in svc.list_data_mapping_rows()}
    assert dm_rows[("MotorCtrl", "SigPP_Proto_TrqMeas")].status == "mapped"
    assert dm_rows[("MotorCtrl", "SigPP_Proto_TrqMeas")].com_signal_name == "TrqMeas_Tx"
    assert dm_rows[("MotorCtrl", "PpInterFsm")].status == "inter_swc"
    assert dm_rows[("Core1DiagSwc", "RpInterFsm")].status == "inter_swc"
    assert dm_rows[("MotorCtrl", "SigRP_Proto_VcuCmd")].status == "unmapped"

    # Auto match VcuCmd_Rx -> SigRP_Proto_VcuCmd
    assert svc.auto_match_data_mappings() == 1
    dm_after = {(r.component_name, r.port_name): r for r in svc.list_data_mapping_rows()}
    assert dm_after[("MotorCtrl", "SigRP_Proto_VcuCmd")].com_signal_name == "VcuCmd_Rx"
    assert dm_after[("MotorCtrl", "SigRP_Proto_VcuCmd")].status == "mapped"

    # Service port auto connect & diagnostics
    sp_before = {(r.requester_component, r.requester_port): r for r in svc.list_service_port_rows()}
    assert sp_before[("MotorCtrl", "UR_CN_CAN00")].status == "unconnected"
    assert any(d.code == "SERVICE_PORT_UNCONNECTED" and d.workbench_tab == 4 for d in svc.collect_diagnostics())

    assert svc.auto_connect_service_ports() == 1
    sp_after = {(r.requester_component, r.requester_port): r for r in svc.list_service_port_rows()}
    assert sp_after[("MotorCtrl", "UR_CN_CAN00")].status == "connected"
    assert sp_after[("MotorCtrl", "UR_CN_CAN00")].provider_component == "ComM"
    assert sp_after[("MotorCtrl", "UR_CN_CAN00")].server_symbol == "ComM_RequestComMode"

    # Provoke direction mismatch & broken ComSignal diagnostics (tab 3)
    svc.set_data_mapping("MotorCtrl", "SigRP_Proto_VcuCmd", "TrqMeas_Tx", direction="RX")
    assert any(d.code == "DATA_MAPPING_DIRECTION_MISMATCH" and d.workbench_tab == 3 for d in svc.collect_diagnostics())
    svc.set_data_mapping("MotorCtrl", "SigRP_Proto_VcuCmd", "NonExistent_Sig", direction="RX")
    assert any(d.code == "DATA_MAPPING_BROKEN_COM_SIGNAL" and d.workbench_tab == 3 for d in svc.collect_diagnostics())
    svc.set_data_mapping("MotorCtrl", "SigRP_Proto_VcuCmd", "VcuCmd_Rx", direction="RX")

    # SWC Event-to-Task map/unmap & reorder
    _, unmapped_swc = svc.list_task_mappings(include_swc=True, include_unmapped_swc=True)
    init_ev = next(r for r in unmapped_swc if r.is_swc and r.event_name == "Init_MotorCtrl")
    svc.map_swc_event_to_task(
        init_ev.instance_name,
        init_ev.event_name,
        "OsTask_ApplicationInit_Core0",
        event_ref=init_ev.event_ref,
        event_kind=init_ev.event_kind,
    )
    mapped_by_task, _ = svc.list_task_mappings(include_swc=True)
    assert any(r.symbol_or_name if hasattr(r, "symbol_or_name") else r.entity_name == "MotorCtrl_Init" for r in mapped_by_task["OsTask_ApplicationInit_Core0"])

    # Save .dpa and reload -> overlays persist cleanly
    ws.save_project()
    reloaded, failed = WorkspaceManager().load_project(proj_dir / "Phase23Test.dpa")
    assert not failed
    svc2 = RteWorkbenchService(reloaded)
    dm2 = {(r.component_name, r.port_name): r for r in svc2.list_data_mapping_rows()}
    sp2 = {(r.requester_component, r.requester_port): r for r in svc2.list_service_port_rows()}
    assert dm2[("MotorCtrl", "SigRP_Proto_VcuCmd")].com_signal_name == "VcuCmd_Rx"
    assert sp2[("MotorCtrl", "UR_CN_CAN00")].provider_component == "ComM"


def test_phase2_phase3_generation_and_clang_syntax_check(tmp_path):
    project, proj_dir, _ = build_phase23_project(tmp_path)
    svc = RteWorkbenchService(project)
    svc.auto_match_data_mappings()
    svc.auto_connect_service_ports()
    _, unmapped_swc = svc.list_task_mappings(include_swc=True, include_unmapped_swc=True)
    init_ev = next(r for r in unmapped_swc if r.is_swc and r.event_name == "Init_MotorCtrl")
    svc.map_swc_event_to_task(
        init_ev.instance_name,
        init_ev.event_name,
        "OsTask_ApplicationInit_Core0",
        event_ref=init_ev.event_ref,
        event_kind=init_ev.event_kind,
    )

    gen_root = proj_dir / "gen"
    report = RteSchMGenerator(project, include_phase2_3=True).generate(gen_root, flat=False)
    assert report.ok

    inc = gen_root / "Rte/include"
    src = gen_root / "Rte/src"
    assert (inc / "Rte_Type.h").is_file()
    assert (inc / "Rte_DataHandleType.h").is_file()
    assert (inc / "Components/Rte_MotorCtrl.h").is_file()
    assert (inc / "Components/Rte_MotorCtrl_Type.h").is_file()
    assert (inc / "Components/Rte_Core1DiagSwc.h").is_file()
    assert (inc / "Components/Rte_ComM.h").is_file()
    assert (src / "Rte.c").is_file()
    assert (src / "Rte_SystemApplication_OsCore0.c").is_file()
    assert (src / "Rte_SystemApplication_OsCore1.c").is_file()

    rte_type_txt = (inc / "Rte_Type.h").read_text(encoding="utf-8")
    assert "typedef uint16 SigTrq_Type;" in rte_type_txt
    assert "typedef struct" in rte_type_txt and "MotorInfo_Struct;" in rte_type_txt

    rte_c_txt = (src / "Rte.c").read_text(encoding="utf-8")
    assert "SchM_StartTimingCore0" in rte_c_txt
    assert "ActivateTask(OsTask_ApplicationInit_Core0)" in rte_c_txt

    core0_txt = (src / "Rte_SystemApplication_OsCore0.c").read_text(encoding="utf-8")
    assert "Com_SendSignal(ComConf_ComSignal_TrqMeas_Tx" in core0_txt
    assert "Com_ReceiveSignal(ComConf_ComSignal_VcuCmd_Rx" in core0_txt
    assert "ComM_RequestComMode(0U, ComMode)" in core0_txt
    assert "VAR(FsmState_Type, RTE_VAR_INIT) Rte_MotorCtrl_PpInterFsm_State = 1U;" in core0_txt
    assert "TASK(OsTask_10ms_Core0)" in core0_txt and "MotorCtrl_10ms();" in core0_txt

    core1_txt = (src / "Rte_SystemApplication_OsCore1.c").read_text(encoding="utf-8")
    assert "TASK(OsTask_10ms_Core1)" in core1_txt and "Core1Diag_10ms();" in core1_txt

    clang = shutil.which("clang")
    if clang:
        stub_dir = tmp_path / "stubs"
        stub_dir.mkdir(parents=True, exist_ok=True)
        (stub_dir / "Platform_Types.h").write_text(
            "typedef unsigned char boolean;\n"
            "typedef unsigned char uint8;\ntypedef unsigned short uint16;\n"
            "typedef unsigned int uint32;\ntypedef unsigned long long uint64;\n"
            "typedef signed char sint8;\ntypedef signed short sint16;\n"
            "typedef signed int sint32;\ntypedef signed long long sint64;\n"
            "typedef float float32;\ntypedef double float64;\n"
            "#define TRUE ((boolean)1)\n#define FALSE ((boolean)0)\n",
            encoding="utf-8",
        )
        (stub_dir / "Compiler.h").write_text(
            "#define FUNC(rettype, memclass) rettype\n"
            "#define VAR(vartype, memclass) vartype\n"
            "#define P2VAR(ptrtype, memclass, ptrclass) ptrtype *\n"
            "#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype *\n"
            "#define AUTOMATIC\n#define NULL_PTR ((void *)0)\n",
            encoding="utf-8",
        )
        (stub_dir / "Std_Types.h").write_text(
            '#include "Platform_Types.h"\n#include "Compiler.h"\n'
            "typedef uint8 Std_ReturnType;\n#define E_OK ((Std_ReturnType)0U)\n#define E_NOT_OK ((Std_ReturnType)1U)\n",
            encoding="utf-8",
        )
        (stub_dir / "Os.h").write_text(
            '#include "Std_Types.h"\n'
            "typedef uint32 TickType;\ntypedef uint32 EventMaskType;\ntypedef uint8 TaskType;\n"
            "#define TASK(x) void x(void)\n"
            "uint32 GetCoreID(void); void SuspendAllInterrupts(void); void ResumeAllInterrupts(void);\n"
            "void SuspendOSInterrupts(void); void ResumeOSInterrupts(void);\n"
            "#define ActivateTask(t) ((void)#t)\n"
            "Std_ReturnType TerminateTask(void);\n"
            "Std_ReturnType SetRelAlarm(uint32 a, TickType i, TickType c); Std_ReturnType CancelAlarm(uint32 a);\n"
            "Std_ReturnType StartScheduleTableRel(uint32 s, TickType o);\n"
            "#define WaitEvent(m) ((void)(m))\n"
            "#define GetEvent(t, e) ((void)(e))\n"
            "#define ClearEvent(e) ((void)(e))\n"
            "extern uint32 OsAlarm_10ms_Core0;\n",
            encoding="utf-8",
        )
        (stub_dir / "Com.h").write_text(
            '#include "Std_Types.h"\n'
            "#define ComConf_ComSignal_TrqMeas_Tx (0U)\n"
            "#define ComConf_ComSignal_VcuCmd_Rx (1U)\n"
            "Std_ReturnType Com_SendSignal(uint16 s, const void *d);\n"
            "Std_ReturnType Com_ReceiveSignal(uint16 s, void *d);\n",
            encoding="utf-8",
        )
        for mm in ("MemMap.h", "Rte_MemMap.h", "MotorCtrl_MemMap.h", "Core1DiagSwc_MemMap.h", "ComM_MemMap.h", "Com_MemMap.h"):
            (stub_dir / mm).write_text("/* stub */\n", encoding="utf-8")

        app_c = tmp_path / "MotorCtrl_AppTest.c"
        app_c.write_text(
            '#include "Components/Rte_MotorCtrl.h"\n'
            "void app_usage_smoke(void) {\n"
            "  FsmState_Type cmd = 0U;\n"
            "  (void)Rte_Read_SigRP_Proto_VcuCmd_Cmd(&cmd);\n"
            "  (void)Rte_Write_SigPP_Proto_TrqMeas_Val(500U);\n"
            "  (void)Rte_Write_PpInterFsm_State(cmd);\n"
            "  (void)Rte_Call_UR_CN_CAN00_RequestComMode(2U);\n"
            "}\n",
            encoding="utf-8",
        )

        for cfile in (src / "Rte.c", src / "Rte_SystemApplication_OsCore0.c", src / "Rte_SystemApplication_OsCore1.c", app_c):
            proc = subprocess.run(
                [clang, "-fsyntax-only", "-Wall", "-Wextra", "-Werror", f"-I{stub_dir}", f"-I{inc}", f"-I{inc / 'Components'}", str(cfile)],
                capture_output=True,
                text=True,
            )
            assert proc.returncode == 0, f"clang failed for {cfile.name}:\n{proc.stderr}"


def test_real_startapplication1_dpa_phase2_phase3_readonly(tmp_path):
    real_dpa = Path("/Users/qlwang/Desktop/test3/StartApplication1/StartApplication1.dpa")
    if not real_dpa.is_file():
        pytest.skip("External StartApplication1.dpa fixture not available")

    proj, _ = WorkspaceManager().load_project(real_dpa)
    svc = RteWorkbenchService(proj)

    dm_rows = svc.list_data_mapping_rows()
    sp_rows = svc.list_service_port_rows()
    swc_rows = svc.list_swc_instance_rows()
    assert len(swc_rows) >= 5
    assert any(r.status == "mapped" and r.com_signal_name for r in dm_rows)
    assert any(r.status == "connected" for r in sp_rows)

    out_dir = tmp_path / "sa_p23_out"
    report = RteSchMGenerator(proj, include_phase2_3=True).generate(out_dir, flat=False)
    assert report.ok

    inc = out_dir / "Rte/include"
    src = out_dir / "Rte/src"
    assert (inc / "Rte_DataHandleType.h").is_file()
    assert (inc / "Components/Rte_McuFsmComponent.h").is_file()
    assert (inc / "Components/Rte_ComM.h").is_file()
    assert (src / "Rte.c").is_file()
    assert (src / "Rte_SystemApplication_OsCore0.c").is_file()
    assert (src / "Rte_SystemApplication_OsCore1.c").is_file()

    c0 = (src / "Rte_SystemApplication_OsCore0.c").read_text(encoding="utf-8")
    c1 = (src / "Rte_SystemApplication_OsCore1.c").read_text(encoding="utf-8")
    assert "Com_SendSignal(" in c0
    assert "Com_ReceiveSignal(" in c0
    assert "TASK(OsTask_100ms_Core0)" in c0 and "RunnableUserTest();" in c0
    assert "TASK(OsTask_10ms_Core1)" in c1
