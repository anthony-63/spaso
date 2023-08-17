#version 330 core

layout (location=0) in vec3 pos;
out vec3 col;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
    col = pos;
    gl_Position = proj * view * model * vec4(pos, 1.0);
}