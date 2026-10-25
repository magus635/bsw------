#****************************************************************************************************
#*   FileName			 : makefile
#*
#*   Platform			 : AUTOSAR
#*
#*   Peripheral			 : None
#*
#*   brief				 : This file contains makefile build tool for ADS, IAR and GHS. 
#*						   This file is only a Demo for user and is not part of the production code
#*						   deliverables.
#*
#*   Autosar Version	 : 4.4.0
#*
#*   Build Version		 : Cortex-R52+/THA6xxx
#*
#*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
#*   All Rights Reserved.
#*
#****************************************************************************************************
#
#****************************************************************************************************
#**						  Revision Control History								                   **
#****************************************************************************************************
#*
# 
# 
#*
#****************************************************************************************************

#****************************************************************************************************
# Define global variables
#****************************************************************************************************

# build log file
BUILD_LOG = None

#****************************************************************************************************
# Import and check the configuration
#****************************************************************************************************
# VAR_CFG_MAK_FILE := Make/

#****************************************************************************************************
# Compiler selected (Default is ads, Optional: ads, ghs, iar, tasking)
#****************************************************************************************************
ifeq ($(TOOLCHAIN),)
    TOOLCHAIN := ads
endif

#****************************************************************************************************
# Makefile top path
#****************************************************************************************************
TOP_PATH1 ?= $(dir $(lastword $(MAKEFILE_LIST)))
TOP_PATH2 ?= $(subst /,\,$(TOP_PATH1))
TOP_PATH := $(patsubst %\,%, $(TOP_PATH2))
# TOP_PATH = .

#****************************************************************************************************
# Toolchain choose
#****************************************************************************************************
# Invoke shell to print the toolchain used in the makefile
$(shell echo Using the $(TOOLCHAIN) toolchain for make 1>&2)

#****************************************************************************************************
# Path conversion utilities
#****************************************************************************************************
cmdpath = $(subst /,\,$(1))
mkpath = $(subst \,/,$(1))

#****************************************************************************************************
# Import the source file and source file paths included in the Makefile
#****************************************************************************************************
include $(call cmdpath, $(TOP_PATH)/Make/Build_Files.mak)

#****************************************************************************************************
# Define output directory
#****************************************************************************************************
# Debug output path
BUILD_PATH ?= $(TOP_PATH)\Debug
# Linker file path
LINKER_PATH ?= $(TOP_PATH)\LinkFiles\$(TOOLCHAIN)
# Output project name
OUTPUT_PRJ_N := $(DERIVATIVE)_Demo_Prj

ifeq ($(TOOLCHAIN),ads)
    # *.axf file only generate form ADS toolchain
    TARGET=$(BUILD_PATH)\$(OUTPUT_PRJ_N).axf
endif
ifeq ($(TOOLCHAIN),ghs)
    TARGET=$(BUILD_PATH)\$(OUTPUT_PRJ_N).elf
endif
ifeq ($(TOOLCHAIN),iar)
    TARGET=$(BUILD_PATH)\$(OUTPUT_PRJ_N).out
endif
ifeq ($(TOOLCHAIN),hightec)
    TARGET=$(BUILD_PATH)\$(OUTPUT_PRJ_N).elf
endif
ifeq ($(TOOLCHAIN),tasking)
    TARGET=$(BUILD_PATH)\$(OUTPUT_PRJ_N).abs
endif

BINARY=$(BUILD_PATH)\$(OUTPUT_PRJ_N).bin
HEXFILE=$(BUILD_PATH)\$(OUTPUT_PRJ_N).hex
MAPFILE=$(BUILD_PATH)\$(OUTPUT_PRJ_N).map
ASMFILE=$(BUILD_PATH)\$(OUTPUT_PRJ_N).asm
ELFFILE=$(BUILD_PATH)\$(OUTPUT_PRJ_N).elf


#****************************************************************************************************
# Import toolchain support directive
#****************************************************************************************************
include  $(call mkpath, $(TOP_PATH)/Make/$(TOOLCHAIN)/Build_Config_*.mak)

#****************************************************************************************************
# Directive
#****************************************************************************************************
.PHONY: build
build: $(TARGET)

.PHONY: clean
clean:
	del /f /q $(BUILD_PATH)\*
