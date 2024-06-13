:: Add the directory containing this file to $PATH

@echo off

:: Make sure a C++ file is provided 
if "%1"=="" (
    echo Usage: %0 cppfile.cpp
    exit /b 1
)

set CPPFILE=%1
set EXEFILE=a.exe
set INPUTFILE=%~dp0in.txt

:: Compile the C++ file
echo Compiling...
g++ -Wall -Wextra --std=c++17 -DDB_LOCAL %CPPFILE% -o %EXEFILE%

:: Check that the compilation was successful
if %ERRORLEVEL% NEQ 0 (
    echo Compilation failed.
    exit /b %ERRORLEVEL%
)
echo Compilation Successful

:: Run the C++ executable with input from INPUTFILE
echo Running...
echo --------------------------
type %INPUTFILE% | .\%EXEFILE%

:: clean up the executable
del %EXEFILE%
