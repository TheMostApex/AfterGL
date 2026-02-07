#include "AfterGL.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

struct Vertex {
    float pos[2];
    float color[3];
};

namespace AfterGL {
    static GLFWwindow* window;
    static std::vector<Vertex> vertices;
    static GLuint vao, vbo;

    void Init(int width, int height, const char* title) {
        if (!glfwInit()) return;
        window = glfwCreateWindow(width, height, title, NULL, NULL);
        glfwMakeContextCurrent(window);
        glewInit();

        // Set up Orthographic Projection (Pixel Coordinates)
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, width, height, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);

        // Generate Buffers
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
    }

    bool IsRunning() {
        return !glfwWindowShouldClose(window);
    }

    void Clear(float r, float g, float b) {
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        vertices.clear(); // Reset batch for the new frame
    }

    void DrawQuad(float x, float y, float w, float h, float r, float g, float b) {
        // Define 6 vertices (2 triangles) for one quad
        Vertex q[6] = {
            {{x, y}, {r, g, b}}, {{x+w, y}, {r, g, b}}, {{x+w, y+h}, {r, g, b}},
            {{x, y}, {r, g, b}}, {{x+w, y+h}, {r, g, b}}, {{x, y+h}, {r, g, b}}
        };
        for(int i = 0; i < 6; i++) vertices.push_back(q[i]);
    }

    void Render() {
        if (!vertices.empty()) {
            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);

            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(2, GL_FLOAT, sizeof(Vertex), (void*)0);
            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(3, GL_FLOAT, sizeof(Vertex), (void*)sizeof(float[2]));

            glDrawArrays(GL_TRIANGLES, 0, vertices.size());

            glDisableClientState(GL_COLOR_ARRAY);
            glDisableClientState(GL_VERTEX_ARRAY);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    void Shutdown() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}
