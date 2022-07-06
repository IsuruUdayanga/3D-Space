#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;

out vec4 vColor;
out vec2 TexCord;


uniform mat4 model;
uniform mat4 camMatrix;

void main()
{
	gl_Position = camMatrix * model * vec4(pos, 1.0);
	vColor = vec4(clamp(pos, 0.0, 0.8), 1.0);

	TexCord = tex;
}
