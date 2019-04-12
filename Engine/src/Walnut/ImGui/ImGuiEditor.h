#pragma once
#include "Walnut/Core.h"

namespace Walnut
{
	class WALNUT_API ImGuiEditor
	{
	public:
		void static ShowEditor(bool* show);

	private:
		static void ShowMenuBar(bool* open);
		static void ShowStats(bool* open);
		static void ShowSceneView(bool* open);
		static void ShowInspector(bool* open);
	};
}