gcc -Wextra -Wall -Wvla -lm ./TreeAnalyzer.c -o TreeAnalyzer
cp ./TreeAnalyzer ./ex2_test/TEST/TreeAnalyzer

valgrind --leak-check=full --show-leak-kinds=all ./TreeAnalyzer ex2_test/TEST/tests/in/test_static/long_one_sided/long_one_sided.txt 0 7

echo "-------"
echo "\n"

valgrind --leak-check=full --show-leak-kinds=all ./TreeAnalyzer ex2_test/TEST/tests/in/test_static/same_node_route/same_node_route.txt 0 7
same_node_route.txt 0 0
