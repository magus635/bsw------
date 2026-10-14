Elektrobit tresos MicroOS with TRACE32 Trace over ARTI Hooks

This archive provides an implementation to trace Elektrobit's MK_TRACE_STATE_THREAD
interface with Lauterbach's TRACE32 tools. It uses the AUTOSAR ARTI standard.

REQUIREMENTS:

- TRACE32 Version R2020-09 or higher


CONTENTS:

- readme.txt
  This file

- Mk_kconfig.h
  Header file mapping the OS hooks to ARTI hooks

- arti_eb_microos.c
  Source file for MicorOS specific ARTI variables

- gen_eb_rte_hook.py
  Python script to generate RTE VFB Hook implementations

- rthread2rtask.cmm
  TRACE32 script to convert the EB ORTI file

- ../../common
  Directory to be copied to your project

- ../../scripts
  Directory containing scripts to trace the ARTI hooks


QUICK GUIDE

1. Copy the the complete contents of the "common" directory, the "Mk_kconfig.h" and
   "arti_eb_microos.c" file into your project's subdirectory "source\stubs".

2. Read the readme.txt file in the "common" directory.

3. Edit the arti.h file and select your tracing method.

4. Edit the header file of the selected tracing method according to
   the readme.txt file in the appropriate subdirectory.

5. Copy the "gen_eb_rte_hook.py" Python script into the "util" directory and
   edit it to adjust the paths to point to your Rte_Cfg.h file.

6. Run the "gen_eb_rte_hook.py" Python script to generate the RTE hook implementation
   "Rte_Hook_Arti.c" and Runnable declaration script "rte_runnable.cmm".

7. Add an "Arti_Init" call to your EcuM InitListOne

8. Make a clean build of your project.

9. Copy the "rthread2rtask.cmm" file into your project's "output\generated\orti"
   directory.

10. When starting TRACE32, run the "rthread2rtask.cmm" script once.
   It creates an "os_task.orti" file out of the "os.orti" file.
   When debugging, use the newly created "os_task.orti" instead.
