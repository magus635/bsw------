#include "Port.h"
#include "Port_Cfg.h"

/*===========================================================================
 *                          Port Pin Configuration
 *===========================================================================*/

const Port_ConfigType Port_Config = {
    .PinConfig = {
        
        
        {
            .PinId = 10,
            .PinMode = PORT_PIN_MODE_GPIO,
            .Direction = PORT_PIN_IN,
            .InitialMode = PORT_PIN_MODE_GPIO
        }
        
        
    }
};
