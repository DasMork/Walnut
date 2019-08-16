#include "wnpch.h"

#include "Application.h"
#include "Graphics/RenderCommand.h"
#include "Graphics/Renderer.h"
#include "Input.h"
#include "KeyCodes.h"
#include "GLFW/glfw3.h"

Walnut::Application* Walnut::Application::sInstance = nullptr;



Walnut::Application::Application()
{
	WN_CORE_ASSERT(!Application::sInstance, "Application already exists!");
	sInstance = this;
	mWindow = std::unique_ptr<Window>(Window::Create());
	mWindow->SetEventCallback(WN_BIND_EVENT_FN(Walnut::Application::OnEvent));

	mImGuiLayer = new ImGuiLayer();
	PushOverlay(mImGuiLayer);
}


Walnut::Application::~Application()
{
}

void Walnut::Application::Run()
{
	while (mRunning)
	{
		float time = (float)glfwGetTime(); //TODO Move to Platform::GetTime
		Timestep timestep = time - mLastFrameTime;
		mLastFrameTime = time;

		for (Layer* layer : mLayerStack)
			layer->OnUpdate(timestep);

		mImGuiLayer->Begin();
		for (Layer* layer : mLayerStack)
			layer->OnImGuiRender(timestep);
		mImGuiLayer->End();


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

