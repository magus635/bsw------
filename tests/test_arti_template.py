import pathlib
import pytest
from jinja2 import Environment, FileSystemLoader

TEMPLATE_DIR = pathlib.Path(r"D:\davinci\mcuapp\Components\Arti\newTemplate")


@pytest.fixture
def arti_env():
    return Environment(
        loader=FileSystemLoader(str(TEMPLATE_DIR)),
        trim_blocks=True,
        lstrip_blocks=True,
    )


def test_arti_cfg_h_template_defaults(arti_env):
    tpl = arti_env.get_template("Arti_Cfg.h.tpl")
    rendered = tpl.render(general={})
    assert "#define ARTI_CFG_MAJOR_VERSION          (1u)" in rendered
    assert "#define ARTI_CFG_MINOR_VERSION          (2u)" in rendered
    assert "#define ARTI_DEV_ERROR_DETECT           (STD_ON)" in rendered
    assert "#define ARTI_VERSION_INFO_API           (STD_OFF)" in rendered


def test_arti_cfg_h_template_custom_params(arti_env):
    tpl = arti_env.get_template("Arti_Cfg.h.tpl")
    rendered = tpl.render(
        general={
            "dev_error_detect": "STD_OFF",
            "dev_error_report": "STD_OFF",
            "version_info_api": "STD_ON",
        },
        precompile_params=[{"name": "max_hooks", "value": "16u"}],
    )
    assert "#define ARTI_DEV_ERROR_DETECT           (STD_OFF)" in rendered
    assert "#define ARTI_VERSION_INFO_API           (STD_ON)" in rendered
    assert "#define ARTI_MAX_HOOKS    (16u)" in rendered


def test_arti_lcfg_h_template(arti_env):
    tpl = arti_env.get_template("Arti_Lcfg.h.tpl")
    rendered = tpl.render(
        hooks=[{"name": "ARTI_HOOK_OS_TASK_START", "params": "taskId", "body": "Arti_TraceTask(taskId)"}],
        trace_variables=[
            {"macro_name": "ARTI_TRACE_VAR_CPU", "is_indexed": False, "target_var": "Arti_CpuLoad"},
            {"macro_name": "ARTI_TRACE_VAR_CORE", "is_indexed": True, "target_array": "Arti_CoreState"},
        ],
        vfb_trace_hooks=[
            {"rte_hook_name": "Rte_Runnable_Init_Start", "params": "", "arti_hook_call": "ARTI_HOOK_RUNNABLE_START()"}
        ],
    )
    assert "# define ARTI_HOOK_OS_TASK_START(taskId)    Arti_TraceTask(taskId)" in rendered
    assert "# define ARTI_TRACE_VAR_CPU(val)           (Arti_CpuLoad = (val))" in rendered
    assert "# define ARTI_TRACE_VAR_CORE(index, val)    (Arti_CoreState[(index)] = (val))" in rendered
    assert "# define Rte_Runnable_Init_Start()    ARTI_HOOK_RUNNABLE_START()" in rendered

