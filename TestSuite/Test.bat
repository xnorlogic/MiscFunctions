cls
echo off
rem Compile and build
gcc -c ..\Functions\MonotonicCheck.c -I ..\Functions  -o MonotonicCheck.o
gcc -c ..\Functions\CheckSumCalc.c -I ..\Functions -o CheckSumCalc.o
gcc -c ..\Test\TestSuite.c -I ..\Functions -o TestSuite.o
gcc TestSuite.o MonotonicCheck.o CheckSumCalc.o -o TestApp.exe
@echo Build Complete
rem cleanup
rm TestSuite.o
rm MonotonicCheck.o
rm CheckSumCalc.o
rem Test App execution
@echo Perform Tests
rem Run the executable
TestApp.exe
echo off
rem check for the test results
IF %ERRORLEVEL% == 0 ( 
   echo Test suite completed and succeeded
) ELSE ( echo Test suite completed and failed )
rm TestApp.exe