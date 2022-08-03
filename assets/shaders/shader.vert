#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;

out vec4 color;

void main() {
    gl_Position = projection * view * transform  * vec4(pos, 1.0);
    color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}