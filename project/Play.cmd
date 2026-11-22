@echo off
setlocal
cd /d "%~dp0"
set "EXE="
rem Candidate (b9c88175e + reward private batch + kill-stall capture gate) is
rem validated for: real dungeon kills keep the simulation advancing, idle
rem reward capture no longer re-serializes the region every frame, and a real
rem 1->2 level-up completes and persists. Still unverified: dynamic spawn
rem queue hard bound/backpressure, full regression (two pre-existing
rem order-dependent dnf_tests checkpoints fail with or without this change).
if exist "%~dp0..\checkpoints\build\dnf_native.exe" set "EXE=%CD%\..\checkpoints\build\dnf_native.exe"
if not defined EXE if exist "%~dp0..\temp-project-dir\b9c-baseline-build\dnf_native.exe" set "EXE=%CD%\..\temp-project-dir\b9c-baseline-build\dnf_native.exe"
if not defined EXE (
    echo No runnable executable found. Build checkpoints\build or restore the baseline build.
    pause
    exit /b 1
)
rem Skill lab: every source ACTIVE skill of the job is unlocked, MP and
rem cooldown are ignored, and F1/F2 page through the hotbar. Drop the flag to
rem play the normal traced chain only.
"%EXE%" --content-profile "%~dp0content-profile.json" --save-dir "%~dp0saves\refactor" --unlock-all-skills %*
set "dnf_exit=%errorlevel%"
if not "%dnf_exit%"=="0" pause
exit /b %dnf_exit%
