"""Every configuration template agrees with the vendor definition of its module."""
from pathlib import Path

import pytest

from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.core.template_manager import TemplateManager

PLUGINS = Path(__file__).resolve().parent.parent.parent / "test_import_project/Def/plugins"
TEMPLATES = TemplateManager().list_templates()
_defs = {}


def _module(name):
    if name not in _defs:
        xdm = PLUGINS / f"{name}_THA6_AS440/config/{name}.xdm"
        _defs[name] = EcucDefParser().parse_module_def_file(xdm)
    return _defs[name]


def _container(template):
    node = None
    for index, part in enumerate(template.container_def.split("/")):
        node = (_module(template.module).containers if index == 0 else node.sub_containers).get(part)
        if node is None:
            return None
    return node


def _problems(template):
    container = _container(template)
    if container is None:
        return [f"container {template.container_def} not in the definition"]
    problems = []
    values = {p.name: set(p.options or []) | ({p.default_value} if isinstance(p.default_value, str) else set())
              for p in template.adjustable_params}
    values.update({name: {value} for name, value in template.fixed_params.items() if isinstance(value, str)})
    for name in [p.name for p in template.adjustable_params] + list(template.fixed_params):
        definition = container.parameters.get(name)
        if definition is None:
            problems.append(f"{name}: not a parameter of {template.container_def}")
        elif definition.literals and values.get(name, set()) - set(definition.literals):
            problems.append(f"{name}: {sorted(values[name] - set(definition.literals))} "
                            f"not among {definition.literals}")
    return problems


def test_templates_were_found():
    assert len(TEMPLATES) >= 9


@pytest.mark.parametrize("template", TEMPLATES, ids=lambda t: t.name)
def test_template_agrees_with_the_vendor_definition(template):
    assert _problems(template) == []
