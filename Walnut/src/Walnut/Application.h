#pragma once

#include <GLFW/glfw3.h>
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
	};

	Application* CreateApplication();
}

