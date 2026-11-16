@echo off
setlocal

cd /d "%~dp0"

echo ========================================
echo          RAYTRACER - RELEASE
echo ========================================

echo.
echo [1/2] Configuration CMake...

cmake --preset windows-vcpkg
if errorlevel 1 goto error

echo.
echo [2/2] Compilation Release...

cmake --build --preset windows-release --parallel
if errorlevel 1 goto error

echo.
echo Run raytracer in Release...

build\Release\raytracer.exe 1920 1080

goto end

:error
echo.
echo An error occurs.
pause
exit /b 1

:end
endlocal