#pragma once

#include "Component.h"
#include "Input.h"

class Model
{
public:
	Model(float* vertices, unsigned int* indices, unsigned int verticesCount, unsigned int indicesCount, const char* vetx_shdr, const char* frgm_shdr, int width, int height, const char* texture);
	~Model();

	void Trasnform(glm::vec3 xyz);

	void DrawModel();
	void DrawProperties();
	void Render();

private:
	Entity* m_properties{ nullptr };
};