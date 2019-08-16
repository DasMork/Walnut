#include "wnpch.h"
#include "Shader.h"
#include "glad/glad.h"

#include <glm/gtc/type_ptr.hpp>

Walnut::Shader::Shader()
{
	std::string vertexSrc = R"(
		#version 330 core
		
		layout(location = 0) in vec3 aPosition;
		
		uniform mat4 uViewProjection;
		uniform mat4 uTransform;

		out vec3 vPosition;

		void main()
		{
			gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0);
		}
	)";

	std::string fragentSrc = R"(
		#version 330 core
		
		layout(location = 0) out vec4 oColor;
		
		void main()
		{
			oColor = vec4(1.0,1.0,1.0,1.0);
		}
	
	)";

	Init(vertexSrc, fragentSrc);
}

Walnut::Shader::Shader(const std::string & vertexSrc, const std::string & fragmentSrc)
{
	Init(vertexSrc, fragmentSrc);
}

Walnut::Shader::~Shader()
{
	glDeleteProgram(mRenderID);
}

void Walnut::Shader::Bind() const
{
	glUseProgram(mRenderID);
}

void Walnut::Shader::Unbind() const
{
	glUseProgram(0);
}

void Walnut::Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
{
	int location = glGetUniformLocation(mRenderID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Walnut::Shader::Init(const std::string& vertexSrc, const std::string& fragmentSrc)
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
