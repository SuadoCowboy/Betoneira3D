#include "shader.h"

#include "shared/shared.h"
#include "file/file.h"

#include <iostream>

using namespace Betoneira;

Shader::Shader(){}

Shader::Shader(const char* vertexFilePath, const char* fragmentFilePath, const char* geometryFilePath)
{
    compileFile(vertexFilePath, fragmentFilePath, geometryFilePath);
}

Shader& Shader::use()
{ 
    glUseProgram(id); 
    return *this;
}

void Shader::compileFile(const char* vertexFilePath, const char* fragmentFilePath, const char* geometryFilePath)
{
    std::string vertexSource, fragmentSource, geometrySource;

    FileSystem::getFileContent(vertexFilePath, vertexSource);
    FileSystem::getFileContent(fragmentFilePath, fragmentSource);
    if (geometryFilePath != nullptr)
    {
        FileSystem::getFileContent(geometryFilePath, geometrySource);
        compile(vertexSource.c_str(), fragmentSource.c_str(), geometrySource.c_str());
    }
    else
        compile(vertexSource.c_str(), fragmentSource.c_str());

}

void Shader::compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource)
{
    unsigned int vertexShader, fragmentShader, geometryShader;

    // vertex Shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader, "VERTEX");

    // fragment Shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, "FRAGMENT");
    
    // if geometry shader source code is given, also compile geometry shader
    if (geometrySource != nullptr)
    {
        geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometryShader, 1, &geometrySource, NULL);
        glCompileShader(geometryShader);
        checkCompileErrors(geometryShader, "GEOMETRY");
    }

    // shader program
    id = glCreateProgram();
    
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    
    if (geometrySource != nullptr)
        glAttachShader(id, geometryShader);
    
    glLinkProgram(id);
    
    checkCompileErrors(id, "PROGRAM");
    
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    if (geometrySource != nullptr)
        glDeleteShader(geometryShader);
}

void Shader::setFloat(const char* name, float value, bool useShader)
{
    if (useShader)
        use();
    glUniform1f(glGetUniformLocation(id, name), value);
}
void Shader::setInteger(const char* name, int value, bool useShader)
{
    if (useShader)
        use();
    glUniform1i(glGetUniformLocation(id, name), value);
}
void Shader::setVector2f(const char* name, float x, float y, bool useShader)
{
    if (useShader)
        use();
    glUniform2f(glGetUniformLocation(id, name), x, y);
}
void Shader::setVector2f(const char* name, const Math::Vector2f& value, bool useShader)
{
    if (useShader)
        use();
    glUniform2f(glGetUniformLocation(id, name), value.x, value.y);
}
void Shader::setVector3f(const char* name, float x, float y, float z, bool useShader)
{
    if (useShader)
        use();
    glUniform3f(glGetUniformLocation(id, name), x, y, z);
}
void Shader::setVector3f(const char* name, const Math::Vector3f& value, bool useShader)
{
    if (useShader)
        use();
    glUniform3f(glGetUniformLocation(id, name), value.x, value.y, value.z);
}
void Shader::setVector4f(const char* name, float x, float y, float z, float w, bool useShader)
{
    if (useShader)
        use();
    glUniform4f(glGetUniformLocation(id, name), x, y, z, w);
}
void Shader::setVector4f(const char* name, const Math::Vector4f& value, bool useShader)
{
    if (useShader)
        use();
    glUniform4f(glGetUniformLocation(id, name), value.x, value.y, value.z, value.w);
}
void Shader::setMatrix2x2(const char* name, const glm::mat2 &mat, bool useShader) const
{
    glUniformMatrix2fv(glGetUniformLocation(id, name), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setMatrix3x3(const char* name, const glm::mat3 &mat, bool useShader) const
{
    glUniformMatrix3fv(glGetUniformLocation(id, name), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setMatrix4x4(const char* name, const glm::mat4 &mat, bool useShader) const
{
    glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER: Compile-time error: Type: " << type << "\n" << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER: Link-time error: Type: " << type << "\n" << infoLog << std::endl;
        }
    }
}