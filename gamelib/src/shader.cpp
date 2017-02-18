#include <shader.h>
#include <GL/glew.h>
#include <filehelper.h>

Shader::Shader() {

}

void Shader::createProgram(const std::string& vertexFile, const std::string& pixelFile) {
	std::string srcVertex = FileHelper::readFileIntoString(vertexFile);
	std::string srcPixel = FileHelper::readFileIntoString(pixelFile);

	_handle = glCreateProgram();
	GLuint hV = glCreateShader(GL_VERTEX_SHADER);
	GLuint hP = glCreateShader(GL_FRAGMENT_SHADER);

	const char* srcVertexC = srcVertex.c_str();
	const char* srcPixelC = srcPixel.c_str();
	glShaderSource(hV, 1, &srcVertexC, NULL);
	glCompileShader(hV);

	GLint result;
	glGetShaderiv(hV, GL_COMPILE_STATUS, &result);
	if (GL_FALSE == result) {
		printf("error compiling vertex shader\n");
		throw std::runtime_error("error compiling vertex shader");
	}
	else {
		glAttachShader(_handle, hV);
	}

	glShaderSource(hP, 1, &srcPixelC, NULL);
	glCompileShader(hP);

	glGetShaderiv(hP, GL_COMPILE_STATUS, &result);
	if (GL_FALSE == result) {
		printf("error compiling pixel shader\n");
		throw std::runtime_error("error compiling pixel shader");
	}
	else {
		glAttachShader(_handle, hP);
	}

	glLinkProgram(_handle);
	GLint status = 0;
	glGetProgramiv(_handle, GL_LINK_STATUS, &status);
	if (GL_FALSE == status) {
		printf("error linking the program.\n");
		throw std::runtime_error("error linking the program");
	}
	GLenum err = glGetError();
	if (err != 0) printf("gl error: %d", err);
}

Shader::Shader(const std::string& vertexFile, const std::string& pixelFile) {
	createProgram(vertexFile, pixelFile);
}

void Shader::bindToPipeline() {
	glUseProgram(_handle);
}