#pragma once

#include <string>
#include "transform.h"
#include "camera.h"

class Shader
{
public:
	Shader(const std::string& file);
	~Shader();

	void bind();
	void update(const Transform& transform, const Camera& camera);

private:
	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS,
	};

	unsigned int program;
	unsigned int shaders[2];
	unsigned int uniforms[NUM_UNIFORMS];
};
