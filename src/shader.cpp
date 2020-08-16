#include "shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>

static void checkShaderError(unsigned int shader, unsigned int flag, bool isProgram, const std::string& msg)
{
	int success;
	char error[1024] = { '\0' };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cout << "[Error] " << msg << ": " << error << std::endl;
	}
}

static std::string loadShader(const std::string& file)
{
	std::ifstream stream(file);
	std::string line;
	std::stringstream ss;

	while (getline(stream, line))
	{
		ss << line << "\n";
	}

	return ss.str();
}

static unsigned int createShader(const std::string& source, unsigned int type)
{
	unsigned int shader = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	checkShaderError(shader, GL_COMPILE_STATUS, false, "[Error] shader failed to compile!");

	return shader;
}

Shader::Shader(const std::string& file)
	: program(glCreateProgram())
{
	this->shaders[0] = createShader(loadShader(file + ".vs"), GL_VERTEX_SHADER);
	this->shaders[1] = createShader(loadShader(file + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < sizeof(shaders) / sizeof(unsigned int); i++)
	{
		glAttachShader(this->program, this->shaders[i]);
	}

	glBindAttribLocation(this->program, 0, "position");
	glBindAttribLocation(this->program, 1, "texCoord");
	glBindAttribLocation(this->program, 2, "normal");

	glLinkProgram(this->program);
	checkShaderError(this->program, GL_LINK_STATUS, true, "[Error] program linking failed!");

	glValidateProgram(this->program);
	checkShaderError(this->program, GL_VALIDATE_STATUS, true, "[Error] program is invalid!");

	this->uniforms[TRANSFORM_U] = glGetUniformLocation(this->program, "transform");
}

Shader::~Shader()
{
	for (unsigned int i = 0; i < sizeof(shaders) / sizeof(unsigned int); i++)
	{
		glDetachShader(this->program, this->shaders[i]);
		glDeleteShader(this->shaders[i]);
	}

	glDeleteProgram(this->program);
}

void Shader::bind()
{
	glUseProgram(this->program);
}

void Shader::update(const Transform& transform, const Camera& camera)
{
	glm::mat4 model = camera.getViewProjection() * transform.getModel();
	glUniformMatrix4fv(this->uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}
