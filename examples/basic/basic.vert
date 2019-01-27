#version 330 core

layout(location = 0) in vec3 a_vertex;

void main() {
    gl_Position.xyz = a_vertex;
    gl_Position.w = 1.0;
}
