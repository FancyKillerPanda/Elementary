@echo off

IF NOT [%1]==[--clang] call :Clean build
IF NOT [%1]==[--msvc] call :Clean build-clang
exit /B 0

:Clean
IF NOT EXIST %~1\ exit /B 1
pushd %~1

rem Deletes intermediate directories
rmdir /S /Q */elementary-int >nul 2>nul
rmdir /S /Q */sandbox-int >nul 2>nul

rem Deletes output files
del */elementary.lib >nul 2>nul
del */sandbox.exe >nul 2>nul

popd
exit /B 0
