#pragma once
#include "GL/glew.h"
#include "Log.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

#ifdef WN_DEBUG
#define ASSERT(x) if(!(x)) __debugbreak();
#else
#define ASSERT(x) x;
#endif
#define GLCall(x) glClearErrors(); x; ASSERT(glLogCall(#x, __FILE__, __LINE__))

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