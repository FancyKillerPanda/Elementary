@echo off

IF [%1]==[--clang] (
	pushd build-clang
) ELSE (
	pushd build
)

IF EXIST release\ (
	pushd release
) ELSE (
	pushd debug
)

sandbox.exe

popd
popd
