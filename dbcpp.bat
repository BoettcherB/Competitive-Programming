:: Add the directory containing this file to $PATH

@echo off

:: Make sure a task letter is provided 
if "%1"=="" (
    echo Usage: %0 task
    exit /b 1
)

set CPPFILE=%1.cpp
set EXEFILE=a.exe
set INPUTFILE=%~dp0in.txt

:: Compile the C++ file
echo Compiling...
g++ -g -Wall -Wextra --std=c++17 -DDB_LOCAL %CPPFILE% -o %EXEFILE%

:: Check that the compilation was successful
if %ERRORLEVEL% NEQ 0 (
    echo Compilation failed.
    exit /b %ERRORLEVEL%
)
echo Compilation Successful

:: Run gdb to debug the program
echo Running...
echo --------------------------
gdb .\a.exe -ex "run"
