#include "AfterGL.h"
#include <GL/glew.h>  // Use GLEW to load GL 4.0 entry points
#include <GLFW/glfw3.h>
#include <iostream>

// Internal state
static GLFWwindow* g_Window = nullptr;
static GLuint g_VAO = 0;
static GLuint g_VBO = 0;
static GLuint g_ShaderProgram = 0;

// Simple GLSL 4.0 Shaders
const char* vertexShaderSource = "#version 400\n"
"layout (location = 0) in vec3 aPos;\n"
"void main() { gl_Position = vec4(aPos, 1.0); }\0";

const char* fragmentShaderSource = "#version 400\n"
"out vec4 FragColor;\n"
"void main() { FragColor = vec4(1.0, 0.5, 0.2, 1.0); }\0";

// --- Internal Helper: Shader Compiler ---
static GLuint CompileShaders() {
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShaderSource, NULL);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShaderSource, NULL);
    glCompileShader(fs);

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

// --- API Implementation ---

void Init(int width, int height, const char* title) {
    if (!glfwInit()) return;

    // Force OpenGL 4.0 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    g_Window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!g_Window) {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(g_Window);
    glewInit(); // Load GL 4.0 functions

    g_ShaderProgram = CompileShaders();

    // Setup Geometry for DrawTriangle (Point #5 Fix)
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
