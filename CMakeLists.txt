cmake_minimum_required(VERSION 3.30)
project(OmegaX C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB SRCs "*.c")
add_executable(OmegaX ${SRCs})
target_link_libraries(OmegaX PRIVATE SDL2::SDL2 OpenGL::GL)
