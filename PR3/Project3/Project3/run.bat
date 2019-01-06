:run.bat

cd %~dp0
cd Debug
start ServerPrototype.exe
cd../
cd GUI/bin/x86/debug
start WpfApp1.exe 8081
start WpfApp1.exe 8082
cd ../../..
