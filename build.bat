@echo off

WHERE cl.exe >nul 2>nul
IF %ERRORLEVEL% NEQ 0 call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

set commonCompilerFlags=/nologo /MT /GR- /EHsc /Od /Oi /FC /Zi /WX /W4 /IP:\Elementary\elementary\include
set files=..\elementary\src\elementary.cpp

IF NOT EXIST build\ mkdir build
pushd build

cl /c /Fo:elementary.obj %commonCompilerFlags% %files%
IF %ERRORLEVEL% EQU 0 lib /nologo /WX elementary.obj
IF %ERRORLEVEL% EQU 0 cl /Fe:sandbox.exe /Fo:sandbox.obj %commonCompilerFlags% ..\sandbox\src\main.cpp /link elementary.lib

IF %ERRORLEVEL% EQU 0 sandbox.exe

popd
