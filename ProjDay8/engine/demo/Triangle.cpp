﻿#include "Vec3.h"
#include "Shader.h"
#include "Triangle.h"
#include <d3d11.h>
#include <VertexBuffer.h>
#include <DeviceContext.h>
#include <filesystem>
#include <iostream>
#include <ostream>

struct vertex
{
	Vec3 position;
};

TriangleDemo::TriangleDemo(const std::shared_ptr<GraphicEngine>& engine)
{
	m_engine = engine.get();
}


TriangleDemo::~TriangleDemo()
{
}

void TriangleDemo::onCreate()
{
	vertex list[] = 
	{
		//X - Y - Z
		Vec3{-0.5f,-0.5f,0.0f}, // POS1
		Vec3{0.0f,0.5f,0.0f}, // POS2
		Vec3{ 0.5f,-0.5f,0.0f}
	};
	
	UINT size_list = ARRAYSIZE(list);

	// C++17 std::filesystem 사용
	std::cout << "Current directory (std::filesystem): " << std::filesystem::current_path() << std::endl;

	Shader* shader = new Shader(m_engine->m_deviceContext);

	shader->load(L"../demo/shader.fx");

	m_engine->m_deviceContext->createVertexBuffer(list, sizeof(vertex), size_list, shader->getShaderBuffer(), shader->getShaderSize());
	
}

void TriangleDemo::onUpdate()
{

	//// FINALLY DRAW THE TRIANGLE
	///현재 월드 -> 카메라 -> 클립 변환이 없이 그대로 ndc까지 값전달
	///Normalized Device Coordinates (NDC)를 Viewport Space로 변환하는 식은 DirectX의 뷰포트 변환 공식에 따라 계산됩니다.
	///이 과정은 NDC에서 뷰포트 공간으로 매핑되는 과정으로, 화면 좌표계에서의 위치를 결정합니다.
	m_engine->m_deviceContext->drawTriangleList(m_engine->m_deviceContext->getVertexBuffer()->getSizeVertexList(), 0);

}

void TriangleDemo::onDestroy()
{
	m_engine->m_deviceContext->getVertexBuffer()->release();
}