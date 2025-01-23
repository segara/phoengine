#pragma once
#include <Windows.h>
#include <Vec4.h>
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>

class DeviceContext;

class Shader
{
public:
	Shader(DeviceContext* deviceContext);
	~Shader();
	bool load(const wchar_t* shaderfile);
	void getShaderBufferAndSize(void** bytecode, UINT* size);
	void* getShaderBuffer();
	UINT getShaderSize();
	DeviceContext* m_deviceContext = nullptr;

	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;
};

