@echo off
rem Double-click entry point: opens the skill previewer built into checkpoints\build.
setlocal
cd /d "%~dp0"
call "project\Play-Skill-Preview.cmd" %*
exit /b %errorlevel%
