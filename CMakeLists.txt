cmake_minimum_required(VERSION 3.7)
project(socketBank)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES server/server.cpp server/postMsg.cpp server/postMsg.h include/error.h include/error.cpp)
add_executable(socketBank ${SOURCE_FILES})
