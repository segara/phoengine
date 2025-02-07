#pragma once
#include <memory>
#include "Graphic/GraphicEngine.h"
#include "Graphic/VertexBuffer.h"
#include "ShaderProgram.h"

class TriangleDemo
{
public:
	TriangleDemo(const std::shared_ptr<GraphicEngine>& engine);
	~TriangleDemo();

	 void onCreate();
	 void onUpdate();
	 void onDestroy();
private:
	std::shared_ptr <GraphicEngine> m_engine;
	std::shared_ptr<ShaderProgram> shader;
};