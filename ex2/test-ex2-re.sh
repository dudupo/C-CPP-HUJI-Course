gcc -Wextra -Wall -Wvla -lm ./TreeAnalyzer.c -o TreeAnalyzer
cp ./TreeAnalyzer ./ex2_test/TEST/TreeAnalyzer
#cd ./ex2_test/TEST
#python3 ./c_ex2_tester.py > log 
cd ./tests 
python3 -m pytest ./tester.py
cd ../
