#include "texture.h"
#include "stb_image.h"

#include <iostream>
#include <assert.h>
#include <GL/glew.h>

Texture::Texture(const std::string& file)
{
	int wigth, height, numCmponents;
	unsigned char* imageData = stbi_load(file.c_str(), &wigth, &height, &numCmponents, 4);

	if (!imageData)
	{
		std::cout << "[Error] failed to load texture!" << std::endl;
	}

	glGenTextures(1, &(this->texture));
	glBindTexture(GL_TEXTURE_2D, this->texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, wigth, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);
}

Texture::~Texture()
{
	glDeleteTextures(1, &(this->texture));
}

void Texture::bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, this->texture);
}
