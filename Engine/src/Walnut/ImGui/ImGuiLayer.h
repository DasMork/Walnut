#pragma once
#include "Walnut/Layer.h"
#include "Walnut/Events/ApplicationEvent.h"
#include "Walnut/Events/KeyEvent.h"
#include "Walnut/Events/MouseEvent.h"

namespace Walnut
{
	class WALNUT_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
	private:
		void OnAttach();
		void OnDetach();

		void OnUpdate();
		void OnEvent(Event& event);

		bool OnMouseButtonPressed(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& event);
		bool OnMouseMoved(MouseMovedEvent& event);
		bool OnMouseScrolled(MouseScrolledEvent& event);

		bool OnKeyPressed(KeyPressedEvent& event);
		bool OnKeyReleased(KeyReleasedEvent& event);
		bool OnKeyTyped(KeyTypedEvent& event);

		bool OnWindowResize(WindowResizeEvent& event);

	private:
		float mTime = 0.0f;
	};
}