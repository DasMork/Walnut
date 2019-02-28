#include "wnpch.h"

#include "Application.h"
#include "glad\glad.h"

#include "Input.h"

Walnut::Application* Walnut::Application::sInstance = nullptr;

Walnut::Application::Application()
{
	WN_CORE_ASSERT(!Application::sInstance, "Application already exists!");
	Application::sInstance = this;
	mWindow = std::unique_ptr<Window>(Window::Create());
	mWindow->SetEventCallback(WN_BIND_EVENT_FN(Walnut::Application::OnEvent));
}


Walnut::Application::~Application()
{
}

void Walnut::Application::Run()
{
	while (mRunning)
	{
		glClearColor(0.2f, 0, 0.1f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		for (Layer* layer : mLayerStack)
			layer->OnUpdate();

		if (Input::GetMouseButton(0))
			WN_CORE_LOG("Pressed Mouse Button 0");

		mWindow->OnUpdate();
	}
}

void Walnut::Application::OnEvent(Event & event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowCloseEvent>(WN_BIND_EVENT_FN(Walnut::Application::OnWindowClose));

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
	layer->OnAttach();
}

void Walnut::Application::PushOverlay(Layer * overlay)
{
	mLayerStack.PushOverlay(overlay);
	overlay->OnAttach();
}

bool Walnut::Application::OnWindowClose(WindowCloseEvent & e)
{
	mRunning = false;
	return true;
}

