@echo off
echo Building C++ Game with Visual Studio Compiler...
echo.

:: Try to find and setup Visual Studio environment
call "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat" 2>nul
if %errorlevel% neq 0 (
    call "%ProgramFiles%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" 2>nul
)
if %errorlevel% neq 0 (
    call "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars64.bat" 2>nul
)
if %errorlevel% neq 0 (
    call "%ProgramFiles%\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat" 2>nul
)

:: Check if cl is available now
where cl >nul 2>&1
if %errorlevel% neq 0 (
    echo Error: Visual Studio C++ compiler not found!
    echo.
    echo Please install one of the following:
    echo 1. Visual Studio Community ^(free^): https://visualstudio.microsoft.com/vs/community/
    echo 2. Visual Studio Build Tools: https://visualstudio.microsoft.com/downloads/
    echo 3. MinGW-w64: https://www.mingw-w64.org/downloads/
    echo.
    echo Make sure to include "C++ build tools" during installation.
    pause
    exit /b 1
)

:: Compile the game
cl /EHsc /std:c++17 /O2 game.cpp /Fe:game.exe

if %errorlevel% equ 0 (
    echo.
    echo ✅ Build successful!
    echo Executable created: game.exe
    echo.
    echo To run the game, type: game.exe
    pause
) else (
    echo.
    echo ❌ Build failed!
    echo Please check the error messages above.
    pause
    exit /b 1
)
