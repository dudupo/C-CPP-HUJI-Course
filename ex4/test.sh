# -Wall -Wvla -Wextra -Werror -g
# g++  -g  -std=c++17 test.cpp -o test
# ./test.exe

mingw32-make
./mlpnetwork.exe parameters/w1 parameters/w2 parameters/w3 parameters/w4 parameters/b1 parameters/b2 parameters/b3 parameters/b4
