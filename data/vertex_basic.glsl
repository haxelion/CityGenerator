#version 330

layout(location=0) in vec3 in_Position;
layout(location=1) in vec2 in_TexturePosition;

smooth out vec2 texturePosition;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void)
{
	
	gl_Position = (projectionMatrix * viewMatrix) * vec4(in_Position, 1.0);
	texturePosition = in_TexturePosition;
}