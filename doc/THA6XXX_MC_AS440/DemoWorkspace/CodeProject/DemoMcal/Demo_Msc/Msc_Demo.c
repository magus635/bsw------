/****************************************************************************************************
 *
 ****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Msc_Demo.c
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : Msc
 *
 *   brief                 : This file contains Demo application for Msc Driver
 *
 *   Autosar Version       : 4.4.0
 *
 *   Build Version         : Cortex-R52+/THA6xxx
 *
 *   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
 *
 ****************************************************************************************************/
#if defined(THA6_THA6104)
#include "Msc_Demo.h"
#include "Demo_Common.h"

void Msc_DemoEntry
(
    void
)
{
  DEBUG_PRINTF("\n/****** THA6104 Do not support *****/\n");
}

#else

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Msc_Demo.h"
#include "ComStack_Types.h"
#include "Msc_GeneralTypes.h"
#include "Msc.h"
#include "Msc_Irq.h"
#include "Intc.h"
#include "Dio.h"
#include "Demo_Common.h"
#include "Msc_Version.h"

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
#define L9788_UNLOCK_COMMAND      0x55F3
#define L9788_CONFIG2_COMMAND     0x80BD
#define L9788_DRIVEREN_COMMAND    0x998D
#define L9788_WDTDISABLE_COMMAND  0x99F3
#define L9788_READ11_COMMAND      0x7755
#define L9788_LEDEN_COMMAND       0x1800
#define L9788_LEDDISABLE_COMMAND  0x0000
#define L9788_SWRESET_COMMAND     0xB6BB
/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
static uint32 Msc_DataFrameCounter;
static uint32 Msc_TimeFrameCounter;
static uint32 Msc_CmdFrameCounter;
static uint32 Msc_RxFrameCounter;

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/
#define MSC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Msc_MemMap.h"

#define MSC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Msc_MemMap.h"

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
#define MSC_START_SEC_CODE_ASIL_D_GLOBAL
#include "Msc_MemMap.h"

/****************************************************************************************************
**                                Global Function                                                  **
****************************************************************************************************/
void Msc0_DataFrameNotification(void)
{
  Msc_DataFrameCounter++;
}

void Msc0_CmdFrameNotification(void)
{
  Msc_CmdFrameCounter++;
}

void Msc0_TimeFrameNotification(void)
{
  Msc_TimeFrameCounter++;
}

void Msc0_RxNotification(void)
{
  Msc_RxFrameCounter++;
}

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/****************************************************************************************************
 *   Function Name           : Msc_SendCmdL9788
 *
 *   Service ID              : None.
 *
 *   Description             : This function is the API that send a data command to L9788.
 *
 *   Parameters in           : Command: command to be transmitted.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous
 *
 *   Reentrancy              : Reentrant
 *
 *   Return value            : None
 *
 *   Preconditions           : Msc_Driver must be uninitialized.
 *
 ****************************************************************************************************/
FUNC(void, MSC_PRIVATE_CODE)
Msc_SendCmdL9788(uint32 Command)
{
  Msc_TxStatusType TxStatus;
  TxStatus = MSC_CMDFRMTX_NOTREADY;
  while (MSC_CMDFRMTX_READY != TxStatus)
  {
    TxStatus = Msc_GetTxStatus(0U, MSC_CMD_FRAME);
  }
  Command = Command >> 1;
  Msc_TxCmdFrame(0U, MSC_TARGET_EN0, Command);
}
/****************************************************************************************************
 *   Function Name           : Msc_sendDataL9788
 *
 *   Service ID              : None.
 *
 *   Description             : This function is the API that send a data frame to L9788.
 *
 *   Parameters in           : DataVal:The data to be transmitted.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous
 *
 *   Reentrancy              : Non-Reentrant
 *
 *   Return value            : None
 *
 *   Preconditions           : Msc_Driver must be uninitialized.
 *
 ****************************************************************************************************/
FUNC(void, MSC_PRIVATE_CODE)
Msc_SendDataL9788(uint32 DataVal)
{
  uint32 Temp = 0X00;
  Msc_TxStatusType TxStatus;
  TxStatus = MSC_DATAFRMTX_NOTREADY;
  while (MSC_DATAFRMTX_READY != TxStatus)
  {
    TxStatus = Msc_GetTxStatus(0U, MSC_DATA_FRAME);
  }
  Temp = ((DataVal >> 1) & 0xFFFF) | ((DataVal >> 17) & 0xFFFF);
  Msc_TxDataFrame(0U, MSC_TARGET_EN0, MSC_TARGET_EN0, Temp);
}

/****************************************************************************************************
 *   Function Name           : Msc_DemoEntry
 *
 *   Service ID              : None.
 *
 *   Description             : Msc demo application entry.
 *                             Select which core to use to run Msc Channel.
 *                             This APi shall be called by main core(Core 0).
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous
 *
 *   Reentrancy              : Non-Reentrant
 *
 *   Return value            : None
 *
 *   Preconditions           : None
 *
 ****************************************************************************************************/
/* Pin description:
 * MCU - L9788
 * P13.0 - FCLN
 * P13.1 - FCLP
 * P13.2 - SON
 * P13.3 - SOP
 * P14.3 - SDI2
 * P10.4 - EN0
 * */
void Msc_DemoEntry(void)
{
  Msc_RxStatus Status;
  uint8 DataRead;
  uint8 Cmd;
  uint8 Msc_Exit;
  Std_VersionInfoType Msc_ver;

  Msc_Exit = 0U;

  /* Initialize the Msc */
  Msc_Init(&Msc_ConfigSet[0]);
  /* Enable interrupt */
  Msc_EnableNotfication(0U);
  /* Select receive device */
  Msc_SelectRxDevice(0U, MSC_SDI_2);

  Msc_SendCmdL9788(L9788_UNLOCK_COMMAND);
  Msc_SendCmdL9788(L9788_CONFIG2_COMMAND);
  Msc_SendCmdL9788(L9788_DRIVEREN_COMMAND);
  Msc_SendCmdL9788(L9788_WDTDISABLE_COMMAND);

  DEBUG_PRINTF("\n/*********************************************************/\n");
  /* Print the Msc driver version information */
  Msc_GetVersionInfo(&Msc_ver);
  DEBUG_PRINTF("\n\n\n");
  DEBUG_PRINTF("\n/*********************************************************/");
  DEBUG_PRINTF("\n           Msc DRIVER DEMO MENU V%02d.%02d.%02d            \r\n",
               Msc_ver.sw_major_version, Msc_ver.sw_minor_version, Msc_ver.sw_patch_version);
  DEBUG_PRINTF("All demos are based on the L9788, you can connect the L9788 or\r\n");
  DEBUG_PRINTF("observe the phenomenon through an oscilloscope,The pin connections\r\n");
  DEBUG_PRINTF("are shown below\r\n\r\n");
  DEBUG_PRINTF("- P13.0:FCLN\r\n");
  DEBUG_PRINTF("- P13.1:FCLP\r\n");
  DEBUG_PRINTF("- P13.2:SON\r\n");
  DEBUG_PRINTF("- P13.3:SOP\r\n");
  DEBUG_PRINTF("- P14.3:SDI2\r\n");
  DEBUG_PRINTF("- P10.4:EN0\r\n");
  /* An infinite loop is used to let the user select a demo */
  while (0U == Msc_Exit)
  {
    Msc_DataFrameCounter = 0U;
    Msc_TimeFrameCounter = 0U;
    Msc_CmdFrameCounter = 0U;
    Msc_RxFrameCounter = 0U;

    DEBUG_PRINTF("\r\n---------------------------------------\r\n");
    DEBUG_PRINTF("Please select a demo to execute ");

    DEBUG_PRINTF("\n                                                         ");
    DEBUG_PRINTF("\n '1'. Send a Command Frame");
    DEBUG_PRINTF("\n '2'. Send data frame 0");
    DEBUG_PRINTF("\n '3'. Send data frame 1");
    DEBUG_PRINTF("\n '4'. Read Data in UD");
    DEBUG_PRINTF("\n 'X'. Exit and go back to main menu \n");
    DEBUG_PRINTF("\n  ENTER YOUR OPTION   : \r\n");

    /* Wait for the user to enter options of the core */
    Cmd = DEBUG_GETC();

    switch (Cmd)
    {
    case '1':
    {
      Msc_SendCmdL9788(L9788_READ11_COMMAND);
      DEBUG_PRINTF("\n - Command frame has been send!\r\n");
      break;
    }
    case '2':
    {
      Msc_SendDataL9788(L9788_LEDEN_COMMAND);
      DEBUG_PRINTF("\n - Data frame has been send!\r\n");
      break;
    }
    case '3':
    {
      Msc_SendDataL9788(L9788_LEDDISABLE_COMMAND);
      DEBUG_PRINTF("\n - Data frame has been send!\r\n");
      break;
    }
    case '4':
    {
      DataRead = 0U;
      Status = Msc_GetRxData(0U, MSC_UD2, &DataRead);
      if (MSC_RXSTATUS_PE == Status)
      {
        DEBUG_PRINTF("\r\n- UD2 received error data \r\n");
      }
      else if (MSC_RXSTATUS_RECEIVED == Status)
      {
        DEBUG_PRINTF("- UD2 received data:%d \r\n", (uint32)DataRead);
      }
      else
      {
        DEBUG_PRINTF("\r\n - No data received in UD2\r\n");
      }
      break;
    }
    case 'X':
    {
      Msc_Exit = 1U;
      Msc_DisableNotfication(0U);
      Msc_DeInit();
      break;
    }
    default:
    {
      DEBUG_PRINTF("\r\nIf you entered the wrong option, \
                    please enter the correct option\r\n");
      break;
    }
    }
  }
}

#define MSC_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Msc_MemMap.h"

#endif
