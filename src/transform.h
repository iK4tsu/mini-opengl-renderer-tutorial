#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Transform
{
	Transform(const glm::vec3& pos = glm::vec3(),
				const glm::vec3& rot = glm::vec3(),
				const glm::vec3& scale = glm::vec3(1.f, 1.f, 1.f))
		: pos(pos),
		rot(rot),
		scale(scale)
	{}

	inline const glm::mat4 getModel() const
	{
		glm::mat4 posMatrix = glm::translate(pos);

		glm::mat4 rotXMatrix = glm::rotate(rot.x, glm::vec3(1.f, 0.f, 0.f));
		glm::mat4 rotYMatrix = glm::rotate(rot.y, glm::vec3(0.f, 1.f, 0.f));
		glm::mat4 rotZMatrix = glm::rotate(rot.z, glm::vec3(0.f, 0.f, 1.f));
		glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

		glm::mat4 scaleMatrix = glm::scale(scale);

		return posMatrix * rotMatrix * scaleMatrix;
	}

	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
};
