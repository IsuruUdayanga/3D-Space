#include "Window.h"

Window::Window(std::string title)
{
	if (initWindow(title.c_str()) != 0)
		return;
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

int Window::initWindow(const char* title)
{
	if (!glfwInit()) {

		printf("GLFW initialization failed!\n");
		glfwTerminate();
		return 1;
	}

	// Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
	// GL ES 2.0 + GLSL 100
	const char* glsl_version = "#version 100";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
	// GL 3.2 + GLSL 150
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 410";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	m_width = mode->width;
	m_height = mode->height;

	m_window = glfwCreateWindow(m_width, m_height, title, nullptr, nullptr);
	if (!m_window) {
		printf("GLFW Window creation failed!\n");
		glfwTerminate();
		return 2;
	}

	glfwGetFramebufferSize(m_window, &m_bufferW, &m_bufferH);
	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1);
	//glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		printf("GLEW initialization failed!\n");
		glfwDestroyWindow(m_window);
		glfwTerminate();
		return 3;
	}

	glViewport(0, 0, m_bufferW, m_bufferH);
	printf("GLFW and GLEW successfully initialized\n");

	glEnable(GL_DEPTH_TEST);
	return 0;
}

bool Window::isRunning()
{
	return glfwWindowShouldClose(m_window);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(m_window);
}

void Window::pollEvents()
{
	glfwPollEvents();
}

GLFWwindow* Window::getWindowLocation() const
{
	return m_window;
}

int Window::getBufferWidth() const
{
	return m_bufferW;
}
int Window::getBufferHeight() const
{
	return m_bufferH;
}

int Window::getWidth() const
{
	return m_width;
}

int Window::getHeight() const
{
	return m_height;
}