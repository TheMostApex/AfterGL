#ifndef AFTERGL_H
#define AFTERGL_H

namespace AfterGL {
    // Lifecycle
    void Init(int width, int height, const char* title);
    bool IsRunning();
    void Render();   // This now handles the "Flush" of the batch
    void Shutdown();

    // Drawing
    void Clear(float r, float g, float b);
    void DrawQuad(float x, float y, float w, float h, float r, float g, float b);
}

#endif
