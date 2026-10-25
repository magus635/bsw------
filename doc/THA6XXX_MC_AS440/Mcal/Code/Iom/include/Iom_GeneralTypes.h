/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Iom_GeneralTypes.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : IOM
*
*   brief                 : This file contains all type definitions of Iom Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright /(c) 2021,Beijing Tongxin Microelectroics co.Ltd
*
****************************************************************************************************/

/****************************************************************************************************
**                          Codeing Rule Violations                                                **
****************************************************************************************************/
/*
*#Violation Summary
*#Iom_GeneralTypes_h_REF_1:MISRAC2012-Dir-4.8; 
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#Iom_GeneralTypes_h_REF_2:CertC-DCL12-C; 
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*/

#ifndef IOM_GENERAL_TYPES_H_
#define IOM_GENERAL_TYPES_H_
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Mcall.h"
#include "iom_hal.h"

/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
/* Type definition for PPU Prescaler factor threshold */
typedef uint32                          Iom_PpuPrescalerThresholdType;
/* Type definition for PPU filter time */
typedef uint32                          Iom_PpuFilterTimeType;
/* Type definition for LPU event window counter threshold */
typedef uint32                          Iom_EventWinTimeThresType;
/* Type definition for glitch flags */
typedef Iom_PpuGlitchFlag               Iom_PpuGlitchFlagType;
/* Type definition for Ppu channel id */
typedef Iom_PpuId                       Iom_PpuChannelType;
/* Type definition for IOM LPU configuration */
typedef Iom_LpuConfig                   Iom_LpuConfigType;
/* Type definition for the Logic Module Analyser (LPU) Module Number */
typedef Iom_LpuId                       Iom_LpuChannelIdType;
/* Type definition for IOM LPU configuration */
typedef Iom_Lpu                         Iom_LpuChannelType;
/* Type definition for recording Emu's selection of LPU channel trigger events.  */
typedef uint32                          Iom_EmuSelectionType;

typedef Iom_EventCounterThreshold       Iom_EmuCounterThresholdType;

typedef Iom_EventCounterChannel         Iom_EventCounterChannelType;
/****************************************************************************************************
**                          Global Enumeration Definitions                                          **
****************************************************************************************************/
typedef enum
{
    IOM_UNINITIALIZED     = 0U,                 /* Not initialized */
    IOM_INITIALIZED                             /* Already initialized */
}Iom_InitType;

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/
/* #Violation: Iom_GeneralTypes_h_REF_1*/
/* #Violation: Iom_GeneralTypes_h_REF_2*/
typedef struct
{
    Iom_EventCounterChannel     EmuCounterIndex;
    Iom_LpuChannelIdType        Channel;
    Iom_EmuCounterThresholdType Iom_EmuCounterThreshold;
}Iom_EmuCombinerType;

/* #Violation: Iom_GeneralTypes_h_REF_2*/
typedef struct
{
    const Iom_LpuConfigType             *Iom_LpuChannelConfigPtr;
    const Iom_EmuSelectionType          Iom_EmuSelection;
    const Iom_EmuCombinerType           *Iom_EmuCombinerPtr;
    const uint8                         Iom_Clock_Div;
}Iom_ConfigType;

#endif/* IOM_GENERAL_TYPES_H_ */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
