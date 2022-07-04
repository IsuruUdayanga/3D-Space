#pragma once

#include "Component.h"

class Model
{
public:
	Model(float* vertices, unsigned int* indices, unsigned int verticesCount, unsigned int indicesCount, const char* vetx_shdr, const char* frgm_shdr, int width, int height);
	~Model();

	void Trasnform(glm::vec3 xyz);
	void Rotate(float angle, glm::vec3 ax);
	void Scale(float scaler);

	glm::mat4 GetProjection();
	void SetProjection(float fovy, float aspect, float near, float far);
	void DrawModel();
	void DrawProperties();
	void Render();

private:
	glm::mat4 m_projection{ 1.0f };
	Entity* m_properties{ nullptr };
};