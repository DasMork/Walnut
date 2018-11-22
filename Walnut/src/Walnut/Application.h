#pragma once

#include "Core.h"
#include "Log.h"
#include "Window.h"
#include "Rendering.h"


namespace Walnut {

	class WALNUT_API Application
	{
	private:
		bool mRunning;
		Test::Window * mWindow;
		Rendering::Renderer* mRenderer;
	public:
		Application();
		virtual ~Application();

		void Run();
		virtual void Start();
		virtual void Render();
	};

	Application* CreateApplication();
}

