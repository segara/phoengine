#ifndef __TRIANGLEDEMO_H__
#define __TRIANGLEDEMO_H__
#pragma once
#include <memory>

class GraphicEngine;
class ShaderProgram;
class DeviceContext;
class TriangleDemo
{
public:
	TriangleDemo(const std::shared_ptr<GraphicEngine>& engine);
	~TriangleDemo();

	 void onCreate();
	 void onUpdate();
	 void onDestroy();

	std::shared_ptr <GraphicEngine> m_engine;
    std::shared_ptr <ShaderProgram> shader;

};
#endif
