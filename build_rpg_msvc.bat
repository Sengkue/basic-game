@echo off
echo Building Advanced RPG Game with Visual Studio Compiler...
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
    echo Please install Visual Studio or use build_rpg.bat with MinGW
    pause
    exit /b 1
)

:: Compile the RPG game
cl /EHsc /std:c++17 /O2 rpg.cpp /Fe:rpg.exe

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
