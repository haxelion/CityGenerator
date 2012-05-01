#version 330

smooth in vec2 in_TexturePosition;

out vec4 out_Color;

uniform sampler2D textureSampler;

void main(void)
{
	out_Color = texture(textureSampler, in_TexturePosition);
}