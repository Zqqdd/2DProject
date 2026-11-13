cmake_minimum_required(VERSION 3.50)
project(Sylven LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(game src/main.cpp src/Window.cpp src/Game.cpp)

set(SDL3_DIR "${CMAKE_SOURCE_DIR}/third_party/SDL3/cmake")
find_package(SDL3 REQUIRED CONFIG)
find_package(OpenGL REQUIRED)

target_link_libraries(game PRIVATE SDL3::SDL3 OpenGL::GL)

if(WIN32)
    add_custom_command(TARGET game POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL3::SDL3> $<TARGET_FILE_DIR:game> VERBATIM)
endif()