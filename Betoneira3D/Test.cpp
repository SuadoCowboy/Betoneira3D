#define BX_CONFIG_DEBUG 1
#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "Logger.h"
#include "File.h"
#include "Shader.h"
#include "Mesh.h"

#include <vector>

static std::vector<Betoneira::Graphics::VertexData2D> quadVertices = {
    {-1.0f,  1.0f, 0.0f}, // down left
    { 1.0f,  1.0f, 0.0f}, // down right
    {-1.0f, -1.0f, 0.0f}, // top left
    { 1.0f, -1.0f, 0.0f}, // top right
};

static const std::vector<uint16_t> quadIndices = {
    0, 1, 2,
    1, 3, 2,
};

static void glfwErrorCallback(int error, const char* description)
{
    Betoneira::Logger::log({std::to_string(error).c_str(), ": ", description }, {"ERROR", "GLFW"});
}

int main() {
    Betoneira::Logger::init();

    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit())
        return 1;
    
    Betoneira::Logger::log({ "initialized" }, { "GLFW" });

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // TODO: see hints to add

    GLFWwindow* window = glfwCreateWindow(1024, 768, "Betoneira3D - 2D Square Test", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return 1;
    }
    
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    Betoneira::Logger::log({ "created window ", std::to_string(width), "x", std::to_string(height) }, { "WINDOW" });

    // Make the window's context current
    //glfwMakeContextCurrent(window);

    bgfx::Init init;
    init.platformData.nwh = glfwGetWin32Window(window);
    
    init.resolution.width = (uint32_t)width;
    init.resolution.height = (uint32_t)height;
    init.resolution.reset = BGFX_RESET_VSYNC;
    if (!bgfx::init(init))
        return 1;

    Betoneira::Logger::log({"initialized with renderer: ", bgfx::getRendererName(bgfx::getRendererType())}, {"BGFX"});

    Betoneira::Logger::log({ "compiling shader program..." }, { "BGFX", "SHADER" });

    // Create shader program
    Betoneira::Graphics::Shader shader{ "vs_quad.sc", "fs_quad.sc" };
    bgfx::ProgramHandle program = bgfx::createProgram(shader.getVertexShader(), shader.getFragmentShader(), true);

    Betoneira::Logger::log({ "created shader program" }, { "BGFX", "SHADER" });

    Betoneira::Graphics::VertexData2D::init();
    //Betoneira::Graphics::VertexData2DTextured::init();
    //Betoneira::Graphics::VertexData3D::init();
    //Betoneira::Graphics::VertexData3DTextured::init();
    
    // Create vertex and index buffers
    Betoneira::Graphics::Mesh quad{ quadVertices, quadIndices };

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
        
        quad.render();
        bgfx::submit(0, program);

        // Advance to next frame. Process submitted rendering primitives.
        bgfx::frame();
    }

    // Shutdown BGFX
    bgfx::shutdown();
    Betoneira::Logger::log({ "terminated" }, { "BGFX" });

    // Terminate GLFW
    glfwTerminate();
    Betoneira::Logger::log({ "terminated" }, { "GLFW" });

    return 0;
}