#ifndef CAN_CFG_H
#define CAN_CFG_H

#include "Std_Types.h"

/* ==================== General ==================== */

#define CAN_DEV_ERROR_DETECT   STD_ON

#define CAN_CONTROLLER_COUNT  2

/* ==================== Controller IDs ==================== */

/* ECUC: CanController0/CanControllerId */
#define CAN_CONTROLLER_ID_0  0
/* ECUC: CanController1/CanControllerId */
#define CAN_CONTROLLER_ID_1  1

#endif /* CAN_CFG_H */