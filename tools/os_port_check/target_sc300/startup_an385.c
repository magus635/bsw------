/* Minimal startup for QEMU mps2-an385 (Cortex-M3): vector table, data/bss init,
 * semihosting output and exit. Test harness only, not product code. */
#include <stdint.h>

extern uint32_t __stack_top, __data_load, __data_start, __data_end, __bss_start, __bss_end;
extern void SysIRQ_Handler(void);
extern void SVC_Handler(void);
extern int main(void);

static int sh_call(int op, const void *arg)
{
    register int r0 __asm__("r0") = op;
    register const void *r1 __asm__("r1") = arg;
    __asm volatile("bkpt 0xab" : "+r"(r0) : "r"(r1) : "memory");
    return r0;
}

void sh_puts(const char *s) { sh_call(0x04, s); }        /* SYS_WRITE0 */

void sh_exit(int ok)
{
    /* SYS_EXIT with ADP_Stopped_ApplicationExit (0x20026) or RunTimeErrorUnknown (0x20023) */
    sh_call(0x18, (const void *)(ok ? 0x20026u : 0x20023u));
    for (;;) { }
}

void sh_hex(uint32_t v)
{
    char b[11] = "0x";
    for (int i = 0; i < 8; i++) {
        uint32_t n = (v >> (28 - 4 * i)) & 0xF;
        b[2 + i] = (char)(n < 10 ? '0' + n : 'a' + n - 10);
    }
    b[10] = 0;
    sh_puts(b);
}

static void Fault_Report(uint32_t *frame);
__attribute__((naked)) static void Fault_Handler(void)
{
    __asm volatile("mov r0, sp\n b Fault_Report");
}

__attribute__((used)) static void Fault_Report(uint32_t *frame)
{
    uint32_t ipsr;
    __asm volatile("mrs %0, ipsr" : "=r"(ipsr));
    sh_puts("FAULT pc ");
    sh_hex(frame[6]);
    sh_puts(" lr ");
    sh_hex(frame[5]);
    sh_puts(" BFAR ");
    sh_hex(*(volatile uint32_t *)0xE000ED38u);
    sh_puts("\n");
    sh_puts("FAULT exception ");
    sh_hex(ipsr);
    sh_puts(" CFSR ");
    sh_hex(*(volatile uint32_t *)0xE000ED28u);
    sh_puts("\n");
    sh_exit(0);
}

void Reset_Handler(void)
{
    uint32_t *s = &__data_load, *d = &__data_start;
    while (d < &__data_end) { *d++ = *s++; }
    for (d = &__bss_start; d < &__bss_end; ) { *d++ = 0; }
    *(volatile uint32_t *)0xE000ED24u |= (7u << 16);  /* enable Mem/Bus/Usage faults */
    (void)main();
    sh_puts("main returned\n");
    sh_exit(0);
}

typedef void (*vector_t)(void);
__attribute__((section(".vectors"), used))
const vector_t vectors[16 + 32] = {
    (vector_t)&__stack_top, Reset_Handler,
    Fault_Handler, Fault_Handler, Fault_Handler, Fault_Handler, Fault_Handler,  /* NMI..Usage */
    0, 0, 0, 0,
    SVC_Handler, Fault_Handler, 0, Fault_Handler,                               /* SVC, Debug, -, PendSV */
    SysIRQ_Handler,                                                             /* SysTick */
    [16 ... 47] = SysIRQ_Handler,
};
