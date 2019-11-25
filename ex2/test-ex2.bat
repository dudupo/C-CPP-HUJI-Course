gcc -Wextra -Wall -Wvla -lm .\TreeAnalyzer.c -o TreeAnalyzer.exe
move TreeAnalyzer.exe .\ex2_test\TEST\TreeAnalyzer.exe
cd .\ex2_test\TEST
.\run_tester.bat
cd ..\..\
