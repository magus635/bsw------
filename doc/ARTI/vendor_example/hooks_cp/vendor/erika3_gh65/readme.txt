Erika3 with TRACE32 Trace over ARTI Hooks.
This archive provides an implementation to trace Erika3 with Lauterbach's TRACE32 tools.
Depending on the method used to record the ARTI Hooks, you need to include the necessary files from ~~\demo\kernel\arti\hooks_cp\common. 
Afterward, you must select the appropriate trace and compiler for your environment in arti.h file.

This implementation is tested with Erika3_gh65

REQUIREMENTS:

- TRACE32 Version R2022-09 or higher

CONTENTS:

- readme.txt
  This file

- patch_erika3_gh65.patch
  Patch file to patch the Erika3gh65 source code, adding ARTI hooks.

- ../../common
  Directory to be copied to your project


QUICK GUIDE

1.  Copy the "patch_erika3_gh65.patch" file into the "Erika3" directory:
    e.g. eclipse-rtdruid3-photon-win32-x86_64_20190524_gh65\eclipse\plugins\com.eu.evidence.ee3_3.0.1.20190524_gh65\ee_files\pkg

2.  Open a terminal in the "Erika3" directory and run the "patch_erika3_gh65.patch" patch script.
    e.g. patch -p1 < patch_erika3_gh65.patch

3.  Copy common\arti.h, common\arti_common.h and *all subfolders* of "common" 
    to your application's source folder, e.g. com.eu.evidence.ee3_3.0.1.20190524_gh65\ee_files\pkg\arch\tricore

4.  Read the "readme.txt" file in the "common" directory.

5.  Edit the "arti.h" file:
    - Select your tracing method.

6.  Modify the paths of included files in the ee_pull.mk file to exclusively incorporate the script associated with the selected tracing method.
    e.g. OS_EE_PULL_SRC_FILES += $(ERIKA_FILES)/pkg/arch/tricore/common/arti_t32_tc3xx_olda_tasking/arti_t32_tc3xx_olda_tasking.h

7.  Make a clean build of your project.

8.  Load the ORTI file in your TRACE32 project script (see pdf/rtos_orti.pdf)