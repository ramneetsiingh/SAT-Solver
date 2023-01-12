cmake_minimum_required(VERSION 2.8.12)

project(pa2)

if (EXISTS "${CMAKE_SOURCE_DIR}/minisat")
  add_subdirectory(minisat)
else()
  message (FATAL_ERROR "MiniSat not found. Use `git clone https://github.com/agurfinkel/minisat` to check it out.")
endif()

# enable c++11 support
set (CMAKE_CXX_FLAGS "-std=c++11 -Wall -g ${CMAKE_CXX_FLAGS}")

# expose minisat header files
include_directories(${CMAKE_SOURCE_DIR}/minisat)

# create the main executable
## change .cpp files if needed
add_executable(${PROJECT_NAME} main.cc Lexer.cc Parser.cc ASTree.cc SATSolver.cc Tseitin.cc)
# link MiniSAT libraries
target_link_libraries(${PROJECT_NAME} minisat-lib-static)