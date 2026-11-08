@echo off
rem Copyright (c) 2026 Skitzelles - part of Game Vault, https://github.com/skitzellez/xbox-game-vault
rem Packs and signs Flycast for Game Vault: package_gv.bat <version> -> dist\FlycastForGameVault_<version>_x64.appx
rem (as upstream's uwp.yml: the built .msix unpacked, the Release DLLs added, packed again, signed with our key)
setlocal
cd /d "%~dp0"
if "%~1"=="" (echo usage: package_gv.bat 0.1.0.x & exit /b 1)
set SDK=C:\Program Files (x86)\Windows Kits\10\bin\10.0.26100.0\x64
set GV=%~dp0..\wt-gv-naomidat\GameVault
set PKG=build-uwp\AppPackages\flycast\flycast_%~1_x64_Test
if not exist "%PKG%\flycast_%~1_x64.msix" (echo no %PKG%\flycast_%~1_x64.msix & exit /b 1)
if exist stage rmdir /s /q stage
"%SDK%\makeappx.exe" unpack /o /p "%PKG%\flycast_%~1_x64.msix" /d stage || exit /b 1
copy /y build-uwp\Release\*.dll stage\ >nul
del /q stage\AppxSignature.p7x stage\AppxBlockMap.xml stage\[Content_Types].xml 2>nul
if not exist dist mkdir dist
"%SDK%\makeappx.exe" pack /o /d stage /p dist\FlycastForGameVault_%~1_x64.appx || exit /b 1
if not defined PFX_PASSWORD for /f "usebackq delims=" %%p in (`powershell -NoProfile -ExecutionPolicy Bypass -File "%GV%\pfx_password.ps1"`) do set "PFX_PASSWORD=%%p"
if not defined PFX_PASSWORD (echo password could not be read & exit /b 1)
"%SDK%\signtool.exe" sign /fd SHA256 /a /f "%GV%\cert\GameVault.pfx" /p %PFX_PASSWORD% dist\FlycastForGameVault_%~1_x64.appx || exit /b 1
rmdir /s /q stage
echo Package ready: dist\FlycastForGameVault_%~1_x64.appx
