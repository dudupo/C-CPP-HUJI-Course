cmake_minimum_required(VERSION 3.13)
project(ex4)
set(CMAKE_CXX_STANDARD 14)
add_executable(mlpnetwork main.cpp MlpNetwork.cpp Dense.cpp Activation.cpp Matrix.cpp  )