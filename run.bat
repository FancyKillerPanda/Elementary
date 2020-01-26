@echo off

set debugReleaseDir=debug
set toolchainDir=build

for %%A in (%*) do (
	if [%%A]==[--clang] (
		set toolchainDir=build-clang
	)

	if [%%A]==[--release] (
		set debugReleaseDir=release
	)
)

pushd %toolchainDir%\%debugReleaseDir%
sandbox.exe
popd
