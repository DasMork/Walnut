#pragma once

namespace Walnut
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* CreateDefault();
		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};
}
