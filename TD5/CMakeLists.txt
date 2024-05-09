cmake_minimum_required(VERSION 3.5)

project(TD5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TD5 main.cpp genmatrix2x2f.h genmatrix2x2f.cpp point2f.h point2f.cpp diag2f.cpp diag2f.h rotation2f.cpp rotation2f.h)
