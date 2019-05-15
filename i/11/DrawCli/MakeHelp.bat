@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by DRAWCLI.HPJ. >"hlp\DrawCli.hm"
echo. >>"hlp\DrawCli.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\DrawCli.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\DrawCli.hm"
echo. >>"hlp\DrawCli.hm"
echo // Prompts (IDP_*) >>"hlp\DrawCli.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\DrawCli.hm"
echo. >>"hlp\DrawCli.hm"
echo // Resources (IDR_*) >>"hlp\DrawCli.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\DrawCli.hm"
echo. >>"hlp\DrawCli.hm"
echo // Dialogs (IDD_*) >>"hlp\DrawCli.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\DrawCli.hm"
echo. >>"hlp\DrawCli.hm"
echo // Frame Controls (IDW_*) >>"hlp\DrawCli.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\DrawCli.hm"
REM -- Make help for Project DRAWCLI


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\DrawCli.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\DrawCli.hlp" goto :Error
if not exist "hlp\DrawCli.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\DrawCli.hlp" Debug
if exist Debug\nul copy "hlp\DrawCli.cnt" Debug
if exist Release\nul copy "hlp\DrawCli.hlp" Release
if exist Release\nul copy "hlp\DrawCli.cnt" Release
echo.
goto :done

:Error
echo hlp\DrawCli.hpj(1) : error: Problem encountered creating help file

:done
echo.
