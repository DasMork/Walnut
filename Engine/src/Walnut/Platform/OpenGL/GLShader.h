#pragma once
#include <string>
#include <glm/mat4x4.hpp>
#include "Walnut/Graphics/Shader.h"

namespace Walnut
{
	class GLShader : public Shader
	{
	public:
		GLShader(const std::string& shaderType);
		GLShader(const std::string & name, const std::string & vertexSrc, const std::string & fragmentSrc);
		virtual ~GLShader();

		void Bind() const override;
		void Unbind() const override;

		const std::string& GetTypeName() const override { return mName; };

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& vector);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& vector);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& vector);
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		void Init(const std::string& vertexSrc, const std::string& fragmentSrc);

	private:
		uint32_t mRenderID;
		std::string mName;
	};
}
