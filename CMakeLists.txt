cmake_minimum_required(VERSION 3.20)
project(ChessEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# El motor como librería
add_library(engine
    src/engine/Board.cpp
    src/engine/MoveGen.cpp
)
target_include_directories(engine PUBLIC include)

# Programa principal (consola por ahora)
add_executable(chess src/main.cpp)
target_link_libraries(chess PRIVATE engine)

# Tests
add_executable(perft_tests tests/perft_tests.cpp)
target_link_libraries(perft_tests PRIVATE engine)