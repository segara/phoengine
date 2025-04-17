#include "ShaderProgram.h"
#include "DeviceContext.h"  // Assumes DeviceContext exposes a method getMTLDevice()
#import <Metal/Metal.h>
#import <Foundation/Foundation.h>
#include <iostream>

// Constructor: initialize Metal device from your device context.
ShaderProgram::ShaderProgram(DeviceContext* deviceContext)
: m_deviceContext(deviceContext),
  m_library(nil),
  m_vertexFunction(nil),
  m_fragmentFunction(nil),
  m_pipelineState(nil)
{
    mtlDevice = m_deviceContext->m_mtlDevice;
}

// Destructor: release allocated Metal objects.
ShaderProgram::~ShaderProgram() {
    release();
}


id<MTLLibrary> LoadDefaultShaderLibrary(id<MTLDevice> device) {
    @autoreleasepool {
        NSError* error = nil;

        // 번들에서 metallib 파일 찾기 (자동 생성됨)
        NSURL* libURL = [[NSBundle mainBundle] URLForResource:@"default" withExtension:@"metallib"];
        if (!libURL) {
            NSLog(@"metallib 파일을 찾을 수 없습니다.");
            return nil;
        }

        NSData* data = [NSData dataWithContentsOfURL:libURL];
        dispatch_data_t dispatchData = dispatch_data_create([data bytes], [data length], dispatch_get_main_queue(), ^{
                   // cleanup block, 필요 없으면 그냥 비워도 됨
               });
        return [device newLibraryWithData:dispatchData error:&error];
    }
}
// Load a shader file from disk, read its contents, and compile it into a Metal library.
bool ShaderProgram::load(const char* shaderfile){
   
   
    m_library = LoadDefaultShaderLibrary(mtlDevice);

    compileShader(0);
    compileShader(1);
        
    MTLRenderPipelineDescriptor *pipelineDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    MTLVertexDescriptor *vertexDescriptor = [[MTLVertexDescriptor alloc] init];

    // Attribute 0 - position
    vertexDescriptor.attributes[0].format = MTLVertexFormatFloat4;
    vertexDescriptor.attributes[0].offset = 0;
    vertexDescriptor.attributes[0].bufferIndex = 0;

    // Buffer layout
    vertexDescriptor.layouts[0].stride = sizeof(float) * 4; // float4 = 16 bytes
    vertexDescriptor.layouts[0].stepRate = 1;
    vertexDescriptor.layouts[0].stepFunction = MTLVertexStepFunctionPerVertex;

    // 적용
    pipelineDescriptor.vertexDescriptor = vertexDescriptor;
    
    pipelineDescriptor.vertexFunction = m_vertexFunction;
    pipelineDescriptor.fragmentFunction = m_fragmentFunction;
    pipelineDescriptor.colorAttachments[0].pixelFormat = MTLPixelFormatBGRA8Unorm;

    
    NSError* error = nil;
    m_deviceContext->m_pipelineState  = [mtlDevice newRenderPipelineStateWithDescriptor:pipelineDescriptor error:&error];
  
    if (!m_deviceContext->m_pipelineState) {
        // 파이프라인 디스크립터 내용 로깅
        NSLog(@" 파이프라인 생성 실패: %@", error.localizedDescription);
        NSLog(@"파이프라인 상태 생성 실패: %@", error);
        return;
    }
    NSLog(@"Vertex function: %@", pipelineDescriptor.vertexFunction.name);
    NSLog(@"Fragment function: %@", pipelineDescriptor.fragmentFunction.name);
    NSLog(@"Pixel format: %lu", (unsigned long)pipelineDescriptor.colorAttachments[0].pixelFormat);
    
    return true;
}

// Returns the pointer to the shader source buffer.
void* ShaderProgram::getShaderBuffer() {
    return nullptr;
}

// Returns the size (in bytes) of the shader source.
size_t ShaderProgram::getShaderSize() {
    return 0;
}

// Compiles a specific shader function (vertex or fragment) from the loaded library.
// Here we assume function names "vertex_main" and "fragment_main" for simplicity.
size_t ShaderProgram::compileShader(size_t shaderType) {
 
    NSError* error = nil;
 
     if (!m_library) {
         NSLog(@"Failed to compile shader library: %@", error);
         return false;
     }
    
    // Decide which function to retrieve based on shaderType.
    NSString* functionName = nil;
    if (shaderType == 0) {  // Vertex shader
        functionName = @"VS";
    } else if (shaderType == 1) {  // Fragment shader
        functionName = @"PS";
    } else {
        return 0;
    }
    
    // Get the shader function from the library.
    id<MTLFunction> function = [m_library newFunctionWithName:functionName];
    if (!function) {
        NSLog(@"Failed to get function: %@", functionName);
        return 0;
    }
    
    if (shaderType == 0) {
        m_vertexFunction = function;
    } else {
        m_fragmentFunction = function;
    }
    
    
    // For demonstration, return the pointer value cast to size_t.
    return reinterpret_cast<size_t>(function);
}

// Returns an identifier for the pipeline state.
// In Metal there isn’t a program ID like in OpenGL, so we return the pointer (as a size_t) to the pipeline state.
size_t ShaderProgram::getProgramID() const {
    return reinterpret_cast<size_t>(m_pipelineState);
}

// Releases the Metal objects allocated.
bool ShaderProgram::release() {
    if (m_library) {
        //[m_library release];
        m_library = nil;
    }
    if (m_pipelineState) {
        //[m_pipelineState release];
        m_pipelineState = nil;
    }
    // Note: m_vertexFunction and m_fragmentFunction are managed by the library or pipeline state.
    return true;
}

