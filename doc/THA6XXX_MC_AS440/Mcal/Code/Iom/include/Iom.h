/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Iom.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : IOM
*
*   brief                 : This file contains all function declarations of IOM module
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Codeing Rule Violations                                                **
****************************************************************************************************/
/*
*#Violation Summary
*#Iom_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*#Iom_h_REF_2:MISRAC2012-Rule-20.7; 
* Justification: Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*
*/

#ifndef IOM_H_
#define IOM_H_

/***************************************************************************************************
*                               Include
***************************************************************************************************/
#include "Iom_GeneralTypes.h"
#include "Iom_Cfg.h"
#include "Iom_PBcfg.h"
#include "Mcall.h"
#include "Iom_Version.h"
#include "Det.h"

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

#define IOM_E_INIT                          (0x00U)
#define IOM_E_UNINIT                        (0x01U)
#define IOM_E_PARAM_INVALID                 (0x02U)
#define IOM_E_PARAM_PPUNO                   (0x03U)
#define IOM_E_PARAM_LPUNO                   (0x04U)
#define IOM_E_PARAM_THRESHOLD               (0x05U)
#define IOM_E_REGISTER_WRITTEN_FALSE        (0x06U)
#define IOM_E_PARAM_PPUFILTER_MODE          (0x07U)
#define IOM_E_CORE_NOT_CONFIGURED           (0x08U)
#define IOM_E_WRITE_REGISTER                (0x09U)
#define IOM_E_PARAM_PPUPRESCALER_MODE       (0x0AU)

/* Service ID for IOM */
#define IOM_SID_INIT                        (0x00U)
#define IOM_SID_GETGLITCH                   (0x01U)
#define IOM_SID_SETPPUPRECALER              (0x02U)
#define IOM_SID_GETPPUPRECALER              (0x03U)
#define IOM_SID_SETPPUFILTERTIME            (0x04U)
#define IOM_SID_GETPPUFILTERTIME            (0x05U)
#define IOM_SID_SETLPUEVENTWINTHRESHOLD     (0x06U)
#define IOM_SID_GETLPUEVENTWINTHRESHOLD     (0x07U)
#define IOM_SID_GETLPUHISTORY               (0x08U)
#define IOM_SID_CLRLPUHISTORY               (0x09U)
#define IOM_SID_ENABLEEMUCOUNTER            (0x10U)
#define IOM_SID_DISBLEEMUCOUNTER            (0x11U)
#define IOM_SID_GETVERINFO                  (0x12U)

/* Maximum PPU channel   */
#define IOM_PPU_CHANNEL_MAX                 (0x0FU)
/* Maximum LPU channel   */
#define IOM_LPU_CHANNEL_MAX                 (0x0FU)
/* Ppu channel mask */
#define IOM_PPU_CHANNEL_MASK                (0x00FFU)
/* Maximum event window count threshold value MASK */
#define IOM_LPU_THRES_MAX                   (0x00FFFFFFU)
/* Maximum filter or precaler count threshold value */
#define IOM_PPU_THRES_MAX                   (0x0000FFFFU)
/* An error occurred with the returned threshold */
#define IOM_THRESHOLD_FALSE                 (0U)
/* EMU configuration max index */
#define IOM_EMUCONFIG_MAX_INDEX             (0xFFU)


/* #Violation: Iom_h_REF_1*/
#define Input_IOM_MONINPUT_P33_0            (IOM_MONINPUT_P33_0)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_MONINPUT_P33_1            (IOM_MONINPUT_P33_1)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_MONINPUT_P33_2            (IOM_MONINPUT_P33_2)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_MONINPUT_P33_3            (IOM_MONINPUT_P33_3)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_MONINPUT_P33_4            (IOM_MONINPUT_P33_4)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_MONINPUT_P33_5            (IOM_MONINPUT_P33_5)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_MONINPUT_P33_6            (IOM_MONINPUT_P33_6)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_MONINPUT_P33_7            (IOM_MONINPUT_P33_7)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_MONINPUT_P33_8            (IOM_MONINPUT_P33_8)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_MONINPUT_P33_9            (IOM_MONINPUT_P33_9)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_MONINPUT_P33_10           (IOM_MONINPUT_P33_10)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_MONINPUT_P33_11           (IOM_MONINPUT_P33_11)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_MONINPUT_P33_12           (IOM_MONINPUT_P33_12)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_MONINPUT_P20_12           (IOM_MONINPUT_P20_12)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_MONINPUT_P20_13           (IOM_MONINPUT_P20_13)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_MONINPUT_P20_14           (IOM_MONINPUT_P20_14)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_MONINPUT_GTMTOUT22     (IOM_MONINPUT_GTMTOUT22)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_MONINPUT_GTMTOUT23     (IOM_MONINPUT_GTMTOUT23)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_MONINPUT_GTMTOUT24     (IOM_MONINPUT_GTMTOUT24)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_MONINPUT_GTMTOUT25     (IOM_MONINPUT_GTMTOUT25)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_MONINPUT_GTMTOUT26     (IOM_MONINPUT_GTMTOUT26)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_MONINPUT_GTMTOUT27     (IOM_MONINPUT_GTMTOUT27)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_MONINPUT_GTMTOUT28     (IOM_MONINPUT_GTMTOUT28)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_MONINPUT_GTMTOUT29     (IOM_MONINPUT_GTMTOUT29)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_MONINPUT_GTMTOUT30     (IOM_MONINPUT_GTMTOUT30)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_MONINPUT_GTMTOUT31     (IOM_MONINPUT_GTMTOUT31)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_MONINPUT_GTMTOUT32     (IOM_MONINPUT_GTMTOUT32)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_MONINPUT_GTMTOUT33     (IOM_MONINPUT_GTMTOUT33)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_MONINPUT_GTMTOUT34     (IOM_MONINPUT_GTMTOUT34)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_MONINPUT_GTMTOUT68     (IOM_MONINPUT_GTMTOUT68)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_MONINPUT_GTMTOUT69     (IOM_MONINPUT_GTMTOUT69)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_MONINPUT_GTMTOUT70     (IOM_MONINPUT_GTMTOUT70)
#if defined(THA6_THA6104)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO1G0OUT0      (IOM_MONINPUT_GTMTIO1G0OUT0 )
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO1G0OUTN0     (IOM_MONINPUT_GTMTIO1G0OUTN0)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO1G0OUT1      (IOM_MONINPUT_GTMTIO1G0OUT1 )
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO1G0OUTN1     (IOM_MONINPUT_GTMTIO1G0OUTN1)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO1G0OUT2      (IOM_MONINPUT_GTMTIO1G0OUT2 )
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO1G0OUTN2     (IOM_MONINPUT_GTMTIO1G0OUTN2)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO1G0OUT3      (IOM_MONINPUT_GTMTIO1G0OUT3 )
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO1G0OUTN3     (IOM_MONINPUT_GTMTIO1G0OUTN3)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO1G0OUT4      (IOM_MONINPUT_GTMTIO1G0OUT4 )
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO1G0OUTN4     (IOM_MONINPUT_GTMTIO1G0OUTN4)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO1G0OUT5      (IOM_MONINPUT_GTMTIO1G0OUT5 )
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO1G0OUTN5     (IOM_MONINPUT_GTMTIO1G0OUTN5)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO1G0OUT6      (IOM_MONINPUT_GTMTIO1G0OUT6 )
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO1G0OUTN6     (IOM_MONINPUT_GTMTIO1G0OUTN6)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO1G0OUT7      (IOM_MONINPUT_GTMTIO1G0OUT7 )
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO1G0OUTN7     (IOM_MONINPUT_GTMTIO1G0OUTN7)
#endif /* THA6_THA6104 */
#if defined(THA6_THA6412)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO3PWM06     (IOM_MONINPUT_GTMTIO3PWM06)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO2PWM05     (IOM_MONINPUT_GTMTIO2PWM05)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO1PWM04     (IOM_MONINPUT_GTMTIO1PWM04)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO1PWM00     (IOM_MONINPUT_GTMTIO1PWM00)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO2PWM01     (IOM_MONINPUT_GTMTIO2PWM01)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO3PWM02     (IOM_MONINPUT_GTMTIO3PWM02)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO4PWM03     (IOM_MONINPUT_GTMTIO4PWM03)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO4PWM13     (IOM_MONINPUT_GTMTIO4PWM13)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO1PWM14     (IOM_MONINPUT_GTMTIO1PWM14)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO2PWM15     (IOM_MONINPUT_GTMTIO2PWM15)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO3PWM16     (IOM_MONINPUT_GTMTIO3PWM16)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO1PWM10     (IOM_MONINPUT_GTMTIO1PWM10)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO2PWM11     (IOM_MONINPUT_GTMTIO2PWM11)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_GTMTIO3PWM12     (IOM_MONINPUT_GTMTIO3PWM12)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_PSI5TX0          (IOM_MONINPUT_PSI5TX0)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_MONINPUT_PSI5TX1          (IOM_MONINPUT_PSI5TX1)
#endif /* THA6_THA6412 */
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_MONINPUT_ESPI0MRST     (IOM_MONINPUT_ESPI0MRST)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_MONINPUT_ESPI1MRST     (IOM_MONINPUT_ESPI1MRST)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_MONINPUT_ESPI2MRST     (IOM_MONINPUT_ESPI2MRST)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_MONINPUT_ESPI3MRST     (IOM_MONINPUT_ESPI3MRST)
#if defined(THA6_THA6412)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_MONINPUT_ESPI4MRST     (IOM_MONINPUT_ESPI4MRST)
#endif /* THA6_THA6412 */
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_MONINPUT_CAN00TXD      (IOM_MONINPUT_CAN00TXD)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_MONINPUT_CAN01TXD      (IOM_MONINPUT_CAN01TXD)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_MONINPUT_CAN02TXD      (IOM_MONINPUT_CAN02TXD)
#if defined(THA6_THA6412)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_MONINPUT_CAN30TXD      (IOM_MONINPUT_CAN30TXD)
#endif /* THA6_THA6412 */
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_MONINPUT_GTMTOUT104    (IOM_MONINPUT_GTMTOUT104)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_MONINPUT_GTMTOUT105    (IOM_MONINPUT_GTMTOUT105)
#if defined(THA6_THA6104)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_MONINPUT_GTMTOUT106    (IOM_MONINPUT_GTMTOUT106)
#endif /* THA6_THA6104 */
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_MONINPUT_ASI0ATX    (IOM_MONINPUT_ASI0ATX)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_MONINPUT_ASI1ATX    (IOM_MONINPUT_ASI1ATX)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_MONINPUT_ASI2ATX    (IOM_MONINPUT_ASI2ATX)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_MONINPUT_ASI3ATX    (IOM_MONINPUT_ASI3ATX)

/* #Violation: Iom_h_REF_1*/
#define Input_IOM_REFINPUT_P33_0            (IOM_REFINPUT_P33_0)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_REFINPUT_P33_1            (IOM_REFINPUT_P33_1)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_REFINPUT_P33_2            (IOM_REFINPUT_P33_2)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_REFINPUT_P33_3            (IOM_REFINPUT_P33_3)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_REFINPUT_P33_4            (IOM_REFINPUT_P33_4)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_REFINPUT_P33_5            (IOM_REFINPUT_P33_5)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_REFINPUT_P33_6            (IOM_REFINPUT_P33_6)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_REFINPUT_P33_7            (IOM_REFINPUT_P33_7)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_REFINPUT_P33_8            (IOM_REFINPUT_P33_8)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_REFINPUT_P33_9            (IOM_REFINPUT_P33_9)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_REFINPUT_P33_10           (IOM_REFINPUT_P33_10)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_REFINPUT_P33_11           (IOM_REFINPUT_P33_11)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_REFINPUT_P33_12           (IOM_REFINPUT_P33_12)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_REFINPUT_P20_12           (IOM_REFINPUT_P20_12)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_REFINPUT_P20_13           (IOM_REFINPUT_P20_13)
/* #Violation: Iom_h_REF_1*/
#define Input_IOM_REFINPUT_P20_14           (IOM_REFINPUT_P20_14)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_REFINPUT_GTMTOUT0      (IOM_REFINPUT_GTMTOUT0)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_REFINPUT_GTMTOUT1      (IOM_REFINPUT_GTMTOUT1)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_REFINPUT_GTMTOUT2      (IOM_REFINPUT_GTMTOUT2)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_REFINPUT_GTMTOUT3      (IOM_REFINPUT_GTMTOUT3)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_REFINPUT_GTMTOUT4      (IOM_REFINPUT_GTMTOUT4)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_REFINPUT_GTMTOUT5      (IOM_REFINPUT_GTMTOUT5)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_REFINPUT_GTMTOUT6      (IOM_REFINPUT_GTMTOUT6)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_REFINPUT_GTMTOUT7      (IOM_REFINPUT_GTMTOUT7)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_REFINPUT_GTMTOUT8      (IOM_REFINPUT_GTMTOUT8)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_REFINPUT_GTMTOUT9      (IOM_REFINPUT_GTMTOUT9)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_REFINPUT_GTMTOUT10     (IOM_REFINPUT_GTMTOUT10)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_REFINPUT_GTMTOUT11     (IOM_REFINPUT_GTMTOUT11)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_REFINPUT_GTMTOUT12     (IOM_REFINPUT_GTMTOUT12)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_REFINPUT_GTMTOUT13     (IOM_REFINPUT_GTMTOUT13)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_REFINPUT_GTMTOUT14     (IOM_REFINPUT_GTMTOUT14)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL0_IOM_REFINPUT_GTMTOUT15     (IOM_REFINPUT_GTMTOUT15)

#if defined(THA6_THA6104)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO1G0OUT0      (IOM_REFINPUT_GTMTIO1G0OUT0 )
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO1G0OUTN0     (IOM_REFINPUT_GTMTIO1G0OUTN0)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO1G0OUT1      (IOM_REFINPUT_GTMTIO1G0OUT1 )
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO1G0OUTN1     (IOM_REFINPUT_GTMTIO1G0OUTN1)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO1G0OUT2      (IOM_REFINPUT_GTMTIO1G0OUT2 )
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO1G0OUTN2     (IOM_REFINPUT_GTMTIO1G0OUTN2)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO1G0OUT3      (IOM_REFINPUT_GTMTIO1G0OUT3 )
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO1G0OUTN3     (IOM_REFINPUT_GTMTIO1G0OUTN3)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO1G0OUT4      (IOM_REFINPUT_GTMTIO1G0OUT4 )
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO1G0OUTN4     (IOM_REFINPUT_GTMTIO1G0OUTN4)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO1G0OUT5      (IOM_REFINPUT_GTMTIO1G0OUT5 )
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO1G0OUTN5     (IOM_REFINPUT_GTMTIO1G0OUTN5)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO1G0OUT6      (IOM_REFINPUT_GTMTIO1G0OUT6 )
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO1G0OUTN6     (IOM_REFINPUT_GTMTIO1G0OUTN6)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO1G0OUT7      (IOM_REFINPUT_GTMTIO1G0OUT7 )
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO1G0OUTN7     (IOM_REFINPUT_GTMTIO1G0OUTN7)
#endif /* THA6_THA6104 */
#if defined(THA6_THA6412)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO4PWM03       (IOM_REFINPUT_GTMTIO4PWM03)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO3PWM02       (IOM_REFINPUT_GTMTIO3PWM02)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO2PWM01       (IOM_REFINPUT_GTMTIO2PWM01)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO1PWM00       (IOM_REFINPUT_GTMTIO1PWM00)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO3PWM06       (IOM_REFINPUT_GTMTIO3PWM06)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO2PWM05       (IOM_REFINPUT_GTMTIO2PWM05)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO1PWM04       (IOM_REFINPUT_GTMTIO1PWM04)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO4PWM13       (IOM_REFINPUT_GTMTIO4PWM13)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO3PWM12       (IOM_REFINPUT_GTMTIO3PWM12)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO2PWM11       (IOM_REFINPUT_GTMTIO2PWM11)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO1PWM10       (IOM_REFINPUT_GTMTIO1PWM10)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO3PWM16       (IOM_REFINPUT_GTMTIO3PWM16)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO2PWM15       (IOM_REFINPUT_GTMTIO2PWM15)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_GTMTIO1PWM14       (IOM_REFINPUT_GTMTIO1PWM14)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_PSI5TX0            (IOM_REFINPUT_PSI5TX0     )
/* #Violation: Iom_h_REF_1*/
#define CHANNEL1_IOM_REFINPUT_PSI5TX2            (IOM_REFINPUT_PSI5TX2     )
#endif /* THA6_THA6412 */

/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_REFINPUT_ESPI0MRST     (IOM_REFINPUT_ESPI0MRST)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_REFINPUT_ESPI1MRST     (IOM_REFINPUT_ESPI1MRST)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_REFINPUT_ESPI2MRST     (IOM_REFINPUT_ESPI2MRST)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_REFINPUT_ESPI3MRST     (IOM_REFINPUT_ESPI3MRST)
#if defined(THA6_THA6412)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_REFINPUT_ESPI4MRST     (IOM_REFINPUT_ESPI4MRST)
#endif /* THA6_THA6412 */
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_REFINPUT_CAN00TXD      (IOM_REFINPUT_CAN00TXD)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_REFINPUT_CAN01TXD      (IOM_REFINPUT_CAN01TXD)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_REFINPUT_CAN02TXD      (IOM_REFINPUT_CAN02TXD)
#if defined(THA6_THA6412)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_REFINPUT_CAN30TXD      (IOM_REFINPUT_CAN30TXD)
#endif /* THA6_THA6412 */
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_REFINPUT_GTMTOUT107    (IOM_REFINPUT_GTMTOUT107)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_REFINPUT_GTMTOUT108    (IOM_REFINPUT_GTMTOUT108)
#if defined(THA6_THA6104)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_REFINPUT_GTMTOUT109    (IOM_REFINPUT_GTMTOUT109)
#endif /* THA6_THA6104 */
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_REFINPUT_ASI0ATX    (IOM_REFINPUT_ASI0ATX)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_REFINPUT_ASI1ATX    (IOM_REFINPUT_ASI1ATX)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_REFINPUT_ASI2ATX    (IOM_REFINPUT_ASI2ATX)
/* #Violation: Iom_h_REF_1*/
#define CHANNEL2_IOM_REFINPUT_ASI3ATX    (IOM_REFINPUT_ASI3ATX)
/* #Violation: Iom_h_REF_1*/
#define IOM_REFINPUT_GTMEXORCOMBINER0       (IOM_REFINPUT_EXORCOMBINER0)
/* #Violation: Iom_h_REF_1*/
#define IOM_REFINPUT_GTMEXORCOMBINER1       (IOM_REFINPUT_EXORCOMBINER1)
/* #Violation: Iom_h_REF_1*/
#define IOM_REFINPUT_GTMEXORCOMBINER2       (IOM_REFINPUT_EXORCOMBINER2)
/* #Violation: Iom_h_REF_1*/
#define IOM_REFINPUT_GTMEXORCOMBINER3       (IOM_REFINPUT_EXORCOMBINER3)
/* #Violation: Iom_h_REF_1*/
#define IOM_REFINPUT_GTMEXORCOMBINER4       (IOM_REFINPUT_EXORCOMBINER4)
/* #Violation: Iom_h_REF_1*/
#define IOM_REFINPUT_GTMEXORCOMBINER5       (IOM_REFINPUT_EXORCOMBINER5)
/* #Violation: Iom_h_REF_1*/
#define IOM_REFINPUT_GTMEXORCOMBINER6       (IOM_REFINPUT_EXORCOMBINER6)
/* #Violation: Iom_h_REF_1*/
#define IOM_REFINPUT_GTMEXORCOMBINER7       (IOM_REFINPUT_EXORCOMBINER7)
/* #Violation: Iom_h_REF_1*/
#define IOM_REFINPUT_GTMEXORCOMBINER8       (IOM_REFINPUT_EXORCOMBINER8)
/* #Violation: Iom_h_REF_1*/
#define IOM_REFINPUT_GTMEXORCOMBINER9       (IOM_REFINPUT_EXORCOMBINER9)
/* #Violation: Iom_h_REF_1*/
#define IOM_REFINPUT_GTMEXORCOMBINER10      (IOM_REFINPUT_EXORCOMBINER10)
/* #Violation: Iom_h_REF_1*/
#define IOM_REFINPUT_GTMEXORCOMBINER11      (IOM_REFINPUT_EXORCOMBINER11)
/* #Violation: Iom_h_REF_1*/
#define IOM_REFINPUT_GTMEXORCOMBINER12      (IOM_REFINPUT_EXORCOMBINER12)
/* #Violation: Iom_h_REF_1*/
#define IOM_REFINPUT_GTMEXORCOMBINER13      (IOM_REFINPUT_EXORCOMBINER13)
/* #Violation: Iom_h_REF_1*/
#define IOM_REFINPUT_GTMEXORCOMBINER14      (IOM_REFINPUT_EXORCOMBINER14)
/* #Violation: Iom_h_REF_1*/
#define IOM_REFINPUT_GTMEXORCOMBINER15      (IOM_REFINPUT_EXORCOMBINER15)

#define BOTHEDGES_DD                        (IOM_PPUFILTERMODE_DELAYDEBOUNCEBOTHEDGE)
/* #Violation: Iom_h_REF_1*/
#define BOTHEDGES_ID                        (IOM_PPUFILTERMODE_IMMEDIATEDEBOUNCEBOTHEDGE)
/* #Violation: Iom_h_REF_1*/
#define RISINGEDGE_ID                       (IOM_PPUFILTERMODE_IMMEDIATEDEBOUNCERISINGEDGE)
/* #Violation: Iom_h_REF_1*/
#define FALLINGEDGE_ID                      (IOM_PPUFILTERMODE_IMMEDIATEDEBOUNCEFALLINGEDGE)
/* #Violation: Iom_h_REF_1*/
#define RISING_DD_FALLING_ID                (IOM_PPUFILTERMODE_DELAYDEBOUNCERISINGEDGEIMMEDIATEDEBOUNCEFALLINGEDGE)
/* #Violation: Iom_h_REF_1*/
#define RISING_ID_FALLING_DD                (IOM_PPUFILTERMODE_IMMEDIATEDEBOUNCERISINGEDGEDELAYDEBOUNCEFALLINGEDGE)
#if defined(THA6_THA6412) || defined(THA6_THA6104)
/* #Violation: Iom_h_REF_1*/
#define RISINGEDGE_PRESCALER                (IOM_PPUFILTERMODE_PRESCALERONRISINGEDGE)
/* #Violation: Iom_h_REF_1*/
#define FALLINGEDGE_PRESCALER               (IOM_PPUFILTERMODE_PRESCALERONFALLINGEDGE)
/* #Violation: Iom_h_REF_1*/
#define NO_FILTER                           (IOM_PPUFILTERMODE_NOFILTER)
#endif /* THA6_THA6412 */
/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
/* #Violation: Iom_h_REF_1*/
#define IOM_START_SEC_CODE_ASIL_D_GLOBAL
#include "Iom_MemMap.h"

extern FUNC(void, IOM_PUBLIC_CODE) Iom_Init
(
    P2CONST(Iom_ConfigType, AUTOMATIC, IOM_APPL_CONST) ConfigPtr
);

#if (STD_ON == IOM_VERSION_INFO_API)
extern FUNC(void, IOM_PUBLIC_CODE) Iom_GetVersionInfo
(
/* #Violation: Iom_h_REF_2*/
    CONSTP2VAR(Std_VersionInfoType, AUTOMATIC, IOM_APPL_DATA) VersionInfoPtr
);
#endif /* (IOM_VERSION_INFO_API  \== STD_ON) */

#if (STD_ON == IOM_GET_PPUGLITCH_API)
FUNC(Iom_PpuGlitchFlagType, IOM_PUBLIC_CODE) Iom_GetPpuGlitch
(
    Iom_PpuChannelType PpuChannelNumber
);
#endif /* (IOM_GET_PPUGLITCH_API  \== STD_ON) */

#if (STD_ON == IOM_PPU_PRESCALER_API)
FUNC(void, IOM_PUBLIC_CODE) Iom_SetPpuPrecalerThreshold
(
    Iom_PpuChannelType PpuChannelNumber,
    Iom_PpuPrescalerThresholdType Threshold
);

FUNC(Iom_PpuPrescalerThresholdType, IOM_PUBLIC_CODE) Iom_GetPpuPrecalerThreshold
(
    Iom_PpuChannelType PpuChannelNumber
);
#endif /* (IOM_PPU_PRESCALER_API  \== STD_ON) */

#if (STD_ON == IOM_PPU_FILTER_API)
FUNC(void, IOM_PUBLIC_CODE) Iom_SetPpuFilterTimeThreshold
(
    Iom_PpuChannelType PpuChannelNumber,
    Iom_PpuFilterTimeType FilterTime
);

FUNC(Iom_PpuFilterTimeType, IOM_PUBLIC_CODE) Iom_GetPpuFilterTimeThreshold
(
    Iom_PpuChannelType PpuChannelNumber
);
#endif /* (IOM_PPU_FILTER_API  \== STD_ON) */

FUNC(void, IOM_PUBLIC_CODE) Iom_SetLpuEventWindowTimeThreshold
(
    Iom_LpuChannelIdType LpuChannelNumber, 
    Iom_EventWinTimeThresType EventWindowTimeThreshold
);

FUNC(Iom_EventWinTimeThresType, IOM_PUBLIC_CODE) Iom_GetLpuEventWindowTimeThreshold
(
    Iom_LpuChannelIdType LpuChannelNumber
);

FUNC(Std_ReturnType, IOM_PUBLIC_CODE) Iom_GetLpuChannelTrigHistory
(
    Iom_LpuChannelIdType LpuChannelNumber
);

extern FUNC(void, IOM_PUBLIC_CODE) Iom_ClrEmuEventTriggerHistory
(
    void
);

extern FUNC(void, IOM_PUBLIC_CODE) Iom_EnableEmuCounter
(
    void
);

extern FUNC(void, IOM_PUBLIC_CODE) Iom_DisableEmuCounter
(
    void
);

/* #Violation: Iom_h_REF_1*/
#define IOM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Iom_MemMap.h"

#endif /* IOM_H_ */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
