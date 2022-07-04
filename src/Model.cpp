#include "Model.h"

Model::Model(float* vertices, unsigned int* indices, unsigned int verticesCount, unsigned int indicesCount, const char* vetx_shdr, const char* frgm_shdr, int width, int height)
{
	m_properties = new Entity();
	m_properties->AddComponent<Mesh>(vertices, indices, verticesCount, indicesCount, width, height);
	m_properties->AddComponent<Transform>();
	m_properties->AddComponent<Shader>(vetx_shdr, frgm_shdr);
}

Model::~Model()
{
	delete m_properties;
}

glm::mat4 Model::GetProjection() {
	return m_projection;
}

void Model::SetProjection(float fovy, float aspect, float near, float far) {
	m_projection = glm::perspective(fovy, aspect, near, far);
}

void Model::Trasnform(glm::vec3 xyz)
{
	m_properties->GetComponent<Transform>().SetPostion(xyz);
}

void Model::DrawModel() {
	m_properties->GetComponent<Mesh>().Draw();
}

void Model::DrawProperties() {
	m_properties->GetComponent<Transform>().Draw();
}

void Model::Render() {

	glm::mat4 model{ 1.0f };
	m_properties->GetComponent<Shader>().UseShader();
	model = glm::translate(model, m_properties->GetComponent<Transform>().GetPosition());
	model = glm::rotate(model, glm::radians(m_properties->GetComponent<Transform>().GetAngles()), m_properties->GetComponent<Transform>().GetAxis());
	model = glm::scale(model, m_properties->GetComponent<Transform>().GetScales());
	glUniformMatrix4fv(m_properties->GetComponent<Shader>().GetUniformModel(), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(m_properties->GetComponent<Shader>().GetUniformProjection(), 1, GL_FALSE, glm::value_ptr(m_projection));
	m_properties->GetComponent<Transform>().Draw();

	m_properties->GetComponent<Mesh>().Bind();
	m_properties->GetComponent<Mesh>().Draw();
	m_properties->GetComponent<Mesh>().Unbind();

	ImGui::Begin("Scene");

	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	static glm::vec2 Size = { viewportPanelSize.x, viewportPanelSize.y };

	// add rendered texture to ImGUI scene window
	uint64_t textureID = m_properties->GetComponent<Mesh>().GetTextureID();
	ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ Size.x, Size.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

	ImGui::End();

	glUseProgram(0);
}
