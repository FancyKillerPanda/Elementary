@echo off

rem Cleans build directory
call clean.bat --msvc

set ORIGINAL_DIRECTORY=%CD%

WHERE cl.exe >nul 2>nul
IF %ERRORLEVEL% NEQ 0 call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

set sdlLibs=sdl2.lib sdl2main.lib sdl2_image.lib sdl2_ttf.lib sdl2_mixer.lib

set elemSrcDir=..\..\..\elementary\src
set elementaryFiles=%elemSrcDir%\utils\*.cpp %elemSrcDir%\gfx\*.cpp %elemSrcDir%\audio\*.cpp %elemSrcDir%\animations\*.cpp
set elementaryObjFiles=elementary-int\*.obj

set debugReleaseDir=debug
set debugReleaseFlags=/Od

for %%A in (%*) do (
	if [%%A]==[--unity] (
		set elementaryFiles=%elemSrcDir%\unity_build.cpp
		set elementaryObjFiles=elementary-int\unity_build.obj
	)

	if [%%A]==[--release] (
		set debugReleaseDir=release
		set debugReleaseFlags=/O2 /Ob3
	)
)

set commonCompilerFlags=/nologo /MT /GR- /EHsc /Oi /FC /Zi /WX /W4 /wd4100 %debugReleaseFlags% /DELEMENTARY_DEBUG /DELEMENTARY_WIN32 /IP:\Elementary\elementary\include\elementary /IP:\Elementary\deps\sdl2\include
set commonLinkerFlags=/subsystem:console /LIBPATH:P:\Elementary\deps\sdl2\lib

IF NOT EXIST build\ mkdir build
pushd build
IF NOT EXIST %debugReleaseDir%\ mkdir %debugReleaseDir%
pushd %debugReleaseDir%

IF NOT EXIST elementary-int\ mkdir elementary-int
pushd elementary-int
cl /c %commonCompilerFlags% %elementaryFiles%
IF %ERRORLEVEL% NEQ 0 (
	echo.
	echo Build [91mFailed[0m: Elementary ^(Compile^)
	cd %ORIGINAL_DIRECTORY%
	goto :eof
)
popd

lib /nologo /WX /out:elementary.lib %elementaryObjFiles%
IF %ERRORLEVEL% NEQ 0 (
	echo.
	echo Build [91mFailed[0m: Elementary ^(Link^)
	cd %ORIGINAL_DIRECTORY%
	goto :eof
)

echo Build [92mSuceeded[0m: Elementary
echo.

IF NOT EXIST sandbox-int\ mkdir sandbox-int
pushd sandbox-int
cl /c /Fe:sandbox.exe /Fo:sandbox.obj %commonCompilerFlags% ..\..\..\sandbox\src\main.cpp
IF %ERRORLEVEL% NEQ 0 (
	echo.
	echo Build [91mFailed[0m: Sandbox ^(Compile^)
	cd %ORIGINAL_DIRECTORY%
	goto :eof
)
popd

link /nologo /WX %commonLinkerFlags% sandbox-int\*.obj elementary.lib %sdlLibs%
IF %ERRORLEVEL% NEQ 0 (
	echo.
	echo Build [91mFailed[0m: Sandbox ^(Link^)
	cd %ORIGINAL_DIRECTORY%
	goto :eof
)

echo Build [92mSuceeded[0m: Sandbox
echo.

sandbox.exe

popd
popd
