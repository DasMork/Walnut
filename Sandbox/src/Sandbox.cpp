#include <Walnut.h>

#include "ImGui/imgui.h"
#include "Walnut/Platform/OpenGL/GLShader.h"
#include <glm/gtc/type_ptr.hpp>



class SandboxLayer : public Walnut::Layer
{
public:
	SandboxLayer(const std::string& name)
		: Layer(name), mSquareColor({ 0,0,0 }), mSquareColor2({ 0,0,0 })
	{
		//mCamera.reset(new Walnut::OrthographicCamera(0, 16, 0, 9));
		mCamera.reset(new Walnut::PerspectiveCamera(65, 16, 9, 0.1f, 100));
		//mCamera->SetPosition({ 16, 9, 2 });
		mCamera->SetPosition(glm::vec3(8, 4.5f, 10));
		auto square = std::make_shared<Walnut::Square>();
		square->SetPosition(glm::vec3(0, 0, 0));

		auto square2 = std::make_shared<Walnut::Square>();
		square2->SetPosition(glm::vec3(3, 2, 0));

		auto square3 = std::make_shared<Walnut::Square>();
		square3->SetPosition(glm::vec3(8, 4, 0));

		mSquares.push_back(square);
		mSquares.push_back(square2);
		mSquares.push_back(square3);

		Walnut::RenderCommand::EnableDepthTesting();
	}

	void OnImGuiRender(Walnut::Timestep ts) override
	{
		bool show = true;
		ShowStatsWindow(&show, ts);
		DrawDockSpace();
		DrawInspector();
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


		mCamera->SetPosition(mCamera->GetPosition() + glm::vec3(x, y, 0));
		mCamera->SetRotation(mCamera->GetRotation() + r);

		Walnut::Renderer::BeginScene(*mCamera);

		for (const auto& square : mSquares)
		{
			Walnut::Renderer::Submit(square);
		}

		Walnut::Renderer::EndScene();
	}

	void DrawInspector()
	{
		ImGui::Begin("Inspector");

		static int selected = 0;
		ImGui::BeginChild("left pane", ImVec2(150, 0), true);
		int i = 0;
		for (auto& square : mSquares)
		{
			if (ImGui::Selectable(square->GetName().c_str(), selected == i))
				selected = i;
			i++;
		}
		ImGui::EndChild();
		ImGui::SameLine();

		// right
		ImGui::BeginGroup();
		ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
		if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
		{
			if (ImGui::BeginTabItem("Properties"))
			{
				ImGui::Text("Transform");

				//Position
				glm::vec3 pos = mSquares[selected]->GetPosition();
				ImGui::InputFloat3("Position", glm::value_ptr(pos));
				mSquares[selected]->SetPosition(pos);
				//Scale
				glm::vec3 scale = mSquares[selected]->GetScale();
				ImGui::InputFloat3("Scale", glm::value_ptr(scale));
				mSquares[selected]->SetScale(scale);

				ImGui::Separator();
				ImGui::Text("Material");

				//Color
				glm::vec3 color = mSquares[selected]->GetColor();
				ImGui::ColorEdit3("Color", glm::value_ptr(color));
				mSquares[selected]->SetColor(color);

				//Texture#
				uint32_t textureId = mSquares[selected]->GetTexture();
				ImGui::Image((void*)textureId, ImVec2(50, 50), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
				ImGui::SameLine();
				ImGui::Text("Texture");
				ImGui::SameLine();
				if (ImGui::Button("Load"))
				{

				}

				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::EndChild();
		if (ImGui::Button("Add"))
		{
			auto square = std::make_shared<Walnut::Square>();
			mSquares.push_back(square);
		}
		ImGui::SameLine();
		if (ImGui::Button("Remove"))
		{
			mSquares.erase(mSquares.begin() + selected);
			selected--;

			if (selected < 0)
				selected = 0;
		}
		ImGui::EndGroup();
		ImGui::End();
	}

	void DrawDockSpace()
	{
		bool open = true;

		static bool opt_fullscreen_persistant = true;
		static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_PassthruDockspace;
		bool opt_fullscreen = opt_fullscreen_persistant;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruDockspace, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (opt_flags & ImGuiDockNodeFlags_PassthruDockspace)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace", &open, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Dockspace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::End();
	}


	void ShowStatsWindow(bool* p_open, Walnut::Timestep ts) const
	{
		// FIXME-VIEWPORT-ABS: Select a default viewport
		const float DISTANCE = 10.0f;
		static int corner = 2;
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
	std::vector<std::shared_ptr<Walnut::Square>> mSquares;
	std::shared_ptr<Walnut::VertexArray> mVertexArray;
	std::shared_ptr<Walnut::Shader> mShader;
	std::shared_ptr<Walnut::Camera> mCamera;

	glm::vec3 mSquareColor;
	glm::vec3 mSquareColor2;
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