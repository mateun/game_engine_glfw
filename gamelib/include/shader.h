#pragma once
#include <renderlib_api.h>
#include <string>
#include <GL/glew.h>

/** \class	Shader
	\brief	Represents an GLSL shader
 *
 */
#ifdef _WIN32
class RENDERLIB_API Shader
#else
class Shader
#endif
{

public:
	Shader();
	Shader(const std::string& vertexShaderFile, const std::string& pixelShaderFile);
	virtual void createProgram(const std::string& vertexShaderFile, const std::string& pixelShaderFile);
	virtual void bindToPipeline();

private:
	GLuint _handle = 0;
	
};