cls
echo off
gcc -c ..\Checks\MonotonicCheck.c -I ..\Checks  -o MonotonicCheck.o
gcc -c ..\Checks\CheckSumCalc.c -I ..\Checks -o CheckSumCalc.o
gcc -c ..\Test\TestSuite.c -I ..\Checks -o TestSuite.o
gcc TestSuite.o MonotonicCheck.o CheckSumCalc.o -o TestApp.exe
@echo Build Complete
rm TestSuite.o
rm MonotonicCheck.o
rm CheckSumCalc.o
@echo Perform Tests
rem Run the executable
TestApp.exe
echo off
rem check for the test results
IF %ERRORLEVEL% == 0 ( 
   echo Test suite completed and succeeded
) ELSE ( echo Test suite completed and failed )
rm TestApp.exe