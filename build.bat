@echo off

WHERE cl.exe >nul 2>nul
IF %ERRORLEVEL% NEQ 0 call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

set commonCompilerFlags=/nologo /MT /GR- /EHsc /Od /Oi /FC /Zi /WX /W4 /IP:\Elementary\elementary\include /IP:\Elementary\deps\sdl2\include
set commonLinkerFlags=/LIBPATH:P:\Elementary\deps\sdl2\lib

set sdlLibs=sdl2.lib sdl2main.lib sdl2_image.lib sdl2_ttf.lib sdl2_mixer.lib
set elementaryFiles=..\elementary\src\elementary.cpp

IF NOT EXIST build\ mkdir build
pushd build

echo ----- Building Elementary -----
cl /c /Fo:elementary.obj %commonCompilerFlags% %elementaryFiles%
IF %ERRORLEVEL% EQU 0 lib /nologo /WX elementary.obj

echo.
echo ----- Building Sandbox -----
IF %ERRORLEVEL% EQU 0 cl /Fe:sandbox.exe /Fo:sandbox.obj %commonCompilerFlags% ..\sandbox\src\main.cpp /link %commonLinkerFlags% elementary.lib %sdlLibs%

echo.
echo ----- Output -----
IF %ERRORLEVEL% EQU 0 sandbox.exe

popd
