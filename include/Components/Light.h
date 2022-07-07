#pragma once

#include "ECS.h"

class Light : public Component
{
public:
	Light() = default;
	Light(float red, float green, float blue, float ambient_intensity)
	{
		m_color = glm::vec3(red, green, blue);
		m_ambientIntensity = ambient_intensity;
	}

	void UseLight(unsigned int ambient_intensity_location, unsigned int ambient_color_location)
	{
		glUniform3f(ambient_color_location, m_color.x, m_color.y, m_color.z);
		glUniform1f(ambient_intensity_location, m_ambientIntensity);
	}

	virtual ~Light() = default;

	bool Init() override
	{
		return true;
	}
	void Update() override
	{

	}
	void Draw() override
	{

	}

private:
	glm::vec3 m_color{ 1.0f, 1.0f, 1.0f };
	float m_ambientIntensity{ 1.0f };
};
