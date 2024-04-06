#include <stdio.h>

#define BX_CONFIG_DEBUG 1
#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "Logger.h"
#include "File.h"

static bool s_showStats = false;

static void glfw_errorCallback(int error, const char* description)
{
    Betoneira::Logger::log({std::to_string(error).c_str(), ": ", description }, {"ERROR", "GLFW"});
}

static void glfw_keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_F1 && action == GLFW_RELEASE)
        s_showStats = !s_showStats;
}

int main() {
    Betoneira::Logger::init();

    glfwSetErrorCallback(glfw_errorCallback);
    if (!glfwInit())
        return 1;
    
    Betoneira::Logger::log({ "initialized" }, { "GLFW" });

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    
    GLFWwindow* window = glfwCreateWindow(1024, 768, "Betoneira3D - HelloWorld", nullptr, nullptr);
    if (!window)
        return 1;
    glfwSetKeyCallback(window, glfw_keyCallback);
    
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    Betoneira::Logger::log({ "created window ", std::to_string(width), "x", std::to_string(height) }, { "WINDOW" });

    bgfx::Init init;
    init.platformData.nwh = glfwGetWin32Window(window);
    
    init.resolution.width = (uint32_t)width;
    init.resolution.height = (uint32_t)height;
    init.resolution.reset = BGFX_RESET_VSYNC;
    if (!bgfx::init(init))
        return 1;

    Betoneira::Logger::log({"initialized"}, {"BGFX"});

    // Set view 0 to the same dimensions as the window and to clear the color buffer.
    const bgfx::ViewId kClearView = 0;
    bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR);
    bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);

    bgfx::setViewClear(0, BGFX_CLEAR_COLOR, 0x0045aaff, 1.0f, 0);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Poll for and process events
        glfwPollEvents();
        
        int oldWidth = width, oldHeight = height;
        glfwGetWindowSize(window, &width, &height);
        
        if (width != oldWidth || height != oldHeight) {
            bgfx::reset((uint32_t)width, (uint32_t)height, BGFX_RESET_VSYNC);
            bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
        }
        
        // This dummy draw call is here to make sure that view 0 is cleared if no other draw calls are submitted to view 0.
        bgfx::touch(kClearView);
        
        // Use debug font to print information about this example.
        bgfx::dbgTextClear();
        bgfx::dbgTextPrintf(0, 0, 0x0f, "Press F1 to toggle stats.");
        bgfx::dbgTextPrintf(0, 1, 0x0f, "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");
        bgfx::dbgTextPrintf(80, 1, 0x0f, "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
        bgfx::dbgTextPrintf(80, 2, 0x0f, "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");
        
        const bgfx::Stats* stats = bgfx::getStats();
        bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters.", stats->width, stats->height, stats->textWidth, stats->textHeight);
        
        // Enable stats or debug text.
        bgfx::setDebug(s_showStats ? BGFX_DEBUG_STATS : BGFX_DEBUG_TEXT);
        
        // Advance to next frame. Process submitted rendering primitives.
        bgfx::frame();
    }

    // Shutdown BGFX
    bgfx::shutdown();
    Betoneira::Logger::log({ "shutdown" }, { "BGFX" });

    // Terminate GLFW
    glfwTerminate();
    Betoneira::Logger::log({ "terminate" }, { "GLFW" });

    return 0;
}