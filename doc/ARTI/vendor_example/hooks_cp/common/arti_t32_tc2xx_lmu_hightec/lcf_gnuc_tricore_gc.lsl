% Snippet to include LMU memory to linker script (Hightec Compiler)

MEMORY
{
	task_lmu_nc     (w!xp): org = 0xB0000000, len = 32
	runnable_lmu_nc (w!xp): org = 0xB0000008, len = 32
	syscall_lmu_nc  (w!xp): org = 0xB0000010, len = 32
}
SECTIONS
{
	CORE_SEC(.TRACE32_TASKEVENT_BASE_MEM) : {
		*(.TRACE32_TASKEVENT_BASE_MEM)
	} > task_lmu_nc
	CORE_SEC(.TRACE32_RUNNABLE_BASE_MEM) : {
		*(.TRACE32_RUNNABLE_BASE_MEM)
	} > runnable_lmu_nc
	CORE_SEC(.TRACE32_SYSCALL_BASE_MEM) : {
		*(.TRACE32_SYSCALL_BASE_MEM)
	} > syscall_lmu_nc
}
