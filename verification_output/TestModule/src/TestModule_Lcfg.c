/**
 * @file TestModule_Lcfg.c
 * @brief Link-Time Configuration for TestModule module
 */

#include "TestModule_Cfg.h"
#include "TestModule_MemMap.h"

#define TESTMODULE_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "TestModule_MemMap.h"

/* Link-Time Parameters Configuration */
CONST(TestModule_ConfigType, TESTMODULE_CONST) TestModule_Config = {

};

#define TESTMODULE_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "TestModule_MemMap.h"
