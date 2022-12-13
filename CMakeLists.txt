cmake_minimum_required(VERSION 3.0.0)
project(physics-engine VERSION 0.0.1)

add_executable(physics-engine main.cpp engine/pointpart.cpp engine/env.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
