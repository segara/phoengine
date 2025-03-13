#include "Graphic/ShaderProgram.h"
#include "Graphic/GraphicEngine.h"
#include <windows.h>
#include <assert.h>
#include <stdexcept>
// Include necessary DirectX headers
#include <d3d11.h>
#include <dxgi.h>


ShaderProgram::ShaderProgram(DeviceContext* deviceContext)
{
	m_deviceContext = deviceContext;
}

ShaderProgram::~ShaderProgram()
{
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
	ID3DBlob* errblob = nullptr;
	D3DCompileFromFile(ConvertToWideChar(shaderfile), nullptr, nullptr, "VS", "vs_5_0", NULL, NULL, &m_vsblob, &errblob);
	D3DCompileFromFile(ConvertToWideChar(shaderfile), nullptr, nullptr, "PS", "ps_5_0", NULL, NULL, &m_psblob, &errblob);
	m_deviceContext->getDevice()->CreateVertexShader(m_vsblob->GetBufferPointer(), m_vsblob->GetBufferSize(), nullptr, &m_vs);
	m_deviceContext->getDevice()->CreatePixelShader(m_psblob->GetBufferPointer(), m_psblob->GetBufferSize(), nullptr, &m_ps);

	m_deviceContext->getDeviceContext()->VSSetShader(m_vs, nullptr, 0);
	m_deviceContext->getDeviceContext()->PSSetShader(m_ps, nullptr, 0);

	return true;
}

void ShaderProgram::getShaderBufferAndSize(void** bytecode, size_t* size)
{
	*bytecode = this->m_vsblob->GetBufferPointer();
	*size = (size_t)this->m_vsblob->GetBufferSize();
}

void* ShaderProgram::getShaderBuffer()
{
	return this->m_vsblob->GetBufferPointer();
}

size_t ShaderProgram::getShaderSize()
{
	return (size_t)this->m_vsblob->GetBufferSize();
}

bool ShaderProgram::release()
{
}
