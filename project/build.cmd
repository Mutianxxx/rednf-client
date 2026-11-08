@echo off
setlocal
cd /d "%~dp0"
set "TEMP=%~dp0cache\build-tmp"
set "TMP=%TEMP%"
set "TMPDIR=%TEMP%"
if not exist "%TEMP%" mkdir "%TEMP%"
"D:\ProgramData\anaconda3\python.exe" -X utf8 -B tools\build.py %*
exit /b %errorlevel%
