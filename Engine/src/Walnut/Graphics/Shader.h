#pragma once
#include <string>

namespace Walnut
{
	class Shader
	{
	public:
		Shader();
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;
	private:
		void Init(const std::string& vertexSrc, const std::string& fragmentSrc);

	private:
		uint32_t mRenderID;
	};
}