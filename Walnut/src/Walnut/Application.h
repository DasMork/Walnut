#pragma once

#include <fstream>
#include <sstream>
#include "Core.h"
#include "Window.h"
#include "Log.h"


namespace Walnut {

	class WALNUT_API Application
	{
	private:
		bool mRunning;
		Test::Window * mWindow;
	public:
		Application();
		virtual ~Application();

		void Run();
		virtual void Start();
		virtual void Render();
	};

	Application* CreateApplication();
}

