/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    dsadc_hal.h
 * Author:      30037
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all hardware abstract layer data type definitions and
 *              function declarations.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #dsadc_hal_h_REF_1:MISRAC2012-Dir-4.9
* Justification:Function like macros are used to reduce code complexity.
*
* #dsadc_hal_h_REF_2:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers
*
* #dsadc_hal_h_REF_3:MISRAC2012-Dir-4.8
* Justification:Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
* #dsadc_hal_h_REF_4:MISRAC2012-Rule-11.4;
* Justification:Converting integers to object pointers to reduce register access complexity.
*
* #dsadc_hal_h_REF_5:MISRAC2012-Rule-10.5
* Justification:Necessary type casting to reduce code complexity; Code review ensure the safety of the casting.
*
* #dsadc_hal_h_REF_6:CERTC-DCL12-C;
* Justification:Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
* #dsadc_hal_h_REF_7:CERTC-PRE00-C;
* Justification:Function like macros are used to reduce code complexity.
*
* #dsadc_hal_h_REF_8:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/

#ifndef DSADC_HAL_H_
#define DSADC_HAL_H_

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "dsadc_register.h"
#include "dsadc_std.h"
#include "dev.h"
#include "tha6_cfg.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* #Violation: dsadc_hal_h_REF_1 */
/* #Violation: dsadc_hal_h_REF_7 */
/* #Violation: dsadc_hal_h_REF_2 */
#define Dsadc_Hal_GetResultSigned(module, channel) ((sint16)Dsadc_Hal_GetConversionResult(module, channel))

/* #Violation: dsadc_hal_h_REF_2 */
#define DSADC_INVALID_TIMESTAMP 0xFFFFU
/** \brief  Interrupt or Interrupt status*/
/* Interrupt 0 . */
/* #Violation: dsadc_hal_h_REF_2 */
#define    DSADC_EXTERNAL_TRIGGER_INTERRUPT         ((uint32)1U << 0U)
/* Interrupt 1 . */
/* #Violation: dsadc_hal_h_REF_2 */
#define    DSADC_FIFO_INTERRUPT                     ((uint32)1U << 1U)
/* Interrupt 2 . */
/* #Violation: dsadc_hal_h_REF_2 */
#define    DSADC_MAIN_SAUL_INTERRUPT                ((uint32)1U << 2U)
/* Interrupt 3 . */
/* #Violation: dsadc_hal_h_REF_2 */
#define    DSADC_MAIN_SBUL_INTERRUPT                ((uint32)1U << 3U)
/* Interrupt 4 . */
/* #Violation: dsadc_hal_h_REF_2 */
#define    DSADC_TIMESTAMP_INTERRUPT                ((uint32)1U << 4U)
/* Interrupt 5 . */
/* #Violation: dsadc_hal_h_REF_2 */
#define    DSADC_AUXILIARY_SAUL_INTERRUPT           ((uint32)1U << 5U)
/* Interrupt 6 . */
/* #Violation: dsadc_hal_h_REF_2 */
#define    DSADC_AUXILIARY_SBUL_INTERRUPT           ((uint32)1U << 6U)
/* Interrupt 7 . */
/* #Violation: dsadc_hal_h_REF_2 */
#define    DSADC_AUXILIARY_COMPLETED_INTERRUPT      ((uint32)1U << 7U)
/* Interrupt 8 . */
/* #Violation: dsadc_hal_h_REF_2 */
#define    DSADC_DMA_FIFO_INTERRUPT                 ((uint32)1U << 8U)
/* Interrupt 9 . */
/* #Violation: dsadc_hal_h_REF_2 */
#define    DSADC_DMA_EXTERNAL_TRIGGER_INTERRUPT     ((uint32)1U << 9U)
/* Interrupt 10 . */
/* #Violation: dsadc_hal_h_REF_2 */
#define    DSADC_DMA_TIMESTAMP_INTERRUPT            ((uint32)1U << 10U)
/* Interrupt 11 . */
/* #Violation: dsadc_hal_h_REF_2 */
#define    DSADC_DMA_AUXILIARY_COMPLETED_INTERRUPT  ((uint32)1U << 11U)

/* #Violation: dsadc_hal_h_REF_2 */
#define    X1X2_DIFFERENCEVALUE                     7328U
/* #Violation: dsadc_hal_h_REF_2 */
#define    X1_VALUE                                 2443U
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* DSADC Input multiplexer trigger mode config. */
typedef enum
{
    DSADC_MAINCHANNEL = 0U,                         /* Main channel */
    DSADC_AUXILIARYCHANNEL,                         /* Auxiliary channel */
} Dsadc_ChannelSelect;

/* DSADC  multiplexer. */
typedef enum
{
    DSADC_MULTIPLEXERB = 0U,                        /* Multiplexer B */
    DSADC_MULTIPLEXERA,                             /* Multiplexer A */
} Dsadc_MultiplexerSelect;

/* DSADC fifo error status. */
typedef enum
{
    DSADC_NOERRORFLAG = 0U,                        /* No FIFO error */
    DSADC_READERROR,                               /* Read error */
    DSADC_WRITEERROR,                              /* Write error */
    DSADC_READANDWRITEERROR,                       /* Read and write error */
} Dsadc_FifoErrorStatus;

/* DSADC Calibration input channel. */
typedef enum
{
    DSADC_FIFOVALUE_0 = 0U,                         /* No value in FIFO */
    DSADC_FIFOVALUE_1,                              /* 1 value in FIFO */
    DSADC_FIFOVALUE_2,                              /* 2 value in FIFO */
    DSADC_FIFOVALUE_3,                              /* 3 value in FIFO */
    DSADC_FIFOVALUE_4,                              /* 4 value in FIFO */
} Dsadc_FifoFillValue;

/* DSADC Result Status. */
typedef enum
{
    DSADC_RESULTVALID = 0U,                         /* Result  valid*/
    DSADC_RESULTINVALID,                            /* Result  invalid*/
} Dsadc_ResultStatus;

/* Select Bias voltage. */
typedef enum
{
    DSADC_BIASVOLTAGE_0 = 0U,                         /* 1/2 VREF. */
    DSADC_BIASVOLTAGE_1,                              /* 1/5 VREF. */
    DSADC_BIASVOLTAGE_2,                              /* 4/5 VREF. */
    DSADC_BIASVOLTAGE_3,                              /* VREF. */
} Dsadc_BiasVoltageSelect;

#if defined(THA6_THA6412)
/* Select Input port. */
typedef enum
{
    DSADC_INPUTPORT_A = 0U,                         /* Input port A . */
    DSADC_INPUTPORT_B,                              /* Input port B . */
    DSADC_INPUTPORT_C,                              /* Input port C . */
    DSADC_INPUTPORT_D,                              /* Input port D . */
} Dsadc_InputPortSelect;
#endif

/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* #Violation: dsadc_hal_h_REF_3 */
/* #Violation: dsadc_hal_h_REF_6 */
/* Dsadc module initialization structure */
typedef struct
{
    const Dsadc_ModulatorConfig *pModulatorConfig;                           /* Modulator Config */
    const Dsadc_DemodulatorConfig *pDemodulatorConfig;                       /* Demodulator Config */
    const Dsadc_TimeStampConfig *pTimeStampConfig;                           /* Time-Stamp Config */
    const Dsadc_ThresholdConfig *pThresholdConfig;                           /* Threshold Config */
    const Dsadc_MainFilterConfig *pMainFilterConfig;                         /* Main Filter Config */
    const Dsadc_AuxiliaryFilterConfig *pAuxiliaryFilterConfig;               /* Auxiliary Filter Config */
    const Dsadc_MeanConfig *pMeanConfig;                                     /* Mean Config */
    const Dsadc_FifoConfig *pFifoConfig;                                     /* Fifo Config */
} Dsadc_ModuleConfig;

/* #Violation: dsadc_hal_h_REF_3 */
/* #Violation: dsadc_hal_h_REF_6 */
/* Dsadc module carrier wave configuration structure */
typedef struct
{
    boolean excitationEnable;                       /* 0: Excitation disable. 1: Excitation enable */
    boolean pcmEnable;                              /* 0: PCM disable 1: PCM enable */
    boolean carrierWave;                            /* 0: Forward  1: Reverse */
    Dsadc_WaveMode mode;                            /* Set wave mode */
} Dsadc_CarrierWaveConfig;

/* #Violation: dsadc_hal_h_REF_3 */
/* #Violation: dsadc_hal_h_REF_6 */
/* Dsadc module carrier wave sync configuration structure */
typedef struct
{
    uint8 SyncStart;                                /* Set sync start time. */
    uint8 SyncEnd;                                  /* Set sync end time */
} Dsadc_CarrierWaveSyncConfig;

/* #Violation: dsadc_hal_h_REF_3 */
/* #Violation: dsadc_hal_h_REF_6 */
/* Dsadc module compensation configuration structure */
typedef struct
{
    uint16 dcOffset;                                /* DC compensation offset. */
    uint16 gcOffset;                                /* Gain compensation offset. */
} Dsadc_CompensationConfig;

/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
#define DSADC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: dsadc_hal_h_REF_8 */
#include "Dsadc_MemMap.h"
/**********************************************************************************************************************
 * Function:     Dsadc_Hal_InitModule
 * Description:  Initialize the specified dsadc module
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different DSADC module, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pDsadc: pointer to pdsadc module
 *               pConfig: pointer to pdsadc configuration structure
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Hal_InitModule(DSADC_MODULE *const pDsadc, const Dsadc_ModuleConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Dsadc_Hal_ConfigCarrierWave
 * Description:  Config carrier wave function
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pConfig: pointer to carrier wave configuration structure
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Hal_ConfigCarrierWave(const Dsadc_CarrierWaveConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Dsadc_Hal_ConfigCarrierWaveSync
 * Description:  Config carrier wave sync function
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different DSADC module, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pDsadc: pointer to pdsadc module
 *               pConfig: pointer to carrier wave sync configuration structure
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Hal_ConfigCarrierWaveSync(DSADC_MODULE *const pDsadc, const Dsadc_CarrierWaveSyncConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Dsadc_Hal_EnableInterrupt
 * Description:  Enable dsadc interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different DSADC module, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pDsadc: pointer to pdsadc module
 *               interruptSource:interrupt source select
 *               interruptID:
 *               1<<0   External trigger interrupt
 *               1<<1   FIFO interrupt
 *               1<<2   Main saul interrupt
 *               1<<3   Main sbul interrupt
 *               1<<4   Time-stamp interrupt
 *               1<<5   Auxiliary saul interrupt
 *               1<<6   Auxiliary sbul interrupt
 *               1<<7   Auxiliary transition completed interrupt
 *               1<<8   DMA FIFO interrupt
 *               1<<9   DMA external trigger interrupt
 *               1<<10  DMA Time-stamp interrupt
 *               1<<11  Auxiliary transition completed DMA interrupt
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Hal_EnableInterrupt(DSADC_MODULE *const pDsadc, uint32 interruptSource);

/**********************************************************************************************************************
 * Function:     Dsadc_Hal_DisableInterrupt
 * Description:  Disable all dsadc interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different DSADC module, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pDsadc: pointer to pdsadc module
 *               interruptSource:interrupt source select
 *               interruptID:
 *               1<<0  External trigger interrupt
 *               1<<1  FIFO interrupt
 *               1<<2  Main saul interrupt
 *               1<<3  Main sbul interrupt
 *               1<<4  Time-stamp interrupt
 *               1<<5  Auxiliary saul interrupt
 *               1<<6  Auxiliary sbul interrupt
 *               1<<7  Auxiliary transition completed interrupt
 *               1<<8  DMA FIFO interrupt
 *               1<<9  DMA external trigger interrupt
 *               1<<10 DMA Time-stamp interrupt
 *               1<<11 Auxiliary transition completed DMA interrupt
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Hal_DisableInterrupt(DSADC_MODULE *const pDsadc, uint32 interruptSource);

/**********************************************************************************************************************
 * Function:     Dsadc_Hal_GetInterruptStatus
 * Description:  Get interrupt status.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDsadc: pointer to pdsadc module
 * Inout:        None
 * Output:       None
 * Return:       uint32:interrupt status
 *               interruptID:
 *               1<<0 External trigger interrupt generate
 *               1<<1 FIFO interrupt generate
 *               1<<2 Main saul interrupt generate
 *               1<<3 Main sbul interrupt generate
 *               1<<4 Time-stamp interrupt generate
 *               1<<5 Auxiliary saul interrupt generate
 *               1<<6 Auxiliary sbul interrupt generate
 *               1<<7 Auxiliary transition completed interrupt generate
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern uint32 Dsadc_Hal_GetInterruptStatus(const DSADC_MODULE *const pDsadc);

/**********************************************************************************************************************
 * Function:     Dsadc_Hal_ClearInterruptStatus
 * Description:  Clear interrupt status.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDsadc: pointer to pdsadc module
 *               interruptSource: select interrupt source to clear
 *               interruptID:
 *               1<<0 External trigger interrupt
 *               1<<1 FIFO interrupt
 *               1<<2 Main saul interrupt
 *               1<<3 Main sbul interrupt
 *               1<<4 Time-stamp interrupt
 *               1<<5 Auxiliary saul interrupt
 *               1<<6 Auxiliary sbul interrupt
 *               1<<7 Auxiliary transition completed interrupt
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern void Dsadc_Hal_ClearInterruptStatus(DSADC_MODULE *const pDsadc, uint32 interruptSource);

/**********************************************************************************************************************
 * Function:     Dsadc_Hal_GetConversionResult
 * Description:  Get conversion result
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDsadc: pointer to pdsadc module
 *               channel:0:Main channel 1:Auxiliary channel
 * Inout:        None
 * Output:       None
 * Return:       uint16:Conversion result
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern uint16 Dsadc_Hal_GetConversionResult(const DSADC_MODULE *const pDsadc, Dsadc_ChannelSelect channel);


/**********************************************************************************************************************
 * Function:     Dsadc_Hal_EnableModuleSync
 * Description:  Enable the specified dsadc.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        module: dsadc module ID
 *               moduleID:
 *               1<<0 dsadc0
 *               1<<1 dsadc1
 *               1<<2 dsadc2
 *               1<<3 dsadc3
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Hal_EnableModuleSync(uint16 module);

/**********************************************************************************************************************
 * Function:     Dsadc_Hal_EnableModule
 * Description:  Enable the specified dsadc.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDsadc: pointer to pdsadc module
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Hal_EnableModule(const DSADC_MODULE *const pDsadc);

/**********************************************************************************************************************
 * Function:     Void Dsadc_Hal_DisableModule
 * Description:  Disable the specified dsadc.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDsadc: pointer to pdsadc module
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Hal_DisableModule(const DSADC_MODULE *const pDsadc);

/**********************************************************************************************************************
 * Function:     Rcc_ErrorFlag Dsadc_Hal_DeInitModule
 * Description:  DeInit the specified dsadc Module
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDsadc: pointer to pdsadc module
 *               *retValue: Back to check value
 * Inout:        None
 * Output:       None
 * Return:       boolean: RCC error flag
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Hal_DeInitModule(DSADC_MODULE *const pDsadc);

/**********************************************************************************************************************
 * Function:     Dsadc_Hal_ClearFifo
 * Description:  Clear FIFO.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different DSADC module, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pDsadc: pointer to pdsadc module
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Hal_ClearFifo(DSADC_MODULE *const pDsadc);


/**********************************************************************************************************************
 * Function:     Dsadc_Hal_EnableMainChannel
 * Description:  Enable main channel.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDsadc: pointer to pdsadc module
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Hal_EnableMainChannel(const DSADC_MODULE *const pDsadc);

/**********************************************************************************************************************
 * Function:     Dsadc_Hal_EnableMainChannelSync
 * Description:  Enable main channel.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        module: DSADC module main channel ID
 *               use macro define parameter DSADCx_MAIN_CHANNEL in tha6xxx_cfg.h
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Hal_EnableMainChannelSync(uint32 module);

/**********************************************************************************************************************
 * Function:     Dsadc_Hal_DisableMainChannel
 * Description:  Disable main channel.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDsadc: pointer to pdsadc module
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Hal_DisableMainChannel(const DSADC_MODULE *const pDsadc);

/**********************************************************************************************************************
 * Function:     Dsadc_Hal_EnableAuxChannel
 * Description:  Enable auxiliary channel.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDsadc: pointer to pdsadc module
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Hal_EnableAuxChannel(const DSADC_MODULE *const pDsadc);

/**********************************************************************************************************************
 * Function:     Dsadc_Hal_EnableAuxChannelSync
 * Description:  Enable auxiliary channel.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        module: DSADC module auxiliary channel ID
 *               use macro define parameter DSADCx_AUX_CHANNEL in tha6xxx_cfg.h
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Hal_EnableAuxChannelSync(uint32 module);

/**********************************************************************************************************************
 * Function:     Void Dsadc_Hal_DisableAuxChannel
 * Description:  Disable auxiliary channel.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDsadc: pointer to pdsadc module
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Hal_DisableAuxChannel(const DSADC_MODULE *const pDsadc);

/**********************************************************************************************************************
 * Function:     Dsadc_Hal_CloseLoop
 * Description:  Close ADC loop reset
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDsadc:pointer to dsadc module
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Hal_CloseLoop(DSADC_MODULE *const pDsadc);


/**********************************************************************************************************************
 * Function:     Dsadc_Hal_EnableDithering
 * Description:  Dithering enable
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different DSADC module, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pDsadc:pointer to dsadc module 
 *               enable: 0:disable 1:enable
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Hal_EnableDithering(DSADC_MODULE *const pDsadc , boolean enable);

/**********************************************************************************************************************
 * Function:     Dsadc_Hal_GetTriggerTimeStamp
 * Description:  Get Trigger Time Stamp
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different DSADC module, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pDsadc:pointer to dsadc module 
 * Inout:        None
 * Output:       None
 * Return:       uint16:time stamp
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern uint16 Dsadc_Hal_GetTriggerTimeStamp(const DSADC_MODULE *const pDsadc);


/**********************************************************************************************************************
 * Function:     Dsadc_Hal_GetMultiplexerSetting
 * Description:  Get multiplexer setting
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDsadc:pointer to dsadc module 
 * Inout:        None
 * Output:       None
 * Return:       Dsadc_MultiplexerSelect:Multiplexer Select
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern Dsadc_MultiplexerSelect Dsadc_Hal_GetMultiplexerSetting(const DSADC_MODULE *const pDsadc);

/**********************************************************************************************************************
 * Function:     Dsadc_Hal_ResetLoop
 * Description:  ADC loop reset
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDsadc:pointer to dsadc module 
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Hal_ResetLoop(DSADC_MODULE *const pDsadc);


/**********************************************************************************************************************
 * Function:     Dsadc_Hal_GetMainResultStatus
 * Description:  Get main channel result status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDsadc:pointer to dsadc module
 * Inout:        None
 * Output:       None
 * Return:       Dsadc_ResultStatus: result status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern Dsadc_ResultStatus Dsadc_Hal_GetMainResultStatus(const DSADC_MODULE *const pDsadc);

/**********************************************************************************************************************
 * Function:     Dsadc_Hal_ConfigCompensation
 * Description:  Config dc and gc compensation
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different DSADC module, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pDsadc:pointer to dsadc module 
 *               pConfig:Compensation config
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Hal_ConfigCompensation(DSADC_MODULE *const pDsadc, const Dsadc_CompensationConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Dsadc_Hal_ConfigBiasVoltage
 * Description:  Config bias voltage
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different DSADC module, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pDsadc: pointer to dsadc module 
 *               voltage: Config vref voltage
 *               enable: 0:disable 1:enable
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Hal_ConfigBiasVoltage(DSADC_MODULE *const pDsadc, Dsadc_BiasVoltageSelect voltage,
                                           boolean enable);

/**********************************************************************************************************************
 * Function:     Dsadc_Hal_ConfigDsadc1InPort
 * Description:  Config Dsadc1 InPort
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        Dsadc_InputPortSelect: port
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
#if defined(THA6_THA6412)
extern boolean Dsadc_Hal_ConfigDsadc1InPort(Dsadc_InputPortSelect port);
#endif

/**********************************************************************************************************************
 * Function:     Dsadc_Hal_BypassAllAdcComVolSpb
 * Description:  Set all DSADC COMVOSPBBYPASS bit to 1
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       This function is applicable to THA6206 version C and THA6412 chip, refer to DSADC errata.
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Hal_BypassAllAdcComVolSpb(void);

/**********************************************************************************************************************
 * Function:     Dsadc_Hal_SetSyncMode
 * Description:  Set synchronization mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        mode: 0:synchronization 1:asynchronization
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Dsadc_Hal_SetSyncMode(boolean mode);

/**********************************************************************************************************************
 * Function:     Dsadc_Hal_SetIntegratorState
 * Description:  Enable/Disable integrator state.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        state: 0:Integrator disable 1:Integrator enable
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Dsadc_Hal_SetIntegratorState(boolean state);


/**********************************************************************************************************************
 * Function:     Dsadc_Hal_GetTimeStamp
 * Description:  Get time stamp counter
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDsadc:pointer to dsadc module 
 * Inout:        None
 * Output:       None
 * Return:       uint16: time stamp counter
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint16 Dsadc_Hal_GetTimeStamp(const DSADC_MODULE *const pDsadc);


/**********************************************************************************************************************
 * Function:     Dsadc_Hal_EnableCarrierWave
 * Description:  Enable/Disable carrier wave
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        enable:0:Excitation disable. 1: Excitation enable
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Dsadc_Hal_EnableCarrierWave(boolean enable);


/**********************************************************************************************************************
 * Function:     Dsadc_Hal_GetFifoErrorFlag
 * Description:  Get fifo error status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDsadc:pointer to dsadc module 
 * Inout:        None
 * Output:       None
 * Return:       Dsadc_FifoErrorStatus: fifo error status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE Dsadc_FifoErrorStatus Dsadc_Hal_GetFifoErrorFlag(const DSADC_MODULE *const pDsadc);


/**********************************************************************************************************************
 * Function:     Dsadc_Hal_GetFifoFillValue
 * Description:  Get fifo fill value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDsadc:pointer to dsadc module 
 * Inout:        None
 * Output:       None
 * Return:       Dsadc_FifoFillValue: fifo fill value
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE Dsadc_FifoFillValue Dsadc_Hal_GetFifoFillValue(const DSADC_MODULE *const pDsadc);


/**********************************************************************************************************************
 * Function:     Dsadc_Hal_BypassDcCompensation
 * Description:  DC Compensation bypass
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different DSADC module, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pDsadc:pointer to dsadc module 
 *               bypass:0:enable 1:bypass
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Dsadc_Hal_BypassDcCompensation(DSADC_MODULE *const pDsadc , boolean bypass);

/**********************************************************************************************************************
 * Function:     void Dsadc_Hal_BypassGainCompensation
 * Description:  Gain Compensation bypass
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different DSADC module, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pDsadc:pointer to dsadc module 
 *               bypass:0:enable 1:bypass
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Dsadc_Hal_BypassGainCompensation(DSADC_MODULE *const pDsadc , boolean bypass);

/**********************************************************************************************************************
 * Function:     void Dsadc_Hal_GetCarrierWaveSyncDelay
 * Description:  Get Carrier Wave Sync Delay
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       uint8: carrier wave sync delay
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint8 Dsadc_Hal_GetCarrierWaveSyncDelay(void);

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Dsadc_Hal_SetSyncMode(boolean mode)
{
    boolean ret = TRUE;
    
    /* #Violation: dsadc_hal_h_REF_4 */
    DSADC_COMMON_MODULE->GLOBSYNC.B.SYNCSWITCH = mode;
    /* #Violation: dsadc_hal_h_REF_4 */
    ret = Dsadc_Register_ReadBack_Check(ret, (uint32)mode, DSADC_COMMON_MODULE->GLOBSYNC.B.SYNCSWITCH);

    return ret;
}

LOCAL_FORCEINLINE boolean Dsadc_Hal_SetIntegratorState(boolean state)
{
    boolean ret = TRUE;
    
    /* #Violation: dsadc_hal_h_REF_4 */
    DSADC_COMMON_MODULE->GLOBSYNC.B.INTEREN = state;
    /* #Violation: dsadc_hal_h_REF_4 */
    ret = Dsadc_Register_ReadBack_Check(ret, (uint32)state, DSADC_COMMON_MODULE->GLOBSYNC.B.INTEREN);

    return ret;
}

LOCAL_FORCEINLINE uint16 Dsadc_Hal_GetTimeStamp(const DSADC_MODULE *const pDsadc)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /*Check if the pDsadc is null pointer*/
    /* #Violation: dsadc_hal_h_REF_1 */
    /* #Violation: dsadc_hal_h_REF_4 */
    Assert((boolean)(CHECK_DSADC_BASE(pDsadc)));
#endif

    /* Close ADC loop reset */
    return pDsadc->TSCNT.B.TSCVAL;
}

LOCAL_FORCEINLINE boolean Dsadc_Hal_EnableCarrierWave(boolean enable)
{
    /* Set Excitation enable  */
    /* #Violation: dsadc_hal_h_REF_4 */
    DSADC0->CWCFG.B.EN = enable;

    return TRUE;
}

LOCAL_FORCEINLINE Dsadc_FifoErrorStatus Dsadc_Hal_GetFifoErrorFlag(const DSADC_MODULE *const pDsadc)
{
    uint8 errFlag;
    uint8 temp1;
    uint8 temp2;
    
#if(INPUT_ARG_DETECT == STD_ON)
    /*Check if the pDsadc is null pointer*/
    /* #Violation: dsadc_hal_h_REF_1 */
    /* #Violation: dsadc_hal_h_REF_4 */
    Assert((boolean)(CHECK_DSADC_BASE(pDsadc)));
#endif

    temp1 = (pDsadc->RFCON.B.WREF << 1U);
    temp2 = (pDsadc->RFCON.B.RDEF);
    errFlag = temp1 + temp2;
    /* return fifo error flag  */
    /* #Violation: dsadc_hal_h_REF_5 */
    return (Dsadc_FifoErrorStatus)(errFlag);
}

LOCAL_FORCEINLINE Dsadc_FifoFillValue Dsadc_Hal_GetFifoFillValue(const DSADC_MODULE *const pDsadc)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /*Check if the pDsadc is null pointer*/
    /* #Violation: dsadc_hal_h_REF_1 */
    /* #Violation: dsadc_hal_h_REF_4 */
    Assert((boolean)(CHECK_DSADC_BASE(pDsadc)));
#endif

    /* return fifo error flag  */
    /* #Violation: dsadc_hal_h_REF_5 */
    return (Dsadc_FifoFillValue)(pDsadc->RFCON.B.FILLVAL);
}

LOCAL_FORCEINLINE boolean Dsadc_Hal_BypassDcCompensation(DSADC_MODULE *const pDsadc , boolean bypass)
{
    boolean ret = TRUE;
    
#if(INPUT_ARG_DETECT == STD_ON)
    /*Check if the pDsadc is null pointer*/
    /* #Violation: dsadc_hal_h_REF_1 */
    /* #Violation: dsadc_hal_h_REF_4 */
    Assert((boolean)(CHECK_DSADC_BASE(pDsadc)));
#endif

    /* return fifo error flag  */
    pDsadc->COMPCON.B.DCOBEN = bypass;
    ret = Dsadc_Register_ReadBack_Check(ret, (uint32)bypass, pDsadc->COMPCON.B.DCOBEN);

    return ret;
}

LOCAL_FORCEINLINE boolean Dsadc_Hal_BypassGainCompensation(DSADC_MODULE *const pDsadc , boolean bypass)
{
    boolean ret = TRUE;
    
#if(INPUT_ARG_DETECT == STD_ON)
    /*Check if the pDsadc is null pointer*/
    /* #Violation: dsadc_hal_h_REF_1 */
    /* #Violation: dsadc_hal_h_REF_4 */
    Assert((boolean)(CHECK_DSADC_BASE(pDsadc)));
#endif

    /* return fifo error flag  */
    pDsadc->COMPCON.B.GCOBEN = bypass;
    ret = Dsadc_Register_ReadBack_Check(ret, (uint32)bypass, pDsadc->COMPCON.B.GCOBEN);

    return ret;
}


LOCAL_FORCEINLINE uint8 Dsadc_Hal_GetCarrierWaveSyncDelay(void)
{
    /******************************************************
     * Usage Restrictions
     * - The API can only be used in calibration phase in 
     *   THA6206 and THA6412, please refer to errata.
     *******************************************************/
    /* #Violation: dsadc_hal_h_REF_4 */
    return DSADC0->CWSYNC.B.DELAY;
}

#define DSADC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: dsadc_hal_h_REF_8 */
#include "Dsadc_MemMap.h"

#endif /* DSADC_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
