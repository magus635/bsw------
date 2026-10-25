/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    psi5_std.h
 * Author:      01849
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: PSI5 standard driver source file.
 *              This file contains implementations for PSI5 standard driver.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #psi5_std_h_REF_1:MISRAC2012-Rule-19.2;
* Justification:Define a union type to assign a one-time value to a register.
*
* #psi5_std_h_REF_2:MISRAC2012-Rule-2.3;
* Justification:The members of the type are used in configuration-generated code.
*
* #psi5_std_h_REF_3:MISRAC2012-Rule-19.2;
* Justification:Using unions for bit-field access to registers.
*
* #psi5_std_h_REF_4:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
* #psi5_std_h_REF_5:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #psi5_std_h_REF_6:MISRAC2012-Dir-4.8
* Justification:Apply such struct/union definitions to simplify the code structure and reduce the code complexity.
*
* #psi5_std_h_REF_7:CERTC-DCL12-C;
* Justification:Apply such struct/union definitions to simplify the code structure and reduce the code complexity.
*/
#ifndef PSI5_STD_H_
#define PSI5_STD_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "psi5_register.h"
#include "Platform_Types.h"
#include "compilertypes.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
**********************************************************************************************************************/
/* ^PSI5_CH^ chip select slot max */
#define PSI5_NUM_SLOTS (6U)
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* Psi5 protect enum */
typedef enum
{
    PSI5_PROT_PARITY = 0U,  /* Brief parity selection */
    PSI5_PROT_CRC    = 1U   /* Brief crc selection */
} Psi5_Prot;

/* Psi5 messaging bits enum */
typedef enum
{
    PSI5_MESSAGINGBITS_ABSENT  = 0U, /* Brief no messaging bits */
    PSI5_MESSAGINGBITS_PRESENT = 1U  /* Brief 2 messaging bits */
/* #Violation: psi5_std_h_REF_2 */
} Psi5_MessagingBits;

/* Psi5 communicate mode enum */
typedef enum
{
    PSI5_COMMUNICATEMODE_SYNC  = 0U, /* Brief sync communicate mode */
    PSI5_COMMUNICATEMODE_ASYNC = 1U  /* Brief async communicate mode */
} Psi5_CommunicateMode;

/* Psi5 frame expectation enum */
typedef enum
{
    PSI5_FRAMEEXPECTATION_NOTEXPECTED = 0U,  /* Brief no frame is expected */
    PSI5_FRAMEEXPECTATION_EXPECTED    = 1U   /* Brief frame is expected */
/* #Violation: psi5_std_h_REF_2 */
} Psi5_FrameExpectation;

/* Psi5 Crc mode enum */
typedef enum
{
    PSI5_CRCMODE_HARDWARE = 0U,  /* Brief specifies crc hardware generated */
    PSI5_CRCMODE_SOFTWARE = 1U   /* Brief specifies crc software generated */
} Psi5_CrcMode;

/* Psi5 auto stuff enum */
typedef enum
{
    PSI5_AUTOSTUFF_DISABLE = 0U,  /* Brief specifies auto stuff disable */
    PSI5_AUTOSTUFF_ENABLE  = 1U   /* Brief specifies auto stuff enable */
} Psi5_AutoStuff;

/* Psi5 auto start sequence enum */
typedef enum
{
    PSI5_AUTOSTARTSEQUE_DISABLE = 0U,  /* Brief specifies auto start sequence disable */
    PSI5_AUTOSTARTSEQUE_ENABLE  = 1U   /* Brief specifies auto start sequence enable */
} Psi5_AutoStartSeque;

/* Psi5 slot ID enum */
typedef enum
{
    PSI5_SLOT_0 = 0U,      /* Brief slot 0 */
    PSI5_SLOT_1 = 1U,      /* Brief slot 1 */
    PSI5_SLOT_2 = 2U,      /* Brief slot 2 */
    PSI5_SLOT_3 = 3U,      /* Brief slot 3 */
    PSI5_SLOT_4 = 4U,      /* Brief slot 4 */
    PSI5_SLOT_5 = 5U,      /* Brief slot 5 */
    PSI5_SLOT_MAX          /* Brief slot max */
} Psi5_Slot;

/* Psi5 channel ID enum */
typedef enum
{
    PSI5_CHANNELID_0    = 0,   /* Brief specifies PSI5 channel 0 */
    PSI5_CHANNELID_1    = 1,   /* Brief specifies PSI5 channel 1 */
    PSI5_CHANNELID_2    = 2,   /* Brief specifies PSI5 channel 2 */
    PSI5_CHANNELID_3    = 3    /* Brief specifies PSI5 channel 3 */
} Psi5_ChannelId;

/* Psi5 Tx type enum */
typedef enum
{
    PSI5_TXTYPE_CTRLDATA      = 0U,  /* Brief specifies tx control data */
    PSI5_TXTYPE_PAYLOADDATA   = 1U   /* Brief specifies tx payload data */
/* #Violation: psi5_std_h_REF_2 */
} Psi5_TxType;

/* Psi5 Rx type enum */
typedef enum
{
    PSI5_RXTYPE_CTRLDATA     = 0U,   /* Brief specifies rx control data */
    PSI5_RXTYPE_TIMESTAMP    = 1U,   /* Brief specifies rx timestamp data */
    PSI5_RXTYPE_PAYLOADDATE  = 2U,   /* brief specifies rx payload data */
    PSI5_RXTYPE_ILLEGAL              /* brief specifies rx illegal data */
} Psi5_RxType;

/* Psi5 sync mode enum */
typedef enum
{
    PSI5_TSYNCMODE_INTER = 0U,  /* Brief specifies sync internally generated */
    PSI5_TSYNCMODE_EXTER = 1U   /* Brief specifies sync externally generated */
} Psi5_TsyncMode;

/* Psi5 sync enable mode enum */
typedef enum
{
    PSI5_TSYNCEN_DISABLE = 0U,  /* Brief specifies sync disable */
    PSI5_TSYNCEN_ENABLE  = 1U   /* Brief specifies sync enable */
} Psi5_TsyncEn;

/* Psi5 enhanced protocol enum */
typedef enum
{
    PSI5_ENHPROT_TOOTHGAP = 0U,   /* Brief specifies Tooth Gap frame */
    PSI5_ENHPROT_PWM1_3   = 1U,   /* Brief specifies PWM frame will be enable for frame format 1-3 */
    PSI5_ENHPROT_PWM4     = 2U    /* Brief specifies PWM frame will be enable for frame format 4 */
} Psi5_EnhProt;

/* Psi5 tx startpat enum */
typedef enum
{
    PSI5_STARTPAT_5ZERO = 0U,  /* Brief the start sequence at least 5 consecutive zeros */
    PSI5_STARTPAT_31ONE = 1U   /* Brief the start sequence at least 31 consecutive ones */
} Psi5_Startpat;

/* Psi5 verbose enum */
typedef enum
{
    PSI5_VERBOSE_OFF = 0U,  /* Brief verbose mode is turned off */
    PSI5_VERBOSE_ON  = 1U   /* Brief verbose mode is turned on */
} Psi5_Verbose;

/* Psi5 interrupt request enum */
typedef enum
{
    PSI5_IRQREQUEST_DISABLED = 0U,  /* Brief no interrupt request can be generated for source */
    PSI5_IRQREQUEST_ENABLED  = 1U   /* Brief an interrupt request can be generated for source */
} Psi5_IrqRequest;

/* Psi5 fifo flush enum */
typedef enum
{
    PSI5_FIFOFLUSHTYPE_TX  = (1U << 0U),   /* Brief fifo flush type Tx */
    PSI5_FIFOFLUSHTYPE_RX  = (1U << 1U),   /* Brief fifo flush type Rx */
    PSI5_FIFOFLUSHTYPE_ALL = 0x00000003U   /* Brief fifo flush type Rx and Tx */
/* #Violation: psi5_std_h_REF_2 */
} Psi5_FifoFlushType;

/* Psi5 Interrupt Source enum */
typedef enum
{
    PSI5_IRQSOURCE_CHN0   = (1U << 0U),  /* IRQ enable for channel 0 */
    PSI5_IRQSOURCE_CHN1   = (1U << 1U),  /* IRQ enable for channel 1 */
    PSI5_IRQSOURCE_CHN2   = (1U << 2U),  /* IRQ enable for channel 2 */
    PSI5_IRQSOURCE_CHN3   = (1U << 3U),  /* IRQ enable for channel 3 */
    PSI5_IRQSOURCE_ALL    = 0x0000000FU  /* IRQ enable for all channel */
/* #Violation: psi5_std_h_REF_2 */
} Psi5_IrqSource;

/* Psi5 channel interrupt source enum */
typedef enum
{
    PSI5_CHIRQSOURCE_TXDONE      = ((uint32)1U << 0U),  /* Interrupt for done transmission of command/packet */
    PSI5_CHIRQSOURCE_RXREADY     = ((uint32)1U << 1U), /* Interrupt for ready reception of command/packet */
    PSI5_CHIRQSOURCE_TXCMDERROR  = ((uint32)1U << 2U), /* Interrupt for when bit 0 of TX_FIFO is set inverse */
    PSI5_CHIRQSOURCE_MEIERROR    = ((uint32)1U << 3U), /* Interrupt for messaging Bits with manchester coding error */
    PSI5_CHIRQSOURCE_CRCERROR    = ((uint32)1U << 4U), /* Interrupt for checksum error */
    PSI5_CHIRQSOURCE_TEIERROR    = ((uint32)1U << 5U), /* Interrupt for frame not sent in expected time slot */
    PSI5_CHIRQSOURCE_STARTERROR  = ((uint32)1U << 6U), /* Interrupt for start bit errors */
    PSI5_CHIRQSOURCE_SEIERROR    = ((uint32)1U << 7U), /* Interrupt for sync timing error. */
    PSI5_CHIRQSOURCE_TXFIFOTT    = ((uint32)1U << 8U), /* Interrupt for transmit FIFO threshold reached on read */
    PSI5_CHIRQSOURCE_TXFIFOUR    = ((uint32)1U << 9U), /* Interrupt for transmit FIFO underrun */
    PSI5_CHIRQSOURCE_TXFIFOOR    = ((uint32)1U << 10U),/* Interrupt for transmit FIFO overrun */
    PSI5_CHIRQSOURCE_TXFIFOFULL  = ((uint32)1U << 11U),/* Interrupt for transmit data FIFO full */
    PSI5_CHIRQSOURCE_TXFIFOEMPTY = ((uint32)1U << 12U),/* Interrupt for transmit data FIFO empty */
    PSI5_CHIRQSOURCE_RXFIFOTT    = ((uint32)1U << 13U),/* Interrupt for receive data FIFO threshold reached on write */
    PSI5_CHIRQSOURCE_RXFIFOUR    = ((uint32)1U << 14U),/* Interrupt for receive FIFO underrun */
    PSI5_CHIRQSOURCE_RXFIFOOR    = ((uint32)1U << 15U),/* Interrupt for receive FIFO overrun */
    PSI5_CHIRQSOURCE_RXFIFOFULL  = ((uint32)1U << 16U),/* Interrupt for receive FIFO full */
    PSI5_CHIRQSOURCE_RXFIFOEMPTY = ((uint32)1U << 17U),/* Interrupt for receive FIFO empty */
    PSI5_CHIRQSOURCE_ALL         = 0x0003FFFFU  /* Interrupt for all bits  */
} Psi5_ChIrqSource;

/* Psi5 frame type enum */
typedef enum
{
    PSI5_FRAMETYPE_SHORT        = 0U,  /* Brief specifies short frame type */
    PSI5_FRAMETYPE_LONG1        = 1U,  /* Brief specifies long1 frame type */
    PSI5_FRAMETYPE_LONG2        = 2U,  /* Brief specifies long2 frame type */
    PSI5_FRAMETYPE_XLONG        = 3U,  /* Brief specifies xlong frame type */
    PSI5_FRAMETYPE_XXLONG_SHORT = 4U,  /* Brief specifies xxlong_short frame type */
    PSI5_FRAMETYPE_XXLONG_LONG1 = 5U,  /* Brief specifies xxlong_long1 frame type */
    PSI5_FRAMETYPE_XXLONG_LONG2 = 6U,  /* Brief specifies xxlong_long2 frame type */
    PSI5_FRAMETYPE_XXLONG_XLONG = 7U,  /* Brief specifies xxlong_xlong frame type */
    PSI5_FRAMETYPE_XXLONG_ANY   = 8U   /* Brief specifies xxlong_any frame type */
} Psi5_FrameType;

/* Psi5 sensor address enum */
typedef enum
{
    PSI5_SENSORADDR_SETADDR   = 0U,  /* Brief specifies set sensor address */
    PSI5_SENSORADDR_SENSOR1   = 1U,  /* Brief specifies set sensor1 */
    PSI5_SENSORADDR_SENSOR2   = 2U,  /* Brief specifies set sensor2 */
    PSI5_SENSORADDR_SENSOR3   = 3U,  /* Brief specifies set sensor3 */
    PSI5_SENSORADDR_SENSOR4   = 4U,  /* Brief specifies set sensor4 */
    PSI5_SENSORADDR_SENSOR5   = 5U,  /* Brief specifies set sensor5 */
    PSI5_SENSORADDR_SENSOR6   = 6U,  /* Brief specifies set sensor6 */
    PSI5_SENSORADDR_SENSORALL = 7U   /* Brief specifies set all sensor */
} Psi5_SensorAddr;

/* Psi5 function code enum */
typedef enum
{
    PSI5_FUNCTIONCODE_XLONGREAD    = 0U,  /* Brief specifies xlong frame read */
    PSI5_FUNCTIONCODE_XLONGRWRITE  = 1U,  /* Brief specifies xlong frame write */
    PSI5_FUNCTIONCODE_LONGREAD     = 2U,  /* Brief specifies long frame read */
    PSI5_FUNCTIONCODE_LONGRWRITE   = 3U,  /* Brief specifies long frame write */
    PSI5_FUNCTIONCODE_SPFUNTION1   = 4U,  /* Brief specifies special funtion1 */
    PSI5_FUNCTIONCODE_SPFUNTION2   = 5U,  /* Brief specifies special funtion2 */
    PSI5_FUNCTIONCODE_SPFUNTION3   = 6U,  /* Brief specifies special funtion3 */
    PSI5_FUNCTIONCODE_SPFUNTION4   = 7U,  /* Brief specifies special funtion4 */
    PSI5_FUNCTIONCODE_ZERO         = 0U,  /* Brief specifies set function code is zero */
    PSI5_FUNCTIONCODE_SETADDR1     = 1U,  /* Brief specifies set sensor addr1 */
    PSI5_FUNCTIONCODE_SETADDR2     = 2U,  /* Brief specifies set sensor addr2 */
    PSI5_FUNCTIONCODE_SETADDR3     = 3U,  /* Brief specifies set sensor addr3 */
    PSI5_FUNCTIONCODE_SETADDR4     = 4U,  /* Brief specifies set sensor addr4 */
    PSI5_FUNCTIONCODE_SETADDR5     = 5U,  /* Brief Specifies set sensor addr5 */
    PSI5_FUNCTIONCODE_SETADDR6     = 6U   /* Brief specifies set sensor addr6 */
} Psi5_FunctionCode;

/* The status for interrupt flag enum */
typedef enum
{
    PSI5_INTERRUPFLAG_NOTSETUP = 0U, /* The status for interrupt flag sets up */
    PSI5_INTERRUPFLAG_SETUP    = 1U  /* The status for interrupt flag does not set up */
} Psi5_InterruptFlag;

/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* Brief receive control slot configuration structure */
typedef struct
{
    ureg32 RX_MSG:1;      /* [0:0] Messaging bits, if set, the 2 Messaging bits are configured in slot- RW */
    ureg32 RX_FEC:1;      /* [1:1] Frame Expectation Control, if set, a frame is expected for the PSI5 in slot- RW */
    ureg32 RX_VBS:1;      /* [2:2] Verbose mode, message is expected in slot0 an empty frame is stored in buffer- RW */
    ureg32 RX_PROT:1;     /* [3:3] Using CRC or parity protection for frames from Sensor to ECU for slot- RW */
    ureg32 reserved_4:28; /* [31:4] Internal reserved */
} Psi5_ReceiveControl_Slot_Bits;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/* Data reception slot control union */
typedef union
/* #Violation: psi5_std_h_REF_3 */
{
    uint32 U;                        /* Unsigned access */
    Psi5_ReceiveControl_Slot_Bits B; /* Bit-field access */
} Psi5_ReceiveControl_Slot;
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* Brief Receive control slot width configuration structure */
typedef struct
{
    uint8 chSlot_Width0;       /* Controls the width of slot0 in number of bits from start bits to parity/CRC bits */
    uint8 chSlot_Width1;       /* Controls the width of slot1 in number of bits from start bits to parity/CRC bits */
    uint8 chSlot_Width2;       /* Controls the width of slot2 in number of bits from start bits to parity/CRC bits */
    uint8 chSlot_Width3;       /* Controls the width of slot3 in number of bits from start bits to parity/CRC bits */
    uint8 chSlot_Width4;       /* Controls the width of slot4 in number of bits from start bits to parity/CRC bits */
    uint8 chSlot_Width5;       /* Controls the width of slot5 in number of bits from start bits to parity/CRC bits */
} Psi5_ChSlot_Width;

/* Brief receive control configuration structure */
typedef struct
{
    Psi5_CommunicateMode asynchronousModeSelected;              /* The asynchronous mode of operation */
    Psi5_Verbose avbsEnable;                                    /* Enable the avbs mode for asyncchornous mode */
    uint8 fifoThresholdLevel;                                   /* The fifo threshold level, the maximum value is 96 */
    Psi5_ReceiveControl_Slot receiveControlSlot[PSI5_NUM_SLOTS];/* The receive control slot */
} Psi5_ReceiveControl;

/* Brief data frame structure for ECU data */
/* #Violation: psi5_std_h_REF_6 */
/* #Violation: psi5_std_h_REF_7 */
typedef struct
{
    Psi5_SensorAddr sAddr;         /* Brief specifies data frame structure of sensor address */
    Psi5_FunctionCode functionCode;/* Brief specifies data frame structure of function code */
    uint8 rAddr;                   /* Brief specifies data frame structure of register address */
    uint32 payLoadData;            /* Brief specifies data frame structure of payload data */
    Psi5_FrameType frameType;      /* Brief specifies data frame structure of frame type */
} Psi5_TransmitFrame;
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/* #Violation: psi5_std_h_REF_4 */
#define PSI5_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: psi5_std_h_REF_5 */
#include "Psi5_MemMap.h"

/**********************************************************************************************************************
 * Function:     Psi5_Std_EnableChStart_Ctrl
 * Description:  Enable automatic generation of the start sequence.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pPsi5: pointer to the psi5 module
 *               channelId: channel number of operation
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/10    01849     Created
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Psi5_Std_EnableChStart_Ctrl(PSI5_MODULE *pPsi5, Psi5_ChannelId channelId);

/**********************************************************************************************************************
 * Function:     Psi5_Std_SetTransmitChENH_Prot
 * Description:  Enhances protocol selection.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pPsi5: pointer to the psi5 module
 *               channelId: channel number of operation
 *               prot: selection of different modulation waveforms
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/10    01849     Created
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Psi5_Std_SetTransmitChENH_Prot(PSI5_MODULE *pPsi5, Psi5_ChannelId channelId, Psi5_EnhProt prot);

/**********************************************************************************************************************
 * Function:     Psi5_Std_SetTransmitChToothgap_StarPat
 * Description:  Controls the start pattern when doing ECU to Sensor when TX0_TOOTH_GAP is selected.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pPsi5: pointer to the psi5 module
 *               channelId: channel number of operation
 *               pat: selection of different start pattern
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/10    01849     Created
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Psi5_Std_SetTransmitChToothgap_StarPat(PSI5_MODULE *pPsi5, Psi5_ChannelId channelId,
                                                              Psi5_Startpat pat);

/**********************************************************************************************************************
 * Function:     Psi5_Std_EnableChTsync
 * Description:  This field enables sending sync generation.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pPsi5: pointer to the psi5 module
 *               channelId: channel number of operation
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/10    01849     Created
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Psi5_Std_EnableChTsync(PSI5_MODULE *pPsi5, Psi5_ChannelId channelId);

/**********************************************************************************************************************
 * Function:     Psi5_Std_SetTransmitChTsycnPeriod
 * Description:  Controls the Tsync width in internal clock (Prescaler output).
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pPsi5: pointer to the psi5 module
 *               channelId: channel number of operation
 *               period: the Tsync width have how many clock are there, the value ranges from 0 to 255
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/10    01849     Created
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Psi5_Std_SetTransmitChTsycnPeriod(PSI5_MODULE *pPsi5, Psi5_ChannelId channelId, uint8 period);

/**********************************************************************************************************************
 * Function:     Psi5_Std_SetTransmitChToothgap_SyncGap
 * Description:  Controls gap between two Sync pulse for ECU to Sensor communication when using Tooth Gap.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pPsi5: pointer to the psi5 module
 *               channelId: channel number of operation
 *               gap: the gap width have how many clock are there, the value ranges from 0 to 255
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/10    01849     Created
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Psi5_Std_SetTransmitChToothgap_SyncGap(PSI5_MODULE *pPsi5, Psi5_ChannelId channelId, uint8 gap);

/**********************************************************************************************************************
 * Function:     Psi5_Std_SetTransmitChPWM_Add
 * Description:  controls PWM width, add to extended sync pulse width in PWM1 ECU to sensor communication.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pPsi5: pointer to the psi5 module
 *               channelId: channel number of operation
 *               add: the add width have how many clock are there, the value ranges from 0 to 255
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/10    01849     Created
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Psi5_Std_SetTransmitChPWM_Add(PSI5_MODULE *pPsi5, Psi5_ChannelId channelId, uint8 add);

/**********************************************************************************************************************
 * Function:     Psi5_Std_SetTransmitChSync_SlotGap
 * Description:  Controls the gap between two slots in prescaler output clock.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pPsi5: pointer to the psi5 module
 *               channelId: channel number of operation
 *               slotgap: the gap between two slots width have how many clock are there, the value ranges from 0 to 255
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/10    01849     Created
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Psi5_Std_SetTransmitChSync_SlotGap(PSI5_MODULE *pPsi5, Psi5_ChannelId channelId, uint8 slotgap);

/**********************************************************************************************************************
 * Function:     Psi5_Std_SetTransmitChSlot_Post
 * Description:  Controls the gap between last slot and sync pulse in prescaler output clock.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pPsi5: pointer to the psi5 module
 *               channelId: channel number of operation
 *               post: the gap between last slot and sync pulse width have how many clock are there, the value ranges
 *               from 0 to 255
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/10    01849     Created
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Psi5_Std_SetTransmitChSlot_Post(PSI5_MODULE *pPsi5, Psi5_ChannelId channelId, uint8 post);

/**********************************************************************************************************************
 * Function:     Psi5_Std_SetTransmitChSlot_Gap
 * Description:  Controls the gap between sync pulse and first slot in prescaler output clock.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pPsi5: pointer to the psi5 module
 *               channelId: channel number of operation
 *               gap: the gap between sync pulse and first slot width have how many clock are there, the value
 *               ranges from 0 to 255
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/10    01849     Created
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Psi5_Std_SetTransmitChSlot_Gap(PSI5_MODULE *pPsi5, Psi5_ChannelId channelId, uint8 gap);

/**********************************************************************************************************************
 * Function:     Psi5_Std_GetTransmitDone
 * Description:  Retrieve the result of the data transmission.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pPsi5: pointer to the psi5 module
 *               channelId: channel number of operation
 * Inout:        None
 * Output:       None
 * Return:       boolean: Result of whether the sending of data was completed
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/10    01849     Created
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Psi5_Std_GetTransmitDone(const PSI5_MODULE *pPsi5, Psi5_ChannelId channelId);

/**********************************************************************************************************************
 * Function:     Psi5_Std_GetReceiveReady
 * Description:  Retrieve the result of the data reception.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pPsi5: pointer to the psi5 module
 *               channelid: channel number of operation
 * Inout:        None
 * Output:       None
 * Return:       boolean: Result of whether the reception of data is complete
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/10    01849     Created
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Psi5_Std_GetReceiveReady(const PSI5_MODULE *pPsi5, Psi5_ChannelId channelId);

/**********************************************************************************************************************
 * Function:     Psi5_Std_ReadReceiveChFifoData
 * Description:  Inline Function Prototypes for data receive.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pPsi5: pointer to the psi5 module
 *               channelId: channel number of operation
 * Inout:        None
 * Output:       None
 * Return:       PSI5_CH_RX_FIFO: The data received in RXfifo
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/10    01849     Created
 *********************************************************************************************************************/
LOCAL_FORCEINLINE PSI5_CH_RX_FIFO Psi5_Std_ReadReceiveChFifoData(const PSI5_MODULE *pPsi5, Psi5_ChannelId channelId);

/**********************************************************************************************************************
 * Function:     Psi5_Std_GlitchFilter
 * Description:  Set glitch filter parameters.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pPsi5: pointer to the psi5 module
 *               glitchFilter: Glitch filter width, the value ranges from 0 to 255, recommended setting is 4.
 *                             If set to 0, the glitch filter is turned off
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/10    01849     Created
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Psi5_Std_GlitchFilter(PSI5_MODULE *pPsi5, uint8 glitchFilter);

/**********************************************************************************************************************
 * Function:     Psi5_Std_SetDma
 * Description:  Set DMA to on or off
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pPsi5: pointer to the psi5 module
 *               dmaEn: DMA on or off
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date         Author   Modified
 *  2024/11/10   01849    create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Psi5_Std_SetDma(PSI5_MODULE *pPsi5, boolean dmaEn);

/**********************************************************************************************************************
 * Function:     Psi5_Std_TimestampPrescaler
 * Description:  Controls the prescale for timestamp counter, this divides output clock of prescale
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pPsi5: pointer to the psi5 module
 *               timestampPrescaler: the prescale for timestamp counter, the value ranges from 1 to 65535
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date         Author   Modified
 *  2024/11/10   01849    create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Psi5_Std_TimestampPrescaler(PSI5_MODULE *pPsi5, uint16 timestampPrescaler);

/**********************************************************************************************************************
 * Function:     Psi5_Std_ChannelPrescaler
 * Description:  Controls the prescale for Channel counter, this divides output clock of prescale
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pPsi5: pointer to the psi5 module
 *               channelId: channel number of operation
 *               channelPrescaler: the prescale for Channel counter, the value ranges from 1 to 65535
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date         Author   Modified
 *  2024/11/10   01849    create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Psi5_Std_ChannelPrescaler(PSI5_MODULE *pPsi5,Psi5_ChannelId channelId,uint16 channelPrescaler);


/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Psi5_Std_EnableChStart_Ctrl(PSI5_MODULE *pPsi5, Psi5_ChannelId channelId)
{
    pPsi5->CH[channelId].CH_TX_CONTROL.B.TX_START_CTRL = 1U;
}

LOCAL_FORCEINLINE void Psi5_Std_SetTransmitChENH_Prot(PSI5_MODULE *pPsi5, Psi5_ChannelId channelId, Psi5_EnhProt prot)
{
    pPsi5->CH[channelId].CH_TX_CONTROL.B.TX_ENH_PROT = (uint32)prot;
}

LOCAL_FORCEINLINE void Psi5_Std_SetTransmitChToothgap_StarPat(PSI5_MODULE *pPsi5, Psi5_ChannelId channelId,
                                                              Psi5_Startpat pat)
{
    pPsi5->CH[channelId].CH_TX_CONTROL.B.TX_START_PAT = (uint32)pat;
}

LOCAL_FORCEINLINE void Psi5_Std_EnableChTsync(PSI5_MODULE *pPsi5, Psi5_ChannelId channelId)
{
    pPsi5->CH[channelId].CH_TX_CONTROL.B.TX_TSYNC_EN = 1U;
}

LOCAL_FORCEINLINE void Psi5_Std_SetTransmitChTsycnPeriod(PSI5_MODULE *pPsi5, Psi5_ChannelId channelId, uint8 period)
{
    pPsi5->CH[channelId].CH_TX_CONTROL.B.TX_TSYNC_PERIOD = (uint32)period;
}

LOCAL_FORCEINLINE void Psi5_Std_SetTransmitChToothgap_SyncGap(PSI5_MODULE *pPsi5, Psi5_ChannelId channelId, uint8 gap)
{
    pPsi5->CH[channelId].CH_TX_CONTROL.B.TX_ENC_GAP = (uint32)gap;
}

LOCAL_FORCEINLINE void Psi5_Std_SetTransmitChPWM_Add(PSI5_MODULE *pPsi5, Psi5_ChannelId channelId, uint8 add)
{
    pPsi5->CH[channelId].CH_TX_CONTROL.B.TX_PWM_ADD = (uint32)add;
}

LOCAL_FORCEINLINE void Psi5_Std_SetTransmitChSync_SlotGap(PSI5_MODULE *pPsi5, Psi5_ChannelId channelId, uint8 slotgap)
{
    pPsi5->CH[channelId].CH_TX_SLOT_CTRL.B.TX_SYNC_SLOT_GAP = (uint32)slotgap;
}

LOCAL_FORCEINLINE void Psi5_Std_SetTransmitChSlot_Post(PSI5_MODULE *pPsi5, Psi5_ChannelId channelId, uint8 post)
{
    pPsi5->CH[channelId].CH_TX_SLOT_CTRL.B.TX_SLOT_POST = (uint32)post;
}

LOCAL_FORCEINLINE void Psi5_Std_SetTransmitChSlot_Gap(PSI5_MODULE *pPsi5, Psi5_ChannelId channelId, uint8 gap)
{
    pPsi5->CH[channelId].CH_TX_SLOT_CTRL.B.TX_SLOT_GAP = (uint32)gap;
}

LOCAL_FORCEINLINE boolean Psi5_Std_GetTransmitDone(const PSI5_MODULE *pPsi5, Psi5_ChannelId channelId)
{
    return (boolean) pPsi5->CH[channelId].CH_IRQ_STATUS.B.IRQ_CH_TX_DONE;
}

LOCAL_FORCEINLINE boolean Psi5_Std_GetReceiveReady(const PSI5_MODULE *pPsi5, Psi5_ChannelId channelId)
{
    return (boolean) pPsi5->CH[channelId].CH_IRQ_STATUS.B.IRQ_CH_RX_READY;
}

LOCAL_FORCEINLINE PSI5_CH_RX_FIFO Psi5_Std_ReadReceiveChFifoData(const PSI5_MODULE *pPsi5, Psi5_ChannelId channelId)
{
    return pPsi5->CH[channelId].CH_RX_FIFO;
}

LOCAL_FORCEINLINE void Psi5_Std_GlitchFilter(PSI5_MODULE *pPsi5, uint8 glitchFilter)
{
    pPsi5->GLITCH_FILTER.U = (uint32)glitchFilter;
}

LOCAL_FORCEINLINE void Psi5_Std_SetDma(PSI5_MODULE *pPsi5, boolean dmaEn)
{
    /* Enable/Disable DMA TX */
    pPsi5->CONTROL.B.EXT_DMA_ENABLE = (uint32)dmaEn;
}

LOCAL_FORCEINLINE void Psi5_Std_TimestampPrescaler(PSI5_MODULE *pPsi5, uint16 timestampPrescaler)
{
    /* Timestamp psrescaler */
    pPsi5->TS_PRESCALER.B.TS_PRESCALER = (uint32)timestampPrescaler;
}

LOCAL_FORCEINLINE void Psi5_Std_ChannelPrescaler(PSI5_MODULE *pPsi5, Psi5_ChannelId channelId, uint16 channelPrescaler)
{
    /* Channel Prescaler */
    pPsi5->CH[channelId].CH_PRESCALER.B.CH_PRESCALER = (uint32)channelPrescaler;
}



/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:     Psi5_Std_SetReceiveChSlot_Width
 * Description:  Set the time slot for each slot in the interpretation channel.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pPsi5: pointer to the psi5 module
 *               channelId: channel number of operation
 *               width: pointer to time slot length of the slot0-5
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/10    01849     Created
 *********************************************************************************************************************/
extern void Psi5_Std_SetReceiveChSlot_Width(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId,
                                            const Psi5_ChSlot_Width *const width);


/**********************************************************************************************************************
 * Function:     Psi5_Std_SetChSlot_Prot
 * Description:  Set the protect mode for each slot in the interpretation channel.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pPsi5: pointer to the psi5 module
 *               channelId: channel number of operation
 *               receiveControl: pointer to the psi5 receive control parameter.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/10    01849     Created
 *********************************************************************************************************************/
extern void Psi5_Std_SetChSlot_Prot(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId,
                                    const Psi5_ReceiveControl *const receiveControl);

/**********************************************************************************************************************
 * Function:     Psi5_Std_ProtectSync
 * Description:  Set the protection mode of each slot in the channel to match the command data.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pPsi5: pointer to the psi5 module
 *               channelId: channel number of operation
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/10    01849     Created
 *********************************************************************************************************************/
extern void Psi5_Std_ProtectSync(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId);

/**********************************************************************************************************************
 * Function:     Psi5_Std_SendChannelDataFrame4
 * Description:  Send the channel data for frame4
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pPsi5: pointer to the psi5 module
 *               channelId: channel number of operation
 *               pFrame: pointer to the psi5 module transmit frame
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/07    01849     Create
 *********************************************************************************************************************/
extern void Psi5_Std_SendChannelDataFrame4(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId,
                                           const Psi5_TransmitFrame *const pFrame);

/**********************************************************************************************************************
 * Function:     Psi5_Std_SendChannelDataFrame13
 * Description:  Send the channel data for frame1->3
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pPsi5: pointer to the psi5 module
 *               channelId: channel number of operation
 *               pFrame: pointer to the psi5 module transmit frame
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/07    01849     Create
 *********************************************************************************************************************/
extern void Psi5_Std_SendChannelDataFrame13(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId,
                                            const Psi5_TransmitFrame *const pFrame);


/* #Violation: psi5_std_h_REF_4 */
#define PSI5_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: psi5_std_h_REF_5 */
#include "Psi5_MemMap.h"

#endif /* PSI5_STD_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
