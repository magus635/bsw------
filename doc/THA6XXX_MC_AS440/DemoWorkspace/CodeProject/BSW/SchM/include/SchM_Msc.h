/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Msc.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Msc
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

#ifndef SCHM_MSC_H
#define SCHM_MSC_H

#include "Std_Types.h"

extern void SchM_Enter_Msc_TxCmdFrame
(
  void
);

extern void SchM_Exit_Msc_TxCmdFrame
(
  void
);

extern void SchM_Enter_Msc_TxDataFrame
(
  void
);

extern void SchM_Exit_Msc_TxDataFrame
(
  void
);

extern void SchM_Enter_Msc_GetRxData
(
  void
);


extern void SchM_Exit_Msc_GetRxData
(
  void
);

extern void SchM_Enter_Msc_DeInit
(
  void
);

extern void SchM_Exit_Msc_DeInit
(
  void
);

#endif /* SCHM_MSC_H */
