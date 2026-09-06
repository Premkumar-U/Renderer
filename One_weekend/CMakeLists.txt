cmake_minimum_required(VERSION 3.31)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(One_weekend)

add_executable(one_weekend src/main.cpp
                        src/gradient_renderer.cpp 
                        src/vector.cpp
                        src/point.cpp
                        src/sphere.cpp
                        src/red_sphere_renderer.cpp)

target_include_directories(one_weekend PRIVATE "include")

find_package(Boost REQUIRED)

target_include_directories(one_weekend PRIVATE BOOST:BOOST)