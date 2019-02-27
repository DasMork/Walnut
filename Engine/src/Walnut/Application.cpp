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
		for (Layer* layer : mLayerStack)
			layer->OnUpdate();

		mWindow->OnUpdate();
	}
}

void Walnut::Application::OnEvent(Event & event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Walnut::Application::OnWindowClose));

	WN_CORE_LOG(event);

	for (auto it = mLayerStack.end(); it != mLayerStack.begin();)
	{
		(*--it)->OnEvent(event);
		if (event.Handled)
			break;
	}
}

void Walnut::Application::PushLayer(Layer * layer)
{
	mLayerStack.PushLayer(layer);
}

void Walnut::Application::PushOverlay(Layer * overlay)
{
	mLayerStack.PushOverlay(overlay);
}

bool Walnut::Application::OnWindowClose(WindowCloseEvent & e)
{
	mRunning = false;
	return true;
}

