@echo off
setlocal
cd /d "%~dp0"
if not exist "cache\refactor-build\dnf_native.exe" (
    echo No refactor executable. Run Build-And-Test.cmd first.
    pause
    exit /b 1
)
"cache\refactor-build\dnf_native.exe" --content-profile "%~dp0content-profile.json" --save-dir "%~dp0saves\refactor" %*
set "dnf_exit=%errorlevel%"
if not "%dnf_exit%"=="0" pause
exit /b %dnf_exit%
