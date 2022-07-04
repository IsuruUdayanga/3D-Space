#pragma once

#include "3D Space.h"

class Window
{
public:
	Window(std::string title);
	~Window();

	int initWindow(const char* title);
	bool isRunning();
	void swapBuffers();
	void pollEvents();
	GLFWwindow* getWindowLocation() const;

	int getBufferWidth() const;
	int getBufferHeight() const;

	int getWidth() const;
	int getHeight() const;

public:
	static const int WINDOW_WIDTH = 800;
	static const int WINDOW_HEIGHT = 600;

private:
	GLFWwindow* m_window;
	int m_width, m_height;
	int m_bufferW, m_bufferH;
};