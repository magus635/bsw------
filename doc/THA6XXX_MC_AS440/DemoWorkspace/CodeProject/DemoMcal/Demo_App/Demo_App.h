/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Demo_App.h
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

#ifndef DEMO_APP_H_
#define DEMO_APP_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
/* Header for MCAL modules demo files */
#include "Demo_Version.h"
#include "Demo_Common.h"
#include "Std_Types.h"
#include "Mcall.h"
#include "Port.h"



#if (STD_ON == MCAL_MODULE_CFG_INTC_EN)
#include "Intc_Demo.h"
#endif /* (STD_ON == MCAL_MODULE_CFG_INTC_EN) */

#if (STD_ON == MCAL_MODULE_CFG_MCU_EN)
#include "Mcu_Demo.h"
#endif /* (STD_ON == MCAL_MODULE_CFG_MCU_EN) */

#if (STD_ON == MCAL_MODULE_CFG_ICU_EN)
#include "Icu_Demo.h"
#endif /* (STD_ON == MCAL_MODULE_CFG_ICU_EN) */

#if (STD_ON == MCAL_MODULE_CFG_DIO_EN)
#include "Dio_Demo.h"
#endif /* (STD_ON == MCAL_MODULE_CFG_DIO_EN) */

#if (STD_ON == MCAL_MODULE_CFG_SPI_EN)
#include "Spi_Demo.h"
#endif /* (STD_ON == MCAL_MODULE_CFG_SPI_EN) */

#if (STD_ON == MCAL_MODULE_CFG_CAN_EN)
#include "Can_Demo.h"
#endif /* (STD_ON == MCAL_MODULE_CFG_CAN_EN) */

#if (STD_ON == MCAL_MODULE_CFG_LIN_EN)
#include "Lin_Demo.h"
#endif /* (STD_ON == MCAL_MODULE_CFG_LIN_EN) */

#if (STD_ON == MCAL_MODULE_CFG_GPT_EN)
#include "Gpt_Demo.h"
#endif /* (STD_ON == MCAL_MODULE_CFG_GPT_EN) */

#if (STD_ON == MCAL_MODULE_CFG_PWM_EN)
#include "Pwm_Demo.h"
#endif /* (STD_ON == MCAL_MODULE_CFG_PWM_EN) */

#if (STD_ON == MCAL_MODULE_CFG_OCU_EN)
#include "Ocu_Demo.h"
#endif /* (STD_ON == MCAL_MODULE_CFG_OCU_EN) */

#if (STD_ON == MCAL_MODULE_CFG_WDG_EN)
#include "Wdg_Demo.h"
#endif /* (STD_ON == MCAL_MODULE_CFG_WDG_EN) */

#if (STD_ON == MCAL_MODULE_CFG_FEE_EN)
#include "Fee_Demo.h"
#endif /* (STD_ON == MCAL_MODULE_CFG_FEE_EN) */

#if (STD_ON == MCAL_MODULE_CFG_FLS_EN)
#include "Fls_Demo.h"
#endif /* (STD_ON == MCAL_MODULE_CFG_FLS_EN) */

#if (STD_ON == MCAL_MODULE_CFG_ETH_EN)
#include "Eth_Demo.h"
#endif /* (STD_ON == MCAL_MODULE_CFG_ETH_EN) */

#if (STD_ON == MCAL_MODULE_CFG_IOM_EN)
#include "Iom_Demo.h"
#endif /* (STD_ON == MCAL_MODULE_CFG_IOM_EN) */

#if (STD_ON == MCAL_MODULE_CFG_PORT_EN)
#include "Port_Demo.h"
#endif /* (STD_ON == MCAL_MODULE_CFG_PORT_EN) */

#if (STD_ON == MCAL_MODULE_CFG_DMA_EN)
#include "Dma_Demo.h"
#endif /* (STD_ON == MCAL_MODULE_CFG_DMA_EN) */

#if (STD_ON == MCAL_MODULE_CFG_SENT_EN)
#include "Sent_Demo.h"
#endif /* (STD_ON == MCAL_MODULE_CFG_SENT_EN) */

#if ((defined(MCAL_MODULE_CFG_MSC_EN)) && (STD_ON == MCAL_MODULE_CFG_MSC_EN))
#include "Msc_Demo.h"
#endif /* ((defined(MCAL_MODULE_CFG_MSC_EN)) && (STD_ON == MCAL_MODULE_CFG_MSC_EN)) */

#if (STD_ON == MCAL_MODULE_CFG_ADC_EN)
#include "Adc_Demo.h"
#endif /* (STD_ON == MCAL_MODULE_CFG_ADC_EN) */

#if (STD_ON == MCAL_MODULE_CFG_I2C_EN)
#include "I2c_Demo.h"
#endif /* (STD_ON == MCAL_MODULE_CFG_I2C_EN) */

#if ((defined(MCAL_MODULE_CFG_DSADC_EN)) && (STD_ON == MCAL_MODULE_CFG_DSADC_EN))
#include "Dsadc_Demo.h"
#endif /* (defined(MCAL_MODULE_CFG_DSADC_EN)) && (STD_ON == MCAL_MODULE_CFG_DSADC_EN) */

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
*                               Typedef Definition
****************************************************************************************************/

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

#define DEMO_START_SEC_CODE_ASIL_D_GLOBAL
#include "Demo_MemMap.h"

extern void DemoApp_Init(void);
extern void DemoApp_Main(void);
extern void DemoApp_MainCore1(void);
#if (defined(MCAL_CFG_ENABLE_CORE2) && (MCAL_CFG_ENABLE_CORE2 == STD_ON))
extern void DemoApp_MainCore2(void);
#endif /* #if (defined(MCAL_CFG_ENABLE_CORE2) && (MCAL_CFG_ENABLE_CORE2 == STD_ON)) */
#if (defined(MCAL_CFG_ENABLE_CORE3) && (MCAL_CFG_ENABLE_CORE3 == STD_ON))
extern void DemoApp_MainCore3(void);
#endif /* #if (defined(MCAL_CFG_ENABLE_CORE3) && (MCAL_CFG_ENABLE_CORE3 == STD_ON)) */

#define DEMO_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Demo_MemMap.h"

#endif /* _DEMO_APP_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

