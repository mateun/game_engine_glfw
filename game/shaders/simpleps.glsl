#version 450 core

out vec4 color;
uniform sampler2D s;

in VS_OUT {
	vec2 uvs;
	vec2 col;
} ps_in;

in vec2 vs_color;

void main() {
	color = vec4(1, 0.6, 0.0, 1.0);
	color = texelFetch(s, ivec2(1, 0), 0);
	color = texture(s, ps_in.uvs);
	//color = color + vec4(0, 0, 0, 1);
	//color = vec4(ps_in.uvs, 1, 0);
	
}