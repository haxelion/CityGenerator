#version 330

layout(location=0) in vec4 in_Position;
layout(location=1) in vec2 in_TexturePosition;

smooth out vec2 out_TexturePosition;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void)
{
	
	gl_Position = (projectionMatrix * viewMatrix) * vec4(in_Position, 1.0);
	out_TexturePosition = in_TexturePosition;
}