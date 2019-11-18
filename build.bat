@echo off

WHERE cl.exe >nul 2>nul
IF %ERRORLEVEL% NEQ 0 call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

set commonCompilerFlags=/nologo /MT /GR- /EHsc /Od /Oi /FC /Zi /WX /W4 /IP:\Elementary\elementary\include /IP:\Elementary\deps\sdl2\include
set commonLinkerFlags=/LIBPATH:P:\Elementary\deps\sdl2\lib

set sdlLibs=sdl2.lib sdl2main.lib sdl2_image.lib sdl2_ttf.lib sdl2_mixer.lib
set elementaryFiles=..\elementary\src\elementary.cpp ..\elementary\src\utils\log.cpp
set elementaryObjectFiles=elementary.obj log.obj

IF NOT EXIST build\ mkdir build
pushd build

echo ----- Building Elementary -----
cl /c %commonCompilerFlags% %elementaryFiles%
IF %ERRORLEVEL% NEQ 0 (
	popd
	goto :eof
)
lib /nologo /WX %elementaryObjectFiles%

echo.
echo ----- Building Sandbox -----
IF %ERRORLEVEL% NEQ 0 (
	popd
	goto :eof
)
cl /Fe:sandbox.exe /Fo:sandbox.obj %commonCompilerFlags% ..\sandbox\src\main.cpp /link %commonLinkerFlags% elementary.lib %sdlLibs%

echo.
echo ----- Output -----
IF %ERRORLEVEL% NEQ 0 (
	popd
	goto :eof
)
sandbox.exe

popd
