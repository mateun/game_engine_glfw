#version 450

layout (location=0) in vec3 pos;
layout (location=1) in vec3 normal;

uniform mat4 mv;
uniform mat4 proj; 
uniform vec4 baseCol;

out Data {
	vec4 col;
} data;

void main(void) {
	//gl_Position = vec4(0.0, 0.0, 0.f, 1.0);
	// Light position in world coordinates
	vec3 lpos = vec3(-2, -2, -5);
	vec3 mvPos = vec3(mv * vec4(pos, 1.0));
	//vec3 l = normalize(lpos - mvPos);
	vec3 l = vec3(0, 0, 1);
	vec3 n = normalize(vec3(mv * vec4(normal, 0)));
	float diff = max(dot(l,n), 0.1);
	data.col = baseCol * diff;
	gl_Position = proj * mv * vec4(pos, 1.0);
}