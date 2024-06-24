cmake_minimum_required(VERSION 3.20)

project(random-generators LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(fmt CONFIG REQUIRED)
find_package(range-v3 CONFIG REQUIRED)
find_package(libcmaes CONFIG REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)

add_subdirectory(src)

