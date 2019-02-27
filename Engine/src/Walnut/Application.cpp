#include "wnpch.h"

#include "Application.h"
#include "Events/ApplicationEvent.h"

Walnut::Application::Application()
{
}


Walnut::Application::~Application()
{
}

void Walnut::Application::Run()
{
	WindowResizeEvent e(1280, 720);
	WN_LOG(e);
	for (;;)
	{
	}
	WindowCloseEvent c;
	WN_LOG(c);
}

