#https://www.glfw.org/docs/3.3/build_guide.html

cmake_minimum_required(VERSION 3.11)
project(glfw-test VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)

set(SOURCES main.cpp ext/glad/glad.c)
add_executable(app ${SOURCES})
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${PROJECT_SOURCE_DIR}/ext/glfw build)
target_link_libraries(app glfw)

target_link_libraries(app OpenGL::GL)

target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ext)
