/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:  pmu_register.h
 * Author:    00412
 * Version:   V1.2.0
 * Date:      2026/02/28
 * Description: This file contains all definitions of Cache module registers
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #pmu_register_h_REF_1:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*/

#ifndef PMU_REGISTER_H_
#define PMU_REGISTER_H_
/**********************************************************************************************************************
 *                                                Includes
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/*PMCR Register*/
#define PMCR_ENABLE_POS 0U                       /* PMU MCR: ENABLE Position */
#define PMCR_ENABLE_MASK (1UL << PMCR_ENABLE_POS) /* PMU MCR: ENABLE Mask */

#define PMCR_EVT_COUN_RST_POS 1U                             /* PMU MCR:Event counter reset position */
#define PMCR_EVT_COUN_RST_MASK (1UL << PMCR_EVT_COUN_RST_POS) /* PMU MCR: Event counter reset Mask */

#define PMCR_CLK_COUN_RST_POS 2U                             /* PMU MCR:Clock counter reset position */
#define PMCR_CLK_COUN_RST_MASK (1UL << PMCR_CLK_COUN_RST_POS) /* PMU MCR: Clock counter reset Mask */

#define PMCR_CLK_DIV_POS 3U                        /* PMU MCR:Clock divider Position */
#define PMCR_CLK_DIV_MASK (1UL << PMCR_CLK_DIV_POS) /* PMU MCR: Clock divider  Mask */

#define PMCR_LONG_COUNTER_EN_POS 6U                                /* PMU MCR:Long cycle count enable position*/
#define PMCR_LONG_COUNTER_EN_MASK (1UL << PMCR_LONG_COUNTER_EN_POS) /* PMU MCR: Clock divider  Mask */

/* Violation: pmu_register_h_REF_1 */
#define PMCR_EV_CN_NUM_POS 11U                            /* PMU MCR:Number of event counters */
/* Violation: pmu_register_h_REF_1 */
#define PMCR_EV_CN_NUM_MASK (0x1FUL << PMCR_EV_CN_NUM_POS) /* PMU MCR: Number of event counters */

/* Violation: pmu_register_h_REF_1 */
#define Long cycle count enable

/*PMSELR */
/* Violation: pmu_register_h_REF_1 */
#define PMSELR_SEL_POS 0U                         /* PMU MCR:Number of event counters */
/* Violation: pmu_register_h_REF_1 */
#define PMSELR_SEL_MASK (0x3FUL << PMSELR_SEL_POS) /* PMU MCR: Number of event counters */

/*PMUSERENR Register*/
/* Violation: pmu_register_h_REF_1 */
#define PMUSERENR_EN_POS 0U                        /* Traps EL0 accesses to the Performance Monitors registers */
/* Violation: pmu_register_h_REF_1 */
#define PMUSERENR_EN_MASK (1UL << PMUSERENR_EN_POS) /* Traps EL0 accesses to the Performance MonitorsMask */

/* Violation: pmu_register_h_REF_1 */
#define PMUSERENR_SW_POS 1U                        /* Software increment write trap control */
/* Violation: pmu_register_h_REF_1 */
#define PMUSERENR_SW_MASK (1UL << PMUSERENR_SW_POS) /* Software increment write trap control Mask */

/* Violation: pmu_register_h_REF_1 */
#define PMUSERENR_CR_POS 2U                        /* Cycle counter read trap control */
/* Violation: pmu_register_h_REF_1 */
#define PMUSERENR_CR_MASK (1UL << PMUSERENR_CR_POS) /* Cycle counter read trap control Mask */

/* Violation: pmu_register_h_REF_1 */
#define PMUSERENR_ER_POS 3U                        /* Event counter read trap control */
/* Violation: pmu_register_h_REF_1 */
#define PMUSERENR_ER_MASK (1UL << PMUSERENR_ER_POS) /* Event counter read trap control Mask */

#define PMUSERENR_ALL_MASK 0x0000000FUL

/*PMCNTENSET*/
#define PMCNTENSET_C_POS 31U                       /* Enables the cycle counter register*/
#define PMCNTENSET_C_MASK (1UL << PMCNTENSET_C_POS) /* Enables the cycle counter Mask */

/*PMCNTENCLR*/
#define PMCNTENCLR_C_POS 31U                       /* Disables the cycle counter register */
#define PMCNTENCLR_C_MASK (1UL << PMCNTENCLR_C_POS) /* Disables the cycle counter Mask */

/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                              Global Union Definitions
 **********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Function Definitions
 *********************************************************************************************************************/

#endif /* PMU_REGISTER_H_ */

/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
