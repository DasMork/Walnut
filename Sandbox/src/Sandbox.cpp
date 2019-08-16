#include <Walnut.h>

#include "imgui/imgui.h"

class SandboxLayer : public Walnut::Layer
{
public:
	SandboxLayer(const std::string& name)
		: Layer(name), mCamera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		//RenderTest
		mVertexArray.reset(Walnut::VertexArray::Create());

		float vertices[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			 -0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<Walnut::VertexBuffer> vertexbuffer;
		vertexbuffer.reset(Walnut::VertexBuffer::Create(vertices, sizeof(vertices)));

		Walnut::BufferLayout layout = {
			{Walnut::ShaderDataType::Float3, "aPosition"},
			{Walnut::ShaderDataType::Float4, "aColor"}
		};

		vertexbuffer->SetLayout(layout);

		mVertexArray->AddVertexBuffer(vertexbuffer);

		uint32_t indices[6] = { 0,1,2,0,2,3 };

		std::shared_ptr<Walnut::IndexBuffer> indexBuffer;
		indexBuffer.reset(Walnut::IndexBuffer::Create(indices, 6));
		mVertexArray->SetIndexBuffer(indexBuffer);

		mShader.reset(new Walnut::Shader());
	}

	void OnImGuiRender(Walnut::Timestep ts) override
	{
		bool show = true;
		ShowStatsWindow(&show, ts);
	}

	void OnEvent(Walnut::Event& event) override
	{
		Walnut::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Walnut::KeyPressedEvent>(WN_BIND_EVENT_FN(SandboxLayer::OnKeyPressed));
	}

	bool OnKeyPressed(Walnut::KeyPressedEvent& event)
	{
		return false;
	}

	void OnUpdate(Walnut::Timestep ts) override
	{
		//RenderTest
		Walnut::RenderCommand::SetClearColor({ 0.2f, 0, 0.1f, 1 });
		Walnut::RenderCommand::Clear();

		float x = 0, y = 0, r = 0;
		float cameraMoveSpeed = 2;

		if (Walnut::Input::GetKey(WN_KEY_D))
			x += cameraMoveSpeed * ts.GetSeconds();
		if (Walnut::Input::GetKey(WN_KEY_A))
			x -= cameraMoveSpeed * ts.GetSeconds();

		if (Walnut::Input::GetKey(WN_KEY_W))
			y += cameraMoveSpeed * ts.GetSeconds();
		if (Walnut::Input::GetKey(WN_KEY_S))
			y -= cameraMoveSpeed * ts.GetSeconds();

		if (Walnut::Input::GetKey(WN_KEY_E))
			r -= cameraMoveSpeed * ts.GetSeconds();
		if (Walnut::Input::GetKey(WN_KEY_Q))
			r += cameraMoveSpeed * ts.GetSeconds();


		mCamera.SetPosition(mCamera.GetPosition() + glm::vec3(x, y, 0));
		mCamera.SetRotation(mCamera.GetRotation() + r);

		Walnut::Renderer::BeginScene(mCamera);
		Walnut::Renderer::Submit(mShader, mVertexArray, glm::mat4(1.0f));
		Walnut::Renderer::EndScene();
	}

	void ShowStatsWindow(bool* p_open, Walnut::Timestep ts) const
	{
		// FIXME-VIEWPORT-ABS: Select a default viewport
		const float DISTANCE = 10.0f;
		static int corner = 0;
		ImGuiIO& io = ImGui::GetIO();
		if (corner != -1)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImVec2 window_pos = ImVec2((corner & 1) ? (viewport->Pos.x + viewport->Size.x - DISTANCE) : (viewport->Pos.x + DISTANCE), (corner & 2) ? (viewport->Pos.y + viewport->Size.y - DISTANCE) : (viewport->Pos.y + DISTANCE));
			ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
			ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
			ImGui::SetNextWindowViewport(viewport->ID);
		}
		ImGui::SetNextWindowBgAlpha(0.3f); // Transparent background
		if (ImGui::Begin("Example: Simple overlay", p_open, (corner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
		{
			ImGui::Text("FPS: %.0f", 1.0f / ts.GetSeconds());
			ImGui::Text("Time Step: %.2f ms", ts.GetMilliSeconds());
			if (ImGui::BeginPopupContextWindow())
			{
				if (ImGui::MenuItem("Custom", NULL, corner == -1)) corner = -1;
				if (ImGui::MenuItem("Top-left", NULL, corner == 0)) corner = 0;
				if (ImGui::MenuItem("Top-right", NULL, corner == 1)) corner = 1;
				if (ImGui::MenuItem("Bottom-left", NULL, corner == 2)) corner = 2;
				if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
				if (p_open && ImGui::MenuItem("Close")) *p_open = false;
				ImGui::EndPopup();
			}
		}
		ImGui::End();
	}

private:
	std::shared_ptr<Walnut::VertexArray> mVertexArray;
	std::shared_ptr<Walnut::Shader> mShader;

	Walnut::OrthographicCamera mCamera;
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