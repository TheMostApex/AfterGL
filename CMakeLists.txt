cmake_minimum_required(VERSION 3.10)
project(AfterGL VERSION 0.2 LANGUAGES C CXX)

set(OpenGL_GL_PREFERENCE GLVND)
include(GNUInstallDirs)

# 1. Dependencies
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# 2. Source Files (Matching your actual folder structure now)
set(SOURCES
    src/AfterGL.cpp
    src/glad.c
)

# 3. Build the Library
add_library(aftergl SHARED ${SOURCES})

# 4. Include Paths
target_include_directories(aftergl PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# 5. Link (Using GLAD means we don't need to link GLEW)
target_link_libraries(aftergl PRIVATE glfw OpenGL::GL ${CMAKE_DL_LIBS})
