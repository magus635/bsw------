/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Uart_Cfg.h
*
*   Platform             : AUTOSAR
*
*   Peripheral           : Uart
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*
*   Build Version        : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/


/***************************************************************************************************/

/***************************************************************************************************/
#ifndef UART_CFG_H_
#define UART_CFG_H_
/****************************************************************************************************
*                            Global Macro Definitions
****************************************************************************************************/
/***************************************************************************************************
*                               Version Information
***************************************************************************************************/
#define UART_CFG_AR_RELEASE_MAJOR_VERSION        (4U)
#define UART_CFG_AR_RELEASE_MINOR_VERSION        (4U)
#define UART_CFG_AR_RELEASE_REVISION_VERSION     (0U)

#define UART_CFG_SW_MAJOR_VERSION                (1U)
#define UART_CFG_SW_MINOR_VERSION                (2U)
#define UART_CFG_SW_PATCH_VERSION                (0U)


#define UART_CFG_VENDOR_ID                       (175U) /* 0xAF */
#define UART_CFG_MODULE_ID                       (255U) /* 0xFF */


/****************************************************************************************************
**                           Diagnostic report settings                                            **
****************************************************************************************************/
/*
Configuration: UART_DEV_ERROR_DETECT
- if Selected, DET is Enabled
- if Deselected, DET is Disabled
*/
#define UART_DEV_ERROR_DETECT                    (STD_ON) 
/*
Configuration: UART_VERSION_INFO_API
- if Selected, Function Uart_GetVersionInfo is Enabled
- if Deselected, Function Uart_GetVersionInfo is Enabled
*/
#define UART_VERSION_INFO_API                    (STD_ON) 
/****************************************************************************************************
**                               interrupt settings                                                **
****************************************************************************************************/
/*
Configuration: UART_TIMEOUT_DURATION
 Specifies duration of UART channel timeout.
*/
#define UART_TIMEOUT_DURATION                    (50000U)

/*
Configuration: UART_CONFIG_COUNT
 Defines the total number of UART Config infomation.
*/
#define UART_CONFIG_COUNT                        (1U)

/*
Configuration: UART_MAX_HWUNIT_COUNT
 Defines the total number of UART HwUnit.
*/
#define UART_MAX_HWUNIT_COUNT                    (24U)

/*
Configuration: UART_TOTAL_CFG_CHANNEL_NUM
 Define the total number of UART channels.
*/
#define UART_TOTAL_CFG_CHANNEL_NUM               (1U)

/*
Configuration: UART_MAX_CHANNEL_TO_COREx
 Defines the total number of channels mapped to Corex.
*/
#define UART_MAX_CHANNEL_TO_CORE0                (1U)
#define UART_MAX_CHANNEL_TO_CORE1                (0U)
#define UART_MAX_CHANNEL_TO_CORE2                (0U)
#define UART_MAX_CHANNEL_TO_CORE3                (0U)


/*
Configuration: UART_CFG_RX_INTERRUPT_ENABLE
- if Selected, There is a Uart channel to enable receive interrupt
- if Deselected, There is no Uart channel to enable receive interrupt
*/
#define UART_CFG_RX_INTERRUPT_ENABLE             (STD_OFF)


/*
Configuration: UART_CFG_TX_INTERRUPT_ENABLE
- if Selected, There is a Uart channel to enable transmit interrupt
- if Deselected, There is no Uart channel to enable transmit interrupt
*/
#define UART_CFG_TX_INTERRUPT_ENABLE             (STD_OFF)


/*
Configuration: UART_CFG_ERROR_INTERRUPT_ENABLE
- if Selected, There is a Uart channel to enable error interrupt
- if Deselected, There is no Uart channel to enable error interrupt
*/
#define UART_CFG_ERROR_INTERRUPT_ENABLE          (STD_OFF)
/*
Macro definition: UART Channel name
 Generate the macro definition for UART Channel name.
*/
#ifndef UartConf_UartChannel_DebugChannel
/* UartChannelId: 0 -> DebugChannel, mapped to ASI0 in Core0 */
#define UartConf_UartChannel_DebugChannel        (0U)
#endif


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

#endif /* _UART_CFG_H_ */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
