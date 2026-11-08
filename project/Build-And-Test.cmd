@echo off
setlocal
cd /d "%~dp0"
call build.cmd --test %*
set "dnf_exit=%errorlevel%"
if not "%dnf_exit%"=="0" pause
exit /b %dnf_exit%
