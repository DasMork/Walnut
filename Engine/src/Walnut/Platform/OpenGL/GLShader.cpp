#include "wnpch.h"
#include "glad/glad.h"

#include <glm/gtc/type_ptr.hpp>
#include "GLShader.h"

std::string vertexSrc = R"(
		#version 330 core
		
		layout(location = 0) in vec3 aPosition;
		layout(location = 1) in vec2 aTexCoord;	

		uniform mat4 uViewProjection;
		uniform mat4 uTransform;

		out vec2 vTexCoord;
		
		void main()
		{
			vTexCoord = aTexCoord;
			gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0);
		}
	)";

std::string fragentSrc = R"(
		#version 330 core
		
		layout(location = 0) out vec4 oColor;
		
		uniform vec3 uColor;

		in vec2 vTexCoord;

		uniform sampler2D uTexture;

		void main()
		{
			oColor = /*texture(uTexture, vTexCoord) * */vec4(uColor, 1.0);
		}
	
	)";

std::string textureFragentSrc = R"(
		#version 330 core
		
		layout(location = 0) out vec4 oColor;
		
		uniform vec3 uColor;

		in vec2 vTexCoord;

		uniform sampler2D uTexture;

		void main()
		{
			oColor = texture(uTexture, vTexCoord) * vec4(uColor, 1.0);
		}
	
	)";

Walnut::GLShader::GLShader(const std::string & name, const std::string & vertexSrc, const std::string & fragmentSrc)
	: mName(name)
{
	Init(vertexSrc, fragmentSrc);
}

Walnut::GLShader::GLShader(const std::string & shaderType)
	: mName(shaderType)
{
	if (shaderType == "Flat Color")
	{
		Init(vertexSrc, fragentSrc);
	}
	else if (shaderType == "Default")
	{
		Init(vertexSrc, textureFragentSrc);
	}
	else
	{
		WN_CORE_ASSERT(false, "Unknown Shader!")
	}
}

Walnut::GLShader::~GLShader()
{
	glDeleteProgram(mRenderID);
}

void Walnut::GLShader::Bind() const
{
	glUseProgram(mRenderID);
}

void Walnut::GLShader::Unbind() const
{
	glUseProgram(0);
}

void Walnut::GLShader::UploadUniformInt(const std::string & name, int value)
{
	const int location = glGetUniformLocation(mRenderID, name.c_str());
	glUniform1i(location, value);
}

void Walnut::GLShader::UploadUniformFloat(const std::string & name, float value)
{
	const int location = glGetUniformLocation(mRenderID, name.c_str());
	glUniform1f(location, value);
}

void Walnut::GLShader::UploadUniformFloat2(const std::string & name, const glm::vec2 & vector)
{
	const int location = glGetUniformLocation(mRenderID, name.c_str());
	glUniform2f(location, vector.x, vector.y);
}

void Walnut::GLShader::UploadUniformFloat3(const std::string & name, const glm::vec3 & vector)
{
	const int location = glGetUniformLocation(mRenderID, name.c_str());
	glUniform3f(location, vector.x, vector.y, vector.z);
}

void Walnut::GLShader::UploadUniformFloat4(const std::string & name, const glm::vec4 & vector)
{
	const int location = glGetUniformLocation(mRenderID, name.c_str());
	glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
}

void Walnut::GLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
{
	const int location = glGetUniformLocation(mRenderID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Walnut::GLShader::UploadUniformMat3(const std::string & name, const glm::mat3 & matrix)
{
	const int location = glGetUniformLocation(mRenderID, name.c_str());
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Walnut::GLShader::Init(const std::string& vertexSrc, const std::string& fragmentSrc)
{
	// Create an empty vertex shader handle
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Send the vertex shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	const GLchar *source = (const GLchar *)vertexSrc.c_str();
	glShaderSource(vertexShader, 1, &source, 0);

	// Compile the vertex shader
	glCompileShader(vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(vertexShader);

		// Use the infoLog as you see fit.
		WN_CORE_ERROR("Failed to compile vertex shader! Errorcode: {0}", infoLog.data());

		// In this simple program, we'll just leave
		return;
	}

	// Create an empty fragment shader handle
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Send the fragment shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	source = (const GLchar *)fragmentSrc.c_str();
	glShaderSource(fragmentShader, 1, &source, 0);

	// Compile the fragment shader
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(fragmentShader);
		// Either of them. Don't leak shaders.
		glDeleteShader(vertexShader);

		// Use the infoLog as you see fit.
		WN_CORE_ERROR("Failed to compile fragment shader! Errorcode: {0}", infoLog.data());

		// In this simple program, we'll just leave
		return;
	}

	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	mRenderID = glCreateProgram();

	// Attach our shaders to our program
	glAttachShader(mRenderID, vertexShader);
	glAttachShader(mRenderID, fragmentShader);

	// Link our program
	glLinkProgram(mRenderID);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(mRenderID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(mRenderID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(mRenderID, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(mRenderID);
		// Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Use the infoLog as you see fit.
		WN_CORE_ERROR("Failed to link shaders! Errorcode: {0}", infoLog.data());

		// In this simple program, we'll just leave
		return;
	}

	// Always detach shaders after a successful link.
	glDetachShader(mRenderID, vertexShader);
	glDetachShader(mRenderID, fragmentShader);
}
