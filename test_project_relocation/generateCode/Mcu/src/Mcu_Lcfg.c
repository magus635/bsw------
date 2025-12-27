#include "Mcu.h"
#include "Mcu_Cfg.h"

/*===========================================================================
 *                          MCU Clock Configuration
 *===========================================================================*/



/* McuClockConfig_0 */
const Mcu_ClockSettingConfigType McuClockConfig_0_Settings = {
    .ClockSources = {
        
        
        {
            
            .Frequency = 160000000U,
            
            
            .Source = MCU_CLOCK_PLL
            
        }
        
        
    }
};



const Mcu_ConfigType Mcu_Config = {
    .ClockSettings = {
        
        
        &McuClockConfig_0_Settings
        
        
    }
};
