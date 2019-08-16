#include "wnpch.h"

#include "Application.h"
#include "Graphics/RenderCommand.h"
#include "Graphics/Renderer.h"
#include "Input.h"
#include "KeyCodes.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "imgui.h"

Walnut::Application* Walnut::Application::sInstance = nullptr;



Walnut::Application::Application()
{
	WN_CORE_ASSERT(!Application::sInstance, "Application already exists!");
	sInstance = this;
	mWindow = std::unique_ptr<Window>(Window::Create({ "Walnut", 1600, 900 }));
	mWindow->SetEventCallback(WN_BIND_EVENT_FN(Walnut::Application::OnEvent));

	mImGuiLayer = new ImGuiLayer();
	PushOverlay(mImGuiLayer);
}


Walnut::Application::~Application()
{
}

void Walnut::Application::Run()
{
	while (mRunning)
	{
		float time = (float)glfwGetTime(); //TODO Move to Platform::GetTime
		Timestep timestep = time - mLastFrameTime;
		mLastFrameTime = time;

		RenderCommand::Clear();

		//Frame Buffer
		unsigned int fbo;
		glGenFramebuffers(1, &fbo);

		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		RenderCommand::Clear();

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1600, 900, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

		for (Layer* layer : mLayerStack)
			layer->OnUpdate(timestep);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDeleteFramebuffers(1, &fbo);


		mImGuiLayer->Begin();



		for (Layer* layer : mLayerStack)
			layer->OnImGuiRender(timestep);
		//create our ImGui window
		//ImGuiWindowFlags flags = ImGuiWindowFlags_
		ImGui::Begin("Scene Window");

		//pass the texture of the FBO
		//window.getRenderTexture() is the texture of the FBO
		//the next parameter is the upper left corner for the uvs to be applied at
		//the third parameter is the lower right corner
		//the last two parameters are the UVs
		//they have to be flipped (normally they would be (0,0);(1,1) 
		ImGui::GetWindowDrawList()->AddImage(
			(void *)texture,
			ImVec2(ImGui::GetCursorScreenPos()),
			ImVec2(ImGui::GetCursorScreenPos().x + 1280,
				ImGui::GetCursorScreenPos().y + 720), ImVec2(0, 1), ImVec2(1, 0));

		//we are done working with this window
		ImGui::End();
		mImGuiLayer->End();



		mWindow->OnUpdate();
		glDeleteTextures(1, &texture);
	}
}

void Walnut::Application::OnEvent(Event & event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowCloseEvent>(WN_BIND_EVENT_FN(Walnut::Application::OnWindowClose));

	for (auto it = mLayerStack.end(); it != mLayerStack.begin();)
	{
		(*--it)->OnEvent(event);
		if (event.Handled)
			break;
	}
}

void Walnut::Application::PushLayer(Layer * layer)
{
	mLayerStack.PushLayer(layer);
	layer->OnAttach();
}

void Walnut::Application::PushOverlay(Layer * overlay)
{
	mLayerStack.PushOverlay(overlay);
	overlay->OnAttach();
}

bool Walnut::Application::OnWindowClose(WindowCloseEvent & e)
{
	mRunning = false;
	return true;
}

