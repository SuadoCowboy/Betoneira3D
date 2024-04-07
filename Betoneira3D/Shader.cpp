#include "Shader.h"

#include <string>

#include "File.h"
#include "Logger.h"
#include "BetoneiraUtils.h"

using namespace Betoneira::Graphics;

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
    Betoneira::FileSystem::FileHandler file{ vertexShaderPath };

    // load vertex shader
    const char* vertexShaderSource;
    size_t vertexShaderSize;
    {
        Betoneira::handleStatusLogging(file.open(Betoneira::FileSystem::FILE_READ));

        std::string vertexShaderString;
        Betoneira::handleStatusLogging(file.read(vertexShaderString));

        vertexShaderSize = vertexShaderString.length();

        vertexShaderSource = vertexShaderString.c_str();

        Betoneira::handleStatusLogging(file.close());
    }


    // load fragment shader
    const char* fragmentShaderSource;
    size_t fragmentShaderSize;
    {
        Betoneira::handleStatusLogging(file.open(Betoneira::FileSystem::FILE_READ));

        std::string fragmentShaderString;
        Betoneira::handleStatusLogging(file.read(fragmentShaderString));

        fragmentShaderSize = fragmentShaderString.length();

        fragmentShaderSource = fragmentShaderString.c_str();
        
        Betoneira::handleStatusLogging(file.close());
    }

    // Compile shaders
    vertexShader = bgfx::createShader(bgfx::copy(vertexShaderSource, vertexShaderSize));
    fragmentShader = bgfx::createShader(bgfx::copy(fragmentShaderSource, fragmentShaderSize));
}

Shader::~Shader() {
    bgfx::destroy(vertexShader);
    bgfx::destroy(fragmentShader);
}

bgfx::ShaderHandle Shader::getVertexShader() const {
    return vertexShader;
}

bgfx::ShaderHandle Shader::getFragmentShader() const {
    return fragmentShader;
}