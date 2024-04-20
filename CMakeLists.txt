cmake_minimum_required(VERSION 3.23)
project(labwork_8_IgorM27)

set(CMAKE_CXX_STANDARD 17)

include_directories(CCircularBuffer/inc)
include_directories(CCircularBufferExt/inc)
link_directories(CCircularBufferExt)
add_executable(labwork_8_IgorM27
        main.cpp)
enable_testing()
add_subdirectory(tests)

