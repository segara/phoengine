#pragma once
#include <memory>
#include <Windows.h>
#include "Graphic/GraphicEngine.h"
#include "Graphic/VertexBuffer.h"


class TriangleDemo
{
public:
	TriangleDemo(const std::shared_ptr<GraphicEngine>& engine);
	~TriangleDemo();

	 void onCreate();
	 void onUpdate();
	 void onDestroy();
private:
	GraphicEngine* m_engine;

};