cmake_minimum_required(VERSION 3.3)
project(AffichageLaby)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(EXECUTABLE_NAME ${PROJECT_NAME})

file(GLOB SOURCES
        *.hpp
        *.cpp
        )
add_executable(${EXECUTABLE_NAME} ${SOURCES})

set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-audio)