cmake_minimum_required(VERSION 3.18)

project(rcairplane)
set(CMAKE_CXX_STANDARD 17)

add_executable(plane
    src/main.cpp

    src/gpio/raspgpio.cpp
    
    src/i2c/i2cbus.cpp
    src/i2c/i2cdevice.cpp

    src/modules/ads1115.cpp
    src/modules/servo.cpp

    src/plane/plane.cpp
    src/plane/lighting.cpp

    src/utils/utils.cpp
)

target_include_directories(plane PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_precompile_headers(plane PRIVATE
    ${CMAKE_SOURCE_DIR}/src/pch.h
)

target_link_libraries(plane
    pthread
    rt
    pigpiod_if2
    rf24
)