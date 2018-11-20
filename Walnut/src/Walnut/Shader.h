#pragma once

#include "Core.h"
#include <string>
#include <unordered_map>

namespace Walnut {
	namespace Rendering {

		struct ShaderSources
		{
			std::string VertexSource;
			std::string FragmentSource;
		};
		class WALNUT_API Shader
		{
		private:
			unsigned int mRenderID;
			std::unordered_map<std::string, unsigned int> mUniformLocationCache;
		public:
			Shader(const std::string& fielpath);
			~Shader();

			void Bind();
			void Unbind();

			inline unsigned int GetID() { return mRenderID; }

			void SetUniform4f(const std::string & name, float v1, float v2, float v3, float v4);
			unsigned int GetUniformLocation(const std::string& name);

			ShaderSources ParseShader(const std::string& filepath);
			unsigned int CompileShader(unsigned int type, const std::string & source);
			unsigned int CreateShader(const std::string & vertexShader, const std::string & fragmentShader);
		};
	}
}

