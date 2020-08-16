#include "mesh.h"
#include "obj_loader.h"
#include <vector>

Mesh::Mesh(const std::string& file)
{
	IndexedModel model = OBJModel(file).ToIndexedModel();
	initMesh(model);
}

Mesh::Mesh(Vertex* vertices, unsigned int amount, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;

	for (unsigned int i = 0; i < amount; i++)
	{
		model.positions.push_back(vertices[i].pos);
		model.texCoords.push_back(vertices[i].texCoord);
		model.normals.push_back(vertices[i].normal);
	}

	for (unsigned int i = 0; i < numIndices; i++)
	{
		model.indices.push_back(indices[i]);
	}

	initMesh(model);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &(this->vertexArrayObject));
}

void Mesh::initMesh(const IndexedModel& model)
{
	this->drawCount = model.indices.size();

	glGenVertexArrays(1, &(this->vertexArrayObject));
	glBindVertexArray(this->vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, this->vertexArrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexArrayBuffer[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, this->vertexArrayBuffer[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.texCoords.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// normals
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexArrayBuffer[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vertexArrayBuffer[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Mesh::draw()
{
	glBindVertexArray(this->vertexArrayObject);

	glDrawElements(GL_TRIANGLES, this->drawCount, GL_UNSIGNED_INT, 0);
	// glDrawArrays(GL_TRIANGLES, 0, this->drawCount);

	glBindVertexArray(0);
}
