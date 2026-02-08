#ifndef AFTERGL_H
#define AFTERGL_H

#include <vector>
#include <string>

#define AGL_KEY_W 87
#define AGL_KEY_S 83
#define AGL_KEY_A 65
#define AGL_KEY_D 68
#define AGL_KEY_SPACE 32

namespace AfterGL {
    struct Vert {
        float x, y, z;
        float r, g, b;
    };

    void Init(int width, int height, const char* title);
    void Clear(float r, float g, float b);

    // 3D Quad drawing with rotation
    void DrawQuad3D(float x, float y, float z, float w, float h, float rotX, float rotY, float r, float g, float b);

    // UI drawing (orthographic overlay)
    void DrawNumber(int num, float x, float y, float size, float r, float g, float b);

    void Render();
    bool IsRunning();
    void Shutdown();
    bool IsKeyDown(int key);
}

#endif
