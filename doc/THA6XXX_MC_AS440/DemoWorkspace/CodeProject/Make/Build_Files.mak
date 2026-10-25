#****************************************************************************************************
#*   FileName              : Build_Files.mak
#*
#*   Platform              : AUTOSAR
#*
#*   Peripheral            : None
#*
#*   brief                 : This file contains source and header files needs to be build. 
#*                           This file is only a Demo for user and is not part of the production code
#*                           deliverables.
#*
#*   Autosar Version       : 4.4.0
#*
#*   Build Version         : Cortex-R52+/THA6xxx
#*
#*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
#*   All Rights Reserved.
#*
#****************************************************************************************************
#
#****************************************************************************************************
#**                          Revision Control History                                              **
#****************************************************************************************************
#*
# 
#*
#****************************************************************************************************

#****************************************************************************************************
# Define Platform and derivative, Default is THA6206
#****************************************************************************************************
ifeq ($(DERIVATIVE),)
    DERIVATIVE := THA6412
endif
PLATFORM := THA6

# Invoke shell to print the Platform and derivative used in the makefile
$(shell echo Running for $(DERIVATIVE) derivative, on $(PLATFORM) platform 1>&2)

ifeq ($(DERIVATIVE_SUB),)

else
$(shell echo Chip version is tha6206 D 1>&2)
endif


#****************************************************************************************************
# Define the source file and source file paths included in the Makefile
#****************************************************************************************************
SRC_DIRS = 
INCLUDE_DIRS = 

BSW_DIRS = $(TOP_PATH)\BSW
SDK_DIRS = $(TOP_PATH)\..\..\SDK
MCAL_DIRS = $(TOP_PATH)\..\..\Mcal
DEMO_DIRS = $(TOP_PATH)\DemoMcal

# Source files  dsadc msc  gipc

ifeq ($(DERIVATIVE),THA6412)
SRC_DIRS += $(DEMO_DIRS)\Config\THA6412_BGA516\src \
            $(MCAL_DIRS)\Code\Dsadc\src \
            $(MCAL_DIRS)\Code\Msc\src \
            $(SDK_DIRS)\msc\src \
            $(SDK_DIRS)\dsadc\src \
            $(SDK_DIRS)\gipc\src \
            $(SDK_DIRS)\fc\src \
            $(SDK_DIRS)\psi5\src \
            $(SDK_DIRS)\rdc\src \

INCLUDE_DIRS += $(DEMO_DIRS)\Config\THA6412_BGA516\include \
                $(MCAL_DIRS)\Code\Dsadc\include \
                $(MCAL_DIRS)\Code\Msc\include \
                $(SDK_DIRS)\dsadc\inc \
                $(SDK_DIRS)\msc\inc \
                $(SDK_DIRS)\gipc\inc \
                $(SDK_DIRS)\fc\inc \
                $(SDK_DIRS)\psi5\inc \
                $(SDK_DIRS)\rdc\inc \

else  ifeq ($(DERIVATIVE),THA6206)
SRC_DIRS += $(DEMO_DIRS)\Config\THA6206_LFBGA292\src \
            $(MCAL_DIRS)\Code\Dsadc\src \
            $(MCAL_DIRS)\Code\Msc\src \
            $(SDK_DIRS)\msc\src \
            $(SDK_DIRS)\dsadc\src \
            $(SDK_DIRS)\gipc\src \
            $(SDK_DIRS)\fc\src \
            $(SDK_DIRS)\rdc\src \
            
INCLUDE_DIRS += $(DEMO_DIRS)\Config\THA6206_LFBGA292\include \
                $(MCAL_DIRS)\Code\Dsadc\include \
                $(MCAL_DIRS)\Code\Msc\include \
                $(SDK_DIRS)\dsadc\inc \
                $(SDK_DIRS)\msc\inc \
                $(SDK_DIRS)\gipc\inc \
                $(SDK_DIRS)\fc\inc \
                $(SDK_DIRS)\rdc\inc \

else
SRC_DIRS += $(DEMO_DIRS)\Config\THA610X_LFBGA180\src 
INCLUDE_DIRS += $(DEMO_DIRS)\Config\THA610X_LFBGA180\include 
endif


SRC_DIRS += $(TOP_PATH) \
    $(BSW_DIRS)\CanIf \
    $(BSW_DIRS)\Dem\src \
    $(BSW_DIRS)\Det\src \
    $(BSW_DIRS)\EcuM \
    $(BSW_DIRS)\EthIf \
    $(BSW_DIRS)\EthTrcv \
    $(BSW_DIRS)\EthSwt \
    $(BSW_DIRS)\LinIf \
    $(BSW_DIRS)\SchM\src \
    $(DEMO_DIRS)\Demo_Adc \
    $(DEMO_DIRS)\Demo_App \
    $(DEMO_DIRS)\Demo_Can \
    $(DEMO_DIRS)\Demo_Common \
    $(DEMO_DIRS)\Demo_Dio \
    $(DEMO_DIRS)\Demo_Dma \
    $(DEMO_DIRS)\Demo_Dsadc \
    $(DEMO_DIRS)\Demo_Eth \
    $(DEMO_DIRS)\Demo_Fee \
    $(DEMO_DIRS)\Demo_Fls \
    $(DEMO_DIRS)\Demo_Gpt \
    $(DEMO_DIRS)\Demo_I2c \
    $(DEMO_DIRS)\Demo_Icu \
    $(DEMO_DIRS)\Demo_Intc \
    $(DEMO_DIRS)\Demo_Iom \
    $(DEMO_DIRS)\Demo_Lin \
    $(DEMO_DIRS)\Demo_Mcu \
    $(DEMO_DIRS)\Demo_Msc \
    $(DEMO_DIRS)\Demo_Ocu \
    $(DEMO_DIRS)\Demo_Port \
    $(DEMO_DIRS)\Demo_Pwm \
    $(DEMO_DIRS)\Demo_Sent \
    $(DEMO_DIRS)\Demo_Spi \
    $(DEMO_DIRS)\Demo_Uart \
    $(DEMO_DIRS)\Demo_Wdg \
    $(MCAL_DIRS)\Code\Adc\src \
    $(MCAL_DIRS)\Code\Can\src \
    $(MCAL_DIRS)\Code\Dio\src \
    $(MCAL_DIRS)\Code\Dma\src \
    $(MCAL_DIRS)\Code\Eth\src \
    $(MCAL_DIRS)\Code\Fee\src \
    $(MCAL_DIRS)\Code\Fls\src \
    $(MCAL_DIRS)\Code\Gpt\src \
    $(MCAL_DIRS)\Code\I2c\src \
    $(MCAL_DIRS)\Code\Icu\src \
    $(MCAL_DIRS)\Code\Intc\src \
    $(MCAL_DIRS)\Code\Iom\src \
    $(MCAL_DIRS)\Code\Lin\src \
    $(MCAL_DIRS)\Code\Mcall\src \
    $(MCAL_DIRS)\Code\Mcu\src \
    $(MCAL_DIRS)\Code\Ocu\src \
    $(MCAL_DIRS)\Code\Port\src \
    $(MCAL_DIRS)\Code\Pwm\src \
    $(MCAL_DIRS)\Code\Sent\src \
    $(MCAL_DIRS)\Code\Spi\src \
    $(MCAL_DIRS)\Code\Uart\src \
    $(MCAL_DIRS)\Code\Wdg\src \
    $(SDK_DIRS)\asi\src \
    $(SDK_DIRS)\basetimer\src \
    $(SDK_DIRS)\can\src \
    $(SDK_DIRS)\core\src \
    $(SDK_DIRS)\cpuwdt\src \
    $(SDK_DIRS)\dma\src \
    $(SDK_DIRS)\espi\src \
    $(SDK_DIRS)\eth\src \
    $(SDK_DIRS)\firewall\src \
    $(SDK_DIRS)\flash\src \
    $(SDK_DIRS)\gtm\common\timebase \
    $(SDK_DIRS)\gtm\common\trig \
    $(SDK_DIRS)\gtm\icu \
    $(SDK_DIRS)\gtm\ocu \
    $(SDK_DIRS)\gtm\pwm \
    $(SDK_DIRS)\gtm\std\atom \
    $(SDK_DIRS)\gtm\std\tbu \
    $(SDK_DIRS)\gtm\std\tim \
    $(SDK_DIRS)\gtm\std\tio \
    $(SDK_DIRS)\gtm\std\tom \
    $(SDK_DIRS)\gtm\timer \
    $(SDK_DIRS)\i2c\src \
    $(SDK_DIRS)\intc\src \
    $(SDK_DIRS)\iom\src \
    $(SDK_DIRS)\port\src \
    $(SDK_DIRS)\pwrc\src \
    $(SDK_DIRS)\rcc\src \
    $(SDK_DIRS)\itmu\src \
    $(SDK_DIRS)\sac\src \
    $(SDK_DIRS)\safewdt\src \
    $(SDK_DIRS)\saradc\src \
    $(SDK_DIRS)\sent\src \
    $(SDK_DIRS)\sicc\src \
    $(SDK_DIRS)\stm\src \
    $(SDK_DIRS)\ovc\src \
    $(SDK_DIRS)\gmu\src \
    $(SDK_DIRS)\ecrc\src \
    $(SDK_DIRS)\busprot\src \
    $(SDK_DIRS)\es\src \
    $(SDK_DIRS)\exti\src \
    $(SDK_DIRS)\tsensor\src \
    $(TOP_PATH)\Startup \







# Header files
INCLUDE_DIRS += \
    $(BSW_DIRS)\CanIf \
    $(BSW_DIRS)\Dem\include \
    $(BSW_DIRS)\Det\include \
    $(BSW_DIRS)\EcuM \
    $(BSW_DIRS)\EthIf \
    $(BSW_DIRS)\EthTrcv \
    $(BSW_DIRS)\LinIf \
    $(BSW_DIRS)\MemIf \
    $(BSW_DIRS)\SchM\include \
    $(BSW_DIRS)\WdgIf \
    $(BSW_DIRS)\EthSwt \
    $(DEMO_DIRS)\Demo_Adc \
    $(DEMO_DIRS)\Demo_App \
    $(DEMO_DIRS)\Demo_Can \
    $(DEMO_DIRS)\Demo_Common \
    $(DEMO_DIRS)\Demo_Dio \
    $(DEMO_DIRS)\Demo_Dma \
    $(DEMO_DIRS)\Demo_Dsadc \
    $(DEMO_DIRS)\Demo_Eth \
    $(DEMO_DIRS)\Demo_Fee \
    $(DEMO_DIRS)\Demo_Fls \
    $(DEMO_DIRS)\Demo_Gpt \
    $(DEMO_DIRS)\Demo_I2c \
    $(DEMO_DIRS)\Demo_Icu \
    $(DEMO_DIRS)\Demo_Intc \
    $(DEMO_DIRS)\Demo_Iom \
    $(DEMO_DIRS)\Demo_Lin \
    $(DEMO_DIRS)\Demo_Mcu \
    $(DEMO_DIRS)\Demo_Msc \
    $(DEMO_DIRS)\Demo_Ocu \
    $(DEMO_DIRS)\Demo_Port \
    $(DEMO_DIRS)\Demo_Pwm \
    $(DEMO_DIRS)\Demo_Sent \
    $(DEMO_DIRS)\Demo_Spi \
    $(DEMO_DIRS)\Demo_Uart \
    $(DEMO_DIRS)\Demo_Wdg \
    $(MCAL_DIRS)\Code\Adc\include \
    $(MCAL_DIRS)\Code\Can\include \
    $(MCAL_DIRS)\Code\Dio\include \
    $(MCAL_DIRS)\Code\Dma\include \
    $(MCAL_DIRS)\Code\Eth\include \
    $(MCAL_DIRS)\Code\Fee\include \
    $(MCAL_DIRS)\Code\Fls\include \
    $(MCAL_DIRS)\Code\Gpt\include \
    $(MCAL_DIRS)\Code\I2c\include \
    $(MCAL_DIRS)\Code\Icu\include \
    $(MCAL_DIRS)\Code\Intc\include \
    $(MCAL_DIRS)\Code\Iom\include \
    $(MCAL_DIRS)\Code\Lin\include \
    $(MCAL_DIRS)\Code\Mcall\include \
    $(MCAL_DIRS)\Code\Mcu\include \
    $(MCAL_DIRS)\Code\Ocu\include \
    $(MCAL_DIRS)\Code\Port\include \
    $(MCAL_DIRS)\Code\Pwm\include \
    $(MCAL_DIRS)\Code\Sent\include \
    $(MCAL_DIRS)\Code\Spi\include \
    $(MCAL_DIRS)\Code\Uart\include \
    $(MCAL_DIRS)\Code\Wdg\include \
    $(SDK_DIRS)\asi\inc \
    $(SDK_DIRS)\basetimer\inc \
    $(SDK_DIRS)\can\inc \
    $(SDK_DIRS)\core\inc \
    $(SDK_DIRS)\cpuwdt\inc \
    $(SDK_DIRS)\dma\inc \
    $(SDK_DIRS)\espi\inc \
    $(SDK_DIRS)\eth\inc \
    $(SDK_DIRS)\firewall\inc \
    $(SDK_DIRS)\flash\inc \
    $(SDK_DIRS)\gtm\common \
    $(SDK_DIRS)\gtm\common\timebase \
    $(SDK_DIRS)\gtm\common\trig \
    $(SDK_DIRS)\gtm\icu \
    $(SDK_DIRS)\gtm\inc \
    $(SDK_DIRS)\gtm\ocu \
    $(SDK_DIRS)\gtm\pwm \
    $(SDK_DIRS)\gtm\std\atom \
    $(SDK_DIRS)\gtm\std\cmu \
    $(SDK_DIRS)\gtm\std\tbu \
    $(SDK_DIRS)\gtm\std\tim \
    $(SDK_DIRS)\gtm\std\tio \
    $(SDK_DIRS)\gtm\std\tom \
    $(SDK_DIRS)\gtm\timer \
    $(SDK_DIRS)\i2c\inc \
    $(SDK_DIRS)\intc\inc \
    $(SDK_DIRS)\iom\inc \
    $(SDK_DIRS)\platform\compiler \
    $(SDK_DIRS)\platform\common \
    $(SDK_DIRS)\port\inc \
    $(SDK_DIRS)\pwrc\inc \
    $(SDK_DIRS)\rcc\inc \
    $(SDK_DIRS)\sac\inc \
    $(SDK_DIRS)\safewdt\inc \
    $(SDK_DIRS)\saradc\inc \
    $(SDK_DIRS)\sent\inc \
    $(SDK_DIRS)\itmu\inc \
    $(SDK_DIRS)\sicc\inc \
    $(SDK_DIRS)\ovc\inc \
    $(SDK_DIRS)\stm\inc \
    $(SDK_DIRS)\gmu\inc \
    $(SDK_DIRS)\busprot\inc \
    $(SDK_DIRS)\ecrc\inc \
    $(SDK_DIRS)\es\inc \
    $(SDK_DIRS)\exti\inc \
    $(SDK_DIRS)\tsensor\inc \
    $(TOP_PATH)\CommonFile\include \
    $(TOP_PATH)\CommonFile\include \
    $(TOP_PATH)\CommonFile\Memmap \
    $(TOP_PATH)\Startup \


#****************************************************************************************************
# Set path to find the .c and .s files
#****************************************************************************************************
vpath %.c $(addsuffix :, $(SRC_DIRS))
vpath %.C $(addsuffix :, $(SRC_DIRS))
SOURCE_FILES = $(foreach DIR,$(SRC_DIRS),$(notdir $(wildcard $(DIR)/*.c)))

OUT_FILES = $(patsubst %.c,$(BUILD_PATH)/%.o, ${SOURCE_FILES})
WIN_OUT_FILES = $(subst /,\,$(OUT_FILES))
