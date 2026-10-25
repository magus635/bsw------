[!CODE!][!//
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
[!NOCODE!][!//
[!INCLUDE "Port.m"!][!//
[!ENDNOCODE!][!//
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

[!SELECT "as:modconf('Port')[1]"!][!//
[!CALL "Port_GetLVDSConfigNumber"!][!//
[!CALL "Port_GetInputOutputConfig"!][!//
/* Configure Port-Pin Direction, Push-pull&Open-drain, Output Function Select (CTR0/4/8/12) */
static const Port_PinControlDataType Port_PinControlData[PORT_AVAILABEL_TOTAL_NUMBER] =
{
    [!CALL "CG_GetPortPinDirectionAndModeAttributes_CTRx"!][!//
};
/* Configure Port-Pin initial output Level */
static const Port_Pin1BitType Port_PinInitLevel[PORT_AVAILABEL_TOTAL_NUMBER] =
{
    [!CALL "CG_GetPortPinOutputVoltageLevel_ODR"!][!//
};
[!IF "as:modconf('Resource')[1]/ResourceGeneral/ResourceSubderivative != 'THA6206_LFBGA292'"!][!//
/* Configure Port-Pin TTL level working mode */
static const Port_Pin1BitType Port_PinSTTLLevel[PORT_AVAILABEL_TOTAL_NUMBER] =
{
    [!CALL "CG_GetPortPinOutputVoltageLevel_STTL"!][!//
};
[!ENDIF!][!//
/* Configure Port-Pin Pad level, slew-rate, Pad input mode, Pad driver Select (DSR0/DSR8) */
static const Port_Pin4BitType Port_PinPadControlData[PORT_AVAILABEL_TOTAL_NUMBER] =
{
    [!CALL "CG_GetPortPinDriverLevelAndStrength_DSRx"!][!//
};
/* Configure Port-Pin digital function enable */
static const Port_Pin2BitType Port_PinDigitalEnable[PORT_AVAILABEL_TOTAL_NUMBER] =
{
    [!CALL "CG_GetPortPinDigitalFunctionsEnable_DFR"!][!//
};
/* Configure Port-Pin hardware control select */
static const Port_Pin2BitType Port_PinHwSelect[PORT_AVAILABEL_TOTAL_NUMBER] =
{
    [!CALL "CG_GetPortPinIoControlSelect_HWCR"!][!//
};
/* Configure Port-Pin Pull_Up/Pull_Down */
static const Port_Pin2BitType Port_PinPullSelect[PORT_AVAILABEL_TOTAL_NUMBER] =
{
    [!CALL "CG_GetPortPinPullUpModeSelect_PSR"!][!//
};
/* Configure Port-Pin input multiplexing function selection */
static const RXMUX_SELType RXMUX_SelectData[PORT_RXMUX_REG_TOTAL_NUMBER] =
{
    [!INDENT "4"!][!//
        [!CALL "CG_GetCanRxMuxSelect", "Index" = "num:i(0)"!][!//
        [!IF "not(contains(as:modconf('Resource')[1]/ResourceGeneral/ResourceSubderivative, 'THA610X'))"!][!//
            [!CALL "CG_GetDSADCRxMuxSelect", "Index" = "num:i(0)"!][!//
        [!ELSE!][!//
            [!CALL "CG_GetRxMuxSelectReserve", "RegNum" = "num:i(1)"!][!//
        [!ENDIF!][!//
        [!CALL "CG_GetETHRxMuxSelect", "Index" = "num:i(0)"!][!//
        [!CALL "CG_GetI2CRxMuxSelect", "Index" = "num:i(0)"!][!//
        [!CALL "CG_GetASIRxMuxSelect", "Index" = "num:i(0)"!][!//
        [!IF "contains(as:modconf('Resource')[1]/ResourceGeneral/ResourceSubderivative, 'THA610X')"!][!//
            [!CALL "CG_GetESPIRxMuxSelect", "Index" = "num:i(0)"!][!//
            [!CALL "CG_GetRxMuxSelectReserve", "RegNum" = "num:i(3)"!][!//
            [!CALL "CG_GetSENTRxMuxSelect", "Index" = "num:i(0)"!][!//
            [!CALL "CG_GetRxMuxSelectReserve", "RegNum" = "num:i(1)"!][!//
        [!ELSE!][!//
            [!CALL "CG_GetESPIRxMuxSelect", "Index" = "num:i(0)"!][!//
            [!CALL "CG_GetSENTRxMuxSelect", "Index" = "num:i(0)"!][!//
        [!ENDIF!][!//
        [!CALL "CG_GetIOMMONRxMuxSelect", "Index" = "num:i(0)"!][!//
        [!CALL "CG_GetDBGTraceRxMuxSelect", "Index" = "num:i(0)"!][!//
        [!IF "contains(as:modconf('Resource')[1]/ResourceGeneral/ResourceSubderivative, 'THA6412')"!][!//
            [!CALL "CG_GetCanRxMuxSelect", "Index" = "num:i(1)"!][!//
            [!CALL "CG_GetDSADCRxMuxSelect", "Index" = "num:i(1)"!][!//
            [!CALL "CG_GetI2CRxMuxSelect", "Index" = "num:i(1)"!][!//
            [!CALL "CG_GetASIRxMuxSelect", "Index" = "num:i(1)"!][!//
            [!CALL "CG_GetSENTRxMuxSelect", "Index" = "num:i(1)"!][!//
            [!CALL "CG_GetIOMMONRxMuxSelect", "Index" = "num:i(1)"!][!//
            [!CALL "CG_GetPSI5RxMuxSelect", "Index" = "num:i(0)"!][!//
        [!ENDIF!][!//
        [!IF "contains(as:modconf('Resource')[1]/ResourceGeneral/ResourceSubderivative, 'THA610X')"!][!//
            [!CALL "CG_GetRxMuxSelectReserve", "RegNum" = "num:i(3)"!][!//
            [!CALL "CG_GetI2CRxMuxSelect", "Index" = "num:i(1)"!][!//
            [!CALL "CG_GetASIRxMuxSelect", "Index" = "num:i(1)"!][!//
            [!CALL "CG_GetRxMuxSelectReserve", "RegNum" = "num:i(3)"!][!//
            [!CALL "CG_GetIOMMONRxMuxSelect", "Index" = "num:i(1)"!][!//
            [!CALL "CG_GetIOMPINRxMuxSelect", "Index" = "num:i(0)"!][!//
            [!CALL "CG_GetGTMRxMuxSelect", "Index" = "num:i(0)"!][!//
            [!CALL "CG_GetEXTIRxMuxSelect", "Index" = "num:i(0)"!][!//
        [!ENDIF!][!//
    [!ENDINDENT!][!//
};
/* Output ALT mode changeable flag */
static const Port_Pin1BitType Port_PinModeChangeControl[PORT_AVAILABEL_TOTAL_NUMBER] =
{
    [!CALL "CG_GetPinModeChangeEnable"!][!//
};
/* Port-Pin direction changeable flag */
static const Port_Pin1BitType Port_PinDirChangeControl[PORT_AVAILABEL_TOTAL_NUMBER] =
{
    [!CALL "CG_GetPinDirectionChangeEnable"!][!//
};
/* ALT mode mask supported by Port-Pin hardware */
static const Port_ALTModeType Port_PinHwSupportedAltModes[PORT_AVAILABEL_TOTAL_NUMBER] =
{
    [!CALL "CG_GetPinHwSupportAltModes"!][!//
};

[!IF "$LVDSPairTotalNumber != num:i(0) and ./PortGeneral/PortLvdsEnable = 'true'"!][!//
/* Port-Pin LVDS Pair configuration information structure */
static const Port_LVDSPairType Port_PinLVDSPairConfig[[!"$LVDSPairTotalNumber"!]] =
{
    [!CALL "Port_GetLVDSConfig"!][!//
};

/* Port-Pin LVDS configuration information structure */
static const Port_LVDSType Port_PinLVDSConfig =
{
    [!INDENT "4"!][!//
    [!IF "$LVDSPairTotalNumber != num:i(0)"!][!//
        &Port_PinLVDSPairConfig[0],
    [!ELSE!][!//
        NULL_PTR,
    [!ENDIF!][!//
    [!"$LVDSPairTotalNumber"!]U     /* LVDS Pair Total Number */
    [!ENDINDENT!][!//
};
[!ENDIF!][!//

/* Mask of valid Pins in the Port group */
static const uint16 Port_AvailablePins[PORT_AVAILABEL_TOTAL_NUMBER] =
{
    [!CALL "CG_GetAvailablePortPins"!][!//
};

/* The index of the Port group in the current configuration */
static const uint8 Port_AvailablePortIndexMap[PORT_MAX_NUMBER] =
{
    [!CALL "CG_GetAvailablePortIndex"!][!//
};

/* The available Port hardware base address */
static PORT_MODULE *const Port_BaseAddress[PORT_AVAILABEL_TOTAL_NUMBER] =
{
    [!CALL "CG_GenePortHwUnitMap"!][!//
};

/* Port-Pin global configuration information structure */
/* #Violation: Port_PBcfg_c_REF_2 */
[!IF "variant:name() != ''"!][!//
const Port_ConfigType Port_ConfigSet_[!"variant:name()"!][PORT_CONFIG_COUNT] =
[!ELSE!][!//
const Port_ConfigType Port_ConfigSet[PORT_CONFIG_COUNT] =
[!ENDIF!][!//
{
    [!INDENT "4"!][!//
    {
        [!INDENT "8"!][!//
        /* Configure Port-Pin Direction, Push-pull&Open-drain, Output Function Select(CTR0/4/8/12) */
        &Port_PinControlData[0],
        /* Configure Port-Pin initial output Level (ODR) */
        &Port_PinInitLevel[0],
        /* Configure Port-Pin TTL level working mode */
        [!IF "as:modconf('Resource')[1]/ResourceGeneral/ResourceSubderivative != 'THA6206_LFBGA292'"!][!//
            &Port_PinSTTLLevel[0],
        [!ELSE!][!//
            NULL_PTR,
        [!ENDIF!][!//
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
        [!IF "$LVDSPairTotalNumber != num:i(0) and ./PortGeneral/PortLvdsEnable = 'true'"!][!//
            &Port_PinLVDSConfig,
        [!ELSE!][!//
            NULL_PTR,
        [!ENDIF!][!//
        /* Mask of valid Pins in the Port group */
        &Port_AvailablePins[0],
        /* The index of the Port group in the current configuration */
        &Port_AvailablePortIndexMap[0],
        /* The available Port hardware base address */
        &Port_BaseAddress[0]
        [!ENDINDENT!][!//
    }
    [!ENDINDENT!][!//
};
[!ENDSELECT!][!//
/* #Violation: Port_PBcfg_c_REF_1 */
#define PORT_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Port_PBcfg_c_REF_3 */
#include "Port_MemMap.h"
[!ENDCODE!][!//
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
