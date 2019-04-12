#include <Walnut.h>

#include "ImGui/imgui.h"
class SandboxLayer : public Walnut::Layer
{
public:
	SandboxLayer(const std::string& name)
		: Layer(name)
	{

	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::TextUnformatted("Hello World");
		ImGui::End();
	}
};

class Sandbox : public Walnut::Application
{
public:
	Sandbox()
	{
		PushOverlay(new SandboxLayer("SandboxLayer"));
		WN_LOG("Initialized Sandbox!");
	}

	~Sandbox()
	{

	}
};



Walnut::Application* Walnut::CreateApplication()
{
	return new Sandbox();
}