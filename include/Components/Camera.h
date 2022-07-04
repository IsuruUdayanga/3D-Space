#pragma once

#include "ECS.h"
#include "Window.h"

class Camera : public Component
{
public:
	Camera() = default;
	Camera(int width, int height, glm::vec3 position)
	{
		this->width = width;
		this->height = height;
		Position = position;
	}

	virtual ~Camera() = default;

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

	void ViewMatrix(float FOVdeg, float nearPlane, float farPlane)
	{
		// Initializes matrices since otherwise they will be the null matrix
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		// Makes camera look in the right direction from the right position
		view = glm::lookAt(Position, Position + Orientation, Up);
		// Adds perspective to the scene
		projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);
		m_projection = projection * view;
	}

	glm::mat4 GetProjection()const
	{
		return m_projection;
	}

	void KeyBaordInputs(int key)
	{
		switch (key)
		{
		case GLFW_KEY_W:
			Position += speed * Orientation;
			break;

		case GLFW_KEY_A:
			Position += speed * -glm::normalize(glm::cross(Orientation, Up));
			break;

		case GLFW_KEY_S:
			Position += speed * -Orientation;
			break;

		case GLFW_KEY_D:
			Position += speed * glm::normalize(glm::cross(Orientation, Up));
			break;

		case GLFW_KEY_Z:
			Position += speed * Up;
			break;

		case GLFW_KEY_X:
			Position += speed * -Up;
			break;

		default:
			break;
		}
	}

	void MouseInput(float rotX, float rotY)
	{
		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			Orientation = newOrientation;
		}

		// Rotates the Orientation left and right
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
	}

private:
	//Stores the main vectors of the camera
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	// Stores the width and height of the window
	int width;
	int height;

	// Adjust the speed of the camera and it's sensitivity when looking around
	float speed = 0.1f;

	glm::mat4 m_projection;
};