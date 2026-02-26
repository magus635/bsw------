/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : I2c_PBcfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : I2C
*
*   brief                 : This file contains all configurations of I2C module
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

#ifndef I2C_PBCFG_H_
#define I2C_PBCFG_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "I2c_GeneralTypes.h"

/***************************************************************************************************
*                            Definitions and Macros
****************************************************************************************************/
[!INDENT "0"!][!//
  [!VAR "AllVariantNumber" = "variant:size()"!][!//
  [!IF "num:i($AllVariantNumber) != num:i(0)"!][!//
      [!FOR "VariantIdx" = "num:i(1)" TO "num:i($AllVariantNumber)"!][!//
          [!VAR "VariantName" = "variant:all()[num:i($VariantIdx)]"!][!//
          /* Extern declaration of I2c configuration parameters entry for [!"$VariantName"!] */
          extern const I2c_ConfigType I2c_ConfigSet_[!"$VariantName"!][I2C_CONFIG_COUNT];
      [!ENDFOR!][!//
  [!ELSE!][!//
      /* Extern declaration of I2c configuration parameters entry */
      extern const I2c_ConfigType I2c_ConfigSet[I2C_CONFIG_COUNT];
  [!ENDIF!][!//
[!ENDINDENT!][!//

#endif /* I2C_PBCFG_H */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
