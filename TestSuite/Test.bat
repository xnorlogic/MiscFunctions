cls
echo off
echo Test Suite for MiscFunctions has started...
rem Project architecture
SET APPLICATION_NAME=TestApp
SET FUNCTIONS_PATH=..\Functions
SET PLATFORM_PATH=..\Platform
SET TEST_PATH=..\Test
SET OBJECT_FILES=TestSuite.o MonotonicCheck.o CheckSumCalc.o Sort.o
rem Compile and build
gcc -c %FUNCTIONS_PATH%\MonotonicCheck.c -I %FUNCTIONS_PATH% -I %PLATFORM_PATH% -o MonotonicCheck.o
gcc -c %FUNCTIONS_PATH%\CheckSumCalc.c -I %FUNCTIONS_PATH% -I %PLATFORM_PATH% -o CheckSumCalc.o
gcc -c %FUNCTIONS_PATH%\Sort.c -I %FUNCTIONS_PATH% -I %PLATFORM_PATH% -o Sort.o
gcc -c %TEST_PATH%\TestSuite.c -I %FUNCTIONS_PATH% -I %PLATFORM_PATH% -o TestSuite.o
gcc %OBJECT_FILES% -o %APPLICATION_NAME%.exe
@echo Build Complete
rem cleanup
del TestSuite.o
del MonotonicCheck.o
del CheckSumCalc.o
del Sort.o
rem Test App execution
@echo Perform Tests
rem Run the executable
%APPLICATION_NAME%.exe
echo off
rem check for the test results
IF %ERRORLEVEL% == 0 ( 
   echo Test suite completed and succeeded
) ELSE ( echo Test suite completed and failed )
del TestApp.exe
