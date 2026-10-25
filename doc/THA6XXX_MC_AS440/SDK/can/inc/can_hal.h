/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    can_hal.h
 * Author:      01107
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #can_hal_h_REF_1:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers
*
* #can_hal_h_REF_2:MISRAC2012-Rule-4.8;
* Justification:Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
* #can_hal_h_REF_3:CERTC-DCL12-C;
* Justification:Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
* #can_hal_h_REF_4:MISRAC2012-Rule-19.2;
* Justification: Necessary union type for bitwise access to register. Data integrity and correctness will be ensured by code review.
*
* #can_hal_h_REF_5:MISRAC2012-Rule-6.1;
* Justification: The type uint64 is implementation defined type, and is supported by the hardware. The behavior is defined and clear.
*/

#ifndef CAN_HAL_H_
#define CAN_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "can_register.h"
#include "tha6_cfg.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* ^CAN_Functional_State^ CAN functional state */
#define CAN_DISABLE                     (0x00U)
#define CAN_ENABLE                      (0x01U)

/* ^CAN_TIMEOUT^ CAN timeout value for setting register  */
#define CAN_INITIALIZATION_TIMEOUT      ((uint64)0x0000FFFFUL)

/* ^CAN_IT_Flags^ CAN Interrupt Flags */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_RXFIFO0MSG               ((uint32)0x00000001U)   /* [00] - Rx FIFO 0 new message interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_RXFIFO0WMREACHED         ((uint32)0x00000002U)   /* [01] - Rx FIFO 0 watermark reached interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_RXFIFO0FULL              ((uint32)0x00000004U)   /* [02] - Rx FIFO 0 full interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_RXFIFO0MSGLOST           ((uint32)0x00000008U)   /* [03] - Rx FIFO 0 message lost interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_RXFIFO1MSG               ((uint32)0x00000010U)   /* [04] - Rx FIFO 1 new message interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_RXFIFO1WMREACHED         ((uint32)0x00000020U)   /* [05] - Rx FIFO 1 watermark reached interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_RXFIFO1FULL              ((uint32)0x00000040U)   /* [06] - Rx FIFO 1 full interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_RXFIFO1MSGLOST           ((uint32)0x00000080U)   /* [07] - Rx FIFO 1 message lost interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_HIGHPRIMSG               ((uint32)0x00000100U)   /* [08] - High priority message interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_TXCOMPLETED              ((uint32)0x00000200U)   /* [09] - Transmission completed interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_TXCANCELLATIONFIN        ((uint32)0x00000400U)   /* [10] - Transmission cancellation finished interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_TXFIFOEMPTY              ((uint32)0x00000800U)   /* [11] - Tx FIFO empty interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_TXEVENTFIFONEWENTRY      ((uint32)0x00001000U)   /* [12] - Tx event FIFO new entry interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_TXEVENTFIFOWMREACHED     ((uint32)0x00002000U)   /* [13] - Tx event FIFO watermark reached interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_TXEVENTFIFOFULL          ((uint32)0x00004000U)   /* [14] - Tx event FIFO full interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_TXEVENTFIFOEVENTLOST     ((uint32)0x00008000U)   /* [15] - Tx event FIFO event lost interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_TIMESTAMPWRAPAROUND      ((uint32)0x00010000U)   /* [16] - Timestamp wraparound interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_RAMACCESSFAILURE         ((uint32)0x00020000U)   /* [17] - Message RAM access failure interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_TIMEOUTOCCOURRED         ((uint32)0x00040000U)   /* [18] - Timeout occurred interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_MSGDEDICATEDRXBUF        ((uint32)0x00080000U)   /* [19] - Message stored to dedicated Rx buffer interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_BITERRCORRECTED          ((uint32)0x00100000U)   /* [20] - Bit error corrected interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_BITERRUNCORRECTED        ((uint32)0x00200000U)   /* [21] - Bit error uncorrected interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ERROVERFLOW              ((uint32)0x00400000U)   /* [22] - Error logging overflow interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ERRPASSIVE               ((uint32)0x00800000U)   /* [23] - Error passive interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_WARNINGSTATUS            ((uint32)0x01000000U)   /* [24] - Warning status interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_BUSOFFSTATUS             ((uint32)0x02000000U)   /* [25] - Bus off status interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_WATCHDOG                 ((uint32)0x04000000U)   /* [26] - Watchdog interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_PROERRARBITRATION        ((uint32)0x08000000U)   /* [27] - Protocol error in arbitration phase interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_PROERRDATA               ((uint32)0x10000000U)   /* [28] - Protocol error in Data phase interrupt */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ACCESSRESADDR            ((uint32)0x20000000U)   /* [29] - Access to reserved address interrupt */
#define CAN_IT_MASK                     ((uint32)0x3FFFFFFFU)

/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_RXFIFO0_MASK             (CAN_IT_RXFIFO0MSG | CAN_IT_RXFIFO0WMREACHED | \
                                        CAN_IT_RXFIFO0FULL | CAN_IT_RXFIFO0MSGLOST) /* CAN interrupt RX-FIFO0 mask */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_RXFIFO1_MASK             (CAN_IT_RXFIFO1MSG | CAN_IT_RXFIFO1WMREACHED | \
                                        CAN_IT_RXFIFO1FULL | CAN_IT_RXFIFO1MSGLOST) /* CAN interrupt RX-FIFO1 mask */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_TXEVENT_MASK             (CAN_IT_TXEVENTFIFONEWENTRY | CAN_IT_TXEVENTFIFOWMREACHED | \
                                        CAN_IT_TXEVENTFIFOFULL | CAN_IT_TXEVENTFIFOEVENTLOST)   /* CAN interrupt TX event mask */
/* #Violation: can_hal_h_REF_1 */
#define CAN_ERRORSTATUS_MASK            (CAN_IT_ERRPASSIVE | CAN_IT_WARNINGSTATUS | \
                                        CAN_IT_BUSOFFSTATUS)    /* CAN error status mask */
/* #Violation: can_hal_h_REF_1 */
#define CAN_ERRORS_MASK                 (CAN_IT_ERROVERFLOW | CAN_IT_WATCHDOG | \
                                        CAN_IT_PROERRARBITRATION | CAN_IT_PROERRDATA |\
                                        CAN_IT_ACCESSRESADDR)   /* CAN error mask */

/* ^CAN_IT_RouterFlags^ CAN router interrupt flags
   Note: Some interrupts are triggers with combinatorial properities.
*/
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_REINT             CAN_IT_MSGDEDICATEDRXBUF        /* [00] See CAN_IT_Flags IR-[19]*/
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_RXF1F             CAN_IT_RXFIFO1FULL              /* [01] See CAN_IT_Flags IR-[06] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_RXF0F             CAN_IT_RXFIFO0FULL              /* [02] See CAN_IT_Flags IR-[02] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_RXF1N             CAN_IT_RXFIFO1MSG               /* [03] See CAN_IT_Flags IR-[04] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_RXF0N             CAN_IT_RXFIFO0MSG               /* [04] See CAN_IT_Flags IR-[00] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_RETI              CAN_IT_TIMEOUTOCCOURRED         /* [05] See CAN_IT_Flags IR-[18] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_TRAQ              CAN_IT_TXFIFOEMPTY              /* [06] See CAN_IT_Flags IR-[11] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_TRACO             (CAN_IT_TXCOMPLETED | \
                                        CAN_IT_TXCANCELLATIONFIN)       /* [07] See CAN_IT_Flags IR-[09\10] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_TEFIFO            (CAN_IT_TXEVENTFIFONEWENTRY | \
                                        CAN_IT_TXEVENTFIFOFULL)         /* [08] See CAN_IT_Flags IR-[12\14] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_HPE               CAN_IT_HIGHPRIMSG               /* [09] See CAN_IT_Flags IR-[8] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_WAIT              (CAN_IT_RXFIFO0WMREACHED | \
                                        CAN_IT_RXFIFO1WMREACHED | \
                                        CAN_IT_TXEVENTFIFOWMREACHED)    /* [10] See CAN_IT_Flags IR-[01\05\13] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_ALERT             (CAN_IT_RXFIFO0MSGLOST | \
                                        CAN_IT_RXFIFO1MSGLOST | \
                                        CAN_IT_TXEVENTFIFOEVENTLOST | \
                                        CAN_IT_TIMESTAMPWRAPAROUND | \
                                        CAN_IT_BITERRCORRECTED | \
                                        CAN_IT_BITERRUNCORRECTED | \
                                        CAN_IT_ERRPASSIVE | \
                                        CAN_IT_WARNINGSTATUS | \
                                        CAN_IT_ACCESSRESADDR)           /* [11] See CAN_IT_Flags IR-[3\7\15\16\20\21\23\24\29] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_MORE              (CAN_IT_RAMACCESSFAILURE | \
                                        CAN_IT_WATCHDOG)                /* [12] See CAN_IT_Flags IR-[17\26] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_SAFE              CAN_IT_ERROVERFLOW              /* [13] See CAN_IT_Flags IR-[22] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_BUSOFF            CAN_IT_BUSOFFSTATUS             /* [14] See CAN_IT_Flags IR-[25] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_LOI               (CAN_IT_PROERRARBITRATION | \
                                        CAN_IT_PROERRDATA)              /* [15] See CAN_IT_Flags IR-[27\28] */

/* ^CAN_IT_LINES_FLAGS^ CAN interrupt line flags */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_LINE0                    ((uint32)0x00000000U)
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_LINE1                    ((uint32)0x00000001U)

/* ^CAN_IT_ROUTER_LINES_FLAGS^ CAN router interrupt line flags */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_LINE0             ((uint32)0x00000000U)
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_LINE1             ((uint32)0x00000001U)
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_LINE2             ((uint32)0x00000002U)
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_LINE3             ((uint32)0x00000003U)
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_LINE4             ((uint32)0x00000004U)
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_LINE5             ((uint32)0x00000005U)
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_LINE6             ((uint32)0x00000006U)
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_LINE7             ((uint32)0x00000007U)
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_LINE8             ((uint32)0x00000008U)
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_LINE9             ((uint32)0x00000009U)
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_LINE10            ((uint32)0x0000000AU)
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_LINE11            ((uint32)0x0000000BU)
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_LINE12            ((uint32)0x0000000CU)
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_LINE13            ((uint32)0x0000000DU)
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_LINE14            ((uint32)0x0000000EU)
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_ROUTER_LINE15            ((uint32)0x0000000FU)

/* ^CAN_IR_RouterFlags^ CAN router interrupt status flags */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IR_ROUTER_REINT             ((uint32)0x00000001U)   /* [00] See CAN_IT_Flags IR-[19]*/
/* #Violation: can_hal_h_REF_1 */
#define CAN_IR_ROUTER_RXF1F             ((uint32)0x00000002U)   /* [01] See CAN_IT_Flags IR-[06] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IR_ROUTER_RXF0F             ((uint32)0x00000004U)   /* [02] See CAN_IT_Flags IR-[02] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IR_ROUTER_RXF1N             ((uint32)0x00000008U)   /* [03] See CAN_IT_Flags IR-[04] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IR_ROUTER_RXF0N             ((uint32)0x00000010U)   /* [04] See CAN_IT_Flags IR-[00] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IR_ROUTER_RETI              ((uint32)0x00000020U)   /* [05] See CAN_IT_Flags IR-[18] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IR_ROUTER_TRAQ              ((uint32)0x00000040U)   /* [06] See CAN_IT_Flags IR-[11] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IR_ROUTER_TRACO             ((uint32)0x00000080U)   /* [07] See CAN_IT_Flags IR-[09\10] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IR_ROUTER_TEFIFO            ((uint32)0x00000100U)   /* [08] See CAN_IT_Flags IR-[12\14] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IR_ROUTER_HPE               ((uint32)0x00000200U)   /* [09] See CAN_IT_Flags IR-[8] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IR_ROUTER_WAIT              ((uint32)0x00000400U)   /* [10] See CAN_IT_Flags IR-[01\05\13] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IR_ROUTER_ALERT             ((uint32)0x00000800U)   /* [11] See CAN_IT_Flags IR-[3\7\15\16\20\21\23\24\29] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IR_ROUTER_MORE              ((uint32)0x00001000U)   /* [12] See CAN_IT_Flags IR-[17\26] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IR_ROUTER_SAFE              ((uint32)0x00002000U)   /* [13] See CAN_IT_Flags IR-[22] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IR_ROUTER_BUSOFF            ((uint32)0x00004000U)   /* [14] See CAN_IT_Flags IR-[25] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IR_ROUTER_LOI               ((uint32)0x00008000U)   /* [15] See CAN_IT_Flags IR-[27\28] */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IR_ROUTER_MASK              ((uint32)0x0000FFFFU)

/* ^CAN_IT_DMU_Flags^ CAN DMU interrupt flags */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_TXENSAE              ((uint32)0x00000001U)   /* [00] TX element not start address */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_TXEIEE               ((uint32)0x00000002U)   /* [01] TX element illegal enqueueing */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_TXEIASE              ((uint32)0x00000004U)   /* [02] TX element illegal access sequence */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_TXEIDLCE             ((uint32)0x00000008U)   /* [03] TX element illegal DLC */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_TXEWATAE             ((uint32)0x00000010U)   /* [04] TX element write after trigger address */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_TXEIRE               ((uint32)0x00000020U)   /* [05] TX element illegal Read */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_TXEEE                ((uint32)0x00000040U)   /* [06] TX element enqueued */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_RX0ENSAE             ((uint32)0x00000100U)   /* [08] RX0 element not start address */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_RX0EIDE              ((uint32)0x00000200U)   /* [09] RX0 element illegal dequeueing */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_RX0EIASE             ((uint32)0x00000400U)   /* [10] RX0 element illegal access sequence */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_RX0EIWE              ((uint32)0x00000800U)   /* [11] RX0 element illegal write */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_RX0EDE               ((uint32)0x00001000U)   /* [12] RX0 element dequeued */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_RX0EIOE              ((uint32)0x00002000U)   /* [13] RX0 element illegal overwrite by time stamp enable */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_BECE                 ((uint32)0x00004000U)   /* [14] Bit error corrected  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_BEUE                 ((uint32)0x00008000U)   /* [15] Bit error uncorrected */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_RX1ENSAE             ((uint32)0x00010000U)   /* [16] RX1 element not start address */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_RX1EIDE              ((uint32)0x00020000U)   /* [17] RX1 element illegal dequeueing */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_RX1EIASE             ((uint32)0x00040000U)   /* [18] RX1 element illegal access sequence */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_RX1EIWE              ((uint32)0x00080000U)   /* [19] RX1 element illegal write */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_RX1EDE               ((uint32)0x00100000U)   /* [20] RX1 element dequeued */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_RX1EIOE              ((uint32)0x00200000U)   /* [21] RX1 element illegal overwrite by time stamp enable */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_TXEENSAE             ((uint32)0x01000000U)   /* [24] TX event element not start address */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_TXEEIDE              ((uint32)0x02000000U)   /* [25] TX event element illegal dequeueing */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_TXEEIASE             ((uint32)0x04000000U)   /* [26] TX event element illegal access sequence */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_TXEEIWE              ((uint32)0x08000000U)   /* [27] TX event element illegal write */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_TXEEDE               ((uint32)0x10000000U)   /* [28] TX event element dequeued */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_DTE                  ((uint32)0x20000000U)   /* [29] Debug trigger */
/* #Violation: can_hal_h_REF_1 */
#define CAN_IT_DMU_IACE                 ((uint32)0x40000000U)   /* [30] Illegal access while in configuration mode */
#define CAN_IT_DMU_MASK                 ((uint32)0x7F3FFF7FU)

/* ^CAN_RxLocation^ CAN RX dedicated buffer index and FIFO 0\1 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER0                  ((uint32)0x00000000U)   /* Get received message from Rx Buffer 0  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER1                  ((uint32)0x00000001U)   /* Get received message from Rx Buffer 1  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER2                  ((uint32)0x00000002U)   /* Get received message from Rx Buffer 2  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER3                  ((uint32)0x00000003U)   /* Get received message from Rx Buffer 3  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER4                  ((uint32)0x00000004U)   /* Get received message from Rx Buffer 4  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER5                  ((uint32)0x00000005U)   /* Get received message from Rx Buffer 5  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER6                  ((uint32)0x00000006U)   /* Get received message from Rx Buffer 6  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER7                  ((uint32)0x00000007U)   /* Get received message from Rx Buffer 7  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER8                  ((uint32)0x00000008U)   /* Get received message from Rx Buffer 8  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER9                  ((uint32)0x00000009U)   /* Get received message from Rx Buffer 9  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER10                 ((uint32)0x0000000AU)   /* Get received message from Rx Buffer 10 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER11                 ((uint32)0x0000000BU)   /* Get received message from Rx Buffer 11 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER12                 ((uint32)0x0000000CU)   /* Get received message from Rx Buffer 12 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER13                 ((uint32)0x0000000DU)   /* Get received message from Rx Buffer 13 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER14                 ((uint32)0x0000000EU)   /* Get received message from Rx Buffer 14 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER15                 ((uint32)0x0000000FU)   /* Get received message from Rx Buffer 15 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER16                 ((uint32)0x00000010U)   /* Get received message from Rx Buffer 16 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER17                 ((uint32)0x00000011U)   /* Get received message from Rx Buffer 17 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER18                 ((uint32)0x00000012U)   /* Get received message from Rx Buffer 18 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER19                 ((uint32)0x00000013U)   /* Get received message from Rx Buffer 19 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER20                 ((uint32)0x00000014U)   /* Get received message from Rx Buffer 20 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER21                 ((uint32)0x00000015U)   /* Get received message from Rx Buffer 21 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER22                 ((uint32)0x00000016U)   /* Get received message from Rx Buffer 22 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER23                 ((uint32)0x00000017U)   /* Get received message from Rx Buffer 23 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER24                 ((uint32)0x00000018U)   /* Get received message from Rx Buffer 24 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER25                 ((uint32)0x00000019U)   /* Get received message from Rx Buffer 25 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER26                 ((uint32)0x0000001AU)   /* Get received message from Rx Buffer 26 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER27                 ((uint32)0x0000001BU)   /* Get received message from Rx Buffer 27 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER28                 ((uint32)0x0000001CU)   /* Get received message from Rx Buffer 28 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER29                 ((uint32)0x0000001DU)   /* Get received message from Rx Buffer 29 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER30                 ((uint32)0x0000001EU)   /* Get received message from Rx Buffer 30 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER31                 ((uint32)0x0000001FU)   /* Get received message from Rx Buffer 31 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER32                 ((uint32)0x00000020U)   /* Get received message from Rx Buffer 32 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER33                 ((uint32)0x00000021U)   /* Get received message from Rx Buffer 33 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER34                 ((uint32)0x00000022U)   /* Get received message from Rx Buffer 34 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER35                 ((uint32)0x00000023U)   /* Get received message from Rx Buffer 35 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER36                 ((uint32)0x00000024U)   /* Get received message from Rx Buffer 36 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER37                 ((uint32)0x00000025U)   /* Get received message from Rx Buffer 37 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER38                 ((uint32)0x00000026U)   /* Get received message from Rx Buffer 38 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER39                 ((uint32)0x00000027U)   /* Get received message from Rx Buffer 39 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER40                 ((uint32)0x00000028U)   /* Get received message from Rx Buffer 40 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER41                 ((uint32)0x00000029U)   /* Get received message from Rx Buffer 41 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER42                 ((uint32)0x0000002AU)   /* Get received message from Rx Buffer 42 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER43                 ((uint32)0x0000002BU)   /* Get received message from Rx Buffer 43 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER44                 ((uint32)0x0000002CU)   /* Get received message from Rx Buffer 44 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER45                 ((uint32)0x0000002DU)   /* Get received message from Rx Buffer 45 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER46                 ((uint32)0x0000002EU)   /* Get received message from Rx Buffer 46 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER47                 ((uint32)0x0000002FU)   /* Get received message from Rx Buffer 47 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER48                 ((uint32)0x00000030U)   /* Get received message from Rx Buffer 48 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER49                 ((uint32)0x00000031U)   /* Get received message from Rx Buffer 49 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER50                 ((uint32)0x00000032U)   /* Get received message from Rx Buffer 50 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER51                 ((uint32)0x00000033U)   /* Get received message from Rx Buffer 51 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER52                 ((uint32)0x00000034U)   /* Get received message from Rx Buffer 52 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER53                 ((uint32)0x00000035U)   /* Get received message from Rx Buffer 53 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER54                 ((uint32)0x00000036U)   /* Get received message from Rx Buffer 54 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER55                 ((uint32)0x00000037U)   /* Get received message from Rx Buffer 55 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER56                 ((uint32)0x00000038U)   /* Get received message from Rx Buffer 56 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER57                 ((uint32)0x00000039U)   /* Get received message from Rx Buffer 57 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER58                 ((uint32)0x0000003AU)   /* Get received message from Rx Buffer 58 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER59                 ((uint32)0x0000003BU)   /* Get received message from Rx Buffer 59 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER60                 ((uint32)0x0000003CU)   /* Get received message from Rx Buffer 60 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER61                 ((uint32)0x0000003DU)   /* Get received message from Rx Buffer 61 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER62                 ((uint32)0x0000003EU)   /* Get received message from Rx Buffer 62 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_BUFFER63                 ((uint32)0x0000003FU)   /* Get received message from Rx Buffer 63 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_FIFO0                    ((uint32)0x00000040U)   /* Get received message from Rx FIFO 0    */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RX_FIFO1                    ((uint32)0x00000041U)   /* Get received message from Rx FIFO 1    */

/* ^CAN_TxLocation^ CAN TX dedecated buffer index and FIFO\QUEUE */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER0                  ((uint32)0x00000000U)   /* Add message to Tx Buffer 0  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER1                  ((uint32)0x00000001U)   /* Add message to Tx Buffer 1  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER2                  ((uint32)0x00000002U)   /* Add message to Tx Buffer 2  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER3                  ((uint32)0x00000003U)   /* Add message to Tx Buffer 3  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER4                  ((uint32)0x00000004U)   /* Add message to Tx Buffer 4  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER5                  ((uint32)0x00000005U)   /* Add message to Tx Buffer 5  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER6                  ((uint32)0x00000006U)   /* Add message to Tx Buffer 6  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER7                  ((uint32)0x00000007U)   /* Add message to Tx Buffer 7  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER8                  ((uint32)0x00000008U)   /* Add message to Tx Buffer 8  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER9                  ((uint32)0x00000009U)   /* Add message to Tx Buffer 9  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER10                 ((uint32)0x0000000AU)   /* Add message to Tx Buffer 10 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER11                 ((uint32)0x0000000BU)   /* Add message to Tx Buffer 11 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER12                 ((uint32)0x0000000CU)   /* Add message to Tx Buffer 12 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER13                 ((uint32)0x0000000DU)   /* Add message to Tx Buffer 13 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER14                 ((uint32)0x0000000EU)   /* Add message to Tx Buffer 14 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER15                 ((uint32)0x0000000FU)   /* Add message to Tx Buffer 15 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER16                 ((uint32)0x00000010U)   /* Add message to Tx Buffer 16 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER17                 ((uint32)0x00000011U)   /* Add message to Tx Buffer 17 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER18                 ((uint32)0x00000012U)   /* Add message to Tx Buffer 18 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER19                 ((uint32)0x00000013U)   /* Add message to Tx Buffer 19 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER20                 ((uint32)0x00000014U)   /* Add message to Tx Buffer 20 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER21                 ((uint32)0x00000015U)   /* Add message to Tx Buffer 21 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER22                 ((uint32)0x00000016U)   /* Add message to Tx Buffer 22 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER23                 ((uint32)0x00000017U)   /* Add message to Tx Buffer 23 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER24                 ((uint32)0x00000018U)   /* Add message to Tx Buffer 24 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER25                 ((uint32)0x00000019U)   /* Add message to Tx Buffer 25 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER26                 ((uint32)0x0000001AU)   /* Add message to Tx Buffer 26 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER27                 ((uint32)0x0000001BU)   /* Add message to Tx Buffer 27 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER28                 ((uint32)0x0000001CU)   /* Add message to Tx Buffer 28 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER29                 ((uint32)0x0000001DU)   /* Add message to Tx Buffer 29 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER30                 ((uint32)0x0000001EU)   /* Add message to Tx Buffer 30 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_BUFFER31                 ((uint32)0x0000001FU)   /* Add message to Tx Buffer 31 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_FIFOQUEUE                ((uint32)0x00000020U)   /* Add message to Tx FIFO\QUEUE */

/* ^CAN_DMU_RequestType^  CAN DMU request type */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DMU_REQUEST_TX              ((uint32)0x00000000U)   /* DMA request signal of Tx Queue\FIFO */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DMU_REQUEST_RX0             ((uint32)0x00000001U)   /* DMA request signal of Rx FIFO 0 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DMU_REQUEST_RX1             ((uint32)0x00000002U)   /* DMA request signal of Rx FIFO 1 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DMU_REQUEST_TXE             ((uint32)0x00000003U)   /* DMA request signal of Tx event FIFO */

/* ^CAN_DMU_AddressType^ CAN DMU address type */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DMU_ADDRESSTYPE_TX          ((uint32)0x00000000U)   /* TX address type */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DMU_ADDRESSTYPE_RX_0        ((uint32)0x00000001U)   /* RX-0 address type */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DMU_ADDRESSTYPE_RX_1        ((uint32)0x00000002U)   /* RX-1 address type */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DMU_ADDRESSTYPE_TXE         ((uint32)0x00000003U)   /* TX event address type */

/* ^CAN_SleepStatus^ The status for sleep*/
/* #Violation: can_hal_h_REF_1 */
#define CAN_SLEEPSTATUS_INACTIVE        ((uint32)0x00000000U)   /* The status for sleep is inactive */
/* #Violation: can_hal_h_REF_1 */
#define CAN_SLEEPSTATUS_ACTIVE          ((uint32)0x00000001U)   /* The status for sleep is active */

/* ^CAN_InternalTimestampPrescaler^ CAN internal timestamp prescaler */
/* #Violation: can_hal_h_REF_1 */
#define CAN_INTERNAL_TIMESTAMP_PRESC_1  ((uint32)0x00000000U)   /* Timestamp counter time unit in equal to CAN bit time                 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_INTERNAL_TIMESTAMP_PRESC_2  ((uint32)0x00000001U)   /* Timestamp counter time unit in equal to CAN bit time multipled by 2  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_INTERNAL_TIMESTAMP_PRESC_3  ((uint32)0x00000002U)   /* Timestamp counter time unit in equal to CAN bit time multipled by 3  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_INTERNAL_TIMESTAMP_PRESC_4  ((uint32)0x00000003U)   /* Timestamp counter time unit in equal to CAN bit time multipled by 4  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_INTERNAL_TIMESTAMP_PRESC_5  ((uint32)0x00000004U)   /* Timestamp counter time unit in equal to CAN bit time multipled by 5  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_INTERNAL_TIMESTAMP_PRESC_6  ((uint32)0x00000005U)   /* Timestamp counter time unit in equal to CAN bit time multipled by 6  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_INTERNAL_TIMESTAMP_PRESC_7  ((uint32)0x00000006U)   /* Timestamp counter time unit in equal to CAN bit time multipled by 7  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_INTERNAL_TIMESTAMP_PRESC_8  ((uint32)0x00000007U)   /* Timestamp counter time unit in equal to CAN bit time multipled by 8  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_INTERNAL_TIMESTAMP_PRESC_9  ((uint32)0x00000008U)   /* Timestamp counter time unit in equal to CAN bit time multipled by 9  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_INTERNAL_TIMESTAMP_PRESC_10 ((uint32)0x00000009U)   /* Timestamp counter time unit in equal to CAN bit time multipled by 10 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_INTERNAL_TIMESTAMP_PRESC_11 ((uint32)0x0000000AU)   /* Timestamp counter time unit in equal to CAN bit time multipled by 11 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_INTERNAL_TIMESTAMP_PRESC_12 ((uint32)0x0000000BU)   /* Timestamp counter time unit in equal to CAN bit time multipled by 12 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_INTERNAL_TIMESTAMP_PRESC_13 ((uint32)0x0000000CU)   /* Timestamp counter time unit in equal to CAN bit time multipled by 13 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_INTERNAL_TIMESTAMP_PRESC_14 ((uint32)0x0000000DU)   /* Timestamp counter time unit in equal to CAN bit time multipled by 14 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_INTERNAL_TIMESTAMP_PRESC_15 ((uint32)0x0000000EU)   /* Timestamp counter time unit in equal to CAN bit time multipled by 15 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_INTERNAL_TIMESTAMP_PRESC_16 ((uint32)0x0000000FU)   /* Timestamp counter time unit in equal to CAN bit time multipled by 16 */

/* ^CAN_TimestampOperation^ CAN time stamp operation */
#define CAN_TIMESTAMP_OPS_STOP          ((uint32)0x00000000U)   /* Timestamp counter value always 0x0000                */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TIMESTAMP_OPS_INTERNAL      ((uint32)0x00000001U)   /* Timestamp counter value incremented according to TCP */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TIMESTAMP_OPS_EXTERNAL      ((uint32)0x00000002U)   /* External timestamp counter value used                */

/* ^CAN_TimeoutOperation^ CAN timeout operation */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TIMEOUT_CONTINUOUS          ((uint32)0x00000000U)   /* Timeout continuous operation        */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TIMEOUT_TX_EVENT_FIFO       ((uint32)0x00000001U)   /* Timeout controlled by Tx Event FIFO */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TIMEOUT_RX_FIFO0            ((uint32)0x00000002U)   /* Timeout controlled by Rx FIFO 0     */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TIMEOUT_RX_FIFO1            ((uint32)0x00000003U)   /* Timeout controlled by Rx FIFO 1     */

/* ^CAN_OperationMode^ CAN operating mode */
#define CAN_OPERATION_MODE_NORMAL       ((uint32)0x00000000U)   /* Normal */
#define CAN_OPERATION_MODE_MONITOR      ((uint32)0x00000001U)   /* Bus monitor */
#define CAN_OPERATION_MODE_INLOOPBACK   ((uint32)0x00000002U)   /* Internal loop back */
#define CAN_OPERATION_MODE_EXLOOPBACK   ((uint32)0x00000003U)   /* External loop back */
#define CAN_OPERATION_MODE_ASM          ((uint32)0x00000004U)   /* Restricted operation */

/* ^CAN_FrameFormat^ CAN frame format */
#define CAN_FRAME_FORMAT_STANDARD        ((uint32)0x00000000U)   /* Standard CAN frame (transmit and receive) */
#define CAN_FRAME_FORMAT_FD_NO_BRS       ((uint32)0x00000001U)   /* CAN FD long frame in transmit and CAN FD long and fast frame in receive */
#define CAN_FRAME_FORMAT_FDFAST          ((uint32)0x00000002U)   /* CAN FD long and fast frames (transmit and receive) */

/* ^CAN_FrameType^ Can frame type */
/* #Violation: can_hal_h_REF_1 */
#define CAN_FRAME_TYPE_DATA             ((uint32)0x00000000U)   /* Data frame   */
/* #Violation: can_hal_h_REF_1 */
#define CAN_FRAME_TYPE_REMOTE           ((uint32)0x00000001U)   /* Remote frame */

/* ^Can_ID_Type^ Can ID type */
#define CAN_ID_TYPE_STANDARD            ((uint32)0x00000000U)   /* Standard ID element */
/* #Violation: can_hal_h_REF_1 */
#define CAN_ID_TYPE_EXTENDED            ((uint32)0x00000001U)   /* Extended ID element */

/* ^CAN_FifoWatermark^ CAN FIFO watermark */
#define CAN_WATERMARK_TX_EVENT_FIFO     ((uint32)0x00000000U)   /* Tx event FIFO */
#define CAN_WATERMARK_RX_FIFO0          ((uint32)0x00000001U)   /* Rx FIFO0      */
#define CAN_WATERMARK_RX_FIFO1          ((uint32)0x00000002U)   /* Rx FIFO1      */

/* ^CAN_RxFifoOperationMode^ CAN Rx FIFO 0/1 operating mode */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RXFIFOMODE_BLOCKING         ((uint32)0x00000000U)   /* Blocking mode.  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_RXFIFOMODE_OVERWRITE        ((uint32)0x00000001U)   /* Overwrite mode. */

/* ^CAN_TxFifoQueueMode^ CAN Tx FIFO/Queue Mode */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_FIFO_OPERATION           ((uint32)0x00000000U)   /* FIFO mode  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_QUEUE_OPERATION          ((uint32)0x00000001U)   /* Queue mode */

/* ^Can_DataFieldSize^  CAN data length for every element */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DATAFIELDSIZE_8             ((uint32)0x00000000U)   /* 8 Byte data field  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DATAFIELDSIZE_12            ((uint32)0x00000001U)   /* 12 Byte data field  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DATAFIELDSIZE_16            ((uint32)0x00000002U)   /* 16 Byte data field  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DATAFIELDSIZE_20            ((uint32)0x00000003U)   /* 20 Byte data field  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DATAFIELDSIZE_24            ((uint32)0x00000004U)   /* 24 Byte data field  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DATAFIELDSIZE_32            ((uint32)0x00000005U)   /* 32 Byte data field  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DATAFIELDSIZE_48            ((uint32)0x00000006U)   /* 48 Byte data field  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DATAFIELDSIZE_64            ((uint32)0x00000007U)   /* 64 Byte data field  */

/* ^CAN_DataLengthCode^ CAN data length code, eg. the length of TX send data  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DLC_BYTES_0                 ((uint32)0x00000000U)   /* 0 bytes data field  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DLC_BYTES_1                 ((uint32)0x00000001U)   /* 1 bytes data field  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DLC_BYTES_2                 ((uint32)0x00000002U)   /* 2 bytes data field  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DLC_BYTES_3                 ((uint32)0x00000003U)   /* 3 bytes data field  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DLC_BYTES_4                 ((uint32)0x00000004U)   /* 4 bytes data field  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DLC_BYTES_5                 ((uint32)0x00000005U)   /* 5 bytes data field  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DLC_BYTES_6                 ((uint32)0x00000006U)   /* 6 bytes data field  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DLC_BYTES_7                 ((uint32)0x00000007U)   /* 7 bytes data field  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DLC_BYTES_8                 ((uint32)0x00000008U)   /* 8 bytes data field  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DLC_BYTES_12                ((uint32)0x00000009U)   /* 12 bytes data field */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DLC_BYTES_16                ((uint32)0x0000000AU)   /* 16 bytes data field */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DLC_BYTES_20                ((uint32)0x0000000BU)   /* 20 bytes data field */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DLC_BYTES_24                ((uint32)0x0000000CU)   /* 24 bytes data field */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DLC_BYTES_32                ((uint32)0x0000000DU)   /* 32 bytes data field */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DLC_BYTES_48                ((uint32)0x0000000EU)   /* 48 bytes data field */
/* #Violation: can_hal_h_REF_1 */
#define CAN_DLC_BYTES_64                ((uint32)0x0000000FU)   /* 64 bytes data field */

/* ^CAN_NonMatchingFrames^ CAN non-matching frames
    Indicate the action to be taken with the messages which do not
    match with any element of the filter.*/
/* #Violation: can_hal_h_REF_1 */
#define CAN_NOMATCHINGFRAME_ACCEPTFIFO0 ((uint32)0x00000000U)   /* Accept the non matching messages into Rx FIFO 0  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_NOMATCHINGFRAME_ACCEPTFIFO1 ((uint32)0x00000001U)   /* Accepts the non matching messages into Rx FIFO 1 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_NOMATCHINGFRAME_REJECT      ((uint32)0x00000002U)   /* Reject the non-matching messages                 */

/* ^CAN_RejectRemoteFrames^ CAN reject remote frames */
/* #Violation: can_hal_h_REF_1 */
#define CAN_FILTER_REMOTE               ((uint32)0x00000000U)   /* Filter remote frames     */
/* #Violation: can_hal_h_REF_1 */
#define CAN_REJECT_REMOTE               ((uint32)0x00000001U)   /* Reject all remote frames */

/* ^CAN_FilterType^ CAN filter type */
/* #Violation: can_hal_h_REF_1 */
#define CAN_FILTERTYPE_RANGE            ((uint32)0x00000000U)   /* Range filter, ID1 to ID2 (ID2 >= ID1)  */
/* #Violation: can_hal_h_REF_1 */
#define CAN_FILTERTYPE_DUALID           ((uint32)0x00000001U)   /* Dual ID filter */
/* #Violation: can_hal_h_REF_1 */
#define CAN_FILTERTYPE_CLASSIC          ((uint32)0x00000002U)   /* Classic filter,FID1 = filter, ID2 = mask */
/* #Violation: can_hal_h_REF_1 */
#define CAN_FILTERTYPE_STD_DISABLE      ((uint32)0x00000003U)   /* Only for standard filter, disable filter elment */
/* #Violation: can_hal_h_REF_1 */
#define CAN_FILTERTYPE_EX_RANGE_NOXIDAM ((uint32)0x00000003U)   /* Only for extended filter: Range filter from
                                                                   ID1 to ID2 (ID2 >= ID1), XIDAM mask not applied */

/* ^CAN_FilterElmCfg^  CAN filter element configuration */
/* #Violation: can_hal_h_REF_1 */
#define CAN_FILTERELECFG_DISABLE        ((uint32)0x00000000U)   /* Disable filter element */
/* #Violation: can_hal_h_REF_1 */
#define CAN_FILTERELECFG_STORE_FIFO0    ((uint32)0x00000001U)   /* Store in Rx FIFO 0 if filter matches */
/* #Violation: can_hal_h_REF_1 */
#define CAN_FILTERELECFG_STORE_FIFO1    ((uint32)0x00000002U)   /* Store in Rx FIFO 1 if filter matches */
/* #Violation: can_hal_h_REF_1 */
#define CAN_FILTERELECFG_REJECTID       ((uint32)0x00000003U)   /* Reject ID if filter matches */
/* #Violation: can_hal_h_REF_1 */
#define CAN_FILTERELECFG_SETP_RIORITY   ((uint32)0x00000004U)   /* Set priority if filter matches */
/* #Violation: can_hal_h_REF_1 */
#define CAN_FILTERELECFG_SETPRIST_FIFO0 ((uint32)0x00000005U)   /* Set priority and store in FIFO 0 if filter matches */
/* #Violation: can_hal_h_REF_1 */
#define CAN_FILTERELECFG_SETPRIST_FIFO1 ((uint32)0x00000006U)   /* Set priority and store in FIFO 1 if filter matches */
#define CAN_FILTERELECFG_STORE_RXBUFFER ((uint32)0x00000007U)   /* Store into Rx buffer */

/* ^CAN_EventType^ CAN Tx event type */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_EVENT                    ((uint32)0x00000000U)   /* Tx event                              */
/* #Violation: can_hal_h_REF_1 */
#define CAN_TX_IN_SPITE_OF_ABORT        ((uint32)0x00000001U)   /* Transmission in spite of cancellation */

/* ^CAN_CommunicationState^ CAN communication state */
/* #Violation: can_hal_h_REF_1 */
#define CAN_COM_STATE_SYNC              ((uint32)0x00000000U)   /* Node is synchronizing on CAN communication */
/* #Violation: can_hal_h_REF_1 */
#define CAN_COM_STATE_IDLE              ((uint32)0x00000008U)   /* Node is neither receiver nor transmitter   */
/* #Violation: can_hal_h_REF_1 */
#define CAN_COM_STATE_RX                ((uint32)0x00000010U)   /* Node is operating as receiver              */
/* #Violation: can_hal_h_REF_1 */
#define CAN_COM_STATE_TX                ((uint32)0x00000018U)   /* Node is operating as transmitter           */

/* ^CAN_ProtocolErrorCode^ CAN protocol error code */
/* #Violation: can_hal_h_REF_1 */
#define CAN_PROTOCOL_ERROR_NONE         ((uint32)0x00000000U)   /* No error occurred                      */
/* #Violation: can_hal_h_REF_1 */
#define CAN_PROTOCOL_ERROR_STUFF        ((uint32)0x00000001U)   /* Stuff error                            */
/* #Violation: can_hal_h_REF_1 */
#define CAN_PROTOCOL_ERROR_FORM         ((uint32)0x00000002U)   /* Form error                             */
/* #Violation: can_hal_h_REF_1 */
#define CAN_PROTOCOL_ERROR_ACK          ((uint32)0x00000003U)   /* Acknowledge error                      */
/* #Violation: can_hal_h_REF_1 */
#define CAN_PROTOCOL_ERROR_BIT1         ((uint32)0x00000004U)   /* Bit 1 (recessive) error                */
/* #Violation: can_hal_h_REF_1 */
#define CAN_PROTOCOL_ERROR_BIT0         ((uint32)0x00000005U)   /* Bit 0 (dominant) error                 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_PROTOCOL_ERROR_CRC          ((uint32)0x00000006U)   /* CRC check sum error                    */
/* #Violation: can_hal_h_REF_1 */
#define CAN_PROTOCOL_ERROR_NO_CHANGE    ((uint32)0x00000007U)   /* No change since last read              */

/* ^CAN_ProtocolState^ CAN protocol state */
/* #Violation: can_hal_h_REF_1 */
#define CAN_PROTOCOL_LEC                ((uint32)0x00000007U)   /*Last Error Code                         */
/* #Violation: can_hal_h_REF_1 */
#define CAN_PROTOCOL_ACT                ((uint32)0x00000018U)   /*Activity                                */
/* #Violation: can_hal_h_REF_1 */
#define CAN_PROTOCOL_EP                 ((uint32)0x00000020U)   /*Error Passive                           */
/* #Violation: can_hal_h_REF_1 */
#define CAN_PROTOCOL_EW                 ((uint32)0x00000040U)   /*Warning Status                          */
/* #Violation: can_hal_h_REF_1 */
#define CAN_PROTOCOL_BO                 ((uint32)0x00000080U)   /*Bus_Off Status                          */
/* #Violation: can_hal_h_REF_1 */
#define CAN_PROTOCOL_DLEC               ((uint32)0x00000700U)   /*Data Last Error Code                    */
/* #Violation: can_hal_h_REF_1 */
#define CAN_PROTOCOL_RESI               ((uint32)0x00000800U)   /*ESI flag of last received CAN Message   */
/* #Violation: can_hal_h_REF_1 */
#define CAN_PROTOCOL_RBRS               ((uint32)0x00001000U)   /*BRS flag of last received CAN Message   */
/* #Violation: can_hal_h_REF_1 */
#define CAN_PROTOCOL_REDL               ((uint32)0x00002000U)   /*Received CAN Message                    */
/* #Violation: can_hal_h_REF_1 */
#define CAN_PROTOCOL_PXE                ((uint32)0x00004000U)   /*Protocol Exception Event                */
/* #Violation: can_hal_h_REF_1 */
#define CAN_PROTOCOL_TDCV               ((uint32)0x007F0000U)   /*Transmitter Delay Compensation Value    */

/* ^CAN_HpMsgStorage^ CAN high priority message storage */
/* #Violation: can_hal_h_REF_1 */
#define CAN_HP_STORAGE_NO_FIFO          ((uint32)0x00000000U)   /* No FIFO selected         */
/* #Violation: can_hal_h_REF_1 */
#define CAN_HP_STORAGE_MSG_LOST         ((uint32)0x00000001U)   /* FIFO message lost        */
/* #Violation: can_hal_h_REF_1 */
#define CAN_HP_STORAGE_RXFIFO0          ((uint32)0x00000002U)   /* Message stored in FIFO 0 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_HP_STORAGE_RXFIFO1          ((uint32)0x00000003U)   /* Message stored in FIFO 1 */

/* ^CAN_OperationStatus^ CAN Operation state */
/* #Violation: can_hal_h_REF_1 */
#define CAN_OP_STATE_NORMAL             ((uint32)0x00000000U)   /* Normal Operation                 */
/* #Violation: can_hal_h_REF_1 */
#define CAN_OP_STATE_INITIALIZE         ((uint32)0x00000001U)   /* Initialization is started        */

/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/

/* Can_Status, enumeration for the CAN function status  */
typedef enum
{
    CAN_STATUS_OK = 0U,     /* Status available*/

    CAN_STATUS_ERROR,       /* Status errors */

    CAN_STATUS_BUSY,        /* Status busy */

    CAN_STATUS_TIMEOUT,     /* operation timeout */

    CAN_STATUS_PARAM_ERROR /* Illegal parameter */

} Can_Status;

/* Can_FilterIDType, enumeration for CAN filter id type */
typedef enum
{
    CAN_FILTER_ID_TYPE_STANDARD  = 0U,      /* Standard identifier filter */

    CAN_FILTER_ID_TYPE_EXTENDED,            /* Extended identifier filter */

    CAN_FILTER_ID_TYPE_MIXED               /* Standard identifier filter + Extended identifier filter */

} Can_FilterIDType;

/* Can_FifoType, enumeration for CAN FIFO type */
typedef enum
{
    CAN_FIFO_TYPE_RXFIFO0  = 0U,      /* Rx FIFO0 */

    CAN_FIFO_TYPE_RXFIFO1,            /* Rx FIFO1 */

    CAN_FIFO_TYPE_TXFIFO,             /* Tx FIFO */

    CAN_FIFO_TYPE_TXEVENTFIFO,        /* Tx Event FIFO */

} Can_FifoType;

/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/

/* Structure for nominal baud rate */
/* #Violation: can_hal_h_REF_3 */
typedef struct
{
    uint32 syncJumpWidth;       /* Specifies the maximum number of time quanta the CAN
                                   hardware is allowed to lengthen or shorten a bit to perform
                                   re-synchronization.
                                   This parameter must be a number between 0 and 127. */

    uint32 prescaler;           /* Specifies the value by which the oscillator frequency is
                                   divided for generating the nominal bit time quanta.
                                   This parameter must be a number between 0 and 511. */

    uint32 timeSegment1;         /* Specifies the number of time quanta in Bit Segment 1.
                                    This parameter must be a number between 1 and 255. */

    uint32 timeSegment2;         /* Specifies the number of time quanta in Bit Segment 2.
                                    This parameter must be a number between 1 and 127. */

} Can_BaudRate;

/* Structure for fast baudrate and Transmission delay compensation parameters */
/* #Violation: can_hal_h_REF_3 */
typedef struct
{
    uint32 syncJumpWidth;      /* Specifies the maximum number of time quanta the CAN
                                  hardware is allowed to lengthen or shorten a data bit to
                                  perform re-synchronization.
                                  This parameter must be a number between 0 and 15. */

    uint32 prescaler;          /* Specifies the value by which the oscillator frequency is
                                  divided for generating the data bit time quanta.
                                  This parameter must be a number between 0 and 31. */

    uint32 timeSegment1;       /* Specifies the number of time quanta in Data Bit Segment 1.
                                  This parameter must be a number between 0 and 31. */

    uint32 timeSegment2;       /* Specifies the number of time quanta in Data Bit Segment 2.
                                  This parameter must be a number between 0 and 15. */

    uint8 compDlyOffset;       /* Transceiver delay compensation offset.
                                  This parameter must be a number between 0x00 and 0x7F. */

    uint8 compFilterWindow;    /* Transceiver delay compensation filter window length.
                                  This parameter must be a number between 0x00 and 0x7F. */

} Can_FastBaudRate;

/* Structure for CAN filter configuration */
/* #Violation: can_hal_h_REF_2 */
/* #Violation: can_hal_h_REF_3 */
typedef struct
{
    Can_FilterIDType  idType;  /* Specifies the filter index which will be initialized.
                                  This parameter must be a value of ref Can_FilterIDType */

    uint32  stdIndex;          /* Specifies the standard filter index.
                                  This parameter must be a number between:
                                  - 0 and 127, ID Type CAN_FILTER_ID_TYPE_STANDARD. */

    uint32  extIndex;          /* Specifies the extended filter index.
                                  This parameter must be a number between:
                                  - 0 and 63, ID Type is CAN_FILTER_ID_TYPE_EXTENDARD. */

    uint32  id1;               /* Specifies the filter identification 1.
                                  This parameter must be a number between:
                                   - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID.
                                   - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID. */

    uint32  id2;               /* Specifies the filter identification 2.
                                  This parameter is ignored if FilterConfig is set to
                                   FDCAN_FILTER_TO_RXBUFFER.
                                  This parameter must be a number between:
                                   - 0 and 0x7FF, if IdType is CAN_FILTER_ID_TYPE_STANDARD
                                                  or CAN_FILTER_ID_TYPE_MIXED.
                                   - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID
                                                  or  CAN_FILTER_ID_TYPE_MIXED. */
    uint8 elmConfig;           /* Specifies the filter type.
                                  This parameter can be a value of #REF CAN_FilterElmCfg. */

    uint8  type;               /*  Specifies the filter configuration.
                                   This parameter can be a value of #REF CAN_FilterType.
                                   This parameter is ignored if FilterConfig is set to
                                   CAN_FILTERELECFG_STORE_RXBUFFER. */

    uint8 rxBufferOffset;      /* Contains the index of the Rx buffer in which the
                                  matching message will be stored.
                                  This parameter must be a number between 0 and 63.
                                  This parameter is ignored if FilterConfig is different
                                  from CAN_FILTERELECFG_STORE_RXBUFFER. */
} Can_Filter;

/* Structure for CAN Tx header definition */
/* #Violation: can_hal_h_REF_2 */
/* #Violation: can_hal_h_REF_3 */
typedef struct
{
    uint32 identifier;            /* This identifier parameter must be a number between:
                                      - 0 and 0x7FF, if IdType is STANDARD_ID.
                                      - 0 and 0x1FFFFFFF, if IdType is EXTENDED_ID. */

    uint8 isErrorStateIndicator;  /* 0: transmitting is error passive.
                                     1: transmitting is error active */

    uint8 idType;                 /* Specifies the ID type. #REF Can_ID_Type. */

    uint8 frameType;              /* Specifies the Frame type. #REF CAN_FrameType */

    uint16 messageMarker;         /* Written by CPU during TX Buffer configuration.
                                     Copied into TX Event FIFO element for identification
                                         of TX message status.
                                     This parameter must be a number between 0 and 0xFFFF. */

    uint8 eventControl;          /*  Specifies the event control type.
                                     This parameter can be a value
                                       0: Don't store TX events.
                                       1: Store TX events. */

    uint8 FDFormat;              /* Specifies the FD format.This parameter can be a value
                                    This parameter can be a value:
                                     0: Classical CAN frame format.
                                     1: CAN FD frame format. */

    uint8 bitRateSwitch;         /* Specifies the bit rate switch.
                                    This parameter can be a value
                                      0: Frame received without bit rate switching.
                                      1: Frame received with bit rate switching. */

    uint32 dataLength;           /* Data length, only the following parameters are available
                                         #REF CAN_DataLengthCode. */

    uint8 immediatelySend;       /* Specifies the action if load the data into TX message RAM.
                                    This parameter is ignored if not for tx dedicated buffer.
                                     0: Dedicated TX buffer manual send.
                                     1: Dedicated TX buffer send immediately. */
} CAN_TxHeaderTypeDef;

/* Structure for CAN RX header definition */
/* #Violation: can_hal_h_REF_2 */
/* #Violation: can_hal_h_REF_3 */
typedef struct
{
    uint32 identifier;              /* This identifier parameter must be a number between:
                                       - 0 and 0x7FF, if IdType is STANDARD_ID.
                                       - 0 and 0x1FFFFFFF, if IdType is EXTENDED_ID. */

    uint8 isErrorStateIndicator;   /* Specifies error state indicator.
                                      This parameter can be:
                                       0: transmitting is error passive.
                                       1: transmitting is error active. */

    uint8 idType;                  /* Specifies the ID type. #REF Can_ID_Type
                                       0: Standard identifier.
                                       1:Extended identifier. */

    uint8 frameType;               /* Specifies the frame type. #REF CAN_FrameType
                                       0: data frame.
                                       1: Remote frame. */

    uint8 isFilterMatchingFrame;   /* Specifies the matching filter index.
                                      This parameter can be a value:
                                       0: Received frame matching filter index.
                                       1: Received frame did not match any RX filter element. */

    uint8 filterIndex;             /* The index of matching RX acceptance filter element.
                                      This parameter must be a number between:
                                       - 0 and 127, if IdType is CAN_STANDARD_ID.
                                       - 0 and 63, if IdType is CAN_EXTENDED_ID. */

    uint8 FDFormat;                /* Specifies the FD format.
                                      This parameter can be a value
                                       0: Classical CAN frame format.
                                       1: CAN FD frame format. */

    uint8 bitRateSwitch;           /* 0: Frame received without bit rate switching.
                                      1: Frame received with bit rate switching. */

    uint32 dataLength;             /* Data length, only the following parameters are available
                                      0~8,12,16,20,24,32,48,64. */

    uint32 rxTimestamp;            /* The time stamp counter value captured on
                                      start of frame reception. */

} CAN_RxHeaderTypeDef;

/* Structure for CAN Tx event header definition */
/* #Violation: can_hal_h_REF_2 */
/* #Violation: can_hal_h_REF_3 */
typedef struct
{
    uint32 identifier;            /* This identifier parameter must be a number between:
                                     - 0 and 0x7FF, if IdType is STANDARD_ID.
                                     - 0 and 0x1FFFFFFF, if IdType is EXTENDED_ID. */

    uint8 isErrorStateIndicator;  /* Specifies error state indicator.
                                     This parameter can be:
                                     0: transmitting is error passive.
                                     1: transmitting is error active. */

    uint8 idType;                 /* ID type. #REF Can_ID_Type
                                     This parameter can be:
                                     0: Standard identifier.
                                     1:Extended identifier. */

    uint8 frameType;              /* Frame type. #REF CAN_FrameType
                                     0: data frame.
                                     1: Remote frame. */

    uint8 FDFormat;               /* This parameter can be:
                                     0: Classical CAN frame format.
                                     1: CAN FD frame format. */

    uint8 bitRateSwitch;          /* This parameter can be:
                                     0: Frame received without bit rate switching.
                                     1: Frame received with bit rate switching. */

    uint32 dataLength;            /* Data length, only the following parameters are available
                                     0~8,12,16,20,24,32,48,64. */

    uint32 txTimestamp;           /* the time stamp counter value captured on start of frame reception */

    uint16 messageMarker;         /* Specifies the message marker copied into Tx Event FIFO element
                                     for identification of Tx message status.
                                     This parameter must be a number between 0 and 0xFFFF */

    uint8 eventType;              /* Specifies the event type.
                                     This parameter can be a value of #REF CAN_EventType. */

} CAN_TxEvenHeaderTypeDef;

/* Structure for CAN High Priority Message Status definition */
typedef struct
{
    uint8 filterList;     /* Specifies the filter list of the matching filter element.
                             This parameter can be:
                             - 0 : Standard Filter List.
                             - 1 : Extended Filter List. */

    uint8 filterIndex;    /* Specifies the index of matching filter element.
                             This parameter can be a number between:
                             - 0 and 127, if FilterList is 0 (Standard).
                             - 0 and 63, if FilterList is 1 (Extended). */

    uint8 messageStorage; /* Specifies the HP Message Storage.
                             This parameter can be a value of #ref CAN_HpMsgStorage. */

    uint8 messageIndex;   /* Specifies the Index of Rx FIFO element to which the
                             message was stored.
                             This parameter is valid only when MessageStorage is:
                             CAN_HP_STORAGE_RXFIFO0 or CAN_HP_STORAGE_RXFIFO1. */

} CAN_HpMsgStatusTypeDef;

/* Structure for CAN Error Counters structure definition */
/* #Violation: can_hal_h_REF_2 */
/* #Violation: can_hal_h_REF_3 */
typedef struct
{
    uint8 txErrorCnt;     /* Specifies the Transmit Error Counter Value.
                             This parameter can be a number between 0 and 255 . */

    uint8 rxErrorCnt;     /* Specifies the Receive Error Counter Value.
                             This parameter can be a number between 0 and 127. */

    uint8 rxErrorPassive; /* Specifies the Receive Error Passive status.
                             This parameter can be:
                             - 0 : The Receive Error Counter (RxErrorCnt) is below the error passive level of 128
                             - 1 : The Receive Error Counter (RxErrorCnt) has reached the error passive level of 128. */

    uint8 errorLogging;   /* Specifies the Transmit/Receive error logging counter value.
                             This parameter can be a number between 0 and 255.
                             This counter is incremented each time when a CAN protocol error causes the TxErrorCnt
                             or the RxErrorCnt to be incremented. The counter stops at 255; the next increment of
                             TxErrorCnt or RxErrorCnt sets interrupt flag CAN_IT_ERROVERFLOW. */

} CAN_ErrorCountersTypeDef;


/* Structure for message RAM configuration */
/* #Violation: can_hal_h_REF_3 */
typedef struct
{
    uint32 standardFilterSA; /* Specifies the Standard Filter List Start Address.
                                This parameter must be a 32-bit word address. */

    uint32 extendedFilterSA; /* Specifies the Extended Filter List Start Address.
                                This parameter must be a 32-bit word address. */

    uint32 rxFIFO0SA;        /* Specifies the Rx FIFO 0 Start Address.
                                This parameter must be a 32-bit word address. */

    uint32 rxFIFO1SA;        /* Specifies the Rx FIFO 1 Start Address.
                                This parameter must be a 32-bit word address. */

    uint32 rxBufferSA;       /* Specifies the Rx Buffer Start Address.
                                This parameter must be a 32-bit word address. */

    uint32 txEventFIFOSA;    /* Specifies the Tx Event FIFO Start Address.
                                This parameter must be a 32-bit word address. */

    uint32 txBufferSA;       /* Specifies the Tx Buffers Start Address.
                                This parameter must be a 32-bit word address. */

} Can_MessageRAM;

/* Structure for acceptance filter configuration*/
/* #Violation: can_hal_h_REF_3 */
typedef struct
{
    uint8 stdRejectRemoteFrame;     /* Specify whether to reject remote frames.
                                       This parameter must one of value #REF CAN_RejectRemoteFrames. */

    uint8 extRejectRemoteFrame;     /* Specify whether to reject remote frames.
                                       This parameter must one of value  #REF CAN_RejectRemoteFrames.*/

    uint8 stdNotMatch;              /* Defines how received messages with 11-bit IDs that
                                         do not match any element of the filter list are treated.
                                       This parameter can be value of #REF CAN_NonMatchingFrames. */

    uint8 extNotMatch;              /* Defines how received messages with 29-bit IDs that
                                         do not match any element of the filter list are treated.
                                       This parameter can be value of #REF CAN_NonMatchingFrames.*/

    uint32 stdFiltersNbr;           /* Specifies the number of standard Message ID filters.
                                       This parameter must be a number between 0 and 128. */

    uint32 extFiltersNbr;           /* Specifies the number of extended Message ID filters.
                                       This parameter must be a number between 0 and 64. */

} Can_FilterConfig;

/* Structure for Rx handle configuration*/
/* #Violation: can_hal_h_REF_3 */
typedef struct
{
    uint8 fifo0OperatingMode;     /* Specifies the Rx FIFO 0 operating mode.
                                     This parameter can be a value of #REF Can_RxFifoMode. */

    uint8 fifo1OperatingMode;     /* Specifies the Rx FIFO 1 operating mode.
                                     This parameter can be a value of #REF Can_RxFifoMode. */

    uint8 fifo0WatermarkLevel;    /* Specifies the Rx FIFO 0 watermark level
                                     This parameter must be a number between 0 and 64. */

    uint8 fifo1WatermarkLevel;    /* Specifies the Rx FIFO 1 watermark level
                                     This parameter must be a number between 0 and 64. */

    uint8 fifo0ElmtSize;          /* Specifies the Rx FIFO 0 data field size.
                                     This parameter can be a value of #REF Can_DataFieldSize. */

    uint8 fifo1ElmtSize;          /* Specifies the Data Field Size in an Rx FIFO 1 element.
                                     This parameter can be a value of #REF Can_DataFieldSize. */

    uint32 bufferElmSize;         /* Specifies the Data Field Size in an Rx Buffer element.
                                     This parameter can be a value of #REF Can_DataFieldSize. */

    uint32 buffersNbr;            /* Specifies the number of Dedicated Rx Buffer elements.
                                     This parameter must be a number between 0 and 64. */

    uint32 fifo0ElmtsNbr;         /* Specifies the number of Rx FIFO0 Elements.
                                     This parameter must be a number between 0 and 64. */

    uint32 fifo1ElmtsNbr;         /* Specifies the number of Rx FIFO1 Elements.
                                     This parameter must be a number between 0 and 64. */

} Can_RxConfig;

/* Structure for Tx handle configuration*/
/* #Violation: can_hal_h_REF_3 */
typedef struct
{
    uint8 fifoQueueMode;             /* Tx FIFO/Queue Mode selection.
                                        This parameter can be a value of #REF CAN_TxFifoQueueMode. */

    uint8 elmtSize;                  /* Specifies the Data Field Size in a Tx Element.
                                        This parameter can be a value of #REF Can_DataFieldSize. */

    uint32 buffersNbr;               /* Specifies the number of Dedicated Tx Buffers.
                                       This parameter must be a number between 0 and 32. */

    uint32 fifoQueueElmtsNbr;        /* Specifies the number of Tx Buffers used for Tx FIFO/Queue.
                                        This parameter must be a number between 0 and 32. */

    uint32 eventsNbr;                /* Specifies the number of Tx Event FIFO elements.
                                        This parameter must be a number between 0 and 32. */

    uint8 eventFifoWatermarkLevel;   /* Specifies the number of Transmit event FIFO water mark level
                                        This parameter must be a number between 0 and 32. */

} Can_TxConfig;

/* Structure for one node of XIDAM configuration */
typedef struct
{
    uint32 enable;      /* Enable or disable the XIDAM configuration.
                           This parameter can be set to CAN_ENABLE or CAN_DISABLE. */

    uint32 XIDAM;       /* Specifies the extended filter XIDAM mask value.
                           This parameter must be a number between 0 and 0x1FFF FFFF. */
} Can_XidamConfig;

/* Structure for the DMU request line node configuration */
typedef struct
{
    uint32 enableTX;    /* Enable or disable the DMU of TX.
                           This parameter can be set to CAN_ENABLE or CAN_DISABLE. */

    uint32 enableRX0;   /* Enable or disable the DMU of RX0.
                           This parameter can be set to CAN_ENABLE or CAN_DISABLE. */

    uint32 enableRX1;   /* Enable or disable the DMU of RX1.
                           This parameter can be set to CAN_ENABLE or CAN_DISABLE. */

    uint32 enableTXE;   /* Enable or disable the DMU of TXE.
                           This parameter can be set to CAN_ENABLE or CAN_DISABLE. */
} Can_ReqDmuLineConfig;

/* Structure for node handle configuration */
typedef struct
{
    uint8 frameFormat;                  /* Specifies the CAN frame format.
                                           This parameter can be a value of #ref CAN_FrameFormat. */

    uint8 opsMode;                      /* Specifies the CAN operating mode.
                                           This parameter can be a value of #ref CAN_OperationMode. */

    uint8 retransmission;              /* Specifies the automatic retransmission mode.
                                          This parameter can be set to CAN_ENABLE or CAN_DISABLE. */

    uint8 transmitPause;               /* Enable or disable the Transmit Pause feature.
                                          This parameter can be set to CAN_ENABLE or CAN_DISABLE. */

    uint8 protocolException;           /* Enable or disable the Protocol Exception Handling.
                                          This parameter can be set to CAN_ENABLE or CAN_DISABLE. */

    uint8 wideMessageMark;             /* Specifies the automatic wide message mark mode.
                                          This parameter can be set to CAN_ENABLE or CAN_DISABLE. */

    uint8 edgeFilter;                  /* Specifies edge filtering during Bus Integration.
                                          This parameter can be set to CAN_ENABLE or CAN_DISABLE. */

    uint32 messageRAMOffset;           /* Specifies the message RAM start address in this node.
                                          This parameter must be a number between 0 and (8192 * 4) byte.
                                          This parameter must be 4-byte aligned. */

    Can_BaudRate baudRate;             /* Classic CAN Baud Rate configuration.
                                          This parameter see #ref Can_BaudRate. */

    Can_FastBaudRate fdBaudRate;       /* Classic CAN Baud Rate configuration.
                                          This parameter see #ref Can_FastBaudRate. */

    Can_FilterConfig filterConfig;     /* Filter parameter configuration.
                                          This parameter see #ref Can_FilterConfig. */

    Can_XidamConfig xidamConfig;       /* XIDAM parameter configuration.
                                          This parameter see #ref Can_XIDAM_Cofnig. */

    Can_ReqDmuLineConfig dmuLineConfig;/* Request DMU line configuration.
                                          This parameter see #ref Can_ReqDmuLineConfig.
                                          Used for interacting with peripheral DMA.
                                          If DMA is not used, there is no need to configure it */

    Can_TxConfig txConfig;             /* Send parameter configuration.
                                          This parameter see #ref Can_TxConfig. */

    Can_RxConfig rxConfig;             /* Receive parameter configuration.
                                          This parameter see #ref Can_RxConfig. */

} Can_NodeConfig;

/* Structure for one node of tx FIFO status */
typedef struct
{
    boolean fifoMsgLost;   /* FIFO Message Lost, for tx event FIFO, rx FIFO0/1, except tx FIFO */

    uint8 fifoFull;        /* FIFO/Queue Full. */

    uint8 fifoPutIdx;      /* FIFO/Queue Put Index. */

    uint8 fifoGettIdx;     /* FIFO/Queue Get Index. */

    uint8 fifoFreeLevel;   /* FIFO Get Index */

} Can_FifoStatus;

/* Fast transmit header structure T0&T1 */
typedef struct
{
    /* #Violation: can_hal_h_REF_5 */
    uint64 identifier:29;            /* [28:0]  Identifier - RW  */
    /* #Violation: can_hal_h_REF_5 */
    uint64 frameType:1;              /* [29:29] Remote transmission request - RW  */
    /* #Violation: can_hal_h_REF_5 */
    uint64 idType:1;                 /* [30:30] Extended identifier - RW  */
    /* #Violation: can_hal_h_REF_5 */
    uint64 isErrorStateIndicator:1;  /* [31:31] Error state indicator - RW  */
    
    /* #Violation: can_hal_h_REF_5 */
    uint64 messageMarkerHigh:16;     /* [15:8]  Message marker high 8 bit, [7:0] reserved */
    /* #Violation: can_hal_h_REF_5 */
    uint64 dataLength:4;             /* [19:16] Data length code - RW  */
    /* #Violation: can_hal_h_REF_5 */
    uint64 bitRateSwitch:1;          /* [20:20] Bit rate switching - RW  */
    /* #Violation: can_hal_h_REF_5 */
    uint64 FDFormat:2;               /* [21:21] FD format - RW, [22:22]  Internal reserved  */
    /* #Violation: can_hal_h_REF_5 */
    uint64 eventControl:1;           /* [23:23] Event FIFO control - RW  */
    /* #Violation: can_hal_h_REF_5 */
    uint64 messageMarkerLow:8;       /* [31:24] Message marker low 8 bit - RW  */
} Can_TxHeaderBit;

/* Fast transmit header union */
typedef union
/* #Violation: can_hal_h_REF_4 */
{
    uint32 T[2];       /* Unsigned access */
    Can_TxHeaderBit B;    /* Bitfield access */
} CAN_TxHeaderPack;

/* Fast receive header R0&R1A/B */
typedef struct
{
    /* #Violation: can_hal_h_REF_5 */
    uint64 identifier:29; /* [28:0] Identifier - RW  */
    /* #Violation: can_hal_h_REF_5 */
    uint64 frameType:1; /* [29:29] Remote transmission request - RW  */
    /* #Violation: can_hal_h_REF_5 */
    uint64 idType:1; /* [30:30] Extended identifier - RW  */
    /* #Violation: can_hal_h_REF_5 */
    uint64 isErrorStateIndicator:1; /* [31:31] Error state indicator - RW  */

    /* #Violation: can_hal_h_REF_5 */
    uint64 rxTimestamp:16;       /* [15:0] Rx time stamp for R1A only - RW  */
    /* #Violation: can_hal_h_REF_5 */
    uint64 dataLength:4;         /* [19:16] Data length code - RW  */
    /* #Violation: can_hal_h_REF_5 */
    uint64 bitRateSwitch:1;      /* [20:20] Bit rate switch - RW  */
    /* #Violation: can_hal_h_REF_5 */
    uint64 FDFormat:3;           /* [21:21] Frame data format - RW, [23:22]  Internal reserved  */
    /* #Violation: can_hal_h_REF_5 */
    uint64 filterIndex:7;        /* [30:24] Filter index - RW  */
    /* #Violation: can_hal_h_REF_5 */
    uint64 isFilterMatchingFrame:1;        /* [31:31] Accepted non-matching frame - RW  */
} Can_RxHeaderBit;

/*  Fast receive header union */
typedef union
/* #Violation: can_hal_h_REF_4 */
{
    uint32 R[2];          /* Unsigned access */
    Can_RxHeaderBit B;    /* Bitfield access */
} CAN_RxHeaderPack;

/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/

#define CAN_START_SEC_CODE_ASIL_D_GLOBAL
#include "Can_MemMap.h"

/**********************************************************************************************************************
 * Function:     Can_Hal_ModuleRamClear
 * Description:  Clear CAN module1\2 RAM zero
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       Can_Status: The execution status
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/05    01107      Create
 *********************************************************************************************************************/
extern Can_Status Can_Hal_ModuleRamClear(void);

/**********************************************************************************************************************
 * Function:     Can_Hal_Init
 * Description:  CAN node initialization
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When initializing different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register.
 *               cfg: Specify a pointer of structure Can_NodeConfig.
 * Inout:        None
 * Output:       msgEndAddress: message end RAM address which is the relative offset address of this module's RAM.
 * Return:       Can_Status: The execution status
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/05    01107      Create
 *********************************************************************************************************************/
extern Can_Status Can_Hal_Init(CAN_NODE *const pNode, const Can_NodeConfig *const cfg, uint32 *const msgEndAddress);

/**********************************************************************************************************************
 * Function:     Can_Hal_Deinit
 * Description:  CAN de-initialize
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register.
 * Inout:        None
 * Output:       None
 * Return:       Can_Status: The execution status
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/05    01107      Create
 *********************************************************************************************************************/
extern Can_Status Can_Hal_Deinit(CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Hal_EnterPowerDownMode
 * Description:  Enter CAN peripheral in sleep mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register.
 * Inout:        None
 * Output:       None
 * Return:       Can_Status: The execution status
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/05    01107      Create
 *********************************************************************************************************************/
extern Can_Status Can_Hal_EnterPowerDownMode(CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Hal_ExitPowerDownMode
 * Description:  Exit power down mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register.
 * Inout:        None
 * Output:       None
 * Return:       Can_Status: The execution status
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/05    01107      Create
 *********************************************************************************************************************/
extern Can_Status Can_Hal_ExitPowerDownMode(CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Hal_GetPowerStatus
 * Description:  get CAN power status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pNode: Specify a pointer to the CAN node register
 * Inout:        None
 * Output:       None
 * Return:       uint32: CAN is asleep or not #arg CAN_SleepStatus
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/08    01107      Create
 *********************************************************************************************************************/
extern uint32 Can_Hal_GetPowerStatus(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Hal_ConfigWideMessageMark
 * Description:  Enable\Disable wide message mark
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               enable: CAN_ENABLE\CAN_DISABLE
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       Call Can_Hal_EnterInitMode() to unlock protection before Can_Hal_ConfigWideMessageMark()
 * History:
 *  Date          Author    Modified
 *  2023/09/17    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_ConfigWideMessageMark(CAN_NODE *const pNode, uint32 enable);

/**********************************************************************************************************************
 * Function:     Can_Hal_ConfigAutomaticRetransmission
 * Description:  Enable\Disable Automatic Retransmission.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               enable: CAN_ENABLE\CAN_DISABLE
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       Call Can_Hal_EnterInitMode() to unlock protection before Can_Hal_ConfigAutomaticRetransmission()
 * History:
 *  Date          Author    Modified
 *  2023/09/17    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_ConfigAutomaticRetransmission(CAN_NODE *const pNode, uint32 enable);

/**********************************************************************************************************************
 * Function:     Can_Hal_ConfigFrameFormat
 * Description:  Sets frame format for CAN
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               frameFormat: see structure #arg Can_FrameFormat
 *
 * Inout:        None
 * Output:       None
 * Return:       Can_Status: The execution status
 * Others:       Call Can_Hal_EnterInitMode() to unlock protection before Can_Hal_ConfigFrameFormat()
 * History:
 *  Date          Author    Modified
 *  2023/09/05    01107      Create
 *********************************************************************************************************************/
extern Can_Status Can_Hal_ConfigFrameFormat(CAN_NODE *const pNode, uint32 frameFormat);

/**********************************************************************************************************************
 * Function:     Can_Hal_ConfigBaudrate
 * Description:  Sets Baud Rate for the Standard CAN
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               pBaudRate: pointer Structure Baud Rate
 *
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/05    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_ConfigBaudrate(CAN_NODE *const pNode, const Can_BaudRate *const pBaudRate);

/**********************************************************************************************************************
 * Function:     Can_Hal_ConfigFastBaudrate
 * Description:  Sets Baud Rate for the Fast FD-CAN
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               pFastBaudRate: Pointer structure Baud Rate for CANFD
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/05    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_ConfigFastBaudrate(CAN_NODE *const pNode, const Can_FastBaudRate *const pFastBaudRate);

/**********************************************************************************************************************
 * Function:     Can_Hal_ConfigOperationMode
 * Description:  Set Operation Mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               mode: see CAN_OPERATION_MODE type
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/08    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_ConfigOperationMode(CAN_NODE *const pNode, uint32 mode);

/**********************************************************************************************************************
 * Function:     Can_Hal_ConfigTransmissionPause
 * Description:  Enable\Disable transmission Pause
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               enable: CAN_ENABLE\CAN_DISABLE
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       Call Can_Hal_EnterInitMode() to unlock protection before Can_Hal_ConfigTransmissionPause()
 * History:
 *  Date          Author    Modified
 *  2023/09/08    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_ConfigTransmissionPause(CAN_NODE *const pNode, boolean enable);

/**********************************************************************************************************************
 * Function:     Can_Hal_InitMessageRam
 * Description:  initialize rx message RAM
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               pFilterConfig: pointer Structure of filter configuration
 *               pRxConfig: pointer Structure of tx configuration
 *               pTxConfig: pointer Structure of tx configuration
 *               pMessageRam: Pointer message RAM
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/14    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_InitMessageRam(CAN_NODE *const pNode,
                                      const Can_FilterConfig *const pFilterConfig,
                                      const Can_RxConfig *const pRxConfig,
                                      const Can_TxConfig *const pTxConfig,
                                      const Can_MessageRAM *const pMessageRam);

/**********************************************************************************************************************
 * Function:     Can_Hal_ConfigureFilter
 * Description:  Configure the CAN global filter.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               pFilter: Specify a pointer to the filter parameter
 * Inout:        None
 * Output:       None
 * Return:       Can_Status: The execution status
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/05    01107      Create
 *********************************************************************************************************************/
extern Can_Status Can_Hal_ConfigureFilter(const CAN_NODE *const pNode, const Can_Filter *const pFilter);
/**********************************************************************************************************************
 * Function:     Can_Hal_ConfigExtendedFilterXIDAM
 * Description:  Set the extended ID and Mask.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 *               mask: Extended ID Mask
 *                     This parameter can be a value between 0U and 0x1FFFFFFU
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_ConfigExtendedFilterXIDAM(CAN_NODE *const pNode, uint32 mask);

/**********************************************************************************************************************
 * Function:     Can_Hal_ConfigFifoWatermark
 * Description:  Configure the FIFO watermark.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               fifoType: select the FIFO to be configured.
 *               This parameter can be a value of #arg CAN_FifoWatermark.
 *               watermark: level for FIFO watermark interrupt.
 *               This parameter must be a number between
 *               - 0 and 32, if FIFO is CAN_CFG_TX_EVENT_FIFO
 *               - 0 and 64, if FIFO is CAN_CFG_RX_FIFO0 or CAN_CFG_RX_FIFO1
 * Inout:        None
 * Output:      None
 * Return:      Can_Status: The execution status
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/05   01107      Create
 *********************************************************************************************************************/
extern Can_Status Can_Hal_ConfigFifoWatermark(CAN_NODE *const pNode, uint32 fifoType, uint32 watermark);

/**********************************************************************************************************************
 * Function:     Can_Hal_ConfigExternalTimestamp
 * Description:  Configure the external time stamp counter.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               timeStampUnit: time stamp unit.
 *               This parameter must be a number between 0 and 32767
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/013   01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_ConfigExternalTimestamp(CAN_NODE *const pNode, uint32 timeStampUnit);

/**********************************************************************************************************************
 * Function:     Can_Hal_ConfigInternalTimestamp
 * Description:  Configure the internal time stamp counter.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               timestampPrescaler: Time stamp Counter prescaler.
 *               This parameter can be a value of #arg CAN_InternalTimestampPrescaler.
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/05    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_ConfigInternalTimestamp(CAN_NODE *const pNode, uint32 timestampPrescaler);

/**********************************************************************************************************************
 * Function:     Can_Hal_StartTimestampCounter
 * Description:  Start the time stamp counter.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               timestampOperation: Times tamp counter operation.
 *               This parameter can be a value of #arg CAN_TimestampOperation.
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/05    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_StartTimestampCounter(CAN_NODE *const pNode, uint32 timestampOperation);

/**********************************************************************************************************************
 * Function:     Can_Hal_StopTimestampCounter
 * Description:  Disable the time stamp counter.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/05    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_StopTimestampCounter(CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Hal_GetTimestampCounter
 * Description:  Get the time stamp counter value.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pNode: Specify a pointer to the CAN node register
 *
 * Inout:        None
 * Output:       None
 * Return:       uint32: The time stamp counter
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/05    01107      Create
 *********************************************************************************************************************/
extern uint32 Can_Hal_GetTimestampCounter(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Hal_ResetTimestampCounter
 * Description:  Reset the time stamp counter to zero.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/05    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_ResetTimestampCounter(CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Hal_ConfigTimeoutCounter
 * Description:  Configure the time out counter.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               timeoutOperation: Timeout counter operation.
 *               This parameter can be a value of #arg CAN_TimeoutOperation.
 *               timeoutPeriod: Start value of the timeout down-counter.
 *               This parameter must be a number between 0x0000 and 0xFFFF
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/05    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_ConfigTimeoutCounter(CAN_NODE *const pNode, uint32 timeoutOperation, uint32 timeoutPeriod);

/**********************************************************************************************************************
 * Function:     Can_Hal_StartTimeoutCounter
 * Description:  Start the timestamp counter.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/05    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_StartTimeoutCounter(CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Hal_StopTimeoutCounter
 * Description:  Stop the time stamp counter.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/05    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_StopTimeoutCounter(CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Hal_GetTimeoutCounter
 * Description:  Get the timeout counter value.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pNode: Specify a pointer to the CAN node register
 *
 * Inout:        None
 * Output:       None
 * Return:       uint32: The timeout counter value
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/05    01107      Create
 *********************************************************************************************************************/
extern uint32 Can_Hal_GetTimeoutCounter(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Hal_ResetTimeoutCounter
 * Description:  Reset the timeout counter to its start value.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/05    01107      Create
 *********************************************************************************************************************/
extern void Can_Hal_ResetTimeoutCounter(CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Hal_ConfigTxDelayCompensation
 * Description:  Configure the transmitter delay compensation.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               offset: Transmitter Delay Compensation Offset.
 *               This parameter must be a number between 0x00 and 0x7F.
 *               filter: Transmitter Delay Compensation Filter Window Length.
 *               This parameter must be a number between 0x00 and 0x7F.
 *               enable: CAN_ENABLE\CAN_DISABLE
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/05    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_ConfigTxDelayCompensation(CAN_NODE *const pNode, uint32 offset, uint32 filter, uint32 enable);

/**********************************************************************************************************************
 * Function:     Can_Hal_EnterInitMode
 * Description:  Stop the CAN module and enable access to configuration registers.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 * Inout:        None
 * Output:       None
 * Return:       Can_Status: The execution status
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/05    01107      Create
 *********************************************************************************************************************/
extern Can_Status Can_Hal_EnterInitMode(CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Hal_ExitInitMode
 * Description:  Disable configure and start the CAN module.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 * Inout:        None
 * Output:       None
 * Return:       Can_Status: The execution status
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/05   01107      Create
 *********************************************************************************************************************/
extern Can_Status Can_Hal_ExitInitMode(CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Hal_WriteMessage
 * Description:  Add a message to the TX FIFO/Queue and activate the corresponding transmission request
 *               Add a message to a dedicated TX buffer(Note, Require manual request to send)
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               txLocation: FIFO\QUEUE or dedicated TX buffer number #arg CAN_TxLocation
 *               pTxHeader: CAN_TxHeaderTypeDef structure.
 *               pTxData: pointer to a buffer containing the pay-load of the TX frame.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/03    01107      Create
 *********************************************************************************************************************/
extern void Can_Hal_WriteMessage(CAN_NODE *const pNode, uint32 txLocation, const CAN_TxHeaderTypeDef *const pTxHeader,
                                    const uint8 *const pTxData);

/**********************************************************************************************************************
 * Function:     Can_Hal_WriteMessageDMA
 * Description:  Add a message to the TX FIFO/Queue header,and output data pointer.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pNode: Specify a pointer to the CAN node register
 *               srcAddress: Specify a source address write by DMA to DMU.
 *               pTxHeader: Specify a pointer to a CAN_TxHeaderTypeDef structure.
 * Inout:        None
 * Output:       pTxData: Specify a pointer to a buffer containing the pay-load of the TX frame.
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/03    01107      Create
 *********************************************************************************************************************/
extern void Can_Hal_WriteMessageDMA(const CAN_NODE *const pNode, uint32 srcAddress,
                                    const CAN_TxHeaderTypeDef *const pTxHeader, uint8 **const pTxData);

/**********************************************************************************************************************
 * Function:     Can_Hal_FastWriteMessage
 * Description:  Fast add a message to the TX FIFO/Queue and activate the corresponding transmission request
 *               Fast add a message to a dedicated TX buffer
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               txLocation: FIFO\QUEUE or dedicated TX buffer number #arg CAN_TxLocation
 *               pTxHeader: CAN_TxHeaderPack union.
 *               pTxData: pointer to a buffer containing the pay-load of the TX frame.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/03    01107      Create
 *********************************************************************************************************************/
extern void Can_Hal_FastWriteMessage(CAN_NODE *const pNode, uint32 txLocation,  CAN_TxHeaderPack *const pTxHeader,
                          const uint8 *const pTxData);

/**********************************************************************************************************************
 * Function:     Can_Hal_GetTxBufferPendingStatus
 * Description:  Get the pending Data flags
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pNode: Specify a pointer to the CAN node register
 *               bufferIndex: dedicated TX buffer number #arg CAN_TxLocation
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE is pending, FALSE is not pending
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/03    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_GetTxBufferPendingStatus(const CAN_NODE *const pNode, uint32 bufferIndex);

/**********************************************************************************************************************
 * Function:     Can_Hal_GetTxBufferTransFinishedStatus
 * Description:  Get the successful transmission flags
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pNode: Specify a pointer to the CAN node register
 *               bufferIndex: dedicated TX buffer number #arg CAN_TxLocation
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE is transfer successful, FALSE is transfer fail.
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/03    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_GetTxBufferTransFinishedStatus(const CAN_NODE *const pNode, uint32 bufferIndex);

/**********************************************************************************************************************
 * Function:     Can_Hal_GetTxBufferAbortFinishedStatus
 * Description:  Get the successful abort finished flags
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pNode: Specify a pointer to the CAN node register
 *               bufferIndex: dedicated TX buffer number #arg CAN_TxLocation
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE is transfer abort successful, FALSE is transfer abort fail.
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/03    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_GetTxBufferAbortFinishedStatus(const CAN_NODE *const pNode, uint32 bufferIndex);

/**********************************************************************************************************************
 * Function:     Can_Hal_TxBufferRequest
 * Description:  Enable transmission request.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pNode: Specify a pointer to the CAN node register
 *               bufferIndex: the dedicated TX buffer number #arg CAN_TxLocation
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/03    01107      Create
 *********************************************************************************************************************/
extern void Can_Hal_TxBufferRequest(CAN_NODE *const pNode, uint32 bufferIndex);

/**********************************************************************************************************************
 * Function:     Can_Hal_AbortTxRequest
 * Description:  Abort transmission request
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pNode: Specify a pointer to the CAN node register
 *               bufferIndex: the dedicated TX buffer number #arg CAN_TxLocation
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/03    01107      Create
 *********************************************************************************************************************/
extern void Can_Hal_AbortTxRequest(CAN_NODE *const pNode, uint32 bufferIndex);

/**********************************************************************************************************************
 * Function:     Can_Hal_ClearMessageFlag
 * Description:  Clear transmission and receive message flag.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/05   01107      Create
 *********************************************************************************************************************/
extern void Can_Hal_ClearMessageFlag(CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Hal_GetRxBufferMessageAvailableStatus
 * Description:  Get the New Data flags of the dedicated RX buffer
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pNode: Specify a pointer to the CAN node register
 *               bufferIndex: the dedicated RX buffer bit 0 ~ 63 #REF CAN_RxLocation
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE is available, FALSE is not available.
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/03    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_GetRxBufferMessageAvailableStatus(const CAN_NODE *const pNode, uint32 bufferIndex);

/**********************************************************************************************************************
 * Function:     Can_Hal_GetRxBufferMessageIndex
 * Description:  Get the New Data bit of the dedicated RX buffer
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pNode: Specify a pointer to the CAN node register
 * Inout:        None
 * Output:       None
 * Return:       uint64: New Data bit.
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/03    00976      Create
 *********************************************************************************************************************/
extern uint64 Can_Hal_GetRxBufferMessageIndex(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Hal_ReadMessage
 * Description:  Get an CAN frame from the Rx Buffer/FIFO zone into the message RAM.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               rxLocation: Location of the received message to be read.
 *                  This parameter can be a value of #arg CAN_RxLocation.
 * Inout:        None
 * Output:       pRxHeader: Specify a pointer to a CAN_RxHeaderTypeDef structure.
 *               pRxData: Specify a pointer to a buffer where the payload of the Rx frame will be stored.
 * Return:       Can_Status: The execution status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/03    01107      Create
 *********************************************************************************************************************/
extern Can_Status Can_Hal_ReadMessage(CAN_NODE *const pNode, uint32 rxLocation, CAN_RxHeaderTypeDef *const pRxHeader,
        uint8 *const pRxData);

/**********************************************************************************************************************
 * Function:     Can_Hal_ReadMessageDMA
 * Description:  Parse an Rx header from pSrcAddress content and get payload pointer
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        srcAddress: Specify a source address read by DMA from DMU.
 * Inout:        None
 * Output:       pRxHeader: Specify a pointer to a CAN_RxHeaderTypeDef structure.
 *               pRxData: Specify a pointer to a buffer where the payload of the Rx frame will be stored.
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/12/26    01107      Create
 *********************************************************************************************************************/
extern void Can_Hal_ReadMessageDMA(uint32 srcAddress, CAN_RxHeaderTypeDef *const pRxHeader, uint8 **const pRxData);


/**********************************************************************************************************************
 * Function:     Can_Hal_FastReadMessage
 * Description:  Fast get an CAN frame from the Rx Buffer/FIFO zone into the message RAM.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               rxLocation: Location of the received message to be read.
 *                  This parameter can be a value of #arg CAN_RxLocation.     
 * Inout:        None
 * Output:       pRxHeader: Specify a pointer to a CAN_RxHeaderPack union.
 *               pRxData: Specify a pointer to a buffer where the payload of the Rx frame will be stored.
 * Return:       Can_Status: The execution status
 * Others:       The user-defined pRxData pointed data buffer address must be word aligned, and buffer size must be 64 bytes.
 * History:
 *  Date          Author    Modified
 *  2023/09/03    00976      Create
 *********************************************************************************************************************/
extern Can_Status Can_Hal_FastReadMessage(CAN_NODE *const pNode, uint32 rxLocation, CAN_RxHeaderPack *const pRxHeader, uint8 *const pRxData);


/**********************************************************************************************************************
 * Function:     Can_Hal_ReadTxEvent
 * Description:  Get an CAN Tx event from the Tx Event FIFO zone into the message RAM.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 * Inout:        pEvHeader: pointer to a CAN_TxEventFifoTypeDef structure.
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/03    01107      Create
 *********************************************************************************************************************/
extern void Can_Hal_ReadTxEvent(CAN_NODE *const pNode, CAN_TxEvenHeaderTypeDef *const pEvHeader);

/**********************************************************************************************************************
 * Function:     Can_Hal_ReadTxEventDMA
 * Description:  Parse an CAN Tx event from pSrcAddress content
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pNode: Specify a pointer to the CAN node register
 *               srcAddress: Specify a source data address.
 * Inout:        None
 * Output:       pEvHeader: Specify a pointer to a CAN_TxEventFifoTypeDef structure.
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/12/29    01107      Create
 *********************************************************************************************************************/
extern void Can_Hal_ReadTxEventDMA(const CAN_NODE *const pNode, uint32 srcAddress, CAN_TxEvenHeaderTypeDef *const pEvHeader);

/**********************************************************************************************************************
 * Function:     Can_Hal_GetHighPriorityMessageStatus
 * Description:  Get high priority message status.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pNode: Specify a pointer to the CAN node register
 * Inout:        None
 * Output:       pHpMsgStatus: pointer to an CAN_HpMsgStatusTypeDef structure.
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/03    01107      Create
 *********************************************************************************************************************/
extern void Can_Hal_GetHighPriorityMessageStatus(const CAN_NODE *const pNode, CAN_HpMsgStatusTypeDef *const pHpMsgStatus);

/**********************************************************************************************************************
 * Function:     Can_Hal_GetProtocolStatus
 * Description:  Get protocol status.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pNode: Specify a pointer to the CAN node register
 *               protocolStatus pointer to an CAN_ProtocolStatusTypeDef structure.
 * Inout:        None
 * Output:       None
 * Return:       uint32: The protocol state, arg CAN_ProtocolState
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/03    01107      Create
 *********************************************************************************************************************/
extern uint32 Can_Hal_GetProtocolStatus(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Hal_GetOperationStatus
 * Description:  Get Controller Operation status.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pNode: Specify a pointer to the CAN node register
 *               protocolStatus pointer to an CAN_ProtocolStatusTypeDef structure.
 * Inout:        None
 * Output:       None
 * Return:       uint32: The protocol state, arg CAN_ProtocolState
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/09/16    00949      Create
 *********************************************************************************************************************/
extern uint32 Can_Hal_GetOperationStatus(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:    Can_Hal_GetErrorCounters
 * Description: Get error counter values.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:       pNode: Specify a pointer to the CAN node register
 * Inout:       pErrorCounters: pointer to an CAN_ErrorCountersTypeDef structure.
 * Output:      None
 * Return:      None
 * Others:      None
 * History:
 *  Date          Author    Modified
 *  2023/09/03    01107      Create
 *********************************************************************************************************************/
extern void Can_Hal_GetErrorCounters(const CAN_NODE *const pNode, CAN_ErrorCountersTypeDef *const pErrorCounters);

/**********************************************************************************************************************
 * Function:     Can_Hal_GetTxEventFifoLevel
 * Description:  Get Event FIFO fill level
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pNode: Specify a pointer to the CAN node register
 * Inout:        None
 * Output:       None
 * Return:       uint32: The event FIFO fill level
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/05    00949      Create
 *********************************************************************************************************************/
extern uint32 Can_Hal_GetTxEventFifoLevel(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:    Can_Hal_GetRxFifo0FillLevel
 * Description: Get Rx FIFO 0 fill Level
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:       pNode: Specify a pointer to the CAN node register
 * Inout:        None
 * Output:      None
 * Return:      uint32: The Rx FIFO 0 fill Level
 * Others:      None
 * History:
 *  Date          Author    Modified
 *  2023/09/03    01107      Create
 *********************************************************************************************************************/
extern uint32 Can_Hal_GetRxFifo0FillLevel(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:    Can_Hal_GetRxFifo1FillLevel
 * Description: Get Rx FIFO 1 fill Level
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:       pNode: Specify a pointer to the CAN node register
 * Inout:        None
 * Output:      None
 * Return:      uint32: Rx FIFO 1 fill Level
 * Others:      None
 * History:
 *  Date          Author    Modified
 *  2023/09/03    01107      Create
 *********************************************************************************************************************/
extern uint32 Can_Hal_GetRxFifo1FillLevel(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:    Can_Hal_GetTxFifoFreeLevel
 * Description: Get Tx FIFO free Level
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:       pNode: Specify a pointer to the CAN node register
 * Inout:        None
 * Output:      None
 * Return:      uint32: The Tx FIFO free Level
 * Others:      None
 * History:
 *  Date          Author    Modified
 *  2023/09/03    01107      Create
 *********************************************************************************************************************/
extern uint32 Can_Hal_GetTxFifoFreeLevel(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:    Can_Hal_GetFifoStatus
 * Description: Get FIFO status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:       pNode: Specify a pointer to the CAN node register
 *              fifoType: Specify FIFO type
 * Inout:       fifoSta: The pointer to specified FIFO status
 * Output:      None
 * Return:      None
 * Others:      None
 * History:
 *  Date          Author    Modified
 *  2025/06/03    00976      Create
 *********************************************************************************************************************/
extern void Can_Hal_GetFifoStatus(const CAN_NODE *const pNode, Can_FifoType fifoType, Can_FifoStatus* fifoSta);

/**********************************************************************************************************************
 * Function:    Can_Hal_IsRestrictedOperationMode
 * Description: Check if it is in restricted working mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:       pNode: Specify a pointer to the CAN node register
 * Inout:        None
 * Output:      None
 * Return:      uint32: TRUE is restricted working mode. FALSE is normal working mode
 * Others:      None
 * History:
 *  Date          Author    Modified
 *  2023/09/03    01107      Create
 *********************************************************************************************************************/
extern uint32 Can_Hal_IsRestrictedOperationMode(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:    Can_Hal_ExitRestrictedOperationMode
 * Description: Exit restricted working mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:       pNode: Specify a pointer to the CAN node register
 * Inout:        None
 * Output:      None
 * Return:      boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:      None
 * History:
 *  Date          Author    Modified
 *  2023/09/03    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_ExitRestrictedOperationMode(CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Hal_SelectInterruptLine
 * Description:  Select interrupt line
 *               Note: This function for line0\1 interrupt(not router IT).
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               it: interrupt type, see #arg CAN_IT_Flags
 *               itLine: Interrupt line number(0 ~ 1), see #arg CAN_IT_LINES_FLAGS
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/10/25    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_SelectInterruptLine(CAN_NODE *const pNode,  uint32 it, uint32 itLine);

/**********************************************************************************************************************
 * Function:     Can_Hal_SelectRouterInterruptLine
 * Description:  Select interrupt router line
 *               Note: This function for router interrupt.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               it: Type of Interrupt, see #arg CAN_IT_Flags
 *               itLine: Interrupt line number(0 ~ 15), see #arg CAN_IT_ROUTER_LINES_FLAGS
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/08    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_SelectRouterInterruptLine(CAN_NODE *const pNode, uint32 it, uint32 itLine);

/**********************************************************************************************************************
 * Function:     Can_Hal_EnableRouterInterrupt
 * Description:  enable the selected router interrupt
 *               Note: This function for router interrupt.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               it: Type of interrupt
 *               bufferIndexes: Tx Buffer Indexes.
 *                 This parameter can be any combination of #arg CAN_Tx_location.
 *                 This parameter is ignored if it does not include one of the following
 *                     - CAN_IT_TX_COMPLETE
 *                     - CAN_IT_TX_ABORT_COMPLETE
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/05    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_EnableRouterInterrupt(CAN_NODE *const pNode, uint32 it, uint32 bufferIndexes);

/**********************************************************************************************************************
 * Function:     Can_Hal_DisableRouterInterrupt
 * Description:  disable the selected router interrupt
 *               Note: This function for router interrupt.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               it: Type of interrupt
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/05    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_DisableRouterInterrupt(CAN_NODE *const pNode, uint32 it);

/**********************************************************************************************************************
 * Function:     Can_Hal_GetInterruptFlag
 * Description:  get the selected interrupt flag
 *               Note: This function for MCAN and router interrupt.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pNode: Specify a pointer to the CAN node register
 * Inout:        None
 * Output:       None
 * Return:       uint32: The status of interrupt flag is interrupt flag by setting up or not
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/05    01107      Create
 *********************************************************************************************************************/
extern uint32 Can_Hal_GetInterruptFlag(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Hal_ClearInterruptFlag
 * Description:  Clear the selected interrupt flag
 *               Note: This function for MCAN and router interrupt.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               it: interrupt type
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/05    01107      Create
 *********************************************************************************************************************/
extern void Can_Hal_ClearInterruptFlag(CAN_NODE *const pNode, uint32 it);

/**********************************************************************************************************************
 * Function:     Can_Hal_EnableInterrupt
 * Description:  Enable interrupts for CAN
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               it: indicates which interrupts will be enabled.
 *                 This parameter can be any combination of #arg CAN_IT_Flags.
 *               bufferIndexes: Tx Buffer Indexes.
 *                 This parameter can be any combination of #arg CAN_Tx_location.
 *                 This parameter is ignored if it does not include one of the following
 *                     - CAN_IT_TX_COMPLETE
 *                     - CAN_IT_TX_ABORT_COMPLETE
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/06    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_EnableInterrupt(CAN_NODE *const pNode, uint32 it, uint32 bufferIndexes);

/**********************************************************************************************************************
 * Function:     Can_Hal_DisableInterrupt
 * Description:  Disable interrupts for MACN.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               it: indicates which interrupts will be enabled.
 *                 This parameter can be any combination of #arg CAN_IT_Flags.
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/06    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_DisableInterrupt(CAN_NODE *const pNode, uint32 it);

/**********************************************************************************************************************
 * Function:     Can_Hal_GetDmuAddress
 * Description:  Get DMU TX\TXE\RX0\RX1 element base address
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pNode: Specify a pointer to the CAN node register
 *               dmuAddressType: DMU TX\TXE\RX0\RX1 element type.
 *                 This parameter can be a value of #arg CAN_DMU_AddressType.
 * Inout:        None
 * Output:       None
 * Inout         elementAddress: Specify a pointer to out element address.
 * Return:       Can_Status: The execution status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/12/20    01107      Create
 *********************************************************************************************************************/
extern Can_Status Can_Hal_GetDmuAddress(const CAN_NODE *const pNode, uint32 dmuAddressType, uint32 *const elementAddress);

/**********************************************************************************************************************
 * Function:     Can_Hal_DmuRequestLine
 * Description:  Enable\Disable DMU request.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specify a pointer to the CAN node register
 *               dmuRequestType: indicates which DMU type will be operated.
 *                 This parameter can be a value of #arg CAN_DMU_RequestType.
 *               enable: CAN_ENABLE is enable line, CAND_DISABLE is disable line.
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/12/20    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_DmuRequestLine(CAN_NODE *const pNode, uint32 dmuRequestType, boolean enable);

/**********************************************************************************************************************
 * Function:     Can_Hal_GetDmuInterruptFlag
 * Description:  Get DMU IR flag
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: DMU interrupt flag #arg CAN_IT_DMU_Flags
 * Others:
 * History:
 *  Date         Author    Modified
 *  2024/01/02   01107      Create
 *********************************************************************************************************************/
extern uint32 Can_Hal_GetDmuInterruptFlag(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Hal_ClearDmuInterruptFlag
 * Description:  Clear the interrupt of DMU IR
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               it: DMU interrupt #arg CAN_IT_DMU_Flags
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date         Author    Modified
 *  2024/01/02   01107      Create
 *********************************************************************************************************************/
extern void Can_Hal_ClearDmuInterruptFlag(CAN_NODE *const pNode, uint32 it);

/**********************************************************************************************************************
 * Function:     Can_Hal_EnableDmuInterrupt
 * Description:  Enable DMU interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               it: DMU IE #arg CAN_IT_DMU_Flags
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date         Author    Modified
 *  2024/01/02   01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_EnableDmuInterrupt(CAN_NODE *const pNode, uint32 it);

/**********************************************************************************************************************
 * Function:     Can_Hal_DisableDmuInterrupt
 * Description:  Disable DMU interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different CAN node, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               it: DMU IE interrupt mask #arg CAN_IT_DMU_Flags
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date         Author    Modified
 *  2024/01/02   01107      Create
 *********************************************************************************************************************/
extern boolean Can_Hal_DisableDmuInterrupt(CAN_NODE *const pNode, uint32 it);

#define CAN_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Can_MemMap.h"

#endif /* CAN_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
