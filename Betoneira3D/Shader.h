#pragma once

#include <bgfx/bgfx.h>

namespace Betoneira::Graphics {
    class Shader {
    public:
        Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
        ~Shader();

        bgfx::ShaderHandle getVertexShader() const;
        bgfx::ShaderHandle getFragmentShader() const;

    private:
        bgfx::ShaderHandle vertexShader;
        bgfx::ShaderHandle fragmentShader;
    };
}