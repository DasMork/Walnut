#include "wnpch.h"

#include "Application.h"
#include "glad\glad.h"

Walnut::Application* Walnut::Application::sInstance = nullptr;



Walnut::Application::Application()
{
	WN_CORE_ASSERT(!Application::sInstance, "Application already exists!");
	sInstance = this;
	mWindow = std::unique_ptr<Window>(Window::Create());
	mWindow->SetEventCallback(WN_BIND_EVENT_FN(Walnut::Application::OnEvent));

	mImGuiLayer = new ImGuiLayer();
	PushOverlay(mImGuiLayer);

	//RenderTest
	mVertexArray.reset(VertexArray::Create());

	float vertices[4 * 7] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, 0.0f, 0.5f, 1.0f, 1.0f, 1.0f,
		 -0.5f,  0.5f, 0.0f,0.0f, 0.5f, 1.0f, 1.0f
	};
	std::shared_ptr<VertexBuffer> vertexbuffer;
	vertexbuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

	BufferLayout layout = {
		{ShaderDataType::Float3, "aPosition"},
		{ShaderDataType::Float4, "aColor"}
	};

	vertexbuffer->SetLayout(layout);

	mVertexArray->AddVertexBuffer(vertexbuffer);

	uint32_t indices[6] = { 0,1,2,0,2,3 };

	std::shared_ptr<IndexBuffer> indexBuffer;
	indexBuffer.reset(IndexBuffer::Create(indices, 6));
	mVertexArray->SetIndexBuffer(indexBuffer);

	std::string vertexSrc = R"(
		#version 330 core
		
		layout(location = 0) in vec3 aPosition;
		layout(location = 1) in vec4 aColor;
		
		out vec3 vPosition;
		out vec4 vColor;

		void main()
		{
			vPosition = aPosition;
			vColor = aColor;

			gl_Position = vec4(aPosition, 1.0);
		}
	)";

	std::string fragentSrc = R"(
		#version 330 core
		
		layout(location = 0) out vec4 oColor;
		
		in vec3 vPosition;
		in vec4 vColor;

		void main()
		{
			oColor = vColor;
		}
	
	)";

	mShader.reset(new Shader(vertexSrc, fragentSrc));
}


Walnut::Application::~Application()
{
}

void Walnut::Application::Run()
{
	while (mRunning)
	{
		glClearColor(0.2f, 0, 0.1f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		//RenderTest
		mShader->Bind();
		mVertexArray->Bind();
		glDrawElements(GL_TRIANGLES, mVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

		for (Layer* layer : mLayerStack)
			layer->OnUpdate();

		mImGuiLayer->Begin();
		for (Layer* layer : mLayerStack)
			layer->OnImGuiRender();
		mImGuiLayer->End();


		mWindow->OnUpdate();
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

