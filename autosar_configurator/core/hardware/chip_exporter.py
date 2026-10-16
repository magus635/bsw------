"""
Chip Definition Exporter

Exports ChipDefinition objects to standard YAML format (matching data/chips/<name>.yaml)
and EB Tresos compatible .properties resource files.
"""
import os
import tempfile
from pathlib import Path
from typing import Dict, List, Optional, Any
import yaml

from .chip_database import ChipDefinition
from .ecu_resource_data import serialize_value


class _FlowMap(dict):
    """Mapping emitted in YAML flow style ({ k: v }) - one pin per line."""


class _BlockMap(dict):
    """Mapping emitted in YAML block style (index range notation, one range per line)."""


class _ChipYamlDumper(yaml.SafeDumper):
    pass


_ChipYamlDumper.add_representer(
    _FlowMap,
    lambda dumper, data: dumper.represent_mapping('tag:yaml.org,2002:map', data.items(), flow_style=True),
)


_ChipYamlDumper.add_representer(
    _BlockMap,
    lambda dumper, data: dumper.represent_mapping('tag:yaml.org,2002:map', data.items(), flow_style=False),
)


def _atomic_write_text(target_path: Path, content: str):
    """Write via a temp file + rename so a failed write never truncates an existing file"""
    target_path = Path(target_path)
    target_path.parent.mkdir(parents=True, exist_ok=True)
    fd, tmp = tempfile.mkstemp(dir=target_path.parent, prefix=f".{target_path.name}.", suffix=".tmp")
    try:
        with os.fdopen(fd, 'w', encoding='utf-8') as f:
            f.write(content)
        os.replace(tmp, target_path)
    except BaseException:
        if os.path.exists(tmp):
            os.unlink(tmp)
        raise


_PROPS_LINE_WIDTH = 100


def _format_scalar(value: Any) -> str:
    """One scalar as it appears in a .properties file (re-parses to an equal value)."""
    if value is None:
        return ""
    if isinstance(value, bool):
        return "true" if value else "false"
    return str(value)


def _format_property_line(key: str, value: Any) -> List[str]:
    """Lines of one ``key: value`` entry; long lists use backslash continuation lines."""
    if not isinstance(value, list):
        text = _format_scalar(value)
        if text[:1].isspace() and len(text) - len(text.lstrip()) == 1:
            # A value written as "key: \" + continuation line reads back with one
            # leading space, which templates rely on (contains(ecu:get(..), 'X ')).
            # A plain "key: value" line would lose it.
            return [f"{key}: \\", " " * (len(key) + 2) + text.lstrip()]
        return [f"{key}: {text}" if text else f"{key}:"]

    if not value:
        return [f"{key}: ,"]           # parses back to an empty list
    items = [_format_scalar(v) for v in value]
    if len(items) == 1:
        return [f"{key}: {items[0]},"]  # trailing comma keeps it a one-element list

    prefix = f"{key}: "
    indent = " " * len(prefix)
    lines: List[str] = []
    current = prefix
    first_on_line = True
    for i, item in enumerate(items):
        piece = item + (", " if i < len(items) - 1 else "")
        if not first_on_line and len(current) + len(piece) > _PROPS_LINE_WIDTH:
            lines.append(current.rstrip() + " \\")
            current = indent
            first_on_line = True
        current += piece
        first_on_line = False
    lines.append(current.rstrip())
    return lines


class ChipDefinitionExporter:
    """Exporter for ChipDefinition to YAML and EB Tresos .properties"""

    def to_yaml_dict(self, chip: ChipDefinition) -> Dict[str, Any]:
        """Convert ChipDefinition to dictionary conforming to data/chips/*.yaml schema.

        Must stay lossless w.r.t. ChipDatabase._load_chip_from_yaml.
        """
        data: Dict[str, Any] = {
            'name': chip.name,
            'family': chip.family,
            'package': chip.package,
            'description': chip.description,
        }

        if chip.ports:
            ports_dict = {}
            for port_name in sorted(chip.ports.keys()):
                pins_data = []
                for p in sorted(chip.ports[port_name], key=lambda x: x.pin):
                    p_entry = _FlowMap(
                        pin=p.pin,
                        name=p.name,
                        alternate_functions=list(p.alternate_functions),
                    )
                    if p.default_direction and p.default_direction != "INPUT":
                        p_entry['default_direction'] = p.default_direction
                    if p.alt_modes:
                        p_entry['modes'] = {k: p.alt_modes[k] for k in sorted(p.alt_modes)}
                    pins_data.append(p_entry)
                ports_dict[port_name] = pins_data
            data['ports'] = ports_dict

        if chip.can_resources:
            data['can_resources'] = [
                {
                    'name': c.name,
                    'controller_id': c.controller_id,
                    'max_baudrate': c.max_baudrate,
                    'supports_fd': c.supports_fd,
                    'mailbox_count': c.mailbox_count
                }
                for c in sorted(chip.can_resources, key=lambda x: x.controller_id)
            ]

        if chip.adc_resources:
            data['adc_resources'] = [
                {
                    'name': a.name,
                    'unit_id': a.unit_id,
                    'channel_count': a.channel_count,
                    'resolution_bits': a.resolution_bits,
                    'channels': list(a.channels)
                }
                for a in sorted(chip.adc_resources, key=lambda x: x.unit_id)
            ]

        if chip.spi_resources:
            data['spi_resources'] = [
                {
                    'name': s.name,
                    'unit_id': s.unit_id,
                    'max_baudrate': s.max_baudrate,
                    'supports_dma': s.supports_dma
                }
                for s in sorted(chip.spi_resources, key=lambda x: x.unit_id)
            ]

        if chip.intc_sources:
            data['intc_sources'] = [
                {
                    'name': i.name,
                    'vector_number': i.vector_number,
                    'priority_bits': i.priority_bits,
                    'is_configurable': i.is_configurable
                }
                for i in sorted(chip.intc_sources, key=lambda x: x.vector_number)
            ]

        if chip.metadata:
            data['metadata'] = dict(chip.metadata)

        if chip.resource_version:
            data['resource_version'] = chip.resource_version

        if chip.ecu_resources:
            ecu: Dict[str, Any] = {}
            for module, entries in chip.ecu_resources.items():
                params: Dict[str, Any] = {}
                for name, value in entries.items():
                    out = serialize_value(value)
                    params[name] = _BlockMap(out) if isinstance(out, dict) else out
                ecu[module] = params
            data['ecu_resources'] = ecu

        return data

    def to_yaml_string(self, chip: ChipDefinition) -> str:
        """Convert ChipDefinition to YAML text (properly quoted/escaped by PyYAML)"""
        return yaml.dump(
            self.to_yaml_dict(chip),
            Dumper=_ChipYamlDumper,
            sort_keys=False,
            allow_unicode=True,
            default_flow_style=None,
            width=4096,
        )

    def save_yaml(self, chip: ChipDefinition, target_path: Path):
        """Save ChipDefinition to YAML file"""
        _atomic_write_text(Path(target_path), self.to_yaml_string(chip))

    def module_properties_strings(self, chip: ChipDefinition) -> Dict[str, str]:
        """One .properties text per module, taken only from ``chip.ecu_resources``.

        Modules and keys keep the order of the YAML; nothing is added or defaulted.
        The result maps ``<Module>_<chip>.properties`` to the file content.
        """
        files: Dict[str, str] = {}
        for module, entries in chip.ecu_resources.items():
            lines = [
                "#####################################################################################################",
                f"# Generated from chip definition {chip.name}"
                + (f" (resource_version {chip.resource_version})" if chip.resource_version else ""),
                "# Do not edit: the chip YAML is the source of this file.",
                "#####################################################################################################",
            ]
            for name, value in entries.items():
                lines.extend(_format_property_line(f"{module}.{name}", value))
            files[f"{module}_{chip.name}.properties"] = "\n".join(lines) + "\n"
        return files

    def save_module_properties(self, chip: ChipDefinition, target_dir: Path) -> List[Path]:
        """Write one .properties file per module into ``target_dir``; returns the paths."""
        target_dir = Path(target_dir)
        target_dir.mkdir(parents=True, exist_ok=True)
        written: List[Path] = []
        for file_name, content in self.module_properties_strings(chip).items():
            path = target_dir / file_name
            _atomic_write_text(path, content)
            written.append(path)
        return written

    def to_properties_string(
        self,
        chip: ChipDefinition,
        num_cores: int = 2,
        available_cores: Optional[List[str]] = None,
        master_core: str = "CORE0"
    ) -> str:
        """Convert ChipDefinition to EB Tresos compatible .properties resource file

        When the chip has ``ecu_resources`` the text is built from them only (all
        modules one after another, for preview); otherwise the legacy output.
        """
        if chip.ecu_resources:
            return "\n".join(
                f"# ---- {file_name} ----\n{content}"
                for file_name, content in self.module_properties_strings(chip).items()
            )
        if available_cores is None:
            available_cores = [f"CORE{i}" for i in range(num_cores)]

        lines = [
            "#####################################################################################################",
            f"#   FileName             : CotexR52_{chip.name}.properties",
            "#   Platform             : AUTOSAR",
            f"#   brief                : Hardware resource definitions for {chip.name} ({chip.package})",
            "#   Autosar Version      : 4.4.0",
            f"#   Build Version        : {chip.family}",
            "#####################################################################################################",
            "",
            "#####################################################################################################",
            "##                                          Resource module                                        ##",
            "#####################################################################################################",
            f"Resource.NumOfCores: {num_cores}",
            f"Resource.AvailableCores: {', '.join(available_cores)}",
            f"Resource.Cluster.TotalNum: {num_cores}",
            f"Resource.Clsuter.C0.Cores: {', '.join(available_cores)}",
            f"Resource.MasterCore: {master_core}",
            f"Resource.SupportProcessor: {chip.name}",
            "",
            "#####################################################################################################",
            "##                                            Port module                                          ##",
            "#####################################################################################################",
        ]

        # Calculate max port and pin counts
        max_pin_id = 15
        max_mode_count = 8
        all_pins = chip.get_all_pins()
        if all_pins:
            max_pin_id = max(p.pin for p in all_pins)
            max_mode_count = max(len(p.alternate_functions) for p in all_pins)

        lines.extend([
            f"Port.MaxAvailablePortID: {len(chip.ports)}",
            f"Port.MaxAvailablePinID: {max_pin_id}",
            f"Port.MaxPortPinModeNumber: {max_mode_count}",
            ""
        ])

        # CAN
        lines.extend([
            "#####################################################################################################",
            "##                                            Can module                                           ##",
            "#####################################################################################################",
            f"Can.MaxModules: {len(chip.can_resources)}",
            f"Can.MaxNodes: {len(chip.can_resources)}",
            "Can.MaxHwObjects: 512",
            ""
        ])

        # ADC
        adc_units = [a.name for a in chip.adc_resources] if chip.adc_resources else ["SARADC0", "SARADC1"]
        lines.extend([
            "#####################################################################################################",
            "##                                            Adc module                                           ##",
            "#####################################################################################################",
            f"Adc.MaxControllers: {len(adc_units)}",
            f"Adc.HwUnitId: {', '.join(adc_units)}",
            f"Adc.MaxResolution: {max((a.resolution_bits for a in chip.adc_resources), default=12)}",
            ""
        ])

        # SPI
        lines.extend([
            "#####################################################################################################",
            "##                                            Spi module                                           ##",
            "#####################################################################################################",
            f"Spi.MaxHwUnit: {len(chip.spi_resources) if chip.spi_resources else 6}",
            ""
        ])

        return "\n".join(lines)

    def save_properties(
        self,
        chip: ChipDefinition,
        target_path: Path,
        num_cores: int = 2,
        available_cores: Optional[List[str]] = None,
        master_core: str = "CORE0"
    ):
        """Save ChipDefinition to EB Tresos .properties file

        When the chip has ``ecu_resources``, one file per module is written next
        to ``target_path`` instead (see save_module_properties).
        """
        if chip.ecu_resources:
            self.save_module_properties(chip, Path(target_path).parent)
            return
        content = self.to_properties_string(chip, num_cores, available_cores, master_core)
        _atomic_write_text(Path(target_path), content)
