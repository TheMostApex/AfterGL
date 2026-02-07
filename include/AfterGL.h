#ifndef AFTERGL_H
#define AFTERGL_H

/*
 * =========================================================================
 * AfterGL Engine Core
 * A low-overhead graphics library for "Old Metal" hardware.
 * =========================================================================
 */

// Include standard headers for basic types
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
    #endif

    /**
     * @brief Initialize the AfterGL window and graphics context.
     * FIX (Point #2): Parameter order standardized to (Width, Height, Title).
     */
    void Init(int width, int height, const char* title);

    /**
     * @brief Clear the screen with a solid color.
     */
    void Clear(float r, float g, float b);

    /**
     * @brief Swap buffers and finalize the current frame.
     */
    void Render();

    /**
     * @brief Poll events and check if the window is still open.
     * @return Returns 1 (true) if running, 0 (false) if closing.
     */
    int IsRunning();

    /**
     * @brief Cleanup and destroy the AfterGL context.
     */
    void Shutdown();

    /* * ROADMAP (Point #5): Basic Draw Calls
     * These are implemented to allow testing beyond a blank screen.
     */
    void DrawTriangle();
    void DrawQuad();

    #ifdef __cplusplus
} // End extern "C"

/**
 * C++ Wrapper Namespace (Point #1)
 * Allows developers to use AfterGL::Init instead of global scope.
 */
namespace AfterGL {
    inline void Init(int w, int h, const char* t) {
        ::Init(w, h, t);
    }

    inline void Clear(float r, float g, float b) {
        ::Clear(r, g, b);
    }

    inline void Render() {
        ::Render();
    }

    inline bool IsRunning() {
        return ::IsRunning() != 0;
    }

    inline void Shutdown() {
        ::Shutdown();
    }

    // Planned Features Roadmap Placeholder
    namespace Experimental {
        inline void SetCamera(float x, float y, float z) { /* Planned */ }
    }
}
#endif

#endif // AFTERGL_H
