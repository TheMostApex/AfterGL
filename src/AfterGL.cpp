#include "AfterGL.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

// Internal State
static GLFWwindow* g_Window = nullptr;
static GLuint g_ShaderProgram = 0;
static GLuint g_VAO = 0;
static GLuint g_VBO = 0;

// GLSL 4.0 Shaders (Standard for Old Metal)
const char* vertexShaderSource = "#version 400\n"
"layout (location = 0) in vec3 aPos;\n"
"void main() {\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 400\n"
"out vec4 FragColor;\n"
"void main() {\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n" // Classic Orange
"}\0";

// Helper: Shader Compiler
static GLuint CompileShader(unsigned int type, const char* source) {
    GLuint id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);
    return id;
}

// --- API Implementation ---

void Init(int width, int height, const char* title) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    // Target OpenGL 4.0 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    g_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!g_Window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(g_Window);

    // Initialize GLAD (Replaces GLEW)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    // Setup Shaders
    GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    g_ShaderProgram = glCreateProgram();
    glAttachShader(g_ShaderProgram, vs);
    glAttachShader(g_ShaderProgram, fs);
    glLinkProgram(g_ShaderProgram);
    glDeleteShader(vs);
    glDeleteShader(fs);

    // Setup Geometry (Triangle)
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    glGenVertexArrays(1, &g_VAO);
    glGenBuffers(1, &g_VBO);

    glBindVertexArray(g_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, g_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Clear(float r, float g, float b) {
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void DrawTriangle() {
    glUseProgram(g_ShaderProgram);
    glBindVertexArray(g_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Render() {
    glfwSwapBuffers(g_Window);
    glfwPollEvents();
}

int IsRunning() {
    return !glfwWindowShouldClose(g_Window);
}

void Shutdown() {
    glDeleteVertexArrays(1, &g_VAO);
    glDeleteBuffers(1, &g_VBO);
    glDeleteProgram(g_ShaderProgram);
    glfwDestroyWindow(g_Window);
    glfwTerminate();
}
