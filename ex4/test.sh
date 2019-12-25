# -Wall -Wvla -Wextra -Werror -g
g++  -g  -std=c++17 test.cpp -o test
./test
#--leak-check=full .
#make
#./mlpnetwork
#(valgrind --leak-check=full  ./mlpnetwork parameters/w1 parameters/w2 parameters/w3 parameters/w4 parameters/b1 parameters/b2 parameters/b3 parameters/b4 < ./inp2.txt )> ./log
#


