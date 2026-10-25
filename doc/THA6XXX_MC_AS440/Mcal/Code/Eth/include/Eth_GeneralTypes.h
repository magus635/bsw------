/****************************************************************************************************
 *
 ****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Eth_GeneralTypes.h
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : Ethernet
 *
 *   brief                 : This file contains all type definitions of Ethernet Driver
 *
 *   Autosar Version       : 4.4.0
 *
 *   Build Version         : Cortex-R52+/THA6xxx
 *
 *   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
 *
 ****************************************************************************************************/

/*
*#Violation Summary
*
*
*#Eth_GeneralTypes_h_REF_1:MISRAC2012-Dir-4.8; 
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the 
* code complexity.
*
*#Eth_GeneralTypes_h_REF_2:MISRAC2012-Rule-2.3; 
* Justification: Reserved types are defined in AUTOSAR specifications.*
*/
#ifndef ETH_GENERALTYPES_H
#define ETH_GENERALTYPES_H

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
/* \[SWS_Eth_00149][SWS_Eth_00026] */
#include "ComStack_Types.h"

/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
/* \[SWS_Eth_00160]*/
/* This type defines the Ethernet frame type used in the Ethernet frame header */
typedef uint16       Eth_FrameType;
/* \[SWS_Eth_00161] defines the Ethernet data type used for data transmission */
typedef uint8        Eth_DataType;
/* \[SWS_Eth_00175] Ethernet buffer identifier type */
typedef uint32       Eth_BufIdxType;
/* \[SWS_Eth_00159]*/
typedef enum
{
    ETH_STATE_UNINIT = 0U, /* The driver has not been initialized yet */
    ETH_STATE_INIT         /* The driver has been configured  */
} Eth_StateType;

/* Define the controller modes */
typedef enum
{
    ETH_MODE_DOWN = 0U, /* Controller disabled */
    ETH_MODE_ACTIVE     /* Controller enabled */
} Eth_ModeType;

/* Define the action to be taken for the MAC address */
typedef enum
{
    ETH_ADD_TO_FILTER = 0U, /* Add address to the filter */
    ETH_REMOVE_FROM_FILTER  /* Remove address */
} Eth_FilterActionType;

/* \[SWS_Eth_00177]Depending on the HW, quality information regarding the evaluated time stamp might be
supported. If not supported, the value shall be always Valid. For Uncertain and Invalid values, the
upper layer shall discard the time stamp */
typedef enum
{
  ETH_VALID = 0x0U,
  ETH_INVALID,
  ETH_UNCERTAIN
}Eth_TimeStampQualType;

/* Structure for ETH the time stamp structure */
/* #Violation: Eth_GeneralTypes_h_REF_1 */
typedef struct
{
    uint32 nanoseconds; /* Nanoseconds part of the time */
    uint32 seconds;     /* 32 bit LSB of the 48 bits Seconds */
    uint16 secondsHi;   /* 16 bit MSB of the 48 bits Seconds */
} Eth_TimeStampType;


/* Structure is used to express time differences */
typedef struct
{
    Eth_TimeStampType diff; /* Time difference */
    boolean sign;           /* Positive (True) Or negative (False) time */
} Eth_TimeIntDiffType;


/* Structure is used to express frequency ratios */
/* #Violation: Eth_GeneralTypes_h_REF_1 */
typedef struct
{
    Eth_TimeIntDiffType IngressTimeStampDelta; /* IngressTimeStampSync2 -IngressTimeStampSync1 */
    Eth_TimeIntDiffType OriginTimeStampDelta;  /* OriginTimeStampSync2[FUP2]-OriginTimeStampSync1[FUP1] */
} Eth_RateRatioType;



/* Statistic counter for diagnostics */
/* #Violation: Eth_GeneralTypes_h_REF_1 */
typedef struct
{
    uint32 DropPktBufOverrun; /* Dropped packets due to buffer overrun */
    uint32 DropPktCrc;        /* Dropped packets due to CRC errors*/
    uint32 UndersizePkt;      /* Number of undersize packets which were less than 64 octets long
                                 (excluding framing bits, but including FCS octets) */
    uint32 OversizePkt;       /* Number of oversize packets which are longer than 1518 octets
                                 (excluding framing bits, but including FCS octets) */
    uint32 AlgnmtErr;         /* Number of alignment errors */
    uint32 SqeTestErr;        /* SQE test error according to IETF RFC1643 dot3StatsSQETestErrors*/
    uint32 DiscInbdPkt;       /* The number of inbound packets which were chosen to be discarded
                                 even though no errors had been detected to prevent their being
                                 deliverable to a higher-layer protocol */
    uint32 ErrInbdPkt;        /* Total number of erroneous inbound packets*/
    uint32 DiscOtbdPkt;       /* The number of outbound packets which were chosen to be discarded even
                                 though no errors had been detected to prevent their being transmitted */
    uint32 ErrOtbdPkt;        /* Total number of erroneous outbound packets */
    uint32 SnglCollPkt;       /* Single collision frames: A count of successfully transmitted frames on
                                 a particular interface for which transmission is inhibited by exactly
                                 one collision */
    uint32 MultCollPkt;       /* Multiple collision frames: A count of successfully transmitted frames
                                 on a particular interface for which transmission is inhibited by more
                                 than one collision */
    uint32 DfrdPkt;           /* Number of deferred transmission: A count of frames for which the first
                                 transmission attempt on a particular interface is delayed because the
                                 medium is busy */
    uint32 LatCollPkt;        /* Number of late collisions: The number of times that a collision is
                                 detected on a  particular interface later than 512 bit times into the
                                 transmission of a packet */
    uint32 HwDepCtr0;         /* Hardware dependent counter value*/
    uint32 HwDepCtr1;         /* Hardware dependent counter value */
    uint32 HwDepCtr2;         /* Hardware dependent counter value */
    uint32 HwDepCtr3;         /* Hardware dependent counter value*/
} Eth_CounterType;

/* Structure for ETH statistic - Rx*/
/* #Violation: Eth_GeneralTypes_h_REF_1 */
typedef struct
{
    uint32 RxStatsDropEvents;     /* The total number of events in which packets were dropped by the
                                     probe due to lack of resources*/
    uint32 RxStatsOctets;         /* The total number of octets of data (including those in bad packets)
                                     received on the network (excluding framing bits but including FCS
                                     octets) */
    uint32 RxStatsPkts;           /* The total number of packets (including bad packets, broadcast packets,
                                     and multicast packets) received */
    uint32 RxStatsBroadcastPkts;  /* The total number of good packets received that were directed to the
                                     broadcast address */
    uint32 RxStatsMulticastPkts;  /* The total number of good packets received that were directed to a
                                     multicast address */
    uint32 RxStatsCrcAlignErrors; /* The total number of packets received that had a length of bertween 64
                                     and 1518 octets that had either a bad Frame Check Sequence (FCS) with
                                     an integral number of octets (FCS Error) or a bad FCS with a
                                     non-integral number of octets (Alignment Error) */
    uint32 RxStatsUndersizePkts;  /* The total number of packets received that were less than 64 octets
                                     long (excluding framing bits, but including FCS octets) and were
                                     otherwise well formed */
    uint32 RxStatsOversizePkts;   /* The total number of packets received that were longer than 1518 octets
                                     (excluding framing bits, but including FCS octets) and were otherwise
                                     well formed */
    uint32 RxStatsFragments;      /* The total number of packets received that were less than 64 octets in
                                     length (excluding framing bits but including FCS octets) and  had either
                                     a bad Frame Check Sequence (FCS) with an integral number of octets
                                     (FCS Error) or a bad FCS with a non-integral number of octets
                                     (Alignment Error) */
    uint32 RxStatsJabbers;        /* The total number of packets received that were longer than 1518 octets,
                                     and had either a bad Frame Check Sequence (FCS) with an integral number
                                     of octets (FCS Error) or a bad FCS with a non integral number of octets
                                     (Alignment Error) */
    uint32 RxStatsCollisions;     /* The best estimate of the total number of collisions on this Ethernet
                                     segment */
    uint32 RxStatsPkts64Octets;   /* The total number of packets (including bad packets) received that were
                                     64 octets in length */
    uint32 RxStatsPkts65to127Octets; /* The total number of packets (including bad packets) received that were
                                        between 65 and 127 octets in length */
    uint32 RxStatsPkts128to255Octets; /* The total number of packets (including bad packets) received that were
                                         between 128 and 255 octets in length */
    uint32 RxStatsPkts256to511Octets; /* The total number of packets (including bad packets) received that were
                                         between 256 and 511 octets in length */
    uint32 RxStatsPkts512to1023Octets; /* The total number of packets (including bad packets) received that were
                                          between 512 and 1023 octets in length */
    uint32 RxStatsPkts1024to1518Octets; /* The total number of packets (including bad packets) received that
                                           were between 1024 and 1518octets in length */
    uint32 RxUnicastFrames; /* The number of subnetwork-unicast packets delivered to a higher-layer protocol */
} Eth_RxStatsType;

/* Structure for ETH statistic - Tx */
/* #Violation: Eth_GeneralTypes_h_REF_1 */
typedef struct
{
    uint32 TxNumberOfOctets; /* The total number of octets transmitted out of the interface, including
                                framing characters */
    uint32 TxNUcastPkts;     /* The total number of packets that higher level protocols requested be
                                transmitted to a non-unicast (i.e., a subnetwork broadcast or
                                subnetwork-multicast) address, including those that were discarded or not sent */
    uint32 TxUniCastPkts;    /* The total number of packets that highe level protocols requested be transmitted
                                to a subnetwork-unicast address, including those that were discarded or not sent */
} Eth_TxStatsType;

/* Structure for transmission error counters */
/* #Violation: Eth_GeneralTypes_h_REF_1 */
typedef struct
{
    uint32 TxDroppedNoErrorPkts; /* The number of outbound packets which were chosen to be discarded even though no
                                    errors had been detected to prevent their being transmitted. One possible reason
                                    for discarding such a packet could be to free up buffer space*/
    uint32 TxDroppedErrorPkts;   /* transmitted because of errors */
    uint32 TxDeferredTrans;      /* A count of frames for which the first transmission attempt on a particular
                                    interface is delayed because the medium is busy. The count represented by an
                                    instance of this object does not include frames involved in collisions */
    uint32 TxSingleCollision;    /* A count of successfully transmitted frames on a particular interface for which
                                    transmission is inhibited by exactly one collision. A frame that is counted by
                                    an instance of this object is also counted by the corresponding instance of either
                                    the txUniCastPkts and txNUcastPkts and is not counted by the corresponding instance
                                    of the txMultipleCollision object */
    uint32 TxMultipleCollision;  /* A count of successfully transmitted frames on a particular interface for which
                                    transmission is inhibited by more than one collision. A frame that is counted by an
                                    instance of this object is also counted by the corresponding instance of either the
                                    txUniCastPkts and txNUcastPkts and is not counted by the corresponding instance of
                                    the txSingleCollision object */
    uint32 TxLateCollision;      /* The number of times that a collision is detected on a particular interface later than
                                    512 bit-times into the transmission of a packet. Five hundred and twelve bit-times
                                    corresponds to 51.2 microseconds on a 10 Mbit/s system. A (late) collision included
                                    in a count represented by an instance of this object is also considered as a (generic)
                                    collision for purposes of other collision-related statistics */
    uint32 TxExcessiveCollison;  /* A count of frames for which transmission on a particular interface fails due to
                                    excessive collisions*/
} Eth_TxErrorCounterValuesType;



/* \[SWS_Eth_00162] Used as out parameter in Eth_Receive() indicates whether a frame has been received
 * and if so, whether more frames are available or frames got lost.*/
/* Define the Ethernet reception status */
typedef enum
{
    ETH_RECEIVED = 0U,               /* A frame has been received and there are no more frames in the queue */
    ETH_NOT_RECEIVED,                /* No frames received */
    ETH_RECEIVED_MORE_DATA_AVAILABLE /* A frame received and at least another one in the queue detected */
} Eth_RxStatusType;








/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/




/*SWS_Eth_91001 This type is used to read out addresses from the address resolution logic (ARL) table of the
 * switch.*/
/* #Violation: Eth_GeneralTypes_h_REF_1*/
typedef struct
{
    uint8  macAddress[6]; /*Specifies the MAC address*/
    uint16 VlanId;        /*Specifies the VLAN address*/
    uint32 SwitchPort;    /*Specifies the ports of the switch as bit mask*/
/* #Violation: Eth_GeneralTypes_h_REF_2*/
} Eth_MacVlanType;
/* Structure for controller's state */

#endif /* ETH_GENERALTYPES_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

