/****************************************************************************************************
*   FileName              : Eth_Cfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Ethernet
*
*   brief                 : This file contains all configuration declarations of Ethernet Driver
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
*#Eth_Cfg_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers
*
*/
#ifndef ETH_CFG_H 
#define ETH_CFG_H 
[!NOCODE!][!//
[!INCLUDE "Eth_Cfg_Common.m"!][!//
[!ENDNOCODE!][!//
[!INDENT "0"!][!//
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

[!AUTOSPACING!]
#define ETH_CFG_VENDOR_ID                    ([!"num:i(CommonPublishedInformation/VendorId)"!]U)
#define ETH_CFG_MODULE_ID                    ([!"num:i(CommonPublishedInformation/ModuleId)"!]U)

/* Autosar specification version */
#define ETH_CFG_AR_RELEASE_MAJOR_VERSION     ([!"num:i(CommonPublishedInformation/ArReleaseMajorVersion)"!]U)
#define ETH_CFG_AR_RELEASE_MINOR_VERSION     ([!"num:i(CommonPublishedInformation/ArReleaseMinorVersion)"!]U)
#define ETH_CFG_AR_RELEASE_REVISION_VERSION  ([!"num:i(CommonPublishedInformation/ArReleaseRevisionVersion)"!]U)

/* Vendor specific implementation version information */
#define ETH_CFG_SW_MAJOR_VERSION             ([!"num:i(CommonPublishedInformation/SwMajorVersion)"!]U)
#define ETH_CFG_SW_MINOR_VERSION             ([!"num:i(CommonPublishedInformation/SwMinorVersion)"!]U)
/* #Violation: Eth_Cfg_h_REF_1*/
#define ETH_CFG_SW_PATCH_VERSION             ([!"num:i(CommonPublishedInformation/SwPatchVersion)"!]U)

/* Container : EthGeneralConfiguration */
#define ETH_DEV_ERROR_DETECT                 ([!//
    [!IF "EthGeneral/EthDevErrorDetect = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
#define ETH_VERSION_INFO_API                 ([!//
    [!IF "EthGeneral/EthVersionInfoApi = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
#define ETH_GET_DROP_COUNT_API               ([!//
    [!IF "EthGeneral/EthGetDropCountApi = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
#define ETH_GET_ETHER_STATS_API              ([!//
    [!IF "EthGeneral/EthGetEtherStatsApi = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
#define ETH_GLOBAL_TIME_SUPPORT_API          ([!//
    [!IF "EthGeneral/EthGlobalTimeSupport = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
#define ETH_GETTXSTATS_API        ([!//
    [!IF "EthGeneral/EthGetTxStatsApi = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
#define ETH_GETTXERRCNTRVAL_API        ([!//
    [!IF "EthGeneral/EthGetTxErrorCounterValuesApi = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )

/*
  Configuration: ETH_SWT_MANAGEMENT_SUPPORT
- if STD_ON, Ethernet switch management support is enabled
- if STD_OFF, Ethernet switch management support is disabled
*/
[!VAR "SwtMgmtSupport"= "num:i(0)"!][!//
[!IF "not(node:exists(as:modconf('EthSwt')[1]))"!][!//
  #define ETH_SWT_MANAGEMENT_SUPPORT        (STD_OFF)
[!ELSE!][!//
  [!SELECT "as:modconf('EthSwt')[1]"!][!//
    [!IF "EthSwtGeneral/EthSwtManagementSupportApi = 'true'"!][!//
      #define ETH_SWT_MANAGEMENT_SUPPORT        (STD_ON)
      [!VAR "SwtMgmtSupport"= "num:i(1)"!][!//
    [!ELSE!][!//
      #define ETH_SWT_MANAGEMENT_SUPPORT        (STD_OFF)
    [!ENDIF!][!//
  [!ENDSELECT!][!//
[!ENDIF!][!//

[!VAR "MaxControllers"= "ecu:get('Eth.MaxControllers')"!][!//

[!VAR "TxBuffer"= "num:i(0)"!][!//
[!VAR "RxBuffer"= "num:i(0)"!][!//
[!SELECT "EthConfigSet"!][!//
  [!FOR "ControllerId" = "num:i(0)" TO "num:i($MaxControllers) - num:i(1)"!][!//
    [!IF "node:exists(./EthCtrlConfig/*[num:i($ControllerId)+num:i(1)])"!][!//
      [!SELECT "EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]"!][!//
        [!NOCODE!][!//
          /* Rx buffer memory is allocated as 16 byte aligned for optimal performance.
              Total Rx memory allocated = Size of one buffer (16 byte aligned) * Number of buffers */
          [!FOR "IngressFifo" = "num:i(0)" TO "num:i(3)"!][!//
            [!IF "node:exists(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]) = 'true'"!][!//
              [!VAR "EthCtrlConfigIngressFifoBufLenByteValue" = "EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoBufLenByte"!][!//
              [!VAR "EthCtrlConfigIngressFifoBufTotalValue" = "EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoBufTotal"!][!//
              [!VAR "RxBufQuotient" = "num:i($EthCtrlConfigIngressFifoBufLenByteValue) div 16"!][!//
              [!IF "num:i($EthCtrlConfigIngressFifoBufLenByteValue) mod 16 != 0"!][!//
                [!VAR "EthCtrlConfigIngressFifoBufLenByteValue" = "(num:i($RxBufQuotient) + 1) * 16"!][!//
              [!ENDIF!]!][!//
              [!VAR "RxBuffer" = "(string(num:i($EthCtrlConfigIngressFifoBufLenByteValue) * num:i($EthCtrlConfigIngressFifoBufTotalValue)))"!][!//
              [!VAR "IngressFifoIdx" = "EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoIdx"!][!//
              [!CODE!]
                /* Rx buffer count and size for controller[!"./EthCtrlIdx"!] FIFO Index[!"num:i($IngressFifoIdx)"!] */
                #define ETH_FIFO[!"num:i($IngressFifoIdx)"!]_CTRL[!"./EthCtrlIdx"!]_RXBUF_COUNT      ([!"num:i($EthCtrlConfigIngressFifoBufTotalValue)"!]U)
                #define ETH_FIFO[!"num:i($IngressFifoIdx)"!]_CTRL[!"./EthCtrlIdx"!]_RXBUF_SIZE       ([!"string($RxBuffer)"!]U)
                /* #Violation: Eth_Cfg_h_REF_1*/
                #define ETH_FIFO[!"num:i($IngressFifoIdx)"!]_CTRL[!"./EthCtrlIdx"!]_RXBUF_PER_SIZE   ([!"num:i($EthCtrlConfigIngressFifoBufLenByteValue)"!]U)
              [!ENDCODE!][!CR!]
            [!ELSE!][!//
              [!CODE!]
                /* Rx buffer count and size for controller[!"./EthCtrlIdx"!] FIFO Index[!"num:i($IngressFifo)"!] */
                #define ETH_FIFO[!"num:i($IngressFifo)"!]_CTRL[!"./EthCtrlIdx"!]_RXBUF_COUNT      (0U)
                #define ETH_FIFO[!"num:i($IngressFifo)"!]_CTRL[!"./EthCtrlIdx"!]_RXBUF_SIZE       (0U)
                /* #Violation: Eth_Cfg_h_REF_1*/
                #define ETH_FIFO[!"num:i($IngressFifo)"!]_CTRL[!"./EthCtrlIdx"!]_RXBUF_PER_SIZE   (0U)
              [!ENDCODE!][!CR!]
            [!ENDIF!][!//
          [!ENDFOR!][!//
          [!CODE!][!//
          /* Number of Receive FIFOs configured */
          #define ETH_CTRL[!"./EthCtrlIdx"!]_RXFIFO_CFGD       ([!"num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*))"!]U)
          #define ETH_CTRL[!"./EthCtrlIdx"!]_RXSCHEDULED_CFGD       ([!"num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*))"!]U)
          [!ENDCODE!][!CR!]
          /* If switch management support is enabled */
          [!IF "$SwtMgmtSupport = num:i(1)"!][!//
            [!IF "num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*)) > num:i(1)"!][!//
              [!ERROR!][!//
                When switch management support functionality is enabled, only one ingress FIFO is supported. Configure only one ingress FIFO for controller [!"./EthCtrlIdx"!]
              [!ENDERROR!][!//
            [!ENDIF!]!][!//
          [!ENDIF!]!][!//          
          /* Tx buffer memory is allocated as 16 byte aligned for optimal performance.
            Total Tx memory allocated = Size of one 16 byte aligned buffer * Number of Buffers. */
          [!FOR "EgressFifo" = "num:i(0)" TO "num:i(3)"!][!//
            [!IF "node:exists(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[EthCtrlConfigEgressFifoIdx = ($EgressFifo)]) = 'true'"!][!//
              [!VAR "EthCtrlConfigEgressFifoBufLenByteValue" = "EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[EthCtrlConfigEgressFifoIdx = ($EgressFifo)]/EthCtrlConfigEgressFifoBufLenByte"!][!//
              [!VAR "EthCtrlConfigEgressFifoBufTotalValue" = "EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[EthCtrlConfigEgressFifoIdx = ($EgressFifo)]/EthCtrlConfigEgressFifoBufTotal"!][!//
              [!IF "(num:i($EthCtrlConfigEgressFifoBufTotalValue) = num:i(0)) or (num:i($EthCtrlConfigEgressFifoBufLenByteValue) = num:i(0))"!][!//
                [!ERROR!][!//
                  88-000-01-ERROR:The egress FIFO buffer length and buffer size should not be zero for packets to be transmitted. If the egress FIFO is not required for transmission in any of the variant, delete the egress container having FIFO index [!"num:i($EgressFifo)"!] for controller [!"./EthCtrlIdx"!].
                [!ENDERROR!][!//
              [!ENDIF!]!][!//
              [!IF "num:i($EthCtrlConfigEgressFifoBufLenByteValue) <= num:i(18)"!][!//
                [!ERROR!][!//
                  88-000-02-ERROR:The egress FIFO buffer length configured should be greater than 18 bytes as the length of 18 bytes are consumed by Header and FCFS fields of Ethernet packets. Modify accordingly the FIFO buffer length of egress FIFO having FIFO index [!"num:i($EgressFifo)"!] for controller [!"./EthCtrlIdx"!].
                [!ENDERROR!][!//
              [!ENDIF!]!][!//
              [!VAR "TxBufQuotient" = "num:i($EthCtrlConfigEgressFifoBufLenByteValue) div 16"!][!//
              [!IF "num:i($EthCtrlConfigEgressFifoBufLenByteValue) mod 16 != 0"!][!//
                [!VAR "EthCtrlConfigEgressFifoBufLenByteValue" = "(num:i($TxBufQuotient) + 1) * 16"!][!//
              [!ENDIF!]!][!//
              [!VAR "TxBuffer" = "(string(num:i($EthCtrlConfigEgressFifoBufLenByteValue) * num:i($EthCtrlConfigEgressFifoBufTotalValue)))"!][!//
              [!VAR "EgressFifoIdx" = "EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[EthCtrlConfigEgressFifoIdx = ($EgressFifo)]/EthCtrlConfigEgressFifoIdx"!][!//
              [!CODE!][!//
                /* Tx buffer count and size for controller[!"./EthCtrlIdx"!] FIFO Index[!"num:i($EgressFifoIdx)"!] */
                #define ETH_FIFO[!"num:i($EgressFifoIdx)"!]_CTRL[!"./EthCtrlIdx"!]_TXBUF_COUNT      ([!"num:i($EthCtrlConfigEgressFifoBufTotalValue)"!]U)
                #define ETH_FIFO[!"num:i($EgressFifoIdx)"!]_CTRL[!"./EthCtrlIdx"!]_TXBUF_SIZE       ([!"string($TxBuffer)"!]U)
                /* #Violation: Eth_Cfg_h_REF_1*/
                #define ETH_FIFO[!"num:i($EgressFifoIdx)"!]_CTRL[!"./EthCtrlIdx"!]_TXBUF_PER_SIZE   ([!"num:i($EthCtrlConfigEgressFifoBufLenByteValue)"!]U)
              [!ENDCODE!][!CR!]
            [!ELSE!][!//
              [!CODE!]
                /* Tx buffer count and size for controller[!"./EthCtrlIdx"!] FIFO Index[!"num:i($EgressFifo)"!] */
                #define ETH_FIFO[!"num:i($EgressFifo)"!]_CTRL[!"./EthCtrlIdx"!]_TXBUF_COUNT      (0U)
                #define ETH_FIFO[!"num:i($EgressFifo)"!]_CTRL[!"./EthCtrlIdx"!]_TXBUF_SIZE       (0U)
                /* #Violation: Eth_Cfg_h_REF_1*/
                #define ETH_FIFO[!"num:i($EgressFifo)"!]_CTRL[!"./EthCtrlIdx"!]_TXBUF_PER_SIZE   (0U)
              [!ENDCODE!][!CR!]
            [!ENDIF!][!//
          [!ENDFOR!][!//
          [!CODE!][!//
          /* Number of Transmit FIFOs configured */
          #define ETH_CTRL[!"./EthCtrlIdx"!]_TXFIFO_CFGD       ([!"num:i(count(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*))"!]U)
          [!ENDCODE!][!//
        [!ENDNOCODE!][!//
        [!VAR "TxBuffer"= "num:i(0)"!][!//
        [!VAR "RxBuffer"= "num:i(0)"!][!//
        [!VAR "EthCtrlRxBufLenBytevalue"= "num:i(0)"!][!//
        [!VAR "EthCtrlTxBufLenBytevalue"= "num:i(0)"!][!//
        [!VAR "RxBufQuotient"= "num:i(0)"!][!//
        [!VAR "TxBufQuotient"= "num:i(0)"!][!//
        [!VAR "TotalRxBufferSize"= "num:i(0)"!][!//
      [!ENDSELECT!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
[!ENDSELECT!][!//

/* \[SWS_Eth_00216] [SWS_Eth_00217]*/    
#define ETH_OFFLOAD_CHECKSUM_ICMP            ([!//
    [!IF "EthGeneral/EthCtrlOffloading/EthCtrlEnableOffloadChecksumICMP = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
#define ETH_OFFLOAD_CHECKSUM_IPV4            ([!//
    [!IF "EthGeneral/EthCtrlOffloading/EthCtrlEnableOffloadChecksumIPv4 = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
#define ETH_OFFLOAD_CHECKSUM_TCP             ([!//
    [!IF "EthGeneral/EthCtrlOffloading/EthCtrlEnableOffloadChecksumTCP = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
#define ETH_OFFLOAD_CHECKSUM_UDP             ([!//
    [!IF "EthGeneral/EthCtrlOffloading/EthCtrlEnableOffloadChecksumUDP = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
#define ETH_OFFLOAD_CHECKSUM                                                            \
    (ETH_OFFLOAD_CHECKSUM_ICMP | ETH_OFFLOAD_CHECKSUM_IPV4 | ETH_OFFLOAD_CHECKSUM_TCP | \
     ETH_OFFLOAD_CHECKSUM_UDP)

/* #Violation: Eth_Cfg_h_REF_1*/
#define ETH_MAIN_FUNCTION_PERIOD_IN_NANOSEC  ([!"num:i(node:value(EthGeneral/EthMainFunctionPeriod )*1000)"!]U)
/* Configuration: ETH_MAX_CTRLS 
   Limits the total number of supported controllers */
#define ETH_MAX_CTRLS                        ([!//
[!"num:i(node:value(EthGeneral/EthMaxCtrlsSupported ))"!]U)
/* Configuration: ETH_INDEX 
   Ethernet Driver Instance ID, used in DET_Report(.,.) Interface. */
#define ETH_INDEX                            ([!//
[!"num:i(node:value(EthGeneral/EthIndex ))"!]U)


#define ETH_ENA_MII_API                      ([!//
    [!IF "EthConfigSet/EthCtrlConfig/*[1]/EthCtrlEnableMii = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
#define ETH_ENA_TX_INT                       ([!//
    [!IF "EthConfigSet/EthCtrlConfig/*[1]/EthCtrlEnableTxInterrupt = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
#define ETH_ENA_RX_INT                       ([!//
    [!IF "EthConfigSet/EthCtrlConfig/*[1]/EthCtrlEnableRxInterrupt = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
/* \[SWS_Eth_00003] The Ethernet Driver is using a zero-based index to abstract the access for upper
software layers. The parameter Eth_CtrlIdx within configuration corresponds to
parameter CtrlIdx used in the API.*/
[!FOR "ConfigId" = "num:i(0)" TO "num:i(1) - num:i(1)"!][!//
    [!SELECT "EthConfigSet/EthCtrlConfig/*[1]"!][!//
      #ifndef EthConf_EthCtrlConfig_[!"node:name(.)"!]
      #define EthConf_EthCtrlConfig_[!"node:name(.)"!] ([!//
      [!"num:i(node:value(./EthCtrlIdx))"!]U)
      #endif
    [!ENDSELECT!][!//
[!ENDFOR!][!//
/* ETH  mapped to Core0 */
#define ETH_MAX_CTRL_TO_CORE0             ([!"num:i($EthChannelMappedCore0)"!]U)
/* ETH  mapped to Core1 */
#define ETH_MAX_CTRL_TO_CORE1             ([!"num:i($EthChannelMappedCore1)"!]U)
/* ETH  mapped to Core2 */
#define ETH_MAX_CTRL_TO_CORE2             ([!"num:i($EthChannelMappedCore2)"!]U)
/* ETH  mapped to Core3 */
#define ETH_MAX_CTRL_TO_CORE3             ([!"num:i($EthChannelMappedCore3)"!]U)
[!ENDINDENT!][!//
#define ETH_SAFETY_ENABLE                 ([!//
[!IF "EthGeneral/EthSafetyErrorDetect = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

#endif /* ETH_CFG_H */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

