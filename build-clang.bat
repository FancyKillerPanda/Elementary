@echo off

set ORIGINAL_DIRECTORY=%CD%

set linkSdlLibs=-lsdl2.lib -lsdl2main.lib -lsdl2_image.lib -lsdl2_ttf.lib -lsdl2_mixer.lib

set commonCompilerFlags=-Wall -Werror -Wno-pragma-pack -Wno-reorder -DELEMENTARY_DEBUG -DELEMENTARY_WIN32 -IP:\Elementary\elementary\include\elementary -IP:\Elementary\deps\sdl2\include
set sandboxLinkerFlags=--for-linker=-subsystem:console -LP:\Elementary\deps\sdl2\lib %linkSdlLibs% -lelementary.lib

set elemSrcDir=..\..\elementary\src
set elementaryFiles=%elemSrcDir%\*.cpp %elemSrcDir%\utils\*.cpp %elemSrcDir%\gfx\*.cpp %elemSrcDir%\audio\*.cpp %elemSrcDir%\animations\*.cpp
set elementaryObjFiles=elementary-int\*.o

REM NOTE(fkp): Unity build only
IF [%1]==[--unity] (
	set elementaryFiles=%elemSrcDir%\unity_build.cpp
	set elementaryObjFiles=elementary-int\unity_build.o
)

IF NOT EXIST build-clang\ mkdir build-clang
pushd build-clang

IF NOT EXIST elementary-int\ mkdir elementary-int
pushd elementary-int
clang++ -c %commonCompilerFlags% %elementaryFiles%
IF %ERRORLEVEL% NEQ 0 (
	echo.
	echo Build [91mFailed[0m: Elementary ^(Compile^)
	cd %ORIGINAL_DIRECTORY%
	goto :eof
)
popd

llvm-ar rc elementary.lib %elementaryObjFiles%
IF %ERRORLEVEL% NEQ 0 (
	echo.
	echo Build [91mFailed[0m: Elementary ^(Link^)
	cd %ORIGINAL_DIRECTORY%
	goto :eof
)

echo Build [92mSuceeded[0m: Elementary

clang++ -osandbox.exe %commonCompilerFlags% ..\sandbox\src\main.cpp %sandboxLinkerFlags%
IF %ERRORLEVEL% NEQ 0 (
	echo.
	echo Build [91mFailed[0m: Sandbox
	cd %ORIGINAL_DIRECTORY%
	goto :eof
)

echo Build [92mSuceeded[0m: Sandbox

echo.
sandbox.exe

popd
