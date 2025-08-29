@echo off
echo Building Advanced RPG Game...
echo.

:: Check if g++ is available
where g++ >nul 2>&1
if %errorlevel% neq 0 (
    echo Error: g++ compiler not found!
    echo Please install MinGW-w64 or use build_rpg_msvc.bat for Visual Studio
    pause
    exit /b 1
)

:: Compile the RPG game
g++ -std=c++17 -Wall -Wextra -O2 -o rpg.exe rpg.cpp

if %errorlevel% equ 0 (
    echo.
    echo ✅ RPG Build successful!
    echo Executable created: rpg.exe
    echo.
    echo To play the game, type: rpg.exe
    pause
) else (
    echo.
    echo ❌ Build failed!
    echo Please check the error messages above.
    pause
    exit /b 1
)
