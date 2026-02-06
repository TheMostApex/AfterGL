#include <glad/glad.h>   // MUST come before GLFW
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    // 1. Initialize GLFW (The window manager)
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // 2. FORCE OPENGL 4.0 (Good middle ground for older GPUs)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 3. Create the Window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Garuda GL4 Tech", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create window. Your GPU might not support GL 4.0" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 4. Load GLAD (Connects your code to the GPU driver)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 5. The Main Loop
    while (!glfwWindowShouldClose(window)) {
        // Render colors here! (A nice "Garuda Purple")
        glClearColor(0.45f, 0.0f, 0.9f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
