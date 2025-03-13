#pragma once
#include <Windows.h>
#include <minwindef.h>
#include <Vec4.h>
#include <d3d11.h>
#include <dxgi.h>

class VertexBuffer;

class DeviceContext
{
public:
	DeviceContext(ID3D11Device* d3d_device, ID3D11DeviceContext* device_context);
	void createVertexBuffer(void* list_vertices, UINT size_vertex_struct, UINT size_list, void* shader_byte_code, UINT size_shader);
	VertexBuffer* getVertexBuffer();

	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);


	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();
	bool release();
	~DeviceContext();
private:
	//렌더링 명령(그리기 명령, 상태 설정 등)을 GPU에 전달합니다.
	//리소스 바인딩 및 셰이더 설정을 관리합니다.
	//뷰포트 설정 및 렌더 타겟을 관리합니다.
	ID3D11DeviceContext* m_device_context;


	//Direct3D 리소스(버퍼, 텍스처, 셰이더 등)를 생성하고 관리할 수 있습니다.
	//주요 역할 :
	//렌더링에 필요한 그래픽 리소스를 생성합니다.
	//GPU에 작업을 지시하는 명령을 준비합니다.
	//Direct3D 11 기능 수준을 설정합니다.
	ID3D11Device* m_d3d_device;
	VertexBuffer* m_vb;
};