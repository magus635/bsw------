/* SC300 kernel port test on QEMU mps2-an385. Every step appends a number to the trace; the
 * run passes when the trace equals EXPECTED. Covers: task preemption/termination, Cat2 ISR
 * preempting a task, nested Cat2 ISRs, resource ceiling, alarm on SysTick + WaitEvent/SetEvent,
 * task switch at the end of an ISR. */
#include "Os.h"
#include "Os_task_Cfg.h"
#include "Os_alarm_Cfg.h"
#include "Os_resource_Cfg.h"
#include "Os_application_Cfg.h"
#include "Os_kernel.h"
#include "Os_counter_Cfg.h"

extern void sh_puts(const char *s);
extern void sh_hex(uint32 v);
extern void sh_exit(int ok);

#define NVIC_ISPR0 (*(volatile uint32 *)0xE000E200UL)
#define IRQ_LOW    (1UL << 0)    /* exception 16: Test_Isr2_Low, priority 4 */
#define IRQ_HIGH   (1UL << 1)    /* exception 17: Test_Isr2_High, priority 3 (higher) */

static const uint8 EXPECTED[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
static volatile uint8 Trace[32];
static volatile uint32 TraceLen;
static volatile uint32 Phase;
static volatile uint32 Ticks;

static void step(uint8 n, const char *what)
{
    if (TraceLen < sizeof(Trace)) { Trace[TraceLen] = n; }
    TraceLen++;
    sh_puts(what);
    sh_puts("\n");
}

static void finish(void)
{
    uint32 i;
    boolean ok = (TraceLen == sizeof(EXPECTED)) ? TRUE : FALSE;
    for (i = 0; (i < sizeof(EXPECTED)) && (i < TraceLen); i++) {
        if (Trace[i] != EXPECTED[i]) { ok = FALSE; }
    }
    sh_puts(ok ? "RESULT: PASS\n" : "RESULT: FAIL\n");
    sh_exit(ok);
}

/* Highest priority autostart task */
TASK(Default_Init_Task)
{
    step(1, " 1 Init_Task runs first (highest autostart)");
    (void)ActivateTask(STARTAPPLICATION_APPL_INIT_TASK);
    step(2, " 2 Init_Task continues after activating a lower task");
    Phase = 1;
    NVIC_ISPR0 = IRQ_LOW;                 /* Cat2 ISR preempts the task */
    __asm volatile("dsb\n isb");
    step(6, " 6 Init_Task resumes after the ISRs");
    (void)TerminateTask();
}

void Test_Isr2_Low(void)
{
    if (1U == Phase) {
        step(3, " 3 ISR low entered (preempted Init_Task)");
        NVIC_ISPR0 = IRQ_HIGH;            /* nested higher-priority ISR */
        __asm volatile("dsb\n isb");
        step(5, " 5 ISR low resumes after the nested ISR");
    } else {
        step(14, "14 ISR low activates RTE task (higher than Appl_Task)");
        (void)ActivateTask(DEFAULT_RTE_MODE_SWITCH_TASK);
    }
}

void Test_Isr2_High(void)
{
    step(4, " 4 ISR high nested in ISR low");
}

TASK(Default_Init_Task_Trusted)
{
    step(7, " 7 Init_Task_Trusted (next autostart)");
    (void)TerminateTask();
}

TASK(StartApplication_Appl_Init_Task)
{
    step(8, " 8 Appl_Init_Task");
    (void)ActivateTask(DEFAULT_BSW_ASYNC_TASK_CORE0);
    (void)TerminateTask();
}

TASK(Default_BSW_Async_Task_Core0)
{
    (void)GetResource(OSRESOURCE);       /* ceiling = Sync task priority */
    (void)ActivateTask(DEFAULT_BSW_SYNC_TASK);
    step(9, " 9 Async_Task holds the resource: Sync_Task does not preempt");
    (void)ReleaseResource(OSRESOURCE);
    step(11, "11 Async_Task after ReleaseResource");
    (void)ActivateTask(STARTAPPLICATION_APPL_TASK_CORE0);
    (void)TerminateTask();
}

TASK(Default_BSW_Sync_Task)
{
    step(10, "10 Sync_Task runs at ReleaseResource");
    (void)TerminateTask();
}

TASK(StartApplication_Appl_Task_Core0)
{
    TickType before = 0, after = 0;
    step(12, "12 Appl_Task waits for an alarm on the SysTick counter");
    (void)GetCounterValue(SYSTEMTIMER_CORE0, &before);
    (void)SetRelAlarm(RTE_AL_TE_STARTAPPLICATION_APPL_TASK_CORE0_0_100MS, 3, 0);
    (void)WaitEvent(RTE_EV_CYCLIC_STARTAPPLICATION_APPL_TASK_CORE0_0_100MS);
    (void)GetCounterValue(SYSTEMTIMER_CORE0, &after);
    (void)ClearEvent(RTE_EV_CYCLIC_STARTAPPLICATION_APPL_TASK_CORE0_0_100MS);
    sh_puts("   counter ticks waited: ");
    sh_hex((uint32)(after - before));
    sh_puts("\n");
    step((after - before) == 3U ? 13 : 99, "13 Appl_Task woken by the alarm after 3 ticks");
    Phase = 2;
    NVIC_ISPR0 = IRQ_LOW;
    __asm volatile("dsb\n isb");
    step(16, "16 Appl_Task resumes after the higher task");
    finish();
}

TASK(Default_RTE_Mode_switch_Task)
{
    step(15, "15 RTE task runs right after the ISR, before Appl_Task resumes");
    (void)TerminateTask();
}


TASK(Idle_Task_Core0)
{
    for (;;) { __asm volatile("nop"); }
}

int main(void)
{
    sh_puts("SC300 kernel port test (QEMU mps2-an385)\n");
    Os_PreInit();
    StartOS(OSDEFAULTAPPMODE);
    return 0;
}
