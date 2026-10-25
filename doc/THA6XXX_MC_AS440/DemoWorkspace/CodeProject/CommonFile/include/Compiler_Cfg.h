/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Compiler_Cfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Compiler
*
*   brief                 : This file contains sample code only. It is not part of the production
*                           code deliverables.
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/


/*
 * The following memory and pointer classes can be configured per module.
 * These #defines are passed to the compiler abstraction macros in Compiler.h
 *
 * Note:
 * module internal functions (statics) that get into one section
 * (together with API) shall fit into one page.
 */

#define REGSPACE                       /* Registers                           */

/***************************************************************************************************
*                               CAN Module Start
****************************************************************************************************/
#define CAN_PUBLIC_CODE                /* API functions                       */
#define CAN_PUBLIC_CONST               /* API constants                       */
#define CAN_PRIVATE_CODE               /* Internal functions                  */
#define CAN_PRIVATE_DATA               /* Module internal data                */
#define CAN_PRIVATE_CONST              /* Internal ROM Data                   */
#define CAN_CODE
#define CAN_CONST
#define CAN_APPL_DATA
#define CAN_APPL_CONST
#define CAN_APPL_CODE
#define CAN_CALLOUT_CODE
#define CAN_VAR_NOINIT
#define CAN_VAR_POWER_ON_INIT
#define CAN_VAR_FAST
#define CAN_VAR_LOW
#define CAN_VAR
#define CAN_INTERNAL_VAR
/***************************************************************************************************
*                               CAN Module Stop
****************************************************************************************************/


/***************************************************************************************************
*                               CANIF Module Start
****************************************************************************************************/
#define CANIF_CODE
#define CANIF_CONST
#define CANIF_APPL_DATA
#define CANIF_APPL_CONST
#define CANIF_APPL_CODE
#define CANIF_CALLOUT_CODE
#define CANIF_VAR_NOINIT
#define CANIF_VAR_POWER_ON_INIT
#define CANIF_VAR_FAST
#define CANIF_VAR_LOW
#define CANIF_VAR
#define CANIF_INTERNAL_VAR
/***************************************************************************************************
*                               CAN Module Stop
****************************************************************************************************/


/***************************************************************************************************
*                               SPI ointer classes.
****************************************************************************************************/
#define SPI_CODE
#define SPI_CONST
#define SPI_APPL_DATA
#define SPI_APPL_CONST
#define SPI_APPL_CODE
#define SPI_CALLOUT_CODE
#define SPI_VAR_NOINIT
#define SPI_VAR_POWER_ON_INIT
#define SPI_VAR_FAST
#define SPI_VAR

/***************************************************************************************************
*                               Det Module Start
****************************************************************************************************/
#define DET_CODE
#define DET_CONST
#define DET_APPL_DATA
#define DET_APPL_CONST
#define DET_APPL_CODE
#define DET_CALLOUT_CODE
#define DET_VAR_NOINIT
#define DET_VAR_POWER_ON_INIT
#define DET_VAR_FAST
#define DET_VAR
/***************************************************************************************************
*                               Det Module Stop
****************************************************************************************************/


/***************************************************************************************************
*                               Mcu Module Start
****************************************************************************************************/

/*Code*/
#define MCU_CODE
#define MCU_CODE_5MS /*PERIOD is the typical period time value and unit of the ExecutableEntitys in this MemorySection. */
/*   #define MCU_CallOut_CODE To be used for callout code.<CN> is the callback name (including module reference) written in uppercase letters*/
#define MCU_CODE_FAST /*To be used for code that shall go into fast code memory segments*/
#define MCU_CODE_SLOW /*To be used for code that shall go into slow code memory segments*/

/*Constants*/
#define  MCU_CONST /* To be used for global or static constants. */
#define  MCU_CALIB /* To be used for calibration constants */
#define  MCU_CONFIG_DATA /*To be used for module configuration constants*/
#define  MCU_CONST_SAVED_RECOVERY_ZONE0 /*To be used for ROM buffers of variables saved in non-volatile memory.*/
#define  MCU_CONST_SAVED_RECOVERY_ZONE1

/*Pointer*/
#define  MCU_APPL_DATA/* To be used for references on application data */
#define  MCU_APPL_CONST/*To be used for references on application constants*/
#define  MCU_CallOut_CODE/*To be used for references on application functions. (e.g. call back function pointers*/
#define  REGSPACE/*To be used for pointers to registers*/

/*Variables*/
#define  MCU_VAR_NO_INIT /*Used for variables that are never cleared and never initialized.*/
#define  MCU_VAR_CLEARED /*Used for variables that are cleared to zero after every reset*/
#define  MCU_VAR_POWER_ON_CLEARED /*Used for variables that are cleared to zero only after power on reset.*/
#define  MCU_VAR_INIT /*Used for variables that are initialized with values after every reset*/
#define  MCU_VAR_POWER_ON_INIT /*Used for variables that are initialized with values only after power on reset.*/

#define  MCU_VAR_FAST_NO_INIT /*Used for variables that are never cleared and never initialized.*/
#define  MCU_VAR_FAST_CLEARED /*Used for variables that are cleared to zero after every reset*/
#define  MCU_VAR_FAST_POWER_ON_CLEARED /*Used for variables that are cleared to zero only after power on reset.*/
#define  MCU_VAR_FAST_INIT /*Used for variables that are initialized with values after every reset*/
#define  MCU_VAR_FAST_POWER_ON_INIT /*Used for variables that are initialized with values only after power on reset.*/

#define  MCU_VAR_SLOW_NO_INIT /*Used for variables that are never cleared and never initialized.*/
#define  MCU_VAR_SLOW_CLEARED /*Used for variables that are cleared to zero after every reset*/
#define  MCU_VAR_SLOW_POWER_ON_CLEARED /*Used for variables that are cleared to zero only after power on reset.*/
#define  MCU_VAR_SLOW_INIT /*Used for variables that are initialized with values after every reset*/
#define  MCU_VAR_SLOW_POWER_ON_INIT /*Used for variables that are initialized with values only after power on reset.*/

/*To be used for global or static variables which are accessible from a calibration tool.*/
#define  MCU_INTERNAL_VAR_NO_INIT /*Used for variables that are never cleared and never initialized.*/
#define  MCU_INTERNAL_VAR_CLEARED /*Used for variables that are cleared to zero after every reset*/
#define  MCU_INTERNAL_VAR_POWER_ON_CLEARED /*Used for variables that are cleared to zero only after power on reset.*/
#define  MCU_INTERNAL_VAR_INIT /*Used for variables that are initialized with values after every reset*/
#define  MCU_INTERNAL_VAR_POWER_ON_INIT /*Used for variables that are initialized with values only after power on reset.*/

#define  MCU_VAR_SAVED_ZONE0 /*To be used for RAM buffers of variables saved on non-volatile memory*/
#define  MCU_VAR_SAVED_ZONE1
                                /* which are initialized by driver     */

/***************************************************************************************************
*                               Mcu Module Stop
****************************************************************************************************/

/***************************************************************************************************
*                               Gpt Module Start
****************************************************************************************************/

#define GPT_PUBLIC_CODE                /* API functions                       */
#define GPT_PUBLIC_CONST               /* API constants                       */

#define GPT_PRIVATE_CODE               /* Internal functions                  */

#define GPT_PRIVATE_DATA               /* Module internal data                */
#define GPT_PRIVATE_CONST              /* Internal ROM Data                   */

#define GPT_APPL_CODE                  /* callbacks of the Application        */
#define GPT_APPL_CONST                 /* Applications' ROM Data              */
#define GPT_APPL_DATA                  /* Applications' RAM Data              */
#define GPT_FAST_DATA                  /* 'Near' RAM Data                     */

#define GPT_FAST_CODE                   /* API functions                      */
#define GPT_FAST_CONST                  /* API constants                      */

#define GPT_CONFIG_CONST               /* Desc. Tables -> Config-dependent    */
#define GPT_CONFIG_DATA                /* Config. dependent (reg. size) data  */

#define GPT_INIT_DATA                  /* Data which is initialized during
                                          Startup                             */
#define GPT_NOINIT_DATA                /* Data which is not initialized during
                                          Startup                             */
#define GPT_CONST                      /* Data Constants                      */
#define GPT_VAR                        /* Memory class for global variables   */
                                       /* which are initialized after every   */
                                       /* reset                               */
#define GPT_VAR_NOINIT                 /* Memory class for global variables   */
                                       /* which are initialized by driver     */

/***************************************************************************************************
*                               Gpt Module Stop
****************************************************************************************************/

/***************************************************************************************************
*                               Ocu Module Start
****************************************************************************************************/

#define OCU_PUBLIC_CODE                /* API functions                       */
#define OCU_PUBLIC_CONST               /* API constants                       */

#define OCU_PRIVATE_CODE               /* Internal functions                  */

#define OCU_PRIVATE_DATA               /* Module internal data                */
#define OCU_PRIVATE_CONST              /* Internal ROM Data                   */

#define OCU_APPL_CODE                  /* callbacks of the Application        */
#define OCU_APPL_CONST                 /* Applications' ROM Data              */
#define OCU_APPL_DATA                  /* Applications' RAM Data              */
#define OCU_FAST_DATA                  /* 'Near' RAM Data                     */

#define OCU_FAST_CODE                   /* API functions                      */
#define OCU_FAST_CONST                  /* API constants                      */

#define OCU_CONFIG_CONST               /* Desc. Tables -> Config-dependent    */
#define OCU_CONFIG_DATA                /* Config. dependent (reg. size) data  */

#define OCU_INIT_DATA                  /* Data which is initialized during
                                          Startup                             */
#define OCU_NOINIT_DATA                /* Data which is not initialized during
                                          Startup                             */
#define OCU_CONST                      /* Data Constants                      */
#define OCU_VAR                        /* Memory class for global variables   */
                                       /* which are initialized after every   */
                                       /* reset                               */
#define OCU_VAR_NOINIT                 /* Memory class for global variables   */
                                       /* which are initialized by driver     */
/*Code*/
#define OCU_CODE
/***************************************************************************************************
*                               Ocu Module Stop
****************************************************************************************************/

/***************************************************************************************************
*                               Wdg Module Start
****************************************************************************************************/

#define WDG_PUBLIC_CODE        /* API functions                    */
#define WDG_PUBLIC_CONST       /* API constants                    */

#define WDG_PRIVATE_CODE       /* Internal functions               */

#define WDG_PRIVATE_DATA       /* Module internal data             */
#define WDG_PRIVATE_CONST      /* Internal ROM Data                */

#define WDG_APPL_CODE          /* callbacks of the Application     */
#define WDG_APPL_CONST         /* Applications' ROM Data           */
#define WDG_APPL_DATA          /* Applications' RAM Data           */
#define WDG_FAST_DATA          /* 'Near' RAM Data                  */

#define WDG_FAST_CODE           /* API functions                   */
#define WDG_FAST_CONST          /* API constants                   */

#define WDG_CONFIG_CONST       /* Desc. Tables -> Config-dependent */
#define WDG_CONFIG_DATA        /* Config. dependent (reg. size)
                                             data                             */

#define WDG_INIT_DATA          /* Data which is initialized during
                                             Startup                          */
#define WDG_NOINIT_DATA        /* Data which is not initialized
                                             during Startup                   */
#define WDG_CONST              /* Data Constants                   */
#define WDG_VAR             /* Memory class for global variables   */
                                       /* which are initialized after every   */
                                       /* reset                               */
#define WDG_VAR_NOINIT      /* Memory class for global variables   */
                                       /* which are initialized by driver     */

/***************************************************************************************************
*                               Wdg Module Stop
****************************************************************************************************/

/***************************************************************************************************
*                               Port Module Start
****************************************************************************************************/

#define PORT_PUBLIC_CODE                /* API functions                      */
#define PORT_PUBLIC_CONST               /* API constants                      */

#define PORT_PRIVATE_CODE               /* Internal functions                 */

#define PORT_PRIVATE_DATA               /* Module internal data               */
#define PORT_PRIVATE_CONST              /* Internal ROM Data                  */

#define PORT_APPL_CODE                  /* callbacks of the Application       */
#define PORT_APPL_CONST                 /* Applications' ROM Data             */
#define PORT_APPL_DATA                  /* Applications' RAM Data             */
#define PORT_FAST_DATA                  /* 'Near' RAM Data                    */

#define PORT_FAST_CODE                   /* API functions                     */
#define PORT_FAST_CONST                  /* API constants                     */

#define PORT_CONFIG_CONST               /* Desc. Tables -> Config-dependent   */
#define PORT_CONFIG_DATA                /* Config. dependent (reg. size) data */

#define PORT_INIT_DATA                  /* Data which is initialized during
                                           Startup                            */
#define PORT_NOINIT_DATA                /* Data which is not initialized during
                                           Startup                            */
#define PORT_CONST                      /* Data Constants                     */
#define PORT_VAR                        /* Memory class for global variables  */
                                        /* which are initialized after every  */
                                        /* reset                              */
#define PORT_VAR_NOINIT                 /* Memory class for global variables  */
                                        /* which are initialized by driver    */

/***************************************************************************************************
*                               Port Module Stop
****************************************************************************************************/

/***************************************************************************************************
*                               Dio Module Start
****************************************************************************************************/

#define DIO_PUBLIC_CODE                /* API functions                       */
#define DIO_PUBLIC_CONST               /* API constants                       */

#define DIO_PRIVATE_CODE               /* Internal functions                  */

#define DIO_PRIVATE_DATA               /* Module internal data                */
#define DIO_PRIVATE_CONST              /* Internal ROM Data                   */

#define DIO_APPL_CODE                  /* callbacks of the Application        */
#define DIO_APPL_CONST                 /* Applications' ROM Data              */
#define DIO_APPL_DATA                  /* Applications' RAM Data              */
#define DIO_FAST_DATA                  /* 'Near' RAM Data                     */

#define DIO_FAST_CODE                   /* API functions                      */
#define DIO_FAST_CONST                  /* API constants                      */

#define DIO_CONFIG_CONST               /* Desc. Tables -> Config-dependent    */
#define DIO_CONFIG_DATA                /* Config. dependent (reg. size) data  */

#define DIO_INIT_DATA                  /* Data which is initialized during
                                          Startup                             */
#define DIO_NOINIT_DATA                /* Data which is not initialized during
                                          Startup                             */
#define DIO_CONST                      /* Data Constants                      */
#define DIO_VAR                        /* Memory class for global variables   */
                                       /* which are initialized after every   */
                                       /* reset                               */
#define DIO_VAR_NOINIT                 /* Memory class for global variables   */
                                       /* which are initialized by driver     */

/***************************************************************************************************
*                               Dio Module Stop
****************************************************************************************************/

/***************************************************************************************************
*                               Pwm Module Start
****************************************************************************************************/

#define PWM_PUBLIC_CODE                /* API functions                       */
#define PWM_PUBLIC_CONST               /* API constants                       */

#define PWM_PRIVATE_CODE               /* Internal functions                  */

#define PWM_PRIVATE_DATA               /* Module internal data                */
#define PWM_PRIVATE_CONST              /* Internal ROM Data                   */

#define PWM_APPL_CODE                  /* callbacks of the Application        */
#define PWM_APPL_CONST                 /* Applications' ROM Data              */
#define PWM_APPL_DATA                  /* Applications' RAM Data              */
#define PWM_FAST_DATA                  /* 'Near' RAM Data                     */

#define PWM_FAST_CODE                   /* API functions                      */
#define PWM_FAST_CONST                  /* API constants                      */

#define PWM_CONFIG_CONST               /* Desc. Tables -> Config-dependent    */
#define PWM_CONFIG_DATA                /* Config. dependent (reg. size) data  */

#define PWM_INIT_DATA                  /* Data which is initialized during
                                          Startup                             */
#define PWM_NOINIT_DATA                /* Data which is not initialized during
                                          Startup                             */
#define PWM_CONST                      /* Data Constants                      */
#define PWM_VAR                        /* Memory class for global variables   */
                                       /* which are initialized after every   */
                                       /* reset                               */
#define PWM_VAR_NOINIT                 /* Memory class for global variables   */
                                       /* which are initialized by driver     */

/***************************************************************************************************
*                               Pwm Module Stop
****************************************************************************************************/

/***************************************************************************************************
*                               Spi Module Start
****************************************************************************************************/

#define SPI_PUBLIC_CODE                /* API functions                       */
#define SPI_PUBLIC_CONST               /* API constants                       */

#define SPI_PRIVATE_CODE               /* Internal functions                  */

#define SPI_PRIVATE_DATA               /* Module internal data                */
#define SPI_PRIVATE_CONST              /* Internal ROM Data                   */

#define SPI_APPL_CODE                  /* callbacks of the Application        */
#define SPI_APPL_CONST                 /* Applications' ROM Data              */
#define SPI_APPL_DATA                  /* Applications' RAM Data              */
#define SPI_FAST_DATA                  /* 'Near' RAM Data                     */

#define SPI_FAST_CODE                   /* API functions                      */
#define SPI_FAST_CONST                  /* API constants                      */

#define SPI_CONFIG_CONST               /* Desc. Tables -> Config-dependent    */
#define SPI_CONFIG_DATA                /* Config. dependent (reg. size) data  */

#define SPI_INIT_DATA                  /* Data which is initialized during
                                          Startup                             */
#define SPI_NOINIT_DATA                /* Data which is not initialized during
                                          Startup                             */
#define SPI_CONST                      /* Data Constants                      */
#define SPI_VAR                        /* Memory class for global variables   */
                                       /* which are initialized after every   */
                                       /* reset                               */
#define SPI_VAR_NOINIT                 /* Memory class for global variables   */
                                       /* which are initialized by driver     */

/***************************************************************************************************
*                               Spi Module Stop
****************************************************************************************************/

/***************************************************************************************************
*                               Adc Module Start
****************************************************************************************************/

#define ADC_PUBLIC_CODE                /* API functions                       */
#define ADC_PUBLIC_CONST               /* API constants                       */

#define ADC_PRIVATE_CODE               /* Internal functions                  */

#define ADC_PRIVATE_DATA               /* Module internal data                */
#define ADC_PRIVATE_CONST              /* Internal ROM Data                   */

#define ADC_APPL_CODE                  /* callbacks of the Application        */
#define ADC_APPL_CONST                 /* Applications' ROM Data              */
#define ADC_APPL_DATA                  /* Applications' RAM Data              */
#define ADC_FAST_DATA                  /* 'Near' RAM Data                     */

#define ADC_FAST_CODE                   /* API functions                      */
#define ADC_FAST_CONST                  /* API constants                      */

#define ADC_CONFIG_CONST               /* Desc. Tables -> Config-dependent    */
#define ADC_CONFIG_DATA                /* Config. dependent (reg. size) data  */

#define ADC_INIT_DATA                  /* Data which is initialized during
                                          Startup                             */
#define ADC_NOINIT_DATA                /* Data which is not initialized during
                                          Startup                             */
#define ADC_CONST                      /* Data Constants                      */
#define ADC_VAR                        /* Memory class for global variables   */
                                       /* which are initialized after every   */
                                       /* reset                               */
#define ADC_VAR_NOINIT                 /* Memory class for global variables   */
                                       /* which are initialized by driver     */

/***************************************************************************************************
*                               Adc Module Stop
****************************************************************************************************/

/***************************************************************************************************
*                               Icu Module Start
****************************************************************************************************/

/*Code*/
#define ICU_CODE
#define ICU_CODE_5MS /*PERIOD is the typical period time value and unit of the ExecutableEntitys in this MemorySection. */
#define ICU_CODE_FAST /*To be used for code that shall go into fast code memory segments*/
#define ICU_CODE_SLOW /*To be used for code that shall go into slow code memory segments*/

/*Constants*/
#define  ICU_CONST /* To be used for global or static constants. */
#define  ICU_CALIB /* To be used for calibration constants */
#define  ICU_CONFIG_DATA /*To be used for module configuration constants*/
#define  ICU_CONST_SAVED_RECOVERY_ZONE0 /*To be used for ROM buffers of variables saved in non-volatile memory.*/
#define  ICU_CONST_SAVED_RECOVERY_ZONE1

/*Pointer*/
#define  ICU_APPL_DATA/* To be used for references on application data */
#define  ICU_APPL_CONST/*To be used for references on application constants*/
#define  ICU_CallOut_CODE/*To be used for references on application functions. (e.g. call back function pointers*/
#define  REGSPACE/*To be used for pointers to registers*/

/*Variables*/
#define  ICU_VAR_NO_INIT /*Used for variables that are never cleared and never initialized.*/
#define  ICU_VAR_CLEARED /*Used for variables that are cleared to zero after every reset*/
#define  ICU_VAR_POWER_ON_CLEARED /*Used for variables that are cleared to zero only after power on reset.*/
#define  ICU_VAR_INIT /*Used for variables that are initialized with values after every reset*/
#define  ICU_VAR_POWER_ON_INIT /*Used for variables that are initialized with values only after power on reset.*/

#define  ICU_VAR_FAST_NO_INIT /*Used for variables that are never cleared and never initialized.*/
#define  ICU_VAR_FAST_CLEARED /*Used for variables that are cleared to zero after every reset*/
#define  ICU_VAR_FAST_POWER_ON_CLEARED /*Used for variables that are cleared to zero only after power on reset.*/
#define  ICU_VAR_FAST_INIT /*Used for variables that are initialized with values after every reset*/
#define  ICU_VAR_FAST_POWER_ON_INIT /*Used for variables that are initialized with values only after power on reset.*/

#define  ICU_VAR_SLOW_NO_INIT /*Used for variables that are never cleared and never initialized.*/
#define  ICU_VAR_SLOW_CLEARED /*Used for variables that are cleared to zero after every reset*/
#define  ICU_VAR_SLOW_POWER_ON_CLEARED /*Used for variables that are cleared to zero only after power on reset.*/
#define  ICU_VAR_SLOW_INIT /*Used for variables that are initialized with values after every reset*/
#define  ICU_VAR_SLOW_POWER_ON_INIT /*Used for variables that are initialized with values only after power on reset.*/

/*To be used for global or static variables which are accessible from a calibration tool.*/
#define  ICU_INTERNAL_VAR_NO_INIT /*Used for variables that are never cleared and never initialized.*/
#define  ICU_INTERNAL_VAR_CLEARED /*Used for variables that are cleared to zero after every reset*/
#define  ICU_INTERNAL_VAR_POWER_ON_CLEARED /*Used for variables that are cleared to zero only after power on reset.*/
#define  ICU_INTERNAL_VAR_INIT /*Used for variables that are initialized with values after every reset*/
#define  ICU_INTERNAL_VAR_POWER_ON_INIT /*Used for variables that are initialized with values only after power on reset.*/

#define  ICU_VAR_SAVED_ZONE0 /*To be used for RAM buffers of variables saved on non-volatile memory*/
#define  ICU_VAR_SAVED_ZONE1

/***************************************************************************************************
*                               Icu Module Stop
****************************************************************************************************/

/***************************************************************************************************
*                               Lin Module Start
****************************************************************************************************/

#define LIN_PUBLIC_CODE                /* API functions                       */
#define LIN_PUBLIC_CONST               /* API constants                       */

#define LIN_PRIVATE_CODE               /* Internal functions                  */

#define LIN_PRIVATE_DATA               /* Module internal data                */
#define LIN_PRIVATE_CONST              /* Internal ROM Data                   */

#define LIN_APPL_CODE                  /* callbacks of the Application        */
#define LIN_APPL_CONST                 /* Applications' ROM Data              */
#define LIN_APPL_DATA                  /* Applications' RAM Data              */
#define LIN_FAST_DATA                  /* 'Near' RAM Data                     */

#define LIN_FAST_CODE                   /* API functions                      */
#define LIN_FAST_CONST                  /* API constants                      */

#define LIN_CONFIG_CONST               /* Desc. Tables -> Config-dependent    */
#define LIN_CONFIG_DATA                /* Config. dependent (reg. size) data  */

#define LIN_INIT_DATA                  /* Data which is initialized during
                                          Startup                             */
#define LIN_NOINIT_DATA                /* Data which is not initialized during
                                          Startup                             */
#define LIN_CONST                      /* Data Constants                      */
#define LIN_VAR                        /* Memory class for global variables   */
                                       /* which are initialized after every   */
                                       /* reset                               */
#define LIN_VAR_NOINIT                 /* Memory class for global variables   */
                                       /* which are initialized by driver     */

/***************************************************************************************************
*                               Lin Module Stop
****************************************************************************************************/

/***************************************************************************************************
*                               Uart Module Start
****************************************************************************************************/

#define UART_PUBLIC_CODE                /* API functions                       */
#define UART_PUBLIC_CONST               /* API constants                       */

#define UART_PRIVATE_CODE               /* Internal functions                  */

#define UART_PRIVATE_DATA               /* Module internal data                */
#define UART_PRIVATE_CONST              /* Internal ROM Data                   */

#define UART_APPL_CODE                  /* callbacks of the Application        */
#define UART_APPL_CONST                 /* Applications' ROM Data              */
#define UART_APPL_DATA                  /* Applications' RAM Data              */
#define UART_FAST_DATA                  /* 'Near' RAM Data                     */

#define UART_FAST_CODE                   /* API functions                      */
#define UART_FAST_CONST                  /* API constants                      */

#define UART_CONFIG_CONST               /* Desc. Tables -> Config-dependent    */
#define UART_CONFIG_DATA                /* Config. dependent (reg. size) data  */

#define UART_INIT_DATA                  /* Data which is initialized during
                                          Startup                             */
#define UART_NOINIT_DATA                /* Data which is not initialized during
                                          Startup                             */
#define UART_CONST                      /* Data Constants                      */
#define UART_VAR                        /* Memory class for global variables   */
                                       /* which are initialized after every   */
                                       /* reset                               */
#define UART_VAR_NOINIT                 /* Memory class for global variables   */
                                       /* which are initialized by driver     */

/***************************************************************************************************
*                               Uart Module Stop
****************************************************************************************************/

/***************************************************************************************************
*                               Fls Module Start
****************************************************************************************************/

#define FLS_PUBLIC_CODE                /* API functions                       */
#define FLS_PUBLIC_CONST               /* API constants                       */

#define FLS_PRIVATE_CODE               /* Internal functions                  */

#define FLS_PRIVATE_DATA               /* Module internal data                */
#define FLS_PRIVATE_CONST              /* Internal ROM Data                   */

#define FLS_APPL_CODE                  /* callbacks of the Application        */
#define FLS_APPL_CONST                 /* Applications' ROM Data              */
#define FLS_APPL_DATA                  /* Applications' RAM Data              */
#define FLS_FAST_DATA                  /* 'Near' RAM Data                     */

#define FLS_FAST_CODE                   /* API functions                      */
#define FLS_FAST_CONST                  /* API constants                      */

#define FLS_CONFIG_CONST               /* Desc. Tables -> Config-dependent    */
#define FLS_CONFIG_DATA                /* Config. dependent (reg. size) data  */

#define FLS_INIT_DATA                  /* Data which is initialized during
                                          Startup                             */
#define FLS_NOINIT_DATA                /* Data which is not initialized during
                                          Startup                             */
#define FLS_CONST                      /* Data Constants                      */
#define FLS_VAR                        /* Memory class for global variables   */
                                       /* which are initialized after every   */
                                       /* reset                               */
#define FLS_VAR_NOINIT                 /* Memory class for global variables   */
                                       /* which are initialized by driver     */

/***************************************************************************************************
*                               Fls Module Stop
****************************************************************************************************/

/***************************************************************************************************
*                               Dee Module Start
****************************************************************************************************/

#define FEE_PUBLIC_CODE                /* API functions                       */
#define FEE_PUBLIC_CONST               /* API constants                       */

#define FEE_PRIVATE_CODE               /* Internal functions                  */

#define FEE_PRIVATE_DATA               /* Module internal data                */
#define FEE_PRIVATE_CONST              /* Internal ROM Data                   */

#define FEE_APPL_CODE                  /* callbacks of the Application        */
#define FEE_APPL_CONST                 /* Applications' ROM Data              */
#define FEE_APPL_DATA                  /* Applications' RAM Data              */
#define FEE_FAST_DATA                  /* 'Near' RAM Data                     */

#define FEE_FAST_CODE                   /* API functions                      */
#define FEE_FAST_CONST                  /* API constants                      */

#define FEE_CONFIG_CONST               /* Desc. Tables -> Config-dependent    */
#define FEE_CONFIG_DATA                /* Config. dependent (reg. size) data  */

#define FEE_INIT_DATA                  /* Data which is initialized during
                                          Startup                             */
#define FEE_NOINIT_DATA                /* Data which is not initialized during
                                          Startup                             */
#define FEE_CONST                      /* Data Constants                      */
#define FEE_VAR                        /* Memory class for global variables   */
                                       /* which are initialized after every   */
                                       /* reset                               */
#define FEE_VAR_NOINIT                 /* Memory class for global variables   */
                                       /* which are initialized by driver     */

/***************************************************************************************************
*                               Fee Module Stop
****************************************************************************************************/

/***************************************************************************************************
*                               Flstst Module Start
****************************************************************************************************/

#define FLSTST_PUBLIC_CODE             /* API functions                       */
#define FLSTST_PUBLIC_CONST            /* API constants                       */

#define FLSTST_APPL_CODE               /* callbacks of the Application        */
#define FLSTST_APPL_CONST              /* Applications' ROM Data              */
#define FLSTST_APPL_DATA               /* Applications' RAM Data              */
#define FLSTST_FAST_DATA               /* 'Near' RAM Data                     */

#define FLSTST_CONFIG_CONST           /* Desc. Tables -> Config-dependen      */
#define FLSTST_CONFIG_DATA            /* Config. dependent (reg. size) data   */

#define FLSTST_INIT_DATA              /* Data which is initialized during     */
                                      /*Startup                               */
#define FLSTST_NOINIT_DATA            /* Data which is not initialized during */
                                      /*Startup                               */
#define FLSTST_CONST                  /* Data Constants                       */

/***************************************************************************************************
*                               Flstst Module Stop
****************************************************************************************************/

/***************************************************************************************************
*                               Cortst Module Start
****************************************************************************************************/

#define CORTST_PUBLIC_CODE             /* API functions                       */

#define CORTST_APPL_CODE               /* callbacks of the Application        */
#define CORTST_APPL_DATA               /* Applications' RAM Data              */

#define CORTST_CONFIG_CONST            /* Desc. Tables -> Config-dependent    */
#define CORTST_CONFIG_DATA             /* Config. dependent (reg. size) data  */

#define CORTST_INIT_DATA               /* Data which is initialized during    */
                                       /* Startup                             */
#define CORTST_NOINIT_DATA             /* Data which is not initialized during*/
                                       /* Startup                             */
#define CORTST_CONST                   /* Data Constants                      */

/***************************************************************************************************
*                               Cortst Module Stop
****************************************************************************************************/

/***************************************************************************************************
*                               Ram Module Start
****************************************************************************************************/

#define RAMTST_PUBLIC_CODE                /* API functions                    */
#define RAMTST_PUBLIC_CONST               /* API constants                    */

#define RAMTST_PRIVATE_CODE               /* Internal functions               */

#define RAMTST_PRIVATE_DATA               /* Module internal data             */
#define RAMTST_PRIVATE_CONST              /* Internal ROM Data                */

#define RAMTST_APPL_CODE                  /* callbacks of the Application     */
#define RAMTST_APPL_CONST                 /* Applications' ROM Data           */
#define RAMTST_APPL_DATA                  /* Applications' RAM Data           */
#define RAMTST_FAST_DATA                  /* 'Near' RAM Data                  */


#define RAMTST_CONFIG_CONST               /* Desc. Tables -> Config-dependent */
#define RAMTST_CONFIG_DATA                /* Config. dependent (reg. size)
                                                                        data  */

#define RAMTST_INIT_DATA                  /* Data which is initialized during
                                          Startup                             */
#define RAMTST_NOINIT_DATA                /* Data which is not initialized
                                          during Startup                      */
#define RAMTST_CONST                      /* Data Constants                   */

#define RAMTST_CODE

/***************************************************************************************************
*                               Ram Module Stop
****************************************************************************************************/

/***************************************************************************************************
*                               Eth Module Start
****************************************************************************************************/
#define ETH_CODE                /* code                    */
#define ETH_PUBLIC_CODE                /* API functions                    */
#define ETH_PUBLIC_CONST               /* API constants                    */

#define ETH_PRIVATE_CODE               /* Internal functions               */

#define ETH_PRIVATE_DATA               /* Module internal data             */
#define ETH_PRIVATE_CONST              /* Internal ROM Data                */

#define ETH_APPL_CODE                  /* callbacks of the Application     */
#define ETH_APPL_CONST                 /* Applications' ROM Data           */
#define ETH_APPL_DATA                  /* Applications' RAM Data           */
#define ETH_FAST_DATA                  /* 'Near' RAM Data                  */

#define ETH_FAST_CODE                   /* API functions                   */
#define ETH_FAST_CONST                  /* API constants                   */

#define ETH_CONFIG_CONST              /* Desc. Tables -> Config-dependent  */
#define ETH_CONFIG_DATA               /* Config. dependent (reg. size) data*/

#define ETH_INIT_DATA                 /* Data which is initialized during
                                         Startup                              */
#define ETH_NOINIT_DATA               /* Data which is not initialized during
                                         Startup                              */
#define ETH_CONST                     /* Data Constants                    */
#define ETH_VAR                       /* Memory class for global variables */
                                       /* which are initialized after every   */
                                       /* reset                               */
#define ETH_VAR_NOINIT                 /* Memory class for global variables*/
                                       /* which are initialized by driver     */

/***************************************************************************************************
*                               Eth Module Stop
****************************************************************************************************/

/***************************************************************************************************
*                               Intc Module Start
****************************************************************************************************/
#define INTC_PUBLIC_CODE                /* API functions                    */
#define INTC_PUBLIC_CONST               /* API constants                    */

#define INTC_PRIVATE_CODE               /* Internal functions               */

#define INTC_PRIVATE_DATA               /* Module internal data             */
#define INTC_PRIVATE_CONST              /* Internal ROM Data                */

#define INTC_APPL_CODE                  /* callbacks of the Application     */
#define INTC_APPL_CONST                 /* Applications' ROM Data           */
#define INTC_APPL_DATA                  /* Applications' RAM Data           */
#define INTC_FAST_DATA                  /* 'Near' RAM Data                  */

#define INTC_FAST_CODE                  /* API functions                   */
#define INTC_FAST_CONST                 /* API constants                   */

#define INTC_CONFIG_CONST               /* Desc. Tables -> Config-dependent  */
#define INTC_CONFIG_DATA                /* Config. dependent (reg. size) data*/

#define INTC_INIT_DATA                  /* Data which is initialized during
                                         Startup                              */
#define INTC_NOINIT_DATA                /* Data which is not initialized during
                                         Startup                              */
#define INTC_CONST                      /* Data Constants                    */
#define INTC_VAR                        /* Memory class for global variables */
                                        /* which are initialized after every   */
                                        /* reset                               */
#define INTC_VAR_NOINIT                 /* Memory class for global variables*/
                                        /* which are initialized by driver     */

/***************************************************************************************************
*                               Intc Module Stop
****************************************************************************************************/

/***************************************************************************************************
*                               Iom Module Start
****************************************************************************************************/
#define IOM_PUBLIC_CODE                /* API functions                    */
#define IOM_PUBLIC_CONST               /* API constants                    */

#define IOM_PRIVATE_CODE               /* Internal functions               */

#define IOM_PRIVATE_DATA               /* Module internal data             */
#define IOM_PRIVATE_CONST              /* Internal ROM Data                */

#define IOM_APPL_CODE                  /* callbacks of the Application     */
#define IOM_APPL_CONST                 /* Applications' ROM Data           */
#define IOM_APPL_DATA                  /* Applications' RAM Data           */
#define IOM_FAST_DATA                  /* 'Near' RAM Data                  */

#define IOM_FAST_CODE                  /* API functions                   */
#define IOM_FAST_CONST                 /* API constants                   */

#define IOM_CONFIG_CONST               /* Desc. Tables -> Config-dependent  */
#define IOM_CONFIG_DATA                /* Config. dependent (reg. size) data*/

#define IOM_INIT_DATA                  /* Data which is initialized during
                                         Startup                              */
#define IOM_NOINIT_DATA                /* Data which is not initialized during
                                         Startup                              */
#define IOM_CONST                      /* Data Constants                    */
#define IOM_VAR                        /* Memory class for global variables */
                                        /* which are initialized after every   */
                                        /* reset                               */
#define IOM_VAR_NOINIT                 /* Memory class for global variables*/
                                        /* which are initialized by driver     */

/***************************************************************************************************
*                               Iom Module Stop
****************************************************************************************************/

/***************************************************************************************************
*                               Dma Module Start
****************************************************************************************************/
#define DMA_PUBLIC_CODE                /* API functions                    */
#define DMA_PUBLIC_CONST               /* API constants                    */

#define DMA_PRIVATE_CODE               /* Internal functions               */

#define DMA_PRIVATE_DATA               /* Module internal data             */
#define DMA_PRIVATE_CONST              /* Internal ROM Data                */

#define DMA_APPL_CODE                  /* callbacks of the Application     */
#define DMA_APPL_CONST                 /* Applications' ROM Data           */
#define DMA_APPL_DATA                  /* Applications' RAM Data           */
#define DMA_FAST_DATA                  /* 'Near' RAM Data                  */

#define DMA_FAST_CODE                  /* API functions                   */
#define DMA_FAST_CONST                 /* API constants                   */

#define DMA_CONFIG_CONST               /* Desc. Tables -> Config-dependent  */
#define DMA_CONFIG_DATA                /* Config. dependent (reg. size) data*/

#define DMA_INIT_DATA                  /* Data which is initialized during
                                         Startup                              */
#define DMA_NOINIT_DATA                /* Data which is not initialized during
                                         Startup                              */
#define DMA_CONST                      /* Data Constants                    */
#define DMA_VAR                        /* Memory class for global variables */
                                        /* which are initialized after every   */
                                        /* reset                               */
#define DMA_VAR_NOINIT                 /* Memory class for global variables*/
                                        /* which are initialized by driver     */

/***************************************************************************************************
*                               Dma Module Stop
****************************************************************************************************/

/***************************************************************************************************
*                               Dsadc Module Start
****************************************************************************************************/
#define DSADC_PUBLIC_CODE                /* API functions                    */
#define DSADC_PUBLIC_CONST               /* API constants                    */

#define DSADC_PRIVATE_CODE               /* Internal functions               */

#define DSADC_PRIVATE_DATA               /* Module internal data             */
#define DSADC_PRIVATE_CONST              /* Internal ROM Data                */

#define DSADC_APPL_CODE                  /* callbacks of the Application     */
#define DSADC_APPL_CONST                 /* Applications' ROM Data           */
#define DSADC_APPL_DATA                  /* Applications' RAM Data           */
#define DSADC_FAST_DATA                  /* 'Near' RAM Data                  */

#define DSADC_FAST_CODE                  /* API functions                   */
#define DSADC_FAST_CONST                 /* API constants                   */

#define DSADC_CONFIG_CONST               /* Desc. Tables -> Config-dependent  */
#define DSADC_CONFIG_DATA                /* Config. dependent (reg. size) data*/

#define DSADC_INIT_DATA                  /* Data which is initialized during
                                         Startup                              */
#define DSADC_NOINIT_DATA                /* Data which is not initialized during
                                         Startup                              */
#define DSADC_CONST                      /* Data Constants                    */
#define DSADC_VAR                        /* Memory class for global variables */
                                        /* which are initialized after every   */
                                        /* reset                               */
#define DSADC_VAR_NOINIT                 /* Memory class for global variables*/
                                        /* which are initialized by driver     */

/***************************************************************************************************
*                               Dsadc Module Stop
****************************************************************************************************/

/***************************************************************************************************
*                               MCALL Module Start
****************************************************************************************************/
#define MCAL_PUBLIC_CODE                /* API functions                    */
#define MCAL_PUBLIC_CONST               /* API constants                    */

#define MCAL_PRIVATE_CODE               /* Internal functions               */

#define MCAL_PRIVATE_DATA               /* Module internal data             */
#define MCAL_PRIVATE_CONST              /* Internal ROM Data                */

#define MCAL_APPL_CODE                  /* callbacks of the Application     */
#define MCAL_APPL_CONST                 /* Applications' ROM Data           */
#define MCAL_APPL_DATA                  /* Applications' RAM Data           */
#define MCAL_FAST_DATA                  /* 'Near' RAM Data                  */

#define MCAL_FAST_CODE                  /* API functions                   */
#define MCAL_FAST_CONST                 /* API constants                   */

#define MCAL_CONFIG_CONST               /* Desc. Tables -> Config-dependent  */
#define MCAL_CONFIG_DATA                /* Config. dependent (reg. size) data*/

#define MCAL_INIT_DATA                  /* Data which is initialized during
                                         Startup                              */
#define MCAL_NOINIT_DATA                /* Data which is not initialized during
                                         Startup                              */
#define MCAL_CONST                      /* Data Constants                    */
#define MCAL_VAR                        /* Memory class for global variables */
                                        /* which are initialized after every   */
                                        /* reset                               */
#define MCAL_VAR_NOINIT                 /* Memory class for global variables*/
                                        /* which are initialized by driver     */

/***************************************************************************************************
*                               MCALL Module Stop
****************************************************************************************************/

/***************************************************************************************************
*                               Msc Module Start
****************************************************************************************************/

#define MSC_PUBLIC_CODE                /* API functions                       */
#define MSC_PUBLIC_CONST               /* API constants                       */

#define MSC_PRIVATE_CODE               /* Internal functions                  */

#define MSC_PRIVATE_DATA               /* Module internal data                */
#define MSC_PRIVATE_CONST              /* Internal ROM Data                   */

#define MSC_APPL_CODE                  /* callbacks of the Application        */
#define MSC_APPL_CONST                 /* Applications' ROM Data              */
#define MSC_APPL_DATA                  /* Applications' RAM Data              */
#define MSC_FAST_DATA                  /* 'Near' RAM Data                     */

#define MSC_FAST_CODE                   /* API functions                      */
#define MSC_FAST_CONST                  /* API constants                      */

#define MSC_CONFIG_CONST               /* Desc. Tables -> Config-dependent    */
#define MSC_CONFIG_DATA                /* Config. dependent (reg. size) data  */

#define MSC_INIT_DATA                  /* Data which is initialized during
                                          Startup                             */
#define MSC_NOINIT_DATA                /* Data which is not initialized during
                                          Startup                             */
#define MSC_CONST                      /* Data Constants                      */
#define MSC_VAR                        /* Memory class for global variables   */
                                       /* which are initialized after every   */
                                       /* reset                               */
#define MSC_VAR_NOINIT                 /* Memory class for global variables   */
                                       /* which are initialized by driver     */

/***************************************************************************************************
*                               Msc Module Stop
****************************************************************************************************/


#endif /* COMPILER_CFG_H */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
