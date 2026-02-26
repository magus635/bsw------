/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Wdg_PBCfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : CPUWDT
*
*   brief                 : This file contains all configurations of Wdg Driver
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
*
*#Wdg_PBcfg_c_REF_1:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*#Wdg_PBcfg_c_REF_2:MISRAC2012-Rule-8.9;
* Justification:The value should be placed in the const data sections to reduce code complexity 
* and stack size.
*
*#Wdg_PBcfg_c_REF_3:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts 
* of the driver must be placed.
*
*/

[!NOCODE!][!//
[!INCLUDE "Wdg.m"!][!//
[!ENDNOCODE!][!//

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Wdg.h"
#include "Wdg_Cfg.h"

/***************************************************************************************************
*                         Function declaration
***************************************************************************************************/
[!NOCODE!][!//
[!SELECT "as:modconf('Wdg')[1]"!][!//
[!VAR "NotificationFuncName0" = "'NULL_PTR'"!][!//
[!VAR "NotificationFuncName1" = "'NULL_PTR'"!][!//
[!FOR "CoreID" = "1" TO "num:i(ecu:get('Resource.NumOfCores'))"!][!//
[!LOOP "WdgSettingsConfig/*"!][!//
    [!VAR "WDG_DeviceID" = "./WdgDeviceID"!][!//
    [!IF "$WDG_DeviceID = num:i(0)"!][!//
      [!IF "node:exists(./WdgNotification)"!][!//
        [!VAR "NotificationFuncName0" = "./WdgNotification"!][!//
        [!IF "$NotificationFuncName0 = 'NULL' or $NotificationFuncName0 = 'NULL_PTR' or $NotificationFuncName0 = '0'"!][!//
          [!VAR "NotificationFuncName0" = "'NULL_PTR'"!][!//
        [!ENDIF!][!//
      [!ELSE!][!//
        [!VAR "NotificationFuncName0" = "'NULL_PTR'"!][!//
      [!ENDIF!][!//
    [!ELSE!][!//
      [!IF "node:exists(./WdgNotification)"!][!//
        [!VAR "NotificationFuncName1" = "./WdgNotification"!][!//
        [!IF "$NotificationFuncName1 = 'NULL' or $NotificationFuncName1 = 'NULL_PTR' or $NotificationFuncName1 = '0'"!][!//
          [!VAR "NotificationFuncName1" = "'NULL_PTR'"!][!//
        [!ENDIF!][!//
      [!ELSE!][!//
        [!VAR "NotificationFuncName1" = "'NULL_PTR'"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDFOR!][!//
    [!IF "$NotificationFuncName0 != 'NULL_PTR'"!][!//
      [!IF "$NotificationFuncName1 != 'NULL_PTR'"!][!//
        [!IF "$NotificationFuncName0 = $NotificationFuncName1"!][!//
[!CODE!][!//
/* Notification function for WDG device0 and device1 */
extern void [!"$NotificationFuncName0"!](void);
[!ENDCODE!][!//
        [!ELSE!][!//
[!CODE!][!//
/* Notification function for WDG device0 */
extern void [!"$NotificationFuncName0"!](void);
/* Notification function for WDG device1 */
extern void [!"$NotificationFuncName1"!](void);
[!ENDCODE!][!//
        [!ENDIF!][!//
      [!ELSE!][!//
[!CODE!][!//
/* Notification function for WDG device0 and device1 */
extern void [!"$NotificationFuncName0"!](void);
[!ENDCODE!][!//
      [!ENDIF!][!//
    [!ELSE!][!//
      [!IF "$NotificationFuncName1 != 'NULL_PTR'"!][!//
[!CODE!][!//
/* Notification function for WDG device ID1 */
extern void [!"$NotificationFuncName1"!](void);
[!ENDCODE!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDNOCODE!][!//

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
[!SELECT "as:modconf('Wdg')[1]"!][!//
[!CALL "Wdg_GetWdgDeviceConfig"!][!//

[!CALL "Wdg_GetWdgCoreConfig"!][!//

/* #Violation: Wdg_PBcfg_c_REF_1 */
#define WDG_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Wdg_PBcfg_c_REF_3 */
#include "Wdg_MemMap.h"
[!CALL "Wdg_GetWdgConfig"!][!//
/* #Violation: Wdg_PBcfg_c_REF_1 */
#define WDG_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Wdg_PBcfg_c_REF_3 */
#include "Wdg_MemMap.h"

[!ENDSELECT!][!//
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
