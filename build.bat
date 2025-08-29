@echo off
echo Building C++ Game...
echo.

:: Check if g++ is available
where g++ >nul 2>&1
if %errorlevel% neq 0 (
    echo Error: g++ compiler not found!
    echo Please install MinGW-w64 or Visual Studio Build Tools
    pause
    exit /b 1
)

:: Compile the game
g++ -std=c++17 -Wall -Wextra -O2 -o game.exe game.cpp

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
