@echo off

IF NOT EXIST build\ goto :eof
pushd build

rem Deletes intermediate directories
RMDIR /S /Q elementary-int >nul 2>nul
RMDIR /S /Q sandbox-int >nul 2>nul

rem Deletes output files
del elementary.lib >nul 2>nul
del sandbox.exe >nul 2>nul

popd
