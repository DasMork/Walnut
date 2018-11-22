#include "Application.h"


Walnut::Application::Application()
	: mRunning(true)
{
	mWindow = Walnut::Test::Window::WN_CreateWindow(640 * 2, 360 * 2, "MyNameIsWalnut");
	mRenderer = new Rendering::Renderer();
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
	-1.0f, -1.0f, 0.0f, 0.0f,
	1.0f, -1.0f,  1.0f, 0.0f,
	1.0f,  1.0f,  1.0f, 1.0f,
	-1.0f, 1.0f,  0.0f, 1.0f
	};

	unsigned int indices[] = {
		0,1,2,2,3,0
	};

	//---Create Vertex Array
	Rendering::VertexArray va;

	//---Create Vertex buffer
	Rendering::VertexBuffer vb(positions, 4 * 4 * sizeof(float));

	//Set Layout
	Rendering::VertexBufferLayout layout;
	layout.Push<float>(2);
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

	//Create and bind Texture
	Rendering::Texture texture("Walnut/images/inside.png");
	texture.Bind();

	//Set Uniform
	shader.SetUniform1i("u_Texture", 0);
	shader.SetUniform4f("u_Color", 0, 0.5f, 0, 1);

	//Draw call
	mRenderer->Draw(va, ib, shader);
}