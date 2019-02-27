#include "wnpch.h"

#include "GLWindow.h"

#include "Walnut/Events/ApplicationEvent.h"
#include "Walnut/Events/KeyEvent.h"
#include "Walnut/Events/MouseEvent.h"
#include "glad/glad.h"

static bool sGLFWInitialized;

static void GLFWErrorCallback(int error, const char* description)
{
	WN_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

Walnut::Window* Walnut::Window::Create(const WindowProps& props)
{
	return new GLWindow(props);
}


Walnut::GLWindow::GLWindow(const WindowProps & props)
{
	Init(props);
}

Walnut::GLWindow::~GLWindow()
{
	Shutdown();
}

void Walnut::GLWindow::OnUpdate()
{
	glClearColor(0.2f, 0, 0.1f, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwPollEvents();
	glfwSwapBuffers(mWindow);
}

unsigned int Walnut::GLWindow::GetWidth() const
{
	return 0;
}

unsigned int Walnut::GLWindow::GetHeight() const
{
	return 0;
}

void Walnut::GLWindow::SetVSync(bool enabled)
{
	if (enabled)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	mData.VSync = enabled;
}

bool Walnut::GLWindow::IsVSync() const
{
	return mData.VSync;
}

void Walnut::GLWindow::Init(const WindowProps & props)
{
	mData.Title = props.Title;
	mData.Width = props.Width;
	mData.Height = props.Height;

	WN_CORE_LOG("Creating Window '{0}' ({1}, {2})", props.Title, props.Width, props.Height);

	if (!sGLFWInitialized)
	{
		int succes = glfwInit();
		WN_CORE_ASSERT(succes, "Could not initalize GLFW");

		sGLFWInitialized = true;
	}

	mWindow = glfwCreateWindow((int)mData.Width, (int)mData.Height, mData.Title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(mWindow);

	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	WN_CORE_ASSERT(status, "Failed to initalize Glad!");
	glfwSetWindowUserPointer(mWindow, &mData);
	SetVSync(true);

	//Set GLFW Callbacks
	glfwSetErrorCallback(GLFWErrorCallback);

	glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		data.Width = width;
		data.Height = height;

		WindowResizeEvent event(width, height);
		data.EventCallback(event);
	});

	glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		WindowCloseEvent event;
		data.EventCallback(event);
	});

	glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
		case GLFW_PRESS:
		{
			KeyPressedEvent event(key, 0);
			data.EventCallback(event);
			break;
		}
		case GLFW_RELEASE:
		{
			KeyReleasedEvent event(key, 0);
			data.EventCallback(event);
			break;
		}
		case GLFW_REPEAT:
		{
			KeyPressedEvent event(key, 1);
			data.EventCallback(event);
			break;
		}
		}
	});

	glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
		case GLFW_PRESS:
		{
			MouseButtonPressedEvent event(button);
			data.EventCallback(event);
			break;
		}
		case GLFW_RELEASE:
		{
			MouseButtonReleasedEvent event(button);
			data.EventCallback(event);
		}
		}
	});

	glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xOffset, double yOffset)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		MouseScrolledEvent event((float)xOffset, (float)yOffset);
		data.EventCallback(event);
	});

	glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double xPos, double yPos)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		MouseMovedEvent event((float)xPos, (float)yPos);
		data.EventCallback(event);
	});
}

void Walnut::GLWindow::Shutdown()
{
	glfwDestroyWindow(mWindow);
}
