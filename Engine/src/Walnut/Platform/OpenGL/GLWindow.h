#pragma once
#include "Walnut/Window.h"

#include <GLFW/glfw3.h>
#include "Walnut/Graphics/Context.h"

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

		void SetEventCallback(const EventCallbackFn & callback) override
		{
			mData.EventCallback = callback;
		};
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline void* GetNativeWindow() const override { return mWindow; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow * mWindow;
		Context* mContext;

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
