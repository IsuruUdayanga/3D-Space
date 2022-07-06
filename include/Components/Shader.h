#pragma once

#include "ECS.h"

class Shader : public Component
{
public:
	Shader() = default;
	Shader(const char* vertexShader, const char* fragmentShader)
	{
		this->vertexShader = ImportShaders(vertexShader);
		this->fragmentShader = ImportShaders(fragmentShader);

		CompileShaderProgram(this->vertexShader.c_str(), this->fragmentShader.c_str());
	}
	virtual ~Shader()
	{
		if (shaderID != NULL)
		{
			glDeleteProgram(shaderID);
			uniformProjection = NULL;
			uniformModel = NULL;
		}
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

	void UseShader()
	{
		glUseProgram(shaderID);
	}
	std::size_t GetUniformModel()
	{
		return uniformModel;
	}
	std::size_t GetUniformProjection()
	{
		return uniformProjection;
	}


private:
	std::string ImportShaders(const char* file)
	{
		std::string fileContent{ " " };
		std::ifstream shaderFile(file, std::ios::in);

		if (!shaderFile.is_open())
		{
			printf("[ERROR]:Unable to open %s.\n", file);
			return fileContent;
		}
		else
		{
			std::string lines{ " " };
			while (!shaderFile.eof())
			{
				std::getline(shaderFile, lines);
				fileContent.append(lines + "\n");
			}

			shaderFile.close();
		}

		return fileContent;
	}
	void CreateShaderProgram(std::size_t shaderProgram, const char* shader, std::size_t shaderType)
	{
		unsigned int shader_ID = glCreateShader(shaderType);
		const char* src = shader;
		const int lenght = strlen(shader);

		glShaderSource(shader_ID, 1, &shader, &lenght);
		glCompileShader(shader_ID);

		int mlenght{ 0 };
		char message[1024] = { 0 };

		glGetShaderiv(shader_ID, GL_COMPILE_STATUS, &mlenght);
		if (!lenght) {
			glGetShaderInfoLog(shader_ID, sizeof(message), &mlenght, message);
			std::cout << "[COMPILE-ERROR]:[" << ((shaderType == GL_VERTEX_SHADER) ? "VERTEX-SHADER] :" : "FRAGMENT-SHADER] : ") << message << std::endl;
			return;
		}

		glAttachShader(shaderProgram, shader_ID);
	}
	void CompileShaderProgram(const char* vertexShader, const char* fragmentShader)
	{
		shaderID = glCreateProgram();
		if (!shaderID) {
			printf("Shader program wasn't create properly.\n");
			return;
		}

		CreateShaderProgram(shaderID, vertexShader, GL_VERTEX_SHADER);
		CreateShaderProgram(shaderID, fragmentShader, GL_FRAGMENT_SHADER);

		int lenght{ 0 };
		char message[1024] = { 0 };

		glLinkProgram(shaderID);
		glGetProgramiv(shaderID, GL_LINK_STATUS, &lenght);
		if (!lenght) {
			glGetProgramInfoLog(shaderID, sizeof(message), &lenght, message);
			printf("[LINK-ERROR]: %s\n", message);
			return;
		}

		glValidateProgram(shaderID);
		glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &lenght);
		if (!lenght) {
			glGetProgramInfoLog(shaderID, sizeof(message), &lenght, message);
			printf("[VALIDATION-ERROR]: %s\n", message);
			return;
		}

		uniformModel = glGetUniformLocation(shaderID, "model");
		uniformProjection = glGetUniformLocation(shaderID, "camMatrix");
	}

private:
	std::size_t shaderID{ NULL }, uniformModel{ NULL }, uniformProjection{ NULL };
	std::string vertexShader, fragmentShader;
};