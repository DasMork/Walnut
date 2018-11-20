#pragma once
#include "Core.h"
#include "Rendering.h"

namespace Walnut {
	namespace Rendering {

		class WALNUT_API Renderer
		{
		public:
			Renderer();
			~Renderer();

			void Draw() const;

		};
	}
}

