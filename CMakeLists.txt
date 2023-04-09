cmake_minimum_required(VERSION 3.24)
project(chess_ai)

set(CMAKE_CXX_STANDARD 23)
set(SFML_DIR "/opt/homebrew/opt/sfml")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(chess_ai main.cpp)

target_link_libraries(chess_ai sfml-graphics sfml-audio)

