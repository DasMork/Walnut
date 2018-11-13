#pragma once

#include "Core.h"
#include <GLFW/glfw3.h>

namespace Walnut {
	namespace Test {

		class WALNUT_API  Window
		{
		private:
			bool mOpen;
			GLFWwindow* mWindow;
			Window(GLFWwindow* window);
			virtual ~Window();
		public:
			static Window* WN_CreateWindow(const int width, const int height, const char* name);

			void Render();
			void Clear();
			void Close();

			inline GLFWwindow* GetCurrentWindow() { return mWindow; }
		};
	}
}

