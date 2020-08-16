#pragma once

#include <glm/glm.hpp>

struct Vertex
{
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3 normal = glm::vec3(0,0,0))
		: pos(pos), texCoord(texCoord), normal(normal)
	{}

	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};
