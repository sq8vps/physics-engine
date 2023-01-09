cmake_minimum_required(VERSION 3.0.0)
project(physics-engine VERSION 0.0.1)

add_executable(physics-engine 
            main.cpp 
            object.hpp
            common.hpp
            error.hpp
            vec.hpp
            engine/pointpart.cpp engine/env.cpp
            engine/pointpart.hpp engine/env.hpp engine/body.hpp
            graphics/graphics.cpp
            graphics/graphics.hpp graphics/shape.hpp graphics/plane.hpp graphics/sphere.hpp
            

            lib/libfreeglut.a
)

target_link_libraries(physics-engine ${CMAKE_SOURCE_DIR}/lib/libfreeglut.a)
target_link_libraries(physics-engine libopengl32.a)
target_link_libraries(physics-engine libglu32.a)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
