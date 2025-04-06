cmake_minimum_required(VERSION 3.10)
project(Stockfish LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Quell-Dateien im src Verzeichnis
file(GLOB SOURCES "src/*.cpp")

add_executable(Stockfish ${SOURCES})