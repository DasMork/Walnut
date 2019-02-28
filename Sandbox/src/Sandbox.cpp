#include <Walnut.h>

class Sandbox : public Walnut::Application
{
public:
	Sandbox()
	{
		PushOverlay(new Walnut::ImGuiLayer());
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