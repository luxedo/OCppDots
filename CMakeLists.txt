cmake_minimum_required(VERSION 3.13)
project(OCppDots)

set(CMAKE_CXX_STANDARD 20)

add_executable(OCppDots main.cpp OCDots.cpp OCDots.h)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(OCppDots ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
