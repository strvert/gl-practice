cmake_minimum_required(VERSION 3.1)
project(gl_3d)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O0 -g3 -std=c++1z -lSOIL -ldl -lGL -lglfw -lX11 -pthread")

include_directories(thirdparty/glad/include)
set(LIBS thirdparty/glad/src/glad.c)

include_directories(thirdparty/stb)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(
    gl_3d
    main.cpp
    ${SOURCES}
    ${LIBS}
)
