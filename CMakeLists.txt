cmake_minimum_required(VERSION 3.18)

project(rcairplane)

add_executable(rcairplane
    src/main.cpp
    src/raspgpio.cpp
    src/modules/servo.cpp
    src/math/math.cpp
)

target_link_libraries(rcairplane
    pthread
    rt
    pigpiod_if2
    rf24
)

target_include_directories(rcairplane PUBLIC
    src/
)

target_precompile_headers(rcairplane PUBLIC
    src/pch.h
)