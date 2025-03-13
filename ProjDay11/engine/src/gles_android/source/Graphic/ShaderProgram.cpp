#include "ShaderProgram.h"
#include "DeviceContext.h"
#include <iostream>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/native_activity.h>
#include <android_native_app_glue.h>
ShaderProgram::ShaderProgram(DeviceContext* deviceContext)
    : m_deviceContext(deviceContext),m_programID(0), m_vertexShaderID(0), m_fragmentShaderID(0)
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

std::string ReadFromAsset(AAssetManager* assetManager, const std::string& filename) {

    if (!assetManager) {
        //LOGE("AssetManager is NULL!");
        return "";
    }

    AAsset* asset = AAssetManager_open(assetManager, filename.c_str(), AASSET_MODE_BUFFER);
    if (!asset) {
        //LOGE("Failed to open asset: %s", filename.c_str());
        return "";
    }

    size_t fileSize = AAsset_getLength(asset);
    std::string fileContent(fileSize, '\0');

    AAsset_read(asset, &fileContent[0], fileSize);
    AAsset_close(asset);

    return fileContent;
}
std::string GetFileNameWithoutExtension(const std::string& filepath, const std::string& extension) {
    // 경로에서 파일명만 추출
    size_t lastSlash = filepath.find_last_of("/\\");
    std::string filename = (lastSlash == std::string::npos) ? filepath : filepath.substr(lastSlash + 1);

    // 확장자 제거
    size_t extPos = filename.rfind(extension);
    if (extPos != std::string::npos) {
        filename = filename.substr(0, extPos);
    }

    return filename;
}
bool ShaderProgram::load(const char* shaderfile)
{
    android_app* app = ( android_app*)(m_deviceContext->m_nativeApp);
    ANativeActivity* nativeActivity = app->activity;
    AAssetManager* assetManager = nativeActivity->assetManager;

    std::string vs = ReadFromAsset(assetManager, GetFileNameWithoutExtension(shaderfile,".fx")+"_vs.glsl");
    std::string ps = ReadFromAsset(assetManager, GetFileNameWithoutExtension(shaderfile,".fx")+"_ps.glsl");
    // Compile vertex shader
    m_vertexShaderID = compileShader(vs.c_str(), GL_VERTEX_SHADER);
    if (!m_vertexShaderID)
        return false;

    // Compile fragment shader
    m_fragmentShaderID = compileShader(ps.c_str(), GL_FRAGMENT_SHADER);
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