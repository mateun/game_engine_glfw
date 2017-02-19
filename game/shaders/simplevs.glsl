#version 430 core

layout (location = 0) in vec4 pos;
layout (location = 1) in vec2 uvs;
layout (location = 2) in vec2 col;

out VS_OUT 
{
	vec2 uvs;
	vec2 col;
} vs_out;

out vec2 vs_color;

void main(void) {
	gl_Position = pos;
	vs_out.uvs = uvs;
	vs_out.col = col;
	vs_color = col;
	
}