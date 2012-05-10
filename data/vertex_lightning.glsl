#version 330

layout(location=0) in vec3 in_Position;
layout(location=1) in vec2 in_TexturePosition;
layout(location=2) in vec3 in_Normal;

smooth out vec2 texturePosition;
noperspective out vec3 normal;
noperspective out vec3 eyeVector;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

void main(void)
{
	gl_Position = viewMatrix * vec4(in_Position, 1.0);
	eyeVector = -vec3(gl_Position);
	gl_Position = projectionMatrix*gl_Position;
	normal = normalize(normalMatrix*in_Normal);
	texturePosition = in_TexturePosition;
}