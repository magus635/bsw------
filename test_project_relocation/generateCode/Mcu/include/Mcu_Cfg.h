/**
 * @file Mcu_Cfg.h
 * @brief Configuration header for MCU module
 */

#ifndef MCU_CFG_H
#define MCU_CFG_H

#include "Mcu_Types.h"

/*===========================================================================
 *                   MCU PRE-COMPILE PARAMETERS
 *===========================================================================*/


/* McuClockConfig_0 */
#define MCU_MCUCLOCKFREQUENCY  (80000000)

/* McuClockConfig_0 */
#define MCU_MCUCLOCKSOURCETYPE  (MCU_CLOCK_PLL)

/* McuClockConfig_0_McuClockSource_0 */
#define MCU_MCUCLOCKFREQUENCY  (160000000)

/* McuClockConfig_0_McuClockSource_0 */
#define MCU_MCUCLOCKSOURCETYPE  (MCU_CLOCK_PLL)


/*===========================================================================
 *                   MCU CLOCK CONFIGURATION
 *===========================================================================*/



/* Clock Configuration: McuClockConfig_0 */
#define MCU_MCUCLOCKCONFIG_0_EN  (STD_ON)



#endif /* MCU_CFG_H */
