ETAS RTA-OS with TRACE32 Trace over ARTI Hooks

This archive provides an implementation to trace ETAS' RTA-OS hook
interface with Lauterbach's TRACE32 tools. It uses the AUTOSAR ARTI standard.

REQUIREMENTS:

- TRACE32 Version R2020-09 or higher


CONTENTS:

- readme.txt
  This file

- gen_etas_rte_hook.py
  Python script to generate RTE VFB Tracing Hook implementations

- arti_etas_rtaos_singlecore.c, arti_etas_rtaos_multicore.c
  Source file mapping the OS hooks to ARTI hooks

- ../../common
  Directory to be copied to your project

- ../../scripts
  Directory containing scripts to trace the ARTI hooks


QUICK GUIDE

1. Copy the the complete contents of the "common" directory into your project.

2. Read the readme.txt file in the "common" directory.

3. Edit the arti.h file and select your tracing method.

4. Edit the header file of the selected tracing method according to
   the readme.txt file in the appropriate subdirectory.

5. Edit the "gen_etas_rte_hook.py" file and adjust the paths to point
   to your Rte_Hook.h file.

6. Run the "gen_etas_rte_hook.py" Python script to generate the RTE hook implementation
   "Rte_Hook_Arti.c" and Runnable declaration script "rte_runnable.cmm".

7. Add "arti.c", "Rte_Hook_Arti.c" to your build environment.

8. Copy and add "arti_etas_rtaos_singlecore.c" or "arti_etas_rtaos_multicore.c.c"
   to your build environment, depending if you have a single-core or multi-core OS.

9. Configure your RTA-OS:
   - Enable "Pre-Task Hook", "Post-Task Hook"
   - Enable "Addtional Task Hooks", "Task Activation Hook", "Task Termination Hook"
   - Enable "Additional ISR Hooks"
   - Enable "ORTI/Lauterbach", "ORTI Stack Fill", "ORTI/SMP"

10. Make a clean build of your project.

11. If you use a multi-core OS, edit the ORTI file:
    In the "ENUM" of "RUNNINGISR2", add a comma after the "NO_ISR" entry and add the line:
      "CROSSCORE_ISR" = "1"
    (You can also use the "orti_with_crosscore_isr.py" script to do this.)

12. Include the generated "rte_runnable.cmm" script to your TRACE32 startup script.
