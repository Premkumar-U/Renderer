cmake_minimum_required(VERSION 3.31)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Renderer)

add_executable(renderer src/main.cpp 
                        src/gradient_renderer.cpp 
                        src/vector.cpp
                        src/point.cpp
                        src/sphere.cpp
                        src/red_sphere_renderer.cpp)

target_include_directories(renderer PRIVATE "include")

find_package(Boost REQUIRED)

target_include_directories(renderer PRIVATE BOOST:BOOST)