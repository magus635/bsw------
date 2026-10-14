OpenERIKA with TRACE32 Trace over ARTI Hooks.

This archive provides an implementation to trace OpenERIKA with Lauterbach's TRACE32 tools.

This implementation is based on OpenErika version OE5

REQUIREMENTS:

- OpenErika/OpenDruid version OE5
- TRACE32 Version R2026-09 or higher

CONTENTS:

- readme.txt
  This file

- gencode
  Directory with Arti interface to OpenErika

- ../../common
  Directory to be copied to your project


QUICK GUIDE

1.  Activate ARTI within OpenDruid and generate the OS within OpenDruid.

2.  Copy the the contents of the "gencode" folder into the generated 
    "out/Arti/gencode" folder, overwriting the existing files.
    NOTE: this folder will be overwritten every time you generate the OS!

3.  Create a "trace32/Arti" directory within your project.

4.  Copy the the complete contents of the "common" directory into the newly created
    "trace32/Arti" folder.

5.  Read the "readme.txt" file in the "trace32/Arti" directory.

6.  Edit the "arti.h" file:
    - Select your tracing method.

7.  (Re-)Build the application.
