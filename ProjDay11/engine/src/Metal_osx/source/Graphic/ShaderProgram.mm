#include "ShaderProgram.h"
#include "DeviceContext.h"  // Assumes DeviceContext exposes a method getMTLDevice()
#include "dxc/dxcapi.h"
#include <spirv_msl.hpp>  // Make sure to include the SPIRV-Cross headers

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

LPCWSTR ConvertCharToWChar(const char* str) {
    // Get the required size for the new wide string
    size_t size = strlen(str) + 1;
    wchar_t* wstr = new wchar_t[size];
    
    // Convert the string
    #ifdef _WIN32
        size_t convertedChars = 0;
        mbstowcs_s(&convertedChars, wstr, size, str, _TRUNCATE);
    #else
        mbstowcs(wstr, str, size);
    #endif
    
    return wstr;
}

// Load a shader file from disk, read its contents, and compile it into a Metal library.
bool ShaderProgram::load(const char* shaderfile) {
    // Initialize DXC compiler
    CComPtr<IDxcLibrary> library;
    CComPtr<IDxcCompiler> compiler;
    CComPtr<IDxcBlobEncoding> sourceBlob;
    

    HRESULT hr = DxcCreateInstance(CLSID_DxcLibrary, IID_PPV_ARGS(&library));
    if (FAILED(hr)) {
        std::cerr << "Failed to create DXC library" << std::endl;
        return false;
    }
    
    hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&compiler));
    if (FAILED(hr)) {
        std::cerr << "Failed to create DXC compiler" << std::endl;
        return false;
    }
    
    // Load shader source file
    uint32_t codePage = CP_UTF8;
    hr = library->CreateBlobFromFile(ConvertCharToWChar(shaderfile), &codePage, &sourceBlob);
    if (FAILED(hr)) {
        std::cerr << "Failed to load shader file: " << shaderfile << std::endl;
        return false;
    }
// Define compilation arguments for Metal conversion
   std::vector<LPCWSTR> arguments = {
       L"-spirv",              // Output SPIR-V
       L"-fspv-reflect",       // Add reflection data
       L"-D", L"ENABLE_METAL=1"     // 메탈용 전처리기 정의
   };
  
    
    // Compile shader
    CComPtr<IDxcOperationResult> result_vs;
    hr = compiler->Compile(
        sourceBlob,             // Source code
                           ConvertCharToWChar(shaderfile),             // File name
        L"VS",                // Entry point name
        L"vs_5_0",              // Target profile
        arguments.data(),       // Arguments
        arguments.size(),       // Number of arguments
        nullptr,                // Define macros
        0,                      // Number of define macros
        nullptr,                // Include handler
        &result_vs                 // Compilation result
    );
    
    if (SUCCEEDED(hr)) {
        result_vs->GetStatus(&hr);
    }
    
    // Check for compilation errors
    if (FAILED(hr)) {
        CComPtr<IDxcBlobEncoding> errors;
        result_vs->GetErrorBuffer(&errors);
        if (errors) {
            std::cerr << "Shader compilation failed: " << static_cast<const char*>(errors->GetBufferPointer()) << std::endl;
        }
        return false;
    }
    
    CComPtr<IDxcOperationResult> result_ps;
    hr = compiler->Compile(
        sourceBlob,             // Source code
                           ConvertCharToWChar(shaderfile),             // File name
        L"PS",                // Entry point name
        L"ps_5_0",              // Target profile
        arguments.data(),       // Arguments
        arguments.size(),       // Number of arguments
        nullptr,                // Define macros
        0,                      // Number of define macros
        nullptr,                // Include handler
        &result_ps                 // Compilation result
    );
    
    if (SUCCEEDED(hr)) {
        result_ps->GetStatus(&hr);
    }
    
    // Check for compilation errors
    if (FAILED(hr)) {
        CComPtr<IDxcBlobEncoding> errors;
        result_ps->GetErrorBuffer(&errors);
        if (errors) {
            std::cerr << "Shader compilation failed: " << static_cast<const char*>(errors->GetBufferPointer()) << std::endl;
        }
        return false;
    }
        
    // Get compiled shader blob
    CComPtr<IDxcBlob> spirvBlobVS;
    result_vs->GetResult(&spirvBlobVS);
    CComPtr<IDxcBlob> spirvBlobPS;
    result_ps->GetResult(&spirvBlobPS);
        
    // SPIR-V 바이너리로 변환
    uint32_t* data_vs = reinterpret_cast<uint32_t*>(spirvBlobVS->GetBufferPointer());
    size_t size_in_bytes = spirvBlobVS->GetBufferSize();
    size_t word_count = size_in_bytes / sizeof(uint32_t);
    std::vector<uint32_t> spirv_vs(data_vs, data_vs + word_count);
    
    uint32_t* data_ps = reinterpret_cast<uint32_t*>(spirvBlobPS->GetBufferPointer());
    size_in_bytes = spirvBlobPS->GetBufferSize();
    word_count = size_in_bytes / sizeof(uint32_t);
    std::vector<uint32_t> spirv_ps(data_ps, data_ps + word_count);
    
    spirv_cross::CompilerMSL compiler_spirv_cross_vs(spirv_vs);
    spirv_cross::CompilerMSL compiler_spirv_cross_ps(spirv_ps);

    // 옵션 설정 (필요 시)
    spirv_cross::CompilerMSL::Options msl_options;
    msl_options.platform = spirv_cross::CompilerMSL::Options::Platform::macOS;
    msl_options.msl_version = spirv_cross::CompilerMSL::Options::make_msl_version(2, 4);
    // 예: Metal 2.4
    compiler_spirv_cross_vs.set_msl_options(msl_options);
    compiler_spirv_cross_ps.set_msl_options(msl_options);

    // 변환
    std::string msl_source_vs = compiler_spirv_cross_vs.compile();
    std::string msl_source_ps = compiler_spirv_cross_ps.compile();

    compileShader(msl_source_vs,0);
    compileShader(msl_source_ps,1);
        
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
    return (void*)m_shaderSource.c_str();
}

// Returns the size (in bytes) of the shader source.
size_t ShaderProgram::getShaderSize() {
    return m_shaderSource.size();
}

// Compiles a specific shader function (vertex or fragment) from the loaded library.
// Here we assume function names "vertex_main" and "fragment_main" for simplicity.
size_t ShaderProgram::compileShader(std::string shaderBuffer, size_t shaderType) {
 
    m_shaderSource = shaderBuffer;
    
    NSError* error = nil;
 
    NSString* source = [NSString stringWithUTF8String:m_shaderSource.c_str()];
     m_library = [mtlDevice newLibraryWithSource:source options:nil error:&error];
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
        [m_library release];
        m_library = nil;
    }
    if (m_pipelineState) {
        [m_pipelineState release];
        m_pipelineState = nil;
    }
    // Note: m_vertexFunction and m_fragmentFunction are managed by the library or pipeline state.
    return true;
}

