#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "AfterGL.h"

namespace AfterGL {
    static GLFWwindow* window;
    static std::vector<Vert> batch;
    static GLuint vao, vbo, shaderProgram;
    static GLuint projLoc, viewLoc, modelLoc;
    static int winW, winH;

    const char* vSrc = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos; layout (location = 1) in vec3 aCol;\n"
    "uniform mat4 uProj; uniform mat4 uView; uniform mat4 uModel;\n"
    "out vec3 vCol; void main() { gl_Position = uProj * uView * uModel * vec4(aPos, 1.0); vCol = aCol; }";

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

        glEnable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE); // Ensures we see both sides of the quads while testing

        GLuint v = glCreateShader(GL_VERTEX_SHADER); glShaderSource(v, 1, &vSrc, NULL); glCompileShader(v);
        GLuint f = glCreateShader(GL_FRAGMENT_SHADER); glShaderSource(f, 1, &fSrc, NULL); glCompileShader(f);
        shaderProgram = glCreateProgram(); glAttachShader(shaderProgram, v); glAttachShader(shaderProgram, f);
        glLinkProgram(shaderProgram);

        projLoc = glGetUniformLocation(shaderProgram, "uProj");
        viewLoc = glGetUniformLocation(shaderProgram, "uView");
        modelLoc = glGetUniformLocation(shaderProgram, "uModel");

        glGenVertexArrays(1, &vao); glGenBuffers(1, &vbo);
        glBindVertexArray(vao); glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glEnableVertexAttribArray(0); glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), (void*)0);
        glEnableVertexAttribArray(1); glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), (void*)(sizeof(float)*3));
    }

    void DrawQuad3D(float x, float y, float z, float w, float h, float rotX, float rotY, float r, float g, float b) {
        float hw = w / 2.0f;
        float hh = h / 2.0f;

        Vert v1 = {-hw, -hh, 0, r, g, b}; Vert v2 = {hw, -hh, 0, r, g, b};
        Vert v3 = {hw, hh, 0, r, g, b};   Vert v4 = {-hw, hh, 0, r, g, b};

        auto transform = [&](Vert& v) {
            glm::mat4 m = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
            m = glm::rotate(m, rotX, glm::vec3(1, 0, 0));
            m = glm::rotate(m, rotY, glm::vec3(0, 1, 0));
            glm::vec4 res = m * glm::vec4(v.x, v.y, v.z, 1.0f);
            v.x = res.x; v.y = res.y; v.z = res.z;
        };

        transform(v1); transform(v2); transform(v3); transform(v4);

        batch.push_back(v1); batch.push_back(v2); batch.push_back(v3);
        batch.push_back(v1); batch.push_back(v3); batch.push_back(v4);
    }

    void Clear(float r, float g, float b) {
        glClearColor(r, g, b, 1.0f);
        // Clear both Color and Depth so the next frame starts fresh
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Render() {
        glUseProgram(shaderProgram);

        // Standard perspective matrix
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)winW/winH, 0.1f, 2000.0f);

        // Move the camera back -600 units
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -600.0f));

        // Identity model matrix (transformations are baked into vertices in DrawQuad3D)
        glm::mat4 model = glm::mat4(1.0f);

        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        if (!batch.empty()) {
            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, batch.size() * sizeof(Vert), batch.data(), GL_STREAM_DRAW);
            glDrawArrays(GL_TRIANGLES, 0, batch.size());
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
        batch.clear();
    }

    bool IsRunning() { return !glfwWindowShouldClose(window); }
    void Shutdown() { glfwTerminate(); }
    bool IsKeyDown(int key) { return glfwGetKey(window, key) == GLFW_PRESS; }
}
