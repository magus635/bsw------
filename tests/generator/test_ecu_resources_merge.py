"""The generator merges ECU resources from every selected .properties file."""
from autosar_configurator.generator.generator import CodeGenerator


def test_resources_from_several_properties_files_are_merged(tmp_path):
    res = tmp_path / "Def" / "plugins"
    (res / "Os_X" / "resource").mkdir(parents=True)
    (res / "Resource_X" / "resource").mkdir(parents=True)
    (res / "Os_X" / "resource" / "Os_Resource_THA6206.properties").write_text(
        "OsResource.NumOfCores: 2\n", encoding="utf-8")
    (res / "Resource_X" / "resource" / "CotexR52_THA6206_LFBGA292.properties").write_text(
        "Port.AvailablePortsTotalNumber: 7\n", encoding="utf-8")
    (res / "Resource_X" / "resource" / "CotexR52_THA610X_LFBGA180.properties").write_text(
        "Port.Other: 1\n", encoding="utf-8")
    templates = tmp_path / "templates"
    templates.mkdir()

    gen = CodeGenerator.__new__(CodeGenerator)
    gen.project_template_dir = templates
    gen.selected_chip = "THA6206_LFBGA292"
    resources = gen._load_ecu_resources()

    assert resources["OsResource.NumOfCores"] == 2
    assert resources["Port.AvailablePortsTotalNumber"] == 7
    assert "Port.Other" not in resources
