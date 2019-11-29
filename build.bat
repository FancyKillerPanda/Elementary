@echo off

WHERE cl.exe >nul 2>nul
IF %ERRORLEVEL% NEQ 0 call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

set commonCompilerFlags=/nologo /MT /GR- /EHsc /Od /Oi /FC /Zi /WX /W4 /wd4100 /DELEMENTARY_DEBUG /DELEMENTARY_WIN32 /IP:\Elementary\elementary\include /IP:\Elementary\deps\sdl2\include
set commonLinkerFlags=/subsystem:console /LIBPATH:P:\Elementary\deps\sdl2\lib

set sdlLibs=sdl2.lib sdl2main.lib sdl2_image.lib sdl2_ttf.lib sdl2_mixer.lib

set elemSrcDir=..\..\elementary\src
set elementaryFiles=%elemSrcDir%\*.cpp %elemSrcDir%\utils\*.cpp %elemSrcDir%\gfx\*.cpp %elemSrcDir%\audio\*.cpp %elemSrcDir%\animations\*.cpp
set elementaryObjectFiles=elementary.obj log.obj init.obj window.obj texture.obj text.obj menu.obj console_colour.obj random.obj input_text.obj sound.obj music.obj animation.obj fade.obj scale.obj translate.obj

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

echo.
echo ----- Building Sandbox -----
cl /Fe:sandbox.exe /Fo:sandbox.obj %commonCompilerFlags% ..\sandbox\src\main.cpp /link %commonLinkerFlags% elementary.lib %sdlLibs%
IF %ERRORLEVEL% NEQ 0 (
	popd
	goto :eof
)

echo.
echo ----- Output -----
sandbox.exe

popd
