#include "Application.h"
#include "Rendering.h"


Walnut::Application::Application()
	: mRunning(true)
{
	mWindow = Walnut::Test::Window::WN_CreateWindow(640, 360, "MyNameIsWalnut");
	Start();
}

Walnut::Application::~Application()
{
	mWindow->Close();
	WN_CORE_LOG("Shutdown Engine!");
}

void Walnut::Application::Run()
{
	while (!glfwWindowShouldClose(mWindow->GetCurrentWindow()))
	{
		mWindow->Clear();
		Render();
		mWindow->SwapBuffer();
	}
}
struct ShaderSources
{
	std::string VertexSource;
	std::string FragmentSource;
};

void Walnut::Application::Start()
{
}

void Walnut::Application::Render()
{
	float positions[] = {
	-0.5f, -0.5f,
	0.5f, -0.5f,
	0.5f,  0.5f,
	-0.5f, 0.5f
	};

	unsigned int indices[] = {
		0,1,2,2,3,0
	};

	//---Create Vertex Array
	Rendering::VertexArray va;

	//---Create Vertex buffer
	Rendering::VertexBuffer vb(positions, 4 * 2 * sizeof(float));

	//Set Layout
	Rendering::VertexBufferLayout layout;
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	//---Create IndexBuffer
	Rendering::IndexBuffer ib(indices, 6);

	//---Clear all buffers
	va.Unbind();
	vb.Unbind();
	ib.Unbind();

	//Bind only Vertex array and index buffer
	va.Bind();
	ib.Bind();

	//Load Shader
	Rendering::Shader shader("Walnut/shaders/default");

	//Set Uniform
	shader.SetUniform4f("u_Color", 0, 0.5f, 0, 1);

	//Draw call
	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}