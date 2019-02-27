#pragma once
#include "Walnut/Window.h"

#include <GLFW/glfw3.h>

namespace Walnut
{
	class GLWindow : public Window
	{
	public:
		GLWindow(const WindowProps& props);
		virtual ~GLWindow();

		void OnUpdate() override;

		unsigned int GetWidth() const override;
		unsigned int GetHeight() const override;

		virtual void SetEventCallback(const EventCallbackFn & callback) override
		{
			mData.EventCallback = callback;
		};
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow * mWindow;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData mData;
	};
}