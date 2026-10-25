/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Adc_Demo.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : SARADC
*
*   brief                 : This file contains all function declarations of Adc Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

#ifndef ADC_DEMO_H_
#define ADC_DEMO_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"
#include "Adc.h"

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#define ADC_DMA_TRSNAFER_SW_TRIG_COUNT                    (5U)
#define ADC_DMA_TRANSFER_SW_TRIG_CHS                      (4U)

#define ADC_DMA_TRSNAFER_SW_TRIG_ONE_RES_REG_COUNT        (6U)  /* 1000ms */

/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/
#define ADC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Adc_MemMap.h"

#if (defined(MCAL_MODULE_CFG_DMA_USED) && (MCAL_MODULE_CFG_DMA_USED == STD_ON))
extern Adc_ValueGroupType Adc_DmaTransferSwTrigResult[ADC_DMA_TRANSFER_SW_TRIG_CHS *
                                                      ADC_DMA_TRSNAFER_SW_TRIG_COUNT];
#endif /* (defined(MCAL_MODULE_CFG_DMA_USED) && (MCAL_MODULE_CFG_DMA_USED \== STD_ON)) */

#define ADC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Adc_MemMap.h"

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
#define ADC_START_SEC_CODE_ASIL_D_GLOBAL
#include "Adc_MemMap.h"

extern void Adc_DemoEntry(void);
extern void Adc_Demo(void);
extern void AdcDemo_Adc0HwTrigNotif(void);
extern void AdcDemo_Adc2ContinuousNotif(void);
extern void AdcDemo_Adc0HwTrigRsltAccumNotif(void);

#define ADC_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Adc_MemMap.h"

#endif /* _ADC_DEMO_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
