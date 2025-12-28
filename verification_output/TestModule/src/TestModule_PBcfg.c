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

};

#define TESTMODULE_STOP_SEC_CONFIG_DATA_POSTBUILD
#include "TestModule_MemMap.h"
