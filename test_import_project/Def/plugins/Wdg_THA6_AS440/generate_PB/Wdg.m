/****************************************************************************************************
* 
****************************************************************************************************/
/****************************************************************************************************
*   FileName             : Wdg.m
*
*   Platform             : AUTOSAR
*
*   Peripheral           : Wdg
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*
*   Build Version        : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

[!/************************************************************
    Macro:Wdg_GetWdgDeviceConfig
    Macro to generate Wdg device config
****************************************************************/!]
[!MACRO "Wdg_GetWdgDeviceConfig"!][!//
[!NOCODE!][!//
[!IF "num:i(count(WdgSettingsConfig/*)) != num:i(0)"!][!// x
[!FOR "DeviceID" = "1" TO "num:i(ecu:get('Resource.NumOfCores'))"!][!//
[!LOOP "WdgSettingsConfig/*"!][!//
    [!VAR "WDG_DeviceID" = "./WdgDeviceID"!][!//
    [!IF "$WDG_DeviceID = num:i($DeviceID - num:i(1))"!][!//
[!VAR "WDG_CLOCK_TEMP_HZ" = "num:i(node:value(node:ref(../../WdgGeneral/WdgClockReference)/McuClockReferencePointFrequency))"!][!//
[!VAR "WDG_Slow_RefreshTime" = "./WdgSettingsSlow/WdgRefreshTime"!][!//
[!VAR "WDG_Fast_RefreshTime" = "./WdgSettingsFast/WdgRefreshTime"!][!//
[!VAR "Wdg_ResetTime" = "./WdgProcessTimeBeforeReset"!][!//
      [!IF "$Wdg_ResetTime < $WDG_Slow_RefreshTime"!][!//
        [!VAR "Wdg_ClockSelect" = "$WDG_Slow_RefreshTime"!][!//
        [!VAR "Wdg_ClockSelectName" = "'WDG Slow mode RefreshTime'"!][!//
      [!ELSE!][!//
        [!VAR "Wdg_ClockSelect" = "$Wdg_ResetTime"!][!//
        [!VAR "Wdg_ClockSelectName" = "'WdgProcessTimeBeforeReset'"!][!//
      [!ENDIF!][!//
      [!VAR "Wdg_DivCheck" = "$Wdg_ClockSelect * $WDG_CLOCK_TEMP_HZ div 131071"!][!// 17bit
      [!IF "$Wdg_DivCheck < 1"!][!//
        [!VAR "Wdg_DeviceClkDiv" = "'CLKDIV_THROUGH'"!][!//
      [!ELSE!][!//
        [!IF "$Wdg_DivCheck < 64"!][!//
          [!VAR "Wdg_DeviceClkDiv" = "'CLKDIV_64'"!][!//
        [!ELSE!][!//
          [!IF "$Wdg_DivCheck < 256"!][!//
            [!VAR "Wdg_DeviceClkDiv" = "'CLKDIV_256'"!][!//
          [!ELSE!][!//
            [!IF "$Wdg_DivCheck < 16384"!][!//
              [!VAR "Wdg_DeviceClkDiv" = "'CLKDIV_16384'"!][!//
            [!ELSE!][!//
              [!ERROR!][!//
                102-00-01-ERROR: Device ID[!"$WDG_DeviceID"!] [!"$Wdg_ClockSelectName"!] setting is unreasonable.[!//
              [!ENDERROR!][!//
            [!ENDIF!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!VAR "Wdg_DivCheck" = "$WDG_Fast_RefreshTime * $WDG_CLOCK_TEMP_HZ div 131071"!][!// 17bit
      [!IF "$Wdg_DivCheck >= 16384"!][!//
      [!ERROR!][!//
        102-00-02-ERROR: Device ID[!"$WDG_DeviceID"!] WDG_Fast_RefreshTime setting is unreasonable.[!//
      [!ENDERROR!][!//
      [!ENDIF!][!//

      [!IF "$Wdg_DeviceClkDiv = 'CLKDIV_THROUGH'"!][!//
        [!VAR "WDG_CLOCK_HZ" = "$WDG_CLOCK_TEMP_HZ"!][!//
      [!ELSE!][!//
        [!IF "$Wdg_DeviceClkDiv = 'CLKDIV_64'"!][!//
          [!VAR "WDG_CLOCK_HZ" = "$WDG_CLOCK_TEMP_HZ div 64"!][!//
        [!ELSE!][!//
          [!IF "$Wdg_DeviceClkDiv = 'CLKDIV_256'"!][!//
            [!VAR "WDG_CLOCK_HZ" = "$WDG_CLOCK_TEMP_HZ div 256"!][!//
          [!ELSE!][!//
            [!VAR "WDG_CLOCK_HZ" = "$WDG_CLOCK_TEMP_HZ div 16384"!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//

    [!VAR "WDG_Fast_RefreshTimeHigh" = "./WdgSettingsFast/WdgRefreshTime"!][!//
    [!VAR "WDG_Slow_RefreshTimeHigh" = "./WdgSettingsSlow/WdgRefreshTime"!][!//
    [!VAR "WDG_ClkDiv" = "$Wdg_DeviceClkDiv"!][!//
    [!VAR "WDG_DefaultMode" = "./WdgDefaultMode"!][!//
    [!VAR "WDG_First_InitialTimeout" = "./WdgDeviceInitialTimeout"!][!//
[!IF "$WDG_DefaultMode = 'WDGIF_SLOW_MODE'"!][!//2
    [!VAR "WDG_RefreshTimeHigh" = "num:i($WDG_Slow_RefreshTimeHigh * $WDG_CLOCK_HZ)"!][!//
[!ELSEIF "$WDG_DefaultMode = 'WDGIF_FAST_MODE'"!][!//2
    [!VAR "WDG_RefreshTimeHigh" = "num:i($WDG_Fast_RefreshTimeHigh * $WDG_CLOCK_HZ)"!][!//
[!ELSE!][!//
    [!VAR "WDG_RefreshTimeHigh" = "num:i(1)"!][!//
[!ENDIF!][!//2

    [!VAR "Wdg_ResetTime" = "./WdgProcessTimeBeforeReset"!][!//
    [!VAR "Wdg_ResetTime" = "num:i($Wdg_ResetTime * $WDG_CLOCK_HZ)"!][!//
[!CODE!][!//
/* #Violation: Wdg_PBcfg_c_REF_1 */
#define WDG_START_SEC_CONFIG_DATA_ASIL_D_CORE[!"$WDG_DeviceID"!]_UNSPECIFIED
/* #Violation: Wdg_PBcfg_c_REF_3 */
#include "Wdg_MemMap.h"
/* CpuWdt[!"$WDG_DeviceID"!] device configuration. */
static const Wdg_DeviceConfigType Wdg_Device[!"$WDG_DeviceID"!]ConfigSet =
{
    /* WDT password initial value */
    0xA30U,
    /* WDT low threshold value of first dog feeding interval */
    0U,
    /* WDT low threshold value of second dog feeding interval */
    0U,
    /* WDT high threshold value of first dog feeding interval */
    [!"$WDG_RefreshTimeHigh"!]U,
    /* WDT high threshold value of second dog feeding interval */
    [!"$Wdg_ResetTime"!]U,
    /* WDT error output mode of first interval */
    CPUWDT_OUTMODE_INTERRUPT,
    /* WDT password generation mode */
    CPUWDT_PWMODE_FIXED,
    /* WDT clock divisor coefficient */
    CPUWDT_[!"$WDG_ClkDiv"!]
};
/* #Violation: Wdg_PBcfg_c_REF_1 */
#define WDG_STOP_SEC_CONFIG_DATA_ASIL_D_CORE[!"$WDG_DeviceID"!]_UNSPECIFIED
/* #Violation: Wdg_PBcfg_c_REF_3 */
#include "Wdg_MemMap.h"

[!ENDCODE!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDFOR!][!//
[!CODE!][!//
[!ENDCODE!][!//
[!ENDIF!][!// x
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/************************************************************
    Macro:Wdg_GetWdgCoreConfig
    Macro to generate WDG config
****************************************************************/!]
[!MACRO "Wdg_GetWdgCoreConfig"!][!//
[!NOCODE!][!//
[!FOR "DeviceID" = "1" TO "num:i(ecu:get('Resource.NumOfCores'))"!][!//
[!LOOP "WdgSettingsConfig/*"!][!//
    [!VAR "WDG_DeviceID" = "./WdgDeviceID"!][!//
    [!IF "$WDG_DeviceID = num:i($DeviceID - num:i(1))"!][!//
      [!VAR "WDG_CLOCK_TEMP_HZ" = "num:i(node:value(node:ref(../../WdgGeneral/WdgClockReference)/McuClockReferencePointFrequency))"!][!//
      [!VAR "WDG_Slow_RefreshTime" = "./WdgSettingsSlow/WdgRefreshTime"!][!//
      [!VAR "WDG_Fast_RefreshTime" = "./WdgSettingsFast/WdgRefreshTime"!][!//
      [!VAR "Wdg_ResetTime" = "./WdgProcessTimeBeforeReset"!][!//

[!VAR "WDG_CLOCK_TEMP_HZ" = "num:i(node:value(node:ref(../../WdgGeneral/WdgClockReference)/McuClockReferencePointFrequency))"!][!//
[!VAR "WDG_Slow_RefreshTime" = "./WdgSettingsSlow/WdgRefreshTime"!][!//
[!VAR "WDG_Fast_RefreshTime" = "./WdgSettingsFast/WdgRefreshTime"!][!//
[!VAR "Wdg_ResetTime" = "./WdgProcessTimeBeforeReset"!][!//
      [!IF "$Wdg_ResetTime < $WDG_Slow_RefreshTime"!][!//
        [!VAR "Wdg_ClockSelect" = "$WDG_Slow_RefreshTime"!][!//
        [!VAR "Wdg_ClockSelectName" = "'WDG Slow mode RefreshTime'"!][!//
      [!ELSE!][!//
        [!VAR "Wdg_ClockSelect" = "$Wdg_ResetTime"!][!//
        [!VAR "Wdg_ClockSelectName" = "'WdgProcessTimeBeforeReset'"!][!//
      [!ENDIF!][!//
      [!VAR "Wdg_DivCheck" = "$Wdg_ClockSelect * $WDG_CLOCK_TEMP_HZ div 131071"!][!// 17bit
      [!IF "$Wdg_DivCheck < 1"!][!//
        [!VAR "Wdg_DeviceClkDiv" = "'CLKDIV_THROUGH'"!][!//
      [!ELSE!][!//
        [!IF "$Wdg_DivCheck < 64"!][!//
          [!VAR "Wdg_DeviceClkDiv" = "'CLKDIV_64'"!][!//
        [!ELSE!][!//
          [!IF "$Wdg_DivCheck < 256"!][!//
            [!VAR "Wdg_DeviceClkDiv" = "'CLKDIV_256'"!][!//
          [!ELSE!][!//
            [!IF "$Wdg_DivCheck < 16384"!][!//
              [!VAR "Wdg_DeviceClkDiv" = "'CLKDIV_16384'"!][!//
            [!ELSE!][!//
              [!ERROR!][!//
                102-00-01-ERROR: Device ID[!"$WDG_DeviceID"!] [!"$Wdg_ClockSelectName"!] setting is unreasonable.[!//
              [!ENDERROR!][!//
            [!ENDIF!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!IF "$Wdg_DeviceClkDiv = 'CLKDIV_THROUGH'"!][!//
        [!VAR "WDG_CLOCK_HZ" = "$WDG_CLOCK_TEMP_HZ"!][!//
      [!ELSE!][!//
        [!IF "$Wdg_DeviceClkDiv = 'CLKDIV_64'"!][!//
          [!VAR "WDG_CLOCK_HZ" = "$WDG_CLOCK_TEMP_HZ div 64"!][!//
        [!ELSE!][!//
          [!IF "$Wdg_DeviceClkDiv = 'CLKDIV_256'"!][!//
            [!VAR "WDG_CLOCK_HZ" = "$WDG_CLOCK_TEMP_HZ div 256"!][!//
          [!ELSE!][!//
            [!VAR "WDG_CLOCK_HZ" = "$WDG_CLOCK_TEMP_HZ div 16384"!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//

    [!VAR "WDG_DefaultMode" = "./WdgDefaultMode"!][!//
    [!VAR "WDG_InitialTimeout" = "./WdgDeviceInitialTimeout"!][!//
    [!VAR "WDG_MaxTimeout" = "./WdgDeviceMaxTimeout"!][!//
    [!VAR "WDG_DisableAllowed" = "./WdgDeviceDisableAllowed"!][!//
    [!IF "node:exists(./WdgNotification)"!][!//
      [!VAR "Wdg_Notification" = "./WdgNotification"!][!//
    [!ELSE!][!//
      [!VAR "Wdg_Notification" = "'NULL_PTR'"!][!//
    [!ENDIF!][!//
    [!VAR "WDG_General_DisableAllowed" = "../../WdgGeneral/WdgDisableAllowed"!][!//

    [!IF "num:i(4294967295) < num:i($WDG_InitialTimeout * $WDG_CLOCK_HZ)"!]
    [!ERROR!][!//
        102-00-03-ERROR: Device ID[!"$WDG_DeviceID"!] WDG_InitialTimeout exceeds the maximum value. MAX:[!"(4294967295 div $WDG_CLOCK_HZ)"!]s.[!//
    [!ENDERROR!][!//
    [!ENDIF!][!//
    [!VAR "Wdg_ResetTime" = "./WdgProcessTimeBeforeReset"!][!//

    [!IF "$Wdg_Notification = 'NULL' or $Wdg_Notification = 'NULL_PTR' or $Wdg_Notification = '0'"!][!//
        [!VAR "Wdg_Notification" = "'NULL_PTR'"!][!//
    [!ENDIF!][!//
[!CODE!][!//
/* #Violation: Wdg_PBcfg_c_REF_1 */
#define WDG_START_SEC_CONFIG_DATA_ASIL_D_CORE[!"$WDG_DeviceID"!]_UNSPECIFIED
/* #Violation: Wdg_PBcfg_c_REF_3 */
#include "Wdg_MemMap.h"
/* WDG Core[!"$WDG_DeviceID"!] configuration. */
static const Wdg_CoreConfigType Wdg_Core[!"$WDG_DeviceID"!]ConfigSet =
{
    /* DeviceConfigPtr */
    &Wdg_Device[!"$WDG_DeviceID"!]ConfigSet,
    /* Fast RefreshTime Counter [!"$WDG_Fast_RefreshTime"!]s */
    [!"num:i($WDG_Fast_RefreshTime * $WDG_CLOCK_HZ)"!]U,
    /* Slow RefreshTime Counter [!"$WDG_Slow_RefreshTime"!]s */
    [!"num:i($WDG_Slow_RefreshTime * $WDG_CLOCK_HZ)"!]U,
    /* WdgDeviceInitialTimeout(Counter) [!"$WDG_InitialTimeout"!]s */
    [!"num:i($WDG_InitialTimeout * $WDG_CLOCK_HZ)"!]U,
    /* WdgProcessTimeBeforeReset(Counter) [!"$Wdg_ResetTime"!]s */
    [!"num:i($Wdg_ResetTime * $WDG_CLOCK_HZ)"!]U,
    /* WdgDeviceMaxTimeout(ms) [!"$WDG_MaxTimeout"!]s */
    [!"num:i($WDG_MaxTimeout * 1000)"!]U,
    /* Wdg clock kHz */
    [!"num:i($WDG_CLOCK_HZ div 1000)"!]U,
    /* WdgNotification */
    [!"$Wdg_Notification"!],
    /* DefaultMode */
    [!"$WDG_DefaultMode"!],
[!ENDCODE!][!//
[!IF "$WDG_DisableAllowed = 'false' or $WDG_General_DisableAllowed = 'false'"!][!//
[!CODE!][!//
    /* DisableAllowed */
    (boolean)(FALSE)
[!ENDCODE!][!//
[!ELSE!][!//
[!CODE!][!//
    /* DisableAllowed */
    (boolean)(TRUE)
[!ENDCODE!][!//
[!ENDIF!][!//
[!CODE!][!//
};
/* #Violation: Wdg_PBcfg_c_REF_1 */
#define WDG_STOP_SEC_CONFIG_DATA_ASIL_D_CORE[!"$WDG_DeviceID"!]_UNSPECIFIED
/* #Violation: Wdg_PBcfg_c_REF_3 */
#include "Wdg_MemMap.h"

[!ENDCODE!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDFOR!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/************************************************************
    Macro:Wdg_GetWdgConfig
    Macro to generate WDG config
****************************************************************/!]
[!MACRO "Wdg_GetWdgConfig"!][!//
[!NOCODE!][!//
[!CODE!][!//
/* WDG module initialization routine for configuration. */
/* #Violation: Wdg_PBcfg_c_REF_2 */

[!IF "variant:name() != ''"!][!//
const Wdg_ConfigType Wdg_ConfigSet_[!"variant:name()"!][WDG_CONFIG_COUNT] =
[!ELSE!][!//
const Wdg_ConfigType Wdg_ConfigSet[WDG_CONFIG_COUNT] =
[!ENDIF!][!//
{
    {
        {
[!ENDCODE!][!//
[!FOR "DeviceID" = "1" TO "num:i(ecu:get('Resource.NumOfCores'))"!][!//
[!VAR "WDG_DeviceFindFlag" = "num:i(0)"!][!//
[!LOOP "WdgSettingsConfig/*"!][!//
    [!VAR "WDG_DeviceID" = "./WdgDeviceID"!][!//
    [!IF "$WDG_DeviceID = num:i($DeviceID - num:i(1))"!][!//
    [!VAR "WDG_DeviceFindFlag" = "num:i(1)"!][!// 1
[!CODE!][!//
            &Wdg_Core[!"$WDG_DeviceID"!]ConfigSet[!IF "$DeviceID != num:i(ecu:get('Resource.NumOfCores'))"!],[!ENDIF!]
[!ENDCODE!][!//
    [!ENDIF!][!// 1
[!ENDLOOP!][!//
    [!IF "$WDG_DeviceFindFlag = num:i(0)"!][!// 1
[!CODE!][!//
            NULL_PTR[!IF "$DeviceID != num:i(ecu:get('Resource.NumOfCores'))"!],[!ENDIF!]
[!ENDCODE!][!//
    [!ENDIF!][!// 1
[!ENDFOR!][!//
[!CODE!][!//
        }
    }
};
[!ENDCODE!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

