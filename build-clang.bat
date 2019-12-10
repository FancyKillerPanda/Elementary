@echo off

set ORIGINAL_DIRECTORY=%CD%

set linkSdlLibs=-lsdl2.lib -lsdl2main.lib -lsdl2_image.lib -lsdl2_ttf.lib -lsdl2_mixer.lib

set elemSrcDir=..\..\..\elementary\src
set elementaryFiles=%elemSrcDir%\utils\*.cpp %elemSrcDir%\gfx\*.cpp %elemSrcDir%\audio\*.cpp %elemSrcDir%\animations\*.cpp
set elementaryObjFiles=elementary-int\*.o

set debugReleaseDir=debug
set debugReleaseFlags=-O0 -g
set elementaryOutputName=elementary-d.lib

for %%A in (%*) do (
	if [%%A]==[--unity] (
		set elementaryFiles=%elemSrcDir%\unity_build.cpp
		set elementaryObjFiles=elementary-int\unity_build.o
	)

	if [%%A]==[--release] (
		set debugReleaseDir=release
		set debugReleaseFlags=-O3
		set elementaryOutputName=elementary.lib
	)
)

set commonCompilerFlags=-Wall -Werror -Wno-pragma-pack -Wno-reorder %debugReleaseFlags% -DELEMENTARY_DEBUG -DELEMENTARY_WIN32 -IP:\Elementary\elementary\include\elementary -IP:\Elementary\deps\sdl2\include
set sandboxLinkerFlags=--for-linker=-subsystem:console -LP:\Elementary\deps\sdl2\lib %linkSdlLibs% -l%elementaryOutputName%

rem Cleans build directory
call clean.bat --clang --%debugReleaseDir%

IF NOT EXIST build-clang\ mkdir build-clang
pushd build-clang
IF NOT EXIST %debugReleaseDir%\ mkdir %debugReleaseDir%
pushd %debugReleaseDir%

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

llvm-ar rc %elementaryOutputName% %elementaryObjFiles%
IF %ERRORLEVEL% NEQ 0 (
	echo.
	echo Build [91mFailed[0m: Elementary ^(Link^)
	cd %ORIGINAL_DIRECTORY%
	goto :eof
)

echo Build [92mSuceeded[0m: Elementary

clang++ -osandbox.exe %commonCompilerFlags% ..\..\sandbox\src\main.cpp %sandboxLinkerFlags%
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
popd
