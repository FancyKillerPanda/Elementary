@echo off

set cleanCompiler=msvc
set cleanDir=debug

for %%A in (%*) do (
	IF [%%A]==[--clang] (
		set cleanCompiler=clang
	)

	IF [%%A]==[--release] (
		set cleanDir=release
	)
)

IF %cleanCompiler%==msvc (
	call :Clean build
) ELSE (
	call :Clean build-clang
)
exit /B 0

:Clean
IF NOT EXIST %~1\ exit /B 1
pushd %~1
IF NOT EXIST %cleanDir%\ exit /B 1
pushd %cleanDir%

rem Deletes intermediate directories
rmdir /S /Q elementary-int >nul 2>nul
rmdir /S /Q sandbox-int >nul 2>nul

rem Deletes output files
del elementary.lib >nul 2>nul
del sandbox.exe >nul 2>nul

popd
popd
exit /B 0
