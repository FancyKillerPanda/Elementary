@echo off

WHERE cl.exe >nul 2>nul
IF %ERRORLEVEL% NEQ 0 call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

set commonCompilerFlags=/nologo /MT /GR- /EHsc /Od /Oi /FC /Zi /WX /W4 /wd4100 /DELEMENTARY_DEBUG /DELEMENTARY_WIN32 /IP:\Elementary\elementary\include\elementary /IP:\Elementary\deps\sdl2\include
set commonLinkerFlags=/subsystem:console /LIBPATH:P:\Elementary\deps\sdl2\lib

set sdlLibs=sdl2.lib sdl2main.lib sdl2_image.lib sdl2_ttf.lib sdl2_mixer.lib

set elemSrcDir=..\..\elementary\src
set elementaryFiles=%elemSrcDir%\*.cpp %elemSrcDir%\utils\*.cpp %elemSrcDir%\gfx\*.cpp %elemSrcDir%\audio\*.cpp %elemSrcDir%\animations\*.cpp

IF NOT EXIST build\ mkdir build
pushd build

IF NOT EXIST elementary-int\ mkdir elementary-int
pushd elementary-int
echo ----- Building Elementary -----
cl /c %commonCompilerFlags% %elementaryFiles%
IF %ERRORLEVEL% NEQ 0 (
	popd
	popd
	goto :eof
)
popd

lib /nologo /WX /out:elementary.lib elementary-int\*.obj
IF %ERRORLEVEL% NEQ 0 (
	popd
	goto :eof
)

IF NOT EXIST sandbox-int\ mkdir sandbox-int
pushd sandbox-int
echo.
echo ----- Building Sandbox -----
cl /c /Fe:sandbox.exe /Fo:sandbox.obj %commonCompilerFlags% ..\..\sandbox\src\main.cpp
IF %ERRORLEVEL% NEQ 0 (
	popd
	popd
	goto :eof
)
popd

link /nologo /WX %commonLinkerFlags% sandbox-int\*.obj elementary.lib %sdlLibs%
IF %ERRORLEVEL% NEQ 0 (
	popd
	goto :eof
)

echo.
echo ----- Output -----
sandbox.exe

popd
