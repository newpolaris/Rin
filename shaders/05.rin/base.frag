#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 outColor;
layout(location = 0) in vec3 color;

void main() {
    outColor = vec4(normalize(color)*0.5 + 0.5, 1.0);
}
