/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName   : exti_hal.h
 * Author     : 01077
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all hardware abstract layer data type definitions and
 *              function declarations.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
* #Violation Summary
*
* #exti_hal_h_REF_1:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
* #exti_hal_h_REF_2:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #exti_hal_h_REF_3:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*/
#ifndef EXTI_HAL_H_
#define EXTI_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "exti_register.h"
#include "Platform_Types.h"
#include "compilertypes.h"
#include "cpuwdt_hal.h"
#include "tha6_cfg.h"

/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
#define EXTI_REG_CHECK

/* Register offset 16 */
#define EXTI_REGISTER_OFFSET_16 (16U)

/* Select pattern detect input signal */
/* ETL don't participation pattern detection */
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_PATTERNDETECTSELECTION_NONE (0x0U)
/* ETL0 participation pattern detection */
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_PATTERNDETECTSELECTION_0 (0x1U)    
/* ETL1 participation pattern detection */
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_PATTERNDETECTSELECTION_1 (0x2U)   
/* ETL2 participation pattern detection */ 
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_PATTERNDETECTSELECTION_2 (0x4U)   
/* ETL3 participation pattern detection */ 
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_PATTERNDETECTSELECTION_3 (0x8U)    
/* ETL4 participation pattern detection */
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_PATTERNDETECTSELECTION_4 (0x10U)   
/* ETL5 participation pattern detection */
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_PATTERNDETECTSELECTION_5 (0x20U)   
/* ETL6 participation pattern detection */
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_PATTERNDETECTSELECTION_6 (0x40U)  
/* ETL7 participation pattern detection */ 
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_PATTERNDETECTSELECTION_7 (0x80U)   

/* Input filter selection */
/* Filter select None */
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_FILTERCHANNEL_NONE (0x0U)   
/* Filter select 0A */
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_FILTERCHANNEL_0A (0x1U)     
/* Filter select 5A */
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_FILTERCHANNEL_5A (0x2U)     
/* Filter select 2A */
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_FILTERCHANNEL_2A (0x4U)     
/* Filter select 3A */
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_FILTERCHANNEL_3A (0x8U)     
/* Filter select 0C */
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_FILTERCHANNEL_0C (0x10U)    
/* Filter select 1C */
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_FILTERCHANNEL_1C (0x20U)    
/* Filter select 3C */
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_FILTERCHANNEL_3C (0x40U)    
/* Filter select 2C */
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_FILTERCHANNEL_2C (0x80U)    
/* Filter select 4A */
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_FILTERCHANNEL_4A (0x100U)   
/* Filter select 6A */
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_FILTERCHANNEL_6A (0x200U)   
/* Filter select 1A */
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_FILTERCHANNEL_1A (0x400U)   
/* Filter select 7A */
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_FILTERCHANNEL_7A (0x800U)   
/* Filter select 6D */
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_FILTERCHANNEL_6D (0x1000U)  
/* Filter select 4D */
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_FILTERCHANNEL_4D (0x2000U)  
/* Filter select 2B */
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_FILTERCHANNEL_2B (0x4000U)  
/* Filter select 3B */
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_FILTERCHANNEL_3B (0x8000U)  
/* Filter select 7C */
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_FILTERCHANNEL_7C (0x10000U) 
/* Filter select 6B */
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_FILTERCHANNEL_6B (0x20000U) 
/* Filter select 7B */
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_FILTERCHANNEL_7B (0x40000U) 
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* Enum for set EXTI function enable/disable */
typedef enum
{
    EXTI_STATE_DISABLE = 0U, /* Set EXTI function state disable */
    EXTI_STATE_ENABLE        /* Set EXTI function state enable */
} Exti_State;

/* Digital glitch filter depth */
typedef enum
{
    EXTI_FILTERDEPTH_0 = 0U, /* Filter depth 0, disable all glitch filter */
    EXTI_FILTERDEPTH_1,      /* Filter depth 1  */
    EXTI_FILTERDEPTH_2,      /* Filter depth 2  */
    EXTI_FILTERDEPTH_3,      /* Filter depth 3  */
    EXTI_FILTERDEPTH_4,      /* Filter depth 4  */
    EXTI_FILTERDEPTH_5,      /* Filter depth 5  */
    EXTI_FILTERDEPTH_6,      /* Filter depth 6  */
    EXTI_FILTERDEPTH_7,      /* Filter depth 7  */
    EXTI_FILTERDEPTH_8,      /* Filter depth 8  */
    EXTI_FILTERDEPTH_9,      /* Filter depth 9  */
    EXTI_FILTERDEPTH_10,     /* Filter depth 10  */
    EXTI_FILTERDEPTH_11,     /* Filter depth 11  */
    EXTI_FILTERDEPTH_12,     /* Filter depth 12  */
    EXTI_FILTERDEPTH_13,     /* Filter depth 13  */
    EXTI_FILTERDEPTH_14,     /* Filter depth 14  */
    EXTI_FILTERDEPTH_15      /* Filter depth 15  */
} Exti_FilterDepth;

/* Digital glitch filter clock predivider */
typedef enum
{
    EXTI_FILTERPREDIVIDER_0 = 0U, /* Filter predivider 0, disable all glitch filter */
    EXTI_FILTERPREDIVIDER_1,      /* Filter predivider 1  */
    EXTI_FILTERPREDIVIDER_2,      /* Filter predivider 2  */
    EXTI_FILTERPREDIVIDER_3,      /* Filter predivider 3  */
    EXTI_FILTERPREDIVIDER_4,      /* Filter predivider 4  */
    EXTI_FILTERPREDIVIDER_5,      /* Filter predivider 5  */
    EXTI_FILTERPREDIVIDER_6,      /* Filter predivider 6  */
    EXTI_FILTERPREDIVIDER_7,      /* Filter predivider 7  */
    EXTI_FILTERPREDIVIDER_8,      /* Filter predivider 8  */
    EXTI_FILTERPREDIVIDER_9,      /* Filter predivider 9  */
    EXTI_FILTERPREDIVIDER_10,     /* Filter predivider 10  */
    EXTI_FILTERPREDIVIDER_11,     /* Filter predivider 11  */
    EXTI_FILTERPREDIVIDER_12,     /* Filter predivider 12  */
    EXTI_FILTERPREDIVIDER_13,     /* Filter predivider 13  */
    EXTI_FILTERPREDIVIDER_14,     /* Filter predivider 14  */
    EXTI_FILTERPREDIVIDER_15      /* Filter predivider 15  */
} Exti_FilterPredivider;

/* Etl module selection */
typedef enum
{
    EXTI_INPUTCHANNEL_0 = 0U, /* Select ETL0 */
    EXTI_INPUTCHANNEL_1,      /* Select ETL1 */
    EXTI_INPUTCHANNEL_2,      /* Select ETL2 */
    EXTI_INPUTCHANNEL_3,      /* Select ETL3 */
    EXTI_INPUTCHANNEL_4,      /* Select ETL4 */
    EXTI_INPUTCHANNEL_5,      /* Select ETL5 */
    EXTI_INPUTCHANNEL_6,      /* Select ETL6 */
    EXTI_INPUTCHANNEL_7       /* Select ETL7 */
} Exti_InputChannel;

/* Input multiplexer selection */
typedef enum
{
    EXTI_INPUTMULTIPLEXER_A = 0U, /* Input multiplex select A */
    EXTI_INPUTMULTIPLEXER_B,      /* Input multiplex select B */
    EXTI_INPUTMULTIPLEXER_C,      /* Input multiplex select C */
    EXTI_INPUTMULTIPLEXER_D,      /* Input multiplex select D */
    EXTI_INPUTMULTIPLEXER_E,      /* Input multiplex select E */
    EXTI_INPUTMULTIPLEXER_F       /* Input multiplex select F */
} Exti_InputMultiplexer;

/* Edge detect selection mode */
typedef enum
{
    EXTI_EDGEDETECTIONMODE_NONE = 0U, /* Select ETLx disable edge detect */
    EXTI_EDGEDETECTIONMODE_FAILING,   /* Select ETLx detect failing edge */
    EXTI_EDGEDETECTIONMODE_RAISING,   /* Select ETLx detect raising edge */
    EXTI_EDGEDETECTIONMODE_BOTH       /* Select ETLx detect both failing and raising edge */
} Exti_EdgeDetectionMode;

/* Ogu module selection */
typedef enum
{
    EXTI_OUTPUTCHANNEL_0 = 0U, /* Select OGU0 */
    EXTI_OUTPUTCHANNEL_1,      /* Select OGU1 */
    EXTI_OUTPUTCHANNEL_2,      /* Select OGU2 */
    EXTI_OUTPUTCHANNEL_3,      /* Select OGU3 */
    EXTI_OUTPUTCHANNEL_4,      /* Select OGU4 */
    EXTI_OUTPUTCHANNEL_5,      /* Select OGU5 */
    EXTI_OUTPUTCHANNEL_6,      /* Select OGU6 */
    EXTI_OUTPUTCHANNEL_7       /* Select OGU7 */
} Exti_OutputChannel;

/* Select interrupt gating mode */
typedef enum
{
    EXTI_TRIGGERGATINGMODE_CLOSE = 0U, /* Trigger always disable */
    EXTI_TRIGGERGATINGMODE_OPEN,       /* Trigger always enable */
    EXTI_TRIGGERGATINGMODE_MATCH,      /* Trigger enable when pattern match */
    EXTI_TRIGGERGATINGMODE_MISS        /* Trigger enable when pattern miss */
} Exti_TriggerGatingMode;

/* Pattern detect result */
typedef enum
{
    EXTI_PATTERNDETECTRESULT_MISS = 0U, /* Pattern detect result is miss */
    EXTI_PATTERNDETECTRESULT_MATCH      /* Pattern detect result is match */
} Exti_PatternDetectResult;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* EXTI filter configuration structure */
typedef struct
{
    Exti_FilterDepth filterDepth;           /* Filter depth */
    Exti_FilterPredivider filterPredivider; /* Filter divider */
    uint32 filterMask;                      /* Filter select to enable/disable */
    Exti_State filterEnable;                /* Set selected filter enable/disable */
} Exti_FilterConfig;

/* EXTI etl module configuration structure */
typedef struct
{
    Exti_InputChannel inputChannel;           /* Select etl module to configure */
    Exti_InputMultiplexer inputMultiplexer;   /* Set etl input multiplexer */
    Exti_EdgeDetectionMode edgeDetectionMode; /* Set edge detect mode */
    Exti_State autoClear;                     /* Set auto-clear function enable/disable */
    Exti_State triggerEnable;                 /* Set interrupt trigger enable/disable */
    Exti_OutputChannel triggerOutput;         /* Select interrupt trigger output to witch OGU module */
} Exti_InputChannelConfig;

/* EXTI ogu module configuration structure */
typedef struct
{
    Exti_OutputChannel outputChannel;         /* Select ogu module to configure */
    uint32 patternDetectSelection;            /* Select ETL participate in pattern detect
                                               * (1 << 0)   EXTI_PATTERNDETECTSELECTION_0
                                               * (1 << 1)   EXTI_PATTERNDETECTSELECTION_1
                                               * (1 << 2)   EXTI_PATTERNDETECTSELECTION_2
                                               * (1 << 3)   EXTI_PATTERNDETECTSELECTION_3
                                               * (1 << 4)   EXTI_PATTERNDETECTSELECTION_4
                                               * (1 << 5)   EXTI_PATTERNDETECTSELECTION_5
                                               * (1 << 6)   EXTI_PATTERNDETECTSELECTION_6
                                               * (1 << 7)   EXTI_PATTERNDETECTSELECTION_7 */
    Exti_State patternTrigger;                /* Set pattern detect result change trigger interrupt enable/disable */
    Exti_TriggerGatingMode triggerGatingMode; /* Set interrupt gating mode */
} Exti_OutputChannelConfig;

/* EXTI module configuration structure */
typedef struct
{
    Exti_FilterConfig filterConfig;                /* EXTI filter configuration */
    uint8 inputChannelConfigLength;                /* EXTI ETL module configuration mask */
    uint8 outputChannelConfigLength;               /* EXTI OGU module configuration mask */
    Exti_InputChannelConfig *inputChannelConfig;   /* EXTI ETL module configuration array */
    Exti_OutputChannelConfig *outputChannelConfig; /* EXTI OGU module configuration array */
} Exti_Config;
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/* #Violation: exti_hal_h_REF_3 */
#define EXTI_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: exti_hal_h_REF_2 */
#include "Exti_MemMap.h"

/**********************************************************************************************************************
 * Function:    Exti_Hal_SetEventFlag
 * Description: Sets the external event flag of ETLx.
 * Sync/Async:  Synchronous
 * Reentrancy:  Non-Reentrant
 * Input:       inputChannel: Select ETLx to set external event flag.
 * Inout:       None
 * Output:      None
 * Return:      boolean: TRUE:  Register read back check correct
 *                       FALSE: Register read back check incorrect
 * Others:      None.
 * History:     None.
 * Date         Author   Modified
 * 2023/05/11   01077     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Exti_Hal_SetEventFlag(Exti_InputChannel inputChannel);

/**********************************************************************************************************************
 * Function:    Exti_Hal_ClearEventFlag
 * Description: Clears the external event flag of ETLx.
 * Sync/Async:  Synchronous
 * Reentrancy:  Non-Reentrant
 * Input:       inputChannel: Select ETLx to clear external event flag.
 * Inout:       None
 * Output:      None
 * Return:      boolean: TRUE:  Register read back check correct
 *                       FALSE: Register read back check incorrect
 * Others:      None.
 * Histor:      None.
 * Date         Author   Modified
 * 2023/05/11   01077     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Exti_Hal_ClearEventFlag(Exti_InputChannel inputChannel);

/**********************************************************************************************************************
 * Function:    Exti_Hal_GetEventFlag
 * Description: Get the external event flag of ETLx.
 * Sync/Async:  Synchronous
 * Reentrancy:  Reentrant
 * Input:       inputChannel: Select ETLx to get external event flag.
 * Inout:       None
 * Output:      None
 * Return:      boolean: TRUE: Event flag is 1
 *                       FALSE: Event flag is 0
 * Others: None.
 * History: None.
 * Date         Author   Modified
 * 2023/05/11   01077     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Exti_Hal_GetEventFlag(Exti_InputChannel inputChannel);

/**********************************************************************************************************************
 * Function:     Exti_Register_ReadBack_Check
 * Description:  Check register read back value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        state: Indicates whether the register is configured correctly
 *               expect: Expect value
 *               actual: Actual value
 * Inout:       None
 * Output:       None
 * Return:       boolean: Indicates whether the register is configured correctly
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/03/10    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Exti_Register_ReadBack_Check(boolean state, uint32 expect, uint32 actual);

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Exti_Hal_SetEventFlag(Exti_InputChannel inputChannel)
{
    boolean ret;

    ret = TRUE;
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();                           /* Unlock endinit protect */
    /* #Violation: exti_hal_h_REF_1 */
    EXTI->FLBMR.U = ((uint32)1 << (uint32)inputChannel); /* Set flag */
    ret &= Cpuwdt_Hal_SetEndinit();                             /* Lock endinit protect */
    ENABLE_ALL_INTERRUPTS();

    return ret;
}

LOCAL_FORCEINLINE boolean Exti_Hal_ClearEventFlag(Exti_InputChannel inputChannel)
{
    boolean ret;

    ret = TRUE;
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();                                                      /* Unlock endinit protect */
    /* #Violation: exti_hal_h_REF_1 */
    EXTI->FLBMR.U = ((uint32)1 << (uint32)inputChannel) << EXTI_REGISTER_OFFSET_16; /* Clear flag */
    ret &= Cpuwdt_Hal_SetEndinit();                                                        /* Lock endinit protect */
    ENABLE_ALL_INTERRUPTS();

    return ret;
}

LOCAL_FORCEINLINE boolean Exti_Hal_GetEventFlag(Exti_InputChannel inputChannel)
{
    /* #Violation: exti_hal_h_REF_1 */
    return (boolean)(((uint32)EXTI->ETIPF.U >> (uint32)inputChannel) & 1U);
}

#if defined(EXTI_REG_CHECK)
LOCAL_FORCEINLINE boolean Exti_Register_ReadBack_Check(boolean state, uint32 expect, uint32 actual)
{
    boolean ret;
    ret = state;
    if (expect != actual)
    {
        ret &= FALSE;
    }
    return ret;
}
#else
LOCAL_FORCEINLINE boolean Exti_Register_ReadBack_Check(boolean state, uint32 expect, uint32 actual)
{
    (void)state;
    (void)expect;
    (void)actual;
    return state;
}
#endif

/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:    Exti_Hal_Init
 * Description: Initializing the EXTI module based on the configuration contained in the structure.
 * Sync/Async:  Synchronous
 * Reentrancy:  Non-Reentrant
 * Input:       pConfig: Pointer to EXTI configuration.
 * Inout:       None
 * Output:      None
 * Return:      boolean: TRUE:  Register read back check correct
 *                       FALSE: Register read back check incorrect
 * Others:      None.
 * History:     None.
 * Date         Author   Modified
 * 2023/05/11   01077     create
 *********************************************************************************************************************/
extern boolean Exti_Hal_Init(const Exti_Config *const pConfig);

/**********************************************************************************************************************
 * Function:    Exti_Hal_InitFilter
 * Description: Initializing the EXTI filter based on the configuration contained in the structure.
 * Sync/Async:  Synchronous
 * Reentrancy:  Non-Reentrant
 * Input:       pConfig: Pointer to EXTI filter configuration.
 * Inout:       None
 * Output:      None
 * Return:      boolean: TRUE:  Register read back check correct
 *                       FALSE: Register read back check incorrect
 * Others:      None.
 * History:     None.
 * Date         Author   Modified
 * 2023/05/11   01077     create
 *********************************************************************************************************************/
extern boolean Exti_Hal_InitFilter(const Exti_FilterConfig *const pConfig);

/**********************************************************************************************************************
 * Function:    Exti_Hal_InitInputChannel
 * Description: Initializing the EXTI ETL based on the configuration contained in the structure.
 * Sync/Async:  Synchronous
 * Reentrancy:  Non-Reentrant
 * Input:       pConfig: Pointer to EXTI ETL configuration.
 * Inout:       None
 * Output:      None
 * Return:      boolean: TRUE:  Register read back check correct
 *                       FALSE: Register read back check incorrect
 * Others:      None.
 * History:     None.
 * Date         Author   Modified
 * 2023/05/11   01077     create
 *********************************************************************************************************************/
extern boolean Exti_Hal_InitInputChannel(const Exti_InputChannelConfig *const pConfig);

/**********************************************************************************************************************
 * Function:    Exti_Hal_InitOutputChannel
 * Description: Initializing the EXTI OGU based on the configuration contained in the structure.
 * Sync/Async:  Synchronous
 * Reentrancy:  Non-Reentrant
 * Input:       pConfig: Pointer to EXTI OGU configuration.
 * Inout:       None
 * Output:      None
 * Return:      boolean: TRUE:  Register read back check correct
 *                       FALSE: Register read back check incorrect
 * Others:      None.
 * History:     None.
 * Date         Author   Modified
 * 2023/05/11   01077     create
 *********************************************************************************************************************/
extern boolean Exti_Hal_InitOutputChannel(const Exti_OutputChannelConfig *const pConfig);

/**********************************************************************************************************************
 * Function:    Exti_Hal_GetPatternDetectResult
 * Description: Get the pattern detection result of OGUy.
 * Sync/Async:  Synchronous
 * Reentrancy:  Reentrant
 * Input:       outputChannel: Select OGUy to get pattern detection result.
 * Inout:       None
 * Output:      None
 * Return:      Exti_PatternDetectResult: EXTI_PATTERNDETECTRESULT_MISS: Pattern detection result miss.
 *                                        EXTI_PATTERNDETECTRESULT_MATCH: Pattern detection result match.
 * Others:      None.
 * History:     None.
 * Date         Author   Modified
 * 2023/05/11   01077     create
 *********************************************************************************************************************/
extern Exti_PatternDetectResult Exti_Hal_GetPatternDetectResult(Exti_OutputChannel outputChannel);

/* #Violation: exti_hal_h_REF_3 */
#define EXTI_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: exti_hal_h_REF_2 */
#include "Exti_MemMap.h"
#endif /* EXTI_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
