#version 330

smooth in vec2 texturePosition;
noperspective in vec3 normal;
noperspective in vec3 eyeVector;


out vec4 color;

uniform sampler2D textureSampler;
uniform vec3 sunDirection;
uniform vec3 sunColor;
uniform vec3 ambientColor;
uniform int reflectionIntensity;

void main(void)
{
	float intensity = max(0,dot(sunDirection, normal)) + pow(max(0,dot(reflect(-sunDirection, normalize(normal)), normalize(eyeVector))), reflectionIntensity);
	color.rgb = (texture(textureSampler, texturePosition).rgb)*(ambientColor + sunColor*intensity);
	color.a = 1.0;
}