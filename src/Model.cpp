#include "Model.h"

Model::Model(float* vertices, unsigned int* indices, unsigned int verticesCount, unsigned int indicesCount, const char* vetx_shdr, const char* frgm_shdr, int width, int height,const char* texture)
{
	m_properties = new Entity();
	m_properties->AddComponent<Mesh>(vertices, indices, verticesCount, indicesCount, width, height);
	m_properties->AddComponent<Transform>();
	m_properties->AddComponent<Shader>(vetx_shdr, frgm_shdr);
	m_properties->AddComponent<Camera>(width, height, glm::vec3(0.0f, 0.1f, 2.5f));
	m_properties->AddComponent<Texture>(texture);
	m_properties->AddComponent<Light>(1.0f, 0.5f, 0.2f, 0.3f);

	Input::setControlEntity(m_properties);
}

Model::~Model()
{
	delete m_properties;
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
	m_properties->GetComponent<Light>().UseLight(m_properties->GetComponent<Shader>().GetUniformAmbientIntensityLocation(), m_properties->GetComponent<Shader>().GetUniformAmbientColorLocation());

	model = glm::translate(model, m_properties->GetComponent<Transform>().GetPosition());
	model = glm::rotate(model, glm::radians(m_properties->GetComponent<Transform>().GetAngles()), m_properties->GetComponent<Transform>().GetAxis());
	model = glm::scale(model, m_properties->GetComponent<Transform>().GetScales());

	glUniformMatrix4fv(m_properties->GetComponent<Shader>().GetUniformModel(), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(m_properties->GetComponent<Shader>().GetUniformProjection(), 1, GL_FALSE, glm::value_ptr(m_properties->GetComponent<Camera>().GetProjection()));
	m_properties->GetComponent<Transform>().Draw();
	m_properties->GetComponent<Texture>().UseTexture();
	m_properties->GetComponent<Mesh>().Draw();

	ImGui::Begin("Scene View");
	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	static glm::vec2 Size = { viewportPanelSize.x, viewportPanelSize.y};

	// add rendered texture to ImGUI scene window
	uint64_t textureID = m_properties->GetComponent<Mesh>().GetTextureID();
	ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ Size.x, Size.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
	ImGui::End();

	m_properties->GetComponent<Camera>().ViewMatrix(45.0f, 0.1f, 100.0f);

	glUseProgram(0);
}
