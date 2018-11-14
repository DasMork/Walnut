#include "Application.h"


Walnut::Application::Application()
	: mRunning(true)
{
	mWindow = Walnut::Test::Window::WN_CreateWindow(1280, 720, "MyNameIsWalnut");
}


Walnut::Application::~Application()
{
	mWindow->Close();
	WN_CORE_LOG("Shutdown Engine!");
}

void Walnut::Application::Run()
{
	while (!glfwWindowShouldClose(mWindow->GetCurrentWindow()))
	{
		mWindow->Render();
		mWindow->Clear();
	}
}

