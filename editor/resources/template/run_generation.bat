@echo off

pushd ..
premake5.exe --file="scripts\proj_solution_gen.lua" vs2022
popd