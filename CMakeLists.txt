cmake_minimum_required(VERSION 3.10)
project(network_analyzer C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

add_executable(network_analyzer
    src/main.c
    src/banner.c
    src/capture.c
    src/dns_handler.c
)

target_include_directories(network_analyzer PRIVATE include)
target_compile_options(network_analyzer PRIVATE -Wall -Wextra)
