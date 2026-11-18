"""Task 3-RED: MCAL 资源提取。

从 EB plugin Resource 的 .properties 文件提取可用资源，生成 chip YAML 约束。

资源格式示例（来自真实 SIP 结构）：
- Port.AvailableEXTIModule: _1_  （EXTI 模块数）
- Uart.AvailableModule_0: Uart1_0  （可用 UART 实例）
- MemoryPartition.AvailablePartitions: PARTITION_0, PARTITION_1  （内存分区）

输出格式：YAML，记录 chip 的资源约束（给 task 4 CLI 使用）
"""

import pytest
from pathlib import Path
import tempfile
import yaml

from autosar_configurator.core.davinci_importer import McalResourceExtractor


class TestMcalResourceExtractor:
    """从 plugin Resource 的 .properties 提取资源。"""

    def test_extract_resources_from_properties(self):
        """从 .properties 文件读取资源列表。"""
        properties_content = """
# Port driver
Port.AvailableEXTIModule: _1_
Port.AvailableModule_0: Port_0
Port.AvailableModule_1: Port_1

# UART
Uart.AvailableModule_0: Uart1_0
Uart.AvailableModule_1: Uart1_1

# SPI
Spi.AvailableModule_0: Spi_0
"""

        with tempfile.TemporaryDirectory() as tmp_path:
            tmp_path = Path(tmp_path)

            # 创建 properties 文件
            resource_dir = tmp_path / "resource"
            resource_dir.mkdir()
            (resource_dir / "resources.properties").write_text(properties_content)

            extractor = McalResourceExtractor(tmp_path)
            resources = extractor.extract_from_properties(resource_dir / "resources.properties")

            # 验证提取结果
            assert "Port" in resources
            assert resources["Port"]["AvailableEXTIModule"] == "_1_"
            assert resources["Port"]["AvailableModule_0"] == "Port_0"

            assert "Uart" in resources
            assert resources["Uart"]["AvailableModule_0"] == "Uart1_0"

    def test_extract_resources_scoped_by_chip(self):
        """资源按 chip 子目录组织。"""
        with tempfile.TemporaryDirectory() as tmp_path:
            tmp_path = Path(tmp_path)

            # 模拟 DaVinci 结构：Components/Port/GeneratorMsr/resource/<chip>/
            chip1_dir = tmp_path / "Components" / "Port" / "GeneratorMsr" / "resource" / "Generic_CortexR52_ASIMD"
            chip1_dir.mkdir(parents=True)
            (chip1_dir / "resources.properties").write_text("""
Port.AvailableModule_0: Port_0
Port.AvailableModule_1: Port_1
""")

            chip2_dir = tmp_path / "Components" / "Port" / "GeneratorMsr" / "resource" / "S32Gxx"
            chip2_dir.mkdir(parents=True)
            (chip2_dir / "resources.properties").write_text("""
Port.AvailableModule_0: Port_0
""")

            extractor = McalResourceExtractor(tmp_path)
            all_resources = extractor.extract_all_chips_resources()

            # 验证：应该按 chip 分组
            assert len(all_resources) >= 2
            # 至少包含两个 chip 的资源

    def test_extract_and_generate_yaml_constraint(self):
        """提取资源并生成 YAML 约束文件。"""
        with tempfile.TemporaryDirectory() as tmp_path:
            tmp_path = Path(tmp_path)

            # 创建 chip 资源目录
            chip_dir = tmp_path / "Components" / "Port" / "GeneratorMsr" / "resource" / "MyChip"
            chip_dir.mkdir(parents=True)
            (chip_dir / "resources.properties").write_text("""
Port.AvailableModule_0: Port_0
Port.AvailableModule_1: Port_1
Port.AvailableEXTIModule: _2_
Uart.AvailableModule_0: Uart1_0
""")

            extractor = McalResourceExtractor(tmp_path)

            # 提取并生成 YAML
            yaml_output = tmp_path / "chip_resources.yaml"
            extractor.extract_and_generate_yaml("MyChip", yaml_output)

            # 验证 YAML 文件
            assert yaml_output.exists()
            with open(yaml_output) as f:
                data = yaml.safe_load(f)

            assert "Port" in data
            assert data["Port"]["AvailableModule_0"] == "Port_0"
            assert data["Uart"]["AvailableModule_0"] == "Uart1_0"

    def test_extract_handles_missing_properties(self):
        """properties 文件缺失时返回空。"""
        with tempfile.TemporaryDirectory() as tmp_path:
            tmp_path = Path(tmp_path)

            extractor = McalResourceExtractor(tmp_path)
            resources = extractor.extract_from_properties(tmp_path / "missing.properties")

            assert resources == {}

    def test_extract_handles_malformed_properties(self):
        """格式不对的行（如不含 =）被跳过。"""
        properties_content = """
# Comment
Port.AvailableModule_0=Port_0
InvalidLine
Uart.AvailableModule_0=Uart1_0
"""

        with tempfile.TemporaryDirectory() as tmp_path:
            tmp_path = Path(tmp_path)
            props_file = tmp_path / "resources.properties"
            props_file.write_text(properties_content)

            extractor = McalResourceExtractor(tmp_path)
            resources = extractor.extract_from_properties(props_file)

            # InvalidLine 应被忽略
            assert "Port" in resources
            assert "Uart" in resources
            assert len(resources) == 2
