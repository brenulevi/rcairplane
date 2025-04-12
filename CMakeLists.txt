cmake_minimum_required(VERSION 3.10)

project(rcairplane)

add_executable(rcairplane
    src/receiver.cpp
)

target_link_libraries(rcairplane
    pthread
    rt
    pigpio
    rf24
)