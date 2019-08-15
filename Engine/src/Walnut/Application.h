#pragma once
#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"
#include "Graphics/Shader.h"
#include "Graphics/Buffer.h"
#include "Graphics/VertexArray.h"

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
		inline Window& GetWindow() { return *mWindow; };

		inline static Application& Get() { return *sInstance; }
	private:
		bool mRunning = true;
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> mWindow;
		ImGuiLayer* mImGuiLayer;
		LayerStack mLayerStack;

		std::shared_ptr<VertexArray> mVertexArray;
		std::shared_ptr<Shader> mShader;

		static Application* sInstance;
	};

	Application* CreateApplication();

}

