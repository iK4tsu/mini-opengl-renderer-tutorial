#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);
	~Camera();

	inline glm::mat4 getViewProjection() const
	{
		return perspective * glm::lookAt(position, position - foward, up);
	}

private:
	glm::mat4 perspective;
	glm::vec3 position;
	glm::vec3 foward;
	glm::vec3 up;
};
