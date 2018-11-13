#include "Window.h"
#include "Log.h"

Walnut::Test::Window::Window(GLFWwindow* window)
{
	mWindow = window;
}
Walnut::Test::Window::~Window() 
{

}

Walnut::Test::Window* Walnut::Test::Window::WN_CreateWindow(const int width, const int height, const char* name)
{
	GLFWwindow* window = nullptr;

	if (!glfwInit())
		WN_CORE_ERROR("Failed to init GLFW!");

	window = glfwCreateWindow(width, height, name, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		WN_CORE_ERROR("Failed to create GLFW Window!");
	}

	glfwMakeContextCurrent(window);
	WN_CORE_LOG("Created GLFW Window!");
	return new Window(window);
}

void Walnut::Test::Window::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0, 0.5f);
	glEnd();
}

void Walnut::Test::Window::Clear()
{

	glfwSwapBuffers(mWindow);
	glfwPollEvents();

}

void Walnut::Test::Window::Close()
{
	mOpen = false;
	glfwTerminate();
	WN_CORE_LOG("Closed GLFW Window!");
}


