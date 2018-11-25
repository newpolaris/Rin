#version 450
#extension GL_ARB_separate_shader_objects : enable

const vec3 vertices[] = 
{
	vec3(0.0, 0.5, 0.0),
	vec3(0.5, -0.5, 0.0),
	vec3(-0.5, -0.5, 0.0),
};

void main() {
    gl_Position = vec4(vertices[gl_VertexIndex], 1.0);
}