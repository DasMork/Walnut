#pragma once

namespace Walnut
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const std::string& GetTypeName() const = 0;

		Walnut::Shader * Create(const std::string & name, const std::string & vertexSrc, const std::string & fragmentSrc);
		static Shader* Create(const std::string& shaderType);
	};
}
