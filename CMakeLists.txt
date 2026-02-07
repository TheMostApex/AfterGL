cmake_minimum_required(VERSION 3.10)
project(AfterGL VERSION 0.2 LANGUAGES C CXX)

# 1. Use standard GNU directories (lib, include, etc.)
include(GNUInstallDirs)

# 2. Set C++ Standard for our Namespace Bridge
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3. Find Dependencies for GL 4.0
# We need GLEW to access 4.0 functions and GLFW for the window
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# 4. Collect Source Files
set(SOURCES src/AfterGL.cpp)

# 5. Create the Shared Library
add_library(AfterGL SHARED ${SOURCES})

# 6. FIX Point #4: Professional Naming
# Outputs libaftergl.so so users can link with -laftergl
set_target_properties(AfterGL PROPERTIES OUTPUT_NAME "aftergl")

# 7. FIX Point #3: Header inclusion
# Handles both local builds and installed system headers
target_include_directories(AfterGL PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# 8. Link everything together
# This connects your code to the GPU drivers and window system
target_link_libraries(AfterGL PRIVATE
    GLEW::GLEW
    glfw        # or glfw3, depending on what your system prefers
    OpenGL::GL
)

# 9. Versioning
set_target_properties(AfterGL PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 0
)

# 10. INSTALLATION Logic
# This makes 'sudo make install' work properly
install(TARGETS AfterGL
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(FILES include/AfterGL.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
