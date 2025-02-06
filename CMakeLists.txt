cmake_minimum_required(VERSION 3.25)
project(OmegaX C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB SRCs "*.c")
add_executable(OmegaX ${SRCs})

target_include_directories(OmegaX PRIVATE ${SDL2_INCLUDE_DIRS})
if(WIN32)
    target_link_libraries(OmegaX PRIVATE SDL2::SDL2 SDL2::SDL2main OpenGL::GL)
    target_link_options(OmegaX PRIVATE -mconsole)
else()
    target_link_libraries(OmegaX PRIVATE SDL2::SDL2 OpenGL::GL)
endif()
