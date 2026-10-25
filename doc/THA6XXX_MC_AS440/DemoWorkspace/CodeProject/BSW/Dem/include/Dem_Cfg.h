/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Dem_Cfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Dem
*
*   brief                 : This file contains sample code only. It is not part of the production
*                           code deliverables.
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

#ifndef DEM_CFG_H
#define DEM_CFG_H

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/


#define DemConf_DemEventParameter_MCU_E_CLOCK_FAILURE               (1U)

#define DemConf_DemEventParameter_ETH_E_ACCESS                      (20U)
#define DemConf_DemEventParameter_ETH_E_RX_FRAMES_LOST               (23U)
#define DemConf_DemEventParameter_ETH_E_ALIGNMENT                   (24U)
#define DemConf_DemEventParameter_ETH_E_CRC                         (25U)
#define DemConf_DemEventParameter_ETH_E_SINGLECOLLISION             (26U)
#define DemConf_DemEventParameter_ETH_E_MULTIPLECOLLISION           (27U)
#define DemConf_DemEventParameter_ETH_E_LATECOLLISION               (28U)
#define DemConf_DemEventParameter_ETH_E_UNDERSIZEFRAME              (29U)
#define DemConf_DemEventParameter_ETH_E_OVERSIZEFRAME               (30U)

#define DemConf_DemEventParameter_WDG_E_MODE_FAILED                 (40U)
#define DemConf_DemEventParameter_WDG_E_DISABLE_REJECTED            (41U)

#define DemConf_DemEventParameter_DSADC_E_FIFO_FAILURE              (50U)

#define DemConf_DemEventParameter_LIN_E_TIMEOUT                     (60U)

#define DemConf_DemEventParameter_SPI_E_HARDWARE_ERROR              (70U)

#define DemConf_DemEventParameter_FEE_E_GC_WRITE                    (81U)
#define DemConf_DemEventParameter_FEE_E_GC_READ                     (82U)
#define DemConf_DemEventParameter_FEE_E_GC_ERASE                    (83U)
#define DemConf_DemEventParameter_FEE_E_GC_TRIG                     (84U)
#define DemConf_DemEventParameter_FEE_E_WRITE_CYCLES_EXHAUSTED      (85U)
#define DemConf_DemEventParameter_FEE_E_UNCONFIG_BLK_EXCEEDED       (86U)

#endif /* DEM_CFG_H */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
