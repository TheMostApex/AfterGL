

<img width="800" height="600" alt="image" src="https://github.com/user-attachments/assets/155984a0-7f3c-45d5-8614-64ceda569016" />

AfterGL is a lightweight OpenGL 4.0 fork designed for compatibility. It is specifically built to provide a modern graphics foundation for legacy GPUs that can no longer handle heavy modern engines.

It requires GLM for 3D processing.

Uses OpenGL 4.0 for 2010+ GPUs

Project Structure
* `main.cpp`: The engine core and shader logic.
* `install.sh`: Automated dependency and build script.
* `src/glad.c`: The OpenGL loader.
* `include/`: Headers for GLAD and KHR.

AfterGL comes with an automated installer that handles dependencies (cmake, glfw, etc.) for both Arch and Ubuntu/Debian.
