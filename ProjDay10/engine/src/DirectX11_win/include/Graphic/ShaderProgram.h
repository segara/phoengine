#pragma once
#include <Windows.h>
#include <Vec4.h>
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>

class DeviceContext;

class ShaderProgram
{
public:
	ShaderProgram(DeviceContext* deviceContext);
	~ShaderProgram();
	bool load(const char* shaderfile);
	void getShaderBufferAndSize(void** bytecode, size_t* size);
	void* getShaderBuffer();
	size_t getShaderSize();
	bool release();

	DeviceContext* m_deviceContext = nullptr;

	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;
};

