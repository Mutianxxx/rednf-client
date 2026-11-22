@echo off
setlocal
cd /d "%~dp0"
set "EXE="
if exist "..\checkpoints\build\dnf_native.exe" set "EXE=%CD%\..\checkpoints\build\dnf_native.exe"
if not defined EXE if exist "cache\combat-route-build\dnf_native.exe" set "EXE=%CD%\cache\combat-route-build\dnf_native.exe"
if not defined EXE if exist "cache\refactor-build\dnf_native.exe" set "EXE=%CD%\cache\refactor-build\dnf_native.exe"
if not defined EXE (
    echo No refactor executable. Run Build-And-Test.cmd first.
    pause
    exit /b 1
)
"%EXE%" --content-profile "%~dp0content-profile.json" --combat-preview %*
set "dnf_exit=%errorlevel%"
if not "%dnf_exit%"=="0" pause
exit /b %dnf_exit%
