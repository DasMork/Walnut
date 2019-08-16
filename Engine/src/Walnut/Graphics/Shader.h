#pragma once
#include <string>
#include <glm/mat4x4.hpp>

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

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		void Init(const std::string& vertexSrc, const std::string& fragmentSrc);

	private:
		uint32_t mRenderID;
	};
}
