#pragma once

#include "Log.h"
#include "Window.h"

#ifdef WN_PLATFORM_WINDOWS

extern Walnut::Application* Walnut::CreateApplication();

int main(int argc, char** argv)
{
	Walnut::Log::Init();
	WN_CORE_LOG("Initialized Engine!");

	auto app = Walnut::CreateApplication();
	app->Run();
	delete app;
	system("pause");


}
#else
#error Walnut only supports Windows at the moment!
#endif