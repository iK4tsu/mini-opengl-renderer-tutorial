#include <iostream>
#include <GL/glew.h>
#include <algorithm>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "vertex.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

int main(void)
{
	const unsigned int WIDTH = 1280, HEIGHT = 720;

	Display display(WIDTH,HEIGHT,"Hello");

	Vertex vertices[] = {
		{ glm::vec3(-0.5f, -0.5f, 0.f), glm::vec2(0.f, 0.f)},
		{ glm::vec3(0.f, 0.5f, 0.f), glm::vec2(0.5f, 1.f) },
		{ glm::vec3(0.5f, -0.5f, 0.f), glm::vec2(1.f, 0.f) }
	};

	unsigned int indices[] = { 0, 1, 2 };

	// Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
	Mesh meshMonkey("../res/models/monkey3.obj");
	Shader shader("../res/shaders/basicShader");
	Texture texture("../res/textures/bricks.jpg");
	Camera camera(glm::vec3(0,0,7), 70.f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.f);
	Transform transform;

	float counter = 0.f;

	while (!display.isClosed())
	{
		display.clear(0.15f,0.13f,0.15f,1.f);

		transform.pos.x = sinf(counter);
		transform.pos.z = cosf(counter);
		transform.rot.x = counter;
		transform.rot.y = counter;
		transform.rot.z = counter;
		// transform.scale.x = fabs(cosf(counter));
		// transform.scale.y = cosf(counter);
		// transform.scale.z = cosf(counter);

		shader.bind();
		texture.bind(0);
		shader.update(transform, camera);
		meshMonkey.draw();
		display.update();

		counter += 0.01f;
	}

	return 0;
}
