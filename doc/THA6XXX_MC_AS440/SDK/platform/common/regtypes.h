/**************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName: regtypes.h
 * Author:    30032
 * Version:   V1.2.0
 * Date:      2026/02/28
 * Description: This file defines register data types.
 ************************************************************************************************/
/*
* #Violation Summary
*
* #regtypes_h_REF_1:MISRAC2012-Rule-2.3;
* Justification:The typedef are reserved for upper layers.
*/

#ifndef REGYPES_H_
#define REGYPES_H_

/* redefine register type */
/* #Violation: regtypes_h_REF_1 */
typedef unsigned char ureg8;
/* #Violation: regtypes_h_REF_1 */
typedef unsigned short ureg16;
typedef unsigned int ureg32;
/* #Violation: regtypes_h_REF_1 */
typedef unsigned long long ureg64;
/* #Violation: regtypes_h_REF_1 */
typedef signed char sreg8;
/* #Violation: regtypes_h_REF_1 */
typedef signed short sreg16;
/* #Violation: regtypes_h_REF_1 */
typedef signed int sreg32;
/* #Violation: regtypes_h_REF_1 */
typedef signed long long sreg64;
/* #Violation: regtypes_h_REF_1 */
typedef float freg32;
#endif /* REGYPES_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
