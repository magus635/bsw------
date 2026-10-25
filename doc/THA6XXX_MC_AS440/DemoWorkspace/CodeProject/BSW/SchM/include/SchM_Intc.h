/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Intc.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Intc/Gic
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

#ifndef SCHM_INTC_H_
#define SCHM_INTC_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

#include "Std_Types.h"

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/

extern void SchM_Enter_Intc_EnableInterrupt(void);
extern void SchM_Exit_Intc_EnableInterrupt(void);
extern void SchM_Enter_Intc_DisableInterrupt(void);
extern void SchM_Exit_Intc_DisableInterrupt(void);
extern void SchM_Enter_Intc_GenSwInterrupt(void);
extern void SchM_Exit_Intc_GenSwInterrupt(void);

#endif /* SCHM_INTC_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
