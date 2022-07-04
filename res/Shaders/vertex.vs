#version 330 core

layout (location = 0) in vec3 pos;

out vec4 vColor;

// Imports the camera matrix from the main function
uniform mat4 model;
uniform mat4 camMatrix;

void main()
{
	gl_Position = camMatrix * model * vec4(pos, 1.0);
	vColor = vec4(clamp(pos, 0.0, 0.8), 1.0);
}
