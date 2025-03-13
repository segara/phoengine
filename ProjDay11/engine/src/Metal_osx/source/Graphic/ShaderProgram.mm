#import "ShaderProgram.h"
#import "DeviceContext.h"  // Assumes DeviceContext exposes a method getMTLDevice()


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

// Load a shader file from disk, read its contents, and compile it into a Metal library.
bool ShaderProgram::load(const char* shaderfile) {
    std::string str(shaderfile);
    // Find the last dot in the filename
        size_t dotPos = str.find_last_of('.');
        
        if (dotPos != std::string::npos) {
            // If a dot was found, replace everything after it with "metal"
            str = str.substr(0, dotPos + 1) + "metal";
        } else {
            // If no dot was found, append ".metal"
            str += ".metal";
        }
    
    std::ifstream file(str);
    if (!file.is_open()) {
        return false;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    m_shaderSource = buffer.str();
    
    NSError* error = nil;
    NSString* source = [NSString stringWithUTF8String:m_shaderSource.c_str()];
    m_library = [mtlDevice newLibraryWithSource:source options:nil error:&error];
    if (!m_library) {
        NSLog(@"Failed to compile shader library: %@", error);
        return false;
    }
    
    compileShader(shaderfile,0);
    compileShader(shaderfile,1);
    
    MTLRenderPipelineDescriptor *pipelineDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    pipelineDescriptor.vertexFunction = m_vertexFunction;
    pipelineDescriptor.fragmentFunction = m_fragmentFunction;
    pipelineDescriptor.colorAttachments[0].pixelFormat = MTLPixelFormatBGRA8Unorm;


    m_deviceContext->m_pipelineState  = [mtlDevice newRenderPipelineStateWithDescriptor:pipelineDescriptor error:&error];
    if (!m_deviceContext->m_pipelineState) {
        NSLog(@"파이프라인 상태 생성 실패: %@", error);
        return;
    }
    
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
size_t ShaderProgram::compileShader(const char* path, size_t shaderType) {
    // If the library is not loaded yet, attempt to load it from the provided path.
    if (!m_library) {
        if (!load(path)) {
            return 0;
        }
    }
    
    // Decide which function to retrieve based on shaderType.
    NSString* functionName = nil;
    if (shaderType == 0) {  // Vertex shader
        functionName = @"vertexMain";
    } else if (shaderType == 1) {  // Fragment shader
        functionName = @"fragmentMain";
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

