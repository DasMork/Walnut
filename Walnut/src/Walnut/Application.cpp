#include "Application.h"

#ifdef WN_DEBUG
#define ASSERT(x) if(!(x)) __debugbreak();
#else
#define ASSERT(x) x;
#endif
#define GLCall(x) glClearErrors(); x; ASSERT(glLogCall(#x, __FILE__, __LINE__));

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

static void glClearErrors() {
	while (glGetError() != GL_NO_ERROR);
}

static bool glLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		WN_CORE_WARNING("OpenGl Error {} in {} on line {}", error, function, line);
		return false;
	}

	return true;
}


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
	float positions[8] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f,  0.5f,
		-0.5f, 0.5f

	};

	unsigned int indices[] = {
		0,1,2,2,3,0
	};
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glEnableVertexAttribArray(0);

	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	ShaderSources ss = ParseShader("Walnut/shaders/default");
	unsigned int shader = CreateShader(ss.VertexSource, ss.FragmentSource);
	glUseProgram(shader);
}

void Walnut::Application::Render()
{
	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}

