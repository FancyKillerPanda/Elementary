@echo off

set linkSdlLibs=-lsdl2.lib -lsdl2main.lib -lsdl2_image.lib -lsdl2_ttf.lib -lsdl2_mixer.lib

set commonCompilerFlags=-Wall -Werror -Wno-pragma-pack -Wno-reorder -DELEMENTARY_DEBUG -DELEMENTARY_WIN32 -IP:\Elementary\elementary\include\elementary -IP:\Elementary\deps\sdl2\include
set sandboxLinkerFlags=--for-linker=-subsystem:console -LP:\Elementary\deps\sdl2\lib %linkSdlLibs% -lelementary.lib

set elemSrcDir=..\..\elementary\src
set elementaryFiles=%elemSrcDir%\*.cpp %elemSrcDir%\utils\*.cpp %elemSrcDir%\gfx\*.cpp %elemSrcDir%\audio\*.cpp %elemSrcDir%\animations\*.cpp

IF NOT EXIST build-clang\ mkdir build-clang
pushd build-clang

IF NOT EXIST elementary-int\ mkdir elementary-int
pushd elementary-int
echo ----- Building Elementary -----
clang++ -c %commonCompilerFlags% %elementaryFiles%
IF %ERRORLEVEL% NEQ 0 (
	popd
	popd
	goto :eof
)
popd

llvm-ar rc elementary.lib elementary-int\*.o
IF %ERRORLEVEL% NEQ 0 (
	popd
	goto :eof
)

echo.
echo ----- Building Sandbox -----
clang++ -osandbox.exe %commonCompilerFlags% ..\sandbox\src\main.cpp %sandboxLinkerFlags%
IF %ERRORLEVEL% NEQ 0 (
	popd
	goto :eof
)

echo.
echo ----- Output -----
sandbox.exe

popd
