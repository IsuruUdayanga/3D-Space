#pragma once

#include "Window.h"
#include "Model.h"
#include "Input.h"

class Application
{
public:
	Application(const char* title);
	~Application();

	void Run();
	void DockSpace();
	void SceneView();

private:
	Window* m_window{ nullptr };
	Model* m_model{ nullptr };
	bool m_disableMouse;
};