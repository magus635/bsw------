"""Where the tests find the Os ARTI templates.

The templates are not kept in this repository. Their master copy is the THA6 Os plugin
(Os_THA6_ASR21/generate_PB, under SVN); a project such as t1 has the same layout in templates/Os.
OS_TEMPLATE_DIR selects such a directory; by default the plugin's generate_PB is used. When none
is found, the tests that render the templates are skipped.
"""
import os
import shutil
from pathlib import Path

import pytest

DEFAULT = Path("D:/19_AutosarOS/02_THA6204/02_Software/02_ConfiguratorPlugins/01_Trunk/eclipse/plugins/"
               "Os_THA6_ASR21/generate_PB")

# template file -> path relative to the template root (generate_PB or <project>/templates/Os)
LAYOUT = {
    "Os_ArtiEvents.m": "Os_ArtiEvents.m",
    "Os_AppCommon.m": "Os_AppCommon.m",
    "Os_Arti.arxml": "Os/Os_Arti.arxml",
    "Os_ArtiCfg.h": "Os/kernel/Os_ArtiCfg.h",
    "Os_ArtiHooks.h": "Os/kernel/Os_ArtiHooks.h",
    "Os_Arti_Mock.h": "Os/kernel/Os_Arti_Mock.h",
    "Os_Arti_Mock.c": "Os/kernel/Os_Arti_Mock.c",
}


def template_root():
    root = Path(os.environ.get("OS_TEMPLATE_DIR", DEFAULT))
    return root if (root / LAYOUT["Os_Arti.arxml"]).is_file() else None


ROOT = template_root()
requires_templates = pytest.mark.skipif(
    ROOT is None, reason="Os templates not found: set OS_TEMPLATE_DIR to the plugin's generate_PB or <project>/templates/Os")


def template(name):
    """Path of one template file (skips the test when the templates are not available)"""
    if ROOT is None:
        pytest.skip("Os templates not found (OS_TEMPLATE_DIR)")
    return ROOT / LAYOUT[name]


def copy_templates(dest, *names):
    """Copy templates flat into dest (the generator's module template directory)"""
    for name in names:
        shutil.copy(template(name), Path(dest) / name)
