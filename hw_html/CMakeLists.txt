cmake_minimum_required(VERSION 3.0)
project(hw_html CXX)
add_definitions(-g)
add_executable(${PROJECT_NAME} html.cpp main.cpp mcubase.cpp bit.cpp
    mcureg.cpp instance.cpp var.cpp memory.cpp)
add_library(xmlParser xmlParser/xmlParser.cpp)
add_subdirectory(CTML)
target_include_directories(xmlParser PUBLIC xmlParser)
target_link_libraries(${PROJECT_NAME} PRIVATE xmlParser CTML)
target_include_directories(${PROJECT_NAME} PRIVATE .)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -std=c++17)
