

/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Eth_Demo.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Geth
*
*   brief                 : This file contains all function declarations of Eth Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/
#ifndef ETH_DEMO_H_
#define ETH_DEMO_H_
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "ComStack_Types.h"
#include "Eth_GeneralTypes.h"
#include "Eth.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

#define ETH_CRC_FIELD_LENGTH             (4U)
#define ETH_MAC_ADD_LEN                  (6U)
#define ETH_FRAMEHEADER_LEN              (14U)

/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/
extern uint32 Src_IPaddress;
extern volatile uint32 ArpReply;
extern volatile uint8  PromiscuousCheck, StabilityTest;
extern uint8  Ret_MacAddr[ETH_MAC_ADD_LEN];
extern void   TransmitArpFrame(void);


extern volatile uint16 Test_EthTxConfirmCount[ETH_MAX_CTRLS];
extern volatile uint16 Test_EthTxTimeConfirmCount[ETH_MAX_CTRLS];
extern volatile uint16 Test_EthRxConfirmCount[ETH_MAX_CTRLS];
extern volatile uint16 Test_EthRxTimeConfirmCount[ETH_MAX_CTRLS];
/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/


/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/

extern void Eth_Demo(void);


#endif /* _ETH_DEMO_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/



