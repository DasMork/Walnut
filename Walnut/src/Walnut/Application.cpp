#include "Application.h"

Walnut::Application::Application()
	: mRunning(true)
{
	mWindow = Walnut::Test::Window::WN_CreateWindow(640, 360, "MyNameIsWalnut");
	Start();
}


Walnut::Application::~Application()
{
	mWindow->Close();
	WN_CORE_LOG("Shutdown Engine!");
}

void Walnut::Application::Run()
{
	while (!glfwWindowShouldClose(mWindow->GetCurrentWindow()))
	{
		mWindow->Clear();
		Render();
		mWindow->SwapBuffer();
	}
}
struct ShaderSources
{
	std::string VertexSource;
	std::string FragmentSource;
};

static ShaderSources ParseShader(const std::string& filepath) {

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
static unsigned int CompileShader(unsigned int type, const std::string& source)
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
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
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

void Walnut::Application::Start()
{
	float positions[6] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.0f,	0.5f
	};
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glEnableVertexAttribArray(0);
	ShaderSources ss = ParseShader("Walnut/shaders/default");
	unsigned int shader = CreateShader(ss.VertexSource, ss.FragmentSource);
	glUseProgram(shader);
}

void Walnut::Application::Render()
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

