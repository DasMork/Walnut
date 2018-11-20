#include "Shader.h"

#include "Rendering.h"
#include "Log.h"
#include <fstream>
#include <sstream>


Walnut::Rendering::Shader::Shader(const std::string& filepath)
{
	ShaderSources ss = ParseShader(filepath);
	mRenderID = CreateShader(ss.VertexSource, ss.FragmentSource);
	glUseProgram(mRenderID);
}


Walnut::Rendering::Shader::~Shader()
{
	glDeleteProgram(mRenderID);
}

void Walnut::Rendering::Shader::Bind()
{
	glUseProgram(mRenderID);
}

void Walnut::Rendering::Shader::Unbind()
{
	glUseProgram(0);
}

void Walnut::Rendering::Shader::SetUniform4f(const std::string & name, float v1, float v2, float v3, float v4)
{
	GLCall(glUniform4f(GetUniformLocation(name), v1, 2, v3, v4));
}

unsigned int Walnut::Rendering::Shader::GetUniformLocation(const std::string & name)
{
	if (mUniformLocationCache.find(name) != mUniformLocationCache.end()) {
		return mUniformLocationCache[name];
	}
	else {
		GLCall(unsigned int location = glGetUniformLocation(mRenderID, name.c_str()));
		if (location == -1) {
			WN_CORE_WARNING("Uniform {} does not exist!", name);
		}
		mUniformLocationCache[name] = location;
		return location;
	}
}

Walnut::Rendering::ShaderSources Walnut::Rendering::Shader::ParseShader(const std::string& filepath) {

	std::ifstream stream(filepath + ".glsl");

	if (!stream)
		WN_CORE_WARNING("The requested shader path is invalid!");

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		}
		else {
			ss[(int)type] << line << "\n";
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Walnut::Rendering::Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) {
		if (type == GL_VERTEX_SHADER) {
			WN_CORE_ERROR("Failed to compile vertex shader!");
		}
		else {
			WN_CORE_ERROR("Failed to compile fragment shader!");
		}
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)(alloca(length * sizeof(char)));
		glGetShaderInfoLog(id, length, &length, message);
		WN_CORE_ERROR(message);
	}
	else {
		if (type == GL_VERTEX_SHADER) {
			WN_CORE_LOG("Compiled vertex shader!");
		}
		else {
			WN_CORE_LOG("Compiled fragment shader!");
		}
	}

	return id;
}

unsigned int Walnut::Rendering::Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
