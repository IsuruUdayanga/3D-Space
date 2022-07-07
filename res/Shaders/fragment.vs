#version 330 core

out vec4 color;
in vec4 vColor;
in vec2 TexCord;

uniform sampler2D theTexture;
uniform vec3 ambientColor;
uniform float ambientIntensity;
		
void main()
{
	vec4 ambientColor = vec4(ambientColor, 1.0f) * ambientIntensity;
	color = texture(theTexture, TexCord) * ambientColor;
}
