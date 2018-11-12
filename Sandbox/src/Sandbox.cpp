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

	}
};


Walnut::Application* Walnut::CreateApplication()
{
	return new Sandbox();
}


