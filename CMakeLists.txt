# 1. Define the version of CMake we are using
cmake_minimum_required(VERSION 3.10)

# 2. Set the Project Name
project(AfterGL)

# 3. Use Modern C++ (C++17 is great for performance)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. Find the necessary libraries on Garuda
# This looks for GLFW3 (the window maker)
find_package(glfw3 REQUIRED)

# 5. Tell the compiler where your header files are
# This lets you use #include <glad/glad.h>
include_directories(include)

# 6. Build the executable
# This combines your code and the GLAD loader into one program
# This tells Linux to create a "Shared Library" (.so)
add_library(AfterGL SHARED src/glad.c)

# We move your 'main.cpp' code into a separate test app
add_executable(AfterGL_Test main.cpp)
target_link_libraries(AfterGL_Test AfterGL glfw ${OPENGL_LIBRARIES} dl)

# 7. Link the "Engine" parts together
# AfterGL needs GLFW, OpenGL, and 'dl' (the Linux library loader)
target_link_libraries(AfterGL glfw ${OPENGL_LIBRARIES} dl)
