#pragma once

#include "ECS.h"

class Transform : public Component
{
public:
	Transform() = default;
	Transform(glm::vec3 position, float angle, float scaler) : m_position(position), m_angle(angle), m_scaler(scaler) {}
	virtual ~Transform() = default;

	bool Init() override 
	{
		return true;
	}

	void Update() override 
	{

	}

	void Draw() override {
		ImGui::Begin("Model Properties", (bool*)1, 1);

		ImGui::Text("Position");
		ImGui::DragFloat("X", &m_position.x, 0.01f);
		ImGui::DragFloat("Y", &m_position.y, 0.01f);
		ImGui::DragFloat("Z", &m_position.z, 0.01f);

		ImGui::Text("Rotation");
		static bool x = 1, y = 0, z = 0;
		ImGui::Checkbox("X Axis", &x);
		ImGui::Checkbox("Y Axis", &y);
		ImGui::Checkbox("Z Axis", &z);
		ImGui::DragFloat("Angle", &m_angle, 1.0f, -360.0f, 360.0f, "%.3f", NULL);
		m_rotationAxis.x = (x) ? 1.0f : 0.0f;
		m_rotationAxis.y = (y) ? 1.0f : 0.0f;
		m_rotationAxis.z = (z) ? 1.0f : 0.0f;

		ImGui::Text("Scale");
		ImGui::DragFloat("All axise", &m_scaler, 0.01f);
		ImGui::Separator();
		ImGui::Text("Hits");
		ImGui::Text("	Right-Click Enable or Disable the Camera.");
		ImGui::End();
	}

	void SetPostion(glm::vec3 pos) 
	{
		m_position = pos;
	}

	glm::vec3 GetPosition() 
	{
		return m_position;
	}

	float GetAngles()
	{
		return m_angle;
	}

	glm::vec3 GetAxis()
	{
		return m_rotationAxis;
	}

	glm::vec3 GetScales()
	{
		m_scaleAxises.x = m_scaler;
		m_scaleAxises.y = m_scaler;
		m_scaleAxises.z = m_scaler;

		return m_scaleAxises;
	}

private:
	glm::vec3 m_position{ 0.0f, 0.0f, 0.0f };
	float m_angle{ 0.0f };
	glm::vec3 m_rotationAxis{ 0.0f, 0.0f, 0.0f };
	float m_scaler{ 0.2f };
	glm::vec3 m_scaleAxises{ 0.2f };
};