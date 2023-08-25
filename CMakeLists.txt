cmake_minimum_required(VERSION 3.23)
project(Milestone1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Milestone1 ms3.cpp Utilities.h Station.h Station.cpp Utilities.cpp CustomerOrder.cpp CustomerOrder.h Workstation.h LineManager.h Workstation.cpp LineManager.cpp)
