#pragma once

#include <EGL/egl.h>
#include <GLES3/gl3.h>
class DeviceContext;

class ShaderProgram
{
public:
    ShaderProgram(DeviceContext* deviceContext);
    ~ShaderProgram();
    bool load(const char* shaderfile);
    void* getShaderBuffer();
    size_t getShaderSize();
   
    size_t compileShader(const char* path, GLenum shaderType);
    size_t getProgramID() const;

    bool release();

private:
    DeviceContext* m_deviceContext;
    size_t m_programID;  // Shader program ID
    size_t m_vertexShaderID; // Vertex shader ID
    size_t m_fragmentShaderID; // Fragment shader ID
 
};