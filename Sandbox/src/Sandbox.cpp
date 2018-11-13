#include <Walnut.h>

class Sandbox : public Walnut::Application
{
public:
	Sandbox()
	{
		WN_LOG("Initialized Sandbox!");
	}

	~Sandbox()
	{
		WN_LOG("Shutdown Sandbox!");
	}
};


Walnut::Application* Walnut::CreateApplication()
{
	return new Sandbox();
}


