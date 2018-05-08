cmake_minimum_required(VERSION 2.8.4)

PROJECT(SERVER)

set (CMAKE_MODULE_PATH ${SERVER_SOURCE_DIR}/CMake)

CMAKE_POLICY(SET CMP0045 OLD)

SET(CMAKE_CXX_FLAGS " -Wall -std=c++0x -fno-omit-frame-pointer -o0 -g")
#SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -D_DEBUG -DDEBUG -O0 -g -Werror -Wno-unused -Wno-unused-function -Wno-unused-variable -Wno-invalid-offsetof -Wno-sign-compare ")
#SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -D_DEBUG -DDEBUG -DDNA_LIVE_ENV -O1 -g -Werror -Wno-unused -Wno-unused-function -Wno-unused-variable -Wno-invalid-offsetof -Wno-sign-compare ")

SET(EXECUTABLE_OUTPUT_PATH ${SERVER_BINARY_DIR}/bin)

MESSAGE(STATUS "Server Bin path: ${SERVER_BINARY_DIR}")
MESSAGE(STATUS "Exe path: ${EXECUTABLE_OUTPUT_PATH}")
MESSAGE(STATUS "Src path: ${SERVER_SOURCE_DIR}")

INCLUDE_DIRECTORIES(${SERVER_SOURCE_DIR}/common )

#LINK_DIRECTORIES(...lib)

ADD_SUBDIRECTORY(test)
