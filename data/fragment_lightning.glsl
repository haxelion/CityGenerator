#version 330

//recuperation des variables envoyees par le vertex shader
smooth in vec2 texturePosition;
smooth in vec3 normal;
smooth in vec3 eyeVector;
//variable contenant la couleur finale du fragment
out vec4 color;
//variable uniformes
uniform sampler2D textureSampler;
uniform vec3 sunDirection;
uniform vec3 sunColor;
uniform vec3 ambientColor;
uniform int reflectionIntensity;

void main(void)
{
	//calcul de l'intensite de la lumiere du soleil du a la diffusion et a la reflexion
	float intensity = max(0,dot(sunDirection, normal)) + pow(max(0,dot(reflect(-sunDirection, normalize(normal)), normalize(eyeVector))), reflectionIntensity);
	//calcul de la couleur finale en fonction de la texture, de la lumiere ambiante et de l'intensite de la lumiere du soleil
	color.rgb = (texture(textureSampler, texturePosition).rgb)*(ambientColor + sunColor*intensity);
	//on definit la face comme opaque
	color.a = 1.0;
}