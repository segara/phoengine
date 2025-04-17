#ifndef __SHADER_PROGRAM_METAL_H__
#define __SHADER_PROGRAM_METAL_H__

#import <Metal/Metal.h>
#include <string>
#include <fstream>
#include <sstream>

// Forward declaration of your device context wrapper
class DeviceContext;

class ShaderProgram {
public:
    ShaderProgram(DeviceContext* deviceContext);
    ~ShaderProgram();

    // Loads the full shader source file and compiles it into a library.
    bool load(const char* shaderfile);

    // Returns a pointer to the shader source buffer.
    void* getShaderBuffer();

    // Returns the size of the shader source code.
    size_t getShaderSize();

    // Loads and compiles a specific shader function from the library.
    // Here shaderType could be defined as: 0 for vertex, 1 for fragment.
    size_t compileShader(size_t shaderType);

    // Returns an identifier for the pipeline state (as a size_t).
    size_t getProgramID() const;

    // Releases allocated resources.
    bool release();

private:
    DeviceContext* m_deviceContext;
    id<MTLDevice> mtlDevice;

    // Metal objects
    id<MTLLibrary> m_library;
    id<MTLFunction> m_vertexFunction;
    id<MTLFunction> m_fragmentFunction;
    id<MTLRenderPipelineState> m_pipelineState;

   
};

#endif // __SHADER_PROGRAM_METAL_H__
