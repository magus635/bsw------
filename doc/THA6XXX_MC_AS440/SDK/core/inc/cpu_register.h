/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    cpu_register.h
 * Author:      01254
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all definitions of CPU module registers.
 *********************************************************************************************************************/
#ifndef CPU_REGISTER_H_
#define CPU_REGISTER_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/*CPUACTLR Register*/
#define CPUACTLR_DSPECDIS_POS 32U
#define CPUACTLR_DSPECDIS_MASK (1ULL << CPUACTLR_DSPECDIS_POS)
#define CPUACTLR_ISPECDIS_POS 33U
#define CPUACTLR_ISPECDIS_MASK (1ULL << CPUACTLR_ISPECDIS_POS)
#define CPUACTLR_L1DPFCTL_POS 13U
#define CPUACTLR_L1DPFCTL_MASK (7ULL << CPUACTLR_L1DPFCTL_POS)
#define CPUACTLR_L1IPFCTL_POS 11U
#define CPUACTLR_L1IPFCTL_MASK (1ULL << CPUACTLR_L1IPFCTL_POS)
/*IMP_BPCTLR Register*/
#define IMP_BPCTLR_DBPEL2DIS_POS 2U
#define IMP_BPCTLR_DBPEL1DIS_POS 1U
#define IMP_BPCTLR_DBPEL0DIS_POS 0U
#define IMP_BPCTLR_DBPEL2DIS_MASK (1UL << IMP_BPCTLR_DBPEL2DIS_POS)
#define IMP_BPCTLR_DBPEL1DIS_MASK (1UL << IMP_BPCTLR_DBPEL1DIS_POS)
#define IMP_BPCTLR_DBPEL0DIS_MASK (1UL << IMP_BPCTLR_DBPEL0DIS_POS)
/**********************************************************************************************************************
 *                                        CPU Register Bit-Fields Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                             CPU Register Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                        CPU Register Configuration Structure
 *********************************************************************************************************************/
#endif /* CPU_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
