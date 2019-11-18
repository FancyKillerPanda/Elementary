@echo off

set compilerFlags=/nologo /Fo:elementary.obj /MT /GR- /EHsc /Od /Oi /FC /Zi /WX /W4 /IP:\Elementry\src
set files=..\src\elementary.cpp

WHERE cl.exe >nul 2>nul
IF %ERRORLEVEL% NEQ 0 call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

IF NOT EXIST build\ mkdir build
pushd build

cl /c %compilerFlags% %files%
lib /nologo /WX elementary.obj

popd
