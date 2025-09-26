cmake_minimum_required(VERSION 4.0)
project(ASS_4_310)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ASS_4_310
        codingAssign4.cpp
        gradeBook.cpp
        gradeBook.h
        student.cpp
        student.h
)
