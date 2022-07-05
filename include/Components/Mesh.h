#pragma once

#include "ECS.h"

class Mesh : public Component {
public:
	Mesh() = default;
	Mesh(float* vertices, unsigned int* indices, unsigned int verticesCount, unsigned int indicesCount, int width, int height)
	{
		FrameBuffer(width, height);
		VertexBuffers(vertices, indices, verticesCount, indicesCount);
	}

	virtual ~Mesh()
	{
		if (m_IBO != 0) {
			glDeleteBuffers(1, &m_IBO);
			m_IBO = NULL;
		}

		if (m_VBO != 0) {
			glDeleteBuffers(1, &m_VBO);
			m_IBO = NULL;
		}

		if (m_VAO != 0) {
			glDeleteVertexArrays(1, &m_VAO);
			m_VAO = NULL;
		}

		if (m_FBO != 0)
		{
			glDeleteFramebuffers(GL_FRAMEBUFFER, &m_FBO);
			glDeleteTextures(1, &m_TexID);
			glDeleteTextures(1, &m_DepthID);
			m_TexID = 0;
			m_DepthID = 0;
		}

		m_indexCount = NULL;
	}

	bool Init() override 
	{
		return true;
	}
	void Update() override 
	{

	}

	void Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		glViewport(0, 0, m_width, m_height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Draw() override 
	{
		Bind();
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		Unbind();
	}

	unsigned int GetTextureID()
	{
		return m_TexID;
	}

private:
	void VertexBuffers(float* vertices, unsigned int* indices, unsigned int verticesCount, unsigned int indicesCount)
	{
		m_indexCount = indicesCount;

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(std::size_t) * indicesCount, indices, GL_STATIC_DRAW);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(std::size_t) * verticesCount, vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void FrameBuffer(int width, int height)
	{
		m_width = width;
		m_height = height;

		glGenFramebuffers(1, &m_FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		glCreateTextures(GL_TEXTURE_2D, 1, &m_TexID);
		glBindTexture(GL_TEXTURE_2D, m_TexID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TexID, 0);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthID);
		glBindTexture(GL_TEXTURE_2D, m_DepthID);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_width, m_height);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthID, 0);

		GLenum buffers[4] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(m_TexID, buffers);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}


private:
	unsigned int m_VAO{ 0 }, m_VBO{ 0 }, m_IBO{ 0 }, m_FBO{ 0 }, m_TexID{ 0 }, m_DepthID{ 0 };
	int m_width, m_height;
	std::size_t m_indexCount{ NULL };
};
