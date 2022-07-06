#pragma once

#define HEADER_SIMPLE_OPENGL_IMAGE_LIBRARY

#include "ECS.h"

class Texture : public Component
{
public:
	Texture() = default;
	Texture(const char* texture_location)
	{
		m_textureLocation = texture_location;
		LoadTexture();
	}
	virtual ~Texture()
	{
		glDeleteTextures(1, &m_textureID);
		m_width = m_height = m_bitDepth = NULL;
		m_textureLocation = nullptr;
	}

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

	void UseTexture() const
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}

private:
	void LoadTexture()
	{
		unsigned char* textureData = SOIL_load_image(m_textureLocation, &m_width, &m_height, &m_bitDepth, SOIL_LOAD_RGBA);
		if (!textureData)
		{
			std::cerr << "[ERROR]: Unable to load texture -> " << m_textureLocation << std::endl;
			return;
		}

		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, NULL, GL_RGBA, m_width, m_height, NULL, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
		SOIL_free_image_data(textureData);
	}

private:
	unsigned int m_textureID{ NULL };
	int m_width{ NULL }, m_height{ NULL }, m_bitDepth{ NULL };
	const char* m_textureLocation{ nullptr };
};
