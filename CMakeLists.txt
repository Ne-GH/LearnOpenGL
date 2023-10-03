cmake_minimum_required(VERSION 3.27)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 23)

add_executable(LearnOpenGL main.cpp glad.c)
include_directories(header)
#find_package(glfw3 glad REQUIRED )
#target_link_libraries(LearnOpenGL GL glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(LearnOpenGL PRIVATE glfw ${OPENGL_LIBRARIES})

