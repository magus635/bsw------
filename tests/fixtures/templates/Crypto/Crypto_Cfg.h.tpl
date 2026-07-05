/**
 * @file Crypto_Cfg.h
 * @brief Configuration header for Crypto module
 */

#ifndef CRYPTO_CFG_H
#define CRYPTO_CFG_H

#include "Crypto_Types.h"

/*===========================================================================
 *                   CRYPTO PRE-COMPILE PARAMETERS
 *===========================================================================*/

{% for param in precompile_params %}
/* {{ param.path }} */
#define CRYPTO_{{ param.name.upper() }}  ({{ param.value }})
{% endfor %}

/*===========================================================================
 *                   CRYPTO SPECIFIC MACROS
 *===========================================================================*/

#define CRYPTO_NUM_KEYS  ({{ references|length }})

#endif /* CRYPTO_CFG_H */
