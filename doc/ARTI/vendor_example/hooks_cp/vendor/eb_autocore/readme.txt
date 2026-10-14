Elektrobit tresos AutoCore OS with TRACE32 Trace over ARTI Hooks

This archive provides an implementation to trace Elektrobit's OS_TRACE_STATE_TASK 
interface with Lauterbach's TRACE32 tools. It uses the AUTOSAR ARTI standard.

REQUIREMENTS:

- TRACE32 Version R2022-09 or higher


CONTENTS:

- readme.txt
  This file

- Dbg.h
  Header file mapping the OS hooks to ARTI hooks

- gen_eb_rte_hook.py
  Python script to generate RTE VFB Hook implementations

- ../../common
  Directory to be copied to your project

- ../../scripts
  Directory containing scripts to trace the ARTI hooks


QUICK GUIDE

1. Copy the the complete contents of the "common" directory and the "Dbg.h" 
   file into your project's subdirectory "source\stubs".

2. Read the readme.txt file in the "common" directory.

3. Edit the arti.h file and select your tracing method.

4. Edit the header file of the selected tracing method according to
   the readme.txt file in the appropriate subdirectory.

5. Enable OS tracing in your OS configuration:
   <project> -> ECU -> Os -> Os: Tab "OsOS": enable "OsTrace".
   Generate your project.

6. Copy the "gen_eb_rte_hook.py" Python script into the "util" directory and 
   edit it to adjust the paths to point to your Rte_Cfg.h file.

7. Run the "gen_eb_rte_hook.py" Python script to generate the RTE hook implementation
   "Rte_Hook_Arti.c" and Runnable declaration script "rte_runnable.cmm".

8. Make a clean build of your project.

9. **IMPORTANT** Edit the "output\generated\orti\os.orti" file:
   - In the "ENUM" of "RUNNINGTASK", shift the "NO_TASK" entry to the end of the list.
   - In the "ENUM" of "RUNNINGISR2", shift the "NO_ISR" entry to the end of the list.


