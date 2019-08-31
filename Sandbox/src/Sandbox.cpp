#include <Walnut.h>

#include "ImGui/imgui.h"
#include "Walnut/Platform/OpenGL/GLShader.h"
#include <glm/gtc/type_ptr.hpp>
#include "Walnut/Cube.h"
#include "Walnut/Components/RendererComp.h"
#include "Walnut/Components/Transform.h"
#include "Walnut/Platform/OpenGL/GLTexture.h"


class SandboxLayer : public Walnut::Layer
{
public:
	SandboxLayer(const std::string& name)
		: Layer(name)
	{
		//mCamera.reset(new Walnut::OrthographicCamera(0, 16, 0, 9));
		mCamera.reset(new Walnut::PerspectiveCamera(65, 16, 9, 0.1f, 100));
		//mCamera->SetPosition({ 16, 9, 2 });
		mCamera->SetPosition(glm::vec3(8, 4.5f, -12));
		/*	auto square = std::make_shared<Walnut::Square>();
			square->SetPosition(glm::vec3(0, 0, 0));

			auto square2 = std::make_shared<Walnut::Square>();
			square2->SetPosition(glm::vec3(3, 2, 0));

			auto square3 = std::make_shared<Walnut::Cube>();
			square3->SetPosition(glm::vec3(8, 4, 0));*/

			//mObjects.push_back(square);
			//mObjects.push_back(square2);
			//mObjects.push_back(square3);

		std::shared_ptr<Walnut::GameObject>object;
		object.reset(new Walnut::GameObject("Test"));
		object->AddComponent(new Walnut::Components::Transform());
		object->AddComponent(new Walnut::Components::RendererComp());

		object->GetComponent<Walnut::Components::Transform>()->SetPosition(glm::vec3(6, 0, 0));
		mObjects.push_back(object);

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
			x -= cameraMoveSpeed * ts.GetSeconds();
		if (Walnut::Input::GetKey(WN_KEY_A))
			x += cameraMoveSpeed * ts.GetSeconds();

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


		for (auto& obj : mObjects)
		{
			for (auto& comp : obj->GetAllComponents())
			{
				comp->Update();
			}
		}

		Walnut::Renderer::EndScene();
	}

	void DrawInspector()
	{
		ImGui::Begin("Inspector");

		static int selected = 0;
		ImGui::BeginChild("left pane", ImVec2(150, 0), true);
		if (ImGui::Button("Add"))
		{
			std::shared_ptr<Walnut::GameObject> object;
			object.reset(new Walnut::GameObject());
			object->AddComponent(new Walnut::Components::Transform());
			mObjects.push_back(object);
		}
		ImGui::SameLine();
		if (ImGui::Button("Remove"))
		{
			mObjects.erase(mObjects.begin() + selected);
			selected--;

			if (selected < 0)
				selected = 0;
		}
		int i = 0;
		for (auto& square : mObjects)
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
				for (const auto& comp : mObjects[selected]->GetAllComponents())
				{
					DisplayComponent(*comp);
					ImGui::Separator();
				}
				static int listbox_item_current = -2;
				if (ImGui::Button("Add Component"))
				{
					listbox_item_current = -1;
				}

				if (listbox_item_current == -1)
				{
					const char* listbox_items[] = { "Renderer" };
					ImGui::ListBox("Components", &listbox_item_current, listbox_items, IM_ARRAYSIZE(listbox_items));

					if (listbox_item_current > -1)
					{
						listbox_item_current = -2;
						mObjects[selected]->AddComponent(new Walnut::Components::RendererComp());
					}
				}

				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::EndChild();

		ImGui::EndGroup();
		ImGui::End();
	}

	void DisplayComponent(const Walnut::Component& comp)
	{
		if (ImGui::CollapsingHeader(comp.GetName(), ImGuiTreeNodeFlags_DefaultOpen))
		{
			switch (comp.GetEventType())
			{
			case Walnut::Component::ComponentType::Transform:
			{
				Walnut::Components::Transform* t = (Walnut::Components::Transform*)&comp;

				//Position
				glm::vec3 pos = t->GetPosition();
				ImGui::InputFloat3("Position", glm::value_ptr(pos));
				t->SetPosition(pos);
				//Scale
				glm::vec3 scale = t->GetScale();
				ImGui::InputFloat3("Scale", glm::value_ptr(scale));
				t->SetScale(scale);
				break;
			}
			case Walnut::Component::ComponentType::Renderer:
			{
				Walnut::Components::RendererComp* r = (Walnut::Components::RendererComp*)&comp;

				const char* listbox_items[] = { "Flat Color", "Default" };

				const char* item_current = r->GetShader()->GetTypeName().c_str();

				if (ImGui::BeginCombo("Shader", item_current)) // The second parameter is the label previewed before opening the combo.
				{
					for (int n = 0; n < IM_ARRAYSIZE(listbox_items); n++)
					{
						bool is_selected = (item_current == listbox_items[n]);
						if (ImGui::Selectable(listbox_items[n], is_selected))
							item_current = listbox_items[n];
						if (is_selected)
							ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
					}
					r->SetShader(item_current);
					ImGui::EndCombo();
				}

				//Color
				glm::vec3 color = r->GetColor();
				ImGui::ColorEdit3("Color", glm::value_ptr(color));
				r->SetColor(color);

				/*	if (item_current != "Default")
						break;*/


						//Get Current Texture Path as char array
				const std::string path = r->GetTexture()->GetPath();

				char filePath[64] = "";
				strncpy_s(filePath, path.c_str(), path.size());
				filePath[path.size()] = 0;

				ImGui::InputText("Texture: ", filePath, 64);

				static std::shared_ptr<Walnut::Texture> t;
				t.reset(Walnut::Texture::Create(filePath));

				if (ImGui::Button("Load"))
				{
				}
				if (t)
				{
					ImTextureID my_tex_id = (ImTextureID)t->GetID();
					ImGui::Image(my_tex_id, ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
					ImGui::SameLine();
					ImGui::Text("Texture");

					r->SetTexture(t);
				}
				break;
			}
			}
		}
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
	std::vector<std::shared_ptr<Walnut::GameObject>> mObjects;
	std::shared_ptr<Walnut::Camera> mCamera;
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