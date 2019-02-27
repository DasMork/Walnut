#pragma once
#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

namespace Walnut
{
	class WALNUT_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& event);

	private:
		bool mRunning = true;
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> mWindow;
	};

	Application* CreateApplication();

}

