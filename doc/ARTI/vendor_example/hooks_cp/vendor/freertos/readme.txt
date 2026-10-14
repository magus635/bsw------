FreeRTOS with TRACE32 Trace over ARTI Hooks

This archive provides an implementation to trace FreeRTOS' hook interface with Lauterbach's TRACE32 tools.
It uses the ASAM ARTI standard.


REQUIREMENTS:

- TRACE32 Version R2022-09 or higher


CONTENTS:

- readme.txt
  This file.

- FreeRTOSARTI.h
  FreeRTOS ARTI hook configuration to be included in the global FreeRTOS configuration file (single core variant).

- FreeRTOSARTISMP.h
  FreeRTOS ARTI hook configuration to be included in the global FreeRTOS configuration file (SMP variant).
  This file is aligned to the official FreeRTOS SMP kernel. Custom SMP derivatives may need some adaption.

- ../../common
  Directory to be copied to your project.

- ../../scripts
  Directory containing scripts to trace the ARTI hooks.


QUICK GUIDE

1.  Copy the the complete contents of the "common" directory into your project.

2.  Read the "readme.txt" file in the "common" directory.

3.  Edit the "arti.h" file:
    - Comment the "ARTI_AUTOSAR" definition and uncomment the "ARTI_ASAM" definition
    - Select your tracing method.

4.  Edit the header file of the selected tracing method according to
    the "readme.txt" file in the appropriate subdirectory.

5.  When using FreeRTOS v9 or lower:
    Edit the "FreeRTOSARTI.h" or "FreeRTOSARTISMP.h" file and change the "pxContainer" member to "pvContainer".

6.  Edit the "FreeRTOSConfig.h" configuration file of your project
    - Include the "FreeRTOSARTI.h" file, if you are using a single core FreeRTOS project.
    - Include the "FreeRTOSARTISMP.h" file, if you are using an SMP FreeRTOS project.

7.  Add "arti.c" to your build environment.

8.  Make a clean build of your project.

9.  Load the FreeRTOS Awareness in your TRACE32 project script (see pdf/rtos_freertos.pdf)
    and add "TASK.Option TRACEID ID".

10. Enable ARTI tracing, see the script (in folder "cmm_scripts")
    appropriate for the selected tracing method.
