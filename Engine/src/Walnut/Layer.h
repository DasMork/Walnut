#pragma once
#include "wnpch.h"

#include "Core.h"
#include "Events/Event.h"

namespace Walnut
{
	class WALNUT_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return mDebugName; }
	protected:
		std::string mDebugName;
	};
}
