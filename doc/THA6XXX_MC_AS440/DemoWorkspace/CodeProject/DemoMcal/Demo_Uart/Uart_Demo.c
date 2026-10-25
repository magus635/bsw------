/****************************************************************************************************
 *
****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Uart_Demo.c
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : ASI
 *
 *   brief                 : This file contains Demo application for ASI Driver
 *
 *   Autosar Version       : 4.4.0
 *
 *   Build Version         : Cortex-R52+/THA6xxx
 *
 *   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
 *
****************************************************************************************************/

/****************************************************************************************************
**                          WARNING!!!                                                             **
* All APIs covered in Uart_Demo.c and Uart_Demo.h are only suitable for Demo testing and           **
* provide no functionality or performance guarantees for OTHER PROJECTS.                           **
****************************************************************************************************/


/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include <stdarg.h>
#include "Uart_Demo.h"
#include "Mcall.h"
#include "Demo_Common.h"
#include "Platform_Types.h"
#include "common_hal.h"
#include "Platform_Types.h"
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
/* Mask: Align right, use 0 placeholder on the left, bit[1:0] (0:1) */
#define MASK_RIGHTALIGNED_FILLZREO          0x01U
/* Mask: Align left, use space placeholder on the right, bit[1:0] (1:0) */
#define MASK_LEFTALIGNED_FILLSPACE          0x02U
/* Mask: Align right, use space placeholder on the left, bit[1:0] (1:1) */
#define MASK_RIGHTALIGNED_FILLSPACE         0x03U
/* Mask: Enable long integer, bit[3:2] (0)*/
#define MASK_NOLONGTYPEUMM                 (0x00U << 2U)
/* Mask: Enable long integer, bit[3:2] (1)*/
#define MASK_LONGTYPE_POSITIVENUM          (0x01U << 2U)
/* Mask: Enable long integer negative type, bit[3:2] (2) */
#define MASK_LONGTYPE_NEGATIVENUM           (0x02U << 2U)
/* Mask: Enable floating point fraction bit width limitation, bit[4] (1) */
#define MASK_ENABLEFLOAT_FRACTIONWIDTH      (0x01U << 4U)
/* Mask: Default bit width limit for floating point fraction part */
#define MASK_FLOATDEFAULT_FRACTIONWIDTH     (0x06U)
/* Mask: Data output base type, bit[6:4] (1) */
#define MASK_OUTPUTCHAR                     (0x00U)
#define MASK_OUTPUTBINARY                   (0x02U)
#define MASK_OUTPUTOCTAL                    (0x08U)
#define MASK_OUTPUTDECIMAL                  (0x0AU)
#define MASK_OUTPUTHEX                      (0x10U)
/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#define UART_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Uart_MemMap.h"

#if (STD_ON == DEMO_PRINTQUEUEMODE)
typedef struct __attribute__((aligned(64)))
{
    uint32 lockStatus;  /* Lock of GIPC. 0: Unlocked; 1: Locked */
    uint32 reserved[15]; /* Reserved to ensure that the size of structure conforms to marked address size(64 Bytes). */
} Uart_Lock;
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)

/* Printf spin lock print variable */
static Uart_Lock Printf_LockStatus;
#endif
#endif /* (STD_ON == DEMO_PRINTQUEUEMODE) */

#define UART_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Uart_MemMap.h"
/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/
#if (STD_ON == DEMO_PRINTQUEUEMODE)

#if (STD_ON == DEMO_PRINTINTERRUPT)
#include "Gpt.h"
#include "Gpt_Cfg.h"
#endif /* STD_ON == DEMO_PRINTINTERRUPT */

#define UART_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Uart_MemMap.h"
/* Define Debug printing temporary Queue variable */
static volatile Mcal_SeqQueueType Print_Queue;
/* Define Debug printing Queue initialization status variable */
/* Actually  Print_QueueInitStatus = FALSE */
static boolean Print_QueueInitStatus;
static uint8 Print_ElemBuffer[PRINTF_QUEUE_BUFFER_LEN];

#define UART_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Uart_MemMap.h"

#define UART_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#include "Uart_MemMap.h"
/* Define Core0 data sending cache buffer */
static char         TxDataCore0[PRINTF_EACH_BUFFER_LEN];
static uint8        TxSizeCore0;
#define UART_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#include "Uart_MemMap.h"

#define UART_START_SEC_CONST_ASIL_D_CORE0_UNSPECIFIED
#include "Uart_MemMap.h"
static const PrintfbufferType PrintfbufferCore0 =
{
    &TxDataCore0[0],
    &TxSizeCore0,
    FALSE
};
#define UART_STOP_SEC_CONST_ASIL_D_CORE0_UNSPECIFIED
#include "Uart_MemMap.h"

#define UART_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
#include "Uart_MemMap.h"
/* Define Core0 data sending cache buffer */
static char         TxDataCore1[PRINTF_EACH_BUFFER_LEN];
static uint8        TxSizeCore1;
#define UART_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
#include "Uart_MemMap.h"

#define UART_START_SEC_CONST_ASIL_D_CORE1_UNSPECIFIED
#include "Uart_MemMap.h"
static const PrintfbufferType PrintfbufferCore1 =
{
    &TxDataCore1[0],
    &TxSizeCore1,
    FALSE
};
#define UART_STOP_SEC_CONST_ASIL_D_CORE1_UNSPECIFIED
#include "Uart_MemMap.h"

#define UART_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "Uart_MemMap.h"

/* Pointer to the SPI HW unit data structure set for each core */
static CONSTP2CONST(PrintfbufferType, UART_VAR, UART_APPL_CONST)
                                        Printfbuffer[MCAL_NUMBER_OF_CORES] =
{
#if (MCAL_NUMBER_OF_CORES > 0U)
    &PrintfbufferCore0
#else
    NULL_PTR
#endif /* (SPI_MAX_HWUNIT_CORE0 > 0U) */

#if (MCAL_NUMBER_OF_CORES > 1U)
    ,&PrintfbufferCore1
#else
    ,NULL_PTR
#endif /* (MCAL_NUMBER_OF_CORES > 1U) */
};
#define UART_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "Uart_MemMap.h"
#endif /* (STD_ON == DEMO_PRINTQUEUEMODE) */
/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
#define UART_START_SEC_CODE_ASIL_D_GLOBAL
#include "Uart_MemMap.h"
/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
/*********************************Declare Debug printing related functions**********************************/
#if (STD_ON == DEMO_PRINTQUEUEMODE)
static Std_ReturnType Printf_GetLock(void);
static void Printf_ReleaseLock(void);
#endif /* (STD_ON == DEMO_PRINTQUEUEMODE) */

static void PrintfCharHandle(PrintfbufferType Buffer, uint8 data);
static void PrintfStringHandle(PrintfbufferType Buffer, const uint8* StringPtr);
static void PrintfFloatHandle(uint64 DataInt, uint8* str, uint8* Length);
static uint8 GetStringLenth(uint64 Data);
static uint8 PrintfByteHandle(boolean DirectPrintf, char* str, const uint8* fmt, va_list arp);
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

#if (STD_ON == DEMO_PRINTQUEUEMODE)
/****************************************************************************************************
*   Function Name           : Printf_GetLock
*
*   Service ID              : NONE.
*
*   Description             : Printf acquires the spin lock.
*                             this is just design for demo and take no responsibility for any other
*                             formal projects and outer callers
*
*   Parameters in           : NONE.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : E_OK: Printf successfully acquires the spin lock.
*                             E_NOT_OK: Printf failed to acquire spin lock.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static Std_ReturnType Printf_GetLock(void)
{
    Std_ReturnType Result;
    #if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)


#ifdef __TASKING__
    ASM_VOLATILE(
        "   mov r1, #0                 \n"     /* Initialize count register r1 to 0 */
        "   1:                         \n"     /* Start Loop */
        "   mov r2, #1                 \n"     /* r2 = 1 (Locked) */
        "   ldr r3, [%1]               \n"     /* r3 = *Printf_LockStatus (Get lock status) */
        "   cmp r3, r2                 \n"     /* Compare lock status with 1 (locked) */
        "   beq 2n                     \n"     /* If locked (r3 == 1), jump to failure handler */
            
        "   ldrex r4, [%1]             \n"     /* Try to read the lock atomically */
        "   strex r3, r2, [%1]         \n"     /* Try to write the lock atomically (1) */
        "   cmp r3, #0                 \n"     /* Check if the lock was successfully acquired */
        "   beq 3n                     \n"     /* If lock acquired successfully (r3 == 0), jump to success handler */
            
        /* Lock acquisition failed, check timeout */
        "   add r1, r1, #1             \n"     /* Increment timeout count in r1 */
        "   cmp r1, #0x1000            \n"     /* Compare count with max timeout value 0xFFFFFFFFU */
        "   beq 1p                     \n"     /* If timeout not reached, repeat the loop */
        "   bne 2n                     \n"     /* If timeout reached, jump to failure handler */
            
        "   2:                         \n"     /* Lock failure handler */
        "   mov %0, #1                 \n"     /* Set Result to 1 (failure) */
        "   b 5n                       \n"     /* Jump to end */
            
        "   3:                         \n"     /* Lock success handler */
        "   mov %0, #0                 \n"     /* Set Result to 0 (success) */
            
        "   5:                         \n"     /* End loop */
        :   "=&r"(Result)                     /* Output: Result */
        :   "r"(&Printf_LockStatus)           /* Input: Address of Printf_LockStatus */
        :   "cc", "memory", "r1","r2", "r3", "r4"  /* Clobbered registers and status flags */
    );
#else
    ASM_VOLATILE(
        "mov r1, #0                 \n"     /* Initialize count register r1 to 0 */
        "1:                         \n"     /* Start Loop */
        "mov r2, #1                 \n"     /* r2 = 1 (Locked) */
        "ldr r3, [%1]               \n"     /* r3 = *Printf_LockStatus (Get lock status) */
        "cmp r3, r2                 \n"     /* Compare lock status with 1 (locked) */
        "beq 2f                     \n"     /* If locked (r3 == 1), jump to failure handler */

        "ldrex r4, [%1]             \n"     /* Try to read the lock atomically */
        "strex r3, r2, [%1]         \n"     /* Try to write the lock atomically (1) */
        "cmp r3, #0                 \n"     /* Check if the lock was successfully acquired */
        "beq 3f                     \n"     /* If lock acquired successfully (r3 == 0), jump to success handler */

        /* Lock acquisition failed, check timeout */
        "add r1, r1, #1             \n"     /* Increment timeout count in r1 */
        "cmp r1, #0xFFFFFFFFU       \n"     /* Compare count with max timeout value */
        "blt 1b                     \n"     /* If timeout not reached, repeat the loop */
        "b 2f                       \n"     /* If timeout reached, jump to failure handler */

        "2:                         \n"     /* Lock failure handler */
        "mov %0, #1                 \n"     /* Set Result to 1 (failure) */
        "b 5f                       \n"     /* Jump to end */

        "3:                         \n"     /* Lock success handler */
        "mov %0, #0                 \n"     /* Set Result to 0 (success) */

        "5:                         \n"     /* End loop */
        : "=&r"(Result)                     /* Output: Result */
        : "r"(&Printf_LockStatus)           /* Input: Address of Printf_LockStatus */
        : "cc", "memory", "r1","r2", "r3", "r4"  /* Clobbered registers and status flags */
    );
    #endif
#else
Result = FALSE;
#endif
    return Result;
}
#endif /* (STD_ON == DEMO_PRINTQUEUEMODE) */


#if (STD_ON == DEMO_PRINTQUEUEMODE)
/****************************************************************************************************
*   Function Name           : Printf_ReleaseLock
*
*   Service ID              : NONE.
*
*   Description             : Printf releases the spin lock.
*                             this is just design for demo and take no responsibility for any other
*                             formal projects and outer callers
*
*   Parameters in           : NONE.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static void Printf_ReleaseLock(void)
{
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)

    /* Release lock */
    Printf_LockStatus.lockStatus = 0U;
#endif
}
#endif /* (STD_ON == DEMO_PRINTQUEUEMODE) */
/****************************************************************************************************
*   Function Name           : PrintfCharHandle
*
*   Service ID              : NONE.
*
*   Description             : Push a characters into sent queue
*                             this is just design for demo and take no responsibility for any other
*                             formal projects and outer callers
*
*   Parameters in           : c: Character to sent
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static void PrintfCharHandle(PrintfbufferType Buffer, uint8 data)
{
    if(NULL_PTR != Buffer.BufferPtr)
    {
        Buffer.BufferPtr[*Buffer.SizePtr] = (char)data;
        *Buffer.SizePtr += 1U;
    }
    else
    {
        if(TRUE == Buffer.DirectPrintFlag)
        {
            while((boolean)Uart_Write(DebugChannel, &data, 0x01U));
        }
    }
}
/****************************************************************************************************
*   Function Name           : PrintfStringHandle
*
*   Service ID              : NONE.
*
*   Description             : Put a NULL_PTR-terminated string to the default device.
*                             this is just design for demo and take no responsibility for any other
*                             formal projects and outer callers
*
*   Parameters in           : str: Pointer to the string
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static void PrintfStringHandle(PrintfbufferType Buffer, const uint8* StringPtr)
{
    /* Loop until the end of the string, the flag is '\0' */
    while (*StringPtr != 0U)
    {
        PrintfCharHandle(Buffer, *StringPtr++);
    }
}
/****************************************************************************************************
*   Function Name           : GetStringLenth
*
*   Service ID              : NONE.
*
*   Description             : Get the length of the string corresponding to the given data.
*                             this is just design for demo and take no responsibility for any other
*                             formal projects and outer callers
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static uint8 GetStringLenth(uint64 Data)
{
    uint8 Curlen = 0U;
    /* Get the data width in decimal form of the data */
    while (Data != 0U)
    {
        Curlen++;
        Data /= 10U;
    }

    return Curlen;
}
/****************************************************************************************************
*   Function Name           : PrintfFloatHandle
*
*   Service ID              : NONE.
*
*   Description             : Push a Single-precision floating-point data into sent queue.
*                             this is just design for demo and take no responsibility for any other
*                             formal projects and outer callers
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static void PrintfFloatHandle(uint64 DataInt, uint8* str, uint8* Length)
{
    uint8   Curlen;
    uint8   Count;

    Curlen = GetStringLenth(DataInt);
    Count = Curlen;
    /* The floating point value is converted into characters and stored in sequence
       at the address offset *Length pointed to by str. */
    while (DataInt != 0U)
    {
        Count--;
        str[*Length + Count] = (uint8)('0' + DataInt % 10U);
        DataInt /= 10U;
    }
    *Length += Curlen;
}
/****************************************************************************************************
*   Function Name           : PrintfCheckFloat64
*
*   Service ID              : NONE.
*
*   Description             : Check if a given 64-bit floating point number is NaN (Not a Number)
*                             or Inf (Infinity). This function is designed for demonstration purposes
*                             and should not be used in formal projects or by external callers.
*
*   Parameters in           : value - The 64-bit floating point number to be checked.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : A pointer to a constant character string representing "NaN" if the value
*                             is NaN, "Inf" if the value is Inf, or NULL_PTR if the value is neither.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static const char * PrintfCheckFloat64(float64 value)
{
    /* Union to hold the float64 value and its bit pattern as uint64 */
    F64Union fu64;
    boolean isNan = FALSE;
    boolean isInf = FALSE;

    /* Assign the floating point value to the union */
    fu64.f64 = value;

    /* Check if the exponent is all 1s and the mantissa is not all 0s (NaN condition) */
    isNan = (boolean)((fu64.u64 & 0x7FF0000000000000ULL) == 0x7FF0000000000000ULL &&
                      (fu64.u64 & 0x000FFFFFFFFFFFFFULL) != 0);

    /* Check if the exponent is all 1s and the mantissa is all 0s  (Inf condition) */
    isInf = (boolean)((fu64.u64 & 0x7FF0000000000000ULL) == 0x7FF0000000000000ULL &&
                      (fu64.u64 & 0x000FFFFFFFFFFFFFULL) == 0);

    if (isNan)
    {
        return "NaN";
    }
    if(isInf) {
        return "Inf";
    }
    else
    {
        return NULL_PTR;
    }
}

/****************************************************************************************************
*   Function Name           : PrintfByteHandle
*
*   Service ID              : NONE.
*
*   Description             : Formatted string output:
*                             PrintfByteHandle: DEBUG_PRINTF("\n");                             newline character
*                             PrintfByteHandle: DEBUG_PRINTF("%c\n", 'a');                      "a"
*                             PrintfByteHandle: DEBUG_PRINTF("%s\n", "abc");                    "abc"
*                             PrintfByteHandle: DEBUG_PRINTF("%4s\n", "abc");                   " abc"
*                             PrintfByteHandle: DEBUG_PRINTF("%04s\n", "abc");                  "0abc"
*                             PrintfByteHandle: DEBUG_PRINTF("%-4s\n", "abc");                  "abc "
*                             PrintfByteHandle: DEBUG_PRINTF("%b\n", 0x550);                    "10101010000"
*                             PrintfByteHandle: DEBUG_PRINTF("%16b\n", 0x550);                  "     10101010000"
*                             PrintfByteHandle: DEBUG_PRINTF("%016b\n", 0x550);                 "0000010101010000"
*                             PrintfByteHandle: DEBUG_PRINTF("%-16b\n", 0x550);                 "10101010000     "
*                             PrintfByteHandle: DEBUG_PRINTF("%d\n", 1234);                     "1234"
*                             PrintfByteHandle: DEBUG_PRINTF("%6d\n", 1234);                    "  1234"
*                             PrintfByteHandle: DEBUG_PRINTF("%06d\n", 1234);                   "001234"
*                             PrintfByteHandle: DEBUG_PRINTF("%-6d\n", 1234);                   "1234  "
*                             PrintfByteHandle: DEBUG_PRINTF("%6d,%3d%%\n", -200, 5);           "  -200,  5%"
*                             PrintfByteHandle: DEBUG_PRINTF("%ld\n", 0xFFF2);                  "65522"
*                             PrintfByteHandle: DEBUG_PRINTF("%ld\n", -0xFFF2);                 "-65522"
*                             PrintfByteHandle: DEBUG_PRINTF("%lld\n", 0xFFFFFFFF2);            "68719476722"
*                             PrintfByteHandle: DEBUG_PRINTF("%lld\n", -0xFFFFFFFF2);           "-68719476722"
*                             PrintfByteHandle: DEBUG_PRINTF("%u\n", 100);                      "100"
*                             PrintfByteHandle: DEBUG_PRINTF("%6u\n", 100);                     "   100"
*                             PrintfByteHandle: DEBUG_PRINTF("%06u\n", 100);                    "000100"
*                             PrintfByteHandle: DEBUG_PRINTF("%-6u\n", 100);                    "100   "
*                             PrintfByteHandle: DEBUG_PRINTF("%x\n", 0xA3);                     "a3"
*                             PrintfByteHandle: DEBUG_PRINTF("%4x\n", 0xA3);                    "  a3"
*                             PrintfByteHandle: DEBUG_PRINTF("%04x\n", 0xA3);                   "00a3"
*                             PrintfByteHandle: DEBUG_PRINTF("%-4x\n", 0xA3);                   "a3  "
*                             PrintfByteHandle: DEBUG_PRINTF("%-4X\n", 0xA3);                   "A3  "
*                             PrintfByteHandle: DEBUG_PRINTF("%LX\n", 0x9abcdef0);              "9ABCDEF0"
*                             PrintfByteHandle: DEBUG_PRINTF("%LLX\n", 0x9abcdef012345678);     "9ABCDEF012345678"
*                             PrintfByteHandle: DEBUG_PRINTF("%f\n", 10.12345);                 "10.123450"
*                             PrintfByteHandle: DEBUG_PRINTF("%8.3f\n", 10.12345);              "  10.123"
*                             PrintfByteHandle: DEBUG_PRINTF("%08.3f\n", 10.12345);             "0010.123"
*                             PrintfByteHandle: DEBUG_PRINTF("%8.3f\n", -10.12345);             " -10.123"
*                             PrintfByteHandle: DEBUG_PRINTF("%f\n", -0.027314067);             "-0.027314"
*                             PrintfByteHandle: DEBUG_PRINTF("%0.9f\n", -0.027314067);          "-0.027314068"
*                             PrintfByteHandle: DEBUG_PRINTF("%lf\n", 10.0);                    "10.000000"
*                             PrintfByteHandle: DEBUG_PRINTF("%f\n", 10.0/0.0);                 "inf"
*                             PrintfByteHandle: DEBUG_PRINTF("%f\n", 0.0/0.0);                  "nan"
*                             this is just design for demo and take no responsibility for any other
*                             formal projects and outer callers
*
*   Parameters in           : flag: Single byte immediate output flag
*                             str:  Temporary data storage buffer passed in by the user
*                             fmt:  Pointer to the format string
*                             arp:  Pointer to arguments
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static uint8 PrintfByteHandle(boolean DirectPrintf, char* str, const uint8* fmt, va_list arp)
{
    uint8               TempChar, CapChar, DataBuffer[16], DecimalMask, FormatFlag;
    uint8               IntegerBitWidth, FractionBitWidth, ListCount, Count, StringLength, FloatLen;
    uint8               *Va_List8;
    uint32              FloatIntPart;
    float32             TempFloat32;
    uint64              Va_List64;
    float64             TempFloat64;
    PrintfbufferType    TempBufferPtr;
    const char *        TempFloatStr;
    uint8               PrintFloatStrCnt;
#if (STD_ON == DEMO_PRINTQUEUEMODE)
    Mcal_SeqQueueType * PrintQueuePtr;
    Mcal_CoreType CoreId;

    CoreId = Mcal_GetCoreId();
#endif /* (STD_ON == DEMO_PRINTQUEUEMODE) */
    /* 'FormatFlag' variable Bit description
        bit 0 alignment type: 0 represents left;
                              1 represents right.
        bit 1 flag of placeholder; 0 represents 0;
                                   1 represents ' '.
        bit 2 flag of long
        bit 3 (+/-) value types of long
        bit 4 User-defined floating point number width limit
        bit 5 (+/-) value types of float
     */
    StringLength = 0U;
    TempBufferPtr.BufferPtr = str;
    TempBufferPtr.SizePtr = &StringLength;
    TempBufferPtr.DirectPrintFlag = DirectPrintf;
    while(1)
    {
        FractionBitWidth = 0U;
        /* Get a uint8 type data from format and address offset */
        TempChar = *fmt++;
        /***********************************************************************************
         * Check the end of string flag, ends 'all While'
         ***********************************************************************************/
        /* Format ending with '\0' correspond to ASCII value 0 */
        if (TempChar == 0U)
        {
            /* Format output ends, ends While */
            break;
        }
        /***********************************************************************************
         * Process characters, e.g: "Hello World!", ends 'current While'
         ***********************************************************************************/
        /* If it is not a % sequence, it is transmitted immediately */
        if (TempChar != (uint8)'%')
        {
            PrintfCharHandle(TempBufferPtr, TempChar);
            /* The current character format output ends, ending the current While */
            continue;
        }
        /* Get the first uint8 of the 'fmt' sequence */
        TempChar = *fmt++;
        /***********************************************************************************
         * Check whether the character '%' is output
         ***********************************************************************************/
        if(TempChar == (uint8)'%')
        {
           PrintfCharHandle(TempBufferPtr, TempChar);
            /* The current character format output ends, ending the current While */
            continue;
        }
        /***********************************************************************************
         * Get 'va_list' alignment and placeholder characters
         ***********************************************************************************/
        /* Align right, use 'zero' placeholder on the left */
        if (TempChar == (uint8)'0')
        {
            /* Set flag: filled with '0' */
            FormatFlag = MASK_RIGHTALIGNED_FILLZREO;
            /* Get next uint8 char */
            TempChar = *fmt++;
        }
        /* Align left, use 'space' placeholder on the right */
        else if(TempChar == (uint8)'-')
        {
            /* Check Flag: left justified */
            FormatFlag = MASK_LEFTALIGNED_FILLSPACE;
            /* Get next uint8 char */
            TempChar = *fmt++;
        }
        /* Default Align right, use 'space' placeholder on the left */
        else
        {
            FormatFlag = MASK_RIGHTALIGNED_FILLSPACE;
        }
        /***********************************************************************************
         * Get the bit width limit value of the 'integer' part of 'va_list'
         ***********************************************************************************/
        /* Process the integer part width feature value in %*** */
        IntegerBitWidth = 0U;
        while(TempChar >= (uint8)'0' && TempChar <= (uint8)'9')
        {
            /* Change 'IntegerBitWidth' to a integer value */
            IntegerBitWidth = IntegerBitWidth * 10U + (TempChar - (uint8)'0');
            TempChar = *fmt++;
        }
        /***********************************************************************************
         * Get the bit width limit value of the 'fractional' part of 'va_list'
         ***********************************************************************************/
        if (TempChar == (uint8)'.')
        {
            FormatFlag |= MASK_ENABLEFLOAT_FRACTIONWIDTH;
            TempChar = *fmt++;
            /* Process the decimal part width feature value in %*** */
            FractionBitWidth = 0U;
            while(TempChar >= (uint8)'0' && TempChar <= (uint8)'9')
            {
                /* Change 'FractionBitWidth' to a integer value */
                FractionBitWidth = FractionBitWidth * 10U + (TempChar - (uint8)'0');
                TempChar = *fmt++;
            }
        }
        /***********************************************************************************
         * Gets whether the long type is enabled, the default is a positive number
         ***********************************************************************************/
        if (TempChar == (uint8)'l' || TempChar == (uint8)'L')
        {
            /* Check Flag: Prefix Size is long int */
            TempChar = *fmt++;
            if (TempChar == (uint8)'l' || TempChar == (uint8)'L')
            {
                /* Check Flag: Prefix Size is long long int */
                FormatFlag |= MASK_LONGTYPE_POSITIVENUM;
                TempChar = *fmt++;
            }
        }
        /***********************************************************************************
         * Check the output format type of 'va_list'
         ***********************************************************************************/
        CapChar = TempChar;
        if (CapChar >= (uint8)'a')
        {
            /* Change lowercase characters to uppercase characters */
            CapChar -= 0x20U;
        }
        DecimalMask = MASK_OUTPUTCHAR;
        ListCount = 0U;
        switch (CapChar)
        {
            /* Data is of 'string' type */
            case (uint8)'S':
            {
                /* Get parameters from 'va_list arp' and cast to 'uint8*' */
                Va_List8 = va_arg(arp, uint8*);
                /* Get the length of 'va_list arp' by looking for the end of string mark '\0' */
                while (Va_List8[ListCount] != 0U)
                {
                    ListCount++;
                }
                /* Get placeholder characters */
               TempChar = (MASK_RIGHTALIGNED_FILLZREO == (FormatFlag & MASK_RIGHTALIGNED_FILLSPACE)) ? (uint8)'0' : (uint8)' ';
                /* Align right, print placeholder characters in advance */
                while ((MASK_LEFTALIGNED_FILLSPACE != (FormatFlag & MASK_RIGHTALIGNED_FILLSPACE))
                        && (ListCount++ < IntegerBitWidth))
                {
                    PrintfCharHandle(TempBufferPtr, TempChar);
                }
                /* Transfer string to output buffer */

                PrintfStringHandle(TempBufferPtr, Va_List8);
                /* left-aligned placeholder character output */
                while ((MASK_LEFTALIGNED_FILLSPACE == (FormatFlag & MASK_RIGHTALIGNED_FILLSPACE))
                        && (ListCount++ < IntegerBitWidth))
                {
                    PrintfCharHandle(TempBufferPtr, (uint8)' ');
                }
                break;
            }
            /* Data is of 'char' type */
            case (uint8)'C':
            {
                /* Get placeholder characters */
                TempChar = (MASK_RIGHTALIGNED_FILLZREO == (FormatFlag & MASK_RIGHTALIGNED_FILLSPACE)) ? (uint8)'0' : (uint8)' ';
                /* Align right, print placeholder characters in advance */
                while ((MASK_LEFTALIGNED_FILLSPACE != (FormatFlag & MASK_RIGHTALIGNED_FILLSPACE))
                        && (ListCount++ < IntegerBitWidth))
                {
                    PrintfCharHandle(TempBufferPtr, TempChar);
                }
                /* Get parameters from 'va_list arp' and cast to 'sint32' */
                PrintfCharHandle(TempBufferPtr, (uint8)va_arg(arp, sint32));
                /* left-aligned placeholder character output */
                while ((MASK_LEFTALIGNED_FILLSPACE == (FormatFlag & MASK_LEFTALIGNED_FILLSPACE))
                        && (ListCount++ < IntegerBitWidth))
                {
                    PrintfCharHandle(TempBufferPtr, (uint8)' ');
                }
                break;
            }
            /* Data is of 'Float' type */
            case (uint8)'F':
            {
                /* Get parameters from 'va_list arp' and cast to 'Double Precision float64' */
                TempFloat64 = va_arg(arp, float64);
                /* check wether the float is NaN or Inf */
                TempFloatStr = PrintfCheckFloat64(TempFloat64);
                PrintFloatStrCnt = 0;
                if (TempFloatStr != NULL_PTR)
                {
                    /* Transfer string to output buffer */
                    while(TempFloatStr[PrintFloatStrCnt] != '\0')
                    {
                        DataBuffer[ListCount++] = TempFloatStr[PrintFloatStrCnt++];
                    }
                    DataBuffer[ListCount] = '\0';
                    PrintfStringHandle(TempBufferPtr, DataBuffer);
                    break;
                }
                /* Handling negative type floating point numbers */
                else if (TempFloat64 < (float64)0.0)
                {
                    /* Set the sign of negative floating point numbers in the output string */
                    DataBuffer[ListCount++] = (uint8)'-';
                    /* Get the absolute value of a negative type floating point number */
                    TempFloat64 = -TempFloat64;
                }
                else
                {
                    /* Do Nothing */
                }
                /* Get the integer part of a floating point number */
                FloatIntPart = (uint32)TempFloat64;
                if (0U == FloatIntPart)
                {
                    /* Set the sign of positive floating point numbers in the output string */
                    DataBuffer[ListCount++] = (uint8)'0';
                }
                else
                {
                    /* Convert floating point integer value to character and store in temporary buffer */
                    PrintfFloatHandle(FloatIntPart, DataBuffer, &ListCount);
                }
                /* Set the '.' character in the output floating point string */
                DataBuffer[ListCount++] = (uint8)'.';
                /* Get the decimal part of a floating point number */
                TempFloat64 -= (float64)FloatIntPart;
                /* Check floating point flags in output format */
                if (MASK_ENABLEFLOAT_FRACTIONWIDTH == (FormatFlag & MASK_ENABLEFLOAT_FRACTIONWIDTH))
                {
                    /* Format output floating point number decimal part */
                    for (Count = 0U; Count < FractionBitWidth; Count++)
                    {
                        TempFloat64 *= (float64)10U;
                    }
                    /* This is necessary, otherwise the accuracy will be lost */
                    TempFloat32 = (float32)TempFloat64;
                    FloatIntPart = (uint32)TempFloat32;
                    FloatLen = FractionBitWidth - GetStringLenth(FloatIntPart);
                }
                else
                {
                    /* This is necessary, otherwise the accuracy will be lost */
                    TempFloat32 = (float32)(TempFloat64 * (float64)1000000U);
                    FloatIntPart = (uint32)TempFloat32;
                    FloatLen = MASK_FLOATDEFAULT_FRACTIONWIDTH - GetStringLenth(FloatIntPart);
                }
                while(FloatLen > 0U)
                {
                    FloatLen--;
                    DataBuffer[ListCount++] = (uint8)'0';
                }
                PrintfFloatHandle(FloatIntPart, DataBuffer, &ListCount);
                DataBuffer[ListCount] = (uint8)'\0';
                /* Get placeholder characters */
               TempChar = (MASK_RIGHTALIGNED_FILLZREO == (FormatFlag & MASK_RIGHTALIGNED_FILLSPACE)) ? (uint8)'0' : (uint8)' ';
                /* Align right, print placeholder characters in advance */
                while ((MASK_LEFTALIGNED_FILLSPACE != (FormatFlag & MASK_RIGHTALIGNED_FILLSPACE))
                        && (ListCount++ < IntegerBitWidth))
                {
                    PrintfCharHandle(TempBufferPtr, TempChar);
                }
                PrintfStringHandle(TempBufferPtr, DataBuffer);
                break;
            }
            /* Data is of 'Binary' type */
            case (uint8)'B':
            {
                DecimalMask = MASK_OUTPUTBINARY;
                break;
            }
            /* Data is of 'octal' type */
            case (uint8)'O':
            {
                /* Octal */
                DecimalMask = MASK_OUTPUTOCTAL;
                break;
            }
            /* Data is of 'Signed decimal' type */
            case (uint8)'D':
            {
                DecimalMask = MASK_OUTPUTDECIMAL;
                break;
            }
            /* Data is of 'Unsigned decimal' type */
            case (uint8)'U':
            {
                DecimalMask = MASK_OUTPUTDECIMAL;
                break;
            }
            /* Data is of 'Hex decimal' type */
            case (uint8)'X':
            {
                DecimalMask = MASK_OUTPUTHEX;
                break;
            }
            default:
            {
                DecimalMask = 0U;
                PrintfCharHandle(TempBufferPtr, TempChar);
                break;
            }
        }
        /***********************************************************************************
         * Check for string, character, float output, ends 'current While'
         ***********************************************************************************/
        if (DecimalMask == 0U)
        {
            continue;
        }
        /***********************************************************************************
         * Get 'va_list' of 'binary, octal, signed decimal, unsigned decimal, hexadecimal' numbers
         ***********************************************************************************/
        if(MASK_LONGTYPE_POSITIVENUM == (FormatFlag & MASK_LONGTYPE_POSITIVENUM))
        {
            /* Use '%lld, %lx' format to output positive(+) integers */
            Va_List64 = (uint64)va_arg(arp, sint64);
            if((CapChar == (uint8)'D') && ((Va_List64 & 0x8000000000000000UL) != 0UL))
            {

                Va_List64 = 0UL - Va_List64;
                /* Set the signed negative flag */
                FormatFlag |= MASK_LONGTYPE_NEGATIVENUM;
            }
        }
        else
        {
            /* Use '%b,%o,%u,%d,%x,%ld,%lx' format to output positive(+) integers */
            Va_List64 = (uint64)va_arg(arp, sint32);
            if((CapChar == (uint8)'D') && ((Va_List64 & 0x80000000UL) != 0UL))
            {

                Va_List64 = 0UL - Va_List64;
                /* Set the signed negative flag */
                FormatFlag |= MASK_LONGTYPE_NEGATIVENUM;
            }
            Va_List64 = (uint32)Va_List64;
        }
        /***********************************************************************************
         * Convert the data to n-base and store it in the buffer
         ***********************************************************************************/
        ListCount = 0U;
        do
        {
            /* Remainder operation to obtain the actual value under DecimalMask */
            CapChar = (uint8)(Va_List64 % DecimalMask);
            Va_List64 /= DecimalMask;
            /* Check remainder is greater than 9, convert to letters */
            if (CapChar > 9U)
            {
                /* Use upper/lower case letters for output,
                Calculate ASCII values starting from '0' */
                CapChar += (TempChar == (uint8)'x') ? 0x27U : 0x07U;
            }
            /* Convert numeric value to character and save to temporary data buffer */
            DataBuffer[ListCount++] = CapChar + (uint8)'0';
        } while ((Va_List64 != 0U) && ListCount < sizeof(DataBuffer));

        /* Check if there is a negative sign */
        if ((MASK_LONGTYPE_NEGATIVENUM == (FormatFlag & MASK_LONGTYPE_NEGATIVENUM)) && (ListCount < sizeof(DataBuffer)))
        {
            DataBuffer[ListCount++] = (uint8)'-';
        }

        Count = ListCount;
        /* Get placeholder characters */
        TempChar = (MASK_RIGHTALIGNED_FILLZREO == (FormatFlag & MASK_RIGHTALIGNED_FILLSPACE)) ? (uint8)'0' : (uint8)' ';
        /* Align right, print placeholder characters in advance */
        while ((MASK_LEFTALIGNED_FILLSPACE != (FormatFlag & MASK_RIGHTALIGNED_FILLSPACE))
                && (ListCount++ < IntegerBitWidth))
        {
            PrintfCharHandle(TempBufferPtr, TempChar);
        }
        /* Print the string of data conversion in the reverse direction */
        do
        {
            PrintfCharHandle(TempBufferPtr, DataBuffer[--Count]);
        } while (Count != 0U);
        /* left-aligned placeholder character output */
        while ((MASK_LEFTALIGNED_FILLSPACE == (FormatFlag & MASK_RIGHTALIGNED_FILLSPACE))
                && (ListCount++ < IntegerBitWidth))
        {
            PrintfCharHandle(TempBufferPtr, (uint8)' ');
        }
    }

#if (STD_ON == DEMO_PRINTQUEUEMODE)
    if (TRUE == TempBufferPtr.DirectPrintFlag)
    {
        /* Write the string into Queue */
        Printfbuffer[CoreId]->BufferPtr[0] = *TempBufferPtr.SizePtr + 1U;
        SuspendAllInterrupts();
        while(Printf_GetLock());
        /* save the print data into the queue */
        PrintQueuePtr = (Mcal_SeqQueueType *)&Print_Queue;
        (void)Mcal_QueuePush(PrintQueuePtr, (uint8 *)&Printfbuffer[CoreId]->BufferPtr[0]);
        Printf_ReleaseLock();
        ResumeAllInterrupts();
    }
#endif /* (STD_ON == DEMO_PRINTQUEUEMODE) */

    return StringLength;
}
/****************************************************************************************************
**                           Global Function Definitions                                           **
****************************************************************************************************/
#if (STD_ON == DEMO_PRINTQUEUEMODE)
/****************************************************************************************************
*   Function Name           : Mcal_QueueCreate
*
*   Service ID              : None.
*
*   Description             : Create a sequence queue.
*                             this is just design for demo and take no responsibility for any other
*                             formal projects and outer callers
*
*   Parameters in           : SeqQueuePtr: Pointer to a Queue;
*                             ElemBufferPtr: Pointer to a buffer that used for store the queue data;
*                             ElemBufferLen: Total length of queue element buffer.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant(thread-safe)
*
*   Return value            :
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(Mcal_QueueStatusType, MCAL_PUBLIC_CODE) Mcal_QueueCreate
(
    P2VAR(Mcal_SeqQueueType, AUTOMATIC, INTC_APPL_CONST) SeqQueuePtr,
    P2VAR(uint8, AUTOMATIC, INTC_APPL_CONST) ElemBufferPtr,
    Mcal_QueueLenType ElemBufferLen
)
{
    Mcal_QueueStatusType QueueStatus;

    QueueStatus = MCAL_QUEUE_NORMAL;

    if (NULL_PTR == SeqQueuePtr)
    {
        /* Queue element buffer pointer to null */
        QueueStatus = MCAL_QUEUE_NULL;
    }
    else if (NULL_PTR == ElemBufferPtr)
    {
        QueueStatus = MCAL_QUEUE_BUF_NULL;
    }
    else if (0U == ElemBufferLen)
    {
        /* Queue length is 0 */
        QueueStatus = MCAL_QUEUE_LEN_ZERO;
    }
    else
    {
        /* Pointer the buffer that the queue data store buffer */
        SeqQueuePtr->QueueElemPtr = ElemBufferPtr;
        /* Set the queue length */
        SeqQueuePtr->QueueSize = ElemBufferLen;
        /* Clear queue flags */
        SeqQueuePtr->QueueFront = 0U;
        SeqQueuePtr->QueueRear = 0U;
        SeqQueuePtr->QueueCount = 0U;
    }

    return QueueStatus;
}

/****************************************************************************************************
*   Function Name           : Printf_QueueInit
*
*   Service ID              : NONE.
*
*   Description             : Init debug printf data queue.
*                             this is just design for demo and take no responsibility for any other
*                             formal projects and outer callers
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, MCAL_PUBLIC_CODE) Printf_QueueInit
(
    void
)
{
    Mcal_SeqQueueType *PrintQueuePtr;
    PrintQueuePtr = (Mcal_SeqQueueType *)&Print_Queue;
    /* Initialize the queue for store the data to be print */
    (void)Mcal_QueueCreate(PrintQueuePtr, &Print_ElemBuffer[0], PRINTF_QUEUE_BUFFER_LEN);
}

/****************************************************************************************************
*   Function Name           : Mcal_QueuePush
*
*   Service ID              : None.
*
*   Description             : Create a sequence queue.
*                             this is just design for demo and take no responsibility for any other
*                             formal projects and outer callers
*
*   Parameters in           : SeqQueuePtr: Pointer to a Queue;
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant(thread-safe)
*
*   Return value            :
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(Std_ReturnType, MCAL_PUBLIC_CODE) Mcal_QueuePush
(
    P2VAR(Mcal_SeqQueueType, AUTOMATIC, INTC_APPL_CONST) SeqQueuePtr,
    P2VAR(uint8, AUTOMATIC, INTC_APPL_CONST) DataPtr
)
{
    Mcal_QueueStatusType QueueStatus;
    Std_ReturnType Status;
    uint8 ElemCnt;
    Mcal_QueueLenType QueueCurIdx;

    Status = E_NOT_OK;
    /* DET check - TBD */

    QueueStatus = Mcal_GetQueueFullStatus(SeqQueuePtr, DataPtr);
    if (MCAL_QUEUE_NORMAL == QueueStatus)
    {
        /* The first byte of 'DataPtr' is Data length that to be insert the queue */
        for (ElemCnt = 0U; ElemCnt <= DataPtr[MCAL_CORE_COMM_LEN_POS]; ElemCnt++)
        {
            QueueCurIdx = (SeqQueuePtr->QueueRear + ElemCnt) % (SeqQueuePtr->QueueSize);
            /* Pointer to the user buffer */
            SeqQueuePtr->QueueElemPtr[QueueCurIdx] = DataPtr[ElemCnt];

            SeqQueuePtr->QueueCount++;
        }
        /* Point the queue tail to next element */
        SeqQueuePtr->QueueRear =
            (SeqQueuePtr->QueueRear + DataPtr[MCAL_CORE_COMM_LEN_POS] + 1U) % SeqQueuePtr->QueueSize;

        Status = E_OK;
    }

    return Status;
}

/****************************************************************************************************
*   Function Name           : Mcal_QueuePop
*
*   Service ID              : None.
*
*   Description             : Create a sequence queue
*                             this is just design for demo and take no responsibility for any other
*                             formal projects and outer callers
*
*   Parameters in           : SeqQueuePtr: Pointer the queue.
*                             DataPtr: Data that to be inserted into the queue.
*                                      Data[0] - Data length without this byte
*                                      Data[2 ... n] - Data parameters
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant(thread-safe)
*
*   Return value            :
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(Std_ReturnType, MCAL_PUBLIC_CODE) Mcal_QueuePop
(
    P2VAR(Mcal_SeqQueueType, AUTOMATIC, INTC_APPL_CONST) SeqQueuePtr,
    P2VAR(uint8, AUTOMATIC, INTC_APPL_CONST) DataPtr
)
{
    Mcal_QueueStatusType QueueStatus;
    Std_ReturnType       Status;
    uint8                ElemCnt;
    Mcal_QueueLenType    QueueCurIdx;

    Status = E_NOT_OK;

    /* DET check - TBD */
    QueueStatus = Mcal_GetQueueEmptyStatus(SeqQueuePtr);
    if (MCAL_QUEUE_NORMAL == QueueStatus)
    {
        /* Pop user data */
        /* The first byte of 'DataPtr' is Data length */
        for (ElemCnt = 0U; ElemCnt <= SeqQueuePtr->QueueElemPtr[SeqQueuePtr->QueueFront]; ElemCnt++)
        {
            QueueCurIdx = (SeqQueuePtr->QueueFront + ElemCnt) % (SeqQueuePtr->QueueSize);
            /* Pointer to the user buffer */
            DataPtr[ElemCnt] = SeqQueuePtr->QueueElemPtr[QueueCurIdx];

            SeqQueuePtr->QueueCount--;
        }
        /* Point the queue header to next element */
        SeqQueuePtr->QueueFront =
           (SeqQueuePtr->QueueFront + DataPtr[MCAL_CORE_COMM_LEN_POS] + 1U) % SeqQueuePtr->QueueSize;

        Status = E_OK;
    }

    return Status;
}
/****************************************************************************************************
*   Function Name           : Mcal_GetQueueFullStatus
*
*   Service ID              : None.
*
*   Description             : Create a sequence queue.
*                             this is just design for demo and take no responsibility for any other
*                             formal projects and outer callers
*
*   Parameters in           : SeqQueuePtr: Pointer the queue.
*                             DataPtr: Data that to be inserted into the queue.
*                                      Data[0] - Data length without this byte
*                                      Data[1] - Service Id
*                                      Data[2 ... n] - Data parameters
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant(thread-safe)
*
*   Return value            :
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(Mcal_QueueStatusType, MCAL_PUBLIC_CODE) Mcal_GetQueueFullStatus
(
    P2VAR(Mcal_SeqQueueType, AUTOMATIC, INTC_APPL_CONST) SeqQueuePtr,
    P2VAR(uint8, AUTOMATIC, INTC_APPL_CONST) DataPtr
)
{
    Mcal_QueueStatusType QueueStatus;

    QueueStatus = MCAL_QUEUE_NORMAL;

    if ((SeqQueuePtr->QueueCount + DataPtr[0]) >= SeqQueuePtr->QueueSize)
    {
        /* Queue is full */
        QueueStatus = MCAL_QUEUE_FULL;
    }
    else if (DataPtr[0] == 0U)
    {
        /* Invalid data */
        QueueStatus = MCAL_QUEUE_DATA_INVALID;
    }
    else
    {
        /* Do Nothing */
    }

    return QueueStatus;
}
/****************************************************************************************************
*   Function Name           : Mcal_GetQueueEmptyStatus
*
*   Service ID              : None.
*
*   Description             : Create a sequence queue.
*                             this is just design for demo and take no responsibility for any other
*                             formal projects and outer callers
*
*   Parameters in           : SeqQueuePtr: Pointer the queue.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant(thread-safe)
*
*   Return value            :
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(Mcal_QueueStatusType, MCAL_PUBLIC_CODE) Mcal_GetQueueEmptyStatus
(
    P2VAR(Mcal_SeqQueueType, AUTOMATIC, INTC_APPL_CONST) SeqQueuePtr
)
{
    Mcal_QueueStatusType Status;

    Status = MCAL_QUEUE_NORMAL;

    if (0U == SeqQueuePtr->QueueCount)
    {
        /* SeqQueue->QueueFront = SeqQueue->QueueRear indicate that queue is empty */
        Status = MCAL_QUEUE_EMPTY;
    }

    return Status;
}

/****************************************************************************************************
*   Function Name           : PrintfPrint
*
*   Service ID              : NONE.
*
*   Description             : Read data from the queue and sent
*                             this is just design for demo and take no responsibility for any other
*                             formal projects and outer callers
*
*   Parameters in           : DirectPrintf Whether to POP all queues at once
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
void PrintfPrint(void)
{
    uint8                    QElemBuf[PRINTF_EACH_BUFFER_LEN];
    Std_ReturnType           QueueStatus;
    uint16                   Count;
    Mcal_SeqQueueType *      PrintQueuePtr;
    
    QueueStatus = E_OK;
    PrintQueuePtr = (Mcal_SeqQueueType *)&Print_Queue;
#if (STD_OFF == DEMO_PRINTINTERRUPT)
    while(E_OK == QueueStatus)
#endif /* STD_ON == DEMO_PRINTINTERRUPT */
    {
        SuspendAllInterrupts();
        while(Printf_GetLock());
        /* save the print data into the queue */
        QueueStatus = Mcal_QueuePop(PrintQueuePtr, &QElemBuf[0]);
        Printf_ReleaseLock();
        ResumeAllInterrupts();

        if (E_OK == QueueStatus)
        {
            for (Count = 1U; Count < QElemBuf[0]; Count++)
            {
                while((boolean)Uart_Write(DebugChannel, &QElemBuf[Count], 0x01U));
            }
        }
    }
}
#endif /* (STD_ON == DEMO_PRINTQUEUEMODE) */
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : TmcPrintf
*
*   Service ID              : NONE.
*
*   Description             : Put a formatted string to the specified device
*                             this is just design for demo and take no responsibility for any other
*                             formal projects and outer callers
*
*   Parameters in           : func: Pointer to the output function
*                             fmt:  Pointer to the format string
*                             ...:  Optional arguments
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
uint8 TmcPrintf(char* str, const uint8* fmt, ...)
{
    va_list arp;
    uint8 SprintfLength;

    SprintfLength = 0U;
#if (STD_ON == DEMO_PRINTQUEUEMODE)
    Mcal_CoreType CoreId;

    CoreId = Mcal_GetCoreId();
    if (FALSE == Print_QueueInitStatus)
    {
        /* Initialize the queue when first called */
        Printf_QueueInit();
        Print_QueueInitStatus = TRUE;
    }
    va_start(arp, fmt);
    if (NULL_PTR == str)
    {
        (void)PrintfByteHandle(TRUE, &Printfbuffer[CoreId]->BufferPtr[1], fmt, arp);
    }
    else
    {
        SprintfLength = PrintfByteHandle(FALSE, str, fmt, arp);
    }
#else
    va_start(arp, fmt);
    if (NULL_PTR == str)
    {
        (void)PrintfByteHandle(TRUE, NULL_PTR, fmt, arp);
    }
    else
    {
        SprintfLength = PrintfByteHandle(FALSE, str, fmt, arp);
    }
#endif /* (STD_ON == DEMO_PRINTQUEUEMODE) */
    va_end(arp);

    return SprintfLength;
}

/****************************************************************************************************
*   Function Name           : getChar
*
*   Service ID              : NONE.
*
*   Description             : Read received data and Reset receiving status Flag.
*                             this is just design for demo and take no responsibility for any other
*                             formal projects and outer callers
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : The data of Finish receiving.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : 0: Failed
*                             1: Successful
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
char getChar(void)
{
    Uart_DataBufferType RXDataBuffer = 0xFFU;

    while((boolean)Uart_Read(DebugChannel, &RXDataBuffer));

    return (char)RXDataBuffer;
}

void Gpt_Notification_UartPrintf(void)
{
#if ((STD_ON == DEMO_PRINTQUEUEMODE) && (STD_ON == DEMO_PRINTINTERRUPT))
    PrintfPrint();
#endif /* (STD_ON == DEMO_PRINTQUEUEMODE) && (STD_ON == DEMO_PRINTINTERRUPT) */
}

#define UART_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Uart_MemMap.h"
