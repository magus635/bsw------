"""[废弃] 标记：只在描述里有明确的弃用措辞时标记，并且标记行只置灰、仍可编辑。

用例文本取自真实厂商定义文件（Adc/Lin/Spi/Pwm/Fls 的 THA6 MCAL arxml），
误报组是调查中确认过的活参数描述（如 SpiMainFunctionPeriod、PwmChannelCoherentSelection）。
"""
import pytest

PySide6 = pytest.importorskip("PySide6")

from autosar_configurator.core.baseline.origin import Origin
from autosar_configurator.core.model.configuration_model import (
    EcucContainerValue, EcucParameterValue)
from autosar_configurator.core.model.definition_model import (
    EcucContainerDef, EcucParameterDef, EcucParameterType)
from autosar_configurator.ui.widgets.davinci_config_panel import DaVinciConfigPanel


def _param(description):
    return EcucParameterDef(short_name="P", param_type=EcucParameterType.STRING,
                            definition_ref="/Vendor/M/C/P", description=description)


def _flagged(description):
    # 方法不读 self，直接以未绑定形式调用
    return DaVinciConfigPanel._is_deprecated_parameter(None, _param(description))


DEPRECATED_NOTES = [
    # Adc AdcClockSource
    "The ADC module specific clock input can statically be configured. <h1>Note</h1> "
    "This parameter is not used and has been replaced by AdcConfigSet/AdcAnalogClockSource.",
    # Adc AdcChannelConvTime
    "Configuration of conversion time for each channel. <h1>Note</h1>This parameter is not used.",
    # Adc AdcChannelRefVoltsrcHigh
    "Upper reference voltage source for each channel. <h1>Note</h1>"
    "Not supported on Adc Channel and has been replaced by AdcHwUnit/AdcRefVoltHigh.",
    # Lin LinClockRef
    "Reference to the LIN clock source configuration. <h1>Note</h1> "
    "This parameter is not used, replaced by 'LinClockSet/LinSysClockRef'",
    # Spi SpiMaxChannel
    "This parameter is not used, the max number of channels will be auto calculated "
    "when 'SpiChannel' container configurated.",
    "This parameter is deprecated and will be removed in a future release.",
    "This parameter is obsolete.",
    "Do not use this parameter. Use AdcNewParam instead.",
]

ACTIVE_NOTES = [
    # SecOCMaxAlignScalarType（Vector SecOC bswmd：required=LOWER-MULTIPLICITY 1，但"不被生成器使用"）
    "The scalar type which has the maximum alignment restrictions on the given platform. "
    "This type can be e.g. uint8, uint16 or uint32.\n\nThis parameter is NOT used by the generator.",
    # SpiMainFunctionPeriod（标准参数 ECUC_Spi_00242，被上层使用）
    "ECUC_Spi_00242: This parameter defines the cycle time of the function "
    "Spi_MainFunction_Handling in seconds. The parameter is not used by the driver "
    "it self, but it is used by upper layer.",
    # PwmChannelCoherentSelection（它让别的参数失效，自己是活的）
    "Switch for enabling the update of the period / duty parameter at the end of the "
    "current period. Switching on this parameter obsoletes PwmDutycycleUpdatedEndperiod "
    "and PwmPeriodUpdatedEndperiod.",
    # Fls 外部驱动容器说明（描述别人不用它的场景，不是弃用）
    "This container is present for external Flash drivers only. Internal Flash drivers "
    "do not use the parameter listed in this container, hence its multiplicity is 0 "
    "for internal drivers.",
    # 描述里提到的是“被它取代的那个”废弃参数
    "This parameter replaces the deprecated parameter AdcOldClockSource.",
    # 可选替换，不是弃用
    "The default value can be replaced by a user defined callback at run time.",
    "",
]


@pytest.mark.parametrize("desc", DEPRECATED_NOTES)
def test_vendor_deprecation_notes_are_flagged(desc):
    assert _flagged(desc) is True


@pytest.mark.parametrize("desc", ACTIVE_NOTES)
def test_active_parameter_descriptions_are_not_flagged(desc):
    assert _flagged(desc) is False


class _Manager:
    """面板需要的最小 manager：无锁、来源 REC。"""
    prototype = None

    def check_editable(self, instance, name=None):
        return None

    def value_origin(self, instance, name):
        return Origin.REC

    def pre_unlock_state(self, instance, name):
        return None


def _show(qtbot, description):
    container = EcucContainerDef(short_name="C", definition_ref="/Vendor/M/C")
    container.parameters["P"] = _param(description)
    instance = EcucContainerValue(short_name="C", definition_ref="/Vendor/M/C")
    instance.parameter_values["P"] = EcucParameterValue(
        definition_ref="/Vendor/M/C/P", value="x")
    panel = DaVinciConfigPanel()
    qtbot.addWidget(panel)
    panel.show_instance(instance, container, _Manager())
    return panel


def test_deprecated_row_is_greyed_but_still_editable(qtbot):
    panel = _show(qtbot, "<h1>Note</h1>This parameter is not used.")
    item = panel.params_table.item(0, 0)
    assert item.text().startswith("[废弃]")
    assert "废弃" in item.toolTip()
    assert item.background().color().name().upper() == "#CCCCCC"   # 置灰
    assert panel.params_table.cellWidget(0, 1).isEnabled() is True  # 但仍可编辑


def test_qualified_usage_note_is_not_marked(qtbot):
    panel = _show(qtbot, "The parameter is not used by the driver it self, "
                         "but it is used by upper layer.")
    item = panel.params_table.item(0, 0)
    assert "[废弃]" not in item.text()
    assert panel.params_table.cellWidget(0, 1).isEnabled() is True
