#include "input.h"

Window* Input::m_window = nullptr;
float Input::m_xChange = 0.0f;
float Input::m_yChange = 0.0f;
float Input::m_sensitivity = 2.0f;
Entity* Input::m_entity = nullptr;
bool Input::m_disableMouse = false;

void Input::setTargetWindow(Window* window)
{
	m_window = window;
	m_xChange = 0.0f;
	m_yChange = 0.0f;

	glfwSetKeyCallback(m_window->getWindowLocation(), keyboardCallback);
	glfwSetCursorPosCallback(m_window->getWindowLocation(), mouseCallback);
}

void Input::setControlEntity(Entity* entity)
{
	m_entity = entity;
}

void Input::keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	if (key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(m_window->getWindowLocation(), true);
	}
	else
	{
		m_entity->GetComponent<Camera>().KeyBaordInputs(key);
	}		
}

void Input::DisableMouse()
{
	if (glfwGetMouseButton(m_window->getWindowLocation(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		m_disableMouse = !m_disableMouse;
		if (m_disableMouse)
		{
			glfwSetInputMode(m_window->getWindowLocation(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else
		{
			glfwSetInputMode(m_window->getWindowLocation(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

	}
}

void Input::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	m_xChange = m_sensitivity * static_cast<float>(ypos - (m_window->getHeight() / 2)) / m_window->getHeight();
	m_yChange = m_sensitivity * static_cast<float>(xpos - (m_window->getWidth() / 2)) / m_window->getWidth();

	if (m_disableMouse)
	{
		m_entity->GetComponent<Camera>().MouseInput(m_xChange, m_yChange);
	}
}