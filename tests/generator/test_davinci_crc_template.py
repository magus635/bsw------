from pathlib import Path
from lxml import etree

from autosar_configurator.core.parser.arxml_parser import ArxmlParser
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.generator.generator import CodeGenerator

REPO_ROOT = Path(__file__).resolve().parents[2]
CRC_TEMPLATE_DIR = REPO_ROOT / "template_packs" / "davinci" / "Crc"
CRC_BSWMD = Path(r"D:\davinci\mcuapp\Components\Crc\BSWMD\Crc_bswmd.arxml")
CRC_ECUC = Path(r"D:\davinci\mcuapp\Applications\SipAddon\StartApplication\Config\ECUC\StartApplication_Crc_Crc_ecuc.arxml")
CRC_REF_H = Path(r"D:\davinci\mcuapp\Applications\SipAddon\StartApplication\Appl\GenData\Crc_Cfg.h")


def _load_crc():
    mod_def = EcucDefParser().parse_module_def_file(CRC_BSWMD)
    tree = etree.parse(str(CRC_ECUC))
    elem = tree.xpath('//*[local-name()="ECUC-MODULE-CONFIGURATION-VALUES"]')[0]
    cfg = ArxmlParser().parse_ecuc_configuration_values(elem)
    return mod_def, cfg


def _extract_body(text: str) -> str:
    marker = "/**** Protection against multiple inclusion"
    idx = text.index(marker)
    return text[idx:].replace("\r\n", "\n").rstrip("\n")


def test_crc_cfg_h_matches_davinci_reference_body_byte_for_byte(tmp_path):
    mod_def, cfg = _load_crc()
    gen = CodeGenerator(mod_def, cfg, package_template_dir=CRC_TEMPLATE_DIR)

    ok = gen.generate_all(tmp_path, flat=True)
    assert ok is True
    assert gen.last_status == "generated"

    out_file = tmp_path / "include" / "Crc_Cfg.h"
    assert out_file.is_file()

    generated_text = out_file.read_text(encoding="utf-8")
    reference_text = CRC_REF_H.read_text(encoding="utf-8")

    assert "Vector Informatik GmbH" not in generated_text
    assert "BETA VERSION" not in generated_text
    assert _extract_body(generated_text) == _extract_body(reference_text)


def test_crc_cfg_h_reflects_all_config_switches(tmp_path):
    mod_def, cfg = _load_crc()
    params = cfg.containers[0].parameter_values
    params["Crc8Mode"].value = "CRC_8_RUNTIME"
    params["Crc8H2FMode"].value = "CRC_8H2F_RUNTIME"
    params["Crc16Mode"].value = "CRC_16_TABLE_8"
    params["Crc32Mode"].value = "CRC_32_RUNTIME"
    params["Crc32P4Mode"].value = "CRC_32P4_TABLE_4"
    params["Crc64Mode"].value = "CRC_64_TABLE_8"
    params["CrcVersionInfoApi"].value = True

    gen = CodeGenerator(mod_def, cfg, package_template_dir=CRC_TEMPLATE_DIR)
    ok = gen.generate_all(tmp_path, flat=True)
    assert ok is True

    text = (tmp_path / "include" / "Crc_Cfg.h").read_text(encoding="utf-8")
    assert "# define CRC_8_MODE              (CRC_8_RUNTIME)" in text
    assert "# define CRC_8H2F_MODE           (CRC_8H2F_RUNTIME)" in text
    assert "# define CRC_16_MODE             (CRC_16_TABLE_8)" in text
    assert "# define CRC_32_MODE             (CRC_32_RUNTIME)" in text
    assert "# define CRC_32P4_MODE           (CRC_32P4_TABLE_4)" in text
    assert "# define CRC_64_MODE             (CRC_64_TABLE_8)" in text
    assert "# define CRC_VERSION_INFO_API    (STD_ON)" in text


def test_crc_cfg_h_uses_bswmd_defaults_when_container_omitted(tmp_path):
    mod_def, cfg = _load_crc()
    cfg.containers.clear()

    gen = CodeGenerator(mod_def, cfg, package_template_dir=CRC_TEMPLATE_DIR)
    ok = gen.generate_all(tmp_path, flat=True)
    assert ok is True
    assert gen.last_status == "generated"
    text = (tmp_path / "include" / "Crc_Cfg.h").read_text(encoding="utf-8")
    assert "# define CRC_8_MODE              (CRC_8_TABLE)" in text
    assert "# define CRC_VERSION_INFO_API    (STD_OFF)" in text


def test_crc_cfg_h_errors_when_crc_general_missing(tmp_path):
    mod_def, cfg = _load_crc()
    mod_def.containers.pop("CrcGeneral", None)
    cfg.containers.clear()

    gen = CodeGenerator(mod_def, cfg, package_template_dir=CRC_TEMPLATE_DIR)
    ok = gen.generate_all(tmp_path, flat=True)
    assert ok is False
    assert gen.last_status == "failed"
