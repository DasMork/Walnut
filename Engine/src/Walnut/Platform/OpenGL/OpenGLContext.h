#pragma once
#include "Walnut/Graphics/Context.h"

struct GLFWwindow;

namespace Walnut
{
	class OpenGLContext : public Context
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		void Init() override;
		void SwapBuffers() override;

	private:
		GLFWwindow* mWindowHandle;
	};
}
