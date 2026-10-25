/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    gtm_trig_hal.h
 * Author:      01031
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of interfaces.
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031     Create
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
* #Violation Summary
*
* #gtm_trig_hal_h_REF_1:MISRAC2012-Dir-4.8;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
* #gtm_trig_hal_h_REF_2:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
* #gtm_trig_hal_h_REF_3:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #gtm_trig_hal_h_REF_4:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
* #gtm_trig_hal_h_REF_5:MISRAC2012-Rule-2.3;
* Justification:The members of the type are used in configuration-generated code.
*
*/
 #ifndef GTM_TRIG_HAL_H_
#define GTM_TRIG_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "gtm_register.h"
#include "gtm.h"
#include "Platform_Types.h"
#include "tha6_cfg.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* Enum for ADC group */
typedef enum
{
    GTM_TRIG_ADCGROUP_0 = 0U,   /* For ADC group 0  */
    GTM_TRIG_ADCGROUP_1,           /* For ADC group 1  */
    GTM_TRIG_ADCGROUP_2,           /* For ADC group 2  */
    GTM_TRIG_ADCGROUP_3,           /* For ADC group 3  */
    GTM_TRIG_ADCGROUP_4,           /* For ADC group 4 */
    GTM_TRIG_ADCGROUP_5,           /* For ADC group 5  */
    GTM_TRIG_ADCGROUP_6,           /* For ADC group 6  */
    GTM_TRIG_ADCGROUP_7,           /* For ADC group 7  */
    GTM_TRIG_ADCGROUP_8,           /* For ADC group 8  */
    GTM_TRIG_ADCGROUP_9,           /* For ADC group 9  */
    GTM_TRIG_ADCGROUP_10,          /* For ADC group 10  */
    GTM_TRIG_ADCGROUP_11           /* For ADC group 11  */
} Gtm_Trig_AdcGroup;

/* Enum for ADC trigger */
typedef enum
{
    GTM_TRIG_ADCTRIG_0 = 0U,    /* ADC trigger 0  */
    GTM_TRIG_ADCTRIG_1,            /* ADC trigger 1  */
    GTM_TRIG_ADCTRIG_2,            /* ADC trigger 2  */
    GTM_TRIG_ADCTRIG_3,            /* ADC trigger 3  */
#if defined(THA6_THA6412)
    GTM_TRIG_ADCTRIG_4,            /* ADC trigger 4  */
#endif
    GTM_TRIG_ADCTRIG_COUNT  /* Count of the enum definition */
} Gtm_Trig_AdcTrig;

/* Enum for level 1 DMA trigger multiplex */
typedef enum
{
    GTM_TRIG_DMAL1_MUX_00 = 0U,       /* DMA level 1 multiplex 00 */
    GTM_TRIG_DMAL1_MUX_01,            /* DMA level 1 multiplex 01 */
    GTM_TRIG_DMAL1_MUX_02,            /* DMA level 1 multiplex 02 */
    GTM_TRIG_DMAL1_MUX_03,            /* DMA level 1 multiplex 03 */
    GTM_TRIG_DMAL1_MUX_04,            /* DMA level 1 multiplex 04 */
    GTM_TRIG_DMAL1_MUX_05,            /* DMA level 1 multiplex 05 */
    GTM_TRIG_DMAL1_MUX_06,            /* DMA level 1 multiplex 06 */
    GTM_TRIG_DMAL1_MUX_07,            /* DMA level 1 multiplex 07 */
    GTM_TRIG_DMAL1_MUX_10,            /* DMA level 1 multiplex 10 */
    GTM_TRIG_DMAL1_MUX_11,            /* DMA level 1 multiplex 11 */
    GTM_TRIG_DMAL1_MUX_12,            /* DMA level 1 multiplex 12 */
    GTM_TRIG_DMAL1_MUX_13,            /* DMA level 1 multiplex 13 */
    GTM_TRIG_DMAL1_MUX_14,            /* DMA level 1 multiplex 14 */
    GTM_TRIG_DMAL1_MUX_15,            /* DMA level 1 multiplex 15 */
    GTM_TRIG_DMAL1_MUX_16,            /* DMA level 1 multiplex 16 */
    GTM_TRIG_DMAL1_MUX_17,            /* DMA level 1 multiplex 17 */
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    GTM_TRIG_DMAL1_MUX_20,            /* DMA level 1 multiplex 20 */
    GTM_TRIG_DMAL1_MUX_21,            /* DMA level 1 multiplex 21 */
    GTM_TRIG_DMAL1_MUX_22,            /* DMA level 1 multiplex 22 */
    GTM_TRIG_DMAL1_MUX_23,            /* DMA level 1 multiplex 23 */
    GTM_TRIG_DMAL1_MUX_24,            /* DMA level 1 multiplex 24 */
    GTM_TRIG_DMAL1_MUX_25,            /* DMA level 1 multiplex 25 */
    GTM_TRIG_DMAL1_MUX_26,            /* DMA level 1 multiplex 26 */
    GTM_TRIG_DMAL1_MUX_27,            /* DMA level 1 multiplex 27 */
    GTM_TRIG_DMAL1_MUX_30,            /* DMA level 1 multiplex 30 */
    GTM_TRIG_DMAL1_MUX_31,            /* DMA level 1 multiplex 31 */
    GTM_TRIG_DMAL1_MUX_32,            /* DMA level 1 multiplex 32 */
    GTM_TRIG_DMAL1_MUX_33,            /* DMA level 1 multiplex 33 */
    GTM_TRIG_DMAL1_MUX_34,            /* DMA level 1 multiplex 34 */
    GTM_TRIG_DMAL1_MUX_35,            /* DMA level 1 multiplex 35 */
    GTM_TRIG_DMAL1_MUX_36,            /* DMA level 1 multiplex 36 */
    GTM_TRIG_DMAL1_MUX_37,            /* DMA level 1 multiplex 37 */
#endif
    GTM_TRIG_DMAL1_COMMUX_0 = 32U,  /* DMA level 1 common multiplex 0 */
    GTM_TRIG_DMAL1_COMMUX_1,        /* DMA level 1 common multiplex 1 */
    GTM_TRIG_DMAL1_COMMUX_2,        /* DMA level 1 common multiplex 2 */
    GTM_TRIG_DMAL1_COMMUX_3,        /* DMA level 1 common multiplex 3 */
    GTM_TRIG_DMAL1_COMMUX_4,        /* DMA level 1 common multiplex 4 */
    GTM_TRIG_DMAL1_COMMUX_5,        /* DMA level 1 common multiplex 5 */
    GTM_TRIG_DMAL1_COMMUX_6,        /* DMA level 1 common multiplex 6 */
    GTM_TRIG_DMAL1_COMMUX_7,        /* DMA level 1 common multiplex 7 */
    GTM_TRIG_DMAL1_COMMUX_8,        /* DMA level 1 common multiplex 8 */
    GTM_TRIG_DMAL1_COMMUX_9,        /* DMA level 1 common multiplex 9 */
#if defined(THA6_THA6412)
    GTM_TRIG_DMAL1_MUX_40,            /* DMA level 1 multiplex 40 */
    GTM_TRIG_DMAL1_MUX_41,            /* DMA level 1 multiplex 41 */
    GTM_TRIG_DMAL1_MUX_42,            /* DMA level 1 multiplex 42 */
    GTM_TRIG_DMAL1_MUX_43,            /* DMA level 1 multiplex 43 */
    GTM_TRIG_DMAL1_MUX_44,            /* DMA level 1 multiplex 44 */
    GTM_TRIG_DMAL1_MUX_45,            /* DMA level 1 multiplex 45 */
    GTM_TRIG_DMAL1_MUX_46,            /* DMA level 1 multiplex 46 */
    GTM_TRIG_DMAL1_MUX_47,            /* DMA level 1 multiplex 47 */
    GTM_TRIG_DMAL1_MUX_50,            /* DMA level 1 multiplex 50 */
    GTM_TRIG_DMAL1_MUX_51,            /* DMA level 1 multiplex 51 */
    GTM_TRIG_DMAL1_MUX_52,            /* DMA level 1 multiplex 52 */
    GTM_TRIG_DMAL1_MUX_53,            /* DMA level 1 multiplex 53 */
    GTM_TRIG_DMAL1_MUX_54,            /* DMA level 1 multiplex 54 */
    GTM_TRIG_DMAL1_MUX_55,            /* DMA level 1 multiplex 55 */
    GTM_TRIG_DMAL1_MUX_56,            /* DMA level 1 multiplex 56 */
    GTM_TRIG_DMAL1_MUX_57,            /* DMA level 1 multiplex 57 */
    GTM_TRIG_DMAL1_MUX_60,            /* DMA level 1 multiplex 60 */
    GTM_TRIG_DMAL1_MUX_61,            /* DMA level 1 multiplex 61 */
    GTM_TRIG_DMAL1_MUX_62,            /* DMA level 1 multiplex 62 */
    GTM_TRIG_DMAL1_MUX_63,            /* DMA level 1 multiplex 63 */
    GTM_TRIG_DMAL1_MUX_64,            /* DMA level 1 multiplex 64 */
    GTM_TRIG_DMAL1_MUX_65,            /* DMA level 1 multiplex 65 */
    GTM_TRIG_DMAL1_MUX_66,            /* DMA level 1 multiplex 66 */
    GTM_TRIG_DMAL1_MUX_67,            /* DMA level 1 multiplex 67 */
    GTM_TRIG_DMAL1_MUX_70,            /* DMA level 1 multiplex 70 */
    GTM_TRIG_DMAL1_MUX_71,            /* DMA level 1 multiplex 71 */
    GTM_TRIG_DMAL1_MUX_72,            /* DMA level 1 multiplex 72 */
    GTM_TRIG_DMAL1_MUX_73,            /* DMA level 1 multiplex 73 */
    GTM_TRIG_DMAL1_MUX_74,            /* DMA level 1 multiplex 74 */
    GTM_TRIG_DMAL1_MUX_75,            /* DMA level 1 multiplex 75 */
    GTM_TRIG_DMAL1_MUX_76,            /* DMA level 1 multiplex 76 */
    GTM_TRIG_DMAL1_MUX_77            /* DMA level 1 multiplex 77 */
#endif
} Gtm_Trig_DmaL1;

/* Enum for DMA channel */
typedef enum
{
    GTM_TRIG_DMACHANNEL_0 = 0U,    /* DMA trigger channel 0 */
    GTM_TRIG_DMACHANNEL_1,        /* DMA trigger channel 1 */
    GTM_TRIG_DMACHANNEL_2,        /* DMA trigger channel 2 */
    GTM_TRIG_DMACHANNEL_3,        /* DMA trigger channel 3 */
    GTM_TRIG_DMACHANNEL_4,        /* DMA trigger channel 4 */
    GTM_TRIG_DMACHANNEL_5,        /* DMA trigger channel 5 */
    GTM_TRIG_DMACHANNEL_6,        /* DMA trigger channel 6 */
    GTM_TRIG_DMACHANNEL_7        /* DMA trigger channel 7 */
} Gtm_Trig_DmaChannel;

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
/* Enum for MSC Sets */
typedef enum
{
    GTM_TRIG_MSCTRIGSET_0 = 0U,     /* For MSC set 0 */
    GTM_TRIG_MSCTRIGSET_1,             /* For MSC set 1 */
    GTM_TRIG_MSCTRIGSET_2,             /* For MSC set 2 */
    GTM_TRIG_MSCTRIGSET_3,             /* For MSC set 3 */
#if defined(THA6_THA6412)
    GTM_TRIG_MSCTRIGSET_4,             /* For MSC set 4 */
    GTM_TRIG_MSCTRIGSET_5,             /* For MSC set 5 */
    GTM_TRIG_MSCTRIGSET_6,             /* For MSC set 6 */
#endif
    GTM_TRIG_MSCTRIGSET_COUNT          /* Count of the enum definition */
} Gtm_Trig_MscTrigSet;
#endif

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
/* Enum for MSC Signal */
typedef enum
{
    GTM_TRIG_MSCTRIGSIGNAL_0 = 0U,      /* For MSC set n mux 0  */
    GTM_TRIG_MSCTRIGSIGNAL_1,             /* For MSC set n mux 1  */
    GTM_TRIG_MSCTRIGSIGNAL_2,             /* For MSC set n mux 2  */
    GTM_TRIG_MSCTRIGSIGNAL_3,             /* For MSC set n mux 3  */
    GTM_TRIG_MSCTRIGSIGNAL_4,             /* For MSC set n mux 4  */
    GTM_TRIG_MSCTRIGSIGNAL_5,             /* For MSC set n mux 5  */
    GTM_TRIG_MSCTRIGSIGNAL_6,             /* For MSC set n mux 6  */
    GTM_TRIG_MSCTRIGSIGNAL_7,             /* For MSC set n mux 7  */
    GTM_TRIG_MSCTRIGSIGNAL_8,             /* For MSC set n mux 8  */
    GTM_TRIG_MSCTRIGSIGNAL_9,             /* For MSC set n mux 9  */
    GTM_TRIG_MSCTRIGSIGNAL_10,            /* For MSC set n mux 10  */
    GTM_TRIG_MSCTRIGSIGNAL_11,            /* For MSC set n mux 11  */
    GTM_TRIG_MSCTRIGSIGNAL_12,            /* For MSC set n mux 12  */
    GTM_TRIG_MSCTRIGSIGNAL_13,            /* For MSC set n mux 13  */
    GTM_TRIG_MSCTRIGSIGNAL_14,            /* For MSC set n mux 14  */
    GTM_TRIG_MSCTRIGSIGNAL_15             /* For MSC set n mux 15  */
} Gtm_Trig_MscTrigSignal;
#endif

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
/* Enum for MSC trigger input type */
typedef enum
{
    GTM_TRIG_MSCTRIGINPUT_LOW = 0U,       /* MSC SR low */
    GTM_TRIG_MSCTRIGINPUT_LOWEXTENDED,    /* MSC SR low extend */
    GTM_TRIG_MSCTRIGINPUT_HIGH            /* MSC SR high */
} Gtm_Trig_MscTrigInput;
#endif

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
/* Enum for MSC number */
typedef enum
{
    GTM_TRIG_MSCNUM_0 = 0U,        /* MSC 0 */
#if defined(THA6_THA6412)
    GTM_TRIG_MSCNUM_1,             /* MSC 1 */
    GTM_TRIG_MSCNUM_2              /* MSC 2 */
#endif
} Gtm_Trig_MscNum;
#endif

/* Enum for multiplexer value */
typedef enum
{
    GTM_CHXSEL_0 = 0U,        /* Gtm multiplexer selection 0 */
    GTM_CHXSEL_1,            /* Gtm multiplexer selection 1 */
    GTM_CHXSEL_2,            /* Gtm multiplexer selection 2 */
    GTM_CHXSEL_3,            /* Gtm multiplexer selection 3 */
    GTM_CHXSEL_4,            /* Gtm multiplexer selection 4 */
    GTM_CHXSEL_5,            /* Gtm multiplexer selection 5 */
    GTM_CHXSEL_6,            /* Gtm multiplexer selection 6 */
    GTM_CHXSEL_7,            /* Gtm multiplexer selection 7 */
    GTM_CHXSEL_8,            /* Gtm multiplexer selection 8 */
    GTM_CHXSEL_9,            /* Gtm multiplexer selection 9 */
    GTM_CHXSEL_10,           /* Gtm multiplexer selection 10 */
    GTM_CHXSEL_11,           /* Gtm multiplexer selection l1*/
    GTM_CHXSEL_12,           /* Gtm multiplexer selection 12 */
    GTM_CHXSEL_13,           /* Gtm multiplexer selection 13 */
    GTM_CHXSEL_14,           /* Gtm multiplexer selection 14 */
    GTM_CHXSEL_15            /* Gtm multiplexer selection 15 */
} Gtm_ChxSel;

/* Enum for multiplexer value */
typedef enum
{
    GTM_TOUTSEL_0 = 0U,        /* Gtm Tout multiplexer selection 0 */
    GTM_TOUTSEL_1,          /* Gtm Tout multiplexer selection 1 */
    GTM_TOUTSEL_2,          /* Gtm Tout multiplexer selection 2 */
    GTM_TOUTSEL_3,          /* Gtm Tout multiplexer selection 3 */
    GTM_TOUTSEL_4,          /* Gtm Tout multiplexer selection 4 */
    GTM_TOUTSEL_5,          /* Gtm Tout multiplexer selection 5 */
    GTM_TOUTSEL_6,          /* Gtm Tout multiplexer selection 6 */
    GTM_TOUTSEL_7,          /* Gtm Tout multiplexer selection 7 */
    GTM_TOUTSEL_8,          /* Gtm Tout multiplexer selection 8 */
    GTM_TOUTSEL_9,          /* Gtm Tout multiplexer selection 9 */
    GTM_TOUTSEL_10,         /* Gtm Tout multiplexer selection 10 */
    GTM_TOUTSEL_11,          /* Gtm Tout multiplexer selection 11 */
    GTM_TOUTSEL_12,         /* Gtm Tout multiplexer selection 12 */
    GTM_TOUTSEL_13,         /* Gtm Tout multiplexer selection 13 */
    GTM_TOUTSEL_14,         /* Gtm Tout multiplexer selection 14 */
    GTM_TOUTSEL_15          /* Gtm Tout multiplexer selection 15 */
} Gtm_ToutSel;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* ADCTRIG configuration */
typedef struct
{
    Gtm_Trig_AdcGroup         adcGroup;   /* ADC group */
    Gtm_Trig_AdcTrig          adcTrig;    /* ADC trigger */
    Gtm_ChxSel                select;     /* ADC multiplexer value */
/* #Violation: gtm_trig_hal_h_REF_1 */
/* #Violation: gtm_trig_hal_h_REF_2 */
} Gtm_AdcTrigConfig;

/* DMATRIG configuration */
typedef struct
{
    Gtm_Trig_DmaL1            trigL1Mux;    /* Level 1 DMA trigger multiplex */
    uint32                    select;       /* DMA level 1 multiplexer value */
/* #Violation: gtm_trig_hal_h_REF_1 */
/* #Violation: gtm_trig_hal_h_REF_2 */
} Gtm_DmaTrigL1Config;

/* DMATRIG configuration */
typedef struct
{
    Gtm_Trig_DmaL1             trigL1Mux;    /* Level 1 DMA trigger multiplex */
    Gtm_Trig_DmaChannel        dmaChannel;   /* DMA channel index */
/* #Violation: gtm_trig_hal_h_REF_1 */
/* #Violation: gtm_trig_hal_h_REF_2 */
} Gtm_DmaTrigL2Config;

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
/* MSCTRIG configuration */
typedef struct
{
    Gtm_Trig_MscTrigSet       mscSet;     /* MSC Sets */
    Gtm_Trig_MscTrigSignal    signals;    /* MSC signal */
    uint32                    select;     /* MSC level 1 multiplexer value */
/* #Violation: gtm_trig_hal_h_REF_1 */
/* #Violation: gtm_trig_hal_h_REF_2 */
/* #Violation: gtm_trig_hal_h_REF_5 */
} Gtm_MscTrigL1Config;
#endif

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
/* MSCTRIG configuration */
typedef struct
{
    Gtm_Trig_MscTrigSet     mscSet;     /* MSC Sets */
    Gtm_Trig_MscTrigInput   input;      /* MSC input */
    Gtm_Trig_MscTrigSignal  signals;    /* MSC Signal */
    Gtm_Trig_MscNum         Num;        /* MSC num */
/* #Violation: gtm_trig_hal_h_REF_1 */
/* #Violation: gtm_trig_hal_h_REF_2 */
/* #Violation: gtm_trig_hal_h_REF_5 */
} Gtm_MscTrigL2Config;
#endif

/* TIM pin mapping structure */
typedef struct
{
    Gtm_Tim_Index        tim;        /* TIM index */
    Gtm_Tim_Ch_Index     channel;    /* TIM channel index */
    Gtm_ChxSel           select;     /* Input multiplexer value */
/* #Violation: gtm_trig_hal_h_REF_1 */
/* #Violation: gtm_trig_hal_h_REF_2 */
} Gtm_Tim_In;

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
/* DSADC input mapping structure */
typedef struct
{
    uint8        index;      /* Index, corresponding to TIM index. */
    uint8        mux;        /* Mux index, corresponding to TIM channel index. */
    Gtm_ChxSel   select;     /* Input multiplexer value */
/* #Violation: gtm_trig_hal_h_REF_1 */
/* #Violation: gtm_trig_hal_h_REF_2 */
/* #Violation: gtm_trig_hal_h_REF_5 */
} Gtm_Dsadc_In;
#endif

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
/* DSADCTRIG mapping structure */
typedef struct
{
    uint8        index;      /* Index, output mapping index. */
    uint8        mux;        /* Mux index, corresponding to DSADC index */
    Gtm_ChxSel   select;     /* Multiplexer value */
/* #Violation: gtm_trig_hal_h_REF_1 */
/* #Violation: gtm_trig_hal_h_REF_2 */
/* #Violation: gtm_trig_hal_h_REF_5 */
} Gtm_Dsadc_Out;
#endif

/* (A)TOM pin mapping structure */
typedef struct
{
    Gtm_ToutSel      toutSel;    /* Output multiplexer value */
    uint32           toutNum;    /* TOUT number */
/* #Violation: gtm_trig_hal_h_REF_1 */
/* #Violation: gtm_trig_hal_h_REF_2 */
} Gtm_Tout_Out;
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/* #Violation: gtm_trig_hal_h_REF_4 */
#define GTM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_trig_hal_h_REF_3 */
#include "Gtm_MemMap.h"

/**********************************************************************************************************************
 * Function:     Gtm_Trig_Hal_ToSaradc
 * Description:  Configuration of connections between GTM and SARADC/SENT/FC/DSADC
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pConfig: ADCTRIG configuration
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *  2023/08/02    01031      Parameter modification
 *********************************************************************************************************************/
extern boolean Gtm_Trig_Hal_ToSaradc(const Gtm_AdcTrigConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Gtm_Trig_Hal_ToDmaL1
 * Description:  Configuration of connections between GTM interrupt and DMA level 1 MUX
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pConfig: DMATRIG level 1 configuration
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *  2023/08/03    01031      Parameter modification
 *********************************************************************************************************************/
extern boolean Gtm_Trig_Hal_ToDmaL1(const Gtm_DmaTrigL1Config *const pConfig);

/*********************************************************************************************************************
 * Function:     Gtm_Trig_Hal_ToDmaL2
 * Description:  Configuration of connections between DMA level 1 MUX and DMA
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pConfig: DMATRIG level 2 configuration
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/03    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Trig_Hal_ToDmaL2(const Gtm_DmaTrigL2Config *const pConfig);

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
/**********************************************************************************************************************
 * Function:     Gtm_Trig_Hal_ToMscL1
 * Description:  Configuration of connections between GTM and MSC level 1 MUX
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pConfig: MSCTRIG level 1 configuration
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Trig_Hal_ToMscL1(const Gtm_MscTrigL1Config *const pConfig);
#endif /* THA6_THA6206 || THA6_THA6206D || THA6_THA6412 */

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
/**********************************************************************************************************************
 * Function:     Gtm_Trig_Hal_ToMscL2
 * Description:  Configuration of connections between MSC level 1 MUX and MSC
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pConfig: MSCTRIG level 2 configuration
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Trig_Hal_ToMscL2(const Gtm_MscTrigL2Config *const pConfig);
#endif /* THA6_THA6206 || THA6_THA6206D || THA6_THA6412 */

/**********************************************************************************************************************
 * Function:     Gtm_Trig_Hal_TimIn
 * Description:  Configuration of connections between GTM TIM and IO/DSADCINMUX/SARADC/CAN/FC/EXTI
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTin: The structure of TIM input
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Trig_Hal_TimIn(const Gtm_Tim_In *const pTin);

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
/**********************************************************************************************************************
 * Function:     Gtm_Trig_Hal_DsadcIn
 * Description:  Configuration of connections between DSADC and GTM DSADCINMUX
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDsadcIn: The structure of DSADC input
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/04/09    01177     Create
 *********************************************************************************************************************/
extern boolean Gtm_Trig_Hal_DsadcIn(const Gtm_Dsadc_In *const pDsadcIn);
#endif /* THA6_THA6206 || THA6_THA6206D || THA6_THA6412 */

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
/**********************************************************************************************************************
 * Function:     Gtm_Trig_Hal_ToDsadc
 * Description:  Configuration of connections between GTM (A)TOM and DSADC/SENT Trigger input
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDsadcIn: The structure of DSADCTRIG mapping
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/06/21    01177     Create
 *********************************************************************************************************************/
extern boolean Gtm_Trig_Hal_ToDsadc(const Gtm_Dsadc_Out *const pDsadcOut);
#endif /* THA6_THA6206 || THA6_THA6206D || THA6_THA6412 */

/**********************************************************************************************************************
 * Function:     Gtm_Trig_Hal_ToutOut
 * Description:  Configuration of connections between GTM (A)TOM and IO
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTout: The structure of TOUT output
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Trig_Hal_ToutOut(const Gtm_Tout_Out *const pTout);

/* #Violation: gtm_trig_hal_h_REF_4 */
#define GTM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_trig_hal_h_REF_3 */
#include "Gtm_MemMap.h"
#endif /* GTM_TRIG_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
