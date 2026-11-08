@echo off
rem ASCII only, CRLF line endings. cmd.exe reads batch files with the OEM code
rem page, so UTF-8 text in a .cmd file corrupts the parser and breaks the
rem surrounding if-blocks. Keep every byte here in the ASCII range.
rem The real launcher is tools\play_skill_preview.py: it locates the built
rem executable across cache\*-build directories and forwards every argument.
setlocal
cd /d "%~dp0"
set "EXITCODE=0"

where python >nul 2>nul
if errorlevel 1 goto :fallback

python -X utf8 -B "tools\play_skill_preview.py" %*
set "EXITCODE=%errorlevel%"
rem 9009 means "command not found": a Microsoft Store python stub or a broken
rem install can answer where.exe but still refuse to run, so fall back.
if "%EXITCODE%"=="9009" goto :fallback
goto :done

:fallback
set "EXE="
if exist "..\checkpoints\build\dnf_skill_previewer.exe" set "EXE=%CD%\..\checkpoints\build\dnf_skill_previewer.exe"
if not defined EXE if exist "cache\refactor-build\dnf_skill_previewer.exe" set "EXE=%CD%\cache\refactor-build\dnf_skill_previewer.exe"
if not defined EXE if exist "cache\skill-previewer-build\dnf_skill_previewer.exe" set "EXE=%CD%\cache\skill-previewer-build\dnf_skill_previewer.exe"
if not defined EXE goto :nobuild
"%EXE%" --content-profile "%CD%\content-profile.json" --report-dir "%CD%\reports\skill-previewer" %*
set "EXITCODE=%errorlevel%"
goto :done

:nobuild
echo [skill-previewer] No usable python and no built previewer.
echo [skill-previewer] Build it first:
echo     python tools\build.py --build-dir ..\checkpoints\build
set "EXITCODE=1"

:done
if not "%EXITCODE%"=="0" pause
exit /b %EXITCODE%
