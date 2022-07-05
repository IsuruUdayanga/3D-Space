#pragma once

#include "window.h"
#include "Component.h"

class Input
{
public:
	static void setTargetWindow(Window* window);
	static void setControlEntity(Entity* entity);
	static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	static void DisableMouse();

private:
	static Window* m_window;
	static Entity* m_entity;
	static float m_xChange;
	static float m_yChange;
	static float m_sensitivity;
	static bool m_disableMouse;
};