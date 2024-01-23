@echo off

pushd ..
premake\Windows\premake5.exe --file=build.lua vs2022
popd
pause
