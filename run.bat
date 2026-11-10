@echo off
cmake -S . -B build
if errorlevel 1 exit /b 1

cmake --build build
if errorlevel 1 exit /b 1

build\Debug\raytracer.exe 1920 1080