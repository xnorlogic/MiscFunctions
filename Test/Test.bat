rem Run the executable
MiscFunctions.exe
echo off
rem check for the test results
IF %ERRORLEVEL% == 0 ( 
   echo Test suite completed and succeeded 
) ELSE ( echo Test suite completed and failed 
)