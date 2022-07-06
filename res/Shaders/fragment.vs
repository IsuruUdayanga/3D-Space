#version 330 core

out vec4 color;
in vec4 vColor;
in vec2 TexCord;

uniform sampler2D theTexture;
		
void main()
{
	color = texture(theTexture, TexCord);
}
