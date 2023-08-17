#version 330 core

out vec4 fragColor;
in vec3 col;

void main() {
    fragColor = vec4(col.x + 0.5, col.y + 0.5, col.z + 0.5, 1.0);
}