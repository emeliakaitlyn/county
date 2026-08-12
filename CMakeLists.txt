cmake_minimum_required(VERSION 3.20)
project(CounterApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(CounterApp WIN32
    src/main.cpp
)

target_link_libraries(CounterApp PRIVATE user32 gdi32 comctl32)

target_compile_definitions(CounterApp PRIVATE UNICODE _UNICODE)
