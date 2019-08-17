#pragma once
#include <glm/vec3.hpp>
#include "Graphics/Shader.h"
#include "Graphics/VertexArray.h"
#include <glm/glm.hpp>
#include "Renderable.h"

namespace Walnut
{
	class Square : public Renderable
	{
	public:
		Square(const glm::vec3& color = { 1,1,1 });
	};
}
