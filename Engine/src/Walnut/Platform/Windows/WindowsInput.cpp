#include "wnpch.h"
#include "WindowsInput.h"
#include "Walnut\Application.h"

#include <GLFW\glfw3.h>

Walnut::Input* Walnut::Input::sInstance = new Walnut::WindowsInput();

bool Walnut::WindowsInput::GetKeyImpl(int keycode)
{
	auto window = static_cast<GLFWwindow*>(Walnut::Application::Get().GetWindow().GetNativeWindow());
	auto state = glfwGetKey(window, keycode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Walnut::WindowsInput::GetMouseButtonImpl(int button)
{
	auto window = static_cast<GLFWwindow*>(Walnut::Application::Get().GetWindow().GetNativeWindow());
	auto state = glfwGetMouseButton(window, button);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

float Walnut::WindowsInput::GetMousePosXImpl()
{
	auto[x, y] = GetMousePosImpl();
	return x;
}

float Walnut::WindowsInput::GetMousePosYImpl()
{
	auto[x, y] = GetMousePosImpl();
	return y;
}

std::pair<float, float> Walnut::WindowsInput::GetMousePosImpl()
{
	auto window = static_cast<GLFWwindow*>(Walnut::Application::Get().GetWindow().GetNativeWindow());
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
	return { (float)xPos, (float)yPos };
}
