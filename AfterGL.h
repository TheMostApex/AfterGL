#ifndef AFTERGL_H
#define AFTERGL_H

// The simple commands you are giving the world:
namespace AfterGL {
    void Init(int width, int height, const char* title);
    void Clear(float r, float g, float b);
    void Render();
    bool IsRunning();
    void Close();
}

#endif
