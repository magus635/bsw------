[!/*****************************************************************************************************
*   FileName              : Eth-PBcfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Ethernet
*
*   brief                 : Eth post build configuration 
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
*****************************************************************************************************/!]
/****************************************************************************************************
*   FileName              : Eth_PBCfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Ethernet
*
*   brief                 : This file contains all configurations of Ethernet Driver
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
*#Eth_PBcfg_c_REF_1:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Eth_PBcfg_c_REF_2:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers
*
*#Eth_PBcfg_c_REF_3:MISRAC2012-Rule-10.5;
* Justification:Redundant cast is necessary to maintain the software structure and reduce the 
* complexity.
*
*#Eth_PBcfg_c_REF_4:MISRAC2012-Rule-11.4; 
* Justification:Converting integers to object pointers to reduce register access complexity.
*
*#Eth_PBcfg_c_REF_7:CWE-547; 
* Justification: The Tresos-generated code does not use symbolic constants for buffer size 
* substitution.
*
*/
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
[!NOCODE!][!//
[!VAR "IsTha6104" = "num:i(0)"!][!//
[!IF "node:containsValue(as:modconf('Resource')/ResourceGeneral/ResourceSubderivative, 'THA610X_LFBGA180')"!][!//
[!VAR "IsTha6104" = "num:i(1)"!][!//
[!ENDIF!][!//
[!INCLUDE "Eth_Cfg_Common.m"!][!//
[!ENDNOCODE!][!//
[!INDENT "0"!][!//
/* Include ETH Module File */
#include "Eth.h"



#if (ETH_FIFO0_CTRL0_RXBUF_SIZE > 0)
extern ALIGNED(64)  uint8 Eth_FIFO0RxBuffer[ETH_FIFO0_CTRL0_RXBUF_SIZE];
#endif /*(ETH_FIFO0_CTRL0_RXBUF_SIZE \> 0)*/
#if (ETH_FIFO1_CTRL0_RXBUF_SIZE > 0)
extern ALIGNED(64)  uint8 Eth_FIFO1RxBuffer[ETH_FIFO1_CTRL0_RXBUF_SIZE];
#endif /*(ETH_FIFO1_CTRL0_RXBUF_SIZE \> 0)*/
#if (ETH_FIFO2_CTRL0_RXBUF_SIZE > 0)
extern ALIGNED(64) uint8 Eth_FIFO2RxBuffer[ETH_FIFO2_CTRL0_RXBUF_SIZE];
#endif /*(ETH_FIFO2_CTRL0_RXBUF_SIZE \> 0)*/
#if (ETH_FIFO3_CTRL0_RXBUF_SIZE > 0)
extern ALIGNED(64)  uint8 Eth_FIFO3RxBuffer[ETH_FIFO3_CTRL0_RXBUF_SIZE];
#endif /*(ETH_FIFO3_CTRL0_RXBUF_SIZE \> 0)*/

#if (ETH_FIFO0_CTRL0_TXBUF_SIZE > 0)
extern ALIGNED(64)  uint8 Eth_FIFO0TxBuffer[ETH_FIFO0_CTRL0_TXBUF_SIZE];
#endif /*(ETH_FIFO0_CTRL0_TXBUF_SIZE \> 0)*/
#if (ETH_FIFO1_CTRL0_TXBUF_SIZE > 0)
extern ALIGNED(64)  uint8 Eth_FIFO1TxBuffer[ETH_FIFO1_CTRL0_TXBUF_SIZE];
#endif /*(ETH_FIFO1_CTRL0_TXBUF_SIZE \> 0)*/

#if (ETH_FIFO2_CTRL0_TXBUF_SIZE > 0)
extern ALIGNED(64)  uint8 Eth_FIFO2TxBuffer[ETH_FIFO2_CTRL0_TXBUF_SIZE];
#endif /*(ETH_FIFO2_CTRL0_TXBUF_SIZE \> 0)*/
#if (ETH_FIFO3_CTRL0_TXBUF_SIZE > 0)
extern ALIGNED(64)  uint8 Eth_FIFO3TxBuffer[ETH_FIFO3_CTRL0_TXBUF_SIZE];
#endif /*(ETH_FIFO3_CTRL0_TXBUF_SIZE \> 0)*/



#if (ETH_FIFO0_CTRL0_TXBUF_COUNT > 0)
extern ALIGNED(64)  Eth_TxDescr Eth_Tx0descr[ETH_FIFO0_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO0_CTRL0_TXBUF_COUNT \> 0)*/
#if (ETH_FIFO1_CTRL0_TXBUF_COUNT > 0)
extern ALIGNED(64)  Eth_TxDescr Eth_Tx1descr[ETH_FIFO1_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO1_CTRL0_TXBUF_COUNT \> 0)*/
#if (ETH_FIFO2_CTRL0_TXBUF_COUNT > 0)
extern ALIGNED(64)  Eth_TxDescr Eth_Tx2descr[ETH_FIFO2_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO2_CTRL0_TXBUF_COUNT \> 0)*/
#if (ETH_FIFO3_CTRL0_TXBUF_COUNT > 0)
extern ALIGNED(64)  Eth_TxDescr Eth_Tx3descr[ETH_FIFO3_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO3_CTRL0_TXBUF_COUNT \> 0)*/

#if (ETH_FIFO0_CTRL0_RXBUF_COUNT > 0)
extern ALIGNED(64)  Eth_RxDescr Eth_Rx0descr[ETH_FIFO0_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO0_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO1_CTRL0_RXBUF_COUNT > 0)
extern ALIGNED(64)  Eth_RxDescr Eth_Rx1descr[ETH_FIFO1_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO1_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO2_CTRL0_RXBUF_COUNT > 0)
extern ALIGNED(64)  Eth_RxDescr Eth_Rx2descr[ETH_FIFO2_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO2_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO3_CTRL0_RXBUF_COUNT > 0)
extern ALIGNED(64)  Eth_RxDescr Eth_Rx3descr[ETH_FIFO3_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO3_CTRL0_RXBUF_COUNT \> 0)*/


[!ENDINDENT!][!//

[!AUTOSPACING!]
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
[!INDENT "0"!][!//
[!NOCODE!]
[!INCLUDE "Eth_Cfg_Common.m"!][!//
[!ENDNOCODE!]

/* the source clock of Geth is AXI clock. config in MCU*/
[!SELECT "as:modconf('Mcu')[1]"!][!//
  [!VAR "EthPeripheralBusFrequency" = "num:i(node:value(McuModuleConfiguration/McuClockSettingConfig/*[1]/McuSysClkDiv_Configuration/McuAXIClkFrequency))"!][!//
  [!IF "node:containsValue(as:modconf('Resource')/ResourceGeneral/ResourceSubderivative, 'THA610X_LFBGA180')"!][!//
  [!VAR "EthPeripheralBusFrequency" = "num:i(node:value(McuModuleConfiguration/McuClockSettingConfig/*[1]/McuSysClkDiv_Configuration/McuAHBClkFrequency))"!][!//
  [!ENDIF!][!//

   /* Clock configuration for MDIO - between 1.0 MHz to 2.5 MHz frequency. */
  [!IF "(($EthPeripheralBusFrequency >= 60000000) and ($EthPeripheralBusFrequency < 100000000) )"!][!//
    [!VAR "CrValue" = "num:i(0)"!][!//
  [!ELSEIF "(($EthPeripheralBusFrequency >= 100000000) and ($EthPeripheralBusFrequency <150000000) )"!][!//
    [!VAR "CrValue" = "num:i(1)"!][!//
  [!ELSEIF "(($EthPeripheralBusFrequency >= 150000000) and ($EthPeripheralBusFrequency <250000000) )"!][!//
    [!VAR "CrValue" = "num:i(4)"!][!//
  [!ELSEIF "(($EthPeripheralBusFrequency >= 250000000) and ($EthPeripheralBusFrequency <300000000) )"!][!//
    [!VAR "CrValue" = "num:i(5)"!][!//
  [!ELSE!]
    #error Invalid Mcu McuAXIClkFrequency in McuModuleConfiguration
  [!ENDIF!][!//
[!ENDSELECT!][!//

[!AUTOSPACING!][!//
[!SELECT "as:modconf('Eth')[1]"!][!//
  [!NOCODE!][!//
  [!VAR "MaxControllers"= "ecu:get('Eth.MaxControllers')"!][!//

  [!/*************Macro for Config Shaper detection************/!][!//
  [!NOCODE!][!//
  [!MACRO "Eth_ShaperDet", "PredecessorRef" = "", "RetVal" = ""!][!//
    [!VAR "PredString" = "$PredecessorRef"!][!//
    [!VAR "LoopCount" = "count(EthCtrlConfigEgress/EthCtrlConfigShaper/*)"!][!//
    [!FOR "Count1" = "num:i(1)" TO "num:i($LoopCount)"!][!//
      [!VAR "StringSearch" = "node:name(EthCtrlConfigEgress/EthCtrlConfigShaper/*[num:i($Count1)])"!][!//
      [!IF "$StringSearch = $PredString"!][!//
        [!VAR "RetVal" = "num:i(1)"!][!//
        [!BREAK!][!//
      [!ENDIF!][!//
    [!ENDFOR!][!//
  [!ENDMACRO!][!//
  [!ENDNOCODE!][!//

  [!/***********************************SORTING MACRO******************************/!][!//
  [!NOCODE!][!//
  [!MACRO "Sorting","SortArray" = "","VItem" = "","VTotalNum" = "",,"VDrctn" = ""!][!//
    [!VAR "VTempStr1" = "''"!][!//
    [!VAR "VTempStr2" = "''"!][!//
    [!VAR "VTempStr1_1" = "''"!][!//
    [!VAR "VTempStr2_2" = "''"!][!//
    [!VAR "Vcount1" = "num:i(0)"!][!//
    [!VAR "Vcount2" = "num:i(0)"!][!//
    [!VAR "VTempInt1" = "num:i(0)"!][!//
    [!VAR "VTempInt2" = "num:i(0)"!][!//
    [!VAR "VTempReplceStr1" = "'String1'"!][!//
    [!VAR "VTempReplceStr2" = "'String2'"!][!//
    [!FOR "Vcount1" = "num:i(1)" TO "num:i($VTotalNum - 1)"!][!//
      [!FOR "Vcount2" = "num:i($Vcount1 + 1)" TO "num:i($VTotalNum)"!][!//
        [!VAR "VTempStr1" = "text:split($SortArray,'@')[num:i($Vcount1)]"!][!//
        [!VAR "VTempStr2" = "text:split($SortArray,'@')[num:i($Vcount2)]"!][!//
        [!VAR "VTempStr1_1" = "text:split($VTempStr1,',')[num:i($VItem)]"!][!//
        [!VAR "VTempStr2_2" = "text:split($VTempStr2,',')[num:i($VItem)]"!][!//
        [!VAR "VTempInt1" = "num:i(number($VTempStr1_1))"!][!//
        [!VAR "VTempInt2" = "num:i(number($VTempStr2_2))"!][!//
        [!IF "$VDrctn > num:i(0)"!][!//
          [!IF "$VTempInt1 > $VTempInt2"!][!//
            [!VAR "SortArray" = "text:replace($SortArray,$VTempStr1,$VTempReplceStr1)"!][!//
            [!VAR "SortArray" = "text:replace($SortArray,$VTempStr2,$VTempReplceStr2)"!][!//
            [!VAR "SortArray" = "text:replace($SortArray,$VTempReplceStr2,$VTempStr1)"!][!//
            [!VAR "SortArray" = "text:replace($SortArray,$VTempReplceStr1,$VTempStr2)"!][!//
          [!ENDIF!][!//
        [!ELSE!][!//
          [!IF "$VTempInt1 < $VTempInt2"!][!//
            [!VAR "SortArray" = "text:replace($SortArray,$VTempStr1,$VTempReplceStr1)"!][!//
            [!VAR "SortArray" = "text:replace($SortArray,$VTempStr2,$VTempReplceStr2)"!][!//
            [!VAR "SortArray" = "text:replace($SortArray,$VTempReplceStr2,$VTempStr1)"!][!//
            [!VAR "SortArray" = "text:replace($SortArray,$VTempReplceStr1,$VTempStr2)"!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDFOR!][!//
    [!ENDFOR!][!//
  [!ENDMACRO!][!//
  [!ENDNOCODE!][!//
  [!/******/!][!//

  [!/***********************************REPLACE MACRO******************************/!][!//
  [!NOCODE!][!//
  [!MACRO "ReplaceValue","ReplaceArray" = "","VPosition" = "","VReplaceVal" = ""!][!//
    [!VAR "VRplc1" = "''"!][!//
    [!VAR "VRplc2" = "''"!][!//
    [!VAR "VRplc1" = "substring($ReplaceArray,1,(num:i($VPosition)-1))"!][!//
    [!VAR "VRplc2" = "substring($ReplaceArray,(num:i($VPosition)+1))"!][!//
    [!VAR "ReplaceArray" = "concat($VRplc1,$VReplaceVal,$VRplc2)"!][!//
  [!ENDMACRO!][!//
  [!ENDNOCODE!][!//
  [!/******/!][!//

  [!/***********************************SUM MACRO******************************/!][!//
  [!NOCODE!][!//
  [!MACRO "SumElem","SumArray" = "","VNumElem" = "","SumVal" = ""!][!//
    [!VAR "VTempSum" = "num:i(0)"!][!//
    [!FOR "Vcount" = "num:i(1)" TO "num:i($VNumElem)"!][!//
      [!VAR "VElemVal" = "text:split($SumArray,' ')[num:i($Vcount)]"!][!//
      [!VAR "VTempSum" = "num:i($VTempSum) + num:i($VElemVal)"!][!//
    [!ENDFOR!][!//
    [!VAR "SumVal" = "num:i($VTempSum)"!][!//
  [!ENDMACRO!][!//
  [!ENDNOCODE!][!//
  [!/******/!][!//

  [!/*** Error check if Predecessor Order is continuous in Strict Priority ******/!][!//
  [!/*** Error check if Weight with value 0 is configured for WRR ***********/!][!//
  [!/*** Error check if DMA Weights are not configured for WSP and WRR  ******/!][!//
  [!FOR "ControllerId" = "num:i(0)" TO "num:i($MaxControllers)-num:i(1)"!][!//
    [!VAR "Count" = "''"!][!//
    [!SELECT "EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]/EthCtrlConfigEgress"!][!//
      [!LOOP "(EthCtrlConfigScheduler/*)"!][!//
        [!IF "node:value(./EthCtrlConfigSchedulerAlgorithm) = 'ETH_SCHEDULER_STRICT_PRIORITY'"!][!//
          [!VAR "PredecessorRange" = "num:i(count(EthCtrlConfigSchedulerPredecessor/*)) - num:i(1)"!][!//
          [!LOOP "(EthCtrlConfigSchedulerPredecessor/*)"!][!//
            [!VAR "Order" = "num:i(./EthCtrlConfigSchedulerPredecessorOrder)"!][!//
            [!IF "$Order > num:i($PredecessorRange)"!][!//
              [!ERROR!][!//
                88-000-03-ERROR: EthCtrlConfigSchedulerPredecessorOrder is not within the range [0,[!"num:i($PredecessorRange)"!]] for Strict Priority scheduling algorithm.
              [!ENDERROR!][!//
            [!ENDIF!][!//
            [!IF "contains($Count, $Order)"!][!//
              [!ERROR!][!//
                88-000-05-ERROR: EthCtrlConfigSchedulerPredecessorOrder is not unique for Strict Priority scheduling algorithm.
              [!ENDERROR!][!//
            [!ELSE!][!//
              [!VAR "Count" = "concat($Count,string($Order))"!][!//
            [!ENDIF!][!//
          [!ENDLOOP!][!//
        [!ELSE!][!//
          [!LOOP "(EthCtrlConfigSchedulerPredecessor/*)"!][!//
            [!VAR "Order" = "num:i(./EthCtrlConfigSchedulerPredecessorOrder)"!][!//
            [!IF "$Order = num:i(0)"!][!//
              [!ERROR!][!//
                88-000-06-ERROR: EthCtrlConfigSchedulerPredecessorOrder which corresponds to the weight cannot be 0 for Weighted Round Robin scheduling.
              [!ENDERROR!][!//
            [!ENDIF!][!//
          [!ENDLOOP!][!//
        [!ENDIF!][!//
      [!ENDLOOP!][!//
    [!ENDSELECT!][!//
    [!SELECT "EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]/EthCtrlConfigEgress/EthCtrlConfigDMAArbitration/*[1]"!][!//
        [!IF "node:value(./EthCtrlConfigDMAArbitrationAlgorithm) != 'ETH_DMA_ARBITRATION_FIXED_PRIORITY'"!][!//
          [!IF "not(node:exists(EthCtrlConfigDMAWeightAssignment/*))"!][!//
            [!ERROR!][!//
              88-000-07-ERROR: Weights for the DMA scheduler needs to be configured for the egress FIFOs in Weighted Round Robin or Weighted Strict Priority scheduling.
            [!ENDERROR!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDSELECT!][!//
  [!ENDFOR!][!//

  [!/*************Error check if FIFO order is continuous and Priority is assigned to IngressFifo************/!][!//
  [!FOR "ControllerId" = "num:i(0)" TO "num:i($MaxControllers)-num:i(1)"!][!//
    [!VAR "Count" = "num:i(0)"!][!//
    [!VAR "IngressFifoConfigured" = "num:i(0)"!][!//
    [!VAR "FifoIdx" = "num:i(0)"!][!//
    [!SELECT "EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]"!][!//
      [!VAR "EgressVal" = "node:isconsecutive(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*/EthCtrlConfigEgressFifoIdx,0)"!][!//
      [!IF "($EgressVal) = 'false'"!][!//
        [!ERROR!][!//
          88-000-08-ERROR : EthCtrlConfigEgressFifoIdx order is not continuous. EthCtrlConfigEgressFifoIdx order should be continuous and start from 0.
        [!ENDERROR!][!//
      [!ENDIF!][!//
      [!VAR "IngressVal" = "node:isconsecutive(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*/EthCtrlConfigIngressFifoIdx,0)"!][!//
      [!IF "($IngressVal) = 'false'"!][!//
        [!ERROR!][!//
          88-000-09-ERROR : EthCtrlConfigIngressFifoIdx order is not continuous. EthCtrlConfigIngressFifoIdx order should be continuous and start from 0.
        [!ENDERROR!][!//
      [!ENDIF!][!//
      [!VAR "IngressFifoConfigured" = "num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*))"!][!//
      [!IF "$IngressFifoConfigured > num:i(1)"!][!//
        [!FOR "IngressFifo" = "num:i(0)" TO "num:i($IngressFifoConfigured) - num:i(1)"!][!//
          [!VAR "FifoIdx" = "EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoIdx"!][!//
          [!IF "not(node:exists(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoPriorityAssignment/*))"!][!//
            [!ERROR!][!//
              88-000-10-ERROR : Priority not assigned to Ingress Fifo index [!"$FifoIdx"!]. If more than one FIFO is configured, priority assignment for all the FIFOs is mandatory.
            [!ENDERROR!][!//
          [!ENDIF!][!//
        [!ENDFOR!][!//
      [!ENDIF!][!//
    [!ENDSELECT!][!//
  [!ENDFOR!][!//

  [!/******* Error check for missing priority and valid reference************/!][!//
  [!FOR "ControllerId" = "num:i(0)" TO "num:i($MaxControllers)-num:i(1)"!][!//
  [!VAR "EFifoPriorityOrderString" ="''"!][!//
  [!VAR "EFifoPriorityCountString" ="''"!][!//
  [!VAR "IFifoPriorityOrderString" ="''"!][!//
  [!IF "node:exists(EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = $ControllerId])"!][!//
    [!SELECT "EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]"!][!//
      [!/****************Egress valid reference error**************/!][!//
      [!VAR "EgressFifoConfigured" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*))"!][!//
      [!IF "$EgressFifoConfigured > num:i(0)"!][!//
        [!VAR "SchedString" = "node:name(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1])"!][!//
        [!VAR "PredecessorMax" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*))"!][!//
        [!FOR "Predecessor" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
          [!VAR "RefVal" = "node:refvalid(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)"!][!//
          [!IF "$RefVal = 'false'"!][!//
            [!ERROR!][!//
              88-000-11-ERROR:Select valid reference for EthCtrlConfigSchedulerPredecessorRef parameter for scheduling the Egress FIFO.
            [!ENDERROR!][!//
          [!ENDIF!][!//
          [!VAR "PredRefString" = "text:split(node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef),'/')[last()]"!][!//
          [!IF "$SchedString = $PredRefString"!][!//
            [!ERROR!][!//
              88-000-12-ERROR:The parameter EthCtrlConfigSchedulerPredecessorRef cannot have a reference to scheduler, as only one scheduler is supported by the Ethernet driver. Remove the scheduler reference.
            [!ENDERROR!][!//
          [!ENDIF!][!//
        [!ENDFOR!][!//
      [!ENDIF!][!//
      [!/*************Missing priority and valid reference error************/!][!//
      [!VAR "IngressFifoConfigured" = "num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*))"!][!//
      [!IF "$IngressFifoConfigured > num:i(0)"!][!//
        [!FOR "IngressFifo" = "num:i(0)" TO "num:i($IngressFifoConfigured) - num:i(1)"!][!//
          [!VAR "IFifoPriorityCount" = "num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoPriorityAssignment/*))"!][!//
          [!IF "$IFifoPriorityCount != num:i(0)"!][!//
            [!FOR "Count" = "num:i(1)" TO "num:i($IFifoPriorityCount)"!][!//
              [!VAR "IngressPriority" = "EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoPriorityAssignment/*[num:i($Count)]"!][!//
              [!VAR "IFifoPriorityOrderString" = "string(concat($IFifoPriorityOrderString,$IngressPriority))"!][!//
            [!ENDFOR!][!//
          [!ELSE!][!//
            [!VAR "IFifoPriorityOrderString" = "string("01234567")"!][!//
          [!ENDIF!][!//
        [!ENDFOR!][!//
        [!FOR "Count" = "num:i(0)" TO "num:i(7)"!][!//
          [!VAR "BolVal" = "text:contains(string($IFifoPriorityOrderString),string($Count))"!][!//
          [!IF "$BolVal = 'false'"!][!//
            [!ERROR!][!//
              88-000-13-ERROR:All the ingress priorities within the range [0,7] should be configured within the Ingress FIFOs. This is required by the GETHMAC IP hardware for routing of packets.
            [!ENDERROR!][!//
          [!ENDIF!][!//
        [!ENDFOR!][!//
        [!VAR "RefVal" = "node:refvalid(EthCtrlConfigIngress/EthCtrlConfigIngressUntaggedPktsFifoRef)"!][!//
        [!IF "$RefVal = 'false'"!][!//
          [!ERROR!][!//
            88-000-11-ERROR:Select a valid reference for EthCtrlConfigIngressUntaggedPktsFifoRef parameter to route the untagged packets to the Ingress FIFO.
          [!ENDERROR!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDSELECT!][!//
  [!ENDIF!][!//
  [!ENDFOR!][!//

  [!/*************Error check if Config shaper is scheduled before normal scheduler************/!][!//
  [!FOR "ControllerId" = "num:i(0)" TO "num:i($MaxControllers) - num:i(1)"!][!//
    [!VAR "TempVal" = "num:i(0)"!][!//
    [!VAR "ShaperCnt" = "num:i(0)"!][!//
    [!SELECT "EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]"!][!//
    [!VAR "EgressFifoConfigured" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*))"!][!//
    [!IF "$EgressFifoConfigured > num:i(0)"!][!//
      [!VAR "ShaperMax" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigShaper/*))"!][!//
      [!IF "node:exists(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]) = 'true'"!][!//
        [!VAR "PredecessorMax" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*))"!][!//
        [!FOR "Predecessor" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
          [!VAR "PredecessorString" = "text:split(node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef),'/')[last()]"!][!//
          [!CALL "Eth_ShaperDet", "PredecessorRef" = "$PredecessorString", "RetVal" = "num:i(255)"!][!//            
          [!IF "$RetVal = num:i(255)"!][!//
            [!VAR "EFifoId" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoIdx))"!][!//
          [!ELSE!][!//
            [!VAR "EFifoId" = "num:i(255)"!][!//
            [!VAR "ShaperCnt" = "num:i($ShaperCnt+num:i(1))"!][!//
          [!ENDIF!][!//
          [!FOR "Shaper" = "num:i(1)" TO "num:i($ShaperMax)"!][!//
            [!VAR "SFifoId" = "node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigShaper/*[num:i($Shaper)]/EthCtrlConfigShaperPredecessorFifoRef)/EthCtrlConfigEgressFifoIdx)"!][!//
            [!IF "$EFifoId = $SFifoId"!][!//
              [!ERROR!][!//
                88-000-14-ERROR:Fifo index [!"$EFifoId"!] is configured in EthCtrlConfigShaper as well as in Config scheduler. EthCtrlConfigShaper needs to be configured in Config scheduler.
              [!ENDERROR!][!//
            [!ENDIF!][!//
          [!ENDFOR!][!//
        [!ENDFOR!][!//
        [!IF "$ShaperCnt = $PredecessorMax"!][!//
          [!ERROR!][!//
            88-000-15-ERROR:EthCtrlConfigScheduler cannot have only EthCtrlConfigShaper scheduled. There should be atleast one egress FIFO without shaper configured for scheduling.
          [!ENDERROR!][!//
        [!ENDIF!][!//
        [!IF "node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerAlgorithm) = 'ETH_SCHEDULER_STRICT_PRIORITY'"!][!//
          [!VAR "TempVal" = "num:i(0)"!][!//
          [!FOR "Predecessor" = "num:i(0)" TO "num:i($PredecessorMax) - num:i(1)"!][!//
            [!VAR "PredecessorString" = "text:split(node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[EthCtrlConfigSchedulerPredecessorOrder = ($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef),'/')[last()]"!][!//
            [!CALL "Eth_ShaperDet", "PredecessorRef" = "$PredecessorString", "RetVal" = "num:i(255)"!][!//
            [!IF "$RetVal = num:i(1)"!][!//
              [!VAR "TempVal" = "num:i(1)"!][!//
            [!ENDIF!][!//
            [!IF "$TempVal = num:i(1)"!][!//
              [!IF "$RetVal = num:i(255)"!][!//
                [!ERROR!][!//
                   88-000-16-ERROR:EthCtrlConfigFifo [!"$PredecessorString"!] should be scheduled in EthCtrlConfigScheduler before EthCtrlConfigShaper.
                [!ENDERROR!][!//
              [!ENDIF!][!//
            [!ENDIF!][!//
          [!ENDFOR!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!ENDSELECT!][!//
  [!ENDFOR!][!//

  [!/*************Error check if configured MAC type and speed is not supported by the device************/!][!//
  [!FOR "ControllerId" = "num:i(0)" TO "num:i($MaxControllers)-num:i(1)"!][!//
    [!SELECT "EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]"!][!//
      [!IF "./EthCtrlMacLayerType = 'ETH_MAC_LAYER_TYPE_XGMII' and ./EthCtrlMacLayerSubType = 'REDUCED'"!][!//
        [!VAR "PhyIntfFlag" = "(node:containsValue((ecu:list('Eth.EthPhyIntf')), 'RGMII'))"!][!//
        [!IF "$PhyIntfFlag = 'false'"!][!//
          [!ERROR!]
            88-000-17-ERROR : The configured MAC layer type/ subtype- RGMII for controller [!"./EthCtrlIdx"!] is not supported by the device.
          [!ENDERROR!]
        [!ENDIF!][!//
      [!ELSEIF "./EthCtrlMacLayerType = 'ETH_MAC_LAYER_TYPE_XMII' and ./EthCtrlMacLayerSubType = 'REDUCED'"!][!//
        [!VAR "PhyIntfFlag" = "(node:containsValue((ecu:list('Eth.EthPhyIntf')), 'RMII'))"!][!//
        [!IF "$PhyIntfFlag = 'false'"!][!//
          [!ERROR!]
            88-000-17-ERROR: The configured MAC layer type/ subtype- RMII for controller [!"./EthCtrlIdx"!] is not supported by the device.
          [!ENDERROR!]
        [!ENDIF!][!//
      [!ELSEIF "./EthCtrlMacLayerType = 'ETH_MAC_LAYER_TYPE_XMII' and ./EthCtrlMacLayerSubType = 'STANDARD'"!][!//
        [!VAR "PhyIntfFlag" = "(node:containsValue((ecu:list('Eth.EthPhyIntf')), 'MII'))"!][!//
        [!IF "$PhyIntfFlag = 'false'"!][!//
          [!ERROR!]
            88-000-17-ERROR: The configured MAC layer type/ subtype- MII for controller [!"./EthCtrlIdx"!] is not supported by the device.
          [!ENDERROR!]
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!IF "(./EthCtrlMacLayerSpeed = 'ETH_MAC_LAYER_SPEED_1G')"!][!//
        [!VAR "MacSpeedFlag" = "(node:containsValue((ecu:list('Eth.EthSpeed')), 'ETH_1000MBPS'))"!][!//
        [!IF "$MacSpeedFlag = 'false'"!][!//
          [!ERROR!]
            88-000-17-ERROR: The configured MAC layer speed of 1 Gbps for controller [!"./EthCtrlIdx"!] is not supported by the device.
          [!ENDERROR!]
        [!ENDIF!][!//
      [!ELSEIF "(./EthCtrlMacLayerSpeed = 'ETH_MAC_LAYER_SPEED_100M')"!][!//
        [!VAR "MacSpeedFlag" = "(node:containsValue((ecu:list('Eth.EthSpeed')), 'ETH_100MBPS'))"!][!//
        [!IF "$MacSpeedFlag = 'false'"!][!//
          [!ERROR!]
            88-000-17-ERROR: The configured MAC layer speed of 100 Mbps for controller [!"./EthCtrlIdx"!] is not supported by the device.
          [!ENDERROR!]
        [!ENDIF!][!//
        [!IF "$IsTha6104 = num:i(1)"!][!//
          [!IF "./EthCtrlMacLayerType = 'ETH_MAC_LAYER_TYPE_XMII' and ./EthCtrlMacLayerSubType = 'STANDARD'"!][!//
            [!ERROR!]
              88-000-17-ERROR: The configured MAC layer type/ subtype- MII with 100 Mbps for controller [!"./EthCtrlIdx"!] is not supported by the device.
            [!ENDERROR!]
          [!ENDIF!][!//
        [!ENDIF!][!//

      [!ELSEIF "(./EthCtrlMacLayerSpeed = 'ETH_MAC_LAYER_SPEED_10M')"!][!//
        [!VAR "MacSpeedFlag" = "(node:containsValue((ecu:list('Eth.EthSpeed')), 'ETH_10MBPS'))"!][!//
        [!IF "$MacSpeedFlag = 'false'"!][!//
          [!ERROR!]
            88-000-17-ERROR: The configured MAC layer speed of 10 Mbps for controller [!"./EthCtrlIdx"!] is not supported by the device.
          [!ENDERROR!]
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDSELECT!][!//
  [!ENDFOR!][!//
  [!ENDNOCODE!][!//

[!SELECT "EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i(0)]"!][!//
  
[!VAR "ConfiguredFifoIngress" = "num:i(0)"!][!//
  [!VAR "InFifoOrderString" ="''"!][!//
  [!VAR "PriorityString" ="''"!][!//
  [!VAR "IngressFifoIdx" ="num:i(0)"!][!//
  [!VAR "PriorityCnt" = "num:i(0)"!][!//
  [!VAR "Flag" ="num:i(0)"!][!//
  [!VAR "ConfiguredFifoIngress" = "num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*))"!][!//
  [!INDENT "2"!][!//
  [!IF "$ConfiguredFifoIngress > num:i(0)"!][!//
    [!FOR "IngressFifo" = "num:i(0)" TO "num:i($ConfiguredFifoIngress) - num:i(1)"!][!//
      [!IF "node:exists(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]) = 'true'"!][!//
        [!VAR "IngressFifoIdx" = "node:value(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoIdx)"!][!//
        [!VAR "PriorityCnt" = "num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoPriorityAssignment/*))"!][!//
        [!IF "$PriorityCnt > num:i(0)"!][!//
          [!VAR "Priority" = "num:max(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifoIdx)]/EthCtrlConfigIngressFifoPriorityAssignment/*)"!][!//
        [!ELSE!][!//
          [!VAR "Priority" = "num:i(7)"!][!//
        [!ENDIF!][!//
        [!VAR "InBufTotal" = "node:value(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifoIdx)]/EthCtrlConfigIngressFifoBufTotal)"!][!//
        [!VAR "InBufLength" = "node:value(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifoIdx)]/EthCtrlConfigIngressFifoBufLenByte)"!][!//
        [!IF "(num:i($InBufTotal) = num:i(0)) or (num:i($InBufLength) = num:i(0))"!][!//
          [!ERROR!][!//
            88-000-24-ERROR:The ingress FIFO buffer length and buffer size should not be zero for successful reception of packets. If the ingress FIFO is not required for reception, delete the ingress container having FIFO index [!"num:i($IngressFifoIdx)"!] for controller [!"./EthCtrlIdx"!].
          [!ENDERROR!][!//
        [!ENDIF!][!//
        [!IF "num:i($InBufLength) <= num:i(18)"!][!//
          [!ERROR!][!//
            88-000-25-ERROR:The ingress FIFO buffer length configured should be greater than 18 bytes as the length of 18 bytes are consumed by Header and FCFS fields of Ethernet packets. Modify accordingly the FIFO buffer length of ingress FIFO having FIFO index [!"num:i($IngressFifoIdx)"!] for controller [!"./EthCtrlIdx"!].
          [!ENDERROR!][!//
        [!ENDIF!][!//
        [!VAR "InFifoOrderString" = "concat($InFifoOrderString,$IngressFifoIdx,',',$Priority,',',$InBufTotal,',',$InBufLength,'@')"!][!//
      [!ENDIF!][!//
    [!ENDFOR!][!//
  [!ELSE!][!//
  [!ENDIF!][!//
  [!ENDINDENT!][!//
    
    [!VAR "NewPriority" ="num:i(0)"!][!//
      [!VAR "Flag" ="num:i(0)"!][!//
      [!VAR "FifoOrderString" ="''"!][!//
      [!VAR "NonCBSOrderString" ="''"!][!//
      [!VAR "CBSOrderString" ="''"!][!//
      [!VAR "CBSCount" = "num:i(0)"!][!//
      [!VAR "PredecessorString" ="''"!][!//
      [!VAR "BufTotal" = "num:i(0)"!][!//
      [!VAR "BufLength" = "num:i(0)"!][!//

    [!IF "node:exists(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]) = 'true'"!][!//
      [!IF "node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerAlgorithm) = 'ETH_SCHEDULER_STRICT_PRIORITY'"!][!//
        [!FOR "Predecessor" = "num:i(0)" TO "num:i($PredecessorMax)-num:i(1)"!][!//
          [!VAR "PredecessorOrder" = "num:i(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[EthCtrlConfigSchedulerPredecessorOrder = ($Predecessor)]/EthCtrlConfigSchedulerPredecessorOrder)"!][!//
          [!VAR "OldPriority" = "$NewPriority"!][!//
          [!VAR "PredecessorString" = "text:split(node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[EthCtrlConfigSchedulerPredecessorOrder = ($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef),'/')[last()]"!][!//
          [!CALL "Eth_ShaperDet", "PredecessorRef" = "$PredecessorString", "RetVal" = "num:i(255)"!][!//
          [!IF "$RetVal = num:i(1)"!][!//
            [!VAR "FifoIdx" = "node:value(node:ref(node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[EthCtrlConfigSchedulerPredecessorOrder = ($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigShaperPredecessorFifoRef))/EthCtrlConfigEgressFifoIdx)"!][!//
            [!VAR "BufTotal" = "node:value(node:ref(node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[EthCtrlConfigSchedulerPredecessorOrder = ($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigShaperPredecessorFifoRef))/EthCtrlConfigEgressFifoBufTotal)"!][!//
            [!VAR "BufLength" = "node:value(node:ref(node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[EthCtrlConfigSchedulerPredecessorOrder = ($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigShaperPredecessorFifoRef))/EthCtrlConfigEgressFifoBufLenByte)"!][!//
          [!ELSE!][!//
            [!VAR "FifoIdx" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[EthCtrlConfigSchedulerPredecessorOrder = ($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoIdx))"!][!//
            [!VAR "BufTotal" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[EthCtrlConfigSchedulerPredecessorOrder = ($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoBufTotal))"!][!//
            [!VAR "BufLength" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[EthCtrlConfigSchedulerPredecessorOrder = ($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoBufLenByte))"!][!//
          [!ENDIF!][!//
          [!VAR "FifoOrderString" = "concat($FifoOrderString,$FifoIdx,',',$PredecessorOrder,',',$BufTotal,',',$BufLength,'@')"!][!//form the string FifoIdx,PredecessorOrder,BufTotal,BufLength@.....
        [!ENDFOR!][!//
      [!ELSE!][!//
        [!FOR "Predecessor" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
          [!VAR "PredecessorOrder" = "num:i(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorOrder)"!][!//
          [!VAR "PredecessorString" = "text:split(node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef),'/')[last()]"!][!//
          [!CALL "Eth_ShaperDet", "PredecessorRef" = "$PredecessorString", "RetVal" = "num:i(255)"!][!//
          [!IF "$RetVal = num:i(1)"!][!//
            [!VAR "FifoIdx" = "node:value(node:ref(node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigShaperPredecessorFifoRef))/EthCtrlConfigEgressFifoIdx)"!][!//
            [!VAR "BufTotal" = "node:value(node:ref(node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigShaperPredecessorFifoRef))/EthCtrlConfigEgressFifoBufTotal)"!][!//
            [!VAR "BufLength" = "node:value(node:ref(node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigShaperPredecessorFifoRef))/EthCtrlConfigEgressFifoBufLenByte)"!][!//
          [!ELSE!][!//
            [!VAR "FifoIdx" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoIdx))"!][!//
            [!VAR "BufTotal" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoBufTotal))"!][!//
            [!VAR "BufLength" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoBufLenByte))"!][!//
          [!ENDIF!][!//
          [!IF "node:exists(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[EthCtrlConfigEgressFifoIdx = ($FifoIdx)]/EthCtrlConfigEgressFifoPriorityAssignment/*) = 'true'"!][!//
            [!VAR "NewPriority" = "num:max(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[EthCtrlConfigEgressFifoIdx = ($FifoIdx)]/EthCtrlConfigEgressFifoPriorityAssignment/*)"!][!//
          [!ELSE!][!//
            [!VAR "NewPriority" ="num:i(0)"!][!//
          [!ENDIF!][!//
          [!IF "$RetVal = num:i(1)"!][!//
            [!VAR "CBSCount" = "num:i($CBSCount) + num:i(1)"!][!//
            [!VAR "CBSOrderString" = "concat($CBSOrderString,$FifoIdx,',',$NewPriority,',',$PredecessorOrder,',',$BufTotal,',',$BufLength,'@')"!][!//form the string FifoIdx,MaxPriority,PredecessorOrder,BufTotal,BufLength@.....
          [!ELSE!][!//
            [!VAR "NonCBSOrderString" = "concat($NonCBSOrderString,$FifoIdx,',',$NewPriority,',',$PredecessorOrder,',',$BufTotal,',',$BufLength,'@')"!][!//form the string FifoIdx,MaxPriority,PredecessorOrder,BufTotal,BufLength@.....
          [!ENDIF!][!//
        [!ENDFOR!][!//
        [!CALL "Sorting","SortArray" = "$CBSOrderString","VItem" = "num:i(2)","VTotalNum" = "$CBSCount","VDrctn" = "num:i(1)"!][!//
        [!VAR "CBSOrderString" = "$SortArray"!][!//
        [!CALL "Sorting","SortArray" = "$NonCBSOrderString","VItem" = "num:i(2)","VTotalNum" = "$PredecessorMax - $CBSCount","VDrctn" = "num:i(1)"!][!//
        [!VAR "NonCBSOrderString" = "$SortArray"!][!//
        [!VAR "FifoOrderString" = "concat($NonCBSOrderString,$CBSOrderString)"!][!//
        [!FOR "Predecessor" = "num:i(0)" TO "num:i($PredecessorMax) - num:i(1)"!][!//
          [!VAR "StringElem" = "text:split($FifoOrderString,'@')[num:i($Predecessor+1)]"!][!//
          [!CALL "ReplaceValue","ReplaceArray" = "$StringElem","VPosition" = "num:i(3)","VReplaceVal" = "$Predecessor"!][!//
          [!VAR "FifoOrderString" = "text:replace($FifoOrderString,$StringElem,$ReplaceArray)"!][!//
        [!ENDFOR!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//    

[!ENDSELECT!][!//
/*Array to store index of the controller in the allocated core.*/
[!VAR "CurrentIdx" = "num:i(255)"!][!//
[!FOR "CoreId" = "num:i(0)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!][!//
    [!VAR "MaxControllersCore" = "num:i(0)"!][!//
    [!VAR "TempCoreId" = "concat('CORE',$CoreId)"!][!//
    [!IF "$CoreId = '0'"!][!//
      [!VAR "CoreUsedForEthChFlg" = "num:i($EthChannelMappedCore0)"!][!//
    [!ELSEIF "$CoreId = '1'"!][!//
      [!VAR "CoreUsedForEthChFlg" = "num:i($EthChannelMappedCore1)"!][!//
    [!ELSEIF "$CoreId = '2'"!][!//
      [!VAR "CoreUsedForEthChFlg" = "num:i($EthChannelMappedCore2)"!][!//
    [!ELSEIF "$CoreId = '3'"!][!//
      [!VAR "CoreUsedForEthChFlg" = "num:i($EthChannelMappedCore3)"!][!//
    [!ELSEIF "$CoreId = '4'"!][!//
      [!VAR "CoreUsedForEthChFlg" = "num:i($EthChannelMappedCore4)"!][!//
    [!ENDIF!][!//
    [!IF "num:i($CoreUsedForEthChFlg) != '0'"!][!//
/* Eth configuration informations which mapped to Core[!"$CoreId"!] */
/* #Violation: Eth_PBcfg_c_REF_2*/
#define ETH_START_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreId"!]_UNSPECIFIED
/* #Violation: Eth_PBcfg_c_REF_1*/
#include "Eth_MemMap.h"
      [!FOR "ControllerID" = "num:i(0)" TO "num:i($MaxControllers) - num:i(1)"!][!//
        [!VAR "MaxPriority" = "num:i(8)"!][!//
        [!VAR "PriorityIdx" = "num:i(255)"!][!//
        [!VAR "FifoIdx" = "num:i(0)"!][!//
        [!VAR "FifoIdxPrint" = "num:i(0)"!][!//
        [!VAR "FifoIdxNotSched" ="''"!][!//
        [!VAR "SchedulerString" ="''"!][!//
        [!VAR "EgressFifoConfigured" = "num:i(0)"!][!//
        [!VAR "Flag" = "num:i(0)"!][!//
        [!VAR "EgressFifoOrderString" ="''"!][!//
        [!VAR "CreditValue" ="num:i(0)"!][!//
        [!VAR "PortTxRate" ="num:i(0)"!][!//
        [!VAR "RemQueueSize" ="num:i(0)"!][!//
        [!VAR "IdleBandwidth" ="num:i(0)"!][!//
        [!VAR "TotalQueueSize" ="num:i(0)"!][!//
        [!IF "node:exists(EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]) = 'true'"!][!//
        [!SELECT "EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]"!][!//
          [!VAR "NodeName" = "node:name(.)"!][!//
          [!IF "num:i($CoreUsedForEthChFlg) != '0'"!][!//
            [!VAR "EgressFifoConfigured" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*))"!][!//
            [!IF "$EgressFifoConfigured > num:i(0)"!][!//
                [!VAR "RemQueueSize" = " num:i(ecu:get('Eth.MaxTxRam')) - num:i($TotalQueueSize)"!][!//
                [!VAR "RemQueueQuotient" = " num:i($RemQueueSize) div num:i(256)"!][!//
                [!VAR "RemQueueQuotient_1" = " num:i($RemQueueQuotient) div num:i($EgressFifoConfigured)"!][!//
                [!VAR "RemQueueMod" = " num:i($RemQueueQuotient) mod num:i($EgressFifoConfigured)"!][!//
                [!/* algorithm to calculate Egress Queue Size */!][!//
                [!VAR "BufTotArr" = "''"!][!//
                [!VAR "BufLenArr" = "''"!][!//
                [!VAR "InitArr" = "'1 1 1 1'"!][!//
                [!CALL "Sorting","SortArray" = "$FifoOrderString","VItem" = "num:i(2)","VTotalNum" = "$PredecessorMax","VDrctn" = "num:i(-1)"!][!//
                [!VAR "FifoOrderString" = "$SortArray"!][!//
                [!FOR "Predecessor" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
                  [!VAR "Split" = "text:split($FifoOrderString,'@')[num:i($Predecessor)]"!][!//
                  [!IF "node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerAlgorithm) = 'ETH_SCHEDULER_STRICT_PRIORITY'"!][!//
                    [!VAR "BufTotArr" = "concat($BufTotArr,text:split($Split,',')[num:i(3)],' ')"!][!//
                    [!VAR "BufLen" = "text:split($Split,',')[num:i(4)]"!][!//
                  [!ELSE!][!//
                    [!VAR "BufTotArr" = "concat($BufTotArr,text:split($Split,',')[num:i(4)],' ')"!][!//
                    [!VAR "BufLen" = "text:split($Split,',')[num:i(5)]"!][!//
                  [!ENDIF!][!//
                  [!IF "num:i($BufLen) mod 256 != 0"!][!//
                    [!VAR "VQuotient" = "num:i($BufLen) div 256"!][!//
                    [!VAR "BufLen" = "(num:i($VQuotient) + 1) * 256"!][!//
                  [!ENDIF!][!//
                  [!VAR "BufLen" = "num:i(num:i($BufLen) div 256)"!][!//
                  [!VAR "BufLenArr" = "concat($BufLenArr,$BufLen,' ')"!][!//
                [!ENDFOR!][!//
                [!VAR "EgQueueSize" = "num:i(num:i(ecu:get('Eth.MaxTxRam')) div 256)"!][!//
                [!VAR "NewInitArr" = "$InitArr"!][!//
                [!FOR "$VLoop" = "num:i(0)" TO "num:i($EgQueueSize)"!][!//
                  [!VAR "NewInitArr" = "''"!][!//
                  [!FOR "VLoop2" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
                    [!VAR "VBufTotArElem" = "text:split($BufTotArr,' ')[num:i($VLoop2)]"!][!//
                    [!VAR "VInitArrElem" = "text:split($InitArr,' ')[num:i($VLoop2)]"!][!//
                    [!IF "num:i($VBufTotArElem)-num:i($VInitArrElem) > num:i(0)"!][!//
                      [!VAR "VNewInitArrElem" =  "num:i($VInitArrElem) + num:i(1)"!][!//
                      [!VAR "NewInitArr" = "concat($NewInitArr,num:i($VNewInitArrElem),' ')"!][!//
                    [!ELSE!][!//
                      [!VAR "NewInitArr" = "concat($NewInitArr,num:i($VInitArrElem),' ')"!][!//
                    [!ENDIF!][!//
                  [!ENDFOR!][!//
                  [!VAR "MulRes" = "num:mul(text:split($BufLenArr),text:split($NewInitArr))"!][!//
                  [!VAR "MulRes" = "text:join(text:split($MulRes, ','), ' ')"!][!//
                  [!VAR "MulRes" = "substring-before(substring-after($MulRes, '['),']')"!][!//
                  [!CALL "SumElem","SumArray"="$MulRes","VNumElem"="num:i($PredecessorMax)","SumVal"="num:i(0)"!][!//
                  [!VAR "SumMulElem" = "$SumVal"!][!//
                  [!IF "(num:i($SumMulElem) = num:i($EgQueueSize))"!][!//
                    [!VAR "InitArr" = "$NewInitArr"!][!//
                    [!VAR "FinalAlloc" = "$MulRes"!][!//
                    [!BREAK!][!//
                  [!ELSEIF "(num:i($SumMulElem) > num:i($EgQueueSize))"!][!//
                    [!VAR "MulRes" = "num:mul(text:split($BufLenArr),text:split($InitArr))"!][!//
                    [!VAR "MulRes" = "text:join(text:split($MulRes, ','), ' ')"!][!//
                    [!VAR "MulRes" = "substring-before(substring-after($MulRes, '['),']')"!][!//
                    [!VAR "FinalAlloc" = "$MulRes"!][!//
                    [!FOR "VLoop3" = "num:i(1)" TO "num:i(2)"!][!//
                      [!FOR "Predecessor" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
                        [!VAR "VInitArrGetElem" = "num:i(text:split($FinalAlloc,' ')[num:i($Predecessor)])"!][!//
                        [!VAR "VInitArrGetElem" = "num:i($VInitArrGetElem + (num:i(1)))"!][!//
                        [!VAR "FinalAlloc" = "concat(substring-before($FinalAlloc, text:split($FinalAlloc,' ')[num:i($Predecessor)]),$VInitArrGetElem,substring-after($FinalAlloc, text:split($FinalAlloc,' ')[num:i($Predecessor)]))"!][!//
                        [!CALL "SumElem","SumArray"="$FinalAlloc","VNumElem"="num:i($PredecessorMax)","SumVal"="num:i(0)"!][!//
                        [!IF "$SumVal = num:i($EgQueueSize)"!][!//
                          [!BREAK!][!//
                        [!ENDIF!][!//
                      [!ENDFOR!][!//
                      [!IF "$SumVal = num:i($EgQueueSize)"!][!//
                        [!BREAK!][!//
                      [!ENDIF!][!//
                    [!ENDFOR!][!//
                    [!BREAK!][!//
                  [!ELSEIF "(contains($InitArr, $BufTotArr))"!][!//
                    [!VAR "MulRes" = "num:mul(text:split($BufLenArr),text:split($InitArr))"!][!//
                    [!VAR "MulRes" = "text:join(text:split($MulRes, ','), ' ')"!][!//
                    [!VAR "MulRes" = "substring-before(substring-after($MulRes, '['),']')"!][!//
                    [!CALL "SumElem","SumArray"="$MulRes","VNumElem"="num:i($PredecessorMax)","SumVal"="num:i(0)"!][!//
                    [!VAR "VInitArrFirstElem" = "num:i(text:split($MulRes,' ')[num:i(1)])"!][!//
                    [!VAR "VInitArrFirstElem" = "num:i($VInitArrFirstElem + (num:i($EgQueueSize)-num:i($SumVal)))"!][!//
                    [!VAR "FinalAlloc" = "concat($VInitArrFirstElem,substring-after($MulRes, text:split($MulRes,' ')[num:i(1)]))"!][!//
                    [!BREAK!][!//
                  [!ELSE!][!//
                    [!VAR "InitArr" = "$NewInitArr"!]
                  [!ENDIF!][!//
                [!ENDFOR!][!//
                /* #Violation: Eth_PBcfg_c_REF_7 */
                static const Eth_TxChannelConfig Eth_TxChannelCtrl[!"$ControllerID"!][[!"num:i($PredecessorMax)"!]] =
                {
                  [!FOR "EgressFifo" = "num:i(0)" TO "num:i($EgressFifoConfigured) - num:i(1)"!][!//
                    [!NOCODE!][!//
                      [!VAR "EgressFifoIdx" = "num:i(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[EthCtrlConfigEgressFifoIdx = ($EgressFifo)]/EthCtrlConfigEgressFifoIdx)"!][!//check if EgressFifoIdx can be removed as this should be same as EgressFifo
                      [!IF "node:exists(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]) = 'true'"!][!//
                        [!VAR "PredecessorMax" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*))"!][!//
                        [!FOR "Predecessor" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
                          [!VAR "PredecessorString" = "text:split(node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef),'/')[last()]"!][!//
                          [!CALL "Eth_ShaperDet", "PredecessorRef" = "$PredecessorString", "RetVal" = "num:i(255)"!][!//
                            [!IF "$RetVal = num:i(1)"!][!//
                              [!VAR "SchedFifoIdx" = "node:value(node:ref(node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigShaperPredecessorFifoRef))/EthCtrlConfigEgressFifoIdx)"!][!//
                            [!ELSE!][!//
                              [!VAR "SchedFifoIdx" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoIdx))"!][!//
                            [!ENDIF!][!//
                            [!IF "$EgressFifoIdx = $SchedFifoIdx"!][!//
                              [!VAR "TempVal" = "num:i(0)"!][!//
                              [!BREAK!][!//
                            [!ELSE!][!//
                              [!VAR "TempVal" = "num:i(1)"!][!//
                            [!ENDIF!][!//
                        [!ENDFOR!][!//
                      [!ENDIF!][!//
                      [!/*************Warning for Fifo configured but not scheduled************/!][!//
                      [!IF "$TempVal = num:i(1)"!][!//
                        [!WARNING!][!//
                          Egress FIFO index [!"$EgressFifo"!] is configured but not scheduled for transmission. The transmission requests from FIFO index [!"$EgressFifo"!] will not be accepted.
                        [!ENDWARNING!][!//
                      [!ELSE!][!//

                      [!FOR "Count1" = "num:i(1)" TO "num:i($EgressFifoConfigured)"!][!//
                        [!VAR "SplitStr" = "text:split($FifoOrderString,'@')[num:i($Count1)]"!][!//
                        [!VAR "Index" = "text:split($SplitStr,',')[num:i(1)]"!][!//
                        [!IF "num:i($Index) = num:i($EgressFifo)"!][!//
                          [!VAR "EngressQueueSize" = "num:i(text:split($FinalAlloc,' ')[num:i($Count1)])*256"!][!//
                          [!BREAK!][!//
                        [!ENDIF!][!//
                      [!ENDFOR!][!//



                        [!/*****Check if the scheduled FIFO is configured with DMA weight in WSP/ WRR*****/!][!//
                        [!VAR "DmaChnlWeight" = "num:i(0)"!][!//
                        [!IF "node:value(EthCtrlConfigEgress/EthCtrlConfigDMAArbitration/*[1]/EthCtrlConfigDMAArbitrationAlgorithm) != 'ETH_DMA_ARBITRATION_FIXED_PRIORITY'"!][!//
                          [!FOR "Count1" = "num:i(1)" TO "num:i(count(EthCtrlConfigEgress/EthCtrlConfigDMAArbitration/*[1]/EthCtrlConfigDMAWeightAssignment/*))"!][!//
                            [!VAR "DMASchedFifoIdx" =  "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigDMAArbitration/*[1]/EthCtrlConfigDMAWeightAssignment/*[num:i($Count1)]/EthCtrlConfigDMAEgressFifoRef)/EthCtrlConfigEgressFifoIdx))"!][!//
                            [!IF "$EgressFifo = $DMASchedFifoIdx"!][!//
                              [!VAR "DmaChnlWeight" = "node:value(EthCtrlConfigEgress/EthCtrlConfigDMAArbitration/*[1]/EthCtrlConfigDMAWeightAssignment/*[num:i($Count1)]/EthCtrlConfigDMAArbitrationWeight)"!][!//
                              [!BREAK!][!//
                            [!ENDIF!][!//
                          [!ENDFOR!][!//
                          [!IF "$DmaChnlWeight = num:i(0)"!][!//
                            [!ERROR!][!//
                              88-000-20-ERROR: The Weight for Egress FIFO index [!"$EgressFifo"!] is not configured in the EthCtrlConfigDMAWeightAssignment container. Configuration of weight is mandatory in Weighted Strict Priority/ Weight Round Robin scheduling mechanism.
                            [!ENDERROR!][!//
                          [!ELSE!][!//
                            [!VAR "DmaChnlWeight" = "num:i(num:i($DmaChnlWeight) - num:i(1))"!][!//
                          [!ENDIF!][!//
                        [!ENDIF!][!//

                      [!ENDIF!][!//
                    [!ENDNOCODE!][!//
                    [!IF "$TempVal = num:i(0)"!][!//
                      [!INDENT "2"!][!//
                      {
                        [!INDENT "4"!][!//
                        ETH_DMA_BURSTLENGTH16,     /* Maximum burst length of the channel */
                        &Eth_Tx[!"$EgressFifoIdx"!]descr[0],              /* Pointer to TX descriptors RAM */
                        (uint8 *)&Eth_FIFO[!"$EgressFifoIdx"!]TxBuffer[0],              /* Ponter to Tx Buffer 1 */
                        /* DMA channel Tx interrupt enable */
                        {
                          [!INDENT "6"!][!//
                          [!IF "./EthCtrlEnableTxInterrupt = 'true'"!][!//
                          0x8001,/*NIE TIE*/
                          [!ELSE!][!//
                          0,
                          [!ENDIF!][!//
                          [!ENDINDENT!][!//
                        },
                        TRUE,/* Enable/Disable Tx Channel */
                        ETH_FIFO[!"$EgressFifoIdx"!]_CTRL0_TXBUF_COUNT,/* Number of tx buffers.*/    
                        ETH_FIFO[!"$EgressFifoIdx"!]_CTRL0_TXBUF_PER_SIZE,/* Configured tx buffer size after align*/
                        [!"num:i($Predecessor -1)"!]U,/* DMA channel id*/
                        [!"num:inttohex($DmaChnlWeight)"!]U,/* DMA channel Arbitration weight*/
                        [!ENDINDENT!][!//
                      },
                      [!ENDINDENT!][!//
                    [!ENDIF!][!//
                  [!ENDFOR!][!//
                };
                [!VAR "MaxValue" ="num:i(536870912)"!][!//
                [!VAR "TxQueueMode" ="num:i(0)"!][!//

                /* #Violation: Eth_PBcfg_c_REF_7 */
                static const Eth_TxQueueConfig Eth_TxFifoCtrl[!"$ControllerID"!][[!"num:i($PredecessorMax)"!]] =
                {
                  [!FOR "EgressFifo" = "num:i(0)" TO "num:i($EgressFifoConfigured) - num:i(1)"!][!//
                    [!NOCODE!][!//
                      [!VAR "EgressFifoIdx" = "num:i(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[EthCtrlConfigEgressFifoIdx = ($EgressFifo)]/EthCtrlConfigEgressFifoIdx)"!][!//check if EgressFifoIdx can be removed as this should be same as EgressFifo
                      [!IF "node:exists(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]) = 'true'"!][!//
                        [!VAR "PredecessorMax" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*))"!][!//
                        [!FOR "Predecessor" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
                          [!VAR "PredecessorString" = "text:split(node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef),'/')[last()]"!][!//
                          [!CALL "Eth_ShaperDet", "PredecessorRef" = "$PredecessorString", "RetVal" = "num:i(255)"!][!//                       
                            [!IF "$RetVal = num:i(1)"!][!//
                              [!VAR "SchedFifoIdx" = "node:value(node:ref(node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigShaperPredecessorFifoRef))/EthCtrlConfigEgressFifoIdx)"!][!//
                            [!ELSE!][!//
                              [!VAR "SchedFifoIdx" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoIdx))"!][!//
                            [!ENDIF!][!//
                            [!IF "$EgressFifoIdx = $SchedFifoIdx"!][!//
                              [!VAR "TempVal" = "num:i(0)"!][!//
                              [!BREAK!][!//
                            [!ELSE!][!//
                              [!VAR "TempVal" = "num:i(1)"!][!//
                            [!ENDIF!][!//
                        [!ENDFOR!][!//
                      [!ENDIF!][!//
                      [!/*************Warning for Fifo configured but not scheduled************/!][!//                    
                      [!IF "$TempVal = num:i(1)"!][!//
                        [!WARNING!][!//
                          Egress FIFO index [!"$EgressFifo"!] is configured but not scheduled for transmission. The transmission requests from FIFO index [!"$EgressFifo"!] will not be accepted.
                        [!ENDWARNING!][!//
                      [!ELSE!][!//
                        [!/*************Slope Calculation(IdleSlope, SendSlope, HiCredit, LoCredit)************/!][!//
                        [!IF "$RetVal = num:i(1)"!][!//
                          [!IF "$IsTha6104 = num:i(1)"!][!//
                              [!ERROR!]
                                88-000-23-ERROR: THA610X do not support AVB feature, Delete all item in EthCtrlConfigShaper list.
                              [!ENDERROR!]
                          [!ENDIF!][!//
                          [!IF "(./EthCtrlMacLayerSpeed = 'ETH_MAC_LAYER_SPEED_10M')"!][!//
                            [!VAR "PortTxRate" ="num:i(10000000)"!][!//
                          [!ELSEIF "(./EthCtrlMacLayerSpeed = 'ETH_MAC_LAYER_SPEED_100M')"!][!//
                            [!VAR "PortTxRate" ="num:i(100000000)"!][!//
                          [!ELSE!][!//
                            [!VAR "PortTxRate" ="num:i(1000000000)"!][!//
                          [!ENDIF!][!//
                          [!IF "./EthCtrlMacLayerType = 'ETH_MAC_LAYER_TYPE_XGMII' and ./EthCtrlMacLayerSubType = 'REDUCED'"!][!//
                            [!IF "(./EthCtrlMacLayerSpeed = 'ETH_MAC_LAYER_SPEED_10M') or (./EthCtrlMacLayerSpeed = 'ETH_MAC_LAYER_SPEED_100M')"!][!//
                              [!VAR "CreditValue" ="num:i(4)"!][!//
                            [!ELSE!][!//
                              [!VAR "CreditValue" ="num:i(8)"!][!//
                            [!ENDIF!][!//
                          [!ELSEIF "./EthCtrlMacLayerType = 'ETH_MAC_LAYER_TYPE_XMII' and ./EthCtrlMacLayerSubType = 'REDUCED'"!][!//
                            [!IF "(./EthCtrlMacLayerSpeed = 'ETH_MAC_LAYER_SPEED_10M') or (./EthCtrlMacLayerSpeed = 'ETH_MAC_LAYER_SPEED_100M')"!][!//
                              [!VAR "CreditValue" ="num:i(4)"!][!//
                            [!ENDIF!][!//
                          [!ELSE!][!//
                            [!VAR "CreditValue" ="num:i(4)"!][!//
                          [!ENDIF!][!//
                          [!FOR "Shaper" = "num:i(1)" TO "num:i($ShaperMax)"!][!//
                            [!VAR "ShaperFifoIdx" = "node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigShaper/*[num:i($Shaper)]/EthCtrlConfigShaperPredecessorFifoRef)/EthCtrlConfigEgressFifoIdx)"!][!//
                            [!IF "$ShaperFifoIdx = $SchedFifoIdx"!][!//
                              [!VAR "IdleSlopeValue" ="EthCtrlConfigEgress/EthCtrlConfigShaper/*[num:i($Shaper)]/EthCtrlConfigShaperIdleSlope/*[1]"!][!//               
                              [!IF "(./EthCtrlMacLayerSpeed = 'ETH_MAC_LAYER_SPEED_10M')"!][!//
                                [!IF "$IdleSlopeValue > num:i(10000000)"!][!//
                                  [!ERROR!][!//
                                    88-000-21-ERROR: Value of EthCtrlConfigShaperIdleSlope parameter is beyond the maximum range for the configured MAC layer type and speed.
                                  [!ENDERROR!][!//
                                [!ENDIF!][!//
                              [!ELSEIF "(./EthCtrlMacLayerSpeed = 'ETH_MAC_LAYER_SPEED_100M')"!][!//
                                [!IF "$IdleSlopeValue > num:i(100000000)"!][!//
                                  [!ERROR!][!//
                                    88-000-21-ERROR: Value of EthCtrlConfigShaperIdleSlope parameter is beyond the maximum range for the configured MAC layer type and speed.
                                  [!ENDERROR!][!//
                                [!ENDIF!][!//
                              [!ENDIF!][!//
                              [!VAR "HiCreditValue" ="EthCtrlConfigEgress/EthCtrlConfigShaper/*[num:i($Shaper)]/EthCtrlConfigShaperHiCredit"!][!//
                              [!VAR "LoCreditValue" ="EthCtrlConfigEgress/EthCtrlConfigShaper/*[num:i($Shaper)]/EthCtrlConfigShaperLoCredit"!][!//
                              [!VAR "IdleBandwidth" ="num:i($IdleSlopeValue) div num:i($PortTxRate)"!][!//
                              [!VAR "IdleSlopeCredit" ="$IdleBandwidth * $CreditValue"!][!//
                              [!VAR "SendSlopeCredit" ="$CreditValue - $IdleSlopeCredit"!][!//
                              [!VAR "IdleSlopeCredit" ="num:i(round($IdleSlopeCredit * num:i(1024)))"!][!//
                              [!VAR "SendSlopeCredit" ="num:i(round($SendSlopeCredit * num:i(1024)))"!][!//
                              [!VAR "HiCreditValue" ="$HiCreditValue * num:i(1024)"!][!//
                              [!IF "$LoCreditValue > num:i(0)"!][!//
                                [!VAR "LoCreditValue" ="($MaxValue - ($LoCreditValue * num:i(1024)))"!][!//
                              [!ENDIF!][!//
                              [!VAR "TxQueueMode" ="num:inttohex(1)"!][!//
                            [!ENDIF!][!//
                          [!ENDFOR!][!//
                        [!ELSE!][!//
                          [!IF "node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerAlgorithm) = 'ETH_SCHEDULER_STRICT_PRIORITY'"!][!//
                            [!VAR "IdleSlopeCredit" ="num:i(0)"!][!//
                          [!ELSE!][!//
                            [!FOR "Count1" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
                              [!VAR "SplitStr" = "text:split($FifoOrderString,'@')[num:i($Count1)]"!][!//
                              [!VAR "Index" = "text:split($SplitStr,',')[num:i(1)]"!][!//
                              [!IF "num:i($Index) = num:i($EgressFifo)"!][!//
                                [!VAR "IdleSlopeCredit" = "num:i(text:split($SplitStr,',')[num:i(3)])"!][!//
                                [!BREAK!][!//
                              [!ENDIF!][!//
                            [!ENDFOR!][!//
                          [!ENDIF!][!//
                          [!VAR "SendSlopeCredit" ="num:i(0)"!][!//
                          [!VAR "HiCreditValue" ="num:i(0)"!][!//
                          [!VAR "LoCreditValue" ="num:i(0)"!][!//
                          [!VAR "TxQueueMode" ="num:inttohex(2)"!][!//                            
                        [!ENDIF!][!//
         
                      [!ENDIF!][!//
                    [!ENDNOCODE!][!//
                    [!IF "$TempVal = num:i(0)"!][!//
                      [!INDENT "2"!][!//
                      {
                        [!INDENT "4"!][!//
                        TRUE, /* Transmit store and forward enable/disable */
                        ETH_TXQUEUE_SIZE_[!"num:i($EngressQueueSize)"!]B, /* Tx Queue size */
                        ETH_TXQUEUE_THRESHOLD_64B, /* Transmit Queue Threshold */
                        FALSE, /* Enable/Disable Tx Queue Underflow Interrupt */
                        TRUE, /*ENABLE QUEUE*/
                        /* #Violation: Eth_PBcfg_c_REF_3*/
                        (Eth_MtlTxqen)[!"$TxQueueMode"!]U, /* MTL_TxQ_Operation_Mode*/ 
                        (uint16)[!"num:inttohex($IdleSlopeCredit)"!]U,  /* The Idle slope credit for Queue or Configured weight for WRR algorithm*/
                        (uint32)[!"num:inttohex($HiCreditValue)"!]U, /* The high credit for qav Queue*/
                        (uint32)[!"num:inttohex($LoCreditValue)"!]U,   /* The low credit for qav Queue*/
                        (uint16)[!"num:inttohex($SendSlopeCredit)"!]U,  /* The send slope credit for qav Queue*/
                        (uint16)[!"num:i($Predecessor -1)"!]U, /* The queue id*/
                        [!ENDINDENT!][!//
                      },
                      [!ENDINDENT!][!//
                    [!ENDIF!][!//
                  [!ENDFOR!][!//
                };

            [!ELSE!][!//
            [!ENDIF!][!//
            
            [!VAR "ConfiguredFifoIngress" = "num:i(0)"!][!//
            [!VAR "InFifoOrderString" ="''"!][!//
            [!VAR "PriorityString" ="''"!][!//
            [!VAR "IngressFifoIdx" ="num:i(0)"!][!//
            [!VAR "PriorityCnt" = "num:i(0)"!][!//
            [!VAR "Flag" ="num:i(0)"!][!//
            [!VAR "ConfiguredFifoIngress" = "num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*))"!][!//
            [!INDENT "2"!][!//
            [!IF "$ConfiguredFifoIngress > num:i(0)"!][!//
              [!FOR "IngressFifo" = "num:i(0)" TO "num:i($ConfiguredFifoIngress) - num:i(1)"!][!//
                [!IF "node:exists(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]) = 'true'"!][!//
                  [!VAR "IngressFifoIdx" = "node:value(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoIdx)"!][!//
                  [!VAR "PriorityCnt" = "num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoPriorityAssignment/*))"!][!//
                  [!IF "$PriorityCnt > num:i(0)"!][!//
                    [!VAR "Priority" = "num:max(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifoIdx)]/EthCtrlConfigIngressFifoPriorityAssignment/*)"!][!//
                  [!ELSE!][!//
                    [!VAR "Priority" = "num:i(7)"!][!//
                  [!ENDIF!][!//
                  [!VAR "InBufTotal" = "node:value(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifoIdx)]/EthCtrlConfigIngressFifoBufTotal)"!][!//
                  [!VAR "InBufLength" = "node:value(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifoIdx)]/EthCtrlConfigIngressFifoBufLenByte)"!][!//
                  [!IF "(num:i($InBufTotal) = num:i(0)) or (num:i($InBufLength) = num:i(0))"!][!//
                    [!ERROR!][!//
                      88-000-24-ERROR:The ingress FIFO buffer length and buffer size should not be zero for successful reception of packets. If the ingress FIFO is not required for reception, delete the ingress container having FIFO index [!"num:i($IngressFifoIdx)"!] for controller [!"./EthCtrlIdx"!].
                    [!ENDERROR!][!//
                  [!ENDIF!][!//
                  [!IF "num:i($InBufLength) <= num:i(18)"!][!//
                    [!ERROR!][!//
                      88-000-25-ERROR:The ingress FIFO buffer length configured should be greater than 18 bytes as the length of 18 bytes are consumed by Header and FCFS fields of Ethernet packets. Modify accordingly the FIFO buffer length of ingress FIFO having FIFO index [!"num:i($IngressFifoIdx)"!] for controller [!"./EthCtrlIdx"!].
                    [!ENDERROR!][!//
                  [!ENDIF!][!//
                  [!VAR "InFifoOrderString" = "concat($InFifoOrderString,$IngressFifoIdx,',',$Priority,',',$InBufTotal,',',$InBufLength,'@')"!][!//
                [!ENDIF!][!//
              [!ENDFOR!][!//
            [!ELSE!][!//
            [!ENDIF!][!//
            [!ENDINDENT!][!//
          [!VAR "IngressFifoConfigured" = "num:i(0)"!][!//
          [!VAR "PriorityConfigured" = "num:i(0)"!][!//
          [!VAR "PriorityValue" = "num:i(0)"!][!//
          [!VAR "PriorityCount" = "num:i(0)"!][!//
          [!VAR "IngressFifoConfigured" = "num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*))"!][!//
          [!//Allocte the queue size
          [!IF "$IngressFifoConfigured > num:i(0)"!][!//
            [!NOCODE!][!//
            [!// The logic below this is used to allocated receive queue size for all configurated FIFO
            [!VAR "InFifoOrdSortedStr" = "$InFifoOrderString"!][!//
            [!//Sort(from high to low) the channel information string by priority(the second item in string)
            [!CALL "Sorting","SortArray" = "$InFifoOrdSortedStr","VItem" = "num:i(2)","VTotalNum" = "$IngressFifoConfigured","VDrctn" = "num:i(-1)"!][!//
            [!VAR "InFifoOrdSortedStr" = "$SortArray"!][!//
            [!VAR "InBufTotArr" = "''"!][!//
            [!//Number of ingress FIFO of one buffer divided by 256
            [!VAR "InBufLenArr" = "''"!][!//
            [!//To calculate the InBufLenArr variable
            [!FOR "vCount" = "num:i(1)" TO "num:i($IngressFifoConfigured)"!][!//
              [!VAR "InSplit" = "text:split($InFifoOrdSortedStr,'@')[num:i($vCount)]"!][!//
              [!VAR "InBufTotArr" = "concat($InBufTotArr,text:split($InSplit,',')[num:i(3)],' ')"!][!//
              [!VAR "InBufLen" = "text:split($InSplit,',')[num:i(4)]"!][!//
              [!IF "num:i($InBufLen) mod 256 != 0"!][!//
                [!VAR "VQuotient" = "num:i($InBufLen) div 256"!][!//
                [!VAR "InBufLen" = "(num:i($VQuotient) + 1) * 256"!][!//
              [!ENDIF!][!//
              [!VAR "InBufLen" = "num:i(num:i($InBufLen) div 256)"!][!//
              [!VAR "InBufLenArr" = "concat($InBufLenArr,$InBufLen,' ')"!][!//
            [!ENDFOR!][!//
            [!VAR "InQueueSize" = "num:i(num:i(ecu:get('Eth.MaxRxRam')) div 256)"!][!//
            [!VAR "InInitArr" = "'1 1 1 1'"!][!//
            [!//Now allocated the queue size(Every loop incrase one for every FIFO)
            [!FOR "$VLoop" = "num:i(0)" TO "num:i($InQueueSize)"!][!//
              [!VAR "NewInInitArr" = "''"!][!//
                [!//Incrase one size for all FIFO
                [!FOR "VLoop2" = "num:i(1)" TO "num:i($IngressFifoConfigured)"!][!//
                  [!VAR "VBufTotArElem" = "text:split($InBufTotArr,' ')[num:i($VLoop2)]"!][!//
                  [!VAR "VInitArrElem" = "text:split($InInitArr,' ')[num:i($VLoop2)]"!][!//
                  [!IF "num:i($VBufTotArElem)-num:i($VInitArrElem) > num:i(0)"!][!//
                    [!VAR "VNewInitArrElem" =  "num:i($VInitArrElem) + num:i(1)"!][!//
                    [!VAR "NewInInitArr" = "concat($NewInInitArr,num:i($VNewInitArrElem),' ')"!][!//
                  [!ELSE!][!//
                    [!VAR "NewInInitArr" = "concat($NewInInitArr,num:i($VInitArrElem),' ')"!][!//
                  [!ENDIF!][!//
                [!ENDFOR!][!//
                [!//Get the total size after the allocation
                [!VAR "MulRes" = "num:mul(text:split($InBufLenArr),text:split($NewInInitArr))"!][!//
                [!VAR "MulRes" = "text:join(text:split($MulRes, ','), ' ')"!][!//
                [!VAR "MulRes" = "substring-before(substring-after($MulRes, '['),']')"!][!//
                [!CALL "SumElem","SumArray"="$MulRes","VNumElem"="num:i($IngressFifoConfigured)","SumVal"="num:i(0)"!][!//
                [!VAR "SumMulElem" = "$SumVal"!][!//
                [!//If the total queue size(after the newest allocation) is equal to the hardware total queue size, allocation is completely
                [!IF "(num:i($SumMulElem) = num:i($InQueueSize))"!][!//
                  [!VAR "InInitArr" = "$NewInInitArr"!][!//
                  [!VAR "InFinalAlloc" = "$MulRes"!][!//
                  [!BREAK!][!//
                [!//If the total queue size(after the newest allocation) is larger than the hardware total queue size, then, the last allocation is appropriate
                [!ELSEIF "(num:i($SumMulElem) > num:i($InQueueSize))"!][!//
                  [!VAR "MulRes" = "num:mul(text:split($InBufLenArr),text:split($InInitArr))"!][!//
                  [!VAR "MulRes" = "text:join(text:split($MulRes, ','), ' ')"!][!//
                  [!VAR "MulRes" = "substring-before(substring-after($MulRes, '['),']')"!][!//
                  [!VAR "InFinalAlloc" = "$MulRes"!][!//
                  [!/*Since we used the last allocation method and entered this branch, there must still be space not allocated, and now we will start to allocate
                      FIFO by FIFO according to priority until the space is allocated*/!]
                  [!FOR "VLoop3" = "num:i(1)" TO "num:i($IngressFifoConfigured)"!][!//
                    [!VAR "VInitArrGetElem" = "num:i(text:split($InFinalAlloc,' ')[num:i($VLoop3)])"!][!//
                    [!VAR "VInitArrGetElem" = "num:i($VInitArrGetElem + (num:i(1)))"!][!//
                    [!VAR "InFinalAlloc" = "concat(substring-before($InFinalAlloc, text:split($InFinalAlloc,' ')[num:i($VLoop3)]),$VInitArrGetElem,substring-after($InFinalAlloc, text:split($InFinalAlloc,' ')[num:i($VLoop3)]))"!][!//
                    [!CALL "SumElem","SumArray"="$InFinalAlloc","VNumElem"="num:i($IngressFifoConfigured)","SumVal"="num:i(0)"!][!//
                    [!IF "$SumVal = num:i($InQueueSize)"!][!//
                      [!BREAK!][!//
                    [!ENDIF!][!//
                  [!ENDFOR!][!//
                [!/*The total size of the current buffer is still smaller than the hardware queue size, and the current allocation method is exactly the same as 
                  the current configuration. Then excute this allocation method.*/!]
                [!ELSEIF "(contains($InInitArr, $InBufTotArr))"!][!//
                  [!VAR "MulRes" = "num:mul(text:split($InBufLenArr),text:split($InInitArr))"!][!//
                  [!VAR "MulRes" = "text:join(text:split($MulRes, ','), ' ')"!][!//
                  [!VAR "MulRes" = "substring-before(substring-after($MulRes, '['),']')"!][!//
                  [!CALL "SumElem","SumArray"="$MulRes","VNumElem"="num:i($IngressFifoConfigured)","SumVal"="num:i(0)"!][!//
                  [!VAR "VInitArrFirstElem" = "num:i(text:split($MulRes,' ')[num:i(1)])"!][!//
                  [!//The remaining space is given to the FIFO with the highest priority
                  [!VAR "VInitArrFirstElem" = "num:i($VInitArrFirstElem + (num:i($InQueueSize)-num:i($SumVal)))"!][!//
                  [!VAR "InFinalAlloc" = "concat($VInitArrFirstElem,substring-after($MulRes, text:split($MulRes,' ')[num:i(1)]))"!][!//
                [!/*The total size of the current buffer is still smaller than the queue size of the hardware, and the new allocation method is accepted and the next
                   round of allocation is entered*/!]
                [!ELSE!][!//
                  [!VAR "InInitArr" = "$NewInInitArr"!]
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!ENDNOCODE!][!//
            /* Ingress FIFO configuration */
            /* #Violation: Eth_PBcfg_c_REF_7 */
              static const Eth_RxQueueConfig Eth_RxFifoCtrl[!"$ControllerID"!][[!"num:i($IngressFifoConfigured)"!]] =
            {
              [!FOR "IngressFifo" = "num:i(0)" TO "num:i($IngressFifoConfigured) - num:i(1)"!][!//
              [!NOCODE!][!//
                [!VAR "PriorityConfigured" = "num:i(0)"!][!//
                [!VAR "PriorityCount" = "num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoPriorityAssignment/*))"!][!//
                [!IF "$PriorityCount != num:i(0)"!][!//
                  [!FOR "Priority" = "num:i(1)" TO "num:i($PriorityCount)"!][!//
                    [!VAR "PriorityValue" = "EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoPriorityAssignment/*[num:i($Priority)]"!][!//
                    [!IF "$PriorityValue != ''"!][!//
                    [!VAR "PriorityConfigured" = "bit:or($PriorityConfigured,bit:shl(num:i(1),$PriorityValue))"!][!//
                    [!INDENT "2"!][!//
                    [!CODE!][!//
                    /*priority: [!"$PriorityValue"!]*/  
                    [!ENDCODE!][!//
                    [!ENDINDENT!][!//
                    [!ENDIF!][!//
                  [!ENDFOR!][!//
                  [!IF "$PriorityConfigured = num:i(0)"!][!//
                    [!VAR "PriorityConfigured" = "num:i(255)"!][!//
                  [!ENDIF!][!//
                [!ELSE!][!//
                  [!VAR "PriorityConfigured" = "num:i(255)"!][!//
                [!ENDIF!][!//
                [!FOR "Count1" = "num:i(1)" TO "num:i($IngressFifoConfigured)"!][!//
                  [!VAR "SplitStr" = "text:split($InFifoOrdSortedStr,'@')[num:i($Count1)]"!][!//
                  [!VAR "Index" = "text:split($SplitStr,',')[num:i(1)]"!][!//
                  [!IF "num:i($Index) = num:i($IngressFifo)"!][!//
                    [!VAR "IngressQueueSize" = "num:i(text:split($InFinalAlloc,' ')[num:i($Count1)])*256"!][!//
                    [!BREAK!][!//
                  [!ENDIF!][!//
                [!ENDFOR!][!//
                [!ENDNOCODE!][!//
                [!INDENT "2"!][!//
                {
                  [!INDENT "4"!][!//
                  TRUE,                       /* Receive Store and Forward Enable/Disable */
                  ETH_RXQUEUE_SIZE_[!"num:i($IngressQueueSize)"!]B,     /* Rx Queue size */
                  ETH_RXFLOWCONTROL_THRESHOLD_2KB,/*Threshold for activating flow control*/
                  ETH_RXFLOWCONTROL_THRESHOLD_1KB,/* RFD: Threshold for deactivating flow control */    
                  ETH_RXQUEUE_THRESHOLD_64B, /* Receive Queue Threshold */
                  ETH_DMA_CHANNEL0,          /* NOT USE! .Mapped DMA Channel of Rx Queue */
                  [!"$PriorityConfigured"!],                          /* tagged packets user priority, set 0 if single channel */
                  FALSE,                      /* Error Packet Forwarding Enable/Disable */
                  TRUE,                      /* Undersized Good Packet Forwarding Enable/Disable */
                  FALSE,                      /* Enable/Disable Rx Queue Overflow Interrupt */
                  TRUE,                      /* Enable/Disable Rx Queue */
                  FALSE,                     /* Enable/Disable flow control signal operation */
                  [!ENDINDENT!][!//
                }[!IF "$IngressFifo < num:i($IngressFifoConfigured) - num:i(1)"!],[!ENDIF!][!CR!]
                [!ENDINDENT!][!//
              [!ENDFOR!][!//
            };

            /* #Violation: Eth_PBcfg_c_REF_7 */
              static const Eth_RxChannelConfig Eth_RxChannelCtrl[!"$ControllerID"!][[!"num:i($IngressFifoConfigured)"!]] =
            {
              [!FOR "IngressFifo" = "num:i(0)" TO "num:i($IngressFifoConfigured) - num:i(1)"!][!//
              [!NOCODE!][!//
                [!VAR "IngressFifoIdx" = "num:i(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoIdx)"!][!//
                [!ENDNOCODE!][!//
                [!INDENT "2"!][!//
                {
                  [!INDENT "4"!][!//
                  ETH_DMA_BURSTLENGTH1,      /* Maximum burst length of the channel */
                  &Eth_Rx[!"$IngressFifoIdx"!]descr[0],              /* pointer to Rx descriptors RAM */
                  (uint8 *)&Eth_FIFO[!"$IngressFifoIdx"!]RxBuffer[0],               /* Ponter to Rx Buffer 1 */
                  /* DMA channel Rx interrupt enable */
                  {
                    [!INDENT "6"!][!//
                    [!IF "EthCtrlEnableRxInterrupt = 'true'"!][!//
                    0xC0C0,/* NIE,RIE,RUBE,AIE */
                    [!ELSE!][!//
                    0,
                    [!ENDIF!][!//
                    [!ENDINDENT!][!//
                  },
                  TRUE,/* Enable/Disable rx Channel */
                  /*Rx Ingress cfg */
                  ETH_FIFO[!"$IngressFifoIdx"!]_CTRL0_RXBUF_COUNT,/*NumOfRxBuffers*/
                  ETH_FIFO[!"$IngressFifoIdx"!]_CTRL0_RXBUF_PER_SIZE,/*RxBufferAlignSize*/
                  [!ENDINDENT!][!//
                }[!IF "$IngressFifo < num:i($IngressFifoConfigured) - num:i(1)"!],[!ENDIF!][!CR!]
                [!ENDINDENT!][!//
              [!ENDFOR!][!//
            };
            [!ENDIF!][!//
          [!ENDIF!][!//
        [!ENDSELECT!][!//
        [!ENDIF!][!//
      [!ENDFOR!][!//

static  const Eth_DemType EthDem[]=
{
      [!FOR "ControllerID" = "num:i(0)" TO "num:i($MaxControllers) - num:i(1)"!][!//
        [!IF "node:exists(EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]) = 'true'"!][!//
          [!SELECT "EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]"!][!//
            [!VAR "NodeName" = "node:name(.)"!][!//
            [!VAR "EthCtrlIdxTemp" = "./EthCtrlIdx"!][!//
            [!IF "num:i($CoreUsedForEthChFlg) != '0'"!][!//
              [!NOCODE!][!//
                /* Total Egress FIFO configured */
                [!VAR "EFifoConfigured" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*))"!][!//
                /* Egress FIFO Scheduled */
                [!VAR "EFifoScheduled" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*))"!][!//
                /* Total Ingress FIFO configured */
                [!VAR "IFifoConfigured" = "num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*))"!][!//

                /* DMA transmit arbitration algorithm */
                [!IF "node:value(EthCtrlConfigEgress/EthCtrlConfigDMAArbitration/*[1]/EthCtrlConfigDMAArbitrationAlgorithm) = 'ETH_DMA_ARBITRATION_FIXED_PRIORITY'"!][!//
                  [!VAR "PDMATxArbitAlgo" = "num:i(0)"!][!//
                [!ELSEIF "node:value(EthCtrlConfigEgress/EthCtrlConfigDMAArbitration/*[1]/EthCtrlConfigDMAArbitrationAlgorithm) = 'ETH_DMA_ARBITRATION_WEIGHTED_STRICT_PRIORITY'"!][!//
                  [!VAR "PDMATxArbitAlgo" = "num:i(1)"!][!//
                [!ELSE!][!//Weighted Round Robin
                   [!VAR "PDMATxArbitAlgo" = "num:i(2)"!][!//
                [!ENDIF!][!//

                /* MTL Scheduling algorithm */
                [!IF "node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerAlgorithm) = 'ETH_SCHEDULER_STRICT_PRIORITY'"!][!//
                  [!VAR "PSchedAlgo" = "num:i(3)"!][!//
                [!ELSE!][!//
                  [!VAR "PSchedAlgo" = "num:i(0)"!][!//
                [!ENDIF!][!//

                /* Untagged RX packets to queue routing */
                [!VAR "RefVal" = "node:refvalid(EthCtrlConfigIngress/EthCtrlConfigIngressUntaggedPktsFifoRef)"!][!//
                [!IF "$RefVal = 'false'"!][!//
                  [!VAR "UntaggedQueueNum" = "num:i(255)"!][!//
                [!ELSE!][!//
                  [!VAR "UntaggedQueueNum" =  "node:value(node:ref(EthCtrlConfigIngress/EthCtrlConfigIngressUntaggedPktsFifoRef)/EthCtrlConfigIngressFifoIdx)"!][!//
                [!ENDIF!][!//

              [!ENDNOCODE!][!//
              [!INDENT "2"!][!//
                [!INDENT "4"!][!//
                {
                /*DEM Id for Ethernet controller hardware test failure*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_ACCESS/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_ACCESS/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_ACCESS/*[1])))"!],
                [!ELSE!][!//
                  ETH_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                /*DEM Id for Ethernet controller Frames Lost Error*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_RX_FRAMES_LOST/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_RX_FRAMES_LOST/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_RX_FRAMES_LOST/*[1])))"!],
                [!ELSE!][!//
                  ETH_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                /*DEM Id for Ethernet controller Frames Alignment Error*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_ALIGNMENT/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_ALIGNMENT/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_ALIGNMENT/*[1])))"!],
                [!ELSE!][!//
                  ETH_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                /*DEM Id for Ethernet controller Frames CRC Error*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_CRC/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_CRC/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_CRC/*[1])))"!],
                [!ELSE!][!//
                  ETH_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                /*DEM Id for Ethernet controller  Undersize frame Error*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_UNDERSIZEFRAME/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_UNDERSIZEFRAME/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_UNDERSIZEFRAME/*[1])))"!],
                [!ELSE!][!//
                  ETH_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                /*DEM Id for Ethernet controller  Oversize frame Error*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_OVERSIZEFRAME/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_OVERSIZEFRAME/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_OVERSIZEFRAME/*[1])))"!],
                [!ELSE!][!//
                  ETH_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                /*DEM Id for Ethernet controller Single collision Error*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_SINGLECOLLISION/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_SINGLECOLLISION/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_SINGLECOLLISION/*[1])))"!],
                [!ELSE!][!//
                  ETH_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                /*DEM Id for Ethernet controller Multiple collision Error*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_MULTIPLECOLLISION/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_MULTIPLECOLLISION/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_MULTIPLECOLLISION/*[1])))"!],
                [!ELSE!][!//
                  ETH_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                /*DEM Id for Ethernet controller Late collision Error*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_LATECOLLISION/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_LATECOLLISION/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_LATECOLLISION/*[1])))"!],
                [!ELSE!][!//
                  ETH_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                }
                [!ENDINDENT!][!//
              [!ENDINDENT!][!//
            [!ENDIF!][!//
          [!ENDSELECT!][!//
        [!ENDIF!][!//
      [!ENDFOR!][!//
      
};

    [!ENDIF!][!//
  [!ENDFOR!][!//

[!ENDSELECT!][!//
[!ENDINDENT!][!//


  [!NOCODE!][!//
  [!MACRO "Eth_ShaperDet", "PredecessorRef" = "", "RetVal" = ""!][!//
    [!VAR "PredString" = "$PredecessorRef"!][!//
    [!VAR "LoopCount" = "count(EthCtrlConfigEgress/EthCtrlConfigShaper/*)"!][!//
    [!FOR "Count1" = "num:i(1)" TO "num:i($LoopCount)"!][!//
      [!VAR "StringSearch" = "node:name(EthCtrlConfigEgress/EthCtrlConfigShaper/*[num:i($Count1)])"!][!//
      [!IF "$StringSearch = $PredString"!][!//
        [!VAR "RetVal" = "num:i(1)"!][!//
        [!BREAK!][!//
      [!ENDIF!][!//
    [!ENDFOR!][!//
  [!ENDMACRO!][!//






  [!VAR "MaxControllers"= "ecu:get('Eth.MaxControllers')"!][!//

  [!ENDNOCODE!][!//
      [!FOR "ControllerID" = "num:i(0)" TO "num:i($MaxControllers) - num:i(1)"!][!//
        [!VAR "MaxPriority" = "num:i(8)"!][!//
        [!VAR "PriorityIdx" = "num:i(255)"!][!//
        [!VAR "FifoIdx" = "num:i(0)"!][!//
        [!VAR "FifoIdxPrint" = "num:i(0)"!][!//
        [!VAR "FifoIdxNotSched" ="''"!][!//
        [!VAR "SchedulerString" ="''"!][!//
        [!IF "node:exists(EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]) = 'true'"!][!//
        [!SELECT "EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]"!][!//
          [!VAR "NodeName" = "node:name(.)"!][!//

            [!VAR "EgressFifoConfigured" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*))"!][!//
            [!IF "$EgressFifoConfigured > num:i(0)"!][!//
/* Priority to FIFO index mapping */
            [!VAR "PredecessorMax" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*))"!][!//
/* #Violation: Eth_PBcfg_c_REF_7 */
static const uint8 EthPrioToFifoMap[!"$ControllerID"!][[!"num:i($MaxPriority)"!]] =
{
              [!INDENT "2"!][!//
              [!FOR "EgressFifo" = "num:i(0)" TO "num:i($EgressFifoConfigured) - num:i(1)"!][!//
                [!VAR "FifoIdx" = "num:i($EgressFifo)"!][!//
                [!VAR "TempVal" = "num:i(1)"!][!//
                [!IF "node:exists(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]) = 'true'"!][!//
                  [!FOR "Predecessor" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
                    [!VAR "SchedulerString" = "text:split(node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef),'/')[last()]"!][!//
                    [!CALL "Eth_ShaperDet", "PredecessorRef" = "$SchedulerString", "RetVal" = "num:i(255)"!][!//
                    [!IF "$RetVal = num:i(1)"!][!//
                      [!VAR "SchedFifoIdx" = "node:value(node:ref(node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigShaperPredecessorFifoRef))/EthCtrlConfigEgressFifoIdx)"!][!//
                    [!ELSE!][!//
                      [!VAR "SchedFifoIdx" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoIdx))"!][!//
                    [!ENDIF!][!//
                    [!IF "$FifoIdx = $SchedFifoIdx"!][!//
                      [!VAR "TempVal" = "num:i(0)"!][!//
                      [!BREAK!][!//
                    [!ENDIF!][!//
                  [!ENDFOR!][!//
                [!ENDIF!][!//
                [!IF "$TempVal = num:i(1)"!][!//
                  [!VAR "FifoIdxNotSched" = "concat($FifoIdxNotSched,$FifoIdx,',')"!][!//
                [!ENDIF!][!//
              [!ENDFOR!][!//
              [!VAR "MaxVal" = "count(text:split($FifoIdxNotSched,','))"!][!//
              [!FOR "Priority" = "num:i(0)" TO "num:i($MaxPriority) - num:i(1)"!][!//
                [!VAR "IdxFlag" = "num:i(0)"!][!//
                [!FOR "EgressFifo" = "num:i(1)" TO "num:i($EgressFifoConfigured)"!][!//
                  [!VAR "FifoIdx" = "num:i(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[num:i($EgressFifo)]/EthCtrlConfigEgressFifoIdx)"!][!//
                  [!IF "$EgressFifoConfigured > num:i(1)"!][!//
                    [!IF "node:exists(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[num:i($EgressFifo)]/EthCtrlConfigEgressFifoPriorityAssignment/*[1]) = 'true'"!][!//
                      [!VAR "FifoPriorityCount" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[num:i($EgressFifo)]/EthCtrlConfigEgressFifoPriorityAssignment/*))"!][!//
                      [!FOR "FifoPriority" = "num:i(1)" TO "num:i($FifoPriorityCount)"!][!//
                        [!VAR "EgressPriority" = "EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[num:i($EgressFifo)]/EthCtrlConfigEgressFifoPriorityAssignment/*[num:i($FifoPriority)]"!][!//
                        [!IF "$Priority = $EgressPriority"!][!//
                          [!VAR "IdxTest" = "text:contains(text:split($FifoIdxNotSched,','),string($FifoIdx))"!][!//
                          [!IF "$IdxTest = 'false'"!][!//
                            [!VAR "FifoIdxPrint" = "num:i($FifoIdx)"!][!//
                            [!FOR "FifoValue" = "num:i(1)" TO "num:i($MaxVal)"!][!//
                              [!IF "$FifoIdx > text:split($FifoIdxNotSched,',')[num:i($FifoValue)]"!][!//
                                [!VAR "FifoIdxPrint" = "num:i($FifoIdxPrint) - num:i(1)"!][!//
                              [!ENDIF!][!//
                            [!ENDFOR!][!//
                            [!"num:inttohex(($FifoIdxPrint))"!]U[!IF "$Priority < num:i($MaxPriority) - num:i(1)"!],[!ENDIF!][!CR!]
                            [!VAR "IdxFlag" = "num:i(1)"!][!//
                          [!ELSE!][!//
                            [!VAR "IdxFlag" = "num:i(0)"!][!//
                          [!ENDIF!][!//
                        [!ENDIF!][!//
                      [!ENDFOR!][!//
                    [!ELSE!][!//
                      [!ERROR!][!//
                        88-000-26-ERROR:Priority not assigned to Egress FIFO index [!"$FifoIdx"!]. If more than one FIFO is configured priority assignment for all the fifo is mandatory.
                      [!ENDERROR!][!//
                    [!ENDIF!][!//
                  [!ELSE!][!//
                    [!VAR "FifoPriorityCount" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[num:i($EgressFifo)]/EthCtrlConfigEgressFifoPriorityAssignment/*))"!][!//
                    [!IF "$FifoPriorityCount = num:i(0)"!][!//
                      [!"num:inttohex(($FifoIdx))"!]U[!IF "$Priority < num:i($MaxPriority) - num:i(1)"!],[!ENDIF!][!CR!]
                      [!VAR "IdxFlag" = "num:i(1)"!][!//
                    [!ELSE!][!//
                      [!FOR "FifoPriority" = "num:i(1)" TO "num:i($FifoPriorityCount)"!][!//
                        [!VAR "EgressPriority" = "EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[num:i($EgressFifo)]/EthCtrlConfigEgressFifoPriorityAssignment/*[num:i($FifoPriority)]"!][!//
                        [!IF "$Priority = $EgressPriority"!][!//
                          [!VAR "IdxTest" = "text:contains(text:split($FifoIdxNotSched,','),string($FifoIdx))"!][!//
                          [!IF "$IdxTest = 'false'"!][!//
                            [!VAR "FifoIdxPrint" = "num:i($FifoIdx)"!][!//
                            [!"num:inttohex(($FifoIdxPrint))"!]U[!IF "$Priority < num:i($MaxPriority) - num:i(1)"!],[!ENDIF!][!CR!]
                            [!VAR "IdxFlag" = "num:i(1)"!][!//
                          [!ELSE!][!//
                            [!VAR "IdxFlag" = "num:i(0)"!][!//
                          [!ENDIF!][!//
                        [!ENDIF!][!//
                      [!ENDFOR!][!//
                    [!ENDIF!][!//
                  [!ENDIF!][!//
                [!ENDFOR!][!//
                [!IF "$IdxFlag = num:i(0)"!][!//
                  [!"num:inttohex($PriorityIdx)"!]U[!IF "$Priority < num:i($MaxPriority) - num:i(1)"!],[!ENDIF!][!CR!]
                [!ENDIF!][!//
              [!ENDFOR!][!//
              [!ENDINDENT!][!//
};

/* Fifo to Egress Queue Mapping   DMA FIFO to queue id. */
            [!VAR "NewPriority" ="num:i(0)"!][!//
            [!VAR "Flag" ="num:i(0)"!][!//
            [!VAR "FifoOrderString" ="''"!][!//
            [!VAR "NonCBSOrderString" ="''"!][!//
            [!VAR "CBSOrderString" ="''"!][!//
            [!VAR "CBSCount" = "num:i(0)"!][!//
            [!VAR "PredecessorString" ="''"!][!//
            [!VAR "BufTotal" = "num:i(0)"!][!//
            [!VAR "BufLength" = "num:i(0)"!][!//
            [!IF "node:exists(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]) = 'true'"!][!//
              [!VAR "PredecessorMax" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*))"!][!//
            [!ENDIF!][!//
            [!VAR "PredecessorString" = "text:split(node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[1]/EthCtrlConfigSchedulerPredecessorRef),'/')[last()]"!][!//
/* #Violation: Eth_PBcfg_c_REF_7 */
static const uint8 EthTxFifoToChMap[!"$ControllerID"!][[!"num:i($PredecessorMax)"!]] =
{
              [!INDENT "2"!][!//
                [!IF "node:exists(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]) = 'true'"!][!//
                  [!IF "node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerAlgorithm) = 'ETH_SCHEDULER_STRICT_PRIORITY'"!][!//
                    [!FOR "Predecessor" = "num:i(0)" TO "num:i($PredecessorMax)-num:i(1)"!][!//
                      [!VAR "PredecessorOrder" = "num:i(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[EthCtrlConfigSchedulerPredecessorOrder = ($Predecessor)]/EthCtrlConfigSchedulerPredecessorOrder)"!][!//
                      [!VAR "OldPriority" = "$NewPriority"!][!//
                      [!VAR "PredecessorString" = "text:split(node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[EthCtrlConfigSchedulerPredecessorOrder = ($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef),'/')[last()]"!][!//
                      [!CALL "Eth_ShaperDet", "PredecessorRef" = "$PredecessorString", "RetVal" = "num:i(255)"!][!//
                      [!IF "$RetVal = num:i(1)"!][!//
                        [!VAR "FifoIdx" = "node:value(node:ref(node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[EthCtrlConfigSchedulerPredecessorOrder = ($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigShaperPredecessorFifoRef))/EthCtrlConfigEgressFifoIdx)"!][!//
                        [!VAR "BufTotal" = "node:value(node:ref(node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[EthCtrlConfigSchedulerPredecessorOrder = ($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigShaperPredecessorFifoRef))/EthCtrlConfigEgressFifoBufTotal)"!][!//
                        [!VAR "BufLength" = "node:value(node:ref(node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[EthCtrlConfigSchedulerPredecessorOrder = ($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigShaperPredecessorFifoRef))/EthCtrlConfigEgressFifoBufLenByte)"!][!//
                      [!ELSE!][!//
                        [!VAR "FifoIdx" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[EthCtrlConfigSchedulerPredecessorOrder = ($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoIdx))"!][!//
                        [!VAR "BufTotal" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[EthCtrlConfigSchedulerPredecessorOrder = ($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoBufTotal))"!][!//
                        [!VAR "BufLength" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[EthCtrlConfigSchedulerPredecessorOrder = ($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoBufLenByte))"!][!//
                      [!ENDIF!][!//
                      [!VAR "FifoOrderString" = "concat($FifoOrderString,$FifoIdx,',',$PredecessorOrder,',',$BufTotal,',',$BufLength,'@')"!][!//form the string FifoIdx,PredecessorOrder,BufTotal,BufLength@.....
                    [!ENDFOR!][!//
                  [!ELSE!][!//
                    [!FOR "Predecessor" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
                      [!VAR "PredecessorOrder" = "num:i(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorOrder)"!][!//
                      [!VAR "PredecessorString" = "text:split(node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef),'/')[last()]"!][!//
                      [!CALL "Eth_ShaperDet", "PredecessorRef" = "$PredecessorString", "RetVal" = "num:i(255)"!][!//
                      [!IF "$RetVal = num:i(1)"!][!//
                        [!VAR "FifoIdx" = "node:value(node:ref(node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigShaperPredecessorFifoRef))/EthCtrlConfigEgressFifoIdx)"!][!//
                        [!VAR "BufTotal" = "node:value(node:ref(node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigShaperPredecessorFifoRef))/EthCtrlConfigEgressFifoBufTotal)"!][!//
                        [!VAR "BufLength" = "node:value(node:ref(node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigShaperPredecessorFifoRef))/EthCtrlConfigEgressFifoBufLenByte)"!][!//
                      [!ELSE!][!//
                        [!VAR "FifoIdx" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoIdx))"!][!//
                        [!VAR "BufTotal" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoBufTotal))"!][!//
                        [!VAR "BufLength" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoBufLenByte))"!][!//
                      [!ENDIF!][!//
                      [!IF "node:exists(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[EthCtrlConfigEgressFifoIdx = ($FifoIdx)]/EthCtrlConfigEgressFifoPriorityAssignment/*) = 'true'"!][!//
                        [!VAR "NewPriority" = "num:max(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[EthCtrlConfigEgressFifoIdx = ($FifoIdx)]/EthCtrlConfigEgressFifoPriorityAssignment/*)"!][!//
                      [!ELSE!][!//
                        [!VAR "NewPriority" ="num:i(0)"!][!//
                      [!ENDIF!][!//
                      [!IF "$RetVal = num:i(1)"!][!//
                        [!VAR "CBSCount" = "num:i($CBSCount) + num:i(1)"!][!//
                        [!VAR "CBSOrderString" = "concat($CBSOrderString,$FifoIdx,',',$NewPriority,',',$PredecessorOrder,',',$BufTotal,',',$BufLength,'@')"!][!//form the string FifoIdx,MaxPriority,PredecessorOrder,BufTotal,BufLength@.....
                      [!ELSE!][!//
                        [!VAR "NonCBSOrderString" = "concat($NonCBSOrderString,$FifoIdx,',',$NewPriority,',',$PredecessorOrder,',',$BufTotal,',',$BufLength,'@')"!][!//form the string FifoIdx,MaxPriority,PredecessorOrder,BufTotal,BufLength@.....
                      [!ENDIF!][!//
                    [!ENDFOR!][!//
                    [!CALL "Sorting","SortArray" = "$CBSOrderString","VItem" = "num:i(2)","VTotalNum" = "$CBSCount","VDrctn" = "num:i(1)"!][!//
                    [!VAR "CBSOrderString" = "$SortArray"!][!//
                    [!CALL "Sorting","SortArray" = "$NonCBSOrderString","VItem" = "num:i(2)","VTotalNum" = "$PredecessorMax - $CBSCount","VDrctn" = "num:i(1)"!][!//
                    [!VAR "NonCBSOrderString" = "$SortArray"!][!//sort by priority
                    [!VAR "FifoOrderString" = "concat($NonCBSOrderString,$CBSOrderString)"!][!//Replace the skip-sorted order of priorities 0, 3, 5 with a sequential order of 0, 1, 2
                    [!FOR "Predecessor" = "num:i(0)" TO "num:i($PredecessorMax) - num:i(1)"!][!//
                      [!VAR "StringElem" = "text:split($FifoOrderString,'@')[num:i($Predecessor+1)]"!][!//
                      [!CALL "ReplaceValue","ReplaceArray" = "$StringElem","VPosition" = "num:i(3)","VReplaceVal" = "$Predecessor"!][!//
                      [!VAR "FifoOrderString" = "text:replace($FifoOrderString,$StringElem,$ReplaceArray)"!][!//
                    [!ENDFOR!][!//
                  [!ENDIF!][!//
                [!ENDIF!][!//
                [!VAR "MapIdx" = "num:i(0)"!][!//
                [!VAR "ChnlMapStr" = "''"!][!//
                [!FOR "Count" = "num:i(1)" TO "num:i(4)"!][!//
                  [!FOR "Count1" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
                    [!VAR "Split" = "text:split($FifoOrderString,'@')[num:i($Count1)]"!][!//
                    [!VAR "Index" = "text:split($Split,',')[num:i(1)]"!][!//
                    [!VAR "PredOrder" = "text:split($Split,',')[num:i(2)]"!][!//
                    [!IF "num:i($Index) = num:i($Count)-num:i(1)"!][!///*Fifo index start with 0 ,1,2,3 base on fifo index, can get priorty from fifo idex*/
                      [!VAR "ChnlMapStr" = "concat($ChnlMapStr,$PredOrder,',',$MapIdx,'@')"!][!///* priority, 0,@ priority,1,@ */
                      [!VAR "MapIdx" ="num:i($MapIdx + num:i(1))"!][!//
                      [!VAR "Flag" ="$Flag + num:i(1)"!][!//
                      [!"num:i($PredOrder)"!]U[!IF "$Flag < num:i($PredecessorMax)"!],[!ENDIF!][!CR!]
                      [!BREAK!][!//
                    [!ENDIF!][!//
                  [!ENDFOR!][!//
                [!ENDFOR!][!//
              [!ENDINDENT!][!//
};
            [!NOCODE!][!//
/* Channel to Egress FIFO Mapping  */
/* #Violation: Eth_PBcfg_c_REF_7 */
static const uint8 EthTxChToFifoMap[!"$ControllerID"!][4] =
{
              [!CALL "Sorting","SortArray" = "$ChnlMapStr","VItem" = "num:i(1)","VTotalNum" = "$PredecessorMax","VDrctn" = "num:i(1)"!][!//
              [!VAR "ChnlMapStr" = "$SortArray"!][!//
              [!INDENT "2"!][!//
                [!FOR "Count1" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
                  [!VAR "Split" = "text:split($ChnlMapStr,'@')[num:i($Count1)]"!][!//
                  [!VAR "ChnlIdx" = "text:split($Split,',')[num:i(1)]"!][!//
                  [!VAR "MapFifoIdx" = "text:split($Split,',')[num:i(2)]"!][!//
                  [!IF "num:i($ChnlIdx) = num:i($Count1)-num:i(1)"!][!//can get fifo index from priority.
                    [!"num:i($MapFifoIdx)"!]U[!IF "$Count1 < num:i(4)"!],[!ENDIF!][!CR!]
                  [!ENDIF!][!//
                [!ENDFOR!][!//
                [!IF "$PredecessorMax < num:i(4)"!][!//
                  [!FOR "Count1" = "num:i($Count1+num:i(1))" TO "num:i(4)"!][!//
                    [!"num:i(255)"!]U[!IF "$Count1 < num:i(4)"!],[!ENDIF!][!CR!]
                  [!ENDFOR!][!//
                [!ENDIF!][!//
              [!ENDINDENT!][!//
};
/* Egress FIFO configuration */
            [!VAR "EgressFifoConfigured" = "num:i(0)"!][!//
            [!VAR "Flag" = "num:i(0)"!][!//
            [!VAR "EgressFifoOrderString" ="''"!][!//
            [!VAR "CreditValue" ="num:i(0)"!][!//
            [!VAR "PortTxRate" ="num:i(0)"!][!//
            [!VAR "RemQueueSize" ="num:i(0)"!][!//
            [!VAR "IdleBandwidth" ="num:i(0)"!][!//
            [!VAR "TotalQueueSize" ="num:i(0)"!][!//
            [!VAR "EgressFifoConfigured" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*))"!][!//
            [!VAR "PredecessorString" = "text:split(node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[1]/EthCtrlConfigSchedulerPredecessorRef),'/')[last()]"!][!//
            [!CALL "Eth_ShaperDet", "PredecessorRef" = "$PredecessorString", "RetVal" = "num:i(255)"!][!//
              [!IF "$EgressFifoConfigured > num:i(0)"!][!//
                [!VAR "ShaperMax" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigShaper/*))"!][!//
                [!IF "node:exists(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]) = 'true'"!][!//
                  [!VAR "PredecessorMax" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*))"!][!//
                  [!FOR "Predecessor" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
                    [!VAR "PredecessorString" = "text:split(node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef),'/')[last()]"!][!//
                    [!CALL "Eth_ShaperDet", "PredecessorRef" = "$PredecessorString", "RetVal" = "num:i(255)"!][!//
                    [!IF "$RetVal = num:i(1)"!][!//
                      [!VAR "BufLength" = "node:value(node:ref(node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigShaperPredecessorFifoRef))/EthCtrlConfigEgressFifoBufLenByte)"!][!//
                      [!IF "num:i($BufLength) mod 256 != 0"!][!//
                        [!VAR "EgressQueueQuotient" = "num:i($BufLength) div 256"!][!//
                        [!VAR "BufLength" = "(num:i($EgressQueueQuotient) + 1) * 256"!][!//
                      [!ENDIF!][!//
                      [!VAR "TotalQueueSize" = "num:i($TotalQueueSize) + num:i($BufLength)"!][!//
                    [!ELSE!][!//
                      [!VAR "BufLength" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoBufLenByte))"!][!//
                      [!IF "num:i($BufLength) mod 256 != 0"!][!//
                        [!VAR "EgressQueueQuotient" = "num:i($BufLength) div 256"!][!//
                        [!VAR "BufLength" = "(num:i($EgressQueueQuotient) + 1) * 256"!][!//
                      [!ENDIF!][!//
                      [!VAR "TotalQueueSize" = "num:i($TotalQueueSize) + num:i($BufLength)"!][!//
                    [!ENDIF!][!//
                  [!ENDFOR!][!//
                  [!IF "num:i($TotalQueueSize) > num:i(ecu:get('Eth.MaxTxRam'))"!][!//
                    [!ERROR!][!//
                        88-000-19-ERROR:The sum of the individual buffer lengths (rounded off to 256 byte length) of Egress FIFOs is greater than [!"num:i(ecu:get('Eth.MaxTxRam'))"!] BYTES. Reduce to size of buffer lengths to fit within [!"num:i(ecu:get('Eth.MaxTxRam'))"!] BYTES size.
                    [!ENDERROR!][!//
                  [!ENDIF!][!//
                [!ENDIF!][!//

                 
              [!ENDIF!][!//
              [!ENDNOCODE!][!//
            [!ELSE!][!//
              [!NOCODE!][!//
              /* Priority to FIFO index mapping */
              /* #Violation: Eth_PBcfg_c_REF_7 */
                static const uint8 Eth_TxPrioFifoMapCtrl[!"$ControllerID"!][[!"num:i($MaxPriority)"!]] =
              {
                [!INDENT "2"!][!//
                [!FOR "Priority" = "num:i(0)" TO "num:i($MaxPriority) - num:i(1)"!][!//
                  [!"num:inttohex(num:i(255))"!]U[!IF "$Priority < num:i($MaxPriority) - num:i(1)"!],[!ENDIF!][!CR!]
                [!ENDFOR!][!//
                [!ENDINDENT!][!//
              };
              /* Channel to Egress FIFO Mapping */
              /* #Violation: Eth_PBcfg_c_REF_7 */
              static const uint8 Eth_TxChnlFifoMapCtrl[!"$ControllerID"!][4] =
              {
              [!INDENT "2"!][!//
                [!FOR "Count1" = "num:i(1)" TO "num:i(4)"!][!//
                  [!"num:i(255)"!]U[!IF "$Count1 < num:i(4)"!],[!ENDIF!][!CR!]
                [!ENDFOR!][!//
              [!ENDINDENT!][!//
              };
              [!ENDNOCODE!][!//
            [!ENDIF!][!//
            [!NOCODE!][!//
            /* Channel to Ingress FIFO Mapping */
            [!VAR "ConfiguredFifoIngress" = "num:i(0)"!][!//
            [!VAR "InFifoOrderString" ="''"!][!//
            [!VAR "PriorityString" ="''"!][!//
            [!VAR "IngressFifoIdx" ="num:i(0)"!][!//
            [!VAR "PriorityCnt" = "num:i(0)"!][!//
            [!VAR "Flag" ="num:i(0)"!][!//
            [!VAR "ConfiguredFifoIngress" = "num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*))"!][!//
              /* #Violation: Eth_PBcfg_c_REF_7 */
                static const uint8 EthRxChToFifoMap[!"$ControllerID"!][4] =
            {
            [!INDENT "2"!][!//
            [!IF "$ConfiguredFifoIngress > num:i(0)"!][!//
              [!FOR "IngressFifo" = "num:i(0)" TO "num:i($ConfiguredFifoIngress) - num:i(1)"!][!//
                [!IF "node:exists(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]) = 'true'"!][!//
                  [!VAR "IngressFifoIdx" = "node:value(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoIdx)"!][!//
                  [!VAR "PriorityCnt" = "num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoPriorityAssignment/*))"!][!//
                  [!IF "$PriorityCnt > num:i(0)"!][!//
                    [!VAR "Priority" = "num:max(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifoIdx)]/EthCtrlConfigIngressFifoPriorityAssignment/*)"!][!//
                  [!ELSE!][!//
                    [!VAR "Priority" = "num:i(7)"!][!//
                  [!ENDIF!][!//
                  [!VAR "InBufTotal" = "node:value(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifoIdx)]/EthCtrlConfigIngressFifoBufTotal)"!][!//
                  [!VAR "InBufLength" = "node:value(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifoIdx)]/EthCtrlConfigIngressFifoBufLenByte)"!][!//
                  [!VAR "InFifoOrderString" = "concat($InFifoOrderString,$IngressFifoIdx,',',$Priority,',',$InBufTotal,',',$InBufLength,'@')"!][!//
                [!ENDIF!][!//
              [!ENDFOR!][!//
              [!VAR "Split1" = "$InFifoOrderString"!][!//
              [!VAR "VTempReplceStr1" = "'String1'"!][!//
              [!VAR "VTempReplceStr2" = "'String2'"!][!//
              [!FOR "Count" = "num:i(1)" TO "num:i($ConfiguredFifoIngress)"!][!//
                [!FOR "Count1" = "num:i(1)" TO "num:i($ConfiguredFifoIngress)- num:i($Count)"!][!//
                  [!VAR "Split" = "text:split($Split1,'@')[num:i($Count1)]"!][!//
                  [!VAR "Temp2" = "text:split($Split1,'@')[num:i($Count1) + num:i(1)]"!][!//
                  [!VAR "Index" = "text:split($Split,',')[num:i(1)]"!][!//
                  [!VAR "Priority1" = "text:split($Split,',')[num:i(2)]"!][!//
                  [!VAR "Priority2" = "text:split($Temp2,',')[num:i(2)]"!][!//
                  [!IF "$Priority1 > $Priority2"!][!//
                    [!VAR "Split1" = "text:replace($Split1,$Split,$VTempReplceStr1)"!][!//
                    [!VAR "Split1" = "text:replace($Split1,$Temp2,$VTempReplceStr2)"!][!//
                    [!VAR "Split1" = "text:replace($Split1,$VTempReplceStr2,$Split)"!][!//
                    [!VAR "Split1" = "text:replace($Split1,$VTempReplceStr1,$Temp2)"!][!//
                  [!ENDIF!][!//
                [!ENDFOR!][!//
              [!ENDFOR!][!//
              [!FOR "Count" = "num:i(1)" TO "num:i($ConfiguredFifoIngress)"!][!//
                [!VAR "Split_2" = "text:split($Split1,'@')[num:i($Count)]"!][!//
                [!VAR "Index" = "text:split($Split_2,',')[num:i(1)]"!][!//
                [!VAR "Flag" ="$Flag + num:i(1)"!][!//
                [!"$Index"!]U[!IF "$Flag < num:i(4)"!],[!ENDIF!][!CR!]
              [!ENDFOR!][!//
              [!IF "$ConfiguredFifoIngress < num:i(4)"!][!//
                [!FOR "Count" = "num:i($Count+num:i(1))" TO "num:i(4)"!][!//
                  [!"num:i(255)"!]U[!IF "$Count < num:i(4)"!],[!ENDIF!][!CR!]
                [!ENDFOR!][!//
              [!ENDIF!][!//
            [!ELSE!][!//
              [!FOR "Count" = "num:i(1)" TO "num:i(4)"!][!//
                [!"num:i(255)"!]U[!IF "$Count < num:i(4)"!],[!ENDIF!][!CR!]
              [!ENDFOR!][!//
            [!ENDIF!][!//
            [!ENDINDENT!][!//
            };
            [!VAR "Flag" ="num:i(0)"!][!//
            [!ENDNOCODE!][!//
            [!IF "$ConfiguredFifoIngress > num:i(0)"!][!//
/* Fifo Ingress to Queue Mapping */
/* #Violation: Eth_PBcfg_c_REF_7 */
static const uint8 EthRxFifoToChMap[!"$ControllerID"!] [[!"num:i($ConfiguredFifoIngress)"!]] =
{
              [!INDENT "2"!][!//
              [!FOR "Count1" = "num:i(0)" TO "num:i($ConfiguredFifoIngress) - num:i(1)"!][!//
                [!FOR "Count" = "num:i(0)" TO "num:i($ConfiguredFifoIngress) - num:i(1)"!][!//
                  [!VAR "Split" = "text:split($Split1,'@')[num:i($Count) + num:i(1)]"!][!//
                  [!VAR "Index" = "text:split($Split,',')[num:i(1)]"!][!//
                  [!IF "$Index = $Count1"!][!//
                    [!VAR "Flag" ="$Flag + num:i(1)"!][!//
                    [!"$Count"!]U[!IF "$Flag < num:i($ConfiguredFifoIngress)"!],[!ENDIF!][!CR!]
                    [!BREAK!][!//
                  [!ENDIF!][!//
                [!ENDFOR!][!//
              [!ENDFOR!][!//
              [!ENDINDENT!][!//
};
          [!ENDIF!][!//
        [!ENDSELECT!][!//
        [!ENDIF!][!//
      [!ENDFOR!][!//

/* Container: EthConfigset */
[!FOR "CoreId" = "num:i(0)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!][!//
[!INDENT "0"!][!//
  [!IF "$CoreId = '0'"!][!//
    [!VAR "CoreUsedForEthChFlg" = "num:i($EthChannelMappedCore0)"!][!//
  [!ELSEIF "$CoreId = '1'"!][!//
    [!VAR "CoreUsedForEthChFlg" = "num:i($EthChannelMappedCore1)"!][!//
  [!ELSEIF "$CoreId = '2'"!][!//
    [!VAR "CoreUsedForEthChFlg" = "num:i($EthChannelMappedCore2)"!][!//
  [!ELSEIF "$CoreId = '3'"!][!//
    [!VAR "CoreUsedForEthChFlg" = "num:i($EthChannelMappedCore3)"!][!//
  [!ELSEIF "$CoreId = '4'"!][!//
    [!VAR "CoreUsedForEthChFlg" = "num:i($EthChannelMappedCore4)"!][!//
  [!ENDIF!][!//
  [!IF "num:i($CoreUsedForEthChFlg) != '0'"!][!//
[!LOOP "EthConfigSet/EthCtrlConfig/*"!][!//
[!VAR "EthCtrlIdxTemp" = "./EthCtrlIdx"!][!//
[!IF "node:exists(EthCtrlPhyAddress)"!][!//
[!VAR "EthMACAddress" = "text:replaceAll(node:value(./EthCtrlPhyAddress),'-',':')"!][!//
[!ENDIF!][!//
static const EthSdkCtrlConfigType Eth_CtrlConfigCore[!"$CoreId "!][ETH_MAX_CTRLS]=
{
[!INDENT "4"!][!//
  {
    [!INDENT "8"!][!//
    /* Pointer to ETH register base address */
    /* #Violation: Eth_PBcfg_c_REF_4*/
    ETH,
    /* External Phy Interface RMII Mode */
    [!IF "./EthCtrlMacLayerType = 'ETH_MAC_LAYER_TYPE_XGMII' and ./EthCtrlMacLayerSubType = 'REDUCED'"!][!//
    ETH_PHY_INTERFACE_RGMII,
    [!ELSEIF "./EthCtrlMacLayerType = 'ETH_MAC_LAYER_TYPE_XMII' and ./EthCtrlMacLayerSubType = 'REDUCED'"!][!//
    ETH_PHY_INTERFACE_RMII,
    [!ELSEIF "./EthCtrlMacLayerType = 'ETH_MAC_LAYER_TYPE_XMII' and ./EthCtrlMacLayerSubType = 'STANDARD'"!][!//
    ETH_PHY_INTERFACE_MII,
    [!ELSE!][!//
    ETH_PHY_INTERFACE_MII,
    [!WARNING!][!//
      Warning: Only MII, RMII,RGMII are supported.
    [!ENDWARNING!][!//
    [!ENDIF!][!//

    /* Set the Tx clock delay in RGMII mode */
    ETH_CLKDELAY_CELL_[!"./EthSkewTxClockDelay "!],
    /* Set the Rx clock delay in RGMII mode */
    ETH_CLKDELAY_CELL_[!"./EthSkewRxClockDelay "!],
    /* pins N.A */
    {
      NULL_PTR,
      NULL_PTR,
      NULL_PTR
    },
    {
      [!INDENT "12"!][!//
      /* Duplex Mode */
      ETH_[!"string(node:value(./EthOpMode))"!]_MODE,
      /* Ethernet line speed */
      [!IF "./EthCtrlMacLayerSpeed = 'ETH_MAC_LAYER_SPEED_100M'"!][!//
      ETH_LINESPEED_100M,
      [!ELSEIF "./EthCtrlMacLayerSpeed = 'ETH_MAC_LAYER_SPEED_1G'"!]
      ETH_LINESPEED_1000M,
      [!ELSE!]
      ETH_LINESPEED_10M,
      [!ENDIF!][!//
      /* Loopback mode enable/disable */
      [!IF "./EthCtrlEnableLoopback  = 'true'"!][!//
      ETH_LOOPBACK_ENABLE,
      [!ELSE!]
      ETH_LOOPBACK_DISABLE,
      [!ENDIF!]
      /* Maximum size of the ethernet packet */
      1518,
      /* MAC address for the ethernet */
      {
        [!INDENT "16"!][!//
        [!IF "node:exists(./EthCtrlPhyAddress)"!][!//
        /*MAC address (uint8 *)"[!"string(./EthCtrlPhyAddress)"!]";*/
        (uint8)0x[!"text:split($EthMACAddress, ':')[position() = 1]"!]U,
        (uint8)0x[!"text:split($EthMACAddress, ':')[position() = 2]"!]U,
        (uint8)0x[!"text:split($EthMACAddress, ':')[position() = 3]"!]U,
        (uint8)0x[!"text:split($EthMACAddress, ':')[position() = 4]"!]U,
        (uint8)0x[!"text:split($EthMACAddress, ':')[position() = 5]"!]U,
        (uint8)0x[!"text:split($EthMACAddress, ':')[position() = 6]"!]U
        [!ELSE!][!//
        (uint8)0x00U,
        (uint8)0x00U,
        (uint8)0x00U,
        (uint8)0x00U,
        (uint8)0x00U,
        (uint8)0x00U,
        [!ENDIF!][!//
        [!ENDINDENT!][!//
      },
      /* Enable/disable timestamp */
      [!NOCODE!]
        [!TRACE "string:concat('--- DEBUG EthGlobalTimeSupport ---')"!][!//
        [!TRACE "string:concat('Context Path: ', node:path(.))"!][!//
        [!TRACE "string:concat('Parent Path (...): ', node:path(..))"!][!//
        [!TRACE "string:concat('Grandparent Path (../..): ', node:path(../..))"!][!//
        [!TRACE "string:concat('Great-Grandparent Path (../../..): ', node:path(../../../.))"!][!//
        [!TRACE "string:concat('Path to EthGeneral (../../../EthGeneral) exists: ', node:exists(../../../EthGeneral))"!][!//
        [!TRACE "string:concat('Value of EthGlobalTimeSupport: ', node:value(../../../EthGeneral/EthGlobalTimeSupport))"!][!//
        [!TRACE "string:concat('--- END DEBUG ---')"!][!//
      [!ENDNOCODE!]
      [!IF "../../../EthGeneral/EthGlobalTimeSupport = 'true'"!][!//
      TRUE,
      [!ELSE!][!//
      FALSE,
      [!ENDIF!][!//
      /* Set receive all packet */
      TRUE,
      /* Set destination address inverse Filter */
      FALSE,
      /* Set VLAN Tag Filter */
      FALSE,
      /* Set enablePromiscuous */
      TRUE,
      /* Set enableMulticast */
      TRUE,
      /* Set enableBroadcast */ 
      TRUE,
      /* Set checksum offload */
      (boolean)(ETH_OFFLOAD_CHECKSUM),
      FALSE, /* Set CRC stripping for Type packets */
      FALSE, /* Set pad stripping for Type or ethernet packets */
      FALSE, /* Set CRC Checking for Received Packets */
      [!ENDINDENT!][!//
    },
/* MTL */
    {

      [!INDENT "12"!][!//
      /* Set ECC feature for MTL Tx FIFO memory */
      TRUE,
      /* Set ECC feature for MTL Rx FIFO memory */
      TRUE,
      /*not used*/
      {
        FALSE,                       /*Overriding MC-BC queue priority select,OMCBCQ */
        /* Broad And Multicast queue config */
        {
          ETH_MTL_QUEUE0,
          FALSE
        },   
        /* Unicast AVTP queue, AVCPQ */
        {
          ETH_MTL_QUEUE0,
          FALSE
        },
        /* #Violation: Eth_PBcfg_c_REF_3*/  
        (Eth_MtlQueue)[!"$UntaggedQueueNum"!]U,              /* Unicast PTP queue, PTPQ */
        /* #Violation: Eth_PBcfg_c_REF_3*/
        (Eth_MtlQueue)[!"$UntaggedQueueNum"!]U,              /* Remaining Unicast queue, UPQ */
        ETH_MTL_QUEUE0,                          /* All preemptable packet queue */
      },
      &Eth_TxFifoCtrl[!"$EthCtrlIdxTemp"!][0],/* Tx queue configurations of selected queues */
      &Eth_RxFifoCtrl[!"$EthCtrlIdxTemp"!][0],/* Rx queue configurations of selected queues */
      [!ENDINDENT!][!//
    },
/*DMA*/
    {
    [!INDENT "12"!][!//
    TRUE,                   /* Enable/Disable Address Aligned Beats */
    ETH_DMA_INTERRUPT_MODE2, /* Interrupt mode */
    /*txchannel*/
    &Eth_TxChannelCtrl0[0],
    /* rx Channels configurations of selected Channels */
    &Eth_RxChannelCtrl0[0],
    [!ENDINDENT!][!//
    },

        /* Number of Tx channels used in the controller */
        [!IF "$EFifoConfigured > num:i(0)"!][!//
        (uint8)[!"$EFifoScheduled"!]U,
        [!ELSE!][!//
        (uint8)[!"num:i(0)"!]U,
        [!ENDIF!][!//
        /* DMA transmit arbitration algorithm */
        (uint8)[!"$PDMATxArbitAlgo"!]U,
        /* MTL transmit scheduling algorithm */
        (uint8)[!"$PSchedAlgo"!]U,
        /* Number of Rx Channels used in the controller */
        (uint8)[!"$IFifoConfigured"!]U,
        /* Queue where the untagged Rx frames are routed */
        (uint8)[!"$UntaggedQueueNum"!]U,
        /* Transmit interrupt is enabled */
        ETH_ENA_TX_INT,
        /* Recive interrupt is enabled */        
        ETH_ENA_RX_INT,
        /*ETH frequency*/
        [!"$EthPeripheralBusFrequency"!]U,
        /*CR value for MII*/
        /* #Violation: Eth_PBcfg_c_REF_3*/
        (Eth_CsrClockRange)[!"$CrValue"!]U,
    [!ENDINDENT!][!//
  },
[!ENDINDENT!][!//
};
[!ENDLOOP!][!//
[!CALL "EthDemProcess"!][!//
[!IF "$EthDemEnabled = num:i(1)"!][!//
[!LOOP "EthConfigSet/EthCtrlConfig/*"!][!//
static const Eth_DemType Eth_DemCore[!"$CoreId "!][ETH_MAX_CTRLS]=
{
[!INDENT "4"!][!//
  {
    [!INDENT "8"!][!//
    /*DEM Id for Ethernet controller hardware test failure*/
    [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_ACCESS/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_ACCESS/*[1]) != ' ' )"!][!//
      DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_ACCESS/*[1])))"!],
    [!ELSE!][!//
      ETH_DISABLE_DEM_REPORT,
    [!ENDIF!][!//
    /*DEM Id for Ethernet controller Frames Lost Error*/
    [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_RX_FRAMES_LOST/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_RX_FRAMES_LOST/*[1]) != ' ' )"!][!//
      DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_RX_FRAMES_LOST/*[1])))"!],
    [!ELSE!][!//
      ETH_DISABLE_DEM_REPORT,
    [!ENDIF!][!//
    /*DEM Id for Ethernet controller Frames Alignment Error*/
    [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_ALIGNMENT/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_ALIGNMENT/*[1]) != ' ' )"!][!//
      DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_ALIGNMENT/*[1])))"!],
    [!ELSE!][!//
      ETH_DISABLE_DEM_REPORT,
    [!ENDIF!][!//
    /*DEM Id for Ethernet controller Frames CRC Error*/
    [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_CRC/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_CRC/*[1]) != ' ' )"!][!//
      DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_CRC/*[1])))"!],
    [!ELSE!][!//
      ETH_DISABLE_DEM_REPORT,
    [!ENDIF!][!//
    /*DEM Id for Ethernet controller  Undersize frame Error*/
    [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_UNDERSIZEFRAME/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_UNDERSIZEFRAME/*[1]) != ' ' )"!][!//
      DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_UNDERSIZEFRAME/*[1])))"!],
    [!ELSE!][!//
      ETH_DISABLE_DEM_REPORT,
    [!ENDIF!][!//
    /*DEM Id for Ethernet controller  Oversize frame Error*/
    [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_OVERSIZEFRAME/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_OVERSIZEFRAME/*[1]) != ' ' )"!][!//
      DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_OVERSIZEFRAME/*[1])))"!],
    [!ELSE!][!//
      ETH_DISABLE_DEM_REPORT,
    [!ENDIF!][!//
    /*DEM Id for Ethernet controller Single collision Error*/
    [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_SINGLECOLLISION/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_SINGLECOLLISION/*[1]) != ' ' )"!][!//
      DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_SINGLECOLLISION/*[1])))"!],
    [!ELSE!][!//
      ETH_DISABLE_DEM_REPORT,
    [!ENDIF!][!//
    /*DEM Id for Ethernet controller Multiple collision Error*/
    [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_MULTIPLECOLLISION/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_MULTIPLECOLLISION/*[1]) != ' ' )"!][!//
      DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_MULTIPLECOLLISION/*[1])))"!],
    [!ELSE!][!//
      ETH_DISABLE_DEM_REPORT,
    [!ENDIF!][!//
    /*DEM Id for Ethernet controller Late collision Error*/
    [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_LATECOLLISION/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_LATECOLLISION/*[1]) != ' ' )"!][!//
      DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_LATECOLLISION/*[1])))"!],
    [!ELSE!][!//
      ETH_DISABLE_DEM_REPORT,
    [!ENDIF!][!//
    [!ENDINDENT!][!//
  },
[!ENDINDENT!][!//
};
[!ENDLOOP!][!//
[!ENDIF!][!//

static const EthCtrlConfigType EthCtrlConfigCore[!"$CoreId "!][]=
{
[!SELECT "EthConfigSet"!][!//
  [!FOR "ControllerID" = "num:i(0)" TO "num:i(ecu:get('Eth.MaxControllers')) - num:i(1)"!][!//
    [!IF "node:exists(./EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]) = 'true'"!][!//
      [!SELECT "./EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]"!][!//
        [!VAR "NodeName" = "node:name(.)"!][!//
        [!VAR "EthCtrlIdxTemp" = "./EthCtrlIdx"!][!//
          [!NOCODE!][!//
            /* Untagged RX packets to queue routing */
            [!VAR "RefVal" = "node:refvalid(EthCtrlConfigIngress/EthCtrlConfigIngressUntaggedPktsFifoRef)"!][!//
            [!IF "$RefVal = 'false'"!][!//
              [!VAR "UntaggedQueueNum1" = "num:i(255)"!][!//
            [!ELSE!][!//
              [!VAR "UntaggedFifoIdx" =  "node:value(node:ref(EthCtrlConfigIngress/EthCtrlConfigIngressUntaggedPktsFifoRef)/EthCtrlConfigIngressFifoIdx)"!][!//
              [!VAR "IngressFifoConfigured" = "num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*))"!][!//
              [!VAR "UntaggedQueueNum1" = "num:i(0)"!][!//
              [!FOR "Count" = "num:i(0)" TO "num:i($IngressFifoConfigured) - num:i(1)"!][!//
                [!VAR "Split" = "text:split($Split1,'@')[num:i($Count) + num:i(1)]"!][!//
                [!VAR "Index" = "text:split($Split,',')[num:i(1)]"!][!//
                [!IF "$Index = $UntaggedFifoIdx"!][!//
                    [!IF "$Index != $UntaggedQueueNum"!][!//
                      [!ERROR!][!//
                        88-000-04-ERROR: Untagged Fifo Idx is not be used.
                      [!ENDERROR!][!//
                    [!ENDIF!][!//

                  [!BREAK!][!//
                [!ENDIF!][!//
              [!ENDFOR!][!//
            [!ENDIF!][!//

          [!ENDNOCODE!][!//
          [!INDENT "2"!][!//
          {
            [!INDENT "4"!][!//
            &Eth_CtrlConfigCore[!"$CoreId "!][0],
    /* Pointer to the mapping of Tx FIFO to Channels */
            [!IF "$EFifoConfigured > num:i(0)"!][!//
              &EthTxFifoToChMap[!"$EthCtrlIdxTemp "!][0],
            [!ELSE!][!//
              NULL_PTR,
            [!ENDIF!][!//
    /* Pointer to the mapping of configured Priority to FifoIdx */
            &EthPrioToFifoMap[!"$EthCtrlIdxTemp "!][0],

    /* Pointer to the mapping of Rx FIFO to Channels */
            [!IF "$IFifoConfigured > num:i(0)"!][!//
            &EthRxFifoToChMap[!"$EthCtrlIdxTemp "!][0],
            [!ELSE!][!//
              NULL_PTR,
            [!ENDIF!][!//
            /* Eth Controller Index */
            (uint8)[!"$EthCtrlIdxTemp"!]U,
            &EthDem[0],
            [!ENDINDENT!][!//
          },
          [!ENDINDENT!][!//
      [!ENDSELECT!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDSELECT!][!//

};

static const Eth_CoreConfigType Eth_CoreConfigCore[!"$CoreId "!][]=
{
[!INDENT "4"!][!//
  {
    [!INDENT "8"!][!//
        &EthCtrlConfigCore[!"$CoreId "!][0],
        ETH_MAX_CTRL_TO_CORE[!"$CoreId "!]
    [!ENDINDENT!][!//
  },
[!ENDINDENT!][!//
};

/* #Violation: Eth_PBcfg_c_REF_2*/
#define ETH_STOP_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreId"!]_UNSPECIFIED
/* #Violation: Eth_PBcfg_c_REF_1*/
#include "Eth_MemMap.h"
  [!ELSE!][!//
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDFOR!][!//

[!INDENT "0"!][!//
[!CODE!][!//
/* #Violation: Eth_PBcfg_c_REF_2*/
#define ETH_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Eth_PBcfg_c_REF_1*/
#include "Eth_MemMap.h"

/* 
This array is used for mapping Eth controller to the Core. 
Array index is Eth channel -> array member is index of Eth_ChannelConfigSetCorex[x=0~4]
*/
/* #Violation: Eth_PBcfg_c_REF_7 */
static const Eth_MappingType Eth_CtrlIdxToCoreMap[[!"num:i(count(EthConfigSet/EthCtrlConfig/*))"!]] =
{
[!ENDCODE!][!//
    [!INDENT "4"!][!//
    [!VAR "Channel2Core0Num" = "0"!][!//
    [!VAR "Channel2Core1Num" = "0"!][!//
    [!VAR "Channel2Core2Num" = "0"!][!//
    [!VAR "Channel2Core3Num" = "0"!][!//
    [!VAR "Channel2Core4Num" = "0"!][!//
    [!VAR "x" = "0"!][!//
    [!VAR "TotalChannelNum" = "num:i(count(EthConfigSet/EthCtrlConfig/*))"!][!//
    [!FOR "EthChannelIndex" = "0" TO "num:i($TotalChannelNum - 1)"!][!//
    [!LOOP "EthConfigSet/EthCtrlConfig/*"!][!//
    [!IF "EthCtrlIdx = $EthChannelIndex"!][!//
    [!CALL "CG_FindEthChannelMappedCoreId", "EthChId"="node:name(.)"!][!//
    [!IF "$EthchannelMappedCoreId = num:i(0)"!][!//
    [!VAR "Channel2CoreNumIndex" = "num:i($Channel2Core0Num)"!][!//
    [!VAR "Channel2Core0Num" = "$Channel2Core0Num + 1"!][!//
    [!ELSEIF "$EthchannelMappedCoreId = num:i(1)"!][!//
    [!VAR "Channel2CoreNumIndex" = "num:i($Channel2Core1Num)"!][!//
    [!VAR "Channel2Core1Num" = "$Channel2Core1Num + 1"!][!//
    [!ELSEIF "$EthchannelMappedCoreId = num:i(2)"!][!//
    [!VAR "Channel2CoreNumIndex" = "num:i($Channel2Core2Num)"!][!//
    [!VAR "Channel2Core2Num" = "$Channel2Core2Num + 1"!][!//
    [!ELSEIF "$EthchannelMappedCoreId = num:i(3)"!][!//
    [!VAR "Channel2CoreNumIndex" = "num:i($Channel2Core3Num)"!][!//
    [!VAR "Channel2Core3Num" = "$Channel2Core3Num + 1"!][!//
    [!ELSEIF "$EthchannelMappedCoreId = num:i(4)"!][!//
    [!VAR "Channel2CoreNumIndex" = "num:i($Channel2Core4Num)"!][!//
    [!VAR "Channel2Core4Num" = "$Channel2Core4Num + 1"!][!//
    [!ENDIF!][!//
[!CODE!][!//
    /* Eth Ch[!"$EthChannelIndex"!]*/
    {[!"num:i($Channel2CoreNumIndex)"!]U, MULTICOREID_CPU[!"$EthchannelMappedCoreId"!]}[!IF "$x != num:i($TotalChannelNum - 1)"!],[!ENDIF!]

[!ENDCODE!][!//
    [!VAR "x" = "$x+1"!][!//
    [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!ENDFOR!][!//
    [!ENDINDENT!][!//
[!CODE!][!//
};
[!ENDCODE!][!//
[!ENDINDENT!][!//

[!CODE!][!//
[!IF "variant:name() != ''"!][!//
const Eth_ConfigType Eth_ConfigSet_[!"variant:name()"!][ETH_MAX_CTRLS] =
[!ELSE!][!//
const Eth_ConfigType Eth_ConfigSet[ETH_MAX_CTRLS] =
[!ENDIF!][!//
{
    {
        {
            /* Pointer to Core Configuration structure */
    [!FOR "CoreId" = "num:i(0)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!][!//
      [!IF "$CoreId = num:i(0)"!][!//
          [!VAR "CoreUsedForEthHwUnitFlg" = "num:i($EthChannelMappedCore0)"!][!//
      [!ELSEIF "$CoreId = num:i(1)"!][!//
          [!VAR "CoreUsedForEthHwUnitFlg" = "num:i($EthChannelMappedCore1)"!][!//
      [!ELSEIF "$CoreId = num:i(2)"!][!//
          [!VAR "CoreUsedForEthHwUnitFlg" = "num:i($EthChannelMappedCore2)"!][!//
      [!ELSEIF "$CoreId = num:i(3)"!][!//
          [!VAR "CoreUsedForEthHwUnitFlg" = "num:i($EthChannelMappedCore3)"!][!//
      [!ENDIF!][!//
    [!IF "num:i($CoreUsedForEthHwUnitFlg) != num:i(0)"!][!//
            /* Eth configuration information of core[!"num:i($CoreId)"!] */
            &Eth_CoreConfigCore[!"num:i($CoreId)"!][0][!//
    [!ELSE!][!//
            /* No configuration information for core[!"num:i($CoreId)"!] */
            NULL_PTR[!//
    [!ENDIF!][!//
    [!IF "num:i($CoreId) < num:i(ecu:get('Mcu.NoOfCoreAvailable') - 1)"!][!//
,
    [!ENDIF!][!//
    [!ENDFOR!][!//

        },
        &Eth_CtrlIdxToCoreMap[0]
    }
};

/* #Violation: Eth_PBcfg_c_REF_2*/
#define ETH_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Eth_PBcfg_c_REF_1*/
#include "Eth_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

[!ENDCODE!][!//

