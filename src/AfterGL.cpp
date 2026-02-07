#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "AfterGL.h"
#include <vector>

namespace AfterGL {
    static GLFWwindow* window;
    struct Vert { float x, y, r, g, b; };
    static std::vector<Vert> batch;
    static GLuint vao, vbo, shaderProgram;
    static int winW, winH;

    // Built-in Shaders
    const char* vSrc = "#version 330 core\n"
    "layout (location = 0) in vec2 aPos; layout (location = 1) in vec3 aCol;\n"
    "out vec3 vCol; void main() { gl_Position = vec4(aPos, 0.0, 1.0); vCol = aCol; }";
    const char* fSrc = "#version 330 core\n"
    "out vec4 fCol; in vec3 vCol; void main() { fCol = vec4(vCol, 1.0); }";

    void Init(int width, int height, const char* title) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, title, NULL, NULL);
        glfwMakeContextCurrent(window);
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        winW = width; winH = height;

        // Compile Shaders
        GLuint v = glCreateShader(GL_VERTEX_SHADER); glShaderSource(v, 1, &vSrc, NULL); glCompileShader(v);
        GLuint f = glCreateShader(GL_FRAGMENT_SHADER); glShaderSource(f, 1, &fSrc, NULL); glCompileShader(f);
        shaderProgram = glCreateProgram(); glAttachShader(shaderProgram, v); glAttachShader(shaderProgram, f);
        glLinkProgram(shaderProgram);

        // Buffer Setup
        glGenVertexArrays(1, &vao); glGenBuffers(1, &vbo);
        glBindVertexArray(vao); glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glEnableVertexAttribArray(0); glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vert), (void*)0);
        glEnableVertexAttribArray(1); glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), (void*)(sizeof(float)*2));
    }

    bool IsKeyDown(int key) {
        return glfwGetKey(window, key) == GLFW_PRESS;
    }

    void Clear(float r, float g, float b) {
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        batch.clear();
    }

    void DrawQuad(float x, float y, float w, float h, float r, float g, float b) {
        auto nx = [&](float v, float m) { return (v / m) * 2.0f - 1.0f; };
        auto ny = [&](float v, float m) { return 1.0f - (v / m) * 2.0f; };
        float x1 = nx(x, winW), x2 = nx(x+w, winW), y1 = ny(y, winH), y2 = ny(y+h, winH);

        batch.push_back({x1, y1, r, g, b}); batch.push_back({x2, y1, r, g, b});
        batch.push_back({x2, y2, r, g, b}); batch.push_back({x1, y1, r, g, b});
        batch.push_back({x2, y2, r, g, b}); batch.push_back({x1, y2, r, g, b});
    }

    void Render() {
        if (!batch.empty()) {
            glUseProgram(shaderProgram);
            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, batch.size() * sizeof(Vert), batch.data(), GL_STREAM_DRAW);
            glDrawArrays(GL_TRIANGLES, 0, batch.size());
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    bool IsRunning() { return !glfwWindowShouldClose(window); }
    void Shutdown() { glfwTerminate(); }
}
