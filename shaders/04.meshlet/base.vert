#version 450
#extension GL_EXT_shader_8bit_storage : require
#extension GL_EXT_shader_16bit_storage : require
#extension GL_GOOGLE_include_directive : require

#include "mesh.h"

layout(binding = 0) readonly buffer Vertices
{
    Vertex vertices[];
};

layout(location = 0) out vec4 color;

void main()
{
    vec3 position = vec3(vertices[gl_VertexIndex].x, vertices[gl_VertexIndex].y, vertices[gl_VertexIndex].z);
    vec3 normal = vec3(int(vertices[gl_VertexIndex].nx), int(vertices[gl_VertexIndex].ny), int(vertices[gl_VertexIndex].nz)) / 127.0 - 1.0;

    gl_Position = vec4(position*vec3(0.4, 0.4, 0.1) + vec3(0.0, -0.7, 0.5), 1.0);
    color = vec4(normal * 0.5 + vec3(0.5), 1.0);
}