gcc -Wextra -Wall -Wvla -lm ./TreeAnalyzer.c -o TreeAnalyzer 
valgrind --leak-check=full --show-leak-kinds=all ./TreeAnalyzer ex2_test/TEST/tests/in/test_static/long_one_sided/long_one_sided.txt 0 7
