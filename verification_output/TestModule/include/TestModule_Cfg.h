/**
 * @file TestModule_Cfg.h
 * @brief Pre-Compile Configuration for TestModule module
 * @note Auto-generated - PRE-COMPILE parameters only
 */

#ifndef TESTMODULE_CFG_H
#define TESTMODULE_CFG_H

#include "Std_Types.h"

/* --- Pre-Compile Parameters --- */
{% for path_name_value in precompile_params %}
#define { module_name.upper() }_{ path_name_value.1.upper() }    ({ path_name_value.2 })
{% endfor %}

/* --- Pre-Compile References --- */
{% for path_name_target in references %}
/* Reference from { path_name_target.0 } to { path_name_target.2 } */
#define { module_name.upper() }_{ path_name_target.1.upper() }_REF    { resolve_ref(path_name_target.2) }
{% endfor %}

#endif /* TESTMODULE_CFG_H */
