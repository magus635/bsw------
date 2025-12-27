/**
 * @file Crypto_PBcfg.c
 * @brief Post-Build Configuration for Crypto module
 */

#include "Crypto_Cfg.h"
#include "Crypto_MemMap.h"

#define CRYPTO_START_SEC_CONFIG_DATA_POSTBUILD
#include "Crypto_MemMap.h"

/* Post-Build Parameters Configuration */
CONST(Crypto_ConfigType, CRYPTO_CONST) Crypto_PBConfig = {
{% for path_name_value in postbuild_params %}
    ./* { path_name_value.0 } */{ path_name_value.1 } = { path_name_value.2 },
{% endfor %}
};

#define CRYPTO_STOP_SEC_CONFIG_DATA_POSTBUILD
#include "Crypto_MemMap.h"
