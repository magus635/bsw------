/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    tha6_cfg.h
 * Author:      00930
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains THA6 chip configuration information.
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#tha6_cfg_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: Compiler macro is defined and used followed AUTOSAR standard rule.
*/
#ifndef THA6_CFG_H_
#define THA6_CFG_H_

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* THA6_Series_SDK_VERSION */
/* #Violation: tha6_cfg_h_REF_1 */
#define THA6_Series_SDK_VERSION_MAJOR        1   /**< \brief Informs about changes which could lead to incompatibilities */
/* #Violation: tha6_cfg_h_REF_1 */
#define THA6_Series_SDK_VERSION_MINOR        2   /**< \brief Informs about new additions to the library */
/* #Violation: tha6_cfg_h_REF_1 */
#define THA6_Series_SDK_VERSION_PATCH        0   /**< \brief Informs about patches and/or documentation changes */

/********************************************************************************************
 * THA6 series selection macro define description
 * 1. Define THA6_THA6104 to select THA6104
 * 2. Define THA6_THA6206 to select THA6206 Version C, define THA6_THA6206D to select THA6206 Version D
 * 3. Define THA6_THA6412 to select THA6412
 * Note: If user choose to define THA6_THA6412,
 *       user need to use the THA6412 linker file,
 *       such as tha6412.scat for ADS; similarly,
 *       if user choose to define THA6_THA6206 or THA6_THA6206D,
 *       the linker file should be switched to THA6206.
 *       If neither of the macros is explicitly defined,
 *       the project compilation will result in an error.
 * More usage information see Compile Macro Define Parameters chapter in release note.
 * *******************************************************************************************/
#if defined(THA6_THA6104)
#include "tha6104_cfg.h"
#endif /* THA6_THA6104 */

#if defined(THA6_THA6206) || defined(THA6_THA6206D)
#include "tha6206_cfg.h"
#endif /* THA6_THA6206 Ver. C&D */

#if defined(THA6_THA6412)
#include "tha6412_cfg.h"
#endif /* THA6_THA6412 */

#if !defined(THA6_THA6104) && !defined(THA6_THA6206) && !defined(THA6_THA6206D) && !defined(THA6_THA6412)
    #error "tha6_cfg.h, no valid chip type macro defined. Please define THA6_THA6104, THA6_THA6206, THA6_THA6206D or THA6_THA6412."
    #error "More information see release note(Compile Macro Define Parameters)."
#endif

#endif /* THA6_CFG_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
