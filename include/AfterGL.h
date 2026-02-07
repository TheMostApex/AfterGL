#ifndef AFTERGL_H
#define AFTERGL_H

// Map common keys so the user doesn't need GLFW headers
#define AGL_KEY_W 87
#define AGL_KEY_S 83
#define AGL_KEY_A 65
#define AGL_KEY_D 68
#define AGL_KEY_SPACE 32

namespace AfterGL {
    void Init(int width, int height, const char* title);
    void Clear(float r, float g, float b);
    void DrawQuad(float x, float y, float w, float h, float r, float g, float b);
    void Render();
    bool IsRunning();
    void Shutdown();

    // The "Engine" way to handle input
    bool IsKeyDown(int key);
}

#endif
