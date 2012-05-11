#version 330

//recupere les differents attributs du vertex
layout(location=0) in vec3 in_Position;
layout(location=1) in vec2 in_TexturePosition;
layout(location=2) in vec3 in_Normal;

//envoie au fragment shader la position de la texture, la normale et le vecteur camera
smooth out vec2 texturePosition;
smooth out vec3 normal;
smooth out vec3 eyeVector;

//matrice de transformation
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

void main(void)
{
	//calcul de la position dans le repere de la camera
	gl_Position = viewMatrix * vec4(in_Position, 1.0);
	//definition du vecteur camera
	eyeVector = -vec3(gl_Position);
	//projection du vertex
	gl_Position = projectionMatrix*gl_Position;
	//transformation de la normale dans l'espace de la camera
	normal = normalize(normalMatrix*in_Normal);
	//passage des coordonees de la texture
	texturePosition = in_TexturePosition;
}