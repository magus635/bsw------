#****************************************************************************************************
#*   FileName              : Build_Config_Ads.mak
#*
#*   Platform              : AUTOSAR
#*
#*   Peripheral            : None
#*
#*   brief                 : This file contains makefile build toolchain for IAR. 
#*                           This file is only a Demo for user and is not part of the production code
#*                           deliverables.
#*
#*   Autosar Version       : 4.2.2
#*
#*   Build Version         : Cortex-R52+/THA6xxx
#*
#*   Copyright (c) 2021, Beijing Tongxin Microelectroics Co., Ltd.
#*   All Rights Reserved.
#*
#****************************************************************************************************
#
#****************************************************************************************************
#**                          Revision Control History                                              **
#****************************************************************************************************
#*
#*   V1.0.0:  28-Nov-2024 : Create for Tasking toolchain
#*
#****************************************************************************************************
#****************************************************************************************************
#* Update ARM tool chain path that has been installed correctly
#****************************************************************************************************
# Do not change there path when you build project via "Build.bat"
# Update these paths, when you use Tasking toolchain and these paths are incorrect
ifeq ($(TASKING_DIR),)
    TASKING_DIR := C:\Program Files\TASKING\Arm v7.1r1\carm\bin
    $(shell echo Default Tasking selected: $(TASKING_DIR) 1>&2)
endif
FLOATTYPE :=--fpu=neon-fp-armv8

# Linker files
ifeq ($(DERIVATIVE),THA6412)
    LINKER_FILE := LinkerTaskingPfTha6412.lsl
    DEFCHIP :=THA6_THA6412
else  ifeq ($(DERIVATIVE),THA6206)
    LINKER_FILE := LinkerTaskingPf.lsl
    DEFCHIP :=THA6_THA6206
    ifeq ($(DERIVATIVE_SUB),)

	else
		DEFCHIP :=THA6_THA6206D
	endif

else
	LINKER_FILE := LinkerTaskingPfTha6104.lsl
	DEFCHIP :=THA6_THA6104
	FLOATTYPE :=--fpu=VFPv3-sp

endif

#****************************************************************************************************
# Tasking toolchain build directive
#****************************************************************************************************
CC := $(TASKING_DIR)\ccarm.exe
LD := $(TASKING_DIR)\lkarm.exe

CFLAGS = \
	--cpu=ARMv8R \
	--iso=99 \
	-t \
	--endianness=little \
	--fp-model=cFrz \
	-g3 \
	-W1 \
	-D$(DEFCHIP) \
	--control-flow-info \
	--language=+gcc,-volatile,+strings,-kanji \
	$(FLOATTYPE) \
	--optimize=0 \
	-DAUTOSAR_OS_NOT_USED \
	--source \
	# --misrac=1.1,1.2,1.3,2.1,2.2,2.3,2.4,2.5,2.6,2.7,3.1,3.2,4.1,4.2,5.1,5.2,5.3,5.4,5.5,5.6,5.7,5.8,5.9,6.1,6.2,7.1,7.2,7.3,7.4,8.1,8.2,8.3,8.4,8.5,8.6,8.7,8.8,8.9,8.10,8.11,8.12,8.13,8.14,9.1,9.2,9.3,9.4,9.5,10.1,10.2,10.3,10.4,10.5,10.6,10.7,10.8,11.1,11.2,11.3,11.4,11.5,11.6,11.7,11.8,11.9,12.1,12.2,12.3,12.4,12.5,13.1,13.2,13.3,13.4,13.5,13.6,14.1,14.2,14.3,14.4,15.1,15.2,15.3,15.4,15.5,15.6,15.7,16.1,16.2,16.3,16.4,16.5,16.6,16.7,17.1,17.2,17.3,17.4,17.5,17.6,17.7,17.8,18.1,18.2,18.3,18.4,18.5,18.6,18.7,18.8,19.1,19.2,20.1,20.2,20.3,20.4,20.5,20.6,20.7,20.8,20.9,20.10,20.11,20.12,20.13,20.14,21.1,21.2,21.3,21.4,21.5,21.6,21.7,21.8,21.9,21.10,21.11,21.12,21.13,21.14,21.15,21.16,21.17,21.18,21.19,21.20 \
	# --misrac-version=2012 \
	# --misrac-mandatory-warnings	\
	# --misrac-required-warnings	\
	# --misrac-advisory-warnings	\




LDFLAGS = \
	--cpu=ARMv8R	\
	--map-file	\
	-t \
    -O0    \
	--user-provided-initialization-code \
	--chip-output=$(TARGET):BIN \
	--output=$(HEXFILE):IHEX:4 \
	--output=$(ELFFILE):ELF \
	--map-file=$(MAPFILE).mapxml:XML \
	--hex-format=S \
	-d$(LINKER_PATH)\$(LINKER_FILE) \
	-lcarm -lfparm -lrtarm	\
	-mq	\
	# -OtZxycL \

# Link file rule
$(TARGET) : $(OUT_FILES)  
	@$(LD) -o $(TARGET) $(OUT_FILES) $(LDFLAGS)

# C file build rule.
$(BUILD_PATH)/%.o : %.c
	@$(CC) $(CFLAGS) $(addprefix -I, $(INCLUDE_DIRS)) -c -o $@ $<
