#pragma once

#include "glad/gl.h"

class DeviceContext;

class ShaderProgram
{
public:
    ShaderProgram(DeviceContext* deviceContext);
    ~ShaderProgram();
    void* getShaderBuffer();
    size_t getShaderSize();
    bool load(const char* shaderfile);
    size_t compileShader(const char* path, GLenum shaderType);
    size_t getProgramID() const;

    bool release();

private:

    size_t m_programID;  // Shader program ID
    size_t m_vertexShaderID; // Vertex shader ID
    size_t m_fragmentShaderID; // Fragment shader ID
    DeviceContext* m_deviceContext; // Associated device context
};