cmake_minimum_required(VERSION 3.17)
project(3des_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(3des_cpp
        main.cpp
        cli/Parser.cpp cli/Parser.h
        3des/Sequence.cpp 3des/Sequence.h
        3des/SequenceD.h 3des/Permutation.h 3des/KeyGen.cpp 3des/KeyGen.h 3des/SequenceD.cpp)
