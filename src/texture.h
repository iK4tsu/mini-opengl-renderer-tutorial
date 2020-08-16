#pragma once

#include <string>

class Texture
{
public:
	Texture(const std::string& file);
	~Texture();

	void bind(unsigned int unit);

private:
	unsigned int texture;
};
