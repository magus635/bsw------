#include "Dsadc.h"
#include "Dsadc_Cfg.h"

/*===========================================================================
 *                         Dsadc Channel Configuration
 *===========================================================================*/

const Dsadc_ConfigType Dsadc_Config = {
    .Channels = {
        
        
        {
            .Id = 0,
            .Modulator = {
                .ClockDivider = 4,
                .InputSelect = INPUT_A
            },
            .Filter = {
                .OverSamplingRate = 64,
                .CombFilterShift = 2
            }
        }
        
        
    }
};
