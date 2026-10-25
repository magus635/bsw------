/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    can_std.h
 * Author:      00949
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #can_std_h_REF_1:MISRAC2012-Rule-19.2;
* Justification:Necessary union type for bitwise access to register. Data integrity and correctness will be ensured by
*               code review.
*
* #can_std_h_REF_2:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers
*
* #can_std_h_REF_3:CERTC-DCL06-C;
* Justification:The Tresos-generated code does not use symbolic constants for buffer size substitution.
*
* #can_std_h_REF_4:CWE-1701;
* Justification:MISRA-2012 Rule 15.7/Rule 16.4 require reserved empty code block.
*
* #can_std_h_REF_5:CERTC-547;
* Justification:The Tresos-generated code does not use symbolic constants for buffer size substitution.
*
* #can_std_h_REF_6:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #can_std_h_REF_7:MISRAC2012-Rule-11.4;
* Justification: Casting a pointer to an integral type to obtain its address.
* 
*/

#ifndef CAN_STD_H_
#define CAN_STD_H_

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "can_register.h"
#if(STD_ON == INPUT_ARG_DETECT)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */

/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* ^CAN_STD_ModuleRamSize^ The RAM size of CAN module */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_MODULE_RAM_SIZE             (sizeof(CAN0->RAM) / sizeof(CAN0->RAM[0]))

/* ^CAN_STD_InterruptsFlags^ CAN STD interrupts flags */
#define CAN_STD_IT_RXFIFO0MSG               ((uint32)0x00000001U)  /* [00] Rx FIFO 0 new message interrupt */
#define CAN_STD_IT_RXFIFO0WMREACHED         ((uint32)0x00000002U)  /* [01] Rx FIFO 0 watermark reached interrupt */
#define CAN_STD_IT_RXFIFO0FULL              ((uint32)0x00000004U)  /* [02] Rx FIFO 0 full interrupt */
#define CAN_STD_IT_RXFIFO0MSGLOST           ((uint32)0x00000008U)  /* [03] Rx FIFO 0 message lost interrupt */
#define CAN_STD_IT_RXFIFO1MSG               ((uint32)0x00000010U)  /* [04] Rx FIFO 1 new message interrupt */
#define CAN_STD_IT_RXFIFO1WMREACHED         ((uint32)0x00000020U)  /* [05] Rx FIFO 1 watermark reached interrupt */
#define CAN_STD_IT_RXFIFO1FULL              ((uint32)0x00000040U)  /* [06] Rx FIFO 1 full interrupt */
#define CAN_STD_IT_RXFIFO1MSGLOST           ((uint32)0x00000080U)  /* [07] Rx FIFO 1 message lost interrupt */
#define CAN_STD_IT_HIGHPRIMSG               ((uint32)0x00000100U)  /* [08] High priority message interrupt */
#define CAN_STD_IT_TXCOMPLETED              ((uint32)0x00000200U)  /* [09] Transmission completed interrupt */
#define CAN_STD_IT_TXCANCELLATIONFIN        ((uint32)0x00000400U)  /* [10] Transmission cancellation finished interrupt */
#define CAN_STD_IT_TXFIFOEMPTY              ((uint32)0x00000800U)  /* [11] Tx FIFO empty interrupt */
#define CAN_STD_IT_TXEVENTFIFONEWENTRY      ((uint32)0x00001000U)  /* [12] Tx event FIFO new entry interrupt */
#define CAN_STD_IT_TXEVENTFIFOWMREACHED     ((uint32)0x00002000U)  /* [13] Tx event FIFO watermark reached interrupt */
#define CAN_STD_IT_TXEVENTFIFOFULL          ((uint32)0x00004000U)  /* [14] Tx event FIFO full interrupt */
#define CAN_STD_IT_TXEVENTFIFOEVENTLOST     ((uint32)0x00008000U)  /* [15] Tx event FIFO event lost interrupt */
#define CAN_STD_IT_TIMESTAMPWRAPAROUND      ((uint32)0x00010000U)  /* [16] Time stamp wraparound interrupt */
#define CAN_STD_IT_RAMACCESSFAILURE         ((uint32)0x00020000U)  /* [17] Message RAM access failure interrupt */
#define CAN_STD_IT_TIMEOUTOCCOURRED         ((uint32)0x00040000U)  /* [18] Timeout occurred interrupt */
#define CAN_STD_IT_MSGDEDICATEDRXBUF        ((uint32)0x00080000U)  /* [19] Message stored to dedicated Rx buffer interrupt */
#define CAN_STD_IT_BITERRCORRECTED          ((uint32)0x00100000U)  /* [20] Bit error corrected interrupt */
#define CAN_STD_IT_BITERRUNCORRECTED        ((uint32)0x00200000U)  /* [21] Bit error uncorrected interrupt */
#define CAN_STD_IT_ERROVERFLOW              ((uint32)0x00400000U)  /* [22] Error logging overflow interrupt */
#define CAN_STD_IT_ERRPASSIVE               ((uint32)0x00800000U)  /* [23] Error passive interrupt */
#define CAN_STD_IT_WARNINGSTATUS            ((uint32)0x01000000U)  /* [24] Warning status interrupt */
#define CAN_STD_IT_BUSOFFSTATUS             ((uint32)0x02000000U)  /* [25] Bus off status interrupt */
#define CAN_STD_IT_WATCHDOG                 ((uint32)0x04000000U)  /* [26] Watchdog interrupt */
#define CAN_STD_IT_PROERRARBITRATION        ((uint32)0x08000000U)  /* [27] Protocol error in arbitration phase interrupt */
#define CAN_STD_IT_PROERRDATA               ((uint32)0x10000000U)  /* [28] Protocol error in Data phase interrupt */
#define CAN_STD_IT_ACCESSRESADDR            ((uint32)0x20000000U)  /* [29] Access to reserved address interrupt */
#define CAN_STD_IT_MASK                     ((uint32)0x3FFFFFFFU)

/* ^CAN_STD_IT_RouterFlags^ CAN router interrupt flags
   Note: Some interrupts are triggers with combinatorial priority.
*/
#define CAN_STD_IT_ROUTER_REINT             CAN_STD_IT_MSGDEDICATEDRXBUF       /* [00] See CAN_STD_IT_FLAGS IR-[19]*/
#define CAN_STD_IT_ROUTER_RXF1F             CAN_STD_IT_RXFIFO1FULL             /* [01] See CAN_STD_IT_FLAGS IR-[06] */
#define CAN_STD_IT_ROUTER_RXF0F             CAN_STD_IT_RXFIFO0FULL             /* [02] See CAN_STD_IT_FLAGS IR-[02] */
#define CAN_STD_IT_ROUTER_RXF1N             CAN_STD_IT_RXFIFO1MSG              /* [03] See CAN_STD_IT_FLAGS IR-[04] */
#define CAN_STD_IT_ROUTER_RXF0N             CAN_STD_IT_RXFIFO0MSG              /* [04] See CAN_STD_IT_FLAGS IR-[00] */
#define CAN_STD_IT_ROUTER_RETI              CAN_STD_IT_TIMEOUTOCCOURRED        /* [05] See CAN_STD_IT_FLAGS IR-[18] */
#define CAN_STD_IT_ROUTER_TRAQ              CAN_STD_IT_TXFIFOEMPTY             /* [06] See CAN_STD_IT_FLAGS IR-[11] */
#define CAN_STD_IT_ROUTER_TRACO             (CAN_STD_IT_TXCOMPLETED | \
                                            CAN_STD_IT_TXCANCELLATIONFIN)      /* [07] See CAN_STD_IT_FLAGS IR-[09\10] */
#define CAN_STD_IT_ROUTER_TEFIFO            (CAN_STD_IT_TXEVENTFIFONEWENTRY | \
                                            CAN_STD_IT_TXEVENTFIFOFULL)        /* [08] See CAN_STD_IT_FLAGS IR-[12\14] */
#define CAN_STD_IT_ROUTER_HPE                CAN_STD_IT_HIGHPRIMSG              /* [09] See CAN_STD_IT_FLAGS IR-[8] */
#define CAN_STD_IT_ROUTER_WAIT              (CAN_STD_IT_RXFIFO0WMREACHED | \
                                            CAN_STD_IT_RXFIFO1WMREACHED | \
                                            CAN_STD_IT_TXEVENTFIFOWMREACHED)   /* [10] See CAN_STD_IT_FLAGS IR-[01\05\13] */
#define CAN_STD_IT_ROUTER_ALERT             (CAN_STD_IT_RXFIFO0MSGLOST | \
                                            CAN_STD_IT_RXFIFO1MSGLOST | \
                                            CAN_STD_IT_TXEVENTFIFOEVENTLOST | \
                                            CAN_STD_IT_TIMESTAMPWRAPAROUND | \
                                            CAN_STD_IT_BITERRCORRECTED | \
                                            CAN_STD_IT_BITERRUNCORRECTED | \
                                            CAN_STD_IT_ERRPASSIVE | \
                                            CAN_STD_IT_WARNINGSTATUS | \
                                            CAN_STD_IT_ACCESSRESADDR)          /* [11] See CAN_STD_IT_FLAGS IR-[3\7\15\16\20\21\23\24\29] */
#define CAN_STD_IT_ROUTER_MORE              (CAN_STD_IT_RAMACCESSFAILURE | \
                                            CAN_STD_IT_WATCHDOG)               /* [12] See CAN_STD_IT_FLAGS IR-[17\26] */
#define CAN_STD_IT_ROUTER_SAFE               CAN_STD_IT_ERROVERFLOW             /* [13] See CAN_STD_IT_FLAGS IR-[22] */
#define CAN_STD_IT_ROUTER_BUSOFF             CAN_STD_IT_BUSOFFSTATUS            /* [14] See CAN_STD_IT_FLAGS IR-[25] */
#define CAN_STD_IT_ROUTER_LOI               (CAN_STD_IT_PROERRARBITRATION | \
                                            CAN_STD_IT_PROERRDATA)             /* [15] See CAN_STD_IT_FLAGS IR-[27\28] */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_ROUTER_MASK              ((uint32)0x0000FFFFU)

/* ^CAN_STD_IT_DMU_Flags^ CAN DMU interrupt flags */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_TXENSAE              ((uint32)0x00000001U)   /* [00] TX element not start address */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_TXEIEE               ((uint32)0x00000002U)   /* [01] TX element illegal enqueueing */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_TXEIASE              ((uint32)0x00000004U)   /* [02] TX element illegal access sequence */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_TXEIDLCE             ((uint32)0x00000008U)   /* [03] TX element illegal DLC */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_TXEWATAE             ((uint32)0x00000010U)   /* [04] TX element write after trigger address */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_TXEIRE               ((uint32)0x00000020U)   /* [05] TX element illegal Read */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_TXEEE                ((uint32)0x00000040U)   /* [06] TX element enqueued */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_RX0ENSAE             ((uint32)0x00000100U)   /* [08] RX0 element not start address */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_RX0EIDE              ((uint32)0x00000200U)   /* [09] RX0 element illegal dequeueing */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_RX0EIASE             ((uint32)0x00000400U)   /* [10] RX0 element illegal access sequence */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_RX0EIWE              ((uint32)0x00000800U)   /* [11] RX0 element illegal write */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_RX0EDE               ((uint32)0x00001000U)   /* [12] RX0 element dequeued */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_RX0EIOE              ((uint32)0x00002000U)   /* [13] RX0 element illegal overwrite by time stamp enable */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_BECE                 ((uint32)0x00004000U)   /* [14] Bit error corrected  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_BEUE                 ((uint32)0x00008000U)   /* [15] Bit error uncorrected */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_RX1ENSAE             ((uint32)0x00010000U)   /* [16] RX1 element not start address */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_RX1EIDE              ((uint32)0x00020000U)   /* [17] RX1 element illegal dequeueing */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_RX1EIASE             ((uint32)0x00040000U)   /* [18] RX1 element illegal access sequence */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_RX1EIWE              ((uint32)0x00080000U)   /* [19] RX1 element illegal write */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_RX1EDE               ((uint32)0x00100000U)   /* [20] RX1 element dequeued */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_RX1EIOE              ((uint32)0x00200000U)   /* [21] RX1 element illegal overwrite by time stamp enable */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_TXEENSAE             ((uint32)0x01000000U)   /* [24] TX event element not start address */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_TXEEIDE              ((uint32)0x02000000U)   /* [25] TX event element illegal dequeueing */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_TXEEIASE             ((uint32)0x04000000U)   /* [26] TX event element illegal access sequence */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_TXEEIWE              ((uint32)0x08000000U)   /* [27] TX event element illegal write */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_TXEEDE               ((uint32)0x10000000U)   /* [28] TX event element dequeued */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_DTE                  ((uint32)0x20000000U)   /* [29] Debug trigger */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_IACE                 ((uint32)0x40000000U)   /* [30] Illegal access while in configuration mode */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_IT_DMU_MASK                 ((uint32)0x7F3FFF7FU)

/* ^CAN_STD_RxLocation^  CAN RX dedicated buffer index and FIFO 0\1  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_0         ((uint32)0x00000000U)   /* Rx buffer 0 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_1         ((uint32)0x00000001U)   /* Rx buffer 1 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_2         ((uint32)0x00000002U)   /* Rx buffer 2 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_3         ((uint32)0x00000003U)   /* Rx buffer 3 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_4         ((uint32)0x00000004U)   /* Rx buffer 4 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_5         ((uint32)0x00000005U)   /* Rx buffer 5 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_6         ((uint32)0x00000006U)   /* Rx buffer 6 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_7         ((uint32)0x00000007U)   /* Rx buffer 7 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_8         ((uint32)0x00000008U)   /* Rx buffer 8 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_9         ((uint32)0x00000009U)   /* Rx buffer 9 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_10        ((uint32)0x0000000AU)   /* Rx buffer 10  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_11        ((uint32)0x0000000BU)   /* Rx buffer 11  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_12        ((uint32)0x0000000CU)   /* Rx buffer 12  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_13        ((uint32)0x0000000DU)   /* Rx buffer 13  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_14        ((uint32)0x0000000EU)   /* Rx buffer 14  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_15        ((uint32)0x0000000FU)   /* Rx buffer 15  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_16        ((uint32)0x00000010U)   /* Rx buffer 16  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_17        ((uint32)0x00000011U)   /* Rx buffer 17  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_18        ((uint32)0x00000012U)   /* Rx buffer 18  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_19        ((uint32)0x00000013U)   /* Rx buffer 19  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_20        ((uint32)0x00000014U)   /* Rx buffer 20  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_21        ((uint32)0x00000015U)   /* Rx buffer 21  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_22        ((uint32)0x00000016U)   /* Rx buffer 22  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_23        ((uint32)0x00000017U)   /* Rx buffer 23  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_24        ((uint32)0x00000018U)   /* Rx buffer 24  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_25        ((uint32)0x00000019U)   /* Rx buffer 25  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_26        ((uint32)0x0000001AU)   /* Rx buffer 26  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_27        ((uint32)0x0000001BU)   /* Rx buffer 27  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_28        ((uint32)0x0000001CU)   /* Rx buffer 28  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_29        ((uint32)0x0000001DU)   /* Rx buffer 29  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_30        ((uint32)0x0000001EU)   /* Rx buffer 30  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_31        ((uint32)0x0000001FU)   /* Rx buffer 31  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_32        ((uint32)0x00000020U)   /* Rx buffer 32  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_33        ((uint32)0x00000021U)   /* Rx buffer 33  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_34        ((uint32)0x00000022U)   /* Rx buffer 34  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_35        ((uint32)0x00000023U)   /* Rx buffer 35  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_36        ((uint32)0x00000024U)   /* Rx buffer 36  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_37        ((uint32)0x00000025U)   /* Rx buffer 37  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_38        ((uint32)0x00000026U)   /* Rx buffer 38  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_39        ((uint32)0x00000027U)   /* Rx buffer 39  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_40        ((uint32)0x00000028U)   /* Rx buffer 40  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_41        ((uint32)0x00000029U)   /* Rx buffer 41  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_42        ((uint32)0x0000002AU)   /* Rx buffer 42  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_43        ((uint32)0x0000002BU)   /* Rx buffer 43  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_44        ((uint32)0x0000002CU)   /* Rx buffer 44  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_45        ((uint32)0x0000002DU)   /* Rx buffer 45  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_46        ((uint32)0x0000002EU)   /* Rx buffer 46  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_47        ((uint32)0x0000002FU)   /* Rx buffer 47  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_48        ((uint32)0x00000030U)   /* Rx buffer 48  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_49        ((uint32)0x00000031U)   /* Rx buffer 49  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_50        ((uint32)0x00000032U)   /* Rx buffer 50  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_51        ((uint32)0x00000033U)   /* Rx buffer 51  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_52        ((uint32)0x00000034U)   /* Rx buffer 52  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_53        ((uint32)0x00000035U)   /* Rx buffer 53  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_54        ((uint32)0x00000036U)   /* Rx buffer 54  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_55        ((uint32)0x00000037U)   /* Rx buffer 55  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_56        ((uint32)0x00000038U)   /* Rx buffer 56  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_57        ((uint32)0x00000039U)   /* Rx buffer 57  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_58        ((uint32)0x0000003AU)   /* Rx buffer 58  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_59        ((uint32)0x0000003BU)   /* Rx buffer 59  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_60        ((uint32)0x0000003CU)   /* Rx buffer 60  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_61        ((uint32)0x0000003DU)   /* Rx buffer 61  */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_RXLOCATION_BUFFER_62        ((uint32)0x0000003EU)   /* Rx buffer 62  */
#define CAN_STD_RXLOCATION_BUFFER_63        ((uint32)0x0000003FU)   /* Rx buffer 63  */
#define CAN_STD_RXLOCATION_FIFO0            ((uint32)0x00000040U)   /* Rx FIFO 0 */
#define CAN_STD_RXLOCATION_FIFO1            ((uint32)0x00000041U)   /* Rx FIFO 1 */

/* ^CAN_STD_TxLocation^ CAN TX dedicated buffer index and FIFO\QUEUE */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_0         ((uint32)0x00000000U)   /* Tx buffer 0 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_1         ((uint32)0x00000001U)   /* Tx buffer 1 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_2         ((uint32)0x00000002U)   /* Tx buffer 2 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_3         ((uint32)0x00000003U)   /* Tx buffer 3 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_4         ((uint32)0x00000004U)   /* Tx buffer 4 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_5         ((uint32)0x00000005U)   /* Tx buffer 5 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_6         ((uint32)0x00000006U)   /* Tx buffer 6 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_7         ((uint32)0x00000007U)   /* Tx buffer 7 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_8         ((uint32)0x00000008U)   /* Tx buffer 8 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_9         ((uint32)0x00000009U)   /* Tx buffer 9 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_10        ((uint32)0x0000000AU)   /* Tx buffer 10 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_11        ((uint32)0x0000000BU)   /* Tx buffer 11 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_12        ((uint32)0x0000000CU)   /* Tx buffer 12 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_13        ((uint32)0x0000000DU)   /* Tx buffer 13 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_14        ((uint32)0x0000000EU)   /* Tx buffer 14 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_15        ((uint32)0x0000000FU)   /* Tx buffer 15 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_16        ((uint32)0x00000010U)   /* Tx buffer 16 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_17        ((uint32)0x00000011U)   /* Tx buffer 17 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_18        ((uint32)0x00000012U)   /* Tx buffer 18 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_19        ((uint32)0x00000013U)   /* Tx buffer 19 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_20        ((uint32)0x00000014U)   /* Tx buffer 20 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_21        ((uint32)0x00000015U)   /* Tx buffer 21 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_22        ((uint32)0x00000016U)   /* Tx buffer 22 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_23        ((uint32)0x00000017U)   /* Tx buffer 23 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_24        ((uint32)0x00000018U)   /* Tx buffer 24 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_25        ((uint32)0x00000019U)   /* Tx buffer 25 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_26        ((uint32)0x0000001AU)   /* Tx buffer 26 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_27        ((uint32)0x0000001BU)   /* Tx buffer 27 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_28        ((uint32)0x0000001CU)   /* Tx buffer 28 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_29        ((uint32)0x0000001DU)   /* Tx buffer 29 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_30        ((uint32)0x0000001EU)   /* Tx buffer 30 */
/* #Violation: can_std_h_REF_2 */
#define CAN_STD_TXLOCATION_BUFFER_31        ((uint32)0x0000001FU)   /* Tx buffer 31 */
#define CAN_STD_TXLOCATION_FIFO_QUEUE       ((uint32)0x00000020U)   /* Tx FIFO or Queue */

/* ^CAN_STD_DMU_ADDRESS^ CAN DMU address type */
#define CAN_STD_DMU_ADDRESS_TX              ((uint32)0x00000000U)   /* TX address type */
#define CAN_STD_DMU_ADDRESS_RX_0            ((uint32)0x00000001U)   /* RX-0 address type */
#define CAN_STD_DMU_ADDRESS_RX_1            ((uint32)0x00000002U)   /* RX-1 address type */
#define CAN_STD_DMU_ADDRESS_TXE             ((uint32)0x00000003U)   /* TX event address type */

/* ^CAN_STD_DMU_REQUEST^ CAN DMU enable type */
#define CAN_STD_DMU_REQUEST_TX              ((uint32)0x00000000U)   /* TX DMU request type */
#define CAN_STD_DMU_REQUEST_RX_0            ((uint32)0x00000001U)   /* RX-0 DMU request type */
#define CAN_STD_DMU_REQUEST_RX_1            ((uint32)0x00000002U)   /* RX-1 DMU request type */
#define CAN_STD_DMU_REQUEST_TXE             ((uint32)0x00000003U)   /* TX event DMU request type */

#define CAN_REG_CHECK_READ                  ((uint16)0x3FFFU)       /* CAN register check read */

#define CAN_REG_CHECK
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *                                         Global Function Definitions
 *********************************************************************************************************************/

 /**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
#define CAN_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: can_std_h_REF_6 */
#include "Can_MemMap.h"
/**********************************************************************************************************************
 * Function:    Can_Register_ReadBack_Check
 * Description: Checks whether the register value written is equal to the value read back
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:       expect: Read back the value of the register
 *              value: value written to register
 *              state: Wrong initial state
 * Inout:        None
 * Output:      None
 * Return:      boolean: Flag indicating whether the value written to register is the same as the value read back
 * Others:      None
 * History:
 * Date         Author    Modified
 * 2025/03/10   01744     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Register_ReadBack_Check(boolean state, uint32 value, uint32 expect);

/**********************************************************************************************************************
 * Function:     Can_Std_ElementSzieToBytes
 * Description:  Element Szie To Byte
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        value: Actual Element szie
 * Inout:        None
 * Output:       None
 * Return:       uint32: Size of alements in the converted register
 * Others:
 * History:
 *  Date         Author    Modified
 *  2023/09/27   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_ElementSzieToBytes(uint32 value);

/**********************************************************************************************************************
 * Function:     Can_Std_DlcToBytes
 * Description:  the value of DLC register convert to byte
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        value: the value of DLC register
 * Inout:        None
 * Output:       None
 * Return:       uint32: Actual number bytes
 * Others:
 * History:
 *  Date         Author    Modified
 *  2023/09/27   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_DlcToBytes(uint32 value);

/**********************************************************************************************************************
 * Function:     Can_Std_EscToBytes
 * Description:  the Tx\Rx buffer data field size of TX\RX-ESC register convert to byte
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        value:the Tx\Rx buffer data field size of TX\RX-ESC register
 * Inout:        None
 * Output:       None
 * Return:       uint32: Actual number bytes
 * Others:
 * History:
 *  Date         Author    Modified
 *  2023/12/22   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_EscToBytes(uint32 value);

/**********************************************************************************************************************
 * Function:     Can_Std_SetFDBaudrate
 * Description:  Set data bit timing & prescaler
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               prescaler: Data bit rate prescaler [0x00-0x1F]
 *               syncJumpWidth:Data (Re)Synchronization Jump Width [0x0-0xF]
 *               timeSegment1: Data time segment before sample point[0x00-0x1F]
 *               timeSegment2: Data time segment after sample point [0x0-0xF]
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetFDBaudrate(CAN_NODE *const pNode,
                                             uint32 prescaler,
                                             uint32 syncJumpWidth,
                                             uint32 timeSegment1,
                                             uint32 timeSegment2);

/**********************************************************************************************************************
 * Function:     Can_Std_SetTxDelayCompensation
 * Description:  Set transmitter delay compensation
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               enable: 0= Transmitter Delay Compensation disabled
 *                       1= Transmitter Delay Compensation enabled
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetTxDelayCompensation(CAN_NODE *const pNode, uint32 enable);

/**********************************************************************************************************************
 * Function:     Can_Std_SetTestLBCK
 * Description:  Set the look back mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               enable: 0= Reset value, Loop Back Mode is disabled
 *                       1= Loop Back Mode is enabled
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetTestLBCK(CAN_NODE *const pNode, uint32 enable);

/**********************************************************************************************************************
 * Function:     Can_Std_GetTestLBCK
 * Description:  Get value of the 'look back mode' bit of the 'TEST register'
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: 0= Reset value, Loop Back Mode is disabled
 *                       1= Loop Back Mode is enabled
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetTestLBCK(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_SetCccrInit
 * Description:  Set the initialization
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               enable: 0= Normal Operation
 *                       1= Initialization is started
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Can_Std_SetCccrInit(CAN_NODE *const pNode, uint32 enable);

/**********************************************************************************************************************
 * Function:     Can_Std_GetCccrInit
 * Description:  Get value of the 'INIT' bit of the 'CCCR register'
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: 0= Normal Operation
 *                       1= Initialization is started
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetCccrInit(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_SetCccrConfigurationChange
 * Description:  Configuration Change Enable
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               enable: 0= The CPU has no write access to the protected configuration registers
 *                       1= The CPU has write access to the protected configuration registers
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetCccrConfigurationChange(CAN_NODE *const pNode, uint32 enable);

/**********************************************************************************************************************
 * Function:     Can_Std_GetCcccrConfigurationChange
 * Description:  Get value of the 'CCCE' bit of the 'CCCR register'
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: 0= The CPU has no write access to the protected configuration registers
 *                       1= The CPU has write access to the protected configuration registers
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetCcccrConfigurationChange(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_SetCccrRestricted
 * Description:  Restricted Operation Mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               enable: 0= Normal CAN operation
 *                       1= Restricted Operation Mode active
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetCccrRestricted(CAN_NODE *const pNode, uint32 enable);

/**********************************************************************************************************************
 * Function:     Can_Std_GetCccrRestricted
 * Description:  Get value of the 'ROM' bit of the 'CCCR register'
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: 0= Normal CAN operation
 *                       1= Restricted Operation Mode active
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetCccrRestricted(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_GetCccrClockStopACK
 * Description:  Get the state of Clock Stop Acknowledge
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: 0= No clock stop acknowledged
 *                       1= M_TTCAN may be set in power down by stopping m_ttcan_hclk and m_ttcan_cclk
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetCccrClockStopACK(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_SetCccrClockRequestStop
 * Description:  Clock Stop Request
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               enable: 0= No clock stop is requested
 *                       1= Clock stop requested.
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetCccrClockRequestStop(CAN_NODE *const pNode, uint32 enable);

/**********************************************************************************************************************
 * Function:     Can_Std_GetCccrClockRequestStop
 * Description:  Get value of the 'CSR' bit of the 'CCCR register'
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: 0= No clock stop is requested
 *                       1= Clock stop requested.
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetCccrClockRequestStop(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_SetMonitorMode
 * Description:  Bus Monitoring Mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               enable: 0= Bus Monitoring Mode is disabled
 *                       1= Bus Monitoring Mode is enabled
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetMonitorMode(CAN_NODE *const pNode, uint32 enable);

/**********************************************************************************************************************
 * Function:     Can_Std_GetMonitorMode
 * Description:  Get value of the 'MON' bit of the 'CCCR register'
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: 0= Bus Monitoring Mode is disabled
 *                       1= Bus Monitoring Mode is enabled
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetMonitorMode(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_SetCccrDisableAutomaticRetransmission
 * Description:  Disable Automatic Retransmission
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               enable: 0= Automatic retransmission of messages not transmitted successfully enabled
 *                       1= Automatic retransmission disabled
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetCccrDisableAutomaticRetransmission(CAN_NODE *const pNode, uint32 enable);

/**********************************************************************************************************************
 * Function:     Can_Std_GetCccrDisableAutomaticRetransmission
 * Description:  Get value of the 'DAR' bit of the 'CCCR register'
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: 0= Automatic retransmission of messages not transmitted successfully enabled
 *                       1= Automatic retransmission disabled
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetCccrDisableAutomaticRetransmission(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_SetCccrTest
 * Description:  Test Mode Enable
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               enable: 0= Normal operation, register TEST holds reset values
 *                       1= Test Mode, write access to register TEST enabled
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetCccrTest(CAN_NODE *const pNode, uint32 enable);

/**********************************************************************************************************************
 * Function:     Can_Std_GetCccrTest
 * Description:  Get value of the 'TEST' bit of the 'CCCR register'
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: 0= Normal operation, register TEST holds reset values
 *                       1= Test Mode, write access to register TEST enabled
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetCccrTest(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_SetTestMode
 * Description:  Set LoopBack mode
 *               CAN Operating Mode:
 *                            | Normal | Restricted |    Bus     | Internal | External
 *                            |        | Operation  | Monitoring | LoopBack | LoopBack
 *                  CCCR.TEST |   0    |     0      |     0      |    1     |    1
 *                  TEST.LBCK |   0    |     0      |     0      |    1     |    1
 *                  CCCR.MON  |   0    |     0      |     1      |    1     |    0
 *                  CCCR.ASM  |   0    |     1      |     0      |    0     |    0
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetTestMode(CAN_NODE *const pNode, uint32 internalLoopBack);

/**********************************************************************************************************************
 * Function:     Can_Std_SetCccrFD
 * Description:  FD Operation Enable
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               enable: 0= FD operation disabled
 *                       1= FD operation enabled
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetCccrFD(CAN_NODE *const pNode, uint32 enable);

/**********************************************************************************************************************
 * Function:     Can_Std_GetCccrFD
 * Description:  Get value of the 'FDOE' bit of the 'CCCR register'
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: 0= FD operation disabled
 *                       1= FD operation enabled
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetCccrFD(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_SetCccrBRS
 * Description:  Bit Rate Switch Enable
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               enable: 0= Bit rate switching for transmissions disabled
 *                       1= Bit rate switching for transmissions enabled
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetCccrBRS(CAN_NODE *const pNode, uint32 enable);

/**********************************************************************************************************************
 * Function:     Can_Std_GetCccrBRS
 * Description:  Get value of the 'BRSE' bit of the 'CCCR register'
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32:  0= Bit rate switching for transmissions disabled
 *                        1= Bit rate switching for transmissions enabled
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetCccrBRS(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_SetWideMessageMark
 * Description:  Enables the use of 16-bit Wide Message Markers.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               enable: 0= 8-bit Message Marker used
 *                       1= 16-bit Message Marker used, replacing 16-bit time stamps in Tx Event FIFO
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetWideMessageMark(CAN_NODE *const pNode, uint32 enable);

/**********************************************************************************************************************
 * Function:     Can_Std_GetWideMessageMark
 * Description:  Get value of the 'WMM' bit of the 'CCCR register'
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: 0= 8-bit Message Marker used
 *                       1= 16-bit Message Marker used, replacing 16-bit timestamps in Tx Event FIFO
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetWideMessageMark(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_SetCccrDisableProtocolExceptionHandling
 * Description:  Protocol Exception Handling Disable
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               enable: 0= Protocol exception handling enabled
 *                       1= Protocol exception handling disabled
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetCccrDisableProtocolExceptionHandling(CAN_NODE *const pNode, uint32 enable);

/**********************************************************************************************************************
 * Function:     Can_Std_GetCccrProtocolExceptionHandlingDisable
 * Description:  Get value of the 'PXHD' bit of the 'CCCR register'
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: 0= Protocol exception handling enabled
 *                       1= Protocol exception handling disabled
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetCccrProtocolExceptionHandlingDisable(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_SetCccrEdgeFiltering
 * Description:  Edge Filtering during Bus Integration
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               enable: 0= Edge filtering disabled
 *                       1= Two consecutive dominant tq required to detect an edge for hard synchronization
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetCccrEdgeFiltering(CAN_NODE *const pNode, uint32 enable);

/**********************************************************************************************************************
 * Function:     Can_Std_GetCccrEdgeFiltering
 * Description:  Get value of the 'EFBI' bit of the 'CCCR register'
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: 0= Edge filtering disabled
 *                       1= Two consecutive dominant tq required to detect an edge for hard synchronization
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetCccrEdgeFiltering(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_SetCccrTransmissionPause
 * Description:  Transmit Pause
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               enable: 0= Transmit pause disabled
 *                       1= Transmit pause enabled
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetCccrTransmissionPause(CAN_NODE *const pNode, uint32 enable);

/**********************************************************************************************************************
 * Function:     Can_Std_SetBaudrate
 * Description:  Set nominal bit timing & prescaler register
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               prescaler: Normal data bit rate prescaler [0x000-0x1FF]
 *               syncJumpWidth: Normal data (Re)Synchronization Jump Width [0x00-0x7F]
 *               timeSegment1: Normal data time segment before sample point [0x000-0x1FF]
 *               timeSegment2: Normal data time segment after sample point [0x01-0x7F]
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetBaudrate(CAN_NODE *const pNode,
                                              uint32 prescaler,
                                              uint32 syncJumpWidth,
                                              uint32 timeSegment1,
                                              uint32 timeSegment2);

/**********************************************************************************************************************
 * Function:     Can_Std_SetimestampCounter
 * Description:  Set time stamp counter prescaler
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               timestampPrescaler: Time stamp Counter Prescaler[0x0-0xF]
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetimestampCounter(CAN_NODE *const pNode,  uint32 timestampPrescaler);

/**********************************************************************************************************************
 * Function:     Can_Std_SetTimestampCounterOperation
 * Description:  Time stamp Select
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               timestampPrescaler:
 *                  00= Time stamp counter value always 0x0000
 *                  01= Time stamp counter value incremented according to TCP
 *                  10= External time stamp counter value used
 *                  11= Same as "00"
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetTimestampCounterOperation(CAN_NODE *const pNode,  uint32 timestampOperation);

/**********************************************************************************************************************
 * Function:     Can_Std_GetTimestampCounter
 * Description:  Get Time stamp Counter Value
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: Time stamp Counter [0:15]
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetTimestampCounter(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_ResetTimestampCounter
 * Description:  Clear time stamp value
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
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
LOCAL_FORCEINLINE boolean Can_Std_ResetTimestampCounter(CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_ConfigTimeoutCounter
 * Description:  Configure Timeout Counter
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               timeoutOperation:
 *                       00= Continuous operation
 *                       01= Timeout controlled by Tx Event FIFO
 *                       10= Timeout controlled by Rx FIFO 0
 *                       11= Timeout controlled by Rx FIFO 1
 *               timeoutPeriod:Timeout Period [15:0]
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_ConfigTimeoutCounter(CAN_NODE *const pNode,
                        uint32 timeoutOperation, uint32 timeoutPeriod);

/**********************************************************************************************************************
 * Function:     Can_Std_SetTimeoutCounter
 * Description:  Enable\Disable timeout counter
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               enable:0= Timeout Counter disabled
 *                      1= Timeout Counter enabled
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetTimeoutCounter(CAN_NODE *const pNode, uint32 enable);

/**********************************************************************************************************************
 * Function:     Can_Std_GetTimeoutCounter
 * Description:  Get timeout counter value
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: Time stamp Counter [0:15]
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetTimeoutCounter(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_ResetTimeoutCounter
 * Description:  Reset timeout counter
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Can_Std_ResetTimeoutCounter(CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_GetErrorCounters
 * Description:  Get error Counters
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       pTxErrorCnt: Actual state of the Receive Error Counter, values between 0 and 127
 *               pRxErrorCnt: Actual state of the Receive Error Counter, values between 0 and 127
 *               pRxErrorPassive:
 *                    0= The Receive Error Counter is below the error passive level of 128
 *                    1= The Receive Error Counter has reached the error passive level of 128
 *               pErrorLogging: CAN Error Logging [7:0]
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Can_Std_GetErrorCounters(const CAN_NODE *const pNode,
                                                uint8 *const pTxErrorCnt,
                                                uint8 *const pRxErrorCnt,
                                                uint8 *const pRxErrorPassive,
                                                uint8 *const pErrorLogging);

/**********************************************************************************************************************
 * Function:     Can_Std_GetProtocolStatus
 * Description:  Get protocol status
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: protocol state
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetProtocolStatus(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_ConfigTxDelayCompensation
 * Description:  configure transmitter delay compensation
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               delay:Transmitter Delay Compensation SSP Offset [6:0]
 *               filter_window: Transmitter Delay Compensation Filter Window Length [6:0]
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_ConfigTxDelayCompensation(CAN_NODE *const pNode, uint32 delay, uint32 filter_window);

/**********************************************************************************************************************
 * Function:     Can_Std_GetInterruptFlag
 * Description:  Get interrupt flags
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: interrupt flags
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetInterruptFlag(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_ClearInterruptFlag
 * Description:  Clear interrupt flag
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               it: interrupt flag which want to clear
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Can_Std_ClearInterruptFlag(CAN_NODE *const pNode, uint32 it);

/**********************************************************************************************************************
 * Function:     Can_Std_GetInterruptEnable
 * Description:  Get the enable interrupt flag
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: the enable interrupt flag of CAN node.
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetInterruptEnable(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_SetITLine
 * Description:  Enable\Disbale interrupt line
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               it:   interrupt flag ref CAN_STD_InterruptsFlags
 *               line: 0= Interrupt assigned to interrupt line m_ttcan_int0
 *                     1= Interrupt assigned to interrupt line m_ttcan_int1
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetITLine(CAN_NODE *const pNode, uint32 it, uint32 line);

/**********************************************************************************************************************
 * Function:     Can_Std_SetIleEnt0
 * Description:  Enable\Disable interrupt line 0
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               enable: 0= Interrupt line m_ttcan_int0 disabled
 *                       1= Interrupt line m_ttcan_int0 enabled
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetIleEnt0(CAN_NODE *const pNode, uint32 enable);

/**********************************************************************************************************************
 * Function:     Can_Std_SetIleEnt1
 * Description:  Enable\Disbale interrupt line 1
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               enable: 0= Interrupt line m_ttcan_int1 disabled
 *                       1= Interrupt line m_ttcan_int1 enabled
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetIleEnt1(CAN_NODE *const pNode, uint32 enable);

/**********************************************************************************************************************
 * Function:     Can_Std_ConfigGlobalFilter
 * Description:  Global Filter Configuration
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               NonMatchingStd: 00= Accept in Rx FIFO 0
 *                               01= Accept in Rx FIFO 1
 *                               10= Reject
 *                               11= Reject
 *               NonMatchingExt: 00= Accept in Rx FIFO 0
 *                               01= Accept in Rx FIFO 1
 *                               10= Reject
 *                               11= Reject
 *               RejectRemoteStd: 0= Filter remote frames with 11-bit standard IDs
 *                                1= Reject all remote frames with 11-bit standard IDs
 *               RejectRemoteExt: 0= Filter remote frames with 29-bit extended IDs
 *                                1= Reject all remote frames with 29-bit extended IDs
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/31   00949      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_ConfigGlobalFilter(CAN_NODE *const pNode,
                                                     uint32 NonMatchingStd,
                                                     uint32 NonMatchingExt,
                                                     uint32 RejectRemoteStd,
                                                     uint32 RejectRemoteExt);

/**********************************************************************************************************************
 * Function:     Can_Std_SetStdFilterListStartAddress
 * Description:  Set Standard filter list start address
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               address: Start address of standard message ID filter list in the message RAM [15:0]
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetStdFilterListStartAddress(CAN_NODE *const pNode, uint32 address);

/**********************************************************************************************************************
 * Function:     Can_Std_GetStdFilterListStartAddress
 * Description:  Get Standard filter list start address
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: Standard filter list start address
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/31   00949      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetStdFilterListStartAddress(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_SetStandardFilterListSize
 * Description:  Set the standard  message ID filter list size
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               size: Number of standard message ID filter elements [7:0]
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/31   00949      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetStandardFilterListSize(CAN_NODE *const pNode, uint32 size);

/**********************************************************************************************************************
 * Function:     Can_Std_SetExtFilterStartAddress
 * Description:  Set the start address of extended message ID filter list
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 *               address: Start address of extended message ID filter list in the message RAM [15:0]
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/31   00949      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetExtFilterStartAddress(CAN_NODE *const pNode, uint32 address);

/**********************************************************************************************************************
 * Function:     Can_Std_GetExtFilterStartAddress
 * Description:  Get extended filter list start address
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: Extended filter list start address [15:0]
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetExtFilterStartAddress(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_SetExtendedFilterListSize
 * Description:  Set the extended message ID filter list size
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 *               size: Number of extended message ID filter elements [6:0]
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/31   00949      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetExtendedFilterListSize(CAN_NODE *const pNode, uint32 size);

/**********************************************************************************************************************
 * Function:     Can_Std_SetExtendedFilterXIDAM
 * Description:  Set the extended ID and Mask.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 *               mask: Extended ID Mask [28:0]
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetExtendedFilterXIDAM(CAN_NODE *const pNode, uint32 mask);

/**********************************************************************************************************************
 * Function:     Can_Std_GetHighProotityStatus
 * Description:  Get high priority status
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 * Inout:        None
 * Output:       pFilterList pointer, 0= Standard Filter List
 *                                   1= Extended Filter List
 *               pFilterIndex pointer: Index of matching filter element.[6:0]
 *               pMessageStorage pointer:
 *                               00= No FIFO selected
 *                               01= FIFO message lost
 *                               10= Message stored in FIFO 0
 *                               11= Message stored in FIFO 1
 *               pMessageIndex pointer: Index of Rx FIFO element to which the message was stored. [5:0]
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Can_Std_GetHighProotityStatus(const CAN_NODE *const pNode,
                                                     uint8 *const pFilterList,
                                                     uint8 *const pFilterIndex,
                                                     uint8 *const pMessageStorage,
                                                     uint8 *const pMessageIndex);
                                                
/**********************************************************************************************************************
 * Function:     Can_Std_GetRxBufferMessageAvailable
 * Description:  Get the available index bit of the Rx buffer message.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 * Inout:        None
 * Output:       None
 * Return:       uint64: the available index bit of the Rx buffer message. [0:63]
 *               0= Rx Buffer not updated
 *               1= Rx Buffer updated from new message
 *
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint64 Can_Std_GetRxBufferMessageAvailable(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_SetRxFifo0StartAddress
 * Description:  Set Rx FIFO-0 start address
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 *               address: Start address of Rx FIFO 0 in Message RAM [15:0]
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetRxFifo0StartAddress(CAN_NODE *const pNode, uint32 address);

/**********************************************************************************************************************
 * Function:     Can_Std_SetRxFifo0Size
 * Description:  Set Rx FIFO-0 size
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 *               size: 0= No Rx FIFO 0
 *                     1-64= Number of Rx FIFO 0 elements
 *                     >64= Values greater than 64 are interpreted as 64
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetRxFifo0Size(CAN_NODE *const pNode, uint32 size);

/**********************************************************************************************************************
 * Function:     Can_Std_SetRxFifo0WatermarkLevel
 * Description:  Set Rx FIFO-0 water mark
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 *               level: 0= Watermark interrupt disabled
 *                      1-64= Level for Rx FIFO 0 watermark interrupt (IR.RF0W)
 *                      >64= Watermark interrupt disabled
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetRxFifo0WatermarkLevel(CAN_NODE *const pNode, uint32 level);

/**********************************************************************************************************************
 * Function:     Can_Std_SetRxFifo0OperatingMode
 * Description:  Set Rx FIFO-0 operation mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 *               mode: 0= FIFO 0 blocking mode
 *                     1= FIFO 0 overwrite mode
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetRxFifo0OperatingMode(CAN_NODE *const pNode, uint32 mode);

/**********************************************************************************************************************
 * Function:     Can_Std_GetRxFifo0FillLevel
 * Description:  Get Rx FIFO-0 fill level
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: Number of elements stored in Rx FIFO 0, range 0 to 64.
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetRxFifo0FillLevel(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_SetRxBuffersStartAddress
 * Description:  Set Rx buffer start address
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 *               address:Rx Buffer Start Address [15:0]
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetRxBuffersStartAddress(CAN_NODE *const pNode, uint32 address);

/**********************************************************************************************************************
 * Function:     Can_Std_SetRxFifo1StartAddress
 * Description:  Set Rx FIFO-1 start address
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 *               address: Rx FIFO-1 start address [15:0]
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetRxFifo1StartAddress(CAN_NODE *const pNode, uint32 address);

/**********************************************************************************************************************
 * Function:     Can_Std_SetRxFifo1Size
 * Description:  Set Rx FIFO-1 size
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 *               size: 0= No Rx FIFO 1
 *                     1-64= Number of Rx FIFO 1 elements
 *                     >64= Values greater than 64 are interpreted as 64
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetRxFifo1Size(CAN_NODE *const pNode, uint32 size);

/**********************************************************************************************************************
 * Function:     Can_Std_SetRxFifo1WatermarkLevel
 * Description:  Set Rx FIFO-1 watermark
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 *               level: 0= Watermark interrupt disabled
 *                      1-64= Level for Rx FIFO 1 watermark interrupt (IR.RF1W)
 *                      >64= Watermark interrupt disabled
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetRxFifo1WatermarkLevel(CAN_NODE *const pNode, uint32 level);

/**********************************************************************************************************************
 * Function:     Can_Std_SetRxFifo1OperatingMode
 * Description:  Set Rx FIFO-1 operation mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 *               mode: 0= FIFO 1 blocking mode
 *                     1= FIFO 1 overwrite mode
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetRxFifo1OperatingMode(CAN_NODE *const pNode, uint32 mode);

/**********************************************************************************************************************
 * Function:     Can_Std_GetRxFifo1FillLevel
 * Description:  Get Rx FIFO-1 fill level
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: Number of elements stored in Rx FIFO 1, range 0 to 64.
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetRxFifo1FillLevel(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_ClearMessageFlag
 * Description:  Clear transmission and receive message flag.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Can_Std_ClearMessageFlag(CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_SetRxBufferDataFieldSize
 * Description:  Set Rx dedicated buffer element size
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 *               size: 000= 8 byte data field
 *                     001= 12 byte data field
 *                     010= 16 byte data field
 *                     011= 20 byte data field
 *                     100= 24 byte data field
 *                     101= 32 byte data field
 *                     110= 48 byte data field
 *                     111= 64 byte data field
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetRxBufferDataFieldSize(CAN_NODE *const pNode, uint32 size);

/**********************************************************************************************************************
 * Function:     Can_Std_SetRxFifo0DataFieldSize
 * Description:  Set Rx FIFO-0 element size
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 *               size: 000= 8 byte data field
 *                     001= 12 byte data field
 *                     010= 16 byte data field
 *                     011= 20 byte data field
 *                     100= 24 byte data field
 *                     101= 32 byte data field
 *                     110= 48 byte data field
 *                     111= 64 byte data field
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetRxFifo0DataFieldSize(CAN_NODE *const pNode, uint32 size);

/**********************************************************************************************************************
 * Function:     Can_Std_SetRxFifo1DataFieldSize
 * Description:  Set Rx FIFO-1 element size
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 *               size: 000= 8 byte data field
 *                     001= 12 byte data field
 *                     010= 16 byte data field
 *                     011= 20 byte data field
 *                     100= 24 byte data field
 *                     101= 32 byte data field
 *                     110= 48 byte data field
 *                     111= 64 byte data field
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetRxFifo1DataFieldSize(CAN_NODE *const pNode, uint32 size);

/**********************************************************************************************************************
 * Function:     Can_Std_SetTxBuffersStartAddress
 * Description:  Set Tx buffer start address
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 *               address: Tx buffer start address [15:0]
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetTxBuffersStartAddress(CAN_NODE *const pNode, uint32 address);

/**********************************************************************************************************************
 * Function:     Can_Std_SetDedicatedTxBuffersNumber
 * Description:  Set the number of dedicated transmit buffers
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 *               number: 0= No Dedicated Tx Buffers
 *                       1-32= Number of Dedicated Tx Buffers
 *                       >32= Values greater than 32 are interpreted as 32
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetDedicatedTxBuffersNumber(CAN_NODE *const pNode, uint32 number);

/**********************************************************************************************************************
 * Function:     Can_Std_SetTransmitFifoQueueSize
 * Description:  Set the number of transmit FIFO\QUEUE
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 *               number: 0= No Tx FIFO/Queue
 *                       1-32= Number of Tx Buffers used for Tx FIFO/Queue
 *                       >32= Values greater than 32 are interpreted as 32
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetTransmitFifoQueueSize(CAN_NODE *const pNode, uint32 number);

/**********************************************************************************************************************
 * Function:     Can_Std_SetTransmitFifoQueueMode
 * Description:  Set Tx FIFO/Queue mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 *               number: 0= Tx FIFO operation
 *                       1= Tx Queue operation
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetTransmitFifoQueueMode(CAN_NODE *const pNode, uint32 mode);

/**********************************************************************************************************************
 * Function:     Can_Std_GetTxFifoFreeLevel
 * Description:  Get Tx FIFO free leve
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: Number of consecutive free Tx FIFO elements starting from TFGI, range 0 to 32
 *               Read as zero when Tx Queue operation is configured (TXBC.TFQM = '1' )
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetTxFifoFreeLevel(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_SetTxBufferElrSize
 * Description:  Set Tx buffer element unit size
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 *               size: 000= 8 byte data field
 *                     001= 12 byte data field
 *                     010= 16 byte data field
 *                     011= 20 byte data field
 *                     100= 24 byte data field
 *                     101= 32 byte data field
 *                     110= 48 byte data field
 *                     111= 64 byte data field
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetTxBufferElrSize(CAN_NODE *const pNode, uint32 size);

/**********************************************************************************************************************
 * Function:     Can_Std_GetTxBufferPending
 * Description:  Get the flags of transmission request pending
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: the flags of transmission request pending
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetTxBufferPending(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_TxBufferRequest
 * Description:  Tx Buffer add request by setting corresponding flags
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Can_Std_TxBufferRequest(CAN_NODE *const pNode, uint32 bufferIndex);

/**********************************************************************************************************************
 * Function:     Can_Std_AbortTxRequest
 * Description:  Abort transmission by setting corresponding flags
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Can_Std_AbortTxRequest(CAN_NODE *const pNode, uint32 bufferIndex);

/**********************************************************************************************************************
 * Function:     Can_Std_GetTxBufferTransOccured
 * Description:  Get the result flags of Tx buffer transmission occurred
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: the flags of Tx buffer transmission occurred
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetTxBufferTransOccured(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_GetTxBufferAbortFinished
 * Description:  Get the result flags of transmit buffer cancellation Finished
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: the result flags of transmit buffer cancellation Finished
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetTxBufferAbortFinished(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_GetTxBufferTransOccuredIE
 * Description:  Get the flags of Tx Buffer Transmission Interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: the flags of Tx Buffer transmission interrupt [31:0]
 *                   0= Transmission interrupt disabled
 *                   1= Transmission interrupt enable
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetTxBufferTransOccuredIE(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_GetTxBufferAbortFinishedIE
 * Description:  Get the flags of Tx Buffer abort transmission Interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN Node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: the flags of Tx Buffer abort transmission interrupt [31:0]
 *                   0= Cancellation finished interrupt disabled
 *                   1= Cancellation finished interrupt enabled
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetTxBufferAbortFinishedIE(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_SetTxEventFifoStartAddress
 * Description:  Set Tx event Fifo start address
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               address: Tx event Fifo start address
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/31   00949      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetTxEventFifoStartAddress(CAN_NODE *const pNode, uint32 address);

/**********************************************************************************************************************
 * Function:     Can_Std_SetTxEventFifoSize
 * Description:  Set Tx Event Fifo Size
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               size: 0= Tx Event FIFO disabled
 *                     1-32= Number of Tx Event FIFO elements
 *                     >32= Values greater than 32 are interpreted as 32
 *
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetTxEventFifoSize(CAN_NODE *const pNode, uint32 size);

/**********************************************************************************************************************
 * Function:     Can_Std_SetTxEventFifoWatermarkLevel
 * Description:  Set Tx event Fifo watermark level
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               level: 0= Watermark interrupt disabled
 *                      1-32= Level for Tx Event FIFO watermark interrupt (IR.TEFW)
 *                      >32= Watermark interrupt disabled
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetTxEventFifoWatermarkLevel(CAN_NODE *const pNode, uint32 level);

/**********************************************************************************************************************
 * Function:     Can_Std_GetTxEventFifoLevel
 * Description:  Get event FIFO fill level
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               level: Number of elements stored in Tx Event FIFO, range 0 to 32
 * Inout:        None
 * Output:       None
 * Return:       uint32: Value of event FIFO fill level
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/14   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetTxEventFifoLevel(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_DmuGetAddress
 * Description:  Get DMU TX\TXE\RX0\RX1 address
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               dmuAddressType: #arg CAN_STD_DMU_ADDRESS
 * Inout:        None
 * Output:       None
 * Return:       uint32: Value of DMU TX\TXE\RX0\RX1 address
 * Others:
 * History:
 *  Date         Author    Modified
 *  2023/09/19   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_DmuGetAddress(const CAN_NODE *const pNode, uint32 dmuAddressType);

/**********************************************************************************************************************
 * Function:     Can_Std_ClearDmuIR
 * Description:  Clear the interrupt of DMU IR
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               it: DMU interrupt #arg CAN_STD_IT_DMU_Flags
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date         Author    Modified
 *  2023/09/19   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Can_Std_ClearDmuIR(CAN_NODE *const pNode, uint32 it);

/**********************************************************************************************************************
 * Function:     Can_Std_GetDmuIR
 * Description:  Get DMU IR
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: DMU IR #arg CAN_STD_IT_DMU_Flags
 * Others:
 * History:
 *  Date         Author    Modified
 *  2023/09/19   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetDmuIR(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_SetDmuIE
 * Description:  Enable\Disable DMU IE
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               it: DMU IE #arg CAN_STD_IT_DMU_Flags
 *               enable: 0- Disable  interrupt
 *                       1- Enable  interrupt
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date         Author    Modified
 *  2023/09/19   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetDmuIE(CAN_NODE *const pNode, uint32 it, uint32 enable);

/**********************************************************************************************************************
 * Function:     Can_Std_GetDmuIE
 * Description:  Get DMU IE
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               it: DMU IE #arg CAN_STD_IT_DMU_Flags
 * Inout:        None
 * Output:       None
 * Return:       uint32: The value of DMU IE
 * Others:
 * History:
 *  Date         Author    Modified
 *  2024/01/02   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetDmuIE(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_ActivateRouterInterrupt
 * Description:  Enable\Disable router IE
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               it: same as M-CAN IE [0~29] #arg CAN_STD_InterruptsFlags
 *               bufferIndexes: Tx Buffer Indexes.
 *                     This parameter can be any combination of #arg CAN_STD_TxLocation.
 *                     This parameter is ignored if ActiveITs does not include one of the following
 *                       - CAN_STD_IT_TXCOMPLETED
 *                       - CAN_STD_IT_TXCANCELLATIONFIN
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date         Author    Modified
 *  2023/09/19   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_ActivateRouterInterrupt(CAN_NODE *const pNode, uint32 it, uint32 bufferIndexes);

/**********************************************************************************************************************
 * Function:     Can_Std_DeactivateRouterInterrupt
 * Description:  Enable\Disable router IE
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               it: same as M-CAN IE [0~29] #arg CAN_STD_InterruptsFlags
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date         Author    Modified
 *  2023/09/19   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_DeactivateRouterInterrupt(CAN_NODE *const pNode, uint32 it);

/**********************************************************************************************************************
 * Function:     Can_Std_GetRouterIR
 * Description:  Get router IR
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: All status of router group interrupt #arg CAN_STD_IT_RouterFlags
 * Others:
 * History:
 *  Date         Author    Modified
 *  2023/09/19   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetRouterIR(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_GetRouterIE
 * Description:  Get router IE
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: All router group interrupt signal line #arg CAN_STD_IT_RouterFlags
 * Others:
 * History:
 *  Date         Author    Modified
 *  2023/09/19   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetRouterIE(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_SetDmuRequest
 * Description:  DMU request line
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               dmuRequestType: #arg CAN_STD_DMU_REQUEST
 *                  Bit 0:DMA request enable signal for Tx FIFO/Queue data transmission in DMU
 *                  Bit 1:DMA request enable signal for Rx FIFO-0     data transmission in DMU
 *                  Bit 2:DMA request enable signal for Rx FIFO-1     data transmission in DMU
 *                  Bit 3:DMA request enable signal for Tx Event      data transmission in DMU
 *               enable: 0- is disable request line signal.
 *                       1- is enable request line signal. 
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date         Author    Modified
 *  2023/09/19   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetDmuRequest(CAN_NODE *const pNode, uint32 dmuRequestType, uint32 enable);

/**********************************************************************************************************************
 * Function:     Can_Std_GetDmuGateCnt
 * Description:  DMU request wait time
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 * Inout:        None
 * Output:       pRx0Counter: Rx0R request wait time counter
 *               pRx1Counter: Rx1R request wait time counter
 *               pTxCounter:  Tx request wait time counter
 *               pTxEventCounter: Tx event request wait time counter
 * Return:       None
 * Others:
 * History:
 *  Date         Author    Modified
 *  2023/09/19   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Can_Std_GetDmuGateCnt(const CAN_NODE *const pNode,
                                             uint32 *const pRx0Counter,
                                             uint32 *const pRx1Counter,
                                             uint32 *const pTxCounter,
                                             uint32 *const pTxEventCounter);

/**********************************************************************************************************************
 * Function:     Can_Std_ConfigExternalTimeStamp
 * Description:  CAN external time stamp counter unit
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        timeStampUnit: [0 ~ 0x7FFF], multiple of AHB frequency
 *
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date         Author    Modified
 *  2023/09/19   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_ConfigExternalTimeStamp(CAN_NODE *const pNode, uint32 timeStampUnit);

/**********************************************************************************************************************
 * Function:     Can_Std_SetExternalTimeStamp
 * Description:  Start\Stop CAN external time stamp counter
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        enable: 0- Start CAN external time stamp counter
 *                       1- Stop CAN external time stamp counter
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date         Author    Modified
 *  2023/09/19   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetExternalTimeStamp(CAN_NODE *const pNode, uint32 enable);

/**********************************************************************************************************************
 * Function:     Can_Std_GetExternalTimeStampCounter
 * Description:  Get CAN external time stamp counter
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       uint32: Value of CAN external time stamp counter
 * Others:
 * History:
 *  Date         Author    Modified
 *  2023/09/19   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Can_Std_GetExternalTimeStampCounter(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_SetStandardFilterId2
 * Description:  Set the standard filter ID for standard filter element
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pStdMsg: Standard filter element
 *               id: Standard Filter ID 2
 *               This bit field has a different meaning depending on the configuration of SFEC:
 *               1) SFEC = "001"..."110" Second ID of standard ID filter element
 *               2) SFEC = "111" Filter for Rx Buffers or for debug messages
 *               SFID2[10:9] decides whether the received message is stored into an Rx Buffer or treated as
 *               message A, B, or C of the debug message sequence.
 *               00= Store message into an Rx Buffer
 *               01= Debug Message A
 *               10= Debug Message B
 *               11= Debug Message C
 *               SFID2[8:6] is used to control the filter event pins m_ttcan_fe[2:0] at the Extension Interface. A one
 *               at the respective bit position enables generation of a pulse at the related filter event pin with the
 *               duration of one m_ttcan_hclk period in case the filter matches.
 *               SFID2[5:0] defines the offset to the Rx Buffer Start Address RXBC.RBSA for storage of a matching
 *               message
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/19   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetStandardFilterId2(CAN_STDMSG *const pStdMsg, uint32 id);

/**********************************************************************************************************************
 * Function:     Can_Std_SetStandardFilterId1
 * Description:  Set the filter ID 1 for standard filter element
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pStdMsg: Standard filter element
 *               id: Filter ID 1
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/19   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetStandardFilterId1(CAN_STDMSG *const pStdMsg, uint32 id);

/**********************************************************************************************************************
 * Function:     Can_Std_SetStandardFilterConfiguration
 * Description:  Set the standard filter element configuration
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pStdMsg: Standard filter element
 *               filterEleCfg:
 *                   000= Disable filter element
 *                   001= Store in Rx FIFO 0 if filter matches
 *                   010= Store in Rx FIFO 1 if filter matches
 *                   011= Reject ID if filter matches, not intended to be used with Sync messages
 *                   100= Set priority if filter matches, not intended to be used with Sync messages, no storage
 *                   101= Set priority and store in FIFO 0 if filter matches
 *                   110= Set priority and store in FIFO 1 if filter matches
 *                   111= Store into Rx Buffer or as debug message, configuration of SFT[1:0] ignored
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/19   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetStandardFilterConfiguration(CAN_STDMSG *const pStdMsg, uint32 config);

/**********************************************************************************************************************
 * Function:     Can_Std_SetStandardFilterType
 * Description:  Set the standard filter type for standard filter element
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pStdMsg: Specifies the pointer to standard filter element
 *               filterType: 00= Range filter from SFID1 to SFID2 (SFID2 >= SFID1)
 *                           01= Dual ID filter for SFID1 or SFID2
 *                           10= Classic filter: SFID1 = filter, SFID2 = mask
 *                           11= Filter element disabled
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/19   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetStandardFilterType(CAN_STDMSG *const pStdMsg, uint32 filterType);

/**********************************************************************************************************************
 * Function:     Can_Std_SetExtendedFilterId2
 * Description:  Set the extended filter ID 2 for extended filter element
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEtxMsg: Specifies the pointer to extended filter element
 *               id: Extended Filter ID 2
 *                1) EFEC = "001"..."110" Second ID of extended ID filter element
 *                2) EFEC = "111" Filter for Rx Buffers or for debug messages
 *                EFID2[10:9] decides whether the received message is stored into an Rx Buffer or treated as
 *                message A, B, or C of the debug message sequence.
 *                00= Store message into an Rx Buffer
 *                01= Debug Message A
 *                10= Debug Message B
 *                11= Debug Message C
 *                EFID2[8:6] is used to control the filter event pins m_ttcan_fe[2:0] at the Extension Interface. A one
 *                at the respective bit position enables generation of a pulse at the related filter event pin with the
 *                duration of one m_ttcan_hclk period in case the filter matches.
 *                EFID2[5:0] defines the offset to the Rx Buffer Start Address RXBC.RBSA for storage of a matching
 *                message
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/19   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetExtendedFilterId2(CAN_EXTMSG *const pEtxMsg, uint32 id);

/**********************************************************************************************************************
 * Function:     Can_Std_SetExtendedFilterType
 * Description:  Set the extended filter type for extended filter element
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pExtMsg: Extended filter element
 *               filterType: Filter type
 *                   00= Range filter from EFID1 to EFID2 (EFID2 >= EFID1)
 *                   01= Dual ID filter for EFID1 or EFID2
 *                   10= Classic filter: EFID1 = filter, EFID2 = mask
 *                   11= Range filter from EFID1 to EFID2 (EFID2 >= EFID1), XIDAM mask not applied
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/19   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetExtendedFilterType(CAN_EXTMSG *const pExtMsg, uint32 filterType);

/**********************************************************************************************************************
 * Function:     Can_Std_SetExtendedFilterId1
 * Description:  Set the extended filter ID 1 for extended filter element
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEtxMsg: Specifies the pointer to extended filter element
 *               id: Extended Filter ID 1
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/19   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetExtendedFilterId1(CAN_EXTMSG *const pEtxMsg, uint32 id);

/**********************************************************************************************************************
 * Function:     Can_Std_SetExtendedFilterConfiguration
 * Description:  Set the extended filter element configuration
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEtxMsg: Specifies the pointer to extended filter element
 *               filterEleCfg: Filter element configuration
 *                  000= Disable filter element
 *                  001= Store in Rx FIFO 0 if filter matches
 *                  010= Store in Rx FIFO 1 if filter matches
 *                  011= Reject ID if filter matches, not intended to be used with Sync messages
 *                  100= Set priority if filter matches, not intended to be used with Sync messages, no storage
 *                  101= Set priority and store in FIFO 0 if filter matches
 *                  110= Set priority and store in FIFO 1 if filter matches
 *                  111= Store into Rx Buffer or as debug message, configuration of EFT[1:0] ignored
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/19   01107      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Can_Std_SetExtendedFilterConfiguration(CAN_EXTMSG *const pEtxMsg, uint32 filterEleCfg);


/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
#if defined(CAN_REG_CHECK)
LOCAL_FORCEINLINE boolean Can_Register_ReadBack_Check(boolean state, uint32 value, uint32 expect)
{
    boolean ret;

    ret = state;
    if (expect != value)
    {
        ret &= FALSE;
    }

    return ret;
}
#else
LOCAL_FORCEINLINE boolean Can_Register_ReadBack_Check(boolean state, uint32 value, uint32 expect)
{
    (void)state;
    (void)expect;
    (void)value;

    return state;
}
#endif

LOCAL_FORCEINLINE uint32 Can_Std_ElementSzieToBytes(uint32 value)
{
    /* #Violation: can_std_h_REF_3 */
    /* #Violation: can_std_h_REF_5 */
    volatile uint8 elementSizeToBytes[8] = {16, 20, 24, 28, 32, 40, 56, 72};

    return elementSizeToBytes[value];
}

LOCAL_FORCEINLINE uint32 Can_Std_DlcToBytes(uint32 value)
{
    /* #Violation: can_std_h_REF_3 */
    /* #Violation: can_std_h_REF_5 */
    volatile uint8 dlcToBytes[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64};

    return dlcToBytes[value];
}

LOCAL_FORCEINLINE uint32 Can_Std_EscToBytes(uint32 value)
{
    /* #Violation: can_std_h_REF_3 */
    /* #Violation: can_std_h_REF_5 */
    volatile uint8 escToBytes[8] = {8, 12, 16, 20, 24, 32, 48, 64};

    return escToBytes[value];
}

LOCAL_FORCEINLINE boolean Can_Std_SetFDBaudrate(CAN_NODE *const pNode,
                                             uint32 prescaler,
                                             uint32 syncJumpWidth,
                                             uint32 timeSegment1,
                                             uint32 timeSegment2)
{
    boolean ret = TRUE;

    pNode->DBTP.B.DBRP   = prescaler;
    ret = Can_Register_ReadBack_Check(ret, pNode->DBTP.B.DBRP, prescaler);

    pNode->DBTP.B.DSJW   = syncJumpWidth;
    ret = Can_Register_ReadBack_Check(ret, pNode->DBTP.B.DSJW, syncJumpWidth);

    pNode->DBTP.B.DTSEG1 = timeSegment1;
    ret = Can_Register_ReadBack_Check(ret, pNode->DBTP.B.DTSEG1, timeSegment1);

    pNode->DBTP.B.DTSEG2 = timeSegment2;
    ret = Can_Register_ReadBack_Check(ret, pNode->DBTP.B.DTSEG2, timeSegment2);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetTxDelayCompensation(CAN_NODE *const pNode, uint32 enable)
{
    boolean ret = TRUE;  

    pNode->DBTP.B.TDC = enable;
    ret = Can_Register_ReadBack_Check(ret, pNode->DBTP.B.TDC, enable);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetTestLBCK(CAN_NODE *const pNode, uint32 enable)
{
    boolean ret = TRUE; 

    pNode->TEST.B.LBCK = enable;
    ret = Can_Register_ReadBack_Check(ret, pNode->TEST.B.LBCK, enable);
    
    return ret;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetTestLBCK(const CAN_NODE *const pNode)
{
    return pNode->TEST.B.LBCK;
}

LOCAL_FORCEINLINE void Can_Std_SetCccrInit(CAN_NODE *const pNode, uint32 enable)
{
    pNode->CCCR.B.INIT = enable;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetCccrInit(const CAN_NODE *const pNode)
{
    return pNode->CCCR.B.INIT;
}

LOCAL_FORCEINLINE boolean Can_Std_SetCccrConfigurationChange(CAN_NODE *const pNode, uint32 enable)
{
    boolean ret = TRUE;

    pNode->CCCR.B.CCE = enable;
    ret = Can_Register_ReadBack_Check(ret, pNode->CCCR.B.CCE, enable);

    return ret;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetCcccrConfigurationChange(const CAN_NODE *const pNode)
{
    return pNode->CCCR.B.CCE;
}

LOCAL_FORCEINLINE boolean Can_Std_SetCccrRestricted(CAN_NODE *const pNode, uint32 enable)
{
    boolean ret = TRUE;  

    pNode->CCCR.B.ROM = enable;
    ret = Can_Register_ReadBack_Check(ret, pNode->CCCR.B.ROM, enable);

    return ret;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetCccrRestricted(const CAN_NODE *const pNode)
{
    return pNode->CCCR.B.ROM;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetCccrClockStopACK(const CAN_NODE *const pNode)
{
    return pNode->CCCR.B.CSA;
}

LOCAL_FORCEINLINE boolean Can_Std_SetCccrClockRequestStop(CAN_NODE *const pNode, uint32 enable)
{
    boolean ret = TRUE;     
    pNode->CCCR.B.CSR = enable;
    ret = Can_Register_ReadBack_Check(ret, pNode->CCCR.B.CSR, enable);
    return ret;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetCccrClockRequestStop(const CAN_NODE *const pNode)
{
    return pNode->CCCR.B.CSR;
}

LOCAL_FORCEINLINE boolean Can_Std_SetMonitorMode(CAN_NODE *const pNode, uint32 enable)
{
    boolean ret = TRUE;

    pNode->CCCR.B.MON = enable;
    ret = Can_Register_ReadBack_Check(ret, pNode->CCCR.B.MON, enable);

    return ret;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetMonitorMode(const CAN_NODE *const pNode)
{
    return pNode->CCCR.B.MON;
}

LOCAL_FORCEINLINE boolean Can_Std_SetCccrDisableAutomaticRetransmission(CAN_NODE *const pNode, uint32 enable)
{
    boolean ret = TRUE;

    pNode->CCCR.B.DAR = enable;
    ret = Can_Register_ReadBack_Check(ret, pNode->CCCR.B.DAR, enable);

    return ret;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetCccrDisableAutomaticRetransmission(const CAN_NODE *const pNode)
{
    return pNode->CCCR.B.DAR;
}

LOCAL_FORCEINLINE boolean Can_Std_SetCccrTest(CAN_NODE *const pNode, uint32 enable)
{
    boolean ret = TRUE;

    pNode->CCCR.B.TEST = enable;
    ret = Can_Register_ReadBack_Check(ret, pNode->CCCR.B.TEST, enable);

    return ret;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetCccrTest(const CAN_NODE *const pNode)
{
    return pNode->CCCR.B.TEST;
}

LOCAL_FORCEINLINE boolean Can_Std_SetTestMode(CAN_NODE *const pNode, uint32 internalLoopBack)
{
    boolean ret = TRUE;    
    pNode->CCCR.B.TEST = 1U;
    ret = Can_Register_ReadBack_Check(ret, pNode->CCCR.B.TEST, 1U);

    pNode->TEST.B.LBCK = 1U;
    ret = Can_Register_ReadBack_Check(ret, pNode->TEST.B.LBCK, 1U);

    pNode->CCCR.B.MON = internalLoopBack;
    ret = Can_Register_ReadBack_Check(ret, pNode->CCCR.B.MON, internalLoopBack);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetCccrFD(CAN_NODE *const pNode, uint32 enable)
{
    boolean ret = TRUE;

    pNode->CCCR.B.FDOE = enable;
    ret = Can_Register_ReadBack_Check(ret, pNode->CCCR.B.FDOE, enable);

    return ret;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetCccrFD(const CAN_NODE *const pNode)
{
    return pNode->CCCR.B.FDOE;
}

LOCAL_FORCEINLINE boolean Can_Std_SetCccrBRS(CAN_NODE *const pNode, uint32 enable)
{
    boolean ret = TRUE;

    pNode->CCCR.B.BRSE = enable;
    ret = Can_Register_ReadBack_Check(ret, pNode->CCCR.B.BRSE, enable);

    return ret;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetCccrBRS(const CAN_NODE *const pNode)
{
    return pNode->CCCR.B.BRSE;
}

LOCAL_FORCEINLINE boolean Can_Std_SetWideMessageMark(CAN_NODE *const pNode, uint32 enable)
{
    boolean ret = TRUE;

    pNode->CCCR.B.WMM = enable;
    ret = Can_Register_ReadBack_Check(ret, pNode->CCCR.B.WMM, enable);

    return ret;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetWideMessageMark(const CAN_NODE *const pNode)
{
    return pNode->CCCR.B.WMM;
}

LOCAL_FORCEINLINE boolean Can_Std_SetCccrDisableProtocolExceptionHandling(CAN_NODE *const pNode, uint32 enable)
{
    boolean ret = TRUE;

    pNode->CCCR.B.PXHD = enable;
    ret = Can_Register_ReadBack_Check(ret, pNode->CCCR.B.PXHD, enable);

    return ret;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetCccrProtocolExceptionHandlingDisable(const CAN_NODE *const pNode)
{
    return pNode->CCCR.B.PXHD;
}

LOCAL_FORCEINLINE boolean Can_Std_SetCccrEdgeFiltering(CAN_NODE *const pNode, uint32 enable)
{
    boolean ret = TRUE;

    pNode->CCCR.B.EFBI = enable;
    ret = Can_Register_ReadBack_Check(ret, pNode->CCCR.B.EFBI, enable);

    return ret;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetCccrEdgeFiltering(const CAN_NODE *const pNode)
{
    return pNode->CCCR.B.EFBI;
}

LOCAL_FORCEINLINE boolean Can_Std_SetCccrTransmissionPause(CAN_NODE *const pNode, uint32 enable)
{
    boolean ret = TRUE;

    pNode->CCCR.B.TXP = enable;
    ret = Can_Register_ReadBack_Check(ret, pNode->CCCR.B.TXP, enable);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetBaudrate(CAN_NODE *const pNode,
                                              uint32 prescaler,
                                              uint32 syncJumpWidth,
                                              uint32 timeSegment1,
                                              uint32 timeSegment2)
{
    boolean ret = TRUE;

    pNode->NBTP.B.NBRP   = prescaler;
    ret = Can_Register_ReadBack_Check(ret, pNode->NBTP.B.NBRP, prescaler);

    pNode->NBTP.B.NSJW   = syncJumpWidth;
    ret = Can_Register_ReadBack_Check(ret, pNode->NBTP.B.NSJW, syncJumpWidth);

    pNode->NBTP.B.NTSEG1 = timeSegment1;
    ret = Can_Register_ReadBack_Check(ret, pNode->NBTP.B.NTSEG1, timeSegment1);

    pNode->NBTP.B.NTSEG2 = timeSegment2;
    ret = Can_Register_ReadBack_Check(ret, pNode->NBTP.B.NTSEG2, timeSegment2);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetimestampCounter(CAN_NODE *const pNode,  uint32 timestampPrescaler)
{
    boolean ret = TRUE;

    pNode->TSCC.B.TCP = timestampPrescaler;

    ret = Can_Register_ReadBack_Check(ret, pNode->TSCC.B.TCP, timestampPrescaler);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetTimestampCounterOperation(CAN_NODE *const pNode,  uint32 timestampOperation)
{
    boolean ret = TRUE;

    pNode->TSCC.B.TSS = timestampOperation;

    ret = Can_Register_ReadBack_Check(ret, pNode->TSCC.B.TSS, timestampOperation);

    /* External time stamp counter value used */
    if (pNode->TSCC.B.TSS == 0x02U) {
        /* Count Start */
        pNode->EXTMSTPCFG.B.TMSTART = 0x01U;
        ret = Can_Register_ReadBack_Check(ret, pNode->EXTMSTPCFG.B.TMSTART, 0x01U);
    }
    else {
        /* Count Stop */
        pNode->EXTMSTPCFG.B.TMSTART = 0x00U;
        ret = Can_Register_ReadBack_Check(ret, pNode->EXTMSTPCFG.B.TMSTART, 0x00U);
    }

    return ret;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetTimestampCounter(const CAN_NODE *const pNode)
{
    uint32 value;

    if (pNode->TSCC.B.TSS == 0x01U) {
        /* Internal TimestampCounter */
        value = pNode->TSCV.B.TSC;
    }
    else if (pNode->TSCC.B.TSS == 0x02U) {
        /* External TimestampCounter */
        value = pNode->EXTMSTPCFG.B.TMSTPCNT;
    }
    else {
        value = 0;
    }

    return value;
}

LOCAL_FORCEINLINE boolean Can_Std_ResetTimestampCounter(CAN_NODE *const pNode)
{
    boolean ret = TRUE;

    if (pNode->TSCC.B.TSS == 0x01U) {
        /* Internal timestampCounter reset*/
        pNode->TSCV.B.TSC = 0U;
    }

    /* External timestampCounter reset*/
    if (pNode->TSCC.B.TSS == 0x02U) {

        pNode->EXTMSTPCFG.B.TMSTART = 0x00U;
        ret = Can_Register_ReadBack_Check(ret, pNode->EXTMSTPCFG.B.TMSTART, 0x00U);

        pNode->EXTMSTPCFG.B.TMSTART = 0x01U;

        ret = Can_Register_ReadBack_Check(ret, pNode->EXTMSTPCFG.B.TMSTART, 0x01U);
    }

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_ConfigTimeoutCounter(CAN_NODE *const pNode,
                        uint32 timeoutOperation, uint32 timeoutPeriod)
{
    boolean ret = TRUE;

    pNode->TOCC.B.TOS = timeoutOperation;
    ret = Can_Register_ReadBack_Check(ret, pNode->TOCC.B.TOS, timeoutOperation);

    pNode->TOCC.B.TOP = timeoutPeriod;
    ret = Can_Register_ReadBack_Check(ret, pNode->TOCC.B.TOP, timeoutPeriod);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetTimeoutCounter(CAN_NODE *const pNode, uint32 enable)
{
    boolean ret = TRUE;

    pNode->TOCC.B.ETOC = enable;

    ret = Can_Register_ReadBack_Check(ret, pNode->TOCC.B.ETOC, enable);

    return ret;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetTimeoutCounter(const CAN_NODE *const pNode)
{
    return pNode->TOCV.B.TOC;
}

LOCAL_FORCEINLINE void Can_Std_ResetTimeoutCounter(CAN_NODE *const pNode)
{
    pNode->TOCV.B.TOC = 0U;
}

LOCAL_FORCEINLINE void Can_Std_GetErrorCounters(const CAN_NODE *const pNode,
                                                uint8 *const pTxErrorCnt,
                                                uint8 *const pRxErrorCnt,
                                                uint8 *const pRxErrorPassive,
                                                uint8 *const pErrorLogging)
{
    /* #Violation: can_std_h_REF_1 */
    CAN_ECR ecr;

    ecr = pNode->ECR;

    *pTxErrorCnt     = ecr.B.TEC;
    *pRxErrorCnt     = ecr.B.REC;
    *pRxErrorPassive = ecr.B.RP;
    *pErrorLogging   = ecr.B.CEL;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetProtocolStatus(const CAN_NODE *const pNode)
{
    /* Read the protocol status register */
    return pNode->PSR.U;
}

LOCAL_FORCEINLINE boolean Can_Std_ConfigTxDelayCompensation(CAN_NODE *const pNode, uint32 delay, uint32 filter_window)
{
    boolean ret = TRUE;
    /* set Transceiver Delay Compensation offset and filter window */
    pNode->TDCR.B.TDCO = delay;
    ret = Can_Register_ReadBack_Check(ret, pNode->TDCR.B.TDCO, delay);

    pNode->TDCR.B.TDCF = filter_window;
    ret = Can_Register_ReadBack_Check(ret, pNode->TDCR.B.TDCF, filter_window);

    return ret;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetInterruptFlag(const CAN_NODE *const pNode)
{
    return pNode->IR.U;
}

LOCAL_FORCEINLINE void Can_Std_ClearInterruptFlag(CAN_NODE *const pNode, uint32 it)
{
    pNode->IR.U = it;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetInterruptEnable(const CAN_NODE *const pNode)
{
    return pNode->IE.U;
}

LOCAL_FORCEINLINE boolean Can_Std_SetITLine(CAN_NODE *const pNode, uint32 it, uint32 line)
{
    boolean ret = TRUE;

   if (line == 0U)
   {
        pNode->ILS.U &= ~it;
        ret = Can_Register_ReadBack_Check(ret, (pNode->ILS.U&it), 0U);
   }

   if (line == 1U)
   {
        pNode->ILS.U |= it;
        ret = Can_Register_ReadBack_Check(ret, (pNode->ILS.U&it), it);
   }

   return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetIleEnt0(CAN_NODE *const pNode, uint32 enable)
{
    boolean ret = TRUE;

    pNode->ILE.B.EINT0 = enable;
    ret = Can_Register_ReadBack_Check(ret, pNode->ILE.B.EINT0, enable);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetIleEnt1(CAN_NODE *const pNode, uint32 enable)
{
    boolean ret = TRUE;

    pNode->ILE.B.EINT1 = enable;
    ret = Can_Register_ReadBack_Check(ret, pNode->ILE.B.EINT1, enable);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_ConfigGlobalFilter(CAN_NODE *const pNode,
                                                     uint32 NonMatchingStd,
                                                     uint32 NonMatchingExt,
                                                     uint32 RejectRemoteStd,
                                                     uint32 RejectRemoteExt)
{
    boolean ret = TRUE;

    pNode->GFC.B.ANFS = NonMatchingStd;
    ret = Can_Register_ReadBack_Check(ret, pNode->GFC.B.ANFS, NonMatchingStd);

    pNode->GFC.B.ANFE = NonMatchingExt;
    ret = Can_Register_ReadBack_Check(ret, pNode->GFC.B.ANFE, NonMatchingExt);

    pNode->GFC.B.RRFS = RejectRemoteStd;
    ret = Can_Register_ReadBack_Check(ret, pNode->GFC.B.RRFS, RejectRemoteStd);

    pNode->GFC.B.RRFE = RejectRemoteExt;
    ret = Can_Register_ReadBack_Check(ret, pNode->GFC.B.RRFE, RejectRemoteExt);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetStdFilterListStartAddress(CAN_NODE *const pNode, uint32 address)
{
    boolean ret = TRUE;
    uint32 tempaddress;

    tempaddress = (address >> 2U) & CAN_REG_CHECK_READ;
    pNode->SIDFC.B.FLSSA = tempaddress;
    ret = Can_Register_ReadBack_Check(ret, pNode->SIDFC.B.FLSSA, tempaddress);

    return ret;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetStdFilterListStartAddress(const CAN_NODE *const pNode)
{
    return ((uint32)pNode->SIDFC.B.FLSSA << 2U);
}

LOCAL_FORCEINLINE boolean Can_Std_SetStandardFilterListSize(CAN_NODE *const pNode, uint32 size)
{
    boolean ret = TRUE;

    pNode->SIDFC.B.LSS = size;
    ret = Can_Register_ReadBack_Check(ret, pNode->SIDFC.B.LSS, size);

    return ret;    
}

LOCAL_FORCEINLINE boolean Can_Std_SetExtFilterStartAddress(CAN_NODE *const pNode, uint32 address)
{
    boolean ret = TRUE;
    uint32 tempaddress;

    tempaddress = (address >> 2U) & CAN_REG_CHECK_READ;
    pNode->XIDFC.B.FLESA = tempaddress;
    ret = Can_Register_ReadBack_Check(ret, pNode->XIDFC.B.FLESA, tempaddress);

    return ret;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetExtFilterStartAddress(const CAN_NODE *const pNode)
{
    return ((uint32)pNode->XIDFC.B.FLESA << 2U);
}

LOCAL_FORCEINLINE boolean Can_Std_SetExtendedFilterListSize(CAN_NODE *const pNode, uint32 size)
{
    boolean ret = TRUE;

    pNode->XIDFC.B.LSE = size;
    ret = Can_Register_ReadBack_Check(ret, pNode->XIDFC.B.LSE, size);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetExtendedFilterXIDAM(CAN_NODE *const pNode, uint32 mask)
{
    boolean ret = TRUE;

    pNode->XIDAM.B.EIDM = mask;
    ret = Can_Register_ReadBack_Check(ret, pNode->XIDAM.B.EIDM, mask);

    return ret;
}

LOCAL_FORCEINLINE void Can_Std_GetHighProotityStatus(const CAN_NODE *const pNode,
                                                     uint8 *const pFilterList,
                                                     uint8 *const pFilterIndex,
                                                     uint8 *const pMessageStorage,
                                                     uint8 *const pMessageIndex)
{
    /* #Violation: can_std_h_REF_1 */
    /* #Violation: can_std_h_REF_4 */
    CAN_HPMS hpms;

    hpms = pNode->HPMS;

    *pFilterList     = hpms.B.FLST;
    *pFilterIndex    = hpms.B.FIDX;
    *pMessageStorage = hpms.B.MSI;
    *pMessageIndex   = hpms.B.BIDX;
}

LOCAL_FORCEINLINE uint64 Can_Std_GetRxBufferMessageAvailable(const CAN_NODE *const pNode)
{
    uint64 value;

    value = pNode->NDAT1.U;

    value += (uint64)pNode->NDAT2.U << 32U;

    return value;
}

LOCAL_FORCEINLINE boolean Can_Std_SetRxFifo0StartAddress(CAN_NODE *const pNode, uint32 address)
{
    boolean ret = TRUE;
    uint32 tempaddress;

    tempaddress = (address >> 2U) & CAN_REG_CHECK_READ;
    pNode->RX.F0C.B.F0SA = tempaddress;
    ret = Can_Register_ReadBack_Check(ret, pNode->RX.F0C.B.F0SA, tempaddress);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetRxFifo0Size(CAN_NODE *const pNode, uint32 size)
{
    boolean ret = TRUE;

    pNode->RX.F0C.B.F0S = size;
    ret = Can_Register_ReadBack_Check(ret, pNode->RX.F0C.B.F0S, size);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetRxFifo0WatermarkLevel(CAN_NODE *const pNode, uint32 level)
{
    boolean ret = TRUE;

    pNode->RX.F0C.B.F0WM = level;
    ret = Can_Register_ReadBack_Check(ret, pNode->RX.F0C.B.F0WM, level);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetRxFifo0OperatingMode(CAN_NODE *const pNode, uint32 mode)
{
    boolean ret = TRUE;

    pNode->RX.F0C.B.F0OM = mode;
    ret = Can_Register_ReadBack_Check(ret, pNode->RX.F0C.B.F0OM, mode);

    return ret;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetRxFifo0FillLevel(const CAN_NODE *const pNode)
{
    return pNode->RX.F0S.B.F0FL;
}

LOCAL_FORCEINLINE boolean Can_Std_SetRxBuffersStartAddress(CAN_NODE *const pNode, uint32 address)
{
    boolean ret = TRUE;
    uint32 tempaddress;

    tempaddress = (address >> 2U) & CAN_REG_CHECK_READ;
    pNode->RX.BC.B.RBSA = tempaddress;
    ret = Can_Register_ReadBack_Check(ret, pNode->RX.BC.B.RBSA, tempaddress);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetRxFifo1StartAddress(CAN_NODE *const pNode, uint32 address)
{
    boolean ret = TRUE;
    uint32 tempaddress;

    tempaddress = (address >> 2U) & CAN_REG_CHECK_READ;
    pNode->RX.F1C.B.F1SA = tempaddress;
    ret = Can_Register_ReadBack_Check(ret, pNode->RX.F1C.B.F1SA, tempaddress);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetRxFifo1Size(CAN_NODE *const pNode, uint32 size)
{
    boolean ret = TRUE;

    pNode->RX.F1C.B.F1S = size;
    ret = Can_Register_ReadBack_Check(ret, pNode->RX.F1C.B.F1S, size);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetRxFifo1WatermarkLevel(CAN_NODE *const pNode, uint32 level)
{
    boolean ret = TRUE;

    pNode->RX.F1C.B.F1WM = level;
    ret = Can_Register_ReadBack_Check(ret, pNode->RX.F1C.B.F1WM, level);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetRxFifo1OperatingMode(CAN_NODE *const pNode, uint32 mode)
{
    boolean ret = TRUE;

    pNode->RX.F1C.B.F1OM = mode;
    ret = Can_Register_ReadBack_Check(ret, pNode->RX.F1C.B.F1OM, mode);

    return ret;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetRxFifo1FillLevel(const CAN_NODE *const pNode)
{
    return pNode->RX.F1S.B.F1FL;
}

LOCAL_FORCEINLINE void Can_Std_ClearMessageFlag(CAN_NODE *const pNode)
{
    /* Clear RX FIFO-0 level */
    while (pNode->RX.F0S.B.F0FL > 0U)
    {
        pNode->RX.F0A.B.F0AI = pNode->RX.F0S.B.F0GI;
    }

    /* Clear RX FIFO-1 level */
    while (pNode->RX.F1S.B.F1FL > 0u)
    {
        pNode->RX.F1A.B.F1AI = pNode->RX.F1S.B.F1GI;
    }

    /* Clear RX dedicated buffer */
    pNode->NDAT1.U = 0xFFFFFFFFU;

    pNode->NDAT2.U = 0xFFFFFFFFU;

    /* Clear TX */
    pNode->TX.BCR.U = 0xFFFFFFFFU;

    /* Clear TX event FIFO level */
    while (pNode->TX.EFS.B.EFFL > 0U)
    {
        pNode->TX.EFA.B.EFAI = pNode->TX.EFS.B.EFGI;
    }
}

LOCAL_FORCEINLINE boolean Can_Std_SetRxBufferDataFieldSize(CAN_NODE *const pNode, uint32 size)
{
    boolean ret = TRUE;

    pNode->RX.ESC.B.RBDS = size;
    ret = Can_Register_ReadBack_Check(ret, pNode->RX.ESC.B.RBDS, size);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetRxFifo0DataFieldSize(CAN_NODE *const pNode, uint32 size)
{
    boolean ret = TRUE;

    pNode->RX.ESC.B.F0DS = size;
    ret = Can_Register_ReadBack_Check(ret, pNode->RX.ESC.B.F0DS, size);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetRxFifo1DataFieldSize(CAN_NODE *const pNode, uint32 size)
{
    boolean ret = TRUE;

    pNode->RX.ESC.B.F1DS = size;
    ret = Can_Register_ReadBack_Check(ret, pNode->RX.ESC.B.F1DS, size);

    return ret;    
}

LOCAL_FORCEINLINE boolean Can_Std_SetTxBuffersStartAddress(CAN_NODE *const pNode, uint32 address)
{
    boolean ret = TRUE;
    uint32 tempaddress;

    tempaddress = (address >> 2U) & CAN_REG_CHECK_READ;
    pNode->TX.BC.B.TBSA = tempaddress;
    ret = Can_Register_ReadBack_Check(ret, pNode->TX.BC.B.TBSA, tempaddress);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetDedicatedTxBuffersNumber(CAN_NODE *const pNode, uint32 number)
{
    boolean ret = TRUE;

    pNode->TX.BC.B.NDTB = number;
    ret = Can_Register_ReadBack_Check(ret, pNode->TX.BC.B.NDTB, number);

    return ret;    
}

LOCAL_FORCEINLINE boolean Can_Std_SetTransmitFifoQueueSize(CAN_NODE *const pNode, uint32 number)
{
    boolean ret = TRUE;

    pNode->TX.BC.B.TFQS = number;
    ret = Can_Register_ReadBack_Check(ret, pNode->TX.BC.B.TFQS, number);

    return ret;    
}

LOCAL_FORCEINLINE boolean Can_Std_SetTransmitFifoQueueMode(CAN_NODE *const pNode, uint32 mode)
{
    boolean ret = TRUE;

    pNode->TX.BC.B.TFQM = mode;
    ret = Can_Register_ReadBack_Check(ret, pNode->TX.BC.B.TFQM, mode);

    return ret;    
}

LOCAL_FORCEINLINE uint32 Can_Std_GetTxFifoFreeLevel(const CAN_NODE *const pNode)
{
    return pNode->TX.FQS.B.TFFL;
}

LOCAL_FORCEINLINE boolean Can_Std_SetTxBufferElrSize(CAN_NODE *const pNode, uint32 size)
{
    boolean ret = TRUE;

    pNode->TX.ESC.B.TBDS = size;
    ret = Can_Register_ReadBack_Check(ret, pNode->TX.ESC.B.TBDS, size);

    return ret;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetTxBufferPending(const CAN_NODE *const pNode)
{
    return pNode->TX.BRP.U;
}

LOCAL_FORCEINLINE void Can_Std_TxBufferRequest(CAN_NODE *const pNode, uint32 bufferIndex)
{
    pNode->TX.BAR.U = bufferIndex;
}

LOCAL_FORCEINLINE void Can_Std_AbortTxRequest(CAN_NODE *const pNode, uint32 bufferIndex)
{
    pNode->TX.BCR.U = bufferIndex;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetTxBufferTransOccured(const CAN_NODE *const pNode)
{
    return pNode->TX.BTO.U;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetTxBufferAbortFinished(const CAN_NODE *const pNode)
{
    return pNode->TX.BCF.U;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetTxBufferTransOccuredIE(const CAN_NODE *const pNode)
{
    return pNode->TX.BTIE.U;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetTxBufferAbortFinishedIE(const CAN_NODE *const pNode)
{
    return pNode->TX.BCIE.U;
}

LOCAL_FORCEINLINE boolean Can_Std_SetTxEventFifoStartAddress(CAN_NODE *const pNode, uint32 address)
{
    boolean ret = TRUE;
    uint32 tempaddress;

    tempaddress = (address >> 2U) & CAN_REG_CHECK_READ;
    pNode->TX.EFC.B.EFSA = tempaddress;
    ret = Can_Register_ReadBack_Check(ret, pNode->TX.EFC.B.EFSA, tempaddress);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetTxEventFifoSize(CAN_NODE *const pNode, uint32 size)
{
    boolean ret = TRUE;

    pNode->TX.EFC.B.EFS = size;
    ret = Can_Register_ReadBack_Check(ret, pNode->TX.EFC.B.EFS, size);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetTxEventFifoWatermarkLevel(CAN_NODE *const pNode, uint32 level)
{
    boolean ret = TRUE;

    pNode->TX.EFC.B.EFWM = level;
    ret = Can_Register_ReadBack_Check(ret, pNode->TX.EFC.B.EFWM, level);

    return ret;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetTxEventFifoLevel(const CAN_NODE *const pNode)
{
    return pNode->TX.EFS.B.EFFL;
}

LOCAL_FORCEINLINE uint32 Can_Std_DmuGetAddress(const CAN_NODE *const pNode, uint32 dmuAddressType)
{
    uint32 address;

    if (CAN_STD_DMU_ADDRESS_TX == dmuAddressType)
    {
        /* #Violation: can_std_h_REF_7 */
        address = (uint32)&pNode->DMU.DMU_TXElement;
    }
    else if (CAN_STD_DMU_ADDRESS_RX_0 == dmuAddressType)
    {
        /* #Violation: can_std_h_REF_7 */
        address = (uint32)&pNode->DMU.DMU_RX0Element;
    }
    else if (CAN_STD_DMU_ADDRESS_RX_1 == dmuAddressType)
    {
        /* #Violation: can_std_h_REF_7 */
        address = (uint32)&pNode->DMU.DMU_RX1Element;
    }
    else if (CAN_STD_DMU_ADDRESS_TXE == dmuAddressType)
    {
        /* #Violation: can_std_h_REF_7 */
        address = (uint32)&pNode->DMU.DMU_TXEventElement;
    }
    else
    {
        address = 0;
    }

    return address;
}

LOCAL_FORCEINLINE void Can_Std_ClearDmuIR(CAN_NODE *const pNode, uint32 it)
{
    pNode->DMU.DMUIR.U = it;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetDmuIR(const CAN_NODE *const pNode)
{
    return pNode->DMU.DMUIR.U;
}

LOCAL_FORCEINLINE boolean Can_Std_SetDmuIE(CAN_NODE *const pNode, uint32 it, uint32 enable)
{
    boolean ret = TRUE;

    if (enable != 0U)
    {
        pNode->DMU.DMUIE.U |=  it;
        ret = Can_Register_ReadBack_Check(ret, (pNode->DMU.DMUIE.U&it), it);
    }
    else{
        pNode->DMU.DMUIE.U &=  ~it;
        ret = Can_Register_ReadBack_Check(ret, (pNode->DMU.DMUIE.U&it), 0U);
    }

    return ret;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetDmuIE(const CAN_NODE *const pNode)
{
   return pNode->DMU.DMUIE.U;
}

LOCAL_FORCEINLINE boolean Can_Std_ActivateRouterInterrupt(CAN_NODE *const pNode, uint32 it, uint32 bufferIndexes)
{
    boolean ret = TRUE;
    /* Violation: can_std_h_REF_1 */
    CAN_RIE tempRIE;
    /* Violation: can_std_h_REF_1 */
    CAN_TX_BTIE tempBTIE;
    /* Violation: can_std_h_REF_1 */
    CAN_TX_BCIE tempBCIE;

    tempRIE.U = pNode->RIE.U;
    tempBTIE.U = pNode->TX.BTIE.U;
    tempBCIE.U = pNode->TX.BCIE.U;

    tempRIE.U |= it;
    pNode->RIE.U |= it;
    ret = Can_Register_ReadBack_Check(ret, pNode->RIE.U, tempRIE.U);

    if (0U != (it & CAN_STD_IT_TXCOMPLETED))
    {
        /* Enable Tx Buffer Transmission Interrupt to set TC flag in IR register,
        but interrupt will only occur if TC is enabled in IE register */
        tempBTIE.U |= bufferIndexes;
        pNode->TX.BTIE.U |= bufferIndexes;
        ret = Can_Register_ReadBack_Check(ret, pNode->TX.BTIE.U, tempBTIE.U);
    }

    if (0U != (it & CAN_STD_IT_TXCANCELLATIONFIN))
    {
        /* Enable Tx Buffer Cancellation Finished Interrupt to set TCF flag in IR register,
        but interrupt will only occur if TCF is enabled in IE register */
        tempBCIE.U |= bufferIndexes;
        pNode->TX.BCIE.U |= bufferIndexes;
        ret = Can_Register_ReadBack_Check(ret, pNode->TX.BCIE.U, tempBCIE.U);
    }

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_DeactivateRouterInterrupt(CAN_NODE *const pNode, uint32 it)
{
    boolean ret = TRUE;
    /* Violation: can_std_h_REF_1 */
    CAN_RIE tempRIE;

    if (0U != (it & CAN_STD_IT_TXCOMPLETED))
    {
        /* Disable Tx Buffer Transmission Interrupts */
        pNode->TX.BTIE.U = 0U;
        ret = Can_Register_ReadBack_Check(ret, pNode->TX.BTIE.U, 0U);
    }

    if (0U != (it & CAN_STD_IT_TXCANCELLATIONFIN))
    {
        /* Disable Tx Buffer Cancellation Finished Interrupt */
        pNode->TX.BCIE.U = 0U;
        ret = Can_Register_ReadBack_Check(ret, pNode->TX.BCIE.U, 0U);
    }

    tempRIE.U = pNode->RIE.U;
    tempRIE.U &=  ~it;
    pNode->RIE.U &=  ~it;
    ret = Can_Register_ReadBack_Check(ret, pNode->RIE.U, tempRIE.U);

    return ret;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetRouterIR(const CAN_NODE *const pNode)
{
   return pNode->ISREG.U;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetRouterIE(const CAN_NODE *const pNode)
{
   return pNode->ISREG_EN.U;
}

LOCAL_FORCEINLINE boolean Can_Std_SetDmuRequest(CAN_NODE *const pNode, uint32 dmuRequestType, uint32 enable)
{
    boolean ret = TRUE;

    if (CAN_STD_DMU_REQUEST_TX == dmuRequestType)
    {
        pNode->DREN.B.DMU_TXRE = enable;
        ret = Can_Register_ReadBack_Check(ret, pNode->DREN.B.DMU_TXRE, enable);
    }
    else if (CAN_STD_DMU_REQUEST_RX_0 == dmuRequestType)
    {
        pNode->DREN.B.DMU_RX0RE = enable;
        ret = Can_Register_ReadBack_Check(ret, pNode->DREN.B.DMU_RX0RE, enable);
    }
    else if (CAN_STD_DMU_REQUEST_RX_1 == dmuRequestType)
    {
        pNode->DREN.B.DMU_RX1RE = enable;
        ret = Can_Register_ReadBack_Check(ret, pNode->DREN.B.DMU_RX1RE, enable);
    }
    else if (CAN_STD_DMU_REQUEST_TXE == dmuRequestType)
    {
        pNode->DREN.B.DMU_TXERE = enable;
        ret = Can_Register_ReadBack_Check(ret, pNode->DREN.B.DMU_TXERE, enable);
    }
    else
    /* #Violation: can_std_h_REF_4 */
    {
        ret = FALSE;
    }

    return ret;
}

LOCAL_FORCEINLINE void Can_Std_GetDmuGateCnt(const CAN_NODE *const pNode,
                                             uint32 *const pRx0Counter,
                                             uint32 *const pRx1Counter,
                                             uint32 *const pTxCounter,
                                             uint32 *const pTxEventCounter)
{
    /* #Violation: can_std_h_REF_1 */
    /* #Violation: can_std_h_REF_4 */
    CAN_DGC1 DGC1;
    /* #Violation: can_std_h_REF_1 */
    /* #Violation: can_std_h_REF_4 */
    CAN_DGC2 DGC2;

    DGC1 = pNode->DGC1;

    DGC2 = pNode->DGC2;

    *pRx0Counter = DGC1.B.RX0R_CNT;

    *pRx1Counter = DGC2.B.RX1R_CNT;

    *pTxCounter  = DGC1.B.TXR_CNT;

    *pTxEventCounter = DGC2.B.TXER_CNT;
}

LOCAL_FORCEINLINE boolean Can_Std_ConfigExternalTimeStamp(CAN_NODE *const pNode, uint32 timeStampUnit)
{
    boolean ret = TRUE;

    pNode->EXTMSTPCFG.B.TMSTPUNIT = timeStampUnit;

    ret = Can_Register_ReadBack_Check(ret, pNode->EXTMSTPCFG.B.TMSTPUNIT, timeStampUnit);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetExternalTimeStamp(CAN_NODE *const pNode, uint32 enable)
{
    boolean ret = TRUE;

    pNode->EXTMSTPCFG.B.TMSTART = enable;

    ret = Can_Register_ReadBack_Check(ret, pNode->EXTMSTPCFG.B.TMSTART, enable);
    
    return ret;
}

LOCAL_FORCEINLINE uint32 Can_Std_GetExternalTimeStampCounter(const CAN_NODE *const pNode)
{
    return pNode->EXTMSTPCFG.B.TMSTPCNT;
}

LOCAL_FORCEINLINE boolean Can_Std_SetStandardFilterId2(CAN_STDMSG *const pStdMsg, uint32 id)
{
    boolean ret = TRUE;

    pStdMsg->S0.B.SFID2 = id;
    ret = Can_Register_ReadBack_Check(ret, pStdMsg->S0.B.SFID2, id);

    return ret;  
}

LOCAL_FORCEINLINE boolean Can_Std_SetStandardFilterId1(CAN_STDMSG *const pStdMsg, uint32 id)
{
    boolean ret = TRUE;

    pStdMsg->S0.B.SFID1 = id;
    ret = Can_Register_ReadBack_Check(ret, pStdMsg->S0.B.SFID1, id);

    return ret;    
}

LOCAL_FORCEINLINE boolean Can_Std_SetStandardFilterConfiguration(CAN_STDMSG *const pStdMsg, uint32 config)
{
    boolean ret = TRUE;

    pStdMsg->S0.B.SFEC = config;
    ret = Can_Register_ReadBack_Check(ret, pStdMsg->S0.B.SFEC, config);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetStandardFilterType(CAN_STDMSG *const pStdMsg, uint32 filterType)
{
    boolean ret = TRUE;

    pStdMsg->S0.B.SFT = filterType;
    ret = Can_Register_ReadBack_Check(ret, pStdMsg->S0.B.SFT, filterType);

    return ret;  
}

LOCAL_FORCEINLINE boolean Can_Std_SetExtendedFilterId2(CAN_EXTMSG *const pEtxMsg, uint32 id)
{
    boolean ret = TRUE;

    pEtxMsg->F1.B.EFID2 = id;
    ret = Can_Register_ReadBack_Check(ret, pEtxMsg->F1.B.EFID2, id);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetExtendedFilterType(CAN_EXTMSG *const pExtMsg, uint32 filterType)
{
    boolean ret = TRUE;

    pExtMsg->F1.B.EFT = filterType;
    ret = Can_Register_ReadBack_Check(ret, pExtMsg->F1.B.EFT, filterType);

    return ret;
}

LOCAL_FORCEINLINE boolean Can_Std_SetExtendedFilterId1(CAN_EXTMSG *const pEtxMsg, uint32 id)
{
    boolean ret = TRUE;

    pEtxMsg->F0.B.EFID1 = id;
    ret = Can_Register_ReadBack_Check(ret, pEtxMsg->F0.B.EFID1, id);

    return ret;    
}

LOCAL_FORCEINLINE boolean Can_Std_SetExtendedFilterConfiguration(CAN_EXTMSG *const pEtxMsg, uint32 filterEleCfg)
{
    boolean ret = TRUE;

    pEtxMsg->F0.B.EFEC = filterEleCfg;
    ret = Can_Register_ReadBack_Check(ret, pEtxMsg->F0.B.EFEC, filterEleCfg);

    return ret;
}

/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:     Can_Std_GetModuleBase
 * Description:  Get CAN module base address.
 *
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *
 * Inout:        None
 * Output:       None
 * Return:       uint32: The CAN module base address.
 * Others:
 * History:
 *  Date         Author    Modified
 *  2023/09/03    01107      Create
 *********************************************************************************************************************/
extern uint32 Can_Std_GetModuleBase(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_GetModuleRAMStartAddr
 * Description:  Get CAN module RAM start address.
 *
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *
 * Inout:        None
 * Output:       None
 * Return:       uint32: The CAN module RAM start address.
 * Others:
 * History:
 *  Date         Author    Modified
 *  2023/09/03    01107      Create
 *********************************************************************************************************************/
extern uint32 Can_Std_GetModuleRAMStartAddr(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_GetModuleRAMEndAddr
 * Description:  Get CAN Module message end address.
 *
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *
 * Inout:        None
 * Output:       None
 * Return:       uint32: The CAN module RAM end address.
 * Others:
 * History:
 *  Date         Author    Modified
 *  2023/09/03    01107      Create
 *********************************************************************************************************************/
extern uint32 Can_Std_GetModuleRAMEndAddr(const CAN_NODE *const pNode);

/**********************************************************************************************************************
 * Function:     Can_Std_ActivateNotification
 * Description:  Enable interrupts.
 *
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               activeITs: indicates which interrupts will be enabled.
 *                     This parameter can be any combination of #arg CAN_STD_Interrupts.
 *              bufferIndexes: Tx Buffer Indexes.
 *                     This parameter can be any combination of #arg CAN_STD_TxLocation.
 *                     This parameter is ignored if ActiveITs does not include one of the following
 *                       - CAN_STD_IT_TXCOMPLETED
 *                       - CAN_STD_IT_TXCANCELLATIONFIN
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date         Author    Modified
 *  2023/09/03    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Std_ActivateNotification(CAN_NODE *const pNode, uint32 activeITs, uint32 bufferIndexes);

/**********************************************************************************************************************
 * Function:     Can_Std_DeactivateNotification
 * Description:  Disable interrupts.
 *
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               inactiveITs: indicates which interrupts will be disabled.
 *               This parameter can be any combination of #arg CAN_STD_Interrupts.
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date         Author    Modified
 *  2023/09/03    01107      Create
 *********************************************************************************************************************/
extern boolean Can_Std_DeactivateNotification(CAN_NODE *const pNode, uint32 inactiveITs);

/**********************************************************************************************************************
 * Function:     Can_Std_AddMessageToTxBuffer
 * Description:  Add a message to the TX FIFO/Queue and activate the corresponding transmission request
 *               Add a message to a dedicated TX buffer
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               txLocation: FIFO\QUEUE or dedicated TX buffer number of #arg CAN_STD_TxLocation
 *               pTxHeaderSrc: Specifies the pointer of CAN_TXMSG structure.
 *               immediatelySend: Require manual request to send if set 0.
 *                                Send immediately if set 1.
 *               pTxData: pointer to a buffer containing the pay-load of the TX frame.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date         Author    Modified
 *  2023/09/03    01107      Create
 *********************************************************************************************************************/
extern void Can_Std_AddMessageToTxBuffer(CAN_NODE *const pNode, uint32 txLocation, const CAN_TXMSG *const pTxHeaderSrc,
                                                 uint32 immediatelySend, const uint8 *const pTxData);

/**********************************************************************************************************************
 * Function:     Can_Std_GetRxMessage
 * Description:  Get an CAN frame from the Rx Buffer/FIFO zone into the message RAM.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               rxLocation: FIFO 0 or FIFO 1 or dedicated RX buffer number of #arg CAN_STD_RxLocation
 *               pHeader: Specifies the pointer to receive header
 *               pData: pointer to a buffer where the pay-load of the RX frame will be stored
 * Inout:        None
 * Output:       pHeader: Specifies the pointer to receive header
 * Return:       None
 * Others:
 * History:
 *  Date         Author    Modified
 *  2023/09/03   01107     Create
 *********************************************************************************************************************/
extern void Can_Std_GetRxMessage(CAN_NODE *const pNode, uint32 rxLocation, CAN_RXMSG *const pHeader, uint8 *const pData);

/**********************************************************************************************************************
 * Function:     Can_Std_GetTxEvent
 * Description:  Get an CAN TX event from the Tx Event FIFO zone into the message RAM
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               pHeader: Specifies the pointer to the CAN TX event header
 * Inout:        None
 * Output:       pHeader: Specifies the pointer to receive header
 * Return:       None
 * Others:
 * History:
 *  Date         Author    Modified
 *  2023/09/03   01107     Create
 *********************************************************************************************************************/
extern void Can_Std_GetTxEvent(CAN_NODE *const pNode, CAN_TXEVENT* const pHeader);

/**********************************************************************************************************************
 * Function:     Can_Std_SetITRouterLine
 * Description:  Set the selected interrupt to the selected interrupt line
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specify a pointer to the CAN node register
 *               it: Type of Interrupt, see #arg CAN_STD_IT_RouterFlags
 *               itLine: Interrupt line number(0 ~ 15)
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/08    01107      Create
 *  2025/05/08    00976      Modify
 * 
 *********************************************************************************************************************/
extern boolean Can_Std_SetITRouterLine(CAN_NODE *const pNode, uint32 it, uint32 itLine);

#define CAN_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: can_std_h_REF_6 */
#include "Can_MemMap.h"

#endif /* CAN_STD_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
