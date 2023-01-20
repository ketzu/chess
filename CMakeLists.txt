cmake_minimum_required(VERSION 3.17)
project(chess)

set(CMAKE_CXX_STANDARD 20)

add_executable(chess main.cpp engine/piece.cpp engine/piece.h engine/board.cpp engine/board.h engine/Move.cpp engine/Move.h)