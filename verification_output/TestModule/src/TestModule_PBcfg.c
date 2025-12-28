/**
 * @file TestModule_PBcfg.c
 * @brief Post-Build Configuration for TestModule module
 */

#include "TestModule_Cfg.h"
#include "TestModule_MemMap.h"

#define TESTMODULE_START_SEC_CONFIG_DATA_POSTBUILD
#include "TestModule_MemMap.h"

/* Post-Build Parameters Configuration */
CONST(TestModule_ConfigType, TESTMODULE_CONST) TestModule_PBConfig = {
{% for path_name_value in postbuild_params %}
    ./* { path_name_value.0 } */{ path_name_value.1 } = { path_name_value.2 },
{% endfor %}
};

#define TESTMODULE_STOP_SEC_CONFIG_DATA_POSTBUILD
#include "TestModule_MemMap.h"
