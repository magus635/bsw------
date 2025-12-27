/**
 * @file Port_Cfg.h
 * @brief Configuration header for Port module
 */

#ifndef PORT_CFG_H
#define PORT_CFG_H

#include "Port_Types.h"

/*===========================================================================
 *                   PORT PRE-COMPILE PARAMETERS
 *===========================================================================*/


/* PortPin_0 */
#define PORT_PORTPINDIRECTION  (PORT_PIN_IN)

/* PortPin_0 */
#define PORT_PORTPINID  (10)

/* PortPin_0 */
#define PORT_PORTPININITIALMODE  (PORT_PIN_MODE_GPIO)

/* PortPin_0 */
#define PORT_PORTPINMODE  (PORT_PIN_MODE_GPIO)


/*===========================================================================
 *                   PORT PIN MACROS
 *===========================================================================*/

#define PORT_NUM_CONFIGURED_PINS  (1)

#endif /* PORT_CFG_H */
