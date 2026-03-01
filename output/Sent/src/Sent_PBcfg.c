/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Sent_PBCfg.c
*
*   Platform             : AUTOSAR
*
*   Peripheral           : SENT
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*
*   Build Version        : Cortex-R52+/THA6xxx
*
*   Copyright /(c) 2021,Beijing Tongxin Microelectroics co.Ltd
*
****************************************************************************************************/
/*
*#Violation Summary
*#Sent_PBCfg_c_REF_1:CertC-DCL06-C;
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*
*#Sent_PBCfg_c_REF_2:CWE-547;
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*
*#Sent_PBCfg_c_REF_3:MISRAC2012-Rule-20.1;
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*/
/****************************************************************************************************
 
****************************************************************************************************/
/*
  
 *
 ****************************************************************************************************/
/***************************************************************************************************
 *                               Include
 ***************************************************************************************************/

 #include "Sent.h"

/****************************************************************************************************
 **                          Global Function Declarations                                           *
 ***************************************************************************************************/
/* Application Callback function for SENT Channel0 */
extern void Sent_CalloutChan0 (Sent_ChannelIdxType ChannelId, Sent_NotifType *StatPtr);
/* Application Callback function for SENT Channel error0 */
extern void Sent_ErrCalloutChan0 (Sent_ChannelIdxType ChannelId, Sent_NotifType *StatPtr);
/* Application Callback function for SENT Channel1 */
extern void Sent_CalloutChan1 (Sent_ChannelIdxType ChannelId, Sent_NotifType *StatPtr);
/* Application Callback function for SENT Channel error1 */
extern void Sent_ErrCalloutChan1 (Sent_ChannelIdxType ChannelId, Sent_NotifType *StatPtr);
/* Application Callback function for SENT Channel2 */
extern void Sent_CalloutChan2 (Sent_ChannelIdxType ChannelId, Sent_NotifType *StatPtr);
/* Application Callback function for SENT Channel error2 */
extern void Sent_ErrCalloutChan2 (Sent_ChannelIdxType ChannelId, Sent_NotifType *StatPtr);

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

#define SENT_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Sent_PBcfg_c_REF_3 */
#include "Sent_MemMap.h"
/* Sent_Spc_Config for SentChannelConfigSet_1 */
static const Sent_Spc_Config SpcConfig2 =
{
    SENT_TRIGGER_MODE_SPC, /* The trigger mode (SPC or GTM)  */
    300, /* per tick time in clock of SPC  */
    SENT_GTM_CHANNEL_0, /* Gtm channel for triggering SPC */
    0x02FAF07FUL /* Time out time for Gtm trigger */
};

/* Sent_Spc_Config for SentChannelConfigSet_2 */
static const Sent_Spc_Config SpcConfig3 =
{
    SENT_TRIGGER_MODE_GTM, /* The trigger mode (SPC or GTM)  */
    300, /* per tick time in clock of SPC  */
    SENT_GTM_CHANNEL_3, /* Gtm channel for triggering SPC */
    0x02FAF07FUL /* Time out time for Gtm trigger */
};

/*Channel Structure for selected Core*/
static const Sent_ChannelCfgType Sent_ChanConfig_Core0[SENT_CHANNEL_COUNT_CORE0] =
{
/* Channel: */
    {
        {
            {, SENT_CRC_WITH_OUT_STATUS, SENT_CRC_ENABLE_ON}, /* CRC configuration */
            SENT_NIBBLES_NUM_, /* SentChanFrameDataLen */
            SENT_PAUSE_ENABLE,
            , /* polarity */            
            0, /* Maximum number of clocks in a tick as resulting from the sync pulse */            
            0,  /* Minimum number of clocks in a tick as resulting from the sync pulse */
            SENT_VALIDINT_DISMASK, /* Valid interrupt mask configuration, THA6104 is supported,but THA6206 and THA6412 are not supported */
            SENT_ERRORINT_DISMASK  /* Error interrupt mask configuration, THA6104 is supported,but THA6206 and THA6412 are not supported */
        },
#if (SENT_SPC_USED == STD_ON)
        NULL_PTR, 
        0,
        0x0U, /* Enable SPC. */
#endif
        /* SENT Physical Channel Id arranged corewise */
        (U),
        /*Callback function ptr */
        ,
                
                                    
    },
                                    /* Channel:SentChannelConfigSet_0 */
    {
        {
            {SENT_CRC_TYPE_2010, SENT_CRC_WITH_OUT_STATUS, SENT_CRC_ENABLE_ON}, /* CRC configuration */
            SENT_NIBBLES_NUM_6, /* SentChanFrameDataLen */
            SENT_PAUSE_ENABLE,
            SENT_POLARITY_FALLING, /* polarity */            
            360, /* Maximum number of clocks in a tick as resulting from the sync pulse */            
            240,  /* Minimum number of clocks in a tick as resulting from the sync pulse */
            SENT_VALIDINT_DISMASK, /* Valid interrupt mask configuration, THA6104 is supported,but THA6206 and THA6412 are not supported */
            SENT_ERRORINT_DISMASK  /* Error interrupt mask configuration, THA6104 is supported,but THA6206 and THA6412 are not supported */
        },
#if (SENT_SPC_USED == STD_ON)
        NULL_PTR, 
        0,
        0x0U, /* Enable SPC. */
#endif
        /* SENT Physical Channel Id arranged corewise */
        (2U),
        /*Callback function ptr */
        Sent_CalloutChan0,
        Sent_ErrCalloutChan0        
                                    
    },
                                    /* Channel:SentChannelConfigSet_1 */
    {
        {
            {SENT_CRC_TYPE_2010, SENT_CRC_WITH_STATUS, SENT_CRC_ENABLE_ON}, /* CRC configuration */
            SENT_NIBBLES_NUM_6, /* SentChanFrameDataLen */
            SENT_PAUSE_DISABLE,
            SENT_POLARITY_FALLING, /* polarity */            
            360, /* Maximum number of clocks in a tick as resulting from the sync pulse */            
            240,  /* Minimum number of clocks in a tick as resulting from the sync pulse */
            SENT_VALIDINT_DISMASK, /* Valid interrupt mask configuration, THA6104 is supported,but THA6206 and THA6412 are not supported */
            SENT_ERRORINT_DISMASK  /* Error interrupt mask configuration, THA6104 is supported,but THA6206 and THA6412 are not supported */
        },
#if (SENT_SPC_USED == STD_ON)
        &SpcConfig2, 
        3,
        0x1U, /* Enable SPC. */
#endif
        /* SENT Physical Channel Id arranged corewise */
        (3U),
        /*Callback function ptr */
        Sent_CalloutChan1,
        Sent_ErrCalloutChan1        
                                    
    },
                                    /* Channel:SentChannelConfigSet_2 */
    {
        {
            {SENT_CRC_TYPE_2010, SENT_CRC_WITH_STATUS, SENT_CRC_ENABLE_ON}, /* CRC configuration */
            SENT_NIBBLES_NUM_6, /* SentChanFrameDataLen */
            SENT_PAUSE_DISABLE,
            SENT_POLARITY_FALLING, /* polarity */            
            360, /* Maximum number of clocks in a tick as resulting from the sync pulse */            
            240,  /* Minimum number of clocks in a tick as resulting from the sync pulse */
            SENT_VALIDINT_DISMASK, /* Valid interrupt mask configuration, THA6104 is supported,but THA6206 and THA6412 are not supported */
            SENT_ERRORINT_DISMASK  /* Error interrupt mask configuration, THA6104 is supported,but THA6206 and THA6412 are not supported */
        },
#if (SENT_SPC_USED == STD_ON)
        &SpcConfig3, 
        3,
        0x1U, /* Enable SPC. */
#endif
        /* SENT Physical Channel Id arranged corewise */
        (6U),
        /*Callback function ptr */
        Sent_CalloutChan2,
        Sent_ErrCalloutChan2        
                                    
    }
                                    };

#define SENT_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Sent_PBcfg_c_REF_3 */
#include "Sent_MemMap.h"

                        
#define SENT_START_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Sent_PBcfg_c_REF_3 */
#include "Sent_MemMap.h"
/*Channel Structure for selected Core*/
static const Sent_ChannelCfgType Sent_ChanConfig_Core1[SENT_CHANNEL_COUNT_CORE1] =
{
/* Channel:SentChannelConfigSet_3 */
    {
        {
            {SENT_CRC_TYPE_2010, SENT_CRC_WITH_OUT_STATUS, SENT_CRC_ENABLE_ON}, /* CRC configuration */
            SENT_NIBBLES_NUM_6, /* SentChanFrameDataLen */
            SENT_PAUSE_ENABLE,
            SENT_POLARITY_RISING, /* polarity */            
            360, /* Maximum number of clocks in a tick as resulting from the sync pulse */            
            240,  /* Minimum number of clocks in a tick as resulting from the sync pulse */
            SENT_VALIDINT_DISMASK, /* Valid interrupt mask configuration, THA6104 is supported,but THA6206 and THA6412 are not supported */
            SENT_ERRORINT_DISMASK  /* Error interrupt mask configuration, THA6104 is supported,but THA6206 and THA6412 are not supported */
        },
#if (SENT_SPC_USED == STD_ON)
        NULL_PTR, 
        0,
        0x0U, /* Enable SPC. */
#endif
        /* SENT Physical Channel Id arranged corewise */
        (7U),
        /*Callback function ptr */
        NULL_PTR,
        NULL_PTR        
                                    
    },
                                    /* Channel:SentChannelConfigSet_4 */
    {
        {
            {SENT_CRC_TYPE_2010, SENT_CRC_WITH_OUT_STATUS, SENT_CRC_ENABLE_ON}, /* CRC configuration */
            SENT_NIBBLES_NUM_6, /* SentChanFrameDataLen */
            SENT_PAUSE_ENABLE,
            SENT_POLARITY_RISING, /* polarity */            
            360, /* Maximum number of clocks in a tick as resulting from the sync pulse */            
            240,  /* Minimum number of clocks in a tick as resulting from the sync pulse */
            SENT_VALIDINT_DISMASK, /* Valid interrupt mask configuration, THA6104 is supported,but THA6206 and THA6412 are not supported */
            SENT_ERRORINT_DISMASK  /* Error interrupt mask configuration, THA6104 is supported,but THA6206 and THA6412 are not supported */
        },
#if (SENT_SPC_USED == STD_ON)
        NULL_PTR, 
        0,
        0x0U, /* Enable SPC. */
#endif
        /* SENT Physical Channel Id arranged corewise */
        (9U),
        /*Callback function ptr */
        NULL_PTR,
        NULL_PTR        
                                    
    },
                                    /* Channel:SentChannelConfigSet_5 */
    {
        {
            {SENT_CRC_TYPE_2010, SENT_CRC_WITH_OUT_STATUS, SENT_CRC_ENABLE_ON}, /* CRC configuration */
            SENT_NIBBLES_NUM_6, /* SentChanFrameDataLen */
            SENT_PAUSE_ENABLE,
            SENT_POLARITY_RISING, /* polarity */            
            360, /* Maximum number of clocks in a tick as resulting from the sync pulse */            
            240,  /* Minimum number of clocks in a tick as resulting from the sync pulse */
            SENT_VALIDINT_DISMASK, /* Valid interrupt mask configuration, THA6104 is supported,but THA6206 and THA6412 are not supported */
            SENT_ERRORINT_DISMASK  /* Error interrupt mask configuration, THA6104 is supported,but THA6206 and THA6412 are not supported */
        },
#if (SENT_SPC_USED == STD_ON)
        NULL_PTR, 
        0,
        0x0U, /* Enable SPC. */
#endif
        /* SENT Physical Channel Id arranged corewise */
        (5U),
        /*Callback function ptr */
        NULL_PTR,
        NULL_PTR        
                                    
    }
                                    };

#define SENT_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Sent_PBcfg_c_REF_3 */
#include "Sent_MemMap.h"

                        
#define SENT_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Sent_PBcfg_c_REF_3 */
#include "Sent_MemMap.h"
static const Sent_CoreConfigType Sent_CoreConfigCore0 =
{
    (Sent_ChannelIdxType)4U,
                        Sent_ChanConfig_Core0
                        };

#define SENT_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Sent_PBcfg_c_REF_3 */
#include "Sent_MemMap.h"

                    
#define SENT_START_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Sent_PBcfg_c_REF_3 */
#include "Sent_MemMap.h"
static const Sent_CoreConfigType Sent_CoreConfigCore1 =
{
    (Sent_ChannelIdxType)3U,
                        Sent_ChanConfig_Core1
                        };

#define SENT_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Sent_PBcfg_c_REF_3 */
#include "Sent_MemMap.h"

                    

#define SENT_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Sent_PBcfg_c_REF_3 */
#include "Sent_MemMap.h"
/* Data structure to hold core channel index map */
/* Allocation of the channels to different cores */

static const Sent_ChannelMapType Sent_ChannelLookUp[6] =      
{
        
    /*CoreID, ChannelIndex*/           
        {MULTICOREID_CPU0,0x0U},
                            {MULTICOREID_CPU0,0x1U},
                            {MULTICOREID_CPU0,0x2U},
                            {MULTICOREID_CPU1,0x0U},
                            {MULTICOREID_CPU1,0x1U},
                            {MULTICOREID_CPU1,0x2U}
};

/* Physical to Logical channel mapping */
/* physical channel id is the index value of Sent_ChannelId and corresponding
   logical channel id in the channel configuration is stored */
static const Sent_ChannelIdxType Sent_LogicalChannelId[SENT_HW_MAX_CHANNELS] =
{
    0xFFU,
            0xFFU,
            0U
            ,
            1U
            ,
            0xFFU,
            5U
            ,
            2U
            ,
            3U
            ,
            0xFFU,
            4U
            
};

/* Logical to physical channel mapping */
/* Logical id is the index value hardware channel id and
   physical id is the mapping to the configured channel in sequence */
static const Sent_ChannelIdxType Sent_PhyChannelId[SENT_MAX_CHANNELS_CONFIGURED] =
{
2U,
    3U,
    6U,
    7U,
    9U,
    5U
};

/* SENT Module Configuration */
const Sent_ConfigType Sent_ConfigSet =

{
{
                &Sent_CoreConfigCore0,
        &Sent_CoreConfigCore1

},
    /* SENT channels configured */
    (6U),
    /* Channel Id to the core sequence mapping */
    Sent_ChannelLookUp,
    /* Physical to Logical Id mapping */
    Sent_LogicalChannelId,
    /* Logical to Physical ID mapping */
    Sent_PhyChannelId
};

#define SENT_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Sent_PBcfg_c_REF_3 */
#include "Sent_MemMap.h"

/****************************************************************************************************
 **                          End of File                                                            *
 ***************************************************************************************************/
