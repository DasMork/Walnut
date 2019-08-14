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
}

void Walnut::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(mWindowHandle);
}
