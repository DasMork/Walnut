#pragma once

#ifdef WN_PLATFORM_WINDOWS

extern Walnut::Application* Walnut::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Walnut::CreateApplication();
	app->Run();
	delete app;
}

#else
#error 
#endif