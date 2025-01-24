#include "ShaderProgram.h"
#include <iostream>

#include "hlslcc.h"
#include <d3d11.h>
#include <d3dcompiler.h>

ShaderProgram::ShaderProgram(DeviceContext* deviceContext)
    : m_deviceContext(deviceContext), m_programID(0), m_vertexShaderID(0), m_fragmentShaderID(0)
{
}

ShaderProgram::~ShaderProgram()
{
    release();
}

void* ShaderProgram::getShaderBuffer()
{
    return nullptr;
}

size_t ShaderProgram::getShaderSize()
{
    return 0;
}
const wchar_t* ConvertToWideChar(const char* charStr) {
    // 입력 문자열 길이 계산
    int len = MultiByteToWideChar(CP_UTF8, 0, charStr, -1, nullptr, 0);

    // 메모리 할당
    wchar_t* wideStr = new wchar_t[len];

    // 변환
    MultiByteToWideChar(CP_UTF8, 0, charStr, -1, wideStr, len);

    return wideStr;
}
bool ShaderProgram::load(const char* shaderfile)
{
    /************************/
    /* use hlslcc */
    const char* filename = shaderfile;
    unsigned int flags = 0;
    GLLang language = LANG_330; // OpenGL 3.3 GLSL
    GlExtensions extensions = {}; // 확장 설정 (필요 없으면 기본값)
    GLSLCrossDependencyData dependencies = {}; // 교차 종속성 데이터
    HLSLccSamplerPrecisionInfo samplerPrecisions = {};
    HLSLccReflection reflectionCallbacks = {};

	GLSLShader result_vs = {};
	GLSLShader result_ps = {};

    // hlsl 을 DXBC(D3D Shader Bytecode)로 컴파일
    ID3DBlob* m_vsblob = nullptr;
    ID3DBlob* m_psblob = nullptr;
    ID3DBlob* errblob = nullptr;
    D3DCompileFromFile(ConvertToWideChar(shaderfile), nullptr, nullptr, "VS", "vs_5_0", NULL, NULL, &m_vsblob, &errblob);
    D3DCompileFromFile(ConvertToWideChar(shaderfile), nullptr, nullptr, "PS", "ps_5_0", NULL, NULL, &m_psblob, &errblob);

    // HLSL 파일을 GLSL로 변환
    int success = TranslateHLSLFromMem(
        (const char*)m_vsblob->GetBufferPointer(),
        flags,
        language,
        &extensions,
        &dependencies,
        samplerPrecisions,
        reflectionCallbacks,
        &result_vs
    );

    success = TranslateHLSLFromMem(
        (const char*)m_psblob->GetBufferPointer(),
        flags,
        language,
        &extensions,
        &dependencies,
        samplerPrecisions,
        reflectionCallbacks,
        &result_ps
    );
    /* complie hlsl to glsl end */



    // Compile vertex shader
    m_vertexShaderID = compileShader(result_vs.sourceCode.c_str(), GL_VERTEX_SHADER);
    if (!m_vertexShaderID)
        return false;

    // Compile fragment shader
    m_fragmentShaderID = compileShader(result_ps.sourceCode.c_str(), GL_FRAGMENT_SHADER);
    if (!m_fragmentShaderID)
        return false;

    // Link shaders into a program
    m_programID = glCreateProgram();
    glAttachShader(m_programID, m_vertexShaderID);
    glAttachShader(m_programID, m_fragmentShaderID);
    glLinkProgram(m_programID);

    // Check for linking errors
    GLint isLinked;
    glGetProgramiv(m_programID, GL_LINK_STATUS, &isLinked);
    if (!isLinked)
    {
        char infoLog[512];
        glGetProgramInfoLog(m_programID, 512, nullptr, infoLog);
        std::cerr << "Error linking shader program: " << infoLog << std::endl;
        return false;
    }

    glUseProgram(m_programID);
    return true;
}

size_t ShaderProgram::compileShader(const char* result, GLenum shaderType)
{
    const char* source = result;
    // OpenGL에서 셰이더 객체를 생성합니다.
    //shaderType은 생성할 셰이더의 종류를 지정합니다.
    //    GL_VERTEX_SHADER: 버텍스 셰이더
    //    GL_FRAGMENT_SHADER : 프래그먼트 셰이더
    GLuint shaderID = glCreateShader(shaderType); 
    //셰이더 객체에 GLSL 소스 코드를 전달합니다.
    glShaderSource(shaderID, 1, &source, nullptr);
    //설정된 GLSL 소스 코드를 컴파일합니다.
    glCompileShader(shaderID);

    // Check for compilation errors
    GLint isCompiled;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
    if (!isCompiled)
    {
        char infoLog[512];
        glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
        std::cerr << "Error compiling shader: " << infoLog << std::endl;
        glDeleteShader(shaderID);
        return 0;
    }

    return shaderID;
}

size_t ShaderProgram::getProgramID() const
{
    return m_programID;
}

bool ShaderProgram::release()
{
    if (m_programID != 0)
    {
        glDeleteProgram(m_programID);
        m_programID = 0;
    }

    if (m_vertexShaderID != 0)
    {
        glDeleteShader(m_vertexShaderID);
        m_vertexShaderID = 0;
    }

    if (m_fragmentShaderID != 0)
    {
        glDeleteShader(m_fragmentShaderID);
        m_fragmentShaderID = 0;
    }

    return true;
}