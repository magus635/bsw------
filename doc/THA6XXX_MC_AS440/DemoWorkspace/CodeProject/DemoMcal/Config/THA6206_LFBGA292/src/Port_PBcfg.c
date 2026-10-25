/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Port_PBCfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GPIO
*
*   brief                 : This file contains all configurations of Port Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/
/*
*#Violation Summary
*
*#Port_PBcfg_c_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*#Port_PBcfg_c_REF_2:MISRAC2012-Rule-8.9; 
* Justification: Static global variables are placed in non-cached RAM regions to ensure accessibility by multiple cores.
*
*#Port_PBcfg_c_REF_3:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Port_PBcfg_c_REF_4:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
*/
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
/*  SWS_Port_00133:
    Port_PBcfg.c shall include Port_MemMap.h and Port.h.
*/
#include "Port.h"
#include "Port_Cfg.h"
#include "tha6_cfg.h"
/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
/* #Violation: Port_PBcfg_c_REF_1 */
#define PORT_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Port_MemMap.h"

/* Configure Port-Pin Direction, Push-pull&Open-drain, Output Function Select (CTR0/4/8/12) */
static const Port_PinControlDataType Port_PinControlData[PORT_AVAILABEL_TOTAL_NUMBER] =
{
    {
        {
            {
                /*        Port0: Pn_CTR        */
                (uint8)(PORT_PIN_IN),                                                             /* P0.0 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P0.1 */
                (uint8)(PORT_PIN_IN),                                                             /* P0.2 */
                (uint8)(PORT_PIN_IN),                                                             /* P0.3 */
                ((uint8)PORT_PIN_INOUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O6),   /* P0.4 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O1),   /* P0.5 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O1),   /* P0.6 */
                ((uint8)PORT_PIN_INOUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O6),   /* P0.7 */
                ((uint8)PORT_PIN_INOUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O6),   /* P0.8 */
                (uint8)(PORT_PIN_IN),                                                             /* P0.9 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O0),   /* P0.10 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O1),   /* P0.11 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P0.12 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P0.13 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P0.14 */
                ((uint8)PORT_PIN_UNSUPPORT)                                                       /* P0.15 */
            }
        }
    },
    {
        {
            {
                /*        Port1: Pn_CTR        */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P1.0 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P1.1 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P1.2 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P1.3 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O0),   /* P1.4 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O0),   /* P1.5 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O0),   /* P1.6 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O0),   /* P1.7 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P1.8 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P1.9 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P1.10 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P1.11 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P1.12 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P1.13 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P1.14 */
                ((uint8)PORT_PIN_UNSUPPORT)                                                       /* P1.15 */
            }
        }
    },
    {
        {
            {
                /*        Port2: Pn_CTR        */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O1),   /* P2.0 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O1),   /* P2.1 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O1),   /* P2.2 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O1),   /* P2.3 */
                (uint8)(PORT_PIN_IN),                                                             /* P2.4 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O2),   /* P2.5 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O1),   /* P2.6 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O1),   /* P2.7 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O1),   /* P2.8 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P2.9 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P2.10 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P2.11 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P2.12 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P2.13 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P2.14 */
                ((uint8)PORT_PIN_UNSUPPORT)                                                       /* P2.15 */
            }
        }
    },
    {
        {
            {
                /*        Port10: Pn_CTR        */
                (uint8)(PORT_PIN_IN),                                                             /* P10.0 */
                (uint8)(PORT_PIN_IN),                                                             /* P10.1 */
                (uint8)(PORT_PIN_IN),                                                             /* P10.2 */
                (uint8)(PORT_PIN_IN),                                                             /* P10.3 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O5),   /* P10.4 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O2),   /* P10.5 */
                (uint8)(PORT_PIN_IN),                                                             /* P10.6 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O1),   /* P10.7 */
                (uint8)(PORT_PIN_IN),                                                             /* P10.8 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P10.9 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P10.10 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P10.11 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P10.12 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P10.13 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P10.14 */
                ((uint8)PORT_PIN_UNSUPPORT)                                                       /* P10.15 */
            }
        }
    },
    {
        {
            {
                /*        Port11: Pn_CTR        */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P11.0 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P11.1 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O6),   /* P11.2 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O6),   /* P11.3 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P11.4 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P11.5 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O6),   /* P11.6 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P11.7 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P11.8 */
                (uint8)(PORT_PIN_IN),                                                             /* P11.9 */
                (uint8)(PORT_PIN_IN),                                                             /* P11.10 */
                (uint8)(PORT_PIN_IN),                                                             /* P11.11 */
                (uint8)(PORT_PIN_IN),                                                             /* P11.12 */
                (uint8)(PORT_PIN_IN),                                                             /* P11.13 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P11.14 */
                ((uint8)PORT_PIN_NOTENABLE)                                                       /* P11.15 */
            }
        }
    },
    {
        {
            {
                /*        Port12: Pn_CTR        */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O6),   /* P12.0 */
                ((uint8)PORT_PIN_INOUT | (uint8)PORT_OUTPUT_PUSHPULL),                            /* P12.1 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P12.2 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P12.3 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P12.4 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P12.5 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P12.6 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P12.7 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P12.8 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P12.9 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P12.10 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P12.11 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P12.12 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P12.13 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P12.14 */
                ((uint8)PORT_PIN_UNSUPPORT)                                                       /* P12.15 */
            }
        }
    },
    {
        {
            {
                /*        Port13: Pn_CTR        */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O5),   /* P13.0 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O5),   /* P13.1 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O5),   /* P13.2 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O5),   /* P13.3 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P13.4 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P13.5 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P13.6 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P13.7 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P13.8 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P13.9 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P13.10 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P13.11 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P13.12 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P13.13 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P13.14 */
                ((uint8)PORT_PIN_UNSUPPORT)                                                       /* P13.15 */
            }
        }
    },
    {
        {
            {
                /*        Port14: Pn_CTR        */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O1),   /* P14.0 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O1),   /* P14.1 */
                (uint8)(PORT_PIN_IN),                                                             /* P14.2 */
                (uint8)(PORT_PIN_IN),                                                             /* P14.3 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O0),   /* P14.4 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O0),   /* P14.5 */
                (uint8)(PORT_PIN_IN),                                                             /* P14.6 */
                (uint8)(PORT_PIN_IN),                                                             /* P14.7 */
                (uint8)(PORT_PIN_IN),                                                             /* P14.8 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O0),   /* P14.9 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P14.10 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P14.11 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P14.12 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P14.13 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P14.14 */
                ((uint8)PORT_PIN_UNSUPPORT)                                                       /* P14.15 */
            }
        }
    },
    {
        {
            {
                /*        Port15: Pn_CTR        */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O5),   /* P15.0 */
                (uint8)(PORT_PIN_IN),                                                             /* P15.1 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O2),   /* P15.2 */
                (uint8)(PORT_PIN_IN),                                                             /* P15.3 */
                ((uint8)PORT_PIN_INOUT | (uint8)PORT_OUTPUT_OPENDRAIN | (uint8)PORT_OUTPUTALT_O6),   /* P15.4 */
                ((uint8)PORT_PIN_INOUT | (uint8)PORT_OUTPUT_OPENDRAIN | (uint8)PORT_OUTPUTALT_O6),   /* P15.5 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O3),   /* P15.6 */
                (uint8)(PORT_PIN_IN),                                                             /* P15.7 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O3),   /* P15.8 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P15.9 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P15.10 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P15.11 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P15.12 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P15.13 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P15.14 */
                ((uint8)PORT_PIN_UNSUPPORT)                                                       /* P15.15 */
            }
        }
    },
    {
        {
            {
                /*        Port20: Pn_CTR        */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O2),   /* P20.0 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P20.1 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P20.2 */
                (uint8)(PORT_PIN_IN),                                                             /* P20.3 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P20.4 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P20.5 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P20.6 */
                (uint8)(PORT_PIN_IN),                                                             /* P20.7 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O5),   /* P20.8 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O3),   /* P20.9 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P20.10 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O3),   /* P20.11 */
                (uint8)(PORT_PIN_IN),                                                             /* P20.12 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P20.13 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O3),   /* P20.14 */
                ((uint8)PORT_PIN_UNSUPPORT)                                                       /* P20.15 */
            }
        }
    },
    {
        {
            {
                /*        Port21: Pn_CTR        */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P21.0 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P21.1 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P21.2 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P21.3 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P21.4 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P21.5 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P21.6 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P21.7 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P21.8 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P21.9 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P21.10 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P21.11 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P21.12 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P21.13 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P21.14 */
                ((uint8)PORT_PIN_UNSUPPORT)                                                       /* P21.15 */
            }
        }
    },
    {
        {
            {
                /*        Port22: Pn_CTR        */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P22.0 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P22.1 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O4),   /* P22.2 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P22.3 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P22.4 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P22.5 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P22.6 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P22.7 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P22.8 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P22.9 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P22.10 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P22.11 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P22.12 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P22.13 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P22.14 */
                ((uint8)PORT_PIN_UNSUPPORT)                                                       /* P22.15 */
            }
        }
    },
    {
        {
            {
                /*        Port23: Pn_CTR        */
                (uint8)(PORT_PIN_IN),                                                             /* P23.0 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O5),   /* P23.1 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O5),   /* P23.2 */
                (uint8)(PORT_PIN_IN),                                                             /* P23.3 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P23.4 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P23.5 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P23.6 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P23.7 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P23.8 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P23.9 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P23.10 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P23.11 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P23.12 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P23.13 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P23.14 */
                ((uint8)PORT_PIN_UNSUPPORT)                                                       /* P23.15 */
            }
        }
    },
    {
        {
            {
                /*        Port32: Pn_CTR        */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P32.0 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P32.1 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O1),   /* P32.2 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P32.3 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O4),   /* P32.4 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P32.5 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P32.6 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P32.7 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P32.8 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P32.9 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P32.10 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P32.11 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P32.12 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P32.13 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P32.14 */
                ((uint8)PORT_PIN_UNSUPPORT)                                                       /* P32.15 */
            }
        }
    },
    {
        {
            {
                /*        Port33: Pn_CTR        */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O2),   /* P33.0 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O0),   /* P33.1 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O1),   /* P33.2 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O1),   /* P33.3 */
                (uint8)(PORT_PIN_IN),                                                             /* P33.4 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O0),   /* P33.5 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P33.6 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O1),   /* P33.7 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P33.8 */
                ((uint8)PORT_PIN_OUT | (uint8)PORT_OUTPUT_PUSHPULL | (uint8)PORT_OUTPUTALT_O5),   /* P33.9 */
                (uint8)(PORT_PIN_IN),                                                             /* P33.10 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P33.11 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P33.12 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P33.13 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P33.14 */
                ((uint8)PORT_PIN_UNSUPPORT)                                                       /* P33.15 */
            }
        }
    },
    {
        {
            {
                /*        Port34: Pn_CTR        */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P34.0 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P34.1 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P34.2 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P34.3 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P34.4 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P34.5 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P34.6 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P34.7 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P34.8 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P34.9 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P34.10 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P34.11 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P34.12 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P34.13 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P34.14 */
                ((uint8)PORT_PIN_UNSUPPORT)                                                       /* P34.15 */
            }
        }
    },
    {
        {
            {
                /*        Port40: Pn_CTR        */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P40.0 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P40.1 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P40.2 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P40.3 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P40.4 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P40.5 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P40.6 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P40.7 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P40.8 */
                ((uint8)PORT_PIN_NOTENABLE),                                                      /* P40.9 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P40.10 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P40.11 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P40.12 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P40.13 */
                ((uint8)PORT_PIN_UNSUPPORT),                                                      /* P40.14 */
                ((uint8)PORT_PIN_UNSUPPORT)                                                       /* P40.15 */
            }
        }
    }
};
/* Configure Port-Pin initial output Level */
static const Port_Pin1BitType Port_PinInitLevel[PORT_AVAILABEL_TOTAL_NUMBER] =
{
    {
        {
            /*          Port0: Pn_ODR          */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P0.0 */
            (uint8)PORT_PIN_NOTENABLE,           /* P0.1 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P0.2 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P0.3 */
            (uint8)PORT_PIN_LEVEL_HIGH,           /* P0.4 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P0.5 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P0.6 */
            (uint8)PORT_PIN_LEVEL_HIGH,           /* P0.7 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P0.8 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P0.9 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P0.10 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P0.11 */
            (uint8)PORT_PIN_NOTENABLE,           /* P0.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P0.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P0.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P0.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*          Port1: Pn_ODR          */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.0 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.1 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.2 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.3 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P1.4 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P1.5 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P1.6 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P1.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*          Port2: Pn_ODR          */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P2.0 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P2.1 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P2.2 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P2.3 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P2.4 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P2.5 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P2.6 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P2.7 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P2.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*          Port10: Pn_ODR          */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P10.0 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P10.1 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P10.2 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P10.3 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P10.4 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P10.5 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P10.6 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P10.7 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P10.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*          Port11: Pn_ODR          */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.0 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.1 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P11.2 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P11.3 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.4 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.5 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P11.6 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.7 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.8 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P11.9 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P11.10 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P11.11 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P11.12 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P11.13 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.14 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*          Port12: Pn_ODR          */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P12.0 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P12.1 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.2 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.3 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.4 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.5 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.6 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*          Port13: Pn_ODR          */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P13.0 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P13.1 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P13.2 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P13.3 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.4 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.5 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.6 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*          Port14: Pn_ODR          */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P14.0 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P14.1 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P14.2 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P14.3 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P14.4 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P14.5 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P14.6 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P14.7 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P14.8 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P14.9 */
            (uint8)PORT_PIN_NOTENABLE,           /* P14.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P14.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P14.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P14.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P14.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P14.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*          Port15: Pn_ODR          */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P15.0 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P15.1 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P15.2 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P15.3 */
            (uint8)PORT_PIN_LEVEL_HIGH,           /* P15.4 */
            (uint8)PORT_PIN_LEVEL_HIGH,           /* P15.5 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P15.6 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P15.7 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P15.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*          Port20: Pn_ODR          */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P20.0 */
            (uint8)PORT_PIN_NOTENABLE,           /* P20.1 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P20.2 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P20.3 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P20.4 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P20.5 */
            (uint8)PORT_PIN_NOTENABLE,           /* P20.6 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P20.7 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P20.8 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P20.9 */
            (uint8)PORT_PIN_NOTENABLE,           /* P20.10 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P20.11 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P20.12 */
            (uint8)PORT_PIN_NOTENABLE,           /* P20.13 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P20.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P20.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*          Port21: Pn_ODR          */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.0 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.1 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.2 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.3 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.4 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.5 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.6 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*          Port22: Pn_ODR          */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.0 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.1 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P22.2 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.3 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.4 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.5 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.6 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P22.8 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.9 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.10 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P22.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P22.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P22.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P22.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*          Port23: Pn_ODR          */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P23.0 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P23.1 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P23.2 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P23.3 */
            (uint8)PORT_PIN_NOTENABLE,           /* P23.4 */
            (uint8)PORT_PIN_NOTENABLE,           /* P23.5 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.6 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*          Port32: Pn_ODR          */
            (uint8)PORT_PIN_NOTENABLE,           /* P32.0 */
            (uint8)PORT_PIN_NOTENABLE,           /* P32.1 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P32.2 */
            (uint8)PORT_PIN_NOTENABLE,           /* P32.3 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P32.4 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.5 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.6 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*          Port33: Pn_ODR          */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P33.0 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P33.1 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P33.2 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P33.3 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P33.4 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P33.5 */
            (uint8)PORT_PIN_NOTENABLE,           /* P33.6 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P33.7 */
            (uint8)PORT_PIN_NOTENABLE,           /* P33.8 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P33.9 */
            (uint8)PORT_PIN_LEVEL_LOW,           /* P33.10 */
            (uint8)PORT_PIN_NOTENABLE,           /* P33.11 */
            (uint8)PORT_PIN_NOTENABLE,           /* P33.12 */
            (uint8)PORT_PIN_NOTENABLE,           /* P33.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P33.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P33.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*          Port34: Pn_ODR          */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.0 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.1 */
            (uint8)PORT_PIN_NOTENABLE,           /* P34.2 */
            (uint8)PORT_PIN_NOTENABLE,           /* P34.3 */
            (uint8)PORT_PIN_NOTENABLE,           /* P34.4 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.5 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.6 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*          Port40: Pn_ODR          */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.0 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.1 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.2 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.3 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.4 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.5 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.6 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.7 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.8 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P40.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P40.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P40.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P40.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P40.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P40.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    }
};
/* Configure Port-Pin Pad level, slew-rate, Pad input mode, Pad driver Select (DSR0/DSR8) */
static const Port_Pin4BitType Port_PinPadControlData[PORT_AVAILABEL_TOTAL_NUMBER] =
{
    {
        {
            /*          Port0: Pn_DSR          */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P0.0 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P0.1 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P0.2 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P0.3 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P0.4 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P0.5 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P0.6 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P0.7 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P0.8 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P0.9 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P0.10 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P0.11 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P0.12 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P0.13 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P0.14 */
            ((uint8)PORT_PIN_UNSUPPORT)                                                  /* P0.15 */
        }
    },
    {
        {
            /*          Port1: Pn_DSR          */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P1.0 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P1.1 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P1.2 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P1.3 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P1.4 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P1.5 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P1.6 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P1.7 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P1.8 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P1.9 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P1.10 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P1.11 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P1.12 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P1.13 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P1.14 */
            ((uint8)PORT_PIN_UNSUPPORT)                                                  /* P1.15 */
        }
    },
    {
        {
            /*          Port2: Pn_DSR          */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P2.0 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P2.1 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P2.2 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P2.3 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P2.4 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P2.5 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P2.6 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P2.7 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P2.8 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P2.9 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P2.10 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P2.11 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P2.12 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P2.13 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P2.14 */
            ((uint8)PORT_PIN_UNSUPPORT)                                                  /* P2.15 */
        }
    },
    {
        {
            /*          Port10: Pn_DSR          */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P10.0 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P10.1 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P10.2 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P10.3 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P10.4 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P10.5 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P10.6 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P10.7 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P10.8 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P10.9 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P10.10 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P10.11 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P10.12 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P10.13 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P10.14 */
            ((uint8)PORT_PIN_UNSUPPORT)                                                  /* P10.15 */
        }
    },
    {
        {
            /*          Port11: Pn_DSR          */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P11.0 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P11.1 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_HIGH),    /* P11.2 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_HIGH),    /* P11.3 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P11.4 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P11.5 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_HIGH),    /* P11.6 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P11.7 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P11.8 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_CMOS_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P11.9 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_CMOS_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P11.10 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_CMOS_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P11.11 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_CMOS_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P11.12 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_CMOS_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P11.13 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P11.14 */
            ((uint8)PORT_PIN_NOTENABLE)                                                  /* P11.15 */
        }
    },
    {
        {
            /*          Port12: Pn_DSR          */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_HIGH),    /* P12.0 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_HIGH),    /* P12.1 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P12.2 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P12.3 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P12.4 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P12.5 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P12.6 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P12.7 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P12.8 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P12.9 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P12.10 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P12.11 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P12.12 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P12.13 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P12.14 */
            ((uint8)PORT_PIN_UNSUPPORT)                                                  /* P12.15 */
        }
    },
    {
        {
            /*          Port13: Pn_DSR          */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_HIGH),    /* P13.0 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_HIGH),    /* P13.1 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P13.2 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P13.3 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P13.4 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P13.5 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P13.6 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P13.7 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P13.8 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P13.9 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P13.10 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P13.11 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P13.12 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P13.13 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P13.14 */
            ((uint8)PORT_PIN_UNSUPPORT)                                                  /* P13.15 */
        }
    },
    {
        {
            /*          Port14: Pn_DSR          */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P14.0 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P14.1 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P14.2 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P14.3 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P14.4 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P14.5 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P14.6 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P14.7 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P14.8 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P14.9 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P14.10 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P14.11 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P14.12 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P14.13 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P14.14 */
            ((uint8)PORT_PIN_UNSUPPORT)                                                  /* P14.15 */
        }
    },
    {
        {
            /*          Port15: Pn_DSR          */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P15.0 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P15.1 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P15.2 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P15.3 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P15.4 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P15.5 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P15.6 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P15.7 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_HIGH),    /* P15.8 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P15.9 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P15.10 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P15.11 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P15.12 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P15.13 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P15.14 */
            ((uint8)PORT_PIN_UNSUPPORT)                                                  /* P15.15 */
        }
    },
    {
        {
            /*          Port20: Pn_DSR          */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P20.0 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P20.1 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P20.2 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P20.3 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P20.4 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P20.5 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P20.6 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_CMOS_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P20.7 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P20.8 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P20.9 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P20.10 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_HIGH),    /* P20.11 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_CMOS_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P20.12 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P20.13 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_HIGH),    /* P20.14 */
            ((uint8)PORT_PIN_UNSUPPORT)                                                  /* P20.15 */
        }
    },
    {
        {
            /*          Port21: Pn_DSR          */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P21.0 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P21.1 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P21.2 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P21.3 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P21.4 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P21.5 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P21.6 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P21.7 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P21.8 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P21.9 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P21.10 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P21.11 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P21.12 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P21.13 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P21.14 */
            ((uint8)PORT_PIN_UNSUPPORT)                                                  /* P21.15 */
        }
    },
    {
        {
            /*          Port22: Pn_DSR          */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P22.0 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P22.1 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P22.2 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P22.3 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P22.4 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P22.5 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P22.6 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P22.7 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P22.8 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P22.9 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P22.10 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P22.11 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P22.12 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P22.13 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P22.14 */
            ((uint8)PORT_PIN_UNSUPPORT)                                                  /* P22.15 */
        }
    },
    {
        {
            /*          Port23: Pn_DSR          */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P23.0 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_HIGH),    /* P23.1 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P23.2 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P23.3 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P23.4 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P23.5 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P23.6 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P23.7 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P23.8 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P23.9 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P23.10 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P23.11 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P23.12 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P23.13 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P23.14 */
            ((uint8)PORT_PIN_UNSUPPORT)                                                  /* P23.15 */
        }
    },
    {
        {
            /*          Port32: Pn_DSR          */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P32.0 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P32.1 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P32.2 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P32.3 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P32.4 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P32.5 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P32.6 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P32.7 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P32.8 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P32.9 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P32.10 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P32.11 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P32.12 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P32.13 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P32.14 */
            ((uint8)PORT_PIN_UNSUPPORT)                                                  /* P32.15 */
        }
    },
    {
        {
            /*          Port33: Pn_DSR          */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P33.0 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P33.1 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P33.2 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P33.3 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P33.4 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P33.5 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P33.6 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P33.7 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P33.8 */
            ((uint8)PORT_PDR_AL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P33.9 */
            ((uint8)PORT_PDR_TTL_AUTOMOTIVE_LEVEL | (uint8)PORT_SLEWRATEMODE_DISABLE |
             (uint8)PORT_SCHMIDT_LEVEL_MODE       | (uint8)PORT_DRIVER_STRENGTH_LOW),    /* P33.10 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P33.11 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P33.12 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P33.13 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P33.14 */
            ((uint8)PORT_PIN_UNSUPPORT)                                                  /* P33.15 */
        }
    },
    {
        {
            /*          Port34: Pn_DSR          */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P34.0 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P34.1 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P34.2 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P34.3 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P34.4 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P34.5 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P34.6 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P34.7 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P34.8 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P34.9 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P34.10 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P34.11 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P34.12 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P34.13 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P34.14 */
            ((uint8)PORT_PIN_UNSUPPORT)                                                  /* P34.15 */
        }
    },
    {
        {
            /*          Port40: Pn_DSR          */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P40.0 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P40.1 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P40.2 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P40.3 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P40.4 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P40.5 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P40.6 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P40.7 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P40.8 */
            ((uint8)PORT_PIN_NOTENABLE),                                                 /* P40.9 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P40.10 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P40.11 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P40.12 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P40.13 */
            ((uint8)PORT_PIN_UNSUPPORT),                                                 /* P40.14 */
            ((uint8)PORT_PIN_UNSUPPORT)                                                  /* P40.15 */
        }
    }
};
/* Configure Port-Pin digital function enable */
static const Port_Pin2BitType Port_PinDigitalEnable[PORT_AVAILABEL_TOTAL_NUMBER] =
{
    {
        {
            /*          Port0: Pn_DFR          */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P0.0 */
            (uint8)PORT_PIN_NOTENABLE,           /* P0.1 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P0.2 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P0.3 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P0.4 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P0.5 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P0.6 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P0.7 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P0.8 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P0.9 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P0.10 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P0.11 */
            (uint8)PORT_PIN_NOTENABLE,           /* P0.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P0.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P0.14 */
            (uint8)PORT_PIN_UNSUPPORT            /* P0.15 */
        }
    },
    {
        {
            /*          Port1: Pn_DFR          */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.0 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.1 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.2 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.3 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P1.4 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P1.5 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P1.6 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P1.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.14 */
            (uint8)PORT_PIN_UNSUPPORT            /* P1.15 */
        }
    },
    {
        {
            /*          Port2: Pn_DFR          */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P2.0 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P2.1 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P2.2 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P2.3 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P2.4 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P2.5 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P2.6 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P2.7 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P2.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.14 */
            (uint8)PORT_PIN_UNSUPPORT            /* P2.15 */
        }
    },
    {
        {
            /*          Port10: Pn_DFR          */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P10.0 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P10.1 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P10.2 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P10.3 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P10.4 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P10.5 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P10.6 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P10.7 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P10.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.14 */
            (uint8)PORT_PIN_UNSUPPORT            /* P10.15 */
        }
    },
    {
        {
            /*          Port11: Pn_DFR          */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.0 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.1 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P11.2 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P11.3 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.4 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.5 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P11.6 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.7 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.8 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P11.9 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P11.10 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P11.11 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P11.12 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P11.13 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.14 */
            (uint8)PORT_PIN_NOTENABLE            /* P11.15 */
        }
    },
    {
        {
            /*          Port12: Pn_DFR          */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P12.0 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P12.1 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.2 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.3 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.4 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.5 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.6 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.14 */
            (uint8)PORT_PIN_UNSUPPORT            /* P12.15 */
        }
    },
    {
        {
            /*          Port13: Pn_DFR          */
            (uint8)PORT_FUNCTION_MODE_ANALOG,    /* P13.0 */
            (uint8)PORT_FUNCTION_MODE_ANALOG,    /* P13.1 */
            (uint8)PORT_FUNCTION_MODE_ANALOG,    /* P13.2 */
            (uint8)PORT_FUNCTION_MODE_ANALOG,    /* P13.3 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.4 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.5 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.6 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.14 */
            (uint8)PORT_PIN_UNSUPPORT            /* P13.15 */
        }
    },
    {
        {
            /*          Port14: Pn_DFR          */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P14.0 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P14.1 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P14.2 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P14.3 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P14.4 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P14.5 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P14.6 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P14.7 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P14.8 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P14.9 */
            (uint8)PORT_PIN_NOTENABLE,           /* P14.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P14.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P14.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P14.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P14.14 */
            (uint8)PORT_PIN_UNSUPPORT            /* P14.15 */
        }
    },
    {
        {
            /*          Port15: Pn_DFR          */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P15.0 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P15.1 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P15.2 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P15.3 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P15.4 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P15.5 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P15.6 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P15.7 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P15.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.14 */
            (uint8)PORT_PIN_UNSUPPORT            /* P15.15 */
        }
    },
    {
        {
            /*          Port20: Pn_DFR          */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P20.0 */
            (uint8)PORT_PIN_NOTENABLE,           /* P20.1 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P20.2 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P20.3 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P20.4 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P20.5 */
            (uint8)PORT_PIN_NOTENABLE,           /* P20.6 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P20.7 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P20.8 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P20.9 */
            (uint8)PORT_PIN_NOTENABLE,           /* P20.10 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P20.11 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P20.12 */
            (uint8)PORT_PIN_NOTENABLE,           /* P20.13 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P20.14 */
            (uint8)PORT_PIN_UNSUPPORT            /* P20.15 */
        }
    },
    {
        {
            /*          Port21: Pn_DFR          */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.0 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.1 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.2 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.3 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.4 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.5 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.6 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.14 */
            (uint8)PORT_PIN_UNSUPPORT            /* P21.15 */
        }
    },
    {
        {
            /*          Port22: Pn_DFR          */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.0 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.1 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P22.2 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.3 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.4 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.5 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.6 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P22.8 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.9 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.10 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P22.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P22.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P22.14 */
            (uint8)PORT_PIN_UNSUPPORT            /* P22.15 */
        }
    },
    {
        {
            /*          Port23: Pn_DFR          */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P23.0 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P23.1 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P23.2 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P23.3 */
            (uint8)PORT_PIN_NOTENABLE,           /* P23.4 */
            (uint8)PORT_PIN_NOTENABLE,           /* P23.5 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.6 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.14 */
            (uint8)PORT_PIN_UNSUPPORT            /* P23.15 */
        }
    },
    {
        {
            /*          Port32: Pn_DFR          */
            (uint8)PORT_FUNCTION_MODE_ANALOG,    /* P32.0 */
            (uint8)PORT_FUNCTION_MODE_ANALOG,    /* P32.1 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P32.2 */
            (uint8)PORT_FUNCTION_MODE_ANALOG,    /* P32.3 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P32.4 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.5 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.6 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.14 */
            (uint8)PORT_PIN_UNSUPPORT            /* P32.15 */
        }
    },
    {
        {
            /*          Port33: Pn_DFR          */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P33.0 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P33.1 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P33.2 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P33.3 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P33.4 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P33.5 */
            (uint8)PORT_PIN_NOTENABLE,           /* P33.6 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P33.7 */
            (uint8)PORT_PIN_NOTENABLE,           /* P33.8 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P33.9 */
            (uint8)PORT_FUNCTION_MODE_DIGITAL,   /* P33.10 */
            (uint8)PORT_PIN_NOTENABLE,           /* P33.11 */
            (uint8)PORT_PIN_NOTENABLE,           /* P33.12 */
            (uint8)PORT_PIN_NOTENABLE,           /* P33.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P33.14 */
            (uint8)PORT_PIN_UNSUPPORT            /* P33.15 */
        }
    },
    {
        {
            /*          Port34: Pn_DFR          */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.0 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.1 */
            (uint8)PORT_PIN_NOTENABLE,           /* P34.2 */
            (uint8)PORT_PIN_NOTENABLE,           /* P34.3 */
            (uint8)PORT_PIN_NOTENABLE,           /* P34.4 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.5 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.6 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.14 */
            (uint8)PORT_PIN_UNSUPPORT            /* P34.15 */
        }
    },
    {
        {
            /*          Port40: Pn_DFR          */
            (uint8)PORT_FUNCTION_MODE_ANALOG,    /* P40.0 */
            (uint8)PORT_FUNCTION_MODE_ANALOG,    /* P40.1 */
            (uint8)PORT_FUNCTION_MODE_ANALOG,    /* P40.2 */
            (uint8)PORT_FUNCTION_MODE_ANALOG,    /* P40.3 */
            (uint8)PORT_FUNCTION_MODE_ANALOG,    /* P40.4 */
            (uint8)PORT_FUNCTION_MODE_ANALOG,    /* P40.5 */
            (uint8)PORT_FUNCTION_MODE_ANALOG,    /* P40.6 */
            (uint8)PORT_FUNCTION_MODE_ANALOG,    /* P40.7 */
            (uint8)PORT_FUNCTION_MODE_ANALOG,    /* P40.8 */
            (uint8)PORT_FUNCTION_MODE_ANALOG,    /* P40.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P40.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P40.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P40.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P40.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P40.14 */
            (uint8)PORT_PIN_UNSUPPORT            /* P40.15 */
        }
    }
};
/* Configure Port-Pin hardware control select */
static const Port_Pin2BitType Port_PinHwSelect[PORT_AVAILABEL_TOTAL_NUMBER] =
{
    {
        {
            /*          Port0: Pn_HWCR         */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P0.0 */
            (uint8)PORT_PIN_NOTENABLE,               /* P0.1 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P0.2 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P0.3 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P0.4 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P0.5 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P0.6 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P0.7 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P0.8 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P0.9 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P0.10 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P0.11 */
            (uint8)PORT_PIN_NOTENABLE,               /* P0.12 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P0.13 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P0.14 */
            (uint8)PORT_PIN_UNSUPPORT                /* P0.15 */
        }
    },
    {
        {
            /*          Port1: Pn_HWCR         */
            (uint8)PORT_PIN_UNSUPPORT,               /* P1.0 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P1.1 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P1.2 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P1.3 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P1.4 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P1.5 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P1.6 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P1.7 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P1.8 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P1.9 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P1.10 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P1.11 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P1.12 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P1.13 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P1.14 */
            (uint8)PORT_PIN_UNSUPPORT                /* P1.15 */
        }
    },
    {
        {
            /*          Port2: Pn_HWCR         */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P2.0 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P2.1 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P2.2 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P2.3 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P2.4 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P2.5 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P2.6 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P2.7 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P2.8 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P2.9 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P2.10 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P2.11 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P2.12 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P2.13 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P2.14 */
            (uint8)PORT_PIN_UNSUPPORT                /* P2.15 */
        }
    },
    {
        {
            /*          Port10: Pn_HWCR         */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P10.0 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P10.1 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P10.2 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P10.3 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P10.4 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P10.5 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P10.6 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P10.7 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P10.8 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P10.9 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P10.10 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P10.11 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P10.12 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P10.13 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P10.14 */
            (uint8)PORT_PIN_UNSUPPORT                /* P10.15 */
        }
    },
    {
        {
            /*          Port11: Pn_HWCR         */
            (uint8)PORT_PIN_NOTENABLE,               /* P11.0 */
            (uint8)PORT_PIN_NOTENABLE,               /* P11.1 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P11.2 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P11.3 */
            (uint8)PORT_PIN_NOTENABLE,               /* P11.4 */
            (uint8)PORT_PIN_NOTENABLE,               /* P11.5 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P11.6 */
            (uint8)PORT_PIN_NOTENABLE,               /* P11.7 */
            (uint8)PORT_PIN_NOTENABLE,               /* P11.8 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P11.9 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P11.10 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P11.11 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P11.12 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P11.13 */
            (uint8)PORT_PIN_NOTENABLE,               /* P11.14 */
            (uint8)PORT_PIN_NOTENABLE                /* P11.15 */
        }
    },
    {
        {
            /*          Port12: Pn_HWCR         */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P12.0 */
            (uint8)PORT_CONTROLLER_VIA_PERIPHERAL,   /* P12.1 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P12.2 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P12.3 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P12.4 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P12.5 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P12.6 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P12.7 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P12.8 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P12.9 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P12.10 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P12.11 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P12.12 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P12.13 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P12.14 */
            (uint8)PORT_PIN_UNSUPPORT                /* P12.15 */
        }
    },
    {
        {
            /*          Port13: Pn_HWCR         */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P13.0 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P13.1 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P13.2 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P13.3 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P13.4 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P13.5 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P13.6 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P13.7 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P13.8 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P13.9 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P13.10 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P13.11 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P13.12 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P13.13 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P13.14 */
            (uint8)PORT_PIN_UNSUPPORT                /* P13.15 */
        }
    },
    {
        {
            /*          Port14: Pn_HWCR         */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P14.0 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P14.1 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P14.2 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P14.3 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P14.4 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P14.5 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P14.6 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P14.7 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P14.8 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P14.9 */
            (uint8)PORT_PIN_NOTENABLE,               /* P14.10 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P14.11 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P14.12 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P14.13 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P14.14 */
            (uint8)PORT_PIN_UNSUPPORT                /* P14.15 */
        }
    },
    {
        {
            /*          Port15: Pn_HWCR         */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P15.0 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P15.1 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P15.2 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P15.3 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P15.4 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P15.5 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P15.6 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P15.7 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P15.8 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P15.9 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P15.10 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P15.11 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P15.12 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P15.13 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P15.14 */
            (uint8)PORT_PIN_UNSUPPORT                /* P15.15 */
        }
    },
    {
        {
            /*          Port20: Pn_HWCR         */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P20.0 */
            (uint8)PORT_PIN_NOTENABLE,               /* P20.1 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P20.2 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P20.3 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P20.4 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P20.5 */
            (uint8)PORT_PIN_NOTENABLE,               /* P20.6 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P20.7 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P20.8 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P20.9 */
            (uint8)PORT_PIN_NOTENABLE,               /* P20.10 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P20.11 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P20.12 */
            (uint8)PORT_PIN_NOTENABLE,               /* P20.13 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P20.14 */
            (uint8)PORT_PIN_UNSUPPORT                /* P20.15 */
        }
    },
    {
        {
            /*          Port21: Pn_HWCR         */
            (uint8)PORT_PIN_NOTENABLE,               /* P21.0 */
            (uint8)PORT_PIN_NOTENABLE,               /* P21.1 */
            (uint8)PORT_PIN_NOTENABLE,               /* P21.2 */
            (uint8)PORT_PIN_NOTENABLE,               /* P21.3 */
            (uint8)PORT_PIN_NOTENABLE,               /* P21.4 */
            (uint8)PORT_PIN_NOTENABLE,               /* P21.5 */
            (uint8)PORT_PIN_NOTENABLE,               /* P21.6 */
            (uint8)PORT_CONTROLLER_VIA_PERIPHERAL,   /* P21.7 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P21.8 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P21.9 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P21.10 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P21.11 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P21.12 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P21.13 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P21.14 */
            (uint8)PORT_PIN_UNSUPPORT                /* P21.15 */
        }
    },
    {
        {
            /*          Port22: Pn_HWCR         */
            (uint8)PORT_PIN_NOTENABLE,               /* P22.0 */
            (uint8)PORT_PIN_NOTENABLE,               /* P22.1 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P22.2 */
            (uint8)PORT_PIN_NOTENABLE,               /* P22.3 */
            (uint8)PORT_PIN_NOTENABLE,               /* P22.4 */
            (uint8)PORT_PIN_NOTENABLE,               /* P22.5 */
            (uint8)PORT_PIN_NOTENABLE,               /* P22.6 */
            (uint8)PORT_PIN_NOTENABLE,               /* P22.7 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P22.8 */
            (uint8)PORT_PIN_NOTENABLE,               /* P22.9 */
            (uint8)PORT_PIN_NOTENABLE,               /* P22.10 */
            (uint8)PORT_PIN_NOTENABLE,               /* P22.11 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P22.12 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P22.13 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P22.14 */
            (uint8)PORT_PIN_UNSUPPORT                /* P22.15 */
        }
    },
    {
        {
            /*          Port23: Pn_HWCR         */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P23.0 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P23.1 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P23.2 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P23.3 */
            (uint8)PORT_PIN_NOTENABLE,               /* P23.4 */
            (uint8)PORT_PIN_NOTENABLE,               /* P23.5 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P23.6 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P23.7 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P23.8 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P23.9 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P23.10 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P23.11 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P23.12 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P23.13 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P23.14 */
            (uint8)PORT_PIN_UNSUPPORT                /* P23.15 */
        }
    },
    {
        {
            /*          Port32: Pn_HWCR         */
            (uint8)PORT_PIN_NOTENABLE,               /* P32.0 */
            (uint8)PORT_PIN_NOTENABLE,               /* P32.1 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P32.2 */
            (uint8)PORT_PIN_NOTENABLE,               /* P32.3 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P32.4 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P32.5 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P32.6 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P32.7 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P32.8 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P32.9 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P32.10 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P32.11 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P32.12 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P32.13 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P32.14 */
            (uint8)PORT_PIN_UNSUPPORT                /* P32.15 */
        }
    },
    {
        {
            /*          Port33: Pn_HWCR         */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P33.0 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P33.1 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P33.2 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P33.3 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P33.4 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P33.5 */
            (uint8)PORT_PIN_NOTENABLE,               /* P33.6 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P33.7 */
            (uint8)PORT_CONTROLLER_VIA_PERIPHERAL,   /* P33.8 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P33.9 */
            (uint8)PORT_CONTROLLER_VIA_PORT,         /* P33.10 */
            (uint8)PORT_PIN_NOTENABLE,               /* P33.11 */
            (uint8)PORT_PIN_NOTENABLE,               /* P33.12 */
            (uint8)PORT_PIN_NOTENABLE,               /* P33.13 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P33.14 */
            (uint8)PORT_PIN_UNSUPPORT                /* P33.15 */
        }
    },
    {
        {
            /*          Port34: Pn_HWCR         */
            (uint8)PORT_PIN_UNSUPPORT,               /* P34.0 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P34.1 */
            (uint8)PORT_PIN_NOTENABLE,               /* P34.2 */
            (uint8)PORT_PIN_NOTENABLE,               /* P34.3 */
            (uint8)PORT_PIN_NOTENABLE,               /* P34.4 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P34.5 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P34.6 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P34.7 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P34.8 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P34.9 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P34.10 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P34.11 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P34.12 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P34.13 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P34.14 */
            (uint8)PORT_PIN_UNSUPPORT                /* P34.15 */
        }
    },
    {
        {
            /*          Port40: Pn_HWCR         */
            (uint8)PORT_PIN_NOTENABLE,               /* P40.0 */
            (uint8)PORT_PIN_NOTENABLE,               /* P40.1 */
            (uint8)PORT_PIN_NOTENABLE,               /* P40.2 */
            (uint8)PORT_PIN_NOTENABLE,               /* P40.3 */
            (uint8)PORT_PIN_NOTENABLE,               /* P40.4 */
            (uint8)PORT_PIN_NOTENABLE,               /* P40.5 */
            (uint8)PORT_PIN_NOTENABLE,               /* P40.6 */
            (uint8)PORT_PIN_NOTENABLE,               /* P40.7 */
            (uint8)PORT_PIN_NOTENABLE,               /* P40.8 */
            (uint8)PORT_PIN_NOTENABLE,               /* P40.9 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P40.10 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P40.11 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P40.12 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P40.13 */
            (uint8)PORT_PIN_UNSUPPORT,               /* P40.14 */
            (uint8)PORT_PIN_UNSUPPORT                /* P40.15 */
        }
    }
};
/* Configure Port-Pin Pull_Up/Pull_Down */
static const Port_Pin2BitType Port_PinPullSelect[PORT_AVAILABEL_TOTAL_NUMBER] =
{
    {
        {
            /*          Port0: Pn_PSR          */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P0.0 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P0.1 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P0.2 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P0.3 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P0.4 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P0.5 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P0.6 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P0.7 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P0.8 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P0.9 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P0.10 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P0.11 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P0.12 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P0.13 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P0.14 */
            (uint8)PORT_PIN_UNSUPPORTPSR         /* P0.15 */
        }
    },
    {
        {
            /*          Port1: Pn_PSR          */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P1.0 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P1.1 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P1.2 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P1.3 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P1.4 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P1.5 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P1.6 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P1.7 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P1.8 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P1.9 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P1.10 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P1.11 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P1.12 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P1.13 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P1.14 */
            (uint8)PORT_PIN_UNSUPPORTPSR         /* P1.15 */
        }
    },
    {
        {
            /*          Port2: Pn_PSR          */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P2.0 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P2.1 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P2.2 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P2.3 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P2.4 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P2.5 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P2.6 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P2.7 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P2.8 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P2.9 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P2.10 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P2.11 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P2.12 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P2.13 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P2.14 */
            (uint8)PORT_PIN_UNSUPPORTPSR         /* P2.15 */
        }
    },
    {
        {
            /*          Port10: Pn_PSR          */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P10.0 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P10.1 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P10.2 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P10.3 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P10.4 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P10.5 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P10.6 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P10.7 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P10.8 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P10.9 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P10.10 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P10.11 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P10.12 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P10.13 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P10.14 */
            (uint8)PORT_PIN_UNSUPPORTPSR         /* P10.15 */
        }
    },
    {
        {
            /*          Port11: Pn_PSR          */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P11.0 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P11.1 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P11.2 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P11.3 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P11.4 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P11.5 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P11.6 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P11.7 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P11.8 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P11.9 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P11.10 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P11.11 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P11.12 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P11.13 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P11.14 */
            (uint8)PORT_INPUTMODE_PULLUP         /* P11.15 */
        }
    },
    {
        {
            /*          Port12: Pn_PSR          */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P12.0 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P12.1 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P12.2 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P12.3 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P12.4 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P12.5 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P12.6 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P12.7 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P12.8 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P12.9 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P12.10 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P12.11 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P12.12 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P12.13 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P12.14 */
            (uint8)PORT_PIN_UNSUPPORTPSR         /* P12.15 */
        }
    },
    {
        {
            /*          Port13: Pn_PSR          */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P13.0 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P13.1 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P13.2 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P13.3 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P13.4 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P13.5 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P13.6 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P13.7 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P13.8 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P13.9 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P13.10 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P13.11 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P13.12 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P13.13 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P13.14 */
            (uint8)PORT_PIN_UNSUPPORTPSR         /* P13.15 */
        }
    },
    {
        {
            /*          Port14: Pn_PSR          */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P14.0 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P14.1 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P14.2 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P14.3 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P14.4 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P14.5 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P14.6 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P14.7 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P14.8 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P14.9 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P14.10 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P14.11 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P14.12 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P14.13 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P14.14 */
            (uint8)PORT_PIN_UNSUPPORTPSR         /* P14.15 */
        }
    },
    {
        {
            /*          Port15: Pn_PSR          */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P15.0 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P15.1 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P15.2 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P15.3 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P15.4 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P15.5 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P15.6 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P15.7 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P15.8 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P15.9 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P15.10 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P15.11 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P15.12 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P15.13 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P15.14 */
            (uint8)PORT_PIN_UNSUPPORTPSR         /* P15.15 */
        }
    },
    {
        {
            /*          Port20: Pn_PSR          */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P20.0 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P20.1 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P20.2 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P20.3 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P20.4 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P20.5 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P20.6 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P20.7 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P20.8 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P20.9 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P20.10 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P20.11 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P20.12 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P20.13 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P20.14 */
            (uint8)PORT_PIN_UNSUPPORTPSR         /* P20.15 */
        }
    },
    {
        {
            /*          Port21: Pn_PSR          */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P21.0 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P21.1 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P21.2 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P21.3 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P21.4 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P21.5 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P21.6 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P21.7 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P21.8 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P21.9 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P21.10 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P21.11 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P21.12 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P21.13 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P21.14 */
            (uint8)PORT_PIN_UNSUPPORTPSR         /* P21.15 */
        }
    },
    {
        {
            /*          Port22: Pn_PSR          */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P22.0 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P22.1 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P22.2 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P22.3 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P22.4 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P22.5 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P22.6 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P22.7 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P22.8 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P22.9 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P22.10 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P22.11 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P22.12 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P22.13 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P22.14 */
            (uint8)PORT_PIN_UNSUPPORTPSR         /* P22.15 */
        }
    },
    {
        {
            /*          Port23: Pn_PSR          */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P23.0 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P23.1 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P23.2 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P23.3 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P23.4 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P23.5 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P23.6 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P23.7 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P23.8 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P23.9 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P23.10 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P23.11 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P23.12 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P23.13 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P23.14 */
            (uint8)PORT_PIN_UNSUPPORTPSR         /* P23.15 */
        }
    },
    {
        {
            /*          Port32: Pn_PSR          */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P32.0 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P32.1 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P32.2 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P32.3 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P32.4 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P32.5 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P32.6 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P32.7 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P32.8 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P32.9 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P32.10 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P32.11 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P32.12 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P32.13 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P32.14 */
            (uint8)PORT_PIN_UNSUPPORTPSR         /* P32.15 */
        }
    },
    {
        {
            /*          Port33: Pn_PSR          */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P33.0 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P33.1 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P33.2 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P33.3 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P33.4 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P33.5 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P33.6 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P33.7 */
            (uint8)PORT_INPUTMODE_NONE,          /* P33.8 */
            (uint8)PORT_INPUTMODE_PULLUP,          /* P33.9 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P33.10 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P33.11 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P33.12 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P33.13 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P33.14 */
            (uint8)PORT_PIN_UNSUPPORTPSR         /* P33.15 */
        }
    },
    {
        {
            /*          Port34: Pn_PSR          */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P34.0 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P34.1 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P34.2 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P34.3 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P34.4 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P34.5 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P34.6 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P34.7 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P34.8 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P34.9 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P34.10 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P34.11 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P34.12 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P34.13 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P34.14 */
            (uint8)PORT_PIN_UNSUPPORTPSR         /* P34.15 */
        }
    },
    {
        {
            /*          Port40: Pn_PSR          */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P40.0 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P40.1 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P40.2 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P40.3 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P40.4 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P40.5 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P40.6 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P40.7 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P40.8 */
            (uint8)PORT_INPUTMODE_PULLUP,        /* P40.9 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P40.10 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P40.11 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P40.12 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P40.13 */
            (uint8)PORT_PIN_UNSUPPORTPSR,        /* P40.14 */
            (uint8)PORT_PIN_UNSUPPORTPSR         /* P40.15 */
        }
    }
};
/* Configure Port-Pin input multiplexing function selection */
static const RXMUX_SELType RXMUX_SelectData[PORT_RXMUX_REG_TOTAL_NUMBER] =
{
    {/* RxMux: 0 */
        {
            /*             CAN0ISEL            */
            (uint8)PORT_CAN_RXDB,                /* CAN00RXSEL */
            (uint8)PORT_CAN_RXDD,                /* CAN01RXSEL */
            (uint8)PORT_CAN_RXDA,                /* CAN02RXSEL */
            (uint8)PORT_RXRESERVE,               /* RESERVE    */
            (uint8)PORT_RXRESERVE,               /* RESERVE    */
            (uint8)PORT_RXRESERVE,               /* RESERVE    */
            (uint8)PORT_RXRESERVE,               /* RESERVE    */
            (uint8)PORT_RXRESERVE                /* RESERVE    */
        }
    },
    {/* RxMux: 1 */
        {
            /*             CAN1ISEL            */
            (uint8)PORT_CAN_RXDC,                /* CAN10RXSEL */
            (uint8)PORT_CAN_RXDA,                /* CAN11RXSEL */
            (uint8)PORT_CAN_RXDC,                /* CAN12RXSEL */
            (uint8)PORT_RXRESERVE,               /* RESERVE    */
            (uint8)PORT_RXRESERVE,               /* RESERVE    */
            (uint8)PORT_RXRESERVE,               /* RESERVE    */
            (uint8)PORT_RXRESERVE,               /* RESERVE    */
            (uint8)PORT_RXRESERVE                /* RESERVE    */
        }
    },
    {/* RxMux: 2 */
        {
            /*            DSADCISEL0           */
            (uint8)PORT_RXRESERVE,               /* TR0SEL */
            (uint8)PORT_RXRESERVE,               /* TR1SEL */
            (uint8)PORT_RXRESERVE,               /* TR2SEL */
            (uint8)PORT_RXRESERVE,               /* TR3SEL */
            (uint8)PORT_RXRESERVE,               /* RESERVE */
            (uint8)PORT_RXRESERVE,               /* RESERVE */
            (uint8)PORT_RXRESERVE,               /* RESERVE */
            (uint8)PORT_RXRESERVE                /* RESERVE */
        }
    },
    {/* RxMux: 3 */
        {
            /*             ETHISEL0            */
            (uint8)PORT_MDIOC,                   /* MDIOSEL  */
            (uint8)PORT_REFCLKA,                 /* RXCKSEL  */
            (uint8)PORT_RXRESERVE,               /* CRSSEL   */
            (uint8)PORT_RXRESERVE,               /* COLSEL   */
            (uint8)PORT_CRSDVA,                  /* DVSEL    */
            (uint8)PORT_RXERA,                   /* RXERSEL  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE                /* RESERVE  */
        }
    },
    {/* RxMux: 4 */
        {
            /*             ETHISEL1            */
            (uint8)PORT_RXDxA,                   /* RXD0SEL  */
            (uint8)PORT_RXDxA,                   /* RXD1SEL  */
            (uint8)PORT_RXRESERVE,               /* RXD2SEL  */
            (uint8)PORT_RXRESERVE,               /* RXD3SEL  */
            (uint8)PORT_RXRESERVE,               /* TXCLKSEL */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE                /* RESERVE  */
        }
    },
    {/* RxMux: 5 */
        {
            /*             I2C0ISEL            */
            (uint8)PORT_SCLC,                    /* SCLSEL   */
            (uint8)PORT_SDAC,                    /* SDASEL   */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE                /* RESERVE  */
        }
    },
    {/* RxMux: 6 */
        {
            /*             ASIISEL0            */
            (uint8)PORT_ARXB,                    /* ARXSEL0 */
            (uint8)PORT_RXRESERVE,               /* ARXSEL1 */
            (uint8)PORT_ARXD,                    /* ARXSEL2 */
            (uint8)PORT_ARXC,                    /* ARXSEL3 */
            (uint8)PORT_RXRESERVE,               /* ARXSEL4 */
            (uint8)PORT_ARXB,                    /* ARXSEL5 */
            (uint8)PORT_RXRESERVE,               /* ARXSEL6 */
            (uint8)PORT_RXRESERVE                /* ARXSEL7 */
        }
    },
    {/* RxMux: 7 */
        {
            /*            ESPI0ISEL            */
            (uint8)PORT_MRSTA,                   /* MRSTSEL  */
            (uint8)PORT_RXRESERVE,               /* MTSRSEL  */
            (uint8)PORT_RXRESERVE,               /* SCLKSEL  */
            (uint8)PORT_RXRESERVE,               /* SLSISEL  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE                /* RESERVE  */
        }
    },
    {/* RxMux: 8 */
        {
            /*            ESPI1ISEL            */
            (uint8)PORT_RXRESERVE,               /* MRSTSEL  */
            (uint8)PORT_RXRESERVE,               /* MTSRSEL  */
            (uint8)PORT_RXRESERVE,               /* SCLKSEL  */
            (uint8)PORT_RXRESERVE,               /* SLSISEL  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE                /* RESERVE  */
        }
    },
    {/* RxMux: 9 */
        {
            /*            ESPI2ISEL            */
            (uint8)PORT_MRSTB,                   /* MRSTSEL  */
            (uint8)PORT_RXRESERVE,               /* MTSRSEL  */
            (uint8)PORT_RXRESERVE,               /* SCLKSEL  */
            (uint8)PORT_RXRESERVE,               /* SLSISEL  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE                /* RESERVE  */
        }
    },
    {/* RxMux: 10 */
        {
            /*            ESPI3ISEL            */
            (uint8)PORT_RXRESERVE,               /* MRSTSEL  */
            (uint8)PORT_RXRESERVE,               /* MTSRSEL  */
            (uint8)PORT_RXRESERVE,               /* SCLKSEL  */
            (uint8)PORT_RXRESERVE,               /* SLSISEL  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE                /* RESERVE  */
        }
    },
    {/* RxMux: 11 */
        {
            /*            ESPI4ISEL            */
            (uint8)PORT_RXRESERVE,               /* MRSTSEL  */
            (uint8)PORT_RXRESERVE,               /* MTSRSEL  */
            (uint8)PORT_RXRESERVE,               /* SCLKSEL  */
            (uint8)PORT_RXRESERVE,               /* SLSISEL  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE                /* RESERVE  */
        }
    },
    {/* RxMux: 12 */
        {
            /*            ESPI5ISEL            */
            (uint8)PORT_RXRESERVE,               /* MRSTSEL  */
            (uint8)PORT_RXRESERVE,               /* MTSRSEL  */
            (uint8)PORT_RXRESERVE,               /* SCLKSEL  */
            (uint8)PORT_RXRESERVE,               /* SLSISEL  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE                /* RESERVE  */
        }
    },
    {/* RxMux: 13 */
        {
            /*            ESPI6ISEL            */
            (uint8)PORT_RXRESERVE,               /* MRSTSEL  */
            (uint8)PORT_RXRESERVE,               /* MTSRSEL  */
            (uint8)PORT_RXRESERVE,               /* SCLKSEL  */
            (uint8)PORT_RXRESERVE,               /* SLSISEL  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE                /* RESERVE  */
        }
    },
    {/* RxMux: 14 */
        {
            /*            ESPI7ISEL            */
            (uint8)PORT_RXRESERVE,               /* MRSTSEL  */
            (uint8)PORT_RXRESERVE,               /* MTSRSEL  */
            (uint8)PORT_RXRESERVE,               /* SCLKSEL  */
            (uint8)PORT_RXRESERVE,               /* SLSISEL  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE                /* RESERVE  */
        }
    },
    {/* RxMux: 15 */
        {
            /*            ESPI8ISEL            */
            (uint8)PORT_RXRESERVE,               /* MRSTSEL  */
            (uint8)PORT_RXRESERVE,               /* MTSRSEL  */
            (uint8)PORT_RXRESERVE,               /* SCLKSEL  */
            (uint8)PORT_RXRESERVE,               /* SLSISEL  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE,               /* RESERVE  */
            (uint8)PORT_RXRESERVE                /* RESERVE  */
        }
    },
    {/* RxMux: 16 */
        {
            /*            SENTISEL0            */
            (uint8)PORT_RXRESERVE,               /* SENT0SEL */
            (uint8)PORT_RXRESERVE,               /* SENT1SEL */
            (uint8)PORT_SENTxB,                  /* SENT2SEL */
            (uint8)PORT_SENTxB,                  /* SENT3SEL */
            (uint8)PORT_RXRESERVE,               /* SENT4SEL */
            (uint8)PORT_SENTxC,                  /* SENT5SEL */
            (uint8)PORT_SENTxB,                  /* SENT6SEL */
            (uint8)PORT_SENTxB                   /* SENT7SEL */
        }
    },
    {/* RxMux: 17 */
        {
            /*            SENTISEL8            */
            (uint8)PORT_RXRESERVE,               /* SENT8SEL */
            (uint8)PORT_SENTxC,                  /* SENT9SEL */
            (uint8)PORT_RXRESERVE,               /* RESERVE    */
            (uint8)PORT_RXRESERVE,               /* RESERVE    */
            (uint8)PORT_RXRESERVE,               /* RESERVE    */
            (uint8)PORT_RXRESERVE,               /* RESERVE    */
            (uint8)PORT_RXRESERVE,               /* RESERVE    */
            (uint8)PORT_RXRESERVE                /* RESERVE    */
        }
    },
    {/* RxMux: 18 */
        {
            /*           IOMMON0SEL0           */
            (uint8)PORT_RXRESERVE,               /* MON0SEL0 */
            (uint8)PORT_RXRESERVE,               /* MON0SEL1 */
            (uint8)PORT_RXMUX_IOMMON0_33_2,      /* MON0SEL2 */
            (uint8)PORT_RXMUX_IOMMON0_33_3,      /* MON0SEL3 */
            (uint8)PORT_RXRESERVE,               /* MON0SEL4 */
            (uint8)PORT_RXRESERVE,               /* MON0SEL5 */
            (uint8)PORT_RXRESERVE,               /* MON0SEL6 */
            (uint8)PORT_RXMUX_IOMMON0_33_7       /* MON0SEL7 */
        }
    },
    {/* RxMux: 19 */
        {
            /*           IOMMON0SEL8           */
            (uint8)PORT_RXRESERVE,               /* MON0SEL8 */
            (uint8)PORT_RXRESERVE,               /* MON0SEL9 */
            (uint8)PORT_RXRESERVE,               /* MON0SEL10 */
            (uint8)PORT_RXRESERVE,               /* MON0SEL11 */
            (uint8)PORT_RXRESERVE,               /* MON0SEL12 */
            (uint8)PORT_RXRESERVE,               /* MON0SEL13 */
            (uint8)PORT_RXRESERVE,               /* MON0SEL14 */
            (uint8)PORT_RXRESERVE                /* MON0SEL15 */
        }
    },
    {/* RxMux: 20 */
        {
            /*           IOMMON2SEL0           */
            (uint8)PORT_RXRESERVE,               /* MON2SEL0 */
            (uint8)PORT_RXRESERVE,               /* MON2SEL1 */
            (uint8)PORT_RXRESERVE,               /* MON2SEL2 */
            (uint8)PORT_RXRESERVE,               /* MON2SEL3 */
            (uint8)PORT_RXRESERVE,               /* MON2SEL4 */
            (uint8)PORT_RXMUX_IOMMON2_20_8,      /* MON2SEL5 */
            (uint8)PORT_RXMUX_IOMMON2_33_9,      /* MON2SEL6 */
            (uint8)PORT_RXMUX_IOMMON2_15_0       /* MON2SEL7 */
        }
    },
    {/* RxMux: 21 */
        {
            /*           IOMMON2SEL8           */
            (uint8)PORT_RXRESERVE,               /* MON2SEL8 */
            (uint8)PORT_RXRESERVE,               /* MON2SEL9 */
            (uint8)PORT_RXRESERVE,               /* MON2SEL10 */
            (uint8)PORT_RXRESERVE,               /* MON2SEL11 */
            (uint8)PORT_RXMUX_IOMMON2_15_2,      /* MON2SEL12 */
            (uint8)PORT_RXRESERVE,               /* MON2SEL13 */
            (uint8)PORT_RXMUX_IOMMON2_10_5,      /* MON2SEL14 */
            (uint8)PORT_RXMUX_IOMMON2_20_0       /* MON2SEL15 */
        }
    },
    {/* RxMux: 22 */
        {
            /*            DBGTRIGSEL           */
            (uint8)PORT_RXRESERVE,               /* TRIGSEL */
            (uint8)PORT_RXRESERVE,               /* RESERVE */
            (uint8)PORT_RXRESERVE,               /* RESERVE */
            (uint8)PORT_RXRESERVE,               /* RESERVE */
            (uint8)PORT_RXRESERVE,               /* RESERVE */
            (uint8)PORT_RXRESERVE,               /* RESERVE */
            (uint8)PORT_RXRESERVE,               /* RESERVE */
            (uint8)PORT_RXRESERVE                /* RESERVE */
        }
    }
};
/* Output ALT mode changeable flag */
static const Port_Pin1BitType Port_PinModeChangeControl[PORT_AVAILABEL_TOTAL_NUMBER] =
{
    {
        {
            /*      Port0: Pin Mode Change     */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P0.0 */
            (uint8)PORT_PIN_NOTENABLE,           /* P0.1 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P0.2 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P0.3 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P0.4 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P0.5 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P0.6 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P0.7 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P0.8 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P0.9 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P0.10 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P0.11 */
            (uint8)PORT_PIN_NOTENABLE,           /* P0.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P0.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P0.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P0.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*      Port1: Pin Mode Change     */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.0 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.1 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.2 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.3 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P1.4 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P1.5 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P1.6 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P1.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*      Port2: Pin Mode Change     */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P2.0 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P2.1 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P2.2 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P2.3 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P2.4 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P2.5 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P2.6 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P2.7 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P2.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*      Port10: Pin Mode Change     */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P10.0 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P10.1 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P10.2 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P10.3 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P10.4 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P10.5 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P10.6 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P10.7 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P10.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*      Port11: Pin Mode Change     */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.0 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.1 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P11.2 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P11.3 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.4 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.5 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P11.6 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.7 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.8 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P11.9 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P11.10 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P11.11 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P11.12 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P11.13 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.14 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*      Port12: Pin Mode Change     */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P12.0 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P12.1 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.2 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.3 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.4 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.5 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.6 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*      Port13: Pin Mode Change     */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P13.0 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P13.1 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P13.2 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P13.3 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.4 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.5 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.6 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*      Port14: Pin Mode Change     */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P14.0 */
            (uint8)PORT_PIN_ALT_CHANGEABLE,      /* P14.1 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P14.2 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P14.3 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P14.4 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P14.5 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P14.6 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P14.7 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P14.8 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P14.9 */
            (uint8)PORT_PIN_NOTENABLE,           /* P14.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P14.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P14.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P14.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P14.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P14.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*      Port15: Pin Mode Change     */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P15.0 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P15.1 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P15.2 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P15.3 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P15.4 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P15.5 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P15.6 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P15.7 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P15.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*      Port20: Pin Mode Change     */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P20.0 */
            (uint8)PORT_PIN_NOTENABLE,           /* P20.1 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P20.2 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P20.3 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P20.4 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P20.5 */
            (uint8)PORT_PIN_NOTENABLE,           /* P20.6 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P20.7 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P20.8 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P20.9 */
            (uint8)PORT_PIN_NOTENABLE,           /* P20.10 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P20.11 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P20.12 */
            (uint8)PORT_PIN_NOTENABLE,           /* P20.13 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P20.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P20.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*      Port21: Pin Mode Change     */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.0 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.1 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.2 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.3 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.4 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.5 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.6 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*      Port22: Pin Mode Change     */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.0 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.1 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P22.2 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.3 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.4 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.5 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.6 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P22.8 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.9 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.10 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P22.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P22.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P22.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P22.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*      Port23: Pin Mode Change     */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P23.0 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P23.1 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P23.2 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P23.3 */
            (uint8)PORT_PIN_NOTENABLE,           /* P23.4 */
            (uint8)PORT_PIN_NOTENABLE,           /* P23.5 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.6 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*      Port32: Pin Mode Change     */
            (uint8)PORT_PIN_NOTENABLE,           /* P32.0 */
            (uint8)PORT_PIN_NOTENABLE,           /* P32.1 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P32.2 */
            (uint8)PORT_PIN_NOTENABLE,           /* P32.3 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P32.4 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.5 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.6 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*      Port33: Pin Mode Change     */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P33.0 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P33.1 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P33.2 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P33.3 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P33.4 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P33.5 */
            (uint8)PORT_PIN_NOTENABLE,           /* P33.6 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P33.7 */
            (uint8)PORT_PIN_NOTENABLE,           /* P33.8 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P33.9 */
            (uint8)PORT_PIN_ALT_NOT_CHANGEABLE,  /* P33.10 */
            (uint8)PORT_PIN_NOTENABLE,           /* P33.11 */
            (uint8)PORT_PIN_NOTENABLE,           /* P33.12 */
            (uint8)PORT_PIN_NOTENABLE,           /* P33.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P33.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P33.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*      Port34: Pin Mode Change     */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.0 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.1 */
            (uint8)PORT_PIN_NOTENABLE,           /* P34.2 */
            (uint8)PORT_PIN_NOTENABLE,           /* P34.3 */
            (uint8)PORT_PIN_NOTENABLE,           /* P34.4 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.5 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.6 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*      Port40: Pin Mode Change     */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.0 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.1 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.2 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.3 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.4 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.5 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.6 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.7 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.8 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P40.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P40.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P40.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P40.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P40.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P40.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    }
};
/* Port-Pin direction changeable flag */
static const Port_Pin1BitType Port_PinDirChangeControl[PORT_AVAILABEL_TOTAL_NUMBER] =
{
    {
        {
            /*   Port0: Pin Direction Change   */
            (uint8)PORT_PIN_DIR_CHANGEABLE,      /* P0.0 */
            (uint8)PORT_PIN_NOTENABLE,           /* P0.1 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P0.2 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P0.3 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P0.4 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P0.5 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P0.6 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P0.7 */
            (uint8)PORT_PIN_DIR_CHANGEABLE,      /* P0.8 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P0.9 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P0.10 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P0.11 */
            (uint8)PORT_PIN_NOTENABLE,           /* P0.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P0.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P0.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P0.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*   Port1: Pin Direction Change   */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.0 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.1 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.2 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.3 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P1.4 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P1.5 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P1.6 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P1.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P1.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*   Port2: Pin Direction Change   */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P2.0 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P2.1 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P2.2 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P2.3 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P2.4 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P2.5 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P2.6 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P2.7 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P2.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P2.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*   Port10: Pin Direction Change   */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P10.0 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P10.1 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P10.2 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P10.3 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P10.4 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P10.5 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P10.6 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P10.7 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P10.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P10.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*   Port11: Pin Direction Change   */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.0 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.1 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P11.2 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P11.3 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.4 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.5 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P11.6 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.7 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.8 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P11.9 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P11.10 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P11.11 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P11.12 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P11.13 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.14 */
            (uint8)PORT_PIN_NOTENABLE,           /* P11.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*   Port12: Pin Direction Change   */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P12.0 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P12.1 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.2 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.3 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.4 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.5 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.6 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P12.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*   Port13: Pin Direction Change   */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P13.0 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P13.1 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P13.2 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P13.3 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.4 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.5 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.6 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P13.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*   Port14: Pin Direction Change   */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P14.0 */
            (uint8)PORT_PIN_DIR_CHANGEABLE,      /* P14.1 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P14.2 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P14.3 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P14.4 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P14.5 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P14.6 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P14.7 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P14.8 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P14.9 */
            (uint8)PORT_PIN_NOTENABLE,           /* P14.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P14.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P14.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P14.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P14.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P14.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*   Port15: Pin Direction Change   */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P15.0 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P15.1 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P15.2 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P15.3 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P15.4 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P15.5 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P15.6 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P15.7 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P15.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P15.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*   Port20: Pin Direction Change   */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P20.0 */
            (uint8)PORT_PIN_NOTENABLE,           /* P20.1 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P20.2 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P20.3 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P20.4 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P20.5 */
            (uint8)PORT_PIN_NOTENABLE,           /* P20.6 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P20.7 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P20.8 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P20.9 */
            (uint8)PORT_PIN_NOTENABLE,           /* P20.10 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P20.11 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P20.12 */
            (uint8)PORT_PIN_NOTENABLE,           /* P20.13 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P20.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P20.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*   Port21: Pin Direction Change   */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.0 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.1 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.2 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.3 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.4 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.5 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.6 */
            (uint8)PORT_PIN_NOTENABLE,           /* P21.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P21.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*   Port22: Pin Direction Change   */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.0 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.1 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P22.2 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.3 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.4 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.5 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.6 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P22.8 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.9 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.10 */
            (uint8)PORT_PIN_NOTENABLE,           /* P22.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P22.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P22.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P22.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P22.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*   Port23: Pin Direction Change   */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P23.0 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P23.1 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P23.2 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P23.3 */
            (uint8)PORT_PIN_NOTENABLE,           /* P23.4 */
            (uint8)PORT_PIN_NOTENABLE,           /* P23.5 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.6 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P23.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*   Port32: Pin Direction Change   */
            (uint8)PORT_PIN_NOTENABLE,           /* P32.0 */
            (uint8)PORT_PIN_NOTENABLE,           /* P32.1 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P32.2 */
            (uint8)PORT_PIN_NOTENABLE,           /* P32.3 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P32.4 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.5 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.6 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P32.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*   Port33: Pin Direction Change   */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P33.0 */
            (uint8)PORT_PIN_DIR_CHANGEABLE,      /* P33.1 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P33.2 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P33.3 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P33.4 */
            (uint8)PORT_PIN_DIR_CHANGEABLE,      /* P33.5 */
            (uint8)PORT_PIN_NOTENABLE,           /* P33.6 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P33.7 */
            (uint8)PORT_PIN_NOTENABLE,           /* P33.8 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P33.9 */
            (uint8)PORT_PIN_DIR_NOT_CHANGEABLE,  /* P33.10 */
            (uint8)PORT_PIN_NOTENABLE,           /* P33.11 */
            (uint8)PORT_PIN_NOTENABLE,           /* P33.12 */
            (uint8)PORT_PIN_NOTENABLE,           /* P33.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P33.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P33.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*   Port34: Pin Direction Change   */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.0 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.1 */
            (uint8)PORT_PIN_NOTENABLE,           /* P34.2 */
            (uint8)PORT_PIN_NOTENABLE,           /* P34.3 */
            (uint8)PORT_PIN_NOTENABLE,           /* P34.4 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.5 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.6 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.7 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.8 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P34.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    },
    {
        {
            /*   Port40: Pin Direction Change   */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.0 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.1 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.2 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.3 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.4 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.5 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.6 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.7 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.8 */
            (uint8)PORT_PIN_NOTENABLE,           /* P40.9 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P40.10 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P40.11 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P40.12 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P40.13 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P40.14 */
            (uint8)PORT_PIN_UNSUPPORT,           /* P40.15 */
            (uint16)PORT_RXRESERVE               /* RXRESERVE */
        }
    }
};
/* ALT mode mask supported by Port-Pin hardware */
static const Port_ALTModeType Port_PinHwSupportedAltModes[PORT_AVAILABEL_TOTAL_NUMBER] =
{
    {
        {
            /*              Port0            */
            0x002bU,        /* Alt mask: supported by Pin0 */
            0x0000U,        /* Alt mask: not enabled by Pin1 */
            0x0043U,        /* Alt mask: supported by Pin2 */
            0x0043U,        /* Alt mask: supported by Pin3 */
            0x004bU,        /* Alt mask: supported by Pin4 */
            0x007fU,        /* Alt mask: supported by Pin5 */
            0x0057U,        /* Alt mask: supported by Pin6 */
            0x0047U,        /* Alt mask: supported by Pin7 */
            0x0047U,        /* Alt mask: supported by Pin8 */
            0x0067U,        /* Alt mask: supported by Pin9 */
            0x0043U,        /* Alt mask: supported by Pin10 */
            0x0003U,        /* Alt mask: supported by Pin11 */
            0x0000U,        /* Alt mask: not enabled by Pin12 */
            0x0000U,        /* Alt mask: not supported by Pin13 */
            0x0000U,        /* Alt mask: not supported by Pin14 */
            0x0000U         /* Alt mask: not supported by Pin15 */
        }
    },
    {
        {
            /*              Port1            */
            0x0000U,        /* Alt mask: not supported by Pin0 */
            0x0000U,        /* Alt mask: not supported by Pin1 */
            0x0000U,        /* Alt mask: not supported by Pin2 */
            0x0000U,        /* Alt mask: not supported by Pin3 */
            0x0005U,        /* Alt mask: supported by Pin4 */
            0x0009U,        /* Alt mask: supported by Pin5 */
            0x0021U,        /* Alt mask: supported by Pin6 */
            0x0061U,        /* Alt mask: supported by Pin7 */
            0x0000U,        /* Alt mask: not supported by Pin8 */
            0x0000U,        /* Alt mask: not supported by Pin9 */
            0x0000U,        /* Alt mask: not supported by Pin10 */
            0x0000U,        /* Alt mask: not supported by Pin11 */
            0x0000U,        /* Alt mask: not supported by Pin12 */
            0x0000U,        /* Alt mask: not supported by Pin13 */
            0x0000U,        /* Alt mask: not supported by Pin14 */
            0x0000U         /* Alt mask: not supported by Pin15 */
        }
    },
    {
        {
            /*              Port2            */
            0x00bfU,        /* Alt mask: supported by Pin0 */
            0x009bU,        /* Alt mask: supported by Pin1 */
            0x002fU,        /* Alt mask: supported by Pin2 */
            0x000bU,        /* Alt mask: supported by Pin3 */
            0x002bU,        /* Alt mask: supported by Pin4 */
            0x002fU,        /* Alt mask: supported by Pin5 */
            0x000fU,        /* Alt mask: supported by Pin6 */
            0x004bU,        /* Alt mask: supported by Pin7 */
            0x0047U,        /* Alt mask: supported by Pin8 */
            0x0000U,        /* Alt mask: not supported by Pin9 */
            0x0000U,        /* Alt mask: not supported by Pin10 */
            0x0000U,        /* Alt mask: not supported by Pin11 */
            0x0000U,        /* Alt mask: not supported by Pin12 */
            0x0000U,        /* Alt mask: not supported by Pin13 */
            0x0000U,        /* Alt mask: not supported by Pin14 */
            0x0000U         /* Alt mask: not supported by Pin15 */
        }
    },
    {
        {
            /*              Port10            */
            0x000bU,        /* Alt mask: supported by Pin0 */
            0x003fU,        /* Alt mask: supported by Pin1 */
            0x001bU,        /* Alt mask: supported by Pin2 */
            0x005bU,        /* Alt mask: supported by Pin3 */
            0x003bU,        /* Alt mask: supported by Pin4 */
            0x001fU,        /* Alt mask: supported by Pin5 */
            0x004bU,        /* Alt mask: supported by Pin6 */
            0x004bU,        /* Alt mask: supported by Pin7 */
            0x000bU,        /* Alt mask: supported by Pin8 */
            0x0000U,        /* Alt mask: not supported by Pin9 */
            0x0000U,        /* Alt mask: not supported by Pin10 */
            0x0000U,        /* Alt mask: not supported by Pin11 */
            0x0000U,        /* Alt mask: not supported by Pin12 */
            0x0000U,        /* Alt mask: not supported by Pin13 */
            0x0000U,        /* Alt mask: not supported by Pin14 */
            0x0000U         /* Alt mask: not supported by Pin15 */
        }
    },
    {
        {
            /*              Port11            */
            0x0000U,        /* Alt mask: not enabled by Pin0 */
            0x0000U,        /* Alt mask: not enabled by Pin1 */
            0x00ffU,        /* Alt mask: supported by Pin2 */
            0x00cfU,        /* Alt mask: supported by Pin3 */
            0x0000U,        /* Alt mask: not enabled by Pin4 */
            0x0000U,        /* Alt mask: not enabled by Pin5 */
            0x00efU,        /* Alt mask: supported by Pin6 */
            0x0000U,        /* Alt mask: not enabled by Pin7 */
            0x0000U,        /* Alt mask: not enabled by Pin8 */
            0x00afU,        /* Alt mask: supported by Pin9 */
            0x009fU,        /* Alt mask: supported by Pin10 */
            0x00bfU,        /* Alt mask: supported by Pin11 */
            0x005fU,        /* Alt mask: supported by Pin12 */
            0x0007U,        /* Alt mask: supported by Pin13 */
            0x0000U,        /* Alt mask: not enabled by Pin14 */
            0x0000U         /* Alt mask: not enabled by Pin15 */
        }
    },
    {
        {
            /*              Port12            */
            0x0047U,        /* Alt mask: supported by Pin0 */
            0x0027U,        /* Alt mask: supported by Pin1 */
            0x0000U,        /* Alt mask: not supported by Pin2 */
            0x0000U,        /* Alt mask: not supported by Pin3 */
            0x0000U,        /* Alt mask: not supported by Pin4 */
            0x0000U,        /* Alt mask: not supported by Pin5 */
            0x0000U,        /* Alt mask: not supported by Pin6 */
            0x0000U,        /* Alt mask: not supported by Pin7 */
            0x0000U,        /* Alt mask: not supported by Pin8 */
            0x0000U,        /* Alt mask: not supported by Pin9 */
            0x0000U,        /* Alt mask: not supported by Pin10 */
            0x0000U,        /* Alt mask: not supported by Pin11 */
            0x0000U,        /* Alt mask: not supported by Pin12 */
            0x0000U,        /* Alt mask: not supported by Pin13 */
            0x0000U,        /* Alt mask: not supported by Pin14 */
            0x0000U         /* Alt mask: not supported by Pin15 */
        }
    },
    {
        {
            /*              Port13            */
            0x00bbU,        /* Alt mask: supported by Pin0 */
            0x006bU,        /* Alt mask: supported by Pin1 */
            0x007bU,        /* Alt mask: supported by Pin2 */
            0x002fU,        /* Alt mask: supported by Pin3 */
            0x0000U,        /* Alt mask: not supported by Pin4 */
            0x0000U,        /* Alt mask: not supported by Pin5 */
            0x0000U,        /* Alt mask: not supported by Pin6 */
            0x0000U,        /* Alt mask: not supported by Pin7 */
            0x0000U,        /* Alt mask: not supported by Pin8 */
            0x0000U,        /* Alt mask: not supported by Pin9 */
            0x0000U,        /* Alt mask: not supported by Pin10 */
            0x0000U,        /* Alt mask: not supported by Pin11 */
            0x0000U,        /* Alt mask: not supported by Pin12 */
            0x0000U,        /* Alt mask: not supported by Pin13 */
            0x0000U,        /* Alt mask: not supported by Pin14 */
            0x0000U         /* Alt mask: not supported by Pin15 */
        }
    },
    {
        {
            /*              Port14            */
            0x0027U,        /* Alt mask: supported by Pin0 */
            0x0007U,        /* Alt mask: supported by Pin1 */
            0x000fU,        /* Alt mask: supported by Pin2 */
            0x000fU,        /* Alt mask: supported by Pin3 */
            0x0043U,        /* Alt mask: supported by Pin4 */
            0x000bU,        /* Alt mask: supported by Pin5 */
            0x000fU,        /* Alt mask: supported by Pin6 */
            0x002bU,        /* Alt mask: supported by Pin7 */
            0x0003U,        /* Alt mask: supported by Pin8 */
            0x001bU,        /* Alt mask: supported by Pin9 */
            0x0000U,        /* Alt mask: not enabled by Pin10 */
            0x0000U,        /* Alt mask: not supported by Pin11 */
            0x0000U,        /* Alt mask: not supported by Pin12 */
            0x0000U,        /* Alt mask: not supported by Pin13 */
            0x0000U,        /* Alt mask: not supported by Pin14 */
            0x0000U         /* Alt mask: not supported by Pin15 */
        }
    },
    {
        {
            /*              Port15            */
            0x002fU,        /* Alt mask: supported by Pin0 */
            0x000fU,        /* Alt mask: supported by Pin1 */
            0x002fU,        /* Alt mask: supported by Pin2 */
            0x002fU,        /* Alt mask: supported by Pin3 */
            0x004fU,        /* Alt mask: supported by Pin4 */
            0x006fU,        /* Alt mask: supported by Pin5 */
            0x003fU,        /* Alt mask: supported by Pin6 */
            0x000fU,        /* Alt mask: supported by Pin7 */
            0x000fU,        /* Alt mask: supported by Pin8 */
            0x0000U,        /* Alt mask: not supported by Pin9 */
            0x0000U,        /* Alt mask: not supported by Pin10 */
            0x0000U,        /* Alt mask: not supported by Pin11 */
            0x0000U,        /* Alt mask: not supported by Pin12 */
            0x0000U,        /* Alt mask: not supported by Pin13 */
            0x0000U,        /* Alt mask: not supported by Pin14 */
            0x0000U         /* Alt mask: not supported by Pin15 */
        }
    },
    {
        {
            /*              Port20            */
            0x0087U,        /* Alt mask: supported by Pin0 */
            0x0000U,        /* Alt mask: not enabled by Pin1 */
            0x0000U,        /* Alt mask: not supported by Pin2 */
            0x001fU,        /* Alt mask: supported by Pin3 */
            0x0000U,        /* Alt mask: not supported by Pin4 */
            0x0000U,        /* Alt mask: not supported by Pin5 */
            0x0000U,        /* Alt mask: not enabled by Pin6 */
            0x002bU,        /* Alt mask: supported by Pin7 */
            0x003bU,        /* Alt mask: supported by Pin8 */
            0x001bU,        /* Alt mask: supported by Pin9 */
            0x0000U,        /* Alt mask: not enabled by Pin10 */
            0x000bU,        /* Alt mask: supported by Pin11 */
            0x001bU,        /* Alt mask: supported by Pin12 */
            0x0000U,        /* Alt mask: not enabled by Pin13 */
            0x000bU,        /* Alt mask: supported by Pin14 */
            0x0000U         /* Alt mask: not supported by Pin15 */
        }
    },
    {
        {
            /*              Port21            */
            0x0000U,        /* Alt mask: not enabled by Pin0 */
            0x0000U,        /* Alt mask: not enabled by Pin1 */
            0x0000U,        /* Alt mask: not enabled by Pin2 */
            0x0000U,        /* Alt mask: not enabled by Pin3 */
            0x0000U,        /* Alt mask: not enabled by Pin4 */
            0x0000U,        /* Alt mask: not enabled by Pin5 */
            0x0000U,        /* Alt mask: not enabled by Pin6 */
            0x0000U,        /* Alt mask: not enabled by Pin7 */
            0x0000U,        /* Alt mask: not supported by Pin8 */
            0x0000U,        /* Alt mask: not supported by Pin9 */
            0x0000U,        /* Alt mask: not supported by Pin10 */
            0x0000U,        /* Alt mask: not supported by Pin11 */
            0x0000U,        /* Alt mask: not supported by Pin12 */
            0x0000U,        /* Alt mask: not supported by Pin13 */
            0x0000U,        /* Alt mask: not supported by Pin14 */
            0x0000U         /* Alt mask: not supported by Pin15 */
        }
    },
    {
        {
            /*              Port22            */
            0x0000U,        /* Alt mask: not enabled by Pin0 */
            0x0000U,        /* Alt mask: not enabled by Pin1 */
            0x005fU,        /* Alt mask: supported by Pin2 */
            0x0000U,        /* Alt mask: not enabled by Pin3 */
            0x0000U,        /* Alt mask: not enabled by Pin4 */
            0x0000U,        /* Alt mask: not enabled by Pin5 */
            0x0000U,        /* Alt mask: not enabled by Pin6 */
            0x0000U,        /* Alt mask: not enabled by Pin7 */
            0x0000U,        /* Alt mask: not supported by Pin8 */
            0x0000U,        /* Alt mask: not enabled by Pin9 */
            0x0000U,        /* Alt mask: not enabled by Pin10 */
            0x0000U,        /* Alt mask: not enabled by Pin11 */
            0x0000U,        /* Alt mask: not supported by Pin12 */
            0x0000U,        /* Alt mask: not supported by Pin13 */
            0x0000U,        /* Alt mask: not supported by Pin14 */
            0x0000U         /* Alt mask: not supported by Pin15 */
        }
    },
    {
        {
            /*              Port23            */
            0x0043U,        /* Alt mask: supported by Pin0 */
            0x007fU,        /* Alt mask: supported by Pin1 */
            0x0063U,        /* Alt mask: supported by Pin2 */
            0x0047U,        /* Alt mask: supported by Pin3 */
            0x0000U,        /* Alt mask: not enabled by Pin4 */
            0x0000U,        /* Alt mask: not enabled by Pin5 */
            0x0000U,        /* Alt mask: not supported by Pin6 */
            0x0000U,        /* Alt mask: not supported by Pin7 */
            0x0000U,        /* Alt mask: not supported by Pin8 */
            0x0000U,        /* Alt mask: not supported by Pin9 */
            0x0000U,        /* Alt mask: not supported by Pin10 */
            0x0000U,        /* Alt mask: not supported by Pin11 */
            0x0000U,        /* Alt mask: not supported by Pin12 */
            0x0000U,        /* Alt mask: not supported by Pin13 */
            0x0000U,        /* Alt mask: not supported by Pin14 */
            0x0000U         /* Alt mask: not supported by Pin15 */
        }
    },
    {
        {
            /*              Port32            */
            0x0000U,        /* Alt mask: not enabled by Pin0 */
            0x0000U,        /* Alt mask: not enabled by Pin1 */
            0x0007U,        /* Alt mask: supported by Pin2 */
            0x0000U,        /* Alt mask: not enabled by Pin3 */
            0x0053U,        /* Alt mask: supported by Pin4 */
            0x0000U,        /* Alt mask: not supported by Pin5 */
            0x0000U,        /* Alt mask: not supported by Pin6 */
            0x0000U,        /* Alt mask: not supported by Pin7 */
            0x0000U,        /* Alt mask: not supported by Pin8 */
            0x0000U,        /* Alt mask: not supported by Pin9 */
            0x0000U,        /* Alt mask: not supported by Pin10 */
            0x0000U,        /* Alt mask: not supported by Pin11 */
            0x0000U,        /* Alt mask: not supported by Pin12 */
            0x0000U,        /* Alt mask: not supported by Pin13 */
            0x0000U,        /* Alt mask: not supported by Pin14 */
            0x0000U         /* Alt mask: not supported by Pin15 */
        }
    },
    {
        {
            /*              Port33            */
            0x0007U,        /* Alt mask: supported by Pin0 */
            0x000bU,        /* Alt mask: supported by Pin1 */
            0x000bU,        /* Alt mask: supported by Pin2 */
            0x000bU,        /* Alt mask: supported by Pin3 */
            0x004bU,        /* Alt mask: supported by Pin4 */
            0x000fU,        /* Alt mask: supported by Pin5 */
            0x0000U,        /* Alt mask: not enabled by Pin6 */
            0x000bU,        /* Alt mask: supported by Pin7 */
            0x0000U,        /* Alt mask: not enabled by Pin8 */
            0x006fU,        /* Alt mask: supported by Pin9 */
            0x000fU,        /* Alt mask: supported by Pin10 */
            0x0000U,        /* Alt mask: not enabled by Pin11 */
            0x0000U,        /* Alt mask: not enabled by Pin12 */
            0x0000U,        /* Alt mask: not enabled by Pin13 */
            0x0000U,        /* Alt mask: not supported by Pin14 */
            0x0000U         /* Alt mask: not supported by Pin15 */
        }
    },
    {
        {
            /*              Port34            */
            0x0000U,        /* Alt mask: not supported by Pin0 */
            0x0000U,        /* Alt mask: not supported by Pin1 */
            0x0000U,        /* Alt mask: not enabled by Pin2 */
            0x0000U,        /* Alt mask: not enabled by Pin3 */
            0x0000U,        /* Alt mask: not enabled by Pin4 */
            0x0000U,        /* Alt mask: not supported by Pin5 */
            0x0000U,        /* Alt mask: not supported by Pin6 */
            0x0000U,        /* Alt mask: not supported by Pin7 */
            0x0000U,        /* Alt mask: not supported by Pin8 */
            0x0000U,        /* Alt mask: not supported by Pin9 */
            0x0000U,        /* Alt mask: not supported by Pin10 */
            0x0000U,        /* Alt mask: not supported by Pin11 */
            0x0000U,        /* Alt mask: not supported by Pin12 */
            0x0000U,        /* Alt mask: not supported by Pin13 */
            0x0000U,        /* Alt mask: not supported by Pin14 */
            0x0000U         /* Alt mask: not supported by Pin15 */
        }
    },
    {
        {
            /*         Port40 ReadOnly        */
            0x0000U,        /* Pin0 */
            0x0000U,        /* Pin1 */
            0x0000U,        /* Pin2 */
            0x0000U,        /* Pin3 */
            0x0000U,        /* Pin4 */
            0x0000U,        /* Pin5 */
            0x0000U,        /* Pin6 */
            0x0000U,        /* Pin7 */
            0x0000U,        /* Pin8 */
            0x0000U,        /* Pin9 */
            0x0000U,        /* Pin10 */
            0x0000U,        /* Pin11 */
            0x0000U,        /* Pin12 */
            0x0000U,        /* Pin13 */
            0x0000U,        /* Pin14 */
            0x0000U         /* Pin15 */
        }
    }
};

/* Port-Pin LVDS Pair configuration information structure */
static const Port_LVDSPairType Port_PinLVDSPairConfig[2] =
{
    {
        13,        /* LVDS PortNumber */
        0,         /* LVDS PinNumber0 */
        1,         /* LVDS PinNumber1 */
        0,         /* LVDS LVDSR_Pair Number */
        /* LVDSR register configuration value */
        ((uint8)PORT_LVDS | (uint8)PORT_LVDS_RTERM_DISABLE | (uint8)PORT_LDVS_CURRENT_SWING_LEVEL3 |
         (uint8)PORT_LDVS_CURRENT_RATIO_POSITIVE_0 | (uint8)PORT_LDVS_BIAS_VOL_INTERNAL_SHARE)
    },
    {
        13,        /* LVDS PortNumber */
        2,         /* LVDS PinNumber0 */
        3,         /* LVDS PinNumber1 */
        1,         /* LVDS LVDSR_Pair Number */
        /* LVDSR register configuration value */
        ((uint8)PORT_LVDS | (uint8)PORT_LVDS_RTERM_DISABLE | (uint8)PORT_LDVS_CURRENT_SWING_LEVEL3 |
         (uint8)PORT_LDVS_CURRENT_RATIO_POSITIVE_0 | (uint8)PORT_LDVS_BIAS_VOL_INTERNAL_SHARE)
    } 
};

/* Port-Pin LVDS configuration information structure */
static const Port_LVDSType Port_PinLVDSConfig =
{
    &Port_PinLVDSPairConfig[0],
    2U     /* LVDS Pair Total Number */
};

/* Mask of valid Pins in the Port group */
static const uint16 Port_AvailablePins[PORT_AVAILABEL_TOTAL_NUMBER] =
{
    0x1fffU,        /* Port0 */
    0x00f0U,        /* Port1 */
    0x01ffU,        /* Port2 */
    0x01ffU,        /* Port10 */
    0xffffU,        /* Port11 */
    0x0003U,        /* Port12 */
    0x000fU,        /* Port13 */
    0x07ffU,        /* Port14 */
    0x01ffU,        /* Port15 */
    0x7fcbU,        /* Port20 */
    0x00ffU,        /* Port21 */
    0x0effU,        /* Port22 */
    0x003fU,        /* Port23 */
    0x001fU,        /* Port32 */
    0x3fffU,        /* Port33 */
    0x001cU,        /* Port34 */
    0x03ffU         /* Port40 */
};

/* The index of the Port group in the current configuration */
static const uint8 Port_AvailablePortIndexMap[PORT_MAX_NUMBER] =
{
    0x00U,          /* Port0 */
    0x01U,          /* Port1 */
    0x02U,          /* Port2 */
    0xFFU,          /* Port3 UnSupport*/
    0xFFU,          /* Port4 UnSupport*/
    0xFFU,          /* Port5 UnSupport*/
    0xFFU,          /* Port6 UnSupport*/
    0xFFU,          /* Port7 UnSupport*/
    0xFFU,          /* Port8 UnSupport*/
    0xFFU,          /* Port9 UnSupport*/
    0x03U,          /* Port10 */
    0x04U,          /* Port11 */
    0x05U,          /* Port12 */
    0x06U,          /* Port13 */
    0x07U,          /* Port14 */
    0x08U,          /* Port15 */
    0xFFU,          /* Port16 UnSupport*/
    0xFFU,          /* Port17 UnSupport*/
    0xFFU,          /* Port18 UnSupport*/
    0xFFU,          /* Port19 UnSupport*/
    0x09U,          /* Port20 */
    0x0AU,          /* Port21 */
    0x0BU,          /* Port22 */
    0x0CU,          /* Port23 */
    0xFFU,          /* Port24 UnSupport*/
    0xFFU,          /* Port25 UnSupport*/
    0xFFU,          /* Port26 UnSupport*/
    0xFFU,          /* Port27 UnSupport*/
    0xFFU,          /* Port28 UnSupport*/
    0xFFU,          /* Port29 UnSupport*/
    0xFFU,          /* Port30 UnSupport*/
    0xFFU,          /* Port31 UnSupport*/
    0x0DU,          /* Port32 */
    0x0EU,          /* Port33 */
    0x0FU,          /* Port34 */
    0xFFU,          /* Port35 UnSupport*/
    0xFFU,          /* Port36 UnSupport*/
    0xFFU,          /* Port37 UnSupport*/
    0xFFU,          /* Port38 UnSupport*/
    0xFFU,          /* Port39 UnSupport*/
    0x10U           /* Port40 ReadOnly*/
};

/* The available Port hardware base address */
static PORT_MODULE *const Port_BaseAddress[PORT_AVAILABEL_TOTAL_NUMBER] =
{
    /* #Violation: Port_PBcfg_c_REF_4 */
    PORT_MODULE_P00,        /* Port0 */
    /* #Violation: Port_PBcfg_c_REF_4 */
    PORT_MODULE_P01,        /* Port1 */
    /* #Violation: Port_PBcfg_c_REF_4 */
    PORT_MODULE_P02,        /* Port2 */
    /* #Violation: Port_PBcfg_c_REF_4 */
    PORT_MODULE_P10,        /* Port10 */
    /* #Violation: Port_PBcfg_c_REF_4 */
    PORT_MODULE_P11,        /* Port11 */
    /* #Violation: Port_PBcfg_c_REF_4 */
    PORT_MODULE_P12,        /* Port12 */
    /* #Violation: Port_PBcfg_c_REF_4 */
    PORT_MODULE_P13,        /* Port13 */
    /* #Violation: Port_PBcfg_c_REF_4 */
    PORT_MODULE_P14,        /* Port14 */
    /* #Violation: Port_PBcfg_c_REF_4 */
    PORT_MODULE_P15,        /* Port15 */
    /* #Violation: Port_PBcfg_c_REF_4 */
    PORT_MODULE_P20,        /* Port20 */
    /* #Violation: Port_PBcfg_c_REF_4 */
    PORT_MODULE_P21,        /* Port21 */
    /* #Violation: Port_PBcfg_c_REF_4 */
    PORT_MODULE_P22,        /* Port22 */
    /* #Violation: Port_PBcfg_c_REF_4 */
    PORT_MODULE_P23,        /* Port23 */
    /* #Violation: Port_PBcfg_c_REF_4 */
    PORT_MODULE_P32,        /* Port32 */
    /* #Violation: Port_PBcfg_c_REF_4 */
    PORT_MODULE_P33,        /* Port33 */
    /* #Violation: Port_PBcfg_c_REF_4 */
    PORT_MODULE_P34,        /* Port34 */
    /* #Violation: Port_PBcfg_c_REF_4 */
    PORT_MODULE_P40         /* Port40 */
};

/* Port-Pin global configuration information structure */
/* #Violation: Port_PBcfg_c_REF_2 */
const Port_ConfigType Port_ConfigSet[PORT_CONFIG_COUNT] =
{
    {
        /* Configure Port-Pin Direction, Push-pull&Open-drain, Output Function Select(CTR0/4/8/12) */
        &Port_PinControlData[0],
        /* Configure Port-Pin initial output Level (ODR) */
        &Port_PinInitLevel[0],
        /* Configure Port-Pin TTL level working mode */
        NULL_PTR,
        /* Configure Port-Pin Pad level, slew-rate, Pad input mode, Pad driver Select (DSR0/8) */
        &Port_PinPadControlData[0],
        /* Configure Port-Pin digital function enable (DFR) */
        &Port_PinDigitalEnable[0],
        /* Configure Port-Pin hardware control select (HWCR) */
        &Port_PinHwSelect[0],
        /* Configure Port-Pin Pull_Up/Pull_Down (PSR) */
        &Port_PinPullSelect[0],
        /* Configure Port-Pin input multiplexing function selection */
        &RXMUX_SelectData[0],
        /* Port pin run time mode changeable(ALT)*/
        &Port_PinModeChangeControl[0],
        /* Port pin run time direction changeable */
        &Port_PinDirChangeControl[0],
        /* Port pin Hardware supported ALT mode Mask */
        &Port_PinHwSupportedAltModes[0],
        /* Port Pin supported LVDS configuration information structure */
        &Port_PinLVDSConfig,
        /* Mask of valid Pins in the Port group */
        &Port_AvailablePins[0],
        /* The index of the Port group in the current configuration */
        &Port_AvailablePortIndexMap[0],
        /* The available Port hardware base address */
        &Port_BaseAddress[0]
    }
};
/* #Violation: Port_PBcfg_c_REF_1 */
#define PORT_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Port_PBcfg_c_REF_3 */
#include "Port_MemMap.h"
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
