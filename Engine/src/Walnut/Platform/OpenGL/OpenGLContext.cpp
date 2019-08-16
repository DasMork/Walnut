#include "wnpch.h"
#include "OpenGLContext.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"

Walnut::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	: mWindowHandle(windowHandle)
{
}

void Walnut::OpenGLContext::Init()
{
	glfwMakeContextCurrent(mWindowHandle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	WN_CORE_ASSERT(status, "Failed to initalize Glad!");

	WN_CORE_LOG("OpenGL Info: ");
	WN_CORE_LOG("Renderer: {0}", glGetString(GL_RENDERER));
	WN_CORE_LOG("Version: {0}", glGetString(GL_VERSION));
}

void Walnut::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(mWindowHandle);
}
