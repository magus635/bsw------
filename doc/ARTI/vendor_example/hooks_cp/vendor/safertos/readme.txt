SaveRTOS with TRACE32 Trace over ARTI Hooks

This archive provides an implementation to trace SafeRTOS with Lauterbach's TRACE32 tools.
It uses the ASAM ARTI standard.

This implementation is tested with SafeRTOS_GCC_STM32H723_EVAL_v9.3.1.


REQUIREMENTS:

- TRACE32 Version R2022-09 or higher


CONTENTS:

- readme.txt
  This file

- patch_safertostrace.py
  Python script to patch the SafeRTOS source code, adding ARTI hooks.

- ../../common
  Directory to be copied to your project

- ../../scripts
  Directory containing scripts to trace the ARTI hooks


QUICK GUIDE

1.  Copy the the complete contents of the "common" directory into the 
    "SafeRTOS" directory (alongside "kernel"), and rename it to "arti".

2.  Copy the "patch_safertostrace.py" file into the "SafeRTOS" directory.

3.  Open a terminal in the "SafeRTOS" directory and run the "patch_safertostrace.py"
    Python script.

4.  Read the "readme.txt" file in the new "arti" directory.

5.  Edit the "arti.h" file:
    - Comment the "ARTI_AUTOSAR" definition and uncomment the "ARTI_ASAM" definition
    - Select your tracing method.

6.  Edit the header file of the selected tracing method according to
    the "readme.txt" file in the appropriate subdirectory.

7.  Add "arti.c" file in the new "arti" directory to your build environment.

8.  Make a clean build of your project.

9.  Load the FreeRTOS Awareness in your TRACE32 project script (see pdf/rtos_freertos.pdf)
    and add "TASK.Option TRACEID ID".

10. Enable ARTI tracing, see the script (in folder "cmm_scripts")
    appropriate for the selected tracing method.
