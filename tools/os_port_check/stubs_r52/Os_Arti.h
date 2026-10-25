/* Stand-in for the trace tool's Os_Arti.h so that the kernel compiles without ARTI tracing hooks. */
#ifndef OS_ARTI_STUB_H
#define OS_ARTI_STUB_H
#define ARTI_TRACE(...) ((void)0)
#endif
