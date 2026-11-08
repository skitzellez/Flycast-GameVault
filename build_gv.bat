@echo off
rem Copyright (c) 2026 Skitzelles - part of Game Vault, https://github.com/skitzellez/xbox-game-vault
rem Builds Flycast for Game Vault (Xbox, UWP x64): build_gv.bat <version, e.g. 0.1.0.1> > build-uwp.log
cd /d "%~dp0"
if "%~1"=="" (echo usage: build_gv.bat 0.1.0.x & exit /b 1)
cmake -B build-uwp -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 17 2022" -A x64 -DCMAKE_SYSTEM_NAME=WindowsStore -DCMAKE_SYSTEM_VERSION=10.0.26100.0 -DGV_VERSION=%~1 || exit /b 1
cmake --build build-uwp --config Release -- /m || exit /b 1
