AfterGL is a lightweight OpenGL 4.0 "branch" designed for speed and compatibility. It is specifically built to provide a modern graphics foundation for legacy GPUs that can no longer handle heavy modern engines.



Uses OpenGL 4.0 for 2010+ GPUs

Project Structure
* `main.cpp`: The engine core and shader logic.
* `install.sh`: Automated dependency and build script.
* `src/glad.c`: The OpenGL loader.
* `include/`: Headers for GLAD and KHR.

AfterGL comes with an automated installer that handles dependencies (cmake, glfw, etc.) for both Arch and Ubuntu/Debian.

```bash
git clone [https://github.com/YOUR_USERNAME/AfterGL.git](https://github.com/YOUR_USERNAME/AfterGL.git) && cd AfterGL && chmod +x install.sh && ./install.sh
