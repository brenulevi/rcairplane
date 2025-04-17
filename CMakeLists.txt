cmake_minimum_required(VERSION 3.18)

project(rcairplane)
set(CMAKE_CXX_STANDARD 17)

add_executable(plane
    src/main.cpp
    src/gpio.cpp
)

target_include_directories(plane PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(plane
    pthread
    rt
    pigpiod_if2
    rf24
)