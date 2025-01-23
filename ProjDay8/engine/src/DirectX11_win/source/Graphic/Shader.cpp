#include "Graphic/Shader.h"
#include "Graphic/GraphicEngine.h"
#include <windows.h>
#include <assert.h>
#include <stdexcept>
// Include necessary DirectX headers
#include <d3d11.h>
#include <dxgi.h>


Shader::Shader(DeviceContext* deviceContext)
{
	m_deviceContext = deviceContext;
}

Shader::~Shader()
{
}

bool Shader::load(const wchar_t* shaderfile)
{
	ID3DBlob* errblob = nullptr;
	D3DCompileFromFile(shaderfile, nullptr, nullptr, "vsmain", "vs_5_0", NULL, NULL, &m_vsblob, &errblob);
	D3DCompileFromFile(shaderfile, nullptr, nullptr, "psmain", "ps_5_0", NULL, NULL, &m_psblob, &errblob);
	m_deviceContext->getDevice()->CreateVertexShader(m_vsblob->GetBufferPointer(), m_vsblob->GetBufferSize(), nullptr, &m_vs);
	m_deviceContext->getDevice()->CreatePixelShader(m_psblob->GetBufferPointer(), m_psblob->GetBufferSize(), nullptr, &m_ps);

	m_deviceContext->getDeviceContext()->VSSetShader(m_vs, nullptr, 0);
	m_deviceContext->getDeviceContext()->PSSetShader(m_ps, nullptr, 0);

	return true;
}

void Shader::getShaderBufferAndSize(void** bytecode, UINT* size)
{
	*bytecode = this->m_vsblob->GetBufferPointer();
	*size = (UINT)this->m_vsblob->GetBufferSize();
}

void* Shader::getShaderBuffer()
{
	return this->m_vsblob->GetBufferPointer();
}

UINT Shader::getShaderSize()
{
	return (UINT)this->m_vsblob->GetBufferSize();
}
