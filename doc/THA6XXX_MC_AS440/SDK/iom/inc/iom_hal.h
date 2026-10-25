/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    iom_hal.h
 * Author:      00915
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations.
 *********************************************************************************************************************/

/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
*#Violation Summary
*
*#iom_hal_h_REF_1:MISRAC2012-Rule-2.3;
* Justification:The members of the type are used in configuration-generated code.
*
*/

#ifndef IOM_HAL_H_
#define IOM_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "compilertypes.h"
#include "iom_register.h"
#include "tha6_cfg.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* Offset for rising edge detected */
#define IOM_PPUESTS_REDC_OFF (16u)

/* Offset for IOM_EMUESEL_Bits.RCES0 */
#define IOM_EMUESEL_RCES0_OFF (16u)

/* Offset for IOM_EMUCCFG_Bits.TEC0 */
#define IOM_EMUCCFG_TEC0_OFF (4u)

/* Offset for IOM_EMUCCFG_Bits.SELC1 */
#define IOM_EMUCCFG_SELC1_OFF (8u)

/* Get type of reference input signal */
#define IOM_LPU_GET_REF_INPUT_SIGNAL(refInput) (((uint32)refInput >> 8u) & 0xFFu)

/* Get type of monitor input signal */
#define IOM_LPU_GET_MON_INPUT_SIGNAL(monInput) (((uint32)monInput >> 8u) & 0xFFu)

/* Get PPU index of reference input signal */
#define IOM_LPU_GET_REF_INPUT_INDEX(refInput)  ((uint32)refInput & 0xFFu)

/* Get PPU index of monitor input signal */
#define IOM_LPU_GET_MON_INPUT_INDEX(monInput)  ((uint32)monInput & 0xFFu)

/* Mask for IOM_EMUETH0_Bits.AEH0/IOM_EMUETH1_Bits.AEH2 */
#define IOM_EMUETH_AEH0_AEH2_MASK    (0xFFFFu)

/* Offset for IOM_EMUETH0_Bits.AEH1/IOM_EMUETH1_Bits.AEH3 */
#define IOM_EMUETH_AEH1_AEH3_OFF    (16u)

#define IOM_REG_CHECK
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* IOM event source configuration */
typedef enum
{
    IOM_LPUEVENTSOURCE_MON                       = 0,  /* Monitor signal is sourced directly from PPU monitor channel */
    IOM_LPUEVENTSOURCE_MONXORREF                       /* Monitor signal is EXOR'd with PPU reference channel */
} Iom_LpuEventSource;

/* IOM event trigger configuration */
typedef enum
{
    IOM_LPUEVENTTRIGGER_NONE                     = 0,                    /* Neither edge used to gate event generation */
    IOM_LPUEVENTTRIGGER_RISINGEDGE                  ,                    /* Positive edge used to gate event generation */
    IOM_LPUEVENTTRIGGER_FALLINGEDGE                 ,                    /* Negative edge used to gate event generation */
    IOM_LPUEVENTTRIGGER_ANYEDGE                                          /* Either edge used to gate event generation */
} Iom_LpuEventTrigger;

/* IOM Timer clear event configuration */
typedef enum
{
    IOM_LPUEVENTWINDOWCLEAREVENT_NONE                     = 0,                    /* Neither edge used to clear event windowcounter */
    IOM_LPUEVENTWINDOWCLEAREVENT_RISINGEDGE                  ,                    /* Positive edge used to clear event windowcounter */
    IOM_LPUEVENTWINDOWCLEAREVENT_FALLINGEDGE                 ,                    /* Negative edge used to clear event windowcounter */
    IOM_LPUEVENTWINDOWCLEAREVENT_ANYEDGE                                          /* Either edge used to clear event windowcounter */
} Iom_LpuEventWindowClearEvent;


/* IOM timer control source configuration */
typedef enum
{
    IOM_LPUEVENTWINDOWCONTROLSOURCE_REF          = 0,                   /* Event window generation is determined from the reference signal */
    IOM_LPUEVENTWINDOWCONTROLSOURCE_MON                                 /* Event window generation is determined from the monitor signal */
} Iom_LpuEventWindowControlSource;

/* IOM LPU timer run configuration */
typedef enum
{
    IOM_LPUEVENTWINDOWRUNCONTROL_FREERUNNING     = 0,                   /* Event window generation is free-running. */
    IOM_LPUEVENTWINDOWRUNCONTROL_GATED                                  /* Event window generation is gated with the monitor or reference signal */
} Iom_LpuEventWindowRunControl;

/* IOM PPU filer mode */
typedef enum
{
    IOM_PPUFILTERMODE_DELAYDEBOUNCEBOTHEDGE                             = 0,  /* Delayed Debounce Filter Mode on both edges */
    IOM_PPUFILTERMODE_IMMEDIATEDEBOUNCEBOTHEDGE                         = 1,  /* Immediate Debounce Filter Mode on both edges */
    IOM_PPUFILTERMODE_IMMEDIATEDEBOUNCERISINGEDGE                       = 2,  /* Rising edge: Immediate Debounce Filter Mode, falling edge: no filtering */
    IOM_PPUFILTERMODE_IMMEDIATEDEBOUNCEFALLINGEDGE                      = 3,  /* Rising edge: no filtering, falling edge: Immediate Debounce Filter Mode */
    IOM_PPUFILTERMODE_DELAYDEBOUNCERISINGEDGEIMMEDIATEDEBOUNCEFALLINGEDGE = 4,  /* Rising edge: Delayed Debounce Filter Mode, falling edge: Immediate Debounce Filter Mode */
    IOM_PPUFILTERMODE_IMMEDIATEDEBOUNCERISINGEDGEDELAYDEBOUNCEFALLINGEDGE = 5,  /* Rising edge: Immediate Debounce Filter Mode, falling edge: Delayed Debounce Filter Mode */
#if defined(THA6_THA6412) || defined(THA6_THA6104)
    IOM_PPUFILTERMODE_PRESCALERONRISINGEDGE                               = 6,  /* Prescaler Mode (triggered on rising edge), only THA6412 and THA6104 support */
    IOM_PPUFILTERMODE_PRESCALERONFALLINGEDGE                              = 7,  /* Prescaler Mode (triggered on falling edge), only THA6412 and THA6104 support */
    IOM_PPUFILTERMODE_NOFILTER                                            = 8   /* No filter (value used for software only ) */
#endif
} Iom_PpuFilterMode;

/* Specifies the Logic Module Analyser (LPU) Module Number */
typedef enum
{
    IOM_LPUID_0 = 0,                    /* Specifies the LPU Id0  */
    IOM_LPUID_1   ,                     /* Specifies the LPU Id1  */
    IOM_LPUID_2   ,                     /* Specifies the LPU Id2  */
    IOM_LPUID_3   ,                     /* Specifies the LPU Id3  */
    IOM_LPUID_4   ,                     /* Specifies the LPU Id4  */
    IOM_LPUID_5   ,                     /* Specifies the LPU Id5  */
    IOM_LPUID_6   ,                     /* Specifies the LPU Id6  */
    IOM_LPUID_7   ,                     /* Specifies the LPU Id7  */
    IOM_LPUID_8   ,                     /* Specifies the LPU Id8  */
    IOM_LPUID_9   ,                     /* Specifies the LPU Id9  */
    IOM_LPUID_10  ,                     /* Specifies the LPU Id10  */
    IOM_LPUID_11  ,                     /* Specifies the LPU Id11  */
    IOM_LPUID_12  ,                     /* Specifies the LPU Id12  */
    IOM_LPUID_13  ,                     /* Specifies the LPU Id13  */
    IOM_LPUID_14  ,                     /* Specifies the LPU Id14  */
    IOM_LPUID_15                        /* Specifies the LPU Id15  */
} Iom_LpuId;


/* Specifies which active edges of the monitor and reference signals are used for the event window generation */
typedef enum
{
    IOM_EVENTACTIVEEDGESELECTION_NEITHERGATENEITHERCLEAR   = 0,     /* neither edge used to gate event generation and neither edge used to clear event window counter. */
    IOM_EVENTACTIVEEDGESELECTION_NEITHERGATEPOSITIVECLEAR  ,        /* neither edge used to gate event generation and positive edge used to clear event window counter. */
    IOM_EVENTACTIVEEDGESELECTION_NEITHERGATENEGATIVECLEAR  ,        /* neither edge used to gate event generation and negative edge used to clear event window counter. */
    IOM_EVENTACTIVEEDGESELECTION_NEITHERGATEEITHERCLEAR    ,        /* neither edge used to gate event generation and either edge used to clear event window counter. */
    IOM_EVENTACTIVEEDGESELECTION_POSITIVEGATENEITHERCLEAR  ,        /* positive edge used to gate event generation and neither edge used to clear event window counter. */
    IOM_EVENTACTIVEEDGESELECTION_POSITIVEGATEPOSITIVECLEAR ,        /* positive edge used to gate event generation and positive edge used to clear event window counter. */
    IOM_EVENTACTIVEEDGESELECTION_POSITIVEGATENEGATIVECLEAR ,        /* positive edge used to gate event generation and negative edge used to clear event window counter. */
    IOM_EVENTACTIVEEDGESELECTION_POSITIVEGATEEITHERCLEAR   ,        /* positive edge used to gate event generation and negative edge used to clear event window counter. */
    IOM_EVENTACTIVEEDGESELECTION_NEGATIVEGATENEITHERCLEAR  ,        /* negative edge used to gate event generation and neither edge used to clear event window counter. */
    IOM_EVENTACTIVEEDGESELECTION_NEGATIVEGATEPOSITIVECLEAR ,        /* negative edge used to gate event generation and positive edge used to clear event window counter. */
    IOM_EVENTACTIVEEDGESELECTION_NEGATIVEGATENEGATIVECLEAR ,        /* negative edge used to gate event generation and negative edge used to clear event window counter. */
    IOM_EVENTACTIVEEDGESELECTION_NEGATIVEGATEEITHERCLEAR   ,        /* negative edge used to gate event generation and either edge used to clear event window counter. */
    IOM_EVENTACTIVEEDGESELECTION_EITHERGATENEITHERCLEAR    ,        /* either edge used to gate event generation and neither edge used to clear event window counter. */
    IOM_EVENTACTIVEEDGESELECTION_EITHERGATEPOSITIVECLEAR   ,        /* either edge used to gate event generation and positive edge used to clear event window counter. */
    IOM_EVENTACTIVEEDGESELECTION_EITHERGATENEGATIVECLEAR   ,        /* either edge used to gate event generation and negative edge used to clear event window counter. */
    IOM_EVENTACTIVEEDGESELECTION_EITHERGATEEITHERCLEAR     ,        /* either edge used to gate event generation and either edge used to clear event window counter. */
    /* #Violation: iom_hal_h_REF_1*/
} Iom_EventActiveEdgeSelection;

/* Specifies whether the event window generation is from the monitor or reference signal */
typedef enum
{
    IOM_EVENTSOURCE_REFERENCE                    = 0,                   /* Specifies  the event window generation is from the reference signal. */
    IOM_EVENTSOURCE_MONITOR                                             /* Specifies  the event window generation is from the monitor signal. */
    /* #Violation: iom_hal_h_REF_1*/
} Iom_EventSource;

/* Specifies the number of Filter & Prescaler Cell channel Id */
typedef enum
{
    IOM_PPUID_0                           = 0,                  /* Specifies the PPU Id0  */
    IOM_PPUID_1                              ,                  /* Specifies the PPU Id1  */
    IOM_PPUID_2                              ,                  /* Specifies the PPU Id2  */
    IOM_PPUID_3                              ,                  /* Specifies the PPU Id3  */
    IOM_PPUID_4                              ,                  /* Specifies the PPU Id4  */
    IOM_PPUID_5                              ,                  /* Specifies the PPU Id5  */
    IOM_PPUID_6                              ,                  /* Specifies the PPU Id6  */
    IOM_PPUID_7                              ,                  /* Specifies the PPU Id7  */
    IOM_PPUID_8                              ,                  /* Specifies the PPU Id8  */
    IOM_PPUID_9                              ,                  /* Specifies the PPU Id9  */
    IOM_PPUID_10                             ,                  /* Specifies the PPU Id10  */
    IOM_PPUID_11                             ,                  /* Specifies the PPU Id11  */
    IOM_PPUID_12                             ,                  /* Specifies the PPU Id12  */
    IOM_PPUID_13                             ,                  /* Specifies the PPU Id13  */
    IOM_PPUID_14                             ,                  /* Specifies the PPU Id14  */
    IOM_PPUID_15                                                /* Specifies the PPU Id15  */
} Iom_PpuId;

/* PPU glitch flags */
typedef enum
{
    IOM_PPUGLITCHFLAG_NONE                     = 0,                    /* Neither edge glitch flag */
    IOM_PPUGLITCHFLAG_RISINGEDGE                  ,                    /* Positive edge glitch flag */
    IOM_PPUGLITCHFLAG_FALLINGEDGE                 ,                    /* Negative edge glitch flag */
    IOM_PPUGLITCHFLAG_ANYEDGE                                          /* Either edge glitch flag */
} Iom_PpuGlitchFlag;

/* Specifies the monitor signal input for Filter & Prescaler cell */
typedef enum
{
    IOM_MONITORSIGNAL_PORTLOGIC                  = 0,                   /* Specifies the specific pad pins as monitor signal */
    IOM_MONITORSIGNAL_0                          = 1,                   /* Specifies the monitor signal 0  */
#if defined(THA6_THA6412) || defined(THA6_THA6104)
    IOM_MONITORSIGNAL_1                          = 2,                   /* Specifies the monitor signal 1, only THA6412 and THA6104 support */
#endif
    IOM_MONITORSIGNAL_2                          = 3                    /* Specifies the monitor signal 2  */
} Iom_MonitorSignal;

/* Specifies the reference signal input for Filter & Prescaler cell */
typedef enum
{
    IOM_REFERENCESIGNAL_PORTLOGIC                = 0,                   /* Specifies the specific pad pins as reference signal */
    IOM_REFERENCESIGNAL_0                        = 1,                   /* Specifies the reference signal 0  */
#if defined(THA6_THA6412) || defined(THA6_THA6104)
    IOM_REFERENCESIGNAL_1                        = 2,                   /* Specifies the reference signal 1, only THA6412 and THA6104 support */
#endif
    IOM_REFERENCESIGNAL_2                        = 3,                   /* Specifies the reference signal 2  */
#if defined(THA6_THA6412) || defined(THA6_THA6104)
    IOM_REFERENCESIGNAL_GTMEXORCOMBINER          = 4                    /* Specifies the GTM EXOR Combiner pins, only THA6412 and THA6104 support */
#endif
} Iom_ReferenceSignal;

/* EMUCCFG.TECx(x= 0,1,2,3), Specifies which channel event output is to be routed to counterCn.*/
typedef enum
{
    IOM_EVENTCOUNTERCHANNEL_0 = 0,      /* channel 0 event output to be routed to event counter  */
    IOM_EVENTCOUNTERCHANNEL_1,          /* channel 1 event output to be routed to event counter  */
    IOM_EVENTCOUNTERCHANNEL_2,          /* channel 2 event output to be routed to event counter  */
    IOM_EVENTCOUNTERCHANNEL_3,          /* channel 3 event output to be routed to event counter  */
    IOM_EVENTCOUNTERCHANNEL_NOCOUNTER   /* invalid event channel */
} Iom_EventCounterChannel;

/* EMUCCFG.CXECx(x= 0,1,2,3), Specifies the threshold count value. Upon the counter meeting the threshold, the counter event output becomes active high */
typedef enum
{
    IOM_EVENTCOUNTERTHRESHOLD_DISABLE = 0,  /* Specifies counter event output set to inactive */
    IOM_EVENTCOUNTERTHRESHOLD_1,            /* Specifies threshold count value 1  */
    IOM_EVENTCOUNTERTHRESHOLD_2,            /* Specifies threshold count value 2  */
    IOM_EVENTCOUNTERTHRESHOLD_3,            /* Specifies threshold count value 3  */
    IOM_EVENTCOUNTERTHRESHOLD_4,            /* Specifies threshold count value 4  */
    IOM_EVENTCOUNTERTHRESHOLD_5,            /* Specifies threshold count value 5  */
    IOM_EVENTCOUNTERTHRESHOLD_6,            /* Specifies threshold count value 6  */
    IOM_EVENTCOUNTERTHRESHOLD_7,            /* Specifies threshold count value 7  */
    IOM_EVENTCOUNTERTHRESHOLD_8,            /* Specifies threshold count value 8  */
    IOM_EVENTCOUNTERTHRESHOLD_9,            /* Specifies threshold count value 9  */
    IOM_EVENTCOUNTERTHRESHOLD_10,           /* Specifies threshold count value 10  */
    IOM_EVENTCOUNTERTHRESHOLD_11,           /* Specifies threshold count value 11  */
    IOM_EVENTCOUNTERTHRESHOLD_12,           /* Specifies threshold count value 12  */
    IOM_EVENTCOUNTERTHRESHOLD_13,           /* Specifies threshold count value 13  */
    IOM_EVENTCOUNTERTHRESHOLD_14,           /* Specifies threshold count value 14  */
    IOM_EVENTCOUNTERTHRESHOLD_15            /* Specifies threshold count value 15  */
} Iom_EventCounterThreshold;

/* LPU monitor inputs */
 typedef enum
 {
     IOM_MONINPUT_P33_0                          = 0x0,     /* Specifies the p33.0  in PPU 0  */
     IOM_MONINPUT_P33_1                               ,     /* Specifies THE P33.1  IN PPU 1  */
     IOM_MONINPUT_P33_2                               ,     /* Specifies the p33.2  in PPU 2  */
     IOM_MONINPUT_P33_3                               ,     /* Specifies the p33.3  in PPU 3  */
     IOM_MONINPUT_P33_4                               ,     /* Specifies the p33.4  in PPU 4  */
     IOM_MONINPUT_P33_5                               ,     /* Specifies the p33.5  in PPU 5  */
     IOM_MONINPUT_P33_6                               ,     /* Specifies the p33.6  in PPU 6  */
     IOM_MONINPUT_P33_7                               ,     /* Specifies the p33.7  in PPU 7  */
     IOM_MONINPUT_P33_8                               ,     /* Specifies the p33.8  in PPU 8  */
     IOM_MONINPUT_P33_9                               ,     /* Specifies the p33.9  in PPU 9  */
     IOM_MONINPUT_P33_10                              ,     /* Specifies the p33.10 in PPU a  */
     IOM_MONINPUT_P33_11                              ,     /* Specifies the p33.11 in PPU b  */
     IOM_MONINPUT_P33_12                              ,     /* Specifies the p33.12 in PPU c  */
     IOM_MONINPUT_P20_12                              ,     /* Specifies the p20.12 in PPU d  */
     IOM_MONINPUT_P20_13                              ,     /* Specifies the p20.13 in PPU e  */
     IOM_MONINPUT_P20_14                              ,     /* Specifies the p20.14 in PPU f  */
     IOM_MONINPUT_GTMTOUT22                    = 0x100,     /* Specifies the gtmTout22 in PPU 0  */
     IOM_MONINPUT_GTMTOUT23                           ,     /* Specifies the gtmTout23 in PPU 1  */
     IOM_MONINPUT_GTMTOUT24                           ,     /* Specifies the gtmTout24 in PPU 2  */
     IOM_MONINPUT_GTMTOUT25                           ,     /* Specifies the gtmTout25 in PPU 3  */
     IOM_MONINPUT_GTMTOUT26                           ,     /* Specifies the gtmTout26 in PPU 4  */
     IOM_MONINPUT_GTMTOUT27                           ,     /* Specifies the gtmTout27 in PPU 5  */
     IOM_MONINPUT_GTMTOUT28                           ,     /* Specifies the gtmTout28 in PPU 6  */
     IOM_MONINPUT_GTMTOUT29                           ,     /* Specifies the gtmTout29 in PPU 7  */
     IOM_MONINPUT_GTMTOUT30                           ,     /* Specifies the gtmTout30 in PPU 8  */
     IOM_MONINPUT_GTMTOUT31                           ,     /* Specifies the gtmTout31 in PPU 9  */
     IOM_MONINPUT_GTMTOUT32                           ,     /* Specifies the gtmTout32 in PPU a  */
     IOM_MONINPUT_GTMTOUT33                           ,     /* Specifies the gtmTout33 in PPU b  */
     IOM_MONINPUT_GTMTOUT34                           ,     /* Specifies the gtmTout34 in PPU c  */
     IOM_MONINPUT_GTMTOUT68                           ,     /* Specifies the gtmTout68 in PPU d  */
     IOM_MONINPUT_GTMTOUT69                           ,     /* Specifies the gtmTout69 in PPU e  */
     IOM_MONINPUT_GTMTOUT70                           ,     /* Specifies the gtmTout70 in PPU f  */
#if defined(THA6_THA6104)
     IOM_MONINPUT_GTMTIO1G0OUT0                 = 0x200,     /* Specifies the gtmTio1out0 in PPU 0, only THA6104 support */
     IOM_MONINPUT_GTMTIO1G0OUTN0                       ,     /* Specifies the gtmTio1outn0 in PPU 1, only THA6104 support */
     IOM_MONINPUT_GTMTIO1G0OUT1                        ,     /* Specifies the gtmTio1out1 in PPU 2, only THA6104 support */
     IOM_MONINPUT_GTMTIO1G0OUTN1                       ,     /* Specifies the gtmTio1outn1 in PPU 3, only THA6104 support */
     IOM_MONINPUT_GTMTIO1G0OUT2                        ,     /* Specifies the gtmTio1out2 in PPU 4, only THA6104 support */
     IOM_MONINPUT_GTMTIO1G0OUTN2                       ,     /* Specifies the gtmTio1outn2 in PPU 5, only THA6104 support */
     IOM_MONINPUT_GTMTIO1G0OUT3                        ,     /* Specifies the gtmTio1out3 in PPU 6, only THA6104 support */
     IOM_MONINPUT_GTMTIO1G0OUTN3                       ,     /* Specifies the gtmTio1outn3 in PPU 7, only THA6104 support */
     IOM_MONINPUT_GTMTIO1G0OUT4                        ,     /* Specifies the gtmTio1out4 in PPU 8, only THA6104 support */
     IOM_MONINPUT_GTMTIO1G0OUTN4                       ,     /* Specifies the gtmTio1outn4 in PPU 9, only THA6104 support */
     IOM_MONINPUT_GTMTIO1G0OUT5                        ,     /* Specifies the gtmTio1out5 in PPU a, only THA6104 support */
     IOM_MONINPUT_GTMTIO1G0OUTN5                       ,     /* Specifies the gtmTio1outn5 in PPU b, only THA6104 support */
     IOM_MONINPUT_GTMTIO1G0OUT6                        ,     /* Specifies the gtmTio1out6 in PPU c, only THA6104 support */
     IOM_MONINPUT_GTMTIO1G0OUTN6                       ,     /* Specifies the gtmTio1outn6 in PPU d, only THA6104 support */
     IOM_MONINPUT_GTMTIO1G0OUT7                        ,     /* Specifies the gtmTio1out7 in PPU e, only THA6104 support */
     IOM_MONINPUT_GTMTIO1G0OUTN7                       ,     /* Specifies the gtmTio1outn7 in PPU f, only THA6104 support */
#endif /* THA6_THA6104 */
#if defined(THA6_THA6412)
     IOM_MONINPUT_GTMTIO3PWM06                 = 0x200,     /* Specifies the gtmTio3pwm06 in PPU 0, only THA6412 support */
     IOM_MONINPUT_GTMTIO2PWM05                        ,     /* Specifies the gtmTio2pwm05 in PPU 1, only THA6412 support */
     IOM_MONINPUT_GTMTIO1PWM04                        ,     /* Specifies the gtmTio1pwm04 in PPU 2, only THA6412 support */
     IOM_MONINPUT_GTMTIO1PWM00                        ,     /* Specifies the gtmTio1pwm00 in PPU 3, only THA6412 support */
     IOM_MONINPUT_GTMTIO2PWM01                        ,     /* Specifies the gtmTio2pwm00 in PPU 4, only THA6412 support */
     IOM_MONINPUT_GTMTIO3PWM02                        ,     /* Specifies the gtmTio3pwm02 in PPU 5, only THA6412 support */
     IOM_MONINPUT_GTMTIO4PWM03                        ,     /* Specifies the gtmTio4pwm03 in PPU 6, only THA6412 support */
     IOM_MONINPUT_GTMTIO4PWM13                        ,     /* Specifies the gtmTio4pwm13 in PPU 7, only THA6412 support */
     IOM_MONINPUT_GTMTIO1PWM14                        ,     /* Specifies the gtmTio1pwm14 in PPU 8, only THA6412 support */
     IOM_MONINPUT_GTMTIO2PWM15                        ,     /* Specifies the gtmTio2pwm15 in PPU 9, only THA6412 support */
     IOM_MONINPUT_GTMTIO3PWM16                        ,     /* Specifies the gtmTio3pwm16 in PPU a, only THA6412 support */
     IOM_MONINPUT_GTMTIO1PWM10                        ,     /* Specifies the gtmTio1pwm10 in PPU b, only THA6412 support */
     IOM_MONINPUT_GTMTIO2PWM11                        ,     /* Specifies the gtmTio2pwm11 in PPU c, only THA6412 support */
     IOM_MONINPUT_GTMTIO3PWM12                        ,     /* Specifies the gtmTio3pwm12 in PPU d, only THA6412 support */
     IOM_MONINPUT_PSI5TX0                             ,     /* Specifies the Psi5Tx0 in PPU e, only THA6412 support */
     IOM_MONINPUT_PSI5TX1                             ,     /* Specifies the Psi5Tx1 in PPU f, only THA6412 support */
#endif /* THA6_THA6412 */
     IOM_MONINPUT_ESPI0MRST                    = 0x300,     /* Specifies the espi0Mrst  in PPU 0 */
     IOM_MONINPUT_ESPI1MRST                           ,     /* Specifies the espi1Mrst  in PPU 1 */
     IOM_MONINPUT_ESPI2MRST                           ,     /* Specifies the espi2Mrst  in PPU 2 */
     IOM_MONINPUT_ESPI3MRST                           ,     /* Specifies the espi3Mrst  in PPU 3 */
#if defined(THA6_THA6412)
     IOM_MONINPUT_ESPI4MRST                           ,     /* Specifies the espi4Mrst  in PPU 4, only THA6412 support */
#endif /* THA6_THA6412 */
     IOM_MONINPUT_CAN00TXD                     = 0x305,     /* Specifies the can00Txd   in PPU 5 */
     IOM_MONINPUT_CAN01TXD                            ,     /* Specifies the can01Txd   in PPU 6 */
     IOM_MONINPUT_CAN02TXD                            ,     /* Specifies the can02Txd   in PPU 7 */
#if defined(THA6_THA6412)
     IOM_MONINPUT_CAN30TXD                            ,     /* Specifies the can30Txd   in PPU 8, only THA6412 support */
#endif /* THA6_THA6412 */
     IOM_MONINPUT_GTMTOUT104                   = 0x309,     /* Specifies the gtmTout104 in PPU 9 */
     IOM_MONINPUT_GTMTOUT105                          ,     /* Specifies the gtmTout105 in PPU a */
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
     IOM_MONINPUT_GTMTOUT106                          ,     /* Specifies the gtmTout106 in PPU b, only THA6206 and THA6412 support */
#endif /* THA6_THA6206 || THA6_THA6206D || THA6_THA6412 */
     IOM_MONINPUT_ASCLIN0ATX                   = 0x30C,     /* Specifies the asclin0Atx in PPU c */
     IOM_MONINPUT_ASCLIN1ATX                          ,     /* Specifies the asclin1Atx in PPU d */
     IOM_MONINPUT_ASCLIN2ATX                          ,     /* Specifies the asclin2Atx in PPU e */
     IOM_MONINPUT_ASCLIN3ATX                                /* Specifies the asclin3Atx in PPU f */
 } Iom_MonInput;

 /* LPU reference inputs */
 typedef enum
 {
     IOM_REFINPUT_P33_0                          = 0x0,     /* Specifies the p33.0  in PPU 0  */
     IOM_REFINPUT_P33_1                               ,     /* Specifies the p33.1  in PPU 1  */
     IOM_REFINPUT_P33_2                               ,     /* Specifies the p33.2  in PPU 2  */
     IOM_REFINPUT_P33_3                               ,     /* Specifies the p33.3  in PPU 3  */
     IOM_REFINPUT_P33_4                               ,     /* Specifies the p33.4  in PPU 4  */
     IOM_REFINPUT_P33_5                               ,     /* Specifies the p33.5  in PPU 5  */
     IOM_REFINPUT_P33_6                               ,     /* Specifies the p33.6  in PPU 6  */
     IOM_REFINPUT_P33_7                               ,     /* Specifies the p33.7  in PPU 7  */
     IOM_REFINPUT_P33_8                               ,     /* Specifies the p33.8  in PPU 8  */
     IOM_REFINPUT_P33_9                               ,     /* Specifies the p33.9  in PPU 9  */
     IOM_REFINPUT_P33_10                              ,     /* Specifies the p33.10 in PPU a  */
     IOM_REFINPUT_P33_11                              ,     /* Specifies the p33.11 in PPU b  */
     IOM_REFINPUT_P33_12                              ,     /* Specifies the p33.12 in PPU c  */
     IOM_REFINPUT_P20_12                              ,     /* Specifies the p20.12 in PPU d  */
     IOM_REFINPUT_P20_13                              ,     /* Specifies the p20.13 in PPU e  */
     IOM_REFINPUT_P20_14                              ,     /* Specifies the p20.14 in PPU f  */
     IOM_REFINPUT_GTMTOUT0                     = 0x100,     /* Specifies the gtmTout0 in PPU 0  */
     IOM_REFINPUT_GTMTOUT1                            ,     /* Specifies the gtmTout1 in PPU 1  */
     IOM_REFINPUT_GTMTOUT2                            ,     /* Specifies the gtmTout2 in PPU 2  */
     IOM_REFINPUT_GTMTOUT3                            ,     /* Specifies the gtmTout3 in PPU 3  */
     IOM_REFINPUT_GTMTOUT4                            ,     /* Specifies the gtmTout4 in PPU 4  */
     IOM_REFINPUT_GTMTOUT5                            ,     /* Specifies the gtmTout5 in PPU 5  */
     IOM_REFINPUT_GTMTOUT6                            ,     /* Specifies the gtmTout6 in PPU 6  */
     IOM_REFINPUT_GTMTOUT7                            ,     /* Specifies the gtmTout7 in PPU 7  */
     IOM_REFINPUT_GTMTOUT8                            ,     /* Specifies the gtmTout8 in PPU 8  */
     IOM_REFINPUT_GTMTOUT9                            ,     /* Specifies the gtmTout9 in PPU 9  */
     IOM_REFINPUT_GTMTOUT10                           ,     /* Specifies the gtmTout10 in PPU a  */
     IOM_REFINPUT_GTMTOUT11                           ,     /* Specifies the gtmTout11 in PPU b  */
     IOM_REFINPUT_GTMTOUT12                           ,     /* Specifies the gtmTout12 in PPU c  */
     IOM_REFINPUT_GTMTOUT13                           ,     /* Specifies the gtmTout13 in PPU d  */
     IOM_REFINPUT_GTMTOUT14                           ,     /* Specifies the gtmTout14 in PPU e  */
     IOM_REFINPUT_GTMTOUT15                           ,     /* Specifies the gtmTout15 in PPU f  */
#if defined(THA6_THA6104)
     IOM_REFINPUT_GTMTIO1G0OUT0                 = 0x200,     /* Specifies the gtmTio1out0 in PPU 0, only THA6104 support */
     IOM_REFINPUT_GTMTIO1G0OUTN0                       ,     /* Specifies the gtmTio1outn0 in PPU 1, only THA6104 support */
     IOM_REFINPUT_GTMTIO1G0OUT1                        ,     /* Specifies the gtmTio1out1 in PPU 2, only THA6104 support */
     IOM_REFINPUT_GTMTIO1G0OUTN1                       ,     /* Specifies the gtmTio1outn1 in PPU 3, only THA6104 support */
     IOM_REFINPUT_GTMTIO1G0OUT2                        ,     /* Specifies the gtmTio1out2 in PPU 4, only THA6104 support */
     IOM_REFINPUT_GTMTIO1G0OUTN2                       ,     /* Specifies the gtmTio1outn2 in PPU 5, only THA6104 support */
     IOM_REFINPUT_GTMTIO1G0OUT3                        ,     /* Specifies the gtmTio1out3 in PPU 6, only THA6104 support */
     IOM_REFINPUT_GTMTIO1G0OUTN3                       ,     /* Specifies the gtmTio1outn3 in PPU 7, only THA6104 support */
     IOM_REFINPUT_GTMTIO1G0OUT4                        ,     /* Specifies the gtmTio1out4 in PPU 8, only THA6104 support */
     IOM_REFINPUT_GTMTIO1G0OUTN4                       ,     /* Specifies the gtmTio1outn4 in PPU 9, only THA6104 support */
     IOM_REFINPUT_GTMTIO1G0OUT5                        ,     /* Specifies the gtmTio1out5 in PPU a, only THA6104 support */
     IOM_REFINPUT_GTMTIO1G0OUTN5                       ,     /* Specifies the gtmTio1outn5 in PPU b, only THA6104 support */
     IOM_REFINPUT_GTMTIO1G0OUT6                        ,     /* Specifies the gtmTio1out6 in PPU c, only THA6104 support */
     IOM_REFINPUT_GTMTIO1G0OUTN6                       ,     /* Specifies the gtmTio1outn6 in PPU d, only THA6104 support */
     IOM_REFINPUT_GTMTIO1G0OUT7                        ,     /* Specifies the gtmTio1out7 in PPU e, only THA6104 support */
     IOM_REFINPUT_GTMTIO1G0OUTN7                       ,     /* Specifies the gtmTio1outn7 in PPU f, only THA6104 support */
#endif /* THA6_THA6104 */
#if defined(THA6_THA6412)
     IOM_REFINPUT_GTMTIO4PWM03                 = 0x200,     /* Specifies the gtmTio4Pwm03 in PPU 0, only THA6412 support */
     IOM_REFINPUT_GTMTIO3PWM02                        ,     /* Specifies the gtmTio3Pwm02 in PPU 1, only THA6412 support */
     IOM_REFINPUT_GTMTIO2PWM01                        ,     /* Specifies the gtmTio2Pwm01 in PPU 2, only THA6412 support */
     IOM_REFINPUT_GTMTIO1PWM00                        ,     /* Specifies the gtmTio1Pwm00 in PPU 3, only THA6412 support */
     IOM_REFINPUT_GTMTIO3PWM06                        ,     /* Specifies the gtmTio3Pwm06 in PPU 4, only THA6412 support */
     IOM_REFINPUT_GTMTIO2PWM05                        ,     /* Specifies the gtmTio2Pwm05 in PPU 5, only THA6412 support */
     IOM_REFINPUT_GTMTIO1PWM04                        ,     /* Specifies the gtmTio1Pwm04 in PPU 6, only THA6412 support */
     IOM_REFINPUT_GTMTIO4PWM13                        ,     /* Specifies the gtmTio4Pwm13 in PPU 7, only THA6412 support */
     IOM_REFINPUT_GTMTIO3PWM12                        ,     /* Specifies the gtmTio3Pwm12 in PPU 8, only THA6412 support */
     IOM_REFINPUT_GTMTIO2PWM11                        ,     /* Specifies the gtmTio2Pwm11 in PPU 9, only THA6412 support */
     IOM_REFINPUT_GTMTIO1PWM10                        ,     /* Specifies the gtmTio1Pwm10 in PPU a, only THA6412 support */
     IOM_REFINPUT_GTMTIO3PWM16                        ,     /* Specifies the gtmTio3Pwm16 in PPU b, only THA6412 support */
     IOM_REFINPUT_GTMTIO2PWM15                        ,     /* Specifies the gtmTio2Pwm15 in PPU c, only THA6412 support */
     IOM_REFINPUT_GTMTIO1PWM14                        ,     /* Specifies the gtmTio1Pwm14 in PPU d, only THA6412 support */
     IOM_REFINPUT_PSI5TX0                             ,     /* Specifies the Psi5Tx0 in PPU e, only THA6412 support */
     IOM_REFINPUT_PSI5TX2                             ,     /* Specifies the Psi5Tx2 in PPU f, only THA6412 support */
#endif /* THA6_THA6412 */
     IOM_REFINPUT_ESPI0MRST                    = 0x300,     /* Specifies the espi0Mrst  in PPU 0 */
     IOM_REFINPUT_ESPI1MRST                           ,     /* Specifies the espi1Mrst  in PPU 1 */
     IOM_REFINPUT_ESPI2MRST                           ,     /* Specifies the espi2Mrst  in PPU 2 */
     IOM_REFINPUT_ESPI3MRST                           ,     /* Specifies the espi3Mrst  in PPU 3 */
#if defined(THA6_THA6412)
     IOM_REFINPUT_ESPI4MRST                           ,     /* Specifies the espi4Mrst  in PPU 4, only THA6412 support */
#endif /* THA6_THA6412 */
     IOM_REFINPUT_CAN00TXD                     = 0x305,     /* Specifies the can00Txd   in PPU 5 */
     IOM_REFINPUT_CAN01TXD                            ,     /* Specifies the can01Txd   in PPU 6 */
     IOM_REFINPUT_CAN02TXD                            ,     /* Specifies the can02Txd   in PPU 7 */
#if defined(THA6_THA6412)
     IOM_REFINPUT_CAN30TXD                            ,     /* Specifies the can30Txd   in PPU 8, only THA6412 support */
#endif /* THA6_THA6412 */
     IOM_REFINPUT_GTMTOUT107                   = 0x309,     /* Specifies the gtmTout107 in PPU 9 */
     IOM_REFINPUT_GTMTOUT108                          ,     /* Specifies the gtmTout108 in PPU a */
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
     IOM_REFINPUT_GTMTOUT109                          ,     /* Specifies the gtmTout109 in PPU b, only THA6412 and THA6206 support */
#endif /* THA6_THA6206 || THA6_THA6206D || THA6_THA6412 */
     IOM_REFINPUT_ASCLIN0ATX                   = 0x30C,     /* Specifies the asclin0Atx in PPU c */
     IOM_REFINPUT_ASCLIN1ATX                          ,     /* Specifies the asclin1Atx in PPU d */
     IOM_REFINPUT_ASCLIN2ATX                          ,     /* Specifies the asclin2Atx in PPU e */
     IOM_REFINPUT_ASCLIN3ATX                          ,     /* Specifies the asclin3Atx in PPU f */
     IOM_REFINPUT_EXORCOMBINER0                = 0x400,     /* Specifies the EXOR signal in PPU 0 */
     IOM_REFINPUT_EXORCOMBINER1                       ,     /* Specifies the EXOR signal in PPU 1 */
     IOM_REFINPUT_EXORCOMBINER2                       ,     /* Specifies the EXOR signal in PPU 2 */
     IOM_REFINPUT_EXORCOMBINER3                       ,     /* Specifies the EXOR signal in PPU 3 */
     IOM_REFINPUT_EXORCOMBINER4                       ,     /* Specifies the EXOR signal in PPU 4 */
     IOM_REFINPUT_EXORCOMBINER5                       ,     /* Specifies the EXOR signal in PPU 5 */
     IOM_REFINPUT_EXORCOMBINER6                       ,     /* Specifies the EXOR signal in PPU 6 */
     IOM_REFINPUT_EXORCOMBINER7                       ,     /* Specifies the EXOR signal in PPU 7 */
     IOM_REFINPUT_EXORCOMBINER8                       ,     /* Specifies the EXOR signal in PPU 8 */
     IOM_REFINPUT_EXORCOMBINER9                       ,     /* Specifies the EXOR signal in PPU 9 */
     IOM_REFINPUT_EXORCOMBINER10                      ,     /* Specifies the EXOR signal in PPU a */
     IOM_REFINPUT_EXORCOMBINER11                      ,     /* Specifies the EXOR signal in PPU b */
     IOM_REFINPUT_EXORCOMBINER12                      ,     /* Specifies the EXOR signal in PPU c */
     IOM_REFINPUT_EXORCOMBINER13                      ,     /* Specifies the EXOR signal in PPU d */
     IOM_REFINPUT_EXORCOMBINER14                      ,     /* Specifies the EXOR signal in PPU e */
     IOM_REFINPUT_EXORCOMBINER15                            /* Specifies the EXOR signal in PPU f */
 } Iom_RefInput;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* IOM PPU filter configuration */
typedef struct 
{
    uint32                              prescalerFactor;                /* Prescaler factor, must be > 0, only valid for prescaler mode */
    Iom_PpuFilterMode                   mode;                           /* Filter mode */
    uint32                              filterTime;                     /* Filter time for filter mode. In THA6206 and THA6206D, must be > 0 */
    boolean                             clearTimerOnGlitch;             /* If set, the timer is cleared on glitch, else it is decremented, only valid for delayDebounce mode*/
} Iom_PpuFilterConfig;

/* IOM LPU event window configuration */
typedef struct 
{
    Iom_LpuEventWindowControlSource     controlSource;                  /* Timer control source */
    Iom_LpuEventWindowClearEvent        clearEvent;                     /* Timer clear event */
    Iom_LpuEventWindowRunControl        run;                            /* Timer run control */
    boolean                             inverted;                       /* If TRUE, the event window is inverted */
    uint32                              threshold;                      /* Event window threshold in second. If 0, no event are generated */
} Iom_LpuEventWindowConfig;

/* IOM LPU event configuration */
typedef struct 
{
    Iom_LpuEventSource                      source;                         /* Event source */
    Iom_LpuEventTrigger                     trigger;                        /* Event trigger */
} Iom_LpuEventConfig;

/* IOM LPU monitor input configuration */
typedef struct 
{
    Iom_PpuFilterConfig                 filter;                         /* Filter configuration */
    Iom_MonInput                        input;                          /* Monitor input */
    boolean                             inverted;                       /* If TRUE, the signal is inverted */
} Iom_LpuMonConfig;

/* IOM LPU reference input configuration */
typedef struct 
{
    Iom_PpuFilterConfig                 filter;                         /* Filter configuration */
    Iom_RefInput                        input;                          /* Reference input */
    uint8                               exor;                           /* EXOR selection , only valid when choose Iom_RefInput_exorCombiner */
    boolean                             inverted;                       /* If TRUE, the signal is inverted */
} Iom_LpuRefConfig;

/* IOM channel event counter configuration */
typedef struct
{
    Iom_EventCounterChannel   input;           /* Specifies which event channel to be routed to the Counter */
    Iom_EventCounterThreshold threshold;       /* Specifies the Counter threshold value */
} Iom_EmuConfigCounter;

/* IOM LPU configuration */
/* #Violation: iom_hal_h_REF_3*/
typedef struct
{
    Iom_LpuId                       channel;                        /* LPU channel to be used */
    Iom_LpuEventConfig              event;                          /* LPU event configuration */
    Iom_LpuEventWindowConfig        eventWindow;                    /* LPU eventWindow configuration */
    Iom_LpuMonConfig                monitor;                        /* LPU Monitor input configuration */
    Iom_LpuRefConfig                reference;                      /* LPU reference input configuration */
    Iom_EmuConfigCounter            counter;                        /* ECM counter configuration,max 4 counters exists for the IOM */
} Iom_LpuConfig;

/* IOM LPU object */
/* #Violation: iom_hal_h_REF_3*/
typedef struct
{
    Iom_LpuId                       channel;                        /* LPU Channel */
    uint8                           monIndex;                       /* Monitor input index */
    uint8                           refIndex;                       /* Reference input index */
    Iom_ReferenceSignal             refInput;                       /* Reference input */
    Iom_MonitorSignal               monInput;                       /* Monitor input */
    Iom_EmuConfigCounter            counter;                        /* ECM counter configuration,max 4 counters exists for the IOM */
} Iom_Lpu;

#define IOM_START_SEC_CODE_ASIL_D_GLOBAL
#include "Iom_MemMap.h"
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:    Iom_Register_ReadBack_Check
 * Description: Checks whether the register value written is equal to the value read back 
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:       expect: Read back the value of the register
 *              value: value written to register
 *              state: Wrong initial state
 * Inout:       None
 * Output:      None
 * Return:      boolean: Flag indicating whether the value written to register is the same as the value read back
 * Others:      None
 * History:
 * Date         Author    Modified
 * 2025/03/10   01744     create
 *********************************************************************************************************************/ 
LOCAL_FORCEINLINE boolean Iom_Register_ReadBack_Check(boolean state, uint32 value, uint32 expect);

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
#if defined(IOM_REG_CHECK)
LOCAL_FORCEINLINE boolean Iom_Register_ReadBack_Check(boolean state, uint32 value, uint32 expect)
{
    boolean ret;

    ret = state;
    if (expect != value)
    {
        ret &= FALSE;
    }

    return ret;
}
#else
LOCAL_FORCEINLINE boolean Iom_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    (void)state;
    (void)expect;
    (void)value;

    return state;
}
#endif

/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:     Iom_Hal_SetClock
 * Description:  Set the clock divider of the IOM module.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        clockDivider: IOM clock divider. Set to 1 for max clock. clockDivider ranging from 0 to 255.
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/07    00393     Create
 *********************************************************************************************************************/
extern boolean Iom_Hal_SetClock(uint8 clockDivider);

/**********************************************************************************************************************
 * Function:     Iom_Hal_InitLpu
 * Description:  Initialize monitor, reference and LPU channels, configure the EMU.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pLPU: Pointer to the LPU object
 *               pConfig: LPU configuration. Will be initialized by the function
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/07    00393     Create
 *********************************************************************************************************************/
extern boolean Iom_Hal_InitLpu(Iom_Lpu *const pLPU, const Iom_LpuConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Iom_Hal_GetGlitch
 * Description:  Get glitch signal flag bits.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        index: Get the channel number for glitch, index ranging from 0 to 15.
 * Inout:        None
 * Output:       None
 * Return:       Iom_PpuGlitchFlag: The channel glitch flag
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/07    00393     Create
 *********************************************************************************************************************/
extern Iom_PpuGlitchFlag Iom_Hal_GetGlitch(Iom_PpuId index);

/**********************************************************************************************************************
 * Function:     Iom_Hal_ClearGlitch
 * Description:  Clear glitch signal flag bits.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        index: Clear the channel number for glitch, index ranging from 0 to 15.
 *               edge: edge glitch flag.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/07    00393     Create
 *********************************************************************************************************************/
extern void Iom_Hal_ClearGlitch(Iom_PpuId index, Iom_PpuGlitchFlag edge);

/**********************************************************************************************************************
 * Function:     Iom_Hal_SetPpuThreshold
 * Description:  Set the threshold value for PPU channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different PPU channels, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        index: Specifies the PPU channel , index ranging from 0 to 15.
 *               threshold: the threshold value that is compared witch the timer. In THA6206 and THA6206D, the threshold is not allowed to be set to 0. 
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/07    00393     Create
 *********************************************************************************************************************/
extern boolean Iom_Hal_SetPpuThreshold(Iom_PpuId index, uint16 threshold);

/**********************************************************************************************************************
 * Function:     Iom_Hal_GetPpuThreshold
 * Description:  Get the threshold value for PPU channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        index: Specifies the PPU channel, index ranging from 0 to 15.
 * Inout:        None
 * Output:       None
 * Return:       uint16: the threshold value that is compared witch the timer
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/07    00393     Create
 *********************************************************************************************************************/
extern uint16 Iom_Hal_GetPpuThreshold(Iom_PpuId index);

/**********************************************************************************************************************
 * Function:     Iom_Hal_SetEventWindowThreshold
 * Description:  Set the threshold value for event window of LPU channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different LPU channels, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        index: Specifies the LPU channel , index ranging from 0 to 15.
 *               threshold: the threshold value for the event windows activation 
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/07    00393     Create
 *********************************************************************************************************************/
extern boolean Iom_Hal_SetEventWindowThreshold(Iom_LpuId index, uint32 threshold);

/**********************************************************************************************************************
 * Function:     Iom_Hal_GetEventWindowThreshold
 * Description:  Get the threshold value for LPU channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        index: Specifies the LPU channel, index ranging from 0 to 15.
 * Inout:        None
 * Output:       None
 * Return:       uint32: the threshold value for LPU channel
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/07    00393     Create
 *********************************************************************************************************************/
extern uint32 Iom_Hal_GetEventWindowThreshold(Iom_LpuId index);

/**********************************************************************************************************************
 * Function:     Iom_Hal_SetCombiner
 * Description:  Event Counter configuration for LPU channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        index: Specifies the combiner module , index ranging from 0 to 3.
 *               channel: Specifies the lpu channel
 *               threshold: Specifies threshold of the lpu channel
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/07    00393     Create
 *********************************************************************************************************************/
extern boolean Iom_Hal_SetCombiner(Iom_EventCounterChannel index, Iom_LpuId channel, Iom_EventCounterThreshold threshold);

/**********************************************************************************************************************
 * Function:     Iom_Hal_GetCombiner
 * Description:  Get the threshold value for LPU channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        index: Specifies the LPU channel, index ranging from 0 to 15.
 * Inout:        None
 * Output:       pChannel: The lpu channel.
 *               pThreshold: Threshold of the lpu channel.
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/07    00393     Create
 *********************************************************************************************************************/
extern void Iom_Hal_GetCombiner(Iom_EventCounterChannel index, Iom_LpuId *const pChannel, Iom_EventCounterThreshold *const pThreshold);

/**********************************************************************************************************************
 * Function:     Iom_Hal_GetAllHistory
 * Description:  Get event trigger history.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       pEh0: Alarm triggered event history 0
 *               pEh1: Alarm triggered event history 1
 *               pEh2: Alarm triggered event history 2
 *               pEh3: Alarm triggered event history 3
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/07    00393     Create
 *********************************************************************************************************************/
extern void Iom_Hal_GetAllHistory(uint16 *const pEh0, uint16 *const pEh1, uint16 *const pEh2, uint16 *const pEh3);

/**********************************************************************************************************************
 * Function:     Iom_Hal_ClearAllHistory
 * Description:  Clear event trigger history.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/07    00393     Create
 *********************************************************************************************************************/
extern void Iom_Hal_ClearAllHistory(void);

/**********************************************************************************************************************
 * Function:     Iom_Hal_GetSafetyStatus
 * Description:  Get safety status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       uint8: The status of the safety module
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/07    00393     Create
 *********************************************************************************************************************/
extern uint8 Iom_Hal_GetSafetyStatus(void);

/**********************************************************************************************************************
 * Function:     Iom_Hal_ClearSafetyStatus
 * Description:  Clear safety status
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        flag: Specifies the flag to clear
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/07    00393     Create
 *********************************************************************************************************************/
extern boolean Iom_Hal_ClearSafetyStatus(uint8 flag);

/**********************************************************************************************************************
 * Function:     Iom_Hal_GetEmuGlobalEventSel
 * Description:  Get the event trigger source
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       uint32: The event trigger source
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/07    00393     Create
 *********************************************************************************************************************/
extern uint32 Iom_Hal_GetEmuGlobalEventSel(void);

/**********************************************************************************************************************
 * Function:     Iom_Hal_SetEmuGlobalEventSel
 * Description:  Set Event Trigger Source
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        EventSel: Specifies which channel or counter trigger the event
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/07    00393     Create
 *********************************************************************************************************************/
extern boolean Iom_Hal_SetEmuGlobalEventSel(uint32 EventSel);

#define IOM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Iom_MemMap.h"

#endif /* IOM_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
