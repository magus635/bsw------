@REM ************************************************************************************************
@REM   FileName              : Build.bat
@REM 
@REM   Platform              : AUTOSAR
@REM 
@REM   Peripheral            : None
@REM 
@REM   brief                 : This bat script is used for build the MCAL Demo project .
@REM 
@REM   Autosar Version       : 4.4.0
@REM 
@REM   Build Version         : Cortex-R52+/THA6xxx
@REM 
@REM   Copyright (c) 2021, Beijing Tongxin Microelectroics Co., Ltd.
@REM   All Rights Reserved.
@REM 
@REM ************************************************************************************************
@REM 
@REM ************************************************************************************************
@REM                         Revision Control History                                              **
@REM ************************************************************************************************
@REM 
@REM V1.0.0:  30-Jun-2023 : (00863) Create for build project
@REM 
@REM ************************************************************************************************

@echo off

SET "folder=Debug"
IF NOT EXIST "%folder%" (
    mkdir "%folder%"
    echo Folder "%folder%" created.
)

@REM ******************************** EB tresos path ************************************************
set "EB_TRESOS_PATH=C:\Software\EB\tresos\bin"
@REM ******************************** ADS toolchain path ********************************************
set "ARM_CONFIG_PATH=C:\Program Files\ARM\Development Studio 2022.1\sw\ARMCompiler6.18\bin"
set "ARMLMD_LICENSE_FILE=29000@192.168.11.254"
set "ARM_PRODUCT_DEF=C:\Program Files\ARM\Development Studio 2022.1\sw\mappings\gold.elmap"
@REM ******************************** GHS toolchain path ********************************************
set "GHS_DIR=C:\ghs\comp_202314"
@REM ******************************** IAR toolchain path ********************************************
set "IAR_DIR=C:\Program Files\IAR Systems\Embedded Workbench 9.2 EWARM FS 9.50.3\arm\bin"
@REM ******************************** HighTec toolchain path ********************************************
set "HIGHTEC_DIR=C:\HighTec\toolchains\arm\v8.1.0\bin"
@REM ******************************** Tasking toolchain path ********************************************
set "TASKING_DIR=C:\Program Files\TASKING\Arm v7.1r1\carm\bin"
set "MAKE_DIR=C:\Program Files\ARM\Development Studio 2022.1\bin"

@REM ************************************************************************************************
@REM !!! DO NOT EDIT, set environment variable !!!
@REM ************************************************************************************************
@REM Clear the PATH environment variable. There are other compiler environment variables in PATH, 
@REM which may cause execution of other *.EXE with the same name, resulting in compilation errors
set PATH=

set "LocalDir=%~dp0"

set PATH=%MAKE_DIR%;%PATH%
if "%1"=="ads"           set PATH=%ARM_CONFIG_PATH%;%PATH%
if "%1"=="ghs"           set PATH=%GHS_DIR%;%PATH%
if "%1"=="iar"           set PATH=%IAR_DIR%;%PATH%
if "%1"=="hightec"       set PATH=%HIGHTEC_DIR%;%PATH%
if "%1"=="tasking"       set PATH=%TASKING_DIR%;%PATH%
set "RLM_LICENSE=192.168.110.27@5053"
setlocal enabledelayedexpansion
@REM ************************************************************************************************
@REM Get input argument
@REM ************************************************************************************************
if "%1"=="ads"       SET TOOLCHAIN=ads
if "%1"=="ghs"       SET TOOLCHAIN=ghs
if "%1"=="iar"       SET TOOLCHAIN=iar
if "%1"=="hightec"   SET TOOLCHAIN=hightec
if "%1"=="tasking"   SET TOOLCHAIN=tasking
if "%3"=="tha6206"   SET DERIVATIVE=THA6206
if "%3"=="tha6206d"  (
    SET DERIVATIVE=THA6206
    SET DERIVATIVE_SUB=THA6206D
)
if "%3"=="tha6206D"  (
    SET DERIVATIVE=THA6206
    SET DERIVATIVE_SUB=THA6206D
)    
if "%3"=="tha6412"   SET DERIVATIVE=THA6412
if "%3"=="tha6104"   SET DERIVATIVE=THA6104
if /i "%4"=="thumb" (
    SET DTHUMBEN=THUMB_ENABLE
    echo %DTHUMBEN%
) else (
    SET DTHUMBEN=THUMB_DISABLE
    echo %DTHUMBEN%
)

if "%1"=="-h"        goto HELP_FUNC
if "%1"=="--help"    goto HELP_FUNC
if "%2"=="-h"        goto HELP_FUNC
if "%2"=="--help"    goto HELP_FUNC
if "%2"=="clean"     goto CLEAN_FUNC
if "%2"=="make"      goto BUILD_FUNC
if "%2"=="build"     goto BUILD_FUNC
if "%2"=="rebuild"   goto CLEAN_AND_BUILD_FUNC


@REM Wrong argument input
echo Build.bat *** No rule to execute target "%1", refer to help for more information. ***
goto HELP_FUNC

@REM ************************************************************************************************
@REM Fucntion used to display the help information
@REM ************************************************************************************************
:HELP_FUNC
    echo.
    echo.
    echo    Usage: Build.bat [parameter1] [parameter2] [parameter3] [parameter4]
    echo.
    echo    parameter1 : toolchain: ads,ghs,iar,hightec,tasking
    echo    parameter2 : cmd: clean,make,build,rebuild
    echo    parameter3 : optional cmd: tha6206,tha6206D,tha6104,tha6412(default)
    echo    parameter4 : optional cmd: thumb, nothumb(default)
    echo.      
    echo    options: 
    echo        -h, --help    Print this help message
    echo        clean         clean project
    echo        make,build    make the project, default is ADS
    echo        ads           make project with ADS toolchain
    echo        ghs           make project with GHS toolchain
    echo        iar           make project with IAR toolchain
    echo        hightec       make project with hightec toolchain
    echo        tasking       make project with tasking toolchain
    echo        tha6206       make project for tha6206
    echo        tha6206D      make project for tha6206 D version
    echo        thumb         make project in thumb instruction set
    echo.
    echo.
goto END_FUNC


@REM ************************************************************************************************
@REM Function used to execute clean
@REM ************************************************************************************************
:CLEAN_FUNC

    @REM clean project
    make clean

goto END_FUNC

@REM ************************************************************************************************
@REM Function used to execute build
@REM ************************************************************************************************
:BUILD_FUNC
    @REM EB build 

    make -j12 -C ./ build
    @REM make project

goto MAKE_FUNC


@REM ************************************************************************************************
@REM Function used to execute clean and build
@REM ************************************************************************************************
:CLEAN_AND_BUILD_FUNC

    make clean
    @REM EB build 

    make -j12 -C ./ build
    @REM make project

goto MAKE_FUNC


@REM ************************************************************************************************
@REM Function used to execute make
@REM ************************************************************************************************
:MAKE_FUNC

    @REM make project with mutil-thread
    @REM make -j12 -C ./ all

    if errorlevel 1 (
        echo.
        echo === Build Failed ===
        echo.
        exit /b 1
    ) else (
        echo.
        echo === Build Succeeded ===
        echo.
        exit /b 0
    )

goto END_FUNC

:END_FUNC
@REM end the setlocal enabledelayedexpansion
endlocal
:end
