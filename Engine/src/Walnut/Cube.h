#pragma once
#include <glm/glm.hpp>
#include "Renderable.h"

namespace Walnut
{
	class Cube : public Renderable
	{
	public:
		Cube(const glm::vec3& color = { 1,1,1 });
	};
}
