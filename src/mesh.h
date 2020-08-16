#pragma once

#include <string>
#include <GL/glew.h>
#include "vertex.h"
#include "obj_loader.h"

class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int amount, unsigned int* indices, unsigned int numIndices);
	Mesh(const std::string& file);
	~Mesh();

	void draw();

private:
	void initMesh(const IndexedModel& model);

	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		INDEX_VB,
		NORMAL_VB,

		NUM_BUFFERS,
	};

	unsigned int vertexArrayObject;
	unsigned int vertexArrayBuffer[NUM_BUFFERS];
	unsigned int drawCount;
};
