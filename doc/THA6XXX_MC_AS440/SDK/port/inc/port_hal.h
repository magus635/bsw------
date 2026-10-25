/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    port_hal.h
 * Author:      01077
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all hardware abstract layer data type definitions and function declarations.
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#port_hal_h_REF_1:MISRAC2012-Dir-4.8; 
* Justification:Apply such struct/union definitons to simplify the code structure and reduce the code complexity .
*
*#port_hal_h_REF_2:MISRAC2012-Rule-2.3; 
* Justification:This type is used by other file or inline assembly.
*
*#port_hal_h_REF_3:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers
*
*#port_hal_h_REF_4:MISRAC2012-Rule-10.5;
* Justification:Cortex-R52+ lacks bool type; minimum unit is uint8.
*
*#port_hal_h_REF_5:MISRAC2012-Dir-4.3;
* Justification:Mixing inline assembly with C code reduces code complexity
*
*#port_hal_h_REF_6:MISRAC2012-Dir-4.2;
* Justification:The assembler statements is used to synchronize the data of the ARM core.
*
*#port_hal_h_REF_7:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity
*/
#ifndef PORT_HAL_H_
#define PORT_HAL_H_

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "port_register.h"
#include "port_std.h"
#include "cpuwdt_hal.h"
#include "Platform_Types.h"
#include "tha6_cfg.h"
#include "compilertypes.h"
#if(STD_ON == INPUT_ARG_DETECT)
#include "dev.h"
#endif

/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* PORT_MODULE_NUM */
/* #Violation: port_hal_h_REF_3 */
#define PORT_PIN_LIMIT 16U    /* Number of port pins */
/* #Violation: port_hal_h_REF_3 */
#define PORT_HWCR_MASK 3U     /* PORT HWCR register mask */

/* PORT_SPI_FUNCTION_MACRO */
/* #Violation: port_hal_h_REF_3 */
#define Port_Hal_SetEspiSlsoPin(pConfig) Port_Hal_SetPinOutput(pConfig) /* Initial ESPI slso pin */
/* #Violation: port_hal_h_REF_3 */
#define Port_Hal_SetMscEnPin(pConfig) Port_Hal_SetPinOutput(pConfig)    /* Initial MSC en pin */

/* PORT_LVDSBIASVOL_SEL */
/* #Violation: port_hal_h_REF_3 */
#define PORT_LVDSBIASVOL_INTERNAL 0U /* Internal Bias voltage */
/* #Violation: port_hal_h_REF_3 */
#define PORT_LVDSBIASVOL_EXTERNAL 1U /* External Bias voltage */

/* PORT_LVDSTXCM_SEL */
/* #Violation: port_hal_h_REF_3 */
#define PORT_LVDSTXCM_SUBMODE 0U  /* Sub-LVDS mode 0.9V */
/* #Violation: port_hal_h_REF_3 */
#define PORT_LVDSTXCM_HSMODE  1U  /* HS LVDS mode 1.2V */

/* PORT_LVDSIRATIO_TRIM */
/* #Violation: port_hal_h_REF_3 */
#define PORT_LVDSIRATIO_8N  0U  /* Output current ratio -8%  */
/* #Violation: port_hal_h_REF_3 */
#define PORT_LVDSIRATIO_0P  1U  /* Output current ratio +0%  */
/* #Violation: port_hal_h_REF_3 */
#define PORT_LVDSIRATIO_9P  2U  /* Output current ratio +9%  */
/* #Violation: port_hal_h_REF_3 */
#define PORT_LVDSIRATIO_20P 3U  /* Output current ratio +20% */

/* PORT_LVDSRTERMVAL_SEL */
/* #Violation: port_hal_h_REF_3 */
#define PORT_LVDSRTERMVAL_83  0U  /* Termination Resistor 83 Ohm  */
/* #Violation: port_hal_h_REF_3 */
#define PORT_LVDSRTERMVAL_87  1U  /* Termination Resistor 87 Ohm  */
/* #Violation: port_hal_h_REF_3 */
#define PORT_LVDSRTERMVAL_92  2U  /* Termination Resistor 92 Ohm  */
/* #Violation: port_hal_h_REF_3 */
#define PORT_LVDSRTERMVAL_97  3U  /* Termination Resistor 97 Ohm  */
/* #Violation: port_hal_h_REF_3 */
#define PORT_LVDSRTERMVAL_103 4U  /* Termination Resistor 103 Ohm */
/* #Violation: port_hal_h_REF_3 */
#define PORT_LVDSRTERMVAL_109 5U  /* Termination Resistor 109 Ohm */
/* #Violation: port_hal_h_REF_3 */
#define PORT_LVDSRTERMVAL_117 6U  /* Termination Resistor 117 Ohm */
/* #Violation: port_hal_h_REF_3 */
#define PORT_LVDSRTERMVAL_125 7U  /* Termination Resistor 125 Ohm */

#define PORT_RUNSTATE_OK     0U
#define PORT_RUNSTATE_NOT_OK 1U
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/***************************************************** RXMUX *****************************************************/
/* Enum for PORT RXMUX */
typedef enum
{
    PORT_INPUTSEL_A = 0U, /* Port rxmux input select multiplexer A */
    PORT_INPUTSEL_B,      /* Port rxmux input select multiplexer B */
    PORT_INPUTSEL_C,      /* Port rxmux input select multiplexer C */
    PORT_INPUTSEL_D,      /* Port rxmux input select multiplexer D */
    PORT_INPUTSEL_E,      /* Port rxmux input select multiplexer E */
    PORT_INPUTSEL_F,      /* Port rxmux input select multiplexer F */
    PORT_INPUTSEL_G,      /* Port rxmux input select multiplexer G */
    PORT_INPUTSEL_H,      /* Port rxmux input select multiplexer H */
    PORT_INPUTSEL_I,      /* Port rxmux input select multiplexer I */
    PORT_INPUTSEL_J,      /* Port rxmux input select multiplexer J */
    PORT_INPUTSEL_K,      /* Port rxmux input select multiplexer K */
    PORT_INPUTSEL_L,      /* Port rxmux input select multiplexer L */
    PORT_INPUTSEL_M,      /* Port rxmux input select multiplexer M */
    PORT_INPUTSEL_N,      /* Port rxmux input select multiplexer N */
    PORT_INPUTSEL_O,      /* Port rxmux input select multiplexer O */
    PORT_INPUTSEL_P,      /* Port rxmux input select multiplexer P */
    PORT_INPUTSEL_Q,      /* Port rxmux input select multiplexer Q */
    PORT_INPUTSEL_R,      /* Port rxmux input select multiplexer R */
    PORT_INPUTSEL_S,      /* Port rxmux input select multiplexer S */
    PORT_INPUTSEL_T,      /* Port rxmux input select multiplexer T */
    PORT_INPUTSEL_U,      /* Port rxmux input select multiplexer U */
    PORT_INPUTSEL_V       /* Port rxmux input select multiplexer V */
} Port_InputSel;

/* Enum for PORT RXMUX select IOM/EXTI pin input */
typedef enum
{
    PORT_RXMUXPINSEL_0 = 0U, /* Port rxmux select IOM/EXTI input source pin, only THA6104 support */
    PORT_RXMUXPINSEL_1 = 1U  /* Port rxmux select IOM/EXTI input source pin, only THA6104 support */
/* #Violation: port_hal_h_REF_2 */
} Port_RxmuxPinInputSel;

/***************************************************** RXMUX CAN *****************************************************/
/* Enum for PORT RXMUX select CAN module */
typedef enum
{
    PORT_RXMUXCANID_0 = 0U, /* Port rxmux select can0 */
    PORT_RXMUXCANID_1,      /* Port rxmux select can1 */
    PORT_RXMUXCANID_2,      /* Port rxmux select can2, only THA6412 support */
    PORT_RXMUXCANID_3       /* Port rxmux select can3, only THA6412 support */
} Port_RxmuxCanId;

/* Enum for PORT RXMUX select CANx channel */
typedef enum
{
    PORT_RXMUXCANCHANNEL_0 = 0U, /* Port rxmux select canx channel 0 */
    PORT_RXMUXCANCHANNEL_1 = 4U, /* Port rxmux select canx channel 1 */
    PORT_RXMUXCANCHANNEL_2 = 8U  /* Port rxmux select canx channel 2 */
} Port_RxmuxCanChannel;

/***************************************************** RXMUX I2C *****************************************************/
/* Enum for PORT RXMUX select I2C module */
typedef enum
{
    PORT_RXMUXI2CID_0 = 0U, /* Port rxmux select I2C0 */
    PORT_RXMUXI2CID_1,      /* Port rxmux select I2C1, only THA6412 and THA6104 support */
} Port_RxmuxI2cId;

/***************************************************** RXMUX DSADC *****************************************************/
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* Enum for PORT RXMUX select DSADC trigger channel */
typedef enum
{
    PORT_RXMUXDSADCTRIGGERCHANNEL_0 = 0x0200, /* Port rxmux select DSADC0 trigger channel, only THA6206 and THA6412 support */
    PORT_RXMUXDSADCTRIGGERCHANNEL_1 = 0x0204, /* Port rxmux select DSADC1 trigger channel, only THA6206 and THA6412 support */
    PORT_RXMUXDSADCTRIGGERCHANNEL_2 = 0x0208, /* Port rxmux select DSADC2 trigger channel, only THA6206 and THA6412 support */
    PORT_RXMUXDSADCTRIGGERCHANNEL_3 = 0x020C, /* Port rxmux select DSADC3 trigger channel, only THA6206 and THA6412 support */
#if defined(THA6_THA6412)
    PORT_RXMUXDSADCTRIGGERCHANNEL_4 = 0x0210, /* Port rxmux select DSADC4 trigger channel, only THA6412 support */
    PORT_RXMUXDSADCTRIGGERCHANNEL_5 = 0x0214, /* Port rxmux select DSADC5 trigger channel, only THA6412 support */
    PORT_RXMUXDSADCTRIGGERCHANNEL_6 = 0x0218, /* Port rxmux select DSADC6 trigger channel, only THA6412 support */
    PORT_RXMUXDSADCTRIGGERCHANNEL_7 = 0x021C, /* Port rxmux select DSADC7 trigger channel, only THA6412 support */
    PORT_RXMUXDSADCTRIGGERCHANNEL_8 = 0x1900, /* Port rxmux select DSADC8 trigger channel, only THA6412 support */
    PORT_RXMUXDSADCTRIGGERCHANNEL_9 = 0x1904  /* Port rxmux select DSADC9 trigger channel, only THA6412 support */
#endif
} Port_RxmuxDsadcTriggerChannel;
#endif

/***************************************************** RXMUX ASI *****************************************************/
/* Enum for PORT RXMUX select ASI module */
typedef enum
{
    PORT_RXMUXASIID_0 = 0U,   /* Port rxmux select ASI0 */
    PORT_RXMUXASIID_1 = 4U,   /* Port rxmux select ASI1 */
    PORT_RXMUXASIID_2 = 8U,   /* Port rxmux select ASI2 */
    PORT_RXMUXASIID_3 = 12U,  /* Port rxmux select ASI3 */
    PORT_RXMUXASIID_4 = 16U,  /* Port rxmux select ASI4 */
    PORT_RXMUXASIID_5 = 20U,  /* Port rxmux select ASI5 */
    PORT_RXMUXASIID_6 = 24U,  /* Port rxmux select ASI6 */
    PORT_RXMUXASIID_7 = 28U,  /* Port rxmux select ASI7 */
    PORT_RXMUXASIID_8 = 32U,  /* Port rxmux select ASI8, only THA6412 and THA6104 support */
    PORT_RXMUXASIID_9 = 36U,  /* Port rxmux select ASI9, only THA6412 and THA6104 support */
    PORT_RXMUXASIID_10 = 40U, /* Port rxmux select ASI10, only THA6412 and THA6104 support */
    PORT_RXMUXASIID_11 = 44U, /* Port rxmux select ASI11, only THA6412 and THA6104 support */
    PORT_RXMUXASIID_12 = 48U, /* Port rxmux select ASI12, only THA6412 support */
    PORT_RXMUXASIID_13 = 52U, /* Port rxmux select ASI13, only THA6412 support */
    PORT_RXMUXASIID_14 = 56U, /* Port rxmux select ASI14, only THA6412 support */
    PORT_RXMUXASIID_15 = 60U, /* Port rxmux select ASI15, only THA6412 support */
    PORT_RXMUXASIID_16 = 64U, /* Port rxmux select ASI16, only THA6412 support */
    PORT_RXMUXASIID_17 = 68U, /* Port rxmux select ASI17, only THA6412 support */
    PORT_RXMUXASIID_18 = 72U, /* Port rxmux select ASI18, only THA6412 support */
    PORT_RXMUXASIID_19 = 76U, /* Port rxmux select ASI19, only THA6412 support */
    PORT_RXMUXASIID_20 = 80U, /* Port rxmux select ASI20, only THA6412 support */
    PORT_RXMUXASIID_21 = 84U, /* Port rxmux select ASI21, only THA6412 support */
    PORT_RXMUXASIID_22 = 88U, /* Port rxmux select ASI22, only THA6412 support */
    PORT_RXMUXASIID_23 = 92U  /* Port rxmux select ASI23, only THA6412 support */
} Port_RxmuxAsiId;

/***************************************************** RXMUX ESPI *****************************************************/
/* Enum for PORT RXMUX select ESPI module */
typedef enum
{
    PORT_RXMUXESPIID_0 = 7U, /* Port rxmux select ESPI0 */
    PORT_RXMUXESPIID_1,      /* Port rxmux select ESPI1 */
    PORT_RXMUXESPIID_2,      /* Port rxmux select ESPI2 */
    PORT_RXMUXESPIID_3,      /* Port rxmux select ESPI3 */
    PORT_RXMUXESPIID_4,      /* Port rxmux select ESPI4 */
    PORT_RXMUXESPIID_5,      /* Port rxmux select ESPI5 */
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    PORT_RXMUXESPIID_6,      /* Port rxmux select ESPI6, only THA6206 and THA6412 support */
    PORT_RXMUXESPIID_7,      /* Port rxmux select ESPI7, only THA6206 and THA6412 support */
    PORT_RXMUXESPIID_8       /* Port rxmux select ESPI8, only THA6206 and THA6412 support */
#endif
} Port_RxmuxEspiId;

/***************************************************** RXMUX SENT *****************************************************/
/* Enum for PORT RXMUX select SENT module */
typedef enum
{
    PORT_RXMUXSENTID_0 = 0U,   /* Port rxmux select SENT 0 */
    PORT_RXMUXSENTID_1 = 4U,   /* Port rxmux select SENT 1 */
    PORT_RXMUXSENTID_2 = 8U,   /* Port rxmux select SENT 2 */
    PORT_RXMUXSENTID_3 = 12U,  /* Port rxmux select SENT 3 */
    PORT_RXMUXSENTID_4 = 16U,  /* Port rxmux select SENT 4 */
    PORT_RXMUXSENTID_5 = 20U,  /* Port rxmux select SENT 5 */
    PORT_RXMUXSENTID_6 = 24U,  /* Port rxmux select SENT 6, only THA6206 and THA6412 support */
    PORT_RXMUXSENTID_7 = 28U,  /* Port rxmux select SENT 7, only THA6206 and THA6412 support */
    PORT_RXMUXSENTID_8 = 32U,  /* Port rxmux select SENT 8, only THA6206 and THA6412 support */
    PORT_RXMUXSENTID_9 = 36U,  /* Port rxmux select SENT 9, only THA6206 and THA6412 support */
    PORT_RXMUXSENTID_10 = 40U, /* Port rxmux select SENT 10, only THA6412 support */
    PORT_RXMUXSENTID_11 = 44U, /* Port rxmux select SENT 11, only THA6412 support */
    PORT_RXMUXSENTID_12 = 48U, /* Port rxmux select SENT 12, only THA6412 support */
    PORT_RXMUXSENTID_13 = 52U, /* Port rxmux select SENT 13, only THA6412 support */
    PORT_RXMUXSENTID_14 = 56U, /* Port rxmux select SENT 14, only THA6412 support */
    PORT_RXMUXSENTID_15 = 60U, /* Port rxmux select SENT 15, only THA6412 support */
    PORT_RXMUXSENTID_16 = 64U, /* Port rxmux select SENT 16, only THA6412 support */
    PORT_RXMUXSENTID_17 = 68U, /* Port rxmux select SENT 17, only THA6412 support */
    PORT_RXMUXSENTID_18 = 72U, /* Port rxmux select SENT 18, only THA6412 support */
    PORT_RXMUXSENTID_19 = 76U, /* Port rxmux select SENT 19, only THA6412 support */
    PORT_RXMUXSENTID_20 = 80U, /* Port rxmux select SENT 20, only THA6412 support */
    PORT_RXMUXSENTID_21 = 84U, /* Port rxmux select SENT 21, only THA6412 support */
    PORT_RXMUXSENTID_22 = 88U, /* Port rxmux select SENT 22, only THA6412 support */
    PORT_RXMUXSENTID_23 = 92U, /* Port rxmux select SENT 23, only THA6412 support */
    PORT_RXMUXSENTID_24 = 96U  /* Port rxmux select SENT 24, only THA6412 support */
} Port_RxmuxSentId;

/***************************************************** RXMUX EXTI *****************************************************/
/* Enum for PORT RXMUX select EXTI module */
typedef enum
{
    PORT_RXMUXEXTISEL_72 = 0U  /* Port rxmux select EXTI Channel 7 inputs 2, only THA6104 support */
/* #Violation: port_hal_h_REF_2 */
} Port_RxmuxExtiChannel;

/***************************************************** RXMUX IOM *****************************************************/
/* Enum for PORT RXMUX select IOM module */
typedef enum
{
    PORT_RXMUXIOMID_0 = 0x12U, /* Port rxmux select IOM 0 */
#if defined(THA6_THA6104) || defined(THA6_THA6412)
    PORT_RXMUXIOMID_1 = 0x1FU, /* Port rxmux select IOM 1, only THA6104 and THA6206 support */
#endif
    PORT_RXMUXIOMID_2 = 0x14U  /* Port rxmux select IOM 2 */
} Port_RxmuxIomId;

/* Enum for PORT RXMUX select IOM pin input */
typedef enum
{
    PORT_RXMUXIOMPIN_13 = 13U, /* Port rxmux select IOM pin13 input, only THA6104 support */
    PORT_RXMUXIOMPIN_14 = 14U, /* Port rxmux select IOM pin14 input, only THA6104 support */
    PORT_RXMUXIOMPIN_15 = 15U  /* Port rxmux select IOM pin15 input, only THA6104 support */
/* #Violation: port_hal_h_REF_2 */
} Port_RxmuxIomPin;

/* Enum for PORT RXMUX select IOM module */
typedef enum
{
    PORT_RXMUXIOMCHANNEL_0 = 0U,   /* Port rxmux select IOM channel 0 */
    PORT_RXMUXIOMCHANNEL_1 = 2U,   /* Port rxmux select IOM channel 1 */
    PORT_RXMUXIOMCHANNEL_2 = 4U,   /* Port rxmux select IOM channel 2 */
    PORT_RXMUXIOMCHANNEL_3 = 6U,   /* Port rxmux select IOM channel 3 */
    PORT_RXMUXIOMCHANNEL_4 = 8U,   /* Port rxmux select IOM channel 4 */
    PORT_RXMUXIOMCHANNEL_5 = 10U,  /* Port rxmux select IOM channel 5 */
    PORT_RXMUXIOMCHANNEL_6 = 12U,  /* Port rxmux select IOM channel 6 */
    PORT_RXMUXIOMCHANNEL_7 = 14U,  /* Port rxmux select IOM channel 7 */
    PORT_RXMUXIOMCHANNEL_8 = 16U,  /* Port rxmux select IOM channel 8 */
    PORT_RXMUXIOMCHANNEL_9 = 18U,  /* Port rxmux select IOM channel 9 */
    PORT_RXMUXIOMCHANNEL_10 = 20U, /* Port rxmux select IOM channel 10 */
    PORT_RXMUXIOMCHANNEL_11 = 22U, /* Port rxmux select IOM channel 11 */
    PORT_RXMUXIOMCHANNEL_12 = 24U, /* Port rxmux select IOM channel 12 */
    PORT_RXMUXIOMCHANNEL_13 = 26U, /* Port rxmux select IOM channel 13 */
    PORT_RXMUXIOMCHANNEL_14 = 28U, /* Port rxmux select IOM channel 14 */
    PORT_RXMUXIOMCHANNEL_15 = 30U  /* Port rxmux select IOM channel 15 */
} Port_RxmuxIomChannel;

/***************************************************** RXMUX PSI5 *****************************************************/
/* Enum for PORT RXMUX select PSI5RX module */
typedef enum
{
    PORT_RXMUXPSI5CHANNEL_0 = 0U, /* Port rxmux select PSI5RX 0, only THA6412 support */
    PORT_RXMUXPSI5CHANNEL_1 = 4U, /* Port rxmux select PSI5RX 1, only THA6412 support */
    PORT_RXMUXPSI5CHANNEL_2 = 8U, /* Port rxmux select PSI5RX 2, only THA6412 support */
    PORT_RXMUXPSI5CHANNEL_3 = 12U /* Port rxmux select PSI5RX 3, only THA6412 support */
} Port_RxmuxPsi5Channel;

/* Enum for port pin slew rate */
typedef enum
{
    PORT_SLEWRATE_LOW = 0U, /* Port pin slew rate is low */
    PORT_SLEWRATE_HIGH      /* Port pin slew rate is high */
} Port_SlewRate;

/* Enum for port emergency state */
typedef enum
{
    PORT_EMERGENCYSTATE_DISABLE = 0U, /* Port emergency disable */
    PORT_EMERGENCYSTATE_ENABLE = 3U   /* Port emergency enable */
} Port_EmergencyState;

/* Enum for port pin controller port(default) or peripheral */
typedef enum
{
    PORT_CONTROLLER_PORT = 0U,      /* Port pin controller is port  */
    PORT_CONTROLLER_PERIPHERAL = 3U /* Port pin controller is peripheral  */
} Port_Controller;

/* Enum for port pin function mode */
typedef enum
{
    PORT_FUNCTIONMODE_DIGITAL = 0U, /* Port pin digital mode */
    PORT_FUNCTIONMODE_ANALOG = 3U   /* Port pin analog mode */
} Port_FunctionMode;

/* Enum for port pin STTL state */
typedef enum
{
    PORT_STTL_LOW = 0U, /* Port pin STTL state is low, only THA6412 and THA6104 support */
    PORT_STTL_HIGH      /* Port pin STTL state is high, only THA6412 and THA6104 support */
} Port_SttlState;

/* Enum for port backup status */
typedef enum
{
    PORT_BACKUPSTS_DISABLE = 0U, /* Port backup status disable, only THA6412 and THA6104 support */
    PORT_BACKUPSTS_ENABLE = 1U   /* Port backup status enable, only THA6412 and THA6104 support */
/* #Violation: port_hal_h_REF_2 */
} Port_BackupState;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/***************************************************** PORT Pin Configuration Structure ******************************************************/
/* Port module and pin */
/* #Violation: port_hal_h_REF_1 */
typedef struct
{
    PORT_MODULE *port; /* Port module */
    Port_Pin pin;     /* Port pin */
} Port_ModulePin;

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* Port module and pins for LVDS */
/* #Violation: port_hal_h_REF_1 */
typedef struct
{
    PORT_MODULE *port; /* Port module */
    Port_Pin pinP;    /* Port pin P */
    Port_Pin pinN;    /* Port pin N */
} Port_LvdsModulePin;
#endif

/* Port input configuration */
typedef struct
{
    Port_ModulePin modulePin; /* Port module and pin */
    Port_Pull pull;           /* Select pull-up/pull-down */
    Port_Level level;         /* Select AL/TTL level */
} Port_InputConfig;

/* Port output configuration */
/* #Violation: port_hal_h_REF_7 */
typedef struct
{
    Port_ModulePin modulePin;         /* Port module and pin */
    Port_OutputSel outputSel;         /* Output multiplexer */
    Port_OutputMode outputMode;       /* Select push-pull/open-drain */
    Port_Controller controller;       /* Select controller port/peripheral */
    Port_DriveStrength driveStrength; /* Select drive strength */
} Port_OutputConfig;

/* Port output state configuration */
typedef struct
{
    Port_ModulePin modulePin;     /* Port module and pin */
    Port_OutputState outputState; /* Select port pin output state */
} Port_OutputStateConfig;

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* Port LVDS configuration */
/* #Violation: port_hal_h_REF_1 */
typedef struct
{
    PORT_MODULE *port; /* Port module */
    Port_Pin pinP;    /* Port pin P */
    Port_Pin pinN;    /* Port pin N */

    Port_OutputSel outputSel; /* Output multiplexer */
    boolean txEnable;         /* LVDS transmit driver enable */
    boolean biasEnable;       /* Bias circuit enable */
    uint8 biasVol;            /* Bias voltage for I/O
                                 This parameter can be a value of PORT_LVDSBIASVOL_SEL */
    uint8 txCommonMode;       /* Transmitter common mode
                                 This parameter can be a value of PORT_LVDSTXCM_SEL */
    uint8 iRatio;             /* Output current ratio
                                 This parameter can be a value of PORT_LVDSIRATIO_TRIM */
    uint8 vod;                /* Drive current and differential output voltage magnitude
                                 This parameter must be a number between 0U and 3U */
    uint8 rTermVal;           /* Termination value
                                 This parameter can be a value of PORT_LVDSRTERMVAL_SEL */
    boolean rTermEnable;      /* Termination Resistor enable/disable */
} Port_LvdsConfig;
#endif

/* Port STTL state configuration */
typedef struct
{
    Port_ModulePin modulePin; /* Port module and pin */
    Port_SttlState state;     /* Select port pin STTL state */
/* #Violation: port_hal_h_REF_2 */
} Port_SttlStateConfig;

/* Port pull configuration */
typedef struct
{
    Port_ModulePin modulePin; /* Port module and pin */
    Port_Pull pull;           /* Select pull-up/pull-down */
} Port_PullConfig;

/* Port slew rate configuration */
typedef struct
{
    Port_ModulePin modulePin; /* Port module and pin */
    Port_SlewRate slewRate;   /* Select slew rate */
} Port_SlewRateConfig;

/* Port input mode configuration */
typedef struct
{
    Port_ModulePin modulePin; /* Port module and pin */
    Port_InputMode mode;      /* Select input mode cmos/schmidt */
} Port_InputModeConfig;

/* Port emergency configuration */
typedef struct
{
    Port_ModulePin modulePin;  /* Port module and pin */
    Port_EmergencyState state; /* Set emergency enable/disable */
} Port_EmergencyConfig;

/* Port controller configuration */
typedef struct
{
    Port_ModulePin modulePin;   /* Port module and pin */
    Port_Controller controller; /* Set port pin controller */
} Port_ControllerConfig;

/* Port analog/digital configuration */
typedef struct
{
    Port_ModulePin modulePin; /* Port module and pin */
    Port_FunctionMode mode;   /* Set port pin analog/digital */
} Port_AnalogDigitalConfig;

/***************************************************** Peripheral Pin Configuration Structure *****************************************************/
/***************************************************** ASI *****************************************************/
/* ASI input and input RXMUX configuration */
/* #Violation: port_hal_h_REF_1 */
typedef struct
{
    Port_InputConfig inputConfig; /* Port input configuration */
    Port_RxmuxAsiId id;           /* Select ASI module */
    Port_InputSel inputSel;       /* Select ASI input multiplexer */
} Port_AsiInputConfig;

/****************************************************** CAN ******************************************************/
/* Can input and input RXMUX configuration */
/* #Violation: port_hal_h_REF_1 */
typedef struct
{
    Port_InputConfig inputConfig; /* Port input configuration */
    Port_RxmuxCanId id;           /* Select can module */
    Port_RxmuxCanChannel channel; /* Select can channel */
    Port_InputSel inputSel;       /* Select can input multiplexer */
} Port_CanInputConfig;

/***************************************************** DSADC *****************************************************/
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* DSADC trigger input and input RXMUX configuration */
/* #Violation: port_hal_h_REF_1 */
typedef struct
{
    Port_InputConfig inputConfig;                 /* Port input configuration */
    Port_RxmuxDsadcTriggerChannel triggerChannel; /* Select DSADC trigger channel */
    Port_InputSel inputSel;                       /* Select DSADC trigger input multiplexer */
} Port_DsadcTriggerInputConfig;
#endif

/****************************************************** ESPI *****************************************************/
/* ESPI input and input RXMUX configuration */
/* #Violation: port_hal_h_REF_1 */
typedef struct
{
    Port_InputConfig inputConfig; /* Port input configuration */
    Port_RxmuxEspiId id;          /* Select ESPI module */
    Port_InputSel inputSel;       /* Select ESPI input multiplexer */
} Port_EspiInputConfig;

/* ESPI input/output pin configuration */
/* #Violation: port_hal_h_REF_1 */
typedef struct
{
    Port_OutputConfig outputConfig; /* Port output configuration */
    Port_RxmuxEspiId id;            /* Select ESPI module */
    Port_InputSel inputSel;         /* Port input configuration */
} Port_EspiInOutConfig;

/****************************************************** ETH ******************************************************/
/* ETH input and input RXMUX configuration */
/* #Violation: port_hal_h_REF_1 */
/* #Violation: port_hal_h_REF_7 */
typedef struct
{
    Port_InputConfig inputConfig; /* Port input configuration */
    Port_InputSel inputSel;       /* Port input multiplexer */
} Port_EthInputConfig;

/* ETH input/output configuration */
/* #Violation: port_hal_h_REF_1 */
/* #Violation: port_hal_h_REF_7 */
typedef struct
{
    Port_OutputConfig outputConfig; /* Port output configuration */
    Port_InputSel inputSel;         /* Port input multiplexer */
} Port_EthInOutConfig;

/****************************************************** I2C ******************************************************/
/* I2C input/output pin configuration */
/* #Violation: port_hal_h_REF_1 */
typedef struct
{
    Port_OutputConfig outputConfig; /* Port output configuration */
    Port_RxmuxI2cId id;             /* Select I2C module */
    Port_InputSel inputSel;         /* Select I2C input multiplexer */
} Port_I2cInOutConfig;

/****************************************************** SENT *****************************************************/
/* SENT input and input RXMUX configuration */
/* #Violation: port_hal_h_REF_1 */
typedef struct
{
    Port_InputConfig inputConfig; /* Port input configuration */
    Port_RxmuxSentId id;          /* Select SENT module */
    Port_InputSel inputSel;       /* Select SENT input multiplexer */
} Port_SentInputConfig;

/* SENT input/output pin configuration */
/* #Violation: port_hal_h_REF_1 */
typedef struct
{
    Port_OutputConfig outputConfig; /* Port output configuration */
    Port_RxmuxSentId id;            /* Select SENT module */
    Port_InputSel inputSel;         /* Select SENT input multiplexer */
} Port_SentInOutConfig;

/****************************************************** PSI5 *****************************************************/
/* PSI5 input and input RXMUX configuration */
/* #Violation: port_hal_h_REF_1 */
typedef struct
{
    Port_InputConfig inputConfig;  /* Port input configuration */
    Port_InputSel inputSel;        /* Select PSI5 input multiplexer */
    Port_RxmuxPsi5Channel channel; /* Select PSI5 channel */
} Port_Psi5InputConfig;
/******************************************************** PORT Pin Map Structure ********************************************************/
/****************************************************** ASI ******************************************************/
/* ASI IO configuration structure */
/* #Violation: port_hal_h_REF_1 */
typedef struct
{
    Port_AsiInputConfig const *pRx; /* ASI rx configuration */
    Port_OutputConfig const *pTx;   /* ASI tx configuration */
} Port_AsiPinsConfig;

/****************************************************** CAN ******************************************************/
/* CAN IO configuration structure */
/* #Violation: port_hal_h_REF_1 */
typedef struct
{
    Port_CanInputConfig const *pRx; /* CAN rx configuration */
    Port_OutputConfig const *pTx;   /* CAN tx configuration */
    Port_InputConfig const *pEctt;  /* CAN ectt configuration */
} Port_CanPinsConfig;

/****************************************************** ESPI *****************************************************/
/* ESPI master full-duplex mode IO configuration structure */
/* #Violation: port_hal_h_REF_1 */
typedef struct
{
    Port_OutputConfig const *pSclk;    /* ESPI sclk configuration */
    Port_OutputConfig const *pMtsr;    /* ESPI mtsr configuration */
    Port_EspiInputConfig const *pMrst; /* ESPI mrst configuration */
    Port_OutputConfig const *pSlso;    /* ESPI slso configuration */
} Port_EspiMasterFullDuplexPinsConfig;

/* ESPI master half-duplex mode IO configuration structure */
/* #Violation: port_hal_h_REF_1 */
typedef struct
{
    Port_OutputConfig const *pSclk;    /* ESPI sclk configuration */
    Port_EspiInOutConfig const *pMtsr; /* ESPI mtsr configuration */
    Port_OutputConfig const *pSlso;    /* ESPI slso configuration */
} Port_EspiMasterHalfDuplexPinsConfig;

/* ESPI slave full-duplex mode IO configuration structure */
/* #Violation: port_hal_h_REF_1 */
typedef struct
{
    Port_EspiInputConfig const *pSclk; /* ESPI sclk configuration */
    Port_EspiInputConfig const *pMtsr; /* ESPI mtsr configuration */
    Port_OutputConfig const *pMrst;    /* ESPI mrst configuration */
    Port_EspiInputConfig const *pSlsi; /* ESPI slsi configuration */
} Port_EspiSlaveFullDuplexPinsConfig;

/* ESPI slave half-duplex mode IO configuration structure */
/* #Violation: port_hal_h_REF_1 */
typedef struct
{
    Port_EspiInputConfig const *pSclk; /* ESPI sclk configuration */
    Port_EspiInOutConfig const *pMtsr; /* ESPI mtsr configuration */
    Port_EspiInputConfig const *pSlsi; /* ESPI slsi configuration */
} Port_EspiSlaveHalfDuplexPinsConfig;

/****************************************************** ETH ******************************************************/
/* ETH MII IO configuration structure */
/* #Violation: port_hal_h_REF_1 */
/* #Violation: port_hal_h_REF_7 */
typedef struct
{
    /* ETH clock and control signal */
    Port_EthInputConfig const *pCrs;   /* ETH crs configuration */
    Port_EthInputConfig const *pCol;   /* ETH col configuration */
    Port_EthInputConfig const *pTxClk; /* ETH txClk configuration */
    Port_EthInputConfig const *pRxClk; /* ETH rxClk configuration */
    Port_EthInputConfig const *pRxDv;  /* ETH rxDv configuration */
    Port_EthInputConfig const *pRxEr;  /* ETH rxEr configuration */
    /* ETH rx signal */
    Port_EthInputConfig const *pRxd0; /* ETH rxd0 configuration */
    Port_EthInputConfig const *pRxd1; /* ETH rxd1 configuration */
    Port_EthInputConfig const *pRxd2; /* ETH rxd2 configuration */
    Port_EthInputConfig const *pRxd3; /* ETH rxd3 configuration */
    /* ETH tx signal */
    Port_OutputConfig const *pTxEn; /* ETH txEn configuration */
    Port_OutputConfig const *pTxEr; /* ETH txEr configuration */
    Port_OutputConfig const *pTxd0; /* ETH txd0 configuration */
    Port_OutputConfig const *pTxd1; /* ETH txd1 configuration */
    Port_OutputConfig const *pTxd2; /* ETH txd2 configuration */
    Port_OutputConfig const *pTxd3; /* ETH txd3 configuration */
    Port_OutputConfig const *pMdc;  /* ETH mdc configuration */
    /* ETH mdio signal */
    Port_EthInOutConfig const *pMdio; /* ETH mdio configuration */
} Port_EthMiiPinsConfig;

/* ETH RGMII IO configuration structure */
/* #Violation: port_hal_h_REF_1 */
/* #Violation: port_hal_h_REF_7 */
typedef struct
{
    /* ETH clock and control signal */
    Port_InputConfig const *pGrefClk;  /* ETH grefClk configuration */
    Port_EthInputConfig const *pRxCtl; /* ETH rxCtl configuration */
    Port_EthInputConfig const *pRxClk; /* ETH rxClk configuration */
    Port_EthInputConfig const *pCol;   /* ETH col configuration */
    Port_EthInputConfig const *pCrs;   /* ETH crs configuration */
    /* ETH rx signal */
    Port_EthInputConfig const *pRxd0; /* ETH rxd0 configuration */
    Port_EthInputConfig const *pRxd1; /* ETH rxd1 configuration */
    Port_EthInputConfig const *pRxd2; /* ETH rxd2 configuration */
    Port_EthInputConfig const *pRxd3; /* ETH rxd3 configuration */
    /* ETH tx signal */
    Port_OutputConfig const *pTxClk; /* ETH txClk configuration */
    Port_OutputConfig const *pTxCtl; /* ETH txCtl configuration */
    Port_OutputConfig const *pTxd0;  /* ETH txd0 configuration */
    Port_OutputConfig const *pTxd1;  /* ETH txd1 configuration */
    Port_OutputConfig const *pTxd2;  /* ETH txd2 configuration */
    Port_OutputConfig const *pTxd3;  /* ETH txd3 configuration */
    Port_OutputConfig const *pMdc;   /* ETH mdc configuration */
    /* ETH mdio signal */
    Port_EthInOutConfig const *pMdio; /* ETH mdio configuration */
} Port_EthRgmiiPinsConfig;

/* ETH RMII IO configuration structure */
/* #Violation: port_hal_h_REF_1 */
/* #Violation: port_hal_h_REF_7 */
typedef struct
{
    /* ETH clock and control signal */
    Port_EthInputConfig const *pRefClk; /* ETH refClk configuration */
    Port_EthInputConfig const *pCrsDv;  /* ETH crsDv configuration */
    Port_EthInputConfig const *pRxEr;   /* ETH rxEr configuration */
    /* ETH rx signal */
    Port_EthInputConfig const *pRxd0; /* ETH rxd0 configuration */
    Port_EthInputConfig const *pRxd1; /* ETH rxd1 configuration */
    /* ETH tx signal */
    Port_OutputConfig const *pTxEn; /* ETH txEn configuration */
    Port_OutputConfig const *pTxd0; /* ETH txd0 configuration */
    Port_OutputConfig const *pTxd1; /* ETH txd1 configuration */
    Port_OutputConfig const *pMdc;  /* ETH mdc configuration */
    /* ETH mdio signal */
    Port_EthInOutConfig const *pMdio; /* ETH mdio configuration */
} Port_EthRmiiPinsConfig;

/****************************************************** I2C ******************************************************/
/* I2C master mode IO configuration structure */
/* #Violation: port_hal_h_REF_1 */
typedef struct
{
    Port_I2cInOutConfig const *pScl; /* I2C scl configuration */
    Port_I2cInOutConfig const *pSda; /* I2C sda configuration */
} Port_I2cMasterPinsConfig;

/****************************************************** MSC ******************************************************/
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* MSC IO configuration structure */
/* #Violation: port_hal_h_REF_1 */
typedef struct
{
    Port_OutputConfig const *pEn0; /* MSC en0 configuration */
    Port_OutputConfig const *pEn1; /* MSC en1 configuration */
    Port_OutputConfig const *pEn2; /* MSC en2 configuration, only THA6412 support */
    Port_InputConfig const *pSdi;  /* MSC sdi configuration */
    Port_LvdsConfig const *pFclpn; /* MSC fclpn configuration */
    Port_LvdsConfig const *pSopn;  /* MSC sopn configuration */
} Port_MscPinsConfig;
#endif

/****************************************************** SENT *****************************************************/
/* SENT normal mode IO configuration structure */
/* #Violation: port_hal_h_REF_1 */
typedef struct
{
    Port_SentInputConfig const *pSent; /* SENT sent configuration */
} Port_SentNormalPinsConfig;

/* SENT spc mode IO configuration structure */
/* #Violation: port_hal_h_REF_1 */
typedef struct
{
    Port_SentInOutConfig const *pSpc; /* SENT spc input/output configuration */
} Port_SentSpcPinsConfig;

/****************************************************** IOM *****************************************************/
/* IOM input/output pin configuration */
/* #Violation: port_hal_h_REF_1 */
typedef struct
{
    Port_InputConfig inputConfig; /* Port input configuration */
    Port_RxmuxIomId id;           /* Select IOM module */
    Port_RxmuxIomChannel channel; /* Select IOM channel */
    Port_InputSel inputSel;       /* Select input multiplexer */
} Port_IomInputConfig;

/****************************************************** PSI5 *****************************************************/
/* PSI5 input/output configuration structure */
/* #Violation: port_hal_h_REF_1 */
typedef struct
{
    Port_Psi5InputConfig const *pRx; /* PSI5 rx configuration */
    Port_OutputConfig const *pTx;    /* PSI5 tx configuration */
/* #Violation: port_hal_h_REF_2 */
} Port_Psi5PinsConfig;
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
#define PORT_START_SEC_CODE_ASIL_D_GLOBAL
#include "Port_MemMap.h"
/************************************************** PORT pin input ***************************************************/
/**********************************************************************************************************************
 * Function: Port_Hal_GetPinInputState
 * Description: Get port pin input state.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input: pModulePin: Pointer to port module and pin.
 * Inout:  None
 * Output: None
 * Return: Port_InputState: PORT_INPUTSTATE_HIGH: Pin level is high. 
 *                          PORT_INPUTSTATE_LOW: Pin level is low.
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE Port_InputState Port_Hal_GetPinInputState(const Port_ModulePin *pModulePin);

/**********************************************************************************************************************
 * Function: Port_Hal_GetPinGroupInputState
 * Description: Get port pin group input state.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input: pModulePin: Pointer to port module and pin.
 *        pinMask: Selects the pins which should be read, starting from pModulePin->pin.
 * Inout:  None
 * Output: None
 * Return: uint16: Selected pin values.
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint16 Port_Hal_GetPinGroupInputState(const Port_ModulePin *pModulePin, uint16 pinMask);

/************************************************** PORT pin output **************************************************/
/**********************************************************************************************************************
 * Function: Port_Hal_SetPinState
 * Description: Set port pin output state.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different pins, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input: pConfig: Pointer to port module pin and output state configuration.
 * Inout:  None
 * Output: None
 * Return: None
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Port_Hal_SetPinState(const Port_OutputStateConfig *pConfig);

/**********************************************************************************************************************
 * Function: Port_Hal_SetPinGroupState
 * Description: Set port pin group output state.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different PORT modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input: pConfig: Pointer to all port module pin and output state configuration.
 *        pinMask: Selects the pins which should be modified, starting from pConfig->modulePin.pin.
 * Inout:  None
 * Output: None
 * Return: None
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Port_Hal_SetPinGroupState(const Port_OutputStateConfig *pConfig, uint16 pinMask);

/**********************************************************************************************************************
 * Function: Port_Hal_SetPinHigh
 * Description: Set port pin output high.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input: pModulePin: Pointer to port module and pin.
 * Inout:  None
 * Output: None
 * Return: None
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Port_Hal_SetPinHigh(const Port_ModulePin *pModulePin);

/**********************************************************************************************************************
 * Function: Port_Hal_SetPinGroupHigh
 * Description: Set port pin group output high.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different PORT modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input: pModulePin: Pointer to port module and pin.
 *        pinMask: Selects the pins which should be modified, starting from pModulePin->pin.
 * Inout:  None
 * Output: None
 * Return: None
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Port_Hal_SetPinGroupHigh(const Port_ModulePin *pModulePin, uint16 pinMask);

/**********************************************************************************************************************
 * Function: Port_Hal_SetPinLow
 * Description: Set port pin output low.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input: pModulePin: Pointer to port module and pin.
 * Inout:  None
 * Output: None
 * Return: None
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Port_Hal_SetPinLow(const Port_ModulePin *pModulePin);

/**********************************************************************************************************************
 * Function: Port_Hal_SetPinGroupLow
 * Description: Set port pin group output low.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different PORT modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input: pModulePin: Pointer to port module and pin.
 *        pinMask: Selects the pins which should be modified, starting from pModulePin->pin.
 * Inout:  None
 * Output: None
 * Return: None
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Port_Hal_SetPinGroupLow(const Port_ModulePin *pModulePin, uint16 pinMask);

/**********************************************************************************************************************
 * Function: Port_Hal_SetPinToggle
 * Description: Set port pin output toggle.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different pins, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input: pModulePin: Pointer to port module and pin.
 * Inout:  None
 * Output: None
 * Return: None
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Port_Hal_SetPinToggle(const Port_ModulePin *pModulePin);

/**********************************************************************************************************************
 * Function: Port_Hal_SetPinGroupToggle
 * Description: Set port pin group output toggle.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different PORT modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input: pModulePin: Pointer to port module and pin.
 *        pinMask: Selects the pins which should be modified, starting from pModulePin->pin.
 * Inout:  None
 * Output: None
 * Return: None
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Port_Hal_SetPinGroupToggle(const Port_ModulePin *pModulePin, uint16 pinMask);

/******************************************************* PORT pin mode *******************************************************/
/**********************************************************************************************************************
 * Function: Port_Hal_SetPinPull
 * Description: Set port pin pull mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different pins, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input: pConfig: Pointer to port module pin and pull configuration.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Port_Hal_SetPinPull(const Port_PullConfig *pConfig);

/**********************************************************************************************************************
 * Function: Port_Hal_SetPinSlewRate
 * Description: Set port pin slew rate.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to port module pin and slew rate configuration.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Port_Hal_SetPinSlewRate(const Port_SlewRateConfig *pConfig);

/**********************************************************************************************************************
 * Function: Port_Hal_SetPinInputMode
 * Description: Set port pin input mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant 
 * Input: pConfig: Pointer to port module pin and input mode configuration.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Port_Hal_SetPinInputMode(const Port_InputModeConfig *pConfig);

/**********************************************************************************************************************
 * Function: Port_Hal_SetSttlState
 * Description: Select STTL standard as the input threshold.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different pins, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input: pConfig: Pointer to port module pin sttl configuration.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
#if defined(THA6_THA6412) || defined(THA6_THA6104)
LOCAL_FORCEINLINE boolean Port_Hal_SetSttlState(const Port_SttlStateConfig *pConfig);
#endif

/**********************************************************************************************************************
 * Function: Port_Hal_SetPinBackupReq
 * Description: Set port pin backup request.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input: pMoudlePin: Pointer to port module pin.
 * Inout:  None
 * Output: None
 * Return: None
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
#if defined(THA6_THA6412) || defined(THA6_THA6104)
LOCAL_FORCEINLINE void Port_Hal_SetPinBackupReq(const Port_ModulePin *pMoudlePin);
#endif

/**********************************************************************************************************************
 * Function: Port_Hal_SetPinBackupClr
 * Description: Clear Port pin back request status.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input: pMoudlePin: Pointer to port module pin.
 * Inout:  None
 * Output: None
 * Return: None
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
#if defined(THA6_THA6412) || defined(THA6_THA6104)
LOCAL_FORCEINLINE void Port_Hal_SetPinBackupClr(const Port_ModulePin *pMoudlePin);
#endif

/**********************************************************************************************************************
 * Function: Port_Hal_GetPinBackupSts
 * Description: Get port pin backup status.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input: pMoudlePin: Pointer to port module pin.
 * Inout:  None
 * Output: None
 * Return: Port_BackupState: Port pin backup status.
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
#if defined(THA6_THA6412) || defined(THA6_THA6104)
LOCAL_FORCEINLINE Port_BackupState Port_Hal_GetPinBackupSts(const Port_ModulePin *pMoudlePin);
#endif

/**********************************************************************************************************************
 * Function: Port_Hal_SetPinEmergency
 * Description: Set port pin emergrncy mode enable/disable.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to port module pin.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Port_Hal_SetPinEmergency(const Port_EmergencyConfig *pConfig);

/**********************************************************************************************************************
 * Function: Port_Hal_SetPinController
 * Description: Set port pin controller.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different pins, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input: pConfig: Pointer to port module pin and controller configuration.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Port_Hal_SetPinController(const Port_ControllerConfig *pConfig);

/**********************************************************************************************************************
 * Function: Port_Hal_SetPinAnalogDigitalMode
 * Description: Set port pin analog/digital mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to port module pin and analog/digital configuration.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Port_Hal_SetPinAnalogDigitalMode(const Port_AnalogDigitalConfig *pConfig);

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
/*************************************************** PORT pin input **************************************************/
LOCAL_FORCEINLINE Port_InputState Port_Hal_GetPinInputState(const Port_ModulePin *pModulePin)
{
    Port_InputState inputState;
    uint8 pin;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pModulePin));
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pModulePin->port));
#endif

    pin = (uint8)pModulePin->pin;

    /* Read port pin input state */
    if(0U != (pModulePin->port->IDR.U & ((uint32)1U << pin)))
    {
        inputState = PORT_INPUTSTATE_HIGH;
    }
    else
    {
        inputState = PORT_INPUTSTATE_LOW;
    }
    return inputState;
}

LOCAL_FORCEINLINE uint16 Port_Hal_GetPinGroupInputState(const Port_ModulePin *pModulePin, uint16 pinMask)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pModulePin));
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pModulePin->port));
#endif

    /* Read port pin group input state */
    return ((uint16)pModulePin->port->IDR.U & (pinMask << (uint16)pModulePin->pin));
}

/******************************************************* PORT pin output *******************************************************/
LOCAL_FORCEINLINE void Port_Hal_SetPinState(const Port_OutputStateConfig *pConfig)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pConfig->modulePin.port));
#endif

    /* Set port pin output state */
    pConfig->modulePin.port->BSRR.U = ((uint32)pConfig->outputState << (uint32)pConfig->modulePin.pin);
}

LOCAL_FORCEINLINE void Port_Hal_SetPinGroupState(const Port_OutputStateConfig *pConfig, uint16 pinMask)
{
    uint32 bsrr;
    uint8 pinCounter;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pConfig->modulePin.port));
#endif

    bsrr = 0;

    /* Set port pin group output state */
    for(pinCounter = (uint8)pConfig->modulePin.pin; pinCounter < PORT_PIN_LIMIT; pinCounter++)
    {
        if(0U != (pinMask & ((uint16)1U << pinCounter)))
        {
            bsrr |= ((uint32)pConfig->outputState << pinCounter);
        }
    }
    pConfig->modulePin.port->BSRR.U = bsrr;
}

LOCAL_FORCEINLINE void Port_Hal_SetPinHigh(const Port_ModulePin *pModulePin)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pModulePin));
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pModulePin->port));
#endif

    /* Set port pin output high */
    pModulePin->port->BSRR.U = ((uint32)PORT_OUTPUTSTATE_HIGH << (uint32)pModulePin->pin);
}

LOCAL_FORCEINLINE void Port_Hal_SetPinGroupHigh(const Port_ModulePin *pModulePin, uint16 pinMask)
{
    uint32 bsrr;
    uint8 pinCounter;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pModulePin));
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pModulePin->port));
#endif

    bsrr = 0;

    /* Set port pin group output high */
    for(pinCounter = (uint8)pModulePin->pin; pinCounter < PORT_PIN_LIMIT; pinCounter++)
    {
        if(0U != (pinMask & ((uint16)1U << pinCounter)))
        {
            bsrr |= ((uint32)PORT_OUTPUTSTATE_HIGH << pinCounter);
        }
    }
    pModulePin->port->BSRR.U = bsrr;
}

LOCAL_FORCEINLINE void Port_Hal_SetPinLow(const Port_ModulePin *pModulePin)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pModulePin));
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pModulePin->port));
#endif

    /* Set port pin output low */
    pModulePin->port->BSRR.U = ((uint32)PORT_OUTPUTSTATE_LOW << (uint32)pModulePin->pin);
}

LOCAL_FORCEINLINE void Port_Hal_SetPinGroupLow(const Port_ModulePin *pModulePin, uint16 pinMask)
{
    uint32 bsrr;
    uint8 pinCounter;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pModulePin));
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pModulePin->port));
#endif

    bsrr = 0;

    /* Set port pin group output low */
    for(pinCounter = (uint8)pModulePin->pin; pinCounter < PORT_PIN_LIMIT; pinCounter++)
    {
        if(0U != (pinMask & ((uint16)1U << pinCounter)))
        {
            bsrr |= ((uint32)PORT_OUTPUTSTATE_LOW << pinCounter);
        }
    }
    pModulePin->port->BSRR.U = bsrr;
}

LOCAL_FORCEINLINE void Port_Hal_SetPinToggle(const Port_ModulePin *pModulePin)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pModulePin));
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pModulePin->port));
#endif

    /* Set port pin output toggle */
    pModulePin->port->BSRR.U = ((uint32)PORT_OUTPUTSTATE_TOGGLE << (uint32)pModulePin->pin);
}

LOCAL_FORCEINLINE void Port_Hal_SetPinGroupToggle(const Port_ModulePin *pModulePin, uint16 pinMask)
{
    uint32 bsrr;
    uint8 pinCounter;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pModulePin));
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pModulePin->port));
#endif

    bsrr = 0;

    /* Set port pin group output toggle */
    for(pinCounter = (uint8)pModulePin->pin; pinCounter < PORT_PIN_LIMIT; pinCounter++)
    {
        if(0U != (pinMask & ((uint16)1U << pinCounter)))
        {
            bsrr |= ((uint32)PORT_OUTPUTSTATE_TOGGLE << (uint32)pinCounter);
        }
    }
    pModulePin->port->BSRR.U = bsrr;
}

/******************************************************* PORT pin mode *******************************************************/
LOCAL_FORCEINLINE boolean Port_Hal_SetPinPull(const Port_PullConfig *pConfig)
{
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pConfig->modulePin.port));
#endif

    ret = Port_Std_SetPinPullMode(pConfig->modulePin.port, pConfig->modulePin.pin, pConfig->pull);
    return ret;
}

/* #Violation: port_hal_h_REF_5 */
LOCAL_FORCEINLINE boolean Port_Hal_SetPinSlewRate(const Port_SlewRateConfig *pConfig)
{
    /* Value for configure DSRx */
    volatile PORT_DSR0 *pDsr; /* Pointer to DSR module */
    uint8 dsrIndex;
    uint8 dsrShift;
    boolean ret;
    uint32 dsr;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pConfig->modulePin.port));
#endif

    ret = TRUE;
    pDsr = &(pConfig->modulePin.port->DSR0);                  /* Point to DSR register */
    dsrIndex = ((uint8)pConfig->modulePin.pin >> PORT_SHIFT_3); /* Calculate DSR register offset */
    /* Calculate level bit field offset */
    dsrShift = ((((uint8)pConfig->modulePin.pin & PORT_MASK_BIT_LOW_3) << PORT_SHIFT_2) + PORT_DSR_SLEWRATE_OFFSET);

    /* #Violation: port_hal_h_REF_6 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit(); /* Unlock endinit protect */
    if(PORT_SLEWRATE_HIGH == pConfig->slewRate)
    {
        dsr = pDsr[dsrIndex].U | ((uint32)1U << dsrShift); /* Set high slew rate */
    }
    else
    {
        dsr = pDsr[dsrIndex].U & (~((uint32)1U << dsrShift)); /* Set low slew rate */
    }
    pDsr[dsrIndex].U = dsr;
    ret &= Cpuwdt_Hal_SetEndinit(); /* Lock endinit protect */
    /* #Violation: port_hal_h_REF_6 */
    ENABLE_ALL_INTERRUPTS();

    ret = Port_Register_ReadBack_Check(ret, dsr, pDsr[dsrIndex].U);
    return ret;
}

/* #Violation: port_hal_h_REF_5 */
LOCAL_FORCEINLINE boolean Port_Hal_SetPinInputMode(const Port_InputModeConfig *pConfig)
{
    volatile PORT_DSR0 *pDsr;
    uint32 dsr;
    uint32 dsrIndex;
    uint32 shift;
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pConfig->modulePin.port));
#endif

    ret = TRUE;
    dsrIndex = (uint32)pConfig->modulePin.pin >> PORT_SHIFT_3; /* Calculate DSR index */
    shift = ((((uint32)pConfig->modulePin.pin & PORT_MASK_BIT_LOW_3) << PORT_SHIFT_2) + PORT_DSR_INPUTMODE_OFFSET); /* Calculate input mode bit field shift */
    pDsr = &(pConfig->modulePin.port->DSR0); /* Point to DSR register */

    dsr = pDsr[dsrIndex].U;                         /* Read DSR register */
    dsr &= ~((uint32)PORT_MASK_BIT_LOW_1 << shift); /* Clear input mode bit field */
    dsr |= ((uint32)pConfig->mode << shift);        /* Write input mode to bit field */

    /* #Violation: port_hal_h_REF_6 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit(); /* Unlock endinit protect */
    pDsr[dsrIndex].U = dsr;    /* Write DSR register */
    ret &= Cpuwdt_Hal_SetEndinit();   /* Lock endinit protect */
    /* #Violation: port_hal_h_REF_6 */
    ENABLE_ALL_INTERRUPTS();

    ret = Port_Register_ReadBack_Check(ret, dsr, pDsr[dsrIndex].U);
    return ret;
}

#if defined(THA6_THA6412) || defined(THA6_THA6104)
LOCAL_FORCEINLINE boolean Port_Hal_SetSttlState(const Port_SttlStateConfig *pConfig)
{    
    uint32 sttl;
    boolean ret;

#if (INPUT_ARG_DETECT == STD_ON)
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pConfig->modulePin.port));
#endif

    ret = TRUE;
    sttl = pConfig->modulePin.port->STTL.U;
    sttl &= (~((uint32)1U << (uint32)pConfig->modulePin.pin));
    sttl |= ((uint32)pConfig->state << (uint32)pConfig->modulePin.pin);
    pConfig->modulePin.port->STTL.U = sttl;

    ret = Port_Register_ReadBack_Check(ret, sttl, pConfig->modulePin.port->STTL.U);
    return ret;
}
#endif

#if defined(THA6_THA6412) || defined(THA6_THA6104)
LOCAL_FORCEINLINE void Port_Hal_SetPinBackupReq(const Port_ModulePin *pMoudlePin)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pMoudlePin));
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pMoudlePin->port));
#endif
    pMoudlePin->port->BACKUPREQ.U = ((uint32)PORT_MASK_BIT_LOW_1 << (uint32)pMoudlePin->pin);
}
#endif

#if defined(THA6_THA6412) || defined(THA6_THA6104)
LOCAL_FORCEINLINE void Port_Hal_SetPinBackupClr(const Port_ModulePin *pMoudlePin)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pMoudlePin));
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pMoudlePin->port));
#endif
    pMoudlePin->port->BACKUPCLR.U = ((uint32)PORT_MASK_BIT_LOW_1 << (uint32)pMoudlePin->pin);
}
#endif

#if defined(THA6_THA6412) || defined(THA6_THA6104)
LOCAL_FORCEINLINE Port_BackupState Port_Hal_GetPinBackupSts(const Port_ModulePin *pMoudlePin)
{
    Port_BackupState backupSts;
    uint8 pin;
    
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pMoudlePin));
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pMoudlePin->port));
#endif

    pin = (uint8)pMoudlePin->pin;

    /* Read port pin backup state */
    if(0U != (pMoudlePin->port->BACKUPSTS.U & ((uint32)PORT_MASK_BIT_LOW_1 << (uint32)pin)))
    {
        backupSts = PORT_BACKUPSTS_ENABLE;
    }
    else
    {
        backupSts = PORT_BACKUPSTS_DISABLE;
    }
    return backupSts;
}
#endif

/* #Violation: port_hal_h_REF_5 */
LOCAL_FORCEINLINE boolean Port_Hal_SetPinEmergency(const Port_EmergencyConfig *pConfig)
{
    uint32 esr;
    uint32 shift;
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pConfig->modulePin.port));
#endif

    ret = TRUE;
    shift = ((uint32)pConfig->modulePin.pin << PORT_SHIFT_1);
    esr = pConfig->modulePin.port->ESR.U; /* Read ESR register */
    esr &= (~((uint32)PORT_MASK_BIT_LOW_2 << shift));
    esr |= ((uint32)pConfig->state << shift);

    /* #Violation: port_hal_h_REF_6 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();              /* Unlock endinit protect */
    pConfig->modulePin.port->ESR.U = esr; /* Write to ESR register */
    ret &= Cpuwdt_Hal_SetEndinit();                /* Lock endinit protect */
    /* #Violation: port_hal_h_REF_6 */
    ENABLE_ALL_INTERRUPTS();

    ret = Port_Register_ReadBack_Check(ret, esr, pConfig->modulePin.port->ESR.U);
    return ret;
}

LOCAL_FORCEINLINE boolean Port_Hal_SetPinController(const Port_ControllerConfig *pConfig)
{
    uint32 hwcr;
    uint32 shift;
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pConfig->modulePin.port));
#endif

    ret = TRUE;
    shift = ((uint32)pConfig->modulePin.pin << PORT_SHIFT_1);
    hwcr = pConfig->modulePin.port->HWCR.U; /* Read HWCR register */
    hwcr &= (~((uint32)PORT_MASK_BIT_LOW_2 << shift));
    hwcr |= ((uint32)pConfig->controller << shift);

    pConfig->modulePin.port->HWCR.U = hwcr;   /* Write to HWCR register */

    ret = Port_Register_ReadBack_Check(ret, hwcr, pConfig->modulePin.port->HWCR.U);
    return ret;
}

/* #Violation: port_hal_h_REF_5 */
LOCAL_FORCEINLINE boolean Port_Hal_SetPinAnalogDigitalMode(const Port_AnalogDigitalConfig *pConfig)
{
    uint32 shift;
    uint32 dfr;
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_h_REF_4 */
    Assert((boolean)(NULL_PTR != pConfig->modulePin.port));
#endif

    ret = TRUE;
    shift = (uint32)pConfig->modulePin.pin << PORT_SHIFT_1;
    dfr = (pConfig->modulePin.port->DFR.U & (~((uint32)PORT_MASK_BIT_LOW_2 << shift))) | ((uint32)pConfig->mode << shift);
    /* #Violation: port_hal_h_REF_6 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit(); /* Unlock endinit protect */
    pConfig->modulePin.port->DFR.U = dfr;
    ret &= Cpuwdt_Hal_SetEndinit(); /* Lock endinit protect */
    /* #Violation: port_hal_h_REF_6 */
    ENABLE_ALL_INTERRUPTS();

    ret = Port_Register_ReadBack_Check(ret, dfr, pConfig->modulePin.port->DFR.U);
    return ret;
}
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/*************************************************** PORT pin input **************************************************/
/**********************************************************************************************************************
 * Function: Port_Hal_SetPinInput
 * Description: Set port pin input mode with all input configuration.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to port module pin and all input configuration.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
extern boolean Port_Hal_SetPinInput(const Port_InputConfig *const pConfig);

/**********************************************************************************************************************
 * Function: Port_Hal_SetPinGroupInput
 * Description: Set port pin group input mode with all input configuration.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to port module pin and input configuration.
 *        pinMask: Selects the pins which should be modified, starting from pConfig->modulePin.pin.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 **********************************************************************************************************************/
extern boolean Port_Hal_SetPinGroupInput(const Port_InputConfig *const pConfig, uint16 pinMask);

/*************************************************** PORT pin output **************************************************/
/**********************************************************************************************************************
 * Function: Port_Hal_SetPinOutput
 * Description: Set port pin output mode with all output configuration.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to port module pin and output configuration.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
extern boolean Port_Hal_SetPinOutput(const Port_OutputConfig *const pConfig);

/**********************************************************************************************************************
 * Function: Port_Hal_SetPinGroupOutput
 * Description: Set port pin group output mode with all output configuration.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to port module pin and output configuration.
 *        pinMask: Selects the pins which should be modified, starting from pConfig->modulePin.pin.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
extern boolean Port_Hal_SetPinGroupOutput(const Port_OutputConfig *const pConfig, uint16 pinMask);

/*************************************************** PORT pin lvds ***************************************************/
/**********************************************************************************************************************
 * Function: Port_Hal_SetPinLvds
 * Description: Initializing and enable lvds function.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to lvds configuration.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
extern boolean Port_Hal_SetPinLvds(const Port_LvdsConfig *const pConfig);
#endif

/**********************************************************************************************************************
 * Function: Port_Hal_ResetPinLvds
 * Description: Disable lvds function.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pLvdsPins: Pointer to lvds configuration.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
extern boolean Port_Hal_ResetPinLvds(const Port_LvdsModulePin *const pLvdsPins);
#endif

/**********************************************************************************************************************
 * Function: Port_Hal_SetPinGroupPull
 * Description: Set port pin group pull mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different PORT modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input: pConfig: Pointer to port module pin and pull configuration.
 *        pinMask: Selects the pins which should be modified, starting from pConfig->pin.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
extern boolean Port_Hal_SetPinGroupPull(const Port_PullConfig *const pConfig, uint16 pinMask);

/**********************************************************************************************************************
 * Function: Port_Hal_SetPinGroupSlewRate
 * Description: Set port pin group slew rate.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to port module pin and slew rate configuration.
 *        pinMask: Selects the pins which should be modified, starting from pConfig->modulePin.pin.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
extern boolean Port_Hal_SetPinGroupSlewRate(const Port_SlewRateConfig *const pConfig, uint16 pinMask);

/**********************************************************************************************************************
 * Function: Port_Hal_SetPinGroupInputMode
 * Description: Set port pin group input mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to port module pin and input mode configuration.
 *        pinMask: Selects the pins which should be modified, starting from pConfig->modulePin.pin.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
extern boolean Port_Hal_SetPinGroupInputMode(const Port_InputModeConfig *const pConfig, uint16 pinMask);

/**********************************************************************************************************************
 * Function: Port_Hal_SetPinGroupEmergency
 * Description: Set port pin group emergrncy function enable/disable.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to port module pin and emergrncy function configuration.
 *        pinMask: Selects the pins which should be modified, starting from pConfig->modulePin.pin.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
extern boolean Port_Hal_SetPinGroupEmergency(const Port_EmergencyConfig *const pConfig, uint16 pinMask);

/**********************************************************************************************************************
 *                                          PORT Initializing Peripheral Pin
 *********************************************************************************************************************/
/******************************************************** ASI ********************************************************/
/**********************************************************************************************************************
 * Function: Port_Hal_SetAsiPins
 * Description: Initializing all pins for ASI.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to all ASI pins configuration.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/06/13   01077     create
 *********************************************************************************************************************/
extern boolean Port_Hal_SetAsiPins(const Port_AsiPinsConfig *const pConfig);

/******************************************************** CAN ********************************************************/
/**********************************************************************************************************************
 * Function: Port_Hal_SetCanPins
 * Description: Initializing all pins for CAN.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to all CAN pins configuration.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/06/13   01077     create
 *********************************************************************************************************************/
extern boolean Port_Hal_SetCanPins(const Port_CanPinsConfig *const pConfig);

/******************************************************* DSADC *******************************************************/
/**********************************************************************************************************************
 * Function: Port_Hal_SetDsadcTriggerPins
 * Description: Initializing trigger input pins for DSADC.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to DSADC trigger input pins configuration.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/07/21   01077     create
 *********************************************************************************************************************/
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
extern boolean Port_Hal_SetDsadcTriggerPins(const Port_DsadcTriggerInputConfig *const pConfig);
#endif

/******************************************************** ESPI *******************************************************/
/**********************************************************************************************************************
 * Function: Port_Hal_SetEspiMasterFullDuplexPins
 * Description: Initializing all pins for ESPI master full-duplex mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to all ESPI master full-duplex mode pins configuration.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/06/13   01077     create
 *********************************************************************************************************************/
extern boolean Port_Hal_SetEspiMasterFullDuplexPins(const Port_EspiMasterFullDuplexPinsConfig *const pConfig);

/**********************************************************************************************************************
 * Function: Port_Hal_SetEspiMasterHalfDuplexPins
 * Description: Initializing all pins for ESPI master half-duplex mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to all ESPI master half-duplex mode pins configuration.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/06/13   01077     create
 *********************************************************************************************************************/
extern boolean Port_Hal_SetEspiMasterHalfDuplexPins(const Port_EspiMasterHalfDuplexPinsConfig *const pConfig);

/**********************************************************************************************************************
 * Function: Port_Hal_SetEspiSlaveFullDuplexPins
 * Description: Initializing all pins for ESPI slave full-duplex mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to all ESPI slave full-duplex mode pins configuration.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/06/13   01077     create
 *********************************************************************************************************************/
extern boolean Port_Hal_SetEspiSlaveFullDuplexPins(const Port_EspiSlaveFullDuplexPinsConfig *const pConfig);

/**********************************************************************************************************************
 * Function: Port_Hal_SetEspiSlaveHalfDuplexPins
 * Description: Initializing all pins for ESPI slave half-duplex mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to all ESPI slave half-duplex mode pins configuration.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/06/13   01077     create
 *********************************************************************************************************************/
extern boolean Port_Hal_SetEspiSlaveHalfDuplexPins(const Port_EspiSlaveHalfDuplexPinsConfig *const pConfig);

/******************************************************** ETH ********************************************************/
/**********************************************************************************************************************
 * Function: Port_Hal_SetEthMiiPins
 * Description: Initializing all pins for ETH with MII mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to all ETH pins configuration with MII mode.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/06/13   01077     create
 *********************************************************************************************************************/
extern boolean Port_Hal_SetEthMiiPins(const Port_EthMiiPinsConfig *const pConfig);

/**********************************************************************************************************************
 * Function: Port_Hal_SetEthRgmiiPins
 * Description: Initializing all pins for ETH with RGMII mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to all ETH pins configuration with RGMII mode.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/06/13   01077     create
 *********************************************************************************************************************/
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
extern boolean Port_Hal_SetEthRgmiiPins(const Port_EthRgmiiPinsConfig *const pConfig);
#endif

/**********************************************************************************************************************
 * Function: Port_Hal_SetEthRmiiPins
 * Description: Initializing all pins for ETH with RMII mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to all ETH pins configuration with RMII mode.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/06/13   01077     create
 *********************************************************************************************************************/
extern boolean Port_Hal_SetEthRmiiPins(const Port_EthRmiiPinsConfig *const pConfig);

/******************************************************** I2C ********************************************************/
/**********************************************************************************************************************
 * Function: Port_Hal_SetI2cMasterPins
 * Description: Initializing all pins for I2C master mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to all I2C master mode pins configuration.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/06/13   01077     create
 *********************************************************************************************************************/
extern boolean Port_Hal_SetI2cMasterPins(const Port_I2cMasterPinsConfig *const pConfig);

/******************************************************** MSC ********************************************************/
/**********************************************************************************************************************
 * Function: Port_Hal_SetMscPins
 * Description: Initializing all pins for MSC.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to all MSC pins configuration.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/06/13   01077     create
 *********************************************************************************************************************/
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
extern boolean Port_Hal_SetMscPins(const Port_MscPinsConfig *const pConfig);
#endif

/******************************************************** SENT *******************************************************/
/**********************************************************************************************************************
 * Function: Port_Hal_SetSentNormalPins
 * Description: Initializing all pins for SENT normal mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to all SENT normal mode pins configuration.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/06/13   01077     create
 *********************************************************************************************************************/
extern boolean Port_Hal_SetSentNormalPins(const Port_SentNormalPinsConfig *const pConfig);

/**********************************************************************************************************************
 * Function: Port_Hal_SetSentSpcPins
 * Description: Initializing all pins for SENT spc mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to all SENT spc mode pins configuration.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/06/13   01077     create
 *********************************************************************************************************************/
extern boolean Port_Hal_SetSentSpcPins(const Port_SentSpcPinsConfig *const pConfig);

/**********************************************************************************************************************
 * Function   : Port_Hal_SetIomPins
 * Description: Initializing IOM pin.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to IOM pin configuration.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date          Author   Modified
 * 2023/10/27    01077    create
 *********************************************************************************************************************/
extern boolean Port_Hal_SetIomPins(const Port_IomInputConfig *const pConfig);

/**********************************************************************************************************************
 * Function   : Port_Hal_SetIomPinsInput
 * Description: Select source pin for IOM pin.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:  iomPin: IOM pad input pin to FPC.
 *         inputSel: Input source pin to IOM
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date          Author   Modified
 * 2025/02/17    01358    create
 *********************************************************************************************************************/
#if defined(THA6_THA6104)
extern boolean Port_Hal_SetIomPinsInput(Port_RxmuxIomPin iomPin, Port_RxmuxPinInputSel inputSel);
#endif

/**********************************************************************************************************************
 * Function   : Port_Hal_SetExtiPinsInput
 * Description: Select source pin for EXTI pin.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:  extiChannel: Exti channel.
 *         inputSel: Input source pin to Exti channel
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date          Author   Modified
 * 2025/02/17    01358    create
 *********************************************************************************************************************/
#if defined(THA6_THA6104)
extern boolean Port_Hal_SetExtiPinsInput(Port_RxmuxExtiChannel extiChannel, Port_RxmuxPinInputSel inputSel);
#endif

/**********************************************************************************************************************
 * Function: Port_Hal_SetPsi5Pins
 * Description: Initializing pins for PSI5.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to PSI5 configuration.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/06/13   01077     create
 *********************************************************************************************************************/
#if defined(THA6_THA6412)
extern boolean Port_Hal_SetPsi5Pins(const Port_Psi5PinsConfig *const pConfig);
#endif

#define PORT_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Port_MemMap.h"
/**********************************************************************************************************************
 *                                         Global LOCAL_FORCEINLINE Function Definitions
 *********************************************************************************************************************/

#endif /* PORT_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
