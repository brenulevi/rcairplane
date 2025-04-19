cmake_minimum_required(VERSION 3.18)

project(rcairplane)
set(CMAKE_CXX_STANDARD 17)

add_executable(plane
    src/main.cpp
    src/raspgpio.cpp
    
    src/i2c/i2cbus.cpp
    src/i2c/i2cdevice.cpp

    src/modules/ads1115.cpp
    src/modules/servo.cpp

    src/plane/rcplane.cpp

    src/utils.cpp
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