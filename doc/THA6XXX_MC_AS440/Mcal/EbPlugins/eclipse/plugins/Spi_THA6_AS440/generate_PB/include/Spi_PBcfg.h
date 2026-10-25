/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Spi_PBcfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Espi
*
*   brief                 : This file contains all configurations of SPI module
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

#ifndef SPI_PBCFG_H_
#define SPI_PBCFG_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Spi_GeneralTypes.h"

/***************************************************************************************************
*                            Definitions and Macros
****************************************************************************************************/
[!INDENT "0"!][!//
[!VAR "AllVariantNumber" = "variant:size()"!][!//
[!IF "num:i($AllVariantNumber) != num:i(0)"!][!//
    [!FOR "VariantIdx" = "num:i(1)" TO "num:i($AllVariantNumber)"!][!//
        [!VAR "VariantName" = "variant:all()[num:i($VariantIdx)]"!][!//
        /* Extern declaration of Spi configuration parameters entry for [!"$VariantName"!] */
        extern const Spi_ConfigType Spi_ConfigSet_[!"$VariantName"!][SPI_CONFIG_COUNT];
    [!ENDFOR!][!//
[!ELSE!][!//
    /* Extern declaration of Spi configuration parameters entry */
    extern const Spi_ConfigType Spi_ConfigSet[SPI_CONFIG_COUNT];
[!ENDIF!][!//
[!ENDINDENT!][!//

#endif /* SPI_PBCFG_H */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
