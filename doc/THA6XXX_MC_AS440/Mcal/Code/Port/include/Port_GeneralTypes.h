/****************************************************************************************************
 *
****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Port_GeneralTypes.h
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : GPIO
 *
 *   brief                 : This file contains all type definitions of Port Driver
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
*#Port_GeneralTypes_h_REF_1:MISRAC2012-Dir-4.8; 
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#Port_GeneralTypes_h_REF_2:MISRAC2012-Rule-2.3; 
* Justification: Reserved types are defined in AUTOSAR specifications.
*
*#Port_GeneralTypes_h_REF_3:MISRAC2012-Rule-19.2; 
* Justification: Using unions for bit-field access to registers.
*
*#Port_GeneralTypes_h_REF_4:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*/
#ifndef PORT_GENERALTYPES_H_
#define PORT_GENERALTYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"
#include "regtypes.h"
#include "Port_Cfg.h"
#include "port_register.h"
/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
/*  SWS_Port_00229]:
    Data type for the symbolic name of a port pin.
    Range: 0 - <number of port pins:>
           Shall cover all available port pins.
           The type should be chosen for the specific MCU platform (best performance).
    SWS_Port_00013:
    The type Port_PinType shall be used for the symbolic name of a Port Pin.
    SWS_Port_00219:
    The type Port_PinType shall be uint8, uint16 or uint32 based on the specific MCU platform.
    Note: The user shall use the symbolic names provided by the configuration tool.
*/
typedef uint16 Port_PinType;

/*  SWS_Port_00231:
    Different port pin modes.
    Range: Implementation specific
           As several port pin modes shall be configurable on one pin, the range shall be determined
           by the implementation.
    SWS_Port_00124:
    A port pin shall be configurable with a number of port pin modes (type Port_PinModeType).
    SWS_Port_00221:
    The type Port_PinModeType shall be uint8, uint16 or uint32.
*/
typedef uint8 Port_PinModeType;
/****************************************************************************************************
**                          Global Enumration Definitions                                          **
****************************************************************************************************/
/*  SWS_Port_00230:
    Possible directions of a port pin.
    Range: PORT_PIN_IN        Sets port pin as input.
           PORT_PIN_OUT       Sets port pin as output.
    SWS_Port_00046:
    The type Port_PinDirectionType is a type for defining the direction of a Port Pin.
    SWS_Port_00220:
    The type Port_PinDirectionType shall be of enumeration type having range as
    PORT_PIN_IN and PORT_PIN_OUT.
*/
typedef enum
{
    PORT_PIN_IN    = 0x00U,   /* Pin direction is input. */
    PORT_PIN_OUT   = 0x40U,   /* Pin direction is output. */
    PORT_PIN_INOUT = 0x40U    /* Pin direction is input and output. */
} Port_PinDirectionType;

/* ECUC_Port_00131:
    Pre-processor switch to enable / disable the use of the function Port_SetPinDirection(). 
    TRUE: Enabled - Function Port_SetPinDirection() is available. 
    FALSE: Disabled - Function Port_SetPinDirection() is not available.
   ECUC_Port_00126:
    Parameter to indicate if the direction is changeable on a port pin during runtime. 
    true: Port Pin direction changeable enabled. 
    false: Port Pin direction changeable disabled.
Configuration Options: to define whether pin direction can be changed during runtime or not
*/
typedef enum
{
    PORT_PIN_DIR_NOT_CHANGEABLE = 0x00U, /* Define Pin direction cannot be changed */
    PORT_PIN_DIR_CHANGEABLE     = 0x01U  /* Define Pin direction cannot be changed */
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_DirChangeableType;

/* ECUC_Port_00132:
    Pre-processor switch to enable / disable the use of the function Port_SetPinMode()
    true: Enabled - Function Port_SetPinMode() is available. 
    false: Disabled - Function Port_SetPinMode() is not available.
   ECUC_Port_00134:
    Parameter to indicate if the mode is changeable on a port pin during runtime. 
    True: Port Pin mode changeable allowed. 
    False: Port Pin mode changeable not permitted.
Configuration Options: to define whether pin ALT mode can be changed during runtime or not
*/
typedef enum
{
    PORT_PIN_ALT_NOT_CHANGEABLE = 0x00U, /* Define Pin ALT mode cannot be changed */
    PORT_PIN_ALT_CHANGEABLE     = 0x01U  /* Define Pin ALT mode can    be changed */
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_AltModeChangeableType;

/* ECUC_Port_00128:
    Port pin mode from mode list for use with Port_Init() function.
Type definition for Port pin output ALT mode
*/
typedef enum
{
    PORT_OUTPUTALT_O0 = 0U, /* Port multiplexer select 0 */
    PORT_OUTPUTALT_O1,      /* Port multiplexer select 1 */
    PORT_OUTPUTALT_O2,      /* Port multiplexer select 2 */
    PORT_OUTPUTALT_O3,      /* Port multiplexer select 3 */
    PORT_OUTPUTALT_O4,      /* Port multiplexer select 4 */
    PORT_OUTPUTALT_O5,      /* Port multiplexer select 5 */
    PORT_OUTPUTALT_O6,      /* Port multiplexer select 6 */
    PORT_OUTPUTALT_O7,      /* Port multiplexer select 7 */
    PORT_OUTPUTALT_O8,      /* Port multiplexer select 8 */
    PORT_OUTPUTALT_O9       /* Port multiplexer select 9 */
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_OutputAltModeType;

/* ECUC_Port_00129:
    Port Pin Level value from Port pin list.
Configuration Options: to define output Pin initial level high or low
*/
typedef enum
{
    PORT_PIN_LEVEL_LOW  = 0x00U, /* Pin output data Low , ODR-write 0(1bit * 16,RSV).*/
    PORT_PIN_LEVEL_HIGH = 0x01U  /* Pin output data High, ODR-write 1(1bit * 16,RSV).*/
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_InitLevelType;

/*
Type definition PORT module initialization state
*/
typedef enum
{
    PORT_UNINITIALIZED = 0x00U, /* Port module isn't init. */
    PORT_INITIALIZED   = 0x01U  /* Port module already init. */
} Port_DriverStateType;

/*
Enum to define default configuration
*/
typedef enum
{
    PORT_PIN_UNSUPPORT      = 0x00U,  /* The hardware does not support the current Port-Pin */
    PORT_PIN_NOTENABLE      = 0x00U,  /* The user has not enabled the current Port-Pin      */
    PORT_PIN_UNSUPPORTPSR   = 0x03U,  /* The hardware does not support the current Port-Pin */
    PORT_RXRESERVE          = 0x00U   /* RXMUX: Receive select for Reserve.                 */
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_AvailabeType;

/*
Macro to define Pin output push-pull/open-drain mode
*/
typedef enum
{
    PORT_OUTPUT_PUSHPULL  = 0x00U, /* Pin output mode push_pull,  CTRx-bit5-write 0(8bit * 4). */
    PORT_OUTPUT_OPENDRAIN = 0x20U  /* Pin output mode open_drain, CTRx-bit5-write 1(8bit * 4). */
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_OutputModeType;

/*
Configuration Options: Pin Level
*/
typedef enum
{
    PORT_PDR_AL_AUTOMOTIVE_LEVEL  = 0x00U,  /* Level mode AL,  DSRx-bit3-write 0(4bit * 8). */
    PORT_PDR_TTL_AUTOMOTIVE_LEVEL = 0x08U,  /* Level mode TTL, DSRx-bit3-write 1(4bit * 8). */
#if defined(THA6_THA6104) || defined (THA6_THA6412)
    PORT_PDR_DTTL_AUTOMOTIVE_LEVEL = 0x00U, /* Level mode TTL, DSRx-bit3-write 1(4bit * 8). */
    PORT_PDR_STTL_AUTOMOTIVE_LEVEL = 0x01U  /* Level mode TTL, DSRx-bit3-write 1(4bit * 8). */
#endif
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_LevelModeType;

/*
Configuration Options: Slew-rate
*/
typedef enum
{
    PORT_SLEWRATEMODE_DISABLE = 0x00U, /* Slew-rate  enable, DSRx-bit2-write 0(4bit * 8). */
    PORT_SLEWRATEMODE_ENABLE  = 0x04U  /* Slew-rate disable, DSRx-bit2-write 1(4bit * 8). */
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_SlewRateEnableType;

/*
Configuration Options: Pin input mode selection
*/
typedef enum
{
    PORT_SCHMIDT_LEVEL_MODE = 0x00U, /* Input mode schmidt, DSRx-bit1-write 0(4bit * 8). */
    PORT_CMOS_LEVEL_MODE    = 0x02U  /* Input mode cmos   , DSRx-bit1-write 1(4bit * 8). */
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_InputLevelModeType;

/*
Configuration Options: Pin driver strength
*/
typedef enum
{
    PORT_DRIVER_STRENGTH_LOW  = 0x00U, /* Pin driver strength Low , DSRx-bit0-write 0(4bit * 8). */
    PORT_DRIVER_STRENGTH_HIGH = 0x01U  /* Pin driver strength High, DSRx-bit0-write 1(4bit * 8). */
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_DriverStrengthType;

/*
Configuration Options: Pin digital and analog function enable
*/
typedef enum
{
    PORT_FUNCTION_MODE_DIGITAL = 0x00U, /* Digital function  enable, DFR-write 0(2bit * 16).*/
    PORT_FUNCTION_MODE_ANALOG  = 0x03U  /* Digital function disable, DFR-write 3(2bit * 16).*/
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_DigitalEnableCtrlType;

/*
Enum for Port Pin controller port(default) or peripheral
*/
typedef enum
{
    PORT_CONTROLLER_VIA_PORT       = 0x00U, /* Pereipheral control disable, HWCR-write 0(2bit * 16).*/
    PORT_CONTROLLER_VIA_PERIPHERAL = 0x03U  /* Pereipheral control enable , HWCR-write 3(2bit * 16).*/
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_ControllerType;

/*
Configuration Options: Pin input pull-down mode
*/
typedef enum
{
    PORT_INPUTMODE_NONE     = 0x00U, /* Not Pull_Down select, PSR-write 0(2bit * 16).*/
    PORT_INPUTMODE_PULLDOWN = 0x02U, /* Pull_Down     select, PSR-write 2(2bit * 16).*/
    PORT_INPUTMODE_PULLUP   = 0x03U  /* Pull_Up       select, PSR-write 3(2bit * 16).*/
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_InputModeType;

/*
Internal termination resistor RTERM enable
*/
typedef enum
{
    PORT_LVDS_RTERM_DISABLE = 0x000UL, /* LVDS internal RTERM disable, LVDSR-bit13-write 0 */
    PORT_LVDS_RTERM_ENABLE  = 0x800UL  /* LVDS internal RTERM  enable, LVDSR-bit13-write 1 */
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_LvdsRtermCtrlType;

/*
For LVDS Vcom Output Voltage Setting
*/
typedef enum
{
    PORT_SUBLDVS_RTERM_83ohm  = 0x000UL, /* LVDS Terminal resistance value 83ohm , LVDSR-bit[8:10]-write 0 */
    PORT_SUBLDVS_RTERM_87ohm  = 0x100UL, /* LVDS Terminal resistance value 87ohm , LVDSR-bit[8:10]-write 1 */
    PORT_SUBLDVS_RTERM_92ohm  = 0x200UL, /* LVDS Terminal resistance value 92ohm , LVDSR-bit[8:10]-write 2 */
    PORT_SUBLDVS_RTERM_97ohm  = 0x300UL, /* LVDS Terminal resistance value 97ohm , LVDSR-bit[8:10]-write 3 */
    PORT_LDVS_RTERM_103ohm    = 0x400UL, /* LVDS Terminal resistance value 103ohm, LVDSR-bit[8:10]-write 4 */
    PORT_LDVS_RTERM_109ohm    = 0x500UL, /* LVDS Terminal resistance value 109ohm, LVDSR-bit[8:10]-write 5 */
    PORT_LDVS_RTERM_117ohm    = 0x600UL, /* LVDS Terminal resistance value 117ohm, LVDSR-bit[8:10]-write 6 */
    PORT_LDVS_RTERM_125ohm    = 0x700UL  /* LVDS Terminal resistance value 125ohm, LVDSR-bit[8:10]-write 7 */
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_LvdsRtermSelectType;

/*
For LVDS current and swing Setting
*/
typedef enum
{
    PORT_LDVS_CURRENT_SWING_LEVEL0 = 0x00UL,     /* LVDS current and swing value LEVEL0, LVDSR-bit[6:7]-write 0 */
    PORT_LDVS_CURRENT_SWING_LEVEL1 = 0x40UL,     /* LVDS current and swing value LEVEL1, LVDSR-bit[6:7]-write 1 */
    PORT_LDVS_CURRENT_SWING_LEVEL2 = 0x80UL,     /* LVDS current and swing value LEVEL2, LVDSR-bit[6:7]-write 2 */
    PORT_LDVS_CURRENT_SWING_LEVEL3 = 0xC0UL      /* LVDS current and swing value LEVEL3, LVDSR-bit[6:7]-write 3 */
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_LvdsSwingSelectType;

/*
For LVDS output current ratio trim Setting
*/
typedef enum
{
    PORT_LDVS_CURRENT_RATIO_NEGATIVE_8  = 0x00UL, /* LVDS output current ratio trim -8 , LVDSR-bit[4:5]-write 0 */
    PORT_LDVS_CURRENT_RATIO_POSITIVE_0  = 0x10UL, /* LVDS output current ratio trim  0 , LVDSR-bit[4:5]-write 1 */
    PORT_LDVS_CURRENT_RATIO_POSITIVE_9  = 0x20UL, /* LVDS output current ratio trim  9 , LVDSR-bit[4:5]-write 2 */
    PORT_LDVS_CURRENT_RATIO_POSITIVE_20 = 0x30UL  /* LVDS output current ratio trim 20, LVDSR-bit[4:5]-write 3 */
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_LvdsCurrentRatioSelectType;

/*
For LVDS Bias voltage selection
*/
typedef enum
{
    PORT_LDVS_BIAS_VOL_INTERNAL_SHARE  = 0x00UL, /* LVDS Bias voltage selection internal share, LVDSR-bit[0]-write 0 */
    PORT_LDVS_BIAS_VOL_EXTERNAL_INPUT  = 0x04UL  /* LVDS Bias voltage selection external input, LVDSR-bit[0]-write 1 */
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_LvdsBiasVolSelectType;

/*
LVDS working mode selection
*/
typedef enum
{
    PORT_LVDS      = 0x08UL, /* LVDS mode Select:LVDS    , LVDSR-bit3-write 1 */
    PORT_SUB_LVDS  = 0x00UL  /* LVDS mode Select:SUB_LVDS, LVDSR-bit3-write 0 */
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_LvdsModeType;

/* CAN input multiplex register configuration value. */
typedef enum
{
    PORT_CAN_RXDA = 0x00U,  /* CAN: Receive select for CAN_RXDA. */
    PORT_CAN_RXDB,          /* CAN: Receive select for CAN_RXDB. */
    PORT_CAN_RXDC,          /* CAN: Receive select for CAN_RXDC. */
    PORT_CAN_RXDD,          /* CAN: Receive select for CAN_RXDD. */
    PORT_CAN_RXDE,          /* CAN: Receive select for CAN_RXDE. */
    PORT_CAN_RXDF,          /* CAN: Receive select for CAN_RXDF. */
    PORT_CAN_RXDG,          /* CAN: Receive select for CAN_RXDG. */
    PORT_CAN_RXDH           /* CAN: Receive select for CAN_RXDH. */
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_CAN_RXMUXType;

/* DSADC input multiplex register configuration value. */
typedef enum
{
    PORT_DSADC_ITRxE = 0x04U,  /* DSADC: Receive select for DSADC_ITRxE. */
    PORT_DSADC_ITRxF           /* DSADC: Receive select for DSADC_ITRxF. */
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_DSADC_RXMUXType;

/* ETH SEL0 input multiplex register configuration value. */
typedef enum
{
    PORT_RXERA   = 0x00U,   /* ETH: Receive select for RXERA.   Reg0 [21:20]*/
    PORT_RXERB   = 0x01U,   /* ETH: Receive select for RXERB.   Reg0 [21:20]*/
    PORT_RXERC   = 0x02U,   /* ETH: Receive select for RXERC.   Reg0 [21:20]*/
    PORT_RXDVA   = 0x00U,   /* ETH: Receive select for RXDVA.   Reg0 [17:16]*/
    PORT_RXDVB   = 0x01U,   /* ETH: Receive select for RXDVB.   Reg0 [17:16]*/
    PORT_CRSDVA  = 0x00U,   /* ETH: Receive select for CRSDVA.  Reg0 [17:16]*/
    PORT_CRSDVB  = 0x01U,   /* ETH: Receive select for CRSDVB.  Reg0 [17:16]*/
    PORT_RCTLA   = 0x02U,   /* ETH: Receive select for RCTL.    Reg0 [17:16]*/
    PORT_COLA    = 0x00U,   /* ETH: Receive select for COLA.    Reg0 [13:12]*/
    PORT_CRSA    = 0x00U,   /* ETH: Receive select for CRSA.    Reg0 [ 9: 8]*/
    PORT_CRSB    = 0x01U,   /* ETH: Receive select for CRSB.    Reg0 [ 9: 8]*/
    PORT_REFCLKA = 0x00U,   /* ETH: Receive select for REFCLKA. Reg0 [ 5: 4]*/
    PORT_RXCLKA  = 0x00U,   /* ETH: Receive select for RXCLKA.  Reg0 [ 5: 4]*/
    PORT_RXCLKB  = 0x01U,   /* ETH: Receive select for RXCLKB.  Reg0 [ 5: 4]*/
    PORT_RXCLKC  = 0x02U,   /* ETH: Receive select for RXCLKC.  Reg0 [ 5: 4]*/
    PORT_MDIOA   = 0x00U,   /* ETH: Receive select for MDIOA.   Reg0 [ 1: 0]*/
    PORT_MDIOC   = 0x02U,   /* ETH: Receive select for MDIOC.   Reg0 [ 1: 0]*/
    PORT_MDIOD   = 0x03U    /* ETH: Receive select for MDIOD.   Reg0 [ 1: 0]*/
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_ETHSEL0_RXMUXType;

/* ETH SEL1 input multiplex register configuration value. */
typedef enum
{
    PORT_TXCLKA   = 0x00U,   /* ETH: Receive select for TXCLKA. Reg0 [17:16]*/
    PORT_TXCLKB   = 0x01U,   /* ETH: Receive select for TXCLKB. Reg0 [17:16]*/
    PORT_RXDxA    = 0x00U,   /* ETH: Receive select for RXDxA.  Reg0 [13:0]*/
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_ETHSEL1_RXMUXType;

/* I2C input multiplex register configuration value. */
typedef enum
{
    PORT_SDAA = 0x00U,       /* I2C: Receive select for SDAA. Reg0 [ 5: 4]*/
    PORT_SDAB = 0x01U,       /* I2C: Receive select for SDAB. Reg0 [ 5: 4]*/
    PORT_SDAC = 0x02U,       /* I2C: Receive select for SDAC. Reg0 [ 5: 4]*/
    PORT_SCLA = 0x00U,       /* I2C: Receive select for SCLA. Reg0 [ 1: 0]*/
    PORT_SCLB = 0x01U,       /* I2C: Receive select for SCLB. Reg0 [ 1: 0]*/
    PORT_SCLC = 0x02U        /* I2C: Receive select for SCLC. Reg0 [ 1: 0]*/
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_I2C_RXMUXType;

/* ASI input multiplex register configuration value. */
typedef enum
{
    PORT_ARXA = 0x00U,       /* ASI: Receive select for ARXA. */
    PORT_ARXB,               /* ASI: Receive select for ARXB. */
    PORT_ARXC,               /* ASI: Receive select for ARXC. */
    PORT_ARXD,               /* ASI: Receive select for ARXD. */
    PORT_ARXE,               /* ASI: Receive select for ARXE. */
    PORT_ARXF,               /* ASI: Receive select for ARXF. */
    PORT_ARXG,               /* ASI: Receive select for ARXG. */
    PORT_ARXH                /* ASI: Receive select for ARXH. */
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_ASI_RXMUXType;

/* ESPI input multiplex register SLSI configuration value. */
typedef enum
{
    PORT_SLSIA = 0x00U,      /* ESPI: Receive SLSI select for SLSIA. */
    PORT_SLSIB,              /* ESPI: Receive SLSI select for SLSIB. */
    PORT_SLSIC,              /* ESPI: Receive SLSI select for SLSIC. */
    PORT_SLSID,              /* ESPI: Receive SLSI select for SLSID. */
    PORT_SLSIE,              /* ESPI: Receive SLSI select for SLSIE. */
    PORT_SLSIF,              /* ESPI: Receive SLSI select for SLSIF. */
    PORT_SLSIG,              /* ESPI: Receive SLSI select for SLSIG. */
    PORT_SLSIH               /* ESPI: Receive SLSI select for SLSIH. */
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_ESPI_SLSI_RXMUXType;

/* ESPI input multiplex register SCLK configuration value. */
typedef enum
{
    PORT_SCLKA = 0x00U,      /* ESPI: Receive SCLK select for SCLKA. */
    PORT_SCLKB,              /* ESPI: Receive SCLK select for SCLKB. */
    PORT_SCLKC,              /* ESPI: Receive SCLK select for SCLKC. */
    PORT_SCLKD,              /* ESPI: Receive SCLK select for SCLKD. */
    PORT_SCLKE,              /* ESPI: Receive SCLK select for SCLKE. */
    PORT_SCLKF,              /* ESPI: Receive SCLK select for SCLKF. */
    PORT_SCLKG,              /* ESPI: Receive SCLK select for SCLKG. */
    PORT_SCLKH               /* ESPI: Receive SCLK select for SCLKH. */
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_ESPI_SCLK_RXMUXType;

/* ESPI input multiplex register MTSR configuration value. */
typedef enum
{
    PORT_MTSRA = 0x00U,      /* ESPI: Receive MTSR select for MTSRA. */
    PORT_MTSRB,              /* ESPI: Receive MTSR select for MTSRB. */
    PORT_MTSRC,              /* ESPI: Receive MTSR select for MTSRC. */
    PORT_MTSRD,              /* ESPI: Receive MTSR select for MTSRD. */
    PORT_MTSRE,              /* ESPI: Receive MTSR select for MTSRE. */
    PORT_MTSRF,              /* ESPI: Receive MTSR select for MTSRF. */
    PORT_MTSRG,              /* ESPI: Receive MTSR select for MTSRG. */
    PORT_MTSRH               /* ESPI: Receive MTSR select for MTSRH. */
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_ESPI_MTSR_RXMUXType;

/* ESPI input multiplex register MRST configuration value. */
typedef enum
{
    PORT_MRSTA  = 0x00U,      /* ESPI: Receive MRST select for MRSTA. */
    PORT_MRSTB  = 0x01U,      /* ESPI: Receive MRST select for MRSTB. */
    PORT_MRSTC  = 0x02U,      /* ESPI: Receive MRST select for MRSTC. */
    PORT_MRSTD  = 0x03U,      /* ESPI: Receive MRST select for MRSTD. */
    PORT_MRSTE  = 0x04U,      /* ESPI: Receive MRST select for MRSTE. */
    PORT_MRSTF  = 0x05U,      /* ESPI: Receive MRST select for MRSTF. */
    PORT_MRSTG  = 0x06U,      /* ESPI: Receive MRST select for MRSTG. */
    PORT_MRSTH  = 0x07U,      /* ESPI: Receive MRST select for MRSTH. */
    PORT_MRSTI  = 0x00U,      /* ESPI: Receive MRST select for MRSTI. */
    PORT_MRSTJ  = 0x01U,      /* ESPI: Receive MRST select for MRSTJ. */
    PORT_MRSTK  = 0x02U,      /* ESPI: Receive MRST select for MRSTK. */
    PORT_MRSTL  = 0x03U,      /* ESPI: Receive MRST select for MRSTL. */
    PORT_MRSTM  = 0x04U,      /* ESPI: Receive MRST select for MRSTM. */
    PORT_MRSTN  = 0x05U,      /* ESPI: Receive MRST select for MRSTN. */
    PORT_MRSTO  = 0x06U,      /* ESPI: Receive MRST select for MRSTO. */
    PORT_MRSTP  = 0x07U,      /* ESPI: Receive MRST select for MRSTP. */
    PORT_MRSTQ  = 0x00U,      /* ESPI: Receive MRST select for MRSTQ. */
    PORT_MRSTR  = 0x01U,      /* ESPI: Receive MRST select for MRSTR. */
    PORT_MRSTS  = 0x02U,      /* ESPI: Receive MRST select for MRSTS. */
    PORT_MRSTT  = 0x03U,      /* ESPI: Receive MRST select for MRSTT. */
    PORT_MRSTU  = 0x04U,      /* ESPI: Receive MRST select for MRSTU. */
    PORT_MRSTV  = 0x05U,      /* ESPI: Receive MRST select for MRSTV. */
    PORT_MRSTAH = 0x00U,      /* ESPI: Receive MRST select for MRSTA~MRSTH. */
    PORT_MRSTIP = 0x01U,      /* ESPI: Receive MRST select for MRSTI~MRSTP. */
    PORT_MRSTQV = 0x02U       /* ESPI: Receive MRST select for MRSTQ~MRSTV. */
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_ESPI_MRST_RXMUXType;

/* SENT input multiplex register configuration value. */
typedef enum
{
    PORT_SENTxA = 0x00U,     /* SENT: Receive select for SENTxA. */
    PORT_SENTxB,             /* SENT: Receive select for SENTxB. */
    PORT_SENTxC              /* SENT: Receive select for SENTxC. */
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_SENT_RXMUXType;

/* Debug Trace input multiplex register configuration value. */
typedef enum
{
    PORT_TRIG_IO = 0x00U,     /* Debug Trace: Receive select for TRIG_IO. */
    PORT_TRIG_IN,             /* Debug Trace: Receive select for TRIG_IN. */
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_DBG_RXMUXType;

/* PSI5 input multiplex register configuration value. */
typedef enum
{
    PORT_RXxA = 0x00U,     /* PSI5: Receive select for RXxA. */
    PORT_RXxB,             /* PSI5: Receive select for RXxB. */
    PORT_RXxC,             /* PSI5: Receive select for RXxC. */
/* #Violation: Port_GeneralTypes_h_REF_2 */
} Port_PSI5_RXMUXType;
/****************************************************************************************************
**                          Global Union Definitions                                               **
****************************************************************************************************/
/* Define type configure Port-Pin Direction, Push-pull Open-drain, Output Function Select */
/* #Violation: Port_GeneralTypes_h_REF_1 */
typedef union
/* #Violation: Port_GeneralTypes_h_REF_3 */
/* #Violation: Port_GeneralTypes_h_REF_4 */
{
    struct
    {
        uint8 PC[PIN_MAX_NUMBER];   /* Pin x control data */
    } B;

    uint32 U[PORT_CTRX_NUMBER];        /* uint32 type value register value */
} Port_PinControlDataType;

/* Shield QAC warning Message 0635: Bit fields should be defined as signed or unsigned int types. */
/* Define a register type with a bit field width of 1bit */
/* #Violation: Port_GeneralTypes_h_REF_1 */
typedef union
/* #Violation: Port_GeneralTypes_h_REF_3 */
/* #Violation: Port_GeneralTypes_h_REF_4 */
{
    struct
    {
        ureg32 Pin0       : 1;  /* Pin0  control bit field */
        ureg32 Pin1       : 1;  /* Pin1  control bit field */
        ureg32 Pin2       : 1;  /* Pin2  control bit field */
        ureg32 Pin3       : 1;  /* Pin3  control bit field */
        ureg32 Pin4       : 1;  /* Pin4  control bit field */
        ureg32 Pin5       : 1;  /* Pin5  control bit field */
        ureg32 Pin6       : 1;  /* Pin6  control bit field */
        ureg32 Pin7       : 1;  /* Pin7  control bit field */
        ureg32 Pin8       : 1;  /* Pin8  control bit field */
        ureg32 Pin9       : 1;  /* Pin9  control bit field */
        ureg32 Pin10      : 1;  /* Pin10 control bit field */
        ureg32 Pin11      : 1;  /* Pin11 control bit field */
        ureg32 Pin12      : 1;  /* Pin12 control bit field */
        ureg32 Pin13      : 1;  /* Pin13 control bit field */
        ureg32 Pin14      : 1;  /* Pin14 control bit field */
        ureg32 Pin15      : 1;  /* Pin15 control bit field */
        ureg32 Reserve0   : 16; /* reserved bit field */
    } B;

    uint32 U;                   /* uint32 type value register value */
} Port_Pin1BitType;

/* Define a register type with a bit field width of 2bit */
/* #Violation: Port_GeneralTypes_h_REF_1 */
typedef union
/* #Violation: Port_GeneralTypes_h_REF_3 */
/* #Violation: Port_GeneralTypes_h_REF_4 */
{
    struct
    {
        ureg32 Pin0  : 2; /* [ 1: 0] Pin0  control bit field  */
        ureg32 Pin1  : 2; /* [ 3: 2] Pin1  control bit field  */
        ureg32 Pin2  : 2; /* [ 5: 4] Pin2  control bit field  */
        ureg32 Pin3  : 2; /* [ 7: 6] Pin3  control bit field  */
        ureg32 Pin4  : 2; /* [ 9: 8] Pin4  control bit field  */
        ureg32 Pin5  : 2; /* [11:10] Pin5  control bit field  */
        ureg32 Pin6  : 2; /* [13:12] Pin6  control bit field  */
        ureg32 Pin7  : 2; /* [15:14] Pin7  control bit field  */
        ureg32 Pin8  : 2; /* [17:16] Pin8  control bit field  */
        ureg32 Pin9  : 2; /* [19:18] Pin9  control bit field  */
        ureg32 Pin10 : 2; /* [21:20] Pin10 control bit field  */
        ureg32 Pin11 : 2; /* [23:22] Pin11 control bit field  */
        ureg32 Pin12 : 2; /* [25:24] Pin12 control bit field  */
        ureg32 Pin13 : 2; /* [27:26] Pin13 control bit field  */
        ureg32 Pin14 : 2; /* [29:28] Pin14 control bit field  */
        ureg32 Pin15 : 2; /* [31:30] Pin15 control bit field  */
    } B;

    uint32 U;             /* uint32 type value register value */
} Port_Pin2BitType;

/* Define a register type with a bit field width of 4bit */
/* #Violation: Port_GeneralTypes_h_REF_1 */
typedef union
/* #Violation: Port_GeneralTypes_h_REF_3 */
/* #Violation: Port_GeneralTypes_h_REF_4 */
{
    struct
    {
        ureg32 Pin0  : 4; /* [ 3: 0] Pin0  control bit field */
        ureg32 Pin1  : 4; /* [ 7: 4] Pin1  control bit field */
        ureg32 Pin2  : 4; /* [11: 8] Pin2  control bit field */
        ureg32 Pin3  : 4; /* [15:12] Pin3  control bit field */
        ureg32 Pin4  : 4; /* [19:16] Pin4  control bit field */
        ureg32 Pin5  : 4; /* [23:20] Pin5  control bit field */
        ureg32 Pin6  : 4; /* [27:24] Pin6  control bit field */
        ureg32 Pin7  : 4; /* [31:28] Pin7  control bit field */
        ureg32 Pin8  : 4; /* [ 3: 0] Pin8  control bit field */
        ureg32 Pin9  : 4; /* [ 7: 4] Pin9  control bit field */
        ureg32 Pin10 : 4; /* [11: 8] Pin10 control bit field */
        ureg32 Pin11 : 4; /* [15:12] Pin11 control bit field */
        ureg32 Pin12 : 4; /* [19:16] Pin12 control bit field */
        ureg32 Pin13 : 4; /* [23:20] Pin13 control bit field */
        ureg32 Pin14 : 4; /* [27:24] Pin14 control bit field */
        ureg32 Pin15 : 4; /* [31:28] Pin15 control bit field */
    } B;

    uint32 DSR[PORT_DSRX_NUMBER];        /* uint32 type value register value */
} Port_Pin4BitType;

/* Define a register type with a bit field width of 4bit */
/* #Violation: Port_GeneralTypes_h_REF_1 */
typedef union
/* #Violation: Port_GeneralTypes_h_REF_3 */
/* #Violation: Port_GeneralTypes_h_REF_4 */
{
    struct
    {
        ureg32 INSEL0 : 4; /* [ 3: 0] Input multiplexer select 0 - RW */
        ureg32 INSEL1 : 4; /* [ 7: 4] Input multiplexer select 1 - RW */
        ureg32 INSEL2 : 4; /* [11: 8] Input multiplexer select 2 - RW */
        ureg32 INSEL3 : 4; /* [15:12] Input multiplexer select 3 - RW */
        ureg32 INSEL4 : 4; /* [19:16] Input multiplexer select 4 - RW */
        ureg32 INSEL5 : 4; /* [23:20] Input multiplexer select 5 - RW */
        ureg32 INSEL6 : 4; /* [27:24] Input multiplexer select 6 - RW */
        ureg32 INSEL7 : 4; /* [31:28] Input multiplexer select 7 - RW */
    } B;

    uint32 U;              /* uint32 type value register value */
} RXMUX_SELType;

/* Define a union type with a bit field width of uint16 */
/* #Violation: Port_GeneralTypes_h_REF_1 */
typedef union
/* #Violation: Port_GeneralTypes_h_REF_3 */
/* #Violation: Port_GeneralTypes_h_REF_4 */
{
    struct
    {
        uint16 Pin0;  /* Multiplexing functions supported by Pin0  */
        uint16 Pin1;  /* Multiplexing functions supported by Pin1  */
        uint16 Pin2;  /* Multiplexing functions supported by Pin2  */
        uint16 Pin3;  /* Multiplexing functions supported by Pin3  */
        uint16 Pin4;  /* Multiplexing functions supported by Pin4  */
        uint16 Pin5;  /* Multiplexing functions supported by Pin5  */
        uint16 Pin6;  /* Multiplexing functions supported by Pin6  */
        uint16 Pin7;  /* Multiplexing functions supported by Pin7  */
        uint16 Pin8;  /* Multiplexing functions supported by Pin8  */
        uint16 Pin9;  /* Multiplexing functions supported by Pin9  */
        uint16 Pin10; /* Multiplexing functions supported by Pin10 */
        uint16 Pin11; /* Multiplexing functions supported by Pin11 */
        uint16 Pin12; /* Multiplexing functions supported by Pin12 */
        uint16 Pin13; /* Multiplexing functions supported by Pin13 */
        uint16 Pin14; /* Multiplexing functions supported by Pin14 */
        uint16 Pin15; /* Multiplexing functions supported by Pin15 */
    } Pin;

    uint16 PortPin[PIN_MAX_NUMBER];    /* Multiplexing functions supported by Portx */
} Port_ALTModeType;

/* Define type LVDS pair configuration information structure */
/* #Violation: Port_GeneralTypes_h_REF_1 */
typedef struct
/* #Violation: Port_GeneralTypes_h_REF_4 */
{
    uint8  PortId;          /* LVDS GPIO Port ID */
    uint8  PinId0;          /* LVDS GPIO Pin0 ID */
    uint8  PinId1;          /* LVDS GPIO Pin1 ID */
    uint8  LVDSRNumber;     /* LVDS group number */
    uint32 LVDSConfig;      /* LVDS register configuration values */
} Port_LVDSPairType;

/* Define type LVDS configuration information structure */
/* #Violation: Port_GeneralTypes_h_REF_1 */
typedef struct
/* #Violation: Port_GeneralTypes_h_REF_4 */
{
    /* Define type LVDS pair configuration information structure */
    const Port_LVDSPairType *LVDSPairConfigPtr;
    /* Define the total number of valid LVDS Pairs */
    uint8                    LVDSPairNumber;
} Port_LVDSType;
/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/
/*  SWS_Port_00079:
    The PORT Driver module shall provide additional configurations for the MCU port/port pins:
    - Pin direction (input/output)
    - Pin level initial value
    - Pin direction changeable during runtime (yes/no).
    - Port mode changeable during runtime.
    SWS_Port_00081:
    The PORT Driver module shall provide a number of optional configurations for the MCU ports and
    port pins (if supported by hardware):
    - Slew rate control
    - Activation of internal pull-ups
    - Input Thresholds
    - Pin driven mode (push-pull / open drain).
    - Type of Readback support (pin level, output register value).
    SWS_Port_00082:
    The PORT Driver module shall not provide the facility to configure pin level inversion. The
    default value shall be set (i.e. not inverted).
    SWS_Port_00228:
    Type of the external data structure containing the initialization data for this module.
    Range: Hardware Dependent Structure
           The contents of the initialization data structure are specific to the microcontroller.
    SWS_Port_00072:
    A list of possible port configurations for the structure Port_ConfigType is given below:
    - Pin mode (e.g. DIO, ADC, SPI .) - this port pin configuration is mandatory unless the port pin is configured for DIO.
    - Pin direction (input, output) - this port pin configuration is mandatory when the port pin is to be used for DIO.
    - Pin level init value (see SWS_Port_00055) - this port pin configuration is mandatory when the port pin is used for DIO.
    - Pin direction changeable during runtime (STD_ON/STD_OFF) - this port pin configuration is MCU dependent.
    - Pin mode changeable during runtime (STD_ON/STD_OFF) - configuration is MCU dependent.
    Optional parameters (if supported by hardware)
    - Slew rate control.
    - Activation of internal pull-ups.
    - Microcontroller specific port pin properties.
    SWS_Port_00073:
    The type Port_ConfigType is a type for the external data structure containing the initialization data for the PORT Driver.
*/
typedef struct
/* #Violation: Port_GeneralTypes_h_REF_4 */
{
    /* Configure Port-Pin Direction, Push-pull&Open-drain, Output Function Select(CTR0/4/8/12) */
    const Port_PinControlDataType   *CTRxCfgPtr;
    /* Configure Port-Pin initial output Level (ODR) */
    const Port_Pin1BitType          *ODRCfgPtr;
    /* Configure Port-Pin initial output Level (STTL) */
    const Port_Pin1BitType          *STTLCfgPtr;
    /* Configure Port-Pin Pad level, slew-rate, Pad input mode, Pad driver Select (DSR0/8) */
    const Port_Pin4BitType          *DSRxCfgPtr;
    /* Configure Port-Pin digital function enable (DFR) */
    const Port_Pin2BitType          *DFRCfgPtr;
    /* Configure Port-Pin hardware control select (HWCR) */
    const Port_Pin2BitType          *HWCRCfgPtr;
    /* Configure Port-Pin Pull_Up/Pull_Down (PSR) */
    const Port_Pin2BitType          *PSRCfgPtr;
    /* Configure Port-Pin input multiplexing function selection */
    const RXMUX_SELType             *RXMUXSelPtr;
    /* Port pin run time mode changeable(ALT)*/
    const Port_Pin1BitType          *ModeChangeCtrlPtr;
    /* Port pin run time direction changeable */
    const Port_Pin1BitType          *DirChangeCtrlPtr;
    /* Port pin Hardware supported ALT mode Mask */
    const Port_ALTModeType          *HwSupportedModesPtr;
    /* Port Pin supported LVDS configuration information structure */
    const Port_LVDSType             *LVDSConfigPtr;
    /* Mask of valid Pins in the Port group */
    const uint16                    *AvailablePinsPtr;
    /* The index of the Port group in the current configuration */
    const uint8                     *AvailablePortIndexPtr;
    /* The available Port hardware base address */
    PORT_MODULE * const             *HwUnitBaseAddressPtr;
} Port_ConfigType;

#endif /* PORT_GENERALTYPES_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
