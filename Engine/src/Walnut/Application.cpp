#include "wnpch.h"

#include "Application.h"

#define BIND_EVENT_FN(x) std::bind(&::x, this, std::placeholders::_1)

Walnut::Application::Application()
{
	mWindow = std::unique_ptr<Window>(Window::Create());
	mWindow->SetEventCallback(BIND_EVENT_FN(Walnut::Application::OnEvent));
}


Walnut::Application::~Application()
{
}

void Walnut::Application::Run()
{
	while (mRunning)
	{
		mWindow->OnUpdate();
	}
}

void Walnut::Application::OnEvent(Event & event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Walnut::Application::OnWindowClose));

	WN_CORE_LOG(event);
}

bool Walnut::Application::OnWindowClose(WindowCloseEvent & e)
{
	mRunning = false;
	return true;
}

