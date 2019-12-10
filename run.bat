@echo off

IF [%1]==[--clang] (
	pushd build-clang
) ELSE (
	pushd build
)

sandbox.exe
popd
