#pragma once
#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"

namespace Walnut
{
	class WALNUT_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:
		bool mRunning = true;
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> mWindow;
		LayerStack mLayerStack;
	};

	Application* CreateApplication();

}

