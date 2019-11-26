gcc -Wextra -Wall -Wvla -lm ./TreeAnalyzer.c -o TreeAnalyzer
mv ./TreeAnalyzer ./ex2_test/TEST/TreeAnalyzer
cd ./ex2_test/TEST
python3 ./c_ex2_tester.py 
