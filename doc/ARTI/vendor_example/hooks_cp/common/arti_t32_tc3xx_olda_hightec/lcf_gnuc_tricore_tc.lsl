% Snippet to include OLDA memory to linker script (Hightec Compiler)


MEMORY
{
	task_olda_nc     (w!xp): org = 0xAFE00000, len = 32
	runnable_olda_nc (w!xp): org = 0xAFE00008, len = 32
	syscall_olda_nc  (w!xp): org = 0xAFE00010, len = 32
}
SECTIONS
{
	CORE_SEC(.TRACE32_TASKEVENT_BASE_MEM) (NOLOAD) : {
		*(.TRACE32_TASKEVENT_BASE_MEM)
	} > task_olda_nc
	CORE_SEC(.TRACE32_RUNNABLE_BASE_MEM) (NOLOAD) : {
		*(.TRACE32_RUNNABLE_BASE_MEM)
	} > runnable_olda_nc
	CORE_SEC(.TRACE32_SYSCALL_BASE_MEM) (NOLOAD) : {
		*(.TRACE32_SYSCALL_BASE_MEM)
	} > syscall_olda_nc
}
