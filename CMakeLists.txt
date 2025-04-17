cmake_minimum_required(VERSION 3.18)

project(rcairplane)
set(CMAKE_CXX_STANDARD 17)

add_executable(plane
    src/plane/main.cpp
)

target_include_directories(plane PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(plane
    pthread
    rt
    pigpio
    rf24
)

add_executable(control
    src/control/main.cpp
)

target_link_libraries(control
    pthread
    rt
    pigpio
    rf24
)